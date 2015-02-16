#include "drelease.h"
char TOOLKIT_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.12 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*
 *	filename toolkit.c
 *		$Revision: 1.12 $ $Date: 2014/12/17 07:20:39 $	
 *
 *      ~~ Copyright 1999-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: toolkit.c,v 1.12 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolkit.c,v $
 *	Revision 1.12  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.11  2005/09/05 10:44:46  rudahl
 *	got rid of GetMsgNo
 *
 *	Revision 1.10  2005/08/01 04:49:46  rudahl
 *	remove need for non-default dlimits.h
 *	
 *	Revision 1.9  2005/03/19 06:33:30  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.9  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.8  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; 
 *	except for toolcmd6, much work still needed
 *	
 *	Revision 1.7  2004/12/23 12:10:47  rudahl
 *	cleanup for linux,mingw
 *	
 *	Revision 1.6  2001/10/17 19:24:42  rudahl
 *	documentation
 *	
 *	Revision 1.5  2001/10/17 17:20:01  rudahl
 *	changes propagating from revs to filename.c & strsfn
 *	
 *	Revision 1.4  1999/10/04 15:15:12  rudahl
 *	typo in THIS_FILE
 *	
 *	Revision 1.3  1999/07/05 14:12:50  rudahl
 *	fixup RCS fields to not use const char[]
 *
 *	Revision 1.2  1999/04/18 21:25:55  rudahl
 *	Minor changes for MSC 32 compile
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.0.1.1.2.1  1997/09/06  06:18:00  tower
 * checkin for class class5_0
 * 
 * Revision 4.0.1.1.1.1  1997/09/06  06:18:00  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0.1.1  1993/12/23  14:05:22  tower
 * first released version for DRAGON 4.0
 * ( initial checkin of 4.0 was premature.)
 * 
 * Revision 4.0  92/06/02  10:58:36  tower
 * 
 ****************************************************************
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers.
 *
 *    The API for the toolkit users should be strictly ANSI C, so no
 *    far pointers or '//'.
 *
 *    Originally this was the primary source file for the toolkit
 *    but at this point almost all the functions have been moved
 *    to other source files. 
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 * 5.7	2005-9-5 ktr	got rid of GetMsgNo
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#if defined __GCC__
#include <unistd.h>
#else
#include <process.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "filename.h"
#include "werror.h"  // d_Format
#include "dtk6.h"
#include "toolerr.h"

//#ifndef TEST

#ifdef NOMORE
int dtk_MakeBak(const char * filename)
	/* 	if filename already exists, rename it to have BAK extension
	 * 	returns negative value if bad filename else 0 
         */
    {
    return makebak((char *) filename);
    }
#endif

int GetFileMsg(const int msgnum,char * msg,const int bufsize)
	/*	local private function - for ShowMsg() and Error()
	 *	try to get msg from file if msgnum > 1;
	 *	   if successful, copy it into 'msg' and return length
	 *	     of copied string
	 *	   else return 0
	 */
    {
    int retval=0;
    if (msgnum > 1)
	{
	char msgbuf[D_PRINTBUF];
	char msgn[D_NUMBUF];
	sprintf(msgn,"%%e%d ",msgnum);
	 /* if msg# not found, GetMsgNo supplies a string & returns < 0 */
	if (GetMsg(msgn,msgbuf,sizeof(msgbuf))< 0)
	    msgbuf[0]='\0';	/* zap dummy message */
	if (strlen(msgbuf))
	    {
	    strtok(msgbuf,"\r\n");
	    strncpy(msg,msgbuf,bufsize-1);
	    msg[bufsize-1]='\0';
	    retval=strlen(msg);
	    }
	}
    return retval;
    }

/* ~~~ Possibly this should be removed. It only works in a console window */
int dtk_ShowMsgAt(const int line,const int col,const uint msgnum,
			const char * msg,...)
	/*	-1,-1 as positions means do not reposition
	 *	In graphics mode, this function will position 
	 *	the text as specified in character rows and columns.
	 *	In text mode, position will be approximated:
	 *	   line > previous line will be preceeded by newline
	 *	   col > 0 will be created using spaces (blanks)
	 *		(col and line < 0 => do not move)
	 *	In no case will there be a <cr><lf> after the text
	 */
    {
    static int prevlineno=0;
    int len=0;
    char buf[D_PRINTBUF];
    char buf1[D_PRINTBUF];
    va_list args;
	{
	buf1[0]='\0';
	if (col > 0)
	    {
	    memset(buf1,' ',col);
	    buf1[col]='\0';
	    }
	len=strlen(buf1);
	}
    if (msg)			/* ignore if NULL */
	{ strcpy_array(buf,msg); }	/* in case we can't find it in file */
    GetFileMsg(msgnum,buf,sizeof(buf));
    va_start(args,msg);
    d_Format(&buf1[len],msgnum,buf,args);
    va_end(args);
	{
	if (line > prevlineno)
	    {
	    prevlineno = line;
	    fputc('\n',stdout);
	    }
	if (col >= 0)
	    fputc('\r',stdout);
	fprintf(stdout,buf1);
        fflush(stdout);
	}
    return 0;
    }

int dtk_ShowMsg(const uint msgnum,const char * msg,...)
	/*	show message on screen.
	 *	get message 'msgnum'' from file if possible 
	 *	else use 'msg'
	 *	If message has %1-%9 format specifiers, substitute 
	 *	string argn (1-9). If it has %0, substitute 'msgnum' 
	 *	numerical value. "%%" is also recognized.
	 *	The total string length < D_PRINTBUF (256)
	 */
    {
    char buf1[D_PRINTBUF];
    char buf[D_PRINTBUF];
    va_list args;
    buf[0]=buf1[0]='\0';
    if (msg)			/* ignore if NULL */
	{ strcpy_array(buf,msg); }	/* in case we can't find it in file */
    GetFileMsg(msgnum,buf,sizeof(buf));

    va_start(args,msg);
    d_Format(buf1,msgnum,buf,args);
    va_end(args);
    puts(buf1);
    return 0;
    }

static int already = 0;			/* > 0 => dtk_init has happened */

/*************************************************************************
 *
 *		initialization
 *
 *************************************************************************/
/* ~~~ WHAT OTHER INITIALIZATION DO WE WANT TO DO? */
/* All init related to 16-bit Dragon has now been removed. */
int dtk_init(const char * cfgfilename)
	/*	initialize at startup exactly once
	 *	If 'cfgfilename' is non-null it MUST be the name
	 *	(or full path name) of a file used as the .CFG file.
	 *	If a CFG file is found, look for LOCALE= to specify
	 *	i/o locale. Possibilities may include:
	 *		"C"	""	"USA"	"Italy"
	 *		"Netherlands"	"Norway"	
	 *		"Switzerland"	"UK"
	 *		"Japan"		"Korea"
	 *		"China"
	 *	Errors: DTKE_NO_CFG if specified .CFG files does not exist
	 *		DTKE_BADLOCALE if specified locale not available (warning)
	 *		DTKE_NO_FGATE if FGATE DLL not available (fatal)
	 *	else return 0
         */
    {
    char localename[CONFIGSTRLEN+1];
    strcpy(localename,"C");
    if (already++)	/* only call this once */
	return 0;
    if ((cfgfilename != NULL) && (strlen(cfgfilename)>1))
	{
        char * pExt = NULL;
        char* brk;
 	int status;
        char newname[PATH_MAX];
        strcpy_array(newname,cfgfilename); /* gets modified by strsfn */
        status = strsfn6_grs(newname, NULL, NULL, NULL, &pExt, NULL);
        if (status < 0)
	    return dtk_Error(DTKE_NO_CFG,NULL);
        strcpy_array(newname,cfgfilename);
        if ((pExt != NULL) && (strlen(pExt) > 1) )
            {
            if (strlen(pExt) < 4)
		return dtk_Error(DTKE_NO_CFG,NULL);
            if (strcmp(strupr(pExt),".CFG"))
		return dtk_Error(DTKE_NO_CFG,NULL);
            }
        else
            {
            brk = strpbrk(newname,".");
    	    if (brk)
   		*brk = '\0';
            strcat(newname,".CFG");            
            }
	if (RegisterCfgFile(newname))
	    return dtk_Error(DTKE_NO_CFG,NULL);
	}

    if (GetConfig("LOCALE",localename,sizeof(localename)) >= 0)
	{
	char * actual;
	setlocale(LC_ALL,localename);
	actual=setlocale(LC_ALL,NULL);
	if (stricmp(actual,localename))
	    dtk_Error(DTKE_BADLOCALE,"%1",actual);
	}
    return 0;
    }

int dtk_RegisterCfgFile(const char * name)
	/*	Specify the name of the file to be the source of
	 *	messages supplied by dtk_Getconfig(). 
	 *	'name' may include a drive, path, and/or extension. 
	 *	If the path or drive is not supplied, the current 
	 *	directory or drive is assumed. If an extension is supplied, 
	 *	it MUST be ".CFG". The total resulting path and file name
	 *	must be less than FMSIZE.
	 *
	 *	Return 0, or error code if file specified and doesn't exist
	 */
    {
    int status;
    char * pExt = NULL;
    char newname[PATH_MAX];
    strcpy_array(newname,name); /* gets modified by strsfn */
    status = strsfn6_grs(newname, NULL, NULL, NULL, &pExt, NULL);
    if (status < 0)
	return dtk_Error(DTKE_NO_CFG,NULL);
    strcpy(newname,name);
    if ((pExt != NULL) && (strlen(pExt) > 1) )
        {
        if (strlen(pExt) < 4)
	    return dtk_Error(DTKE_NO_CFG,NULL);
	if (strcmp(strupr(pExt),".CFG"))
	    return dtk_Error(DTKE_NO_CFG,NULL);
	}
    else
        {
	char* brk = strpbrk(newname,".");
	if (brk)
   	    *brk = '\0';
	strcat(newname,".CFG");            
	}
    if (RegisterCfgFile(newname) != 0)
	return DTKE_FILENOTFOUND;
    else 
	return DTKE_OK;
    }

/*************************************************************************
 *
 *		error message handling
 *
 *************************************************************************/

void dtk_PrintExit(const int ernum,const char * msg,const int level)
	/*	print message and exit at errorlevel 'level'
	 */
    {
    dtk_ShowMsg(ernum,msg);
    exit(level);	
    }

void dtk_ErrorMsgDisplay(void)
	/*	display the error message stack
	 *	in the order of oldest first
	 *	This is always called on exiting a toolkit pgm
	 *	Puts it back into text mode ONLY if there are error msgs
         */
    {
    int count = dtk_ErrorMsgCount();
    if (count > 0)
        dtk_ShowMsg(0,"\n\n\n");  /* space down */
    while (count)
	dtk_ShowMsg(0,dtk_ErrorMsg(--count));
    }

/*************************************************************************
 *
 *		Query functions
 *
 *************************************************************************/

int dtk_MaxBands()
          /*  Returns maximum number of bands DRAGON can
           *  currently handle, for classification etc.
           *  No error conditions.
           */
    {
    return D_NBAND;
    }

int dtk_MaxClasses()
          /*  Returns maximum number of classes DRAGON can
           *  currently handle, for classification etc.
           *  No error conditions.
           */
    {
    return D_NCLS;
    }

ulong dtk_ToolkitVersion()
    {
    return DRAGON_TOOLKIT_600;
    }

void TOOLKIT_END()     { puts(FIL_ID); }

/*************************************************************************
 *
 *		test program
 *
 *************************************************************************/

#ifdef TEST

char * Banner[] = 
    { 	"DRAGON Toolkit Rev 1.0 Test Program",
	"Copyright (c) 1992 Goldin-Rudahl Systems, Inc.",
	"" } ;
char * Help[] =
    {	"\nusage: tooltest [ ] infile outfile",
	"" } ;

/*int testerr(char * [],CmdDescriptor *); */
int testerr();

int testflag=0,mflag=0,gflag=0;

CmdDescriptor cmds[] =
    {
    'e',0,dtk_CmdSetFlag,&testflag,
    0
    } ;

int main(int argc,char **argv)
    {
    char buf[80];
    int status;
    int iError = 0;
    if (dtk_init("TOOLTEST.CFG")< 0)
	exit(1);
    dtk_banner(Banner);
    dtk_qhelp(argc,argv,Help);
    if (argc < 2)
	dtk_help(Help);
    status=dtk6_ProcessCommandLine(argc,argv,cmds,&iError);
    if ((status < 0) || (iError < 0))
	{
	sprintf(buf,"ERROR - CommandLine error status=%d",iError);
	dtk_ErrorMsgPush(buf);
	}
    else
	{
        sprintf(buf,"CommandLine status=%d; next token is %s; remaining tokens: %d flag=%X",
		status,*(argv+status),argc-status,testflag);
	dtk_ShowMsg(0,buf);
	}
#ifdef DR
    if (mflag)
	dtk_MouseInit();
    if (gflag)
	dtk_GrafInit();
#endif
	{
	sprintf(nbuf3,"10.3=%f",10.3);
	dtk_ShowMsg(0,"Testing showmsg() %1 %2 %3",
	    itoa(10000,nbuf,10),itoa(-10000,nbuf2,10),nbuf3);
	}
    if (testflag)
	testerr();
    dtk_PrintExit(0,"Finished",status);
    }

int testerr() /* char * argv[],CmdDescriptor * cmd) */
    {
    char buf[80];
    dtk_ErrorMsgPush("first message");
    dtk_ErrorMsgPush("second message");
    sprintf(buf,"Error Stack has %d messages",dtk_ErrorMsgCount());
    dtk_ShowMsg(0,buf);
    dtk_ErrorMsgDisplay();
    dtk_ErrorMsgClear();
    sprintf(buf,"Error Stack has %d messages",dtk_ErrorMsgCount());
    dtk_ShowMsg(0,buf);
    return 0;
    }

#endif

