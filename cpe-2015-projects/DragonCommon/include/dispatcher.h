/*
 *	filename DISPATCHER.H
 *
 *      fns in dispatcher.c used by DragonServer and ScriptServer
 *
 *         Copyright 2001-2006 Kurt Rudahl and Sally Goldin
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
 *
 ****************************************************************
 *	$Id: dispatcher.h,v 1.40 2010/12/13 12:51:05 goldin Exp $
 *	$Log: dispatcher.h,v $
 *	Revision 1.40  2010/12/13 12:51:05  goldin
 *	Add necessary infrastructure for new Export op
 *
 *	Revision 1.39  2008/07/11 10:42:39  goldin
 *	Working on text boxes and InfoText behavior
 *
 *	Revision 1.38  2007/10/17 10:44:31  goldin
 *	Implement SET-VP script command
 *	
 *	Revision 1.37  2007/02/03 05:48:39  goldin
 *	Prohibit interactive ops in scripts
 *	
 *	Revision 1.36  2006/12/29 11:32:41  goldin
 *	Add symbol for G COM
 *	
 *	Revision 1.35  2006/12/10 12:08:50  goldin
 *	Integrating new geography operations
 *	
 *	Revision 1.34  2006/11/18 11:41:31  goldin
 *	Add Import to dispatcher
 *	
 *	Revision 1.33  2006/11/13 14:11:10  goldin
 *	integrating PCA into Dragon
 *	
 *	Revision 1.32  2006/01/20 08:45:04  rudahl
 *	fixed misspelled fn name
 *	
 *	Revision 1.31  2006/01/19 09:21:48  rudahl
 *	improvements in logging
 *	
 *	Revision 1.30  2005/12/20 13:07:42  rudahl
 *	added names for dragon ops
 *	
 *	Revision 1.29  2005/11/19 03:40:36  rudahl
 *	simplified pwfTab
 *	
 *	Revision 1.28  2005/10/20 09:47:19  goldin
 *	Integrate clserror into Dragon
 *	
 *	Revision 1.27  2005/10/01 11:07:42  rudahl
 *	adding persistent storage to Ipc and SS
 *	
 *	Revision 1.26  2005/09/16 11:50:06  goldin
 *	Working on moving CUR to 32 bit code
 *	
 *	Revision 1.25  2005/08/19 05:15:40  rudahl
 *	adding annotation
 *	
 *	Revision 1.24  2005/04/01 08:51:55  goldin
 *	Changes to support adding new 32-bit display fns
 *	
 *	Revision 1.23  2005/02/16 04:17:02  rudahl
 *	adapt to GCC/MINGW differences
 *	
 *	Revision 1.22  2003/04/20 19:29:57  rudahl
 *	make isAspace a macro
 *	
 *	Revision 1.21  2003/04/17 23:39:36  rudahl
 *	adding -ENCODING for script files
 *	
 *	Revision 1.20  2002/09/05 00:47:46  rudahl
 *	moved GetProductLevel to IPC
 *	
 *	Revision 1.19  2002/07/18 19:48:46  goldin
 *	Extend manual reader functionality to send command via the ScriptServer
 *	
 *	Revision 1.18  2002/04/18 00:22:58  goldin
 *	Add new field to table structure to record if op is interactive only
 *	
 *	Revision 1.17  2002/03/29 02:13:53  goldin
 *	Implement new C FEA operation
 *	
 *	Revision 1.16  2002/03/26 17:33:57  rudahl
 *	added support for Rhett's pattern detection
 *	
 *	Revision 1.15  2002/02/12 23:13:43  goldin
 *	Add proto for GetProductLevel
 *	
 *	Revision 1.14  2002/01/21 19:52:57  goldin
 *	Implement HEA in 32 bits
 *	
 *	Revision 1.13  2001/11/28 18:57:52  rudahl
 *	reordered sequence of defns
 *	
 *	Revision 1.12  2001/11/28 11:56:29  rudahl
 *	removed ExecuteKnownCommand
 *	
 *	Revision 1.11  2001/11/06 18:06:19  goldin
 *	Implement MEA in 32 bit world
 *	
 *	Revision 1.10  2001/10/08 15:07:44  rudahl
 *	added DPATH
 *	
 *	Revision 1.9  2001/10/06 11:43:48  rudahl
 *	added impliedarg processing
 *	
 *	Revision 1.8  2001/09/28 11:47:51  goldin
 *	Add new isAdigit function
 *	
 *	Revision 1.7  2001/09/14 18:24:45  goldin
 *	Added infrastructure for new REG operation
 *	
 *	Revision 1.6  2001/08/17 19:03:57  rudahl
 *	added PWF_STATE_NAMES
 *	
 *	Revision 1.5  2001/08/17 13:54:23  rudahl
 *	moved PWF_CMD enum from dispatcher.c
 *	
 *	Revision 1.4  2001/08/17 12:03:53  rudahl
 *	added local commands; removed dependency between enum and PWF_TAB
 *	
 *	Revision 1.3  2001/08/15 16:39:21  rudahl
 *	added PreTrim()
 *	
 *	Revision 1.2  2001/07/03 10:00:39  rudahl
 *	fixed dispatch parsing bug
 *	
 *	Revision 1.1  2001/07/02 20:09:32  rudahl
 *	cleaned almost everyting out of DragonServer, and created dispatcher.c
 *	
 ****************************************************************
 *
 *	7/2/01  ktr	Created
 * 5.5	2005-2-15 ktr	imported from Dragon 5.4.4
 * 5.7	2005-Aug-19 ktr	added annotation
 *	2005-Sep-27 ktr	simplified PWF_TAB structure
 * -------------------------------------------------------------*/

#ifndef DISPATCHER_H
#define DISPATCHER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
    {
    GROUND, 
    READ_KNOWN, EXEC_KNOWN, 
//    READ_GENERIC, EXEC_GENERIC,
    READ_COLON, EXEC_COLON, 
    READ_DISPLAY, EXEC_DISPLAY, /* multi line commands handled locally */
    READ_DOC, EXEC_DOC,         /* User manual help */
    EXEC_LOCAL,                 /* one line commands handled locally */
    EXEC_SCRIPT,                /* one line cmds only in scripts */
    EXEC_NOOP,                  /* one line commands ignored locally */
    SKIP, PWF_NOTFOUND
    } PWF_STATE ;

#define PWF_STATE_NAMES \
    "GROUND", \
    "READ_KNOWN", "EXEC_KNOWN", \
 /*   "READ_GENERIC", "EXEC_GENERIC", */ \
    "READ_COLON", "EXEC_COLON", \
    "READ_DISPLAY", "EXEC_DISPLAY", \
    "EXEC_LOCAL", \
    "EXEC_SCRIPT", \
    "EXEC_NOOP", \
    "SKIP", "PWF_NOTFOUND"

typedef enum Pwf_cmds  /* must match the following table */
    {
      // display
    PWF_D_1BA, PWF_D_3BA, PWF_D_GRA, PWF_D_OVE, 
    PWF_D_ANN_ADD,PWF_D_ANN_ERA,PWF_D_ANN_LEG,
    PWF_TRA_DEF, PWF_TRA_APP, PWF_TRA_AUT,
      // classify 
    PWF_C_LIS,
    PWF_EDI_SHO, PWF_EDI_MOD, PWF_EDI_COP, PWF_EDI_COM,
    PWF_EDI_REN, PWF_EDI_SAV, PWF_EDI_DEL, PWF_EDI_HIS,
    PWF_BOX, PWF_MAX, PWF_MDM,
    PWF_CLU, PWF_SLI, PWF_AGC,
    PWF_C_REC,
    PWF_C_FEA, PWF_C_ERR,
     // enhance  
    PWF_SUM, PWF_DIF, PWF_SYM, PWF_RAT,
    PWF_VEG, PWF_GVI, PWF_MAS, PWF_FIL, PWF_REL, PWF_WAV,
    PWF_PCA,
     // file
    PWF_F_SAV,  PWF_F_SUB, PWF_F_IMP, PWF_F_EXP,
    PWF_ULIS,   PWF_UHIS, PWF_USCA, PWF_UHEA, PWF_UCUR,
     // geometry
    PWF_GCAL,   PWF_GREG, PWF_GCOO, PWF_GMEA, PWF_GVEC, PWF_GGCP,
    PWF_GSLO,   PWF_GASP, PWF_GBUF, PWF_GCOM, PWF_GRULE,

//    PWF_GENERIC,
    PWF_TOOL,
    PWF_L_TEXTW,   PWF_L_TEXT,  PWF_L_KILLTEXT,
    PWF_L_EOS,     PWF_L_ECHOON,  PWF_L_ECHOOFF,  PWF_L_NOSHOW,
    PWF_L_VAR1,    PWF_L_VAR2,    PWF_L_ENDIF,
    PWF_L_IFEQ,    PWF_L_IFNEQ,   PWF_L_IFDOS,    PWF_L_IFWIN,
    PWF_L_CLOCK,   PWF_L_SPEED,   PWF_L_DPATH,    PWF_L_ASK,
    PWF_SHOW,	   PWF_L_ENCODING, PWF_VP_SET,
    PWF_NOOP,
    PWF_INVALID  /* last member */
    } PWF_CMD ;

#define PWF_CMD_NAMES  /* must match the above */ \
    "PWF_D_1BA", "PWF_D_3BA", "PWF_D_GRA", "PWF_D_OVE",  \
    "PWF_D_ANN_ADD","PWF_D_ANN_ERA","PWF_D_ANN_LEG", \
    "PWF_TRA_DEF", "PWF_TRA_APP", "PWF_TRA_AUT", \
    "PWF_C_LIS", \
    "PWF_EDI_SHO", "PWF_EDI_MOD", "PWF_EDI_COP", "PWF_EDI_COM", \
    "PWF_EDI_REN", "PWF_EDI_SAV", "PWF_EDI_DEL", "PWF_EDI_HIS", \
    "PWF_BOX", "PWF_MAX", "PWF_MDM", \
    "PWF_CLU", "PWF_SLI", "PWF_AGC", \
    "PWF_C_REC", \
    "PWF_C_FEA", "PWF_C_ERR", \
 \
    "PWF_SUM", "PWF_DIF", "PWF_SYM", "PWF_RAT", \
    "PWF_VEG", "PWF_GVI", "PWF_MAS", "PWF_FIL", "PWF_REL", "PWF_WAV", \
    "PWF_PCA", \
\
      "PWF_F_SAV",  "PWF_F_SUB", "PWF_F_IMP", "PWF_F_EXP",  \
    "PWF_ULIS",   "PWF_UHIS", "PWF_USCA", "PWF_UHEA", "PWF_UCUR", \
    "PWF_GCAL",   "PWF_GREG", "PWF_GCOO", "PWF_GMEA", "PWF_GVEC", "PWF_GGCP", \
 \
    "PWF_GSLO", "PWF_GASP","PWF_GBUF", "PWF_GCOM", "PWF_GRULE",\
    "PWF_TOOL", \
    "PWF_L_TEXTW",   "PWF_L_TEXT", "PWF_L_KILLTEXT",\
    "PWF_L_EOS",     "PWF_L_ECHOON",  "PWF_L_ECHOOFF",  "PWF_L_NOSHOW", \
    "PWF_L_VAR1",    "PWF_L_VAR2",    "PWF_L_ENDIF", \
    "PWF_L_IFEQ",    "PWF_L_IFNEQ",   "PWF_L_IFDOS",    "PWF_L_IFWIN", \
    "PWF_L_CLOCK",   "PWF_L_SPEED",   "PWF_L_DPATH",    "PWF_L_ASK", \
    "PWF_SHOW",	   "PWF_L_ENCODING", "PWF_VP_SET",\
    "PWF_NOOP", \
    "PWF_INVALID"  /* last member */

const char * getPwfCmdName(uint uOp);

typedef struct PWF_TAB_t
    {
    PWF_CMD uCommand;    /* the Pwf_cmd value */
    char * name;
    PWF_STATE iNextState;
      /* next three fields only used by KNOWN, GENERIC, TOOLS */
    long (*ProcessCmd)(const char * name,
		       const char * valuebuf,
		       const struct PWF_TAB_t * pTable);
//    int iPreExec;    /* char denoting op to run BEFORE spec'd cmd */
//    int iPostExec;   /* char denoting op to run AFTER spec'd cmd */
    int iImpliedArg; /* char denoting what arg(s) should be inferred 
		      * by ProcessCmd if not present in valuebuf */
    int iInteractiveOnly; /* char - if 0, can be run in a script,
			    if 'I', only interactive mode.
			    */
    } PWF_TAB;

  /*
   * fns in CmdProcessor.cpp which are ref'd in table in dispatcher
   * They are not used by DragonServer.
   */
long ProcessKnownCmd(const char * filename, const char * bigbuf,
		     const struct PWF_TAB_t * pTable);
long ProcessGenericCmd(const char * filename, const char * bigbuf,
		     const struct PWF_TAB_t * pTable);
long ProcessToolsCmd(const char * filename, const char * bigbuf,
		     const struct PWF_TAB_t * pTable);
long ProcessDocumentCmd(const char * filename,const char * pCmdPtr,
		     const struct PWF_TAB_t * pTable);

     /* execute a 'grsproc' command as specified by 's_iPwfTabIndex'
      * command args are in 'commfile'
      * Return value should be 0, or -1 if cmd not known
      */
//long ExecuteKnownCmd(const char * commfile);

     /* search the table for pczBegin, setting the s_... vars if found 
      * @param  pczBegin string which begins with command to be found
      *                  (no leading whitespace or CMD>>) 
      *                  pczBegin is not modified
      * @return  ptr to found element if found, else NULL
      */
const PWF_TAB * SearchPwf(const char * pczBegin);

   /* isspace() replacement; isspace is broken
    * @return TRUE if char is blank, or ctrl from tab through cr
    */
//BOOL isAspace(int c);

   /* isdigit() replacement
    * @return TRUE if char is 0 through 9
    */
BOOL isAdigit(int c);

    /*     advance past CMD>> and any whitespace and comment
     *     @param pczCmdLine  command line, or NULL
     *     @return            pointer into pczCmdLine pointing to first
     *                        important non-white character,
     *                        or NULL if there aren't any
     */
const char * PreTrim(const char * pczCmdLine);

    /**
     * Read the file created by the installation kit and determine
     * the current product that is installed. If the file cannot
     * be read, assume a demo.
     * If the value is not one of the defined values, assume demo.
     * Returns one of the product codes defined in PERMBITS.H,
     * as an unsigned short.
     */
//ushort GetProductLevel();


#ifdef __cplusplus
    }
#endif

#endif
