/*
 *	filename dragonVectorDataWriter.h	
 *		$Revision: 1.4 $ $Date: 2014/12/05 13:41:51 $	
 *      ~~ Copyright 2006-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: dragonVectorDataWriter.h,v 1.4 2014/12/05 13:41:51 rudahl Exp $
 *   $Log: dragonVectorDataWriter.h,v $
 *   Revision 1.4  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.3  2008/04/26 10:55:55  rudahl
 *   improved notices
 *
 *   Revision 1.2  2006/08/14 07:20:17  goldin
 *   Debugging new vector framework
 *
 *   Revision 1.1  2006/08/04 11:05:22  goldin
 *   Create header file for dragon-specific vector reading and writing classes
 *
 *
 *
 *******************************************************************
 *   Header file for the DragonVectorDataWriter class. This class knows
 *   how to write data into OpenDragon vector files.
 *
 *   Created by Sally Goldin, 4 August 2006
 *	
 ****************************************************************
 */
#ifndef DRAGONVECTORDATAWRITER_H
#define DRAGONVECTORDATAWRITER_H	/* signal this file has been loaded */


class DragonVectorDataWriter : public VectorDataWriter
    {
    private: /* members */
        int m_lastWritten;              /* keep track of sequence numbers when
                                         * writing vectors.
                                         */
        FILE* m_Fp;                     /* If non-null, file is open */
	static Class s_class_Base;

    public:  /* methods */
    	 DragonVectorDataWriter(int iDebug=0,int iTrace=0);
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB



	   /* Write a vector feature to the vector file. 
	    * This function assumes that the header, if any,
	    * has been written. It opens the file for append access,
	    * the first time the function is called. It
	    * closes the file when the function is called with
	    * VECFEATURE* = NULL.
	    * It does NOT free the VECFEATURE structure after use.
	    * The caller is responsible for this.
	    * IFF the feature pointer is NULL, writes an END record
	    * to the file before closing the file.
	    * @param pFeature Pointer to feature data to write. If NULL
	    *                 signals we should write "-END" 
	    * @return 0 for success, negative for error.
	    */  
    int putNextFeature(VECFEATURE* pFeature);


    /* Debugging functions */

	/* dump current values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
    const char * dump(int detail=1, const char * pczTitle=NULL) const;
    };

#endif






