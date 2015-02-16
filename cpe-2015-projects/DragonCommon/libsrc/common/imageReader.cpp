#include "drelease.h"
char IMAGEREADER_ID[]=
"\0@(#) " __FILE__ "  $Revision: 1.6 $$Date: 2015/01/21 10:37:33 $ " VERR;
D_REL_IDSTR;

/*
 *	filename imageReader.cpp
 *		$Revision: 1.6 $ $Date: 2015/01/21 10:37:33 $	
 *
 *      ~~ Copyright 2005-2015 Kurt Rudahl and Sally Goldin
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
 ****************************************************************
 *   $Id: imageReader.cpp,v 1.6 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: imageReader.cpp,v $
 *   Revision 1.6  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.5  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.4  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.3  2014/12/05 07:05:28  rudahl
 *   tracing
 *
 *   Revision 1.2  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.1  2014/03/08 12:27:13  rudahl
 *   moved class methods from dhead to their own files, and adjusted Makefiles
 *
 *
 ****************************************************************
 * 
 * Define a base class for reading from real image files.
 * 
 * Various query functions are also provided.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 6.4	2014-03-08 ktr	extracted from dhead.h
 */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <errno.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcat_array */
#include "files.h"
#include "dragon-errors.h"
#include "dragonHd.h"
#include "ob.h"
#include "logger.h"
#include "dhead.h"
#include "dragonOb.h"
//#include "dhead-old.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"

Class ImageReader::s_class_Base("ImageReader");
char ImageReader::s_czDumpBuf[READER_DUMPBUF_SIZE];
int ImageReader::s_iNumBands = DERR_FN_NOTIMPL;     // used by externImageReader and importers; set by test()

ImageReader::ImageReader(int iDebug, int iTrace) : OB()
    {
    m_pClass = &s_class_Base; 
    m_pClass->setSubClass(OB::getObjectClass());
    m_pHdr = NULL;
    m_pFp = NULL;
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    m_puLinesBlob = NULL;
    m_uLinesBlobLen = 0;
    memset(&m_DesiredData,0,sizeof(m_DesiredData));
    }

		// read the file 
		// @param pczFilename	name of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		some readers may need this
		// @return		TRUE if OK
BOOL ImageReader::readHeader(const char * pczFilename,
			     IMAGEHDR * pHdr,
			     int * pErrNum, Image * pImg)
    {
    if (m_iDebug)
	fprintf(stderr,"ImageReader::readHeader (en) %s\n",pczFilename);
    if (m_iTrace)
	logTrace("ImageReader::readHeader (en) %s",pczFilename);
    m_pHdr = pHdr;
    FILE * pf = fopen(pczFilename,"rb");
    pHdr->h_uOriginalBandCount = 0;  // make sure initialized to something
    BOOL bRetval = readHeader(pf,pHdr,pErrNum,pImg); // exec fn in subclass
    if ((pf != NULL) && fclose(pf) && (*pErrNum == 0))
	*pErrNum = DERR_FILE_CLOSE;
    if (m_iTrace)
	logTrace("ImageReader::readHeader (ex) errnum=%d returning %s",
		 *pErrNum,YESNO(bRetval));
    return (*pErrNum == 0) ? bRetval : FALSE;
    }

	/*	Calc byte offset into file of specified image line,
	 *	The base class calcs are OK for file formats where
	 *	line offsets follow sequentially from ulDataOffset
	 *	or can be overridden in subclasses.
	 *
	 * 	@param uLineNo	line number to seek`<
	 *	@param pImage	ptr to IMAGE (must be non-NULL)
	 *			  pImage is ref'd but not altered	
	 *	@param pDataSel permits passing e.g. band number
	 *			not used for Dragon, but is used for e.g. BIL
	 * 	@return		offset
	 */
long ImageReader::CalcImageFileOffset(uint uLineNo, const IMAGE * pImage,
			 		       IMAGEDATA_SELECTOR * pDataSel)

    {
    const IMAGEHDR * pHdr = (m_pHdr != NULL) ? m_pHdr : pImage->pImageObj->getImageHeader()->getImageHdr();
    long lImageLineOffset = pHdr->ulDataOffset
			 + pHdr->ulLinePitch * (ulong)uLineNo;
    if (m_iDebug)
        fprintf(stderr,"ImageReader::CalcImageFileOffset line %d returns %ld (m_pHdr=%p pHdr=%p)\n",
		uLineNo,lImageLineOffset,m_pHdr,pHdr);
    return lImageLineOffset;
    }

	/*	Retrieve a line of raw data from the appropriate
	 *	location into buffer. 
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *			   -51  open error
	 *			   -53  read error
	 *			   -56  past EOF ?
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 *			     or errors from fread, fseek
	 */
int ImageReader::getImageLineRaw(byte * pBuf, ushort uLineNo,
				 size_t uBufSize, const Image * pImage,
				 IMAGEDATA_SELECTOR * pDataSel)
    {
    return getImageLine(pBuf,uLineNo,uBufSize,pImage,pDataSel);
    }

	/*	Retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The base class calcs are OK for file formats where
	 *	lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *	NOTE this fn (and any overloaded fns) does not and should not
	 *	     enforce ProcessRect
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param pDataSel	NULL or selects data to read
	 *			(at present, ignored for Dragon format files)
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			   -51  open error
	 *			   -53  read error
	 *			   -56  past EOF ?
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 *			     or errors from fread, fseek
	 */
int ImageReader::getImageLine(byte * pBuf, ushort uLineNo,
			      size_t uBufSize, const Image * pImage,
			      IMAGEDATA_SELECTOR * pDataSel)
    {
    const IMAGE * pImg = &pImage->image;
    ushort uBytesPP = (pImg->ulPixPitch > 0) ? (ushort) pImg->ulPixPitch : 1 ;
    int iRetval = DERR_FILE_OOB;
    uint uPixReadCount = min((pImg->ProcessRect.Xmax + 1),pImg->pixels);
    if (m_iDebug != 0)
	fprintf(stderr,"ImageReader::getImageLine (en) bytespp=%d count=%d\n",uBytesPP,uPixReadCount);
    if (uLineNo >= pImg->lines)
	{
	iRetval = DERR_FN_ARG1;
	if (m_iTrace)
	    Logger::logTrace("ImageReader::getImageLine: "
			     "Image index %d requested line %d of %d",
			     pImg->thisone,uLineNo,pImg->lines);
	if (m_iDebug != 0)
	    fprintf(stderr,"ImageReader::getImageLine: "
		    "Image index %d requested line %d of %d\n",
		    pImg->thisone,uLineNo,pImg->lines);
	}
//    else if ((ushort)(uPixReadCount * uBytesPP) <= (ushort)uBufSize)
    else if (uPixReadCount * (uint)uBytesPP <= uBufSize)
        {
	// mode needs to be "rb" (not +) if file might be on a read-only medium
        const char * pczMode = ((pImage->getState() == IMG_INITFROMFILE) 
				&& !pImage->getModifiable()) 
				    ? "rb" : "rb+";
	if (m_iDebug != 0)
	    fprintf(stderr,"ImageReader::getImageLine m_pFp=%p filename=|%s|\n",
		    m_pFp,NN(pImg->filename));
	if ((m_pFp == NULL) 
	     && ((m_pFp = (FILE *)fopen(pImg->filename,pczMode)) == NULL))
            {
	    perror("ImageReader::getImageLine open error");
	    fprintf(stderr,"filename='%s'\n",pImg->filename);
	    iRetval = m_iErrno = DERR_FILE_OPEN;
	    }
	else 
	    {
	    FILE * pFp = (FILE *) m_pFp;
	    if (m_iDebug != 0)
		fprintf(stderr,"ImageReader::getImageLine pFp=%p datasel=%p\n",pFp,pDataSel);
	    long lFilePosition = CalcImageFileOffset(uLineNo,pImg,pDataSel);

            if (m_iDebug)
		fprintf(stderr,"Size of file is %ld position=%ld\n", fsize(pFp),lFilePosition);

            iRetval = fseek(pFp,lFilePosition,SEEK_SET);
	    /*
	    if (m_iDebug)
	        {
		long filePos = ftell(pImg->pFp);
		fprintf(stderr,"Ftell returns %ld; should be %ld\n", filePos,lFilePosition);
		}
	    */
	    if (iRetval == 0)
	        iRetval = fread(pBuf, uBytesPP, uPixReadCount, pFp);
            /* 
	    if (m_iDebug)
	        {
		int errnum = errno;
		perror("result of read");
		fprintf(stderr,"fread returned %d errno=%d\n", iRetval,errnum);
		}
	    */
	    if (iRetval < (int)uPixReadCount)
		{
		int sysernum = errno;
		Logger::logTrace("ImageReader::getImageLine error %s (%d) only %d of %d pixels offset %lu errno=%d",
		    	        dragonErrorMessage(DERR_FILE_RW),DERR_FILE_RW,
				iRetval,uPixReadCount,lFilePosition,sysernum);
		if (m_iDebug != 0)
		    fprintf(stderr,"ImageReader::getImageLine error %s (%d) only %d of %d pixels offset %lu errno=%d\n",
		    	        dragonErrorMessage(DERR_FILE_RW),DERR_FILE_RW,
				iRetval,uPixReadCount,lFilePosition,sysernum);
		iRetval = DERR_FILE_RW; /* else it's the count */
		}
	    }
	}
    else
	iRetval = DERR_IMAGE_TOOBIG;
    if (iRetval < 0)
	{
	if (m_iDebug != 0)
	    fprintf(stderr,"ImageReader::getImageLine "
		   "error %s (%d) reading real line %d of %d of %s "
		   "pixcnt=%d bufsiz=%d bytespp=%d\n",
		   dragonErrorMessage(iRetval),iRetval,uLineNo,pImg->lines,pImg->filename,
		   uPixReadCount,uBufSize,uBytesPP);
	Logger::logTrace("ImageReader::getImageLine "
			 "error %s (%d) reading real line %d of %d "
			 "pixcnt=%d bufsiz=%d bytesPP=%d",
			 dragonErrorMessage(iRetval),iRetval,
			 uLineNo,pImg->lines,uPixReadCount,uBufSize,uBytesPP);
	}
    return iRetval;
    }

	/* if m_pFp is open it must be a file; close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
int ImageReader::close()
    {
    int iRetval = 0;
    if (m_iDebug)
	fprintf(stderr,"ImageReader::close (en) m_pFp = %p\n",m_pFp);
    if (m_iTrace)
	logTrace("ImageReader::close (en) m_pFp = %p",m_pFp);
    if (m_pFp != NULL)
        {
	FILE * pFp = (FILE *)m_pFp;
	iRetval = fclose(pFp);
	m_pFp = NULL;
	}
    if (m_iTrace)
	logTrace("ImageReader::close (ex) returns %s",iRetval);
    return iRetval;
    }

	// return a formatted dump of the class member
const char * ImageReader::dump(int detail, const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "ImageReader dump imagehdr=%p fp=%p",
	     m_pHdr,m_pFp);
    return s_czDumpBuf;
    }

void ImageReader::SetDesiredData(const IMAGEDATA_SELECTOR * pSel)
    {
    if (pSel != NULL)
	memcpy(&m_DesiredData,pSel,sizeof(IMAGEDATA_SELECTOR));
    }

	/* this has something to do with vector data
	 * ~~~
	 */
#if DRAGON_VER >= 6
int ImageReader::saveLinesBlob(const byte * pBlob,size_t uBlobSize)
    {
    int iRetval = DERR_MEM_ALLOC;
    m_uLinesBlobLen = uBlobSize;
    m_puLinesBlob = (byte *)calloc(uBlobSize,1);
    if (m_puLinesBlob != NULL)
        {
	memcpy(m_puLinesBlob,pBlob,uBlobSize);
	iRetval = 0;
	}
    return iRetval;
    }
#endif

void IMAGEREADER_END() { puts(FIL_ID); }
