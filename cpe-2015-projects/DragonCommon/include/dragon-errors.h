/*
 *	filename dragon-errors.h		- 
 *		$Revision: 1.27 $ $Date: 2015/01/21 10:39:37 $	
 *      ~~ Copyright 1988-2014 Kurt Rudahl and Sally Goldin
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
 * $Id: dragon-errors.h,v 1.27 2015/01/21 10:39:37 rudahl Exp $
 * $Log: dragon-errors.h,v $
 * Revision 1.27  2015/01/21 10:39:37  rudahl
 * improving imageReader - 2drag coordination
 *
 * Revision 1.26  2014/12/05 07:10:54  rudahl
 * added -102,-111
 *
 * Revision 1.25  2014/02/22 10:01:03  rudahl
 * added msg 101
 *
 * Revision 1.15.4.1  2014/02/21 07:07:53  rudahl
 * integrated changes from v 6.4, especially new file header fields
 *
 * Revision 1.24  2011/09/02 11:24:40  rudahl
 * added generic OpenCL error
 *
 * Revision 1.23  2011/06/08 02:10:51  rudahl
 * added OVERFLOW error
 *
 * Revision 1.22  2011/02/27 08:26:33  rudahl
 * added -4096
 *
 * Revision 1.21  2011/02/26 06:16:50  rudahl
 * new errors for foreign stuff
 *
 * Revision 1.20  2010/12/05 03:54:12  rudahl
 * added diskfull
 *
 * Revision 1.19  2008/09/27 10:40:34  rudahl
 * added DERR_IPC_DAMAGED
 *
 * Revision 1.18  2008/09/13 10:28:08  rudahl
 * fixed license key removal handling
 *
 * Revision 1.17  2008/08/17 06:04:23  rudahl
 * minor fix
 *
 * Revision 1.16  2007/12/08 06:43:06  rudahl
 * new for fsm
 *
 * Revision 1.15  2005/11/25 12:36:47  rudahl
 * added DB error
 *
 * Revision 1.14  2005/10/21 11:37:01  rudahl
 * added nullptr error
 *
 * Revision 1.13  2005/10/21 10:16:28  rudahl
 * added errors for ipc
 *
 * Revision 1.12  2005/09/24 14:22:25  rudahl
 * added DERR_DB_xxx
 *
 * Revision 1.11  2005/09/12 07:30:41  rudahl
 * fixes re dp.h
 *
 * Revision 1.10  2005/07/03 13:28:56  rudahl
 * improving createImage
 *
 * Revision 1.9  2005/03/31 10:38:00  rudahl
 * added IMAGE_CONFLICT error
 *
 * Revision 1.8  2005/03/19 06:25:44  rudahl
 * CVS moved from windu; maybe some history lost
 *
 * Revision 1.9  2005/03/11 18:06:31  rudahl
 * added DERR_OK, DERR_OP_CONFLICT
 *
 * Revision 1.8  2005/03/11 17:21:10  rudahl
 * added NOT_NEEDED
 *
 * Revision 1.7  2005/03/03 23:11:26  rudahl
 * added TOOSMALL
 *
 * Revision 1.6  2005/02/18 02:49:44  rudahl
 * added INTERRUPTED
 *
 * Revision 1.4  2005/02/15 21:39:43  rudahl
 * added -66
 *
 * Revision 1.3  2005/02/10 04:59:39  rudahl
 * cleaned up tracing and error reporting
 * cleaned up image file writing
 *
 * Revision 1.2  2005/02/07 05:41:08  rudahl
 * added putImageLine fns
 *
 * Revision 1.1  2005/02/03 03:24:00  rudahl
 * work on implementing new create(), getImageLine etc in img class
 * plus beginning of standardized error numbers
 *
 ****************************************************************
 *
 *	defines error values for low-level functions.
 *
 *  per Err-spec.txt, low-level functions (roughly, the ones in
 *  the common libraries) returt errors by returning negative
 *  integers in the range of -50 to -99.
 *
 *  This file lists some popular values, which may be used either
 *  numerically or symbolically.
 * 
****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 * 5.5	2005-02-02 ktr	extracted from various old v 5.4 files
 * 5.7	2005-9-01 ktr	added errors for persistent storage
 *	2005-10-21 ktr	added IPC errors
 * 	2010-12-02 ktr	added DERR_DISK_FULL
 *	2011-02-25 ktr	added errors -100 through -140 for non-Dragon
 *			files. -100 through -119 are fatal
 *			       -120 through -139 are non-fatal
 * 5.14, 6.4	2014-02-21 ktr	added 101
 *****************************************************************/

#if ! defined DRAGONERRORS_H
#define DRAGONERRORS_H

#define DERR_OK			0	/* no error */
/* -10 to -20 special purpose */
#define DERR_IPC_MISMATCH	-10	/* something in IPC out of sync */ 
#define DERR_IPC_UNKNOWN	-11	/* unrecognized IPC command or subcommand */ 
#define DERR_IPC_DAMAGED	-12	/* for some reason, file is damaged */

#define DERR_NOT_NEEDED		-16	/* req. op not needed */
#define STAT_INTERRUPTED	-17	/* equiv to SIGINT */
/* -30 to -39 reserved */
#define DERR_UNSUP_DEPTH 	-40	/* depth (bits/pix) not supported */
#define DERR_UNSUP_BANDCOUNT 	-41	/* specified bands not supported */
#define DERR_UNSUP_RESCOUNT 	-42	/* num of resolutions not supported*/
#define DERR_UNSUP_FORMAT	-43	/* requested format not supported*/
#define DERR_BAD_STATE		-44	/* state machine (e.g.) in invalid state */
#define DERR_ACTION_FAILED	-45	/* state machine error in setting new state */
#define DERR_DISK_FULL		-46	/* not enough disk space */

#define DERR_MEM_NULLPTR	-47	/* found NULL ptr in bad place */
#define DERR_MEM_ALLOC		-48	/* failed memory allocation */
#define DERR_CLASS_UNRELATED	-49	/* returned by OB */
/* file operation errors */
#define DERR_FILE_ACCESS 	-50	/* can't find file */
#define DERR_FILE_OPEN		-51	/* open or create failure */
#define DERR_FILE_SEEK		-52	/* seek failure */
#define DERR_FILE_RW		-53	/* read or write failure */
#define DERR_FILE_CLOSE		-54	/* close failure */
#define DERR_FILE_NULL		-55	/* file supposed to be open, isn't */
#define DERR_FILE_OOB		-56	/* out-of-bounds (e.g. past EOF) */
#define DERR_FILE_ALREADY	-57	/* already exists in context where overwrite not permitted */
#define DERR_FILE_DENY		-58	/* permissions problem */
#define DERR_FILE_BADNAME 	-59	/* bad name */

/* image errors */
#define DERR_IMAGE_UNINIT	-60	/* image completely uninitialized */
#define DERR_IMAGE_UNKNOWN	-61
#define DERR_IMAGE_CORRUPT	-62
#define DERR_IMAGE_TOOBIG	-63
#define DERR_IMAGE_REINIT	-64	/* trying to reinit. an image */
#define DERR_IMAGE_NONAME	-65	/* no filename supplied */
#define DERR_IMAGE_BADSTATE	-66	/* req. op conflicts with Image State*/
#define DERR_IMAGE_TOOSMALL	-67	/* file size too small for some offset or datasize */
#define DERR_IMAGE_NOREAD	-68
#define DERR_IMAGE_NOWRITE	-69
#define DERR_IMAGE_INVALIDOP	-70
#define DERR_HDR_NOSTATS	-71	/* hdr stats not init */
#define DERR_HDR_UNINIT		-72
#define DERR_HDR_WRITE		-73
#define DERR_HDR_READ		-74
#define DERR_HDR_MISMATCH	-75
#define DERR_HDR_BADFIELD	-76	/* using an unused or obsolete field */
#define DERR_HDR_NOHISTO	-77
#define DERR_DATASIZE_ASYNC	-78

#define DERR_OP_CONFLICT	-80	/* two operations conflict */
#define DERR_IMAGE_CONFLICT	-81	/* some image (sizes?, probably) conflict */
#define DERR_OP_FORBIDDEN	-82	/* operation prohibited */
#define DERR_OP_FORBIDDEN_FATAL	-83	/* operation prohibited--exit */
#define DERR_OVERFLOW		-84	/* something overflowed buffer */
#define DERR_DB_OPEN		-85	/* DB create/open failed */
#define DERR_DB_UNKNOWN		-86	/* DB access unknown table, column */
#define DERR_DB_CONFLICT	-87	/* DB or system constraint violation */
#define DERR_DB_SQL		-88	/* SQL error */
#define DERR_DB_NOTFOUND	-89	/* something missing from DB */

/* function call errors */
#define DERR_FN_ARG0		-90	/* error in arg */
#define DERR_FN_ARG1		-91	/* error in arg */
#define DERR_FN_ARG2		-92	/* error in arg */
#define DERR_FN_ARG3		-93	/* error in arg */
#define DERR_FN_ARG4		-94	/* error in arg */
#define DERR_FN_ARG5		-95	/* error in arg */
#define DERR_FN_ARG6		-96	/* error in arg */
#define DERR_FN_ARG7		-97	/* error in arg */
#define DERR_FN_NULL		-98	/* fn ptr NULL */
#define DERR_FN_NOTIMPL		-99	/* fn (c++ method) not implemented */

/* related to non-Dragon files and processes - fatal */
#define DERR_TIFF_NOTHANDLED	-100	/* TIFF file cannot be read */
#define DERR_FGN_NOTHANDLED	-101	/* Foreign format file cannot be read */
#define DERR_FGN_NOTCONVERTED	-102	/* Foreign format file conversion error */
#define DERR_OPENCL_ERROR	-110	/* OpenCL error */
#define DERR_SPAWN_ERROR	-111	/* Error spawning command */

/* related to non-Dragon files and processes - nonfatal */
#define DERR_NON_FATAL		-120	/* generic non-fatal error */
#define DERR_UNKNOWN_GEOREF	-121	/* georeferencing type has unknowns */

/* add this to error numbers to indicate already processed */
#define DERR_ALREADY_PROCESSED	-4096

#define ERROR_MESSAGES \
	"OK","","","","", \
	"","","","","", \
	"DERR_IPC_MISMATCH: something in IPC out of sync", \
	"DERR_IPC_UNKNOWN: unrecognized IPC command or subcommand", \
	"DERR_IPC_DAMAGED: for some reason, file is damaged", \
	"","", \
	"","DERR_NOT_NEEDED: req. op not needed", \
	"STAT_INTERRUPTED=SIGINT: cancel requested", \
	"","", \
	"","","","","", \
	"","","","","", \
	"","","","","", \
	"","","","","", \
	"DERR_UNSUP_DEPTH: depth (bits/pix) not supported",	/* -40 */ \
	"DERR_UNSUP_BANDCOUNT: spacified bands not supported", \
	"DERR_UNSUP_RESCOUNT: num of resolutions not supported", \
	"DERR_UNSUP_FORMAT: requested format not supported", \
	"DERR_BAD_STATE: state machine (e.g.) in invalid state",\
	"DERR_ACTION_FAILED: state machine error in setting new state", /* 45 */\
	"DERR_DISK_FULL: not enough disk space", \
	"DERR_MEM_NULLPTR: found NULL ptr in bad place", \
	"DERR_MEM_ALLOC: failed memory allocation", \
	"DERR_CLASS_UNRELATED: returned by OB",			/* -49 */ \
		/* file operation errors */ \
	"DERR_FILE_ACCESS: can't find file ", 			/* -50 */ \
	"DERR_FILE_OPEN: open or create failure ", \
	"DERR_FILE_SEEK: seek failure ", \
	"DERR_FILE_RW: read or write failure ", \
	"DERR_FILE_CLOSE: close failure ", \
	"DERR_FILE_NULL: file supposed to be open, isn't ", 	/* -55 */ \
	"DERR_FILE_OOB: out-of-bounds (e.g. past EOF) ", \
	"DERR_FILE_ALREADY: already exists in context where overwrite not permitted ", \
	"DERR_FILE_DENY: permissions problem ", \
	"DERR_FILE_BADNAME: bad name ", \
	    /* image errors */ \
	"DERR_IMAGE_UNINIT: image completely uninitialized ",	/* -60 */ \
	"DERR_IMAGE_UNKNOWN: ",\
	"DERR_IMAGE_CORRUPT: ", \
	"DERR_IMAGE_TOOBIG: ", \
	"DERR_IMAGE_REINIT: trying to reinit. an image ", \
	"DERR_IMAGE_NONAME: no filename supplied ", 		/* -65 */\
	"DERR_IMAGE_BADSTATE: ", \
	"DERR_IMAGE_TOOSMALL: file size too small for some offset or lines/pixels ", \
	"DERR_IMAGE_NOREAD: ", \
	"DERR_IMAGE_NOWRITE: ", \
	"DERR_IMAGE_INVALIDOP: ",				/* -70 */ \
	"DERR_HDR_NOSTATS: hdr stats not init ", \
	"DERR_HDR_UNINIT: ", \
	"DERR_HDR_WRITE: ", \
	"DERR_HDR_READ: ", \
	"DERR_HDR_MISMATCH: ",					/* -75 */ \
	"DERR_HDR_BADFIELD: using an unused or obsolete field", \
	"DERR_HDR_NOHISTO: histogram not initialized", \
	"DERR_DATASIZE_ASYNC: datasize or packing inconsistent","", \
	"DERR_OP_CONFLICT: two operations conflict", 		/* -80 */ \
	"DERR_IMAGE_CONFLICT: some image (sizes?, probably) conflict", \
        "DERR_OP_FORBIDDEN: operation prohibited", \
        "DERR_OP_FORBIDDEN_FATAL: operation prohibited - exiting", \
	"DERR_OVERFLOW: something overflowed buffer", \
	"DERR_DB_OPEN: DB create/open failed", \
	"DERR_DB_UNKNOWN: DB access unknown table, column", \
	"DERR_DB_CONFLICT: DB or system constraint violation", \
	"DERR_DB_SQL: SQL error", \
	"DERR_DB_NOTFOUND: something missing from DB", \
		/* function call errors */ \
	"DERR_FN_ARG0: error in first argument",		/* -90 */\
	"DERR_FN_ARG1: error in secomd argument", \
	"DERR_FN_ARG2: error in arg 3", \
	"DERR_FN_ARG3: error in arg 4", \
	"DERR_FN_ARG4: error in arg 5", \
	"DERR_FN_ARG5: error in arg 6", \
	"DERR_FN_ARG6: error in arg 7", \
	"DERR_FN_ARG7: error in arg 8", \
	"DERR_FN_NULL: function pointer null ", \
	"DERR_FN_NOTIMPL: function or c++ method not implemented ", /* -99 */\
	"DERR_TIFF_NOTHANDLED :TIFF file cannot be read", /* 100 */ \
	"DERR_FGN_NOTHANDLED: Foreign format file cannot be read", \
	"DERR_FGN_NOTCONVERTED: Foreign format file conversion error", \
	"","",\
	"","","","","", \
	"DERR_OPENCL_ERROR: OpenCL error ", /* -110 */ \
	"DERR_SPAWN_ERROR: Error spawning command" , \
	"","","", \
	"","","","","", \
	"DERR_NON_FATAL: generic non-fatal error", /* -120 */ \
	"DERR_UNKNOWN_GEOREF: georeferencing has unknowns", \
	"","","",\
	"","","","","", \
	"","","","","", \
	"","","","",""


#ifdef __cplusplus
extern "C"
#endif

	/* return an English text string describing iErrno */
const char * dragonErrorMessage(int iErrno);

#endif /* DRAGONERRORS_H */

