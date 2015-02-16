/*
 *	filename tiffImageHeaderWriter.h
 *		$Revision: 1.6 $ $Date: 2014/12/05 13:41:51 $	
 *
 *      ~~ Copyright 2010-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: tiffImageWriter.h,v 1.6 2014/12/05 13:41:51 rudahl Exp $
 *   $Log: tiffImageWriter.h,v $
 *   Revision 1.6  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.5  2011/02/27 08:24:51  rudahl
 *   final work on tiff IO
 *
 *   Revision 1.4  2011/01/31 02:12:50  rudahl
 *   working on geotiff in tiff export
 *
 *   Revision 1.3  2010/12/25 05:17:00  rudahl
 *   work on tiffwriter
 *
 *   Revision 1.2  2010/12/24 08:57:08  rudahl
 *   integrate the tiffWriter into the build
 *
 *   Revision 1.1  2010/12/19 06:39:09  rudahl
 *   not yet compilable
 *
 *
 ****************************************************************
 * 
 * Define a class for writing GeoTIFF files headers from Dragon image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 6.1	2010-12-18 ktr	created
 */

#if !defined TIFFIMGWRTR_H
#define TIFFIMGWRTR_H

class TiffImageWriter : public ImageWriter
    {
    public:
	TiffImageWriter(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
	static BOOL test(const char * pczFilename);

		// read the file 
		// @param pczFilename	name of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @return		TRUE if OK
	BOOL writeHeader(const char * pczFilename, const IMAGEHDR * pHdr,
		  int * pErrNum);

	/*	Put a line of raw data to the file
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *	Ignores ProcessRect.
	 *
	 *	@param pBuf	pointer to the data buffer
	 *	@param uLineNo	image memory line to write
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param bReReadable  TRUE => we may be reading/writing mixed
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			   -51  file open error
	 *			   -52  seek error
	 *			   -53  write error
	 *			   -55  file not open 
	 *			   -56  trying to write past end-of-file
	 *			   -75  buffer size doesn't match image line
	 *			   -91  line number bigger than image
	 *			     or errors from fwrite, fseek
	 */
	int putImageLineRaw(const byte * pBuf, ushort uLineNo,
				 size_t uBufSize, const IMAGE * pImg,
				     BOOL bReReadable);

	/* if m_pFp is open, close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
	int close();


		// rewrite selected header info if changed
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

		/* overwrite any IMAGEHDR values necessary for 
		 * this format by calling pImageheader->revise_geom()
		 * @param pImageHdr	pointer to hdr struct
		 * @param plOffset	init sets offset of start of image
		 *			data, or -1;
		 * @return		0 if OK else:
		 *			-40 uBitsPerPix is unsupported
		 *			-41 uNumBands is unsupported
		 *			-42 uNumResolutions is unsupported
		 */
       int init(ImageHdr * pImageHdr,long * plOffset); 


	/* calc and return the size of the header plus image data, or 0
	 * This cannot be done until the header has been written
	 */
	ulong getTrailerOffset() const;

//	virtual int setLinesBlob(const byte * pBlob,size_t uBlobSize);

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
	/* ~~ these private sector need to be verified */ 
    private:
	        // make output image header agree with contents of m_pHdr.
	        // @@param pDestHdr DHEAD-sized buffer (actually s_outbuf)
                //                 
                // @@return        <0 if err (missing argument)
//        int copyFields(DRAGON_HEAD * pDestHdr);

	        // make output image header agree with contents of passed
                // IMAGEHDR structure.
	        // @@param pDestHdr DHEAD-sized buffer 
                // @@param pSrcHdr  IMAGEHDR holding data to copy             
                // @@return        <0 if err (missing argument)
        int copyFields(DRAGON_HEAD * pDestHdr, const IMAGEHDR * pSrcHdr);

		// create the IFD
		// return size of tags (in bytes) or 0 if error
	int createIFD(void * pTif, const IMAGEHDR * pSrcHdr,
		      int * pErrNum,
		      ulong ulImageDataSize);

	int m_iTagBufLen;	// size of data following the tags
				// in s_uDataBuf (which should move here also)
	ushort m_uiTagCount;

	        // copy mapcoord structure
	void mapCoord_copy(const MapCoord * src, HDR_MapCoord * dest);
	/* ~~ need to implement the following fn */
//        int convertHeaderClassNames(const DRAGON_HEAD * pSrcHdr, 
//				    size_t * pMaxLabelLen); 
	static const char * s_czTrailerNames[];
    } ;

#endif // TIFFIMGWRTR_H
