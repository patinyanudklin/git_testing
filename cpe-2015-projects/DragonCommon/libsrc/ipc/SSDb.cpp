extern "C" {
#include "drelease.h"
char SS_DB_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.73 $$Date: 2014/12/29 03:30:57 $";
D_REL_IDSTR;
}
/*
 *	filename SSDb.cpp
 *		$Revision: 1.73 $ $Date: 2014/12/29 03:30:57 $	
 *
 *      ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 ********************************************************************
 * $Id: SSDb.cpp,v 1.73 2014/12/29 03:30:57 rudahl Exp $
 * $Log: SSDb.cpp,v $
 * Revision 1.73  2014/12/29 03:30:57  rudahl
 * convert to using dragon version number
 *
 * Revision 1.72  2014/12/10 11:09:53  rudahl
 * zap internet use
 *
 * Revision 1.71  2014/12/07 08:25:47  rudahl
 * adapt to OpenDragon
 *
 * Revision 1.70  2014/01/31 04:07:25  rudahl
 * revised to support NOKEY timeouts
 *
 * Revision 1.69  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.68  2012/06/02 11:04:56  rudahl
 * fix for Windows 7
 *
 * Revision 1.67  2012/05/30 09:24:45  rudahl
 * working on the web licensing
 *
 * Revision 1.66  2012/05/13 13:46:35  rudahl
 * adapt setup to win7 - add ask.exe
 *
 * Revision 1.65  2012/05/13 10:10:01  rudahl
 * minor improved tyracing
 *
 * Revision 1.64  2012/05/06 11:45:24  rudahl
 * fix write and read BITS for eval
 *
 * Revision 1.63  2012/05/02 11:40:27  rudahl
 * implemented WEBSGL enforcement
 *
 * Revision 1.62  2012/04/15 04:40:39  rudahl
 * support internet licensing
 *
 * Revision 1.61  2012/02/28 02:07:06  rudahl
 * working on unique machine code
 *
 * Revision 1.60  2012/01/30 10:11:06  rudahl
 * working on internet licensing
 *
 * Revision 1.59  2011/12/13 08:41:17  rudahl
 * restored calcmachinecode in test
 *
 * Revision 1.58  2010/11/14 19:33:10  rudahl
 * added creation of DROF EVAL version
 *
 * Revision 1.57  2008/10/14 08:40:21  rudahl
 * documentation
 *
 * Revision 1.56  2008/10/09 05:38:22  rudahl
 * minor fixes for Vista64
 *
 * Revision 1.55  2008/04/24 06:20:24  rudahl
 * get rid of setpersist in server
 *
 * Revision 1.54  2007/09/30 09:10:42  rudahl
 * fixul VDecorate table
 *
 * Revision 1.53  2007/08/12 04:08:44  rudahl
 * completed adaptations for cgDb
 *
 * Revision 1.52  2007/08/11 09:30:13  rudahl
 * improve getFile, get,putVCurrent
 *
 * Revision 1.51  2007/08/10 10:42:05  rudahl
 * added getFile
 *
 * Revision 1.50  2007/08/09 02:01:58  rudahl
 * add fns to access VCurrent table
 *
 * Revision 1.49  2007/06/23 13:03:58  rudahl
 * fix system registration for 5.10.5
 *
 * Revision 1.48  2007/06/19 05:52:00  rudahl
 * fine-tuning the KEYREQ
 *
 * Revision 1.47  2007/06/17 10:41:35  rudahl
 * fine-tuning on install DB and Hasp key stuff
 *
 * Revision 1.46  2007/05/31 09:43:20  rudahl
 * moved SSDb to ipc
 *
 * Revision 1.45  2007/05/30 14:55:42  rudahl
 * adapt to setup initializing DB
 *
 * Revision 1.44  2007/03/23 10:52:02  goldin
 * lint
 *
 * Revision 1.43  2007/01/07 06:28:41  rudahl
 * problem with setting DB CURRENT/M clear
 *
 * Revision 1.42  2006/04/24 07:18:12  rudahl
 * prevent changing some .CFG-set fields
 *
 * Revision 1.41  2006/04/09 11:12:07  rudahl
 * require registration within 15 days; fix bugs
 *
 * Revision 1.40  2006/03/01 04:32:44  rudahl
 * got rid of extra printout line
 *
 * Revision 1.39  2006/02/26 11:52:09  rudahl
 * working on registration
 *
 * Revision 1.38  2006/02/24 06:44:40  rudahl
 * improved tracing
 *
 * Revision 1.37  2006/02/19 12:31:10  rudahl
 * working on registration
 *
 * Revision 1.36  2006/02/13 11:43:48  rudahl
 * typoe
 *
 * Revision 1.35  2006/02/13 11:29:38  rudahl
 * improved tracing
 *
 * Revision 1.34  2006/02/12 08:48:24  rudahl
 * fix problem with no status report on FIL
 *
 * Revision 1.33  2006/02/11 09:31:59  rudahl
 * improved tracing
 *
 * Revision 1.32  2006/01/26 06:57:26  rudahl
 * added schema version
 *
 * Revision 1.31  2006/01/24 05:15:15  rudahl
 * added argVal to CURRENT
 *
 * Revision 1.30  2006/01/20 12:42:29  rudahl
 * lint and purges
 *
 * Revision 1.29  2006/01/20 09:01:33  rudahl
 * improved docs
 *
 * Revision 1.28  2006/01/14 11:48:48  rudahl
 * working on scripting
 *
 * Revision 1.27  2006/01/13 14:39:42  rudahl
 * major reworking of tracing; refactoring of eventLoop;. polling
 *
 * Revision 1.26  2005/12/27 11:09:36  rudahl
 * cleanup output of getProfile
 *
 * Revision 1.25  2005/12/24 04:44:39  rudahl
 * extra defenses against string garbage
 *
 * Revision 1.24  2005/12/10 11:47:56  rudahl
 * purge PATHS, FILES on startup
 *
 * Revision 1.23  2005/12/04 11:17:34  rudahl
 * made dumpTables more selective
 *
 * Revision 1.22  2005/11/26 05:15:11  rudahl
 * fixes for Win build
 *
 * Revision 1.21  2005/11/25 12:35:11  rudahl
 * added DB use to chq
 *
 * Revision 1.20  2005/11/24 09:19:28  rudahl
 * added SCRIPTVARS; modified CHECKSUMS; improved debug info
 *
 * Revision 1.19  2005/11/24 08:18:00  rudahl
 * create a utility version of SSDb
 *
 * Revision 1.18  2005/11/22 04:58:58  rudahl
 * use symbol for dragon.cfg filename
 *
 * Revision 1.17  2005/11/19 05:04:30  rudahl
 * fixed getCurrent for =R,G,B: zap trailing blank
 *
 * Revision 1.16  2005/11/05 13:05:02  goldin
 * Work on replacing =M and =C with correct persistent data
 *
 * Revision 1.15  2005/11/05 09:55:40  rudahl
 * replaced the Parameter class by DB use
 *
 * Revision 1.14  2005/11/04 10:51:05  goldin
 * Working on correcting the queries for status returns
 *
 * Revision 1.13  2005/11/04 06:42:49  rudahl
 * added more support for opKey in status report
 *
 * Revision 1.12  2005/11/04 05:26:07  rudahl
 * added supooprt for opKey in status report
 *
 * Revision 1.11  2005/10/22 04:25:01  rudahl
 * improved getCurrent; added getFiles
 *
 * Revision 1.10  2005/10/21 11:36:39  rudahl
 * fixed bug in getpersist
 *
 * Revision 1.9  2005/10/21 11:12:59  rudahl
 * fixed bug in getpersist
 *
 * Revision 1.8  2005/10/21 11:01:39  rudahl
 * augmented getpersist STATUS report
 *
 * Revision 1.7  2005/10/02 08:13:01  rudahl
 * working on persistent data
 *
 * Revision 1.6  2005/10/01 11:11:56  rudahl
 * adding persistent storage to Ipc and SS
 *
 * Revision 1.5  2005/09/27 03:23:18  rudahl
 * some bad declarations
 *
 * Revision 1.4  2005/09/27 03:11:42  rudahl
 * integrating SSDb into Executable
 *
 * Revision 1.3  2005/09/25 12:43:10  rudahl
 * working on persistent data
 *
 * Revision 1.2  2005/09/24 14:19:59  rudahl
 * got SSDb to work up to putting CURRENT
 *
 * Revision 1.1  2005/09/23 01:19:26  rudahl
 * initial from moochie, for Dragon Prof
 *
 *
 ********************************************************************
 *   Maintain a database for status and other persistent info
 *
 * The methods in this class are specific to the needs of Dragon,
 * and are not at all a generic or orthogonal set of relational DB 
 * functions.
 *
 * class SSDb is a base class for use with different DB systems
 * class SSDbSqlite is the subclass for SQLite.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.7 	2005-9-19 ktr	new
 *	2005-11-24 ktr	added create()
 *	2006-1-7 ktr	rev. getCurrent semantics: returns NULL if not found
 *	2006-1-14 ktr	putCurrent now enforces value include a path
 *	2006-1-20 ktr	setpersist for which==0 value=NULL means reset
 *			to orginal value
 *	2006-1-23 ktr	added argVal to CURRENT for VP & script variables
 *			added iWhich=3,4 to putCurrent 
 * 6.1	2010-11-14 ktr	added queryExpirationDay
 * 6.2	2012-05-01 ktr	added queryExpiration
 * 6.3	2012-12-27 ktr	added IPC to Profile table and .cfg
 ********************************************************************
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>  // for toupper
#ifdef __GCC__
#define _snprintf snprintf
#define _vsnprintf vsnprintf
#include <glob.h>
#include <netinet/ether.h>
#else
#include <windows.h>
//#include <process.h>
//#include <winsock2.h>
#define strcasecmp(a,b) stricmp(a,b)
#endif
#include <openssl/sha.h> // SHA1

#include "sqlite3.h"

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"

#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dp.h"

// following needed for 'whichtable()'
#include "IpcFile.h"
#include "IpcWatcher.h"
#include "IpcReceiveWatcher.h"
#include "IpcCmdWatcher.h"

//#include "ScriptServer.h"
#include "SSDb.h"

static int iDbRecCount = 0;	/* count of records matching query */
static int iDbSize = 0;		/* buffer size req. for ALL matching records */
static int iOID = 0;
static int uDbFieldCount = 0;	/* gets set by each callback 
				 * to number of fields in retrieved record */
static char czOutbuf[2048];	/* mostly for getCurrent() */

/* Count records retrieved from DB
 * this fn is executed once for each row of the query fn.
 * @return 0 unless error
 */
static int ss_count(void *NotUsed, int argc, char **argv, char **azColName)
    {
    iDbRecCount++;
    uDbFieldCount = argc;
    return 0;
    }

/* Count records retrieved from DB, and return the OID of the first
 * record into iOID.
 * Actually this just converts the first column returned, which is
 * assumed to be numeric.
 * This fn is executed once for each row of the query fn.
 * @return 0 unless error
 */
static int ss_OIDCallback(void *NotUsed, int argc, 
			  char **argv, char **azColName)
    {
    if (iDbRecCount == 0)
	sscanf(argv[0],"%d",&iOID);
    iDbRecCount++;
    uDbFieldCount = argc;
    return 0;
    }

/* Format record as attribute=value; pairs
 * this fn is executed once for each row of the query fn.
 * @param pczBuf	if non-NULL, put resulting data there
 *			assume big enough
 * @param argc		count of argv, azColName
 * @param argv		array of value strings
 * @param azColName	array of column name strings
 * @return 0 unless error
 */
static int ss_AttrValCallback(void *pczBuf, int argc, 
			      char **argv, char **azColName)
    {
    int i;
    char czDbRecord[256];	/* one record retrieved from DB */
    memset(czDbRecord,'\0',sizeof(czDbRecord));
//    fprintf(stderr,"AttrValCallBack rec %d has %d args\n",iDbRecCount,argc);
//    logTrace("SSDb::AttrValCallBack retrieved record %d has %d args buf=%p=%s",
//	iDbRecCount,argc,pczBuf,NN(pczBuf));
    for(i=0; i < argc; i++)
        {
	if (argv[i] == NULL)
	    continue;
	strcat_array(czDbRecord,azColName[i]);
	strcat_array(czDbRecord,"=");
	strcat_array(czDbRecord,argv[i]);
	strcat_array(czDbRecord,";");
//	logTrace("SSDb::AttrValCallBack arg %d named '%s' val='%s'",
//		i,azColName[i],argv[i]);
//	fprintf(stderr,"AttrValCallBack arg %d named '%s' val='%s' \n",
//		i,azColName[i],argv[i]);
	}
    iDbSize += 1 + strlen(czDbRecord);
    if (pczBuf != NULL)
	strcat((char *)pczBuf,czDbRecord);
    uDbFieldCount = argc;
//    logTrace("SSDb::AttrValCallBack (ex) got |%s|",czDbRecord,pczBuf);
    iDbRecCount++;
    return 0;
    }

/* Format records for Server =C param specs
 * this fn is executed once for each row of the query fn.
 * @param pczBuf	if non-NULL, put resulting data there
 *			assume big enough
 * @param argc		count of argv, azColName
 * @param argv		array of value strings
 * @param azColName	array of column name strings
 * @return 0 unless error
 */
static int ss_RGBCallback(void *pczBuf, int argc, 
			     char **argv, char **azColName)
    {
    int i;
    char czDbRecord[PATH_MAX+10];	/* one record retrieved from DB */
    char name[PATH_MAX];	/* might be a filename or a pathname */
    char path[PATH_MAX];	/* pathname if name is a file */
    char idStr[16];
    memset(czDbRecord,'\0',sizeof(czDbRecord));
    idStr[0] = name[0] = path[0] = '\0';
    for(i=0; i < argc; i++)
        {
	if (argv[i] == NULL)
	    continue;
	if (strcmp(azColName[i],"idStr") == 0)
	    { strcpy_array(idStr,argv[i]); }
	else if (strcmp(azColName[i],"name") == 0)
	    { strcpy_array(name,argv[i]); }
	else if (strcmp(azColName[i],"path") == 0)
	    { strcpy_array(path,argv[i]); }
	}
    snprintf(czDbRecord,sizeof(czDbRecord),
	     " %s \"%s/%s\" \n",
	     (strcmp(idStr,"B") == 0) ? "-FBB"
	     : (strcmp(idStr,"G") == 0) ? "-FGG" : "-FRR",
	     path,name);
    iDbSize += 1 + strlen(czDbRecord);
    if (pczBuf != NULL)
	strcat((char *)pczBuf,czDbRecord);
    uDbFieldCount = argc;
    iDbRecCount++;
    return 0;
    }

/* Format records for Server =C param specs
 * this fn is executed once for each row of the query fn.
 * @param pczBuf	if non-NULL, put resulting data there
 *			assume big enough
 * @param argc		count of argv, azColName
 * @param argv		array of value strings
 * @param azColName	array of column name strings
 * @return 0 unless error
 */
static int ss_FullpathCallback(void *pczBuf, int argc, 
			     char **argv, char **azColName)
    {
    int i;
    char czDbRecord[PATH_MAX+10];	/* one record retrieved from DB */
    char name[PATH_MAX];	/* might be a filename or a pathname */
    char path[PATH_MAX];	/* pathname if name is a file */
    char idStr[16];
    memset(czDbRecord,'\0',sizeof(czDbRecord));
    idStr[0] = name[0] = path[0] = '\0';
    for(i=0; i < argc; i++)
        {
	if (argv[i] == NULL)
	    continue;
	if (strcmp(azColName[i],"idStr") == 0)
	    { strcpy_array(idStr,argv[i]); }
	else if (strcmp(azColName[i],"name") == 0)
	    { strcpy_array(name,argv[i]); }
	else if (strcmp(azColName[i],"path") == 0)
	    { strcpy_array(path,argv[i]); }
	}
    snprintf(czDbRecord,sizeof(czDbRecord),
	     "%s/%s",path,name);
    iDbSize += 1 + strlen(czDbRecord);
    if (pczBuf != NULL)
	strcat((char *)pczBuf,czDbRecord);
    uDbFieldCount = argc;
    iDbRecCount++;
    return 0;
    }

/* Format records suitable for UI status report
 * this fn is executed once for each row of the query fn.
 * @param pczBuf	if non-NULL, put resulting data there
 *			assume big enough.
 *			However, if it == czOutbuf 
 *			use sizeof(czOutbuf) to verify
 * @param argc		count of argv, azColName
 * @param argv		array of value strings
 * @param azColName	array of column name strings
 * @return 0 unless error
 */
static int ss_UIStatusCallback(void *pczBuf, int argc, 
			       char **argv, char **azColName)
    {
    int i;
    char czDbRecord[PATH_MAX];	/* one record retrieved from DB */
    char name[PATH_MAX];	/* might be a filename or a pathname */
    char path[PATH_MAX];	/* pathname if name is a file */
    char opKey[16];
    char idStr[16];
    int lines=0,pix=0;
    memset(czDbRecord,'\0',sizeof(czDbRecord));
    name[0] = path[0] = idStr[0] = opKey[0] = '\0';
    for(i=0; i < argc; i++)
        {
	if (argv[i] == NULL)
	    continue;
	if (strcmp(azColName[i],"idStr") == 0)
	    { strcpy_array(idStr,argv[i]); }
	else if (strcmp(azColName[i],"name") == 0)
	    { strcpy_array(name,argv[i]); }
	else if (strcmp(azColName[i],"path") == 0)
	    { strcpy_array(path,argv[i]); }
	else if (strcmp(azColName[i],"opKey") == 0)
	    { strcpy_array(opKey,argv[i]); }
	else if (strcmp(azColName[i],"pixels") == 0)
	    pix = atoi(argv[i]);
	else if (strcmp(azColName[i],"lines") == 0)
	    lines = atoi(argv[i]);
	}
    if (strlen(idStr) == 1) // this used to have a MFileType also
        {
	if (strlen(opKey) > 0)
	    snprintf(czDbRecord,sizeof(czDbRecord),
		     "%sFile==M\n%sOp=%s\n%sLines=%d\n%sPixels=%d\n",
		     idStr,idStr,opKey,idStr,lines,idStr,pix);
	else
	    snprintf(czDbRecord,sizeof(czDbRecord),
		     "%sFile=%s\n%sPath=%s\n%sLines=%d\n%sPixels=%d\n",
		     idStr,name,idStr,path,idStr,lines,idStr,pix);
	}
    else if ((strlen(idStr) > 1) && (strcmp(&idStr[1],"PATH") == 0))
	snprintf(czDbRecord,sizeof(czDbRecord),
		 "%s=%s\n",idStr,path);
    else if (strlen(idStr) == 0)	// must be dpath
	snprintf(czDbRecord,sizeof(czDbRecord),
		 "DPATH=%s\n",path);
    else       // for any other path and file, just name=value
	snprintf(czDbRecord,sizeof(czDbRecord),
		 "%sFile=%s\n%sPath=%s\n",idStr,name,idStr,path);
    iDbSize += 1 + strlen(czDbRecord);
    if (pczBuf != NULL)
        { /* normally will use czOutbuf else calloc'd string */
	if ((pczBuf != czOutbuf) 
	    || ((strlen((char *)pczBuf)+strlen(czDbRecord)+1) < sizeof(czOutbuf)))
	    strcat((char *)pczBuf,czDbRecord);
	}
    uDbFieldCount = argc;
    iDbRecCount++;
    return 0;
    }

#define MAX_FIELDS 12 // > largest number of fields per table 
typedef struct { int width[MAX_FIELDS]; } FIELDWIDTHS_T;

// print field sizes for tables. Must match in sequence.
// This is initially used by dumpTables(); 
// Does not include space for enclosing blanks, etc
#define FIELD_WIDTHS \
	{4,8,5,10,64,32} ,	/* TRACING */ \
	{4,16,16,24} ,		/* LEGALVALS */ \
	{30,10,30} ,		/* SCRIPTVARS */ \
	{4,12,16,32} ,		/* profile */ \
	{4,16,20} ,		/* history */ \
	{4,32,16,16} ,		/* checksums */ \
	{4,48,8,2} ,		/* paths */ \
	{4,32,4} ,		/* files */ \
	{3,9,10,6,6,6,5,1,8} ,	/* current */ \
	{3,20,3,40} ,		/* VCurrent */ \
        {3,16,3,3,3,3,15,3,3,16,32}	/* VDecorations */

static const FIELDWIDTHS_T s_iFieldwidths[] = { FIELD_WIDTHS } ;
static uint uDbTableNo;

/* Format record as a table
 * this fn is executed once for each row of the query fn.
 * @param pczBuf	if non-NULL, put resulting data there
 *			assume big enough
 * @param argc		count of argv, azColName
 * @param argv		array of value strings
 * @param azColName	array of column name strings
 * @return 0 unless error
 */
static int ss_TableCallback(void *pczBuf, int argc, 
			      char **argv, char **azColName)
    {
    int i;
    char czDbVal[256];
    char czDbRecord[256];	/* one record retrieved from DB */
    memset(czDbRecord,'\0',sizeof(czDbRecord));
    if (iDbRecCount == 0)
        {
	for(i=0; i < argc; i++)
            {
	    int uColWidth = s_iFieldwidths[uDbTableNo].width[i];
	    snprintf(czDbVal,sizeof(czDbVal)," %-*s |",uColWidth,azColName[i]);
	    strcat_array(czDbRecord,czDbVal);
	    }
	strcat_array(czDbRecord,"\n");
	iDbSize += 1+strlen(czDbRecord);
	if (pczBuf != NULL)
	    strcat((char *)pczBuf,czDbRecord);
	memset(czDbRecord,'\0',sizeof(czDbRecord));
	memset(czDbRecord,'-',iDbSize-1);
	strcat_array(czDbRecord,"\n");
	iDbSize += 1+strlen(czDbRecord); // 1+ allows for DOS \n\r
	if (pczBuf != NULL)
	    strcat((char *)pczBuf,czDbRecord);
	}
    memset(czDbRecord,'\0',sizeof(czDbRecord));
    for(i=0; i < argc; i++)
        {
	int uColWidth = s_iFieldwidths[uDbTableNo].width[i];
	snprintf(czDbVal,sizeof(czDbVal)," %-*s |",uColWidth,
		 (argv[i] != NULL) ? argv[i] : "");
	strcat_array(czDbRecord,czDbVal);
	}
    czDbRecord[strlen(czDbRecord)-1] = '\0';        // trim extra '|' at end
    while (czDbRecord[strlen(czDbRecord)-1] == ' ') // then trim whitespace at end
	czDbRecord[strlen(czDbRecord)-1] = '\0';
    strcat_array(czDbRecord,"\n");
    iDbSize += 1+strlen(czDbRecord);
    if (pczBuf != NULL)
	strcat((char *)pczBuf,czDbRecord);
    iDbRecCount++;
    uDbFieldCount = argc;
    return 0;
    }

Class SSDb::s_class_Base("SSDb","Base class to maintain a database");

Class SSDbSqlite::s_class_Base("SSDbSqlite",
			       "Class to maintain a sqlite database");

char * SSDb::s_czSignatureFields[] // which fields included in Signature
=   { 	"InstallDate",
	"InstallTime",
	"OsVersion",
	"ProcessorBits",
	"ExpireDate",
	"ExpireTime",
	"LicenseType",
	"SN",
	"Machine",
	"ValCode",
	"SPATH",
	"UPATH",
	"ValDate",
	"ProductLevel", /* current effective level not higher than SN[7] */ 
	"Bits",
	"WORKING_LINES",
	"WORKING_PIXELS",
	"WORKING_IMAGES"
    };

#ifdef NOT_HERE // keep list here for ref.
#define SCHEMA_VERSION "1.2"

// tables which need to exist in the DB
// This list is defined in SSDb.h
#define TABLE_LIST \
	"TRACING",	/* only if m_iTrace */ \
	"LEGALVALS",	/* limit permitted strings in some fields */ \
	"SCRIPTVARS", 	/* variables; for scripts, mostly */ \
	"PROFILE",	/* replace PrivateProfile, .cfg */ \
	"HISTORY",	/* prior system runs */ \
	"CHECKSUMS",	/* of the system components */ \
	"PATHS", \
	"FILES", \
	"CURRENT"	/* =M, etc */
	"VDecorations"	/* viewport decorations */ 
//	"VirtualSchema"	/* schema for virtual data */ 
//	"VirtualIntData"     /* data spec'd by user; maybe several tables */ 
//	"VirtualStringData"  /* data spec'd by user; maybe several tables */ 
#endif

const char * SSDb::s_czTables[] = { TABLE_LIST };
const char * SSDb::s_czTableFields[] = { FIELD_LIST };
//const int SSDb::s_iFieldwidths[] = { FIELD_WIDTHS } ;
const char * SSDb::s_czLegalValues[] = { LEGALVALS };
const char * SSDb::s_czCurrentEntries[] = { CURRENT_ENTRIES };
const char * SSDb::s_czZapRows[] = { ZAP_ROWS };

	// simply create an object and set properties to default
	// @param iDebug	debug level if > than set by OB::OB
	// @param iTrace	trace level if > than set by OB::OB
SSDb::SSDb(int iDebug,int iTrace) 
    {
    if (iTrace || m_iTrace)
        {
	Logger::logTrace("SSDb::SSDb (en)");
//	Logger::setTraceLevel(TRACE_LVL_SSDb);
	}
    if (iDebug || m_iDebug)
	fprintf(stderr,"SSDb::SSDb (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
//    czDbRecord[0] = '\0';
    }

	// Setup the legal values table.
	// This table is probably never subsequently modified
	// This is a protected function
	// @return 		0 if OK
int SSDb::_setLegalValues()
    {
    int iRetval = 0;
    const char * pOld = getProfileString("db","schemaVersion",NULL,NULL);
    if (pOld != NULL) 
	return 0;     // they're already set - don't change them    
    for (uint j=0; j<AY_COUNT(s_czLegalValues); j++)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "insert into LEGALVALS (dbtable,field,string) values (%s);",
		 s_czLegalValues[j]);
	if (((iRetval = sqlQuery(m_czSqlCmd,DB_TEST)) != 0)
		&& (iRetval != SQLITE_CONSTRAINT))
	    {
	    char * pErrmsg = errmsg("LEGALVALS:");
	    logTrace("SSDb::_setLegalValues error %d '%s' not inserted to %s",
			 iRetval,s_czLegalValues[j],pErrmsg);
	    if (m_iDebug)
		printf("SSDb::_setLegalValues error %d '%s' not inserted to %s\n",
		       iRetval,s_czLegalValues[j],pErrmsg);
	    free(pErrmsg);
	    iRetval = DERR_DB_SQL;
	    break;
	    }
	}
    return iRetval;
    }

	// Setup the db fields of profile.
	// This is never subsequently modified
	// This is a protected function
	// @return 		0 if OK
int SSDb::_setDbSchemaValues()
    {
    char buf[21];
    const char * pOld = getProfileString("db","schemaVersion",NULL,NULL);
    if (pOld != NULL) 
        return 0;     // they're already set - don't change them    
    int iRetval = putProfileString("db","schemaVersion",SCHEMA_VERSION);
    calcTimeStamp(buf,sizeof(buf));
    iRetval = putProfileString("db","created",buf);
    return iRetval;
    }

	// Setup the Current table, which can contain only predefined entries
	// This table is probably never subsequently modified
	// This is a protected function
	// @return 		0 if OK
int SSDb::_setCurrentEntries()
    {
    int iRetval = 0;
    for (uint j=0; j<AY_COUNT(s_czCurrentEntries); j++)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "insert into CURRENT (idstr,scriptName) values (%s);",
		 s_czCurrentEntries[j]);
	if (((iRetval = sqlQuery(m_czSqlCmd,DB_TEST)) != 0)
		&& (iRetval != SQLITE_CONSTRAINT))
	    {
	    char * pErrmsg = errmsg("CURRENT");
	    logTrace("SSDb::_setCurrentEntries error %d '%s' not inserted to %s",
		     iRetval,s_czCurrentEntries[j],pErrmsg);
	    if (m_iDebug)
		printf("SSDb::_setCurrentEntries error %d '%s' not inserted to %s\n",
		       iRetval,s_czCurrentEntries[j],pErrmsg);
	    free(pErrmsg);
	    iRetval = DERR_DB_SQL;
	    break;
	    }
	else
	    iRetval = 0;
	}
    return iRetval;
    }

	// Open the DB if it exists, create it if it doesn't exist
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// Do nothing which is site. product, or situation dependent
	// In other words, this is NOT a validation step.
	// @param bPreserve	if TRUE, do nothing except open the DB
	// @return 		0 if OK
int SSDb::init(BOOL bPreserve)
    {
    int iRetval = 0;
    uint j;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDb::init (en) preserve? %s",YESNO(bPreserve));
    if (m_iDebug)
	printf("SSDb::init (en)\n");
    if (bPreserve)
	return iRetval;
    for (j=0; j<AY_COUNT(s_czTables); j++)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select * from %s limit 1;",s_czTables[j]);
	if (sqlQuery(m_czSqlCmd,DB_TEST))
	    {
	    logTrace("table %s not found; creating it",s_czTables[j]);
	    if (m_iDebug)
		fprintf(stderr,
			"table %s not found; creating it\n",s_czTables[j]);
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),"create table %s (%s);",
		     s_czTables[j],s_czTableFields[j]);
	    if ((iRetval = sqlQuery(m_czSqlCmd)) > SQLITE_ERROR)
	        {
		char * pErrmsg = errmsg("");
		logTrace("SSDb::init error %d creating table %s: %s",
			 iRetval,s_czTables[j],pErrmsg);
		if (m_iDebug)
		    fprintf(stderr,
			    "SSDb::init error %d creating table %s: %s\n",
		       iRetval,s_czTables[j],pErrmsg);
		free(pErrmsg);
		iRetval = DERR_DB_SQL;
		break;
		}
	    else  // returns SQLITE_ERROR on creation; why?
		iRetval = 0;
	    }
	else  // not found, but that's OK
	    iRetval = 0;
	}
    for (j=0; j<AY_COUNT(s_czZapRows); j += 2)
        {
	if (iRetval != 0)
	    break;
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "delete from %s %s %s;",s_czZapRows[j],
		 (strlen(s_czZapRows[j+1]) > 0) ? "where " : "",
		 (strlen(s_czZapRows[j+1]) > 0) ? s_czZapRows[j+1] : "");
	if (((iRetval = sqlQuery(m_czSqlCmd,DB_TEST)) != 0)
	        && (iRetval != SQLITE_ERROR)) // nothing found
	    {
	    char * pErrmsg = errmsg("");
	    logTrace("SSDb::init error %d entry '%s' "
		     "not deleted from %s: %s",
		     iRetval,s_czZapRows[j+1],s_czZapRows[j],pErrmsg);
	    if (m_iDebug)
		printf("SSDb::init error %d entry '%s' "
		       "not deleted from %s: %s\n",
		       iRetval,s_czZapRows[j+1],s_czZapRows[j],pErrmsg);
	    free(pErrmsg);
	    iRetval = DERR_DB_SQL;
	    break;
	    }
	else
	    iRetval = 0;
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDb::init (mid) iRetval=%d",iRetval);
    if (iRetval == 0)
	iRetval = _setLegalValues();
    if (iRetval == 0)
	iRetval = _setDbSchemaValues();
    if (iRetval == 0)
	iRetval = _setCurrentEntries();
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDb::init (ex) returning %d",iRetval);
    return iRetval;
    }

#if defined UTIL  // currently only used for the utility version
	// Create the DB.
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// @return 		0 if OK
int SSDb::create()
    {
    int iRetval = 0;
    uint j;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	//   if (m_iTrace)
	logTrace("SSDb::create (en)");
    if (m_iDebug)
	printf("SSDb::create (en)\n");
    for (j=0; j<AY_COUNT(s_czTables); j++)
        {
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//	if (m_iTrace)
	    logTrace("SSDb::create creating table '%s'",s_czTables[j]);
	if (m_iDebug)
	    fprintf(stderr,"SSDb::create creating table '%s'\n",s_czTables[j]);
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),"create table %s (%s);",
		 s_czTables[j],s_czTableFields[j]);
	if ((iRetval = sqlQuery(m_czSqlCmd)) > 0) // SQLITE_ERROR)
	    {
	    char * pErrmsg = errmsg("");
	    logTrace("SSDb::create error %d creating table %s: %s",
		     iRetval,s_czTables[j],pErrmsg);
//	    if (m_iDebug)
	    fprintf(stderr,
		    "SSDb::create error %d creating table %s: %s\n\n",
		    iRetval,s_czTables[j],pErrmsg);
	    free(pErrmsg);
	    iRetval = DERR_DB_SQL;
	    break;
	    }
	else
	    iRetval = 0;
	}
    if (iRetval == 0)
	iRetval = _setLegalValues();
    if (iRetval == 0)
	iRetval = _setDbSchemaValues();
    if (iRetval == 0)
	iRetval = _setCurrentEntries();
    return iRetval;
    }

#endif // if defined UTIL

	// Load data from .cfg file, plus other locations (s/n, etc)
	// some fields (e.g. Installxxx) cannot be changed once 
	// they are initially set
	// This also (re)sets ProductLevel if it was set to DEMO
	// by a license failure (which also sets DegradedTime to non-zero)
	// This is called (only?) from ScriptServer/SSModel
	// @return		0 if OK
int SSDb::initFromCfg() 
    {
    int iRetval = 0;
    char czBuf[258];
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDb::initFromConfig (en)");
    int iDbLevel = getProductLevel(FALSE); // according to DB 
    int iSnLevel = getProductLevel(TRUE);  // according to SN
	// For license types with a timeout, check current state
	// The checking depends on LicenseType
	//   0 => OK, 1 => not registered but not yet timedout, 2 => timed out 3 => error
    int iExpirationStatus = queryExpiration();
    if (iSnLevel < 0) // verifySignature error
	return -1;
    if ((iDbLevel == 4)                  /* DEMO_PRODUCT */ 
	    && (iSnLevel == 1))          /* ACAD_PRODUCT */
	setProductLevel(1);
    if ((iDbLevel == 4)                  /* DEMO_PRODUCT */ 
	    && (iSnLevel == 9)           /* PROF_PRODUCT */
            && (iExpirationStatus < 2))  /* not yet expired */
	setProductLevel(9);
    FILE * pf = fopen(CFGFILE,"r"); // "dragon.cfg" in dragonOb.h
    const char * pCh = NULL;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
        {
	char * pczDump = dumpTables("initFromCfg (en)\n",0);
	if (pczDump != NULL)
	    {
	    logTrace(pczDump);
	    free(pczDump);
	    }
	}
//    struct ether_addr mac;
//   iRetval = ether_hostton("localhost",&mac);
 //   printf("hostton returns %d\n",iRetval);
    if (pf == NULL)
	iRetval = DERR_FILE_OPEN;
    else
        {
	while (fgets(czBuf,sizeof(czBuf),pf) != NULL) 
	    {
	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
		logTrace("SSDb::initFromCfg line from cfg='%s'",czBuf);
	    char * pFirst = strtok(czBuf,"=");
	    char * pSecond = (pFirst != NULL) ? strtok(NULL,"\r\n\t ;") : NULL;
	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
		logTrace("SSDb::initFromCfg cfg parses to '%s','%s'",
			 pFirst,pSecond);
	    m_czSqlCmd[0] = '\0';
	    if (( // ((pCh = strstr(pFirst,"WORKING_")) != NULL)//?? no longer used
//		      || ((pCh = strstr(pFirst,"BUILDDATE")) != NULL)
		    //   || ((pCh = strstr(pFirst,"SN")) != NULL)
		    //  || ((pCh = strstr(pFirst,"InstallTime")) != NULL)
//		      || ((pCh = strstr(pFirst,"RELEASE")) != NULL)
		       ((pCh = strstr(pFirst,"Key")) != NULL))
		    && (pCh == pFirst)) // beginning of string 
	        {
		const char * pOld = getProfileString("install",pFirst,NULL,NULL);
		if (pOld == NULL)  /* not yet set, so do it */
		    iRetval = putProfileString("install",pFirst,pSecond);
		}
	    //    else if (((pCh = strstr(pFirst,"Installed")) != NULL)
	    //	    && (pCh == pFirst))
	    //   {
	    //	const char * pOld = getProfileString("install","InstallDate",
	    //					     NULL,NULL);
	    //	if (pOld == NULL)  /* not yet set, so do it */
	    //	    iRetval = putProfileString("install","InstallDate",
	    //				       pSecond);
	    //	}
	    else if ((((pCh = strstr(pFirst,"VIEWPORT-")) != NULL)
		      || ((pCh = strstr(pFirst,"DRAGONUI")) != NULL))
		    && (pCh == pFirst))
		iRetval = putProfileString("runtime",pFirst,pSecond);
	    else if (((pCh = strstr(pFirst,"COUNTRY")) != NULL)
		    && (pCh == pFirst))
		iRetval = putProfileString("runtime","LANGUAGE",pSecond);
	    else if (((pCh = strstr(pFirst,"IPC")) != NULL)
		    && (pCh == pFirst))
		iRetval = putProfileString("runtime",pFirst,pSecond);
	    else if (((pCh = strstr(pFirst,"DPATH")) != NULL)
		    && (pCh == pFirst))
		iRetval = putPath(pSecond,"",TRUE);
	    else if (( // ((pCh = strstr(pFirst,"SPATH")) != NULL)
		        ((pCh = strstr(pFirst,"KPATH")) != NULL)
		       || ((pCh = strstr(pFirst,"WPATH")) != NULL))
		     && (pCh == pFirst))
		iRetval = putCurrent(pFirst,2,pSecond);

	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
		logTrace("SSDb::initFromCfg processing '%s' retval=%d",
			 pFirst,iRetval);
	    if (iRetval > 0)  /* putPath, etc, return the OID */
		iRetval = 0;
	    if (iRetval < 0)
		break;
	    }
	fclose(pf);
	}
    if (iRetval < 0)
        {
	char * pErrmsg = errmsg("SSDb::initFromCfg");
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    else
        {
	iRetval = putTracing("SS","init","(ex)",
			     "SSDb::initFromCfg: initial setup of DB");
#ifdef __GCC__   //~~~
	char czNumBuf[20];
	sprintf(czNumBuf,"%d",getpid());
	putProfileString("processId","SS",czNumBuf);
#endif
	putHistory("start");
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
        {
	char * pczDump = dumpTables("initFromCfg (ex)\n",0);
	if (pczDump != NULL)
	    {
	    logTrace(pczDump);
	    free(pczDump);
	    }
	}
    setSignature();
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDb::initFromConfig (ex) returning %d",iRetval);
    return iRetval;
    }

/* generate a time stamp. 
 * @param pczBuf	If is small (< 10) use hh:mm:ss
 *			If large (at least 20) include date
 */
const char * SSDb::calcTimeStamp(char * pczBuf,size_t iBufSize)
    {
    time_t now = time(NULL);
    struct tm * pTime = localtime(&now);
    if (iBufSize < 10)
	strftime(pczBuf,iBufSize,"%H:%M:%S",pTime);
    else
	strftime(pczBuf,iBufSize,"%Y-%m-%d %H:%M:%S",pTime);
    return pczBuf;
    }

/* get the number of matches found in recent query */
//int SSBb::getRecCount() { return iDbRecCount; }

	// put an entry into the TRACING table at current time
	// does not check for already exists, since each is unique
	// @param pczWhich	executable 
	// @param pczWhy	e.g. error, exec, etc
	// @param pczWhat	did they do
	// @param pczWho	class and function name, other info
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
int SSDb::putTracing(const char * pczWhich, 
		     const char * pczWhy,
		     const char * pczWhat, 
		     const char * pczWho)
    {
    int iRetval = 0;
    char timebuf[9];
    char czLocalSqlCmd[256];
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	//if (m_iTrace)
	logTrace("SSdb::putTracing (en) which='%s' what='%s'",
		 pczWhich,pczWhat);
    calcTimeStamp(timebuf,sizeof(timebuf));
    snprintf(czLocalSqlCmd,sizeof(czLocalSqlCmd),
	     "insert into TRACING "
	     "values('%s','%s','%s','%s','%s');",
	     timebuf,pczWhich, pczWhy, pczWhat, pczWho);
    iRetval = sqlQuery(czLocalSqlCmd,DB_TEST);
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//  if (m_iTrace)
	logTrace("SSdb::putTracing (ex) sqlstatus=%d",iRetval);
    if (iRetval != 0)
	iRetval = DERR_DB_SQL;
    return iRetval;
    }

// factorization for use within SSdb fns
void SSDb::putTracingLocal(const char * pczWhich,
			   const char * pczWhy,
			   const char * pczWho)
    {
    if (pczWhich != NULL)
        {
	char * traceMsg = strdup(m_czSqlCmd);
	if (traceMsg != NULL)
	    {
	    char * pQ;
	    while ((pQ = strchr(traceMsg,'\'')) != NULL)
		*pQ = '_';
	    putTracing(pczWhich,pczWhy,traceMsg,NN(pczWho));
	    free(traceMsg);
	    }
	}
    }

	// put an entry into the HISTORY table
	// does not check for already exists, since each is unique
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
int SSDb::putHistory(const char * pczStartStop,
		     const char * pczWhich, 
		     const char * pczWho)
    {
    int iRetval = 0;
    char timebuf[40];
    calcTimeStamp(timebuf,sizeof(timebuf));
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "insert into HISTORY values('%s','%s');",pczStartStop,timebuf);
    iRetval = sqlQuery(m_czSqlCmd,DB_COUNT);
    if (iRetval != 0)
	iRetval = DERR_DB_SQL;
    else
	putTracingLocal(pczWhich,"DB::putHistory",NN(pczWho));
    return iRetval;
    }

	// put an entry into the PROFILE table
	// verifies that pczName and pczSection are valid values
	// checks 3 possibilities: current value already there? do nothing
	//			   entry already exists? update value
	//			   no entry? add one
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_CONFLICT if invalid entry
	//			DERR_DB_SQL if DB error
int SSDb::putProfileString(const char * pczSection, 
			   const char * pczName,
			   const char * pczValue,
			   const char * pczWhich, 
			   const char * pczWho)
    {
    int iRetval = 0;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::putProfileString (en) name='%s' value='%s'",
		 pczName,pczValue);
    if (m_iDebug)
	printf("SSdb::putProfileString (en) name='%s' value='%s'\n",
		 pczName,pczValue);
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select * from LEGALVALS where  dbtable='PROFILE' "
	     "and field='section' and string='%s';",pczSection);
    iRetval = sqlQuery(m_czSqlCmd,DB_COUNT);
    if (iRetval != 0)
	iRetval = DERR_DB_SQL;
    else if (iDbRecCount != 1)
	iRetval = DERR_DB_CONFLICT;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::putProfileString verified %s as valid section for table PROFILE: %s\n",
	       pczSection,YESNO(iRetval == 0));
    if (m_iDebug)
	printf("SSdb::putProfileString validated section = %s\n",
	       YESNO(iRetval == 0));
    if (iRetval == 0)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select * from LEGALVALS where  dbtable='PROFILE' "
	     "and field='name' and string='%s';",pczName);
	iRetval = sqlQuery(m_czSqlCmd,DB_COUNT);

	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	else if (iDbRecCount != 1)
	    iRetval = DERR_DB_CONFLICT;
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace("SSdb::putProfileString verified %s as valid name for section %s: %s\n",
	       pczName,pczSection,YESNO(iRetval == 0));
	if (m_iDebug)
	    printf("SSdb::putProfileString validated name = %s\n",
		   YESNO(iRetval == 0));
	}
    if (iRetval == 0)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select OID from PROFILE where "
		 "section='%s' and name='%s' and value='%s';",
		 pczSection,pczName,pczValue);
	iRetval = sqlQuery(m_czSqlCmd,DB_COUNT);
	if ((iRetval == 0) && (iDbRecCount == 1))	// already there
	    {
	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
		logTrace("SSdb::putProfileString value %s already in DB\n",
			 pczValue);
	    // iRetval = 0;  // redundant
	    }
	else	// is there alread some value there which needs to be changed?
	    {
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		     "select OID from PROFILE where section='%s' and name='%s';",
		     pczSection,pczName);
	    iRetval = sqlQuery(m_czSqlCmd,DB_COUNT);
	    if ((iRetval == 0) && (iDbRecCount == 1))	// already there
		snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
			 "update PROFILE set value='%s' where section='%s' and name='%s';",
			 pczValue,pczSection,pczName);
	    else
		snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
			 "insert into PROFILE values ('%s','%s','%s');",
			 pczSection,pczName,pczValue);
	    iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	    if (iRetval == SQLITE_CONSTRAINT)
		iRetval = DERR_DB_CONFLICT;
	    else if (iRetval != 0)
		iRetval = DERR_DB_SQL;
	    }
	}
    if (iRetval != 0)
        {
	char * pErrmsg = errmsg("SSDb::putProfileString FAILED");
	logTrace("%s cmd='%s'",pErrmsg,m_czSqlCmd);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    else
	putTracingLocal(pczWhich,"SSDb::putProfile",NN(pczWho));
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::putProfileString (ex) returns %d",iRetval);
    return iRetval;
    }

	// get an entry from the PROFILE table
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		(volatile) string value from table if OK
	//			else NULL
const char * SSDb::getProfileString(const char * pczSection, 
				    const char * pczName,
				    const char * pczWhich, 
				    const char * pczWho)
    {
    char *  pczRetval = NULL;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::getProfileString (en) section='%s' name='%s'",
		 pczSection,pczName);
    if (m_iDebug)
	fprintf(stdout,"SSdb::getProfileString (en) section='%s' name='%s'\n",
		 pczSection,pczName);
    memset(czOutbuf,0,sizeof(czOutbuf));
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select value from PROFILE where section='%s' "
	     "and name='%s';",pczSection,pczName);
    if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
        {
	pczRetval = strstr(czOutbuf,"=");
//	logTrace("SSdb::getProfileString result is in %p=|%s|",
//	 	 pczRetval,NN(pczRetval));
	char * pSave = NULL;
	if (pczRetval != NULL)
	    {
	    pczRetval++;		// zap leading 'value=
	    *(pczRetval+strlen(pczRetval)-1) = '\0'; // zap trailing ';'
	    pSave = strdup(pczRetval);
	    }
//	logTrace("SSdb::getProfileString result is in %p=|%s|",
//		 pczRetval,NN(pczRetval));
	// putTracingLocal sometimes kills the returned value
	putTracingLocal(pczWhich,"SSDb::getProfile",NN(pczRetval));
	if (pSave != NULL)
	    {
	    strcpy_array(czOutbuf,pSave);
	    free(pSave);
	    pczRetval = czOutbuf;
	    }
	}
    else
        {
	char obuf[256];
	snprintf(obuf,sizeof(obuf)-1,
	    "SSDb::getProfileString got error: |%s|",m_czSqlCmd);
	char * pErrmsg = errmsg(obuf);
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::getProfileString (ex) value of '%s' is '%s'",pczName,NN(pczRetval));
    if (m_iDebug)
	fprintf(stdout,"SSdb::getProfileString (ex) value of '%s' is '%s'\n",pczName,NN(pczRetval));
//    if (m_iDebug)
//	fprintf(stderr,"SSdb::getProfileString (ex) value of '%s' is '%s'\n",
//		pczName,NN(pczRetval));
    return pczRetval;
    }

	// get an entry from the VCurrent table
	// @param which, who	are for tracing. Not initially implemented.
	//			if pczWhich is NULL, don't trace this call
	// @return		(volatile) string value from table if OK
	//			else NULL
const char * SSDb::getVCurrentString(const char * pczIdstr,
				     int iVp,
				     const char * pczWhich, 
				     const char * pczWho)
    {
    char *  pczRetval = NULL;
    const char * FN_NAME = "SSdb::getVCurrentString";
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("%s (en) idstr='%s' cp=%d",FN_NAME,pczIdstr,iVp);
    memset(czOutbuf,0,sizeof(czOutbuf));
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select argVal from VCurrent where  idstr='%s' "
	     "and vp='%d';",pczIdstr,iVp);
    if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
        {
	if (m_iDebug)
	    fprintf(stderr," %s retrieved raw value '%s'\n",
		    FN_NAME,NN(czOutbuf));
	pczRetval = strstr(czOutbuf,"=");
	if (pczRetval != NULL)
	    {
	    pczRetval++;		// zap leading 'value=
	    *(pczRetval+strlen(pczRetval)-1) = '\0'; // zap trailing ';'
	    }
	if (m_iDebug)
	    fprintf(stderr," %s retrieved cooked value '%s'\n",
		    FN_NAME,NN(czOutbuf));
//	putTracingLocal(pczWhich,"DB::getVCurrent",NN(pczWho));
	}
    else
        {
	char obuf[256];
	sprintf(obuf,"%s got error",FN_NAME);
	char * pErrmsg = errmsg(obuf);
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("%s (ex) value of '%s' for VP %d is '%s'",
		 FN_NAME,pczIdstr,iVp,NN(pczRetval));
    if (m_iDebug)
	fprintf(stderr," %s (ex) value of '%s'for VP %d is '%s'\n",
		FN_NAME,pczIdstr,iVp,NN(pczRetval));
    return pczRetval;
    }

	// put an entry to the VCurrent table
	// @param which, who	are for tracing. Not initially implemented.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	//			DERR_DB_CONFLICT if pczIdStr unknown
	//			DERR_FN_ARG2 if pczValue is file with no path
int SSDb::putVCurrentString(const char * pczIdstr,
			    int iVp,
			    const char * pczArgVal,
			    const char * pczWhich, 
			    const char * pczWho)
    {
    int iRetval = 0;
    const char * FN_NAME = "SSdb::putVCurrentString";
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("%d (en) idstr='%s' vp=%d value='%s'",
		 FN_NAME,pczIdstr,iVp,pczArgVal);
    if (m_iDebug)
	fprintf(stderr,"%s (en) idstr='%s' vp=%d value='%s'\n",
		FN_NAME,pczIdstr,iVp,pczArgVal);
//    memset(czOutbuf,0,sizeof(czOutbuf));
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select argVal from VCurrent where  idstr='%s' and vp='%d';",
	     pczIdstr,iVp);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if (iRetval != 0)
	iRetval = DERR_DB_SQL; // idstr not found in VCurrent
    else if (iDbRecCount != 1) // no record found, so create one
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "insert into VCurrent(idstr,vp,argVal) values ('%s','%d','%s');",
		 pczIdstr,iVp,pczArgVal);
	iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	}
    else                       // record found, so update it
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "update VCurrent set argVal='%s' where idstr='%s' and vp='%d';",
		 pczArgVal,pczIdstr,iVp);
	iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("%s (ex) returns %d",FN_NAME,iRetval);
    if (m_iDebug)
	fprintf(stderr,"%s (ex) returns %d\n",FN_NAME,iRetval);
    return iRetval;
    }

	// put an entry into the CURRENT table
	// use update
	//
	// NOTE
	//   This will NEVER insert an idStr which doesn't already
	//   exist in the table.
	//
	// @param pczIdStr	which record to update
	// @param iWhichVal	what kind of value is being supplied?
	//			    0 => complete path & file
	//			    1 => op
	//			    2 => path
	//			    3 => single variable (e.g. VP)
	//				pczValue put into argVal
	//			    4 => single variable keyed by scriptName
	//				pczValue put into argVal 
	//				(not currently used)
	// @param pczValue	value per iWhichVal, or NULL => emtpy it
	// @param iPixels	size of PROCESSED image (iwhich < 2)
	// @param iLines 	size of PROCESSED image (iwhich < 2)
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	//			DERR_DB_CONFLICT if pczIdStr unknown
	//			DERR_FN_ARG2 if pczValue is file with no path
int SSDb::putCurrent(const char * pczIdStr, 
		     int iWhichVal,
		     const char * pczValue, 
		     int iPixels, int iLines,
		     const char * pczWhich, 
		     const char * pczWho)
    {
    int iRetval = 0;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::putCurrent (en) id='%s' which=%d value='%s'",
		 pczIdStr,iWhichVal,pczValue);
    if (m_iDebug)
	fprintf(stderr,"SSdb::putCurrent (en) id='%s' which=%d value='%s'\n",
		pczIdStr,iWhichVal,pczValue);
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select OID from CURRENT where idstr='%s';",pczIdStr);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if ((iRetval != 0) || (iDbRecCount != 1))
	iRetval = DERR_DB_SQL; // id not found in CURRENT
    else if (iWhichVal == 0)   // it's a file; make sure path is in PATHS
        {
	if ((pczValue == NULL) 
	    || (strspn(pczValue,"0") == strlen(pczValue))) // NULL xlated into 00000
	    {
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		     "update CURRENT set fileId=0, opKey='',bWritten=0, "
		     "pixels=0, lines=0 where idstr='%s';",pczIdStr);
	    iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	    if (iRetval != 0)
	        iRetval = DERR_DB_SQL;
	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	        logTrace("SSdb::putCurrent (ex) retval=%d",iRetval);
	    return iRetval ;
	    }
	char * pczLocFile = strdup(pczValue);
	if (pczLocFile != NULL)
	    {
	    char * pFs = strrchr(pczLocFile,'/');
	    char * pBs = strrchr(pczLocFile,'\\');
	    char * pCol = strrchr(pczLocFile,':');
	    char * pczNode = (pBs > pFs) // and therefore bigger than pCol 
		  ? pBs
		  : (pFs > pCol) ? pFs	// ditto
		  : (pCol > pczLocFile) ? pCol : pczLocFile;
	    const char * pczRealNode = &pczValue[pczNode - pczLocFile]; 
	    if (pczRealNode > pczValue)
	        pczRealNode++;		// go past the delimiter
	    if (*pczNode == ':')
	        pczNode++;
	    *pczNode = '\0';
	    int iPathId = 0;
	    if (strlen(pczLocFile) > 0)
	        iPathId = putPath(pczLocFile,"",FALSE);
	    free(pczLocFile);
	    if (m_iDebug)
	        printf("putCurrent pathId=%d\n",iPathId);
	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
		  //	    if (m_iTrace)
	        logTrace("putCurrent pathId=%d",iPathId);
	    if (iPathId == 0)
		return DERR_FN_ARG2;
	    else if (iPathId > 0)
	        {
		int iFileId = putFile(pczRealNode,iPathId);
		if (m_iDebug)
		    printf("putCurrent pathId=%d fileid=%d\n",iPathId,iFileId);
		if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
		    //	if (m_iTrace)
		    logTrace("putCurrent pathId=%d fileid=%d",iPathId,iFileId);
	        if (iFileId > 0)
	            {
		    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
			     "update CURRENT set fileId=%d, opKey='',bWritten=1, "
			     "pixels=%d, lines=%d where idstr='%s';",
			     iFileId,iPixels,iLines,pczIdStr);
		    iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
		    if (iRetval != 0)
			iRetval = DERR_DB_SQL;
		    }
		}
	    else
		iRetval = iPathId; // which is the error code
	    }
	else
	    iRetval = DERR_MEM_ALLOC;
	}
    else if (iWhichVal == 1)   // it's an op for 'M'
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "update CURRENT set fileId=0, opKey='%s',"
		"bWritten=0, pixels=%d, lines=%d where idstr='%s';",
		 pczValue,iPixels,iLines,pczIdStr);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	}
    else if (iWhichVal == 2)   // it's a path for WPATH etc
        {
	int iPathId = putPath(pczValue,"",FALSE);
	if (m_iDebug)
	    printf("putCurrent w=2 pathId=%d\n",iPathId);
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    //if (m_iTrace)
	    logTrace("putCurrent w=2 pathId=%d",iPathId);
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "update CURRENT set fileId=%d,opKey='',bWritten=0 "
		 "where idstr='%s';",
		 iPathId,pczIdStr);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	}
    else if (iWhichVal == 3)   // set single value keyed by idStr
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "update CURRENT set argVal = '%s' where idStr='%s';",
		 pczValue,pczIdStr);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	}
    else if (iWhichVal == 4)   // set single value keyed by scriptName
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "update CURRENT set argVal = '%s' where scriptName='%s';",
		 pczValue,pczIdStr);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	}
    if (iRetval != 0)
        {
	char obuf[256];
	sprintf(obuf,"SSDb::putCurrent returns %d",iRetval);
	char * pErrmsg = errmsg(obuf);
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    else 
	putTracingLocal(pczWhich,"DB::putCurrent",NN(pczWho));
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
        {
	char * pczDump = dumpTables("putCurrent (ex)\n",DUMP_CURRENT);
	if (pczDump != NULL)
	    {
	    logTrace(pczDump);
	    free(pczDump);
	    }
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::putCurrent (ex) retval=%d",iRetval);
    return iRetval;
    }

	// put an entry into the PATHS table if not already exists
	// use either insert or update, as needed
	// @param pczPath	complete path, using '/' separators
	//   the following are used to update any previously-existing record
	// @param pczQual	if NON-NULL, update any entry to new values
	// @param bDpath	TRUE is this is the NEWEST DPATH 
	// @return		OID of new or already-existing entry
	//			DERR_DB_SQL if DB error
int SSDb::putPath(const char * pczPath,
		  const char * pczQual, 
		  BOOL bDpath,
		  const char * pczWhich, 
		  const char * pczWho)
    {
    int iRetval = 0;
    int iNewDPATH = (bDpath) ? 1 : 0;
    const char * pczPathPtr = pczPath;
    char * pczModPath = strdup(pczPath);
    if (pczModPath != NULL) // change drive ltrs to UC and '\' to '/'
        {
	pczPathPtr = pczModPath;
	if (pczModPath[1] == ':')
	    pczModPath[0] = toupper(pczModPath[0]);
	for (uint j=0; j<strlen(pczModPath); j++)
	    if (pczModPath[j] == '\\')
	         pczModPath[j] = '/';
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::putPath (en) path='%s' modpath='%s' dPath=%s",
		 pczPath,pczPathPtr,YESNO(bDpath));
    if ((iRetval == 0) && bDpath)  // was there a prior one? 
        {	// Get the number (not OID) of the latest
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select DPATH from PATHS where DPATH > 0 "
		 "order by dpath DESC limit 1;");
	iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	else if (iDbRecCount == 1)
	    iNewDPATH = 1 + iOID; // NOTE: not the OID
	}
    if (iRetval < 0)
        {
	char * pErrmsg = errmsg("SSDb::putPath exiting error");
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	return iRetval;
	}
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select OID from PATHS where path='%s';",pczPathPtr);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if ((iRetval != 0) || (iDbRecCount > 1))
        {
	logTrace("putPath sqlerror %d seeking %s; count=%d",iRetval,
		 pczPathPtr,iDbRecCount);
	iRetval = DERR_DB_SQL;
        }
    else if (iDbRecCount == 0) // not found
        {
	if (m_iDebug)
	    printf("about to do the insert; status=%d\n",
		   iRetval);
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace("putPath sqlerror %d about to do the insert",iRetval);
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "insert into PATHS values('%s','%s',%d);",
		 pczPathPtr,(pczQual==NULL) ? "" : pczQual,iNewDPATH);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    {
	    logTrace("putPath sqlerror %d doing insert; cmd='%s'",
			 iRetval,m_czSqlCmd);
	    iRetval = DERR_DB_SQL;
	    }
	}
    else
        {
	if (bDpath)  // is this one already a DPATH? if so, keep same num.
            {
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		     "select DPATH from PATHS where DPATH>0 and path='%s';",
		     pczPathPtr);
	    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	    if ((iRetval != 0) || (iDbRecCount > 1))
		iRetval = DERR_DB_SQL;
	    else if (iDbRecCount == 1)
		iNewDPATH = iOID; // we'll just keep it the same
	    }
	if (m_iDebug)
	    printf("about to do the update; status=%d iOID=%d\n",
		   iRetval,iOID);
	if ((iRetval == 0) 
	        && (((pczQual != NULL) && (strlen(pczQual) > 0)) || bDpath))
	    {
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		     "update PATHS set qual='%s', dpath=%d where path = '%s';",
		     pczQual,iNewDPATH, pczPathPtr);
	    iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	    if (iRetval != 0)
		iRetval = DERR_DB_SQL;
	    if (m_iDebug)
		printf("doing the update; cmd='%s'\n",m_czSqlCmd);
	    }
	}
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select OID from PATHS where path='%s';",pczPathPtr);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if ((iRetval != 0) || (iDbRecCount != 1))
        {
	logTrace("putPath 8a sqlerror %d seeking %s; count=%d",iRetval,
		 pczPathPtr,iDbRecCount);
	iRetval = DERR_DB_SQL;
	}
    else
	iRetval = iOID;
    if (iRetval != 0)
        {
	char obuf[256];
	sprintf(obuf,"SSDb::putPath returns %d",iRetval);
	char * pErrmsg = errmsg(obuf);
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    if (iRetval >= 0)
	putTracingLocal(pczWhich,"DB::putPath",NN(pczWho));
    if (pczModPath != NULL)
	free(pczModPath);
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace("SSdb::putPath (ex) retval=%d",iRetval);
    return iRetval;
    }

	// put an entry into the FILES table
	// use either insert or ignore call
	// @param pczFile	file name, excluding path 
	// @param iPathId	id of the corresponding path
	// @return		OID of new or already-existing entry if OK
	//			DERR_DB_SQL if DB error
int SSDb::putFile(const char * pczFile, int iPathId,
		  const char * pczWhich, const char * pczWho)
    {
    int iRetval;
    #undef FN_NAME
    #define FN_NAME "SSDb::putFile"
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace(FN_NAME " (en) file='%s' pathId=%d",pczFile,iPathId);
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (en) file='%s' pathId=%d\n",pczFile,iPathId);
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select OID from FILES where name='%s' and pathId=%d;",
	     pczFile,iPathId);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if ((iRetval != 0) || (iDbRecCount > 1))
	iRetval = DERR_DB_SQL;
    else if (iDbRecCount == 0) // not found
        {
	if (m_iDebug)
	    printf("about to do the insert\n");
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "insert into FILES values('%s',%d);",pczFile,iPathId);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	}
    if (iRetval == 0)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select OID from FILES where name='%s' and pathId=%d;",
		 pczFile,iPathId);
	iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	if ((iRetval != 0) || (iDbRecCount != 1))
	    iRetval = DERR_DB_SQL;
	else
	    iRetval = iOID;
        }
    if (iRetval != 0)
        {
	char obuf[256];
	sprintf(obuf,"SSDb::putFile returns %d",iRetval);
	char * pErrmsg = errmsg(obuf);
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    if (iRetval >= 0)
	putTracingLocal(pczWhich,"DB::putFile",NN(pczWho));
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace(FN_NAME " (ex) retval=%d",iRetval);
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (ex) retval=%d",iRetval);
    return iRetval;
    }

	// get a single composite path/files from the FILES & PATHS tables
	// @param pczIdStr	which record to get. (OID in Files table)
	// @return		pointer to result string or NULL if error
	//			The result is created in the shared
	//			s_outbuf, so it is somewhat volatile
const char * SSDb::getFile(const char * pczIdStr)
    {
    char * pczRetval = NULL;
    czOutbuf[0] = '\0';
    #undef FN_NAME
    #define FN_NAME "SSDb::getFile"
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace(FN_NAME " (en) id='%s'",pczIdStr);
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select path,name from FILES f, PATHS p "
	     "where f.pathID = p.OID and f.OID = %s;",pczIdStr);
    if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
        {
	    // raw has form 'path=xxx;name=yyy;'
	if (m_iDebug)
	    fprintf(stderr,FN_NAME " raw retrieval got '%s'\n",czOutbuf);
	char * pEq = strstr(czOutbuf,"=");
	if (pEq != NULL)
	    memmove(czOutbuf,pEq+1,strlen(pEq)); // includes the '\0'
	char * pSemi = strstr(czOutbuf,";");
	if (pSemi != NULL)
	    {
	    *pSemi = '/';
	    pEq = strstr(pSemi,"=");
	    if (pEq != NULL)
		memmove(pSemi+1,pEq+1,strlen(pEq)); // includes the '\0'
	    }
	pSemi = strstr(czOutbuf,";");
	if (pSemi != NULL)
	    *pSemi = '\0';
	pczRetval = czOutbuf;
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace(FN_NAME " (ex) got '%s'",NN(czOutbuf));
    if (m_iDebug)
	fprintf(stderr,FN_NAME " (ex) got '%s'\n",NN(czOutbuf));
    return pczRetval;
    }

	// get the product level either from the SN or the ProductLevel entry
	// first verify the checksum
	// @param bOriginal	TRUE => get from SN else from ProductLevel
	// @return		> 0 is product level
	//			< 0 is error
int SSDb::getProductLevel(BOOL bOriginal)
    {
    int iRetval = 0;
    if (! verifySignature())
	iRetval = DERR_DB_CONFLICT;
    else if (bOriginal)
        {
	const char * pczSN = getProfileString("install","SN",NULL,NULL);
	iRetval = (pczSN == NULL) ? DERR_DB_NOTFOUND : pczSN[7] & 0xF; 
        }
    else
        {
	const char * pczPL = getProfileString("install","ProductLevel",NULL,NULL);
	iRetval = (pczPL == NULL) ? DERR_DB_NOTFOUND : (int)strtol(pczPL,NULL,16);
	}
    return iRetval;
    }

#if DRAGON_VER >= 6
     /* get product bit pattern (less the product bits)
      * @param  ulProduct  the product number
      * @return           bit pattern corresponding to specified product
      */
static ulong MyProductBits(ushort uProduct)
    {
// defined in dp.h
    PRODUCT_BITS_FN
    }
#endif

	// set the ProductLevel entry and set signature
	// first verify the signature
	// 2012-05-02 added Bits 
	// @param uProduct	value to set
	// @return		> 0 is product level
	//			< 0 is error
int SSDb::setProductLevel(uint uProduct)
    {
    int iRetval = 0;
    char czProduct[2];
#if DRAGON_VER >= 6
    char czBits[20];
    ulong ulBits = MyProductBits(uProduct);
    snprintf(czBits,sizeof(czBits),"%ld",ulBits);
#endif
    snprintf(czProduct,sizeof(czProduct),"%X",uProduct);
    if (! verifySignature())
	iRetval = DERR_DB_CONFLICT;
    else
	iRetval = putProfileString("install","ProductLevel",czProduct);
#if DRAGON_VER >= 6
    if (iRetval == 0)
	iRetval = putProfileString("install","Bits",czBits);
#endif
    if (iRetval == 0)
	setSignature();
    return (iRetval == 0) ? uProduct : iRetval;
    }

/* set the DB to show it's been registered
 * This will set ValCode and ValDate only if pValCode is non-empty
 * In all cases, unless DB error, sets workinglines etc in DB
 * called only from SSDp::checkProductStatus
 * @param pValCode		validation code: NULL or "" or validation code
 * @param uProductlevel		DEMO_PRODUCT or UNAUTH_PRODUCT or 
 * @param czWorkingLines	set maximum size
 *	  czWorkingPixels	(ignored if == NULL)
 * @param czWorkingImages
 * @param uBits			processor register size
 * @return 			0 if OK else -1
 */
int SSDb::registerToDb(const char * pValCode,uint uProductLevel, 
		       const char * czWorkingLines,
		       const char * czWorkingPixels,
		       const char * czWorkingImages,
		       uint uBits)
    {
    const char * czMethod = "SSDb::registertoDb";
    logTrace("%s (en)",czMethod);
    int iRetval = setProductLevel(uProductLevel); // do first, since verifies DB signature
    if (iRetval  >= 0)
        {
	char buf[20];
	iRetval = 0;
	if ((pValCode != NULL) && (strlen(pValCode) > 0))
	    {
	    const char * pOV = getProfileString("install","ValCode",0,0);
	    if ((pOV == NULL) || (strspn(pOV," ") == strlen(pOV)))
	        {
		calcTimeStamp(buf,sizeof(buf));
		putProfileString("install","ValDate",buf); 
		iRetval = putProfileString("install","ValCode",pValCode); 
		}
	    }
	if ((iRetval == 0) && (czWorkingLines != NULL))
	    iRetval = putProfileString("install","WORKING_LINES",
				       czWorkingLines); 
	if ((iRetval == 0) && (czWorkingPixels != NULL))
	    iRetval = putProfileString("install","WORKING_PIXELS",
				       czWorkingPixels); 
	if ((iRetval == 0) && (czWorkingImages != NULL))
	    iRetval = putProfileString("install","WORKING_IMAGES",
				       czWorkingImages); 
	snprintf(buf,sizeof(buf),"%d",uBits);
	if (iRetval == 0)
	    iRetval = putProfileString("install","Bits",buf); 
	if (iRetval == 0)
	    iRetval = setSignature();
	logTrace("%s (ex) setSignature returns %d",czMethod,iRetval);
	}
    else
        {
	logTrace("%s (ex) verifySignature insetProductLevel failed",czMethod);
	}
    return iRetval;
    }

	// put an entry into the CHECKSUMS table
	// @param pczFile	file name, excluding path 
	// @param pczChecksum	file checksum as a string
	// @param pczDate	file date
	// @return		OID of new or already-existing entry if OK
	//			DERR_DB_SQL if DB error
int SSDb::putChecksum(const char * pczFile, const char * pczChecksum, const char * pczDate)
    {
    int iRetval;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace("SSdb::putChecksum (en) file='%s' date='%s' ck='%s'",pczFile,pczChecksum,pczDate);
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select OID from CHECKSUMS where file='%s';",
	     pczFile);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if ((iRetval != 0) || (iDbRecCount > 1))
	iRetval = DERR_DB_SQL;
    else if (iDbRecCount == 0) // not found
        {
	if (m_iDebug)
	    printf("about to do the insert\n");
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "insert into CHECKSUMS values('%s','%s','%s');",pczFile,
		 pczChecksum, pczDate);
	iRetval = sqlQuery(m_czSqlCmd,DB_TEST);
	if (iRetval != 0)
	    iRetval = DERR_DB_SQL;
	}
    if (iRetval == 0)
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select OID from CHECKSUMS where file='%s';",
		 pczFile);
	iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	if ((iRetval != 0) || (iDbRecCount != 1))
	    iRetval = DERR_DB_SQL;
	else
	    iRetval = iOID;
        }
    if (iRetval != 0)
        {
	char obuf[256];
	sprintf(obuf,"SSDb::putChecksum returns %d",iRetval);
	char * pErrmsg = errmsg(obuf);
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace("SSdb::putChecksum (ex) retval=%d",iRetval);
    return iRetval;
    }

	// verify an entry in the CHECKSUMS table
	// @param pczFile	file name, excluding path 
	// @param pczChecksum	file checksum as a string
	// @param pczDate	file date
	// @return		0 if matches
	//			DERR_FN_ARG1 or DERR_FN_ARG2 if present but not matches
	//			DERR_DB_NOTFOUND if file not found
	//			DERR_DB_SQL if DB error
int SSDb::verifyChecksum(const char * pczFile, const char * pczChecksum, const char * pczDate)
    {
    int iRetval = 0;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace("SSdb::verifyChecksum(en) file='%s' ck='%s' date='%s'",pczFile,pczChecksum,pczDate);
    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
	     "select OID from CHECKSUMS where file='%s' and checksum='%s' and date='%s' ;",
	     pczFile,pczChecksum,pczDate);
    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
    if ((iRetval != 0) || (iDbRecCount > 1))
	iRetval = DERR_DB_SQL;
    else if (iDbRecCount == 1) // found and matches
	iRetval = DERR_DB_SQL;
    else			// no match
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select OID from CHECKSUMS where file='%s' and checksum='%s';",
		 pczFile,pczChecksum);
	iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	if ((iRetval != 0) || (iDbRecCount > 1))
	    iRetval = DERR_DB_SQL;
	else if (iDbRecCount == 1) // found and matches except date
	    iRetval = DERR_FN_ARG2;
	else			// no match
	    {
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		     "select OID from CHECKSUMS where file='%s';",
		     pczFile);
	    iRetval = sqlQuery(m_czSqlCmd,DB_ID);
	    if ((iRetval != 0) || (iDbRecCount > 1))
		iRetval = DERR_DB_SQL;
	    else if (iDbRecCount == 1) // found file, no match of attrribs
		iRetval = DERR_FN_ARG1;
	    else
		iRetval = DERR_DB_NOTFOUND;
	    }
	}
    if (iRetval != 0)
        {
	char obuf[256];
	sprintf(obuf,"SSDb::verifyChecksum returns %d",iRetval);
	char * pErrmsg = errmsg(obuf);
	logTrace(pErrmsg);
	if (m_iDebug)
	    printf("%s\n",pErrmsg);
	free(pErrmsg);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace("SSdb::verifyChecksum (ex) retval=%d",iRetval);
    return iRetval;
    }

	// get one or more entries from the CURRENT table
	// @param pczIdStr	which record to get.
	//			if NULL or 'STATUS', get all info needed by UI,
	//			   formatted for UI use
	//			if 'RGB', get the three files which make up =C
	//			   formatted for Server use
	// @return		pointer to result string or NULL if error
	//			The result is created in the shared
	//			s_outbuf, so it is somewhat volatile
	//			NOTE Returns NULL if count==0,
	//			  but '' if found and == ''
const char * SSDb::getCurrent(const char * pczIdStr)
    {
    char * pczRetval = NULL;
    czOutbuf[0] = '\0';
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::getCurrent (en) id='%s'",
		 (pczIdStr==NULL) ? "NULL" : pczIdStr);
    if ((pczIdStr == NULL) || (strcmp(pczIdStr,"STATUS") == 0))	// create record for UI
        {
	char wpath[PATH_MAX+30];
	char dpath[PATH_MAX+30];
	char opcurrent[256]; /* only =M can have an opStr */
	wpath[0] = dpath[0] = opcurrent[0] = czOutbuf[0] = '\0';

	// get WPATH
	strcpy(m_czSqlCmd,"select idStr,path from CURRENT c, PATHS p "
	       "where  (c.fileId = p.OID and idStr = 'WPATH');");
	if (sqlQuery(m_czSqlCmd,DB_STATUS,czOutbuf) == 0)
	    { strcat_array(wpath,czOutbuf); }
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace("SSdb::getCurrent WPATH got '%s'",wpath);

	// get DPATH
	strcpy(m_czSqlCmd,"select path from PATHS where dpath > 0 "
	       "ORDER by dpath DESC limit 1; ");
	if (sqlQuery(m_czSqlCmd,DB_STATUS,czOutbuf) == 0)
	    { strcat_array(dpath,czOutbuf); }
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace("SSdb::getCurrent DPATH got '%s'",dpath);

	// get =M
	strcpy(m_czSqlCmd,"select DISTINCT idStr,pixels,lines,opKey from "
	       "CURRENT where opKey != '' and idStr = 'M';");
	if (sqlQuery(m_czSqlCmd,DB_STATUS,czOutbuf) == 0)
	    { strcat_array(opcurrent,czOutbuf); }
	if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    logTrace("SSdb::getCurrent WM got '%s'",opcurrent);

	// get all file/path combos
	strcpy(m_czSqlCmd,"select DISTINCT idStr,name,pixels,lines,path from "
	       "CURRENT as c, FILES as f, PATHS as p "
	       "where c.fileId = f.OID and f.pathID = p.OID "
	       "and idStr NOT LIKE '%PATH' and opKey = '';");
	if (sqlQuery(m_czSqlCmd,DB_STATUS,czOutbuf) == 0)
	    {
	    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	        logTrace("SSdb::getCurrent file/path combos got '%s'",
			 czOutbuf);
	    strcat_array(czOutbuf,wpath);
	    strcat_array(czOutbuf,dpath);
	    strcat_array(czOutbuf,opcurrent);
            pczRetval = czOutbuf;
	    }
	}
    else if (strcmp(pczIdStr,"RGB") == 0)	// create =C record for Server
        {		// needs quotes around files EXCEPT not at begin or end
	strcpy (czOutbuf,"=C\" ");
	strcpy(m_czSqlCmd,"select idStr,name,path from "
	       "CURRENT as c, FILES as f, PATHS as p "
	       "where c.fileId = f.OID and f.pathID = p.OID "
	       "and (idStr='R' or idStr='G' or idStr='B');");
	if (sqlQuery(m_czSqlCmd,DB_RGB,czOutbuf) == 0)
	    {
            pczRetval = czOutbuf;
	    if (czOutbuf[strlen(czOutbuf)-1] == '"')
	      czOutbuf[strlen(czOutbuf)-1] = '\0';
	    }
	}
#ifdef NOMORE
    else if (strcmp(pczIdStr,"(CURCOL") == 0)	// create -C S -CF  record
        {
	strcpy (czOutbuf,"S\" -CF \"");
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select idStr,name,path from "
		 "CURRENT as c, FILES as f, PATHS as p "
		 "where c.fileId = f.OID and f.pathID = p.OID "
		 "and scriptName='%s';",pczIdStr);
	if (sqlQuery(m_czSqlCmd,DB_FULLPATH,czOutbuf) == 0)
	    {
            pczRetval = czOutbuf;
	    if (czOutbuf[strlen(czOutbuf)-1] == '"')
	      czOutbuf[strlen(czOutbuf)-1] = '\0';
	    }
	}
#endif
    else if ((strcmp(pczIdStr,"(CURVP") == 0) || (*pczIdStr == '&'))
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select argVal from CURRENT where scriptName='%s';", 
		 pczIdStr);
	if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
            pczRetval = czOutbuf;
	}
    else if ((*pczIdStr == '=') || (*pczIdStr == '('))	// create file record for Server
        {  // e.g. =B, etc; (CURCOL, etc
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select idStr,name,path from "
		 "CURRENT as c, FILES as f, PATHS as p "
		 "where c.fileId = f.OID and f.pathID = p.OID "
		 "and scriptName='%s';",pczIdStr);
	if (sqlQuery(m_czSqlCmd,DB_FULLPATH,czOutbuf) == 0)
            pczRetval = czOutbuf;
	}
    else
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select * from CURRENT where idStr='%s';",pczIdStr);
	if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
            pczRetval = czOutbuf;
	}
    if (strlen(czOutbuf) == 0)
	pczRetval = NULL;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::getCurrent (ex) got '%s'",NN(pczRetval));
    return pczRetval;
    }

	// get one or more entries from the FILES & PATHS tables
	// @param pczIdStr	which record to get.
	//			if 'IMAGE', get all recognized image files
	//			other values to be defined
	// @return		pointer to result string or NULL if error
	//			The result is created in the shared
	//			s_outbuf, so it is somewhat volatile
const char * SSDb::getFiles(const char * pczIdStr)
    {
    char * pczRetval = NULL;
    czOutbuf[0] = '\0';
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::getFiles (en) id='%s'",
		 (pczIdStr==NULL) ? "NULL" : pczIdStr);
    if (strcmp(pczIdStr,"IMAGE") == 0)	// get all image files
        {
	strcpy(m_czSqlCmd,"select name,path from FILES f, PATHS p "
	       "where f.pathID = p.OID "
	       "and (name LIKE '%.IMG' OR name LIKE '%.TIF');");
	if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
            pczRetval = czOutbuf;
	}
#ifdef NOTYET // don't know what else we'll need
    else
        {
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select * from CURRENT where idStr='%s';",pczIdStr);
	if (sqlQuery(m_czSqlCmd,DB_ATTRVAL,czOutbuf) == 0)
            pczRetval = czOutbuf;
	}
#endif
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
//    if (m_iTrace)
	logTrace("SSdb::getFiles (ex) got '%s'",NN(czOutbuf));
    return pczRetval;
    }

	// calculate a checksum of the PROFILE fields listed in s_czSignatureFields
	// and return it
	// @return		calculated chacksum & 0x7FFFFFFF
	//			else
uint SSDb::_calcSignature()
    {
    uint uChecksum = 0;
    uint j;
    for (j=0; j<AY_COUNT(s_czSignatureFields); j++)
        {
	const char * pVal = getProfileString("install",s_czSignatureFields[j],0,0);
	if (pVal != NULL)
	    {
	    int jj = 0;
//	    const char * savepVal = pVal;
	    while(*pVal != '\0')
	        {
		uChecksum += (*pVal) << (7 * (jj%4)); // i.e. each value <= 0x0FFFFFFF
//		logTrace("_calcSignature field=%s pVal='%s' uChecksum=x%X *pVal=x%X jj=%d",
//			 s_czSignatureFields[j],pVal,uChecksum,*pVal,jj);
		jj++;
		pVal++;
		}
//	    logTrace("_calcSignature field=%s value='%s' uChecksum=x%X",
//			 s_czSignatureFields[j],savepVal,uChecksum);
	    }
	}
    return uChecksum & 0x7FFFFFFF;
    }

	// calculate a checksum of the PROFILE fields listed in s_czSignatureFields
	// and store it in the Signature field.
	// @return		0 if OK
int SSDb::setSignature()
    {
    int iRetval = 0;
    uint uSig = _calcSignature();
    char czSig[10];
    snprintf(czSig,sizeof(czSig),"%08X",uSig);
//    ulong ulOldLevel = Logger::getTraceLevel();
//    Logger::setTraceLevel(ulOldLevel | TRACE_LVL_SSDb);
    iRetval = putProfileString("install","Signature",czSig);
    logTrace("SSDb::setSignature '%s' = x%X returns %d",czSig,uSig,iRetval);
//    Logger::setTraceLevel(ulOldLevel);
    return iRetval;
    }

	// calculate a checksum of the PROFILE fields listed in s_czSignatureFields
	// and verify it against the Signature field.
	// @return		TRUE if matches
	//			FALSE (0) if match fails
BOOL SSDb::verifySignature()
    {
    BOOL bRetval = 0;
    uint uSig = _calcSignature();
    const char * pVal = getProfileString("install","Signature",0,0);
    if (pVal != NULL)
        {
	uint uOldSig = (uint)strtoul(pVal,NULL,16);
	bRetval = (uOldSig == uSig);
	logTrace("SSDb::verifySignature old=x%X new=x%X",uOldSig,uSig);
	}
    logTrace("SSDb::verifySignature returns %s",YESNO(bRetval));
    if (! bRetval)
	{
	char * pczDump = dumpTables("SSDb::signature mismatch\n",0);
	if (pczDump != NULL)
	    {
	    logTrace(pczDump);
	    free(pczDump);
	    }
	}
    return bRetval;
    }

	// dump all tables
	// @param pczTitle	if non-NULL, prefix dump with a title string.
	// @param ulTableMask	bitmap of tables to NOT dump
	//			   bit# corresponds to index in s_czTables
	// @return		ptr to static buffer containing output
	//
char * SSDb::dumpTables(const char * pczTitle,ulong ulTableMask /* = 0 */)
    {
    char * pczRetval = NULL;
    int iDumpSize = (pczTitle != NULL) ? 1+strlen(pczTitle) : 0;
    int iTraceSave = m_iTrace;
    m_iTrace=0;
    ulong uOldLevel = Logger::getTraceLevel();
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::dumpTables (en) title='%s', mask=x%X",
		 NN(pczTitle),ulTableMask);
    Logger::setTraceLevel(0); // suppress tracing during DUMP
    uDbTableNo = 0;
    if (m_iDebug)
        printf("dumpTables before calc tables dumpsize=%d\n",iDumpSize);
    for (uint j=0; j<AY_COUNT(s_czTables); j++)
        {
	uDbTableNo = j;
	snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select OID,* from %s;",s_czTables[j]);
	if (sqlQuery(m_czSqlCmd,DB_TABLE,NULL) == 0) // && (iDbRecCount > 0))
            iDumpSize += iDbSize + 8 + strlen(s_czTables[j]);
//	if (m_iDebug)
//	    printf("dumpTables after calc table %s recCount=%d iDbSize=%d dumpsize=%d\n",
//		   s_czTables[j],iDbRecCount,iDbSize,iDumpSize);
	}
    if (m_iDebug)
	printf("dumpTables dumpsize=%d\n",iDumpSize);
    pczRetval = (char *)calloc(iDumpSize,1);
    if (pczRetval != NULL)
        {
	if (pczTitle != NULL)
	    strcpy(pczRetval,pczTitle);
	for (uint j=0; j<AY_COUNT(s_czTables); j++)
            {
	    uDbTableNo = j;
	    if (ulTableMask & (1 << j)) // suppress this one?
	        continue;
	    snprintf(m_czSqlCmd,sizeof(m_czSqlCmd),
		 "select OID,* from %s;",s_czTables[j]);
	    sprintf(pczRetval+strlen(pczRetval),"\n'%s'\n",s_czTables[j]);
	    sqlQuery(m_czSqlCmd,DB_TABLE,pczRetval+strlen(pczRetval));
//	    if (m_iDebug)
//		printf("dumpTables after table %s recCount=%d dumpsize=%d\n",
//		       s_czTables[j],iDbRecCount,strlen(pczRetval));
	    }
	}
    m_iTrace=iTraceSave;
    Logger::setTraceLevel(uOldLevel); // suppress tracing during DUMP
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSdb::dumpTables (ex)");
    return pczRetval;
    }

	// Find which, if any table is named
	// @param pNamePtr	name of table
	// @return		index within s_czTables, or -1
int SSDb::whichTable(const char * pNamePtr)
    {
    int ndx = IpcCmdWatcher::whichKnownCommand(s_czTables,
					       AY_COUNT(s_czTables),
					       pNamePtr);
    return ndx;
    }

	// simply create an object and set properties to default
	// @param iDebug	debug level if > than set by OB::OB
	// @param iTrace	trace level if > than set by OB::OB
SSDbSqlite::SSDbSqlite(int iDebug,int iTrace) 
    {
//    if (iTrace || m_iTrace)
//	logTrace("SSDbSqlite::SSDbSqlite (en)");
    //   if (iDebug || m_iDebug)
//	printf("SSDb::SSDbSqlite (en)\n");
    m_pClass = &s_class_Base; m_pClass->setSubClass(SSDb::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_pDb = NULL;
    m_pczError = NULL;
    }

SSDbSqlite::~SSDbSqlite()
    {
    int iStat = -99;
    if (m_pDb != NULL)
	iStat = sqlite3_close(m_pDb);
//    logTrace("SSDbSqlite::~SSDbSqlite close return %d",iStat);
    m_pDb = NULL;
    }

	// Open the DB if it exists, create it if it doesn't exist
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// Do nothing which is site. product, or situation dependent
	// In other words, this is NOT a validation step.
	// @param bPreserve	if TRUE, do nothing except open the DB
	// @return 		0 if OK
	//			-50 = DERR_FILE_ACCESS if DB missing
	//			-85 = DERR_DB_OPEN if unable to open or create
int SSDbSqlite::init(const char * dbName,BOOL bPreserve)
    {
    int iRetval = 0;
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDbSqlite::init (en)");
    if (access(dbName,F_OK) != 0)
        {
	logTrace("Database %s not found", dbName);
	if (m_iDebug)
	    fprintf(stderr, "Database %s not found\n", dbName);
	iRetval = DERR_FILE_ACCESS;
        }
    else
        {
	iRetval = sqlite3_open(dbName, &m_pDb);
	if (iRetval)
            {
	    logTrace("Can't open database: %s", sqlite3_errmsg(m_pDb));
	    if (m_iDebug)
		fprintf(stderr, "Can't open database: %s\n", 
			sqlite3_errmsg(m_pDb));
	    sqlite3_close(m_pDb);
	    m_pDb = NULL;
	    iRetval = DERR_DB_OPEN;
	    }
	else
	    iRetval = SSDb::init(bPreserve);
	}
    if (Logger::getTraceLevel() & TRACE_LVL_SSDb)
	logTrace("SSDbSqlite::init (ex) returning %d",iRetval);
    return iRetval;
    }

const char * SSDbSqlite::setupSubstMsgs()
    {
    static char substMsgs[1024] = "";
    if (strlen(substMsgs) == 0)
	{
	const char * pProf = getProfileString("install", "SN", NULL,NULL);
	char * pczSerialNum = NULL;
	char * pczMachine = NULL;
	if (pProf != NULL)
	    { 
	    strcat_array(substMsgs,pProf);
	    pczSerialNum = strdup(pProf);
	    }
	strcat_array(substMsgs,"|"); 
	pProf = getProfileString("install", "Machine", NULL,NULL);
	if (pProf != NULL)
	    { 
	    strcat_array(substMsgs,pProf); 
	    pczMachine = strdup(pProf);
	    }
	strcat_array(substMsgs,"|"); 
	strcat_array(substMsgs,"Dragon/ips|");
	strcat_array(substMsgs,"https://dragon-ips.com/cgi-bin/dragonVerify.pl|");
	strcat_array(substMsgs,"https://dragon-ips.com/cgi-bin/bugReport.pl");
	}
    return substMsgs;
    }

#if DRAGON_VER >= 6
	// pczCorruptField amd pczCorruptValue are used for testing.
	// Changes the DB
void SSDbSqlite::setCorrupt(const char * pczCorruptField,const char * pczCorruptValue)
    {
    const char * pczSection = 
	(strcmp(pczCorruptField,"ExpireTime") == 0) ? "install"
	: (strcmp(pczCorruptField,"ProductLevel") == 0) ? "install"
	: (strcmp(pczCorruptField,"Bits") == 0) ? "install"
	: (strcmp(pczCorruptField,"LicenseType") == 0) ? "install"
	: (strcmp(pczCorruptField,"SN") == 0) ? "install"
	: (strcmp(pczCorruptField,"Machine") == 0) ? "install"
	: (strcmp(pczCorruptField,"LANGUAGE") == 0) ? "runtime"
	: "unknown";
    int iStat = putProfileString(pczSection,pczCorruptField,pczCorruptValue,"set corrupt value",""); 
    if (iStat == 0)
	setSignature();
    logTrace("Setting corrupt to %s,%s status=%d",NN(pczCorruptField),NN(pczCorruptValue),iStat);
    char * pczDump = dumpTables("putProfile (ex)\n",DUMP_PROFILE);
    if (pczDump != NULL)
	{
	logTrace(pczDump);
	free(pczDump);
	}
    }
#endif

#if defined UTIL  // currently only used for the utility version
	// Create the DB. Delete it first if necessary.
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// Do nothing which is site. product, or situation dependent
	// @return 		0 if OK
int SSDbSqlite::create(const char * dbName)
    {
    int iRetval = 0;
    if (access(dbName,F_OK) == 0)
	iRetval = unlink(dbName);
    if (iRetval)
        {
	logTrace("Can't delete existing database '%s'; status=%d",
		 dbName,iRetval);
	if (m_iDebug)
	    fprintf(stderr, "Can't delete existing database '%s'; status=%d\n",
		    dbName,iRetval);
	m_pDb = NULL;
	iRetval = DERR_DB_OPEN;
	}
    else
        {
	iRetval = sqlite3_open(dbName, &m_pDb);
	if (iRetval)
            {
	    logTrace("Can't open database: %s", sqlite3_errmsg(m_pDb));
	    if (m_iDebug)
		fprintf(stderr, "Create Can't open database: %s\n", 
			sqlite3_errmsg(m_pDb));
	    sqlite3_close(m_pDb);
	    m_pDb = NULL;
	    iRetval = DERR_DB_OPEN;
	    }
	else
	    iRetval = SSDb::create();
	}
    return iRetval;
    }
#endif // if defined UTIL

	// Do some query or command to DB
	// @param pczSqlCmd		command to DB
	// @param uFormatSelector	select output format or not supplied
	//				default is DB_TEST
	// @param pczResultBuf		buffer to pack results into, or NULL
	// @return 			SQLITE error code	
int SSDbSqlite::sqlQuery(const char * pczSqlCmd, 
			 DBFORMAT_SEL uFormatSelector,
			 char * pczResultBuf)
    {
    int iRetval = 0;
    // actually, pczResultBuf IS czOutbuf.
    // It should have been cleared by the calling fn. This is just bulletproofing.
    memset(czOutbuf,0,sizeof(czOutbuf));
    iDbRecCount = 0;
    iOID = 0;
    iDbSize = 0;
    uDbFieldCount = 0;
    if (m_pczError != NULL)
	free(m_pczError);
    m_pczError = NULL;
    if ((Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    && (Logger::getTraceLevel() & 2))
	logTrace("SSdbSqlite::sqlQuery (en) format=%d cmd=%s",
	    uFormatSelector,pczSqlCmd);
    if (m_iDebug)
	fprintf(stderr,"SSdbSqlite::sqlQuery (en) cmd='%s'\n",pczSqlCmd);
    switch (uFormatSelector)
	{
	case DB_FULLPATH:    /* get the full path and filename */
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_FullpathCallback, 
				   pczResultBuf,&m_pczError);
	    break;
	case DB_RGB:    /* get the RGB file info for =C */
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_RGBCallback, 
				   pczResultBuf,&m_pczError);
	    break;
	case DB_STATUS: /* get the status info for the UI */
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_UIStatusCallback, 
				   pczResultBuf,&m_pczError);
	    break;
	case DB_ID: /* get the OID of the first record, and count of records */
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_OIDCallback, 
				   NULL,&m_pczError);
	    break;
	case DB_TABLE:
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_TableCallback, 
				   pczResultBuf,&m_pczError);
	    break;
	case DB_ATTRVAL:
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_AttrValCallback,
				   pczResultBuf,&m_pczError);
//	    logTrace("SSdbSqlite::sqlQuery DB_ATTRVAL got |%s|",pczResultBuf);
	    break;
	case DB_COUNT:
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, ss_count, NULL, 
				   &m_pczError);
	    break;
	case DB_TEST:
	default:
	    iRetval = sqlite3_exec(m_pDb, pczSqlCmd, NULL, NULL, &m_pczError);
	    break;
	}
    if ((Logger::getTraceLevel() & TRACE_LVL_SSDb)
	    && (Logger::getTraceLevel() & 2))
        {
	char * pErrMsg = errmsg("");
	logTrace("SSdbSqlite::sqlQuery (ex) returns %d, count=%d iOID=%d err=%s",
		 iRetval,iDbRecCount,iOID,pErrMsg);
	free(pErrMsg);
	}
    if (m_iDebug)
        {
	char * pErrMsg = errmsg("");
	fprintf(stderr,
		"SSdbSqlite::sqlQuery (ex) returns %d, count=%d iOID=%d err=%s\n",
		iRetval,iDbRecCount,iOID,pErrMsg);
	free(pErrMsg);
	}
    return iRetval;
    }

	// Create by calloc an error message consisting of pczFn, 
	// the error from sqlite3, and the sql cmd.
	// Free and/or zero each of the components to indicate they have
	// been used.
	// The resulting string must be freed.
	// @param pczFn		name/description  of fn where error occurred
	// @return		string which must be freed
char * SSDbSqlite::errmsg(const char * pczFn)
    { 
    size_t sz = strlen(sqlite3_errmsg(m_pDb)); 
    //   const char * pRetval = sqlite3_errmsg(m_pDb); 
    if (m_pczError != NULL)
	sz = strlen(m_pczError);
    sz += strlen(m_czSqlCmd) + 50 + strlen(pczFn);
    char * pRetval = (char *)calloc(sz,1);
    if (pRetval != NULL)
        {
	const char * pDbMsg = (m_pczError != NULL) 
	    ? m_pczError : sqlite3_errmsg(m_pDb);
	if ((pDbMsg != NULL) && (strncmp(pDbMsg,"not an er",9) == 0))
	    pDbMsg = "";
	snprintf(pRetval,sz,"%s: %s cmd='%s'",
		 pczFn, pDbMsg,
		 m_czSqlCmd);
	if (m_pczError != NULL)
	    free(m_pczError);
	m_pczError = NULL;
	m_czSqlCmd[0] = '\0';
	}
    else
	pRetval = strdup("Memory failure");
    return pRetval;
    }

/*********************************************************************
 *
 * utility fns - not DB but used in combo with DB operations
 *
 *********************************************************************/
#ifndef __GCC__
void _getRegistryHLMValue(BOOL bVerbose,const char * pczKeyName,
			  const char * pczValName, 
			  char * pczBuf, DWORD * puBufSize)
    {
    HKEY hKey = 0;
    DWORD ulRegStatus = 0;
    if ((*pczKeyName == 'd') || (*pczKeyName == 'D'))
	{
	ulRegStatus = RegOpenKey(HKEY_CLASSES_ROOT,pczKeyName,&hKey);
	if (bVerbose)
	    fprintf(stderr,"\nroot status=%ld - ",ulRegStatus);
	}
    else
	{
	ulRegStatus = RegOpenKey(HKEY_LOCAL_MACHINE,pczKeyName,&hKey);
    //				       "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0",
    //				       &CPUKey);
	if (bVerbose)
	    fprintf(stderr,"\nlocal status=%ld - ",ulRegStatus);
	}
    if (ulRegStatus == 0)
        {
	ulRegStatus = RegQueryValueEx(hKey,pczValName,
				      NULL,NULL,(BYTE *)pczBuf,puBufSize);
	pczBuf[*puBufSize] = '\0'; // make sure null-term
	}
    else
	{
	char errbuf[256];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,ulRegStatus,0,errbuf,sizeof(errbuf),NULL);
	fprintf(stderr,"Error getting key %s: %s\n",pczKeyName,errbuf);
	}
    if (bVerbose)
        fprintf(stderr,
		"_getRegistry of '%s' '%s' "
		"got status=%ld key=x%lX buf=%d='%s' size=%d\n",
		pczKeyName,pczValName,ulRegStatus,(long)hKey,
		*(int *)pczBuf,pczBuf,*(int*)puBufSize);
    if (ulRegStatus)
	{
	char errbuf[256];
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,0,ulRegStatus,0,errbuf,sizeof(errbuf),NULL);
	fprintf(stderr,"Error getting value %s\n",errbuf);
	}
    logTrace("_getRegistry of %s %s "
	     "got status=%ld key=x%lX buf=%d='%s' size=%d",
	     pczKeyName,pczValName,ulRegStatus,(long)hKey,
	     *(int *)pczBuf,pczBuf,*(int*)puBufSize);
    }

typedef struct MSKey_t
    {
    char czKeyName[256];
    char czValName[16];
    uint utype;	// 0 = DWORD, 1= REG_SZ (string) ... 
    } MSKey_T;
#endif

/* calculate and return an integer (about 63 bits) as a string 
 * which is more-or-less characteristic of this computer
 * To avoid overflows, mask off high-order bit
 * @param bVerbose	
 */
const char * SSDb::CalcMachineCode(BOOL bVerbose)
    {
    static char retbuf[D_PRINTBUF];
#ifndef __GCC__
    static MSKey_T keys[] 
      = {
	    {"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0","~MHz",0},
	    {"device\\CLSID","",1}
    //  {"DiskManagement.Connection\\CLSID","",1} // not in win7 ?
        };
    uint uTotal = 0;
    char * czTmpName = tempnam(NULL,"mac");
    char czSystemCall[PATH_MAX];
    for (uint j=0; j<AY_COUNT(keys); j++)
        {
	char buf[256] = "";
	DWORD bufsz = sizeof(buf);
	memset(buf,'\0',sizeof(buf));
	_getRegistryHLMValue(bVerbose,keys[j].czKeyName,keys[j].czValName,
			     buf,&bufsz);
	if (keys[j].utype == 0)
	    {
	    uTotal += *(uint *) buf;
	    if (bVerbose)
		fprintf(stderr,"key |%s,%s| => |x%X|\n",keys[j].czKeyName,keys[j].czValName,buf);
	    }
	else
	    {
	    unsigned long ulVal = strtoul(buf,NULL,16);
	    uTotal += (uint) ulVal;
	    if (bVerbose)
		fprintf(stderr,"key |%s,%s| => |%s| val=x%lX\n",keys[j].czKeyName,keys[j].czValName,buf,ulVal);
	    }
        }
    DWORD uVolSn = 0;
    DWORD uMaxPathLen = 0; // not used
    DWORD uFlags = 0; // not used
    char czVolumeName[128];
    char czFileSysName[128];
    if (GetVolumeInformation(NULL,czVolumeName,sizeof(czVolumeName)-1,
			     &uVolSn,&uMaxPathLen,&uFlags,
			     czFileSysName,sizeof(czFileSysName)-1))
        {
	if (bVerbose)
	    fprintf(stderr,
		    "for current drive volname='%s' fsname='%s' volsn=%d\n",
		    czVolumeName,czFileSysName,uVolSn);
	uTotal += uVolSn;
        }
    if (GetVolumeInformation("C:\\",czVolumeName,sizeof(czVolumeName)-1,
			     &uVolSn,&uMaxPathLen,&uFlags,
			     czFileSysName,sizeof(czFileSysName)-1))
        {
	if (bVerbose)
	    fprintf(stderr,
		    "for drive C: volname='%s' fsname='%s' volsn=%d\n",
		    czVolumeName,czFileSysName,uVolSn);
	uTotal += uVolSn;
        }
    memset(retbuf,0,sizeof(retbuf));
    snprintf(retbuf,sizeof(retbuf)-1,"%08X",uTotal & 0x7FFFFFFF);
    char ipcbuf[2048];
    int ipconfigstat = 0;
    memset(czSystemCall,0,sizeof(czSystemCall));
    memset(ipcbuf,0,sizeof(ipcbuf));
    // use ipconfig to get the mac address
    if (czTmpName != NULL) // we don't handle the possibility it will fail
	{
	snprintf(czSystemCall,sizeof(czSystemCall)-1,"%%systemroot%%\\system32\\ipconfig /all > %s",czTmpName);
	ipconfigstat = system(czSystemCall);  // get ipconfig info
//    int ipconfigstat = system("ipconfig /all > ipc.tmp");  // get ipconfig
	if (ipconfigstat == 0)
	    rsf(czTmpName,ipcbuf,sizeof(ipcbuf),0,0);  // get ipconfig results
	free(czTmpName);
	}
    char * pNext = strtok(ipcbuf,"\n\r");
    // get the Physical Address of the first internet adapter, whatever it is
    while ((pNext != NULL) && (strstr(pNext,"Physical Address") == NULL))
	pNext = strtok(NULL,"\n\r");
    if (pNext != NULL)
	{
	char * pBlank = strrchr(pNext,' ');
	if (bVerbose)
	    printf("desired line is |%s| str=|%s|\n",pNext,pBlank);
	while((pBlank != NULL) && (*pBlank != '\0') && (strlen(retbuf) < sizeof(retbuf)-2))
	    {
	    if (isdigit(*pBlank))
		{
		if (bVerbose)
		    printf("pblank=%c, retbuf=|%s|\n",*pBlank,retbuf);
		retbuf[strlen(retbuf)] = *pBlank;
		}
	    pBlank++;
	    }
	}
    if (bVerbose)
	fprintf(stdout,"ipconfig status=%d will return=%s\n",ipconfigstat,retbuf);
#else
    snprintf(retbuf,sizeof(retbuf)-1,"5A5AB4B4"); // linux ~~~
#endif
    return retbuf;
    }

#ifdef USE_WEBSITE
/* prelim function which mimics what's in OD website
 * Old (OpenDragon) version: just the sum of czMachine & czExpire
 * New version: include part of SN, and checksum
 * @param czMachine	hex 8-digit string
 * @param czSn		serial number
 * @param czValDate	date on which Valcode was put into DB YYYY-MM-DD
 * @return 		SHA1 digest of the input args
 */
const char * SSDb::CalcValCode(const char * czMachine, const char * czSn,
			       const char * czValDate)
    {
//    static char buf[20];
//    ulong ulMachine = strtoul(czMachine,NULL,16);
//    ulong ulExpire = 10 * 365; // days
//    if (czExpire != NULL)
    //       {
//	char czYear[5];
//	strncpy(czYear,czExpire,4);
//	czYear[4] = '\0';
//	char czMonth[3];
//	strncpy(czMonth,czExpire+5,2);
//	czMonth[2] = '\0';
//	ulExpire = 365 * (atoi(czYear)-1970) + 12 * atoi(czMonth); // website uses 1970 as a basis
//	}
//    snprintf(buf,sizeof(buf),"%08lX",ulMachine+ulExpire);

    char basestr[1024];
    static char mimebuf[30];
    sprintf(basestr,"%s%s%sarchaeopteryx",czSn,czMachine,czValDate);
#ifdef __MINGCC__ // ~~~ temp avoid linking in ssl stuff
		  // SSL things cause a link error at runtime (how does that happen?)
		  // linux doesn't currently (2012-12-31) use the web for validation,
		  // but SSDb by default uses SHA1 to create the machine code
                  // (maybe use mysha1.exe or somethng like that as a workaround)
//    byte shabuf[22];
//    memset(shabuf,0,sizeof(shabuf));
//    SHA1((const byte *)basestr,strlen(basestr),shabuf);
    int j=0;
    char * pMime = mimebuf;
    for (j=0; j<7; j++)
	{
	uint bits = (0xFF0000 & shabuf[j*3]<<16)|(0xFF00 & shabuf[j*3+1]<<8)|(0xFF & shabuf[j*3+2]);
//	    printf("j=%d bits=x%X\n",j,bits);
	int jj;
	uint mask[] = {0xFC0000,0x3F000,0xFC0,0x3F};
	char xlate[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		           "abcdefghijklmnopqrstuvwxyz"
			   "01234567890+/";
	for (jj=0; jj<4; jj++) // pull the bits 3 at a time
	    {
	    byte oct = (bits & mask[jj]) >> (3-jj)*6;
//		printf("    jj=%d mask=0x%X oct=x%X\n",jj,mask[jj],oct);
	    *pMime++ = xlate[oct];
	    }
	}
    mimebuf[27] = '\0'; // match Perl's SHA1_base64 which gives 27 chars
#else
    strcpy(mimebuf,basestr);
#endif // __MINGCC__
    return mimebuf;
    }
#else
/* prelim function which mimics what's in OD website
 * Old (OpenDragon) version: just the sum of czMachine & czExpire
 * New version: include part of SN, and checksum
 * @param czMachine	hex 8-digit string
 * @param czSn		serial number - not currently used
 * @param czExpire	expiration date as YYYY-MM
 */
const char * SSDb::CalcValCode(const char * czMachine, const char * czSn,
			       const char * czExpire)
    {
    static char buf[20];
    ulong ulMachine = strtoul(czMachine,NULL,16);
    ulong ulExpire = 10 * 365; // days
    if (czExpire != NULL)
        {
	char czYear[5];
	strncpy(czYear,czExpire,4);
	czYear[4] = '\0';
	char czMonth[3];
	strncpy(czMonth,czExpire+5,2);
	czMonth[2] = '\0';
	ulExpire = 365 * (atoi(czYear)-1970) + 12 * atoi(czMonth); // website uses 1970 as a basis
	}
    snprintf(buf,sizeof(buf),"%08lX",ulMachine+ulExpire);
    return buf;
    }
#endif // ifdef USE_WEBSITE

// For license types with a timeout, check current state
// The checking depends on LicenseType
// @return		0 => OK
//			1 => not registered but not yet timedout
//			2 => timed out
//			3 => DB error or inconsistency
int SSDb::queryExpiration()
    {
#undef FN_NAME
#define FN_NAME "SSDb::queryExpiration"
    int iRetval = 2;
    const char * pLicenseType 
	= getProfileString("install","LicenseType",NULL,NULL);
    if ((strcmp(pLicenseType,"KEYREQ") == 0)
	|| (strcmp(pLicenseType,"KEYINI") == 0)
	|| (strcmp(pLicenseType,"KEYWEB") == 0))
	iRetval = 0;
    else if (strcmp(pLicenseType,"WEBSGL") == 0)
	{
	const char * pExp = getProfileString("install","ExpireTime",0,0);
	if (pExp == NULL)
	    iRetval = 3; // DB error
	else
	    {
	    uint uExpireMonth = atoi(pExp); // when the DB says it expires
	    const char * pValCode 
		= getProfileString("install","ValCode",NULL,NULL);
	    time_t now = time(NULL);
	    struct tm * ptm = gmtime(&now);
	    uint uThisMonth = (ptm->tm_year - 70) * 12 + ptm->tm_mon;
	    logTrace(FN_NAME " expiremonth from DB=%d now=%d",
		    uExpireMonth,uThisMonth);
	    if ((pValCode != NULL) && (strspn(pValCode," ") < strlen(pValCode)))
		iRetval = 0;
	    else if (uThisMonth < uExpireMonth)
		iRetval = 1;
	    }
	}
    else // ~~~ are there more cases?
	iRetval = 0;
    logTrace(FN_NAME " (ex) return %d",iRetval);
    return iRetval;
    }

#if DRAGON_VER >= 6
// set or check DegradedTime,product (based on SN),InstallTime
// This is called by SSDp::checkProductStatus but retruned value not used
// Look at S/N. 
// This tries to set DegradedTime in DB but fails; no side effects
//   If installed as EVAL then compare InstalledTime to iDays
//   If installed as PROF/ACAD 
//	then if current ProductLevel matches and DegradedTime defined
//	   clear DegradedTime
//	else if DegradedTime == 0 or not defined, set it
//	else compare DegradedTime to iDays
// called (only) from SSDp::checkProductStatus 
// @return 	0 if OK
//		2 if expired
#define SECPERDAY (60 * 60 * 24)
int SSDb::queryExpirationDays(int iDays)
    {
    int iRealProductLevel = getProductLevel(TRUE);
    int iCurProductLevel = getProductLevel(FALSE);
    const char * czInstallTime = getProfileString("install","InstallTime",
					    "queryExpiration",NULL);
    long lInstallTime = 
      (czInstallTime) ? strtol(czInstallTime,NULL,10) : -1;
    const char * czDegradedTime = getProfileString("runtime","DegradedTime",
					    "queryExpiration",NULL);
    long lDegradedTime = 
      (czDegradedTime) ? strtol(czDegradedTime,NULL,10) : -1;
    time_t ulNow = time(NULL);
    int iDaysAgo = 0;
    if(iRealProductLevel == DEMO_PRODUCT) 
	iDaysAgo = (ulNow - lInstallTime)/SECPERDAY;
    else if ((iRealProductLevel == iCurProductLevel)
	&& ((iRealProductLevel == ACAD_PRODUCT) 
	    || (iRealProductLevel == PROF_PRODUCT)))
        { // no problem
	if (lDegradedTime > 0)
	    putProfileString("runtime","DegradedTime","0");
        }
    else if ((iRealProductLevel == ACAD_PRODUCT) 
	    || (iRealProductLevel == PROF_PRODUCT))
        { // degraded
	if (lDegradedTime <= 0)
	    {
	    char czTimeBuf[20];
	    snprintf(czTimeBuf,sizeof(czTimeBuf),"%ld",ulNow);
	    putProfileString("runtime","DegradedTime",czTimeBuf);
	    lDegradedTime = ulNow; // so we can test below
	    }
	iDaysAgo = (lDegradedTime >= 0) 
	  ? (ulNow - lDegradedTime)/SECPERDAY : 0;
        }
    return (iDaysAgo > iDays) ? 2 : 0;
    }
#endif

#if DRAGON_VER >= 6
	// get IPC_STYLE from the DB
	// Currently this applies only to communications with the viewport	
IPC_STYLE_t SSDb::getIpcStyle(MODULE_INDICES uModule)
    {
    const char * czStyle = getProfileString("runtime","IPC","getIpcStyle",NULL);
    /* MODULE_INDICES defined in dragonOb.h */
    return ((uModule < MODULE_VIEWPORT_1) || (uModule > MODULE_VIEWPORT_4)) ? IPC_CLASSIC
	: (czStyle == NULL) ? IPC_CLASSIC
	: (strcmp(czStyle,"XML") == 0) ? IPC_XML
	: (strcmp(czStyle,"URL") == 0) ? IPC_URL
	: (strcmp(czStyle,"SOCKET") == 0) ? IPC_SOCKET
	: IPC_CLASSIC ;
    }
#endif

#define DB_NAME "dragon.db"
#define DB_STATUS_TABLE "status"

void SSDB_END() { puts(FIL_ID); }

#if defined TEST
// create a unit test version.
// This isn't used in the system, so adapt the code as needed
// during testing
int main(int argc, char **argv)
    {
    int rc;
    if(( argc > 1 ) && (strncmp(argv[1],"-",1) == 0))
        {
	fprintf(stderr, "Usage: %s dump\n\tor\n", argv[0]);
	fprintf(stderr, "Usage: %s SQL-STATEMENT\n", argv[0]);
	exit(1);
	}
    SSDbSqlite * pDb = new SSDbSqlite(1,1);
    if (pDb->init(DB_NAME,TRUE))
        {
	fprintf(stderr, "Test Main Can't open database: %s\n", 
		pDb->errmsg("TEST"));
	delete pDb;
	exit(1);
	}
    if(( argc > 0 ) && (strcmp(argv[1],"dump") == 0))
        {
	char * pczDump = pDb->dumpTables("TEST\n");
	if (pczDump != NULL)
	    {
	    printf(pczDump);
	    free(pczDump);
	    }
	delete pDb;
	exit(0);
	}
/*
    rc = pDb->initFromCfg();
    if( rc != 0 )
        {
	fprintf(stderr, "SQL error %d in initFromCfg: %s\n", 
		rc,pDb->errmsg("TEST"));
	}
    pDb->putPath("/jim/jack/joe","some quals",1);
    pDb->putFile("cyrano.img",3);
    pDb->putCurrent("M",0,"/home/fred/indomdm.img");
	printf("%s\n",pDb->dumpTables());
*/
    rc = pDb->sqlQuery(argv[1],DB_TABLE);
    if( rc != SQLITE_OK )
        {
	fprintf(stderr, "SQL error: %s\n", pDb->errmsg("TEST"));
	}
//    printf("Found %d records totalling %d long\n", iDbRecCount,iDbSize);
    if (iDbSize > 0)
        {
	char * pczOutbuf = (char *)calloc(iDbSize,1);
	if (pczOutbuf != NULL)
	    {
	    rc = pDb->sqlQuery(argv[1],DB_TABLE,pczOutbuf);
	    printf("%s\n", pczOutbuf);
	    free(pczOutbuf);
	    }
	}
    delete pDb;
    return 0;
    }
#endif // TEST

#if defined UTIL

void usage(const char * name)
        {
	fprintf(stderr, "Usage: %s [-c | -d | -e stmt] [-v]\n", name);
	fprintf(stderr, "    -c       create the DB\n");
	fprintf(stderr, "    -d       dump the DB\n");
	fprintf(stderr, "    -e stmt  execute an SQL statement on the DB\n");
	fprintf(stderr, "    		(stmt must be quoted)\n");
	fprintf(stderr, "    -m       calculate and show the Machine Code\n");
	fprintf(stderr, "    -v       for verbose\n");
	exit(1);
	}

// create a utility executable which can:
// 1. create the Dragon DB
// 2. Examine the Dragon DB
int main(int argc, char **argv)
    {
    int rc = 0;
    int iOp = 0;  // 'C' or 'D' or 'E' or 'M'
    int iStatus = 0;
    char * pCmd = NULL;
    BOOL bVerbose = FALSE;
//    fprintf(stderr,"argc = %d\n",argc);
    while(++rc < argc)
        {
	if (strcasecmp(argv[rc],"-c") == 0)
	    iOp = 'C';
	else if (strcasecmp(argv[rc],"-d") == 0)
	    iOp = 'D';
	else if (strcasecmp(argv[rc],"-e") == 0)
	    {
	    pCmd = strdup(argv[++rc]);
	    if (pCmd != NULL)
		iOp = 'E';
	    else
	        {
		fprintf(stderr,"Error unable to strdup command '%s'\n",
			argv[rc]);
		exit(1);
		}
	    }
	else if (strcasecmp(argv[rc],"-m") == 0)
	    iOp = 'M';
	else if (strcasecmp(argv[rc],"-v") == 0)
	    bVerbose = TRUE;
	else
	    usage(argv[0]);
	}
    SSDbSqlite * pDb = new SSDbSqlite(bVerbose,bVerbose);
    switch (iOp)
	{
	case 'C':
	    iStatus = pDb->create(DB_NAME);
	    break;
	case 'D':
	case 'E':
	    iStatus = pDb->init(DB_NAME,TRUE);
	    break;
	case 'M':
	    break;
	default:
	    fprintf(stderr,"No operation specified\n");
	    delete pDb;
	    usage(argv[0]);
	    exit(1);
	    break;
	}
    if (iStatus == DERR_FILE_ACCESS)
        {
	fprintf(stderr, "Database %s missing\n", DB_NAME);
	exit(1);
	}
    else if (iStatus)
        {
	fprintf(stderr, "SSDb::Main Can't open database: %s\n", 
		pDb->errmsg(DB_NAME));
	delete pDb;
	exit(1);
	}
    switch (iOp)
	{
	case 'D':
	    {
	    char * pczDump = pDb->dumpTables("",0);
	    if (pczDump != NULL)
	        {
		printf(pczDump);
		free(pczDump);
	        }
	    }
	    break;
	case 'E':
	    iStatus = pDb->sqlQuery(pCmd,DB_TABLE);
	    if( iStatus != SQLITE_OK )
	        {
		fprintf(stderr, "SQL error: %s\n", pDb->errmsg("DB_NAME"));
	        }
	    if (iDbSize > 0)
	        {
		char * pczOutbuf = (char *)calloc(iDbSize,1);
		if (pczOutbuf != NULL)
		    {
		    rc = pDb->sqlQuery(pCmd,DB_TABLE,pczOutbuf);
		    printf("%s\n", pczOutbuf);
		    free(pczOutbuf);
		    }
		}
	    break;
	case 'M':
	    {
	    const char * pMachineCode = pDb->CalcMachineCode(bVerbose);
	    printf("Machine Code = %s\n",pMachineCode);
	    }
	    break;
	default:
	    break;
	}
    delete pDb;
    return 0;
    }
#endif // UTIL
