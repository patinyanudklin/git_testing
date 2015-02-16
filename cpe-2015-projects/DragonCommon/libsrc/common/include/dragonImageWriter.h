/*
 *	filename dragonImageWriter.h
 *		$Revision: 1.18 $ $Date: 2014/12/29 03:28:29 $	
 *
 *      ~~ Copyright 2004-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: dragonImageWriter.h,v 1.18 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: dragonImageWriter.h,v $
 *   Revision 1.18  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.17  2014/12/06 11:27:44  rudahl
 *   conditional changes for OpenDragon
 *
 *   Revision 1.16  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.15  2010/12/19 06:56:58  rudahl
 *   fix some docs
 *
 *   Revision 1.14  2008/06/14 10:15:28  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.13  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.12  2005/06/26 06:18:15  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.11  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.12  2005/03/11 20:27:54  goldin
 *   debugging rewriteImageHeader
 *
 *   Revision 1.11  2005/03/10 22:41:32  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.10  2005/03/10 03:18:31  goldin
 *   Still working on img_acc test code
 *
 *   Revision 1.9  2005/03/03 16:27:05  rudahl
 *   added getTrailerOffset
 *
 *   Revision 1.8  2005/03/01 16:02:36  rudahl
 *   adding writeTrailer
 *
 *   Revision 1.7  2005/02/15 02:33:25  san
 *   Fixes error
 *
 *   Revision 1.6  2005/02/10 23:21:56  rudahl
 *   added debug flags into constructors
 *
 *   Revision 1.5  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.4  2005/01/27 21:35:53  rudahl
 *   fixed enough to compile
 *
 *   Revision 1.3  2005/01/27 02:09:17  san
 *   fixes compilation errors
 *
 *   Revision 1.2  2005/01/18 22:04:06  san
 *   added private methods to convert virtual 
 *   image header structure to new image header structure
 *
 *   Revision 1.1  2005/01/04 16:03:22  rudahl
 *   new from moochie
 *
 *   Revision 1.1  2005/01/03 05:28:56  rudahl
 *   init from Moochie
 *
 ****************************************************************
 * 
 * Define a class for writing new-format Dragon image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *              san     San Ratanasanya
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-01 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 	2005-01-17 san  create methods to transfer header from memory to file
 * 	2005-1-31 ktr	renamed/rescoped from HeaderWriter
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h
 * 5.11	2008-06-14 ktr	added LinesBlob to trailer
 * 
 */

#if !defined DRAGIMGWRTR_H
#define DRAGIMGWRTR_H

class DragonImageWriter : public ImageWriter
    {
    public:
	DragonImageWriter(int iDebug=0, int iTrace=0);

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

#if DRAGON_VER >= 6
	virtual int setLinesBlob(const byte * pBlob,size_t uBlobSize);
#endif

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
	/* ~~ these private sector need to be verified */ 
    private:
	        // make output image header agree with contents of m_pHdr.
	        // @@param pDestHdr DHEAD-sized buffer (actually s_outbuf)
                //                 
                // @@return        <0 if err (missing argument)
        int copyFields(DRAGON_HEAD * pDestHdr);

	        // make output image header agree with contents of passed
                // IMAGEHDR structure.
	        // @@param pDestHdr DHEAD-sized buffer 
                // @@param pSrcHdr  IMAGEHDR holding data to copy             
                // @@return        <0 if err (missing argument)
        int copyFields(DRAGON_HEAD * pDestHdr, const IMAGEHDR * pSrcHdr);

	        // copy mapcoord structure
	void mapCoord_copy(const MapCoord * src, HDR_MapCoord * dest);
	/* ~~ need to implement the following fn */
        int convertHeaderClassNames(const DRAGON_HEAD * pSrcHdr, 
				    size_t * pMaxLabelLen); 
	static const char * s_czTrailerNames[];
    } ;

#endif // DRAGIMGWRTR_H
