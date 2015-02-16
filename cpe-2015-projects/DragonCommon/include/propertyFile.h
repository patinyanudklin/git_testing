/* 
 *	filename PropertyFile.h
 *		$Id: propertyFile.h,v 1.3 2014/12/05 10:38:00 rudahl Exp $	
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
 * $Id: propertyFile.h,v 1.3 2014/12/05 10:38:00 rudahl Exp $
 * $Log: propertyFile.h,v $
 * Revision 1.3  2014/12/05 10:38:00  rudahl
 * no significant differences between DragonProf and OpenDragon
 *
 * Revision 1.2  2008/04/27 10:31:41  rudahl
 * improved notices
 *
 * Revision 1.1  2005/03/19 06:25:44  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.2  2005/03/16 00:06:02  goldin
 * Add bInitialized and isInitialized
 *
 * Revision 1.1  2005/03/13 23:30:05  goldin
 * Begin implementation of new class to replace WritePrivateProfileString
 *
 ****************************************************************
 * 
 * This is the header file for the PropertyFile class.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005-3-13 seg	Created to replace WritePrivateProfileString etc.
 * 
 */

#ifndef PROPERTY_FILE_H
#define PROPERTY_FILE_H

/**
 * This class represents an instance of a file that holds
 * property-value pairs, in a format similar to Windows INI files
 * or Dragon.cfg files, i.e. Property=value. It does not pay
 * any attention to section headers (e.g. [section]) but maintains
 * them in any file where it finds them. 
 * 
 * The class enforces uniqueness of property names, that is, only
 * one instance of a property can exist in any file. The property
 * names are recorded in whatever case they are sent by the caller,
 * but searched in a case-insensitive manner.
 */

class DragonObject;
class Logger;

#define PROPERTY_FILENAME_SZ 255
#define PROPERTY_SZ 64
#define VALUE_SZ 128

class PropertyFile : public DragonObject
    {
      /* METHODS */
    public:
      /* Constructor, does nothing except initialize variables.
       */
      PropertyFile(int iDebug=0, int iTrace=0);

      /* Getter functions
       */
      char* getFileName()
	{ return czFileName; };

      BOOL isDragonConfigFile()
	{ return bDragonConfigFile; };

      BOOL isInitialized()
	{ return bInitialized; };



      /* Associate the object instance with a particular
       * file. The file is not opened until a read or write
       * function is called.
       * @param pczFileName  Name of the file.
       * @param bMustExist   Return an error if the file does not already exist
       * @param bOverwrite    If true, delete the file and start from 
       *                     scratch with the first write.
       * @return 0 if successful, -1 if file doesn't exist when it should
       *         -2 if try to delete and cannot.
       */
      int init(const char* pczFileName, BOOL bMustExist, BOOL bOverwrite);

      /* Read a property and return its value. This function
       * will open and close the file for each call.
       * @param pczSection    Section of file. Not currently used 
       * @param pczProperty   Property we want. Must match exactly except
       *                      for case.
       * @param czValueBuf    Value buffer - for returning the value.
       * @param uBufSize      Size of the value buffer
       * @return  0 if all is ok, negative for error. If property not
       *          found will return 0 plus an empty string in the buffer.
       */
      int readPropertyValue(const char* pczSection,
			    const char* pczProperty,
			    char * czValueBuf, uint uBufSize);

      /* Write a property and its value. This function
       * will open and close the file for each call.
       * If the property already is in the file, we'll replace the
       * value. If the property is not in the file, it will be
       * written, with its value, at the end.
       * @param pczSection    Section of file. Not currently used 
       * @param pczProperty   Property we want. Must match exactly except
       *                      for case.
       * @param pczValue      Value 
       * @return  0 if all is ok, negative for error.
       */
      int writePropertyValue(const char* pczSection,
			     const char* pczProperty,
			     const char* pczValue);

    protected:
 
    private:
	void doError(const char * czMessage,const int iCode);

	/* Scan the file to try and find the specified
         * property. If bRewrite is true, write every
	 * line read to a temporary file. If property is
	 * found, returns with current value in the 
	 * value buffer. If rewriting, does not write
	 * the line with the property to the temp file.
	 * @param  pczProperty  property we are looking for.
	 * @param  czValueBuf   buffer for returning the value
	 * @param  uBufSize     size of the buffer
	 * @param  piStatus     pointer for returning error status
	 * @param  bRewrite     if true, write contents as we read.
	 * @param  tempFp       file pointer for temp file, assumed
	 *                        to be open. Ignored if not bRewrite.
	 * @return true if found, false if not. 0 returned in piStatus
	 * unless there is an IO error.
	 */
       BOOL findProperty(const char* pczProperty, 
                        char * czValueBuf, uint uBufSize, int* piStatus,
                        BOOL bRewrite, FILE* tempFp);

      /* MEMBERS */
    protected: 

	/**
	 * Full filename of file (with path). 
	 */
	char czFileName[PROPERTY_FILENAME_SZ+1];

	/**
	 * Name of temp file used when we are revising
	 * a property file. It is based on the filename with
	 * a .TMP appended
	 */
	char czTempFileName[PROPERTY_FILENAME_SZ+5];

	/**
	 * File pointer if file is open. 
	 */
	FILE* pFp;

	/**
	 * True if this is a dragon.cfg file (based on file name) 
	 */
	BOOL bDragonConfigFile;

	/*
	 * True if successfully initialized with file name.
	 */
	BOOL bInitialized;

    private:
	static Class s_class_Base;

    };

#endif //IPCFILE_H
