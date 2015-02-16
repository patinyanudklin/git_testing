/* filename dragonObject.cpp - base class for IPC
 *
 *	~~ Copyright 2002-2015 Kurt Rudahl and Sally Goldin
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
 * $Id: dragonObject.cpp,v 1.30 2015/01/21 10:37:33 rudahl Exp $
 * $Log: dragonObject.cpp,v $
 * Revision 1.30  2015/01/21 10:37:33  rudahl
 * improving imageReader - 2drag coordination
 *
 * Revision 1.29  2014/03/08 06:02:18  rudahl
 * improve debug, comments
 *
 * Revision 1.28  2006/12/09 12:38:00  goldin
 * give error and exit if kpath does not exist
 *
 * Revision 1.27  2005/03/28 09:41:08  goldin
 * Use upper case in looking for kpath
 *
 * Revision 1.26  2005/03/23 10:32:32  goldin
 * Make qUsingMenus work on linux
 *
 * Revision 1.25  2005/03/19 06:31:51  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.25  2005/03/13 02:40:59  rudahl
 * fix probs found working with enhance
 *
 * Revision 1.24  2005/02/15 19:02:09  rudahl
 * moved out product fns
 *
 * Revision 1.23  2005/02/12 02:19:46  rudahl
 * added Class, dump()
 *
 * Revision 1.22  2005/02/10 03:51:27  rudahl
 * cleaned up tracing and error handling
 * cleaned up image file writing
 *
 * Revision 1.21  2005/01/29 11:51:58  rudahl
 * adapt for v 5.5
 *
 * Revision 1.20  2004/12/23 12:02:59  rudahl
 * added unistd.h for linux
 *
 * Revision 1.19  2002/09/25 18:04:54  rudahl
 * rev'd kpath to avoid infinite loop
 *
 * Revision 1.18  2002/07/16 19:51:21  goldin
 * Bump module count
 *
 * Revision 1.17  2002/02/12 21:25:48  rudahl
 * added ProductBits
 *
 * Revision 1.16  2002/01/10 22:25:45  rudahl
 * added support for small-mode ZOR version
 *
 * Revision 1.15  2001/09/26 19:04:52  rudahl
 * minor changes and de-linting for GCC, including fine_first
 *
 * Revision 1.14  2001/09/14 14:14:22  rudahl
 * revised sequence number ranges for Cmd, Msg files
 *
 * Revision 1.13  2001/08/22 16:54:35  rudahl
 * added conditionals for GCC
 *
 * Revision 1.12  2001/07/10 11:36:14  rudahl
 * added qUsingMenus
 *
 * Revision 1.11  2001/07/04 21:33:09  rudahl
 * fixed some bugs; added sbility to SendRpy alt. to UI or SS
 *
 * Revision 1.10  2001/07/03 19:58:10  rudahl
 * made getkpath more robust
 *
 * Revision 1.9  2001/07/03 13:35:21  rudahl
 * added defenses against no kpath
 *
 * Revision 1.8  2001/06/28 21:10:26  rudahl
 * improvements in text messages and documentation
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
 * Revision 1.1  2001/04/27 21:25:57  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 ********************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * history
 *	5/2001 ktr	created
 *	10/2001 ktr	changed strategy for generating filenames to
 *                      make the leftmost of the three digits of the
 *                      name derived from the MODULE_INDEX (see DragonOb.h)
 * 5.4	12/22/2004 ktr	added unistd.h for linux for access()
 * 5.5	2005-1-29 ktr	adapt for dragon 5.5; moved from ipc to common
 */


extern "C" { 
#include "drelease.h"
ID_ DRAGONOBJECT_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.30 $$Date: 2015/01/21 10:37:33 $";
D_REL_IDSTR; }

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#if defined __GCC__
#include <unistd.h>
#else
#include <dos.h>
#include <io.h>
#include <process.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"

#include "ob.h"
#include "dragonOb.h"

DragonObject::DragonObject() {}

DragonObject::DragonObject(int iDebug,int iTrace) : OB()
    {
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    }

const char * DragonObject::className() { return "DragonObject"; }
 
const char * DragonObject::getThisModule() { return czThisModule; }

const char * DragonObject::getModuleAbbrev(const size_t uModuleIndex)
    { return pczModuleAbbrevs[uModuleIndex]; }

	/* way to specify the module abbrev and index */
void DragonObject::setThisModule(const char * czAbbrev)
    {
    size_t i;
    for (i=0; i<10; i++)
        if (strcmp(czAbbrev,pczModuleAbbrevs[i]) == 0)
	    {
	    s_uThisModule = i;
	    break;
	    }
    strcpy_array(czThisModule,czAbbrev);
    }

/* the kpath used here will have a trailing [\/] if any removed */ 
const char * DragonObject::getKpath()
    {
	int iAccessStat = 0;
      //#if defined _WIN32 || defined __ZTC__ || defined __GCC__
    if (pczKpath == NULL)
        {
	char kp[CONFIGSTRLEN+1];
	char * pkp = getenv("TMP");
	// 3/28/05 changed to upper case
	if (GetConfig("KPATH",kp,sizeof(kp)) > 0)
	    {
	    if(strchr("\\/",kp[strlen(kp)-1]) != NULL)
	        kp[strlen(kp)-1] = '\0';
	    if ((iAccessStat = access(kp,F_OK)) == 0)
	        pczKpath = strdup(kp);
	    else
	        {
		  //pczKpath = "."; /* just to prevent a null value */
		  /* This is a fatal error - give a message and exit! */
		  fprintf(stderr,"\nFATAL ERROR: Temporary directory %s does not exist.\n",
			  kp);
		  fprintf(stderr,"Please create this directory, or rerun the Dragon installation.\n");
		  fprintf(stderr,"Press any key to exit: ");
		  fgetc(stdin);
		  exit(1);     
		}
	    }
	else if ((pkp != NULL) && (access(pkp,F_OK) == 0))
	    pczKpath = strdup(pkp);
	else
	    pczKpath = (char *)"."; /* just to prevent a null value */
	if(strchr("\\/",pczKpath[strlen(pczKpath)-1]) != NULL)
	    pczKpath[strlen(pczKpath)-1] = '\0';
        }
    //#endif
    return pczKpath;
    }

/* the kpath used here will have a trailing [\/] if any removed */ 
void DragonObject::setKpath(const char * kpath)
    {
    if (pczKpath != NULL)
        free(pczKpath);
    pczKpath = strdup(kpath);
    if(strchr("\\/",pczKpath[strlen(pczKpath)-1]) != NULL)
        pczKpath[strlen(pczKpath)-1] = '\0';
    }

/* return 1 if there's a recognized menu system running
 * to receive messages; else 0 */ 
const int DragonObject::qUsingMenus()
    {
    static int iYes = -1;
    if (iYes == -1)
        {
	char buf[CONFIGSTRLEN+1];
	int stat = GetConfig("NOMENUS",buf,sizeof(buf));
	iYes = (stat >= 0) ? 0 : 1;
        }
    return iYes;
    }

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
const char * DragonObject::dump(int detail, const char * pczTitle) const
    {
    memset(s_outbuf,0,sizeof(s_outbuf));
    sprintf(s_outbuf,
	    "%s %s Class at %p: \tisA=%p \tsubclassof '%s'\n\tabout='%s'",
	    NOTNULL(pczTitle),nameOf(),this,isA(),isSubclassOf()->nameOf(),
	    NOTNULL(about()));
    return s_outbuf;
    }

char DragonObject::czThisModule[IPC_MODULEABBR_SZ+1] = "";
size_t DragonObject::s_uThisModule = 10;
char * DragonObject::pczKpath = NULL;
const char * DragonObject::pczModuleAbbrevs[] = { MODULE_ABBREV } ;

const char * getKpath() { return DragonObject::getKpath(); } 

void DRAGONOB_END() { puts(FIL_ID); }


