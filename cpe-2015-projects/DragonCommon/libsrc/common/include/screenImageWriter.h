/*
 *	filename screenImageWriter.h
 *		$Revision: 1.12 $ $Date: 2014/12/05 13:41:51 $	
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
 *
 ****************************************************************
 *   $Id: screenImageWriter.h,v 1.12 2014/12/05 13:41:51 rudahl Exp $
 *   $Log: screenImageWriter.h,v $
 *   Revision 1.12  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.11  2011/12/13 13:32:36  rudahl
 *   write chunk file in linux actually creates JPG
 *
 *   Revision 1.10  2005/06/26 06:18:15  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.9  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.9  2005/03/16 04:06:53  rudahl
 *   fixing writeTrailer tests
 *
 *   Revision 1.8  2005/03/10 22:41:32  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.7  2005/03/03 16:27:05  rudahl
 *   added getTrailerOffset
 *
 *   Revision 1.6  2005/02/15 02:35:06  san
 *   Fixes error
 *
 *   Revision 1.5  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.4  2005/02/07 05:40:17  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.3  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.2  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.1  2005/01/26 02:04:00  rudahl
 *   initial from moochie
 *
 *
 ****************************************************************
 * 
 * Define a class for writing headers for screen (chunk) image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *              san     San Ratanasanya
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-20 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 	2005-1-31 ktr	renamed/rescoped from HeaderWriter
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h
 * 
 */

#if !defined CHUNKIMGWRTR_H
#define CHUNKIMGWRTR_H

class ScreenImageWriter : public ImageWriter
    {
    public:
	ScreenImageWriter(int iDebug=0, int iTrace=0);

		// write the file 
		// @param pczFilename	name of file to read
		// @param pHdr		pointer of ImageHdr struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		//			  -51 for file open/create error
		//			  -53 for file write error
		//			  -54 for file close error
		//			  -60 for uninit. header
		// @return		TRUE if OK
/* ~~ change const IMAGEHDR variable to normal one */
	BOOL writeHeader(const char * pczFilename, const IMAGEHDR * pHdr,
			 int * pErrNum) ;

		// rewrite selected header info if changed
		// @param pFp		open file at unknown position
		// @param pHdr		pointer of IMAGEHDR struct to write
		// @param pErrNum	pointer to variable to receive errnum
		// @return		0 if OK else ...
	int rewriteHeader(const Image * pImg);

		// append trailer on the file 
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
	int writeTrailer(const char * pczFilename,
			 const IMAGEHDR * pHdr,UINT32 uDataCheck);

		// overwrite any IMAGEHDR values necessary for 
		// this format by calling pImageheader->revise_geom()
		// @param pImageHdr	pointer to ImageHdr
		// @param plOffset	init sets offset of start of image
		//			data, or -1;
		// @return		0 if OK else:
		//			-40 uBitsPerPix is unsupported
		//			-41 uNumBands is unsupported
		//			-42 uNumResolutions is unsupported
	int init(ImageHdr * pImageHdr,long * plOffset) ;

#if defined __GCC__ 
	/*	Put a line of raw data to the file
	 *
	 *	@param pBuf	pointer to the data buffer
	 *	@param uLineNo	image memory line to write
	 *	@param uBufSize	the size of pBuf - i.e. how much data to write
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param bReReadable  TRUE => we may be reading/writing mixed
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *			     or errors from fwrite, fseek
	 */
	int putImageLineRaw(const byte * pBuf, ushort uLineNo,
			    size_t uBufSize, const IMAGE * pImg,
			    BOOL bReReadable);
#else // #if defined __GCC__ 

		//	Put a line of pixels to the file
		//	This fn should merge one band a raw line.
		//	However, there should be no need for this, so the fn
		// 	is unimplemented.
		//
		//	@param pBuf	pointer to the data buffer
		//	@param uLineNo	image memory line to write
		//	@param uBufSize	the size of pBuf
		//	@param pImg	pointer to IMAGE struct
		// 	@param bReReadable  TRUE => we may be 
		//			reading/writing mixed
		//	@return 	-99 - this fn should not be used 
		//			for ScreenImageFile
	int putImageLine(const byte * pBuf, ushort uLineNo,
			 size_t uBufSize, const IMAGE * pImg,
			 BOOL bReReadable)
	    { return DERR_FN_NOTIMPL; } ;
#endif // #if defined __GCC__ 

		// return how many bytes will be needed 
		// for one line of raw data
	size_t getRawImageLineSize(size_t uPixels);

		// calc and return the size of the header plus image data, or 0
		// This cannot be done until the header has been written
		// In this case
	ulong getTrailerOffset() const;

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
    private:
	        // make image header agree with 'pSrcHdr'
	        // @@param pSrcHdr DHEAD-sized buffer (actually s_outbuf)
                //                 which has been filled from a file 
                // @@return        <0 if err (missing argument)
//        int copyFields(const DRAGON_HEAD * pSrcHdr);
	static Class s_class_Base;
    } ;


#endif // CHUNKIMGWRTR_H
