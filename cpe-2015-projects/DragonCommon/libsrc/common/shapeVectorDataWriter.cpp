extern "C"
{
#include "drelease.h"
char SHAPEVECTORDATAWRITER_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.4 $$Date: 2008/04/26 10:55:55 $";
D_REL_IDSTR;
}
/*
 *	filename shapeVectorDataWriter.cpp
 *		$Revision: 1.4 $ $Date: 2008/04/26 10:55:55 $	
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
 *  $Id: shapeVectorDataWriter.cpp,v 1.4 2008/04/26 10:55:55 rudahl Exp $
 *  $Log: shapeVectorDataWriter.cpp,v $
 *  Revision 1.4  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.3  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.2  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.1  2006/08/09 09:49:07  goldin
 *  Adding support for writing shapefiles
 *
 *
 *
 *
 *******************************************************************
 *   This is the ShapeVectorDataWriter class. This class knows
 *   how to write vector data to an ESRI Shapefile. It is
 *   a concrete subclass of VectorDataWriter, and is created
 *   by a parent VectorData object, which holds on to global information
 *   about the vector file/datasource, including its header.
 *
 *   This class only writes vector features - not the header.
 *
 *   Created by Sally Goldin, 9 August 2006
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
#include "vectorData.h"
#include "vectorDataWriter.h"
#include "shapefil.h"
#include "shapeVectorDataWriter.h"
//#include "i18n.h"

#include "dragonOb.h"
#include "logger.h"
//#include "dp.h"

Class ShapeVectorDataWriter::s_class_Base("ShapeVectorDataWriter",
                                           "Class for writing Shape vector files");


		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
ShapeVectorDataWriter::ShapeVectorDataWriter(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("ShapeVectorDataWriter::ShapeVectorDataWriter (en)");
    if (iDebug || m_iDebug)
	printf("ShapeVectorDataWriter::ShapeVectorDataWriter (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_pVectorData = NULL;
    m_hSHP = NULL;
    m_nShapeType = SHPT_POLYGON;  /* assume type is polygon */
                                  /* may be reset */ 
    m_dragonFeatureType = VEC_POLY_FEATURE;
    m_currentEntity = -1;
    if (iTrace || m_iTrace)
	logTrace("ShapeVectorDataWriter::ShapeVectorDataWriter (ex)");
    if (iDebug || m_iDebug)
	printf("ShapeVectorDataWriter::ShapeVectorDataWriter (ex)\n");
    }
/*-------------------------------------------------------------*/

	   /* Update the shape type for the file.
            * This must be done before anything is written
            * to the file.
            * @param type  One of 'P' (polygon), 'L' (polyline)
            *              or 'M' (market). Shape files can handle
            *              other types, but Dragon cannot.
	    * @return TRUE unless some bad type is passed.
            */ 
BOOL ShapeVectorDataWriter::setShapeType(char type)
   {
   BOOL bReturn = TRUE;
   switch (type)
      {
      case 'P':
         m_nShapeType = SHPT_POLYGON;
         m_dragonFeatureType = VEC_POLY_FEATURE;
         break;
      case 'L':
         m_nShapeType = SHPT_ARC;
         m_dragonFeatureType = VEC_LINE_FEATURE;
         break;
      case 'M':
         m_nShapeType = SHPT_POINT;
         m_dragonFeatureType = VEC_POINT_FEATURE;
         break;
      default:
          bReturn = FALSE;  /* error if not a valid type */
      }         
   return bReturn;
   }
/*-------------------------------------------------------------*/

     /* Write a vector feature to the vector file. 
      * This function assumes that the header, if any,
      * has been written. It opens the file if it is not
      * yet open. 
      * It does NOT free the VECFEATURE structure after use.
      * The caller is responsible for this.
      * IFF the feature pointer is NULL, closes the file
      * and cleans up.
      * @param pFeature Pointer to feature data to write. If NULL
      *                 signals we should close 
      * @return 0 for success, negative for error,
      *         1 if feature is of wrong type. In this
      *         case we will skip the feature since
      *         shape files are only allowed to have
      *         one feature type.
      */  
int ShapeVectorDataWriter::putNextFeature(VECFEATURE* pFeature)
   { 
   int status = 0;
   int i = 0;
   if (m_pVectorData == NULL)
      {
      status = DERR_IMAGE_NOWRITE;
      return status;
      }
   const char* pczVectorFilename = m_pVectorData->getFilename();
   status = 0;
   m_currentEntity++;   /* initialized to -1 when writer is created */
   /* Is the file open? If not, then create it */
   if (m_hSHP == NULL)
      {
      m_hSHP = SHPCreate(pczVectorFilename,m_nShapeType);
      if (m_hSHP == NULL)   /* error */
	 {
         status = DERR_FILE_OPEN;
	 return status;
         }
      }
   if (pFeature == NULL)
      {
      SHPClose(m_hSHP);
      m_hSHP = NULL;
      m_pVectorData->setState(IMG_CLOSED);
      }
   else
      {
      SHPObject * psShape = NULL;
      double* xv = NULL;   /* coordinate arrays */
      double* yv = NULL;
      double* zv = NULL;
      int nVertices = pFeature->vertexCount;
      /* If this feature is the correct type, create and write it */
      if (pFeature->featureType == m_dragonFeatureType)
	 {
         xv = (double*) calloc(nVertices,sizeof(double));
         yv = (double*) calloc(nVertices,sizeof(double));
         zv = (double*) calloc(nVertices,sizeof(double));
         if ((xv == NULL) || (yv == NULL) || (zv == NULL))
	    {
            status = DERR_MEM_ALLOC;
            }
         else 
	    {
	    /* copy the coordinates */
            for (i = 0; i < nVertices; i++)
	       {
               xv[i] = pFeature->points[i].x;
               yv[i] = pFeature->points[i].y;
               zv[i] = pFeature->points[i].z;
               }
            /* create the shape to write */
            psShape = SHPCreateSimpleObject(m_nShapeType,nVertices,
                   xv, yv, zv);
            if (psShape != NULL)
	       {
               m_currentEntity = SHPWriteObject(m_hSHP, -1, psShape);
               if (m_currentEntity < 0)  /* assume this would be an error */
		  {
                  status = DERR_FILE_RW;
                  }     
               /* whether successful or not, free the object */
               SHPDestroyObject(psShape);
               }
            else
	       {
               status = DERR_MEM_ALLOC;
               }
            }
         /* free the coordinate arrays */
         if (xv != NULL) free(xv);
         if (yv != NULL) free(yv);
         if (zv != NULL) free(zv);
         } 
      else  /* Not the right feature type */
         {
         status = 1;  /* indicated that we skipped it */
         }
      }
   if ((status == 0) && (pFeature != NULL))
      {
      m_pVectorData->adjustExtent(pFeature);
      }
   if (status < 0)
      {
      if (m_hSHP != NULL)
	 {
         SHPClose(m_hSHP);
         m_hSHP = NULL;
         }
      m_pVectorData->setState(IMG_ERROR);
      }

   return status;
   }

/*-------------------------------------------------------------*/

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
const char * ShapeVectorDataWriter::dump(int detail, const char * pczTitle) const
    {
    static char buffer[2048];
    char temp[64];
    memset(buffer,0, sizeof(buffer));
    sprintf(buffer,"ShapeVectorDataWriter %s\n",pczTitle); 
    sprintf(temp,"File pointer is X%p\n", m_hSHP);
    strcat(buffer,temp);
    sprintf(temp,"VectorData pointer is X%p\n", m_pVectorData);
    strcat(buffer,temp);
    printf(buffer);
    return(buffer);
    }


void ShapeVectorDataWriter_END() { puts(FIL_ID); }
