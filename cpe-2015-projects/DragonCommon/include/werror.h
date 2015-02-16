/****************************************************************
 *	WERROR.H- ultimate error handler ueh()
 *
 *	~~ Copyright 1992-2014 Kurt Rudahl and Sally goldin
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
 *	$Id: werror.h,v 1.6 2014/12/05 09:58:46 rudahl Exp $
 *	$Log: werror.h,v $
 *	Revision 1.6  2014/12/05 09:58:46  rudahl
 *	no differences between DragonProf and OpenDragon
 *
 *	Revision 1.5  2005/02/23 20:36:15  rudahl
 *	revising grsproc1 for new Image usages
 *
 *	Revision 1.4  2002/04/09 21:32:36  rudahl
 *	adapt for long filenames
 *	
 *	Revision 1.3  2001/08/16 15:55:40  rudahl
 *	fixup fort win32
 *	
 *	Revision 1.2  2000/06/17 21:09:24  rudahl
 *	changed ueh errnum type to signed
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:18  rudahl
 *	first checkin of only SOME common dirs
 *	
 * Revision 4.4  1997/09/12  13:20:14  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1997/09/12  13:20:14  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.2  1995/12/18  11:52:38  lcd
 * checkin for class class49
 * 
 * Revision 4.1  1994/07/20  09:03:36  tower
 * Released with DRAGON 4.10 12/94
 * 
 * Revision 4.0.1.7  1993/02/13  15:55:28  tower
 * final for DRAGON 4.0G.
 * general changes: MSC v 6 adaptations, graphics screens to 1280 pix.
 * 
 * Revision 4.0  1993/02/13  15:55:28  tower
 * Final for DRAGON Release 4.0
 * 
 * Revision 1.2  93/02/13  15:55:24  tower
 * added RegisterMsgfile(), RegisterCfgFile
 * 
 * Revision 1.1  93/01/30  16:16:43  tower
 * Initial revision
 * 
 *
 *****************************************************************
 *	This file implements an easy-to-use but very general
 *	error handler and reported called ueh(). It can 
 *	optionally handle errstat_set(), UI-based error windows,
 *	and i18n'd messages.
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 *	12/12/95 ktr	adapt to Watcom 10.0 & MSC v 8
 * 5.0	6/22/97 ktr	changed variable 'errno' to 'errnum' for WATCOM
 *      6/17/00 ktr     changed errnum arg of ueh to signed
 *                       and copied documentation to this file
 * 5.5	2005-2-23 ktr	imported from Dragon v 5.4
 *****************************************************************/

#ifndef WERROR_H
#define WERROR_H

#ifdef __cplusplus
extern "C" {
#endif

/* __MSC__ is in dtypes.h */
#if defined __MSC__ && !defined MSC
#define MSC 1
#endif

#if defined MSC || defined __WATCOMC__
#define _CDECLP __cdecl *
#else
#define _CDECLP *
#endif

	/*	function to report, to user and to system, an error condition.
	 *	If 'report' (e.g. errstat_set) and level>=NOTIFY, report to
	 *		system using 'report' fn, 'module','level','errbits',
	 *		and msg generated by 'format' (see below). This never
	 *		uses a substitute string from msg data file.
	 *	If 'display' (e.g.          ) display a message generated by
	 *		'format' (see below). This uses a substitute string
	 *		if available.
	 *	If 'level' == FATAL, do exit(1);
	 *	   WARNING - this will probably hang the system if used 
	 *		within a TSR
	 *	Return 'errnum'.
	 *	'format' is a string of chars which determine, in order, what
	 *		the following args are and what to do with them:
	 *	    'p' => arg is a near pointer to free()
	 *	    'P' => arg is a  pointer to dos_free()
	 *	xx    'F' => arg is pernament filename for msg file
	 *	xx    'f' => arg is temp (this time only) filename for msg file
	 *	7/3/94 ktr	changed ueh() so that:
	 *	      'f' in format specifies msg file for this op only
	 *		  (same as previously, but may not work)
	 *  		  the temporary message file is checked to exist.
	 *	      'F' is obsolete, but for compat., does same as 'f'
	 *		  neither -> use std msg file, and DO NOT verify exists.
	 *		  (this is normal for DRAGON using FGATE).
	 *	   the remaining format chars are used to build up a message
	 *	   string for report and POSSIBLY for display (if no 'mM').
	 *	    'i' => arg is an integer to be appended (as string) to
	 *		message being built.
	 *	    'I' => arg is a long to be appended (as string) to
	 *		message being built.
	 *	    's' => arg is a string to be appended to message being built.
	 *	   if a translatable string is to be displayed, format MUST
	 *	    include an 'mM' pair specifying message number and default 
	 *	    message. All remaining args are passed to d_Format.
	 *	    if 'M' but not 'm', no file access is attempted.
	 *	    'M' => arg is a message string as described in dtk_ShowMsg
	 *		documentation, which will be replaced by message
	 *		from data file, if available.
	 *	    'm' => arg is a uint msgno equivalent to 'M'
	 */
#if defined MSC && !defined _WIN32
int ueh(void (_CDECLP)(const uint,const UINT32,const uint,const char *),
	void (_CDECLP)(const char *),const uint module,const ulong errbits,
	const uint level,const int errnum,const char * format,...);
#elif defined __WATCOMC__
int ueh(void (_CDECLP report)(const uint,const UINT32,const uint,const char *),
	void (_CDECLP display)(const char *),const uint module,const ulong errbits,
	const uint level,const int errnum,const char * format,...);
#else
int ueh(void (* report)(const uint,const UINT32,const uint,const char *),
	void (* display)(const char *),const uint module,const ulong errbits,
	const uint level,const int errnum,const char * format,...);
#endif

char * d_Format(char * buf,const int ernum,const char * msg,va_list args);

	/*	Specify the name of the file to be the source of
	 *	messages supplied by GetMsg(). 
	 *	@param  'name' may include a drive, path, and/or extension 
	 *              and has no size limit.
	 *	        If the path or drive is not supplied, the current 
	 *	        directory or drive is assumed. 
	 *
	 *	@return 0, 
	 *              or F_RSF_OPEN code if file specified and doesn't exist
	 */
int RegisterMsgFile(const char * name);
int RegisterCfgFile(const char * name);

#ifdef __cplusplus
   }
#endif

#endif
