/*
 *	filename dragonOldImageReader.h
 *		$Revision: 1.14 $ $Date: 2015/01/21 10:37:33 $	
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
 *   $Id: dragonOldImageReader.h,v 1.14 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: dragonOldImageReader.h,v $
 *   Revision 1.14  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.13  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.12  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.11  2014/03/28 14:54:33  rudahl
 *   working on auto import
 *
 *   Revision 1.10  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.9  2005/09/12 12:18:39  goldin
 *   Fixing version inconsistencies
 *
 *   Revision 1.8  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.7  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
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
 *   Revision 1.4  2005/01/26 02:02:31  rudahl
 *   improved field conversions
 *
 *   Revision 1.3  2005/01/05 02:05:15  rudahl
 *   finished making it dhead build and test right
 *
 *   Revision 1.2  2005/01/04 16:04:31  rudahl
 *   fixed prototype mismatches to .cpp
 *
 *   Revision 1.1  2005/01/03 05:28:56  rudahl
 *   init from Moochie
 *
 ****************************************************************
 * 
 * Define a class for reading old-format headers from Dragon image files.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-01 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 	2005-1-31 ktr	renamed/rescoped from HeaderReader
 * 5.7	2005-7-20 ktr	added getLineBufferSize()
 */

#if !defined DRAGOLDIMGRDR_H
#define DRAGOLDIMGRDR_H

class DragonOldImageReader : public ImageReader
    {
    public:
	DragonOldImageReader(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
	static BOOL test(const char * pczFilename,BOOL bDebug=FALSE);

		// read the file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
	virtual BOOL readHeader(FILE * pFile,IMAGEHDR * pHdr,
				int * pErrNum, Image * pImg = NULL);

	         /* how big a buffer do we need? */
	size_t getLineBufferSize();

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
	IMGTYPE_T getImageType() const { return IT_DRAGON_OLD; } ;

	IMG_LAYOUT getImageLayout() { return IMG_PACKED1; } ;
    private:

		// make ImageHdr agree with 'pSrcHdr'
		// @param pSrcHdr	DHEAD-sized buffer (actually s_outbuf)
		//			which has been filled from a file
		// @return		< 0 if err (missing argument)
	int copyFields(IHEAD_OLD * pSrcHdr);

		// copy mapcoord structure
	void mapCoord_copy(const MapCoord_old * src,MapCoord * dest);

		// convert classnames read from file to current form.
	    	// Most importantly, Unicode-ify old classnames
		// @param pSrcHdr	DHEAD-sized buffer (actually s_outbuf)
		//			which has been filled from a file
		// @param puMaxLabelLen	??
		// @return		< 0 if err (none currently known)
		// 			or actual number of classnames found .
	int convertHeaderClassnames(IHEAD_OLD * pSrcHdr,
				    size_t * puMaxLabelLen);

		/*	make sure all version-specific info is set consistently
		 *      used here and in imagsw-o.c.
		 */
	void SetHdrToCurrent(IHEAD_OLD * hdr);

		/*	fixup older hdrs to 4.1. This assumes the fields
		 *	being set did not contain useful info.
		 */
	void SetHdrTo401(IHEAD_OLD * hdr);

	static Class s_class_Base;
    } ;


#endif // DRAGOLDIMGRDR_H
