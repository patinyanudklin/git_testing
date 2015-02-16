/*
 *	filename screenImageReader.h
 *		$Revision: 1.11 $ $Date: 2015/01/21 10:37:33 $	
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
 *   $Id: screenImageReader.h,v 1.11 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: screenImageReader.h,v $
 *   Revision 1.11  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.10  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.9  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.8  2014/03/28 14:54:33  rudahl
 *   working on auto import
 *
 *   Revision 1.7  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.6  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.5  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.4  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.3  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.2  2005/01/29 17:22:27  rudahl
 *   working now apparently
 *
 *   Revision 1.1  2005/01/26 02:04:00  rudahl
 *   initial from moochie
 *
 *
 ****************************************************************
 * 
 * Define a class for reading headers from screen (chunk) files.
 * This code is extracted from viewport/cinfo, graf/windrv, etc
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-21 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 	2005-1-31 ktr	renamed/rescoped from HeaderReader
 * 5.7	2005-7-20 ktr	added getLineBufferSize()
 */

#if !defined CHUNKIMGRDR_H
#define CHUNKIMGRDR_H

#if defined  _WIN32 || defined MSC || defined __GCC__
#pragma pack(1)
#endif

class ScreenImageReader : public ImageReader
    {
    public:
	ScreenImageReader(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
	static BOOL test(const char * pczFilename,BOOL bTrace=FALSE);

		// read the file 
		// @param pFile		file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
	virtual BOOL readHeader(FILE * pFile,IMAGEHDR * pHdr,
				int * pErrNum, Image * pImg = NULL);

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;

	IMGTYPE_T getImageType() const { return IT_CHUNK54; } ;
	IMG_LAYOUT getImageLayout() { return IMG_PIL; } ;

		// how big a buffer do we need? 
	size_t getLineBufferSize();

	~ScreenImageReader();
    private:

		// make IMAGEHDR agree with 'pSrcHdr'
		// @param pSrcHdr	DHEAD-sized buffer (actually s_outbuf)
		//			which has been filled from a file
		// @return		< 0 if err (missing argument)
//	int copyFields(const IHEAD_OLD * pSrcHdr);

		// copy mapcoord structure
//	void mapCoord_copy(const MapCoord_old * src,MapCoord * dest);

		// convert classnames read from file to current form.
	    	// Most importantly, Unicode-ify old classnames
		// @param pSrcHdr	DHEAD-sized buffer (actually s_outbuf)
		//			which has been filled from a file
		// @param puMaxLabelLen	??
		// @return		< 0 if err (none currently known)
		// 			or actual number of classnames found .
//	int convertHeaderClassnames(const IHEAD_OLD * pSrcHdr,
//				    size_t * puMaxLabelLen);

	CHUNK_FILE_HDR m_FileHdr;
	CHUNK_HDR * m_pChunkHdr;	// array of chunk headers 
					// in same sequence as in file
	static Class s_class_Base;
	static const char * s_czInfTypes[];
    } ;


#if defined  _WIN32 || defined MSC || defined __GCC__
#pragma pack()
#endif

#endif // CHUNKIMGRDR_H
