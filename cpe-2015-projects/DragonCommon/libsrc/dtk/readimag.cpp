#include "drelease.h"
 ID_ READIMAG_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.7 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
static char rev[] = "$Revision: 1.7 $";
/*
 * 				READIMAG.CPP
 *	
 *      ~~ Copyright (C) 1988-2014 Kurt T. Rudahl and Sally Goldin. All rights reserved.
 *	~~ EndC
 ******************************************************************
 * $Id: readimag.cpp,v 1.7 2014/12/17 07:20:39 rudahl Exp $
 * $Log: readimag.cpp,v $
 * Revision 1.7  2014/12/17 07:20:39  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.6  2004/12/23 12:16:13  rudahl
 * lint-ish fix
 *
 * Revision 1.5  2002/06/10 12:33:53  rudahl
 * updated TIFF-related fns to MSC4.1
 *
 * Revision 1.4  2002/04/09 21:34:51  rudahl
 * adapt for long filenames, & fixed bugs
 *
 * Revision 1.3  2000/06/03 14:46:23  rudahl
 * fixes for SuSE6.3 GCC
 *
 * Revision 1.2  1999/07/03 16:50:25  rudahl
 * Fixed args for SWAPIT
 *
 * Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 * first checkin of only SOME common dirs
 *
 * Revision 4.0.1.1  1994/01/04  18:59:06  tower
 * no significant changes
 *
 * Revision 4.0  1994/01/04  18:59:06  tower
 * distributed with DRAGON rel. 4.0 - minor changes
 *
 * Revision 3.3  1992/06/02  19:02:01  tower
 *   Changes to TIFF library for Zortech 3.0, for released DRAGSCAN & TIF2DRAG
 *   and for first released use of imagfile
 * Revision 3.2  92/04/28  18:10:24  tower
 *   structural cleanup
 * Revision 3.1  91/05/04  18:56:47  tower
 *   updated use of filename() & removed some obsolete code
 * Revision 3.0  91/02/21  20:09:48  tower
 *   3.0 is initial version of READIMAG.CPP. It replaces READIMAG.C
 *   (which is now obsolete). Also, it no longer needs TIFTAGS.C
 *
 ******************************************************************
 *	derived from the TIFF IBM package distributed by DEST
 *	with cleanup and debugging supplied by Kurt Rudahl - Aug 1988
 *	most annotation supplied by KTR
 *
 * mods
 *	10/10/90 ktr	added host.h
 *	2/5/91 ktr	eliminated 'plane' & 'fdtype' from read_image call
 *			(were 2nd and 3rd arg). Their definition was inconsistent.
 *	2/11/91 ktr	mod to use Zortech C++ and TIFF.CPP class
 *	5/25/92 ktr	updated to Zortech 3.0 - very minor mods
 *	3/6/94 ktr	made so_tab etc be malloc'd - never freed?
 * 5.0	6/22/97 ktr	some changes for Watcom just to get it to compile.
 *			Probably correct but untested.
 *      6/3/00 ktr      fixes for gcc for suSE 63
 *
 *	particular problems noticed, hopefully to be corrected:
 *		read_image 'planes' variable not used
 *		read_image always returns 1 bit per pixel, packed
 *	function now uses extern IMAG_ATTR Tags, which must have been init by
 *	prior call to GetTifTags();
 *
 *	revisions to original supplied by DEST:
 *	    1.	read_image redefined as (signed 16-bit) INT
 *			values returned are
 *			   < 0 => error: -1 = file seek error
 *					 -2 = file read error
 *					 -3 = req. data > 64K
 *					 -4 = req. data past EOF
 *					 -5 = error getting attributes
 *					 -6 = too big for spec'd buffer
 *					 -7 = could not uncompress req'd amount
 *					 -8 = unsupported compress method
 *			   = 0 => no lines read (probably EOF, or none req'd)
 *			   > 0 => # lines read. See next note.
 *	    2.  read_imag never reads past strip boundary. Thus returned value
 *		may be less then req. number of lines.
 *	    3.  can read multi-bit per pixel data, if uncompressed	      
 *
 *			NOTE that output data is packed into user buffer at
 *			     8, 4, 2, or 1 pixel per byte
 */

/* the new improved read image.  Reads and holds in memory the strip
   tables.  Should be 40-50 percent faster than the old readimage */

/* modified 1/12/88 by BGM  To handle default tag values for various */
/* nonessential tags and motorola files.  To become compatable with  */
/* proposed tiff specification, Still need to add code which will    */
/* simulate the presense of the Strip byte count tables.             */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef __GCC__
#include <unistd.h>
#include <sys/stat.h>
#else
#include <sys\stat.h>
#include <dos.h>
#include <io.h>
#endif
#include "dtypes.h"
#include "dlimits.h"

//#include "host.h"
extern "C" {
//#include "zortech.h"
#include "files.h"	/*	for b_memcpy */
    }
//#include "printiff.h"
#include "tiff.hpp"

/* #define NO_COMPRESS		1 */
/* #define ONE_D_MODIFIED_HUFFMAN	2 * uncomment line to enable decompr */
/* #define RUN_LENGTH_BYTES	5331 */

#define FULRES_TYPE 1		/* full res. image */
#define STRIP_TAB_SZ 2000	/* max number strips we can handle */
	/* 	following two init. at start by 'tiff_img_tables_read */
//UINT32 sbc_tab[STRIP_TAB_SZ+1];	/* strip byte counts */
//UINT32 so_tab[STRIP_TAB_SZ+1];	/* strip offsets */
static UINT32 * sbc_tab = (UINT32 *)NULL;	/* strip byte counts */
static UINT32 * so_tab = (UINT32 *)NULL;	/* strip offsets */
	/* the +1 is so that we have room to compute the strip tables if nec. */

#ifdef ONE_D_MODIFIED_HUFFMAN
LONGPTR	decblk = 0;
LONGPTR decblk2 = 0;
#define bigalloc(a) farmalloc(a)
#define bigfree(a)  farfree(a)
#endif /* ONE_D_MODIFIED_HUFFMAN */

ulong	ulMaxbytesstrip = 0;

extern long ifdptr;	
	/** pointer to the first file descriptor: tiftags.c */
static	short	bytes_per_line;
static 	long	lNumber_strips;
static  long	old_start;
static	short	one_strip_image;

/* function return values */
int tiff_img_tables_read(char * fname);

void ZapTiffTables()
    {
    if (so_tab)
	free(so_tab);
    if (sbc_tab)
	free(sbc_tab);
    }

int read_tif_image( char * fname, int iline, int numlines,
		      	char far *buffer,long max_length)
	/* 	fname = file name
	 * 	iline = linenumber of first line to read
	 * 	numlines = how many to read
	 * 	buffer = where to put data
	 * 	max_length = how big is data buffer
	 * 	return number of lines actually read, <0 => error
	 */
    {
	/* define the attributes of this image */
    long start_strip; 	/* which strip# has init. line to read */
    long startoffset;	/* offset into start_strip for first line */
    long seek_addr;
    long bytes_to_read;
//    long temp;
    if (rowsPerStrip.get() > 0)
	{
	start_strip = (long) iline/rowsPerStrip.get();
	startoffset = (long)(iline%rowsPerStrip.get()) * (long) bytes_per_line;
	int iRowsPS = rowsPerStrip.get();
	numlines = min(numlines,(iRowsPS * (start_strip + 1) - iline));
	}
    else	/* must be single-strip img */
	start_strip = startoffset = 0L;
    int iImageLen = imageLength.get();
    numlines = min(numlines,(iImageLen - iline)); /* for partial last strip */
  	/* make sure that the user has not asked for too much data */
    if(start_strip > lNumber_strips)
	return -4;	/* error - start strip is past end-of-file */
    bytes_to_read = (long)numlines * (long)bytes_per_line;
    if(bytes_to_read > max_length)
	return -6;	/* error - too big for buffer */
    if(bytes_to_read > 65535L)
	return -3;  	/* error - more than 64K */
		/* read in the data.  There are 8 cases that can occur during 
       		 * a read.  they are:
		 *	1. strip uncompressed, rows contained in one strip.
		 *	2. strip uncompressed, rows consume one strip
		 *	3. strip uncompressed, rows cross strip boundry
		 *	4. strip uncompressed, rows cross more than one strip
		 *		boundry.
		 *	5. strip compressed, rows contained in one strip.
		 *	6. strip compressed, rows consume one strip
		 *	7. strip compressed, rows cross strip boundry.
		 *	8. strip compressed, rows cross more than one strip
		 *		boundry.
		 */
  	/* case 1,2,5,6: requested image rows are contained in the same strip */
	/* only this half of fn is debugged , so be sure to use cases 1,2,5,6 - ktr */
	switch((UINT16)compression.get())   /* do things differently */
	    {				    /* if the image is compressed */
	    case 1:
		/* read just the bytes needed.  case 1 is uncompressed */
		seek_addr = so_tab[start_strip] + startoffset;
//		bytes_to_read = numlines * bytes_per_line;
/*
printf(">READIMAG about to rsf: offset=%ld count=%ld numlines=%d bytes_per_line=%d\n",
	seek_addr,bytes_to_read,numlines,bytes_per_line);
printf("\t\t: startstrip=%ld so_tab=%ld startoffset=%ld\n",
	start_strip,so_tab[start_strip],startoffset);
*/
		if (rsf(fname,buffer,(int)bytes_to_read,seek_addr,0) 
			< (int)bytes_to_read)
		    return -1;	/* error - file read error */
		break;
#ifdef ONE_D_MODIFIED_HUFFMAN
	    case ONE_D_MODIFIED_HUFFMAN:
		if(start_strip != old_start)
		    {
		    old_start = start_strip;
		    seek_addr = so_tab[start_strip];
		    if (rsf(fname,decblk2,(SHORTx)sbc_tab[start_strip],seek_addr,0) 
			    < (SHORTx)sbc_tab[start_strip)
			return -1;	/* error */
			/* now, decompress the buffer */
	            ldc = decompress_block(decblk,decblk2,width,
			(long)numlines,sbc_tab[start_strip]);
		    if(ldc != temp) /*  * bytes_per_line)  */
		    	return -7;	/* error - didn't decompress whole strip */
		    }
	/* the block is in memory now, so just copy the requested line */		
		b_memcpy(buffer,(LONGPTR)&decblk[startoffset],
			numlines * bytes_per_line);
		break;		 
#endif /* ONE_D_MODIFIED_HUFFMAN */
	    default:
		return -8; break;   /* unsupported compress method */	
	    }
    return(numlines);
    }
#ifdef NOMORER
static int read_dirent(int tag,TDIRENT * dirent)
		/*	read one directory entry matching 'tag' into
		 *	'dirent'. Return 0 if ok, else < 0
		 */
    {
    if (stdtags[tag].tag.type == NONE)
	return -1;	// hasn't been initialized
    memcpy(dirent,&stdtags[tag].tag,sizeof(TDIRENT));
//printf(">READIMAG read_dirent tag=%d (index %d); lcount=%ld; foffset=%ld\n",
//	    dirent->tagno,tag,dirent->lcount,dirent->foffset);
    return 0;
    }
#endif// NOMORER

int tiff_img_tables_read(char * fname)
	/*	reads the strip offsets and sizes tables, and
	 *	the bits_per_sample entries if more than one
	 *	Return < 0 if error, else 1
	 */
    {
    DISKADDR diskloc;
    short BitsPerSampTable[3];	// there may be 1 or 3, and they are short
				// if only one, all table entries are init
    long strip_offset;
    long bytes_to_read;
    long i,temp;
    if (rowsPerStrip.gettype() == TT_NONE)
	{
	rowsPerStrip = (long)imageLength.get();
	printf("No Rows/Strip Tag -- assuming %ld\n",rowsPerStrip.get());
	}
	/*	first get the BitsPerSample value(s)	*/
    temp = bitsPerSample.getlen();	// this is, effectively, # of bands
    if ((samplesPerPixel.get() > 1) && (bitsPerSample.getlen() > 1))	
	{
	diskloc=bitsPerSample.get();
	bytes_to_read = temp * sizeof(short);
	if (rsf(fname,NEAR2FAR(BitsPerSampTable),bytes_to_read,diskloc,0)
		< bytes_to_read)	// read the entries
	    return(-11);		// error
	for(i=0;i<temp;i++) 
	    swapit((UINT16 *)&BitsPerSampTable[i],tiff_hdr.ID[0]);
//printf("\tsamplesPerPixel.get()=%d,bitsPerSample.getlen()=%d\n",
//	samplesPerPixel.get(),bitsPerSample.getlen());
	}
    else
	for(i=0;i<3;i++) 
	    BitsPerSampTable[i] = (short) bitsPerSample.get();
	/* following necessary since bits/sample may be different for dif. bands*/
    bytes_per_line = 7;
    temp = samplesPerPixel.get();	// works even if single 'bitsPerSample'
    for(i=0;i<temp;i++) 
    	bytes_per_line += (imageWidth.get() * BitsPerSampTable[i]);
    bytes_per_line /= 8;
    bitsPerSample = BitsPerSampTable[0]; // use typical value to export
/*
printf(">IMAGE_ATT_GET: width=%ld bits/samp=%ld samp/pix=%ld vytes_ln=%d\n",
	imageWidth.get(),bitsPerSample.get(),samplesPerPixel.get(),bytes_per_line);
printf("\ttemp=%ld; BitsperSampTable = %d %d %d\n",temp,
	BitsPerSampTable[0],BitsPerSampTable[1],BitsPerSampTable[2]);
*/
    one_strip_image = (rowsPerStrip.get() == imageLength.get());
    if (stripOffsets.gettype() == TT_NONE)
	{
	printf(">READIMAG: read_dirent error\n");
	return(-10);	/* error */
	}
    lNumber_strips = stripOffsets.getlen();
//    if (lNumber_strips > STRIP_TAB_SZ)	/* more than we have allowed for */
//	return(-11);	/* error */
    old_start = lNumber_strips+1;
    strip_offset = stripOffsets.get();
    bytes_to_read = lNumber_strips * (long) sizeof(long);
    if (so_tab == NULL)
	so_tab = (UINT32 *)malloc(bytes_to_read + sizeof(UINT32));	// one extra
    if (sbc_tab == NULL)
	sbc_tab = (UINT32 *)malloc(bytes_to_read + sizeof(UINT32));	// one extra
    if (sbc_tab == NULL)	// implies they both failed
	return -18;
    if(one_strip_image) 
	{
	so_tab[0] = strip_offset;
	sbc_tab[0] = bytes_per_line * imageLength.get();
	} 
    else
	{
	if (rsf(fname,NEAR2FAR(so_tab),bytes_to_read,strip_offset,0)
		< bytes_to_read)	// read the strip offsets
	    return(-12);		// error
		/* now check the originator and swap the bytes if necessary */
	for(i=0;i<lNumber_strips;i++) 	// who is originator
	    {
	    swapit((UINT32 *)&so_tab[i],tiff_hdr.ID[0]);
	    }
		/* now read the strip byte count tables */
		/* if the strip byte count table is not present, then */
		/* we need to fudge the data by using the strip offsets */
		/* to compute the strip byte counts */
	if(stripByteCounts.gettype() == TT_NONE) 
	    {
	    	/* read_dirent failed, fudge the data */
	    so_tab[lNumber_strips+1] 
		= bytes_per_line * imageLength.get() - so_tab[0];
	    for(i=0;i<lNumber_strips;i++) 
		sbc_tab[i] = so_tab[i+1] - so_tab[i];
	    }
	else
	    {
            strip_offset = stripByteCounts.get();
	    if (rsf(fname,NEAR2FAR(sbc_tab),bytes_to_read,strip_offset,0)
		    < bytes_to_read)
		return(-14);		 /* error */
	    for(i=0;i<lNumber_strips;i++) /* swap the bytes if necessary */
	    	{
		swapit((UINT32 *)&sbc_tab[i],tiff_hdr.ID[0]);
	    	}
	    }
	}
		/* find the biggest strip */
	ulMaxbytesstrip = 0;
	for(int j=0; j < lNumber_strips; j++) 
	    if(ulMaxbytesstrip < sbc_tab[j] ) 
		ulMaxbytesstrip = sbc_tab[j];
#ifdef ONE_D_MODIFIED_HUFFMAN
	if(l_compression == ONE_D_MODIFIED_HUFFMAN) 
	    {
	    decblk2 = (LONGPTR) bigalloc(ulMaxbytesstrip);
	    if(decblk2 == (LONGPTR)0)
		{
		return(-16);
		}
	    decblk=(LONGPTR)bigalloc((rows_per_strip+1) *  bytes_per_line);
	    if(decblk == (LONGPTR)0)
		{
		bigfree(decblk2);
		return(-17);
		}
	    }
#endif /* ONE_D_MODIFIED_HUFFMAN */
	return(1);
    }
