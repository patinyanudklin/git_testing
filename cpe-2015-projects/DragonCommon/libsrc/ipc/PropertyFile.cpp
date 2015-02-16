extern "C" {
#include "drelease.h"
char PROPERTY_FILE_ID[]=
  "\0@(#) " __FILE__ " $Revision: 1.6 $$Date: 2014/12/06 10:49:20 $";
D_REL_IDSTR;
}
/*
 *	filename PropertyFile.cpp
 *		$Id: PropertyFile.cpp,v 1.6 2014/12/06 10:49:20 rudahl Exp $
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
 * $Id: PropertyFile.cpp,v 1.6 2014/12/06 10:49:20 rudahl Exp $
 * $Log: PropertyFile.cpp,v $
 * Revision 1.6  2014/12/06 10:49:20  rudahl
 * reconciled DragonProfessional with OpenDragon
 *
 * Revision 1.5  2008/04/26 10:55:55  rudahl
 * improved notices
 *
 * Revision 1.4  2005/11/22 04:57:42  rudahl
 * use symbol for dragon.cfg filename
 *
 * Revision 1.3  2005/08/03 08:04:16  goldin
 * Add libraries to make PropertyFile.TEST link
 *
 * Revision 1.2  2005/03/19 09:19:43  rudahl
 * lintish
 *
 * Revision 1.1  2005/03/19 06:34:45  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.3  2005/03/16 00:06:26  goldin
 * Add bInitialized and isInitialized
 *
 * Revision 1.2  2005/03/15 22:53:22  goldin
 * Complete testing
 *
 * Revision 1.1  2005/03/13 23:29:47  goldin
 * Begin implementation of new class to replace WritePrivateProfileString
 *
 ****************************************************************
 * 
 *  This class provides read and write access to "property files"
 *  of a format like Windows INI and the Dragon.CFG file.
 *  It can read and write property-value pairs of the form
 *  PROPERTY_NAME = PROPERTY_VALUE.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/3/13 seg  created to replace WritePrivateProfileString.
 * 5.7	2005-11-19 ktr	use std symbol CFGFILE instead of "dragon.cfg"
 * 
 ********************************************************************
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include <unistd.h>
extern "C" char * strupr(char * p); /* in wfutl/compmisc.c */

#include "dtypes.h"
#include "dragon-errors.h"
#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "propertyFile.h"

Class PropertyFile::s_class_Base("PropertyFile",
				 "File holding property-value pairs");

      /* Constructor, does nothing except initialize variables.
       */
PropertyFile::PropertyFile(int iDebug, int iTrace)
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    memset(czFileName,0, sizeof(czFileName));
    bDragonConfigFile = FALSE;
    bInitialized = FALSE;
    pFp = NULL;
    }

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
int PropertyFile::init(const char* pczFileName, 
		       BOOL bMustExist, BOOL bOverwrite)
   {
   int iRetval = 0;
   memset(czFileName,0,sizeof(czFileName));
   memset(czTempFileName,0,sizeof(czFileName));
   if (bMustExist)
       {
       if (access(pczFileName,F_OK) != 0)
	  iRetval = -1;
       }
   if ((iRetval == 0) && (bOverwrite))
       {
       if (access(pczFileName,F_OK) == 0)
	  {
	  if (remove(pczFileName) != 0)
	      iRetval = -2;
	  }
       /* Create a new file with a single line */
       if (iRetval == 0)
	  {
	  pFp = fopen(pczFileName,"w");
	  if (pFp == NULL)
	      {
	      iRetval = -3;
              } 
	  else
	      {
	      fprintf(pFp,"## Property File ##\n");
	      fclose(pFp);
	      pFp = NULL;
	      }  
	  }
       }
   if (iRetval == 0)
       {
       strncpy(czFileName,pczFileName,PROPERTY_FILENAME_SZ);
       strncpy(czTempFileName,pczFileName,PROPERTY_FILENAME_SZ);
       strcat(czTempFileName,".TMP");
       if (strstr(czFileName,CFGFILE) != NULL) // "dragon.cfg"
	  bDragonConfigFile = TRUE;
//       if (strstr(czFileName,"dragon.cfg") != NULL)
//	  bDragonConfigFile = TRUE;
       bInitialized = TRUE;
       }  
   return iRetval;
   }

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
int PropertyFile::readPropertyValue(const char* pczSection,
				    const char* pczProperty,
				    char * czValueBuf, uint uBufSize)
   {
   int iRetval = 0;
   if (pczProperty != NULL)
       findProperty(pczProperty, 
		czValueBuf,uBufSize, &iRetval, FALSE,NULL);
   return iRetval;
   }

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
int PropertyFile::writePropertyValue(const char* pczSection,
				     const char* pczProperty,
				     const char* pczValue)
   {
   int iRetval = 0;
   BOOL bFound = FALSE;
   char czValueBuf[VALUE_SZ];
   char czInputLine[256];
   /* open the temp file */
   if ((pczProperty == NULL) && (pczValue == NULL))
       return iRetval;  // eventually we may want to write sections
                        // but for now there's nothing to do.
   FILE* tempFp = fopen(czTempFileName,"w");
   if (tempFp == NULL)
      {
      doError("Error opening temporary file", -1);
      iRetval = -1;
      }
   bFound = findProperty(pczProperty, czValueBuf,VALUE_SZ, 
			 &iRetval,TRUE,tempFp);
   if (iRetval == 0)
      {
      fprintf(tempFp,"%s=%s\n",pczProperty,pczValue);
      } 
   /* if we found the property, we may need to write more file lines */
   if ((bFound) && (iRetval == 0)) 
      {
      while (fgets(czInputLine,256,pFp))
	  fprintf(tempFp,"%s",czInputLine);
      }
   if (pFp != NULL)
      fclose(pFp);
   pFp = NULL;
   if (tempFp != NULL)
      fclose(tempFp);
   tempFp = NULL;
   /* RENAME TEMP FILE HERE */
   remove(czFileName);
   rename(czTempFileName,czFileName);
   return iRetval;
   }  

	/* Scan the file to try and find the specified
         * property. If bRewrite is true, write every
	 * line read to a temporary file. If property is
	 * found, returns with current value in the 
	 * value buffer. If rewriting, does not write
	 * the line with the property to the temp file.
	 *
         * NOTE: this function both opens and closes the
         * main file if bRewrite is FALSE. If bRewrite is TRUE,
	 * opens the main file and leaves it open.
	 *
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
BOOL PropertyFile::findProperty(const char* pczProperty, 
				char * czValueBuf, uint uBufSize, 
				int* piStatus,
				BOOL bRewrite, FILE* tempFp)
   {
   BOOL bFound = FALSE;
   char czInput[256];
   char czCopyInput[256];
   *piStatus = 0;
   char* pczPropUpper = strupr(strdup(pczProperty));
   char* pczFilePropUpper = NULL;
   memset(czValueBuf,0,uBufSize);
   pFp = fopen(czFileName,"r");
   if (pFp == NULL)
      {
      doError("Error opening property file", -2);
      *piStatus = -2;
      }
   if ((*piStatus == 0)&& (bRewrite) && (tempFp == NULL))
      {
      doError("Temp file for rewrite is not open", -1);
      *piStatus = -1;
      }
   while ((*piStatus == 0) && (!bFound))
      {
      if (fgets(czInput,256,pFp) == NULL)
	 break;
      /* copy because strtok will modify the original */
      strcpy(czCopyInput,czInput);
      czInput[strlen(czInput) - 1] = '\0'; // zap newline 
      char* first = strtok(czInput,"=");
      if (first != NULL) // this is a property/value
	 {
         pczFilePropUpper = strupr(strdup(first));
	 /* Note that if a user edits a property file, 
	  * he or she must not have any extra spaces
	  * before or after the '=' or the property
	  * and value. Extra spaces will cause a property
	  * not to be found.
	  */
	 if (strcmp(pczFilePropUpper, pczPropUpper) == 0)
	    {
	    bFound = TRUE;
	    char* second = strtok(NULL,"=");
	    if (second != NULL)
	        strncpy(czValueBuf,second,uBufSize); 
	    } 
	 free(pczFilePropUpper);
	 pczFilePropUpper = NULL;
	 }
      if ((bRewrite) && (!bFound))
         fprintf(tempFp,"%s",czCopyInput);
      } 
      free(pczPropUpper);
      pczPropUpper = NULL;
      /* if rewrite is false, this is just looking up a value,
       * so close the file.
       */
      if (!bRewrite)
         fclose(pFp);
      return bFound;
   }   

void PropertyFile::doError(const char * pczMessage, const int iCode)
    {
    Logger::logError(iCode,"PropertyFile %s %s",pczMessage,czFileName);
    }

void PROPERTYFILE_END() { puts(FIL_ID); }

#ifdef TEST
/* Test driver */

int main(int argc, char** argv)
    {
    int iRetval = 0;
    int iOption;
    char buffer[256];
    char filename[256];
    char property[256];
    char value[256];
    PropertyFile *propFile = NULL;

    fprintf(stdout,"Testing PropertyFile - test options:\n");
    fprintf(stdout,"  1 - Write new file\n");
    fprintf(stdout,"  2 - Look up properties in a file\n");
    fprintf(stdout,"  3 - Add properties to existing file\n");
    fprintf(stdout,"Option? ");
    fgets(buffer,256,stdin);
    sscanf(buffer,"%d",&iOption);
    switch (iOption)
       {
       case 1:
         fprintf(stdout,"Enter file name: ");
	 fgets(buffer,256, stdin);
	 sscanf(buffer,"%s",filename);
	 propFile = new PropertyFile(0,0);
	 iRetval = propFile->init(filename,FALSE,TRUE);
	 if (iRetval != 0)
	    {
            fprintf(stderr,"Error initializing property file - %d\n",iRetval);
	    break;
            } 

	 while (iRetval == 0)
	    {
	    fprintf(stdout,"Enter property name: ");
	    fgets(buffer,256, stdin);
	    memset(property,0, 256);
	    sscanf(buffer,"%s",property);
	    if (strlen(property) == 0)
	       break;
	    fprintf(stdout,"Enter property value: ");
	    fgets(buffer,256, stdin);
	    sscanf(buffer,"%s",value);
	    iRetval = propFile->writePropertyValue(NULL,property,value);
	    }
	 break;
       case 2:
         fprintf(stdout,"Enter file name: ");
	 fgets(buffer,256, stdin);
	 sscanf(buffer,"%s",filename);
	 propFile = new PropertyFile(0,0);
	 iRetval = propFile->init(filename,TRUE,FALSE);
	 if (iRetval != 0)
	    {
            fprintf(stderr,"Error initializing property file - %d\n",iRetval);
	    break;
            } 
	 while (iRetval == 0)
	    {
	    fprintf(stdout,"Enter property name: ");
	    fgets(buffer,256, stdin);
	    memset(property,0, 256);
	    sscanf(buffer,"%s",property);
	    if (strlen(property) == 0)
	       break;
	    iRetval = propFile->readPropertyValue((const char*) NULL,
						  (const char*) &property[0],
						  value,256);
	    if (iRetval == 0)
	        {
		if (strlen(value) > 0)
		    fprintf(stdout,"Value for property '%s' is '%s'\n",
			    property, value);
		else 
		    fprintf(stdout,"Property '%s' not found\n", property);
		}
	    else
	        {
		fprintf(stdout,"readPropertyValue returns %d\n", iRetval);
		}
	    }
	 break;
       case 3:
         fprintf(stdout,"Enter file name: ");
	 fgets(buffer,256, stdin);
	 sscanf(buffer,"%s",filename);
	 propFile = new PropertyFile(0,0);
	 iRetval = propFile->init(filename,TRUE,FALSE);
	 if (iRetval != 0)
	    {
            fprintf(stderr,"Error initializing property file - %d\n",iRetval);
	    break;
            } 
	 fprintf(stdout,"File %s a Dragon configuration file\n",
		 (propFile->isDragonConfigFile() ? "IS" : "is NOT"));
	 while (iRetval == 0)
	    {
	    fprintf(stdout,"Enter property name: ");
	    fgets(buffer,256, stdin);
	    memset(property,0, 256);
	    sscanf(buffer,"%s",property);
	    if (strlen(property) == 0)
	       break;
	    fprintf(stdout,"Enter property value: ");
	    fgets(buffer,256, stdin);
	    sscanf(buffer,"%s",value);
	    iRetval = propFile->writePropertyValue(NULL,property,value);
	    }
	 break;
       default:
	 fprintf(stderr,"Invalid option!\n");
       }
    exit(0);
    }

#endif
