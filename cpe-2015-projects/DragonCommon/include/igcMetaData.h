/*
 *	filename igcMetaData.h		- 
 *		$Revision: 1.11 $ $Date: 2014/12/05 10:38:00 $	
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
 *   $Id: igcMetaData.h,v 1.11 2014/12/05 10:38:00 rudahl Exp $
 *   $Log: igcMetaData.h,v $
 *   Revision 1.11  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.10  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.9  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.8  2006/12/17 11:38:57  goldin
 *   Bug fixes
 *
 *   Revision 1.7  2006/11/24 11:59:23  goldin
 *   Make parameter a const
 *
 *   Revision 1.6  2006/11/17 10:44:24  goldin
 *   debug facade functions to create new meta info
 *
 *   Revision 1.5  2006/11/16 10:04:57  goldin
 *   Add new functions to update meta data from appl. programs
 *
 *   Revision 1.4  2006/11/13 14:11:10  goldin
 *   integrating PCA into Dragon
 *
 *   Revision 1.3  2006/11/12 07:00:51  goldin
 *   New functions to update meta info for images and vector data sets
 *
 *   Revision 1.2  2006/11/11 08:06:55  goldin
 *   Refactoring to support igc metafile update
 *
 *   Revision 1.1  2006/09/29 11:35:38  goldin
 *   Begin implementation of meta data file classes
 *
 *
 *
 *******************************************************************
 *   Header file for the IgcMetaData class, new class to handle
 *   reading, writing and modification of OpenDragon IGC MetaData files.
 *   IGC MetaData files are a new mechanism to group files that have
 *   congruent geographical extents. An IGC MetData file is just like
 *   a Dragon header; it has some additional fields added (for
 *   all headers) in Dragon 5.10.
 *   This class is roughly analogous to the the Image class,
 *   and uses some of the same helper classes for reading and
 *   interpreting the header data.
 *
 *   Created by Sally Goldin, 29 September 2006
 *	
 ****************************************************************
 */
#ifndef IGCMETADATA_H
#define IGCMETADATA_H	/* signal this file has been loaded */

#ifdef __cplusplus
    class IgcMetaData;
extern "C" {
#else
    typedef void * IgcMetaData;
#endif

/* Vector data structure definition. 
 * Every VectorFile class instance will hold one of these
 * structures as data. This is needed so tht we can
 * access the information in the class from C.
 */
typedef struct 
    {
    BOOL bValid;                     /* If true, initialized, else not  */
    char czFullFilename[PATH_MAX];  /* filename with path */
    IgcMetaData * pMetaDataObj;     /* ptr to object which owns this struct */
    } METAHANDLE;

#ifdef __cplusplus
} /* end of extern C */
#endif

#ifdef __cplusplus

class IgcMetaData : public OB
    {
    private: /* members */
        unsigned m_uState;              /* as in Image */
        int m_iStatus;                  /* as in Image */
	ImageReader * m_pReader;        /* reads the header (only) */
	ImageWriter * m_pWriter;        /* writes the header (only) */
	ImageHdr * m_pHdr;              /* pointer to image header. */
	BOOL m_bHdrUpdated;		/* TRUE => need to rewrite header */
        char m_Filename[PATH_MAX];      /* filename including path */
        METAHANDLE m_Handle;            /* Handle used in C functions */ 
	static Class s_class_Base;
   
    public:  /* methods */
    	 IgcMetaData(int iDebug=0,int iTrace=0);
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
         int create(const char * pczFilename, BOOL bOverwrite, 
	       const IgcMetaData * pSrcMetaData, const Image* pSrcImage);

	/* change text information (except classnames, unitnames) 
	 * for an existing vector file.
	 * Only the params with non-NULL vals will be changed.
         * NOTE that color file, filetype cannot be changed, unlike
         * the corresponding function in the Image class.
	 * This may be invoked after writing the header
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
			const char * pczBand);

	/* change georeferencing information information for a metadata.
	 * This may be invoked after writing the header and the image data
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
	int update_metainfo(const char * pczMetafile,
			  const char * pczGuid);

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
	int update_extent(double minX, double minY,
			  double maxX, double maxY);

	/* set to valid but not meaningful values (mostly 0 or NULL)
         * In particular set georef info to identity transform.
	 * @return		0 if OK
	 *			else
	 *				-54 if file close error
	 */
	int zero();


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
	const char* getFilename() {return m_Filename;}

        /* Get the header fields as a struct for use in C */
	const IMAGEHDR * getIMAGEHDR() const 
	  {return (m_pHdr != NULL) ? m_pHdr->getImageHdr() : NULL; };
	const ImageHdr * getImageHeader() const { return m_pHdr; } ;

        /* Get the metadata handle struct for use in C */
        const METAHANDLE * getMETAHANDLE() const
	    { return &m_Handle; } 

        /* Debugging functions */

	const char * dump(int detail=1, const char * pczTitle=NULL) const;

    protected:
		/*	read image header.
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

	/* private function to generate and set the identifying info 
	 * for a metafile, i.e. its filename and GUID.
	 * @return 0 if okay, -1 for error.
	 */
	int generateIdentifyingInfo();

    };  /* end of class */
#endif /* c plus plus */


#ifdef __cplusplus
extern "C" {
#endif
 /* Facade function to create a new metafile based
  * on an initialized image.
  * @param metaFileName  Name of metafile to create including path
  * @param pSrcImage  pointer to IMAGE to use for source data
  * @return 0 if successful, else negative for error.
  */
int createMetaInfo(const char* pczMetaFileName, const IMAGE* pSrcImage);

/* Facade function - update the header information for an image based on
 * the identifying information in the meta file. DOES NOT REWRITE IMAGE HEADER 
 * @param pImage  Pointer to image to update
 * @param pczMetaFileName   Name of metafile including path
 * @return 0 if success, negative for error. 
 */
int updateImageFromMetaFile(const IMAGE* pImage, const char* pczMetaFileName);  
#ifdef __cplusplus
}
#endif

#endif
