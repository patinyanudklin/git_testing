/**********************************************************
 *  This file simply contains prototypes for functions
 *  in HDRSTATS.C. Must be preceeded by DHEAD.H.
 *
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
 *   $Id: hdrstats.h,v 1.6 2014/12/05 09:58:46 rudahl Exp $
 *   $Log: hdrstats.h,v $
 *   Revision 1.6  2014/12/05 09:58:46  rudahl
 *   no differences between DragonProf and OpenDragon
 *
 *   Revision 1.5  2006/09/17 05:01:03  rudahl
 *   got rid of 'far' keyword
 *
 *   Revision 1.4  2005/02/23 17:46:44  rudahl
 *   new update, wrapper fns; moved from hdrstats to dhead
 *
 *   Revision 1.3  2005/01/30 04:03:53  rudahl
 *   initial conversion for v 5.5
 *
 *   Revision 1.2  2001/09/14 18:24:29  goldin
 *   moved several protos from dragon.h to hdrstats.h for consistency
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/02/27  05:25:10  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.2  1995/12/11  08:20:08  lcd
 * checkin for class class49
 * 
 * Revision 4.1  1994/07/19  18:54:32  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/06/04  11:56:20  tower
 * final for DRAGON 4.0G.
 * general changes: MSC v 6 adaptations, graphics screens to 1280 pix.
 * 
 * Revision 4.0  1993/06/04  11:56:20  tower
 * Final for DRAGON Release 4.0
 * 
 * Revision 1.4  93/02/13  15:54:19  tower
 * minor fixes in prototypes
 * 
 * Revision 1.3  92/11/23  12:57:13  tower
 * very minor fixes
 * 
 *
 ************************************************************************
 *
 *      S.E.Goldin     3/22/92
 *
 * 5/16/92  SEG  Added some typedefs, revamped for use with
 *		 DRAGON toolkit
 * 5/30/92  SEG  Added line-by-line calculation functions
 *   3/13/93 	ktr	changed InitNewHdr, SaveHdrStats, SetHdrVals
 *			 to use pointer to IHEAD
 *   7/16/94 	seg	modifications to support calculating stats for
 *                       multi-byte data. New structure 
 *                       IMGSTATS to replace HDRSTATS. New
 *                       parameters in the functions, to
 *                       generate compile errors if the caller hasn't
 *                       updated his/her code.
 *			(also macro for halloc() etc)
 * 	12/11/95 ktr	update for Watcom 10.0
 * 5.0	2/27/97 ktr	moved decl. for SetHdrToCurrent() here
 * 5.5	2005-1-23 ktr	convert for v 5.5 Delete 16 bit stuff. New dhead.h.
 **********************************************************
 *
 * requires : dhead.h
 */
#ifndef HDRSTATS_H
#define HDRSTATS_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _LINEACCESS_DEFINED
#define _LINEACCESS_DEFINED
typedef void* (*LineAccess)(int); 	/* this is also in toolkit.h */
#endif

/* prototypes for functions in hdrstats.c */
void InitNewHdr(IHEAD * hdr,       /* ptr to header to be initialized */
		const int nl,	       /* number of lines in img */
		const int np);	       /* number of pixels in the img  */

void SetHdrVals(IHEAD * hdr,    /* header struct to modify */
		const char* ftype,     /* if non-null, filetype to set  */
		const char* filename,  /* if non-null, filename to set  */
		const char* bandn,     /* if non-null, band num to set  */
		const char* comment,   /* if non-null, comment to set  */
		const char* source,    /* if non-null, source string to set  */
		const int norm);       /* normalization flag */
		   /* This function initializes selected fields in the
		    * passed header structure, with passed values.
		    * We assume that InitNewHdr was called first to
		    * make sure all fields were initialized to zero.
		    */

IMGSTATS * ImgStatsAlloc();
        /*  Allocates a new image statistics structure in 
         *  near memory and returns a pointer to it.
         *  Will return a NULL ptr if insufficient memory.
         */
void ImgStatsFree(IMGSTATS* stats);
        /*  Frees an image statistics structure.
         *  Uses the contents to see if it is also necessary to
         *  free any pointers to memory allocated during the
         *  calculation of stats. 
         */

int CalcImgStats(const int bitspp,  /* bits per pix  */
                 const int bytespp, /* bytes per pix  */
		 const int nl,     /* number of lines to consider   */
		 const int np,     /* number of pixels to consider per line  */
		 IMGSTATS* stats, /* ptr to structure for storing results */
		 LineAccess linefn);  /* function to return lines of data */

int SaveHdrStats(const char* outname,const IMGSTATS* stats,IHEAD * inhdr);
		/* Calculate statistics for newly created DRAGON
		 * image and store in the header.
		 * If 'hdr' is NULL and 'outname' is not, uses
		 * a local hdr initialized by reading 'outname'.
		 * Assumes that the header passed in already has the
		 * number of lines and pixels per line fields set.
		 */
/* alternate header calculating functions - where the caller initializes */
/* the process, then supplies the data line by line, then finally completes */
/* the calculations and gets the resulting statistics. */

void InitLineCalc(const int nl,  /* number of lines to be processed */
		  const int np,  /* number of pixels per line       */
		  const int bitspp, /* bits per pixel */
		  const int bytespp, /* bytes per pixel */
		  IMGSTATS * stats);  /* structure for holding the info */
     	/*  Initialize static variables used calculating line by line
	 *  statistics.
	 */

void NextLineCalc(const void * databuf,const byte * maskbuf, 
                  const int maskpix,
                  IMGSTATS * stats);
       /*  Accumulate data for statistics calculation, based on
	*  information in the passed buffer 'databuf'. Assumes
	*  that the user wants to process 'numpix' elements (initialized
	*  based on 'np' passed to the InitLineCalc function. If
        *  maskbuf is non-null, only accumulate data for pixels
        *  where maskbuf[px] is non-zero. Maskpix is the amount of
        *  data in maskbuf.
	*/

void FinishLineCalc(IMGSTATS* stats);
       /* Called after all lines of data to be considered have been
	* passed to NextLineCalc. Uses accumulated histogram to compute
	* mean, variance, max, min, etc.
	* 'stats' is a ptr to structure for storing/returning the results
	*/

void SetHdrToCurrent(IHEAD * hdr);
void SetHdrTo401(IHEAD * hdr);
	/*	fixup older hdrs to 4.1. This assumes the fields
	 *	being set did not contain useful info.
	 */

#ifdef __cplusplus
    }	/* end of extern "C" */
#endif
#endif
