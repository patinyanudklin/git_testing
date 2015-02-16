#include "drelease.h"
 ID_ OB_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.6 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
//static char sccsid[]="(@)#ERDIMAG.CPP $Date: 2014/12/17 07:20:39 $ $Revision: 1.6 $";
/****************************************************************
 *
 *		>> OB.CPP <<	
 *
 *          by K.T. Rudahl
 *          $Revision: 1.6 $ $Date: 2014/12/17 07:20:39 $
 *
 *          ~~ Copyright 1991-2014 by Goldin-Rudahl Associates
 *                            P.O. Box 9648
 *                            North Amherst, MA 01059 U.S.A.
 *	    ~~ EndC
 ***************************************************************/
//  $Id: ob.cpp,v 1.6 2014/12/17 07:20:39 rudahl Exp $
//  $Log: ob.cpp,v $
//  Revision 1.6  2014/12/17 07:20:39  rudahl
//  consolidating Dragon and OpenDragon
//
//  Revision 1.5  2002/04/17 23:09:45  rudahl
//  fixups for 32-bit, long filenames
//
//  Revision 1.4  2002/04/09 21:34:51  rudahl
//  adapt for long filenames, & fixed bugs
//
//  Revision 1.3  2001/10/17 17:20:01  rudahl
//  changes propagating from revs to filename.c & strsfn
//
//  Revision 1.2  2000/06/03 14:46:23  rudahl
//  fixes for SuSE6.3 GCC
//
//  Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
//  first checkin of only SOME common dirs
//
/*
 * Revision 4.3  1997/09/10  04:40:26  tower
 * checkin for class class5_0
 *
 * Revision 4.2  1997/09/10  04:40:26  tower
 *checkin for class CLASS5_0
 */
// Revision 4.0  1993/12/22  15:22:20  tower
//  updated for use with initial released version of DRAGON programmer's toolkit.
// Revision 1.3  92/06/02  18:30:03  tower
// For Zortech 3.0 and first release of TIF2DRAG & DRAGSCAN
// This is the first released version of this file
// Revision 1.2  92/04/30  14:40:21  tower
// for 3.05: added access() to class File, release() to FileHeader; fixed constructors
// Revision 1.1  92/03/08  12:28:06  tower
// Initial revision
//
/***************************************************************
 *
 * define base classes for a class library
 *   class Class, class OB, class File
 * 
 *	12/20/91 ktr	added 'confidence' return to fileOK()
 *  	3/92		added access() to class File, release() to FileHeader
 * 1.3	5/26/92	ktr	updated to Zortech 3.0
 *			rewrite errorstr to return informative msg
 *	8/14/92	ktr	changed zortech.h --> dtypes.h & dlimits.h
 * 4.1	1/7/95	ktr	fixed error #'s to use DTKE_OB_BASE;
 *			replaced most printf with put
 *      6/3/00 ktr      fixes for gcc for suSE 63
 ***************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef __GCC__
#include <unistd.h>
#include <sys/stat.h>
#else
#include <sys\stat.h>
#include <io.h>
#include <dos.h>
#endif
#include "dtypes.h"
#include "dlimits.h"

#ifdef __cplusplus
extern "C" {
#endif
#include	"ztoolkit.h"
#include	"zfilespc.h"
#include        "zfile.h"
#include "files.h"
#include "filename.h"
#ifdef __cplusplus
  }
#endif
#include "dhead.h"
#ifndef FARNULL
#define FARNULL (void far *) 0L
#endif

#include "toolerr.h"
#include "ob.h"

static Class class_Object("Object");
static Class class_Class("Class");
static Class class_FileHeader("File Header");
static Class class_File("File");
//static Class class_DragonImgFileHeader("DRAGON Image File Header");

Class * OB::isA() const
	{ return &class_Object; }
const Class * OB::desc() 
	{ return &class_Object; }

void OB::printOn()
	{ puts(className()); }
void OB::dumpOn(int detail)
	{ puts(className()); }

Class::Class(char * text,int obdescsize) 
	//	'text' is string naming class
	//	'obdescsize' is size of object descriptor table >= 1
    {
//    nextClass = topClass;	// link for list of all Class objects 
//    topClass = this;
    memset(descr,0,OB_NAMESZ);
    strncpy(descr,text,OB_NAMESZ-1);
    memset(obdescr0,0,OB_0SZ);
    obdescrsz = obdescsize;
    obdescr = (char **) NULL;
    }

void Class::obdescinit()
	//	this is called once, at the first use of obdesc.
	//	should be in constructor, but can't ddue to 'new'
    {
    if (obdescr != NULL)
	return;		// already been done
    if (obdescrsz > 1)
	obdescr = new charptr[obdescrsz];	// last+1 = NULL
    if (obdescr != NULL)
	{
	obdescr[0] = obdescr0;
	memset(obdescr0,0,OB_0SZ);		// 80 bytes
	for (int i=1; i<obdescrsz; i++)
	    obdescr[i] = (char *)NULL;
	}
    }

Class::~Class()
    {
    if (obdescr != NULL)
	{
	obdesc_zap();
	if (obdescrsz > 0)
#if defined MSC || defined __WATCOMC__
	    delete obdescr;
#else
	    delete [obdescrsz] obdescr;
#endif
	obdescr = (char **) NULL;
	}
    }

const int Class::obdesc_zap()
	//	clear obdesc list: zero string[0] & release higher ones
	//	return obdescsz
    {
//printf("Class::obdesc_zap for %s\n",descr);
    memset(obdescr0,0,OB_0SZ);
    if ((obdescrsz > 1) && (obdescr != NULL))
	{
	for(int i=1; i<obdescrsz; i++)
	    {
	    if (obdescr[i] != NULL)
#if defined MSC || defined __WATCOMC__
	    	delete obdescr[i];
#else
	    	delete [strlen(obdescr[i])+1] obdescr[i];
#endif
	    obdescr[i] = (char *)NULL;
	    }
	}
    return obdescrsz;
    } 

const int Class::obdesc_count()
	//	how many lines needed for showing full obdesc:
	//	count '\n' embedded within lines
    {
    int count = 0;
    obdescinit();	// set up obdesc array if not yet done
    for(int i=0; i<obdescrsz; i++)
	{
	if ( (obdescr[i] != NULL) && (strlen(obdescr[i]) > 0) )
	    count++;
	char * tmp = obdescr[i];
	while ((tmp=strchr(tmp,'\n')) != NULL)
	    count++; 
	}
    return count;
    } 

const int Class::obdesc_append(const char * text)
	//	put text into next available obdescr element (above 0)
	//	Return 0 if OK else -1
    {
    obdescinit();	// set up obdesc array if not yet done
    if (obdescrsz > 1)
	{
	for (int i=1; i<obdescrsz; i++)
	    if (obdescr[i] == NULL)
	    	return (obdesc_put(text,i));
	}
    return -1;	// none available
    }

const int Class::obdesc_put(const char * text,const int index)
	//	put text into specified available obdescr element
	//	Return 0 if OK else -1
    {
    obdescinit();	// set up obdesc array if not yet done
    if (index == 0)
	{
	memset(obdescr0,0,sizeof(obdescr0));
	strncpy(obdescr0,text,sizeof(obdescr0)-1);
	}
    else
	{
	if (index >= obdescrsz)
	    return -1;
	if (obdescr[index] != NULL)
#if defined MSC || defined __WATCOMC__
	    delete obdescr[index];
#else
	    delete [strlen(obdescr[index])+1] obdescr[index];
#endif
	obdescr[index] = new char[strlen(text)+1];
	if (obdescr[index] == NULL)
	    return -1;
	strcpy(obdescr[index],text);
	}
    return 0;
    }

FileHeader::FileHeader(const File * ffile)
    {
    if (file != NULL)
	file = (File *)ffile;	// probably won't use this
    header = NULL; 
    hdrsize = 0; 
    hdroffset = 0L;
    hdr_written_flag = 0;	// 1 => hdr has been written to file
    }

long FileHeader::init(const File * ffile,const int size,const long offset)
	//	fn is called after 'header' & 'file' have been initialized 
	//	by the derived class constructor (not called by constructor,
	//	and not at all by class File.
	//	This fn calls virtual fn read() for an 'r' mode file
	//	'size' is size of file hdr info 
	//		(-1 => unknown, 0 => no header ); 
	//	'offset' is where in file it's located.
    {
memtest(81);
    long tmp=0;
//fprintf(stdprn,">FileHeader::inithdr 0 - ffile=%p file=%p header=%p sz=%d\n",
//	ffile,file,header,hdrsize);
    hdr_written_flag = 0;	// 1 => hdr has been written to file
    hdrsize=size;
    hdroffset=offset;
    if (hdrsize>0)
	{
	memset((char *) header,0,hdrsize);
//fprintf(stdprn,">FileHeader::inithdr 1 - file=%p\n",file);
	if (ffile != NULL)	// if there is a file
	    if (ffile->mode == 'r')	// read the header
	        tmp=read();
	}
//fprintf(stdprn,">FileHeader::inithdr 2  read returns %ld\n",tmp);
    return tmp;
    }

void FileHeader::release()
	//	release the hdr buffer
    {
//printf("releasing fileheader\n");
    if (header != NULL)  
#if defined MSC || defined __WATCOMC__
	delete (char*)header;
#else
	delete[hdrsize](char*)header;
#endif
    header=NULL;
    }

const long FileHeader::read()
	//	fn is called after 'header', 'hdrsize', & 'hdrofset'
	//	have been initialized by the derived class constructor.
	//	This is virtual fn, so may be redefined by derived classes;
	//	however, should not be needed unless header is not part of
	//	the actual disk image file.
	// 	return offset in file of end of header, or < 0 => error
    {
//fprintf(stdprn,">FileHeader::read() about to read header: %d bytes at %p\n",
//	hdrsize,header);
//memtest(30);
    if (hdroffset < 0)
	return FILE_BAD_HDR_FN;
    if ((hdrsize>0) && (file != NULL) && (header != NULL))
	{
	if (file->read(NEAR2FAR(header),hdrsize,hdroffset) == hdrsize)
	    {
//memtest(31);
//fprintf(stdprn,">FileHeader::read() successful\n");
	    return (hdroffset+hdrsize);
	    }
	else
	    {
//fprintf(stdprn,">FileHeader::read() failure\n");
	    return FILE_WRITEHDRERR;
	    }
	}
    return 0;
    }

const long FileHeader::write()
	// return offset in file of end of header, or < 0 => error
    {
//fprintf(stdprn,">Fileheader::write - about to write header to %s: %d bytes\n",file->name,hdrsize);
    if (hdroffset < 0)
	return FILE_BAD_HDR_FN;
    if ((hdrsize>0) && (file != NULL))
	{
	hdr_written_flag = 1;	// 1 => hdr has been written to file
				// must set BEFORE calling write()
//fprintf(stdprn,"                   size=%d offset=%ld lines=%d pix=%d loc'n=%p\n",
//		hdrsize,hdroffset,
//		*(int *) header,*(((int *) header)+1),header);
	if (file->write(NEAR2FAR(header),hdrsize,hdroffset) == hdrsize)
	    {
	    release();
	    return hdrsize;
	    }
	else
	    {
	    hdr_written_flag = 0;	// 1 => hdr has been written to file
	    return FILE_WRITEHDRERR;
	    }
	}
    return FILE_BAD_HDR_FN;
    }

Class * FileHeader::isA() const
	{ return &class_FileHeader; }
const Class * FileHeader::desc() 
	{ return &class_FileHeader; }

File::File(const int fmode,const int buffersize)
	//	This is not invoked by derived classes, so calls 'init'
	//	fmode:  'r' => read; 'R' => fastread	
	//		'W' => fast version of 'w'
	//		'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
    {
    init(fmode,buffersize);
    verifier = verify_filename;
    }

int File::init(const int fmode,const int buffersize)
	//	fmode:  'r' => read; 'R' => fastread	
	//		'W' => fast version of 'w'
	//		'x' => error if exists
	//		'a' => append;	'm' => overwrite in place
	//		'w' => delete & write
	//		'b' => copy to .BAK & delete
	//	return error number or 0
	//	'buffersize' can be overridden by 'access'
	//	this is called by constructors, & cannot use derived class
	//		member fns.
	//	must be followed by setting for 'verifier'
    {
//printf(">File::init mode=%X buffersize=%d\n",fmode,buffersize);
    errn = 0;
    mode = (fmode == 'R') ? 'r' : (fmode == 'W') ? 'w' : fmode;
    bFastRead = (fmode == 'R');
    bFastWrite = (fmode == 'W');
    czFileName = (char *) NULL;
    fileHandle = NULL;
    hdr = (FileHeader *)NULL;
    foffset = fstart = fbuf_hwm = 0L;
    buffer = (byte *) NULL;
    bufloc = (mode == 'r') ? -1L : 0L;	// -1 => buffer not yet filled by read.
    bufsize = buffersize;
    return (errn = 0);
    }

const int File::access(const char * fname,const int buffersize)
	//	initializes File access. This fn may be called
	//	mult. times, changing name or size.
	//	return error number (< 0) or buffer size (>= 0)
	//	'fname' may be a tmp name, but only if mode != 'r'
	//	'buffersize' == -1 => use as spec'd in constructor
	//		     == 0 => no buffer
	//	This fn creates a FileHeaer class instance, but 
	//	does nothing with it.
    {
memtest(78);
    int status=0;
    char tmp[FMSIZE];
    if (errn)				// previously-existing error
	return errn;
    status = ( *verifier)(tmp,mode,fname); // get full name into 'tmp'
    //    printf(">ob.cpp:File::access 1: "
    //   "filename=%s; mode=%X; verify_name returns %d\n",
    //   fname,mode,status);
    if (czFileName != NULL)
	free(czFileName);
    if (fileHandle != NULL)
        fclose(fileHandle); /* close it; only open if needed by read, write*/
    fileHandle = NULL;
    //printf(">ob.cpp:File::access 1.5 tmp=%s\n",(tmp != NULL) ? tmp : "NULL");
    czFileName = strdup(tmp);	 // setup 'name' before error exit
    if (czFileName == NULL)
	return (errn = FILE_NOMEM);
    if ((status < 0)			// now return if verify error
	    && (status != FILE_NOT_FOUND))
	return (errn = status);	// from verifier
    if ((mode == 'x') && (::access(tmp,F_OK)==0 ))
	return (errn = FILE_ALREADY);
    if ((mode == 'w') && (::access(tmp,F_OK)==0 ))
	if (remove(tmp) < 0)
	    return (errn = FILE_DELETEFAIL);
    if ((mode == 'b') && (::access(tmp,F_OK)==0 ))
	{
	strcpy(tmp,czFileName);
	status=filename(tmp,sizeof(tmp),".BAK",NULL,EXT_SUB,
			(char *)NULL,0); // just build name
	if ((status >= 0) && (::access(tmp,F_OK)==0 ) && (remove(tmp) < 0))
	    return (errn = FILE_DELETEFAIL);
	if (::access(tmp,F_OK)==0)	// still there?
	    return (errn = FILE_DELETEFAIL);
	rename(czFileName,tmp);		// 'tmp' now has .BAK name 
	}
    if (mode == 'a')
	fstart = size();
    //printf(">File::access 2: name=%p hdr=%p\n",czFileName,hdr);
    if (hdr == NULL)		// only need one copy
	hdr = new FileHeader();	// this does NOT alloc hdr buffer, or read it
    if (hdr == NULL)
	return(errn = FILE_NOMEM);
    if (buffer)
#if defined MSC || defined __WATCOMC__
	delete buffer;
#else
	delete[bufsize] buffer;
#endif
	//printf(">File::access %s bufsize=%d buffersize=%d\n",
	//	fname,bufsize,buffersize);
    if (buffersize >= 0)
	bufsize = buffersize;
    if (bufsize > 0)
	{
	while((buffer = new byte[bufsize]) == NULL)
	    if (bufsize >= 2048)	/* don't bother below 1024 */
		bufsize -= 1024;
	    else
		{
		bufsize = 0;
		buffer = (byte *)NULL;
//		return(errn = FILE_NOMEM);
		break;
		}
	}
    //fprintf(stdprn,">File::access %s bufsize=%d buffersize=%d\n",
    //	fname,bufsize,buffersize);
    //fprintf(stdout,">File::access : %s buffer alloc'd %d bytes\n",fname,bufsize);
    //fprintf(stdprn,">File::access 2: buffer alloc'd at %p (%d bytes)\n",buffer,bufsize);
    //fprintf(stdprn,">File::init 4: file header at %p\n",hdr);
    errn = 0;
    //printf(">File::access 3: name=%p hdr=%p buffer=%p  size=%d\n",
    //	   czFileName,hdr,buffer,bufsize);
    return bufsize;
    }

File::~File()
    {
/*
	printf("deleting File %s at %p, buffer at %p, hdr at %p\n",
	    (name) ? name : " ",this,buffer,hdr);
*/
    if (errn == 0)
	flush();
    if (czFileName) free(czFileName);
#if defined MSC || defined __WATCOMC__
    if (buffer) delete buffer;
#else
    if (buffer) delete [bufsize] buffer;
#endif
    if (hdr) delete hdr;
    }

const int File::fileOK(const char * name)
	//	test whether 'name' is one of these. 
	//	Return >=0 if yes, errn<0 if no
	//	A 'yes' response is in range 0-9, indicating "confidence"
	//	This fn must be replicated for each derived class
    {
    char ebuf[FMSIZE];
    int tmp=verify_filename(ebuf,'r',name);
//printf("File fileOK: %s status=%d\n",name,tmp);
    return (tmp<0) ? tmp : 9;
    }

int File::read(void far * buf, const int count, const long offset)
	//	read from file at next loc'n if 'offset' not spec'd or == -1,
	//	or at offset. Return >0 = bytes read, or error
    {
    int tmp=0,loc_count=count,bufofset=0;
/*
//fprintf(stdprn,">File::read - file %s read of %d bytes at offset=%ld\n",
//	czFileName,count,offset);
//fprintf(stdprn,"\tinto memory at %lp,bufsize=%d, buffer is at %p, bufloc=%ld\n",
//	buf,bufsize,buffer,bufloc);
*/
//memtest(1);
    if (mode != 'r')
	return (errn=FILE_WRONGMODE);
    if (offset == size())
	return FILE_EOF;	// don't set errn - not real error
    if (offset > size())
	return (errn=FILE_PASTEOF);
    if (offset >= 0)
	foffset = offset;	// 'offset'==-1 => foffset maintains position
    if (bFastRead && (fileHandle == NULL))
	fileHandle = fopen(czFileName,"rb");
    if (bFastRead && (fileHandle == NULL))
        bFastRead = FALSE;
    //printf("read 1 handle=%p offset=%ld\n",fileHandle,(long)foffset);
    if (count > bufsize)	// no buffer, or it won't fit
	{
	if (bFastRead)
	    {
	    fseek(fileHandle,foffset,SEEK_SET);
	    tmp = fread(buf,1,count,fileHandle);	// read it directly
	    }
	else
	    tmp = rsf(czFileName,buf,count,foffset,0);	// read it directly
/*
//printf("file %s has been read directly: tmp=%d\n",czFileName,tmp);
*/
	}
    else 
	{
	if(((foffset+count) > (bufloc+bufsize)) // past buffer
		|| (foffset < bufloc)		// preceeds current buffer
		|| (bufloc < 0))		// hasn't had first read
	    {
	    if (bFastRead)
	        {
		fseek(fileHandle,foffset,SEEK_SET);
		tmp = fread(buffer,1,bufsize,fileHandle);
		}
	    else
	        tmp = rsf(czFileName,NEAR2FAR(buffer),bufsize,
			  foffset,0); // read in a new buffer
	    bufloc = foffset;	// remember where on disk buffer is a copy of
	    bufofset = 0;
	    if ((tmp > 0) && (loc_count > tmp))
		loc_count = tmp;		// not enough read in
/*
//printf("file %s read buffer has been filled with %d bytes\n",czFileName,tmp);
*/
	    }
	else
	    {
	    tmp=loc_count;
	    bufofset = (int)(foffset-bufloc);
	    }
	b_memcpy(buf,NEAR2FAR(buffer+bufofset),loc_count);
//	bufofset += loc_count;	// past part read
	}
//printf("file has been read: tmp=%d\n",tmp);
//memtest(10);
    if (tmp > 0)		// successfully got something?
	{
	if (tmp < loc_count)
	    loc_count = tmp;
	foffset += loc_count;
//memtest(11);
	return loc_count;
	}
//memtest(12);
    return(errn = tmp);	// from rsf(), neg. value or 0 only
				// must remap value
    }

int File::write(void far * buf, const int count, const long offset)
	//	write to file at end if 'offset' not spec'd or == -1,
	//	or at offset. 
	//	Return >0 = bytes written, or error
	//	if 'offset' > current size of file+buffersize, is error
	//	if mode is 'a', 'offset' and "size of file" refer to the 
	//	   current chunk - i.e. discounting the initial filesize
	//	if there is a buffer, can write anywhere in the buffer;
	//	   however, unless mode=='m' can write buffer only at EOF.
    {
    int tmp=0, bufofset=0;
    if (mode == 'r')
	return (errn = FILE_WRONGMODE);
    if (hdr->hdr_written_flag==0)	// 1 => hdr has already been written to file
	hdr->write();
//	foffset = foffset + (long) hdr->write();
/*
//fprintf(stdprn,">File::write %d bytes at %ld offset (foffset=%ld, size=%ld)\n",
//	count,offset,foffset,size());
//fprintf(stdprn,"             bufsize=%d bufloc=%ld\n",bufsize,bufloc);
*/
    if ((mode == 'm') && (offset < 0))
	return(errn = FILE_OFFSETNEEDED);
    if ( (bufsize > 0)			// if there is a buffer
	    && (( (offset >= 0) && ( (offset < bufloc) 
			|| ((offset+count) > (bufloc+bufsize)) ))
		|| ((foffset+count) > (bufloc+bufsize)) ))
	{
//printf("flushing file %s\n",czFileName);
	if ((tmp=flush()) < 0)		// flush it, resetting foffset=bufloc=EOF
	    return tmp;
	}
    if ( (offset > foffset)		// trying to write past current EOF
	    && ((offset+count) > (bufloc+bufsize)) ) // & won't fit in buffer
	return(errn = FILE_PASTEOF);
    if (offset >= 0)
	{
	if (offset < bufloc)
	    {
	    if (mode == 'm')
		bufloc = offset;
	    else
		return(errn = FILE_NOTMODIFYMODE);
	    }
	foffset = offset;
	}
    if (bufsize > 0)			// if there is a buffer
	{
	bufofset = (int)(foffset-bufloc);
	b_memcpy(NEAR2FAR(buffer+bufofset),buf,count);
	tmp = count;
	foffset += count;
	}
    else
	{
/*
//fprintf(stdout,">File::write NO buffer: czFileName=%s count=%d buf=%lp fstart=%ld\n",
//		czFileName,count,buf,fstart);
*/
	if (bFastWrite && (fileHandle == NULL))
	    fileHandle = fopen(czFileName,"wb");
	if (bFastWrite && (fileHandle == NULL))
	    bFastWrite = FALSE;
	if (bFastRead)
	    {
	    fseek(fileHandle,foffset,SEEK_SET);
	    tmp = fwrite(buf,1,count,fileHandle);	// write it directly
	    }
	else
	    {
	    if (foffset < (size()-fstart))
	        tmp = wsfo(czFileName,buf,count,foffset+fstart);
	    else
	        tmp = wsf(czFileName,buf,count,WSF_APPEND); // write directly
	    }
	bufloc = foffset = size()-fstart; // these are tested by flush() at end
	}
    if (fbuf_hwm < foffset)
	fbuf_hwm = foffset;
    return (errn) ? errn : tmp;
    }

const int File::flush()
	//	if it's a 'r' mode, clean out variables
	//	else write any partial buffers
	//	Return byte count if OK
    {
    int tmp = 0,bufregion=0;
    if (mode != 'r')
	{
//fprintf(stdprn,">File::flush hwm=%ld bufloc=%ld czFileName=%s\n",fbuf_hwm,bufloc,czFileName);
	if (fbuf_hwm > bufloc)
	    {
	    bufregion = (int)(fbuf_hwm-bufloc);
	    if (bufregion)
		tmp = wsfo(czFileName,NEAR2FAR(buffer),bufregion,bufloc);
	    }
	}
    bufloc = foffset = fbuf_hwm = size() - fstart;
    return tmp;
    }

const int File::verify_filename(char * result, const int mode, const char * root)
	//	construct full path + file name in result
	//	'result' is a FMSIZE-byte pre-alloc'd buffer.
	//	return != 0 if input file unacceptable for some reason
	//	file must exist and may have other reqs.
    {
    int status=parse_filename(result,mode,root,NULL,NULL);
    if ((status < 0) || (mode != 'r'))
	return status;
    return (::access(result,F_OK)) ? FILE_NOT_FOUND : 0; // no validation test
    }

const int File::parse_filename(char * fullname,const int mode,
			const char * root,const char * ext,const char * path)
	//	return != 0 if file unacceptable for some reason
	//	construct full path + file name in fullname
	//	'fullname' is a FMSIZE-byte pre-alloc'd buffer.
	//	return 0, or error number if file not found or invalid
    {
    int status;
    unsigned int patflags 
      = (ext == NULL) ? EXT_DEFAULT : (EXT_REQ|EXT_DEFAULT);
    memset(fullname,0,FMSIZE);
    strncpy(fullname,root,FMSIZE);
    /* 
     * the strlen(fullname) doesn't really do the trick, but it should be safe
     * (what is needed is sizeof, or an additioal arg to parse_filename)
     */
    if (mode == 'r')
	status=filename(fullname,strlen(fullname)+1,
			ext,path,patflags,(char *)NULL,VERIFY);
    else
	status=filename(fullname,strlen(fullname)+1,
			ext,path,patflags,(char *)NULL,0);
    //printf("ob.cpp::parse_filename for %s, mode %c; result=%d\n",
    // root,mode,status);
    if (status == FILENOTFOUND)		// in filename.h
	return FILE_NOT_FOUND;		// in ob.h
    return (status<0) ? FILE_BAD_NAME : 0;
    }

//
// 	following fns create & return strings
//
const char * File::errorstr() const
    {
    static char * FileErrMsg[] = { FILE_ERR_MSG } ;	// in OB.H
    return FileErrMsg[-(errn-DTKE_OB_BASE)];
    }

const char * File::classname() const 
    {
    return isA()->name();
    }

const char * File::datestr() const 
    {
    struct stat sbuf;
    struct tm * datex;
    static char date[DATE_STR_SZ];
    if (stat(czFileName,&sbuf)==0)
	{
	datex = localtime(&sbuf.st_atime);
	strcpy(date,"1900/00/00");
	itoa(1900+datex->tm_year,date,10);	// 4-digit year
	itoa(1+datex->tm_mon,((datex->tm_mon>8) ? (date+5) : (date+6)),10);
	itoa(datex->tm_mday,((datex->tm_mday>9) ? (date+8) : (date+9)),10);	// day
	date[4]=date[7]='/';	/* they got zapped by itoa */
	}
    else
	strcpy(date,"NOT FOUND");
    return date;
    }

const char * File::sizestr() const 
    {
    struct stat sbuf;
    static char size[SIZE_STR_SZ];
    if (stat(czFileName,&sbuf)==0)
	{
	ltoa(sbuf.st_size,size,10);
	strcat(size," bytes");
	}
    else
	size[0] = '\0';		// must be reinit at each execution
    return size;
    }

#define ERROR_INTRO_MSG "** "
#define ERROR_SEC_MSG " error ** "

const char * File::errormsg(char * buf,const int bufsiz)
    {
    char * tmp=(char *)classname();
    int bufleft=bufsiz-1;
    if (bufsiz==0)
	return "Double Error";
    memset(buf,0,bufsiz);
    if ((bufleft -= strlen(ERROR_INTRO_MSG)) < 0)
	return buf; 
    strcpy(buf,ERROR_INTRO_MSG);
    if ((bufleft -= strlen(tmp)) < 0)
	return buf; 
    strcat(buf,tmp);
    if ((bufleft -= strlen(ERROR_SEC_MSG)) < 0)
	return buf; 
    strcat(buf,ERROR_SEC_MSG);
    if ((bufleft -= strlen(czFileName)) < 0)
	return buf; 
    strcat(buf,czFileName);
    tmp = (char *) errorstr();
    if ((bufleft -= strlen(tmp)) < 0)
	return buf; 
    strcat(buf,tmp);
    return buf;
    }

const char ** File::about(const int detail)
	//	return descriptive string array: elt 0 always 80 chars
	//	detail == 0 => name only	1 => full path
	//		  2 => path, date,size	
	//		  3 up handled by derived classes
	//		  3 & 4: one line of info
	//		  5 => up to three lines of info
	//		  6 => up to 128 lines of info
    {
    char tmp[FMSIZE+50];
    char * pczNameDup = strdup(czFileName);
    memset(tmp,0,sizeof(tmp));
    isA()->obdesc_zap();	// clear array ptrs
    if (pczNameDup != NULL)
        {
	  //	char ext[5],node[20],drv[4];
	char * pNode = NULL, * pExt = NULL;
	//	strsfn_grs(pczNameDup,NULL,tmp,node,ext);
	if (strsfn6_grs(pczNameDup,NULL,NULL,&pNode,&pExt,NULL) == 0)
	    {
	    switch(detail)
	      {
	      case 0:	strcpy_array(tmp,pNode);
	                break;
	      case 1:	strcpy(tmp,czFileName); 
		        break;
	      default:  sprintf(tmp,"%s%s \t%s %s\t%s",
				pNode,(pExt != NULL) ? pExt : "",
				classname(),sizestr(),datestr());
	      break;
	      }
	    }
	free(pczNameDup);
	}
    isA()->obdesc_put(tmp);
    return isA()->obdesc();
    }

void File::operator=(File& src)
	//	copy one file to another
    {
    byte * locbuf = (bufsize) ? buffer : new byte [1024];
    int lbsize = (bufsize) ? bufsize : 1024;
    int rb=0,tmp=0;
    long off=0;		// force src reset
    if (locbuf == NULL)
	{
	errn=FILE_NOMEM;
	return;
	}
    if (mode == 'r')
	{
	errn=FILE_READONLY;
	return;
	}
memtest(99);
    int thistime;
    hdr->hdr_written_flag=1;	// 1 => pretend hdr has been written to file
    while ( ((rb=src.read(locbuf,lbsize,off)) > 0) && (src.error()==0) )
	{
	off = -1;	// now just keep reading
	while (rb)
	    {
	    if (bufsize)
		{
		thistime=min(bufsize,rb);
		fbuf_hwm = bufloc+(long)thistime;
		tmp = flush();
		}
	    else
		tmp=write(locbuf,rb);
//printf(">operator= : rb=%d tmp=%d (bufsize=%d bufloc=%ld hwm=%ld foffset=%ld)\n",
//	rb,tmp,bufsize,bufloc,fbuf_hwm,foffset);
	    if (tmp <= 0)
		return;	// how handle error?
	    rb -= tmp;
	    }
	}
memtest(98);
    if (bufsize==0)	// else we were using file's own buffer
#if defined MSC || defined __WATCOMC__
	delete locbuf;
#else
	delete [lbsize] locbuf;
#endif
    }

//void File::operator=(char * src)
//	//	copy one file to another
//    {
//    operator=((File&) src);
//    }

#ifdef NOMORE
static char * File::find(char * buf,const char * name,
			const char * path,const char * ext)
	//	find name of matching file or NULL
	//	if 'path' == NULL, assume 'name' includes a path
	//	if 'ext' != NULL, it must be used & must match supplied if any
	//	if 'name' == NULL, find next one
    {
    char tmp[FMSIZE];
    int status=0;
//    struct FIND * findptr=NULL;
    if (name != NULL)
	{
	strcpy(tmp,name);
//printf("find: name=%s, path=%s ext=%s\n",tmp,path,ext);
	status = filename(tmp,(char *)ext,(char *)path,EXT_SUB,NULL,FINDFIRST);
printf("find: name=%s; status=%X\n",tmp,status);
	if (status < 0)
	    return NULL;
//	findptr = findfirst(tmp,0);
	}
    else
	status = filename(tmp,NULL,NULL,0,NULL,FINDNEXT);
//	findptr = findnext();
//printf("       findptr=%p; name=%s\n",findptr,(findptr==NULL) ? "not found" : findptr->name);
//    if (findptr == NULL)	/* fixup the real name */
//	return NULL;
//    strcpy(buf,findptr->name);
    strcpy(buf,tmp);
    return buf;
    }
#endif //ifdef NOMORE

Class * File::isA() const
	{ return &class_File; }
const Class * File::desc() 
	{ return &class_File; }

void File::printOn()
    { 
    if (error())
	{ char tmp[10]; fputs("error ",stdout); puts(itoa(error(),tmp,10)); }
    else
	puts(about(2)[0]);
    }

void File::dumpOn(int detail)
    { 
    if (error())
	{
	char tmp[10];
	fputs(className(),stdout);
	fputs(" error status=",stdout); puts(itoa(error(),tmp,10));
	}
    else
	{
	const char ** descrptr = about(detail);
	int counter = 0;
	if (descrptr == NULL)	// no descriptions at all?
	    return;
	puts(descrptr[0]);
	while (descrptr[++counter] != NULL)
	    { fputs("   ",stdout); puts(descrptr[counter]);  }
	}
    }

/*
void filedate(char * buf,unsigned date)
	//	convert file date to ascii string - DOS format
	//	'date' is format returned by e.g. dos_getftime & stats
	//	'buf' (at least 12 chars) is filled by string
	//	same routine with slightly diff. args is used in rpanel
    {
    int d1=1980+(date>>9), d2=(date>>5)&0xF, d3=date&0x1F;
    strcpy(buf,"1900/00/00");
    itoa(d1,buf,10);	// 4-digit year
    itoa(d2,((d2>9) ? (buf+5) : (buf+6)),10);	// month
    itoa(d3,((d3>9) ? (buf+8) : (buf+9)),10);	// day
    buf[4]=buf[7]='/';	// they got zapped by itoa
    }
*/

#ifdef TESTX

DragonImgFileHeader::DragonImgFileHeader(const DragonImgFile * ffile) 
//	: FileHeader(ffile)
    {
/*
memtest(9);
    file = (DragonImgFile *) ffile;
memtest(2);
    header = new IHEAD; 
//printf("File Header at: %p\n",header);
    if (header != NULL)
//	file->errn = FILE_NOMEM;
//    else
	{
	hdrsize = sizeof(IHEAD); 
	hdroffset = 0;	// where the header gets placed in the file
//	inithdr(ffile);	// read or clear header
	}
memtest(3);
*/
    }
#endif

#ifdef TEST
char fredbuf[256];

void main()
    {
    char errbuf[80];
    memtest(0);
    printf("testing joe = %d\n",File::fileOK("sam.tst"));
    printf("testing jim = %d\n",File::fileOK("jim"));
    memtest(1);
    File * qfred = new File('r');
    if (qfred)
	{
	printf("qfred access = %d\n",qfred->access("sam.tst",4096));
     	memtest(91);
	delete qfred;
     	memtest(92);
	}
    File fred('r');
    if (fred.access("indo1.img") >= 0)
	{
	fred.dumpOn(2);
	fred.printOn();
	fred.read(fredbuf,256,0);
	printf("fred=\n%s\n",fredbuf);
	}
    else
	printf("fred status: %s\n",fred.errormsg(errbuf,80));

    File ffred('b');
    memtest(2);
    if (ffred.access("sam.tst",2048) >= 0)
	{
	ffred.dumpOn(2);
	ffred=fred;
	}
    else
	printf("ffred status: %s\n",ffred.errormsg(errbuf,80));
    memtest(3);
/*
    File sfred('w');
    sfred.access("sam.tss",2048);
    if (fred.access("indo1.img",2048) >= 0)
	{
	sfred.dumpOn();
	sfred=fred;
	}
    else
	printf("sfred status: %s\n",sfred.errormsg(errbuf,80));
    memtest(4);
*/
    }
#endif
