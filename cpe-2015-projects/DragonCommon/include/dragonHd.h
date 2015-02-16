/****************************************************************
 *	dragonHd.h - structure for DRAGON image header
 *	  (renamed from dhead.h)
 *          $Revision: 1.32 $	$Date: 2015/01/21 10:39:37 $
 *
 *          ~~ Copyright 1986-2015 Kurt Rudahl and Sally Goldin
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
 *****************************************************************
 *
 *	$Id: dragonHd.h,v 1.32 2015/01/21 10:39:37 rudahl Exp $
 *	$Log: dragonHd.h,v $
 *	Revision 1.32  2015/01/21 10:39:37  rudahl
 *	improving imageReader - 2drag coordination
 *
 *	Revision 1.31  2014/12/05 11:51:02  rudahl
 *	added ifdefs to match DragonProf and OpenDragon
 *
 *	Revision 1.30  2014/01/25 05:48:40  rudahl
 *	add geotiff fields to header
 *
 *	Revision 1.29  2011/02/27 08:27:43  rudahl
 *	added some docs
 *
 *	Revision 1.28  2011/01/12 04:42:34  rudahl
 *	added new registration fields to update_georef and header
 *
 *	Revision 1.27  2011/01/10 06:37:23  rudahl
 *	working on georef info
 *
 *	Revision 1.26  2008/08/16 06:28:53  goldin
 *	define string constants for header field lengths (used in grsproc1.c)
 *
 *	Revision 1.25  2008/06/14 10:15:55  rudahl
 *	added LinesBlob to trailer
 *	
 *	Revision 1.24  2007/08/02 11:27:09  rudahl
 *	changed some stats vars from uint to int
 *	
 *	Revision 1.23  2007/01/01 09:43:22  rudahl
 *	improved tracing, dumps; originalfileinfo
 *	
 *	Revision 1.22  2007/01/01 04:51:25  rudahl
 *	improved docs; added ulByteOrder
 *	
 *	Revision 1.21  2006/12/31 12:15:00  rudahl
 *	fixing up the external driver and trailer access
 *	
 *	Revision 1.20  2006/08/20 11:05:07  goldin
 *	Add fields for metafile and extent to Dragon header, reader and writer
 *	
 *	Revision 1.19  2006/01/06 03:08:04  rudahl
 *	added HDR-SPECTRAL
 *	
 *	Revision 1.18  2005/12/10 11:54:14  rudahl
 *	chamged interpretation of h_ulByteOrder
 *	
 *	Revision 1.17  2005/09/17 14:41:29  rudahl
 *	revised args for trailer
 *	
 *	Revision 1.16  2005/07/15 02:42:03  rudahl
 *	bumped header version to 5.08
 *	
 *	Revision 1.15  2005/03/04 16:09:15  san
 *	changed size of magic
 *	
 *	Revision 1.14  2005/03/03 23:11:51  rudahl
 *	shortened fixed text
 *	
 *	Revision 1.13  2005/03/02 16:44:19  rudahl
 *	changed trailer struct
 *	
 *	Revision 1.12  2005/03/01 19:32:34  rudahl
 *	improved trailer documentation
 *	
 *	Revision 1.11  2005/03/01 16:04:12  rudahl
 *	changed label structure
 *	
 *	Revision 1.10  2005/02/23 01:04:27  rudahl
 *	changed text fields to include magic
 *	
 *	Revision 1.9  2005/01/03 07:40:04  rudahl
 *	cleanup
 *	
 *	Revision 1.8  2004/12/31 11:03:17  rudahl
 *	import with new header definitions for v 5.5
 *	
 *	Revision 1.7  2004/12/28 12:18:30  rudahl
 *	added UTF-8 text fields to trailer
 *	
 *	Revision 1.4  2002/05/03 00:33:56  rudahl
 *	added trailer defns
 *
 *****************************************************************
 *
 * Define the header structure used by Dragon image files
 * This represents the actual structure of the dragon image files
 * using the new (5.8) format. The older formats are in dhead-old.h.
 * This file used to be named dhead.h, but dhead.h is now a virtual
 * equivalent.
 *
 *		data types are little-endian, 80x86 format
 *
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 *	12/26/90 ktr	changed IHEAD.class to IHEAD.dclass for c++ use
 *       8/24/90 seg	adjusted field size for clstab[128] to fit actual
 *			usage.
 *       2/09/92 seg	Modifications for V3.05. Added new fields for
 *			georeferencing info, and for extensible headers
 *			in the future. Also improved comments.
 *       2/15/92 seg	Moved georef info to end of header
 *	 5/16/92 ktr	Added HDRSTATS typedef; augmented 5/30/92
 *	3/13/93	ktr	revised HDRSTATS to use SCALAR_STATS_FIELDS
 * 4.0	11/21/93 ktr	cosmetic changes B4 release toolkit v 4
 *      04/24/94 seg	Added bits_per_pix field, which is assumed
 *			to be initialized only if vn == 41. Otherwise
 *			assume 8 bits/pix. Change mean, min, max,upper,lower,
 *			to be unsigned.  Add sum, sumsq fields to hdrstats
 *			structure.
 * 4.1	6/24/94 ktr	fixed bits_per_pix to preserve packing
 *			added z_scale, z_offset, z_unit for pix. value calibration
 *	7/17/94 seg	moved HDRSTATS to hdrstats.h, renamed it 
 *			IMGSTATS. Added new consts HDR_HIST_LEN,
 *                      IMG_HIST_LEN, replacing old HIST_LEN.
 *	10/18/94 ktr	added provision for EXTended class names using
 *			wide chars as Unicode.
 *      12/12/94 seg    Changed ftype to be a char[2] array, bits_per_pix to
 *                      ushort, to avoid problem with RP setdefault on 1byte
 *      12/19/94 seg    Fixed errorneous field mapping on old style class
 *                      names (i.e. revised defn for dclass field)
 * 5.0	1/19/98 ktr	Revised for version 5.0: added fields:
 *			 czProjection,uScaleFactor,dScaleFactor,dScaleOffset
 * 5.4	5/1/2002 ktr	added definition and documentation for trailer
 *	12/27/2004 ktr	added COMMENT, SCENE etc to trailer in utf8
 *			(not yet used by Dragon)
 * 5.5	2004-12-31 ktr	New header version (5.6) for Dragon 5.5 and later
 *			completely non-compat with previous versions
 * 5.7	2005-7-14 ktr	initial use will be v 5.7
 *	2006-1-6 ktr	added HDR_SPECTRAL; not currently used
 * 5.10	2007-01-01 ktr	bump DHEAD_VERSION to 50A
 * 5.11 2007-05-12 ktr	permit 32-bit signed data; bump DHEAD_VERSION to 50C
 *	2008-06-14 ktr	added LinesBlob to trailer
 */

/*	NOTE 
 *		All text fields in header are
 *		assumed to be UTF-8
 */

#ifndef DRAGONHD_H
#define DRAGONHD_H	/* signal this file has been loaded */

#define DHEAD_VERSION	0x50C

#define DHEAD 2048
#define IMG_HIST_LEN 257     /* elements in in-memory histogram */
#define DOUBLE_SZ 32	     /* # ASCII chars in scientific notation for double */
#define DOUBLE_SZ_SMALL 24 

/* sizes for text strings are number of <b>characters</b>, 
 * not number of <b>bytes</b>. 
 * For Unicode, the size of the buffer needs to be up to
 * 3 * the number of characters, +1 for the NULL.
 * To achieve pack(4), number of characters should be 4n+1,
 * for some 'n'.
 */

/* the HDR_DESCRIPT_FIELDS are description only
 */
#define HDR_RO_SZ 	12       /* ASCII chars */
#define HDR_TITLE_CHRS 	33
#define HDR_ID_CHRS 	21 
#define HDR_COMMENT_CHRS 65
#define HDR_COMMENT_LEN_STR "195"
#define HDR_SOURCE_CHRS 5
#define HDR_SOURCE_LEN_STR "15"
#define HDR_SCENE_CHRS 	23
#define HDR_SCENE_LEN_STR "69"
#define HDR_SUBSCENE_CHRS 21
#define HDR_SUBSCENE_LEN_STR "63"
#define HDR_BAND_CHRS 	5
#define HDR_BAND_LEN_STR "15"
#define HDR_SENSOR_CHRS	33
#define HDR_TITLE_RO 	"DragonImg  " /* constant text in file */
#define HDR_ID_RO 	" ID="		/* ASCII only, not translated */
#define HDR_COMMENT_RO 	"\n Comment: "
#define HDR_SOURCE_RO 	"\n   Source="
#define HDR_SCENE_RO 	"     Scene="
#define HDR_SUBSCENE_RO "  Subscene="
#define HDR_BAND_RO 	"      Band="
#define HDR_DESCRIPION \
	char h_title_ro[HDR_RO_SZ]; 		/* 12 */ \
	char h_title[HDR_TITLE_CHRS * 3 + 1]; 	/* 112 */ \
	char h_id_ro[HDR_RO_SZ]; 		/* 124 */ \
	char h_id[HDR_ID_CHRS * 3 + 1]; 	/* 188 */ \
	char h_comment_ro[HDR_RO_SZ]; 		/* 200 */ \
	char comment[HDR_COMMENT_CHRS * 3 + 1]; /* 396 */ \
	char h_source_ro[HDR_RO_SZ]; 		/* 408 */ \
	char source[HDR_SOURCE_CHRS * 3 + 1];	/* 424 */ \
	char h_scene_ro[HDR_RO_SZ]; 		/* 436 */ \
	char scene[HDR_SCENE_CHRS * 3 + 1]; 	/* 506 */ \
	char cMagic[7];		/* a magic number = "GRSI then vn" for file id \
				 * thus version# is last 2 bytes of the first 512\ 
				 * (see DHEAD_VERSION)\
				 * for this version of hdr, should be 0x506 */\
	char h_subscene_ro[HDR_RO_SZ]; 		/* start at 512; total=524 */ \
	char subscene[HDR_SUBSCENE_CHRS * 3 + 1]; /* 588 */ \
	char h_band_ro[HDR_RO_SZ];  		/* 600 */ \
	char band[HDR_BAND_CHRS * 3 + 1]; 	/* 616 */

/* the following values cannot be changed in any file header 
 * without having to rewrite the image data as well.
 */   
#define HDR_FILE_PARAMS /* 32 bytes */ \
	char h_czFtype[4];	/* 'C'=class. 'I'=image 'L'=layer */ \
                        	/* (use only char[0] of array ) */ \
	UINT32 h_ulWidth; \
	UINT32 h_ulHeight; \
 	UINT32 h_ulBitsPerPix; 	/* allows us to handle multibyte images \
				 * in limited fashion. \
				 * maximum supported is 16 bits/pix */ \
	UINT32 h_ulEncoding;	/* normally 'SR' = standard raster */ \
	UINT32 h_ulIff_offset; 	/* if non-zero, indicates location \
				 * (from start of file) of trailer. */ \
	UINT32 h_ulKey;		/* v 5.4; non-zero => this is a locked file */\
	UINT32 h_ulByteOrder;	/* writer sets to 'A' 'B' 'C' 'D' */

#define HDR_STATS /* 24 + 64 = 88 bytes*/ \
	SINT32 h_ilImgmean;		/* mean value of all image data */ \
	SINT32 h_ilImgmax;		/* max data value in image */ \
	SINT32 h_ilImgmin;		/* min data value in image */ \
	UINT32 h_ulNorm;		/* normalization: \
					 * 0=none,1=default,2=inverse,3=usr*/ \
					/* 4 = equalized, 5 = Gaussian */ \
	UINT32 h_ulUpper;		/* upper bnd for stretch \
					 * if norm == 1, 2, or 3 */ \
	UINT32 h_ulLower;		/* lower bound */ \
	char h_czImgvar[DOUBLE_SZ];	/* variance of all image data  */ \
	char h_czImgsd[DOUBLE_SZ];	/* standard deviation of image data */

#define HDR_UNIT_CHRS 	17        	/* max text chars in name of map unit*/
#define HDR_UNIT_LEN_STR "51"
#define UNITSZ HDR_UNIT_CHRS

#define HDR_SCALING /* 132 + 52 = 184 bytes */\
		/* following are two alternative ways to represent \
		 * the scaling which MAY have been used to scale from \
		 * multibyte to 8-bit data. */ \
	char h_czScaleFactor[DOUBLE_SZ]; /* BINARY or OPTIMAL scaling */ \
	char h_czScaleOffset[DOUBLE_SZ]; /* OPTIMAL scale offset */ \
	char h_czScalingType[4];	 /* 'B', 'O', or \0 */	\
		/* the following give calibration meaning to pixel values */ \
	char h_czZ_scale[DOUBLE_SZ];  /* mult by pixel value to produce z_unit\
				       * - default=1.0 */ \
	char h_czZ_offset[DOUBLE_SZ]; /* calibrated_value \
				       * = (pixvalue+65 z_offset)*z_scale */ \
	char z_unit[HDR_UNIT_CHRS*3+1]; /* name of pixel calibration units */

        /* Structure to allow flexible encoding of map or reference coordinates
	 * including lat/long coordinates. Now we are using only v0.    
	 */
typedef struct hdr_mapcoord_t /* 44 bytes */
    {
    char cz_v0[DOUBLE_SZ];
    UINT32 tag;                 /* reserved */
    SINT32 v1;
    SINT32 v2;
    } HDR_MapCoord; 

#define HDR_PROJECTION_CHRS 33
#define HDR_GEOREF /* 12 + 88 + 64 + 100 + 52 = 306 bytes */ \
	/* georeferencing information \
	 * normally initialized by registration utility \
	 * or via DRAGON HEA operation */ \
	UINT32 h_ulGeoref_init;	/* non-zero if following fields have been init'd*/ \
	SINT32 h_uImg_x;	/* +/- pixel number of origin/fixed point - usually 0*/ \
	SINT32 h_uImg_y;	/* +/- line number of fixed point - usually 0 */ \
	HDR_MapCoord ref_x; 	/* map/reference x coord of fixed point   */ \
	HDR_MapCoord ref_y; 	/* map/reference y coord of fixed point   */ \
	char h_czXcell_size[DOUBLE_SZ];/* size of one cell in X direction at fixed pt */ \
	char h_czYcell_size[DOUBLE_SZ];/* size of one cell in Y direction at fixed pt */ \
			/* if negative, the corresponding axis is reversed \
			 * relative to the image coordinate system. I.e. \
			 * if xcell_size is negative, pixels have smaller  \
			 * x map coordinates as you move from left to right \
			 * if ycell_size is negative, pixels have smaller  \
			 * y map coords as you move from top to bottom */ \
        char czProjection[HDR_PROJECTION_CHRS*3+1]; /* code for map projection -  \
						     * not currently used */ \
	char unitname[HDR_UNIT_CHRS*3+1]; /* map units - null terminated */

#define HDR_SPECTRAL \
	/* Defines spectral characteristics of image band \
	 * Also 'band' is specifically defined to be a band # or 'RED' etc \
	 * czSpectralWidth is ideally the units from Center to the -3db point \
	 * defined but not used in Dragon v 5.8 \
	 */ \
	char czSensor[HDR_SENSOR_CHRS*3+1]; /* 100  bytes */\
	char czSpectralUnit[HDR_UNIT_CHRS*3+1]; /* (52) 'nm' or 'angstrom' */\
	char czSpectralCenter[DOUBLE_SZ]; /* (32) in czSpectralUnit */ \
	char czSpectralWidth[DOUBLE_SZ]; /* (32) in czSpectralUnit */
	/* above is 216 bytes */

#define HDR_HIST_LEN 65      /* elements in header histogram */

/* Added 8/20/06 for maintaining IGC information */
#define HDR_METAFILE_CHRS 128
#define HDR_GUID_CHRS 64
#define HDR_METAFILE \
	char h_metafile[HDR_METAFILE_CHRS];  \
        char h_guid[HDR_GUID_CHRS];
/* above is 306  bytes */

/* Added 8/20/06 for maintaining extent information */
#define HDR_EXTENT \
	char h_czMinX[DOUBLE_SZ_SMALL];/* min X coord defining bounding box */\
	char h_czMinY[DOUBLE_SZ_SMALL];/* min Y coord of bounding box  */ \
	char h_czMaxX[DOUBLE_SZ_SMALL];/* max X coord defining bounding box */\
	char h_czMaxY[DOUBLE_SZ_SMALL];/* max Y coord of bounding box  */
/* above is 160 bytes */

/* added 2011-01-10 for missing GEOTIFF data - also see trailer */
/* At present (v 6.1) these are set only by:
 *   import geotiff, if the data is WGS84 and aligned to map
 *   Dragon REG
 * If NOT set, then Export to geotiff does not set any geotiff tags
 *   except (if cellsize and MapCoord are known)
 *   ModelPixelScaleTag and one tiepoint */
#define HDR_GEOTIFF \
	char h_czDateTime[21]; 	/* yyyy:mm:dd HH:MM:SS */ \
	char h_czUTMZone[5]; 	/* 1-60[N|S] */ \
	BOOL h_bRegistered;       /* is it registered to map coords? */\
		/* The following fields are essentially identical to the \
		 * corresponding georeferencing fields in the Geotiff spec \
		 * (www.remotesensing.org/geotiff/spec) assuming a \
		 * "Projected Coordinate System \
		 * Typically a code value of 0 means the field has not been \
		 * specified or initialized. \
		 */ \
		/* the model type. Only 1 & 2 supported */ \
		/* several tags have different meanings depending on the model value */ \
	UINT16 uModelType;            /* default: 0 = not specified */ \
		/* params Proj... for model type 1 only */ \
		/* params Geo... for model type 2 (geographics lat-long) */ \
	UINT16 uType;      	/* default: 0 = not specified */ \
	/* depending on model: uType is uProjectedCSType or uGeographicType */  \
	UINT16 uCode1; 		/* default: 0 = not specified */	\
	/* depending on model: uCode1 is uProjectedLinearUnits or uGeographicDatum */  \
	UINT16 uCode2;        	/* default: 0 = not specified */ \
	/* depending on model: uCode2 is uProjectionGeo or uGeographicPrimeMeridian */  \
	UINT16 uProjectionCoordTrans; /* default: 0 = not specified */ \
		/* params in case of vertical data */ \
	UINT16 uVerticalType;        /* default: 0 = not specified */ \
	UINT16 uVerticalUnits;       /* default: 0 = not specified */
/* h_czOrientation currently used only as T/F, implies North, for use
 * by viewport and CUR calculation of cursor position */	 
/* above is 28 bytes */

typedef union		/* DRAGON image file header */
    {
    char buffer[DHEAD];	
    struct
	{
	HDR_DESCRIPION			/* 616 bytes */
	HDR_FILE_PARAMS  		/* +32 bytes  =  648 */
	HDR_STATS 			/* +88 bytes  =  736 */
	HDR_SCALING			/* +184 bytes =  924 */
	HDR_GEOREF			/* +306 bytes = 1230 */
	UINT32 histo[HDR_HIST_LEN]; 	/* +260 bytes = 1490 */
			       /* image histogram: 
				* 0'th elt. is total count.
				* others are binned in fours
				* i.e. each elt. 1 to 64 holds total 
				* count for four data values  */
	    		       /* NOTE: bin size will be > 4 for 
				* images with more than 8 bits/pix */
	HDR_SPECTRAL			/* +216 bytes = 1506 */
	HDR_METAFILE			/* +306 bytes = 1812 */
	HDR_EXTENT			/* +160 bytes = 1972 */
	HDR_GEOTIFF			/* +28 bytes = 2000 */
	// ~~~ need to preserve UTM zone 1-60[NS]
	} fields ;	/* for accessing individual fields */
    } DRAGON_HEAD ;

/*========================================================================
 *
 * Structure of image file trailer
 *
 * Introduced in Dragon v5.4, but not initially used much
 *
 *========================================================================
 *
 * The trailer is an optional binary block appended to the image file
 * following the data section. 
 * If present, the header field iff_offset mut be set
 * The trailer consists of a number of 'records', in a predefined sequence.
 * The number of records may grow with subsequent revisions, and almost
 *  all have non-required values, but all known records must be included,
 *  and in the predefined sequence. 
 *
 * Each record consists of a 'preamble' plus, optionally, a 'body'.
 * All preambles are of fixed size and appear first in the trailer,
 *  followed by the bodies in any sequence and of any length. The structure
 *  of the body is entirely determined by the record identity.
 *========================================================================*/

typedef struct PREAMBLE_t
    {
    char czName[24];	/* optional, for display. Ascii */
    UINT32 uOffset;	/* depends on TRAILER_RECORD type,
			 * but by convention is offset to payload
			 * or: 0 => no payload */
    UINT32 uSize;	/* size of payload if any */
    UINT32 uArg;	/* depends on TRAILER_RECORD type */
    UINT32 uArg1;	/* 0 if this preamble not used, 1 if it is
			 * except for TR_LABEL: uColorNdx */
    char czArg2[8];	/* only for TR_LABEL: I18N key string */
    } PREAMBLE_T;

enum TRAILER_RECORDS
    {
    TR_TRAILER_SIZE,	  /* 'uArg' is byte count of trailer, all inclusive */
    TR_TRAILER_RECCOUNT,  /* 'uArg' lowword is number of records in trailer
			   *        highword is value of TR_LAST_RECORD */
    TR_TRAILER_VERSION,   /* 'uArg' is DHEAD_VERSION */
    TR_HEADER_CHECKSUM,	  /* 'uArg' is unsigned 32-bit checksum of header */
    TR_DATA_CHECKSUM,	  /* 'uArg' is unsigned 32-bit checksum of img data */
    TR_TRAILER_CHECKSUM,  /* 'uArg' is unsigned 32-bit checksum of trailer,
			   *         EXCLUDING the checksum itself */
    TR_COLORFILENAME,	  /* 'uOffset' is offset from start of file
			   *         to UTF-8 name of file,
			   *         or 0
			   * 'uArg' == 1 => valid
			   * 'uSize' is strlen+1 */
    TR_PALETTE,		  /* 'uOffset' is offset to array of 32-bit colors,
			   * 'uArg' is count of entries */
    TR_ORIGIN,		  /* 'uOffset' is offset to original name of file,
			   * 'uArg' low 16 bits is band count high 16 bits is selected band */
    TR_LABELCOUNT,	  /* 'uArg' is how many label records there are 
			   * 'uOffset' is offset to label preambles */
    TR_TIEPOINTS,	  /* 'uArg' is how many tiepoint records
			   * 'uOffset' is offset to the first 
			   * (2 uint and 2 double each)*/
    TR_LINESBLOB,	  /* 'uArg' is size of entry
			   * 'uOffset' is offset to LinesBlob */
    TR_LAST_RECORD,	  /* keep at end of list (but before TR_LABEL) */
    TR_LABEL		  /* 'uOffset' is offset to UTF-8 string,
			   * 'uArg' is classnum, 
			   * 'uArg1' is color 
			   * 'czArg2' is I18N key */
    };

/* the values which should be in czName */
#define TRAILER_RECORD_NAMES \
    "TR_TRAILER_SIZE", \
    "TR_TRAILER_RECCOUNT", \
    "TR_TRAILER_VERSION", \
    "TR_HEADER_CHECKSUM", \
    "TR_DATA_CHECKSUM", \
    "TR_TRAILER_CHECKSUM", \
    "TR_COLORFILENAME", \
    "TR_PALETTE", \
    "TR_ORIGIN", \
    "TR_LABELCOUNT", \
    "TR_TIEPOINTS", \
    "TR_LINESBLOB", \
    "TR_LAST_RECORD", \
    "TR_LABEL"

    /* can use this structure for WRITING, 
     * but for reading only with care (since
     * size of array is unknown until partially read).
     */
typedef struct TRAILER_t
    {
    PREAMBLE_T record[TR_LAST_RECORD+1];
    } TRAILER_T;

	/* TRAILER_T is followed by a number of TR_LABEL headers 
	 * specified by TR_LABELCOUNT
	 */

#endif /* DRAGONHD_H */
