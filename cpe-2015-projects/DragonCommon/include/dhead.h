/*
 *	filename dhead.h
 *		$Revision: 1.43 $ $Date: 2015/01/21 10:39:37 $	
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
 *   $Id: dhead.h,v 1.43 2015/01/21 10:39:37 rudahl Exp $
 *   $Log: dhead.h,v $
 *   Revision 1.43  2015/01/21 10:39:37  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.42  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.41  2014/12/05 11:51:02  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.40  2014/04/01 07:24:45  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.39  2014/03/28 15:00:51  rudahl
 *   working on auto import
 *
 *   Revision 1.38  2014/02/22 13:26:11  rudahl
 *   lint
 *
 *   Revision 1.37  2014/01/25 05:48:40  rudahl
 *   add geotiff fields to header
 *
 *   Revision 1.36  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.35  2011/01/10 06:37:23  rudahl
 *   working on georef info
 *
 *   Revision 1.34  2008/06/14 10:15:55  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.33  2007/08/02 11:26:02  rudahl
 *   changed some member vars from ushort to int
 *
 *   Revision 1.32  2007/01/01 09:43:22  rudahl
 *   improved tracing, dumps; originalfileinfo
 *
 *   Revision 1.31  2006/12/31 12:15:00  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.30  2006/08/20 11:05:07  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.29  2006/08/11 07:17:47  rudahl
 *   added BIL_ESRI
 *
 *   Revision 1.28  2006/08/09 09:49:20  goldin
 *   Adding support for writing shapefiles
 *
 *   Revision 1.27  2006/08/04 08:23:09  goldin
 *   Separate vector reading from base VectorData class
 *
 *   Revision 1.26  2005/07/23 08:24:07  rudahl
 *   fine-tuning geotiff
 *
 *   Revision 1.25  2005/07/22 15:19:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.24  2005/07/15 02:41:09  rudahl
 *   added czFileType
 *
 *   Revision 1.23  2005/07/13 11:06:21  rudahl
 *   added geotiff-style georeferencing fields
 *
 *   Revision 1.22  2005/06/26 06:18:29  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.21  2005/03/19 06:25:44  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.22  2005/03/09 23:14:12  rudahl
 *   moved class ImageHdr from dhead to imageHdr.h
 *
 *   Revision 1.21  2005/03/09 01:34:50  rudahl
 *   fix missing args in update_text(), add CloseImage
 *
 *   Revision 1.20  2005/03/06 17:32:09  rudahl
 *   revising create() and update_text() args
 *
 *   Revision 1.19  2005/03/06 00:14:43  rudahl
 *   Moved creation of writer until writeTrailer
 *
 *   Revision 1.18  2005/03/03 21:50:01  goldin
 *   Implement remaining revise_ & update_ methods
 *
 *   Revision 1.17  2005/03/03 16:15:43  rudahl
 *   refinements while converting grstop
 *
 *   Revision 1.16  2005/03/01 23:04:43  goldin
 *   Implement new create function for new output images; fix update functions
 *
 *   Revision 1.15  2005/03/01 16:04:12  rudahl
 *   changed label structure
 *
 *   Revision 1.14  2005/02/28 21:15:51  goldin
 *   add update_georef methods
 *
 *   Revision 1.13  2005/02/24 17:42:52  rudahl
 *   added m_uImageType
 *
 *   Revision 1.12  2005/02/23 17:46:44  rudahl
 *   new update, wrapper fns; moved from hdrstats to dhead
 *
 *   Revision 1.11  2005/02/10 04:59:39  rudahl
 *   cleaned up tracing and error reporting
 *   cleaned up image file writing
 *
 *   Revision 1.10  2005/02/07 05:41:08  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.9  2005/02/03 03:24:00  rudahl
 *   work on implementing new create(), getImageLine etc in img class
 *   plus beginning of standardized error numbers
 *
 *   Revision 1.8  2005/02/01 01:41:48  rudahl
 *   cvt from header r/w to image r/w
 *
 *   Revision 1.7  2005/01/27 21:37:21  rudahl
 *   writer now has const struct
 *
 *   Revision 1.6  2005/01/27 16:09:14  rudahl
 *   enhanced testing
 *
 *   Revision 1.5  2005/01/26 01:51:13  rudahl
 *   added typenames, tracing
 *
 *   Revision 1.4  2005/01/20 19:39:20  rudahl
 *   added image type defns
 *
 *   Revision 1.3  2005/01/18 18:22:41  rudahl
 *   added IMG_LAYOUT and pitch params
 *
 *   Revision 1.2  2005/01/05 02:26:28  rudahl
 *   add s_class_Base
 *
 *   Revision 1.1  2005/01/04 15:48:59  rudahl
 *   initial from moochie
 *
 ****************************************************************
 * 
 * This file defines a typedef struct which abstracts all 
 * image header information which is used by Dragon during processing.
 *
 * The content of this and imagehdr.cpp are derived from parts
 * of img_hdr.c, img_acc.c, img.cpp, and ob.cpp in Dragon 5.4.
 * The structs defined herein are similar to the Dragon header
 * structure in v 5.4 and earlier. 
 *
 * This file requires dtypes.h
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2004-12-31 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 *	2005-3-9 ktr	moved definition of class ImageHdr to imageHdr.h
 * 5.7	2005-6-25 ktr	added DRAGON_OLD file type, for backward compat
 * 	2005-7-13 ktr	added Geotiff-stype georeferencing fields
 *			added more filetypes (e.g. jpeg)
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 *	2008-06-14 ktr	added LinesBlob to trailer
 */

#if ! defined DHEAD_H
#define DHEAD_H	/* signal this file has been loaded */

//#pragma pack(4) // makes no difference

// these came from img.h v 5.4, with IT_CHUNK54 and IT_CHUNK60 added
typedef enum { 	IT_UNINIT,	// no other field is valid
		IT_AUTO,	// only 'filename' is valid.
		IT_VIRTUAL,	// structure refers to a virtual file
		IT_DRAGON,	// DRAGON .IMG file
		IT_ERDAS,
		IT_BIL,		// not yet implemented
		IT_BSQ,		//  "       "
		IT_TIFF,	// non-banded, non-compr. not yet impl.
		IT_CHUNK54,	// reverse-line-ordered RGB
		IT_CHUNK60,	// std-line-ordered RGBA
		IT_DRAGON_OLD,	// DRAGON .IMG file
		IT_JPEG,
		IT_JPEG2000,
		IT_PNG,
		IT_BIL_ESRI,	// .dat BIL file and matching .hdr metafile
		IT_EXTERN=29,	// unspecified proxy from externImageReader
				// EXTERN => bandcount, dimensions, origfilename are valid
                IT_DRAGON_VEC = 30,   // vector formats start here
		IT_ESRI_SHAPE,
		IT_IGC_META = 50,   // IGC metafile
		IT_INVALID } IMGTYPE_T;

#define IMGTYPE_NAMES "IT_UNINIT", \
		"IT_AUTO",\
		"IT_VIRTUAL",\
		"IT_DRAGON",\
		"IT_ERDAS", \
		"IT_BIL",\
		"IT_BSQ",\
		"IT_TIFF",\
		"IT_CHUNK54",\
		"IT_CHUNK60",\
		"IT_DRAGON_OLD",\
		"IT_JPEG", \
		"IT_JPEG2000", \
		"IT_PNG", \
		"IT_BIL_ESRI", \
                "","","","","", \
                "","","","","", \
		"","","","","IT_EXTERN", \
		"IT_DRAGON_VEC",\
		"IT_ESRI_SHAPE",\
		"","","", \
		"","","","","", \
		"","","","","", \
		"","","","","", \
                "IT_IGC_META",\
		"IT_INVALID"

typedef enum 
    {
    IMG_PACKED1,	/* packed single band */
    IMG_PIL,		/* interleaved pixels */ 
    IMG_BIL,		/* interleaved lines */ 
    IMG_BSQ,		/* sequential bands */
    IMG_UNKNOWN = 10
    } IMG_LAYOUT;

#define IMG_LAYOUT_NAMES \
    "IMG_PACKED1 : packed single band",\
    "IMG_PIL : interleaved pixels",\
    "IMG_BIL : interleaved lines",\
    "IMG_BSQ : sequential bands", \
    "","","","","","", \
    "IMG_UNKNOWN : not known"

/* The following values are usually properties which are constant
 * for any specific file format.
 */
#define FILETYPE_SZ 64
#define IHDR_IMAGE_FORMAT \
	BOOL bBinary;		/* FALSE => ASCII data */ \
	BOOL bRectangular;	/* FALSE => eash line is different length */ \
	uint uBands;		/* how many bands in file */ \
	ulong ulDataOffset;	/* bytes from start of file to image data */ \
	/* following mostly useful if uBands > 1 */ \
	IMG_LAYOUT uBandLayout;	/* enum */ \
	ulong ulDataSize;	/* total bytes of image data; 0 => unknown */ \
	ulong ulPixelPitch;	/* bytes from one pixel of band to the next */\
	ulong ulLinePitch;	/* bytes from one line of band to the next */ \
	ulong ulBandPitch;	/* bytes from one band to the next */ \
	char czFileType[FILETYPE_SZ+1];  /* orig. file type and version */ 

/* the following sets of fields parallel the ones named HDR_xx in dragonHd.h
 * but they have (in general) the same names and sizes as did the older 
 * version of dhead.h. 
 * However, note that all appropriate character buffers are allocated
 */
#define IHDR_DESCRIPION \
	char * h_title; \
	char * h_id; 	\
	char * comment; \
	char * source;	\
	char * scene; 	\
	char * subscene; \
	char * band; \
	uint h_uOriginalBandCount; /* how many bands in original file */ \
	uint h_uOriginalBandNumber; /* which band did this come from (0-based)? */ \
	char * h_OriginalFileName;  	/* orig. name */ \
        BOOL bImageHdrDescriptionInit; /* TRUE => this section has been set */

/* the following values cannot be changed in any file header 
 * without having to rewrite the image data as well.
 */   
#define IHDR_FILE_PARAMS \
	char ftype[2];		/* 'C'=class. 'I'=image 'L'=layer */ \
                        	/* (use only char[0] of array ) */ \
	ushort size[2]; 	/* elt[0] is lines, [1] is pix */\
	ushort bits_per_pix; 	/* allows us to handle multibyte images */ \
				/* in limited fashion. Only used if vn >= 41*/\
				/* maximum supported is 16 bits/pix */ \
	ushort uEncoding;	/* normally 'SR' = standard raster */ \
	ulong iff_offset; 	/* if non-zero, indicates location \
				 * (from start of file) of trailer. */ \
	ushort uKey;		/* v 5.4; non-zero => this is a locked file */\
        BOOL bImageHdrInitialized; /* TRUE => this section has been set */

#if DRAGON_VER >= 6
	/* h_ulByteOrder not needed; it was used reading this data */
#define IHDR_STATS \
	int m_ihImgmean;	/* mean value of all image data */ \
	int m_ihImgmax;		/* max data value in image */ \
	int m_ihImgmin;		/* min data value in image */ \
	double m_dhImgvar;	/* variance of all image data  */ \
	double m_dhImgsd;	/* standard deviation of image data */ \
        BOOL bImageHdrStatsInit; /* TRUE => this section has been set */
#else
#define IHDR_STATS \
        short imgmean;          /* mean value of all image data */ \
        short imgmax;           /* max data value in image */ \
        short imgmin;           /* min data value in image */ \
        double imgvar;          /* variance of all image data  */ \
        double imgsd;           /* standard deviation of image data */ \
        BOOL bImageHdrStatsInit; /* TRUE => this section has been set */
#endif

	/* ~~ norm, upper, and lower maybe no longer in use */
//        ushort norm;		/* normalization: 
//				 * 0=none,1=default,2=inverse,3=usr 
//				 * 4 = equalized, 5 = Gaussian */ 
//	ushort upper;		/* upper bnd for stretch 
//				 * if norm == 1, 2, or 3 */ 
//	ushort lower;		/* lower bound */ 

#define IHDR_SCALING \
		/* following are two alternative ways to represent \
		 * the scaling which MAY have been used to scale from \
		 * multibyte to 8-bit data. \
		 * Only ONE of uScaleFactor/dScaleFactor may be non-zero */\
	ushort uScaleFactor;	/* BINARY scaling used, or 0 */ \
	double dScaleFactor;	/* OPTIMAL scale factor or 0.0 */ \
	double dScaleOffset;	/* OPTIMAL scale offset, or 0.0 */ \
		/* the following give calibration meaning to pixel values */ \
	double z_scale;	/* mult by pixel value to produce z_unit-default=1.0*/\
	double z_offset; /* calibrated_value=(pixvalue+65 z_offset)*z_scale*/\
	char * z_unit; 		/* name of pixel calibration units */\
        BOOL bImageHdrScalingInit; /* TRUE => this section has been set */

        /* Structure to allow flexible encoding of map or reference coordinates
	 * including lat/long coordinates. Now we are using only v0.    
	 */
typedef struct
    {
    double v0;
    ulong ulTag;                 /* reserved */
    long v1;
    long v2;
    } MapCoord; 

typedef struct
    {
    ushort uI, uJ, uK;	/* location in raster space */
    double dX, dY, dZ;  /* location on model space */
    } TIEPOINT_t;

#define IHDR_GEOREF \
	/* georeferencing information \
	 * normally initialized by registration utility \
	 * or via DRAGON HEA operation */ \
	short img_x;	    /* +/- pixel num of origin/fixed point-usually 0*/\
	short img_y;	    /* +/- line number of fixed point - usually 0 */ \
	MapCoord ref_x;     /* map/reference x coord of fixed point   */ \
	MapCoord ref_y;     /* map/reference y coord of fixed point   */ \
	double xcell_size;  /* size of one cell in X direction at fixed pt */ \
	double ycell_size;  /* size of one cell in Y direction at fixed pt */ \
			    /* if negative, the corresponding axis is reversed\
			     * relative to the image coordinate system. I.e. \
			     * if xcell_size is negative, pixels have smaller \
			     * x map coords as you move from left to right\
			     * if ycell_size is negative, pixels have smaller \
			     * y map coords as you move from top to bottom */ \
        char * czProjection; /* code for map proj'n - not currently used */ \
	char * unitname;   /* map units - null terminated */ \
	char * czUTMZone;  /* 1-60[N|S] not yet in Dragon header */ \
	char * czDateTime; /* yyyy:mm:dd HH:MM:SS not yet in Dragon header */ \
	BOOL bRegistered;  /* is it registered to map coords? */\
	BOOL georef_init;  /* TRUE => georeferencing fields have been set */\
        BOOL bImageHdrProjectionInit; /* TRUE => projection has been set */ \
		/* The following fields are essentially identical to the \
		 * corresponding georeferencing fields in the Geotiff spec \
		 * (www.remotesensing.org/geotiff/spec) assuming a \
		 * "Projected Coordinate System \
		 * Typically a code value of 0 means the field has not been \
		 * specified or initialized. \
		 * Either pModelTiepoints must = NULL and uModelTiepoints = 0,\
		 * or both must be defined and uModelTiepoints must be the \
		 *    number of tiepoints pointed to by pModelTiepoints \
		 *    AND  the older georef params must agree with \
		 *    pModeltiepoints[0] \
		 */ \
		/* first the coordinate transforms data */ \
	TIEPOINT_t * pModelTiepoints;  /* default; NULL */ \
	ushort uModelTiepoints;      /* default: 0 */ \
	double dModelPixelScale[3]; \
	BOOL bModelPixelScaleInit;\
	double dModelTransformation[16]; \
	BOOL bModelTransformInit;\
		/* then the raster type */ \
	ushort uRasterType;           /* 0=not spec'd 1=area 2=point */ \
		/* the model type. Only 1 & 2 supported */ \
	ushort uModelType;            /* default: 0 = not specified */ \
		/* params for model type 1 (projected) */ \
	ushort uProjectedCSType;      /* default: 0 = not specified */ \
	ushort uProjectedLinearUnits; /* default: 0 = not specified */ \
/*	ushort uGeoAngularUnits; */ /* default: 0 = not specified */ \
		    /* following only needed only for non-std CSTypes */ \
	ushort uProjectionGeo;        /* default: 0 = not specified */ \
	ushort uProjectionCoordTrans; /* default: 0 = not specified */ \
		/* params for model type 2 (geographics lat-long) */ \
	ushort uGeographicType;      /* default: 0 = not specified */ \
	ushort uGeodeticDatum;     /* default: 0 = not specified */ \
	ushort uGeographicPrimeMeridian; /* default: 0 = not specified */ \
		/* params in case of vertical data */ \
	ushort uVerticalType;        /* default: 0 = not specified */ \
	ushort uVerticalUnits;       /* default: 0 = not specified */

/* Fields for metafile information. These strings are
 * alloc'ed when the header is read, and must be freed.
 */
#define IHDR_METAFILE \
	char* pczMetafile; \
        char* pczGUID;

/* Fields for extent information */
#define IHDR_EXTENT \
	BOOL bExtentInit;   /* TRUE => extent fields have been set */\
	double dMinX;       /* min X coord defining bounding box */ \
	double dMinY;       /* min Y coord of bounding box  */ \
	double dMaxX;       /* max X coord defining bounding box */ \
	double dMaxY;       /* max Y coord of bounding box  */

typedef struct	/* info about each label */
    {
    ushort uValue;	/* for each 'extname' or 'oldname', 
			 * the corresponding image data value.
			 * For a 'C' file, this is the class#*/
    byte uColorNdx;	/* palette index - not yet used */
    char czI18NKey[8];	/* if != '', is probably in range of %h4600-%h460F.
			 *   to form I18N key for name */
    char * pczText;
    } LABEL_INFO;

#define IHDR_CLASSIFY \
	char * pczColorFileName; \
	uint uNumLabels; \
	LABEL_INFO * pLabels; 	/* array of LABEL_INFOs */ \
	void * pPalette;    	/* ~~ not currently used : array of UINT32 */ \
	ushort uPaletteCount; 	/* how many UINT32s */ \
        BOOL bImageHdrClassifyInit; /* TRUE => classification has been set */

typedef struct 		/* DRAGON image header info extracted from file */
    {
    IHDR_DESCRIPION
    IHDR_FILE_PARAMS
    IHDR_STATS
    IHDR_SCALING
    IHDR_GEOREF
    UINT32 * histo; 	/* image histogram: 0'th elt. is total.
			 * successive elts are binned in fours, 
			 * so each elt. 1 to 64 holds total count 
			 * for four data values.
			 * NOTE: bin size will be > 4 for images with
			 * more than 8 bits/pix */
    ushort uHdrHistLen; /* number of elements in histo, or 0 if not init.*/
    IHDR_CLASSIFY
    IHDR_IMAGE_FORMAT
    IHDR_METAFILE
    IHDR_EXTENT
    } IMAGEHDR ;

typedef IMAGEHDR IHEAD; /* for backward compat. */

//#pragma pack()

/* moved here from img.h per Sally's recommendation 2005-2-23 */
#define IMG_HIST_LEN 257     /* elements in in-memory histogram */

/* structure for neatly passing header statistics information */
/* around between functions.                                  */
/* moved here from hdrstats.h per Sally's recommendation 2005-2-23 */

typedef struct imgstats
    {
    IHDR_STATS			/* see dhead.h */
//  SCALAR_STATS_FIELDS	/* see dhead.h - has odd number of 16-bit elements */
    unsigned short numlines, numpix; /* keep info on number of lines/pix per line    */
    unsigned short bits_per_pix;	/*  if 8 or less, we store actual values in the */
                        /*  histogram array. Otherwise, we store pointers */
			/*  to other histograms.                          */
    unsigned short bytes_per_pix;  /*  in case we need this */
    union
        {
        unsigned long imghist[IMG_HIST_LEN];  	/* histogram array */
        struct 
             {
             unsigned long histcount;
             unsigned long * ptr_array[IMG_HIST_LEN - 1];
             } ptrhist;
        } hist;
    double sum;    /* sum of pix values - for mean, variance */
    double sumsq ; /* sum of squares - for var -double to prevent overflow */
    } IMGSTATS ;


#endif // DHEAD_H

