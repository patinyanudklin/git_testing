/*
 *	filename dp.h
 *		$Revision: 1.12 $ $Date: 2007/06/24 13:01:13 $	
 *
 *      Copyright 2005-2007 Kurt Rudahl and Sally Goldin
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
 *   $Id: dp.h,v 1.12 2007/06/24 13:01:13 rudahl Exp $
 *   $Log: dp.h,v $
 *   Revision 1.12  2007/06/24 13:01:13  rudahl
 *   new macro for setup
 *
 *   Revision 1.11  2007/06/23 13:00:41  rudahl
 *   fix system registration for 5.10.5
 *
 *   Revision 1.10  2007/06/20 01:18:11  rudahl
 *   fine-tuning the validation
 *
 *   Revision 1.9  2005/12/09 13:23:56  rudahl
 *   sync with current serialnumber style
 *
 *   Revision 1.8  2005/09/15 05:38:35  rudahl
 *   fix linkage problems involving dp.cpp, wgetWorkingLines
 *
 *   Revision 1.7  2005/09/12 07:37:40  rudahl
 *   fixes re dp.h
 *
 *   Revision 1.6  2005/04/01 03:13:15  rudahl
 *   working on dragonServer
 *
 *   Revision 1.5  2005/03/04 23:10:13  rudahl
 *   added some bit sets
 *
 *   Revision 1.4  2005/02/23 20:37:40  rudahl
 *   revising grsproc1 for new Image usages*.h
 *
 *   Revision 1.3  2005/02/20 17:11:57  rudahl
 *   keytable code macro
 *
 *   Revision 1.2  2005/02/16 01:08:15  goldin
 *   Add GetProductLevel macro
 *
 *   Revision 1.1  2005/02/15 18:26:19  rudahl
 *   initial from moochie
 *
 *
 ****************************************************************
 * 
 * Functions to distinguish different products
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-02-15 ktr	imported from Dragon Academic Edition rev 5.4.4
 *			functions in img.cpp, img_acc.c, IpcWrap.c
 * 5.7	2005-9-12 ktr	added test to suppress Locked Dragon Demo files
 *	2005-12-8 ktr	added some LICENSE_xx and xx_PRODUCT symbols; 
 */

#if ! defined DP_H
#define DP_H

#define UNAUTH_PRODUCT	0x0
#define ACAD_PRODUCT	0x1
#define OPEN_PRODUCT	0x6
#define DEMO_PRODUCT	0x4
#define UNINIT_PRODUCT	0xFF /* variable not yet set */

// normally the LICENSE is OR_ED with the PRODUCT
#define LICENSE_FLOAT	0x30
#define LICENSE_NO	0x00
#define LICENSE_MASK	0xF0

#define DEFAULT_LICENSE "WEBTIM"


/* Return the product level based on the
 * installation. For OpenDragon, always
 * Academic.
 */
#define GetProductLevel()  0x1 //~~~

#define GET_SN_LEVEL ((pczSerialNum[0] == 'K') \
	? OPEN_PRODUCT | LICENSE_FLOAT : UNAUTH_PRODUCT | LICENSE_NO)

	/* check if specified key is valid 
	 * @return	0 if OK
	 */
#define validate_key(uKey,pImg) 0

	/* Set the keyed line and the key table in the output image.
	 * This is moved here from grsproc1.
	 * @return		0 if OK else complicated error number
	 */
#define setOutputKey(iKeyLine,pOutImage,pSrcImage,pczOpnameKey,pczOperator) 0

        /**
	 * Set working lines and pixels based on the product.
	 */
#define SetProductCapacity() 0

     /* exclude REG, SAV, HEA, CUR, COL, all classification */
#define UNAUTH_SET	0x200D2BBL
     /* add back in CUR, all classification */
#define DEMO_SET	0x7FFDABBL
#define EXEC_SET	0xFFFFFFFL
#define DTK_SET		0xFFFFFFFL

     /* get product bit pattern (less the product bits)
      * @param  uProduct  the product number
      * @return           bit pattern corresponding to specified product
      */
#define ProductBits(uProduct) EXEC_SET

	/* return the bit set appropriate to the current user
	 * This is invoked from DragonServer::main upon starting each op.
	 */
#define getKeyBits(pTab,buf) EXEC_SET

/* prevent some ops which will fail on a locked file */
#define Q_SUPPRESS_LOCKED getIMAGEHDR()->uKey != 0

/* these fns declared im img_acc.h but defined here
 * They may possibly return smaller values than the Image:: equivs
 */
#define GET_WORKING_LINES Image::getWorkingLines()
#define GET_WORKING_PIXELS Image::getWorkingPixels()

#define VERIFY_SN_LEVEL 1

#endif
