extern "C"
{
#include "drelease.h"
char DRAGONVECTORDATAREADER_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.9 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
}
/*
 *	filename dragonVectorDataReader.cpp
 *		$Revision: 1.9 $ $Date: 2014/12/05 14:24:30 $	
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
 *  $Id: dragonVectorDataReader.cpp,v 1.9 2014/12/05 14:24:30 rudahl Exp $
 *  $Log: dragonVectorDataReader.cpp,v $
 *  Revision 1.9  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.8  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.7  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.6  2007/01/27 11:11:36  rudahl
 *  improve tracing
 *
 *  Revision 1.5  2006/11/20 11:15:35  goldin
 *  comment out some tracing
 *
 *  Revision 1.4  2006/09/30 10:21:20  goldin
 *  Fixing bug in reading/writing fill
 *
 *  Revision 1.3  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.2  2006/08/06 11:23:44  goldin
 *  Working on georeferenced vectors
 *
 *  Revision 1.1  2006/08/04 11:06:40  goldin
 *  Create class hierarchy similar to that for image classes
 *
 *
 *
 *******************************************************************
 *   This is the DragonVectorDataReader class. This class knows
 *   how to read vector data from a Dragon vector file. It is
 *   a concrete subclass of VectorDataReader, and is created
 *   by a parent VectorData object, which holds on to global information
 *   about the vector file/datasource, including its header.
 *
 *   Created by Sally Goldin, 4 August 2006
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
#include "vectorData.h"
#include "vectorDataReader.h"
#include "dragonVectorDataReader.h"
//#include "i18n.h"

//#include "dp.h"

Class DragonVectorDataReader::s_class_Base("DragonVectorDataReader","Class for reading Dragon vector files");

		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
DragonVectorDataReader::DragonVectorDataReader(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("DragonVectorDataReader::DragonVectorDataReader (en)");
    if (iDebug || m_iDebug)
	printf("DragonVectorDataReader::DragonVectorDataReader (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_pVectorData = NULL;
    m_Fp = NULL;
    if (iTrace || m_iTrace)
	logTrace("DragonVectorDataReader::DragonVectorDataReader (ex)");
    if (iDebug || m_iDebug)
	printf("DragonVectorDataReader::DragonVectorDataReader (ex)\n");
    }

/*-------------------------------------------------------------*/
        /* Read the next vector feature and any fill information
         * from the vector file. This function allocates the structure
         * that is returned. The caller must free the structure by
         * calling freeVecFeature()
         *
         * @param  pStatus  0 is returned in this variable for success,
         *                  otherwise an error number
         * @return pointer to new VECFEATURE structure or null if error.
         */
VECFEATURE * DragonVectorDataReader::getNextFeature(int* pStatus)
   {
   long localStatus = 0;
   char inbuf[256];
   if (m_iTrace)
      logTrace("DragonVectorDataReader::getNextFeature (en)");
   if (m_pVectorData == NULL)
      {
      *pStatus = DERR_IMAGE_NOREAD;
      logTrace("getNextFeature - m_pVectorData (parent vectorData) is null");
      return NULL; 
      }
   const char* pczVectorFilename = m_pVectorData->getFilename();
   BOOL bHasHeader = m_pVectorData->headerExists(pczVectorFilename);
   VECFEATURE * pNewFeature = NULL;
   *pStatus = 0;
   /* If the file is not open, we open it and skip 
    * the header, if any 
    */
   if (m_Fp == NULL)
      {
      //printf("Opening vector file \n");
      m_Fp = fopen(pczVectorFilename,"r");
      if (m_Fp == NULL)
	 {
         *pStatus = DERR_FILE_OPEN;
         }
      else if (bHasHeader)
	 {
	 //printf("Skipping header\n");
         localStatus = fseek(m_Fp,DHEAD,SEEK_SET);
         if (localStatus != 0)
	     {
             *pStatus = DERR_FILE_SEEK;  
	     }
         }
      }
   if (*pStatus == 0)
      {
      char * fgetsReturn = NULL;
      char * dummy;
      int vertexCount = 0;
      int id = 0;
      int fillId = 0;
      int color = 0;
      char typecode;
      memset(inbuf,0,sizeof(inbuf));
      /* find the start of the next feature */
      //printf("Looking for the next feature\n");
      while ((fgetsReturn = fgets(inbuf,sizeof(inbuf)-1,m_Fp)) != NULL)
	 {
	 //if (m_iTrace)
 	 //   logTrace("getNextFeature -  Read: %s",inbuf);
	 //printf("getNextFeature -  Read: %s",inbuf);
         if (strncmp(inbuf,"-FIGURE",strlen("-FIGURE")) == 0)
            break;
         } 
      if (fgetsReturn == NULL)  /* No more records */
	 {
         fclose(m_Fp);
         m_Fp = NULL;
         return pNewFeature; /* which will be null */
         }
      /* parse feature record */ 
      dummy = strpbrk(inbuf," ,\r\n");
      if (dummy)
	  {	
	  char * endptr = NULL;
          char * endptr2 = NULL;
          char * endptr3 = NULL;
          char * endptr4 = NULL;
	  id = (int) strtol(dummy,&endptr,10);
	  endptr2=strtok(endptr," \r\n");
          if (endptr2 != NULL)
	      {
	      typecode = *endptr2;
	      endptr2 = strtok(NULL,"\r\n");	// rest of line
	      }
          if (endptr2 != NULL)
	      {
  	      vertexCount = (int) strtol(endptr2,&endptr3,10);
              }
          if (endptr3 != NULL)
	      {
	      color = (int) strtol(endptr3,&endptr4,10);
	      }
	  if ((endptr2 == NULL) || (endptr3 == NULL) ||
              (dummy==endptr) || (typecode < 'A')
	      || ( endptr2==endptr3) || (endptr3 == endptr4))
	     *pStatus = DERR_IMAGE_CORRUPT;  /* bad format */
	  /* alloc and init feature here */
          pNewFeature = allocateVecFeature((unsigned) vertexCount);
          if (pNewFeature == NULL) /* alloc error */
	      {
              *pStatus = DERR_MEM_ALLOC;
              } 
          else
              {
              snprintf(pNewFeature->ID,sizeof(pNewFeature->ID),
		       "%d",id);
              pNewFeature->color = color;
              switch (typecode)
		 {
                 case 'M':
                    pNewFeature->featureType = VEC_POINT_FEATURE;
                    break; 
                 case 'L':
                    pNewFeature->featureType = VEC_LINE_FEATURE;
                    break; 
                 case 'P':
                    pNewFeature->featureType = VEC_POLY_FEATURE;
                    break; 
		 default:
                    *pStatus = DERR_IMAGE_CORRUPT;
		    break;
                 }
              }
  	  }
      else  /* dummy is null */
	  {
	  *pStatus = DERR_IMAGE_CORRUPT;
          }

      int j = 0; /* counter for COORDS records */
      while ((*pStatus == 0) && (j < vertexCount) &&
             ((fgets(inbuf,sizeof(inbuf)-1,m_Fp) != NULL)))
	  {
	    //printf("getNextFeature -  COORDS Read: %s",inbuf);
	  /* read the next 'vertexCount' records and try to parse
           * them as coordinate records
           */
	  if (strncmp(inbuf,"-COORDS",strlen("-COORDS")) != 0)
              {
              *pStatus = DERR_IMAGE_CORRUPT; /* bad format */
              break;  /* exit from loop */
              }             
	  dummy = strpbrk(inbuf," ,\r\n");
	  if (dummy)
	      {	
	      char * endptr = NULL; 
	      char * endptr2 = NULL;
	      pNewFeature->points[j].x = strtod(dummy,&endptr);
	      pNewFeature->points[j].y = strtod(endptr,&endptr2);
	      pNewFeature->points[j].z = strtod(endptr2,NULL);
	      if ((dummy==endptr) || (endptr == endptr2))
		  {
                  *pStatus = DERR_IMAGE_CORRUPT;
                  }
              else
		  { 
	          j += 1;
                  }
	      } /* end if dummy not null */
	  else
	      {
	      *pStatus = DERR_IMAGE_CORRUPT;
              }
	  } /* end while loop through coord records */
      
      /* If we got a feature, check if the next line is an "INTERNAL" */
      long currentFilePos = ftell(m_Fp);
      if (currentFilePos <= 0)
	 {
	 *pStatus = DERR_FILE_SEEK;
         }
      if ((*pStatus == 0) && (pNewFeature != NULL))
         {
	 /* get one record */
	 memset(inbuf,0,sizeof(inbuf));
	 if (fgets(inbuf,sizeof(inbuf)-1,m_Fp) != NULL)
            {
	    if (strncmp(inbuf,"-INTERNAL",strlen("-INTERNAL")) == 0) // fill 
	       { 
	       dummy = strpbrk(inbuf," ,\r\n");
	       if (dummy)
		   {	
		   char * endptr,* endptr2;
		   fillId = (int) strtol(dummy,&endptr,10);
		   color = (int) strtol(endptr,&endptr2,10);
		   if ((dummy==endptr) || (endptr == endptr2))
		       {
		       *pStatus = DERR_IMAGE_CORRUPT;
		       } 
		   else if (fillId == id) /* we will ignore if IDs do not match */
		       {
                       if (m_iTrace)
                           logTrace("    Found fill record with color %d", color); 
		       pNewFeature->fillColor = color;
		       }
		   }
	       else
		   {
		   *pStatus = DERR_IMAGE_CORRUPT;
		   }
	       } /* end if 'I' */
	    else /* not an INTERNAL record, so reset the file pointer backwards */
	       {
	       if (fseek(m_Fp,currentFilePos,SEEK_SET) != 0)
		  {
		  *pStatus = DERR_FILE_SEEK;
		  }
	       }
            } /* end if fgets is successful */
	  }   /* end if status is zero and we have a feature */
       }      /* end if status == 0 after open */
	 
   /* If we encountered an error after we allocated the feature
    * record, we need to free it.
    */
   if ((*pStatus < 0) && (pNewFeature != NULL))
      {
      freeVecFeature(pNewFeature);
      pNewFeature = NULL;
      } 
   if ((*pStatus == 0) && (pNewFeature != NULL))
      {
      m_pVectorData->adjustExtent(pNewFeature);
      }
   /* If there was an error, close the file and set the state to indicate
    * this fact.
    */
   if (*pStatus < 0)
      {
      logTrace("DragonVectorDataReader::getNextFeature (ex) with error - status is %d",
                *pStatus);
      if (m_Fp != NULL)
	 {
         fclose(m_Fp);
         m_Fp = NULL;
         }
      m_pVectorData->setState(IMG_ERROR);
      }
    if (m_iTrace)
        logTrace("DragonVectorDataReader::getNextFeature (ex) status is %d",
		 *pStatus);
    return pNewFeature;
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
const char * DragonVectorDataReader::dump(int detail, const char * pczTitle) const
    {
    static char buffer[2048];
    char temp[64];
    memset(buffer,0, sizeof(buffer));
    sprintf(buffer,"DragonVectorDataReader %s\n",pczTitle); 
    sprintf(temp,"File pointer is X%p\n", m_Fp);
    strcat(buffer,temp);
    sprintf(temp,"VectorData pointer is X%p\n", m_pVectorData);
    strcat(buffer,temp);
    printf(buffer);
    return(buffer);
    }

void DragonVectorDataReader_END() { puts(FIL_ID); }
