/*
 *	filename jpegImageWriter.h
 *		$Revision: 1.1 $ $Date: 2014/03/01 01:51:54 $	
 *
 *      ~~ Copyright 2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: jpegImageWriter.h,v 1.1 2014/03/01 01:51:54 rudahl Exp $
 *   $Log: jpegImageWriter.h,v $
 *   Revision 1.1  2014/03/01 01:51:54  rudahl
 *   extracted from screenImageWriter
 *
 *
 ****************************************************************
 * 
 * Define a class for writing headers for jpeg image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.14 & 6.4	2014-02-28 ktr	extracted from screenImageWriter
 */

#if !defined JPEGIMGWRTR_H
#define JPEGIMGWRTR_H

class JpegImageWriter : public ImageWriter
    {
    public:
	JpegImageWriter(int iDebug=0, int iTrace=0);

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
		// @return		0 if OK else:
		//			-40 uBitsPerPix is unsupported
		//			-41 uNumBands is unsupported
		//			-42 uNumResolutions is unsupported
	int init(ImageHdr * pImageHdr);

		//	Put a line of raw data to the file
		//	The data consists of 8-bit pixels in RGB sequence
 		//	or single 8-bit pixels for grey-scale output
		//
		//	@param pBuf	pointer to the data buffer
		//	@param uLineNo	image memory line to write
		//	@param uBufSize	the size of pBuf - i.e. how much data to write
		//			(uLineNo & all of the following are ignored)
		//	@param pImg	pointer to IMAGE struct
		// 	@param bReReadable  TRUE => we may be reading/writing mixed
		//	@return 	ubufSize
		//
	int putImageLineRaw(const byte * pBuf, ushort uLineNo,
			    size_t uBufSize, const IMAGE * pImg,
			    BOOL bReReadable);

		//	Put a line of pixels to the file
		//	This fn should merge one band into a raw line.
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
		//			for JpegImageFile
	int putImageLine(const byte * pBuf, ushort uLineNo,
			 size_t uBufSize, const IMAGE * pImg,
			 BOOL bReReadable)
	    { return DERR_FN_NOTIMPL; } ;

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


#endif // JPEGIMGWRTR_H
