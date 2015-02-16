#include "drelease.h"
ID_ CFG_ID[] = 
  "\0@(#) " __FILE__ "   $Revision: 1.17 $ $Date: 2012/05/02 11:45:10 $ CFG";
D_REL_IDSTR;
/* 
 *	GETCFG.C - GetConfig() & GetMsg() functions for use with DRAGON & WF
 *		Extracted from files.c
 *      ~~ Copyright (C) 1988-2012 Kurt T. Rudahl and Sally Goldin
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
 *
 ************************************************************************
 *   $Id: getcfg.c,v 1.17 2012/05/02 11:45:10 rudahl Exp $
 *   $Log: getcfg.c,v $
 *   Revision 1.17  2012/05/02 11:45:10  rudahl
 *   copyright notices
 *
 *   Revision 1.16  2005/11/22 04:57:42  rudahl
 *   use symbol for dragon.cfg filename
 *
 *   Revision 1.15  2005/09/05 09:28:28  rudahl
 *   got rid of GetMsgNo
 *
 *   Revision 1.14  2005/03/28 09:42:04  goldin
 *   Use lower case for config file name
 *
 *   Revision 1.13  2005/03/19 06:31:51  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.13  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.12  2005/02/28 22:48:33  goldin
 *   Uncomment GetMsg and modify to use straight file I/O
 *
 *   Revision 1.11  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.10  2005/01/29 11:52:30  rudahl
 *   adapt for v 5.5
 *
 *   Revision 1.9  2004/12/23 11:50:03  rudahl
 *   replace itoa base sprintf in 32-bit, add unistd.h
 *
 *   Revision 1.8  2004/12/04 06:05:37  rudahl
 *   adapt for Mingw
 *
 *   Revision 1.7  2002/07/13 00:37:18  rudahl
 *   got rid of mem_ ops in 32-bit
 *
 *   Revision 1.6  2001/09/26 19:06:45  rudahl
 *   minor changes and de-linting for GCC
 *
 *   Revision 1.5  2001/08/22 19:17:21  rudahl
 *   fixup for gcc
 *
 *   Revision 1.4  2001/08/22 18:27:45  rudahl
 *   fixup for gcc
 *
 *   Revision 1.3  1999/07/05 14:12:49  rudahl
 *   fixup RCS fields to not use const char[]
 *
 *   Revision 1.2  1999/04/18 21:25:55  rudahl
 *   Minor changes for MSC 32 compile
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  04:45:02  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  04:45:02  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/12/20  15:51:22  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/12/23  11:02:20  tower
 * final for DRAGON 4.0G - fixed bug in size-of-file test.
 * 
 * Revision 4.0  1993/05/15  20:23:14  tower
 * final for DRAGON Release 4.0
 * 
 * Revision 1.2  92/04/30  14:23:12  tower
 * for 3.05: fixed cache buf. in GetConfig with 0 terminator
 * 
 * Revision 1.1  92/03/21  19:57:50  tower
 * Initial revision
 * 
 *
 ************************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * History
 *		  int GetConfig(char * pattern, char  * dest)
 *			like 'getenv' except gets info from DRAGON.CFG file
 *			return -1 if error, charcount if OK
 *		  int GetMsg(const char * pattern, char * dest)
 *			get message ( < D_PRINTBUF chars) from EMSG.DAT
 *			first chars match pattern, which is excluded from 'dest'
 *			return -1 if error, charcount if OK
 *
 *	4/12/92		fixed cache buffer in GetConfig to have 0 terminator
 *			avoiding ghosts from previous run
 *	7/5/92 ktr	split into two modules for compilation, dependent
 *			on compile variables CFG and MSG
 *			GetMsg now uses a local filename buffer.
 *	2/1/93 ktr	GetMsg returns empty string if no MSGFILE specified
 *	5/15/93 ktr	fixed GetCfg to terminate str on tab as well as blank
 *	3/29/94 ktr	added max buffer len param to GetMsg() & GetConfig()
 *			changed cfgfile, msgfile to pointers to save memory
 *			(to set to different value, pgm must alloc local space)
 *			moved RegisterCfgFile here, since it needs cfg_file to
 *			  be local and is always used by somebody.
 * 			changed RegisterCfgFile to locally alloc. memory;
 *			added GetMsgNo()
 *	7/19/94		minor fixes for MSC v 8
 *	9/176/94	fixed GetMsgNo to always return -1 exactly if error
 *	12/20/94 ktr	changed GetMsg() to
 *			 1. require search msg is at beginning of line.
 *			 2. terminate search if "%EOM" is found
 * 5.0	5/17/96 ktr	changed FATAL to SERIOUS error
 *	8/4/96 ktr	add PutConfig; initially only for LARGE model
 * 			 to save spece in DRAGON DOS modules
 *	8/4/97 ktr	adapted GetConfig to large model
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *      4/18/99 seg     added provision for MSC 32 compile (_WIN32)
 * 5.4	12/1/2004 ktr	modified for Mingw
 *	12/22/2004 ktr	added unistd.h for linux
 *			convert ltoa, itoa to sprintf for 32-bit versions
 * 5.5	2005-1-29 ktr	adapt for Dragon 5.5
 * 5.7	2005-9-5 ktr	got rid of GetMsgNo
 */

#include "drelease.h"	/* should be first one */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy */
#include <fcntl.h>	/* OPEN parameters	*/
#include <math.h>

#if defined __GCC__
#include <unistd.h>
#else
#include <dos.h>
#include <io.h>
#endif

#if defined __GCC__ || defined __MINGCC__
#include <sys/stat.h>
#else
#include <sys\stat.h>
#endif
#include <errno.h>
#include <limits.h>
#include <ctype.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"

#include "files.h"
#include "dragonOb.h"

void CFGX()
    { }		/* just a marker for the link file */

char * msg_file="EMSG.DAT";

int GetMsg(const char * msgno,char * dest,const int destsize)
	/*	get message ( < D_PRINTBUF && < 'destsize' chars) from msg_file
	 *	first chars match pattern, which is excluded from 'dest'
	 *	return -1 if error, charcount if OK
	 */
    {
    FILE* pInfile = NULL;
    //long offset=0;
    char strx[D_PRINTBUF];
    static char eom[] = "%EOM";
    int retval=-1;
    if (strlen(msg_file)==0)
	{
	*dest='\0';	/* this isn't an actual error */
	retval=0;
	}
    else
        {
	pInfile = fopen(msg_file,"r");
	if (pInfile != NULL)
	    {
	    while (fgets(strx,D_PRINTBUF,pInfile) != NULL)
	        {
		if (strncmp(strx,msgno,strlen(msgno))==0)
		    {
		    strncpy(dest,&strx[strlen(msgno)],destsize-1);
		    dest[destsize-1]='\0';
		    strtok(dest,"\r\n");
		    retval=strlen(dest);
		    break;
		    }
		if (strncmp(strx,eom,strlen(eom))==0)
		    break;
		}
	    fclose(pInfile);
	    }
	}
    return retval;
    }

#ifdef NOMORE // 2005-9-5 doesn't work anymore
int GetMsgNo(const int msgnum,char * dest,const int destsize)
	/*	get message ( < D_PRINTBUF && < 'destsize' chars) from msg_file
	 *	first chars match "%e<msgnum> ", which is excluded from 'dest'
	 *	return -1 if error (but a valid string put into 'dest' anyway),
	 *	charcount if OK
	 */
    {
    char msgno[D_NUMBUF];
    int tmp;
    sprintf(msgno,"%%e%d",msgnum);
    strcat(msgno," ");
		/* trailing blank in msgno forces full match of number */
    tmp=GetMsg(msgno,dest,destsize);
    if (tmp <= 0) /* can't find it? */
	{
	sprintf(dest,"message number %d",msgnum);
	tmp = -1;
	}
    return tmp;
    }
#endif

char * cfg_file=CFGFILE; // "dragon.cfg" in dragonOb.h

char * strupr(char * buf)
    {
    char * pBuf = buf;
    while (*pBuf)
        {
	*pBuf = toupper(*pBuf);
	pBuf++;
        }
    return buf;
    }

int GetConfig(const char * searchstr,char  * dest,const int destsize)
	/*	get value of matching string from DRAGON.CFG (cfg_file)
	 *	form is <searchstr>=<target>
	 *	target delim by first char <= X20, or by matching quote
	 *	copies info to errstat also ONLY if found.
	 *	Normally reads actual file only once; 
	 *	  if 'searchstr' == NULL, just read file into buffer
	 *	  'cfgbuf' and tokenize it like environment.
	 *	Return < 0 if error or no match found, else charcnt
	 *	Releases buffer if search with empty string or searchstr==NULL
	 *	size of 'dest' could be as much as CONFIGSTRLEN+1
	 */
    {
    char  * tmpptr=NULL;
    static char *  buffer = NULL;
    char loc_srch[20];
    long fsize;
    int status=0;
    *dest = '\0';
    if ((searchstr == NULL) || (strlen(searchstr)==strspn(searchstr," \r\n")))
	{
	if (buffer != NULL)
	    {
	    free (buffer);
	    buffer = NULL;
	    }
	return 0;
	}
    memset(loc_srch,0,sizeof(loc_srch));
    strncpy(loc_srch,searchstr,sizeof(loc_srch)-2);
    strcat(strupr(loc_srch),"=");
    if (buffer == NULL)
	{
	fsize = file_size(cfg_file); /* "dragon.cfg"); */
	if ((fsize < 0) || (fsize > INT_MAX))
	    {
	    return -4;		/* file not found, too big, etc */
	    }
	buffer = malloc((int)fsize+1);
	if (buffer == NULL)
	    {
	    return -1;
	    }
	status = rsf(cfg_file,buffer,(int)fsize,0L,0);
	if (status < 0)
	    {
	    free(buffer);
	    buffer = NULL;
	    return -2;
	    }
	}
    tmpptr = strstr(buffer,loc_srch);	/* search for pattern */
    if (tmpptr == NULL)			/* not found */
	status = -3 ;
    else
	{
        char termchr[]=" \r\n\t"; /* blank must be first char */
	tmpptr += strlen(loc_srch);
	if (*tmpptr == '"')
	    termchr[0] = *tmpptr++;	/* instead of ' '  */
	status=min(strcspn(tmpptr,termchr),CONFIGSTRLEN-1);
	status=min(status,destsize-1);
	memcpy(dest,tmpptr,status);
	dest[status]='\0';
	if (status>0)
	    {
	    char msgtemp[CONFIGSTRLEN+1+30];
	    memset(msgtemp,0,sizeof(msgtemp));
	    strcpy_array(msgtemp,"GetConfig: ");	/* for err logging */
	    strcat_array(msgtemp,loc_srch);
	    strncat(msgtemp,tmpptr,status);
	    }
	}
    return status;
    }

#if defined __LARGE__ || defined _WIN32
#ifdef NOTNOW
int PutConfig(const char * pczKey, const char * pczValue, const BOOL bReplace)
	/* rewrite current config file to contain a line of form:
	 *     'pczKey'='pczValue', where 'pczValue' may include a
	 *	comment prefixed by blank or tab not within quotes
	 *	If 'bReplace', delete any existing string with 'pczKey'
	 *	else add additional one
	 *	If 'pczValue'==NULL, just delete do not replace
	 *	Return 0 if OK
	 */
    {
    int retval = 0;
    char  * tmpptr=NULL;
    char  * buffer = NULL;
    int status=0;
    long lOutOffset = 0;	/* offset into output where changes start */
    long fsize = file_size(cfg_file); /* "DRAGON.CFG"); */
    if ((fsize < 0) || (fsize > INT_MAX))
	{
	retval = -4;		/* file not found, too big, etc */
	}
    else
	buffer = malloc((int)fsize + 10 + strlen(pczKey) + strlen(pczValue));
    if (buffer == NULL)
	{
	retval = -1;
	}
    else
	status = rsf(cfg_file,buffer,(int)fsize,0L,0);
    if (status < (int)fsize)
	{
	free(buffer);
	retval = -2;
	}
    else
	{
	char * nextline = buffer;
	char * thisline = buffer;
	char msgtemp[CONFIGSTRLEN];
/* printf("PutConfig:  cfg_file=%s, size=%ld, search=%s\n", 
	    cfg_file,fsize,searchstr); */
	strcpy_array(msgtemp,pczKey);
	strcat_array(strupr(msgtemp),"=");
	do
	    {
	    tmpptr = strstr(buffer,msgtemp);	/* search for pattern */
	    thisline = nextline;
	    nextline = strchr(thisline,'\n');
	    }	/* get past all lines preceeding desired line */
	while (tmpptr > nextline);	    
	if (tmpptr == NULL)
	    lOutOffset = fsize;
	else if (!bReplace)
	    lOutOffset = nextline - buffer;
	else
	    lOutOffset = thisline - buffer;
		/* append the new string */
	if ((pczValue != NULL) && strlen(pczValue))
	    {
	    strcat_array(strupr(msgtemp),pczValue);
	    status = wsfo(cfg_file,msgtemp,strlen(msgtemp),lOutOffset);
	    lOutOffset += strlen(msgtemp);
	    if (status < 0)
	        retval = status;
	    }
	if (strlen(nextline) > 2)
	    status = wsfo(cfg_file,nextline,strlen(msgtemp),lOutOffset);
	if (status < 0)
	    retval = status;
	}
    return retval;
    }
#endif
#endif

int RegisterCfgFile(const char * name)
	/*	Specify the name of the file to be the source of
	 *	info supplied by GetCfg(). 
	 *	'name' must include any necessary drive, path, and/or extension. 
	 *	If the path or drive is not supplied, the current 
	 *	directory or drive is assumed.
	 *
	 *	Return 0, or F_RSF_OPEN code if file specified and doesn't exist
	 */
    {
    if ((name != NULL) && strlen(name))
	{
	if ((cfg_file == NULL) || stricmp(cfg_file,name)) /* different file?*/
	    {
	    char * tmp = strdup(name);
	    if (tmp)
		{
		if (access(name,F_OK))
	            return DERR_FILE_OPEN;
		cfg_file=tmp;
		}
	    }
	}
    return 0;
    }

void CFG_END() { puts(FIL_ID);}
