extern "C"
{
#include "drelease.h"
char DRAGONVECTORDATAWRITER_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.10 $$Date: 2015/01/21 10:37:33 $";
D_REL_IDSTR;
}
/*
 *	filename dragonVectorDataWriter.cpp
 *		$Revision: 1.10 $ $Date: 2015/01/21 10:37:33 $	
 *
 *      ~~ Copyright 2006-2015 Kurt Rudahl and Sally Goldin
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
 *  $Id: dragonVectorDataWriter.cpp,v 1.10 2015/01/21 10:37:33 rudahl Exp $
 *  $Log: dragonVectorDataWriter.cpp,v $
 *  Revision 1.10  2015/01/21 10:37:33  rudahl
 *  improving imageReader - 2drag coordination
 *
 *  Revision 1.9  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.8  2008/09/12 11:42:23  rudahl
 *  added handling of extents, georef header fields; new create() for de-novo files
 *
 *  Revision 1.7  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.6  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.5  2006/09/17 13:33:35  goldin
 *  deal with special cases
 *
 *  Revision 1.4  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.3  2006/08/11 07:34:22  goldin
 *  Fix logic problems
 *
 *  Revision 1.2  2006/08/05 13:21:00  goldin
 *  begin upgrade to use vectorData functions
 *
 *  Revision 1.1  2006/08/04 11:06:40  goldin
 *  Create class hierarchy similar to that for image classes
 *
 *
 *
 *******************************************************************
 *   This is the DragonVectorDataWriter class. This class knows
 *   how to write vector data to a Dragon vector file. It is
 *   a concrete subclass of VectorDataWriter, and is created
 *   by a parent VectorData object, which holds on to global information
 *   about the vector file/datasource, including its header.
 *
 *   This class only writes vector features - not the header.
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
//#include <errno.h>	/* perror */

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
#include "vectorDataWriter.h"
#include "dragonVectorDataWriter.h"
//#include "i18n.h"

//#include "dp.h"

Class DragonVectorDataWriter::s_class_Base("DragonVectorDataWriter",
                                           "Class for writing Dragon vector files");

extern "C"
{
const char* featureTypeCodes[] = {FEATURE_TYPE_CODES};
}

		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
DragonVectorDataWriter::DragonVectorDataWriter(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("DragonVectorDataWriter::DragonVectorDataWriter (en)");
    if (iDebug || m_iDebug)
	fprintf(stderr,"DragonVectorDataWriter::DragonVectorDataWriter (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_pVectorData = NULL;
    m_Fp = NULL;
    m_lastWritten = -1;
    if (iTrace || m_iTrace)
	logTrace("DragonVectorDataWriter::DragonVectorDataWriter (ex)");
    if (iDebug || m_iDebug)
	fprintf(stderr,"DragonVectorDataWriter::DragonVectorDataWriter (ex)\n");
    }
/*-------------------------------------------------------------*/

     /* Write a vector feature to the vector file. 
      * This function assumes that the header, if any,
      * has been written. It opens the file for append access,
      * the first time the function is called. It
      * closes the file when the function is called with
      * VECFEATURE* = NULL.
      * It does NOT free the VECFEATURE structure after use.
      * The caller is responsible for this.
      * IFF the feature pointer is NULL, writes an END record
      * to the file before closing the file.
      * @param pFeature Pointer to feature data to write. If NULL
      *                 signals we should write "-END" 
      * @return 0 for success, negative for error.
      */  
int DragonVectorDataWriter::putNextFeature(VECFEATURE* pFeature)
   { 
   int status = 0;
   int i = 0;
   status = 0;
   if (m_pVectorData == NULL)
      {
      status = DERR_IMAGE_NOWRITE;
      return status;
      }
   const char* pczVectorFilename = m_pVectorData->getFilename();
   if (m_Fp == NULL)
      {
      m_Fp = fopen(pczVectorFilename,"a");
      if (m_Fp == NULL)
         {
         status = DERR_FILE_OPEN;
         }
      }
   if (status == 0)
      {
      if (pFeature == NULL) /* end of the file */
	 {
	 fprintf(m_Fp,"-END\n");
	 fclose(m_Fp);
	 m_Fp = NULL;
	 m_pVectorData->setState(IMG_CLOSED);
	 }
      else
	 {
	 m_lastWritten++;   /* initialized to -1 when writer is created */
	 fprintf(m_Fp,"-FIGURE %d %s %d %d\n", 
		  m_lastWritten,featureTypeCodes[pFeature->featureType], 
		  pFeature->vertexCount, pFeature->color);
	 for (i = 0; i < (int) pFeature->vertexCount; i++)
	    {
	    fprintf(m_Fp,"-COORDS %10.5f %10.5f %d\n",
		      pFeature->points[i].x, pFeature->points[i].y,
		      (int) pFeature->points[i].z);
	    } 
	 /* if this feature is filled, write an "INTERNAL" record. */
	 if (pFeature->fillColor >= 0)
	    {
	    fprintf(m_Fp,"-INTERNAL %d %d\n", m_lastWritten, 
                      pFeature->fillColor);
	    }
	 }
      }  /* if status == 0 */
   if ((status == 0) && (pFeature != NULL))
      {
      m_pVectorData->adjustExtent(pFeature);
      m_pVectorData->incrementFeatureCount();
      }
   else if (status < 0)
      {
      if (m_Fp != NULL)
	 {
         fclose(m_Fp);
         m_Fp = NULL;
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
const char * DragonVectorDataWriter::dump(int detail, const char * pczTitle) const
    {
    static char buffer[2048];
    char temp[64];
    memset(buffer,0, sizeof(buffer));
    sprintf(buffer,"DragonVectorDataWriter %s\n",pczTitle); 
    sprintf(temp,"File pointer is X%p\n", m_Fp);
    strcat(buffer,temp);
    sprintf(temp,"VectorData pointer is X%p\n", m_pVectorData);
    strcat(buffer,temp);
    //    printf(buffer);
    return(buffer);
    }

void DragonVectorDataWriter_END() { puts(FIL_ID); }
