/*
 *	filename permbits.h
 *
 *          ~~ Copyright 2002-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: permbits.h,v 1.12 2014/12/05 09:58:46 rudahl Exp $
 *	$Log: permbits.h,v $
 *	Revision 1.12  2014/12/05 09:58:46  rudahl
 *	no differences between DragonProf and OpenDragon
 *
 *	Revision 1.11  2005/12/09 13:43:18  rudahl
 *	cleanout debris
 *
 *	Revision 1.10  2005/03/03 16:15:43  rudahl
 *	refinements while converting grstop
 *	
 *	Revision 1.9  2005/03/02 09:02:45  rudahl
 *	adapt product into for v 5.5
 *	
 *	Revision 1.8  2004/12/11 07:46:24  rudahl
 *	
 *	Revision 1.7  2002/09/15 21:34:02  rudahl
 *	more power to the demo
 *	
 *	Revision 1.6  2002/09/05 18:18:23  rudahl
 *	refined DEMO bits
 *	
 *	Revision 1.5  2002/09/05 00:47:17  rudahl
 *	work around keyed images
 *	
 *	Revision 1.4  2002/02/12 23:12:41  goldin
 *	Add new constants for product-based limits
 *	
 *	Revision 1.3  2002/02/08 18:02:50  goldin
 *	Add macros for version test file name and offset
 *	
 *	Revision 1.2  2002/02/06 14:24:31  rudahl
 *	added UNAUTH
 *	
 *	Revision 1.1  2002/01/30 13:06:25  rudahl
 *	initial deposit
 *	
 *
 ****************************************************************
 * This file ddefines the bit patterns which enable different
 * DRAGON operations. It is extracted from the various .WFT files.
 * However, some values have been modified, and at least one (REG) added
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5 	2005-3-2 ktr	imported from Dragon v 5.5
 */

#ifndef PERMBITS_H
#define PERMBITS_H

#ifdef __cplusplus
extern "C" {
#endif

    /* display */
#define OVE_BITS	0x1L
#define REP_BITS	0x2L
#define CLE_BITS	0x2L
//#define LAY_BITS	0x4L

    /* geometry */
#define CAL_BITS	0x8L
#define VEC_BITS	0x10L
#define GCP_BITS	0x10L
#define MEA_BITS	0x20L
#define COO_BITS	0x20L
#define REG_BITS	0x40L

    /* files */
#define SUB_BITS	0x80L
//#define SYS_BITS	0x80L
//#define DIR_BITS	0x100L
//#define FDEL_BITS	0x100L
//#define FREN_BITS	0x100L
//#define FCOP_BITS	0x100L
#define FSAV_BITS	0x100L

    /* utility */
#define ULIS_BITS	0x200L
#define HEA_BITS	0x400L
#define CUR_BITS	0x800L
#define UHIS_BITS	0x1000L
#define SCA_BITS	0x1000L
#define COL_BITS	0x2000L

    /* enhancement */
#define SUM_BITS	0x4000L
#define DIF_BITS	0x4000L
#define SYM_BITS	0x4000L
#define GVI_BITS	0x4000L
#define MAS_BITS	0x4000L
#define REL_BITS	0x4000L
#define RAT_BITS	0x8000L
#define VEG_BITS	0x8000L
#define FIL_BITS	0x10000L

     /* classification */
#define CLIS_BITS	0x20000L
#define REC_BITS	0x20000L
#define DEF_BITS	0x40000L
#define APP_BITS	0x80000L
#define BOX_BITS	0x80000L
#define AUT_BITS	0x100000L
#define MAX_BITS	0x100000L
#define MDM_BITS	0x200000L
#define SHO_BITS	0x200000L
#define HIS_BITS	0x200000L
#define REN_BITS	0x200000L
#define MOD_BITS	0x400000L
#define COP_BITS	0x400000L
#define COM_BITS	0x400000L
#define SAV_BITS	0x400000L
#define DEL_BITS	0x400000L
#define CLU_BITS	0x400000L
#define SLI_BITS	0x800000L
#define AGC_BITS	0x800000L
             /* 1000000 - 8000000 not yet assigned */


     /* is current function enabled in current product?
      * @param  ulPattern the above-defined bit pattern for target fn
      * @return           TRUE if enabled
      */
BOOL QFn(ulong ulPattern);


#ifdef __cplusplus
 } 
#endif

#endif
