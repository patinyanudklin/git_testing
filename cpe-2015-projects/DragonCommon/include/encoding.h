/****************************************************************
 *
 *          ENCODING.H - Encoding class
 *			 and I18N stuff for DRAGON
 *			 K.T. Rudahl
 *
 *          ~~ Copyright 1996-2014 Kurt Rudahl and Sally goldin
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
 *	    ~~ EndC
 ****************************************************************
 *   $Id: encoding.h,v 1.7 2014/04/01 07:24:45 rudahl Exp $
 *   $Log: encoding.h,v $
 *   Revision 1.7  2014/04/01 07:24:45  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.6  2005/02/16 04:17:02  rudahl
 *   adapt to GCC/MINGW differences
 *
 *   Revision 1.5  2005/02/15 21:35:55  rudahl
 *   rev. for 5.5
 *
 *   Revision 1.4  2003/04/30 15:30:50  rudahl
 *   fine tuning
 *
 *   Revision 1.3  2003/04/22 22:39:02  rudahl
 *   final I18n changes
 *
 *   Revision 1.2  2003/04/20 19:29:24  rudahl
 *   make charset inherit from Encoding
 *
 *   Revision 1.1  2003/04/17 23:39:36  rudahl
 *   adding -ENCODING for script files
 *
 *
 ****************************************************************
 *
 *    Modification History
 * 
 * 1.0	4/17/2003 ktr  derived from charset.h by omitting MSWindows specifics
 *		       including all CFont, HFONT stuff
 * 5.5	2005-2-15 ktr	import from Dragon v 5.4.4
 ****************************************************************/

#ifndef ENCODING_H
#define ENCODING_H 1

/************************************************************************
 *
 *	Encoding for I18N
 *
 ************************************************************************/

#define ANSI_SO 0xE
#define ANSI_SI 0xF

#define MAX_OEM_CHAR 256
#define MAX_ANSI_CHAR 256

typedef enum ENCODING_NAME_t
	{ ENC_UTF8,ENC_Cp1252=2,ENC_ISO8859_1,ENC_Cp1250,ENC_ISO8859_2,
	  ENC_Cp1251,ENC_ISO8859_5};

class Encoding : public OB
    {
public:
    Encoding(int iDebug=0,int iTrace=0);
    BOOL Create(BOOL bCountry,const char * czSelector);
	// initialize the Encoding based on the selector string
	// @param	bCountry	TRUE => pczSelector is country abbrev.
	//				(TRUE: default encoding is ISO8859-1)
	//				(FALSE: default encoding is UTF8)
	// @param	pczSelector	name of an encoding unless 'bCountry',
	// 	Errno = -1094 => unknown language or country code

//    void OemToAnsi(char * str);
	//	convert 'str' from DOS to Windows code page
	//	if conversion not initialized, leave unconverted
	//	These fns protect any substring surrounded by
	//	SI/SO, which is assumed to be HTF8 Unicode

//    void AnsiToOem(char * str);
	//	convert 'str' from Windows to DOS code page
	//	if conversion not initialized, leave unconverted

    void strlwr_Ansi(char * str);
	//	convert 'str' in Windows codepage to lowercase

    void Utf8ToAnsi(char * str);
	//	convert 'str' from UTF8 to Windows code page
	//	if conversion not initialized, leave unconverted

    void Utf8ToOem(char * str);
	//	convert 'str' from UTF8 to DOS code page
	//	if conversion not initialized, leave unconverted
	//	This fn preceeds results with SI if any chars > x7F

	//
	// ** following fns meaningful only for 8-bit codepages
	//
protected:
    int wctocp(const wchar_t w, const wchar_t * bzMap);
	//	convert 'w', in WCS-2 Unicode
	//	return 8-bit char; '.' if 'w' not in current cp
	//	meaningful only for 8-bit codepages
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF

public:
    int cptomb(char * mb,const char ch, const size_t mbsize,
	       const wchar_t * bzMap);
	//	convert 'ch', in local code page form, to UFH8 Unicode
	//	return count of chars put into 'mb'
	//	if conversion not initialized, copy 'ch'; return 1
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF. If NULL, assume bzAnsiUnicode 

protected:
    int mbtocp(char * ch,const char * mb, const wchar_t * bzMap);
	//	convert 'ch', in local code page form, from UFH8 Unicode
	//	return count of chars taken from 'mb'
	//	if conversion not initialized, copy 'ch'; return 1
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF

    int cpstombs(char * pmb,const char * pch, const size_t mbsize,
		 const wchar_t * bzMap);
	//	convert 'pch', in local code page form, to UFH8 Unicode
	//	return count of chars put into 'pmb' (max size 'mbsize').
	//	'pmb' will AWAYS be returned null-terminated 
	//	(the null byte is not incl in the returned count)
	//	if conversion not initialized, copy 'pch'; return 1
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF

public:
   int mbstocps(char * pch,const char * pmb,const size_t uchsize,
		    const wchar_t * bzMap);
	//	convert 'pmb', in local code page form, from UTF8 Unicode
	//	'uchsize' is  size of 'pch' buffer
	//	return count of chars taken from 'pmb'
	//	if conversion not initialized, copy 'pmb'
	//	'pch' always null terminated
	//	meaningful only for 8-bit codepages
	//	'pch' and 'pmb' can NOT be the same buffer
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF

//    int mbstocps(char * pch,const char * pmb,const size_t uchsize,
//			const BOOL bMixed, const wchar_t * bzMap);
	//	convert 'pch', in local code page form, from UFH8 Unicode
	//	'uchsize' is  size of 'pch' buffer
	//	if 'bMixed', then convert ONLY substrings surrounded by
	//	  SI/SO pairs (which are removed).
	//	return count of chars taken from 'pmb'
	//	if conversion not initialized, copy 'pmb'
	//	'pch' always null terminated
	//	'pch' and 'pmb' can NOT be the same buffer
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF

public:
    ushort tolower_Ansi(ushort curchar);
//    static void SetDefaultLanguage(const char * czLanguage)
//		{ strcpy_array(s_czDefaultLanguage,czLanguage); } ;

    int GetError() { return m_iErrno; } ;

    ENCODING_NAME_t getEncoding() { return m_uEncoding; } ;

		// return a formatted dump of the class member
    const char * dump(int detail=6, 
		      const char * czArg=NULL) const;

    void Test(const char * str);
	//	fill 'str' with alt rows of UC & lc chars in ANSI seq.

protected:
    BOOL init(ENCODING_NAME_t uEncoding);
	//	return TRUE if OK; else use GetError for details:
	// 	Errno = -1094 => unknown language code

    int m_iErrno;
    ENCODING_NAME_t m_uEncoding;

//    byte * bzOemToAnsi;
//    byte * bzAnsiToOem;
    wchar_t * bzOemUnicode;
    wchar_t * bzAnsiUnicode;
    byte * bzAnsiLowercase;
	// following tables are included only for chars >= 0x80
#ifdef NOMORE
    static byte s_bz852To1250[MAX_OEM_CHAR];
    static byte s_bz1250To852[MAX_ANSI_CHAR];
    static byte s_bz850To1252[MAX_OEM_CHAR];
    static byte s_bz1252To850[MAX_ANSI_CHAR];
#endif
    static wchar_t s_bz1250ToUnicode[MAX_ANSI_CHAR];
    static wchar_t s_bz1251ToUnicode[MAX_ANSI_CHAR];
    static wchar_t s_bz1252ToUnicode[MAX_ANSI_CHAR];
    static wchar_t s_bz850ToUnicode[MAX_ANSI_CHAR];
    static wchar_t s_bz852ToUnicode[MAX_ANSI_CHAR];
    static wchar_t s_bz855ToUnicode[MAX_ANSI_CHAR];
    static byte s_bz1250lowercase[MAX_ANSI_CHAR];
    static byte s_bz1251lowercase[MAX_ANSI_CHAR];
    static byte s_bz1252lowercase[MAX_ANSI_CHAR];
    static char s_czDefaultLanguage[4];	// 2 or 3-letter code from .CFG file
private:
    static Class s_class_Base;
    } ;

#endif
