/*
 *	filename shapeVectorDataWriter.h	
 *		$Revision: 1.3 $ $Date: 2014/12/05 13:41:51 $	
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
 *   $Id: shapeVectorDataWriter.h,v 1.3 2014/12/05 13:41:51 rudahl Exp $
 *   $Log: shapeVectorDataWriter.h,v $
 *   Revision 1.3  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.2  2008/04/26 10:55:55  rudahl
 *   improved notices
 *
 *   Revision 1.1  2006/08/09 09:49:07  goldin
 *   Adding support for writing shapefiles
 *
 *
 *
 *******************************************************************
 *   Header file for the ShapeVectorDataWriter class. This class knows
 *   how to write data into ESRI shapefiles.
 *
 *   Created by Sally Goldin, 4 August 2006
 *	
 ****************************************************************
 */
#ifndef SHAPEVECTORDATAWRITER_H
#define SHAPEVECTORDATAWRITER_H	/* signal this file has been loaded */

#ifndef _SHAPEFILE_H_INCLUDED
#define SHPHandle void *
#endif

class ShapeVectorDataWriter : public VectorDataWriter
    {
    private: /* members */
	static Class s_class_Base;
        SHPHandle  m_hSHP;  /* opaque handle for writing the file */
        int m_nShapeType;   /* A shape file can only have figures of one type*/
        int m_dragonFeatureType; /* Translated into Dragon types as 
                                  * specified in vectorData.h
                                  */
        int m_currentEntity; 


    public:  /* methods */
    	 ShapeVectorDataWriter(int iDebug=0,int iTrace=0);
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB

	   /* Update the shape type for the file.
            * This must be done before anything is written
            * to the file.
            * @param type  One of 'P' (polygon), 'L' (polyline)
            *              or 'M' (market). Shape files can handle
            *              other types, but Dragon cannot.
	    * @return TRUE unless some bad type is passed.
            */ 
         BOOL setShapeType(char type);         

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






