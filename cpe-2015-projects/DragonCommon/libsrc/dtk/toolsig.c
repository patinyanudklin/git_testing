#include "drelease.h"
char TOOLSIG_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.4 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*
 *	filename toolsig.c
 *		$Revision: 1.4 $ $Date: 2014/12/17 07:20:39 $	
 *
 *      ~~ Copyright 1999-2014 Kurt Rudahl and Sally Goldin
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
 *****************************************************************
 *	$Id: toolsig.c,v 1.4 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolsig.c,v $
 *	Revision 1.4  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.3  2005/03/19 06:33:30  rudahl
 *	CVS moved from windu; maybe some history lost
 *
 *	Revision 1.3  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.2  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; except for toolcmd6, much work still needed
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *	
 * Revision 4.3  1997/09/06  06:18:20  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:18:20  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1992/11/20  15:18:06  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1992/11/20  15:18:06  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. 
 *    This file contains only
 *    fns to manipulate signatures within DRAGON; 
 *
 *    (Actually, these functions have not yet been implemented.)
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-02-21 seg	imported from Dragon Academic Edition rev 5.4.4
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "dtk6.h"

//#ifndef TEST

void TOOLSIG()
    { }		/* just a marker for the line file */

/*************************************************************************
 *
 *		local data
 *
 *************************************************************************/

/*************************************************************************
 *
 *		public signature functions
 *
 *************************************************************************/

void TOOLSIG_END()
    { puts(FIL_ID); }		/* just a marker for the line file */

#ifdef TEST

#include <stdlib.h>
void main()
    {
    char buf[80];
    int status;
    dtk_init(NULL);
    printf("DRAGON %s running\n",
	(dtk_DragonIsRunning()) ? "IS" : "is NOT");
    }
#endif
