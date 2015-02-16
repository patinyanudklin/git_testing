#ifndef TOOLGR_2
static char RCSID[] = "$RCSfile: toolgraf.c,v $ ";
char TOOLGRAF_ID[] = "@(#) " __FILE__ " $Revision: 1.5 $ $Date: 2014/12/17 07:20:39 $ @ "__DATE__ " " __TIME__;
#else
char TOOLGRAF_ID2[] = "TOOLGRAF2";
#endif
/****************************************************************
 *	TOOLGRAF.C - functions for building DRAGON utilities
 *			fns for graphics only
 *          $Revision: 1.5 $	$Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1992-2014 by Goldin-Rudahl Associates
 *                            P.O. Box 9648
 *                            North Amherst, MA 01059 U.S.A.
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *	    ~~ EndC
 *
 *****************************************************************
 *	$Id: toolgraf.c,v 1.5 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolgraf.c,v $
 *	Revision 1.5  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.4  1999/10/23 19:23:16  rudahl
 *	added some 32-bit provisions
 *
 *	Revision 1.3  1999/10/04 15:25:19  rudahl
 *	added RCS keys; changed GrafOpen params
 *
 *	Revision 1.2  1999/04/11 17:31:46  rudahl
 *	converting away from VFiles
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:16:54  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:16:54  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/11/30  12:15:44  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/11/30  12:15:44  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *	non-ANSI (rev ?) library functions used:
 *
 *
 *	non-Posix (rev ?) library functions used:
 *
 *
 *	Current maintenance status of $Id: toolgraf.c,v 1.5 2014/12/17 07:20:39 rudahl Exp $
 *
 *					Preliminary		Detailed
 *					(date  & rev)		(date & rev)
 *	----------------------		-------------		------------
 *
 *  Stylized file format (this info)	92/12/18 4.0______	_______________
 *
 *  Delete unneeded header files    	__________________	_______________
 *
 *  convert zortech.h & host.h to  	4.0_______________	_______________
 *	dtypes.h & dlimits.h
 *
 *  Are allocs & strdups checked?   	__________________	_______________
 *
 *      are they freed?             	__________________	_______________
 *
 *  Are strcpy & strcat length limited?	__________________	_______________
 *
 *  Are string buffers adequate size?	__________________	_______________
 *
 *  Are static data elements really   	__________________	_______________
 *	needed?
 *
 *  Are data types portable?        	__________________	_______________
 *
 *  Verify magic numbers & array sizes	__________________	_______________
 *
 *  Checked for ANSI compliance?    	__________________	_______________
 *	(method used:   )
 *
 *  Checked for POSIX compliance?    	__________________	_______________
 *	(method used:   )
 *
 *  lint checked?                    	__________________	_______________
 *	(lint version:     )
 *
 *****************************************************************/
/**/
/*
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. These TOOLxxxx.C
 *    files will not be supplied to users, but TOOLKIT.H will be.
 *
 *    Refer to TOOLKIT.C for general comments. This file contains only
 *    fns to manipulate graphics; therefore this is for DR library only
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *	Public functions in TOOLGRAF.C
 *	  int dtk_GrafInit()		 * initialize graphics driver
 *	  int dtk_GrafGetMode()
 * 	  int dtk_GrafRes()
 * 	  int dtk_GrafIsText()
 * 	  int dtk_GrafIsGray()
 * 	  int dtk_GrafSet(const int mode) * select graphics mode
 * 	  int dtk_TextSet()		 * set into text mode
 * 	  int dtk_GrafScreenLines()
 * 	  int dtk_GrafScreenPixels()
 *	  int dtk_GrafPuts(const char * msg)
 * 	  int dtk_GrafClipWind(const uint x0, const uint y0,
 *			const uint x1, const uint y1)
 * 	  int dtk_GrafFillWind(const ulong color_index,
 *			const uint x0, const uint y0,
 *			const uint x1, const uint y1)
 * 	  int dtk_GrafLine(const ulong color_index, const uint x0,
 *			const uint y0, const uint x1, 
 *			const uint y1)
 * 	  int dtk_GrafCircle(const ulong color_index, const uint x,
 *			const uint y0, const uint rad)
 * 	  int dtk_GrafClearScreen()
 * 	  int dtk_GrafSetColors(const char* filename)
 * 	  int dtk_GrafDisplayImage(const int img_index, const int iline,
 *			const int ipix, const int nlines,
 *			const int npix, const int subsample)
 *        int dtk_GrafDisplayComposite(const int blueindex, 
 *                      const int greenindex,
 *                      const int redindex,
 *                      const int iline,const int ipix, 
 *                      const int nlines,const int npix, 
 *                      const int subsample)
 *		
 * 1.0	6/27/92 ktr	extracted from TOOLKIT.C
 * 	11/12/93 seg	added dtk_GrafDisplayComposite
 * 4.1	3/29/94 ktr	added extra arg for GetConfig
 *	5/3/94 ktr	removed code for spawning DGRAPH - must load with FGATE
 *			split into two obj. modules
 *	8/25/94 ktr	revised GrafInit() to correctly use .CFG file
 *			even if !DragonIsRunning() (not a published combo)
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 * 5.0	4/1/99 ktr	revamped IMAGE.residentflag to symbolic values
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef __GCC__
#include <process.h>
#include <dos.h>
#include <io.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "basemem.h"
#include "drelease.h"
#ifdef __cplusplus
extern "C" 
    {
#endif
//#include "tstack.h"
#include "wf.h"
#ifdef __cplusplus
    }
#endif

#include "stats.h"	/*for module numbers */
#include "files.h"	/* for CONFIGSTRLEN */
#include "dhead.h"	/* must preceed toolkit.h & img.h */
#include "img.h"
#include "graf.h"
#include "img_acc.h"
#include "werror.h"
#include "d_msg.h"
#include "dtk.h"
#include "toolkit.h"
#include "toolerr.h"

#ifndef TEST

#ifdef __SMALL__
#define _COMP_MODEL "SMALL"
#elif __MEDIUM__
#define _COMP_MODEL "MEDIUM"
#elif __LARGE__
#define _COMP_MODEL "LARGE"
#else
#define _COMP_MODEL "32-bit"
#endif
#ifdef MSWIND
#define _WIN_TXT " MSWIND"
#else
#define _WIN_TXT ""
#endif
#ifdef _DEBUG
#define _DBG_TXT " DEBUG"
#else
#define _DBG_TXT " NODEBUG"
#endif

#ifndef TOOLGR_2
static char THIS_FILE[] 
	= "@(#)         compiled " _DBG_TXT " @ " __DATE__ " " __TIME__ " " _COMP_MODEL " " _WIN_TXT;
void TOOLGRAF()
    { }		/* just a marker for the link file */

//
//	TOOLGRAF1 is the minimal functions needed by TOOLKIT.C
//	if no actual graphics fns are called by app. pgm.

int Inst_Module(unsigned enum_base);	

/*************************************************************************
 *
 *		local data
 *
 *************************************************************************/

//static char dgraph[CONFIGSTRLEN+1];
int graf_id=0;	/* non-zero => graphics driver successfully opened */
int grafmode=0;	/*  != 0  => graphics initialized AND display is in non-text mode */ 

/*************************************************************************
 *
 *	private function. This is called explicitly by dtk_PrintExit
 *	and as an atexit() function setup by dtk_GrafInit()
 *+
 *************************************************************************/

void zap_dgraph(void)
        /* close dgraph ONLY if dtk_GrafInit was done */
    {
    if ((graf_id == 0) || dtk_DragonIsRunning())
	return;
    if (dtk_GrafGetMode() >= 0)
	GrafDMode(3);	/* reset to text before exit */
    GrafClose();
    graf_id = 0;
    }

/*************************************************************************
 *
 *		graphics functions
 *
 *************************************************************************/

int dtk_GrafGetMode(void)
	/*	return >= 0 if it's in a graphics (non-text) mode
	 *	and < 0 if not initialized, or not possible, or text
	 *	None of these produce actual errors, so can be used
	 *	even if graphics not installed
	 */
    {
    int status=0;
    grafmode=0;
    if (graf_id == 0)
        return DTKE_GRAF_NOT_INIT	;
    if((status = CurScreen(SCR_QMODE,-1)) & 2)
        return DTKE_GRAF_TEXT;
    if (status == -1)
	return DTKE_GRAF_ERR;
    grafmode = 1;
    return status;
    }

int dtk_TextSet()
	/*	Switches graphics driver to text mode.
	 *	If graphics not installed this is a noop
	 */
    {
//    char numbuf[D_NUMBUF];
    if (graf_id == 0)
        return 0;	/* already in text mode */
    if (GrafDMode(3) < 0)
        return Error(DTKE_GRAF_BAD_MODE,"%1",FID_TextSet,NULL);
    grafmode = 0;
    return 0;
    }

int dtk_GrafPuts(const char * msg)
	/*	Displays text 'string' on the graphics screen in a
	 *	default color. Positioning of the string is handled by
	 *	embedded control characters.
	 *	
	 *	See ??? for embedded control sequences. When control
	 *	sequence takes numerical arg, do not use \0. Instead,
	 *	use 0x80 to mean 0.
	 */
    {
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafPuts,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafPuts,NULL);
    GrafCom((const byte *)msg,1);
    return 0;
    }

void TOOLGRAF_END()
    { }		/* just a marker for the line file */

#else	// TOOLGRAF2
static char THIS_FILE2[] 
	= "@(#)         compiled " _DBG_TXT " @ " __DATE__ " " __TIME__ " " _COMP_MODEL " " _WIN_TXT;

void TOOLGRAF2()
    { }		/* just a marker for the link file */

extern int graf_id;	/* non-zero => graphics driver successfully opened */
extern int grafmode;	/*  != 0  => graphics initialized AND display is in non-text mode */ 
extern void zap_dgraph(void);

int dtk_GrafInit(void)
	/*	initialize graphics driver AT MOST once
	 *	On failure, return error < 0
	 *	else return 0
	 */
    {
    int tmp;
    id_struct dev_id;
    id_struct far * idptr;
    if (graf_id)	// only call this once
	return 0;
//printf("dtk_GrafInit starting; dragon is %srunning, Inst_Module is %x\n",
//	((dtk_DragonIsRunning()) ? "" : "NOT "),
//        Inst_Module(D_ENUM));
#ifdef NOMORE	// can ONLY be preloaded
    if (Inst_Module(D_ENUM) == 0)	// was NOT preloaded by FGATE?
	{
	memset(dgraph,0,sizeof(dgraph));
	if ((GetConfig("DGRAPH",NEAR2FAR(dgraph),sizeof(dgraph)) <= 0)
		|| (GetConfig("DRAGVIDEO",NEAR2FAR(dragvideo),sizeof(dragvideo)) <= 0) )
	    return Error(DTKE_NO_CFG,"%1",FID_GrafInit,NULL);
	else 
	    {
	    if((spawnl(0,dgraph,dgraph,"-T",NULL) & 0xFF) != QUIT) /* ok exits QUIT */
	        return Error(DTKE_NO_DGRAPH,"%1",FID_GrafInit,NULL);
	    else
	        atexit(zap_dgraph);
	    }
	}
#endif
    if (!dtk_DragonIsRunning())
	{
	char dragvideo[CONFIGSTRLEN+1];
	if (GetConfig("DRAGVIDEO",NEAR2FAR(dragvideo),sizeof(dragvideo)) <= 0)
	    strcpy(dragvideo,"VGA");
	if (GrafOpen(FALSE,dragvideo) == 0)
	    return Error(DTKE_GRAF_INIT_ERR,"%1",FID_GrafInit,NULL);
        atexit(zap_dgraph);
	SetPMode(1);
    	}
    idptr=NEAR2FAR(&dev_id);
    graf_id=ChkDrvID(NEAR2FAR(&idptr));
    return 0;
    }

int dtk_GrafRes()
	/*	Query current resolution bits
	 *	return <0 if error
	 */
    {
    int status=dtk_GrafGetMode();
    return (status < 0) ? status : status & 0x30;
    }

int dtk_GrafIsText()
	/*	Query text versus graphics mode
	 */
    {
    int status=dtk_GrafGetMode();
    return (status == DTKE_GRAF_TEXT);
    }

int dtk_GrafIsGray()
	/*	Query gray versus color mode
	 */
    {
    int status=dtk_GrafGetMode();
    return (status < 0) ? status : status & 1;
    }

int dtk_GrafSet(const int mode)
	/*	Switches graphics driver to graphics mode and potentially
	 *	resets the color/gray or resolution dimensions. The value
	 *	passed for 'mode' may be a value retrieved by
	 *	dtk_GrafGetMode, or it may be constructed by ORing any
	 *	pair of the following constants (one from column A, one
	 *	from column B):
	 *
	 *	   A			   B
	 *	DTK_GRAY             	DTK_LOWRES
	 *      DTK_COLOR		DTK_MEDRES
	 *				DTK_HIRES
         *				DTK_FULL
	 *
	 * 	This is actually a general function, although the dtk
	 *	user does not know about other possible 'mode' values.
	 */
    {
    char numbuf[D_NUMBUF];
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafSet,NULL);
    if (GrafDMode(mode) < 0)
        return Error(DTKE_GRAF_BAD_MODE,"%1 %2",FID_GrafSet,itoa(mode,numbuf,10));
    grafmode = ((mode & 2)==0);
    return 0;
    }

int dtk_GrafScreenLines()
	/*	Returns number of display lines available
	 *	on display screen or region in current resolution, 
	 *	or error code
	 */
    {
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafScreenLines,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafScreenLines,NULL);
    return CurScreen(SCR_HIGH,-1);
    }

int dtk_GrafScreenPixels()
	/*	Returns number of display pixels per line available
	 *	on display screen or region in current resolution, 
	 *	or error code
	 */
    {
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafScreenPixels,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafScreenPixels,NULL);
    return CurScreen(SCR_WIDE,-1);
    }

int dtk_GrafClipWind(const uint x0, const uint y0, 
			const uint x1, const uint y1)
	/*	Set clipping window to a rectangle on the screen defined by 
	 *	'x0', 'y0','x1', 'y1'. Images and graphical objects will not
	 *	display outside of this area.
	 */
    {
    rect box;
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafClipWind,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafClipWind,NULL);
    if ((x0 >= CurScreen(SCR_PIX,-1)) || (y0 >= CurScreen(SCR_LINES,-1)))
        return DTKE_GRAF_OFFSCREEN;	/* may not be an error */
    box.Xmin=x0; 
    box.Ymin=y0; 
    box.Xmax=x1; 
    box.Ymax=y1; 
    SetWind(&box);
    return 0;
    }

int dtk_GrafFillWind(const ulong color_index,
			const uint x0, const uint y0, 
			const uint x1, const uint y1)
	/*	Fills a rectangle on the screen defined by 'x0', 'y0',
	 *	'x1', 'y1' with color defined by 'color_index'. This will
	 *	overwrite any previous graphics information in that
	 *	area. Fills entire screen if rectangle coordinates are
	 *	all zeros. Clips to current clipping window, but returns
	 *	error if completely outside current clipping area.
	 *
	 *	x0,y0 is upper left corner, x1,y1 is lower right
	 *	(i.e. x0 < x1, y0 < y1)
	 *
	 *	Available colors are defined in toolkit.h via
	 *	manifest constants.
	 */
    {
    rect box,* oldbox;
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafFillWind,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafFillWind,NULL);
    oldbox = GetWind();	/* get clipping window */
/*
printf("GrafFillwind: old rect=%d,%d to %d,%d, new=%d, %d to %d,%d\n",
	oldbox->Xmin,oldbox->Ymin,oldbox->Xmax,oldbox->Ymax,
	x0,y0,x1,y1);
*/
    if ((x0 >= oldbox->Xmax) || (y0 >= oldbox->Ymax)
	    || (x1 <= oldbox->Xmin) || (y1 <= oldbox->Ymin) )
	return DTKE_GRAF_OFFSCREEN;
    box.Xmin=x0; 
    box.Ymin=y0; 
    box.Xmax=x1; 
    box.Ymax=y1; 
    FillWind((uint) color_index,&box);
    return 0;
    }

int dtk_GrafLine(const ulong color_index, const uint x0,
			const uint y0, const uint x1, 
			const uint y1)
    {
    rect * oldbox;
    point pt;
    int xmin=min(x0,x1);
    int ymin=min(y0,y1);
    int xmax=max(x0,x1);
    int ymax=max(y0,y1);
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafLine,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafLine,NULL);
    oldbox = GetWind();	/* get clipping window */
    if ((xmin >= oldbox->Xmax) || (ymin >= oldbox->Ymax)
	    || (xmax <= oldbox->Xmin) || (ymax <= oldbox->Ymin) )
	return DTKE_GRAF_OFFSCREEN;
    pt.X=x0;
    pt.Y=y0;
    SetColr(color_index);
    SetGXY(pt);
    pt.X=(x1 - oldbox->Xmin);
    pt.Y=(y1 - oldbox->Ymin);
    DrawLine(&pt,4);	// what is  'mode'
    return 0;
    }

int dtk_GrafCircle(const ulong color_index, const uint x,
			const uint y, const uint rad)
    {
    rect * oldbox;
    point pt;
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafCircle,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafCircle,NULL);
    oldbox = GetWind();	/* get clipping window */
//    fprintf(stdprn,
//   "oldbox coordinates: x0=%d, y0=%d,x1=%d, y1=%d\n",
//            oldbox->Xmin,oldbox->Ymin,oldbox->Xmax,oldbox->Ymax);
//    fprintf(stdprn,
//   "x center=%d, y center=%d,radius=%d\n",x,y,rad);

    if ((((int)x-(int)rad) >= oldbox->Xmax) || 
        (((int)y-(int)rad) >= oldbox->Ymax) || 
        ((x+rad) <= oldbox->Xmin) || 
        ((y+rad) <= oldbox->Ymin) )
	return DTKE_GRAF_OFFSCREEN;
    pt.X=x;
    pt.Y=y;
    SetColr(color_index);
    DrawCirc(&pt,rad,4);
    return 0;
    }

int dtk_GrafClearScreen()
	/*     	Clears the full available area of the graphics screen.
         * 	Also resets clipping window to full screen.
 
	 */
    {
    rect box;
    if (graf_id == 0)
        return Error(DTKE_GRAF_NOT_INIT,"%1",FID_GrafClearScreen,NULL);
    if (!grafmode)
        return Error(DTKE_GRAF_TEXT,"%1",FID_GrafClearScreen,NULL);
    box.Xmin=0; 
    box.Ymin=0; 
    box.Xmax=dtk_GrafScreenPixels() - 1; 
    box.Ymax=dtk_GrafScreenLines() - 1; 
    SetWind(&box);
    FillWind(0,&box);
    return 0;
    }

#ifdef NOMORE
  /* 9/5/97 this part of colt_io has been moved to cgate
   * - as yet there is no cgatecal fn equivalent defined
   */
int dtk_GrafSetColors(const char* filename)
	/* 	Set graphics color table from DRAGON color file
	 *	Reads a color file specified by 'filename' and uses it
	 *	to set the color table for the next image display.
	 *	Returns 0 or error:
	 *		DTKE_GRAF_NOT_INIT
         *		
	 *		DTKE_FILEREAD
	 */
    {
    byte far * retv;	/* this won't actually work in 3.05 
		         * so dont use this value */
    int retval;

    if (graf_id == 0)
        return DTKE_GRAF_NOT_INIT;
    if (dtk_GrafIsText())
        return DTKE_GRAF_TEXT;
      
    retval=colt_io(NEAR2FAR(filename),&retv,0x00004301);
    return (retval >= 0) ? 0 : DTKE_FILEREAD ;
    }
#endif

int dtk_GrafDisplayImage(const int img_index, const int iline,
			const int ipix, const int nlines,
			const int npix, const int subsample)
	/*	Displays image on graphics screen
	 *	Displays image in memory buffer identified by 'img_index'
	 *	on the graphics screen, starting at screen line 0, screen
	 *	pixel 0.
	 *
	 *	Allows user to display only a subset of the entire image
	 *	data, or to subsample by 2, if desired: the data to be
	 *	displayed starts with line 'iline' and pixel 'ipix'.
	 *	Display a total of 'nlines' lines and 'npix' pixels, if
	 *	both 'nlines' and 'npix' are greater than zero (if they
	 *	are zero, use all the image data that is available and
	 *	will fit on the screen).  If 'subsample' is non-zero,
	 *	display every second line and pixel.
	 *	Return 0 or <0 => error:
	 *		DTKE_IMGBAD	img_index bad
	 *		DTKE_IMGNOTOPEN	img not open or no data
         *              DTKE_GRAF_NOT_INIT graphics not initialized
         *              DTKE_GRAF_TEXT  in text mode 
         *
	 */
    {
    image far * iptr = GetImagePtr(img_index);
    int status =  dtk_GrafGetMode();
    if (status < 0) 
        return status;
    if (iptr == FARNULL)
	return DTKE_BADIMG ;
    if ((iptr->ivfp == FARNULL)
	    || ((ushort)(iptr->residentflag & RES_RESMASK) < (ushort)RES_LOADED))
	return DTKE_IMGNOTOPEN;

    iptr->imgwindow.Xmin=min(ipix,iptr->pixels);
    iptr->imgwindow.Ymin=min(iline,iptr->lines);
    iptr->imgwindow.Xmax=min((ipix+npix),iptr->pixels);
    iptr->imgwindow.Ymax=min((iline+nlines),iptr->lines);
    DispImg(iptr,(subsample) ? 2 : 0);
    return 0;
    }

/**/
#ifndef R305
int dtk_GrafDisplayComposite(const int blueindex, 
                        const int greenindex,
                        const int redindex,
                        const int iline,const int ipix, 
                        const int nlines,const int npix, 
                        const int subsample)
	/*	Displays composite image on graphics screen
         *      using images in blueindex, greenindex, redindex.
	 *	Displays image in memory buffer identified by 'img_index'
	 *	on the graphics screen, starting at screen line 0, screen
	 *	pixel 0.
	 *
	 *	Allows user to display only a subset of the entire image
	 *	data, or to subsample by 2, if desired: the data to be
	 *	displayed starts with line 'iline' and pixel 'ipix'.
	 *	Display a total of 'nlines' lines and 'npix' pixels, if
	 *	both 'nlines' and 'npix' are greater than zero (if they
	 *	are zero, use all the image data that is available and
	 *	will fit on the screen).  If 'subsample' is non-zero,
	 *	display every second line and pixel.
	 *	Return 0 or <0 => error:
	 *		DTKE_IMGBAD	img_index bad
	 *		DTKE_IMGNOTOPEN	img not open or no data
         *              DTKE_GRAF_NOT_INIT graphics not initialized
         *              DTKE_GRAF_TEXT  in text mode 
	 */
    {
    image far * imgptr[3];
    int i;
    unsigned long modeno;
    int status =  dtk_GrafGetMode();
    if (status < 0) 
        return status;

    imgptr[0] = GetImagePtr(blueindex);
    imgptr[1] = GetImagePtr(greenindex);
    imgptr[2] = GetImagePtr(redindex);
     
    for (i = 0; i < 3; i++)
        if (imgptr[i] == FARNULL) 
        	return DTKE_BADIMG ;
    for (i = 0; i < 3; i++)
        if ((imgptr[i]->ivfp == FARNULL)
	      || ((ushort)(imgptr[i]->residentflag & RES_RESMASK) < (ushort)RES_LOADED))
	    return DTKE_IMGNOTOPEN;
     
    for (i = 0; i < 3; i++)
        {
        imgptr[i]->imgwindow.Xmin=min(ipix,imgptr[i]->pixels);
        imgptr[i]->imgwindow.Ymin=min(iline,imgptr[i]->lines);
        imgptr[i]->imgwindow.Xmax=min((ipix+npix),imgptr[i]->pixels);
        imgptr[i]->imgwindow.Ymax=min((iline+nlines),imgptr[i]->lines);
        modeno = ((long)(i+1)) << 9;
        modeno |= (subsample << 1) ;  
        DispImg(imgptr[i],modeno);
        }
    return 0;
    }
#endif

void TOOLGRAF2_END()
    { }		/* just a marker for the link file */
#endif

#else	/* #ifdef TEST */

#include <stdlib.h>
void main()
    {
    char buf[80];
    int status;
    dtk_init(NULL);
    printf("DRAGON %s running; max error level is %d\n",
	(dtk_DragonIsRunning()) ? "IS" : "is NOT",dtk_DragonErrorLevel());
    }
#endif
