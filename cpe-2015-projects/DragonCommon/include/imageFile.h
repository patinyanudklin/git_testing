/*
 *	filename imageFile.h
 *		$Revision: 1.3 $ $Date: 2014/12/05 09:58:46 $	
 *
 *      ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: imageFile.h,v 1.3 2014/12/05 09:58:46 rudahl Exp $
 *   $Log: imageFile.h,v $
 *   Revision 1.3  2014/12/05 09:58:46  rudahl
 *   no differences between DragonProf and OpenDragon
 *
 *   Revision 1.2  2005/01/20 22:58:57  rudahl
 *   added screenfile
 *
 *   Revision 1.1  2005/01/20 19:40:12  rudahl
 *   initial, incomplete
 *
 *
 ****************************************************************
 * 
 * This file defines a virtual base 
 *	class for reading and writing image data
 *
 *	The content of this and imageFile.cpp are derived from parts
 *	of img_hdr.c, img_acc.c, and imagfile.cpp in Dragon 5.4.
 *
 *	This file requires dtypes.h, dhead.h
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-1-20 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 
 */

#if ! defined IMAGEFILE_H
#define IMAGEFILE_H	/* signal this file has been loaded */


#if defined __cplusplus

public class ImageFile : public OB
    {
    public:
		// ctor will correctly init things into a null state
		// This is used for reading a file, and must be followed
		// by a call to init();
	ImageFile();  

		// ctor will correctly init things in praparation for
		// creating a new file
		// @param pczFilePath	file to create
		// @param uFileType	what format file
		// @param uLineCount	how many lines in file
		// @param uPixCount	how many pixels in file
		// @param uBandCount	how many bands in file
		//			( >1 only if supported by uFileType)
	ImageFile(const char * pczFilePath,IMGTYPE_T uFileType,
		  size_t uLineCount, size_t uPixCount, size_t uBandCount=1);  

		// initialize class member by reading from the specified file
		// @param pczFilePath	file to read
		// @param bRW		TRUE => file data can be written
		//			as well as read.
	int init(const char * pczFilePath);  

		// get (part of) a line of image pixels from one band 
		// into a buffer
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uFirstPixel	index of first pixel to read
		// @param uPixelCount	number of pixels to read if available
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
	int getLine(ushort * puBuf,size_t uBufSize,size_t uLineNo,
		    size_t uFirstPixel, size_t uPixelCount, size_t uBandNo=0);

		// get a line of image pixels from one band 
		// into a buffer
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
	int getLine(ushort * puBuf,size_t uBufSize,size_t uLineNo,
		    size_t uBandNo=0);

		// get a line of raw pixel data into a buffer
		// @param pbBuf		buffer where data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @return		0 if OK else error number
	int getLineRaw(byte * puBuf,size_t uBufSize,size_t uLineNo);

		// put (part of) a line of image pixels to one band 
		// from a buffer
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uFirstPixel	index of first pixel to read
		// @param uPixelCount	number of pixels to read if available
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
	int putLine(const ushort * puBuf,size_t uBufSize,size_t uLineNo,
		    size_t uFirstPixel, size_t uPixelCount, size_t uBandNo=0);

		// put a line of image pixels to one band 
		// from a buffer
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
	int putLine(const ushort * puBuf,size_t uBufSize,size_t uLineNo,
		    size_t uBandNo=0);

		// put a line of raw pixel data from a buffer
		// @param pbBuf		buffer where data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @return		0 if OK else error number
	int putLineRaw(const byte * puBuf,size_t uBufSize,size_t uLineNo);

		// write all data to file or other medium as appropriate
		// @return	0 if OK
		// 		-1 if something missing
		// 		-2 other error
	int flush();

	ImageHdr * getImageHdr() { return pHdr; } ;
    protected:
	ImageHdr * pHdr;
    } ;

#endif /* if defined __cplusplus */

#ifdef NOTHERE /* these need to be in the subclasses not here */
		// get (part of) a line of image pixels from one band 
		// into a buffer
		// @param piFile	pointer to an ImageFile
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uFirstPixel	index of first pixel to read
		// @param uPixelCount	number of pixels to read if available
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
int getXXLine(const void * pIfile,ushort * puBuf,size_t uBufSize,
	      size_t uLineNo,
	      size_t uFirstPixel, size_t uPixelCount, size_t uBandNo=0);

		// get a line of image pixels from one band 
		// into a buffer
		// @param piFile	pointer to an ImageFile
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
int getXXLine(const void * pIfile,ushort * puBuf,size_t uBufSize,
	      size_t uLineNo,size_t uBandNo=0);

		// get a line of raw pixel data into a buffer
		// @param piFile	pointer to an ImageFile
		// @param pbBuf		buffer where data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @return		0 if OK else error number
int getXXLineRaw(const void * pIfile,byte * puBuf,size_t uBufSize,
		 size_t uLineNo);

		// put (part of) a line of image pixels to one band 
		// from a buffer
		// @param piFile	pointer to an ImageFile
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uFirstPixel	index of first pixel to read
		// @param uPixelCount	number of pixels to read if available
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
int putXXLine(const void * pIfile,const ushort * puBuf,size_t uBufSize,
	      size_t uLineNo,
	      size_t uFirstPixel, size_t uPixelCount, size_t uBandNo=0);

		// put a line of image pixels to one band 
		// from a buffer
		// @param piFile	pointer to an ImageFile
		// @param puBuf		buffer where pixel data is placed
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @param uBandNo	index of band number to read
		// @return		0 if OK else error number
int putXxLine(const void * pIfile,const ushort * puBuf,size_t uBufSize,
	      size_t uLineNo, size_t uBandNo=0);

		// put a line of raw pixel data from a buffer
		// @param pbBuf		buffer where data is placed
		// @param piFile	pointer to an ImageFile
		// @param uBufSize	size of buffer
		// @param uLineNo	line number to read
		// @return		0 if OK else error number
int putXXLineRaw(const void * pIfile,const byte * puBuf,size_t uBufSize,
		 size_t uLineNo);

#endif /* NOTHERE */

#endif /* define IMAGEFILE_H	* signal this file has been loaded */
