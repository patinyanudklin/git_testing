/*
 *	filename vectorDataWriter.h		- 
 *		$Revision: 1.4 $ $Date: 2014/12/05 10:38:00 $	
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
 *   $Id: vectorDataWriter.h,v 1.4 2014/12/05 10:38:00 rudahl Exp $
 *   $Log: vectorDataWriter.h,v $
 *   Revision 1.4  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.3  2008/04/27 10:31:41  rudahl
 *   improved notices
 *
 *   Revision 1.2  2006/08/14 07:19:41  goldin
 *   Debugging new vector framework
 *
 *   Revision 1.1  2006/08/04 11:07:19  goldin
 *   Create class hierarchy similar to that for image classes
 *
 *
 *
 *******************************************************************
 *   Header file for the VectorDataWriterer class. This is an abstract
 *   class that will be instantiated in various ways to provide
 *   the ability to write specific vector formats.
 *   This class is roughly analagous to the the ImageWriter class,
 *   but the specific methods it provides are quite different.
 *
 *   Created by Sally Goldin, 4 August 2006
 *	
 ****************************************************************
 */
#ifndef VECTORDATAWRITER_H
#define VECTORDATAWRITER_H	/* signal this file has been loaded */


#ifndef __cplusplus
extern "C" {
    typedef void * VectorDataWriter;
}  /* end of extern "C" */
#endif

#ifdef __cplusplus

class VectorDataWriter : public OB
    {
    protected: /* members */
        VectorData * m_pVectorData;       /* Vector data object that owns this reader instance */
	static Class s_class_Base;

    public:  /* methods */
    	 VectorDataWriter(int iDebug=0,int iTrace=0);
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB

	/* set the pointer to the parent VectorData instance */
	void setVectorDataPointer(VectorData* pVD) {m_pVectorData = pVD;}  

        /* Write a vector feature to the vector file. 
	 * This function assumes that the header, if any,
	 * has been written. It opens the file for append access,
	 * and closes it after writing.
	 * It does NOT free the VECFEATURE structure after use.
	 * The caller is responsible for this.
         * IFF the feature pointer is NULL, writes an END record
         * to the file. 
         * @param pFeature Pointer to feature data to write. If NULL
         *                 signals we should write "-END" 
         * @return 0 for success, negative for error.
         */  
    virtual int putNextFeature(VECFEATURE* pFeature) = 0;

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



