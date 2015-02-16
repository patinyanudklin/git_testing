extern "C" {
#include "drelease.h"
char IPC_RECEIVE_WATCHER_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.27 $$Date: 2014/12/07 03:01:38 $";
D_REL_IDSTR;
}
/*
 *	filename IpcReceiveFile.cpp
 *		$Revision: 1.27 $ $Date: 2014/12/07 03:01:38 $	
 *      ~~ Copyright 2001-2014 Kurt Rudahl and Sally Goldin
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
 * $Id: IpcReceiveWatcher.cpp,v 1.27 2014/12/07 03:01:38 rudahl Exp $
 * $Log: IpcReceiveWatcher.cpp,v $
 * Revision 1.27  2014/12/07 03:01:38  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.26  2014/12/06 10:49:20  rudahl
 * reconciled DragonProfessional with OpenDragon
 *
 * Revision 1.25  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.24  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.23  2006/01/08 09:31:20  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.22  2005/09/25 12:11:41  rudahl
 * working on persistent data
 *
 * Revision 1.21  2005/04/25 05:06:48  rudahl
 * lintish
 *
 * Revision 1.20  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.19  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.18  2005/02/11 19:22:33  goldin
 * Save interim changes
 *
 * Revision 1.17  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.16  2004/12/24 06:42:43  rudahl
 * moved find_first to zfiles
 *
 * Revision 1.15  2004/12/23 12:08:02  rudahl
 * replace assignment by strcpy, per lint
 *
 * Revision 1.14  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.13  2001/08/28 20:06:47  rudahl
 * some improved logging
 *
 * Revision 1.12  2001/08/22 17:34:13  rudahl
 * added GCC version of find_first
 *
 * Revision 1.11  2001/08/22 16:54:35  rudahl
 * added conditionals for GCC
 *
 * Revision 1.10  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.9  2001/07/31 19:51:44  rudahl
 * fixed problem with rpyFiles
 *
 * Revision 1.8  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.7  2001/05/15 10:00:50  rudahl
 * adapted for Zortech build, which requires short filenames.
 * The build happens in a subdir named 'zor' and results in a
 * library in /lib/zor.
 *
 * Revision 1.6  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
 *
 * Revision 1.5  2001/05/08 20:26:29  rudahl
 * extensive revisions to support Viewport (16-bit), and to generally
 * advance the implementation stage.
 *
 * Revision 1.4  2001/05/04 08:44:41  rudahl
 * Adapted to dual MSoft 16-bit & 32-bit build
 * added fn to IpcCmdWatcher to process the default commands automatically
 *
 * Revision 1.3  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.2  2001/04/29 18:02:05  rudahl
 * fixed problem retrieving command from cmd file
 *
 * Revision 1.1  2001/04/27 21:25:57  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 ****************************************************************
 * 
 *  This is a subclass of IpcWatcher that looks for files being
 *  sent to the current component.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2006-1-8 ktr	put in bit-wise conditionals for logTrace
 * 	2006-1-12 ktr	protect against pfile == NULL
 * 6.3	2012-12-28 ktr	added IpcStyle
 * 
 ********************************************************************
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

//#include <glob.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcCmdFile.h"
#include "IpcRpyFile.h"
#include "IpcNakFile.h"
#include "IpcMsgFile.h"
#include "IpcProFile.h"
#include "IpcQryFile.h"
#include "IpcDatFile.h"
#include "IpcWatcher.h"
#include "IpcSendWatcher.h"
#include "IpcReceiveWatcher.h"

Class IpcReceiveWatcher::s_class_Base("IpcReceiveWatcher",
"Instance of class to detect incoming IPC files.");

const char * IpcReceiveWatcher::className() { return "IpcReceiveWatcher"; }

IpcReceiveWatcher::IpcReceiveWatcher(const char * m_czRemoteModule, 
				     const int iType,IPC_STYLE_t uStyle)
    : IpcWatcher(m_czRemoteModule,iType,FALSE,uStyle)
    {
    pczCurrentFileName = NULL;
    pRpySendWatcher = NULL;
    }

/* is there a file available? If so, process it */
/* ultimately, this MUST be followed by cleanup() before a new
 * IpcFile can be sought */
BOOL IpcReceiveWatcher::isAvailable(const char * filename)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    BOOL bComplete = FALSE;
    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
        Logger::logTrace("ipcReceiveWatcher::isAvailable (en) "
			 "seeking file %s getTrace is x%X",
			 filename,Logger::getTraceLevel());
    struct _find_t * ff = find_first(filename,0);

    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
         Logger::logTrace("ipcReceiveWatcher::isAvailable seeking %s "
                          "\n   found=%p ('%s',%p) current=%p pfile=%p",
                          filename,ff,(ff != NULL) ? ff->name : "",
			  (ff != NULL) ? ff->name : NULL,
			  pczCurrentFileName,m_pFile);
    if (ff != NULL)
        {
	if (pczCurrentFileName != NULL) // do we already have one?
	    { /* for a PRO file, seeing it many times is normal */
	    if (m_pFile != NULL)
	        bComplete = m_pFile->isComplete();
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
	        {
		if (strcmp(pczCurrentFileName,ff->name) == 0) // same one?
		    Logger::logTrace("%s::isAvailable found %s again",
				     className(),ff->name);
		else
		    Logger::logTrace("%s::isAvailable found DIFFERENT file %s",
				     className(),ff->name);
	        }

	    find_free();
	    return bComplete;
	    }
	if (m_pFile != NULL)
	    delete m_pFile;
	m_pFile = NULL;
	pczCurrentFileName = strdup(ff->name);
	if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
	    Logger::logTrace("ipcReceiveWatcher::isAvailable "
			     "found %s of type %d curname=%p",
			     ff->name,getType(),pczCurrentFileName);
	switch(getType())
	  {
	  case CMD_FILE_TYPE:
	    m_pFile = new IpcCmdFile(ff->name);
	    break;
	  case RPY_FILE_TYPE:
	    m_pFile = new IpcRpyFile(ff->name);
	    break;
	  case NAK_FILE_TYPE:
	    m_pFile = new IpcNakFile(ff->name);
	    break;
	  case MSG_FILE_TYPE:
	    m_pFile = new IpcMsgFile(ff->name);
	    break;
	  case PRO_FILE_TYPE:
	    m_pFile = new IpcProFile(ff->name);
	    break;
	  case QRY_FILE_TYPE:
	    m_pFile = new IpcQryFile(ff->name);
	    break;
	    //~~	  case DAT_FILE_TYPE:
	    //m_pFile = new IpcDatFile(ff->name);
	    //break;
	  }
	if (m_pFile != NULL)
	    bComplete = m_pFile->isComplete();
	if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
	    Logger::logTrace("%s::isAvailable "
			     "found name=%s complete=%d m_pFile=%p",
			     className(),ff->name,bComplete,m_pFile);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_IPCReceive)
	Logger::logTrace("ipcReceiveWatcher::isAvailable (ex) "
			 "findfile=%p complete=%d",ff,bComplete);
    find_free();
    return ((ff != NULL) && bComplete);
    }

void IpcReceiveWatcher::cleanup() 
    {
    if (pczCurrentFileName != NULL) 
        free(pczCurrentFileName);
    pczCurrentFileName = NULL;
    IpcWatcher::cleanup();
    }

	/* create and send a Rpy file.
	 * then immediately do a cleanup
	 * @param   czMessage   all text which follows the initial, (), line
	 */
void IpcReceiveWatcher::sendReply(const char * czMessage)
    {

    if (pRpySendWatcher == NULL)
	pRpySendWatcher = new IpcSendWatcher(m_czRemoteModule,RPY_FILE_TYPE);
    if ((pRpySendWatcher != NULL) && (m_pFile != NULL))
        {
	const char * fname = m_pFile->getFileName();
	char seq[4];
	memset(seq,0,sizeof(seq));
	strncpy(seq,fname+5,3);
	pRpySendWatcher->send(czMessage,seq);
	}
    else
        Logger::logError(44,
			 "IpcReceiveWatcher::sendReply to %s missing %s info",
			 m_czRemoteModule,
			 (pRpySendWatcher == NULL) 
		            ? "Reply Watcher" : "IPC File");
    }
	/* don't know why we need this */
IpcSendWatcher * IpcReceiveWatcher::getSendWatcher()
    {
    return pRpySendWatcher;
    }

	/* retrieve sender of received file
	 * @return         static buffer containing the sender abbreviation
	 */
const char * IpcReceiveWatcher::getSender()
    {
    return (m_pFile != NULL) ? m_pFile->getSourceModule() : NULL;
    }

	/* retrieve sequence string of current file
	 * @return         static buffer containing the sequence string,
	 *                 or '000' if fname is NULL
	 */
//const char * IpcReceiveWatcher::getFileSequence()
//   {
//   return getFileSequence(fname);
//   }

void IPCRECWATCH_END() { puts(FIL_ID); }
