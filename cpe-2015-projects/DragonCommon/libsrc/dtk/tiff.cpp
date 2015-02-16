#include "drelease.h"
 ID_ TIFF_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.7 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/****************************************************************************
 *
 * 	file TIFF.CPP
 *	
 *      $Revision: 1.7 $ $Date: 2014/12/17 07:20:39 $
 *	definition of TAG class for TIFF
 *	created 1/30/91 for Zortech C++ rev 2.1
 *	TIFF revision 5.0, TIFF X classes
 *
 *	~~ Copyright kurt t. rudahl 1988-2014
 *
 *******************************************************************
 * $Id: tiff.cpp,v 1.7 2014/12/17 07:20:39 rudahl Exp $
 * $Log: tiff.cpp,v $
 * Revision 1.7  2014/12/17 07:20:39  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.6  2004/12/23 12:12:51  rudahl
 * replace itoa base sprintf in 32-bit, add unistd.g
 *
 * Revision 1.5  2004/11/30 09:45:11  rudahl
 * adapt for mingw
 *
 * Revision 1.4  2002/06/10 12:33:53  rudahl
 * updated TIFF-related fns to MSC4.1
 *
 * Revision 1.3  2002/04/09 21:34:51  rudahl
 * adapt for long filenames, & fixed bugs
 *
 * Revision 1.2  1999/07/03 16:50:24  rudahl
 * Fixed args for SWAPIT
 *
 * Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 * first checkin of only SOME common dirs
 *
 * Revision 4.0.1.1  1994/03/06  14:22:08  tower
 *  no significant changes
 *
 * Revision 4.0  1994/01/04  19:33:12  tower
 *  distrib. concurrent with DRAGON rel 4.0 - minor change
 * Revision 3.4  92/06/02  19:04:01  tower
 *  Changes to TIFF library for Zortech 3.0, for released DRAGSCAN & TIF2DRAG
 *  and for first released use of imagfile
 * Revision 3.3  92/04/28  18:09:43  tower
 * for 3.05. structural changes, gettypical, TIFF 5.0
 * Revision 3.2  91/05/04  19:31:43  tower
 * added clear_std_tags(), some bullittproofing, some annotation
 * Revision 3.1  91/04/09  21:58:02  tower
 *   augmented dTag::print; added dTag::ttoa; other improvements
 * Revision 3.0  91/02/21  20:06:33  tower
 *
 *******************************************************************
 *	9/15/91 ktr	fixed delete's to delete []
 *	12/3/91 ktr	changed entries for x&y position, resolution 
 *			unit made read_std_tags, clear_std_tags static
 *			member fns
 *			added get_typical()
 * 	12/20/91 ktr 	added special conditions required for TIFF classes
 * 3.3    5/26/92 ktr	updated to Zortech 3.0
 * 3.4    7/13/92 ktr	corrected: printiff CAN handle palette files
 *			  & FCONVERT has now been made capable
 * 5.0	6/22/97 ktr	some changes for Watcom just to get it to compile.
 *			Probably correct but untested.
 *	6/27/99 ktr	revised swapit() to always have unsigned first arg.
 *			created TIFF_BUF_T type
 * 5.4	11/30/2004 ktr	changed delete calls for MINGCC
 *	12/22/2004 ktr	added unistd for linux
 *
 * Memory usage
 *    linking this module automatically includes a set of "standard"
 *	tags (listed near the bottom of this file). Each standard tag
 *	contains a pointer value which points to a TAGINFO structure
 *	(16 bytes in small model), so minimum memory usage is about
 *	18 * number-of-std-tags (about 45), or about 1K.
 *    If 'read_std_tags()' is called, the file header is read into an
 *	allocated chunk of memory, which is used to initailize the
 *	standard tags and then freed by 'read_std_tags()'. Each of the 
 *	standard tags which was present in the data file now has its 
 *	TAGINFO initialized. The function is() tells whether a tag has
 *	been initialized (was present in the file).
 */

#if defined __GCC__
#include <unistd.h>
#else
#include <dos.h>
#include <io.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h> /* for offsetof */

#include "dtypes.h"
#include "dlimits.h"

extern "C" {
#include "files.h"
	   }
#include "tiff.hpp"

struct THDR tiff_hdr;	// globally available; esp for ID[0]

UINT16 dTag::resultspecs = 0;	//  - results of read_std_tags

dTag::dTag(TAGINFO * taginf)
    {
    init (taginf);
    }

int dTag::init(TAGINFO * taginf)
	//	set tag number and type appropriately
	//	return -1 if error else >= 0
    {
    taginfo = taginf;
    return 0;
    }

ulong dTag::get()
	//	return long value
	//	if rational or ascii type, will return DISKADDR
    {
    ulong retval;
    if (taginfo->tag.length > 1)
	return ((ulong) taginfo->tag.value.ptr);
    switch (taginfo->tag.type)
	{
	case TT_BYTE:	retval = (ulong) taginfo->tag.value.b; break;
	case TT_SHORT: 	retval = (ulong) taginfo->tag.value.s; break;
	case TT_LONG: 	retval = (ulong) taginfo->tag.value.l; break;
	default:	retval = (ulong) taginfo->tag.value.ptr; break;
	}
    return retval;
    }

typedef	union { SINT32 * lbuf; SINT16 * sbuf; char * cbuf; } TIFF_BUF_T; 

ulong dTag::gettypical(char * fname)
	//	return typical value. 
	//	File name must be spec'd in case a file read is needed.
	//	This will be the same as get() unless there are several
	//	scalar values in which case the 0-th item will be returned
	//	if rational or ascii type, will return DISKADDR
    {
    TIFF_BUF_T buf;
    ulong rval=0;
    if ((diskitemcount() > 0) && (gettype() != TT_RATIONAL)
		 && (gettype() != TT_ASCII))
	{
	if (gettype() == TT_SHORT)
	    buf.sbuf = (SINT16 *) diskitemread(fname);
	else
	    buf.lbuf = (SINT32 *) diskitemread(fname);
	if (buf.lbuf != NULL)
	    {
	    if (gettype() == TT_SHORT)
		rval = (ulong)buf.sbuf[0];
	    else
		rval = buf.lbuf[0];
	    }
	delete buf.lbuf;
	}
    else
	rval = get();	
    return rval;
    }

ulong dTag::getlen()
    {
    return taginfo->tag.length;
    }

TAGTYPE dTag::gettype()
	//	return type. If not initialized, return NONE.
    {
    if (taginfo == NULL)
	return TT_NONE;
    return (TAGTYPE)taginfo->tag.type;
    }

#ifdef NONO

int dTag::set (byte val)
	//	set value length and type appropriately
	//	return -1 if error else >= 0
    {
    type = BYTE;
    length = sizeof(byte);
    value.b=val;
    return 0;
    }

int dTag::set (short val)
	//	set value length and type appropriately
	//	return -1 if error else >= 0
    {
    type = SHORT;
    length = sizeof(short);
    value.s=val;
    return 0;
    }

int dTag::set (long val)
	//	set value length and type appropriately
	//	return -1 if error else >= 0
    {
    type = LONG;
    length = sizeof(long);
    value.l=val;
    return 0;
    }

int dTag::set (ulong val)
	//	set value length and type appropriately
	//	return -1 if error else >= 0
    {
    type = LONG;
    length = sizeof(long);
    value.u=val;
    return 0;
    }

int dTag::set (DISKADDR val,TAGTYPE ttype)
	//	set value length and type appropriately
	//	return -1 if error else >= 0
    {
    switch(ttype)
    	{
	case TT_BYTE:
	case TT_SHORT:
	case TT_LONG:	return -1; break;
	case TT_RATIONAL:
		length = 2 * sizeof(long); break;
	case TT_ASCII:
		length = strlen("SAM"); break;
	}
    type = ttype;
    value.ptr=val;
    return 0;
    }
#endif

int dTag::is()
	//	return 0 if not initialized else 1
    {
    return (gettype() != TT_NONE);
    }

struct TAG * dTag::getstruct()
	//	get pointer to struct TAG
    {
    return &taginfo->tag;
    }

int dTag::diskitemcount()
	//	return -1 if not init;
	//		0 if scalar
	//		strlen if ASCII
	//		# elements if array
	//		2 if RATIONAL
    {
    TAGTYPE ttype = gettype();
    int retval = 0;
    switch(ttype)
	{
	case TT_NONE:		retval = -1; break;
	case TT_RATIONAL:	retval = 2; break;
 	case TT_ASCII:		retval = getlen()-1; break;
	default:		if (getlen() == 1)
				    retval = 0;
				else
				    retval = getlen();
				break;
	}
    return retval;
    }

int dTag::diskitemsize()
	//	get size of disk read req'd
	//	return -1 if not init;
	//		0 if scalar
	//		strlen+1 if ASCII
	//		# elements * sizeof elt if array or RATIONAL
    {
    if (diskitemcount() < 1)	// should never equal 1
	return diskitemcount();
    int size;
    switch(gettype())
	{
	case TT_RATIONAL:	size = sizeof(rational); break;
 	case TT_ASCII:
	case TT_BYTE:	size = sizeof(byte); break;
	case TT_SHORT:	size = sizeof(short); break;
	case TT_LONG:	size = sizeof(long); break;
	default:	break;
	}
    return getlen() * size;
    }

void * dTag::diskitemread(char * fname)
	//	read into new buffer, or NULL is error.
	//	Calling pgm must delete()
    {
    int size = diskitemsize();
    int count = getlen();
    if (gettype() == TT_RATIONAL)
	count *= 2;
    TIFF_BUF_T buf;
//    union { char * cbuf; short * sbuf; unsigned long * lbuf; } buf;
    if (size < 1)
	return NULL;
    buf.cbuf = new char[size];
    if (buf.cbuf == NULL)
	return NULL;
    if (rsf(fname,NEAR2FAR(buf.cbuf),size,get(),0) < size)
	{
#ifdef __WATCOMC__
	delete buf.cbuf;
#else
	delete [] buf.cbuf;
	//	delete [size] buf.cbuf;
#endif
	return NULL;
	}
    while(--count >= 0)
        {
	if (gettype() == TT_SHORT)
	    swapit((UINT16 *) &buf.sbuf[count],tiff_hdr.ID[0]);
	else	// long or rational
	    swapit((UINT32 *) &buf.lbuf[count],tiff_hdr.ID[0]);
	}
    return ((void *)buf.cbuf);
    }

int dTag::operator==(const dTag &a)
	// 	equality compares the tag number
    {
    if (taginfo->tag.tag != a.taginfo->tag.tag)
	return 0;
    return 1;
    }

int dTag::operator==(const TAG &a)
	// 	equality compares the tag number
    {
    if (taginfo->tag.tag != a.tag)
	return 0;
    return 1;
    }

int dTag::operator==(const UINT32 u)
	// 	equality compares the value
	//	returns FALSE if type == NONE (uninitialized)
    {
    if (taginfo->tag.type == TT_NONE)
	return 0;
    return (taginfo->tag.value.u == u);
    }

int dTag::operator==(const UINT16 s)
	// 	equality compares the value
	//	returns FALSE if type == NONE (uninitialized)
    {
    if (taginfo->tag.type == TT_NONE)
	return 0;
    return (taginfo->tag.value.s == s);
    }

char * dTag::ttoa(char * filename,char * buf,size_t len)
	//	convert value to string in format depending on tag.type
	//	if tag.type is string > 'len', truncate
    {
    char tmp[40];
    memset(buf,0,len);
    switch(taginfo->tag.type)
	{
	case TT_NONE:	tmp[0]='\0'; break;
	case TT_BYTE:
	case TT_SHORT:
	case TT_LONG:	
#if defined __ZTC__
	  		ltoa((long)taginfo->tag.value.u,tmp,10);
#else
			sprintf(tmp,"%ld",(long)(taginfo->tag.value.u));
#endif
			break;
	case TT_ASCII:
			{
			char * fbuf = (char *) diskitemread(filename);
			if (fbuf == NULL)
			    strcpy(tmp,"Error reading file");
			else
			    {
			    strncpy(buf,fbuf,len-1);
#if defined __WATCOMC__ || defined __MINGCC__ || defined __GCC__
			    delete fbuf;
#else
			    delete [diskitemsize()] fbuf;
#endif
			    }
			}
			break;
	case TT_RATIONAL:
			{
			ulong * gbuf = (ulong *) diskitemread(filename);
			if (gbuf == NULL)
			    strcpy(tmp,"Error reading file");
			else
			    {
#if defined __ZTC__
			    ltoa(*gbuf++,tmp,10);
			    if (*gbuf != 1)
				{
			    	strcat(tmp,"/");
			    	ltoa(*gbuf,&tmp[strlen(tmp)],10);
				}
#else
			    sprintf(tmp,"%d",*gbuf++);
			    if (*gbuf != 1)
			    	sprintf(&tmp[strlen(tmp)],"/%d",*gbuf);
#endif
#if defined __WATCOMC__ || defined __MINGCC__ || __GCC__
			    delete --gbuf;
#else
			    delete [diskitemsize()] --gbuf;
#endif
			    }
			}
			break;
	}
    if (strlen(buf))
	return buf;
    if (strlen(tmp) > len-1)
	strncpy(buf,tmp,len-1);
    else
	strcpy(buf,tmp);
    return buf;
    }

char * dTag::print(char * filename,char * buf)
	//	if 'buf' non-NULL, assume it's at least 160 bytes long
	//	  stuff msg into it (no final \n) & return ptr to it
	//	else just print it & return NULL.
    {
    char tmp[40],tmp1[200];
    sprintf(tmp1,"Tag %3d: %s=%s %s%s",
	(int)(taginfo->tag.tag),taginfo->printname,
	((diskitemcount()>0) && (gettype() != TT_RATIONAL)
		&& (gettype() != TT_ASCII))
	    ? " " : ttoa(filename,tmp,sizeof(tmp)),
        (strlen(taginfo->printinfo)>47) ? "\n \t" : "\t",
        taginfo->printinfo) ;
    if (buf != NULL)
	{
	memset(buf,0,160);
	strncpy(buf,tmp1,159);
	}
    else
	printf("%s\n",tmp1);
    return buf;
    }

dTag& dTag::operator=(byte val)
	//	set the value
    {
    taginfo->tag.value.b = val;
    taginfo->tag.type = TT_BYTE;
    taginfo->tag.length = 1;
    return *this;
    }

dTag& dTag::operator=(short val)
	//	set the value
    {
    taginfo->tag.value.s = val;
    taginfo->tag.type = TT_SHORT;
    taginfo->tag.length = 1;
    return *this;
    }

dTag& dTag::operator=(long val)
	//	set the value
    {
    taginfo->tag.value.l = val;
    taginfo->tag.type = TT_LONG;
    taginfo->tag.length = 1;
    return *this;
    }
/*
UINT32 dTag::operator=()
	//	get the value
    {
    return     taginfo->tag.value.u;
    }
*/
void swapit(UINT32 * val,char creat)
	/* this function will swap the bytes of a long */
    {
    byte temp, * ptr= (byte *) val;
    if (creat == 'I')
	return;
    temp = *(ptr+3);
    *(ptr+3) = *ptr;
    *ptr = temp;
    temp = *(ptr+2);
    *(ptr+2) = *(ptr+1);
    *(ptr+1) = temp;
    }

void swapit(UINT16 * val,char creat)
	/* this function will swap the bytes of a short */
    {
    byte temp, * ptr= (byte *) val;
    if (creat == 'I')
	return;
    temp = *ptr;
    *ptr = *(ptr+1);
    *(ptr+1) = temp;
    }

int read_tif_hdr(char * fname,long offset,THDR * hdr)
	//	read a header from 'offset' within a file
	//	initialize 'hdr' structure esp. 'creator' & 'ifd'
	//	then read two bytes of Directory
	//	return -1 or number of tags
    {
    UINT16 tagcnt;
    if (fname == NULL)
	return -1;
    if (access(fname,F_OK) != 0)
	return -2;
    if (rsf(fname,NEAR2FAR(hdr),8,offset,0) < 8)
	return -3;
    swapit((UINT32 *)&hdr->ifd,hdr->ID[0]);
    if (rsf(fname,NEAR2FAR(&tagcnt),2,hdr->ifd,0) < 2)
	return -4;
    swapit(&tagcnt,hdr->ID[0]);
    return tagcnt;
    }

struct TAG * read_tags(char * fname,int * error,char ** errmsg)
	//	read set of tags from a file. Tags are in numerical order
	//	with no additional processing
	//	Return NULL if error and set 'error' < 0:
	//		-1 => no file name specified
	//		-2 => file not found
	//		-3 => error reading IFF header
	//		-4 => error reading IFD header
	//		-5 => not enough memory
	//		-6 => error reading tags
	//		-7 => error reading next IFD
    {
    int count,i;
    dTag tag;
    UINT32 nextdir = 0L;
    static struct TAG * tags;
    if ((count = read_tif_hdr(fname,nextdir,&tiff_hdr)) < 1)	// read header
	{
	*error = count;
	*errmsg = "Error reading header";
	return NULL;
	}
    if ((tags=new struct TAG[count]) == NULL)
	{
	*errmsg = "Error allocating tags";
	*error = -5;
        return NULL;
	}
    int size = sizeof (struct TAG)*count;
printf(">TIFF: read_tags. count=%d ifd=%ld size to read=%d\n",
	count,tiff_hdr.ifd,size);
    if (rsf(fname,NEAR2FAR(tags),size,tiff_hdr.ifd+2,0) < size)
	{
	*errmsg = "Error reading tags";
	*error = -6;
        return NULL;
	}
    for (i=0 ; i<count; i++)
	{
	swapit((ushort *)&tags[i].tag,tiff_hdr.ID[0]);
	swapit((ushort *)&tags[i].type,tiff_hdr.ID[0]);
	swapit(&tags[i].length,tiff_hdr.ID[0]);
	if(tags[i].type == TT_BYTE && tags[i].length == 1)
	    continue;
	if(tags[i].type == TT_SHORT && tags[i].length == 1)
	    swapit((UINT16 *)&tags[i].value.s,tiff_hdr.ID[0]);
	else 
	    swapit(&tags[i].value.u,tiff_hdr.ID[0]);	// either long or multi
	}
    if (rsf(fname,NEAR2FAR(&nextdir),4,tiff_hdr.ifd+(long)size+2,0) < 4)
	{
	*error = -7;
	*errmsg = "Error reading next IFD";
        return NULL;
	}
    swapit((UINT32 *)&nextdir,tiff_hdr.ID[0]);	// not actually using 'nextdir' now 
    *error = count;
    return tags;
    }

TAGINFO stdtags[] =
    {
    { NewSubfileType,TT_NONE,1,0 ,NULL,NULL },	/* 0xFE: 1 LONG */
    { SubfileType,TT_NONE,1,0 ,NULL,NULL },	/* 0xFF: 1 SHORT */
    { ImageWidth,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x100: 1 SHORT or LONG */
    { ImageLength,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x101: 1 SHORT or LONG */
    { BitsPerSample,TT_NONE,0,0 ,NULL,NULL },   /* 0x102: count=SamplesPerPixel, SHORT */
    { Compression,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x103: 1 SHORT */
    { PhotometricInterpretation,TT_NONE,1,0 ,NULL,NULL }, /* 0x106: 1 SHORT */
    { Threshholding,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x107: 1 SHORT */
    { CellWidth,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x108: 1 SHORT */
    { CellLength,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x109: 1 SHORT */
    { FillOrder,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x10A: 1 SHORT */
    { DocumentName,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x10D: ASCII */
    { ImageDescription,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x10E: ASCII */
    { Make,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x10F: ASCII */
    { Model,TT_NONE,1,0 ,NULL,NULL },		/* 0x110: ASCII */
    { StripOffsets,TT_NONE,1,0 ,NULL,NULL },   /* 0x111: count-see docs. SHORT or LONG */
    { Orientation,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x112: 1 SHORT */ 
    { SamplesPerPixel,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x115: 1 SHORT */
    { RowsPerStrip,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x116: 1 SHORT or LONG */
    { StripByteCounts,TT_NONE,1,0 ,NULL,NULL }, /* 0x117: count-see docs. SHORT or LONG */
    { MinSampleValue,TT_NONE,1,0 ,NULL,NULL },  /* 0x118: SamplesPerPixel SHORT */
    { MaxSampleValue,TT_NONE,1,0 ,NULL,NULL },  /* 0x119: SamplesPerPixel SHORT */
    { XResolution,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x11A: 1 RAT */
    { YResolution,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x11B: 1 RAT */
    { PlanarConfiguration,TT_NONE,1,0 ,NULL,NULL }, /* 0x11C: 1 SHORT */
    { PageName,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x11D: ASCII */
    { XPosition,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x11E: 1 RAT */
    { YPosition,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x11F: 1 RAT */
    { FreeOffsets,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x120: ? LONG */
    { FreeByteCounts,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x121: ? LONG */
    { GrayResponseUnit,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x122: 1 SHORT */
    { GrayResponseCurve,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x123: 2**BitsPerSample SHORT */
    { Group3Options,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x124: 1 LONG */
    { Group4Options,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x125: 1 LONG */
    { ResolutionUnit,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x128: 1 SHORT */
    { PageNumber,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x129: 2 SHORT */ 
    { ColorResponseCurves,TT_NONE,1,0 ,NULL,NULL }, /* 0x12D: 3*(2**BitsPerSample SHORT */
    { Software,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x131: ASCII */
    { DateTime,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x132: ASCII */
    { Artist,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x13B: ASCII */
    { HostComputer,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x13C: ASCII */
    { Predictor,TT_NONE,1,0 ,NULL,NULL }, 		/* 0x13D: 1 SHORT */
    { WhitePoint,TT_NONE,1,0 ,NULL,NULL }, 	/* 0x13E: 2 RAT */
    { PrimaryChromaticities,TT_NONE,1,0 ,NULL,NULL }, /* 0x13F: 6 RAT */
    { ColorMap,TT_NONE,1,0 ,NULL,NULL } 	/* 0x140: 3*(2**BitsPerSample) SHORT*/
    } ;

UINT16 tagspecs[] = { TAGSSPEC } ;
//UINT16 resultspecs = 0xFFFF;

int dTag::read_std_tags(char * fname,char ** errmsg) 
	//	read set of tags from a file, and copy into 'stdtags'.
	//	'fname' must be complete with path and extension
	//	Return < 0 if error (see 'read_tags' for codes),
	//	else count of tags found
    {
    UINT16 locspecs[ColorMap_I+1];
    int error,i,j,tagindex,bps;
    TAGINFO taginfo;
    dTag tag;
    *errmsg=" ";
    resultspecs=0x1D0F; // check BGPRX,DRAG
    for (j=0 ; j<=ColorMap_I ; j++)	/* ColorMap_I is last one */
	{
	locspecs[j]=tagspecs[j];	/* make copy of tagsspecs */
	stdtags[j].tag.type = TT_NONE;	/* reinit stdtags */
	stdtags[j].printname = NULL;
	stdtags[j].printinfo = NULL;
	}
		//	now copy them into 'stdtags' array
    struct TAG * tags = read_tags(fname,&error,errmsg);
		// 	for each supplied tag, check it
printf("read_std_tags sizeof struct TAG=%d offsetof value=%d\n",
       sizeof(struct TAG),offsetof(struct TAG,value));
    if (tags != NULL)
	{
	for (i=0 ; i<error ; i++)	// 'error' is count of tags
	    {
	    tagindex = -1;
	    memcpy(&taginfo.tag,&tags[i],sizeof (struct TAG));
	    if (taginfo.tag.type == TT_NONE)
		continue;		// invalid setting, so don't init
	    tag.init(&taginfo);
		// 	cycle through standard tags to find this one
		//	subfiletype & newsubfiletype are handled specially,
		//	since we need one or the other but not both
	    for (j=0 ; j<=ColorMap_I ; j++) // ColorMap_I is last one
	    	if (tag == stdtags[j].tag)
		    tagindex = j;	// remember it
//printf("Item=%d tagindex=%d results=%X\n",i,tagindex,resultspecs);
//	    swapit(&tags[i],ID[0]);	// do swapit's 
	    if (tagindex >= 0)		// don't do it if it's proprietary
		{
		memcpy(&stdtags[tagindex].tag,&tags[i],sizeof (struct TAG));
		locspecs[tagindex]=0; // => "meets all requirements"
		}
		    /* verify special cases for TIFF classes & DRAGON pgms */
	    if (tagindex == SamplesPerPixel_I)
		{
		int val = tags[i].value.s;
		if (val != 3)
		    resultspecs &= ~TIFF_R;
		if (val != 1)
		    resultspecs &= (~TIFF_G | ~TIFF_B | ~TIFF_P);
		}
	    if (tagindex == PhotometricInterpretation_I)
		{
		int val = tags[i].value.s;
		if (val != 3)
		    resultspecs &= ~TIFF_P;
		else	// IFILE can't yet handle Palette files
		    resultspecs &= ~(TIFF_IFILE);
		if (val != 2)
		    resultspecs &= ~TIFF_R;
		if ((val != 0) && (val != 1))
		    resultspecs &= ~(TIFF_G | TIFF_B);
		}
	    if (tagindex == Compression_I)
		{
		int val = tags[i].value.s;
		if (val != 1)
		    resultspecs &= ~(TIFF_PRINTIFF | TIFF_FCONVERT | TIFF_IFILE);
		if ((val != 1) && (val != 5))
		    resultspecs &= ~(TIFF_G | TIFF_P | TIFF_R);
		if ((val != 1) && (val != 2) && (val != 32773))
		    resultspecs &= ~TIFF_B;
		}
	    if (tagindex == BitsPerSample_I)
		{
		if (tag.diskitemcount() > 0)
		    {
		    union { long * lbuf; short * sbuf; } buf;
		    buf.sbuf = (short *) tag.diskitemread(fname);
		    bps=buf.sbuf[0];
		    delete buf.lbuf;
		    }
		else
		    bps=tag.get();
		if (bps != 8)
		    resultspecs &= ~(TIFF_FCONVERT | TIFF_R);
		if ((bps != 4) && (bps != 8))
		    resultspecs &= ~(TIFF_PRINTIFF | TIFF_FCONVERT | TIFF_G);
		if (bps != 1)
		    resultspecs &= ~TIFF_B;
		if ((bps != 1) && (bps != 4) && (bps != 8))
		    resultspecs &= ~TIFF_IFILE;
//printf("resultspecs=x%X; bps=%d\n",resultspecs,bps);
		}
	    }
		// following has effect of permitting [1] to be absent IFF
		// [0] is present && vice-versa.
	if (!subfileType.is() && newSubfileType.is())
	    locspecs[1] &= ~tagspecs[0];  // clear bits satisfied by [0]
	if (subfileType.is() && !newSubfileType.is())
	    locspecs[0] &= ~tagspecs[1];  // clear bits satisfied by [1]
	delete tags;
	}
//printf("resultspecs=x%X; locspecs=%X, %X\n",resultspecs,locspecs[0],locspecs[1]);
//    resultspecs &= (~locspecs[0]);	// specs for NewSubfileType & SubfileType
    for (j=0 ; j<=ColorMap_I ; j++) // ColorMap_I is last one
	resultspecs &= (~locspecs[j]);
//printf("resultspecs=x%X\n",resultspecs);
    return error; 
    }

void dTag::clear_std_tags() 
	//	clear (initialize) standard tags.
    {
    int j;
    for (j=0 ; j<=ColorMap_I ; j++) // ColorMap_I is last one
    	stdtags[j].tag.type = TT_NONE;
    }


dTag newSubfileType(&stdtags[NewSubfileType_I]);
dTag subfileType(&stdtags[SubfileType_I]);
dTag imageWidth(&stdtags[ImageWidth_I]);
dTag imageLength(&stdtags[ImageLength_I]);
dTag bitsPerSample(&stdtags[BitsPerSample_I]);
dTag compression(&stdtags[Compression_I]);
dTag photometricInterpretation(&stdtags[PhotometricInterpretation_I]);
//dTag threshholding(&stdtags[Threshholding_I]);
//dTag cellWidth(&stdtags[CellWidth_I]);
//dTag cellLength(&stdtags[CellLength_I]);
//dTag fillOrder(&stdtags[FillOrder_I]);
//dTag documentName(&stdtags[DocumentName_I]);
dTag imageDescription(&stdtags[ImageDescription_I]);
//dTag make(&stdtags[Make_I]);
//dTag model(&stdtags[Model_I]);
dTag stripOffsets(&stdtags[StripOffsets_I]);
//dTag orientation(&stdtags[Orientation_I]);
dTag samplesPerPixel(&stdtags[SamplesPerPixel_I]);
dTag rowsPerStrip(&stdtags[RowsPerStrip_I]);
dTag stripByteCounts(&stdtags[StripByteCounts_I]);
//dTag minSampleValue(&stdtags[MinSampleValue_I]);
//dTag maxSampleValue(&stdtags[MaxSampleValue_I]);
//dTag xResolution(&stdtags[XResolution_I]);
//dTag yResolution(&stdtags[YResolution_I]);
dTag planarConfiguration(&stdtags[PlanarConfiguration_I]);
//dTag pageName(&stdtags[PageName_I]);
dTag xPosition(&stdtags[XPosition_I]);
dTag yPosition(&stdtags[YPosition_I]);
//dTag freeOffsets(&stdtags[FreeOffsets_I]);
//dTag freeByteCounts(&stdtags[FreeByteCounts_I]);
dTag grayResponseUnit(&stdtags[GrayResponseUnit_I]);
dTag grayResponseCurve(&stdtags[GrayResponseCurve_I]);
//dTag group3Options(&stdtags[Group3Options_I]);
//dTag group4Options(&stdtags[Group4Options_I]);
dTag resolutionUnit(&stdtags[ResolutionUnit_I]);
//dTag pageNumber(&stdtags[PageNumber_I]);
dTag colorResponseCurves(&stdtags[ColorResponseCurves_I]);
dTag software(&stdtags[Software_I]);
dTag dateTime(&stdtags[DateTime_I]);
//dTag artist(&stdtags[Artist_I]);
//dTag hostComputer(&stdtags[HostComputer_I]);
//dTag predictor(&stdtags[Predictor_I]);
//dTag whitePoint(&stdtags[WhitePoint_I]);
//dTag primaryChromaticities(&stdtags[PrimaryChromaticities_I]);
dTag colorMap(&stdtags[ColorMap_I]);
