#include "drelease.h"
ID_ IFF_ID[] = 
   "\0@(#) " __FILE__ "      $Revision: 1.5 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/* 
 *	IFF.C - misc functions for use with DRAGON & WF
 *		IFF-structured files.
 *	Used mostly by chk.exe
 *
 *          $Revision: 1.5 $	$Date: 2014/12/05 14:24:30 $
 *
 *	~~ Copyright 1989-2014 Kurt Rudahl and Sally goldin
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
 *
 *	$Log: iff.c,v $
 *	Revision 1.5  2014/12/05 14:24:30  rudahl
 *	reconciled DragonProfessional with OpenDragon
 *
 *	Revision 1.4  2005/12/10 11:36:53  rudahl
 *	fixing some of the double-tilde comments
 *
 *	Revision 1.3  2005/03/23 14:24:42  goldin
 *	no change; some debug
 *	
 *	Revision 1.2  2005/03/19 11:07:26  rudahl
 *	commented out some maybe unused fns
 *	
 *	Revision 1.1  2005/03/19 06:31:51  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.4  2005/03/16 02:30:40  rudahl
 *	cleanup
 *	
 *	Revision 1.3  2004/12/25 04:19:09  rudahl
 *	adapt for linux
 *	
 *	Revision 1.2  2002/01/15 12:35:03  rudahl
 *	the old Microsoft bug of needing to mask-off extra bits
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *	first checkin of only SOME common dirs
 *	
 * Revision 4.4  1997/09/06  05:21:04  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1997/09/06  05:21:04  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/07/19  18:32:54  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/12/22  21:44:22  tower
 * final for DRAGON 4.0G - adapte
 * adapted for MSC v 6.
 * 
 * Revision 4.0  1993/02/11  10:59:04  tower
 * final for DRAGON Release 4.0
 * 
 * Revision 3.5  91/12/07  13:29:28  tower
 * rewrite_iff & seek_iff were lost betweeen 3.2 & 3.3. This version is
 * a merge of 3.2 and 3.4 to reintroduce those fns
 * 
 * Revision 3.4  91/11/25  21:33:15  tower
 * for 3.05: converted to NEAR2FAR
 * Revision 3.3  91/06/17  12:53:15  at
 * minor cosmetic, docunentation, & ANSI updates for DRAGON 3.05
 * full Lattice compliance dropped
 * Revision 3.2  91/02/16  22:42:13  tower
 * added seek_iff, rewrite_iff fns and corrected in-line
 * documentation. Works with Zortech 2.1
 * 
 *
 ****************************************************************
 *
 *  Written by Kurt Rudahl
 *  creates either of two object modules: if IFF_CHK not defined, 
 *	creates module with traditional IFF functions
 *  if IFF_CHK defined, creates module with iff_xxx_check()
 *  if TEST defined, creates stand-alone program with both sets
 *					
 *	included non-IFF_CHK functions are:
 *	   void num2rad64(num, *buf)
 *			convert number to rad64 string
 *			'buf' must have room for 5 bytes
 *	   long iffhdrcnt(*buf)
 * 			convert rad64 string to long
 *
 *     	the read functions recognize either format for size
 *	   long read_iff(file,*buf)
 *			read size, hdr name from file
 *			'buf' must have room for 5 bytes
 *			return <0L if error (disk or EOF), 0L for not an IFF file
 *	   int qread_iffhdr(name,long *	pos'n, long * blk)
 *			get int matching tagname for file 'name' at 'pos'n', 
 *			and set 'pos'n to loc'n of next IFF hdr
 *			set 'blk' to loc'n following IFF hdr
 *			returns 0 for not-IFF, <0 for err,
 *			see IFF.H for >0 return values  
 *
 *	the write functions create rad64 format headers
 *	   int write_iff(name,long size,*buf,mode)
 *			write (append) size, hdr name to file
 *			'mode' is as for 'wsf' 
 *			(=1 for create/append )
 * 	   int rewrite_iff(nasme,long size,*buf,long offset) 
 *	 		rewrite (overwrite) IFF header to file 'name',
 *			containing 'text' as an id and 'size' as the
 *			block size which will follow. 'offset' is same as
 *			for 'wsfo'. Return <0 if err.
 *	   SINT32 seek_iff(char * name,char * id,SINT32 offset)
 *			get file position if any where iff id is to be found
 *			starting at file position 'offset' .
 *			'id' is four-char string.
 *			Return file position immed. following IFF, 
 *			or <= 0L if error
 *	   char * iff_ermsgptr(int errnum, char * array[] )
 *			return NULL if errnum is not an IFF error number, 
 *			or ptr into the message table 'array' in iff.h
 *
 *	included non-IFF_CHK functions are:
 *
 *	The header structure, which is an augmented form of
 *	the IFF protocol, is:
 *		bytes[0:1] = 'WF'
 *		bytes[2:3] = tag_name for this chunk
 *		bytes[4:7] = chunk size EXCLUDING HEADER
 *			this info is stored 'little-endian'
 *			in one of two formats. The normal
 *			IFF standard form is just a binary long.
 *			Alternatively, each byte may use only the
 *			low-order 6-bits (24-bits total), with the
 *			higher bits set to some value which forces
 *			the byte to be a printing character.
 *			The reading software can determine which is
 *			the case by examining byte[7]: 
 *				> 0x3F => the second form.
 *
 *	The IFF_CHECK structure, which is an augmented header structure, is
 *		bytes 0:7 = IFF header "WFCK" in ASCII modulo-64 form
 *		bytes 8:11 = DISKADDR of start of checked part of file
 *				in ASCII rad-64 form
 *		bytes 12:15 = size of checked part of file
 *				in ASCII rad-64 form
 *		bytes 16:19 = 24-bit checksum of checked part of file
 *				in ASCII rad-64 form
 *		bytes 20:23 unused
 *
 *	These functions are compatible with both Lattice 3.2, 3.3, and QuickC
 *
 *	compile with DEBG for debugging version
 *		with TEST for test version (incl. debugging)
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *   12/14/89 	ktr	vetted for large-model problems
 *			   also added host.h typedefs
 *   1/12/90 ktr        mod. to use only rsf, wsf file ops. This implies
 *			   that old read_iffhdr, write_iffhdr have new arguments.
 *   12/3/90 ktr	mod to work with Lattice	
 *   2/16/91 ktr	added rewrite_iff(), seek_iff()
 *   12/2/91 ktr	dropped Lattice conditionals; remerged v 3.2 & 3.4.	
 *   10/23/92 ktr	added iff_write_check() & iff_read_check()
 *			   to be compiled as separate module
 *			removed vfiles_qinstall calls, which are now embedded
 *			   in filecall (if filecall linked in)
 *	12/22/93 ktr	began adapting for MSC6
 *	6/27/94 ktr	added free() in IFF_CHK fn (not presently used anyway)
 *	7/19/94 ktr	minor fixes for MSC v 8
 *	1/22/95 ktr	minor fixes for MSC v 8
 *	12/10/95 ktr	adapted for Watcom 10.0
 * 5.4	12/25/2004 ktr	adapt for linux. 
 * 5.5	2005-3-15 ktr	imported from Dragon v 5.4.4
 */

//#ifndef IFF_CHK		/* only one or the other */
//#define IFF_NOCHK
//#endif
	  
#ifdef TEST
#define IFF_CHK		/* unless we're doing testing, which */
#define DEBG`		/* needs both */
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	/* memcpy */
#include <fcntl.h>	/* OPEN parameters	*/
#ifdef __GCC__
#include <sys/stat.h>
#else
#include <sys\stat.h>
//#include <dos.h>
//#include <io.h>
#endif
#ifdef _MSC_VER
//#include <sys\types.h>
//#include <malloc.h>
#endif

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
//#include "zfile.h"

#include "iff.h"
#include "files.h"
//#include "stats.h"
//#include "dragfile.h"

void num2rad64(long,byte *);	/* convert number to rad64 string */
long iffhdrcnt(byte *);		/* convert rad64 string to long */

//#ifdef IFF_NOCHK
void num2rad64(long size,byte * buf)
	/* convert number 'size' to rad64 string in 'buf'[0-4]
	 */
    {
    byte * sptr = buf;
    buf[4] = 0;	/* null terminator */
    memset(buf,'@',4);
    while(size)
	{
	long piece=size & 0x3F;
	*(sptr++) = (byte)((piece == 0x3F) ? 0x3F : (piece | 0x40));
	size >>= 6;
	}
    }

SINT32 iffhdrcnt(byte * buf)
	/* convert iffhdrcnt string in 'buf' to long 
	 */
    {	
    union { byte ch[6]; SINT32 val; } lb;
    memcpy((char *) &lb,buf,4);
    if (buf[3] < 0x40)
	{
    	lb.ch[4] = 0;
	return(atol((char *) &lb));
	}
    else
	{
	lb.val &= 0x3F3F3F3FL; /* mask high bits */
	return( (SINT32)(lb.ch[0]) + ((SINT32)(lb.ch[1]) << 6)
	    + ((SINT32)(lb.ch[2]) << 12) + ((SINT32)(lb.ch[3]) << 18) );
	}
    }

int write_iff(const char * name,const SINT32 size,
			 const byte * text,const UINT16 mode)
	/* 	write (append) IFF header to file 'name',
	 *	containing 'text' as an id and 'size' as the
	 *	block size which will follow. 'mode' is same as
	 *	for 'wsf' (=1 for create or append). Return <0 if err.
	 */
    {
    byte loc_buf[9];
    int tmp;
    memcpy(loc_buf,text,4);
    num2rad64(size,&loc_buf[4]);
    tmp = wsf(name,loc_buf,8,mode);	/* create or append */
    if (tmp < 8)
	return (IFF_WRITE_ERR);
    return(0);
    }

#ifdef NOTUSED // 2005-3-19
int rewrite_iff(const char * name,const SINT32 size,
			 const byte * text,const UINT32 offset)
	/* 	rewrite (overwrite) IFF header to file 'name',
	 *	containing 'text' as an id and 'size' as the
	 *	block size which will follow. 'offset' is same as
	 *	for 'wsfo'. Return <0 if err.
	 */
    {
    byte loc_buf[9];
    int tmp;
    memcpy(loc_buf,text,4);
    num2rad64(size,&loc_buf[4]);
    tmp = wsfo(name,loc_buf,8,offset);
    if (tmp < 8)
	return (IFF_WRITE_ERR);
    return(0);
    }
#endif // ifdef NOTUSED // 2005-3-19

long seek_iff(const char * name,const char * id,long offset)
	/*	get file position if any where iff id is to be found
	 *	starting a file position 'offset' .
	 *	'id' is four-char string.
	 *	Return file position immed. following IFF, 
	 *	or <= 0L if error
	 */
    {
    UINT32 cur_iff = offset;
    UINT32 bloc_loc;
    int tmp;
    if (strncmp(id,"WF",2))
	return -1L;
    while((tmp=qread_iffhdr(name,&cur_iff,&bloc_loc)) != (id[3] + (id[2]<<8)) )
	if (tmp <= 0)
	    return tmp;
    return (long) bloc_loc;
    }

#if defined MSC || defined __WATCOMC__
/* #include <sys\types.h>
 * #include <sys\stat.h> */
static long filesize(const char * name)
    {
    struct _stat stats;
    if (!_stat(name,&stats))
	return stats.st_size;
    return -1;
    }
#endif
    
int qread_iffhdr(const char * name,const UINT32 * posn,UINT32 * blk) 
	/* 	get int matching tagname
	 * 	for file 'name' at 'pos'n', and
	 * 	set 'posn' to loc'n of next IFF hdr
	 * 	set 'blk' to loc'n of data following IFF hdr
	 *	returns (UINT16) bytes 2 & 3, or 0 if not iff
	 * 	see IFF.H for error return values  
	 */ 				     
    {
    int j;
    long * loc_posn = (long *)posn;
    byte tag_buf[8];
    SINT32 length;
    if (*loc_posn == file_size((char *)name))
	return IFF_EOF;
    j = rsf(name,tag_buf,8,*(SINT32 *)loc_posn,0);
    if (j < 8)
	return IFF_READ_ERR;
    //printf("iff::qread_iffhdr read '%s', bytes = x%02X x%02X WF_NAME=x%X\n",
    //   tag_buf,tag_buf[0],tag_buf[1],WF_NAME);
    if (((SINT16)tag_buf[0] + ((SINT16)tag_buf[1]<<8)) != WF_NAME)
	return NOT_IFF_ERR;	/* no error, but not IFF file */
    length = iffhdrcnt(&tag_buf[4]);
    *blk = *loc_posn + (long) j;	/* locn of data block */ 
    *loc_posn += (length+(long)j);	/* loc'n of next iff hdr if any */
    return((0xFF & tag_buf[3]) + ((0xFF & tag_buf[2])<<8));
    }

const char * iff_ermsgptr(const int errnum,const char * array[])  
	/*	 return NULL if errnum is not an IFF
	 *	 error number, or pointer into
	 *	 the message table 'array' in iff.h
	 */
    {	   
    SINT16 msg=0;
    switch(errnum)
	{
	case IFF_OPEN_ERR: msg=1; break;
	case IFF_SEEK_ERR: msg=2; break;
	case IFF_EOF: 	   msg=3; break;
	case IFF_READ_ERR: msg=2; break;
	case IFF_WRITE_ERR: msg=4; break;
	}
    return((msg) ? array[msg] : NULL);
    }	
//#endif
//#ifdef IFF_CHK

static int iff_docheck(const char * filename,const ulong start,const ulong size,
			const int r_notw,IFF_CHK_BLK * block)
	/*	calc checksum of specified part of file
	 *	If r_notw, check against supplied block return 0 if err 1 if OK
	 *	else, copy to supplied block return 1
	 *	Return <0 if file i/o error
	 */
    {
    ulong bsize=0x4000,locstart=start;
    char * buf = NULL;
    size_t i;
    ulong checksum=0;
    int status;
    ulong sizeleft=size;
    IFF_CHK_BLK locblock;
    if (r_notw)
	{
	locstart=iffhdrcnt(block->startloc);
	sizeleft=iffhdrcnt(block->size);
	}
    while (buf == NULL)
	{
	buf=malloc(bsize);
	if (buf)
	    break;
	if (bsize < 0x400)
	    return IFF_NOMEM;
	bsize >>= 1;
	}
    while (sizeleft)
	{
	if (sizeleft < bsize)
	    bsize=sizeleft;
	if ((status=rsf(filename,buf,bsize,locstart,0)) < 0)
	    {
	    free(buf);
	    return status;
	    }
	locstart=-1;
	sizeleft -= bsize;
	for (i=0; i<bsize; i++)
	    checksum += buf[i];
	}
    free(buf);
    memset(&locblock,0,sizeof(locblock));
    num2rad64(start,locblock.startloc);
    num2rad64(size,locblock.size);
    num2rad64(checksum,locblock.checksum);
    if (r_notw)
	return (memcmp(&locblock,block,sizeof(locblock)) != 0);
    memcpy(block,&locblock,sizeof(locblock));
    return 1;
    }

int iff_check_file(const char * filename)
	/* NOT YET IMPLEMENTED */
	/*	check entire file is reasonable sequence of IFF segs covered by
	 *	IFF_CHECKs, and that checksums match
	 *	Return < 0 if error, or number of IFF segs excl IFF_CHECKS
	 */
    {
    int counter=0;
    return counter;
    }

int iff_read_check(const char * filename,ulong curroffset)
    {
/*    static uint id[]={WF_NAME,IFF_CHECK}; */
    ulong loco;	/* local offset*/
//    long start,size;
    int status;
    IFF_CHK_BLK block;
    int blkid=qread_iffhdr(filename,&curroffset,&loco);
    if (blkid != IFF_CHECK)
	return IFF_WRONGID;
    if ((status=rsf(filename,&block,sizeof(block),curroffset,0)) < 0)
	return status;
    return iff_docheck(filename,0,0,1,&block);
    }

#ifdef NOTUSED // 2005-3-19
int iff_rewrite_check(const char * filename,const ulong offset,
			const ulong start,const ulong size)
	/*	write at 'offset IFF_CHK segment covering 'size' bytes of file 
	 *	beginning with 'start'. If 'size'==0, do entire remainder of file
	 *	Return <0 => error
	 */
    {
    static uint id[]={WF_NAME,IFF_CHECK};
    IFF_CHK_BLK block;
    int status=rewrite_iff(filename,sizeof(IFF_CHK_BLK),(byte *)(id),offset);
    if (status<0)
	return status;
    if((status=iff_docheck(filename,start,size,0,&block)) < 0)
	return status;	/* file i/o or memory error */
    if (wsfo(filename,&block,sizeof(block),offset+8) < sizeof(block))
	return (IFF_WRITE_ERR);
    return 0;
    }
#endif // ifdef NOTUSED // 2005-3-19

int iff_write_check(const char * filename,const ulong start,const ulong size)
	/*	append IFF_CHK segment covering 'size' bytes of file 
	 *	beginning with 'start'. If 'size'==0, do entire remainder of file
	 *	Return <0 => error
	 */
    {
    static uint id[]={WF_NAME,IFF_CHECK};
    IFF_CHK_BLK block;
    int status;
    if (write_iff(filename,sizeof(IFF_CHK_BLK),(byte *)(id),WSF_APPEND) < 0)
	return (IFF_WRITE_ERR);
    if((status=iff_docheck(filename,start,size,0,&block)) < 0)
	return status;	/* file i/o or memory error */
    if (wsf(filename,&block,sizeof(block),WSF_APPEND) < sizeof(block))
	return (IFF_WRITE_ERR);
    return 0;
    }
//#endif

void IFF_O_END() { puts(FIL_ID); }

#ifdef TEST
#define NO_FONT_CLASS /* for non-C++ */
#include "vfile.h"
#include "font.h"
char cfgfile[13] = "DRAGON";
STATS stats ;
static FontNameTab * FontFind(char * pattern);

main(argc,argv)
int argc;
byte **argv;
    {
    byte * infile;
    SINT16 result;
    UINT32 curpos=0L;	/* file position */
    UINT32 blk;
    printf("testing IFF: file = %s\n",*++argv);
    if (argc > 1)
	{
	infile = *argv;
	while((result = qread_iffhdr(infile,&curpos,&blk)) > 0)
	    printf("IFF type=x%X=%c%c, data at %lX next IFF at %lX\n",
		result,(byte)(result&0xFF),(byte)(result>>8),blk,curpos);
    	printf("IFF status=%d, data at %lX, next IFF at %lX\n",
	    result,blk,curpos);
	}
    FontFind("*");
    while(FontFind(NULL))
	;
    }

void errstat_set(unsigned module,UINT32 flags,unsigned level,char * msg)
	/* dummy fn */
   {
   if (level)
	printf("Dummy errstat_set module=%d flags=%lx level=%d\n",
	    module,flags,level);
   }

	/* following is extracted & modified from FONT.CPP */
static int namematch(pattern,name)
		/*	return 1 if name matches pattern else 0
		 *	pattern matching is simple and DOS-like:
		 *		char 0 in font name is ignored
		 *		char 1 in font name is bit pattern where low
		 *		  3 bits enable a resolution (L,M,H) which must
		 *		  match current display resolution
		 *		then each char must equal corresp. pattern char 
		 *		unless a: pattern char = '?'
		 *		or     b: pattern char = '*' which stops match
		 *	DOS style matching.
		 */
char * pattern, *name;
    {
    char temp;
    char modepat = 0xFF;	/* testing - all resolutions */
/* printf("namematch: name=%s (%d chars), pattern=%s (%d chars), modepat=%d (mo de=x%X)\n",
	name,strlen(name),pattern,strlen(pattern),modepat,CurScreen(SCR_QMODE)); */ 
    if ((*++name & modepat) == 0)	/* not for this resolution */
	return 0;
    pattern -= 1;
    while (*++pattern)
	{
	if (*pattern == '*') return 1;
	temp = *++name;		/* avoid dependencies on expression eval seq. */
	if ((*pattern != '?') && (*pattern != temp))
	    return 0;
	}
    return (*++name == '\0') ? 1 : 0;	/* pattern done, so name must be also */
    }

static FontPrefix * FontCheckHdr(FontNameTab * foname,char * pattern)
	/*	check whether font described in 'foname'
	 *	(which has it's filename and position)
	 *	is available to be loaded (& verify it's validity
	 *	and that it matches 'pattern')
	 *	Return ptr to FontPrefix. If N.G., charcount=0.
	 */
    {
    int size = sizeof(FontPrefix);
    static FontPrefix fontpfx;
    if (rsf(foname->filnam,&fontpfx,size,foname->off,0) != size)
	fontpfx.charcount=0;
    if (strcmp(fontpfx.id,ID))	/* ID matches? */
	fontpfx.charcount=0;
	/* add validation operations here */
    if (namematch(pattern,fontpfx.fontname))
	strcpy(foname->fontname,fontpfx.fontname);	/* replace pattern */
    else
	fontpfx.charcount=0;
    return &fontpfx;
    }

static FontNameTab * FontFind(char * pattern)
	/*	find font with name matching 'pattern', setup info
	 *	into table, and return pointer to entry (or NULL).
	 *	pattern matching is simple and DOS-like:
	 *		char 0 in font name is ignored
	 *		char 1 in font name is bit pattern where low
	 *		  3 bits enable a resolution (L,M,H) which must
	 *		  match current display resolution
	 *		then each char must equal corresp. pattern char 
	 *		unless a: pattern char = '?'
	 *		or     b: pattern char = '*' which stops match
	 *	This fn is very idiosyncratic to op. sys. and
	 *	structure of font files. Used by XListFonts
	 *	and XLoadQueryFont (font::load)
	 */
    {
    static FontNameTab foname;
#ifdef __ZTC__
    static struct FIND * ffile;
#else
    static struct find_t * ffile;
#endif
    static char fname[FONTNSZ+1];
    int iffflg,next_file=0;
    FontPrefix * fntpfx;
    static unsigned long fileoffset=0L;
    printf("\nSTARTING FontFind: pattern=%s\n",pattern);
    if (pattern)
	{
	strcpy(fname,pattern);
    	if ((ffile = findfirst("*.fnt",0)) == NULL)
	    return NULL;		/* no font files found */
	printf("FontFind: found first font file: filename = %s (%lX bytes)\n",
		ffile->name,ffile->size);
	fileoffset=0L;
	}
    while(1)
	{
	printf("Trying file %s: size=%lX, prev offset=%lX, next_file=%d\n",
	    ffile->name,ffile->size,fileoffset,next_file);
	if (fileoffset >= ffile->size)
	    next_file = 1;		/* for next time around */
	if (next_file)
	    {
    	    if ((ffile = findnext()) == NULL)
	    	return NULL;		/* no font files found */
	    printf("FontFind: found next font file: filename = %s (%lu bytes)\n",
		ffile->name,ffile->size);
	    fileoffset=0L;
	    next_file = 0;
	    }
    	iffflg = qread_iffhdr(ffile->name,&fileoffset,&foname.off);
    printf("FONT: IFF type=x%X=%c%c, data at %lX next IFF at %lX\n",
		iffflg,(byte)(iffflg&0xFF),(byte)(iffflg>>8),
		foname.off,fileoffset);
    	if (iffflg != 'FT')
	    next_file = 1;		/* invalid, so try next file */
	else
	    {
    	    strcpy(foname.filnam,ffile->name);	/* init 'foname' filename */
	    fntpfx=FontCheckHdr(&foname,fname);	/* reads fntpfx */
/*	    printf("FontFind: Matching %s with %s\n", fname,fntpfx->fontname);*/
	    if (fntpfx->charcount)
		{
		printf("FontFind: name matched. file=%s, font=%s\n",
		    foname.filnam,foname.fontname);
		return &foname;			/* valid font */
		}
	    }
	}
    return NULL;
    }

#endif
    
