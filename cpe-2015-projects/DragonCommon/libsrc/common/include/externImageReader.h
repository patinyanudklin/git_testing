/*
 *	filename externImageReader.h
 *		$Revision: 1.12 $ $Date: 2015/01/21 10:37:33 $
 *
 *      ~~ Copyright 2006-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: externImageReader.h,v 1.12 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: externImageReader.h,v $
 *   Revision 1.12  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.11  2015/01/02 03:16:27  rudahl
 *   fix Dragon/OpenDragon conditional
 *
 *   Revision 1.10  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.9  2014/12/06 11:27:44  rudahl
 *   conditional changes for OpenDragon
 *
 *   Revision 1.8  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.7  2014/12/05 07:07:18  rudahl
 *   added close() importBands()
 *
 *   Revision 1.6  2014/04/01 07:27:57  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.5  2014/03/28 14:54:33  rudahl
 *   working on auto import
 *
 *   Revision 1.4  2008/04/26 10:55:55  rudahl
 *   improved notices
 *
 *   Revision 1.3  2007/01/29 10:36:02  rudahl
 *   better propagation of iTrace,iDebug
 *
 *   Revision 1.2  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.1  2006/11/20 13:29:20  rudahl
 *   added externImageReader
 *
 *
 ****************************************************************
 * 
 * Define a class for reading miscellaneous image files by
 * using external executables.
 * 
 * The read functions are implemented indirectly:
 *  the first invocation causes the external executable to 
 *  read an entire band into a buffer file, which is then
 *  accessed line by line from this driver
 *
 * Each external executable must support a command line of the 
 * following forms:
 *    xxx.exe -b # -o outfile infile	read a band
 *    xxx.exe -t infile			test file, returning errstat=bandcount
 *					   or 0 if not recognized
 *    xxx.exe -d infile			dump file params to stdout
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.9	2006-11-21 ktr	created
 * 
 */

#if !defined EXTERNIMGRDR_H
#define EXTERNIMGRDR_H

// subclass DragonImageReader to be able to call DragonImageReader::readHeader()?
#if DRAGON_VER >= 6
class ExternImageReader : public ImageReader
#else
class ExternImageReader : public DragonImageReader
#endif
    {
    public:
	ExternImageReader(int iDebug=0, int iTrace=0);

		// return TRUE if specified file can be handled by this class
		// This fn cannot be virtual since it's static
		// This also sets s_uNumBands which can be retrieved
		// by getNumBands()
	static BOOL test(const char * pczFilename, 
			 BOOL bTrace=FALSE,int iTrace=0);

		// read the metadata file 
		// @param pczImageFile	name of image file
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		do need this
		// @return		TRUE if OK
	BOOL readHeader(const char * pczImagefile,IMAGEHDR * pHdr,
			int * pErrNum, Image * pImg = NULL);

		// read the file 
		// @param pFile		handle of file to read
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		// @param pImg		do need this
	BOOL readHeader(FILE * pFile,IMAGEHDR * pHdr,int * pErrNum,
			Image * pImg = NULL);

		/*	Retrieve a line of pixels from the appropriate
		 *	location into buffer. 
		 *	The base class calcs are OK for file formats where
		 *	lines are sequential pixel data
		 *	or can be overridden in subclasses.
		 *	The image data may be 16-bit data.
		 *	NOTE this fn (and any overloaded fns) 
		 *	    does not and should not enforce ProcessRect
		 *
		 *	@param pBuf	pointer to the destination data buffer
		 *	@param uLineNo	image memory line to retrieve data
		 *	@param uBufSize	the size of pBuf
		 *	@param pImg	pointer to IMAGE struct
		 * 	@param pDataSel	NULL or selects data to read
		 *	@return 	number of pixels transferred 
		 *			or <= 0 if error
		 *		 ( return 0 => line is outside ProcessRect;
		 *		   -51  open error
		 *		   -53  read error
		 *		   -56  past EOF ?
		 *		   -63  buffer size too small for image line
		 *		   -91  line number bigger than image
		 *		     or errors from fread, fseek
		 */
	int getImageLine(byte * pBuf, const ushort uLineNo,
				 const size_t uBufSize,const Image * pImg,
				 IMAGEDATA_SELECTOR * pDataSel = NULL);

		/* if m_pFp is open it's a DragonImageReader, close it
		 * NOTE this is different from the base class implementation
		 * @return	0 if not open or successful close
		 *		else close() error status
		 */
	int close();

		/* import one or all bands of a file
		 * @param pczInfile		path and name of file to convert
		 * @param pczOutfilePattern	path and pattern for output file name
		 * @param bScale		TRUE => use auto-scaling
		 * @param iOutBand		-1 => all bands, or band to convert
		 * @param pczComment		NULL or comment to put in header
		 *				NOTE not all importers support this
		 * @return 			0 for success, 
		 *				DERR_FGN_NOTCONVERTED (-102 )
		 *				DERR_SPAWN_ERROR (-111)	
		 */
	int importBands(const char * pczInfile, const char * pczOutfilePattern, 
			BOOL bScale, int iOutBand, const char * pczComment);

		// how big a buffer do we need?
	size_t getLineBufferSize();

		// return a formatted dump of the class member
	const char * dump(int detail=6, const char * czTitle=NULL) const;
	IMGTYPE_T getImageType() const { return IT_EXTERN; } ;
	static const char * getImporter() { return s_pLatestImporter; } ;
    private:
	IMG_LAYOUT getImageLayout() { return IMG_UNKNOWN; } ;
	/** use the currently known importer fn to extract a band into kpath
	 *  @return	0 if success
	 */
	int _extract_band(const char * pczImagefile,int iBandNo);
	static char * s_pLatestImporter; 
	static char s_czRawImage[PATH_MAX]; // the name of the non-Dragon file
	BOOL m_bImageUpdated;
//#if DRAGON_VER >= 6
	static uint s_uNumBands;     // ~~~ should be found by test()
//#endif
	static Class s_class_Base;
    } ;

#endif // EXTERNIMGRDR_H
