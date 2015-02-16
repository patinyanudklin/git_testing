/*
 *	filename imageHdr.h
 *		$Revision: 1.18 $ $Date: 2015/01/21 10:39:37 $	
 *
 *      ~~ Copyright 1985-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: imageHdr.h,v 1.18 2015/01/21 10:39:37 rudahl Exp $
 *   $Log: imageHdr.h,v $
 *   Revision 1.18  2015/01/21 10:39:37  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.17  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.16  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.15  2008/06/14 10:15:55  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.14  2007/01/26 06:38:15  goldin
 *   Change doc to deprecate passing zeros to create functions
 *
 *   Revision 1.13  2007/01/01 09:43:22  rudahl
 *   improved tracing, dumps; originalfileinfo
 *
 *   Revision 1.12  2006/12/31 12:15:22  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.11  2006/08/20 11:05:07  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.10  2005/12/30 10:36:58  rudahl
 *   added support for dump(detail
 *
 *   Revision 1.9  2005/09/17 10:57:57  rudahl
 *   added bulletproofing
 *
 *   Revision 1.8  2005/09/17 05:40:16  rudahl
 *   improved dump, trace, docs; ProcessRect
 *
 *   Revision 1.7  2005/09/12 07:30:41  rudahl
 *   fixes re dp.h
 *
 *   Revision 1.6  2005/09/07 05:03:53  rudahl
 *   added getLabel
 *
 *   Revision 1.5  2005/07/22 15:19:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.4  2005/07/03 13:28:56  rudahl
 *   improving createImage
 *
 *   Revision 1.3  2005/04/07 10:23:21  rudahl
 *   cleaned up some arg lists
 *
 *   Revision 1.2  2005/04/06 09:26:45  rudahl
 *   expanded revise_geometry
 *
 *   Revision 1.1  2005/03/19 06:25:44  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.2  2005/03/10 22:41:56  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.1  2005/03/09 23:14:12  rudahl
 *   moved class ImageHdr from dhead to imageHdr.h
 *
 *
 *   Revision 1.1  2005/01/04 15:48:59  rudahl
 *   initial from moochie
 *
 ****************************************************************
 * 
 *      This file defines the ImageHdr class which
 *	encapsulates a file-independent set of header info.
 *
 *	The content of this and dhead.cpp are derived from parts
 *	of img_hdr.c, img_acc.c, img.cpp, and ob.cpp in Dragon 5.4.
 *	by way of dhead.h
 *	The structs defined herein are similar to the Dragon header
 *	structure in v 5.4 and earlier. 
 *
 *	This file requires dtypes.h, dhead.h, and ob.h
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-03-09 ktr	created by extraction from dhead.h
 * 5.7 	2005-7-20 ktr	added h_OriginalFileName
 *	2005-9-7 ktr	added getLabel
 * 5.9	2006-12-31 ktr	moved IMAGEDATA_SELECTOR here from img.h
 *			and added it as arg to several fns
 * 5.11	2008-06-14 ktr	added LinesBlob to trailer
*/

#if ! defined IMGEHDR_H
#define IMAGEHDR_H	/* signal this file has been loaded */

typedef enum
    { 
    IMG_UPDATE_NONE=0,
    IMG_REVISE_GEOM=1,
    IMG_UPDATE_TEXT=2,
    IMG_UPDATE_SCALING=4,
    IMG_UPDATE_LABELS=8,
    IMG_UPDATE_STATS=16,
    IMG_UPDATE_GEOREF=32,
    IMG_UPDATE_CLASSTABLE=64,
    IMG_UPDATE_META=128,
    IMG_UPDATE_EXTENT=256,
    IMG_UPDATE_ORIGINAL=512,
    IMG_UPDATE_ALL=0xFFFF
    } HDR_UPDATES_t;

/* Define a base class for reading and writing to real image files.
 * For each type of image file (defined by a different derived class),
 * this class will support reading and optionally writing the header.
 * 
 * Various query functions are also provided.
 */

    /* structure which contains non-default values used during 
     * image data file I/O. When this is supplied as an argument
     * to some function (such as getImageLine), 
     * supplying NULL implies that the default values will be used.
     * This is properly part of imageReader.h, but needs to be
     * known to lots of .c modules which do not include imageReader.h
     */
typedef struct
    {
    ushort uBandNo;	/* default: 0; only applies to multiband images */
    ushort uResNo;	/* default: 0; only applies to multiresolution images*/
//    BOOL bScale;	/* default: FALSE */
    } IMAGEDATA_SELECTOR;

#if defined __cplusplus // everything in the file is only for C++

class ImageReader;
class ImageWriter;
class Image;

class ImageHdr : public OB
    {
    public:
		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
	ImageHdr(int iDebug=0,int iTrace=0);

		// this is basically a copy constructor,
		// although the default constructor must be called first.
		// @param pSrc		header to copy
		// @param uImgType	File format of new image file
		// @param pczFtype      Dragon file type - "I", "C" or "L",
		//			or NULL to keep type from copy
		// @return 		0 if OK
		//			<0 if error:
		//		  	-48 strdup failure, 
		//		  	-72 pSrc not init
		//		  	-76 using an unused field
	int copy(const ImageHdr * pSrc, IMGTYPE_T uImgType,
		 const char* pczFtype);

		// Get a pointer to a label
		// @param uLabelNo	index of label
		// @return 		pointer 
		// 			or NULL if uLabelNo out of range
	const LABEL_INFO * getLabel(size_t uLabelNo) const;

		// Get label text
		// @param uLabelNo	index of label
		// @param pczUTF8Buffer	buffer to place text
		// @param uBufLen	size of buffer
		// @return 		-90 (DERR_FN_ARG0) 
		//				if uLabelNo out of range
		//			else label color index >= 0
	int getLabel(size_t uLabelNo, char * pczUTF8Buffer, 
		     size_t uBufLen) const;

		// read specified file and initialize IMAGEHDR
		// Assumes caller has already verified that
		// file exists and has read permissions
		// @param pczName	name of file to read
		// @param pSel		specify band of multimand file
		// @param pImg		some readers may need this
		// @return		reader if OK 
		// 			else NULL
	ImageReader * read(const char * pczName, 
			   const IMAGEDATA_SELECTOR * pSel, 
			   Image * pImg = NULL);
 
		// read specified file and initialize IMAGEHDR
		// @return	0 if OK else  ...
	int write(const char * pczName);

		// return a reader which can read the specified file
		// or NULL
	ImageReader * imageReaderFactory(const char * pczName);
 		
		// return a writer which can write the specified file
		// or NULL
	ImageWriter * imageWriterFactory(IMGTYPE_T uFormat) const;
 		
	/* revise critical values for an existing writable image.
	 * Only the params with non-default vals will be changed.
	 * This must be invoked BEFORE writing the header
	 * @param pczFilename	NULL => do not change
	 * @param bOverwrite	FALSE => do not change
	 * @param bReReadable	FALSE => do not change
	 * @param uImgType	IT_INVALID => do not change
	 * @param uNumLines	0 => do not change
	 * @param uNumPixels	0 => do not change
	 * @param uBitsPerPix	0 => do not change
	 * @param uNumBands	0 => do not change
	 * @param uNumResolutions 
	 * @param ulPixPitch	0 => accept default calculations
	 * @param ulLinePitch	0 => accept default calculations
	 * @param ulBandPitch	0 => accept default calculations
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int revise_geom(const char * pczFilename=NULL, BOOL bOverwrite=FALSE,
			BOOL bReReadable=FALSE, IMGTYPE_T uImgType=IT_INVALID,
			ushort uNumLines=0, ushort uNumPixels=0,
			ushort uBitsPerPix=0, ushort uNumBands=0,
			ushort uNumResolutions=0,
			ulong ulPixPitch=0,
			ulong ulLinePitch=0,
			ulong ulBandPitch=0);

	/* change scaling information for an existing image.
	 * Only the params with non-default vals will be changed.
	 * This may be invoked after writing the header and the image data
	 * @param dScaleFactor	factor, value for BINARY or OPTIMAL scaling
	 * @param ScaleOffset	offset, value only if OPTIMAL scaling
	 * @param pczScalingType 'B', 'O', 'N'o change, or \0 for none
	 *   ( the following give calibration meaning to pixel values )
	 *   ( if dZ_scale == 0, none of these are set by this fn)
	 *   ( calibrated value = (pixel value * dz_Scale) + dZ_offset)
	 * @param dZ_scale	multiplicative factor
	 * @param dZ_offset	additive factor 
	 * @param pcZ_unit 	name of pixel calibration units
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int update_scaling(double dScaleFactor,
			   double dScaleOffset,
			   const char * pczScalingType,
			   double dZ_scale=0.0,
			   double dZ_offset=0.0,
			   const char * pcZ_unit=NULL);

	/* change text information (except classnames, unitnames) 
	 * for an existing image.
	 * Only the params with non-NULL vals will be changed.
	 * This may be invoked after writing the header and the image data
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

	/* change stats and histogram information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * @param pImgStats	stats for image
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
	int update_stats(const IMGSTATS * pImgStats);


	/* change georeferencing information information for an existing image.
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

	/* change labels information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * @param iNumLabels	-1 for don't change the number of
         *                      labels, or number of labels in img
	 *                      If different from than the current 
	 *                      number of labels, we will discard 
	 *                      all the old labels and replace with the
	 *                      ones passed in. If -1, or the same
	 *                      as the current number, we only replace
	 *                      the first "uArrayCount" labels.
	 * @param uArrayCount	number of items in pLabels
	 * @param pLabels	label info
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
	int update_labels(int iNumLabels,
			  size_t uArrayCount,
			  const LABEL_INFO * pLabels);

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

	/* change originalfile information 
	 * for an existing image.
	 * Only the params with non-NULL or >= 0 vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int update_original(uint uOriginalBandCount,
			    uint uOriginalBandNumber,
			    const char * pczOriginalFileName);

	/* change extent information for an existing image.
	 * This may be invoked after writing the header and the image data
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

		// return a description of the class member
	const char * about(const char * arg = NULL);

		// return a formatted dump of the class member
		// @param detail	specify amount of detail
		//			0 => uninit, dragon-specific fields not reported
		//			1 => full info
	const char * dump(int detail=6, const char * czTitle=NULL) const;

		// return a formatted dump of the IMAGEHDR structure
		// The calling program must supply a title
		// static function
		// @param detail	specify amount of detail
		//			0 => uninit, dragon-specific fields not reported
		//			1 => full info
	static const char * dump(int detail, const IMAGEHDR * pHdr);

		// return 0 if operation (read or write was OK
		// else the error value most recently returned
//	int getErrorNum() { return m_iErrnum; } ;

		// return NULL if no error,
		// else a description in english of the most recent error
//	const char * getErrorStr();

		// return NULL if no error,
		// else a tag for an internationalized message 
		// for the most recent error. 
		// Return '' if there is no appropriate tag
	//const char * errorTag();

	~ImageHdr();

		// set to valid but not meaningful values (mostly 0 or NULL)
		// @param bFirstTime	if TRUE, assume ptrs are junk
	void zero(BOOL bFirstTime);

		/* Set to a minimum set of values needed to be meaningful.
		 * This sets values specified by calling args.
		 * @param pczFtype	type char for Dragon image file:
		 *			"I", "C", "L", or NULL=> "I"
		 * @param uNumLines	number of lines in target image
		 * @param uNumPixels	number of pixels/line in target image
		 * @param uBitsPerPix	if 0, is determined by uImgType
		 *                      DEPRECATED - should pass correct value
		 * @param uNumBands	if 0, is determined by uImgType
		 *                      DEPRECATED - should pass correct value
		 * @param uNumResolutions if 0, is determined by uImgType
		 *                      DEPRECATED - should pass correct value
		 * @param pczOriginalName NULL or name of source file
		 * @return		0 if OK else:
		 *			-48 memory errir
		 */
	int init(IMGTYPE_T uImgType,const char * pczFtype,
		 ushort uNumLines, ushort uNumPixels,
		 ushort uBitsPerPix, ushort uNumBands,
		 ushort uNumResolutions,
		 const char * pczOriginalName);

	const char * ImageTypeName() const;
//	    { return (m_uImageType < AY_COUNT(s_czImgTypeNames))
//		  ? s_czImgTypeNames[m_uImageType] : "Unknown" ; } ;
	static const char * ImageTypeName(IMGTYPE_T uType);
//	    { return (uType < AY_COUNT(s_czImgTypeNames))
//		  ? s_czImgTypeNames[uType] : "Unknown"; } ;
	    const char * LayoutName() const;
//	    { return (m_hi.uBandLayout < AY_COUNT(s_czLayoutNames))
//		  ? s_czLayoutNames[m_hi.uBandLayout] : "Unknown"; } ;
	IMGTYPE_T getImageType() const { return m_uImageType; } ;

	const IMAGEHDR * getImageHdr() const { return &m_hi; } ;

	void setDataOffset(long lOffset)
	    {if (lOffset >= 0) m_hi.ulDataOffset = lOffset;};
	void setTrailerOffset(ulong ulOffset)
	    {if (ulOffset > 0) m_hi.iff_offset = ulOffset;};
        HDR_UPDATES_t getUpdatesNeeded() { return m_uUpdates; } ;
	void clearUpdatesNeeded() { m_uUpdates = IMG_UPDATE_NONE; } ;
	void setKey(ushort uKey) { m_hi.uKey = uKey; } ;

    protected:
	IMAGEHDR m_hi;
	IMGTYPE_T m_uImageType;
        HDR_UPDATES_t m_uUpdates; /* bitmap of changes since latest write */
    private:
	/* Helper function. Checks to see if pointer pointed to
	 * by destination pointer is not null. If it is not, frees it, 
	 * and sets it to null. Then tries to strdup the source pointer
	 * and assign it to the destination.
	 * @param pczDestStringPointer - pointer to be freed & initialized
	 * @param pczSourceString      - string to be assigned 
	 * @return   0 or error from memory allocation failure.
	 */
	int freeAndCopy(char ** pczDestStringPointer, const char * pczSourceString);
	static Class s_class_Base;
	static const char * s_czImgTypeNames[];
	static const char * s_czLayoutNames[];
    } ;

#endif // if defined __cplusplus
#endif // IMAGEHDR_H	/* signal this file has been loaded */

