#include "drelease.h"
char SCRNIMAGEWRTR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.25 $$Date: 2014/12/29 03:28:29 $";
D_REL_IDSTR;

/*
 *	filename screenImageWriter.cpp
 *		$Revision: 1.25 $ $Date: 2014/12/29 03:28:29 $	
 *
 *      ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: screenImageWriter.cpp,v 1.25 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: screenImageWriter.cpp,v $
 *   Revision 1.25  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.24  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.23  2014/04/02 12:02:22  rudahl
 *   finished separating dtk,rosetta to new mingw version adaptations for Linux build
 *
 *   Revision 1.22  2011/12/30 11:54:37  rudahl
 *   lint
 *
 *   Revision 1.21  2011/12/16 09:35:10  rudahl
 *   add jpeg for Linux, https web communications
 *
 *   Revision 1.20  2011/12/13 13:32:36  rudahl
 *   write chunk file in linux actually creates JPG
 *
 *   Revision 1.19  2008/04/05 11:46:24  rudahl
 *   tracing
 *
 *   Revision 1.18  2005/09/17 05:25:45  rudahl
 *   improved dump, trace
 *
 *   Revision 1.17  2005/09/10 05:58:24  goldin
 *   Fix inconsistency in screen file creation
 *
 *   Revision 1.16  2005/06/26 06:18:15  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.15  2005/04/06 12:15:16  rudahl
 *   fixed probs in revise_geometry
 *
 *   Revision 1.14  2005/04/06 09:27:17  rudahl
 *   expanded revise_geometry
 *
 *   Revision 1.13  2005/04/05 08:01:45  rudahl
 *   fixed image dimension error
 *
 *   Revision 1.12  2005/04/03 10:37:38  goldin
 *   Adding debug statements
 *
 *   Revision 1.11  2005/03/22 08:18:35  goldin
 *   Add stdarg.h for windows compile
 *
 *   Revision 1.10  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.11  2005/03/16 04:06:53  rudahl
 *   fixing writeTrailer tests
 *
 *   Revision 1.10  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.9  2005/03/10 00:06:29  rudahl
 *   added imageHdr.h
 *
 *   Revision 1.8  2005/03/03 16:27:05  rudahl
 *   added getTrailerOffset
 *
 *   Revision 1.7  2005/02/15 02:31:20  san
 *   Fixes error
 *
 *   Revision 1.6  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.5  2005/02/07 05:40:17  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.4  2005/02/03 16:07:19  rudahl
 *   initial support for multi-resolution formats
 *
 *   Revision 1.3  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.2  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.1  2005/01/26 02:04:00  rudahl
 *   initial from moochie
 *
 *
 ****************************************************************
 * 
 * Define a class for writing to screen (chunk) image files.
 * For linux, this writes a totally different format (jpg)
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *              san     San Ratanasanya
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-01-20 ktr	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h
 *	2005-9-17 ktr	enhanced dump()
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>

#if defined __GCC__ 
extern "C" {
#include "jpeglib.h"
}
#endif // #if defined __GCC__ 

#include "dtypes.h"
#include "dlimits.h"  /* for strcat_array */
#include "dragon-errors.h"
#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"

#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "portfile.h"
#include "imageWriter.h"
#include "screenImageWriter.h"

Class ScreenImageWrtr_class("ScreenImageWriter",
			    "Class for writing new Screen image files");

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
ScreenImageWriter::ScreenImageWriter(int iDebug, int iTrace)
    {
    m_pClass = &ScreenImageWrtr_class; 
    m_pClass->setSubClass(ImageWriter::getBaseClass());
    if (iDebug > m_iDebug)
      m_iDebug = iDebug;
    if (iTrace > m_iTrace)
      m_iTrace = iTrace;
    if (m_iDebug)
	printf("DragonImageWriter constructor\n");
    m_uHeaderChecksum = 0;
    m_pHdr = NULL;
    }

#if DRAGON_VER >= 6
#if defined __GCC__ 
/*
 * IMAGE DATA FORMATS:
 *
 * The standard input image format is a rectangular array of pixels, with
 * each pixel having the same number of "component" values (color channels).
 * Each pixel row is an array of JSAMPLEs (which typically are unsigned chars).
 * If you are working with color data, then the color values for each pixel
 * must be adjacent in the row; for example, R,G,B,R,G,B,R,G,B,... for 24-bit
 * RGB color.
 *
 * For this example, we'll assume that this data structure matches the way
 * our application has stored the image in memory, so we can just pass a
 * pointer to our image buffer.  In particular, let's say that the image is
 * RGB color and is described by:
 */

//static JSAMPLE * image_buffer = NULL;	/* Points to large array of R,G,B-order data */
//static int image_height = 0;	/* Number of rows in image */
//static int image_width = 0;		/* Number of columns in image */

/*
 * Sample routine for JPEG compression.  We assume that the target file name
 * and a compression quality factor are passed in.
 */

typedef struct jpeg_compress_struct JPG_INFO;

static JPG_INFO s_cinfo;
static FILE * pOutfile = NULL;

/** setup to write 3-color jpg file
 *  Called by class fn write_header
 *  @param cinfo	opaque structure used only by the three
 *			JPEG functions
 *  @param outfile	handle to opened destination file
 *  @param quality	???
 *  @param image_height	size in lines
 *  @param image_width	size in pixels
 *  @return		0 if OK
 */
static int init_JPEG_file (JPG_INFO * cinfo,
			   FILE * outfile, int quality,
			   int image_height,int image_width)
    {
    int iRetval = 0;
    /* This struct contains the JPEG compression parameters and pointers to
     * working space (which is allocated as needed by the JPEG library).
     * It is possible to have several such structures, representing multiple
     * compression/decompression processes, in existence at once.  We refer
     * to any one struct (and its associated working data) as a "JPEG object".
     */

    /* This struct represents a JPEG error handler.  It is declared separately
     * because applications often want to supply a specialized error handler
     * (see the second half of this file for an example).  But here we just
     * take the easy way out and use the standard error handler, which will
     * print a message on stderr and call exit() if compression fails.
     * Note that this struct must live as long as the main JPEG parameter
     * struct, to avoid dangling-pointer problems.
     */
    struct jpeg_error_mgr jerr;

    /* Step 1: allocate and initialize JPEG compression object */
    
    /* We have to set up the error handler first, in case the initialization
     * step fails.  (Unlikely, but it could happen if you are out of memory.)
     * This routine fills in the contents of struct jerr, and returns jerr's
     * address which we place into the link field in cinfo.
     */
    cinfo->err = jpeg_std_error(&jerr);
    /* Now we can initialize the JPEG compression object. */
   jpeg_create_compress(cinfo);

    /* Step 2: specify data destination (eg, a file) */
    /* Note: steps 2 and 3 can be done in either order. */

    /* Here we use the library-supplied code to send compressed data to a
     * stdio stream.  You can also write your own code to do something else.
     * VERY IMPORTANT: use "b" option to fopen() if you are on a machine that
     * requires it in order to write binary files.
     */
    //    if ((outfile = fopen(filename, "wb")) == NULL) 
    //  {
    //fprintf(stderr, "can't open %s\n", filename);
    //return DERR_FILE_OPEN;
    //}
    jpeg_stdio_dest(cinfo, outfile);

    /* Step 3: set parameters for compression */
    /* First we supply a description of the input image.
     * Four fields of the cinfo struct must be filled in:
     */
    cinfo->image_width = image_width; 	/* image width and height, in pixels */
    cinfo->image_height = image_height;
    /* alternative for next args are 1, JCS_GRAYSCALE */
    /* however, displayImg always writes a 3-color file, even for grey */
    cinfo->input_components = 3;	/* # of color components per pixel */
    cinfo->in_color_space = JCS_RGB; 	/* colorspace of input image */

    /* Now use the library's routine to set default compression parameters.
     * (You must set at least cinfo->in_color_space before calling this,
     * since the defaults depend on the source color space.)
     */
    jpeg_set_defaults(cinfo);

    /* Now you can set any non-default parameters you wish to.
     * Here we just illustrate the use of quality (quantization table) scaling:
     */
    jpeg_set_quality(cinfo, quality, TRUE /* limit to baseline-JPEG values */);
    
    /* Step 4: Start compressor */
    
    /* TRUE ensures that we will write a complete interchange-JPEG file.
     * Pass TRUE unless you are very sure of what you're doing.
     */
    jpeg_start_compress(cinfo, TRUE);
    
    return iRetval;
    }

    /* Step 5: while (scan lines remain to be written) */
    /*           jpeg_write_scanlines(...); */
    /* Here we use the library's state variable cinfo->next_scanline as the
     * loop counter, so that we don't have to keep track ourselves.
     * To keep things simple, we pass one scanline per call; you can pass
     * more if you wish, though.
     */
//    while (cinfo.next_scanline < cinfo.image_height) 
/** write one line of data
 */
static int write_JPEG_line(JPG_INFO * cinfo,JSAMPLE * image_buffer)
    {
	/* jpeg_write_scanlines expects an array of pointers to scanlines.
	 * Here the array is only one element long, but you could pass
	 * more than one scanline at a time if that's more convenient.
	 */
      //    int row_stride		/* physical row width in image buffer */
      //	 = cinfo->image_width * 3;	/* JSAMPLEs per row in image_buffer */
      //    JSAMPROW row_pointer	/* pointer to JSAMPLE row[s] */
      //	     = & image_buffer[0];
    (void) jpeg_write_scanlines(cinfo, &image_buffer, 1);
    //    (void) jpeg_write_scanlines(cinfo, &row_pointer, 1);
    return 0;
    }

    /* Step 6: Finish compression */
/* @return 	0 if OK
 *		DERR_FILE_CLOSE if close error
 */
static int close_JPEG_file(JPG_INFO * cinfo,FILE * outfile)
    {
    int iRetval = 0;
    jpeg_finish_compress(cinfo);
    /* After finish_compress, we can close the output file. */
    if (fclose(outfile))
        iRetval = DERR_FILE_CLOSE;
    /* Step 7: release JPEG compression object */
    /* This is an important step since it will release a good deal of memory. */
    jpeg_destroy_compress(cinfo);
    /* And we're done! */
    return iRetval;
    }

/*
 * SOME FINE POINTS:
 *
 * In the above loop, we ignored the return value of jpeg_write_scanlines,
 * which is the number of scanlines actually written.  We could get away
 * with this because we were only relying on the value of cinfo.next_scanline,
 * which will be incremented correctly.  If you maintain additional loop
 * variables then you should be careful to increment them properly.
 * Actually, for output to a stdio stream you needn't worry, because
 * then jpeg_write_scanlines will write all the lines passed (or else exit
 * with a fatal error).  Partial writes can only occur if you use a data
 * destination module that can demand suspension of the compressor.
 * (If you don't know what that's for, you don't need it.)
 *
 * If the compressor requires full-image buffers (for entropy-coding
 * optimization or a multi-scan JPEG file), it will create temporary
 * files for anything that doesn't fit within the maximum-memory setting.
 * (Note that temp files are NOT needed if you use the default parameters.)
 * On some systems you may need to set up a signal handler to ensure that
 * temporary files are deleted if the program is interrupted.  See libjpeg.doc.
 *
 * Scanlines MUST be supplied in top-to-bottom order if you want your JPEG
 * files to be compatible with everyone else's.  If you cannot readily read
 * your data in that order, you'll need an intermediate array to hold the
 * image.  See rdtarga.c or rdbmp.c for examples of handling bottom-to-top
 * source data using the JPEG code's internal virtual-array mechanisms.
 */

/*
 * ERROR HANDLING:
 *
 * The JPEG library's standard error handler (jerror.c) is divided into
 * several "methods" which you can override individually.  This lets you
 * adjust the behavior without duplicating a lot of code, which you might
 * have to update with each future release.
 *
 * Our example here shows how to override the "error_exit" method so that
 * control is returned to the library's caller when a fatal error occurs,
 * rather than calling exit() as the standard error_exit method does.
 *
 * We use C's setjmp/longjmp facility to return control.  This means that the
 * routine which calls the JPEG library must first execute a setjmp() call to
 * establish the return point.  We want the replacement error_exit to do a
 * longjmp().  But we need to make the setjmp buffer accessible to the
 * error_exit routine.  To do this, we make a private extension of the
 * standard JPEG error handler object.  (If we were using C++, we'd say we
 * were making a subclass of the regular error handler.)
 *
 * Here's the extended error handler struct:
 */

struct my_error_mgr 
    {
    struct jpeg_error_mgr pub;	/* "public" fields */

      //    jmp_buf setjmp_buffer;	/* for return to caller */
    };

typedef struct my_error_mgr * my_error_ptr;

/*
 * Here's the routine that will replace the standard error_exit method:
 */

METHODDEF(void)
my_error_exit (j_common_ptr cinfo)
    {
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
      // my_error_ptr myerr = (my_error_ptr) cinfo->err;

  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
    (* cinfo->err->output_message) (cinfo);

  /* Return control to the setjmp point */
    //    longjmp(myerr->setjmp_buffer, 1);
    }

#endif // #if defined __GCC__ 
#endif // #if DRAGON_VER >= 6


		// write the file 
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct to init.
		// @param pErrNum	pointer to variable to receive errnum
		//			  -51 for file open/create error
		//			  -53 for file write error
		//			  -54 for file close error
		//			  -72 for uninit. header
		// @return		TRUE if OK
/* ~~ change const IMAGEHDR variable to normal one */
BOOL ScreenImageWriter::writeHeader(const char * pczFilename,
				    const IMAGEHDR * pHdr,
				    int * pErrNum)
    {
    BOOL bRetval = FALSE;
    * pErrNum = 0;
    if (m_iDebug)
	printf("ScreenImageWriter::writeHeader (en) %s pHdr=%p\n",
	       pczFilename,pHdr);
    if (m_iTrace)
	logTrace("ScreenImageWriter::writeHeader (en) %s pHdr=%p",
	       pczFilename,pHdr);
    if ((pHdr == NULL) || ! pHdr->bImageHdrInitialized)
	* pErrNum = DERR_HDR_UNINIT;
    else
        {
#if ! defined __GCC__ 
	m_pHdr = pHdr;
	ulong ulOffset = 14 + sizeof(CHUNK_HDR); // + sizeof(CH_DISPIMG);
	ulong ulDataSize = (ulong)(pHdr->size[0]) * (ulong)(pHdr->size[1]) * 3;
	CHUNK_FILE_HDR cfhHdr;
	ushort * p_cfhHdr = (ushort *)&cfhHdr;
	memset(&cfhHdr,0,sizeof(CHUNK_FILE_HDR));
	cfhHdr.uType = BFT_CHUNK;
//	cfhHdr.ulSize = 
//	cfhHdr.uFlags = 
	p_cfhHdr[4] = 0x490;
//cfhHdr.uVersion = 0x490; 
//	cfhHdr.ulTotChunkSize = 

	CHUNK_HDR chImgHdr;	/* remember so we can delete file */
	memset(&chImgHdr,0,sizeof(CHUNK_HDR));
	chImgHdr.ulHdrSize = sizeof(CHUNK_HDR);
	chImgHdr.ulSize = ulDataSize;
	chImgHdr.lOffset = ulOffset;
	ulOffset += sizeof(CH_DISPIMG);
	logTrace("ScreenImageWriter::writeHeader - ulDataSize=%d ulOffset after adjust=%d sizeof(CH_DISPIMG) is %d",
              ulDataSize, ulOffset, sizeof(CH_DISPIMG));
	//	chImgHdr.lNxtOffset = ulOffset+ulDataSize;
	// SEE BELOW
	strcpy_array(chImgHdr.cChunk,"DL-PIX24");
	strcpy_array(chImgHdr.cFile,pczFilename); // full path to image
	chImgHdr.ulTimeStamp = time(NULL);

	CH_DISPIMG chunkImg;    /* this IS the DispImg chunk */ 
	memset(&chunkImg,0,sizeof(CH_DISPIMG));
	chunkImg.ulSize = sizeof(CH_DISPIMG);
	chunkImg.uPix = pHdr->size[1];
	chunkImg.uLines = pHdr->size[0];
	chunkImg.ulSizeImage = ulDataSize;
	chunkImg.ulOffset = ulOffset;
	chunkImg.uTilesW = 1;	// these five are maybe not used
	chunkImg.uTilesH = chunkImg.uLines;
	chunkImg.uTileLn = 1;
	chunkImg.uTilePix = chunkImg.uPix;
	    // according to docs in v 5.4.4 graf/windrv, windows requires a multiple of 4
	chunkImg.ulTileRowBytes = ((chunkImg.uTileLn * chunkImg.uPix * 3)+3) & ~3;
	/* include padding bytes in the data count */
	chImgHdr.lNxtOffset = ulOffset+
                   (chunkImg.ulTileRowBytes*chunkImg.uLines);

	strcpy_array(chunkImg.cImage,"TEST"); // ~~ descriptor for VP title?

	FILE * pf = fopen(pczFilename,"wb");
	if (pf != NULL)
            {
	    size_t w;	
	    if (((w=fwrite(&cfhHdr,sizeof(CHUNK_FILE_HDR),1,pf)) != 1)
		|| fseek(pf,14,SEEK_SET) // ~~ gccdoesn't handle sizeof right
		    || ((w=fwrite(&chImgHdr,sizeof(CHUNK_HDR),1,pf)) != 1)
		    || ((w=fwrite(&chunkImg,sizeof(CH_DISPIMG),1,pf)) != 1))
	        {
		*pErrNum = DERR_FILE_RW;
		if (m_iDebug)
		    printf("ScreenImageWriter::writeHeader "
			   "error count=%d (hdrsz=%d)\n",
			   w,sizeof(CHUNK_FILE_HDR));
		if (m_iTrace)
		    logTrace("ScreenImageWriter::writeHeader "
			   "error count=%d (hdrsz=%d)",
			   w,sizeof(CHUNK_FILE_HDR));
		}
	    if (fclose(pf))
		*pErrNum = DERR_FILE_CLOSE;
	    }
	else
	    *pErrNum = DERR_FILE_OPEN;
#else // #if ! defined __GCC__ 
#if DRAGON_VER >= 6
	pOutfile = fopen(pczFilename, "wb");
        if (pOutfile == NULL) 
	    {
	    if (m_iDebug)
	        fprintf(stderr, "can't open %s\n", pczFilename);
	    *pErrNum = DERR_FILE_OPEN;
	    }
	else
	    {
	    //int jpgstat = 
	    init_JPEG_file (&s_cinfo,pOutfile, 100, //int quality,
			   pHdr->size[0],pHdr->size[1]);
	    }
#endif
#endif // #if ! defined __GCC__ 
        }
    if (*pErrNum == 0)
	bRetval = TRUE;
    if (m_iDebug)
	printf("ScreenImageWriter::writeHeader (ex) "
	       "creating file '%s' success=%s errnum=%d\n",
	       pczFilename, YESNO(bRetval),*pErrNum);
    if (m_iTrace)
	logTrace("ScreenImageWriter::writeHeader (ex) "
	       "creating file '%s' success=%s errnum=%d",
	       pczFilename, YESNO(bRetval),*pErrNum);
    return bRetval;
    }

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
int ScreenImageWriter::init(ImageHdr * pImageHdr,
			    long * plOffset)
    {
    int iRetval = -1;
    ulong ulTileRowBytes = 0;
    //#if ! defined __GCC__ 
    // according to docs in v 5.4.4 graf/windrv, windows requires a multiple of 4
    ulTileRowBytes=(((ulong)(pImageHdr->getImageHdr()->size[1]) * 3L)+3L) & ~3L;

    //    ulong ulTileRowBytes=(ulong)(pImageHdr->getImageHdr()->size[1]) * 3L;

    // saying 24 bits/pix sets line buffer size
    iRetval = pImageHdr->revise_geom(NULL,  // Filename
				     FALSE, // bOverwrite
				     FALSE, // bReReadable
				     IT_CHUNK54,
				     0,0,   // uNumLines uNumPixels
				     24,    // uBitsPerPix 
				     3,     // uNumBands
				     1,	    // uNumResolutions
				     0,
				     ulTileRowBytes,
				     0);
    *plOffset = 14 + sizeof(CHUNK_HDR) + sizeof(CH_DISPIMG); 
    //#endif // #if ! defined __GCC__ 
    if (m_iDebug)
	printf("ScreenImageWriter::init (ex) "
	       "data offset will be %ld linepitch will be %ld; returning %d\n",
	       *plOffset,ulTileRowBytes,iRetval);
    if (m_iTrace)
	logTrace("ScreenImageWriter::init (ex) "
	       "data offset will be %ld linepitch will be %ld; returning %d",
	       *plOffset,ulTileRowBytes,iRetval);
    return iRetval;
    }

#if defined __GCC__ 
	/*	Put a line of raw data to the file
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
int ScreenImageWriter::putImageLineRaw(const byte * pBuf, ushort uLineNo,
				       size_t uBufSize, const IMAGE * pImg,
				       BOOL bReReadable)
    {
    int iRetval = uBufSize;
#if DRAGON_VER >= 6
    write_JPEG_line(&s_cinfo,(JSAMPLE *)pBuf);
#endif
    return iRetval;
    }
#endif // #if defined __GCC__ 

	/* calc and return the size of the header plus image data, or 0
	 * This cannot be done until the header has been written
	 * In this case
	 */
ulong ScreenImageWriter::getTrailerOffset() const
    {
    ulong ulRetval = 0;
#if ! defined __GCC__ 
    ulRetval = 14 + sizeof(CHUNK_HDR) + sizeof(CH_DISPIMG) 
	+ m_pHdr->ulLinePitch * (ulong)m_pHdr->size[0];
    if (m_iDebug)
	printf("ScreenImageWriter::getTrailerOffset "
	       "based on components %d, %d, %d and %ld x %d = %ld\n",
	       14,sizeof(CHUNK_HDR),sizeof(CH_DISPIMG),
	       m_pHdr->ulLinePitch,m_pHdr->size[0],ulRetval);
    if (m_iTrace)
	logTrace("ScreenImageWriter::getTrailerOffset "
	       "based on components %d, %d, %d and %ld x %d = %ld",
	       14,sizeof(CHUNK_HDR),sizeof(CH_DISPIMG),
	       m_pHdr->ulLinePitch,m_pHdr->size[0],ulRetval);
#endif // #if ! defined __GCC__ 
    return ulRetval;
    }

	/* return how many bytes will be needed for one line of raw data
	 */
size_t ScreenImageWriter::getRawImageLineSize(size_t uPixels)
    {
    return uPixels * 3;  /* 3-bytes per pix, 8-bit data */
    }

		// rewrite selected header info if changed
		// @return		0 if OK else ...
int ScreenImageWriter::rewriteHeader(const Image * pImage)
	    { return 0; } 

		// append trailer on the file : closed on return
		// @param pczFilename	name of file to write
		// @param pHdr		pointer of IMAGEHDR struct 
		//			containing info to write
		// @param uDataCheck	checksum of image data
		// @return		0 if OK
int ScreenImageWriter::writeTrailer(const char * pczFilename,
				    const IMAGEHDR * pHdr,UINT32 uDataCheck)
    { 
    int iRetval = 0;
#if ! defined __GCC__ 
    CHUNK_HDR chunkHdr;
    ulong ulFSize = file_size(pczFilename);
    logTrace("ScreenImageWriter::writeTrailer (en) %s ",pczFilename);
    if ((pHdr->iff_offset == 0) || (ulFSize != pHdr->iff_offset))
        {
	  //	if (m_iDebug)
	printf("ScreenImageWriter::writeTrailer trailer offset inconsistent "
	       "current filesize=%ld iff_offset=%ld\n",
	       ulFSize,pHdr->iff_offset);
	//if (m_iDebug)
	logTrace("ScreenImageWriter::writeTrailer (ex) trailer offset inconsistent "
		 "current filesize=%ld iff_offset=%ld",
		 ulFSize,pHdr->iff_offset);
	return DERR_IMAGE_CORRUPT;
	}
    memset(&chunkHdr,0,sizeof(CHUNK_HDR));
    chunkHdr.ulHdrSize = sizeof(CHUNK_HDR);
    chunkHdr.ulSize = 0;
    chunkHdr.lOffset = pHdr->iff_offset;
    chunkHdr.lNxtOffset = 0;
//	strcpy_array(chunkHdr.cFile,pHdr->); full path to image
    chunkHdr.ulTimeStamp = time(NULL);
    strcpy_array(chunkHdr.cChunk,"DL-TRAILER");
    //    chunkHdr.ulTotChunkSize = 0;
    FILE * pf = fopen(pczFilename,"ab");
    if (pf != NULL)
        {
	  //	if (fseek(pf,pHdr->iff_offset,SEEK_SET) != 0)
	  //  iRetval = DERR_FILE_SEEK;
	if ((fwrite(&chunkHdr,sizeof(CHUNK_HDR),1,pf)) != 1)
	    iRetval = DERR_FILE_RW;
	if ((iRetval == 0) && (fclose(pf) != 0))
	    iRetval = DERR_FILE_CLOSE;
	}
    else
	iRetval = DERR_FILE_OPEN;
#else
#if DRAGON_VER >= 6
    iRetval = close_JPEG_file(&s_cinfo,pOutfile);
#endif
#endif // #if ! defined __GCC__ 
    if (m_iDebug)
	printf("ScreenImageWriter::writeTrailer at offset %ld error %d\n",
	       pHdr->iff_offset,iRetval);
    if (m_iTrace)
	logTrace("ScreenImageWriter::writeTrailer at offset %ld error %d",
	       pHdr->iff_offset,iRetval);
    logTrace("ScreenImageWriter::writeTrailer (ex) returns %d",iRetval);
    return iRetval; 
    } 

		// return a formatted dump of the class member
const char * ScreenImageWriter::dump(int detail, 
					   const char * czTitle) const
    {
    snprintf(s_czDumpBuf,sizeof(s_czDumpBuf),
	     "ScreenImageWriter dump imagehdr=%p fp=%p",
	     m_pHdr,m_pFp);
    return s_czDumpBuf;
    }

void SCREEN_IMG_WRTR_END() { puts(FIL_ID); }

