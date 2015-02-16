/*
 *	filename SSDb.h
 *		$Id: SSDb.h,v 1.39 2014/12/29 03:28:29 rudahl Exp $
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
 * $Id: SSDb.h,v 1.39 2014/12/29 03:28:29 rudahl Exp $
 * $Log: SSDb.h,v $
 * Revision 1.39  2014/12/29 03:28:29  rudahl
 * convert to using dragon version number
 *
 * Revision 1.38  2014/12/10 02:55:19  rudahl
 * lint for new mingw
 *
 * Revision 1.37  2014/12/05 12:32:30  rudahl
 * added ifdefs to match DragonProf and OpenDragon
 *
 * Revision 1.36  2014/04/01 07:24:45  rudahl
 * lint esp from old mingc
 *
 * Revision 1.35  2013/01/03 13:53:04  rudahl
 * build linux kit
 *
 * Revision 1.34  2012/05/02 11:40:27  rudahl
 * implemented WEBSGL enforcement
 *
 * Revision 1.33  2012/04/15 04:46:45  rudahl
 * support internet licensing
 *
 * Revision 1.32  2010/11/14 19:32:14  rudahl
 * added creation of DROF EVAL version
 *
 * Revision 1.31  2008/10/14 08:40:21  rudahl
 * documentation
 *
 * Revision 1.30  2008/10/09 05:38:21  rudahl
 * minor fixes for Vista64
 *
 * Revision 1.29  2008/04/26 09:48:05  rudahl
 * improved copyrights, tracing
 *
 * Revision 1.28  2007/09/30 09:10:42  rudahl
 * fixul VDecorate table
 *
 * Revision 1.27  2007/09/01 13:28:41  rudahl
 * added and fixed server DB access
 *
 * Revision 1.26  2007/08/19 15:37:52  rudahl
 * working on v5.12
 *
 * Revision 1.25  2007/08/12 04:08:44  rudahl
 * completed adaptations for cgDb
 *
 * Revision 1.24  2007/08/11 09:30:26  rudahl
 * improve getFile, get,putVCurrent
 *
 * Revision 1.23  2007/08/10 10:42:05  rudahl
 * added getFile
 *
 * Revision 1.22  2007/08/10 08:58:12  rudahl
 * further impl of DB fns for server
 *
 * Revision 1.21  2007/08/09 02:01:38  rudahl
 * add fns to access VCurrent table
 *
 * Revision 1.20  2007/08/07 02:36:58  rudahl
 * adding tables for viewport
 *
 * Revision 1.19  2007/06/19 05:52:00  rudahl
 * fine-tuning the KEYREQ
 *
 * Revision 1.18  2007/06/17 10:41:35  rudahl
 * fine-tuning on install DB and Hasp key stuff
 *
 * Revision 1.17  2007/05/31 09:43:20  rudahl
 * moved SSDb to ipc
 *
 * Revision 1.16  2007/05/30 14:55:42  rudahl
 * adapt to setup initializing DB
 *
 * Revision 1.15  2006/01/26 06:57:26  rudahl
 * added schema version
 *
 * Revision 1.14  2006/01/14 11:48:48  rudahl
 * working on scripting
 *
 * Revision 1.13  2005/12/24 04:42:35  rudahl
 * added getProfileString, putTracingLocal
 *
 * Revision 1.12  2005/12/10 11:49:31  rudahl
 * fixed conditional dump flags
 *
 * Revision 1.11  2005/12/04 11:17:34  rudahl
 * made dumpTables more selective
 *
 * Revision 1.10  2005/11/25 12:35:11  rudahl
 * added DB use to chq
 *
 * Revision 1.9  2005/11/24 09:19:28  rudahl
 * added SCRIPTVARS; modified CHECKSUMS; improved debug info
 *
 * Revision 1.8  2005/11/24 08:18:00  rudahl
 * create a utility version of SSDb
 *
 * Revision 1.7  2005/11/05 09:57:21  rudahl
 * replaced the Parameter class by DB use
 *
 * Revision 1.6  2005/10/22 04:25:01  rudahl
 * improved getCurrent; added getFiles
 *
 * Revision 1.5  2005/10/02 08:13:37  rudahl
 * working on persistent data
 *
 * Revision 1.4  2005/10/01 11:11:56  rudahl
 * adding persistent storage to Ipc and SS
 *
 * Revision 1.3  2005/09/27 03:11:41  rudahl
 * integrating SSDb into Executable
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
 * 5.7 	2005-9-22 ktr	new
 *	2005-11-24 ktr	added create()
 * 5.10	2007-05-27 ktr	moved DB definition from SSDb.cpp to here
 * 5.11	2007-08-06 ktr	added VCurrent, VDecorations; upped schema version
 * 6.1	2010-11-14 ktr	added queryExpiration
 * 6.3	2012-12-28 ktr	added IpcStyle
 ********************************************************************
 */

#ifndef SSDB_H
#define SSDB_H 1

#define TRACE_LVL_SSDb		0x0100000

#ifndef DRAGONOBJECT_H
typedef unsigned int MODULE_INDICES;
#endif // ! DRAGONOBJECT_H
#if ! defined IPCFILE_H && ! defined IPCWRAP_H
typedef unsigned int IPC_STYLE_t;
#endif // ! IPCFILE_H

typedef enum 
    {
    DB_TEST,	/* no operation, just do the query return status */
    DB_COUNT, 	/* count the responses into iDbCount */
    DB_ATTRVAL,	/* format as attribute=value; pairs */
    DB_TABLE,	/* format as table */
    DB_ID,	/* get the OID of the first record, and count of records */
    DB_STATUS, 	/* STATUS for UI */
    DB_RGB, 	/* RGB files for server =C */
    DB_FULLPATH, /* full path/filename */
   } DBFORMAT_SEL;

//Dragon Prof uses schema 1.3; opendragon uses 1.2
// about 100 lines are copied from the OpenDragon file
#if DRAGON_VER >= 6
// tables which need to exist in the DB
typedef enum 
    {
    DB_TRACING,
    DB_LEGALVALS,
    DB_SCRIPTVARS,
    DB_PROFILE,
    DB_HISTORY,
    DB_CHECKSUMS,
    DB_PATHS,
    DB_FILES,
    DB_CURRENT,
    DB_VCurrent,
    DB_VDecorations
//    DB_VirtualSchema,
//    DB_VirtualIntData,
//    DB_VirtualStringData
    } DBTABLE_SEL ;

// tables which need to exist in the DB
// This list must match the above enum
#define TABLE_LIST \
	"TRACING",	/* only if m_iTrace */ \
	"LEGALVALS",	/* limit permitted strings in some fields */ \
	"SCRIPTVARS", 	/* variables; for scripts, mostly */ \
	"PROFILE",	/* replace PrivateProfile, .cfg */ \
	"HISTORY",	/* prior system runs */ \
	"CHECKSUMS",	/* of the system components */ \
	"PATHS", \
	"FILES", \
	"CURRENT",	/* =M, etc */ \
        "VCurrent",     /* current viewport locations,sizes, files */ \
        "VDecorations"  /* current viewport decorations */

//	"VirtualSchema"	/* schema for virtual data */ 
//	"VirtualIntData"     /* data spec'd by user; maybe several tables */ 
//	"VirtualStringData"  /* data spec'd by user; maybe several tables */ 

// Definitions for above tables. Must match.
// in all cases, the OID is the index and is autogen
#define FIELD_LIST \
	"_when timestamp default CURRENT_TIMESTAMP, which char(16)," \
		"why char(16), what char(256), who char(256)", \
	"dbtable char(16), field char(16), string char(16), " \
		"unique(dbtable,field,string)", \
	"name char(64), ndx char(64) default '', value char(64)",/*variables*/\
 	"section char(32), name char(32), value char(32), " \
		"unique(section,name,value)", /* profile */ \
	"start_stop char(5) NOT NULL,"\
		"date timestamp default CURRENT_TIMESTAMP",\
	"file char(32), checksum char(32), date date, unique(file)",\
		 /* checksums */ \
	"path char(512) NOT NULL, qual char(32) default '', "\
		"dpath int default 0,unique(path)", \
	"name char(256) NOT NULL, pathId int,unique(name,pathId)", \
	"idstr char(16) NOT NULL unique, scriptName char(16), " \
		"fileId int default -1, opKey char(8) default '',"\
		" pixels int default -1, lines int default -1, "\
		"bWritten int default 0, argVal char(32) default '' ",\
		 /* CURRENT: argVal for non-file entries (e.g. VP# ) */\
	"idstr char(16) NOT NULL, vp int, argVal char(32), "\
		"unique(idstr,vp)", \
		/* VCurrent: vp=-1 is SCREEN; argVal depends on idstr */ \
	"idstr char(16) NOT NULL, vp int, ndx int, x int, y int, " \
		"ref char(16), color int, size int, font char(64), "\
		"string varchar, " \
		"unique(idstr,vp,ndx)", \
		/* VDecorations: index for TXT, LEGITEM; ref=e.g. image, page*/
      /* NOTE when adding table must also add FIELD_WIDTHS in SSDb.cpp */

#define LEGALVALS \
	"'PROFILE','section','db'", \
	"'PROFILE','section','processId'", \
	"'PROFILE','section','site'", \
	"'PROFILE','section','install'", \
	"'PROFILE','section','trace'", \
	"'PROFILE','section','runtime'", \
	"'PROFILE','name','schemaVersion'", /* db */ \
	"'PROFILE','name','created'", \
	"'PROFILE','name','SS'",  /* processId */ \
	"'PROFILE','name','DS'", \
	"'PROFILE','name','V0'", \
	"'PROFILE','name','V1'", \
	"'PROFILE','name','UI'", \
	"'PROFILE','name','DPATH'",  /* site */ \
	"'PROFILE','name','WPATH'", \
	"'PROFILE','name','KPATH'", \
	"'PROFILE','name','SPATH'", \
	"'PROFILE','name','UPATH'", \
	"'PROFILE','name','VIEWPORT-0'", /* runtime */ \
	"'PROFILE','name','VIEWPORT-1'", \
	"'PROFILE','name','VIEWPORT-2'", \
	"'PROFILE','name','VIEWPORT-3'", \
	"'PROFILE','name','VIEWPORT-4'", \
	"'PROFILE','name','DRAGONUI'", \
	"'PROFILE','name','LANGUAGE'",\
	"'PROFILE','name','BUILDDATE'", /* install info */\
	"'PROFILE','name','InstallDate'", \
	"'PROFILE','name','InstallTime'", \
	"'PROFILE','name','OsVersion'", \
	"'PROFILE','name','ProcessorBits'", \
	"'PROFILE','name','ExpireDate'", \
	"'PROFILE','name','ExpireTime'", \
	"'PROFILE','name','LicenseType'", \
	"'PROFILE','name','RELEASE'", \
	"'PROFILE','name','PRODUCT'", \
	"'PROFILE','name','WORKING_LINES'", \
	"'PROFILE','name','WORKING_PIXELS'", \
	"'PROFILE','name','WORKING_IMAGES'", \
	"'PROFILE','name','SN'", \
	/* "'PROFILE','name','Key'", */\
	"'PROFILE','name','Machine'", \
	"'PROFILE','name','ValDate'", \
	"'PROFILE','name','ValCode'", \
	/* ProductLevel may change to Demo, but get from SN can restore it */ \
	"'PROFILE','name','ProductLevel'", /* current effective level not higher than SN[7] */ \
	"'PROFILE','name','Bits'", \
	"'PROFILE','name','IPC'", \
	"'PROFILE','name','Signature'", /* checksum - this must be the last 'name' entry */\
	"'CURRENT','idstr','M'", \
	"'CURRENT','idstr','R'", \
	"'CURRENT','idstr','G'", \
	"'CURRENT','idstr','B'", \
	"'CURRENT','idstr','SIGS'", \
	"'CURRENT','idstr','POLYGONS'", \
	"'CURRENT','idstr','COLORFILE'", \
	"'CURRENT','idstr','KPATH'", \
	"'CURRENT','idstr','SPATH'", \
	"'CURRENT','idstr','UPATH'", \
	"'CURRENT','idstr','WPATH'", \
	"'CURRENT','idstr','VP'", \
	"'VCurrent','idstr','VPSize'",      /* format: lines,pixels */ \
	"'VCurrent','idstr','VPLocation'",  /* format: lines,pixels */ \
	"'VCurrent','idstr','DefaultSize'", /* derived from .cfg */ \
	"'VCurrent','idstr','DefaultLocation'", \
	"'VCurrent','idstr','ImageOrigin'", /* format: lines,pixels */ \
	"'VCurrent','idstr','ImageScale'", \
	"'VCurrent','idstr','RegionSize'", \
	"'VCurrent','idstr','OP'",          /* 'RGB', 'C', 'G' */ \
	"'VCurrent','idstr','Stretch'",     /* 'type= [UBP= LBP=]; [..] ' */ \
	"'VCurrent','idstr','ImageFiles'",  /* 1 or 3 indices into FILES */ \
	"'VCurrent','idstr','ColorFiles'",  /* index into FILES */ \
	"'VDecorations','idstr','TXT'", \
	"'VDecorations','idstr','LEGEND'", \
	"'VDecorations','idstr','LEGITEM'"

#define CURRENT_ENTRIES \
	"'M','=M'", \
	"'R','=R'", \
	"'G','=G'", \
	"'B','=B'", \
	"'SIGS','(CURSIG'", \
	"'POLYGONS','(CURPLY'", \
	"'COLORFILE','(CURCOL'", \
	"'WPATH','-WPATH'", \
	"'SPATH',''", \
	"'UPATH',''", \
	"'KPATH',''", \
	"'VP','(CURVP'"

// list of rows which should be deleted at the start of each run
// format is, alternately, table name followed by row selector
#define ZAP_ROWS \
	"PROFILE","section='processId'",	/* all process IDs */ \
	"PROFILE","section='trace'",		/* all trace flags */ \
	"PROFILE","section='runtime'",		/* all runtime info */ \
	"CURRENT","",				/* all current info ? */ \
	"TRACING","",				/* all rows from TRACING */ \
	"SCRIPTVARS","",			/* all rows from SCRIPTVARS */\
	"FILES","",				/* all rows from FILES */ \
	"PATHS","",				/* all rows from PATHS */ \
	"VCurrent","",				/* all rows from VCurrent */ 

#define SCHEMA_VERSION "1.3"
#else
// this is the OpenDragon schema
// tables which need to exist in the DB
typedef enum 
    {
    DB_TRACING,
    DB_LEGALVALS,
    DB_SCRIPTVARS,
    DB_PROFILE,
    DB_HISTORY,
    DB_CHECKSUMS,
    DB_PATHS,
    DB_FILES,
    DB_CURRENT,
    DB_VDecorations,
    DB_VirtualSchema,
    DB_VirtualIntData,
    DB_VirtualStringData
    } DB_TABLES_LIST_t;

// tables which need to exist in the DB
// This list must match the above enum
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

//	"VDecorations"	/* viewport decorations */ 
//	"VirtualSchema"	/* schema for virtual data */ 
//	"VirtualIntData"     /* data spec'd by user; maybe several tables */ 
//	"VirtualStringData"  /* data spec'd by user; maybe several tables */ 

// Definitions for above tables. Must match.
// in all cases, the OID is the index and is autogen
#define FIELD_LIST \
	"_when timestamp default CURRENT_TIMESTAMP, which char(16)," \
		"why char(16), what char(256), who char(256)", \
	"dbtable char(16), field char(16), string char(16), " \
		"unique(dbtable,field,string)", \
	"name char(64), ndx char(64) default '', value char(64)",/*variables*/\
 	"section char(32), name char(32), value char(32), " \
		"unique(section,name,value)", /* profile */ \
	"start_stop char(5) NOT NULL,"\
		"date timestamp default CURRENT_TIMESTAMP",\
	"file char(32), checksum char(32), date date, unique(file)",\
		 /* checksums */ \
	"path char(512) NOT NULL, qual char(32) default '', "\
		"dpath int default 0,unique(path)", \
	"name char(256) NOT NULL, pathId int,unique(name,pathId)", \
	"idstr char(16) NOT NULL unique, scriptName char(16), " \
		"fileId int default -1, opKey char(8) default '',"\
		" pixels int default -1, lines int default -1, "\
		"bWritten int default 0, argVal char(32) default ''"
		 /* CURRENT: argVal for non-file entries (e.g. VP# ) */

#define LEGALVALS \
	"'PROFILE','section','db'", \
	"'PROFILE','section','processId'", \
	"'PROFILE','section','site'", \
	"'PROFILE','section','install'", \
	"'PROFILE','section','trace'", \
	"'PROFILE','section','runtime'", \
	"'PROFILE','name','schemaVersion'", /* db */ \
	"'PROFILE','name','created'", \
	"'PROFILE','name','SS'",  /* processId */ \
	"'PROFILE','name','DS'", \
	"'PROFILE','name','V0'", \
	"'PROFILE','name','V1'", \
	"'PROFILE','name','UI'", \
	"'PROFILE','name','DPATH'",  /* site */ \
	"'PROFILE','name','WPATH'", \
	"'PROFILE','name','KPATH'", \
	"'PROFILE','name','SPATH'", \
	"'PROFILE','name','UPATH'", \
	"'PROFILE','name','VIEWPORT-0'", /* runtime */ \
	"'PROFILE','name','VIEWPORT-1'", \
	"'PROFILE','name','VIEWPORT-2'", \
	"'PROFILE','name','VIEWPORT-3'", \
	"'PROFILE','name','VIEWPORT-4'", \
	"'PROFILE','name','DRAGONUI'", \
	"'PROFILE','name','LANGUAGE'",\
	"'PROFILE','name','BUILDDATE'", /* install info */\
	"'PROFILE','name','InstallDate'", \
	"'PROFILE','name','InstallTime'", \
	"'PROFILE','name','ExpireDate'", \
	"'PROFILE','name','ExpireTime'", \
	"'PROFILE','name','LicenseType'", \
	"'PROFILE','name','RELEASE'", \
	"'PROFILE','name','PRODUCT'", \
	"'PROFILE','name','WORKING_LINES'", \
	"'PROFILE','name','WORKING_PIXELS'", \
	"'PROFILE','name','WORKING_IMAGES'", \
	"'PROFILE','name','SN'", \
	/* "'PROFILE','name','Key'", */\
	"'PROFILE','name','Machine'", \
	"'PROFILE','name','ValDate'", \
	"'PROFILE','name','ValCode'", \
	"'PROFILE','name','ProductLevel'", /* current effective level not higher than SN[7] */ \
	"'PROFILE','name','Bits'", \
	"'PROFILE','name','Signature'", /* checksum */\
	"'CURRENT','idstr','M'", \
	"'CURRENT','idstr','R'", \
	"'CURRENT','idstr','G'", \
	"'CURRENT','idstr','B'", \
	"'CURRENT','idstr','SIGS'", \
	"'CURRENT','idstr','POLYGONS'", \
	"'CURRENT','idstr','COLORFILE'", \
	"'CURRENT','idstr','KPATH'", \
	"'CURRENT','idstr','SPATH'", \
	"'CURRENT','idstr','UPATH'", \
	"'CURRENT','idstr','WPATH'", \
	"'CURRENT','idstr','VP'"

#define CURRENT_ENTRIES \
	"'M','=M'", \
	"'R','=R'", \
	"'G','=G'", \
	"'B','=B'", \
	"'SIGS','(CURSIG'", \
	"'POLYGONS','(CURPLY'", \
	"'COLORFILE','(CURCOL'", \
	"'WPATH','-WPATH'", \
	"'SPATH',''", \
	"'UPATH',''", \
	"'KPATH',''", \
	"'VP','(CURVP'"

// list of rows which should be deleted at the start of each run
// format is, alternately, table name followed by row selector
#define ZAP_ROWS \
	"PROFILE","section='processId'",	/* all process IDs */ \
	"PROFILE","section='trace'",		/* all trace flags */ \
	"PROFILE","section='runtime'",		/* all runtime info */ \
	"CURRENT","",				/* all current info ? */ \
	"TRACING","",				/* all rows from TRACING */ \
	"SCRIPTVARS","",			/* all rows from SCRIPTVARS */\
	"FILES","",				/* all rows from FILES */ \
	"PATHS","",				/* all rows from PATHS */ 

#define SCHEMA_VERSION "1.2"

#endif

class SSDb : public OB
    {
    public:
	// simply create an object and set properties to default
	// @param iDebug	debug level if > than set by OB::OB
	// @param iTrace	trace level if > than set by OB::OB
	SSDb(int iDebug=0, int iTrace=0);

	// Open the DB if it exists, create it if it doesn't exist
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// Do nothing which is site. product, or situation dependent
	// In other words, this is NOT a validation step.
	// @param bPreserve	if TRUE, do nothing except open the DB
	// @return 		0 if OK
	int init(BOOL bPreserve= FALSE);

	// Create the DB.
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// @return 		0 if OK
	int create();

	const char * calcTimeStamp(char * pczBuf,size_t iBufSize);

	// Load data from .cfg file, plus other locations (s/n, etc)
	// @return		0 if OK
	int initFromCfg();

	// get the number of matches found in recent query 
//	int getRecCount();

	// put an entry into the TRACING table at current time
	// does not check for already exists, since each is unique
	// @param pczWhich	executable 
	// @param pczWhy	e.g. error, exec, etc
	// @param pczWhat	did they do
	// @param pczWho	class and function name, other info
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	int putTracing(const char * pczWhich, 
		       const char * pczWhy,
		       const char * pczWhat, 
		       const char * pczWho);

	// factorization fos use within SSdb fns
	void putTracingLocal(const char * pczWhich,
			     const char * pczWhy,
			     const char * pczWho);

	// put an entry into the HISTORY table
	// does not check for already exists, since each is unique
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	int putHistory(const char * pczStartStop,
		       const char * pczWhich = NULL, 
		       const char * pczWho = NULL);

	// put an entry into the PROFILES table
	// verifies that pczName and pczSection are valid values
	// checks 3 possibilities: current value already there? do nothing
	//			   entry already exists? update value
	//			   no entry? add one
	// @param which, who, why are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_CONFLICT if invalid entry
	//			DERR_DB_SQL if DB error
	int putProfileString(const char * pczSection, 
			     const char * pczName,
			     const char * pczValue,
			     const char * pczWhich = NULL, 
			     const char * pczWho = NULL);

	// get an entry from the PROFILE table
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		(volatile) string value from table if OK
	//			else NULL
	const char * getProfileString(const char * pczSection, 
				      const char * pczName,
				      const char * pczWhich, 
				      const char * pczWho);

	// put an entry to the VCurrent table
	// @param which, who	are for tracing. Not initially implemented.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	//			DERR_DB_CONFLICT if pczIdStr unknown
	//			DERR_FN_ARG2 if pczValue is file with no path
	int putVCurrentString(const char * pczIdstr,
			    int iVp,
			    const char * pczArgVal,
			    const char * pczWhich, 
			    const char * pczWho);

	// get an entry from the VCurrent table
	// @param which, who	are for tracing. Not initially implemented.
	//			if pczWhich is NULL, don't trace this call
	// @return		(volatile) string value from table if OK
	//			else NULL
	const char * getVCurrentString(const char * pczIdstr,
				     int iVp,
				     const char * pczWhich, 
				     const char * pczWho);

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
	// @param pczValue	value per iWhichVal
	// @param iPixels	size of PROCESSED image (iwhich < 2)
	// @param iLines 	size of PROCESSED image (iwhich < 2)
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	//			DERR_DB_CONFLICT is pczIdStr unknown
	//			DERR_FN_ARG2 if pczValue is file with no path
	int putCurrent(const char * pczIdStr, 
		       int iWhichVal,
		       const char * pczValue, 
		       int iPixels = -1, int iLines = -1, 
		       const char * pczWhich = NULL, 
		       const char * pczWho = NULL);

	// put an entry into the PATHS table if not already exists
	// use either insert or update, as needed
	// @param pczPath	complete path, using '/' separators
	//   the following are used to update any previously-existing record
	// @param pczQuals	if NON-NULL, update any entry to new values
	// @param bDpath	TRUE is this is the NEWEST DPATH 
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		OID of new or already-existing entry
	//			DERR_DB_SQL if DB error
	int putPath(const char * pczPath,
		    const char * pczQuals, 
		    BOOL bDpath,
		    const char * pczWhich = NULL, 
		    const char * pczWho = NULL);

	// put an entry into the FILES table
	// use either insert or update, as needed
	// @param pczFile	file name, excluding path 
	// @param iPathId	id of the corresponding path
	// @param which, who	are for tracing.
	//			if pczWhich is NULL, don't trace this call
	// @return		0 if OK
	//			DERR_DB_SQL if DB error
	int putFile(const char * pczFile, int iPathId,
		    const char * pczWhich = NULL, 
		    const char * pczWho = NULL); 

	// get a single composite path/files from the FILES & PATHS tables
	// @param pczIdStr	which record to get. (OID in Files table)
	// @return		pointer to result string or NULL if error
	//			The result is created in the shared
	//			s_outbuf, so it is somewhat volatile
	const char * getFile(const char * pczIdStr);

	// put an entry into the CHECKSUMS table
	// @param pczFile	file name, excluding path 
	// @param pczChecksum	file checksum as a string
	// @param pczDate	file date
	// @return		OID of new or already-existing entry if OK
	//			DERR_DB_SQL if DB error
	int putChecksum(const char * pczFile, const char * pczChecksum, const char * pczDate);

	// get one or more entries from the CURRENT table
	// @param pczIdStr	which record to get.
	//			if NULL, get all info needed by UI, 
	//			   formatted appropriately
	// @return		pointer to result if OK else NULL
	//			The result is created in the shared
	//			s_outbuf, so it is somewhat volatile
	const char *getCurrent(const char * pczIdStr = NULL);

	// get one or more entries from the FILES & PATHS tables
	// @param pczIdStr	which record to get.
	//			if 'IMAGE', get all recognized image files
	//			other values to be defined
	// @return		pointer to result string or NULL if error
	//			The result is created in the shared
	//			s_outbuf, so it is somewhat volatile
	const char * getFiles(const char * pczIdStr);

	// verify an entry in the CHECKSUMS table
	// @param pczFile	file name, excluding path 
	// @param pczChecksum	file checksum as a string
	// @param pczDate	file date
	// @return		0 if matches
	//			DERR_FN_ARG1 or DERR_FN_ARG2 if present but not matches
	//			DERR_DB_NOTFOUND if file not found
	//			DERR_DB_SQL if DB error
	int verifyChecksum(const char * pczFile, const char * pczChecksum, const char * pczDate);

	// get the product level either from the SN or the ProductLevel entry
	// first verify the signature
	// @param bOriginal	TRUE => get from SN else from ProductLevel
	// @return		> 0 is product level
	//			< 0 is error
	int getProductLevel(BOOL bOriginal);

	// set the ProductLevel entry and set signature
	// first verify the signature
	// @param uProduct	value to set
	// @return		> 0 is product level
	//			< 0 is error
	int setProductLevel(uint uProduct);

	/* set the DB to show it's been registered
	 * @return 	0 if OK else -1
	 */
	int registerToDb(const char * pValCode,uint uProductLevel, 
			 const char * czWorkingLines,const char * czWorkingPixels,
			 const char * czWorkingImages,
			 uint uBits);

	// calculate a checksum of the PROFILE fields listed in s_czSignatureFields
	// and store it in the Signature field.
	// @return		0 if OK
	int setSignature();

	// calculate a checksum of the PROFILE fields listed in s_czSignatureFields
	// and verify it against the Signature field.
	// @return		TRUE if matches
	//			FALSE (0) if match fails
	BOOL verifySignature();

	// For license types with a timeout, check current state
	// The checking depends on LicenseType
	// @return		0 => OK
	//			1 => not registered but not yet timed out
	//			2 => timed out
	//			3 => DB error or inconsistency
	int queryExpiration();

	// set or check DegradedTime,product (based on SN),InstallTime
	// Look at S/N. 
	//   If installed as EVAL then compare InstalledTime to iDays
	//   If installed as PROF/ACAD 
	//	then if current ProductLevel matches and DegradedTime defined
	//	   clear DegradedTime
	//	else if DegradedTime == 0 or not defined, set it
	//	else compare DegradedTime to iDays
	// called (only) from SSDp::checkProductStatus 
	// @return 	0 if OK
	//		2 if expired
	int queryExpirationDays(int iDays);

    protected:
	// calculate a checksum of the PROFILE fields listed in s_czSignatureFields
	// and return it
	// @return		is calculated chacksum % 0x7FFFFFFF
	uint _calcSignature();

    public:
	// Do some query or command to DB
	// @param pczSqlCmd		command to DB
	// @param uFormatSelector	select output format or not supplied
	//				default is DB_TEST
	// @param pczResultBuf		buffer to pack results into, or NULL
	virtual int sqlQuery(const char * pczSqlCmd, 
			     DBFORMAT_SEL uFormatSelector = DB_TEST,
			     char * pczResultBuf = NULL) = 0;

	// Create by calloc an error message consisting of pczFn, 
	// the error from sqlite3, and the sql cmd.
	// Free and/or zero each of the components to indicate they have
	// been used.
	// The resulting string must be freed.
	// @param pczFn		name/description  of fn where error occurred
	// @return		string which must be freed
	virtual char * errmsg(const char * pczFn) = 0;

	// dump current structure values
	// @param detail	how much detail to include:
	//			0 => suppress completely
	//			1 => normal
	//			2 => extra
	//			3 => excessive
	// @param pczTitle	if non-NULL, prefix dump with a title string.
	// @return		ptr to static buffer containing output
	//
	const char * dump(int detail=1, const char * pczTitle=NULL) const = 0;

	// dump all tables
	// @param pczTitle	if non-NULL, prefix dump with a title string.
	// @param ulTableMask	bitmap of tables to NOT dump
	//			   bit# corresponds to index in s_czTables
	// @return		ptr to static buffer containing output
	//
	char * dumpTables(const char * pczTitle = NULL,ulong ulTableMask=0);

	//	some useful constants for dumpTables:
	#define DUMP_CURRENT (1<<DB_LEGALVALS) | (1<<DB_PROFILE) | (1<<DB_HISTORY) | (1<<DB_CHECKSUMS)
	#define DUMP_PROFILE (1<<DB_LEGALVALS) | (1<<DB_CURRENT) | (1<<DB_HISTORY) | (1<<DB_CHECKSUMS) \
		| (1 << DB_TRACING) | (1 << DB_FILES) | (1 << DB_PATHS) | (1 << DB_VCurrent) \
		| (1 << DB_VDecorations)

	// Find which, if any table is named
	// @param pNamePtr	name of table
	// @return		index within s_czTables, or -1
	int whichTable(const char * pNamePtr);

	// get IPC_STYLE from the DB
	// Currently this applies only to communications with the viewport	
	IPC_STYLE_t getIpcStyle(MODULE_INDICES uModule);

/*********************************************************************
 *
 * utility fns - not DB but used in combo with DB operations
 *
 *********************************************************************/

	// calculate and return an integer (about 63 bits) as a string 
	// which is more-or-less characteristic of this computer
	// moved from OpenDragon SSDp.cpp v 5.10.4
	// @param bVerbose	
	static const char * CalcMachineCode(BOOL bVerbose);

	/* prelim function which mimics what's in OD website
	 * Old (OpenDragon) version: just the sum of czMachine & czExpire
	 * New version: include part of SN, and checksum
	 */
	static const char * CalcValCode(const char * czMachine, const char * czSn,
					const char * czExpire);
    protected:

	// Setup the legal values table.
	// This table is probably never subsequently modified
	// @return 		0 if OK
	int _setLegalValues();

	// Setup the Current table, which can contain only predefined entries
	// This table is probably never subsequently modified
	// @return 		0 if OK
	int _setCurrentEntries();

	// Setup the db fields of profile.
	// This is never subsequently modified
	// This is a protected function
	// @return 		0 if OK
	int _setDbSchemaValues();

	char m_czSqlCmd[512];

	/* pczCorruptField amd pczCorruptValue are used for testing.
	 * Any get from the DB for the corruptfield will receive the
	 * corruptvalue.
	 * They must be static because validateUser uses a different
	 * instance of SSDb than SSModel.
	 */
//	static const char * s_pczCorruptField;
//	static const char * s_pczCorruptValue;

	static const char * s_czTables[];
	static const char * s_czTableFields[];
	static const char * s_czLegalValues[];
	static const char * s_czCurrentEntries[];
	static const char * s_czZapRows[];
    private:
	static char * s_czSignatureFields[]; // which fields included in Signature
	static Class s_class_Base;
    };

class SSDbSqlite : public SSDb
    {
    public:
	// simply create an object and set properties to default
	// @param iDebug	debug level if > than set by OB::OB
	// @param iTrace	trace level if > than set by OB::OB
	SSDbSqlite(int iDebug=0, int iTrace=0);

	// Open the DB if it exists, create it if it doesn't exist
	// @param bPreserve	if TRUE, do nothing except open the DB
	//			-50 = DERR_FILE_ACCESS if DB missing
	//			-85 = DERR_DB_OPEN if unable to open or create
	// @return 		0 if OK
	int init(const char * dbName,BOOL bPreserve=FALSE);

	// pczCorruptField amd pczCorruptValue are used for testing.
	// Changes the DB
	void setCorrupt(const char * pczCorruptField,const char * pczCorruptValue);

	// Create the DB. Delete it first if necessary.
	// make sure it contains all necessary tables, 
	// and all necessary entries in tables which contain a pre-defined set
	// Do nothing which is site. product, or situation dependent
	// @return 		0 if OK
	int create(const char * dbName);

	~SSDbSqlite();

	// Do some query or command to DB
	// @param pczSqlCmd		command to DB
	// @param uFormatSelector	select output format or not supplied
	//				default is DB_TEST
	// @param pczResultBuf		buffer to pack results into, or NULL
	// @return 			SQLITE error code	
	int sqlQuery(const char * pczSqlCmd, 
		     DBFORMAT_SEL uFormatSelector = DB_TEST,
		     char * pczResultBuf = NULL);

	// Create by calloc an error message consisting of pczFn, 
	// the error from sqlite3, and the sql cmd.
	// Free and/or zero each of the components to indicate they have
	// been used.
	// The resulting string must be freed.
	// @param pczFn		name/description  of fn where error occurred
	// @return		string which must be freed
	char * errmsg(const char * pczFn);

	const char * setupSubstMsgs();

	// dump current structure values
	// @param detail	how much detail to include:
	//			0 => suppress completely
	//			1 => normal
	//			2 => extra
	//			3 => excessive
	// @param pczTitle	if non-NULL, prefix dump with a title string.
	// @return		ptr to static buffer containing output
	//
	const char * dump(int detail=1, const char * pczTitle=NULL) const
	    { return "SSDbSqlite"; } ;

    private:
	char * m_pczError; /* malloc'd by sqlite */
	sqlite3 * m_pDb;
	static Class s_class_Base;
    };

#endif // ifndef SSDB_H
