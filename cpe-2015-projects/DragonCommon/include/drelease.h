/*
 *	filename DRELEASE.H		- 
 *		$Revision: 1.8.2.4 $ $Date: 2014/12/18 05:21:17 $	
 *
 *      ~~ Copyright 1992-2015 Kurt Rudahl and Sally Goldin
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
 *   $Id: drelease.h,v 1.8.2.4 2014/12/18 05:21:17 rudahl Exp $
 *   $Log: drelease.h,v $
 *   Revision 1.8.2.4  2014/12/18 05:21:17  rudahl
 *   consolidating Dragon and OpenDragon - added DRAGON-VER
 *
 *   Revision 1.8.2.3  2014/12/10 03:03:36  rudahl
 *   added symbol needed by new mingw
 *
 *   Revision 1.8.2.2  2014/02/21 08:25:39  rudahl
 *   upped version number
 *
 *   Revision 1.6  2006/03/04 10:41:15  rudahl
 *   adapt for product-specific builds
 *
 *   Revision 1.5  2006/03/01 04:21:42  rudahl
 *   working on Dragon/ips required some changes here
 *
 *   Revision 1.4  2006/02/26 11:32:40  rudahl
 *   revised to 5.8
 *
 *   Revision 1.3  2005/12/04 11:11:59  rudahl
 *   added product name symbol
 *
 *   Revision 1.2  2005/07/03 13:27:50  rudahl
 *   revise to v 5.7
 *
 *   Revision 1.1  2004/12/31 19:21:28  rudahl
 *   Initial from moochie
 *
 *   Revision 1.2  2004/12/31 02:00:10  rudahl
 *   augmented commentary
 *
 *   Revision 1.1  2004/12/30 23:24:30  rudahl
 *   initial from Dragon Academic Edition
 *
 *
 ****************************************************************
 * 
 *	This file defines some macros which must be used to
 *	embed identification strings within each .c or .cpp file.
 *
 *	Use this as follows:
 *	each .c or .cpp file must start with:
 *		#include "drelease.h"
 *		ID_ <some_unique_name>_ID[] = 
 *			"\0@(#) " __FILE__ " $Revision: 1.8.2.4 $$Date: 2014/12/18 05:21:17 $";
 *		D_REL_IDSTR;
 *
 *****************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2004/12/31 ktr	imported from Dragon Academic Edition 5.4.4
 * 5.7	2005-7-2 ktr	updated to rel 5.7
 * 5.8	2006-2-24 ktr	updated to rel 5.8
 * 5.9	2006-8-7 ktr	updated to rel 5.9
 * 5.12	2012-5-11 ktr	updated to rel 5.12 (skipped 5.11)
 * 5.14	2014-2-15 ktr	updated to rel 5.14 (skipped 5.13)
 */

#ifndef D_RELEASE_H
#define D_RELEASE_H 1

#define VIEWPORT_DATE "January 2015"
// Note: when changing this also must change javasrc/com/grs/gui/ApplicationManager.java
#define D_MAJOR "5."
#define D_MINOR "14"
#define DRAGON_VER 5

#define D_PRODUCT "OpenDragon"
#define _PRODUCT_ "OpenDragon"
#define _OPEN_DRAGON 1

#define DRELBASE 0x353C2000L	/* "5C " */
#ifdef _DEBUG
#define D_OPT "-D"
#define DBG_OPT "DEBUG"
#else
#define D_OPT ""
#define DBG_OPT "NODEBUG"
#endif
#define D_VAR ".a"
#define DVARIENT 0x6BL	/* "k" */

#define DRELEASE DRELBASE | DVARIENT
#define DRELEASEID '@','(','#',')', \
		   DRELBASE>>24,'.',(DRELBASE>>16)&0xFF,'.',DVARIENT
#define VERSION ((ushort) ((DRELBASE >> 24) - '0') << 8) | \
                 (ushort) (((DRELBASE >> 16) & 0xFF) - '0')      
      /* version number for identifying files */
 /* 5.1.nD-L */
#ifndef ID_
#define ID_ char
#define SID_ static char
#else
#define SID_ static ID_ 
#endif 
#define D_RELSTR D_MAJOR D_MINOR D_VAR D_OPT D_MODEL
#define D_REL_IDSTR_VAL \
	"@(#)            " D_PRODUCT " v " D_MAJOR D_MINOR " built " DBG_OPT " @ " __DATE__ " " __TIME__
#define D_REL_IDSTR static char FIL_ID[] = D_REL_IDSTR_VAL
#endif // ifndef D_RELEASE_H
