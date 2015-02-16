/*
 *	filename dragonOldImageHeaderWriter.h
 *		$Revision: 1.5 $ $Date: 2005/09/17 05:25:45 $	
 *
 *      Copyright 2004-2005 Kurt Rudahl and Sally Goldin
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
 *
 ****************************************************************
 *   $Id: dragonOldImageWriter.h,v 1.5 2005/09/17 05:25:45 rudahl Exp $
 *   $Log: dragonOldImageWriter.h,v $
 *   Revision 1.5  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.4  2005/08/18 03:48:36  rudahl
 *   fixes to scaling
 *
 *   Revision 1.3  2005/07/03 13:31:17  rudahl
 *   improving createImage
 *
 *   Revision 1.2  2005/06/26 06:18:15  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.1  2005/06/19 08:30:17  rudahl
 *   initial from mehitabel
 *
 *
 ****************************************************************
 * 
 * Define a class for writing old-format headers for Dragon image files.
 * Arguably this will be used only during a transition period.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *              san     San Ratanasanya
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-06-19 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 
 */

#if !defined DRAGOLDIMGWRTR_H
#define DRAGOLDIMGWRTR_H

class DragonOldImageWriter : public ImageWriter
    {
    public:
	DragonOldImageWriter(int iDebug=0, int iTrace=0);

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
	int rewriteHeader(const Image * pImage);

		// append trailer on the file 
		// @param pczFilename	name of file to write
		// @param pSrcHdr	pointer to IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
	int writeTrailer(const char * pczFilename,
			 const IMAGEHDR * pSrcHdr,UINT32 uDataCheck);

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

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
    private:
	        // make output image header agree with contents of passed
                // IMAGEHDR structure.
	        // @@param pDestHdr DHEAD-sized buffer 
                // @@param pSrcHdr  IMAGEHDR holding data to copy             
                // @@return        <0 if err (missing argument)
        int copyFields(IHEAD_OLD * pDestHdr, const IMAGEHDR * pSrcHdr);

	        // copy mapcoord structure
	void mapCoord_copy(const MapCoord * src, MapCoord_old * dest);
	/* following fn probably will never be needed for OldDragon */
        int convertHeaderClassNames(const IHEAD_OLD * pSrcHdr, 
				    size_t * pMaxLabelLen); 
	static const char * s_czTrailerNames[];
//	const IMAGEHDR * m_pHdr;
    } ;


#endif // DRAGOLDIMGWRTR_H
