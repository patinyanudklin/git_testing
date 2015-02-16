/*
 *	filename IMG.H		- 
 *		$Revision: 1.89 $ $Date: 2015/01/02 03:16:27 $	
 *      ~~ Copyright 1988-2015 Kurt Rudahl and Sally Goldin
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
 *
 *	Requirements:
 *	   
 *	   dtypes.h dlimits.h dhead.h
 *
 ****************************************************************
 *   $Id: img.h,v 1.89 2015/01/02 03:16:27 rudahl Exp $
 *   $Log: img.h,v $
 *   Revision 1.89  2015/01/02 03:16:27  rudahl
 *   fix Dragon/OpenDragon conditional
 *
 *   Revision 1.88  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.87  2014/12/06 11:31:45  rudahl
 *   conditional changes for OpenDragon
 *
 *   Revision 1.86  2014/12/05 12:32:30  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.85  2014/04/01 07:24:45  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.84  2014/03/01 01:45:40  rudahl
 *   added create() for foreign files, for rosetta
 *
 *   Revision 1.83  2014/02/09 04:27:08  rudahl
 *   lint
 *
 *   Revision 1.82  2012/02/06 01:53:45  rudahl
 *   clean up and document calcImageScale
 *
 *   Revision 1.81  2012/01/02 02:55:28  rudahl
 *   add readimage,saveimage
 *
 *   Revision 1.80  2011/01/12 04:42:34  rudahl
 *   added new registration fields to update_georef and header
 *
 *   Revision 1.79  2010/12/19 06:58:05  rudahl
 *   getImageReader/Writer
 *
 *   Revision 1.78  2008/09/12 11:44:23  rudahl
 *   added handling of extents, georef header fields; new create() for de-novo files
 *
 *   Revision 1.77  2008/08/12 11:37:36  goldin
 *   update documentation
 *
 *   Revision 1.76  2008/06/19 08:24:32  rudahl
 *   testing blob access
 *
 *   Revision 1.75  2008/06/19 07:12:42  rudahl
 *   testing blob access
 *
 *   Revision 1.74  2008/06/14 10:15:55  rudahl
 *   added LinesBlob to trailer
 *
 *   Revision 1.73  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.72  2007/09/09 11:45:25  goldin
 *   Move getWorkingImagePath to the server
 *
 *   Revision 1.71  2007/08/19 08:04:49  rudahl
 *   changes to CG_ViewportSenddisplayCommand
 *
 *   Revision 1.70  2007/08/02 11:25:37  rudahl
 *   changed some member vars from ushort to int
 *
 *   Revision 1.69  2007/01/26 06:38:15  goldin
 *   Change doc to deprecate passing zeros to create functions
 *
 *   Revision 1.68  2006/12/31 12:15:22  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.67  2006/12/31 09:20:59  goldin
 *   change INPUTBASE to support Combine operation
 *
 *   Revision 1.66  2006/11/20 13:31:28  rudahl
 *   added IMAGEDATA_SELECTOR arg to open
 *
 *   Revision 1.65  2006/11/11 08:06:55  goldin
 *   Refactoring to support igc metafile update
 *
 *   Revision 1.64  2006/08/20 11:05:07  goldin
 *   Add fields for metafile and extent to Dragon header, reader and writer
 *
 *   Revision 1.63  2006/08/05 10:34:51  goldin
 *   move inline functions
 *
 *   Revision 1.62  2006/07/29 11:13:54  goldin
 *   add static fn to get status message
 *
 *   Revision 1.61  2006/04/19 09:55:09  goldin
 *   Moved getWorkingBits to img.cpp
 *
 *   Revision 1.60  2006/03/04 09:21:58  rudahl
 *   corrected docs
 *
 *   Revision 1.59  2005/12/31 05:19:59  rudahl
 *   improved error reporting on create()
 *
 *   Revision 1.58  2005/12/30 10:35:28  rudahl
 *   cleanup
 *
 *   Revision 1.57  2005/11/29 13:18:20  goldin
 *   Move enum for image states outside of C++ conditional
 *
 *   Revision 1.56  2005/09/17 10:57:34  rudahl
 *   added bulletproofing
 *
 *   Revision 1.55  2005/09/17 05:40:16  rudahl
 *   improved dump, trace, docs; ProcessRect
 *
 *   Revision 1.54  2005/09/12 07:30:41  rudahl
 *   fixes re dp.h
 *
 *   Revision 1.53  2005/07/29 04:03:57  rudahl
 *   improved docs
 *
 *   Revision 1.52  2005/07/22 15:19:32  rudahl
 *   added header fields, functions
 *
 *   Revision 1.51  2005/07/03 13:28:56  rudahl
 *   improving createImage
 *
 *   Revision 1.50  2005/06/26 06:18:29  rudahl
 *   moved pFp from Image to ImageReader,Writer
 *
 *   Revision 1.49  2005/04/28 13:21:07  goldin
 *   change documentation for revise_geometry
 *
 *   Revision 1.48  2005/04/01 03:27:52  rudahl
 *   working on grstop Server modules
 *
 *   Revision 1.47  2005/03/19 06:25:44  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.53  2005/03/13 02:42:58  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.52  2005/03/11 21:37:28  rudahl
 *   added getWorkingImage stuff
 *
 *   Revision 1.51  2005/03/11 20:28:20  goldin
 *   debugging rewriteImageHeader
 *
 *   Revision 1.50  2005/03/11 18:00:26  rudahl
 *   added getWorkingbits
 *
 *   Revision 1.49  2005/03/11 17:11:32  rudahl
 *   revised zero, CloseImage, rewriteHeader
 *
 *   Revision 1.48  2005/03/10 22:41:56  rudahl
 *   added rewriteHeader
 *
 *   Revision 1.47  2005/03/09 01:34:50  rudahl
 *   fix missing args in update_text(), add CloseImage
 *
 *   Revision 1.46  2005/03/06 17:32:09  rudahl
 *   revising create() and update_text() args
 *
 *   Revision 1.45  2005/03/06 00:14:43  rudahl
 *   Moved creation of writer until writeTrailer
 *
 *   Revision 1.44  2005/03/03 21:50:01  goldin
 *   Implement remaining revise_ & update_ methods
 *
 *   Revision 1.43  2005/03/03 16:15:43  rudahl
 *   refinements while converting grstop
 *
 *   Revision 1.42  2005/03/01 23:04:43  goldin
 *   Implement new create function for new output images; fix update functions
 *
 *   Revision 1.41  2005/02/28 21:15:51  goldin
 *   add update_georef methods
 *
 *   Revision 1.40  2005/02/23 17:46:44  rudahl
 *   new update, wrapper fns; moved from hdrstats to dhead
 *
 *   Revision 1.39  2005/02/22 19:58:04  rudahl
 *   new update, wrapper fns
 *
 *   Revision 1.38  2005/02/22 03:43:04  rudahl
 *   removed hdrInfo, header fields
 *
 *   Revision 1.37  2005/02/20 17:06:00  rudahl
 *   prelim create IMAGEHDR accessor fns
 *
 *   Revision 1.36  2005/02/16 00:19:56  rudahl
 *   typo
 *
 *   Revision 1.35  2005/02/15 21:37:52  rudahl
 *   rototypes for revise, update, rewriteHdr
 *
 *   Revision 1.34  2005/02/15 02:36:41  san
 *   Fixes error
 *
 *   Revision 1.33  2005/02/12 02:23:16  rudahl
 *   added (but not yet using) IMG_STATES ~~
 *
 *   Revision 1.32  2005/02/10 04:59:39  rudahl
 *   cleaned up tracing and error reporting
 *   cleaned up image file writing
 *
 *   Revision 1.31  2005/02/07 05:41:08  rudahl
 *   added putImageLine fns
 *
 *   Revision 1.30  2005/02/03 03:24:00  rudahl
 *   work on implementing new create(), getImageLine etc in img class
 *   plus beginning of standardized error numbers
 *
 *   Revision 1.29  2005/01/30 03:49:31  rudahl
 *   add some extern C access fns
 *
 *   Revision 1.28  2005/01/30 01:30:21  rudahl
 *   moved some fns from img_xx; added TEST, logging
 *
 *   Revision 1.27  2002/09/23 13:52:25  rudahl
 *   added OriginalVersion
 *
 *   Revision 1.26  2002/09/23 13:31:27  rudahl
 *   added band, comment
 *
 *   Revision 1.25  2002/09/15 16:19:20  rudahl
 *   purge
 *
 *   Revision 1.24  2002/09/09 16:45:43  rudahl
 *   changed img::GetHeaderInfo
 *
 *   Revision 1.23  2002/08/31 23:04:04  rudahl
 *   adding classnamelen fields; improving dump
 *
 *   Revision 1.22  2002/08/30 20:34:01  rudahl
 *   added a couple of Image fields
 *
 *   Revision 1.21  2002/08/28 16:11:11  rudahl
 *   improved dump, zero
 *
 *   Revision 1.20  2002/08/22 15:57:39  rudahl
 *   moved RECT typedef to dtypes
 *
 *   Revision 1.19  2002/08/22 00:29:48  goldin
 *   Add new header argument to adjust_geoinfo
 *
 *   Revision 1.18  2002/07/20 00:23:27  rudahl
 *   revs to IMAGE struct; add init(pImage)
 *
 *   Revision 1.17  2002/07/19 14:37:55  rudahl
 *   expanded docs in status
 *
 *   Revision 1.16  2002/07/13 00:37:33  rudahl
 *   continue to impl. Image class
 *
 *   Revision 1.15  2002/07/12 17:07:18  goldin
 *   Make lines and pixels elements be ushort
 *
 *   Revision 1.14  2002/07/12 00:10:33  rudahl
 *   renumbered images; implemented Image class
 *
 *   Revision 1.13  2002/07/01 14:22:51  rudahl
 *   added OUTPUTIMAGE
 *
 *   Revision 1.12  2002/06/25 00:31:19  rudahl
 *   rearrangement of structure
 *
 *   Revision 1.11  2002/06/18 18:55:42  rudahl
 *   changed field sequence
 *
 *   Revision 1.10  2002/06/17 14:23:37  rudahl
 *   moved remap fn to img_acc.h
 *
 *   Revision 1.9  2002/06/14 23:56:50  goldin
 *   Added prototype for fn to compute remapping table
 *
 *   Revision 1.8  2002/05/15 15:52:47  rudahl
 *   improved docs
 *
 *   Revision 1.7  2002/05/15 00:57:11  rudahl
 *   added some fields
 *
 *   Revision 1.6  2002/05/03 00:33:35  rudahl
 *   purged and added fields
 *
 *   Revision 1.5  2000/06/18 22:45:22  rudahl
 *   fixup for grsproc class table; fwrthdr additional arg
 *
 *   Revision 1.4  1999/04/23 01:01:47  rudahl
 *   adapted for WIN32, non-WF environment
 *
 *   Revision 1.3  1999/04/16 18:04:48  rudahl
 *   revising IHEAD and IMAGE functions
 *
 *   Revision 1.2  1999/04/11 17:30:01  rudahl
 *   converting away from VFiles
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:18  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.6  1998/01/22  12:09:08  tower
 * checkin for class class5_0
 * 
 * Revision 4.5  1998/01/22  12:09:08  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.4  1996/07/04  05:44:58  lcd
 * checkin for class class49
 * 
 * Revision 4.3  1996/04/27  06:06:58  lcd
 * checkin for class class49
 * 
 * Revision 4.1  1994/08/14  11:20:18  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/06/03  10:55:54  tower
 * final for DRAGON 4.0G.
 * general changes: MSC v 6 adaptations, graphics screens to 1280 pix.
 * 
 * Revision 4.0  1993/06/03  10:55:54  tower
 * Final for DRAGON Release 4.0
 * 
 * Revision 4.0.1.6  93/02/28  15:03:37  at
 * moved DispImg prototype from img.h to graf.h; thus graf.h is
 * now the ONLY exportable fns from the graphics driver
 * 
 * Revision 4.0.1.5  93/02/27  15:04:34  tower
 * split out most of the graphics driver prototypes and definitions into
 * new file called graf.h. 
 * Augmented IMAGE structure with 'stretch' and 'thisone' and 'control', 
 * and fixed alignment for packing.
 * 
 * Revision 4.0.1.4  93/02/14  14:29:51  at
 * Changed image structure: header ptr now far,
 * filename field now FMSIZE, rearranged fields
 * for better alignment. Old structure available
 * conditional on R305. Also, added some prototypes.
 * 
 * Revision 4.0.1.1  92/11/23  12:58:45  tower
 * changed DEBUG in enum to DEBUGP
 * 
 * Revision 4.1  92/11/13  11:32:57  tower
 * added DrawCirc prototype.
 * 
 * Revision 4.0  92/06/03  08:45:09  tower
 * Update for Zortech 3.0; begin DRAGON Professional
 * 
 * Revision 3.12  92/02/23  16:16:46  tower
 * for 3.05. Added some more CONFIG values (ATI-1024), smoe prototypes
 *           for DFILES, prototype for GrafCal().
 * 
 * Revision 3.11  91/12/19  16:40:12  tower
 * for 3.05. minor fixes & cleanup
 * 
 * Revision 3.10  91/11/25  21:02:48  tower
 * for 3.05: RESBITS=1,2,4 depending on scr pix; 
 * TARGA_PLUS_CONFIG; Graf_Drelease
 * 
 * Revision 3.9  91/09/19  19:08:17  tower
 * added D_RELEASE; removed old Lattice stuff
 * 
 * Revision 3.8  91/09/19  16:58:54  at
 * development of DRAGON 3.05. removed obsolete material; added
 * prototypes for image file header fns
 * 
 * Revision 3.7  91/08/18  10:47:06  tower
 * for 3.05: added Fullcolor; enum for CurScreen; RES_TEXT; changed id_struct
 * 
 * Revision 3.6  91/06/17  13:43:02  at
 * revisions, including moved some stuff here from WF.H, in prepn
 * for DRAGON 3.05
 * 
 *
 ****************************************************************
 *
 *	defines structures relating to images
 * 
 * Requires: hdrstats.h
 *
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	July 24, 1988
 *	rev 1/7/89 added SETLUTS,GETLUTS
 *	rev 2/26/89 added #defines for CurScreen() 
 *	rev 6/6/89 incr MAXVPIX for 8514
 *             rev 7/7/89 changed image field "buffer" to
 *                        be a virtual file ptr. Added pixbits field
 *	rev 7/25/89 added IN_DGRAPH op. for DGRAPH
 *	rev 4/90 added STDPIX etc, GrafChar proto, revd MapColr
 *	rev 9/28/90 added COLNYBS field to idflags for hi color res.
 *	rev 10/8/90 added ifdef LATTICE kludge
 *	rev 10/16/90 added CFG512 as Targa var.
 *	rev 11/12/90 added VESA
 *	rev 3/7/91 added N9, N9R
 *	rev 4/9/91 added defn of MAINIMG, get_line,put_line,
 *                         fillimage macros
 *	rev 6/7/91 moved color names, rect, point, Gswitch prototype,
 *                        etc from DRAGON.H to here for 3.05. 
 *	7/3/91 changed CurScreen values from #defines to enum G_PARAMS
 *		added FCRES bit to id_struct flags word
 *	8/17/91 added RES_TEXT
 *	8/18/91 seg   Removed obsolete STDPIX, etc.
 *                           Added prototype for CopyImgInfo
 *	8/20/91 ktr   added NOZAP to CurScreen enum
 *	8/25/91 seg   added prototype for InitHeaderTokens
 *	8/31/91 seg   added prototype for copy_hdr, modified
 *                            Examine_Ihdr,fwrtihdr prototypes.
 *	9/19/91 ktr   added D_RELEASE (fn 0xD) to return the compiled
 *			DRAGON release number. 
 *			Refer to DRELEASE.H for details
 *	10/14/91 ktr  added RESBITS - return 1,2,4 depending on scr pix	
 *	12/31/91 ktr  added ATI1024_CONFIG, ATIXL_CONFIG
 *	1/5/92	      added prototype for GrafCal()	
 *	2/23/92       added some more prototypes for DFILES.C
 * 4.0	5/10/92 ktr	updating for Zortech 3.0: removed redundant decls.
 *			began mods for DRAGON Prof
 * 	8/22/92 ktr	added DrawCirc()
 * 	2/13/93 seg	added prototypes for new functions in dfiles
 * 	                also, made the hdr pointer in img structure far,
 *                        use FMSIZE to set filename length.
 *	2/14/93 ktr	removed the definitions belonging to DRAPH to
 *			GRAF.H. Added 'control' and 'stretch' to IMAGE and
 *			rearranged members to improve 32-bit alignment
 *	2/28/93 seg	Increased MAXIMG to 12, put imagelist extern defn
 *                         here in img.h
 *   3/13/93 	ktr	revised IMAGE to use SCALAR_STATS_FIELDS (ref dhead.h)
 *      8/14/94 seg     Added proto for get_calibrated_val
 *	1/22/95 ktr	minor syntax changes for MSC 8.5
 *	10/21/95 ktr	removed query_font prototype as cleanup 
 *	4/27/96 ktr	changed some fns in DFILES.C
 *	7/3/96 ktr      added FormatHdrVal()
 *	7/5/97 ktr 	new Examine_Ihdr loadflag value of 4. 
 *			   Just read the hdr. Essentially this is frdihdr.
 *	8/25/97 ktr	change IMAGE struct histptr and residentflag defns.
 *	12/22/97 ktr	get_data_val and get_ref_coord subsumed into
 *			DisplayImageInfo, declared in cgatpriv.h
 * 5.0	4/1/99 ktr	enhanced IMAGE def'n with RES_xxxMASK's
 *			and added documentation	and fields.
 *      4/22/99 seg     Added conditional NO_WF to exclude refs to
 *                       TOKEN
 *      6/18/00 ktr     added ability to prevent fwrthdr from setting filename
 *	5/1/2002 ktr	added puKeyTable to IMAGE
 *	7/1/2002 ktr	added OUTPUTIMAGE symbol; init used in DRAGREG
 *	7/6/2002 ktr	resequenced fields; added some; removed some;
 *			added docs.
 * 5.5	2005-1-28 ktr	Adapt for v 5.5, which includes a new header fmt
 *			and a "virtual" header as IMAGEHDR (dhead.h)
 *		NOTE
 *		    The current class includes many data fields which
 *		    are effectively redundant with IMAGEHDR
 *		    For the moment, keep this
 *		    Eventually, make ImageHdr a member of Image
 *	2005-2-21 ktr	got rid of HEADER_INFO_FIELDS, hdrInfo, header
 * 5.7	2005-06-25 ktr	moved pFp from img.h to imageWriter.h
 * 	2005-7-20 ktr	added h_OriginalFileName and IMAGEDATA_SELECTOR
 * 5.11	2007-5-11 ktr	adapt for 32-bit imageMem; renamed some members
 *	2008-06-14 ktr	added LinesBlob to trailer
 * 6.1	2012-01-01 ktr	added saveImage
 *************************************************************************
 *
 * requires: dhead.h
 */

#ifndef IMG_H
#define IMG_H	/* signal this file has been loaded */

/* Structure to represent one point/vertex. Currently z is not
 * used in OpenDragon
 */
typedef struct
    {
    double x;
    double y;
    double z;
    } VERTEX;

#ifdef __cplusplus
class Image;
extern "C" {
#else
#if DRAGON_VER >= 6
    typedef void Image;
#else
    typedef void * Image;
#endif
#endif

/* temporary macros for conversion to explicit image indices in imgacc */ 

#define MAINIMG  0    /* index into imagelist for primary img */

/* image structure */

#if DRAGON_VER >= 6
#define SCALAR_STATS_FLDS   \
    double m_dImgvar;	/* image data variance   */ \
    double m_dImgsd;	/* image data standard deviation */ \
    int m_iImgmean;	/* image data mean value */ \
    int m_iImgmax;	/* maximum value in img  */ \
    int m_iImgmin;	/* minimum value in img  */
#else
#define SCALAR_STATS_FLDS   \
    double imgvar;            /* image data variance   */ \
    double imgsd;             /* image data standard deviation */ \
    unsigned short imgmean;   /* image data mean value */ \
    unsigned short imgmax;    /* maximum value in img  */ \
    unsigned short imgmin;    /* minimum value in img  */
#endif

typedef struct tagSCALAR_STATS
    {
    SCALAR_STATS_FLDS	/* like dhead-old.h, copied here for independent use */
    } SCALAR_STATS ;	/* used mostly for sizeof() argument */

typedef struct tagBYTEMAP { byte element[256]; /* FARMEM control;*/ } BYTEMAP;

typedef struct { ulong bin[IMG_HIST_LEN]; } IMGHISTO;
	   /* histogram array (256 bins); 0'th elt. is total */

//typedef struct { ulong bin[HDR_HIST_LEN]; } HDRHISTO;
	   /* histogram array (binned in fours); 0'th elt. is total */

/* constant values for residentflag low-nybble */
#define RES_NOTINIT   0
#define RES_INIT      1
#define RES_LOADED    2
#define RES_COMBINED  3
#define RES_RESMASK   0xF	/* to mask just these bits */

/* constant values for residentflag high-nybble */
#define RES_NOHIST    0		/* histptr should be NULL */
#define RES_MEMHIST   0x10	/* histptr points to IMGHISTO of 257 bins */
#define RES_SMALLHIST 0x20	/* histptr points to HDRHISTO of 65 bins */
#define RES_FILEHIST  0x40	/* histptr points to filename with IMGHISTO */
#define RES_HISTMASK  0xF0	/* to mask just these bits */
/* constant values for modflag */
/* should be or-ed together    */ 
#define MOD_MATCHDISK 0
#define MOD_MODIFIED  1
#define MOD_SCALED    2
#define MOD_SUBSET    4

/*	An IMAGE structure controls how image data is used by the
 *	software. It is passed around alternately as a pointer to
 *	an IMAGE, or as an index into array 'imagelist', whose
 *	elements have stylized usage (e.g. element 0 is MAINIMAGE).
 *
 *	Initially, all fields are 0. Then, the structure is initialized
 *	in phases, not all of which may occur. Each phase involves a
 *	subset of the fields, as explained here.
 *
 *	uImageType, which is an enum IMGTYPE_T, is the primary selector.
 *	If it is IT_UNINIT, then no other field is valid
 *	If it is IT_AUTO, then only 'filename' is valid. 'uImageType'
 *		will be changed to some other value by ...
 *	If it is IT_VIRTUAL, the structure refers to a virtual file
 *		and at least 'ivfp' is valid.
 *	else, it refers to a physical file of format 'uImageType',
 *		and at least the fields needed to read and parse
 *		the image data are valid: 
 *
 *	Fields required to read and parse a disk data file are:
 *	    uImageType
 *	    filename (and fnlen ?)
 *	    geometry of the disk file:
 *		pixels, lines, ulFileOffset, ulLinePitch, ulPixPitch
 *		pixbits, uDataFloor, uScaleFactor (test for != 0)
 *	    geometry of region to read:
 *		ProcessRect (prev. called 'filewindow')
 *
 *	Fields required for virtual file
 *	    uImageType and ivfp
 *	    pixels, lines are the same as mem_X, mem_Y, and are the 
 *		file structure
 * 
 *	Usage of the following fields may depend on whether the IMAGE is
 *	an input IMAGE ('I:', thisone != MAINIMAGE or OUTPUTIMAGE)
 *	an output IMAGE ('O:', thisone == OUTPUTIMAGE)
 *	a buffer IMAGE ('B:', thisone == MAINIMAGE)
 */
typedef struct tagIMAGE_R400
	{
	size_t	thisone;	/* array index of this IMAGE */
//	IHEAD * header;	/* default: NULL; O: header to be written */
	BYTEMAP * pStretch;	/* default: NULL; I: ??
				 * in CGATE, there are four stretch tables
				 * assumed to corresp to images 0-3. 
				 * This points to the appropriate one of these
				 * and should NEVER be freed. */
	void * histptr;	/* I: derive from hdr; B: NULL; 
				 * O: construct for output. 
				 * See type defined above */
	SCALAR_STATS_FLDS	/* see above and  dhead-old.h
				 * - has odd number of 16-bit elts */
		/* 'fnlen' through 'lines' init. by header read function */
		/* file is then closed */
	char	residentflag;	/* bit vect: see RES_xx defns above.
				 * has it been read-in yet? 0 => no;
				 * 1 => image struct init. 
				 *     but file not resident;
				 * 2 => file data resident */
	char	modflag;	/* 1 => different from orig. file  */
	char	filename[PATH_MAX]; 
	ushort  pixels,lines;	/* I: of disk file
				 * B: of source clipped to workinglines,pix 
				 * O: of image to write */
	rect	ProcessRect;   	/* I: x0 y0 x1 y1 (inclusive) subset to process
				 * default: 0,0,pixels-1,lines-1 */
	IMGTYPE_T uImageFormat;	/* see IT_xx enum defined above
				 * B: IT_VIRTUAL */
	ushort pixbits;		/* # bits per pixel: e.g. 1,2,4,8,12,16,24,32
				 * this number refers to the file packing, 
				 * not the significance */
	ushort uDataOffset;	/* optimal: subtract from disk data, then ...*/
	ushort uDataFactor;	/* > 0 => divide disk data to yield 8 bits */
	ushort uScaleFactor;	/* or, simple scaling factor to yield 8 bits */
	ushort uPreferredScaling; /* 0 => none; 1 => scaling; 2 => optimal */ 
		/* following fields refer to the file on the disk */
	ushort uNumLabels;	/* actual number of class names in file;
				 * NOT the same as header->numlabels
				 * this value is calc'd by actually counting
				 * the labels which may be sparse 
				 * and may be in 'I'-type files. */
	ushort uMaxLabelLen;	/* how long in chars is biggest actual? */
	ushort uLabelEncoding;	/* how are labels actually in the file header?
				 * 1=>10 chars of ASCII; 2=>32 chars of Uni16*/
	ulong ulFileOffset;	/* file offset where line 0 pixel 0 starts */
	ulong ulLinePitch;	/* bytes from one line to the next */
	ulong ulPixPitch;	/* bytes fron one pixel to the next in a line*/
	ushort * puKeyTable; /* if non-NULL, ptr to array of line number
				  * remapping indices
				  * used only during GetImageLine ops */ 
	size_t uKeyTableLen;	/* number of ELEMENTS in KeyTable */
//	FILE * ivfp;		/* pointer to image file, if any open */
	  /* pFp should be last in structure, since
	   * a) if must be a near pointer 
	   * b) near ptrs are different sizes in different compile models
	   */
//	FILE * pFp;		/* if non-NULL, is fopen'd file */
	Image * pImageObj;	/* ptr to object which owns this struct */
	} IMAGE;

//ushort getWorkingLines();
//ushort getWorkingPixels();

//typedef IMAGE image;		/* for consistency */

#define SCRATCHIMG 4
#define REDIMAGE  3
#define GRNIMAGE  2
#define BLUIMAGE  1
#define MASKIMAGE 5
#define OUTPUTIMAGE 6
#define INPUTBASE 12   
  /* modified 12/30/06 for new combine operation */

#ifdef __cplusplus
}  /* end of extern "C" */
#endif


typedef enum
    {
    IMG_UNINIT,		/* i.e. ctor called, nothing else */
    IMG_ZEROED,
    IMG_ERROR,		/* unusable b'casue of error */
    IMG_INITFROMFILE,	/* image has been initialized from a file */
    IMG_WRITABLE,	/* image geometry has been init but not yet written */
    IMG_HDRWRITTEN,	/* too late to change the geometry */
    IMG_CHANGED,	/* some non-geometry item has changed since the write*/
    IMG_CLOSED
    } IMG_STATES_T;

#define IMG_STATE_NAMES \
    "IMG_UNINIT (ctor called, nothing else)", \
    "IMG_ZEROED", \
    "IMG_ERROR (unusable because of error)", \
    "IMG_INITFROMFILE (initialized by reading a file)",\
    "IMG_WRITABLE (geometry has been init but not yet written)",\
    "IMG_HDRWRITTEN (too late to change the geometry)",\
    "IMG_CHANGED (some non-geometry item has changed since the write)",\
    "IMG_CLOSED"

#ifdef __cplusplus
class ImageReader;
class ImageWriter;

class Image : public OB
    {

    public: /* methods */
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
	Image(int iDebug=0,int iTrace=0);

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
	 * @return		>0 (m_iStatus) if OK else error #:
	 */
	int open(const char * pczFilename, BOOL bModifiable,
		 const IMAGEDATA_SELECTOR * pSel = NULL);

	/* set up an Image BASED ON AN EXISTING FOREIGN IMAGE
	 *   This is for use in a foreign imageReader subclass, which requires
	 *   an IMAGE * in the getImageLine function()
	 *   See e.g. jasperImageReader
	 * @param pImageHdrStruct  already initialized header
	 *			   MUST have the following fields initialized:
	 *			       h_OriginalFileName,size[0,1],ulPixelPitch,bits_per_pix
	 * @return		   0 if OK
	 */
	int create(const IMAGEHDR * pImageHdrStruct);

	/* set up an Image for output
	 * This works by: 1. Create a new ImageHdr
	 *                2. Copy an existing ImageHdr
	 *		  3. Allow the selected writer subclass to 
	 *                   modify the new ImageHdr
	 * 		  4. Init 'this' from the new ImageHdr.
	 * If the image geometry need to be cahsed, 
	 *   call revise_geom() BEFORE calling write().
	 * If the image data differs from pSrcImage,
	 *   call update() AFTER writing the image data, 
	 *   then call rewriteImageHeader().
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param bReReadable	if TRUE, data can be re-read after writing
	 * @param uImgType	type of image file
	 * @param pSrcImage	Image to copy
	 * @param pczFtype      Dragon file type - "I", "C" or "L",
	 *			or NULL to keep type from copy
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
	int create(const char * pczFilename, BOOL bOverwrite,
		   BOOL bReReadable, IMGTYPE_T uImgType,
		   const Image * pSrcImage,const char* pczFtype);

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
	int readImage(byte ** pBuf, 
		     const char * pczPath,const char * pczRootName,
	    	     const char * pczModifier, int iVerbose);

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
	int saveImage(const byte * pOutBuf,uint uLines,uint uPix, Image * pImg,
			     const char * pczPath,const char * pczRootName,
		 	     const char * pczModifier, int iVerbose);

	/* revise critical values for an existing writable image.
	 * Only the params with non-default vals will be changed.
	 * This must be invoked BEFORE writing the header
	 * @param pczFilename	NULL => do not change
	 * @param bOverwrite	FALSE means FILE MUST NOT EXIST ON DISK
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
	int revise_geom(const char * pczFilename=NULL, BOOL bOverwrite=TRUE,
			BOOL bReReadable=FALSE, IMGTYPE_T uImgType=IT_INVALID,
			ushort uNumLines=0, ushort uNumPixels=0,
			ushort uBitsPerPix=0, ushort uNumBands=0,
			ushort uNumResolutions=0);

	/* change scaling information for an existing image.
	 * Only the params with non-default vals will be changed.
	 * This may be invoked after writing the header and the image data
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
	int update_scaling(double dScaleFactor,
			   double dScaleOffset,
			   const char * pczScalingType,
			   double dZ_scale=0.0,
			   double dZ_offset=0.0,
			   const char * pcZ_unit=NULL);

	/* change text information (except classnames, unitnames) 
	 * for an existing image.
	 * Only the params with non-NULL vals will be changed.
	 * This may be invoked after writing the header and the image data
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int update_text(const char * pczTitle,
			const char * pczId,
			const char * pczComment,
			const char * pczSource,
			const char * pczScene,
			const char * pczSubscene,
			const char * pczBand,
			const char * pczColorfileName,
			const char * pczFtype);

	/* change stats and histogram information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * @param pImgStats	stats for image
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
	int update_stats(const IMGSTATS * pImgStats);

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
	int update_georef(int img_x, int img_y, 
			  const MapCoord * ref_x, const MapCoord * ref_y,
			  double xcell_size, double ycell_size,
			  const char* pczProjection, const char* pczUnitname,
			  const char * pczDateTime,const char * pczUTMZone,
			  int iRegistered);

	/* change labels information for an existing image.
	 * This may be invoked after writing the header and the image data
	 * If <b>iNumLabels</b> is different from than the current number of labels,
	 * 	the function will discard all the old labels and replace them
	 * 	with the new ones.
	 * If <b>iNumLabels</b> is -1, or the same as the current number, 
	 * 	the function will only replace the first <b>uArrayCount</b> labels.
	 * @param iNumLabels	-1 for don't change, or number of labels in img
	 * @param uArrayCount	number of items in pLabels
	 * @param pLabels	label info
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 - invalid argument
	 */
	int update_labels(int iNumLabels,
			  size_t uArrayCount,
			  const LABEL_INFO * pLabels);

	/* change metafile information 
	 * for an existing image.
	 * Only the params with non-NULL vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int update_metainfo(const char * pczMetafile,
			    const char * pczGuid);

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
	int update_extent(double minX, double minY,
			  double maxX, double maxY);

	/* change originalfile information 
	 * for an existing image.
	 * Only the params with non-NULL or >= 0 vals will be changed.
	 * To CLEAR a value, pass an empty non-null string
	 * @param (all of them)	NULL or new value (possibly "")
	 * @return		0 if OK
	 *			-66 => state conflict
	 *			-90 to -97 - invalid argument
	 */
	int update_original(uint uOriginalBandCount,
			    uint uOriginalBandNumber,
			    const char * pczOriginalFileName);

	/* copy blob info from an existing image.
	 * @return		0 if OK
	 *			-66 => state conflict
	 */
	int copy_blob();

	/* initialize critical values for a new file with specified name
	 * which may be deleted if it already exists.
	 * This fn is provided for creating an image which is in no way
	 * a derivative of an existing image.
	 * Should be preceeded by zero().
	 * @param pczFilename	full, long path to file
	 * @param bOverwrite	TRUE => silently delete if exists
	 * @param bReReadable	if TRUE, data can be re-read after writing
	 * @param uImgType	type of image file
	 * @param uNumLines	number of lines in target image
	 * @param uNumPixels	number of pixels/line in target image
	 * @param uBitsPerPix	if 0, is determined by uImgType
	 *                         DEPRECATED - should pass correct value
	 * @param uNumBands	if 0, is determined by uImgType
	 *                         DEPRECATED - should pass correct value
	 * @param uNumResolutions if 0, is determined by uImgType
	 *                         DEPRECATED - should pass correct value
	 *                         (not currently used as of 1/2007)
	 * @param pczFtype      Dragon file type ("I", "C" or "L")
	 * @param pczOriginalName NULL or name of source file
	 * @return		0 if OK
	 *			-57 => already exists and bOverwrite=FALSE
	 *			-90 to -97 - invalid argument
	 */
	int create(const char * pczFilename, BOOL bOverwrite,
		   BOOL bReReadable, IMGTYPE_T uImgType,
		   ushort uNumLines, ushort uNumPixels,
		   ushort uBitsPerPix, ushort uNumBands=0,
		   ushort uNumResolutions=0, const char* pczFtype="I",
		   const char * pczOriginalName = NULL);

	/*	Close files and zero image
	 *
	 *	Returns 0 if OK 
	 *      else 
	 *		-54 if error
	 */
	int CloseImage();

//    private:
	/* set to valid but not meaningful values (mostly 0 or NULL)
	 * @param bFirstTime	if TRUE, assume ptrs are junk
	 *			if FALSE, ignore iIndex
	 * @param iIndex	if >= 0, set 'thisone'
	 * @return		0 if OK
	 *			else
	 *				-54 if file close error
	 */
	int zero(BOOL bFirstTime,int iIndex);

	/*	Close reader and writer files if open
	 *
	 *	Returns 0 if OK 
	 *      else 
	 *		-54 if error
	 */
	int closeImageFile();

    public:
	/* getWorkingBits - max number bitspp for mainimage
         * this may depend on the operation
	 * @param pczOp		3-letter operation code, or "" or NULL
	 *			if "" or NULL return lowest value
	 */
	static ushort getWorkingBits(const char * pczOp);

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
	const char * dump(int detail=1, const char * pczTitle=NULL) const;

	/* get read-only pointer to hdrInfo */
//	const HEADER_INFO_FIELDS * GetHeaderInfo() const { return &hdrInfo; };
	// GetHeaderInfo is deprecated name
	const IHEAD * GetHeaderInfo() const 
	    { return (m_pHdr != NULL) ? m_pHdr->getImageHdr() : NULL; };
	const IMAGEHDR * getIMAGEHDR() const 
	    { return (m_pHdr != NULL) ? m_pHdr->getImageHdr() : NULL; };

	/* what state is this Image in? */
	BOOL isInitialized() { return (strlen(image.filename) > 0); } ;
//	BOOL isOpen() 
//	  { return (image.pFp != NULL); } ;
//	  { return ((image.pFp != NULL) || (image.ivfp != NULL)); } ;
//	BOOL operator==(const char * pczFileName) 
//	  { return (strcmp(pczFileName,image.filename) == 0); } ;

	/* what kind of Image is it? */
	BOOL isOutput() { return (image.thisone == OUTPUTIMAGE); } ;
	BOOL isBuffer() { return (image.thisone == MAINIMG); } ;
	BOOL isInput() { return !isOutput() && !isBuffer(); } ;

	/* get the bitpattern (see valid_image())
	 * for current Image.
	 * Return value of Image.iStatus, except:
	 *    return m_iErrno if non-zero
	 */
	int getStatus() const   /* see iStatus for values */
	    { return (m_iErrno < 0) ? m_iErrno : m_iStatus; } ; 

	/* get size limits for MAINIMG.
	 */
	static ushort getWorkingLines() { return s_uWorkingLines; } ;
	static ushort getWorkingPixels() { return s_uWorkingPixels; } ;
#if defined MOVEDTOSERVER || DRAGON_VER <= 5
	static const char * getWorkingImageFile() { return "$$m.img"; } ;
#endif // #if defined MOVEDTOSERVER || DRAGON_VER <= 5

    protected:
		/*	read image header and set 'image' accordingly.
		 *	   fill in 'image->lines', 'pixels', 'pixbits',
		 *		and all other fields
		 *	EXCEPT, for non-DRAGON input images, 
		 *	    some fields set to defaults.
		 *	On exit, file is closed
		 * 	@param pczName	name of file to read
		 * 	@param pSel	specify band of multimand file
		 *	@return 	TRUE if OK and set m_iErrno to 0.
		 *	If fn returns FALSE, m_iErrno is < 0 if error.
		 *	Error values are:
		 *		-50 => file not found or not readable
		 *		-60 => header completely uninitialized 
		 *		-64 => there's alread an open file in pFp,
		 *			so just leave values alone
		 *		-65 => no name supplied
		 *		-74 => file not found, or error reading hdr
		 *		-75 => file contents preclude valid interp.
		 *              -961-964 errors from CalculateKeyTable
		 */
	BOOL readImageHeader(const char * pczFileName,
			     const IMAGEDATA_SELECTOR * pSel);

    public:
	/*	Retrieve a line of raw data from the appropriate
	 *	location into buffer. 
	 *	This is for situations where the caller either knows the
	 *      structure of the data, or doesn't care.
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
         *                      This MUST be big enough to hold an entire line
	 *                      of data from this image or an error will result
	 * 	@param pDataSel	NULL or selects data to read
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			 ( return 0 => line is outside ProcessRect;
	 *				-60 => image not yet initialized
	 *				-66 => image state conflict
	 *				-68 => image not readable
	 *				-51 => file open error
	 *				-56 => past EOF
	 *				-63 => element too big for buffer)
	 *			        -91 => line number bigger than image
	 *			             or errors from fread, fseek
	 */
	int getImageLineRaw(byte * pBuf, const ushort uLineNo,
			    const size_t uBufSize,
			    IMAGEDATA_SELECTOR * pDataSel = NULL);

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
	 *				-91 => element too big for buffer)
	 */
	int getImageLine(byte * pBuf, const ushort uLineNo,
			 const size_t uBufSize,
			 IMAGEDATA_SELECTOR * pDataSel = NULL);

	// how big a buffer do we need for GetImageLine?
	// (This actually returns size for a full line of read data,
	// regardless of multiband and scaling considerations.)
	size_t getLineBufferSize();
//	    { return (m_pReader!=NULL) ? m_pReader->getLineBufferSize() : 0;};

	/*	write image header and close output file
	 * 	if bReReadable, creates the reader
	 *	On exit, file is closed
	 *	Return 0 if OK and set m_iErrno to 0.
	 *	Error values are:
	 *		-60 => header completely uninitialized 
	 *		-64 => there's alread an open file in pFp,
	 *			so just leave values alone
	 *		-65 => no name supplied
	 *		-66 => image state conflict
	 *		-68 => need reader but unable to create one
	 *		-69 => no header writer found
	 */
	int writeHeader();

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
	int rewriteHeader(UINT32 uDataCheck, BOOL bWriteTrailer=TRUE);

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
	int writeTrailer(UINT32 uDataCheck);

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
	int putImageLineRaw(const byte * pBuf, ushort uLineNo,
			    size_t uBufSize);

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
	int putImageLine(const byte * pBuf, ushort uLineNo,
			 size_t uBufSize);


	const IMAGE * getImage() { return &image; } ;
	const ImageHdr * getImageHeader() const { return m_pHdr; } ;

	void setKey(ushort uKey) 
  	    { if (m_pHdr != NULL) m_pHdr->setKey(uKey); } ;

	int setLinesBlob(const byte * pBlob,size_t uBlobSize) const;
 
	~Image() { zero(FALSE,-1); } ;

    protected: /* methods */
		/* initialize the Image::image from the already initialized 
		 * ImageHdr. 
		 * @return		0 if OK
		 *			errors:
		 *			  -72 hdr not init
		 */
	int _MapFromImageHeader();

		/*	bring 'image' image stats & scaling into agreement
		 *	with hdr before attempting to load or use an input
		 *	image file.
		 *	Requires that pixels, lines, ulPixPitch, ulLinePitch
		 *	be already set, and pHdr updated to 4.1 or later
		 *	This is ONLY for DRAGON format files,
		 *	and ONLY for input images.
		 *	Return < 0 if err
		 *		-70: not permitted for this image.
		 *		-71: hdr stats not initialized
		 */
	int SynchImage2DragonHdr(const IMAGEHDR * pHdr);

		/*	bring histogram stats into agreement with 'pHdr',
		 *	before attempting to load or use an input image file.
		 *	This is ONLY for DRAGON format files,
		 *	and ONLY for input images.
		 *	Return < 0 if err
		 *		-70: not permitted for this image.
		 *		-71: hdr stats not initialized
		 */
	int SynchImageHistogram(const IMAGEHDR * pHdr);

		/**	
		 *      Initialize the buffer IMAGE structure appropriately
		 *      based on the contents of an input IMAGE specified
		 *      by uSrcNdx.  Unlike its progenitor MapRealtoVirtual
		 *      this function explicitly does nothing about reading
		 *      or initializing header information.
		 *      Prerequisites: assumes uWorkingLines and uWorkingPixels
		 *			     are set
		 *  @param uSrcNdx  Index of the input file to use as basis
		 *                       The destination index is implicit.
		 *  @return		< 0 if err 
		 *			-90 => source not appropriately init) 
		 *			else 0
		 */
	int MapFromInputToBuffer(const Image * pSrcImage);

	/* Calculate and return a scaling factor needed to 
	 * convert data ranging from 'uMinV' to 'uMaxV' to 8-bits
	 * NOTES 2012-Feb
	 *   If not > 8 bits this has no significant effect except
	 *   to set IMAGE fiedls to default values
	 *   This fn is used only by Image::SynchImage2DragonHdr
	 *   and the return value is never used
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
	 *			(really, just uMinV)
	 * @param  puDataFactor	NULL or where to put optimized scaling factor
	 *			(divisor for optimized:
	 *			  8BitVal 
	 *			     = (16BitVal - uDataOffset) / uDataFactor)
	 * @return		power-of-two divisor for non-optimized scaling
	 *			(=0 if uBitsPP <= 8)
	 *                      also set three IMAGE fields
	 */
#if DRAGON_VER >= 6
	ushort CalcImageScale(ushort uBitsPP, int iMaxV, int iMinV,
			      ushort * puDataOffset, 
			      ushort * puDataFactor);
#else
	ushort CalcImageScale(ushort uBitsPP, ushort iMaxV, ushort iMinV,
			      ushort * puDataOffset, 
			      ushort * puDataFactor);
#endif

    public: /* getters & setters */

	    /* if non-NULL, ptr to blob of vector data */
	byte * getLinesBlob() const;
   	    /* number of BYTES in LinesBlob */
	size_t getLinesBlobLen() const;

    public: /* members */
	    /* IMAGE is maintained for the moment as a structure, to minimize
	     * the effort in converting to using the class.
	     * However whenever possible members should be moved from IMAGE
	     * into being individual class members (preferably protected),
	     * and any new members should be so added.
	     * The function GetImage(size_t uIndex) (in img.c) 
	     * cann retrieve an Image class instance.
	     */
	IMAGE image;
		/* following describe 'histptr' in IMAGE */ 
	ushort m_uHistPtrCount;	/* probably 65 or 257 */
	ushort m_uHistPtrBinsize; /* 1 or 4 or, for 16-bit data, even bigger */
	const BOOL getModifiable() const { return m_bModifiable; } ;
	const IMG_STATES_T getState() const { return m_uState; } ;
	const ImageWriter * getImageWriter() { return m_pWriter; } ;
	const ImageReader * getImageReader() { return m_pReader; } ;
	const char * getStateName() const;
	static char * getStateName(unsigned int uState);

	static void set(ushort uSelector, ushort uValue);

    protected: /* members */
	/* HEADER_INFO_FIELDS contains values which are exact copies 
	 * of data in the header of an input .IMG file and are never modified.
	 * Note however that the strings are strdup'd and must be freed.
	 */
//        HEADER_INFO_FIELDS hdrInfo;
		/* for future use */
	void * m_puPalette;	/* if non-NULL, ptr to array of 256 
				 * 3 or 4 byte colors. Not yet used */
	size_t m_uPaletteLen;	/* number of BYTES in palette */
	int m_iStatus;		/* 0 if Image not init; 
				 * >0 if valid image:
				 *    bits 0:7 are the header cFtype[0]
				 *    bit 8 : N/A
				 *    bit 9 => it's a recognized image file
				 *    bit 10 => it's a DRAGON image file
				 *    bit 11 => it's a valid DRAGON image file
				 *      (size matches, etc)
				 *   Assuming all of the above are true, then:
				 *    bit 12 => it's multibyte
				 *    bit 13 => it's oversize (working_...)
				 *    bit 14 => it's bigger than display size 
				 *	(not yet)
				 */
	IMG_STATES_T m_uState;	/* limits possible actions to apply to image*/ 
    private: /* members */
	ImageReader * m_pReader;
	ImageWriter * m_pWriter;
	ImageHdr * m_pHdr;
	const Image * m_pSrcImage;		/* set only if created by create (copy) */
	BOOL m_bModifiable;
	BOOL m_bReReadable;
	BOOL m_bHdrUpdated;		/* TRUE => need to rewrite header */
	static ushort s_uLatest;	/* used to init. thisone for array elements */
	static ushort s_uWorkingLines;  /* these control the */
	static ushort s_uWorkingPixels; /* max size of image to use */ 
	static Class s_class_Base;
	static const char * s_czStateNames[];
    } ;

#endif // __cplusplus

#endif
