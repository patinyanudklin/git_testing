#include "drelease.h"
ID_ JPEG_WRT_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.3 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*      JPEG-WRT.C      Dragon/WhitherForth output image to JPEG file
 *
 *      ~~ Copyright 2002-2014 by Goldin-Rudahl Associates
 *                            P.O. Box 9648
 *                            North Amherst, MA 01059 U.S.A.
 *	~~ EndC
 ****************************************************************
 *   $Id: jpeg-wrt.c,v 1.3 2014/12/17 07:20:39 rudahl Exp $
 *   $Log: jpeg-wrt.c,v $
 *   Revision 1.3  2014/12/17 07:20:39  rudahl
 *   consolidating Dragon and OpenDragon
 *
 *   Revision 1.2  2002/08/28 16:19:15  rudahl
 *   working on TIFF & JPEG
 *
 *   Revision 1.1  2002/08/26 16:27:35  rudahl
 *   initial deposit; skeletal
 *
 *
 ****************************************************************
 *
 *		This module contains software particularly for
 *              creating TIFF files from image data.
 *		It is adapted from wftiff, from the DRAGPRNT pgm.
 *
 *	8/26/02 ktr	adapted from tiff-wrt
 *----------------------------------------------------------------------
 *
 * Externally accessable routines:
 *
 * int  JpegPlotOpen(filename,mode,
 *			planes)		return 0 if error; else 1
 * int  JpegPlotNextLine(data,pixpitch) plot next line
 * void	JpegPlotClose()			flush buffers to printer & clear
 */
/**/

/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>	/* OPEN parameters	*/
#ifdef __GCC__
#include <sys/stat.h>
#else
#include <dos.h>
#include <sys\stat.h>
#include <io.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dhead.h"
//#include "tiffint.h"	/* official tag names */
#include "jpeglib.h"	/* for using libjpeg.lib */
#include "jpeg-wrt.h"	/* for public decls for this module */

#define cputsq(a) puts(a)
#define LandScape 0			/* rotate lengthwise */
#define TopPix 0
#define BitsPerPix 8
#define GrafCom(a,b)

static rect * box;	/* create and initialize a box structure somewhere.
		 * containing the data rectangle that will become the Jpeg file
		 * Actually, only the X and Y sizes are used, not the actual
		 * coordinates
		 */	
static uint uXmin = 0;
static uint uWidth = 0;
static uint g_uPlanes = 0;
static uint g_uOutBufSize = 0;

static ushort Palette[256*3];

/*----------------------------------------------------------------------*
 *
 *	local prototypes
 *
 *----------------------------------------------------------------------*/

//void set_tagval(int,long,long);
static short header_write();
static int header_rewrite();
//int write_fields(IFDSTRC *,int);
//int field_data_write(IFDSTRC *,int size);
static long write_image(long numlines,const byte * buffer); 
	/* changed from char far *, which was wrong! */
static int close_create();
static int  PlotNextPix(const int x,const byte * pColor,
		 byte * const stuffPtr,const int planes);
static int SendBuf(const byte * buffer,const long count);

/*----------------------------------------------------------------------*
 *
 *	local data
 *
 *----------------------------------------------------------------------*/

static int plotfp = -1;		/* plotter file = level 1		*/
static FILE * pLogFp = NULL;		/* plotter file = level 2		*/
static byte * pOutBuffer = NULL;

/*----------------------------------------------------------------------*/

/****************************************************************
 *
 *	public functions for creating a Jpeg image file
 *	typically from DRAGON data.
 *
 *	These are intended to be models for a similar API for
 *	other formats.
 *
 ***************************************************************/

int JpegPlotOpen(const char * czFilename,const uint uMode,
		 const uint uPlanes, const void * lpHdr)
	/*	open file and write eader based on info in lpHdr
	 *	uMode low byte: Photometric Interpretation
	 *                      1 for b/w
	 *			2 3-plane RGB
	 *			  (properly, BITSPIX tag requires 3 values)
	 *			3 for mapped (include palatte)
	 *	uMode high byte 1 => lpHdr is an IHEAD
	 *			0 => lpHdr is a rect
	 *	uPlanes is IGNORED
	 *	return 0 if error; else 1
	 */
    {
    int imlength,ymin;
    static char softname[] = "DRAGON 5.4";
    IHEAD * lpIHdr = NULL;
    rect * lpBox = NULL;
    if (uMode & 0x100)
	lpIHdr = (IHEAD *) lpHdr;
    else
	lpBox = (rect *) lpHdr;
    g_uPlanes = ((uMode & 0xFF) == 2) ? 3 : 1; /* 8/2002 multiplane not OK */
pLogFp = fopen("h:\\tmp\\Jpeglog.jnk","w");
//    fieldbytecount=sizeof(wf_ifd);  /*	size of tags struct-must re-init here*/
    plotfp = open(czFilename,O_RDWR | O_CREAT | O_TRUNC | O_BINARY,0666);
    if (plotfp < 0)
	{
	cputsq("PlotOpen: error opening output file\r");
	return 0;
	}
		/* set up values of tags */
    if (LandScape)	/* switch horiz & vertical */
	{
	imlength = (lpIHdr == NULL)
		? lpBox->Xmax - lpBox->Xmin : lpIHdr->fields.size[1];
	uWidth = (lpIHdr == NULL)
		? lpBox->Ymax - lpBox->Ymin : lpIHdr->fields.size[0];
    	//set_tagval(TAG_ORIENT,1L,5L);
	}
    else
	{
	imlength = (lpIHdr == NULL)
		? lpBox->Ymax - lpBox->Ymin : lpIHdr->fields.size[0];
	uWidth = (lpIHdr == NULL)
		? lpBox->Xmax - lpBox->Xmin : lpIHdr->fields.size[1];
    //	set_tagval(TAG_ORIENT,1L,1L);
	}
    uXmin = (lpIHdr == NULL) ? lpBox->Xmin : 0;
    ymin = (lpIHdr == NULL) ? lpBox->Ymin - TopPix : 0;
    g_uOutBufSize = uWidth * g_uPlanes;
    pOutBuffer = malloc(g_uOutBufSize);
    if (pOutBuffer == NULL)
	{
	cputsq("PlotOpen: Not enough memory for output buffer ");
	return 0;
	}
    if (pLogFp != NULL)
	fprintf(pLogFp,"output buffer size=%d (%d planes; mode=x%X)\n",
		g_uOutBufSize,g_uPlanes,uMode);
    memset(pOutBuffer,0,g_uOutBufSize);
#ifdef NOTYET
    set_tagval(TAG_IMWIDTH,1L,(long)uWidth);
    set_tagval(TAG_IMLENGTH,1L,(long)imlength);
    set_tagval(TAG_BITSPIX,1L,(long) (g_uPlanes > 1) ? 8 : BitsPerPix);
    set_tagval(TAG_SAMPIX,1L, (g_uPlanes > 1) ? 3L : 1L);
    set_tagval(TAG_ROW_STRIP,1L,(long) imlength);
    set_tagval(TAG_SOFTWARE,1L,(long) softname);
    set_tagval(TAG_XPOS,1L,(long) uXmin);
    set_tagval(TAG_YPOS,1L,(long) ymin);
    set_tagval(TAG_PHOTOINTERP,1L,uMode & 0xFF);
		/* write tags to file; write palette only if mode == 3 */
    if (write_fields(wf_ifd,((uMode & 0xFF) != 3)) <= 0) /* inits the Palette*/
	{
	cputsq("PlotOpen: Error writing tag fields ");
	return 0;
	}
#endif
    return 1;
    }

void JpegPlotNextLine(const byte * lpData, const uint uPixWidth)
	/* 	write line of data to the open file. 
	 * 	If uPixWidth > 1 (byte), write three planes
	 * 	else if it's a 3-plane image, map the data through
	 *	palette.
	 */
    {
    uint j;
    byte * pStuffPtr = pOutBuffer;
    memset(pOutBuffer,0,g_uOutBufSize);
    for (j=0 ; j < uWidth*uPixWidth; j += uPixWidth) /* screen pixels */
	pStuffPtr += PlotNextPix(j,&lpData[j],pStuffPtr,uPixWidth);
    SendBuf(pOutBuffer,1L);
    }

int JpegPlotClose()
	/* 	flush buffers & zero them
	 * 	return 0 if OK else -1
	 */
    {
    if (pOutBuffer != NULL)
	free(pOutBuffer);
    pOutBuffer = NULL;
    if (pLogFp != NULL)
	fclose(pLogFp);
    return( !close_create()); 
    }

/*----------------------------------------------------------------------*/

int SendBuf(const byte * buffer,const long count)
       /* 	send 'count' lines of 'buffer' to file
	* 	return 0 if OK else actual lines output 
	*/
    {
//    long temp = write_image(count, buffer);
    return 0 ; //(temp != count) ? 0 : (int)temp;
    }

/*----------------------------------------------------------------------*/

int PlotNextPix(const int x,const byte * pColors,
			byte * const stuffPtr,const int pixbytes)
        /* 	stuff next pixel
	 *	Must be even # pixels per line
	 * 	& they must be plotted in sequence.
	 *	'x' is used only to indicate odd or even pix num,
	 *		which is important only if creating 1 or 4 bit data
	 *	Used in perverse way when plotting forced Jpeg24:
	 *	if planes == 3, plot 3 bytes first mapping successively through
	 *	the R,G,B, palettes
	 */
    {
    byte loc_color = (byte)(*pColors & 0xFF);
    size_t green_offset=256;
    size_t blue_offset=512;
    byte * pOutPtr = stuffPtr;
    if (BitsPerPix < 8)
	{
	loc_color &= 0xF;
	green_offset = 16;
	blue_offset = 32;
	}
    if ((g_uPlanes>1) && (pixbytes == 1)) /* cvt from mapped to RGB */
	{
	stuffPtr[0] = Palette[loc_color];		/* red */
	stuffPtr[1] = Palette[loc_color+green_offset];	/* green */
	stuffPtr[2] = Palette[loc_color+blue_offset];	/* blue */
	}
    else if (g_uPlanes>1)                 /* output RGB */
	{
	stuffPtr[0] = pColors[0];		/* red */
	stuffPtr[1] = pColors[1];		/* green */
	stuffPtr[2] = pColors[2];		/* blue */
	}
    else if ( (x & 1) || (BitsPerPix == 8))
	*stuffPtr |= loc_color;
    else
   	*stuffPtr = (loc_color << 4);
    return pixbytes;
    }

/*----------------------------------------------------------------------*/

/* ------------------------------------------------------------------ *
 *
 *		TIFF IMAGE DATA WRITE AND UPDATE FUNCTION
 *
 *		DEVELOPED BY:	VIJAY RANGARAJAN of DEST
 *		TIFWRITE Modified & included in WFTIFF 3/90 ktr
 *
 * ------------------------------------------------------------------ */

#ifdef NOMORE
/*
 *	revised ktr 3/23/89 to restrict strips-per-image to 1 
 *			    which saves lots of memory
 *
 *	actual list of functions
 *		write_image & close_create used by wftiff & dragprnt
 *
 *	long write_image(fdtype,numlines,buffer_ptr)
 *	static long get_tagval(tag_num)  * used by write_image only 
 *	int close_create()	  * Close TIFF creating subsystem 
 *	static int rewrite_field_data(...) * only by close_create
 *	void set_tagval(...)    *  used by close_create & tifcreat
 */


#define T_IMG_WIDTH 	256	/* image width */
#define T_IMG_LENGTH	257	/* length */
#define T_BITS_SAMPLE	258	/* bits per sample */
#define BITSSAMP	8	  /* default value */
#define T_COMPRESS	259	/* compression type */
#define T_SAMP_PIX	277	/* samples per pixel */
#define SAMPPIXEL	1	  /* default value */
#define T_RWPRSTRP	278	/* rows per strip */

static long field_data_endpos;
//static long field_data_pos;
//static long sav_fil_pos;

static short g_iStatus = 0;

static long offset_strip_mem;
static long count_strip_mem;

//static long lines_alloc = 0L;
//static long line_count;
//static long tot_byte_count;
/*static short byte_width;*/

/*---------------------------------------------------------------------*/

long write_image(long numlines,const byte * buffer_ptr)
	 /* write 'numlines' of data to file
	  * changed from char far *, which was wrong! */
    {
    static long	 l_bytewidth;
    static long get_tagval(short); // made static 4/00 - is this OK?
    int num_bytes;
    if (g_iStatus == 0) 	/* on first iteration only? */
	{
	long image_length=0,image_width=0;
	long bitssamp,samppix;
	g_iStatus = 1;
	image_length = get_tagval(T_IMG_LENGTH);
	image_width =  get_tagval(T_IMG_WIDTH);
	if((bitssamp = get_tagval(T_BITS_SAMPLE)) == 0L) 
	    bitssamp = BITSSAMP;
	if((samppix = get_tagval(T_SAMP_PIX)) == 0L) 
	    samppix = SAMPPIXEL;
/*	byte_width = (short)(image_width * samppix * bitssamp + 7 ) / 8;*/
/*printf("WFTIFF: width=%ld samppix=%ld bitssamp=%ld\n",image_width,samppix,bitssamp);*/
	l_bytewidth = (image_width * samppix * bitssamp + 7 ) / 8;
//	tot_byte_count = 0L;
//	rowsprstrp = get_tagval(T_RWPRSTRP);
//	if (rowsprstrp == 0)
//	    rowsprstrp = image_length;
	if (lseek(plotfp, field_data_endpos,0) < 0L)
	    return (0L);
//	strpofst_mem_ptr = (long *) &(offset_strip_mem[0]);
//	strpbytcnt_mem_ptr = (long *) &(count_strip_mem[0]);
//	sav_fil_pos = get_cpos(fhandle);
//	*strpofst_mem_ptr =(long) sav_fil_pos;
//	*strpbytcnt_mem_ptr =l_bytewidth * image_length;
	offset_strip_mem = lseek(plotfp,0,SEEK_CUR);
	count_strip_mem =l_bytewidth * image_length;
	}
		/*  how much to write to file? */
    num_bytes = (int) (l_bytewidth * numlines);
//    line_count = numlines;
//    lines_alloc = line_count;
//printf("Write_image bytes %ld (numlines=%ld,width=%ld)\n",
//	num_bytes,numlines,image_width);
    if (pLogFp != NULL)
	fprintf(pLogFp,"about to write x%X bytes of image at %lX\n",
			num_bytes, lseek(plotfp,0,SEEK_CUR));
    if (write (plotfp,(char *) buffer_ptr, num_bytes) != num_bytes)
	return (0L);
    return(numlines);
    }
#endif
static int close_create()
	/* 	Close TIFF creating subsystem 
	 */
    {
#ifdef NOOMOUY
    int field_data_rewrite();
    g_iStatus = 0;		/* indicate it's been closed */
	/* fill in header fields with actual strip offset, count */
    set_tagval(TAG_STRIP_OFFSET, 1L, offset_strip_mem);
    set_tagval(TAG_STRIP_BYTE, 1L, count_strip_mem);
    if (field_data_rewrite() < 0)
	return (0);
    return( !close(plotfp));
#endif
    return 0;
    }

#ifdef NOOMOUY
static IFDSTRC * find_tag(int tagnum)
	/*	get ptr to tag within wf_ifd, or NULL
	 */
    {
    int i;
    IFDSTRC * ptr = wf_ifd;
    for(i=0;i<TAG_COUNT;i++,ptr++)
	if (tagnum==ptr->tagnum)
	    return ptr;
    return NULL;
    }
	     
static long get_tagval(short tagnum)
	/*  Get the value of the specfied tag */
    {
    IFDSTRC * tagptr=find_tag(tagnum);
    return (tagptr) ? tagptr->offset_rvalue : 0L;    
/*
    short *field_ptr;
    long  tag_val, *ptr;
    short i = TAG_COUNT;  	// number of tags
    field_ptr = (short *) wf_ifd;
    while (i-- > 0)
    	{
        if (tag_num != *field_ptr)
	    field_ptr += 6;
        else
	    {
	    field_ptr += 4;
	    ptr = (long *) field_ptr;
	    tag_val = *ptr;
	    return(tag_val);
	    }
	}
   return(0L);
*/
   }

void set_tagval(int tagnum,long tagln,long tagval)
	/*  	Write tag number, length and value into 'wf_ifd'
	 *	finds & overwrites existing tag
	 */
    {
    IFDSTRC * ptr = find_tag(tagnum);
//fprintf(stdprn,">>DP set_tag %d to %ld; ptr=%p\n",tagnum,tagval,ptr);
    if (ptr != NULL)
	{
	ptr->fieldlen = tagln;
	ptr->offset_rvalue = tagval;
	}
    }

/* ------------------------------------------------------------------ */
/*								      */
/*		TIFF CREATING SYSTEM				      */
/*		TIFCREAT simplified and merged into WFTIFF 3/90	      */	
/*								      */
/* ------------------------------------------------------------------ */
/*
 *  	functions in this file:
 *		write_fields used by wftiff used by dragprnt
 *		field_data_write by tifwrite
 *
 *	short write_fields(buf_ptr,flag)		  
 *	void init_tif_hdr()    * Create TIFF header-used by write_fields only 
 *	short header_write() * write header structure into the file 
 *	int field_data_write(...)     * Write ifd data 
 *	int header_rewrite() *  " write_fields " 
 */

//static long header_fil1_pos;  	      	/* header file position */
// static long next_val_pos;

//static short no_more_strp_del = 0;

struct header_tiff_struc tiff_header = 
    { 
    INTEL_FMT,
    TIF_VERSION,
    sizeof(struct header_tiff_struc)
    };
		    
/*----------------------------------------------------------------------*/

int write_fields(IFDSTRC * buf_ptr,int nopal)
	/*	write to file data structure 'buf_ptr' consisting
	 *	of initialized tags in ascending tag number order. 
	 *	'fieldbytecount' is size in bytes of structure
	 *	if 'nopal', get palette but don't write to file
	 *	Return <= 0 if error, or the number of tags written.
	 * 	Structure in file is:
	 *	  HDR PALETTE RATFIELDS (ASCIIFLDS) TAGS IMAGE
	 */
    {
    int i,tlen=0;
    RATNL temprat;
    long field_data_pos;
//    void init_tif_hdr();
    long PaletteCount;	/* how many ushorts of palette reg info is there */  
		/**** write HDR to file */
    if (header_write() < 0)
	return (-1);
    PaletteCount = (long)GetPalette(Palette,AY_COUNT(Palette));
/*cputsnum("PaletteCount=",PaletteCount);*/
    if ( (PaletteCount != 0L) && (nopal == 0) )
	{
		/**** write PALETTE to file */
	long palette_fill_pos = lseek(plotfp,0,SEEK_CUR);	/* save palette file pos'n */
	if (pLogFp != NULL)
	    fprintf(pLogFp,"about to write Palette field=%d at %lX\n",
			(int)PaletteCount,lseek(plotfp,0,SEEK_CUR));
	if (write (plotfp, Palette,sizeof(Palette)) != sizeof(Palette))
 	    return (-2);
	set_tagval(TAG_COLORMAP,AY_COUNT(Palette),palette_fill_pos);
	}
    else
	{
	fieldbytecount -= sizeof(IFDSTRC); /* no colormap, which is last one */
	}
		/**** write RATIONAL FIELDS to file */
    temprat.denom=1;	/* all RATNL fields curr used have denom=1 */
//    for (i=0 ; i<=MAX_TAG ; i++)
    for (i=0 ; i< TAG_COUNT ; i++)
	{
	if (buf_ptr[i].fieldtype != TRATNL)	/* search for TRATNL tags */
	    continue;  //i++;

	if (pLogFp != NULL)
	    fprintf(pLogFp,"about to write TRATNL field %d at %lX\n",
			i, lseek(plotfp,0,SEEK_CUR));
	temprat.num=buf_ptr[i].offset_rvalue;	/* assume rvalue is numerator */
//	rat_data_pos = lseek(plotfp,0,SEEK_CUR);	/* this is where it goes */
/*cputsnum("RatPos=",rat_data_pos);*/
	set_tagval(buf_ptr[i].tagnum,1,lseek(plotfp,0,SEEK_CUR)); /* set tag offset */
	if (write (plotfp, &temprat, sizeof(temprat)) != sizeof(temprat))
 	    return (-2);
//	set_tagval(buf_ptr[i].tagnum,1,rat_data_pos); /* set tag offset */
	}
		/**** write ASCII FIELDS to file */
//    for (i=0 ; i<=MAX_TAG ; i++)
    for (i=0 ; i< TAG_COUNT ; i++)
	{
	if (buf_ptr[i].fieldtype != TASCII)	/* search for TASCII tags */
	    continue; // i++;
	if (pLogFp != NULL)
	    fprintf(pLogFp,"about to write TASCII field %d at %lX\n",
			i, lseek(plotfp,0,SEEK_CUR));
	if ((buf_ptr[i].offset_rvalue != 0) 
	  	&& ((char *)buf_ptr[i].offset_rvalue != NULL)
	  	&& ((tlen=strlen((char *)buf_ptr[i].offset_rvalue))>0))
	    {
		// save cur. rvalue, since we're about to change it
	    char * srcptr = (char *)buf_ptr[i].offset_rvalue;
	    if (++tlen&1)	/* result must be even */
		tlen += 1;
	    buf_ptr[i].fieldlen=tlen;
//	    asc_data_pos = lseek(plotfp,0,SEEK_CUR);	/* this is where it goes */
	    set_tagval(buf_ptr[i].tagnum,tlen,lseek(plotfp,0,SEEK_CUR)); /* set tag offset */
/*cputsnum("AscPos=",asc_data_pos);*/
	    if (write (plotfp, srcptr,tlen) != tlen)	/* write ASCII string */
		return (-2);
	    }
	else
//	    asc_data_pos=0;
	    set_tagval(buf_ptr[i].tagnum,tlen,0); /* set tag offset */
	}
		/**** write TAGS to file */
    tiff_header.first_ifd_addr = lseek(plotfp,0,SEEK_CUR); /* save file pos'n before write tags */
    field_data_pos = lseek(plotfp,0,SEEK_CUR);		/* save file pos'n before tag out */
/*cputsnum("FieldDataPos=",field_data_pos);*/
		/* build & write the tags */
    if (field_data_write(buf_ptr, fieldbytecount) < 0)
	return(-4);
    field_data_endpos = lseek(plotfp,0,SEEK_CUR); 	/* and after writing tags */
/*cputsnum("FieldDataEndPos=",field_data_endpos);*/
	   /*  printf("File positions:hdr=%lx, field=%lx, field-end=%lx\n",
		header_fil1_pos,field_data_pos,field_data_endpos); */
//    tiff_header.first_ifd_addr = field_data_pos;
		/**** write corrected HDR to file */
    if (header_rewrite() < 0)
	return(-5); 				/* modify hdr 	*/
    if (pLogFp != NULL)
	    fprintf(pLogFp,"write_fields (%d fields) successful at %lX\n",
			TAG_COUNT,field_data_pos);
    return(TAG_COUNT);	/* approx no_of_tags); */
    }

short header_write()
	/* write header structure into the file */
    {
    if (pLogFp != NULL)
	fprintf(pLogFp,"about to write header at %lX\n",
			lseek(plotfp,0,SEEK_CUR));
    if ((write (plotfp,(char *)&tiff_header, sizeof(struct header_tiff_struc)))
	  != sizeof(struct header_tiff_struc))
 	return (-1);
    return (0);
    }

/*  Rewrite the file header at beginning of file */

int header_rewrite()
    {
    if (lseek (plotfp, 0, 0) < 0)
    	return (-1);
    if (pLogFp != NULL)
	fprintf(pLogFp,"about to rewrite header at %lX\n",
			lseek(plotfp,0,SEEK_CUR));
    if (header_write() < 0)
    	return (-1);
    return (0);
    }

int field_data_write(IFDSTRC *  buffer,int size)
	/* 	Write 'buffer' data into the file
	 *	Return -1 if error else 0
	 */
    {
    short total_tags = TAG_COUNT;
    long next_ifd=0; 	/* we don't use more than one IFD per file */
    if (pLogFp != NULL)
	fprintf(pLogFp,"about to write x%X + x%X bytes of field data at %lX\n",
			sizeof(total_tags) + sizeof(next_ifd),
			size,lseek(plotfp,0,SEEK_CUR));
    if ( (write(plotfp, &total_tags,sizeof(total_tags)) != sizeof(total_tags))
	   || (write(plotfp, buffer, size) != size)
	   || (write(plotfp, &next_ifd, sizeof(next_ifd)) != sizeof(next_ifd)) )
	return (-1);
    return (0);
    }

int field_data_rewrite()	
	/*  	Return to saved position 'tiff_header.first_ifd_addr'
	 *	and revise TIF field data 
	 *	Return -1 if error else 0
	 */
    {	     
//    if (lseek(plotfp, field_data_pos,0) < 0L)
    if (lseek(plotfp, tiff_header.first_ifd_addr,0) < 0L)
  	return (-1);
    return(field_data_write (wf_ifd, fieldbytecount));
    }
#endif // ifdef NOMORE

