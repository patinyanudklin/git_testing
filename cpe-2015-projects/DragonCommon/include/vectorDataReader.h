/*
 *	filename vectorDataReader.h		- 
 *		$Revision: 1.5 $ $Date: 2014/12/05 10:38:00 $	
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
 *   $Id: vectorDataReader.h,v 1.5 2014/12/05 10:38:00 rudahl Exp $
 *   $Log: vectorDataReader.h,v $
 *   Revision 1.5  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.4  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.3  2006/09/17 13:33:35  goldin
 *   deal with special cases
 *
 *   Revision 1.2  2006/08/14 07:19:41  goldin
 *   Debugging new vector framework
 *
 *   Revision 1.1  2006/08/04 08:23:09  goldin
 *   Separate vector reading from base VectorData class
 *
 *
 *
 *******************************************************************
 *   Header file for the VectorDataReader class. This is an abstract
 *   class that will be instantiated in various ways to provide
 *   the ability to read specific vector formats.
 *   This class is roughly analagous to the the ImageReader class,
 *   but the specific methods it provides are quite different.
 *
 *   Created by Sally Goldin, 4 August 2006
 *	
 ****************************************************************
 */
#ifndef VECTORDATAREADER_H
#define VECTORDATAREADER_H	/* signal this file has been loaded */


#ifndef __cplusplus
    typedef void * VectorDataReader;
#endif

#ifdef __cplusplus

class VectorDataReader : public OB
    {
    protected: /* members */
        VectorData * m_pVectorData;       /* Vector data object that owns this reader instance */
	static Class s_class_Base;

    public:  /* methods */
    	 VectorDataReader(int iDebug=0,int iTrace=0);
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB

	/* set the pointer to the parent VectorData instance */
	virtual void setVectorDataPointer(VectorData* pVD) {m_pVectorData = pVD;}  

        /* Read the next vector feature from the vector file. 
	 * This function allocates the structure
         * that is returned. The caller must free the structure by
         * calling freeVecFeature()
         *
         * This function is virtual because it will have a different
         * implementation for each type of vector file.
         *
         * @param  pStatus  0 is returned in this variable for success,
         *                  otherwise an error number
         * @return pointer to new VECFEATURE structure or null if error.
         */
    virtual VECFEATURE * getNextFeature(int* pStatus) = 0;

    /* Debugging functions */

	/* dump current structure values
	 * @param detail	how much detail to include:
	 *			0 => suppress completely
	 *			1 => normal
	 *			2 => extra
	 *			3 => excessive
	 * @param pczTitle	if non-NULL, prefix dump with a title string.
	 * @return		ptr to static buffer containing output
	 */
    const char * dump(int detail, const char * pczTitle) const {return NULL;}
    };

#endif /* c plus plus */
#endif



