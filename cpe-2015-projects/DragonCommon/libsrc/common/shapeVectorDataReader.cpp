extern "C"
{
#include "drelease.h"
char SHAPEVECTORDATAREADER_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.11 $$Date: 2012/07/03 12:44:39 $";
D_REL_IDSTR;
}
/*
 *	filename shapeVectorDataReader.cpp
 *		$Revision: 1.11 $ $Date: 2012/07/03 12:44:39 $	
 *
 *      Copyright 2006-2008 Kurt Rudahl and Sally Goldin
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
 *
 ***************************************************
 *  $Id: shapeVectorDataReader.cpp,v 1.11 2012/07/03 12:44:39 rudahl Exp $
 *  $Log: shapeVectorDataReader.cpp,v $
 *  Revision 1.11  2012/07/03 12:44:39  rudahl
 *  fix logic problem in handling file with one feature
 *
 *  Revision 1.10  2008/09/14 10:06:19  rudahl
 *  error setting extents in shapefile
 *
 *  Revision 1.9  2008/09/12 11:42:23  rudahl
 *  added handling of extents, georef header fields; 
 *   new create() for de-novo files
 *
 *  Revision 1.8  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.7  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.6  2006/09/24 10:37:30  goldin
 *  Make test for shape file more stringent and more correct
 *
 *  Revision 1.5  2006/09/17 13:33:35  goldin
 *  deal with special cases
 *
 *  Revision 1.4  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.3  2006/08/09 14:01:26  goldin
 *  Fix logic error in test code
 *
 *  Revision 1.2  2006/08/09 09:48:09  goldin
 *  Adding support for writing shapefiles
 *
 *  Revision 1.1  2006/08/07 10:05:07  goldin
 *  Begin work on support for shape files
 *
 *
 *
 *******************************************************************
 *   This is the ShapeVectorDataReader class. This class knows
 *   how to read vector data from an ESRI shapefile. It is
 *   a concrete subclass of VectorDataReader, and is created
 *   by a parent VectorData object, which holds on to global information
 *   about the vector file/datasource, including its header.
 *
 *   Note that at the moment, this class handles geographic coordinate
 *   data only - not attributes.
 *
 *   Created by Sally Goldin, 7 August 2006
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
#include "shapefil.h"  // in vendors tree
#include "vectorData.h"
#include "vectorDataReader.h"
#include "shapeVectorDataReader.h"
//#include "i18n.h"

#include "dragonOb.h"
#include "logger.h"
//#include "dp.h"

Class ShapeVectorDataReader::s_class_Base("ShapeVectorDataReader",
					  "Class for reading ESRI shapefiles");

		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
ShapeVectorDataReader::ShapeVectorDataReader(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("ShapeVectorDataReader::ShapeVectorDataReader (en)");
    if (iDebug || m_iDebug)
	fprintf(stderr,"ShapeVectorDataReader::ShapeVectorDataReader (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_pVectorData = NULL;
    m_hSHP = NULL;
    if (iTrace || m_iTrace)
	logTrace("ShapeVectorDataReader::ShapeVectorDataReader (ex)");
    if (iDebug || m_iDebug)
	fprintf(stderr,"ShapeVectorDataReader::ShapeVectorDataReader (ex)\n");
    }

   /* Override superclass method to also get the number of features.
    * in the file.
    */
void ShapeVectorDataReader::setVectorDataPointer(VectorData* pVD) 
    {
    if (m_iTrace)
	logTrace("ShapeVectorDataReader::setVectorDataPointer (en)");
    if (m_iDebug)
	fprintf(stderr,"ShapeVectorDataReader::setVectorDataPointer (en)\n");
    m_pVectorData = pVD;
    const char* pczVectorFilename = m_pVectorData->getFilename();
    if (m_hSHP == NULL)  /* file not open yet */
        { 
        m_hSHP = SHPOpen(pczVectorFilename, "rb" );
        if( m_hSHP != NULL )
 	    { // adf... is 4 doubles: x,y,z,m (what is m?)
            SHPGetInfo( m_hSHP, &m_nEntities, &m_nShapeType, 
			m_adfMinBound, m_adfMaxBound );
	    m_pVectorData->setFeatureCount(m_nEntities);
	    m_pVectorData->set_extent(m_adfMinBound[0],m_adfMinBound[1],
				      m_adfMaxBound[0],m_adfMaxBound[1]);
	    }
	SHPClose(m_hSHP);
        m_currentEntity = 0;
	m_hSHP = NULL;
	}
    if (m_iTrace)
	logTrace("ShapeVectorDataReader::setVectorDataPointer (ex)");
    if (m_iDebug)
	fprintf(stderr,"ShapeVectorDataReader::setVectorDataPointer (ex)\n");
    }  

/*-------------------------------------------------------------*/
        /* Read the next vector feature and any fill information
         * from the vector file. This function allocates the structure
         * that is returned. The caller must free the structure by
         * calling freeVecFeature()
         *
         * 9/17/06 now transforms a multi-part feature into 
         * multiple individual Dragon features. Every part except
         * the first is given the special attribute value of 0.
         *
         * @param  pStatus  0 is returned in this variable for success,
         *                  otherwise an error number
         * @return pointer to new VECFEATURE structure or null if error.
         */
VECFEATURE * ShapeVectorDataReader::getNextFeature(int* pStatus)
   {
   VECFEATURE * pNewFeature = NULL;
   int j;
   int k;
   int startIndex = 0;
   int endIndex = 0;
   int nVertices = 0;
   SHPObject *psShape;
   *pStatus = 0;
   if (m_iTrace)
      logTrace("ShapeVectorDataReader::getNextFeature (en)");
   if (m_iDebug)
      fprintf(stderr,"ShapeVectorDataReader::getNextFeature (en)\n");
   if (m_pVectorData == NULL)
      {
      *pStatus = DERR_IMAGE_NOREAD;
      logTrace("getNextFeature - m_pVectorData (parent vectorData) is null");
      if (m_iDebug)
          fprintf(stderr,"getNextFeature - m_pVectorData (parent vectorData) is null\n");
      return NULL; 
      }
   const char* pczVectorFilename = m_pVectorData->getFilename();
   logTrace("getNextFeature: - m_currentEntity=%d m_nEntities=%d",
      m_currentEntity, m_nEntities);
   if (m_hSHP == NULL)  /* file not open yet */
      { 
      logTrace("Opening shape file");
      m_hSHP = SHPOpen(pczVectorFilename, "rb" );
      if( m_hSHP == NULL )
         {
         *pStatus = DERR_FILE_OPEN;
         }
      else  /* get and save basic info */
	 {
         SHPGetInfo( m_hSHP, &m_nEntities, &m_nShapeType, 
                      m_adfMinBound, m_adfMaxBound );
         m_pVectorData->setFeatureCount(m_nEntities);
	 m_currentEntity = 0;
         m_currentPart = 0;
         m_partCount = 0;
         if (m_iDebug)
	    {
	    fprintf(stderr, "Shapefile Type: %s   # of Shapes: %d\n\n",
               SHPTypeName( m_nShapeType ), m_nEntities );
            fprintf(stderr, "File Bounds: (%12.3f,%12.3f,%g,%g)\n"
		    "         to  (%12.3f,%12.3f,%g,%g)\n",
		    m_adfMinBound[0], 
		    m_adfMinBound[1], 
		    m_adfMinBound[2], 
		    m_adfMinBound[3], 
		    m_adfMaxBound[0], 
		    m_adfMaxBound[1], 
		    m_adfMaxBound[2], 
		    m_adfMaxBound[3] );
            }  /* end if debug */
         }  /* end if file open was okay */
      }
   logTrace("*pStatus is %d", *pStatus);
   /* 3 July 2012 - seg removed "else" before this if. Logic error. */
   if (m_currentEntity >= m_nEntities)  /* if all the entities have been read */
      {
      logTrace("getNextFeature - no more features to read");
      SHPClose(m_hSHP);
      m_hSHP = NULL;
      m_pVectorData->setState(IMG_CLOSED);
      return pNewFeature;
      }
   if (*pStatus == 0)
      {
      logTrace("About to call SHPReadObject - m_currentEntity is %d",
	  m_currentEntity);
      /* get the next shape (or the current shape again) from the file */
      psShape = SHPReadObject(m_hSHP,m_currentEntity );
      logTrace("SHPReadObject returned %p",psShape);
      if (m_partCount > 1)  /* more than one part in the previous feature */
	 {
         if (m_iDebug)
	     fprintf(stderr,"Case 1 - on part %d of %d multiple parts\n", 
		 m_currentPart+1,m_partCount);
	 startIndex = psShape->panPartStart[m_currentPart];
	 if (m_currentPart == m_partCount - 1)  /* last part */
	    endIndex = psShape->nVertices-1;
	 else 
	    endIndex = psShape->panPartStart[m_currentPart + 1] - 1;
	 }
      else if (psShape->nParts > 1) /* new multipart feature */
	 {
	 m_partCount = psShape->nParts;
	 m_currentPart = 0;
	 startIndex = psShape->panPartStart[m_currentPart];
	 endIndex = psShape->panPartStart[m_currentPart + 1] - 1;
         if (m_iDebug)
	     fprintf(stderr,"Case 2 - new multipart with  %d parts\n",
		 m_partCount);
	} 
      else  /* single part feature */
	 {
         if (m_iDebug)
	    fprintf(stderr,"Case 3 - single part\n");
	  
	 m_currentPart = 0;
	 startIndex = 0;
	 endIndex = psShape->nVertices-1;
	 }
      if (m_iDebug)
          fprintf(stderr,"num vertices %d startIndex %d, endIndex %d\n",
		psShape->nVertices,startIndex,endIndex);
      /* alloc and init feature here */
      nVertices = (endIndex - startIndex) + 1;
      if (m_iDebug)
          fprintf(stderr,"Number of vertices in this part is %d\n", nVertices);
      pNewFeature = allocateVecFeature((unsigned) nVertices);
      if (pNewFeature == NULL) /* alloc error */
	 {
	 *pStatus = DERR_MEM_ALLOC;
	 } 
      else
	 {
	 sprintf(pNewFeature->ID,"%d",m_currentEntity + m_currentPart);
         if (m_currentPart == 0)
	    pNewFeature->color = 255;
         else
	    pNewFeature->color = 0;  /* special attribute value */
	 switch (m_nShapeType)
	    {
	    case SHPT_POINT:
	    case SHPT_POINTZ:
	      pNewFeature->featureType = VEC_POINT_FEATURE;
	      break; 
	    case SHPT_ARC:
	    case SHPT_ARCZ:
	      pNewFeature->featureType = VEC_LINE_FEATURE;
	      break; 
	    case SHPT_POLYGON:
            case SHPT_POLYGONZ:
	      pNewFeature->featureType = VEC_POLY_FEATURE;
	      break; 
            default:
              *pStatus = DERR_UNSUP_FORMAT;
	    }
          }
      }
   if (*pStatus == 0)
      { 
      if (m_iDebug)
	 fprintf(stderr, "\nShape:%d (%s)  nVertices=%d, nParts=%d\n"
                "  Bounds:(%12.3f,%12.3f, %g, %g)\n"
                "      to (%12.3f,%12.3f, %g, %g)\n",
	        m_currentEntity, SHPTypeName(psShape->nSHPType),
                psShape->nVertices, psShape->nParts,
                psShape->dfXMin, psShape->dfYMin,
                psShape->dfZMin, psShape->dfMMin,
                psShape->dfXMax, psShape->dfYMax,
                psShape->dfZMax, psShape->dfMMax );
       for(j = 0, k=startIndex; k <= endIndex; j++, k++)
	  {
	  pNewFeature->points[j].x = psShape->padfX[k];
	  pNewFeature->points[j].y = psShape->padfY[k];
	  pNewFeature->points[j].z = psShape->padfZ[k];
	  } /* end while loop through coord records */
       SHPDestroyObject( psShape );
       if (m_partCount > 0)
	  {
	  m_currentPart++;
          if (m_currentPart >= m_partCount)
	      m_partCount = m_currentPart = 0; /* done with this feature */
          }
       /* only increment the entity count if we don't have any more parts */
       if (m_partCount == 0)
          m_currentEntity++; /* ready to read the next object */
      }     /* end if status == 0 after open */
   /* If we encountered an error after we allocated the feature
    * record, we need to free it. We also want to close the shape file
    * if open, and set the image state to indicate an error.
    */
   if (*pStatus < 0) 
      {
      if (m_hSHP != NULL)
	 {
         SHPClose(m_hSHP);
         m_hSHP = NULL;
         }
      if (pNewFeature != NULL)
         {
	 freeVecFeature(pNewFeature);
	 pNewFeature = NULL;
         }
      m_pVectorData->setState(IMG_ERROR);
      }
   if ((*pStatus == 0) && (pNewFeature != NULL))
      {
      m_pVectorData->adjustExtent(pNewFeature);
      }
   if (m_iTrace)
      logTrace("ShapeVectorDataReader::getNextFeature (ex) status is %d",
                *pStatus);
   if (m_iDebug)
      logTrace("ShapeVectorDataReader::getNextFeature (ex) status is %d\n",
                *pStatus);
   /* If there was an error, should we close the file??? */
   return pNewFeature;
   } 

	/* Test function. Is this a shape file? We base
         * this on the file suffix, plus our ability to 
         * open and read the basic information about the file.
         * @param pczVectorFilename  Name of file to test
	 * @return TRUE if this appears to be a shapefile, else FALSE
         */
BOOL ShapeVectorDataReader::vectest(const char* pczVectorFilename)
     {
     logTrace("ShapeVectorDataReader::vectest (en) - filename is %s\n",
	      pczVectorFilename);
     BOOL bIsShapefile = FALSE;
     char * pczExt = NULL;
     /* SHPOpen checks the file suffix
      * but it is too lenient. If the VEC file and the original
      * shape file are in the same directory, it will open the
      * original shape file!!
      */
     pczExt = strrchr(pczVectorFilename,'.');
     if (pczExt != NULL)
        {
	if (stricmp(pczExt,".shp") == 0)
	    bIsShapefile = TRUE;
        } 
     if (bIsShapefile)
        {
	bIsShapefile = FALSE;
	SHPHandle hSHP = SHPOpen(pczVectorFilename,"rb");
	int nEntities = 0;
	int nShapeType = 0;
	/* SHPOpen checks the file suffix
	 * but it is too lenient. If the VEC file and the original
	 * shape file are in the same directory, it will open the
	 * original shape file!!
	 */
	if (hSHP != NULL)
	   {
	   SHPGetInfo(hSHP,&nEntities,&nShapeType,NULL,NULL);
	   if ((nEntities > 0) && 
	       ((nShapeType == SHPT_ARC) ||
		(nShapeType == SHPT_POLYGON) ||
		(nShapeType == SHPT_POINT) ||
		(nShapeType == SHPT_POINTZ) ||
		(nShapeType == SHPT_ARCZ) ||
		(nShapeType == SHPT_POLYGONZ)))
	       bIsShapefile = TRUE;
	  SHPClose(hSHP);
	  }  
	}
     return bIsShapefile;
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
const char * ShapeVectorDataReader::dump(int detail, 
					 const char * pczTitle) const
    {
    static char buffer[2048];
    char temp[64];
    memset(buffer,0, sizeof(buffer));
    sprintf(buffer,"ShapeVectorDataReader %s\n",pczTitle); 
    sprintf(temp,"VectorData pointer is X%p\n", m_pVectorData);
    strcat(buffer,temp);
    //    printf(buffer);
    return(buffer);
    }

void ShapeVectorDataReader_END() { puts(FIL_ID); }
