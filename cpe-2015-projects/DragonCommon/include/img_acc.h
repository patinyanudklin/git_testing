/*
 *	definitions necessary for using functions in  
 *      IMG_ACC.C.
 *
 *	~~ Copyright 1992-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: img_acc.h,v 1.85 2015/01/02 03:16:27 rudahl Exp $
 *   $Log: img_acc.h,v $
 *   Revision 1.85  2015/01/02 03:16:27  rudahl
 *   fix Dragon/OpenDragon conditional
 *
 *   Revision 1.84  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.83  2014/12/06 11:33:25  rudahl
 *   added getWorkingImageFile() for OpenDragon
 *
 *   Revision 1.82  2014/12/05 12:32:30  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.81  2014/02/09 04:27:08  rudahl
 *   lint
 *
 *   Revision 1.80  2012/02/06 01:53:45  rudahl
 *   clean up and document calcImageScale
 *
 *   Revision 1.79  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.78  2010/12/05 03:54:56  rudahl
 *   changed some param datatypes
 *
 *   Revision 1.77  2008/09/12 03:40:22  rudahl
 *   enhanced dump
 *
 *   Revision 1.76  2008/08/12 06:11:19  goldin
 *   Clarify function doc for GetImageLine
 *
 *   Revision 1.75  2008/06/19 12:51:54  goldin
 *   Working on vector blob handling
 *
 *   Revision 1.74  2008/06/19 08:24:32  rudahl
 *   testing blob access
 *
 *   Revision 1.73  2008/06/14 15:56:18  goldin
 *   Implement code to save and
 *
 *   Revision 1.72  2008/06/14 10:15:55  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.71  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.70  2007/10/03 11:36:19  goldin
 *   Move getMostRecentWorkingImage and related fns to separate source
 *
 *   Revision 1.69  2007/09/09 11:45:25  goldin
 *   Move getWorkingImagePath to the server
 *
 *   Revision 1.68  2007/02/11 02:45:04  rudahl
 *   removed prototype for LineOp
 *
 *   Revision 1.67  2007/01/26 06:38:15  goldin
 *   Change doc to deprecate passing zeros to create functions
 *
 *   Revision 1.66  2006/12/31 12:15:22  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.65  2006/11/16 10:04:57  goldin
 *   Add new functions to update meta data from appl. programs
 *
 *   Revision 1.64  2006/11/12 07:00:51  goldin
 *   New functions to update meta info for images and vector data sets
 *
 *   Revision 1.63  2006/11/11 10:07:10  goldin
 *   add clearImageMetaInfo
 *
 *   Revision 1.62  2006/11/11 08:06:55  goldin
 *   Refactoring to support igc metafile update
 *
 *   Revision 1.61  2006/02/12 10:44:53  goldin
 *   Update documentation on CalcAndSetImageStats
 *
 *   Revision 1.60  2006/02/12 08:13:50  rudahl
 *   fixed fns which should have required a const IMAGE
 *
 *   Revision 1.59  2006/02/07 08:36:23  goldin
 *   add new fn to explicitly set processRect values
 *
 *   Revision 1.58  2005/12/30 10:35:04  rudahl
 *   added arg to dumpImageHeader
 *
 *   Revision 1.57  2005/12/30 09:26:50  goldin
 *   Change documentation for SetupImage
 *
 *   Revision 1.56  2005/09/25 12:07:49  rudahl
 *   re-enabled LineOp for geovec
 *
 *   Revision 1.55  2005/09/17 05:40:16  rudahl
 *   improved dump, trace, docs; ProcessRect
 *
 *   Revision 1.54  2005/09/07 05:03:53  rudahl
 *   added getLabel
 *
 *   Revision 1.53  2005/08/02 02:14:17  rudahl
 *   fine-tuning separation into product,common
 *
 *   Revision 1.52  2005/08/01 02:51:54  rudahl
 *   re-enabled GetImageLine temporarily
 *
 *   Revision 1.51  2005/07/29 04:03:57  rudahl
 *   improved docs
 *
 *   Revision 1.50  2005/07/22 15:19:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.49  2005/07/03 13:28:56  rudahl
 *   improving createImage
 *
 *   Revision 1.48  2005/06/27 11:46:11  rudahl
 *   added some access fns
 *
 *   Revision 1.47  2005/04/25 13:54:17  goldin
 *   Make IMAGE* args const
 *
 *   Revision 1.46  2005/04/08 07:20:38  goldin
 *   Re-implement fillImage (was fill_image)
 *
 *   Revision 1.45  2005/03/31 06:47:08  goldin
 *   Add convenience method CalcAndSetStats
 *
 *   Revision 1.44  2005/03/19 06:25:44  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.52  2005/03/16 04:07:34  rudahl
 *   fixing writeTrailer tests
 *
 *   Revision 1.51  2005/03/13 17:03:13  rudahl
 *   adapting to new header format
 *
 *   Revision 1.50  2005/03/13 02:42:58  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.49  2005/03/11 21:37:28  rudahl
 *   added getWorkingImage stuff
 *
 *   Revision 1.48  2005/03/11 20:28:20  goldin
 *   debugging rewriteImageHeader
 *
 *   Revision 1.47  2005/03/11 18:00:26  rudahl
 *   added getWorkingbits
 *
 *   Revision 1.46  2005/03/11 17:11:32  rudahl
 *   revised zero, CloseImage, rewriteHeader
 *
 *   Revision 1.45  2005/03/10 21:33:51  goldin
 *   Added new fn openImage
 *
 *   Revision 1.44  2005/03/09 01:34:50  rudahl
 *   fix missing args in update_text(), add CloseImage
 *
 *   Revision 1.43  2005/03/07 23:39:59  goldin
 *   Moved functions that take img index to img.c in Server
 *
 *   Revision 1.42  2005/03/06 17:32:09  rudahl
 *   revising create() and update_text() args
 *
 *   Revision 1.41  2005/03/06 00:14:43  rudahl
 *   Moved creation of writer until writeTrailer
 *
 *   Revision 1.40  2005/03/03 23:26:14  goldin
 *   Added CalcImageStats and PutImageLineByImage
 *
 *   Revision 1.39  2005/03/03 21:50:01  goldin
 *   Implement remaining revise_ & update_ methods
 *
 *   Revision 1.38  2005/03/03 16:15:43  rudahl
 *   refinements while converting grstop
 *
 *   Revision 1.37  2005/03/01 23:04:43  goldin
 *   Implement new create function for new output images; fix update functions
 *
 *   Revision 1.36  2005/03/01 16:05:00  rudahl
 *   fixed docs
 *
 *   Revision 1.35  2005/02/23 17:46:44  rudahl
 *   new update, wrapper fns; moved from hdrstats to dhead
 *
 *   Revision 1.34  2005/02/22 19:58:04  rudahl
 *   new update, wrapper fns
 *
 *   Revision 1.33  2005/02/20 17:06:00  rudahl
 *   prelim create IMAGEHDR accessor fns
 *
 *   Revision 1.32  2005/02/17 02:50:47  rudahl
 *   adapting server for dragon 5.5
 *
 *   Revision 1.31  2005/02/15 21:36:56  rudahl
 *   cleanup
 *
 *
 ***************************************************
 *
 ***************************************************
 *	Sally E. Goldin  -- August 20, 1989
 *
 *	This file must be AFTER IMG.H, which defines 'image'
 *
 * 12/22/93 ktr	minor error in ImageOp() prototype
 * 8/25/94 ktr	added arg to InitImageAccess()
 * 1/8/95 ktr	added error msgs for STATS.C;
 *			rationalized some error numbers
 * 2/8/98 ktr	added new fns GetImageLine(), PutImageLine(),
 *			 ImageLineSeek() which work with far memory and
 *			 therefore need no local buffers.
 * 3/29/99 ktr	rev'd GetImageLine(), PutImageLine() docs to support
 *		multibyte access. No behavior changes.
 *		Added CalcImageFileOffset() and fns in IMG_HDR.C:
 *		(which is a separate file to form a CGATE overlay)
 *		   GetImageHeader(), 
 *      4/14/99 ktr	moved ReadHdrIfNecessary here, and to img_hdr.c
 *		        rev'd GetImageLine, PutImageLine to not use vfseek.
 *      4/21/99 seg     added new macros MAIN_HDR_PTR and TMP_HDR_PTR
 *      4/27/99 seg     changed my_work_lines and my_work_pixels to be macros
 *      6/25/00 ktr     merged functionality of CloseImage and ImageFileClose
 * 5.4	1/15/2002 ktr	made this module the home of work_lines, work_pix
 *			(basemem version now obsolete & unused)
 * 5.5	2005-2-15 ktr	import from Dragon 5.4.4
 * 	2005-02-15 ktr	Many fns moved to img.cpp or elsewhere, sometimes
 *			with changes in names and functionality.
 *			The old prototypes are kept here for the moment 
 *			in case we need to refer to them.
 * 5.7 	2005-7-20 ktr	added h_OriginalFileName and IMAGEDATA_SELECTOR
 *	2005-8-1 ktr	removed CreateWriteTrailer: using short filenames
 *	2005-9-7 ktr	added getLabel and getLabelText
 *	2006-2-12 ktr	extensive changing of IMAGE * to const IMAGE *,
 *			with a few code revisions to make this work
 * 5.9	2007-2-7 ktr	moved LineOp to geom.h; only used in server
 * 5.11	2008-06-14 ktr	added LinesBlob to trailer
 * 6.1	2010-12-04 ktr	changed data types of args to ScaleImageLine
 * 6.4	2014-01-31 ktr	purged a lot of deadwood
 */

#ifndef IMG_ACC_H							   
#define IMG_ACC_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
/* prototypes */
int InitImageAccess(const int from_dragon); 
    /* call this as part of the initialization if you plan to use
     * DRAGON images
     */
int ImgMemFlag(const int imgidx);
    /* returns 0 or 1 depending on current value of DRAGON's &IMGMEM variable*/

void SetImgMemFlag(const int imgidx, const int value);
    /* sets data-in-memory flag to TRUE or FALSE based on 'value' */  

IMAGE  * GetImagePtr(const int imgidx);
    /* return ptr to image structure */

	/**
	 *      setup the working dimensions and ProcessRect
	 *	for any image. Previously this returned an error
	 *      if it was called with any image index other than
	 *      main image. However, this is no longer true
	 *      as of 12/30/05.
	 *	Returns 0 
	 */
int SetupImage(const IMAGE  * imag);

    /* init img for holding data - open img virtual file */

	/*	Close an image, releasing its file and buffer resources. 
	 *	Set its file pointer field to NULL.
	 *	@param pImage	pointer to image structure 
	 *		        (not index, in case we later 
	 *			want to not use the array).
	 *	@return		0 if OK 
	 *			-54 if error
	 */
int CloseImage(const IMAGE * pImage);

	/*	retrieve a line of pixels from the appropriate
	 *	location into buffer.
	 *	The IMAGE structure must be initialized.
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf (see getLineBufferSize())
         *                      This MUST be big enough to hold an entire line
	 *                      of data from this image or an error will result
	 *	@param pImg	pointer to IMAGE struct
	 *	@param bScale   Scale to 8 bits (GetImageLineP only)
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			    0 => line is outside ProcessRect
	 *			  -60 => image not yet initialized
	 *			  -66 => image state conflict
	 *			  -68 => image not readable
	 *			  -51 => file open error
	 *			  -56 => past EOF
	 *			  -91 => element too big for buffer)
	 */
int GetImageLineP(byte * pBuf, const ushort uLineNo,
		  const size_t uBufSize, const IMAGE  * pImg,
		  const BOOL bScale,
		  IMAGEDATA_SELECTOR * pDataSel);

	/*	How big a buffer do we need for GetI(mageLineP?
	 *	(This actually returns size for a full line of read data,
	 *	regardless of multiband and scaling considerations.)
	 */
size_t getLineBufferSize(const IMAGE  * pImg);

// implementation moved to img.c 
int GetImageLine(byte * lpBuf, const ushort uLineNo,
		 const size_t uNPixBytes, const size_t uImgNdx);

/* copy an image line, scaling as we go.
 * Source and destination may be the same 
 *    (but dest. must be big enough)
 * @param lpDest	buffer where data gets moved to
 * @param lpSrc		buffer containing data
 * @param uPix		number of pixels to move
 * @param uBytesPP	size of pixel
 * @param uBase		0, or offset to subtract from raw data value
 * @param uFactor	1, or divisor of (raw data - uBase)
 */
#if DRAGON_VER >= 6
void ScaleImageLine(byte  * lpDest, const void  * lpSrc,
		    const uint uPix, const uint uBytesPP,
		    const ushort uBase, const uint uFactor);
#else
void ScaleImageLine(byte  * lpDest, const void  * lpSrc,
		    const ushort uPix, const ushort uBytesPP,
		    const ushort uBase, const ushort uFactor);
#endif
	/* create an English text string listing the values in the
	 * the <b>IMAGE</b> structure. (see <b>img.h</b>)
	 * @param pImg		pointer to an IMAGE
	 * @param pczTitle	title to be prefixed to the dump
	 * @return		static string
	 */
void dumpImage(const IMAGE * pImg,const char * pczTitle);

	/* create an English text string listing the values in the
	 * the <b>IMAGEHDR</b> structure. (see <b>dhead.h</b>)
	 * dump the image header at detail level 0
	 * @param pImg		pointer to an IMAGE
	 * @param pczTitle	title to be prefixed to the dump
	 * @param bPrint	TRUE => print output else send to logtrace
	 * @param uDetailLevel	how much detail to include
	 * @return		static string
	 */
void dumpImageHeader(const IMAGE * pImage,const char * czTitle, 
		     BOOL bPrint,uint uDetailLevel);

/*	stores line of pixels in the appropriate
 *	location in image memory, based on a line number and
 *	source location to copy from.
 *
 *	'lpBufptr' is a pointer to the source data buffer
 *	'uLineNo' indicates which image memory line to store data into
 *	'uImgNdx' indicates which image buffer to use.
 *
 *	probably always 8-bit data
 *
 *	Return number of bytes if successful, < 0 if error
 */
int PutImageLine(const byte * lpBuf, const ushort uLineNo,
		 const size_t uImgNdx);

	/*	Write line of pixel data 
	 *
	 *	@param lpBuf 	pointer to the source data buffer
	 *	@param uLineNo	which image memory line to write
	 *	@param pImg	img to use.
	 *	@return 	number of pixels if successful, < 0 if error
	 *			   0 => line is outside ProcessRect;
	 *			   -51 => file open error
	 *			   -60 => image not yet initialized
	 *			   -68 => image not writable
	 */
int PutImageLineP(const byte * lpBuf, const ushort uLineNo,
		  const IMAGE * pImg);

/*	calc byte offset into file of specified image line,
 *	return TRUE if OK and set *piStatus to 0
 *		and *pulImageLine to the offset.
 *	This fn maintains state: if the filename is non-NULL,
 *	  the state is initialized from the supplied info
 *	  and from analyzing the file header (GetImageHeader)
 *	  copy entire resulting image structure to lpImage.
 *	  In this case, if lpHdr non-NULL, copy header there.
 *	Otherwise, the offset is calc'd from the internal state.
 *	  and lpImage is ref'd but not altered	
 *	If fn return FALSE, *piState is < 0 if true error,
 *		-7 if no lpImage
 *		or vals from GetImageHeader
 *	or 0 if uLine is out of range.
 */
BOOL CalcImageFileOffset(const char * pczFileName, IHEAD  * lpHdr,
			 const IMGTYPE_T uFT,
			 int * piStatus, uint uLine, IMAGE  * pImage,
			 ulong * pulImageLine);

/*
 *	set of fns (in DRAGONU) which make implementation of
 *	image files opaque.
 */
typedef struct DISKIMAGEINFO_tag
    {
//    uint uBytesPP;
//    uint uPixels;
//    uint uLines;
    FILE * pFp;
    char * pBuf;
    } DISKIMAGEINFO_T ;

extern DISKIMAGEINFO_T s_DiskFiles[];

BOOL ImageFilesSetup(const size_t uFirstNdx,const size_t uNBands,
		    int * piStatus);
/*	setup files whose info is stored in imglistptr[uFirstNdx]  
 *	through imglistptr[uFirstNdx+uNBands-1], 
 *	If OK return TRUE & set *piStatus = 0
 *	else set *piStatus to -1 * band# plus -10
 *		   if vfile construct error
 *		or -1 * band# plus -100 * errorcode if vfopen error
 */  
BOOL ImageFileClose(const size_t uImgNo);
/* close one image, freeing its resources
 * Return TRUE if it did exist, else FALSE
 * (but not existing does not => an error)
 *
 * DEPRECATED - use CloseImagei

 */

	/* Recalculate header statistics for image identified
	 * by 'pImg', and returns them in the 'pStats'
	 * structure which must be allocated and freed by the
	 * caller.
	 * User must set ftype in header to determine
	 * binning. If not set to 'C', assume regular img file.
	 * @param pImg    IMAGE to read
	 * @param pStats  Structure to hold stat calc work
	 * @return 0 if ok, negative for error.
	 */
int CalcImageStats(const IMAGE * pImg, IMGSTATS * pStats);

	/* Get a pointer to a label
	 * @param pImage  	Pointer to IMAGE
	 * @param uLabelNo	index of label
	 * @return 		pointer or NULL if uLabelNo out of range
	 */
const LABEL_INFO * getLabel(const IMAGE * pImage, size_t uLabelNo);

	/* Get label text
	 * @param pImage  	Pointer to IMAGE
	 * @param uLabelNo	index of label
	 * @param pczUTF8Buffer	buffer to place text
	 * @param uBufLen	size of buffer
	 * @return 		-90 (DERR_FN_ARG0) if uLabelNo out of range
	 *			else label color index >= 0
	 */
int getLabelText(const IMAGE * pImage, size_t uLabelNo, 
		 char * pczUTF8Buffer, size_t uBufLen);

byte  * ImageFileSeekRaw(const size_t uImgNo, int * piStatus,
			    const uint uLineNo,
			    const uint uIPixByte,
			    const uint uNPixBytes);
	//	Return a pointer to a buffer starting with 'uIPixByte'
	//	and containing at least 'uNPixBytes'
	//	If 'uLineNo' too large, close file & return NULL
	//	Also, return NULL if error and set *piStatus:
	//		-5 -> req. more pix than permitted
	//		or from CalcImageFileOffset
	//	The data returned is exactly the data in the file.

/*
 *  fns in IMG_HDR.C:
 *		(which is a separate file to form a CGATE overlay)
 *		   GetImageHeader(), 
 */

/*	Setup read file whose info is stored in imglistptr[uImgNdx]
 *	This sets up (via CalcImageFileOffset) many of
 *	the IMAGE fields.
 *	~~~ 'pczFilename' no longer permitted to be NULL
 *	If OK return TRUE & set *piStatus = 0
 *	else set *piStatus to:
 *		-1 to -4: see GetImageHeader
 *		-6 if file open error
 *		-7 if invalid img index
 *		-96x see CalculateKeyTable
 */  
BOOL ImageFileSetup(const char * pczFilename,
		    const size_t uImgNdx, int * piStatus);

/*
 * old fns in IMG_ACC
 */

int fillImage(const IMAGE* pImage, const byte uVal); 
	/*	Initialize the passed image according to 'val':
	 *	Used by boxcar. 
         */

   /**
    *  Read the image header and return the size parameters:
    *  lines, pixels and pitch. Return an error
    *  if the file cannot be read (-1), or the file is bigger
    *  than the absolute Dragon max (-2). Otherwise return 0.
    *  @param pczFilename  Image file to check
    *  @param pLines       If no error, use to return lines from hdr
    *  @param pPix         "" use to return pixels from hdr
    *  @param pBytesPerPix  Used to return Bytes per pixel (1 or 2).
    *  @returns error code or 0 for success.
    */
long getImageDimensions(const char* pczFilename,
                        int* pLines, int* pPix, int* pBytesPerPix);

/* init() the image 
 * Return value of Image.iStatus, except:
 *    return -1 if pImage is NULL
 */
int InitImage(IMAGE * pImage, const char * pczFilename);

void DumpImage(const int iImgNdx);

/* get read-only pointer to hdrInfo */
//const HEADER_INFO_FIELDS * GetImageHeaderInfo(const IMAGE * pImage);

/* get read-only histo info */
const void * GetImageHistoInfo(const IMAGE * pImage,
			       ushort * puHistPtrCount,
			       ushort * puHistPtrBinsize);

/************************************************************************
 *
 * C language wrapper fns for img.cpp
 *
 ************************************************************************/

/* create a new Image (for use by C pgms) and return a ptr to its IMAGE struct
 * @param iDebug	debug level if > than set by OB::OB
 * @param iTrace	trace level if > than set by OB::OB
 */
IMAGE * newImage(int iDebug,int iTrace);

/* Open an image and initialize using the information
 * in an existing file. Optionally set this image as
 * being capable of modification. 
 * Basically this is just a wrapper around Image::open.
 * @param pImg         IMAGE structure identifying an existing image
 * @param pczFilename  Filename for image (with path)
 * @param bModifiable  If true, this image can be modified. Else it is
 *                     read only.
 * @return 0 if ok, else negative error value returned from Image::open.
 */
int openImage(const IMAGE * pImg, const char* pczFilename,
	      BOOL bModifiable);


/* set up an Image for output based on another image
 * This works by: 1. Create a new ImageHdr
 *                2. Copy an existing ImageHdr
 *		  3. Allow the selected writer subclass to 
 *                   modify the new ImageHdr
 * 		  4. Init 'this' from the new ImageHdr.
 * If the image geometry need to be cahsed, 
 *   call revise_geom() BEFORE calling write().
 * If the image data differes from pSrcImage,
 *   call update() AFTER writing the image data, 
 *   then call rewriteImageHeader().
 * @param pImg		writable IMAGE
 * @param pczFilename	full, long path of file
 * @param bOverwrite	TRUE => silently delete file if exists
 * @param bReReadable	if TRUE, data can be re-read after writing
 * @param uImgType	type of image file
 * @param pSrcImage	Image to copy
 * @param pczFtype      Dragon file type - "I", "C" or "L",
 *			or NULL to keep type from copy
 * @return		0 if OK
 *			-57 => already exists and bOverwrite=FALSE
 *			-90 to -97 - invalid argument
 */
int createImageCopy(const IMAGE * pImg,
		    const char * pczFilename, BOOL bOverwrite,
		    BOOL bReReadable, IMGTYPE_T uImgType,
		    const IMAGE * pSrcImage,
		    const char* pczFtype);

/* Setup a new output image, specifying critical values
 * This is a wrapper for another Image::create variant
 * All values must be specified.
 * @param pImg		writable IMAGE
 * @param pczFilename	filename with path
 * @param bOverwrite	FALSE = don't overwrite existing file
 * @param bReReadable	TRUE = can read as well as write
 * @param uImgType	type of file to write
 * @param uNumLines	number of lines
 * @param uNumPixels	number of pixels per line
 * @param uBitsPerPix   number of bits per pixel
 * @param uNumBands	number of bands 
 * @param uNumResolutions number of pyramids/resolution tiers
 * @param pczFtype      Dragon file type - "I", "C" or "L"
 * @param pczOriginalName NULL or name of source file
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int createImageNew(const IMAGE * pImg,
		   const char * pczFilename, BOOL bOverwrite,
		   BOOL bReReadable, IMGTYPE_T uImgType,
		   ushort uNumLines, ushort uNumPixels,
		   ushort uBitsPerPix, ushort uNumBands,
		   ushort uNumResolutions, const char* pczFtype,
		   const char * pczOriginalName);

/* Revise critical values for an existing writable image.
 * This is a wrapper for img::revise_geom.
 * Only the params with non-default vals will be changed.
 * This must be invoked BEFORE writing the header
 * @param pImg		writable IMAGE
 * @param pczFilename	NULL => do not change
 * @param bOverwrite	FALSE => do not change
 * @param bReReadable	FALSE => do not change
 * @param uImgType	IT_INVALID => do not change
 * @param uNumLines	0 => do not change
 * @param uNumPixels	0 => do not change
 * @param uBitsPerPix	0 => do not change
 * @param uNumBands	0 => do not change
 * @param uNumResolutions 
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int reviseImageGeometry(const IMAGE * pImg,
			const char * pczFilename, BOOL bOverwrite,
			BOOL bReReadable, IMGTYPE_T uImgType,
			ushort uNumLines, ushort uNumPixels,
			ushort uBitsPerPix, ushort uNumBands,
			ushort uNumResolutions);

/* change scaling information for an existing image.
 * Only the params with non-default vals will be changed.
 * This may be invoked after writing the header and the image data
 * @param pImg		writable IMAGE
 * @param dScaleFactor	factor, value for BINARY or OPTIMAL scaling
 * @param ScaleOffset	offset, value only if OPTIMAL scaling
 * @param pczScalingType 'B', 'O', 'N'o change, or \0 for none
 *   ( the following give calibration meaning to pixel values )
 *   ( if dZ_scale == 0, none of these are set by this fn)
 *   ( calibrated value = (pixel value * dz_Scale) + offset)
 * @param dZ_scale	multiplicative factor
 * @param dZ_offset	additive factor 
 * @param pcZ_unit 	name of pixel calibration units
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int updateImageScaling(const IMAGE * pImg,double dScaleFactor,
		       double dScaleOffset,
		       const char * pczScalingType,
		       double dZ_scale,
		       double dZ_offset,
		       const char * pcZ_unit);

/* change text information (except classnames, unitnames) 
 * for an existing image.
 * Only the params with non-NULL vals will be changed.
 * This may be invoked after writing the header and the image data
 * @param pImg		writable IMAGE
 * @param (all of them)	NULL or new value (possibly "")
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int updateImageText(const IMAGE * pImg,
		    const char * pczTitle,
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
int updateImageStats(const IMAGE * pImg,const IMGSTATS * pImgStats);

/* change georeferencing information information for an existing image.
 * This may be invoked after writing the header and the image data
 *
 * NOTE: ref_x, ref_y, pczProjection, pczUnitname 
 *	 may be NULL to indicate no change
 *	 but other args MUST be supplied.
 *
 * @param pImg     Pointer to IMAGE to be updated
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
 *			-66 => state conflict
 *			-90 - invalid argument
 */
int updateImageGeoref(const IMAGE * pImg, 
		      int img_x, int img_y, 
		      const MapCoord * ref_x, const MapCoord * ref_y,
		      double xcell_size, double ycell_size,
		      const char* czProjection, const char* unitname,
		      const char * pczDateTime,const char * pczUTMZone,
		      int iRegistered);

	/* change labels information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * If <b>iNumLabels</b> is different from than the current number of labels,
	 * 	the function will discard all the old labels and replace them
	 * 	with the new ones.
	 * If <b>iNumLabels</b> is -1, or the same as the current number, 
	 * 	the function will only replace the first <b>uArrayCount</b> labels.
	 * @param iNumLabels	-1 for don't change, or number of labels in img
	 * @param uArrayCount	number of items in pLabels
	 * @param pLabels	label info
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
int updateImageLabels(const IMAGE * pImg,
		      int iNumLabels,
		      size_t uArrayCount,
		      const LABEL_INFO * pLabels);

        /* Use a source image to copy the meta file information to a target
         * image. This will effectively add the target image to the same
         * IGC group as the source.
         * @param pTargetImage  Image to update
         * @param pSrcImage     Image to use to get metafile information.
         * @return 0 if successful otherwise negative error code.
         */
int updateImageMetaInfo(const IMAGE* pTargetImage, const IMAGE* pSrcImage);

	/* change originalfile information 
	 * for an existing image.
	 * Only the params with non-NULL or >= 0 vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int updateImageOriginal(const IMAGE * pImage,
			uint uOriginalBandCount,
			uint uOriginalBandNumber,
			const char * pczOriginalFileName);

	/* write the image header
	 * @return 	0 if OK
	 *		else error number - see img.h
	 */
int writeImageHeader(const IMAGE * pImg);

	/*	rewrite image header and write trailer
	 *	On exit, file is closed
	 *	This CAN be used for modifiable input image
	 *	@param pImg		image to be written
	 *	@param uDataCheck	checksum of the image data rows
	 *				for trailer (0 => not valid, ignore)
	 *	@param bWriteTrailer	FALSE => don't write trailer yet
	 *	Return 0 if OK
	 *	Error values are:
	 *		-16 => op not needed (not an error)
	 *		-50 - -55 file IO errors
	 *		-65 => no name supplied
	 *		-66 => image state conflict
	 *		-69 => no header writer found
	 */
int rewriteImageHeader(const IMAGE * pImg, UINT32 uDataCheck, 
			BOOL bWriteTrailer);

	/* write the image trailer
	 *	On exit, file is closed
	 * @param uDataCheck	checksum of image data
	 * @return 	0 if OK
	 *		else error number - see img.h
	 */
int writeImageTrailer(IMAGE * pImg,UINT32 uDataCheck);

      /* Sets image structure to empty, default values.
       */
void zeroImgInfo(IMAGE * pImg);

	/* get size limits for MAINIMG.
	 * For getWorkingBits, this may depend on the operation
	 * @param pczOp		3-letter operation code, or "" or NULL
	 *			if "" or NULL return lowest value
	 */

	/* copy blob info from an existing image.
	 * @param pImg 	        Image to be updated
         *                      Source existing image is already
         *                         known because it was used to initialize
	 *                         pImg.
	 * @return		0 if OK
	 *			-66 => state conflict
	 */
int copy_blob(const IMAGE * pImg);

/**
 * This is a convenience function that calls the statistics
 * calculation on the passed image and then updates the
 * internal image header statistics information.
 * It does NOT rewrite the header, unlike the previous
 * function with this name.
 * Unlike the function in imstat-o, this function does not
 * deal with things like stretching or masking.
 * ~~~ DO NOT CONFUSE THIS WITH CalcandSetImageStats IN imstat-o.c
 * (although they essentially do the same thing)
 * @param pImage  Pointer to IMAGE for which we want to calc stats
 * @return 0 unless error occurs,then negative value.
 */
int CalcAndSetImageStats(const IMAGE * pImage);

ushort getWorkingBits(const char * pczOp);
ushort getWorkingLines();
ushort getWorkingPixels();
#if DRAGON_VER <= 5
const char * getWorkingImageFile();
#endif // #if DRAGON_VER <= 5

/* get read-only pointer to hdrInfo */
/* GetImageHeaderInfo() is deprecated name */
const IMAGEHDR * GetImageHeaderInfo(const IMAGE * pImage);

/**
 * Convenience function allows us to get the image header
 * structure associated with an Image class instance by
 * way of its IMAGE structure (so we can use this in C).
 * @param pImage Pointer to IMAGE structure.
 * @return corresponding (read-only) header structure.
 */
const IMAGEHDR * getIMAGEHDR(const IMAGE * pImage);

/* get the bitpattern (see valid_image())
 * for current Image.
 * Return value of Image.iStatus, except:
 *    return -60 if pImage is NULL
 *    return m_iErrno if other errors
 */
int GetImageStatus(const IMAGE * pImage);

   /* Given a Dragon header structure, calculate the
    * minimum and maximum extent in geographic coordinates
    * that is represented by the image.
    * @param pHdr  Pointer to OpenDragon header structure.
    * @param pMinExtent Pointer for returning minimum X and Y value
    * @param pMaxExtent Pointer for returning maximum X and Y value
    * Note that the min Y could be at the lower left rather
    * than the upper left, depending on the coordinate system.
    * @return TRUE if coordinate system flipped (Y cell size negative)
    *         else FALSE;
    */
BOOL calculateHeaderExtent(const IMAGEHDR * pHdr, VERTEX* pMinExtent, VERTEX* pMaxExtent);

/* Clear out igc meta file and GUID information from image
 * header, and rewrite the header. This should be called whenever
 * the user does something that will destroy geographical congruence.
 * @param pImage  Pointer to IMAGE that should be cleared.
 * @return 0 or negative for error.
 */
int clearImageMetaInfo(const IMAGE* pImage);

/* Compare the georeferencing information in two images
 * to see if they are the same or not. Returns TRUE if
 * they are the same, FALSE if different.
 * @param pImage1 First image to compare - assumed to be open and initialized
 * @param pImage2 Second image to compare - ditto
 * @return TRUE if the georeferencing is the same for the two images.
 */
BOOL compareImageGeoref(const IMAGE* pImage1, const IMAGE* pImage2);

/* Test to see if an image is georeferenced. We do this by
 * looking at the map coordinates of the image X and Y pt.
 * @param pImage  Image to check
 * @return TRUE if georeferenced  else FALSE
 */
BOOL isGeoreferenced(const IMAGE* pImage);

/* Explicitly set the processing rectangle to something special.
 * This is needed in CUR to make sure that we don't try to read
 * more data than will fit in our buffer when the background image
 * is smaller than the data images.
 * @param pImage  Image whose rectangle we want to set.
 * @param xmin  minimum pixel value
 * @param xmax  maximum pixel value; if == 0 ignore xmin,xmax
 * @param ymin  minimum line value
 * @param ymax  maximum line value; if == 0 ignore ymin,ymax
 */
void SetImageProcessRect(const IMAGE* pImage,
			 uint xmin, uint xmax, uint ymin, uint ymax);
	    /* COPY the specified blob */
int setLinesBlob(const IMAGE * pImg,const byte * pBlob,size_t uBlobSize);
	    /* if non-NULL, ptr to blob of vector data */
byte * getLinesBlob(const IMAGE * pImg);
	    /* number of bytes in LinesBlob */
size_t getLinesBlobLen(const IMAGE * pImg);
#ifdef __cplusplus
        }
#endif

#endif
