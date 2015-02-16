extern "C"
{
#include "drelease.h"
char VECTORDATAACCESS_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.20 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
}
/*
 *	filename vectorDataAccess.cpp
 *		$Revision: 1.20 $ $Date: 2014/12/05 14:24:30 $	
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
 *  $Id: vectorDataAccess.cpp,v 1.20 2014/12/05 14:24:30 rudahl Exp $
 *  $Log: vectorDataAccess.cpp,v $
 *  Revision 1.20  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.19  2011/01/12 04:42:34  rudahl
 *  added new registration fields to update_georef and header
 *
 *  Revision 1.18  2008/09/14 10:06:19  rudahl
 *  error setting extents in shapefile
 *
 *  Revision 1.17  2008/09/12 11:42:23  rudahl
 *  added handling of extents, georef header fields; 
 *  new create() for de-novo files
 *
 *  Revision 1.16  2008/06/12 13:48:15  goldin
 *  implement rewriteHeader for vectors
 *
 *  Revision 1.15  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.14  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.13  2007/02/25 10:35:19  goldin
 *  Exposed code to set shape type for Shapefiles
 *
 *  Revision 1.12  2007/02/03 11:30:37  rudahl
 *  fixed filtering fn
 *
 *  Revision 1.11  2007/02/03 02:06:19  rudahl
 *  revised tracing
 *
 *  Revision 1.10  2007/01/28 12:48:40  goldin
 *  Add function to filter duplicate points in a vector
 *
 *  Revision 1.9  2006/11/12 07:01:06  goldin
 *  New functions to update meta info for images and vector data sets
 *
 *  Revision 1.8  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.7  2006/08/11 07:34:22  goldin
 *  Fix logic problems
 *
 *  Revision 1.6  2006/08/09 14:01:26  goldin
 *  Fix logic error in test code
 *
 *  Revision 1.5  2006/08/09 10:38:07  goldin
 *  Continued work on vector read/write/scale
 *
 *  Revision 1.4  2006/08/09 09:48:09  goldin
 *  Adding support for writing shapefiles
 *
 *  Revision 1.3  2006/08/06 11:23:44  goldin
 *  Working on georeferenced vectors
 *
 *  Revision 1.2  2006/08/05 13:21:00  goldin
 *  begin upgrade to use vectorData functions
 *
 *  Revision 1.1  2006/08/05 10:32:58  goldin
 *  C Wrapper funs for methods of the vectorData class
 *
 *
 *
 *******************************************************************
 *   This file implements a set of wrapper functions so that the
 *   methods in the VectorData class, a new class to handle
 *   reading, writing and transformation of OpenDragon vector data,
 *   can be called from C.
 *   This file is (very) roughly analagous to img_acc.cpp.
 *
 *   Created by Sally Goldin, 5 August 2006
 *	
 ****************************************************************
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

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
#include "img_acc.h"
#include "vectorData.h"
#include "vectorDataAccess.h"
//#include "i18n.h"

#include "dragonOb.h"
#include "logger.h"
//#include "dp.h"

#ifdef __cplusplus
extern "C" {
#endif

    /* Wrapper for constructor. Creates new 
     * VectorData object and returns the pointer
     * to its VECTORDATA structure.
     * @param iDebug  Use to set debug flag
     * @param iTrace  Use to set trace flag.
     * @return pointer to VECTORDATA structure.
     */
const VECTORDATA * allocateVectorData(int iDebug,int iTrace)
    {
    VectorData* v = new VectorData(iDebug,iTrace);
    return v->getVecData();
    }        
 
    /* Wrapper for destructor. 
     * @param  pVD  Structure that points to vectorData to delete.
     */
void freeVectorData(const VECTORDATA* pVD)
    {
    VectorData * v = pVD->pVectorDataObj;
    delete v;
    } 

    /* initialize all values based on header info in
     * specified file, which must exist. 
     * Should be preceeded by zero(). 
     * @param pVD               Pointer to VECTORDATA structure
     * @param pczFilename	full, long path to file
     * @return		0 if OK else negative error #:
     */
int openVectorData(const VECTORDATA* pVD, const char * pczFilename)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->open(pczFilename);
    return iReturn;
    }

    /* Set up a VectorData for output. This could be 
     * a brand new file or it could be based on an existing
     * file, depending on the value of pSrcVectors. 
     * @param pVD               pointer to VECTORDATA to set up
     * @param pczFilename	full, long path to file
     * @param bOverwrite	TRUE => silently delete if exists
     * @param pSVD	        If non-null, pointer to vector data
     *                           to copy
     * @param vectorFormat      If pSVD is null and this argument represents
     *                            a valid vector format, use it to decide
     *                            what format to create.
     * @return		0 if OK
     *			-57 => already exists and bOverwrite=FALSE
     *			-90 to -97 - invalid argument
     */
int createVectorData(const VECTORDATA* pVD, 
		    const char * pczFilename, BOOL bOverwrite,
		    const VECTORDATA* pSVD, IMGTYPE_T vectorFormat)
    {
    VectorData * pSource = NULL;
    int iReturn = 0;
    if (pSVD != NULL)
	pSource = pSVD->pVectorDataObj;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->create(pczFilename,bOverwrite,
					      pSource,vectorFormat);
    return iReturn;
    }

	/* set up a VectorData for output. This will be
         * a brand new file based on pSrcData
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcData	Vector data to initialize from
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
int createVectorDataNew(const VECTORDATA* pVD, 
			const char * pczFilename, BOOL bOverwrite,
			const VECTORDATA * pSrcData)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else if (pSrcData == NULL)
	iReturn = DERR_FN_ARG3;
    else
	iReturn = pVD->pVectorDataObj->create(pczFilename,bOverwrite,
					      pSrcData);
    return iReturn;
    }

    /* change text information (except classnames, unitnames) 
     * for an existing vector file.
     * Only the params with non-NULL vals will be changed.
     * This may be invoked after writing the header and the vector data
     * @param pVD               pointer to VECTORDATA to update
     * @param (all of them)	NULL or new value (possibly "")
     * @return		0 if OK
     *			-66 => state conflict
     *			-90 to -97 - invalid argument
     */
int updateVectorDataText(const VECTORDATA* pVD,
			 const char * pczTitle,
			 const char * pczId,
			 const char * pczComment,
			 const char * pczSource,
			 const char * pczScene,
			 const char * pczSubscene,
			 const char * pczBand,
			     const char * pczColorfileName,
			 const char * pczFtype)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->update_text(pczTitle,pczId,
						   pczComment,pczSource,pczScene,pczSubscene,
						   pczBand,NULL,"V");
    /* never set a color file - not in header */
    /* always set filetype to "V" */
    return iReturn;
    }

    /* change georeferencing information information for a vector file.
     * This may be invoked after writing the header and the image data
     *
     * NOTE: ref_x, ref_y, pczProjection, pczUnitname 
     *	 may be NULL to indicate no change
     *	 but other args MUST be supplied.
     *
     * @param pVD       pointer to VECTORDATA to update
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
     * @return		0 if OK
     *			DERR_MEM_ALLOC if allocation fails
     */
int updateVectorDataGeoref(const VECTORDATA* pVD,
			       int img_x, int img_y, 
			       const MapCoord * ref_x, const MapCoord * ref_y,
			       double xcell_size, double ycell_size,
			       const char* pczProjection, 
			       const char* pczUnitname)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->update_georef(img_x, img_y,
						     ref_x, ref_y, 
						     xcell_size, ycell_size,
						     pczProjection, 
						     pczUnitname,
						     NULL,NULL,-1); // ~~~ ?
    return iReturn;
    }

	/* set extent (bounding box) information for a vector file.
	 * This invokes update_geomery and update_extents to
	 * set pczUnitName (meter by default) and optionally pczProjection
	 * @param pVD       pointer to VECTORDATA to update
	 * @param dMinX,dMinY  	u.l. corner of bounding box in UTM
	 * @param dMaxX,dMaxY  	l.r. corner of bounding box in UTM
	 * @param pczProjection NULL or code for map proj'n 
	 * @param pczUnitname	usually 'meter'
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int updateVectorDataExtent(const VECTORDATA* pVD,
			   double dMinX,double dMinY,
			   double dMaxX,double dMaxY,
			   const char* pczProjection, 
			   const char* pczUnitname)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
        iReturn = pVD->pVectorDataObj->update_extent(dMinX,dMinY,dMaxX,dMaxY,
						     pczProjection, 
						     pczUnitname);
    return iReturn;
    }

   /* Use a source image to copy the meta file information to a target
    * vector data set. This will effectively add the vector dataset to the same
    * IGC group as the source image.
    * @param pVD           Vector data to update
    * @param pSrcImage     Image to use to get metafile information.
    * @return 0 if successful otherwise negative error code.
    */
int updateVectorMetaInfo(const VECTORDATA* pVD, const IMAGE* pSrcImage)
    {
    const IMAGEHDR * pSrcHdr = getIMAGEHDR(pSrcImage);
    return pVD->pVectorDataObj->update_metainfo(pSrcHdr->pczMetafile, pSrcHdr->pczGUID);
    } 

    /* close any open files, reset to indicate that the file
     * is not currently valid.
     * @param  pVD   Pointer to VECTORDATA to close
     */
int closeVectorData(const VECTORDATA* pVD)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->close();
    return iReturn;
    }

    /*	write vectorData header and close output file
     *	On exit, file is closed
     * @param  pVD   Pointer to VECTORDATA to close
     *	Return 0 if OK and set m_iErrno to 0.
     *	Error values are:
     *		-60 => header completely uninitialized 
     *		-64 => there's alread an open file in pFp,
     *			so just leave values alone
     *		-65 => no name supplied
     *		-69 => no header writer found
     */
int writeVectorDataHeader(const VECTORDATA* pVD)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->writeHeader();
    return iReturn;
    }

    /*	rewrite vectorData header and close output file
     *	On exit, file is closed
     * @param  pVD   Pointer to VECTORDATA to close
     *	Return 0 if OK and set m_iErrno to 0.
     *	Error values are:
     *		-60 => header completely uninitialized 
     *		-64 => there's alread an open file in pFp,
     *			so just leave values alone
     *		-65 => no name supplied
     *		-69 => no header writer found
     */
int rewriteVectorDataHeader(const VECTORDATA* pVD)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = pVD->pVectorDataObj->rewriteHeader();
    return iReturn;
    }

    /* Get the header fields as a struct for use in C
     * Returns null if argument is bad.
     */
const IMAGEHDR * getVectorIMAGEHDR(const VECTORDATA* pVD)
    {  
    if (pVD == NULL)
	return NULL;
    else
	return (pVD->pVectorDataObj->getIMAGEHDR());
    }
      
    /* Get a vector feature from the file/data sourc. 
     * This function allocates the structure
     * that is returned. The caller must free the structure by
     * calling freeVecFeature()
     * @param  pVD      Initialized VECTORDATA (init for input)
     * @param  pStatus  0 is returned in this variable for success,
     *                  otherwise an error number
     * @param  bTransformOnRead  If true, transform from geographic
     *                to screen coordinates before returning to the caller
     * @return pointer to new VECFEATURE structure or null if error.
     */
VECFEATURE * getNextFeature(const VECTORDATA* pVD,
                    int* pStatus, BOOL bTransformOnRead)
    {
    if (pVD == NULL)
	return NULL;
    else
	return (pVD->pVectorDataObj->getNextFeature(pStatus,bTransformOnRead));
    }

    /* Write a vector feature to the vector file. 
     * This function assumes that the header, if any,
     * has been written. 
     * This is a wrapper for the vectorDataWriter function
     * of the same name.
     * IFF the feature pointer is NULL, does any necessary
     * cleanup or finalization of the output file.
     * @param  pVD      Initialized VECTORDATA (init for output)
     * @param pFeature Pointer to feature data to write. If NULL
     *                 signals we should write "-END" 
     * @param  bTransformOnWrite  If true, transform from 
     *                  screen to geographic
     *                  coordinates before writing.
     * @return 0 for success, negative for error.
     */  
int putNextFeature(const VECTORDATA* pVD,
		   VECFEATURE* pFeature,BOOL bTransformOnWrite)
    {
    int iReturn = 0;
    if (pVD == NULL)
	iReturn = DERR_FN_ARG0;
    else
	iReturn = 
	    pVD->pVectorDataObj->putNextFeature(pFeature,bTransformOnWrite);
    return iReturn;
    }


    /* Set the data type for this data set.
     * Currently only relevant for Shapefiles, which
     * can hold only one type of feature.
     * Returns TRUE unless invalid type is passed 
     */
BOOL setVectorShapeType(const VECTORDATA* pVD,char type)
    {
    return pVD->pVectorDataObj->setShapeType(type);
    }

/**/
  /* Compute the extent of the passed vector data source   
   * by reading through it completely. 
   * Encapsulates the construction, opening, reading, closing
   * and freeing of the vector data source.
   * @param filename   Name of vector data source to read
   * @param minExtent  Pointer to vertex that will be set to hold 
   *			minimum extent
   * @param maxExtent  Pointer to vertex that will be set to hold
   *			maximum extent
   * @param pGeog      Set true if the file seems to have geographic coords
   *			else set false.
   * @return  		0 if successful, else negative error number
   */
int computeVectorExtent(const char* filename, 
			VERTEX * minExtent, VERTEX * maxExtent,BOOL * pGeog)
    {
    int status = 0;
    VectorData * pVectorData = new VectorData(0,1);
    VECFEATURE * pFeature = NULL;
    const VECTORDATA* pVD = NULL; 
    /* open the vector data file */ 
    status = pVectorData->open(filename);
    while (status >= 0) 
        {
	/* Read - adjusting the extent is a side effect of the reading */
	pFeature = pVectorData->getNextFeature(&status,FALSE);
	if (pFeature == NULL) 
	    break;
	else
	    freeVecFeature(pFeature);
	}
    pVD = pVectorData->getVecData();
    *pGeog = isGeographic(pVD);
    minExtent->x = pVD->minExtent.x;
    minExtent->y = pVD->minExtent.y;
    maxExtent->x = pVD->maxExtent.x;
    maxExtent->y = pVD->maxExtent.y;
    pVectorData->close();
    delete pVectorData;
    return status;
    }

   /* Is the passed VECTORDATA data source georeferenced
    * or not? We can't know for sure but if either the
    * x reference coordinate is not 0, or the minimum X extent
    * is greater than 1024, we will say that it is. 
    * @param pVD vector data source to check
    * @rturn TRUE if we think it is geographic, FALSE if not.
    */
BOOL isGeographic(const VECTORDATA* pVD)
    {
    BOOL bGeog = FALSE;
    if ((pVD != NULL) && (pVD->bValid))
        { 
	const IMAGEHDR* pHdr = getVectorIMAGEHDR(pVD);
	if ((pHdr != NULL) && (pHdr->ref_x.v0 != 0))
	    bGeog = TRUE;
	else if (pVD->minExtent.x > 1024)
	    bGeog = TRUE;
	}
    return bGeog;
    }

/* ~~~ limited size of vector coordinates at present, due to
 * algo in georast.c. See vectorData.h
 */
//#define VECTOR_MAX_X 8000
//#define VECTOR_MAX_Y 8000
  /* Filter out duplicate points in a vector feature.
   * Returns pointer to the same feature, but with the vertex
   * count adjusted and duplicate successive points
   * removed.
   * This also clips the coordinates to be >= 0 and <= VECTOR_MAX
   * to make them compat. with georast.c algorithms.
   * @param pFeature  	Feature to filter
   * @return 		pointer to feature after adjustment.
   */
VECFEATURE * filterDuplicatePoints(VECFEATURE * pFeature)
    {
    VERTEX lastVertex;
    uint uCount = 1;
    uint uMaxCount = pFeature->vertexCount;
    unsigned int uPnt = 0;
    unsigned int j = 0;
    int iFeatureNumber = atoi(pFeature->ID);
    logTrace("filterDuplicatePoints (en) feature %d",iFeatureNumber); 
//    if (iFeatureNumber == 1627)
//        {
//	logTrace("filterDuplicatePoints skipping %s listed below",
//		 pFeature->ID); 
//	for (uPnt = 0; uPnt < pFeature->vertexCount; uPnt++)
//            {   
//	    logTrace("    vertexNo=%d x=%7.2f y=%7.2f",
//		     uPnt,pFeature->points[uPnt].x,pFeature->points[uPnt].y); 
//	    }
//	return pFeature; //~~~ don't filter this one
//	}
    if (pFeature->points[0].x < 0)
	pFeature->points[0].x = 0;
    if (pFeature->points[0].y < 0)
	pFeature->points[0].y = 0;
    if (pFeature->points[0].x > VECTOR_MAX_X)
	pFeature->points[0].x = VECTOR_MAX_X;
    if (pFeature->points[0].y > VECTOR_MAX_Y)
	pFeature->points[0].y = VECTOR_MAX_Y;
    lastVertex.x = pFeature->points[0].x;
    lastVertex.y = pFeature->points[0].y;
    for (uPnt = 1; uPnt < uMaxCount; uPnt++)
        {   
	if (pFeature->points[uPnt].x < 0)
	    pFeature->points[uPnt].x = 0;
	if (pFeature->points[uPnt].y < 0)
	    pFeature->points[uPnt].y = 0;
	if (pFeature->points[uPnt].x > VECTOR_MAX_X)
	     pFeature->points[uPnt].x = VECTOR_MAX_X;
	if (pFeature->points[uPnt].y > VECTOR_MAX_Y)
	    pFeature->points[uPnt].y = VECTOR_MAX_Y;
	if ((fabs(pFeature->points[uPnt].x - lastVertex.x) >= 1.0)
	    || (fabs(pFeature->points[uPnt].y - lastVertex.y) >= 1.0))
	    {
	    /* if the points differ by at least one pixel */  
	    lastVertex.x = pFeature->points[uPnt].x;
	    lastVertex.y = pFeature->points[uPnt].y;
	    /* move on */
	    }  
	else /* move up all the elements of the array */
	    {
	    for (j = uPnt+1; j < pFeature->vertexCount; j++)
	        {
   	        pFeature->points[j-1].x = pFeature->points[j].x;
		pFeature->points[j-1].y = pFeature->points[j].y;
		}
	    uMaxCount--;
	    }
	uCount++;
	}
    logTrace("filterDuplicatePoints: "
	     "For feature %s original count was %d and revised count is %d", 
	     pFeature->ID, pFeature->vertexCount, uCount);
//    if (iFeatureNumber == 1627)
//        {
//	logTrace("filterDuplicatePoints results of %s listed below",
//		 pFeature->ID); 
//	for (uPnt = 0; uPnt < pFeature->vertexCount; uPnt++)
    //           {   
//	    logTrace("    vertexNo=%d x=%7.2f y=%7.2f",
//		     uPnt,pFeature->points[uPnt].x,pFeature->points[uPnt].y); 
//	    }
//	return pFeature; //~~~ don't filter this one
//	}
    pFeature->vertexCount = uCount;   
    /***
	if (iCount < 20)
	for (j = 0; j < pFeature->vertexCount; j++)
	logTrace("   %d: x %f  y %f", 
	j, pFeature->points[j].x,pFeature->points[j].y);  
    **/
    logTrace("filterDuplicatePoints (ex)"); 
    return pFeature;  
    }

void VectorDataAccess_END() { puts(FIL_ID); }

/************************************************************************/
#ifdef TEST

extern "C"
{

void usage()
     {
    printf ("Test VectorDataAccess class by reading some file header\n");
    printf ("Usage: VectorDataAccess.TEST inputfilepath outputfilepath\n");
    exit(1);
    }

int main(int argc, char ** argv)
     {
    MapCoord refx;
    MapCoord refy;
    const VECTORDATA* pInV;
    const VECTORDATA* pOutV;

    VECFEATURE * pNextFeature = NULL;
    char czFilename[PATH_MAX] = "";
    char czOutFilename[PATH_MAX] = "";
    if (argc < 3)
	usage();
    strcpy(czFilename,argv[1]);
    strcpy(czOutFilename,argv[2]);
    
    printf("+++ Try to read existing file \n");
    pInV = allocateVectorData(1,1);
    int error = openVectorData(pInV,czFilename);
    if (error < 0)
        {
        printf("Error %d trying to open file %s\n", error,czFilename);
        exit(0);
        }
    printf("+++ Try to open output file \n");
    pOutV = allocateVectorData(0,0);
    error = createVectorData(pOutV,czOutFilename,TRUE,NULL,IT_DRAGON_VEC);
    if (error < 0)
        {
        printf("Error %d trying to create output file\n",error);
        exit(0);
        }
    refx.v0 = 10000.0;
    refy.v0 = 20000.0;

    //    error = updateVectorDataGeoref(pOutV,
    //           0,0,&refx,&refy,10.0,-10.0,NULL,"meters");
    //if (error < 0)
    //    {
    //    printf("Error %d trying to update georeferencing \n",error);
    //    exit(0);
    //    }
    error = writeVectorDataHeader(pOutV);
    if (error < 0)
        {
        printf("Error %d trying to write header\n",error);
        exit(0);
        }

    printf("+++ Try to read vector file and copy to the output file...\n");
    while (error >= 0)
       {
       pNextFeature = getNextFeature(pInV,&error,TRUE);
       if (pNextFeature != NULL)
	  {
          printf("===================\n");
          printf("Just read: \n");
          pInV->pVectorDataObj->dumpVECFEATURE(pNextFeature);
          printf("-----------\n");
          error = putNextFeature(pOutV,pNextFeature,TRUE);
          if (error < 0)
	     {
             printf("Error %d writing vectors\n", error); 
             }
          else
	     {
             printf("Just wrote: \n");
             pOutV->pVectorDataObj->dumpVECFEATURE(pNextFeature);
             }
	  freeVecFeature(pNextFeature);
          }
       else
	  {
	  break;
          }
       }
    if (error < 0)    
        {
        printf("Error %d reading or writing vectors\n", error);
        exit(0);
        }
    /* write the 'END' record */
    putNextFeature(pOutV,NULL,FALSE);

    freeVectorData(pInV);
    freeVectorData(pOutV);
    return 0;
    }
}

#endif /* TEST */

#ifdef __cplusplus
    }
#endif




