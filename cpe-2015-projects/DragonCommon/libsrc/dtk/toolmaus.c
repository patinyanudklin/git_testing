/****************************************************************
 *	TOOLMAUS.C - functions for building DRAGON utilities
 *			fns for mouse only
 *          $Revision: 1.2 $	$Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1992-2014 by Goldin-Rudahl Associates
 *                            P.O. Box 648
 *                            North Amherst, MA 01059 U.S.A.
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *	    ~~ EndC
 *
 *****************************************************************
 *	$Id: toolmaus.c,v 1.2 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolmaus.c,v $
 *	Revision 1.2  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:18:14  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:18:14  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/11/23  16:20:44  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/11/23  16:20:44  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. These TOOLxxxx.C
 *    files will not be supplied to users, but TOOLKIT.H will be.
 *
 *    Refer to TOOLKIT.C for general comments. This file contains only
 *    fns to manipulate mouse; therefore this is for DR library only
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *	Public functions in TOOLMAUS.C
 * *	  int dtk_MouseInit()		 * initialize mouse driver
 * +	  int dtk_MouseResult( **** need to specify exact form of params)
 * +	  int dtk_MouseInit(const int cursor_type,const int x,const int y)
 *		
 * 1.0	6/27/92 ktr	extracted from TOOLKIT.C
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef __GCC__
#include <process.h>
#include <dos.h>
#include <io.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "drelease.h"
#ifdef __cplusplus
extern "C" 
    {
#endif
//#include "tstack.h"
#include "wf.h"
#ifdef __cplusplus
    }
#endif
#include "stats.h"	/*for module numbers */
//#include "basemem.h"
//#include "files.h"	// for CONFIGSTRLEN
//#include "dhead.h"	/* must preceed toolkit.h & img.h */
//#include "img.h"
//#include "filename.h"
//#include "hdrstats.h"
#include "toolkit.h"

#ifndef TEST

void TOOLMAUS()
    { }		/* just a marker for the line file */

int Inst_Module(unsigned enum_base);	/* in filecall.c, but no prototype */

/*************************************************************************
 *
 *		local data
 *
 *************************************************************************/

/*************************************************************************
 *
 *		mouse functions
 *
 *************************************************************************/

static int mouse=0;	/*  "   "   => mouse      "       "           "    */

/*************************************************************************
 *
 *		mouse functions
 *
 *************************************************************************/

int dtk_MouseInit(void)
	//	initialize mouse driver AT MOST once
	//	On failure, return error < 0
	//	else return 0
    {
    if (mouse)	// only call this once
	return 0;
    if (Inst_Module(M_ENUM) == 0)	// was NOT preloaded by FGATE?
	{
	dtk_ErrorMsgPush("Mouse driver not installed");
// don't actually install it since -Q doesn't work in 3.05 
//	if(spawnl(0,"mgate","mgate","-T",NULL) < 0x100) /* ok exits QUIT */
//	    dtk_ErrorMsgPush("Mouse driver not available or wrong version");
//	else
//	    atexit(zap_mgate);
	}
    if (dtk_ErrorMsgCount() > 0)
	return -1;
    mouse=1;
    return 0;
    }

void TOOLMAUS_END()
    { }		/* just a marker for the line file */

#else	/* #ifdef TEST */

#include <stdlib.h>
void main()
    {
    char buf[80];
    int status;
    dtk_init(NULL);
    printf("DRAGON %s running; max error level is %d\n",
	(dtk_DragonIsRunning()) ? "IS" : "is NOT",dtk_DragonErrorLevel());
    }
#endif
