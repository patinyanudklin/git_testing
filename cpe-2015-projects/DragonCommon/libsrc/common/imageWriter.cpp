#include "drelease.h"
char IMAGEWRITER_ID[]=
"\0@(#) " __FILE__ "  $Revision: 1.3 $$Date: 2014/12/29 03:28:29 $ " VERR;
D_REL_IDSTR;

/*
 *	filename imageWriter.cpp
 *		$Revision: 1.3 $ $Date: 2014/12/29 03:28:29 $	
 *
 *      ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: imageWriter.cpp,v 1.3 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: imageWriter.cpp,v $
 *   Revision 1.3  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.2  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.1  2014/03/08 12:27:13  rudahl
 *   moved class methods from dhead to their own files, and adjusted Makefiles
 *
 *
 ****************************************************************
 * 
 * Define a base class for writing to real image files.
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
 * 5.14,6.4	2014-03-08 ktr	extracted from dhead.h
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
#include "imageWriter.h"

Class ImageWriter::s_class_Base("ImageWriter");
char ImageWriter::s_czDumpBuf[WRITER_DUMPBUF_SIZE];

ImageWriter::ImageWriter(int iDebug, int iTrace)
    {
    m_pClass = &s_class_Base; 
    m_pClass->setSubClass(OB::getObjectClass());
    m_pHdr = NULL;
    m_pFp = NULL;
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    m_puLinesBlob = NULL;	/* if non-NULL, ptr to blob of vector data */
    m_uLinesBlobLen = 0;	/* number of BYTES in LinesBlob */
    }

#if DRAGON_VER >= 6
// this is important? ~~~
ImageWriter::~ImageWriter()
    {
    if (m_puLinesBlob != NULL)
        free(m_puLinesBlob);
    }
#endif
	/*	Calc byte offset into file of specified image line,
	 *	The base class calcs are OK for files where
	 *	line offsets follow sequentially from ulDataOffset
	 *	or can be overridden in subclasses.
	 *
	 * 	@param uLineNo	line number to seek
	 *	@param pImage	ptr to IMAGE (must be non-NULL)
	 *			  pImage is ref'd but not altered	
	 *	@param pDataSel permits passing e.g. band number
	 *			not used for Dragon, but is used for e.g. BIL
	 * 	@return		offset > 0 if success
	 *			0 if line number out of range
	 * 			< 0 if error:
	 *			    -60 if not valid for this format
	 *			    -61 if line # beyond current EOF
	 */
long ImageWriter::CalcImageFileOffset(uint uLineNo, const IMAGE * pImage,
				      IMAGEDATA_SELECTOR * pDataSel)
    {
    const IMAGEHDR * pHdr = pImage->pImageObj->getImageHeader()->getImageHdr();
    long lImageLineOffset = pHdr->ulDataOffset
			 + pHdr->ulLinePitch * (ulong)uLineNo;
    return lImageLineOffset;
    }

	/*	Put a line of raw data to the file
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *	Ignores ProcessRect.
	 *
	 *	@param pBuf	pointer to the data buffer
	 *	@param uLineNo	image memory line to write
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param bReReadable  TRUE => we may be reading/writing mixed
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			   -51  file open error
	 *			   -52  seek error
	 *			   -53  write error
	 *			   -55  file not open 
	 *			   -56  trying to write past end-of-file
	 *			   -75  buffer size doesn't match image line
	 *			   -91  line number bigger than image
	 *			     or errors from fwrite, fseek
	 */
int ImageWriter::putImageLineRaw(const byte * pBuf, ushort uLineNo,
				 size_t uBufSize, const IMAGE * pImg,
				 BOOL bReReadable)
    {
#undef FN_NAME
#define FN_NAME "ImageWriter::putImageLineRaw"
    int iRetval = DERR_FILE_OOB;
    int errnum = 0;
    if ((m_pFp == NULL) 
	    && ((m_pFp = (FILE *)fopen(pImg->filename,"rb+")) == NULL))
	iRetval = DERR_FILE_OPEN;
    else if (uLineNo >= pImg->lines)
        {
	iRetval = DERR_FN_ARG1;
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " lineno=%d imagelines=%d\n",
	       uLineNo,pImg->lines);
	logTrace(FN_NAME " lineno=%d imagelines=%d",uLineNo,pImg->lines);
        }
    else if (pImg->ulLinePitch != (ushort)uBufSize)
        {
	iRetval = DERR_HDR_MISMATCH;
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " linepitch=%ld bufsize=%ld\n",
	       pImg->ulLinePitch,uBufSize);
	logTrace(FN_NAME " linepitch=%ld bufsize=%ld",
	       pImg->ulLinePitch,uBufSize);
        }
    else
        {
	long lFilePosition = CalcImageFileOffset(uLineNo,pImg,NULL);
	FILE * pFp = (FILE *)m_pFp;
	ulong ulSize = fsize(pFp);
/*
	if (m_iDebug && ((uLineNo % 50) == 0))
	    fprintf(stderr,FN_NAME " "
		   "writing line %d sz=%d at %ld filesize=%ld\n",
		   uLineNo,uBufSize,lFilePosition,ulSize);
	if (m_iTrace && ((uLineNo % 50) == 0))
	    logTrace(FN_NAME " "
		   "writing line %d sz=%d at %ld filesize=%ld",
		   uLineNo,uBufSize,lFilePosition,ulSize);
*/
	if (lFilePosition < 0) 
	    iRetval = lFilePosition;
	else if ((ulong)lFilePosition > ulSize)
	    {
	    iRetval = DERR_FILE_OOB;
	    logTrace(FN_NAME " error %d=%s\n"
		     "\twriting line %d lFilePosition=%ld currentsize=%ld",
		     iRetval,dragonErrorMessage(iRetval),
		     uLineNo,lFilePosition,ulSize);
	    }
	else
	    {
	    if (fseek(pFp,lFilePosition,SEEK_SET))
		{
		errnum = errno;
		perror(FN_NAME " ");
		iRetval = DERR_FILE_SEEK;
		}
	    else
	        {
		iRetval = fwrite(pBuf, 1, uBufSize, pFp);
		if (iRetval < (int)uBufSize)
		    {
		    errnum = errno;
		    perror(FN_NAME " ");
		    fprintf(stderr,"iretval=%d\n",iRetval);
		    iRetval = DERR_FILE_RW; /* else it's the count */
		    }
//	    if (bReReadable)
		fflush(pFp);
		}
	    }
	if (iRetval < 0)
	    logTrace(FN_NAME " file I/O errno=%d "
		     "linesize=%d at file-position=%ld current-filesize=%ld\n",
		     errnum,uBufSize,lFilePosition,ulSize);
	}
    if (iRetval < 0)
        {
	logTrace(FN_NAME " (ex) error %d=%s\n"
		 "\twriting real line %d "
		 "pixcnt=%d bufsiz=%d fp=%p errno=%d linepitch=%ld",
		 iRetval,dragonErrorMessage(iRetval),
		 uLineNo,pImg->pixels,uBufSize,m_pFp,errnum,
		 pImg->ulLinePitch);
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " (ex) error %d=%s\n"
		   "\twriting real line %d "
		   "pixcnt=%d bufsiz=%d fp=%p errno=%d linepitch=%ld\n",
		   iRetval,dragonErrorMessage(iRetval),
		   uLineNo,pImg->pixels,uBufSize,m_pFp,errnum,
		   pImg->ulLinePitch);
	}
    return iRetval;
    }

	/*	Put a line of pixels to the file
	 *	The base class calcs are OK for file formats where
	 *	lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *	ProcessRect is ignored.
	 *
	 *	@param pBuf	pointer to the data buffer
	 *	@param uLineNo	image memory line to write
	 *	@param uBufSize	the size of pBuf - i.e. how much data to write
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param bReReadable  TRUE => we may be reading/writing mixed
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			   0 => line is outside ProcessRect;
	 *			   -53  write error
	 *			   -55  file not open 
	 *			   -56  trying to write past end-of-file
	 *			   -67  buffer size doesn't match image line
	 *			   -92  line number bigger than image
	 *			     or errors from fwrite, fseek
	 */
int ImageWriter::putImageLine(const byte * pBuf, ushort uLineNo,
			      size_t uBufSize, const IMAGE * pImg,
			      BOOL bReReadable)
    {
    return putImageLineRaw(pBuf,uLineNo,uBufSize,pImg,bReReadable);
    }

	/* return how many bytes will be needed for one line of raw data
	 */
size_t ImageWriter::getRawImageLineSize(size_t uPixels)
    {
    return uPixels;  /* default assumes one band, 8-bit data */
    }

		// return a formatted dump of the class member
const char * ImageWriter::dump(int detail, const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "ImageWriter dump imagehdr=%p fp=%p",
	     m_pHdr,m_pFp);
    return s_czDumpBuf;
    }

	/* if m_pFp is open, close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
int ImageWriter::close()
    {
#undef FN_NAME
#define FN_NAME "ImageWriter::close"
    int iRetval = 0;
    if (m_pFp != NULL)
        {
	FILE * pFp = (FILE *)m_pFp;
	iRetval = fclose(pFp);
	m_pFp = NULL;
	}
    logTrace(FN_NAME " (ex) returns %d",iRetval);
    return iRetval;
    }

	/* this has something to do with vector data
	 * ~~~
	 */
#if DRAGON_VER >= 6
int ImageWriter::setLinesBlob(const byte * pBlob,size_t uBlobSize) 
    { 
    logTrace("ImageWriter::setLinesBlob size=%d ERROR",uBlobSize);
    return DERR_FN_NOTIMPL; 
    } 
#endif

void IMAGEWRITER_END() { puts(FIL_ID); }
