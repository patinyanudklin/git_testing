/****************************************************************
 *
 *          GRS_IPC.H - Interprocess Communicationss
 *			 K.T. Rudahl
 *
 *      ~~ Copyright 1990-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: grs_ipc.h,v 1.57 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: grs_ipc.h,v $
 *   Revision 1.57  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.56  2014/12/10 02:55:19  rudahl
 *   lint for new mingw
 *
 *   Revision 1.55  2014/12/05 11:51:02  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.54  2010/12/15 10:17:21  rudahl
 *   added VDF_EVALVERSION
 *
 *   Revision 1.53  2010/10/28 06:55:09  rudahl
 *   (benign) requirement for msvc2010
 *
 *   Revision 1.52  2008/09/05 08:39:33  rudahl
 *   added composite flag
 *
 *   Revision 1.51  2008/08/09 08:58:46  rudahl
 *   added marker_style
 *
 *   Revision 1.50  2008/08/09 08:37:27  rudahl
 *   added geounit
 *
 *   Revision 1.49  2008/07/14 13:34:35  rudahl
 *   scriptrunning flag
 *
 *   Revision 1.48  2008/06/12 10:30:35  rudahl
 *   added docs
 *
 *   Revision 1.47  2008/06/02 03:26:30  rudahl
 *   merged AFLAGS into FLAGS
 *
 *   Revision 1.46  2008/06/01 10:17:02  rudahl
 *   added VDF_RESTORE.. to avoid RESIZE
 *
 *   Revision 1.45  2008/05/10 08:13:15  goldin
 *   Centralize defn of RPYPATTERN
 *
 *   Revision 1.44  2008/04/06 03:19:42  rudahl
 *   notes on formats
 *
 *   Revision 1.43  2008/02/17 10:49:03  rudahl
 *   renamed VDF_Both
 *
 *   Revision 1.42  2008/02/02 13:29:50  rudahl
 *   GCP - maybe finished now
 *
 *   Revision 1.41  2008/02/02 05:55:34  rudahl
 *   added for RESIZE 10
 *
 *   Revision 1.40  2008/02/01 10:15:18  goldin
 *   Add new symbols OP_ERROR and OP_INFO
 *
 *   Revision 1.39  2008/01/20 12:16:59  rudahl
 *   revised values for ~~RPTTEXT
 *
 *   Revision 1.38  2008/01/20 12:01:09  rudahl
 *   added values for ~~RPTTEXT
 *
 *   Revision 1.37  2008/01/20 05:00:32  rudahl
 *   cleaned spurious NULl char
 *
 *   Revision 1.36  2008/01/11 13:47:03  rudahl
 *   added AFLAGS for ~~ACCEPT
 *
 *   Revision 1.35  2007/12/30 10:50:43  rudahl
 *   one more flag for ~~DISPLAY
 *
 *   Revision 1.34  2007/12/29 14:54:34  rudahl
 *   one more symbol for ~~ACCEPT
 *
 *   Revision 1.33  2007/12/29 10:36:11  rudahl
 *   one more symbol for ~~ACCEPT
 *
 *   Revision 1.32  2007/12/29 08:24:21  rudahl
 *   corrected symbols for ~~ACCEPT
 *
 *   Revision 1.31  2007/12/29 08:22:45  rudahl
 *   added symbols for ~~ACCEPT
 *
 *   Revision 1.30  2007/12/06 04:57:14  rudahl
 *   added flag
 *
 *   Revision 1.29  2007/10/17 07:54:00  rudahl
 *   added NoOverview flag
 *
 *   Revision 1.28  2007/10/12 04:22:27  rudahl
 *   improve docs
 *
 *   Revision 1.27  2007/09/23 07:19:50  rudahl
 *   changed format of ~~DISPLAY for GEO
 *
 *   Revision 1.26  2007/09/02 07:12:37  rudahl
 *   added syms for interactive ROI
 *
 *   Revision 1.25  2007/09/01 13:28:41  rudahl
 *   added and fixed server DB access
 *
 *   Revision 1.24  2007/08/26 08:38:39  rudahl
 *   work on ViewportSendResize
 *
 *   Revision 1.23  2007/08/19 05:55:15  rudahl
 *   new modes in v 5.12 viewport
 *
 *   Revision 1.22  2006/09/17 05:01:03  rudahl
 *   got rid of 'far' keyword
 *
 *   Revision 1.21  2005/11/19 08:41:35  rudahl
 *   revised LangFileName, etc location
 *
 *   Revision 1.20  2005/08/01 02:52:34  rudahl
 *   changed viewport specials to use _INCLUDE_VIEWPORT
 *
 *   Revision 1.19  2005/04/03 04:57:33  goldin
 *   Change size of buffer to PATH_MAX
 *
 *   Revision 1.18  2005/03/31 13:32:37  goldin
 *   conditionalize on viewport
 *
 *   Revision 1.17  2005/03/30 11:10:46  rudahl
 *   adaptations for MFC60/viewport
 *
 *   Revision 1.16  2005/02/23 20:36:15  rudahl
 *   revising grsproc1 for new Image usages
 *
 *   Revision 1.15  2005/02/18 17:24:29  rudahl
 *   first pass adapt to v 5.5
 *
 *
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 
 * 1.0	3/14/95	ktr	Created
 *  	9/12/96 ktr	added new group of error status just for server/IPC
 *	9/13/97 ktr	moved some MPX interrupt decls here from vxd
 *	11/21/97 ktr	added GRS_IPC_FROMSERVER, _TO_SERVER
 *	11/6/99 ktr	added QIsNT(), QUseVxD() as ultimate solution
 *			to run-time configuration branching
 *			Added SendGIF() to centralize writing to VxD/file
 *      6/4/00 ktr      adapt for GCC - defn of STAT_s
 * 5.5	2005-2-17 ktr	imported from Dragon v 5.4
 * 5.10	2006-9-17 ktr	purged a lot of NOTNEEDED
 * 6.1	2010-12-14 ktr	added VDF_EVALVERSION
 ****************************************************************
 *
 * This defines data structures and symbols used to communicate with the
 * viewport clients.
 * Most of this stuff seems obsolete, so comment it out until 
 * proven otherwise.
 *
 ****************************************************************/

#ifndef GRS_IPC_H
#define GRS_IPC_H 1

#if defined __cplusplus
extern "C" {
#endif

#define RPYPATTERN "RpyDS*"

#define SERVER_INFO_XSIZE 450	/* fixed size of window used in server for */
#define SERVER_INFO_YSIZE 300	/* Histograms, scatterplots, etc */
				/* (these may be scaled down by the
				 * viewport client, in integer multiples) */

#define DRW_FONTNAME_SIZE 50 // for WINDOWS.IF file
#define IPC_SKT_NAMESZ 14
#define IPC_SKT_COUNT 10	/* code & filenameplan req. < 99 */

#define IPC_FMSIZE PATH_MAX
	/* need an independent filename size to assure portability */

#define IPC_JUSTDOIT 0	/* no  wait, no reply */
#define IPC_WAIT 1
#define IPC_REPLY 2

#ifdef UNICODE
#ifdef DRAGON_INI
#undef DRAGON_INI
#endif
#define DRAGON_INI L"dragon.ini"
#else
#define DRAGON_INI "dragon.ini"
#endif

#define I18NSMFPAT "i18n*."	// I18Nnxxx, where 'n' is process #
#define I18NMSGPAT ".CH8"	// msg and reply names corresp to above
#define I18NRPLPAT ".$R8"
#define I18NPERMFILE1 "readme.txt"  /* don't zap, and no semiphore, and exit */
#define I18NPERMFILE2 "results.txt"  /* don't zap, and no semiphore, and exit */
#define I18NEXITFILE "i18nexit.$sm"  /* exit immediately */

ushort query_mpx(ushort reg);
//void VxD_Yield();
	/* no-op except for Win3.1 */

//BOOL QIsNT();
	//	Is this running on NT 4.0?

//BOOL QUseVxD();
	//	Should we use VxD? (NT => NO)

// the __cdecl seems necessary for the vfileapi.dll
//#ifdef __ZTC__
int check_kpath(const int setit);
//#else
//int __cdecl check_kpath(const int setit);
//#endif
	//   check_kpath:
	//	check that kpath is set (but do not register .CFG file)
	//	return 0 if ok 
	//		else +1 if setit==0 && not prev. set
	//		else -1 if no .CFG file
	//	if 'setit'==0 (usual), try to set it if not set
	//		  ==1 => set it anyway
	//		  ==2 => just check, don't set
	//		  ==3 => just zap it

#ifdef _INCLUDE_VIEWPORT
//#if defined __ZTC__ || defined __GCC__
//typedef struct stat STAT_s;
//#else
//#define STAT_s struct _stat
//long filesize(const char * name);
//int GrsGetModuleFileName(const char * filename, const size_t namelen);
//#endif

extern char kpath[IPC_FMSIZE];

char * GRSTempnam(char * pczPath, char * pczPrefix);
	/*	like tempnam(), except guaranteed to be in spec'd directroy
	 *	There's no extension.
	 */

typedef enum
	{
	OS_UNKNOWN,
	OS_DOS,
	OS_W31,
	OS_W32S,
	OS_W95,
	OS_NTX,  // OS_NT seems to conflict with msvc2010
	OS_W98,
	OS_W2K,
	OS_OS2W3,
	OS_OS2W4
	} OS_PLATFORM ;

#define OS_NAMES \
	"OS_UNKNOWN", \
	"OS_DOS", \
	"OS_W31", \
	"OS_W32S", \
	"OS_W95", \
	"OS_NTX", \
	"OS_W98", \
	"OS_W2K", \
	"OS_OS/2 Warp3", \
	"OS_OS/2 Warp4"

//OS_PLATFORM GetPlatform();	/* DOS version can't check NT */

typedef enum { MAIL_SB, MAIL_CH, MAIL_LT, MAIL_TXT, MAIL_NUE,
		MAIL_I18N_INCOMPLETE,	/* MAIL_TXT first etc parts */
		MAIL_I18N_DONE,		/* MAIL_TXT last */
		MAIL_I18N_KILL,		/* zap an existing I18N box */
		MAIL_ASCII,		/* like MAIL_NUE, but in text */
		MAIL_APPEND=0x100,	/* bit => append to prior file */
		MAIL_PRIORITY=0x200,	/* bit => overwrite prev. file */
		} MAIL_TYPE ;

#define MAILOPSTRINGS \
	"~~CANCEL~", \
	"PROMPT&RE",\
	"~~DISPLAY", /* display a CH file */\
	"~~RESIZE ", /* resize the VP [Size=x,y]|default */\
			 /* if x,y < ??, iconize */\
			 /* RESIZE not yet implemented */\
	"~~ACCEPT1", /* accept one point for ADD/LEG */\
	"~~ACCEPTt", /* accept one point for ADD/LEG: Size=x,y */\
	"~~ACCEPTg", /* geometry stuff */\
	"~~PUTCURS", /* position the cursor: Pos=x,y */\
	"~~CLEARSB",	/* clear statusbar */\
	"~~RPTTEXT",	/* add text to next report line */\
	"~~SBTEXT~",	/* put text on status bar (default) */\
	"~~DELETE~",	/* detele something (initialy, for GCP, one point) */

typedef enum
	{
	OP_CANCEL,
	OP_PandR,
	OP_DISPLAY,
	OP_RESIZE,
	OP_ACCEPT1,	/* accept one point for ADD/LEG */
	OP_ACCEPTt,	/* accept one point for ADD/LEG */
	OP_ACCEPTg,	/* geometry stuff */
	OP_PUTCURS,	/* position the cursor to x,y */
	OP_CLEARSB,
	OP_RPTTEXT,	/* add text to next report line */
	OP_SBTEXT,	/* put text on status bar (default) */
	OP_DELETE,	/* delete something */
	OP_INVALID
	}  MAIL_OP; 

MAIL_OP WhichOperator(const char * pczFounndFile);
	/*	which operator does string name, if any
	 *	Return OP_INVALID if not found
	 */

/* define arg strings for the ~~DISPLAY and ~~RESIZE ops
 * These take the form of arg=value
 * Note: FLAGS (if supplied) must be the FIRST arg
 *	 since its presence reinits some params (geo, scale)
 *	 (FLAGS not sent with ANN command to preserve old values)
 */
#define VDA_FLAGS "FLAGS"		/* format: =0x... */
#define VDA_SIZE "Size"			/* format: =lines,pixels (I) */
#define VDA_COLFILE "ColorFile"		/* format: ="pathname" */
#define VDA_ORIGIN "Origin"		/* format: =row,column (I) */
#define VDA_SCALE "Scale"		/* format: =scale (I) */
#define VDA_VPSIZE "VPSize"		/* format: =height,width (I,I) */
/* if GEOORIGIN is not supplied assume not georef'd image */
#define VDA_GEOORIGIN "GeoOrigin"	/* format: =North,East meters (F) */
#define VDA_GEOCELL "GeoCell"		/* format: =height,width meters (F) */
#define VDA_GEOUNIT "GeoUnit"		/* format: =string */
#define VDA_STYLE "Style"		/* format: =val (I) (for ~~RESIZE )*/
#define VDA_ARGS "Args"			/* format: =x,y (I) (for ~~RESIZE )*/
#define VDA_OP "Op"			/* format: integer (for ~~ACCEPT/~~RESIZE); 
					   string for ~~RPTTEXT*/
#define VDA_MSG "Msg"			/* format: statusmsg (for ~~ACCEPT)*/
#define VDA_POINTNUM "PointNum"		/* format: integer (for ~~ACCEPT)*/
#define VDA_POINTNAME "PointName"	/* format: string (for ~~ACCEPT)*/
#define VDA_FILENAME "Filename"		/* format: VEC infile full path (for ~~ACCEPT)*/
#define VDA_BOXSIZE "BoxSize"		/* format: integer (for ~~ACCEPT)*/
#define VDA_FONT "Font"			/* format: string (for ~~ACCEPT)*/
  //#define VDA_AFLAGS "AFLAGS"		/* format: =0x..*/
#define VDA_MSG "Msg"			/* format: Msg="text" (for ~~RPTTEXT) */
#define OP_WARN "Warn"				/* values for OP for ~~RPTTEXT */
#define OP_ERROR "Error"			/* values for OP for ~~RPTTEXT */
#define OP_INFO "Info"				/* values for OP for ~~RPTTEXT */
#define OP_SCA "U/SCA"				/* values for OP     " */
#define OP_CUR "U/CUR"				/* values for OP     " */
#define OP_HIS "U/HIS"				/* values for OP     " */
#define OP_CHIS "C/EDI/HIS"			/* values for OP     " */
#define VDA_SUBOP "SubOp"		/* format: SubOp="text" (for ~~RPTTEXT) */
#define SUBOP_REPLACE "REPLACE"			/* values for SUBOP  */
#define VDA_FILE "File"			/* format: string for ~~RPTTEXT */

/* define FLAGS value for the ~~DISPLAY op
 * In most cases these can be ORed but not always
 */
#define VDF_NOZAP 1	/* display nozap - ? v 5.8 no longer used */
#define VDF_EMPTY 2	/* display empty VP - ? v 5.8 no longer used */
#define VDF_NEW 4	/* display new image */
#define VDF_NO1to1 0x10	/* display non-native: the VP is permitted to scale */
// if neither of the following two flags is set, ~~ACCEPTg is enabled
// at most one of the following three flags is allowed to be set
#define VDF_ROI 0x20	/* enable non-interactive ROI */
#define VDF_1to1ROI 0x40 	/* enable interactive ROI requires fullres */
#define VDF_BothROI 0x80 	/* enable both interactive ROI and interactive OP */
// define additional flags for specialized behavior for different ops
#define VDF_NoOverview 0x100	/* special for D/OVERLAY */
#define VDF_FULLEXTENT 0x200	/* true=>we are showing entire image */
#define VDF_COMPOSITE  0x400	/* true=>we are showing =C */
#define VDF_RESETINTERACTIVE 0x1000 /* signal a new interactive session */ 
#define VDF_RESTOREPOSITION  0x2000 /* like ~~RESIZE 3 */
#define VDF_EVALVERSION      0x4000 /* this is eval version-disable things?*/
#define VDF_SCRIPTRUNNING    0x100000 /* TRUE => commands coming from a script*/

/* define STYLE values for the ~~RESIZE op
 */
#define VDS_RESTORE 3	/* restore to saved position */
#define VDS_SIZE 4	/* set absolute size */
#define VDS_RELPOS 5	/* move to (screen-pct) position */
#define VDS_ICONIZE 6	/* save position and iconize */
#define VDS_UNZOOM 7	/* unzoom if zoomed */
#define VDS_RESET 8	/* clear interactive counters and move to Z top */
#define VDS_TOP 9	/* move to top of Z-order */

	//	if file exists, read it and erase it (unless NOZAP)
	//	return ptr to new buffer (which must be freed by caller)
	//	if 'pstat' non-NULL, set it to file stat info (obsolete)
	//	if 'bSuppressEmpty', don't read a file which appears to
	//		be almost empty.
	//	if 'pErr', set it to 0 or cause of failure:
	//		-1 => filesize <= 0
	//		-2 => filesize almost empty
	//		-3 => mem alloc failure
	//		-4 => no write permission (fails only if pErr==NULL)
	//		special case for CDROMS: accept but report not writable
	//		-5 => not there
char * ReadAndZapFile(const char * czFilename,// STAT_s * pstat,
			const BOOL bSuppressEmpty, const BOOL bNozap,
			int * pErr);

#endif // ifdef _INCLUDE_VIEWPORT

extern char czLanguage[4];	// 3-letter abbrev. for language

#if defined __GCC__ || defined __MINGCC__  // causes error in MFC60
	/*	format current time into 'buf', prefixed by 'prefix' 
	 *		and postfixed by 'postfix' if non-NULL.
	 *	For convenience, return ptr to 'buf'
	 *	Always succeeds and always NULL-terminated.
	 */
#if DRAGON_VER >= 6
// now in logger.h
//char * NowString(const char * prefix, const char * postfix,
//		 char * buf, const size_t bufsize);
#else
//char * NowString(const char * prefix, const char * postfix,
//		 char * buf, const size_t bufsize);
#endif

#endif

#define SV_ERRMSG errstat_set,ErrorMsg,M_SERVER	// req. stats.h, werror.h
#define SV_SENDMAIL	0x1L
#define SV_GETMAIL	0x2L

	/* one message per bit in the error word */
#define SERVER_MSGS \
	"Error sending mail", \
	"Error sending mail", \
	"LAST MESSAGE"

#ifdef _INCLUDE_VIEWPORT
typedef struct
    {
    BOOL bValid;	/* data is valid (write is finished) */
    BOOL bAckRequired;	/* sender is blocked */
			/* => ulAckTime >= ulModifiedTime */
    ushort uCRCC;	/* detect changed data, even if time not incr yet */
			/* only applies to SB (item 0-7); sum of *(ushort *) */
    ushort uProcNo;	/* source or dest (depending) process */
    char czHint[8];	/* typically, ID of source module */
    ulong ulBufSize;
    time_t ulModifiedTime; /* time of latest mod to this struct */
	/* if bIndirect TRUE, following fields are offset within
	 * entire VM data space, not within buffer or file */
    ulong ulDataSize;	/* how much of the buffer is used? */
    ulong ulBufOffset;	/* bytes from begin. of structure */
    } GRS_IPC_ITEM ;	/* sizeof = 32 */

typedef struct { char buf[256]; } IPC_TEXT ;
//typedef struct { char buf[512]; } IPC_TEXT ;
#define FROMSERVER_ITEMS 11
#define TOSERVER_ITEMS 2

typedef struct
    {
    time_t ulWatchdogTime;	/* time of latest known server activity */
    ulong ulItemCount;		/* AY_COUNT of Item */
    GRS_IPC_ITEM Item[FROMSERVER_ITEMS];
    IPC_TEXT czStatusLine[FROMSERVER_ITEMS - 3];
    time_t ulAckTime[TOSERVER_ITEMS];	/* one per TOSERVER.Item[] */
//#ifdef DHEAD_H
//    byte Header[DHEAD];
//#else
    byte Header[2048];
//#endif
    byte cLinkTab[1];		/* grows; includes modarray */
    } GRS_IPC_FROMSERVER;	/* sizeof <= 8K + sizeof cLinkTab */

typedef struct
    {
    time_t ulWatchdogTime;	/* time of latest known exec activity */
    ulong ulItemCount;		/* AY_COUNT of Item */
    GRS_IPC_ITEM Item[TOSERVER_ITEMS];
    time_t ulAckTime[FROMSERVER_ITEMS];	/* one per FROMSERVER.Item[] */
    byte cCmdLine[512];
    } GRS_IPC_TO_SERVER;	/* sizeof < 1K */
#endif // _INCLUDE_VIEWPORT

   /* Structure used in drawing file created for viewport (VP).
    * Each instance describes a line to be drawn from
    * x0, y0 to x1, y1 in color 'color'. 'featureid' not
    * currently used. 'style' as below.
    */
    typedef enum  /* used in georast.c */
    {
    DRAW_STYLE, FILL_STYLE, MARKER_STYLE
    } DRAWING_STYLE_t;
 
typedef struct _VP_DRAWLINE
    {
    ushort x0;     
    ushort y0;
    ushort x1;
    ushort y1;
    ushort color;
    ushort featureid;
    ushort command;
    ushort style;    /* see DRAWING_STYLE_t above */
    } VP_DRAWLINE;

#if defined __cplusplus
    }
#endif

#endif
