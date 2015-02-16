/*
 *	filename I18N.H
 *		$Revision: 1.10 $ $Date: 2014/12/05 10:38:00 $
 *      ~~ Copyright 1994-2014 by Kurt Rudahl and Sally Goldin
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *	~~ EndC
 ****************************************************************
 *   $Id: i18n.h,v 1.10 2014/12/05 10:38:00 rudahl Exp $
 *   $Log: i18n.h,v $
 *   Revision 1.10  2014/12/05 10:38:00  rudahl
 *   no significant differences between DragonProf and OpenDragon
 *
 *   Revision 1.9  2010/11/15 13:12:16  rudahl
 *   fix for linux
 *
 *   Revision 1.8  2010/10/28 06:53:44  rudahl
 *   msvc2010 doesn't like wcslen decl
 *
 *   Revision 1.7  2005/01/27 23:03:15  rudahl
 *   adapt for 64-bit
 *
 *   Revision 1.6  2004/12/28 12:17:09  rudahl
 *   fixed problem reading UTF-8 from header
 *
 *   Revision 1.5  2004/11/30 03:38:02  rudahl
 *   adapt to Mingw 3.4.2 compiler
 *
 *   Revision 1.4  2003/04/22 22:37:37  rudahl
 *   final I18n changes
 *
 *   Revision 1.3  2003/04/21 17:35:26  rudahl
 *   fixup and generalize uni_mbstocps
 *
 *   Revision 1.2  2002/05/08 00:10:19  rudahl
 *   added wcslen
 *
 *   Revision 1.1.1.1  1999/03/11 00:35:18  rudahl
 *   first checkin of only SOME common dirs
 *
 * Revision 1.3  1995/01/22  14:08:54  tower
 * checkin for class class5_0
 * 
 * Revision 1.1  1994/12/27  18:08:27  tower
 * Initial revision
 * 
 *
 ****************************************************************
 *
 *	Defines headers for use with I18N.C, for Unicode char conversions.
 *	Requires dtypes.h
 *
 *	Revision History
 * 1.0	10/21/94 ktr	Created
 *	1/22/95		minor syntactic fix for MSC8
 * 5.0	6/12/98 ktr	added fns to cvt between UTF-8 and UCS-2 unicode,
 *			and adapted mbstowcs accordingly
 * 5.4 	11/29/2004 ktr	adapt for Mingw GCC
 *	12/27/2004 ktr	added mbslen
 */
#ifndef I18N_H
#define I18N_H

#define WIDEESC 'u'
#define NARROWESC 'x'
#define STD_ESC '\\'
#ifdef MB_CUR_MAX
#undef MB_CUR_MAX
#endif
#define MB_CUR_MAX 6	/* must be at least 6 */

#ifdef __cplusplus
extern "C" {
#endif

	/* return the number of characters (wchars) in pStr
	 */
#if defined __MINGCC__
size_t grs_wcslen(const UNICODE_WCHAR * pStr);
#else
#if defined __GCC__
size_t wcslen(const UNICODE_WCHAR * pStr);
#else
  // msvc2010 conflicts with this declaration
  //size_t wcslen(const UNICODE_WCHAR * pStr);
#endif
#endif

	/*	return the number of initial valid multibyte chars
	 *	in 'mbstr'.
	 *	@param mbstr	null-terminated string of possibly 
	 *			multibyte chars, possibly including
	 *			wide or narrow escape chars.
	 *	@param bQuoted	if TRUE, and if mbstr begins with a quote ("),
	 *			then terminate count with the 
	 *			trailing matching quote
	 *			and return the count less the quotes
	 *	@param xlate	if non-NULL and current char is not a 
	 *			wide escape, assume 'mbchar' contains either 
	 *			ASCII with narrow escapes 
	 *			or some code page chars which 'xlate' 
	 *			translates to WCS2.
	 *	@return		number of characters before first invalid
	 *			character.
	 */
size_t mbslen(const char * mbstr,
	      BOOL bQuoted,
	      int (* xlate)(UNICODE_WCHAR * pwChar,const int));

	/*	convert 'mbchar' to 2-byte wide char at 'wchar', examining
	 *	at most 'count' chars in 'mbchar'.
	 *	if 'mbchar' points to a wide escape sequences, 
	 *		convert and return it without translation.
	 *	else if 'xlate' non-NULL, assume 'mbchar' contains either 
	 *		ASCII with narrow escapes or some code page chars,
	 *		and that 'xlate' translates those to WCS2
	 *	else assume 'mbchar' points to UTF8.
	 *
	 *	If 'wchar'==NULL, convert but don't store
	 *	   unconvertable chars replaced by blank (x0020)
	 *	Return 0 if 'mbchar' is NULL or empty,
	 *		-1 if invalid 'mbchar' string
	 *		else # chars of 'mbchar' which were used
	 */
int uni_mbtowc(UNICODE_WCHAR * wchar, const char * mbchar,
	       const size_t count,
	       int (* xlate)(UNICODE_WCHAR * pwChar,const int));

	/*	convert 'mbstr' to string of 2-byte wide chars at 'wstr',
	 *	examining at most 'icount' chars in 'mbstr'.
	 *	and writing at most 'osize' chars to 'wstr'.
	 *	A double NULL is appended ONLY if NULL on input (?).
	 *
	 *	for each single or multibyte subsequence 'mbchar' in 'mbstr':
	 *	  if 'mbchar' points to a wide escape sequences, 
	 *		convert and return it without translation.
	 *	  else if 'xlate' non-NULL, assume 'mbchar' contains either 
	 *		ASCII with narrow escapes or some code page chars,
	 *		and that 'xlate' translates those to WCS2
	 *	  else assume 'mbchar' points to UTF8.
	 *
	 *	If 'wstr'==NULL, convert but don't store
	 *	If pOcount != NULL, set it to count of resulting WCHARS
	 *	Return 0 if 'mbstr' is NULL or empty,
	 *		-1 if invalid 'mbstr' string
	 *		else # chars of 'mbstr' which were used
	 *		if (return == count) result is NOT NULL terminated.
	 */
int uni_mbstowcs(UNICODE_WCHAR * wstr, const char * mbstr,
	const size_t icount,const size_t osize, size_t * pOcount,
	int (* xlate)(UNICODE_WCHAR * pwChar,const int));

int uni_wctomb(char * mbchar, const UNICODE_WCHAR wchar,const size_t,
	int (* xlate)(char * mbchar,const UNICODE_WCHAR,const size_t));
int uni_wcstombs(char * mbstr,const UNICODE_WCHAR * wstr,const size_t count,
	int (* xlate)(char * mbchar,const UNICODE_WCHAR,const size_t));
	/*	convert 'wstr' to string of multibyte chars at 'mbstr',
	 *	writing at most 'count' chars to 'mbstr'.
	 *	('count' doesn't incl TWO NULL bytes)
	 *	A (wide) NULL is appended ONLY if NULL on input (?).
	 *	If 'mbstr'==NULL, convert but don't store
	 *	If wide chars in 'wstr' are ASCII, value is same
	 *	else if 'xlate' is non-NULL, use it to create narrow esc. seq.
	 *	 ('xlate' returns -1 if unable to convert)
	 *	else create wide-escape seq.
	 *	Return 0 if 'wstr' is NULL or empty,
	 *		else # chars of 'mbchar' which were written
	 *		if (return == count) result is NOT NULL terminated.
	 */
int cp_UCS2toUTF8(char * mbchar,const UNICODE_WCHAR wChar,
		const size_t uBufSpace);
	/* convert 16-bit (UCS-2) Unicode to multibyte UTF-8 form,
	 * provided that there is room for it.
	 * Always append '\0' if it will fit
	 * Return #bytes added to 'mbchar' if OK else -1
	 */

int cp_UTF8toUCS2(UNICODE_WCHAR  * pwChar,const byte * mbchar);
//int cp_UTF8toUCS2(UNICODE_WCHAR * pwChar,const ulong mbchar);
	/* convert multibyte UTF-8 Unicode to 16-bit (UCS-2) form,
	 * Return #bytes used from 'mbchar' if OK else -1
	 */

int check_UTF8_char(const ulong mbchar);
	/* check whether mbchar is a valid UTF-8 char 
	 * Return # bytes consumed if OK else 0
	 */

int check_UTF8_string(const byte * pMbchar);
	/* check whether pMbchar is a valid UTF-8 string
	 * Return byte number where error occurs, or -1 if OK
	 */

#ifdef __cplusplus
    }
#endif
#endif
