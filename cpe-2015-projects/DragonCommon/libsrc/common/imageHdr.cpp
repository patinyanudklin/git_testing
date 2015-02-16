#include "drelease.h"
char IMAGEHDR_ID[]=
"\0@(#) " __FILE__ "  $Revision: 1.8 $$Date: 2015/01/21 10:37:33 $ " VERR;
D_REL_IDSTR;

/*
 *	filename imageHdr.cpp
 *		$Revision: 1.8 $ $Date: 2015/01/21 10:37:33 $	
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
 *   $Id: imageHdr.cpp,v 1.8 2015/01/21 10:37:33 rudahl Exp $
 *   $Log: imageHdr.cpp,v $
 *   Revision 1.8  2015/01/21 10:37:33  rudahl
 *   improving imageReader - 2drag coordination
 *
 *   Revision 1.7  2015/01/16 07:39:47  rudahl
 *   working on import
 *
 *   Revision 1.6  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.5  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.4  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.3  2014/03/28 14:51:12  rudahl
 *   working on auto import
 *
 *   Revision 1.2  2014/03/15 10:28:18  rudahl
 *   moved some stuff from dhead to imageHdr
 *
 *   Revision 1.1  2014/03/08 12:27:13  rudahl
 *   moved class methods from dhead to their own files, and adjusted Makefiles
 *
 *   Revision 1.105  2014/03/01 01:45:40  rudahl
 *   added create() for foreign files, for rosetta
 *
 *   Revision 1.104  2014/02/10 04:12:37  rudahl
 *   no longer want screenfile in rosetta
 *
 *   Revision 1.103  2014/02/09 04:43:32  rudahl
 *   some imageReaders not needed by rosetta
 *
 *   Revision 1.102  2012/07/01 09:54:24  rudahl
 *   fixed copyright
 *
 *   Revision 1.101  2012/07/01 09:30:27  rudahl
 *   fix problems importing GeoEye tiff files
 *
 *   Revision 1.100  2011/12/16 09:35:10  rudahl
 *   add jpeg for Linux, https web communications
 *
 *   Revision 1.99  2011/12/13 13:32:36  rudahl
 *   write chunk file in linux actually creates JPG
 *
 *   Revision 1.98  2011/02/27 08:24:51  rudahl
 *   final work on tiff IO
 *
 *   Revision 1.97  2011/02/06 10:30:11  rudahl
 *   tracing
 *
 *   Revision 1.96  2011/02/05 10:40:41  rudahl
 *   be certain number of bands start out zeroed
 *
 *   Revision 1.95  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.94  2011/01/03 06:31:22  rudahl
 *   improved tracing
 *
 *   Revision 1.93  2010/12/27 02:37:01  rudahl
 *   working on tiff generation
 *
 *   Revision 1.92  2010/12/24 08:57:08  rudahl
 *   integrate the tiffWriter into the build
 *
 *   Revision 1.91  2010/12/11 07:49:22  rudahl
 *   change Linear_meter to meter
 *
 *   Revision 1.90  2010/12/09 12:19:32  rudahl
 *   specialcase for unitname: change linear_meter to meter
 *
 *   Revision 1.89  2010/12/05 07:40:07  rudahl
 *   fix 'line too big' test in GetImageLine
 *
 *   Revision 1.88  2008/09/27 08:17:16  rudahl
 *   improved tracing
 *
 *   Revision 1.87  2008/09/12 11:41:24  rudahl
 *   improved tracing
 *
 *   Revision 1.86  2008/09/05 07:39:56  rudahl
 *   improved tracing
 *
 *   Revision 1.85  2008/06/19 12:05:50  rudahl
 *   testing blob access
 *
 *   Revision 1.84  2008/06/19 07:38:36  rudahl
 *   testing blob access
 *
 *   Revision 1.83  2008/06/14 10:15:28  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.82  2008/04/27 06:01:08  rudahl
 *   improved notices, tracing
 *
 *   Revision 1.81  2008/04/26 09:45:23  rudahl
 *   improved copyrights, tracing
 *
 *   Revision 1.80  2007/10/07 06:05:47  goldin
 *   Don't free pczMetaFile or pczGUID in the first time branch
 *
 *   Revision 1.79  2007/08/02 12:46:08  rudahl
 *   part of 32-bit convert; IMG now has signed params
 *
 *   Revision 1.78  2007/05/13 06:35:10  goldin
 *   Set unsupported format error if all image tests fail
 *
 *   Revision 1.77  2007/02/11 04:40:35  rudahl
 *   removed excessive tracing
 *
 *   Revision 1.76  2007/01/29 10:36:02  rudahl
 *   better propagation of iTrace,iDebug
 *
 *   Revision 1.75  2007/01/26 06:38:57  goldin
 *   Handle 0 bits/pix correctly in create functions
 *
 *   Revision 1.74  2007/01/02 10:31:29  goldin
 *   Add tracing, fix bug in formatting
 *
 *   Revision 1.73  2007/01/01 14:27:38  rudahl
 *   error in printf
 *
 *   Revision 1.72  2007/01/01 13:35:51  rudahl
 *   improving tracing
 *
 *   Revision 1.71  2007/01/01 11:25:59  rudahl
 *   improved tracing
 *
 *   Revision 1.70  2007/01/01 09:42:47  rudahl
 *   improved tracing, dumps; originalfileinfo
 *
 *   Revision 1.69  2007/01/01 04:50:15  rudahl
 *   minor fixes
 *
 *   Revision 1.68  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.67  2006/12/11 07:45:35  rudahl
 *   enhanced tracing around the update_ fns
 *
 *   Revision 1.66  2006/12/09 14:54:03  rudahl
 *   separated common.a and rose.a
 *
 *   Revision 1.65  2006/11/20 13:29:20  rudahl
 *   added externImageReader
 *
 *   Revision 1.64  2006/09/29 11:36:39  goldin
 *   Begin implementation of meta data file classes
 *
 *   Revision 1.63  2006/08/20 11:04:52  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.62  2006/08/14 06:28:47  rudahl
 *   finalized init version of bilEsri
 *
 *   Revision 1.61  2006/08/04 04:29:51  goldin
 *   Create new test for vector files in dragonImageReader
 *
 *   Revision 1.60  2006/07/29 11:13:11  goldin
 *   Add tracing
 *
 *   Revision 1.59  2006/03/04 08:14:41  rudahl
 *   improve tracing
 *
 *   Revision 1.58  2006/01/25 01:59:31  rudahl
 *   dump improvement
 *
 *   Revision 1.57  2006/01/19 09:21:05  rudahl
 *   improved dump
 *
 *   Revision 1.56  2006/01/08 09:33:25  rudahl
 *   removed doubly-defined macro
 *
 *   Revision 1.55  2006/01/02 11:32:15  goldin
 *   Update stats was not storing item 0 of the histogram. Fixed
 *
 *   Revision 1.54  2005/12/30 10:37:53  rudahl
 *   added support for dump(detail
 *
 *   Revision 1.53  2005/09/18 03:00:54  rudahl
 *   lint-ish
 *
 *   Revision 1.52  2005/09/17 10:59:54  rudahl
 *   added bulletproofing
 *
 *   Revision 1.51  2005/09/17 05:27:39  rudahl
 *   improved dump, trace, docs; readerfactory; ProcessRect
 *
 *   Revision 1.50  2005/09/12 12:18:39  goldin
 *   Fixing version inconsistencies
 *
 *   Revision 1.49  2005/09/07 05:04:18  rudahl
 *   added getLabel
 *
 *   Revision 1.48  2005/07/23 08:23:19  rudahl
 *   fine-tuning geotiff
 *
 *   Revision 1.47  2005/07/22 15:12:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.46  2005/07/18 12:56:36  rudahl
 *   work on geotiff
 *
 *   Revision 1.45  2005/07/15 02:40:32  rudahl
 *   added czFileType
 *
 *   Revision 1.44  2005/07/06 09:52:47  rudahl
 *   added jasperreader
 *
 *   Revision 1.43  2005/07/04 13:37:55  rudahl
 *   working with toollibs
 *
 *   Revision 1.42  2005/07/03 13:30:52  rudahl
 *   improving createImage
 *
 *   Revision 1.41  2005/06/26 06:18:14  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.40  2005/04/25 13:55:04  goldin
 *   get rid of debugging msg
 *
 *   Revision 1.39  2005/04/24 10:52:16  goldin
 *   Fix bug in copying of header - was not allocating new histogram
 *
 *   Revision 1.38  2005/04/07 10:24:49  rudahl
 *   cleaned up some arg lists and tracing
 *
 *   Revision 1.37  2005/04/06 12:15:15  rudahl
 *   fixed probs in revise_geometry
 *
 *   Revision 1.36  2005/04/06 09:27:17  rudahl
 *   expanded revise_geometry
 *
 *   Revision 1.35  2005/04/03 10:37:38  goldin
 *   Adding debug statements
 *
 *   Revision 1.34  2005/03/19 07:58:50  rudahl
 *   make img.TEST work for chunk files
 *
 *   Revision 1.42  2005/03/16 04:06:53  rudahl
 *   fixing writeTrailer tests
 *
 *   Revision 1.41  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.40  2005/03/11 22:45:13  goldin
 *   Debug update_labels
 *
 *   Revision 1.39  2005/03/11 20:27:54  goldin
 *   debugging rewriteImageHeader
 *
 *   Revision 1.38  2005/03/10 22:41:12  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.37  2005/03/10 21:33:33  goldin
 *   Working on new test
 *
 *   Revision 1.36  2005/03/10 04:28:01  rudahl
 *   fixes for writing
 *
 *   Revision 1.35  2005/03/10 03:18:31  goldin
 *   Still working on img_acc test code
 *
 *   Revision 1.34  2005/03/10 01:51:17  rudahl
 *   added imageHdr.h
 *
 *   Revision 1.33  2005/03/09 01:34:14  rudahl
 *   fix missing args in new(), add CloseImage
 *
 *   Revision 1.32  2005/03/06 17:31:04  rudahl
 *   revising create() and update_text() args
 *
 *   Revision 1.31  2005/03/06 00:17:13  rudahl
 *   moved creation of writer to createheader
 *
 *   Revision 1.30  2005/03/04 23:05:25  rudahl
 *   improved tracing
 *
 *   Revision 1.29  2005/03/03 23:30:48  rudahl
 *   improved testing
 *
 *   Revision 1.28  2005/03/03 21:49:54  goldin
 *   Implement remaining revise_ & update_ methods
 *
 *   Revision 1.27  2005/03/03 16:35:02  rudahl
 *   improved update_georef
 *
 *   Revision 1.26  2005/03/02 21:35:45  san
 *   clean up tracing
 *
 *   Revision 1.25  2005/03/01 23:04:21  goldin
 *   Implement new create function for new output images; fix update functions
 *
 *   Revision 1.24  2005/03/01 16:02:07  rudahl
 *   slight change to dragonHd.h
 *
 *   Revision 1.23  2005/02/28 21:15:34  goldin
 *   Add update_georef methods
 *
 *   Revision 1.22  2005/02/28 20:44:46  goldin
 *   implement update_stats
 *
 *   Revision 1.21  2005/02/25 18:52:46  san
 *   testing/debuging: fixes some errors, except IMAGE_FORMAT errors
 *
 *   Revision 1.20  2005/02/23 18:21:31  rudahl
 *   new update, wrapper fns; moved from hdrstats to dhead
 *
 *   Revision 1.19  2005/02/22 01:57:33  san
 *   testing and debuging
 *
 *   Revision 1.18  2005/02/15 18:56:54  rudahl
 *   fixes for mingw
 *
 *   Revision 1.17  2005/02/12 03:19:16  rudahl
 *   undo prev. change
 *
 *   Revision 1.16  2005/02/11 18:57:17  rudahl
 *   added mingcc ansidecl
 *
 *   Revision 1.15  2005/02/10 23:21:56  rudahl
 *   added debug flags into constructors
 *
 *   Revision 1.14  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.13  2005/02/07 05:40:17  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.12  2005/02/03 16:07:19  rudahl
 *   initial support for multi-resolution formats
 *
 *   Revision 1.11  2005/02/03 03:15:02  rudahl
 *   Added support for getline and write header in img class,
 *   plus initial use of standardized error numbers
 *
 *   Revision 1.10  2005/02/01 01:39:36  rudahl
 *   Convert from header reader/writers to image reader/writers
 *   This version just changes names without adding any
 *   new functionality
 *
 *   Revision 1.9  2005/01/30 01:28:36  rudahl
 *   added printout of data element sizes
 *
 *   Revision 1.8  2005/01/27 23:13:11  rudahl
 *   fixed writing test
 *
 *   Revision 1.7  2005/01/27 21:35:22  rudahl
 *   added new dragon stuff
 *
 *   Revision 1.6  2005/01/27 15:56:41  rudahl
 *   enhanced testing
 *
 *   Revision 1.5  2005/01/26 02:05:23  rudahl
 *   added screen files, tracing
 *
 *   Revision 1.4  2005/01/18 22:44:29  rudahl
 *   improve dump
 *
 *   Revision 1.3  2005/01/05 02:23:23  rudahl
 *   use free() instead of delete for strings
 *
 *   Revision 1.2  2005/01/05 02:05:15  rudahl
 *   finished making it dhead build and test right
 *
 *   Revision 1.1  2005/01/04 16:29:17  rudahl
 *   new from moochie
 *
 ****************************************************************
 * 
 * Define a base class for reading and writing to real image files.
 * For each type of image file (defined by a different derived class),
 * this class will support reading and optionally writing the header.
 * 
 * Various query functions are also provided.
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
 * 5.7	2005-06-25 ktr	moved pFp from Image class to imageReader,imageWriter
 * 	2005-7-20 ktr	added h_OriginalFileName and IMAGEDATA_SELECTOR
 *	2005-9-7 ktr	added getLabel
 *	2005-9-16 ktr	getImageLine no longer enforces ProcessRect
 *	2005-9-17 ktr	enhanced reader, writer dump()
 * 5.9	2006-8-12 ktr	added pDataSel to CalcImageFileOffset
 * 	2006-12-8 ktr	implement ROSE_ONLY and re-sequence factory tests
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 *	2008-06-14 ktr	added LinesBlob to trailer
 * 6	2010-12-09 ktr	as a special 9but frequent) case, replace the
 *			unitname 'linear_meter' by 'meter'
 * 6.4	2014-03-08 ktr	moved MOST imageHdr fns from dhead.cpp
 *			HOWEVER imageReader,WriterFactory are still in dhead.cpp
 */

#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <ctype.h>
#include <errno.h>
#include <stddef.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcat_array */
#include "files.h"
#include "dragon-errors.h"
#include "dragonHd.h"
#include "ob.h"
#include "logger.h"
#include "portfile.h"
#include "dhead.h"
#include "dragonOb.h"
#include "dhead-old.h"
#include "imageHdr.h"
typedef void IMAGE;
#include "imageReader.h"
#include "imageWriter.h"
#include "dragonImageReader.h"
#include "dragonImageWriter.h"
#include "dragonOldImageReader.h"
#include "dragonOldImageWriter.h"
#include "tiffImageReader.h"
#if ! defined ROSE_ONLY // imageReaderFactory in rosetta only needs Dragon/TIFF images
#include "screenImageReader.h"
#include "screenImageWriter.h"
#include "tiffImageWriter.h"
#include "externImageReader.h"
#endif
#include "geotiff.h"

Class ImageHdr::s_class_Base("ImageHdr","Class for reading and writing image headers");
const char * ImageHdr::s_czLayoutNames[] = { IMG_LAYOUT_NAMES };
const char * ImageHdr::s_czImgTypeNames[] = {IMGTYPE_NAMES};

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
ImageHdr::ImageHdr(int iDebug,int iTrace)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_uUpdates = IMG_UPDATE_ALL;
    zero(TRUE);
    }

		/* this is basically a copy constructor,
		 * although the default constructor must be called first.
		 * @param pSrc	header to copy
		 * @param uImgType	File format of new image file
		 * @param pczFtype      Dragon file type - "I", "C" or "L",
		 *			or NULL to keep type from copy
		 * @return 		0 if OK
		 *			<0 if error:
		 *			  -48 strdup failure, 
		 *			  -72 pSrc not init
		 *			  -76 using an unused field
		 */
int ImageHdr::copy(const ImageHdr * pSrc,IMGTYPE_T uImgType,
		   const char* pczFtype)
    {
    int iRetval = 0;
    const char * czMethod = "ImageHdr::copy";
    if (m_iDebug)
	fprintf(stderr,"%s (en) from=%p to %s this.errno=%d src.errno=%d "
		"init=%s src.init=%s ftype: new='%s' src='%s'\n",
		czMethod,pSrc,s_czImgTypeNames[uImgType],getErrorNo(),
		pSrc->getErrorNo(),
		YESNO(m_hi.bImageHdrInitialized),
		YESNO(pSrc->getImageHdr()->bImageHdrInitialized),
		NN(pczFtype),pSrc->m_hi.ftype);
    if (m_iTrace)
        {
	logTrace("%s (en) from=%p to %s this.errno=%d src.errno=%d"
		 " init=%s src.init=%s ftype: new='%s' src='%s'",
		 czMethod,pSrc,s_czImgTypeNames[uImgType],getErrorNo(),
		 pSrc->getErrorNo(),
		 YESNO(m_hi.bImageHdrInitialized),
		 YESNO(pSrc->getImageHdr()->bImageHdrInitialized),
		 NN(pczFtype),pSrc->m_hi.ftype);
	logTrace(pSrc->dump(1,"ImageHdr::copy source image="));
	}
    zero(FALSE); /* release any prior mem allocs */
    if ((pSrc == NULL) || ! pSrc->getImageHdr()->bImageHdrInitialized)
	return DERR_HDR_UNINIT;
    const IMAGEHDR * pSrcH = pSrc->getImageHdr();
    		 /* then make an exact copy */
    memcpy((byte *)&m_hi,(const byte *)pSrcH,sizeof(m_hi));
    m_hi.uKey = 0;
    if (pczFtype != NULL)   /* override the copied value */
        { strcpy_array(m_hi.ftype,pczFtype); }
        // for PIL (Pixel Interleaved) the input image line/pixel 
	// contain all uBands but the output image is only one band.
        // line pitch is used to calculate the buffer size during read.
	// bandpitch always 0 for Dragon files
    if (m_hi.uBandLayout == IMG_PIL)
	m_hi.ulPixelPitch /= m_hi.uBands;
    m_hi.ulLinePitch = (ulong)m_hi.size[1] * m_hi.ulPixelPitch;
    		 /* finally deep copy the alloc'd stuff */
	// in implementing this:
	//   we should NOT free any ptrs before the strdups because that 
	//     would effectively free the strings in pSrcH
	//   we should NOT check the boolean init's in the source,
	//     since if they're wrong the src hdr is inconsistent anyway
    if ((pSrcH->h_title != NULL)
	        && ((m_hi.h_title = strdup(pSrcH->h_title)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->h_id != NULL)
		&& ((m_hi.h_id = strdup(pSrcH->h_id)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->comment != NULL)
	        && ((m_hi.comment = strdup(pSrcH->comment)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->source != NULL)
	        && ((m_hi.source = strdup(pSrcH->source)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->scene != NULL)
	        && ((m_hi.scene = strdup(pSrcH->scene)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->subscene != NULL)
	        && ((m_hi.subscene = strdup(pSrcH->subscene)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->band != NULL)
	        && ((m_hi.band = strdup(pSrcH->band)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->z_unit != NULL)
	        && ((m_hi.z_unit = strdup(pSrcH->z_unit)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->czProjection != NULL)
	    && ((m_hi.czProjection = strdup(pSrcH->czProjection)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->unitname != NULL)
	        && ((m_hi.unitname = strdup(pSrcH->unitname)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->pczColorFileName != NULL)
	    && ((m_hi.pczColorFileName = strdup(pSrcH->pczColorFileName)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->h_OriginalFileName != NULL)
	     && ((m_hi.h_OriginalFileName = strdup(pSrcH->h_OriginalFileName)) 
		 == NULL))
	iRetval = DERR_MEM_ALLOC;
    /* added for IGC metafile 8/20/06 */   
    else if ((pSrcH->pczMetafile != NULL)
	        && ((m_hi.pczMetafile = strdup(pSrcH->pczMetafile)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if ((pSrcH->pczGUID != NULL)
	        && ((m_hi.pczGUID = strdup(pSrcH->pczGUID)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    else if (pSrcH->pLabels != NULL)
        { 
	m_hi.pLabels 
	    = (LABEL_INFO *)calloc(m_hi.uNumLabels,sizeof(LABEL_INFO));
	if (m_hi.pLabels == NULL)
	    iRetval = DERR_MEM_ALLOC;
	else
	    for (ushort j=0; j<m_hi.uNumLabels; j++)
	        {
		memcpy((byte *)&m_hi.pLabels[j],
		       (const byte *)(&pSrcH->pLabels[j]),
		       sizeof(LABEL_INFO));
		if ((pSrcH->pLabels[j].pczText != NULL)
		        && ((m_hi.pLabels[j].pczText 
			     = strdup(pSrcH->pLabels[j].pczText)) == NULL))
		    {
		    iRetval = DERR_MEM_ALLOC;
		    break;
		    }
		}
	}
    /* 4/24/05 was 'else if!' so wasn't executing SEG */
    if (pSrcH->histo != NULL)
        { 
	m_hi.histo = (UINT32 *)calloc(pSrcH->uHdrHistLen,sizeof(UINT32));
	if (m_hi.histo == NULL)
	    iRetval = DERR_MEM_ALLOC;
	else
	    memcpy((byte *)m_hi.histo, (const byte *)pSrcH->histo,
		   pSrcH->uHdrHistLen*sizeof(UINT32));
	}
    if (pSrcH->pPalette != NULL)
	iRetval = DERR_HDR_BADFIELD;

    if (iRetval != 0)
	m_hi.bImageHdrInitialized = FALSE; /* something wrong */
    m_uImageType = uImgType;
    if (m_iDebug)
	fprintf(stderr,"%s (ex) "
	       "src=%p this.errno=%d src.errno=%d init=%s src.init=%s\n",
	       czMethod,pSrc,getErrorNo(),pSrc->getErrorNo(),
	       YESNO(m_hi.bImageHdrInitialized),
	       YESNO(pSrc->getImageHdr()->bImageHdrInitialized));
    if (m_iTrace)
        {
	logTrace("%s (ex) "
		 "src=%p this.errno=%d src.errno=%d init=%s src.init=%s",
		 czMethod,pSrc,getErrorNo(),pSrc->getErrorNo(),
		 YESNO(m_hi.bImageHdrInitialized),
		 YESNO(pSrc->getImageHdr()->bImageHdrInitialized));
	logTrace(dump(1,"ImageHdr::copy destination image="));
	}
    return iRetval;
    }

	// Get a pointer to a label
	// @param uLabelNo	index of label
	// @return 		pointer or NULL if uLabelNo out of range
const LABEL_INFO * ImageHdr::getLabel(size_t uLabelNo) const
    {
    return (uLabelNo < m_hi.uNumLabels) ? &m_hi.pLabels[uLabelNo] : NULL;
    }

	// Get label text
	// @param uLabelNo	index of label
	// @param pczUTF8Buffer	buffer to place text
	// @param uBufLen	size of buffer
	// @return 		-90 (DERR_FN_ARG0) if uLabelNo out of range
	//			else label color index >= 0
int ImageHdr::getLabel(size_t uLabelNo, char * pczUTF8Buffer, 
		       size_t uBufLen) const
    {
    int iRetval = DERR_FN_ARG0;
    const LABEL_INFO * pLabel = getLabel(uLabelNo);
    if (pLabel != NULL)
        {
	if (uBufLen > 0)
	    {
	    memset(pczUTF8Buffer,0,uBufLen);
	    if (pLabel->pczText != NULL)  /* not an error if it is */
		strncpy(pczUTF8Buffer,pLabel->pczText, uBufLen-1);
	    }
	iRetval = pLabel->uColorNdx;
	}
    return iRetval;
    }
		   
		// write specified file from IMAGEHDR
		// @return	0 if OK else  ...
int ImageHdr::write(const char * pczName)
    { return DERR_FN_NOTIMPL; }

		// return a formatted dump of the class member
		// @param detail	specify amount of detail
		//			0 => uninit, dragon-specific fields not reported
		//			1 => full info
const char * ImageHdr::dump(int detail, const char * czTitle) const
    {
    char tmpbuf[sizeof(s_outbuf)];
    const char * czMethod = "ImageHdr::dump";
    sprintf(tmpbuf,"%s %s\n\t\tIMGTYPE=%s layout=%s\n",czMethod,NN(czTitle),ImageTypeName(),LayoutName());
    // note that the static dump() writes to s_outbuf, so we need to recopy
    strcat_array(tmpbuf,dump(detail,&m_hi)); // call the static function (can be used with IMAGEHDR)
    strcpy_array(s_outbuf,tmpbuf);
    return s_outbuf;
    }

		// return a formatted dump of the IMAGEHDR structure
		// static function
		// @param detail	specify amount of detail
		//			0 => uninit, dragon-specific fields not reported
		//			1 => full info
const char * ImageHdr::dump(int detail, const IMAGEHDR * pHdr)
    {
    char tbuf[256];
    s_outbuf[0] = '\0';
    if ( ! pHdr->bImageHdrInitialized)
        {
	strcat(s_outbuf,"not initialized\n");
	return s_outbuf;
	}
    if (detail == 0)
	sprintf(s_outbuf+strlen(s_outbuf),
		"IMAGEFORMAT: \tbands=%d filetype=%s\n"
		"\t\tpitches: pix=%ld at %d line=%ld band=%ld\n", 
		pHdr->uBands,pHdr->czFileType,
		pHdr->ulPixelPitch,offsetof(IMAGEHDR,ulPixelPitch),pHdr->ulLinePitch,pHdr->ulBandPitch);
    else
	sprintf(s_outbuf+strlen(s_outbuf),
		"IMAGEFORMAT: \tbinary: %s rectangular: %s bands=%d\n"
		"\t\tfiletype=%s datasize=x%lX=%ld dataoffset=x%lX \n"
		"\t\tpitches: pix=%ld at %d, line=%ld band=%ld\n", 
		YESNO(pHdr->bBinary),YESNO(pHdr->bRectangular),pHdr->uBands,
		pHdr->czFileType,pHdr->ulDataSize,
		pHdr->ulDataSize,pHdr->ulDataOffset,
	        pHdr->ulPixelPitch,offsetof(IMAGEHDR,ulPixelPitch),pHdr->ulLinePitch,pHdr->ulBandPitch);

    if (pHdr->bImageHdrDescriptionInit)
	sprintf(s_outbuf+strlen(s_outbuf),"DESCRIPTION: \ttitle='%s'\n"
		"\t\tcomment='%s'\n"
		"\t\tID %s: source='%s' scene='%s' subscene='%s' band='%s'\n"
		"\t\toriginal: bands=%d bandno=%d file='%s'",
		NN(pHdr->h_title),NN(pHdr->comment),
		NN(pHdr->h_id),NN(pHdr->source),NN(pHdr->scene),
		NN(pHdr->subscene),NN(pHdr->band),
	        pHdr->h_uOriginalBandCount,pHdr->h_uOriginalBandNumber,
	        NN(pHdr->h_OriginalFileName));
    else
	sprintf(s_outbuf+strlen(s_outbuf),"DESCRIPTION: \t(not initialized)\n"
		"\t\toriginal='%s'",
		NN(pHdr->h_OriginalFileName));
    if (pHdr->h_uOriginalBandCount > 0)
	sprintf(s_outbuf+strlen(s_outbuf),
		" with %d bands using band %d",
		pHdr->h_uOriginalBandCount,pHdr->h_uOriginalBandNumber);
    sprintf(s_outbuf+strlen(s_outbuf),"\n");

//    logTrace("dump debug 1.3");
    if (detail == 0)
	snprintf(tbuf,sizeof(tbuf),"FILE_PARAMS: \tsize=%d lines x %d pixels %d bits/pix %s\n",
		 pHdr->size[0],pHdr->size[1], pHdr->bits_per_pix,(pHdr->uKey) ? "LOCKED" : "");
    else
	snprintf(tbuf,sizeof(tbuf),"FILE_PARAMS: \tsize=%d lines x %d pixels\n"
		 "\t\ttype=x%X ('%c') bits/pix=%d trailer @ x%lX %sx%X\n",
		 pHdr->size[0],pHdr->size[1],
		 pHdr->ftype[0],(isalpha(pHdr->ftype[0])) ? pHdr->ftype[0] : ' ',
		 pHdr->bits_per_pix,
		 pHdr->iff_offset,(pHdr->uKey) ? "LOCKED key=" : "",pHdr->uKey); 
    strcat_array(s_outbuf,tbuf);

//    logTrace("dump debug 3");
    if (! pHdr->bImageHdrStatsInit)
        {
	if (detail > 0)
	    { 
	    strcat_array(s_outbuf,
			 "STATS: \t\timage statistics not initialized\n"); }
	//	return s_outbuf;
	}
    else if (detail > 0)
        {
#if DRAGON_VER >= 6
	sprintf(tbuf,"STATS: \t\t"
		"imgmean=%d imgvar=%4.2f imgsd=%4.2f imgmax=%d imgmin=%d\n",
		pHdr->m_ihImgmean,pHdr->m_dhImgvar,pHdr->m_dhImgsd,
		pHdr->m_ihImgmax,pHdr->m_ihImgmin);
#else
	sprintf(tbuf,"STATS: \t\t"
		"imgmean=%d imgvar=%4.2f imgsd=%4.2f imgmax=%d imgmin=%d\n",
		pHdr->imgmean,pHdr->imgvar,pHdr->imgsd,
		pHdr->imgmax,pHdr->imgmin);
#endif
	strcat_array(s_outbuf,tbuf);
	}
//    sprintf(tbuf,"\n\tStretch (obsolete): normflag=%d upper=%d lower=%d\n",
//	   pHdr->norm,pHdr->upper,pHdr->lower);	/* lower bound */
//    strcat_array(s_outbuf,tbuf);

    if (! pHdr->bImageHdrScalingInit)
        { 
	if (detail > 0)
	    { strcat_array(s_outbuf,"CALIBRATION: \tnot initialized\n"); }
	}
    else
        {
		/* the following give calibration meaning to pixel values */
	sprintf(tbuf,"CALIBRATION: \tscale=%4.3f offset=%4.3f units=%s\n",
	       pHdr->z_scale,pHdr->z_offset,pHdr->z_unit);
	        /* the following reflect image rescaling from multibyte */
	strcat_array(s_outbuf,tbuf);
	sprintf(tbuf,"\t\tRescaling method: %s factors=%d or %4.3f; offset=%4.3f\n",
	       (pHdr->uScaleFactor != 0) ? "BINARY" 
	       : (pHdr->dScaleFactor != 0.0)? "OPTIMAL" : "NONE",
	       pHdr->uScaleFactor,pHdr->dScaleFactor,pHdr->dScaleOffset);
	strcat_array(s_outbuf,tbuf);
	}

//    sprintf(tbuf,"\tmagic='%c%c%c%c' version=x%X\n",
//   pHdr->cMagic[0],pHdr->cMagic[1],pHdr->cMagic[2],pHdr->cMagic[3],pHdr->vn);
//    strcat_array(s_outbuf,tbuf);
//    sprintf(tbuf,"\tnumber of classes=%d\n",pHdr->numclasses);
    //   strcat_array(s_outbuf,tbuf);
//    logTrace("dump debug 5");
    if (! pHdr->georef_init)
        {
	if (detail > 0)
	    {  strcat_array(s_outbuf,"GEOREFERENCING: not initialized\n"); }
	}
    else
        {
	sprintf(tbuf,"GEOREFERENCING: "
	       "img_x=%d img_y=%d ref_x=%4.3f ref_y=%4.3f\n"
	       "\t\tx_size=%4.3f y_size=%4.3f units=%s\n"
		"\t\tDate=%s UTMZone=%s registered=%s\n",
		pHdr->img_x,pHdr->img_y,pHdr->ref_x.v0,pHdr->ref_y.v0,
		pHdr->xcell_size,pHdr->ycell_size,pHdr->unitname,
		pHdr->czDateTime,pHdr->czUTMZone,YESNO(pHdr->bRegistered));
	strcat_array(s_outbuf,tbuf);
	}
    sprintf(tbuf,"\tAux. Georeferencing info:\n\t\t"
		"%d Tiepoints:\t",pHdr->uModelTiepoints);
    strcat_array(s_outbuf,tbuf);
    tbuf[0] = '\0';
    if (pHdr->pModelTiepoints != NULL)
        {
	int i;
	const TIEPOINT_t * pT = pHdr->pModelTiepoints;
	for (i=0; i<pHdr->uModelTiepoints; i++)
	    {
	    if (i > 0)
		{ strcat_array(tbuf,"\t\t\t\t"); }
	    sprintf(tbuf+strlen(tbuf),
		    "%-4d %-4d %-4d <--> %10.3f %10.3f %10.3f\n",
		    pT->uI, pT->uJ, pT->uK, pT->dX, pT->dY, pT->dZ);
	    strcat_array(s_outbuf,tbuf);
	    tbuf[0] = '\0';
	    pT++;
	    }
	}
//    logTrace("dump debug 7");
    if (pHdr->bModelPixelScaleInit)
        {
	sprintf(tbuf,"\t\tModel Scale = %10.3f %10.3f %10.3f\n",
		pHdr->dModelPixelScale[0],pHdr->dModelPixelScale[1],
		pHdr->dModelPixelScale[2]);
	strcat_array(s_outbuf,tbuf);
	tbuf[0] = '\0';
	}
    if (pHdr->bModelTransformInit)
        {
	strcat_array(s_outbuf,"\t\tModel Transform:");
	for (int i=0; i < 16; i++)
            {
	    sprintf(tbuf+strlen(tbuf)," %7.3f",pHdr->dModelTransformation[i]);
	    if (i == 7)
		strcat(tbuf,"\n\t\t\t");
	    }
	strcat_array(tbuf,"\n");
	strcat_array(s_outbuf,tbuf);
	}
    snprintf(tbuf,sizeof(tbuf),"\t\tRasterType: %s (%d)\n"
	    "\t\tModelType: %s (%d)\n"
	    "\t\tProjectedCSType: %s (%d)\n"
	     "\t\tProjectedLinearUnits: %s (%d)\n",
//	    "\t\tProjectedAngularUnits: %s (%d)\n",
	    GTIFValueName(GTRasterTypeGeoKey,pHdr->uRasterType),
	      pHdr->uRasterType,
	    GTIFValueName(GTModelTypeGeoKey,pHdr->uModelType),pHdr->uModelType,
	    GTIFValueName(ProjectedCSTypeGeoKey,pHdr->uProjectedCSType),
	      pHdr->uProjectedCSType,
	    GTIFValueName(ProjLinearUnitsGeoKey,pHdr->uProjectedLinearUnits),
	     pHdr->uProjectedLinearUnits);
//	    GTIFValueName(ProjAngularUnitsGeoKey,pHdr->uProjectedAngularUnits),
//	      pHdr->uProjectedAngularUnits);
    strcat_array(s_outbuf,tbuf);
//    logTrace("dump debug 9");
    sprintf(tbuf,"\t\tProjectionGeo: %s (%d)\n"
	    "\t\tProjectionCoordTrans: %s (%d)\n",
	    GTIFValueName(ProjectionGeoKey,pHdr->uProjectionGeo),
	      pHdr->uProjectionGeo,
	    GTIFValueName(ProjCoordTransGeoKey,pHdr->uProjectionCoordTrans),
	      pHdr->uProjectionCoordTrans);
    strcat_array(s_outbuf,tbuf);
    sprintf(tbuf,"\t\tGeographicType: %s (%d)\n"
	    "\t\tGeodeticDatum: %s (%d)\n"
	    "\t\tGeographicPrimeMeridian: %s (%d)\n",
	   GTIFValueName(GeographicTypeGeoKey,pHdr->uGeographicType),
	      pHdr->uGeographicType,
	   GTIFValueName(GeogGeodeticDatumGeoKey,pHdr->uGeodeticDatum),
	      pHdr->uGeodeticDatum,
	   GTIFValueName(GeogPrimeMeridianGeoKey,pHdr->uGeographicPrimeMeridian),
	      pHdr->uGeographicPrimeMeridian);
    strcat_array(s_outbuf,tbuf);
    sprintf(tbuf,"\t\tVerticalType: %s (%d) \n"
	    "\t\tVerticalUnits: %s (%d)\n",
	    GTIFValueName(VerticalCSTypeGeoKey,pHdr->uVerticalType),
	      pHdr->uVerticalType,
	    GTIFValueName(VerticalUnitsGeoKey,pHdr->uVerticalUnits),
	      pHdr->uVerticalUnits);
    strcat_array(s_outbuf,tbuf);
    if (! pHdr->bImageHdrProjectionInit)
        { 
	if (detail > 0)
	    { strcat_array(s_outbuf,"PROJECTION \tnot initialized\n"); }
	}
    else
        {
	sprintf(tbuf,"PROJECTION: \t'%s'\n", pHdr->czProjection);
	strcat_array(s_outbuf,tbuf);
	}
    if (! pHdr->bImageHdrClassifyInit)
        { 
	if (detail > 0)
	    { strcat_array(s_outbuf,"LABELS: \tnot initialized\n"); }
	}
    else
        {
	sprintf(tbuf,"LABELS: \tnumlabels=%d (colorfile=' %s'):\n"
		     "\t\t    data#\tcol#\tI18Nkey\tLabel\n",
		pHdr->uNumLabels,NN(pHdr->pczColorFileName));
	strcat_array(s_outbuf,tbuf);

	for(size_t j=0; j<pHdr->uNumLabels; j++)
	    {
	    LABEL_INFO * pLabel = & pHdr->pLabels[j]; 
	    sprintf(tbuf,"\t\t    x%X\t%d\t'%s'\t%s\n",
		    pLabel->uValue,pLabel->uColorNdx,
		    pLabel->czI18NKey,pLabel->pczText);
	    strcat_array(s_outbuf,tbuf);
	    }

	strcat_array(s_outbuf,"\n");
	}
//    logTrace("dump debug 11");
    if (pHdr->uHdrHistLen > 0)
        {
        if (pHdr->histo[0] == 0)
	    { strcat_array(s_outbuf,"HISTOGRAM: \tnot initialized"); }
	else
	    {
	    sprintf(tbuf,"HISTOGRAM: \ttotal=%7ld\n\t\t   ",pHdr->histo[0]);
	    strcat_array(s_outbuf,tbuf);
	    size_t j;
	    for (j=1; j<pHdr->uHdrHistLen; j++)
                {
	        sprintf(tbuf," %6ld%s",
			pHdr->histo[j],((j % 8) == 0) ? "\n\t\t   " : "");
		strcat_array(s_outbuf,tbuf);
		}
	    }
	strcat_array(s_outbuf,"\n");
	}
    if (! pHdr->bExtentInit)
        {
	if (detail > 0)
	    {  strcat_array(s_outbuf,"EXTENTS: \tnot initialized\n"); }
	}
    else
        {
	sprintf(tbuf,
		"EXTENTS: \tX=%8.3f Y=%8.3f to X=%8.3f Y=%8.3f\n",
	       pHdr->dMinX,pHdr->dMinY,pHdr->dMaxX,pHdr->dMaxY);
	strcat_array(s_outbuf,tbuf);
	}
    if ((pHdr->pczMetafile != NULL) && (strlen(pHdr->pczMetafile) > 0))
        {
	sprintf(tbuf,"IGC METAFILE: (offset %X) %s  GUID: %s\n",
		offsetof(IMAGEHDR,pczMetafile),pHdr->pczMetafile,pHdr->pczGUID);
	}
    else
        {  
	sprintf(tbuf,"IGC METAFILE: (offset %X) not initialized\n",
		offsetof(IMAGEHDR,pczMetafile)); 
	}
    strcat_array(s_outbuf,tbuf);

    sprintf(tbuf,"   (dumplength=%d)\n\n",strlen(s_outbuf));
    if (detail > 0)
        {
	sprintf(tbuf,"   (dumplength=%d)\n\n",strlen(s_outbuf));
	strcat_array(s_outbuf,tbuf);
	}
//    logTrace("dump debug 13");
    return s_outbuf;
    }

const char * ImageHdr::ImageTypeName() const
	    { return ((uint)m_uImageType < AY_COUNT(s_czImgTypeNames))
		  ? s_czImgTypeNames[m_uImageType] : "Unknown" ; } 
const char * ImageHdr::ImageTypeName(IMGTYPE_T uType)
	    { return ((uint)uType < AY_COUNT(s_czImgTypeNames))
		  ? s_czImgTypeNames[uType] : "Unknown"; } 
const char * ImageHdr::LayoutName() const
	    { return ((uint)m_hi.uBandLayout < AY_COUNT(s_czLayoutNames))
		  ? s_czLayoutNames[m_hi.uBandLayout] : "Unknown"; } 

		// return NULL if no error,
		// else a description in english of the most recent error
//const char * ImageHdr::getErrorStr()
//    { return "not implemented"; }

		// return NULL if no error,
		// else a tag for an internationalized message 
		// for the most recent error. 
		// Return '' if there is no appropriate tag
//const char * ImageHdr::errorTag()
//   { return NULL; }

ImageHdr::~ImageHdr()
    {
    zero(0);
    }

    /* set to valid but not meaningful values (mostly 0 or NULL)
     * @param bFirstTime	if TRUE, assume ptrs are junk
     *				if FALSE, ignore iIndex
     */
void ImageHdr::zero(BOOL bFirstTime)
    {
      //    if (m_iTrace)
    logTrace("ImageHdr::zero (en) firsttime=%s",YESNO(bFirstTime));
    if (! bFirstTime) /* else assume pointers are meaningless */
	{
	if (m_hi.h_title != NULL) free(m_hi.h_title);
	if (m_hi.h_id != NULL) free(m_hi.h_id);
	if (m_hi.comment != NULL) free(m_hi.comment);
	if (m_hi.source != NULL) free(m_hi.source);
	if (m_hi.scene != NULL) free(m_hi.scene);
	if (m_hi.subscene != NULL) free(m_hi.subscene);
	if (m_hi.band != NULL) free(m_hi.band);
	if (m_hi.h_OriginalFileName != NULL) free(m_hi.h_OriginalFileName);

	if (m_hi.z_unit != NULL) free(m_hi.z_unit);
	if (m_hi.czProjection != NULL) free(m_hi.czProjection);
	if (m_hi.unitname != NULL) free(m_hi.unitname);
	if (m_hi.pczColorFileName != NULL) free(m_hi.pczColorFileName);
	if (m_hi.pLabels != NULL) /* array of LABEL_INFOs */ 
	    {
	    size_t j;
	    for (j=0; j<m_hi.uNumLabels; j++)
		if (m_hi.pLabels[j].pczText != NULL)
		    free(m_hi.pLabels[j].pczText);
	    free(m_hi.pLabels);
	    m_hi.pLabels = NULL;
	    }
//	if (m_hi.pPalette != NULL) delete m_hi.pPalette;
	if (m_hi.histo != NULL) free(m_hi.histo);
	if (m_hi.pczMetafile != NULL) free(m_hi.pczMetafile);
	if (m_hi.pczGUID != NULL) free(m_hi.pczGUID);
	}
    memset(&m_hi,0,sizeof(m_hi));
#if DRAGON_VER >= 6
    m_hi.m_dhImgvar = 0.0;		/* variance of all image data  */ 
    m_hi.m_dhImgsd = 0.0;		/* standard deviation of image data */
#else
    m_hi.imgvar = 0.0;		/* variance of all image data  */ 
    m_hi.imgsd = 0.0;		/* standard deviation of image data */
#endif
    m_hi.dScaleFactor = 0.0;	/* OPTIMAL scale factor or 0.0 */
    m_hi.dScaleOffset = 0.0;	/* OPTIMAL scale offset, or 0.0 */
    m_hi.z_scale = 0.0;
    m_hi.z_offset = 0.0;
    m_hi.xcell_size = 1.0;
    m_hi.ycell_size = 1.0;
    m_hi.ref_x.v0 = 0.0;
    m_hi.ref_y.v0 = 0.0;
    m_hi.bExtentInit = FALSE;
    m_hi.dMinX = m_hi.dMinY = 0.0;
    m_hi.dMaxX = m_hi.dMaxY = 0.0;
    logTrace("ImageHdr::zero (ex)");
    }

		/* Set to a minimum set of values needed to be meaningful.
		 * This sets values specified by calling args.
		 * @param uImgType	File format of new image file
		 * @param pczFtype	type char for Dragon image file:
		 *			"I", "C", "L", or NULL=> "I"
		 *                      8/2006 can also be "V" for Vector
		 *                                         "M" for Metafile
		 * @param uNumLines	number of lines in target image
		 * @param uNumPixels	number of pixels/line in target image
		 * @param uBitsPerPix	if 0, is determined by uImgType
		 *                          DEPRECATED - pass correct value
		 * @param uNumBands	if 0, is determined by uImgType
		 *                          DEPRECATED - pass correct value
		 * @param uNumResolutions if 0, is determined by uImgType
		 *                          DEPRECATED - pass correct value
		 *                          (not used as of 1/2007)
		 * @param pczOriginalName NULL or name of source file
		 * @return		0 if OK else, for this format,:
		 *			-48 memory error
		 */
int ImageHdr::init(IMGTYPE_T uImgType,const char * pczFtype,
		   ushort uNumLines, ushort uNumPixels,
		   ushort uBitsPerPix, ushort uNumBands,
		   ushort uNumResolutions,
		   const char * pczOriginalName)
    {
    int iRetval = 0;
    const char * czMethod = "ImageHdr::init";
    if (m_iTrace)
	Logger::logTrace("%s (en) type=%s this=%p origname='%s'",
			 czMethod,pczFtype,this,NN(pczOriginalName));
    if (m_iDebug)
	fprintf(stderr,"%s (en) type=%s this=%p origname='%s'\n",
		czMethod,pczFtype,this,NN(pczOriginalName));
    m_hi.bBinary = TRUE;	/* initially, assume all these things */
    m_hi.bRectangular = TRUE;
    m_hi.uBands = (uNumBands == 0) ? 1 : uNumBands;
    m_hi.ulDataOffset = 0;	/* bytes from start of file to image data */ 
    m_hi.ulPixelPitch = (uBitsPerPix > 8) ? 2 : 1;
	/* following mostly useful if uBands > 1 */ 
    m_hi.uBandLayout = IMG_PACKED1;
    m_hi.ulLinePitch = (ulong)uNumPixels * m_hi.ulPixelPitch;
    m_hi.ulBandPitch = (uNumBands < 2) ? 0 : m_hi.ulLinePitch * (ulong)uNumLines;
    m_hi.ulDataSize = (ulong)uNumLines * m_hi.ulLinePitch * (ulong)uNumBands;
	/* the following values cannot be changed in any file header 
	 * without having to rewrite the image data as well.
	 */   
    m_hi.ftype[0] = (pczFtype == NULL) ? 'I' : pczFtype[0];
    m_uImageType = uImgType;
    m_hi.size[0] = uNumLines;
    m_hi.size[1] = uNumPixels;
    m_hi.bits_per_pix = (uBitsPerPix > 8) ? 16 : 8;
    if ((pczOriginalName != NULL)
	     && ((m_hi.h_OriginalFileName = strdup(pczOriginalName)) == NULL))
	iRetval = DERR_MEM_ALLOC;
    if (iRetval == 0)
	m_hi.bImageHdrInitialized = TRUE;
    if (m_iTrace)
	logTrace("%s (ex)",czMethod);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) iRetval is %d\n", czMethod,iRetval);
    return iRetval;
    }

	/* revise critical values for an existing writable image.
	 * Only the params with non-default vals will be changed.
	 * This must be invoked BEFORE writing the header
	 * @param pczFilename	NULL => do not change
	 * @param bOverwrite	FALSE => do not change
	 * @param bReReadable	FALSE => do not change
	 * @param uImgType	IT_INVALID => do not change
	 * @param uNumLines	0 => do not change
	 * @param uNumPixels	0 => do not change
	 * @param uBitsPerPix	0 => do not change
	 * @param uNumBands	0 => do not change
	 * @param uNumResolutions 
	 * @param ulPixPitch	0 => accept default calculations
	 * @param ulLinePitch	0 => accept default calculations
	 * @param ulBandPitch	0 => accept default calculations
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int ImageHdr::revise_geom(const char * pczFilename/*=NULL*/, 
			  BOOL bOverwrite/*=FALSE*/,
			  BOOL bReReadable/*=FALSE*/, 
			  IMGTYPE_T uImgType/*=IT_INVALID*/,
			  ushort uNumLines/*=0*/, ushort uNumPixels/*=0*/,
			  ushort uBitsPerPix/*=0*/, ushort uNumBands/*=0*/,
			  ushort uNumResolutions/*=0*/,
			  ulong ulPixPitch /*=0*/,
			  ulong ulLinePitch /*=0*/,
			  ulong ulBandPitch /*=0*/)
    {
    int iRetval = 0;
    if (m_iDebug)
	fprintf(stderr,"ImageHdr::revise_geom (en) args=%s %s %s %s   %d %d %d %d %d  %ld %ld %ld\n",
	       NN(pczFilename),YESNO(bOverwrite),YESNO(bReReadable),
	       ImageHdr::ImageTypeName(uImgType),
	       uNumLines,uNumPixels,uBitsPerPix,uNumBands,uNumResolutions,
	       ulPixPitch,ulLinePitch,ulBandPitch);
    if (m_iTrace)
	logTrace("ImageHdr::revise_geom (en) args=%s %s %s %s   %d %d %d %d %d  %ld %ld %ld",
		 NN(pczFilename),YESNO(bOverwrite),YESNO(bReReadable),
		 ImageHdr::ImageTypeName(uImgType),
		 uNumLines,uNumPixels,uBitsPerPix,uNumBands,uNumResolutions,
		 ulPixPitch,ulLinePitch,ulBandPitch);
    /* ~~~ What do we do with the file name and the flags */
    /* ~~~ WHAT DO WE DO with the IMG TYPE */
    if (uNumLines > 0)
	m_hi.size[0] = uNumLines; 
    if (uNumPixels > 0)
	m_hi.size[1] = uNumPixels;
    if (uBitsPerPix > 0)
        {
	m_hi.bits_per_pix = uBitsPerPix;
	m_hi.ulPixelPitch = (m_hi.bits_per_pix + 7) / 8;
	}
    if (uNumBands > 0)
	m_hi.uBands = uNumBands;
    if (uImgType != IT_INVALID) /* 2014-03-25 - this case had been omitted */
	m_uImageType = uImgType;
    m_hi.bBinary = TRUE;	/* initially, assume all these things */
    m_hi.bRectangular = TRUE;

    /* now make the other fields match the changes */
	/* following mostly useful if uBands > 1 */ 
    m_hi.uBandLayout = IMG_PACKED1;
    m_hi.ulLinePitch = (ulong)m_hi.size[1] * m_hi.ulPixelPitch;
    m_hi.ulBandPitch = (uNumBands < 2) ? 0 
      : m_hi.ulLinePitch * (ulong)uNumLines;
    if (ulPixPitch > 0)
	m_hi.ulPixelPitch = ulPixPitch;
    if (ulLinePitch > 0)
	m_hi.ulLinePitch = ulLinePitch;
    if (ulBandPitch > 0)
	m_hi.ulBandPitch = ulBandPitch;
    m_hi.ulDataSize = (ulong)uNumLines * m_hi.ulLinePitch * (ulong)uNumBands;
    return iRetval;
    }

	/* change scaling information for an existing image.
	 * Only the params with non-default vals will be changed.
	 * This may be invoked after writing the header and the image data
	 * @param dScaleFactor	factor, value for BINARY or OPTIMAL scaling
	 * @param ScaleOffset	offset, value only if OPTIMAL scaling
	 * @param pczScalingType 'B', 'O', 'N'o change, or \0 for none
	 *   ( the following give calibration meaning to pixel values )
	 *   ( if dZ_scale == 0, none of these are set by this fn)
	 *   ( calibrated value = (pixel value * dz_Scale) + dz_offset)
	 * @param dZ_scale	multiplicative factor
	 * @param dZ_offset	additive factor 
	 * @param pcZ_unit 	name of pixel calibration units
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int ImageHdr::update_scaling(double dScaleFactor,
			   double dScaleOffset,
			   const char * pczScalingType,
			   double dZ_scale,
			   double dZ_offset,
			   const char * pcZ_unit)
    {
    int iRetval = 0;
    switch (pczScalingType[0])
       {
       case 'B':
	   m_hi.uScaleFactor = (ushort) dScaleFactor;
	   break;

       case 'O':
	   m_hi.dScaleFactor = dScaleFactor;		
	   m_hi.dScaleOffset = dScaleOffset;
	   break;
	   /* otherwise do nothing */    
       }
    if (dZ_scale > 0.00005)  /* if scaling should be changed */
       {
       m_hi.z_scale = dZ_scale;
       m_hi.z_offset = dZ_offset;
       if (m_hi.z_unit != NULL)
          {
	  free(m_hi.z_unit);
	  m_hi.z_unit = NULL;
          }
       m_hi.z_unit = strdup(pcZ_unit);
       if (m_hi.z_unit == NULL)
          {
	  iRetval = DERR_MEM_ALLOC;
	  }
       }
    if (iRetval == 0)
        {
	m_hi.bImageHdrScalingInit = TRUE;
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_SCALING);
	}
    return iRetval;
    }

	/* change text information (except classnames, unitnames) 
	 * for an existing image.
	 * Only the params with non-NULL vals will be changed.
	 * This may be invoked after writing the header and the image data
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int ImageHdr::update_text(const char * pczTitle,
			  const char * pczId,
			  const char * pczComment,
			  const char * pczSource,
			  const char * pczScene,
			  const char * pczSubscene,
			  const char * pczBand,
			  const char * pczColorfileName,
			  const char * pczFtype)
    {
    int iRetval = 0;
    if (pczTitle != NULL)
        {
        iRetval = freeAndCopy(&(m_hi.h_title), pczTitle);
	}
    if ((iRetval == 0) && (pczId != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.h_id), pczId);
	}
    if ((iRetval == 0) && (pczComment != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.comment), pczComment);
	}
    if ((iRetval == 0) && (pczSource != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.source), pczSource);
	}
    if ((iRetval == 0) && (pczScene != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.scene), pczScene);
	}
    if ((iRetval == 0) && (pczSubscene != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.subscene), pczSubscene);
	}
    if ((iRetval == 0) && (pczBand != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.band), pczBand);
        }
    if ((iRetval == 0) && (pczColorfileName != NULL))
        {
	iRetval = freeAndCopy(&(m_hi.pczColorFileName), pczColorfileName);
	}
    if ((iRetval == 0) && (pczFtype != NULL))
        {
	strcpy_array(m_hi.ftype,pczFtype);
	}
    if (iRetval == 0)
        {
	m_hi.bImageHdrDescriptionInit = TRUE;
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_TEXT);
	}

    return iRetval;
    }

	/* change stats and histogram information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * @param pImgStats	stats for image
	 * @return		0 if OK
	 *                      DERR_MEM_ALLOC if mem alloc of histogram fails
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
int ImageHdr::update_stats(const IMGSTATS * pImgStats)
    {
    int iRetval = 0;
#if DRAGON_VER >= 6
    m_hi.m_ihImgmean = pImgStats->m_ihImgmean;
    m_hi.m_ihImgmax = pImgStats->m_ihImgmax;
    m_hi.m_ihImgmin = pImgStats->m_ihImgmin;
    m_hi.m_dhImgvar = pImgStats->m_dhImgvar;	
    m_hi.m_dhImgsd = pImgStats->m_dhImgsd;
#else
    m_hi.imgmean = pImgStats->imgmean;
    m_hi.imgmax = pImgStats->imgmax;
    m_hi.imgmin = pImgStats->imgmin;
    m_hi.imgvar = pImgStats->imgvar;	
    m_hi.imgsd = pImgStats->imgsd;
#endif
    if (m_hi.histo == NULL)
        {
	m_hi.histo = (UINT32 *)calloc(HDR_HIST_LEN,sizeof(UINT32));
	}
    if (m_hi.histo == NULL)
        {
	iRetval = DERR_MEM_ALLOC;
	}
    else
        {
	int i, j, k, kk;
	m_hi.uHdrHistLen = HDR_HIST_LEN;
	m_hi.histo[0] = pImgStats->hist.imghist[0];
        for (i = 1; i < HDR_HIST_LEN; i++)
            {
            m_hi.histo[i] = 0L;
            if (m_hi.bits_per_pix <= 8)
                {
                if (m_hi.ftype[0] == 'I')
                    {
                    /* bin by fours for saving in the header */
                    for (j = 0; j < 4; j++)
  	              m_hi.histo[i] += 
                          pImgStats->hist.imghist[(i-1)*4+1+j];
                    }
                else  /* for classified images, etc., do not bin */
                      /* just copy the first 64 values */
                    {
                    m_hi.histo[i] = 
                          pImgStats->hist.imghist[i];
                    }

                }  /* end if bpp <= 8 */
            else   /* if > 8 bit data, each element of pImgStats histogram */
		   /* is a pointer to a second level histogram */
                {
                k = (i-1) * 4;
                for (j = 0; j < 4; j++)
                    {
                    if (pImgStats->hist.ptrhist.ptr_array[k+j] == NULL)
                       continue;
                    for (kk = 0; kk < IMG_HIST_LEN -1; kk++)
    	                m_hi.histo[i] += 
                           pImgStats->hist.ptrhist.ptr_array[k+j][kk];
                    }                        
               }  /* end if > 8 bpp */
            }   /* end for loop through header histogram */
	}  /* end else - if mem alloc ok or not needed */
    if (iRetval == 0)
        {
	m_hi.bImageHdrStatsInit = TRUE;
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_STATS);
	}
    return iRetval;
    }

	/* change georeferencing information information for an existing image.
	 * This may be invoked after writing the header and the image data
	 *
	 * NOTE: ref_x, ref_y, pczProjection, pczUnitname 
	 *	 may be NULL to indicate no change
	 *	 but other args MUST be supplied.
	 *
	 * @param img_x    	+/- pixel num of origin/fixed point-usually 0
	 * @param img_y    	+/- line number of fixed point - usually 0 
	 * @param ref_x    	NULL or ptr to map/ref x coord of fixed point
	 * @param ref_y    	NULL or ptr to map/ref y coord of fixed point 
	 * @param xcell_size  	size of one cell in X direction at fixed pt 
	 * @param ycell_size 	size of one cell in Y direction at fixed pt
	 *                    	if negative, the corresponding axis is reversed
	 *		      	relative to the image coordinate system.
	 * @param pczProjection NULL or code for map proj'n 
	 * @param pczUnitname	NULL or map unit name 
	 * @param pczDateTime	NULL or date, time of image acquisition
	 *			in form yyyy:mm:dd HH:MM:SS
	 * @param pczUTMZone	NULL or utmzone in form [1-60][N|S]
	 * @param iRegistered	<0 => don't change 0 => FALSE >0 => TRUE
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int ImageHdr::update_georef(int img_x, int img_y, 
			    const MapCoord * ref_x, const MapCoord * ref_y,
			    double xcell_size, double ycell_size,
			    const char* pczProjection, const char* pczUnitname,
			    const char * pczDateTime,const char * pczUTMZone,
			    int iRegistered)
    {
    int iRetval = 0;
    if (m_iDebug)
	fprintf(stderr,"ImageHdr::update_georef "
	       "args: %d %d %8.3f %8.3f %8.3f %8.3f %s %s\n",
	       img_x, img_y, 
	       (ref_x == NULL) ? -11111.0 : ref_x->v0, 
	       (ref_y == NULL) ? -11111.0 : ref_y->v0,
	       xcell_size, ycell_size,
	       (pczProjection == NULL) ? "(NULL)" : pczProjection,
	       (pczUnitname == NULL) ? "(NULL)" : pczUnitname);
//    if (m_iTrace)
	logTrace("ImageHdr::update_georef "
	       "args: %d %d %8.3f %8.3f %8.3f %8.3f %s %s",
	       img_x, img_y, 
	       (ref_x == NULL) ? -11111.0 : ref_x->v0, 
	       (ref_y == NULL) ? -11111.0 : ref_y->v0,
	       xcell_size, ycell_size,
	       (pczProjection == NULL) ? "(NULL)" : pczProjection,
	       (pczUnitname == NULL) ? "(NULL)" : pczUnitname);
    m_hi.img_x = img_x;
    m_hi.img_y = img_y;
    m_hi.xcell_size = xcell_size;
    m_hi.ycell_size = ycell_size;
    if (ref_x != NULL)
	memcpy(&(m_hi.ref_x), ref_x, sizeof(MapCoord));  /* this is a struct */
    if (ref_y != NULL)
	memcpy(&(m_hi.ref_y), ref_y, sizeof(MapCoord)); 

    if (pczProjection != NULL)
	iRetval = freeAndCopy(&(m_hi.czProjection), pczProjection);
    if ((iRetval == 0) && (pczUnitname != NULL))
        {
	    // actually, this is probably done in TiffImageReader, not here
	if ((pczUnitname != NULL) && (strcasecmp(pczUnitname,"linear_meter") == 0))
	    iRetval = freeAndCopy(&(m_hi.unitname), "Meter");
	else
	    iRetval = freeAndCopy(&(m_hi.unitname), pczUnitname);
	}
    if ((iRetval == 0) && (pczDateTime != NULL))
	iRetval = freeAndCopy(&(m_hi.czDateTime), pczDateTime);
    if ((iRetval == 0) && (pczUTMZone != NULL))
	iRetval = freeAndCopy(&(m_hi.czUTMZone), pczUTMZone);
    if ((iRetval == 0) && (iRegistered >= 0))
	m_hi.bRegistered = (iRegistered > 0);
    if (iRetval == 0)
        {
	m_hi.georef_init = TRUE;
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_GEOREF);
	}
    return iRetval;
    }

	/* change labels information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * @param iNumLabels	-1 for don't change the number of
         *                      labels, or number of labels in img
	 *                      If different from than the current 
	 *                      number of labels, we will discard 
	 *                      all the old labels and replace with the
	 *                      ones passed in. If -1, or the same
	 *                      as the current number, we only replace
	 *                      the first "uArrayCount" labels.
	 * @param uArrayCount	number of items in pLabels
	 * @param pLabels	label info
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
int ImageHdr::update_labels(int iNumLabels,
			  size_t uArrayCount,
			  const LABEL_INFO * pLabels)
    {
    int iRetval = 0;
    uint j = 0;
    if (m_iDebug)
       {
       fprintf(stderr,"ImageHdr::update_labels (en) numlabels=%d array count=%d ptr to array=%p\n", 
	      iNumLabels, uArrayCount, pLabels);
       }
    logTrace("ImageHdr::update_labels (en) numlabels=%d array count=%d ptr to array=%p", 
	      iNumLabels, uArrayCount, pLabels);
      
    /* if we are changing the number of labels 
     * then get rid of the old ones (if any)
     */ 
    if ((iNumLabels >= 0) && (iNumLabels != (int) m_hi.uNumLabels))
        {
	if (m_hi.pLabels != NULL)
	    {
	    for (j = 0; j < m_hi.uNumLabels; j++)
	        {
		if (m_hi.pLabels[j].pczText != NULL)
		    free(m_hi.pLabels[j].pczText);
	        }
	    free(m_hi.pLabels);
	    m_hi.pLabels = NULL;
	    }
	}
    if (iNumLabels >= 0)
	m_hi.uNumLabels = (unsigned) iNumLabels;
    if (m_hi.pLabels == NULL)
        {
	m_hi.pLabels = (LABEL_INFO*) calloc(iNumLabels,sizeof(LABEL_INFO));
	if (m_hi.pLabels == NULL)
	    iRetval = DERR_MEM_ALLOC;
        }
    if (iRetval == 0)
        {
	for (j = 0; (j < uArrayCount) && (iRetval == 0); j++)
	    {
	    const LABEL_INFO * tempSrc = &pLabels[j];
	    LABEL_INFO * tempDest = &m_hi.pLabels[j];
	    tempDest->uValue = tempSrc->uValue;
	    tempDest->uColorNdx = tempSrc->uColorNdx;
	    strcpy(tempDest->czI18NKey, tempSrc->czI18NKey);
	    if (tempDest->pczText != NULL)
	        {
		free(tempDest->pczText);
		tempDest->pczText = NULL;
		}
	    tempDest->pczText = strdup(tempSrc->pczText);
	    if (tempDest->pczText == NULL)
	       {
	       logTrace("Memory alloc failure on label %d", j);
	       iRetval = DERR_MEM_ALLOC;
	       }
	    }
        }
    if (iRetval == 0)
        {
	m_hi.bImageHdrClassifyInit = TRUE;
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_LABELS);
	}
    
    logTrace("ImageHdr::update_labels (ex) returning=%d",iRetval);
    return iRetval;
    }

	/* change metafile information 
	 * for an existing image.
	 * Only the params with non-NULL vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int ImageHdr::update_metainfo(const char * pczMetafile,
			  const char * pczGuid)
    {
    int iRetval = 0;
    const char * czMethod = "ImageHdr::update_metainfo";
    if (m_iDebug)
       {
       fprintf(stderr,"%s (en) metafile='%s' guid='%s'\n",
	      czMethod,NN(pczMetafile),NN(pczGuid));
       }
    logTrace("%s (en) metafile='%s' guid='%s'",
	      czMethod,NN(pczMetafile),NN(pczGuid));

    if (pczMetafile != NULL)
        {
        iRetval = freeAndCopy(&(m_hi.pczMetafile), pczMetafile);
	}
    if ((iRetval == 0) && (pczGuid != NULL))
        {
        iRetval = freeAndCopy(&(m_hi.pczGUID), pczGuid);
	}
    if (iRetval == 0)
        {
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_META);
	}
    return iRetval;
    }

	/* change extent information for an existing image.
	 * This may be invoked after writing the header and the image data
	 *
	 * NOTE: all values must be supplied. If all four values are
         * 0 then we assume extent is not initialized.
	 *
	 * @param minX    	min X value in extent
	 * @param minY    	min Y value in extent
	 * @param maxX    	max X value in extent
	 * @param maxY    	max Y value in extent
	 * @return		0 if OK
	 *			DERR_MEM_ALLOC if allocation fails
	 */
int ImageHdr::update_extent(double minX, double minY,
			    double maxX, double maxY)
    {
    int iRetval = 0;
    const char * czMethod = "ImageHdr::update_extent";
    if (m_iDebug)
        fprintf(stderr,"%s (en) %f %f %f %f\n",czMethod, minX,minY,maxX,maxY);
    logTrace("%s (en)  %f %f %f %f",czMethod, minX,minY,maxX,maxY);
    m_hi.dMinX = minX;
    m_hi.dMinY = minY;
    m_hi.dMaxX = maxX;
    m_hi.dMaxY = maxY;
    if (m_iDebug)
        fprintf(stderr,"%s mid\n",czMethod);
    if ((minX < maxX) && (minY < maxY))
        m_hi.bExtentInit = TRUE;
    else
        m_hi.bExtentInit = FALSE;
    if (iRetval == 0)
        {
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_EXTENT);
	}
    if (m_iDebug)
        fprintf(stderr,"%s (ex) returns %d\n",czMethod,iRetval);
    return iRetval;
    }

	/* change originalfile information 
	 * for an existing image.
	 * Only the params with non-NULL or >= 0 vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int ImageHdr::update_original(uint uOriginalBandCount,
			    uint uOriginalBandNumber,
			    const char * pczOriginalFileName)
    {
    int iRetval = 0; 
    const char * czMethod = "ImageHdr::update_original";
    if (m_iDebug)
       {
       fprintf(stderr,"%s (en) count=%d number=%d name=%s\n", 
	      czMethod,uOriginalBandCount,uOriginalBandNumber,NN(pczOriginalFileName));
       }
    logTrace("%s (en)  count=%d number=%d name=%s", 
	      czMethod,uOriginalBandCount,uOriginalBandNumber,NN(pczOriginalFileName));

    if (uOriginalBandCount >= 0) /* 0 -> unknown? */
        m_hi.h_uOriginalBandCount = uOriginalBandCount;
    if (uOriginalBandNumber >= 0) /* 0-based */
        m_hi.h_uOriginalBandNumber = uOriginalBandNumber;
    if (pczOriginalFileName != NULL)
        {
        iRetval = freeAndCopy(&m_hi.h_OriginalFileName, pczOriginalFileName);
	}
    if (iRetval == 0)
        {
	m_uUpdates =  (HDR_UPDATES_t) (m_uUpdates | IMG_UPDATE_ORIGINAL);
	}
    if (m_iDebug)
       {
       fprintf(stderr,"%s (ex) returns %d\n", czMethod,iRetval);
       }
    logTrace("%s (ex) returns %d", czMethod,iRetval);
    return iRetval;
    }

	/* Helper function. Checks to see if pointer pointed to
	 * by destination pointer is not null. If it is not, frees it, 
	 * and sets it to null. Then tries to strdup the source pointer
	 * and assign it to the destination.
	 * @param pczDestStringPointer - pointer to be freed & initialized
	 * @param pczSourceString      - string to be assigned 
	 * @return   0 or error from memory allocation failure.
	 */
int ImageHdr::freeAndCopy(char ** pczDestStringPointer, 
			  const char * pczSourceString)
   {
   int iRetval = 0;
   if (*pczDestStringPointer != NULL)    
      {
      free(*pczDestStringPointer);
      *pczDestStringPointer = NULL;
      }
   //fprintf(stderr,"About to strdup '%s'\n",pczSourceString);
   *pczDestStringPointer = strdup(pczSourceString);
   if (*pczDestStringPointer == NULL)
      {
      iRetval = DERR_MEM_ALLOC;	  
      }
   return iRetval;
   }

		// read specified file and initialize IMAGEHDR
		// Assumes caller has already verified that
		// file exists and has read permissions
		// @param pczName	name of file to read
		// @param pSel		specify band of multiband file
		// @param pImg		some readers may need this
		// @return		reader if OK 
		// 			else NULL
		// 2011-02-25 ktr return NULL if any fatal error
ImageReader * ImageHdr::read(const char * pczName,
			     const IMAGEDATA_SELECTOR * pSel, 
			     Image * pImg)
    { 
    ImageReader * pIHR = imageReaderFactory(pczName);
    const char * czMethod = "ImageHdr::read";
    if (m_iDebug)
	fprintf(stderr,"%s (en) file '%s' m_iDebug=%d m_iTrace=%d pIHR=%p\n",
		czMethod,pczName,m_iDebug,m_iTrace,pIHR);
    if (m_iTrace)
	logTrace("%s (en) file '%s' m_iDebug=%d m_iTrace=%d pIHR=%p",
		 czMethod,pczName,m_iDebug,m_iTrace,pIHR);
    if (pIHR != NULL)
        {
 	pIHR->SetDesiredData(pSel);
	BOOL bSuccess = pIHR->readHeader(pczName,&m_hi,&m_iErrno,pImg);
	if (bSuccess && (m_hi.h_OriginalFileName == NULL))
            {
	    const char * pBs = strrchr(pczName,'\\');
	    const char * pFs = strrchr(pczName,'/');
	    const char * pCol = strrchr(pczName,':');
	    const char * pNode = (pBs > pFs) ? pBs+1
		: (pFs > pCol) ? pFs+1 : (pCol != NULL) ? pCol+1 : pczName;
	    if (m_iDebug)
		fprintf(stderr,"    %s assigning '%s' as original name\n",
			czMethod,pNode);
	    m_hi.h_OriginalFileName = strdup(pNode);
	    }
	}
    if (m_iTrace)
	logTrace("%s (ex) file '%s' pIHR=%p err=%d",
		 czMethod,pczName,pIHR,m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) file '%s' pIHR=%p err=%d\n",
		 czMethod,pczName,pIHR,m_iErrno);
    return ((m_iErrno < DERR_OK) && (m_iErrno > DERR_NON_FATAL)) ? NULL : pIHR;
    }

		// return a reader which can read the specified file
		// or NULL
ImageReader * ImageHdr::imageReaderFactory(const char * pczName)
    {
    ImageReader * pReader = NULL;
#undef FN_NAME
#define FN_NAME "ImageHdr::imageReaderFactory"

    if (m_iDebug)
        fprintf(stderr,FN_NAME " (en) file=%s\n",pczName);
    if (m_iTrace)
        logTrace(FN_NAME " (en) file=%s",pczName);
    if (DragonImageReader::test(pczName,m_iDebug))
        {
	pReader = new DragonImageReader(m_iDebug,m_iTrace);
	}
    else if (DragonImageReader::vectest(pczName,m_iDebug))
        {
	pReader = new DragonImageReader(m_iDebug,m_iTrace);
	}
    else if (DragonImageReader::metatest(pczName,m_iDebug))
        {
	pReader = new DragonImageReader(m_iDebug,m_iTrace);
	}
    else if (TiffImageReader::test(pczName,m_iDebug))
        {
	pReader = new TiffImageReader(m_iDebug,m_iTrace);
	}
    else if (DragonOldImageReader::test(pczName,m_iDebug))
        {
	pReader = new DragonOldImageReader(m_iDebug,m_iTrace);
	}
#if ! defined ROSE_ONLY // imageReaderFactory in rosetta only needs Dragon/TIFF images
    else if (ScreenImageReader::test(pczName,m_iDebug))
        {
	pReader = new ScreenImageReader(m_iDebug,m_iTrace);
	}
	        // this must be the last one in the list
    else if (ExternImageReader::test(pczName,m_iDebug,m_iTrace))
        {     	// else serch the objects tree for candidates
		// (fconvert, used by Import/Custom, uses this) 
	pReader = new ExternImageReader(m_iDebug,m_iTrace);
	m_uImageType = IT_EXTERN;
	}
#endif
    if (pReader != NULL)
        {
	m_uImageType = pReader->getImageType();
	pReader->m_pHdr = &m_hi;
	}
    if (pReader != NULL)
        {
	const char * pczDump = pReader->dump(1);
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " (ex) Found reader object: %s\n",pczDump);
	if (m_iTrace)
	    logTrace(FN_NAME " (ex) Found reader object: %s",pczDump);
	}
    else
        {
	m_iErrno = DERR_UNSUP_FORMAT;
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " (ex) reader %s object not found\n",
		    VERR);
	if (m_iTrace)
	    logTrace(FN_NAME " (ex) reader object not found in %s library",VERR);
	}
    return pReader;
    }
 		
		// return a writer which can write the specified file
		// or NULL
ImageWriter * ImageHdr::imageWriterFactory(IMGTYPE_T uFormat) const
    {
    ImageWriter * pWrtr = NULL;
    if (m_iDebug)
	fprintf(stderr,"ImageHdr::imageWriterFactory - uFormat is %d\n",
		uFormat);
    if ((uFormat == IT_DRAGON) || (uFormat == IT_DRAGON_VEC))
	pWrtr = new DragonImageWriter(m_iDebug,m_iTrace);
    else if (uFormat == IT_IGC_META)
	pWrtr = new DragonImageWriter(m_iDebug,m_iTrace);
#if ! defined ROSE_ONLY // imageWriterFactory in rosetta only needs Dragon images
    else if (uFormat == IT_DRAGON_OLD)
	pWrtr = new DragonOldImageWriter(m_iDebug,m_iTrace);
    else if (uFormat == IT_TIFF)
	pWrtr = new TiffImageWriter(m_iDebug,m_iTrace);
//    else if (uFormat == IT_JPEG)
//	pWrtr = new JpegImageWriter(m_iDebug,m_iTrace);
    else if ((uFormat == IT_CHUNK54) || (uFormat == IT_CHUNK60))
	pWrtr = new ScreenImageWriter(m_iDebug,m_iTrace);
#endif // if ! defined ROSE_ONLY // imageWriterFactory in rosetta only needs Dragon images
//    if (pWrtr != NULL)
//	pWrtr->m_pHdr = &m_hi;
    if ((pWrtr != NULL) && m_iDebug)
	fprintf(stderr,"ImageHdr::imageWriterFactory returning writer object: %s\n",
	       pWrtr->dump());
    if ((pWrtr != NULL) && m_iTrace)
	logTrace("ImageHdr::imageWriterFactory returning writer object: %s",
	       pWrtr->dump());
    return pWrtr;
    }
 		
#if defined ROSE_ONLYXX
// these are dummy fns to satisfy links in img.cpp
#include "img.h"
#include "imageReader.h"
class ImageWriter;
ImageReader * ImageHdr::read(const char * pczName,
			     const IMAGEDATA_SELECTOR * pSel, 
			     Image * pImg)
    { 
    return NULL;
    }
ImageReader * ImageHdr::imageReaderFactory(const char * pczName)
    {
    return NULL;
    }
ImageWriter * ImageHdr::imageWriterFactory(IMGTYPE_T uFormat) const
    {
    return NULL;
    }
#endif

void IMAGEHDR_END() { puts(FIL_ID); }

#ifdef TEST

static char* czFile[] = { "","mekdmdm.img",
			  "mek14-1.img","alfagood.img",
			  "viewpt-1.ch"} ;
static char* czFileDescr[] = { "","v 4.1 classified English labels",
			  "v 1.0 8-bit","v 4.1 16-bit",
			  "chunk file"} ;
void usage()
    {
    printf ("Test some file header I/O\n");
    printf ("Usage: dhead.TEST [-v [-v]] [-f filepath [-o outformat]] -t testno\n");
    printf ("	-v => verbose (-v -v) is even more)\n");
    printf ("	-t => test number. Available are:\n");
    printf ("		0 = Read specified file or none\n");
    for (size_t j=1; j<5; j++)
	printf ("		%d = Read file %s: %s\n",
		j,czFile[j],czFileDescr[j]);
    printf ("	-f => file to read for test 0 or write for tests 1...n\n");
    printf ("	-o => when used with tests 1...n also write new file in specified format\n");
    printf ("         Available formats may include: \n");
#if defined ROSE_ONLY
    printf ("		DRAGON DRAGON_OLD TIFF CHUNK54 CHUNK60 DRAGON_VEC BIL_ESRI CEOS_ASTER\n"
            "		JPG ERDAS BIL BSQ \n");
#else
    printf ("		DRAGON DRAGON_OLD TIFF CHUNK54 CHUNK60 DRAGON_VEC EXTERN\n");
#endif
    exit (1);
    }

int main(int argc, char ** argv)
    {
    int iVerbose = 0;
    int iTestNum = -1;
    char czFilename[PATH_MAX] = "";
    char czReadFile[PATH_MAX] = "../../../OpenDragon/testdata/";
    char czFormatName[20] = "";
    IMGTYPE_T uOutFormat = IT_UNINIT;
    
    if (argc < 2)
	usage();
    while (--argc > 0)
        {
	if (strcmp(*(++argv),"-?") == 0)
	    usage();
	else if (strcmp(*argv,"-v") == 0)
	    iVerbose++;
	else if (strcmp(*argv,"-t") == 0)
	    { iTestNum = atoi(*(++argv)); --argc; }
	else if (strcmp(*argv,"-f") == 0)
	    { strcpy(czFilename,*(++argv)); --argc; }
	else if (strcmp(*argv,"-o") == 0)
	    { 
	    strcpy(czFormatName,"IT_");
	    strcat(czFormatName,*(++argv)); --argc;
	    }
	else
	    usage();
        }
    if (iTestNum != 0)
        { strcat_array(czReadFile,czFile[iTestNum]); }
    else if (strlen(czFilename) > 0)
        {
	strcpy_array(czReadFile,czFilename);
	}
    else
	usage();
    ImageHdr im0(iVerbose,0);
    if (strlen(czFormatName) > 0)
        {
	uOutFormat = IT_INVALID;
	for (int j = IT_DRAGON; j<IT_INVALID; j++)
	    {
	    if (strcmp(ImageHdr::ImageTypeName((IMGTYPE_T)j),czFormatName) == 0)
	        {
		uOutFormat = (IMGTYPE_T)j;
		break;
	        }
	    }
	}
    if (iVerbose)
        {
	fprintf(stderr,"\nmain(en) test number %d from file %s outformat %s=%d\n",
	       iTestNum,czReadFile,czFormatName,uOutFormat);
	fprintf(stderr,"    (sizes UINT32=%d uint=%d ushort=%d ulong=%d double=%d)\n",
	       sizeof(UINT32),sizeof(unsigned int),sizeof(ushort),
	       sizeof(ulong),sizeof(double));
	}
    Image img0;
    /*    ImageReader * pRdr = */ im0.read(czReadFile,NULL);
    fprintf(stderr,"Read of %s status=%d=%s\n",
	    czReadFile,im0.getErrorNo(),im0.getErrorMessage());
    fprintf(stderr,"Dump of header: %s\n",im0.dump(iVerbose,czReadFile));
    if (uOutFormat == IT_INVALID)
	printf ("Unable to create %s header: format not supported\n",
		czFormatName);
    else if (uOutFormat != IT_UNINIT)
        {
	ImageWriter * wrtr = im0.imageWriterFactory(uOutFormat);
	int errnum = 0;
	BOOL bOK = FALSE;
	if (wrtr != NULL)
	    bOK = wrtr->writeHeader(czFilename,im0.getImageHdr(),&errnum);
	printf ("creating %s header in %s: succeeded: %s errnum=%d\n",
		czFormatName,czFilename,YESNO(bOK),errnum);
	}
//    fprintf(stderr,"error %d = %s\n",50,dragonErrorMessage(-50));
//    fprintf(stderr,"error %d = %s\n",60,dragonErrorMessage(-60));
//    fprintf(stderr,"error %d = %s\n",70,dragonErrorMessage(-70));
    return 0;
    }
#endif
