/****************************************************************
 *	TOOLERR.H - error values for DRAGON utilities toolkit
 *          $Revision: 1.2 $	$Date: 2014/12/05 09:58:46 $
 *
 *      ~~ Copyright 1992-2014 Kurt Rudahl and Sally Goldin
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
 *
 *****************************************************************
 *	$Id: toolerr.h,v 1.2 2014/12/05 09:58:46 rudahl Exp $
 *	$Log: toolerr.h,v $
 *	Revision 1.2  2014/12/05 09:58:46  rudahl
 *	no differences between DragonProf and OpenDragon
 *
 *	Revision 1.1  2005/03/19 06:25:44  rudahl
 *	CVS moved from windu; maybe some history lost
 *
 *	Revision 1.2  1999/10/04 12:55:49  rudahl
 *	changed ERROR etc to STAT_ERROR
 *	
 *	Revision 1.1  1999/03/11 02:33:28  rudahl
 *	for some reason not added initially; was on R: not J:
 *
 *
 *****************************************************************
 *
 *    error values for DRAGON utilities toolkit
 *
 *    All error values are negative integers.
 *
 *    The API for the toolkit users is strictly ANSI C.
 *
 *	Revision history
 *		
 * 1.0	6/30/92 ktr	created for DRAGON 3.05 and DRAGON Professional
 * 1.1	11/15/93 ktr	updated for 4.0; fixed DTKE_FILExxxx values
 *	9/12/99 ktr	changed ERROR, etc to STAT_ERROR
 */

#ifndef TOOLERR_H
#define TOOLERR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef STATS_H		/* symbols for serious errors */
#define	STAT_ERROR 7
#define STAT_SERIOUS 8	/* user should exit ASAP */
#define	STAT_FATAL 9		/* try to exit */
#endif
	/* toolkit errors */
#define DTKE_OK 0
#define	DTKE_FILEREADBADMODE -1024 /* F_RSF_BADSMODE */
#define	DTKE_FILEOPEN -1025	/* F_RSF_OPEN	if not found */
#define DTKE_FILESEEK -1026	/* F_RSF_SEEK	if seek error */
#define DTKE_FILEREAD -1027	/* F_RSF_READ 	if read error */
#define	DTKE_FILEWRITEBADMODE -1028 /* F_WSF_BADSMODE	*/
#define DTKE_FILECREATE -1029	/* F_WSF_CREATE	0x20L */
#define DTKE_FILEAPPNDOPEN -1030 /* F_WSF_CR_OPEN 0x40L	* couldn't create or open file */
#define DTKE_FILEALREADY -1031 	/* F_WSF_ALREADY 0x80L	* file already exists */
#define DTKE_FILEAPPEND -1032	/* F_WSF_WRITE	0x100L */
#define DTKE_FILEAPPCLOSE -1033	/* F_WSF_CLOSE	0x200L */
#define DTKE_FILEWRTOPEN -1034	/* F_WSFO_OPEN_OFFSET 0x400L * non-zero offset, file doesn't exist */
#define DTKE_FILEWRTCREATE -1035	/* F_WSFO_CREATE 0x800L */
#define DTKE_FILEWRTSEEK -1036	/* F_WSFO_SEEK	0x1000L */
#define DTKE_FILEWRITE -1037	/* F_WSFO_WRITE	0x2000L	 */
#define DTKE_FILEWRTCLOSE -1038 /* F_WSFO_CLOSE	0x4000L */
#define DTKE_FILENOTFOUND -1059
#define DTKE_BADHANDLE -1060
#define DTKE_NOBUF -1061	/*	if required buffer arg not supplied */
#define DTKE_BADFILENAME -1062 	/*	if 'filename' has bad form*/
#define DTKE_NOMEM -1063	/*	failed malloc*/
#define DTKE_FILEOUTPUTGAP -1064 /*	writeline > 1+prevline*/
#define DTKE_IMGLINETOOBIG -1065 /*	img read or write past hdr->lines()*/
#define DTKE_INVALIDHDR -1066 	/*	image header not supplied or invalid*/
#define DTKE_BAD_COMMAND -1067	/* selector not found in table */
#define DTKE_BAD_COMMAND_LINE -1068  /* overrun end of cmd line */
#define DTKE_NO_CFG	-1069	/*	config file not found */
#define DTKE_BADHDR -1070 	/*	header errors*/
#define DTKE_NO_FGATE	-1071	/*	FGATE DLL not found or installed */
#define DTKE_BADLOCALE -1072	/* 	specified locale not available */
#define DTKE_UNKNOWN_MSG -1073	/* 	GetMsg() couldn't find one */

#define DTKE_NO_DGRAPH	-1100	/*	graphics DLL not found or installed */
#define DTKE_GRAF_INIT_ERR -1101 /*	error installing graphics DLL */
#define DTKE_GRAF_NOT_INIT -1102 /*	graphics DLL not yet initialized */
#define DTKE_GRAF_TEXT	-1103	/*	we're in text not graphics mode */
#define DTKE_GRAF_ERR	-1104	/*	unknown graphics error */
#define DTKE_GRAF_OFFSCREEN -1105 /*	doing something that will be invisible */
#define DTKE_GRAF_BAD_MODE -1106 /* 	mode setting to invalid mode */

#define DTKE_NOT_DRAGON_IMG  -1210  /* file spec'fd not a DRAGON image */
#define DTKE_BADIMG -1211           /* invalid image buffer index  */
#define DTKE_OUTRANGE -1212         /* integer param is out of valid range */
                                    /* too large or negative. */  
#define DTKE_BADDIM -1213           /* illegal or invalid image dimensions */
#define DTKE_BADLINE -1214          /* illegal line number */
#define DTKE_BADPIX -1215           /* illegal pixel number */
#define DTKE_VMERR_INIT -1216       /* virtual memory access error - in */ 
#define DTKE_VMERR_READ -1217       /* initializing,reading or writing  */
#define DTKE_VMERR_WRITE -1218       /* initializing,reading or writing  */
#define DTKE_NOHDR -1219            /* image structure has no header block */
                                    /* allocated or associated with it.  */
#define DTKE_IMGNOTOPEN -1220       /* image memory buffer not yet init'ized */
#define DTKE_FILE_CLIPPED 1         /* warning only - file has more data than */
                                    /* will fit in image memory buffer */ 
#define DTKE_OPEN_ERR -1221         /* error opening a file for loading */
#define DTKE_NOIMGDATA -1222        /* attempt to save a memory buffer that */
                                    /* does not hold any image data */
#define DTKE_HDR_WRITE -1223        /* error writing hdr to existing file */
#define DTKE_IMGMEM_BYTEONLY -1224  /* can't load multi-byte image into img mem */

#define DTKE_TOP_ERR -1224

				/* following in OB.H */
#define DTKE_OB_BASE -2048	/*	OB errors = -2048 to -2068 appx*/

#ifdef __cplusplus
    }
#endif


#endif


