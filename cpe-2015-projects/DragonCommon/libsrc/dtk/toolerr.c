#include "drelease.h"
char TOOLERR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.11 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*
 *	filename toolerr.c
 *		$Revision: 1.11 $ $Date: 2014/12/17 07:20:39 $	
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
 *****************************************************************
 *	$Id: toolerr.c,v 1.11 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolerr.c,v $
 *	Revision 1.11  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.10  2005/12/30 10:31:14  rudahl
 *	lintish
 *
 *	Revision 1.9  2005/09/05 10:44:46  rudahl
 *	got rid of GetMsgNo
 *	
 *	Revision 1.8  2005/06/27 11:48:21  rudahl
 *	temp disabled dtk_DragonIsRunning
 *	
 *	Revision 1.7  2005/03/19 06:33:30  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.7  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.6  2005/02/28 22:47:38  goldin
 *	Fix file ID - was duplicate
 *	
 *	Revision 1.5  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; except for toolcmd6, much work still needed
 *	
 *	Revision 1.4  2002/04/09 21:35:07  rudahl
 *	adapt for long filenames
 *	
 *	Revision 1.3  2001/10/17 19:24:10  rudahl
 *	documentation
 *	
 *	Revision 1.2  1999/07/05 14:12:50  rudahl
 *	fixup RCS fields to not use const char[]
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:37:36  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:37:36  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/11/30  12:37:58  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/11/30  12:37:58  tower
 * Initial revision
 * 
 ****************************************************************
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. These TOOLxxxx.C
 *    files will not be supplied to users, but DTK6.H will be.
 *
 *    This file contains only fns for manipulating error messages. \
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-02-21 seg	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-06-27 ktr	disabled dtk_DragonIsRunning for the moment
 * 	2005-9-5 ktr	got rid of GetMsgNo
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifdef __GCC__
#include <time.h>
#else
#include <process.h>
//#include <dos.h>
//#include <io.h>
#endif

#if defined _MSC_VER
//#include <malloc.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "IpcWrap.h"
#include "dtk6.h"
#include "werror.h"
#include "toolerr.h"

//#ifndef TEST

void TOOLERR()
    { }		/* just a marker for the link file */

/*************************************************************************
 *
 *		local data
 *
 *************************************************************************/

struct ErrMsg { int lineno; char * msg; struct ErrMsg * prev; } ;
static struct ErrMsg * toperrmsg = NULL;
static int DatFileFlag = 1;	/* set to 1 to enable pushing err strs */

typedef struct { unsigned id; char * msg; } MSG;

static char * typical_msg_list(size_t index)
    {
    static MSG errmsgs[] = 
	{
/* 1024 */
	{-DTKE_FILEREADBADMODE,  /* -1024 * F_RSF_BADSMODE */ NULL},
	{-DTKE_FILEOPEN,		"if not found "}, /* -1025 * F_RSF_OPEN */	
	{-DTKE_FILESEEK, /* -1026 * F_RSF_SEEK */	"if seek error "},
	{-DTKE_FILEREAD, /* F_RSF_READ*/	"Error reading file %2 in %1"},
	{-DTKE_FILEWRITEBADMODE, /* -1028 * F_WSF_BADSMODE	*/ NULL},
	{-DTKE_FILECREATE, /* -1029 * F_WSF_CREATE	0x20L */ NULL},
	{-DTKE_FILEAPPNDOPEN, /* -1030 * F_WSF_CR_OPEN 0x40L */ "couldn't create or open file "},
	{-DTKE_FILEALREADY, /* -1031 * F_WSF_ALREADY 0x80L*/ "file already exists "},
	{-DTKE_FILEAPPEND, /* -1032 * F_WSF_WRITE	0x100L */ NULL},
	{-DTKE_FILEAPPCLOSE, /* -1033 * F_WSF_CLOSE 0x200L */ NULL},
	{-DTKE_FILEWRTOPEN, /* -1034 * F_WSFO_OPEN_OFFSET 0x400L */ "non-zero offset, file doesn't exist "},
	{-DTKE_FILEWRTCREATE, /*  -1035	* F_WSFO_CREATE 0x800L */ NULL},
	{-DTKE_FILEWRTSEEK, /* -1036 * F_WSFO_SEEK	0x1000L */ NULL},
	{-DTKE_FILEWRITE, /* F_WSFO_WRITE */ "Error writing file %2 in %1"},
	{-DTKE_FILEWRTCLOSE, /* -1038 * F_WSFO_CLOSE 0x4000L */ NULL},
	{-DTKE_FILENOTFOUND, 	"File %2 not found in %1"},
	{-DTKE_BADHANDLE,	"Invalid handle in %1"},
	{-DTKE_NOBUF,		"Invalid argument to %1"},
	{-DTKE_BADFILENAME,	"Bad filename %1"},
	{-DTKE_NOMEM,		"Insufficient memory for local data in %1"},
	{-DTKE_FILEOUTPUTGAP, 	"Gap in output file %1"},
	{-DTKE_IMGLINETOOBIG, 	"Invalid line number %2 in %1"},
	{-DTKE_INVALIDHDR,    	"Image header not allocated or uninitialized in %1"},
	{-DTKE_BAD_COMMAND, /* -1067 */	"selector not found in table "},
	{-DTKE_BAD_COMMAND_LINE, /* -1068 */ "overrun end of cmd line "},
	{-DTKE_NO_CFG,		"Error reading .CFG file"},
	{-DTKE_BADHDR,  		"Error reading header of %2"},
	{-DTKE_NO_FGATE,		"FGATE DLL not found or installed"},
	{-DTKE_BADLOCALE,	"specified locale not available-substituting %1"},
	{-DTKE_UNKNOWN_MSG,	"unknown message"},
/* -1100 */
	{-DTKE_NO_DGRAPH,	"Graphics DLL not found or wrong version"},
	{-DTKE_GRAF_INIT_ERR,	"Error installing graphics DLL"},
	{-DTKE_GRAF_NOT_INIT,	"Graphics DLL not yet initialized"},
	{-DTKE_GRAF_TEXT,	"Graphics in text not graphics mode"},
	{-DTKE_GRAF_ERR,		"Unknown graphics error in %1"},
	{-DTKE_GRAF_OFFSCREEN, 	"Drawing operation would be invisible"},
	{-DTKE_GRAF_BAD_MODE,	"Trying to set to unavailable graphics mode %2"},
/* 1210 */
	{-DTKE_NOT_DRAGON_IMG, 	"File %2 is not a valid DRAGON image file"},
	{-DTKE_BADIMG,		"Invalid image index %1 - must be 0 for current Toolkit version"},
	{-DTKE_OUTRANGE,		"Image fill value %1 is too large"},
	{-DTKE_BADDIM,		"Invalid number of lines or pixels in %1"},
	{-DTKE_BADLINE,		"Invalid line number %2 in %1"},
	{-DTKE_BADPIX,		"Invalid pixel number %2 in %1"},
	{-DTKE_VMERR_INIT, /*-1217*/ "Virtual memory initialization error in %1"},
	{-DTKE_VMERR_READ, 	"Virtual memory read error in %1 - status was %2"},
	{-DTKE_VMERR_WRITE, 	"Virtual memory write error in %1- status was %2"},
	{-DTKE_NOHDR,		"Image number %1 does not have an allocated header"},
	{-DTKE_IMGNOTOPEN,	"Image number %1 has not been initialized"},
	{-DTKE_OPEN_ERR,		"Error accessing image file %2 in %1"},
	{-DTKE_NOIMGDATA,	"Cannot write image number %1 (no data in image)"},
	{-DTKE_HDR_WRITE,	"Error writing header to image file %2 in %1"},
        {-DTKE_IMGMEM_BYTEONLY,  "Cannot write multi-byte pixel data to image memory"}, 
	{0, 			"Error %0 in %1 (2)"}, /* default generic message */
	} ;
    size_t tmp=0;
    while (errmsgs[tmp].id && (errmsgs[tmp].id != index))
	tmp++;
    return errmsgs[tmp].msg;
    }

/*************************************************************************
 *
 *		private functions for creating toolkit & GRS private use
 *
 *************************************************************************/
static char * Lookup_Msg(int msgnum,const char* typical_msg)
       /* Return the appropriate message for message number
        * 'msgnum', based on (in order of precedence) (1) locating
        * the message number in a registered message file;
        * (2) using a typical message supplied by the caller; or
        * (3) looking up the number in the 'typical_msg_list'
        * structure above.
        *
        * Returns pointer to string if found, ptr to empty
        * string if all three lookups fail.
        *
        * This function is used by dtk_Error, dtk_Warning, dtk_Fatal.
       */
   {
   char buf[D_PRINTBUF];
   char mbuf[D_PRINTBUF];
   static char final[D_PRINTBUF];
   const char * msg = (typical_msg == NULL) 
	? typical_msg_list(msgnum)
	: typical_msg;
   
   buf[0]=mbuf[0]=final[0]='\0';
   if (msgnum > 4)
	{
	char msgn[D_NUMBUF];
	sprintf(msgn,"%%e%d ",msgnum);
	if ((GetMsg(msgn,mbuf,sizeof(mbuf)) >= 0)
	       && (strlen(mbuf) > 0))
	    msg=mbuf;
	}
   if ((msg != NULL) && (strlen(msg))) 
        {
        strcpy(final,msg);
        strtok(final,"\r\n");
        }
   return final;
   }  

/**/

static char * GetFunctionId(const unsigned long function_id)
    {
    static char IdStr[50];
    char msgn[D_NUMBUF];
    sprintf(msgn,"%%e%ld ",function_id);
    if ((DatFileFlag==0) 
	    || (GetMsg(msgn,IdStr,sizeof(IdStr)) <= 0) )
	IdStr[0]='\0';
    return IdStr;
    }

int Error(const int errornum,const char * typical_msg,
			const unsigned long function_id,const char * arg)
	/* 	same as dtk_Error() except numerical function_id
	 */
    {
    return dtk_Error(errornum,typical_msg,GetFunctionId(function_id),arg);
    }

int Fatal(const int errornum,const char * typical_msg,
			const unsigned long function_id,const char * arg)
	/* 	same as dtk_Fatal() except numerical function_id
	 */
    {
    return dtk_Fatal(errornum,typical_msg,GetFunctionId(function_id),arg);
    }

int Warning(const int warningnum,const char * typical_msg,
			const unsigned long function_id,const char * arg)
	/* 	same as dtk_Warning() except numerical function_id
	 */
    {
    return dtk_Warning(warningnum,typical_msg,GetFunctionId(function_id),arg);
    }

/*************************************************************************
 *
 *		fns for getting messages from .DAT message file
 *
 *************************************************************************/

int dtk_GetMsgNo(const int msgno,char * dest)
	/* 	Get a string from msg-file (includes '\n')
	 *	get message ( < D_PRINTBUF chars) into 'dest'
	 *	first chars match a pattern consisting of "%e###",
	 *	where ### is 'msgno'. The pattern which is not included in
	 *	the string in 'dest'
	 *	return DTKE_UNKNOWN_MSG if error, charcount if OK
	 */
    {
    char msgn[D_NUMBUF];
    int retval;
    sprintf(msgn,"%%e%d ",msgno);
    retval = GetMsg(msgn,dest,D_PRINTBUF);
    return (retval < 0) ? DTKE_UNKNOWN_MSG : retval;
    }

int dtk_GetMsg(const char * pattern,char * dest)
	/* 	Get a string from msg-file (includes '\n')
	 *	get message ( < D_PRINTBUF chars) into 'dest'
	 *	first chars match pattern, which is excluded from 'dest'
	 *	return DTKE_UNKNOWN_MSG if error, charcount if OK
	 */
    {
    int retval;
    char newpat[D_NUMBUF];
    strcpy_array(newpat,pattern);
    if ( (newpat[strlen(newpat)-1] != 0x20)
	    && (strlen(newpat)<(sizeof(newpat)-2)) )
        strcat(newpat," ");
    /* we need a trailing space because GetMsg uses strstr */
    /* so we want to make sure we match the WHOLE pattern  */
    retval = GetMsg(newpat,dest,D_PRINTBUF);
    return (retval < 0) ? DTKE_UNKNOWN_MSG : retval;
    }

int dtk_RegisterMsgFile(const char * name)
	/*	Specify the name of the file to be the source of
	 *	messages supplied by dtk_GetMsg(). 
	 *	'name' may include a drive, path, and/or extension. 
	 *	If the path or drive is not supplied, the current 
	 *	directory or drive is assumed. If an extension is supplied, 
	 *	it MUST be ".DAT". The total resulting path and file name
	 *	must be less than FMSIZE.
	 *
	 *	Return 0, or error code if file specified and doesn't exist
	 */
    {
    int status;
    DatFileFlag=1;
    status = RegisterMsgFile(name);
    if (status != 0)
        return DTKE_FILENOTFOUND;
    else
        return DTKE_OK;
    }

/*************************************************************************
 *
 *		fns for manipulating error stack
 *
 *************************************************************************/

int dtk_DragonIsRunning()
	/*	Inquire whether DRAGON is running
	 *	Returns 0 if full DRAGON system is not running, else 1
	 */
    {
	return 0;
/* ~~~
    if (qUsingMenus())
        {
	return 1;
	}
    else
        {
	return 0;
	}
*/
    }

int dtk_Error(const int errornum,const char * typical_msg,...)
	/* 	Report a serious error
	 *	Perform four functions to report an error:
	 *	    1. Create a message. see dtk_ShowMsg()
	 *	    2. If dtk_RegisterMsgFile has been done, 
	 *		push the message onto the error message stack.
	 *	    3. If DRAGON is running, report a serious error 
	 *		 *	to the DRAGON error tracking system
	 *	    4. Return the error number (which is less than 0)
	 *
	 *	'errornum', which must be negative, is multiplied by -1
	 *	and used as the message key.
	 *
	 *	Return 'errornum'
	 */
    {
    char buf[D_PRINTBUF];
    va_list args;
    buf[0]='\0';
    if (DatFileFlag)	/* are we pushing messages at all? */
	{
	const char * msg = Lookup_Msg(-errornum,typical_msg);
printf("dtk_error 2: num=%d msg='%s'\n",errornum,msg);
	va_start(args,typical_msg);
	d_Format(buf,-errornum,msg,args);
	va_end(args);
	dtk_ErrorMsgPush(buf);
	}
    return errornum;
    }

void dtk_ErrorMsgClear(void)
	/*	empty the error message stack */
    {
    struct ErrMsg * eptr = toperrmsg;
    while (eptr)
	{
	free (eptr->msg);
	free (eptr);
	eptr = eptr->prev;
	}
    toperrmsg = NULL;
    }

int dtk_ErrorMsgCount(void)
	/*	how many are there?
	 */
    {
    int counter=0;
    struct ErrMsg * eptr = toperrmsg;
    while (eptr)
	{
	counter++;
	eptr = eptr->prev;
	}
    return counter;
    }

void dtk_ErrorMsgPush(const char * msg)
    {
    struct ErrMsg * eptr = malloc(sizeof(struct ErrMsg));
    char * msgptr;
    if (eptr == NULL)
	return;
    msgptr = strdup(msg);
    if (msgptr == NULL)
	{
	free(eptr);
	return;
	}
    eptr->prev = toperrmsg;
    eptr->msg = msgptr;
    toperrmsg = eptr;
    }

char * dtk_ErrorMsg(const int index)
	/*	get one: index number 0 is newest
	 */
    {
    int counter=index;
    struct ErrMsg * eptr = toperrmsg;
    while (eptr)
	{
	if (counter-- == 0)
	    return eptr->msg;
	eptr = eptr->prev;
	}
    return NULL;	/* not found */
    }

int dtk_Fatal(const int errornum,const char * typical_msg,...)
	/*	Report a fatal error
	 *	Perform three functions to report an error:
	 *	    1. Create a message. see dtk_ShowMsg()
	 *	    2. If dtk_RegisterMsgFile has been done, 
	 *		push the message onto the error message stack.
	 *	    3a. If DRAGON is running, report a fatal error 
	 *		to the DRAGON error tracking system, then
	 *	        return the error number (which is less than 0)
	 *	    3b. If DRAGON is not running, exit from the program.
	 *	Refer to dtk_Error() for a full description.
	 */
    {
    char buf[D_PRINTBUF];
    buf[0] = '\0';
//printf("dtk_fatal 1: num=%d typ=%s flag=%d\n",errornum,typical_msg,DatFileFlag);
    if (DatFileFlag)
	{
	va_list args;
	const char * msg = Lookup_Msg(-errornum,typical_msg);
//printf("dtk_fatal 2: num=%d msg='%s'\n",errornum,msg);
	va_start(args,typical_msg);
	d_Format(buf,-errornum,msg,args);
	va_end(args);
	dtk_ErrorMsgPush(buf);
	}
//printf("dtk_fatal 3: buf=%s\n",buf);
    /* ~~~ Even if we exit here, that won't stop other dragon components */
    //exit(1);

    return errornum;
    }

int dtk_Warning(const int warningnum,const char * typical_msg,...)
	/*	Report a warning
	 *	Perform four functions to report a suspicious condition:
	 *	    1. Create a message. see dtk_showMsg()
	 *	    2. If dtk_RegisterMsgFile has been done, 
	 *		push the message onto the error message stack.
	 *	    3. If DRAGON is running, report a WARNING
	 *	       to the DRAGON error tracking system
	 *	    4. return the warning number (which is less than 0)
	 *	Refer to dtk_Error() for a full description.
	 */
    {
    char buf[D_PRINTBUF];
    va_list args;
    const char * msg;
    msg = Lookup_Msg(-warningnum,typical_msg);
    if (DatFileFlag)
	{
	va_start(args,typical_msg);
	d_Format(buf,warningnum,msg,args);
	va_end(args);
	dtk_ErrorMsgPush(buf);
	}
    return warningnum;
    }

void TOOLERR_END() { puts(FIL_ID);}		/* just a marker for the link file */

#ifdef TEST

#include <stdlib.h>
void main()
    {
    char buf[80];
    int status;
/*    dtk_PrinterEcho(1); */
    dtk_init(NULL);
/*    dtk_PrinterEcho(1); */
#ifdef DRTEST
    if (dtk_DragonIsRunning())
	{
	printf("DRAGON IS running\n");
	printf("Error word 0 is %lX\n",errstat_get(0,0xFFFFFFFFL));
	}
    else
	printf("DRAGON is NOT running\n");
#endif
    dtk_ShowMsg(22,"Testing ShowMsg %0: 2=%2 1=%1 3=%3 4=%4 9=%9 5=%5 9=%9",
	"ARG1","ARG2","ARG3","ARG4","ARG5","ARG6","ARG7","ARG8","ARG9");
    dtk_ShowMsgAt(3,5,23,"Testing 1 ShowMsgAt %0: 2=%2 1=%1 5=%5 9=%9",
	"ARG1","ARG2","ARG3","ARG4","ARG5","ARG6","ARG7","ARG8","ARG9");
    dtk_ShowMsgAt(3,15,23,"Testing 2 ShowMsgAt %0: 2=%2 1=%1 5=%5 9=%9",
	"ARG1","ARG2","ARG3","ARG4","ARG5","ARG6","ARG7","ARG8","ARG9");
    dtk_ShowMsgAt(4,-1,23,"Testing 3 ShowMsgAt %0: 2=%2 1=%1 5=%5 9=%9",
	"ARG1","ARG2","ARG3","ARG4","ARG5","ARG6","ARG7","ARG8","ARG9");
    dtk_ShowMsg(0,"");
    dtk_Error(-5,"Test message: arg=%2 errnum=%0 function=%1",
	"FUNCTION","ARG");
/*    dtk_RegisterMsgFile(NULL);*/  /* enable use of prototype messages */
    dtk_Error(-5,"Test message: arg=%2 errnum=%0 function=%1",
	"FUNCTION","ARG");
    dtk_RegisterMsgFile("TOOLKIT.DAT"); /* enable use of file messages */
    dtk_Error(-7,"Test message: arg=%2 errnum=%0 function=%1",
	"FUNCTION","ARG");
    dtk_Error(-10,"Test message: TOOLKIT.DAT has no msg 10; arg=%2 errnum=%0 function=%1",
	"FUNCTION","ARG");
    system("mcb");
    Fatal(-10,"Test message: TOOLKIT.DAT has no msg 10; arg=%2 errnum=%0 function=%1",
	FID_GrafIsText,"ARG");
#ifdef DRTEST
    if (dtk_DragonIsRunning())
	printf("DRAGON IS running\n");
    else
	printf("DRAGON is NOT running\n");
#endif
    }
#endif
