#include "drelease.h"
ID_ FILES_ID[] = 
   "\0@(#) " __FILE__ "    $Revision: 1.39 $$Date: 2014/04/01 07:22:03 $";
D_REL_IDSTR;
/* 
 *	FILES.C - misc functions for use with DRAGON & WF
 *		files.
 *      ~~ Copyright (C) 1988-2014 Kurt T. Rudahl and Sally Goldin
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
 ************************************************************************
 *   $Id: files.c,v 1.39 2014/04/01 07:22:03 rudahl Exp $
 *   $Log: files.c,v $
 *   Revision 1.39  2014/04/01 07:22:03  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.38  2011/05/20 03:55:36  rudahl
 *   good default (infinity) for linux
 *
 *   Revision 1.37  2010/12/11 07:48:48  rudahl
 *   fixed freediskspace
 *
 *   Revision 1.36  2010/12/05 03:55:17  rudahl
 *   added diskfreespace
 *
 *   Revision 1.35  2007/05/18 04:19:52  rudahl
 *   fixed buffer bug in find_first
 *
 *   Revision 1.34  2005/12/31 05:13:05  rudahl
 *   modified arg to rsf
 *
 *   Revision 1.33  2005/12/09 13:33:16  rudahl
 *   rsf was not giving good error reporting
 *
 *   Revision 1.32  2005/08/18 04:43:20  rudahl
 *   fixed bug in stripPath(linux) if no explicit path
 *
 *   Revision 1.31  2005/04/25 10:52:21  rudahl
 *   fixed wsf for large files
 *
 *   Revision 1.30  2005/03/29 09:10:05  goldin
 *   strip off path in find_next, too
 *
 *   Revision 1.29  2005/03/28 09:41:30  goldin
 *   Strip off path in find_first (Linux)
 *
 *   Revision 1.28  2005/03/27 10:41:12  goldin
 *   fix formatting
 *
 *   Revision 1.27  2005/03/23 14:23:57  goldin
 *   rsf seeks were bad
 *
 *   Revision 1.26  2005/03/19 06:31:51  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.26  2005/03/13 02:40:59  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.25  2005/03/03 21:49:54  goldin
 *   Implement remaining revise_ & update_ methods
 *
 *   Revision 1.24  2005/02/16 00:50:06  goldin
 *   Changes to be able to compile under MingW
 *
 *   Revision 1.23  2005/02/16 00:31:29  rudahl
 *   stuff from zfile.c
 *
 *   Revision 1.22  2005/02/16 00:18:58  rudahl
 *   undid prior change
 *
 *   Revision 1.21  2005/02/15 18:56:54  rudahl
 *   fixes for mingw
 *
 *   Revision 1.20  2005/02/11 18:52:00  rudahl
 *   added file_next
 *
 *   Revision 1.19  2005/02/10 03:51:27  rudahl
 *   cleaned up tracing and error handling
 *   cleaned up image file writing
 *
 *   Revision 1.18  2005/01/29 11:52:30  rudahl
 *   adapt for v 5.5
 *
 *   Revision 1.17  2004/12/23 11:50:56  rudahl
 *   replace itoa base sprintf in 32-bit, lint-ish fixes
 *
 *   Revision 1.16  2004/11/30 03:34:25  rudahl
 *   adapt to Mingw 3.4.2 compiler
 *
 *   Revision 1.15  2002/06/25 00:31:53  rudahl
 *   improved error reporting in wfso
 *
 *   Revision 1.14  2002/04/17 23:07:28  rudahl
 *   fixed docs
 *
 *   Revision 1.13  2002/04/09 21:31:33  rudahl
 *   adapt for long filenames
 *
 *   Revision 1.12  2002/02/08 20:27:12  rudahl
 *   made cat() public
 *
 *   Revision 1.11  2002/01/30 13:10:57  rudahl
 *   fixed documentation
 *
 *   Revision 1.10  2001/08/25 20:05:08  rudahl
 *   put in some win32-specific defines
 *
 *   Revision 1.9  2001/08/24 08:39:56  rudahl
 *   adapting for win32
 *
 *   Revision 1.8  2001/08/22 18:27:45  rudahl
 *   fixup for gcc
 *
 *   Revision 1.7  2001/08/22 18:07:58  rudahl
 *   got rid of assignment to errno
 *
 *   Revision 1.6  1999/10/04 14:22:03  rudahl
 *   cosmetic fix
 *
 *   Revision 1.5  1999/07/05 14:12:48  rudahl
 *   fixup RCS fields to not use const char[]
 *
 *   Revision 1.4  1999/07/03 16:55:29  rudahl
 *   rev. split betw. files.c, file_sa.c
 *
 *   Revision 1.3  1999/04/23 01:04:43  rudahl
 *   adapted for WIN32, non-WF environment
 *
 *   Revision 1.2  1999/04/18 21:25:54  rudahl
 *   Minor changes for MSC 32 compile
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.4  1998/03/15  05:56:38  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1998/01/23  13:11:40  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/12/20  15:41:06  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/12/22  21:43:24  tower
 * final for DRAGON 4.0G.
 * removed large char arr
 * array initialization strings to save space.
 * 
 * Revision 4.0  1993/06/28  20:40:10  tower
 * Final for DRAGON Release 4.0
 * 
 * Revision 4.0.1.1  93/03/07  14:17:58  tower
 * improved error checking; updated for Release 4.0
 * 
 * Revision 4.0  92/06/02  10:57:31  tower
 * Cleanup for Zortech 3.0, DRAGON Professional, DTK Toolkit
 * 
 * Revision 3.10  92/03/23  18:01:04  tower
 * for 3.05. Moved GetConfig & GetMsg out to getcfg.c
 * 
 * Revision 3.9  92/03/21  16:43:32  tower
 * final for 3.05. Added GetMsg; changed findfirst usage to access()
 *                 various cleanups. Use  buffer for cat().
 * 
 * Revision 3.7  91/04/15  12:56:10  tower
 * fixed erroneous use of access() for release 3.04
 * 
 * Revision 3.6  91/04/13  15:36:05  tower
 * eliminated use of printf, and changed a findfirst to 'access'
 * for DRAGON 3.04
 * 
 * Revision 3.5  91/02/16  22:43:38  tower
 * minor fixes. Works with Zortech 2.1
 * 
 * Revision 3.4  91/02/13  18:07:31  tower
 * enhanced capabilities for use without FGATE. Define NO_FGATE
 * to enable stand-alone capabilities
 * 
 * Zortech 2.0
 * 
 * Revision 3.3  91/02/03  18:43:51  lcd
 * updated for Zortech C++ 2.1
 * 
 *
 ************************************************************************
 *	This file contains convenience fns for file I/O
 *	see files.h for details. 
 *
 *	compile with TEST for test version (incl. debugging)
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * History
 *	Aug 6, 1989 ktr	added mode 3 for wsf; must add offset later
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *	10/11/97 ktr	added bWsfResetAfterWrite & DosDiskReset()
 *	4/9/02 ktr	moved WFFILE back to files.c - it's private
 *			adapted to long filenames by eliminating some buffers
 * 			and making others long in 32-bits
 * 5.4	11/29/2004 ktr	added provision for Mingw compilation
 *	12/22/2004 ktr	added unistd for linux (for read, lseek, etc)
 * 5.5	2005-1-29 ktr	adapt for Dragon v 5.5, linux, mingw
 *	2005-2011 ktr	merged find_first, find_next from zfile
 * 5.7	2005-12-31 ktr	extended meaning of 'mode' arg for rsf
 * 5.10	2007-5-16 ktr	fixed find_first segvio
 * 6.1	2010-12-02 ktr	added getDiskFreeSpace
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy */
#include <fcntl.h>	/* OPEN parameters	*/
#include <math.h>
#include <limits.h>

#include <ctype.h>
#if defined __GCC__
#define stricmp strcasecmp
#include <glob.h>
#include <unistd.h>
#else
#include <dos.h>
#include <io.h>
#endif

#ifdef _WIN32_xx
#define access      _access
#define chmod       _chmod
#define chsize      _chsize
#define close       _close
#define creat       _creat
#define dup         _dup
#define dup2        _dup2
#define eof         _eof
#define filelength  _filelength
#define isatty      _isatty
#define locking     _locking
#define lseek       _lseek
#define mktemp      _mktemp
#define open        _open
#define read        _read
#define setmode     _setmode
#define sopen       _sopen
#define tell        _tell
#define umask       _umask
#define unlink      _unlink
#define write       _write
#endif // _WIN32

#ifdef __GCC__
#include <sys/stat.h>
#else
#include <sys\stat.h>
#endif
#include <errno.h>
#if defined _MSC_VER
#include <malloc.h>
#define O_NETRDONLY O_RDONLY
#define O_NETRDWR O_RDWR
#define O_RAW _O_RAW
#endif

#if defined __WATCOMC__
//#include <malloc.h>
#define O_NETRDONLY O_RDONLY
#define O_NETRDWR O_RDWR
#define O_RAW O_BINARY
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
 

//#include	"ztoolkit.h"
//#include	"zfilespc.h"
//#include        "zfile.h"

//#include "basemem.h"
//#include "wf.h"
#include "files.h"

void FILES()
    { }		/* just a marker for the link file */

long file_size(const char * pczFileName)
    {
    struct stat sbuf;
    return ((pczFileName != NULL) && (stat(pczFileName,&sbuf) == 0))
	    ? sbuf.st_size : -1;
    }

long fsize(FILE * pFile)
    {
    struct stat sbuf;
    return ((pFile != NULL) && (fstat(fileno(pFile),&sbuf) == 0))
	    ? sbuf.st_size : -1;
    }

#if defined __GCC__
static glob_t globbuf;
static int glob_index = -1;
typedef struct _find_t FIND_t;
static FIND_t f;

/* Given a pathname plus filename string,
 * returns the part after the last separator.
 * which is assumed to be the node plus extension.
 * Tests for the Unix/Linux separator only.
 * @param pczInputFile filename with path
 * @return filename without path (actually, a pointer into the
 *         input buffer.
 */
static char* stripPath(char* pczInputFile)
    {
    char* nodeStart = &pczInputFile[strlen(pczInputFile) - 1];
    while ((nodeStart > pczInputFile) && (*nodeStart != '/'))
	nodeStart--;
    if (*nodeStart == '/')
	nodeStart++;
    return nodeStart;
    }


struct _find_t * find_first(const char * pattern,unsigned int flag)
    {
    FIND_t * ff = NULL;
    int globStat;
    globbuf.gl_offs = 1;
    globStat = glob(pattern,0,NULL,&globbuf);
    char czTemp[PATH_MAX];
    if (globStat == 0)
        {
	ff = &f;
	glob_index = 0;
	strcpy_array(czTemp,globbuf.gl_pathv[glob_index++]);
	f.size = file_size(czTemp);
	strcpy_array(f.name,stripPath(czTemp));
//	logTrace("findFirst found %s",f.name);
        }
    return ff;
    }

struct _find_t * find_next()
    {
    FIND_t * ff = NULL;
    char czTemp[PATH_MAX];
    if (globbuf.gl_pathv[glob_index] != NULL)
        {
	ff = &f;
	strcpy_array(czTemp,globbuf.gl_pathv[glob_index++]);
	f.size = file_size(czTemp);
	strcpy_array(f.name,stripPath(czTemp));
//	logTrace("findNext found %s",f.name);
        }
    return ff;
    }

#else
typedef enum
	 { _ZFILE_FIND1ST, _ZFILE_FINDNXT,
	   _ZFILE_TIME, _ZFILE_SIZE, _ZFILE_RENAME,
	   _ZFILE_COPY, _ZFILE_APPEND,
	   _ZFILE_DIR, _ZFILE_MKDIR
	 } _ZFILE_OPS;

typedef struct
	{
	int errnum;	/* any errno generated */
	int retval;	/* fn return value */
	long auxinfo; 	/* e.g. how many bytes copied */
	const char * fileA;	/* e.g. 'from' */
	const char * fileB;	/* e.g. 'to' */
	_ZFILE_OPS functno;
	} _ZFILE_STATUS ;	/* initially only for file_copy */
				/* spread to others later? */

static struct _find_t local_find;

char found_file_name[NAME_MAX];
static long last_handle = -1;  /*  32 bit also needs this handle for context */
static struct _finddata_t save_find;

static void copy_msfind(const struct _finddata_t msfind)
    {
    /* copy the filename to the static buffer */
    strcpy_array(found_file_name, msfind.name); /* no longer needed 1/02 */
//    if (strlen(msfind.name) < 13)
//       {
       strcpy_array(local_find.name,msfind.name);
//       }
//    else
//       {
//       memset(local_find.name,0,13);
//       }
    /* set the date/time to 0 - finddata_t has only one value */
    local_find.wr_date = local_find.wr_time = 0;
    local_find.attrib = (char) msfind.attrib;
    local_find.size = msfind.size;
    }

static _ZFILE_STATUS zfile_status;

void zfile_setupstatus(const char * fileA,const char * fileB,
			 _ZFILE_OPS functno)
	/*	initialize spec'd values, zero others */
    {
    memset(&zfile_status,0,sizeof(zfile_status));
    zfile_status.fileA = fileA;
    zfile_status.fileB = fileB;
    zfile_status.functno = functno;
    }

int zfile_error(int retval,long auxinfo)
	/*	set errnum & retval and return retval
	 *	'auxinfo' is situation-dependent */
    {
    zfile_status.errnum = errno;
    zfile_status.retval = retval;
    zfile_status.auxinfo = auxinfo;
    return retval;
    }

struct _find_t * find_first(const char * name,const unsigned int attrib)
	/*	MSC & ZOR use similar structures, but aligned differently
	 *	These fns return a MSC struct, which is smaller
	 *	in ZOR case, it is a local static copy
         *
         *      The 32 bit MSC library uses a different structure,
         *      called a _finddata_t. We do the best we can copying
         *      info from that struct to our common _find_t struct.
         *      Note also the 32 bit version does not allow use of
         *      attributes as search criteria, so we ignore attributes
         *      passed in.
	 */
    {
    long retval;
    zfile_setupstatus(name,NULL,_ZFILE_FIND1ST);
#if (defined MSC && !defined _WIN32) || defined __WATCOMC__
    if (_dos_findfirst(name,attrib,&local_find))
	{
	zfile_error(1,attrib);
	return NULL;	/* error */
	}
#endif
    /* clear the buffer */
    memset(found_file_name,0,260);
    retval = _findfirst(name,&save_find);
    if (retval == -1L) /* error */
	{
	zfile_error(1,0);
	if (last_handle != -1)
	    _findclose(last_handle);
        last_handle = -1;
	return NULL;	/* error */
	}
    copy_msfind(save_find);
    last_handle = retval; /* this return value might be needed */
                          /* for find_next */            
    return &local_find;
    }

struct _find_t * find_next()
    {
    int status;
    zfile_setupstatus(NULL,NULL,_ZFILE_FINDNXT);
#if defined MSC && !defined _WIN32
    if (_dos_findnext(&local_find))
	{
	zfile_error(1,0);
	return NULL;	/* error */
	}
#endif
    /* clear the buffer */
    memset(found_file_name,0,260);
    status = _findnext(last_handle,&save_find);
    if (status == -1L) /* error */
	{
	zfile_error(1,0);
	if (last_handle != -1)
	    _findclose(last_handle);
        last_handle = -1;
	return NULL;	/* error */
	}
    copy_msfind(save_find);
    return &local_find;
    }

#endif // ! __GCC__

void find_free()
    {
#ifdef __GCC__
    globfree(&globbuf);
#endif
    }

#if ! defined MSC
/* get total available disk space in the specified directory
 * (For dos/windows, assume first character of directory is a drive)
 * @return	free space (KB) if OK
 *		if free space > LONG_MAX, return LONG_MAX
 *		return -1 if error
 */
long getFreeDiskspace(const char * czDir)
    {
    long totalAvailable;
    double dSize = 0.0;
#ifdef __MINGCC__
    struct _diskfree_t spaceInfo;
    unsigned drive = toupper(czDir[0]) - 'A' + 1; 
    /* unsigned retval = */ 
    _getdiskfree(drive,&spaceInfo);
//    printf("Disk space components: %d %d %d yields size=%f %ld\n",
//	   spaceInfo.avail_clusters,
//	   spaceInfo.sectors_per_cluster,
//	   spaceInfo.bytes_per_sector,
//	   dSize,totalAvailable);
    dSize = (double) spaceInfo.avail_clusters *
      		   (double) spaceInfo.sectors_per_cluster *
      		   (double)spaceInfo.bytes_per_sector;
#else
#ifdef __GCC__
    return LONG_MAX;  // ~~~ don't know how to calculate
#endif
    struct stat buf;
    if (stat(czDir,&buf) != 0)
	totalAvailable = -1;
    else
        {
	printf("Disk space components: type=%d size=%d blksize=%d blocksused=%d\n",
	   (int)buf.st_rdev,(int)buf.st_size,(int)buf.st_blksize,
           (int)buf.st_blocks);
	}
#endif // #if defined __MINGCC__ 
    totalAvailable = (long)(dSize / 1024.0);
    if ((long)(dSize / 1024.0) > LONG_MAX)
	totalAvailable = LONG_MAX;
    return totalAvailable;
    }
#endif

/**/
/*
 *	SMALL file functions
 */

//static int fp=-1;	/* >= 0 is handle of current read file */

#if defined __GCC__  || defined __MINGCC__
#define O_RAW 0
#endif

	/**	read 'size' bytes of small file starting at 'offset':
	 *	@param name	path and name of file
	 *	@param buffer	where to put data
	 *	@param size	size of buffer
	 *	@param offset	where in file to seek to
	 *	@param mode	0 => offset is from start of file
	 *	 	 	2 => offset is from end (like lseek)
	 *			if (mode & 0x1000) => 
	 *				accept less than  'size' bytes of read
	 *	@return 	bytes read 
	 *			<= 0 (Therefore 'size' < 32000)
	 *			-51 => open error
	 *			-52 => seek error
	 *			-53 => read error
	 *			-54 => close error
	 *			-94 => bad mode argument
	 */
int rsf(const char * name,void  * buffer,
	const int size,const SINT32 offset,const int mode)
    {	   
    int status=0,actsize=0;
    FILE * fp;
    int locmode = mode & 0xFFF;
    if ((locmode != 0) && (locmode != 2))
	status = DERR_FN_ARG4;
    else if ((fp = fopen(name,"rb")) == NULL)
	status = DERR_FILE_OPEN;
    else if ((locmode == 0) && fseek(fp,offset,SEEK_SET))
	status = DERR_FILE_SEEK;
    else if ((locmode == 2) && fseek(fp,offset,SEEK_END))
	status = DERR_FILE_SEEK;
    else if (((actsize = fread(buffer,1,size,fp)) != size)
	     && ((mode & 0x1000) == 0))
	status = DERR_FILE_RW;
    else if (fclose(fp))
	status = DERR_FILE_CLOSE;
    return ((status) ? status : actsize);
    }

	/* for local buffering of wsf and rsfgets, maybe rsf later */
#define WFFBUFSIZE 1026	/* incl. extra byte for \n & null terminator */
typedef struct
    {
#ifdef __32BIT__
    char name[PATH_MAX]; /* 32-bit */
#else
    char name[FMSIZE];   /* 16-bit */
#endif
    char * curptr;	/* points somewhere into buffer */
    unsigned long fileoffset;	/* file position of start of buffer - rsfgets only*/
    char buffer[WFFBUFSIZE];
    } WFFILE ;

WFFILE rsfgetsbuf;

BOOL bWsfResetAfterWrite = FALSE;	/* permit external control */

int wsf(const char * name,const void  * buffer,
	const int size,const int mode)
	/*	write 'size' bytes to small file. 
	 *	   mode=0 => replace 'name'
	 *	  	1 => append if 'name' exists
	 *		2 => return -5=error if 'name' exists
	 *		3 => create if doesn't exist or write-in-place
	 *	   if (mode & x8) => buffer until buffer full or EOL ('\n')
	 *		(called WSF_BUFFER)
	 *	   if (mode & x4) => suppress effect of '\n' in WSF_BUFFER mode
	 *		(called WSF_NOFLUSH)
	 *	   return bytes written or < 0 => error 
	 *	    (therefore 'size' < 32000
	 */
    {	   
    const byte  * bufptr = buffer;
    int status=0;
    FILE * fp;
    char * fopenmode="ab";
    switch (mode & 0x3)
	{
	case WSF_TRUNC:
		fopenmode="wb";
		break;
	case WSF_APPEND:
		break;
	case WSF_TEST:
		if (access(name,F_OK) == 0)
		    {
		    status = DERR_FILE_ALREADY;
		    }
	 	break;
	case WSF_OVERWRITE:
		fopenmode="wb";
	 	break;
	}
    if ((fp = fopen(name,fopenmode)) == NULL)
        status = DERR_FILE_OPEN;
    if (status == 0)
	{
	if (size)		/* either non-buffered or too big for buf */
	    {
	    if (fwrite(buffer,1,size,fp) < (unsigned) size)
	    	status = DERR_FILE_RW;
	    }
	if (((mode & WSF_NOFLUSH) == 0) 
	        && (*bufptr + size-1 == '\n'))
	    fflush(fp);
    	if (fclose(fp) < 0)
	    status = DERR_FILE_CLOSE;
	}
    /* this won't work with void buffer */
    return ((status) ? status : size);
    }

#ifdef NOMORE
int wsfo(const char *name,const void  * buffer,
	 const int size,const SINT32 offset)
	/*	write 'size' bytes to small file. Just like wsf mode 3
	 *	except 'offset' tells where in file to write to.
	 *	Therefore if file is too small, or 
	 *		  if offset > 0 and file doesn't exist,
	 *			return -10
	 *	   return bytes written or < 0 => error:
	 *	     -10 => F_WSFO_OPEN_OFFSET - x100*errno
	 *			* non-zero offset > file size
	 * 	     -11 => F_WSFO_CREATE - x100*errno
	 *	     -12 => F_WSFO_SEEK - x100*errno
	 *	     -13 => F_WSFO_WRITE - x100*errno
	 *	     -14 => F_WSFO_CLOSE - x100*errno
	 *	   therefore 'size' < 32000
	 */
    {	   
    const byte  * bufptr = buffer;
    int fp,status=0;			 
#if defined __GCC__ || defined __MINGCC__
    UINT16 openmode = O_RDWR;
#else
    UINT16 openmode = (UINT16)((basemem.osversion < 0x301) ? O_RDWR : O_NETRDWR);
#endif
/*fprintf(stdaux,">FILES wsfo: file=%s offset=%ld size=%d buf=%lp\n",
 *	name,offset,size,buffer);
 */
    errstat_set(M_FILES,F_WSFO_ALL| F_DSK_CRITERR,STAT_CLEAR,NULL);
    if ((fp = zopen(name,openmode | O_RAW )) == -1)
	{
	if (offset > 0L)
	    {
	    status = (errno<<8) + 10;
	    errstat_set(M_FILES,F_WSFO_OPEN_OFFSET,STAT_ERROR,name);
	    }
	if (errno == 3)
	    status = F_DSK_CRITERR;
	else
	    {
//	    if ((fp = creat(name,S_IREAD|S_IWRITE|O_RAW )) == -1)
	    if ((fp = open(name,O_WRONLY | O_RAW | O_CREAT | O_TRUNC,
				S_IREAD | S_IWRITE )) == -1)
		{
	    	status = (errno<<8) + 11;
		}
	    if (status)
	        errstat_set(M_FILES,F_WSFO_CREATE,STAT_ERROR,name);
	    }
	}
    else	/* is file big enough? */
	if (lseek(fp,offset,0) != offset)
	    {
	    status = (errno<<8) + 12;
	    errstat_set(M_FILES,F_WSFO_SEEK,STAT_ERROR,name);
	    }
    if (status == 0)
	{
	if (b_write(fp,bufptr, size) != size)
	    {
	    status = (errno<<8) + 13;
	    errstat_set(M_FILES,DERR_FILE_OPENF_WSFO_WRITE,STAT_ERROR,name);
	    }
	if (close(fp) < 0)
	    {
	    status = (errno<<8) + 14;
	    errstat_set(M_FILES,DERR_FILE_CLOSE,STAT_ERROR,name);
	    }
	}
    if (status)
	{
	char ermsg[UI_PRINTBUF];
	strcpy(ermsg,"WSFO Open error ");
	strcat_array(ermsg,name);
	if (errno == 3)
	    errstat_set(M_FILES,F_DSK_CRITERR,STAT_EXCEPTION,ermsg);
	}
    return ((status) ? -status : size);
    }
#endif

#ifdef NOMORE
char  * rsfgets(char  *str,const UINT16 size,
		   const char *name,const SINT32 offset)
	/*	get a string from a file using rsf. 
	 *	'size' is max buffer size, so actual read is size-1
	 *	If 'offset' == -1L, locally-maintained offset is
	 *	used for file position; otherwise 'offset' must be
	 *	maintained by calling pgm.
	 *	If 'size' == 0, just try reading at 'offset';
	 *	  and returned ptr is significant only as err indicator
	 *	Read is in raw form, so strlen of returned string can 
	 *	be used to maintain current file position.
	 *	return  pointer to string or NULL
	 *
	 *	mod 12/21/90 ktr for rel 3.03 - buffering for rsfgets
	 *		only when using offset == -1 mode
	 */
    {
    int count,length;
    unsigned long newoffset;
	/* following 3 save name & offset of script file during other accesses */
    static char oldspt_name[PATH_MAX];	/* 32-bits */
    static BOOL bOldnameInit = FALSE;
    static ulong oldspt_fileoffset;	/* file position of prev. access */
/*fprintf(stdaux,">FILES rsfgets: file=%s offset=%ld size=%d buf=%lp\n",
 *	name,offset,size,str);
 */
    if (offset != -1L)	/* initialization, or not using local buffering */
	{
	if (strstr(rsfgetsbuf.name,".SPT"))
	    {		/* save info only for script files */
	    strcpy_array(oldspt_name,rsfgetsbuf.name);
	    oldspt_fileoffset=rsfgetsbuf.fileoffset
		+(rsfgetsbuf.curptr-rsfgetsbuf.buffer);
	    }
	strcpy_array(rsfgetsbuf.name,name);
	rsfgetsbuf.curptr = rsfgetsbuf.buffer;
	rsfgetsbuf.fileoffset = offset;
 	*rsfgetsbuf.curptr = '\0';
	}
    else if (stricmp(rsfgetsbuf.name,name))	/* different file */
	{
	if (bOldnameInit && (stricmp(oldspt_name,name)==0))	/* previously accessed? */
	    {					/* restore info */
	    strcpy(rsfgetsbuf.name,oldspt_name);
	    rsfgetsbuf.fileoffset = oldspt_fileoffset;
	    *rsfgetsbuf.buffer='\0';		/* force re-read */
	    rsfgetsbuf.curptr=rsfgetsbuf.buffer;
	    }
	else
	    {
	    char ermsg[UI_PRINTBUF];
	    bOldnameInit = TRUE;
	    strcpy(ermsg,"RSFGETS Uninitialized file ");
	    strcat_array(ermsg,name);
	    errstat_set(M_FILES,F_RSF_READ,STAT_EXCEPTION,ermsg);
	    return NULL;
	    }
	}
    if (size < 2)	/* this is just a test, & to reset locoff */ 
	{
	if (access((char *)name,F_OK)==0)
	    return(str);	/* it's OK */
	if (errno == 3)
	    {
	    char ermsg[UI_PRINTBUF];
	    strcpy(ermsg,"RSFGETS Open error ");
	    strcat_array(ermsg,name);
	    errstat_set(M_FILES,F_DSK_CRITERR,STAT_EXCEPTION,ermsg);
	    }
	return NULL;
	}
    if (((strchr(rsfgetsbuf.curptr,'\n')==NULL) && (rsfgetsbuf.curptr != rsfgetsbuf.buffer))
	    || (offset != -1L) || (*rsfgetsbuf.buffer=='\0') )
	{	/* no complete string available and not EOF, or first read */
	newoffset = rsfgetsbuf.fileoffset+(rsfgetsbuf.curptr-rsfgetsbuf.buffer);
 /*fprintf(stdprn,">RSFGETS about to read %s at %ld; offset=%ld *buffer=x%X\n",
 *  name,newoffset,offset,*rsfgetsbuf.buffer);
 */
	count = rsf(name,rsfgetsbuf.buffer,WFFBUFSIZE-2,newoffset,0);
	if (count<=0)
	    {
	    char ermsg[UI_PRINTBUF];
	    strcpy(ermsg,"RSFGETS read error ");
	    strcat_array(ermsg,name);
	    if (errno == 3)
	    	errstat_set(M_FILES,F_DSK_CRITERR,STAT_EXCEPTION,ermsg);
	    return NULL;
	    }
	rsfgetsbuf.curptr = rsfgetsbuf.buffer;
	rsfgetsbuf.buffer[count] = '\0';
	rsfgetsbuf.fileoffset = newoffset;
	}
    *str = '\0';
/*
    count = rsf(name,str,size-1,locoff,0);
    if (count<=0)
	{
	if (errno == 3)
	    errstat_set(M_FILES,F_DSK_CRITERR,STAT_EXCEPTION,NULL);
	return NULL;
	}
*/
/*    tmpptr = str;*/
/*    tmpptr = strchr(rsfgetsbuf.curptr,'\n'); */
    if (strchr(rsfgetsbuf.curptr,'\n') == NULL)
	strcat(rsfgetsbuf.buffer,"\n");
    length = 1 + strchr(rsfgetsbuf.curptr,'\n') - rsfgetsbuf.curptr;
    if ((rsfgetsbuf.curptr + length) > (rsfgetsbuf.buffer + WFFBUFSIZE))
	{
	char ermsg[UI_PRINTBUF];
	strcpy(ermsg,"RSFGETS past EOF ");
	strcat_array(ermsg,name);
	errstat_set(M_FILES,F_DSK_CRITERR,STAT_EXCEPTION,ermsg);
	return NULL;
	}
    if (length >= size)
	{
	char ermsg[UI_PRINTBUF];
	strcpy(ermsg,"RSFGETS line too long: ");
	strcat_array(ermsg,name);
	errstat_set(M_FILES,F_RSF_READ,STAT_EXCEPTION,ermsg);
	length = size-1;	/* read only what will fit */
	}			/* can get remainder on second read */
    memcpy((byte  *)str,rsfgetsbuf.curptr,length);
    *(str+length)='\0';
    rsfgetsbuf.curptr += length;
/*    while((*tmpptr != 0xA) && count--)	*/	/* find <lf> */
/*	tmpptr++;
    locoff += (long)(++tmpptr - str); 
    *tmpptr = '\0';			*/	/* keep <lf> */
    return (str);
    }
#endif

#ifdef NO_FGATE

void errstat_set(const UINT16 module,const UINT32 flag,
			const UINT16 level,const char * msg)
	/*	this is a fake one, for use when FGATE is not being linked in
	 */
    {
    }

unsigned long errstat_get(const uint module,const UINT32 flag)
	/*	this is a fake one, for use when FGATE is not being linked in
	 */
    {
    return 0;
    }

#endif /* ifdef NO_FGATE */

void FILES_END() { puts(FIL_ID); }		/* just a marker for the line file */
