#include "drelease.h"
ID_ WFUTIL_ID[] = 
   "\0@(#) " __FILE__ "    $Revision: 1.13 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/****************************************************************
 *
 *          WFUTIL - Utilities for Linking with WF
 *			 K.T. Rudahl
 * 
 *          $Revision: 1.13 $	$Date: 2014/12/05 14:24:30 $
 *
 *   Written by Kurt Rudahl
 *
 *      ~~ Copyright 1987-2014 Kurt Rudahl and Sally Goldin
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
 *
 *	$Log: wfutil.c,v $
 *	Revision 1.13  2014/12/05 14:24:30  rudahl
 *	reconciled DragonProfessional with OpenDragon
 *
 *	Revision 1.12  2005/03/29 14:40:46  rudahl
 *	renamed cat()
 *
 *	Revision 1.11  2005/03/19 08:00:06  rudahl
 *	lintish
 *	
 *	Revision 1.10  2005/02/18 21:57:55  rudahl
 *	first pass on wfutil
 *	
 *	Revision 1.9  2004/12/23 11:45:15  rudahl
 *	lint-ish fix
 *	
 *	Revision 1.8  2002/07/01 14:26:04  rudahl
 *	cleanup & rev'd tracing info
 *	
 *	Revision 1.7  2002/06/10 12:44:29  rudahl
 *	created 32-bit version of b_memmap
 *	
 *	Revision 1.6  2002/05/03 01:35:33  rudahl
 *	added checksum
 *	
 *	Revision 1.5  2002/04/30 01:13:30  rudahl
 *	convert cat() to fread for large model
 *	
 *	Revision 1.4  2002/02/08 20:27:12  rudahl
 *	made cat() public
 *	
 *	Revision 1.3  2001/09/26 19:06:45  rudahl
 *	minor changes and de-linting for GCC
 *	
 *	Revision 1.2  1999/04/18 21:25:56  rudahl
 *	Minor changes for MSC 32 compile
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.4  1997/09/06  04:49:16  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1997/09/06  04:49:16  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/07/19  21:56:46  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/05/15  12:57:10  tower
 * final for DRAGON 4.0G.
 * 
 * Revision 4.0  1993/05/15  12:57:10  tower
 * final for DRAGON Release 4.00
 * 
 * Revision 3.1  91/06/17  12:54:27  at
 * minor cosmetic, docunentation, & ANSI updates for DRAGON 3.05
 * full Lattice compliance dropped
 * 
 ****************************************************************
 *
 *    Modification History
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *    Version	Who		What & Why
 *    1.0	ktr      	Created	  
 *	2/11/88 ktr		added xcut_cmd & related fns
 *      2/17/88 ktr		added error messages for DOS
 *	7/21/88 ktr		added cat from DINSTALL
 *	3/28/89 ktr		converted to create library fns
 *				get_array moved to tstack
 *	added cputs 8/89
 *	9/4/89 ktr		fixed cat
 *	12/14/89 ktr		examined for large-model problems.
 *				Added use of host.h
 *	7/90 ktr		moved cat() to FILES.C as local fn. in w_files2
 *	7/19/94 ktr		minor changes for MSC v 8
 *	1/22/95 ktr		minor syntax changes for MSC v 8.5
 *	12/10/95 ktr	adapted for Watcom 10.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *      4/18/99 seg     added provision for MFC 32 bit compilation
 *                        WF-specific functions compiled out
 * 	2/7/2002 ktr	moved cat() here from files.c
 *	5/2/2002 ktr	moved checksum here from bandop-o.c
 * 5.4	12/22/2004 ktr	lint-ish
 * 5.5	2005-2-18 ktr	import from Dragon 5.4.4
 *	2005-3-29 ktr	renamed cat() to catt() because C++ doesn't like 'cat'
 ****************************************************************/
/**/
/**
 *
 * This module defines the error messages corresponding to the codes that
 * can appear in _OSERR.  
 * probably the only fn here used in v 5.5 is checkksum() 
 *  and maybe cat() and b_memmap().
 *
 *	cat(srcname,destname)  Copy file
 *	compile with DEBG for debugging version
 *		with TEST for test version (incl. debugging)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#if defined __GCC__ 
//#include <unistd.h>
#include <sys/stat.h>
#else
#include <sys\stat.h>
#include <dos.h>
#include <io.h>
#endif


#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "logger.h"

//#include "wf.h"
//#include "stats.h"
#include "wfutil.h"
#include "files.h"

#include "dragonOb.h"
//#include "IpcWrap.h"

void WFUTIL() {}

#define OSERRNUM 110	/* Highest valid error number */

#ifdef DEBG
static char *os_errlist[OSERRNUM+1] = {	
			"Unknown error code",
/* 01 */		"Invalid function number",
/* 02 */		"File not found",
/* 03 */		"Path not found",
/* 04 */		"Too many files opened",
/* 05 */		"Access denied",
/* 06 */		"Invalid handle",
/* 07 */		"Memory control blocks destroyed",
/* 08 */		"Insufficient memory",
/* 09 */		"Invalid memory block address",
/* 10 */		"Invalid environment",
/* 11 */		"Invalid format",
/* 12 */		"Invalid access code",
/* 13 */		"Invalid data",
/* 14 */		"Error 14",
/* 15 */		"Invalid drive code",
/* 16 */		"Can't remove current directory",
/* 17 */		"Not same device",
/* 18 */		"No more files",
/* 19 */		"Can't write on protected device",
/* 20 */		"Unknown unit",
/* 21 */		"Drive not ready",
/* 22 */		"Unknown command",
/* 23 */		"Data error",
/* 24 */		"Bad request structure length",
/* 25 */		"Seek error",
/* 26 */		"Unknown media type",
/* 27 */		"Sector not found",
/* 28 */		"Printer paper alarm",
/* 29 */		"Write fault",
/* 30 */		"Read fault",
/* 31 */		"General failure",
/* 32 */		"Sharing violation",
/* 33 */		"Lock violation",
/* 34 */		"Invalid disk change", 
/* 35 */		"FCB unavailable",
/* 36 */		"Sharing buffer overflow",
/* 37 */	NULL,	/*		"Error 37",	*/
/* 38 */	NULL,	/*		"Error 38",	*/
/* 39 */	NULL,	/*		"Error 39",	*/
/* 40 */	NULL,	/*		"Error 40",	*/
/* 41 */	NULL,	/*		"Error 41",	*/
/* 42 */	NULL,	/*		"Error 42",	*/
/* 43 */	NULL,	/*		"Error 43",	*/
/* 44 */	NULL,	/*		"Error 44",	*/
/* 45 */	NULL,	/*		"Error 45",	*/
/* 46 */	NULL,	/*		"Error 46",	*/
/* 47 */	NULL,	/*		"Error 47",	*/
/* 48 */	NULL,	/*		"Error 48",	*/
/* 49 */	NULL,	/*		"Error 49",	*/
/* 50 */	NULL,	/*		"Network request not supported",	*/
/* 51 */	NULL,	/*		"Remote computer not listening",	*/
/* 52 */	NULL,	/*		"Duplicate name on network",	*/
/* 53 */	NULL,	/*		"Network name not found",	*/
/* 54 */	NULL,	/*		"Network busy",	*/
/* 55 */	NULL,	/*		"Network device no longer exists",	*/
/* 56 */	NULL,	/*		"Net BIOS command limit exceeded",	*/
/* 57 */	NULL,	/*		"Network adaptor hardware error",	*/
/* 58 */	NULL,	/*		"Incorrect response from network",	*/
/* 59 */	NULL,	/*		"Unexpected network error",	*/
/* 60 */	NULL,	/*		"Incompatible remote adaptor",	*/
/* 61 */	NULL,	/*		"Print queue full",	*/
/* 62 */	NULL,	/*		"Not enough space for print file",	*/
/* 63 */	NULL,	/*		"Print file was deleted",	*/
/* 64 */	NULL,	/*		"Network name was deleted",	*/
/* 65 */	NULL,	/*		"Access denied",	*/
/* 66 */	NULL,	/*		"Incorrect network device type",	*/
/* 67 */	NULL,	/*		"Network name not found",	*/
/* 68 */	NULL,	/*		"Network name limit exceeded",	*/
/* 69 */	NULL,	/*		"Net BIOS session limit exceeded",	*/
/* 70 */	NULL,	/*		"Temporarily paused",	*/
/* 71 */	NULL,	/*		"Network request not accepted",	*/
/* 72 */	NULL,	/*		"Print or disk redirection is paused",	*/
/* 73 */	NULL,	/*		"Error 73",	*/
/* 74 */	NULL,	/*		"Error 74",	*/
/* 75 */	NULL,	/*		"Error 75",	*/
/* 76 */	NULL,	/*		"Error 76",	*/
/* 77 */	NULL,	/*		"Error 77",	*/
/* 78 */	NULL,	/*		"Error 78",	*/
/* 79 */	NULL,	/*		"Error 79",	*/
/* 80 */	NULL,	/*		"File exists",	*/
/* 81 */	NULL,	/*		"Error 81",	*/
/* 82 */	NULL,	/*		"Cannot make directory entry",	*/
/* 83 */	NULL,	/*		"Fail on INT 24",	*/
/* 84 */	NULL,	/*		"Too many redirections",	*/
/* 85 */	NULL,	/*		"Duplicate redirection",	*/
/* 86 */	NULL,	/*		"Invalid password",	*/
/* 87 */	NULL,	/*		"Invalid parameter",	*/
/* 88 */	NULL,	/*		"Network device fault"	*/
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/*    */	NULL,
/* 100	*/		"Trying to Close Not-open File ", 
/* 101	*/		"File Already Open  ",
/* 102	*/		"File Creation Error ",
/* 103	*/		"File Open Error    ",
/* 104	*/		"Trying to Write Not-open File ", 
/* 105	*/		"Read Error-Probably Past End-of-file ",
/* 106	*/		"Write Error-Device May Be Full      ",
/* 107	*/		"Unable To Delete File ",
/* 108	*/		"Data Truncation-Destination Too Small ",
/* 109  */		"Graphics Driver not installed",
/* last */     		"Unknown error number"
			} ;

#endif	/* DEBG */

#ifdef NOTNOW

static byte os_errflag[OSERRNUM/8+1] =	/* 1 => fatal error */
  /* 0 */	{ 0, 0, 0, 0, 
  /* 32 */	  0, 0, 0, 0,
  /* 64 */	  0, 0, 0, 0, 
  /* 96 */	  0x30, 0xFF } ;
/**/

SINT16 SendIntMsg(intnum,fcode,receiver_id,doubt) 
			/* send message via an interrupt
			 * 'intnum' is interrupt number	and 'fcode' is the message
			 * type number. Message itself is in CTOK[].
			 * If 'doubt' then the receiving task may not be loaded.
			 * 'receiver_id' is both the identifying string and
			 * the .exe (or .com) filename if not yet loaded.
			 * May be extended to handle remote processes.
			 */
SINT16 intnum,fcode,doubt;	   
char *receiver_id;	/* file name */
    {	   
    union REGS Regs;	  
    ptr86 idptr;
    char idbuf[13];
    SINT16 tsrerr;	/* non-zero => interrupt handler not found */
	/* cprintf(">INT86: seg:offset=%x:%xx\n",CtokRegs.x.cx,CtokRegs.x.dx);*/
    tsrerr=doubt;
    if (doubt)
	{
	SetCRegs();	/* make sure it's initialized */
	peek(0,intnum<<2,(char *) &idptr,4);	/* get current interrupt ptr */
	peek(idptr.w.seg,idptr.w.offset-13,idbuf,12); /* get id string */
	/*    cprintf("TSR id = %s\n",idbuf); */
	if (tsrerr=strncmp(receiver_id,&idbuf[4],strlen(receiver_id)))
	    {
	    /* cprintf("   id found=%s, sought=%s, lenght of sought=%d\n",
	    	&idbuf[4],receiver_id,strlen(receiver_id)); */
	    tsrerr=forklp(receiver_id,receiver_id,"-TSR",NULL);
	    if (!tsrerr) wait();
	    }
	}
    CtokRegs.x.ax = -fcode; 
    if(!tsrerr)
	int86(intnum,&CtokRegs,&Regs); /* diff. REGSs to avoid re-init CtokRegs */
    return(tsrerr);	/* 0 if OK */
    }

SetCRegs()	/* set CtokRegs to point to CTOK[0] for use by SendIntMsg */
    {
    makedv((char *) &CTOK[0],&CtokRegs.x.dx,&CtokRegs.x.cx);
    }

#endif /* NOTNOW */

#ifndef __32BIT__	 
void cputs(char * string)
		/*	put string to screen without using DOS */
    {
    union REGS Regs;
    while(*string)
	{
#if defined __WATCOMC__	// just minor diff. in register names
	Regs.w.ax = 0xE00 | *string++;
	Regs.w.bx = 0xFF;	/* white text */
#else
	Regs.x.ax = 0xE00 | *string++;
	Regs.x.bx = 0xFF;	/* white text */
#endif
	int86(0x10,&Regs,&Regs);
  	}
    }
#endif

int xcut_cmd(char ** argv,CMDS * cmd_tab,char * fn_id)
		/* execute command pointed to by argv & update 
		 * return argv increment. Use command table 
		 * pointed to by 'cmd_tab'. 'fn_id' is a string
		 * identifying the calling function for debugging.
		 */
	{
    	CMDS	*cmdp;
/*	strupr(*argv);*/	/* CMD table must be in CAPS */
	/* look up the argument in the command table */
	for (cmdp = cmd_tab;  cmdp->str != NULL;  ++cmdp)
	    {
	    if (stricmp(*argv, cmdp->str) == 0)
		break;	/* match without regard to case */
	    }
	(*cmdp->fnct)(++argv); /* execute the command */
  	return(cmdp->nargs);
	}

#ifdef NOMORE
int pr_ioerr(const int errnum)
		/* print io error message on console &
		 * in logging file. Return 1 if fatal error
		 * messages derived from Lattice's OSERR.C
		 */
    {			     
    if ((errnum < 0) || (errnum > OSERRNUM))
	return(pr_ioerr(OSERRNUM));	/* fatal error */
    return((os_errflag[errnum/8]>>(errnum%8)) & 1);
    }
#endif

#if defined __LARGE__ || defined __32BIT__ 

     /* calculate and return a 32-bit checkup
      */
UINT32 checksum(const void * pData, const size_t uSize)
    {
    UINT32 ulRetval = 0;
    size_t i = 0;
    const UINT32 * pItem = pData;
    while (i < uSize)
	{
	if ((uSize - i) < sizeof(UINT32))
	    {
	    UINT32 tmp = 0;
	    memcpy(&tmp,(char *)pItem,uSize-i);
	    ulRetval += tmp;
	    }
	else
	    ulRetval += *pItem++;
	i += sizeof(UINT32);
	}
    return ulRetval;
    }

int catt(const char *srcname,const char *destname)
	/*	Copy file 'srcname' to 'destname'.
	 *	Files are opened in binary mode.
	 *	Return: -1 = read err, -2 if write err, -3 if mem err,
	 *	 or 0 if OK
	 */
    {
    byte buf[2048];
    long offset = 0L;
    int bsize = sizeof(buf);
    int iRetval = 0;
    size_t got=0;
    FILE * fpI = fopen(srcname,"rb");  
    FILE * fpO = fopen(destname,"wb");  

    logTrace("big CAT: bsize = %x; buf=%p; source='%s' dest='%s'",
	     bsize,buf,srcname,destname);
    if (fpI == NULL)
        iRetval = -1;
    else if (fpO == NULL)
        iRetval = -2;
    else
        {
	while( (got = fread(buf,1,bsize,fpI)) > 0 )
	    {
//	    logTrace("CAT: offset = %ld",offset);
	    if (fwrite(buf,1,got,fpO) < got)
	        {
		iRetval = -2;
		break;
		} 
	    offset += (long) got; /* just used for logging */
	    }
	logTrace("CAT: done; last buffer = %x",got);
	}
    if (fpI != NULL)
        fclose(fpI);
    if (fpO != NULL)
        fclose(fpO);
    return iRetval;
    }

	/*	map data from pSource to pDest possibly changing its size, 
	 *	possible throught a translation table.
	 *	In practice, only specific values of uPitch are supported:
	 *	  specifically (at present) low byte == 1, high byte = 1-n
	 *	Ideally this should be oprimized for speed regardless of size
	 *	    example: b_memmap(to,x202,from,x1FF,320,table)
	 * 		maps 320 elements from a word array to a word array,
	 *		skipping no bytes in either array. Elements of 'from'
	 *		are masked by 1FF, so 'table' must be 512 x 2.
	 *	@param pDest	buffer to put data. Must be large enough.
	 *	@param uPitch	low byte is pitch (# bytes per data element)
	 *			  of destination
	 *			high byte is pitch (# bytes per data element)
	 *			  of source
	 *	@param pSource	buffer to get data. Must be large enough.
	 *	@param uMask	mask applied to source elements (before
	 *			applying remap table)
	 *	@param uCount	number of elements of array 'pSourcer' to map
	 *			to 'pDest'
	 *	@param pTable	if non-NULL, is an array (of length > max
	 *			value resulting from masking a 'pSource'
	 *			data element) which remaps source data values
	 *			to destination values.
	 */
void b_memmap(void * pDest,const unsigned uPitch,
	      const void * pSource, const unsigned uMask,
	      const unsigned uCount, const void * pTable)
    {
    size_t uDestPitch = uPitch & 0xFF;
    size_t uSourcePitch = (uPitch>>8) & 0xFF;
    if (uMask < 0x100) /* move as bytes? */
	{
	byte * pByteDest = pDest;
	const byte * pByteSource = pSource;
	size_t i = 0;
	for (i=0; i<uCount; i++)
	    {
	    byte uTmp = *pByteSource & uMask;
	    * pByteDest = (pTable == NULL) ? uTmp : ((byte *)pTable)[uTmp];
	    pByteSource += uSourcePitch;
	    pByteDest += uDestPitch;
	    }
	}
    }

#else
int cat(const char *srcname,const char *destname)
	/*	Copy file 'srcname' to 'destname'.
	 *	Files are opened in binary mode.
	 *	Return: -1 = read err, -2 if write err, -3 if mem err,
	 *	 or 0 if OK
	 */
    {
    byte far * buf;
    UINT32 offset = 0L;
    int bsize = 0x7000;
    int got=0;
    if (w_files1(destname,WF_MAKE) < 0)		/* make empty file */
	return -1;
    while( ((buf = halloc(bsize,1)) == FARNULL) && (bsize > 0x40)  )
	bsize >>= 1 ;	/* get largest avail buffer */

    if (buf)
	{
    	while( (got = rsf(srcname,buf,bsize,offset,0)) > 0 )
	    {
/* printf("CAT: offset = %ld\n",offset); */
	    if (wsf(destname,buf,got,(offset==0) ? WSF_OVERWRITE : WSF_APPEND) < 0)
		{
		hfree(buf);
		return -2;
		} 
	    offset += (long) bsize;
	    }
/* printf("CAT: got = %x\n",got);*/
    	hfree(buf);
	}
    else
	{
/*printf("CAT: no memory for copy\n");*/
	return -3;
	}
    return ((got < 0) ? -1 : 0);
    }
#endif // if defined __LARGE__ || defined __32BIT__ 

void WFUTIL_END() {puts(FIL_ID);}

