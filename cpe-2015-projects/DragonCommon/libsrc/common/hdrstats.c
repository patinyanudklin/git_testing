#include "drelease.h"
ID_ HDRSTATS_ID[]
   ="\0@(#) " __FILE__ " $Revision: 1.29 $ $Date: 2014/12/29 03:28:29 $";
D_REL_IDSTR;
/*
 *	HDRSTATS.C   DRAGON header statistics calculation and writing.
 *		Extracted from fconvert.c
 *      ~~ Copyright (C) 1992-2014 Kurt Rudahl and Sally Goldin
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
 ************************************************************************
 *   $Id: hdrstats.c,v 1.29 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: hdrstats.c,v $
 *   Revision 1.29  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.28  2014/12/27 10:02:17  rudahl
 *   fix fail to do Lin auto stretch in OD only
 *
 *   Revision 1.27  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.26  2014/12/05 14:24:30  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.25  2008/04/27 06:01:08  rudahl
 *   improved notices, tracing
 *
 *   Revision 1.24  2007/08/02 12:44:42  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.23  2006/11/25 10:04:33  goldin
 *   Fix histogram calc and display for 16 bit images
 *
 *   Revision 1.22  2006/02/12 10:44:34  goldin
 *   Fix minor calculation error
 *
 *   Revision 1.21  2005/12/10 11:41:34  rudahl
 *   cleaned out obsolete
 *
 *   Revision 1.20  2005/03/19 11:07:40  rudahl
 *   lintish
 *
 *   Revision 1.19  2005/02/28 20:45:09  goldin
 *   Remove obsolete doc from file comment
 *
 *   Revision 1.18  2005/02/15 19:17:51  rudahl
 *   lint-ish
 *
 *   Revision 1.17  2005/02/11 00:56:34  rudahl
 *   converting
 *
 *   Revision 1.16  2005/02/11 00:54:27  rudahl
 *   converting
 *
 *   Revision 1.15  2005/01/30 06:58:49  goldin
 *   Added comments and recommendations for migration to OpenDragon
 *
 *   Revision 1.14  2005/01/30 03:53:44  rudahl
 *   initial conversion for v 5.5
 *
 *   Revision 1.13  2004/12/12 05:53:29  goldin
 *   Don't wipe out old georef information in SetHdrTo4.01 
 *   also set cell size to 1 not 0.
 *
 *   Revision 1.12  2004/12/04 06:05:37  rudahl
 *   adapt for Mi gw
 *
 *   Revision 1.11  2002/09/05 18:56:53  goldin
 *   Fix calculation of mean - clip to img max
 *
 *   Revision 1.10  2002/07/13 00:37:01  rudahl
 *   got rid of mem_ ops in 32-bit
 *
 *   Revision 1.9  2002/06/25 13:54:53  rudahl
 *   excluded some unused from 16-bit
 *
 *   Revision 1.8  2002/06/14 23:55:57  goldin
 *   Don't zero out the uKey field in sethdrtocurrent
 *
 *   Revision 1.7  2002/05/08 00:12:20  rudahl
 *   new header version * fields
 *
 *   Revision 1.6  2002/04/19 22:33:17  goldin
 *   Clamp 8 bit mean to 255
 *
 *   Revision 1.5  2002/04/09 21:31:33  rudahl
 *   adapt for long filenames
 *
 *   Revision 1.4  2002/01/15 17:24:50  rudahl
 *   removed some deadwood
 *
 *   Revision 1.3  2001/08/22 18:22:27  rudahl
 *   fixup for gcc
 *
 *   Revision 1.2  1999/04/18 21:25:55  rudahl
 *   Minor changes for MSC 32 compile
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.4  1998/02/22  05:15:46  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1998/02/22  05:15:46  tower
 * checkin for class CLASS5_0
 *
 ************************************************************************
 *   5/16/92    SEG	Revamped - changed function names and parameters,
 *			made more general, in preparation for use in
 *			DRAGON Toolkit. Extracted from DRAGON & FCONVERT.
 *   5/30/92    SEG	Added new functions to do incremental statistics
 *			calculation, line by line.
 *   6/1/92	ktr	changed SaveHdrStats to be able to use a local header
 *			initialized by reading file.
 *     7/12/92  ktr	fixed string assignments in header to not be
 *			dependent on magic numbers.
 *			 to use  pointer to IHEAD
 *   6/04/93 	seg	Added maskbuffer params to NextLineCalc.    
 *   12/21/93 	seg	Modified to replace floating point arithmetic
 *			 with explicit function calls - to simplify
 *			 handling other compilers in Toolkit    
 *   04/24/94   seg     Added code to handle possibility of > 8 bits/pix
 *	6/24/94 ktr	added hdr initialization for calibrated z_ data
 *   07/17/94   seg     Revamped to speed up, revise handing of > 8 bits/pix
 *                      Modified calling parms of many functions, to
 *                       help us detect inconsistencies.
 *                      Added ImgStatsAlloc, ImgStatsFree
 *                      Added test module at end (compile -dTEST)
 *   7/19/94 ktr	minor fixes for MSC v 8
 *   10/18/94 ktr	added missing hdr inits for classname stuff, and
 *			revised for EXTended classnames for v 4.1
 *    12/4/94 ktr	created     SetHdrToCurrent(hdr);
 *    12/12/94 ktr	changed ftype in header to ftype[]
 *    12/26/94 seg	Modified CalcImgStats to use InitLineCalc, etc.,
 *                      thus eliminating duplicate code. 
 *    1/22/95 ktr	minor syntax changes for MSC v 8.5
 * 5.0	12/10/95 ktr	adapt for Watcom 10.0, MSC 8.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *	1/19/98 ktr	updated SetHdrToCurrent for 5.0 hdr
 *			changed VERSION to HEADER_VERSION in DRAGON.H
 *	2/98 ktr	mod NextLineCalc to include the mask info for
 *			 multibyte (why was it excluded?)
 *			 'tho mask itself must be 8-bit
 * 5.4	12/1/2004 ktr	adapt to Mingw
 * 5.5	2005-1-23 ktr	convert for v 5.5. Delete 16 bit stuff. New dhead.h.
 * 5.7	2005-12-9 ktr	cleaned out spurious double-tildes
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 ************************************************************************
 *
 *   This module includes routines related to calculating
 *   image statistics. 
 *
 *
 *   InitLineCalc  - set up for accumulating statistics data
 *   NextLineCalc  - accumulate stats from a single line
 *   FinishLineCalc - calculate statistics based on accumulated data,
 *		     and return in passed structure
 *
 *   ImgStatsAlloc  - Allocate & return ptr to new IMGSTATS structure
 *   ImgStatsFree   - Free passed IMGSTATS structure, including
 *                     -alloced subhistogram ptrs, if needed 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy */
#include <math.h>

#if defined __GCC__
#include <sys/stat.h>
#else
#include <sys\stat.h>
#include <dos.h>
#include <io.h>
#endif
#include <errno.h>
#include <limits.h>    /* USHRT_MAX */

#ifdef TEST
#include <fcntl.h>
#endif

#include "dtypes.h"
#include "dlimits.h"

#include "dhead.h"
#include "img.h"
#include "files.h"
#include "hdrstats.h"
#include "i18n.h"

void HDRSTATSX() { }

/* SEG 1/30/05  This functionality should be replaced by new
 * header class functions.
 */

#ifdef NOMORE
void SetHdrToCurrent(IHEAD  * hdr)
	/*	make sure all version-specific info is set consistently
         *      used here and in imagsw-o.c.
         *      prototype is in DRAGON.H
	 */
    {
    int iClsNum;
    hdr->fields.vn = 5.04;
    hdr->fields.charsize = 2;	/* i.e. classnames are Unicode 2-byte form */
    hdr->fields.class_namesz = EXT_CLASS_NAMESZ;
    hdr->fields.numlabels = NUMLABELS;
	/* make sure floats have valid 0 value */
    hdr->fields.dScaleFactor = 0.0;	/* new for 5.0 */
    hdr->fields.dScaleOffset = 0.0;	/* new for 5.0 */
    hdr->fields.uEncoding = 'SR';
	/* following is a permanent (5.0 & up) file ident. signature: */
	/* exactly 4 bytes located just before the version # */
    memcpy(hdr->fields.cMagic,"GRSI",sizeof(hdr->fields.cMagic));
		/* for v 5.4, need to setup LabelInfo, numlabels */
    hdr->fields.numlabels = 0;
    for (iClsNum=0; iClsNum<NUMLABELS; iClsNum++)
        {
	UNICODE_WCHAR  * pN 
		=(UNICODE_WCHAR  *)hdr->fields.dclass.extname[iClsNum].name;
#if defined __MINGCC__
	if (grs_wcslen(pN) > 0)
	    hdr->fields.numlabels++;
#else
	if (wcslen(pN) > 0)
	    hdr->fields.numlabels++;
#endif
	   /* following just some reasonable values */
	hdr->fields.LabelInfo[iClsNum].uValue = iClsNum;
	hdr->fields.LabelInfo[iClsNum].uColorNdx = iClsNum;
	hdr->fields.LabelInfo[iClsNum].cKeyChar = '\0';
	}
    if (hdr->fields.ftype[0] == 'C')
        hdr->fields.numclasses = hdr->fields.imgmax + 1 ;
    //hdr->fields.uKey = 0;
    /* don't do this - wipes out previously set info! */
    hdr->fields.iff_offset = 0;
    }

void SetHdrTo401(IHEAD  * hdr)
	/*	fixul older hdrs to 4.1. This assumes the fields
	 *	being set did not contain useful info.
         *      prototype is in DRAGON.H
	 */
    {
    hdr->fields.bits_per_pix = 8; /* default - calling pgm can change ... */
    hdr->fields.z_scale = 1.0;	/* for 4.1 */
    hdr->fields.z_offset = 0.0;
    hdr->fields.z_unit[0] = '\0';
    hdr->fields.z_unitlen = 0;
//    hdr->fields.imgvar= 0.0;
//    hdr->fields.imgsd = 0.0;
    /* A pre-4.01 image could have georeferencing info from REGISTER. 
     * We don't want to wipe this out. 
     *
     * However, this is has a very slight risk. If an old Dragon
     * file had garbage in it's header, and the georef_init flag
     * just happened to be 1, then we could be leaving garbage
     * in the floating point fields that might cause a crash if
     * some other function tried to interpret them as floating
     * point values.  SEG 12/12/2004 
     */
    if (hdr->fields.georef_init != 1)
       {
       hdr->fields.georef_init = 1;
       hdr->fields.img_x = 0;
       hdr->fields.img_y = 0;
       hdr->fields.ref_x.v0 = 0.0;
       hdr->fields.ref_y.v0 = 0.0;
       hdr->fields.xcell_size = 1.0;
       hdr->fields.ycell_size = 1.0;
       }
    hdr->fields.charsize = 2;	/* i.e. classnames are Unicode 2-byte form */
    hdr->fields.vn = 0x401;
    }
#endif

#ifdef DTK_NOMORE 

/* SEG 1/30/05  This functionality should also be replaced by new
 * header class functions and/or by the Image class. It is 
 * not relevant to calculating statistics.
 */

void InitNewHdr(IHEAD  * hdr, const int nl,const int np)
	/*	initializes a new img header 'hdr' to default values,
	 *	and sets number of lines, number of pixels fields.
	 *	An img saved with this header should not blow up in DRAGON.
	 */
    {
    memset(hdr->buffer,0,DHEAD); /* start by zeroing it all */
    hdr->fields.size[0] = (ushort)nl;
    hdr->fields.size[1] = (ushort)np;
    hdr->fields.fnlen = 0;
    hdr->fields.ftype[0] = 'I'; /* Image is default */
    SetHdrTo401(hdr);
    SetHdrToCurrent(hdr);
    hdr->fields.bits_per_pix = 8; /* default - calling pgm can change ... */
    hdr->fields.z_scale = 1.0;	/* for 4.1 */
    hdr->fields.z_offset = 0.0;
    hdr->fields.z_unit[0] = '\0';
    hdr->fields.z_unitlen = 0;
    hdr->fields.imgvar= 0.0;
    hdr->fields.imgsd = 0.0;
    hdr->fields.norm = 0;
    hdr->fields.upper = 255;
    hdr->fields.lower = 0;
    hdr->fields.clsname_offset = (unsigned long)
		((byte  *)hdr->fields.size - (byte  *)&(hdr->fields.dclass));
    hdr->fields.georef_init = 1;
    hdr->fields.img_x = 0;
    hdr->fields.img_y = 0;
    hdr->fields.ref_x.v0 = 0.0;
    hdr->fields.ref_y.v0 = 0.0;
    hdr->fields.xcell_size = 1.0;
    hdr->fields.ycell_size = 1.0;
    memcpy(hdr->fields.unitname,"Pixels",sizeof(hdr->fields.unitname)-1);
/*    strncpy(hdr->fields.unitname,"Pixels",sizeof(hdr->fields.unitname)-1); */
    hdr->fields.unlen = (char)strlen("Pixels");
/*    hdr->fields.unlen = strlen(hdr->fields.unitname); */
    }

/**/

/* SEG 1/30/05  This functionality should be replaced by new
 * header class functions and/or by the Image class. It is 
 * not relevant to calculating statistics. It is not used
 * anywhere in Dragon as far as I can tell.
 *
 * The purpose is to set or initialize non-statistics fields 
 * in a header that is about to be written.
 */

void SetHdrVals(IHEAD  * hdr,	/* header struct to modify */
		const char *ftype,	/* if non-null, filetype to set  */
		const char* filename,	/* if non-null, filename to set  */
		const char* bandn,	/* if non-null, band num to set  */
		const char* comment,	/* if non-null, comment to set  */
		const char* source,	/* if non-null, source string to set */
		const int norm)		/* normalization flag */
	/*	Initialize selected fields in the
	 *	passed header structure 'hdr', with passed values.
	 *	We assume that InitNewHdr was called first to
	 *	make sure all fields were initialized to zero.
	 */
    {
    if ((ftype != NULL) && (*ftype != 0))
	hdr->fields.ftype[0] = *ftype;
    if (filename != NULL)
	{
	char * fnamebuf = strdup(filename);
	if (fnamebuf != NULL)
	    {
	    char * node = NULL, * ext = NULL;
	    if (strsfn6_grs(fnamebuf,NULL,NULL,&node,&ext,NULL) == 0)
	        {
		if (ext != NULL)
		    *(ext-1) = '.'; /* restore period */
		memcpy(hdr->fields.fname,strupr(node),
			 sizeof(hdr->fields.fname)-1);
		}
	    hdr->fields.fnlen = 0xFF & strlen(node);
	    /* we assume here that the user passes a valid filename */
	    /* otherwise, we are just going to truncate it. */
	    free(fnamebuf);
	    }
	}
//printf("hdrstats SetHdrVals name copied\n");
    if (bandn != NULL)
	{
	memcpy(&hdr->fields.band[1],bandn,sizeof(hdr->fields.band)-2);
/*	strncpy(&hdr->fields.band[1],bandn,sizeof(hdr->fields.band)-2); */
       /* 1st byte is length byte */
	hdr->fields.band[0] = (char)strlen(bandn);
	}

    if (comment != NULL)
	{
	memcpy(&hdr->fields.comment[1],comment,
		 sizeof(hdr->fields.comment)-2);
/*	strncpy(&hdr->fields.comment[1],comment,sizeof(hdr->fields.comment)-2); */
	/* 1st byte is length byte */
	hdr->fields.comment[0] = (char)strlen(comment);
	}
    if (source != NULL)
	{
	memcpy(&hdr->fields.source[1],source,
		 sizeof(hdr->fields.source)-2);
/*	strncpy(&hdr->fields.source[1],source,sizeof(hdr->fields.source)-2); */
	/* 1st byte is length byte */
	hdr->fields.source[0] = (char)strlen(source);
	}
    hdr->fields.norm = (ushort)norm;
    }

/**/

/* SEG 1/30/05  This functionality is not used in Dragon,
 * at the moment, but I think it should be retained here.
 * It is a way to calculate statistics that is independent
 * of image data access method, very useful for toolkit 
 * and quick development of new operations.
 *
 * The Server source file imstat-o includes the function
 * imstatcalc, which is similar in structure. This is
 * what is used to calculate image statistics in Dragon.
 * The primary differences are as follows:
 *    - imstatcalc takes an optional pointer to a stretch table which
 *      might be applied to data read before calculating the
 *      stats
 *    - imstatcalc takes a flag indicating whether there is a 
 *      mask image, which might be applied to the data before stats calculation
 *    - imstatcalc uses info in the image structure to determine dimensions
 *      and data size (8 bitspp or more). It is passed an image index for
 *      the main image and converts this to an image pointer.
 *    - imstatcalc is not data-access neutral. It uses GetImageLineP and
 *      is in img_acc, to get at the primary data. It also a set of
 *      functions MaskImageInitialize, MaskImageSeek, etc to get at
 *      the mask image data. These functions, for some reason, are
 *      in dragonu.c. Note that imstatcalc does not get passed an
 *      actual image pointer to the mask image or even an index. It
 *      assumes it should use image element MASKIMAGE if the bMask
 *      flag is set to true.
 *    - imstatcalc potentially returns richer error data. Here, the
 *      only way to signal an error in linefn is by returning a null.
 *
 */

int CalcImgStats(const int bitspp,  /* bits per pix  */
                 const int bytespp, /* bytes per pix  */
		 const int nl,     /* number of lines to consider   */
		 const int np,     /* number of pixels to consider per line  */
		 IMGSTATS* stats, /* ptr to structure for storing results */
		 LineAccess linefn)  /* function to return lines of data */
	/*	calculates and returns the mean, variance, max value,
	 *	min value, and histogram for an image in memory or in a file.
	 *	It considers the first 'nl' lines and 'np' pixels per line.
	 *	'bitspp' controls how the histogram is constructed -
         *      as a flat array of counts or as an array of pointers
         *      to secondary array.
	 *	Results put into 'stats' which is passed by the caller.
	 *	'linefn' is a void* (*fn)(int line) returning 
         *      a buffer corresp to 'line'. Depending on the value
         *      of bytespp (1 or 2) we cast the result to a byte* or
         *      an unsigned short*. 
	 *	This version intended for toolkit.
	 *	We assume that the caller has done
	 *	whatever is necessary to initiate the data access
	 *	mechanism (e.g. opening a file or a virtual file, seeking
	 *	past the header, etc). Similarly the caller must do
	 *	any cleanup that is required (e.g. closing a file,
	 *	releasing the data buffer, etc.)
	 *	The buffer for returning data is private to linefn
	 *	- we just get back a pointer to the buffer.
	 *	If this pointer is NULL,
	 *	an error has occurred and we should quit this function.
	 *	Returns 0 if OK, negative if error
         *     
         *      SEG, modified 7/17/94 to handle > 8 bit data 
	 */
    {	
    int lin;
    void * returnbuf;
    InitLineCalc(nl,np,bitspp,bytespp,stats);

    /* now we loop through the pixels in the file, calculating histogram */
    for (lin = 0; lin < nl; lin++)
	{
	returnbuf = (*linefn)(lin);
	if (returnbuf == NULL)
	    {
	    stats->hist.imghist[0] = 0L; /* signal error indirectoy */
	    return(-1);
	    }
        NextLineCalc(returnbuf,NULL,0,stats);
	} /* end of line by line calcs */
    FinishLineCalc(stats);
    return(0);
    }

#endif // #ifdef DTK

// next two used in DTK and in imstat-o
/* SEG 1/30/05 These two functions belong here. They
 * encapsulate knowledge about the detailed structure
 * used to accumulate statistics info during calculations  
 * and finalize it afterwards. Also knows about the different
 * histogram structure used for 16-bit data calculations.
 */
/**/
IMGSTATS * ImgStatsAlloc()
        /*  Allocates a new image statistics structure in 
         *  near memory and returns a pointer to it.
         *  Will return a NULL ptr if insufficient memory.
         */
   {
   IMGSTATS * stats = calloc(sizeof(IMGSTATS),1);
   return stats;   
   }    


/**/
void ImgStatsFree(IMGSTATS* stats)
        /*  Frees an image statistics structure.
         *  Uses the contents to see if it is also necessary to
         *  free any  pointers to memory allocated during the
         *  calculation of stats. 
         */
   {
   if (stats == NULL)
       return;
   if (stats->bits_per_pix <= 8)  /* will be 0 if never used */
       free(stats);               /* will be 8 for 1 byte data */
   else 
       {
       int i;
       for (i = 0; i < IMG_HIST_LEN - 1; i++)
           if (stats->hist.ptrhist.ptr_array[i] != NULL)
               {
               free(stats->hist.ptrhist.ptr_array[i]);
               }
       free(stats);
       }
   }    

/**/
// next four used for toolkit and dragreg.c

/* SEG 1/30/05 SaveHdrStats is no longer used
 * in Dragon. I think this should be replaced with
 * a function that takes a header and an IMGSTATS
 * pointer and copies the statistics to the right places
 * in the header, but does not do any file I/O.
 *
 * (Also this function uses superceded header functions
 * defined earlier in this module, which are now obsolete).
 *
 * For the moment, I have conditionally removed this function.
 */
 
#ifdef NOMORE
int SaveHdrStats(const char* outname,const IMGSTATS* stats,IHEAD  * hdr)
	/*	Initializes header structure 'hdr' with precalculated
	 *	image statistics from 'stats'.
	 *	If 'hdr' is NULL and 'outname' is not, uses
	 *	  a local hdr initialized by reading 'outname'.
	 *	If 'stats' is NULL, it is ignored.
	 *	Then, if 'outname' is not NULL,
	 *	  writes the header to the DRAGON image file specified.
	 *	Assumes that 'hdr' already has the
	 *	number of lines and pixels per line fields set.
	 *	Returns 0 if OK, or negative number if wsfo error.
	 *
	 *	Note that this fn will NOT truncate an existing file.
	 */
    {
    int status = 0;
    int i,j,k,kk;
    
    IHEAD * lochdr=NULL;
    IHEAD  * inhdr = hdr;
    if (hdr == NULL)
	{
	if (outname==NULL)
	    return -1;
	lochdr=malloc(DHEAD);
	if (lochdr==NULL)
	    return -1;
	inhdr = lochdr;
	if ((status=rsf(outname,inhdr,sizeof(IHEAD),0L,0))<= 0)
	    {
	    free(lochdr);
	    return status;
	    }
	}
    SetHdrToCurrent(inhdr);
    /* want to always set new header fields to be current version */
    if (stats != NULL)
        {
        inhdr->fields.imgmean = stats->imgmean;
        inhdr->fields.imgmax = stats->imgmax;
        inhdr->fields.imgmin = stats->imgmin;
        inhdr->fields.imgvar = stats->imgvar;
        inhdr->fields.imgsd = stats->imgsd;

        inhdr->fields.bits_per_pix = stats->bits_per_pix;
        inhdr->fields.histo[0] = stats->hist.imghist[0]; /* added 12/4/94 SEG */

        for (i = 1; i < HDR_HIST_LEN; i++)
            {
            inhdr->fields.histo[i] = 0L;
            if (inhdr->fields.bits_per_pix <= 8)
                {
                if (inhdr->fields.ftype[0] == 'I')
                    {
                    /* bin by fours for saving in the header */
                    for (j = 0; j < 4; j++)
  	              inhdr->fields.histo[i] += 
                          stats->hist.imghist[(i-1)*4+1+j];
                    }
                else  /* for classified images, etc., do not bin */
                      /* just copy the first 64 values */
                    {
                    inhdr->fields.histo[i] = 
                          stats->hist.imghist[i];
                    }

                }  /* end if bpp <= 8 */
            else
                {
                k = (i-1) * 4;
                for (j = 0; j < 4; j++)
                    {
                    if (stats->hist.ptrhist.ptr_array[k+j] == NULL)
                       continue;
                    for (kk = 0; kk < IMG_HIST_LEN -1; kk++)
    	                inhdr->fields.histo[i] += 
                           stats->hist.ptrhist.ptr_array[k+j][kk];
                    }                        
               }  /* end if > 8 bpp */
            }   /* end for loop through header histogram */
        }
    if (outname != NULL)
	status = wsfo(outname,inhdr,sizeof(IHEAD),0L);	
    if(lochdr)
	free(lochdr);
    return status;
    }
#endif

/* SEG 1/30/05 InitLineCalc is used in imstat-o (for dragon)
 * It should be kept, and probably here is a good place for it.
 */

/*****/
void InitLineCalc(const int nl,  /* number of lines to be processed */
		  const int np,  /* number of pixels per line       */
		  const int bitspp, /* bits per pixel */
		  const int bytespp, /* bytes per pixel */
		  IMGSTATS * stats)  /* structure for holding the info */
	/*  Initialize static variables used calculating line by line
	 *  statistics.
	 */
   {
   int i;

   stats->numlines = (unsigned short)nl;
   stats->numpix = (unsigned short)np;
   stats->bits_per_pix = (unsigned short)bitspp;
   stats->bytes_per_pix = (unsigned short)bytespp;

   if (bitspp <= 8)
       for (i = 0; i < IMG_HIST_LEN; i++)
           stats->hist.imghist[i] = 0L;  /* initialize histogram array  */
   else
       {
       for (i = 0; i < IMG_HIST_LEN-1; i++)
           stats->hist.ptrhist.ptr_array[i] = NULL;
       stats->hist.ptrhist.histcount = 0L;
       } 
   stats->sum = 0.0;
   stats->sumsq = 0.0;
#if DRAGON_VER >= 6
   stats->m_ihImgmin = INT_MAX;
   stats->m_ihImgmax = INT_MIN;
#else
   stats->imgmin = SHRT_MAX;
   stats->imgmax = 0;
#endif
   }

/* SEG 1/30/05 NextLineCalc is used in imstat-o (for dragon)
 * It should be kept, and probably here is a good place for it.
 */

/**/
void NextLineCalc(const void  * databuf,
                  const byte * maskbuf, 
                  const int maskpix,
                  IMGSTATS * stats)
       /*  Accumulate data for statistics calculation, based on
	*  information in the passed buffer 'databuf'. Assumes
	*  that the user wants to process 'numpix' elements (initialized
	*  based on 'np' passed to the InitLineCalc function.
        *  If maskbuf is not NULL, use the data in that buffer
        *  to select pixels to include in the processing.
        *  Only include a pixel if the corresponding mask buffer 
        *  element is non-zero. Maskpix is number of data bytes
        *  in maskbuf. If this is fewer than the size of databuf,
        *  all additional pixels ARE included in the calculations.
        *
	* NOTE that this fn is not limited in the image size it can
	*	process. There are no local buffers.
	*
        *  4/24/94 add ability to handle data > 8 bits/pix 
        *  in this case, we assume that databuf is really an
        *  (unsigned short  *). We ignore the mask for > 8 bit data. 
	*
        *  2/98 mod to include the mask info for multibyte
	*	(why was it excluded?), 'tho mask itself must be 8-bit
	*/
    {
    int pix;
    int bin,bin2;
    int np;
    const ushort  * ushortbuf = databuf;  /* for multibyte data */
    const byte  * bytebuf = databuf;	
        /* flag telling us whether histogram is flat or extended */
    int bMultibyte = (stats->bits_per_pix > 8) ? 1 : 0 ;
    int shift = (bMultibyte) ? 8 : 0;
    ulong linetot = 0L;
    np = stats->numpix;

    for (pix = 0; pix < np; pix++)
	{
	ushort val;
	if ((maskbuf == NULL) || (pix >= maskpix) || (maskbuf[pix] != 0))
	    {
	    if (bMultibyte)
		val = ushortbuf[pix];
	    else 
                val = (ushort) bytebuf[pix]; 
	    linetot++;
	    bin = (val >> shift) ;  /* calc primary bin number */
	    if (!bMultibyte)         /* 8 bit data, bin numbering starts */
                                   /* at 1 */ 
                {
                bin += 1;
                stats->hist.imghist[bin]++;  /* increment the appropriate bin */
                /* for 8 bit data, we use a flat array */
                }
	    else  /* otherwise, build subsidiary structures */
                {
                bin2 = val & 0x00FF;  /* get low order byte */
                if (stats->hist.ptrhist.ptr_array[bin] == NULL)
                   /* this sub-bin not in use yet - allocate a */
                   /* 256 element subarray of unsigned longs   */
                    {
		    ulong  * subarray = (ulong *) calloc(IMG_HIST_LEN-1, sizeof(ulong));
                    if (subarray == NULL)
                        {
                        stats->hist.ptrhist.histcount = 0L;  /* error signal */  
                        return;
                        }
		    memset(subarray,0,IMG_HIST_LEN-1 * sizeof(ulong));
                    stats->hist.ptrhist.ptr_array[bin] = subarray;
                    }
                stats->hist.ptrhist.ptr_array[bin][bin2] += 1; 
                }
            /* Keep track of true imgmin and imgmax */
#if DRAGON_VER >= 6
            stats->m_ihImgmin = min((stats->m_ihImgmin),val);
	    stats->m_ihImgmax = max((stats->m_ihImgmax),val);
#else
            stats->imgmin = min((stats->imgmin),val);
	    stats->imgmax = max((stats->imgmax),val);
#endif
            }   /* end if we should count this pixel */
        }   /* end loop through pixels */
    stats->hist.imghist[0] += linetot;
    }

/* SEG 1/30/05 FinishLineCalc is used in imstat-o (for dragon)
 * It should be kept, and probably here is a good place for it.
 */

/**/
void FinishLineCalc(IMGSTATS* stats)
	/* Called after all lines of data to be considered have been
	 * passed to NextLineCalc. Uses accumulated histogram to compute
	 * mean, variance, max, min, etc.
	 * 'stats' is a ptr to structure for storing/returning the results
	 */
    {
    int i,j;
    double fj;
    double tmp, tmp2, tmp3; /* intermediate values for calculations */
    double denom;
    unsigned long totpix = stats->hist.imghist[0]; 	/* # pix to process */
    BOOL bMultibyte = (stats->bits_per_pix > 8);
 
    /* now we need to calculate true sum and sum of squares
     * in order to calculate the mean, variance and SD. 
     * Do it differently for 8 bit and multibyte data 
     */  
     if (bMultibyte)
         {
         for (i = 0; i < IMG_HIST_LEN-1; i++)
             {
	     unsigned long baseval;
             if (stats->hist.ptrhist.ptr_array[i] == NULL)
                 continue;  /* skip next part if no subarray */
             baseval = ((unsigned long) i) << 8;
             for (j = 0; j < IMG_HIST_LEN-1; j++)
                 {
		 unsigned long ltmp;
                 if (stats->hist.ptrhist.ptr_array[i][j] == 0)
                       continue;  /* skip cells with zero frequency */
                 ltmp = baseval + (unsigned long) j;
                 fj = (double)ltmp;  /* data value represented */
                 tmp = (double)stats->hist.ptrhist.ptr_array[i][j];
                                       /* frequency */
                 tmp2 = fj * tmp;
                 stats->sum = stats->sum + tmp2;
                 /* multiply frequency x data value, add to sum */

                 tmp2 = fj * fj; /* square the data value */
                 tmp3 = tmp * tmp2; /* multiply by frequency */
                 stats->sumsq = stats->sumsq + tmp3; 
                     /* and add to the sum of squares */
                 }   /* end loop through sub-histogram */
             }       /* end loop through array of histogram ptrs */
         }           /* end if multibyte */
     else
         {
         for (i = 1; i < IMG_HIST_LEN; i++)
             {
	     unsigned long ltmp;
             if (stats->hist.imghist[i] == 0L)
                 continue;  /* skip cells with zero frequency */
     
             ltmp = stats->hist.imghist[i] * (unsigned long) i;
             /* multiply frequency times data value */
             fj = (double)ltmp;
             stats->sum = stats->sum + fj;
             /* cast to a long and add it to the sum */
             tmp = (double)i;
             tmp2 = tmp * tmp;
             /* square the bin value */
             fj = (double)stats->hist.imghist[i];
             tmp3 = tmp2 * fj;
             /* multiply it by the bin frequency */
             stats->sumsq = stats->sumsq + tmp3; 
             /* and add that to the sum of squares */
             }  /* end loop through histogram */
         }      /* end if not multibyte */

    tmp = (double)totpix;
    tmp2 = stats->sum / tmp;
#if DRAGON_VER >= 6
    stats->m_ihImgmean = (int)tmp2;
    if (!bMultibyte)
        {
        stats->m_ihImgmean = min((stats->m_ihImgmean),(stats->m_ihImgmax));
	}
#else
    stats->imgmean = (unsigned short)tmp2;
    if (!bMultibyte)
        {
        stats->imgmean = min((stats->imgmean),(stats->imgmax));
	}
#endif
    denom = (double)(totpix-1);
    tmp = stats->sumsq / denom;
    tmp3 = stats->sum / (double) totpix;
    tmp2 = stats->sum * tmp3;
    tmp2 = tmp2 / denom;
#if DRAGON_VER >= 6
    stats->m_dhImgvar = tmp - tmp2;

	/* variance = (N*sumsq - sum squared)  divided by N(N-1)    */
	/*  = sumsq/N-1   -  mean * (sum/N-1)  b/c mean = sum/N   */

    stats->m_dhImgsd = sqrt(stats->m_dhImgvar);
#else
    stats->imgvar = tmp - tmp2;
    stats->imgsd = sqrt(stats->imgvar);
#endif
    }

void HDRSTATS_END() { puts(FIL_ID); }

/* SEG 1/30/05 This test code needs to be updated to 
 * use new header structures and fields.
 */

#ifdef TEST

static int testnumlines;
static int testnumpix;
static byte readbuf[D_MAXIMGPIX];
static int testfp;
static IHEAD test_inhdr;

void init_read(char* fname)
     /* initialize image file for reading.
      * open file, set static file pointer variable,
      * read header, 
      * set lines and pixels in static variable, 
      */
    {
    int stat;

    testfp = open(fname,O_RDONLY | O_BINARY);

    if (testfp < 0)
       {
       fprintf(stderr,"Error opening input image\n");
       exit(1);
       }
    stat = read(testfp,test_inhdr.buffer,DHEAD);
    if (stat != DHEAD)    
       {
       fprintf(stderr,"Error reading input image header\n");
       exit(1);
       }
    testnumlines = test_inhdr.fields.size[0];
    testnumpix = test_inhdr.fields.size[1];
    fprintf(stdout,"Input image is %d lines by %d pixels per line\n",
         testnumlines,testnumpix);
    fprintf(stdout,"DHEAD is %d\n",DHEAD);
    }


void * read_img_line(int line)
    {
    long pos;
    long stat;
    
    pos = (long)line * (long)testnumpix + DHEAD;

    stat = lseek(testfp,pos,SEEK_SET);
    if (stat < 0)
       {
       fprintf(stderr,"Error seeking to line in input image - pos=%ld\n",
           pos);
       exit(1);
       }
    stat = read(testfp,readbuf,testnumpix);      
    if (stat != testnumpix)
       {
       fprintf(stderr,"Error reading line %d in input image\n",line);
       exit(1);
       }
    if (line % 10 == 0)
       fprintf(stdout,"Finished with %d lines...\n",line);
    return (void*) readbuf;
    }

void main(int argc,char ** argv)
    {
    char infile[FMSIZE]; /* just for unit test program */
    char outfile[FMSIZE]; /* just for unit test program */
    char resp[10];
    char* brk;
    IMGSTATS * mystats;
    int status;
    int i;

    fprintf(stdout,"Input image file? ");
    fgets(infile,sizeof(infile),stdin);
    brk = strpbrk(infile,"\n");
    if (brk)
        *brk = '\0';   

    fprintf(stdout,"Output image file? ");
    fgets(outfile,sizeof(outfile),stdin);
    brk = strpbrk(outfile,"\n");
    if (brk)
        *brk = '\0';   

    init_read(infile);
    mystats = ImgStatsAlloc();
    if (mystats == NULL)
       {
       fprintf(stderr,"Error allocating IMGSTATS structure\n");
       exit(1);
       }
    
    status = CalcImgStats(8,1,testnumlines,testnumpix,mystats,read_img_line);
    if (status < 0)
       {
       fprintf(stderr,"Error %d returned from CalcImgStats\n",status);
       exit(1);
       }
    close(testfp);
    fprintf(stdout,"\nImage Mean: %d\n", mystats->imgmean);    
    fprintf(stdout,"Image Min: %d\n", mystats->imgmin);    
    fprintf(stdout,"Image Max: %d\n", mystats->imgmax);    
    fprintf(stdout,"Image Variance: %f\n", mystats->imgvar);    
    fprintf(stdout,"Image SD: %f\n", mystats->imgsd);    
    fprintf(stdout,"Total number of pixels: %ld\n",mystats->hist.imghist[0]);
    fprintf(stdout,"Histogram:  ");
    for (i = 1; i < IMG_HIST_LEN; i++)
        {
        if ((i-1) % 16 == 0)
            fprintf(stdout,"\n");
        fprintf(stdout,"%ld ",mystats->hist.imghist[i]);
        }
    fprintf(stdout,"Press a key to continue: ");
    fgets(resp,10,stdin);

#ifdef NOMORE
    status = SaveHdrStats(outfile,mystats,&test_inhdr);
    if (status < 0)
       {
       fprintf(stderr,"Error %d returned from SaveHdrStats\n",status);
       exit(1);
       }
#endif
    ImgStatsFree(mystats);
    }
#endif
