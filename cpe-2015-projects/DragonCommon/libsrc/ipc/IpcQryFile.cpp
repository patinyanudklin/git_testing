extern "C" {
#include "drelease.h"
char IPC_QRY_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.17 $$Date: 2014/12/06 10:47:24 $";
D_REL_IDSTR;
}
/*
 *	filename IpcQryFile.cpp
 *		$Id: IpcQryFile.cpp,v 1.17 2014/12/06 10:47:24 rudahl Exp $	
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
 * $Id: IpcQryFile.cpp,v 1.17 2014/12/06 10:47:24 rudahl Exp $
 * $Log: IpcQryFile.cpp,v $
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
 * Revision 1.11  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.10  2001/09/14 18:44:44  rudahl
 * documentation fixes
 *
 * Revision 1.9  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.8  2001/07/03 13:35:21  rudahl
 * added defenses against no kpath
 *
 * Revision 1.7  2001/06/15 20:33:24  rudahl
 * finished impl. QryFile
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
 *
 ****************************************************************
 * 
 *  This class implements an IPC file to request data from another
 *  component. 
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
#include "IpcQryFile.h"

Class IpcQryFile::s_class_Base("IpcQryFile","Instance of IPC file that represents a request for information from the user.");

const char * IpcQryFile::className() { return "IpcQryFile"; }

IpcQryFile::IpcQryFile(const char * filename)
		: IpcFile(filename)
    {
    qryText = NULL;
    }

IpcQryFile::~IpcQryFile()
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (qryText != NULL) free(qryText);
    }

        /*
	 * The name returned is MALLOC'd and must be freed.
	 */
char * IpcQryFile::createFilename()
    {
    char * buf = 
        (pczKpath != NULL) ? (char *)malloc(strlen(pczKpath)+20) : NULL;
    char numbuf[10];
    sprintf(numbuf,"%03d",uQrySequence++);
    if (uQrySequence > 999)
        uQrySequence = 0;
    if (buf != NULL)
	sprintf(buf,"%s/Qry%s%s.$$$",getKpath(),
		DragonObject::getThisModule(),
		numbuf);
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
char * IpcQryFile::sendFile(const char * czName,const char * czText)
    {
      //     char * pczBuf = (char *)malloc(strlen(czText)+50);
      //char * pczRetval = NULL;
      //if (pczBuf != NULL)
      //{
      //sprintf(pczBuf," )\r\n%s",czText);
      //	char * pczRetval = 
//	free(pczBuf);
//	}
    return IpcFile::sendFile(czName,czText,"",NULL,0);
    }

void IpcQryFile::parseRemainder(char * fbuf)
    {
    if (Logger::getTraceLevel() > 1)
        Logger::logTrace("IpcQryFile::parseRemainder of %p",fbuf);
    char * ptr = strtok(fbuf,"\n");
    memset(czSourceModule,0,sizeof(czSourceModule));
    if (ptr != NULL)
        {
        qryText = strdup(ptr+strlen(ptr)+1);
	strtok(fbuf," "); /* the '(' */
	strtok(NULL," "); /* the timestamp */
	strtok(NULL," "); /* the size */
	strncpy(czSourceModule,czFileName+3,2);
	if (Logger::getTraceLevel() > 1)
	    Logger::logTrace("%s parseRem got qry=%s",className(),qryText);
	}
    if ((ptr == NULL) || (qryText == NULL) || (strlen(czSourceModule) != 2))
        doError("QryFile structural error ",IPC_ERROR_STRUCTURE);
    }

ushort IpcQryFile::uQrySequence = 0;

void IPCQRYFILE_END() { puts(FIL_ID); }
