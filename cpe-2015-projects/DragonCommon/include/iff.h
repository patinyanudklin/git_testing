/*  $Revision: 1.2 $	$Date: 2014/12/05 09:58:46 $
 *
 *	IFF.H - misc definitions for use with DRAGON & WF
 *		IFF-structured files.
 *          Version 1.0    1/26/89
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
 *   $Id: iff.h,v 1.2 2014/12/05 09:58:46 rudahl Exp $
 *   $Log: iff.h,v $
 *   Revision 1.2  2014/12/05 09:58:46  rudahl
 *   no differences between DragonProf and OpenDragon
 *
 *   Revision 1.1  2005/03/19 06:25:44  rudahl
 *   CVS moved from windu; maybe some history lost
 *
 *   Revision 1.2  2005/03/16 04:07:41  rudahl
 *   importing
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 4.2  1994/06/09  12:49:36  tower
 * checkin for class class5_0
 * 
 * Revision 4.1  1994/06/09  16:49:36  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/12/22  22:09:58  tower
 * final for DRAGON 4.0G.
 * general changes: MSC v 6 adaptations, graphics screens to 1280 pix.
 * 
 * Revision 4.0  1992/11/13  11:49:54  tower
 * Final for DRAGON Release 4.0
 * 
 * Revision 4.0  92/11/13  11:49:54  tower
 * added provision for widgets file (needed for DRAG-UI)
 * and iff-chk (not yet used).
 * for Release 4.0
 * 
 * Revision 3.4  91/12/07  13:11:03  tower
 * for 3.05. simplified
 * 
 * Revision 3.3  91/02/16  22:59:41  tower
 * corrected annotation; added prototypes for seek_iff() and rewrite_iff()
 * 
 *      1/26/91 SEG added FNT_LIST constant for new font list handling
 *
 ****************************************************************
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
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *    1/26/91 SEG 	added FNT_LIST constant for new font list handling
 *    2/16/91 ktr 	added seek_iff(), rewrite_iff()
 *    8/14/92 ktr	removed host.h
 *   10/23/92 ktr	added IFF header definitions for widgets, iff_chk
 *			added prototypes for iff_chk.c
 *    12/22/93 ktr	for MSC6, can't use 2-char constants
 *	6/9/94 ktr	added extern "C" for c++ pgms
 * 5.5	2005-3-15 ktr	import from Dragon v 5.4.4
 */

#ifndef IFF_H
#define IFF_H

#ifdef __cplusplus
extern "C" {
#endif

typedef union XN11190
    {
    struct XM11190
	{	
    	byte full_name[4];
    	byte full_size[4];
	} ch;
    struct XO11190
	{
	unsigned int wf_name;
	unsigned int tag_name;
	long lsize;
	} num;	     
    } IFF_HDR;

typedef struct xx92A23
    {
    byte startloc[4];	/* start disk location of checked section (rad64)*/
    byte size[4];	/* size (bytes) of checked section (rad64)*/
    byte checksum[4];	/* checksum (rad24) of checked section (rad64)*/
    byte unused[4];
    } IFF_CHK_BLK;

int write_iff(const char * name ,const SINT32 size, 
		const byte * buf,const UINT16 mode);
	/* write (append) size, hdr name to file
	 * 'mode' is as for 'wsf' (=1 for create/append )
	 * the write function creates rad64 format headers
	 * write IFF header from buf[4] */
int qread_iffhdr(const char * fname,const UINT32 * posn,UINT32 * block);
	/* read IFF header of char=file
	 * posn is offset in file; gets  
	 * adj to offset of next IFF or EOF */
long seek_iff(const char * name,const char * id,long offset);
	/*	get file position if any where iff id is to be found
	 *	starting a file position 'offset' .
	 *	'id' is four-char string.
	 *	Return file position immed. following IFF, 
	 *	or <= 0L if error
	 */
int rewrite_iff(const char * name,const SINT32 size,
		 const byte * text,const UINT32 offset);

const char * iff_ermsgptr(const int,const char *[]);  
		/* return message ptr or NULL */

       /* values for qread_iffhdr return */
#define IFF_OPEN_ERR 	-11	/* file io errors */
#define IFF_SEEK_ERR  	-12	
#define IFF_EOF 	-13	/* EOF indicates no error but no match */
#define IFF_READ_ERR 	-14
#define IFF_WRITE_ERR	-15
#define IFF_NOMEM	-16	/* no room for IFF)CHK buffer */
#define IFF_WRONGID	-17	/* id found was not one specified */
#define NOT_IFF_ERR 	0 	/* no error, but not IFF file */

#ifdef __ZTC__
#define WF_NAME 	'FW'    /* all tags start with this */
#define CHECKSUM	'KC'	/* (long) sum of data excluding IFF hdr:len=4 */
#define COLOR_HI 	'HC'	/* hi-color-res color file */
#define COLOR_LO 	'LC'	/* lo-			   */
#define IMAGE_STD 	'SI'	/* standard DRAGON image file */
#define IMAGE_W	        'WI'	/* word (16-bit) image file   */
#define IMAGE_1	        '1I'	/* 1-bit-per-pixel image file */
#define IMAGE_2	        '2I'	/* 2-bits		      */
#define IMAGE_QUAD      'QI'	/* image in quadtree format   */
#define NDX_TREE 	'TD'    /* balanced tree e.g. for WFAVL */
#define IFF_CHECK 	'KC'    /* 24-byte checksum in IFF-CHK.C */
#define IFF_WIDGET 	'DW'    /* widget definitions for rpanel */

#define FNT_LIST        'FT'    /* font list section of DRAGON.IF */
                                /* used in dfiles.h, query_font... */
                                /* should others be in opposite order?? */   

#else
#define WF_NAME 	'W' + ('F'<<8)  /* all tags start with this */
#define CHECKSUM	'C' + ('K'<<8)	/* (long) sum of data excluding IFF hdr:len=4 */
#define COLOR_HI 	'C' + ('H'<<8)	/* hi-color-res color file */
#define COLOR_LO 	'C' + ('L'<<8)	/* lo-			   */
#define IMAGE_STD 	'I' + ('S'<<8)	/* standard DRAGON image file */
#define IMAGE_W	        'I' + ('W'<<8)	/* word (16-bit) image file   */
#define IMAGE_1	        'I' + ('1'<<8)	/* 1-bit-per-pixel image file */
#define IMAGE_2	        'I' + ('2'<<8)	/* 2-bits		      */
#define IMAGE_QUAD      'I' + ('Q'<<8)	/* image in quadtree format   */
#define NDX_TREE 	'D' + ('T'<<8)  /* balanced tree e.g. for WFAVL */
#define IFF_CHECK 	'C' + ('K'<<8)  /* 24-byte checksum in IFF-CHK.C */
#define IFF_WIDGET 	'W' + ('D'<<8)  /* widget definitions for rpanel */

#define FNT_LIST        'T' + ('F'<<8)  /* font list section of DRAGON.IF */
                                /* used in dfiles.h, query_font... */
                                /* should others be in opposite order?? */   

#endif

#ifdef OLD
#define CLF_LOW COLOR_LO
#define CLF_HIGH COLOR_HI
#endif
    
#ifdef IFF_ERRS
char * iff_errs[] = {
	"","Error opening file" , 
	"Error reading file","Unexpected end-of-file during read",
	"Error writing file","No memory for checking IFF file",
	"Wrong IFF ID found" } ;
#define iff_ermsg(a) iff_ermsgptr(a,iff_errs)
#else
#define iff_ermsg(a) iff_ermsgptr(a,NULL)
#endif

#ifdef __cplusplus
     }
#endif

#endif
