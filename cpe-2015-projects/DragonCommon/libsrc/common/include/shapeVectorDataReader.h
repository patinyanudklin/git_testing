/*
 *	filename ShapeVectorDataReader.h		- 
 *		$Revision: 1.5 $ $Date: 2014/12/05 13:41:51 $	
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
 *   $Id: shapeVectorDataReader.h,v 1.5 2014/12/05 13:41:51 rudahl Exp $
 *   $Log: shapeVectorDataReader.h,v $
 *   Revision 1.5  2014/12/05 13:41:51  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.4  2008/04/26 10:55:55  rudahl
 *   improved notices
 *
 *   Revision 1.3  2006/09/17 13:33:35  goldin
 *   deal with special cases
 *
 *   Revision 1.2  2006/08/09 09:48:09  goldin
 *   Adding support for writing shapefiles
 *
 *   Revision 1.1  2006/08/07 10:05:02  goldin
 *   Begin work on support for shape files
 *
 *   Revision 1.1  2006/08/04 11:05:22  goldin
 *   Create header file for Shape-specific vector reading and writing classes
 *
 *
 *
 *******************************************************************
 *   Header file for the ShapeVectorDataReader class. This class knows
 *   how to read data from ESRI Shapefile vector files.
 *
 *   Created by Sally Goldin, 7 August 2006
 *	
 ****************************************************************
 */
#ifndef SHAPEVECTORDATAREADER_H
#define SHAPEVECTORDATAREADER_H	/* signal this file has been loaded */

#ifndef _SHAPEFILE_H_INCLUDED
#define SHPHandle void *
#endif

class ShapeVectorDataReader : public VectorDataReader
    {
    private: /* members */
	static Class s_class_Base;
        SHPHandle  m_hSHP;  /* opaque handle for reading the file */
        int m_nShapeType;
        int m_nEntities;
        int m_currentEntity; 
        int m_currentPart;   /* used to keep track of where we are in 
                              * multipart features
                              */ 
        int m_partCount;     /* if > 0, we are processing a multipart feature */
        double m_adfMinBound[4];
        double m_adfMaxBound[4];


    public:  /* methods */
    	 ShapeVectorDataReader(int iDebug=0,int iTrace=0);
		// @param iDebug	debug level if > than set by OB::OB
		// @param iTrace	trace level if > than set by OB::OB


	/* set the pointer to the parent VectorData instance */
	 void setVectorDataPointer(VectorData* pVD);  

        /** Function to get data from the file ***/
        /** This function opens the file if it is not open **/
 
        /* Read the next vector feature and any fill information
         * from the vector file. This function allocates the structure
         * that is returned. The caller must free the structure by
         * calling freeVecFeature()
         *
         * @param  pStatus  0 is returned in this variable for success,
         *                  otherwise an error number
         * @return pointer to new VECFEATURE structure or null if error.
         */
	VECFEATURE * getNextFeature(int* pStatus);


	/* Test function. Is this a shape file? We base
         * this on the file suffix, plus our ability to 
         * open and read the basic information about the file.
         * @param pczVectorFilename  Name of file to test
	 * @return TRUE if this appears to be a shapefile, else FALSE
         */
        static BOOL vectest(const char* pczVectorFilename);

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

