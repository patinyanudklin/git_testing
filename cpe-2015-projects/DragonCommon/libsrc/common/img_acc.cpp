#include "drelease.h"
char IMG_ACC1_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.144 $$Date: 2015/01/02 05:33:49 $";
D_REL_IDSTR;
/*-------------------------------------------------------------
 *	   IMG_ACC.CPP
 *
 *	~~ Copyright 1985-2015 Kurt Rudahl and Sally goldin
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
 ***************************************************
 *  $Id: img_acc.cpp,v 1.144 2015/01/02 05:33:49 rudahl Exp $
 *  $Log: img_acc.cpp,v $
 *  Revision 1.144  2015/01/02 05:33:49  rudahl
 *  protect dump wrapper from null header pointer
 *
 *  Revision 1.143  2015/01/02 03:16:27  rudahl
 *  fix Dragon/OpenDragon conditional
 *
 *  Revision 1.142  2014/12/29 03:28:29  rudahl
 *  convert to using dragon version number
 *
 *  Revision 1.141  2014/12/07 12:05:45  rudahl
 *  adapt to OpenDragon
 *
 *  Revision 1.140  2014/04/02 12:02:22  rudahl
 *  finished separating dtk,rosetta to new mingw version adaptations for Linux build
 *
 *  Revision 1.139  2014/04/02 03:23:35  rudahl
 *  prepare to separate dtk,rosetta to new mingw version adaptations for Linux build
 *
 *  Revision 1.138  2014/03/28 14:51:12  rudahl
 *  working on auto import
 *
 *  Revision 1.137  2011/12/30 11:54:37  rudahl
 *  lint
 *
 *  Revision 1.136  2011/09/02 11:23:49  rudahl
 *  reduce amount of trace output
 *
 *  Revision 1.135  2011/01/12 04:42:34  rudahl
 *  added new registration fields to update_georef and header
 *
 *  Revision 1.134  2010/12/05 03:55:25  rudahl
 *  changed some param datatypes
 *
 *  Revision 1.133  2008/09/27 08:17:16  rudahl
 *  improved tracing
 *
 *  Revision 1.132  2008/09/12 03:40:22  rudahl
 *  enhanced dump
 *
 *  Revision 1.131  2008/06/19 12:51:54  goldin
 *  Working on vector blob handling
 *
 *  Revision 1.130  2008/06/19 08:39:22  rudahl
 *  testing blob access
 *
 *  Revision 1.129  2008/06/19 08:27:07  rudahl
 *  testing blob access
 *
 *  Revision 1.128  2008/06/14 15:56:18  goldin
 *  Implement code to save and
 *
 *  Revision 1.127  2008/06/14 10:15:28  rudahl
 *  added LinesBlob to trailer
 *
 *  Revision 1.126  2008/04/30 03:18:54  rudahl
 *  improved tracing, cleanup
 *
 *  Revision 1.125  2008/04/27 10:32:10  rudahl
 *  improved notices, tracing
 *
 *  Revision 1.124  2008/04/27 06:01:08  rudahl
 *  improved notices, tracing
 *
 *  Revision 1.123  2008/04/05 11:46:24  rudahl
 *  tracing
 *
 *  Revision 1.122  2007/10/09 11:23:09  goldin
 *  fix bug in fillImage - was checking for status != 0 from PutImageLIne 
 *  - but it returns number of pixels written
 *
 *  Revision 1.121  2007/10/03 11:35:49  goldin
 *  Move getMostRecentWorkingImage and related fns to separate source
 *
 *  Revision 1.120  2007/10/03 10:13:47  rudahl
 *  simplify symbols matching dlimits
 *
 *  Revision 1.119  2007/09/09 11:45:39  goldin
 *  Move getWorkingImagePath to the server
 *
 *  Revision 1.118  2007/08/07 09:21:56  rudahl
 *  added tracing
 *
 *  Revision 1.117  2007/08/02 12:53:56  rudahl
 *  part of 32-bit convert; IMG now has signed params; cleanup
 *
 *  Revision 1.116  2007/07/11 11:11:20  goldin
 *  removed unused code
 *
 *  Revision 1.115  2007/02/11 04:39:28  rudahl
 *  cleanup
 *
 *  Revision 1.114  2007/02/10 06:50:08  goldin
 *  Use image fields not header values for lines and pixels
 *
 *  Revision 1.113  2007/02/05 11:12:27  goldin
 *  Use image info to allocate buffer
 *
 *  Revision 1.112  2007/01/26 06:38:57  goldin
 *  Handle 0 bits/pix correctly in create functions
 *
 *  Revision 1.111  2007/01/01 13:35:51  rudahl
 *  improving tracing
 *
 *  Revision 1.110  2007/01/01 09:42:47  rudahl
 *  improved tracing, dumps; originalfileinfo
 *
 *  Revision 1.109  2006/12/31 12:12:41  rudahl
 *  fixing up the external driver and trailer access
 *
 *  Revision 1.108  2006/11/16 10:05:23  goldin
 *  Add new functions to update meta data from appl. programs
 *
 *  Revision 1.107  2006/11/12 07:01:06  goldin
 *  New functions to update meta info for images and vector data sets
 *
 *  Revision 1.106  2006/11/11 10:07:21  goldin
 *  add clearImageMetaInfo
 *
 *  Revision 1.105  2006/11/11 08:08:03  goldin
 *  Refactoring to support igc metafile update
 *
 *  Revision 1.104  2006/02/12 10:44:20  goldin
 *  Update documentation on CalcAndSetImageStats
 *
 *  Revision 1.103  2006/02/12 08:14:31  rudahl
 *  fixed fns which should have required a const IMAGE
 *
 *  Revision 1.102  2006/02/07 08:38:10  goldin
 *  add new fn to explicitly set processRect values
 *
 *  Revision 1.101  2006/01/06 12:47:09  goldin
 *  got rid of some deadwood
 *
 *  Revision 1.100  2005/12/30 10:37:53  rudahl
 *  added support for dump(detail
 *
 *  Revision 1.99  2005/12/30 09:25:59  goldin
 *  Allow reading beyond working lines/pixels
 *
 *  Revision 1.98  2005/12/10 11:36:53  rudahl
 *  fixing some of the double-tilde comments
 *
 *  Revision 1.97  2005/09/17 11:01:13  rudahl
 *  improved dump
 *
 *  Revision 1.96  2005/09/17 05:30:09  rudahl
 *  improved trace
 *
 *  Revision 1.95  2005/09/15 05:40:16  rudahl
 *  fix linkage problems involving dp.cpp, wgetWorkingLines
 *
 *  Revision 1.94  2005/09/12 07:30:41  rudahl
 *  fixes re dp.h
 *
 *  Revision 1.93  2005/09/07 05:04:18  rudahl
 *  added getLabel
 *
 *  Revision 1.92  2005/08/18 03:51:51  rudahl
 *  fixed getimageline errormsg
 *
 *  Revision 1.91  2005/08/13 08:40:32  goldin
 *  update documentation
 *
 *  Revision 1.90  2005/08/12 09:21:03  goldin
 *  augment documentation
 *
 *  Revision 1.89  2005/07/29 04:00:41  rudahl
 *  improved docs
 *
 *  Revision 1.88  2005/07/22 15:12:32  rudahl
 *  added header fields, functions
 *
 *  Revision 1.87  2005/07/03 13:30:52  rudahl
 *  improving createImage
 *
 *  Revision 1.86  2005/06/27 11:47:24  rudahl
 *  added some access fns, improved dump
 *
 *  Revision 1.85  2005/06/26 06:18:15  rudahl
 *  moved pFp from Image to ImageReader,Writer
 *
 *  Revision 1.84  2005/04/25 13:55:13  goldin
 *  Make IMAGE* args const
 *
 *  Revision 1.83  2005/04/08 13:24:59  goldin
 *  Add more tracing
 *
 *  Revision 1.82  2005/04/08 07:20:29  goldin
 *  Re-implement fillImage (was fill_image)
 *
 *  Revision 1.81  2005/04/08 06:56:16  goldin
 *  Change source argument in createImageCopy 
 *  to be IMAGE* not Image* (otherwise can't use in C)
 *
 *  Revision 1.80  2005/04/06 13:23:13  goldin
 *  img_acc should pass buffer size to image->getImageLine, 
 *  not number of pixels
 *
 *  Revision 1.79  2005/04/05 08:01:18  rudahl
 *  cleaned up spurious printfs
 *
 *  Revision 1.78  2005/03/31 06:47:26  goldin
 *  Add convenience method CalcAndSetStats
 *
 *  Revision 1.77  2005/03/27 12:48:06  rudahl
 *  fixed hdr status error
 *
 *  Revision 1.76  2005/03/19 06:31:51  rudahl
 *  CVS moved from windu; maybe some history lost
 *
 *  Revision 1.86  2005/03/13 02:40:59  rudahl
 *  fix probs found working with enhance
 *
 *  Revision 1.85  2005/03/11 22:45:13  goldin
 *  Debug update_labels
 *
 *  Revision 1.84  2005/03/11 21:36:52  rudahl
 *  added getWorkingImage stuff
 *
 *  Revision 1.83  2005/03/11 20:27:54  goldin
 *  debugging rewriteImageHeader
 *
 *  Revision 1.82  2005/03/11 18:05:59  rudahl
 *  added getWorkingbits
 *
 *  Revision 1.81  2005/03/11 17:10:34  rudahl
 *  revised zero, CloseImage, rewriteHeader
 *
 *  Revision 1.80  2005/03/10 21:33:33  goldin
 *  Working on new test
 *
 *  Revision 1.79  2005/03/10 03:18:31  goldin
 *  Still working on img_acc test code
 *
 *  Revision 1.78  2005/03/10 00:06:29  rudahl
 *  added imageHdr.h
 *
 *  Revision 1.77  2005/03/09 02:45:17  goldin
 *  Fixing bugs related to creating brand new image
 *
 *  Revision 1.76  2005/03/09 01:34:14  rudahl
 *  fix missing args in new(), add CloseImage
 *
 *  Revision 1.75  2005/03/07 23:39:27  goldin
 *  Working on img_acc test functions
 *
 *  Revision 1.74  2005/03/06 17:31:04  rudahl
 *  revising create() and update_text() args
 *
 *  Revision 1.73  2005/03/06 00:17:13  rudahl
 *  moved creation of writer to createheader
 *
 *  Revision 1.72  2005/03/03 23:25:10  goldin
 *  Began to add test fn to img_acc, added new methods CalcImageStats 
 *  and PutImageLineByImage
 *
 *  Revision 1.71  2005/03/03 21:49:54  goldin
 *  Implement remaining revise_ & update_ methods
 *
 *  Revision 1.70  2005/03/03 16:30:32  rudahl
 *  added getTrailerOffset
 *
 *  Revision 1.69  2005/03/01 23:04:21  goldin
 *  Implement new create function for new output images; fix update functions
 *
 *  Revision 1.68  2005/02/23 20:36:59  rudahl
 *  revising grsproc1 for new Image usages
 *
 *  Revision 1.67  2005/02/23 18:21:31  rudahl
 *  new update, wrapper fns; moved from hdrstats to dhead
 *
 *  Revision 1.66  2005/02/22 20:11:33  rudahl
 *  new update, wrapper fns
 *
 *  Revision 1.65  2005/02/20 17:09:41  rudahl
 *  prelim create IMAGEHDR accessor fns
 *
 *  Revision 1.64  2005/02/16 00:50:06  goldin
 *  Changes to be able to compile under MingW
 *
 *  Revision 1.63  2005/02/15 20:26:16  rudahl
 *  now they compile, but maybe not correct
 *
 *  Revision 1.62  2005/02/03 16:07:19  rudahl
 *  initial support for multi-resolution formats
 *
 *  Revision 1.61  2005/01/30 03:45:21  rudahl
 *  using C fns for logTrace
 *
 *  Revision 1.60  2005/01/30 01:50:11  rudahl
 *  adapted for v 5.5
 *
 *  Revision 1.59  2004/12/30 13:17:37  rudahl
 *  removed some lengthy traces
 *
 *  Revision 1.58  2004/12/25 04:20:15  rudahl
 *  lint-ish fix
 *
 *  Revision 1.57  2004/12/23 11:48:32  rudahl
 *  lint-ish fix
 *
 *  Revision 1.56  2004/12/14 05:11:52  rudahl
 *  adapt for mingw
 *
 *  Revision 1.55  2002/09/23 13:37:36  rudahl
 *  removed PutImageLine trace
 *
 *  Revision 1.54  2002/09/15 21:50:40  rudahl
 *  mork around product level
 *
 *  Revision 1.53  2002/09/09 13:01:36  rudahl
 *  removed a dump
 *
 *  Revision 1.52  2002/09/06 23:51:40  rudahl
 *  removed unneeded hdr file
 *
 *  Revision 1.51  2002/09/05 00:46:00  rudahl
 *  work around keyed images
 *
 *  Revision 1.50  2002/08/28 16:10:46  rudahl
 *  improved dump, zero
 *
 *  Revision 1.49  2002/07/25 21:35:00  rudahl
 *  removed GetImageLine logging
 *
 *  Revision 1.48  2002/07/20 00:23:12  rudahl
 *  revs to IMAGE struct; add init(pImage)
 *
 *  Revision 1.47  2002/07/19 14:39:52  rudahl
 *  removed use of RES_FILEHIST
 *
 *  Revision 1.46  2002/07/13 00:36:38  rudahl
 *  continue to impl. Image class
 *
 *  Revision 1.45  2002/07/12 17:06:36  goldin
 *  Remove casts, rationalize incorrect use of size_t
 *
 *  Revision 1.44  2002/07/12 15:03:39  goldin
 *  Add casts to get rid of warnings
 *
 *  Revision 1.43  2002/07/12 00:11:47  rudahl
 *  implemented Image class
 *
 *  Revision 1.42  2002/07/05 23:37:34  goldin
 *  Continue work on keyed file functionality
 *
 *  Revision 1.41  2002/07/01 14:26:04  rudahl
 *  cleanup & rev'd tracing info
 *
 *  Revision 1.40  2002/06/25 00:32:37  rudahl
 *  got rid of vfile stuff in 16-bits; fixed KeyTable
 *
 *  Revision 1.39  2002/06/18 18:51:03  rudahl
 *  fixed problems with CalculateKeyTable
 *
 *  Revision 1.38  2002/06/17 14:54:20  goldin
 *  Move call to CalculateKeyTable
 *
 *  Revision 1.37  2002/06/14 23:55:19  goldin
 *  Added new function to compute key remapping table
 *
 *  Revision 1.36  2002/06/12 23:56:57  rudahl
 *  added some docs about current usage
 *  Cond. out some code which is used by toolkit, but needs to
 *  be updated. For the moment, keep it but don't compile it.
 *
 *  Revision 1.35  2002/05/21 20:46:48  rudahl
 *  workaround for Zortech fseek bug
 *
 *  Revision 1.34  2002/05/15 15:52:16  rudahl
 *  1. Moved/adapted from dragonu: CalcImageScale, ScaleImageLine
 *  2. Adapted GetImageLine for locked files, 16-bit files, use by
 *  small model
 *  3. cleanup
 *
 *  Revision 1.33  2002/05/06 18:45:15  rudahl
 *  cleanup
 *
 *  Revision 1.32  2002/05/03 01:35:23  rudahl
 *  got rid of multiple .obj's from img_acc
 *
 *  Revision 1.31  2002/04/30 01:14:29  rudahl
 *  fixed/improved a lot around GetImageFile
 *
 *  Revision 1.30  2002/04/24 02:25:21  rudahl
 *  all VF stuff now using vf-sim, not fgate
 *
 *  Revision 1.29  2002/04/09 21:31:33  rudahl
 *  adapt for long filenames
 *
 *  Revision 1.28  2002/02/08 20:27:59  rudahl
 *  fixed some tracing; cleanup
 *
 *  Revision 1.27  2002/02/06 14:26:26  rudahl
 *  revised to use D_MAXIMG instead of MAXIMG
 *
 *  Revision 1.26  2002/01/24 09:55:28  rudahl
 *  removed deadwood, printf's
 *
 *  Revision 1.25  2002/01/15 17:24:30  rudahl
 *  moved worklines etc from basemem to img_acc
 *
 *  Revision 1.24  2001/10/06 11:44:44  rudahl
 *  cleanup
 *
 *  Revision 1.23  2001/08/22 19:17:21  rudahl
 *  fixup for gcc
 *
 *  Revision 1.22  2001/08/22 18:22:27  rudahl
 *  fixup for gcc
 *
 *  Revision 1.21  2001/08/22 18:11:29  rudahl
 *  fixup for gcc
 *
 *  Revision 1.20  2001/08/22 18:08:13  rudahl
 *  fixup for gcc
 *
 *  Revision 1.19  2000/06/30 13:48:05  rudahl
 *  merged CloseImage & ImageFileClose
 *
 *  Revision 1.18  1999/10/04 14:25:24  rudahl
 *  added ipcos.h
 *
 *  Revision 1.17  1999/07/13 23:57:15  rudahl
 *  fixed RCS symbols
 *
 *  Revision 1.16  1999/07/05 14:10:09  rudahl
 *  further readjustments for 32-bit DLL
 *
 *  Revision 1.15  1999/05/09 19:02:30  rudahl
 *  cleanup
 *
 *  Revision 1.14  1999/05/04 01:04:49  rudahl
 *  fixed major bugs involving mem_free
 *
 *  Revision 1.13  1999/04/28 15:50:57  rudahl
 *  modified to support reinitialization of img memory in the DLL for each classification
 *
 *  Revision 1.12  1999/04/27 14:32:53  rudahl
 *  missed one debug msg
 *
 *  Revision 1.11  1999/04/27 14:28:56  rudahl
 *  conditionalize debug msg display
 *
 *  Revision 1.10  1999/04/23 16:22:00  rudahl
 *  Make it safe for win32 dll
 *
 *  Revision 1.9  1999/04/23 15:09:29  rudahl
 *  adapting for _WIN32 simulations of VFILES
 *
 *  Revision 1.8  1999/04/21 21:49:39  rudahl
 *  Creating MAX DLL
 *
 *  Revision 1.7  1999/04/21 14:28:38  rudahl
 *  centralizing IHEAD and IMAGE ops
 *
 *  Revision 1.6  1999/04/17 19:28:38  rudahl
 *  getting away from vfiles
 *
 *  Revision 1.5  1999/04/16 18:05:38  rudahl
 *  revising IHEAD and IMAGE functions
 *
 *  Revision 1.4  1999/04/11 17:31:45  rudahl
 *  converting away from VFiles
 *
 *  Revision 1.3  1999/03/31 01:54:15  rudahl
 *  moving image file loading from vfiles to disk files
 *
 *  Revision 1.2  1999/03/28 22:44:57  rudahl
 *  rev. get_imgline to use GetImageLine
 *
 *  Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *  first checkin of only SOME common dirs
 *
 * Revision 4.3  1998/02/08  06:32:06  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1998/02/08  06:32:06  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/12/12  13:19:16  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/12/23  13:16:36  tower
 * final for DRAGON 4.0G - adapt for MS
 * MSC v 6.
 * 
 * Revision 4.0  1993/07/12  10:20:18  tower
 * final for DRAGON Release 4.0
 * 
 * Revision 3.2  92/04/26  15:48:30  at
 * Release 3.05; converted to Zortech; multiple in-mem imgs; 640x512 size
 *
 *
 ***************************************************
 *  This file contains routines intended for use in the DRAGON
 *  image processing program. It is a reimplementation of imgacc.c,
 *  which was used in DRAGON up to and including release 3.05.
 *  This version has been created for use with the DRAGON
 *  Programmer's Toolkit, which does not have direct access to
 *  global data structures such as the imagelist array.
 *
 *  However, we expect to replace the existing imgacc functions
 *  with functions in this file for the next release of DRAGON.
 *
 *******  Old History - IMGACC.ASM, IMGACC.C *************
 *  Written by S.Goldin, 12/1/85
 *  Modified 1/26/86 to incorporate:
 *       (1) non-square image memory
 *	 (2) all passed line and pixel nums start at 0
 *	 (3) parameterize offset from BP for parameter passing
 *
 *  Translated from ASM to C on 8/17/87
 * mod 11/17/87 ktr  include dragon.h to set MAXPIX
 * mod 4/4/88 ktr    use MainImage params
 *			getpix, putpix used only by immanip, so conditioned out
 *     7/24/88 ktr   added SetupImage - initialize appropriate fields in
 *			image structure
 *
 *     7/7/89 seg    changed SetupImage, get_line, put_line
 *		      to treat image memory as virtual file
 *		   Moved fillimage to this file from dfiles
 *		   Added function - CloseImage to close img memory virt file
 *		   Note that old versions of functions are preserved
 *		      by conditional compilation based on LEVEL1
 *
 *     8/20/89 seg   Added STATS calls
 *
 *     9/04/89 seg   Added interim code in put_line, get_line to
 *		      deal with 24-bit image memory
 *     12/16/89 seg  Modified SetupImage to adjust the size of img memory based
 *		      on size of the img - either 640 x 400 or 512 x 512
 *		   If img mem already open but size doesn't match,
 *		      closes and reopens with correct size
 *	4/5/90 ktr   Added three new functions, which will eventually replace
 *			many of the others: ImageOp(),LineOp(),PixelOp()
 *			These fns are faster, require less local heap,
 *			and conveniently handle multiple images & multi-byte
 *			data.
 *		     Also added extensive documentation.
 *      5/5/90 seg   Fixed bugs in fillline, ImageOp
 *	5/19/90 ktr  Added ptr-to-image to fns ImageOp & LineOp
 *			 pass to 'operator'
 *	8/1/90 ktr   fixed closeimage to return 0 status if image-not-open
 *      4/9/91 seg   modified get_line,put_line,fillimage to take
 *		       explicit img index; created macros for old versions
 *	6/7/91 ktr & seg mod for Zortech small model, DRAGON 3.05
 *      8/18/91 seg  began modifications to simplify and generalize handling
 *		       of img memory size. Now now longer switch between
 *		       512 x 512 and 640 x 400 - use new vars
 *		       work_lines and work_pixels to determine max size.
 *
 *----- New History  IMG_ACC.C   -----------------------------------*
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *      7/12/92 seg  	created new module IMG_ACC.C for use with toolkit.
 *		   	reorganized, removed Level 1 stuff
 *		   	Note: get_imgline, put_imgline now return actual
 *			 number of bytes transferred, NOT line number.
 *			 May need to modify some DRAGON code due to this.
 *			 (see bandop-o.c, clstra-o.c - other modules use
 *			 these files but don't check status!!)
 *      7/26/92 seg  	Added: ImgMemFlag, SetImgMemFlag
 *	9/17/92 ktr  	added: every fn directly or indirectly checks that
 *			   InitImageAccess has been successfully called.
 *		     	changed to dtypes & dlimits
 *      2/14/93 seg  	Began integration into DRAGON 4.0.
 *      5/09/93 ktr	Adapted to compile for either 3.05 or 4.0.
 *      6/13/93 seg	Modified to treat image indices > 0 as
 *                       READ files - either buffer or stream mode.
 *      11/14/93 seg	Fixed toolkit functions (ifdef DR) which were
 *                       still treating img->header as NEAR pointer
 *	4/3/94 ktr   	put in errstat call if CGATE not loaded
 *		     	split into two object modules:
 *			  IMG_ACC1 always called by dtk_init even if no images
 *			  IMG_ACC2 calls HDRSTATS, floating point
 *		     	GetImagePtr is very suspicious!!!
 *	6/24/94 ktr  	began adapting to 16-bit data, calibrated z_ data
 *			  (so far, only in clear_img_hdr)
 *		     	cleaned up memory handling in UpdateHdrStats()
 *	7/8/94 ktr	mod get_imgline() to handle 16-bit little-endian
 *			pixels (scaled based on image struct imgmax, imgmin)
 *			Have not yet put in provision to remember scaling.
 *	7/19/94 ktr	minor changes for MSC v 8
 *	7/23/94 seg	Undid changes to get_imgline - this is not
 *                      where the scaling belongs since all img memory
 *                      is 8-bit. Check for use of old statistics
 *                      calc funs.
 *	8/25/94 ktr	further split obj module-IMG_ACC3 contains only
 *			fns not used directly by DRAGON (i.e. for toolkit)
 *			and all .obj's moved to dtkdrx.lib
 *			Added arg to InitImageAccess() selecting DRAGON vs DTK
 *    12/12/94 ktr	changed ftype in header to ftype[]
 *	12/23/95 ktr	adapt for MSC8 & Watcom 10
 * 5.0	5/17/96 ktr	changed FATAL to SERIOUS error
 *	8/25/97 ktr	histptr may now mean several things controlled by
 *			residentflag high nybble.
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *	2/8/98 ktr	added new fns GetImageLine(), PutImageLine(),
 *			 ImageLineTest() which work with memory and
 *			 therefore need no local buffers.
 *			get_imgline & put_imgline will be reimpl. in those terms.
 *	3/28/99 ktr	rev. SetupImage() to ALWAYS use V_STREAM for img > 0
 *			replaced get_imgline by GetImageLine which
 *			should be the same EXCEPT for error numbers returned.
 *			get_working_vals() removed 'cause not used by anyone
 *			working_images removed 'cause always 1
 *			made ImageLineTest() static
 *			Added CalcImageFileOffset().
 *	4/19/99 ktr	eliminated iIPix from GetImageLine, PutImageLine,
 *			which are rev'd to use vfread,write , not vfseek.
 *      4/21/99 seg     Provide a standalone branch of InitImageAccess
 *                        for use in DLL and other situations with no FGATE 
 *                      Remove GetHdrblkPtr function - added new macros
 *                          MAIN_HDR_PTR and TMP_HDR_PTR
 *	4/23/99 ktr	excluded put_imgline from _WIN32 build, to
 *			avoid need for vfseek. Use PutImageLine instead
 *      4/27/99 seg     Conditionalized display of debug msgs 
 *                      Changed my_work_lines and my_work_pixels to macros
 *                         defined in img_acc.h
 *                      This allows us to change the values from outside
 *                         after InitImageAccess is called
 *                      Added code to set the header pointer on
 *                         the image to NULL in CloseImage
 *	7/5/99 ktr	moved InitBasememforSA to CGATE
 *      6/25/00 ktr     merged functionality of CloseImage and ImageFileClose
 *                      added code to assure that IMAGE pFp and ivfp
 *                      are never simultaneously non-NULL
 * 5.4	1/15/2002 ktr	made this module the home of work_lines, work_pix
 *			(basemem version now obsolete & unused)
 *	4/9/02 ktr	adapted to long filenames by eliminating some buffers
 * 			and making others long in 32-bits
 *	5/3/2002 ktr	adapted to small (for dgraph) vs large/32-bit versions
 *			(see notes below).
 * 	12/13/2004 ktr	adapt for mingw
 * 5.5	2005-01-01 ktr	import from Dragon 5.4.4
 *	2005-3-6 ktr	renamed from img_acc.c to img_acc.cpp
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h, imageReader.h
 *	2005-7-2 ktr	fixed putImageLineP to handle 16-bit data
 * 	2005-7-20 ktr	added h_OriginalFileName and IMAGEDATA_SELECTOR
 *	2005-9-7 ktr	added getLabel and getLabelText
 *	2006-2-12 ktr	extensive changing of IMAGE * to const IMAGE *
 *			with a few code revisions to make this work
 * 5.11	2007-5-9 ktr	cleanup
 * 	2007-05-12 ktr	permit 32-bit signed data
 *	2008-06-14 ktr	added LinesBlob to trailer
 * 6.1	2010-12-04 ktr	changed data types of args to ScaleImageLine
 * 5.14 6.4	2014-04-02 ktr	move GetImageLineP, PutImageLineP to imagelinesIO.cpp
 *				used only by util, rose.a; Server uses imagemem fns
 *------------------------------------------------------------------*
 */

/****************************************************************
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#if defined __GCC__ || defined __MINGCC__
#include <sys/stat.h>
#include <unistd.h>
#else
#include <sys\stat.h>
#endif
#include <stddef.h>	/* for offsetof() */

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"

#include "ob.h"
#include "dhead.h"
#include "imageHdr.h"
#include "files.h"
#include "img.h"
#include "hdrstats.h"
#include "img_acc.h"

#include "dragonOb.h"
#include "logger.h"
#include "IpcWrap.h"
#include "dp.h"

/**/
void IMG_ACC_X() {}

int InitImageAccess(const int from_cgate)
	/*	The pointer corresponding to a particular image number
	 *	can then be accessed via the GetImagePtr function.
	 *	Returns 0 unless FGATE not loaded, then returns -1.
	 *	If this fn not called, or has error, 'imagelist'
	 *	remains at NULL
	 *
	 * 	This is called by dtk_init(img_h), also by
         *      open_cgate() in cgate-o.c (for DRAGON 4.0)
         *
         *      4/99 extended for standalone use in DLL
         *
	 */
    {
    logTrace(">img_acc::InitImageAccess (en) from_cgate=%s",
	     YESNO(from_cgate));
    return 0;
    }

	/**
	 *      setup the working dimensions and ProcessRect
	 *	for any image. Previously this returned an error
	 *      if it was called with any image index other than
	 *      main image. However, this is no longer true
	 *      as of 12/30/05.
	 *	Returns 0 
	 */
int SetupImage(const IMAGE * pImg) 
    {
    int status = 0;
    if ((pImg == NULL) || (pImg->pImageObj == NULL))
	return DERR_FN_ARG0;
    Image * pImage = pImg->pImageObj;
    int imgindex = pImg->thisone;
    if (pImage->m_iTrace)
	logTrace(">img_acc::SetupImage (en) "
	     "indindex=%d filename=%s Process.Xmax=%d type=%d",
	      imgindex,pImg->filename,
	      pImg->ProcessRect.Xmax,pImg->uImageFormat);
    if (imgindex == MAINIMG) /* this is a temp, r/w file */
        {   
	status = pImage->closeImageFile();
	}
    if ((pImg->pixels == 0) || (pImg->pixels > getWorkingPixels()))
        {
        pImage->image.pixels = getWorkingPixels();
	pImage->image.ProcessRect.Xmax = getWorkingPixels() - 1;
	}
    if ((pImg->lines == 0) || (pImg->lines > getWorkingLines()))
        {
        pImage->image.lines = getWorkingLines();
        pImage->image.ProcessRect.Ymax = getWorkingLines() - 1;
	}

    if (pImage->m_iTrace)
	logTrace(">img_acc::SetupImage (ex) "
		 "status=%d filename=%s Process.Xmax=%d type=%d",
		 status,pImg->filename,
		 pImg->ProcessRect.Xmax,pImg->uImageFormat);
    return status;
    }

/* Explicitly set the processing rectangle to something special.
 * This is needed in CUR to make sure that we don't try to read
 * more data than will fit in our buffer when the background image
 * is smaller than the data images.
 * @param pImage  Image whose rectangle we want to set.
 * @param xmin  minimum pixel value
 * @param xmax  maximum pixel value; if == 0 ignore xmin,xmax
 * @param ymin  minimum line value
 * @param ymax  maximum line value; if == 0 ignore ymin,ymax
 */
void SetImageProcessRect(const IMAGE* pImage,
			 uint xmin, uint xmax, uint ymin, uint ymax)
    {
    Image * pImg = pImage->pImageObj;
    if (xmax > 0)
        {
	pImg->image.ProcessRect.Xmin = xmin;
	pImg->image.ProcessRect.Xmax = xmax;
        }
    if (ymax > 0)
        {
	pImg->image.ProcessRect.Ymin = ymin;
	pImg->image.ProcessRect.Ymax = ymax;
	}
    }

              // how big a buffer do we need for GetI(mageLineP?
              // (This actually returns size for a full line of read data,
              // regardless of multiband and scaling considerations.)
size_t getLineBufferSize(const IMAGE  * pImg)
    {
    return (pImg != NULL) ? pImg->pImageObj->getLineBufferSize() : 0;
    }

	/*	New, 7/7/89
	 *	Close real image file and release its memory
	 *
	 *	@param pImage	ptr to IMAGE struct of image to be closed
	 *	Returns 0 if OK 
	 *      else
	 *		-54	file close error
	 */
int CloseImage(const IMAGE * pImage)
    {
      //    logTrace("img_acc::CloseImage pImage=%p obj=%p",
      //	     pImage,(pImage != NULL) ? pImage->pImageObj : NULL);
    return pImage->pImageObj->CloseImage();
    }

	/* copy an image line, scaling as we go.
	 * Source and destination may be the same 
	 *    (but dest. must be big enough)
	 * @param lpDest	buffer where data gets moved to
	 * @param lpSrc		buffer containing data
	 * @param uPix		number of pixels to move
	 * @param uBytesPP	size of pixel
	 * @param uBase		0, or offset to subtract from raw data value
	 * @param uFactor	1, or divisor of (raw data - uBase)
	 */
#if DRAGON_VER >= 6
void ScaleImageLine(byte * lpDest,const void * lpSrc,
		    const uint uPix, const uint uBytesPP,
		    const ushort uBase, const uint uFactor)
#else
void ScaleImageLine(byte * lpDest,const void * lpSrc,
		    const ushort uPix, const ushort uBytesPP,
		    const ushort uBase, const ushort uFactor)
#endif
    {
    if (uBytesPP > 1) /* if more than 8 bits/pix, scale data as we read it */
	{        
	const ushort * lpSrcW = (const ushort *)lpSrc;
	for (uint i = 0; i < uPix; i++)
	    {
	    lpDest[i] = ((*lpSrcW) - uBase) / uFactor;
	    lpSrcW++;
	    }
	}
    else if (lpDest != lpSrc)  /* just copy the data */
	memcpy(lpDest,lpSrc,uPix);
    }

#if defined __ZTC__ && ! defined __SMALL__ && defined NOMORE // only for U/CUR

/*	calc byte offset into file of specified image line,
	 *	return TRUE if OK and set *piStatus to 0
	 *		and *pulImageLine (if non-NULL) to the offset.
	 *	This fn maintains state: if the filename is non-NULL,
	 *	  the state is initialized from the supplied info
	 *	  and from analyzing the file header (GetImageHeader)
	 *	  copy entire resulting image structure to lpImage.
	 *	  In this case, if lpHdr non-NULL, copy header there.
	 *	Otherwise, the offset is calc'd from the internal state.
	 *	  and lpImage is ref'd but not altered	
	 *	If fn return FALSE, *piState is < 0 if true error,
	 *		-7 if no lpImage
	 *		or vals from GetImageHeader
	 *	or 0 if uLine is out of range.
	 * @param pczFilename	NULL, or name of file to read
	 * @param lpHdr		where to copy header
	 * @param uFT		type of file
	 * @param piStatus	where to save resulting status
	 * @param uLine		line number to seek
	 * @param lpImage	ptr to IMAGE of same file (must be non-NULL)
	 * @param pulImageLine	where to put results
	 * @return		TRUE if OK
	 */
BOOL CalcImageFileOffset(const char * pczFileName, IHEAD * lpHdr,
			 const IMGTYPE_T uFT, int * piStatus, 
			 uint uLine, IMAGE * lpImage,
			 ulong * pulImageLine)
    {
    BOOL bRetval = TRUE;
    *piStatus = 0;
    logTrace(">CalcImagefileOffset (en) file='%s' hdr=%p img# %d",
	pczFileName,lpHdr,lpImage->thisone);
    if (lpImage == NULL)
	{
	*piStatus = -7;
	bRetval = FALSE;
	}
    else if (pczFileName != NULL)
	{
	logTrace(">CalcImagefileOffset calling GetImageHeader");
	bRetval = GetImageHeader(pczFileName,uFT,piStatus,lpImage,
		NULL,lpHdr);
	/* the following does nothing except to set the internal variable.
	 * In particular, it does NOT call GetImageHeader() again */
	ReadHdrIfNecessary((bRetval) ? lpImage->thisone : -1,TRUE);
		// just set the internal variable
	}
    if (bRetval)		// now calc the offset
	{
	if (uLine >= (uint)lpImage->lines)
	    bRetval = FALSE;	// not a true error
	else if (pulImageLine != NULL) /* only for imagefileseekraw */
	    {
	    size_t uDataLineNo = (lpImage->puKeyTable == NULL) 
		           ? uLine : lpImage->puKeyTable[uLine];
	    *pulImageLine = lpImage->ulFileOffset
			 + lpImage->ulLinePitch * (ulong)uDataLineNo;
	    }
	}
    logTrace(">CalcImagefileOffset (ex) success=%s status=%d",
	  YESNO(bRetval),*piStatus);
    return bRetval;
    }
#endif

/**/
	/* Recalculate header statistics for image identified
	 * by 'pImg', and returns them in the 'pStats'
	 * structure which must be allocated and freed by the
	 * caller.
	 * User must set ftype in header to determine
	 * binning. If not set to 'C', assume regular img file.
	 * @param pImg    IMAGE to read
	 * @param pStats  Structure to hold stat calc work
	 * @return 	  0 if ok, negative for error.
	 */
int CalcImageStats(const IMAGE * pImg, IMGSTATS * pStats)
    {
#undef FN_NAME
#define FN_NAME "img::CalcImageStats"
    logTrace(FN_NAME " (en)");
    ushort ln;
    int status;

    if (pImg == NULL)
	return DERR_IMAGE_UNKNOWN;
    uint nlines = pImg->lines;
    uint npix = pImg->pixels;
    uint bufsize = pImg->pImageObj->getLineBufferSize(); //getLineBufferSize(pImg);
    uint bitsPP = pImg->pixbits;
    byte * databuf = (byte*) calloc(bufsize,1);
    if (databuf == NULL) /* not enough memory */
        {
	logTrace(FN_NAME " (ex) ERROR status=%d",DERR_MEM_ALLOC);
	return DERR_MEM_ALLOC;
	}
    logTrace("CalcImageStats: nlines %d, npix %d, bitsPP %d, bufsize %d",
	     nlines, npix, bitsPP, bufsize);
    InitLineCalc(nlines,npix,bitsPP,(bitsPP > 8)? 2 : 1,pStats);
    for (ln = 0; ln < nlines; ln++)
	{
	status = GetImageLineP(databuf, ln, bufsize, pImg,FALSE,NULL); /* ~~~ for 16-bit*/
	if (status < 0)
	    {
	    free(databuf);
	    logTrace(FN_NAME " (ex) ERROR %d for line %d",status, ln);
	    return status;
	    }
	NextLineCalc(databuf,NULL,0,pStats);
	}
    FinishLineCalc(pStats);
    free(databuf);
    logTrace(FN_NAME " (ex)");
    return 0;
    }

/*   Initialize the passed image according to 'val':
 *   This is used by boxcar. The Image is assumed
 *   to be initialized to be writable. This function
 *   actually writes data to the image.
 *   @param pImage	target image; always MAINIMG
 *   @return		0 or error from PutImageLineP
 */
int fillImage(const IMAGE * pImage, const byte uVal)
    {
    byte* pOutbuf = NULL;
    int iRetval = 0;
    int ln = 0;
    logTrace("img_acc::fillImage (en) value is %d\n", uVal);
    if (pImage == NULL) 
	return DERR_IMAGE_UNINIT; /* -60 */
    if (pImage->pImageObj->getStatus() <= 0)
	return DERR_IMAGE_UNINIT; /* -60 */

    const IMAGEHDR * pHeader = getIMAGEHDR(pImage);
    int nLines = pImage->lines;
    int nPix = pImage->pixels;
    if (pHeader->bits_per_pix > 8)
	return DERR_IMAGE_CONFLICT; // can't do this with 16 bit image
			    //~~~ why not? fix for 5.12 
    logTrace("img_acc::fillImage, nLines is %d and nPix is %d",
	     nLines, nPix);
    pOutbuf = (byte*) calloc(nPix,1);
    if (pOutbuf == NULL)
	return DERR_MEM_ALLOC;
    memset(pOutbuf,uVal,nPix);
    for (ln = 0; (ln < nLines) && (iRetval >= 0); ln++)
        {
	iRetval = PutImageLineP(pOutbuf,ln,pImage); 
	if (iRetval < 0)
	    break;
        }
    free(pOutbuf);
    logTrace("img_acc::fillImage (ex) returning %d", iRetval);
    return iRetval;
    }

/**/

/*-------------------------------------------------------------
 *	    long PixOp(IMAGE * image,line,pix,long (* p_operator)(),pixsize)
 *		applies 'p_operator' to 'image' line number 'line', pixel 'pix'
 *		'deltax' pixels beginning with pixel 'x'
 *-------------------------------------------------------------*/

/************************************************************************
 *
 * C language wrapper fns for img.cpp
 *
 ************************************************************************/

/* create a new Image (for use by C pgms) and return a ptr to its IMAGE struct
 * @param iDebug	debug level if > than set by OB::OB
 * @param iTrace	trace level if > than set by OB::OB
 */
 IMAGE * newImage(int iDebug,int iTrace)
     {
     Image * img = new Image(iDebug,iTrace);
     return (img == NULL) ? NULL : &(img->image);
     }

/* Open an image and initialize using the information
 * in an existing file. Optionally set this image as
 * being capable of modification. 
 * Basically this is just a wrapper around Image::open.
 * @param pImg         IMAGE structure identifying an existing image
 * @param pczFilename  Filename for image (with path)
 * @param bModifiable  If true, this image can be modified. Else it is
 *                     read only.
 * @return 0 if ok, else negative error value returned from Image::open.
 */
int openImage(const IMAGE * pImg, const char* pczFilename,
	      BOOL bModifiable)
    {
    if ((pImg == NULL) || (pImg->pImageObj == NULL))
	return DERR_IMAGE_UNINIT;
    if (pImg->pImageObj->m_iDebug)
	fprintf(stderr,
		"img_acc::openImage file=%s pImg No %d=%p Image=%p\n",
		pczFilename,pImg->thisone,pImg,pImg->pImageObj);
    Image * pImage = pImg->pImageObj;
    int iStatus = pImage->open(pczFilename,bModifiable);
    return (iStatus < 0) ? iStatus : 0; 
    }

/* set up an Image for output based on an existing image
 * This works by: 1. Create a new ImageHdr
 *                2. Copy an existing ImageHdr
 *		  3. Allow the selected writer subclass to 
 *                   modify the new ImageHdr
 * 		  4. Init 'this' from the new ImageHdr.
 * If the image geometry need to be cahsed, 
 *   call revise_geom() BEFORE calling write().
 * If the image data differes from pSrcImage,
 *   call update() AFTER writing the image data, 
 *   then call rewriteImageHeader().
 * @param pImg		writable IMAGE
 * @param pczFilename	full, long path of file
 * @param bOverwrite	TRUE => silently delete file if exists
 * @param bReReadable	if TRUE, data can be re-read after writing
 * @param uImgType	type of image file
 * @param pSrcImage	Image to copy
 * @param pczFtype      Dragon file type - "I", "C" or "L",
 *			or NULL to keep type from copy
 * @return		0 if OK
 *			-57 => already exists and bOverwrite=FALSE
 *			-90 to -97 - invalid argument
 */
int createImageCopy(const IMAGE * pImg,
		    const char * pczFilename, BOOL bOverwrite,
		    BOOL bReReadable, IMGTYPE_T uImgType,
		    const IMAGE * pSrcImg,
		    const char* pczFtype)
    {
    logTrace("img_acc::createImageCopy (en) pImg=%x, pczFilename=%s, pSrcImg is %x", pImg, pczFilename, pSrcImg);
    Image * pCopy = pImg->pImageObj;
    Image * pSrc = pSrcImg->pImageObj;
    int iRetval = pCopy->create(pczFilename,bOverwrite,bReReadable,uImgType,
			pSrc,pczFtype);
    logTrace("img_acc::createImageCopy (ex)");
    return iRetval;
    }

/* Setup a new output image, specifying critical values
 * This is a wrapper for another Image::create variant
 * All values must be specified.
 * @param pImg		writable IMAGE
 * @param pczFilename	filename with path
 * @param bOverwrite	FALSE = don't overwrite existing file
 * @param bReReadable	TRUE = can read as well as write
 * @param uImgType	type of file to write
 * @param uNumLines	number of lines
 * @param uNumPixels	number of pixels per line
 * @param uBitsPerPix   number of bits per pixel
 * @param uNumBands	number of bands 
 * @param uNumResolutions number of pyramids/resolution tiers
 *                        if 0 default based on type
 * @param pczFtype      Dragon file type - "I", "C" or "L"
 * @param pczOriginalName NULL or name of source file for conversions
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int createImageNew(const IMAGE * pImg,
		   const char * pczFilename, BOOL bOverwrite,
		   BOOL bReReadable, IMGTYPE_T uImgType,
		   ushort uNumLines, ushort uNumPixels,
		   ushort uBitsPerPix, ushort uNumBands,
		   ushort uNumResolutions, const char* pczFtype,
		   const char * pczOriginalName)
    {
    Image * pSrc = pImg->pImageObj;
    // fprintf(stderr,"createImageNew - pSrc is %p\n", pSrc);
    return pSrc->create(pczFilename,bOverwrite,bReReadable,
			uImgType,uNumLines,uNumPixels,
			uBitsPerPix,uNumBands,uNumResolutions,
			pczFtype,pczOriginalName);
    }

/* Revise critical values for an existing writable image.
 * This is a wrapper for img::revise_geom.
 * Only the params with non-default vals will be changed.
 * This must be invoked BEFORE writing the header
 * @param pImg		writable IMAGE
 * @param pczFilename	NULL => do not change
 * @param bOverwrite	FALSE => do not change
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
int reviseImageGeometry(const IMAGE * pImg,
			const char * pczFilename, BOOL bOverwrite,
			BOOL bReReadable, IMGTYPE_T uImgType,
			ushort uNumLines, ushort uNumPixels,
			ushort uBitsPerPix, ushort uNumBands,
			ushort uNumResolutions)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->revise_geom(pczFilename,bOverwrite,bReReadable,
			     uImgType,uNumLines,uNumPixels,
			     uBitsPerPix,uNumBands,uNumResolutions);
    }



/* change scaling information for an existing image.
 * Only the params with non-default vals will be changed.
 * This may be invoked after writing the header and the image data
 * @param pImg		writable IMAGE
 * @param dScaleFactor	factor, value for BINARY or OPTIMAL scaling
 * @param ScaleOffset	offset, value only if OPTIMAL scaling
 * @param pczScalingType 'B', 'O', 'N'o change, or \0 for none
 *   ( the following give calibration meaning to pixel values )
 *   ( if dZ_scale == 0, none of these are set by this fn)
 *   ( calibrated value = (pixel value * dz_Scale) + dZ_offset)
 * @param dZ_scale	multiplicative factor
 * @param dZ_offset	additive factor 
 * @param pcZ_unit 	name of pixel calibration units
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int updateImageScaling(const IMAGE * pImg,double dScaleFactor,
		       double dScaleOffset,
		       const char * pczScalingType,
		       double dZ_scale,
		       double dZ_offset,
		       const char * pcZ_unit)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->update_scaling(dScaleFactor,dScaleOffset,
		       pczScalingType,
		       dZ_scale,dZ_offset,pcZ_unit);
    }

/* change text information (except classnames, unitnames) 
 * for an existing image.
 * Only the params with non-NULL vals will be changed.
 * This may be invoked after writing the header and the image data
 * @param pImg		writable IMAGE
 * @param (all of them)	NULL or new value (possibly "")
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 to -97 - invalid argument
 */
int updateImageText(const IMAGE * pImg,
		    const char * pczTitle,
		    const char * pczId,
		    const char * pczComment,
		    const char * pczSource,
		    const char * pczScene,
		    const char * pczSubscene,
		    const char * pczBand,
		    const char * pczColorfileName,
		    const char * pczFtype)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->update_text(pczTitle,pczId,pczComment,pczSource,
			     pczScene,pczSubscene,pczBand,pczColorfileName,
			     pczFtype);
    }

/* change stats and histogram information for an existing image.
 * This may be invoked after writing the header and the image data
 * @param pImgStats	stats for image
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 - invalid argument
 */
int updateImageStats(const IMAGE * pImg,const IMGSTATS * pImgStats)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->update_stats(pImgStats);
    }

/* change georeferencing information information for an existing image.
 * This may be invoked after writing the header and the image data
 *
 * NOTE: ref_x, ref_y, pczProjection, pczUnitname 
 *	 may be NULL to indicate no change
 *	 but other args MUST be supplied.
 *
 * @param pImg     Pointer to IMAGE to be updated
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
 *			-66 => state conflict
 *			-90 - invalid argument
 */
int updateImageGeoref(const IMAGE * pImg, 
		      int img_x, int img_y, 
		      const MapCoord * ref_x, const MapCoord * ref_y,
		      double xcell_size, double ycell_size,
		      const char* pczProjection, const char* pczUnitname,
		      const char * pczDateTime,const char * pczUTMZone,
		      int iRegistered)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->update_georef(img_x, img_y, ref_x, ref_y,
			       xcell_size, ycell_size, pczProjection,
			       pczUnitname,pczDateTime,pczUTMZone,
			       iRegistered);
    }

	/* copy blob info from an existing image.
	 * @param pImg 	        Image to be updated
         *                      Source existing image is already
         *                         known because it was used to initialize
	 *                         pImg.
	 * @return		0 if OK
	 *			-66 => state conflict
	 */
#if DRAGON_VER >= 6
int copy_blob(const IMAGE * pImg)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->copy_blob();
    }
#endif

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
int updateImageLabels(const IMAGE * pImg,
		      int iNumLabels,
		      size_t uArrayCount,
		      const LABEL_INFO * pLabels)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->update_labels(iNumLabels,uArrayCount,pLabels);
    }

#ifdef NOTNEEDED
/* change class table information for an existing image.
 * This may be invoked after writing the header and the image data
 * @param uArrayCount	number of classes
 * @return		0 if OK
 *			-66 => state conflict
 *			-90 - invalid argument
 */
int updateImageClassTable(IMAGE * pImg,ushort uNumclasses)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->update_classTable(uNumclasses);
    }
#endif

/* write the image header
 * @return 	0 if OK
 *		else error number - see img.h
 */
int writeImageHeader(const IMAGE * pImg)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->writeHeader();
    }

/*	rewrite image header and write trailer
 *	On exit, file is closed
 *	This CAN be used for modifiable input image
 *	@param pImg		image to be written
 *	@param uDataCheck	checksum of the image data rows
 *				for trailer (0 => not valid, ignore)
 *	@param bWriteTrailer	FALSE => don't write trailer yet
 *	Return 0 if OK
 *	Error values are:
 *		-16 => op not needed (not an error)
 *		-50 - -55 file IO errors
 *		-65 => no name supplied
 *		-66 => image state conflict
 *		-69 => no header writer found
 */
int rewriteImageHeader(const IMAGE * pImg,UINT32 uDataCheck, 
		       BOOL bWriteTrailer)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->rewriteHeader(uDataCheck,bWriteTrailer);
    }

/* write the image trailer
 * @param uDataCheck	checksum of image data
 * @return 	0 if OK
 *		else error number - see img.h
 */
int writeImageTrailer(IMAGE * pImg,UINT32 uDataCheck)
    {
    Image * pSrc = pImg->pImageObj;
    return pSrc->writeTrailer(uDataCheck);
    }

      /* Sets image structure to empty, default values.
       */
void zeroImgInfo(IMAGE * pImg)
    {
    Image * pImage = (pImg != NULL) ? pImg->pImageObj : NULL;
    if (pImage != NULL)
        {
	pImage->zero(FALSE,-1);
	}
    }

/**
 * This is a convenience function that calls the statistics
 * calculation on the passed image and then updates the
 * internal image header statistics information.
 * It does NOT rewrite the header, unlike the previous
 * function with this name.
 * Unlike the function in imstat-o, this function does not
 * deal with things like stretching or masking.
 * ~~~ DO NOT CONFUSE THIS WITH CalcandSetImageStats IN imstat-o.c
 * (although they essentially do the same thing)
 * @param pImage  Pointer to IMAGE for which we want to calc stats
 * @return 0 unless error occurs,then negative value.
 */
int CalcAndSetImageStats(const IMAGE * pImage)
    {
    int iRetval = 0;
    IMGSTATS * pStats = ImgStatsAlloc();
    if (pStats == NULL)
	return DERR_MEM_ALLOC;
    iRetval = CalcImageStats(pImage, pStats);
    if (iRetval == 0)
       {
       iRetval = updateImageStats(pImage, pStats);
       }
    ImgStatsFree(pStats);
    return iRetval;
    }

	// Get a pointer to a label
	// @param pImage  	Pointer to IMAGE
	// @param uLabelNo	index of label
	// @return 		pointer or NULL if uLabelNo out of range
const LABEL_INFO * getLabel(const IMAGE * pImage, size_t uLabelNo)
    {
    const LABEL_INFO * pRetval = NULL;
    if (pImage != NULL)
	{
	const ImageHdr * pHdr = pImage->pImageObj->getImageHeader();
	pRetval = pHdr->getLabel(uLabelNo);
	}
    return pRetval;
    }

	// Get label text
	// @param pImage  	Pointer to IMAGE
	// @param uLabelNo	index of label
	// @param pczUTF8Buffer	buffer to place text
	// @param uBufLen	size of buffer
	// @return 		-91 (DERR_FN_ARG1) if uLabelNo out of range
	//			else label color index >= 0
int getLabelText(const IMAGE * pImage, size_t uLabelNo, 
		 char * pczUTF8Buffer, size_t uBufLen)
    {
    int iRetval = DERR_FN_ARG1;
    if (pImage != NULL)
	{
	const ImageHdr * pHdr = pImage->pImageObj->getImageHeader();
	iRetval = pHdr->getLabel(uLabelNo,pczUTF8Buffer,uBufLen);
	}
    return iRetval;
    }

	/* get size limits for MAINIMG.
	 * For getWorkingBits, this may depend on the operation
	 * @param pczOp		3-letter operation code, or "" or NULL
	 *			if "" or NULL return lowest value
	 */
ushort getWorkingBits(const char * pczOp) 
    {return Image::getWorkingBits(pczOp); }
#if defined GET_WORKING_LINES
ushort getWorkingLines() { return GET_WORKING_LINES; }
#endif
#if defined GET_WORKING_PIXELS
ushort getWorkingPixels() 
    {
    ushort uRet = GET_WORKING_PIXELS;
    logTrace("img_acc::getWorkingPixels %d",uRet); 
    return GET_WORKING_PIXELS; 
    }
#endif

#if defined MOVEDTOSERVER || DRAGON_VER <= 5
const char * getWorkingImageFile() { return Image::getWorkingImageFile(); }
#endif // #if defined MOVEDTOSERVER || DRAGON_VER <= 5

/* get read-only pointer to hdrInfo */
/* GetImageHeaderInfo() is deprecated name */
const IMAGEHDR * GetImageHeaderInfo(const IMAGE * pImage) 
    { return getIMAGEHDR(pImage); }

const IMAGEHDR * getIMAGEHDR(const IMAGE * pImage)
    {
    Image * pImg = (pImage == NULL) ? NULL : pImage->pImageObj;
    return (pImg != NULL) ? pImg->getIMAGEHDR() : NULL;
    }

void dumpImage(const IMAGE * pImage,const char * czTitle)
    {
    Image * pImg = (pImage == NULL) ? NULL : pImage->pImageObj;
    logTrace((pImg != NULL) ? pImg->dump(1, czTitle) 
	     : "Image not initialized");
    }

	/* create an English text string listing the values in the
	 * the <b>IMAGEHDR</b> structure. (see <b>dhead.h</b>)
	 * dump the image header at detail level 0
	 * @param pImg		pointer to an IMAGE
	 * @param pczTitle	title to be prefixed to the dump
	 * @param bPrint	TRUE => print output else send to logtrace
	 * @param uDetailLevel	how much detail to include
	 * @return		static string
	 */
void dumpImageHeader(const IMAGE * pImage,const char * czTitle, 
		     BOOL bPrint,uint uDetailLevel)
    {
    Image * pImg = (pImage == NULL) ? NULL : pImage->pImageObj;
    if (bPrint)
	printf(((pImg != NULL) && (pImg->getImageHeader() != NULL))
	       ? pImg->getImageHeader()->dump(uDetailLevel, czTitle) 
	       : "Image not initialized\n");
    else
	logTrace (((pImg != NULL)  && (pImg->getImageHeader() != NULL))
		  ? pImg->getImageHeader()->dump(uDetailLevel, czTitle) 
		  : "Image not initialized");
    }

/* get the bitpattern (see valid_image())
 * for current Image.
 * Return value of Image.iStatus, except:
 *    return -60 if pImage is NULL
 *    return m_iErrno if other errors
 */
int GetImageStatus(const IMAGE * pImage)
    {
    Image * pImg = (pImage == NULL) ? NULL : pImage->pImageObj;
    return (pImg != NULL) ? pImg->getStatus() : DERR_IMAGE_UNINIT; /* -60 */
    }

   /* Given a Dragon header structure, calculate the
    * minimum and maximum extent in geographic coordinates
    * that is represented by the image.
    * @param pHdr  Pointer to OpenDragon header structure.
    * @param pMinExtent Pointer for returning minimum X and Y value
    * @param pMaxExtent Pointer for returning maximum X and Y value
    * Note that the min Y could be at the lower left rather
    * than the upper left, depending on the coordinate system.
    * @return TRUE if coordinate system flipped (Y cell size negative)
    *         else FALSE;
    */
BOOL calculateHeaderExtent(const IMAGEHDR * pHdr, 
			   VERTEX* pMinExtent, VERTEX* pMaxExtent)
    {
    BOOL bFlipped = (pHdr->ycell_size < 0);
    double temp = 0;
    pMinExtent->x = pHdr->ref_x.v0 - (pHdr->img_x * pHdr->xcell_size);
    pMaxExtent->x = pMinExtent->x + pHdr->size[1]* pHdr->xcell_size;
    pMinExtent->y = pHdr->ref_y.v0 - (pHdr->img_y * pHdr->ycell_size);
    pMaxExtent->y = pMinExtent->y + pHdr->size[0]* pHdr->ycell_size;
    if (bFlipped)
        {
        temp = pMinExtent->y;
	pMinExtent->y = pMaxExtent->y;
	pMaxExtent->y = temp;
	}
    return bFlipped;
    }

/* Use a source image to copy the meta file information to a target
 * image. This will effectively add the target image to the same
 * IGC group as the source.
 * @param pTargetImage  Image to update
 * @param pSrcImage     Image to use to get metafile information.
 * @return 0 if successful otherwise negative error code.
 */
int updateImageMetaInfo(const IMAGE* pTargetImage, const IMAGE* pSrcImage)
    {
    const IMAGEHDR * pSrcHdr = getIMAGEHDR(pSrcImage);
    return pTargetImage->pImageObj->update_metainfo(pSrcHdr->pczMetafile, pSrcHdr->pczGUID);
    }

/* Clear out igc meta file and GUID information from image
 * header, and rewrite the header. This should be called whenever
 * the user does something that will destroy geographical congruence.
 * @param pImage  Pointer to IMAGE that should be cleared.
 * @return 0 or negative for error.
 */
int clearImageMetaInfo(const IMAGE* pImage)
    {
    pImage->pImageObj->update_metainfo("","");
    return pImage->pImageObj->rewriteHeader(0,TRUE);
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
int updateImageOriginal(const IMAGE * pImage,
			uint uOriginalBandCount,
			uint uOriginalBandNumber,
			const char * pczOriginalFileName)
    {
    return pImage->pImageObj->update_original(uOriginalBandCount,
					      uOriginalBandNumber,
					      pczOriginalFileName);
    }

/* Compare the georeferencing information in two images
 * to see if they are the same or not. Returns TRUE if
 * they are the same, FALSE if different.
 * @param pImage1 First image to compare - assumed to be open and initialized
 * @param pImage2 Second image to compare - ditto
 * @return TRUE if the georeferencing is the same for the two images.
 */
BOOL compareImageGeoref(const IMAGE* pImage1, const IMAGE* pImage2)
    {
    double maxDelta = 0.01;
    BOOL bSame = TRUE;
    const IMAGEHDR * pHdr1 = getIMAGEHDR(pImage1);
    const IMAGEHDR * pHdr2 = getIMAGEHDR(pImage2);
    if ((pHdr1->img_x != pHdr2->img_x) ||
	    (pHdr1->img_y != pHdr2->img_y) ||
	    (fabs(pHdr1->ref_x.v0 - pHdr2->ref_x.v0) > maxDelta) ||
	    (fabs(pHdr1->ref_y.v0 != pHdr2->ref_y.v0) > maxDelta) ||
	    (pHdr1->xcell_size != pHdr2->xcell_size) ||
	    (pHdr1->ycell_size != pHdr2->ycell_size))
	bSame = FALSE;
   /* for now we don't check the units 
      because there's no spelling enforcement*/
    return bSame;
    }

/* Test to see if an image is georeferenced. We do this by
 * looking at the map coordinates of the image X and Y pt.
 * @param pImage  Image to check
 * @return TRUE if georeferenced  else FALSE
 */
BOOL isGeoreferenced(const IMAGE* pImage)
    {
    const IMAGEHDR * pHdr = getIMAGEHDR(pImage);
    if ((pHdr->ref_x.v0 != 0) || (pHdr->ref_y.v0 != 0))
	return TRUE;
    return FALSE;
    }

#if DRAGON_VER >= 6
	    /* COPY the specified blob */
int setLinesBlob(const IMAGE * pImg,const byte * pBlob,size_t uBlobSize)
	{ return pImg->pImageObj->setLinesBlob(pBlob,uBlobSize); } 
	    /* if non-NULL, ptr to blob of vector data */
byte * getLinesBlob(const IMAGE * pImg) 
        { return pImg->pImageObj->getLinesBlob(); } 
	    /* number of bytes in LinesBlob */
size_t getLinesBlobLen(const IMAGE * pImg) 
        { return pImg->pImageObj->getLinesBlobLen(); } 
#endif

#ifdef TEST

/* Use wrapper functions to create
 * and write a brand new image.
 */
static int writeNewImage()
    {
    IMGSTATS * pStats = NULL;
    int iRetval = 0;
    int j = 0;
    char labelBuf[32];
    char * fileName = "./imgacctst.img";
    byte outbuffer[400];
    LABEL_INFO labels[10];
    Image * outImage = new Image(1,0);
    IMAGE * pImg = &outImage->image;
    printf("Before createImageNew -outImage is %p and pImg is %p\n",
             outImage, pImg);
    iRetval = createImageNew(pImg,fileName,
			     TRUE,TRUE,IT_DRAGON,
			     200,400,8,1,0,"I","img_acc unit test function");
    if (iRetval != 0)
        return iRetval;
    if (iRetval == 0)
       {
       printf("Try updateImageText before writing header\n");
       iRetval = updateImageText(pImg,NULL,NULL,"BEFORE HEADER WRITE",
				 NULL,NULL, NULL,NULL,NULL,NULL);
       printf("UpdateImageText returned %d\n", iRetval);
       }

    printf("About to writeImageHeader\n");
    iRetval = writeImageHeader(pImg);
    if (iRetval != 0)
        {
	printf("writeImageHeader returned %d\n", iRetval);
        return iRetval;
	}
    /* write data to the image */
    for (j = 0; j < 200; j++)
        {
	memset(outbuffer,(byte)(j),400);
	//printf("About to write line %d\n", j);
	iRetval = PutImageLineP(outbuffer, j, pImg);
	if (iRetval != 400)
	    {
	    break;
	    }
	else 
	    {
	    iRetval = 0; // reset
	    }
	}
    if (iRetval != 0)
	return iRetval;
    /* Ok, let's try to calculate the statistics */
    printf("Before ImageStatsAlloc\n");
    pStats = ImgStatsAlloc();
    if (pStats == NULL)
	return DERR_MEM_ALLOC;

    printf("About to call CalcImageStats\n");
    iRetval = CalcImageStats(pImg, pStats);
    if (iRetval == 0)
       {
       printf("About to updateImageStats\n");
       iRetval = updateImageStats(pImg, pStats);
       }
    printf("Mean image value is %d, min is %d, max is %d, variance is %f\n",
	   pStats->m_ihImgmean, pStats->m_ihImgmin, 
	   pStats->m_ihImgmax, pStats->m_dhImgvar);
    ImgStatsFree(pStats);

    /* Test setting some text strings */
    if (iRetval == 0)
       {
       printf("About to updateImageText\n");
       iRetval = updateImageText(pImg,NULL,NULL,"Test comment field",
				 "TST","Test scene", NULL,NULL,"DEFCCF.CLF",NULL);
       printf("UpdateImageText returned %d\n", iRetval);
       }

    for (j = 0; j < 9; j++)
        {
	labels[j].uValue = (ushort) j;
	labels[j].uColorNdx = 0;
	memset(labels[j].czI18NKey,0,8);
	sprintf(labelBuf,"Label number %d", j);
	labels[j].pczText = strdup(labelBuf);
	if (labels[j].pczText == NULL)
	    {
	    printf("strdup failed for label %d\n", j);
	    iRetval = -1;
	    }
        }
    if (iRetval == 0)
        {
	printf("About to updateImageLabels\n");
	iRetval = updateImageLabels(pImg,9,9,labels);
	}

    if (iRetval == 0)
        {
	printf("About to rewriteImageHeader\n");
	iRetval = rewriteImageHeader(pImg,0,TRUE);
	if (iRetval == DERR_NOT_NEEDED)
	    {
	    printf("No header changes to write!\n");
	    iRetval = 0;
	    }
	}
    pImg->pImageObj->CloseImage();
    return iRetval;
    }

/**
 * Read an existing image and update some of its information.
 */
static int updateOldImage(char* czFilename)
    {
    int iRetval = 0;
    //int j = 0;
    //char labelBuf[32];
    MapCoord ref_x;
    MapCoord ref_y;
    ref_x.v0 = 1000000;
    ref_y.v0 = 2000000;
    Image * inImage = new Image(1,0);
    IMAGE * pImg = &inImage->image;
    printf("About to open image %s\n", czFilename);
    iRetval = openImage(pImg,czFilename,TRUE);
    printf("openImage returned %d\n",iRetval);

    if (iRetval == 0)
        {
	printf("About to update georeferencing info\n");
	iRetval = updateImageGeoref(pImg,10,20,&ref_x,&ref_y,
				    15.0, 15.0,"UNKNOWN","Meters",
				    NULL,NULL,FALSE);
        }
    if (iRetval == 0)
        {
	printf("About to update text information\n");
        iRetval = updateImageText(pImg,"TEST IMAGE",NULL,
				  "Playing around in img_acc",
				  "TEST", "Cannot know", "full",
				  "P","DEFGRA.CLF","I");
        }
    if (iRetval == 0)
        {
	printf("About to update text information\n");
	iRetval = updateImageScaling(pImg,0.50, 1000.0,
				     "O", 80.0, 1400.0, "degrees");
        }

    if (iRetval == 0)
        {
	iRetval = rewriteImageHeader(pImg,0,TRUE);
	if (iRetval == DERR_NOT_NEEDED)
	    {
	    printf("No header changes to write!\n");
	    iRetval = 0;
	    }
	}
    pImg->pImageObj->CloseImage();
    return iRetval;
    }

/* Use wrapper functions to create
 * and write a simple image with simple stats.
 */
static int writeStatTestImage()
    {
    IMGSTATS * pStats = NULL;
    int iRetval = 0;
    int j = 0;
    char * fileName = "./stattest.img";
    byte outbuffer[100];
    Image * outImage = new Image(0,0);
    IMAGE * pImg = &outImage->image;
    printf("Before createImageNew -outImage is %p and pImg is %p\n",
             outImage, pImg);
    iRetval = createImageNew(pImg,fileName,
			     TRUE,TRUE,IT_DRAGON,
			     100,100,8,1,0,"I","img_acc unit test function");
    if (iRetval != 0)
        return iRetval;
    printf("About to writeImageHeader\n");
    iRetval = writeImageHeader(pImg);
    if (iRetval != 0)
        {
	printf("writeImageHeader returned %d\n", iRetval);
        return iRetval;
	}
    /* write data to the image */
    for (j = 0; j < 100; j++)
        {
        int val = 0;
        if (j > 49)
           val = 255;    
	memset(outbuffer,(byte)(val),100);
	//printf("About to write line %d\n", j);
	iRetval = PutImageLineP(outbuffer, j, pImg);
	if (iRetval != 100)
	    {
	    break;
	    }
	else 
	    {
	    iRetval = 0; // reset
	    }
	}
    if (iRetval != 0)
	return iRetval;
    /* Ok, let's try to calculate the statistics */
    printf("Before ImageStatsAlloc\n");
    pStats = ImgStatsAlloc();
    if (pStats == NULL)
	return DERR_MEM_ALLOC;

    printf("About to call CalcImageStats\n");
    iRetval = CalcImageStats(pImg, pStats);
    if (iRetval == 0)
       {
       printf("About to updateImageStats\n");
       iRetval = updateImageStats(pImg, pStats);
       }
    printf("Mean image value is %d, min is %d, max is %d, variance is %f, sd is %f\n",
	   pStats->m_ihImgmean, pStats->m_ihImgmin, pStats->m_ihImgmax, 
	   pStats->m_dhImgvar, pStats->m_dhImgsd);
    ImgStatsFree(pStats);

    if (iRetval == 0)
        {
	printf("About to rewriteImageHeader\n");
	iRetval = rewriteImageHeader(pImg,0,TRUE);
	if (iRetval == DERR_NOT_NEEDED)
	    {
	    iRetval = 0;
	    }
	}
    pImg->pImageObj->CloseImage();
    return iRetval;
    }


int main(int argc, char** argv)
    {
    int option = 0;
    int iRetval = 0;
    char inpLine[128];
    char czFilename[128];
    fprintf(stdout,"IMG_ACC Test Driver\n");
    fprintf(stdout,"   1 - Test reading/updating of image\n");
    fprintf(stdout,"   2 - Test writing of image\n");
    fprintf(stdout,"   3 - Test image copy\n");
    fprintf(stdout,"   4 - Create stat test image\n");
    fprintf(stdout,"Enter option: ");
    fgets(inpLine,128,stdin);
    sscanf(inpLine,"%d",&option);
    printf("=========================================\n");
    switch (option)
       {
       case 1:
	   fprintf(stdout,"Enter image file name with path: ");
	   fgets(inpLine,128, stdin);
	   sscanf(inpLine,"%s",czFilename);
	   iRetval = updateOldImage(czFilename);
	   break;
       case 2:
	   iRetval = writeNewImage();
	   if (iRetval != 0)
	       fprintf(stderr,"Error %d trying to write new image\n", iRetval);
	   break;
       case 3:
	   fprintf(stderr, "NOT IMPLEMENTED\n");
	   break;
       case 4:
	   iRetval = writeStatTestImage();
	   break;
       default:
	   fprintf(stderr,"Invalid option, exiting\n\n");
	   break;		      
       }
    exit(0);

    }
#endif

void IMG_ACC_END() { puts(FIL_ID); }
