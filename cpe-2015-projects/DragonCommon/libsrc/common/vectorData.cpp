extern "C"
{
#include "drelease.h"
char VECTORDATA_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.24 $$Date: 2014/04/01 07:22:21 $";
D_REL_IDSTR;
}
/*
 *	filename vectordata.cpp
 *		$Revision: 1.24 $ $Date: 2014/04/01 07:22:21 $	
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
 *  $Id: vectorData.cpp,v 1.24 2014/04/01 07:22:21 rudahl Exp $
 *  $Log: vectorData.cpp,v $
 *  Revision 1.24  2014/04/01 07:22:21  rudahl
 *  lint esp from old mingc
 *
 *  Revision 1.23  2011/01/12 04:42:34  rudahl
 *  added new registration fields to update_georef and header
 *
 *  Revision 1.22  2008/09/14 10:06:19  rudahl
 *  error setting extents in shapefile
 *
 *  Revision 1.21  2008/09/12 11:42:23  rudahl
 *  added handling of extents, georef header fields; 
 *  new create() for de-novo files
 *
 *  Revision 1.20  2008/06/12 13:48:15  goldin
 *  implement rewriteHeader for vectors
 *
 *  Revision 1.19  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.18  2007/08/15 11:00:49  goldin
 *  Allow VEC files open for read to have their header updated
 *
 *  Revision 1.17  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.16  2007/02/25 10:35:19  goldin
 *  Exposed code to set shape type for Shapefiles
 *
 *  Revision 1.15  2007/02/03 02:06:19  rudahl
 *  revised tracing
 *
 *  Revision 1.14  2006/12/31 12:12:41  rudahl
 *  fixing up the external driver and trailer access
 *
 *  Revision 1.13  2006/11/12 07:01:06  goldin
 *  New functions to update meta info for images and vector data sets
 *
 *  Revision 1.12  2006/09/29 11:36:39  goldin
 *  Begin implementation of meta data file classes
 *
 *  Revision 1.11  2006/09/29 04:48:08  goldin
 *  Dump all vector coords in VECFEATUREdump
 *
 *  Revision 1.10  2006/09/17 13:33:35  goldin
 *  deal with special cases
 *
 *  Revision 1.9  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.8  2006/08/11 07:34:22  goldin
 *  Fix logic problems
 *
 *  Revision 1.7  2006/08/09 14:01:26  goldin
 *  Fix logic error in test code
 *
 *  Revision 1.6  2006/08/09 10:38:07  goldin
 *  Continued work on vector read/write/scale
 *
 *  Revision 1.5  2006/08/09 09:48:09  goldin
 *  Adding support for writing shapefiles
 *
 *  Revision 1.4  2006/08/06 11:23:44  goldin
 *  Working on georeferenced vectors
 *
 *  Revision 1.3  2006/08/05 10:33:54  goldin
 *  fix coord transform calculation
 *
 *  Revision 1.2  2006/08/04 11:06:40  goldin
 *  Create class hierarchy similar to that for image classes
 *
 *  Revision 1.1  2006/08/04 04:32:34  goldin
 *  Rename VectorFile to VectorData
 *
 *  Revision 1.4  2006/08/04 04:29:51  goldin
 *  Create new test for vector files in dragonImageReader
 *
 *  Revision 1.3  2006/07/30 07:55:00  goldin
 *  Adding functionality
 *
 *  Revision 1.2  2006/07/29 11:12:57  goldin
 *  continue to add functionality
 *
 *  Revision 1.1  2006/07/24 13:26:04  goldin
 *  New VectorFile class
 *
 *
 *******************************************************************
 *  This is the VectorData class, a new class to handle
 *   reading, writing and transformation of OpenDragon vector data,
 *   and eventually, other vector formats.
 *   This class is roughly analagous to the the Image class,
 *   and uses some of the same helper classes for reading and
 *   interpreting the header data.
 *
 *   Created by Sally Goldin, 14 July 2006
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
#include "dhead.h"
#include "dragonHd.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"
#include "imageWriter.h"
#include "dragonImageReader.h"
#include "vectorData.h"
#include "vectorDataReader.h"
#include "dragonVectorDataReader.h"
#include "shapeVectorDataReader.h"
#include "vectorDataWriter.h"
#include "dragonVectorDataWriter.h"
#include "shapeVectorDataWriter.h"
//#include "i18n.h"

#include "dragonOb.h"
#include "logger.h"
//#include "dp.h"

#define DRAGON_FILE_SIGN "DragonImg"

Class VectorData::s_class_Base("VectorData",
			       "Class to represent a vector data source or sink");

		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
VectorData::VectorData(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("VectorData::VectorData (en)");
    if (iDebug || m_iDebug)
	fprintf(stderr,"VectorData::VectorData (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_iHasHeader = -1;
    m_pHdr = NULL;
    m_pReader = NULL;
    m_pWriter = NULL;
    m_pVReader = NULL;
    m_pVWriter = NULL;
    zero(); // init m_VecFile
    m_VecFile.pVectorDataObj = this;
    if (iTrace || m_iTrace)
	logTrace("VectorData::VectorData (ex)");
    if (iDebug || m_iDebug)
	fprintf(stderr,"VectorData::VectorData (ex)\n");
    }

/*-------------------------------------------------------------*/
	/* initialize all values based on header info in
	 * specified file, which must exist. 
	 * Should be preceeded by zero(). 
	 * @param pczFilename	full, long path to file
	 * @return		0 if OK else negative error #:
	 */
int VectorData::open(const char * pczFilename)
    {
    if (m_iTrace)
	Logger::logTrace("VectorData::open (en) pczFilename='%s' ",
			 pczFilename);
    if (m_iDebug)
	fprintf(stderr,"VectorData::open (en) pczFilename='%s'\n",
			 pczFilename);
    if (m_iErrno < 0)
        {
	Logger::logTrace("VectorData::init ERROR: redundant invocation "
		 "old='%s' new='%s'",
		 m_VecFile.filename,pczFilename);
	if (m_iDebug)
	    fprintf(stderr,"VectorData::init ERROR: redundant invocation "
		 "old='%s' new='%s'\n",
		 m_VecFile.filename,pczFilename);
	m_iErrno = 0;
	zero();
	}
    /* Vector files that lack georeferencing will not
     * necessarily have a header.
     */
    if (headerExists(pczFilename))
        {
        logTrace("VectorData::open - about to read image header");
        readImageHeader(pczFilename);
	if (m_iTrace)
	    Logger::logTrace("VectorData::open (ex) succeeded=%s returns x%X",
			   YESNO(m_iErrno == 0),m_iErrno);
	if (m_iDebug)
	    fprintf(stderr,"VectorData::open (ex) succeeded=%s returns x%X\n",
		 YESNO(m_iErrno == 0),m_iErrno);
        }
    else  /* create new in-memory header with default values */
        {
	m_pHdr = new ImageHdr(m_iDebug,m_iTrace);
        m_pHdr->init(IT_DRAGON,"V",0,0,8,1,0, pczFilename);
        m_pHdr->update_text(NULL,NULL,"Vector File",NULL,
                            NULL,NULL,NULL,NULL,"V");
	strcpy_array(m_VecFile.filename,pczFilename);
        }
    m_pVReader = vectorDataReaderFactory(pczFilename);
    if (m_pVReader == NULL)
        {
        m_iErrno = DERR_UNSUP_FORMAT; 
        }

    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_INITFROMFILE;
    if (m_iErrno >= 0)
        {
        m_VecFile.fileAccess = FILEACCESS_INPUT;
        m_VecFile.bValid = TRUE;
        } 
    if (m_iTrace)
	Logger::logTrace("VectorData::open (ex) ");
    if (m_iDebug)
	fprintf(stderr,"VectorData::open (ex) \n");
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
BOOL VectorData::readImageHeader(const char * pczFileName)
    {
    if (m_iTrace)
	Logger::logTrace("VectorData::readImageHeader (en) name='%s'",
			 pczFileName);
    if (m_iDebug)
	fprintf(stderr,"VectorData::readImageHeader (en) name='%s' errno=%d\n",
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
	fprintf(stderr,"VectorData::readImageHeader errno=%d='%s'\n",
			 m_iErrno,getErrorMessage());
    if (m_iTrace && (m_iErrno != 0))
	logTrace("VectorData::readImageHeader errno=%d='%s'",
			 m_iErrno,getErrorMessage());
    if (m_iErrno == 0)
	{
	const IMAGEHDR * pImgHeader = getIMAGEHDR();
	if (! pImgHeader->bImageHdrInitialized)
	    m_iErrno = DERR_IMAGE_UNINIT;
	else
	    {
	    strcpy_array(m_VecFile.filename,pczFileName);
	    }

	if (m_iDebug && (m_iErrno != 0))
	    fprintf(stderr,"VectorData::readImageHeader 2 errno=%d='%s'\n",
		   m_iErrno,getErrorMessage());
	}
    if (m_iTrace || m_iErrno)
	logTrace("VectorData::readImageHeader (ex) "
		 "succeeded=%s err=%d %s ReadStat=x%X for '%s'",
		 YESNO(m_iErrno==0),m_iErrno,getErrorMessage(),
		 m_iStatus,pczFileName);
    if (m_iDebug)
	fprintf(stderr,"Vector::readImageHeader (ex) "
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
int VectorData::zero()
    {
    int iRetval = 0;
    if (m_iTrace)
	Logger::logTrace("VectorData::zero (en) ");
    if (m_iDebug)
	fprintf(stderr,"VectorData::zero (en) \n");
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
    if (m_pVReader != NULL)
        {
        delete m_pVReader;
	m_pVReader = NULL;
        }
    if (m_pVWriter != NULL)
        {
        delete m_pVWriter;
	m_pVWriter = NULL;
        }
    m_VecFile.bValid = FALSE;
    memset(m_VecFile.filename,0,sizeof(m_VecFile.filename));
    m_VecFile.fileAccess = FILEACCESS_NONE;
    // this set of values will cause update_extents to
    // believe 'not yet initialized'
    m_VecFile.minExtent.x = 1000000000.0;
    m_VecFile.minExtent.y = 1000000000.0;
    m_VecFile.minExtent.z = 1000000000.0;
    m_VecFile.maxExtent.x = 0.0; 
    m_VecFile.maxExtent.y = 0.0; 
    m_VecFile.maxExtent.z = 0.0; 
    m_VecFile.featureCount = -1;  /* not initialized */
    if (m_iTrace)
       Logger::logTrace("VectorData::zero (ex) ");
    if (m_iDebug)
       fprintf(stderr,"VectorData::zero (ex) \n");
    return iRetval;
    }

/*-------------------------------------------------------------*/

	/* set up a VectorData for output. This could be 
         * a brand new file or it could be based on an existing
         * file, depending on the value of pSrcVectors. 
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcVectors	If non-null, vector file to copy
	 * @param pSrcData	If non-null, vector data to initialize from
	 *      (pSrcVectors and pSrcData cannot both be supplied)
	 * @param vectorFormat	If pSrcVectors is null 
	 *			and this is a valid IT_* vector constant, 
	 *			use it to determine what format to create.
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
int VectorData::create(const char * pczFilename, BOOL bOverwrite,
		       const VectorData * pSrcVectors, 
		       IMGTYPE_T vectorFormat)
    {
    if (m_iTrace)
	Logger::logTrace("VectorData::create (en) file='%s' from source '%s'"
			 "overwrite=%s ",
			 pczFilename,(pSrcVectors != NULL) ?
                         pSrcVectors->m_VecFile.filename : "NULL",
                         YESNO(bOverwrite));
    if (m_iDebug)
	fprintf(stderr,"VectorData::create (en) file='%s' from source '%s'"
			 "overwrite=%s \n",
			 pczFilename,(pSrcVectors != NULL) ?
                         pSrcVectors->m_VecFile.filename : "NULL",
                         YESNO(bOverwrite));
    if (!bOverwrite && (access(pczFilename,F_OK)==0))
	m_iErrno = DERR_FILE_ALREADY;
    else if ((pSrcVectors != NULL)  
             && (pSrcVectors->m_uState != IMG_INITFROMFILE)
	     && (pSrcVectors->m_uState != IMG_HDRWRITTEN))
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (m_iErrno == 0)  /* create the output header */
        {
	IMGTYPE_T format = IT_DRAGON_VEC;  // default
	if ((m_pHdr = new ImageHdr(m_iDebug,m_iTrace)) == NULL)
	    m_iErrno = DERR_MEM_ALLOC;
	else
	    {
            if (pSrcVectors != NULL)
	        m_pHdr->copy(pSrcVectors->getImageHeader(),IT_DRAGON,"V");
            else  /* init with default values */
	        {
	        m_pHdr->init(IT_DRAGON,"V",0,0,8,1,0, pczFilename);
	        m_pHdr->update_text(pczFilename,NULL,"Vector File",NULL,
				   NULL,NULL,NULL,NULL,"V");
                }
	    strcpy_array(m_VecFile.filename,pczFilename);
	    m_VecFile.fileAccess = FILEACCESS_OUTPUT;
            m_VecFile.bValid = TRUE;
            }
        if (pSrcVectors != NULL)
            format = pSrcVectors->m_VecFile.vectorFormat;
        else if (vectorFormat >= IT_DRAGON_VEC)
            format = vectorFormat;
        m_pVWriter = vectorDataWriterFactory(format);
        if (m_pVWriter == NULL)
           {
           m_iErrno = DERR_UNSUP_FORMAT; 
           }
	}
    if (m_iTrace)
        {
	logTrace("VectorData::create (ex) status is %d (%s)", 
		 m_iErrno,getErrorMessage());
	}
    if (m_iDebug)
        {
	fprintf(stderr,"VectorData::create status is %d (%s)\n", 
	       m_iErrno,getErrorMessage());
        }
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_WRITABLE;
    return m_iErrno;
    }

	/* set up a VectorData for output. This will be
         * a brand new file based on pSrcData.
	 * This version of create() is for shp2drag, 
	 * and other ops which create vector file de-novo
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcData	Vector data to initialize from
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
int VectorData::create(const char * pczFilename, BOOL bOverwrite,
		       const VECTORDATA * pSrcData)
    {
    IMGTYPE_T format = IT_DRAGON_VEC;  // default
    if (m_iTrace)
	Logger::logTrace("VectorData::create2 (en) file='%s' from source '%p'"
			 " overwrite=%s ",
			 pczFilename,pSrcData,YESNO(bOverwrite));
    if (m_iDebug)
	fprintf(stderr,"VectorData::create2 (en) file='%s' from source '%p'"
			 " overwrite=%s \n",
			 pczFilename,pSrcData,YESNO(bOverwrite));
    if (!bOverwrite && (access(pczFilename,F_OK)==0))
	m_iErrno = DERR_FILE_ALREADY;
    else if (pSrcData == NULL)  
	m_iErrno = DERR_FN_ARG2;
    else if ((m_pHdr = new ImageHdr(m_iDebug,m_iTrace)) == NULL)
        m_iErrno = DERR_MEM_ALLOC;
    else
        {
	m_pHdr->init(IT_DRAGON_VEC,"V",0,0,8,1,0, pczFilename);
	m_pHdr->update_text(pczFilename,NULL,"Vector File",NULL,
			    NULL,NULL,NULL,NULL,"V");
	strcpy_array(m_VecFile.filename,pczFilename);
	m_VecFile.fileAccess = FILEACCESS_OUTPUT;
	m_VecFile.vectorFormat = format;
	m_VecFile.bValid = TRUE;
	m_iErrno = update_extent(pSrcData->minExtent.x,pSrcData->minExtent.y,
			      pSrcData->maxExtent.x,pSrcData->maxExtent.y,
			      NULL,"meter");
	if (m_iErrno < 0)
	    {
	    logTrace("VectorData::create2 error %s in update_extent",
		     dragonErrorMessage(m_iErrno));
	    if (m_iDebug)
	        fprintf(stderr,"VectorData::create2 error %s in update_extent",
			dragonErrorMessage(m_iErrno));
	    }
	else
	    {
	      //    fprintf(stderr,
	      //    m_pHdr->dump(1,"VectorData::create2 after update_extent"));
	    m_pVWriter = vectorDataWriterFactory(format);
	    if (m_pVWriter == NULL)
	        m_iErrno = DERR_UNSUP_FORMAT; 
	    }
	}
    if (m_iTrace)
        {
	logTrace("VectorData::create2 (ex) status is %d (%s)", 
		 m_iErrno,getErrorMessage());
	logTrace(m_pHdr->dump(1,"VectorData::create2 (ex)"));
	}
    if (m_iDebug)
        {
	fprintf(stderr,"VectorData::create2 status is %d (%s)\n", 
	       m_iErrno,getErrorMessage());
	fprintf(stderr,m_pHdr->dump(1,"VectorData::create2 (ex)"));
        }
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_WRITABLE;
    return m_iErrno;
    }

/*-------------------------------------------------------------*/

	/* change text information (except classnames, unitnames) 
	 * for a vector file. 
	 * This is just a wrapper around the ImageHdr function.
	 * Only the params with non-NULL vals will be changed.
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int VectorData::update_text(const char * pczTitle,
			  const char * pczId,
			  const char * pczComment,
			  const char * pczSource,
			  const char * pczScene,
			  const char * pczSubscene,
			  const char * pczBand,
			  const char * pczColorfileName,
			  const char * pczFtype)
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
				  pczColorfileName,"V");
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
int VectorData::update_georef(int img_x, int img_y, 
			    const MapCoord * ref_x, const MapCoord * ref_y,
			    double xcell_size, double ycell_size,
			    const char* pczProjection, const char* pczUnitname,
			    const char * pczDateTime,const char * pczUTMZone,
			    int iRegistered)
    {
    int iRetval = 0;
    if (m_iTrace)
        logTrace("VectorData::update_georef");
    if (m_iDebug)
	fprintf(stderr,"VectorData::update_georef\n");
    if (m_pHdr == NULL)
        iRetval = DERR_IMAGE_UNINIT;
    else
        iRetval = m_pHdr->update_georef(img_x, img_y, ref_x, ref_y,
					xcell_size, ycell_size,
					pczProjection, pczUnitname,
					pczDateTime,pczUTMZone,
					iRegistered);
    return iRetval;
    }

	/* set extent (bounding box) information for a vector file.
	 * This invokes update_georef and update_extents to
	 * set pczUnitName (meter by default) and optionally pczProjection
	 * @param dMinX,dMinY  	u.l. corner of bounding box in UTM
	 * @param dMaxX,dMaxY  	l.r. corner of bounding box in UTM
	 * @param pczProjection NULL or code for map proj'n 
	 * @param pczUnitname	usually 'meter'
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int VectorData::update_extent(double dMinX,double dMinY,
			      double dMaxX,double dMaxY,
			      const char* pczProjection, 
			      const char* pczUnitname)
    {
    int iRetval = 0;
    if (m_iTrace)
        logTrace("VectorData::update_extent (en)");
    if (m_iDebug)
	fprintf(stderr,
		"VectorData::update_extent (en) %.2f,%.2f,%.2f,%.2f format=x%X\n",
		dMinX, dMinY, dMaxX, dMaxY,m_VecFile.vectorFormat);
    if (m_pHdr == NULL)
        iRetval = DERR_IMAGE_UNINIT;
    else if (m_VecFile.vectorFormat != IT_DRAGON_VEC)
        iRetval = DERR_UNSUP_FORMAT;   /* fn is only for Dragon Vector Files*/
    else
        {
	MapCoord mX = {dMinX };
	MapCoord mY = {dMinY };
	iRetval = m_pHdr->update_extent(dMinX, dMinY, dMaxX, dMaxY);
	if (iRetval == 0)
	    iRetval = m_pHdr->update_georef(0,0,&mX, &mY,1.0,1.0,
					    pczProjection,pczUnitname,
					    NULL,NULL,-1); // ~~~ somethng needed?
//			    pczDateTime,pczUTMZone,
//			    iRegistered);

	//	pFileHdr->fields.h_ulWidth = (UINT32)(dMaxX - dMinX);
	//pFileHdr->fields.h_ulHeight = (UINT32)(dMaxY - dMinY);
	}
    if (m_iTrace)
        logTrace("VectorData::update_extent (ex) returns %d",iRetval);
    if (m_iDebug)
	fprintf(stderr,"VectorData::update_extent (ex) returns %d\n",iRetval);
    return iRetval;
    }

	/* set extent (bounding box) information for a vector file.
	 * This sets the extents in the m_VecFile.
	 * @param dMinX,dMinY  	u.l. corner of bounding box in UTM
	 * @param dMaxX,dMaxY  	l.r. corner of bounding box in UTM
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int VectorData::set_extent(double dMinX,double dMinY,double dMaxX,double dMaxY)
    {
    int iRetval = 0;
    if (m_iTrace)
        logTrace("VectorData::set_extent (en)");
    if (m_iDebug)
	fprintf(stderr,
		"VectorData::set_extent (en) %.2f,%.2f,%.2f,%.2f format=x%X\n",
		dMinX, dMinY, dMaxX, dMaxY,m_VecFile.vectorFormat);
    if (m_pHdr == NULL)
        iRetval = DERR_IMAGE_UNINIT;
    else
        {
	m_VecFile.minExtent.x = dMinX;
	m_VecFile.minExtent.y = dMinY;
	m_VecFile.maxExtent.x = dMaxX;
	m_VecFile.maxExtent.y = dMaxY;
	}
    if (m_iTrace)
        logTrace("VectorData::set_extent (ex) returns %d",iRetval);
    if (m_iDebug)
	fprintf(stderr,"VectorData::set_extent (ex) returns %d\n",iRetval);
    return iRetval;
    }

	/* change metafile information 
	 * for an existing vector data source.
	 * Only the params with non-NULL vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int VectorData::update_metainfo(const char * pczMetafile,
			  const char * pczGuid)
    {
    if (m_pHdr == NULL)
       return DERR_IMAGE_UNINIT;
    else
       return m_pHdr->update_metainfo(pczMetafile,pczGuid);
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
int VectorData::writeHeader()
    {
    int iStat = 0;
    if (m_iTrace)
	Logger::logTrace("VectorData::writeHeader (en) "
			 "name='%s' state=%s",
			 m_VecFile.filename,Image::getStateName(m_uState));
    if (m_iDebug)
	fprintf(stderr,"VectorData::writeHeader (en) "
	       "name='%s' errno=%d\n\tstate=%s\n",
		m_VecFile.filename,m_iErrno,Image::getStateName(m_uState));
    if (m_VecFile.vectorFormat != IT_DRAGON_VEC)
        return 0;   /* Write header is only for Dragon Vector Files */
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    if (strlen(m_VecFile.filename) == 0)
	m_iErrno = DERR_IMAGE_NONAME;
#ifdef NOTNOW 
    else if ((m_uState != IMG_WRITABLE) && (m_uState != IMG_CHANGED))   
        // thus cannot use for readable image
	m_iErrno = DERR_IMAGE_BADSTATE;
#endif
    else if (m_pWriter != NULL)
	m_iErrno = DERR_IMAGE_REINIT;
    else if ((m_pWriter = m_pHdr->imageWriterFactory(m_pHdr->getImageType())) == NULL)
	m_iErrno = DERR_UNSUP_FORMAT;
    else
        {
	long lOffset; /* init tells us where image data starts */
	if (m_iDebug)
   	    {
	    fprintf(stderr,"VectorData::writeHeader "
		   "about to init ImageWriter: "
		   "m_pWriter is %p, and hdr at %p\n", 
		    m_pWriter, m_pHdr);
	    }
	m_pWriter->init(m_pHdr,&lOffset);
	if (m_iDebug)
	    fprintf(stderr,"VectorData::writeHeader "
		    "setting data offset to %ld\n", lOffset);
	m_pHdr->setDataOffset(lOffset);
	}
    if ((m_iErrno == 0)
    	    && (! m_pWriter->writeHeader(m_VecFile.filename,
					 pImgHeader,&iStat)))
	m_iErrno = iStat;
    m_pHdr->clearUpdatesNeeded();
    m_bHdrUpdated = FALSE;     /* TRUE => need to rewrite header */
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_HDRWRITTEN;
    if (m_iDebug)
	fprintf(stderr,m_pHdr->dump(1,"VectorData::writeHeader (ex)"));
    if (m_iTrace)
	logTrace(m_pHdr->dump(1,"VectorData::writeHeader (ex)"));
    return m_iErrno;
    }

/*-------------------------------------------------------------*/

	/*	rewrite vector header and close output file
         *      without disturbing the vector data.
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
int VectorData::rewriteHeader()
    {
    DRAGON_HEAD dragonHdr;
    FILE * pFp = NULL;
    const char * czMethod = "VectorData::rewriteHeader";
    if (m_iTrace)
	logTrace("%s (en)",czMethod);
    if (m_iDebug)
	fprintf(stderr,"%s (en)\n",czMethod);
    const IMAGEHDR * pHdr = getIMAGEHDR();
    int iStat = 0;
    if (m_VecFile.vectorFormat != IT_DRAGON_VEC)
        iStat = DERR_UNSUP_FORMAT;   /* rewrite header is only for Dragon Vector Files */
    else if (strlen(m_VecFile.filename) == 0)
	m_iErrno = iStat = DERR_IMAGE_NONAME;
    else
        {
	memset(&dragonHdr,0,sizeof(dragonHdr));
	iStat = copyFields(&dragonHdr,pHdr);
	if (iStat == 0)
            {
	    if (pFp == NULL)
                {
	        if ((pFp = fopen(m_VecFile.filename,"rb+")) == NULL)
		    m_iErrno = DERR_FILE_OPEN;
		}
	    if (pFp != NULL)
	        {
		if (fseek(pFp,0,SEEK_SET) != 0)
		    iStat = DERR_FILE_SEEK;
		else if (fwrite(&dragonHdr.buffer,sizeof(dragonHdr),1,pFp) != 1)
		    iStat = DERR_FILE_RW;
		}
	    }
	}
    if (m_iTrace)
	logTrace("%s (ex) status=%d",czMethod,iStat);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) status=%d\n", czMethod,iStat);
    return iStat;
    }

/*-------------------------------------------------------------*/
    /* Adjust the extent based on the passed x and y coordinates
     * @param pFeature  Vector feature to consider
     */
void VectorData::adjustExtent(VECFEATURE* pFeature)
    {
    int i = 0;
    for (i = 0; i < (int) pFeature->vertexCount; i++)
       {
       m_VecFile.minExtent.x 
	 = min(pFeature->points[i].x, m_VecFile.minExtent.x);
       m_VecFile.minExtent.y 
	 = min(pFeature->points[i].y, m_VecFile.minExtent.y);
       m_VecFile.maxExtent.x 
	 = max(pFeature->points[i].x, m_VecFile.maxExtent.x);
       m_VecFile.maxExtent.y 
	 = max(pFeature->points[i].y, m_VecFile.maxExtent.y);
       }
    }

/*-------------------------------------------------------------*/
        /* Read the next vector feature and any fill information
         * from the vector file. This function allocates the structure
         * that is returned. The caller must free the structure by
         * calling freeVecFeature()
         *
         * @param  pStatus  0 is returned in this variable for success,
         *                  otherwise an error number
         * @param  bTransformOnRead  If true, transform from geographic
         *                  to screen coordinates before returning to the caller
         * @return pointer to new VECFEATURE structure or null if error.
         */
VECFEATURE * VectorData::getNextFeature(int* pStatus, BOOL bTransformOnRead)
    {
    VECFEATURE * pNewFeature = NULL;
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    if ((m_uState == IMG_ERROR) || 
	(m_pVReader == NULL) || (m_VecFile.fileAccess != FILEACCESS_INPUT))
        {
	*pStatus = DERR_IMAGE_BADSTATE;
	}
    else
        {
	pNewFeature = m_pVReader->getNextFeature(pStatus);
	if ((pNewFeature != NULL) && (bTransformOnRead))
	    {
	    unsigned int p = 0;
	    // do geographic to screen coord transform
	    for (p = 0; p < pNewFeature->vertexCount; p++)
	        {
		pNewFeature->points[p].x = 
		    (pNewFeature->points[p].x - pImgHeader->ref_x.v0) / 
		    pImgHeader->xcell_size;
		pNewFeature->points[p].y = 
		    (pNewFeature->points[p].y - pImgHeader->ref_y.v0) / 
		    pImgHeader->ycell_size;
		} 
	    }
	}
    return pNewFeature;
    } 

/*-------------------------------------------------------------*/
     /* Write a vector feature to the vector file. 
      * This function assumes that the header, if any,
      * has been written. 
      * This is a wrapper for the vectorDataWriter function
      * of the same name.
      * IFF the feature pointer is NULL, does any necessary
      * cleanup or finalization of the output file.
      * @param pFeature Pointer to feature data to write. If NULL
      *                 signals we should write "-END" 
      * @param  bTransformOnWrite  If true, transform from screen to geographic
      *                  coordinates before writing.
      * @return 0 for success, negative for error.
      */  
int VectorData::putNextFeature(VECFEATURE* pFeature,BOOL bTransformOnWrite)
   { 
   int status = 0;
   if ((m_uState == IMG_ERROR) || (m_uState == IMG_CLOSED) ||
       (m_pVWriter == NULL) || (m_VecFile.fileAccess != FILEACCESS_OUTPUT))
      {
      status = DERR_IMAGE_BADSTATE;
      }
   else
      {
      const IMAGEHDR * pImgHeader = getIMAGEHDR();
      if (bTransformOnWrite)
	 {
	 // do screen to geographic coord transform
         int p = 0;
         for (p = 0; p < (int) pFeature->vertexCount; p++)
	    {
            pFeature->points[p].x = 
               (pFeature->points[p].x * pImgHeader->xcell_size) +
                          pImgHeader->ref_x.v0;
            pFeature->points[p].y = 
               (pFeature->points[p].y * pImgHeader->ycell_size) +
                          pImgHeader->ref_y.v0;
            } 
         }
      status = m_pVWriter->putNextFeature(pFeature);
      }
   return status;
   }

/*-------------------------------------------------------------*/

/* make file header agree with passed header
 * @param pDestHdr 	DHEAD-sized buffer
 *                  	which needs to be filled from pSrcHdr info 
 * @param pSrcHdr       Pointer to IMAGEHDR to use as the source for 
 *                      header values   
 * @return        <0 if err (missing argument)
 */
int VectorData::copyFields(DRAGON_HEAD * pDestHdr,
			   const IMAGEHDR * pSrcHdr)
    {
    int iRetVal = 0;

    const char * czMethod = "VectorData::copyFields";
    if (m_iTrace)
	logTrace("%s (en)",czMethod);
    if (m_iDebug)
	fprintf(stderr,"%s (en) ref_x=%s\n",czMethod,pDestHdr->fields.ref_x.cz_v0);
    if (! pSrcHdr->bImageHdrInitialized)
	return DERR_IMAGE_UNINIT;

    /*  copy or derive the FILE_PARAMS fields */
    strcpy_array(pDestHdr->fields.h_czFtype,pSrcHdr->ftype);
    pDestHdr->fields.h_ulHeight     = (UINT32) pSrcHdr->size[0];
    pDestHdr->fields.h_ulWidth 	   = (UINT32) pSrcHdr->size[1];
    pDestHdr->fields.h_ulBitsPerPix = (UINT32) pSrcHdr->bits_per_pix;
    pDestHdr->fields.h_ulEncoding   = (UINT32) pSrcHdr->uEncoding;

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
	     sizeof(pDestHdr->fields.h_czXcell_size),
	     "%lf",pSrcHdr->xcell_size);
    snprintf(pDestHdr->fields.h_czYcell_size,
	     sizeof(pDestHdr->fields.h_czYcell_size),"%lf",
	     pSrcHdr->ycell_size);

    if (pSrcHdr->czProjection!= NULL)
	{ strcpy_array(pDestHdr->fields.czProjection,pSrcHdr->czProjection); }
    if (pSrcHdr->unitname!= NULL)
	{ strcpy_array(pDestHdr->fields.unitname,pSrcHdr->unitname); }

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
    /* ulByteOrder not currently used, but can in future permit 
     * cross-platform file decoding */
    char cByteOrder[]={'A','B','C','D'};
    memcpy(&pDestHdr->fields.h_ulByteOrder,cByteOrder,
	   sizeof(pDestHdr->fields.h_ulByteOrder));
    if (m_iTrace)
	logTrace("%s (ex) return %d",czMethod,iRetVal);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) return %d\n",czMethod,iRetVal);
    return iRetVal;
    }

void VectorData::mapCoord_copy(const MapCoord * src,
				      HDR_MapCoord * dest)
    {
    snprintf(dest->cz_v0,sizeof(dest->cz_v0),"%f",src->v0);
    dest->tag = (UINT32) src->ulTag;
    dest->v1 = (SINT32) src->v1;
    dest->v2 = (SINT32) src->v2;
    }

/*-------------------------------------------------------------*/
	/* close any open files, reset to indicate that the file
         * is not currently valid. Currently just calls zero()
         */
int VectorData::close()  { return zero(); }

/*-------------------------------------------------------------*/
void VectorData::setFeatureCount(int count)
   {
   m_VecFile.featureCount = count;
   }

int VectorData::getFeatureCount()
   {
   return m_VecFile.featureCount;
   }

void VectorData::incrementFeatureCount()
   {
   m_VecFile.featureCount++;
   }

/* Set the data type for this file.
 * Currently only relevant for Shapefiles, which
 * can hold only one type of feature.
 * Returns TRUE unless invalid type is passed 
 */
BOOL VectorData::setShapeType(char type)
  {
  BOOL bReturn = TRUE;
  if ((m_VecFile.vectorFormat == IT_ESRI_SHAPE) &&
      (m_pVWriter != NULL))
     {
     bReturn = ((ShapeVectorDataWriter *) m_pVWriter)->setShapeType(type);
     }
  return bReturn;
  }


/*-------------------------------------------------------------*/
        /* Test whether this vector file has 
         * any header information.
         * @param  pczFilename  Name of file to test.
         * @return TRUE if it has a header, else
         *         FALSE. If it has a header it
         *         will always be 5.8 style.
         */
BOOL VectorData::headerExists(const char * pczFilename)
    {
    BOOL result = FALSE;
    if (m_iHasHeader >= 0)
        result = (m_iHasHeader > 0);
    else
       { 
       char buffer[HDR_RO_SZ+2];
       unsigned len = strlen(HDR_TITLE_RO);
       FILE * pFp = NULL;
       memset(buffer,0,sizeof(buffer));
       pFp = fopen(pczFilename,"rb");
       if (pFp != NULL)
	   {
	   if (fread(buffer,1,len,pFp) == len)
	       {
	       if (strcmp(buffer,HDR_TITLE_RO) ==0)
		  result = TRUE;
	       } 
	   fclose(pFp);
	   }
       m_iHasHeader = (result) ? 1 : 0; 
       }
    return result;    
    }    

/* Factory Methods */

   /* Return a VectorDataReader which can read the specified file
    * or NULL if unknown type.
    */
VectorDataReader * VectorData::vectorDataReaderFactory(const char * pczName)
    {
    VectorDataReader * pReader = NULL;
    if (ShapeVectorDataReader::vectest(pczName))
        {
	pReader = new ShapeVectorDataReader(m_iDebug,m_iTrace);
        m_VecFile.vectorFormat = IT_ESRI_SHAPE;
	}
    else if ((!headerExists(pczName)) || (DragonImageReader::vectest(pczName,m_iDebug)))
        {
	pReader = new DragonVectorDataReader(m_iDebug,m_iTrace);
        m_VecFile.vectorFormat = IT_DRAGON_VEC;
	}
    if (pReader != NULL)
        {
        pReader->setVectorDataPointer(this); // set m_pDataVector
        }
    return pReader;
    }

    /* Return a VectorDataWriter which can write the specified file type
     * or NULL if unknown type.
     */
VectorDataWriter * VectorData::vectorDataWriterFactory(IMGTYPE_T type)
    {
    VectorDataWriter * pWriter = NULL;
    switch (type)
        {
        case IT_DRAGON_VEC:
            pWriter = new DragonVectorDataWriter(m_iDebug, m_iTrace);
            m_VecFile.vectorFormat = IT_DRAGON_VEC;
	    if (pWriter != NULL)
                {
	        pWriter->setVectorDataPointer(this); // set m_pDataVector
		setFeatureCount(0);
		}
	    break;
	case IT_ESRI_SHAPE:
            pWriter = new ShapeVectorDataWriter(m_iDebug, m_iTrace);
	    m_VecFile.vectorFormat = IT_ESRI_SHAPE;
	    if (pWriter != NULL)
                {
	        pWriter->setVectorDataPointer(this); // set m_pDataVector
		}
	    break;
        default:  // nothing 
            break;          
       }
    return pWriter;
    }

/***********************************************************************/
/* Debugging functions */

void VectorData::dumpVECFEATURE(VECFEATURE * pFeature) // dump a feature
   {
   printf("Vector feature ID %s, of type %d\n",
               pFeature->ID, pFeature->featureType);
   printf("   Color is %d, Fill is %d, number of vertices is %d\n",
	  pFeature->color, pFeature->fillColor, pFeature->vertexCount);
   for (int i = 0; (i < (int) pFeature->vertexCount); i++)
       printf("    x=%f, y=%f\n", 
              pFeature->points[i].x, pFeature->points[i].y);
   }

void VectorData::dumpVECTORDATA()
   {
   printf("Filename is '%s'\n", m_VecFile.filename);
   printf("File access is %d\n", m_VecFile.fileAccess);
   printf("Vector file valid: %s\n", YESNO(m_VecFile.bValid));
   printf("Extent from %f,%f to %f,%f\n",
           m_VecFile.minExtent.x, m_VecFile.minExtent.y,
           m_VecFile.maxExtent.x, m_VecFile.maxExtent.y); 
   
   }

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
const char * VectorData::dump(int detail, const char * pczTitle) const
    {
    const char* pczHead = NULL; 
    printf("%s\n",pczTitle);
    pczHead = m_pHdr->dump(detail,"Vector File Header");
    printf(pczHead);
    return pczHead;
    }

/***********************************************************************/
/* C language functions */

extern "C"
{

   /* Free all the memory associated with a VECFEATURE. */
void freeVecFeature(VECFEATURE* pFeature)
   {
   if (pFeature != NULL)
      {
      if (pFeature->points != NULL)
	 {
         free(pFeature->points);
         pFeature->points = NULL;
         }
      free(pFeature);
      }
   }

   /* Allocate memory for a vector feature that will hold the
    * specified number of points. 
    * @param  vertexCount How many vertices are needed?
    * @return Pointer to newly allocated VECFEATURE or 
    *         NULL if allocation error.
    */
VECFEATURE * allocateVecFeature(int vertexCount)
    {
    VECFEATURE * pFeature = (VECFEATURE*) calloc(1,sizeof(VECFEATURE));
    if (pFeature != NULL)
       {
       pFeature->fillColor = -1;
       pFeature->color = 255;
       if (vertexCount <= 0) // illegal count 
	  {
	  // free the struct and return a null pointer
          free(pFeature);
	  pFeature = NULL;
          }
       else
	  {
	  pFeature->vertexCount = (unsigned int) vertexCount;
	  pFeature->points = (VERTEX *) calloc(vertexCount,sizeof(VERTEX));
	  if (pFeature->points == NULL)
	     {
	     free(pFeature);
	     pFeature = NULL;
	     } 
	  }
       }
    return pFeature;
    }

}  /* end of extern C */

void VectorData_END() { puts(FIL_ID); }

/************************************************************************/
#ifdef TEST

extern "C"
{

void usage()
    {
    printf ("Test VectorData class by reading some file header\n");
    printf ("Usage: VectorData.TEST inputfilepath outputfilepath\n");
    exit(1);
    }

int main(int argc, char ** argv)
    {
    MapCoord refx;
    MapCoord refy;

    VECFEATURE * pNextFeature = NULL;
    char czFilename[PATH_MAX] = "";
    char czOutFilename[PATH_MAX] = "";
    if (argc < 3)
	usage();
    strcpy(czFilename,argv[1]);
    strcpy(czOutFilename,argv[2]);
    
    printf("+++ Try to read existing file \n");
    VectorData vfile(0,0);
    int error = vfile.open(czFilename);
    if (error < 0)
        {
        printf("Error %d trying to open file %s\n", error,czFilename);
        exit(0);
        }
    //vfile.dumpVectorData();
    //vfile.dump(2,"Vector File");
    printf("+++ Try to open output file \n");
    VectorData oVfile(0,0);
    //    error = oVfile.create(czOutFilename,TRUE,&vfile);
    error = oVfile.create(czOutFilename,TRUE,NULL,IT_DRAGON_VEC);
    if (error < 0)
        {
        printf("Error %d trying to create output file\n",error);
        exit(0);
        }
    //oVfile.dumpVECTORDATA();
    //oVfile.dump(2,"Vector File");
    refx.v0 = 10000.0;
    refy.v0 = 20000.0;

    //error = oVfile.update_georef(0,0,&refx,&refy,10.0,-10.0,NULL,"meters");
    //if (error < 0)
    //    {
    //    printf("Error %d trying to update georeferencing \n",error);
    //    exit(0);
    //    }
    error = oVfile.writeHeader();
    if (error < 0)
        {
        printf("Error %d trying to write header\n",error);
        exit(0);
        }

    printf("+++ Try to read vector file and copy to the output file...\n");
    while (error >= 0)
       {
       pNextFeature = vfile.getNextFeature(&error,TRUE);
       if (error < 0)    
          {
          printf("Error %d reading vector\n", error);
          exit(0);
          }
       if (pNextFeature != NULL)
	  {
          printf("Just read: \n");
          vfile.dumpVECFEATURE(pNextFeature);
          printf("-----------\n");
          error = oVfile.putNextFeature(pNextFeature,TRUE);
          if (error < 0)
	     {
             printf("Error %d writing vectors\n", error);
             }
          else
	     {
	     printf("Just wrote: \n");
	     oVfile.dumpVECFEATURE(pNextFeature);
	     freeVecFeature(pNextFeature);
	     printf("-----------\n");
             }
          }
       else  
	  {
	  break;
          }
       }
    
    if (error < 0)    
        {
        printf("Error %d! -exiting \n", error);
        exit(0);
        }
    else
       {
       /* write the 'END' record */
       oVfile.putNextFeature(NULL,FALSE);
       }

    printf("+++ Dump after reading and setting extents\n");
    vfile.dumpVECTORDATA();

    return 0;
    }
}
#endif /* TEST */










