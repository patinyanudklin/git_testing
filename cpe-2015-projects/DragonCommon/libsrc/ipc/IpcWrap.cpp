extern "C" {
#include "drelease.h"
char IPC_WRAP_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.81 $$Date: 2015/01/21 10:47:25 $";
D_REL_IDSTR;
}
/*
 *	filename IpcWrap.cpp
 *      ~~ Copyright 2001-2015 Kurt Rudahl and Sally Goldin
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
 * $Id: IpcWrap.cpp,v 1.81 2015/01/21 10:47:25 rudahl Exp $
 * $Log: IpcWrap.cpp,v $
 * Revision 1.81  2015/01/21 10:47:25  rudahl
 * tracing and cleanup
 *
 * Revision 1.80  2015/01/02 03:16:27  rudahl
 * fix Dragon/OpenDragon conditional
 *
 * Revision 1.79  2014/12/29 03:30:57  rudahl
 * convert to using dragon version number
 *
 * Revision 1.78  2014/12/07 08:25:47  rudahl
 * adapt to OpenDragon
 *
 * Revision 1.77  2014/01/27 12:20:52  rudahl
 * fixing vsnprintf for mingw
 *
 * Revision 1.76  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.75  2012/05/02 11:40:27  rudahl
 * implemented WEBSGL enforcement
 *
 * Revision 1.74  2008/10/05 03:13:40  rudahl
 * added documentation
 *
 * Revision 1.73  2008/09/27 11:43:33  rudahl
 * added waitReady
 *
 * Revision 1.72  2008/07/14 07:29:41  rudahl
 * Module: ~~DISP etc messages on console now only if tracing enabled
 *
 * Revision 1.71  2008/02/17 11:47:31  goldin
 * Try to fix stack corruption
 *
 * Revision 1.70  2008/02/01 09:03:49  goldin
 * make msg more informative
 *
 * Revision 1.69  2007/11/21 10:33:31  rudahl
 * TEMP on-screen print of ~~Commands
 *
 * Revision 1.68  2007/09/09 11:45:39  goldin
 * Move getWorkingImagePath to the server
 *
 * Revision 1.67  2006/02/11 09:33:13  rudahl
 * improved tracing
 *
 * Revision 1.66  2006/01/08 09:31:20  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.65  2005/12/24 04:37:56  rudahl
 * suppress send msg to SS from SS
 *
 * Revision 1.64  2005/12/04 10:58:30  goldin
 * Mingw does not have glob.h
 *
 * Revision 1.63  2005/11/29 13:29:39  rudahl
 * some ifdefs needed for 5.8 viewport
 *
 * Revision 1.62  2005/11/19 08:42:07  rudahl
 * revised LangFileName, etc location
 *
 * Revision 1.61  2005/10/03 12:31:56  goldin
 * delete Nak file after found in sendCommand
 *
 * Revision 1.60  2005/10/03 10:54:52  goldin
 * Change sendCommand to return -5 if it sees 
 * a NakDS file instead of a CmdSS file
 *
 * Revision 1.59  2005/10/02 08:13:37  rudahl
 * working on persistent data
 *
 * Revision 1.58  2005/10/01 11:08:26  rudahl
 * adding persistent storage to Ipc and SS
 *
 * Revision 1.57  2005/09/25 12:11:41  rudahl
 * working on persistent data
 *
 * Revision 1.56  2005/09/25 04:48:18  rudahl
 * changed sendCommand arg to take actual module number
 *
 * Revision 1.55  2005/09/12 07:32:50  rudahl
 * fixes re dp.h
 *
 * Revision 1.54  2005/08/12 09:22:23  goldin
 * Fix problem in trace statement - bad string arg causing a crash
 *
 * Revision 1.53  2005/04/25 10:49:41  rudahl
 * improved tracing
 *
 * Revision 1.52  2005/04/24 10:53:12  goldin
 * Add more tracing
 *
 * Revision 1.51  2005/04/01 03:30:19  rudahl
 * working on grstop Server modules
 *
 * Revision 1.50  2005/03/30 10:56:00  rudahl
 * small adaptations for MFC60/viewport
 *
 * Revision 1.49  2005/03/19 06:34:45  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.51  2005/03/13 02:42:18  rudahl
 * lint and debug
 *
 * Revision 1.50  2005/03/11 21:40:57  rudahl
 * fixed getWorkingImage stuff
 *
 * Revision 1.49  2005/03/11 21:37:53  rudahl
 * added getWorkingImage stuff
 *
 * Revision 1.48  2005/02/18 21:58:58  rudahl
 * moved logtrace etc to logger.cpp
 *
 * Revision 1.47  2005/02/16 04:14:00  rudahl
 * adapt to GCC/MINGW differences
 *
 * Revision 1.46  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.45  2005/02/15 18:30:36  rudahl
 * moved out product fns
 *
 * Revision 1.44  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.43  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.42  2004/12/23 12:05:23  rudahl
 * replace assignment by strcpy, per lint
 *
 * Revision 1.41  2004/12/20 02:48:02  rudahl
 * conditionalized FLOAT_PRODUCT code
 *
 * Revision 1.40  2004/12/11 08:10:30  rudahl
 * added FLOAT_PRODUCT
 *
 * Revision 1.39  2004/12/04 05:59:35  rudahl
 * added some logging
 *
 * Revision 1.38  2002/09/15 21:37:37  rudahl
 * added SetProductLevel
 *
 * Revision 1.37  2002/09/09 17:22:46  rudahl
 * removed old ZTC debugging stmt
 *
 * Revision 1.36  2002/09/05 00:45:16  rudahl
 * moved GetProductLevel to IPC
 *
 * Revision 1.35  2002/07/01 14:30:50  rudahl
 * eliminated call to send blob
 *
 * Revision 1.34  2002/06/17 16:26:21  goldin
 * Fix sendProgress to put correct (sender) module in filename
 *
 * Revision 1.33  2002/01/10 22:25:45  rudahl
 * added support for small-mode ZOR version
 *
 * Revision 1.32  2001/11/30 19:19:16  rudahl
 * moved whichKnownCommand; added executeKnown
 *
 * Revision 1.31  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.30  2001/10/18 13:46:17  rudahl
 * missing include for Zor
 *
 * Revision 1.29  2001/10/12 20:31:40  rudahl
 * provide for interrupt
 *
 * Revision 1.28  2001/10/05 16:18:45  rudahl
 * added sendSimpleCommand for C
 *
 * Revision 1.27  2001/09/26 19:04:52  rudahl
 * minor changes and de-linting for GCC, including fine_first
 *
 * Revision 1.26  2001/09/26 16:59:55  rudahl
 * added find_first, file_size for GCC
 *
 * Revision 1.25  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.24  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.23  2001/08/22 20:49:57  rudahl
 * added CommFileName
 *
 * Revision 1.22  2001/08/22 20:02:56  rudahl
 * added CommFileName to wrapper
 *
 * Revision 1.21  2001/08/22 17:57:01  rudahl
 * fixup for GCC
 *
 * Revision 1.20  2001/08/22 17:55:22  rudahl
 * fixup for GCC
 *
 * Revision 1.19  2001/08/22 16:54:35  rudahl
 * added conditionals for GCC
 *
 * Revision 1.18  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.17  2001/08/14 17:43:19  goldin
 * debugging cmd/rpy logic to viewport
 *
 * Revision 1.16  2001/08/14 16:26:53  rudahl
 * added getModule
 *
 * Revision 1.15  2001/08/14 13:41:31  rudahl
 * added pczSequence
 *
 * Revision 1.14  2001/07/31 19:51:44  rudahl
 * fixed problem with rpyFiles
 *
 * Revision 1.13  2001/07/30 14:06:34  rudahl
 * added qUsingMenus to wrapper
 *
 * Revision 1.12  2001/07/26 15:08:53  rudahl
 * fixed viewport-to-server communication
 *
 * Revision 1.11  2001/07/13 20:08:11  rudahl
 * misspelled name in name-value pair
 *
 * Revision 1.10  2001/07/12 20:10:52  rudahl
 * changed reportError, added reportOperationError
 *
 * Revision 1.9  2001/07/10 11:36:41  rudahl
 * added reportError; changed logError
 *
 * Revision 1.8  2001/07/04 21:33:09  rudahl
 * fixed some bugs; added sbility to SendRpy alt. to UI or SS
 *
 * Revision 1.7  2001/06/28 21:10:26  rudahl
 * improvements in text messages and documentation
 *
 * Revision 1.6  2001/06/19 12:05:55  rudahl
 * fixed rpyfile
 *
 * Revision 1.5  2001/06/15 20:35:01  rudahl
 * finished impl. QryFile
 *
 * Revision 1.4  2001/06/06 12:08:01  rudahl
 * fixed sendProgress
 *
 * Revision 1.3  2001/06/02 18:25:04  rudahl
 * fixed up for progress file
 *
 * Revision 1.2  2001/05/30 17:28:47  rudahl
 * integrate server and viewport communication
 *
 * Revision 1.1  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 ******************************************************************
 * 
 *   C Wrapper for IPC fns
 *   makes available exactly those fns needed by CGATE & I.P> DLL's
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7 	2005-9-10 ktr	clean out some ifdefs impeding progress
 * 	2005-9-25 ktr	added support for persistent data
 * 	2006-1-8 ktr	put in bit-wise conditionals for logTrace
 * 6.0	2008-09-27 ktr	added waitReady, for GCP
 * 6.3	2012-12-28 ktr	added IpcStyle
 ********************************************************************
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
// this is included in viewport build
#if defined __GCC__ || defined __MINGCC__
#define _snprintf snprintf
#if defined __GCC__ 
#define _vsnprintf vsnprintf
#endif
#if !defined __MINGCC__
#include <glob.h>
#endif
#include <sys/stat.h>
#include <unistd.h>
//typedef struct { char * name; } _find_t;
#else
#include "io.h"
#define strcasecmp(a,b) stricmp(a,b)
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"

#include "files.h"
//#include "permbits.h"
#include "ob.h"
#include "dragonOb.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcCmdFile.h"
#include "IpcMsgFile.h"
#include "IpcProFile.h"
#include "IpcRpyFile.h"
#include "IpcWatcher.h"
#include "IpcSendWatcher.h"
#include "IpcReceiveWatcher.h"
#include "IpcRpyWatcher.h"
#include "IpcCmdWatcher.h"

#include "IpcWrap.h"

static IpcSendWatcher * cmdSendWatcher[MODULE_INVALID] 
    = { NULL, NULL, NULL, NULL, NULL,   NULL, NULL, NULL, NULL, NULL,   NULL };
static IpcSendWatcher * msgSendWatcher = NULL;
static IpcSendWatcher * proSendWatcher = NULL;
static IpcSendWatcher * qrySendWatcher = NULL;
static IpcSendWatcher * rpySendWatcher = NULL;

static IpcRpyWatcher * rpyReceiveWatcher = NULL;

/* initialize info for error and log processing
 * This should be called at the earlies possible moment
 * (before any log output, and before any possible errors)
 * if 'czLoggingPath' is NULL, don't set it
 * 'czTraceArg' can be modified later; the other args should not be
 */
void ipcLogInit(char * czLoggingPath,
		const char * czLoggingFile,
		const char * czTracingFile,
		const char * czModuleAbbr,
		char * czTraceArg)
    {
    DragonObject::getKpath(); /* this sets it from config, except in Win16 */
    if (czLoggingPath != NULL) 
        Logger::setPath(czLoggingPath);
    Logger::setErrorLogFile(czLoggingFile,FALSE); /* FALSE -> append */
    DragonObject::setThisModule(czModuleAbbr);
    Logger::setTraceFile(czTracingFile,FALSE);
    Logger::setTraceArg(czTraceArg);
    Logger::logTrace("IpcWrap::Starting");
    }

void setTraceLevel(ulong ulLevel)
    {
    Logger::setTraceLevel(ulLevel); // enable tracing
    }

/* this fn is structured to permit use by atexit() */
void ipcShutdown()
    {
    uint i;
    logTrace("IpcWrap::Shutting down");
    for (i=0; i<AY_COUNT(cmdSendWatcher); i++)
        {
	if (cmdSendWatcher[i] != NULL)
	    delete cmdSendWatcher[i];
	cmdSendWatcher[i] = NULL;
	}
    if (msgSendWatcher != NULL)
        delete msgSendWatcher;
    msgSendWatcher = NULL;
    if (proSendWatcher != NULL)
        delete proSendWatcher;
    proSendWatcher = NULL;
    if (qrySendWatcher != NULL)
        delete qrySendWatcher;
    qrySendWatcher = NULL;
    if (rpySendWatcher != NULL)
        delete rpySendWatcher;
    rpySendWatcher = NULL;
    if (rpyReceiveWatcher != NULL)
        delete rpyReceiveWatcher;
    rpyReceiveWatcher = NULL;
    }

/* output error information to a logging file using logError(), 
 * and also report the error to the user.
 * @param 'lCode'        error 'number' - see err-spec.txt for details
 * @param 'czKey'        key to the drag5-xx.messages file
 * @param 'czArg'        arg to substitute into retrieved string (if '%s')
 *                       or append to retrieved string. 
 *                       May be NULL or empty if not needed. 
 * @param 'czRemind'     Reminder string or "" or NULL.
 * @param 'czFormat'...  sprintf-style argument list
 */
void reportError(const long lCode,
		 const char * czKey,    /* I18N key; required */
		 const char * czArg,    /* replacement/append arg */
		 const char * czRemind, /* usually NULL */
		 const char * czFormat,...)
    {
    const char * pczRemind = ((czRemind == NULL) || (strlen(czRemind) == 0))
        ? czFormat : czRemind;
    const char * pczArg = (czArg == NULL) ? "" : czArg;
    int iCode = -(int)(abs(lCode) & 0xFFFF); /* want low word, signed */
    int iMsgCode = COMPLEX_ERR_MSG_TYPE | HISTORY_MSG_FORMAT;
                  /* first log the error */
    if (Logger::getTraceLevel() & TRACE_LVL_IPCMisc)
	logTrace("IpcWrap::reportError (en)"); //~~~
    va_list marker;
    va_start(marker,czFormat);
    Logger::logErrorV(lCode,czFormat,marker);
    va_end(marker);
                  /* now try to inform the user */
                  /* this sends msg with name=value pairs per ipc-spec.txt */
    char * czFormatStr 
		= "ErrorCode=%d\nMsgKey=%s\nMsgText=%s\nArgumentText=%s\n";
    size_t bufsize = strlen(czKey) + strlen(pczArg) + strlen(pczRemind)
                + strlen(czFormatStr) + 20;
    char * buf = (char *) calloc(bufsize,1);
    if (buf != NULL)
        {
	_snprintf(buf,bufsize-1,czFormatStr,iCode,czKey,pczRemind,pczArg);
	if (DragonObject::qUsingMenus())
	    sendMessage(iMsgCode,buf);
	else
	    sendMessage(iMsgCode,czKey);
	char * pBuf = buf;
	// tracing puts into DB, so need to deal with special chars
	// just convert them all to blanks - we lose nothing
	while ((pBuf = strchr(buf,'\'')) != NULL)
	    *pBuf = ' ';
	while ((pBuf = strchr(buf,'\"')) != NULL)
	    *pBuf = ' ';
	while ((pBuf = strchr(buf,'\n')) != NULL)
	    *pBuf = ' ';
	if (strcmp(DragonObject::getThisModule(),"SS") != 0)
	    putTracing(buf,"Error","ipc reportError");
	free(buf);
	}
#ifndef _MSC_VER
    else
        {
        printf("Error %d: %s %s\n",iCode,pczRemind,pczArg);
	if (strcmp(DragonObject::getThisModule(),"SS") != 0)
	    putTracing(pczRemind,"Error","IPC reportError");
	}
#endif
    if (Logger::getTraceLevel() & TRACE_LVL_IPCMisc)
	logTrace("IpcWrap::reportError (ex) module='%s'",DragonObject::getThisModule()); //~~~
    }

/* output error information to a logging file using logError(), 
 * and also report the error to the user.
 * This function, which uses reportError and logError, is 
 * specialized for reporting errors within operations whose names
 * are recognized by the user.
 * @param 'lCode'           error 'number' - see err-spec.txt for details
 * @param 'czMsgKey'        key to error msg in the drag5-xx.messages file
 * @param 'czMsgRemind'     Reminder string or "" or NULL.
 * @param 'czOpKey'         key to operation name in the drag5-xx.messages file
 * @param 'czOpCommand'     the cmd string as in a .spt; also acts as remind
 * @param 'czArgKey'        key to pspec label in menu, or NULL or ""
 * @param 'czArgText'       the pspec string as in a .spt, or other text arg
 *                            also acts as remind
 */
void reportOperationError(const long lCode,
			  const char * czMsgKey,
			  const char * czMsgRemind,
			  const char * czOpKey,
			  const char * czOpCommand,
			  const char * czArgKey,
			  const char * czArgText)
    {
      /* transform NULL args into empty strings */
    const char * pczMsgKey = (czMsgKey == NULL) ? "" : czMsgKey;
    const char * pczMsgRemind= (czMsgRemind == NULL) ? "" : czMsgRemind;
    const char * pczOpKey = (czOpKey == NULL) ? "" : czOpKey;
    const char * pczOpCommand = (czOpCommand == NULL) ? "" : czOpCommand;
    const char * pczArgKey = (czArgKey == NULL) ? "" : czArgKey;
    const char * pczArgText = (czArgText == NULL) ? "" : czArgText;
//    const char * pczAbbr = DragonObject::getThisModule();
    int iCode = -(int)(abs(lCode) & 0xFFFF); /* want low word, signed */
    int iMsgCode = COMPLEX_ERR_MSG_TYPE | HISTORY_MSG_FORMAT;
                  /* first log the error */
    logError(lCode,"%s error %s %s",pczOpCommand,pczMsgRemind,pczArgText);
                  /* now try to inform the user */
                  /* this sends msg with name=value pairs per ipc-spec.txt */
    char * czFormatStr 
		= "ErrorCode=%d\nMsgKey=%s\nMsgText=%s\n"
		  "OperationKey=%s\nOperationText=%s\n"
                  "ArgumentKey=%s\nArgumentText=%s\n";
    size_t bufsize = strlen(pczMsgKey) + strlen(pczMsgRemind) 
                  + strlen(pczOpKey) + strlen(pczOpCommand)
                  + strlen(pczArgKey) + strlen(pczArgText)
                  + strlen(czFormatStr) + 20;
    char * buf = (char *) calloc(bufsize,1);
    if (buf != NULL)
        {
	_snprintf(buf,bufsize-1,czFormatStr,iCode,pczMsgKey,pczMsgRemind,
		    pczOpKey,pczOpCommand,pczArgKey,pczArgText);
	if (DragonObject::qUsingMenus())
	    sendMessage(iMsgCode,buf);
	else
	    sendMessage(iMsgCode,pczMsgKey);
	char * pBuf = buf;
	// tracing puts into DB, so need to deal with special chars
	// just convert them all to blanks - we lose nothing
	while ((pBuf = strchr(buf,'\'')) != NULL)
	    *pBuf = ' ';
	while ((pBuf = strchr(buf,'\"')) != NULL)
	    *pBuf = ' ';
	while ((pBuf = strchr(buf,'\n')) != NULL)
	    *pBuf = ' ';
	if (strcmp(DragonObject::getThisModule(),"SS") != 0)
	    putTracing(buf,"Error","IPC reportError");
	free(buf);
	}
#ifndef _MSC_VER
    else
        {
        printf("Error %d: %s error %s %s",
	       iCode,pczOpCommand,pczMsgRemind,pczArgText);
	if (strcmp(DragonObject::getThisModule(),"SS") != 0)
	    putTracing(pczMsgRemind,"Error","IPC reportError");
	}
#endif
    }

int getTraceLevel()
    {
    return Logger::getTraceLevel();
    }

/* send a command to a module, using module number in dragonOb.h, 
 * and optionally wait for response
 * NOTE as of 2008-Oct-3 iWaitCondition==3 seems to return as soon as 
 *	reply file exists, not that write has finished. See waitReady().
 * @param uModuleNo       module #; 4 is first viewport
 *			  (NOTE in Dragon 5.4, first viewport was 1)
 * @param czCommand       Arbitrary command string
 *			  The first word of this can be matched against
 *			  commands defined in dragonOb.h, using 
 *			  whichKnownCommand; 
 *			  however as of v 5.6 the VP usually uses ~~CMD~~ form
 * @param iTimeout        if >0, # secs to wait for reply
 *                        if <0, wait forever
 *                        if == 0, don't wait
 * @param iWaitCondition  if itimeout != 0, specifies condition to wait on:
 *                         0      >= 3, or error (negative) from getSendState
 *                        1-4 have same meaning as getSendState:
 *                         1      accepted or error
 *                         2      progress PRO file seen or error
 *                         3      RPY seen or error
 *                         4      accepted and no further activity expected,
 *                                 or error
 *                        other vals can be defined
 * @param pczSequence     NULL, or ptr to char[4] where seq # is placed
 * @param uStyle      	  what type of IPC communication to use?
 *		              IPC_XML wraps the content in XML
 *		              IPC_URL and IPC_SOCKET yet to be defined
 * @return                result of IpcSendWatcher::getSendState()
 *                        or -5 if a CmdSSxxx.$$$ is detected with iTimeOut < 0
 */
#if DRAGON_VER >= 6
int sendCommand(const uint uModuleNo,const char * czCommand, 
		const int iTimeOut, const int iWaitCondition,
		char * pczSequence,IPC_STYLE_t uStyle)
#else
int sendCommand(const uint uModuleNo,const char * czCommand, 
		const int iTimeOut, const int iWaitCondition,
		char * pczSequence)
#endif
    {
    int iCountdown = iTimeOut;
    int iRetval = 0;
    struct _find_t * pSurprise = NULL;
//    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
        {
#if DRAGON_VER >= 6
	logTrace("IpcWrap::sendCommand (en) to %s style=%s iTimeOut=%d iWaitCon=%d cmd=|%s|",
	         DragonObject::getModuleAbbrev(uModuleNo),
	         IpcFile::getIpcStyleName(uStyle),
	         iTimeOut,iWaitCondition,czCommand);
#else
	logTrace("IpcWrap::sendCommand (en) to %s iTimeOut=%d iWaitCon=%d cmd=|%s|",
	         DragonObject::getModuleAbbrev(uModuleNo),
	         iTimeOut,iWaitCondition,czCommand);
#endif
	}
    if (cmdSendWatcher[uModuleNo] == NULL)
	cmdSendWatcher[uModuleNo] 
#if DRAGON_VER >= 6
	    = new IpcSendWatcher(DragonObject::getModuleAbbrev(uModuleNo),
				CMD_FILE_TYPE,uStyle);
#else
	    = new IpcSendWatcher(DragonObject::getModuleAbbrev(uModuleNo),
				CMD_FILE_TYPE);
#endif
    if (cmdSendWatcher[uModuleNo] != NULL)
        {
        cmdSendWatcher[uModuleNo]->send(czCommand,"");
	if (pczSequence != NULL)
	    {
	    pczSequence[3] = '\0';
	    strncpy(pczSequence,
		    cmdSendWatcher[uModuleNo]->getFileSequence(),4);
	    }
	iRetval = cmdSendWatcher[uModuleNo]->getSendState();
	if (iWaitCondition == 4)
	    cmdSendWatcher[uModuleNo]->setNoWait();
	if (iTimeOut == 0)
	    cmdSendWatcher[uModuleNo]->setNoWait();
	else
	    {
	    while (iCountdown != 0)
	        {
		pSurprise = find_first(Logger::CommFileName("NakDS*.$$$"),0);
                if (pSurprise != NULL)
		    {
		    iRetval = -5;
		    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
			logTrace("About to try and remove %s",
				 CommFileName(pSurprise->name));
		    remove(CommFileName(pSurprise->name));
                    // The file exists only as a signal
		    // No one else will consume it
		    }
		if (iRetval == 3)
		    {
		    char fn[PATH_MAX];
		    sprintf(fn,Logger::CommFileName("Rpy%s*.$$$"),
			    DragonObject::getThisModule());
#ifndef __GCC__
		    pSurprise = find_first(fn,0);
#endif
		    }
		if ((iWaitCondition == 0) && ((iRetval >= 3) || (iRetval < 0)))
	            break;
		if ((iWaitCondition == 1) && ((iRetval == 1) || (iRetval < 0)))
	            break;
		if ((iWaitCondition == 2) && ((iRetval == 2) || (iRetval < 0)))
	            break;
		if ((iWaitCondition == 3) && ((iRetval == 3) || (iRetval < 0)))
	            break;
		if ((iWaitCondition == 4) && ((iRetval == 4) || (iRetval < 0)))
	            break;
		iRetval = cmdSendWatcher[uModuleNo]->getSendState();
		if (iCountdown > 0)
	            iCountdown--;
		}
	    }
	cmdSendWatcher[uModuleNo]->cleanup();
	}
//    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	logTrace("IpcWrap::sendCommand (ex) "
		 "return %d countdown=%d surprise=%s",
		 iRetval,iCountdown,
		 (pSurprise != NULL) ? pSurprise->name : "NONE");
    return iRetval;
    }

/* send command to UI (the default) or SS (if bSS)
 * @param czCmd  command to send
 * @param bSS    if true send to SS else to UI
 */
void sendSimpleCommand(const char * czCmd,const BOOL bSS)
    {
    IpcSendWatcher * pWatcher = NULL;
    if (bSS)
	pWatcher = new IpcSendWatcher("SS",CMD_FILE_TYPE,IPC_CLASSIC); // ~~~
    else
	pWatcher = new IpcSendWatcher("UI",CMD_FILE_TYPE,IPC_CLASSIC); // ~~~
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	Logger::logTrace("::sendSimpleCommand cmd=%s dest=%s",
		     czCmd,(bSS) ? "SS" : "UI");
    if (pWatcher != NULL)
        {
        pWatcher->send(czCmd,NULL);
	pWatcher->setNoWait();
	pWatcher->cleanup();
	delete pWatcher;
	}
    }

void sendMessage(const int iCode, const char * czMessage)
    {
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	logTrace("IpcWrap::sendMessage (en)");
    if (DragonObject::qUsingMenus())
        {
	if (msgSendWatcher == NULL)
	    {
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
		logTrace("::about to create new IpcSendWatcher");
	    msgSendWatcher = new IpcSendWatcher("UI",MSG_FILE_TYPE,IPC_CLASSIC); // ~~~
	    }
	if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	    logTrace("::sendMessage watcher=%p msgType=x%X message=%s",
		     msgSendWatcher, iCode, czMessage);
	if (msgSendWatcher != NULL)
	    {
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	        logTrace("::about to send message");
	    msgSendWatcher->send(iCode,czMessage,"");
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
		logTrace("::message sent");
	    msgSendWatcher->cleanup();
	    }
	}
    else
        puts(czMessage);
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	logTrace("IpcWrap::sendMessage (ex)");
    }

/* generate and send a query
 * Always received by UI
 * @param  uArgTotalSize  est. amount of buffer space needed for the args
 *                         (not counting the format string)
 * @param  czFormat       sprintf-style format string listing name=%s (%d)
 *                        pairs, each \n-terminated.
 * @return                0 => OK
 *                        -1 => some sort of error
 */
int sendModalQuery(const size_t uArgTotalSize,
		   const char * czFormat,...)
    {
    int iRetval = -1;
    const char * czSequence = NULL;
    if (rpyReceiveWatcher == NULL)
	delete rpyReceiveWatcher;
    rpyReceiveWatcher = NULL;
    if (qrySendWatcher == NULL)
        qrySendWatcher = new IpcSendWatcher("UI",QRY_FILE_TYPE,IPC_CLASSIC); // ~~~
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	Logger::logTrace("::sendModalQuery watcher=%p formatstr=%s",
		     qrySendWatcher, czFormat);
    if (qrySendWatcher != NULL)
        {
	size_t bufsize = uArgTotalSize + strlen(czFormat);
	char * pczMsgbuf = (char *)malloc(bufsize);
	if (pczMsgbuf != NULL)
	    {
	    va_list marker;
	    va_start(marker,czFormat);
	    _vsnprintf(pczMsgbuf,bufsize,czFormat,marker);
	    va_end(marker);
	    qrySendWatcher->send(pczMsgbuf,"");
	    czSequence = qrySendWatcher->getFileSequence();
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
		Logger::logTrace("::sendModalQuery sequence=%s message=%s",
		     czSequence,pczMsgbuf);
	    qrySendWatcher->cleanup();
	    free (pczMsgbuf);
	    }
	else
	    iRetval = -2;
	}
    if (czSequence != NULL) 
        {
	rpyReceiveWatcher = new IpcRpyWatcher(czSequence,IPC_CLASSIC); // ~~~
	iRetval = 0;
	}
    return iRetval;
    }

/* check whether current query has been received, if so, get values
 * @param    uAttrCount  number of attributes requested
 * @param    pAttributes array of structures specifying which
 *                       attributes are desired, and which gets filled-in
 *                       by this fn.
 * @return   >0 => yes; value is number of attributes in Rpy
 *           0 => no
 *           -1 => there is no current query
 */
int queryReceive(size_t uAttrCount,ATTRIBUTE_t * pAttributes)
    {
#undef FN_NAME
#define FN_NAME "IpcWrap::queryReceive"
    int retval = -1;
    int iRpyStatus = (rpyReceiveWatcher == NULL) 
                         ? -1 : rpyReceiveWatcher->getRpyStatus();
    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
        logTrace(FN_NAME " (en) watcher=%p status=%d",
		 rpyReceiveWatcher,iRpyStatus);
    if (rpyReceiveWatcher != NULL)
        {
	if (iRpyStatus == 0)
	    retval = 0;
	else
	    {
	    IpcRpyFile * pFile = (IpcRpyFile *) rpyReceiveWatcher->getFile();
//	    logTrace(FN_NAME " fileptr=%p want %d attributes",
//	            pFile,uAttrCount);
	    if (pFile != NULL)
	        {
		retval = pFile->getAttributeCount();
//		logTrace(FN_NAME " found %d attributes in file",retval);
		for (size_t i=0; i<uAttrCount; i++)
		    {
		    char * pVal 
		      = pFile->getAttributeValue(pAttributes[i].czName);
		    memset(pAttributes[i].pczValueBuf,0,
			   pAttributes[i].uValueBufSize);
		    if (pVal != NULL) 
		        {
			strncpy(pAttributes[i].pczValueBuf,pVal,
				pAttributes[i].uValueBufSize);
			if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
			    logTrace(FN_NAME " got val='%s'",pVal);
			free(pVal);
		        }
		    }
		}
	    }
	if (retval > 0)
	    rpyReceiveWatcher->cleanup();
        }
    //  if (Logger::getTraceLevel() > 1)
    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
        logTrace(FN_NAME " (ex) returns %d",retval);
    return retval;
    }

	/* Send something to be put into the TRACING db.
	 * @param pczWhat	text of message
	 * @param pczWho	brief indication e.g. Exec, Error
	 * @param pczWhy	reason for tracing
	 */
void putTracing(const char * pczWhat,const char * pczWho,
		const char * pczWhy)
    {
    char czReport[PATH_MAX+50];
    _snprintf(czReport,sizeof(czReport),"-SETPERSIST TRACING\t%s\t\%s\t\"%s\"",
		pczWho,pczWhy,pczWhat);
#if DRAGON_VER >= 6
    if (strcmp(DragonObject::getThisModule(),"SS") != 0)
	sendCommand(MODULE_SCRIPTSERVER,czReport,0,0,NULL,IPC_CLASSIC); // ~~~
#else
    if (strcmp(DragonObject::getThisModule(),"SS") != 0)
	sendCommand(MODULE_SCRIPTSERVER,czReport,0,0,NULL);
#endif
    }

static IpcCmdWatcher * m_pCmdWatcher = NULL;

	 /* is anything happening?
	  * 2005-9-25 appears used only for showprogress
	  * <0 processing error
	  * 0 OK, nothing to do
	  * >0 something needs attention
	  *  1 ??
	  *  2 - 9 match IpcCmdWatcher::getCmdStatus()
	  * @param pczBuf   buffer to copy any command into
	  * @param uBufSize size of buffer
	  */
int qCommandReceive(char * pczBuf,const size_t uBufSize)
    {
    int retval = 0;
    if (m_pCmdWatcher == NULL)
        m_pCmdWatcher = new IpcCmdWatcher((const char *)NULL,IPC_CLASSIC); // ~~~
    if (m_pCmdWatcher != NULL)
        {
	int iStatus = m_pCmdWatcher->getCmdStatus();
	if(iStatus == IPC_CMD_READY)
	    {
	    const char * cmd = m_pCmdWatcher->getCommand();
	    const char * filename = m_pCmdWatcher->getFilename();
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
		Logger::logTrace("IpcWrap::commandReceive received %s cmd=%s",
				 filename,cmd);
	    if (cmd != NULL)
	        {
		memset(pczBuf,0,uBufSize);
		strncpy(pczBuf,cmd,uBufSize-1);
		strtok(pczBuf,"\r\n");
		}
	    }
	retval = iStatus;
	m_pCmdWatcher->cleanup();
        }
    else
        retval = -2;
    return retval;
    }

/* maintain a progress file
 * If czMessage non-NULL, this is a new file
 * If bRemove, delete the existing file
 */
void sendProgress(const char * czMessage,
		  const ushort uPercent, const BOOL bRemove)
    {
    static long lTare = 0; /* length of an existing file with 0 % */
    if (proSendWatcher == NULL)
        proSendWatcher = new IpcSendWatcher(getThisModule(),PRO_FILE_TYPE,IPC_CLASSIC); // ~~~
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	Logger::logTrace("::sendProgress "
			 "watcher=%p message=%s pct=%d remove=%d",
			 proSendWatcher,
			 (czMessage != NULL) ? czMessage : "(NULL)",
			 uPercent,bRemove);
    if (proSendWatcher != NULL) //~~ not complete yet
        {
	if (bRemove)
	    {
	    proSendWatcher->cleanup();
	    lTare = 0;
	    }
	else if (czMessage != NULL)
	    {
	    proSendWatcher->send(czMessage,"");
	    lTare = proSendWatcher->reSend(0,0);
	    //	    lTare = proSendWatcher->reSend(10,lTare); //~~ just a test
	    }
	else if (lTare > 0) // else we've hit an error; don't repeat
	    proSendWatcher->reSend(uPercent,lTare);
	}
    }

/* send reply to UI (the default) or SS (if bSS)
 */
void sendReply(const char * czSequence, const char * czMessage,
	       const BOOL bSS)
    {
    IpcSendWatcher * pWatcher = NULL;
    if (bSS)
	pWatcher = new IpcSendWatcher("SS",RPY_FILE_TYPE,IPC_CLASSIC); // ~~~
    else
        {
        if (rpySendWatcher == NULL)
            rpySendWatcher = new IpcSendWatcher("UI",RPY_FILE_TYPE,IPC_CLASSIC); // ~~~
	pWatcher = rpySendWatcher;
	}
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	Logger::logTrace("::sendReply watcher=%p message=%s dest=%s%s",
			 rpySendWatcher, czMessage,(bSS) ? "SS" : "UI", 
			 (czSequence != NULL) ? czSequence : "*");
    if (pWatcher != NULL)
        {
        pWatcher->send(czMessage,czSequence);
	pWatcher->cleanup();
	}
    if (bSS)
	delete pWatcher;
    }

void sendReplyBlob(const char * czSequence, const char * czMessage,
		   const byte * pBlob, const size_t uBlobSize)
    {
    if (rpySendWatcher == NULL)
        rpySendWatcher = new IpcSendWatcher("UI",RPY_FILE_TYPE,IPC_CLASSIC); //~~~
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	Logger::logTrace("::sendReply watcher=%p seq='%s' "
			 "blobsize=%d message=%s",
			 rpySendWatcher, 
			 (czSequence == NULL) ? "" : czSequence,
			 uBlobSize, czMessage);
    if (rpySendWatcher != NULL)
        {
        rpySendWatcher->send(czMessage,czSequence);
	//        rpySendWatcher->send(czMessage,czSequnece,pBlob,uBlobSize);
	rpySendWatcher->cleanup();
	}
    }

/* Scan the list of required and return the index
 * of the one found, or -1.
 * @param  czCommandList        list of commands to recognize
 *                              if NULL, use required commands
 * @param  uCommandListSize     count of list
 * @param  cmd                  string containing command
 * @param  bExecuteIfPossible   try to execute the command
 * @return                      -1 if command not found
 *                              -2 if found and executed
 *				else command index
 */
int whichKnownCommand(const char ** czCommandList,
		      const size_t uCommandListSize,
		      char * cmd, BOOL bExecuteIfPossible)
    {
    int iRetval = IpcCmdWatcher::whichKnownCommand(czCommandList,
						   uCommandListSize,
						   cmd);
    if (bExecuteIfPossible && IpcCmdWatcher::executeKnownCommand(iRetval))
        iRetval = -2;
    return iRetval;
    }

/* get current time & return static string of form: ddd/hh:mm:ss (ee)
 * where ddd is the weekday abbreviation, hh:mm:ss is the usual and
 * (ee) is elapsed secs since program start
 * If bOldTime, just return the existing string
 */
char * nowTimeStr(BOOL bOldTime)
    {
    return Logger::nowTimeStr(bOldTime);
    }

/* @return true (1) if menu system is in use,
 *         false    if command-line
 * NOTE: this uses what's in the CFG file to discover this info,
 *       not what processes are actually running.
 */            
int qUsingMenus()
    {
    return DragonObject::qUsingMenus();
    }

/* delete any IPC files which match pattern
 * @param czPattern OS-dependent wildcard pattern
 *                  node-name only - no path or extension
 */
void IpcFileCleanup(const char * czPattern)
    {
    IpcFile::clean(czPattern);
    }

const char * getThisModule()
    { return DragonObject::getThisModule(); }

	/*	create full path name consisting of the communications
	 *	(kpath) directory + name
	 *	Return pointer to static string
	 */
const char * CommFileName(const char * name)
    {
//    printf("IpcWrap::CommFileName (en) of '%s'\n",name);
    return Logger::CommFileName(name);
    }

const char * HomeFileName(const char * name)
    {
    return Logger::HomeFileName(name);
    }

const char * LangFileName(const char * name)
    {
    return Logger::LangFileName(name);
    }

const char * getLanguageAbbr() // access logger::s_czLanguage
    { return Logger::czLanguage; }

	/* static function which uses much of parseHeader() to get
	 * the intended size and compare it to the actual size on the disk
	 * Once called this will block, so the caller should be sure
	 * that the desired file already exists
	 * @param fullFileName	path and name of desired file
	 */
#if DRAGON_VER >= 6
void waitReady(const char * fullFileName) 
    { IpcFile::waitReady(fullFileName); }
#endif

#if defined MOVEDTOSERVER || DRAGON_VER <= 5
const char * getWorkingImagePath() 
    { 
    const char * pWIF;
//    printf("Logger::getWorkingImagePath (en)\n");
    pWIF = Image::getWorkingImageFile();
//    printf("Logger::getWorkingImagePath of '%s'\n",pWIF);
    return CommFileName(pWIF); 
    }

BOOL isWorkingImageFile(const char * pczPath) 
    { 
    const char * pczWif = Image::getWorkingImageFile();
    return (strlen(pczPath) >= strlen(pczWif))
          ? (strcasecmp(&pczPath[strlen(pczPath)-strlen(pczWif)],pczWif) == 0)
	  : FALSE;
    }
#endif // #if defined MOVEDTOSERVER || DRAGON_VER <= 5

void IPCWRAP_END() { puts(FIL_ID); }
