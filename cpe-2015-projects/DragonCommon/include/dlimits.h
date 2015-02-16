/*
 *	filename DLIMITS.H
 *		$Revision: 1.7.2.1 $ $Date: 2014/12/10 11:03:58 $	
 *
 *      Copyright 1992-2006 Kurt Rudahl and Sally Goldin
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
 *   $Id: dlimits.h,v 1.7.2.1 2014/12/10 11:03:58 rudahl Exp $
 *   $Log: dlimits.h,v $
 *   Revision 1.7.2.1  2014/12/10 11:03:58  rudahl
 *   unify DragonCommon, (prod) dlimits.h
 *
 *   Revision 1.7  2007/02/06 02:44:06  rudahl
 *   upped MAXVTX
 *
 *   Revision 1.6  2006/08/18 04:35:15  goldin
 *   change max number of vertices per feature
 *
 *   Revision 1.5  2006/02/07 03:04:17  rudahl
 *   got rid of czShort
 *
 *   Revision 1.4  2005/08/02 02:16:04  rudahl
 *   fine-tuning separation into product,common
 *
 *   Revision 1.3  2005/07/22 15:20:31  rudahl
 *   fixed maxlines problem
 *
 *   Revision 1.2  2005/02/18 21:17:44  rudahl
 *   replaced pczLong in filename
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
 ****************************************************************
 *
 *	Defines data range limits and array sizes for use with
 *	all DRAGON-related software.
 *	1. This header file should be included in all source modules,
 *	   immediately after DTYPES.H.
 *	2. All changes in DRAGON processing limits should be reflected in,
 *	   and controlled by, this file.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2004-12-31 ktr	imported from Dragon Academic Edition 5.4.4
 * 5.7	2005-8-1 ktr	conditionalized CONFIGSTRLEN; noved string macros
 * 5.14 2014-12-10 ktr	include DragonCommon/dlimits.h
 *			Do not include anything here which is defined there,
 *			except by first undef-ing it
 */

/* where possible, all sizes are an even number of bytes (providing
 * automatic 16-bit alignment). All string sizes include room for a
 * NULL delimiter
 */

#ifndef DLIMITSO_H
#define DLIMITSO_H

#include "../../DragonCommon/include/dlimits.h"

#define DR_LEVEL2

/* maximum # lines allowed for keyed files */
#define D_MAXKEYEDIMGLINES 1024

/* DRAGON and utilities processed image size */
#define MAXIMGPIX 4096		/* handled by all utilities, ASAP */
#define MAXIMGLINES 4096
#define D_MAXIMGPIX 1024		/* handled by DRAGON internally */
#define D_MAXIMGLINES 1024
#define D_MAXIMAGES 4
#define D_DFLTIMGPIX 1024		/* handled by DRAGON internally */
#define D_DFLTIMGLINES 1024 /* up from 700 2005-7-20 ktr */
#define D_DFLTIMAGES 4
#define _D_LEVEL "Level 2"

#define DEFAULT_SVF_KB 1024 		/* default, in kbytes, if not in .CFG
					 * This sets size of screen v.f. */

#define __STATUS__ _D_LEVEL _D_DBG

/* current vector processing limits in DRAGON */
#define MAXVTX 4000              /* maximum points per figure */
#define MAXPLINE 3000            /* maximum number of figures */   
#define MAXGCP 30                /* maximum number of GCPs accepted. */

	/* user interface stuff - maybe smaller than regular since limited */
	/* by screen width; but also have to consider wide chars */
#define UI_STRINGS 4	/* each is UI_PRINTBUF bytes */
#define UI_FILES   4	/* each is UI_FILENAME_SZ */
#define UI_BIGBUF  1	/* each is UI_BIGBUF_SZ */

#define D_NCLS 4
#define D_NBAND 4

#ifndef EXCLUDE_ALIAS	/* #define EXCLUDE_ALIAS to avoid name conflicts */
#define NCLS 	D_NCLS
#define MAXNCLS D_MAXNCLS
#define NBAND 	D_NBAND
#define MAXIPIX D_MAXIMGPIX
#define MAXIMG	D_MAXIMG
#endif

#define D_MAXVIDHIGH D_MAXIMGLINES
#define D_MAXVIDWIDE D_MAXIMGPIX
#define D_PRINTBUF	1024
#define D_NUMBUF 	32
#endif
