/*
 * 	JPEG-WRT.H
 *		definitions for writing JPEG files from WF
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
 ****************************************************************
 *   $Id: jpeg-wrt.h,v 1.2 2014/12/05 09:58:46 rudahl Exp $
 *   $Log: jpeg-wrt.h,v $
 *   Revision 1.2  2014/12/05 09:58:46  rudahl
 *   no differences between DragonProf and OpenDragon
 *
 *   Revision 1.1  2002/08/26 16:21:52  rudahl
 *   initial provisional deposit
 *
 ****************************************************************
 *
 *	8/26/02 ktr	adapted from tiff-wrt.h
 */

#ifndef JPEG_WRT_H
#define JPEG_WRT_H

//#ifndef byte  // removed 4/2000 - already in dtypes.h
//typedef unsigned char byte;
//#endif

/****************************************************************
 *
 *	public functions for creating a JPEG image file
 *	typically from DRAGON data.
 *
 *	These are intended to be models for a similar API for
 *	other formats.
 *
 ***************************************************************/

int JpegPlotOpen(const char * czFilename,const uint uMode,
		 const uint uPlanes, const void far * lpHdr);
	/*	open file and write eader based on info in lpHdr
	 *	uMode low byte, for JPEG, should be 1
	 *	uMode high byte 1 => lpHdr is an IHEAD
	 *			0 => lpHdr is a rect
	 *	uPlanes is 1 for 8-bit mapped JPEG, 3 for fullcolor
	 *	return 0 if error; else 1
	 */

void JpegPlotNextLine(const byte * lpData,const uint uPixWidth);
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

int JpegPlotClose();
	/* 	close the current file
	 *	return 1 if error; else 0
	 */

#endif /* #ifndef JPEG_WRT_H */


