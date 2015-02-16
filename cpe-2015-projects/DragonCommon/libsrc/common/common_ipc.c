#include "drelease.h"
ID_ COMMON_IPC_ID[] = 
  "\0@(#) " __FILE__ " $Revision: 1.7 $$Date: 2014/12/05 14:24:30 $";
/****************************************************************
 *
 *          COMMON_IPC.C - useful fns which know about shared resources
 *			 K.T. Rudahl
 *
 *	~~ Copyright 2000-2014 Kurt Rudahl and Sally Goldin
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
 *
 *   $Id: common_ipc.c,v 1.7 2014/12/05 14:24:30 rudahl Exp $
 *   $Log: common_ipc.c,v $
 *   Revision 1.7  2014/12/05 14:24:30  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.6  2005/11/19 08:41:35  rudahl
 *   revised LangFileName, etc location
 *
 *   Revision 1.5  2005/07/31 08:37:55  rudahl
 *   adapt for viewport 5.7, build in GRS-Dragon dir
 *
 *   Revision 1.4  2005/04/01 08:55:09  goldin
 *   fix multiple defines of fns
 *
 *   Revision 1.3  2005/03/30 10:56:51  rudahl
 *   got rid of stat arg to ReadAndZapFile
 *
 *   Revision 1.2  2005/03/29 14:41:24  rudahl
 *   initial adapting viewport to v 5.5
 *
 *   Revision 1.1  2005/03/19 06:31:51  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.12  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.11  2005/03/11 22:45:13  goldin
 *   Debug update_labels
 *
 *   Revision 1.10  2005/03/11 20:34:40  rudahl
 *   add and adapt common_ipc to v 5.5
 *
 *   Revision 1.9  2002/04/30 01:15:52  rudahl
 *   fine-tune GRSTempNam
 *
 *   Revision 1.8  2001/11/30 19:40:51  rudahl
 *   added MailOpName
 *
 *   Revision 1.7  2001/09/26 19:27:52  rudahl
 *   minor fixes to compiler conditions for ZOR
 *
 *   Revision 1.6  2001/09/26 19:08:06  rudahl
 *   fixup for using Unix path separators
 *
 *   Revision 1.5  2001/08/25 21:06:09  rudahl
 *   got rid of redundant STAT_S
 *
 *   Revision 1.4  2001/08/24 08:39:04  rudahl
 *   adapting for win32
 *
 *   Revision 1.3  2001/06/29 20:35:04  rudahl
 *   simplifying, for v 5.4
 *
 *   Revision 1.2  2000/07/08 19:55:26  rudahl
 *   added some whatis variables
 *
 *   Revision 1.1  2000/06/30 13:51:24  rudahl
 *   extracted platform-neutral stuff from grs_ipc.c
 *
 ****************************************************************
 *****************************************************************/
/**/
/*    Modification History
 * 
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * 1.0	6/16/00 ktr     created - extracted from grs_ipc.c
 * 5.5	2005-3-11 ktr	imported from dragon v 5.4
 * 6.7	2005-11-19 ktr	moved LangFileName to logger & IpcWrap;
 *			cleaned out deadwood
 */	    

/**/

#include <time.h>
#include <errno.h>
#include <limits.h>	/* for INT_MAX */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#if defined __GCC__ || defined __MINGCC__
#include <unistd.h>
#endif
#ifdef __GCC__
#include <sys/stat.h>
#else
#include <sys\stat.h>
#endif

#if defined __ZTC__
#else
#if !defined __GCC__ && !defined __MINGCC__
#include <sys\types.h>
#include <malloc.h>
#define access(a,b) _access(a,b)
#define stat(a,b) _stat(a,b)
#define F_OK 0
#include "windows.h"
#endif
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "dragonOb.h"		// AFFIX_BS, FILE_SEP

#include "files.h"
#include "werror.h"
#include "filename.h"

#include "portfile.h"
#if !defined __ZTC__ && ! defined __GCC__ && ! defined __MINGCC__
#define _INCLUDE_VIEWPORT   /* enable some stuff in grs_ipc.h */
#endif
#include "grs_ipc.h"	/* prototypes for this file */

void COMMON_IPC()
    { }		/* just a marker for the link file */
int COMMON_IPC_INIT_DATA=0;
int COMMON_IPC_UNINIT_DATA;

static char kpath[IPC_FMSIZE]=""; /* assumes empty or drv only or trailing \ */
int check_kpath(const int setit)
	//	check that kpath is set (but do not register .CFG file)
	//	Always returns with trailing "\\"
	//	return 0 if ok 
	//		else +1 if setit==0 && not prev. set
	//		else -1 if no .CFG file
	//	if 'setit'==0 (usual), try to set it if not set
	//		  ==1 => set it anyway
	//		  ==2 => just check, don't set
	//		  ==3 => just zap it
    {
    int retval=0;
    if (setit==3)
	kpath[0] = '\0';
    else
	retval = (kpath[0]=='\0') ? -1 : 0;
    if ((setit==1) || retval)
	{
	char tmpbuf[CONFIGSTRLEN+1];
	retval = (setit==0) ? 1 : 0;
	if ((GetConfig("KPATH",tmpbuf,sizeof(tmpbuf)) < 0)
		&& (setit != 0))
	    retval= -1;
	strcpy_array(kpath,tmpbuf);
		// make sure cpath & fpath end with '\'
	if ((strlen(kpath) > 0)
		&& (strchr("\\/",kpath[strlen(kpath)-1]) == NULL))
	    strcat(kpath,"\\");	
	}
    return retval;
    }

time_t timeout=30;	/* # seconds before timeout on listen(), receive() */

char * GRSTempnam(char * pczPath, char * pczPrefix)
	/*	like tempnam(), except guaranteed to be in spec'd directroy
	 *	There's no extension.
	 */
    {
    char * name = (char *) calloc(strlen(pczPath) + strlen(pczPrefix) + 8,1);
    if (name != NULL)
	{
	static int i = 0;
	int start_i = i;
	do
	    {
	    strcpy(name,pczPath);
	    if (strchr("\\/",pczPath[strlen(pczPath)-1]) == NULL)
		strcat(name,FILE_SEP); /* don't append if already there */
	    strcat(name,pczPrefix);
	    sprintf(name+strlen(name),"%d",++i);
//	    sprintf(name,"%s%s%s%02d",pczPath,FILE_SEP,pczPrefix,++i);
	    if (i >= 99)
		i = 0;
	    if (i == start_i)	/* wrap-around? */
		{
		free(name);
		name = NULL;
		break;
		}
	    }
	while (access(name,F_OK) == 0);	
	}
    return name;
    }

char * ReadAndZapFile(const char * czFilename,//STAT_s * pstat,
			const BOOL bSuppressEmpty, const BOOL bNozap,
			int * pErr)
	//	if file exists, read it and erase it (unless NOZAP)
	//	return ptr to new buffer (which must be freed by caller)
	//	if 'pstat' non-NULL, set it to file stat info
	//	if 'bSuppressEmpty', don't read a file which appears to
	//		be almost empty.
	//	if 'pErr', set it to 0 or cause of failure:
	//		-1 => filesize <= 0
	//		-2 => filesize almost empty
	//		-3 => mem alloc failure
	//		-4 => no write permission (fails only if pErr==NULL)
	//		 special case for CDROMS: accept but report not writable
	//		-5 => not there
    {
    int iErr = 0;
    char * buf = NULL;
    BOOL bThere = (access(czFilename,0) == 0); // else it's not there
    BOOL bOK = (access(czFilename,6) == 0); // else it's being written or not there
#ifdef _TRACE
  TRACE_G(">ReadAndZap trying for %s: access6=%d access0=%d sz=%ld\n",
	czFilename,bOK,bThere,(bOK) ? file_size(czFilename) : -1);
#endif
	// special case for CDROMS: accept but report not writable
    if (!bOK && (pErr != NULL))
	{
	bOK = TRUE;
	iErr = -4;
	}
    if (bOK) // else it's being written or not there
	{
	long fs = file_size(czFilename);
	if ( (fs > 0)
		&& ((fs >= 8) || !bSuppressEmpty)
		&& ((buf=(char *)calloc(30+(size_t)fs,1)) != NULL) )
		// buf alloc must be last of the tests
	    {
	    int locstat;
//	    if (pstat != NULL)
//		stat(czFilename,pstat);
	    locstat = rsf(czFilename,buf,(size_t)fs,0,0);
	    if(locstat <= 0)
		{
		strcpy(buf,czFilename);
		strcat(buf," read error");
		}
#ifdef _TRACE
    {
    STAT_s st;
    stat(czFilename,&st);
    TRACE_G("          read %d bytes; NOZAP=%s ftime=%s: %s\n",
			locstat,(bNozap) ? "TRUE" : "FALSE",
			ctime(&st.st_ctime),buf);
    }
#endif
	    if (!bNozap)
		remove(czFilename);
	    }
	else if (!bNozap)	/* kill even if we didn't want it */
	    remove(czFilename);
	if (fs <= 0)
	    iErr = -1;
	else if ((fs < 8) && bSuppressEmpty)
	    iErr = -2;
	else if (buf == NULL)
	    iErr = -3;
	}
    else
	iErr = (bThere) ? -4 : -5;
    if (pErr)
	*pErr = iErr;
    return buf;
    }

#ifdef _DEBUG

/* following extracted from chunkdmp.c 6/97 */
/* they are useful in e.g. chunkdrw, for dumping error info */

#ifndef __ZTC__  /* just to save space in ZOR .exe's */
void dump_filehdr(const CHUNK_FILE_HDR * cfh, const long offset)
	/* 'offset' is not used, just printed */
    {
    TRACE_G("`0003>    CHUNK_FILE_HDR: (structure size=%d at %ld)\n",
	sizeof(CHUNK_FILE_HDR),offset);
    TRACE_G("`0003>\tsignature=%c%c total file size=%ld flags=x%X version=%X\n",
	cfh->uType & 0xFF, cfh->uType>>8, cfh->ulSize, cfh->uFlags,
	cfh->uVersion);
    TRACE_G("`0003>\tTotChunkSize (should probably not be used) = %ld\n",
	cfh->ulTotChunkSize);
    }

void dump_chunkhdr(const CHUNK_HDR * ch, const long offset)
	/* 'offset' is not used, just printed */
    {
    TRACE_G("`0003>    CHUNK_HDR: (structure size=%d at %ld)\n",
	sizeof(CHUNK_HDR),offset);
    TRACE_G("`0003>\thdr size=%ld (%s); chunk size=%ld at %ld (x%lX) in file\n",
	ch->ulHdrSize,(ch->ulHdrSize==sizeof(CHUNK_HDR)) ? "Correct" : "Wrong",
	ch->ulSize,ch->lOffset,ch->lOffset);
    TRACE_G("`0003>\tChunk intended for WF fn %s created %s",
	ch->cChunk, ctime((const long *)&ch->ulTimeStamp));
    TRACE_G("`0003>\tFilename is %s; next chunk header at %ld (x%lX)\n",
	ch->cFile,ch->lNxtOffset,ch->lNxtOffset);
    }

void dump_chunk(const void * chunk_ptr, const char * chname,
	 const long offset)
	/* 'offset' is not used, just printed */
    {
    if ((strcmp(chname,"DISPIMG-24")==0)	// obsolete
		|| (strcmp(chname,"DL-PIXG")==0)
		|| (strcmp(chname,"DL-PIXM")==0)
		|| (strcmp(chname,"DL-PIX24")==0)
		|| (strcmp(chname,"DL-BMP")==0))
	{
	const CH_DISPIMG * di = chunk_ptr;
	TRACE_G("`0003>    CHUNK type %s: (structure size=%d at %ld)\n",
	    chname,sizeof(CH_DISPIMG), offset);
	TRACE_G("`0003>\tchunk size=%ld (%s); image data at file offset %ld (x%lX)\n",
	    di->ulSize,(di->ulSize==sizeof(CH_DISPIMG)) ? "Correct" : "Wrong",
	    di->ulOffset,di->ulOffset);
	TRACE_G("`0003>\timage %d pix by %d lines totalling %ld image bytes\n",
	    di->uPix,di->uLines,di->ulSizeImage);
	TRACE_G("`0003>\ttiling: %d tiles wide (each with %d pix)\n",
	    di->uTilesW,di->uTilePix);
 	TRACE_G("`0003>\t        by %d high (each with %d lines)\n",
	    di->uTilesH,di->uTileLn);
	TRACE_G("`0003>\tTileRowBytes=%ld (mult of 4 for Windows)\n",
	    di->ulTileRowBytes);
	TRACE_G("`0003>\tImage name=%s\n",di->cImage);
	}
    else if ((strcmp(chname,"DL-ANNOT")==0)
		|| (strcmp(chname,"DL-PICK")==0)
		|| (strcmp(chname,"DL-GRAPH")==0)
		|| (strcmp(chname,"DL-REPORT")==0)
		|| (strcmp(chname,"DL-EDIT")==0)
		|| (strcmp(chname,"DL-SCRIB")==0)
		|| (strcmp(chname,"DL-TRAILER")==0)
		|| (strcmp(chname,"DL-CONT")==0) )
	{
	const CH_INFO * ci = chunk_ptr;
	int progressing=1;
	TRACE_G("`0003>    CHUNK type %s: (structure size=%d at %ld)\n",
	    chname,CH_INFO_SIZE, offset);
	while (progressing)
	    {
	    TRACE_G("`0003>\top=%d; ",ci->uOp);
//	    TRACE_G("`0003>\top=%d=%s; ",ci->uOp,nameof(DL_OPNames,ci->uOp));
	    switch(ci->uOp)
		{
		case DL_END:
		case DL_CONTINUE:
		    TRACE_G("`0003> -- end of block\n");
		    progressing = 0; break;
		case DL_VPSIZE:		/* set viewport posn to uX,uY;
					 *    size to uExtra,ushrt[0] */
		    TRACE_G("`0003> UNIMPL - args are %d,%d %d color=x%lX\n",
			ci->uX,ci->uY,ci->uExtra,ci->ulColor);
		    break;
		case DL_MOVETO:		/* set 'current' to uX, uY */
		    TRACE_G("`0003> x,y=%d,%d\n",ci->uX,ci->uY);
		    break;
		case DL_LINETO:		/* from 'current' to uX, uY in ulColor */
		case DL_POINT:		/* at uX, uY in ulColor */
		    TRACE_G("`0003> x,y=%d,%d color=x%lX\n", ci->uX,ci->uY,ci->ulColor);
		    break;
		case DL_POINTAT:	/* at 'current' in ulColor */
		    TRACE_G("`0003> color=x%lX\n", ci->ulColor);
		    break;
		case DL_LINE:		/* from uX, uY to uExtra,uShrt[0] in ulColor */
		case DL_BOX:		/* uX,uY = ul; uExtra,uShrt[0] = lr; in ulColor */
		case DL_FILLEDBOX:	/* uX,uY = ul; uExtra,uShrt[0] = lr; in ulColor */
		    TRACE_G("`0003> x0,y0=%d,%d x1,y1=%d,%d color=x%lX\n",
			ci->uX,ci->uY,ci->uExtra,ci->o.uShrt[0],ci->ulColor);
		    break;
		case DL_CIRCLE:		/* uX,uY = center; uExtra = radius; in ulColor */
		    TRACE_G("`0003> x,y=%d,%d radius=%d color=x%lX\n",
			ci->uX,ci->uY,ci->uExtra,ci->ulColor);
		    break;
		case DL_TEXT:		/* uX,uY = left end of baseline; ulColor, cStr */
		case DL_TEXTR:		/* uX,uY = right end of baseline; ulColor, cStr */
		case DL_TEXTC:		/* uX,uY = center of baseline; ulColor, cStr */
		    TRACE_G("`0003> %s at %d,%d %d color=x%lX\n",
			ci->o.cStr,ci->uX,ci->uY,ci->uExtra,ci->ulColor);
		    break;
		case DL_TEXTAT:		/* 'current' = beginning of baseline; ulColor, cStr
					 * 'uExtra' is direction: degrees cw from East */
		    TRACE_G("`0003> %s at %d degrees color=x%lX\n",
			ci->o.cStr,ci->uExtra,ci->ulColor);
		    break;
		case DL_FONT:		/* cStr is name; uExtra is size */
		    TRACE_G("`0003> %s at %d points color=x%lX\n",
			ci->o.cStr,ci->uExtra,ci->ulColor);
		    break;
		case DL_WEDGE:
		    TRACE_G("`0003> UNIMPL - args are %d,%d %d color=x%lX\n",
			ci->uX,ci->uY,ci->uExtra,ci->ulColor);
		    break;
		case DL_SETSCALE:	/* for scaling coords; dDouble[0] default=1.0 */
		case DL_SETOFFSET:	/*  "  offsetting "      "               =0.0 */
		    TRACE_G("`0003> UNIMPL - arg is %d\n",ci->o.dDouble);
		    break;
		case DL_APPEND:		/* insert chunks from file named 'cStr'
					 * with origin of those chunks at uX,uY */
		    TRACE_G("`0003> file %s at %d,%d \n",ci->o.cStr,ci->uX,ci->uY);
		    break;
	/* interactive ops: return info in chunk file
	 * data values put into uShrt; count in uExtra; drw col in ulColor  */
		case DL_SET_CLIP:	/* uX,uY, uExtra,uShrt[0] define area of acceptance */
		case DL_ACCEPT_PPOINT:	/* uExtra is max number of points */
		case DL_ACCEPT_PLINE:	/* uExtra is max number of vertices*/
		case DL_ACCEPT_BOX:      /* let user specify rect. area */
		case DL_ACCEPT_TEXTSIZE: /* cStr is string (if empty, return avg char size) */
		case DL_ACCEPT_TEXTPOS:	/* cStr is string; let user sel. posn; return uX,uY */
		case DL_ACCEPT_TEXT:	/* let user type a message at x0,y0 */
		case DL_ACCEPT_POINT:	/* accept one point, with mult vars */
		    TRACE_G("`0003> UNIMPL - args are %d,%d %d %d color=x%lX\n",
			ci->uX,ci->uY,ci->uExtra,ci->o.uShrt[0],ci->ulColor);
		    break;
		default:
		    break;
		}
	    ci = (CH_INFO *)((char *)ci + ci->uSize);
	    }
	}
    else
	{
	TRACE_G("`0003>    CHUNK type %s: (structure at %ld)\n",
	    chname, offset);
	TRACE_G("`0003>Error - unknown chunk type\n");
	}
    }
#endif   /* ifdef _WINDOWS  - just to save space in ZOR .exe's */
#endif	/* _DEBUG */

void COMMON_IPC_END()
    { }		/* just a marker for the link file */
int COMMON_IPC_END_INIT_DATA=0;
int COMMON_IPC_END_UNINIT_DATA;
