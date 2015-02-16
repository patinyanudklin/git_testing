/*
 *	filename dragonImageReader.h
 *		$Revision: 1.20 $ $Date: 2015/01/21 10:37:33 $	
 *
 *      ~~ Copyright 2004-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: dragonImageReader.h,v 1.20 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: dragonImageReader.h,v $
 *   Revision 1.20  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.19  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.18  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.17  2014/03/28 14:54:33  rudahl
 *   working on auto import
 *
 *   Revision 1.16  2008/06/19 12:06:46  rudahl
 *   testing blob access
 *
 *   Revision 1.15  2007/03/23 07:21:29  goldin
 *   Fix syntax error
 *
 *   Revision 1.14  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.13  2006/08/20 11:04:52  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.12  2006/08/04 04:29:51  goldin
 *   Create new test for vector files in dragonImageReader
 *
 *   Revision 1.11  2005/12/10 11:36:53  rudahl
 *   fixing some of the double-tilde comments
 *
 *   Revision 1.10  2005/09/18 02:59:39  rudahl
 *   added colorfilename access
 *
 *   Revision 1.9  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.8  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.7  2005/02/10 23:21:56  rudahl
 *   added debug flags into constructors
 *
 *   Revision 1.6  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.5  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.4  2005/01/27 21:35:53  rudahl
 *   fixed enough to compile
 *
 *   Revision 1.3  2005/01/18 22:43:50  rudahl
 *   some fixes to typos
 *
 *   Revision 1.2  2005/01/18 22:03:19  san
 *   added private methods to convert new image header 
 *   structure to virtual structure
 *
 *   Revision 1.1  2005/01/03 05:28:56  rudahl
 *   init from Moochie
 *
 ****************************************************************
 * 
 * Define a class for reading new-format headers from Dragon image files.
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
 *      2005-01-16 san  create methods to transfer header from file to memory
 * 	2005-1-31 ktr	renamed/rescoped from HeaderReader
 * 5.7	2005-7-20 ktr	added getLineBufferSize()
 * 
 */

#if !defined DRAGIMGRDR_H
#define DRAGIMGRDR_H

class DragonImageReader : public ImageReader
    {
    public:
	DragonImageReader(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
	static BOOL test(const char * pczFilename, BOOL bTrace=FALSE);

              /* Factorization of test and vectest 
               * Checks to see if we have a Dragon 5.8 format
               * binary header or not.
               * @return TRUE if Dragon 5.8 format header
               */ 
        static BOOL testHeader(const char* pczFilename, BOOL bDebug);

		// return TRUE if specified file is a Dragon format vector 
                // file. This is based on the .vec extension, plus a possible
                // test of the header.
	static BOOL vectest(const char * pczFilename, BOOL bTrace=FALSE);

		// return TRUE if specified file is a Dragon IGC meta file that
                // can be handled by this class
		// This fn cannot be virtual since it's static
	static BOOL metatest(const char * pczFilename, 
						BOOL bDebug);


		// read the file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
	BOOL readHeader(FILE * pFile,IMAGEHDR * pHdr,int * pErrNum,
			Image * pImg = NULL);

		// how big a buffer do we need?
	size_t getLineBufferSize();

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
	/* ~~ these private sector need to be verified */ 
	IMGTYPE_T getImageType() const { return IT_DRAGON; } ;
	IMG_LAYOUT getImageLayout() { return IMG_PACKED1; } ;

    private:
	        // make image header agree with 'pSrcHdr'
	        // @@param pSrcHdr DHEAD-sized buffer (actually s_outbuf)
                //                 which has been filled from a file 
                // @@return        <0 if err (missing argument)
        int copyFields(const DRAGON_HEAD * pSrcHdr);
	        // copy mapcoord structure
	void mapCoord_copy(const HDR_MapCoord * src, MapCoord * dest);
	/* ~~ need to implement the following fn */
        int convertHeaderClassNames(const DRAGON_HEAD * pSrcHdr, size_t * pMaxLabelLen); 
//        IMAGEHDR * m_pHdr;
	BOOL readTrailer(FILE * pFile,int * pErrNum);

	// save the blob in an output but rereadable file
	int saveLinesBlob(const byte * pBlob,size_t uBlobSize);

	/* alloc and return a buffer filled with data from the trailer
	 * The returned buffer has a terminating 0 byte, in case the data
	 * is a string.
	 * @param pFile		file to read from
	 * @param pErrNum	where to store non-zero errors
	 * @param uDataLen	length of data
	 * @param ulOffset	absolute offset into file for data
	 * @return		calloc'd buffer, or NULL if error
	 */
	char * readTrailerData(FILE * pFile,int * pErrNum,
			       uint uDataLen, ulong ulOffset);

	char m_czBytes[5];
    } ;


#endif // DRAGIMGRDR_H
