static char RCSID[]
   = "@(#) " __FILE__ "  $Revision: 1.4 $$Date: 2014/12/17 07:20:39 $";
/****************************************************************
 *	TOOL_SA.C - functions for building DRAGON utilities
 *			fns for stand-alone only
 *          $Revision: 1.4 $	$Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1992-2014 by Goldin-Rudahl Associates
 *                            P.O. Box 9648
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
 *	$Id: tool_sa.c,v 1.4 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: tool_sa.c,v $
 *	Revision 1.4  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.3  1999/07/05 14:12:50  rudahl
 *	fixup RCS fields to not use const char[]
 *
 *	Revision 1.2  1999/04/23 01:04:44  rudahl
 *	adapted for WIN32, non-WF environment
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:30:18  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:30:18  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1993/02/11  10:58:44  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1993/02/11  10:58:44  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *	non-ANSI (rev ?) library functions used:
 *
 *
 *	non-Posix (rev ?) library functions used:
 *
 *
 *	Current maintenance status of $Id: tool_sa.c,v 1.4 2014/12/17 07:20:39 rudahl Exp $
 *
 *					Preliminary		Detailed
 *					(date  & rev)		(date & rev)
 *	----------------------		-------------		------------
 *
 *  Stylized file format (this info)	92/12/18 4.0______	_______________
 *
 *  Delete unneeded header files    	__________________	_______________
 *
 *  convert zortech.h & host.h to  	4.0_______________	_______________
 *	dtypes.h & dlimits.h
 *
 *  Are allocs & strdups checked?   	__________________	_______________
 *
 *      are they freed?             	__________________	_______________
 *
 *  Are strcpy & strcat length limited?	__________________	_______________
 *
 *  Are string buffers adequate size?	__________________	_______________
 *
 *  Are static data elements really   	__________________	_______________
 *	needed?
 *
 *  Are data types portable?        	__________________	_______________
 *
 *  Verify magic numbers & array sizes	__________________	_______________
 *
 *  Checked for ANSI compliance?    	__________________	_______________
 *	(method used:   )
 *
 *  Checked for POSIX compliance?    	__________________	_______________
 *	(method used:   )
 *
 *  lint checked?                    	__________________	_______________
 *	(lint version:     )
 *
 *****************************************************************/
/**/
/*
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. These TOOLxxxx.C
 *    files will not be supplied to users, but TOOLKIT.H will be.
 *
 *    Refer to TOOLKIT.C for general comments. This file contains only
 *    fns to go into stand-alone library
 *
 *		
 * 1.0	6/27/92 ktr	extracted from TOOLKIT.C
 * 4.1	12/11/95	adapt for Watcom 10.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __GCC__
#include <time.h>
#else
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
#include "wf.h"
#ifdef __cplusplus
    }
#endif
#include "stats.h"	/*for module numbers */
#include "files.h"

void TOOL_SA()
    { }		/* just a marker for the line file */

#undef THIS_FILE
#ifdef _DEBUG
static char THIS_FILE[] 
	= "@(#)            compiled DEBUG @ " __DATE__ " " __TIME__;
#else
static char THIS_FILE[] 
	= "@(#)            compiled NODEBUG @ " __DATE__ " " __TIME__;
#endif

/*************************************************************************
 *
 *		private data and fns for Stand-alone programs
 *
 *************************************************************************/

	/* this is mostly not used (since this is stand-alone pgm) */
#ifdef NOTNOW 
/* defined in NO_FGATE case in files.c */
void errstat_set(const uint module,const UINT32 flag,
			const uint level,const char * msg)
	/*	this is a fake one, for use when FGATE is not being linked in
	 */
    {
    }


unsigned long errstat_get(const uint module,const UINT32 flag)
	/*	this is a fake one, for use when FGATE is not being linked in
	 */
    {
    return 0;
    }
#endif

void TOOL_SA_END()
    { }		/* just a marker for the line file */
