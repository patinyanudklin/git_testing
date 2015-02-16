#include "drelease.h"
 ID_ DRAGON_ERRS_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.4 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/****************************************************************
 *
 *		>> dragon-errors.c <<	
 *
 *          by K.T. Rudahl
 *          $Revision: 1.4 $ $Date: 2014/12/05 14:24:30 $
 *
 *          ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 ***************************************************************
 *  $Id: dragon-errors.c,v 1.4 2014/12/05 14:24:30 rudahl Exp $
 *  $Log: dragon-errors.c,v $
 *  Revision 1.4  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.3  2008/08/17 06:04:23  rudahl
 *  minor fix
 *
 *  Revision 1.2  2005/03/19 06:31:51  rudahl
 *  CVS moved from windu; maybe some history lost
 *
 *  Revision 1.3  2005/03/16 04:06:53  rudahl
 *  fixing writeTrailer tests
 *
 *  Revision 1.2  2005/03/10 21:33:33  goldin
 *  Working on new test
 *
 *  Revision 1.1  2005/02/10 03:51:27  rudahl
 *  cleaned up tracing and error handling
 *  cleaned up image file writing
 *
 *  Revision 1.7  2005/01/04 16:15:37  rudahl
 *  converting to 5.5
 *
 *  Revision 1.6  2004/12/31 09:19:09  rudahl
 *  adapt and simplify from Dragon 5.4.4
 *
 *  Revision 1.5  2002/04/17 23:09:45  rudahl
 *  fixups for 32-bit, long filenames
 *
 *  Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *  first checkin of only SOME common dirs
 *
 ***************************************************************
 *
 * return a text string describing standard errors
 * 
 ***************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	 history
 *	2005-02-08 ktr	created
 ***************************************************************/

#include <string.h>
#include <stdio.h>
//#include <stdlib.h>

#include "dtypes.h"
#include "dlimits.h"  /* for NOTNULL macro */
#include "dragon-errors.h"

static char * ErrorMsgs[] = { ERROR_MESSAGES } ;

	/* return an English text string describing iErrno */
const char * dragonErrorMessage(int iErrno)
    {
    int iMinErrno = -iErrno;
    return (iErrno > 0) ? "Invalid (positive) error number"
       : (iMinErrno > (int) AY_COUNT(ErrorMsgs)) ? "Outside range of standard errors"
	: (strlen(ErrorMsgs[iMinErrno]) == 0) ? "Undefined error"
	: ErrorMsgs[iMinErrno];
    }

void DRAGONERRORS_END() { puts(FIL_ID); }

