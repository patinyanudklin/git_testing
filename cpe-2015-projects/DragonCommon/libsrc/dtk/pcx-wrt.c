static char SCCSIDV[] = "@(#) File: " __FILE__ " $Revision: 1.5 $$Date: 2014/12/17 07:20:39 $";
static char rev[] = "$Revision: 1.5 $";
/*      PCX-WRT.C      Dragon/WhitherForth image output to PCX file
 *        ~~ Copyright (C) 1989-2014 Kurt Rudahl and Sally Goldin
 *			converted from PRINTIFF.C 9/15/89,
 *			then from PCX.C 5/99
 *	  ~~ EndC
 * $Id: pcx-wrt.c,v 1.5 2014/12/17 07:20:39 rudahl Exp $
 * $Log: pcx-wrt.c,v $
 * Revision 1.5  2014/12/17 07:20:39  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.4  2004/12/23 12:17:02  rudahl
 * changed StdPalette to ushort to match GetPalette (in grsproc1)
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>	/* OPEN parameters	*/

#ifdef __GCC__   // 4/2000
#include <unistd.h>
#include <sys/stat.h>
#else
#include <sys\stat.h>
#include <io.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dhead.h"
#include "pcx-wrt.h"

static void encput(byte d,int chcnt,byte ** buf);
static int SquishPcx(byte * inbuf,byte * outbuf,int incount);
int negative_flag;
int plotfp = -1;
void PcxPix(const int x,const int y,const UINT32 color,
		        const int repeat,const int purge);

#ifdef NOMORE
static struct
	{
	char manuf;
	char version;
	char encode;
	char bitpix;
	unsigned int x0,y0,x1,y1;
	int hres,vres;
	char palette[48];
	char vmode;
	char nplanes;
	unsigned int bytes_line;
        int pcxPaletteInfo;
	char pcxFiller[58];	/* filler to make up 128 bytes */
	} pcx_head =
	{ 10,3,1,8,0,0,0,0,640,200} ;
#endif

static int uWidth, uXmin, uLineNo;
static byte * MagBuf = NULL;
static byte * YelBuf = NULL;
static int bsize;
struct IMAGEINFO { int Lmargin; } ImageInfo = { 0 } ;
#define BytesPerSend uWidth

byte PcxPalette[1+256*3];  /* PCX format: x0C followed by RGB triplets */
/****************************************************************
 *
 *	public functions for creating a PCX image file
 *	typically from DRAGON data.
 *
 *	These are intended to be similar to the API for
 *	other formats such as TIFF.
 *
 ***************************************************************/

int PcxPlotOpen(const char * czFilename,const uint uMode,
		 const uint uPlanes, const void far * lpHdr)
	/*	open file and write eader based on info in lpHdr
	 *	uMode low byte, for Pcx, should be 1
	 *	uMode high byte 1 => lpHdr is an IHEAD
	 *	uPlanes is 1 for 8-bit mapped Pcx, 3 for fullcolor
	 *	(however, fullcolor not supported here)
	 *	return 0 if error; else 1
	 */
    {
    int imlength, ymin,i;
    IHEAD far * lpIHdr = FARNULL;
    PCX_HEAD pcx_head = { 10,5,1,8,0,0,639,479,640,480} ;	/* use mode 5 ! */
    ushort StdPalette[256*3];	   /* TIFF format: 256 reds then 256 greens etc */
    lpIHdr = (IHEAD far *) lpHdr;
    if (uPlanes != 1)
	{
	puts("PlotOpen: fullcolor not supported");
	return 0;
	}
    GetPalette(StdPalette,sizeof(StdPalette));
    for (i=0; i<256; i++)
	{
	PcxPalette[1+i*3] = StdPalette[i];	/* red */
	PcxPalette[2+i*3] = StdPalette[i+256];	/* green */
	PcxPalette[3+i*3] = StdPalette[i+512];	/* blue */
	}
    PcxPalette[0] = 0xC;	/* special indicator */
    if ((plotfp = creat(czFilename,S_IREAD | S_IWRITE)) < 0)
	{
	puts("PlotOpen: error opening output file");
	return 0;
	}
    imlength = lpIHdr->fields.size[0];
    uWidth = lpIHdr->fields.size[1];
    uXmin = 0;
    ymin = 0;
    bsize = uWidth * uPlanes;
    MagBuf = malloc(uWidth * uPlanes);	// output buffer, post-squish
    YelBuf = malloc(uWidth);	// temp buffer, pre-squish
    if ((MagBuf == NULL) || (YelBuf == NULL))
	{
	puts("PlotOpen: Not enough memory for output buffer ");
	return 0;
	}
    pcx_head.hres = uWidth;
    pcx_head.vres = imlength;
    pcx_head.x1 = pcx_head.hres-1;
    pcx_head.y1 = pcx_head.vres-1;
    pcx_head.x0 = pcx_head.y0 = 0;
    memset(pcx_head.palette,0,48);
    pcx_head.vmode = 0;
    pcx_head.nplanes = uPlanes;
    pcx_head.bytes_line = pcx_head.hres; /* per-plane? spec says always even? */
    pcx_head.pcxPaletteInfo = 2;	/* color */
    if (write(plotfp,&pcx_head,sizeof(pcx_head)) != sizeof(pcx_head))
	{
	puts("PlotOpen: Error writing Pcx header ");
	return 0;
	}
    uLineNo = 0;
    return 1;
    }

void PcxPlotNextLine(const byte far * lpData,
		      const uint uPixWidth)
	/* 	write line of data to the open file. 
	 * 	If uPixWidth > 1 (byte), write three planes
	 * 	else if it's a 3-plane image, map the data through
	 *	palette.
	 */
    {
    int j;
    for (j=0 ; j < uWidth ; j++) /* screen pixels */
	PcxPix(j,uLineNo,lpData[j],0,0);
    PcxPix(j,uLineNo,lpData[j],0,1);
    }

int PcxPlotClose()
	/* 	flush buffers & zero them
	 * 	return 0 if OK else -1
	 */
    {
    if (MagBuf != NULL)
	free(MagBuf);
    MagBuf = NULL;
    if (YelBuf != NULL)
	free(YelBuf);
    YelBuf = NULL;
    if (write(plotfp,&PcxPalette,sizeof(PcxPalette)) != sizeof(PcxPalette))
	puts("PlotOpen: Error writing Pcx palette ");
    return close(plotfp);
    }

/*----------------------------------------------------------------------*/

static int SendLine(int icount)
	/*	send current line (of 'icount pixels) to pcx file
	 *	Return -1 if error, else count of bytes in outbuf
	 */
    {
    int count=SquishPcx(YelBuf,MagBuf,icount );
    if (count > 0)
	if (write(plotfp,MagBuf,count) != count)
	    return -1;
/*  memset(YelBuf,Background,bsize);*/
    memset(MagBuf,0,2*bsize);
    return count;
    }

/*----------------------------------------------------------------------*/

static int SquishPcx(byte * inbuf,byte * outbuf,int incount)
	/*	copy line of data in 'inbuf' to 'outbuf' ('incount' items)
	 *	squishing with PCPaintbrush run-length algorithm. 
	 *	Return -1 if error, else count of bytes in outbuf
	 *	Routines taken from PCPAINT docs.
	 */
    {
    int c;
    int d=*inbuf++;
    int chcnt=1;
    byte *out = outbuf;
    while (--incount)
	{
	c = *inbuf++;
	if (c==d)
	    {
	    if (++chcnt==63)        /* overflow? */
		{
		encput(d,chcnt,&out);
		chcnt = 0;
		}
	    }
	else    /* c != d  */
	    {
	    encput(d,chcnt,&out);
	    d=c; chcnt=1;
	    }
	if (out > &MagBuf[2*bsize])	/* actually, there's 10 bytes leeway */
	    return -1;
	}
    encput(d,chcnt,&out);
    return (out-outbuf);
    }

static void encput(byte d,int chcnt,byte ** buf)
	/*	append codes to '*buf' for 'chcnt' repetitions of value 'd',
	 *	& update *buf. 'chcnt' must be <= 0x3F.
	 */
    {
    if (chcnt)
	{
	if ((chcnt == 1) && (0xC0 != (0xC0 & d)))
	    *(*buf)++ = d;
	else    /* encode as byte pair */
	    {
	    *(*buf)++ = 0xC0 | chcnt;
	    *(*buf)++ = d;
	    }
	}
    }

void PcxPix(const int x,const int y,const UINT32 color,
		        const int repeat,const int purge) 
	/*	output a pixel to pcx file:
	 *	x,y are integers representing IMAGE coordinates
	 *	'repeat' not used
	 *	color is 0-255 grey-level or color index
	 */
    {
    unsigned loc_color = color & 0xFF;
    static byte * outbufptr;
    if (negative_flag)
	loc_color = 255-loc_color;
    if (((x==ImageInfo.Lmargin) && (y != 0)) || purge)  
	{   		/* send previous line */
 /*	if (SendLine(outbufptr-YelBuf) < 0)*/
	if (SendLine(BytesPerSend) < 0)
	    {
	    puts("PRN write error");
	    return;
	    }
	if (purge)
	    return;
	}
			/* now ready to plot the pixel */ 
    outbufptr = YelBuf+x;
    *outbufptr++ = loc_color;
    }

