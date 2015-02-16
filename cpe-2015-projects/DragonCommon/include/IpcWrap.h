/*
 *	filename IpcWrap.h
 *		$Revision: 1.45 $ $Date: 2015/01/02 03:16:27 $	
 *      ~~ Copyright 1988-2014 Kurt Rudahl and Sally Goldin
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
 *
 *	Requirements:
 *	   dragonOb.h
 ****************************************************************
 *
 * copyright 2001 goldin-rudahl associates
 * $Id: IpcWrap.h,v 1.45 2015/01/02 03:16:27 rudahl Exp $
 * $Log: IpcWrap.h,v $
 * Revision 1.45  2015/01/02 03:16:27  rudahl
 * fix Dragon/OpenDragon conditional
 *
 * Revision 1.44  2014/12/29 03:28:29  rudahl
 * convert to using dragon version number
 *
 * Revision 1.43  2014/12/18 09:08:41  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.42  2014/12/07 02:54:22  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.41  2014/12/06 11:31:02  rudahl
 * conditional changes for OpenDragon
 *
 * Revision 1.40  2014/12/05 11:51:02  rudahl
 * added ifdefs to match DragonProf and OpenDragon
 *
 * Revision 1.39  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.38  2008/09/27 11:43:50  rudahl
 * added waitReady
 *
 * Revision 1.37  2007/10/03 10:03:55  rudahl
 * cleanup
 *
 * Revision 1.36  2007/09/09 11:45:25  goldin
 * Move getWorkingImagePath to the server
 *
 * Revision 1.35  2006/11/30 08:41:40  goldin
 * Add new report generation functions 
 * for multi simple table category of report
 *
 * Revision 1.34  2006/02/11 09:32:50  rudahl
 * improved tracing
 *
 * Revision 1.33  2005/11/29 13:29:39  rudahl
 * some ifdefs needed for 5.8 viewport
 *
 * Revision 1.32  2005/11/19 08:41:35  rudahl
 * revised LangFileName, etc location
 *
 * Revision 1.31  2005/10/02 08:13:01  rudahl
 * working on persistent data
 *
 * Revision 1.30  2005/10/01 11:07:42  rudahl
 * adding persistent storage to Ipc and SS
 *
 * Revision 1.29  2005/09/25 12:06:51  rudahl
 * improved docs, naming
 *
 * Revision 1.28  2005/09/25 04:49:18  rudahl
 * changed sendCommand arg to take actual module number
 *
 * Revision 1.27  2005/04/01 03:27:52  rudahl
 * working on grstop Server modules
 *
 * Revision 1.26  2005/03/19 06:25:44  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.26  2005/03/11 21:37:28  rudahl
 * added getWorkingImage stuff
 *
 * Revision 1.25  2005/02/18 19:55:52  goldin
 * Remove GetProductLevel prototype
 *
 * Revision 1.24  2005/02/16 04:17:02  rudahl
 * adapt to GCC/MINGW differences
 *
 * Revision 1.23  2004/12/30 14:46:30  goldin
 * conditionalized for 16-bit
 *
 * Revision 1.22  2004/12/28 12:20:04  rudahl
 * added a gratuitous _cdecl
 *
 * Revision 1.21  2002/09/15 21:34:20  rudahl
 * added SetProductLevel
 *
 * Revision 1.20  2002/09/05 00:47:46  rudahl
 * moved GetProductLevel to IPC
 *
 * Revision 1.19  2001/11/30 19:19:16  rudahl
 * moved whichKnownCommand; added executeKnown
 *
 * Revision 1.18  2001/10/17 15:52:04  goldin
 * Added new methods for generating Category-based result fields
 *
 * Revision 1.17  2001/10/12 20:31:40  rudahl
 * provide for interrupt
 *
 * Revision 1.16  2001/10/05 16:18:45  rudahl
 * added sendSimpleCommand for C
 *
 * Revision 1.15  2001/08/23 18:03:20  goldin
 * Move Xml report methods to new Ipc module IpcXmlGen
 *
 * Revision 1.14  2001/08/22 20:49:57  rudahl
 * added CommFileName
 *
 * Revision 1.13  2001/08/22 20:03:00  rudahl
 * added CommFileName to wrapper
 *
 * Revision 1.12  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.11  2001/08/14 16:26:53  rudahl
 * added getModule
 *
 * Revision 1.10  2001/08/14 13:41:31  rudahl
 * added pczSequence
 *
 * Revision 1.9  2001/07/30 14:06:34  rudahl
 * added qUsingMenus to wrapper
 *
 * Revision 1.8  2001/07/26 15:08:53  rudahl
 * fixed viewport-to-server communication
 *
 * Revision 1.7  2001/07/12 20:10:52  rudahl
 * changed reportError, added reportOperationError
 *
 * Revision 1.6  2001/07/10 11:36:41  rudahl
 * added reportError; changed logError
 *
 * Revision 1.5  2001/07/04 21:33:09  rudahl
 * fixed some bugs; added sbility to SendRpy alt. to UI or SS
 *
 * Revision 1.4  2001/06/15 20:35:01  rudahl
 * finished impl. QryFile
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
 *
 ************************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * history:
 * 5.5	2005-1-29 ktr   adapt for Dragon 5.5
 * 5.7	2005-9-25 ktr	added support for persistent data
 * 6.0	2008-09-27 ktr	added waitReady, for GCP
 * 6.3	2012-12-28 ktr	added IpcStyle
 */

#ifndef IPCWRAP_H
#define IPCWRAP_H

#ifndef IPCFILE_H
typedef int IPC_STYLE_t;
#define IPC_CLASSIC 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOGGER_H
// override some old ipc_mw.lib fns
#define TRACE_G logTrace
#endif

typedef struct _TEXT_DESCRIPTOR
    {
    char* pczTextKey;   /* key tying this item to help file; may be null */
    char* pczTextValue; /* untranslated value associated with key - used 
                         * as "reminder" if key is not null/empty.
                         * Otherwise this is the primary text.
			 */
    } TEXT_DESCRIPTOR;

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
		char * czTraceArg);

void setTraceLevel(ulong ulLevel); // enable tracing

/* this fn is structured to permit use by atexit() */
void ipcShutdown();

//void logTrace(const char * czFormat,...);

/* output error information to a logging file, 
 * or whatever Logger::logError() is set up to do
 * In any case, the output is purely intended for the developer
 * @param 'lCode'        error 'number' - see err-spec.txt for details
 * @param 'czFormat'...  sprintf-style argument list
 */
//void logError(const long lCode,const char * czFormat,...);

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
		 const char * czFormat,...);

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
			  const char * czArgText);

	/* Send something to be put into the TRACING db.
	 * @param pczWhat	text of message
	 * @param pczWho	brief indication e.g. Exec, Error
	 * @param pczWhy	reason for tracing
	 */
void putTracing(const char * pczWhat,const char * pczWho,const char * pczWhy);

int getTraceLevel();

/* send a command to a module, using module number in dragonOb.h, 
 * and optionally wait for response
 * @param uModuleNo       module #; 4 is first viewport
 *			  (NOTE in Dragon 5.4, first viewport was 1)
 * @param czCommand       arbitrary command string
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
 * @param uStyle          what type of IPC communication to use?
 *		              IPC_XML wraps the content in XML
 *		              IPC_URL and IPC_SOCKET yet to be defined
 * @return                result of IpcSendWatcher::getSendState()
 *                        or -5 if a CmdSSxxx.$$$ is detected with iTimeOut < 0
 */
#if DRAGON_VER >= 6
int sendCommand(const uint uModuleNo,const char * czCommand, 
		const int iTimeOut, const int iWaitCondition,
		char * pczSequence,IPC_STYLE_t uStyle);
#else
int sendCommand(const uint uModuleNo,const char * czCommand, 
    		const int iTimeOut, const int iWaitCondition,
		char * pczSequence);
#endif

/* send command to UI (the default) or SS (if bSS)
 * @param czCmd  command to send
 * @param bSS    if true send to SS else to UI
 */
void sendSimpleCommand(const char * czCmd,const BOOL bSS);

void sendMessage(const int iCode, const char * czMessage);

/* maintain a progress file
 * If czMessage non-NULL, this is a new file
 * If bRemove, delete the existing file
 */
void sendProgress(const char * czMessage,
		  const ushort uPercent, const BOOL bRemove);

/* send reply to UI (the default) or SS (if bSS)
 */
void sendReply(const char * czSequence, const char * czMessage,
	       const BOOL bSS);

void sendReplyBlob(const char * czSequnece, const char * czMessage,
		   const byte * pBlob, const size_t uBlobSize);

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
		      char * cmd, BOOL bExecuteIfPossible);

/* *************************
 *
 * Query-Reply fns
 *
 * *************************/
typedef struct 
    {
    const char * czName;   /* specify before calling queryReceive */
    size_t uValueBufSize;  /*  "        "       "      "          */
    char * pczValueBuf;     /* buffer which gets filled in by queryReceive */
    } ATTRIBUTE_t;

/* generate and send a query; then wait for response.
 * Always received by UI
 * @param  uArgTotalSize  est. amount of buffer space needed for the args
 *                         (not counting the format string)
 * @param  czFormat       sprintf-style format string listing name=%s (%d)
 *                        pairs, each \n-terminated.
 * @return                0 => OK
 *                        -1 => some sort of error
 */
int sendModalQuery(const size_t uArgTotalSize, const char * czFormat,...);

/* check whether current query has been received and, if so, get values.
 * @param    uAttrCount  number of attributes requested
 * @param    pAttributes array of structures specifying which
 *                       attributes are desired, and which gets filled-in
 *                       by this fn.
 * @return   >0 => yes; value is number of attributes in Rpy
 *           0 => no
 *           -1 => there is no current query
 */
int queryReceive(size_t uAttrCount,ATTRIBUTE_t * pAttributes);

/* *************************
 *
 * end of Query-Reply fns
 *
 * *************************/

	 /* is anything happening? <0 for error,
	  * 0 OK, nothing to do
	  * >0 something needs attention
	  *  1 ??
	  *  2 - 9 match IpcCmdWatcher::getCmdStatus()
	  * @param pczBuf   buffer to copy any command into
	  * @param uBufSize size of buffer
	  */
int qCommandReceive(char * pczBuf,const size_t uBufSize);

/* get current time & return static string of form: ddd/hh:mm:ss (ee)
 * where ddd is the weekday abbreviation, hh:mm:ss is the usual and
 * (ee) is elapsed secs since program start
 * If bOldTime, just reutrn the existing string
 */
char * nowTimeStr(BOOL bOldTime);

/* @return true (1) if menu system is in use,
 *         false    if command-line
 * NOTE: this uses what's in the CFG file to discover this info,
 *       not what processes are actually running.
 */            
int qUsingMenus();

/* delete any IPC files which match pattern
 * @param czPattern OS-dependent wildcard pattern
 *                  node-name+extension only - no path
 */
void IpcFileCleanup(const char * czPattern);

const char * getThisModule();

	/*	create full path name consisting of the communications
	 *	(kpath) directory + name
	 *	Return pointer to static string
	 */
// the __cdecl seems necessary for the vfileapi.dll
#if defined __ZTC__ || defined __GCC__ || defined __MINGCC__
const char * CommFileName(const char * name);
const char * HomeFileName(const char * name);
const char * LangFileName(const char * name);
	//	create full path name consisting of the language subdir of
	//	the home directory + name
	//	Also sets czLanguage
	//	Return pointer to static string
const char * getLanguageAbbr(); // access logger::s_czLanguage

#else
const char * __cdecl CommFileName(const char * name);
const char * __cdecl HomeFileName(const char * name);
const char * __cdecl LangFileName(const char * name);
const char * __cdecl getLanguageAbbr(); // access logger::s_czLanguage
#endif

#if defined MOVEDTOSERVER || DRAGON_VER <= 5
const char * getWorkingImagePath();
BOOL isWorkingImageFile(const char * pczPath);
#endif // #if defined MOVEDTOSERVER || DRAGON_VER <= 5

/**
 * XML (calcResult) construction functions
 */
       
/**
 * Start accumulating XML data for a report.
 * pczCalcType is calculation type label.
 * pczId is Identifier. pczTitleKey is translation key
 * for title - if null, no title line will be generated.
 * pczTitleRemind is default/reminder text for title.
 * If pczTitleKey is null, pczTitleRemind will be ignored.
 * Returns a file handle to be passed to other methods
 * that add to the report.
 */
FILE * BeginReport(const char* pczCalcType,
		   const char* pczId,
		   const char* pczTitleKey,
		   const char* pczTitleRemind,
		   const int iRowCount);
/**
 * Finish off the XML generation and use IPC mechanism
 * to send the report to the UI.
 */
void EndReport(FILE* fp);

/**
 * Begin the header for the report. iFldCount is the number
 * of columns per row in the report. 
 */
void BeginHeader(FILE* fp, const int iFldCount);

/**
 * Finish off the header row.
 */
void EndHeader(FILE* fp);

/**
 * Start a group, i.e. a set of columns that should be kept
 * together during formatting.
 */
void BeginGroup(FILE* fp, char cGrpId);

/**
 * Start a group with a translated header
 */
void BeginKeyedGroup(FILE* fp, char cGrpId,
                const char* pczValueKey,
                const char* pczValueRemind,
                const char* pczSubstitute);

/**
 * End a group
 */
void EndGroup(FILE* fp);

/**
 * Add a header field. pczFieldId is the internal label for the column
 * pczFieldKey is the key for looking up the column title. 
 * pczFieldRemind is the default/reminder string for the column title.
 */
void AddHeaderField(FILE* fp,
		    const char* pczFieldId,
		    const char* pczFieldKey,
		    const char* pczFieldRemind,
		    const char* pczSubstitute,
		    const char* pczDisplay);
/**
 * Begin a row of report data.
 */
void BeginResultRow(FILE* fp);

/*
 * Finish off the current row of report data
 */
void EndResultRow(FILE* fp);

/*
 * Add data field to current row.
 * pczValueKey is the key for the value. This may be an empty string, 
 * indicating that the value does not need translation. pczValueRemind is the
 * reminder string, or the actual value if pczValueKey is null.
 * pczDataType is one of several possible data types, which give the 
 * UI clues with respect to formatting. pczEncoding is optional 
 * (may be null), but if specified indicates the encoding associated 
 * with the value.
 */
void AddResultField(FILE* fp,
		    const char* pczValueKey,
		    const char* pczValueRemind,
		    const char* pczSubstitute,
		    const char* pczDataType,
		    const char* pczEncoding);

/*
 * Add data field to current row with an itemCategory & itemIndex.
 * pczValueKey is the key for the value. This may be an empty string, 
 * indicating that the value does not need translation. pczValueRemind is the
 * reminder string, or the actual value if pczValueKey is null.
 * pczDataType is one of several possible data types, which give the 
 * UI clues with respect to formatting. pczEncoding is optional 
 * (may be null), but if specified indicates the encoding associated 
 * with the value.
 * pczCategory is the value to be used for "itemCategory" and
 * iIndex is the value for itemIndex (only relevant for signature reports).
 */
void AddCategoryResultField(FILE* fp,
		    const char* pczValueKey,
		    const char* pczValueRemind,
		    const char* pczSubstitute,
		    const char* pczDataType,
		    const char* pczEncoding,
                    const char* pczCategory,
		    const int iIndex);

/**
 * Add a note consisting of one or more text strings, translated or
 * not. Keystrings is an array of keys, reminders is the corresponding
 * array of reminders, substitutes is an array of substitution strings,
 * uCount is the number of individual text items
 * in the note.
 */
void AddNoteLine(FILE* fp,
		 const char* keystrings[],
		 const char* reminders[],
		 const char* substitutes[],
		 ushort uCount);


/**
 * Start a new table, in a report with multiple tables 
 */
  void BeginTable(FILE* fp, int border);

/**
 * End a subtable
 */
  void EndTable(FILE * fp);

/**
 * Add a ruler line in a table
 */
  void AddHorizontalRule(FILE * fp);

/**
 * Close file and delete tempfile - called in case of error.
 */
void DoReportCleanup(FILE* fp);

/**
 * Application-level function to create a text-only (TextTable) report.
 * TextInfo is an array of TEXT_DESCRIPTORs, each of which will be used
 * to create one paragram in the report. pczTitle is an optional title.
 * uCount is the number of items in TextInfo.
 */
void PrepareTextReport(TEXT_DESCRIPTOR TextInfo[], 
                       ushort uCount, const char* pczTitle);



    /**
     * Set the product level to different from what is determined from the
     * file. It can only be set to a less-priv. level; this is administered
     * here. If necessary, the file is examined to determine 
     * the current product level.
     * @param uProductlevel	desired new level
     * @return			0 if OK
     *				-1 if it's a not-allowed transition
     *				-2 if we can't determine current product level
     */
int SetProductLevel(ushort uProductLevel);

	/* static function which uses much of parseHeader() to get
	 * the intended size and compare it to the actual size on the disk
	 * Once called this will block, so the caller should be sure
	 * that the desired file already exists
	 * @param fullFileName	path and name of desired file
	 */
void waitReady(const char * fullFileName);

#ifdef __cplusplus
  }
#endif

#endif // ifndef IPCWRAP_H
