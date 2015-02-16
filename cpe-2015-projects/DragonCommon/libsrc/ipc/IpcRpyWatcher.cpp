extern "C" {
#include "drelease.h"
char IPC_RPY_WATCHER_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.12 $$Date: 2014/12/07 03:01:38 $";
D_REL_IDSTR;
}
/*
 *	filename IpcRpyWatcher.cpp
 *		$Revision: 1.12 $ $Date: 2014/12/07 03:01:38 $	
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
 *
 * $Id: IpcRpyWatcher.cpp,v 1.12 2014/12/07 03:01:38 rudahl Exp $
 * $Log: IpcRpyWatcher.cpp,v $
 * Revision 1.12  2014/12/07 03:01:38  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.11  2014/12/06 10:49:20  rudahl
 * reconciled DragonProfessional with OpenDragon
 *
 * Revision 1.10  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.9  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.8  2006/01/08 09:31:20  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.7  2005/04/25 05:06:48  rudahl
 * lintish
 *
 * Revision 1.6  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.5  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.4  2005/02/09 13:36:28  goldin
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.3  2001/08/08 15:19:34  rudahl
 * fixed parsing of files including a blob, and permit waylay other modules Rpy files
 *
 * Revision 1.2  2001/07/31 19:51:44  rudahl
 * fixed problem with rpyFiles
 *
 * Revision 1.1  2001/06/15 19:52:50  rudahl
 * initial version
 ****************************************************************
 * 
 *  This class implements a watcher that looks for replies to
 *  commands. 
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2006-1-8 ktr	put in bit-wise conditionals for logTrace
 * 	2006-1-12 ktr	verify protect against pfile == NULL
 * 6.3	2012-12-28 ktr	added IpcStyle
 * 
 ********************************************************************
 */

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcRpyFile.h"
#include "IpcWatcher.h"
#include "IpcReceiveWatcher.h"
#include "IpcRpyWatcher.h"


Class IpcRpyWatcher::s_class_Base("IpcRpyWatcher","Instance of class that watches for replies from completed commands.");

const char * IpcRpyWatcher::className() { return "IpcRpyWatcher"; }

	/*
	 * @param uStyle      what type of IPC communication to use?
	 *		      IPC_XML wraps the content in XML
	 *		      IPC_URL and IPC_SOCKET yet to be defined
	 */
IpcRpyWatcher::IpcRpyWatcher(const char * czSequence,IPC_STYLE_t uStyle)
    : IpcReceiveWatcher("*",RPY_FILE_TYPE,uStyle)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    czProtoFile = IpcRpyFile::createFilename(DragonObject::getThisModule(),
					     czSequence);
    }

/* this constructor permits us to waylay an Rpy addressed to a different
 * module than this one. It is needed by ScriptServer to detect and
 * delete Rpy files sent by Server to UI, which UI knows nothing about.
 * (see the 'G' iPreExec command in CmdProcessor)
 */
IpcRpyWatcher::IpcRpyWatcher(const char * czSequence, const char * czModule,
			    IPC_STYLE_t uStyle)
    : IpcReceiveWatcher("*",RPY_FILE_TYPE,uStyle)
    {
    czProtoFile = IpcRpyFile::createFilename(czModule,czSequence);
    }

IpcRpyWatcher::~IpcRpyWatcher()
    {
    cleanup();
    }

/**
 * Return value associated with named attribute, or null
 * if if name not found
 * The name returned is MALLOC'd and must be freed.
 */
const char * IpcRpyWatcher::getAttributeValue(const char * attributeName)
    {
    IpcRpyFile * pFile = (IpcRpyFile *)getFile();
//    if (Logger::getTraceLevel() > 1)
    if (Logger::getTraceLevel() & TRACE_LVL_IPCRpy)
        Logger::logTrace("IpcRpyWatcher::getAttribVal for %s pFile=%p",
			 attributeName,pFile);
    return (pFile != NULL) ? pFile->getAttributeValue(attributeName) : NULL;
    }

	/**
	 * Return a blank-separated string  of all attribute names 
	 * represented in the attributes table.
	 */
const char * IpcRpyWatcher::getAttributeNames()
    {
    IpcRpyFile * pFile = (IpcRpyFile *)getFile();
//    if (Logger::getTraceLevel() > 1)
    if (Logger::getTraceLevel() & TRACE_LVL_IPCRpy)
        Logger::logTrace("IpcRpyWatcher::getAttribList pFile=%p",pFile);
    return (pFile != NULL) ? pFile->getAttributeNames() : NULL;
    }

/* is the reply available? If so, what is its status?
 * @return  status    =0 => nothing there
 *                    =1 => it's complete; go get it
 *                     (and cleanup afterward)
 */
int IpcRpyWatcher::getRpyStatus()
    {
    int iStatus = 0;
//    if (Logger::getTraceLevel() > 1)
    if (Logger::getTraceLevel() & TRACE_LVL_IPCRpy)
        Logger::logTrace("IpcRpyWatcher::getRpyStatus protofile=%s",
			 czProtoFile);
    if (isAvailable(czProtoFile))
        {
	  //	if (Logger::getTraceLevel() > 1)
	if (Logger::getTraceLevel() & TRACE_LVL_IPCRpy)
	    Logger::logTrace("IpcRpyWatcher::getRpyStatus it IS available");
	iStatus = 1;
        }
    return iStatus;
    }

void IPCRPYWATCH_END() { puts(FIL_ID); }
