/*
 *	filename dragonOb.h
 * 	Generated by Together
 *	~~ Copyright 2001-2014 Kurt Rudahl and Sally Goldin
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
 * ******************************************************************
 * $Id: dragonOb.h,v 1.28 2014/03/08 06:00:00 rudahl Exp $
 * $Log: dragonOb.h,v $
 * Revision 1.28  2014/03/08 06:00:00  rudahl
 * add copyright markers
 *
 * Revision 1.27  2008/06/20 05:13:51  rudahl
 * improved docs
 *
 * Revision 1.26  2007/10/03 10:03:23  rudahl
 * handle SPAWN command from VP
 *
 * Revision 1.25  2006/01/13 14:20:29  rudahl
 * improving tracing control
 *
 * Revision 1.24  2006/01/08 09:30:53  rudahl
 * setup bitwise tests for tracing
 *
 * Revision 1.23  2005/10/01 11:07:42  rudahl
 * adding persistent storage to Ipc and SS
 *
 * Revision 1.22  2005/09/25 12:08:17  rudahl
 * working on persistent data
 *
 * Revision 1.21  2005/09/25 04:49:44  rudahl
 * added symbols for persistent storage
 *
 * Revision 1.20  2005/04/25 05:07:35  rudahl
 * added MsgTypeName, FileTypeName to IpcFile
 *
 * Revision 1.19  2005/03/19 06:25:44  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.19  2005/03/13 02:42:58  rudahl
 * fix probs found working with enhance
 *
 * Revision 1.18  2005/02/12 02:20:58  rudahl
 * added Class, dump()
 *
 * Revision 1.17  2005/01/29 11:29:49  rudahl
 * adapt to v 5.5
 *
 * Revision 1.16  2004/12/11 09:50:46  rudahl
 * made AFFIX_BS long-filename safe
 *
 * Revision 1.15  2002/09/20 18:46:38  goldin
 * Reorder modules
 *
 * Revision 1.14  2002/07/16 19:51:50  goldin
 * Add new module abbreviation and constants for ManReader
 *
 * Revision 1.13  2002/06/10 12:36:50  rudahl
 * added ifdef DRAGON_INI
 *
 * Revision 1.12  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.11  2001/07/30 19:18:50  rudahl
 * got rid of spurious commas
 *
 * Revision 1.10  2001/07/12 20:10:52  rudahl
 * changed reportError, added reportOperationError
 *
 * Revision 1.9  2001/07/10 11:36:14  rudahl
 * added qUsingMenus
 *
 * Revision 1.8  2001/06/15 20:32:23  rudahl
 * added HISORY_MSG_FORMAT
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
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 ************************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * history:
 * 5.5	2005-1-29 ktr   adapt for Dragon 5.5
 *	2005-2-11 ktr	added dump() so Ipcxx classes do not need to
 *	2005-4/25 ktr	added name strings for IPC file and message types
 * 5.7	2005-9-25 ktr	added support for persistent data
 * 	2006-1-8 ktr	put in bit-wise conditionals for logTrace
 */

#ifndef DRAGONOBJECT_H
#define DRAGONOBJECT_H

/* size of strings */
#define IPC_MODULEABBR_SZ 2
#define IPC_FILENAME_SZ 14

#define CFGFILE "dragon.cfg"
#ifndef DRAGON_INI
#define DRAGON_INI "dragon.ini"
#endif

typedef enum 
    { 
    CMD_FILE_TYPE,
    RPY_FILE_TYPE,
    NAK_FILE_TYPE,
    MSG_FILE_TYPE,
    PRO_FILE_TYPE,
    QRY_FILE_TYPE,
    DAT_FILE_TYPE,
    UNKNOWN_FILE_TYPE = 255
    } IPC_FILE_TYPE ;

#define IPC_FILE_TYPE_NAMES \
    "CMD_FILE_TYPE", \
    "RPY_FILE_TYPE", \
    "NAK_FILE_TYPE", \
    "MSG_FILE_TYPE", \
    "PRO_FILE_TYPE", \
    "QRY_FILE_TYPE", \
    "DAT_FILE_TYPE"

typedef enum
    {
    WARN_MSG_TYPE,
    ERR_MSG_TYPE,
    INFORM_MSG_TYPE,
    SPT_MSG_TYPE,
    XML_MSG_TYPE=10,
    COMPLEX_ERR_MSG_TYPE, /* name=value pairs; names are in ipc-spec.txt */
    OTHER_MSG_TYPE = 255
    } IPC_MESSAGE_TYPE ;    

#define IPC_MSG_TYPE_NAMES \
    "WARN_MSG_TYPE", \
    "ERR_MSG_TYPE",\
    "INFORM_MSG_TYPE", \
    "SPT_MSG_TYPE","", \
     "","","","","", \
    "XML_MSG_TYPE", \
    "COMPLEX_ERR_MSG_TYPE"

typedef enum
    {
    TEXT_MSG_FORMAT,           /* msg contains actual text */
    KEY_MSG_FORMAT = 0x100,    /* msg has lookup key then optional argument */
    HISTORY_MSG_FORMAT = 0x200 /* message gets included into history */
    } IPC_MESSAGE_FORMAT ;    

/* this originally was used to enumerate executables controlled by SS;
 * as of 10/13/01, it also defines a subrance of IPC file sequence numbers
 * for 'Cmd' files (initially; maybe others as well) to provide sep.
 * namespaces for different command files. The ones marked "not a real... "
 * are used only for this purpose.
 * MODULE_ABBREV defines the two-letter abbreviations which are also part
 * of IPC.
 */
typedef enum 
    {
    MODULE_UI,
    MODULE_SERVER16,
    MODULE_SERVER,  	  /* not a real module, but has it's own ABBR */
    MODULE_SCRIPTSERVER,  /* not a real module, but has it's own ABBR */
    MODULE_VIEWPORT_1,
    MODULE_VIEWPORT_2,
    MODULE_VIEWPORT_3,
    MODULE_VIEWPORT_4,
    MODULE_MREADER = 10,
    MODULE_INVALID	  /* end marker */
    } MODULE_INDICES ;

#define MODULE_ABBREV \
    "UI","S-","DS", "SS",\
    "V1","V2","V3","V4","","","MR","??"

#define IPC_MSG_TYPE_MASK 0xFF
#define IPC_MSG_FORAT_MASK 0xFF00

typedef enum
    {
    IPC_ERROR_OK, /* reserve 0 for no error*/
    IPC_ERROR_READ,
    IPC_ERROR_WRITE,
    IPC_ERROR_DELETE,
    IPC_ERROR_MEMORY,
    IPC_ERROR_UNKNOWNTYPE, /* unknown file type */
    IPC_ERROR_BADTYPE,     /* shouldn't see this file type here */
    IPC_ERROR_STRUCTURE    /* something wrong with how file is structured */
    } IPC_ERROR_CODE;

typedef enum
    {  /* 2 - 9 are the IPC cmds "required" of all modules */
    IPC_CMD_NOTHING,
    IPC_CMD_READY,        /* cmd is ready to proces */
    IPC_CMD_NOOP,
    IPC_CMD_TRACE,
    IPC_CMD_SETTIME,
    IPC_CMD_GETTIME,
    IPC_CMD_ABEXIT,
    IPC_CMD_WRONG=8,
    IPC_CMD_COMPLETED=9,  /* cmd has been processed and cleaned up */
      /* 10 -19 are commands sent by UI which the ScriptServer carries out */
    IPC_CMD_EXIT=10,      /* commands from UI or script - EXIT system */
    IPC_CMD_CANCEL,       /* cancel script */
    IPC_CMD_RUN,          /* run script */
    IPC_CMD_ECHO,         /* script echoing */
    IPC_CMD_ECHO_ON,      /* script echoing */
    IPC_CMD_ECHO_OFF,     /* script echoing */
    IPC_CMD_START,        /* start the other processes */
    IPC_CMD_UIREADY,      /* ready for commands (Rpy files) */
    IPC_CMD_SPAWN,        /* VP wants SS to spawn something (mServer) */
      /* 20 -29 are commands understood by SS for persistent data */
    IPC_CMD_SETPERSIST = 20,
    IPC_CMD_GETPERSIST,
      /* 30 -?? are commands understood by the viewports  */
      /* these match a subset of the VP_ symbols in grsvxd, but
       * are offset up by 30 */
    IPC_VP_NOTYET=30,		/* status: nothing yet */
    IPC_VP_STARTUP,		/* status & msg: */
    IPC_VP_FESSUP,		/* ?? WRU - sho lo go */
    IPC_VP_BLOWUP,		/* status & msg: goto full screen */
    IPC_VP_SHUTUP,		/* status & msg: go behind things */
    IPC_VP_CLOSEUP,		/* status & msg: iconize */
    IPC_VP_OPENUP,		/* status & msg: go to std posn at top of Z-order */
    IPC_VP_LOCKUP,		/* status & msg: don't permit repaint */
    IPC_VP_WAKEUP,		/* force it to take focus */
    IPC_VP_CLOSEDOWN,	/* status & msg: exit (except for EXEC) */
    IPC_VP_SET_ENABLES,	/* set which capabilities are enabled: lParam */
    IPC_VP_SET_ACTIVE,	/* set which capabilities are active: lParam */
    IPC_VP_SET_POSN,	/* set screen pos'n, DRAGON.CFG format: lParam*/
    IPC_VP_DWIN_ALIVE,
    IPC_VP_CHECK_INFILE
    } IPC_CMD_CODE;

/* the following string set match the above enum.
 * They can be used for matching or generating the commands,
 * or for trace messages */
#define REQUIRED_CMD_NAMES \
    "-NOTHING", \
    "-READY", \
    "-NOOP", \
    "-TRACE", \
    "-SETTIME", \
    "-GETTIME", \
    "-ABEXIT","","WRONGMODULE","COMPLETED"

#define SS_CMD_NAMES \
    "EXIT", \
    "CANCEL", \
    "RUN", \
    "ECHO", \
    "ECHO ON", \
    "ECHO OFF", \
    "START", \
    "READY","SPAWN","", \
    "-SETPERSIST","-GETPERSIST","","","", \
    "","","","",""

#define VP_CMD_NAMES \
    "VP_NOTYET", \
    "VP_STARTUP", \
    "VP_FESSUP",	/* WRU - sho lo go */ \
    "VP_BLOWUP",	/* goto full screen */ \
    "VP_SHUTUP",	/* go behind things */ \
    "VP_CLOSEUP",	/* iconize */ \
    "VP_OPENUP",	/* go to std posn at top of Z-order */ \
    "VP_LOCKUP",	/* don't permit repaint */ \
    "VP_WAKEUP",	/* force it to take focus */ \
    "VP_CLOSEDOWN",	/* exit */ \
    "VP_SET_ENABLES",	/* set which capabilities are enabled: lParam */ \
    "VP_SET_ACTIVE",	/* set which capabilities are active: lParam */ \
    "VP_SET_POSN",	/* set screen pos'n, DRAGON.CFG format: lParam*/ \
    "VP_DWIN_ALIVE",	/* announce DWIN is alive */ \
    "VP_CHECK_INFILE"	/* check to see if there is a file from DRAGON */

#define ALL_CMD_NAMES \
    REQUIRED_CMD_NAMES, \
    SS_CMD_NAMES, \
    VP_CMD_NAMES

#ifdef __cplusplus
class DragonObject : public OB
    {
    public:	
	static const char * getThisModule();
	static size_t getThisModuleIndex() { return s_uThisModule;};

	/* way to specify the module abbrev and index */
	static void setThisModule(const char * czAbbrev);

	static const char * getModuleAbbrev(const size_t uModuleIndex);

	/** get value of KPATH from dragon.cfg (or whereever)
	 *  cache it for repeated use (it won't change), and return it
	 *  Must first call setKpath() to set it
	 *  the kpath used here will have a trailing [\/] if any removed
	 */
	static const char * getKpath();
	/* the kpath used here will have a trailing [\/] if any removed */ 
	static void setKpath(const char * kpath);
	/* return 1 if there's a recognized menu system running
	 * to receive messages; else 0 */ 
	static const int qUsingMenus();

	DragonObject();
	DragonObject(int,int);

    protected:
	virtual const char * className();
	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
	const char * dump(int detail=1, const char * pczTitle=NULL) const;

//	const char * getThisModule();
	static char czThisModule[IPC_MODULEABBR_SZ+1];
	static size_t s_uThisModule; /* 9 until it has been to index of 
				       * pczModuleAbbrevs. */
	 /* *** pczKpath IS ALLOC'D - must be freed */
	static char * pczKpath;
	static const char * pczModuleAbbrevs[];
    };

#endif // __cplusplus

#if defined __cplusplus
extern "C" {
#endif

#ifdef __GCC__
#define FILE_SEP "/"
#else
#define FILE_SEP "\\"
#endif

#ifndef AFFIX_BS
#define AFFIX_BS(str) /* force str to end in '\' */ \
    if ((strlen(str) > 0) && (strchr("\\/",str[strlen(str)-1]) == NULL)) \
      { strcat_array(str,FILE_SEP) }
#endif

const char * getKpath();

/* These masks can be used to control tracing
 * The values can be reused in different executables
 * bit 0 sets more detailed tracing in each case
 * 0x000FF00 is for ipc
 * 0x00000FC possibly for common
 * ScriptServer ones are in ScriptServer.h
 */ 
/* IpcWrap depends on what each fn is wrapping */
#define TRACE_LVL_DETAIL	0x00001
#define TRACE_LVL_IPCMASK	0x0FF00
#define TRACE_LVL_IPCReceive	0x00100
#define TRACE_LVL_IPCSend	0x00200
#define TRACE_LVL_IPCMisc	0x00400 /* for XmlGen, Property, etc */
#define TRACE_LVL_IPCNak	0x00800
#define TRACE_LVL_IPCCmd	0x01000
#define TRACE_LVL_IPCDat	0x02000
#define TRACE_LVL_IPCMsg	0x04000
#define TRACE_LVL_IPCRpy	0x08000
#define TRACE_LVL_IPCFile	0x0F800 /* any of the files */
#define TRACE_LVL_IPCWatcher	0x09300 /* cmd or send or receive or rpy */

#if defined __cplusplus
  }
#endif

#endif //DRAGONOBJECT_H