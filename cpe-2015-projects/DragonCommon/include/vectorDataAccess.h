/*
 *	filename vectorDataAccess.h		- 
 *		$Revision: 1.12 $ $Date: 2014/12/05 12:32:30 $	
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
 ****************************************************************
 *   $Id: vectorDataAccess.h,v 1.12 2014/12/05 12:32:30 rudahl Exp $
 *   $Log: vectorDataAccess.h,v $
 *   Revision 1.12  2014/12/05 12:32:30  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.11  2008/09/12 11:44:23  rudahl
 *   added handling of extents, georef header fields; new create() for de-novo files
 *
 *   Revision 1.10  2008/06/12 13:48:15  goldin
 *   implement rewriteHeader for vectors
 *
 *   Revision 1.9  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.8  2007/02/25 10:35:06  goldin
 *   Exposed code to set shape type for Shapefiles
 *
 *   Revision 1.7  2007/01/28 12:48:30  goldin
 *   Add function to filter duplicate points in a vector
 *
 *   Revision 1.6  2006/11/12 07:00:51  goldin
 *   New functions to update meta info for images and vector data sets
 *
 *   Revision 1.5  2006/08/09 10:38:07  goldin
 *   Continued work on vector read/write/scale
 *
 *   Revision 1.4  2006/08/06 11:23:08  goldin
 *   Adding new functions for working in grstop-geometry
 *
 *   Revision 1.3  2006/08/05 13:21:00  goldin
 *   begin upgrade to use vectorData functions
 *
 *   Revision 1.2  2006/08/05 10:35:07  goldin
 *   C wrapper fun declarations
 *
 *   Revision 1.1  2006/08/05 04:46:13  goldin
 *   Header file for C wrappers
 *
 *
 *
 *******************************************************************
 *   Header file for the VectorDataAccess. This module defines 
 *   a set of wrapper functions that can be called from C,
 *   for the functions that exist in VectorData.cpp.
 *
 *   Requires header file vectorData.h
 *
 *   Created by Sally Goldin, 5 August 2006
 *	
 ****************************************************************
 */
#ifndef VECTORDATAACCESS_H
#define VECTORDATAACCESS_H	/* signal this file has been loaded */


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
const VECTORDATA * allocateVectorData(int iDebug,int iTrace);
 
    /* Wrapper for destructor. 
     * @param  pVD  Structure that points to vectorData to delete.
     */
void freeVectorData(const VECTORDATA* pVD);

    /* initialize all values based on header info in
     * specified file, which must exist. 
     * Should be preceeded by zero(). 
     * @param pVD               Pointer to VECTORDATA structure
     * @param pczFilename	full, long path to file
     * @return		0 if OK else negative error #:
     */
int openVectorData(const VECTORDATA* pVD, const char * pczFilename);

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
     * @return		0 if OK
     *			-57 => already exists and bOverwrite=FALSE
     *			-90 to -97 - invalid argument
     */
int createVectorData(const VECTORDATA* pVD, 
			 const char * pczFilename, BOOL bOverwrite,
			 const VECTORDATA* pSVD,IMGTYPE_T vectorFormat);

	/* set up a VectorData for output. This will be
         * a brand new file based on pSrcData
	 * @param pVD    	pointer to VECTORDATA to set up
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcData	Vector data to initialize from
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
int createVectorDataNew(const VECTORDATA* pVD, 
			const char * pczFilename, BOOL bOverwrite,
			const VECTORDATA * pSrcData);

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
			     const char * pczFtype);

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
			       const char* pczUnitname);

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
			   const char* pczUnitname);

      /* Use a source image to copy the meta file information to a target
       * vector data set. This will effectively add the vector dataset 
       * to the same IGC group as the source image.
       * @param pVD           Vector data to update
       * @param pSrcImage     Image to use to get metafile information.
       * @return 0 if successful otherwise negative error code.
       */
int updateVectorMetaInfo(const VECTORDATA* pVD, const IMAGE* pSrcImage);

    /* close any open files, reset to indicate that the file
     * is not currently valid.
     * @param  pVD   Pointer to VECTORDATA to close
     */
int closeVectorData(const VECTORDATA* pVD);

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
int writeVectorDataHeader(const VECTORDATA* pVD);

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
int rewriteVectorDataHeader(const VECTORDATA* pVD);


    /* Get the header fields as a struct for use in C */
const IMAGEHDR * getVectorIMAGEHDR(const VECTORDATA* pVD);
      
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
                        int* pStatus, BOOL bTransformOnRead);

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
		       VECFEATURE* pFeature,BOOL bTransformOnWrite);


    /* Set the data type for this data set.
     * Currently only relevant for Shapefiles, which
     * can hold only one type of feature.
     * Returns TRUE unless invalid type is passed 
     */
BOOL setVectorShapeType(const VECTORDATA* pVD,char type);


    /* Compute the extent of the passed vector data source   
     * by reading through it completely. 
     * Encapsulates the construction, opening, reading, closing
     * and freeing of the vector data source.
     * @param filename   Name of vector data source to read
     * @param minExtent  Pointer to vertex that will be set to hold minimum extent
     * @param maxExtent  Pointer to vertex that will be set to hold maximum extent
     * @param pGeog      Return true if the file seems to have geographic coords, else false.
     * @return  0 if successful, else negative error number
     */
int computeVectorExtent(const char* filename, VERTEX * minExtent, 
                            VERTEX * maxExtent, BOOL* pGeog);

    /* Is the passed VECTORDATA data source georeferenced
     * or not? We can't know for sure but if either the
     * x cellsize is not 1, or the minimum X extent
     * is greater than 1024, we will say that it is. 
     * @param pVD vector data source to check
     * @return TRUE if we think it is geographic, FALSE if not.
     */
BOOL isGeographic(const VECTORDATA* pVD);


    /* Filter out duplicate points in a vector feature.
     * Returns the same pointer, but with the vertex
     * count adjusted and duplicate successive points
     * removed.
     * @param pFeature  Feature to filter
     * @return pointer to feature after adjustment.
     */
VECFEATURE * filterDuplicatePoints(VECFEATURE * pFeature);

#ifdef __cplusplus
        }
#endif

#endif



