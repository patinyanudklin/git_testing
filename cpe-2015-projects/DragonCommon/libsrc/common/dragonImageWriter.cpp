#include "drelease.h"
char DRAGIMAGEWRTR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.54 $$Date: 2014/12/29 03:28:29 $";
D_REL_IDSTR;

/*
 *	filename dragonImageWriter.cpp
 *		$Revision: 1.54 $ $Date: 2014/12/29 03:28:29 $	
 *
 *      ~~ Copyright 2004-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: dragonImageWriter.cpp,v 1.54 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: dragonImageWriter.cpp,v $
 *   Revision 1.54  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.53  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.52  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.51  2014/01/25 05:48:40  rudahl
 *   add geotiff fields to header
 *
 *   Revision 1.50  2012/07/01 09:30:27  rudahl
 *   fix problems importing GeoEye tiff files
 *
 *   Revision 1.49  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.48  2010/12/19 06:56:58  rudahl
 *   fix some docs
 *
 *   Revision 1.47  2008/09/12 11:41:24  rudahl
 *   improved tracing
 *
 *   Revision 1.46  2008/06/19 07:38:36  rudahl
 *   testing blob access
 *
 *   Revision 1.45  2008/06/19 07:28:39  rudahl
 *   testing blob access
 *
 *   Revision 1.44  2008/06/19 06:22:42  rudahl
 *   testing blob access
 *
 *   Revision 1.43  2008/06/14 10:15:28  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.42  2008/04/05 11:46:24  rudahl
 *   tracing
 *
 *   Revision 1.41  2007/08/02 12:32:45  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.40  2007/01/01 09:42:47  rudahl
 *   improved tracing, dumps; originalfileinfo
 *
 *   Revision 1.39  2007/01/01 07:39:30  rudahl
 *   implement byteorder field
 *
 *   Revision 1.38  2007/01/01 04:50:15  rudahl
 *   minor fixes
 *
 *   Revision 1.37  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.36  2006/08/20 11:04:52  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.35  2006/08/14 07:20:17  goldin
 *   Debugging new vector framework
 *
 *   Revision 1.34  2006/03/04 08:14:41  rudahl
 *   improve tracing
 *
 *   Revision 1.33  2005/12/23 10:38:20  goldin
 *   Make sure that we preserve class values in label structure 
 *   independent of the index
 *
 *   Revision 1.32  2005/12/10 11:36:53  rudahl
 *   fixing some of the double-tilde comments
 *
 *   Revision 1.31  2005/11/24 05:10:30  rudahl
 *   fixed setting of iff_offset during writeHeader
 *
 *   Revision 1.30  2005/09/18 02:59:39  rudahl
 *   added colorfilename access
 *
 *   Revision 1.29  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.28  2005/09/12 12:18:39  goldin
 *   Fixing version inconsistencies
 *
 *   Revision 1.27  2005/08/18 03:48:36  rudahl
 *   fixes to scaling
 *
 *   Revision 1.26  2005/06/26 06:18:15  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.25  2005/04/04 12:55:35  san
 *   put trailer offset
 *
 *   Revision 1.24  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.30  2005/03/16 04:06:53  rudahl
 *   fixing writeTrailer tests
 *
 *   Revision 1.29  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.28  2005/03/11 20:27:54  goldin
 *   debugging rewriteImageHeader
 *
 *   Revision 1.27  2005/03/10 22:41:12  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.26  2005/03/10 21:33:33  goldin
 *   Working on new test
 *
 *   Revision 1.25  2005/03/10 03:18:31  goldin
 *   Still working on img_acc test code
 *
 *   Revision 1.24  2005/03/10 00:06:29  rudahl
 *   added imageHdr.h
 *
 *   Revision 1.23  2005/03/09 02:45:17  goldin
 *   Fixing bugs related to creating brand new image
 *
 *   Revision 1.22  2005/03/07 23:39:27  goldin
 *   Working on img_acc test functions
 *
 *   Revision 1.21  2005/03/04 16:37:45  san
 *   clean up verion testing
 *
 *   Revision 1.20  2005/03/04 16:07:01  san
 *   fixed version writing
 *
 *   Revision 1.19  2005/03/03 23:10:50  rudahl
 *   fixed seq. of fwrite args
 *
 *   Revision 1.18  2005/03/03 16:27:05  rudahl
 *   added getTrailerOffset
 *
 *   Revision 1.17  2005/03/02 16:43:27  rudahl
 *   finished - but not tested- writeTrailer
 *
 *   Revision 1.16  2005/03/01 20:07:11  rudahl
 *   more work on writeTrailer
 *
 *   Revision 1.15  2005/03/01 16:02:36  rudahl
 *   adding writeTrailer
 *
 *   Revision 1.14  2005/02/28 22:17:29  san
 *   clean up tracing
 *
 *   Revision 1.13  2005/02/27 06:31:28  san
 *   writes histogram to new dragon file format
 *
 *   Revision 1.12  2005/02/25 18:52:39  san
 *   testing/debuging: fixes some errors, except IMAGE_FORMAT errors
 *
 *   Revision 1.11  2005/02/22 01:57:12  san
 *   testing and debuging
 *
 *   Revision 1.10  2005/02/15 02:29:36  san
 *   debuging
 *
 *   Revision 1.9  2005/02/10 23:21:56  rudahl
 *   added debug flags into constructors
 *
 *   Revision 1.8  2005/02/07 05:40:17  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.7  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.6  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.5  2005/01/27 22:38:01  san
 *   corrects writing direction
 *
 *   Revision 1.4  2005/01/27 21:35:53  rudahl
 *   fixed enough to compile
 *
 *   Revision 1.3  2005/01/27 02:08:09  san
 *   fixes compilation errors
 *   CVS
 *
 *   : ----------------------------------------------------------------------
 *
 *   Revision 1.2  2005/01/18 22:01:26  san
 *   convert image header for virtual structure to new header structure
 *
 *   Revision 1.1  2005/01/04 16:29:17  rudahl
 *   new from moochie
 *
 ****************************************************************
 * 
 * Define a class for writing new-format Dragon image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *              san     San Ratanasanya
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-01 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 5.5  2005-01-16 san  developed to read physical image into main memory
 * 	2005-1-31 ktr	renamed/rescoped from HeaderWriter
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h
 * 	2005-8-18 ktr	fixed problem recognizing invalid calibration fields
 *	2005-9-17 ktr	enhanced dump(); fixed trailer writing a bit
 *	2005-12-9 ktr	fixed multiple bugs from not bracketing strcpy_array
 * 5.9	2007-01-01 ktr	fixup trailer writing, implement byteorder
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 *	2008-06-14 ktr	added LinesBlob to trailer
 * 6.4	2014-01-24 ktr	copy geotiff fields to GEOTIFF section of header
 */

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcpy_array */
#include "dragon-errors.h"
#include "wfutil.h"
#include "ob.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "dragonHd.h"
#include "imageWriter.h"
#include "dragonImageWriter.h"

static Class DragonImageWrtr_class("DragonImageWriter",
				   "Class for writing new Dragon image files");

const char * DragonImageWriter::s_czTrailerNames[] = {TRAILER_RECORD_NAMES};

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
DragonImageWriter::DragonImageWriter(int iDebug, int iTrace)
    {
    m_pClass = &DragonImageWrtr_class; 
    m_pClass->setSubClass(ImageWriter::getObjectClass());
    if (iDebug > m_iDebug)
      m_iDebug = iDebug;
    if (iTrace > m_iTrace)
      m_iTrace = iTrace;
    if (m_iDebug)
	fprintf(stderr,"DragonImageWriter constructor\n");
    m_uHeaderChecksum = 0;
    m_pHdr = NULL;
    }

		// write the file 
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @return		TRUE if OK
BOOL DragonImageWriter::writeHeader(const char * pczFilename,
				    const IMAGEHDR * pHdr,
				    int * pErrNum)
    {
    DRAGON_HEAD * pDrgHdr = (DRAGON_HEAD *)&s_outbuf;
    int iStat = 0;
    const char * czMethod = "DragonImageWriter::writeHeader";
    *pErrNum = 0;
    if (m_iTrace)
	logTrace("%s (en)",czMethod);
    if (m_iDebug)
	fprintf(stderr,"%s (en)\n",czMethod);
    memset(s_outbuf,0,sizeof(s_outbuf));
    m_pHdr = pHdr;
    iStat = copyFields(pDrgHdr);
    m_uHeaderChecksum = checksum(pDrgHdr,sizeof(s_outbuf));
    if (iStat == 0)
        {
	FILE * pf = fopen(pczFilename,"wb");
	if (pf != NULL)
            {
	    size_t count 
		= fwrite(pDrgHdr->buffer,sizeof(pDrgHdr->buffer),1,pf);
	    if(count != 1)
 		*pErrNum =DERR_FILE_RW;
	    else if (fclose(pf) != 0)
		*pErrNum =DERR_FILE_CLOSE;
	    else
		*pErrNum =0;
	    }
	else
	    *pErrNum =DERR_FILE_OPEN;
	}
    else
	*pErrNum = iStat;
    if (m_iTrace)
	logTrace("%s (ex) filetype='%s' key=x%lX",
		 czMethod,m_pHdr->ftype,pDrgHdr->fields.h_ulKey );
    if (m_iDebug)
	fprintf(stderr,"%s (ex) filetype='%s' key=x%lX\n",
		 czMethod,m_pHdr->ftype,pDrgHdr->fields.h_ulKey );
    return (*pErrNum == 0);
    }

		// rewrite selected header info if changed
		// @return		0 if OK else
int DragonImageWriter::rewriteHeader(const Image * pImg)
    {
    DRAGON_HEAD dragonHdr;
    const char * czMethod = "DragonImageWriter::rewriteHeader";
    if (m_iTrace)
	logTrace("%s (en)",czMethod);
    if (m_iDebug)
	fprintf(stderr,"%s (en)\n",czMethod);
    const IMAGEHDR * pHdr = pImg->getIMAGEHDR();
    int iStat = 0;
    memset(&dragonHdr,0,sizeof(dragonHdr));
    m_pHdr = pHdr;
    iStat = copyFields(&dragonHdr,pHdr);
    m_uHeaderChecksum = checksum(&dragonHdr,sizeof(dragonHdr));
    if (iStat == 0)
        {
        if (m_pFp == NULL)
            {
	    if (strlen(pImg->image.filename) == 0)
		m_iErrno = DERR_IMAGE_NONAME;
	    else if ((m_pFp = (FILE *)fopen(pImg->image.filename,"rb+")) 
		     == NULL)
		m_iErrno = DERR_FILE_OPEN;
	    }
        if (m_pFp != NULL)
	    {
	    FILE * pFp = (FILE *)m_pFp;
	    if (fseek(pFp,0,SEEK_SET) != 0)
		iStat = DERR_FILE_SEEK;
	    else if (fwrite(&dragonHdr.buffer,sizeof(dragonHdr),1,pFp) != 1)
		iStat = DERR_FILE_RW;
	    }
	}
    if (m_iTrace)
	logTrace("%s (ex) status=%d",czMethod,iStat);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) status=%d\n", czMethod,iStat);
    return iStat;
    }

		// append trailer on the file : closed on return
		// @param pczFilename	name of file to write
		//  			(it MUST be closed)
		// @param pHdr		pointer of IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
int DragonImageWriter::writeTrailer(const char * pczFilename,
				    const IMAGEHDR * pHdr,
				    UINT32 uDataCheck)
    { 
    TRAILER_T preambles;
    int iRetval = 0;
    ushort uLabels = pHdr->uNumLabels;
    ulong ulNextOffset = pHdr->iff_offset 
	+ sizeof(preambles) + uLabels * sizeof(PREAMBLE_T);
    UINT32 uTrailerSz = 0;
    PREAMBLE_T * labelPreambles = NULL;
    const char * czMethod = "DragonImageWriter::writeTrailer";
    logTrace("%s (en) file=%s",czMethod,pczFilename);
    if (m_iDebug)
	fprintf(stderr,"%s (en)\n",czMethod);
    memset(&preambles,0,sizeof(preambles));
    for (ushort j=0; j<=TR_LAST_RECORD; j++)
        {
	strcpy_array(preambles.record[j].czName,s_czTrailerNames[j]);
	logTrace("%s preamble for %d='%s'",czMethod,j,preambles.record[j].czName);
	switch(j)
	    {
	    case TR_LAST_RECORD:
		preambles.record[j].uArg1 = 1; /* valid */
		break;
	    case TR_TRAILER_SIZE:
		preambles.record[j].uArg = uTrailerSz;
		break;
	    case TR_TRAILER_RECCOUNT:	
		// ~~~ not sure about the first set of () in the next line
		preambles.record[j].uArg = (TR_LAST_RECORD+uLabels) | (TR_LAST_RECORD << 16); 
		preambles.record[j].uArg1 = 1; /* => valid */
		break;
	    case TR_TRAILER_VERSION: 	
		preambles.record[j].uArg = DHEAD_VERSION; 
		preambles.record[j].uArg1 = 1; /* => valid */
		break;
	    case TR_HEADER_CHECKSUM:	
		preambles.record[j].uArg = m_uHeaderChecksum; 
		preambles.record[j].uArg1 = 1; /* => valid */
		break;
	    case TR_DATA_CHECKSUM: 	
		preambles.record[j].uArg = uDataCheck; 
		preambles.record[j].uArg1 = 1; /* => valid */
		break;
	    case TR_TRAILER_CHECKSUM: 	
		preambles.record[j].uArg = 0;
		break;
	    case TR_COLORFILENAME:	
		if (pHdr->pczColorFileName != NULL)
		    {
		    preambles.record[j].uOffset = ulNextOffset; 
		    preambles.record[j].uArg1 = 1; /* => valid */
		    preambles.record[j].uSize 
			= 1 + strlen(pHdr->pczColorFileName);
		    ulNextOffset += 1 + strlen(pHdr->pczColorFileName);
		    }
		break;
	    case TR_PALETTE:		
		if (pHdr->pPalette != NULL)
		    {
		    preambles.record[j].uOffset = ulNextOffset; 
		    preambles.record[j].uArg = pHdr->uPaletteCount;
		    preambles.record[j].uArg1 = 1; /* => valid */
		    preambles.record[j].uSize 
			= pHdr->uPaletteCount * sizeof(UINT32);
		    ulNextOffset += pHdr->uPaletteCount * sizeof(UINT32);
		    }
		break; /* is offset to array of 32-bit colors,
					*   or 0; 'lArg' is count of entries */
	    case TR_ORIGIN:
		if (pHdr->h_OriginalFileName != NULL)
		    {
		    preambles.record[j].uOffset = ulNextOffset; 
		    preambles.record[j].uArg1 = 1; /* => valid */
		    preambles.record[j].uArg 
			= (pHdr->h_uOriginalBandNumber<<16) | pHdr->h_uOriginalBandCount;
		    preambles.record[j].uSize 
			= 1 + strlen(pHdr->h_OriginalFileName);
		    if (m_iDebug)
			fprintf(stderr,"%s Setting original uArg=x%X str=%s at %ld\n",
				    czMethod,preambles.record[j].uArg,
				    NN(m_pHdr->h_OriginalFileName),ulNextOffset);
		    ulNextOffset += 1 + strlen(pHdr->h_OriginalFileName);
		    }
		break;
	    case TR_LABELCOUNT:	
		preambles.record[j].uArg = uLabels; 
		preambles.record[j].uArg1 = 1; /* => valid */
		preambles.record[j].uOffset 
		    = pHdr->iff_offset + sizeof(preambles);
		if (m_iDebug)
		    fprintf(stderr,"%s Setting Labelcount uArg=x%X at %ld\n",
				    czMethod,preambles.record[j].uArg,ulNextOffset);
		break;
	    case TR_LINESBLOB:	
		preambles.record[j].uArg = m_uLinesBlobLen; 
		preambles.record[j].uArg1 = 1; /* => valid */
		logTrace("DragonImageWriter::writeTrailer linesblob len=%d",
			 preambles.record[j].uArg);
		break;
	    }
        }
    if (uLabels > 0)
        {
	labelPreambles = (PREAMBLE_T *) calloc(uLabels,sizeof(PREAMBLE_T));
	if (labelPreambles == NULL)
	    iRetval = DERR_MEM_ALLOC;
	else
	    for (ushort j=0; j<uLabels; j++)
	        {
		strcpy_array(labelPreambles[j].czName,
			     s_czTrailerNames[TR_LABEL]);
		labelPreambles[j].uOffset = ulNextOffset; 
		labelPreambles[j].uSize = 1 + strlen(pHdr->pLabels[j].pczText);
		labelPreambles[j].uArg = pHdr->pLabels[j].uValue;
		labelPreambles[j].uArg1 = pHdr->pLabels[j].uColorNdx;
		strcpy_array(labelPreambles[j].czArg2,
			     pHdr->pLabels[j].czI18NKey);
		if (m_iDebug)
		    fprintf(stderr,"%s Setting label uArg=x%X str=%s at %ld\n",
				    czMethod,preambles.record[j].uArg,
				    NN(labelPreambles[j].czArg2),ulNextOffset);
		ulNextOffset += 1 + strlen(pHdr->pLabels[j].pczText);
		}
	}
    if (m_uLinesBlobLen > 0)
        {
	preambles.record[TR_LINESBLOB].uOffset = ulNextOffset;
	ulNextOffset += m_uLinesBlobLen;
        }
    if (iRetval == 0)
        {
	FILE * pf = fopen(pczFilename,"rb+");
	if (pf != NULL)
            {
	    if (fseek(pf,pHdr->iff_offset,SEEK_SET) != 0)
		iRetval = DERR_FILE_SEEK;
	    else if (fwrite(&preambles,sizeof(preambles),1,pf) != 1)
		iRetval =DERR_FILE_RW;
	    else if ((uLabels > 0)
		     && (fwrite(labelPreambles,sizeof(PREAMBLE_T),
				uLabels,pf) != uLabels))
		iRetval =DERR_FILE_RW;
	    else if ((pHdr->pczColorFileName != NULL)
		     && (fwrite(pHdr->pczColorFileName,
				1+strlen(pHdr->pczColorFileName),1,pf) != 1))
		iRetval =DERR_FILE_RW;
	    else if ((pHdr->pPalette != NULL)
		     && (fwrite(pHdr->pPalette,sizeof(UINT32),
				pHdr->uPaletteCount,pf) != pHdr->uPaletteCount))
		iRetval =DERR_FILE_RW;
	    else if ((pHdr->h_OriginalFileName != NULL)
		     && (fwrite(pHdr->h_OriginalFileName,
				1+strlen(pHdr->h_OriginalFileName),1,pf) != 1))
		iRetval = DERR_FILE_RW;
	    else
	        {
		for (ushort j=0; j<uLabels; j++)
	             {
		     if (fwrite(pHdr->pLabels[j].pczText,
				1+strlen(pHdr->pLabels[j].pczText),1,pf) != 1)
		         {
			 iRetval = DERR_FILE_RW;
			 break;
			 }
		     }
		}
	    if ((iRetval == 0) && (m_uLinesBlobLen > 0) 
		     && (fwrite(m_puLinesBlob,m_uLinesBlobLen,1,pf) != 1))
		iRetval = DERR_FILE_RW;
	    if ((iRetval == 0) && (fclose(pf) != 0))
		iRetval = DERR_FILE_CLOSE;
	    }
	else
	    iRetval = DERR_FILE_OPEN;
	}
    if (labelPreambles != NULL)
	free(labelPreambles);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) at offset %ld error %d (%s)\n",
		czMethod,pHdr->iff_offset,iRetval,dragonErrorMessage(iRetval));
    logTrace("%s (ex) returns %d",czMethod,iRetval);
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
int DragonImageWriter::init(ImageHdr * pImageHdr,
	 long * plOffset) 
    { 
    *plOffset=DHEAD; 
    return 0; 
    }

	/* calc and return the size of the header plus image data, or 0
	 * This cannot be done until the header has been written
	 */
ulong DragonImageWriter::getTrailerOffset() const
    {
    return DHEAD + m_pHdr->ulLinePitch * (ulong)m_pHdr->size[0];
    }

#if DRAGON_VER >= 6
int DragonImageWriter::setLinesBlob(const byte * pBlob,size_t uBlobSize) 
    { 
    int iRetval = DERR_MEM_ALLOC;
    logTrace("DragonImageWriter::setLinesBlob size=%d",uBlobSize);
    m_puLinesBlob = (byte *)calloc(uBlobSize,1);
    if (m_puLinesBlob != NULL)
        {
	m_uLinesBlobLen = uBlobSize;
	memcpy(m_puLinesBlob,pBlob,uBlobSize);
	iRetval = 0;
	}
    return iRetval;
    }
#endif

		// return a formatted dump of the class member
const char * DragonImageWriter::dump(int detail, 
					   const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "DragonImageWriter dump imagehdr=%p fp=%p LinesBlob size=%d at %p",
	     m_pHdr,m_pFp,m_uLinesBlobLen,m_puLinesBlob);
    return s_czDumpBuf;
    }

        // make file header agree with m_pHdr
        // @param pDestHdr 	DHEAD-sized buffer (actually s_outbuf)
        //                 	which should be filled from m_pHdr info 
	// @return        <0 if err (missing argument)
int DragonImageWriter::copyFields(DRAGON_HEAD * pDestHdr)
    {
    return copyFields(pDestHdr, m_pHdr);
    }

/* make file header agree with passed header
 * @param pDestHdr 	DHEAD-sized buffer
 *                  	which should be filled from pSrcHdr info 
 * @param pSrcHdr       Pointer to IMAGEHDR to use as the source for 
 *                      header values   
 * @return        <0 if err (missing argument)
 */
int DragonImageWriter::copyFields(DRAGON_HEAD * pDestHdr,
				  const IMAGEHDR * pSrcHdr)
    {
    int iRetVal = 0;

    const char * czMethod = "DragonImageWriter::copyFields";
    if (m_iTrace)
	logTrace("%s (en)",czMethod);
    if (m_iDebug)
	fprintf(stderr,"%s (en)\n",czMethod);
    if (! pSrcHdr->bImageHdrInitialized)
	return DERR_IMAGE_UNINIT;

    /*  copy or derive the FILE_PARAMS fields */
    strcpy_array(pDestHdr->fields.h_czFtype,pSrcHdr->ftype);
    pDestHdr->fields.h_ulHeight     = (UINT32) pSrcHdr->size[0];
    pDestHdr->fields.h_ulWidth 	   = (UINT32) pSrcHdr->size[1];
    pDestHdr->fields.h_ulBitsPerPix = (UINT32) pSrcHdr->bits_per_pix;
    pDestHdr->fields.h_ulEncoding   = (UINT32) pSrcHdr->uEncoding;
    pDestHdr->fields.h_ulKey        = (UINT32) pSrcHdr->uKey;
    pDestHdr->fields.h_ulIff_offset = getTrailerOffset();
    /* ulByteOrder not currently used, but can in future permit 
     * cross-platform file decoding */
    char cByteOrder[]={'A','B','C','D'};
    memcpy(&pDestHdr->fields.h_ulByteOrder,cByteOrder,
	   sizeof(pDestHdr->fields.h_ulByteOrder));

    /*  need to revise h_ulByteOrder field if different processor */ 
    /* next copy or derive the STATS */
#if DRAGON_VER >= 6
    pDestHdr->fields.h_ilImgmean	= (UINT32) pSrcHdr->m_ihImgmean;
    snprintf(pDestHdr->fields.h_czImgvar,
	     sizeof(pDestHdr->fields.h_czImgvar),
             "%lf",pSrcHdr->m_dhImgvar);
    snprintf(pDestHdr->fields.h_czImgsd,
	     sizeof(pDestHdr->fields.h_czImgsd),
	     "%lf",pSrcHdr->m_dhImgsd);

    pDestHdr->fields.h_ilImgmax 	= (UINT32) pSrcHdr->m_ihImgmax;
    pDestHdr->fields.h_ilImgmin 	= (UINT32) pSrcHdr->m_ihImgmin;
#else
    pDestHdr->fields.h_ilImgmean      = (UINT32) pSrcHdr->imgmean;
    snprintf(pDestHdr->fields.h_czImgvar,
	     sizeof(pDestHdr->fields.h_czImgvar),
             "%lf",pSrcHdr->imgvar);
    snprintf(pDestHdr->fields.h_czImgsd,
	     sizeof(pDestHdr->fields.h_czImgsd),
	     "%lf",pSrcHdr->imgsd);

    pDestHdr->fields.h_ilImgmax 	= (UINT32) pSrcHdr->imgmax;
    pDestHdr->fields.h_ilImgmin 	= (UINT32) pSrcHdr->imgmin;
#endif

    /* next copy or derive the SCALING fields */

    snprintf(pDestHdr->fields.h_czZ_scale,
	     sizeof(pDestHdr->fields.h_czZ_scale),
           "%lf",pSrcHdr->z_scale);
    snprintf(pDestHdr->fields.h_czZ_offset,
	     sizeof(pDestHdr->fields.h_czZ_offset),
	     "%lf",pSrcHdr->z_offset);

    if ((pSrcHdr->uScaleFactor == 0) && (pSrcHdr->dScaleFactor != 0.0)) 
        { 
	snprintf(pDestHdr->fields.h_czScaleFactor,
		 sizeof(pDestHdr->fields.h_czScaleFactor),
		 "%lf",pSrcHdr->dScaleFactor);
        pDestHdr->fields.h_czScalingType[0] = 'O';
	}
    else if ((pSrcHdr->dScaleFactor == 0.0) && (pSrcHdr->uScaleFactor != 0)) 
        { 
	snprintf(pDestHdr->fields.h_czScaleFactor,
		 sizeof(pDestHdr->fields.h_czScaleFactor),
		 "%d",pSrcHdr->uScaleFactor);
        pDestHdr->fields.h_czScalingType[0] = 'B';
	}
    else /* default values for h_czSacleFactor and h_czScalingType*/
        {
	snprintf(pDestHdr->fields.h_czScaleFactor,
		 sizeof(pDestHdr->fields.h_czScaleFactor),
		 "%d",pSrcHdr->uScaleFactor);
        pDestHdr->fields.h_czScalingType[0] = 'O'; 
	}
    
    /* copy histogram */
    if (pSrcHdr->histo != NULL)
        {
	for (int j=0; j<HDR_HIST_LEN; j++)
	    pDestHdr->fields.histo[j] = pSrcHdr->histo[j];
	}
 
    snprintf(pDestHdr->fields.h_czScaleOffset,
	     sizeof(pDestHdr->fields.h_czScaleOffset),
               "%lf",pSrcHdr->dScaleOffset);
    
    if ((pSrcHdr->z_unit == NULL) || (strlen(pSrcHdr->z_unit) == 0))
	pDestHdr->fields.z_unit[0] = '\0';
    else
        {
	strcpy_array(pDestHdr->fields.z_unit,pSrcHdr->z_unit);
        }
    /* next copy or derive the DESCRIPTION fields */
    /* in all cases, the pSrcHdr text needs to be strdup-ed */

    strcpy_array(pDestHdr->fields.h_title_ro,HDR_TITLE_RO);
    if (pSrcHdr->h_title != NULL)
	{ strcpy_array(pDestHdr->fields.h_title,pSrcHdr->h_title); }
    strcpy_array(pDestHdr->fields.h_id_ro,HDR_ID_RO);

    if (pSrcHdr->h_id!=NULL)
        { strcpy_array(pDestHdr->fields.h_id,pSrcHdr->h_id); }

    /* skip past length byte in following fields */
    strcpy_array(pDestHdr->fields.h_comment_ro,HDR_COMMENT_RO);
    if (pSrcHdr->comment != NULL)
        { strcpy_array(pDestHdr->fields.comment,pSrcHdr->comment); }
    strcpy_array(pDestHdr->fields.h_source_ro,HDR_SOURCE_RO);
    if (pSrcHdr->source != NULL)
	{ strcpy_array(pDestHdr->fields.source,pSrcHdr->source); }
    strcpy_array(pDestHdr->fields.h_scene_ro,HDR_SCENE_RO);
    if (pSrcHdr->scene != NULL)
	{ strcpy_array(pDestHdr->fields.scene,pSrcHdr->scene); }
    strcpy_array(pDestHdr->fields.h_subscene_ro,HDR_SUBSCENE_RO);
    if (pSrcHdr->subscene != NULL)
	{ strcpy_array(pDestHdr->fields.subscene,pSrcHdr->subscene);}
    strcpy_array(pDestHdr->fields.h_band_ro,HDR_BAND_RO);
    if (pSrcHdr->band != NULL)
	{ strcpy_array(pDestHdr->fields.band,pSrcHdr->band); }
     
     /* set magical word */
    char cMagic[7]={'G','R','S','I',
		    DHEAD_VERSION & 0xFF, (DHEAD_VERSION & 0xFF00) >> 8};
    strcpy_array(pDestHdr->fields.cMagic,cMagic);

     /* next copy or derive the GEOREF fields */
    pDestHdr->fields.h_uImg_x = pSrcHdr->img_x;
    pDestHdr->fields.h_uImg_y = pSrcHdr->img_y;
    mapCoord_copy(&(pSrcHdr->ref_x),&(pDestHdr->fields.ref_x));
    mapCoord_copy(&(pSrcHdr->ref_y),&(pDestHdr->fields.ref_y));
    snprintf(pDestHdr->fields.h_czXcell_size,
	     sizeof(pDestHdr->fields.h_czXcell_size),"%lf",
	     pSrcHdr->xcell_size);
    snprintf(pDestHdr->fields.h_czYcell_size,
	     sizeof(pDestHdr->fields.h_czYcell_size),"%lf",
	     pSrcHdr->ycell_size);

    if (pSrcHdr->czProjection != NULL)
	{ strcpy_array(pDestHdr->fields.czProjection,pSrcHdr->czProjection); }
    if (pSrcHdr->unitname != NULL)
	{ strcpy_array(pDestHdr->fields.unitname,pSrcHdr->unitname); }
    if (pSrcHdr->czDateTime != NULL)
	{ strcpy_array(pDestHdr->fields.h_czDateTime,pSrcHdr->czDateTime); }
    if (pSrcHdr->czUTMZone != NULL)
	{ strcpy_array(pDestHdr->fields.h_czUTMZone,pSrcHdr->czUTMZone); }
	/* copy the GeoTIFF fields */
    pDestHdr->fields.uModelType = pSrcHdr->uModelType;
    if (pSrcHdr->uModelType == 1)  // projected e.g. UTM 
	{
	pDestHdr->fields.uType = pSrcHdr->uProjectedCSType;
	pDestHdr->fields.uCode1 = pSrcHdr->uProjectedLinearUnits;
	pDestHdr->fields.uCode2 = pSrcHdr->uProjectionGeo;
	pDestHdr->fields.uProjectionCoordTrans = pSrcHdr->uProjectionCoordTrans;
	}
    else if (pSrcHdr->uModelType == 2)  // geographic lat-lon
	{
	pDestHdr->fields.uType = pSrcHdr->uGeographicType;
	pDestHdr->fields.uCode1 = pSrcHdr->uGeodeticDatum;
	pDestHdr->fields.uCode2 = pSrcHdr->uGeographicPrimeMeridian;
	}
		/* params in case of vertical data */ \
    pDestHdr->fields.uVerticalType = pSrcHdr->uVerticalType;
    pDestHdr->fields.uVerticalUnits = pSrcHdr->uVerticalUnits;

    pDestHdr->fields.h_bRegistered = pSrcHdr->bRegistered;
    pDestHdr->fields.h_ulGeoref_init = pSrcHdr->georef_init;

    /* new, 8/20/05 */
    if (pSrcHdr->pczMetafile != NULL)
	{ 
        strcpy_array(pDestHdr->fields.h_metafile,pSrcHdr->pczMetafile); 
        }
    if (pSrcHdr->pczGUID != NULL)
	{ 
        strcpy_array(pDestHdr->fields.h_guid,pSrcHdr->pczGUID); 
        }
    snprintf(pDestHdr->fields.h_czMinX,sizeof(pDestHdr->fields.h_czMinX),
	     "%f",pSrcHdr->dMinX);
    snprintf(pDestHdr->fields.h_czMinY,sizeof(pDestHdr->fields.h_czMinY),
	     "%f",pSrcHdr->dMinY);
    snprintf(pDestHdr->fields.h_czMaxX,sizeof(pDestHdr->fields.h_czMaxX),
	     "%f",pSrcHdr->dMaxX);
    snprintf(pDestHdr->fields.h_czMaxY,sizeof(pDestHdr->fields.h_czMaxY),
	     "%f",pSrcHdr->dMaxY);
    if (m_iTrace)
	logTrace("%s (ex) lines=%d pix=%d bitsPP=%d band=%d linepitch=%d returns %d",czMethod,
	         pDestHdr->fields.h_ulHeight,
	         pDestHdr->fields.h_ulWidth,
	         pDestHdr->fields.h_ulBitsPerPix,
	         pDestHdr->fields.band,
//	         pDestHdr->fields.h_ulLinePitch,
	         pSrcHdr->ulLinePitch,
		 iRetVal);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) return %d\n",czMethod,iRetVal);
    return iRetVal;
    }

void DragonImageWriter::mapCoord_copy(const MapCoord * src,
				      HDR_MapCoord * dest)
    {
    snprintf(dest->cz_v0,sizeof(dest->cz_v0),"%f",src->v0);
    dest->tag = (UINT32) src->ulTag;
    dest->v1 = (SINT32) src->v1;
    dest->v2 = (SINT32) src->v2;
    }

void DRAGONIMAGEWRITER_END() { puts(FIL_ID); }
