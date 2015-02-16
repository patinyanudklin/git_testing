#include "drelease.h"
char EXTERNIMAGERDR_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.22 $$Date: 2014/12/29 03:28:29 $";
D_REL_IDSTR;

/*
 *	filename externImageReader.cpp
 *		$Revision: 1.22 $Date: 2014/12/29 03:28:29 $	
 *
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
 *   $Id: externImageReader.cpp,v 1.22 2014/12/29 03:28:29 rudahl Exp $
 *   $Log: externImageReader.cpp,v $
 *   Revision 1.22  2014/12/29 03:28:29  rudahl
 *   convert to using dragon version number
 *
 *   Revision 1.21  2014/12/07 12:05:45  rudahl
 *   adapt to OpenDragon
 *
 *   Revision 1.20  2014/12/05 07:05:48  rudahl
 *   working on multi-band import
 *
 *   Revision 1.19  2014/04/01 07:22:21  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.18  2014/03/28 14:51:12  rudahl
 *   working on auto import
 *
 *   Revision 1.17  2011/02/05 10:40:13  rudahl
 *   improved tracing
 *
 *   Revision 1.16  2008/04/26 10:55:55  rudahl
 *   improved notices
 *
 *   Revision 1.15  2007/02/17 10:17:27  goldin
 *   Conditionalize print statements
 *
 *   Revision 1.14  2007/01/29 10:35:22  rudahl
 *   fixed bug parsing Importers file
 *
 *   Revision 1.13  2007/01/27 11:11:36  rudahl
 *   improve tracing
 *
 *   Revision 1.12  2007/01/02 08:13:41  rudahl
 *   externImageReader.cpp
 *
 *   Revision 1.11  2007/01/02 03:09:42  rudahl
 *   permit comments in Importers
 *
 *   Revision 1.10  2007/01/01 14:27:38  rudahl
 *   error in printf
 *
 *   Revision 1.9  2007/01/01 13:35:51  rudahl
 *   improving tracing
 *
 *   Revision 1.8  2007/01/01 11:25:59  rudahl
 *   improved tracing
 *
 *   Revision 1.7  2007/01/01 10:46:31  rudahl
 *   fixes for DOS - again
 *
 *   Revision 1.6  2007/01/01 10:39:58  rudahl
 *   fixes for DOS
 *
 *   Revision 1.5  2007/01/01 10:17:31  rudahl
 *   adapt for dos
 *
 *   Revision 1.4  2007/01/01 04:50:15  rudahl
 *   minor fixes
 *
 *   Revision 1.3  2006/12/31 12:12:41  rudahl
 *   fixing up the external driver and trailer access
 *
 *   Revision 1.2  2006/12/11 07:44:56  rudahl
 *   modified requirements for extern executable
 *
 *   Revision 1.1  2006/11/20 13:29:20  rudahl
 *   added externImageReader
 *
 *
 ****************************************************************
 * 
 * Define a class for reading miscellaneous image files by
 * using external executables.
 * 
 * The read functions are implemented indirectly:
 *  the first invocation causes the external executable to 
 *  read an entire band into a buffer file, which is then
 *  accessed line by line from this driver
 *
 * Each external executable must support a command line of the 
 * following forms:
 *    xxx.exe -b # -o outfile infile	read a band
 *    xxx.exe -t infile			test file, returning errstat=bandcount
 *					   or 0 if not recognized
 *    xxx.exe -d infile			dump file params to stdout
 *    xxx.exe -q			quiet
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.9	2006-11-21 ktr	new
 * 	2006-12-30 ktr	made fully operational
 */

#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <sys/stat.h>

#include "dtypes.h"
#include "dlimits.h"  /* for strcpy_array */
#include "dragon-errors.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "dragonHd.h"
#include "imageReader.h"
#include "foreign.h"
#include "rosefuns.h"
#include "files.h"
#include "dragonImageReader.h"

#include "externImageReader.h"

#define IMPORTERS Logger::HomeFileName("Importers")

Class ExternImageReader::s_class_Base("ExternImageReader","Class for reading external format image files");

		// ctor will correctly init the IMAGEHDR to 
		// valid values indicating that it has not yet
		// been initialized
#if DRAGON_VER >= 6
ExternImageReader::ExternImageReader(int iDebug, int iTrace) : ImageReader(iDebug,iTrace)
#else
uint ExternImageReader::s_uNumBands = 0;

ExternImageReader::ExternImageReader(int iDebug, int iTrace) : DragonImageReader(iDebug,iTrace)
#endif
    {
    m_pClass = &s_class_Base; 
    m_pClass->setSubClass(ImageReader::getBaseClass());
    m_iDebug = iDebug;
    m_iTrace = iTrace;
    m_bImageUpdated = FALSE;
    logTrace("ExternImageReader::ctor");
//    memset(s_czRawImage,0,sizeof(s_czRawImage)); // no no. Set by test()
    }

	// return TRUE if specified file can be handled by this class
	// This fn cannot be virtual since it's static
	// This also sets s_iNumBands which can be retrieved
	// by getNumBands()
	// Test methodology:
	//    1. Read file 'Importers' (in spath)
	//    2. Foreach line in file, which must name an executable,
	//	 run the executable with '-t pczFilename'
	//    3. If it returns with errorlevel=0, save the
	//       executable name and return success
	// @param pczFilename	image data file, possibly without extension
	// @return		TRUE if a valid file pair
BOOL ExternImageReader::test(const char * pczFilename, BOOL bDebug,int iTrace)
    {
#undef FN_NAME
#define FN_NAME "ExternImageReader::test"
    BOOL bRetval = FALSE;
    long importerSize = file_size(IMPORTERS);
    char * pczFilebuf = (char *)calloc(importerSize+1,1);
    char * pName = pczFilebuf;
    if (bDebug)
	fprintf(stderr,"ExternImageReader::test (en) testing %s Importers size=%d\n",
	       pczFilename,importerSize);
    if (iTrace)
	logTrace("ExternImageReader::test (en) testing %s Importers size=%d",
	       pczFilename,importerSize);
    memset(s_czRawImage,0,sizeof(s_czRawImage));
    if (s_pLatestImporter != NULL)
	free(s_pLatestImporter);
    s_pLatestImporter = NULL;
    if (pczFilebuf == NULL)
	return bRetval;
    int rsfstat = rsf(IMPORTERS,pczFilebuf,importerSize,0,0);
    if (rsfstat != importerSize)
	{
	logTrace(FN_NAME " (ex) error reading importer %s size %d != %d",
	    IMPORTERS,rsfstat,importerSize);
	if (bDebug)
	    fprintf(stderr,FN_NAME " (ex) error reading importer %s size %d != %d\n",
		IMPORTERS,rsfstat,importerSize);
	return bRetval;
	}
    while (pName < (pczFilebuf+importerSize))
        {
	struct stat statbuf;
	char czCmdLine[PATH_MAX] = "";
	strtok(pName,"\n");
	int iCmdSize = strlen(pName);
	char * pNext = pName + iCmdSize + 1;
	if ((*pName == '#')   // comment line
	    || (strlen(pName) == strspn(pName," \r\t"))) // empty line
	    {
	    pName = pNext; 
	    continue;
	    }
	if (bDebug)
	    fprintf(stderr,FN_NAME " buf=%p pName='%s' pNext=%p\n",
		    pczFilebuf,NN(pName),pNext);
	if (iTrace)
	    logTrace(FN_NAME " buf=%p pName='%s' pNext=%p\n",
		    pczFilebuf,NN(pName),pNext);
#ifdef __MINGCC__
#else
	if (*pName != '/')
	    strcpy(czCmdLine,"./");
#endif
	strcat_array(czCmdLine,pName);
        strtok(czCmdLine," \r");
#ifdef __MINGCC__
	if (strcasecmp(&czCmdLine[strlen(czCmdLine)-4],".exe") != 0)
	    {strcat_array(czCmdLine,".exe"); }
	while(strchr(czCmdLine,'/') != NULL)
	    *strchr(czCmdLine,'/') = '\\';
#endif
	char * pEndPtr = czCmdLine + strlen(czCmdLine); // remember the end
	if (stat(czCmdLine,&statbuf) != 0)
	    {
	    if (bDebug)
		fprintf(stderr,	FN_NAME " cannot find program '%s'\n",
			czCmdLine);
	    if (iTrace)
		logTrace(FN_NAME " cannot find program '%s'",
			czCmdLine);
	    }
	else
	    {
	    strcat_array(czCmdLine," -t ");
	    if (bDebug || iTrace)
	        {
		strcat_array(czCmdLine," -v ");
		}
	    else
	        {
		strcat_array(czCmdLine," -q ");
		}
	    strcat_array(czCmdLine,pczFilename);
	    if (bDebug)
		fprintf(stderr,FN_NAME " testing program '%s'\n",
			czCmdLine);
	    if (iTrace)
		logTrace(FN_NAME " testing program '%s'",
			czCmdLine);
	    int status = system(czCmdLine);
	    int nbands = status;
#ifdef __MINGCC__
	    nbands &= 0xFF;
#else
	    nbands >>= 8; // ?? ~~~
#endif
	    if (bDebug)
		fprintf(stderr,FN_NAME " testing %s result=%d bands=%d: OK? %s\n",
		       czCmdLine,status,nbands,YESNO(nbands > 0));
	    if (iTrace)
		logTrace(FN_NAME " testing %s result=%d bands=%d: OK? %s",
		       czCmdLine,status,nbands,YESNO(nbands > 0));
	    if (nbands > 0) // || (strncmp(pName,"tif2drag",6) == 0)) //~~~ for test
	        {
		bRetval = TRUE;
		*pEndPtr = '\0';
		s_pLatestImporter = strdup(czCmdLine);
		s_iNumBands = nbands;  // save band count for later
		break;
		}
	    }
	pName = pNext;	
	}
    free(pczFilebuf);
    if (bRetval)
	strcpy_array(s_czRawImage,pczFilename);
    if (bDebug)
	fprintf(stderr,FN_NAME " (ex): file=%s returns %s\n",
	       pczFilename,YESNO(bRetval));
    if (iTrace)
	logTrace(FN_NAME " (ex): file=%s returns %s",
	       pczFilename,YESNO(bRetval));
    return bRetval;
    }

	// read the metadata file 
	// @param pFile		handle of metadata file to read
	// @param pHdr		pointer of IMAGEHDR struct to init.
	// @param pErrNum	pointer to variable to receive errnum
	// @param pImg		do need this
	// @return		TRUE if OK
BOOL ExternImageReader::readHeader(FILE * pFile,IMAGEHDR * pHdr,
				   int * pErrNum, Image * pImg)
    {
    return FALSE; // don't needto implement this one 
    }

	// read the file 
	// This actually extracts band 0 into a Dragon file,
	// then reads the header of that file.
	// Certain header fields (e.g. number of bands, imagetype) will be wrong
	// @param pczImageFile	name of image file
	// @param pHdr		pointer of IMAGEHDR struct to init.
	// @param pErrNum	pointer to variable to receive errnum
	// @param pImg		do need this
	// @return		TRUE if OK
BOOL ExternImageReader::readHeader(const char * pczImagefile,IMAGEHDR * pHdr,
				   int * pErrNum, Image * pImg)
    {
    BOOL bRetval = FALSE;
    const char * czMethod = "ExternImageReader::readHeader";
    if (m_iTrace)
	logTrace("%s (en) file=%s band %d of %d",
	    czMethod, pczImagefile,m_DesiredData.uBandNo,
	    getNumBands());
    if (m_iDebug)
	fprintf(stderr,"%s (en) file=%s band %d\n",
		 czMethod,pczImagefile,m_DesiredData.uBandNo);
	/* s_iNumBands is static and will be changed by pDIReader
	 * Need to restore it afterwards */
    int iSaveNumBands = s_iNumBands;
    int status = _extract_band(pczImagefile,m_DesiredData.uBandNo);
    if (status == 0)
        {
	char czTmpFileName[PATH_MAX]; // name of the temporary file
	const char * kpath = DragonObject::getKpath();
	snprintf(czTmpFileName, sizeof(czTmpFileName),"%s/.imported-%d.img",
		kpath,m_DesiredData.uBandNo);
	FILE * pFp = fopen(czTmpFileName,"rb");
	DragonImageReader * pDIreader = new DragonImageReader(m_iTrace,m_iDebug);
	m_pFp = pDIreader;
	bRetval = pDIreader->readHeader(pFp, pHdr, pErrNum);
	if (m_iDebug)
	    fprintf(stderr,"    %s about to map pImg=%p\n",czMethod,pImg);
	pImg->CloseImage();
	status = pImg->open(czTmpFileName,FALSE,NULL);
	s_iNumBands = iSaveNumBands;
//	logTrace("%s update_original to band %d of %d bands originalfile=%s",
//		 czMethod,m_DesiredData.uBandNo,iSaveNumBands,NN(pczImagefile));
	int udStat = pImg->update_original(iSaveNumBands,
					   m_DesiredData.uBandNo,pczImagefile);
//	if (m_iDebug)
//	    fprintf(stderr,"    %s opened extracted "
//		    "file %s status=%d udStat=%d\n",
//		    czMethod,czTmpFileName,status,udStat);
	}
    else
        {
	fprintf(stderr,"%s (ex) unable to _extract_band status=%d\n",
	       czMethod,status );
	logTrace("%s (ex) unable to _extract_band status=%d",
		 czMethod,status);
	}
    if (status == 0)
	bRetval = TRUE;
    fflush(NULL); // give it a second to finish writing
    if (m_iDebug)
	fprintf(stderr,"%s (ex) filetype='%s' success=%s\n",
	       czMethod,m_pHdr->ftype,YESNO(bRetval) );
    if (m_iTrace)
	logTrace("%s (ex) filetype='%s' bands=%d (saved band count=%d success=%s",
	    czMethod,m_pHdr->ftype,getNumBands(),iSaveNumBands,YESNO(bRetval));
    return bRetval;
    }

/** use the currently known importer fn to extract a temporary band into kpath
 *  @return	0 if success
 */
int ExternImageReader::_extract_band(const char * pczImagefile,int iBandNo)
    {
#undef FN_NAME
#define FN_NAME "ExternImageReader::_extract_band"
    char czCmdLine[PATH_MAX];
    char czFile[PATH_MAX];
    if (m_iDebug)
        fprintf(stderr,FN_NAME " (en) infile=%s bandno=%d\n",pczImagefile,iBandNo);
    if (m_iTrace)
	logTrace(FN_NAME " (en) infile=%s bandno=%d",pczImagefile,iBandNo);
    sprintf(czFile,"%s/.*.img",getKpath()); // remove any old temp image file
    unlink(czFile);
    snprintf(czCmdLine, sizeof(czCmdLine),
	     "%s -b %d %s -q -o %s/.imported-%d.img %s",
	     s_pLatestImporter,iBandNo,(m_iDebug || m_iTrace)?"-v" : "",
	     getKpath(),iBandNo,pczImagefile);
    int retval = system(czCmdLine);
    if (m_iDebug)
        fprintf(stderr,FN_NAME " (ex) returns %d\n\tCmdLine = %s \n",retval,czCmdLine);
    if (m_iTrace)
	logTrace(FN_NAME " (ex) returns %d\n\tCmdLine = %s",retval,czCmdLine);
    return retval;
    }

/* import one or all bands of a file
 * @param pczInfile		path and name of file to convert
 * @param pczOutfilePattern	path and pattern for output file name
 * @param bScale		TRUE => use auto-scaling
 * @param iOutBand		-1 => all bands, or band to convert
 * @param pczComment		NULL or comment to put in header
 *				NOTE not all importers support this
 * @return 			0 for success, 
 *				DERR_FGN_NOTCONVERTED (-102 )
 *				DERR_SPAWN_ERROR (-111)	
 */
int ExternImageReader::importBands(const char * pczInfile, 
				   const char * pczOutfilePattern, 
				   BOOL bScale, int iOutBand,
				   const char * pczComment)
    {
#undef FN_NAME
#define FN_NAME "ExternImageReader::importBands"
    const char * pczImporter = getImporter();
    logTrace(FN_NAME " (en) importer=%s numbands=%d comment=|%s|",
	pczImporter,getNumBands(),NN(pczComment));
    char czErrorFile[20 + PATH_MAX];
    snprintf(czErrorFile,sizeof(czErrorFile),"%s/fconerr.out",getKpath());
    char czCommandLine[50+4*PATH_MAX]; /* cmd, args, + input, output, error paths */ 
    snprintf(czCommandLine,sizeof(czCommandLine),
	    "%s -o %s %s ",pczImporter,pczOutfilePattern,(bScale) ? "-a" : "");
    if (iOutBand >= 0)
	snprintf(czCommandLine+strlen(czCommandLine),
		sizeof(czCommandLine)-strlen(czCommandLine),"-b %d ",iOutBand);
    if (pczComment != NULL)
	snprintf(czCommandLine+strlen(czCommandLine),
		sizeof(czCommandLine)-strlen(czCommandLine),"-c \"%s\" ",pczComment);
    snprintf(czCommandLine+strlen(czCommandLine),
	     sizeof(czCommandLine)-strlen(czCommandLine),
	     " %s > %s/fcon.out 2> %s",pczInfile,getKpath(),czErrorFile);
    logTrace(FN_NAME " About to invoke importer program command=|%s|",czCommandLine);
    int status = system(czCommandLine);
    logTrace(FN_NAME "status %d=x%X returned from system command", status, status);
    if (status != 0)
	status = DERR_SPAWN_ERROR;
    if ((access(czErrorFile,0) == 0) && (file_size(czErrorFile) > 0))
	    /* There was some error */
	status = DERR_FGN_NOTCONVERTED;
    return status;
    }

	         /* how big a buffer do we need? */
size_t ExternImageReader::getLineBufferSize()
    {
    return (m_pFp != NULL) ? ((DragonImageReader *)m_pFp)->getLineBufferSize()
	: (m_pHdr == NULL) ? 0 : m_pHdr->ulLinePitch;
    }

	/* if m_pFp is non-null it's a DragonImageReader so close it
	 * NOTE this is different from the base class implementation
	 * @return	0 
	 *		else close() error status
	 */
int ExternImageReader::close()
    {
    int iRetval = 0;
    if (m_iDebug)
	fprintf(stderr,"ExternImageReader::close (en) m_pFp = %p\n",m_pFp);
    if (m_iTrace)
	logTrace("ExternImageReader::close (en) m_pFp = %p",m_pFp);
    if (m_pFp != NULL)
        {
	DragonImageReader * pFp = (DragonImageReader *)m_pFp;
	iRetval = pFp->close();
	m_pFp = NULL;
	}
    if (m_iTrace)
	logTrace("ExternImageReader::close (ex) returns %d",iRetval);
    return iRetval;
    }

		// return a formatted dump of the class member
const char * ExternImageReader::dump(int detail, 
				      const char * czTitle) const
    {
    char czCmdLine[PATH_MAX];
    const char * kpath = DragonObject::getKpath();
    if (detail > 0)
	{
	if (m_iDebug)
	    printf("ExternImageReader::dump (en) %s\n",czTitle);
	logTrace("ExternImageReader::dump (en) %s",czTitle);
	}
    memset(s_czDumpBuf,0,sizeof(s_czDumpBuf));
    sprintf(s_czDumpBuf,"\n%s\n",(czTitle != NULL) ? czTitle : "ExternImageReader dump");
    if (strlen(s_czRawImage) == 0)
        {
	strcat_array(s_czDumpBuf,"\tNo image file specified");
	return s_czDumpBuf;
        }
    snprintf(czCmdLine, sizeof(czCmdLine),
	     "%s -d -q %s > %s/.imported.data",
	     s_pLatestImporter,s_czRawImage,kpath);
    int status = system(czCmdLine);
    if (detail > 0)
	{
	if (m_iDebug)
	    printf("    dump cmd='%s' result=%d=x%X\n",czCmdLine,status,status);
	logTrace("    dump cmd='%s' result=%d=x%X",czCmdLine,status,status);
	}
    if (status == 0)
        {
	strcat_array(s_czDumpBuf,"\tInfo: ");
	snprintf(czCmdLine, sizeof(czCmdLine),
	     "%s/.imported.data",kpath);
	int rstat = rsf(czCmdLine,s_czDumpBuf+strlen(s_czDumpBuf),
			sizeof(s_czDumpBuf)-strlen(s_czDumpBuf)-1,0,0x1000);
	if (rstat < 0)
	    snprintf(s_czDumpBuf+strlen(s_czDumpBuf),
		     sizeof(s_czDumpBuf)-strlen(s_czDumpBuf),
		     "Error %d=%s rsf of %s",
		     rstat,dragonErrorMessage(rstat),czCmdLine);
	}
    else
	{
	strcat_array(s_czDumpBuf,"\tUnable to read image information");
	}

    if ((detail > 0) && (m_iDebug))
	printf("ExternImageReader::dump (ex)\n");
    return s_czDumpBuf;
    }

	/*	Retrieve a line of pixels from the appropriate
	 *	location into buffer. 
	 *	The base class calcs are OK for file formats where
	 *	lines are sequential pixel data
	 *	or can be overridden in subclasses.
	 *	The image data may be 16-bit data.
	 *	NOTE this fn (and any overloaded fns) does not and should not
	 *	     enforce ProcessRect
	 *
	 *	@param pBuf	pointer to the destination data buffer
	 *	@param uLineNo	image memory line to retrieve data
	 *	@param uBufSize	the size of pBuf
	 *	@param pImg	pointer to IMAGE struct
	 * 	@param pDataSel	NULL or selects data to read
	 *			(at present, ignored for Dragon format files)
	 *	@return 	number of pixels transferred or <= 0 if error
	 *			   -51  open error
	 *			   -53  read error
	 *			   -56  past EOF ?
	 *			   -63  buffer size too small for image line
	 *			   -91  line number bigger than image
	 *			     or errors from fread, fseek
	 */
int ExternImageReader::getImageLine(byte * pBuf, ushort uLineNo,
				    size_t uBufSize,const Image * pImage,
				    IMAGEDATA_SELECTOR * pDataSel)
    {
//    printf("Extern::reading real line %d size=%d\n",uLineNo,uBufSize);
    int iStatus = 0;
//    if (! m_bImageUpdated)
    //   m_bImageUpdated = TRUE;
#ifdef NOMORE
    if (! m_bConvertedToDragon)
	{
	iStatus = _extract_band(s_czRawImage,pDataSel->uBandNo);
	fprintf(stderr,"getImageLine converting band %d\n",pDataSel->uBandNo);
	if (iStatus == 0)
	    {
	    char czTmpFile[PATH_MAX];
	    const char * kpath = DragonObject::getKpath();
	    snprintf(czTmpFile, sizeof(czTmpFile),"%s/.imported-%d.img",
		     kpath,pDataSel->uBandNo);
	    m_bConvertedToDragon = TRUE;
//~~~	    iStatus = pImage->open(czTmpFile,FALSE);
	    }
	}

    if (iStatus == 0)
#endif
	iStatus = ((DragonImageReader *)m_pFp)->getImageLine(pBuf,uLineNo,
							     uBufSize,pImage,
	    						     pDataSel);
    return iStatus;
    }

char * ExternImageReader::s_pLatestImporter = NULL;
char ExternImageReader::s_czRawImage[PATH_MAX]; // the name of the non-Dragon file

void EXTERN_IMG_RDR_END() { puts(FIL_ID); }

#ifdef TEST

extern "C"
{
//static char* czFile[] = { "","mekdmdm.img",
//			  "mek14-1.img","alfagood.img",
//                          "singapore1.img"};
//static char* czFileDescr[] = { "","v 4.1 classified English labels",
//			       "v 1.0 8-bit","v 4.1 16-bit",
//                               "v 5.8 1024 x 1024"};

void usage()
    {
    printf ("Test ExternImageReader class by reading some file\n");
    printf ("Usage: externImageReader.TEST [-v [-v]] [-b #] -f filepath\n");
    printf ("	-v => verbose (-v -v) is even more)\n");
    printf ("	-b # => test reading specified band number (0-based)\n");
    printf ("	       (all tests produce intermediate files named \n"
	    "          and .imported.data\n");
//    printf ("	-t => test number. Available are:\n");
//    printf ("		0 = Read file specified by '-f'\n");
//    for (size_t j=1; j<AY_COUNT(czFile); j++)
//	printf ("		%d = Read file %s: %s\n",
//		j,czFile[j],czFileDescr[j]);
    printf ("	-f => file to read \n");
    exit (1);
    }

int main(int argc, char ** argv)
    {
    int iVerbose = 0;
//    int iTestNum = -1;
    uint uBandNo = 0;
//    int iStatus = 0;
    char czFilename[PATH_MAX] = "";
    if (argc < 2)
	usage();
    while (--argc > 0)
        {
	if (strcmp(*(++argv),"-?") == 0)
	    usage();
	else if (strcmp(*argv,"-v") == 0)
	    iVerbose++;
	else if (strcmp(*argv,"-b") == 0)
	    { uBandNo = atoi(*(++argv)); --argc; }
//	else if (strcmp(*argv,"-t") == 0)
//	    { iTestNum = atoi(*(++argv)); --argc; }
	else if (strcmp(*argv,"-f") == 0)
	    { strcpy(czFilename,*(++argv)); --argc; }
	else
	    usage();
        }
    if (strlen(czFilename) == 0)
	usage();
    if (iVerbose)
        {
	fprintf(stderr,"\nExternImageReader (en) reading from file %s\n",czFilename);
	fprintf(stderr,"    (sizes UINT32=%d uint=%d ushort=%d ulong=%d double=%d)\n",
	       sizeof(UINT32),sizeof(unsigned int),sizeof(ushort),
	       sizeof(ulong),sizeof(double));
	}
    BOOL bTest = ExternImageReader::test(czFilename,1);
    if (!bTest)
        {
	printf ("test() says unrecognized image\n");
	exit(1);
	}
    if (ExternImageReader::getNumBands() <= uBandNo)
        {
	printf ("Requested band %d is larger than %d bands in image\n",
		uBandNo,ExternImageReader::getNumBands());
	exit(1);
	}
    Image img0(iVerbose,0);
    IMAGEDATA_SELECTOR dSEL = {0,0};
    dSEL.uBandNo = uBandNo;
    img0.open(czFilename,FALSE,&dSEL);    
//    ExternImageReader reader(iVerbose,0);

    const IMAGEHDR * hdr = img0.getIMAGEHDR();
//    reader.readHeader(czFilename,&hdr,&iStatus,&img0);
    if (iVerbose)
	fprintf(stderr,"done reading header\n");
    fprintf(stderr,"%s\n\n",img0.dump(0,"Dump of extracted image"));
    int iBufSize = img0.getLineBufferSize();
    
    ushort nLines = hdr->size[0];
    ushort nPix = hdr->size[1];
    fprintf(stderr,"about to read extracted image: band %d of %s "
	   "linebuffer needs %d bytes; linecount=%d pixcount=%d\n",
	   uBandNo,czFilename,iBufSize,nLines,nPix);
    byte * inbuf = (byte *)calloc(iBufSize,1);

    if (inbuf != NULL)
        {
	ushort j;
	int status;
	for (j=0; j<nLines; j++)
	    {
	    status = img0.getImageLine(inbuf,j,iBufSize,&dSEL);
//	    status = reader.getImageLine(inbuf,j,iBufSize,&img0,&dSEL);
	    if (status != nPix)
	        {
		fprintf(stderr,"Error %d reading line %d of %s\n",
		       status,j,czFilename);
		break;
		}
	    fprintf(stderr,"reading line %d = %d\r",j,status);
#ifdef NOTYET
	    if (bOutputLines)
	        {
		if (nBytes > 1) /* scale data to midbuf */
		    {
		    ushort * pIN = (ushort *)inbuf;
		    byte * pMid = midbuf;
		    for (ushort jj=0; jj<nPix; jj++)
			*pMid++ = *pIN++;
		    }
		byte * pMid = midbuf;
		byte * pOut = outbuf;
		for (ushort jj=0; jj<nPix; jj++)
		    {
		    *pOut = *pMid++;
		    pOut += imgout.getImage()->ulPixPitch;
		    }
		int iStat = imgout.putImageLineRaw(outbuf,j,outBytes * nPix);
		if ((j % 50) == 0)
		    printf("	outputting line %d size=%d x %d stat=%d\n",
			   j,outBytes,nPix,iStat);
		if (iStat < 0)
		    break;
	        }
#endif
	    }
	if (status >= 0)
	    fprintf(stderr,"Main succeeded in reading %d lines status=%d\n",j,status);
#ifdef NOTYET
	if (bOutputLines)
	    {
	    status = imgout.rewriteHeader(0,TRUE);
	    fprintf(stderr,"Main creating output file status = %d = %s\n",status,
		   dragonErrorMessage(status));
	    }
#endif
	}
//    img0.CloseImage();
    return 0;
    }
}
#endif
