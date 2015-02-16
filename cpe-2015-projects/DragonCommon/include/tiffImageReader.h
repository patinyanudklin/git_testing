/*
 *	filename tiffImageReader.h
 *		$Revision: 1.15 $ $Date: 2015/01/21 10:39:37 $	
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
 *   $Id: tiffImageReader.h,v 1.15 2015/01/21 10:39:37 rudahl Exp $
 *   $Log: tiffImageReader.h,v $
 *   Revision 1.15  2015/01/21 10:39:37  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.14  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.13  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.12  2014/03/28 14:54:33  rudahl
 *   working on auto import
 *
 *   Revision 1.11  2014/03/08 06:01:04  rudahl
 *   make dtor public
 *
 *   Revision 1.10  2014/01/27 12:21:40  rudahl
 *   adapt to tiles, -a
 *
 *   Revision 1.9  2011/02/27 08:24:51  rudahl
 *   final work on tiff IO
 *
 *   Revision 1.8  2011/02/03 14:21:48  rudahl
 *   fix georef with only intergraph and autodesk tags
 *
 *   Revision 1.7  2011/01/30 01:54:41  rudahl
 *   geotiff import works OK now
 *
 *   Revision 1.6  2010/12/19 06:56:58  rudahl
 *   fix some docs
 *
 *   Revision 1.5  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.4  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.3  2005/07/18 12:56:36  rudahl
 *   work on geotiff
 *
 *   Revision 1.2  2005/07/09 06:24:08  rudahl
 *   working on tiff
 *
 *   Revision 1.1  2005/07/07 15:22:41  rudahl
 *   initial from mooochie
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
 * 5.7	2005-07-07 ktr	new
 * 6.1	2010-12-18 ktr	added getAuxInfo()
 */

#if !defined TIFFIMGRDR_H
#define TIFFIMGRDR_H

class TiffImageReader : public ImageReader
    {
    public:
	TiffImageReader(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
	static BOOL test(const char * pczFilename,BOOL bDebug=FALSE);

		// read header of a not-already-open file 
		// @param pczFileName	name of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
	BOOL readHeader(const char * pczFileName,
			IMAGEHDR * pHdr,int * pErrNum, Image * pImg = NULL);

		// read header of an already-open file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		don't need this
		// @return		TRUE if OK
	BOOL readHeader(FILE * pFile,IMAGEHDR * pHdr,int * pErrNum,
			Image * pImg = NULL);

	int getImageLine(byte * pBuf, ushort uLineNo,
			 size_t uBufSize, const Image * pImage,
			 IMAGEDATA_SELECTOR * pDataSel);

	int getImageLineRaw(byte * pBuf, ushort uLineNo,
			 size_t uBufSize, const Image * pImage,
			 IMAGEDATA_SELECTOR * pDataSel);

	         /* how big a buffer do we need? */
	size_t getLineBufferSize() { return m_readLineBufferSize; } ;

	/* if m_pFp is open, close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
	int close();

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
	IMGTYPE_T getImageType() const { return IT_TIFF; } ;
	IMG_LAYOUT getImageLayout() { return m_pHdr->uBandLayout; } ;

	/* Get some sort of device-dependent info.
	 * initial implementation is for tiffImageReader  (q.v.)
	 *   where pczName names, or uId identifies, one of a few possible tags
	 * These will NOT be valid until header is read;
	 * @return	desired value as a string, or NULL
	 */
	const char * getAuxInfo(const char * pczName) const;
	/* if uId == TIFFTAG_PLANARCONFIG or PHOTOMETRIC, return value by name 
	 * @return	see values in implementation
	 */
	const char * getAuxInfo(uint uId) const;

    public:
	~TiffImageReader() { if (s_pTilesBuf != NULL) free(s_pTilesBuf); };

    private:
		// make ImageHdr agree with 'pSrcHdr'
		// @param pTif		open TIFF handle
		// @return		< 0 if err (missing argument)
	int copyFields(void * pTif);

		// try to get tie points using proj4 based on uZone and cZone 
		// assumes m_pHdr->..ModelTiePoints copied from TIFF file
		// return 0 on success
	int _getTiePointsFromProj4(uint uZone);

		// copy tie points from TIFF file into m_pHdr
		// and rearragne them into a standard sequence 
		// if there are four
		// tiepoint_count is 6 * number of tiepoints (!)
		// set *pcZone, *pdLongitude
		// return < 0 if error
		// else  1 if the coords seem to be already in UTM form, else 0
	int _copyTiePoints(int tiepoint_count,double * tiepoints,
			   char * pcZone, double * pdLongitude);

		// put fixed point and pixel size, calculated from tilepoints, 
		// into header
		// return 0
	int _recordFixedPointsAndPixelSize(int tiepoint_count,
					   BOOL bCellSizeCalcd);

	int _getTiePoints(void * pgInfo,
			  int tiepoint_count, double * tiepoints, 
			  uint * puZone, char * pcZone,
			  BOOL bCellSizeCalcd);

	size_t m_readLineBufferSize;  /* how big a buffer do we need? */

	static Class s_class_Base;
	int m_iPlanar; // >0 => PLANARCONFIG tag value else not init
	int m_iPhoto; // >=0 => PHOTOMETRIC tag value else not init
	static byte * s_pTilesBuf;
	static uint s_uFirstLineInTileRow;
    } ;

#endif // TIFFIMGRDR_H
