/*
 *	filename imageReader.h
 *		$Revision: 1.21 $ $Date: 2015/01/21 10:39:37 $	
 *
 *      ~~ Copyright 1985-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: imageReader.h,v 1.21 2015/01/21 10:39:37 rudahl Exp $
 *   $Log: imageReader.h,v $
 *   Revision 1.21  2015/01/21 10:39:37  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.20  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.19  2014/12/07 04:30:59  rudahl
 *   adapt for OpenDragon
 *
 *   Revision 1.18  2014/12/06 11:31:02  rudahl
 *   conditional changes for OpenDragon
 *
 *   Revision 1.17  2014/12/05 11:51:02  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.16  2014/04/01 07:24:45  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.15  2014/03/28 15:00:51  rudahl
 *   working on auto import
 *
 *   Revision 1.14  2014/02/09 04:27:08  rudahl
 *   lint
 *
 *   Revision 1.13  2010/12/19 06:57:40  rudahl
 *   getauxInfo
 *
 *   Revision 1.12  2008/06/19 12:11:48  rudahl
 *   testing blob access
 *
 *   Revision 1.11  2008/06/14 10:15:55  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.10  2006/12/31 12:15:22  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.9  2006/11/20 13:31:28  rudahl
 *   added IMAGEDATA_SELECTOR arg to open
 *
 *   Revision 1.8  2006/08/14 06:31:01  rudahl
 *   improvements to support bilEsri incl new arg to CalcImageFileOffsets
 *
 *   Revision 1.7  2005/09/17 05:40:16  rudahl
 *   improved dump, trace, docs; ProcessRect
 *
 *   Revision 1.6  2005/07/22 15:19:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.5  2005/06/26 06:18:29  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.4  2005/02/10 04:59:39  rudahl
 *   cleaned up tracing and error reporting
 *   cleaned up image file writing
 *
 *   Revision 1.3  2005/02/03 03:24:00  rudahl
 *   work on implementing new create(), getImageLine etc in img class
 *   plus beginning of standardized error numbers
 *
 *   Revision 1.2  2005/02/01 01:41:48  rudahl
 *   cvt from header r/w to image r/w
 *
 *   Revision 1.1  2005/01/31 16:18:10  rudahl
 *   initial from moochie
 *
 *   Revision 1.7  2005/01/27 21:37:21  rudahl
 *   writer now has const struct
 *
 *   Revision 1.6  2005/01/27 16:09:14  rudahl
 *   enhanced testing
 *
 *   Revision 1.5  2005/01/26 01:51:13  rudahl
 *   added typenames, tracing
 *
 *   Revision 1.4  2005/01/20 19:39:20  rudahl
 *   added image type defns
 *
 *   Revision 1.3  2005/01/18 18:22:41  rudahl
 *   added IMG_LAYOUT and pitch params
 *
 *   Revision 1.2  2005/01/05 02:26:28  rudahl
 *   add s_class_Base
 *
 *   Revision 1.1  2005/01/04 15:48:59  rudahl
 *   initial from moochie
 *
 ****************************************************************
 * 
 * This file defines a base class for reading image files
 *
 *	This file requires dtypes.h
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-31 ktr	extracted from dhead.h
 * 5.7	2005-06-25 ktr	moved pFp here from img.h
 *	2005-7-20 ktr	added getLineBufferSize and IMAGEDATA_SELECTOR
 *	2005-9-17 ktr	enhanced dump()
 * 5.9	2006-8-12 ktr	added pDataSel to CalcImageFileOffset
 * 5.11	2008-06-14 ktr	added LinesBlob to trailer
 * 6.1	2010-12-18 ktr	added virtual getAuxInfo()
 * 6.4	2014-02-01 ktr	for subclasses in rosetta, permit fns to
 *			return DERR_FN_NOTIMPL
 */

#if ! defined IMAGERDR_H
#define IMAGERDR_H	/* signal this file has been loaded */

#define READER_DUMPBUF_SIZE 2048

/* Define a base class for reading from real image files.
 */
class ImageReader : public OB
    {
    public:
	ImageReader(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
		// This should also set s_iNumBands which can be retrieved
		// by getNumBands()
	//static BOOL test(const char * pczFilename);

		// read the file based on filename
		// The base class implementation (which invokes the other
		// readHeader) is usually enough,
		// but can be overridden if necessary
		// @param pczFilename	name of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		some readers may need this
		// @return		TRUE if OK
	virtual BOOL readHeader(const char * pczFilename,
				IMAGEHDR * pHdr,
				int * pErrNum, Image * pImg = NULL);

		// read an already-open file. 
		// MUST be implemented in subclass
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		some readers may need this
		// @return		TRUE if OK
	virtual BOOL readHeader(FILE * pFile,
				IMAGEHDR * pHdr,
				int * pErrNum, Image * pImg = NULL) = 0;

	/*	Calc byte offset into file of specified image line,
	 *	The base class calcs are OK for file formats where
	 *	line offsets follow sequentially from ulDataOffset
	 *	or can be overridden in subclasses.
	 *
	 * 	@param uLineNo	line number to seek
	 *	@param pImage	ptr to IMAGE (must be non-NULL)
	 *			  pImage is ref'd but not altered	
	 *	@param pDataSel permits passing e.g. band number
	 *			not used for Dragon, but is used for e.g. BIL
	 * 	@return		>= 0: offset
	 *			-99 = DERR_FN_NOTIMPL
	 */
	virtual long CalcImageFileOffset(uint uLineNo, const IMAGE * lpImage,
		 			  IMAGEDATA_SELECTOR * pDataSel=NULL);

	/*	Retrieve a line of raw data from the appropriate
	 *	location into buffer. 
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to Image
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			   -51  open error
	 *			   -53  read error
	 *			   -56  past EOF ?
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 *			   -99 = DERR_FN_NOTIMPL
	 *			     or errors from fread, fseek
	 *			 ( return 0 => line is outside ProcessRect;
	 *			     or errors from fread, fseek
	 */
	virtual int getImageLineRaw(byte * pBuf, const ushort uLineNo,
				    const size_t uBufSize, const Image * pImg,
				    IMAGEDATA_SELECTOR * pDataSel = NULL);

	/*	Retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The base class (which calls getImageLineRaw() calcs are OK 
	 *	for file formats where lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *	NOTE this fn (and any overloaded fns) does not and should not
	 *	     enforce ProcessRect
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *			   -51  open error
	 *			   -53  read error
	 *			   -56  past EOF ?
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 *			   -99 = DERR_FN_NOTIMPL
	 *			     or errors from fread, fseek
	 */
	virtual int getImageLine(byte * pBuf, const ushort uLineNo,
				 const size_t uBufSize, const Image * pImg,
				 IMAGEDATA_SELECTOR * pDataSel = NULL);

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;

	IMAGEHDR * getImageHeader() { return m_pHdr; } ;
	virtual IMGTYPE_T getImageType() const = 0;
	virtual IMG_LAYOUT getImageLayout() = 0;

		// how big a buffer do we need?
		// (This actually returns size for a full line of read data,
		// regardless of multiband and scaling considerations.)
	virtual size_t getLineBufferSize() = 0;

		// if m_pFp is open, close it
		// @return	0 if not open or successful close
		//		else close() error status
	virtual int close();
		// return the m_pFp
	const void * getFp() const { return m_pFp; } ;

	void SetDesiredData(const IMAGEDATA_SELECTOR * pSel);

//	void setTrace(BOOL bTrace) { s_bTrace = bTrace;};
	static const Class * getBaseClass() { return &s_class_Base;};

	    /* if non-NULL, ptr to blob of vector data */
#if DRAGON_VER >= 6
	byte * getLinesBlob() { return m_puLinesBlob; } ;
   	    /* number of BYTES in LinesBlob */
	size_t getLinesBlobLen() { return m_uLinesBlobLen; } ;

	int saveLinesBlob(const byte * pBlob,size_t uBlobSize);
#endif

	friend ImageReader * ImageHdr::imageReaderFactory(const char * pName);

#if DRAGON_VER >= 6
	/* Get some sort of device-dependent info.
	 * initial implementation is for tiffImageReader  (q.v.)
	 *   where pczName names, or uId identifies one of a few possible tags
	 * @return	desired value as a string, or NULL
	 */
	virtual const char * getAuxInfo(const char * pczName) const { return NULL; };
	virtual const char * getAuxInfo(uint uId) const { return NULL; };
#endif
	/* return number of bands if known. 0 => not known; DERR_FN_NOTIMPL is default */
	static int getNumBands() { return s_iNumBands; } ;
    protected:
	IMAGEHDR * m_pHdr;	/* structure in ImageHdr - set in readHeader() */

		// m_pFp is normally a FILE *, but may be different in some
		// derived classes. Therefore, specify as 'void' 
		// and cast as needed
	void * m_pFp;
	IMAGEDATA_SELECTOR m_DesiredData; // needed to properly open multi-band files
	    /* if non-NULL, ptr to blob of vector data */
	byte * m_puLinesBlob;
   	    /* number of BYTES in LinesBlob */
	size_t m_uLinesBlobLen;
	static char s_czDumpBuf[READER_DUMPBUF_SIZE];
	static int s_iNumBands;     // used by extern and all importers; found by test()
    private:
	static Class s_class_Base;
    } ;

#endif // if ! defined IMAGERDR_H
