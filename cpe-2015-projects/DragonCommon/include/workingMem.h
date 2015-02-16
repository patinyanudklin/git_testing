/*
 *	definitions necessary for using functions in  
 *      workingMem.cpp
 *	workingMem.h not used in OpenDragon
 *
 *	~~ Copyright 1992-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: workingMem.h,v 1.3 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: workingMem.h,v $
 *   Revision 1.3  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.2  2007/10/07 09:44:07  goldin
 *   Add new function 'isMatchingWorkingImage'
 *
 *   Revision 1.1  2007/10/03 11:36:19  goldin
 *   Move getMostRecentWorkingImage and related fns to separate source
 *
 ***************************************************
 */

#ifndef WORKINGMEM_H							   
#define WORKINGMEM_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
/* prototypes */


/* Return true if pczPath is '$$m*' on any
 * path. Otherwise return false.
 */
BOOL isWorkingImageFile(const char * pczPath);

/* Return a memory file name conditionalized on the
 * viewport. The filename has the form "$$m1.img" (for
 * iVp == 0) or $$m2.img  (for iVp == 1).
 * If iVp is negative, will return only the prefix
 * "$$m" with no number and no .img extension.
 */
const char * getWorkingImageFile(int iVp); 

/* Return appropriate working memory filename
 * with path, based on passed viewport number.
 */
const char * getWorkingImagePath(int iVp);

/**
 * Return the full filename and path of the most recently
 * created memory image file ($$m1.img or $$m2.img). Returns
 * a pointer to a static buffer which is volatile and should
 * be strduped or copied immediately.
 * Returns an empty string (not NULL) if there is no memory
 * image available at all.
 */
 char* getMostRecentMemoryImage();

/* Check to see if the passed filename is the same
 * as the memory image path for the passed viewport.
 * Return TRUE if the same, else FALSE 
 */
BOOL isMatchingWorkingImage(const char * pczFilename, uint uVp);


#ifdef __cplusplus
        }
#endif

#endif
