/*
 *	filename libdtk.h
 *		$Revision: 1.8 $ $Date: 2014/12/29 03:28:29 $	
 *
 *      ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: libdtk.h,v 1.8 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: libdtk.h,v $
 *   Revision 1.8  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.7  2014/12/05 11:51:02  rudahl
 *   added ifdefs to match DragonProf and OpenDragon
 *
 *   Revision 1.6  2014/03/15 10:24:15  rudahl
 *   missing file
 *
 *   Revision 1.5  2007/01/02 09:33:10  goldin
 *   Added vector header files
 *
 *   Revision 1.4  2006/08/20 07:59:12  goldin
 *   Add signature.h
 *
 *   Revision 1.3  2005/08/02 02:14:17  rudahl
 *   fine-tuning separation into product,common
 *
 *   Revision 1.2  2005/07/29 04:03:27  rudahl
 *   added rosefuns, img_acc
 *
 *   Revision 1.1  2005/07/03 13:29:32  rudahl
 *   initial version
 *
 ****************************************************************
 * 
 * This file is a wrapper to assure that the important Dragon include files
 * are included in the correct sequence.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.7	2005-6-30 ktr	imported from Dragon Academic Edition rev 5.4.4
 *	2005-7-24 ktr	added logger.h, img_acc.h, rosefuns.h
 *	2005-8-1 ktr	added dragonOb.h, stdarg.h; 
 *			removed dlimits.h
 */

#if ! defined LIBDTK_H
#define LIBDTK_H

#include <stdarg.h>
#include "dtypes.h"
#include "dlimits.h"
/* dlimits.h was removed in 2005. Tentatively re-including
 * it in 2006 to support new signature-related functionality
 * in the DTK.
 */
#include "files.h"
#include "dragon-errors.h"

#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "files.h"
#include "img.h"
#if DRAGON_VER >= 6
#include "dragonHd.h"
#endif
#include "vectorData.h"
#include "vectorDataAccess.h"
#include "hdrstats.h"
#include "img_acc.h"
#include "rosefuns.h"
#include "signature.h"

#endif
