extern "C" {
#include "drelease.h"
char IPC_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.42 $$Date: 2014/12/29 03:30:57 $";
D_REL_IDSTR;
}
/*
 *	filename IpcFile.cpp
 *		$Revision: 1.42 $ $Date: 2014/12/29 03:30:57 $	
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
 * $Id: IpcFile.cpp,v 1.42 2014/12/29 03:30:57 rudahl Exp $
 * $Log: IpcFile.cpp,v $
 * Revision 1.42  2014/12/29 03:30:57  rudahl
 * convert to using dragon version number
 *
 * Revision 1.41  2014/12/07 03:03:04  rudahl
 * undo some conditionals re STYLE
 *
 * Revision 1.40  2014/12/05 07:09:36  rudahl
 * tracing
 *
 * Revision 1.39  2014/04/02 12:02:22  rudahl
 * finished separating dtk,rosetta to new mingw version adaptations for Linux build
 *
 * Revision 1.38  2014/04/01 07:28:16  rudahl
 * lint esp from old mingc
 *
 * Revision 1.37  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.36  2008/09/27 11:43:33  rudahl
 * added waitReady
 *
 * Revision 1.35  2006/01/13 14:21:47  rudahl
 * improving tracing control
 *
 * Revision 1.34  2006/01/08 09:31:20  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.33  2005/04/25 10:49:41  rudahl
 * improved tracing
 *
 * Revision 1.32  2005/04/25 05:06:30  rudahl
 * added MsgTypeName, FileTypeName
 *
 * Revision 1.31  2005/03/30 10:56:00  rudahl
 * small adaptations for MFC60/viewport
 *
 * Revision 1.30  2005/03/29 09:10:39  goldin
 * Fix clean to work with Linux
 *
 * Revision 1.29  2005/03/27 10:41:50  goldin
 * Fix bug in sendFile - if write failed, then tried to access null ptr
 *
 * Revision 1.28  2005/02/28 22:49:46  goldin
 * Replace rsfgets
 *
 * Revision 1.27  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.26  2005/02/11 19:22:33  goldin
 * Save interim changes
 *
 * Revision 1.25  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.24  2002/09/09 17:09:20  rudahl
 * rewrote clean()
 *
 * Revision 1.23  2002/04/04 16:03:26  rudahl
 * fixed ctrl-Z problem in logtrace
 *
 * Revision 1.22  2002/02/20 16:01:20  rudahl
 * added optional second arg to clean()
 *
 * Revision 1.21  2002/02/12 21:25:18  rudahl
 * cleanup
 *
 * Revision 1.20  2002/01/10 22:25:45  rudahl
 * added support for small-mode ZOR version
 *
 * Revision 1.19  2001/10/05 16:18:45  rudahl
 * added sendSimpleCommand for C
 *
 * Revision 1.18  2001/09/26 19:04:52  rudahl
 * minor changes and de-linting for GCC, including fine_first
 *
 * Revision 1.17  2001/09/18 12:53:09  rudahl
 * documentation changes
 *
 * Revision 1.16  2001/09/14 18:44:44  rudahl
 * documentation fixes
 *
 * Revision 1.15  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.14  2001/08/28 20:06:47  rudahl
 * some improved logging
 *
 * Revision 1.13  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.12  2001/07/10 11:38:10  rudahl
 * improved logging msgs
 *
 * Revision 1.11  2001/06/15 19:52:15  rudahl
 * simplified IpcFile sendfile
 *
 * Revision 1.10  2001/05/31 12:18:23  rudahl
 * fixed typo
 *
 * Revision 1.9  2001/05/30 17:28:47  rudahl
 * integrate server and viewport communication
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
 * Revision 1.4  2001/05/04 08:44:41  rudahl
 * Adapted to dual MSoft 16-bit & 32-bit build
 * added fn to IpcCmdWatcher to process the default commands automatically
 *
 * Revision 1.3  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.2  2001/04/29 18:02:05  rudahl
 * fixed problem retrieving command from cmd file
 *
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 ****************************************************************
 * 
 *  This class is the base class for all kinds of Ipc files
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 *	2005-4/25 ktr	added name strings for file and message types
 * 5.7	2006-1-8 ktr	put in bit-wise conditionals for logTrace
 * 6.0	2008-09-27 ktr	added waitReady, for GCP
 * 6.3	2012-12-28 ktr	added IpcStyle
 ********************************************************************
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#if defined __MINGCC__ || defined __GCC__
#include <unistd.h>
#endif
extern "C" char * strupr(char * p); /* in wfutl/compmisc.c */

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"

Class IpcFile::s_class_Base("IpcFile","Instance of Base class for all IPC files.");

// strings defined in dragonOb.h
const char * IpcFile::s_czFiletypeNames[] = { IPC_FILE_TYPE_NAMES };
const char * IpcFile::s_czMsgtypeNames[] = { IPC_MSG_TYPE_NAMES };

const char * IpcFile::className() { return "IpcFile"; }

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
	 * @param uStyle      what type of IPC communication to use?
	 *		      IPC_XML wraps the content in XML
	 *		      IPC_URL and IPC_SOCKET yet to be defined
	 */
IpcFile::IpcFile(const char * filename,IPC_STYLE_t uStyle)
    {
    m_uStyle = uStyle;
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());

      /* make sure everything's initialized to something */
    sizeInFile = 0;
    timeStamp = 0;
    bComplete = FALSE;
    memset(czFileName,0,sizeof(czFileName));
    memset(czSourceModule,0,sizeof(czSourceModule));
    fileType = UNKNOWN_FILE_TYPE;

    strcpy_array(czFileName,filename);
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        Logger::logTrace("%s::ctor for %s",className(),czFileName);
    }

char * IpcFile::createFilename(const char * czRemoteModule,
			       const char * czSequence)
    { return NULL; }

const char * IpcFile::createFilename(const char * nodename)
    {
    char * buf = (char *)malloc(strlen(pczKpath)+20);
    if (buf != NULL)
	sprintf(buf,"%s/%s",getKpath(),nodename);
    return buf;
    }

	/* STATIC fn: finish creating the file, and send it
	 * To use this, call the subclass with the file contents.
	 * The sublass will prefix that with other necessary fields
	 * and call this fn which will write it to the disk.
	 * @param   czName is without the path
	 * @param   czText is the trailing part of the contents.
	 * @param   czPrefix is prefixed to header before czText.
	 *          it may be "" but must not be NULL
	 * @param   pBlob if non-NULL is binary data to append
	 *          (prefixed by ^Z = 0x1A)
	 * @param   uBlobSize is size of binary data to append or 0
	 * @return  NULL if error; else the full text of the file
	 *          (which must be freed)
	 */
char * IpcFile::sendFile(const char * czName,const char * czText)
    {
    return sendFile(czName,czText,"",NULL,0);
    }

char * IpcFile::sendFile(const char * czName,const char * czText,
			 const char * czPrefix,
			 const byte * pBlob, const size_t uBlobSize)
    {
    size_t uBufSize = strlen(czText)+50+uBlobSize;
    char * pczBuf = (char *)malloc(uBufSize+1);
    char * pczRetval = NULL;
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        logTrace("IpcFile::sendFile (en) filename='%s' prefix='%s' blobsize=%d bufsize=%d text=%s",
    	czName,czPrefix,uBlobSize,uBufSize,czText);
    if (pczBuf != NULL)
        {
	size_t uSize = strlen(czText)+strlen(czPrefix)+27;
	if (pBlob != NULL) 
	    uSize += uBlobSize+1;
	//logTrace("IpcFile::sendFile b4 get corrected time");
	time_t ulCorrectedTime = Logger::getCorrectedTime();
	//logTrace("IpcFile::sendFile after get corrected time = %ld",ulCorrectedTime);
	//#if defined __MINGCC__ || defined __GCC__
#if defined __GCC__
	// This form can't be used with the old mingw
	snprintf(pczBuf,uBufSize,"( %012lld %06d %s)\r\n%s\r\n",
	    (unsigned long long)ulCorrectedTime,uSize,czPrefix,czText);
#else	// viewport building
	sprintf(pczBuf,"( %012ld %06d %s)\r\n%s\r\n",
	    (unsigned long)ulCorrectedTime,uSize,czPrefix,czText);
#endif
	//	printf("IpcFile::sendFile after snprintf=%s\n",pczBuf);
	//logTrace("IpcFile::sendFile after snprintf=%s",pczBuf);
	char * pEnd = pczBuf+strlen(pczBuf);
	if (pBlob != NULL) 
	    {
	    *pEnd = '\x1A'; 
	    memcpy(pEnd+1,pBlob,uBlobSize);
	    }
        int iWritten = 0;
	if ((iWritten = wsf(czName,pczBuf,uSize,WSF_TRUNC)) == (int)uSize)
	    {
	    pczRetval = pczBuf;
	    *pEnd = '\0'; /* don't keep the blob if any */
	    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
		Logger::logTrace("IpcFile sent file %s: %s (%d) (BlobSize=%d)",
			       czName,pczRetval,strlen(pczBuf),uBlobSize);
	    if (strlen(pczRetval) < 60) /* for logging turn '\r\n' into '..' */
	        {
		while (strchr(pczRetval,'\r') != NULL)
		  *strchr(pczRetval,'\r') = '.';
		while (strchr(pczRetval,'\n') != NULL)
		  *strchr(pczRetval,'\n') = '.';
	        }
	    doLevel1Tracing("IpcFile::Send %s {%s}",czName,pczRetval);
	    }
	else
	    {
	    char czOut[20];
//	    printf("NG: iWritten=%d\n",iWritten);
	    sprintf(czOut,"%d",iWritten);
	    doLevel1Tracing(
		"IpcFile::Send error writing contents of Ipc file: "
		"%s\nwsf returned %s\n",
		pczBuf, czOut);
	    }
	}
    else
        Logger::logError(IPC_ERROR_MEMORY,
			 "IpcMsgFile Can't get memory to write");
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        logTrace("IpcFile::sendFile (ex) returning %s",NN(pczRetval));
    return pczRetval;
    }

BOOL IpcFile::processFile()
    {
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        Logger::logTrace("%s::processFile (en)",className());
    FILE* pInfile = NULL;
    const char * fullFilename = createFilename(czFileName);
    long fsize = file_size(fullFilename);
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        Logger::logTrace("%s::processFile size=%ld fullname=%s",
			 className(), fsize,fullFilename);
    bComplete = FALSE;
    fileType = determineFileType(czFileName);	     
    sizeInFile = parseHeader(fullFilename);
    if (fsize == sizeInFile)
        {
	char * fbuf = (char *)malloc(fsize+1);
	if (fbuf != NULL)
	    {
	    memset(fbuf,0,fsize+1);
	    pInfile = fopen(fullFilename,"rb");
	    if (pInfile == NULL)
	        {
	        Logger::logError(IPC_ERROR_READ,"IpcFile can't open %s",
				 fullFilename);
		}
	    else 
		{
		if (fread(fbuf,1,fsize,pInfile) == (unsigned) fsize)
	            {
		    fclose(pInfile);
		    doLevel1Tracing("IpcFile::processFile Receive "
				    "%s {%s}",czFileName,fbuf);
		    parseRemainder(fbuf);
		    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
			logTrace("IpcFile::processFile parsed %s",fbuf);
		    }
		else if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
		    logError(IPC_ERROR_READ,"IpcFile can't read %s",
				 fullFilename);
		}
	    free(fbuf);
	    }
	else
	    Logger::logError(IPC_ERROR_MEMORY,
			     "IpcFile can't get memory to read %s",
			     fullFilename);
	bComplete = TRUE;
	int unlink_stat = 0;
	if (fileType != PRO_FILE_TYPE)
	    unlink_stat = unlink(fullFilename);
	//Logger::logTrace("IpcFile unlink %s returns %d",
	//		 fullFilename,unlink_stat);
        }
    else
	if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
	    Logger::logTrace("IpcFile::processFile wrong size %s sz=%ld infile=%ld",
			     czFileName,fsize,sizeInFile);
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        Logger::logTrace("%s::processFile (ex) return %d",
			 className(),bComplete);
    return bComplete;
    }

int IpcFile::determineFileType(const char * fname)
    {
    int type = UNKNOWN_FILE_TYPE;

    /* want ptr to node, in case it's prefixed by a path
     * ~~ (ignore the bare drive letter case for the moment)
     */
    const char * pbNode = strrchr(fname,'\\');
    const char * pfNode = strrchr(fname,'/');
    const char * pNode = (pbNode > pfNode) ? pbNode+1 
      : (pfNode != NULL) ? pfNode+1 : fname; 
    char * buf = strupr(strdup(pNode));
    if (buf != NULL)
        {
	if (strncmp(buf,"CMD",3) == 0)
	    type = CMD_FILE_TYPE;
	else if (strncmp(buf,"RPY",3) == 0)
	    type = RPY_FILE_TYPE;
	else if (strncmp(buf,"NAK",3) == 0)
	    type = NAK_FILE_TYPE;
	else if (strncmp(buf,"MSG",3) == 0)
	    type = MSG_FILE_TYPE;
	else if (strncmp(buf,"PRO",3) == 0)
	    type = PRO_FILE_TYPE;
	else if (strncmp(buf,"QRY",3) == 0)
	    type = QRY_FILE_TYPE;
	else if (strncmp(buf,"DAT",3) == 0)
	    type = DAT_FILE_TYPE;
	else
	    Logger::logError(IPC_ERROR_UNKNOWNTYPE,
			     "IpcFile unknown filetype %s",fname);
	free(buf);
	}
    else
        Logger::logError(IPC_ERROR_MEMORY,
			     "IpcFile can't get memory to read %s", fname);
    return type;
    }

int IpcFile::parseHeader(const char * fullFileName)
    {
    FILE* pInfile = NULL;
    int size = -1;
    long fsize = file_size(fullFileName);
    char * fbuf = (char *)malloc(fsize+1);
    if (fbuf != NULL)
        {
	memset(fbuf,0,fsize+1);
	pInfile = fopen(fullFileName, "rb");
	if (pInfile == NULL)
	   {
	   Logger::logError(IPC_ERROR_READ,"IpcFile can't open %s",
				 fullFileName);
	   }
	else
	   {
   	   if (fread(fbuf,1,(ushort)fsize,pInfile) == (ushort) fsize)
	       {
	       fclose(pInfile);
	       char * pFirst = strtok(fbuf," \r\n");  /* the '(' */
	       char * pSecond = strtok(NULL," \r\n"); /* the timestamp */
	       char * pThird = strtok(NULL," \r\n");  /* the size */
	       if (pFirst != NULL); /* get rid of warning */
	       if (pSecond != NULL)
		   timeStamp = atol(pSecond);
	       if (pThird != NULL)
		   size = atoi(pThird);
	       }
	   else
	       {
	       Logger::logError(IPC_ERROR_READ,"IpcFile can't read %s",
			    fullFileName);
	       }
	   }
	free(fbuf);
	}
    else
        Logger::logError(IPC_ERROR_MEMORY,
			     "IpcFile can't get memory to read %s",
			     fullFileName);
    //        doError("Can't get memory to read ",IPC_ERROR_MEMORY);
    return size;
    }

#if DRAGON_VER >= 6
// static function which uses much of parseHeader() to get
// the intended size and compare it to the actual size on the disk
// Once called this will block, so the caller should be sure
// that the desired file already exists
// @param fullFileName	path and name of desired file
void IpcFile::waitReady(const char * fullFileName)
    {
    while(1)
	{
        int size = -1;
        long fsize = file_size(fullFileName);
	if (fsize > 0)
	    {
	    char * fbuf = (char *)calloc(fsize+1,1);
	    if (fbuf != NULL)
	        {
		FILE * pInfile = fopen(fullFileName, "rb");
		if (pInfile == NULL)
		    {
		    Logger::logError(IPC_ERROR_READ,"IpcFile can't open %s",
				     fullFileName);
		    }
		else
		    {
		    if (fread(fbuf,1,(ushort)fsize,pInfile) == (ushort) fsize)
		        {
			fclose(pInfile);
			char * pTok = strtok(fbuf," \r\n");  /* the '(' */
			pTok = strtok(NULL," \r\n"); /* the timestamp */
			pTok = strtok(NULL," \r\n");  /* the size */
			if (pTok != NULL)
			    size = atoi(pTok);
			}
		    else
		        {
			Logger::logError(IPC_ERROR_READ,"IpcFile can't read %s",
					 fullFileName);
			}
		    }
		free(fbuf);
		}
	    else
		Logger::logError(IPC_ERROR_MEMORY,
				 "IpcFile can't get memory to read %s",
				 fullFileName);
	    //        doError("Can't get memory to read ",IPC_ERROR_MEMORY);
	    }
	if (size == fsize)
	    break;
	}
    }

/* STATIC fn to get the name of the style */
const char * IpcFile::getIpcStyleName(IPC_STYLE_t uStyle)
    {
    static const char * czStyleNames[] = {IPC_STYLE_NAMES};
    return ((uint)uStyle < AY_COUNT(czStyleNames))
	? czStyleNames[uStyle] : "Unknown";
    }
#endif

//#if defined _WIN32 || defined __ZTC__ //~~ system() not available in win16
/** delete any IPC files which match pattern
 *  @param czPattern    OS-dependent wildcard pattern or NULL
 *                      node-name only - no path or extension
 *  @param czExtension  explicit extension or NULL
 *			(if NULL, deletes $*)
 */

#ifdef NOMORE
void IpcFile::clean(const char * czPattern, const char * czExtension)
    {
    char cmdbuf[PATH_MAX];
    const char * kpath = getKpath();
    //~~ 2> is for NT
    sprintf(cmdbuf,"del /Q %s\\%s.%s 2> NUL",(const char *)kpath,
	    (czPattern != NULL) ? czPattern : "*",
	    (czExtension != NULL) ? czExtension : "$*");
    system(cmdbuf);
//    if (Logger::getTraceLevel() > 1)
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        Logger::logTrace("IpcFile::clean executed %s",cmdbuf);
    }
#endif

void IpcFile::clean(const char * czPattern, const char * czExtension)
    {
    char cmdbuf[PATH_MAX];
    const char * kpath = getKpath();
#ifdef __GCC__
    sprintf(cmdbuf,"%s/%s.%s",(const char *)kpath,
	    (czPattern != NULL) ? czPattern : "*",
	    (czExtension != NULL) ? czExtension : "\\$*");
#else
    sprintf(cmdbuf,"%s\\%s.%s",(const char *)kpath,
	    (czPattern != NULL) ? czPattern : "*",
	    (czExtension != NULL) ? czExtension : "$*");
#endif
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
	Logger::logTrace("ipcFile::clean (en) deleting %s",cmdbuf);
    struct _find_t * ff = find_first(cmdbuf,0);
    while (ff != NULL)
        {
	sprintf(cmdbuf,"%s/%s",kpath,ff->name);
	if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
	    Logger::logTrace("ipcFile::clean found '%s' deleting '%s' ",
			     ff->name, cmdbuf);
	unlink(cmdbuf);
	ff = find_next();
	}

    find_free();
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
        Logger::logTrace("IpcFile::clean executed %s",cmdbuf);
    }

//#endif

BOOL IpcFile::isComplete()
    {
    if (!bComplete)
        bComplete = processFile();
    return bComplete;
    }

const char * IpcFile::getSourceModule()
    {
    return czSourceModule;
    }

int IpcFile::getFileType()
    {
    return fileType;
    }

time_t IpcFile::getTimeStamp()
    {
    return timeStamp;
    }

const char * IpcFile::getFileName() { return czFileName; }

int IpcFile::getSizeInFile()
    {
    return sizeInFile;
    }

/* this does the required Level 1 tracing 
 * STATIC fn
 * the file contents have '\r' replaced by ' ', '\n' by ';' */
void IpcFile::doLevel1Tracing(const char * format, const char * fileName,
			      char * pczMessage)
    {
    char * buf = pczMessage; //strdup(pczMessage);
    while(strchr(" \r\n\x1A",buf[strlen(buf)-1]) != NULL)
        buf[strlen(buf)-1] = '\0'; // get rid of trailing cr,lf,bl
	//	while((pChr = strchr(buf,'\n')) != NULL)
	//    *pChr = ';';
	//while((pChr = strchr(buf,'\r')) != NULL)
	//    *pChr = ' ';
    const char * pUnixNodeName = strrchr(fileName,'/'); 
    const char * pDosNodeName = strrchr(fileName,'\\'); 
    const char * pNodeName 
	  = (pUnixNodeName > pDosNodeName) ? pUnixNodeName+1
	     : (pDosNodeName > fileName) ? pDosNodeName+1 : fileName;
    if (Logger::getTraceLevel() & TRACE_LVL_IPCFile)
	Logger::logTrace(format,pNodeName,buf);
    }

void IpcFile::doError(const char * pczMessage, const int iCode)
    {
    Logger::logError(iCode,"IpcFile %s %s",pczMessage,czFileName);
    }

void IPCFILE_END() { puts(FIL_ID); }
