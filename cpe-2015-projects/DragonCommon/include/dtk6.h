/****************************************************************
 *	filename DTK6.H - functions for DRAGON toolkit DLL
 *          $Revision: 1.17 $	$Date: 2014/12/05 09:58:46 $
 *
 *      ~~ Copyright 1985-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: dtk6.h,v 1.17 2014/12/05 09:58:46 rudahl Exp $
 *	$Log: dtk6.h,v $
 *	Revision 1.17  2014/12/05 09:58:46  rudahl
 *	no differences between DragonProf and OpenDragon
 *
 *	Revision 1.16  2005/07/22 15:19:32  rudahl
 *	added header fields, functions
 *
 *	Revision 1.15  2005/02/21 23:54:34  goldin
 *	Working on toolkit compilation
 *	
 *	Revision 1.14  2004/11/30 10:00:34  rudahl
 *	fixup for mingw
 *	
 *	Revision 1.13  2002/06/10 12:39:43  rudahl
 *	updated docs
 *	
 *	Revision 1.12  2001/10/26 18:03:53  goldin
 *	Add prototype for dtk6_FileFind
 *	
 *	Revision 1.11  2001/10/17 17:09:56  rudahl
 *	adapted for 32-bit, long filenames, and thread-safe strsfn
 *	
 *	Revision 1.10  2001/08/07 20:18:09  rudahl
 *	enhanced file type validation
 *	
 *	Revision 1.9  2001/08/06 16:07:45  rudahl
 *	added docs
 *	
 *	Revision 1.8  2001/07/02 20:10:09  rudahl
 *	improved documentation around cmd line fns
 *	
 *	Revision 1.7  2001/06/30 11:17:48  rudahl
 *	moved some cmdline stuff from grsproc to dtk; other mods to both
 *	
 *	Revision 1.6  2001/06/26 21:42:56  rudahl
 *	symbolic size for short names
 *	
 *	Revision 1.5  2000/08/06 02:18:39  rudahl
 *	 added dtk6_CmsSetRegion *.h
 *	
 *	Revision 1.4  2000/06/17 21:09:43  rudahl
 *	added error return values to arg file parsing
 *	
 *	Revision 1.3  2000/05/29 22:51:04  rudahl
 *	exported and augmented GetConfig
 *	
 *	Revision 1.2  1999/11/13 00:28:35  rudahl
 *	exported dtk_fputs
 *
 *	Revision 1.1  1999/10/04 12:58:31  rudahl
 *	initial insertion
 *
 *
 *****************************************************************
 *    This header declares the public functions which are exported by
 *    DTK6.DLL.
 *
 *    Most functions return an int which will be interpreted as an
 *    error number if < 0. Functions are provided to maintain a stack of
 *    error messages; generally a function that returns an error status
 *    should also push a string onto this stack (the push fn copies the
 *    string) describing the condition. Users are VERY STRONGLY
 *    encouraged to check the returned error status of all toolkit
 *    library functions.
 *
 *****************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *
 *	Revision History
 * 5.5	2005-02-21 seg	imported from various files from Dragon Academic 
 *			Edition rev 5.4.4
 * 
 *
 */

#ifndef DTK6_H
#define DTK6_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef unsigned char byte;
#endif

#ifndef _LINEACCESS_DEFINED
#define _LINEACCESS_DEFINED
typedef void* (*LineAccess)(int); 
#endif

#ifndef STRSIZ
#define STRSIZ 132	/* buffer size used for certain string operations */
#endif

#define DRAGON_TOOLKIT_600 6L

typedef void * DTK_IMGSTATS;  /* this is an opaque data type which is
                               * actually a pointer to a rather complex
                               * statistics structure.
                               */

/* Macros to get rid of the '6' in the function names
 * when used for external consumption
 */
#define dtk_ProcessCommandLine dtk6_ProcessCommandLine
#define dtk6_CmdSetFlag dtk6_CmdSetFlag
#define dtk_CmdSet1int dtk6_CmdSet1int
#define dtk_CmdSet1float dtk6_CmdSet1float
#define dtk_CmdSet1double dtk6_CmdSet1double
#define dtk_CmdSet1string dtk6_CmdSet1string
#define dtk_CmdSetFile  dtk6_CmdSetFile
#define dtk_CmdSet1choice dtk6_CmdSet1choice
#define dtk_CmdSetRegion dtk6_CmdSetRegion
#define dtk_VerifyFileType dtk6_VerifyFileType
#define dtk_FileFind dtk6_FileFind
#define dtk_GetShortName dtk6_GetShortName
#define dtk_FilenameParse dtk6_FilenameParse


/********************************************************************
 *
 * New-style (32-bit, possibly in DLL) command-line parsing
 *
 ********************************************************************/

typedef struct CMDDESCRP_t
    {
    char * selector;	/* the string which specifies the command */
    int argcount;	/* minimum number of arguments for this command */
    int (*ProcessCmd)(char * value[],
	 	      const struct CMDDESCRP_t * table); /* process this */
    const char * czValidateSelector;	/* parameter for ProcessCmd */
    void * resultptr; 	/* put result here */
    } CMDDESCRIPTOR_T;

int EXPORT dtk6_ProcessCommandLine(int argc, char * argv[], 
				   const CMDDESCRIPTOR_T cmddescriptor[],
				   int * piErrnum);
	/*	executive function to pull commands from the program's
	 *	command line. The command style is conventional DRAGON
	 *	or UNIX-like command strings: a sequence of sets each
	 *	of which has a selector followed by zero or more arguments
	 *	Typically the selector sets may be in any sequence on the
	 *	command line. 
	 *	This function accepts the argc, argv which are the arguments
	 *	of main(), together with a table of descriptions of selector 
	 *	sets. It returns with 'argv' set to the first
	 *	string not handled by the table, and either a count of 
	 *	how many tokens were consumed (to be subtracted from 'argc'),
	 *	or a negative error number:
	 *	  -1 - -100 within this fn:
	 *		-1 = "Command line error: bad form for %1",*locargv);
	 *		-2 = "Command line error: unknown command
	 *		-3 = "Command line error: overrun end of line
	 *	  others defined as (-1 - -100) * line # within cmd table
	 *	    counting first line as 0
	 *		1 - 10 are CmdSetFile for input files
	 *		 -1 = bad arg string 
	 *		 -2 = e.g. file not found, or write file already exists
	 *		 -3 = error reading file
	 *		 -4 = validation failure - not recognized image type
	 *		 -5 = validation failure - not recognized other file
	 *		11 - 20 are CmdSetFile for output files
	 *		 -11 = bad arg string
	 *		 -12 = file already exists (for WX) 	
	 *		21 - 30 are for numerical args
	 *              31 - 40 are for region:
	 *               -31 = insufficient count
	 *               -32 = unrecognized format
	 *               -33 = mixed formats
	 *	
	 *	This is like the 16-bit toolkit version except that:
	 *	   'selector' is a full char. string.
	 *	   'cmddescriptor' includes a validate string.
	 */

int EXPORT dtk_ProcessArgFile(const char * pczArgFilename,
			      const char * pczIntro,
			      const CMDDESCRIPTOR_T cmdargs[],
			      int * piErrnum);
	/*	assuming that file contains args which match 'cmdargs',
	 *	read and process it. 
	 *	'pczIntro' if non-NULL is a string which MAY BE ignored
	 *	but only if it is at the beginning of the first non-comment
	 *	line of the file.
	 *	Comments are lines which begin with '('
	 *	Return number of tokens consumed
	 *      In case of error, set *piErrnum to a negative error number.
	 */

	/******************************************************************
	 *	Parsing fns suitable to be included in CMDDESCRIPTOR_T table
	 *
	 *	 These fns MAY use czValidateSelector from the table to
	 *	 select parameters to validate against. The meaning of
	 *	 the selector is entirely idiosyncratic to each fn.
	 *
	 *	Each fn returns < 0 => error else # tokens consumed.
	 */

int EXPORT dtk6_CmdSetFlag(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	set value to the upper-case second char of a token with
	 *	form "-X".
	 *	return 0 if arg matches one of the chars in
	 *	czValidateSelector.
	 *	else -1;
	 */

	/*	The following are all one-argument fns. 
	 *	Each handles 1-argument selector by setting *cmd->resultptr
	 *	to the conversion of next token.
	 *	Return the number of items removed from 'argv' = 1 if OK
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 */
int EXPORT dtk6_CmdSet1int(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	Set to the int conversion of next token.
	 *	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
//int EXPORT dtk6_CmdSet1float(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	Set to the float conversion of next token.
	 *	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
int EXPORT dtk6_CmdSet1double(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	Set to the double conversion of next token.
	 *	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
int EXPORT dtk6_CmdSet1string(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 1-argument selector by COPYING next token
	 *	into cmd->resultptr (no case conversion performed).
	 *	There MUST be enough space for it there!
	 *	Return the number of items removed from 'argv' = 1.
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 *	czValidateSelector may be:
	 *         if supplied, is a number 
	 *         which is the max length (in bytes) of the string; 
	 *         the target buffer must be 1 larget than this.
	 */

int EXPORT dtk6_CmdSetFile(char * argv[],const CMDDESCRIPTOR_T * cmd);
        /*	set both long and short forms of argv[1]
	 *	return results of short form conversion: >0 => OK
	 *	For error #'s, see vfileapi.cpp
	 *	Validate selector "xy" means:
	 *	    x = I => existing image file:
	 *		  ID => must be valid Dragon format
	 *	    x = S => existing signature file:
	 *		  SD => must be valid Dragon format
	 *	    x = C => existing color file:
	 *		  ~~ at present only checks exist
	 *	    x = P => existing polygon file:
	 *		  ~~ at present only checks exist
	 *	    x = V => existing vector file:
	 *		  ~~ at present only checks exist
	 *	    x = W => Write file: (3rd char - require extension)
	 *		  WX[ISC] - must NOT exist
	 *		  WK[ISC] - delete any existing file
	 *		  W-[ISC] - ignore any existing file
         *          x = ^ => there are two descriptions, one for read and
         *                one for write (in that order), separated by a '|'
         *                Only if the READ descriptor fails
         *                will the WRITE descriptor be tried.
         *                NOTE that using WK in this context is dangerous
	 */

int EXPORT dtk6_CmdSet1choice(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *      The important info the the first (or only ) char of next token.
	 *      If it is (case-insensitive) within the validation string, 
	 *	set *cmd->resultptr to (upper-case) of char
	 *	Return the number of items removed from 'argv' = 1,
	 *	or -1 if out-of-range
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 *	czValidateSelector must be a string of choices e.g. "DGQ"
	 *        (upper-case only)
	 */

typedef enum
    {
    COORDS_UNDEFINED,
    COORDS_PIXLINE,  /* use ulCoords */
    COORDS_PERCENT,  /*  "    "      */
    COORDS_GEO       /* use fCoords for as yet undetermined use */
    }
    REGION_FORMAT_T;

#define REGION_FORMAT_NAMES \
    "COORDS_UNDEFINED", \
    "COORDS_PIXLINE", \
    "COORDS_PERCENT", \
    "COORDS_GEO"       /* use fCoords for as yet undetermined use */

typedef struct REGION_t  /* specify a rectangular region */
    {
    float fCoords[4]; /* left, top, width, height in pct or geocoords */
    ulong ulCoords[4]; /* same order, line & pixel form */
    REGION_FORMAT_T uFormat; /* which format was found ? */
    } REGION_T;

int EXPORT dtk6_CmdSetRegion(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	Set a REGION_T structure to the values of four args
	 *      taken to define a rect. region. Args in order are:
	 *      left, top, width, height of the region
	 *	Several formats are possible of which the initially implemented
	 *	ones are: line/pixel numbers (positive longs)
	 *                percent of image: one or two digits with a % sign
	 *	'uFormat' must be set to indicate which was found.
	 */

	/******************************************************************
	 * 
	 * support fns for the abover parsing fns, but which may also 
	 * be generally useful
	 *
	 ******************************************************************/

int EXPORT dtk6_VerifyFileType(const int cType, const char * name);
     /* test whether given filename extension matches.
      * @param cType   single character specifying type:
      *                currently: 'I'mage 'C'olor 'S'ignature
      * @param name    filename to check
      * @return        1 if OK 0 if bad 2 if no extension
      */

int EXPORT dtk6_FileFind(const char * czName, const char * czSelector,
                  char * czResult, size_t uResultSz, BOOL bWPATH);
        /* like find_first(), but tries prepending DPATH, suffixing extension,
	 * etc. If successful, it applies GetShortPath and returns results.
	 * ~~ this does not handle 'special' filenames; unsure abt wildcards
	 * @param czName      file name, possibly including a path 
	 *                    and/or extension. If path or extension is
	 *                    included, they override the implications of
	 *                    czSelector (except for case).
	 * @param czSelector  character string like in dtk6_CmdSetFile()
	 * @param czResult    buffer where found name if any is put
	 * @param uResultSz   size of result buffer
	 * @param bWPATH      TRUE => use WPATH not DPATH,
	 * @return            0 if file found
	 *                    -1 for find_first() failed
	 *                    status from -2 to -9 for parsing errors (strsfn)
	 *                    -10 for memory error
	 *                    -11 or -12 from dtk6_GetShortName()
	 */

#ifdef NOMORE
/* ~~~ WHY ARE THESE EXCLUDED?? */
	/******************************************************************
	 * Validations fns suitable to be included in CMDDESCRIPTOR_T table
	 * Each returns 0 if value is OK
	 *
	 * These fns MAY use czValidateSelector from the table to select
	 * parameters to validate against. The meaning of the selector
	 * is entirely idiosyncratic to each fn.
	 */

int EXPORT dtk_ValidateOK(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/* always return 0 (i.e. good) */

int EXPORT dtk_ValidateFlag(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/* return 0 if arg matches one of the chars in czValidateSelector.
	 */


	/*	The following are all one-argument fns. 
	 *	Each handles 1-argument selector by setting *cmd->resultptr
	 *	to the conversion of next token.
	 *	Return the number of items removed from 'argv' = 1.
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 */
int EXPORT dtk_Validate1int(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
int EXPORT dtk_Validate1float(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
int EXPORT dtk_Validate1double(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
int EXPORT dtk_Validate1string(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	czValidateSelector may be:
	 *	  (to be determined)
	 */
int EXPORT dtk_ValidateFile(char * argv[],const CMDDESCRIPTOR_T * cmd);
	/*	czValidateSelector has the form E[I]-<filetype>
	 *		(where the file must exist)
	 *	  or N  (where the file does not exist)
	 *	E may be followed by: I => recognized image file type
	 */
#endif

int EXPORT dtk6_GetShortName(const char * pczSource, 
		char * pczDest, const size_t uDestSize);
	/* convert to a short-format path/file
	 * Also convert '/' to '\\'
	 * 'pczSource' may be ony a path, with or without terminating '\\'
	 * and may have any mix of '\\' and '/'.
	 * Return length of result, or if error:
	 *	-1 => node doesn't exist
	 *	-2 => it doesn't fit in 'uDestSize' (czDest is empty)
	 */

/********************************************************************
 *
 * Old-style (DRAGON 5.1 and later) command-line parsing
 *
 ********************************************************************/
#ifdef NOMORE
typedef struct CMDDESCRP
    {
    int selector;	/* the single letter which specifies the command */
    int argcount;	/* minimum number of arguments for this command */
    int (*ProcessCmd)(char * [],const struct CMDDESCRP *); /* process this */
    void * resultptr; 	/* put result here */
    } CMDDESCRIPTOR;


int dtk_ProcessCommandLine(int argc, char * argv[], 
	const CMDDESCRIPTOR CMDDESCRIPTOR[]);
#endif
int dtk_WildCard(int * argc,char *** argv);
void dtk_qhelp(const int, const char **, const char * []);
void dtk_help(const char * []);
void dtk_banner(const char * []);

EXPORT int GRS_EXP_CALL dtk_GetConfig(const char * name,
					char result[],
					const int destsize);
int dtk_fgets(const char * name,const long offset,char buf[],const int bufsize);
//int __cdecl dtk_fputs(const char * name,const char * string);
EXPORT int GRS_EXP_CALL dtk_fputs(const char * name,const char * string);
int dtk_read(const char * name,const long offset,byte buf[],const int size);
int dtk_write(const char * name,const byte buf[],const int size); /* append only */

	/*	create a complete file name in 'result'.
	 *	'name' is whatever the program user might have typed
	 *	If 'name' does not include a path (drive and/or directories)
	 *	    and if 'path' is supplied, 'path' will be used.
	 *	If 'name' does not include an extension
	 *	    and if 'ext' is supplied, 'ext' will be used.
	 *	If 'name' DOES include an extension and if 'ext' is
	 *	     supplied, the supplied extension MUST match 'ext'
	 *	'path' may or may not end in a '\'
	 *	'ext' MUST include the '.' (thus, a required no-extension
	 *	     is indicated by 'ext' = ".")
	 *	Return < 0 (DTKE_BADFILENAME or DTKE_FILENOTFOUND) for error
	 */
int dtk_FilenameBuild(const char * name,const char * path, const char * ext,
	char result[],const size_t uResultSize);/* combine to create name */

int dtk_FilenameOK(const char * name);		/* is it legal form? */
int dtk_FilenamePathOK(const char * name);	/* does the path exist? */

int dtk6_FilenameParse(const char * czFullname,
		       char czDrive[],size_t uDriveSize,
		       char czPath[],size_t uPathSize,
		       char czNode[],size_t uNodeSize,
		       char czExt[], size_t uExtSize);

int dtk_ShowMsgAt(const int line,const int col,const uint msgnum,
	const char * message,...);
int dtk_ShowMsg(const uint msgnum,const char * message,...);
#ifdef NOMORE
void dtk_PrinterEcho(int on);	/* set ShowMsg to echo on printer */
#endif 

int dtk_init(const char *);	/* initialize at startup exactly once */
int dtk_RegisterCfgFile(const char * name);

/* ~~~ Do we need/want these? */
ulong dtk_DragonVersion(void);
ulong dtk_ToolkitVersion(void);

int dtk_DragonIsRunning(void);
// int dtk_DragonErrorLevel(void);

/* ~~~ Do we need/want these? */
int dtk_MaxPixels(void);
int dtk_MaxLines(void);
int dtk_MaxImages(void);
int dtk_MaxSigs(void);
int dtk_MaxClasses(void);
int dtk_MaxBands(void);

#ifdef NOMORE
/* Obsolete functions based on old graphics mechanism */
int dtk_GrafInit(void);
int dtk_GrafPuts(const char * msg);
int dtk_GrafGetMode(void);
int dtk_TextSet(void);
int dtk_GrafSet(const int mode);
int dtk_GrafIsText(void);
int dtk_GrafIsGray(void);
int dtk_GrafRes(void);
int dtk_GrafScreenLines(void);
int dtk_GrafScreenPixels(void);
int dtk_GrafDisplayImage(const int img_index, const int iline,
		const int ipix, const int nlines,
		const int npix, const int subsample);
int dtk_GrafDisplayComposite(const int blueindex, 
		const int greenindex,
		const int redindex,
		const int iline,const int ipix, 
		const int nlines,const int npix, 
		const int subsample);
int dtk_GrafClearScreen(void);
int dtk_GrafClipWind(const uint x0, const uint y0, const uint x1,
                const uint y1);
int dtk_GrafFillWind(const ulong color_index, const uint x0, 
		const uint y0, const uint x1, 
		const uint y1);
int dtk_GrafSetColors(const char* filename);
int dtk_GrafLine(const ulong color_index, const uint x0,
		const uint y0, const uint x1, 
		const uint y1);
int dtk_GrafCircle(const ulong color_index, const uint x,
		const uint y0, const uint rad);

int dtk_MouseInit(void);
#endif

void dtk_ErrorMsgDisplay(void);

void dtk_ErrorMsgClear(void);	/* empty the error message stack */
void dtk_ErrorMsgPush(const char *);
int dtk_ErrorMsgCount(void);	/* how many are there? */
char * dtk_ErrorMsg(const int); /* get one: number 0 is newest */
int dtk_Error(const int errornum,const char * typical_msg,...);
int dtk_Fatal(const int errornum,const char * typical_msg,...);
int dtk_GetMsgNo(const int msgno,char * dest);
int dtk_GetMsg(const char * pattern,char * dest);
int dtk_RegisterMsgFile(const char * name);
int dtk_Warning(const int errornum,const char * typical_msg,...);
int dtk_FileError(void);
void dtk_PrintExit(const int ernum,const char * msg,const int level);

#ifdef DHEAD_H
void dtk_ImageHdrInit(IHEAD* hdr, const int nl, const int np);
void dtk_ImageHdrSet(IHEAD* hdr, const char* ftype, const char* filename,
	const char* bandn,const char* comment,const char* source,
	const int norm);
int dtk_ImageCalcStats(const int bitspp, const int bytespp,
        const int nl,
	const int np, DTK_IMGSTATS stats, LineAccess linefn);
int dtk_ImageHdrSetStats(const DTK_IMGSTATS stats,IHEAD* inhdr);
int dtk_ImageHdrWrite(const char* outname,IHEAD* inhdr);
int dtk_ImageHdrRewrite(const char* outname,const DTK_IMGSTATS stats,
	IHEAD* inhdr);
DTK_IMGSTATS dtk_StatStructAlloc();
void dtk_StatStructFree(DTK_IMGSTATS stats);
#endif

#ifndef IMG_H
typedef struct { byte element[256]; byte control[16]; } BYTEMAP;
#else
#ifdef R305
typedef struct { byte element[256]; byte control[16]; } BYTEMAP;
#endif
#endif

#ifdef NOMORE
int dtk_GetRemapTable(const int img_index,BYTEMAP* table);
int dtk_RemapImage(const int img_index,const BYTEMAP* table, 
                   const int change_image);
#endif

#ifndef IFILE_DEFINED
typedef void * IFILEHANDLE;
#endif
IFILEHANDLE dtk_ImageFileReadOpen(const char * filename);
int dtk_ImageFileClose(const IFILEHANDLE handle);
int dtk_ImageFilePixels(const IFILEHANDLE handle);
int dtk_ImageFileLines(const IFILEHANDLE handle);
int dtk_ImageFileName(const IFILEHANDLE handle, char* fname);
int dtk_ImageFileGetLine(const IFILEHANDLE handle, const int linenum,
	const size_t bufsize,byte * buffer, const int ipix, const int npix);
int dtk_ImageFileLoad(const char * filename, const int img_index);
int dtk_ImageFilePutLine(IFILEHANDLE handle, const int linenum,
	const byte * buffer);
#ifdef DHEAD_H
int dtk_ImageFileGetHdr(const char* filename, IHEAD* hdr);
int dtk_ImageFileSave(const char* filename,const int img_index, 
	const IHEAD* hdr, const int iline, const int ipix,
	const int nlines, const int npix);
IFILEHANDLE dtk_ImageFileWriteOpen(const char * filename,const IHEAD* hdr,
                                   const char * filetype,const int do_stats);
#endif
#ifdef NOMORE
/* Obsolete - no longer any "virtual image memory" available */
int dtk_ImageMemGetLine(const int img_index, const int linenum,
		byte * buffer, const int ipix, const int npix);
int dtk_ImageMemPutLine(const int img_index, const int linenum,
		const byte * buffer, const int npix);
int dtk_ImageMemClear(const int img_index);
int dtk_ImageMemFill(const int img_index, const int val,
		const int nlines,const int npix);
int dtk_ImageMemPixels(const int img_index);
int dtk_ImageMemLines(const int img_index);
int dtk_ImageMemMaxPixels(const int img_index);
int dtk_ImageMemMaxLines(const int img_index);
int dtk_ImageMemSetPixels(const int img_index, const int npix);
int dtk_ImageMemSetLines(const int img_index, const int nlines);
int dtk_ImageMemUpdateStats(const int img_index);
#ifdef DHEAD_H
int dtk_ImageMemGetHdr(const int img_index, IHEAD* hdr);
int dtk_ImageMemPutHdr(const int img_index, IHEAD* hdr);
#endif
#endif

#ifdef DSIG_H
/* ~~ These were never implemented */
int dtk_SignatureGet(const int signum,struct statrec * sig);
int dtk_SignaturePut(const int signum,struct statrec * sig);
int dtk_SignatureClear(void);
int dtk_SignatureCount(void);
int dtk_SignatureValid(const int signum);
#endif

/*************************************************************************
 *
 *		error numbers - old format - see TOOLERR.H
 *
 *	error numbers -1024 and lower are reserved for the toolkit
 *	error numbers -4 through -1023 are for user application programs
 *
 *************************************************************************/

#define BAD_COMMAND 		DTKE_BAD_COMMAND 	/* selector not found in table */
#define BAD_COMMAND_LINE 	DTKE_BAD_COMMAND_LINE   /* overrun end of cmd line */

#ifdef __cplusplus
    }	/* end of extern "C" */
#endif
#endif
