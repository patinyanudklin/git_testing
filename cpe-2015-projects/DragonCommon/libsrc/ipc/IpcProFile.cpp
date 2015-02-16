extern "C" {
#include "drelease.h"
char IPC_PRO_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.17 $$Date: 2014/12/06 10:47:24 $";
D_REL_IDSTR;
}
/*
 *	filename IpcProFile.cpp
 *		$Id: IpcProFile.cpp,v 1.17 2014/12/06 10:47:24 rudahl Exp $	
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
 * $Id: IpcProFile.cpp,v 1.17 2014/12/06 10:47:24 rudahl Exp $
 * $Log: IpcProFile.cpp,v $
 * Revision 1.17  2014/12/06 10:47:24  rudahl
 * no significant differences between DragonProf and OpenDragon
 *
 * Revision 1.16  2005/04/25 05:06:48  rudahl
 * lintish
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
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.11  2001/10/12 20:31:40  rudahl
 * provide for interrupt
 *
 * Revision 1.10  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.9  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.8  2001/06/15 20:31:25  rudahl
 * simplified IpcFile sendfile
 *
 * Revision 1.7  2001/06/02 18:25:27  rudahl
 * improved tracing
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
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 ****************************************************************
 * 
 *  This class implements an IPC file to transmit progress information
 *  for a long command, which can then be displayed as a progress bar. 
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 
 ********************************************************************
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
#include "IpcProFile.h"

Class IpcProFile::s_class_Base("IpcProFile","Instance of IPC file that represents a progress update.");

const char * IpcProFile::className() { return "IpcProFile"; }

IpcProFile::IpcProFile(const char * filename)
		: IpcFile(filename)
    {
    msgText = NULL;
    percentDone = 0;
    }

IpcProFile::~IpcProFile()
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (msgText != NULL) free(msgText);
    }

	/* Create a name (including path) valid for Pro file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czRemoteModule   the 2-letter abbreviation src/target
	 *                          must be specified
	 *                          10/12/01 NO LONGER USED
	 * @param  czSequence       "*" means next in seq
	 */
char * IpcProFile::createFilename(const char * czRemoteModule,
				  const char * czSequence)
    {
    char * buf = (char *)malloc(strlen(pczKpath)+20);
    const char * seq = czSequence;
    char numbuf[10];
    if ((czSequence == NULL) || (strlen(czSequence) == 0))
        {
	sprintf(numbuf,"%03d",uProSequence++);
        seq = numbuf;
        }
    if (uProSequence > 999)
        uProSequence = 0;
    if (buf != NULL)
	sprintf(buf,"%s/Pro%s%s.$$$",getKpath(),getThisModule(),seq);
    Logger::logTrace("IpcProFile::createFilename buf=%s seq=%s",buf,seq);
    return buf;
    }

	/* Create a name (including path) valid for Pro file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czModule   the 2-letter abbreviation src/target
	 *                          must be sepcified
	 * @param  czPattern        a full path+name for a Cmd/Qry file, 
	 *                          which the Pro file must match.
	 */
char * IpcProFile::createPatternedFilename(const char * czModule,
					   const char * czPattern)
    {
    char * buf = strdup(czPattern); /* new one will be same length */
    if (buf != NULL)
        {
	char czSave[IPC_FILENAME_SZ+1];
	char * NodePtr = buf + strlen(buf) - strlen("CmdAAxxx.$$$");
	strcpy_array(czSave,NodePtr);
	*NodePtr = '\0';
	strcat(buf,"Pro");
	strcat(buf,czModule);
	sprintf(buf+strlen(buf),"%03d",uProSequence++);
	if (uProSequence > 999)
	    uProSequence = 0;
	strcat(buf,czSave+8);
	}
    return buf;
    }

	/* Create the file, and send it
	 * To use this, call this class with the file contents.
	 * This will prefix that with other necessary fields
	 * and call the parent class fn which will write it to the disk.
	 * @param   czName is without the path
	 * @param   czText is the trailing part of the contents.
	 * @return  NULL if error; else the full text of the file
	 *          (which must be freed)
	 */
char * IpcProFile::sendFile(const char * czName,const char * czText)
    {
      //    char * pczBuf = (char *)malloc(strlen(czText)+50);
      //char * pczRetval = NULL;
    Logger::logTrace("IpcProFile::sendFile name=%s text=%s",
		     (czName != NULL) ? czName : "(NULL)",
		     (czText != NULL) ? czText : "(NULL)");
    //if (pczBuf != NULL)
    //  {
    //	sprintf(pczBuf," )\r\n%s",czText);
	return IpcFile::sendFile(czName,czText,"",NULL,0);
	//free(pczBuf);
	//	}
	// return pczRetval;
    }

void IpcProFile::parseRemainder(char * fbuf)
    {
    long fsize = file_size(czFileName);
    char * ptr = strtok(fbuf,"\n");
    if (ptr != NULL)
        {
        msgText = strdup(ptr+strlen(ptr)+1);
	}
    percentDone = fsize - sizeInFile;
    if ((ptr == NULL) ||(msgText == NULL)
	  || (percentDone < 0) || (percentDone > 100))
        doError("ProFile structural error ",IPC_ERROR_STRUCTURE);
    }

	 /* return value is MALLOC'd and must be freed. */
const char * IpcProFile::getMsgText()
   {
   return msgText;
   }

int IpcProFile::getPercentDone()
    {
    return percentDone;
    }

ushort IpcProFile::uProSequence = 0;

void IPCPROFILE_END() { puts(FIL_ID); }
