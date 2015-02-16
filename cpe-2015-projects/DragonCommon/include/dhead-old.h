/****************************************************************
 *	DHEAD-OLD.H - structure for DRAGON image header
 *          $Revision: 1.12 $	$Date: 2014/12/05 09:58:46 $
 *
 *          ~~ Copyright 1986-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: dhead-old.h,v 1.12 2014/12/05 09:58:46 rudahl Exp $
 *	$Log: dhead-old.h,v $
 *	Revision 1.12  2014/12/05 09:58:46  rudahl
 *	no differences between DragonProf and OpenDragon
 *
 *	Revision 1.11  2005/01/30 01:31:54  rudahl
 *	moved, copied structs to img.h
 *
 *	Revision 1.10  2005/01/27 23:03:15  rudahl
 *	adapt for 64-bit
 *	
 *	Revision 1.9  2005/01/27 21:37:44  rudahl
 *	now requires dragonHd.h
 *	
 *	Revision 1.8  2005/01/04 15:55:48  rudahl
 *	renamed from dhead.h; revised trailer
 *	
 *	Revision 1.7  2004/12/28 12:18:30  rudahl
 *	added UTF-8 text fields to trailer
 *	
 *	Revision 1.6  2002/08/30 20:34:28  rudahl
 *	elaborated some docs
 *	
 *	Revision 1.5  2002/05/08 00:11:09  rudahl
 *	new version; new fields
 *	
 *	Revision 1.4  2002/05/03 00:33:56  rudahl
 *	added trailer defns
 *	
 *	Revision 1.3  2002/04/09 21:33:31  rudahl
 *	update copyright date
 *	
 *	Revision 1.2  2001/10/01 19:13:17  rudahl
 *	added packing statement for WIN, GCC
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:18  rudahl
 *	first checkin of only SOME common dirs
 *	
 * Revision 4.5  1998/03/05  08:54:00  tower
 * checkin for class class5_0
 * 
 * Revision 4.4  1998/03/05  08:54:00  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1998/03/05  08:54:00  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1998/03/05  08:54:00  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/12/19  11:56:30  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/11/21  21:28:22  tower
 * final for DRAGON 4.0G.
 * general changes: MSC v 6 adaptations, graphics screens to 1280 pix.
 *
 *
 *****************************************************************
 *	Old form of DHEAD, renamed so we can convert old files
 *
 *		data types are little-endian, 80x86 format
 *		char = 1 byte
 *		short = int = 2 bytes
 *		long = 4 bytes
 *		double = 8 bytes
 *
 *****************************************************************
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
 *	1/19/98 ktr	Revised for version 5.0: added fields:
 *			 czProjection,uScaleFactor,dScaleFactor,dScaleOffset
 * 5.4	5/1/2002 ktr	added definition and documentation for trailer
 *	12/27/2004 ktr	added COMMENT, SCENE etc to trailer in utf8
 *			(not yet used by Dragon)
 * 5.5	2004-12-31 ktr	converted to be old form of DHEAD, 
 *			renamed so we can convert old files
 */

/*	NOTE (Dragon v5.4.4)
 *		except for classnames, all text fields in header are
 *		assumed to be UTF-8
 */

#ifndef DHEAD_OLD_H
#define DHEAD_OLD_H	/* signal this file has been loaded */
#if defined  _WIN32 || defined MSC || defined __GCC__
#pragma pack(1)
#endif

#define DHEAD_OLD_VERSION	0x500

#define DHEAD 2048
#define UNITSZ_OLD UNITSZ-1  /* max text chars in name of map unit  */
#define HDR_HIST_LEN 65      /* elements in header histogram */

#define NUMLABELS 18	     /* permitted number of class names */
	/* class name params prior to v 4.1 */
	/* these must be maintained for the union in IHEAD */
#define CLASS_NAMESZ 10	     /* biggest permitted class name in hdr */

	/* class name params for v 4.1 */
#define EXT_CLASS_NAMESZ 32  /* this is wchar not char; class name size */
#define WCHAR_SZ sizeof(UNICODE_WCHAR)

#define SCALAR_STATS_FIELDS   \
    double imgvar;		/* image data variance   */ \
    double imgsd;		/* image data standard deviation */ \
    unsigned short imgmean;	/* image data mean value */ \
    unsigned short imgmax;	/* maximum value in img  */ \
    unsigned short imgmin;	/* minimum value in img  */

typedef struct
    {
    double v0;
    ushort tag;                 /* reserved */
    SINT32 v1;
    SINT32 v2;
    } MapCoord_old;         /* Structure to allow flexible encoding */
			/* of map or reference coordinates      */
			/* including lat/long coordinates. Now  */
			/* we are using only the v0 portion.    */

typedef struct	/* class names, each with 2 term. NULL */
	{
	char name[WCHAR_SZ * EXT_CLASS_NAMESZ+2];
	} EXT_CLASS_NAME; 

typedef struct	/* pre-v 4.1 class names, each with length & term. NULL */
	{
	char length;
	char name[CLASS_NAMESZ+1];
	} OLD_CLASS_NAME;

typedef union		/* DRAGON image file header */
    {
    char buffer[DHEAD];	
    struct
	{
	ushort size[2];	/* rows & cols (y then x) in this image */
	char fnlen;	/* length byte for file name */
	char fname[17];	/* file name.ext */
	char ftype[2];	/* 'C'=class. 'I'=image 'L'=layer */
                        /* (don't use second byte of array ) */
 	ushort bits_per_pix; /* allows us to handle multibyte images */
			/* in limited fashion. Only used if vn == 41 */
			/* maximum supported is 16 bits/pix */
	char pad1[10];
	ushort uEncoding; /* normally 'SR' = standard raster */
	UINT32 iff_offset; /* if non-zero, indicates location */
			/* (from start of file) of trailer. */
			/* Field added in V3.05, trailer in 5.4.  */
	ushort imgmean;	/* mean value of all image data     */
	double imgvar;	/* variance of all image data       */
	ushort resvd1;	/* reserved */
	double imgsd;	/* standard deviation of image data */
  	ushort resvd2;	/* reserved */
	ushort imgmax;	/* max data value in image */
	ushort imgmin;	/* min data value in image */
	UINT32 histo[HDR_HIST_LEN]; /* image histogram: 0'th elt. is total */
			/* binned in fours, i.e. each elt. 1 to 64 */
			/* holds total count for four data values  */
			/* NOTE: bin size will be > 4 for images with */
			/* more than 8 bits/pix */
	ushort norm;	/* normalization: 0=none,1=default,2=inverse,3=usr*/
			/* 4 = equalized, 5 = Gaussian */
	ushort upper;	/* upper bnd for stretch if norm == 1,2, or 3 */
	ushort lower;	/* lower bound */
	char source[5];	/* first is string length, last is NULL */
	char pad3[5];
	char scene[18];	/* scene ID, with string length & NULL */
	char pad4[4];
	char subscene[18]; /* subscene ID, with string length & NULL */
	char pad5[4];
	char band[5];	/* band "number", with string length & NULL */
	char pad6[3];
	char comment[48]; /* comment field, with string length & NULL */
	char pad7[2];
	ushort uKey;	/* v 5.4; non-zero => this is a locked file */
	char clf[18];	/* color file name, with string length & NULL */
		/* beginning with v 5.0, this replaces 'projection' */
        char projlen2;   /* length of string in 'projection2' */
        char czProjection[21]; /* code for map projection - not currently used */
			       /* max 20 chars plus terminating NULL */
		/* following are two alternative ways to represent
		 * the scaling which MAY have been used to scale from
		 * multibyte to 8-bit data. For version 5.0 and above only.
		 * Only ONE of uScaleFactor/dScaleFactor may be non-zero */
	ushort uScaleFactor;	/* BINARY scaling used, or 0 */
	double dScaleFactor;	/* OPTIMAL scale factor or 0.0 */
	double dScaleOffset;	/* OPTIMAL scale offset, or 0.0 */
	char cMagic[4];		/* a magic number = "GRSI" for file id */
	ushort vn;	/* version# is last 2 bytes of the first 512 */
			/* (see DHEAD_VERSION) */ 
			/* for this version of header, should be 0x500 */
			/** modified, SEG, 4/24/94 **/

		/* 
		 * next four fields relate to the actual 'class' name strings,
		 * which can (potentially) bi in an image file of any type.
		 */
	UINT32 clsname_offset;
			/* if initialized, location of start of classname */
			/* array  - for future extensibility */
	ushort class_namesz;	/* max permited class name length (wchars) */
	ushort numlabels;	/* actual number of class names in this file;
				 * however older files used this as max count*/
	ushort charsize;	/* sizeof(char) or sizeof(wchar) (1 or 2) */
		/* number of actual, including mixed, classes
		 * in a type 'C' file, 0r 0 */
	ushort numclasses;	/* number of classes */ 
	char resvd[8];		/* byte 524-561 */
	char clstab[128]; 	/* reserved for use by DRAGON */
	union
	    {
	    EXT_CLASS_NAME extname[NUMLABELS];	/* class names, Unicode format */
	    OLD_CLASS_NAME oldname[NUMLABELS];	/* pre-v 4.1 class names */
	    } dclass;
	struct LABELINFO_t	/* info about each 'dclass' label */
	    {
	    ushort uValue;	/* for each 'extname' or 'oldname', 
				 * the corresponding image data value.
				 * For a 'C' file, this is the class#*/
	    byte uColorNdx;	/* palette index - not yet used */
	    char cKeyChar;	/* if != '\0', is suffixed to %h4600.
				 *   to form I18N key for name */
	    } LabelInfo[NUMLABELS];
//	char pad8[1060 - 2*sizeof(double) 
//		 - NUMLABELS * sizeof(struct LABELINFO_t)
//		 -((sizeof(EXT_CLASS_NAME)-sizeof(OLD_CLASS_NAME))*NUMLABELS)];
		/* the following give calibration meaning to pixel values */
	double z_scale;	/* mult by pixel value to produce z_unit - default=1.0 */
	ushort resvd5;	/* reserved - p/o z_scale */
	double z_offset; /* calibrated_value = (pixvalue+65 z_offset)*z_scale */
	ushort resvd6;	/* reserved - p/o z_offset */
	char z_unitlen;	
	char z_unit[UNITSZ_OLD+1]; /* name of pixel calibration units-default="" */
	/* georeferencing information - starts at byte 1968 */
	/* normally initialized by registration utility */
	/* or via DRAGON HEA operation */
	ushort georef_init; /* non-zero if following fields have been init'd*/
	short img_x;	/* +/- pixel number of origin/fixed point - usually 0*/
	short img_y;	/* +/- line number of fixed point - usually 0 */
	MapCoord_old ref_x; /* map/reference x coord of fixed point   */
	MapCoord_old ref_y; /* map/reference y coord of fixed point   */
	double xcell_size;/* size of one cell in X direction at fixed pt */
	ushort resvd3;	/* reserved */
	double ycell_size;/* size of one cell in Y direction at fixed pt */
			/* if negative, the corresponding axis is reversed*/
			/* relative to the image coordinate system. I.e. */
			/* if xcell_size is negative, pixels have smaller */
			/* x map coordinates as you move from left to right*/
			/* if ycell_size is negative, pixels have smaller */
			/* y map coords as you move from top to bottom */
	ushort resvd4;	/* reserved */
	char unlen;     /* length of unitname ... */
	char unitname[UNITSZ_OLD+1]; /* map units - null terminated */
        char projlen;   /* length of string in 'projection' */
		/* beginning with v 5.0, this is replaced by 'czProjection' */
        char projection[9]; /* code for map projection - not currently used */
                        /* max 8 chars plus terminating NULL */
	} fields ;	/* for accessing individual fields */
    } IHEAD_OLD ;


#if defined  _WIN32 || defined MSC || defined __GCC__
#pragma pack()
#endif

#endif
