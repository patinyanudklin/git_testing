extern "C"
{
#include "drelease.h"
char IMG_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.145 $$Date: 2015/01/21 10:37:33 $";
D_REL_IDSTR;
}
/*
 *	filename img.cpp
 *		$Revision: 1.145 $ $Date: 2015/01/21 10:37:33 $	
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
 *
 ***************************************************
 *  $Id: img.cpp,v 1.145 2015/01/21 10:37:33 rudahl Exp $
 *  $Log: img.cpp,v $
 *  Revision 1.145  2015/01/21 10:37:33  rudahl
 *  improving imageReader - 2drag coordination
 *
 *  Revision 1.144  2015/01/02 05:22:41  rudahl
 *  avoid having m_iErrno with non-error value
 *
 *  Revision 1.143  2015/01/02 03:59:57  rudahl
 *  improved tracing
 *
 *  Revision 1.142  2014/12/29 03:28:29  rudahl
 *  convert to using dragon version number
 *
 *  Revision 1.141  2014/12/07 12:05:45  rudahl
 *  adapt to OpenDragon
 *
 *  Revision 1.140  2014/12/05 07:06:20  rudahl
 *  tracing
 *
 *  Revision 1.139  2014/04/01 07:22:21  rudahl
 *  lint esp from old mingc
 *
 *  Revision 1.138  2014/03/28 14:51:12  rudahl
 *  working on auto import
 *
 *  Revision 1.137  2014/03/15 10:28:26  rudahl
 *  improved tracing
 *
 *  Revision 1.136  2014/03/08 06:02:18  rudahl
 *  improve debug, comments
 *
 *  Revision 1.135  2014/03/01 01:45:40  rudahl
 *  added create() for foreign files, for rosetta
 *
 *  Revision 1.134  2012/07/01 09:30:27  rudahl
 *  fix problems importing GeoEye tiff files
 *
 *  Revision 1.133  2012/02/10 04:11:01  rudahl
 *  imported OpenDragon fixes to 16-bit histogram, etc
 *
 *  Revision 1.132  2012/02/06 01:53:45  rudahl
 *  clean up and document calcImageScale
 *
 *  Revision 1.131  2012/02/05 11:28:53  rudahl
 *  added tracing
 *
 *  Revision 1.130  2012/01/02 02:55:28  rudahl
 *  add readimage,saveimage
 *
 *  Revision 1.129  2011/12/13 13:32:36  rudahl
 *  write chunk file in linux actually creates JPG
 *
 *  Revision 1.128  2011/10/18 02:20:29  rudahl
 *  testing region growing module clsItemize
 *  So VERS=P_RT does not link in the verify_key fn
 *
 *  Revision 1.127  2011/02/27 08:24:51  rudahl
 *  final work on tiff IO
 *
 *  Revision 1.126  2011/02/06 10:30:11  rudahl
 *  tracing
 *
 *  Revision 1.125  2011/02/05 10:41:17  rudahl
 *  improved tracing
 *
 *  Revision 1.124  2011/01/12 04:42:34  rudahl
 *  added new registration fields to update_georef and header
 *
 *  Revision 1.123  2011/01/03 06:30:29  rudahl
 *  improved tracing
 *
 *  Revision 1.122  2010/12/11 07:49:22  rudahl
 *  change Linear_meter to meter
 *
 *  Revision 1.121  2010/12/05 03:55:53  rudahl
 *  documentation
 *
 *  Revision 1.120  2010/11/14 19:15:54  rudahl
 *  added creation of DROF EVAL version
 *
 *  Revision 1.119  2008/09/27 08:17:16  rudahl
 *  improved tracing
 *
 *  Revision 1.118  2008/06/19 12:05:50  rudahl
 *  testing blob access
 *
 *  Revision 1.117  2008/06/19 08:39:22  rudahl
 *  testing blob access
 *
 *  Revision 1.116  2008/06/19 08:24:32  rudahl
 *  testing blob access
 *
 *  Revision 1.115  2008/06/19 07:48:29  rudahl
 *  testing blob access
 *
 *  Revision 1.114  2008/06/19 07:12:42  rudahl
 *  testing blob access
 *
 *  Revision 1.113  2008/06/19 06:22:42  rudahl
 *  testing blob access
 *
 *  Revision 1.112  2008/06/19 06:00:33  rudahl
 *  testing blob access
 *
 *  Revision 1.111  2008/06/19 05:56:12  rudahl
 *  testing blob access
 *
 *  Revision 1.110  2008/06/14 10:15:28  rudahl
 *  added LinesBlob to trailer
 *
 *  Revision 1.109  2008/04/27 10:32:10  rudahl
 *  improved notices, tracing
 *
 *  Revision 1.108  2008/04/27 06:01:08  rudahl
 *  improved notices, tracing
 *
 *  Revision 1.107  2008/04/05 11:46:24  rudahl
 *  tracing
 *
 *  Revision 1.106  2008/03/24 02:17:05  rudahl
 *  improved tracing msgs
 *
 *  Revision 1.105  2007/10/09 11:22:00  goldin
 *  set image.lines and image.pixels in creating new image
 *
 *  Revision 1.104  2007/10/03 10:13:36  rudahl
 *  simplify symbols matching dlimits
 *
 *  Revision 1.103  2007/08/07 09:21:56  rudahl
 *  added tracing
 *
 *  Revision 1.102  2007/08/02 12:50:40  rudahl
 *  part of 32-bit convert; IMG now has signed params
 *
 *  Revision 1.101  2007/07/11 11:11:00  goldin
 *  updated documentation
 *
 *  Revision 1.100  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.99  2007/05/13 06:35:10  goldin
 *  Set unsupported format error if all image tests fail
 *
 *  Revision 1.98  2007/02/11 06:51:54  goldin
 *  make sure that Synch functions are always called when opening an image
 *
 *  Revision 1.97  2007/02/05 11:11:01  goldin
 *  fix error in dump
 *
 *  Revision 1.96  2007/01/29 10:36:14  rudahl
 *  better propagation of iTrace,iDebug
 *
 *  Revision 1.95  2007/01/26 06:38:57  goldin
 *  Handle 0 bits/pix correctly in create functions
 *
 *  Revision 1.94  2007/01/01 14:27:38  rudahl
 *  error in printf
 *
 *  Revision 1.93  2007/01/01 13:35:51  rudahl
 *  improving tracing
 *
 *  Revision 1.92  2007/01/01 09:42:47  rudahl
 *  improved tracing, dumps; originalfileinfo
 *
 *  Revision 1.91  2006/12/31 12:12:41  rudahl
 *  fixing up the external driver and trailer access
 *
 *  Revision 1.90  2006/12/11 07:45:35  rudahl
 *  enhanced tracing around the update_ fns
 *
 *  Revision 1.89  2006/11/24 02:31:12  rudahl
 *  added IMAGEDATA_SELECTOR arg to open
 *
 *  Revision 1.88  2006/08/20 11:04:52  goldin
 *  Add fields for metafile and extent to Dragon header, reader and writer
 *
 *  Revision 1.87  2006/08/05 10:34:10  goldin
 *  Move inline functions
 *
 *  Revision 1.86  2006/04/30 05:18:45  rudahl
 *  added keyn to dump
 *
 *  Revision 1.85  2006/04/19 09:55:22  goldin
 *  Moved getWorkingBits to img.cpp
 *
 *  Revision 1.84  2006/03/04 08:14:41  rudahl
 *  improve tracing
 *
 *  Revision 1.83  2006/01/19 09:21:05  rudahl
 *  improved dump
 *
 *  Revision 1.82  2005/12/31 05:18:26  rudahl
 *  improved error reporting on create()
 *
 *  Revision 1.81  2005/12/30 10:38:20  rudahl
 *  lintish
 *
 *  Revision 1.80  2005/12/30 09:25:59  goldin
 *  Allow reading beyond working lines/pixels
 *
 *  Revision 1.79  2005/12/21 06:18:13  goldin
 *  bullet proof handling of labels - don't do calloc of zero labels!
 *
 *  Revision 1.78  2005/11/29 09:22:32  goldin
 *  moved NN macro to dtypes.h
 *
 *  Revision 1.77  2005/11/19 10:00:12  goldin
 *  Improve error propagation
 *
 *  Revision 1.76  2005/11/17 09:28:02  goldin
 *  Make modifiable images rereadable by default
 *
 *  Revision 1.75  2005/11/17 08:20:51  goldin
 *  check to make sure trailer read
 *
 *  Revision 1.74  2005/10/02 15:38:26  rudahl
 *  spurious printf
 *
 *  Revision 1.73  2005/09/25 12:13:35  rudahl
 *  improved tracing
 *
 *  Revision 1.72  2005/09/17 11:01:13  rudahl
 *  improved dump
 *
 *  Revision 1.71  2005/09/17 05:28:34  rudahl
 *  improved dump, trace, docs; ProcessRect
 *
 *  Revision 1.70  2005/09/12 07:30:41  rudahl
 *  fixes re dp.h
 *
 *  Revision 1.69  2005/07/22 15:12:32  rudahl
 *  added header fields, functions
 *
 *  Revision 1.68  2005/07/04 13:37:55  rudahl
 *  working with toollibs
 *
 *  Revision 1.67  2005/07/03 13:30:52  rudahl
 *  improving createImage
 *
 *  Revision 1.66  2005/06/27 11:47:25  rudahl
 *  added some access fns, improved dump
 *
 *  Revision 1.65  2005/06/26 06:18:15  rudahl
 *  moved pFp from Image to ImageReader,Writer
 *
 *  Revision 1.64  2005/04/28 13:27:28  goldin
 *  change documentation for revise_geometry
 *
 *  Revision 1.63  2005/04/08 13:24:59  goldin
 *  Add more tracing
 *
 *  Revision 1.62  2005/04/07 10:24:26  rudahl
 *  cleaned up some arg lists and tracing
 *
 *  Revision 1.61  2005/04/06 12:15:16  rudahl
 *  fixed probs in revise_geometry
 *
 *  Revision 1.60  2005/04/06 09:27:17  rudahl
 *  expanded revise_geometry
 *
 *  Revision 1.59  2005/04/05 08:01:18  rudahl
 *  cleaned up spurious printfs
 *
 *  Revision 1.58  2005/04/03 10:37:38  goldin
 *  Adding debug statements
 *
 *  Revision 1.57  2005/04/01 08:54:40  goldin
 *  return state in open
 *
 *  Revision 1.56  2005/03/31 13:30:04  goldin
 *  call functions to update image stats fields 
 *   from header stats fields under all circumstances
 *
 *  Revision 1.55  2005/03/27 12:48:25  rudahl
 *  tracing fixes
 *
 *  Revision 1.54  2005/03/19 07:58:50  rudahl
 *  make img.TEST work for chunk files
 *
 *  Revision 1.64  2005/03/16 04:06:53  rudahl
 *  fixing writeTrailer tests
 *
 *  Revision 1.63  2005/03/13 02:40:59  rudahl
 *  fix probs found working with enhance
 *
 *  Revision 1.62  2005/03/11 22:45:13  goldin
 *  Debug update_labels
 *
 *  Revision 1.61  2005/03/11 20:27:54  goldin
 *  debugging rewriteImageHeader
 *
 *  Revision 1.60  2005/03/11 17:10:34  rudahl
 *  revised zero, CloseImage, rewriteHeader
 *
 *  Revision 1.59  2005/03/10 22:44:35  rudahl
 *  cleared needed updates
 *
 *  Revision 1.58  2005/03/10 22:41:12  rudahl
 *  added rewriteHeader
 *
 *  Revision 1.57  2005/03/10 21:33:33  goldin
 *  Working on new test
 *
 *  Revision 1.56  2005/03/10 04:28:01  rudahl
 *  fixes for writing
 *
 *  Revision 1.55  2005/03/10 03:18:31  goldin
 *  Still working on img_acc test code
 *
 *  Revision 1.54  2005/03/10 01:51:17  rudahl
 *  added imageHdr.h
 *
 *  Revision 1.53  2005/03/09 01:34:14  rudahl
 *  fix missing args in new(), add CloseImage
 *
 *  Revision 1.52  2005/03/07 23:39:27  goldin
 *  Working on img_acc test functions
 *
 *  Revision 1.51  2005/03/06 17:31:04  rudahl
 *  revising create() and update_text() args
 *
 *  Revision 1.50  2005/03/06 00:17:13  rudahl
 *  moved creation of writer to createheader
 *
 *  Revision 1.49  2005/03/03 23:25:30  goldin
 *  remove img_acc.h
 *
 *  Revision 1.48  2005/03/03 21:49:54  goldin
 *  Implement remaining revise_ & update_ methods
 *
 *  Revision 1.47  2005/03/03 16:30:32  rudahl
 *  added getTrailerOffset
 *
 *  Revision 1.46  2005/03/01 23:04:21  goldin
 *  Implement new create function for new output images; fix update functions
 *
 *  Revision 1.45  2005/03/01 01:04:23  rudahl
 *  fixed bad return value
 *
 *  Revision 1.44  2005/02/28 21:15:34  goldin
 *  Add update_georef methods
 *
 *  Revision 1.43  2005/02/28 20:44:46  goldin
 *  implement update_stats
 *
 *  Revision 1.42  2005/02/23 18:21:31  rudahl
 *  new update, wrapper fns; moved from hdrstats to dhead
 *
 *  Revision 1.41  2005/02/22 20:11:33  rudahl
 *  new update, wrapper fns
 *
 *  Revision 1.40  2005/02/22 03:41:57  rudahl
 *  removed hdrInfo, header fields
 *
 *  Revision 1.39  2005/02/20 17:09:41  rudahl
 *  prelim create IMAGEHDR accessor fns
 *
 *  Revision 1.38  2005/02/16 00:50:06  goldin
 *  Changes to be able to compile under MingW
 *
 *  Revision 1.37  2005/02/16 00:17:27  rudahl
 *  typo
 *
 *  Revision 1.36  2005/02/15 21:24:32  rudahl
 *  extended error checking or writing
 *
 *  Revision 1.35  2005/02/12 03:16:13  rudahl
 *  added m_uState; cleanup
 *
 *  Revision 1.34  2005/02/10 03:51:27  rudahl
 *  cleaned up tracing and error handling
 *  cleaned up image file writing
 *
 *  Revision 1.33  2005/02/07 05:40:17  rudahl
 *  added putImageLine fns
 *
 *  Revision 1.32  2005/02/03 16:07:19  rudahl
 *  initial support for multi-resolution formats
 *
 *  Revision 1.31  2005/02/03 03:15:02  rudahl
 *  Added support for getline and write header in img class,
 *  plus initial use of standardized error numbers
 *
 *  Revision 1.30  2005/01/30 03:46:56  rudahl
 *  add some extern C access fns
 *
 *  Revision 1.29  2005/01/30 01:29:39  rudahl
 *  moved some fns from img_xx; added TEST, logging
 *
 *  Revision 1.28  2004/12/30 13:17:02  rudahl
 *  copy georef info for U/CUR
 *
 *  Revision 1.27  2004/12/28 12:13:12  rudahl
 *  fixed problem reading UTF-8 from header
 *
 *  Revision 1.26  2004/12/23 11:48:35  rudahl
 *  lint-ish fix
 *
 *  Revision 1.25  2004/12/12 05:52:57  goldin
 *  remove extra tracing
 *
 *  Revision 1.24  2004/12/12 04:53:14  goldin
 *  Add more tracing
 *
 *  Revision 1.23  2004/12/11 08:28:59  goldin
 *  Fix bug in Dump
 *
 *  Revision 1.22  2004/12/04 06:06:30  rudahl
 *  adapt for Mingw
 *
 *  Revision 1.21  2002/09/23 13:52:18  rudahl
 *  added OriginalVersion
 *
 *  Revision 1.20  2002/09/23 13:37:04  rudahl
 *  added band, comment
 *
 *  Revision 1.19  2002/09/15 21:50:40  rudahl
 *  mork around product level
 *
 *  Revision 1.18  2002/09/15 16:20:59  rudahl
 *  Significant flow changes in GetDragonImageHeader around
 *  topic of keyed files and product codes
 *
 *  Revision 1.17  2002/09/14 22:08:43  rudahl
 *  fixup SynchHisto
 *
 *  Revision 1.16  2002/09/14 19:43:35  goldin
 *  Get rid of compile warnings
 *
 *  Revision 1.15  2002/09/11 23:54:54  rudahl
 *  defensively, added code to convert any HEADER strings
 *  which might happen to have weird values into pure ASCII
 *
 *  Revision 1.14  2002/09/10 16:50:43  goldin
 *  get rid of warnings
 *
 *  Revision 1.13  2002/09/10 16:44:54  rudahl
 *  augmented dump
 *
 *  Revision 1.12  2002/09/07 21:37:04  rudahl
 *  improve dump(); fix some hdr fields
 *
 *  Revision 1.11  2002/09/05 19:00:45  rudahl
 *  fix  typo
 *
 *  Revision 1.10  2002/09/05 00:46:00  rudahl
 *  work around keyed images
 *
 *  Revision 1.9  2002/08/31 23:03:27  rudahl
 *  adding classnamelen fields; improving dump
 *
 *  Revision 1.8  2002/08/30 20:33:40  rudahl
 *  added a couple of Image fields
 *
 *  Revision 1.7  2002/08/28 16:10:46  rudahl
 *  improved dump, zero
 *
 *  Revision 1.6  2002/07/22 20:16:14  goldin
 *  initialize uHistPtrCount etc when coying histogram
 *
 *  Revision 1.5  2002/07/22 16:57:57  goldin
 *  Change init to return zero status if all ok
 *
 *  Revision 1.4  2002/07/20 00:23:12  rudahl
 *  revs to IMAGE struct; add init(pImage)
 *
 *  Revision 1.3  2002/07/19 14:40:12  rudahl
 *  removed use of RES_FILEHIST
 *
 *  Revision 1.2  2002/07/13 00:36:37  rudahl
 *  continue to impl. Image class
 *
 *  Revision 1.1  2002/07/12 00:11:47  rudahl
 *  implemented Image class
 *
 *
 ***************************************************
 *  This file contains the Image class intended for use in the DRAGON
 *  image processing program. 
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * History
 *	7/6/2002 ktr	created
 * 5.4	12/1/2004 ktr	adapt for Mingw
 *	12/28/2004 ktr	if strings in hdr not UTF-8, 
 *			then for sanity AND each char with 0x7F
 *	2004-12-30 ktr 	MapFromInput2Buffer (for CUR) now copies georef info
 *			(but still not projection info)
 * 5.5	2005-1-28 ktr	Adapt for v 5.5, which includes a new header fmt
 *			and a "virtual" header as IMAGEHDR (dhead.h)
 *	2005-2-21 ktr	got rid of HEADER_INFO_FIELDS, hdrInfo, header
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h, imageReader.h
 * 	2005-7-20 ktr	added h_OriginalFileName and IMAGEDATA_SELECTOR
 *	2006-1-19 ktr	purge deadwood
 * 5.11 2007-05-12 ktr	permit 32-bit signed data
 *	2008-06-14 ktr	added LinesBlob to trailer
 ***************************************************
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>	/* for offsetof() */
#ifdef __GCC__
#include <errno.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"

#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"
#include "imageWriter.h"
#include "i18n.h"

#include "dp.h"

Class Image::s_class_Base("Image","Class for reading and writing images");
const char * Image::s_czStateNames[] = { IMG_STATE_NAMES };
ushort Image::s_uLatest = 0;
ushort Image::s_uWorkingLines=D_MAXIMGLINES;  /* these control the */
ushort Image::s_uWorkingPixels=D_MAXIMGPIX;   /* max size of image to use */ 

		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
Image::Image(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
	logTrace("Image::ctor (en) uLatest=%d traces=%d,%d",
	     s_uLatest,iTrace,m_iTrace);
    if (iDebug || m_iDebug)
	fprintf(stderr,"Image::Image (en) # uLatest=%d\n",s_uLatest);
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_uState = IMG_UNINIT;
    m_bHdrUpdated = FALSE;	/* TRUE => need to rewrite header */
    zero(TRUE,s_uLatest++);
    image.pImageObj = this;
    if (m_iDebug)
	fprintf(stderr,"Image::ctor (ex) "
	       "iDebug is %d, m_iDebug is %d IMAGE #=%d at %p pImageObj=%p\n",
	       iDebug, m_iDebug,image.thisone,&image,image.pImageObj);
    if (m_iTrace)
	logTrace("Image::ctor (ex) "
	       "iDebug is %d, m_iDebug is %d IMAGE #=%d at %p pImageObj=%p",
	       iDebug, m_iDebug,image.thisone,&image,image.pImageObj);
    }

	/* initialize all values based on header/trailer info in
	 * specified file, which must exist. 
	 * Should be preceeded by zero(). If not (i.e. if Image has already
	 * been initialized), current values are discarded and Images is 
	 * re-initialized. However, a message is sent to logTrace.
	 * @param pczFilename	full, long path to file
	 * @param bModifiable	if TRUE, data and some header settings
	 *			can be changed.
	 * @param pSel		if non-NULL, identifies part of multi-part
	 *			image
	 * @return		>0 (m_uState) if OK else error #:
	 */
int Image::open(const char * pczFilename, BOOL bModifiable,
		const IMAGEDATA_SELECTOR * pSel)
    {
#undef FN_NAME
#define FN_NAME "Image::open"
    Logger::logTrace(FN_NAME " (en) img# %d pczFilename='%s' modifiable=%s",
		     image.thisone,pczFilename,YESNO(bModifiable));
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (en) img# %d pczFilename='%s' errno=%d"
	       " modifiable=%s\n",
	       image.thisone,pczFilename,m_iErrno,YESNO(bModifiable));
    if (m_iErrno < 0)
        {
	Logger::logTrace(FN_NAME " ERROR: redundant invocation "
		 "img#%d old='%s' new='%s'",
		 image.thisone,image.filename,pczFilename);
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " ERROR: redundant invocation "
		   "img#%d old='%s' new='%s'",
		   image.thisone,image.filename,pczFilename);
	m_iErrno = 0;
	zero(FALSE,-1);
	}
    m_bModifiable = bModifiable;
    /* If we can modify the image we should be able to reread it */
    m_bReReadable = m_bModifiable;
    readImageHeader(pczFilename,pSel);
#ifdef NOTNOW
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    /* 12/21/2005 - Kurt says that this is ok */
    if ((m_iErrno == 0) && (pImgHeader != NULL) &&
        (pImgHeader->ftype[0] == 'C'))
        {
        logTrace("img max is %d and pointer to labels structure is %x",
                     pImgHeader->imgmax, pImgHeader->pLabels);
	if ((pImgHeader->imgmax > 0) &&
            (pImgHeader->pLabels == NULL))
	   {
	   m_iErrno = DERR_IMAGE_CORRUPT;
	   /* this suggests that the trailer was never written... */
	   }
        }
#endif
    if ((m_iErrno == 0) && (bModifiable) && (m_pHdr != NULL))
	m_pWriter = m_pHdr->imageWriterFactory(image.uImageFormat);
    Logger::logTrace(FN_NAME " (ex) succeeded=%s returns %d",
		     YESNO(m_iErrno == 0),m_iErrno);
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (ex) succeeded=%s returns %d\n",
			 YESNO(m_iErrno == 0),m_iErrno);
    if (m_iErrno < 0) 
        m_uState = IMG_ERROR;
    return (m_iErrno < 0) ? m_iErrno : m_uState;
    }

	/* set up an Image for output - BASED ON AN EXISTING IMAGE
	 * This works by: 1. Create a new ImageHdr
	 *                2. Copy an existing ImageHdr
	 *		  3. Allow the selected writer subclass to 
	 *                   modify the new ImageHdr
	 * 		  4. Init 'this' from the new ImageHdr.
	 * If the image geometry need to be changed,
	 *   call revise() BEFORE calling write().
	 * If the image data differes from pSrcImage,
	 *   call update() AFTER writing the image data, 
	 *   then call rewriteHeader().
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param bReReadable	if TRUE, data can be re-read after writing
	 * @param uImgType	type of image file
	 * @param pSrcImage	Image to copy
	 * @param pczFtype      Dragon file type - "I", "C" or "L",
	 *			or NULL to keep type from copy
	 * @return		0 if OK
	 *			-48 memory problems
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-66 => pSrcImage not init as readable
	 *			-90 to -97 - invalid argument
	 */
int Image::create(const char * pczFilename, BOOL bOverwrite,
		  BOOL bReReadable, IMGTYPE_T uImgType,
		  const Image * pSrcImage,const char* pczFtype)
    {
    if (m_iTrace)
	logTrace("Image::create (en) (copy) img# %d file='%s' from img# %d "
			 "overwrite=%s reread=%s type=%d srcstate=%s",
			 image.thisone,pczFilename,pSrcImage->image.thisone,YESNO(bOverwrite),
			 YESNO(bReReadable),uImgType,
			 pSrcImage->getStateName());
    if (m_iDebug)
	fprintf(stderr,"Image::create (copy) (en) img# %d file='%s' "
			 "overwrite=%s reread=%s type=%d err=%d srcstate=%s\n",
			 image.thisone,pczFilename,YESNO(bOverwrite),
			 YESNO(bReReadable),uImgType,m_iErrno,
	       pSrcImage->getStateName());
    if (m_iErrno < 0)
        {
	logTrace("Image::create ERROR: redundant invocation "
		 "img#%d old='%s' new='%s'",
		 image.thisone,image.filename,pczFilename);
	}
    else if (pSrcImage == NULL)
	m_iErrno = DERR_FN_ARG4;
    else if (! bOverwrite && (access(pczFilename,F_OK)==0))
	m_iErrno = DERR_FILE_ALREADY;
    else if ((pSrcImage->m_uState != IMG_INITFROMFILE)
	     && (pSrcImage->m_uState != IMG_HDRWRITTEN))
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (m_iErrno == 0)  /* create the output header */
        {
	m_bReReadable = bReReadable;
	if ((m_pHdr = new ImageHdr(m_iDebug,m_iTrace)) == NULL)
	    m_iErrno = DERR_MEM_ALLOC;
	else
	    m_pHdr->copy(pSrcImage->getImageHeader(),uImgType,pczFtype);
	}
    strcpy_array(image.filename,pczFilename);
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iErrno)
        {
	logTrace("Image::create status is %d (%s)", 
		 m_iErrno,getErrorMessage());
	logTrace(dump(1,"Created output image"));
	if (m_pHdr == NULL)
	    logTrace("HDR = NULL!! -- can't dump it");
	else
	    logTrace(m_pHdr->dump(1,"Created output image"));
	}
    if (m_iDebug)
	fprintf(stderr,"Image::create (copy) (ex) status is %d (%s)\n", 
	       m_iErrno,getErrorMessage());
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_WRITABLE;
    m_pSrcImage = pSrcImage;	/* set only if created by dreate (copy) */
    if (m_iTrace)
	logTrace("Image::create (ex) (copy)");
    return m_iErrno;
    }

	/* set up an Image BASED ON AN EXISTING FOREIGN IMAGE
	 *   This is for use in a foreign imageReader subclass, which requires
	 *   an IMAGE * in the getImageLine function()
	 *   See e.g. jasperImageReader
	 * @param pImageHdrStruct   already initialized header
	 *			    MUST have the following fields initialized:
	 *			       h_OriginalFileName,size[0,1],ulPixelPitch,bits_per_pix
	 * @return		    0 if OK
	 *			    DERR_MEM_ALLOC
	 */
int Image::create(const IMAGEHDR * pImageHdrStruct)
    {
    const char * pczFilename = pImageHdrStruct->h_OriginalFileName;
    if (m_iTrace)
	logTrace("Image::create (en) (foreign) file='%s' ",
		pczFilename);
    if (m_iDebug)
	fprintf(stderr,"Image::create (foreign) (en) file='%s'\n",
		pczFilename);
    // m_pHdr is not used
//    if ((m_pHdr = new ImageHdr(m_iDebug,m_iTrace)) == NULL)
//	m_iErrno = DERR_MEM_ALLOC;
//    else
//	m_pHdr->m_hi = pHdr;
    // 
    image.ulPixPitch = pImageHdrStruct->ulPixelPitch;
    image.lines = pImageHdrStruct->size[0];
    image.pixels = pImageHdrStruct->size[1];
    image.pixbits = pImageHdrStruct->bits_per_pix;
    strcpy_array(image.filename,pczFilename);
//    m_uState = IMG_WRITABLE;
    m_uState = IMG_INITFROMFILE;
    if (m_iDebug)
	fprintf(stderr,"Image::create (foreign) (ex) status is %d (%s)\n", 
	       m_iErrno,getErrorMessage());
    if (m_iTrace)
	logTrace("Image::create (ex) (foreign)");
    return m_iErrno;
    }

	/* initialize critical values for a new file with specified name
	 * which may be deleted if it already exists.
	 * This fn is provided for creating an image which is in no way
	 * a derivitive of an existing image.
	 * Should be preceeded by zero().
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param bReReadable	if TRUE, data can be re-read after writing
	 * @param uImgType	type of image file
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
	 * @param pczFtype      Dragon file type ("I", "C" or "L")
	 * @param pczOriginalName NULL or name of source file
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
int Image::create(const char * pczFilename, BOOL bOverwrite,
		   BOOL bReReadable, IMGTYPE_T uImgType,
		   ushort uNumLines, ushort uNumPixels,
		   ushort uBitsPerPix, ushort uNumBands,
		   ushort uNumResolutions, const char* pczFtype,
		   const char * pczOriginalName)
    {
    if (m_iTrace)
	logTrace("Image::create (en) (new) img# %d pczFilename='%s' "
			 "overwrite=%s reread=%s type=%d lines=%d pix=%d\n"
			 "bits/pix=%d bands=%d res=%d dragon type=%s",
			 image.thisone,pczFilename,YESNO(bOverwrite),
			 YESNO(bReReadable),uImgType,
			 uNumLines, uNumPixels, uBitsPerPix, uNumBands,
			 uNumResolutions,pczFtype);
    if (m_iDebug)
	fprintf(stderr,"Image::create (new) (en) img# %d pczFilename='%s' "
			 "overwrite=%s reread=%s type=%d errno=%d\n",
			 image.thisone,pczFilename,YESNO(bOverwrite),
			 YESNO(bReReadable),uImgType,m_iErrno);
    if (m_iErrno != 0)
        {
	logTrace("Image::create ERROR: redundant invocation "
		 "img#%d old='%s' new='%s'",
		 image.thisone,image.filename,pczFilename);
	}
    else if (! bOverwrite && (access(pczFilename,F_OK)==0))
	m_iErrno = DERR_FILE_ALREADY;
    else if (m_iErrno == 0)  /* create the output header */
        {
	m_bReReadable = bReReadable;
	if ((m_pHdr = new ImageHdr(m_iDebug,m_iTrace)) == NULL)
	    m_iErrno = DERR_MEM_ALLOC;
	}
    if (m_iErrno == 0)
        {
	m_pHdr->init(uImgType,pczFtype,uNumLines, 
		     uNumPixels, uBitsPerPix,
		     uNumBands, uNumResolutions,
		     pczOriginalName);
	}
    strcpy_array(image.filename,pczFilename);
    image.lines = uNumLines;   /* SEG 10/9/07 - Not done elsewhere?? */
    image.pixels = uNumPixels;
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iTrace || m_iErrno)
	logTrace("Image::create (ex) (new) status is %d", m_iErrno);
    if (m_iDebug || m_iErrno)
	fprintf(stderr,"Image::create (new) (ex) status is %d\n", m_iErrno);
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_WRITABLE;
    return m_iErrno;
    }

	/** Read a Dragon image from a file.
	 *  This does the entire input process for an image with no
	 *  complications
	 *  @param pBuf		gets set to point to allocated image data
	 *			MUST BE FREED BY CALLING PROGRAM
	 *  @param pczPath	where to read file
	 *  @param pczRootName	file name will be pczRootName-pczModifier.img
	 *  @param pczModifier  if NULL, pczRootName is the whole name including .img
	 *  @param iVerbose	show progress to stdout
	 *  @return		>=0 => OK
	 */
int Image::readImage(byte ** pBuf, 
		     const char * pczPath,const char * pczRootName,
		     const char * pczModifier, int iVerbose)
    {
    char czFilename[PATH_MAX];
    if (pczModifier == NULL)
	snprintf(czFilename,sizeof(czFilename),"%s/%s",
	     pczPath,pczRootName);
    else
	snprintf(czFilename,sizeof(czFilename),"%s/%s-%s.img",
	         pczPath,pczRootName,pczModifier);
    int iStatus = open(czFilename,FALSE);
    if (iStatus < 0)
	{
	printf ("open failure of input image %s: %d=%s\n",
		czFilename,iStatus,dragonErrorMessage(iStatus));
	return iStatus;
	}
    uint nLines = getImage()->lines;
    uint nPix = getImage()->pixels;
    uint nBytes = ( getImage()->pixbits + 7 ) / 8;
//    uint uBytesPP = (image.ulPixPitch > 0) 
//	    ? image.ulPixPitch : 1 ;
    *pBuf = (byte *)calloc(nPix*nLines,nBytes);
    if (*pBuf == NULL)
	{
	printf ("memory alloc failure for image %s\n",czFilename);
	return DERR_MEM_ALLOC;
	}
    for (uint uLine = 0; uLine < nLines; uLine++)
	{
	byte * pDest = *pBuf+nPix*uLine;
	iStatus = getImageLine(pDest,uLine,nPix);
	if (iStatus != (int)nPix)
	    {
	    printf ("Error %s=%d reading line %d of input image  %s\n",
		    dragonErrorMessage(iStatus),iStatus,uLine,czFilename);
	    return iStatus;
	    }
	}
    return iStatus;
    }

	/** Output a Dragon image to a file.
	 *  This does the entire output process for an image with no
	 *  complications: 8-bit, silently-overwrite
	 *  NOTE that the imagefile is closed when this exits
	 *  @param pOutBuf	image data
	 *  @param uLines,uPix	image dimensions
	 *  @param pImg		existing Image object with important params
	 *  @param pczPath	where to write file
	 *  @param pczRootName	file name will be pczRootName-pczModifier.img
	 *  @param pczModifier  if NULL, pczRootName is the whole name including .img
	 *  @param iVerbose	show progress to stdout
	 *  @return		>=0 => OK
	 */
int Image::saveImage(const byte * pOutBuf,uint uLines,uint uPix, Image * pImg,
		     const char * pczPath,const char * pczRootName,
		     const char * pczModifier, int iVerbose)
    {
    IMGTYPE_T uOutFormat = IT_DRAGON;
    char czFilename[PATH_MAX];
    if (pczModifier == NULL)
	snprintf(czFilename,sizeof(czFilename),"%s/%s",
	     pczPath,pczRootName);
    else
	snprintf(czFilename,sizeof(czFilename),"%s/%s-%s.img",
	         pczPath,pczRootName,pczModifier);
    // this will silently overwrite an existing image
    int status = create((const char *)czFilename, TRUE, FALSE, 
			uOutFormat,pImg,NULL);
    if (iVerbose > 1)
        fprintf(stderr,"Output image created; img errno=%d=%s\n",
		status,dragonErrorMessage(status));
    if (status < 0)
        return status;
    status = writeHeader();
    if (iVerbose > 1)
        fprintf(stderr,"Writing header : success=%s status=%d hdrstatus=%d\n",
	       YESNO(status==0),getErrorNo(),
	       getImageHeader()->getErrorNo());
    if (iVerbose > 1)
	fprintf(stderr,"%s\n",
	       getImageHeader()->dump(0,
				     "Dump of output image hdr"));
    ushort j;
    for (j=0; j<uLines; j++)
        {
	const byte * pLineBuf = pOutBuf + j * uPix;
	status = putImageLineRaw(pLineBuf,j,uPix);
	if (status < 0)
	    break;
	status = rewriteHeader(0,TRUE);
	if (status < 0)
	    fprintf(stderr,"Creating output file status = %d = %s\n",status,
		   dragonErrorMessage(status));
	}
    CloseImage();
    return status;
    }

	/* revise critical values for an existing writable image.
	 * Only the params with non-default vals will be changed.
	 * This must be invoked BEFORE writing the header
	 * @param pczFilename	NULL => do not change
	 * @param bOverwrite	FALSE => file must not exist
	 * @param bReReadable	FALSE => do not change
	 * @param uImgType	IT_INVALID => do not change
	 * @param uNumLines	0 => do not change
	 * @param uNumPixels	0 => do not change
	 * @param uBitsPerPix	0 => do not change
	 * @param uNumBands	0 => do not change
	 * @param uNumResolutions 
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int Image::revise_geom(const char * pczFilename/*=NULL*/, 
		       BOOL bOverwrite, /* if FALSE, file MUST NOT EXIST */
		       BOOL bReReadable/*=FALSE*/, 
		       IMGTYPE_T uImgType/*=IT_INVALID*/,
		       ushort uNumLines/*=0*/, ushort uNumPixels/*=0*/,
		       ushort uBitsPerPix/*=0*/, ushort uNumBands/*=0*/,
		       ushort uNumResolutions/*=0*/)
    {
    if (m_iTrace)
	Logger::logTrace("Image::revise_geom (en) img# %d pczFilename='%s' "
			 "overwrite=%s reread=%s type=%d lines=%d pix=%d\n"
			 "\tbits/pix=%d bands=%d res=%d m_iErrno=%d",
			 image.thisone,pczFilename,YESNO(bOverwrite),
			 YESNO(bReReadable),uImgType,
			 uNumLines, uNumPixels, uBitsPerPix, uNumBands,
			 uNumResolutions,m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"Image::revise_geom (en) img# %d pczFilename='%s' "
	       "overwrite=%s reread=%s type=%d m_iErrno=%d\n",
	       image.thisone,pczFilename,YESNO(bOverwrite),
	       YESNO(bReReadable),uImgType,m_iErrno);
    if (m_iErrno != 0)
	return m_iErrno;
    if (m_uState != IMG_WRITABLE)
        {
	if (m_iTrace)
	    Logger::logTrace("Image::revise_geom state=%s should be %s",
		    s_czStateNames[m_uState],s_czStateNames[IMG_WRITABLE]);
	if (m_iDebug)
	    fprintf(stderr,"Image::revise_geom state=%s should be %s\n",
		    s_czStateNames[m_uState],s_czStateNames[IMG_WRITABLE]);
	return DERR_IMAGE_BADSTATE;
	}
    m_iErrno = m_pHdr->revise_geom(pczFilename,bOverwrite,bReReadable,
				   uImgType,uNumLines,uNumPixels,
				   uBitsPerPix,uNumBands,
				   uNumResolutions,0,0,0);
    if (pczFilename != NULL)
        { strcpy_array(image.filename,pczFilename); }
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (bReReadable)
	m_bReReadable = bReReadable;
    if ((m_iErrno == 0) && (! bOverwrite) && (access(image.filename,F_OK)==0))
	m_iErrno = DERR_FILE_ALREADY;
    if (m_iDebug)
	fprintf(stderr,"Image::revise_geom (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::revise_geom (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
    }

	/* change scaling information for an existing image.
	 * Only the params with non-default vals will be changed.
	 * This may be invoked after writing the header and the image data
	 * @param dScaleFactor	factor, value for BINARY or OPTIMAL scaling
	 * @param ScaleOffset	offset, value only if OPTIMAL scaling
	 * @param pczScalingType 'B', 'O', 'N'o change, or \0 for none
	 *   ( the following give calibration meaning to pixel values )
	 *   ( if dZ_scale == 0, none of these are set by this fn)
	 *   ( calibrated value = (pixel value * dz_Scale) + offset)
	 * @param dZ_scale	multiplicative factor
	 * @param dZ_offset	additive factor 
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
int Image::update_scaling(double dScaleFactor,
			  double dScaleOffset,
			  const char * pczScalingType,
			  double dZ_scale,
			  double dZ_offset,
			  const char * pcZ_unit)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_scaling (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_scaling (en) image# %d",image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_scaling(dScaleFactor,dScaleOffset,
				 pczScalingType,
				 dZ_scale,dZ_offset,pcZ_unit);
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_scaling (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_scaling (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
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
int Image::update_text(const char * pczTitle,
		       const char * pczId,
		       const char * pczComment,
		       const char * pczSource,
		       const char * pczScene,
		       const char * pczSubscene,
		       const char * pczBand,
		       const char * pczColorfileName,
		       const char * pczFtype)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_text (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_text (en) image# %d",image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_text(pczTitle,pczId,pczComment,pczSource,
			      pczScene,pczSubscene,pczBand,pczColorfileName,
			      pczFtype);
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_text (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_text (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
    }

	/* change stats and histogram information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * @param pImgStats	stats for image
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
int Image::update_stats(const IMGSTATS * pImgStats)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_stats (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_status (en) image# %d",image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_stats(pImgStats);
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_stats (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_stats (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
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
int Image::update_georef(int img_x, int img_y, 
			 const MapCoord * ref_x, const MapCoord * ref_y,
			 double xcell_size, double ycell_size,
			 const char* pczProjection, const char* pczUnitname,
			 const char * pczDateTime,const char * pczUTMZone,
			 int iRegistered)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_georef (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_georef (en) state=%s image# %d",
		 getStateName(),image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_georef(img_x, img_y, ref_x, ref_y,
				xcell_size, ycell_size, pczProjection,
				pczUnitname,pczDateTime,pczUTMZone,
				iRegistered);
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_georef (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_georef (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
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
int Image::update_labels(int iNumLabels,
			  size_t uArrayCount,
			  const LABEL_INFO * pLabels)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_labels (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_labels (en) image# %d",image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_labels(iNumLabels,uArrayCount,pLabels);
    if (m_iErrno == 0)		/* init 'this' from the header */
	m_iErrno = _MapFromImageHeader();
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_labels (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_labels (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
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
int Image::update_metainfo(const char * pczMetafile,
			  const char * pczGuid)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_metainfo (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_metainfo (en) image# %d",image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_metainfo(pczMetafile,pczGuid);
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_metainfo (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_metainfo (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
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
int Image::update_extent(double minX, double minY,
			    double maxX, double maxY)
    {
    if (m_iDebug)
	fprintf(stderr,"Image::update_extent (en) state=%s\n",getStateName());
    if (m_iTrace)
	logTrace("Image::update_metainfo (en) image# %d",image.thisone);
    m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	? DERR_IMAGE_BADSTATE
	: m_pHdr->update_extent(minX,minY,maxX,maxY);
    if (m_iErrno == 0)
        {
        m_uState = IMG_CHANGED;
	m_bHdrUpdated = TRUE;
	}
    if (m_iDebug)
	fprintf(stderr,"Image::update_extent (ex) state=%s return=%d\n",
	       getStateName(),m_iErrno);
    if (m_iTrace)
	logTrace("Image::update_extent (ex) state=%s return=%d",
		 getStateName(),m_iErrno);
    return m_iErrno;
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
int Image::update_original(uint uOriginalBandCount,
			   uint uOriginalBandNumber,
			   const char * pczOriginalFileName)
    {
#undef FN_NAME
#define FN_NAME "Image::update_original"
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (en) count=%d number=%d name=%s currently errno=%d\n", 
		uOriginalBandCount,uOriginalBandNumber,
	        NN(pczOriginalFileName),m_iErrno);
    if (m_iTrace)
	logTrace(FN_NAME " (en)  count=%d number=%d name=%s currently errno=%d", 
		 uOriginalBandCount,uOriginalBandNumber,
	         NN(pczOriginalFileName),m_iErrno);
    if (m_iErrno == 0)
	{
	m_iErrno = ((m_uState != IMG_WRITABLE) 
		     && (m_uState != IMG_HDRWRITTEN)
		     && (m_uState != IMG_CHANGED)
		     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
	    ? DERR_IMAGE_BADSTATE
	    : m_pHdr->update_original(uOriginalBandCount,uOriginalBandNumber,
				  pczOriginalFileName);
//    if (m_iErrno == 0)		/* init 'this' from the header */
//	m_iErrno = _MapFromImageHeader(); // fields aren't in IMAGE, so no need to do this
	if (m_iErrno == 0)
	    {
	    m_uState = IMG_CHANGED;
	    m_bHdrUpdated = TRUE;
	    }
	}
    if (m_iTrace)
	logTrace(FN_NAME " (ex)  returns %d", m_iErrno);
    return m_iErrno;
    }

#if DRAGON_VER >= 6
int Image::copy_blob()
    {
    logTrace("Image::copy_blob (en) (copy) img# %d from img# %d (%s) rereadable? %s",
	     image.thisone,
	     (m_pSrcImage==NULL) ? -1 : (int)m_pSrcImage->image.thisone,
	     (m_pSrcImage==NULL) ? "" : m_pSrcImage->image.filename,
	     YESNO(m_bReReadable));
    if ((m_uState != IMG_WRITABLE) 
	    && (m_uState != IMG_HDRWRITTEN)
	    && (m_uState != IMG_CHANGED)
	    && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable))
        m_iErrno = DERR_IMAGE_BADSTATE;
    if ((m_pSrcImage != NULL)
	    && (m_pSrcImage->getLinesBlobLen() > 0))
        {
	m_iErrno = setLinesBlob(m_pSrcImage->getLinesBlob(),
				m_pSrcImage->getLinesBlobLen());
	logTrace("Image::copy_blob copied LinesBlob size=%d ",
		     m_pSrcImage->getLinesBlobLen());
	}
    return m_iErrno;
    }
#endif

    /* set to valid but not meaningful values (mostly 0 or NULL)
     * @param bFirstTime	if TRUE, assume ptrs are junk
     *				if FALSE, ignore iIndex
     * @param iIndex		if >= 0, set 'thisone'
     * @return			0 if OK
     *				else
     *					-54 if file close error
     */
int Image::zero(BOOL bFirstTime,int iIndex)
    {
    int iRetval = 0;
    if (m_iTrace)
	logTrace("Image::zero (en) index=%d firsttime=%s; "
			 "prev: latest=%d this=%d",
			 iIndex,YESNO(bFirstTime),s_uLatest,image.thisone);
    if (m_iDebug)
	fprintf(stderr,"Image::zero (en) index=%d firsttime=%s; "
			 "prev: latest=%d this=%d\n",
			 iIndex,YESNO(bFirstTime),s_uLatest,image.thisone);
    /* initialize the 'image' structure to known values */
    if (bFirstTime && (iIndex >= 0))
        {
	memset(&image,0,sizeof(IMAGE));
	m_pSrcImage = NULL;		/* set only if created by create() (copy) */
        image.thisone = iIndex;
	}
    else
        {
	size_t saveIndex = image.thisone;
	iRetval = closeImageFile();
logTrace("Image::zero 1 iretval=%d",iRetval);
	if (m_pHdr != NULL)
	    delete m_pHdr;
	// closeImageFile() closed them - now delete them
	if (m_pReader != NULL)
	    delete m_pReader;
	if (m_pWriter != NULL)
	    delete m_pWriter;
	if (image.histptr != NULL)
	    free(image.histptr);
	if (image.puKeyTable != NULL)
	    free(image.puKeyTable);
	if (m_puPalette != NULL)
	    free(m_puPalette);
logTrace("Image::zero 2 ");
	memset(&image,0,sizeof(IMAGE));
        image.thisone = saveIndex;
	image.pImageObj = this;
        }
    m_pHdr = NULL;
    m_pReader = NULL;
    m_pWriter = NULL;
    image.residentflag = RES_NOTINIT;   /* mark it as unused */
    image.uImageFormat = IT_UNINIT;
    image.uScaleFactor = 1;
    image.uDataFactor = 1;
    image.uLabelEncoding = 3; /* assume UTF-8. Obsolete  */
    image.pixbits = 8;
    image.ProcessRect.Xmax = getWorkingPixels() - 1; /* processing region */
    image.ProcessRect.Ymax = getWorkingLines() - 1;
    image.pixels = getWorkingPixels();
    image.lines = getWorkingLines();
#if DRAGON_VER >= 6
    image.m_dImgsd = 0.0;
    image.m_dImgvar = 0.0;
#else
    image.imgsd = 0.0;
    image.imgvar = 0.0;
#endif
    // ~~ image.pStretch = ??; 
    /* initialize ALL other fields to known values */
    m_uHistPtrCount = 0;	  /* probably 65 or 257 */
    m_uHistPtrBinsize = 0;  /* 1 or 4 or, for 16-bit data, even bigger */
    m_puPalette = NULL;
    m_uPaletteLen = 0;
    m_iStatus = 0;
    m_uState = IMG_ZEROED;
    m_iErrno = 0;

    if (m_iDebug)
        fprintf(stderr,"Image::zero (ex) thisone=%d\n",image.thisone);
    if (m_iTrace)
        logTrace("Image::zero (ex) returns %d thisone=%d ",
		 iRetval,image.thisone);
    return iRetval;
    }

	/*	Close any files and zero image ,
	 *
	 *	Returns 0 if OK 
	 *      else 
	 *		-54 if error
	 */
int Image::CloseImage()
    {
    const char * czMethod = "Image::CloseImage";
    if (m_iTrace)
	logTrace("%s (en) ndx=%d name='%s' \n\tm_iErrno=%d state=%s",
		 czMethod,image.thisone,image.filename,
		 m_iErrno,getStateName());
    if (m_iDebug)
	fprintf(stderr,"%s (en) ndx=%d name='%s'\\nt state=%s\n",
		 czMethod,image.thisone,image.filename,getStateName());
    if (m_iErrno > 0)
        m_iErrno = 0;
    if (m_iErrno == 0)
//	fprintf(stderr,"Image::CloseImage (en) return %d ndx=%d \n\tstate=%s\n",
//	       m_iErrno,image.thisone,getStateName());
//    else
	m_iErrno = zero(FALSE,-1);
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_CLOSED;
    if (m_iTrace)
	logTrace("%s (ex) return %d ndx=%d state=%s",
		 czMethod,m_iErrno,image.thisone,getStateName());
    return m_iErrno;
    }

	/*	Close reader and writer files if open
	 *
	 *	Returns 0 if OK 
	 *      else 
	 *		-54 if error
	 */
int Image::closeImageFile()
    {
    int iRetval = 0, iWriterStat = 0;
    if (m_iDebug)
	logTrace("Image::closeImageFile (en) image %d pReader=%p pWriter=%p",
	         image.thisone,m_pReader,m_pWriter);
    if (m_pReader != NULL)
        iRetval = m_pReader->close(); // closed but not deleted
    if (iRetval)
	logTrace("Image::closeImageFile closed reader returns %d",iRetval);
    if (m_pWriter != NULL)
	iWriterStat = m_pWriter->close();
    if (iWriterStat)
	logTrace("Image::closeImageFile closed writer returns %d",iWriterStat);
    if (m_iDebug)
	logTrace("Image::closeImageFile (ex) ");
    return (iWriterStat) ? iWriterStat : iRetval;
    }

/* Get string describing state - for debugging */

const char * Image::getStateName() const
	    { return s_czStateNames[m_uState]; } ;

char * Image::getStateName(unsigned int uState)
    { return (char*) s_czStateNames[uState]; } ;

#if DRAGON_VER >= 6
int Image::setLinesBlob(const byte * pBlob,size_t uBlobSize) const
    { 
    int iRetval = (m_pWriter != NULL) 
        ? m_pWriter->setLinesBlob(pBlob,uBlobSize) : DERR_IMAGE_NOWRITE; 
    if (m_bReReadable && (m_pReader != NULL))
        m_pReader->saveLinesBlob(pBlob,uBlobSize);
    logTrace("Image::setLinesBlob writer=%p rereadable? %s reader=%p len=%d returns %d",
	     m_pWriter,YESNO(m_bReReadable),m_pReader,uBlobSize,iRetval);
    return iRetval;
    } 

	    /* if non-NULL, ptr to blob of vector data */
byte * Image::getLinesBlob() const { return (m_pReader != NULL) ? m_pReader->getLinesBlob() : NULL; } ;
   	    /* number of BYTES in LinesBlob */
size_t Image::getLinesBlobLen() const 
    { 
    size_t sz = 0;
    if (m_pReader != NULL) 
        sz = m_pReader->getLinesBlobLen();
    logTrace("Image::getLinesBlobLen reader=%p len=%d",m_pReader,sz);
    return sz; 
    }
#endif

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
const char * Image::dump(int detail, const char * pczTitle) const
    {
    // size_t i = 0;
    // size_t j = 0;
    char tbuf[128];
    sprintf(s_outbuf,"DUMP=== img# %d: %s filename='%s':\n",
	    image.thisone,NN(pczTitle),image.filename);
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    IMAGE pix=%d ln=%d bpp=%d pxPitch=%ld lnPitch=%ld FileOff=%ld\n",
	    image.pixels,image.lines,image.pixbits,
	    image.ulPixPitch,image.ulLinePitch,
	    image.ulFileOffset);
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    ProcessRect=%d,%d-%d,%d resflag=x%X modflag=x%X\n",
	    image.ProcessRect.Xmin,image.ProcessRect.Ymin,
	    image.ProcessRect.Xmax,image.ProcessRect.Ymax,
	    image.residentflag,image.modflag);
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    uScale=%d uOff=%d uFact=%d PrefScale=%d (1=simple 2=opt)\n",
	    image.uScaleFactor,image.uDataOffset,image.uDataFactor,
	    image.uPreferredScaling);
#if DRAGON_VER >= 6
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    Stats: sd=%7.2lf, var=%7.2lf, mean=%d, max=%d, min=%d\n",
	    image.m_dImgsd,image.m_dImgvar,image.m_iImgmean,
	    image.m_iImgmax,image.m_iImgmin);
#else
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    Stats: sd=%7.2lf, var=%7.2lf, mean=%d, max=%d, min=%d\n",
	    image.imgsd,image.imgvar,image.imgmean,
	    image.imgmax,image.imgmin);
#endif
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    histptr: %p pStretch: %p\n",
	    image.histptr,image.pStretch);
    sprintf(s_outbuf+strlen(s_outbuf),
	    "    NumLabels=%d MaxLabelLen=%d Encoding=%s\n",
	    image.uNumLabels,image.uMaxLabelLen,
	    (image.uLabelEncoding==3) ? "UTF-8" 
	    : (image.uLabelEncoding==2) ? "Unicode UCS-2" : "ASCII");
	        /* georeferencing information */
    sprintf(tbuf,"    status=%d=x%X bRereadable is %s", 
            m_iStatus,m_iStatus,m_bReReadable ? "TRUE" : "FALSE");
    strcat_array(s_outbuf,tbuf);
    if (image.puKeyTable != NULL)
        {
	sprintf(tbuf,"uKeyTableLen = %d\n", image.uKeyTableLen);
	strcat_array(s_outbuf,tbuf);
/*
	sprintf(tbuf,"  Table values: \n");
	strcat_array(s_outbuf,tbuf);
	for (i = 0; i < image.uKeyTableLen; i+= 8)
	    {
	    sprintf(tbuf,"      %-3X: ",i);
	    for (j = 0; (j < 8) && ( i+j < image.uKeyTableLen); j++)
	        {
		sprintf(tbuf+strlen(tbuf),"%03x ",
			image.puKeyTable[i+j]);
		}
	    strcat_array(tbuf,"\n");
	    strcat_array(s_outbuf,tbuf);
	    }
*/
	}
    else 
        { strcat_array(s_outbuf,"  KeyTable pointer is null\n"); }
    if (m_iDebug)
        {
	sprintf(tbuf,"Image::dump sizeof(IHEAD)=%d sizeof(IMAGE)=%d @%p \n",
	     sizeof(IHEAD),sizeof(IMAGE),&image);
	strcat_array(s_outbuf,tbuf);
	}
    sprintf(tbuf,"    m_pHdr=%p m_pReader=%p m_pWriter=%p key=x%X\n",
	    m_pHdr,m_pReader,m_pWriter,
	    (m_pHdr == NULL) ? 0xFFFF : m_pHdr->getImageHdr()->uKey);
    strcat_array(s_outbuf,tbuf);
    if (m_pReader != NULL)
        { 
	strcat_array(s_outbuf,"    "); 
	strcat_array(s_outbuf,m_pReader->dump(detail,pczTitle)); 
	strcat_array(s_outbuf,"\n"); 
        }
    if (m_pWriter != NULL)
        { 
	strcat_array(s_outbuf,"    "); 
	strcat_array(s_outbuf,m_pWriter->dump(detail,pczTitle)); 
	strcat_array(s_outbuf,"\n"); 
        }
    sprintf(tbuf,"   (dumplength=%d)\n\n",strlen(s_outbuf));
    strcat_array(s_outbuf,tbuf);
    return s_outbuf;
    }

	/*	read image header and set 'image' accordingly.
	 *	   fill in 'image->lines', 'pixels', 'pixbits',
	 *		and all other fields
	 *	EXCEPT, for non-DRAGON images, some fields set to defaults.
	 *	On exit, file is closed
	 *	m_iStatus set to appropriate bits if OK,
	 *	  or to m_iErrno - 10 if error
	 *	Return TRUE if OK and set m_iErrno to 0.
	 *	If fn returns FALSE, m_iErrno is < 0 if error.
	 *	Error values are:
	 *		-50 => file not found or not readable
	 *		-60 => header completely uninitialized 
	 *		-64 => there's alread an open imageFileReader,
	 *			so just leave values alone
	 *		-65 => no name supplied
	 *		-74 => file not found, or error reading hdr
	 *		-75 => file contents preclude valid interpretation
	 */
//protected 
BOOL Image::readImageHeader(const char * pczFileName,
			    const IMAGEDATA_SELECTOR * pSel)
    {
#undef FN_NAME
#define FN_NAME "Image::readImageHeader"
    int sys_errno = 0;
    if (m_iTrace)
	logTrace("Image::readImageHeader (en) img# %d name='%s'",
			 image.thisone,pczFileName);
    if (m_iDebug)
	fprintf(stderr,"Image::readImageHeader (en) img# %d name='%s' errno=%d\n",
			 image.thisone,pczFileName,m_iErrno);
    if (m_pHdr != NULL)
	m_iErrno = DERR_IMAGE_REINIT;
    else if (pczFileName == NULL)
	m_iErrno = DERR_IMAGE_NONAME;
    else if (access(pczFileName,F_OK) != 0)
	{
	m_iErrno = DERR_FILE_ACCESS;
	sys_errno = errno;
	}
    else
	{
	m_pHdr = new ImageHdr(m_iDebug,m_iTrace);
	m_pReader = m_pHdr->read(pczFileName,pSel,this);
	if (m_pReader == NULL)
	    m_iErrno = m_pHdr->getErrorNo(); 
        }
    if (m_iDebug && (m_iErrno != 0))
	fprintf(stderr,"Image::readImageHeader errno=%d='%s' sys_errno=%d\n",
	    m_iErrno,getErrorMessage(),sys_errno);
    if (m_iTrace && (m_iErrno != 0))
	logTrace("Image::readImageHeader errno=%d='%s' sys_errno=%d",
	    m_iErrno,getErrorMessage(),sys_errno);
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_INITFROMFILE;
    if (m_iErrno == 0)
	{
	const IMAGEHDR * pImgHeader = getIMAGEHDR();
	ulong ulDataOffset = pImgHeader->ulDataOffset;
	ulong ulSz = file_size(pczFileName);
	if (m_iTrace)
	    logTrace("Image::readImageHeader name='%s' initialized? %s type %s ?= %s",
		     pczFileName,YESNO(pImgHeader->bImageHdrInitialized),
		     ImageHdr::ImageTypeName(m_pHdr->getImageType()),
		     ImageHdr::ImageTypeName(m_pReader->getImageType()));
 	if (! pImgHeader->bImageHdrInitialized)
	    m_iErrno = DERR_IMAGE_UNINIT;
	else if (((pImgHeader->ulDataSize + ulDataOffset) > ulSz)
		 && (m_pReader->getImageType() != IT_TIFF) 	// might be compressed
		 && (m_pReader->getImageType() != IT_JPEG)	// probably not used
		 && (m_pReader->getImageType() != IT_JPEG2000)	// probably not used
		 && (m_pReader->getImageType() != IT_EXTERN))   // from externImageReader
	    {
	    m_iErrno = DERR_HDR_MISMATCH;
	    logTrace(FN_NAME " error HDR_MISMATCH %d + %d > %d (%s type %s)",
		     pImgHeader->ulDataSize,ulDataOffset,ulSz,pczFileName,
		     m_pHdr->ImageTypeName());
	    m_pHdr->dump(1,"Bad Header?");
	    }
	else
	    {
	    strcpy_array(image.filename,pczFileName);
	    m_iErrno = _MapFromImageHeader();
	    if (image.ulLinePitch * (ulong)image.lines + ulDataOffset <= ulSz)
		m_iStatus |= 0x800;
	    }

	if (m_iDebug && (m_iErrno != 0))
	    fprintf(stderr,"Image::readImageHeader 2 errno=%d='%s'\n",
		   m_iErrno,getErrorMessage());
	}
    if (m_iTrace || m_iErrno)
	logTrace("Image::readImageHeader (ex) "
		 "succeeded=%s err=%d %s ReadStat=x%X for '%s'",
		 YESNO(m_iErrno==0),m_iErrno,getErrorMessage(),
		 m_iStatus,pczFileName);
    if (m_iDebug)
	fprintf(stderr,"Image::readImageHeader (ex) "
		     "succeeded=%s err=%d %s ReadStat=x%X for '%s'\n",
		     YESNO(m_iErrno==0),m_iErrno,getErrorMessage(),
		     m_iStatus,pczFileName);
    return (m_iErrno == 0);
    }

	/* initialize the Image::image from the already initialized 
	 * ImageHdr.
	 * @param uImgFormat	will be stored in Image::image
	 * @return		0 if OK
	 *			errors:
	 *			  -72 hdr not init
         *	                  -82 etc: errors from validate_key
	 */
int Image::_MapFromImageHeader()
    {
//    if ((m_iDebug>1) || ((m_iDebug > 0) && (m_iErrno != 0)))
    int iRetval = 0;
    if (m_iDebug)
	fprintf(stderr,
		"    Image::_MapFromImageHeader (en) state=%s\n\tthisone=%d isOutput=%s m_iErrno=%d\n",
		getStateName(),image.thisone,YESNO(isOutput()),m_iErrno);
    if (m_iTrace > 0) //  && (m_iErrno != 0))
	logTrace("Image::_MapFromImageHeader (en) state=%s m_iErrno=%d",
		 getStateName(),m_iErrno);
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    if (! pImgHeader->bImageHdrInitialized)
        {
	iRetval = DERR_HDR_UNINIT;
	return iRetval;
        }
    image.lines = pImgHeader->size[0];
    image.pixels = pImgHeader->size[1];
    image.ulFileOffset = pImgHeader->ulDataOffset;
    image.pixbits = pImgHeader->bits_per_pix;
    image.ulPixPitch = pImgHeader->ulPixelPitch;
    image.ulLinePitch = pImgHeader->ulLinePitch;
    uint uNumBands = pImgHeader->uBands;
    image.uImageFormat = (m_pReader != NULL) ? m_pReader->getImageType() : m_pHdr->getImageType();
    if (m_iTrace > 0) //  && (m_iErrno != 0))
	logTrace("Image::_MapFromImageHeader linepitch=%d nbands=%d filetype=%s ?= %s",
		image.ulLinePitch,uNumBands,m_pHdr->ImageTypeName(),
		(m_pReader != NULL) ? m_pHdr->ImageTypeName(m_pReader->getImageType()): "");
    if (m_uState < IMG_INITFROMFILE) /* rest of the fields not yet set up */
        {
	if (m_iDebug)
	    fprintf(stderr,"    Image::_MapFromImageHeader (ex early) errno=%d\n",
		   iRetval);
	if (m_iTrace)
	    logTrace("    Image::_MapFromImageHeader (ex early) errno=%d",
		     iRetval);
	return iRetval;
	}
    if ((image.uImageFormat == IT_DRAGON)
	|| (image.uImageFormat == IT_DRAGON_OLD))
	{
#ifndef P_RT // we're just testing this version
	if(! isOutput())
	     // can't check uKey if we're trying to create a file
	    iRetval = validate_key(pImgHeader->uKey,&image);
#endif //#ifndef USE_OPEN_CL
	if (m_iDebug)
	    fprintf(stderr,
		"    Image::_MapFromImageHeader validate_key returns errno=%d\n",
		iRetval);
	if (iRetval == 0) 
	    {
	    size_t uMaxLabLen = 0;
	    image.uNumLabels = (pImgHeader->bImageHdrClassifyInit)
		? pImgHeader->uNumLabels : 0;
//    fprintf(stderr,"step1a\n");
	    for(size_t j=0; j<image.uNumLabels; j++)
	        {
		LABEL_INFO * pLabel = & pImgHeader->pLabels[j];
		if (pLabel->pczText != NULL)
		   {
		   size_t len = mbslen(pLabel->pczText,FALSE,NULL);
		   if (uMaxLabLen < len )
		        uMaxLabLen = len;
		   }
		}
	    image.uMaxLabelLen = uMaxLabLen;
	    }
	SynchImage2DragonHdr(pImgHeader);
	SynchImageHistogram(pImgHeader);

	// ~~ actually it can't be OUTPUTIMAGE, can it?
	if ((image.thisone != MAINIMG) && (image.thisone != OUTPUTIMAGE))
	    {	// rect upper bound is zero-based
	    image.ProcessRect.Xmin = 0;
	    image.ProcessRect.Ymin = 0;
	    image.ProcessRect.Xmax = image.pixels-1;
	    image.ProcessRect.Ymax = image.lines-1;
	    }
	}  /* end of DRAGON-specific initializations */
    if (iRetval == 0)
        {
	m_iStatus = 0x300 | pImgHeader->ftype[0] & 0xFF;
	if (image.uImageFormat == IT_DRAGON)
	    m_iStatus |= 0x400;
	if (image.pixbits > 8)
	    m_iStatus |= 0x1000;
	if ((image.lines > s_uWorkingLines) 
	        || (image.pixels > s_uWorkingPixels))
	    m_iStatus |= 0x2000;
	if ((image.lines > D_MAXVIDHIGH) 
	        || (image.pixels > D_MAXVIDWIDE))
	    m_iStatus |= 0x4000;
	}
    if ((m_iDebug>1) || ((m_iDebug > 0) && (m_uState != 0)))
	fprintf(stderr,"    Image::_MapFromImageHeader (ex) "
	       "state=%s m_iErrno=%d status=x%X iRetval=%d\n",
	    getStateName(),m_iErrno,m_iStatus,iRetval);
    if ((m_iTrace>1) || ((m_iTrace > 0) && (m_uState != 0)))
	logTrace("Image::_MapFromImageHeader (ex) "
		 "state=%s m_iErrno=%d status=x%X retval=%d",
	    getStateName(),m_iErrno,m_iStatus,iRetval);
    return iRetval;
    }

	/*	Retrieve a line of raw data from the appropriate
	 *	location into buffer. 
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 * 	@param pDataSel	NULL or selects data to read (not used)
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *				-60 => image not yet initialized
	 *				-66 => image state conflict
	 *				-68 => image not readable
	 *				-51 => file open error
	 *				-56 => past EOF
	 *				-63 => element too big for buffer)
	 *			        -91  line number bigger than image
	 *			             or errors from fread, fseek
	 */
int Image::getImageLineRaw(byte * pBuf, const ushort uLineNo,
			   const size_t uBufSize,
			   IMAGEDATA_SELECTOR * pDataSel)
    {
    ushort uDataLineNo = 0;
    int iRetval = 0;
    if (m_pHdr == NULL)
	m_iErrno = DERR_IMAGE_UNINIT;
    else if (m_pReader == NULL)
	m_iErrno = DERR_IMAGE_NOREAD;
    else if ((m_uState != IMG_INITFROMFILE) && !m_bReReadable)
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (Q_SUPPRESS_LOCKED) /* dp.h */
	m_iErrno = DERR_OP_FORBIDDEN;
    else if ((uLineNo > image.ProcessRect.Ymax) ||
             (uLineNo < image.ProcessRect.Ymin))
	m_iErrno = 0;
    else 
	{
	uDataLineNo = (image.puKeyTable == NULL) 
	    ? uLineNo : image.puKeyTable[uLineNo];
	iRetval = m_pReader->getImageLineRaw(pBuf,uDataLineNo,
					      uBufSize,this);
	if (iRetval < 0)
	    m_iErrno = iRetval;
	}
    if (m_iTrace && (m_iErrno < 0))
	logTrace("Image::getImageLineRaw error on line %d (=%d)"
		 "img# %d name='%s' state=%s rereadable=%s workingLines=%d errno=%d",
		 uLineNo,uDataLineNo,image.thisone,image.filename,
	    getStateName(), YESNO(m_bReReadable),getWorkingLines(),m_iErrno);
    return (m_iErrno < 0) ? m_iErrno : iRetval;
    }

	/*	Retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The base class calcs are OK for file formats where
	 *	lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *				-60 => image not yet initialized
	 *				-66 => image state conflict
	 *				-68 => image not readable
	 *				-51 => file open error
	 *				-56 => past EOF
	 *				-92 => element too big for buffer)
	 */
int Image::getImageLine(byte * pBuf, const ushort uLineNo,
			const size_t uBufSize,
			IMAGEDATA_SELECTOR * pDataSel)
    {
//    if (m_iDebug)
//	fprintf(stderr,"Image::getImageLine (en) "
//	       "img# %d line %d name='%s' errno=%d\n\tstate=%s\n",
//			 image.thisone,uLineNo,
//	       image.filename,m_iErrno,getStateName());
#undef FN_NAME
#define FN_NAME "img::getImageLine"
    int iRetval = 0;
    if ((m_iTrace > 1) || ((m_iTrace > 0) && (uLineNo == 0)))
	logTrace(FN_NAME " (en) image %d lineno %d",image.thisone,uLineNo);
    ushort uDataLineNo = 0;
    if (m_pHdr == NULL)
	m_iErrno = DERR_IMAGE_UNINIT;
    else if (m_pReader == NULL)
	m_iErrno = DERR_IMAGE_NOREAD;
    else if ((m_uState != IMG_INITFROMFILE) && !m_bReReadable)
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (Q_SUPPRESS_LOCKED) /* dp.h */
	m_iErrno = DERR_OP_FORBIDDEN;
    else if ((uLineNo > image.ProcessRect.Ymax) ||
             (uLineNo < image.ProcessRect.Ymin))
	    m_iErrno = 0;
    else
	{
	uDataLineNo = (image.puKeyTable == NULL) 
	    ? uLineNo : image.puKeyTable[uLineNo];
	iRetval = m_pReader->getImageLine(pBuf,uDataLineNo,uBufSize,
					   this, pDataSel);
	if (iRetval < 0)
	    m_iErrno = iRetval;
	}
    if (m_iTrace)
	{
	if (m_iErrno < 0)
	    {
	    logTrace("Image::getImageLine error %s (%d) on line %d=>%d "
		     "img# %d name='%s' state=%s rereadable=%s workingLines=%d",
		     dragonErrorMessage(m_iErrno),m_iErrno,uLineNo,uDataLineNo,image.thisone,
		     image.filename,getStateName(),
		     YESNO(m_bReReadable),getWorkingLines());
	    logTrace(m_pHdr->dump(1,"Image::getImageLine error"));
	    }
	else if (m_iErrno == 0)
	    {
	    logTrace("Image::getImageLine line %d=>%d outside of processing lines %d to %d "
		     "img# %d name='%s' state=%s rereadable=%s workingLines=%d",
		     uLineNo,uDataLineNo,
		     image.ProcessRect.Ymin,image.ProcessRect.Ymax,
		     image.thisone,
		     image.filename,getStateName(),
		     YESNO(m_bReReadable),getWorkingLines());
	    }
	}
    if ((m_iTrace > 1) || ((m_iTrace > 0) && (uLineNo == 0)))
	logTrace(FN_NAME " (ex) returns %d",m_iErrno);
    return (m_iErrno < 0) ? m_iErrno : iRetval;
    }

	// how big a buffer do we need for GetImageLine?
	// (This actually returns size for a full line of read data,
	// regardless of multiband and scaling considerations.)
size_t Image::getLineBufferSize() 
    { 
    return (m_pReader!=NULL) ? m_pReader->getLineBufferSize() : 0;
    }

	/*	write image header and close output file
	 *	This fn creates the m_pwriter
	 * 	if bReReadable, creates the reader
	 *	On exit, file is closed
	 *	Return 0 if OK
	 *	Error values are:
	 *		-60 => header completely uninitialized 
	 *		-64 => there's already an open writer,
	 *			so just leave values alone
	 *		-65 => no name supplied
	 *		-66 => image state conflict
	 *		-68 => need reader but unable to create one
	 *		-69 => no header writer found
	 */
int Image::writeHeader()
    {
    int iStat = 0;
    const char * czMethod = "Image::writeHeader";
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    if (m_iTrace)
	logTrace("%s (en) img# %d name='%s' state=%s "
			 "hdr initialized: %s hdr descr: %s errno=%d",
			 czMethod,image.thisone,image.filename,getStateName(),
			 YESNO(pImgHeader->bImageHdrInitialized),
			 YESNO(pImgHeader->bImageHdrDescriptionInit),m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"%s (en) img# %d name='%s' errno=%d\n\tstate=%s "
		"hdr initialized: %s hdr descr: %s\n",
		czMethod,image.thisone,image.filename,m_iErrno,getStateName(),
		YESNO(pImgHeader->bImageHdrInitialized),
		YESNO(pImgHeader->bImageHdrDescriptionInit));
    if ( ! pImgHeader->bImageHdrInitialized)
	m_iErrno = DERR_IMAGE_UNINIT;
    else if (strlen(image.filename) == 0)
	m_iErrno = DERR_IMAGE_NONAME;
    else if ((m_uState != IMG_WRITABLE) && (m_uState != IMG_CHANGED))   
        // thus cannot use for readable image
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (m_pWriter != NULL)
	m_iErrno = DERR_IMAGE_REINIT;
    else if ((m_pWriter = m_pHdr->imageWriterFactory(m_pHdr->getImageType())) == NULL)
	m_iErrno = DERR_UNSUP_FORMAT;
    else
        {
	long lOffset; /* init tells us where image data starts */
	if (m_iDebug)
   	    {
	    fprintf(stderr,"    %s about to init ImageWriter:"
		    "m_pWriter is %p, and hdr at %p\n", 
		    czMethod,m_pWriter, m_pHdr);
	    }
	m_pWriter->init(m_pHdr,&lOffset);
	if (m_iDebug)
	    fprintf(stderr,"Image::writeHeader setting data offset to %ld\n", lOffset);
	m_pHdr->setDataOffset(lOffset);
	//	if (m_iDebug)
	//   fprintf(stderr,"Image::writeHeader successfully initialized image writer\n");
	}
    if ((m_iErrno == 0)
    	    && (! m_pWriter->writeHeader(image.filename,pImgHeader,&iStat)))
	m_iErrno = iStat;
    if (m_iDebug)
	fprintf(stderr,"    %s return from write->writeHeader error=%d\n",
		czMethod,m_iErrno);
    if (m_iErrno == 0)	/* can't know hdr, data size until after hdr written */
        {
	if (m_iDebug)
	    fprintf(stderr,"    %s about to getTrailerOffset from %p\n",
		   czMethod,m_pWriter);
	ulong ulOff = m_pWriter->getTrailerOffset(); 
	if (m_iDebug)
	    fprintf(stderr,"    %s about to setTrailerOffset to %ld\n",
		   czMethod,ulOff);
	if (m_iTrace>1)
	    logTrace("    %s about to setTrailerOffset to %ld",
		   czMethod,ulOff);
	m_pHdr->setTrailerOffset(ulOff); 
	}
	/* can't get reader until header has been written */
    if (m_iDebug)
	fprintf(stderr,"    %s maybe getting reader: %s errno=%d\n",
	       czMethod,YESNO(m_bReReadable),m_iErrno);
    if (m_iTrace>1)
	logTrace("    %s maybe getting reader: %s errno=%d",
	       czMethod,YESNO(m_bReReadable),m_iErrno);
    if (m_bReReadable && (m_iErrno == 0))
        {
        if (m_iDebug)
	    fprintf(stderr,"    %s about to create reader "
		   "for re-readable image %s\n",
		   czMethod,image.filename);
        if (m_iTrace)
	    logTrace("    %s about to create reader "
		     "for re-readable image %s",
		   czMethod,image.filename);
	m_pReader = m_pHdr->imageReaderFactory(image.filename);
	if (m_pReader == NULL)
	    m_iErrno = m_pHdr->getErrorNo();
        }
    if (m_iErrno == 0)		/* init 'this' from the header */
        m_iErrno = _MapFromImageHeader(); /* in case write->init changed any*/
    m_pHdr->clearUpdatesNeeded();
    m_bHdrUpdated = FALSE;		/* TRUE => need to rewrite header */
    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_HDRWRITTEN;
    if (m_iDebug)
	fprintf(stderr,m_pHdr->dump(1,"Image::writeHeader (ex)"));
    if (m_iTrace)
	logTrace(m_pHdr->dump(1,"Image::writeHeader (ex)"));
    if (m_iTrace)
	logTrace("%s (ex) returns %d",czMethod,m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) returns %d\n",czMethod,m_iErrno);
    return m_iErrno;
    }

	/*	rewrite image header and write trailer
	 *	On exit, file is closed
	 *	This CAN be used for modifiable input image
	 *	@param uDataCheck	checksum of the image data rows
	 *				for trailer (0 => not valid)
	 *	@param bWriteTrailer	FALSE => don't write trailer yet
	 *	Return 0 if OK
	 *	Error values are:
	 *		-16 => op not needed (not an error)
	 *		-50 - -55 file IO errors
	 *		-65 => no name supplied
	 *		-66 => image state conflict
	 *		-69 => no header writer found
	 */
int Image::rewriteHeader(UINT32 uDataCheck, BOOL bWriteTrailer /* TRUE */)
    {
    if (m_iErrno > 0) // seems like it has the line count
	m_iErrno = 0;
    if (m_iTrace)
	logTrace("Image::rewriteHeader (en) "
		 "img# %d name='%s'\n\tstate=%s",
		 image.thisone,image.filename,getStateName());
    if (m_iDebug)
	fprintf(stderr,"Image::rewriteHeader (en) "
	       "img# %d name='%s' errno=%d = %s\n\t state=%s origname=%s\n",
			 image.thisone,image.filename,m_iErrno,
	       getErrorMessage(),getStateName(),m_pHdr->getImageHdr()->h_OriginalFileName);
    if (! m_bHdrUpdated)
	m_iErrno = DERR_NOT_NEEDED;
    else if ((m_uState != IMG_HDRWRITTEN)
	     && (m_uState != IMG_CHANGED) 
	     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable) )
	m_iErrno = DERR_IMAGE_BADSTATE;
    else if (m_pWriter == NULL)
	m_iErrno = DERR_IMAGE_NOWRITE;
    if ((m_iErrno == 0) && (m_uState == IMG_CHANGED)) 
        {
	m_iErrno = m_pWriter->rewriteHeader(this);
	m_pHdr->clearUpdatesNeeded();
	}

    int iStatus = closeImageFile(); // close the files
    if ((m_iErrno >= DERR_NOT_NEEDED) && (iStatus < 0))
    	m_iErrno = iStatus;

    m_uState = (m_iErrno < DERR_NOT_NEEDED) ? IMG_ERROR 
	    : (m_uState == IMG_INITFROMFILE) ? IMG_INITFROMFILE : IMG_HDRWRITTEN;
    m_bHdrUpdated = FALSE;		/* TRUE => need to rewrite header */
    if (((m_iErrno == 0) || (m_iErrno == DERR_NOT_NEEDED)) && bWriteTrailer)
        m_iErrno = writeTrailer(uDataCheck); // does closeImageFile
    if (m_iTrace)
        {
	logTrace("Image::rewriteHeader (ex) "
		 "img# %d name='%s' state=%s",
		 image.thisone,image.filename,getStateName());
	logTrace(m_pHdr->dump(1,"Image::rewriteHeader"));
	}
    return m_iErrno;
    }

	/*	append trailer on the file 
	 *	@param uDataCheck	checksum of image data
	 *	@return		0 if OK
	 *	Error values are:
	 *		-54 => error closing file before append
	 *		-65 => no name supplied
	 *		-66 => image state conflict
	 *		-69 => no header writer found
	 *		-60 => header completely uninitialized 
	 *		plus file and memory errors
	 */
int Image::writeTrailer(UINT32 uDataCheck)
    {
    if (m_iTrace)
	Logger::logTrace("Image::writeTrailer (en) "
			 "img# %d name='%s'\n\tstate=%s",
			 image.thisone,image.filename,getStateName());
    if (m_iDebug)
	fprintf(stderr,"Image::writeTrailer (en) "
	       "img# %d name='%s' errno=%d = %s\n\t state=%s\n",
	       image.thisone,image.filename,m_iErrno,
	       getErrorMessage(),getStateName());
    int iStatus = closeImageFile(); // make sure files are closed
    if ((m_iErrno >= DERR_NOT_NEEDED) && (iStatus < 0))
	m_iErrno = iStatus;
    const IMAGEHDR * pImgHeader = getIMAGEHDR();
    if ((m_iErrno >= DERR_NOT_NEEDED) && (strlen(image.filename) == 0))
	m_iErrno = DERR_IMAGE_NONAME;
    else if (m_pWriter == NULL)
	m_iErrno = DERR_IMAGE_NOWRITE;
    else if ((m_uState != IMG_HDRWRITTEN)
	     && (! (m_uState == IMG_INITFROMFILE) && m_bModifiable) )
	m_iErrno = DERR_IMAGE_BADSTATE;
    else
	m_iErrno = m_pWriter->writeTrailer(image.filename,
					   pImgHeader,uDataCheck);
//    m_uState = (m_iErrno < 0) ? IMG_ERROR : IMG_CLOSED;
    if (m_iTrace)
	Logger::logTrace("Image::writeTrailer (ex) returns %d",m_iErrno);
    return m_iErrno;
    }

	/*	Put a line of raw data to the file
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *
	 *	@param pBuf	pointer to the source data buffer
	 *	@param uLineNo	image memory line to rwrite
	 *	@param uBufSize	the size of pBuf
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *				-60 => image not yet initialized
	 *				-66 => image state conflict
	 *				-68 => image not writable
	 *				-51 => file open error
	 */
int Image::putImageLineRaw(const byte * pBuf, ushort uLineNo,
			   size_t uBufSize)
    {
    int iRetval = 0;
    if (m_pHdr == NULL)
	m_iErrno = DERR_IMAGE_UNINIT;
    else if (m_pWriter == NULL)
	m_iErrno = DERR_IMAGE_NOREAD;
    else if ((m_uState != IMG_HDRWRITTEN) && (m_uState != IMG_CHANGED) 
	     && !m_bModifiable)
	m_iErrno = DERR_IMAGE_BADSTATE;
    else
        {
	iRetval = m_pWriter->putImageLineRaw(pBuf,uLineNo,uBufSize, 
					     &image,m_bReReadable);
	if (iRetval < 0)
	    m_iErrno = iRetval;
	if (((uLineNo % 2000) == 0) && m_iTrace)
	    logTrace("img::putImageLineRaw line %d status=%d pitch=%d\n"
		     "\tbufsize=%d img#=%d ProcRect.X=%d",
		     uLineNo,m_iErrno,image.ulPixPitch,uBufSize,image.thisone,
		     image.ProcessRect.Xmax);
	}
    if (m_iDebug && (m_iErrno < 0))
	fprintf(stderr,"Image::putImageLineRaw Error %d line %d bufsize=%d state=%s\n",
	       m_iErrno,uLineNo,uBufSize,getStateName());
    if (m_iTrace && (m_iErrno < 0))
	logTrace("Image::putImageLineRaw Error %d line %d\n\tbufsize=%d state=%s",
	       m_iErrno,uLineNo,uBufSize,getStateName());
    return (m_iErrno < 0) ? m_iErrno : iRetval;
    }

	/*	put a line of pixels to the file.
	 *	The base class calcs are OK for file formats where
	 *	lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *
	 *	@param pBuf	pointer to the source data buffer
	 *	@param uLineNo	image memory line to write
	 *	@param uBufSize	the size of pBuf
	 *	@return 	number of bytes transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *				-60 => image not yet initialized
	 *				-66 => image state conflict
	 *				-68 => image not writable
	 *				-51 => file open error
	 */
int Image::putImageLine(const byte * pBuf, ushort uLineNo,
			 size_t uBufSize)
    {
#undef FN_NAME
#define FN_NAME "img::putImageLine"
    if ((m_iTrace > 1) || ((m_iTrace > 0) && (uLineNo == 0)))
	logTrace(FN_NAME " (en) image %d line %d",image.thisone,uLineNo);
    int iRetval = 0;
    if (m_pHdr == NULL)
	iRetval = DERR_IMAGE_UNINIT;
    else if (m_pWriter == NULL)
	iRetval = DERR_IMAGE_NOREAD;
    else if ((m_uState != IMG_HDRWRITTEN) && (m_uState != IMG_CHANGED) 
	     && !m_bModifiable)
	iRetval = DERR_IMAGE_BADSTATE;
    else
        {
	iRetval = m_pWriter->putImageLine(pBuf,uLineNo,uBufSize, 
					  &image, m_bReReadable);
	if (((uLineNo % 2000) == 0) && m_iTrace)
	    logTrace(FN_NAME " line %d status=%d pitch=%d "
		     "bufsize=%d img#=%d ProcRect.X=%d",
		     uLineNo,iRetval,image.ulPixPitch,uBufSize,image.thisone,
		     image.ProcessRect.Xmax);
	}
    if (iRetval < 0)
	m_iErrno = iRetval;
    if (m_iDebug && (m_iErrno < 0))
	fprintf(stderr,"Image::putImageLine Error %d line %d bufsize=%d state=%s\n",
	       m_iErrno,uLineNo,uBufSize,getStateName());
    if (m_iTrace && (m_iErrno < 0))
	logTrace("Image::putImageLine Error %d line %d bufsize=%d state=%s\n",
	       m_iErrno,uLineNo,uBufSize,getStateName());
    if ((m_iTrace > 1) || ((m_iTrace > 0) && (uLineNo == 0)))
	logTrace(FN_NAME " (ex) returns %d",iRetval);
    return iRetval;
    }

int Image::SynchImage2DragonHdr(const IMAGEHDR * pHdr)
	/*	bring 'image' image stats & scaling into agreement with 'pHdr',
	 *	before attempting to load or use an input image file.
	 *	Requires that pixels, lines, ulPixPitch, ulLinePitch
	 *	be already set, and pHdr updated to 4.1 or later
	 *	This is ONLY for DRAGON format files,
	 *	and ONLY for input images.
	 *	Return < 0 if err:
	 *		-70: not permitted for this image.
	 *		-71: hdr stats not initialized
	 */
    {
#undef FN_NAME
#define FN_NAME "img::SynchImage2DragonHdr"
    if (m_iTrace)
	logTrace(FN_NAME " (en) img# %d error=%d",image.thisone,m_iErrno);
    if (m_iDebug>1)
	fprintf(stderr,"    Image::SynchImage2DragonHdr (en) img# %d error=%d\n",
		image.thisone,m_iErrno);
//    if ((image.thisone == MAINIMG) || (image.thisone == OUTPUTIMAGE))
//	return DERR_IMAGE_INVALIDOP;
//    hdrInfo.uKey = pHdr->uKey;
    if (!pHdr->bImageHdrStatsInit)
        {
	logTrace(FN_NAME " (ex) ERROR status=%d",DERR_HDR_NOSTATS);
	return DERR_HDR_NOSTATS;
        }
    image.residentflag = RES_INIT;	/* hdr init but file not read yet */
    image.modflag = MOD_MATCHDISK;	/* no modifications yet */
    image.uPreferredScaling = (image.ulPixPitch > 1) ? 1 : 0;
    image.uLabelEncoding = 3;
#if DRAGON_VER >= 6
    image.m_iImgmean = pHdr->m_ihImgmean;
    image.m_iImgmax = pHdr->m_ihImgmax;
    image.m_iImgmin = pHdr->m_ihImgmin;
    image.m_dImgsd  = pHdr->m_dhImgsd;
    image.m_dImgvar  = pHdr->m_dhImgvar;
    CalcImageScale(image.pixbits, pHdr->m_ihImgmax,pHdr->m_ihImgmin,
		   NULL,NULL);
#else
    image.imgmean = pHdr->imgmean;
    image.imgmax = pHdr->imgmax;
    image.imgmin = pHdr->imgmin;
    image.imgsd  = pHdr->imgsd;
    image.imgvar  = pHdr->imgvar;
    CalcImageScale(image.pixbits, pHdr->imgmax,pHdr->imgmin,
		   NULL,NULL);
#endif

    if (m_iDebug>1)
	fprintf(stderr,"    Image::SynchImage2DragonHdr (ex) "
			 "offset of ref_x in header is 0x%x "
			 "value of xcell_size in header is 0%f error=%d\n",
			 offsetof(IHEAD,ref_x),
			 pHdr->xcell_size,m_iErrno);
    
    if (m_iTrace)
	logTrace(FN_NAME " (ex) "
			 "offset of ref_x in header is 0x%x "
			 "value of xcell_size in header is 0%f error=%d",
			 offsetof(IHEAD,ref_x),
			 pHdr->xcell_size,m_iErrno);
    return 0;
    }

int Image::SynchImageHistogram(const IMAGEHDR * pHdr)
	/*	bring histogram stats into agreement with 'pHdr',
	 *	before attempting to load or use an input image file.
	 *	This is ONLY for DRAGON format files,
	 *	and ONLY for input images.
	 *	Return < 0 if err
	 *		-70: not permitted for this image.
	 *		-71: hdr stats not initialized
	 */
    {
	/* if we are loading the data, allocate the histogram if necessary */
	/* and then copy from the header */
      // void * newhist = NULL;
    IMGHISTO * lpHist = NULL;
//    fprintf(stderr,"stepM1\n");
    if (m_iTrace)
	logTrace("Image::SynchImageHistogram (en) img# %d type %c error=%d",
		 image.thisone,pHdr->ftype[0],m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"\tImage::SynchImageHistogram (en) img# %d type %c error=%d\n",
	       image.thisone,pHdr->ftype[0],m_iErrno);
    if (pHdr->histo == NULL)
	return DERR_HDR_NOHISTO;
//    if ((image.thisone == MAINIMG) || (image.thisone == OUTPUTIMAGE))
//	return DERR_IMAGE_INVALIDOP;
    lpHist = (IMGHISTO *) calloc(1,sizeof(IMGHISTO));
    if (lpHist == NULL)
	return DERR_HDR_NOSTATS;
		/* 
		 * copy hist data from HDR to IMGHISTO
		 * expanding as needed 
		 */
            /* zero out all 257 elements first */
    for (int i=0; i < IMG_HIST_LEN; i++)
	lpHist->bin[i] = 0L;
    lpHist->bin[0] = pHdr->histo[0];
    if ((pHdr->ftype[0] != 'C') && (pHdr->ftype[0] != 'L')) 
        {
	for (ushort i = 1; i < IMG_HIST_LEN; i++)
	    {
	    ulong filefreq = pHdr->histo[ ((i-1)>>2) + 1];
	    lpHist->bin[i] = filefreq >> 2;
	    if ((i-1) % 4 == 0)
		lpHist->bin[i] += (filefreq % 4);
	    /* add any excess to first bin in set of 4 */
	    }
	m_uHistPtrCount = IMG_HIST_LEN;
	image.residentflag
	    = (image.residentflag & RES_RESMASK) | RES_MEMHIST;
	}
    /* Split the file histogram frequencies into four
     * equal bins to copy into the memory histogram. The
     * memory histogram now has 256 +1 elements while the
     * file histogram has only 64 + 1. 
     */
    else   /* for classified/layer images, copy directly */
        {
//    fprintf(stderr,"stepM5\n");
	for (int i = 1; i < pHdr->uHdrHistLen; i++)
	    {
	    lpHist->bin[i] = pHdr->histo[i];
	    }
	m_uHistPtrCount = pHdr->uHdrHistLen;
	image.residentflag
	    = (image.residentflag & RES_RESMASK) | RES_SMALLHIST;
	}
    m_uHistPtrBinsize = 1;
    lpHist->bin[0] = pHdr->histo[0];
    if (image.histptr != NULL)
        {
	free(image.histptr);
	image.histptr = NULL;
        }
    image.histptr = lpHist;
    if (m_iTrace)
	logTrace("Image::SynchImageHistogram (ex) success error=%d",m_iErrno);
    if (m_iDebug)
	fprintf(stderr,"\tImage::SynchImageHistogram (ex) success error=%d\n",
		m_iErrno);
    return 0;
    }

	/* Calculate and return a scaling factor needed to 
	 * ~~~ verify this for v 5.12
	 * NOTES 2012-Feb
	 *   If not > 8 bits this has no significant effect except
	 *   to set IMAGE fiedls to default values
	 *   This fn is used only by Image::SynchImage2DragonHdr
	 *   and the return value is never used
	 * convert data ranging from 'iMinV' to 'iMaxV' to 8-bits
	 * The question of which of these to use is tricky:
	 *  The 'optimized' gives a better single-band display and
	 *     is probably better for single-band analysis.
	 *  However, multi-band ops need to use consistent factors
	 *     across all images, which is easier using the scaling version.
	 *  Therefore: 1BA, GRA, OVE use optimized; 3BA uses scaling
	 *	       Enhance all use scaling, but should be rewritten 16bit
	 *	       F/SUB gives a choice
	 *	       G use optimized for display, but VEC & COO produce
	 *		scaled output
	 *	       C use scaled, but signatures could be enhanced
	 *		to specify the optimized values
         * ~~~ IS THE ABOVE TRUE? I don't see where or how it is enforced
         *    seg, 7/11/07
	 * This fn should replace CalcScale in dragonu.c
	 *   'puDataOffset', 'puDataFactor' corresp. more or less 
	 *       to 'dScaleOffset', 'dScaleFactor' in dhead,
	 *	 and 'uDataOffset','uDataFactor' in IMAGE
	 *   while 
	 *      dhead.fields.uScaleFactor = IMAGE.uScaleFactor = 1 << retval
	 * @param  uBitsPP	0, 8, or 16
	 * @param  iMaxV	largest image data value
	 * @param  iMinV	smallest image data value
	 * @param  puDataOffset	NULL or where to put optimized offset
	 *			(really, just iMinV)
	 * @param  puDataFactor	NULL or where to put optimized scaling factor
	 *			(divisor for optimized:
	 *			  8BitVal 
	 *			     = (16BitVal - uDataOffset) / uDataFactor)
	 * @return		power-of-two divisor for non-optimized scaling
	 *			(=0 if uBitsPP <= 8)
	 * 			also set three IMAGE fields
	 */
#if DRAGON_VER >= 6
ushort Image::CalcImageScale(ushort uBitsPP,int iMaxV, int iMinV,
			     ushort * puDataOffset, ushort * puDataFactor)
#else
ushort Image::CalcImageScale(ushort uBitsPP,ushort iMaxV, ushort iMinV,
			     ushort * puDataOffset, ushort * puDataFactor)
#endif
    {
#   undef FN_NAME
#   define FN_NAME "Image::CalcImageScale"
    ushort retval = 0;
    ushort uDataFactor = 1;
    ushort uDataOffset = 0;	
    logTrace(FN_NAME  " (en) bits=%d max=%d min=%d",
	     uBitsPP,iMaxV,iMinV);
    if (uBitsPP > 8)
        {
	int range = iMaxV >> 8;
	int iDiff = iMaxV - iMinV;
	uDataFactor += (ushort)((iDiff + 255L) / 256L);
	uDataOffset = iMinV;
	while(range != 0)
	    {
	    retval++;
	    range >>= 1;
	    }
        }
    if (puDataOffset != NULL)
	*puDataOffset = uDataOffset;
    if (puDataFactor != NULL)
	*puDataFactor = uDataFactor;
    image.uDataOffset = uDataOffset;
    image.uDataFactor = uDataFactor;
    image.uScaleFactor = 1 << retval;
    logTrace(FN_NAME  " (ex) returns %d calc'd offset=%d factor=%d scale=%d",
	     retval,uDataOffset,uDataFactor,image.uScaleFactor);
    return retval;
    }

/* Add operations here if you want to keep full 16-bit resolution */
#define SIXTEENBITOPS "HEA|SAV|"

	/* Get max bits per pixel for main image.
         * This may depend on the operation
	 * @param pczOp		3-letter operation code, or "" or NULL
	 *			if "" or NULL return lowest value
	 */
ushort Image::getWorkingBits(const char * pczOp)
   {
   ushort uBits = 8;
   if ((pczOp != NULL) && (strlen(pczOp) > 0))
      {
      if (strstr(SIXTEENBITOPS,pczOp) != NULL)
	 {
         uBits = 16; 
         }  
      }
   return uBits;
   }

void IMG_END() { puts(FIL_ID); }

/************************************************************************/
#ifdef TEST

// for VP_DRAWLINE?
#include "grs_ipc.h"

extern "C"
{
static char* czFile[] = { "","mekdmdm.img",
			  "mek14-1.img","alfagood.img",
                          "singapore1.img"};
static char* czFileDescr[] = { "","v 4.1 classified English labels",
			       "v 1.0 8-bit","v 4.1 16-bit",
                               "v 5.8 1024 x 1024"};

static char * pczTextBlob = "This is a blob which can be written into the "
			    "trailer of a file for testing. Obviously it "
			    "will not display onto a viewport.";

static VP_DRAWLINE linesBlob[] // x0,y0,x1,y1,color,...
	= { {50,50,50,100,211},
	    {50,100,100,100,211},
	    {100,100,100,50,211},
	    {100,50,50,50,211}};

void usage()
    {
    printf ("Test Image class by reading some file header\n");
    printf ("Usage: img.TEST [-v [-v]] [-f filepath [-o outformat [-b b|t]]] [-r readpath] -t testno\n");
    printf ("	-v => verbose (-v -v) is even more)\n");
    printf ("	-t => test number. Available are:\n");
    printf ("		0 = Read specified file or none\n");
    for (size_t j=1; j<AY_COUNT(czFile); j++)
	printf ("		%d = Read file %s: %s\n",
		j,czFile[j],czFileDescr[j]);
    printf ("	-f => file to read for test 0 or write for tests 1...n\n");
    printf ("	-o => when used with tests 1...n also write new file in specified format\n");
    printf ("         Available formats may include: \n");
    printf ("		DRAGON ERDAS BIL BSQ TIFF CHUNK54 CHUNK60\n");
    printf ("	-b => when used with tests -o to DRAGON, write a LinesBlob\n");
    printf ("         choices are '-b t' write text blob\n");
    printf ("                     '-b b' write binary (real drawlist) blob\n");
    exit (1);
    }

int main(int argc, char ** argv)
    {
    int iVerbose = 0;
    int iTestNum = -1;
    char czFilename[PATH_MAX] = "";
    //    char czReadFile[PATH_MAX] = "../../../OpenDragon/testdata/";
    char czReadFile[PATH_MAX] = "f:/pix/";
    char czFormatName[20] = "";
    uint uBlobType = 0;  // or 'b' or 't'
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
	else if (strcmp(*argv,"-r") == 0)
	    { strcpy(czReadFile,*(++argv)); --argc; }
	else if (strcmp(*argv,"-o") == 0)
	    { 
	    strcpy(czFormatName,"IT_");
	    strcat(czFormatName,*(++argv)); --argc;
	    }
	else if (strcmp(*argv,"-b") == 0)
	    { uBlobType = (uint)**(++argv); --argc; }
	else
	    usage();
        }
    if (iTestNum < 0)
        {
	printf ("missing test number argument\n");
	usage();
        }
    Image img0(iVerbose,0), imgout(iVerbose,0);
    if (iVerbose)
	fprintf(stderr,"Images constructed; test num = %d\n",iTestNum);
    if (iTestNum != 0)
        { strcat_array(czReadFile,czFile[iTestNum]); }
    else if (strlen(czFilename) > 0)
        {
	strcpy_array(czReadFile,czFilename);
	}
    else
	usage();
    BOOL bOutputLines = FALSE;
    if (iVerbose)
	fprintf(stderr,"Format specified: %s (%s)\n",
	       YESNO(strlen(czFormatName)),czFormatName);
    if (strlen(czFormatName) > 0)
        {
	uOutFormat = IT_INVALID;
	for (int j = IT_DRAGON; j<IT_INVALID; j++)
	    {
	    if (strcmp(ImageHdr::ImageTypeName((IMGTYPE_T)j),
		       czFormatName) == 0)
	        {
		uOutFormat = (IMGTYPE_T)j;
		bOutputLines = TRUE;
		break;
	        }
	    }
	}
    if (iVerbose)
        {
	fprintf(stderr,"\nMain (en) test number %d from file %s output to %s\n",
	       iTestNum,czReadFile,ImageHdr::ImageTypeName(uOutFormat));
	fprintf(stderr,"    (sizes UINT32=%d uint=%d ushort=%d ulong=%d double=%d)\n",
	       sizeof(UINT32),sizeof(unsigned int),sizeof(ushort),
	       sizeof(ulong),sizeof(double));
	}
    if (img0.open(czReadFile,bOutputLines) < 0)
        {
	printf ("open failure of input image: %d=%s\n",
		img0.getErrorNo(),img0.getErrorMessage());
	exit(1);
	}
    fprintf(stderr,"%s\n",img0.dump(0,"Dump of input image"));
    fprintf(stderr,"%s\n",img0.getImageHeader()->dump(0,"Dump of input imageHdr"));
    ushort nLines = img0.getImage()->lines;
    ushort nPix = img0.getImage()->pixels;
    ushort nBytes = ( img0.getImage()->pixbits + 7 ) / 8;
    ushort outBytes = 0;
    ushort uBytesPP = (img0.image.ulPixPitch > 0) 
	? (ushort) img0.image.ulPixPitch : 1 ;
    byte * midbuf = (byte *)calloc(nPix,uBytesPP);
    byte * inbuf = midbuf;
    byte * outbuf = NULL;
    if (uOutFormat == IT_INVALID)
	printf ("Unable to create %s: format not supported\n",
		czFormatName);
    else if (uOutFormat != IT_UNINIT)
        {
	int status = imgout.create(czFilename, FALSE, FALSE, uOutFormat,
				   &img0,NULL);
	fprintf(stderr,"output image created; img errno=%d=%s\n",
	       imgout.getErrorNo(),imgout.getErrorMessage());
	if (imgout.getErrorNo())
	    exit(1);
        status = imgout.update_metainfo("demometa.dmf","1234098");
        if (status < 0)
	    fprintf(stderr,"Error %d - in updating the metainfo\n",status);
        else
	    {
            status = imgout.update_extent(0.0,0.0,1024.0,1024.0);
            if (status < 0)
	       fprintf(stderr,"Error %d - in updating the extent\n",status);
            }
	status = imgout.writeHeader();
	outBytes = imgout.getImage()->ulPixPitch;
	fprintf(stderr,"Main: writing header : success=%s status=%d hdrstatus=%d\n",
		YESNO(status==0),imgout.getErrorNo(),
	       imgout.getImageHeader()->getErrorNo());
	fprintf(stderr,"%s\n",
	       imgout.getImageHeader()->dump(0,
					     "Main: dump of output image hdr"));
	outbuf = (byte *)calloc(nPix,outBytes);
	if (nBytes > 1)
	    inbuf = (byte *)calloc(nPix,nBytes);
	else
	    inbuf = midbuf;
	}
    fprintf(stderr,"About to read image of %d lines inbuf = %p\n",nLines,inbuf);
    if (inbuf != NULL)
        {
	ushort j;
	int status;
	for (j=0; j<nLines; j++)
	    {
	    status = img0.getImageLine(inbuf,j,nBytes*nPix*uBytesPP);
	    if (status != nPix)
	        {
		fprintf(stderr,"Error %d reading line %d of %s\n",
		       status,j,czReadFile);
		break;
		}
	    fprintf(stderr,"reading line %d = %d\r",j,status);
	    if (bOutputLines)
	        {
		if (nBytes > 1) /* scale data to midbuf */
		    {
		    ushort * pIN = (ushort *)inbuf;
		    byte * pMid = midbuf;
		    for (ushort jj=0; jj<nPix; jj++)
			*pMid++ = *pIN++;
		    }
		byte * pMid = midbuf;
		byte * pOut = outbuf;
		for (ushort jj=0; jj<nPix; jj++)
		    {
		    *pOut = *pMid++;
		    pOut += imgout.getImage()->ulPixPitch;
		    }
		int iStat = imgout.putImageLineRaw(outbuf,j,outBytes * nPix);
		if ((j % 50) == 0)
		    fprintf(stderr,"	outputting line %d size=%d x %d stat=%d\n",
			   j,outBytes,nPix,iStat);
		if (iStat < 0)
		    break;
	        }
	    }
	if (status >= 0)
	    fprintf(stderr,"Main succeeded in reading %d lines status=%d\n",j,status);
	if ((uOutFormat == IT_DRAGON) && (uBlobType != 0))
	    {
	    if (uBlobType == 't')
	        {
	        imgout.setLinesBlob((byte *)pczTextBlob,strlen(pczTextBlob));
		fprintf(stderr, "Blob test type=x%X = '%c', size=%d\n",
			uBlobType,uBlobType,strlen(pczTextBlob));
		}
	    else
	        {
	        imgout.setLinesBlob((byte *)linesBlob,sizeof(linesBlob));
		fprintf(stderr, "Blob test type=x%X = '%c', size=%d\n",
			uBlobType,uBlobType,sizeof(linesBlob));
		}
	    }
	if (bOutputLines)
	    {
	    status = imgout.rewriteHeader(0,TRUE);
	    fprintf(stderr,"Main creating output file status = %d = %s\n",status,
		   dragonErrorMessage(status));
	    }
	}
    img0.CloseImage();
    return 0;
    }
}
#endif
