#include "drelease.h"
char DRAGIMAGERDR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.50 $$Date: 2015/01/21 10:37:33 $";
D_REL_IDSTR;

/*
 *	filename dragonImageReader.cpp
 *		$Revision: 1.50 $ $Date: 2015/01/21 10:37:33 $	
 *
 *      ~~ Copyright 2004-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: dragonImageReader.cpp,v 1.50 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: dragonImageReader.cpp,v $
 *   Revision 1.50  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.49  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.48  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.47  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.46  2014/01/25 05:48:40  rudahl
 *   add geotiff fields to header
 *
 *   Revision 1.45  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.44  2008/06/14 10:15:28  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.43  2007/08/02 12:32:45  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.42  2007/01/01 13:36:42  rudahl
 *   remove large chunk of redundant trailer-reading code
 *
 *   Revision 1.41  2007/01/01 07:22:30  rudahl
 *   fix problem with changed DHEAD_VERSION
 *
 *   Revision 1.40  2007/01/01 04:50:15  rudahl
 *   minor fixes
 *
 *   Revision 1.39  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.38  2006/08/20 11:04:52  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.37  2006/08/11 07:34:22  goldin
 *   Fix logic problems
 *
 *   Revision 1.36  2006/08/04 11:06:40  goldin
 *   Create class hierarchy similar to that for image classes
 *
 *   Revision 1.35  2006/08/04 04:29:51  goldin
 *   Create new test for vector files in dragonImageReader
 *
 *   Revision 1.34  2006/03/04 08:14:41  rudahl
 *   improve tracing
 *
 *   Revision 1.33  2005/12/21 06:18:13  goldin
 *   bullet proof handling of labels - don't do calloc of zero labels!
 *
 *   Revision 1.32  2005/12/10 11:36:53  rudahl
 *   fixing some of the double-tilde comments
 *
 *   Revision 1.31  2005/11/19 08:42:07  rudahl
 *   revised LangFileName, etc location
 *
 *   Revision 1.30  2005/11/17 08:21:10  goldin
 *   Uncomment code to read the trailer
 *
 *   Revision 1.29  2005/09/18 02:59:39  rudahl
 *   added colorfilename access
 *
 *   Revision 1.28  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.27  2005/08/18 03:48:36  rudahl
 *   fixes to scaling
 *
 *   Revision 1.26  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.25  2005/07/15 02:40:32  rudahl
 *   added czFileType
 *
 *   Revision 1.24  2005/04/21 05:35:33  san
 *   finished reading labels
 *
 *   Revision 1.23  2005/04/08 04:02:30  goldin
 *   Fix syntax problem
 *
 *   Revision 1.22  2005/04/07 13:38:19  san
 *   impelments reading labels part
 *
 *   Revision 1.21  2005/04/04 12:56:11  san
 *   read offset for trailer
 *
 *   Revision 1.20  2005/04/01 08:54:06  goldin
 *   get rid of printf
 *
 *   Revision 1.19  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.20  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.19  2005/03/10 21:29:40  rudahl
 *   removed extra fclose
 *
 *   Revision 1.18  2005/03/10 00:06:29  rudahl
 *   added imageHdr.h
 *
 *   Revision 1.17  2005/03/04 16:37:33  san
 *   clean up verion testing
 *
 *   Revision 1.16  2005/03/04 16:06:35  san
 *   fixed version testing
 *
 *   Revision 1.15  2005/03/01 01:01:16  rudahl
 *   fixed test fn for current header
 *
 *   Revision 1.14  2005/02/28 22:17:18  san
 *   clean up tracing
 *
 *   Revision 1.13  2005/02/27 06:32:09  san
 *   adds reading histogram from new dragon file format
 *
 *   Revision 1.12  2005/02/25 18:52:26  san
 *   testing/debuging: fixes some errors, except IMAGE_FORMAT errors
 *
 *   Revision 1.11  2005/02/22 01:57:02  san
 *   testing and debuging
 *
 *   Revision 1.10  2005/02/15 02:28:36  san
 *   debuging
 *
 *   Revision 1.9  2005/02/10 23:21:56  rudahl
 *   added debug flags into constructors
 *
 *   Revision 1.8  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.7  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.6  2005/01/27 21:43:29  rudahl
 *   added fclose
 *
 *   Revision 1.5  2005/01/27 21:35:53  rudahl
 *   fixed enough to compile
 *
 *   Revision 1.4  2005/01/27 02:06:59  san
 *   fixes compilation error
 *
 *   Revision 1.3  2005/01/18 22:43:50  rudahl
 *   some fixes to typos
 *
 *   Revision 1.2  2005/01/18 22:00:19  san
 *   convert new image header structure to virtual structure
 *
 *   Revision 1.1  2005/01/04 16:29:17  rudahl
 *   new from moochie
 *
 ****************************************************************
 * 
 * Define a class for reading new-format headers from Dragon image files.
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
 * 	2005-1-31 ktr	renamed/rescoped from HeaderReader
 * 5.7	2005-7-14 ktr	initial use will be v 5.7
 *	2005-7-20 ktr	added getLineBufferSize()
 *	2005-9-17 ktr	fixed trailer reading a lot 
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
#include "ob.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "dragonHd.h"
#include "imageReader.h"
#include "dragonImageReader.h"

static Class DragonImageRdr_class("DragonImageReader",
				   "Class for reading Dragon image files");

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
DragonImageReader::DragonImageReader(int iDebug, int iTrace)
    {
    m_pClass = &DragonImageRdr_class; 
    m_pClass->setSubClass(ImageReader::getBaseClass());
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    }

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
BOOL DragonImageReader::test(const char * pczFilename, BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    if (bDebug)
	fprintf(stderr,"DragonImageReader::test (en) %s\n",pczFilename);
    if (strlen(pczFilename) > 4)
	{
	const char * extn = &pczFilename[ strlen(pczFilename)-4];
	if (bDebug)
	    fprintf(stderr,"DragonImageReader::test extn='%s'\n",extn);
	if (strcasecmp(extn,".img") == 0)
	    {
            bRetval = testHeader(pczFilename, bDebug);
            }
	}
    if (bDebug)
	fprintf(stderr,"DragonImageReader::test (ex): %s\n",YESNO(bRetval));
    return bRetval;
    }

		// return TRUE if specified file is a Dragon vector file that
                // can be handled by this class
		// This fn cannot be virtual since it's static
BOOL DragonImageReader::vectest(const char * pczFilename, BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    if (bDebug)
	fprintf(stderr,"DragonImageReader::test (en) %s\n",pczFilename);
    if (strlen(pczFilename) > 4)
	{
	const char * extn = &pczFilename[ strlen(pczFilename)-4];
	if (bDebug)
	    fprintf(stderr,"DragonImageReader::vectest extn='%s'\n",extn);
	if (strcasecmp(extn,".vec") == 0)
	    {
	    if (bDebug)
               fprintf(stderr,"vectest:: about to call testHeader");
            bRetval = testHeader(pczFilename, bDebug);
            }
	}
    if (bDebug)
	fprintf(stderr,"DragonImageReader::vectest (ex): %s\n",YESNO(bRetval));
    return bRetval;
    }

		// return TRUE if specified file is a Dragon IGC meta file that
                // can be handled by this class
		// This fn cannot be virtual since it's static
BOOL DragonImageReader::metatest(const char * pczFilename, BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    if (bDebug)
	fprintf(stderr,"DragonImageReader::metatest (en) %s\n",pczFilename);
    if (strlen(pczFilename) > 4)
	{
	const char * extn = &pczFilename[ strlen(pczFilename)-4];
	if (bDebug)
	    fprintf(stderr,"    DragonImageReader::metatest extn='%s'\n",extn);
	if (strcasecmp(extn,".dmf") == 0)
	    {
	    if (bDebug)
               fprintf(stderr,"    DragonImageReader::metatest about to call testHeader");
            bRetval = testHeader(pczFilename, bDebug);
            }
	}
    if (bDebug)
	fprintf(stderr,"DragonImageReader::metatest (ex): %s\n",YESNO(bRetval));
    return bRetval;
    }

     /* Factorization of test and vectest 
      * Checks to see if we have a Dragon 5.8 format
      * binary header or not.
      * @return TRUE if Dragon 5.8 format header
      */ 
BOOL DragonImageReader::testHeader(const char* pczFilename, BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    FILE * pf = fopen(pczFilename,"rb");
    if (pf != NULL)
        {
	size_t count = fread(s_outbuf,1,sizeof(s_outbuf),pf);
	if (count >= DHEAD)
	    {
	    ushort version = *(ushort *)&s_outbuf[510];
	    if (bDebug)
	        {
		fprintf(stderr,"504: %c %c %c %c  %c %c %c %c\n",
		       s_outbuf[504],s_outbuf[505],s_outbuf[506],s_outbuf[507],
		       s_outbuf[508],s_outbuf[509],s_outbuf[510],s_outbuf[511]);
		fprintf(stderr,"504: %02X %02X %02X %02X  %02X %02X %02X %02X  "
		       "%02X %02X %02X %02X  %02X %02X %02X %02X\n",
		       s_outbuf[504],s_outbuf[505],s_outbuf[506],s_outbuf[507],
		       s_outbuf[508],s_outbuf[509],s_outbuf[510],s_outbuf[511],
		       s_outbuf[512],s_outbuf[513],s_outbuf[514],s_outbuf[515],
		       s_outbuf[516],s_outbuf[517],s_outbuf[518],s_outbuf[519]);
		
		/* verion tracing */
		fprintf(stderr,"version=%X.%02X = %X\n", 
		       s_outbuf[511],s_outbuf[510],version);
		}
	    // compare magical word
	    //if ((strncmp(&s_outbuf[506],"GRSI",6) == 0))
	    if ((version >= 0x508) // =DHEAD_VERSION) 
		&& (strncmp(&s_outbuf[506],"GRSI",4)==0))
	        {
		bRetval = TRUE;
		}
	    }
	fclose(pf);
	}
    return bRetval;
    }


		// read the file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
BOOL DragonImageReader::readHeader(FILE * pFile,IMAGEHDR * pHdr,
				   int * pErrNum, Image * pImg)
    {
    BOOL bRetval = FALSE;
    const char * czMethod = "DragonImageReader::readHeader";
    if (m_iTrace)
	logTrace("%s (en) file=%p",czMethod,pFile);
    if (m_iDebug)
	fprintf(stderr,"%s (en) file=%p\n",czMethod,pFile);
    if (pFile != NULL)
        { 
	size_t count = fread(s_outbuf,1,sizeof(s_outbuf),pFile);
	if (count >= DHEAD)
	    {
            m_pHdr = pHdr;
            if (m_iDebug)
		fprintf(stderr,"    %s About to copy fields\n",czMethod);
            int iStat = copyFields((const DRAGON_HEAD *) s_outbuf);
            if (iStat == 0)
	        {
		*pErrNum = 0;
                bRetval = TRUE;
		}
            else 
	        *pErrNum = iStat;
            /* compare "GRSI" at 506 for new image reader */
 	    if (strncmp(&s_outbuf[506],"GRSI",7) == 0)
			bRetval = TRUE;
            if (m_iDebug)
                fprintf(stderr,"    %s Header iffoffset is %ld\n",
			czMethod, m_pHdr->iff_offset);
            /* Don't try to read the trailer for a vector file!!! */
            if ((m_pHdr->iff_offset > 0) && (m_pHdr->ftype[0] != 'V'))
		{   
		bRetval = readTrailer(pFile,pErrNum);
		// allocate memory to get info on trailer
#ifdef NOMORE
		TRAILER_T * preambles = (TRAILER_T *) calloc(1,sizeof(TRAILER_T));

		if (m_iDebug)
		    fprintf(stderr,"    %s Reading trailer: preambles=%p\n",
			    czMethod, preambles);
		if (preambles == NULL)
		    {
		    *pErrNum = DERR_MEM_ALLOC;
		    bRetval = FALSE;
		    }
		else if (fseek(pFile,m_pHdr->iff_offset,SEEK_SET)!=0)
		    {   // seek to the beginning of trailer
		    *pErrNum = DERR_FILE_SEEK;
		    bRetval = FALSE;
		    }
		else
		    {
		    memset(preambles,0,sizeof(preambles));

		    if (fread(preambles,1,sizeof(TRAILER_T),pFile)<0)
		        {
			*pErrNum = DERR_FILE_RW;
			bRetval = FALSE;
			fprintf(stderr,"   %s readTrailer error=%d='%s'=error reading trailer\n",
				czMethod,*pErrNum,getErrorMessage());
			}
		    else
		        {
		        ulong ulLabels_Offset 
			    = m_pHdr->iff_offset + sizeof(TRAILER_T); // original offset plus size of trailer
			// There are only label in trailer for this moment
			// color filename and palette are not implemented yet
			// read color filename
			//if(preambles->record[TR_COLORFILENAME].uArg1 ==1)
			//  {
			//
			//  }
			// read palette
			//if(preambles->record[TR_PALETTE].uArg1 == 1)
			//  {
			//  }
			// read labels
			if (m_iDebug)
			    fprintf(stderr,"    %s Labelcount=%d\n",
				   czMethod,preambles->record[TR_LABELCOUNT].uArg1);
			if (preambles->record[TR_LABELCOUNT].uArg1 == 1)
			    {
			    m_pHdr->uNumLabels 
				= preambles->record[TR_LABELCOUNT].uArg;

			    m_pHdr->bImageHdrClassifyInit = TRUE; // if all set
			    if (fseek(pFile,ulLabels_Offset,SEEK_SET)!=0) 
			        {	// seek to position for reading label 
			        *pErrNum = DERR_FILE_SEEK;
				bRetval = FALSE;
				}
			    else
			        {
				if (m_pHdr->uNumLabels > 0) 
				  {
			          PREAMBLE_T * labelsPreamble 
				    = (PREAMBLE_T *)calloc(m_pHdr->uNumLabels,
							   sizeof(PREAMBLE_T));
				  m_pHdr->pLabels 
				    = (LABEL_INFO *)calloc(m_pHdr->uNumLabels,
							   sizeof(LABEL_INFO));
				  ulong ulLabelPreambleSz 
				    = m_pHdr->uNumLabels*sizeof(PREAMBLE_T);
				  ulong ulLabelInfoSz 
				    = m_pHdr->uNumLabels*sizeof(LABEL_INFO);
				  if ((labelsPreamble == NULL)
				          ||(m_pHdr->pLabels == NULL))
				      {
				      *pErrNum = DERR_MEM_ALLOC;
				      bRetval = FALSE;
				      }
				  else
				      {
				      memset(labelsPreamble,0,ulLabelPreambleSz);
				      memset(m_pHdr->pLabels,0,ulLabelInfoSz);

				      if (fread(labelsPreamble,1,
					      ulLabelPreambleSz,pFile)<0)
				          {
					  *pErrNum = DERR_FILE_RW;			
					  bRetval = FALSE;
				          fprintf(stderr,"  %s "
					       "readTrailer error=%d='%s'=error reading labels\n",
					       czMethod,*pErrNum,getErrorMessage());
					  }
				      else
				          {   
				          // map to LABEL_INFO
					  for (ushort j = 0;j<m_pHdr->uNumLabels;j++)
					     {
					     m_pHdr->pLabels[j].uValue 
						 = labelsPreamble[j].uArg;
					     m_pHdr->pLabels[j].uColorNdx 
						 = labelsPreamble[j].uArg1;
					     //strcpy_array(m_pHdr->pLabels[j].czI18NKey,labelsPreamble[j].czArg2);
					     m_pHdr->pLabels[j].czI18NKey[0] = '\0';
					     // allocate memory for each label
					     m_pHdr->pLabels[j].pczText 
						 = (char *) calloc(labelsPreamble[j].uSize,
								   sizeof(char));
					     // read real label
					     fseek(pFile,labelsPreamble[j].uOffset,SEEK_SET);
					     fread(m_pHdr->pLabels[j].pczText,1,
						   labelsPreamble[j].uSize,pFile);
					     }
					  }
				      free(labelsPreamble);
				      }
				  fseek(pFile,DHEAD,SEEK_SET);
				  }
				}
			    if (m_iDebug)
				fprintf(stderr,"    %s done with preambles\n",czMethod);
			    fseek(pFile,DHEAD,SEEK_SET);
			    free(preambles);
			    bRetval = TRUE;
			    }
			}
		    }
#endif
	        }
	    }	
	}
    if (m_iTrace)
	logTrace("DragonImageReader::readHeader (ex) filetype='%s' key=x%X",
		 m_pHdr->ftype,m_pHdr->uKey );
    if (m_iDebug)
	fprintf(stderr,"%s (ex) filetype='%s' key=x%X\n",
		 czMethod,m_pHdr->ftype,m_pHdr->uKey );
    return bRetval;
    }

	         /* how big a buffer do we need? */
size_t DragonImageReader::getLineBufferSize()
    {
    return (m_pHdr == NULL) ? 0 : m_pHdr->ulLinePitch;
    }

		// return a formatted dump of the class member
const char * DragonImageReader::dump(int detail, 
					   const char * czTitle) const
    {
    char blobSample[60];
    memset(blobSample,0,sizeof(blobSample));
    strncpy(blobSample,(char *)m_puLinesBlob,min(m_uLinesBlobLen,sizeof(blobSample)-1));
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "DragonImageReader dump imagehdr=%p fp=%p byteorder=%s\n"
	     "    LinesBlob size=%d at %p (%s)",
	     m_pHdr,m_pFp,m_czBytes,m_uLinesBlobLen,m_puLinesBlob,blobSample);
    return s_czDumpBuf;
    }

/* ~~ the following 2 fns need to be verified */
	        // make image header agree with 'pSrcHdr'
	        // @@param pSrcHdr DHEAD-sized buffer (actually s_outbuf)
                //                 which has been filled from a file 
                // @@return        <0 if err (missing argument)
int DragonImageReader::copyFields(const DRAGON_HEAD * pSrcHdr)
    {
    int iRetVal = 0;
    /* first init the IMAGEFORMAT fields */
    m_pHdr->bBinary = TRUE;		/* FALSE => ASCII data */ 
    m_pHdr->bRectangular = TRUE;	/* FALSE => lines are different lens*/
    m_pHdr->uBands = 1;			/* how many bands in file */
    m_pHdr->ulDataOffset = DHEAD;	/* bytes from start of file to image */
    m_pHdr->ulDataSize = 0;		/* bytes of image data; 0 => unknown */
    m_pHdr->uBandLayout = IMG_PACKED1;	/* only if uBands>1 */ 
    m_pHdr->ulPixelPitch = 1;		/* initial guess */
    m_pHdr->ulLinePitch = pSrcHdr->fields.h_ulWidth; /* initial guess */
    m_pHdr->ulBandPitch = 0;		/* bytes from one band to the next */
    sprintf(m_pHdr->czFileType,"Dragon v %d.%d",
	    pSrcHdr->fields.cMagic[5],pSrcHdr->fields.cMagic[4]);
    
    /* then copy or derive the FILE_PARAMS fields */
    strcpy_array(m_pHdr->ftype,pSrcHdr->fields.h_czFtype);
    m_pHdr->size[0] 	= (UINT16) pSrcHdr->fields.h_ulHeight;
    m_pHdr->size[1] 	= (UINT16) pSrcHdr->fields.h_ulWidth;
    m_pHdr->bits_per_pix = (UINT16) pSrcHdr->fields.h_ulBitsPerPix;
    m_pHdr->uEncoding 	= (UINT16) pSrcHdr->fields.h_ulEncoding;
    m_pHdr->iff_offset 	= pSrcHdr->fields.h_ulIff_offset;
    m_pHdr->uKey 	= (UINT16) pSrcHdr->fields.h_ulKey;

    if (m_pHdr->bits_per_pix > 8)
        {
	m_pHdr->ulPixelPitch *= 2;	/* assume 16-bits / pix */
	m_pHdr->ulLinePitch *= 2;
	}
    m_pHdr->ulDataSize = (ulong)m_pHdr->size[0] * m_pHdr->ulLinePitch;
    m_pHdr->bImageHdrInitialized = TRUE;

    /* ~~ check if there is trailer or not */
    if(m_pHdr->iff_offset > 0)
        {
	/* ~~ if so, set classify flag to TRUE */
        m_pHdr->bImageHdrClassifyInit = TRUE; 
        /* ~~ then read trialer */
	} 

    m_pHdr->bImageHdrInitialized = TRUE;

    /* next copy the STATS */

    char * pczEnd;
#if DRAGON_VER >= 6
    m_pHdr->m_ihImgmean     = (UINT16) pSrcHdr->fields.h_ilImgmean;
    m_pHdr->m_dhImgvar      = strtod(pSrcHdr->fields.h_czImgvar,&pczEnd);
    m_pHdr->m_dhImgsd       = strtod(pSrcHdr->fields.h_czImgsd,&pczEnd);
    m_pHdr->m_ihImgmax 	    = (UINT16) pSrcHdr->fields.h_ilImgmax;
    m_pHdr->m_ihImgmin 	    = (UINT16) pSrcHdr->fields.h_ilImgmin;
#else
    m_pHdr->imgmean     = (UINT16) pSrcHdr->fields.h_ilImgmean;
    m_pHdr->imgvar      = strtod(pSrcHdr->fields.h_czImgvar,&pczEnd);
    m_pHdr->imgsd       = strtod(pSrcHdr->fields.h_czImgsd,&pczEnd);
    m_pHdr->imgmax    = (UINT16) pSrcHdr->fields.h_ilImgmax;
    m_pHdr->imgmin    = (UINT16) pSrcHdr->fields.h_ilImgmin;
#endif
    m_pHdr->bImageHdrStatsInit = TRUE;

    /* next copy the SCALING fields */
    m_pHdr->z_scale = strtod(pSrcHdr->fields.h_czZ_scale,&pczEnd);
    m_pHdr->z_offset = strtod(pSrcHdr->fields.h_czZ_offset,&pczEnd);
    /* ~~ need to verify */
    if (pSrcHdr->fields.h_czScalingType[0] == 'B')
	{
	m_pHdr->uScaleFactor = (UINT16) strtod(pSrcHdr->fields.h_czScaleFactor,&pczEnd);
	}
    else if (pSrcHdr->fields.h_czScalingType[0] == 'O')
        {
        m_pHdr->dScaleFactor = strtod(pSrcHdr->fields.h_czScaleFactor,&pczEnd);
	}

    /* ~~ copy histogram */
    m_pHdr->histo = (UINT32 *)calloc(HDR_HIST_LEN,sizeof(UINT32));
    for (int j=0; j<HDR_HIST_LEN; j++)
	m_pHdr->histo[j] = pSrcHdr->fields.histo[j];
    m_pHdr->uHdrHistLen = HDR_HIST_LEN;
    
    m_pHdr->dScaleOffset = strtod(pSrcHdr->fields.h_czScaleOffset,&pczEnd);
    m_pHdr->z_unit = strdup(pSrcHdr->fields.z_unit);

    if (m_pHdr->z_unit == NULL)
	iRetVal = -1;
    else if (strlen(pSrcHdr->fields.z_unit) > 0) /* DOES => fields valid */
	m_pHdr->bImageHdrScalingInit = TRUE;

	    /* next copy the DESCRIPTION fields */
	    /* in all cases, the m_pHdr text needs to be strdup-ed */
    m_pHdr->h_title = strdup(pSrcHdr->fields.h_title); // use name for title
    m_pHdr->h_id = strdup(pSrcHdr->fields.h_id);	       
    m_pHdr->comment = strdup(pSrcHdr->fields.comment);
    m_pHdr->source = strdup(pSrcHdr->fields.source);
    m_pHdr->scene = strdup(pSrcHdr->fields.scene);
    m_pHdr->subscene = strdup(pSrcHdr->fields.subscene);
    m_pHdr->band = strdup(pSrcHdr->fields.band);

    if ((m_pHdr->h_title == NULL)
	    || (m_pHdr->h_id == NULL)
	    || (m_pHdr->comment == NULL)
	    || (m_pHdr->source == NULL)
	    || (m_pHdr->scene == NULL)
	    || (m_pHdr->subscene == NULL)
	    || (m_pHdr->band == NULL))
	iRetVal = -2;
    else
	m_pHdr->bImageHdrDescriptionInit = TRUE;

    /* next copy or derive the GEOREF fields */
    m_pHdr->img_x = pSrcHdr->fields.h_uImg_x;
    m_pHdr->img_y = pSrcHdr->fields.h_uImg_y;
    mapCoord_copy(&(pSrcHdr->fields.ref_x),&(m_pHdr->ref_x));
    mapCoord_copy(&(pSrcHdr->fields.ref_y),&(m_pHdr->ref_y));
    m_pHdr->xcell_size = strtod(pSrcHdr->fields.h_czXcell_size,&pczEnd);
    m_pHdr->ycell_size = strtod(pSrcHdr->fields.h_czYcell_size,&pczEnd);
    
    m_pHdr->czProjection = strdup(pSrcHdr->fields.czProjection);
    m_pHdr->unitname = strdup(pSrcHdr->fields.unitname);
    m_pHdr->czDateTime = strdup(pSrcHdr->fields.h_czDateTime);
    m_pHdr->czUTMZone = strdup(pSrcHdr->fields.h_czUTMZone);
	/* copy the GeoTIFF fields */
    m_pHdr->uModelType = pSrcHdr->fields.uModelType;
    if (pSrcHdr->fields.uModelType == 1)  // projected e.g. UTM 
	{
	m_pHdr->uProjectedCSType = pSrcHdr->fields.uType;
	m_pHdr->uProjectedLinearUnits = pSrcHdr->fields.uCode1;
	m_pHdr->uProjectionGeo = pSrcHdr->fields.uCode2;
	m_pHdr->uProjectionCoordTrans = pSrcHdr->fields.uProjectionCoordTrans;
	}
    else if (pSrcHdr->fields.uModelType == 2)  // geographic lat-lon
	{
	m_pHdr->uGeographicType = pSrcHdr->fields.uType;
	m_pHdr->uGeodeticDatum = pSrcHdr->fields.uCode1;
	m_pHdr->uGeographicPrimeMeridian = pSrcHdr->fields.uCode2;
	}
		/* params in case of vertical data */ \
    m_pHdr->uVerticalType = pSrcHdr->fields.uVerticalType;
    m_pHdr->uVerticalUnits = pSrcHdr->fields.uVerticalUnits;

    m_pHdr->bRegistered = pSrcHdr->fields.h_bRegistered;
    m_pHdr->georef_init = pSrcHdr->fields.h_ulGeoref_init;
    if ((m_pHdr->unitname == NULL) || (m_pHdr->czProjection == NULL))
	iRetVal = -3;
    else if (strlen(pSrcHdr->fields.czProjection) > 0)
	m_pHdr->bImageHdrProjectionInit = TRUE;
//    const char * pBytes = (char *)&m_pHdr.fields.h_ulByteOrder;
//    strcpy_array(m_czBytes,pBytes);
    m_czBytes[0] = '\0';

    /* new 8/20/06 */
    if (strlen(pSrcHdr->fields.h_metafile) > 0)
        m_pHdr->pczMetafile = strdup(pSrcHdr->fields.h_metafile);
    if (strlen(pSrcHdr->fields.h_guid) > 0)
        m_pHdr->pczGUID = strdup(pSrcHdr->fields.h_guid);
    m_pHdr->dMinX = strtod(pSrcHdr->fields.h_czMinX,&pczEnd);
    m_pHdr->dMinY = strtod(pSrcHdr->fields.h_czMinY,&pczEnd);
    m_pHdr->dMaxX = strtod(pSrcHdr->fields.h_czMaxX,&pczEnd);
    m_pHdr->dMaxY = strtod(pSrcHdr->fields.h_czMaxY,&pczEnd);
#if DRAGON_VER >= 6
    s_iNumBands = 1;
#endif
    if (m_pHdr->dMaxX > 0) 
       m_pHdr->bExtentInit = TRUE;
    else
       m_pHdr->bExtentInit = FALSE;
    return iRetVal;
    }

void DragonImageReader::mapCoord_copy(const HDR_MapCoord * src,
				      MapCoord * dest)
    {
    char * pczEnd;
    dest->v0 = strtod(src->cz_v0,&pczEnd);
    dest->ulTag = (ulong) src->tag;
    dest->v1 = (long) src->v1;
    dest->v2 = (long) src->v2;
    }

/* alloc and return a buffer filled with data from the trailer
 * The returned buffer has a terminating 0 byte, in case the data
 * is a string.
 * @param pFile		file to read from
 * @param pErrNum	where to store non-zero errors
 * @param uDataLen	length of data
 * @param ulOffset	absolute offset into file for data
 * @return		calloc'd buffer, or NULL if error
 */
char * DragonImageReader::readTrailerData(FILE * pFile,int * pErrNum,
					  uint uDataLen, ulong ulOffset)
    {
    char * buffer = (char *) calloc(uDataLen+1,sizeof(char));
    /* ~~~ any way to screen out nonsense, huge values? */ 
//	m_pHdr->pLabels[j].pczText 
//			= (char *) calloc(labelsPreamble[j].uSize,
//					  sizeof(char));
				// read real label
    const char * czMethod = "DragonImageReader::readTrailerData";
    if (m_iDebug)
	fprintf(stderr,"%s (en) %d bytes at ulOffset=%ld\n",czMethod,uDataLen,ulOffset);
    if (buffer == NULL)
	*pErrNum = DERR_MEM_ALLOC;
    else if (fseek(pFile,ulOffset,SEEK_SET) != 0)
	*pErrNum = DERR_FILE_SEEK;
    else if (fread(buffer,1,uDataLen,pFile) < 0)
	*pErrNum = DERR_FILE_RW;			
    if (*pErrNum != 0)
        {
	if (buffer != NULL)
	    free(buffer);
	buffer = NULL;
        }
    return buffer;
    }

static const char * czRecName[] = { TRAILER_RECORD_NAMES };

BOOL DragonImageReader::readTrailer(FILE * pFile,int * pErrNum)
    {   
    BOOL bRetval = TRUE;
    const char * czMethod = "DragonImageReader::readTrailer";
    if (m_iDebug)
	fprintf(stderr,"%s (en)\n",czMethod);
    // we can't use the array indices here, since different files may 
    // have added some items
    ulong ulNextPreOffset = m_pHdr->iff_offset;
    for (uint tr = 0; tr < (sizeof(TRAILER_T) / sizeof(PREAMBLE_T)); tr++)
        {
	PREAMBLE_T * pPreamble // = (TRAILER_T *) calloc(1,sizeof(TRAILER_T));
	    = (PREAMBLE_T *) readTrailerData(pFile,pErrNum,sizeof(PREAMBLE_T),
					ulNextPreOffset);
	ulNextPreOffset += sizeof(PREAMBLE_T);
	if (pPreamble == NULL)
	    bRetval = FALSE;
	if (m_iDebug)
	    fprintf(stderr,"%s processing %s as record %d valid=%s arg=%d=x%X error=%s\n",
		    czMethod,pPreamble->czName,tr,YESNO(pPreamble->uArg1),
		    pPreamble->uArg,pPreamble->uArg,  YESNO(! bRetval));
	if (! bRetval)
	    break;
	if (pPreamble->uArg1 == 0)
	    continue;
	if ((strcmp(pPreamble->czName,czRecName[TR_LAST_RECORD]) == 0)
	      || (strcmp(pPreamble->czName,czRecName[TR_LABEL]) == 0)) // error
	    break;
	if (strcmp(pPreamble->czName,czRecName[TR_COLORFILENAME]) == 0)
	    {
	    /* read the colorfile */
	    ulong ulClfOffset = pPreamble->uOffset;
	    if (ulClfOffset != 0) // still OK and clf exists
                {
		uint uLen = pPreamble->uSize;
		m_pHdr->pczColorFileName 
		    = readTrailerData(pFile,pErrNum, uLen, ulClfOffset);
		if (m_pHdr->pczColorFileName == NULL)
		    bRetval = FALSE;
		}
	    if (m_iDebug)
		fprintf(stderr,"    %s Getting colorfile name from offset %ld is %s\n",
			czMethod,ulClfOffset,NN(m_pHdr->pczColorFileName));
	    }
	else if ((strcmp(pPreamble->czName,czRecName[TR_ORIGIN]) == 0)
		 && (pPreamble->uArg1 == 1)) // info on original file
            {
	    /* read the labels and number of labels */
	    m_pHdr->h_uOriginalBandNumber = pPreamble->uArg >> 16;
	    m_pHdr->h_uOriginalBandCount = pPreamble->uArg & 0xFFFF;
	    m_pHdr->h_OriginalFileName
		= readTrailerData(pFile,pErrNum, 
				  pPreamble->uSize,
				  pPreamble->uOffset);
	    if (m_iDebug)
		fprintf(stderr,"    %s Getting original uArg=x%X str=%s\n",
			czMethod,pPreamble->uArg,
			NN(m_pHdr->h_OriginalFileName));
	    if (m_pHdr->h_OriginalFileName == NULL)
		bRetval = FALSE;
	    }
#if DRAGON_VER >= 6
	else if ((strcmp(pPreamble->czName,czRecName[TR_LINESBLOB]) == 0)
		 && (pPreamble->uArg > 0)) // blob exists
	    {
	    /* read the blob */
	    ulong ulOffset = pPreamble->uOffset;
	    uint uLen = pPreamble->uArg;
	    if (ulOffset != 0)
                {
		m_puLinesBlob 
		    = (byte *)readTrailerData(pFile,pErrNum, uLen, ulOffset);
		if (m_puLinesBlob == NULL)
		    bRetval = FALSE;
		else
  		    m_uLinesBlobLen = uLen;
		}
	    if (m_iDebug)
		fprintf(stderr,"    %s Getting blob size=%d from offset %ld colorfile=%s\n",
			czMethod,uLen,ulOffset,NN(m_pHdr->pczColorFileName));
	    }
#endif
	else if ((strcmp(pPreamble->czName,czRecName[TR_LABELCOUNT]) == 0)
		 && (pPreamble->uArg1 == 1)) // labels exist
            {
	    m_pHdr->uNumLabels = pPreamble->uArg;
	    ulong ulLabels_Offset = pPreamble->uOffset;
	    // original offset plus size of trailer
	    // There are only label in trailer for this moment
	    // color filename and palette are not implemented yet
	    // read color filename
	    //if(preambles->record[TR_COLORFILENAME].uArg1 ==1)
			//  {
			//
			//  }
			// read palette
			//if(preambles->record[TR_PALETTE].uArg1 == 1)
			//  {
			//  }
			// read labels
	    ulong ulLabelPreambleSz = m_pHdr->uNumLabels*sizeof(PREAMBLE_T);
	    PREAMBLE_T * labelsPreamble 
		= (PREAMBLE_T *) readTrailerData(pFile,pErrNum,
						 ulLabelPreambleSz,
						 ulLabels_Offset);
	    if (labelsPreamble  == NULL)
		bRetval = FALSE;  // error
/*
	PREAMBLE_T * labelsPreamble 
	    = (PREAMBLE_T *)calloc(m_pHdr->uNumLabels, sizeof(PREAMBLE_T));
	if (labelsPreamble == NULL)
	    {
	    *pErrNum = DERR_MEM_ALLOC;
	    bRetval = FALSE;
	    }
	else if (fseek(pFile,ulLabels_Offset,SEEK_SET) != 0) 
	    {	// seek to position for reading label preambles
	    *pErrNum = DERR_FILE_SEEK;
	    bRetval = FALSE;
	    }
	else if (fread(labelsPreamble,1,ulLabelPreambleSz,pFile)<0)
	    {
	    *pErrNum = DERR_FILE_RW;			
	    bRetval = FALSE;
//	    fprintf(stderr,"DragonImageReader::readHeader "
//		   "readTrailer error=%d='%s'=error reading labels\n",
//		   *pErrNum,getErrorMessage());
	    }
*/
	    else
	        {
	      // ulong ulLabelInfoSz = m_pHdr->uNumLabels*sizeof(LABEL_INFO);
		m_pHdr->pLabels = (LABEL_INFO *)calloc(m_pHdr->uNumLabels,
						       sizeof(LABEL_INFO));
		if (m_pHdr->pLabels == NULL)
	            {
		    *pErrNum = DERR_MEM_ALLOC;
		    bRetval = FALSE;
		    }
		else
	            {   
		    // map to LABEL_INFO
		    for (ushort j = 0;j<m_pHdr->uNumLabels;j++)
		        {
			m_pHdr->pLabels[j].uValue = labelsPreamble[j].uArg;
			m_pHdr->pLabels[j].uColorNdx = labelsPreamble[j].uArg1;
			//strcpy_array(m_pHdr->pLabels[j].czI18NKey,labelsPreamble[j].czArg2);
			m_pHdr->pLabels[j].czI18NKey[0] = '\0';
			// allocate memory for each label
			m_pHdr->pLabels[j].pczText 
			    = readTrailerData(pFile,pErrNum,
					      labelsPreamble[j].uSize,
					      labelsPreamble[j].uOffset);
			if (m_pHdr->pLabels[j].pczText  == NULL)
		            {
			    bRetval = FALSE;
			    break;
			    }
/*
			= (char *) calloc(labelsPreamble[j].uSize,
					  sizeof(char));
				// read real label
		    if (m_pHdr->pLabels[j].pczText == NULL)
		        {
			*pErrNum = DERR_MEM_ALLOC;
			bRetval = FALSE;
		        }
		    if (fseek(pFile,labelsPreamble[j].uOffset,SEEK_SET) != 0)
		        {
			*pErrNum = DERR_FILE_SEEK;
			bRetval = FALSE;
			}
		    else if (fread(m_pHdr->pLabels[j].pczText,1,
				   labelsPreamble[j].uSize,pFile) < 0)
		        {
			*pErrNum = DERR_FILE_RW;			
			bRetval = FALSE;
			}
*/
			}
		    }
		if (labelsPreamble != NULL)
		    free(labelsPreamble);
		}
	    }
	if (bRetval)
	    m_pHdr->bImageHdrClassifyInit = TRUE; // if all set	
	if (pPreamble != NULL)
	    free(pPreamble);
}  // end of tpreambles loop
    fseek(pFile,DHEAD,SEEK_SET);
    if (m_iDebug)
	fprintf(stderr,"%s (ex)\n",czMethod);
    return bRetval;
    }

void DRAGON_IMG_RDR_END() { puts(FIL_ID); }
