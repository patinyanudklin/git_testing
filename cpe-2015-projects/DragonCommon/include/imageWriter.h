/*
 *	filename imageWriter.h
 *		$Revision: 1.20 $ $Date: 2014/12/29 03:28:29 $	
 *
 *      ~~ Copyright 1985-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: imageWriter.h,v 1.20 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: imageWriter.h,v $
 *   Revision 1.20  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.19  2014/12/06 11:31:02  rudahl
 *   conditional changes for OpenDragon
 *
 *   Revision 1.18  2014/12/05 11:51:02  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.17  2011/01/03 06:28:47  rudahl
 *   fixes for tiffImageWriter handling-virtual close
 *
 *   Revision 1.16  2010/12/25 02:17:10  rudahl
 *   annotation
 *
 *   Revision 1.15  2008/06/14 10:15:55  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.14  2006/12/31 12:15:22  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.13  2006/08/14 06:31:01  rudahl
 *   improvements to support bilEsri incl new arg to CalcImageFileOffsets
 *
 *   Revision 1.12  2005/09/17 05:40:16  rudahl
 *   improved dump, trace, docs; ProcessRect
 *
 *   Revision 1.11  2005/07/22 15:19:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.10  2005/07/03 13:28:56  rudahl
 *   improving createImage
 *
 *   Revision 1.9  2005/06/26 06:18:29  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.8  2005/03/19 08:03:06  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.9  2005/03/16 04:07:34  rudahl
 *   fixing writeTrailer tests
 *
 *   Revision 1.8  2005/03/10 22:41:56  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.7  2005/03/10 03:18:31  goldin
 *   Still working on img_acc test code
 *
 *   Revision 1.6  2005/03/03 16:15:43  rudahl
 *   refinements while converting grstop
 *
 *   Revision 1.5  2005/03/01 16:05:21  rudahl
 *   changed writeTrailer
 *
 *   Revision 1.4  2005/02/10 04:59:39  rudahl
 *   cleaned up tracing and error reporting
 *   cleaned up image file writing
 *
 *   Revision 1.3  2005/02/07 05:41:08  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.2  2005/02/03 03:24:00  rudahl
 *   work on implementing new create(), getImageLine etc in img class
 *   plus beginning of standardized error numbers
 *
 *   Revision 1.1  2005/01/31 16:18:10  rudahl
 *   initial from moochie
 *
 *
 ****************************************************************
 * 
 * This file defines a base class for writing image files
 *
 *	This file requires dtypes.h, dragon-errors.h
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-31 ktr	extracted from dhead.h
 *	2005-02-02 ktr	added rewriteHeader, dragon-errors
 * 5.7	2005-06-25 ktr	moved pFp here from img.h
 *	2005-9-17 ktr	enhanced dump()
 * 5.9	2006-8-12 ktr	added pDataSel to CalcImageFileOffset
 */

#if ! defined IMAGEWRTR_H
#define IMAGEWRTR_H	/* signal this file has been loaded */

#define WRITER_DUMPBUF_SIZE 2048
/* Define a base class for writing to real image files.
 */
class ImageWriter : public OB
    {
    public:
	ImageWriter(int iDebug=0, int iTrace=0);

		// write to the file 
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct to write
		// @param pErrNum	pointer to variable to receive errnum
		// @return		TRUE if OK
	virtual BOOL writeHeader(const char * pczFilename,
				 const IMAGEHDR * pHdr,
				 int * pErrNum) = 0;

		// rewrite selected header info if changed
		// @return		TRUE if OK
	virtual int rewriteHeader(const Image * pImg) = 0;

		// append trailer on the file : closed on return
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
	virtual int writeTrailer(const char * pczFilename,
				 const IMAGEHDR * pHdr,
				 UINT32 uDataCheck) = 0;

		/* overwrite any IMAGEHDR values necessary for 
		 * this format by calling pImageheader->revise_geom()
		 * @param pImageHdr	pointer to ImageHdr
		 * @param plOffset	init sets offset of start of image
		 *			data, or -1;
		 * @return		0 if OK else:
		 *			-40 uBitsPerPix is unsupported
		 *			-41 uNumBands is unsupported
		 *			-42 uNumResolutions is unsupported
		 */
	virtual int init(ImageHdr * pImageHdr,long * plOffset) = 0;

	/*	Calc byte offset into file of specified image line,
	 *	The base class calcs are OK for files where
	 *	line offsets follow sequentially from ulDataOffset
	 *	or can be overridden in subclasses.
	 *
	 * 	@param uLineNo	line number to seek
	 *	@param pImage	ptr to IMAGE (must be non-NULL)
	 *			  pImage is ref'd but not altered	
	 *	@param pDataSel permits passing e.g. band number
	 *			not used for Dragon, but is used for e.g. BIL
	 * 	@return		offset > 0 if success
	 *			0 if line number out of range
	 * 			< 0 if error:
	 *			    -60 if not valid for this format
	 *			    -61 if line # beyond current EOF
	 */
	virtual long CalcImageFileOffset(uint uLineNo, const IMAGE * pImage,
			      IMAGEDATA_SELECTOR * pDataSel=NULL);

	/*	Put a line of raw data to the file
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *	ProcessRect is ignored.
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
	virtual int putImageLineRaw(const byte * pBuf, ushort uLineNo,
				    size_t uBufSize, const IMAGE * pImg,
				    BOOL bReReadable);

	/*	Put a line of pixels to the file
	 *	The base class calcs are OK for file formats where
	 *	lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *	Ignores ProcessRect.
	 *
	 *	@param pBuf	pointer to the data buffer
	 *	@param uLineNo	image memory line to write
	 *	@param uBufSize	the size of pBuf - i.e. how much data to write
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param bReReadable  TRUE => we may be reading/writing mixed
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			   0 => line is outside ProcessRect;
	 *			   -51  file open error
	 *			   -52  seek error
	 *			   -53  write error
	 *			   -55  file not open 
	 *			   -56  trying to write past end-of-file
	 *			   -75  buffer size doesn't match image line
	 *			   -91  line number bigger than image
	 *			     or errors from fwrite, fseek
	 */
	virtual int putImageLine(const byte * pBuf, ushort uLineNo,
				 size_t uBufSize, const IMAGE * pImg,
				 BOOL bReReadable);

	/* return how many bytes will be needed for one line of raw data
	 */
	virtual size_t getRawImageLineSize(size_t uPixels);

	/* calc and return the size of the header plus image data, or 0
	 * This cannot be done until the header has been written
	 */
	virtual ulong getTrailerOffset() const = 0;

#if DRAGON_VER >= 6
	/* this has to do with vector data, somehow
	 */
	virtual int setLinesBlob(const byte * pBlob,size_t uBlobSize);
#endif
		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;

//	static void setTrace(BOOL bTrace) { s_bTrace = bTrace;};

	/* if m_pFp is open, close it
	 * @return	0 if not open or successful close
	 *		else close() error status
	 */
	virtual int close();
	const IMAGEHDR * getImageHeader() { return m_pHdr; } ;

	static const Class * getBaseClass() { return &s_class_Base;};
	    /* COPY the blob */
//	friend ImageWriter * ImageHdr::imageWriterFactory(IMGTYPE_T uFormat);
#if DRAGON_VER >= 6
	virtual ~ImageWriter();
#endif
    protected:
	UINT32 m_uHeaderChecksum;
	/* m_pFp is normally a FILE *, but may be different in some
	 * derived classes. Therefore, specify as 'void' and cast as needed
	 */
	void * m_pFp;
	const IMAGEHDR * m_pHdr;	/* structure in ImageHdr */
	static char s_czDumpBuf[WRITER_DUMPBUF_SIZE];
	byte * m_puLinesBlob;	/* if non-NULL, ptr to blob of vector data */
	size_t m_uLinesBlobLen;	/* number of BYTES in LinesBlob */
    private:
	static Class s_class_Base;
    } ;

#endif // if ! defined IMAGEWRTR_H
