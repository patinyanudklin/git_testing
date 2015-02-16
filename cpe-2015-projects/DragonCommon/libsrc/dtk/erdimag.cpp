static char sccsidV[] = "(@)#ERDIMAG.CPP $Date: 2014/12/17 07:20:39 $ $Revision: 1.3 $";
/****************************************************************/
/*
 *		>> ERDIMAG.CPP <<
 *
 *          by K.T. Rudahl
 *          $Revision: 1.3 $ $Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1991-2014 by Goldin-Rudahl Associates
 *                            P.O. Box 9648
 *                            North Amherst, MA 01059 U.S.A.
 *	    ~~ EndC
 ***************************************************/
//  $Id: erdimag.cpp,v 1.3 2014/12/17 07:20:39 rudahl Exp $
//  $Log: erdimag.cpp,v $
//  Revision 1.3  2014/12/17 07:20:39  rudahl
//  consolidating Dragon and OpenDragon
//
//  Revision 1.2  2000/06/03 14:46:23  rudahl
//  fixes for SuSE6.3 GCC
//
//  Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
//  first checkin of only SOME common dirs
//
// Revision 1.2  92/06/02  18:42:12  tower
//  For Zortech 3.0 and first release of TIF2DRAG & DRAGSCAN
//  This is the first released version of this file
// Revision 1.1  92/04/30  14:50:40  tower
//    Initial revision
//
/***************************************************
 *	This is the ERDAS class definitions for use with
 *	IMAGFILE etc
 *
 ****************************************************************/
/*    Modification History
 *
 * Version	Who		What & Why
 * 1.0	3/8/92	ktr	extracted from IMAGFILE.CPP
 * 1.1  5/26/92	ktr	updated to Zortech 3.0
 * 4.1	1/13/95	ktr	changed calling params of init() &&
 *			initcore during read: added bits & bands
 *	12/30/95 ktr	added zfile prototypes, for compat w/ MSC etc
 * 5.0	6/22/97 ktr	some changes for Watcom just to get it to compile.
 *			Probably correct but untested.
 *      6/3/00 ktr      changed spelling of errn to match ob.h, for MSVC
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#ifdef __GCC__
#include <unistd.h> /* for access() */
#else
#include <dos.h>
#include <io.h>
#endif
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
//#include <sys\stat.h>

#include "dtypes.h"
#include "dlimits.h"
extern "C" {
#include	"ztoolkit.h"
#include	"zfilespc.h"
#include        "zfile.h"
#include "files.h"
#include "iff.h"
#include "filename.h"
  }

#include "dhead.h"	/* for IHEAD structure */
#include "hdrstats.h"
#include "foreign.h"	/* for Zucchini,Erdas,EPPL7-must FOLLOW DHEAD.H */
#include "tiff.hpp"

#ifndef FARNULL
#define FARNULL (void far *) 0L
#endif

#define ERDAS_IF
#include "toolerr.h"
#include "ob.h"
#include "imagfile.h"

/**********************************************************
 *
 *	ERDAS class fns
 *
 **********************************************************/

static Class class_ErdasFile("Erdas Image File",2);

ErdasFile::ErdasFile(const int fmode,const int buffersize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    File::init(fmode,buffersize);
    verifier = ErdasFile::verify_filename;
    }

#ifdef NOMORE
const int ErdasFile::access(const char * fname,const int buffersize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    int tmp=File::access(fname,buffersize);
    if (tmp<0)
	return tmp;
    return erdinit();	// default pix, lines = 0,0
    }

const int ErdasFile::access(const char * fname,
	    const long pix,const long lines,const int buffersize)
	//	This version of access() is different for write-modes only
	//	and permits setting target IMGCORE parameters
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    int tmp=File::access(fname,buffersize);
    if (tmp<0)
	return tmp;
    return erdinit(pix,lines);
    }
#endif

const int ErdasFile::init(const long pix,const long lines,
			const int bits,const int bands)
    {
    hdr->file = this;
    hdr->header = new ERDHEAD; 
    if (hdr->header == NULL)
	return(errn = FILE_NOMEM);
    hdr->init(this,sizeof(ERDHEAD),0);	// read or clear header
    eversion = (strncmp(idiohdr()->hdr,"HEADER",6)==0) ? 73 : 74;
/***  the following msg is not correct for erdas ***
printf("ERDAS File Header initialized: image is %d x %d\n",
	((IHEAD *)hdr->header)->fields.size[1],	
	((IHEAD *)hdr->header)->fields.size[0]);
*/
    if (errn)
	return errn;
    initcore(pix,lines,bits,bands);
    return errn;
    }

const int ErdasFile::capabilities()
    {
    return(C_IDENTIFY | C_TEST | C_READ_HDR | C_READ );
    }

const char * ErdasFile::band_id(const int band,const int detail)
	//	return a string identifying the specified band
	//	If 'detail'==0, return full string
	//	else a 1-char long string for synthesizing file names
	//	Return NULL if no multiband capabilities exist or error
    {
    static char * id[MAX_ERDBAND] = { "1","2","3","4","5","6","7" } ;
    static char temp[8] = "Band ";
    if ((band < 0) || (band > MAX_ERDBAND))
	return NULL;
    if (detail == 1)
	return id[band];
    strcpy(&temp[5],id[band]);
    return temp;
    }

const char ** ErdasFile::about(const int detail)
	//	return descriptive string:
	//	detail == 0-4 use ImageFile::about()
	//		  5 => up to two lines of info - adds comment
	//		  6 => more info - filetype specific
	//		  7 => lots of lines of info - not for DRAGON
    {
    const char ** retval = ImageFile::about(detail); // clear array, set line 0
/*	we don't really know much about Erdas header structure 
    if ( (errn==0) && (detail > 4) )
	{
	switch(detail)
	    {
	    case 6:
	    default:
		char tmp[80];
		sprintf(tmp,"scene: %-16s \tsubscene: %-16s \tband: %-3s",
		    idiohdr()->fields.scene+1,idiohdr()->fields.subscene+1,
		    idiohdr()->fields.band+1);
		isA()->obdesc_put(tmp,2);
		sprintf(tmp,"filetype %c \t\t\tsource: %-3s",
		    idiohdr()->fields.ftype,idiohdr()->fields.source+1);
		isA()->obdesc_put(tmp,3);	// fall through
	    case 5:
		if (strlen(idiohdr()->fields.comment) > 1)
		    isA()->obdesc_put(idiohdr()->fields.comment+1,1);
		break;
	    }
	}
*/
    return retval;
    }

Class * ErdasFile::isA() const  
	{ return &class_ErdasFile; }
const Class * ErdasFile::desc() 
	{ return &class_ErdasFile; }

