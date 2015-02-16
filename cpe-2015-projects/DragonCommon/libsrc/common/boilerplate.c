The following header must exist on all module (.c and .cpp) files in the 
OpenDragon project. Replace the text in angle brackets (<>) with
correct values for this file. Then, end the file with a:

#endif


In the case of newly-created files, created by the OpenDragon project,
the copyright line should read:

 *	Copyright <firstyear>-<currentyear> Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri

=============================== cut here =========================
#include "drelease.h"
char <uniquename>_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.2 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/*
 *	filename <name>
 *		$Revision: 1.2 $ $Date: 2014/12/05 14:24:30 $	
 *
 *      ~~ Copyright <firstyear>-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: boilerplate.c,v 1.2 2014/12/05 14:24:30 rudahl Exp $
 *   $Log: boilerplate.c,v $
 *   Revision 1.2  2014/12/05 14:24:30  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.1  2005/01/04 16:29:17  rudahl
 *   new from moochie
 *
 *   Revision 1.2  2005/01/04 15:36:23  rudahl
 *   corrected version number
 ****************************************************************
 * 
 * <include here a few lines describing the purpose of this file>
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	<date> ktr	imported from Dragon Academic Edition rev 5.4.4
 * 
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
<add other standard headers here>

#include "dtypes.h"
#include "dlimits.h"
#include "ob.h"
<add other dragon headers here>

=============================== cut here =========================

#endif
