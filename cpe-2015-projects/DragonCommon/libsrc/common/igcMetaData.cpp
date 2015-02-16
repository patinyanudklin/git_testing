extern "C"
{
#include "drelease.h"
char IGCMETADATA_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.12 $$Date: 2014/04/01 07:22:21 $";
D_REL_IDSTR;
}
/*
 *	filename igcMetaData.cpp
 *		$Revision: 1.12 $ $Date: 2014/04/01 07:22:21 $	
 *
 *      ~~ Copyright 2006-2014 Kurt Rudahl and Sally Goldin
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
 ***************************************************
 *  $Id: igcMetaData.cpp,v 1.12 2014/04/01 07:22:21 rudahl Exp $
 *  $Log: igcMetaData.cpp,v $
 *  Revision 1.12  2014/04/01 07:22:21  rudahl
 *  lint esp from old mingc
 *
 *  Revision 1.11  2011/01/12 04:42:34  rudahl
 *  added new registration fields to update_georef and header
 *
 *  Revision 1.10  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.9  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.8  2007/01/02 10:31:29  goldin
 *  Add tracing, fix bug in formatting
 *
 *  Revision 1.7  2006/12/31 12:12:41  rudahl
 *  fixing up the external driver and trailer access
 *
 *  Revision 1.6  2006/11/24 11:59:05  goldin
 *  Make parameter a const
 *
 *  Revision 1.5  2006/11/17 10:44:58  goldin
 *  debug facade functions to create new meta info
 *
 *  Revision 1.4  2006/11/16 10:05:23  goldin
 *  Add new functions to update meta data from appl. programs
 *
 *  Revision 1.3  2006/11/12 07:01:06  goldin
 *  New functions to update meta info for images and vector data sets
 *
 *  Revision 1.2  2006/11/11 08:07:54  goldin
 *  Allow creation of igcmetafile based on an image
 *
 *  Revision 1.1  2006/09/29 11:36:39  goldin
 *  Begin implementation of meta data file classes
 *
 *
 *******************************************************************
 *  This is the IgcMetaData class, a new class to link together
 *   multiple image and vector files that share the same
 *   georeferencing information.
 *   The class is represented by a bare header file that contains
 *   a GUID and its own filename. All the files that belong to
 *   the same congruence class will have the same GUID and filename
 *   in their headers.
 *   This class is roughly analagous to the the Image class,
 *   and uses some of the same helper classes for reading and
 *   interpreting the header data.
 *
 *   Created by Sally Goldin, 29 September 2006
 *	
 ****************************************************************
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>	/* for offsetof() */

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
//#include "files.h"

#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "dragonHd.h"
#include "imageHdr.h"
#include "img.h"
#include "img_acc.h"
#include "imageReader.h"
#include "imageWriter.h"
#include "dragonImageReader.h"
#include "igcMetaData.h"
//#include "i18n.h"

//#include "dp.h"

Class IgcMetaData::s_class_Base("IgcMetaData","Class to represent a grouping of image or vector files by geography");

		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
IgcMetaData::IgcMetaData(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("IgcMetaData::IgcMetaData (en)");
    if (iDebug || m_iDebug)
	printf("IgcMetaData::IgcMetaData (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_pHdr = NULL;
    m_pReader = NULL;
    m_pWriter = NULL;
    zero();
    m_Handle.pMetaDataObj = this;
    logTrace("Created new IgcMetaData %p (%p)", this,m_Handle.pMetaDataObj);
    if (iTrace || m_iTrace)
	logTrace("IgcMetaData::IgcMetaData (ex)");
    if (iDebug || m_iDebug)
	printf("IgcMetaData::IgcMetaData (ex)\n");
    }
/*-------------------------------------------------------------*/
	/* initialize all values based on header info in
	 * specified file, which must exist. 
	 * Should be preceeded by zero(). 
	 * @param pczFilename	full, long path to file
	 * @return		0 if OK else negative error #:
	 */
int IgcMetaData::open(const char * pczFilename)
    {
    if (m_iTrace)
	Logger::logTrace("IgcMetaData::open (en) pczFilename='%s' ",
			 pczFilename);
    if (m_iDebug)
	printf("IgcMetaData::open (en) pczFilename='%s'\n",
			 pczFilename);
    if (m_iErrno < 0)
        {
	Logger::logTrace("IgcMetaData::init ERROR: redundant invocation ");
	if (m_iDebug)
	  printf("IgcMetaData::init ERROR: redundant invocation\n");
	m_iErrno = 0;
	zero();
	}
    logTrace("IgcMetaData::open - about to read image header");
    readImageHeader(pczFilename);
    if (m_iTrace)
       Logger::logTrace("IgcMetaData::open (ex) succeeded=%s returns x%X",
		       YESNO(m_iErrno == 0),m_iErrno);
    if (m_iDebug)
       printf("IgcMetaData::open (ex) succeeded=%s returns x%X\n",
	     YESNO(m_iErrno == 0),m_iErrno);
    
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_INITFROMFILE;
    if (m_iErrno >= 0)
        {
        m_Handle.bValid = TRUE;
        } 
    if (m_iTrace)
	Logger::logTrace("IgcMetaData::open (ex) ");
    if (m_iDebug)
	printf("IgcMetaData::open (ex) \n");
    return (m_iErrno < 0) ? m_iErrno : m_uState;
    }

/*-------------------------------------------------------------*/
	/*	Read image header and set 'm_VecFile' accordingly.
	 *	On exit, file is closed
	 *	Return TRUE if OK and set m_iErrno to 0.
	 *	If fn returns FALSE, m_iErrno is < 0 if error.
	 *	Error values are:
	 *		-50 => file not found or not readable
	 *		-60 => header completely uninitialized 
	 *		-64 => there's alread an open file in pFp,
	 *			so just leave values alone
	 *		-65 => no name supplied
	 *		-74 => file not found, or error reading hdr
	 *		-75 => file contents preclude valid interp.
	 */
BOOL IgcMetaData::readImageHeader(const char * pczFileName)
    {
    if (m_iTrace)
	Logger::logTrace("IgcMetaData::readImageHeader (en) name='%s'",
			 pczFileName);
    if (m_iDebug)
	printf("IgcMetaData::readImageHeader (en) name='%s' errno=%d\n",
			 pczFileName,m_iErrno);
    if (m_pHdr != NULL)
	m_iErrno = DERR_IMAGE_REINIT;
    else if (pczFileName == NULL)
	m_iErrno = DERR_IMAGE_NONAME;
    else if (access(pczFileName,R_OK) != 0)
	m_iErrno = DERR_FILE_ACCESS;
    else
	{
	m_pHdr = new ImageHdr(m_iDebug,m_iTrace);
	m_pReader = m_pHdr->read(pczFileName,NULL);
	if (m_pReader == NULL)
	    m_iErrno = DERR_HDR_READ;
        }
    if (m_iDebug && (m_iErrno != 0))
	printf("IgcMetaData::readImageHeader errno=%d='%s'\n",
			 m_iErrno,getErrorMessage());
    if (m_iTrace && (m_iErrno != 0))
	logTrace("IgcMetaData::readImageHeader errno=%d='%s'",
			 m_iErrno,getErrorMessage());
    if (m_iErrno == 0)
	{
	const IMAGEHDR * pImgHeader = getIMAGEHDR();
	if (! pImgHeader->bImageHdrInitialized)
	    m_iErrno = DERR_IMAGE_UNINIT;
	if (m_iDebug && (m_iErrno != 0))
	    printf("IgcMetaData::readImageHeader 2 errno=%d='%s'\n",
		   m_iErrno,getErrorMessage());
	}
    if (m_iTrace || m_iErrno)
	logTrace("IgcMetaData::readImageHeader (ex) "
		 "succeeded=%s err=%d %s ReadStat=x%X for '%s'",
		 YESNO(m_iErrno==0),m_iErrno,getErrorMessage(),
		 m_iStatus,pczFileName);
    if (m_iDebug)
	printf("IgcMetaData::readImageHeader (ex) "
		     "succeeded=%s err=%d %s ReadStat=x%X for '%s'\n",
		     YESNO(m_iErrno==0),m_iErrno,getErrorMessage(),
		     m_iStatus,pczFileName);
    return (m_iErrno == 0);
    }
/*-------------------------------------------------------------*/

        /* set to valid but not meaningful values (mostly 0 or NULL)
         * In particular set georef info to identity transform.
         * @return		0 if OK
         *			else
	 *				-54 if file close error
	 */
int IgcMetaData::zero()
    {
    int iRetval = 0;
    if (m_iTrace)
	Logger::logTrace("IgcMetaData::zero (en) ");
    if (m_iDebug)
	printf("IgcMetaData::zero (en) \n");
    if (m_pReader != NULL)
        {
	iRetval = m_pReader->close();
	delete m_pReader;
	m_pReader = NULL;
        }
    if (m_pWriter != NULL)
        {
	iRetval = m_pWriter->close();
	delete m_pWriter;
	m_pWriter = NULL;
        }
    if (m_pHdr != NULL)
        {
        delete m_pHdr;
	m_pHdr = NULL;
        }
    m_Handle.bValid = FALSE;
    if (m_iTrace)
       Logger::logTrace("IgcMetaData::zero (ex) ");
    if (m_iDebug)
       printf("IgcMetaData::zero (ex) \n");
    return iRetval;
    }

/*-------------------------------------------------------------*/


	/* set up a IgcMetaData for output. This could be 
         * a brand new file or it could be based on an existing
         * file, depending on the value of pSrcMetaData or pSrcImageData. 
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcMetaData	If non-null, metadata file to copy
         * @param pSrcImage If non-null, use the info from this image header to copy
         *        will use pSrcMetaData preferentially if both are non-null.
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
int IgcMetaData::create(const char * pczFilename, BOOL bOverwrite, 
			const IgcMetaData * pSrcMetaData, const Image* pSrcImage)
    {
    if (m_iTrace)
	Logger::logTrace("IgcMetaData::create (en) file='%s' from meta source '%s'"
			 " overwrite=%s ",
			 pczFilename,(pSrcMetaData != NULL) ?
                         pSrcMetaData->m_Handle.czFullFilename : "NULL",
                         YESNO(bOverwrite));
    if (m_iDebug)
	printf("IgcMetaData::create (en) file='%s' from meta source '%s'"
			 "overwrite=%s \n",
			 pczFilename,(pSrcMetaData != NULL) ?
                         pSrcMetaData->m_Handle.czFullFilename : "NULL",
                         YESNO(bOverwrite));
    if (!bOverwrite && (access(pczFilename,F_OK)==0))
	m_iErrno = DERR_FILE_ALREADY;
    else if ((pSrcMetaData != NULL)  
             && (pSrcMetaData->m_uState != IMG_INITFROMFILE)
	     && (pSrcMetaData->m_uState != IMG_HDRWRITTEN))
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if ((pSrcImage != NULL)  
             && (pSrcImage->getState() != IMG_INITFROMFILE)
	     && (pSrcImage->getState() != IMG_HDRWRITTEN))
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (m_iErrno == 0)  /* create the output header */
        {
	IMGTYPE_T format = IT_IGC_META;  
	if ((m_pHdr = new ImageHdr(m_iDebug,m_iTrace)) == NULL)
	    m_iErrno = DERR_MEM_ALLOC;
	else
	    {
            if (pSrcMetaData != NULL)
	       {
	       m_pHdr->copy(pSrcMetaData->getImageHeader(),format,"M");
	       }
            else if (pSrcImage != NULL)
	       {
	       m_pHdr->copy(pSrcImage->getImageHeader(),format,"M");
               /* set the extent if the source image has geographic coordinates */
               if (pSrcImage->getIMAGEHDR()->ref_x.v0 != 0)
		  {
		  VERTEX minExtent;
		  VERTEX maxExtent;
		  BOOL bFlipped;
                  bFlipped =  calculateHeaderExtent(pSrcImage->getIMAGEHDR(), 
                                &minExtent,&maxExtent);
		  update_extent(minExtent.x, minExtent.y,maxExtent.x, maxExtent.y);
                  } 
               }
            else  /* init with default values */
	       {
	       m_pHdr->init(format,"M",0,0,8,1,0, pczFilename);
	       m_pHdr->update_text(pczFilename,NULL,"IGC Meta File",NULL,
				   NULL,NULL,NULL,NULL,"M");
               }
	    strcpy_array(m_Handle.czFullFilename,pczFilename);
            m_Handle.bValid = TRUE;
            /* generate the GUID and set the filename */
            generateIdentifyingInfo();
            }
	}
    if (m_iTrace)
        {
	logTrace("IgcMetaData::create (ex) status is %d (%s)", 
		 m_iErrno,getErrorMessage());
      	}
    if (m_iDebug)
        {
	printf("IgcMetaData::create status is %d (%s)\n", 
	       m_iErrno,getErrorMessage());
        }
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_WRITABLE;
    return m_iErrno;
    }

/*-------------------------------------------------------------*/

	/* change text information (except classnames, unitnames) 
	 * for a meta file. This is just a wrapper around the ImageHdr function.
	 * Only the params with non-NULL vals will be changed.
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int IgcMetaData::update_text(const char * pczTitle,
			  const char * pczId,
			  const char * pczComment,
			  const char * pczSource,
			  const char * pczScene,
			  const char * pczSubscene,
			  const char * pczBand)
    {
    if (m_pHdr == NULL)
       return DERR_IMAGE_UNINIT;
    else
       return m_pHdr->update_text(pczTitle,
			          pczId,
				  pczComment,
				  pczSource,
				  pczScene,
				  pczSubscene,
				  pczBand,
				  NULL,"M");
    } 


	/* change georeferencing information information for a vector file.
	 * This is just a wrapper around the ImageHdr function.
	 *
	 * NOTE: ref_x, ref_y, pczProjection, pczUnitname 
	 *	 may be NULL to indicate no change
	 *	 but other args MUST be supplied.
	 *
	 * @param img_x    	+/- pixel num of origin/fixed point-usually 0
	 * @param img_y    	+/- line number of fixed point - usually 0 
	 * @param ref_x    	NULL or ptr to map/ref x coord of fixed point
	 * @param ref_y    	NULL or ptr to map/ref y coord of fixed point 
	 * @param xcell_size  	size of one cell in X direction at fixed pt 
	 * @param ycell_size 	size of one cell in Y direction at fixed pt
	 *                    	if negative, the corresponding axis is reversed
	 *		      	relative to the image coordinate system.
	 * @param pczProjection NULL or code for map proj'n 
	 * @param pczUnitname	NULL or map unit name 
	 * @param pczDateTime	NULL or date, time of image acquisition
	 *			in form yyyy:mm:dd HH:MM:SS
	 * @param pczUTMZone	NULL or utmzone in form [1-60][N|S]
	 * @param iRegistered	<0 => don't change 0 => FALSE >0 => TRUE
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int IgcMetaData::update_georef(int img_x, int img_y, 
			    const MapCoord * ref_x, const MapCoord * ref_y,
			    double xcell_size, double ycell_size,
			    const char* pczProjection, const char* pczUnitname,
			    const char * pczDateTime,const char * pczUTMZone,
			    int iRegistered)
    {
    if (m_iTrace)
       logTrace("IgcMetaData::update_georef (en) - xcell_size is %f, ycell_size is %f",
		xcell_size, ycell_size);

    if (m_pHdr == NULL)
       return DERR_IMAGE_UNINIT;
    else
       return m_pHdr->update_georef(img_x, img_y, ref_x, ref_y,
			    xcell_size, ycell_size,
			    pczProjection, pczUnitname,
			    pczDateTime,pczUTMZone,
			    iRegistered);
    }

	/* change metafile information 
	 * Strictly speaking this should only be called once for
         * an IgcMetaFile.
	 * Only the params with non-NULL vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int IgcMetaData::update_metainfo(const char * pczMetafile,
			  const char * pczGuid)
    {
    if (m_iTrace)
       logTrace("IgcMetaData::update_metainfo (en) - filename %s, GUID %s",
		pczMetafile, pczGuid);

    if (m_pHdr == NULL)
       return DERR_IMAGE_UNINIT;
    else
       return m_pHdr->update_metainfo(pczMetafile, pczGuid);
    if (m_iTrace)
       logTrace("IgcMetaData::update_metainfo (ex)");
    }

	/* change extent information for an existing image.
	 * This may be invoked after writing the header
	 *
	 * NOTE: all values must be supplied. If all four values are
         * 0 then we assume extent is not initialized.
	 *
	 * @param minX    	min X value in extent
	 * @param minY    	min Y value in extent
	 * @param maxX    	max X value in extent
	 * @param maxY    	max Y value in extent
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int IgcMetaData::update_extent(double minX, double minY,
			       double maxX, double maxY)
    {
    if (m_iTrace)
       logTrace("IgcMetaData::update_extent (en) - %f,%f to %f, %f",
		minX, minY, maxX, maxY);

    if (m_pHdr == NULL)
       return DERR_IMAGE_UNINIT;
    else
       return m_pHdr->update_extent(minX, minY, maxX, maxY);
    }


/*-------------------------------------------------------------*/

	/*	write vector header and close output file
	 *	On exit, file is closed
	 *	Return 0 if OK
	 *	Error values are:
	 *		-60 => header completely uninitialized 
	 *		-64 => there's already an open writer,
	 *			so just leave values alone
	 *		-65 => no name supplied
	 *		-66 => image state conflict
	 *		-69 => no header writer found
	 */
int IgcMetaData::writeHeader()
    {
    int iStat = 0;
    if (m_iTrace)
	Logger::logTrace("IgcMetaData::writeHeader (en) "
			 "name='%s' state=%s",
			 m_Handle.czFullFilename,Image::getStateName(m_uState));
    if (m_iDebug)
	printf("IgcMetaData::writeHeader (en) "
	       "name='%s' errno=%d\n\tstate=%s\n",
		m_Handle.czFullFilename,m_iErrno,Image::getStateName(m_uState));
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    if (strlen(m_Handle.czFullFilename) == 0)
	m_iErrno = DERR_IMAGE_NONAME;
    else if ((m_uState != IMG_WRITABLE) && (m_uState != IMG_CHANGED))   
        // thus cannot use for readable image
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (m_pWriter != NULL)
	m_iErrno = DERR_IMAGE_REINIT;
    else if ((m_pWriter = m_pHdr->imageWriterFactory(m_pHdr->getImageType())) == NULL)
	m_iErrno = DERR_UNSUP_FORMAT;
    else
        {
	long lOffset = 0L; 
        /* tells us where image data starts */
	if (m_iDebug)
   	    {
	    printf("IgcMetaData::writeHeader "
		   "about to init ImageWriter: m_pWriter is %p, and hdr at %p\n", 
		   m_pWriter, m_pHdr);
	    }
	m_pWriter->init(m_pHdr,&lOffset);
	if (m_iDebug)
	    printf("IgcMetaData::writeHeader setting data offset to %ld\n", lOffset);
	m_pHdr->setDataOffset(lOffset);
	}
    if ((m_iErrno == 0)
    	    && (! m_pWriter->writeHeader(m_Handle.czFullFilename,
            pImgHeader,&iStat)))
	m_iErrno = iStat;
    m_pHdr->clearUpdatesNeeded();
    m_bHdrUpdated = FALSE;     /* TRUE => need to rewrite header */
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_HDRWRITTEN;
    if (m_iDebug)
	printf(m_pHdr->dump(1,"IgcMetaData::writeHeader (ex)"));
    if (m_iTrace)
	logTrace(m_pHdr->dump(1,"IgcMetaData::writeHeader (ex)"));
    return m_iErrno;
    }

/**/
/* private function to generate and set the identifying info 
 * for a metafile, i.e. its filename and GUID.
 * @return 0 if okay, -1 for error.
 */
int IgcMetaData::generateIdentifyingInfo()
    {
    int status = 0;
    time_t timeValue = 0; /* ulong long in new mingw, not in old */
    char buffer[256];
    logTrace("IgcMetaData::generateIdentifyingInfo (en)");
    sprintf(buffer,"%lld",(unsigned long long)time(&timeValue));
    char * newGUID = buffer;  /* generate here */
    char* pLastSlash = strrchr(m_Handle.czFullFilename,'/');
    if (pLastSlash == NULL)  /* try backward slashes */
       pLastSlash = strrchr(m_Handle.czFullFilename,'\\');
    if (pLastSlash != NULL)
       pLastSlash++;
    else
       pLastSlash = m_Handle.czFullFilename;
    status = update_metainfo(pLastSlash, newGUID);
    logTrace("IgcMetaData::generateIdentifyingInfo (ex)");
    return status;
    }

/***********************************************************************/
/* Debugging functions */


	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
const char * IgcMetaData::dump(int detail, const char * pczTitle) const
    {
    const char* pczHead = NULL; 
    printf("%s\n",pczTitle);
    pczHead = m_pHdr->dump(detail,"Igc Meta File Header");
    printf(pczHead);
    return pczHead;
    }


extern "C"
{
 /* Facade function to create a new metafile based
  * on an initialized image.
  * @param metaFileName  Name of metafile to create including path
  * @param pSrcImage  pointer to IMAGE to use for source data
  * @return 0 if successful, else negative for error.
  */
int createMetaInfo(const char* pczMetaFileName, const IMAGE* pSrcImage)
   {
   int error = 0;
   logTrace("igcMetaData::createMetaInfo (en) pczMetaFileName %s",
	    pczMetaFileName);
   IgcMetaData oIgcfile(0,0);

   error = oIgcfile.create(pczMetaFileName,TRUE,NULL,pSrcImage->pImageObj);
   if (error >= 0)
       error = oIgcfile.writeHeader();
   else
       logTrace("Error %d returned from igcMetaData->create\n", error);
   if (error < 0)
       {
       logTrace("Error %d returned from igcMetaData->writeHeader\n", error);
       }
   return error;
   }

/* Facade function - update the header information for an image based on
 * the identifying information in the meta file. DOES NOT REWRITE IMAGE HEADER 
 * @param pImage  Pointer to image to update
 * @param pczMetaFileName   Name of metafile including path
 * @return 0 if success, negative for error. 
 */
int updateImageFromMetaFile(const IMAGE* pImage, const char* pczMetaFileName)  
   {
   logTrace("igcMetaData::updateImageFromMetaFile (en) pImage %lp, meta file %s",
            pImage, pczMetaFileName);    
   int status = 0;
   IgcMetaData igcFile(0,0);
   status = igcFile.open(pczMetaFileName);
   if (status >= 0)
      {
      const IMAGEHDR * pHdr = igcFile.getIMAGEHDR();
      Image * pRealImage = pImage->pImageObj;
      status = pRealImage->update_metainfo(pHdr->pczMetafile,pHdr->pczGUID);
      }
   logTrace("igcMetaData::updateImageFromMetaFile (ex) status is %d", status);
   return status;
   }  
 

}  /* end extern C */
/***********************************************************************/

void IgcMetaData_END() { puts(FIL_ID); }

/************************************************************************/
#ifdef TEST

extern "C"
{

void usage()
    {
    printf ("Test IgcMetaData class by reading some file header\n");
    printf ("Usage: IgcMetaData.TEST inputfilepath outputfilepath\n");
    exit(1);
    }

int main(int argc, char ** argv)
    {
    MapCoord refx;
    MapCoord refy;

    char czFilename[PATH_MAX] = "";
    char czOutFilename[PATH_MAX] = "";
    if (argc < 3)
	usage();
    strcpy(czFilename,argv[1]);
    strcpy(czOutFilename,argv[2]);
    
    printf("+++ Try to read existing file \n");
    IgcMetaData igcfile(0,0);
    int error = igcfile.open(czFilename);
    if (error < 0)
        {
        printf("Error %d trying to open file %s\n", error,czFilename);
        exit(0);
        }
    igcfile.dump(2,"Input IGC meta data file");
    printf("+++ Try to open output file \n");
    IgcMetaData oIgcfile(0,0);
    error = oIgcfile.create(czOutFilename,TRUE,&igcfile,NULL);
    if (error < 0)
        {
        printf("Error %d trying to create output file\n",error);
        exit(0);
        }
    refx.v0 = 10000.0;
    refy.v0 = 20000.0;

    error = oIgcfile.update_georef(0,0,&refx,&refy,10.0,-10.0,NULL,"meters",
				   NULL,NULL,-1); // ~~~ ?
    if (error < 0)
        {
        printf("Error %d trying to update georeferencing \n",error);
        exit(0);
        }
    error = oIgcfile.update_extent(100.0,200.0, 1200.0, 1240.0);
    if (error < 0)
        {
        printf("Error %d trying to update extent \n",error);
        exit(0);
        }

    error = oIgcfile.writeHeader();
    if (error < 0)
        {
        printf("Error %d trying to write header\n",error);
        exit(0);
        }
    oIgcfile.dump(2,"Output IGC Meta File");

    return 0;
    }

} // end of extern C

#endif /* TEST */










