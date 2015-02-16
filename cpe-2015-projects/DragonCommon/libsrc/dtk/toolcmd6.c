#include "drelease.h"
char TOOLCMD6_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.50 $$Date: 2014/12/29 03:30:57 $";
D_REL_IDSTR;
/*
 *	filename toolcmd6.c
 *		$Revision: 1.50 $ $Date: 2014/12/29 03:30:57 $	
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
 *	$Id: toolcmd6.c,v 1.50 2014/12/29 03:30:57 rudahl Exp $
 *	$Log: toolcmd6.c,v $
 *	Revision 1.50  2014/12/29 03:30:57  rudahl
 *	convert to using dragon version number
 *
 *	Revision 1.49  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.48  2011/05/20 03:54:56  rudahl
 *	protect against too many tokens
 *
 *	Revision 1.47  2007/10/03 11:37:10  goldin
 *	don't check for existence if filename is a memory image
 *
 *	Revision 1.46  2006/04/19 11:00:31  goldin
 *	Change set1Double to handle commas in lieu of decimal pts
 *	
 *	Revision 1.45  2006/01/13 14:36:43  rudahl
 *	cleanup
 *	
 *	Revision 1.44  2005/12/24 12:47:20  rudahl
 *	fixed =C handling
 *	
 *	Revision 1.43  2005/12/20 13:09:16  rudahl
 *	fix file checking for write files
 *	
 *	Revision 1.42  2005/12/11 09:52:56  rudahl
 *	got rid of czShort
 *	
 *	Revision 1.41  2005/12/10 11:40:09  rudahl
 *	ourging czShort
 *	
 *	Revision 1.40  2005/09/22 08:23:22  goldin
 *	add logging
 *	
 *	Revision 1.39  2005/09/12 12:18:16  goldin
 *	Got rid of obsolete test for dragon image - was assuming a 5.4 structure
 *	
 *	Revision 1.38  2005/09/12 07:32:50  rudahl
 *	fixes re dp.h
 *	
 *	Revision 1.37  2005/08/12 09:21:39  goldin
 *	Fix debugging message to use correct arg
 *	
 *	Revision 1.36  2005/08/03 08:03:49  goldin
 *	put dlimits.h back in
 *	
 *	Revision 1.35  2005/08/01 04:49:46  rudahl
 *	remove need for non-default dlimits.h
 *	
 *	Revision 1.34  2005/04/04 09:43:43  goldin
 *	Add tilde comment for read of dragon file
 *	
 *	Revision 1.33  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; 
 *	except for toolcmd6, much work still needed
 *	
 *	Revision 1.32  2004/12/23 12:12:04  rudahl
 *	lint-ish fix
 *	
 *	Revision 1.31  2004/11/30 09:45:11  rudahl
 *	adapt for mingw
 *	
 *	Revision 1.30  2002/06/10 19:27:39  goldin
 *	Fix handling of empty path in FileFind
 *	
 *	Revision 1.29  2002/05/08 00:13:56  rudahl
 *	working on file validation missing extension
 *	
 *	Revision 1.28  2002/05/03 00:32:35  rudahl
 *	file testing for output files now handles WPATH and,depending on the
 *	validation string, default extensions when testing for existence.
 *	
 *	Revision 1.27  2001/11/28 18:57:06  rudahl
 *	added to and revised dtk6_Filefind - 
 *	new subsection for GCC testing lower-case extensions 
 *	fixed an apparent error in the logic preceeding
 *	    the '...next...' log message.x
 *	
 *	Revision 1.26  2001/10/23 11:17:36  rudahl
 *	added TABle, GCP, and COF file types
 *	
 *	Revision 1.25  2001/10/19 20:47:53  rudahl
 *	fixed bug in FindFile
 *	
 *	Revision 1.24  2001/10/18 13:01:56  rudahl
 *	revised logic of dtk6_findfile
 *	
 *	Revision 1.23  2001/10/17 19:25:05  rudahl
 *	added dtk6_FileFind
 *	
 *	Revision 1.22  2001/10/08 15:08:27  rudahl
 *	working on =C
 *	
 *	Revision 1.21  2001/10/06 11:38:11  rudahl
 *	added provision for Special file (=C) validators
 *	
 *	Revision 1.20  2001/10/02 16:00:21  rudahl
 *	 added trace msg for invalid file case
 *	
 *	Revision 1.19  2001/09/26 19:09:15  rudahl
 *	fixup for using Unix path separators, and stud GetShortName
 *	
 *	Revision 1.18  2001/08/22 20:46:26  rudahl
 *	adapting for GCC
 *	
 *	Revision 1.17  2001/08/08 15:18:35  rudahl
 *	fixed bug in SetFile
 *	
 *	Revision 1.16  2001/08/07 20:17:37  rudahl
 *	enhanced file type validation
 *	
 *	Revision 1.15  2001/08/04 13:53:16  rudahl
 *	fixed value returned from ProcessCommandLine
 *	
 *	Revision 1.14  2001/08/04 12:33:04  rudahl
 *	improve trace output in ParseCommandLine
 *	
 *	Revision 1.13  2001/07/13 20:06:58  rudahl
 *	fixed returned error value
 *	
 *	Revision 1.12  2001/07/05 21:46:22  rudahl
 *	added buttitproofing
 *	
 *	Revision 1.11  2001/07/04 21:33:50  rudahl
 *	fixes to arg processing
 *	
 *	Revision 1.10  2001/07/03 19:58:59  rudahl
 *	fixed bug in parsing cmd lines
 *	
 *	Revision 1.9  2001/07/02 20:04:07  rudahl
 *	fixed bug in file type checking
 *	
 *	Revision 1.8  2001/06/30 11:16:38  rudahl
 *	moved some cmdline stuff from grsproc to here
 *	
 *	Revision 1.7  2001/06/29 19:44:33  rudahl
 *	improved tracing and ability to handle wildcarded files
 *	
 *	Revision 1.6  2001/06/28 21:21:04  rudahl
 *	fixes to cli parsing
 *	
 *	Revision 1.5  2000/08/06 02:19:11  rudahl
 *	 added dtk6_CmsSetRegion *.c
 *	
 *	Revision 1.4  2000/07/27 00:38:26  rudahl
 *	added debug stmt
 *	
 *	Revision 1.3  2000/06/17 21:08:07  rudahl
 *	added error return values
 *	
 *	Revision 1.2  2000/06/02 22:46:10  rudahl
 *	fixed up arg parsing
 *	
 *	Revision 1.1  1999/10/04 15:26:43  rudahl
 *	Augmented command-line facilities for DRAGON6
 *
 *
 *****************************************************************
 *
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit and DLL for DRAGON customers.
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
 * 5.7	2005-8-1 ktr	use getWorkingLines not D_DFLTIMG stuff
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#ifdef __GCC__
#include <unistd.h>
#else
#include <process.h>
#include <dos.h>
#include <io.h>
#endif
#include <ctype.h>

#if defined _MSC_VER
#include <malloc.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

#include "libdtk.h"

#include "dtypes.h"
#include "dlimits.h"
//#include "logger.h"
#include "filename.h"
#include "files.h"
#if DRAGON_VER >= 6
#include "workingMem.h"
#endif
#include "toolerr.h"
//#include "img_acc.h"
	// MAKE file for 16-bit either does or does not define TOOLCMD2
#if defined _WIN32 || defined __GCC__ || defined __MINGCC__
#include "dtk6.h"
#endif

#include "IpcWrap.h"

#ifndef TEST

#undef THIS_FILE

void TOOLCMD_6()
    { }		/* just a marker for the link file */

/*************************************************************************
 *
 *		command-line parsing fns
 *
 *************************************************************************/

int dtk6_ProcessCommandLine(int argc, char * argv[], 
			    const CMDDESCRIPTOR_T cmddescriptor[],
			    int * piErrnum)
	/*	executive function to pull commands from the program's
	 *	command line. The command style is conventional DRAGON
	 *	or UNIX-like command strings: a sequence of sets each
	 *	of which has a selector followed by zero or more arguments
	 *	Typically the selector sets may be in any sequence on the
	 *	command line. 
	 *	This function accepts the argc, argv which are the arguments
	 *	of main(), together with a table of descriptions of selector 
	 *	sets. 
	 * @return ('argv' is set to the first string not handled by the table)
	 *      either a count of how many tokens were consumed 
	 *		(to be subtracted from 'argc'),
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

    {
    char ** locargv = argv;
    int counter=0; /* count tokens removed from cmd line; first NOT pgm name*/
    int status=-1;
    BOOL bTrace = (piErrnum != NULL) ? *piErrnum : 0;
    *piErrnum = 0;
    while ((locargv != NULL)
	   && (((*(locargv))[0] == '-') || ((*locargv)[0] == '/')))
	{
	const CMDDESCRIPTOR_T * cmd = cmddescriptor-1;
	int iTableEntryNo = 0;	// for use by the parser fns
	if (bTrace)
	    logTrace("dtk6_ProcessCommandLine: *argv = %s argc=%d",
		     *locargv,argc);
	counter++;
	if (strcmp(*locargv,"-.") == 0)
	    break;
	status=-1;	/* this will tell us if we didn't find selector */
	while ((++cmd)->selector != NULL)
	    {
	      /*
	       * printf(">ProcessCommandLine loop: *argv = %s; selector=%s\n",
	       *	(*locargv),cmd->selector);
	       */
	    if (stricmp((*locargv)+1,cmd->selector) == 0)
		{
		if ((argc - counter) <  cmd->argcount)
		    { /* we don't have enough args left on cmd line */
		    *piErrnum = -1;
		    return counter; // dtk_Error BAD_COMMAND_LINE,
		    }			 
			// "Command line error: bad form for %1",*locargv);
	        if (bTrace)
                    logTrace("    About to call ProcessCmd for %s",
			     *locargv);
		status = (*cmd->ProcessCmd)(locargv,cmd);
		if (bTrace)
		   logTrace("   processing token %d status=%d "
			    "tableline#=%d for arg %s",
			    counter,status,iTableEntryNo,*locargv);
		if (status < 0)
		    {
		    *piErrnum = status - (100 * iTableEntryNo);
		    return counter;
		    }
		counter += status;
		locargv += status;
		break;
		}
	    iTableEntryNo++;	// for use by the parser fns
	    }
    /*
     * printf(">ProcessCommandLine: status=%d counter=%d argc = %d\n",
     *	  status,counter,argc);
     */
	if (status < 0)		/* failed to find command */
	    return -2;// dtk_Error(BAD_COMMAND,
		//"Command line error: unknown switch %1",*locargv);
	if (counter > argc)	/* overrun end of command line */
	    return -3; // dtk_Error(BAD_COMMAND_LINE,
		// "Command line error: bad form for %1",*locargv);
	if (counter == argc)	/* reached end of command line */
	    break;
	locargv++;
	}
    if (bTrace)
        logTrace("dtk6_ProcessCommandLine (ex) "
		 "*argv = %s; status=%d; %d tokens consumed",
		 *locargv,status,counter);
    return counter;
    }

	/*	assuming that file contains args which match 'cmdargs',
	 *	read and process it. 
	 *	Meeting a "-." implies a successful completion
	 *      @param  pczArgFilename  name of file to read
	 *      @param  pczIntro        NULL, or a string which MAY BE ignored
	 *	                        but only if it is at the beginning of
         *                              the first non-comment line of the file.
	 *                      	Comments are lines which begin with '('
	 *      @param  cmdargs         array of recognized commands
	 *	@param  piErrnum        NULL, or points to integer variable:
	 *                              on entry, non-zero => trace process
	 *                              on return is set to error number
	 *	@return number of tokens consumed
	 *      In case of error, set *piErrnum to a negative error number.
	 *        in addition to those listed above:
	 *            -10 is error opening argument file
	 *	      -40 is too many tokens
	 */
int dtk_ProcessArgFile(const char * pczArgFilename,
		       const char * pczIntro,
		       const CMDDESCRIPTOR_T cmdargs[],
		       int * piErrnum)
    {
    int iRetval = 0;
    FILE * fp = fopen(pczArgFilename,"r");
    char czCmdBuf[256];
    int iErrnum = 0;
    BOOL bTrace = (piErrnum != NULL) ? *piErrnum : 0;
    if (bTrace)
        logTrace("dtk_ProcessArgFile (en) file=%s intro='%s'",
                 pczArgFilename,pczIntro);
    if (fp == NULL)
	iErrnum = -10;
    else
	{
	int iLineNo = 0;
	memset(czCmdBuf,0,sizeof(czCmdBuf));
	// keep 3 bytes of nulls at end, for safety
	while (fgets(czCmdBuf,sizeof(czCmdBuf)-3,fp) != NULL)
	    {
	    strtok(czCmdBuf,"\r\n");	// chomp
	    if (bTrace)
		logTrace("dtk_ProcessArgFile input line='%s'; next step=%d,%d,%d",
			 czCmdBuf,
			 strlen(czCmdBuf),strspn(czCmdBuf," \t("),
			 strcspn(czCmdBuf,"(") );
	    if ((strlen(czCmdBuf) > 1) // exclude empty lines and comment lines
		    && (strspn(czCmdBuf," \t(") < strcspn(czCmdBuf,"(")))
		{
		int i = 1;
		char *toks[32];  // ~~~ 
		char * chaser = czCmdBuf;
		char * endptr = czCmdBuf + strlen(czCmdBuf); // pt to '\0'
		memset(toks,0,sizeof(toks));
		iLineNo++;	// only count non-comment lines
		if ((iLineNo == 1) && (pczIntro != NULL)
			&& (strncmp(chaser,pczIntro,strlen(pczIntro)) == 0))
		    chaser += strlen(pczIntro);
                while((*chaser != '\0') && isspace(*chaser))
                    chaser++;  // trim leading whitestuff
		toks[0] = strtok(chaser," \t");
                if (toks[0] != NULL) // e.g. if pczIntro is alone on the line
		    chaser = toks[0] + 1 + strlen(toks[0]);
		else
		    continue;
		if (bTrace)
                     logTrace("dtk_ProcessArgFile chaser=%p endptr=%p",
		              chaser,endptr);
		while ((chaser < endptr) && (i < (int)AY_COUNT(toks)-1))
		    {
                    while((*chaser != '\0') && isspace(*chaser))
                        chaser++;  // trim leading whitestuff
		    if (bTrace)
                        logTrace("    chaser=%p='%s' at line %d; toks[0]='%s'",
                            chaser,chaser,iLineNo,toks[0]);
		    if (*chaser == '\"')
			toks[i] = strtok(++chaser,"\"");
		    else
			toks[i] = strtok(chaser," \t");
		    if (bTrace)
                        logTrace("    tok %d at %p = '%s'",i,toks[i],toks[i]);
		    if (toks[i] != NULL)
			{
			chaser += (1 + strlen(toks[i]));
			while ((chaser < endptr) && (*chaser == '\0'))
			    chaser++;
			i++;
			}
		    else /* last thing on line, if any, is ptd to by chaser */
			{
                        if ((chaser != NULL) && (strlen(chaser) > 0)
			    && (chaser < endptr))
			    toks[i++] = chaser;
			break;
			}
		    if (bTrace)
                        logTrace("    trailing chaser=%p='%s' (%X %X) "
				 "endptr=%p have %d tokens last='%s'",
			         chaser,chaser,*chaser,*(chaser+1),endptr,i,
			         toks[i-1]);
		    if (i >= AY_COUNT(toks)-1) // need NULL as last one
		        {
			iErrnum = -40;
			logTrace("toolcmd6::dtk_ProcessArgFile too many tokens");
			break;
		        }
		    }
		if (iErrnum < 0)
		    break;
		iErrnum = bTrace; /* proc. cmd line will change it back */
		iRetval += dtk6_ProcessCommandLine(i,toks,cmdargs,&iErrnum);
                if (bTrace)
		    {
		    char msgbuf[2048];
		    msgbuf[0] = '\0';
		    int j=0;
		    for (j=0; j<AY_COUNT(toks); j++)
			sprintf(msgbuf+strlen(msgbuf),"'%s' ",toks[j]);
                    logTrace("    processed %d tokens this line; total = %d "
		             " toks=%s errnum=%d", 
		             i,iRetval,msgbuf,iErrnum);
		    }
		if ((strncmp(toks[i-1],"-.",2) == 0)
                       || (strncmp(toks[0],"-.",2) == 0))
		    break;
		if (iErrnum < 0)
		    break;
		}
	    }
	fclose(fp);
	}
    if (bTrace)
        logTrace("dtk_ProcessArgFile Finished err=%d returning %d",
	         iErrnum,iRetval);
    if (piErrnum != NULL)
       *piErrnum = iErrnum;
    return iRetval;
    }

int dtk6_GetShortName(const char * pczSource, char * pczDest,
		 	      const size_t uDestSize)
	/* For windows: convert '/' to '\\'
	 *    else convert '\\' to '/'
	 * Otherwise, just verify it exists and copy the source to dest.
	 * 'pczSource' may be only a path, with or without terminating '\\'
	 * and may have any mix of '\\' and '/'.
	 * Return length of result, or if error:
	 *	-21 => node doesn't exist
	 *	-22 => it doesn't fit in 'uDestSize' (czDest have whatever fits)
	 */
    {
    int iRetval = 0;
    memset(pczDest,'\0',uDestSize);

    if (find_first(pczSource,F_OK) == NULL)
     //    if (access(pczSource,0) != 0)
	iRetval = -21;
    else
//#ifdef _WIN32
//	iRetval = GetShortPathName(pczSource,pczDest,uDestSize-1);
//#else
        {
        strncpy(pczDest,pczSource,uDestSize-1);
        iRetval = strlen(pczDest);
        }
//#endif
    if (iRetval >= (int)uDestSize)
	iRetval = -22;
#ifdef __GCC__
    if (iRetval > 0)
	while (strchr(pczDest,'\\') != NULL)
	    *(strchr(pczDest,'\\')) = '/';
#else
    if (iRetval > 0)
	while (strchr(pczDest,'/') != NULL)
	    *(strchr(pczDest,'/')) = '\\'; /* ?? ~~~ */
#endif
    return iRetval;
    }

int dtk6_VerifyFileType(const int cType, const char * name)
     /* test whether given filename extension matches.
      * @param cType   single character specifying type:
      *                currently: 'I'mage 'C'olor 'S'ignature
      *                           'G'CP   'P'olygon 'V'ector
      *				  'R'=COF 'T'ab
      * @param name    filename to check (long is OK)
      * @return        1 if OK 0 if bad 2 if no extension
      */
    {
    int iRetval = 0;
    char * pExtn = strrchr(name,'.');
    char * pSlash = strrchr(name,'/');
    char * pBsh = strrchr(name,'\\');
    logTrace("dtk6_VerifyFileType type='%c' name='%s'",cType,name);
    if (cType == '\0') /* nothing to be tested so it must be OK? */ 
        iRetval = 1;
    else if ((pExtn == NULL) || (pExtn < pSlash) || (pExtn < pBsh))
        iRetval = 2;
    else if ((cType == 'I')
                && (stricmp(name+strlen(name)-4,".IMG") == 0))
        iRetval = 1;
    else if ((cType == 'S')
		&& (stricmp(name+strlen(name)-4,".SIG") == 0))
        iRetval = 1;
    else if ((cType == 'C')
		&& (stricmp(name+strlen(name)-4,".CLF") == 0))
        iRetval = 1;
    else if ((cType == 'G')
		&& (stricmp(name+strlen(name)-4,".GCP") == 0))
        iRetval = 1;
    else if ((cType == 'P')
		&& (stricmp(name+strlen(name)-4,".PLY") == 0))
        iRetval = 1;
    else if ((cType == 'R')
		&& (stricmp(name+strlen(name)-4,".COF") == 0))
        iRetval = 1;
    else if ((cType == 'T')
		&& (stricmp(name+strlen(name)-4,".TAB") == 0))
        iRetval = 1;
    else if ((cType == 'V')
		&& (stricmp(name+strlen(name)-4,".VEC") == 0))
        iRetval = 1;
    return iRetval;
    }

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
	 * @return            0 if file found (or has form '=X' : just ignore)
	 *                    -1 for find_first() failed
	 *                    status from -2 to -9 for parsing errors (strsfn)
	 *                    -20 for memory error
	 *                    -21 or -22 from dtk6_GetShortName()
	 */
int EXPORT dtk6_FileFind(const char * czName, const char * czSelector,
                  char * czResult, size_t uResultSz,BOOL bWPATH)
    {
    char czTmp[PATH_MAX];
    int iRetval = 0;
#ifdef __GCC__
    char * czSep = "/";
#else
    char * czSep = "\\";
#endif
    char * czNameDup = strdup(czName);
    int iDesiredFileType = 0; /* single char from czSelector */
    if (*czName == '=')
	return 0;
    if (czSelector != NULL)
	{
	iDesiredFileType = czSelector[0];
	if ((iDesiredFileType == 'W') && (strlen(czSelector) > 2))
	     iDesiredFileType = czSelector[2];
	}
    logTrace("dtk6_FileFind (en) name='%s' selector='%s' typecode='%c'",
             czName,czSelector,iDesiredFileType);
    if (czNameDup != NULL)
        {
        char * pDrive=NULL, * pPath=NULL, * pNode=NULL, * pExt=NULL;
        int iPathSep = 0;
        int iStatus = strsfn6_grs(czNameDup,&pDrive,&pPath,&pNode,&pExt,
	                              &iPathSep);
        if (iStatus == 0) /* else some kind of syntactic error */
            {
            if ((pDrive == NULL) && (pPath == NULL))
                GetConfig((bWPATH) ? "WPATH" : "DPATH",czTmp,sizeof(czTmp)); //~~~ use DB
	    else
		sprintf(czTmp,"%s%s%s",
	               (pDrive != NULL) ? pDrive : "",
		       (pDrive != NULL) ? ":" : "",
		       ((pPath != NULL) && (strlen(pPath) > 0)) ? pPath : czSep);
            logTrace("    Before the strchr, czTmp is %s, length is %d",
	        czTmp,strlen(czTmp));
            if (strchr("\\/:",czTmp[strlen(czTmp)-1]) == NULL)
                strcat(czTmp,czSep);
            strcat_array(czTmp,pNode);
	    if (pExt != NULL) /* maybe it wasn't really an extension*/
	        {
		strcat_array(czTmp,".");
		strcat_array(czTmp,pExt);
		}
	    iRetval = (find_first(czTmp,F_OK) == NULL) ? -1 : 0;
            logTrace("    next: trial name='%s' success=%d "
		     "parse yielded '%s' '%s' '%s' '%s'",
                     czTmp,iRetval,(pDrive!=NULL) ? pDrive : "",
                     (pPath!=NULL) ? pPath : "",
                     (pNode!=NULL) ? pNode : "",
                     (pExt!=NULL) ? pExt : "");
	    if (iRetval != 0 )
                {
		  //                if (pExt != NULL) /* maybe it wasn't really an extension*/
		  // {
#if defined __GCC__ || defined __MINGCC__
//		    char czTmp2[PATH_MAX];
//		    strcpy_array(czTmp2,czTmp);
                    switch (iDesiredFileType)
                        {
                        case 'I': strcat_array(czTmp,".img"); break;
                        case 'S': strcat_array(czTmp,".sig"); break;
                        case 'C': strcat_array(czTmp,".clf"); break;
                        case 'G': strcat_array(czTmp,".gcp"); break;
                        case 'P': strcat_array(czTmp,".ply"); break;
                        case 'R': strcat_array(czTmp,".cof"); break;
                        case 'T': strcat_array(czTmp,".tab"); break;
                        case 'V': strcat_array(czTmp,".vec"); break;
			}
//		    iRetval = (find_first(czTmp2,F_OK) == NULL) ? -1 : 0;
#else
//                    strcat_array(czTmp,".");
  //                  strcat_array(czTmp,pExt);
    //                }
                    switch (iDesiredFileType)
                        {
                        case 'I': strcat_array(czTmp,".IMG"); break;
                        case 'S': strcat_array(czTmp,".SIG"); break;
                        case 'C': strcat_array(czTmp,".CLF"); break;
                        case 'G': strcat_array(czTmp,".GCP"); break;
                        case 'P': strcat_array(czTmp,".PLY"); break;
                        case 'R': strcat_array(czTmp,".COF"); break;
                        case 'T': strcat_array(czTmp,".TAB"); break;
                        case 'V': strcat_array(czTmp,".VEC"); break;
			}
                    //}
#endif
		if (iRetval != 0) /* if GCC, we may have already found it */
		    iRetval = (find_first(czTmp,F_OK) == NULL) ? -1 : 0;
		//iRetval = access(czTmp,F_OK); /* nothing else to try */
                logTrace("    final: trial name='%s' success=%d",
                         czTmp,iRetval);
                }
            }
        else
            iRetval = iStatus;  /* syntactic error */
        free(czNameDup);
        }
    else
        iRetval = -20;          /* memory error */
    if (iRetval == 0)
	iRetval = dtk6_GetShortName(czTmp,czResult,uResultSz);
    logTrace("dtk6_FileFind (ex) returning %d result='%s'",
             iRetval,(iRetval > 0) ? czResult : "");
    return (iRetval > 0) ? 0 : iRetval;
    }

int dtk6_CmdSetFile(char * argv[],const CMDDESCRIPTOR_T * cmd)
	//	set long form of argv[[1]
	//	return results of short form conversion: >0 => OK
	//	For error #'s, see vfileapi.cpp
	//	Validate selector "xy" means:
	//	    x = I => existing image file:
	//		  ID => must be valid Dragon format
        //                IDS => 'special' filename is acceptable
	//	    x = S => existing signature file:
	//		  SD => must be valid Dragon format
        //                SDS => 'special' filename is acceptable
	//	    x = C => existing color file:
	//		  ~~ at present only checks exist
        //                CS => 'special' filename is acceptable
	//	    x = P => existing polygon file:
	//		  ~~ at present only checks exist
        //                PS => 'special' filename is acceptable
	//	    x = V => existing vector file:
	//		  ~~ at present only checks exist
	//	    x = W => Write file: (3rd char - require extension)
	//		  WX[ISC] - must NOT exist
	//		  WK[ISC] - delete any existing file
	//		  W-[ISC] - ignore any existing file
        //          x = ^ => there are two descriptions, one for read and
        //                one for write (in that order), separated by a '|'
        //                Only if the READ descriptor fails
        //                will the WRITE descriptor be tried.
        //                NOTE that using WK in this context is dangerous
	// @return	1 if OK
	//		-2 if read file doesn't exist
	//		-4 if read file should be image but is N.G.
	//		-5, -6 if read file not required type
	//		-11 if WRITE filename missing
	//		-12 if WRITE already exists and zap not allowed
	//		-13 if WRITE already exists and does not match req'd extension
	//		-1, -20, -21, -22 from dtk6_FlieFind
    {
    int iStatus = 0;
    const char * pczValR = cmd->czValidateSelector;
    const char * pczValW = cmd->czValidateSelector;
    // this will set pczShortName based on argv[1]
    char pczShortName[PATH_MAX];
    const char * pFirstChar = argv[1];
    const char * pczName = argv[1];
    logTrace("dtk6_CmdSetFile (en) '%s' ",NN(pczName));
    pczShortName[0] = '\0';
    if (pczName == NULL)
	return -1;
    if ((*pczName == '=') || (isWorkingImageFile(pczName)))
        {
	((FILENAME_T *)(cmd->resultptr))->pczLong = strdup(pczName);
	return 1;   // =C etc - just ignore
	}
    if (*pczValW == '^')
        {
        pczValR++;
        pczValW = strchr(pczValR,'W');
        }
    logTrace("dtk6_CmdSetFile '%s' valR=%s valW=%s",pczName,pczValR,pczValW);
    if (*pczValR != 'W')
	{
        const char * pczVal = pczValR;
        if (*pFirstChar == '"') /* want the REAL first char of arg */
             pFirstChar++;
	iStatus = dtk6_FileFind(pFirstChar,pczVal,pczShortName,
				sizeof(pczShortName),FALSE);
	if ((iStatus == 0) && (strlen(pczShortName) == 0))
            strcpy(pczShortName,pczName);

         /* for 'special' filenames, just copy the special form */
#ifdef NOMORE // 2005-12-9 the =M or ( forms no longer get this far
        if ((strcmp(pczValR,"IDS") == 0) && (*pFirstChar == '=')) 
            {
            strcpy(pczShortName,argv[1]);
            iStatus = strlen(pczShortName);
            }
        else if (((strcmp(pczValR,"SDS") == 0) && (*pFirstChar == '(')) 
               ||((strcmp(pczValR,"CS") == 0) && (*pFirstChar == '(')) 
               ||((strcmp(pczValR,"PS") == 0) && (*pFirstChar == '('))) 
            {
            strcpy(pczShortName,argv[1]);
            iStatus = strlen(pczShortName);
            }
	else
#endif 
	if (find_first(pczShortName,F_OK) == NULL)
	    iStatus = -2;	/* doesn't exist */
/* ~~~ The code below assumes the old Dragon header structure */
	else if ((strcmp(pczVal,"ID") == 0)
                   && (dtk6_VerifyFileType('I',pczShortName) != 1))
	    {			/* valid Dragon .IMG file? */
	    logTrace("dtk6_CmdSetFile bad image file '%s'",
		     pczShortName);
	    iStatus = -4;
	    }
#ifdef NOTNOW
   /* ~~~ This is Dragon 5.4 specific. Also a file bigger than
     the limits should not be an eror. 
     Leave out for now.
    */

	    ushort uSize[2];
  	    if (rsf(pczShortName,uSize,sizeof(uSize),0,0) < (int)sizeof(uSize))
		iStatus = -3;
//	    else if ((uSize[0] > D_MAXIMGLINES) || (uSize[1] > D_MAXIMGPIX)
	    else if ((uSize[0] > getWorkingLines()) 
		   || (uSize[1] > getWorkingPixels())
                   || (dtk6_VerifyFileType('I',pczShortName) != 1))
//		   || (stricmp(pczShortName+strlen(pczShortName)-4,".IMG") != 0))
	        {
	        logTrace("bad file '%s' size=%d x %d",
                   pczShortName,uSize[0],uSize[1]);
		iStatus = -4;
                }
#endif
	else if ((strcmp(pczVal,"SD") == 0)
                && (dtk6_VerifyFileType('S',pczShortName) != 1))
	    iStatus = -5;
	else if ((strcmp(pczVal,"C") == 0)
                && (dtk6_VerifyFileType('C',pczShortName) != 1))
	    iStatus = -6;
	else if ((strcmp(pczVal,"P") == 0)
                && (dtk6_VerifyFileType('P',pczShortName) != 1))
	    iStatus = -6;
	else if ((strcmp(pczVal,"V") == 0)
                && (dtk6_VerifyFileType('V',pczShortName) != 1))
	    iStatus = -6;
        logTrace("dtk_CmdSetFile READ '%s' becomes '%s' status=%d",
		 pczName,pczShortName,iStatus);
	}
    if (iStatus < 0)
        logTrace("dtk_CmdSetFile READ of '%s' failed; validations='%s','%s'",
		pczName,(pczValW != NULL) ? pczValW : "NONE",
	        (pczValR != NULL) ? pczValR : "NONE");
    if ((*pczValW == 'W') && ((iStatus < 0) || (*pczValR == 'W'))) 
	{
        const char * pczVal = pczValW;
        iStatus = 0;  /* try again */
	logTrace("dtk_CmdSetFile WRITE trying for an output file '%s' (was '%s')",
			pczShortName,argv[1]);
	if (strlen(argv[1]) == 0)
	    iStatus = -11;	/* too long or bad form */
//	else if (access(argv[1],F_OK) == 0)
	    /* use first char of pczValR to signify the desired extension */
	// NOTE: dtk6_FileFind will zap pczShortname
	else if (dtk6_FileFind(pFirstChar,pczValR,pczShortName,
			       sizeof(pczShortName),TRUE) == 0)
	    {			/* already exists */
	    logTrace("Output file '%s' (was '%s')already exists",
			pczShortName,argv[1]);
	    if (*(pczVal+1) == 'K')
		remove(pczName);
	    else if (*(pczVal+1) == 'X')
		iStatus = -12;
	    }
        if (iStatus == 0)
            {
            int ifs = dtk6_VerifyFileType(*(pczVal+2),pFirstChar);
            if (ifs == 0) /* fails to match req'd extn */
                iStatus = -13;
//            if (ifs == 2) /* accept no-extension or matches */
//                iStatus = -14;
//	if (iStatus == -14)
//	    iStatus = 0; /* return OK, but short name not set */
//	else
	    strcpy_array(pczShortName,pFirstChar); 
            }
	if (strlen(pczShortName) == 0)
	    iStatus = -11;
	}
    if (iStatus >= 0)
	((FILENAME_T *)(cmd->resultptr))->pczLong = strdup(pczShortName);
    logTrace("dtk_CmdSetFile (ex) status=%d newname='%s'",iStatus,pczShortName);
    return (iStatus < 0) ? iStatus : 1;
    }

#ifdef NOTMOVED /* in dtk6.h */
typedef struct REGION_t  /* specify a rectangular region */
    {
    float fCoords[4]; /* left, top, width, height in pct or geocoords */
    ulong ulCoords[4]; /* same order, line & pixel form */
    REGION_FORMAT_T uFormat; /* which format was found ? */
    } REGION_T;
#endif

int dtk6_CmdSet1choice(char * argv[],const CMDDESCRIPTOR_T * cmd)
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
    {
    int retval = -1;
    char cResult = toupper(*(argv[1]));
    char * pFound = strchr(cmd->czValidateSelector,cResult);
    logTrace("dtk6_CmdSet1choice - cResult is %c pFound = %x", 
             cResult,pFound);
    if (pFound != NULL)
        {
	retval = 1;
	*(char *)cmd->resultptr = cResult;
	}
    return retval;
    }

int EXPORT dtk6_CmdSetRegion(char * argv[],const CMDDESCRIPTOR_T * cmd)
	/*	Set a REGION_T structure to the values of four args
	 *      taken to define a rect. region. Args in order are:
	 *      left, top, width, height of the region
	 *	Several formats are possible of which the initially implemented
	 *	ones are: line/pixel numbers (positive longs)
	 *                percent of image: one or two digits with a % sign
	 *	'uFormat' must be set to indicate which was found.
	 */
    {
    int iStatus = 4;
//    const char * pczVal = cmd->czValidateSelector;
    int i;
    for (i=0; i<4; i++)
        {
        char * arg = argv[i+1];
        char * endarg = NULL;
        REGION_T * resptr = (REGION_T *)cmd->resultptr;
        if ((arg == NULL) || (strlen(arg) == 0))
            {
            iStatus = -31; /* not enough args */
            break;
            }
        resptr->ulCoords[i] = strtoul(arg,&endarg,10);
        if (endarg == arg)
            {
            iStatus = -32; /* unknown format */
            break;
            }
        if (i == 0)
            resptr->uFormat = (*endarg == '%') ? COORDS_PERCENT 
	                                       : COORDS_PIXLINE;
        else if (((resptr->uFormat==COORDS_PERCENT) && (*endarg != '%'))
              || ((resptr->uFormat==COORDS_PIXLINE) && (*endarg == '%')))
            {
            iStatus = -33; /* mixed format */
            break;
            }
        }
    return iStatus;
    }

int dtk6_CmdSetFlag(char * argv[],const CMDDESCRIPTOR_T * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 0-argument selector by setting *cmd->resultptr
	 *	to actual value of selector (changed to upper case).
	 *	return 0 if arg matches one of the chars in
	 *	czValidateSelector.
	 *	else -1;
	 */
    {
    int iResult = toupper((*argv)[1]);
    *(int *)cmd->resultptr = iResult;
    return (strchr(cmd->czValidateSelector,iResult) == NULL) ? -1 : 0;
    }

int dtk6_CmdSet1int(char * argv[],const CMDDESCRIPTOR_T * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 1-argument selector by setting *cmd->resultptr
	 *	to the int conversion of next token.
	 *	Return the number of items removed from 'argv' = 1,
	 *	or -1 if out-of-range
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 *	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 */
    {
    long lResult = atol(argv[1]);
    char * pNext;
//    double dStart = strtod(cmd->czValidateSelector,&pNext);
    BOOL bNoStart = (*cmd->czValidateSelector == ':');
    long lStart = strtol(cmd->czValidateSelector,&pNext,10);
    BOOL bNoEnd = *(++pNext) == '\0';
    long lEnd = strtol(pNext,&pNext,10);
    *(int *)cmd->resultptr = (int)lResult;
    return ((!bNoStart && (lResult < lStart))
	    || (!bNoEnd && (lResult > lEnd))) ? -1 : 1;
    }


int dtk6_CmdSet1double(char * argv[],const CMDDESCRIPTOR_T * cmd)
	/*	fn suitable to be included in CMDDESCRIPTOR table
	 *	handles 1-argument selector by setting *cmd->resultptr
	 *	to the float conversion of next token.
	 *	Return the number of items removed from 'argv' = 1,
	 *	or -1 if out-of-range
	 *	czValidateSelector may be:
	 *	  a closed range in the form x:y or x: or :y
	 *	  (in future) a list in the form x,y...,z
	 *	  all numeric strings are decimal and may have [+|-]
	 *	dtk_ProcessCommandLine has guaranteed that a token is avail.
	 */
    {
    char tempBuf[32];
    memset(tempBuf,0,32);
    strncpy(tempBuf,argv[1],strlen(argv[1]));
    char* pChar = tempBuf;
    while (*pChar++ != '\0')
        if (*pChar == ',')
            *pChar = '.';
    double dResult = atof(tempBuf);
    char * pNext;
    BOOL bNoStart = (*cmd->czValidateSelector == ':');
    double dStart = strtod(cmd->czValidateSelector,&pNext);
    BOOL bNoEnd = *(++pNext) == '\0';
    double dEnd = strtod(pNext,NULL);
    *(double *)cmd->resultptr = dResult;
#ifdef DEBG
//  printf("Set1Double results: dResult=%f start,end flags=%d,%d vals=%f,%f\n",
  //      dResult,bNoStart,bNoEnd,dStart,dEnd);
#endif
    return ((!bNoStart && (dResult < dStart))
	    || (!bNoEnd && (dResult > dEnd))) ? -1 : 1;
    }

int dtk6_CmdSet1string(char * argv[],const CMDDESCRIPTOR_T * cmd)
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
    {
    uint maxlen = atoi(cmd->czValidateSelector);
    if ((maxlen > 0) && (strlen(argv[1]) > maxlen))
       return -1;
    strcpy(cmd->resultptr,argv[1]);
    return 1;
    }

#ifndef __GCC__ /* really should use glob() */
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
#endif

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
      //#ifndef __GCC__ // ~~ bypass for the moment
    const char ** msgptr = msgs;
    while ((msgptr != NULL) && (strlen(*msgptr)>1))
	dtk_ShowMsg(0,*msgptr++);
    //#endif
    }

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

void TOOL_CMD_END() { puts(FIL_ID); }
