#include "drelease.h"
#ifdef DRAGON_IF
 ID_ IMAGFILE_CPP_IDA[]
    = "\0@(#) " __FILE__ " $Revision: 1.6 $$Date: 2014/12/17 07:20:39 $";
//#else
// ID_ IMAGFILE_CPP_IDB[]
//   = "\0@(#) " __FILE__ " $Revision: 1.6 $$Date: 2014/12/17 07:20:39 $";
#endif
D_REL_IDSTR;
//static char sccsidV[] = "(@)# $RCSfile: imagfile.cpp,v $ $Date: 2014/12/17 07:20:39 $ $Revision: 1.6 $";
/****************************************************************/
/*
 *		>> IMAGFILE.CPP <<
 *
 *          by K.T. Rudahl
 *          $Revision: 1.6 $ $Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1991-2014 Kurt Rudahl and Sally Goldin
 *	    ~~ EndC
 ***************************************************
 *  $Id: imagfile.cpp,v 1.6 2014/12/17 07:20:39 rudahl Exp $
 *  $Log: imagfile.cpp,v $
 *  Revision 1.6  2014/12/17 07:20:39  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.5  2004/12/23 12:17:35  rudahl
 *  added unistd.h for linux
 *
 *  Revision 1.4  2002/06/10 12:33:53  rudahl
 *  updated TIFF-related fns to MSC4.1
 *
 *  Revision 1.3  2002/04/17 23:09:45  rudahl
 *  fixups for 32-bit, long filenames
 *
 *  Revision 1.2  2002/04/09 21:34:51  rudahl
 *  adapt for long filenames, & fixed bugs
 *
 *  Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *  first checkin of only SOME common dirs
 *
 *  Revision 4.4  1997/09/10  04:40:04  tower
 *  checkin for class class5_0
 *
 *  Revision 4.3  1997/09/10  04:40:04  tower
 *  checkin for class CLASS5_0
 *
 * Revision 4.1  1994/12/12  13:23:08  tower
 *   Released with DRAGON 4.1 12/94
 * Revision 4.0  1993/12/15  11:56:56  tower
 *   updated for use with initial released version of DRAGON programmer's toolkit.
 * Revision 1.4  92/06/02  18:34:35  tower
 *  For Zortech 3.0 and first release of TIF2DRAG & DRAGSCAN
 *  This is the first released version of this file
 * 	Revision 1.3  92/04/30  14:40:50  tower
 *	for 3.05: fixed constructors; extracted derived classes to other files
 * 	Revision 1.2  92/03/08  12:22:03  tower
 * 	for 3.05 utilities. Major changes for use with OB.CPP
 *
 ***************************************************
 *
 *	IMAGFILE.H & .CPP provide two functions:
 *	  1. define IMAGEFILECORE structure which contains processing-time
 *		image structure parameters, portable across
 *		different image formats. This can be used in
 *		standard C programs.
 *	  2. define a class called ImageFile to provide a uniform
 *		programming interface for common image file access
 *		functions. Typically, a particular image file format
 *		is implemented as a descendent of ImageFile, redefining 
 *		as many of the access functions as necessary.
 *	     to conserve code space, some of the descendent classes
 *		are conditionally compiled.
 *	     the available access functions are:
 *		read_line()	reads an image file line
 *		write_line()	writes an image file line
 *		idiopix(), idiolines(), idiopixbits(), idiobands()
 *				virtual fns to get values from file header
 *		fpixels(), flines(), pixbits(), bands()
 *				to get values from IMAGEFILECORE
 *		initcore()	to set values in IMAGEFILECORE
 *		setup_write()	to initialize idioheaders for new files
 *		setup_read()	to rewind files, and permit reading subimages
 *		   // the following are inherited from class File &/| class OB
 *		   // (partial list)
 *		about()		return a string describing the file
 *		operator=()	copy a file
 *		printOn() 	print (on stdout) info about file
 *		dumpOn(detail) 	dump (on stdout) detailed info about file
 *		error()		return errn
 *		flush()		finish writing buffer, & empty buffers
 *		size() 		how big is file
 *		fileOK()	is it a valid name, and does it exist?
 *		errormsg()	create string describing error condition
 *
 * derived classes are located in several files, as follows:
 *	BASE_IF		ImageFile		imagfile.cpp
 *	DRAGON_IF	DragonImgFile		imagfile.cpp
 *	ERDAS_IF	ErdasFile		erdfile.cpp
 *	FAST_IF		EOSAT FAST format file
 *	IDRISI_IF	IdrisiIFile (& IdrisiVFile ?)
 *	TIFF_IF		TiffFile		tifffile.cpp
 *	ZUCCHINI_IF	ZuccFile
 *
 ****************************************************************/
/*    Modification History
 *
 *    Version		Who		What & Why
 *    1.0    2/22/91	ktr	Created
 *           3/10/91    seg     Added Idrisi file type - for
 *                              "glial" routines
 *	     4/9/91     ktr	added Tiff file type for FCONVERT
 *				added is() member fn.
 *				added conditional defines, and changed
 *				dIdrisiFile to dIdrisiIFile (img file)
 *    1.1    8/29/91	ktr	revised to use File, FileHeader classes
 *				defined in ob.h, ob.cpp
 *	     12/20/91   ktr	added 'confidence' return to fileOK()
 *				and to which_file()
 *				added 'band_id()' 
 *				added Erdas file reading & multiband reading
 *    1.2    3/92	ktr	partitioned out most of the derived
 *				class definitions into ERDFILE, etc
 *	     3/22/92	ktr	restructured constructors; added
 *				'access' function
 *    1.3    5/26/92	ktr	updated to Zortech 3.0
 *	     5/30/92	ktr	Automatically calc. hdr stats while writing
 *	     6/1/92 	ktr	Added errormsg()	
 *    1.4    8/14/92	ktr	changed zortech.h --> dtypes.h & dlimits.h
 *	     6/27/94 ktr	fixed call to SaveHdrStats
 *	     7/23/94 seg	Use IMGSTATS not HDRSTATS now
 *	    12/12/94 ktr	changed ftype in header to ftype[]
 *    4.2   1/6/95   ktr	split (for each file type) into three
 *				  compilation units: core, read, and write fns
 *				revised write_line() to eliminate unneeded
 *				  (& wrong) stuff about partial line writes,
 *				   and to handle multi & partial byte pixels.
 *				revised read_line to handle multi & partial byte
 *				   pixels
 *				Fixed initcore to set pitch correctly for
 *				  multibyte pixels.
 *				added provision for access() (write version)
 *				and init() to pass nbands & nbits to initcore
 *	12/95			adapt for Watcom 10.0 & MSC8
 *	2/15/97 ktr	shortened some compile logical names.
 * 5.4	12/22/2004 ktr	adapt to linux with unistd .h
 ****************************************************************/

/**/ 

//#ifdef ITEST
#define BASE_IF		// ImageFile
#define DRAGON_IF	// DragonIFile
//#define ERDAS_IF	// ErdasFile
//#define FAST_IF	// EosatFile
//#define IDRISI_IF	// IdrisiIFile (& IdrisiVFile ?)
//#define TIFF_IF		// TiffFile
//#define ZUCCHINI_IF	// ZuccFile
//#endif

#include <stdio.h>
#include <stdlib.h>
#if defined __GCC__
#include <unistd.h>
#else
#include <dos.h>
#include <io.h>
#endif
#include <string.h>
#include <fcntl.h>
#include <ctype.h>
#include <time.h>
//#include <sys\stat.h>

#include "dtypes.h"
#include "dlimits.h"
extern "C" {
#include	"ztoolkit.h"
#include	"zfilespc.h"
#include        "zfile.h"
#include "files.h"
#include "iff.h"
#include "filename.h"
  }

#include "dhead.h"	/* for IHEAD structure */
#include "hdrstats.h"
	/* the following are needed for imagfile.h */
#include "foreign.h"	/* for Zucchini,Erdas,EPPL7-must FOLLOW DHEAD.H */
#include "tiff.hpp"

#ifndef FARNULL
#define FARNULL (void far *) 0L
#endif

#include "toolerr.h"
#include "ob.h"
#include "imagfile.h"

/**********************************************************
 *
 *	file buffering, if vfiles not in use
 *
 **********************************************************/

/**********************************************************
 *
 *	ImageFile class
 *
 **********************************************************/

#ifdef BASE_IF

#if defined BASECORE
extern "C" void IMAGFILE_BASECORE() {}

char IMAGFILE_BC_ID[] = __FILE__ ;

void ImageFile::initcore(const long pix,const long lines,
			 const int bits,const int bands)
	//	init. IMGCORE from supplied parameters
    {
//    imgcore.pixbits = (bits==-1) ? idiopixbits() : bits;
    if (mode == 'r')	//  none of the args are supplied or used
	{
	imgcore.pixbits = idiopixbits();
	imgcore.fpixels = idiopix();
	imgcore.flines = idiolines();
	fbands = idiobands();
	setup_read();
	}
    else		// all of the args are required
	{
	imgcore.pixbits = bits;
	imgcore.fpixels = pix;
	imgcore.flines = lines;
	fbands = bands;
	setup_write();
	}
    if ((imgcore.pixbits < 1) || (imgcore.pixbits > 32))
	errn = FILE_WRITEHDR_BADARG;
    long pitchbits = (long) imgcore.fpixels * (long) imgcore.pixbits + 7L;
//    fbands = (bands==-1) ? idiobands() : bands;
    pitch = (pitchbits/8) * fbands;
    }

const int ImageFile::access(const signed char * fname,const int buffersize,
				void far * idiobuf,const int idiosize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
	//	Return <0 -> error
	//
	//	This only works  for 'read', but DragonImgFile::about()
	//	links to it nevertheless so it must be in common
    {
memtest(82);
    if (mode != 'r')
	return FILE_WRONGMODE;
    int tmp = File::access((char *)fname,buffersize);
    if (tmp<0)
	return tmp;
    tmp = init();	// default pix, lines = 0,0
    if (tmp<0)
	return tmp;
    if ((idiobuf != FARNULL) && (idiosize >= hdr->idiosize()))
	b_memcpy(idiobuf,NEAR2FAR(hdr->idiohdr()),hdr->idiosize());
    hdr->release();	// release idioheader buffer
memtest(83);
    return tmp;
    }

#endif // #if defined BASECORE

#if defined BASEREAD
extern "C" void IMAGFILE_BASEREAD() {}

int ImageFile::read_line(byte far * buf,const int buflen,const int band,
		const int lineno,const int ipix,const int npix)
	//	read line of data into 'buf' ('buflen' is actual length of buf
	//	'lineno' 'ipix' 'npix' specify what part of which line to read
	//	If 'npix' == -1, read to end of line (checking will fit in buf)
	//	If 'lineno' == -1, use & increment 'currentline'
	//	return #PIX read from file, <0 => error
	//	'band' for multiband types only; count is from 0
	//	For this fn, multiband files are assumed to be line-interleaved
	//	(like Erdas). This won't work for TIFF
	//	This prototypical fn will work for most single-band file types.
    {
    int lastpix = (npix==-1) ? imgcore.fpixels : ipix+npix;
    long linelen = (long)(lastpix - ipix) * (long)(imgcore.pixbits + 7L);
	// bits we want to read; 7L for roundoff to bytes below
    int locband = (band == -1) ? curband : band;
	// calc bit # of first desired pixel; cvt to byte # below
    long linoffset = ((long)(imgcore.fpixels*locband)+(long)ipix)
		* (long)imgcore.pixbits;
    if (lineno >= 0)
	currentline = lineno;
    linoffset /= 8;
    long diskloc = (long)(hdr->idiosize())+(long)pitch*currentline
	+linoffset;
//	+(long)(imgcore.fpixels*locband)+(long)ipix;
    linelen /= 8;
    if (linelen > buflen)
	linelen = buflen;		// don't overflow buffer
    int rpix = read(buf, linelen, diskloc); // reading too few is not an error
//    bufofset += (pitch - rpix);		// up to next scan line
    /*
    //    if (currentline > 2048)
        {
//	printf(">Read_line %ld (%d pix): "
//	       "diskloc=%ld, buflen=%d (hdrsize=%d, pitch=%d)\n",
//	       currentline,linelen,diskloc,buflen,hdr->idiosize(),pitch);
//printf("\tcount = %d : %x %x %x %x %x %x %x %x\n",rpix,
//	buf[0],buf[1],buf[2],buf[3],
//	buf[4],buf[5],buf[6],buf[7]);
	}
	*/
    currentline += lineincr;
    return rpix;
    }

#endif // #if defined BASEREAD

//#define MAXIPIX 4096	// biggest partial-line we can write

#if defined BASEWRITE
extern "C" void IMAGFILE_BASEWRITE() {}

const int ImageFile::access(const signed char * fname,
	    const long pix,const long lines,
	    const int bits,const int bands,const int buffersize)
	//	This version of access() is different for write-modes only
	//	and permits setting target IMGCORE parameters
	//	idiohdr is created, init by imagcore, and released when the
	//	File::write command writes the header
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
	//	Return <0 -> error
    {
memtest(84);
    if (mode == 'r')
	return FILE_WRONGMODE;
    int tmp = File::access((char *)fname,buffersize);
    if (tmp<0)
	return tmp;
    return init(pix,lines,bits,bands);
    }

int ImageFile::write_line(byte far * buf,const int buflen,const int band,
		const int lineno,const int ipix,const int npix)
	//	write line of data from 'buf' ('buflen' is actual length of buf
	//	'lineno' specifies which line to write ( != -1 permits rewrites)
	//	write data starting at buf[0].
	//	'ipix' MUST be 0; 'npix' MUST be -1 or fpixels; buflen ignored.

	//	NOMORE take data starting at buf[0], placing it into the 'ipix'-th
	//	NOMORE position in the output line. 'npix' specifies how many pix
	//	NOMORE if 'npix' == -1. write entire line.
	//	If 'lineno' == -1, use & increment 'currentline'
	//	return #data BYTES written to file, <0 => error
	//	This prototypical fn will work for most single-band file types.
    {
    byte far * bufptr=buf;
    ushort writesize;
    if (lineno >= 0)
	currentline = lineno;
    if (ipix || ((npix > 0) && (npix < imgcore.fpixels)) ) // partial-line write?
	return (errn=FILE_UNIMPLEMENTED);
    writesize=imgcore.fpixels;
    if (imgcore.pixbits > 8)
	writesize *= (imgcore.pixbits>>3);
    else if (imgcore.pixbits < 8)	// assumes 1,2,or 4 bpp
	writesize /= (8 / imgcore.pixbits);
#ifdef NOMOTE	// wrong anyway
    if (ipix || ((npix > 0) && (npix < imgcore.fpixels))
	    || (buflen < imgcore.fpixels)) // partial-line write?
	{
	int lastpix = (npix==-1) ? imgcore.fpixels : ipix+npix;
	int linelen = lastpix - ipix;	// length we want to write
	byte locbuf[MAXIMGPIX];
	memset(locbuf,0,sizeof(locbuf));	// set to black
	if (linelen > buflen)
	    linelen = buflen;		// don't overflow buffer
	b_memcpy(NEAR2FAR(locbuf+ipix),buf,linelen);
	bufptr=NEAR2FAR(locbuf);
	}
#endif
    long diskloc = (long)(hdr->idiosize())+(long)pitch*currentline++;
    int rpix=write(bufptr,writesize,diskloc);
/*
//printf("write_line writing %ld pixels at location %ld\n",
//	imgcore.fpixels,diskloc);
//printf("\thdrsize=%d, pitch=%d, currentline=%ld\n",
//	hdr->idiosize(),pitch,currentline-1);
*/
    if ((rpix < imgcore.fpixels) && (errn == 0))
	errn = FILE_BADWRITE;
    return rpix;
    }
#endif // #if defined BASEWRITE

#if defined BASEREAD
const int ImageFile::setup_read(const int band,const long ipix,const long iline,
	 	    const int skippix,const int skipline)
	//	setup header for reading. 
	//	In simplest case (no args), just rewinds file
	//	otherwise can be used to limit reading (using 'read_line' with
	//	minimal parameters) to only part of an image file. 
	//	Any explicit 'read_line' parameters override these settings.
	// 	    NOTES 'skippix' not yet being used by anybody
	//		'band' used only by multiband file types
	//		only 'iline' & 'band' used by 'write_line'
	//	Return -1 if invalid parameters else 0
    {
    curband=band;		// read band number (default=0)
    currentline=iline;		// next line to read (incr. by read_line)
    startpix=ipix;		// initial pixel number (default=0)
    pixincr=skippix;		// incrementer in pix loop (default=1)
    lineincr=skipline;		// incrementer in line loop (default=1)
    return 0;
    }
extern "C" void IMAGFILE_BASEREAD_END() {}
#endif // #if defined BASEREAD

#if defined BASECORE
const char ** ImageFile::about(const int detail)
	//	return descriptive string:
	//	detail == 0-2 use File::about()
	//		  3 => name & image size; 4 => adds classname
	//		  5 => up to three lines of info - filetype specific
	//		  6 => up to 128 lines of info
    {
    char tmp[FMSIZE+150] = "\0";
    if (errn==0)
	{
	switch(detail)
	    {
	    default:
	    case 4:	
	    case 3:	sprintf(&tmp[strlen(tmp)],"%s %ld x %ld, %d band%s",
			    File::about(2)[0],fpixels(),flines(),bands(),
			    (bands()>1)?"s":"");
			break;
	    case 2:
	    case 1:
	    case 0:	strcpy(tmp,File::about(detail)[0]); break;
	    }
	}
    isA()->obdesc_put(tmp);	// call File::about() first to clear array
    return isA()->obdesc();
    }

const char * ImageFile::errormsg(char * buf,const int bufsiz)
    {
    int bufleft=bufsiz-1;
    if (bufsiz==0)
	return "Double Error";
    memset(buf,0,bufsiz);
    strcpy(buf,czFileName);
    strcat(buf," : ");
    bufleft -= strlen(buf);
    if ((bufleft -= strlen(errorstr())) < 0)
	return buf; 
    strcat(buf,errorstr());
    return buf;
    }
extern "C" void IMAGFILE_BASECORE_END() {}
#endif // #if defined BASECORE

#if defined BASEWRITE
void ImageFile::operator=(ImageFile& src)
	//	copy one imagefile to another. 
	//	Assumes setup_write has been done
	//	copy is done line-by-line, and will be the upper-left
	//	corner of 'src' if 'this' is smaller than 'src'
    {
    byte * locbuf = new byte[imgcore.fpixels];
//printf("copying from %s\n",src.about(1)[0]);
//printf("        to %s:\n",about(1)[0]);
//printf("buf[%ld]=%p; lines=%ld\n",imgcore.fpixels,locbuf,imgcore.flines);
    if (locbuf == NULL)
	{
	errn = FILE_NOMEM;
	return;
	}
    memset(locbuf,0,imgcore.fpixels);
    byte far * locbufptr = TO_FARBYTEPTR NEAR2FAR(locbuf);
    int i,tmp1=0;
    for (i=0;i<imgcore.flines;i++)
	{
	if (src.currentline >= src.imgcore.flines)
	    memset(locbuf,0,imgcore.fpixels);
	else    
	    {
	    tmp1 = src.read_line(locbufptr,imgcore.fpixels);
	    if ( (tmp1 < src.imgcore.fpixels-src.startpix)
		    && (tmp1 < imgcore.fpixels) && (src.errn == 0) )
	        {
		printf("imagfile::operator= readerr "
		       "lineno %d tmp1=%d fpix=%d spix=%d\n",
		       i,tmp1,src.imgcore.fpixels,src.startpix);
		src.errn = FILE_BADREAD;
		}
	    }
	if ( (write_line(locbufptr,imgcore.fpixels) < imgcore.fpixels)
	        && (errn == 0) )
	     errn = FILE_BADWRITE;
	if (error() || src.error())
	    break;
	}
//printf("copy done at line %d: read count=%d, status=%d, err=%d\n",
//	i-1,tmp1,src.error(),error());
#if defined MSC || defined __WATCOMC__
    delete locbuf;
#else
    delete [imgcore.fpixels] locbuf;
#endif
    flush();
    }
extern "C" void IMAGFILE_BASEWRITE_END() {}
#endif // #if defined BASEWRITE

#endif	// BASE_IF
/**********************************************************
 *
 *	DragonImgFile class
 *
 **********************************************************/

#ifdef DRAGON_IF

#if defined DRAGCORE
extern "C" void IMAGFILE_DRAGONCORE() {}

DragonImgFile::DragonImgFile(const int fmode,const int buffersize)
	//	fmode:  'r' => read; 'W' => fastread	
	//		'W' => fast version of 'w'
	//		'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    File::init(fmode,buffersize);
    hdrstatsptr = NULL;
    verifier = DragonImgFile::verify_filename;
    }

DragonImgFile::~DragonImgFile()
    { 
    if (hdrstatsptr)	// presumably it's a write not a read
	{
	FinishLineCalc(hdrstatsptr);
	SaveHdrStats(czFileName,hdrstatsptr,FARNULL);
	ImgStatsFree(hdrstatsptr);
	hdrstatsptr=NULL;
	}
    isA()->obdesc_zap(); 
    }

const int DragonImgFile::init(const long pix,const long lines,
			const int bits,const int bands)
	//	this fn called only by access()
	//	creates an idiohdr 
	//	if 'r' mode, read header & initialize imagcore from it
	//	else set imagcore from pix,lines & call setup_write
    {
    hdr->file = this;
    hdr->header = new IHEAD; 
    if (hdr->header == NULL)
	return(errn = FILE_NOMEM);
    hdr->init(this,sizeof(IHEAD),0); // read header at offset 0
/*
//fprintf(stdout,">draginit: DRAGON Image File Header initialized: image is %d x %d\n",
//	((IHEAD *)hdr->header)->fields.size[1],	
//	((IHEAD *)hdr->header)->fields.size[0]);
*/
    if (errn)
	return errn;
    initcore(pix,lines,bits,bands);
    return errn;
    }

const int DragonImgFile::idiopixbits() const
   {
   short bpp=idiohdr()->fields.bits_per_pix;
   return (bpp) ? bpp : 8;
   }

#endif // #if defined DRAGCORE

#if defined DRAGWRITE
extern "C" void IMAGFILE_DRAGONWRITE() {}

const int DragonImgFile::setup_write(const void * ihdr,const int do_stats)
	//	setup header for writing, based on supplied header or,
	//	if 'ihdr' == NULL, based on IMGCORE
	//	if 'do_stats' (default=1), setup to accumulate statistics.
	//	in either case, filename comes from current 'name',
	//	& lines & pixels come from IMGCORE
    {
    currentline=0;		// next line to write (incr. by 1)
    if (!do_stats && hdrstatsptr)
	{
	ImgStatsFree(hdrstatsptr);
	hdrstatsptr=NULL;
	}
    if (do_stats && (hdrstatsptr==NULL))
	hdrstatsptr = ImgStatsAlloc();
    if ((hdr == NULL) || (idiohdr() == NULL) || (hdr->idiosize() < sizeof(IHEAD))
	    || (do_stats && (hdrstatsptr == NULL)) )
	return -1;
    hdr->hdr_written_flag = 0;	// needs to be written or rewritten
    IHEAD * hptr = (IHEAD *) idiohdr();
    if (ihdr == NULL)		// else is supplied by calling fn 
	{	/* these are DRAGON-specific fns in HDRSTATS.C*/
	InitNewHdr(hptr,flines(),fpixels()); // setup for writing
	SetHdrVals(hptr,"I",czFileName,NULL,NULL,NULL,0);

		// this needs to be expanded to init more draghdr flds
		// perhaps by doing stat. analysis?
	hptr->fields.clf[0] = (byte) strlen("DEFGRA.CLF");
	strcpy(&hptr->fields.clf[1],"DEFGRA.CLF");
	}
    else
	memcpy(hptr,ihdr,sizeof(IHEAD));
		//    init CalcStats structure for single file
//printf(">setup_write: hdrstatsptr=%p this=%p guards=%x %x\n",
//	hdrstatsptr,this,guard1,guard2);
    if (do_stats)
	InitLineCalc(flines(),fpixels(),hptr->fields.bits_per_pix,
             ((hptr->fields.bits_per_pix > 8) ? 2 : 1),hdrstatsptr);
    return 0;
    }

int DragonImgFile::write_line(byte far * buf,const int buflen,const int band,
		const int lineno,const int ipix,const int npix)
	//	same as for ImageFile, but also calcs statistics for new file
    {
    int status = ImageFile::write_line(buf,buflen,band,lineno,ipix,npix);
    if (hdrstatsptr)
	NextLineCalc(buf,FARNULL,0,hdrstatsptr);
    return status;
    }

void DragonImgFile::operator=(ImageFile& src)
    { ImageFile::operator=(src); }

extern "C" void IMAGFILE_DRAGONWRITE_END() {}
#endif // #if defined DRAGWRITE

#if defined DRAGCORE
const int DragonImgFile::capabilities()
    {
    return(C_IDENTIFY | C_TEST | C_READ_HDR | C_WRITE_HDR | C_READ | C_WRITE);
    }

const char * DragonImgFile::band_id(const int band,const int detail)
	//	return a string identifying the specified band
	//	If 'detail'==0, return full string
	//	else a 1-char long string for synthesizing file names
	//	Return NULL if no multiband capabilities exist
    {
    return NULL;
    }

const char ** DragonImgFile::about(const int detail)
	//	return descriptive string:
	//	detail == 0-4 use ImageFile::about()
	//		  5 => up to two lines of info - adds comment
	//		  6 => more info - filetype specific
	//		  7 => lots of lines of info - not for DRAGON
    {
    const char ** retval = ImageFile::about(detail); // clear array, set line 0
    if ( (errn==0) && (detail > 4) )
	{
	IHEAD * idioh=new IHEAD;
	if (idioh == NULL)
	    return retval;
		// following is 'read' version of access(); won't work
		// unless it's a read file
	access((signed char *)czFileName,0,NEAR2FAR(idioh),sizeof(IHEAD));
	switch(detail)
	    {
	    case 6:
	    default:
		char tmp[80];
		sprintf(tmp,"scene: %-16s \tsubscene: %-16s \tband: %-3s",
		    	idioh->fields.scene+1,idioh->fields.subscene+1,
		    	idioh->fields.band+1);
		isA()->obdesc_put(tmp,2);
		sprintf(tmp,"filetype %c \t\t\tsource: %-3s",
		    	idioh->fields.ftype[0],idioh->fields.source+1);
		isA()->obdesc_put(tmp,3);	// fall through
	    case 5:
		if (strlen(idioh->fields.comment) > 1)
		    isA()->obdesc_put(idioh->fields.comment+1,1);
		break;
	    }
	delete idioh;
	}
    return retval;
    }

static Class class_DragonImgFile("DRAGON Image File",4);

Class * DragonImgFile::isA() const
	{ return &class_DragonImgFile; }
const Class * DragonImgFile::desc() 
	{ return &class_DragonImgFile; }
#endif // #if defined DRAGCORE

#endif	//	DRAGON_IF

#ifdef BASE_IF
#if defined DRAGCORE

const int DragonImgFile::verify_filename(char * result, 
			const int mode, const char * root)
	//	construct full path + file name in result
	//	'result' is a FMSIZE-byte pre-alloc'd buffer.
	//	return != 0 if input file unacceptable for some reason
	//	file must exist and may have other reqs.
    {
      //printf("DragonImFile::verify_filename (en)\n");
    int status=parse_filename(result,mode,root,"IMG",NULL);
    //printf("DragonImFile::verify_filename result='%s' status=%d\n",
    //		 result,status);
    if ((status < 0) || (mode != 'r'))
	return status;	// will be 0 if OK
    return (::access(result,F_OK)) ? FILE_NOT_FOUND : 0; // no validation test
    }

const int DragonImgFile::fileOK(const char * name)
	//	test whether 'name' is one of these. 
	//	Return >=0 if yes, errn<0 if no
	//	A 'yes' response is in range 0-9, indicating "confidence"
	//	This fn must be replicated for each derived class
    {
    char ebuf[FMSIZE];
    unsigned size[2];
    int tmp=verify_filename(ebuf,'r',name);
//printf("DragonImgFile fileOK: %s status=%d\n",name,tmp);
    if (tmp < 0)
	return tmp;
    if (rsf(ebuf,NEAR2FAR(size),sizeof(size),0,0) < sizeof(size))
	return FILE_READHDRERR;
    long reqsize= (long)sizeof(IHEAD)+(long)size[0]*(long)size[1];
    if (file_size(ebuf) == reqsize)
	return 9;
    else if (file_size(ebuf) > reqsize)
	return 5;	// too big
    return 1;		// too small
    }
extern "C" void IMAGFILE_DRAGONCORE_END() {}
#endif // DRAGCORE
#endif // ifdef BASE_IF

/**********************************************************
 *
 *	ErdasFile class
 *
 **********************************************************/

#ifdef BASE_IF
#if defined ERDASCORE
extern "C" void IMAGFILE_ERDASCORE() {}

const int ErdasFile::verify_filename(char * result, 
			const int mode, const char * root)
	//	construct full path + file name in result
	//	'result' is a FMSIZE-byte pre-alloc'd buffer.
	//	return != 0 if input file unacceptable for some reason
	//	file must exist and may have other reqs.
    {
    int status=parse_filename(result,mode,root,"LAN",NULL);
    if ((status < 0) || (mode != 'r'))
	return status;
    return (::access(result,F_OK)) ? FILE_NOT_FOUND : 0;	// no validation test
    }

const int ErdasFile::fileOK(const char * name)
	//	test whether 'name' is one of these. 
	//	Return >=0 if yes, errn<0 if no
	//	A 'yes' response is in range 0-9, indicating "confidence"
	//	This fn must be replicated for each derived class
    {
    char ebuf[FMSIZE];
    int tmp=verify_filename(ebuf,'r',name);
    return (tmp<0) ? tmp : 9;
    }

ErdasFile::~ErdasFile()
   { isA()->obdesc_zap(); } ;

extern "C" void IMAGFILE_ERDASCORE_END() {}
#endif
#endif	// BASE_IF

#ifdef OLDD
	// 	constructor - 
	//	if im_info==NULL, read hdr & init imageinfo
	// 	else, write hdr (creating file?) based
	//		on either idiohdr or just info in imageinfo
    {
    initinfo(im_info);
//    filetype = ERDAS_I;
    strcpy(imageinfo.hdrtype,"Erdas");
    idiohdrsize = sizeof(ERDHEAD);
//printf("dErdasFile constructor: %s %s\n",
//	(im_info) ? "writing to" : "reading from",fileroot);
    setupinfo(fileroot,im_info);
    }

char * dErdasFile::parse_outfile_name(char * root)
	//	construct full path + file name in imageinfo
    {
    imageinfo.errn=dImageFile::parse_outfile_name(imageinfo.fname,root,
	    "LAN",NULL);
    return (imageinfo.errn == 0) ? imageinfo.fname : NULL ;
    }

int dErdasFile::write_idiohdr(char * root)
	//	write hdr based on imageinfo
	//	if 'fname'==NULL, use name in imageinfo
	//	else copy fname into imageinfo
	//	if idiohdr==NULL, create hdr from info in
	//	imageinfo; then delete hdr on exit
	//	NOTE: this uses erd74 format
	//	return <0 => error
    {
    char * fname=root;
    ERD74HEAD * erdhdr = new ERD74HEAD;
    if (fname==NULL)
	fname=imageinfo.fname;
    if (imageinfo.idiohdr != NULL)
	memcpy(erdhdr,imageinfo.idiohdr,sizeof(ERD74HEAD));
    else
	{
	memset(erdhdr,0,sizeof(ERD74HEAD));
	erdhdr->nrow = imageinfo.lines;
	erdhdr->ncol = imageinfo.pix;
		// this needs to be expanded to init more hdr flds
		// perhaps by doing stat. analysis?
	erdhdr->nband=1;
	memcpy(erdhdr,"HEAD74",strlen("HEAD74"));
	}
    if (wsf(fname,NEAR2FAR(erdhdr),sizeof(ERD74HEAD),WSF_TRUNC)
	    < (int)sizeof(ERD74HEAD))
	{
	delete erdhdr;
	return(imageinfo.errn=II_WRITEERR);
	}
    delete erdhdr;
    return 0;
    }

int dErdasFile::is(char * rootname,char **reasonmsg)
	//	is 'rootname' an instance of this imagefiletype?
    {
    *reasonmsg=NULL;
    char tmp[II_FNAME_SZ];
    int retval=dImageFile::parse_infile_name(tmp,rootname,"LAN",NULL);
    if (retval != 0)	// II_NAMEERR or II_FINDERR
	*reasonmsg = "File not found";
    return retval;
    }
#endif

// #endif ERDAS_IF

/**********************************************************
 *
 *	IdrisiIFile class
 *
 **********************************************************/

#ifdef IDRISI_IF

static Class class_IdrisiImgFile("Idrisi Image File",2);

IdrisiImgFile :: IdrisiImgFile(const char * fname,const int fmode,const int buffersize)
    : File(IdrisiImgFile::verify_filename,fname,fmode,buffersize),
      ImageFile(fname,fmode,buffersize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    if (idriinit() == 0)
	{
	if (mode == 'r')
	    initcore();
	else
	    {
	    initcore(0,0);
	    setup_write();
	    }
	}
    }

IdrisiImgFile::IdrisiImgFile(const char * fname,const int fmode,
	    const long pix,const long lines,const int buffersize)
    : File(IdrisiImgFile::verify_filename,fname,fmode,buffersize),
      ImageFile(fname,fmode,buffersize)
	//	This version of constructor is different for write-modes only
	//	and permits setting target IMGCORE parameters
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    if (idriinit() == 0)
	{
	if (mode == 'r')
	    initcore();
	else
	    {
	    initcore(pix,lines);
	    setup_write();
	    }
	}
    }

const int IdrisiImgFile::verify_filename(char * result, 
			const int mode, const char * root)
	//	construct full path + file name in result
	//	'result' is a FMSIZE-byte pre-alloc'd buffer.
	//	return != 0 if input file unacceptable for some reason
	//	file must exist and may have other reqs.
    {
    int status=parse_filename(result,mode,root,"IMG",NULL);
//printf("IdrisiImg::verify_filename - status=%d, result=%s\n",status,result);  
//    if ((status < 0) || (mode != 'r'))
	return status;
    return (::access(result,F_OK)) ? FILE_NOT_FOUND : 0;	// no validation test
    }

const char * IdrisiImgFile::band_id(const int band,const int detail)
	//	return a string identifying the specified band
	//	If 'detail'==0, return full string
	//	else a 1-char long string for synthesizing file names
	//	Return NULL if no multiband capabilities exist
    {
    return NULL;
    }

Class * IdrisiImgFile::isA() const
	{ return &class_IdrisiImgFile; }
const Class * IdrisiImgFile::desc() 
	{ return &class_IdrisiImgFile; }
const int IdrisiImgFile::fileOK(const char * name)
	//	test whether 'name' is one of these. 
	//	Return 0 if yes, errn if no
	//	This fn must be replicated for each derived class
    {
    char ebuf[FMSIZE];
    int tmp=verify_filename(ebuf,'r',name);
//printf("IdrisiImgFile fileOK: %s status=%d\n",name,tmp);
    return tmp;
    }

#ifdef OLD
dIdrisiIFile::dIdrisiIFile(char * fileroot,IMAGEINFO * im_info)
	// 	constructor - 
	//	if im_info==NULL, read hdr & init imageinfo
	// 	else, write hdr (creating file?) based
	//		on either idiohdr or just info in imageinfo
    {
    initinfo(im_info);
//    filetype = IDRISI_I;
    strcpy(imageinfo.hdrtype,"Idrisi");
    idiohdrsize = 0;  // Idrisi does not carry header in the file
//printf("dIdrisiIFile constructor: %s %s\n",
//	(im_info) ? "writing to" : "reading from",fileroot);
    setupinfo(fileroot,im_info);
    }

char * dIdrisiIFile::parse_infile_name(char * root)
	//	construct full path + file name in imageinfo
	//	return ptr to it, or NULL if file not found or invalid
    {
    imageinfo.errn=dImageFile::parse_infile_name(imageinfo.fname,root,
	    "IMG",NULL);
    return (imageinfo.errn == 0) ? imageinfo.fname : NULL ;
    }

char * dIdrisiIFile::parse_outfile_name(char * root)
	//	construct full path + file name in imageinfo
	//	return ptr to it, or NULL if bad form
    {
    imageinfo.errn=dImageFile::parse_outfile_name(imageinfo.fname,root,
	    "IMG",NULL);
    return (imageinfo.errn == 0) ? imageinfo.fname : NULL ;
    }

int dIdrisiIFile::read_idiohdr(char * root)
	//	read Idrisi document file and init imageinfo and
        //      idr_info structure in the class instance.
	//	if 'fname'==NULL, use name in imageinfo
	//	else copy fname into imageinfo
	//	return <0 => error
    {
    char * fname=root;
    unsigned date,time;
    int attr;
    char docfile[64];
    char * nodeptr;
    char line[80];
    char* delim;
    char* spaceptr;
    FILE* fp;
    int cls;

    if (fname==NULL)
	fname=imageinfo.fname;
    strcpy(docfile,fname);
    nodeptr = strchr(docfile,'.');
    if (nodeptr)
        {
        *nodeptr = '\0';
        }
    strcat(docfile,".doc");                  
    fp = fopen(docfile,"r");
    if (!fp)
       {
       return (imageinfo.errn = II_READERR);
       }
    while (fgets(line,80,fp))
       {
       delim = strchr(line,':');
       delim+=2; /* skip delim plus leading space */
       if (strstr(line,"image title"))
           {
           strcpy(idr_info.title,delim);
           trimstring(idr_info.title);
           }
       else if (strstr(line,"file type"))
           {
           strcpy(idr_info.ftype,delim);
           trimstring(idr_info.ftype);
           }
       else if (strstr(line,"data type"))
           {
           strcpy(idr_info.datatype,delim);
           trimstring(idr_info.datatype);
           }
       else if (strstr(line,"rows"))
           {
           sscanf(delim,"%ld",&(imageinfo.lines));
           }
       else if (strstr(line,"columns"))
           {
           sscanf(delim,"%ld",&(imageinfo.pix));
           }
       else if (strstr(line,"minimum"))
           {
           sscanf(delim,"%lf",&(idr_info.min));
           }
       else if (strstr(line,"maximum"))
           {
           sscanf(delim,"%lf",&(idr_info.max));
           }
       else if (strstr(line,"cell x"))
           {
           sscanf(delim,"%lf",&(idr_info.cellx));
           }
       else if (strstr(line,"cell y"))
           {
           sscanf(delim,"%lf",&(idr_info.celly));
           }
       else if (strstr(line,"legend"))
           {
           sscanf(delim,"%d",&(idr_info.nclass));
           strcpy(idr_info.cnames[0],"Unclass.");
           }
       else if (strstr(line,"category"))
           {
           spaceptr = strchr(line,' ');
           sscanf(spaceptr,"%d",&cls);
           if (cls <= 16)
               {
               strncpy(idr_info.cnames[cls],delim,32);
               idr_info.cnames[cls][32] = '\0';
               trimstring(idr_info.cnames[cls]);
               } 
           }
       }
    fclose(fp);
    // now, initialize standard struct based on this info
    imageinfo.bands = 1;
    if (strcmpl(idr_info.datatype,"byte")==0) 
        imageinfo.depth = 8;
    else if (strcmpl(idr_info.datatype,"integer")==0) 
        imageinfo.depth = 16;
    else 
        imageinfo.depth = 32;  // real numbers... 
    imageinfo.minval = (SINT16) idr_info.min;
    imageinfo.maxval = (SINT16) idr_info.max;
    imageinfo.errn = 0;  // no err so far
    imageinfo.idiohdr = NULL;
    if ((attr=fileinfo(fname,&date,&time)) >= 0)
	filedate(imageinfo.date,date);
    pitch = imageinfo.pix*imageinfo.bands;
    }

	
int dIdrisiIFile::write_idiohdr(char * root)
	//	write doc file based on imageinfo & idr_info
	//	if 'fname'==NULL, use name in imageinfo
	//	else copy fname into imageinfo
	//	return <0 => error
    {
    char * fname=root;
    int status = 0;
    FILE* fp;
    int i;
    char docfile[64];
    char * nodeptr;
    char line[80];

    if (fname==NULL)
	fname=imageinfo.fname;
    strcpy(docfile,fname);
    nodeptr = strchr(docfile,'.');
    if (nodeptr)
        {
        *nodeptr = '\0';
        }
    strcat(docfile,".doc");                  

    fp = fopen(docfile,"w");
    if (!fp)
        return II_WRITEERR;
    status = fprintf(fp,"image title : %s\n",idr_info.title);
    if (status < 0)
        {
        fclose(fp);
        return status;
        }
    status = fprintf(fp,"data type   : %s\nfile type   : %s\n",
        idr_info.datatype,idr_info.ftype);          
    if (status < 0)
        {
        fclose(fp);
        return status;
        }
    status = fprintf(fp,"rows        : %d\ncolumns     : %d\n",
              imageinfo.lines,imageinfo.pix);
    if (status < 0)
        {
        fclose(fp);
        return status;
        }
    status = fprintf(fp,"minimum     :   %15.10E\nmaximum     :   %15.10E\n",
              (double)imageinfo.minval,(double)imageinfo.maxval);      
    if (status < 0)
        {
        fclose(fp);
        return status;
        }
    status = fprintf(fp,"cell x      :   %15.10E\ncell y      :   %15.10E\n",
               idr_info.cellx,idr_info.celly);          
    if (status < 0)
        {
        fclose(fp);
        return status;
        }
    if (idr_info.nclass == 0)
        status = fprintf(fp,"legend      : 0\n");
    else 
        {
        status = fprintf(fp,"legend      : %d\n",
             idr_info.nclass);
        for (i=1; i <= idr_info.nclass; i++)
           fprintf(fp,"category %2d : %s\n",i,
                   idr_info.cnames[i]);
        }    
    fclose(fp);
    if (status < 0)
        return status;
    else
        return 0;
    } 

int dIdrisiIFile::is(char * rootname,char **reasonmsg)
	//	is 'rootname' an instance of this imagefiletype?
    {
    *reasonmsg=NULL;
    char tmp[II_FNAME_SZ];
    int retval=dImageFile::parse_infile_name(tmp,rootname,"IMG",NULL);
    if (retval != 0)	// II_NAMEERR or II_FINDERR
	*reasonmsg = "File not found";
    return retval;
    }
#endif
#endif //ifdef IDRISI_IF

/**********************************************************
 *
 *	TiffFile class
 *
 **********************************************************/

#ifdef BASE_IF

#if defined TIFFCORE
extern "C" void IMAGFILE_TIFFCORE() {}

const int TiffFile::verify_filename(char * result, 
			const int mode, const char * root)
	//	construct full path + file name in result
	//	'result' is a FMSIZE-byte pre-alloc'd buffer.
	//	return != 0 if input file unacceptable for some reason
	//	file must exist and may have other reqs.
    {
    int status=parse_filename(result,mode,root,"TIF",NULL);
    if (mode != 'r')
	return FILE_UNIMPLEMENTED;
    if ((status < 0) || (mode != 'r'))
	return status;
    return (::access(result,F_OK)) ? FILE_NOT_FOUND : 0;	// no validation test
    }

const int TiffFile::fileOK(const char * name)
	//	test whether 'name' is one of these. 
	//	Return >=0 if yes, errn<0 if no
	//	A 'yes' response is in range 0-9, indicating "confidence"
	//	This fn must be replicated for each derived class
    {
    char ebuf[FMSIZE];
    int tmp=verify_filename(ebuf,'r',name);
    return (tmp<0) ? tmp : 9;
    }

extern "C" void IMAGFILE_TIFFCORE_END() {}
#endif // TIFFCORE
#endif 	// BASE_IF

/**********************************************************
 *
 *	ZuccFile class
 *
 **********************************************************/

#ifdef ZUCCHINI_IF

static Class class_ZuccFile("Zucchini File",256);

ZuccFile :: ZuccFile(const char * fname,const int fmode,const int buffersize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    if (init(ZuccFile::verify_filename,fname,fmode,buffersize) < 0)
	return;
    zuccinit();
    }

ZuccFile::ZuccFile(const char * fname,const int fmode,
	    const long pix,const long lines,const int buffersize)
	//	This version of constructor is different for write-modes only
	//	and permits setting target IMGCORE parameters
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    if (init(ZuccFile::verify_filename,fname,fmode,buffersize) < 0)
	return;
    zuccinit(pix,lines);
    }

const int ZuccFile::zuccinit(const long pix,const long lines)
    {
    long offset=0L;
    hdr->file = this;
    hdr->header = new ZUCHDR; /* use DRAGON header modified */
    if (hdr->header == NULL)
	return(errn = FILE_NOMEM);
    hdr->hdrsize = sizeof(ZUCHDR); 
    if (mode == 'r')
	offset = seek_iff(name,"WFSQ",0L);	// where the header gets placed in the file
    if (offset < 0)
	return(errn = FILE_BAD_IFF);
    hdr->hdroffset = offset;
    hdr->inithdr(this);	// read or clear header
    if (errn)
	return errn;
    initcore(pix,lines);
    return errn;
    }

const int ZuccFile::setup_write(const void * ihdr)
	//	setup header for writing, based on supplied header.
	//	This is DRAGON header PLUS IFF header. DRAGON header
	//	of source file MUST be initialized; it is just copied.
	//	if 'ihdr' == NULL, based on IMGCORE
	//	in either case, filename comes from current 'name',
	//	& lines & pixels come from IMGCORE
    {
    currentline=0;		// next line to write (incr. by 1)
    if ((hdr == NULL) || (idiohdr() == NULL) || (hdr->hdrsize < sizeof(IHEAD)))
	return -1;
    hdr->hdr_written_flag = 0;	// needs to be written or rewritten
    IHEAD * hptr = (IHEAD *) &idiohdr()->ihead;
    memcpy(hptr,ihdr,sizeof(IHEAD));
    return 0;
    }

int ZuccFile::read_line(byte far * buf,const int buflen,const int band,
		const int lineno,const int ipix,const int npix)
	//	read line of data into 'buf' ('buflen' is actual length of buf
	//	'lineno' 'ipix' 'npix' specify what part of which line to read
	//	If 'npix' == -1, read to end of line (checking will fit in buf)
	//	If 'lineno' == -1, use & increment 'currentline'
	//	return #PIX read from file, <0 => error
	//	'band' not used; 'lineincr' not used
    {
    int lastpix = (npix==-1) ? imgcore.fpixels : ipix+npix;
    int linelen = fpixels();
    int rpix;
    byte * locbuf = new byte[linelen*2];	// allow for Zucchini packing overhead
    if (locbuf == NULL)
	return -30;
    if ((lineno > 0) && (lineno != currentline))
	return -31;
    if (lineno == 0)
	currentline = lineno;
    if (currentline == 0)
	currentbyte = seek_iff(name,"WFSQ",0L)+sizeof(ZUCHDR);
    long diskloc = currentbyte; //hdr->hdrsize+(long)pitch*currentline+(long)ipix;
printf("Z:read_line %d; currentline=%ld; currentbyte=%ld; linelen=%d; buflen=%d\n",
	lineno,currentline,currentbyte,linelen,buflen);
    if (linelen > buflen)
	return -32;		// won't fit in buffer
    read(NEAR2FAR(locbuf), linelen*2, diskloc); // reading too few is not an error
//    bufofset += (pitch - rpix);		// up to next scan line

printf(">Read_line %ld (%d pix): diskloc=%ld, buflen=%d (hdrsize=%d, pitch=%d)\n",
       currentline,linelen,diskloc,buflen,hdr->hdrsize,pitch);

    currentline += 1;
    currentbyte += unpack(buf,locbuf,ipix,npix,&rpix);
printf("\tcount = %d : %x %x %x %x %x %x %x %x\n",rpix,
	buf[0],buf[1],buf[2],buf[3],
	buf[4],buf[5],buf[6],buf[7]);
printf("Z3:r rpix=%d currentline=%ld; currentbyte=%ld\n",
	rpix,currentline,currentbyte);
#if defined MSC || defined __WATCOMC__
    delete locbuf;
#else
    delete [linelen*2] locbuf;
#endif
    return rpix;
    }
#ifdef NOTYET
int ZuccFile::write_line(byte far * buf,const int buflen,const int band,
		const int lineno,const int ipix,const int npix)
	//	write line of data from 'buf' ('buflen' is actual length of buf
	//	'lineno' specifies which line to write ( != -1 permits rewrites)
	//	take data starting at buf[0], placing it into the 'ipix'-th
	//	position in the output line. 'npix' specifies how many pix
	//	If 'npix' == -1. write to end of line
	//	If 'lineno' == -1, use & increment 'currentline'
	//	return #data BYTES written to file, <0 => error
    {
    byte far * bufptr=buf;
    if (lineno >= 0)
	currentline = lineno;
    if (ipix || ((npix > 0) && (npix < imgcore.fpixels))
	    || (buflen < imgcore.fpixels)) // partial-line write?
	{
	int lastpix = (npix==-1) ? imgcore.fpixels : ipix+npix;
	int linelen = lastpix - ipix;	// length we want to write
	byte locbuf[MAXIMGPIX];
	memset(locbuf,0,sizeof(locbuf));	// set to black
	if (linelen > buflen)
	    linelen = buflen;		// don't overflow buffer
	b_memcpy(NEAR2FAR(locbuf+ipix),buf,linelen);
	bufptr=NEAR2FAR(locbuf);
	}
    long diskloc = (long)(hdr->hdrsize)+(long)pitch*currentline++;
    int rpix=write(bufptr,imgcore.fpixels,diskloc);
/*
printf("write_line writing %ld pixels at location %ld\n",
	imgcore.fpixels,diskloc);
printf("\thdrsize=%d, pitch=%d, currentline=%ld\n",
	hdr->hdrsize,pitch,currentline-1);
*/
    if ((rpix < imgcore.fpixels) && (errn == 0))
	errn = FILE_BADWRITE;
    return rpix;
    }
#endif

const int ZuccFile::verify_filename(char * result, 
			const int mode, const char * root)
	//	construct full path + file name in result
	//	'result' is a FMSIZE-byte pre-alloc'd buffer.
	//	return != 0 if input file unacceptable for some reason
	//	file must exist and may have other reqs.
    {
    int status=parse_filename(result,mode,root,"ZUC",NULL);
    if ((status < 0) || (mode != 'r'))
	return status;
    return (::access(result,F_OK)) ? FILE_NOT_FOUND : 0;	// no validation test
    }

Class * ZuccFile::isA() const
	{ return &class_ZuccFile; }
const Class * ZuccFile::desc() 
	{ return &class_ZuccFile; }

const int ZuccFile::fileOK(const char * name)
	//	test whether 'name' is one of these. 
	//	Return 0 if yes, errn if no
	//	This fn must be replicated for each derived class
    {
    char ebuf[FMSIZE];
    int tmp=verify_filename(ebuf,'r',name);
    return tmp;
    }

const char ** ZuccFile::about(const int detail)
	//	return descriptive string:
	//	detail == 0-4 use ImageFile::about()
	//		  5 => up to two lines of info - adds comment
	//		  6 => more info - filetype specific
	//		  7 => lots of lines of info - not for DRAGON
    {
    const char ** retval = ImageFile::about(detail); // clear array, set line 0
    if ( (errn==0) && (detail > 4) )
	{
	switch(detail)
	    {
	    case 6:
	    default:
		char tmp[80];
		sprintf(tmp,"scene: %-16s \tsubscene: %-16s \tband: %-3s",
		    idiohdr()->ihead.fields.scene+1,
		    idiohdr()->ihead.fields.subscene+1,
		    idiohdr()->ihead.fields.band+1);
		isA()->obdesc_put(tmp,2);
		sprintf(tmp,"filetype %c \t\t\tsource: %-3s",
		    idiohdr()->ihead.fields.ftype[0],
		    idiohdr()->ihead.fields.source+1);
		isA()->obdesc_put(tmp,3);	// fall through
	    case 5:
		isA()->obdesc_put(idiohdr()->ihead.fields.comment+1,1);
		break;
	    }
	}
    return retval;
    }

#define MAXBYTES 4096 * 3	/* = 8K pix * 1.5 bytes */
typedef struct xx91213
    {
    UINT16 nybcounter;  /* used as counter during filling; will= 2*bytecnt*/
    UINT16 initval;	/* first value used on line */
    byte nybbuf[MAXBYTES]; /* allow for up to 8Kpix worst case line */
    } CLINE ;
CLINE cline;

SINT16 get_nyb()
	/*	unpack next nybble. Return -1 -> error
	 */
    {
    static UINT16 fullbyte = 0;
    if ((cline.nybcounter&1)==0)
	fullbyte = cline.nybbuf[cline.nybcounter>>1];
    else
	fullbyte <<= 4;
    cline.nybcounter++;
    return (fullbyte>>4) & 0xF;
    }

static void setup_line(UINT16 val)
	/*	initialize 'cline'
	 */
    {
    cline.nybcounter=0;
    cline.initval = val;
    memset(cline.nybbuf,0,sizeof(cline.nybbuf));
    }

#define COUNT_TYPE 0
#define SPOS_TYPE 4
#define SNEG_TYPE 8
#define EXT_TYPE 0xC
#define NEG 2

int ZuccFile::remapu1(byte far * outbuf, int length, int ipix)
	/*  	unsquash input buffer 'cline' into output buffer
	 *	'length' is unsquished pixel count 
	 *	'ipix' if > 0 means skip all preceeding pixels on line.
	 *  	Return number of bytes unsquashed 
	 */ 
    {
    UINT16 pix; //,nybcount=cline.nybcounter;
    byte far * outptr = outbuf;
    int width=fpixels();
    byte * obuf=new byte[width];	/* width of original file */
    byte * optr=obuf;
    int i,j;
    SINT16 nyb;
//    cline.nybcounter=0;
    *optr++ = cline.initval;
    for (i=0 ; i<length; i++)
	{
	nyb = get_nyb();
	switch(nyb)
	    {
		/* 	#define COUNT_TYPE 0 */
	    case COUNT_TYPE:	// absolute in 3 nybbles
			pix = get_nyb()<<4;
			pix += get_nyb();
			*optr++=pix;
			break;
	    case COUNT_TYPE+1:	// repeat count of 1-3
	    case COUNT_TYPE+2:
	    case COUNT_TYPE+3:
			for (j=0 ; j<(nyb&3) ; j++)
			    {
			    pix=*(optr-1);
			    *optr++=pix;
			    }
			i += ((nyb&3)-1);
			break;
		/*	#define SPOS_TYPE 4 */
	    case SPOS_TYPE:	// increment of 1-4
	    case SPOS_TYPE+1:
	    case SPOS_TYPE+2:
	    case SPOS_TYPE+3:
			pix = *(optr-1)+(nyb&3)+1;
			*optr++=pix;
			break;
		/*	#define SNEG_TYPE 8 */
	    case SNEG_TYPE:	// decrement of 1-4
	    case SNEG_TYPE+1:
	    case SNEG_TYPE+2:
	    case SNEG_TYPE+3:
			pix = *(optr-1)-(nyb&3)-1;
			*optr++=pix;
			break;
		/*	#define EXT_TYPE 0xC */
	    case EXT_TYPE:	// 2-nyb increment of 5-20
	    case EXT_TYPE+1:
			pix = *(optr-1)+((nyb&1)<<4)+get_nyb()+5;
			*optr++ = pix;
			break;
	    case EXT_TYPE+NEG:	// 2-nyb decrement of 5-20
	    case EXT_TYPE+NEG+1:
			pix = *(optr-1)-((nyb&1)<<4)-get_nyb()-5;
			*optr++ = pix;
			break;
	    }
	}
    b_memcpy(outbuf,NEAR2FAR(obuf+ipix),length-ipix);
#if defined MSC || defined __WATCOMC__
    delete obuf;
#else
    delete [width] obuf;
#endif
    return ((cline.nybcounter+1)/2);
    }

long ZuccFile::unpack(byte far * buf,byte * locbuf,
			const int ipix,const int npix,int * &rpix)
	//	unpack a line of data from locbuf, copying 'npix' values
	//	starting at 'ipix' into 'buf'. 
	//	Set 'rpix' to the count of pixels unpacked.
	//	unsquish image using 1-D compression
	//	Return the number of bytes used in the decoding or <0=error
    {
    int pix=fpixels();
    static UINT32 ob=0,ib=0;	/* tally compression ratio */
    static int line = 0;
    setup_line(0xFF & *locbuf);
    memcpy(cline.nybbuf,locbuf,sizeof(cline.nybbuf));
    int unpcount = remapu1(buf,pix,ipix);
    *rpix = (npix>0) ? npix : pix-ipix;
  ib += (long)pix;
  ob += (long)unpcount;
  printf("Line %d used %d bytes out of %d: current compression %ld%%\r",
        line++,unpcount,pix,100*ob/ib);
    return (long)unpcount;
    }


#endif // ifdef ZUCCHINI_IF

/**********************************************************
 *
 *	utilities
 *
 **********************************************************/

#ifdef BASE_IF_X

void filedate(char * buf,unsigned date)
	//	convert file date to ascii string - DOS format
	//	'date' is format returned by e.g. dos_getftime & stats
	//	'buf' (at least 12 chars) is filled by string
	//	same routine with slightly diff. args is used in rpanel
    {
    int d1=1980+(date>>9), d2=(date>>5)&0xF, d3=date&0x1F;
    strcpy(buf,"1900/00/00");
    itoa(d1,buf,10);	// 4-digit year
    itoa(d2,((d2>9) ? (buf+5) : (buf+6)),10);	// month
    itoa(d3,((d3>9) ? (buf+8) : (buf+9)),10);	// day
    buf[4]=buf[7]='/';	/* they got zapped by itoa */
    }

int fileextn(char * ext,const char * name)
	//	copy extension (if any) from 'name' into 'ext' (no '.')
	//	return 3 or 0
    {
    char *p;
    int x;
    *ext = '\0';
    if((x = strlen(name)) > 0) 
    	for(p = name+x; x > 0; x--) 
	    switch(*--p)
	    {
	    case '.': 	strncpy(ext,p+1,4); return 3; break;
	    case '/':
	    case '\\':
	    case ':': 	return(0); break;
	    }
    return(0);
    }

filenode(char * node,char * name)
    {
    char *p, *extptr;
    int x;
    *node = '\0';
    if((x = strlen(name)) == 0) 
	return 0;	/* not found */
    for(p = extptr = name+x; x > 0; x--) 
	switch(*--p)
	    {
	    case '.': 	extptr = p; break;
	    case '/':
	    case '\\':
	    case ':': 	x=-1; break;
	    }
    if (x == -1)
	p += 1;		/* past delimiter */
    x = extptr - p ;
    strncpy(node,p,x);
    * (char *) &node[x] = 0;
    return 1;
    }

void trimstring(char * instring)
          /* trim trailing blanks and newlines from string */
    {
    int i;
    i = strlen(instring) - 1;
    while ((i >= 0) && isspace(instring[i]))
        i--;
    instring[++i] = '\0';  
    }
#endif // ifdef BASE_IF_X

//==================================================================
//
// 	test routines
//
//==================================================================


#define pr_exit(a,b) puts(a),exit(b)
	// following not permitted with CLSERROR routine
//extern "C" UINT32 errstat_get(UINT16 module,UINT32 flags) { return 0; }

#ifdef BASE_IF
#ifdef BASECORE
char * ErrNames[] = { ERRNAMES } ;
#else
extern char * ErrNames[];
#endif
#endif
//char * FileErrNames[] = { FILENAME_ERRMSG } ;

#ifdef BASE_IF_X
enum IMAGEFILETYPE which_file(char * fname, enum IMAGEFILETYPE type,int * conf)
	//	which, if any, file type is 'fname'
	//	returns NONE_I if none, NOTEXIST_I if file not found.
	//	 BASE_I is impossible
	//	They are checked is IMAGEFILETYPE order starting at 'type', 
	//	If more than one file exists or matches, 
	//	best choice will be returned.
	//	If 'conf' non-NULL, it is set to confidence between 0-9
    {
    char tmp[FMSIZE];
    enum IMAGEFILETYPE retval=NONE_I;
    int confidence=-1,c;
    if (filename(fname,".*",NULL,EXT_DEFAULT,tmp,FINDFIRST) < 0)
	retval=NOTEXIST_I; 
    if ((type <= DRAGON_I) && ((c=DragonImgFile::fileOK(fname)) >= 0) )
	if (c > confidence)
	    {
	    confidence=c;
	    retval=DRAGON_I;
	    }
    if ((type <= ERDAS_I) && ((c=ErdasFile::fileOK(fname)) >= 0))
	if (c > confidence)
	    {
	    confidence=c;
	    retval=ERDAS_I;
	    }
/*
    if ((type <= IDRISI_I) && (dIdrisiIFile::is(fname,&errmsg) >= 0))
	retval=IDRISI_I;
*/
    if ((type <= TIFF_I) && ((c=TiffFile::fileOK(fname)) >= 0))
	if (c > confidence)
	    {
	    confidence=c;
	    retval=TIFF_I;
	    }
/*
    if ((type <= ZUCCH_I) && (ZuccFile::fileOK(fname) >= 0))
	return ZUCCH_I;
*/
    if (conf != NULL)
	*conf = confidence;
    return retval;
    }
#endif 	// BASE_IF

#ifdef IXTEST
void hist(long * table,ImageFile * inf)
    {
    int row,col;
    byte * buf = new byte[inf->fpixels()];
inf->printOn();
    inf->setup_read();	// rewind file
inf->printOn();
    memset(table,0,256*sizeof(long));
printf("hist: inf=%p\n",inf);
inf->printOn();
    for (row=0 ; row<inf->flines(); row++)
	{
	inf->read_line(buf,inf->fpixels());
	for (col = 0 ; col<inf->fpixels(); col++)
	    table[buf[col]]++;
	}
    delete buf;
    }

ImageFile * inFile=NULL, *inFile2=NULL;

mainx(int argc,char ** argv)
    {
    char errbuf[80];
    int xband = 1;	// which band to extract
    enum IMAGEFILETYPE which = NONE_I;
    char inroot[FMSIZE],outfile[64];	/* file names */
    char srchname[FMSIZE];
    int status=0,i;
    char usertype[20];
    long table[256];	/* for histogram */
    byte map[256];	/* for remap */
    usertype[0]='\0';
    while (**++argv == '-')
	{	      
	argc -= 1;
	switch(toupper((*argv)[1]))
	    {
	    case 'T':	strcpy(usertype,*++argv);
 			argc-=1;
			break;
	    case 'B':	sscanf(*++argv,"%d",&xband);
 			argc-=1;
			break;
	    default:  	printf("Unknown operation %s\n",*argv);
		      	exit(1);
		      	break;	
	    }
	}
    DragonImgFile DIF('r',4000);
    DIF.access("ind1.img");

    File * sam = new DragonImgFile('r');
printf("sam access = %d\n",sam->access("ind1.img"));
    delete sam; 

    if (DIF.error() == 0)
	{
	DIF.dumpOn();
	DragonImgFile DOF('b',4000);
	DOF.access("ind1cpy.img",100,100);
	DOF.setup_write(DIF.idiohdr());	// need a way to check this is DRAGON hdr
	DOF.dumpOn();
	DOF=DIF;
	}
    else
	printf("DIF %s\n",DIF.errormsg(errbuf,80));
//		end of OB test
    if ((--argc <= 0) || (sscanf(*argv++,"%s",inroot) < 1))
	{
	printf("no input filename supplied\n");
	return 0;
	}
    strupr(inroot);

    which =  which_file(inroot,NONE_I);
//    printf("%s autoidentified as a(n) %s file\n",inroot,TypeNames[which]);
    if (strlen(usertype))
	{
	switch(toupper(usertype[0]))
		{
		case 'D':		// DRAGON
		    which = DRAGON_I; break;
		case 'E':		// ERDAS
		    which = ERDAS_I; break;
		case 'I':		// IDRISI
		    which = IDRISI_I; break;
		case 'T':		// TIFF
		    which = TIFF_I; break;
		case 'Z':		// ZUCCHINI
		    which = ZUCCH_I; break;
		default:
		    break;
		}
	}
memtest(108);

//strcpy(inroot,"TST.IMG");
//which = DRAGON_I;
    switch(which)
	{
	case DRAGON_I:
	    DragonImgFile inFilex(inroot);
	    hist(table,&inFilex);
//	    inFile = new DragonImgFile(inroot);
	    break;
/*
	case ERDAS_I:
	    inFile = new dErdasFile(inroot,NULL);
	    break;
	case IDRISI_I:
	    inFile = new dIdrisiIFile(inroot,NULL);
	    break;
*/
	case TIFF_I:
	    TiffFile inFiley(inroot);
	    inFiley.setup_read(xband,100,100);	// band #, ul corner, & rewind
	    inFiley.dumpOn();
	DragonImgFile DOG("tiftst.img",'w',400,300,4000);
	DOG.setup_write();
	DOG.dumpOn();
	DOG=(DragonImgFile&)inFiley;
	    inFiley.setup_read(xband);	// band #, ul corner, & rewind
	    hist(table,&inFiley);
//	    inFile = new TiffFile(inroot);
	    break;
//	case ZUCCH_I:
//	    inFile = new dZucchiniFile(inroot,NULL);
//	    break;
	default:
	    break;
	}
/*
    IMAGEINFO * outinfo = new IMAGEINFO;
    memcpy((char *) outinfo,(char *)&inFile2->imageinfo,sizeof(IMAGEINFO));
    strcpy(outinfo->fname,outfile);
    dDragonIFile * outFile = new dDragonIFile(outfile,outinfo);
    if ((outFile == NULL) || outFile->error() || (outinfo == NULL))
	exit(1);
*/
//    hist(table,&inFilex);
//    buildmap(table,map,16,1);	// blue
    for (i=0 ; i<256 ; i++)
	printf("%3d=%4ld%s",i,table[i],((i%8)==7) ? "\n" : " ");

/*    hist(table,inFile2);
    buildmap(table,map2,16,16);	// red
    ifile_copy(inFile,map,inFile2,map2,outFile);	*/
	if (inFile != NULL)
	    {
	    delete inFile; 
	    inFile = NULL;
	    }
//DIF.isA()->obdesc_zap();
//DOF.isA()->obdesc_zap();
//inFile->isA()->obdesc_zap();
return 0;
	status=filename(inroot,NULL,NULL,EXT_DEFAULT,srchname,FINDNEXT);
    printf("Testing status=%d, name=%s, pattern=%s\n",status,inroot,srchname);
    if (status < 0)
	puts(ErrNames[-status]);
    }

main(int argc,char ** argv)
    {
    memtest(1000);
    mainx(argc,argv);
    memtest(1001);
    new FileHeader(NULL);
    memtest(1002);
    }

#endif
