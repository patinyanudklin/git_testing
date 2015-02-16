#include "drelease.h"
char ROSEFUNS_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.13 $$Date: 2014/02/09 04:41:58 $";
D_REL_IDSTR;
/****************************************************************
 *	ROSEFUNS.C -  General routines used by Tools Library programs
 *
 *	  $Revision: 1.13 $	$Date: 2014/02/09 04:41:58 $
 *
 *	~~ Copyright 1994-2011 Kurt Rudahl and Sally Goldin
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *	~~ EndC
 *****************************************************************
 *	$Id: rosefuns.c,v 1.13 2014/02/09 04:41:58 rudahl Exp $
 *	$Log: rosefuns.c,v $
 *	Revision 1.13  2014/02/09 04:41:58  rudahl
 *	made CalcStats take a const IMAGE *; much more useful
 *
 *	Revision 1.12  2013/08/01 10:03:13  rudahl
 *	better use of string fns
 *
 *	Revision 1.11  2011/12/30 11:54:37  rudahl
 *	lint
 *
 *	Revision 1.10  2006/08/14 06:29:14  rudahl
 *	extracted from rosefuns to keyed_files
 *
 *	Revision 1.9  2005/07/29 05:43:52  rudahl
 *	removed dtk usage
 *	
 *	Revision 1.8  2005/07/29 04:01:56  rudahl
 *	removed use of dtk lib
 *	
 *	Revision 1.7  2005/07/22 15:01:34  rudahl
 *	adapting to using Dragon Image classes
 *	
 *	Revision 1.6  2005/07/04 05:58:52  goldin
 *	Fix stats calculation
 *	
 *	Revision 1.5  2005/07/03 13:12:57  rudahl
 *	moved CalcStats from fconvert to rosefuns
 *	
 *	Revision 1.4  2005/06/27 11:35:47  rudahl
 *	adapted fconvert for linux, v 5.8 imageWriter
 *	
 *	Revision 1.3  2004/12/23 12:15:21  rudahl
 *	lint-ish fix
 *	
 *	Revision 1.2  2002/06/10 12:33:53  rudahl
 *	updated TIFF-related fns to MSC4.1
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *	
 *
 *****************************************************************
 *   This module holds several subroutines of general utility
 *   expected to be useful throughout ROSETTA.
 ******************************************************************
 *
 *	Revision history
 *
 * 1.0	12-28-94  seg	Created
 *	1/4/95 ktr	split into two compile modules
 *	1/13/95 seg	added trimstring, also code that would
 *                      allow keywords initializers to be in lower
 *                      case and have trailing blanks - for use
 *                      in outputting the Idrisi doc file for V4.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 * 5.4	12/22/2004 ktr	added stricmp for linux
 * 5.7	2005-6-27 ktr	import for fconvert
 *	2005-7-1 ktr	moved CalcStats here from fconvert
 * 5.9	2006-8-12 ktr	moved keyedfile stuff to separate file
 */

#if defined __GCC__
#else
//#include <io.h>
//#include <dos.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdtk.h"
#include "img_acc.h"
//#include "dtypes.h"
//#include "dlimits.h"
//#include "dragon-errors.h"
//#include "dhead.h"
//#include "hdrstats.h"
#include "toolerr.h"
//#include "toolkit.h"
//#include "files.h"
#include "rosefuns.h"

#ifndef ROSEFUN_READ
#define ROSEFUN_WRITE	// the default - only a few need to read it
#endif

#ifdef __USE_DTK
#include "dtk6.h"
void dtk_errs_to_stderr()
	//	send error messages to stderr not stdout, clear err msg stack
	//	should be arg. to atexit() AFTER dtk_init()
    {
    int emc=dtk_ErrorMsgCount();
    while (emc)
	{
	fputs(dtk_ErrorMsg(--emc),stderr);
	fputs("\n",stderr);
	}
    dtk_ErrorMsgClear();
    }
#endif // ifdef __USE_DTK

/* Calculate the statistics for a Dragon image which has already been written.
 * Then write the statistics to the file.
 * Error messages are sent to stderr.
 * @param  pDestImage	the image which needs to be calculated
 * @param  linesize	the number of BYTES (not elements) per data line
 * @param  iDataType	'S' if 16-bit data else 'C' or 'B' or ...
 * @return		0 if successful else standard Dragon error numbers
 */
int CalcStats(const IMAGE * pDestImg, const size_t  linesize, int iDataType)
    {
    int lin;
    int iRetval = DERR_MEM_ALLOC;
    int bitspp;
    int bytespp;
    IMGSTATS * pStats;   	/* for accumulating image statistics */
    byte * pBuf = calloc(1,linesize+1);
    pStats = ImgStatsAlloc();
    if ((pStats != NULL) && (pBuf != NULL))
        {
	if (iDataType == 'S')
            {
	    bitspp = 16;
	    bytespp = 2;
	    }
	else
            {
	    bitspp = 8;
	    bytespp = 1;
	    }  
//	printf("rosefuns::CalcStats (en) bitspp=%d\n",bitspp);
	InitLineCalc(pDestImg->lines,pDestImg->pixels,bitspp,bytespp,pStats);

        /* now we loop through the pixels in the file, calculating histogram */
        /* and other statistics */
	for (lin = 0; lin < pDestImg->lines; lin++)
	    {
	    iRetval = GetImageLineP(pBuf,lin,linesize,pDestImg,FALSE,NULL);
//	    if ((lin % 50) == 0)
//		printf("rosefuns::CalcStats line %d got %d\n",lin,iRetval);
	    if (iRetval < 0)
	        {
		fprintf(stderr,"Calculating image stats read error %s (%d) on line %d\n",
			dragonErrorMessage(iRetval),iRetval,lin);
		break;
		}
	    NextLineCalc(pBuf,NULL,0,pStats);
	    } /* end of line by line calcs */
	FinishLineCalc(pStats);
	free(pBuf);
	}
    if ((iRetval >= 0) && (pStats != NULL))
        {
        iRetval =  updateImageStats(pDestImg,pStats);
	ImgStatsFree(pStats);
	}
    if (iRetval >= 0)
	iRetval = rewriteImageHeader(pDestImg,0,TRUE);
//    printf("rosefuns::CalcStats (ex) returns %d\n",iRetval);
    if (iRetval == DERR_NOT_NEEDED)
	iRetval = 0;
    return iRetval;
    }

void ROSEFUNSEND() { puts(FIL_ID); }
