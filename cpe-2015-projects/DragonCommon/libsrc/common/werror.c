#include "drelease.h"	/* should be first one */
char WERROR_ID1[] = "\0@(#) " __FILE__ " $Revision: 1.15 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/****************************************************************
 *	WERROR.C - ultimate error handler ueh()
 *
 *      ~~ Copyright 1992-2014 Kurt Rudahl and Sally Goldin
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
 *****************************************************************
 *	$Id: werror.c,v 1.15 2014/12/05 14:24:30 rudahl Exp $
 *	$Log: werror.c,v $
 *	Revision 1.15  2014/12/05 14:24:30  rudahl
 *	reconciled DragonProfessional with OpenDragon
 *
 *	Revision 1.14  2005/09/05 10:44:46  rudahl
 *	got rid of GetMsgNo
 *
 *	Revision 1.13  2005/09/05 09:28:28  rudahl
 *	got rid of GetMsgNo
 *	
 *	Revision 1.12  2005/03/19 08:00:06  rudahl
 *	lintish
 *	
 *	Revision 1.11  2005/03/01 23:04:04  goldin
 *	Fix initializer
 *	
 *	Revision 1.10  2005/03/01 21:38:22  goldin
 *	Version that compiles
 *	
 *	Revision 1.8  2004/12/25 04:21:47  rudahl
 *	lint-ish fix
 *	
 *	Revision 1.7  2004/12/23 11:47:26  rudahl
 *	replace itoa base sprintf in 32-bit
 *	
 *	Revision 1.6  2004/12/14 05:11:25  rudahl
 *	unify formerly separate compiles of werror
 *	
 *	Revision 1.5  2002/04/09 21:31:33  rudahl
 *	adapt for long filenames
 *	
 *	Revision 1.4  2001/08/28 19:32:33  rudahl
 *	more adaptations for GCC
 *	
 *	Revision 1.3  2000/06/17 21:10:04  rudahl
 *	changed ueh errnum type to signed
 *	
 *	Revision 1.2  2000/05/29 23:34:53  rudahl
 *	minor fixes
 *	
 *	Revision 1.1  1999/03/11 00:35:19  rudahl
 *	Initial revision
 *
 * Revision 4.4  1997/09/06  05:45:52  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1997/09/06  05:45:52  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/12/04  18:23:34  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/12/23  10:50:28  tower
 * final for DRAGON 4.0G.
 * removed long initialization of char arrays, to save space.
 * 
 * Revision 4.0  1993/06/04  10:01:52  tower
 * final for DRAGON Release 4.0
 * 
 *
 *****************************************************************
 *	This file implements an easy-to-use but very general
 *	error handler and reported called ueh(). It can 
 *	optionally handle errstat_set(), UI-based error windows,
 *	and i18n'd messages.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *****************************************************************
 */
/**/
/*
 *	Note: RegisterCfgFile is in file_sa.c, since it is only applicable 
 *		when GetConfig is directly linked
 *	11/30/93 ktr	fixed initialization of long string buffers
 *	12/23/93 ktr	adapt to MSC6
 *	3/29/94 ktr	changed RegisterMsgFile to locally alloc. memory
 *			compile in two parts, so FGATE can have d_Format w/o ueh
 *	7/3/94 ktr	changed ueh() so that:
 *			    'f' in format specifies msg file for this op only
 *				(same as previously, but may not work)
 *				the temporary message file is checked to exist.
 *			    'F' is obsolete, but for compat., does same as 'f'
 *			    neither -> use std msg file, 
 *				and DO NOT verify exists.
 *				(this is normal for DRAGON using FGATE).
 *	8/1/94 ktr	fixed ueh() to use default string if msg not found
 *	1/22/95 ktr	minor syntax  changes for MSC v 8.5
 *	5/14/96 ktr	fixed ueh() for better info if format errors
 *			changed variable 'errno' to 'errnum' for MSC
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *	4/9/02 ktr	adapted to long filenames by eliminating some buffers
 * 			and making others long in 32-bits
 * 5.4	12/13/2004 ktr	got rid of three separate compilation pieces
 * 5.7	2005-9-5 ktr	got rid of GetMsgNo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined WERR_3   /* viewport */
#include <dos.h>
#include <io.h>
#else
#if defined __GCC__ || defined __MINGCC__ /* for GCC only do WERR_3 */
#define WERR_2 1
#define WERR_3 1
#else
#define WERR_1 1
#define WERR_2 1
#define WERR_3 1
#include <dos.h>
#include <io.h>
#endif
#endif

#if defined __GCC__ 
#include <unistd.h>
#endif
#if defined __MINGCC__ 
#include <io.h>
#endif

#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <time.h>
#if defined _MSC_VER || defined MSC || defined __WATCOMC__
#include <malloc.h>
#endif

#include "dtypes.h"
#include "dlimits.h"

#include "files.h"
#include "werror.h"
//#include "d_msg.h"

#ifdef WERR_1
void WERROR1()
    { }		/* just a marker for the link file */

int ueh(void (_CDECLP report)(const uint,const UINT32,const uint,const char *),
	void (_CDECLP display)(const char *),
	const uint module,const ulong errbits,
	const uint level,const int errnum,const char * format,...)
	/*	function to report, to user and to system, an error condition.
	 *	If 'report' (e.g. errstat_set) and level>=NOTIFY, report to
	 *		system using 'report' fn, 'module','level','errbits',
	 *		and msg generated by 'format' (see below). This never
	 *		uses a substitute string from msg data file.
	 *	If 'display' (e.g.          ) display a message generated by
	 *		'format' (see below). This uses a substitute string
	 *		if available.
	 *	If 'level' == FATAL, do exit(1);
	 *	   WARNING - this will probably hang the system if used 
	 *		within a TSR
	 *	Return 'errnum'.
	 *	'format' is a string of chars which determine, in order, what
	 *		the following args are and what to do with them:
	 *	    'p' => arg is a near pointer to free()
	 *	    'P' => arg is a pointer to dos_free()
	 *	xx    'F' => arg is pernament filename for msg file
	 *	xx    'f' => arg is temp (this time only) filename for msg file
	 *	7/3/94 ktr	changed ueh() so that:
	 *	      'f' in format specifies msg file for this op only
	 *		  (same as previously, but may not work)
	 *  		  the temporary message file is checked to exist.
	 *	      'F' is obsolete, but for compat., does same as 'f'
	 *		  neither -> use std msg file, and DO NOT verify exists.
	 *		  (this is normal for DRAGON using FGATE).
	 *	   the remaining format chars are used to build up a message
	 *	   string for report and POSSIBLY for display (if no 'mM').
	 *	    'i' => arg is an integer to be appended (as string) to
	 *		message being built.
	 *	    'I' => arg is a long to be appended (as string) to
	 *		message being built.
	 *	    's' => arg is a string to be appended to message being built.
	 *	   if a translatable string is to be displayed, format MUST
	 *	    include an 'mM' pair specifying message number and default 
	 *	    message. All remaining args are passed to d_Format.
	 *	    if 'M' but not 'm', no file access is attempted.
	 *	    'M' => arg is a message string as described in dtk_ShowMsg
	 *		documentation, which will be replaced by message
	 *		from data file, if available.
	 *	    'm' => arg is a uint msgno equivalent to 'M'
	 */
    {
    const char * fptr=format;
    va_list arg_ptr;
    // char tmpmsgfile[FNSIZE];
    char * msgfileptr = NULL; /* errmsgfile; */
    char msgbuf[D_PRINTBUF];
    char rptbuf[D_PRINTBUF];
    char tbuf[D_NUMBUF];
    char * defaultmsg=NULL;
    uint msgno=0;
    int working=1;
    /* errmsgfile[0]=*/
    // tmpmsgfile[0]=
    tbuf[0]=msgbuf[0]=rptbuf[0]='\0';
    va_start(arg_ptr,format);
    while (*fptr && working)
	{
	char * strptrh = NULL;
	int i; uint ui; long l; void * fp; void * np;
//printf("fmt val = %c rptbuf=%s|\n",*fptr,rptbuf);
	switch(*fptr)
	    {
	    case 'P':	fp=va_arg(arg_ptr,void *); hfree(fp);
			break;
	    case 'p':	np=va_arg(arg_ptr,void *); free(np);
			break;
	    case 'M':   defaultmsg=va_arg(arg_ptr,char *);
/*			strcpy_array(msgbuf,strptrh); */
			working=0;	/* exit while() loop */
			break;
	    case 'm':	ui=va_arg(arg_ptr,uint);
			if (ui && 
				((msgfileptr==NULL)
				     || (access(msgfileptr,F_OK)==0) ))
			    msgno=ui; 
			break;
	    case 'F':   /*strptrh=va_arg(arg_ptr,char *);
			 *strcpy_array(errmsgfile,strptrh);
			 *break;
			 */
	    case 'f':   msgfileptr = va_arg(arg_ptr,char *);
			//strcpy_array(tmpmsgfile,strptrh);
			//msgfileptr = tmpmsgfile;
			break;
//#ifdef NOMORE
	    case 's':   strptrh = va_arg(arg_ptr,char *);
			strcat_array(rptbuf,strptrh);
			break;
//#endif
	    case 'i':	i=va_arg(arg_ptr,int);
			strcat_array(rptbuf,itoa(i,tbuf,10)); /* 16-bit only? */
			break;
	    case 'I':	l=va_arg(arg_ptr,long);
			strcat_array(rptbuf,ltoa(l,tbuf,10)); /* 16-bit only? */
			break;
	    default:	strcpy_array(rptbuf,"invalid format: ");
		        strcat_array(rptbuf,format);
		        strcat_array(rptbuf,"; err# ");
			strcat_array(rptbuf,itoa(errnum,tbuf,10)); /* 16-bit only? */
			break;
	    }
	fptr++;
	}
    if (report && (level >= NOTIFY))
	( * report)(module,errbits,level,rptbuf);
    if (msgno > 1)
		/* note sizeof(msgbuf) ignored when using FGATE; need ~80 bytes
		 */
	{
	char msgn[D_NUMBUF];
	sprintf(msgn,"%%e%d ",msgno);
		/* if not found, GetMsgNo supplies a string & returns < 0 */
	if ((GetMsg(msgn,msgbuf,sizeof(msgbuf))< 0) && (defaultmsg != NULL))
	    sprintf(msgbuf,"%s (message file not found)",defaultmsg);
	}
    if (strlen(msgbuf))
	d_Format(rptbuf,msgno,msgbuf,arg_ptr);
    va_end(arg_ptr);
//strcpy(rptbuf,format);
    if (display && strlen(rptbuf))
	( * display)(rptbuf);
    if (level == FATAL)
	exit(1);
    return errnum;
    }

void WERROR1_END()
    { }		/* just a marker for the link file */
#endif
#ifdef WERR_2

void WERROR2()
    { }		/* just a marker for the link file */

char * d_Format(char * buf,const int ernum,const char * msg,va_list args)
	/* 	performs the internal string formatting for 
	 *	ueh,dtk_ShowMsg, dtk_ShowMsgAt,dtk_Error, etc
	 *	Formats 'msg' into 'buf' & returns pointer to it
	 *	   ('msg' and 'buf' should NOT overlap)
	 *	'ernum' used only if 'msg' has a %0 in it
	 */
    {
    char numbuf[D_NUMBUF],*ibuf=(char *)msg,*obuf=buf;
    char * argptrs[10];
    size_t i=0,toparg=0,addedchars=0;
/*	mblen not needed, since multibyte strings can be copied just as chars */
/*    mblen(NULL,MB_LEN_MAX);*/	/* this resets its finite-state-machine */
    do
	{
	if ((*ibuf != '%') || !isdigit(*(ibuf+1)))
	    {
/*
//	    int mb = mblen(ibuf,MB_LEN_MAX); // currently, MB_LEN_MAX=1
//	    if (mb > 1)
//		{
//		memcpy(obuf,ibuf,mb);
//		obuf+= mb;
//		ibuf+= mb;
//		}
//	    else
*/
		*obuf++ = *ibuf++;
	    }
	else 
	    {
	    if (*(++ibuf) == '0')
		{
#if defined __ZTC__
		strcpy(obuf,itoa(ernum,numbuf,10));
#else
		sprintf(numbuf,"%d",ernum);
		strcat_array(obuf,numbuf);
#endif
		addedchars = strlen(numbuf);
		}
	    else
		{
		while (((char)toparg+'0') < *ibuf)
		    argptrs[++toparg]=va_arg(args,char *);
		if ((argptrs[(*ibuf)-'0']) 
			&& (strlen(argptrs[(*ibuf)-'0']) > 0))
		    {
		    strcpy(obuf,argptrs[(*ibuf)-'0']);
		    addedchars = strlen(argptrs[(*ibuf)-'0']);
		    }
		}
	    ++ibuf;
	    i += (addedchars-1);
	    obuf += addedchars;
	    }
	}
    while ((*ibuf != 0) && (++i < D_PRINTBUF));
    *obuf='\0';
    return buf;
    }

void WERROR2_END()
    { }		/* just a marker for the link file */
#endif
#ifdef WERR_3

void WERROR3()
    { }		/* just a marker for the link file */

int RegisterMsgFile(const char * name)
	/*	Specify the name of the file to be the source of
	 *	messages supplied by GetMsg(). 
	 *	@param  'name' may include a drive, path, and/or extension 
	 *              and has no size limit.
	 *	        If the path or drive is not supplied, the current 
	 *	        directory or drive is assumed. 
	 *
	 *	@return 0, 
	 *              or negativeif file specified and doesn't exist
	 */
    {
    if ((name != NULL) && strlen(name))
	if ((msg_file == NULL) || stricmp(msg_file,name)) /* different file? */
	    {
	    char * tmp = strdup(name);
	    if (tmp)
		{
		if (access(name,F_OK) != 0)
		    {
		    free(tmp);
	            return -1025;
		    }
		msg_file=tmp;
		}
	    }
    return 0;
    }


#if defined __GCC__ || defined __MINGCC__
int ueh(void (_CDECLP report)(const uint,const UINT32,const uint,const char *),
	void (_CDECLP display)(const char *),
	const uint module,const ulong errbits,
	const uint level,const int errnum,const char * format,...)
    {
    printf("Werror::ueh error # %d \n",errnum);  
    return errnum;
    }

#endif

void WERROR3_END()
    { puts(FIL_ID); }		/* just a marker for the link file */
#endif

