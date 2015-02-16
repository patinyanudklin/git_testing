extern "C" {
#include "drelease.h"
char IPC_CMDWATCHER_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.24 $$Date: 2014/12/07 03:01:38 $";
D_REL_IDSTR;
}
/*
 *	filename IpcCmdWatcher.cpp
 *		$Id: IpcCmdWatcher.cpp,v 1.24 2014/12/07 03:01:38 rudahl Exp $
 *
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
 ********************************************************************
 *
 * $Id: IpcCmdWatcher.cpp,v 1.24 2014/12/07 03:01:38 rudahl Exp $
 * $Log: IpcCmdWatcher.cpp,v $
 * Revision 1.24  2014/12/07 03:01:38  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.23  2014/12/06 10:49:20  rudahl
 * reconciled DragonProfessional with OpenDragon
 *
 * Revision 1.22  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.21  2006/09/17 13:33:35  goldin
 * deal with special cases
 *
 * Revision 1.20  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.19  2005/12/04 11:18:53  rudahl
 * added some debugging/tracing
 *
 * Revision 1.18  2005/09/27 03:17:20  rudahl
 * missing declaration for whatis
 *
 * Revision 1.17  2005/09/27 03:13:21  rudahl
 * integrating SSDb into Executable required a const
 *
 * Revision 1.16  2005/09/25 12:11:41  rudahl
 * working on persistent data
 *
 * Revision 1.15  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.14  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.13  2005/02/11 19:22:33  goldin
 * Save interim changes
 *
 * Revision 1.12  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.11  2002/09/09 17:08:51  rudahl
 * added bulletproofing to whichknowncommand
 *
 * Revision 1.10  2001/11/30 19:19:16  rudahl
 * moved whichKnownCommand; added executeKnown
 *
 * Revision 1.9  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
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
 * Revision 1.4  2001/05/04 08:44:40  rudahl
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
 *
 ****************************************************************
 * 
 *  This class implements a class that watches for IPC files to show
 *  up. It also knows how to execute some generic commands like GETTIME.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-9-26 ktr	migrate to v 5.7
 * 	2006-1-12 ktr	protect against pfile == NULL
 * 6.3	2012-12-28 ktr	added IpcStyle
 ********************************************************************
 *
 */

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcCmdFile.h"
#include "IpcWatcher.h"
#include "IpcReceiveWatcher.h"
#include "IpcCmdWatcher.h"

Class IpcCmdWatcher::s_class_Base("IpcCmdWatcher","Instance of class to watch for incoming commands.");

IpcCmdWatcher::IpcCmdWatcher(const char * czRemoteModule,IPC_STYLE_t uStyle)
    : IpcReceiveWatcher(czRemoteModule,CMD_FILE_TYPE,uStyle)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    czProtoFile 
        = IpcCmdFile::createFilename(DragonObject::getThisModule(),"*");
    m_lTimeOffsetError = 0;
    if (czProtoFile == NULL)
        Logger::logError(55,"IpcCmdWatcher::ctor "
			 "unable to create ProtoFile name for '%s'",
			 DragonObject::getThisModule());
    }

/** get the abbrev. of the module which sent the command
 */
const char * IpcCmdWatcher::getSourceModule()
    {
    IpcCmdFile * pFile = (IpcCmdFile *)getFile();
    if (Logger::getTraceLevel() & TRACE_LVL_IPCCmd)
        Logger::logTrace("IpcCmdWatcher::getSender pFile=%p",pFile);
    return (pFile != NULL) ? pFile->getSourceModule() : "??" ;
    }

/* the command str is part of the IpcFile
 * both of which are deleted when executing cleanup()
 */
const char * IpcCmdWatcher::getCommand()
    {
    IpcCmdFile * pFile = (IpcCmdFile *)getFile();
    if (Logger::getTraceLevel() & TRACE_LVL_IPCCmd)
        Logger::logTrace("IpcCmdWatcher::getcommand pFile=%p",pFile);
    return (pFile != NULL) ? pFile->getCmdText() : "";
    }

/* is there a command available? If so, what is its status?
 * @return  status    =0 => nothing there
 *                    =1 => it's complete; go get it
 *                     (and cleanup afterward)
 *                    >1 for std cmds which have been fully processed:
 *                     (and therefore the cleanup has already been done;
 *                      however some info is still available)
 *                    2 = -NOOP; 3 = -TRACE 
 *                    4 = -SETTIME; 5 = -GETTIME 6 = -ABEXIT
 */
int IpcCmdWatcher::getCmdStatus()
    {
    int iStatus = IPC_CMD_NOTHING;
    if (Logger::getTraceLevel() & TRACE_LVL_IPCCmd)
        Logger::logTrace("IpcCmdWatcher::getCmdStatus protofile=%s",
			 czProtoFile);
    if (isAvailable(czProtoFile))
        {
	if (Logger::getTraceLevel() & TRACE_LVL_IPCCmd)
	    Logger::logTrace("IpcCmdWatcher::getCmdStatus it IS available");
	const char * pczCmd = getCommand();
	char * cmd = strdup(pczCmd);
	if (cmd == NULL)
	    Logger::logError(55,"IpcCmdWatcher::getCmdStatus "
			     "ran out of memory; cmd=%s",pczCmd);
	else
	    {
	    if (Logger::getTraceLevel() > 1)
	        Logger::logTrace("IpcCmdWatcher::getCmdStatus file=%s cmd=%s",
				 getFilename(),cmd);
	    strtok(cmd," \r\n");
	    int ndx = whichKnownCommand(NULL,10,cmd);
	    iStatus = (ndx >= 0) ? ndx : IPC_CMD_READY;
	    /* now handle any recognized cmd */
	    if (!executeKnownCommand(iStatus)) /* in IpcCmdWatcher */
	        {
		switch(iStatus)
		  {
		    //		  case IPC_CMD_NOOP:
		    //break;
		    //case IPC_CMD_TRACE:
		    //Logger::setTraceArg(strtok(NULL,"\r\n"));
		    //break;
		  case IPC_CMD_SETTIME:
		      Logger::setTimeOffset(time(NULL) 
					    - getFile()->getTimeStamp());
		      m_lTimeOffsetError = 0;
		      break;
		  case IPC_CMD_GETTIME:
		      {
		      long lTempOffset = time(NULL)-getFile()->getTimeStamp();
		      m_lTimeOffsetError 
			  = Logger::getTimeOffset() - lTempOffset;
		      char czReply[128];
		      sprintf(czReply,"TimeError=%+012ld",m_lTimeOffsetError);
		      sendReply(czReply);
		      }
		      break;
		  case IPC_CMD_ABEXIT:
		      break;
		  }
	      }
	    free(cmd);
	    }
	if (iStatus > IPC_CMD_READY)
	    cleanup();
        }
    return iStatus;
    }

	/* return the value which was calc'd when latest -GETTIME was received
	 */
long IpcCmdWatcher::getTimeOffsetError()
    {
    return m_lTimeOffsetError;
    }

/* STATIC fn to scan a list of known commands and return the index
 * of the one found, or -1.
 * @param  czCommandList    list of commands to recognize
 *                          if NULL, use required commands (size=10)
 * @param  uCommandListSize count of list
 * @param  cmd              string containing command
 * @return		    >= 0 is command index
 *			    -1 is not found
 *			    < -1 is arguments error
 */
int IpcCmdWatcher::whichKnownCommand(const char ** czCommandList,
				     const size_t uCommandListSize,
				     const char * cmd)
    {
    size_t ndx;
    int iRetval = -1;
    const char ** pList = (czCommandList == NULL)
      ? s_czIpcCommands : czCommandList;
    if (cmd == NULL)
        iRetval = -3;
    for (ndx = 0; ndx < uCommandListSize && iRetval == -1; ndx++)
        {
	if (pList[ndx] == NULL)
	    iRetval = -2; /* error */
	if (strcmp(cmd,pList[ndx]) == 0)
	    iRetval = ndx;
	}
    return iRetval;
    }

	/* STATIC fn to execute one of the 'known' commands.
	 * @param  iCmd    index of command
	 * @return         true if command was handled
	 */
BOOL IpcCmdWatcher::executeKnownCommand(const int iCmd)
    {
    BOOL bRetval = TRUE;
	    /* handle any recognized cmd */
    switch(iCmd)
        {
	case IPC_CMD_NOOP:
		break;
	case IPC_CMD_TRACE:
		Logger::setTraceArg(strtok(NULL,"\r\n"));
		break;
#ifdef NOTYET
	case IPC_CMD_SETTIME:
		Logger::setTimeOffset(time(NULL) - getFile()->getTimeStamp());
		m_lTimeOffsetError = 0;
		break;
	case IPC_CMD_GETTIME:
		{
		long lTempOffset = time(NULL) - getFile()->getTimeStamp();
		m_lTimeOffsetError = Logger::getTimeOffset() - lTempOffset;
		char czReply[128];
		sprintf(czReply,"TimeError=%+012d",m_lTimeOffsetError);
		sendReply(czReply);
		}
		break;
#endif
	default:
	        bRetval = FALSE;
		break;
	}
    return bRetval;
    }

const char * IpcCmdWatcher::className() { return "IpcCmdWatcher"; }

void IPC_DMD_WATCHER_END() { puts(FIL_ID); }
