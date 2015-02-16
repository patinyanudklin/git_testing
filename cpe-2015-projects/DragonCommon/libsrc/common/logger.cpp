extern "C" {
#include "drelease.h"
char LOGGER_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.45 $$Date: 2014/04/01 07:22:21 $";
D_REL_IDSTR;
}
/* Logger fns 
 *
 *	filename logger.cpp
 *		$Revision: 1.45 $ $Date: 2014/04/01 07:22:21 $	
 *	~~ copyright 2001-2014 Kurt Rudahl and Sally Goldin
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
 ********************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * history
 * 5.4	5/2001  ktr	created
 * 	11/30/2004 ktr	changed unlink() to remove() for Mingw
 *	12/11/2004 ktr	fixed FMSIZE
 * 5.5	2005-1-29 ktr	adapt for Dragon v 5.5
 * 5.7	2005-11-19 ktr	move LangFileName here from common_ipc
 *	2006-1-7 ktr	made logTrace give time in 1 msec resolution
 * 5.9	2006-12-10 ktr	incr language abbr to 5 chars
 ********************************************************************
 * $Id: logger.cpp,v 1.45 2014/04/01 07:22:21 rudahl Exp $
 * $Log: logger.cpp,v $
 * Revision 1.45  2014/04/01 07:22:21  rudahl
 * lint esp from old mingc
 *
 * Revision 1.44  2014/01/27 12:20:52  rudahl
 * fixing vsnprintf for mingw
 *
 * Revision 1.43  2014/01/25 05:49:32  rudahl
 * work with vsnprintf problem
 *
 * Revision 1.42  2012/04/15 04:52:47  rudahl
 * permit logging during setup
 *
 * Revision 1.41  2008/10/18 08:18:00  rudahl
 * bypass bug in mingw
 *
 * Revision 1.40  2008/07/14 12:04:49  rudahl
 * suppress tracing when not wanted
 *
 * Revision 1.39  2006/12/10 11:57:02  rudahl
 * fixed problem with 5-char language abbr
 *
 * Revision 1.38  2006/08/14 07:20:17  goldin
 * Debugging new vector framework
 *
 * Revision 1.37  2006/02/12 08:14:47  rudahl
 * lintish
 *
 * Revision 1.36  2006/02/08 02:30:44  rudahl
 * improved time in tracing
 *
 * Revision 1.35  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.34  2006/01/08 10:00:28  rudahl
 * logTrace now does 1msec logging
 *
 * Revision 1.33  2005/11/29 13:29:39  rudahl
 * some ifdefs needed for 5.8 viewport
 *
 * Revision 1.32  2005/11/19 08:42:07  rudahl
 * revised LangFileName, etc location
 *
 * Revision 1.31  2005/04/25 13:32:35  rudahl
 * finished an unfinished fix
 *
 * Revision 1.30  2005/04/25 10:52:01  rudahl
 * added test for bad logging file open
 *
 * Revision 1.29  2005/03/27 10:40:45  goldin
 * Get rid of printf
 *
 * Revision 1.28  2005/03/19 06:31:51  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.28  2005/03/13 02:40:59  rudahl
 * fix probs found working with enhance
 *
 * Revision 1.27  2005/02/12 02:19:46  rudahl
 * added Class, dump()
 *
 * Revision 1.26  2005/02/10 03:51:27  rudahl
 * cleaned up tracing and error handling
 * cleaned up image file writing
 *
 * Revision 1.25  2005/01/30 03:45:21  rudahl
 * using C fns for logTrace
 *
 * Revision 1.24  2005/01/29 11:52:30  rudahl
 * adapt for v 5.5
 *
 * Revision 1.23  2004/12/11 10:12:35  rudahl
 * fixup of FMSIZE
 *
 * Revision 1.22  2004/11/30 04:31:44  rudahl
 * adapt for Mingw
 *
 * Revision 1.21  2002/06/12 23:51:51  rudahl
 * surround some log strings by quotes
 *
 * Revision 1.20  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.19  2001/08/28 20:06:47  rudahl
 * some improved logging
 *
 * Revision 1.18  2001/08/22 19:07:26  rudahl
 * fixup for gcc
 *
 * Revision 1.17  2001/08/22 19:02:39  rudahl
 * fixup for gcc
 *
 * Revision 1.16  2001/08/04 14:10:26  rudahl
 * output both parts of error code
 *
 * Revision 1.15  2001/08/04 14:06:46  rudahl
 * output both parts of error code
 *
 * Revision 1.14  2001/07/31 19:51:44  rudahl
 * fixed problem with rpyFiles
 *
 * Revision 1.13  2001/07/13 20:07:35  rudahl
 * a bit of bulletproofing
 *
 * Revision 1.12  2001/07/10 11:37:25  rudahl
 * changed logError to use long errnum
 *
 * Revision 1.11  2001/07/03 19:57:41  rudahl
 * cleanup
 *
 * Revision 1.10  2001/06/28 21:10:26  rudahl
 * improvements in text messages and documentation
 *
 * Revision 1.9  2001/06/15 20:34:28  rudahl
 * got rid of malloc's
 *
 * Revision 1.8  2001/05/30 17:28:47  rudahl
 * integrate server and viewport communication
 *
 * Revision 1.7  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.6  2001/05/15 10:00:50  rudahl
 * adapted for Zortech build, which requires short filenames.
 * The build happens in a subdir named 'zor' and results in a
 * library in /lib/zor.
 *
 * Revision 1.5  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
 *
 * Revision 1.4  2001/05/08 20:26:29  rudahl
 * extensive revisions to support Viewport (16-bit), and to generally
 * advance the implementation stage.
 *
 * Revision 1.3  2001/05/04 08:44:41  rudahl
 * Adapted to dual MSoft 16-bit & 32-bit build
 * added fn to IpcCmdWatcher to process the default commands automatically
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:57  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
// need conditional for viewport build
#if defined __GCC__ || defined __MINGCC__
#define _snprintf snprintf
// /mingw/include/stdio.h has inline defn of vsnprinf() for some reason
#if defined __GCC__ 
#define _vsnprintf vsnprintf
#endif
#include <unistd.h>
#else
#define snprintf _snprintf
#include "io.h"
#define access(a,b) _access(a,b)
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"

#include "ob.h"
#include "dragonOb.h"
#include "logger.h"

Class Logger::s_class_Base("ImageHdr","Class for error and trace logging");

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB
Logger::Logger(int iDebug,int iTrace)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    }

/* get current time & return static string of form: ddd/hh:mm:ss (ee)
 * where ddd is the weekday abbreviation, hh:mm:ss is the usual and
 * (ee) is elapsed secs since program start
 * If bOldTime, just return the existing string
 */
char * Logger::nowTimeStr(BOOL bOldTime)
    {
    static char czNow[40] = "";
    //    static time_t ulStartTime = time(NULL);
    static clock_t ulStartCTime = clock();
    if (!bOldTime)
        {
	time_t now = getCorrectedTime();
	clock_t ulCNow = clock();
	//	time_t ulNow = time(NULL); /* don't use corrected time-this is a span*/
	ulong ulDiffMS = ((ulCNow-ulStartCTime) % CLOCKS_PER_SEC);
	ulong ulDiffSeconds = ((ulCNow-ulStartCTime) / CLOCKS_PER_SEC);
        if (CLOCKS_PER_SEC >= 1000000) //POSIX=1000000 Win=1000
	    ulDiffMS /= 1000;
	strftime(czNow,sizeof(czNow),"%a/%H:%M:%S",localtime(&now));
	sprintf(czNow+strlen(czNow)," (%ld.%03ld)", 
		ulDiffSeconds,ulDiffMS);
	//		ulNow-ulStartTime,ulDiff);
	}
    return czNow;
    }

void Logger::logError(const long lCode,const char * pczMessage, ...)
    {
    va_list marker;
    va_start(marker,pczMessage);
    logErrorV(lCode,pczMessage,marker);
    va_end(marker);
    }

	/* guts of Logger::logError and ::logError */
void Logger::logErrorV(const long lCode,const char * pczMessage, 
		       va_list marker)
    {
    char buf[1024];
    ulong ulCode = abs(lCode);
    static clock_t ulStartCTime = clock();
    clock_t ulCNow = clock();
    ulong ulDiff = ulCNow-ulStartCTime;
    if (CLOCKS_PER_SEC >= 1000000) //POSIX=1000000 Win=1000
	ulDiff /= 1000;
    snprintf(buf,sizeof(buf)-1,"%05ld %s -%ld (hi=%ld) '",
	      ulDiff,DragonObject::getThisModule(),
//	      time(NULL),DragonObject::getThisModule(),
              (ulCode&0xFFFF),(ulCode>>16));
    char * pFormattedMsg = buf+strlen(buf); // save ptr to next part
//#if defined __GCC__  // || defined __MINGCC__
//    vsnprintf(pFormattedMsg,
//	       sizeof(buf)-strlen(buf)-strlen(nowTimeStr(FALSE))-3,
//	       pczMessage,marker);
//#else // note that mingw MUST use _vsnprintf (not true of other '_'xxx fns)
      // see INLINE def'n in mingw stdio.h
    _vsnprintf(pFormattedMsg,
	       sizeof(buf)-strlen(buf)-strlen(nowTimeStr(FALSE))-3,
	       pczMessage,marker);
//#endif
    while(strchr(" \r\n",buf[strlen(buf)-1]) != NULL)
        buf[strlen(buf)-1] = '\0'; // get rid of trailing cr,lf,bl
    strcat_array(buf,"' ");
    strcat_array(buf,nowTimeStr(FALSE));
    if (czErrorLogFile != NULL)
        {
	strcat(buf,"\n");
	wsf(czErrorLogFile,buf,strlen(buf),WSF_APPEND);
	}
    else
        puts(buf);
    /* also put errors out to the trace file */
    if (s_ulTraceLevel > 0)
        {
	if (czTraceFile != NULL)
	    {
	    strtok(buf,"\r\n");
	    strcat_array(buf,"\n   (also logged to ");
	    strcat_array(buf,czErrorLogFile);
	    strcat_array(buf,")\n");
	    wsf(czTraceFile,buf,strlen(buf),WSF_APPEND);
	    }
	else
	    puts(buf);
	}
    /*
    char * fn = IpcMsgFile::createFilename("UI","");
    if (fn != NULL)
        {
	IpcMsgFile::sendFile(fn,pFormattedMsg,1);
	free(fn);
        }
	*/
    }

	/* logTrace supplies the required timestamp and module code */
void Logger::logTrace(const char * pczMessage,...)
    {
    if (s_ulTraceLevel > 0)
        {
	va_list marker;
	va_start(marker,pczMessage);
	logTraceV(pczMessage,marker);
	va_end(marker);
	}
    }

	/* guts of Logger::logTrace and ::logTrace */
void Logger::logTraceV(const char * pczMessage,va_list marker)
    {
//    time_t now = getCorrectedTime();
    FILE * fp = (czTraceFile != NULL) ? fopen(czTraceFile,"ab+") : stdout;
    static clock_t ulStartCTime = clock();
    clock_t ulCNow = clock();
    ulong ulDiff = ulCNow-ulStartCTime;
    if (CLOCKS_PER_SEC >= 1000000) //POSIX=1000000 Win=1000
	ulDiff /= 1000;
    if (fp == NULL)
        {
	perror("Logger::logTraceV");
	printf("Logger::logTraceV (en) fp=%p name=%p (%s) \n",
	       fp,czTraceFile,czTraceFile);
	return;
        }
    fprintf(fp,"%05ld %s ",
	    ulDiff,DragonObject::getThisModule());
//	    now,DragonObject::getThisModule());
    if (pczMessage != NULL)
	vfprintf(fp,pczMessage,marker);
    else
        fprintf(fp,"Logger::logTrace called with no message");
    fprintf(fp," %s\n",nowTimeStr(FALSE));
    if (czTraceFile != NULL)
        fclose(fp);
    }

#if ! defined ROSE_ONLY
/* czPath may be NULL, or is alloc'd */
void Logger::setPath(char * czPath)
    {
    if (czOutPath != NULL)
        free(czOutPath);
    czOutPath = czPath;
    }

/* pczErrorLogFile is NOT alloc'd, and must not be NULL 
 * @param  bZap - delete existing file
 */
void Logger::setErrorLogFile(const char* pczErrorLogFile, int bZap)
    {
    if (czErrorLogFile != NULL)
        free(czErrorLogFile);
    if ((czOutPath == NULL) || (strcmp(czOutPath,".") == 0))
        czErrorLogFile = strdup(pczErrorLogFile);
    else
        {
	czErrorLogFile 
	    = (char *)malloc(strlen(czOutPath)+strlen(pczErrorLogFile)+4);
	if (czErrorLogFile != NULL)
	    sprintf(czErrorLogFile,"%s/%s",czOutPath,pczErrorLogFile);
	}
    if (bZap != 0)
	remove(czErrorLogFile);
    }

/* pczTraceFile is NOT alloc'd, and must not be NULL
 * @param  bZap - delete existing file
 */
void Logger::setTraceFile(const char * pczTraceFile, int bZap)
    {
    if (czTraceFile != NULL)
        free(czTraceFile);
    if ((czOutPath == NULL) || (strcmp(czOutPath,".") == 0))
        czTraceFile = strdup(pczTraceFile);
    else
        {
	czTraceFile 
	    = (char *)malloc(strlen(czOutPath)+strlen(pczTraceFile)+2);
	if (czTraceFile != NULL)
	    sprintf(czTraceFile,"%s/%s",czOutPath,pczTraceFile);
	}
    if (bZap != 0)
        remove(czTraceFile);
    }

/* for the moment, setting this to non-NULL => a trace level of 1
 * pczTraceArg may be NULL, or is string
 * If the arg begins with 'file://', this sets the output name
 * (not the path and does not delete an existing fiel)
 */
void Logger::setTraceArg(const char * pczTraceArg)
    {
    s_ulTraceLevel = 0;
    if (pczTraceArg != NULL)
        {
	if (strncmp(pczTraceArg,"file://",7) == 0)
	    setTraceFile(pczTraceArg+7,FALSE);
	else
            {
	    if (czTraceArg != NULL)
		free(czTraceArg);
	    czTraceArg = strdup(pczTraceArg);
	    s_ulTraceLevel
	      = (strcmp(czTraceArg,
			DragonObject::getThisModule()) == 0) ? 2 : 1;
	    }
	}
    }

void Logger::setTraceLevel(ulong ulLevel,const char * pczComment)
    {
    BOOL bReported = FALSE;
    if (s_ulTraceLevel > 0)
        {
        logTrace("Logger::Changing traceLevel from %lX to %lX %s",
		 s_ulTraceLevel,ulLevel,pczComment);
	bReported = TRUE;
	}
    s_ulTraceLevel = ulLevel;
    if ((s_ulTraceLevel > 0) && !bReported)
        logTrace("Changing traceLevel from 0 to %lX",ulLevel);
    }

const char * Logger::getTraceFile()
    { return czTraceFile; }

char * Logger::getTraceArg() { return czTraceArg; }

void Logger::setTimeOffset(const long lOffset)
    { lTimeOffset = lOffset; }

long Logger::getTimeOffset() 
    {return lTimeOffset; }

#endif // #if ! defined ROSE_ONLY

time_t Logger::getCorrectedTime()
    {
    time_t ulRetval = time(NULL) - lTimeOffset;
    return ulRetval;
    }

ulong Logger::getTraceLevel()
    { return s_ulTraceLevel; }

const char * Logger::HomeFileName(const char * name)
	//	create full path name consisting of the home
	//	directory + name
	//	Return pointer to static string
    {
    static char filename[NAME_MAX];
    strcpy(filename,".");
    AFFIX_BS(filename);		// (/ or \\)
    strcat_array(filename,name);
    return filename;
    }

char * Logger::CommFileName(const char * name)
	//	create full path name consisting of the communications
	//	(kpath) directory + name
 	// 	Not declared as 'const' because of probs with 'spawn' args
	//	in CmdProcessor
	//	Return pointer to static string
    {
    static char filename[PATH_MAX];
//    printf("Logger::CommFileName (en) of '%s'\n",name);
    strcpy_array(filename,getKpath());	// has '\'
    AFFIX_BS(filename);		// (/ or \\)
    strcat_array(filename,name);
//  printf("Logger::CommFileName (ex) got '%s'\n",filename);
    return filename;
    }

char Logger::czLanguage[6]="";	// 2 or 5-letter abbrev. for language

const char * Logger::LangFileName(const char * name)
	//	create full path name consisting of the language subdir of
	//	the home directory + name
	//	Also sets czLanguage
	//	Return pointer to static string
    {
#ifdef ROSE_ONLY
    return "EN";
#else
    static char filename[PATH_MAX];
    BOOL bNew = FALSE;
    if (strlen(czLanguage)==0)
	{
	char czTmp[CONFIGSTRLEN+1];
	if (GetConfig("COUNTRY",czTmp,sizeof(czTmp)) <= 0) 
	    strcpy(czLanguage,"EN");
	else
	    { strcpy_array(czLanguage,czTmp); }
	bNew = TRUE;
	}
    strcpy_array(filename,HomeFileName(czLanguage));
    if (bNew)
	{	// if 5-letter extn doesn't work, go for 2-letter version
		// thus, we can handle dialects or parent groups
	char * endptr = filename + strlen(filename) - strlen(czLanguage);
	if (access(filename,F_OK) == -1)
	    {
	    *endptr = '\0';
	    czLanguage[2] = '\0';
	    strcat_array(filename,czLanguage);
	    }
	if (access(filename,F_OK) == -1)	// at worst, revert to english
	    {
	    *endptr = '\0';
	    strcpy(czLanguage,"EN");
	    strcat_array(filename,czLanguage);
//	    strcpy((endptr-2),"EN");
	    }
	}
    strcat_array(filename,FILE_SEP);
    strcat_array(filename,name);
    return filename;
#endif // #ifdef ROSE_ONLY
    }

const char * Logger::className() { return "Logger"; }

ulong Logger::s_ulTraceLevel = 0;
char * Logger::czTraceArg = NULL;
char * Logger::czTraceFile = NULL;
char * Logger::czErrorLogFile = NULL;
char * Logger::czOutPath = strdup(".");
long Logger::lTimeOffset = 0;

void logTrace(const char * czFormat,...)
    {
    if (Logger::getTraceLevel() > 0)
        {
	va_list marker;
	va_start(marker,czFormat);
	Logger::logTraceV(czFormat,marker);
	va_end(marker);
	}
    }

/* output error information to a logging file, 
 * or whatever Logger::logError() is set up to do
 * In any case, the output is purely intended for the developer
 * @param 'lCode'        error 'number' - see err-spec.txt for details
 * @param 'czFormat'...  sprintf-style argument list
 */
void logError(const long lCode,const char * czFormat,...)
    {
    va_list marker;
    va_start(marker,czFormat);
    Logger::logErrorV(lCode,czFormat,marker);
    va_end(marker);
    }

void LOGGER_END() { puts(FIL_ID); }		/* just a marker for the line file */
