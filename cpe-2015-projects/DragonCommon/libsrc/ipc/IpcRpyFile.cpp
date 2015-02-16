extern "C" {
#include "drelease.h"
char IPC_RPY_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.22 $$Date: 2014/12/06 10:47:24 $";
D_REL_IDSTR;
}
/*
 *	filename IpcRpyFile.cpp
 *		$Id: IpcRpyFile.cpp,v 1.22 2014/12/06 10:47:24 rudahl Exp $	
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
 * $Id: IpcRpyFile.cpp,v 1.22 2014/12/06 10:47:24 rudahl Exp $
 * $Log: IpcRpyFile.cpp,v $
 * Revision 1.22  2014/12/06 10:47:24  rudahl
 * no significant differences between DragonProf and OpenDragon
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
 * Revision 1.18  2005/02/09 13:36:28  goldin
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.17  2004/12/24 06:42:20  rudahl
 * adapt for linux
 *
 * Revision 1.16  2002/02/20 16:01:55  rudahl
 * fixed off-by-1 in getAttrVal
 *
 * Revision 1.15  2002/01/10 22:25:45  rudahl
 * added support for small-mode ZOR version
 *
 * Revision 1.14  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.13  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.12  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.11  2001/08/08 15:19:34  rudahl
 * fixed parsing of files including a blob, and permit waylay other modules Rpy files
 *
 * Revision 1.10  2001/07/31 19:51:44  rudahl
 * fixed problem with rpyFiles
 *
 * Revision 1.9  2001/07/03 13:35:21  rudahl
 * added defenses against no kpath
 *
 * Revision 1.8  2001/06/19 12:05:55  rudahl
 * fixed rpyfile
 *
 * Revision 1.7  2001/06/15 20:31:25  rudahl
 * simplified IpcFile sendfile
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
 * Revision 1.3  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * history   This is the IPC package developed within Together
 * 8/8/01   ktr    added protection against trying to parse a blob
 *
 ****************************************************************
 * 
 *  This class implements an IPC file that indicates the successful
 *  completion of a command. 
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
#include "IpcRpyFile.h"

const char * IpcRpyFile::className() { return "IpcRpyFile"; }

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
IpcRpyFile::IpcRpyFile(const char * filename)
		: IpcFile(filename)
    {
    attrList=valueList=NULL;
    valueIndices=NULL;
    }

IpcRpyFile::~IpcRpyFile()
    {
    if (attrList != NULL) free(attrList);
    if (valueList != NULL) free(valueList);
    if (valueIndices != NULL) free(valueIndices);
    }

	/* Create a name (including path) valid for Rpy file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czDestinationModule  2-letter abbreviation of target
	 *                              must be specified
	 * @param  czSequence           must be specified
	 */
char * IpcRpyFile::createFilename(const char * czDestinationModule,
					const char * czSequence)
    {
    char * buf = 
        (pczKpath != NULL) ? (char *)malloc(strlen(pczKpath)+20) : NULL;
    const char * seq = czSequence;
    if (buf != NULL)
	sprintf(buf,"%s/Rpy%s%s.$$$",getKpath(),czDestinationModule,seq);
    return buf;
    }

	/* Create a name (including path) valid for Rpy file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czModule   the 2-letter abbreviation src/target
	 *                          must be sepcified
	 * @param  czPattern        a full path+name for a Cmd/Qry file, 
	 *                          which the Rpy file must match.
	 */
char * IpcRpyFile::createPatternedFilename(const char * czModule,
					   const char * czPattern)
    {
    char * buf = strdup(czPattern); /* new one will be same length */
    if (buf != NULL)
        {
	char czSave[IPC_FILENAME_SZ+1];
	char * NodePtr = buf + strlen(buf) - strlen("CmdAAxxx.$$$");
	strcpy_array(czSave,NodePtr);
	*NodePtr = '\0';
	strcat(buf,"Rpy");
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
	 * @param   pBlob if non-NULL is binary data to append
	 *          (prefixed by ^Z = 0x1A)
	 * @param   uBlobSize is size of binary data to append or 0
	 * @return  NULL if error; else the full text of the file
	 *          with blob removed (this mem must be freed)
	 */
char * IpcRpyFile::sendFile(const char * czName,const char * czText)
    {
    return sendFile(czName,czText,NULL,0);
    }

char * IpcRpyFile::sendFile(const char * czName,const char * czText,
			    const byte * pBlob, const size_t uBlobSize)
    {
      //    char * pczBuf = (char *)malloc(strlen(czText)+50);
      // char * pczRetval = NULL;
      //if (pczBuf != NULL)
      //{
      //sprintf(pczBuf,"%s )\r\n%s",DragonObject::getThisModule(),czText);
    return IpcFile::sendFile(czName,czText,DragonObject::getThisModule(),
			     pBlob,uBlobSize);
	//	free(pczBuf);
	//}
	//    return pczRetval;
    }

	/**
	 * Main method for reading the non-common parts of 
	 * the IPC file. This method specifically implements
	 * Rpy files.
	 */
void IpcRpyFile::parseRemainder(char * fbuf)
    {
    Logger::logTrace("rpyfile::parseRemaineder (en) buf='%s'",fbuf);
    char * ptr = strtok(fbuf,"\n");
    if (ptr != NULL)
        {
	int iLinecount=0;
	char * chaser = ptr+strlen(ptr);
        char * attributesText = chaser+1;
	strtok(fbuf," "); /* the '(' */
	strtok(NULL," "); /* the timestamp */
	strtok(NULL," "); /* the size */
	char * srcMod = strtok(NULL," ");
	strcpy_array(czSourceModule,srcMod);
	
	while ((chaser != NULL) && (*++chaser != '\0'))
	    {
	    while(strchr("\r\n",*chaser) != NULL) /* skip any cr,lf's */
	        chaser++;
	    if (*chaser == '\x1A')  /* ctl-Z */
	        break;
	    iLinecount++; /* count lines */
	    Logger::logTrace("rpyfile::parse counting chaser=%p (%X)",
			     chaser,*chaser);
	    chaser = strchr(chaser,'\n'); 
	    }
	Logger::logTrace("rpyfile::parseRemaineder "
			 "found %d lines; attrText='%s'",
			 iLinecount,(attributesText == NULL) 
			   ? "NULL" : attributesText);
	if (iLinecount > 0)
	    {
	    size_t attrListSz = (iLinecount+1)*32;
	       /* free any previous allocations */
	    if (attrList != NULL) free(attrList);
	    if (valueList != NULL) free(valueList); 
	    if (valueIndices != NULL) free(valueIndices);
	       /* these names will ultimately be multiple-blank separated
	        * located at 1 + a multiple of 32 */
	    attrList = (char *)malloc(attrListSz);
	       /* these values will be '\0'-separated */
	    valueList = (char *)calloc(strlen(attributesText),1);
	      /* and this will be a list of indices into valueList */
	    valueIndices = (size_t *)calloc(iLinecount+1,sizeof(size_t)); 
	    if ((attrList != NULL) && (valueList != NULL) 
		    && (valueIndices != NULL))
	        {
		int i = 0;
		memset(attrList,' ',attrListSz-1);
		attrList[attrListSz-1] = '\0';
		chaser = strtok(attributesText,"=");
		while ((chaser != NULL) && (*chaser != '\0'))
		    {
		    while(strchr("\r\n",*chaser) != NULL) /* skip any cr,lf's*/
		        chaser++;
		    if (*chaser == '\x1A')  /* ctl-Z */
		        break;
		    memcpy(&attrList[i*32+1],chaser,strlen(chaser));
		    chaser = strtok(NULL,"\r\n");
		    strcpy(&valueList[valueIndices[i]],chaser);
		    valueIndices[i+1] = valueIndices[i]+strlen(chaser)+1;
		    Logger::logTrace("rpyfile::parseRemaineder "
		    	     "item %d is '%s' attrList is size %d",
		    	     i,chaser,attrListSz);
		    chaser = strtok(NULL,"=");
		    i++;
		    }
		attrList[i*32] = '\0'; /* so strlen(attrList) reflects count */
		Logger::logTrace("rpyfile::parseRemaineder "
			 "attrList is '%s' strlen=%d",
			 attrList,strlen(attrList));
		}
            }
	}
    if ((ptr == NULL) || (strlen(czSourceModule) != 2) 
	   || (valueIndices == NULL)
	   || (attrList == NULL) || (valueList == NULL))
        {
        doError("RpyFile structural error ",IPC_ERROR_STRUCTURE);
	       /* if any are bad, they all are */
	if (attrList != NULL) free(attrList);
	if (valueList != NULL) free(valueList); 
	if (valueIndices != NULL) free(valueIndices);
	attrList=valueList=NULL;
	valueIndices=NULL;
        }
    //Logger::logTrace("rpyfile::parseRemaineder (ex)");
    }

/* the return value is MALLOCd and must be FREEd */
char * IpcRpyFile::getAttributeValue(const char * name)
    {
    char namebuf[35];
    char * match = NULL;
    char * val = NULL;
    memset(namebuf,0,sizeof(namebuf));
    strcpy(namebuf," ");
    strncpy(namebuf+1,name,32);
    strcat(namebuf," ");
    match = strstr(attrList,namebuf);
    //Logger::logTrace("IpcRpyFile::getAttributeValue "
    //	     "name='%s' buf='%s' match at %s",
    //	     name,namebuf,(match != NULL) ? match : "NULL");
    if (match != NULL)
        {
        size_t index = (match - attrList) / 32;
        val = strdup(&valueList[valueIndices[index]]);
        }
    Logger::logTrace("IpcRpyFile::getAttributeValue for %s returns '%s'",
		     name,(val != NULL) ? val : "NULL");
    return val;
    }

/* return value is MALLOC'd and must be freed. */
const char * IpcRpyFile::getAttributeNames()
    {
    return attrList;
    }

/* get count of attributes (based on 32-chars/attribute) */
size_t IpcRpyFile::getAttributeCount()
    {
    return strlen(attrList)/32;
    }

void IPCRPYFILE_END() { puts(FIL_ID); }
