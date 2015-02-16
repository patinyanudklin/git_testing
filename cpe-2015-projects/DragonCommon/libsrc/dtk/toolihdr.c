#include "drelease.h"
char TOOLIHDR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.6 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*
 *	filename toolihdr.c
 *		$Revision: 1.6 $ $Date: 2014/12/17 07:20:39 $	
 *
 *      ~~ Copyright 1999-2014 Kurt Rudahl and Sally Goldin
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *	~~ EndC
 *****************************************************************
 *	$Id: toolihdr.c,v 1.6 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolihdr.c,v $
 *	Revision 1.6  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.5  2006/09/17 05:00:38  rudahl
 *	got rid of 'far' keyword
 *
 *	Revision 1.4  2005/03/19 06:33:30  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.4  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.3  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; except for toolcmd6, much work still needed
 *	
 *	Revision 1.2  2002/04/09 21:35:07  rudahl
 *	adapt for long filenames
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *	
 * Revision 4.3  1997/09/06  06:17:22  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:17:22  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/11/30  15:24:36  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/11/30  15:24:36  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. 
 *    This file contains only fns used as wrappers for hdrstats.c. 
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-02-21 seg	imported from Dragon Academic Edition rev 5.4.4
 * 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
//#include "werror.h"
#include "dhead.h"	/* must preceed toolkit.h */
#include "dragonHd.h"
#include "hdrstats.h"
#include "dtk6.h"
#include "toolerr.h"

//#ifndef TEST

/*************************************************************************
 *
 *		wrappers for hdrstats functions
 *
 *************************************************************************/

void dtk_ImageHdrInit(IHEAD* hdr, const int nl, const int np)
	/*	initialize header to defaults
	 */
    {
    InitNewHdr(hdr,nl,np);
    }

void dtk_ImageHdrSet(IHEAD* hdr, const char* ftype, const char* filename,
	const char* bandn,const char* comment,const char* source,
	const int norm)
	/*	further initialize header */
    {
#ifdef NOTYET
    SetHdrVals(hdr,ftype,  /* if non-null, filetype to set  */
		filename,  /* if non-null, filename to set  */ 
		bandn,     /* if non-null, band num to set  */  
		comment,   /* if non-null, comment to set  */  
		source,    /* if non-null, source string to set  */  
		norm);     /* normalization flag */
#endif
    }

int dtk_ImageCalcStats(const int bitspp,
                       const int bytespp, 
                       const int nl,
	               const int np, 
                       DTK_IMGSTATS stats, 
                       LineAccess linefn)
	/*	calculate statistics line by line, using
	 *	'linefn'
	 *	Return 0 for OK, -1 for error
	 */
    {
    int status;
    status =  CalcImgStats(bitspp,  /* bits per pixel - up to 16 */
                        bytespp,    /* bytes per pix - 1 or 2 */
			nl,np,	/* number of lines & pix to consider   */
			(IMGSTATS*)stats,
    	                        /* ptr to structure for storing results */
			linefn);  /* function to return ptr to line of data */   
    if (status < 0) 
        return DTKE_NOBUF;
    else
        return DTKE_OK;
    }

int dtk_ImageHdrSetStats(const DTK_IMGSTATS stats,IHEAD* inhdr)
    {

#ifdef NOTYET
    int status = SaveHdrStats(NULL,(IMGSTATS*)stats,inhdr);
    if (status < 0)
        return DTKE_BADHDR;
    else
#endif
        return DTKE_OK;
    }

int dtk_ImageHdrRewrite(const char* outname,const DTK_IMGSTATS stats,
                        IHEAD* inhdr)
	/*	Copy image statistics to user-supplied header & write to file
	 *
	 *	Copy previously-calculated statistics stored in 'stats'
	 *	to header structure pointed to by 'hdr', then write that
	 *	header structure to the file indicated by 'outname'.
	 *	'hdr' is assumed to point to a header structure allocated
	 *	by the caller.
	 *
	 *	If 'outname' and no 'inhdr' is supplied, the old header 
	 *	information is read and modified by 'stats', 
	 *	then rewritten in place.
	 *
	 *	Normally, the values in 'stats' will have been calculated
	 *	by dtk_ImageCalcStats().
	 *
	 *	Note that this fn will NOT truncate an existing file.
	 */
    {
#ifdef NOTYET
    int status = SaveHdrStats(outname,(IMGSTATS*)stats,inhdr);
    if (status < 0)
        return DTKE_FILEWRITE;
    else
#endif
        return DTKE_OK;
    }

int dtk_ImageHdrWrite(const char* outname,IHEAD* inhdr)
    {
    if (access(outname,F_OK) == 0)
        return DTKE_FILEALREADY;
    return wsf(outname,inhdr,sizeof(IHEAD),WSF_TRUNC);
    }


int dtk_ImageFileGetHdr(const char* filename, IHEAD* hdr)
	/*	Return copy of information in DRAGON image file header
	 *	Copy the header information from an existing DRAGON image
	 *	file into an IHEAD structure pointed to by 'hdr'.
	 *	Returns 0 or error code.
	 *	ERRORS : return DTKE_NOBUF if 'hdr' not supplied
	 *			DTKE_BADFILENAME if 'filename' has bad form
	 *			DTKE_BADHDR if header read error
	 */
    {
    char name[FMSIZE];
    int status;
    if (hdr == NULL)
	return DTKE_NOBUF;
    status = dtk_FilenameBuild(filename,NULL,"IMG",name,sizeof(name));
    if (status < 0)
	return DTKE_BADFILENAME;
    status = dtk_read(name,0L,(byte *)hdr,sizeof(IHEAD));
    if (status < 0)
	return DTKE_BADHDR;
    return DTKE_OK;
    }

DTK_IMGSTATS dtk_StatStructAlloc()
     /* Create and return a new IMGSTATS structure.
      * This structure is now opaque to the Toolkit user.
      */
    {
    return (DTK_IMGSTATS)ImgStatsAlloc();
    }

void dtk_StatStructFree(DTK_IMGSTATS stats)
     /* Free an IMGSTATS structure.
      * This structure is now opaque to the Toolkit user.
      */
    {
    if (stats != NULL)
        ImgStatsFree(stats);
    }

void TOOLIHDR_END()     { puts(FIL_ID); }

#ifdef TEST

#include <stdlib.h>
void main()
    {
    char buf[80];
    int status;
    dtk_init(NULL);
    printf("DRAGON %s running\n",
	(dtk_DragonIsRunning()) ? "IS" : "is NOT");
    }
#endif
