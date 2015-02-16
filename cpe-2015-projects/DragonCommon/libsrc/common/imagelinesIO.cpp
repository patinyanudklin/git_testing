#include "drelease.h"
char IMG_IO_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.1 $$Date: 2014/04/02 03:23:35 $";
D_REL_IDSTR;
/*-------------------------------------------------------------
 *	   imagelinesIO.cpp
 *
 *	~~ Copyright 2014 Kurt Rudahl and Sally goldin
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
 ***************************************************
 *  $Id: imagelinesIO.cpp,v 1.1 2014/04/02 03:23:35 rudahl Exp $
 *  $Log: imagelinesIO.cpp,v $
 *  Revision 1.1  2014/04/02 03:23:35  rudahl
 *  prepare to separate dtk,rosetta to new mingw version adaptations for Linux build
 *
 */
/****************************************************************
 * extracted from img_acc only for use with utils and rose.a
 * (Dragon Server uses fns in imageMem
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
//#include <ctype.h>

//#if defined __GCC__ || defined __MINGCC__
//#include <sys/stat.h>
//#include <unistd.h>
//#else
//#include <sys\stat.h>
//#endif
//#include <stddef.h>	/* for offsetof() */

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"

#include "ob.h"
#include "dhead.h"
#include "imageHdr.h"
//#include "files.h"
#include "img.h"
//#include "hdrstats.h"
#include "img_acc.h" /* declarations for this module */

//#include "dragonOb.h"
//#include "logger.h"
//#include "IpcWrap.h"
#include "dp.h"

	/*	retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The IMAGE structure must be initialized with:
	 *	  -- scaling values if not 8-bit data
	 *	  -- uPreferredScaling "      "      "
	 *	  -- key data if it's a locked file
	 *	  -- ulFileOffset & pFp if using fread()
	 *	  -- ulPixPitch, ulLinesPitch, pixels, ProcessRect
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *			  for using vfread (i.e. large model) this
	 *			    must be at least as large as the number of
	 *			    bytes in one image line.
	 *			  using fread (small model, at present)
	 *			    it can be only large enough to hold
	 *			    the beginning portion of the image line.
	 *			  for 16-bit data, this must be twice pix count
	 *			    (pix[0] through pix[ProcesRect.Xmax])
	 *	@param pImg	pointer to IMAGE struct
	 *	@param bScale   Scale to 8 bits (GetImageLineP only)
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
         *                           -66 => image is in an illegal state
	 *			     -60 => image not yet initialized
	 *			     -63 => bufsize too small for ProcessRect
	 *			     -68 => image not readable
	 *			     -51 => file open error
	 *			     -56 => past EOF
	 *			     -92 => element too big for buffer)
	 */
int GetImageLineP(byte * pBuf, const ushort uLineNo,
		  const size_t uBufSize,const IMAGE * pImg,
		  const BOOL bScale,
		  IMAGEDATA_SELECTOR * pDataSel)
    {
    int iRetval = DERR_IMAGE_TOOBIG;
    ushort uBytesPP = (pImg->ulPixPitch > 0) ? (ushort) pImg->ulPixPitch : 1 ;
    ushort uPixReadCount = min((pImg->ProcessRect.Xmax + 1),pImg->pixels);
    if (uPixReadCount * uBytesPP <= (ushort)uBufSize)
	iRetval = pImg->pImageObj->getImageLine(pBuf,uLineNo,
						uBufSize,pDataSel);
    if (bScale && (iRetval > 0) && (uBytesPP > 1))
	{
	if ((pImg->uPreferredScaling == 2) && (pImg->uDataFactor > 0))
	    ScaleImageLine(pBuf,pBuf,uPixReadCount,uBytesPP,
			   pImg->uDataOffset,pImg->uDataFactor);
	else if (pImg->uPreferredScaling >= 1) /* in case uDataFact == 0 */
	    ScaleImageLine(pBuf,pBuf,uPixReadCount,uBytesPP,
			   0,pImg->uScaleFactor);
	}
    return iRetval;
    }

	/*	stores line of pixels in the appropriate
	 *	location in image memory, based on a line number and
	 *	source location to copy from. This version is
	 *      independent of the Dragon array of images - pass
	 *      an actual IMAGE* instead of an index.
	 *
	 *	@param lpBuf 	pointer to the source data buffer
	 *	@param uLineNo	which image memory line to write
	 *	@param pImg	img to use.
	 *	@return number of bytes if successful, < 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *				-51 => file open error
	 *				-60 => image not yet initialized
	 *				-68 => image not writable
	 */
int PutImageLineP(const byte * lpBuf, const ushort uLineNo,
			const IMAGE * pImg)
    {
    int iRetval = 0;
    ushort uByteWriteCount = min((pImg->ProcessRect.Xmax + 1),pImg->pixels);
    if (pImg->ulPixPitch > 0)
	uByteWriteCount *= pImg->ulPixPitch;
    iRetval = pImg->pImageObj->putImageLine(lpBuf,uLineNo,uByteWriteCount);
    return iRetval;
    }


void IMG_IO_END() { puts(FIL_ID); }
