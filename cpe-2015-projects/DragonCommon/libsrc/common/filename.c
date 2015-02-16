#include "drelease.h"
ID_ FILENAME_ID[] =
   "\0@(#) " __FILE__ " $Revision: 1.15 $ $Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;

/****************************************************************/
/* 
 *	FILENAME.C - generalized file name manipulation & validation
 *
 *          by K.T. Rudahl
 *          Version 3.0
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
 ***************************************************
 *  $Id: filename.c,v 1.15 2014/12/05 14:24:30 rudahl Exp $
 *  $Log: filename.c,v $
 *  Revision 1.15  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.14  2005/12/10 11:36:53  rudahl
 *  fixing some of the double-tilde comments
 *
 *  Revision 1.13  2005/10/01 11:08:54  rudahl
 *  missing a header
 *
 *  Revision 1.12  2005/03/19 06:31:51  rudahl
 *  CVS moved from windu; maybe some history lost
 *
 *  Revision 1.12  2005/03/13 02:40:59  rudahl
 *  fix probs found working with enhance
 *
 *  Revision 1.11  2005/02/18 22:25:39  rudahl
 *  first pass for v 5.5
 *
 *  Revision 1.10  2004/12/25 04:20:34  rudahl
 *  lint-ish fix
 *
 *  Revision 1.9  2002/08/31 23:02:42  rudahl
 *  shrank some initializations
 *
 *  Revision 1.8  2002/06/10 12:43:03  rudahl
 *  changed conditional to 32BIT
 *
 *  Revision 1.7  2002/04/09 21:31:51  rudahl
 *  adapt for long filenames, & fixed bug
 *
 *  Revision 1.6  2001/11/30 19:42:54  rudahl
 *  minor documentation
 *
 *  Revision 1.5  2001/11/28 18:58:29  rudahl
 *  added filename.c for strsfn6_grs to linux
 *
 *  Revision 1.4  2001/10/17 19:25:41  rudahl
 *  bug in new strsfn6
 *
 *  Revision 1.3  2001/10/17 17:09:17  rudahl
 *  adapted for 32-bit, log filenames, and thread-safe strsfn
 *
 *  Revision 1.2  1999/04/18 21:25:54  rudahl
 *  Minor changes for MSC 32 compile
 *
 *  Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *  first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/05  10:03:30  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/05  10:03:30  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/07/19  12:15:32  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/12/22  21:47:26  tower
 * final for DRAGON 4.0G - removed char array initialization strings.
 * 
 * Revision 4.0  1993/04/21  19:01:16  tower
 * final for DRAGON 4.00
 * 
 * Revision 3.3  91/11/25  21:36:30  tower
 * for 3.05: added EXT_SUB
 * 
 * Revision 3.2  91/06/17  13:01:20  at
 * mod. strsfn_grs to append colon to drive string. for porting
 * CGATE to Zortech for DRAGON 3.05
 * 
 * Revision 3.1  91/04/15  13:57:55  tower
 * significant revisions of strsfn_grs and filename
 * added fileinfo() to get time, date, network status, etc
 * for DRAGON 3.04
 * 
 *
 ***************************************************
 *
 *	int filename(name,extn,pattern,pat_mode,srchpath,valid_mode)
 *	    modifies basic 'name' according to strings, 'extn' & 'pattern',
 *	    & pat_mode. 'name' must be large enough to (FMSIZE) to receive
 *	    a full path/filename.
 *	 Returns verification number according to valid_mode: 
 *		< 0 => file not found (verify or findfirst) or other error
 *		  0 => correct file name created
 *		> 0 = file attributes (verify or findfirst)
 *		       bits 0-5 are std DOS bits, bit 6=FILE_TTY bit 7=FILE_NET
 *	    details:
 *		Low nybble controls the node (name & ext):
 *		           EXT_DEFAULT: 'extn' becomes ext. (if not supplied)
 *			   EXT_REQ:	ext. if supplied MUST match 'extn'
 *			   EXT_SUB:      extn if supplied replaces 
 *                              that in pattern1
 *				note that 'extn' MUST include the '.'
 *		  wild cards may be included in 'name' & 'extn' if FINDFIRST 
 *		  full regular expression capability will be added later.
 *		  actual name and path used set into 'name'
 *		  also, if 'srchpath' is non-NULL, full wildcarded name set
 *			into 'srchpath'
 *	    	Second nybble bits control path used (may be ORed):
 *		  path is either 1) supplied in 'name' or, if not,
 *				 2) current directory if 'pattern' is NULL or
 *				 3) 'pattern', if PATH_ENVI is NOT set, or
 *				 4) value of environmental named by 'pattern'
 *	obsolete!	  *  PATH_LOCAL: 	enable local dir. 
 *	obsolete! 	  *  PATH_DEFAULT: enable path spec'd in 'name'
 *	obsolete! 	  *  PATH_PAT: 	enable path(s) supplied in pattern.
 *				Pattern may have multiple paths
 *				separated by semicolons.
 *			  *  PATH_ENVI:	enable path supplied by environmental
 *				in pattern.
 *	obsolete!	  *  PATH_TREE:	enable searching subdirectories
 *		High byte is requested attributes (see DOS docs)
 *		valid_mode = 0:		just create file name. <0 => syntax err
 *		           = VERIFY:	does it exist? 0 => yes, <0 => no
 *			   = FINDFIRST: find first matching file. same returns.
 *					'name' has full path & name of found file
 *					'srchpath' if non-NULL has full path
 *					   plus search name with wildcards.
 *			   = FINDNEXT:  find next matching. 'name' & patterns
 *					ignored, but 'name' set & return attrib
 *		obsolete!! = ZAP:	if exists, delete & return 1 else 0
 *
 *	compile with DEBG for debugging version
 *		with TEST for test version (incl. debugging)
 *
 ***********************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 *      5/19/90   ktr   Added revised version of strsfn, which
 *                      does filename syntax checking 
 *	8/6/90	  ktr	modified 'filename' to use 'strsfn_grs'
 *	4/12/91   ktr	fixed & simplified strsfn_grs	
 *	4/12/91	  ktr	fixed and simplified strsfn_grs
 *			added fileinfo()
 *			significant changes to filename, viz:
 *			  old version was never fully implemented due to
 *			  excessively complex & vague specification.
 *                        New version has eliminated some features, 
 *                        fully implemented others:
 *			    ZAP is no longer permissible
 *			    'fileinfo' changed from struct  * FIND to
 *				stringptr for findfirst,next pattern
 *			    'pat_mode' values simplified
 *
 *      6/17/91   ktr   changed strsfn_grs to return colon on end of  
 *                        drive string, as intended; modified filename to
 *                        eliminate concatenation of colon.
 *
 *	8/27/91	ktr	added EXT_SUB. Also corrected decl. for filename:
 *			   srchpath cannot be 'const.
 *	11/30/93 ktr	fixed initialization of long string buffers
 *	12/22/93 ktr	began adapting for MSC6
 *	7/19/94 ktr	minor fixes for MSC v 8: findfirst, etc
 *	12/10/95 ktr	adapted for Watcom 10.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *      4/18/99  seg    changes to support 32 bit MSC 4.1 (_WIN32)
 *      10/16/2001 ktr  strsfn6_grs has extended prototype,
 *                      handles long filenames; is thread-safe
 *	4/9/02 ktr	adapted to long filenames by eliminating some buffers
 * 			and making others long in 32-bits
 * 5.4	12/23/2004 ktr	lint-ish fixes
 * 5.5	2005-2-18 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-9-30 ktr	added files.h
 */
	  
#ifdef TEST
#define DEBG
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy */
#include <fcntl.h>	/* OPEN parameters	*/
#ifndef __GCC__
//#include <dos.h>
//#include <io.h>
#endif
#include <ctype.h>      /* toupper */

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "logger.h"

#include "filename.h"

/**/
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
	       int * pPathDelim)
    {
    char * local = czFullname; /* no reason particularly for copy */
    char * e = &local[strlen(local)];
    if (pczPath != NULL)
        *pczPath = NULL;
    if (pczNode != NULL)
        *pczNode = NULL;
    if (pczExt != NULL)
        *pczExt = NULL;
    if (pczDrive != NULL)
        *pczDrive = NULL;
    if (pPathDelim != NULL)
        *pPathDelim = 0;
    while (--e >= &local[0])	/* find first delim from end */
    	if (strchr("\\/:.",*e))
	    break;
    if (e < &local[0])
        e++;
    if (*e == '.')		/* else there isn't an extension */
	{
//#ifndef __32BIT__
//    	if ((strlen(e) > 4) && (e[4] != '*')) /* ".abc*" is sometimes useful */
//	    return XTOOLONG;
//#endif
	if (pczExt != NULL)
	    * pczExt = e+1;
	*e = '\0';
	e = &local[strlen(local)];
	while (--e >= &local[0]) /* find next significant delim from end */
	    if (strchr("\\/:",*e) != NULL)
	    	break;
	}
    // now e points to either the delim, or beginning of string
     if (strchr("\\/:",*e) != NULL)
	 {
	 if (pPathDelim != NULL)
	     *pPathDelim = *e;
	 *e++ = '\0';		/* set to point to node */
	 }
//#ifndef __32BIT__
//    if (strlen(e) > 8)
//	return NTOOLONG;
//#endif
    if (strlen(e) == 0)
	return NTOOSHORT;
    if (pczNode != NULL)
        *pczNode = e;
    if (e > &local[0])		/* else no drive or path specified */
        {
	char * p;
#ifdef __GCC__ 
	p = local;
#else                    /* no drive letter for Unix */
	p = &local[1];		/* 'e' still points to node start; now '\0' */
	if (*p == ':')		/* 'p' will point to path without drive */
	    {
	    *p++ = '\0';
	    if (pczDrive != NULL)
	        *pczDrive = local;
	    }
	else
	    p--;
#endif
	if (p != e)			/* is there an actual path? */
	    {
	    if (strchr(p,':') )
	        return BADCOLON;	/* invalid path */
	    if (pczPath != NULL)
	        *pczPath = p;
	    }
	}
    return OK;
    }

/* this function is probably no longer used, except for
 * perhaps DREC. In any case, we'll get a link error if
 * we try to reference it in a Win32 build.
 * (It's awkward to fix b/c the 32 bit MSC library returns
 * file times in Unix-like format, and handles the
 * attributes differently as well.
 */

#if !defined _WIN32 && !defined __GCC__
int fileinfo(char * name,unsigned short * date, unsigned short * time)
	/*	get unopened file date and time, and extended attributes
	 *	attributes includes x40 if a device (isatty)
	 *			    x80 if a net (req. DOS 3.3)
	 *	return < 0 => error (-2 => not found, -1 => open err)
	 */
    {
    int fp;
    union REGS Regs;
/*printf(">FILEINFO: name=%s\n",name);*/
#if defined __ZTC__
    uint attribs = dos_getfileattr(name,0);
    if (attribs < 0)
#elif defined MSC || defined __WATCOMC__
    uint attribs;
    if (!_dos_getfileattr(name,&attribs))
#endif
	return -2;
/*if (strcmp(name,"CON")==0)
	fp = fileno(stdout);
else */
    if ((fp=open(name,0)) < 0)
	return -1;
    if (isatty(fp))		/* check for device */
	attribs |= 0x40;
    Regs.h.ah=0x30;		/* check for DOS 3.3 or above */
    intdos(&Regs,&Regs);
    if ((Regs.h.al > 3) || ((Regs.h.al == 3) && (Regs.h.ah > 2)))
	{
#if defined __WATCOMC__		// just slightly dif. register names
	Regs.w.ax=0x440A;	/* check for network device */
	Regs.w.bx = fp;
	intdos(&Regs,&Regs);
	if ((Regs.w.cflag==0) && (Regs.w.dx & 0x8000))
	    attribs |= 0x80;
#else
	Regs.x.ax=0x440A;	/* check for network device */
	Regs.x.bx = fp;
	intdos(&Regs,&Regs);
	if ((Regs.x.cflag==0) && (Regs.x.dx & 0x8000))
	    attribs |= 0x80;
#endif
	}
#if defined MSC || defined __ZTC__
    dos_getftime(fp,(unsigned *)date,(unsigned *)time);
#else
    dos_getftime(fp,date,time);
#endif
/*if (strcmp(name,"CON"))*/
    close(fp);
    return attribs;
    }
#endif /* not _WIN32 */

/**/
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
	 *                     other < 0 are negs of strsfn6_grs()
	 */
#if !defined __GCC__

int filename(char * pczName,const size_t uNameSize,
	     const char * extn,const char * pattern,
	     const unsigned pat_mode,char * srchpath,
	     const unsigned valid_mode)
    {
    char drv[FDSIZE];
    static BOOL bFirstTime = TRUE; /* to init the buffers */
#ifdef __32BIT__
    char path[PATH_MAX],node[PATH_MAX],ext[PATH_MAX]; /* 32 bit */
    static char fullname[PATH_MAX],savenode[PATH_MAX];
#else
    char path[FMSIZE],node[FNSIZE],ext[FESIZE+1]; /* 16-bit */
    static char fullname[FMSIZE],savenode[FNSIZE]; /* 16-bit */
#endif
    static char * nodeptr;
    struct _find_t findstruc;
    struct _find_t * findptr=&findstruc;

#if ! defined __32BIT__
    unsigned short date,time;
    int attribs;
#endif
    int status=0;
    if (bFirstTime)
        {
	bFirstTime = FALSE;
	fullname[0] = savenode[0] = '\0';
        }
    /*printf(">filename: name=%s extn=%s pattern=%s\n",pczName,extn,pattern);*/
    drv[0]=path[0]=node[0]=ext[0] = '\0';
    if ((valid_mode & (FINDNEXT | FINDFIRST)) && (srchpath==NULL))
	return NOSRCHBUF;
    if (valid_mode & 2)	/* old ZAP */
	return INVALIDMODE;
    if ((valid_mode & FINDNEXT) == 0)
	{
	char czFullname[PATH_MAX];
	char * pDrive = NULL, * pPath = NULL, * pNode = NULL, * pExtn = NULL;
	char * endptr = NULL;
	int iPathDelim = 0;
	strcpy_array(czFullname,pczName);
	status = strsfn6_grs(czFullname,
			     &pDrive,&pPath,&pNode,&pExtn,&iPathDelim);
	if (status != 0)
	    return -status;		/* negate error number */
	if ((pat_mode & EXT_REQ) && (pExtn != NULL) 
	        && (strlen(pExtn) > 0)	/* req. extension */
	    	&& stricmp(extn,pExtn))			/* doesn't match */
	    return EXTNOMATCH; /*  /0x8001; */
	if ((pat_mode & EXT_SUB) 
	      && (extn != NULL) && (strlen(extn) > 0))	/* change extension */
	    { 
	    strcpy_array(ext,extn);
	    }
	else if (pExtn != NULL)
	    {
	    strcpy_array(ext,pExtn);
	    }
	if ((strlen(ext) == 0) && (extn != NULL) && (strlen(extn) > 0) 
		&& (pat_mode & EXT_DEFAULT) )
	    { strcpy_array(ext,extn); } /* get default extn */
	fullname[0]='\0';
#ifndef __GCC__
	        /* put in the drive if any. No default. */
	if ((pDrive != NULL) 
	        && (strlen(pDrive) > 0)) /* build full path & name */
	    { 
	    strcat_array(fullname,pDrive);
	    strcat_array(fullname,":\\");
	    }
#endif
		/* build the path */
	if ((pPath != NULL) && (strlen(pPath) > 0))
	    { strcat_array(fullname,pPath); }
	      /* if we don't have any path yet, maybe 'pattern' supplies it */ 
	if ((pattern != NULL) && (strlen(pattern)>0) && (strlen(fullname)==0))
	    {
	    if (pat_mode & PATH_ENVI)
	    	{
	    	char * eptr = getenv(pattern);
	    	if (eptr != NULL)
		    { strcat_array(fullname,eptr); }
		}
	    else
	    	{ strcat_array(fullname,pattern); }
	    }
	endptr = &fullname[strlen(fullname)-1];	/* point to last char */
	if ((strchr("\\/:",*endptr) == NULL) && (endptr > fullname))
#ifdef __GCC__
	    { strcat_array(fullname,"/"); }
#else
	    { strcat_array(fullname,"\\"); }
#endif
	nodeptr = &fullname[strlen(fullname)];	/* save where nodename goes */
	strcat_array(fullname,pNode);           /* can't be NULL */
	if (strlen(ext) > 0) 			/* add extension if any */
	    { 
	    strcat_array(fullname,".");
	    strcat_array(fullname,ext);
	    }
	}
    if (valid_mode & (FINDFIRST | FINDNEXT))
	{
	strcpy(srchpath,fullname);  /* tested earlier to confirm it exists */
	findptr = find_first(fullname,pat_mode>>8);
	if (valid_mode & FINDNEXT)
	    {
	    while ((findptr != NULL) && strcmp(findptr->name,savenode))
	        findptr = find_next();
	    findptr = find_next();
	    }
	if (findptr != NULL)	/* fixup the real name */
	    {
	    strcpy(nodeptr,findptr->name);
	    strcpy_array(savenode,findptr->name);
	    }
	else
	    return FILENOTFOUND ;
	}
    if (strlen(fullname) < uNameSize)
    	strcpy(pczName,strupr(fullname));
    else
        return -7;
#ifdef __32BIT__
//   printf(">FILENAME2: win32 new fullname='%s'\n",fullname);
    if (access(fullname,0) < 0)
	return FILENOTFOUND;		/* probably not found */
    return 0;
#else
    attribs = fileinfo(fullname,&date,&time);
    if (attribs < 0)
	return FILENOTFOUND;		/* probably not found */
    return attribs;
#endif
    }
#endif // ! __GCC__

void FILENAME_END() { puts(FIL_ID);}

#ifdef OLDD
/**
*		following three functions are from Lattice source library
*		Copyright 1988 by Lattice, Inc.
*		slightly modified
*
* name		stcgfn -- isolate node portion of file name
* name		stcgfe -- get file extension
*/
						     
stcgfn(node,name)
char *node,*name;
    {
    char *p;
    int x;
    *node = '\0';
    if((x = strlen(name)) > 0)
    	for(p = name+x; x > 0; x--) 
	    switch(*--p)
		{
		case '/':
		case '\\':
xx		case ':': 	return(stccpy(node,p+1,FNSIZE)-1);
		default: 	continue;
		}
xx    return((stccpy(node,name,FNSIZE)-1));
    }

stcgfe(ext,name)
char *ext,*name;
    {
    char *p;
    int x;
    *ext = '\0';
    if((x = strlen(name)) > 0) 
    	for(p = name+x; x > 0; x--) 
	    switch(*--p)
	    	{
xx	    	case '.': 	return(stccpy(ext,p+1,FESIZE)-1);
	    	case '/':
	    	case '\\':
	    	case ':': 	return(0);
	    	}
    return(0);
    }

stccpy(to,from,length)
char *to,*from;
int length;
    {
    int i;
    for(i = 0;i < (length-1);i++) 
	if((to[i] = from[i]) == '\0')
	    break;
    if (i == (length-1)) 
	to[i] = '\0';
    return(++i);
    }

#endif
