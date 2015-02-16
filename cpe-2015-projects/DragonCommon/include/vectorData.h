/*
 *	filename vectorData.h		- 
 *		$Revision: 1.20 $ $Date: 2014/12/05 10:38:00 $	
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
 *   $Id: vectorData.h,v 1.20 2014/12/05 10:38:00 rudahl Exp $
 *   $Log: vectorData.h,v $
 *   Revision 1.20  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.19  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.18  2010/12/11 07:46:24  rudahl
 *   lint
 *
 *   Revision 1.17  2008/09/12 11:44:23  rudahl
 *   added handling of extents, georef header fields; new create() for de-novo files
 *
 *   Revision 1.16  2008/06/12 13:48:15  goldin
 *   implement rewriteHeader for vectors
 *
 *   Revision 1.15  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.14  2007/03/23 07:31:15  goldin
 *   Fix syntax error
 *
 *   Revision 1.13  2007/02/25 10:35:06  goldin
 *   Exposed code to set shape type for Shapefiles
 *
 *   Revision 1.12  2007/02/03 11:29:57  rudahl
 *   (temp) limit on size of vector coords
 *
 *   Revision 1.11  2006/11/12 07:00:51  goldin
 *   New functions to update meta info for images and vector data sets
 *
 *   Revision 1.10  2006/11/11 08:06:55  goldin
 *   Refactoring to support igc metafile update
 *
 *   Revision 1.9  2006/09/29 11:35:38  goldin
 *   Begin implementation of meta data file classes
 *
 *   Revision 1.8  2006/09/17 13:33:35  goldin
 *   deal with special cases
 *
 *   Revision 1.7  2006/08/14 07:19:41  goldin
 *   Debugging new vector framework
 *
 *   Revision 1.6  2006/08/09 10:38:07  goldin
 *   Continued work on vector read/write/scale
 *
 *   Revision 1.5  2006/08/05 04:45:33  goldin
 *   Fix the capitalization
 *
 *   Revision 1.3  2006/08/04 11:07:19  goldin
 *   Create class hierarchy similar to that for image classes
 *
 *   Revision 1.2  2006/08/04 08:23:09  goldin
 *   Separate vector reading from base VectorData class
 *
 *   Revision 1.1  2006/08/04 04:31:40  goldin
 *   Rename VectorFile to VectorData
 *
 *   Revision 1.3  2006/07/30 07:55:20  goldin
 *   Adding functionality
 *
 *   Revision 1.2  2006/07/29 11:13:37  goldin
 *   Continue to add functionality
 *
 *   Revision 1.1  2006/07/24 13:24:34  goldin
 *   Header for new VectorFile class
 *
 *
 *******************************************************************
 *   Header file for the VectorData class, new class to handle
 *   reading, writing and transformation of OpenDragon vector
 *   data. This class is roughly analogous to the the Image class,
 *  and uses some of the same helper classes for reading and
 *  interpreting the header data.
 *
 *   Created by Sally Goldin, 24 July 2006
 *	
 ****************************************************************
 */
#ifndef VECTORDATA_H
#define VECTORDATA_H	/* signal this file has been loaded */

/* ~~~ limited size of vector coordinates at present, due to
 * algo in georast.c
 */
#define VECTOR_MAX_X 32000
#define VECTOR_MAX_Y 32000

#ifdef __cplusplus
class VectorData;
extern "C" {
#else
    typedef void * VectorData;
#endif

/* VERTEX is defined in img.h */

/* Vector data structure definition. 
 * Every VectorFile class instance will hold one of these
 * structures as data. This is needed so tht we can
 * access the information in the class from C.
 */
typedef struct 
    {
    BOOL bValid;                   /* If true, initialized, else not  */
    char filename[PATH_MAX];       /* file represented by this structure */ 
    VectorData * pVectorDataObj;   /* ptr to object which owns this struct */
    IMGTYPE_T vectorFormat;       /* what format was the original file (or output file) */ 
    int fileAccess;                /* Input? Output? or none. See below */
    VERTEX minExtent;              /* Coordinates of minimum point in file. */
    VERTEX maxExtent;              /* Coorindates of maximum point in file */
    int featureCount;              /* Number of features - may not be known */
    } VECTORDATA;

#define VEC_UNKNOWN_FEATURE 0
#define VEC_POINT_FEATURE 1
#define VEC_LINE_FEATURE 2
#define VEC_POLY_FEATURE 3

#define FILEACCESS_NONE 0
#define FILEACCESS_INPUT 1
#define FILEACCESS_OUTPUT 2

#define FEATURE_TYPE_CODES "N","M","L","P"

/* Structure used for reading vectors from 
 * vector file. Eventually may become the internal
 * vector format.
 */
typedef struct
    {
    char ID[128];          /* unique identifier; not currently used */
    int featureType;    /* one of the constants above */
    int color;            /* color number from file */
    int fillColor;        /* if >= 0, means that figure should be filled */
                          /* and indicates the color; if < 0, not filled */  
    unsigned vertexCount; /* how many vertices in the figure */
    VERTEX * points;      /* actual data for the feature */
    } VECFEATURE;

   /* Free all the memory associated with a VECFEATURE. */
    void freeVecFeature(VECFEATURE* pFeature);

   /* Allocate memory for a vector feature that will hold the
    * specified number of points. 
    * @param  vertexCount How many vertices are needed?
    * @return Pointer to newly allocated VECFEATURE or NULL if allocation error.
    */
    VECFEATURE * allocateVecFeature(int vertexCount); 
#ifdef __cplusplus
}  /* end of extern "C" */
#endif

#ifdef __cplusplus
class VectorDataReader;
class VectorDataWriter;

class VectorData : public OB
    {
    private: /* members */
        unsigned m_uState;              /* as in Image */
        int m_iStatus;                  /* as in Image */
        VECTORDATA m_VecFile;           /* structure to be used in C */
	ImageReader * m_pReader;        /* reads the header (only) */
	ImageWriter * m_pWriter;        /* writes the header (only) */
	VectorDataReader * m_pVReader;  /* reads the vector data */
	VectorDataWriter * m_pVWriter;  /* writes the vector data */
	ImageHdr * m_pHdr;              /* pointer to image header. */
	BOOL m_bHdrUpdated;		/* TRUE => need to rewrite header */
        FILE* m_Fp;                     /* If non-null, file is open */
	int m_iHasHeader;               /* -1 not yet checked, 0 no, 1 yes */
	static Class s_class_Base;
   
    public:  /* methods */
    	 VectorData(int iDebug=0,int iTrace=0);
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB

	 /* Allow other classes to set the state of the class 
          * in order to indicate an error.
	  */ 							
         void setState(unsigned uState) {m_uState = uState;}

	/* initialize all values based on header info in
	 * specified file, which must exist. 
	 * Should be preceeded by zero(). 
	 * @param pczFilename	full, long path to file
	 * @return		0 if OK else negative error #:
	 */
	int open(const char * pczFilename);

	/* set up a VectorData for output. This could be 
         * a brand new file or it could be based on an existing
         * file, depending on the value of pSrcVectors. 
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcVectors	If non-null, vector file to copy
	 * @param vectorFormat	If pSrcVectors is null and this is a valid 
         *                         IT_* vector constant, use it 
	 *			to determine what format to create.
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
	int create(const char * pczFilename, BOOL bOverwrite,
		   const VectorData * pSrcVectors, 
		   IMGTYPE_T vectorFormat=IT_DRAGON_VEC);

	/* set up a VectorData for output. This will be
         * a brand new file based on pSrcData
	 * This version of create() is for shp2drag, 
	 * and other ops which create vector file de-novo
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param pSrcData	Vector data to initialize from
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
	int create(const char * pczFilename, BOOL bOverwrite,
		   const VECTORDATA * pSrcData);

	/* change text information (except classnames, unitnames) 
	 * for an existing vector file.
	 * Only the params with non-NULL vals will be changed.
	 * This may be invoked after writing the header and the vector data
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int update_text(const char * pczTitle,
			const char * pczId,
			const char * pczComment,
			const char * pczSource,
			const char * pczScene,
			const char * pczSubscene,
			const char * pczBand,
			const char * pczColorfileName,
			const char * pczFtype);

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
	int update_georef(int img_x, int img_y, 
			  const MapCoord * ref_x, const MapCoord * ref_y,
			  double xcell_size, double ycell_size,
			  const char* pczProjection, const char* pczUnitname,
			  const char * pczDateTime,const char * pczUTMZone,
			  int iRegistered);

	/* set extent (bounding box) information for a vector file.
	 * This sets the extents in the m_VecFile.
	 * @param dMinX,dMinY  	u.l. corner of bounding box in UTM
	 * @param dMaxX,dMaxY  	l.r. corner of bounding box in UTM
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
	int set_extent(double dMinX,double dMinY,double dMaxX,double dMaxY);

	/* set (bounding box) information for a vector file.
	 *   This invokes update_geomery to
	 *   set pczUnitName (meter by default) and optionally pczProjection
	 * @param dMinX,dMinY  	u.l. corner of bounding box in UTM
	 * @param dMaxX,dMaxY  	l.r. corner of bounding box in UTM
	 * @param pczProjection NULL or code for map proj'n 
	 * @param pczUnitname	usually 'meter'
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
	int update_extent(double dMinX,double dMinY,double dMaxX,double dMaxY,
		       const char* pczProjection, const char* pczUnitname);

	/* change metafile information 
	 * for an existing image.
	 * Only the params with non-NULL vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
        int update_metainfo(const char * pczMetafile,
			    const char * pczGuid);

	/* set to valid but not meaningful values (mostly 0 or NULL)
         * In particular set georef info to identity transform.
	 * @return		0 if OK
	 *			else
	 *				-54 if file close error
	 */
	int zero();

	/* close any open files, reset to indicate that the file
         * is not currently valid.
         */
        int close();

	/*	write image header and close output file
	 *	On exit, file is closed
	 *	Return 0 if OK and set m_iErrno to 0.
	 *	Error values are:
	 *		-60 => header completely uninitialized 
	 *		-64 => there's alread an open file in pFp,
	 *			so just leave values alone
	 *		-65 => no name supplied
	 *		-69 => no header writer found
	 */
	int writeHeader();

	/*	rewrite image header in place.
	 *	On exit, file is closed
	 *	Return 0 if OK
	 *	Error values are:
	 *		-16 => op not needed (not an error)
	 *		-50 - -55 file IO errors
	 *		-65 => no name supplied
	 *		-69 => no header writer found
	 */
	int rewriteHeader();

        /* getter function for filename */
	const char* getFilename() {return m_VecFile.filename;}
        /* getters and setters for feature count */
	void setFeatureCount(int count);
        int getFeatureCount();
	void incrementFeatureCount();

	/* Set the data type for this file.
	 * Currently only relevant for Shapefiles, which
	 * can hold only one type of feature.
	 * Returns TRUE unless invalid type is passed 
	 */
	BOOL setShapeType(char type);

        /* Get the header fields as a struct for use in C */
	const IMAGEHDR * getIMAGEHDR() const 
	    { return (m_pHdr != NULL) ? m_pHdr->getImageHdr() : NULL; };
	const VECTORDATA * getVecData() { return &m_VecFile; } ;
	const ImageHdr * getImageHeader() const { return m_pHdr; } ;

        /* Get a vector feature from the file. This is
         * a wrapper for a call to the VectorDataReader.
         * This function allocates the structure
         * that is returned. The caller must free the structure by
         * calling freeVecFeature()
         *
         * @param  pStatus  0 is returned in this variable for success,
         *                  otherwise an error number
         * @param  bTransformOnRead  If true, transform from geographic
         *                  		to screen coordinates before returning
         * @return pointer to new VECFEATURE structure or null if error.
         */
	VECFEATURE * getNextFeature(int* pStatus, BOOL bTransformOnRead=FALSE);

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
	int putNextFeature(VECFEATURE* pFeature,BOOL bTransformOnWrite=FALSE);

        /* Copy all the features from the current vector file
         * to the destination file, reapplying the coordinate
         * transformation if necessary. Leaves the destination file
         * open when finished.
         * @param pDestVectorData  Pointer to destination (output) instance
         * @return 0 for success else negative for error.
         */
        int transformCopy(VectorData* pDestVectorData);

        /* Test whether this vector file has 
         * any header information.
         * @param  pczFilename  Name of file to test.
         * @return TRUE if it has a header, else
         *         FALSE. If it has a header it
         *         will always be 5.8 style.
         */
        BOOL headerExists(const char * pczFilename);

        /* Adjust the extent based on the passed x and y coordinates
         * @param pFeature  Vector feature to consider
         */
        void adjustExtent(VECFEATURE* pFeature);

    /* Debugging functions */

	void dumpVECFEATURE(VECFEATURE * pFeature); // dump a feature
 
	void dumpVECTORDATA();  // dump contents of m_VecFile

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
	const char * dump(int detail=1, const char * pczTitle=NULL) const;

    protected:
		/*	read image header and set 'm_VecFile' accordingly.
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
	BOOL readImageHeader(const char * pczFileName);

                /* Return a VectorDataReader which can read the specified file
		 * or NULL if unknown type.
		 */
       VectorDataReader * vectorDataReaderFactory(const char * pczName);

                /* Return a VectorDataWriter which can write the specified file type
		 * or NULL if unknown type.
		 */
       VectorDataWriter * vectorDataWriterFactory(IMGTYPE_T type);

       /* make file header agree with passed header
	* @param pDestHdr 	DHEAD-sized buffer
	*                  	which should be filled from pSrcHdr info 
	* @param pSrcHdr       Pointer to IMAGEHDR to use as the source for 
	*                      header values   
	* @return        <0 if err (missing argument)
	*/
       int copyFields(DRAGON_HEAD * pDestHdr,
				  const IMAGEHDR * pSrcHdr);

       void mapCoord_copy(const MapCoord * src,
				      HDR_MapCoord * dest);

    };

#endif /* c plus plus */
#endif
