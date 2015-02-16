#include "drelease.h"
char TOOLIFIL_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.13 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*
 *	filename toolifil.c
 *		$Revision: 1.13 $ $Date: 2014/12/17 07:20:39 $	
 *
 *      ~~ Copyright 1999-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: toolifil.c,v 1.13 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolifil.c,v $
 *	Revision 1.13  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.12  2006/09/17 05:00:38  rudahl
 *	got rid of 'far' keyword
 *
 *	Revision 1.11  2005/08/01 04:49:46  rudahl
 *	remove need for non-default dlimits.h
 *	
 *	Revision 1.10  2005/03/19 06:33:30  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.10  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.9  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; except for toolcmd6, much work still needed
 *	
 *	Revision 1.8  2002/06/10 12:33:00  rudahl
 *	fixed file name building
 *	
 *	Revision 1.7  2002/04/17 23:09:45  rudahl
 *	fixups for 32-bit, long filenames
 *	
 *	Revision 1.6  2002/04/09 21:35:07  rudahl
 *	adapt for long filenames
 *	
 *	Revision 1.5  2002/02/13 01:25:32  rudahl
 *	 converted away from basemem version of workinglines
 *	
 *	Revision 1.4  2001/10/17 17:20:01  rudahl
 *	changes propagating from revs to filename.c & strsfn
 *	
 *	Revision 1.3  1999/10/23 19:23:16  rudahl
 *	added some 32-bit provisions
 *	
 *	Revision 1.2  1999/04/11 17:31:46  rudahl
 *	converting away from VFiles
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:40:18  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:40:18  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/12/22  15:22:12  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/12/22  15:22:12  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. 
 *    These fns are used to access image files. Previously
 *    this file also included functions to access memory images
 *    but these have been removed. Now we include only the
 *    so called "Group A" functions and "Group D" functions.
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *  Group A ( -dGRPA )
 *    Public disk image file access Functions:
 * 	  int dtk_ImageFileClose(const IFILEHANDLE handle)
 * 	  int dtk_ImageFileGetHdr(const char* filename, IHEAD* hdr)
 * 	  int dtk_ImageFileGetLine(const IFILEHANDLE handle, const int linenum,
 *		byte* buffer, const int ipix, const int npix)
 * 	  int dtk_ImageFileLines(const IFILEHANDLE handle)
 *	  int dtk_ImageFileName(const IFILEHANDLE handle, char* fname)
 * 	  int dtk_ImageFilePixels(const IFILEHANDLE handle)
 * 	  int dtk_ImageFilePutLine(const IFILEHANDLE handle, const int linenum,
 * 	  		const byte * buffer)
 * 	  IFILEHANDLE dtk_ImageFileReadOpen(const char * filename)
 * 	  IFILEHANDLE dtk_ImageFileWriteOpen(const char * filename,
 * 	  		const IHEAD* hdr, const char* filetype,
 *			const int do_stats)
 *
 *  Group D ( -dGRPD )
 *    Public query Functions:
 *       int dtk_MaxPixels(void);
 *       int dtk_MaxLines(void);
 *       int dtk_MaxImages(void);
 *       int dtk_GetRemapTable(const int img_index,ByteMap* table);
 *  	 int dtk_RemapImage(const int img_index, const ByteMap* table,
 * 			     const int change_image)
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-02-21 seg	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-8-1 ktr	use getWorkingLines not D_DFLTIMG stuff
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>  /* for toupper */

#ifdef __GCC__
#include <time.h>
#else
#include <process.h>
//#include <dos.h>
//#include <io.h>
#endif

#if defined _MSC_VER
//#include <malloc.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "dhead.h"
#include "dragonHd.h"
#include "hdrstats.h"
//#include "foreign.h"
//#include "ob.h"
//#include "imagfile.h"

/* ~~~ THIS FILE IS MOSTLY COMMENTED OUT. IT NEEDS MASSIVE REVISIONS */

#ifdef WAS_SA /* ~~~ This all needs to be reworked to use new fns */
typedef struct { int lines,pixels,prevline;
		 int do_stats;
		 DragonImgFile * ifile; } DTK_IFILE;
#else
typedef struct { int lines,pixels,prevline;
		 int do_stats;
		 IMGSTATS * hstats;  // only used for WRITING files
                 int bits_per_pix;
		 char * name; } DTK_IFILE;
#endif
#define IFILE_DEFINED
typedef DTK_IFILE * IFILEHANDLE;
//#include "werror.h"
#include "dtk6.h"
extern int fileerror;	/*  in TOOLFILE.C */
#include "toolerr.h"

/*********************************************
 * global and static variables and constants *
 *********************************************
 */
/* ~~~ TEMPORARY */
#define	FID_ImageFileLines 100 
#define	FID_ImageFileName 101 
#define	FID_ImageFilePixels 102
#define FID_ImageFileReadOpen 103
#define FID_ImageFileWriteOpen 103

//#if !defined TEST

/*************************************************************************
 *
 *		disk image file access for SA and DR
 **************************************************************************/

#ifdef NOTNEEDED
static int remap_imgfile_err(const int filestatus)
	/*	change class ImageFile errors to toolkit errors
	 *	also set fileerror
	 */
    {
    return(fileerror=DTKE_OB_BASE+filestatus);
    }
#endif

int dtk_ImageFileClose(const IFILEHANDLE handle)
	/*	Release storage associated with image file processing
	 *	Conceptually completes a set of operations on a DRAGON
	 *	image file, identified by the passed IFILEHANDLE, and
	 *	releases storage associated with the file handle
	 *	structure. This function is used for images that were
	 *	opened for reading or for writing.
	 *
	 *      If the file was opened for writing, and the user requested
	 *      the toolkit to accumulate statistics, this function
	 *      completes the statistics calculations and updates that
	 *      information in the image file's header.
	 *
	 *	Returns 0 or error code.
	 *
	 *	ERRORS : Return DTKE_BADHANDLE if handle invalid
	 *		 or error status from 	dtk_ImageFileName(),
	 *					dtk_ImageFileGetHdr(),
	 *					dtk_ImageHdrRewrite()
	 */
    {
/*
printf(">dtk_ImageFileClose handle=%p handle->ifile=%p\n",handle,handle->ifile);
*/
#ifdef NOTYET
    int status;
    if (handle == NULL)
	return(Error(DTKE_BADHANDLE,"%1",FID_ImageFileClose,NULL));
    fileerror=0;
    if (handle->ifile == NULL)
	return(Error(DTKE_BADHANDLE,"%1",FID_ImageFileClose,NULL));
    delete handle->ifile;
    if (handle->name == NULL)
	return(Error(DTKE_BADHANDLE,"%1",FID_ImageFileClose,NULL));
    if ((handle->do_stats) && (handle->hstats))
	{
	FinishLineCalc(handle->hstats);
	status = SaveHdrStats(handle->name,handle->hstats,NULL);
	if (status < 0)
	    return status;
        ImgStatsFree(handle->hstats);
	}
    free(handle->name);
    free(handle);
#endif
    return DTKE_OK;
    }

int dtk_ImageFileGetLine(const IFILEHANDLE handle, const int linenum,
	    const size_t bufsize,byte * buf, const int ipix, const int npix)
	/*	Read a line from DRAGON image file.
	 *	Read all or part of the data in one line ('linenum') of a
	 *	DRAGON image file into user-supplied buffer 'buf'
	 *	of size 'bufsize' (the data will be truncated to fit if nec.).
	 *	A call to dtk_ImageFileReadOpen must
	 *	precede calls to this function, in order to obtain
	 *	'handle'.
	 *
	 *	Read starts at pixel number 'ipix', for a total of 'npix'
	 *	pixels. 'buffer must point to a structure allocated by the
	 *	caller. Now handles short int pixels as well as byte-sized
         *      pixels.
	 *
	 *	Returns the number of bytes actually read, or error
	 *	code.
	 *
	 *	ERRORS : Return DTKE_BADHANDLE if handle invalid
	 *		 Return DTKE_IMGLINETOOBIG
	 *			  if read would exceed the number of lines
	 *			  in image header
?	 *			DTKE_FILEOPEN 	if not found
?	 *			DTKE_FILESEEK	if seek error
?	 *			DTKE_FILEREAD	if read error
	 *		 or error status from 	dtk_read(),
	 */
    {
#ifdef NOTYET
    int status;
    long offset;
    int bytespp;
    int locline;
    if (handle == NULL)
	return(Error(DTKE_BADHANDLE,"%1",FID_ImageFileGetLine,NULL));
    locline = (linenum < 0) ? handle->prevline+1 : linenum;
    if (locline >= handle->lines)
	{
	char numbuf[D_NUMBUF];    /* used to turn ints to char* in msg handling */
	return Error(DTKE_IMGLINETOOBIG,"%1 %2",
		FID_ImageFileGetLine,itoa(locline,numbuf,10));
	}
    if (linenum >= 0)
	handle->prevline = linenum-1;
#ifdef SA
    fileerror=0;
    status = handle->ifile->read_line(buf,bufsize,-1,
			++(handle->prevline),ipix,npix);
    return (status < 0) ? remap_imgfile_err(status) /* should push err msg */
			: status;
#else
    bytespp = handle->bits_per_pix >> 3;
    offset = (long) sizeof(IHEAD)
	+ ((long) ++(handle->prevline) * (long) handle->pixels * (long) bytespp)
	+ ((long) ipix * (long) bytespp);
    return dtk_read(handle->name,offset,buf,bufsize); // (npix * bytespp));
#endif
#endif
    return 1;  /* ~~~ TEMP - remove */
    }

int dtk_ImageFileLines(const IFILEHANDLE handle)
	/*	Return number of lines in an open image
	 *	file identified by 'handle'. This can be either an input
	 *	or an output image file. For an output file, this
	 *	function returns the intended total number of lines (i.e.
	 *	the value that will be in the header), not the current
	 *	number of lines.
	 *
	 *	Return number of lines
	 *
	 *	ERRORS : Returns DTKE_BADHANDLE if invalid handle
	 */
    {
    return (handle == NULL)
	? DTKE_BADHANDLE
	: handle->lines;
    }


int dtk_ImageFileName(const IFILEHANDLE handle, char* fname)
	/*	Copies the complete filename associated with the
	 *      passed 'handle' to 'fname', which must be large enough
	 *      to hold the string, plus terminating 0.
	 *
	 *	Return 0 or error if invalid handle.
	 *
	 *	ERRORS : Returns DTKE_BADHANDLE if invalid handle
	 */
    {
    if (handle == NULL)
	return DTKE_BADHANDLE;
#ifdef WAS_SA
    strcpy(fname,handle->ifile->fullfilename());
#else
    strcpy(fname,handle->name);
#endif
    return 0;
    }

int dtk_ImageFilePixels(const IFILEHANDLE handle)
	/*	Return number of pixels per line in an open image file
	 *	identified by 'handle'. This can be either an input or an
	 *	output image file.
	 *
	 *	Return number of pixels per line, or error code
	 *
	 *	ERRORS : Returns DTKE_BADHANDLE if invalid handle
	 */
    {
    return (handle == NULL)
	? DTKE_BADHANDLE
	: handle->pixels;
    }

int dtk_ImageFilePutLine(IFILEHANDLE handle, const int linenum,
				const byte * buf)
	/*	Write a line of data to an open DRAGON image file.
	 *	Writes image data from a user-supplied buffer to line
	 *	'linenum' of a DRAGON image file identified by 'handle'.
	 *	A call to dtk_ImageFileWriteOpen must precede calls to
	 *	this function, in order to obtain a handle with which to
	 *	identify the file and specify the dimensions of the
	 *	output file. The number of bytes written from the buffer
	 *	is determined by the number of pixels per line field in
	 *	the header (passed in the dtk_ImageFileWriteOpen call). It
	 *	is the caller's responsibility to insure that the buffer
	 *	contains that much data.
	 *
	 *	Normally this function will be called to append lines
	 *	sequentially to an image file. In this case, 'linenum'
	 *	can be specified as -1, indicating the "next" line.
	 *	However, this function can also be used, with care, to
	 *	re-write lines that have already been written. In this
	 *	case, 'linenum' should be non-negative and less than the
	 *	total number of lines in the file as specified by the
	 *	header. Furthermore, it must be no more than 1 + the line
	 *	number of the last line written. If 'linenum' does not
	 *	conform to these constraints, the function will return an
	 *	error code.
	 *
	 *      Note this function will accumulate histogram and other
	 *      statistics information on the data written if the
	 *      file referenced by 'handle' was opened with 'do_stat' set
	 *      to a non-zero value.
         *
         *      1/7/95 	Now handles ushort data as well as byte data. Still
         *      returns #BYTES written, NOT #pixels
	 *
 	 *	Returns the number of bytes written, or error code
	 *
	 *	ERRORS : Return DTKE_BADHANDLE if handle invalid
	 *		 	DTKE_IMGLINETOOBIG
	 *			  if write would exceed the number of lines
	 *			  in image header
	 *		 	DTKE_FILEOUTPUTGAP
	 *			  if write would leave a gap before specified
	 *			  line number
	 *		 Return file i/o errors during append operation
?	 *			DTKE_FILEAPPNDOPEN if unable to open for append
?	 *			DTKE_FILEAPPEND if write error while appending
?	 *			DTKE_FILEAPPCLOSE if close error while appending
	 *		 Return file i/o errors during overwrite operation
?	 *			DTKE_FILEWRTOPEN if unable to open for overwrite
?	 *			DTKE_FILEWRTSEEK if unable to locate overwrite
	 *			  location
?	 *			DTKE_FILEWRITE if write error while overwriting
?	 *			DTKE_FILEWRTCLOSE if close error while
	 *			  overwriting
	 *		 or error status from 	dtk_Write(),
	 */
    {
    int status=0;
#ifdef NOTYET
    int locline=linenum;
    long longstatus=0;
#ifndef WAS_SA
    long offset;
    int bytespp;
#endif
    if (handle == NULL)
	return(Error(DTKE_BADHANDLE,"%1",FID_ImageFilePutLine,NULL));
    locline = (linenum < 0) ? handle->prevline+1 : linenum;
    if (locline >= handle->lines)
	{
	char numbuf[D_NUMBUF];    /* used to turn ints to char* in msg handling */
	return Error(DTKE_IMGLINETOOBIG,"%1 %2",
	    FID_ImageFilePutLine,itoa(locline,numbuf,10));
	}
    if (linenum > (handle->prevline+1))
	return Error(DTKE_FILEOUTPUTGAP,"%1",FID_ImageFilePutLine,NULL);
    if ((linenum < 0) || (linenum == 1+(handle->prevline)))
	locline = ++handle->prevline;

#ifdef SA
    fileerror=0;
	/* (byte far *) cast in next line is to avoid recompiling IMAGFILE now */
    status = handle->ifile->write_line(buf,0,-1,locline,0,handle->pixels);
    return (status < 0) ? remap_imgfile_err(status)
			: status;
#else
    if (handle->do_stats)
	NextLineCalc(buf,NULL,0,handle->hstats);
    bytespp = handle->bits_per_pix >> 3;
    offset = (long) sizeof(IHEAD) + 
             ((long) locline * (long) handle->pixels * (long) bytespp);
    if ((linenum < 0) || (linenum == 1+(handle->prevline)))
	status = dtk_write(handle->name,buf,(handle->pixels*bytespp));
    else
	{
	longstatus = wsfo(handle->name,buf,
                (handle->pixels*bytespp),offset);
	status = (longstatus < 0L) ? remap_file_error(longstatus) : longstatus;
	}
    return status;
#endif
#endif
    return status; /* ~~~ TEMP */
    }

IFILEHANDLE dtk_ImageFileReadOpen(const char * filename)
	/*	Prepare a (DRAGON) image file for reading
	 *	This routine accesses DRAGON image file 'filename', reads
	 *	its header, and saves relevant information for later
	 *	queries. It constructs an an image file descriptor and
	 *	returns a pointer to this structure (an IFILEHANDLE).
	 *	This handle is passed to other functions in order to
	 *	identify the file to be queried, read, closed, etc.
	 *
	 *	Return file descriptor handle or NULL if error.
 	 *
	 *	ERRORS : Set fileerror to DTKE_BADFILENAME if bad file name
	 *				  DTKE_NOMEM if insufficient low memory
	 *				  DTKE_FILE_NOT_DRAGON_IMG if invalid
	 *					file structure
	 *		 or error status from 	dtk_read(),
?	 *		or remapped imagefile error #
	 */
    {
    char name[FMSIZE];
    IFILEHANDLE handle=NULL;
    long expected_size, real_size;
    int status = 0;
    status = dtk_FilenameBuild(filename,NULL,"IMG",name,sizeof(name));
    fileerror=0;
    //printf("toolifil::ReadOpen name='%s' status=%d\n",name,status);
    if (status < 0)
	{
	fileerror = DTKE_BADFILENAME;
	return NULL;
	}
    if ((handle = (IFILEHANDLE) malloc(sizeof(DTK_IFILE))) == NULL)
	{
	fileerror = DTKE_NOMEM;
        free(handle);
	return NULL;
	}
    //printf("toolifil::ReadOpen handle=%p\n",handle);
    handle->prevline = -1;	/* latest line to have been read */
#ifdef NOTYET
#ifdef SA
    fileerror=0;
	/* 4/10/2002 ~~ try using fastread ('R' instead of 'r') */
    if(((handle->ifile = new DragonImgFile('R',4096)) == NULL)
	    || (handle->ifile->error())
	    || (handle->ifile->access((signed char *)name)) )
	{
        //printf("toolifil::ReadOpen ifile=%p err=%ld\n",handle->ifile,
	//(long)(handle->ifile->error()));
	if (handle->ifile == NULL)
	    fileerror = Error(DTKE_NOMEM,"%1",FID_ImageFileReadOpen,NULL);
	else
	    remap_imgfile_err(handle->ifile->error());
	return NULL;
	}
    handle->lines = handle->ifile->flines();
    handle->pixels = handle->ifile->fpixels();
    handle->do_stats = 0;
#else
    handle->hstats = NULL;
    if ((handle->name = TO_CHARPTR malloc(1+strlen(name))) == NULL)
	{
	fileerror = Error(DTKE_NOMEM,"%1",FID_ImageFileReadOpen,NULL);
	return NULL;
	}
    strcpy(handle->name,name);
        {  /* block to delay allocation of hdr */
        IHEAD * hdr = TO_IHEADPTR calloc(1,sizeof(IHEAD));
        if (hdr == NULL)
           {
   	   fileerror = Error(DTKE_NOMEM,"%1",FID_ImageFileReadOpen,NULL);
           return NULL;
           }
        if((status = dtk_read(name,0L,(byte *)hdr,sizeof(IHEAD))) < 0)
	   {
           fileerror=status;
	   free(hdr);
           free(handle->name);
           free(handle);
	   return NULL;
           }
        handle->lines=hdr->fields.size[0];
        handle->pixels=hdr->fields.size[1];
        handle->do_stats = 0;
        handle->bits_per_pix = (hdr->fields.bits_per_pix > 8) ?
                    hdr->fields.bits_per_pix : 8; 
        free(hdr);
        }
#endif
#endif
    expected_size = (long) handle->lines * (long) handle->pixels;
    expected_size += sizeof(IHEAD);
    real_size = file_size(name);
    //printf("toolifil::ReadOpen expectedsize=%ld real=%ld\n",
      //      expected_size,real_size);
    if (expected_size > real_size)  /* not a dragon file!! */
	{
	fileerror = dtk_Error(DTKE_NOT_DRAGON_IMG,
              "In %1, %2 is not a valid DRAGON image file",
              "dtk_ImageFileReadOpen",name);
	return NULL;
	}
    return handle;
    }

IFILEHANDLE dtk_ImageFileWriteOpen(const char * filename,const IHEAD* hdr,
				   const char * filetype,const int do_stats)
	/*	Prepare a new (DRAGON) image file for writing
	 *	Create a new DRAGON image file named 'filename', writes a
	 *	header to the file using data in 'hdr', and then
	 *	constructs an image file descriptor and returns a pointer
	 *	to this structure (an IFILEHANDLE). This handle is passed
	 *	to other functions in order to identify the file to be
	 *	queried, written to, closed, etc.]
	 *
	 *	The IHEAD structure pointed to by 'hdr' can be blank,
	 *	with the exception that it must have the number of lines
	 *	and number of pixels elements (hdr->fields.size[0] and
	 *	hdr->fields.size[1]) set to the dimensions of the image
	 *	that will be written.
         *
         *      1/7/95 if image to be written is > 8 bits per pix, must
         *      have bits per pix field set as well, otherwise will assume
         *      8 bits per pix.
	 *
	 *      'filetype' is a (one character) string that should hold
	 *      one of the following:
	 *
	 *      "I"   for a normal image file
	 *      "C"   for a classified file  (nominal values, max val 63)
	 *      "L"   for a layer file (nominal values, 0 to 255)
	 *
	 *      If the first character in 'filetype' does not match
	 *      one of these characters, "I" is assumed. This value is
	 * 	stored in the header of the output file.
	 *
	 *      If 'do_stats' is non-zero, the toolkit will accumulate
	 *      information to calculate file statistics each time a new
	 *      line is written to this file with dtk_ImageFilePutLine.
	 *      Statistics will be finally calculated and written to
	 *      the file header when dtk_ImageFileClose is called with
	 *      the handle returned by this function.
	 *
	 *	If a file named 'filename' already exists, it will be
	 *	overwritten.
	 *
	 *	Return file descriptor handle or NULL if error.
	 *
	 *	ERRORS : Set fileerror to DTKE_BADFILENAME if bad file name
	 *				  DTKE_INVALIDHDR if hdr parameters
	 *					wrong or not initialized
	 *				  DTKE_NOMEM if insufficient low memory
	 *		 or error status from 	dtk_write(),
?	 *		or remapped imagefile error #
	 */
    {
    IHEAD * localhdr = NULL;  /* local copy so we can change filename field */
    IFILEHANDLE handle=NULL;
#ifdef NOTYET
    char name[FMSIZE];
    int status = dtk_FilenameBuild(filename,NULL,"IMG",name,sizeof(name));
    fileerror=0;
    if ((status < 0) && (status != DTKE_FILENOTFOUND))
	{
	fileerror = Error(DTKE_BADFILENAME,"%1 %2",
	                  FID_ImageFileWriteOpen,filename);
	return NULL;
	}
    //printf("toolifil::writeopen hdr=%p\n",hdr); 
    if ((hdr == NULL) || (hdr->fields.size[0]==0) || (hdr->fields.size[1]==0))
	{
	fileerror=Error(DTKE_INVALIDHDR,"%1",FID_ImageFileWriteOpen,NULL);
	return NULL;
	}
    if ((handle = (IFILEHANDLE) malloc(sizeof(DTK_IFILE))) == NULL)
	{
	return NULL;
	}
    if ((localhdr = TO_IHEADPTR malloc(sizeof(IHEAD))) == NULL)
	{
	fileerror=Error(DTKE_NOMEM,"%1",FID_ImageFileWriteOpen,NULL);
	free(handle);
	return NULL;
	}
    //printf("toolifil::writeopen localhdr=%p handle=%p\n",localhdr,handle); 
    memcpy(localhdr,hdr,sizeof(IHEAD));  /* copy the passed header info */

    localhdr->fields.ftype[0] = toupper(filetype[0]);
    if ((localhdr->fields.ftype[0] != 'C') 
             && (localhdr->fields.ftype[0] != 'L'))
	localhdr->fields.ftype[0] = 'I';

    handle->lines = localhdr->fields.size[0];
    handle->pixels = localhdr->fields.size[1];
    // printf("toolifil::writeopen about to SetHdrVals\n"); 
    SetHdrVals(localhdr,NULL,name,NULL,NULL,NULL,0);
    /* this will parse the filename and save only node + ext */
    handle->prevline = -1;	/* latest line to have been written */
    handle->do_stats = do_stats;

#ifdef SA
    fileerror=0;
    //printf("toolifil::writeopen about to create DragonImgFile for write\n"); 
	/* 4/10/2002 ~~ try using fastread ('W' instead of 'w') */
    if (((handle->ifile = new DragonImgFile('W',4096))==NULL)
	    || handle->ifile->error()
	    || (handle->ifile->access((signed char *)name,handle->pixels,
		handle->lines,localhdr->fields.bits_per_pix) < 0) )
        {	
	//printf("toolifil::writeopen ifile=%p err=%ls\n",handle->ifile,
	//(long)(handle->ifile->error())); 
	if (handle->ifile == NULL)
	    fileerror=Error(DTKE_NOMEM,"%1",FID_ImageFileWriteOpen,NULL);
	else
	    remap_imgfile_err(handle->ifile->error());
	free(handle);
	free(localhdr);
	return NULL;
	}
    /* if ok, setup for write */
    //printf("toolifil::writeopen about to setup_write\n"); 
    if (handle->ifile->setup_write(localhdr,do_stats) < 0)
	{
	remap_imgfile_err(handle->ifile->error());
 	free(handle);
	free(localhdr);
	return NULL;
	}
#else // SA
    if (do_stats)
        {
        handle->hstats = ImgStatsAlloc();
        if (handle->hstats == NULL)
	    {
            fileerror=Error(DTKE_NOMEM,"%1",FID_ImageFileWriteOpen,NULL);
            free(handle);
	    return NULL;
	    }
	InitLineCalc(handle->lines,handle->pixels,
            localhdr->fields.bits_per_pix,
            ((localhdr->fields.bits_per_pix > 8) ? 2 : 1),          
            handle->hstats);
        }
    else
        handle->hstats = NULL; 

    handle->bits_per_pix = (localhdr->fields.bits_per_pix > 8) ?
                             localhdr->fields.bits_per_pix : 8;
    if((handle->name = TO_CHARPTR malloc(1+strlen(name))) == NULL)
	{
	fileerror=Error(DTKE_NOMEM,"%1",FID_ImageFileWriteOpen,NULL);
        if (handle->hstats)
            ImgStatsFree(handle->hstats);
 	free(handle);
	free(localhdr);
	return NULL;
	}
    strcpy(handle->name,name);
    if (access(name,F_OK) == 0)  /* file exists */
        remove(name);            /* delete it   */
    if((status = dtk_write(name,(byte *)localhdr,sizeof(IHEAD))) < 0)
	{
	fileerror=status;
        if (handle->hstats)
            ImgStatsFree(handle->hstats);
 	free(handle);
	free(localhdr);
	return NULL;
	}
#endif // SA
#endif
    free(localhdr);
    //printf("toolifil::writeopen (ex) handle=%p\n",handle); 
    return handle;
    }

/***************************************************************
 *  Query functions. 
 ***************************************************************
 */
/**/
#ifdef NOMORE // use img_acc 2005-8-1
int dtk_MaxPixels()
          /* return maximum image width, i.e. working pixels
           */
    {
	// return uWorkingPixels;
    return getWorkingPixels(); // D_DFLTIMGPIX;
    /* ~~~ This is probably not what we want to do here... */
    }

int dtk_MaxLines()
          /* return maximum image length, i.e. working lines
           */
    {
	//return uWorkingLines;
    return getWorkingLines(); //D_DFLTIMGLINES;
    }

int dtk_MaxImages()
          /* return maximum number of image buffers. Note that 
             for V4.0, this is NOT working images, but rather
             D_DFLTIMAGES from dlimits.h.
           */
    {
    return (D_DFLTIMAGES);
    }
#endif
/**/

void TOOLIFIL_END()     { puts(FIL_ID); }

#ifdef TEST
/***************************************************************
 *  TEST CODE STARTS HERE.  COMPILE THIS TO ITOOLTST.OBJ and
 *  link to ITOOLTST.EXE.
 ***************************************************************
 */

#include <stdlib.h>

/* ~~~ This test module presently doesn't do much. Needs
   to be enhanced.
*/

char * Banner[] =
    { 	"DRAGON Toolkit Rev 4.0 Image Memory and File Test Program",
	"Copyright (c) 1993 Goldin-Rudahl Systems, Inc.",
	"" } ;
char * Help[] =
    {	"\nusage: toolitst {-f | -m | -l | -e}",
	"-f\ttest dtk_ImageFile... functions",
	"-m\ttest dtk_ImageMem ... functions",
	"-l\ttest dtk_ImageFileLoad & Save functions",
	"-e\ttest error handling for dtk_ImageMem... functions",
	"" } ;


int fileflag=0,memflag=0,loadflag=0,ertstflag = 0;

CMDDESCRIPTOR cmds[] =
    {
    'f',0,dtk6_CmdSetFlag,&fileflag,
    'm',0,dtk6_CmdSetFlag,&memflag,
    'l',0,dtk6_CmdSetFlag,&loadflag,
    'e',0,dtk6_CmdSetFlag,&ertstflag,
    0
    } ;

int main(int argc,char **argv)
    {
    char buf[80];
    int status;
    int iError = 0;

    dtk_init(NULL);
    dtk_banner(Banner);
    dtk_qhelp(argc,argv,Help);
    if (argc < 2)
	dtk_help(Help);
    status=dtk_ProcessCommandLine(argc,argv,cmds,&iError);
    if (iError < 0)
	{
	sprintf(buf,"ERROR - CommandLine status=%d",iError);
	dtk_ErrorMsgPush(buf);
	}
    else
	{
	sprintf(buf,
	"CommandLine status=%d; next token is %s; remaining tokens: %d",
		status,*(argv+status),argc-status);
	dtk_ShowMsg(0,buf);
	}
    printf("DRAGON %s running\n",
	(dtk_DragonIsRunning()) ? "IS" : "is NOT");
    /**
    printf("DRAGON version is %ld; toolkit version is %ld\n",
	dtk_DragonVersion(),dtk_ToolkitVersion());
    **/
    }

#endif  /* TEST */
