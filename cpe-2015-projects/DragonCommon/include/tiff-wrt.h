/*
 * 	TIFF-WRT.H
 *		definitions for writing TIFF files from WF
 *
 *      ~~ Copyright 1987-2014 Kurt Rudahl and Sally Goldin
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
 *
 ****************************************************************
 *   $Id: tiff-wrt.h,v 1.6 2014/12/05 09:58:46 rudahl Exp $
 *   $Log: tiff-wrt.h,v $
 *   Revision 1.6  2014/12/05 09:58:46  rudahl
 *   no differences between DragonProf and OpenDragon
 *
 *   Revision 1.5  2006/12/10 11:58:26  rudahl
 *   got rid of far declaration
 *
 *   Revision 1.4  2002/08/21 23:31:50  rudahl
 *   changed GetPalette
 *
 *   Revision 1.3  2000/05/30 00:33:42  rudahl
 *   fixup for SuSE
 *
 *   Revision 1.2  1999/05/09 22:21:14  rudahl
 *   minor doc. changes
 *
 *   Revision 1.1  1999/05/09 21:19:04  rudahl
 *   Add TIFF output capability to DRAGON & Viewport
 *
 * Revision 4.1  1993/12/19  10:59:14  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/12/19  10:59:14  tower
 * DRAGON Release 4.0G, D4S (prelim) - initial merge of DRAGPRNT
 * into DGRAPH - mostly conditionalized, little optimization - preliminary
 * 
 * Revision 4.0  1992/06/27  20:28:08  tower
 * Updated for DRAGON Release 4.0b - minor changes
 * 
 * Revision 3.1  92/02/23  15:28:46  tower
 * for 3.05 & ImageFile: merged in TIFCREAT.H (which is now dead) and
 *                       updated for TIFF v 5.0
 * 
 *
 ****************************************************************
 *
 *	12/8/91 ktr 	merged TIFCREAT.H into here. 
 *		    	   TIFCREAT.H is now probably dead
 *	12/8/91 	changed MAX_TAG for TIFF 5.0
 *  3.4 6/27/92 ktr	updating for Zortech 3.0: fixed bug in portrait mode
 *			offset.
 *	5/9/99 ktr	adapted from wftiff.h, for use with TIFF-WRT.C
 * 5.9	2006-12-10 ktr	got rid of a far decl.
 */

#ifndef TIFF_WRT_H
#define TIFF_WRT_H

//#ifndef byte  // removed 4/2000 - already in dtypes.h
//typedef unsigned char byte;
//#endif

/****************************************************************
 *
 *	public functions for creating a TIFF image file
 *	typically from DRAGON data.
 *
 *	These are intended to be models for a similar API for
 *	other formats.
 *
 ***************************************************************/

int TiffPlotOpen(const char * czFilename,const uint uMode,
		 const uint uPlanes, const void * lpHdr);
	/*	open file and write eader based on info in lpHdr
	 *	uMode low byte, for TIFF, should be 1
	 *	uMode high byte 1 => lpHdr is an IHEAD
	 *			0 => lpHdr is a rect
	 *	uPlanes is 1 for 8-bit mapped TIFF, 3 for fullcolor
	 *	return 0 if error; else 1
	 */

void TiffPlotNextLine(const byte * lpData,const uint uPixWidth);
	/* 	write line of data to the open file. 
	 * 	If uPixWidth > 1 (byte), write three planes
	 * 	else if it's a 3-plane image, map the data through
	 *	palette.
	 */

int GetPalette(ushort * lpPalette, const size_t uPaletteSize);
	/*	Fn must be provided by the app, and must fill lpPalette
	 *	with no more than the specified number of bytes, 
	 *	and return the number of byters set.
	 *	Typically, the palette is 256 reds, then 256 greens,
	 *	then 256 blue values.
	 */

int TiffPlotClose();
	/* 	close the current file
	 *	return 1 if error; else 0
	 */

/***************************************************************
 *
 *	defns for compat. with old dragplot
 *
 ***************************************************************/

#ifdef DRAGPLOT

#define PlotOpen(filename,mode,planes) TiffPlotOpen(filename,mode,planes,&box)
#define PlotClose() TiffPlotClose()

#endif
/***************************************************************/
/*  TIFF header structure */

struct header_tiff_struc
    {
    short byteorder;
    short version;
    long first_ifd_addr;
    } ;

/*  Default values for header structure */

#define INTEL_FMT	0x4949
#define TIF_VERSION	0x2a

typedef struct 
    {
    long num,denom;
    } RATNL;

/*  Image File Directory structure */

typedef struct 
    {
    short tagnum;
    short fieldtype;
    long fieldlen;
    long offset_rvalue;
    } IFDSTRC;

/*  TIFF definitions */

#define TBYTE	1
#define TASCII	2
#define TSHORT	3
#define TLONG	4
#define TRATNL	5

#define MAX_TAG		320		/* the maximum tag value */

#define get_cpos(fhndl) lseek(fhndl, 0L, SEEK_CUR)
			 /* Gives current position in file */

		/* functions in TIFWRITE & TIFF_WRT */

		/* functions in TIFCREAT & TIFF_WRT */

		/* functions in TIFF_WRT */


#endif /* #ifndef TIFF_WRT_H */


