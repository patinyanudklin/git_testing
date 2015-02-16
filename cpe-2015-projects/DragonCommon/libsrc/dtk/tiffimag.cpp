#include "drelease.h"
 ID_ TIFFIMAG_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.8 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/****************************************************************/
/*
 *		>> TIFFIMAG.CPP <<
 *
 *          by K.T. Rudahl
 *          $Revision: 1.8 $ $Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1991-2014 Kurt Rudahl and Sally Goldin
 *	    ~~ EndC
 ***************************************************/
//  $Id: tiffimag.cpp,v 1.8 2014/12/17 07:20:39 rudahl Exp $
//  $Log: tiffimag.cpp,v $
//  Revision 1.8  2014/12/17 07:20:39  rudahl
//  consolidating Dragon and OpenDragon
//
//  Revision 1.7  2004/12/23 12:14:06  rudahl
//  lint-ish fix
//
//  Revision 1.6  2004/11/30 09:45:11  rudahl
//  adapt for mingw
//
//  Revision 1.5  2002/06/10 12:33:53  rudahl
//  updated TIFF-related fns to MSC4.1
//
//  Revision 1.4  2002/04/09 21:34:51  rudahl
//  adapt for long filenames, & fixed bugs
//
//  Revision 1.3  2000/06/03 14:46:23  rudahl
//  fixes for SuSE6.3 GCC
//
//  Revision 1.2  1999/07/03 16:51:37  rudahl
//  Added TIFF_BUF_T struct
//
//  Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
//  first checkin of only SOME common dirs
//
// Revision 1.2  92/06/02  18:40:09  tower
//  For Zortech 3.0 and first release of TIF2DRAG & DRAGSCAN
//  This is the first released version of this file
// Revision 1.1  92/04/30  14:51:59  tower
//         Initial revision
//
/***************************************************
 *	This is the TIFF class definitions for use with
 *	IMAGFILE etc
 *
 ****************************************************************/
/*    Modification History
 *
 *    Version		Who		What & Why
 * 1.0	3/8/92  ktr	extracted from IMAGFILE.CPP
 * 1.1  5/26/92	ktr	updated to Zortech 3.0
 *			added level 7 to about() for TIFF
 * 1.2  7/10/92	ktr	changed idiopix, idiolines, idiobands
 *			from being inline fns
 * 4.1  1/13/95	ktr	changed calling params of init() &&
 *				initcore during read: added bits & bands
 *	12/30/95 ktr	added zfile prototypes, for compat w/ MSC etc
 * 5.0	6/22/97 ktr	some changes for Watcom just to get it to compile.
 *			Probably correct but untested.
 *      6/3/00 ktr      fixes for gcc for suSE 63
 * 5.4	11/30/2004 ktr	changed delete calls for MINGCC
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#ifdef __GCC__
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
#include "foreign.h"	/* for Zucchini,Erdas,EPPL7-must FOLLOW DHEAD.H */
#include "tiff.hpp"

#ifndef FARNULL
#define FARNULL (void far *) 0L
#endif

#define TIFF_IF
#include "toolerr.h"
#include "ob.h"
#include "imagfile.h"

/**********************************************************
 *
 *	TIFF class fns
 *
 **********************************************************/

static Class class_TiffFile("TIFF File",256);

TiffFile::TiffFile(const int fmode,const int buffersize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    File::init(fmode,buffersize);
    verifier = TiffFile::verify_filename;
//    tiffinit();
    }

TiffFile::~TiffFile()
    { 
//printf("deleting TIFF file %s\n",czFileName); 
#if defined __WATCOMC__ || defined __MINGCC__ || __GCC__
    if (strips) delete strips; 
#else
    if (strips) delete [stripcnt+1] strips; 
#endif
    isA()->obdesc_zap(); 
    }

#ifdef NOMRE
const int TiffFile::access(const char * fname,const int buffersize)
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    int tmp=File::access(fname,buffersize);
    if (tmp<0)
	return tmp;
memtest(701);
    tmp=tiffinit();	// default pix, lines = 0,0
memtest(702);
    return tmp;
    }

const int TiffFile::access(const char * fname,
	    const long pix,const long lines,const int buffersize)
	//	This version of access() is different for write-modes only
	//	and permits setting target IMGCORE parameters
	//	fmode:  'r' => read;	'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    int tmp=File::access(fname,buffersize);
    if (tmp<0)
	return tmp;
memtest(701);
    tmp=tiffinit(pix,lines);
memtest(702);
    return tmp;
    }
#endif

typedef	union { long * lbuf; short * sbuf; char * cbuf; } TIFF_BUF_T; 

const int TiffFile::init(const long pix,const long lines,
			const int bits,const int bands)
    {
    char * errmsg;
    hdr->file = this;
    hdr->init(this,0,0);
    strips = (STRIP *)NULL;
    stripcnt = 0;
    if (mode == 'r')
	{
	int count = dTag::read_std_tags(czFileName,&errmsg);
	if (count <= 0)
	    return(errn = FILE_READHDRERR);
	//printf(">Tiff::init - Reading Tiff header: w=%ld; l=%ld; stripOff=%ld\n",
	//imageWidth.get(),imageLength.get(),stripOffsets.get());
	if (!imageWidth.is() || !imageLength.is() || !stripOffsets.is() )
	    return(errn = FILE_BAD_TYPE);
		/* following not good here since interferes with reporting */
//	if ((dTag::resultspecs & TIFF_IFILE) == 0) // = anything using imagfile
//	    return(errn = FILE_BAD_STRUCT);
	initcore(pix,lines,bits,bands);

//	imgcore.fpixels=imageWidth.get();
//	imgcore.flines=imageLength.get();
//	imgcore.pixbits=8;
//	if (bitsPerSample.is())
//	    {
//	    TAGINFO taginfo;
//	    dTag tag;
//	    memcpy(&taginfo.tag,&stdtags[BitsPerSample_I].tag,
//		sizeof (struct TAG));
//	    tag.init(&taginfo);
//	    imgcore.pixbits=tag.gettypical(czFileName);
//	    }
//	fbands=samplesPerPixel.get();
	stripcnt = stripOffsets.diskitemcount();
	if (stripcnt == 0)
	    stripcnt=1;
	strips = new STRIP[1+stripcnt];
	if (strips == NULL)
	    return(errn = FILE_NOMEM);
	TIFF_BUF_T SObuf,SBCbuf;
//	union { long * lbuf; short * sbuf; } SObuf,SBCbuf;
//	switch (imgcore.pixbits)	// pitch is set wrong in initcore()
//	    {
//	    case 1: pitch = (idiopix()+7)/8; break;	// assume single band
//	    case 4: pitch = (idiopix()+1)/2; break;	// assume single band
//	    case 8: pitch = idiopix()*idiobands(); break;
//	    }
	if(stripOffsets.diskitemcount() > 0)
	    {
	    int SOshort = 0;	// boolean flag
	    int SBCshort = 0;	// boolean flag
	    if (stripOffsets.gettype() == TT_SHORT)
		{
		SOshort = 1;
		SObuf.sbuf = (short *) stripOffsets.diskitemread(czFileName);
		}
	    else
		SObuf.lbuf = (long *) stripOffsets.diskitemread(czFileName);
	    if (stripByteCounts.gettype() == TT_SHORT)
		{
		SBCshort = 1;
		SBCbuf.sbuf = (short *) stripByteCounts.diskitemread(czFileName);
		}
	    else
		SBCbuf.lbuf = (long *) stripByteCounts.diskitemread(czFileName);
	    long lincnt = 0L;
	    for (int i=0; i<stripcnt; i++)
		{
		strips[i].filepos = lincnt / ((long)pitch);
		strips[i].diskpos = 
		    (SOshort) ? *(SObuf.sbuf++) : *(SObuf.lbuf++);
		lincnt += ((SBCshort) ? *(SBCbuf.sbuf++) : *(SBCbuf.lbuf++));
//printf(">Tiff::init - strips %d: %ld %ld\n",i,strips[i].filepos,strips[i].diskpos);
		}
	    strips[stripcnt].filepos = lincnt / ((long)pitch);
	    strips[stripcnt].diskpos =0;
	    }
	else
	    {
	    strips[0].filepos = 0;
	    strips[0].diskpos = stripOffsets.get();
	    strips[1].filepos = flines();
	    strips[1].diskpos = 0;
//printf("strips 0: %ld %ld; 1: %ld %ld\n",strips[0].filepos,strips[0].diskpos,
//	strips[1].filepos,strips[1].diskpos);
	    }
	}
    else	// don't do writing yet
	{
printf("Error - TIFF writing not yet implemented\n");
	}

//printf(">TIFF::init Image File Header initialized: image is %ld x %ld\n",
//	fpixels(),flines());
//printf("\t   pitch=%d; bands=%d\n",pitch,bands());
    return errn;
    }

const int TiffFile::idiopixbits() const
	// 	return bits per pixel per band if spec'd, else 8
    {
    if (bitsPerSample.is())
	{
	TAGINFO taginfo;
	dTag tag;
	memcpy(&taginfo.tag,&stdtags[BitsPerSample_I].tag,
		sizeof (struct TAG));
	tag.init(&taginfo);
	return tag.gettypical(czFileName);
	}
    return 8;
    }

#ifdef NOTNEEDED
const int TiffFile::setup_read(const int band,const long ipix,const long iline,
	 	    const int skippix,const int skipline)
	//	setup header for reading. 
	//	In simplest case (no args), just rewinds file
	//	otherwise can be used to limit reading (using 'read_line' with
	//	minimal parameters) to only part of an image file. 
	//	Any explicit 'read_line' parameters override these settings.
	// 	    NOTES 'skippix' not yet being used by anybody
	//	Return -1 if invalid parameters else 0
    {
    int tmp=ImageFile::setup_read(band,ipix,iline,skippix,skipline);
    pitch = idiopix() * bands();
    return tmp;
    }
#endif

int TiffFile::read_line(byte far * buf,const int buflen,const int band,
			const int lineno,const int ipix,const int npix)
	//	read line of data into 'buf' ('buflen' is actual length of buf
	//	'lineno' 'ipix' 'npix' specify what part of which line to read
	//	If 'npix' == -1, read to end of line (checking will fit in buf)
	//	If 'lineno' == -1, use & increment 'currentline'
	//	return #PIX read from file, <0 => error
	//	'band' for multiband types only; count is from 0
	//	This version works for multi-strip & multi-band tiff files
	//	'pixincr' not yet implemented.
    {
    int i,jj,rpix,linelen = 0;
    int pixperbyte = 1;
    int Samp_mask = 0xFF;
    if (lineno >= 0)
	currentline = lineno;
    if (band >= 0)
	curband = band;
    for (i=0 ; i<=stripcnt; i++)
	if ((currentline >= strips[i].filepos) && (currentline < strips[i+1].filepos))
	    break;
    int lastpix = (npix==-1) ? imgcore.fpixels : ipix+npix;
    //if (currentline == 0)
    //  printf("tiffimag::read_line stripcnt=%d first line of strip %d: %ld\n",
    //       stripcnt,i,strips[i].diskpos); 
    long bufloc = strips[i].diskpos 
             + (long)pitch*(currentline-strips[i].filepos);
	/* deal with non 8-bit-per-pixels situations */
    if (imgcore.pixbits != 8)
	{
	if (fbands > 1)
	    {
	    printf("cannot read multiband TIFF file with %d bits\n",
		imgcore.pixbits);
	    return FILE_BAD_STRUCT;
	    }
	switch (imgcore.pixbits)
	    {
	    case 1:
		Samp_mask = 0x80;
		pixperbyte=8;
		break;
	    case 4:
		Samp_mask = 0xF0;
		pixperbyte=2;
		break;
	    default:		/* must be > 8 */
		printf("cannot read TIFF file with %d bits\n",imgcore.pixbits);
		return FILE_BAD_STRUCT;
//		break;
	    }	
	bufloc += (long)(ipix*fbands)/pixperbyte;	// only one band poss.
	linelen = (lastpix - ipix)/pixperbyte;	// bytes we want to read
	if (ipix % pixperbyte)
	    linelen += 1;			// allow for partial bytes
	if ((lastpix-ipix) % pixperbyte)
	    linelen += 1;			// allow for partial bytes
	}
    else	// multi-band, 8 bits per pix
	{
	bufloc += (long)(ipix*fbands) + (long) curband;	// assume band no = 0,1,2 = r,g,b
	linelen = (lastpix - ipix) * fbands;	// length we want to read
	}
    byte * locbuf = new byte[linelen];
    if (locbuf == NULL)
	return (errn = FILE_NOMEM);

    if (fbands > 1)
	{
	rpix = read(NEAR2FAR(locbuf),linelen,bufloc);
	b_memmap(buf,1+(fbands<<8),NEAR2FAR(locbuf),0xFF,(linelen/fbands),FARNULL);
	}
    else if (pixperbyte != 1)
	{
	rpix = read(NEAR2FAR(locbuf),linelen,bufloc);
	int firstbyte = ipix / pixperbyte;
	byte * inbuf = locbuf;
	byte far * linebuf = buf;
/*
printf("READ_LINE unpacking: %d bytes read, lastpix=%d, pixbits=%d, linelen=%d\n",
   rpix,lastpix,imgcore.pixbits,linelen);
*/
	for (jj=firstbyte*pixperbyte ; jj<lastpix ; jj+=pixperbyte)
	    {
	    if (inbuf > (locbuf+rpix))
		break;
	    byte tmp = *inbuf++;
	    int k;
    	    for (k=0 ; k<pixperbyte ; k++)
    	    	{
		if (jj >= ipix)
    	    	    *linebuf++ = (tmp & Samp_mask);
    	    	tmp <<= imgcore.pixbits;
	    	}
	    }
	rpix = linebuf-buf;
	}
    else
	rpix = read(buf,linelen,bufloc);
#if defined __WATCOMC__ || defined __MINGCC__ || __GCC__
    delete locbuf;
#else
    delete [linelen] locbuf;
#endif
    currentline += lineincr;
    return ((rpix + fbands - 1) / fbands);
    }

Class * TiffFile::isA() const
	{ return &class_TiffFile; }
const Class * TiffFile::desc() 
	{ return &class_TiffFile; }

const int TiffFile::capabilities()
    {
    return(C_IDENTIFY | C_TEST | C_READ_HDR | C_READ );
    }

const long TiffFile:: idiopix() const 
	{ return (long)imageWidth.get(); }
const long TiffFile::idiolines() const 
	{ return (long)imageLength.get(); }
const int TiffFile::idiobands() const  
	{ return (samplesPerPixel.is()) ? samplesPerPixel.get() : 1; }

const char * TiffFile::band_id(const int band,const int detail)
	//	return a string identifying the specified band
	//	If 'detail'==0, return full string
	//	else a 1-char long string for synthesizing file names
	//	Return NULL if no multiband capabilities exist or error
    {
    static char * id[MAX_TIFFBAND] = { "Red","Green","Blue" } ;
    static char temp[2] = { 0,0 };
    if ((band < 0) || (band > MAX_TIFFBAND))
	return NULL;
    if (photometricInterpretation.get() < 2) // grey or bilevel
	return "";
    if (detail == 0)
	return id[band];
    temp[0]=*id[band];	// just the first char
    return temp;
    }

#ifdef NOMORE
feconst char * ImagFile::errormsg(char * buf,const int bufsiz)
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
    strcat(buf,errorstr ());
    return buf;
    }
#endif

const char ** TiffFile::about(const int detail)
	//	return descriptive string:
	//	detail == 0-4 use ImageFile::about()
	//		  5 => up to three lines of info - filetype specific
	//		  6 & 7=> up to 256 lines of info - full TIFF tags list
	//		    (6 doesn't include color or gray map listing)
    {
    const char ** retval = ImageFile::about(detail); // clear array, set line 0
    char tmp[160];
    TAGINFO taginfo;
    dTag tag;
    if ( (errn==0) && (detail > 4) )
	{
	switch(detail)
	    {
	    case 7:
	    case 6:
		{
		union { long * lbuf; short * sbuf; } buf;
		sprintf(tmp,"created on a%s system",
	   	    (tiff_hdr.ID[0] == 'I') ? "n Intel" : " Motorola");
		isA()->obdesc_append(tmp);
		for (int i=0 ; i<=ColorMap_I ; i++)	/* ColorMap_I is last one */
		    {
		    tmp[0] = '\0';
		    memcpy(&taginfo.tag,&stdtags[i].tag,sizeof (struct TAG));
		    tag.init(&taginfo);
   		    if (!tag.is())	// tag not in use
		    	continue;
		    taginfo.printname = tagnames[i];
		    taginfo.printinfo = tagdescribe[i];
		    tag.print(czFileName,tmp);
		    isA()->obdesc_append(tmp);
		    tmp[0] = '\0';
		    int dc = tag.diskitemcount();
		    if ((dc > 0) && (tag.gettype() != TT_RATIONAL) 
			    && (tag.gettype() != TT_ASCII))
			{
			  //int esize = tag.diskitemsize() / dc;
			if (tag.gettype() == TT_SHORT)
			    buf.sbuf = (short *) tag.diskitemread(czFileName);
			else
			    buf.lbuf = (long *) tag.diskitemread(czFileName);
			if (buf.lbuf == NULL)
			    sprintf(tmp,"Error reading tag %d",i);
			// don't do map or other lengthy details at level 6
			else if ((detail == 7) || (dc < 8)) // one text line max.
			    {
		    	    for (int j=0 ; j<dc ; j++)
			    	{
			    	if (tag.gettype() == TT_SHORT)
				    sprintf(&tmp[strlen(tmp)],"%4u ",buf.sbuf[j]);
			    	else
				    sprintf(&tmp[strlen(tmp)],"%8lu ",buf.lbuf[j]);
			    	if ((j%8) == 7)
				    {
				    isA()->obdesc_append(tmp);
				    tmp[0] = '\0';
				    }
			    	}
			    }
			if (buf.lbuf != NULL)
			    {
			    delete buf.lbuf;
			    buf.lbuf = NULL;
			    }
			if (strlen(tmp))
			    isA()->obdesc_append(tmp);
		    	}
		    }
		}
//		break;
	    default:
	    case 5:
		if (imageDescription.is())
		    {
		    memcpy(&taginfo.tag,&stdtags[ImageDescription_I].tag,
			sizeof (struct TAG));
		    taginfo.printname = tagnames[ImageDescription_I];
		    taginfo.printinfo = tagdescribe[ImageDescription_I];
		    tag.init(&taginfo);
		    tag.print(czFileName,tmp);
		    if (strlen(tmp)>1)
			isA()->obdesc_append(tmp);
		    }
		tmp[0]='\0';
		sprintf(&tmp[strlen(tmp)],"%d bits deep  ",idiopixbits());
		if (compression.is())
		    {
		    memcpy(&taginfo.tag,&stdtags[Compression_I].tag,
			sizeof (struct TAG));
		    tag.init(&taginfo);
		    sprintf(&tmp[strlen(tmp)],"%scompressed ",
			(tag.get()==1) ? "NOT " :"");
		    }
		if (strlen(tmp))
		    isA()->obdesc_append(tmp);
		strcpy(tmp,"compatibility: ");
		if (dTag::resultspecs==0)
		    strcat(tmp,"none");
		if (dTag::resultspecs&TIFF_X)
		    strcat(tmp,"X");
		if (dTag::resultspecs&TIFF_B)
		    strcat(tmp,"B");
		if (dTag::resultspecs&TIFF_G)
		    strcat(tmp,"G");
		if (dTag::resultspecs&TIFF_P)
		    strcat(tmp,"P");
		if (dTag::resultspecs&TIFF_R)
		    strcat(tmp,"R");
		if (dTag::resultspecs&TIFF_PRINTIFF)
		    strcat(tmp," PRINTIFF");
//		if (dTag::resultspecs&TIFF_FCONVERT)
//		    strcat(tmp," FCONVERT");
		if (dTag::resultspecs&TIFF_IFILE)
		    strcat(tmp," TIF2DRAG");
		strcat(tmp,"\n");
		isA()->obdesc_append(tmp);
		break;
	    }
	}
    return retval;
    }


