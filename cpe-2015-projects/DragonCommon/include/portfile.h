/*
 *	filename PORTFILE.H
 *		$Revision: 1.7 $ $Date: 2014/12/05 11:51:02 $	
 *      ~~ Copyright 1995-2014 by Kurt Rudahl and Sally Goldin
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
 *   $Log: portfile.h,v $
 *   Revision 1.7  2014/12/05 11:51:02  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.6  2008/04/06 03:19:42  rudahl
 *   notes on formats
 *
 *   Revision 1.5  2008/01/20 02:08:47  rudahl
 *   more useful description
 *
 *   Revision 1.4  2005/01/29 16:41:23  rudahl
 *   added pragma pack, but doesn't seem to work
 *
 *   Revision 1.3  2005/01/26 01:50:10  rudahl
 *   added INF_TYPE etc
 *
 *   Revision 1.2  2002/01/30 13:06:55  rudahl
 *   added DL_STYLE_ANN
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:18  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 1.3  1998/01/02  12:17:12  tower
 * checkin for class class5_0
 * 
 * Revision 1.2  1998/01/02  12:17:12  tower
 * checkin for class CLASS5_0
 * 
 * Revision 1.1  1996/04/28  04:53:54  lcd
 * checkin for class class49
 * 
 * Revision 1.1  1995/07/24  18:03:20  lcd
 * Initial revision
 * 
 *
 ****************************************************************
 *
 *	Defines data structures used by DRAGON-related software,
 *      to create files which are portable across platforms.
 *      The initial use is for writing temp. files by DGRAPH to
 *      be read by the MS Windows image display component of
 *      DRAGON 5.0
 *
 *	This file depends on the correct length for UINT16 & UINT32,
 *	etc. The macros CHECKSCALARSIZES() and ASSERTSCALARSIZES()
 *      test this.
 *
 *	The macro BIGENDIAN() returns FALSE if the MSB of a UINT32
 *	is higher in memory than the LSB.
 *
 *	Revision History
 * 1.0	7/15/95	ktr	Created
 *	8/7/95		Added chunk and opcode defns for graphics & 
 *			report chunks.
 *	8/1/97 ktr	added DL_POLYLINE and DL_EVENT
 *	10/13/98 ktr	added uExtra2 to CH_INFO to resolve packing issues
 * 5.5	2005-1-28 ktr	added pragma pack(1) for GCC
 */
#ifndef PORTFILE_H
#define PORTFILE_H

#if defined __cplusplus
extern "C" {
#endif

#define CHECKSCALARSIZES() /* return TRUE if UINT16 & UINT32 are what */ \
			   /* they should be */ \
    ((sizeof(UINT16)==2) && (sizeof(UINT32)==4))

#define ASSERTSCALARSIZES() assert(CHECKSCALARSIZES)

#define BIGENDIAN() \
    ((* (byte *) &0xFFFFFF00L) > 1)

#define CHUNK_NAME_SZ 12
#define CH_FMSIZE 128 - CHUNK_NAME_SZ - 5*sizeof(UINT32)
	/* need an independent filename size to assure portability */
#define DI_NAME_SZ 32	/* name for image in CH_DISPIMG */

	/* the following is bytewise compatible with, and functionally
	 * a superset of, MS Windows 3.1 bitmap file header.
	 * i.e. fns which can read this can interpret it as a BMP etc
	 *      header if desired, or may be able to read and use
	 *	Windows BMP etc files.
	 *
	 * A chunk file normally will be structured as:
	 *   	CHUNK_FILE_HDR  (the one and only)
	 *	CHUNK_HDR1      (pointing to CHUNK1, forward=HDR2)
	 *	CHUNK1          (the chunk data, of varying structure & size)
	 *      { more HDR, DATA pairs }
	 *      { image data }  (preceeded by a CH_DISPIMG chunk)
	 *      { more HDR, DATA pairs }
	 *	CHUNK_HDRlast   ( points nowhere)
	 *	(trailer chunks can be appended to or removed from file
	 *      after the initial creation/display)
	 */
typedef struct CHUNK_FILE_HDRtag
    {
    UINT16 uType;	/* file type signature: for us = CH */
			/* for MS windows, see signatures below */
    UINT32 ulSize;	/* total size of file in bytes */
			/* this may become obsolete with appends - ignore */
    UINT16 uFlags;	/* normally 0;
			 * bit 0 set => scale-to-fit VP
			 *   (scaling is required for INFO files (which contain
			 *   no images); at present; assume preserve aspect rat
			 * bit 1 set => use "file" in memory pipe, not this one
			 */
    UINT16 uVersion; 	/* normally 0x500; initially 0x490 */
    UINT32 ulTotChunkSize;
			/* for us: size of init part of file which includes */
			/* this header plus initial chunk headers & chunks */ 
			/* trailer chunks and image data not included */
			/* However, it is also permitted for CHUNK_FILE_HDR
			 *  to be at END of file, in which case this field
			 * does NOT include this structure
			 * MS - bfOffBits: byte offset in file to start
			 *   of image data */
    } CHUNK_FILE_HDR ; /* one of these at start or end of file */

typedef struct CHUNK_HDRtag
    {
    UINT32 ulHdrSize;	/* size of this structure */
    UINT32 ulSize;	/* size of chunk it describes - may be 0 */
    SINT32 lOffset;	/* offset in file of chunk data - (might be negative?) */
    UINT32 lNxtOffset;	/* offset in file of next chunk hdr - 0 => none */
    char cChunk[CHUNK_NAME_SZ]; /* name of (WF?) fn which can understand this*/
    char cFile[CH_FMSIZE]; /* name of file containing hdr & chunk */		
    UINT32 ulTimeStamp; /* when chunk was created, more or less */
    } CHUNK_HDR ;	/* any number of these within file, describing chunks*/

	/* for this chunk, cChunk = "DISPIMG-24" */
typedef struct CH_DISPIMGtag
    {
    UINT32 ulSize;		/* size of this structure */
    UINT16 uPix,uLines;		/* dimensions of image */
    UINT32 ulSizeImage;		/* size of image: total bytes img data in file*/
    UINT32 ulOffset;		/* abs. offset in file where image is */
	/* if image data arranged on disk in blocks or tiles,
	 * how is it arranged ? */
    UINT16 uTilesW,uTilesH;	/* if non-tiled, = 1,ulLines */
    UINT16 uTilePix,uTileLn;	/*  "    "       = ulPix,1 */      
    UINT32 ulTileRowBytes;	/* for MSWin, must be mult of 4 */
    char cImage[DI_NAME_SZ];
    } CH_DISPIMG ;

	/* an INFO chunk consists of the following structs packed together
	 * into a 4K block ending with either a DL_END (=> no more)
	 * or DL_CONTINUE (=> there is another INFO chunk, including another
	 * CHUNK_HDR.
	 * The CH_INFO is 16 bytes long unless cStr or uShrt is bigger; in any
	 * case it MUST be a multiple of 4 bytes
	 */

typedef enum
    {
    DL_END,		/* => this is final CH_INFO */
    DL_CONTINUE,	/* => there is another chunk */
    DL_VPSIZE,		/* set viewport posn to uX,uY;
			 *    size to uExtra,ushrt[0] */
    DL_MOVETO,		/* set 'current' to uX, uY */
    DL_POINT,		/* at uX, uY in ulColor */
    DL_POINTAT,		/* at 'current' in ulColor */
    DL_LINE,		/* from uX, uY to uExtra,uShrt[0] in ulColor */
    DL_LINETO,		/* from 'current' to uX, uY in ulColor */
    DL_BOX,		/* uX,uY = ul; uExtra,uShrt[0] = lr; in ulColor */
    DL_FILLEDBOX,	/* uX,uY = ul; uExtra,uShrt[0] = lr; in ulColor */
    DL_CIRCLE,		/* uX,uY = center; uExtra = radius; in ulColor */
			/* uShrt[0] may be a class number */
    DL_TEXT,		/* uX,uY = left end of baseline; ulColor, cStr */
			/* uExtra may be a class number */
			/* may also be used for MESSAGE, in which case
			 * uExtra is >= 2 and specifies style:
			 *    2 => status bar text; 3 => messagebox
			 * o.uShrt[0] etc may have additional specs. */
    DL_TEXTR,		/* uX,uY = right end of baseline; ulColor, cStr */
    DL_TEXTC,		/* uX,uY = center of baseline; ulColor, cStr */
    DL_TEXTAT,		/* 'current' = beginning of baseline; ulColor, cStr
			 * 'uExtra' is direction: degrees cw from East */
    DL_FONT,		/* cStr is name; uExtra is size */
    DL_WEDGE,
    DL_SETSCALE,	/* for scaling coords; dDouble[0] default=1.0 */
    DL_SETOFFSET,	/*  "  offsetting "      "               =0.0 */
    DL_APPEND,		/* insert chunks from file named 'cStr'
			 * with origin of those chunks at uX,uY */
	/* interactive ops: return info in chunk file
	 * data values put into uShrt; count in uExtra; drw col in ulColor  */
    DL_SET_CLIP,	/* uX,uY, uExtra,uShrt[0] define area of acceptance */
			/* for all of the following, o.ulong[1] is 'style'
			 * (see DGRAPH.C) and [0] is 'size' */
    DL_ACCEPT_PPOINT,	/* uExtra is max number of points, or 0 => indef. */
    DL_ACCEPT_PLINE,	/* uExtra is max number of vertices*/
    DL_ACCEPT_BOX,      /* let user specify rect. area */
    DL_ACCEPT_TEXTSIZE,	/* cStr is string (if empty, return avg char size) */
    DL_ACCEPT_TEXTPOS,	/* cStr is string; let user sel. posn; return uX,uY */
    DL_ACCEPT_TEXT,	/* let user type a message at x0,y0
			 *  (uExtra set => let user select position) ; 
			 *  return text and actual x0,y0  */
    DL_ACCEPT_POINT,	/* o.ulLong[0] is mask; x,y are init posn or -1;
			 * uExtra is size (% of screen); o.ulLong[1] is style */
    DL_COLORMAP,	/* ulColor is first of up to 3 #,R,G,B colors
			 * (others in o.ulLong[]; count in uExtra)
			 * The associated colornumber is the hibyte of long
			 */
    DL_POLYLINE,	/* uShrt are used for counts plus all coord values,
			 * so that the .o struct can be used directly by
			 * the DRAGON PLINE ops. uShrt[1] is vertex count,
			 * uShrt[0] is the line number (pcount) if we need it.
			 * First point is in uShrt[2], etc.
			 * ulColor is valid as outline color. */
    DL_POLYGON,		/* closed polygon with same args as DL_POLYLINE */
    DL_POLYFILL,	/* filled polygon with same args as DL_POLYLINE */
    DL_PROPERTY,	/* escape for setting something
			 * not yet defined or used */
    DL_EVENT,		/* uX, uY may be current position or xFFFF;
			 * ulColor may be current color or xFFFFFFFF;
			 * uExtra is the event. */			 
    DL_EXPANDINGBOX,	/* like filled box, except size will expand to include
			 * all subsequent items (til FREEZE).
			 * uX,uY = ul; uExtra,uShrt[0] = lr; in ulColor 
			 * uShrt[1] > 0 => outline on uShrt[1] width,
			 * ulLong[1] color */
    DL_FREEZEBOX,	/* stop expanding the expanding box */
    DL_MARKER,		/* generally, text used locally not put into INFO */
    DL_INVALIDOP    
    } DL_OP ;

#define DL_OP_NAMES \
	"DL_END","DL_CONTINUE", "DL_VPSIZE","DL_MOVETO", \
	"DL_POINT","DL_POINTAT","DL_LINE","DL_LINETO", \
	"DL_BOX","DL_FILLEDBOX","DL_CIRCLE","DL_TEXT", \
	"DL_TEXTR","DL_TEXTC","DL_TEXTAT","DL_FONT", \
	"DL_WEDGE","DL_SETSCALE","DL_SETOFFSET","DL_APPEND", \
        "DL_SET_CLIP","DL_ACCEPT_PPOINT","DL_ACCEPT_PLINE","DL_ACCEPT_BOX", \
	"DL_ACCEPT_TEXTSIZE","DL_ACCEPT_TEXTPOS","DL_ACCEPT_TEXT", \
	"DL_ACCEPT_POINT","DL_COLORMAP", \
	"DL_POLYLINE","DL_POLYGON","DL_POLYFILL", \
	"DL_PROPERTY","DL_EVENT", \
	"DL_EXPANDINGBOX","DL_FREEZEBOX",\
	"DL_MARKER",\
	"DL_INVALIDOP"

//#if _DEBUG_
//#define nameof(strings,val) ((strings && strings[val]) ? strings[val] : "Unknown")
extern char * DL_OPNames[];
//#endif
	/* for this chunk, cChunk = one of the following:
	 *  "DL-PICK"   => non-scrolling interactive probably graphical
	 *  "DL-GRAPH"  => non-scrolling non-interactive probably graphical
	 *  "DL-REPORT" => scrolling non-interactive probably text
	 *  "DL-EDIT"   => scrolling interactive text
	 *  "DL-ANNOT"  => annotation for viewport image
	 *  "DL-SCRIBBLE"  => free-form drawing
	 *  "DL-CONT"   => continuation chunk
	 */

#define CH_INFO_SIZE 4096

#if defined  _WIN32 || defined MSC || defined __GCC__
#pragma pack(1)
#endif

typedef struct CH_INFOtag
    {
    UINT16 uSize;		/* size of this structure plus assoc. string */
    UINT16 uOp;			/* actually an enum DL_OP */
    UINT16 uX,uY;
    UINT32 ulColor;		/* in colnum,R,G,B order */
    UINT16 uExtra;
    UINT16 uExtra2;
    union
	{
	double dDouble[1];
	UINT32 ulLong[2];
	UINT16 uShrt[4]; 	/* as many as necessary */
	    			/* ~~~ v 5/12 unsigned is a problem, but
				 *     eventually the UINT16 will be also */
	char cStr[1];		/* as long as necessary */
	} o;			/* optional values */
    } CH_INFO;

#if defined  _WIN32 || defined MSC || defined __GCC__
#pragma pack()
#endif

typedef enum
    {
    DL_STYLE_CUR,	// no buttons, but report area. For CUR
    DL_STYLE_VEC,
    DL_STYLE_MEA,
    DL_STYLE_COO,
    DL_STYLE_TRA,
//    DL_STYLE_LAST_BUTTON=DL_STYLE_TRA,
    DL_STYLE_GCP,
    DL_STYLE_COL,
    DL_STYLE_ANN,
    DL_STYLE_LAST
    } DL_STYLE_OP ; 	// actually this is bits4:7 of &STYLE
    
#define DL_STYLE_NAMES \
    "DL_STYLE_CUR", \
    "DL_STYLE_VEC", \
    "DL_STYLE_MEA", \
    "DL_STYLE_COO", \
    "DL_STYLE_TRA", \
    "DL_STYLE_GCP", \
    "DL_STYLE_COL", \
    "DL_STYLE_ANN", \
    "DL_STYLE_INVALID"

/* INF_TYPE are values for cChunk field */
typedef enum {	INF_PICK, INF_GRAPH, INF_REPORT, INF_EDIT,
		INF_ANNOT, INF_SCRIB,	/* drawing ops - see portfile.h */
		INF_PIXG, INF_PIXM, INF_PIX24, INF_PIX32, INF_BMP, /* image ops */
		INF_CONT, INF_TRAILER, INF_INVALID	/* administrative ops */
	     } INF_TYPE ;

// limit the following strings to 15`< chars 
#define INF_TYPE_NAMES \
	"DL-PICK", "DL-GRAPH", "DL-REPORT", "DL-EDIT",  \
 	"DL-ANNOT", "DL-SCRIB", \
	"DL-PIXG" /* gray 8-bit */, "DL-PIXM" /* color mapped 8-bit */, \
	"DL-PIX24" /* true color 24-bit */, \
	"DL-PIX32" /* true color plus alpha */, \
        "DL-BMP", \
	"DL-CONT" /* continuation chunk */, "DL-TRAILER", "DL-INVALID"


/* Header signatutes for various resources */
#define BFT_CHUNK  0x4843   /* 'CH' - GRS private */
#define BFT_ICON   0x4349   /* 'IC' */
#define BFT_BITMAP 0x4d42   /* 'BM' */
#define BFT_CURSOR 0x5450   /* 'PT' */


#if defined __cplusplus
    }
#endif

#endif


