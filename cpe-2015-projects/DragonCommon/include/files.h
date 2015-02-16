/*
 *	FILES.H
 *	prototypes necessary for file functions
 *
 *	Kurt T. Rudahl -- May 16, 1989
 *      ~~ Copyright 1989-2014 Kurt Rudahl and Sally Goldin
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
 *	~~  EndC
 ****************************************************************
 *   $Id: files.h,v 1.18 2014/12/05 10:38:00 rudahl Exp $
 *   $Log: files.h,v $
 *   Revision 1.18  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.17  2010/12/05 03:54:31  rudahl
 *   added diskfreespace
 *
 *   Revision 1.16  2008/01/26 15:37:02  rudahl
 *   adjust copyright date
 *
 *   Revision 1.15  2005/12/31 05:13:05  rudahl
 *   modified arg to rsf
 *
 *   Revision 1.14  2005/12/09 13:33:16  rudahl
 *   rsf was not giving good error reporting
 *
 *   Revision 1.13  2005/09/24 14:22:09  rudahl
 *   got rid of far pointers
 *
 *   Revision 1.12  2005/09/12 07:30:41  rudahl
 *   fixes re dp.h
 *
 *   Revision 1.11  2005/09/05 10:45:13  rudahl
 *   got rid of GetMsgNo
 *
 *   Revision 1.10  2005/03/29 14:39:55  rudahl
 *   renamed cat()
 *
 *   Revision 1.9  2005/03/19 06:25:44  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.9  2005/03/13 02:42:58  rudahl
 *   fix probs found working with enhance
 *
 *   Revision 1.8  2005/02/11 18:58:45  rudahl
 *   added file_next
 *
 *   Revision 1.7  2005/02/10 04:59:39  rudahl
 *   cleaned up tracing and error reporting
 *   cleaned up image file writing
 *
 *   Revision 1.6  2005/01/29 11:29:49  rudahl
 *   adapt to v 5.5
 *
 *   Revision 1.5  2002/04/09 21:32:36  rudahl
 *   adapt for long filenames
 *
 *   Revision 1.4  2002/02/08 20:26:28  rudahl
 *   made cat() public
 *
 *   Revision 1.3  2002/01/15 12:33:04  rudahl
 *   fixed error message bug
 *
 *   Revision 1.2  1999/04/18 00:03:16  rudahl
 *   Minor changes to handle _WIN32
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.7  1998/01/23  08:09:48  tower
 * checkin for class class5_0
 * 
 * Revision 4.6  1998/01/23  08:09:48  tower
 * checkin for class class5_0
 * 
 * Revision 4.5  1998/01/23  08:09:48  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.4  1996/08/04  12:02:02  lcd
 * checkin for class class49
 * 
 * Revision 4.3  1995/12/29  06:32:26  lcd
 * checkin for class class49
 * 
 * Revision 4.1  1994/07/23  09:00:20  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/12/23  10:50:28  tower
 * final for DRAGON 4.0G.
 * general changes: MSC v 6 adaptations, graphics screens to 1280 pix.
 * 
 * Revision 4.0  1993/06/15  21:34:32  tower
 * Final for DRAGON Release 4.0
 * 
 * Revision 4.0.1.1  93/02/13  15:54:06  tower
 * added provision for b_mem fns for LARGE model
 * 
 * Revision 4.1  92/11/13  11:52:10  tower
 * made all prototypes be extern "C" for use with C++
 * 
 * Revision 4.0  92/06/03  08:44:06  tower
 * Update for Zortech 3.0; begin DRAGON Professional
 * remove dependency on host.h
 * 
 * Revision 3.7  92/02/23  13:29:42  tower
 * final (?) for 3.05. Added CONFIGSTRLEN to control getconfig
 *                     changed FILES_MSG to a #define
 * 
 * Revision 3.6  91/11/25  21:01:59  tower
 * for 3.05: added 'const's to b_mem fns
 * 
 * Revision 3.5  91/09/19  19:07:12  tower
 * removed ZORTECH symbol; moved SEARCH here from dragfile.h; 
 * changed errmsg.dat to emsg
 * 
 * Revision 3.4  91/08/18  10:46:26  tower
 * for 3.05: added WF_ACCESS, EMSGFILE; fixed some prototypes
 * 
 * Revision 3.3  91/06/17  13:45:02  tower
 * minor fixes; for use with DRAGON 3.05
 * 
 * Revision 3.2  91/02/16  23:00:39  tower
 * added named constants for wsf() modes
 * 
 *
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *	8/1/90 added 'const' as appropriate to prototypes
 *	12/2/90 added 'extern "C"' to b_mema fns
 *	2/16/91 added constant #defines for WSF modes
 *	6/10/91 changed b_mem... fns from byte * to void *
 *	7/12/91  same for b_read, b_write, rsf, wsf, wsfo
 *	8/11/91 added GetMsg, EMSGFILE
 *	8/27/91 removed need for ZORTECH symbol;
 *		 moved SEARCH here from dragfile.h
 *	10/10/91 added 'const's to b_mem fns
 *	2/11/92 added CONFIGSTRLEN to permit GetConfig up to 255 chrs
 *	7/13/92 made all prototypes be extern "C" types
 *	2/11/93 added provision for b_mem fns for LARGE model
 *	4/23/93 added b_strncpy, b_strcmp, b_strlen
 *	5/5/93 added keepfilesopen()
 *	6/13/93 added WSF_NOFLUSH, docs to this file
 *	6/15/93 moved WFFILE structure here from files.c
 *	12/22/93 started adapting to MSC6
 *	3/29/94 ktr	added size param to GetConfig & GetMsg
 *	7/19/94 ktr	cleanup for MSC v 8
 *	1/22/95 ktr	minor syntax change for MSC
 *			renumbered F_DSK_CRITERR from 400000 to 40
 *			  because wsf, etc can return only errs <= MAX_INT
 *			to do this, combined F_WSF_CREATE with F_WSF_CR_OPEN
 *	12/12/95 ktr	adapt for Watcom 10.0
 *	12/29/95	add get_bsize(size_t min,size_t max, size_t incr)
 *	8/4/96 ktr	add PutConfig; initially only for LARGE model
 *	10/11/97 ktr	added bWsfResetAfterWrite & DosDiskReset()
 *	1/23/98 ktr	added WF_DEVICESTATUS
 *	4/9/02 ktr	moved WFFILE back to files.c - it's private
 * 5.5	2005-1-29 ktr	adapt for Dragon 5.5
 *	2005-2-8 ktr	convert to dragon-errors
 *	2005-2-11 ktr	merged find_first, find_next from zfile
 *	2005-3-29 ktr	renamed cat() to catt() because C++ doesn't like 'cat'
 * 5.7	2005-9-5 ktr	got rid of GetMsgNo
 *	2005-12-31 ktr	extended meaning of 'mode' arg for rsf
 * 6.1	2010-12-02 ktr	added getDiskFreeSpace
 */

#ifndef FILES_H
#define FILES_H

#ifndef F_OK	/* for MSC6, at least */
#define F_OK 0
#endif

//#define EMSGFILE "emsg.dat"	/* eventually, get from .CFG */
#ifndef CONFIGSTRLEN
#define CONFIGSTRLEN 256	/* anyone who calls getconfig must allow 1+ */
#endif

#ifdef __cplusplus
extern "C" {
#endif

        /* get the size of the file, or -1
         */
long file_size(const char * pczFileName);

long fsize(FILE * pFile);

/********************************
 * find file matching name & attributes
 * Returns:
 *	NULL	if file doesn't exist
 *      struct * _find_t otherwise
 */

struct _find_t * find_first(const char * name,const unsigned int attrib);
struct _find_t * find_next();
void find_free();  // noop except for unix

	/*   read 'size' bytes of small file starting at 'offset':
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
int rsf(const char * name,void * buffer,
	const int size,const SINT32 offset,const int mode);

	/* write 'size' bytes to small file. 
	 *    mode=WSF_TRUNC => replace 'name'   
	 *	WSF_APPEND => append if 'name' exists
	 *	2 => return -5=error if 'name' exists
	 *	3 => create if doesn't exist or write-in-place
	 *    mode & WSF_BUFFER => buffer until buffer full or EOL ('\n')
	 *    mode & WSF_NOFLUSH => suppress effect of '\n' in WSF_BUFFER mode
	 *    return bytes written or < 0 => error  (therefore 'size' < 32000
	 */
int wsf(const char * name,const void * buffer,const int size,const int mode);
	/*	write 'size' bytes to small file. Just like wsf mode 3
	 *	except 'offset' tells where in file to write to.
	 *	Therefore if file is too small, or 
	 *		  if offset > 0 and file doesn't exist,
	 *			return -1 = error
	 *	return bytes written or < 0 => error; therefore 'size' < 32000
	 */
int wsfo(const char *name,const void * buffer,
	 const int size,const SINT32 offset);

	/*	get a string from a file using rsf. 
	 *	'size' is max buffer size, so actual read is size-1
	 *	If 'offset' == -1L, locally-maintained offset is used for file 
	 *	position; otherwise 'offset' must be maintained by calling pgm.
	 *	If 'size' == 0, just try reading at 'offset';
	 *	  and returned ptr is significant only as err indicator
	 *	Read is in raw form, so strlen of returned string can 
	 *	be used to maintain current file position.
	 *	return pointer to string or NULL
	 *
	 *	mod 12/21/90 ktr for rel 3.03 - buffering for rsfgets
	 *		only when using offset == -1 mode
	 */
char * rsfgets(char *str,const UINT16 size,
		   const char *name,const SINT32 offset);

	/*	Copy file 'srcname' to 'destname'.
	 *	Files are opened in binary mode.
	 *	Return: -1 = read err, -2 if write err, -3 if mem err,
	 *	 or 0 if OK
	 */
int catt(const char *srcname,const char *destname);

	/* in getcfg.c */
	/*	get value of matching string from DRAGON.CFG (cfg_file)
	 *	form is <searchstr>=<target>
	 *	target delim by first char <= X20, or by matching quote
	 *	copies info to errstat also ONLY if found.
	 *	Normally reads actual file only once; 
	 *	  if 'searchstr' == NULL, just read file into buffer
	 *	  'cfgbuf' and tokenize it like environment.
	 *	    filecall, because NULL doesn't get propagated)
	 *	Return < 0 if error or no match found, else charcnt
	 *	Sets errstat if file error
	 *	Releases buffer if search with empty string or searchstr==NULL
	 *	size of 'dest' could be as much as CONFIGSTRLEN+1
	 */
int GetConfig(const char *,char * dest,const int destsize);

	/*	get message ( < D_PRINTBUF && < 'destsize' chars) from msg_file
	 *	first chars match pattern, which is excluded from 'dest'
	 *	return -1 if error, charcount if OK
	 */
int GetMsg(const char * msgno,char * dest,const int destsize);

	/*	get message ( < D_PRINTBUF && < 'destsize' chars) from msg_file
	 *	first chars match "%e<msgnum> ", which is excluded from 'dest'
	 *	return -1 if error (but a valid string put into 'dest' anyway),
	 *	charcount if OK
	 */
//int GetMsgNo(const int msgnum,char * dest,const int destsize);

extern char * msg_file;
extern char * cfg_file;

	/* rewrite current config file to contain a line of form:
	 *     'pczKey'='pczValue', where 'pczValue' may include a
	 *	comment prefixed by blank or tab not within quotes
	 *	If 'bReplace', delete any existing string with 'pczKey'
	 *	else add additional one
	 *	If 'pczValue'==NULL, just delete do not replace
	 *	Return 0 if OK
	 */
int PutConfig(const char * pczKey, const char * pczValue, const BOOL bReplace);

void GetOSVer(void);

int PathOK(const char * pczPath);
	/* chack pczPath is a valid path for current OS
	 * Return 0 if OK else some appropriate code < 0
	 */

	/* get total available disk space in the specified directory
	 * (For dos/windows, assume first character of directory is a drive)
	 * @return	free space (KB) if OK
	 *		if free space > LONG_MAX, return LONG_MAX
	 *		return -1 if error
	 */
long getFreeDiskspace(const char * czDir);

#ifdef __cplusplus
    }
#endif

/* mode selectors for wsf */
#define WSF_TRUNC 	0	/* delete file if exists */
#define WSF_APPEND	1	/* append to file if exists */
#define WSF_TEST	2	/* return error if exists */
#define WSF_OVERWRITE	3	/* overwrite at offset 0 */
#define WSF_BUFFER	8	/* buffer to '\n': OR with other values */
#define WSF_NOFLUSH	4	/* buffer to full buffer: OR with above */

#ifdef NOMORE
/* selectors for w_files0 */
#define WF_DSKSIZE 	0
#define WF_DSKSPACE	1
#define WF_DSKTYPE	2
#define WF_DEVICESTATUS 3	/* return 0 if not ready */

/* selectors for w_files1 */
#define WF_MAKE 	0
#define WF_DEL 		1
#define WF_SIZE 	2
#define WF_ATTRIB	3
#define WF_CD 		4
#define WF_ACCESS	5

/* selectors for w_files2 */
#define WF_RENAME 	0
#define WF_COPY  	1
#define WF_COMPARE 	2

#endif

#ifdef NOMORE
	/* error numbers for errstat */
#define F_BREAD_ALL	0x30000L
#define F_BREAD_EOF 	0x10000L /* b_read premature eof */
#define F_BREAD_ER	0x20000L /* b_read error */

#define F_BWRT_ALL	0xC0000L
#define F_BWRT_ER	0x40000L /* b_wrt error */

#define F_SWAP_ALL	0x300000L
#define F_BAD_SWAP	0x100000L
#define F_INSUF_SWAP	0x200000L

#define F_RSF_ALL	0x20FL
#define F_RSF_BADMODE	0x1L	/* rsf bad mode # */
#define F_RSF_OPEN	0x2L	/* rsf open error */
#define F_RSF_SEEK	0x4L	
#define F_RSF_READ	0x8L

#define F_WSF_ALL	0x3F0L
#define F_WSF_BADMODE	0x10L
/*#define F_WSF_CREATE	0x20L */
#define F_DSK_CRITERR	0x20L	/* used for Find1st, wsf */
#define F_WSF_CR_OPEN	0x40L	/* couldn't create or open file */
#define F_WSF_ALREADY	0x80L	/* file already exists */
#define F_WSF_WRITE	0x100L
#define F_CLOSE		0x200L

#define F_WSFO_ALL	0x7C00L
#define F_WSFO_OPEN_OFFSET 0x400L /* non-zero offset, file doesn't exist */
#define F_WSFO_CREATE	0x800L
#define F_WSFO_SEEK	0x1000L
#define F_WSFO_WRITE	0x2000L	
#define F_WSFO_CLOSE	0x4000L

#define F_DOSCMD_MHEAP	0x1000000L	/* MHEAP removed */

#define F_DOS_HEAPCLR   0x3000000L
/* #define F_DSK_CRITERR	0x4000000L */	/* mostly used for Find1st */
#define F_GETCFG_FILE   0x8000000L	/* error reading DRAGON.CFG */

#define FILES_MSG	/* one msg per bit in errstat word */ \
    	"Rsf bad mode number","Rsf file open error", \
	"Rsf file seek error","Rsf file read error", \
	"Wsf bad mode number","Disk device critical error", \
	"Wsf file create/open error","File already exists", \
	"Wsf file write error","Wsf file close error", \
	"Wsfo file doesn't exist","Wsfo file create error", \
	"Wsf file seek error","Wsf file write error", \
	"Wsf file close error",NULL,	/* can't use bit 15 */\
	"B_read premature end-of-file","B_read file read error", \
	"B_write file write error", NULL,  \
	"Bad swap disk","Too little space on swap disk", \
	NULL, NULL,\
	"MHEAP removed", "" , \
	NULL, "Unable to read DRAGON.CFG", \
	"LAST MESSAGE"

#endif

#endif
