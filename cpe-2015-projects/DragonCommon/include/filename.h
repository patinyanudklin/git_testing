/*
 *	FILENAME.H
 *	prototypes necessary for filename function
 *
 *	Kurt T. Rudahl -- Sept 13, 1989
 *
 *      ~~ Copyright 1989-2014 Kurt Rudahl and Sally Goldin
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
 ************************************************************
 * $Id: filename.h,v 1.5 2014/12/05 09:58:46 rudahl Exp $
 * $Log: filename.h,v $
 * Revision 1.5  2014/12/05 09:58:46  rudahl
 * no differences between DragonProf and OpenDragon
 *
 * Revision 1.4  2005/02/18 22:26:50  rudahl
 * first pass for v 5.5
 *
 * Revision 1.3  2002/06/10 12:39:19  rudahl
 * updated docs
 *
 * Revision 1.2  2001/10/17 17:09:56  rudahl
 * adapted for 32-bit, long filenames, and thread-safe strsfn
 *
 *
 ************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 *	4/10/91 ktr	added prototype for strsfn_grs
 *	8/27/91	ktr	added EXT_SUB. Also corrected decl. for filename:
 *			   srchpath cannot be 'const.
 *	12/10/95 ktr	adapted for Watcom 10.0
 *	2/27/97 ktr	added doc. for strsfn_grs.
 *      10/16/01 ktr    adapt for long filenames and Linux and thread-safe
 * 5.5	2005-2-18 ktr	imported from Dragon Academic Edition rev 5.4.4
 */

#ifndef FILENAME_H
#define FILENAME_H

	/*	pat_mode	*/
#define EXT_DEFAULT	0x1	/* pattern1 becomes extn if not supplied */
#define EXT_REQ		0x2	/* extn if supplied MUST match pattern1 */
#define EXT_SUB		0x4	/* extn if supplied replaces that in pattern1 */
#define PATH_ENVI	0x40	/* enables searching paths spec'd by */
				/* environmental in pattern2. */
				/* Semicolon separators. */
				/* PATH_PAT | PATH_ENVI not allowed */
	/*	valid_mode	*/
#define VERIFY		1	/* does it exist? 0 if yes, -1 if no */
#define FINDFIRST	4	/* find first matching file. set 'name'. */
				/* return its attributes. */
#define FINDNEXT	8	/* find next matching. 'name' & patterns */
				/* ignored, but 'name' set & return attrib */

#ifdef __cplusplus
    extern "C" {
#endif

	/*	modifies basic 'name' according to other args.
	 *      'extn' & 'pattern' & pat_mode
	 *	returns verification number according to valid_mode: 
	 *	    < 0 => file not found or other error
	 *	    > 0 = file attributes
         *          Always returns <= 0 under _WIN32 
	 *	NOTE that 'name' & srchpath' must be big enough to receive 
 	 *	  full path&name. Also, 'srchpath' MUST be supplied for
	 *	  using FINDFIRST, NEXT	
	 * @param pczName      buffer containing string which is both 
	 *                     source and result.
	 *                     If error, this is unmodified.
	 * @param uNameSize    size of 'name' buffer.
	 * @param extn
	 * @param pattern
	 * @param pat_mode     flags indicating how to create file name:
	 * @param srchpath
	 * @param valid_mode   flags indicating how to validate file name:
	 * @return             0 => OK
	 *                     -7 => result too large for uNameSize
	 *			#define EXTNOMATCH 	-10
	 *			#define FILENOTFOUND	-11
	 *			#define NOSRCHBUF	-12
	 *			#define INVALIDMODE	-13
	 *                     other < 0 are negs of strsfn6_grs()
	 */
int filename(char * pczName,const size_t uNameSize,
	     const char * extn,const char * pattern,
	     const unsigned pat_mode,char * srchpath,
	     const unsigned valid_mode);

int stcgfn(char *,char *);
int stcgfe(char *,char *);
int stcgfp(char *,char *);
int stccpy(char *,char *,int);

/****************************************************************/
/*
 *		>> STRSFN6_GRS <<	
 *
 *	parse 'czFullname' into the four components of a DOS filename
 *      or three components of a Unix filename
 *	Return >0 if some kind of error
 *
 *   This replaces the STRSFN function supplied by Lattice
 *   and the old strsfn_grs fn to parse and validate a filename string.
 *   It is now thread-safe.
 *
 * @param czFullname   path and name as supplied
 *                     This gets modified in-situ !!!
 * @param pczDrive     if non-NULL, points to where pointer to drive string
 *                     will be placed. Resulting string does NOT include ':'.
 *                     If no drive is specified (or on Unix), result is NULL.
 *                     A colon anywhere else in czFullname is an error.   
 *                     Drive is defined as the optional single character
 *                     followed by a colon in czFullname.
 * @param pczPath      if non-NULL, points to where pointer to path string
 *                     will be placed. 'Path' is everything between the 
 *                     (optional) ':' and the rightmost '\' or '/'.
 *                     The resulting string includes neither the ':' nor the
 *                     final '\' or '/'. If no path, result is NULL.
 * @param pczNode      if non-NULL, points to where pointer to node string
 *                     will be placed. 'Node' is everything between the
 *                     rightmost ':','\','/' and the rightmost '.'.
 *                     If no node is found, an error is returned.
 * @param pczExt       if non-NULL, points to where pointer to extension string
 *                     will be placed. Ext string does NOT include '.'.
 *                     If no extension, result is NULL
 * @param pPathDelim   if non-NULL, points to integer variable where path
 *                     delimiter found (if any) will be placed, or 0. 
 * @return
 *		0 = OK
 *		2 = BADCOLON = badlyplaced : (or for Unix, any colon)
 *		5 = NTOOLONG = for 16-bit: node too long (> 8 chars)
 *		6 = XTOOLONG = for 16-bit: extn too long (> 3 chars)
 *		8 = BTOOSHORT = node = 0 chars
 *
 ****************************************************************/

int strsfn6_grs(char * czFullname,char ** pczDrive,
	       char ** pczPath,char ** pczNode,char ** pczExt,
	       int * pPathDelim);

int fileinfo(char * name,unsigned short * date, unsigned short * time);

#ifdef __cplusplus
    }
#endif
	/* error numbers for strsfn_grs */

#define OK 		0
/* #define FIXDPATH 1 */
#define BADCOLON 	-2
#define NTOOLONG 	-5
#define XTOOLONG 	-6
/* #define BADCHAR -7 */
#define NTOOSHORT 	-8

#define EXTNOMATCH 	-10
#define FILENOTFOUND	-11
#define NOSRCHBUF	-12
#define INVALIDMODE	-13

#define FILENAME_ERRMSG \
    "OK",NULL,"Misplaced colon",NULL,\
    NULL,"Node name too long","Extension too long",NULL,\
    "Node name not supplied",NULL,"Incorrect extension","File not found",\
    ">FILENAME: srchpath not supplied",">FILENAME: invalid ZAP specified"
#endif
