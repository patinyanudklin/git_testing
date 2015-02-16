#include "drelease.h"
char IMAGEHDR_FACT_ID[]=
"\0@(#) " __FILE__ "  $Revision: 1.107 $$Date: 2014/03/15 10:28:18 $ " VERR;
D_REL_IDSTR;

/*
 *	filename dhead.cpp
 *		$Revision: 1.107 $ $Date: 2014/03/15 10:28:18 $	
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
 *   $Id: dhead.cpp,v 1.107 2014/03/15 10:28:18 rudahl Exp $
 *   $Log: dhead.cpp,v $
 *   Revision 1.107  2014/03/15 10:28:18  rudahl
 *   moved some stuff from dhead to imageHdr
 *
 *   Revision 1.106  2014/03/08 12:27:13  rudahl
 *   moved class methods from dhead to their own files, and adjusted Makefiles
 *
 *
 ****************************************************************
 * 
 * the imageHdr class fns, except for the factory fns, moved to imageHdr.cpp
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 6.4	2014-03-08 ktr	moved imageReader,imageWriter, imageHdr into their own files
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
#include "portfile.h"
#include "dhead.h"
#include "dragonOb.h"
#include "dhead-old.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"
#include "imageWriter.h"
#include "dragonImageReader.h"
#include "dragonOldImageReader.h"
#include "dragonOldImageWriter.h"
#include "dragonImageWriter.h"
#include "tiffImageWriter.h"
#include "screenImageReader.h"
#include "screenImageWriter.h"
#include "tiffImageReader.h"
#include "externImageReader.h"
#include "geotiff.h"

#ifdef NOMOPRE
		// read specified file and initialize IMAGEHDR
		// Assumes caller has already verified that
		// file exists and has read permissions
		// @param pczName	name of file to read
		// @param pSel		specify band of multiband file
		// @param pImg		some readers may need this
		// @return		reader if OK 
		// 			else NULL
		// 2011-02-25 ktr return NULL if any fatal error
ImageReader * ImageHdr::read(const char * pczName,
			     const IMAGEDATA_SELECTOR * pSel, 
			     Image * pImg)
    { 
    ImageReader * pIHR = imageReaderFactory(pczName);
    const char * czMethod = "ImageHdr::read";
    if (m_iDebug)
	fprintf(stderr,"%s (en) file '%s' m_iDebug=%d m_iTrace=%d pIHR=%p\n",
		czMethod,pczName,m_iDebug,m_iTrace,pIHR);
    if (m_iTrace)
	logTrace("%s (en) file '%s' m_iDebug=%d m_iTrace=%d pIHR=%p",
		 czMethod,pczName,m_iDebug,m_iTrace,pIHR);
    if (pIHR != NULL)
        {
 	pIHR->SetDesiredData(pSel);
	BOOL bSuccess = pIHR->readHeader(pczName,&m_hi,&m_iErrno,pImg);
	if (bSuccess && (m_hi.h_OriginalFileName == NULL))
            {
	    const char * pBs = strrchr(pczName,'\\');
	    const char * pFs = strrchr(pczName,'/');
	    const char * pCol = strrchr(pczName,':');
	    const char * pNode = (pBs > pFs) ? pBs+1
		: (pFs > pCol) ? pFs+1 : (pCol != NULL) ? pCol+1 : pczName;
	    if (m_iDebug)
		fprintf(stderr,"    %s assigning '%s' as original name\n",
			czMethod,pNode);
	    m_hi.h_OriginalFileName = strdup(pNode);
	    }
	}
    if (m_iTrace)
	logTrace("%s (ex) file '%s' pIHR=%p err=%d",
		 czMethod,pczName,pIHR,m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) file '%s' pIHR=%p err=%d\n",
		 czMethod,pczName,pIHR,m_iErrno);
    return ((m_iErrno < DERR_OK) && (m_iErrno > DERR_NON_FATAL)) ? NULL : pIHR;
    }

		// return a reader which can read the specified file
		// or NULL
ImageReader * ImageHdr::imageReaderFactory(const char * pczName)
    {
    ImageReader * pReader = NULL;
#undef FN_NAME
#define FN_NAME "ImageHdr::imageReaderFactory"

    if (m_iDebug)
        fprintf(stderr,FN_NAME " (en) file=%s\n",pczName);
    if (m_iTrace)
        logTrace(FN_NAME " (en) file=%s",pczName);
    if (DragonImageReader::test(pczName,m_iDebug))
        {
	pReader = new DragonImageReader(m_iDebug,m_iTrace);
	}
    else if (DragonOldImageReader::test(pczName,m_iDebug))
        {
	pReader = new DragonOldImageReader(m_iDebug,m_iTrace);
	}
    else if (DragonImageReader::vectest(pczName,m_iDebug))
        {
	pReader = new DragonImageReader(m_iDebug,m_iTrace);
	}
    else if (DragonImageReader::metatest(pczName,m_iDebug))
        {
	pReader = new DragonImageReader(m_iDebug,m_iTrace);
	}
#if ! defined ROSE_ONLY // imageReaderFactory in rosetta only needs Dragon images
    else if (ScreenImageReader::test(pczName,m_iDebug))
        {
	pReader = new ScreenImageReader(m_iDebug,m_iTrace);
	}
    else if (TiffImageReader::test(pczName,m_iDebug))
        {
	pReader = new TiffImageReader(m_iDebug,m_iTrace);
	}
    else if (ExternImageReader::test(pczName,m_iDebug,m_iTrace))
        {     // else serch the objects tree for candidates 
	pReader = new ExternImageReader(m_iDebug,m_iTrace);
	}
#endif
    if (pReader != NULL)
        {
	m_uImageType = pReader->getImageType();
	pReader->m_pHdr = &m_hi;
	}
    if (pReader != NULL)
        {
	const char * pczDump = pReader->dump(1);
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " (ex) Found reader object: %s\n",pczDump);
	if (m_iTrace)
	    logTrace(FN_NAME " (ex) Found reader object: %s",pczDump);
	}
    else
        {
	m_iErrno = DERR_UNSUP_FORMAT;
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " (ex) reader %s object not found\n",
		    VERR);
	if (m_iTrace)
	    logTrace(FN_NAME " (ex) reader %s object not found",VERR);
	}
    return pReader;
    }
 		
		// return a writer which can write the specified file
		// or NULL
ImageWriter * ImageHdr::imageWriterFactory(IMGTYPE_T uFormat) const
    {
    ImageWriter * pWrtr = NULL;
    if (m_iDebug)
	fprintf(stderr,"ImageHdr::imageWriterFactory - uFormat is %d\n",
		uFormat);
    if ((uFormat == IT_DRAGON) || (uFormat == IT_DRAGON_VEC))
	pWrtr = new DragonImageWriter(m_iDebug,m_iTrace);
    else if (uFormat == IT_IGC_META)
	pWrtr = new DragonImageWriter(m_iDebug,m_iTrace);
    else if (uFormat == IT_DRAGON_OLD)
	pWrtr = new DragonOldImageWriter(m_iDebug,m_iTrace);
#if ! defined ROSE_ONLY // imageWriterFactory in rosetta only needs Dragon images
    else if (uFormat == IT_TIFF)
	pWrtr = new TiffImageWriter(m_iDebug,m_iTrace);
//    else if (uFormat == IT_JPEG)
//	pWrtr = new JpegImageWriter(m_iDebug,m_iTrace);
    else if ((uFormat == IT_CHUNK54) || (uFormat == IT_CHUNK60))
	pWrtr = new ScreenImageWriter(m_iDebug,m_iTrace);
#endif // if ! defined ROSE_ONLY // imageWriterFactory in rosetta only needs Dragon images
//    if (pWrtr != NULL)
//	pWrtr->m_pHdr = &m_hi;
    if ((pWrtr != NULL) && m_iDebug)
	fprintf(stderr,"ImageHdr::imageWriterFactory returning writer object: %s\n",
	       pWrtr->dump());
    if ((pWrtr != NULL) && m_iTrace)
	logTrace("ImageHdr::imageWriterFactory returning writer object: %s",
	       pWrtr->dump());
    return pWrtr;
    }
#endif 		
void IMAGEHDR_FACT_END() { puts(FIL_ID); }

