/*
 *	filename imageStrip.h		- 
 *		$Revision: 1.6 $ $Date: 2014/02/09 04:27:08 $	
 *          derived from work Sally did exploring Gistda images
 *
 *      ~~ Copyright 2011-2014 Kurt Rudahl and Sally Goldin
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
 *
 ****************************************************************
 *
 *	Requirements:
 *	   
 *	   dtypes.h dlimits.h img.h
 *
 ****************************************************************
 *   $Id: imageStrip.h,v 1.6 2014/02/09 04:27:08 rudahl Exp $
 *   $Log: imageStrip.h,v $
 *   Revision 1.6  2014/02/09 04:27:08  rudahl
 *   lint
 *
 *   Revision 1.5  2011/09/14 02:56:16  rudahl
 *   fixed comments
 *
 *   Revision 1.4  2011/09/10 13:28:55  rudahl
 *   improving strip and OpenCL handling
 *
 *   Revision 1.3  2011/09/02 11:26:27  rudahl
 *   added stripcount explicitly
 *
 *   Revision 1.2  2011/06/08 02:11:29  rudahl
 *   added write, unit test
 *
 *   Revision 1.1  2011/06/03 10:07:56  rudahl
 *   from Raul
 *
 *
 ****************************************************************
 *
 *	Defines imageStrip class
 * 
 *	An imageStrip is intended to be a full image in memory
 *	With a modern OS, that should almost always be possible.
 *	However, the growing size of images to be processed,
 *	combined with the limited address space of a 32-bit
 *	processor, mean that sometimes it will be preferable
 *	to have only a (large, but less than entire) piece of
 *	multiple images in memory rather than all of just one image.
 *
 *	ImageStrip supports reading the entire image into a
 *	single memory buffer, but also permits it to be limited to 
 *	a full-width strip of lines with constrained memory size.
 *	ImageStrip buffers with the same image dimensions and
 *	memory constraint are guaranteed to be the same size.
 *
 *	Overlap support:
 *	  Some algorithms (e.g. convolution) require an input region 
 *	  somewhat larger than the output region, with an overlap
 *	  between successive strips. the parameter 'uBorderWidth'
 *	  provides this capability: the border data is read but 
 *	  not written, and the image line number and count refer 
 *	  to the real (non-border) lines. 
 *
 *	OpenCL support:
 *	  OpenCL requires each image 'element' is power of two
 *	    but 'element' not defined. Assume it to mean pixel.
 *	  Also, there is a maximum image width which can be as low 
 *	  as 8192. However, Dragon images can be up to 32K. 
 *	  See in OpenCL spec descriptions of CL_DEVICE_MAX_MEM_ALLOC_SIZE, 
 *		CL_DEVICE_MAX_IMAGE2D_WIDTH, _HEIGHT,
 *	  To support this, ImageStrip can automatically
 *	  separate the image data into multiple 'windows' with the
 *	  specified width. All windows of a strip are initialized
 *	  from the file, and written to a file, at the same time.
 *	  However, each is a separate memory buffer. (The memory
 *	  size constraint is applied to the collection of windows.)
 *	  If uBorderWidth > 0, it applies to the window left and right
 *	  also.
 *		
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 * 6.12	2011-05-30	created by extraction from memoryImage.c
 *************************************************************************
 *
 */

#ifndef IMAGESTRIP_H
#define IMAGESTRIP_H	/* signal this file has been loaded */

#define  OCL_DEFAULT_MAX_WINDOWS 5 /* might need 5 if img=32K && border > 0*/
#define  OCL_DEFAULT_MAX_WIDTH 8192

#ifdef __cplusplus

class ImageStrip : public OB // ~~~ should be private
    {
    public:
        // Create an ImageStrip for reading or writing.
        // For reading, it can be (?) any format that Dragon can read, 
        // including multiband (but only one band will be read)
        // @param pImage	Image we will read from or write to
	// @param bWrite	TRUE => write
	// @param pSel		if non-NULL, identifies part of
	//			multi-part image. Ignored ib bWrite
        // @param uBorderWidth	number of rows of extra data
        //			surrounding data. This data is read
	//			but not included in counts
        // @param uMaxMB	if > 0, limit amount of memory used
	//			actual amount will be rounded down to
        //			a whole number of image lines
        //			If uBorderWidth>0, the extra data
        //			is not included in this limit
        // @param bOpenCL	TRUE=>conforms to OpenCL requirements.
        //			(see above)
	// @param uMaxWidth	If bOpenCL true, maximum pixels in window
        //			(see above)
	// @param iDebug	debug level if > than set by OB::OB
	// @param iTrace	trace level if > than set by OB::OB
        ImageStrip(Image * pImage, BOOL bWrite,
		   const IMAGEDATA_SELECTOR * pSel = NULL,
		   uint uBorderWidth=0,uint uMaxMB=0, 
		   BOOL bOpenCL = FALSE,uint uMaxWidth=OCL_DEFAULT_MAX_WIDTH,
		   int iDebug=0, int iTrace=0);

        // Create an ImageStrip for writing
	// Result will be a single band image in Dragon format
        // @param uLines	total size of image to create 
        // @param uPixels	total size of image to create 
        // @param uBytesPerPix	total size of image to create 
        // @param uBorderWidth	number of rows of extra data
        //			surrounding data. This data does not
	//			get written and not included in counts
        // @param uMaxMB	if > 0, limit amount of memory used
	//			actual amount will be rounded down to
        //			a whole number of image lines
        // @param bOpenCL	TRUE=>conforms to OpenCL requirements.
        //			(see above)
	// @param uMaxWidth	If bOpenCL true, maximum pixels in window
        //			(see above)
	// @param iDebug	debug level if > than set by OB::OB
	// @param iTrace	trace level if > than set by OB::OB
        ImageStrip(uint uLines, uint uPixels, uint uBytesPerPix,
		   uint uBorderWidth=0,uint uMaxMB=0, 
		   BOOL bOpenCL = FALSE,uint uMaxWidth=OCL_DEFAULT_MAX_WIDTH,
		   int iDebug=0, int iTrace=0);

	// How many lines of data are actually in memory
	// Return 0 if not initialized
	uint getActualLines() const;

	// How many lines of data are the real strip
	// (excluding the border)
	// Return 0 if none
	uint getEffectiveLines() const;

	// What is the image line number of memory line[0]?
	// Return 0 if not initialized
	uint getImageFirstLine() const;

	// What will be image line number of next read
	// (ignoring borders)
	uint getNextImageLine() const;

	// Reset image line number of next read
	void resetNextImageLine();

	// What is the total number of lines in the image?
	// Return 0 if not initialized
	uint getImageTotalLines() const;

	// the following two fns are not really necessary
	// What is the depth of the data
	// Return 0 if not initialized
	uint getBytesPerPix() const;

	// What is the dimension of the data
	// (This is the line pitch, possibly larger than the line width.)
	// @return 		0 if not initialized
	// 			<0 if uWindow too big
	int getBytesPerLine(uint uWindow=0) const;

	// how many windows (0 if not OpenCL)
	uint getWindowsCount() const ;

	// how many strips are needed based on m_uMaxLines
	uint getStripCount() const ;

	// get the size of the buffer
	// @return		size in bytes, or 0
	ulong getBufferSize(uint uWindow=0) const;

	// @return		pointer to memory or NULL
	// 			(need to cast to byte or ushort)
	//			If null, use getErrorNo() for reason
	void * getBuffer(uint uWindow=0) const;

	// read next readable Strip
	// @return		actual lines read
	// 			or < 0 if error
	int read();

	// append a writable Strip to the current disk image
	// (not including uBorderWidth)
	// The ENTIRE buffer will be cleared after the write
	// @return		next image line number 
	//			(even if image is completed)
	// 			or < 0 if error
	int write();

	//
	BOOL isWrite() { return m_bWrite;};

	//	int getErrorNo(); // in ob

	~ImageStrip();

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => simplified
	 *			1 => normal
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
	const char * dump(int detail=1, const char * pczTitle=NULL) const;

        // allocate or clear the buffers as needed
	// This is a public fn because it MUST be called
	// once before a write()
	// It is not necessary before read(), because read() calls it anyway
	// @return	0, or < 0 if error
	int setupBuffers();

	// Do we have enough memory to make a single imageStrip
	// handle all needs?
	// This uses the same calculations as the ctor and setupBuffers,
	// then actually allocates and frees a buffer of the calculated size
	// 'static' because it should be called before any imageStrips
	// have been created
	// @param uLines, 	the obvious
	//	  uPixels,
	//	  uBytesPerPix	for the input bands
	// @param uBands	number of input bands. The calcs also
	//			allow for an output band, a mask image,
	//			and (for CLU) a previous iteration image
	// @return		TRUE if enough memory else false
	static BOOL isSingleStripPossible(uint uLines, uint uPixels,
					  uint uBytesPerPix, uint uBands);

	// If isSingleStripPossible() returns FALSE
	// then how should we set MaxMB to  get the biggest possible strip
	// Uses the same logic as isSingleStripPossible()
	// 'static' because it should be called before any imageStrips
	// have been created
	// @param uLines, 	the obvious
	//	  uPixels,
	//	  uBytesPerPix	for the input bands
	// @param uBands	number of input bands. The calcs also
	//			allow for an output band, a mask image,
	//			and (for CLU) a previous iteration image
	// @return		propppposed value for MaxMB
	static size_t calculateMaxMB(uint uLines, uint uPixels,
				     uint uBytesPerPix, uint uBands);

	// calculate and return a checksum of the 
	// specified buffer
	// utility fn
	static ulong sum(const byte * buf,uint usize);

    protected:
	ImageStrip(int iDebug=0,int iTrace=0);
	void zero();

	// member attributes are initialized by the ctors to values
	// based on supplied parameters.
	// Sometimes the constraints require changing their values
	// This fn does that
	void adjustAttributes(const uint uLines, const uint uPixels, 
			      const uint uBytes);


	Image * m_pImage;
	BOOL m_bWrite;
	uint m_uLines;
	uint m_uPixels;
	uint m_uBytesPerPix;
	uint m_uBorderWidth;
	IMAGEDATA_SELECTOR m_Sel;
	uint m_uMaxMB;
	// next two line counts include uBorderWidth if any
	uint m_uMaxLines; 	// max number of lines that will fit in buffer
	uint m_uActualLines; 	// m_uMaxLines except on last strip
	uint m_uCurrentImageLineNo; // image line number of first non-border ln
	uint m_uNextImageLineNo;    // what will become CurrentLine at next read
	uint m_uStripCount;	// how many strips needed based on m_uMaxLines
	uint m_uPitch[OCL_DEFAULT_MAX_WINDOWS]; 	// line pitch in bytes
	ulong m_ulBufferSize[OCL_DEFAULT_MAX_WINDOWS]; 	// how big is the buffer
	void * m_pBuffer[OCL_DEFAULT_MAX_WINDOWS];
	static Class s_class_Base;
	// following only relate to OpenCL compat.
	BOOL m_bOpenCL;
	uint m_uWindows;
	uint m_uMaxWidth;
    } ;

#endif // #ifdef __cplusplus
#endif // #ifndef IMAGESTRIP_H
