#include "drelease.h"
char TIFFIMAGE_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.44 $$Date: 2015/01/16 07:39:47 $";
D_REL_IDSTR;

/*
 *	filename tiffImageReader.cpp
 *		$Revision: 1.44 $ $Date: 2015/01/16 07:39:47 $	
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
 ****************************************************************
 *   $Id: tiffImageReader.cpp,v 1.44 2015/01/16 07:39:47 rudahl Exp $
 *   $Log: tiffImageReader.cpp,v $
 *   Revision 1.44  2015/01/16 07:39:47  rudahl
 *   working on import
 *
 *   Revision 1.43  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.42  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.41  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.40  2014/03/28 14:51:12  rudahl
 *   working on auto import
 *
 *   Revision 1.39  2014/03/15 10:28:26  rudahl
 *   improved tracing
 *
 *   Revision 1.38  2014/03/08 06:02:18  rudahl
 *   improve debug, comments
 *
 *   Revision 1.37  2014/02/22 13:35:07  rudahl
 *   purge
 *
 *   Revision 1.36  2014/01/31 04:11:03  rudahl
 *   added return value to getImageLineRaw; cleaned out old stuff
 *
 *   Revision 1.35  2014/01/27 12:21:28  rudahl
 *   adapt to tiles, -a
 *
 *   Revision 1.34  2013/08/23 13:25:32  rudahl
 *   adapt to read tiled files, input LatLon
 *
 *   Revision 1.33  2012/07/01 09:30:27  rudahl
 *   fix problems importing GeoEye tiff files
 *
 *   Revision 1.32  2011/02/27 08:24:51  rudahl
 *   final work on tiff IO
 *
 *   Revision 1.31  2011/02/06 10:30:11  rudahl
 *   tracing
 *
 *   Revision 1.30  2011/02/03 14:21:48  rudahl
 *   fix georef with only intergraph and autodesk tags
 *
 *   Revision 1.29  2011/01/30 01:54:41  rudahl
 *   geotiff import works OK now
 *
 *   Revision 1.28  2011/01/18 01:54:08  rudahl
 *   working on tiff I/O
 *
 *   Revision 1.27  2011/01/16 10:55:03  rudahl
 *   improved (but not final) tags reading
 *
 *   Revision 1.26  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.25  2011/01/10 06:39:45  rudahl
 *   working on georef info
 *
 *   Revision 1.24  2011/01/03 07:08:21  rudahl
 *   regressing to libtiff 3.7
 *
 *   Revision 1.23  2011/01/03 06:30:56  rudahl
 *   re-sequence header files
 *
 *   Revision 1.22  2010/12/19 06:56:58  rudahl
 *   fix some docs
 *
 *   Revision 1.21  2010/12/11 07:49:22  rudahl
 *   change Linear_meter to meter
 *
 *   Revision 1.20  2007/09/25 11:50:00  rudahl
 *   fixed  TIFF conversion for ERDAS 3-band TIFFS
 *
 *   Revision 1.19  2007/08/02 12:48:00  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.18  2007/06/17 10:42:00  rudahl
 *   adapt for PLANAR=2
 *
 *   Revision 1.17  2007/06/14 04:39:08  rudahl
 *   testing support for planar=2
 *
 *   Revision 1.16  2007/01/01 09:42:47  rudahl
 *   improved tracing, dumps; originalfileinfo
 *
 *   Revision 1.15  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.14  2006/11/26 07:33:31  rudahl
 *   Trial extension 2 for multibands, bytes
 *
 *   Revision 1.13  2006/11/26 06:45:58  goldin
 *   Fix typos
 *
 *   Revision 1.12  2006/11/25 11:44:27  rudahl
 *   Trial extension for multibands, bytes
 *
 *   Revision 1.11  2006/01/03 06:31:57  rudahl
 *   fixed georeferencing to match Dragon convention
 *
 *   Revision 1.10  2005/12/30 10:32:53  rudahl
 *   fixed dump()
 *
 *   Revision 1.9  2005/08/18 03:48:36  rudahl
 *   fixes to scaling
 *
 *   Revision 1.8  2005/07/23 08:23:19  rudahl
 *   fine-tuning geotiff
 *
 *   Revision 1.7  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.6  2005/07/20 11:12:00  rudahl
 *   added tracing
 *
 *   Revision 1.5  2005/07/18 12:56:36  rudahl
 *   work on geotiff
 *
 *   Revision 1.4  2005/07/15 02:40:07  rudahl
 *   working on geotiff
 *
 *   Revision 1.3  2005/07/09 06:24:08  rudahl
 *   working on tiff
 *
 *   Revision 1.2  2005/07/09 04:59:29  rudahl
 *   working on tiff
 *
 *   Revision 1.1  2005/07/07 15:22:41  rudahl
 *   initial from mooochie
 *
 *
 ****************************************************************
 * 
 * Define a class for reading from Tiff and Geotiff image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.7	2005-07-07 ktr	new
 * 	2006-01-02 ktr	was setting ref_y, ycellsize to wrong sign
 * 5.10	2007-06-14 ktr	testing support for planar==2
 *                      (use JaredImage.tif for testing)
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 * 6	2010-12-09 ktr	as a special (but frequent) case, replace the
 *			unitname 'linear_meter' by 'meter'
 * 6.1	2010-12-18 ktr	added getAuxInfo()
 * 6.4	2014-02-15 ktr	read tiled images
 */

/*
 * alternative to proj4 is
 * http://geographiclib.sourceforge.net/cgi-bin/GeoConvert
 */
 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

// if dtypes.h follows tiffio.h in new libtiff version, 
// then TiffReader::test is not found by linker
//#include "dtypes.h"  // this must preceed tiffio.h for libtiff 3.9

#include "tiffio.h"
#include "xtiffio.h"
#include "geotiffio.h"
#include "geo_tiffp.h"
#include "geo_keyp.h"
#include "geo_normalize.h"
#include "proj_api.h"

#include "dtypes.h"  // this must follow tiffio.h for libtiff 3.7
#include "dlimits.h"  /* for strcat_array */
#include "dragon-errors.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "dragonHd.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"
#include "tiffImageReader.h"

Class TiffImageReader::s_class_Base("TiffImageReader",
				    "Class for reading GEOTIFF image files");

byte * TiffImageReader::s_pTilesBuf = NULL;
uint TiffImageReader::s_uFirstLineInTileRow = 0xFFFFFFFF;

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
TiffImageReader::TiffImageReader(int iDebug, int iTrace)
    {
    m_pClass = &s_class_Base; 
    m_pClass->setSubClass(ImageReader::getBaseClass());
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    m_readLineBufferSize = 0;
    m_iPlanar = -1;
    m_iPhoto = -1;
    }

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
		// This does not set s_iNumBands 
		// so do not call from externImageReader
BOOL TiffImageReader::test(const char * pczFilename, BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    if (bDebug)
	printf("TiffImageReader::test (en) %s\n",pczFilename);
    if (strlen(pczFilename) > 4)
	{
	const char * extn = &pczFilename[ strlen(pczFilename)-4];
	//	if (bDebug)
	//    printf("TiffImageReader::test extn='%s'\n",extn);
	if ((strcasecmp(extn,".tif") == 0)
  	      ||(strcasecmp(extn,"tiff") == 0))
	    bRetval = TRUE;
	}
    if (bDebug)
	printf("TiffImageReader::test (ex): %s\n",YESNO(bRetval));
    return bRetval;
    }

		// read an already-open file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
BOOL TiffImageReader::readHeader(FILE * pFile,
				 IMAGEHDR * pHdr,int * pErrNum, Image * pImg)
    {
    *pErrNum = DERR_FN_NOTIMPL;
    return FALSE;
    }

		// read header of a not-already-open file 
		// @param pczFileName	name of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
BOOL TiffImageReader::readHeader(const char * pczFileName,
				 IMAGEHDR * pHdr,int * pErrNum, Image * pImg)
    {
    BOOL bRetval = FALSE;
    *pErrNum = -1;
    if (m_iDebug)
	printf ("TiffImageReader::readHeader (en) of '%s'\n",
		pczFileName);
    if (m_iTrace)
	logTrace("TiffImageReader::readHeader (en) of '%s'",
		 pczFileName);
    TIFF* tif = XTIFFOpen(pczFileName, "r"); 
    if (tif) 
	{ 
	m_pHdr = pHdr;
	int iStat = copyFields(tif);
	m_pHdr->h_OriginalFileName = strdup(pczFileName);
	if (iStat == 0)
	    {
	    *pErrNum = DERR_OK;
	    bRetval = TRUE;
	    }
	else if (iStat <= DERR_NON_FATAL)
	    {
	    *pErrNum = iStat;
	    bRetval = TRUE;
	    }
	else
	    {
	    *pErrNum = DERR_TIFF_NOTHANDLED;
	    }
	m_readLineBufferSize = TIFFScanlineSize(tif);
	XTIFFClose(tif);
	}
    else
	*pErrNum = DERR_FILE_OPEN;
    if (m_iDebug)
	printf("TiffImageReader::readHeader (ex) of '%s' buffersize=%d "
	       "bandlayout=%d (BSQ=%d) hdr at %p\n",
	       m_pHdr->h_OriginalFileName,m_readLineBufferSize,
	       m_pHdr->uBandLayout,IMG_BSQ,m_pHdr);
    if (m_iTrace)
	logTrace("TiffImageReader::readHeader (ex) of '%s' buffersize=%d header at %p",
	    m_pHdr->h_OriginalFileName,m_readLineBufferSize,m_pHdr);
    return bRetval;
    }

	/*	Retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The image data may be 16-bit data and may be RGB interleaved
	 *	and may be tiled
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param pDataSel	NULL or selects data to read
	 *			(for TIFF, may select R=0, G=1, B=2 band)
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			   0 => line is outside ProcessRect;
	 *			   -53  read error
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 */
int TiffImageReader::getImageLine(byte * pBuf, ushort uLineNo,
				  size_t uBufSize, const Image * pImage,
				  IMAGEDATA_SELECTOR * pDataSel)
    {
    ushort uBandNo = (pDataSel != NULL) ? pDataSel->uBandNo : 0;
    if (m_iDebug && (uLineNo < 4))
        printf("TiffImageReader::getImageLine (en) line %d band %d of %d\n",
	       uLineNo,uBandNo,m_pHdr->uBands);
    int iRetval = getImageLineRaw(pBuf,uLineNo,uBufSize,pImage,pDataSel);
    // if necessary, coalesce the data into the selected band's value
    if (m_iDebug && (uLineNo < 4))
        printf("TiffImageReader::getImageLine returns %d (hdr=%p %d bands, %d bpp)\n",
    	       iRetval,m_pHdr,m_pHdr->uBands,m_pHdr->bits_per_pix);
    // If it's multi-band and not BSQ
    // (for BSQ, getImageLineRaw just returns data for one band)
    if ((iRetval > 0) && (m_pHdr->uBands > 1)
	    && (m_pHdr->uBandLayout != IMG_BSQ))
        {
	iRetval /= m_pHdr->uBands;
	if (m_pHdr->bits_per_pix <= 8)
	    {
	    const byte * pSrc = pBuf + uBandNo; 
	    byte * pDest = pBuf; 
	    for (int j=0; j<iRetval; j++)
	        {
		*pDest = *pSrc;
		pSrc += m_pHdr->uBands;
		pDest++;
		}
	    }
	else
	    {
	    const ushort * pSrc = ((ushort *)pBuf) + uBandNo; 
	    ushort * pDest = (ushort *)pBuf; 
	    for (int j=0; j<iRetval; j++)
	        {
		*pDest++ = *pSrc;
		pSrc += m_pHdr->uBands;
		}
	    }
        }
    //    printf("TiffImageReader::getImageLine (ex) returns %d\n",iRetval);
    return iRetval;
    }

	/*	Retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The image data may be 16-bit data and may be RGB interleaved
	 *	and may be tiled
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param pDataSel	NULL or selects data to read (not used)
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			   0 => line is outside ProcessRect;
	 *			   -51  open error
	 *			   -53  read error
	 *			   -56  past EOF ?
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 */
int TiffImageReader::getImageLineRaw(byte * pBuf, ushort uLineNo,
				     size_t uBufSize, const Image * pImage,
				     IMAGEDATA_SELECTOR * pDataSel)
    {
//    printf("TiffImageReader::getImageLineRaw (en) line %d\n",uLineNo);
    const IMAGE * pImg = &pImage->image;
    // pixel pitch, usually = number of bands
    ushort uTotBytesPP = (pImg->ulPixPitch > 0) ? (ushort) pImg->ulPixPitch : 1 ;
    ushort uBytesPP = (m_pHdr->bits_per_pix > 8) ? 2 : 1;
    int iRetval = 0;
    ushort uPixReadCount = min((pImg->ProcessRect.Xmax + 1),pImg->pixels);
    s_outbuf[0] = '\0'; // build a trace line for error reporting
//    if (m_pHdr->uBandLayout == IMG_BSQ)
//    return DERR_FN_NOTIMPL;
    // set selected band over and over (but no matter)
    m_pHdr->h_uOriginalBandNumber = (pDataSel != NULL) ? pDataSel->uBandNo : 0;
    if (uLineNo >= pImg->lines)
        {
	iRetval = DERR_FILE_OOB;
	if (m_iTrace)
	    Logger::logTrace("TiffImageReader::getImageLine: "
			     "Image index %d requested line %d of %d",
			     pImg->thisone,uLineNo,pImg->lines);
	strcat_array(s_outbuf,"\tline number too high\n");
	}
    else if (uPixReadCount * uTotBytesPP <= (ushort)uBufSize)
        {
	TIFF * pTif = (TIFF *) m_pFp;
	if (((int) uLineNo < pImg->ProcessRect.Ymin)
		|| ((int) uLineNo >  pImg->ProcessRect.Ymax))
	    {
	    strcat_array(s_outbuf,"\tfits inside buffer but outside ProcessRect\n");
	    iRetval = 0;
	    }
	else if ((pTif == NULL) 
	         && ((pTif = XTIFFOpen(pImg->filename,"r")) == NULL))
            {
	    perror("TiffImageReader::getImageLine open error");
	    printf("filename='%s'\n",pImg->filename);
	    strcat_array(s_outbuf,"\topen error\n");
	    m_iErrno = iRetval = DERR_FILE_OPEN;
	    }
	else //if (pImg->pFp != NULL)
	    {
	    m_pFp = (FILE *) pTif;
	    BOOL bTiled = TIFFIsTiled(pTif);
	    //	    if ((uLineNo < 200) && m_iDebug)
	    //	printf("getImageLineRaw line %d buf=%p bTiles=%s tilesbuf=%p tile starts at %d bpp=%d\n",
	    //	    uLineNo,pBuf,YESNO(bTiled),s_pTilesBuf,s_uFirstLineInTileRow,uTotBytesPP);
	    // it looks like TIFFTileSize returns the largest tile, 
	    // or else maybe they/re all the same size
	    uint sizeNeeded = TIFFScanlineSize(pTif);
	    strcat_array(s_outbuf,"\ttesting for tiled\n");
	    if (bTiled && (uBytesPP > 1))
		iRetval = DERR_FN_NOTIMPL;
	    else if (bTiled)
		{
		strcat_array(s_outbuf,"\tIS tiled\n");
		uint uTileSize = TIFFTileSize(pTif);
		uint uTileRowBytes = TIFFTileRowSize(pTif);
		uint uLinesPerTileRow = uTileSize / uTileRowBytes;
		uint uTilesPerRow = (uTotBytesPP*pImg->pixels + uTileRowBytes - 1) / uTileRowBytes;
		uint uPixWidthPerTile = uTileRowBytes / uTotBytesPP;
		uint uCurrLineInTile = uLineNo % uLinesPerTileRow;
		uint uCurrOffsetInTile = uCurrLineInTile * uTileRowBytes;
		// this will hold a row of tiles, 
		// but the data will not be arranged by data row
		byte * pTileBuf = (byte *)calloc(1,uTileSize);
		// to avoid re-reading all the tiles on every image line, 
		// read and save one row's worth. 
		// if s_pTilesBuf not NULL then s_uFirstLineInTileRow says which is 
		// the first line in the current row of tiles.
		// This might be a memory leak in Dragon since we might not
		// release s_pTilesBuf 
		// so if uLineNo < s_uFirstLineInTileRow, free s_pTilesBuf
		// also it's in the dtor (tiffImageReader.h)
		if ((s_pTilesBuf != NULL) && (uLineNo < s_uFirstLineInTileRow))
		    {
		    free (s_pTilesBuf);
		    s_pTilesBuf = NULL;
		    s_uFirstLineInTileRow = 0xFFFFFFFF;
		    }
	        if (s_pTilesBuf == NULL)
		    s_pTilesBuf = (byte *)calloc(uTilesPerRow,uTileSize);
//		if (uLineNo < 200)
//		    printf("getImageLineRaw bufs=%p and %p\n",s_pTilesBuf,pTileBuf);
		if ((s_pTilesBuf == NULL) || (pTileBuf == NULL))
		    iRetval = DERR_MEM_ALLOC;
		else
		    {
		    uint uTileIndex;
		    sizeNeeded = uBufSize;  // force it to fit
//		    if (uLineNo < 200)
//			{
//			uint uTileCount = TIFFNumberOfTiles(pTif);
//			printf("Tiled file with %u tiles size=%u rowbytes=%u "
//			   "expected bytes=%u Lines/TileRow=%u Tiles/Row=%u\n",
//			   uTileCount,uTileSize,uTileRowBytes,
//			   uTotBytesPP*pImg->pixels,uLinesPerTileRow,
//			   uTilesPerRow);
//			}
		    if ((uLineNo >= (s_uFirstLineInTileRow+uLinesPerTileRow))
			    || (s_uFirstLineInTileRow == 0xFFFFFFFF))
			{
			if (s_uFirstLineInTileRow == 0xFFFFFFFF)
			    s_uFirstLineInTileRow = 0;
			while(uLineNo >= (s_uFirstLineInTileRow+uLinesPerTileRow))
			    s_uFirstLineInTileRow += uLinesPerTileRow;
//			if (uLineNo < 200)
//			    printf("   reading %d tiles for lineno %d firstline=%d \n",
//				uTilesPerRow,uLineNo,s_uFirstLineInTileRow);
			for (uTileIndex = 0; uTileIndex < uTilesPerRow; uTileIndex++)
			    {
			    TIFFReadTile(pTif,pTileBuf,uTileIndex*uPixWidthPerTile,
				s_uFirstLineInTileRow,0,0);
			    memcpy(&s_pTilesBuf[uTileIndex*uTileSize],pTileBuf,uTileSize);
			    }
			}
		    for (uTileIndex = 0; uTileIndex < uTilesPerRow; uTileIndex++)
			{
			memcpy(pTileBuf,&s_pTilesBuf[uTileIndex*uTileSize],uTileSize);
//			TIFFReadTile(pTif,pTileBuf,uTileIndex*uPixWidthPerTile,
//			    uLineNo,0,0);
			uint uBytesToCopy = uTileRowBytes;
			if (uTileRowBytes*(1+uTileIndex) > uBufSize)
			    uBytesToCopy =  uBufSize - uTileRowBytes*uTileIndex;
//		    if ((uTileIndex < 4) && (uLineNo < 200))
//			printf("About to copy %u bytes from %p to %p\n",
//			       uBytesToCopy,pTileBuf+uCurrOffsetInTile,
//			       pBuf+uTileRowBytes*uTileIndex);
			memcpy(pBuf+uTileRowBytes*uTileIndex,
			       pTileBuf+uCurrOffsetInTile,uBytesToCopy);
			}
		    iRetval = uPixReadCount;
		    free(pTileBuf);
		    }   // end of bTiles && mem OK
 		}	// end of bTiled
// 	        logTrace("tiffImageReader::size needed = %d have=%d",sizeNeeded,uBufSize);
// 	        printf("size needed = %d have=%d\n",sizeNeeded,uBufSize);
	    if (iRetval < 0)
		{
		strcat_array(s_outbuf,"\terror already: ");
		strcat_array(s_outbuf,dragonErrorMessage(iRetval));
		strcat_array(s_outbuf,"\n");
		}
	    else if (sizeNeeded > (ushort)uBufSize)
	        {
		strcat_array(s_outbuf,"\tbuffer not big enough\n");
		iRetval = DERR_IMAGE_TOOBIG;
		if (m_iDebug != 0)
		    fprintf(stderr,"tiffImageReader::getImageLineRaw too big buffer needed"
			    "needed = %u bufsize=%u\n",sizeNeeded,uBufSize);
		logTrace("tiffImageReader::getImageLineRaw too big buffer needed"
			 "needed = %u bufsize=%u",sizeNeeded,uBufSize);
	        }
	    else
	        {
		iRetval = uPixReadCount;
		if (bTiled) // pBuf is already loaded
		    {
//		    if (TIFFReadTile(pTif, pBuf, 0, uLineNo, 0, 
//					 m_pHdr->h_uOriginalBandNumber) < 0)
//			iRetval = DERR_FILE_RW; /* else it's the count */
		    }
		else if (m_pHdr->uBandLayout == IMG_BSQ)
		    {
		    if (TIFFReadScanline(pTif, pBuf, uLineNo, 
					 m_pHdr->h_uOriginalBandNumber) < 0)
			iRetval = DERR_FILE_RW; /* else it's the count */
		    }
		else
		    {
		    if (TIFFReadScanline(pTif, pBuf, uLineNo) < 0)
			iRetval = DERR_FILE_RW; /* else it's the count */
		    }
		}
	    }
	}
    else
        {
	strcat_array(s_outbuf,"\timage too big\n");
	iRetval = DERR_IMAGE_TOOBIG;
	if (m_iDebug != 0)
	    fprintf(stderr,"tiffImageReader::getImageLineRaw too big for buffer"
		 "count = %u bytesPP=%u bufsize=%u\n",
		 uPixReadCount,uTotBytesPP,uBufSize);
	logTrace("tiffImageReader::getImageLineRaw too big for buffer"
		 "count = %u bytesPP=%u bufsize=%u",
		 uPixReadCount,uTotBytesPP,uBufSize);
	}
    if (iRetval < 0)
	{
	if (m_iDebug != 0)
	    printf("TiffImageReader::getImageLineRaw "
		   "error %s (%d) reading real line %d->%d "
		   "pixcnt=%d bufsiz=%d\ntrace=%s\n",
		   dragonErrorMessage(iRetval),iRetval,
		   uLineNo,uLineNo,uPixReadCount,uBufSize,s_outbuf);
	Logger::logTrace("TiffImageReader::getImageLine "
			 "error %s (%d) reading real line %d->%d "
			 "pixcnt=%d bufsiz=%d\ntrace=%s",
			 dragonErrorMessage(iRetval),iRetval,
		         uLineNo,uLineNo,uPixReadCount,uBufSize,s_outbuf);
	}
//    printf("TiffImageReader::getImageLineRaw (ex) returns %d\n",iRetval);
    return iRetval;
    }

	/* if m_pFp is open, close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
int TiffImageReader::close()
    {
    int iRetval = 0;
    if (m_iDebug)
	printf("TiffImageReader::close (en)\n");
    if (m_pFp != NULL)
        {
	TIFF * pTif = (TIFF *)m_pFp;
	XTIFFClose(pTif);
	m_pFp = NULL;
	}
    if (m_iDebug)
	printf("TiffImageReader::close (ex)\n");
    return iRetval;
    }

	/* Get some sort of device-dependent info.
	 * initial implementation is for tiffImageReader  (q.v.)
	 *   where pczName names one of a few possible tags
	 * @return	desired value as a string, or NULL
	 */
const char * TiffImageReader::getAuxInfo(const char * pczName) const
    {
    return (strcmp(pczName,"PLANARCONFIG") == 0)
	? getAuxInfo(TIFFTAG_PLANARCONFIG) 
	:(strcmp(pczName,"PHOTOMETRIC") == 0)
	? getAuxInfo(TIFFTAG_PHOTOMETRIC) 
	: NULL;
    }
const char * TiffImageReader::getAuxInfo(uint uId) const
    {
	// these names come from tiff.h
    const char * czPlanar[]
	    = { NULL, "PLANARCONFIG_CONTIG","PLANARCONFIG_SEPARATE"} ;
    const char * czPhoto[]
	    =   { 
		"PHOTOMETRIC_MINISWHITE",
		"PHOTOMETRIC_MINISBLACK",
		"PHOTOMETRIC_RGB",
		"PHOTOMETRIC_PALETTE",
		"PHOTOMETRIC_MASK",
		"PHOTOMETRIC_SEPARATED",
		"PHOTOMETRIC_YCBCR",
		NULL,
		"PHOTOMETRIC_CIELAB"
		"PHOTOMETRIC_ICCLAB",
		"PHOTOMETRIC_ITULAB"};
    // there are two additional values at 32844, 32845
    return ((uId == TIFFTAG_PLANARCONFIG)
	    && (m_iPlanar < (int)AY_COUNT(czPlanar))) ? czPlanar[m_iPlanar] 
	: ((uId == TIFFTAG_PHOTOMETRIC)
	    && (m_iPhoto < (int)AY_COUNT(czPhoto)))  ? czPhoto[m_iPhoto] 
	: NULL;
    }

// copy tie points from TIFF file into m_pHdr
// and rearragne them into a standard sequence if there are four
// tiepoint_count is 6 * number of tiepoints (!)
// set *pcZone, *pdLongitude
// return < 0 if error
// else  1 if the coords seem to be already in UTM form, else 0
int TiffImageReader::_copyTiePoints(int tiepoint_count,double * tiepoints,
				    char * pcZone, double * pdLongitude)
    {
#undef FN_NAME
#define FN_NAME "TiffImageReader::_copyTiePoints"
    int iStatus = 0;
    m_pHdr->uModelTiepoints = tiepoint_count / 6;
    m_pHdr->pModelTiepoints 
	= (TIEPOINT_t *)calloc(m_pHdr->uModelTiepoints,sizeof(TIEPOINT_t));
		    // extract all the tiepoints,
		    // plus the easternmost longtitude and whether south/north
    * pdLongitude = -200;
    if (! *pcZone)
	*pcZone = 'N';
    for (int j=0; j<m_pHdr->uModelTiepoints; j++)
        {
	TIEPOINT_t tp;
	tp.uI = (ushort)tiepoints[j*6];
	tp.uJ = (ushort)tiepoints[j*6 + 1];
	tp.uK = (ushort)tiepoints[j*6 + 2];
	tp.dX = tiepoints[j*6 + 3];
	tp.dY = tiepoints[j*6 + 4];
	tp.dZ = tiepoints[j*6 + 5];
	if (*pdLongitude < tp.dX)
	    * pdLongitude = tp.dX;
//	*pcZone = 'N';
	if (tp.dY < 0)
	    *pcZone = 'S';
	if ((tp.dX > 180) || (tp.dY > 180))
	    iStatus = 1; /* > 180 => not lat-lon */
	// SPOT is in ul-ur-lr-ll sequence (which we want)
	if ((j == 0) || (j > 4))
	    memcpy(&m_pHdr->pModelTiepoints[j],&tp,sizeof(TIEPOINT_t));
	else if (tp.uJ == m_pHdr->pModelTiepoints[0].uJ)
	    memcpy(&m_pHdr->pModelTiepoints[1], // ur corner
		   &tp,sizeof(TIEPOINT_t));
	else if (tp.uI == m_pHdr->pModelTiepoints[0].uI)
	    memcpy(&m_pHdr->pModelTiepoints[3], // ll corner
		   &tp,sizeof(TIEPOINT_t));
	else if ((m_pHdr->pModelTiepoints[2].uI == 0)
		 && (m_pHdr->pModelTiepoints[2].uJ == 0))
	    memcpy(&m_pHdr->pModelTiepoints[2], // lr corner?
		   &tp,sizeof(TIEPOINT_t));
	else // maybe these aren't really corners
	    memcpy(&m_pHdr->pModelTiepoints[j],
		   &tp,sizeof(TIEPOINT_t));
	logTrace(FN_NAME 
		 " tiepoint %d: %d %d %d %4.2f %4.2f %4.2f",
		 j,m_pHdr->pModelTiepoints[j].uI,
		 m_pHdr->pModelTiepoints[j].uJ,
		 m_pHdr->pModelTiepoints[j].uK,
		 m_pHdr->pModelTiepoints[j].dX,
		 m_pHdr->pModelTiepoints[j].dY,
		 m_pHdr->pModelTiepoints[j].dZ);
	}
    return iStatus;
    }

// try to get tie points using proj4 based on uZone
// assumes m_pHdr->..ModelTiePoints copied from TIFF file
// return 0 on success
int TiffImageReader::_getTiePointsFromProj4(uint uZone)
    {
#undef FN_NAME
#define FN_NAME "tiffImageReader::_getTiePointsFromProj4"
    int iStatus = -1;
    char czProjInitStr[1024]; // ~~~ should use specified datum
    sprintf(czProjInitStr,"+proj=utm +zone=%d +ellps=WGS84",uZone);
    logTrace(FN_NAME " czProjInitStr=%s",czProjInitStr);
    void * pjProj = pj_init_plus(czProjInitStr);
    projUV * p = (projUV *) calloc(m_pHdr->uModelTiepoints,
				   sizeof(projUV));
    if (p != NULL)
        {
	for (int j=0; j<m_pHdr->uModelTiepoints; j++)
	    {
	    p[j].u = m_pHdr->pModelTiepoints[j].dX * DEG_TO_RAD;
	    p[j].v = m_pHdr->pModelTiepoints[j].dY * DEG_TO_RAD;
	    p[j] = pj_fwd(p[j],pjProj);
	    if (p[j].v < 0) // southern hemisphere? 
		p[j].v += 10000000;
		// see http://geographiclib.sourceforge.net/cgi-bin/GeoConvert
		// to check conversions. Remember tracing is only
		// small number of decimal places.
		//
		// check this is not already UTM
		// this will fail in a very small area on the 
		// equator and prime meridian intersection
	    logTrace(FN_NAME " zone %d: %5.4f,%5.4f => %3.2f,%3.2f",
		     uZone,m_pHdr->pModelTiepoints[j].dX,
		     m_pHdr->pModelTiepoints[j].dY, p[j].u,p[j].v);
			    // revise header to UTM
	    m_pHdr->pModelTiepoints[j].dX = p[j].u;
	    m_pHdr->pModelTiepoints[j].dY = p[j].v;
	    }
	iStatus = 0;
	logTrace(FN_NAME " finished calculating tiepoints old method");
	free(p);
	}
    return iStatus;
    }

// put fixed point and pixel size, calculated from tiepoints, into header
// return 0
int TiffImageReader::_recordFixedPointsAndPixelSize(int tiepoint_count,
						    BOOL bCellSizeCalcd)
    {
#undef FN_NAME
#define FN_NAME "TiffImageReader::_recordFixedPointsAndPixelSize"
		    // calculate the UTM zone and setup PROJ4
    int iStatus = 0;
    uint uHeight = m_pHdr->size[0];
    uint uWidth = m_pHdr->size[1];
    if ((m_pHdr->uModelTiepoints >= 4)
	&& (m_pHdr->pModelTiepoints[0].uI <= 1)
			&& (m_pHdr->pModelTiepoints[0].uJ <= 1)
			&& (m_pHdr->pModelTiepoints[1].uI == uWidth)
			&& (m_pHdr->pModelTiepoints[1].uJ <= 1)
			&& (m_pHdr->pModelTiepoints[2].uI == uWidth)
			&& (m_pHdr->pModelTiepoints[2].uJ == uHeight)
			&& (m_pHdr->pModelTiepoints[3].uI <= 1)
			&& (m_pHdr->pModelTiepoints[3].uJ == uHeight)
			&& (! bCellSizeCalcd))
        {
#define PP m_pHdr->pModelTiepoints
	double dWidth = sqrt((PP[1].dX-PP[0].dX) * (PP[1].dX-PP[0].dX)
			     + (PP[1].dY-PP[0].dY) * (PP[1].dY-PP[0].dY));
	double dHeight  = sqrt((PP[3].dX-PP[0].dX) * (PP[3].dX-PP[0].dX)
			       + (PP[3].dY-PP[0].dY) * (PP[3].dY-PP[0].dY));
	logTrace(FN_NAME " image = %3.2fx%3.2f pixel=%3.2fx%3.2f",
		 dWidth,dHeight,
		 dWidth/(double)m_pHdr->size[1],
		 dHeight/(double)m_pHdr->size[0]);
	m_pHdr->xcell_size = dWidth/(double)uWidth;
	m_pHdr->ycell_size = -dHeight/(double)uHeight;
	logTrace(FN_NAME " cellsize from 4 tiepoints: %.2f,%.2f",
				 m_pHdr->xcell_size,m_pHdr->ycell_size);
			    // it's only aligned if slant < 1 cell height
	if (fabs(PP[0].dY - PP[1].dY) < m_pHdr->ycell_size)
	    m_pHdr->bRegistered = TRUE;
	} // end of 4-tiepoints at corner
#undef PP
		    // record the first tiepoint as our reference point
    m_pHdr->img_x = m_pHdr->pModelTiepoints[0].uI;
    m_pHdr->img_y = m_pHdr->pModelTiepoints[0].uJ;
    m_pHdr->ref_x.v0 = m_pHdr->pModelTiepoints[0].dX;
    m_pHdr->ref_y.v0 = m_pHdr->pModelTiepoints[0].dY;
    m_pHdr->unitname = strdup("Meter");
    m_pHdr->georef_init = TRUE; // but maybe cellsize unknown
    return iStatus;
    }	  // end of geotiff tiepoints

int TiffImageReader::_getTiePoints(void * pgI,
				   int tiepoint_count, double * tiepoints, 
				   uint * puZone, char * pcZone,
				   BOOL bCellSizeCalcd)
    {
#undef FN_NAME
#define FN_NAME "int TiffImageReader::_getTiePoints"
    int iStatus = 0;
    GTIFDefn * pgInfo = (GTIFDefn *)pgI;
    double dLongitude = -200; // used to estimate UTM zone
    uint points_cnt = tiepoint_count / 6;
		    // copy them from TIFF to HDr
    iStatus = _copyTiePoints(tiepoint_count,tiepoints,
			     pcZone,&dLongitude);
    BOOL bAlreadyUTM = (iStatus > 0);
		    // try to get values from Proj4 built into libgeotiff
    double * pX = (double *)calloc(points_cnt,sizeof(double));
    double * pY = (double *)calloc(points_cnt,sizeof(double));
//    BOOL bSuccess = FALSE;
    if ((pX != NULL) && (pY != NULL))
        {
	for (uint j=0; j<points_cnt; j++)
	    {
	    pX[j] = tiepoints[j*6 + 3];
	    pY[j] = tiepoints[j*6 + 4];
	    }
	if (GTIFProj4FromLatLong(pgInfo,points_cnt,pX,pY))
	    {
	    for (uint j=0; j<points_cnt; j++)
	        {
		logTrace(FN_NAME " newmethod tiepoint %d mapped to %f,%f",
			 j,pX[j],pY[j]);	
		}
//	    bSuccess = TRUE;
	    }
	else // we get this a lot - should not be fatal
	    { logTrace(FN_NAME " GTIFProj4FromLatLong error %d points",points_cnt); }
	free(pX);
	free(pY);
	}
    if (*puZone == 0) // happens only if geotiff file missing info
        {
	if (dLongitude < 0)
	    {
	    dLongitude += 180;
	    *puZone = (uint)ceil(dLongitude / 6);
	    }
	else
	    *puZone = 30 + (uint)ceil(dLongitude / 6);
	}
//		    if (! bSuccess) // don't need to use Proj4 explicityl
//		    {
    if ((*puZone < 61) && (! bAlreadyUTM))
	iStatus = _getTiePointsFromProj4(*puZone);
    logTrace(FN_NAME " from proj4=%s uModelTiePoints=%d uZone=%d "
	     "longitude=%f cZone=%c bAlready=%s",
	     YESNO(iStatus==0),m_pHdr->uModelTiepoints,
	     *puZone,dLongitude,*pcZone,YESNO(bAlreadyUTM));
    // many files seem to have four tiepoints at the corners
			// e.g. SPOT
//		    }
    if (iStatus >= 0)
	iStatus = _recordFixedPointsAndPixelSize(tiepoint_count,
						 bCellSizeCalcd);
    return iStatus;
    }

	// init ImageHdr from file tags
	// @param pTif		open TIFF handle
	// @return		< 0 if err (missing or bad argument)
	//			-43 if unsupported format
int TiffImageReader::copyFields(void * pVTif)
    {
#undef FN_NAME
#define FN_NAME "TiffImageReader::copyFields"
    int iRetval = 0;
    GTIF * gtif = NULL; //GTIFNew(tif);
    TIFF * pTif = (TIFF *)pVTif;
    #define MAJOR 1
    #define MINOR 2
    /* first get some basic tags from TIFF */
    uint32 w, h;
    uint16 planar=0,bits=0,compress=0,samp_per_pix=0; 
    int16 iPhoto = -1;
    logTrace(FN_NAME " (en) of %s",m_pHdr->h_OriginalFileName);
    memset(m_pHdr,0,sizeof(IMAGEHDR));
    sprintf(m_pHdr->czFileType,"TIFF");
    // The following tests return 1 if the tag is included in
    // the file. If not, we set some defaults.
    if (TIFFGetField(pTif, TIFFTAG_IMAGEWIDTH, &w) != 1)
        {
	if (m_iDebug) printf("IMAGEWIDTH not defined\n");
	w = 0;
	}
    else if (m_iDebug) printf("IMAGEWIDTH = %ld\n",w);
    if (TIFFGetField(pTif, TIFFTAG_IMAGELENGTH, &h) != 1)
        {
	if (m_iDebug) printf("IMAGELENGTH not defined\n");
	h = 0;
	}
    else if (m_iDebug) printf("IMAGELENGTH = %ld\n",h);
    if (TIFFGetField(pTif, TIFFTAG_BITSPERSAMPLE, &bits) != 1)
        {
	if (m_iDebug) printf("BITSPERSAMPLE not defined\n");
	bits = 0;
	}
    else if (m_iDebug) printf("BITSPERSAMPLE = %d\n",bits);
    // according to spec 6.0, PLANAR is required
    // 1 => pixel-interleaved
    if (TIFFGetField(pTif, TIFFTAG_PLANARCONFIG, &planar) != 1 )
        {
	if (m_iDebug) printf("PLANARCONFIG not defined\n");
	planar = 0;
	}
    else 
	if (m_iDebug) 
	    printf("PLANARCONFIG = %d (2 => band-sequential)\n",planar);
    m_iPlanar = planar;
    // according to spec 6.0, PHOTO=5 is for multi-band (band-interleaved?)
    // but ERDAS uses PHOTO=1, PLANAR=1 for multiband pixel-interleaved
    // and somebody else uses PLANAR=2 multi-sample_per_pix
    if (TIFFGetField(pTif, TIFFTAG_PHOTOMETRIC, &iPhoto) != 1)
        {
	if (m_iDebug) printf("PHOTOMETRIC not defined\n");
	iPhoto = -1;
	}
    else 
	{
	if (m_iDebug) printf("PHOTOMETRIC = %d\n",iPhoto);
	m_iPhoto = iPhoto;
	}
    if (TIFFGetField(pTif, TIFFTAG_COMPRESSION, &compress) != 1)
        {
	if (m_iDebug) printf("COMPRESSION not defined\n");
	compress = 0;
	}
    else if (m_iDebug) 
        printf("COMPRESSION = %d\n",compress);
    if (TIFFGetField(pTif, TIFFTAG_SAMPLESPERPIXEL, &samp_per_pix) != 1)
        {
	if (m_iDebug) printf("SAMPLESPERPIXEL not defined\n");
	samp_per_pix = 1;
	}
    else if (m_iDebug) 
        printf("SAMPLESPERPIXEL = %d\n",samp_per_pix);

    if ((w == 0) || (h == 0) || (planar == 0) || (iPhoto < 0) 
	    || (bits == 0) || (compress == 0))
	iRetval = -100;
    else if (bits < 8)
	iRetval = -101;
//    else if (compress != 1)
//	iRetval = -102;

    // ~~~ ignore this error for the moment (Jan 2011)
    // we still get a usable image file
    // MassGIS files are marked as palette even though they aren't
//    else if (iPhoto == 3)
//	iRetval = -103;  // color mapped
    else if ((samp_per_pix < 3) && (samp_per_pix != 1))
	iRetval = -104;  // unusual number of bands
    else if ((samp_per_pix > 1) && (planar > 2)) 
	iRetval = -105;  // planar - "not much used" according to TIFF spec
    // ref: TIFF v 6 spec pp 37-39. planar==2 is strip offsets model, "not much used"
    //                              ==3 is paletter and ==4 is mask
    else
        {
	const char * pText = NULL;
	uint16 param;
//	size_t npixels; 
	/* first init the IMAGEFORMAT fields */
	m_pHdr->bBinary = TRUE;		/* FALSE => ASCII data */ 
	m_pHdr->bRectangular = TRUE;	/* FALSE => lines are different lens*/
	/* GeoEye files from USGS have format: iPhoto=2 samp_per_pix=4 bits/samp=16 */
	m_pHdr->uBands = m_pHdr->h_uOriginalBandCount = (iPhoto < 2) ? 1 
	    : ((iPhoto == 2) && (samp_per_pix <= 3)) ? 3 
	    : samp_per_pix;  /* how many bands in file */
	m_pHdr->ulPixelPitch = (iPhoto < 2) ? 1 
	    : ((iPhoto == 2) && (samp_per_pix <= 3)) ? 3 
	    : samp_per_pix; /* photo should = 5 */
	m_pHdr->ulLinePitch = (iPhoto < 2) ? w 
	    : ((iPhoto == 2) && (samp_per_pix <= 3)) ? w * 3 
	    : w * samp_per_pix;
	m_pHdr->uBandLayout = (iPhoto < 2) ? IMG_PACKED1 : IMG_PIL;
	// special for ERDAS
	if ((iPhoto == 1) && (planar == PLANARCONFIG_CONTIG /* 1 */ ) 
	         && (samp_per_pix >= 3)) 
	     //~~ was >3 before 25Sept2007 - Samples from DeptNatParks req >= 3
	    {
	    m_pHdr->uBands = m_pHdr->h_uOriginalBandCount
		= samp_per_pix;  /* how many bands in file */
	    m_pHdr->ulPixelPitch = samp_per_pix; /* photo should = 5 */
	    m_pHdr->ulLinePitch = w * samp_per_pix;
	    m_pHdr->uBandLayout = IMG_PACKED1;
	    }
	// special for ??
	else if ((planar == PLANARCONFIG_SEPARATE /* 2 */ ) && (samp_per_pix > 1))
	    {
	    m_pHdr->uBands = m_pHdr->h_uOriginalBandCount
		= samp_per_pix;  /* how many bands in file */
	    m_pHdr->ulPixelPitch = 1;
	    m_pHdr->ulLinePitch = w;
	    m_pHdr->uBandLayout = IMG_BSQ;
	    }
	m_pHdr->ulDataOffset = 0;	/* bytes from start of file to image */
	m_pHdr->ulDataSize = 0;		/* bytes of image data; 0 => unknown */
	m_pHdr->ulBandPitch = 0;	/* bytes from one band to the next */
	pText = TIFFGetVersion();
//	printf("version=%p = '%s'\n",pText,(pText == NULL) ? "" : pText);
	strcpy_array(m_pHdr->czFileType,"TIFF");
	if (pText != NULL)
	    { strcpy_array(m_pHdr->czFileType,pText); }

	strcpy_array(m_pHdr->ftype,"I"); /* assume TIFF always Image */
	m_pHdr->size[0] 	= h;
	m_pHdr->size[1] 	= w;
	m_pHdr->bits_per_pix = bits;
	m_pHdr->uEncoding 	= 'SR';
	m_pHdr->iff_offset 	= 0;
	m_pHdr->uKey 	= 0;
	if (m_pHdr->bits_per_pix > 8)
            {
	    m_pHdr->ulPixelPitch *= (bits+7) / 8; /* probably 16-bits / pix */
	    m_pHdr->ulLinePitch *= (bits+7) / 8;
	    }
	m_pHdr->ulDataSize = (ulong)m_pHdr->size[0] * m_pHdr->ulLinePitch;
	m_pHdr->bImageHdrInitialized = TRUE;

	m_pHdr->source = strdup("IMP");
	    /* next copy or derive the DESCRIPTION fields */
	if (TIFFGetField(pTif, TIFFTAG_IMAGEDESCRIPTION, &pText) == 1)
	    m_pHdr->comment = strdup(pText);
	if (TIFFGetField(pTif, TIFFTAG_DOCUMENTNAME, &pText) == 1)
	    m_pHdr->scene = strdup(pText);
	if (TIFFGetField(pTif, TIFFTAG_PAGENAME, &pText) == 1)
	    m_pHdr->subscene = strdup(pText);
	if (TIFFGetField(pTif, TIFFTAG_DATETIME, &pText) == 1)
	    m_pHdr->czDateTime = strdup(pText);
/*
    m_pHdr->h_title = strdup(pSrcHdr->fields.fname); // use name for title
    // m_pHdr->h_id = ;		// no ID on old ones
    m_pHdr->source = strdup(pSrcHdr->fields.source+1);
    m_pHdr->scene = strdup(pSrcHdr->fields.scene+1);
    m_pHdr->subscene = strdup(pSrcHdr->fields.subscene+1);
    m_pHdr->band = strdup(pSrcHdr->fields.band+1);
*/
	m_pHdr->bImageHdrDescriptionInit = TRUE;
	    /* next copy or derive the STATS */
#if DRAGON_VER >= 6
	if (TIFFGetField(pTif, TIFFTAG_MINSAMPLEVALUE, &param) == 1)
	    m_pHdr->m_ihImgmin 	= param;
	if (TIFFGetField(pTif, TIFFTAG_MAXSAMPLEVALUE, &param) == 1)
	    m_pHdr->m_ihImgmax 	= param;
#else
	if (TIFFGetField(pTif, TIFFTAG_MINSAMPLEVALUE, &param) == 1)
	    m_pHdr->imgmin 	= param;
	if (TIFFGetField(pTif, TIFFTAG_MAXSAMPLEVALUE, &param) == 1)
	    m_pHdr->imgmax 	= param;
#endif
	m_pHdr->bImageHdrStatsInit = TRUE; //~~~ OK even without mean etc?

	gtif = GTIFNew(pTif);
	if (gtif == NULL)
	    {
	    m_pHdr->bModelPixelScaleInit = FALSE;
	    m_pHdr->xcell_size = 1;
	    m_pHdr->ycell_size = 1;
	    m_pHdr->georef_init = FALSE;
	    }
	else
	    {
	    int versions[3];
	    int iStatus = 0;
	    geocode_t model;
	    GTIFDefn gInfo;
	    GTIFDirectoryInfo(gtif,versions,0);
	    sprintf(m_pHdr->czFileType,"GEOTIFF v %d.%d",
		    versions[MAJOR],versions[MINOR]);
	    iStatus = GTIFGetDefn(gtif,&gInfo);
	    logTrace(FN_NAME " GTIFGetDefn returns %s version %d.%d.%d "
		     "ProjCode=%d Projection=%d zone=%d datum=%d "
		     "lengthunits=%d",
		     YESNO(iStatus),
		     versions[0],versions[1],versions[2],
		     gInfo.ProjCode,gInfo.Projection,
		     gInfo.Zone,gInfo.Datum,gInfo.UOMLength);
	    // get the non-Geotiff-registered tags
	    int	tiepoint_count=0, pixelscale_count=0;
	    double 	*tiepoints = NULL;
	    double	*pixel_scale = NULL;
	    BOOL bCellSizeCalcd = FALSE;
	    char 	cZone = '\0'; // UTM S or N or undef
	    uint 	uZone = 0;
	        
	        // get the pixel size
		// ModelPixelScaleTag - Softdesk -  spec 2.6.1
	    if((gtif->gt_methods.get)(pTif, TIFFTAG_GEOPIXELSCALE,
				      &pixelscale_count,&pixel_scale) != 1)
		pixelscale_count = 0;

		// alos samples have this 
	    else if (pixelscale_count == 3)   
	        { /* GEOTiff spec says this also implies >= 1 tiept */
		for (int j=0; j<pixelscale_count; j++)
		    m_pHdr->dModelPixelScale[j] = pixel_scale[j];
		m_pHdr->bModelPixelScaleInit = TRUE;
		m_pHdr->xcell_size = pixel_scale[0];
		m_pHdr->ycell_size = -pixel_scale[1];
		m_pHdr->georef_init = TRUE;
		bCellSizeCalcd = TRUE; // suppress four-corners calcs
		logTrace(FN_NAME " cellsize from GEOPIXELSCALE: %.2f,%.2f",
			 m_pHdr->xcell_size,m_pHdr->ycell_size);
		}
	    // ModelTiepointTag - Intergraph
	    if((gtif->gt_methods.get)(pTif, TIFFTAG_GEOTIEPOINTS,
				      &tiepoint_count,&tiepoints) != 1)
		tiepoint_count = 0;
	    logTrace(FN_NAME " pixelscale_count=%d tiepoint_count=%d",
		     pixelscale_count,tiepoint_count);

	    iStatus = GTIFKeyGet(gtif,GTModelTypeGeoKey,&model,0,1);
	    if (iStatus == 0) /* ignore geotiff stuff */
	        {
		logTrace(FN_NAME " GTIFKeyGet of model %s",YESNO(iStatus));
		iRetval = DERR_UNKNOWN_GEOREF; // non-fatal
	        }
	    else if (versions[MAJOR] > 1) /* else ignore geotiff stuff */
		{
		logTrace(FN_NAME " GTIFKeyGet of model version=%d",
			 versions[MAJOR]);
		iRetval = DERR_UNKNOWN_GEOREF; // non-fatal
	        }
	    else
	        {
		int 	transform_count=0;
//		int 	param;
		double 	*transform   = NULL;
		// deal with linear unit name
		m_pHdr->uProjectedLinearUnits = gInfo.UOMLength;
		const char * pUN = GTIFValueName(ProjLinearUnitsGeoKey,
						     gInfo.UOMLength);
		logTrace(FN_NAME " ProjLinearUnits=%d=|%s|",
			 gInfo.UOMLength,pUN);
		if ((m_pHdr->unitname == NULL)
		    && (strstr(pUN,"Unknown") == NULL))
		    {
		    if ((pUN != NULL) 
			&& (strcasecmp(pUN,"linear_meter") == 0))
			m_pHdr->unitname = strdup("Meter");
		    else
			m_pHdr->unitname = strdup(pUN);
			//= strdup(GTIFValueName(ProjLinearUnitsGeoKey,param));
		    }
		// see if we have a recognized projection and datum
		// ~~~ currently only WGS 84
		uZone = (gInfo.Zone < 61) ? gInfo.Zone : 0;  // UTM zone
		m_pHdr->uProjectionGeo = gInfo.ProjCode;
		if ((gInfo.ProjCode >= 16000) && (gInfo.ProjCode < 16099))
		    {
		    cZone = 'N';
		    }
		else if ((gInfo.ProjCode >= 16100) && (gInfo.ProjCode < 16199))
		    {
		    cZone = 'S';
		    }
		else
		    iRetval = DERR_UNKNOWN_GEOREF; // non-fatal
		    
		if ((cZone && (tiepoint_count == 6)) // > 6 => not registered
		    && (iRetval == DERR_OK))
		    m_pHdr->bRegistered = TRUE;
		logTrace(FN_NAME 
			 " registered? %s uZone=%d cZone=%c projcode=%d",
			 YESNO(m_pHdr->bRegistered),
			 uZone,cZone,gInfo.ProjCode);
		m_pHdr->bImageHdrProjectionInit = TRUE;

		char * pczProjCode
		    = strdup(GTIFValueName(ProjectedCSTypeGeoKey,
						gInfo.ProjCode));
		char * pczProjection
		    = strdup(GTIFValueName(ProjectionGeoKey,
						gInfo.Projection));
		char * pczProjCode2
		    = strdup(GTIFValueName(ProjectionGeoKey,
						gInfo.ProjCode));
		char * pczProjection2
		    = strdup(GTIFValueName(ProjectedCSTypeGeoKey,
						gInfo.Projection));
		logTrace(FN_NAME " based on GTIFGetDefn "
			 "zone=%d%c length=%s proj='%s','%s',(*)'%s','%s'",
			 uZone,cZone,m_pHdr->unitname,
			 pczProjCode,pczProjection,
			 pczProjCode2,pczProjection2);
		if(GTIFKeyGet(gtif,ProjCoordTransGeoKey,&param,0,1))
		    {
		    m_pHdr->uProjectionCoordTrans = param;
		    logTrace(FN_NAME " ProjCoordTrans=%s (%d)",
			     GTIFValueName(ProjCoordTransGeoKey,param),param);
		    }
		if(GTIFKeyGet(gtif,GeographicTypeGeoKey,&param,0,1))
		    {
		    m_pHdr->uGeographicType = param;
		    logTrace(FN_NAME " GeographicType=%s (%d)",
			     GTIFValueName(GeographicTypeGeoKey,param),param);
		    }
		if(GTIFKeyGet(gtif,GeogGeodeticDatumGeoKey,&param,0,1))
		    {
		    m_pHdr->uGeodeticDatum = param;
		    logTrace(FN_NAME " GeogGeodeticDatum=%d",
			     GTIFValueName(GeogGeodeticDatumGeoKey,param));
		    }
		if(GTIFKeyGet(gtif,GeogPrimeMeridianGeoKey,&param,0,1))
		    {
		    m_pHdr->uGeographicPrimeMeridian = param;
		    logTrace(FN_NAME " GeographicPrimeMeridian=%d",
			     GTIFValueName(GeogPrimeMeridianGeoKey,param));
		    }
		if((gtif->gt_methods.get)(pTif, TIFFTAG_GEOTRANSMATRIX,
			      &transform_count,&transform) != 1)
		    transform_count = 0;
		if (transform_count == 16)
		    {
		    for (int j=0; j<transform_count; j++)
			m_pHdr->dModelTransformation[j] = transform[j];
		    m_pHdr->bModelTransformInit = TRUE;
		    }
		m_pHdr->uModelType = model; /* 1=unregistered 2=registered */
		if(GTIFKeyGet(gtif,GTRasterTypeGeoKey,&param,0,1))
		    m_pHdr->uRasterType = param; /* 1=area 2=point */
		if(GTIFKeyGet(gtif,ProjectedCSTypeGeoKey,&param,0,1))
		    m_pHdr->uProjectedCSType = param;
/*
		else if(GTIFKeyGet(gtif,GeogAngularUnitsGeoKey,&param,0,1))
		    {
		    m_pHdr->uGeoAngularUnits = param;
		    m_pHdr->unitname 
			= strdup(GTIFValueName(GeogAngularUnitsGeoKey,param));
		    }
*/
		if(GTIFKeyGet(gtif,VerticalCSTypeGeoKey,&param,0,1))
		    m_pHdr->uVerticalType = param;
		if(GTIFKeyGet(gtif,VerticalUnitsGeoKey,&param,0,1)
		   && (param != 0)) /* undefined */
		    {
		    m_pHdr->uVerticalUnits = param;
		    m_pHdr->z_scale = 1.0;
		    m_pHdr->z_offset = 0.0;
		    m_pHdr->z_unit
			= strdup(GTIFValueName(VerticalUnitsGeoKey,param));
		    m_pHdr->bImageHdrScalingInit = TRUE;
//		    printf("tiffImageReader setting vertical param=%d z_Unit='%s'\n",param,m_pHdr->z_unit);
		    }
		} // end of good geotiff processing

	    // This is independent of GeoTIFF, but uses uZone, cZone
	    // from GeoTIFF processing if found
	    if (tiepoint_count >= 6)// are there any? (six per actual set)
		iStatus = _getTiePoints(&gInfo,tiepoint_count,tiepoints, 
					&uZone, &cZone, bCellSizeCalcd);
	    if (cZone && (uZone > 0) && m_pHdr->bRegistered)
	        {
		char czZone[4];
		snprintf(czZone,sizeof(czZone),"%d%c",uZone,cZone);
		m_pHdr->czUTMZone = strdup(czZone);
		}
	    if (m_iDebug > 1)
		GTIFPrint(gtif,NULL,NULL);
	    GTIFFree(gtif);
	    }
	}
    logTrace(FN_NAME " (ex) returns %d",iRetval);
    return iRetval;
    }

	// return a formatted dump of the class member
	// call with detail == 1 before file has been read
	// Need to add the other tag values here also. Someday ...
const char * TiffImageReader::dump(int detail, 
					const char * czTitle) const
    {
#undef FN_NAME
#define FN_NAME "TiffImageReader::dump"
    s_czDumpBuf[0] = '\0';
    if (detail == 1)
	snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),FN_NAME "TiffImageReader");
    else if (detail == 2)
	{
	const char * pczPhotoTag = getAuxInfo("PHOTOMETRIC");
	const char * pczPlanarTag = getAuxInfo("PLANARCONFIG");
	snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	         FN_NAME "TiffImageReader PhotometricInterpretation=%s PlanarConfig=%s",
	         NN(pczPhotoTag),NN(pczPlanarTag));
	}
    return s_czDumpBuf;
    }

void TIFF_RDR_END() { puts(FIL_ID); }
