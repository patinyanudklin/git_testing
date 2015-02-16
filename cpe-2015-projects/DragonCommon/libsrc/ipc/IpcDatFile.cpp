extern "C" {
#include "drelease.h"
char IPC_DAT_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.12 $$Date: 2014/12/06 10:46:46 $";
D_REL_IDSTR;
}
/* 
 *	filename IpcDatFile.cpp
 *		$Id: IpcDatFile.cpp,v 1.12 2014/12/06 10:46:46 rudahl Exp $	
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
 * $Id: IpcDatFile.cpp,v 1.12 2014/12/06 10:46:46 rudahl Exp $
 * $Log: IpcDatFile.cpp,v $
 * Revision 1.12  2014/12/06 10:46:46  rudahl
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
 * Revision 1.6  2001/11/01 18:17:31  rudahl
 * began implementing Dat files for viewport communications
 *
 * Revision 1.5  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
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
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 ****************************************************************
 * 
 *  This class implements an IPC file to carry data of some sort. 
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
#include "IpcDatFile.h"

Class IpcDatFile::s_class_Base("IpcDatFile","Instance of IPC file that represents data.");

const char * IpcDatFile::className() { return "IpcDatFile"; }

IpcDatFile::IpcDatFile(const char * filename)
		: IpcFile(filename)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    }

	/* different IpcFile types have different syntax of names.
	 * The subclass fns create a name (including path) valid for
	 * that subclass.
	 * For Dat files, the 'xx' is the destination module and
	 *  the sequence numbers range through 0 - 999
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czRemoteModule   the 2-letter abbreviation src/target
	 * @param  czSequence       '' for next avail, '*' for wildcard
	 */
const char * IpcDatFile::createFilename(const char * czRemoteModule,
					const char * czSequence)
    {
    char * buf = 
        (pczKpath != NULL) ? (char *)malloc(strlen(pczKpath)+20) : NULL;
    const char * seq = czSequence;
    char numbuf[10];
    if (uDatSequence > 999)
        uDatSequence = 0;
    if ((czSequence == NULL) || (strlen(czSequence) == 0))
        {
	sprintf(numbuf,"%03d",uDatSequence++);
        seq = numbuf;
        }
    if (buf != NULL)
	sprintf(buf,"%s/Dat%s%s.$$$",getKpath(),czRemoteModule,seq);
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
char * IpcDatFile::sendFile(const char * czName,const char * czText)
    {
    char * pczBuf = (char *)malloc(strlen(czText)+50);
    char * pczRetval = NULL;
    if (pczBuf != NULL)
        {
	sprintf(pczBuf,"%s )\r\n%s",DragonObject::getThisModule(),czText);
	pczRetval = IpcFile::sendFile(czName,pczBuf);
	free(pczBuf);
	}
    return pczRetval;
    }

/* ~~ not fully implemented - only czSourceModule handled
 */
void IpcDatFile::parseRemainder(char * fbuf)
    {
    char * ptr = strtok(fbuf,"\n");
    if (ptr != NULL)
        {
	  //	datText = strdup(ptr+strlen(ptr)+1);
	strtok(fbuf," "); /* the '(' */
	strtok(NULL," "); /* the timestamp */
	strtok(NULL," "); /* the size */
	char * srcMod = strtok(NULL," ");
	strcpy_array(czSourceModule,srcMod);
	}
    if ((ptr == NULL) 
	        // || (datText == NULL) 
	       || (strlen(czSourceModule) != 2))
        doError("DatFile structural error ",IPC_ERROR_STRUCTURE);
    }

ushort IpcDatFile::uDatSequence = 1000; /* this forces it to be reset
					 * on first use */

void IPCDATFILE_END() { puts(FIL_ID); }
