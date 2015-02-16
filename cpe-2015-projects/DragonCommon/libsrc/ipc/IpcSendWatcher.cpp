extern "C" {
#include "drelease.h"
char IPC_SEND_WATCHER_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.37 $$Date: 2014/12/07 03:01:38 $";
D_REL_IDSTR;
}
/*
 *	filename IpcSendWatcher.cpp
 *		$Revision: 1.37 $ $Date: 2014/12/07 03:01:38 $	
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
 * $Id: IpcSendWatcher.cpp,v 1.37 2014/12/07 03:01:38 rudahl Exp $
 * $Log: IpcSendWatcher.cpp,v $
 * Revision 1.37  2014/12/07 03:01:38  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.36  2014/12/06 10:49:20  rudahl
 * reconciled DragonProfessional with OpenDragon
 *
 * Revision 1.35  2014/12/05 07:09:36  rudahl
 * tracing
 *
 * Revision 1.34  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.33  2006/02/12 08:15:06  rudahl
 * reduced tracing
 *
 * Revision 1.32  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.31  2006/01/08 09:31:20  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.30  2005/09/25 12:11:41  rudahl
 * working on persistent data
 *
 * Revision 1.29  2005/08/12 09:22:49  goldin
 * Fix problem in trace statement - bad string arg causing a crash
 *
 * Revision 1.28  2005/04/25 10:49:41  rudahl
 * improved tracing
 *
 * Revision 1.27  2005/04/25 05:06:48  rudahl
 * lintish
 *
 * Revision 1.26  2005/04/24 10:53:12  goldin
 * Add more tracing
 *
 * Revision 1.25  2005/02/16 04:14:00  rudahl
 * adapt to GCC/MINGW differences
 *
 * Revision 1.24  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.23  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.22  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.21  2004/12/23 12:06:34  rudahl
 * lint-ish fix
 *
 * Revision 1.20  2004/11/30 04:31:44  rudahl
 * adapt for Mingw
 *
 * Revision 1.19  2002/06/12 23:52:20  rudahl
 * fixed misleading logmessage
 *
 * Revision 1.18  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.17  2001/08/28 20:06:47  rudahl
 * some improved logging
 *
 * Revision 1.16  2001/08/22 19:05:51  rudahl
 * fixup for gcc
 *
 * Revision 1.15  2001/08/22 19:02:39  rudahl
 * fixup for gcc
 *
 * Revision 1.14  2001/08/22 17:36:07  rudahl
 * mod for GCC
 *
 * Revision 1.13  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.12  2001/08/14 17:43:19  goldin
 * debugging cmd/rpy logic to viewport
 *
 * Revision 1.11  2001/07/26 15:08:53  rudahl
 * fixed viewport-to-server communication
 *
 * Revision 1.10  2001/06/15 20:35:44  rudahl
 * fixed Profile resend
 *
 * Revision 1.9  2001/06/06 12:08:01  rudahl
 * fixed sendProgress
 *
 * Revision 1.8  2001/06/02 18:25:50  rudahl
 * added reSend, for progress file
 *
 * Revision 1.7  2001/05/30 17:28:47  rudahl
 * integrate server and viewport communication
 *
 * Revision 1.6  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.5  2001/05/15 10:00:50  rudahl
 * adapted for Zortech build, which requires short filenames.
 * The build happens in a subdir named 'zor' and results in a
 * library in /lib/zor.
 *
 * Revision 1.4  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
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
 ****************************************************************
 * 
 *  This class watches for IPC files generated in response
 *  to commands, that is rpy, nak and progress files. 
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-9-25 ktr	changed member variable names to m_
 * 	2006-1-13 ktr	put in bit-wise conditionals for logTrace
 * 6.3	2012-12-28 ktr	added IpcStyle
 */

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/stat.h>

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

Class IpcSendWatcher::s_class_Base("IpcSendWatcher","Instance of class that watches, waiting to delete an IPC file that has been processed.");

const char * IpcSendWatcher::className() { return "IpcSendWatcher"; }

IpcSendWatcher::IpcSendWatcher(const char * czRemoteModule, const int iType,IPC_STYLE_t uStyle)
    : IpcWatcher(czRemoteModule,iType,TRUE,uStyle)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    bNoWait = /* for Cmd; some cmds wait, others don't; QRY always does */
      ((iType == RPY_FILE_TYPE) || (iType == NAK_FILE_TYPE)
          || (iType == MSG_FILE_TYPE) || (iType == PRO_FILE_TYPE) 
          || (iType == DAT_FILE_TYPE) );
    pczFilename = NULL;
    ulTimeStamp = 0;
    }

#ifdef __GXCC__
void * find_first(const char * filename, const int flag)
    {
    void * retval = NULL;
    glob_t globbuf;
    globbuf.gl_offs = 1;
    int globStat = glob(filename,0,NULL,&globbuf);
    if (globStat == 0)
        {
	retval = &globbuf; /* we're just testing if it's non-NULL,
			    * not derefing it */
        }
    globfree(&globbuf);
    return retval;
    }
#endif

	/** 
	 *  get current status of message which has been sent:
	 *   0      sent
	 *   1      accepted
	 *   2      progress PRO file seen
	 *   3      RPY seen
	 *   4      accepted and no further activity expected
	 *   < 0 => various errors:
	 *   -1     unknown
	 *   -2     NAK seen
	 *   -3     send blocked ( not supported )
	 *   -4     timeout ( not supported )
	 */
int IpcSendWatcher::getSendState()
    {
    int retval = -1;
    if (pczFilename != NULL)
        {
	retval = 0;             /* we know it existed */
	if (find_first(pczFilename,0) == NULL)
	    {
	    retval = 1;         /* but the file has disappeared */
	    if (bNoWait)
	        {
		retval = 4;     /* end of story */
	        }
	    else
	        {
		const char * czThisModule = DragonObject::getThisModule();
		char * pczProFilename 
		    = IpcProFile::createPatternedFilename(czThisModule,
							  pczFilename);
		char * pczNakFilename 
		    = IpcNakFile::createPatternedFilename(czThisModule,
							  pczFilename);
		char * pczRpyFilename 
		    = IpcRpyFile::createPatternedFilename(czThisModule,
							  pczFilename);
		if (find_first(pczProFilename,0) != NULL)
		    retval = 2; /* PRO file seen */
		else if (find_first(pczRpyFilename,0) != NULL)
		    retval = 3; /* RPY file seen */
		else if(find_first(pczNakFilename,0) != NULL)
		    retval = -2; /* NAK file seen */
		if (pczProFilename != NULL) free(pczProFilename);
		if (pczRpyFilename != NULL) free(pczRpyFilename);
		if (pczNakFilename != NULL) free(pczNakFilename);
		}
	    }
	}
    if ((Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	  && (Logger::getTraceLevel() & TRACE_LVL_DETAIL))
        Logger::logTrace("IpcSendWatcher::getSendState of %s returns %d",
			 pczFilename,retval);
    return retval;
    }

/* the name of the file which has just been sent.
 * Becomes invalid after cleanup()
 */
const char * IpcSendWatcher::getFilename()
    {
    return pczFilename;
    }

/* the timestamp (within 1 second) of the file which has just been sent.
 * Becomes invalid after cleanup()
 */
time_t IpcSendWatcher::getFileTimeStamp() { return ulTimeStamp; }

/* create and send a file.
 * The name of the file can be gotten from getFileName(),
 * the sequence from getFileSequence(),
 * the state from getSendState()
 * but only until cleanup() is executed.
 */
void IpcSendWatcher::send(const char * czMessage, const char * czSequence)
    {
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
    	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
        logTrace("IpcSendWatcher::send1 (en) to %s msg=%s sequence=%s filetype=%d=%s",
		 m_czRemoteModule,czMessage,czSequence,
		 m_iFileType,IpcFile::getFileTypeName(m_iFileType));
    cleanup(); /* from any previous file send */
    if ((m_iFileType == MSG_FILE_TYPE) || (m_iFileType == NAK_FILE_TYPE))
        Logger::logError(55,"IpcSendWatcher::send type missing code number;"
			 " msg=%s",m_iFileType,czMessage);
    else
        {
	char * pczName = NULL;
	char * pczMessageText = NULL;
	//	logTrace("IpcSendWatcher::send1 before getting msg");
	switch(m_iFileType)
	    {
	    case CMD_FILE_TYPE:
	      bNoWait = FALSE; /* in case it was set TRUE for prev. msg */
	      pczName 
		  = IpcCmdFile::createFilename(m_czRemoteModule,czSequence);
	      pczMessageText = IpcCmdFile::sendFile(pczName,czMessage);
	      break;
	    case RPY_FILE_TYPE:
	      pczName 
		  = IpcRpyFile::createFilename(m_czRemoteModule,czSequence);
	      pczMessageText = IpcRpyFile::sendFile(pczName,czMessage);
	      break;
	    case PRO_FILE_TYPE:
	      pczName 
		  = IpcProFile::createFilename(m_czRemoteModule,czSequence);
	      pczMessageText = IpcProFile::sendFile(pczName,czMessage);
	      break;
	    case QRY_FILE_TYPE:
	      pczName = IpcQryFile::createFilename();
	      pczMessageText = IpcQryFile::sendFile(pczName,czMessage);
	      break;
	    }

	//	logTrace("IpcSendWatcher::send1 pczName=%s pczMessageText=%s",
	//	 NN(pczName),NN(pczMessageText));
	if (pczMessageText != NULL)
	    {
	    ulTimeStamp = Logger::getCorrectedTime(); 
	       /* almost same as in the file */
	    free(pczMessageText);
	    }
	else /* error */
	    {
	    Logger::logError(55,"IpcSendWatcher::send1 "
			     "filetype %d (%s) failed filename=%s",
			     m_iFileType,IpcFile::getFileTypeName(m_iFileType),
			     pczName);
	    if (pczName != NULL)
	        free(pczName);
	    pczName = NULL;
	    }
	pczFilename = pczName;
	}
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
        logTrace("IpcSendWatcher::send1 (ex)");
    }

/* see notes above */
/* this version is specialized for cases with a code #, of which the only ones
 * are Msg and Nak */
void IpcSendWatcher::send(const int iCode,const char * czMessage, 
			   const char * czSequence)
    {
    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
	logTrace("IpcSendWatcher::send2 (en) type=%d (%s) code=%d  msg=%s",
		 m_iFileType,IpcFile::getFileTypeName(m_iFileType),
		 iCode,czMessage);
    char * pczName = NULL;
    char * pczMessageText = NULL;
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
	logTrace("::Before cleanup");
    cleanup(); /* from any previous file send */
    if ((m_iFileType != MSG_FILE_TYPE) && (m_iFileType != NAK_FILE_TYPE))
	send(czMessage,czSequence); 
    else
        {
	switch(m_iFileType)
	  {
	  case MSG_FILE_TYPE:
	    pczName = IpcMsgFile::createFilename(DragonObject::getThisModule(),
						 "");
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
		logTrace("IpcSendWatcher::send created name is '%s'",pczName);
	    pczMessageText = IpcMsgFile::sendFile(pczName,czMessage,iCode);
	    break;
	  case NAK_FILE_TYPE:
	    pczName = IpcNakFile::createFilename(m_czRemoteModule,czSequence);
	    pczMessageText = IpcNakFile::sendFile(pczName,czMessage,iCode);
	    break;
	  //~~case QRY_FILE_TYPE:
	    //break;
	    //~~	  case DAT_FILE_TYPE:
	    //pFile = new IpcDatFile(pczName);
	    //break;
	  }
	if (pczMessageText != NULL) //~~ not correct for Pro
	    {
	    ulTimeStamp = Logger::getCorrectedTime();
	    /* almost same as the file itself*/
	    free(pczMessageText);
	    pczMessageText = NULL; 
	    }
	else /* error */
	    {
	    Logger::logError(55,"IpcSendWatcher::send2 "
			     "filetype %d (%s) failed file=%s",
			     m_iFileType,IpcFile::getFileTypeName(m_iFileType),
			     pczName);
	    if (pczName != NULL)
	        free(pczName);
	    pczName = NULL;
	    }
	pczFilename = pczName;
	}
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
	Logger::logTrace("IpcSendWatcher::send (ex)");
    }

/* this version is specialized for cases with a blob, of which the only one
 * is Rpy */
void IpcSendWatcher::send(const char * czMessage, const char * czSequence,
			  const byte * pBlob, const size_t uBlobSize)
    {
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
        Logger::logTrace("IpcSendWatcher::send3 (en) to %s blobsize=%d msg=%s",
			 m_czRemoteModule,uBlobSize,czMessage);
    cleanup(); /* from any previous file send */
    if ((m_iFileType != RPY_FILE_TYPE) || (pBlob == NULL))
	send(czMessage,czSequence);
    else
        {
	char * pczName = IpcRpyFile::createFilename(m_czRemoteModule,czSequence);
	char * pczMessageText = IpcRpyFile::sendFile(pczName,czMessage,
						     pBlob,uBlobSize);
	if (pczMessageText != NULL)
	    {
	    ulTimeStamp = Logger::getCorrectedTime(); 
	       /* almost same as in the file */
	    free(pczMessageText);
	    }
	else /* error */
	    {
	    Logger::logError(55,"IpcSendWatcher::send3 "
			     "filetype %d (%s) failed file=%s",
			     m_iFileType,
			     IpcFile::getFileTypeName(m_iFileType),
			     pczName);
	    if (pczName != NULL)
	        free(pczName);
	    pczName = NULL;
	    }
	pczFilename = pczName;
	}
    }

/* revise an already sent file. Currently only for PRO files
 * The name of the file can be gotten from getFileName(),
 * the sequence from getFileSequence(),
 * the state from getSendState()
 * but only until cleanup() is executed.
 * @param  uPercent ranges from 0 to 99
 * @param  ulTare   is file size with zero percent in it
 * @return new file size ONLY if ulTare == 0, else return 0
 */
long IpcSendWatcher::reSend(const ulong ulPercent, const ulong ulTare)
    {
    long lSize = 0;
    struct stat statbuf;
    if (m_iFileType != PRO_FILE_TYPE)
        {
	lSize = -1;
        Logger::logError(55,"IpcSendWatcher::reSend incorrect file type %d",
			 m_iFileType);
        }
    else if (pczFilename == NULL)
        {
	lSize = -1;
        Logger::logError(35,"IpcSendWatcher::reSend file not found");
	}
    else 
        {
	if (stat(pczFilename,&statbuf) == 0)
	    {
	    if (ulTare > 0)
	        {
		ulong ulOldPct = statbuf.st_size - ulTare;
		if (ulPercent > ulOldPct)
		    {
		    char dots[101];
		    memset(dots,0,sizeof(dots));
		    memset(dots,'.',ulPercent - ulOldPct);
		    wsf(pczFilename,dots,strlen(dots),WSF_APPEND);
		    }
		}
	    else
	        lSize = statbuf.st_size;
	    }
	}
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
        Logger::logTrace("IpcSendWatcher::reSend to %s pct=%ld returning %ld",
			 m_czRemoteModule,ulPercent,lSize);
    return lSize;
    }

/* for certain Cmd files, don't wait. 
 * invoke this AFTER send()
 */
void IpcSendWatcher::setNoWait() { bNoWait = TRUE; }

/* for PRO files, this deletes the file */
void IpcSendWatcher::cleanup()
    {
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
	logTrace("IpcSendWatcher::cleanup (en)");
    if (pczFilename != NULL)
        {
	int stat = 0;
	if (m_iFileType == PRO_FILE_TYPE)
	    {
	    stat = remove(pczFilename);
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCSend)
		Logger::logTrace("IpcSendWatcher unlink %s returns %d",
				 pczFilename,stat);
	    }
	free(pczFilename);
	pczFilename = NULL;
	}
    IpcWatcher::cleanup();
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCSend))
	logTrace("IpcSendWatcher::cleanup (ex)");
    }

void IPCSENDWATCHERM_END() { puts(FIL_ID); }
