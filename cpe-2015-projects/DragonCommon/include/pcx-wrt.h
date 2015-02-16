/*
 * 	PCX-WRT.H
 *		definitions for writing PCX files from WF
 *      Copyright 1987-1999 by Goldin-Rudahl Associates
 *                            P.O. Box 648
 *                            North Amherst, MA 01059 U.S.A.
 *
 ****************************************************************
 *   $Id: pcx-wrt.h,v 1.3 2002/08/21 23:31:50 rudahl Exp $
 *   $Log: pcx-wrt.h,v $
 *   Revision 1.3  2002/08/21 23:31:50  rudahl
 *   changed GetPalette
 *
 *   Revision 1.2  2000/05/30 00:33:42  rudahl
 *   fixup for SuSE
 *
 *   Revision 1.1  1999/05/18 17:55:44  rudahl
 *   For PCX output from DRAGON
 *
 *
 ****************************************************************
 *
 *	5/9/99 ktr	adapted from printiff.h, for use with PCX-WRT.C
 */

#ifndef PCX_WRT_H
#define PCX_WRT_H

//#ifndef byte   // removed 4/2000; already in dtypes.h
//typedef unsigned char byte;
//#endif

/****************************************************************
 *
 *	public functions for creating a PCX image file
 *	typically from DRAGON data.
 *
 *	These are intended to be models for a similar API for
 *	other formats.
 *
 ***************************************************************/

int PcxPlotOpen(const char * czFilename,const uint uMode,
		 const uint uPlanes, const void far * lpHdr);
	/*	open file and write eader based on info in lpHdr
	 *	uMode low byte, for Pcx, should be 1
	 *	uMode high byte 1 => lpHdr is an IHEAD
	 *			0 => lpHdr is a rect
	 *	uPlanes is 1 for 8-bit mapped Pcx, 3 for fullcolor
	 *	return 0 if error; else 1
	 */

void PcxPlotNextLine(const byte * lpData, const uint uPixWidth);
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

int PcxPlotClose();
	/* 	close the current file
	 *	return 1 if error; else 0
	 */

/***************************************************************/
/*  Pcx header structure */

typedef struct xx91922
	{
	char manuf;
	char version;
	char encode;
	char bitpix;
	unsigned int x0,y0,x1,y1;
	int hres,vres;
	char palette[48];
	char vmode;
	char nplanes;
	unsigned int bytes_line;
        int pcxPaletteInfo;
	char pcxFiller[58];	/* filler to make up 128 bytes */
	} PCX_HEAD;		/* color map is at end of file */

#endif /* #ifndef PCX_WRT_H */


