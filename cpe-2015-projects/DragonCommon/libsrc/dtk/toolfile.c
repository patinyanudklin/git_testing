#include "drelease.h"
char TOOLFILE_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.10 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/*
 *	filename toolfile.c
 *		$Revision: 1.10 $ $Date: 2014/12/17 07:20:39 $	
 *
 *      ~~ Copyright 1999-2014 Kurt Rudahl and Sally Goldin
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
 *****************************************************************
 *	$Id: toolfile.c,v 1.10 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: toolfile.c,v $
 *	Revision 1.10  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.9  2006/09/17 05:00:38  rudahl
 *	got rid of 'far' keyword
 *
 *	Revision 1.8  2005/03/19 06:33:30  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.8  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.7  2005/02/21 23:54:10  goldin
 *	First attempt to make toolkit compile; except for toolcmd6, much work still needed
 *	
 *	Revision 1.6  2004/12/11 08:12:00  rudahl
 *	got rid of schar
 *	
 *	Revision 1.5  2002/04/09 21:35:07  rudahl
 *	adapt for long filenames
 *	
 *	Revision 1.4  2001/10/17 19:24:42  rudahl
 *	documentation
 *	
 *	Revision 1.3  2001/10/17 17:20:00  rudahl
 *	changes propagating from revs to filename.c & strsfn
 *	
 *	Revision 1.2  2000/06/02 22:46:31  rudahl
 *	exported GetConfig
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.3  1997/09/06  06:16:38  tower
 * checkin for class class5_0
 * 
 * Revision 4.2  1997/09/06  06:16:38  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.0  1994/01/09  13:11:06  tower
 * initial released version, for use with DRAGON release 4.0.
 * 
 * Revision 1.1  1994/01/09  13:11:06  tower
 * Initial revision
 * 
 *****************************************************************
 *    Functions for creating DRAGON utilities for GRS, and to be
 *    provided as a DRAGON Toolkit for DRAGON customers. 
 *
 *    There is a main() at the end for testing purposes
 *	compile with -dTEST
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.5	2005-02-21 seg	imported from Dragon Academic Edition rev 5.4.4
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#if !defined __GCC__ && !defined __MINGCC__
#include <process.h>
#include <dos.h>
#include <io.h>
#else
#define FA_DIREC 0  /* ~~~ temporary:  does GCC have a way to check if a file is a directory? */
#endif

#ifndef _DLL	// this is really a problem with 16-bit MSC not
		// recognizing __stdcall
//#define _NO_EXPORT 1 
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "filename.h"
//#include "werror.h"
#include "dtk6.h"
#include "toolerr.h"

//#ifndef TEST

void TOOLFILE()
    { }		/* just a marker for the line file */


//#undef THIS_FILE
//#ifdef _DEBUG
//static char THIS_FILE[] 
//	= "\0@(#)            compiled DEBUG @ " __DATE__ " " __TIME__ ;
//#else
//static char THIS_FILE[] 
//	= "\0@(#)            compiled NODEBUG @ " __DATE__ " " __TIME__ ;
//#endif

/*************************************************************************
 *
 *		functions used with TOOLFILE, TOOLIFIL,
 *		for reporting Disk File I/O errors
 *
 *************************************************************************/

/* static */  int fileerror=0;

int remap_file_error(const long filestatus)
	/*	this fn changes the bit mapped status returned by FILES.C
	 *	into a DTK error number
	 *	In fact, all relevent filestatus values are < 64000
	 */
    {
    long locfilestatus = -filestatus;
    fileerror=-1024;
    while ((locfilestatus>>=1) != 0)
	fileerror--;
    return fileerror;
    }

int dtk_FileError(void)
	/*	Return error number for most recent Disk File I/O error
	 *	ERRORS : file i/o error during read:
	 *			DTKE_FILEOPEN 	if not found
	 *			DTKE_FILESEEK	if seek error
	 *			DTKE_FILEREAD	if read error
	 *		 file i/o errors during append:
	 *			DTKE_FILECREATE if unable to create file
	 *			DTKE_FILEAPPNDOPEN if unable to open for append
	 *			DTKE_FILEALREADY if already exists
	 *			DTKE_FILEAPPEND if write error while appending
	 *			DTKE_FILEAPPCLOSE if close error while appending
	 *		 file i/o errors during overwrite:
	 *			DTKE_FILEWRTOPEN if unable to open for overwrite
	 *			DTKE_FILEWRTSEEK if unable to locate overwrite
	 *			  location
	 *			DTKE_FILEWRITE if write error while overwriting
	 *			DTKE_FILEWRTCLOSE if close error while 
	 *			  overwriting
	 */
    {
    return fileerror;
    }

/*************************************************************************
 *
 *		wrappers for files.c filename.c getcfg.c functions
 *
 *************************************************************************/

EXPORT int GRS_EXP_CALL dtk_GetConfig(const achar * name,
					char result[],
					const int destsize)
    {
    int retval=GetConfig(name,result,destsize);
    return (retval < 0) ? DTKE_NO_CFG : retval;
    }

int dtk_fgets(const achar * name,const long offset,achar buf[],const int bufsize)
	/*	get a string from a file at specified file offset.
	 *	'bufsize' is actual size of 'buf'
	 *	If 'offset' == -1L, this has the effect of a 'get-next', 
	 *	but this will be wrong if previous call to dtk_fgets()
	 *	was to a different file.
	 *	Read is in raw form, so strlen of returned string can 
	 *	be used to maintain current file position.
	 *	return number of chars read, or error code
	 *			DTKE_FILEREAD	if any error
	 */
    {
    char * retptr = rsfgets(buf,(UINT16)bufsize,name,offset);
    fileerror=0;
    if (retptr == NULL)
	return fileerror=DTKE_FILEREAD;
    return strlen(buf);
    }

EXPORT int GRS_EXP_CALL dtk_fputs(const achar * name,const achar * string)
	/*	append 'string'' to file 'name'
	 *	The write is buffered, and does not occur until 'string' 
	 *	contains a newline ('\n'). Write is in raw form, 
	 *	so neither '\n' nor '\r' is automatically appended
	 *	return number of chars written, or -1 => error
	 */
    {
    int status=wsf(name,string,strlen(string),WSF_APPEND | 8);
    fileerror=0;
    return (status < 0) ? remap_file_error(status) : status;
    }

int dtk_read(const achar * name,const long offset,byte buf[],const int size)
	/*	read 'size' bytes of small file starting at 'offset':
	 *	return bytes read or <= 0 
	 *			DTKE_FILEOPEN 	if not found
	 *			DTKE_FILESEEK	if seek error
	 *			DTKE_FILEREAD	if read error
         *      modified 11/23/93 to work around problem in DRAGON
       	 *      4.0 FGATE; rsf was not correctly returning status,
         *      if an error. So, if DragonIsRunning, we now get that
         *      info directly from the errstat system.
	 */
    {
    int status;
    status = rsf(name,buf,size,offset,0);
    fileerror=0;
    return (status < 0) ? remap_file_error(status) : status;
    }

int dtk_write(const achar * name,const byte buf[],const int size)
	/*	write 'size' bytes to small file, unbuffered. 
	 *      return bytes written or < 0 => error
	 *	append only
	 */
    {
    int status = wsf(name,buf,size,WSF_APPEND);
    fileerror=0;
    return (status < 0) ? remap_file_error(status) : status;
    }

int dtk_FilenameBuild(const achar * name,
		      const achar * path, const achar * ext,
		      achar result[],const size_t uResultSize)
	/*	create a complete file name in 'result'.
	 *	'name' is whatever the program user might have typed
	 *	If 'name' does not include a path (drive and/or directories)
	 *	    and if 'path' is supplied, 'path' will be used.
	 *	If 'name' does not include an extension
	 *	    and if 'ext' is supplied, 'ext' will be used.
	 *	If 'name' DOES include an extension and if 'ext' is
	 *	     supplied, the supplied extension MUST match 'ext'
	 *	'path' may or may not end in a '\'
	 *	'ext' MUST include the '.' (thus, a required no-extension
	 *	     is indicated by 'ext' = ".")
	 *	Return < 0 (DTKE_BADFILENAME or DTKE_FILENOTFOUND) for error
	 */
    {
    int retval = 0;
    *result='\0';
    if (name != NULL)
        {
	if (strlen(name) < uResultSize)
	    strcpy(result,name);
	else
	    retval = -10;
	}
    if (retval == 0)
        retval = filename(result,uResultSize,(ext) ? ext : "",path,
			  (ext) ? EXT_DEFAULT | EXT_REQ : EXT_DEFAULT, NULL,0);
    //printf("dtk_FileNameBuild name='%s' ext='%s' path='%s' status=%d\n",
	//   name,(ext != NULL) ? ext : "NULL",
	  // (path!=NULL) ? path : "NULL",retval);
    return(retval == FILENOTFOUND) ? DTKE_FILENOTFOUND
                         : (retval<0) ? DTKE_BADFILENAME : 0;
    }

int dtk_FilenameOK(const achar * name)
	/*	is it legal form?
	 */
    {
    int retval;
    achar result[FMSIZE];
    result[0]='\0';
    if (name != NULL) 
	{ strcpy_array(result,name); }
    retval = filename(result,sizeof(result),NULL,NULL,0,NULL,0);
    return(retval<0) ? DTKE_BADFILENAME : 0;
    }

int dtk_FilenamePathOK(const achar * name)
	/*	does the path exist?
	 *	Return 1 if yes, 0 if no (or if 'name' includes a file name)
	 */
    {
    struct _find_t * found = find_first((char *)name,FA_DIREC);
    if ((found == NULL) || ((found->attrib & FA_DIREC) == 0))
       return 0 ;
    else 
       return 1 ;      
    }

int dtk6_FilenameParse(const char * czFullname,
		       char czDrive[],size_t uDriveSize,
		       char czPath[],size_t uPathSize,
		       char czNode[],size_t uNodeSize,
		       char czExt[], size_t uExtSize)
    {
    char * pczFullname = strdup(czFullname);
    int retval = -8;
    if (pczFullname != NULL)
        {
	char * pDrive = NULL, * pPath = NULL, * pNode = NULL, * pExt = NULL;
	retval = strsfn6_grs(pczFullname, 
			     &pDrive, &pPath, &pNode, &pExt, NULL);
	if (retval == 0)
	    {
	    if (pDrive != NULL)
	        {
		if (strlen(pDrive) > uDriveSize-2)
		    retval = -9;
		else
		    sprintf(czDrive,"%s:",pDrive);
	        }
	    if (pPath != NULL)
	        {
		if (strlen(pPath) > uPathSize-2)
		    retval = -9;
		else
		    sprintf(czPath,"%s\\",pPath);
		}
	    if (pNode != NULL)
	        {
		if (strlen(pNode) > uNodeSize-1)
		    retval = -9;
		else
		    strcpy(czNode,pNode);
		}
	    if (pExt != NULL)
	        {
		if (strlen(pExt) > uExtSize-2)
		    retval = -9;
		else
	            sprintf(czExt,".%s",pExt);
		}
	    }
	free(pczFullname);
        }
    return(retval<0) ? DTKE_BADFILENAME : 0;
    }

void TOOLFILE_END()     { puts(FIL_ID); }

#ifdef TEST

#include <stdlib.h>
void main()
    {
    char buf[80];
    int status;
    dtk_init(NULL);
    printf("DRAGON %s running\n",
	(dtk_DragonIsRunning()) ? "IS" : "is NOT");
    }
#endif
