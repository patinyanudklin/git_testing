extern "C" {
#include "drelease.h"
char IPC_NAK_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.12 $$Date: 2014/12/06 10:47:24 $";
D_REL_IDSTR;
}
/*
 *	filename IpcNakFile.cpp
 *		$Id: IpcNakFile.cpp,v 1.12 2014/12/06 10:47:24 rudahl Exp $	
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
 * $Id: IpcNakFile.cpp,v 1.12 2014/12/06 10:47:24 rudahl Exp $
 * $Log: IpcNakFile.cpp,v $
 * Revision 1.12  2014/12/06 10:47:24  rudahl
 * no significant differences between DragonProf and OpenDragon
 *
 * Revision 1.11  2005/04/25 05:06:48  rudahl
 * lintish
 *
 * Revision 1.10  2005/02/16 01:09:21  goldin
 * Fix CVS keywords
 *
 * Revision 1.9  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.8  2005/02/11 19:22:33  goldin
 * Save interim changes
 *
 * Revision 1.7  2005/02/09 13:36:28  goldin
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.6  2001/07/03 13:35:21  rudahl
 * added defenses against no kpath
 *
 * Revision 1.5  2001/06/15 19:52:15  rudahl
 * simplified IpcFile sendfile
 *
 * Revision 1.4  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.3  2001/05/15 10:00:50  rudahl
 * adapted for Zortech build, which requires short filenames.
 * The build happens in a subdir named 'zor' and results in a
 * library in /lib/zor.
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:57  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 ****************************************************************
 * 
 *  This class implements an IPC file indicating that a command
 *  failed for some reason. 
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
#include "IpcFile.h"
#include "IpcNakFile.h"

Class IpcNakFile::s_class_Base("IpcNakFile","Instance of IPC file that represents a reply indicating a command failed.");


const char * IpcNakFile::className() { return "IpcNakFile"; }

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
IpcNakFile::IpcNakFile(const char * filename)
		: IpcFile(filename)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    msgText = NULL;
    msgCode = -1;
    }

IpcNakFile::~IpcNakFile()
    {
    if (msgText != NULL) free(msgText);
    }

	/* Create a name (including path) valid for Nak file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czRemoteModule   the 2-letter abbreviation src/target
	 *                          must be specified
	 * @param  czSequence       must be specified
	 */
char * IpcNakFile::createFilename(const char * czRemoteModule,
				  const char * czSequence)
    {
    char * buf = 
        (pczKpath != NULL) ? (char *)malloc(strlen(pczKpath)+20) : NULL;
    const char * seq = czSequence;
    if (buf != NULL)
	sprintf(buf,"%s/Nak%s%s.$$$",getKpath(),czRemoteModule,seq);
    return buf;
    }

	/* Create a name (including path) valid for Nak file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czModule   the 2-letter abbreviation src/target
	 *                          must be sepcified
	 * @param  czPattern        a full path+name for a Cmd/Qry file, 
	 *                          which the Nak file must match.
	 */
char * IpcNakFile::createPatternedFilename(const char * czModule,
					   const char * czPattern)
    {
    char * buf = strdup(czPattern); /* new one will be same length */
    if (buf != NULL)
        {
	char czSave[IPC_FILENAME_SZ+1];
	char * NodePtr = buf + strlen(buf) - strlen("CmdAAxxx.$$$");
	strcpy_array(czSave,NodePtr);
	*NodePtr = '\0';
	strcat(buf,"Nak");
	strcat(buf,czModule);
	strcat(buf,czSave+5);           /* same seq # as in cmd file */
	}
    return buf;
    }

	/* Create the file, and send it
	 * To use this, call this class with the file contents.
	 * This will prefix that with other necessary fields
	 * and call the parent class fn which will write it to the disk.
	 * @param   czName is without the path
	 * @param   czText is the trailing part of the contents.
	 * @param   iCode  is the message code.
	 * @return  NULL if error; else the full text of the file
	 *          (which must be freed)
	 */
char * IpcNakFile::sendFile(const char * czName,const char * czText,
			    const int iCode)
    {
    char czPrefix[50];
    sprintf(czPrefix,"%s %d ",DragonObject::getThisModule(),iCode);
    return IpcFile::sendFile(czName,czText,czPrefix,NULL,0);
    }

	/**
	 * Main method for reading the non-common parts of 
	 * the IPC file. This method specifically implements
	 * Nak files.
	 */
void IpcNakFile::parseRemainder(char * fbuf)
    {
    char * ptr = strtok(fbuf,"\n");
    if (ptr != NULL)
        {
        msgText = strdup(ptr+strlen(ptr)+1);
	strtok(fbuf," "); /* the '(' */
	strtok(NULL," "); /* the timestamp */
	strtok(NULL," "); /* the size */
	char * srcMod = strtok(NULL," ");
	strcpy_array(czSourceModule,srcMod);
	ptr = strtok(NULL," ");
	msgCode = (ptr != NULL) ? atoi(ptr) : -1;
	}
    if ((ptr == NULL) ||(msgText == NULL) ||(strlen(czSourceModule) != 2))
        doError("NakFile structural error ",IPC_ERROR_STRUCTURE);
    }

void IPCNAKFILE_END() { puts(FIL_ID); }
