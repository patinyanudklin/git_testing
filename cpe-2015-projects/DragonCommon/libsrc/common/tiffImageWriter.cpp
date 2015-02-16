#include "drelease.h"
char TIFFIMAGEWRTR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.24 $$Date: 2014/04/01 07:22:21 $";
D_REL_IDSTR;

/*
 *	filename tiffImageWriter.cpp
 *		$Revision: 1.24 $ $Date: 2014/04/01 07:22:21 $	
 *
 *      ~~ Copyright 2010-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: tiffImageWriter.cpp,v 1.24 2014/04/01 07:22:21 rudahl Exp $
 *   $Log: tiffImageWriter.cpp,v $
 *   Revision 1.24  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.23  2014/01/25 05:48:40  rudahl
 *   add geotiff fields to header
 *
 *   Revision 1.22  2011/02/27 08:24:51  rudahl
 *   final work on tiff IO
 *
 *   Revision 1.21  2011/01/31 02:12:50  rudahl
 *   working on geotiff in tiff export
 *
 *   Revision 1.20  2011/01/03 07:08:21  rudahl
 *   regressing to libtiff 3.7
 *
 *   Revision 1.19  2011/01/03 06:29:32  rudahl
 *   mostly non-libtiff now
 *
 *   Revision 1.18  2011/01/02 11:38:47  rudahl
 *   it sort-of works for single-band images
 *
 *   Revision 1.17  2010/12/29 00:40:48  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.16  2010/12/29 00:11:20  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.15  2010/12/28 23:30:10  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.14  2010/12/28 23:24:01  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.13  2010/12/28 21:06:28  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.12  2010/12/28 04:38:11  rudahl
 *   tracing
 *
 *   Revision 1.11  2010/12/28 09:45:22  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.10  2010/12/28 07:37:24  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.9  2010/12/27 09:17:11  rudahl
 *   trying to get the tags right
 *
 *   Revision 1.8  2010/12/27 06:33:04  rudahl
 *   changed date fmt
 *
 *   Revision 1.7  2010/12/27 06:10:40  rudahl
 *   typo
 *
 *   Revision 1.6  2010/12/27 05:57:41  rudahl
 *   added compression, number of rows
 *
 *   Revision 1.5  2010/12/27 04:29:39  rudahl
 *   added writedirectory
 *
 *   Revision 1.4  2010/12/27 02:37:01  rudahl
 *   working on tiff generation
 *
 *   Revision 1.3  2010/12/25 05:17:00  rudahl
 *   work on tiffwriter
 *
 *   Revision 1.2  2010/12/24 08:57:08  rudahl
 *   integrate the tiffWriter into the build
 *
 *   Revision 1.1  2010/12/19 06:39:09  rudahl
 *   not yet compilable
 *
 *
 ****************************************************************
 * 
 * Define a class for writing new Tiff image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 6.1	2010-12-18 ktr	created
 * 6.4	2014-01-24 ktr	copy geotiff fields to GEOTIFF section of header
 */

/* DOCS:
 * Unlike the standard imageWriter, this subclass can write multi-band
 * files, as follows:
 *   1. create class as usual
 *   2. call writeHeader, with the IMAGEHDR pHdr pointing to a header
 *	which matches any one of the source files, but changed so that
 *	pHdr->band is interpreted as the NUMBER of bands.
 *	Also, ftype[2] may = "R" for RGB sequence or "B" for BGR sequence
 *	All other params which might differ among the component files
 *	are either ignored or assumed to be the same for all
 *   3. for each line of {all files|each file} call ...
 *   4. close
 * if pHdr->band' == 1 or 0, assume a single-band file
 */

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <math.h>
#include <unistd.h>

//#include "dtypes.h"  // this must preceed tiffio.h for libtiff 3.9

#include "tiffio.h"
//#ifdef GTIF
#include "xtiffio.h"
#include "geotiffio.h"
#include "geo_tiffp.h"
#include "geo_keyp.h"
// #endif //#ifdef GTIF

#include "dtypes.h"  // this must follow tiffio.h for libtiff 3.7
#include "dlimits.h"  /* for strcpy_array */
#include "files.h"
#include "dragon-errors.h"
#include "wfutil.h"
#include "ob.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "dragonHd.h"
#include "imageWriter.h"
#include "tiffImageWriter.h"

static Class TiffImageWrtr_class("TiffImageWriter",
				 "Class for writing new Tiff image files");

// write the keys using setTag
// return 1 if OK, 0 if error
static int _WriteGTIFKeys(GTIF *gt,uint uDirEndOffset);

//const char * TiffImageWriter::s_czTrailerNames[] = {TRAILER_RECORD_NAMES};

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
TiffImageWriter::TiffImageWriter(int iDebug, int iTrace)
    {
    m_pClass = &TiffImageWrtr_class; 
    m_pClass->setSubClass(ImageWriter::getObjectClass());
    if (iDebug > m_iDebug)
      m_iDebug = iDebug;
    if (iTrace > m_iTrace)
      m_iTrace = iTrace;
    if (m_iDebug)
	fprintf(stderr,"TiffImageWriter constructor\n");
    logTrace("tiffImageWriter ctor $Revision: 1.24 $$Date: 2014/04/01 07:22:21 $");
    m_uHeaderChecksum = 0;
    m_pHdr = NULL;
    }

// arranged in ascending index, first the scalars then the arrays
static struct myTag 
	{
	uint16	tag;
	uint16	type;
	uint32	count;
	int32  	iDefault;		// -1 => no default or array
	}
tags[] = {
// 	{ TIFFTAG_SUBFILETYPE,		TIFF_LONG,1,	 0 },
	{ TIFFTAG_IMAGEWIDTH,		TIFF_SHORT,1,	-1 },
	{ TIFFTAG_IMAGELENGTH,		TIFF_SHORT,1,	-1  },
	{ TIFFTAG_BITSPERSAMPLE,	TIFF_SHORT,1,	8  },
	{ TIFFTAG_COMPRESSION,		TIFF_SHORT,1,	COMPRESSION_NONE  },
	{ TIFFTAG_PHOTOMETRIC,		TIFF_SHORT,1,	PHOTOMETRIC_MINISBLACK},
//	{ TIFFTAG_THRESHHOLDING,	TIFF_SHORT,1,	-1  },

//	{ TIFFTAG_DOCUMENTNAME,		TIFF_ASCII,1, -1 },
//	{ TIFFTAG_IMAGEDESCRIPTION,	TIFF_ASCII,1, -1 },
//	{ TIFFTAG_MAKE,			TIFF_ASCII,1, -1 },
//	{ TIFFTAG_MODEL,		TIFF_ASCII,1, -1 },
	{ TIFFTAG_STRIPOFFSETS,		TIFF_LONG,1,	-1  },
	{ TIFFTAG_ORIENTATION,		TIFF_SHORT,1,	ORIENTATION_TOPLEFT },
	{ TIFFTAG_SAMPLESPERPIXEL,	TIFF_SHORT,1,	1  },
	{ TIFFTAG_ROWSPERSTRIP,		TIFF_SHORT,1,	-1  },
	{ TIFFTAG_STRIPBYTECOUNTS,	TIFF_LONG,1,	-1  },
//	{ TIFFTAG_MINSAMPLEVALUE,	TIFF_SHORT,1,	-1  },
//	{ TIFFTAG_MAXSAMPLEVALUE,	TIFF_SHORT,1,	-1  },
//	{ TIFFTAG_XRESOLUTION,		TIFF_RATIONAL,1,	1  },
//	{ TIFFTAG_YRESOLUTION,		TIFF_RATIONAL,1,	1  },
	{ TIFFTAG_PLANARCONFIG,		TIFF_SHORT,1,	PLANARCONFIG_CONTIG},

//	{ TIFFTAG_PAGENAME,		TIFF_ASCII,1, -1 },
//	{ TIFFTAG_XPOSITION,		TIFF_RATIONAL,1,-1 },
//	{ TIFFTAG_YPOSITION,		TIFF_RATIONAL,1,-1 },
//	{ TIFFTAG_RESOLUTIONUNIT,	TIFF_SHORT,1, -1 },
	{ TIFFTAG_SOFTWARE,		TIFF_ASCII,1, -1 },
	{ TIFFTAG_DATETIME,		TIFF_ASCII,1, -1 },
//#ifdef GTIF
	{ TIFFTAG_GEOPIXELSCALE,	TIFF_DOUBLE,1, -1 },
	{ TIFFTAG_GEOTIEPOINTS,		TIFF_DOUBLE,1, -1 },
	{ TIFFTAG_GEOTRANSMATRIX,	TIFF_DOUBLE,1, -1 },
//#endif // #ifdef GTIF
	{ TIFFTAG_GEOKEYDIRECTORY,	TIFF_SHORT,1, -1 },
//#ifdef GTIF
	{ TIFFTAG_GEODOUBLEPARAMS,	TIFF_DOUBLE,1, -1 },
	{ TIFFTAG_GEOASCIIPARAMS,	TIFF_ASCII,1, -1 },
//#endif
};

void _tagsDump(const char * pczTitle)
    {
    char outbuf[4096];
    outbuf[0] = '\0';
    for (uint j=0; j<AY_COUNT(tags); j++)
	{
	snprintf(outbuf+strlen(outbuf),sizeof(outbuf)-strlen(outbuf),
		  "    %d: tag=%d type=%d count=%ld default=%ld=x%lX\n\t",
		  j,tags[j].tag,tags[j].type,tags[j].count,
		  tags[j].iDefault,tags[j].iDefault);
	byte * pTag = (byte *) &tags[j];
	for (int jj=0; jj<12; jj++)
	    {
	    snprintf(outbuf+strlen(outbuf),sizeof(outbuf)-strlen(outbuf),
		      "%02X ",pTag[jj]);
	    }
	snprintf(outbuf+strlen(outbuf),sizeof(outbuf)-strlen(outbuf),"\n");
	}
    logTrace("%s\n%s",pczTitle,outbuf);
    }

enum taglist 
{
//	_SUBFILETYPE,
	_IMAGEWIDTH,	
	_IMAGELENGTH,	
	_BITSPERSAMPLE,	
	_COMPRESSION,	
	_PHOTOMETRIC,	
//	_THRESHHOLDING,	

//	_DOCUMENTNAME,	
//	_IMAGEDESCRIPTION,
//	_MAKE,	
//	_MODEL,	
	_STRIPOFFSETS,	
	_ORIENTATION,	
	_SAMPLESPERPIXEL,
	_ROWSPERSTRIP,	
	_STRIPBYTECOUNTS,
//	_MINSAMPLEVALUE,
//	_MAXSAMPLEVALUE,
//	_XRESOLUTION,	
//	_YRESOLUTION,	
	_PLANARCONFIG,	

//	_PAGENAME,
//	_XPOSITION,
//	_YPOSITION,
//	_RESOLUTIONUNIT,
	_SOFTWARE,
	_DATETIME,
//#ifdef GTIF
	_GEOPIXELSCALE,		/* 33550 */
/* tags 33920-33922 are private tags registered to Intergraph, Inc */
	_GEOTIEPOINTS,    	/* 33922 */
/* tags 34263-34264 are private tags registered to NASA-JPL Carto Group */
	_GEOTRANSMATRIX,  	/* 34264 */
/* tags 34735-3438 are private tags registered to SPOT Image, Inc */
//#endif
	_GEOKEYDIRECTORY,  	/* 34735 */
	_GEODOUBLEPARAMS,     	/* 34736 */
	_GEOASCIIPARAMS,      	/* 34737 */
};

static byte s_uDataBuf[2048];
/* set one of the above tags
 * @param uIFDend	file offset where s_uDataBuf will be written
 * @param uTabNo	which tag
 * @param uDataType	TIFF_SHORT, TIFF_LONG, TIFF_ASCII, TIFF_DOUBLE (array)
 * @param uCount	how many elements, or length of string. 
 *			if ==1, set as scalar
 *			else put values into s_uDataBuf
 * @param pData		point to array of appropriate type
 * @return		< 0 => error (invalid tag id)
 *			> 0 is current size of data in s_uDataBuf
 */
static int setTag(uint uIFDend,uint uTagNo,uint uDataType,
		  uint uCount,const void * pData)
    {
    static byte * pNext = s_uDataBuf;
    int iStatus = 0;
    int iOffset = (int)(uIFDend + (pNext - s_uDataBuf));
    logTrace("setTag (en) tag=%d of %d (tag %d at %p) count=%d data at %p => %d=x%X",
	     uTagNo,AY_COUNT(tags),tags[uTagNo].tag,&tags[uTagNo],uCount,pData,
	     iOffset,iOffset);
    if (uTagNo > AY_COUNT(tags))
	return -1;
    tags[uTagNo].count = uCount;
    // scalars
    if ((uDataType == TIFF_SHORT) && (uCount == 1))
	tags[uTagNo].iDefault = *(uint16 *)pData;
    else if ((uDataType == TIFF_LONG) && (uCount == 1))
	tags[uTagNo].iDefault = *(uint32 *)pData;
    // arrays
    else if (uDataType == TIFF_ASCII)
        {
	tags[uTagNo].iDefault = iOffset;
	tags[uTagNo].count = uCount;
	strcpy((char *)pNext,(const char *)pData);
	pNext += 1+strlen((char *)pData);
	if ((pNext-s_uDataBuf) & 1)
	    * pNext++ = '\0';
        }
    else if (uDataType == TIFF_SHORT)
        {
	tags[uTagNo].iDefault = iOffset;
	tags[uTagNo].count = uCount;
	uint16 * pInData = (uint16 *) pData;
	uint16 * pOutData = (uint16 *) pNext;
	for (uint j=0; j<uCount; j++)
	    {
	    *pOutData++ = *pInData++;
	    }
	pNext = (byte *) pOutData;
        }
    else if (uDataType == TIFF_LONG)
        {
	tags[uTagNo].iDefault = iOffset;
	tags[uTagNo].count = uCount;
	uint32 * pInData = (uint32 *) pData;
	uint32 * pOutData = (uint32 *) pNext;
	for (uint j=0; j<uCount; j++)
	    {
	    *pOutData++ = *pInData++;
	    }
	pNext = (byte *) pOutData;
        }
    else if (uDataType == TIFF_DOUBLE)
        {
	tags[uTagNo].iDefault = iOffset;
	tags[uTagNo].count = uCount;
	double * pInData = (double *) pData;
	double * pOutData = (double *) pNext;
	for (uint j=0; j<uCount; j++)
	    {
	    *pOutData++ = *pInData++;
	    }
	pNext = (byte *) pOutData;
        }
    iOffset = (int)(uIFDend + (pNext - s_uDataBuf));
    logTrace("setTag (ex) new offset= %d=x%X",iOffset,iOffset);
    return (iStatus >= 0) ? pNext - s_uDataBuf : iStatus;
    }

// create the IFD
// ulImageDataSize should be either 
//    the bytes of image data (rounded up to mult of 4) if IFD is at END
//    or 0 if IFD is at beginning
// return size of tags aux buffer (in bytes) or 0 if error
int TiffImageWriter::createIFD(void * p,
			       const IMAGEHDR * pSrcHdr,
			       int * pErrNum, 
			       ulong ulImageDataSize)
    {
#undef FN_NAME
#define FN_NAME "TiffImageWriter::createIFD"
    m_iTagBufLen = 0;	    // only need iTagBufLen on final ones
    TIFF * pTif = (TIFF *) p;
    GTIF * pGtif = NULL;
    BOOL bMapScale = ((fabs(pSrcHdr->ref_x.v0) > 0.0001)
		      && (fabs(pSrcHdr->ref_y.v0) > 0.0001)
		      && (fabs(pSrcHdr->xcell_size) > 0.0001)
		      && (fabs(pSrcHdr->ycell_size) > 0.0001));

//	pinfo_t *data;
//	if (!(pGtif->gt_methods.get)(pTif, GTIFF_GEOKEYDIRECTORY, &pGtif->gt_nshorts, &data ))
//	    printf("geokeydirectory not found\n");

//#endif // #ifdef GTIF
//	int fd = TIFFFileno(pTif);
    int iStat = 0;
    char czDateTime[100];
    time_t now = time(NULL);
    struct tm * tm = localtime(&now);
    if (! pSrcHdr->bImageHdrInitialized)
	iStat = DERR_IMAGE_UNINIT;
    else
	{
	strftime(czDateTime,sizeof(czDateTime),"%Y:%m:%d %H:%M:%S",tm);
	char czSoftware[] = D_PRODUCT " " D_MAJOR D_MINOR;
	uint uBytesPerPix = (pSrcHdr->bits_per_pix > 8) ? 2 : 1;
	uint32 ulStripByteCount 
	    = pSrcHdr->size[0]*pSrcHdr->size[1]*uBytesPerPix;
	int iBands = (pSrcHdr->band != NULL) ? atoi(pSrcHdr->band) : 1;
	
	uint uDirEndOffset = 14+sizeof(tags)+ulImageDataSize;
	int iPlanarConfig = PLANARCONFIG_CONTIG;
	int iPhotometric = PHOTOMETRIC_MINISBLACK;
	
	logTrace(FN_NAME " %d bands (%s) %d wide by %d high "
		 "stripbytecount=%ld bitsperpix=%d",
		     iBands,pSrcHdr->band,pSrcHdr->size[1],pSrcHdr->size[0],
		     ulStripByteCount,pSrcHdr->bits_per_pix);
//#define THEIRSTYLE 1
#ifdef THEIRSTYLE
	if (TIFFSetField(pTif, TIFFTAG_IMAGEWIDTH, pSrcHdr->size[1]) == 0)
	    iStat = -101;
	else if (TIFFSetField(pTif, TIFFTAG_IMAGELENGTH, pSrcHdr->size[0]) == 0)
	    iStat = -102;
	else if (TIFFSetField(pTif, TIFFTAG_ROWSPERSTRIP, pSrcHdr->size[0]) == 0)
	    iStat = -103;
	else if (TIFFSetField(pTif, TIFFTAG_SAMPLESPERPIXEL,&iBands) == 0)
	    iStat = -104;
	    else if (TIFFSetField(pTif, TIFFTAG_BITSPERSAMPLE,pSrcHdr->bits_per_pix) == 0)
	    iStat = -105;
	    // according to spec 6.0, PLANAR is required
	    // 1 => pixel-interleaved
	else if (TIFFSetField(pTif, TIFFTAG_COMPRESSION,COMPRESSION_NONE) == 0)
	    iStat = -106;
	else if (TIFFSetField(pTif, TIFFTAG_IMAGEDESCRIPTION,pSrcHdr->comment) == 0)
	    iStat = -107;
	else if (TIFFSetField(pTif, TIFFTAG_ORIENTATION,ORIENTATION_TOPLEFT) == 0)
	    iStat = -108;
	else if (TIFFSetField(pTif, TIFFTAG_XRESOLUTION,1) == 0)
	    iStat = -109; // 1 => N/A
	else if (TIFFSetField(pTif, TIFFTAG_YRESOLUTION,1) == 0)
	    iStat = -110; // 1 => N/A
	else if (TIFFSetField(pTif, TIFFTAG_SOFTWARE,D_PRODUCT) == 0)
	    iStat = -111;
	else if (TIFFSetField(pTif, TIFFTAG_DATETIME,czDateTime) == 0)
	    iStat = -112;
	    else if (TIFFSetField(pTif, TIFFTAG_SAMPLEFORMAT,SAMPLEFORMAT_UINT) == 0)
		iStat = -113;
// maps are 256 ushorts
//    TIFFSetField(pTif, TIFFTAG_COLORMAP,redMap.GreenMap.blueMap);
	if (iStat < 0)
	{
	}
	else if (iBands < 2) // band is used here as the number of bands
	    {
	    if (TIFFSetField(pTif, TIFFTAG_PLANARCONFIG,PLANARCONFIG_CONTIG) == 0)
	    iStat = -114;
		// according to spec 6.0, PHOTO=5 (separated) is for multi-band 
		// (band-interleaved?)
		// but ERDAS uses PHOTO=1, PLANAR=1 for multiband pixel-interleaved
		// and somebody else uses PLANAR=2 multi-sample_per_pix
	    else if (TIFFSetField(pTif, TIFFTAG_PHOTOMETRIC,PHOTOMETRIC_MINISBLACK) == 0)
	    iStat = -115;
	    else if (TIFFSetField(pTif,TIFFTAG_STRIPBYTECOUNTS,&ulStripByteCount) == 0)
	    iStat = -116;
	    }
	else // this one writes band-sequential
	    {
	    uint16 * puBitsPerSample 
		= (uint16 *) calloc(iBands,sizeof(uint16));
	    uint32 * puStripByteCount 
		= (uint32 *) calloc(iBands,sizeof(uint32));
	    if ((puBitsPerSample == NULL) || (puStripByteCount == NULL))
		return DERR_MEM_ALLOC;

	    for (int j=0; j<iBands; j++)
		{
		puBitsPerSample[j] = 8;
		puStripByteCount[j] = ulStripByteCount;
		}
	    if (TIFFSetField(pTif, TIFFTAG_PLANARCONFIG,PLANARCONFIG_SEPARATE) == 0)
	    iStat = -117;
	    else if (TIFFSetField(pTif, TIFFTAG_PHOTOMETRIC,PHOTOMETRIC_RGB) == 0)
	    iStat = -118;
	    else if (TIFFSetField(pTif,TIFFTAG_STRIPBYTECOUNTS,puStripByteCount) == 0)
	    iStat = -119;
//		TIFFSetField(pTif, TIFFTAG_PHOTOMETRIC,PHOTOMETRIC_SEPARATED);
	    }
	XTIFFClose(pTif);	/* save and close the TIFF file descr - void fn */
//	    }
#else // #ifdef THEIRSTYLE

	if (iBands < 2) // band is used here as the number of bands
	    {	// this is the default - nothing to set
	    uint16 uBitsPerSample = uBytesPerPix * 8;
	    setTag(uDirEndOffset,_BITSPERSAMPLE,TIFF_SHORT,
		       1,&uBitsPerSample);
	    setTag(uDirEndOffset,_STRIPBYTECOUNTS,TIFF_LONG,
		       1,&ulStripByteCount);
	    }
//	    else if (iBands == 3) // standard BGR file; pixel-interleaved
//	        {
//		TIFFSetField(pTif, TIFFTAG_PLANARCONFIG,PLANARCONFIG_CONTIG);
//		TIFFSetField(pTif, TIFFTAG_PHOTOMETRIC,PHOTOMETRIC_RGB);
//		TIFFSetField(pTif, TIFFTAG_SAMPLESPERPIXEL,3);
//		}
	else // this one writes band-sequential
	    {
	    iPlanarConfig = PLANARCONFIG_SEPARATE;
	    iPhotometric = PHOTOMETRIC_RGB;
	    uint16 * puBitsPerSample 
		= (uint16 *) calloc(iBands,sizeof(uint16));
	    uint32 * puStripByteCount 
		= (uint32 *) calloc(iBands,sizeof(uint32));
	    if ((puBitsPerSample == NULL) || (puStripByteCount == NULL))
		return DERR_MEM_ALLOC;

	    for (int j=0; j<iBands; j++)
		{
		puBitsPerSample[j] = 8;
		puStripByteCount[j] = ulStripByteCount;
		}
	    setTag(uDirEndOffset,_BITSPERSAMPLE,TIFF_SHORT,
		   iBands,puBitsPerSample);
	    setTag(uDirEndOffset,_STRIPBYTECOUNTS,TIFF_LONG,
		   iBands,puStripByteCount);
	    free(puBitsPerSample);
	    free(puStripByteCount);
	    }

	setTag(uDirEndOffset,_IMAGEWIDTH,TIFF_SHORT,1,&(pSrcHdr->size[1]));
	setTag(uDirEndOffset,_IMAGELENGTH,TIFF_SHORT,
	       1,&(pSrcHdr->size[0]));
	setTag(uDirEndOffset,_SAMPLESPERPIXEL,TIFF_SHORT,
	       1,&iBands);
	setTag(uDirEndOffset,_ROWSPERSTRIP,TIFF_SHORT,
	       1,&(pSrcHdr->size[0]));
	setTag(uDirEndOffset,_SOFTWARE,TIFF_ASCII,
	       1+strlen(czSoftware),czSoftware);
	setTag(uDirEndOffset,_DATETIME,TIFF_ASCII,
	       1+strlen(czDateTime),czDateTime);
	setTag(uDirEndOffset,_PLANARCONFIG,TIFF_SHORT,
	       1,&iPlanarConfig);
	// need iTagBufLen here in order to create the offsets
	m_iTagBufLen = setTag(uDirEndOffset,_PHOTOMETRIC,TIFF_SHORT,
			    1,&iPhotometric);
//#ifdef GTIF
	    // the following is missing the tiepoints and
	    // most of the values, unless the Dragon header happens to
	    // already have Geotiff numerical codes instead of (or in addition to) 
	    // strings. We need to include the ValuePair stuff in the libtiff
	    // epsg files. ~~~
	if (bMapScale)
	    {
	    double tiedata[] = {(double)(pSrcHdr->img_x),
				(double)(pSrcHdr->img_y),0,
				pSrcHdr->ref_x.v0,pSrcHdr->ref_y.v0,0};
	    double sizedata[] = {pSrcHdr->xcell_size,
				 fabs(pSrcHdr->ycell_size),0} ;
	    setTag(uDirEndOffset,_GEOTIEPOINTS,TIFF_DOUBLE,6,&tiedata);
	    setTag(uDirEndOffset,_GEOPIXELSCALE,TIFF_DOUBLE,3,&sizedata);
	    }
	if (pSrcHdr->bRegistered)
	    pGtif = GTIFNew(pTif);
	if ((pGtif != NULL) && pSrcHdr->bRegistered)
	    {
	    GTIFKeySet(pGtif,GTRasterTypeGeoKey,TYPE_SHORT,1,1); /* 1=area 2=point */
		// copy any numerical GeoTIFF fields we happen to have set
	    GTIFKeySet(pGtif,GTModelTypeGeoKey,TYPE_SHORT,1,pSrcHdr->uModelType);
	    if (pSrcHdr->uModelType == 1)
		{
		GTIFKeySet(pGtif,ProjectedCSTypeGeoKey,TYPE_SHORT,1,
		           pSrcHdr->uProjectedCSType);
		GTIFKeySet(pGtif,ProjectionGeoKey,TYPE_SHORT,1,
		           pSrcHdr->uProjectionGeo);
		GTIFKeySet(pGtif,ProjCoordTransGeoKey,TYPE_SHORT,1,
		          pSrcHdr->uProjectionCoordTrans);
		// if our Dragon file has unitname = meter, then set to 9001
		// else use the value of uProjectedLinearUnits (probably 0)
		// (maybe we should put in some more specific string matches)
		if ((pSrcHdr->unitname != NULL) 
		    && (strcasecmp(pSrcHdr->unitname,"meter") == 0))
		    GTIFKeySet(pGtif,ProjLinearUnitsGeoKey,TYPE_SHORT,1,9001);
		else
		    GTIFKeySet(pGtif,ProjLinearUnitsGeoKey,TYPE_SHORT,1,
			       pSrcHdr->uProjectedLinearUnits);
	        }
	    if (pSrcHdr->uModelType == 2)
		{
		GTIFKeySet(pGtif,GeographicTypeGeoKey,TYPE_SHORT,1,
		               pSrcHdr->uGeographicType);
		GTIFKeySet(pGtif,GeogGeodeticDatumGeoKey,TYPE_SHORT,1,
		       pSrcHdr->uGeodeticDatum);
		GTIFKeySet(pGtif,GeogPrimeMeridianGeoKey,TYPE_SHORT,1,
		       pSrcHdr->uGeographicPrimeMeridian);
		}
	    GTIFKeySet(pGtif,VerticalCSTypeGeoKey,TYPE_SHORT,1,
			   pSrcHdr->uVerticalType);
	    GTIFKeySet(pGtif,VerticalUnitsGeoKey,TYPE_SHORT,1,
			   pSrcHdr->uVerticalUnits);
	    // need to do the tie points ~~~
//		    pSrcHdr->z_unit
///		= strdup(GTIFValueName(VerticalUnitsGeoKey,param));
//		    pSrcHdr->bImageHdrScalingInit = TRUE;
//		    printf("tiffImageReader setting vertical param=%d z_Unit='%s'\n",param,pSrcHdr->z_unit);
	
	    _WriteGTIFKeys(pGtif,uDirEndOffset); 	/* Store the keys in the TIFF Tags */
#ifdef GTIF
	    GTIFWriteKeys(pGtif); 	/* Store the keys in the TIFF Tags */
	    GTIFFree(pGtif);	/* get rid of the key parser */
#endif // #ifdef GTIF
	    }
	uint32 uStripOffset = 8;
	if (iBands < 2)
	    {
	    if (ulImageDataSize == 0)
		uStripOffset += 6+sizeof(tags)+m_iTagBufLen+sizeof(uint32);
	    m_iTagBufLen = setTag(uDirEndOffset,_STRIPOFFSETS,TIFF_LONG,
				1,&uStripOffset);
	    }
	else
	    {
	    if (ulImageDataSize == 0)
		uStripOffset 
		    += 6 + sizeof(tags) + m_iTagBufLen + iBands * sizeof(uint32);
	    uint32 * puStripOffsets 
		= (uint32 *)calloc(iBands,sizeof(uint32));
	    if (puStripOffsets == NULL)
		return DERR_MEM_ALLOC;
	    for (int j=0; j<iBands; j++)
		puStripOffsets[j] = uStripOffset + j * ulStripByteCount;
	    m_iTagBufLen = setTag(uDirEndOffset,_STRIPOFFSETS,TIFF_LONG,
				iBands,puStripOffsets);
	    free(puStripOffsets);
		// put in a long array 
		// must be the FINAL tag settings
	    }
	logTrace(FN_NAME " about to write header with %d tags plus "
		     " %d bytes of data; at file offset %d=x%X",
		     AY_COUNT(tags),m_iTagBufLen,uDirEndOffset,uDirEndOffset);
	// if any tag hasn't been initialized, 
	// move the remaining ones down by one
	m_uiTagCount = AY_COUNT(tags);
	uint j=0;
	while(j<m_uiTagCount)
	    {
	    if (tags[j].iDefault < 0)
		{
		logTrace(FN_NAME " Missing value for tag %d",tags[j].tag);
		for (uint jj=j; (jj+1)<m_uiTagCount; jj++)
		    {
		    memcpy(&tags[jj],&tags[jj+1],sizeof(tags[j]));
		    }
		m_uiTagCount--;
		// we will continue to write the whole array of tags,
		// because the offsets (iDefault) are based on that.
		memset(&tags[m_uiTagCount],0,sizeof(tags[j]));
		continue;
		}
	    j++;
	    }
#endif // #ifdef THEIRSTYLE
//	if (iStatus < 0)
//	    {
//	    int32 dir = 8;
//	    int32 nextdir = 0;
//	    int fd = TIFFFileno(pTif);
//	    lseek(fd,4,SEEK_SET);
//	    short count = AY_COUNT(tags);
//	    write(fd,&dir,sizeof(int32));
//	    write(fd,&count,sizeof(short));
//	    write(fd,&tags,sizeof(tags));
//	    write(fd,&nextdir,sizeof(int32));
//	    write(fd,s_uDataBuf,iTagBufLen);
//		::close(fd);
//	    }
//	    exit(1);
#ifdef NOMORE
	    struct stat tifStat;
	    int status = fstat(fd,&tifStat);
	    if (status != 0)
		logTrace(FN_NAME " error %s in fstat of file %d",
			 strerror(errno),fd);
	    long filesize = tifStat.st_size;
	    logTrace(FN_NAME " b4 stripoffsets filesize=%ld",filesize);
	    int iStat = TIFFSetField(pTif, TIFFTAG_STRIPOFFSETS,filesize);
	    if (iStat != 0)
	        {
		logTrace(FN_NAME " error in TIFFSetField to %ld",ulDirOffset);
		TIFFError(FN_NAME,"y"); // ~~~ show on console
		}
	    status = TIFFWriteDirectory(pTif);
	    if (status == 0)
		logTrace(FN_NAME " error in TIFFWriteDirectory");
//	    close();
//	    exit(1);
//	    XTIFFClose(pTif);	/* save and close the TIFF file descr*/
//	    pTif = XTIFFOpen(pczFilename,"a");
	    status = fstat(fd,&tifStat);
//	    long lFilepos = lseek(fd,0,SEEK_CUR);
	    if (status != 0)
		logTrace(FN_NAME " error %s in fstat of file %d",
			 strerror(errno),fd);
	    filesize = tifStat.st_size;
//	    ulDirOffset = TIFFCurrentDirOffset(pTif);
//	    TIFFSetDirectory(pTif,1);
//	    ulong ulNextDirOffset = TIFFCurrentDirOffset(pTif);
	    TIFFSetDirectory(pTif,0);
	    status = TIFFSetField(pTif, TIFFTAG_STRIPOFFSETS,filesize);
	    if (status == 0)
	        {
		logTrace(FN_NAME " error in TIFFSetField to %ld",filesize);
		TIFFError(FN_NAME,"x"); // ~~~ show on console
	    logTrace(FN_NAME " filesize=%ld",filesize);
	    status = TIFFCheckpointDirectory(pTif);
//	    if (status == 0)
//		logTrace(FN_NAME " error in TIFFCheckpointDirectory");
//	    close();
//	    exit(1);
#endif
	m_pFp = pTif;
	}
    *pErrNum = iStat;
    return m_iTagBufLen;
    }

		// write the file 
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @return		TRUE if OK
BOOL TiffImageWriter::writeHeader(const char * pczFilename,
				  const IMAGEHDR * pSrcHdr,
				  int * pErrNum)
    {
#undef FN_NAME
#define FN_NAME "TiffImageWriter::writeHeader"
//    if (m_iTrace)
	logTrace(FN_NAME " (en) create file %s",pczFilename);
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (en) create file %s\n",pczFilename);
    TIFF * pTif = XTIFFOpen(pczFilename, "w"); 
    BOOL bRetval = FALSE;
    if (pTif) 
	{ 
	uint uBytesPerPix = (pSrcHdr->bits_per_pix > 8) ? 2 : 1;
	uint32 ulStripByteCount 
	    = pSrcHdr->size[0]*pSrcHdr->size[1]*uBytesPerPix;
	uint uBands = (pSrcHdr->band != NULL) ? atoi(pSrcHdr->band) : 1;
	uint32 ulImageBytes = ulStripByteCount * (uint32) uBands; 
	while (ulImageBytes & 3) // IPD must start on mult of 4 bytes
	    ulImageBytes++;
	logTrace(FN_NAME " ulImageBytes=%ld",ulImageBytes);
	createIFD(pTif,pSrcHdr,pErrNum,ulImageBytes);
	_tagsDump(FN_NAME " IFD created");
	if (m_iTagBufLen > 0)
	    {
	    uint32 dir = 8 +  ulImageBytes;
//	    int32 nextdir = 0;
	    int fd = TIFFFileno(pTif);
	    lseek(fd,4,SEEK_SET);
//	    short count = AY_COUNT(tags);
	    write(fd,&dir,sizeof(int32));
//	    write(fd,&count,sizeof(short));
//	    write(fd,&tags,sizeof(tags));
//	    write(fd,&nextdir,sizeof(int32));
//	    write(fd,s_uDataBuf,iTagBufLen);
//		::close(fd);
	    }
	bRetval = TRUE;
	}
    else
	*pErrNum = DERR_FILE_OPEN;
//    if (*pErrNum == 0)
//       {
//	pGtif=(GTIF*)0; /* GeoKey-level descriptor */
//	if (! pGtif)
//	    *pErrNum = DERR_FILE_OPEN;
//	}
//    if (m_iTrace)
	logTrace(FN_NAME " (ex) returns %s error %d=%s",YESNO(bRetval),*pErrNum,dragonErrorMessage(*pErrNum));
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (ex) returns %s error %d=%s\n",YESNO(bRetval),*pErrNum,dragonErrorMessage(*pErrNum));
    return bRetval;
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
int TiffImageWriter::putImageLineRaw(const byte * pBuf, ushort uLineNo,
				 size_t uBufSize, const IMAGE * pImg,
				 BOOL bReReadable)
    {
#undef FN_NAME
#define FN_NAME "TiffImageWriter::putImageLineRaw"
    int iRetval = DERR_FILE_OOB;
    int errnum = 0;
    logTrace(FN_NAME " (en) fp=%p line %d length=%d file %s\n",
	     m_pFp,uLineNo,uBufSize,pImg->filename);
    TIFF * pTif = (TIFF *) m_pFp;
    // this is all becasue TIFFWrite requires a non-const buffer
    byte * pLocBuf = (byte *)calloc(uBufSize,1);
    if (pLocBuf == NULL)
	return DERR_MEM_ALLOC;
    memcpy(pLocBuf,pBuf,uBufSize);
    if ((pTif == NULL) 
#ifdef GTIF
	    && ((pTif = XTIFFOpen(pImg->filename,"a")) == NULL))
#else
	    && ((pTif = TIFFOpen(pImg->filename,"a")) == NULL))
#endif // #ifdef GTIF
	iRetval = DERR_FILE_OPEN;
    else if (uLineNo >= pImg->lines)
        {
	iRetval = DERR_FN_ARG1;
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " lineno=%d imagelines=%d\n",
	       uLineNo,pImg->lines);
	if (m_iTrace)
	    logTrace(FN_NAME " lineno=%d imagelines=%d",
	       uLineNo,pImg->lines);
        }
    else if (pImg->ulLinePitch != (ushort)uBufSize)
        {
	iRetval = DERR_HDR_MISMATCH;
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " linepitch=%ld bufsize=%ld\n",
	       pImg->ulLinePitch,uBufSize);
	if (m_iTrace)
	    logTrace(FN_NAME " linepitch=%ld bufsize=%ld",
	       pImg->ulLinePitch,uBufSize);
        }
    else
        {
	int fd = TIFFFileno(pTif);
	if (fd == 0)
	    iRetval = DERR_FILE_NULL;
	else
	    iRetval = write(fd,pLocBuf,uBufSize);
//		iRetval = TIFFWriteScanline(pTif,pLocBuf,uLineNo);
	free(pLocBuf);
	pLocBuf = NULL;
	if (iRetval < 0)
	    {
	    errnum = errno;
	    perror(FN_NAME " ");
	    fprintf(stderr,"failed write iRetval=%d errno=%s (%d)\n",
		    iRetval,strerror(errno),errno);
	    logTrace("write() iRetval=%d errno=%s (%d)",iRetval,strerror(errno),errno);
	    iRetval = DERR_FILE_RW; /* else it's 1 */
	    }
	else if (iRetval != (int)uBufSize)
	    {
	    fprintf(stderr,"incomplete write at line %d=%d bufsize=%d\n",
			    uLineNo,iRetval,uBufSize);
	    logTrace("incomplete write at line %d=%d",
			    uLineNo,iRetval);
	    iRetval = DERR_FILE_RW; /* else it's 1 */
	    }
	if (iRetval < 0)
	    logTrace(FN_NAME " file I/O errno=%d (%s)"
		     " t line %d linesize=%d \n",
		     errnum,strerror(errnum),uLineNo,uBufSize);
	}
    if (iRetval < 0)
        {
	logTrace(FN_NAME " error %d=%s\n"
		 "\twriting real line %d "
		 "pixcnt=%d bufsiz=%d fp=%p errno=%d (%s) linepitch=%ld",
		 iRetval,dragonErrorMessage(iRetval),
		 uLineNo,pImg->pixels,uBufSize,m_pFp,errnum,strerror(errnum),
		 pImg->ulLinePitch);
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " error %d=%s\n"
		   "\twriting real line %d "
		   "pixcnt=%d bufsiz=%d fp=%p errno=%d (%s) linepitch=%ld\n",
		   iRetval,dragonErrorMessage(iRetval),
		    uLineNo,pImg->pixels,uBufSize,m_pFp,errnum,strerror(errnum),
		   pImg->ulLinePitch);
	close();
	}
    else
	m_pFp = (FILE *) pTif;
    return iRetval;
    }

	/* if m_pFp is open, close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
int TiffImageWriter::close()
    {
#undef FN_NAME
#define FN_NAME "TiffImageWriter::close"
    int iRetval = 0;
    if (m_iDebug)
	printf("TiffImageWriter::close (en)\n");
    if (m_pFp != NULL)
        {
	TIFF * pTif = (TIFF *)m_pFp;
//	int status = TIFFWriteDirectory(pTif);
//	if (status == 0)
//	    logTrace(FN_NAME " error in TIFFWriteDirectory");
	int fd = TIFFFileno(pTif);
	::close(fd);
#ifdef GTIF
//	XTIFFClose(pTif);
#else
//	TIFFClose(pTif);
#endif // #ifdef GTIF
	m_pFp = NULL;
	}
    if (m_iDebug)
	printf(FN_NAME " (ex)\n");
    logTrace(FN_NAME " (ex) returns %d",iRetval);
    return iRetval;
    }

		// rewrite selected header info if changed
		// @return		0 if OK else
int TiffImageWriter::rewriteHeader(const Image * pImg)
    {
#undef FN_NAME
#define FN_NAME "TiffImageWriter::rewriteHeader"
    if (m_iTrace)
	logTrace(FN_NAME " (en)");
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (en)\n");
    return DERR_FN_NOTIMPL;
    }

		// append trailer on the file : closed on return
		// @param pczFilename	name of file to write
		//  			(it MUST be closed)
		// @param pHdr		pointer of IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
int TiffImageWriter::writeTrailer(const char * pczFilename,
				    const IMAGEHDR * pHdr,
				    UINT32 uDataCheck)
    { 
#undef FN_NAME
#define FN_NAME "TiffImageWriter::writeTrailer"
    logTrace(FN_NAME " (en) file=%s",pczFilename);
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (en)\n");
    int iRetval = 0;
    uint32 ulSize = 0;
    FILE * pf = fopen(pczFilename,"ab");
    if (pf == NULL)
	iRetval = DERR_FILE_OPEN;
    else if (fseek(pf,0,SEEK_END)) // fopen supposed to set to end, but ???
	iRetval = DERR_FILE_SEEK;
    else
        {
	ulSize = ftell(pf);
	while ((ulSize & 3) && (iRetval == 0))  // IPD must start on mult of 4 bytes
	    {
	    byte by = 0;
	    ulSize++;
	    if (fwrite(&by,1,1,pf) != 1)
		iRetval = DERR_FILE_RW;
	    }
	if (iRetval == 0)
	    {
	    ushort count = AY_COUNT(tags); // includes any zeroed-out ones
	    uint32 nextdir = 0;
//	    write(fd,&dir,sizeof(int32));
	    _tagsDump(FN_NAME " aboout to write IFD");
	    if (fwrite(&m_uiTagCount,sizeof(short),1,pf) != 1)
		iRetval = DERR_FILE_RW;
//	    else if (fwrite(&tags,sizeof(tags[0]),m_uiTagCount,pf) 
//		     != m_uiTagCount)
	    else if (fwrite(&tags,sizeof(tags[0]),count,pf) != count)
		iRetval = DERR_FILE_RW;
	    else if (fwrite(&nextdir,sizeof(int32),1,pf) != 1)
		iRetval = DERR_FILE_RW;
	    else if (fwrite(s_uDataBuf,m_iTagBufLen,1,pf) != 1)
		iRetval = DERR_FILE_RW;
	    _tagsDump(FN_NAME " IFD written");
	    }
	if (fclose(pf) && (iRetval == 0))  	// close file, but don't change 
	    iRetval = DERR_FILE_CLOSE;	// iRetval if already has error
	}
#ifdef LEVEL1_FILES
    int fd = TIFFFileno((TIFF *)m_pFp);
    uint32 ulSize = lseek(fd,0,SEEK_CUR);
    while (ulSize & 3) // IPD must start on mult of 4 bytes
        {
	byte by = 0;
	ulSize++;
	write(fd,&by,1);
        }
    short count = AY_COUNT(tags);
//	    write(fd,&dir,sizeof(int32));
    write(fd,&count,sizeof(short));
    write(fd,&tags,sizeof(tags));
    write(fd,&nextdir,sizeof(int32));
#endif // #ifdef LEVEL1_FILES
//	    write(fd,s_uDataBuf,iTagBufLen);
    if (iRetval)  // else errno is not relevent
	logTrace(FN_NAME " (ex) returns %s (%d) size=%ld errno=%d=%s",
		 dragonErrorMessage(iRetval),iRetval,ulSize,errno,strerror(errno));
    else	
	logTrace(FN_NAME " (ex) returns %s (%d) start of tags=%ld=x%lX",
	     dragonErrorMessage(iRetval),iRetval,ulSize,ulSize);
    return iRetval;
    }

		/* overwrite any IMAGEHDR values necessary for 
		 * this format by calling pImageheader->revise_geom()
		 * @param pImageHdr	pointer to ImageHdr
		 * @param plOffset	init sets offset of start of image
		 *			data, or -1;
		 * @return		0 if OK else:
		 *			-40 uBitsPerPix is unsupported
		 *			-41 uNumBands is unsupported
		 *			-42 uNumResolutions is unsupported
		 */
int TiffImageWriter::init(ImageHdr * pImageHdr,
	 long * plOffset) 
    { 
    *plOffset=0; 
    return 0; 
    }

	/* calc and return the size of the header plus image data, or 0
	 * This cannot be done until the header has been written
	 */
ulong TiffImageWriter::getTrailerOffset() const
    {
    return 0;
    }

#ifdef NOTUSED
int TiffImageWriter::setLinesBlob(const byte * pBlob,size_t uBlobSize) 
    { 
    int iRetval = DERR_MEM_ALLOC;
    logTrace("TiffImageWriter::setLinesBlob size=%d",uBlobSize);
    m_puLinesBlob = (byte *)calloc(uBlobSize,1);
    if (m_puLinesBlob != NULL)
        {
	m_uLinesBlobLen = uBlobSize;
	memcpy(m_puLinesBlob,pBlob,uBlobSize);
	iRetval = 0;
	}
    return iRetval;
    }
#endif // ifdef NOTUSED

		// return a formatted dump of the class member
const char * TiffImageWriter::dump(int detail, 
					   const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "TiffImageWriter dump imagehdr=%p fp=%p LinesBlob size=%d at %p",
	     m_pHdr,m_pFp,m_uLinesBlobLen,m_puLinesBlob);
    return s_czDumpBuf;
    }

void TiffImageWriter::mapCoord_copy(const MapCoord * src,
				      HDR_MapCoord * dest)
    {
    snprintf(dest->cz_v0,sizeof(dest->cz_v0),"%f",src->v0);
    dest->tag = (UINT32) src->ulTag;
    dest->v1 = (SINT32) src->v1;
    dest->v2 = (SINT32) src->v2;
    }

/************************************************************************
 *
 * following are modified from libtiff geo_write.c
 * because we need a version of GTIFFWriteKeys which uses our setTag()
 *
 ************************************************************************/

/*
 * Given GeoKey, write out the KeyEntry entries, returning 0 if failure.
 *  This is the exact complement of ReadKey().
 */
static int WriteKey(GTIF* gt, TempKeyData* tempData,
                    KeyEntry* entptr, GeoKey* keyptr)
    {
    int count;
    entptr->ent_key = (pinfo_t) keyptr->gk_key;
    entptr->ent_count = (pinfo_t) keyptr->gk_count;
    count = entptr->ent_count;
    if (count==1 && keyptr->gk_type==TYPE_SHORT)
        {
        entptr->ent_location = GTIFF_LOCAL;
        entptr->ent_val_offset = *(pinfo_t*)&keyptr->gk_data;
        return 1;
        }
		  
    switch (keyptr->gk_type)
      {
      case TYPE_SHORT:
        entptr->ent_location = GTIFF_GEOKEYDIRECTORY;
        entptr->ent_val_offset = (pinfo_t)
            ((pinfo_t*)keyptr->gk_data - gt->gt_short);
        break;
      case TYPE_DOUBLE:
        entptr->ent_location = GTIFF_DOUBLEPARAMS;
        entptr->ent_val_offset = (pinfo_t) 
            ((double*)keyptr->gk_data - gt->gt_double);
        break;
      case TYPE_ASCII:
        entptr->ent_location = GTIFF_ASCIIPARAMS;
        entptr->ent_val_offset = (pinfo_t) tempData->tk_asciiParamsOffset;
        _GTIFmemcpy (tempData->tk_asciiParams + tempData->tk_asciiParamsOffset
                     , keyptr->gk_data, keyptr->gk_count);
        tempData->tk_asciiParams[tempData->tk_asciiParamsOffset+keyptr->gk_count-1] = '|';
        tempData->tk_asciiParamsOffset += keyptr->gk_count;
        break;
      default:
        return 0; /* failure */
      }
	
    return 1; /* success */
    }

/* 
 * Numerically sort the GeoKeys.
 * We just do a linear search through
 * the list and pull out the keys that were set.
 */

static int SortKeys(GTIF* gt,int *sortkeys)
    {
    int i, did_work;
    for( i = 0; i < gt->gt_num_keys; i++ )
        sortkeys[i] = i+1;
    do 
        {  /* simple bubble sort */
        did_work = 0;
        for( i = 0; i < gt->gt_num_keys-1; i++ )
            {
            if( gt->gt_keys[sortkeys[i]].gk_key 
                > gt->gt_keys[sortkeys[i+1]].gk_key )
                {
                /* swap keys in sort list */
                int j = sortkeys[i];
                sortkeys[i] = sortkeys[i+1];
                sortkeys[i+1] = j;
                
                did_work = 1;
		}
	    }
	} 
    while( did_work );
    return 1;
    }

// write the keys using setTag
// return 1 if OK, 0 if error
static int _WriteGTIFKeys(GTIF *gt,uint uDirEndOffset)
    {
#undef FN_NAME
#define FN_NAME "_WriteGTIFKeys"
    int i;
    GeoKey *keyptr;
    KeyEntry *entptr;
    KeyHeader *header;
    TempKeyData tempData;
    int sortkeys[MAX_KEYS];
	
    if (!(gt->gt_flags & FLAG_FILE_MODIFIED)) return 1;

    if( gt->gt_tif == NULL )
        return 0;
	
    tempData.tk_asciiParams = 0;
    tempData.tk_asciiParamsLength = 0;
    tempData.tk_asciiParamsOffset = 0;

    /*  Sort the Keys into numerical order */
    if (!SortKeys(gt,sortkeys))
        {
        /* XXX error: a key was not recognized */
        }
	
    /* Set up header of ProjectionInfo tag */
    header = (KeyHeader *)gt->gt_short;
    header->hdr_num_keys = (pinfo_t) gt->gt_num_keys;
    header->hdr_version  = GvCurrentVersion;
    header->hdr_rev_major  = GvCurrentRevision;
    header->hdr_rev_minor  = GvCurrentMinorRev;
	
    /* Sum up the ASCII tag lengths */
    for (i = 0; i < gt->gt_num_keys; i++)
        {
        keyptr = gt->gt_keys + sortkeys[i];
        if (keyptr->gk_type == TYPE_ASCII)
            tempData.tk_asciiParamsLength += keyptr->gk_count;
	}
    if (tempData.tk_asciiParamsLength > 0)
        {
        tempData.tk_asciiParams =
            (char *)_GTIFcalloc(tempData.tk_asciiParamsLength + 1);
        tempData.tk_asciiParams[tempData.tk_asciiParamsLength] = '\0';
	}

    /* Set up the rest of SHORT array properly */
    keyptr = gt->gt_keys;
    entptr = (KeyEntry*)(gt->gt_short + 4);
    for (i=0; i< gt->gt_num_keys; i++,entptr++)
        {
        if (!WriteKey(gt,&tempData,entptr,keyptr+sortkeys[i])) 
	    return 0;
	}	
	
    /* Write out the Key Directory */
    logTrace( FN_NAME " %d shorts at %p",gt->gt_nshorts,gt->gt_short);
    setTag(uDirEndOffset, _GEOKEYDIRECTORY, TIFF_SHORT,
			 gt->gt_nshorts, gt->gt_short );	
//    (gt->gt_methods.set)(gt->gt_tif, GTIFF_GEOKEYDIRECTORY, 
//			 gt->gt_nshorts, gt->gt_short );	
	
    /* Write out the params directories */
//    logTrace( FN_NAME " %d doubles at %p",gt->gt_ndoubles,gt->gt_double);
    if (gt->gt_ndoubles)
	setTag(uDirEndOffset, _GEODOUBLEPARAMS, TIFF_DOUBLE,
			 gt->gt_ndoubles, gt->gt_double );	
    //     (gt->gt_methods.set)(gt->gt_tif, GTIFF_DOUBLEPARAMS, 
//			     gt->gt_ndoubles, gt->gt_double );
    else
        { logTrace( FN_NAME " no doubles"); }
//    return 1;
    if (tempData.tk_asciiParamsLength > 0)
        {
        /* just to be safe */
        tempData.tk_asciiParams[tempData.tk_asciiParamsLength] = '\0';
	setTag(uDirEndOffset, _GEOASCIIPARAMS, TIFF_ASCII,
			0, tempData.tk_asciiParams);
//        (gt->gt_methods.set)(gt->gt_tif,
//                             GTIFF_ASCIIPARAMS, 0, tempData.tk_asciiParams);
	}
	
    gt->gt_flags &= ~FLAG_FILE_MODIFIED;

    if (tempData.tk_asciiParamsLength > 0)
        _GTIFFree (tempData.tk_asciiParams);
    return 1;
    }

void TIFFIMAGEWRITER_END() { puts(FIL_ID); }
