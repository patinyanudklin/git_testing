#include "drelease.h"
char DRAGOLDIMAGE_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.34 $$Date: 2015/01/21 10:37:33 $";
D_REL_IDSTR;

/*
 *	filename dragonOldImageReader.cpp
 *		$Revision: 1.34 $ $Date: 2015/01/21 10:37:33 $	
 *
 *      ~~ Copyright 1999-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: dragonOldImageReader.cpp,v 1.34 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: dragonOldImageReader.cpp,v $
 *   Revision 1.34  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.33  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.32  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.31  2007/08/02 12:32:45  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.30  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.29  2006/03/04 08:14:41  rudahl
 *   improve tracing
 *
 *   Revision 1.28  2005/12/21 06:18:13  goldin
 *   bullet proof handling of labels - don't do calloc of zero labels!
 *
 *   Revision 1.27  2005/12/20 13:03:46  rudahl
 *   extended tracing
 *
 *   Revision 1.26  2005/09/18 02:59:39  rudahl
 *   added colorfilename access
 *
 *   Revision 1.25  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.24  2005/08/18 03:48:36  rudahl
 *   fixes to scaling
 *
 *   Revision 1.23  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.22  2005/07/15 02:40:32  rudahl
 *   added czFileType
 *
 *   Revision 1.21  2005/04/08 13:24:21  goldin
 *   Add stdargs.h
 *
 *   Revision 1.20  2005/04/07 10:24:26  rudahl
 *   cleaned up some arg lists and tracing
 *
 *   Revision 1.19  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.20  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.19  2005/03/10 00:06:29  rudahl
 *   added imageHdr.h
 *
 *   Revision 1.18  2005/03/09 02:45:17  goldin
 *   Fixing bugs related to creating brand new image
 *
 *   Revision 1.17  2005/03/03 23:10:19  rudahl
 *   fixed error numbers
 *
 *   Revision 1.16  2005/03/01 16:02:07  rudahl
 *   slight change to dragonHd.h
 *
 *   Revision 1.15  2005/02/15 18:56:54  rudahl
 *   fixes for mingw
 *
 *   Revision 1.14  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.13  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.12  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.11  2005/01/30 01:26:50  rudahl
 *   cleanup
 *
 *   Revision 1.10  2005/01/27 23:02:08  rudahl
 *   adapt for 64-bit machine
 *
 *   Revision 1.9  2005/01/27 21:43:29  rudahl
 *   added fclose
 *
 *   Revision 1.8  2005/01/27 21:36:22  rudahl
 *   added dragonHd.h
 *
 *   Revision 1.7  2005/01/27 15:42:05  rudahl
 *   set image size
 *
 *   Revision 1.6  2005/01/26 02:02:31  rudahl
 *   improved field conversions
 *
 *   Revision 1.5  2005/01/18 22:44:51  rudahl
 *   fixed up pitch vars
 *
 *   Revision 1.4  2005/01/18 18:54:01  rudahl
 *   integrated IMG_LAYOUT and pitch params
 *
 *   Revision 1.3  2005/01/05 02:22:11  rudahl
 *   more, but still incomplete, struct copy
 *
 *   Revision 1.2  2005/01/05 02:05:15  rudahl
 *   finished making it dhead build and test right
 *
 *   Revision 1.1  2005/01/04 16:29:17  rudahl
 *   new from moochie
 *
 ****************************************************************
 * 
 * Define a class for reading old-format headers from Dragon image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-01 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4, especially img_hdr.c
 * 	2005-1-31 ktr	renamed/rescoped from HeaderReader
 * 5.7	2005-7-14 ktr	initial use will be v 5.7
 *	2005-7-20 ktr	added getLineBufferSize()
 * 	2005-8-18 ktr	fixed problem recognizing invalid calibration fields
 *	2005-9-17 ktr	fixed trailer colorfile name reading
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <unistd.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcat_array */
#include "dragon-errors.h"
#include "i18n.h"
#include "dragonHd.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "dhead-old.h"
#include "imageReader.h"
#include "dragonOldImageReader.h"

Class DragonOldImageReader::s_class_Base("DragonOldImageReader",
				   "Class for reading old Dragon image files");

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
DragonOldImageReader::DragonOldImageReader(int iDebug, int iTrace)
    {
    m_pClass = &s_class_Base; 
    m_pClass->setSubClass(ImageReader::getBaseClass());
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    }

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
BOOL DragonOldImageReader::test(const char * pczFilename, BOOL bDebug)
    {
    BOOL bRetval = FALSE;
    if (bDebug)
	fprintf(stderr,"DragonOldImageReader::test (en) %s\n",pczFilename);
    if (strlen(pczFilename) > 4)
	{
	const char * extn = &pczFilename[ strlen(pczFilename)-4];
	//	if (bDebug)
	//    fprintf(stderr,"DragonOldImageReader::test extn='%s'\n",extn);
	if (strcasecmp(extn,".img") == 0)
	    {
	    struct stat sbuf;
	    long lSize = (stat(pczFilename,&sbuf) == 0) ? sbuf.st_size : -1;
	    if (lSize < (long)DHEAD) /* file too small to be valid */
		{
		if (bDebug)
		    fprintf(stderr,"File %s too small (%ld) to contain valid header\n",
			   pczFilename,lSize);
		return FALSE;
	        }
	    FILE * pf = fopen(pczFilename,"rb");
	    if (pf != NULL)
	        {
		size_t count = fread(s_outbuf,1,sizeof(s_outbuf),pf);
		fclose(pf);
		if (count >= DHEAD)
		    {
		    ushort version = *(ushort *)&s_outbuf[510];
		    if (bDebug)
		        {
			fprintf(stderr,"504 in chars: %c %c %c %c  %c %c %c %c\n",
			       s_outbuf[504],s_outbuf[505],
			       s_outbuf[506],s_outbuf[507],
			       s_outbuf[508],s_outbuf[509],
			       s_outbuf[510],s_outbuf[511]);
			fprintf(stderr,"504: %02X %02X %02X %02X  %02X %02X %02X %02X "
			       " %02X %02X %02X %02X  %02X %02X %02X %02X\n",
			       s_outbuf[504],s_outbuf[505],
			       s_outbuf[506],s_outbuf[507],
			       s_outbuf[508],s_outbuf[509],
			       s_outbuf[510],s_outbuf[511],
			       s_outbuf[512],s_outbuf[513],
			       s_outbuf[514],s_outbuf[515],
			       s_outbuf[516],s_outbuf[517],
			       s_outbuf[518],s_outbuf[519]);
			fprintf(stderr,"version=%x.%02X = %X\n",
			       s_outbuf[511],s_outbuf[510],version);
		        }
		    if ((version < 0x504)
			    || (strncmp(&s_outbuf[506],"GRSI",4) == 0))
			bRetval = TRUE;
		    }
		else
		    if (bDebug)
			fprintf(stderr,"read error: %s got %d\n",pczFilename,count);
		}
	    else
		if (bDebug)
		    fprintf(stderr,"unable to open %s\n",pczFilename);
	    }
	}
    if (bDebug)
	fprintf(stderr,"DragonOldImageReader::test (ex): %s\n",YESNO(bRetval));
    return bRetval;
    }

		// read an already-open file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
BOOL DragonOldImageReader::readHeader(FILE * pFile,
				      IMAGEHDR * pHdr,
				      int * pErrNum, Image * pImg)
    {
    BOOL bRetval = FALSE;
    *pErrNum = -1;
    if (m_iDebug)
	printf ("DragonOldImageReader::readHeader (en)\n");
    if (m_iTrace)
	logTrace("DragonOldImageReader::readHeader (en)");
    if (pFile != NULL)
        {
	struct stat sbuf;
	ulong ulSize = (fstat(fileno(pFile),&sbuf) == 0) ? sbuf.st_size : 0;
	fseek(pFile,0,SEEK_SET);       // back to beginning if necessary
	size_t count = fread(s_outbuf,1,sizeof(s_outbuf),pFile);
	if (m_iDebug)
	    printf ("DragonOldImageReader::read %d bytes filesize=%ld=x%lX\n",
		    count,ulSize,ulSize);
	if (count == DHEAD)
	    {
	    m_pHdr = pHdr;
	    int iStat = copyFields((IHEAD_OLD *) s_outbuf);
	    if (iStat == 0)
	        {
		*pErrNum = 0;
		bRetval = TRUE;
		if ((m_pHdr->ulLinePitch *(ulong)m_pHdr->size[0]+(ulong)DHEAD)
		        > ulSize)  // file is too short
		    *pErrNum = DERR_IMAGE_TOOSMALL;
	        else
		    bRetval = TRUE;

		}
	    else
		*pErrNum = iStat;
	    }
	else
	    *pErrNum = DERR_FILE_RW;
	}
    else
	*pErrNum = DERR_FILE_OPEN;
    if (m_iDebug)
	printf ("DragonOldImageReader::readHeader (ex)\n");
    if (m_iTrace)
	logTrace("DragonOldImageReader::readHeader (ex) filetype='%s' key=x%X",
		 m_pHdr->ftype,m_pHdr->uKey );
    return bRetval;
    }

	         /* how big a buffer do we need? */
size_t DragonOldImageReader::getLineBufferSize()
    {
    return (m_pHdr == NULL) ? 0 : m_pHdr->ulLinePitch;
    }

/* the following 2 fns are extracted from img_hdr.c
 * and reworked to:
 *   -- avoid old 16-bit residua
 *   -- initialize the new IMAGEHDR structure from the buffer as read
 * The old function names are retained to provide continuity 
 */ 

		// make IMAGEHDR agree with 'pSrcHdr'
		// @param pSrcHdr	DHEAD-sized buffer (actually s_outbuf)
		//			which has been filled from a file
		// @return		< 0 if err (missing argument)
int DragonOldImageReader::copyFields(IHEAD_OLD * pSrcHdr)
    {
    int iRetval = 0;
    /* first init the IMAGEFORMAT fields */
    m_pHdr->bBinary = TRUE;		/* FALSE => ASCII data */ 
    m_pHdr->bRectangular = TRUE;	/* FALSE => lines are different lens*/
    m_pHdr->uBands = 1;			/* how many bands in file */
    m_pHdr->ulDataOffset = DHEAD;	/* bytes from start of file to image */
    m_pHdr->ulDataSize = 0;		/* bytes of image data; 0 => unknown */
    m_pHdr->uBandLayout = IMG_PACKED1;	/* only if uBands>1 */ 
    m_pHdr->ulPixelPitch = 1;		/* initial guess */
    m_pHdr->ulLinePitch = pSrcHdr->fields.size[1]; /* initial guess */
    m_pHdr->ulBandPitch = 0;		/* bytes from one band to the next */
    sprintf(m_pHdr->czFileType,"Dragon v %d.%d",pSrcHdr->fields.vn/256,pSrcHdr->fields.vn & 0xF);
    if (m_iDebug)
	fprintf(stderr,"Version before SetHdr fns = x%X at %d\n",
	       pSrcHdr->fields.vn,
	       ((char *)(&pSrcHdr->fields.vn) - (char *)pSrcHdr->fields.size));
	    /* must do this BEFORE SetHdr...() */
    m_pHdr->uNumLabels = convertHeaderClassnames(pSrcHdr,NULL);
    if (m_pHdr->uNumLabels > 0)
	m_pHdr->bImageHdrClassifyInit = TRUE;
    if (pSrcHdr->fields.vn < 0x504)
        {
	if (pSrcHdr->fields.vn < 0x401)
	    SetHdrTo401(pSrcHdr);
	SetHdrToCurrent(pSrcHdr); 	/* init other new constant fields */
	}
    m_pHdr->pczColorFileName = strdup(&(pSrcHdr->fields.clf)[1]);
    /* then copy or derive the FILE_PARAMS fields */
    strcpy_array(m_pHdr->ftype,pSrcHdr->fields.ftype);
    m_pHdr->size[0] 	= pSrcHdr->fields.size[0];
    m_pHdr->size[1] 	= pSrcHdr->fields.size[1];
    m_pHdr->bits_per_pix = pSrcHdr->fields.bits_per_pix;
    m_pHdr->uEncoding 	= pSrcHdr->fields.uEncoding;
    m_pHdr->iff_offset 	= pSrcHdr->fields.iff_offset;
    m_pHdr->uKey 	= pSrcHdr->fields.uKey;
    if (m_pHdr->bits_per_pix > 8)
        {
	m_pHdr->ulPixelPitch *= 2;	/* assume 16-bits / pix */
	m_pHdr->ulLinePitch *= 2;
	}
    m_pHdr->ulDataSize = (ulong)m_pHdr->size[0] * m_pHdr->ulLinePitch;
    m_pHdr->bImageHdrInitialized = TRUE;

    /* next copy or derive the STATS */
#if DRAGON_VER >= 6
    m_pHdr->m_ihImgmean 	= pSrcHdr->fields.imgmean;
    m_pHdr->m_dhImgvar 	= pSrcHdr->fields.imgvar;
    m_pHdr->m_dhImgsd 	= pSrcHdr->fields.imgsd;
    m_pHdr->m_ihImgmax 	= pSrcHdr->fields.imgmax;
    m_pHdr->m_ihImgmin 	= pSrcHdr->fields.imgmin;
#else
    m_pHdr->imgmean   = pSrcHdr->fields.imgmean;
    m_pHdr->imgvar    = pSrcHdr->fields.imgvar;
    m_pHdr->imgsd     = pSrcHdr->fields.imgsd;
    m_pHdr->imgmax    = pSrcHdr->fields.imgmax;
    m_pHdr->imgmin    = pSrcHdr->fields.imgmin;
#endif
    m_pHdr->bImageHdrStatsInit = TRUE;

    /* next copy or derive the SCALING fields */
    m_pHdr->z_scale = pSrcHdr->fields.z_scale;
    m_pHdr->z_offset = pSrcHdr->fields.z_offset;
    m_pHdr->uScaleFactor = pSrcHdr->fields.uScaleFactor;
    m_pHdr->dScaleFactor = pSrcHdr->fields.dScaleFactor;
    m_pHdr->dScaleOffset = pSrcHdr->fields.dScaleOffset;
    m_pHdr->z_unit = strdup(pSrcHdr->fields.z_unit+1);
    if (strlen(m_pHdr->z_unit) == 0)
        //iRetval = -1;  /* NOT an error! SEG 12/21/05 */
	m_pHdr->bImageHdrScalingInit = FALSE;
    else if (strlen(pSrcHdr->fields.z_unit+1) > 0) /* DOES => fields valid */
	m_pHdr->bImageHdrScalingInit = TRUE;

    /* next copy or derive the DESCRIPTION fields */
    /* in all cases, the m_pHdr text needs to be strdup-ed */
    m_pHdr->h_title = strdup(pSrcHdr->fields.fname); // use name for title
    // m_pHdr->h_id = ;		// no ID on old ones
    /* skip past length byte in following fields */
    m_pHdr->comment = strdup(pSrcHdr->fields.comment+1);
    m_pHdr->source = strdup(pSrcHdr->fields.source+1);
    m_pHdr->scene = strdup(pSrcHdr->fields.scene+1);
    m_pHdr->subscene = strdup(pSrcHdr->fields.subscene+1);
    m_pHdr->band = strdup(pSrcHdr->fields.band+1);
    if ((m_pHdr->h_title != NULL)
	    || (m_pHdr->comment != NULL)
	    || (m_pHdr->source != NULL)
	    || (m_pHdr->scene != NULL)
	    || (m_pHdr->subscene != NULL)
	    || (m_pHdr->band != NULL))
        m_pHdr->bImageHdrDescriptionInit = TRUE; /* NOT => all exist */

    /* next copy or derive the GEOREF fields */
    m_pHdr->img_x = pSrcHdr->fields.img_x;
    m_pHdr->img_y = pSrcHdr->fields.img_y;
    mapCoord_copy(&(pSrcHdr->fields.ref_x),&(m_pHdr->ref_x));
    mapCoord_copy(&(pSrcHdr->fields.ref_y),&(m_pHdr->ref_y));
    m_pHdr->xcell_size = pSrcHdr->fields.xcell_size;
    m_pHdr->ycell_size = pSrcHdr->fields.ycell_size;
    m_pHdr->czProjection = strdup(pSrcHdr->fields.czProjection);
    m_pHdr->unitname = strdup(pSrcHdr->fields.unitname);
    m_pHdr->georef_init = TRUE;
    if ((m_pHdr->unitname != NULL) &&
        (strlen(pSrcHdr->fields.unitname) > 0))
	m_pHdr->georef_init = TRUE; 
    if ((m_pHdr->czProjection != NULL) &&
        (strlen(pSrcHdr->fields.czProjection) > 0))
	m_pHdr->bImageHdrProjectionInit = TRUE; 
    m_pHdr->uScaleFactor = pSrcHdr->fields.uScaleFactor;
    m_pHdr->histo = (UINT32 *)calloc(HDR_HIST_LEN,sizeof(UINT32));
    for (int j=0; j<HDR_HIST_LEN; j++)
	m_pHdr->histo[j] = pSrcHdr->fields.histo[j];
    m_pHdr->uHdrHistLen = HDR_HIST_LEN;
    /* finally, the misc stuff */
    return iRetval;
    }

void DragonOldImageReader::mapCoord_copy(const MapCoord_old * src,
					 MapCoord * dest)
    {
    dest->v0 = src->v0;
    dest->ulTag = src->tag;
    dest->v1 = src->v1;
    dest->v2 = src->v2;
    }

		// convert classnames read from file to current form.
	    	// Most importantly, Unicode-ify old classnames
		// @param pSrcHdr	DHEAD-sized buffer (actually s_outbuf)
		//			which has been filled from a file
		// @param puMaxLabelLen	??
		// @return		< 0 if err (-50 for calloc failure)
		// 			or actual number of classnames found .
int DragonOldImageReader::convertHeaderClassnames(IHEAD_OLD * pSrcHdr,
						    size_t * puMaxLabelLen)
    {
    int iNumLabs = 0;
    ushort uMaxLabelLen = 0;
		// assume, for older formats, clsname_offset not used
		// may want to change this fn to create an extended set
		// of classnames, but not yet with 5.00
    if (m_iDebug)
	fprintf(stderr,"convert labels charsize=%d numlabels=%d at %d sizeof(wchar_t)=%d\n",
	       pSrcHdr->fields.charsize,pSrcHdr->fields.numlabels,
	       ((char *)&(pSrcHdr->fields.numlabels) - (char *)pSrcHdr),
	       sizeof(wchar_t));
    if (pSrcHdr->fields.numlabels > 0)
       {
       m_pHdr->pLabels = (LABEL_INFO *)calloc(pSrcHdr->fields.numlabels,
					      sizeof(LABEL_INFO));
       if (m_pHdr->pLabels == NULL)
	  return -50;
       char czTemp[3 * EXT_CLASS_NAMESZ+2];
       if ((pSrcHdr->fields.vn < 0x401) || (pSrcHdr->fields.charsize != 2))
	   {
	   for (int i=NUMLABELS-1; i>=0; i--)
	       {
	       const char * pClassSrc 
		 = &(pSrcHdr->fields.dclass.oldname[i].length); 
	       if (*pClassSrc == 0)	// check length byte > 0
		 continue;
	       iNumLabs++;
	       if (strlen(czTemp) > uMaxLabelLen)
		 uMaxLabelLen = strlen(czTemp);
	       // but don't copy the length
	       strcpy_array(czTemp,pClassSrc+1);
	       for (size_t j=0; j<strlen(czTemp); j++)
		 czTemp[j] &= 0x7F; // ascii-ize it
	       m_pHdr->pLabels[i].uValue = i;
	       m_pHdr->pLabels[i].uColorNdx = 0; 	/* not yet used */
	       m_pHdr->pLabels[i].czI18NKey[0] = '\0'; 	/* not yet used */
	       m_pHdr->pLabels[i].pczText = strdup(czTemp);
	       if (m_iDebug)
		 fprintf(stderr,"  cvt ASCII label %d from %s (%p) to %s\n",
		       i,pClassSrc+1,pClassSrc,czTemp);
	       }
	   }
       else
	   {
	   for (int i=0; i < pSrcHdr->fields.numlabels; i++)
	       {
	       const UNICODE_WCHAR * pClassName 
		 = (UNICODE_WCHAR *) (pSrcHdr->fields.dclass.extname[i].name);
	       size_t uLabelLen = 0;
#if defined __MINGCC__
	       uLabelLen = grs_wcslen(pClassName);
#else
	       uLabelLen = wcslen(pClassName);
#endif
	       if (* pClassName != 0)
		  iNumLabs++;
	       if (uLabelLen > uMaxLabelLen)
		  uMaxLabelLen = uLabelLen;
	       if (m_iDebug > 4)
		  fprintf(stderr,"  next cvt UINT16 label %d from %X %X %X %X\n",
			i,pClassName[0],pClassName[1],
			pClassName[2],pClassName[3]);
	       m_pHdr->pLabels[i].uValue = i;
	       m_pHdr->pLabels[i].uColorNdx = i; 	/* not yet used */
	       m_pHdr->pLabels[i].czI18NKey[0] = '\0'; 	/* not yet used */
	       uni_wcstombs(czTemp,pClassName,sizeof(czTemp),cp_UCS2toUTF8);
	       m_pHdr->pLabels[i].pczText = strdup(czTemp);
	       if (m_iDebug > 4)
		  fprintf(stderr,"  cvt UCS label %d from x%04X x%04X x%04X x%04X (%p) to %s (%d)\n",
			i,pClassName[0],pClassName[1],
			pClassName[2],pClassName[3],pClassName,czTemp,sizeof(wchar_t));
	       }
	   }
       }
    if (puMaxLabelLen != NULL)
       *puMaxLabelLen = uMaxLabelLen;
    if (m_iDebug)
	fprintf(stderr,"convertHeaderClassnames returns %d labels; maxlen=%d\n",
	       iNumLabs,uMaxLabelLen);
    return iNumLabs;
    }

		// return a formatted dump of the class member
const char * DragonOldImageReader::dump(int detail, 
					const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "DragonOldImageReader dump imagehdr=%p fp=%p",
	     m_pHdr,m_pFp);
    return s_czDumpBuf;
    }


	/*	make sure all version-specific info is set consistently
         *      used here and in imagsw-o.c.
	 */
void DragonOldImageReader::SetHdrToCurrent(IHEAD_OLD * hdr)
    {
    int iClsNum;
    hdr->fields.vn = 0x504;
    hdr->fields.charsize = 2;	/* i.e. classnames are Unicode 2-byte form */
    hdr->fields.class_namesz = EXT_CLASS_NAMESZ;
    hdr->fields.numlabels = NUMLABELS;
	/* make sure floats have valid 0 value */
    hdr->fields.dScaleFactor = 0.0;	/* new for 5.0 */
    hdr->fields.dScaleOffset = 0.0;	/* new for 5.0 */
    hdr->fields.uEncoding = 'SR';
	/* following is a permanent (5.0 & up) file ident. signature: */
	/* exactly 4 bytes located just before the version # */
    memcpy(hdr->fields.cMagic,"GRSI",sizeof(hdr->fields.cMagic));
		/* for v 5.4, need to setup LabelInfo, numlabels */
    hdr->fields.numlabels = 0;
    for (iClsNum=0; iClsNum<NUMLABELS; iClsNum++)
        {
	UNICODE_WCHAR * pN 
		= (UNICODE_WCHAR *)hdr->fields.dclass.extname[iClsNum].name;
#if defined __MINGCC__
	if (grs_wcslen(pN) > 0)
	    hdr->fields.numlabels++;
#else
	if (wcslen(pN) > 0)
	    hdr->fields.numlabels++;
#endif
	   /* following just some reasonable values */
	hdr->fields.LabelInfo[iClsNum].uValue = iClsNum;
	hdr->fields.LabelInfo[iClsNum].uColorNdx = iClsNum;
	hdr->fields.LabelInfo[iClsNum].cKeyChar = ' '; /* not yet used */
	}
    if (hdr->fields.ftype[0] == 'C')
        hdr->fields.numclasses = hdr->fields.imgmax + 1 ;
    //hdr->fields.uKey = 0;
    /* don't do this - wipes out previously set info! */
    hdr->fields.iff_offset = 0;
    }

	/*	fixul older hdrs to 4.1. This assumes the fields
	 *	being set did not contain useful info.
	 */
void DragonOldImageReader::SetHdrTo401(IHEAD_OLD * hdr)
    {
    hdr->fields.bits_per_pix = 8; /* default - calling pgm can change ... */
    hdr->fields.z_scale = 1.0;	/* for 4.1 */
    hdr->fields.z_offset = 0.0;
    hdr->fields.z_unit[0] = '\0';
    hdr->fields.z_unitlen = 0;
//    hdr->fields.imgvar= 0.0;
//    hdr->fields.imgsd = 0.0;
    /* A pre-4.01 image could have georeferencing info from REGISTER. 
     * We don't want to wipe this out. 
     *
     * However, this is has a very slight risk. If an old Dragon
     * file had garbage in it's header, and the georef_init flag
     * just happened to be 1, then we could be leaving garbage
     * in the floating point fields that might cause a crash if
     * some other function tried to interpret them as floating
     * point values.  SEG 12/12/2004 
     */
    if (hdr->fields.georef_init != 1)
       {
       hdr->fields.georef_init = 1;
       hdr->fields.img_x = 0;
       hdr->fields.img_y = 0;
       hdr->fields.ref_x.v0 = 0.0;
       hdr->fields.ref_y.v0 = 0.0;
       hdr->fields.xcell_size = 1.0;
       hdr->fields.ycell_size = 1.0;
       }
    hdr->fields.charsize = 2;	/* i.e. classnames are Unicode 2-byte form */
    hdr->fields.vn = 0x401;
    }

void DRAGON_OLD_IMG_RDR_END() { puts(FIL_ID); }
