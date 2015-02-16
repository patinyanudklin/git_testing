#ifndef TOOLCMD2
static char RCSID[] = "$RCSfile: toolcmd.c,v $ ";
char TOOLCMD_ID[] = "@(#) " __FILE__ "  $Revision: 1.3 $$Date: 2014/12/17 07:20:39 $";
#endif
/****************************************************************
 *	TOOLCMD.C - functions for building DRAGON utilities
 *			fns related to command-lines only
 *          $Revision: 1.3 $	$Date: 2014/12/17 07:20:39 $
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
 *	$Id: toolcmd.c,v 1.3 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolcmd.c,v $
 *	Revision 1.3  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.2  1999/10/04 15:14:13  rudahl
 *	added RCS keys
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:40:20  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:40:20  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/12/23  11:38:32  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/12/23  11:38:32  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. These TOOLxxxx.C
 *    files will not be supplied to users, but TOOLKIT.H will be.
 *
 *    Refer to TOOLKIT.C for general comments. This file contains only
 *    fns used with command-line pgms. They are the same for both SA and
 *    DR libraries.
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *    Public Functions:
 *	  int dtk_ProcessCommandLine(const int count,
 *		const CMDDESCRIPTOR cmddescriptor[]);
 * 	  int dtk_CmdSetFlag(char * argv[],CMDDESCRIPTOR * cmd)
 * 	  int dtk_CmdSet1int(char * argv[],CMDDESCRIPTOR * cmd)
 * 	  int dtk_CmdSet1float(char * argv[],CMDDESCRIPTOR * cmd)
 * 	  int dtk_CmdSet1string(char * argv[],CMDDESCRIPTOR * cmd)
 *	  int dtk_WildCard(int * argc,char *** argv)
 *	  void dtk_qhelp(const int, const char **, const char * []);
 *	  void dtk_help(const char * []);
 *	  void dtk_banner(const char * []);
 *
 *		
 * 1.0	6/27/92 ktr	extracted from TOOLKIT.C
 *	12/22/93 ktr	began adapting for MSC6
 *	5/3/94 ktr	split into two obj. modules to avoid need
 *			for floating point if not used
 *	5/16/94 ktr	fixed (?) bug in Wildcard
 *	7/19/94 ktr	adapted to file fns in zfile, for compiler independence
 *	1/22/95 ktr	minor syntax change for MSC v 8.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __GCC__
#include <time.h>
#else
#include <process.h>
#include <dos.h>
#include <io.h>
#endif

#if defined _MSC_VER
#include <malloc.h>
#endif

#include	"ztoolkit.h"
#include	"zfilespc.h"
#include        "zfile.h"
#include "z_dbl.h"
#include "dtypes.h"
#include "dlimits.h"
#include "drelease.h"
#include "toolerr.h"
#include "toolkit.h"

#ifndef TEST

#undef THIS_FILE
#ifdef _DEBUG
static char THIS_FILE[] 
	= "@(#)              compiled DEBUG @ " __DATE__ " " __TIME__ ;
#else
static char THIS_FILE[] 
	= "@(#)              compiled NODEBUG @ " __DATE__ " " __TIME__ ;
#endif

#ifndef TOOLCMD2	/* everything except the floating point routine */
void TOOLCMD_1()
    { }		/* just a marker for the link file */

/*************************************************************************
 *
 *		command-line parsing fns
 *
 *************************************************************************/

int dtk_ProcessCommandLine(int argc, char * argv[], 
			const CMDDESCRIPTOR cmddescriptor[])
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
	 *	or a negative error number.
	 */
    {
    const CMDDESCRIPTOR * cmd = cmddescriptor-1;
    char ** locargv = argv;
    int counter=1; /* count tokens removed from cmd line; first is pgm name*/
    int status=-1;
    while (((*(++locargv))[0] == '-') || ((*locargv)[0] == '/'))
	{
#ifdef DEBG
	printf(">ProcessCommandLine: *argv = %s\n",*locargv);
#endif
	counter++;
	status=-1;	/* this will tell us if we didn't find selector */
	cmd = cmddescriptor-1;
	while ((++cmd)->selector)
	    {
/*
printf(">ProcessCommandLine loop: *argv[1] = %X; selector=%X\n",
	(*locargv)[1],cmd->selector);
*/
	    if (toupper((*locargv)[1]) == toupper(cmd->selector))
		{
		if ((argc - counter) <  cmd->argcount)
		    return dtk_Error(BAD_COMMAND_LINE,
			"Command line error: bad form for %1",*locargv);
		status = 
		    (*cmd->ProcessCmd)(locargv,cmd);
		if (status < 0)
		    return status;
		counter += status;
		locargv += status;
		break;
		}
	    }
/*
printf(">ProcessCommandLine: status=%d counter=%d argc = %d\n",
  status,counter,argc);
*/
	if (status < 0)		/* failed to find command */
	    return dtk_Error(BAD_COMMAND,
		"Command line error: unknown switch %1",*locargv);
	if (counter > argc)	/* overrun end of command line */
	    return dtk_Error(BAD_COMMAND_LINE,
		"Command line error: bad form for %1",*locargv);
	if (counter == argc)	/* reached end of command line */
	    break;
	}
#ifdef DEBG
    printf("exiting ProcessCommandLine: *argv = %s; status=%d; %d tokens consumed\n",
	*locargv,status,counter);
#endif
    return counter;
    }

int dtk_CmdSetFlag(char * argv[],CMDDESCRIPTOR * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 0-argument selector by setting *cmd->resultptr
	 *	to actual value of selector (changed to upper case).
	 *	Return the number of items removed from 'argv' = 0.
	 */
    {
    *(int *)cmd->resultptr = toupper((*argv)[1]);
    return 0;
    }

int dtk_CmdSet1int(char * argv[],CMDDESCRIPTOR * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 1-argument selector by setting *cmd->resultptr
	 *	to the int conversion of next token.
	 *	Return the number of items removed from 'argv' = 1.
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 */
    {
    *(int *)cmd->resultptr = atoi(argv[1]);
    return 1;
    }


int dtk_CmdSet1string(char * argv[],CMDDESCRIPTOR * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 1-argument selector by COPYING next token
	 *	into cmd->resultptr (no case conversion performed).
	 *	The MUST be enough space for it there!
	 *	Return the number of items removed from 'argv' = 1.
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 */
    {
    strcpy(cmd->resultptr,argv[1]);
    return 1;
    }

int dtk_WildCard(int * argc,char *** argv)
	/* 	This takes pointers to 'argc' & 'argv' and does
	 *	wild card expansion on any arguments containing a '*' or '?',
	 *	Any errors result in leaving the original arguments intact. 
	 *	Arguments containing wild cards that expand to 0 filenames 
	 *	are deleted. Arguments without wild cards are passed
	 *	straight through. Arguments which are preceded by a " or ', 
	 *	are passed straight through. Filenames with no extension 
	 *	(i.e. no '.') have ".*" appended (ktr: 12/91)
	 *	This is an extensively modified version of Zortech _MAIN.C
	 *	Return 0 if OK, DTKE_NOMEM if error (insuf. memory ?)
	 *	in case of error, partial nargv[] structure is not free'd, 
	 *	but who cares because we're out of memory anyway.
	 */
    {
    struct _find_t * p;
    int i,nargc=0, path_size, nargvmax=0;
    char **nargv=NULL, path[FMSIZE], *cp, *end_path;
    char * wildname;	/* ktr */
    for(i=0; i<*argc; ++i)
	{
 /*printf(">WILDCARD: i=%d cp=%s nargv=%s %s %s %s\n",
 *   i,cp,nargv[0],nargv[1],nargv[2],nargv[3]);
 */
	if (nargc + 2 >= nargvmax)
	    {
	    nargvmax = nargc + 2;
	    nargv = (char **) realloc(nargv,nargvmax * sizeof(char *));
	    if (!nargv)
		return DTKE_NOMEM;
	    }
	cp = (*argv)[i];			/* cck */
 /*printf(">WILDCARD: i=%d cp=%s nargv=%s %s %s %s\n",
 *   i,cp,nargv[0],nargv[1],nargv[2],nargv[3]);
 */

		/* if have expandable names */
	if( !(cp[-1]=='"' || cp[-1]=='\'') &&	/* cck */
		     (strchr(cp, '*') || strchr(cp, '?')) )
	    {
	    end_path = cp + strlen(cp);
	    while (end_path >= cp && *end_path != '\\' &&
		   *end_path != '/' && *end_path != ':')
		end_path--;
	    path_size = 0;
	    if(end_path >= cp)
		{	/* if got a path */
		path_size = end_path - cp + 1;
		memcpy(path, cp, path_size);
		}
	    path[path_size] = 0;
	    wildname = malloc(strlen(cp) + 5); /* ktr */
	    if (!wildname)
		return DTKE_NOMEM;
	    strcpy(wildname,cp);
	    if (strchr(++end_path,'.')==NULL) /* ktr - no ext'n? */
		strcat(wildname,".*");
	     p = find_first(wildname, 0);
	     free(wildname);
	     while (p)
		{
		cp = malloc(path_size + strlen(p->name) + 1);
		if (!cp)
		    return DTKE_NOMEM; 
		strcpy(cp, path);
		strcat(cp, p->name);
		if (nargc + 2 >= nargvmax)
		    {
		    nargvmax = nargc + 2;
		    nargv = (char **) realloc(nargv,nargvmax * sizeof(char *));
		    if (!nargv)
			return DTKE_NOMEM; 
		    }
		nargv[nargc++]  = cp;
		p = find_next();
		}
	    }
	else
	     nargv[nargc++] = (*argv)[i];
	}
    nargv[nargc] = NULL;
    *argc = nargc;
    *argv = nargv;
    return 0;
    }

void dtk_qhelp(const int argc, const char ** argv, const char * msgs[])
	/*	This function accepts the argc, argv which are the arguments
	 *	of main(), together with a table of message strings.
	 *	If the command line has a single argument consisting of
	 *	'/?' or '-?', these messages are displayed and the program 
	 *	exits.
	 */
    {
    if (((argv[1][0] == '/') || (argv[1][0] == '-')) && (argv[1][1] == '?'))
	dtk_help(msgs);
    }

void dtk_help(const char * msgs[])
	/*	This function accepts a table of message strings.
	 *	These messages are displayed and the program 
	 *	exits. The messages do not need a newline at the end;
	 *	messages will appear on succesive lines.
	 */
    {
    dtk_banner(msgs);
    exit(0);
    }

void dtk_banner(const char * msgs[])
    {
    const char ** msgptr = msgs;
    while ((msgptr != NULL) && (strlen(*msgptr)>1))
	dtk_ShowMsg(0,*msgptr++);
    }

void TOOL_CMD_END1() {}
#else
void TOOLCMD_2() {}

int dtk_CmdSet1float(char * argv[],CMDDESCRIPTOR * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 1-argument selector by setting *cmd->resultptr
	 *	to the float conversion of next token.
	 *	Return the number of items removed from 'argv' = 1.
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 */
    {
    float tf;
    DblToFloat(atof(argv[1]),&tf);
    *(float *)cmd->resultptr = tf;
    return 1;
    }
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
