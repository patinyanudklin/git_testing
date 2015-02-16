/*
 *	filename foreign.h
 *		$Id: foreign.h,v 1.6 2015/01/21 10:39:37 rudahl Exp $
 *
 *      ~~ Copyright 2001-2015 Kurt Rudahl and Sally Goldin
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
 *
 *	headers for various kinds of foreign image files
 *	this file must be invoked AFTER TIFF.H ,if that file is used	
 *	k. rudahl -- 2/18/89, originally for use by FCONVERT
 *		6/89 ktr added sturcture for OSU-MAP 3.0 beta version
 *		10/10/90 ktr added ifndef TIFF_H around TAGS_AY
 *              1/26/91 seg added ERD74HEAD, to handle ERDAS version 7.4
 *		12/20/91 ktr changed ERDHEAD to include a union avoiding
 *			need for 2 separate header structures
 *	7/19/94 	missing #endif at end
 *      11/04/94  seg   Updated with new ERDAS fields
 *	7/8/95    ktr	added Windows bitmap (BMP, DIB) structure
 *			typedefs, inspired by windows.h
 */

#ifndef FOREIGN_H
#define FOREIGN_H
	/* header structure for agroclimatic channel files */
	/*** this is old structure - new one follows **** 5/28/89 */
typedef struct 
	{	 /* obtained from brief descr. in docs & use of debug */
	char ftype[4];	/* file type - don't know use */
	char days[3];   /* how many in sample */
	char julstrt[6],julend[6]; /* julian start,end dates */
	char leftd[4],leftm[3],lefts[3],leftc; /* left longtitude */
	char rightd[4],rightm[3],rights[3],rightc; /* right longtitude */
	char botmd[3],botmm[3],botms[3],botmc; /* botm latitude */
	char topd[3],topm[3],tops[3],topc; /* top latitude */
	char equator[6]; /* ok, what is it? */
	char nchan[2];	 /* num. channels (bands) in file */
	char cha[2],chb[2],chc[2],chd[2],che[2]; /* which ones? */
	char nbytes[5],nrec[4],npix[5]; /* bytes/rec, # rec, pix/rec */
	char col0[4],coln[4],row0[4],rown[4]; /* fortran, so origin=1,1 */
	char comment[22];
	char dummy[512-131];	/* filler */
	} 
	AGHEAD ;  /* numeric values are decimal ascii, rt-just., blank-fill */					     

	/* NEW header structure for agroclimatic channel files */   
	/* inferred from code sent by NOAA - 5/28/89	*/
typedef struct 
	{	 /* obtained from brief descr. in docs & use of debug */
	char ftype[4];	/* file type - don't know use */
	char days[3];   /* how many in sample */
	char julstrt[6],julend[6]; /* julian start,end dates */
	char leftd[4],leftm[3],lefts[3],leftc; /* left longtitude */
	char topd[3],topm[3],tops[3],topc; /* top latitude */
	char rightd[4],rightm[3],rights[3],rightc; /* right longtitude */
	char botmd[3],botmm[3],botms[3],botmc; /* botm latitude */
	char pixpdeg[4]; /* pixels per degree */
	char nchan[3]; /* vars per pix = number of channels? */
        char varcodes[10][3]; /* codes for vars 1 through 10 */
        char varsprow[6];
        char bytespvar[2]; 				    
        char nrec[5];    /* number of rows */
        char npix[5];    /* number of pix/rec */
	char col0[5],coln[5],row0[5],rown[5]; /* fortran, so origin=1,1 */
 	char npasses[2]; /* num. of satellite passes */
	char skip[2];   /* blank? */
	char comment[28]; /* description of location */
	char dummy[512-168];	/* filler */
	} 
	NEWAGHEAD ;  
         /* numeric values are decimal ascii, rt-just., blank-fill */					     

	/* header for ERDAS files */
typedef struct
	{
	char hdr[6];	/* always = "HEADER" for 7.3, "HEAD74" for 7.4 */
	short pack;	/* 0 => 8-bit data, 2 => 16-bit data */  
	short nband;	/* # bands */
	char dummy1[6];
	union
 	    {
	    struct 
		{
		float ncol,nrow; /* # rows, columns in file */
		float x0,y0;	/* upper left coord, always 1.0 */
		char dummy2[56];
		short maptyp;	/* always 99 (except sometimes) */
		short nucls;	/* num of classes, always 255 (8-bit), x7FFF (16-bit) */
		char dummy3[20];
		float mapx0,mapy0; /* upper left map coords */
		float xsize,ysize; /* cell size */

		} E73; 	/* Erdas version 73 and earlier */
	    struct
		{
		long ncol,nrow; /* # rows, columns in file */
	        long xleft,yleft; /* upper left coords in "user-defined" coords */
        	char dummy2[56];
	        short maptyp; 
                short nucls; 
   	        char dummy3[20];
		float mapx0,mapy0; /* upper left map coords */
		float xsize,ysize; /* cell size */
		} E74; 	/* Erdas version 74 */
	    } size;
	}
	ERDHEAD ; /* values are little-endian */

	/* header for ERDAS Release 7.4 files */
typedef struct
	{
	char hdr[6];	/* always = "HEAD74" */
	short pack;	/* 0 => 8-bit data, 2 => 16-bit data */  
	short nband;	/* # bands */
	char dummy1[6];
	long ncol,nrow; /* # rows, columns in file */
	char dummy2[104]; /* don't know anything else yet! */
	}
	ERD74HEAD ; /* values are little-endian */

        /* header for EPPL-7 files */
typedef struct
        {  
        short frow;   /* first row index  - assume 0 by us */
        short lrow;   /* last row index - assumed numrows -1 by us */
        short fcol;   /* first column index */
        short lcol;   /* last column index  */
        char fry[8];  /* first row coordinate - e.g. in lat long? */
        char lry[8];  /* last row coordinate */
        char fcx[8];  /* first column coord */
        char lcx[8];  /* last column coord  */
        short precise; /* data precision - always 8 */
        short base;   /* base value - EPPL7 adds to all values before scaling*/
	short scale;  /* scaling factor - 100 = 1.00 */
        short offsite; /* value to be interpreted as non-data; -1 if none */
        char dummy1[24];
        char datemade[16]; /* creation date, any format */
        char timemade[8];  /* creation time, any format */
        char comment[32];  /* remark string */
        }				  
        EPPL7HEAD;  /* little-endian - EPPL7 runs only on PC's */

/*
 *	Definitions necessary for WF pgms compiled under
 *	Lattice C 3.3 to access TIF functions 
 *	-- fns defined in TIFTAGS etc
 */

#ifndef TIFF_HPP	/* these are defined in TIFF.H */

#define MAXTAG  301     /* highest known tag value */

typedef struct
	{
	long val[MAXTAG-254];
	int  flag[MAXTAG-254];
	}
	TAGS_AY;

int ReadTags();       /* read specified file for tags, into
 		       * a TAGS_AY structure. In TIFTAGS */

#define IMAGE_WIDTH_TAG		0x0100
#define IMAGE_LENGTH_TAG	0x0101
#define BITS_PER_SAMPLE_TAG	0x0102 /* 8 */
#define COMPRESSION_TAG		0x0103 /* 1 = uncompressed */
#define STRIP_OFFSETS_TAG	0x0111 /* = header size */
#define SAMPLES_PER_PIXEL_TAG	0x0115 /* 1=mono, 3=color */
#define STRIP_BYTE_COUNTS_TAG	0x0117 /* =length x width in single-strip */
#define PLANAR_CONFIG_TAG	0x011c /* 1 */
extern char creator;	/* 'M' or 'I' for TIF */
#endif

/*
 *	OSU-MAP 3.0 beta version header
 */

typedef char rname[16];
 
typedef struct
    {
    rname region_name[100];
    char status;		/* 'P'=protected, 'E'=exposed */
    char dummy1[63];
    int ove_scale;
    char dummy2[126];
    long rows,columns,scale;
    char dummy3[116];
    char narrate[1920];
    }
    OSU_HEAD ;

/******************************************************************
 *
 *   following structures etc are for MS-Windows compat. bitmap
 *   files. Typically, a file contains
 *       a BITMAPFILEHEADER
 *       a BITMAPINFOHEADER (with NO RGB-quads)
 *       0 or more RGB quads, as needed
 *       the data, in RGB triple form. There may be alignment issues
 *          on successive lines of data.
 *
 *	BITMAPCOREINFOHEADER is obsolete, and maintained here in case
 *	we need it someday.
 *
 *******************************************************************/

/* Bitmap Header structures */
typedef struct tagRGBTRIPLE
    {
    byte    rgbtBlue;
    byte    rgbtGreen;
    byte    rgbtRed;
    }  RGBTRIPLE;

typedef struct tagRGBQUAD
    {
    byte    rgbBlue;
    byte    rgbGreen;
    byte    rgbRed;
    byte    rgbReserved;
    } RGBQUAD;

/* structures for defining DIBs */
typedef struct tagBITMAPCOREHEADER
    {
    ulong   bcSize;
    short   bcWidth;
    short   bcHeight;
    ushort  bcPlanes;
    ushort  bcBitCount;
    } BITMAPCOREHEADER;    /* obsolete - don't use */

typedef struct tagBITMAPINFOHEADER
    {
    ulong   biSize;		/* size in bytes of this structure */
				/* (biSize includes any RGB quads?) */
    long    biWidth;		/* image width in pixels */
    long    biHeight;		/* image height in rows */
    ushort  biPlanes;		/* 1 */
    ushort  biBitCount; 	/* bits deep: 8 or 24 for DRAGON for Win 3.1 */
    ulong   biCompression;  	/* see below. Use BI_RGB for 24-bit */
    ulong   biSizeImage;	/* total bytes of image data */
    long    biXPelsPerMeter;	/* usually 0 */
    long    biYPelsPerMeter;	/*   "       */
    ulong   biClrUsed;		/*   "       for 24-bit files */
    ulong   biClrImportant;	/*   "                        */
    } BITMAPINFOHEADER;

/* constants for the biCompression field */
#define BI_RGB      0L
#define BI_RLE8     1L
#define BI_RLE4     2L

typedef struct tagBITMAPINFO
    {
    BITMAPINFOHEADER bmiHeader;
    RGBQUAD	     bmiColors[1]; /* or 0 for true color */
    } BITMAPINFO;

typedef struct tagBITMAPCOREINFO
    {
    BITMAPCOREHEADER bmciHeader;
    RGBTRIPLE	     bmciColors[1];
    } BITMAPCOREINFO;   /*  obsolete - don't use */

typedef struct tagBITMAPFILEHEADER
    {
    ushort  bfType;	/* see signatures below */
    ulong   bfSize;	/* total size of file in bytes */
    ushort  bfReserved1; /* normally 0 */
    ushort  bfReserved2; /* normally 0 */
    ulong   bfOffBits;	/* byte offset in file to start of image data */
    } BITMAPFILEHEADER;

typedef struct tagBMP_HEAD
    {
    BITMAPFILEHEADER filehdr;
    BITMAPINFOHEADER info;
    } BMP_HEAD;

/*
 * structure for reading/writing BIL-ESRI metadata file
 * Extracted from rosetta.h
 * plus some examples.
 * Not all of these fields may exist in all files;
 * however, at a minimum we need  nrows, ncols, nbands
 */

#define BIL_STR_SIZE 32
/* structure for values in the arc/info style BIL file format header */
typedef struct bil_info  
        {
	char comment[256];
        char byteorder[BIL_STR_SIZE];	/* default "I" */
        char layout[BIL_STR_SIZE];	/* default "BIL" */
        char mapunits[BIL_STR_SIZE];	/* default "METERS" */
        char nrows[BIL_STR_SIZE];	/* required */
        char ncols[BIL_STR_SIZE];	/* required */
        char nbands[BIL_STR_SIZE];	/* required */
	char nbits[BIL_STR_SIZE]; 	/* default = 8 */
	char band_bytes_per_row[BIL_STR_SIZE];	/* default cols*nbits/8 */
        char tot_bytes_per_row[BIL_STR_SIZE];	/* default band_bytes_per_row*nbands */
	char xdim[BIL_STR_SIZE];	/* default 1 */
	char ydim[BIL_STR_SIZE];	/* default 1 */
	char ulxmap[BIL_STR_SIZE];	/* no default */
	char ulymap[BIL_STR_SIZE];	/* no default */
#ifdef NOMORE
        uint nrows;			/* required */
        uint ncols;			/* required */
        uint nbands;			/* required */
	uint nbits;  	 	 	/* default = 8 */
	uint band_bytes_per_row;	/* default cols*nbits/8 */
        uint tot_bytes_per_row;		/* default band_bytes_per_row*nbands */
	uint xdim;			/* default 1 */
	uint ydim;			/* default 1 */
	double ulxmap;			/* no default */
	double ulymap;			/* no default */
#endif
        } BIL_INFO;

#define BIL_INFO_FIELDS \
	"COMMENT", \
        "BYTEORDER", \
	"LAYOUT", \
	"MAPUNITS", \
	"NROWS","NCOLS",\
	"NBANDS","NBITS",\
        "BANDROWBYTES","TOTALROWBYTES",\
	"XDIM","YDIM", \
	"ULXMAP","ULYMAP"

#define BIL_INFO_SIZES \
	256, \
	BIL_STR_SIZE, \
	BIL_STR_SIZE, \
	BIL_STR_SIZE, \
	BIL_STR_SIZE, BIL_STR_SIZE, \
	BIL_STR_SIZE, BIL_STR_SIZE, \
	BIL_STR_SIZE, BIL_STR_SIZE, \
	BIL_STR_SIZE, BIL_STR_SIZE, \
	BIL_STR_SIZE, BIL_STR_SIZE
//	sizeof(uint),sizeof(uint), 
//	sizeof(uint),sizeof(uint),
//	sizeof(uint),sizeof(uint), 
//	sizeof(uint),sizeof(uint), 
//	sizeof(double),sizeof(double)

#if !defined BFT_ICON
/* Header signatutes for various resources */
#define BFT_ICON   0x4349   /* 'IC' */
#define BFT_BITMAP 0x4d42   /* 'BM' */
#define BFT_CURSOR 0x5450   /* 'PT' */
#endif

#endif
