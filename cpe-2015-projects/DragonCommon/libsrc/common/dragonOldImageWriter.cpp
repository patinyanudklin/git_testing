#include "drelease.h"
char DRAGOLDIMAGEWRTR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.10 $$Date: 2014/12/29 03:28:29 $";
D_REL_IDSTR;

/*
 *	filename dragonOldImageWriter.cpp
 *		$Revision: 1.10 $ $Date: 2014/12/29 03:28:29 $	
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
 *   $Id: dragonOldImageWriter.cpp,v 1.10 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: dragonOldImageWriter.cpp,v $
 *   Revision 1.10  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.9  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.8  2007/08/02 12:32:45  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.7  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.6  2005/08/18 03:48:36  rudahl
 *   fixes to scaling
 *
 *   Revision 1.5  2005/07/04 13:37:55  rudahl
 *   working with toollibs
 *
 *   Revision 1.4  2005/07/03 13:30:52  rudahl
 *   improving createImage
 *
 *   Revision 1.3  2005/06/26 06:18:15  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.2  2005/06/19 08:46:27  rudahl
 *   prelim revisions
 *
 *   Revision 1.1  2005/06/19 08:30:17  rudahl
 *   initial from mehitabel
 *
 *
 ****************************************************************
 * 
 * Define a class for writing old-format headers to Dragon image files.
 * Arguably this will be used only during a transition period
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *              san     San Ratanasanya
 *		(add more names here)
 *
 *	Revision History
 * 5.7	2005-06-19 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 	2005-8-17 ktr	fixed problem recognizing invalid calibration fields
 *	2005-9-17 ktr	enhanced dump()
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcat_array */
#include "dragon-errors.h"
#include "wfutil.h"
#include "ob.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "dragonHd.h"
#include "dhead-old.h"
#include "imageWriter.h"
#include "dragonOldImageWriter.h"

static Class DragonOldImageWrtr_class("DragonOldImageWriter",
				   "Class for writing old Dragon image files");

const char * DragonOldImageWriter::s_czTrailerNames[] = {TRAILER_RECORD_NAMES};

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
DragonOldImageWriter::DragonOldImageWriter(int iDebug, int iTrace)
    {
    m_pClass = &DragonOldImageWrtr_class; 
    m_pClass->setSubClass(ImageWriter::getObjectClass());
    if (iDebug > m_iDebug)
      m_iDebug = iDebug;
    if (iTrace > m_iTrace)
      m_iTrace = iTrace;
    if (m_iDebug)
	printf("DragonOldImageWriter constructor\n");
    m_uHeaderChecksum = 0;
    m_pHdr = NULL;
    }

		// write the file 
		// @param pczFilename	name of file to write
		// @param pSrcHdr	pointer to IMAGEHDR struct to write.
		// @param pErrNum	pointer to variable to receive errnum
		// @return		TRUE if OK
BOOL DragonOldImageWriter::writeHeader(const char * pczFilename,
				       const IMAGEHDR * pSrcHdr,
				       int * pErrNum)
    {
    IHEAD_OLD * pDrgHdr = (IHEAD_OLD *)&s_outbuf;
    int iStat = 0;
    if (m_iDebug)
	printf("DragonOldImageWriter::writeHeader (en) bits_per_pix=%d\n",
	       pSrcHdr->bits_per_pix);
    *pErrNum = 0;
    memset(s_outbuf,0,sizeof(s_outbuf));
    iStat = copyFields(pDrgHdr,pSrcHdr);
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
    return (*pErrNum == 0);
    }

		// rewrite selected header info if changed
		// @return		0 if OK else
int DragonOldImageWriter::rewriteHeader(const Image * pImg)
    {
    IHEAD_OLD dragonHdr;
    int iStat = 0;
    const IMAGEHDR * pHdr = pImg->getIMAGEHDR();
    if (m_iDebug)
	printf("DragonOldImageWriter::rewriteHeader (en) histo=%p\n",
	       pHdr->histo);
    memset(&dragonHdr,0,sizeof(dragonHdr));
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
    return iStat;
    }

		// append trailer on the file : closed on return
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
int DragonOldImageWriter::writeTrailer(const char * pczFilename,
				    const IMAGEHDR * pHdr,
				    UINT32 uDataCheck)
    { 
    return 0;
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
int DragonOldImageWriter::init(ImageHdr * pImageHdr,
	 long * plOffset) 
    { 
    *plOffset=DHEAD; 
    return 0; 
    }

	/* calc and return the size of the header plus image data, or 0
	 * This cannot be done until the header has been written
	 */
ulong DragonOldImageWriter::getTrailerOffset() const
    {
    return 0;
    }

		// return a formatted dump of the class member
const char * DragonOldImageWriter::dump(int detail, 
					   const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "DragonOldImageWriter dump imagehdr=%p fp=%p",
	     m_pHdr,m_pFp);
    return s_czDumpBuf;
    }

/* make file header agree with passed header
 * @param pDestHdr 	DHEAD-sized buffer
 *                  	which should be filled from pSrcHdr info 
 * @param pSrcHdr       Pointer to IMAGEHDR to use as the source for 
 *                      header values   
 * @return        <0 if err (missing argument)
 */
int DragonOldImageWriter::copyFields(IHEAD_OLD * pDestHdr,
				     const IMAGEHDR * pSrcHdr)
    {
    int iRetVal = 0;
    if (! pSrcHdr->bImageHdrInitialized)
	return DERR_IMAGE_UNINIT;
    strcpy_array(pDestHdr->fields.ftype,pSrcHdr->ftype);
    pDestHdr->fields.size[0]       = pSrcHdr->size[0];
    pDestHdr->fields.size[1] 	   = pSrcHdr->size[1];
    pDestHdr->fields.bits_per_pix  = pSrcHdr->bits_per_pix;
    pDestHdr->fields.uEncoding     = pSrcHdr->uEncoding;
    pDestHdr->fields.iff_offset    = pSrcHdr->iff_offset;
    pDestHdr->fields.uKey          = pSrcHdr->uKey;
    
#if DRAGON_VER >= 6
    pDestHdr->fields.imgmean	= pSrcHdr->m_ihImgmean;
    pDestHdr->fields.imgmax 	= pSrcHdr->m_ihImgmax;
    pDestHdr->fields.imgmin 	= pSrcHdr->m_ihImgmin;
    pDestHdr->fields.imgvar 	= pSrcHdr->m_dhImgvar;
    pDestHdr->fields.imgsd 	= pSrcHdr->m_dhImgsd;
#else
    pDestHdr->fields.imgmean  = pSrcHdr->imgmean;
    pDestHdr->fields.imgmax   = pSrcHdr->imgmax;
    pDestHdr->fields.imgmin   = pSrcHdr->imgmin;
    pDestHdr->fields.imgvar   = pSrcHdr->imgvar;
    pDestHdr->fields.imgsd    = pSrcHdr->imgsd;
#endif
    pDestHdr->fields.z_scale 	= pSrcHdr->z_scale;
    pDestHdr->fields.z_offset 	= pSrcHdr->z_offset;
    pDestHdr->fields.dScaleFactor 	= pSrcHdr->dScaleFactor;
    pDestHdr->fields.uScaleFactor 	= pSrcHdr->uScaleFactor;
    pDestHdr->fields.dScaleOffset 	= pSrcHdr->dScaleOffset;

    /* copy histogram */
    if (pSrcHdr->histo != NULL)
        {
	for (int j=0; j<HDR_HIST_LEN; j++)
	    pDestHdr->fields.histo[j] = pSrcHdr->histo[j];
	}
 
    if ((pSrcHdr->z_unit == NULL) || (strlen(pSrcHdr->z_unit) == 0))
	pDestHdr->fields.z_unit[0] = '\0';
    else
        {
	strcpy_array(pDestHdr->fields.z_unit,pSrcHdr->z_unit);
        }

    if (pSrcHdr->h_title != NULL)
        {
	pDestHdr->fields.fnlen = strlen(pSrcHdr->h_title); 
        strcpy_array(pDestHdr->fields.fname,pSrcHdr->h_title);
        }

    if (pSrcHdr->comment != NULL)
        {
	pDestHdr->fields.comment[0] = strlen(pSrcHdr->comment); 
        strncpy(pDestHdr->fields.comment+1,pSrcHdr->comment,46);
	}
    if (pSrcHdr->source != NULL)
        {
	pDestHdr->fields.source[0] = strlen(pSrcHdr->source); 
        strncpy(pDestHdr->fields.source+1,pSrcHdr->source,3);
	}
    if (pSrcHdr->scene != NULL)
        {
	pDestHdr->fields.scene[0] = strlen(pSrcHdr->scene); 
        strncpy(pDestHdr->fields.scene+1,pSrcHdr->scene,16);
	}
    if (pSrcHdr->subscene != NULL)
        {
	pDestHdr->fields.subscene[0] = strlen(pSrcHdr->subscene); 
        strncpy(pDestHdr->fields.subscene,pSrcHdr->subscene,16);
	}
     if (pSrcHdr->band != NULL)
        {
	pDestHdr->fields.band[0] = strlen(pSrcHdr->band); 
        strncpy(pDestHdr->fields.band,pSrcHdr->band,3);
	}
     /* set magical word */
     char cMagic[7]={'G','R','S','I',4,5};
     strncpy(pDestHdr->fields.cMagic,cMagic,6); // this is a cheat

     /* next copy or derive the GEOREF fields */
    pDestHdr->fields.img_x = pSrcHdr->img_x;
    pDestHdr->fields.img_y = pSrcHdr->img_y;
    mapCoord_copy(&(pSrcHdr->ref_x),&(pDestHdr->fields.ref_x));
    mapCoord_copy(&(pSrcHdr->ref_y),&(pDestHdr->fields.ref_y));
    pDestHdr->fields.xcell_size = pSrcHdr->xcell_size;
    pDestHdr->fields.ycell_size = pSrcHdr->ycell_size;
    
    if (pSrcHdr->czProjection!= NULL)
        strcpy_array(pDestHdr->fields.czProjection,pSrcHdr->czProjection);
    if (pSrcHdr->unitname!= NULL)
        strcpy_array(pDestHdr->fields.unitname,pSrcHdr->unitname);

    pDestHdr->fields.georef_init = pSrcHdr->georef_init;
    if (pSrcHdr->uNumLabels)
        {
	size_t uMax = 0;
	iRetVal = convertHeaderClassNames(pDestHdr,&uMax);
	}
    return iRetVal;
    }

void DragonOldImageWriter::mapCoord_copy(const MapCoord * src,
					 MapCoord_old * dest)
    {
    dest->v0 = src->v0;
    dest->tag = (UINT32) src->ulTag;
    dest->v1 = (SINT32) src->v1;
    dest->v2 = (SINT32) src->v2;
    }

int DragonOldImageWriter::convertHeaderClassNames(const IHEAD_OLD * pSrcHdr,
                                                    size_t * pMaxLabelLen)
    {
    return DERR_FN_NOTIMPL;
    }

void DRAGONOLDIMAGEWRITER_END() { puts(FIL_ID); }

