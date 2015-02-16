extern "C" {
#include "drelease.h"
char IPC_WATCHER_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.21 $$Date: 2014/12/07 03:01:38 $";
D_REL_IDSTR;
}
/*
 *	filename IpcWatcher.cpp
 *		$Revision: 1.21 $ $Date: 2014/12/07 03:01:38 $	
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
 ****************************************************************
 *
 * $Id: IpcWatcher.cpp,v 1.21 2014/12/07 03:01:38 rudahl Exp $
 * $Log: IpcWatcher.cpp,v $
 * Revision 1.21  2014/12/07 03:01:38  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.20  2014/12/06 10:49:20  rudahl
 * reconciled DragonProfessional with OpenDragon
 *
 * Revision 1.19  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.18  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.17  2006/01/08 09:31:20  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.16  2005/09/25 12:11:41  rudahl
 * working on persistent data
 *
 * Revision 1.15  2005/04/25 05:06:48  rudahl
 * lintish
 *
 * Revision 1.14  2005/04/24 10:53:12  goldin
 * Add more tracing
 *
 * Revision 1.13  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.12  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.11  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.10  2001/11/30 19:19:16  rudahl
 * moved whichKnownCommand; added executeKnown
 *
 * Revision 1.9  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.8  2001/08/22 20:49:57  rudahl
 * added CommFileName
 *
 * Revision 1.7  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.6  2001/05/30 17:28:47  rudahl
 * integrate server and viewport communication
 *
 * Revision 1.5  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.4  2001/05/15 10:00:50  rudahl
 * adapted for Zortech build, which requires short filenames.
 * The build happens in a subdir named 'zor' and results in a
 * library in /lib/zor.
 *
 * Revision 1.3  2001/05/08 20:26:29  rudahl
 * extensive revisions to support Viewport (16-bit), and to generally
 * advance the implementation stage.
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:57  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 ****************************************************************
 * 
 *  This is the base class for classes that watch out for files
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-9-25 ktr	changed member variable names to m_
 * 	2006-1-8 ktr	put in bit-wise conditionals for logTrace
 * 6.3	2012-12-28 ktr	added IpcStyle
 * 
 ********************************************************************
 */

#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcWatcher.h"

Class IpcWatcher::s_class_Base("IpcWatcherFile","Instance of base class for all file monitoring classes.");

const char * IpcWatcher::className() { return "IpcWatcher"; }

/** ctor to be used for sending files
 */
IpcWatcher::IpcWatcher(const char * czRemoteModule, 
		       const int iType,
		       const BOOL bSend,IPC_STYLE_t uStyle)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (Logger::getTraceLevel() & TRACE_LVL_IPCWatcher)
        Logger::logTrace("%s::ctor %p",className(),this);
    if (czRemoteModule == NULL)
        m_czRemoteModule[0] = '\0';
    else
        { strcpy_array(m_czRemoteModule,czRemoteModule); }
    m_iFileType = iType;
    m_pFile = NULL;
    }

time_t IpcWatcher::getFileTimeStamp()
    { return (m_pFile==NULL) ? 0 : m_pFile->getTimeStamp();}

int IpcWatcher::getType(){return m_iFileType;}

const char * IpcWatcher::getFilename()
    {return (m_pFile == NULL) ? NULL : m_pFile->getFileName();}

/* retrieve sequence string of current file
 * @return         static buffer containing the sequence string,
 *                 or '000' if fname is NULL
 */
const char * IpcWatcher::getFileSequence()
    {
    const char * fname = getFilename();
    return getFileSequence(fname);
    }

/* static fn which just string processes name 
 * @param pczName  filename, or NULL
 * @return         static buffer containing the sequence string,
 *                 or '000' if pczName == NULL
 */
const char * IpcWatcher::getFileSequence(const char * pczName)
    {
    static char retval[4];
    if (pczName != NULL)
        strncpy(retval,pczName+strlen(pczName)-7,3);
    else
        strcpy(retval,"000");
    return retval;
    }

IpcFile * IpcWatcher::getFile(){ return m_pFile;}

void IpcWatcher::cleanup() 
    {
    if (Logger::getTraceLevel() & TRACE_LVL_IPCWatcher)
	logTrace("IpcWatcher::cleanup (en) %p file=%p",this,m_pFile);
    if (m_pFile != NULL) 
        {
	if (Logger::getTraceLevel() & TRACE_LVL_IPCWatcher)
	    logTrace("IpcWatcher::cleanup m_pFile is %p = '%s'",
		     m_pFile,NN(m_pFile->getFileName()));
        delete m_pFile;
	}
    m_pFile = NULL;
    if (Logger::getTraceLevel() & TRACE_LVL_IPCWatcher)
	logTrace("IpcWatcher::cleanup (ex)");
    }

const char * IpcWatcher::s_czIpcCommands[] = { REQUIRED_CMD_NAMES };

void IPCWATCHER_END() { puts(FIL_ID); }
