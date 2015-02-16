#include "drelease.h"
char CHUNKIMAGE_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.18 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;

/*
 *	filename screenImageReader.cpp
 *		$Revision: 1.18 $ $Date: 2014/12/05 14:24:30 $	
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
 *   $Id: screenImageReader.cpp,v 1.18 2014/12/05 14:24:30 rudahl Exp $
 *   $Log: screenImageReader.cpp,v $
 *   Revision 1.18  2014/12/05 14:24:30  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.17  2014/03/08 06:02:18  rudahl
 *   improve debug, comments
 *
 *   Revision 1.16  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.15  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.14  2005/09/10 05:58:24  goldin
 *   Fix inconsistency in screen file creation
 *
 *   Revision 1.13  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.12  2005/07/15 02:40:32  rudahl
 *   added czFileType

 *
 *   Revision 1.11  2005/04/08 13:24:21  goldin
 *   Add stdargs.h
 *
 *   Revision 1.10  2005/04/07 10:24:26  rudahl
 *   cleaned up some arg lists and tracing
 *
 *   Revision 1.9  2005/04/06 12:15:16  rudahl
 *   fixed probs in revise_geometry
 *
 *   Revision 1.8  2005/04/05 08:01:45  rudahl
 *   fixed image dimension error
 *
 *   Revision 1.7  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.8  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.7  2005/03/10 00:06:29  rudahl
 *   added imageHdr.h
 *
 *   Revision 1.6  2005/03/09 02:45:17  goldin
 *   Fixing bugs related to creating brand new image
 *
 *   Revision 1.5  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.4  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.3  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.2  2005/01/29 17:22:27  rudahl
 *   working now apparently
 *
 *   Revision 1.1  2005/01/26 02:04:00  rudahl
 *   initial from moochie
 *
 *
 ****************************************************************
 * 
 * Define a class for reading headers from screen (chunk) image files.
 * This code is extracted from Release 5.4.4 viewport/cinfo.cpp, graf/windrv,
 * etc
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-11 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4, especially img_hdr.c
 * 	2005-1-31 ktr	renamed/rescoped from Headerreader
 * 
 *		NOTE - cannot make the CHUNK_FILE_HDR pack(2) here
 *			CHUNK_HDR appears OK, not sure about other structs.
 * 5.7	2005-7-14 ktr	initial use will be v 5.7
 *	2005-7-20 ktr	added getLineBufferSize()
 *	2005-9-17 ktr	enhanced dump()
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcat_array */
#include "dragon-errors.h"

#include "files.h"
#include "portfile.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"
#include "screenImageReader.h"

Class ScreenImageReader::s_class_Base("ScreenImageReader",
				      "Class for reading screen image files");

const char * ScreenImageReader::s_czInfTypes[] = { INF_TYPE_NAMES };

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
ScreenImageReader::ScreenImageReader(int iDebug, int iTrace)
    {
    m_pClass = &s_class_Base; 
    m_pClass->setSubClass(ImageReader::getBaseClass());
    memset(&m_FileHdr,0,sizeof(CHUNK_FILE_HDR));
    m_pChunkHdr = NULL;	// array of chunk headers in same sequence as in file
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    }

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
BOOL ScreenImageReader::test(const char * pczFilename,BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    if (bDebug)
	printf("ScreenImageReader::test (en) %s\n",pczFilename);
    if (strlen(pczFilename) > 4)
	{
	const char * extn = &pczFilename[ strlen(pczFilename)-3];
	//printf("ScreenImageReader::test extn='%s'\n",extn);
	if (strcasecmp(extn,".ch") == 0)
	    {
	    FILE * pf = fopen(pczFilename,"rb");
	    if (pf != NULL)
	        {
		size_t count = fread(s_outbuf,1,sizeof(CHUNK_FILE_HDR),pf);
		if (count == sizeof(CHUNK_FILE_HDR))
		    {
		    if (bDebug)
		        {
			printf("0: %c %c ( %02X %02X)\n",
			      s_outbuf[0],s_outbuf[1],s_outbuf[0],s_outbuf[1]);
		       }
		    if (*(ushort *)s_outbuf == BFT_CHUNK) 
			bRetval = TRUE;
		    }
		else
		    if (bDebug)
			printf("read of %s returns %d\n",pczFilename,count);
		fclose(pf);
		}
	    else
		if (bDebug)
		    printf("unable to open %s\n",pczFilename);
	    }
	}
    if (bDebug)
	printf("ScreenImageReader::test (ex): %s\n",YESNO(bRetval));
    return bRetval;
    }

// in GCC we're not getting the correct sizeof() values, so hack it
#define CHUNK_FILE_HDR_SZ 14

		// read the file 
		// @param pf		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
BOOL ScreenImageReader::readHeader(FILE * pf,
				   IMAGEHDR * pHdr,
				   int * pErrNum, Image * pImg)
    {
    *pErrNum = 0;
    if (m_iDebug)
	printf("ScreenImageReader::readHeader (en)\n");
    if (m_iTrace)
	logTrace("ScreenImageReader::readHeader (en)");
    CH_DISPIMG imgDescr;	// description of contain image
    char czImgType[16];
    size_t uChunkCount = 0;
    if (pf == NULL)
        *pErrNum = DERR_FN_ARG0;
    else
        {
	fseek(pf,0,SEEK_SET);       // back to beginning if necessary
long pos = ftell(pf);
logTrace("ScreenImageReader::readHeader - after reset to 0 ftell returns %d",
	 pos);
	size_t count = fread(&m_FileHdr,1,sizeof(CHUNK_FILE_HDR),pf);
	if (count != sizeof(CHUNK_FILE_HDR))
	    *pErrNum = DERR_FILE_RW;
	else
	    {
	    m_pHdr = pHdr;
	    if (m_iDebug)
	        {
		ushort * verptr = (ushort *)&m_FileHdr;
		printf("ScreenImageReader::read hdr size=%d ver=x%X\n",
		       count,verptr[4]);
		}
	    //	    fseek(pf,CHUNK_FILE_HDR_SZ,SEEK_SET);
	    memset(&imgDescr,0,sizeof(imgDescr));
	    ulong ulOffset = CHUNK_FILE_HDR_SZ;
	    while(1) /* count CHUNK_HDRS */
	        {
		CHUNK_HDR tmp;
		ulong ulFSize = fsize(pf);

logTrace("ScreenImageReader::readHeader - filesize returned is %d",
                             ulFSize);
logTrace("ScreenImageReader::readHeader - ulOffset is %d",
                             ulOffset);
logTrace("ScreenImageReader::readHeader - size of CHUNK_HDR is %d",
                             sizeof(tmp));


		if (fseek(pf,ulOffset,SEEK_SET))  // || errno)
		    {
		    *pErrNum = DERR_FILE_SEEK;
		    int errNum = errno;
		    perror("ScreenImageReader::readHeader seeking CHUNK_HDR");
		    logTrace("ScreenImageReader::readHeader "
			     "seek error 1 seeking CHUNK_HDR at %ld errnum=%d",
			     ulOffset,errNum);
		    if (m_iDebug)
		        printf("ScreenImageReader::readHeader "
			       "next CHUNK_HDR %d not found at %ld errno=%d\n",
			       uChunkCount+1,ulOffset,errNum);
		    break;
		    }
		if (ulFSize < (ulOffset+sizeof(tmp)))
		    {
		    *pErrNum = DERR_IMAGE_CORRUPT;
		    if (m_iDebug)
		        printf("ScreenImageReader::readHeader "
			       "seeking CHUNK_HDR %d at %ld "
			       "but file size=%ld too small\n",
			       uChunkCount+1,ulOffset,ulFSize);
		    break;
		    }
		long lPosn = ftell(pf);
		if (m_iDebug)
		    printf("ftell=%ld desired=%ld\n",lPosn,ulOffset);
		count = fread(&tmp,1,sizeof(tmp),pf);
		if (count != sizeof(tmp))
		    {
		    int errnum = errno;
		    if (m_iDebug)
		        {
			perror("ScreenImageReader read error");
			printf("ScreenImageReader::read "
			       "read %d bytes err=%d\n",
			       count,errnum);
			}
		    *pErrNum = DERR_FILE_RW;
		    break;
		    }
		if (m_iDebug)
			printf("ScreenImageReader::read CHUNK_HDR #%d "
			       "from readoffset=%ld  size=%d\n"
			       "\tcontents: "
			       "type=%s sz=%ld offset=x%lX next at x%lX=%ld\n"
			       "\tfile='%s' time=%ld\n",
			       uChunkCount+1,lPosn,sizeof(CHUNK_HDR),
			       tmp.cChunk,tmp.ulHdrSize,tmp.lOffset,
			       tmp.lNxtOffset,tmp.lNxtOffset,
			       tmp.cFile,tmp.ulTimeStamp);
logTrace("ScreenImageReader::read CHUNK_HDR #%d "
			       "from readoffset=%ld  size=%d\n"
			       "\tcontents: "
			       "type=%s sz=%ld offset=x%lX next at x%lX=%ld\n"
			       "\tfile='%s' time=%ld\n",
			       uChunkCount+1,lPosn,sizeof(CHUNK_HDR),
			       tmp.cChunk,tmp.ulHdrSize,tmp.lOffset,
			       tmp.lNxtOffset,tmp.lNxtOffset,
			       tmp.cFile,tmp.ulTimeStamp);
		uChunkCount++;
		if (tmp.lNxtOffset == 0)
		    break; /* last one */
		ulOffset = tmp.lNxtOffset;
		    /* if this chunk is an image, grab info ~~ */
		if ((strcmp(tmp.cChunk,s_czInfTypes[INF_PIX24])==0)
			|| (strcmp(tmp.cChunk,s_czInfTypes[INF_PIX32])==0))
		    {
		    lPosn = ftell(pf);
		    if (fread(&imgDescr,1,sizeof(imgDescr),pf) 
			        != sizeof(imgDescr))
		        {
			*pErrNum = DERR_FILE_RW;
			if (m_iDebug)
			        printf("    error reading CH_IMGDESCR\n");
			}
		    else
		        {
			strcpy_array(czImgType,tmp.cChunk);
			if (m_iDebug)
			      printf("ScreenImageReader::read CH_DISPIMG "
				     "from readoffset=%ld  size=%d\n"
				     "\tcontents: "
				     "struct sz=%ld, img=%d x %d = %ld "
				     "cImage='%s'\n"
				     "\tat offset %ld=x%lX "
				     "tiles: %d,%d,%d,%d %ld\n",
				   lPosn,sizeof(CH_DISPIMG),
				   imgDescr.ulSize,
				   imgDescr.uPix,imgDescr.uLines,
				   imgDescr.ulSizeImage,imgDescr.cImage,
				   imgDescr.ulOffset,imgDescr.ulOffset,
				   imgDescr.uTilesW,imgDescr.uTilesH,
				   imgDescr.uTilePix,imgDescr.uTileLn,
				   imgDescr.ulTileRowBytes);
			}
		    }
		else 
		    if (m_iDebug)
		        printf("    chunk '%s' is not imgDescr\n",
			       tmp.cChunk);
		} /* end of chunk read loop */
	    if (m_iDebug)
		printf("ScreenImageReader::read "
		       "got %d CHUNK_HDR's err=%d\n",
			       uChunkCount+1,*pErrNum);
	    /* -52 => file structure error, but still possible to read */
	    // if (((*pErrNum == 0) || (*pErrNum == -52)) && (uChunkCount > 0)
	    if ((*pErrNum == 0) && (uChunkCount > 0))
		{
		if (fseek(pf,CHUNK_FILE_HDR_SZ,SEEK_SET) != 0)
		    {
		    *pErrNum = DERR_FILE_SEEK;
		    logTrace("ScreenImageReader::readHeader "
			     "seek error 2 seeking 14 at %ld errno=%d",
			     ulOffset,errno);
		    }
		else if ((m_pChunkHdr 
			  = (CHUNK_HDR *)calloc(uChunkCount+1,sizeof(CHUNK_HDR)))
			== NULL)
		    *pErrNum = DERR_MEM_ALLOC;
		else
		    {  /* read CHUNK_HDRS */
		    size_t uNdx;
		    for (uNdx = 0; uNdx < uChunkCount; uNdx++)
		        {
		        byte * pCh = (byte *)&m_pChunkHdr[uNdx];
			count = fread(pCh,1,sizeof(CHUNK_HDR),pf);
			if (count != sizeof(CHUNK_HDR))
			    {
			    *pErrNum = DERR_FILE_RW;
			    break;
			    }
			if (fseek(pf,((CHUNK_HDR *)pCh)->lNxtOffset,SEEK_SET))
			    {
			    *pErrNum = DERR_FILE_SEEK;
			    logTrace("ScreenImageReader::readHeader "
				     "seek error 3 seeking CHUNK_HDR at %ld errno=%d",
				     ((CHUNK_HDR *)pCh)->lNxtOffset,errno);
			    break;
			    }
			}
		    if ((*pErrNum != 0) && m_iDebug)
		        {
			perror("ScreenImageReader::readHeader ");
			printf("ScreenImageReader::readHeader "
			       "error %d (%s) getting chunk %d\n",
			       *pErrNum,dragonErrorMessage(*pErrNum),uNdx);
			}
		    }
		if ((*pErrNum != 0) && m_iDebug)
		    {
		    perror("ScreenImageReader::readHeader ");
		    printf("ScreenImageReader::readHeader "
			   "error %d (%s) getting chunks\n",
			       *pErrNum,dragonErrorMessage(*pErrNum));
		    }
		}
	    } /* end getting CHUNK_HDRs */
	}
	    /* -52 => file structure error, but still possible to read */
    if (m_iDebug)
	printf("ScreenImageReader::readHeader done reading errnum=%d\n",*pErrNum);
    if (m_iTrace)
	logTrace("ScreenImageReader::readHeader done reading errnum=%d",*pErrNum);
    if (*pErrNum == 0) //  || (*pErrNum == -52))
        {
	if (imgDescr.ulSize == 0)
	    *pErrNum = DERR_IMAGE_CORRUPT;	/* no image in file */
	else
	    {
	    if (m_iDebug)
		printf("ScreenImageReader::read init hdr flds\n");
	    m_pHdr = pHdr;
	    m_pHdr->bBinary = TRUE;
	    m_pHdr->bRectangular = TRUE;
	    m_pHdr->uBands = (strcmp(czImgType,s_czInfTypes[INF_PIX24]) == 0)
		? 3 : 4;
	    m_pHdr->size[0] = imgDescr.uLines; 	/* elt[0] is lines */
	    m_pHdr->size[1] = imgDescr.uPix;
	    m_pHdr->bits_per_pix = 8;
	    m_pHdr->ulDataOffset = imgDescr.ulOffset;
	    m_pHdr->uBandLayout = IMG_PIL;
	    m_pHdr->ulDataSize = imgDescr.ulSizeImage; /* bytes of image data*/
	    m_pHdr->ulPixelPitch = m_pHdr->uBands;
	    m_pHdr->ulLinePitch = imgDescr.ulTileRowBytes; //m_pHdr->ulPixelPitch*m_pHdr->size[1];
	    m_pHdr->ulBandPitch = 0;
	    m_pHdr->bImageHdrInitialized = TRUE;
	    m_pHdr->bImageHdrDescriptionInit = TRUE; /* ~~ not really */
	    }
	}
    sprintf(m_pHdr->czFileType,"Dragon ScreenImage");
    if (m_iDebug)
   	printf("ScreenImageReader::readHeader (ex) got %d CHUNK_HDRs err=%d (%s)\n",
	       uChunkCount,*pErrNum,dragonErrorMessage(*pErrNum));
    if (m_iTrace)
   	logTrace("ScreenImageReader::readHeader (ex) got %d CHUNK_HDRs err=%d (%s)",
	       uChunkCount,*pErrNum,dragonErrorMessage(*pErrNum));
    return (*pErrNum == 0);
    }

size_t ScreenImageReader::getLineBufferSize()
    {
    return (m_pHdr == NULL) ? 0 : m_pHdr->ulLinePitch;
    }

ScreenImageReader::~ScreenImageReader()
    {
    if (m_pChunkHdr != NULL)
	free(m_pChunkHdr);
    }

		// return a formatted dump of the class member
const char * ScreenImageReader::dump(int detail, 
				     const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "ScreenImageReader dump imagehdr=%p fp=%p",
	     m_pHdr,m_pFp);
    return s_czDumpBuf;
    }

void SCREEN_IMG_RDR_END() { puts(FIL_ID); }
