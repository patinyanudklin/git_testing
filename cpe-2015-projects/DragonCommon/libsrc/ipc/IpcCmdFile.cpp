extern "C" {
#include "drelease.h"
char IPC_CMD_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.22 $$Date: 2014/12/06 10:47:24 $";
D_REL_IDSTR;
}
/*
 *	filename IpcCmdFile.cpp
 *		$Id: IpcCmdFile.cpp,v 1.22 2014/12/06 10:47:24 rudahl Exp $
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
 * $Id: IpcCmdFile.cpp,v 1.22 2014/12/06 10:47:24 rudahl Exp $
 * $Log: IpcCmdFile.cpp,v $
 * Revision 1.22  2014/12/06 10:47:24  rudahl
 * no significant differences between DragonProf and OpenDragon
 *
 * Revision 1.21  2014/12/05 07:09:36  rudahl
 * tracing
 *
 * Revision 1.20  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.19  2005/12/04 11:18:53  rudahl
 * added some debugging/tracing
 *
 * Revision 1.18  2005/04/25 05:06:48  rudahl
 * lintish
 *
 * Revision 1.17  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.16  2005/02/11 19:22:33  goldin
 * Save interim changes
 *
 * Revision 1.15  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.14  2002/01/10 22:25:45  rudahl
 * added support for small-mode ZOR version
 *
 * Revision 1.13  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.12  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.11  2001/09/14 18:44:44  rudahl
 * documentation fixes
 *
 * Revision 1.10  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.9  2001/07/03 13:35:21  rudahl
 * added defenses against no kpath
 *
 * Revision 1.8  2001/06/15 20:31:25  rudahl
 * simplified IpcFile sendfile
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
 *  This class implements an IPC file to transmit a command. 
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2006-1-13 ktr	put in bit-wise conditionals for logTrace

 ********************************************************************
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcCmdFile.h"

Class IpcCmdFile::s_class_Base("IpcCmdFile","Instance of IPC file that represents a command.");

const char * IpcCmdFile::className() { return "IpcCmdFile"; }

        /**
	 * The IPC file constructor is called after a file is known to
	 * exist, with a full name including path. It reads the file to
	 * determines if it is complete (based on file size). 
	 * If it is not complete, it leaves the bComplete flag set to false
  	 * and returns immediately. 
	 * The caller must repeatedly call isComplete() until successful.
	 * When the file is complete, isComplete or the constructor 
	 * does further processing, setting
	 * the various attributes of the file, reading the data, etc. 
	 * The detailed processing depends on the type of file involved. 
	 * @param filename    Name of IpcFile (with path). Since this file has 
	 *                    been detected in the file system,
	 *                    it is assumed to exist.
	 */
IpcCmdFile::IpcCmdFile(const char * filename)
		: IpcFile(filename)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    cmdText = NULL;
    } 

IpcCmdFile::~IpcCmdFile()
    {
    if (cmdText != NULL) free(cmdText);
    }

	/* different types have different syntax of names.
	 * The subclass fns create a name (including path) valid for
	 * that subclass.
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czDestinationModule   the 2-letter abbreviation target
	 * @param  czSequence           '' for next avail, '*' for wildcard
	 */
char * IpcCmdFile::createFilename(const char * czDestinationModule,
				  const char * czSequence)
    {
    char * buf = 
        (pczKpath != NULL) ? (char *)malloc(strlen(pczKpath)+20) : NULL;
    const char * seq = czSequence;
    char numbuf[10];
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCCmd))
        Logger::logTrace("IpcCmdFile::createFileame (en) "
			 "dest='%s', sequence='%s' kpath='%s'",
			 czDestinationModule,czSequence,NN(pczKpath));
    if (uCmdSequence > (getThisModuleIndex()*100) + 99)
        uCmdSequence = getThisModuleIndex()*100;
    if ((czSequence == NULL) || (strlen(czSequence) == 0))
        {
	sprintf(numbuf,"%03d",uCmdSequence++);
        seq = numbuf;
        }
    if (buf != NULL)
	sprintf(buf,"%s/Cmd%s%s.$$$",getKpath(),czDestinationModule,seq);
    return buf;
    }

	/* Create the file, and send it
	 * To use this, call this class with the file contents.
	 * This will prefix that with other necessary fields
	 * and call the parent class fn which will write it to the disk.
	 * return value is ALLOC'd and must be freed
	 * @param   czName is without the path
	 * @param   czText is the trailing part of the contents.
	 * @return  NULL if error; else the full text of the file
	 *          (which must be freed)
	 */
char * IpcCmdFile::sendFile(const char * czName,const char * czText)
    {
      //    char * pczBuf = (char *)malloc(strlen(czText)+50);
      //c//har * pczRetval = NULL;
      //if (pczBuf != NULL)
      //{
      //sprintf(pczBuf,"%s )\r\n%s",DragonObject::getThisModule(),czText);
	return IpcFile::sendFile(czName,czText,DragonObject::getThisModule(),
				 NULL,0);
	//free(pczBuf);
	//	}
	// return pczRetval;
    }

void IpcCmdFile::parseRemainder(char * fbuf)
    {
    if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	    && (Logger::getTraceLevel() & TRACE_LVL_IPCCmd))
        Logger::logTrace("IpcCmdFile::parseRemainder of %p",fbuf);
    char * ptr = strtok(fbuf,"\n");
    memset(czSourceModule,0,sizeof(czSourceModule));
    if (ptr != NULL)
        {
        cmdText = strdup(ptr+strlen(ptr)+1);
	strtok(fbuf," "); /* the '(' */
	strtok(NULL," "); /* the timestamp */
	strtok(NULL," "); /* the size */
	char * srcMod = strtok(NULL," ");
	strcpy_array(czSourceModule,srcMod);
	if ((Logger::getTraceLevel() & TRACE_LVL_DETAIL)
	       && (Logger::getTraceLevel() & TRACE_LVL_IPCCmd))
	    Logger::logTrace("%s parseRem got cmd=%s",className(),cmdText);
	}
    if ((ptr == NULL) || (cmdText == NULL) || (strlen(czSourceModule) != 2))
        doError("CmdFile structural error ",IPC_ERROR_STRUCTURE);
    }

/* return value is MALLOC'd; is freed by dtor */
const char * IpcCmdFile::getCmdText()
    {
    return cmdText;
    }

ushort IpcCmdFile::uCmdSequence = 1000; /* this forces it to be reset
					 * on first use */


void IPCCMDFILE_END() { puts(FIL_ID); }
