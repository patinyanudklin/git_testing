#include "drelease.h"
extern "C" const char ENCODING_ID[] 
    = "\0@(#) " __FILE__ " $Revision: 1.15 $$Date: 2014/12/05 14:24:30 $";
/****************************************************************
 *
 *          ENCODING - for I18N
 *			 K.T. Rudahl
 *
 *          ~~ Copyright 1996-2014 Kurt Rudahl and Sally Goldin
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
 ***************************************************************
 *
 *   $Id: encoding.cpp,v 1.15 2014/12/05 14:24:30 rudahl Exp $
 *   $Log: encoding.cpp,v $
 *   Revision 1.15  2014/12/05 14:24:30  rudahl
 *   reconciled DragonProfessional with OpenDragon
 *
 *   Revision 1.14  2008/08/25 12:27:05  rudahl
 *   updating
 *
 *   Revision 1.13  2005/02/17 18:59:58  san
 *   eror in dump() proto
 *
 *   Revision 1.12  2005/02/16 04:15:31  rudahl
 *   adapt to GCC/MINGW differences
 *
 *   Revision 1.11  2005/02/16 00:50:06  goldin
 *   Changes to be able to compile under MingW
 *
 *   Revision 1.10  2005/02/15 21:31:39  rudahl
 *   rev. for 5.5
 *
 *   Revision 1.9  2004/12/23 11:53:03  rudahl
 *   adapt for linux
 *
 *   Revision 1.7  2004/12/04 09:05:47  rudahl
 *   fix lint-ish probs, cvt for mingw
 *
 *   Revision 1.6  2004/12/04 08:43:41  rudahl
 *   fixup for correct encoding compile
 *
 *   Revision 1.5  2003/04/30 15:31:30  rudahl
 *   added support for OEM codepages
 *
 *   Revision 1.4  2003/04/21 17:35:05  rudahl
 *   fixup and generalize uni_mbstocps
 *
 *   Revision 1.3  2003/04/20 19:28:44  rudahl
 *   make charset inherit from Encoding
 *
 *   Revision 1.2  2003/04/18 22:23:34  rudahl
 *   bug fix in Create
 *
 *   Revision 1.1  2003/04/17 23:40:18  rudahl
 *   adding -ENCODING for script files
 *
****************************************************************/
/**/
/*    Modification History
 * 
 * 1.0	4/17/2003 ktr  derived from charset.cpp by omitting MSWindows specifics
 *		       including all CFont, HFONT stuff
 * 5.4	12/21/2004 ktr	adapt for linux
 * 5.5	2005-2-15 ktr	import from Dragon v 5.4.4
 */	    

/**/
#include <stdarg.h>
#include <stddef.h>	// offsetof
#if defined __GCC__ || defined __MINGCC__
#include <time.h>
#include <sys/stat.h>
#else
#include <dos.h>	/* needed for files.h */
#include <io.h>   	// for _access 
#include <direct.h>	// for getcwd
#include <sys\stat.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>	// for is..()
#include <locale.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "i18n.h"
#include "ob.h"

#include "dragonOb.h"
#include "logger.h"

#include "files.h"
#include "i18n.h"

#include "1252-uni.h"
#include "1251-uni.h" // cyrillic
#include "1250-uni.h"

#include "850-uni.h"
#include "855-uni.h" // cyrillic
#include "852-uni.h"

#include "encoding.h"

/************************************************************************
 *
 *	Encoding for I18N
 *
 ************************************************************************/

static const char * s_czCountryNames[] 
	= { "BA","EN","ES","FR",
	    "IT","CZ","RU" };
static ENCODING_NAME_t s_uCountryDefaultEncodings[] 
	= { ENC_ISO8859_1,ENC_ISO8859_1,ENC_ISO8859_1,ENC_ISO8859_1,
	    ENC_ISO8859_1,ENC_ISO8859_2,ENC_ISO8859_5};
static const char * s_czEncodings[]
	= { "UTF8","xxx","Cp1252","ISO8859-1","Cp1250","ISO8859-2",
	    "Cp1251","ISO-8859-5"};


#ifdef NOMORE
byte Encoding::s_bz850To1252[MAX_OEM_CHAR] = {CP_0850_TO_CP_1252_TAB};
byte Encoding::s_bz1252To850[MAX_ANSI_CHAR] = {CP_1252_TO_CP_0850_TAB};
#endif
byte Encoding::s_bz1252lowercase[MAX_ANSI_CHAR]
    =	{	/* 0 => no change; 1 => 0x20 OR char; else explicit value */
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,154,0,156,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,255,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,1,1,1,1,1,1,0, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	};

#ifdef NOMORE
byte Encoding::s_bz852To1250[MAX_OEM_CHAR] = {CP_0852_TO_CP_1250_TAB};
byte Encoding::s_bz1250To852[MAX_ANSI_CHAR] = {CP_1250_TO_CP_0852_TAB};
#endif
byte Encoding::s_bz1250lowercase[MAX_ANSI_CHAR]
    =	{	/* 0 => no change; 1 => 0x20 OR char; else explicit value */
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,0,0,0,0,0,0,0, 0,0,0x9A,0,0x9C,0x9D,0x9E,0x9F,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0xB3,0,0xB9,0,0, 0,0,0xBA,0,0,0,0,0xBF,
	0,0,0,0,0,0,0,0, 0,0,0,0,0xBE,0,0,0,

	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,0, 1,1,1,1,1,1,1,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	};

//byte Encoding::s_bz855To1251[MAX_OEM_CHAR] = {CP_0855_TO_CP_1251_TAB};
//byte Encoding::s_bz1251To855[MAX_ANSI_CHAR] = {CP_1251_TO_CP_0855_TAB};
byte Encoding::s_bz1251lowercase[MAX_ANSI_CHAR]
    =	{	/* 0 => no change; 1 => 0x20 OR char; else explicit value */
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

	0x90,0x83,0,0,0,0,0,0,    0,0,0x9A,0,0x9C,0x9D,0x9E,0x9F,
	0,0,0,0,0,0,0,0,          0,0,0,0,0,0,0,0,
	0,0xA2,0,0xBC,0,0xB4,0,0, 0xB8,0,0xBA,0,0,0,0,0xBF,
	0,0,0xB3,0,0,0,0,0,       0,0,0,0,0,0xBE,0,0,

	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
	};

wchar_t Encoding::s_bz1250ToUnicode[MAX_ANSI_CHAR] = {CP_1250_TO_UNI_TAB};
wchar_t Encoding::s_bz1251ToUnicode[MAX_ANSI_CHAR] = {CP_1251_TO_UNI_TAB};
wchar_t Encoding::s_bz1252ToUnicode[MAX_ANSI_CHAR] = {CP_1252_TO_UNI_TAB};

wchar_t Encoding::s_bz852ToUnicode[MAX_ANSI_CHAR] = {CP_0852_TO_UNI_TAB};
wchar_t Encoding::s_bz855ToUnicode[MAX_ANSI_CHAR] = {CP_855_TO_UNI_TAB};
wchar_t Encoding::s_bz850ToUnicode[MAX_ANSI_CHAR] = {CP_0850_TO_UNI_TAB};

#define DEFAULT_COUNTRY "EN"
#define DEFAULT_ENCODING ENC_UTF8

Class Encoding::s_class_Base("Encoding","Class for character encodings");

Encoding::Encoding(int iDebug, int iTrace)
	//	each Encoding has a particular size
	// 	not actually using this info yet.
    {
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    if (iDebug > m_iDebug)  // OB::OB may have already set these two
	m_iDebug = iDebug;
    if (iTrace > m_iTrace)
	m_iTrace = iTrace;
    m_iErrno = 0;
    bzOemUnicode = NULL;
    bzAnsiUnicode = NULL;
    bzAnsiLowercase = NULL;
    m_uEncoding = ENC_UTF8;
    }

BOOL Encoding::init(ENCODING_NAME_t uEncoding)
	//	return TRUE if OK; else use GetError for details:
	// 	Errno = -1094 => unknown language code
    {
    BOOL retval = TRUE;
    logTrace(">Encoding::init (en) encoding=%d='%s'",
	     uEncoding,s_czEncodings[uEncoding]);
    switch(uEncoding)
        {
	case ENC_ISO8859_1:
	case ENC_Cp1252:	/* W. Europe - these two not exactly same */
		bzAnsiUnicode = s_bz1252ToUnicode;
		bzOemUnicode = s_bz850ToUnicode;
		bzAnsiLowercase = s_bz1252lowercase;
		break;
	case ENC_ISO8859_2:
	case ENC_Cp1250:	/* E. Europe - these two not exactly same */
		bzAnsiUnicode = s_bz1250ToUnicode;
		bzOemUnicode = s_bz852ToUnicode;
		bzAnsiLowercase = s_bz1250lowercase;
		break;
	case ENC_ISO8859_5:
	case ENC_Cp1251:	/* Cyrillic - these two not exactly same */
		bzAnsiUnicode = s_bz1251ToUnicode;
		bzOemUnicode = s_bz855ToUnicode;
		bzAnsiLowercase = s_bz1251lowercase;
		break;
	case ENC_UTF8:
		bzAnsiUnicode = NULL;
		bzAnsiLowercase = NULL;
		break;
	default:
		m_iErrno = 1294;
		retval = FALSE;
		break;
	}
    if (retval)
	m_uEncoding = uEncoding;
    logTrace(">Encoding::init (ex) returns OK=%s, errno=%d",
	     YESNO(retval),m_iErrno);
    return retval;
    }

BOOL Encoding::Create(BOOL bCountry,const char * czSelector)
	// initialize the Encoding based on the selector string
	// @param	bCountry	TRUE => pczSelector is country abbrev.
	//				(TRUE: default encoding is ISO8859-1)
	//				(FALSE: default encoding is UTF8)
	// @param	pczSelector	name of an encoding unless 'bCountry',
	// 	Errno = -1094 => unknown language or country code
    {
    BOOL retval = FALSE;
    ENCODING_NAME_t uEncoding = DEFAULT_ENCODING;
    logTrace(">Encoding::Create (en) bcountry=%s selector='%s'",
	     YESNO(bCountry),czSelector);
    if (bCountry)
        {
	uEncoding = ENC_ISO8859_1;
	for (uint i=0; i<AY_COUNT(s_czCountryNames); i++)
	    if (stricmp(s_czCountryNames[i],czSelector) == 0)
	        {
		uEncoding = s_uCountryDefaultEncodings[i]; 
		break;
		}
	}
    else
        {
	const char * pSel = czSelector;
	while ((pSel != NULL) && (*pSel != '\0') && isAspace(*pSel))
	    pSel++;
	for (uint i=0; i<AY_COUNT(s_czEncodings); i++)
	    if (stricmp(s_czEncodings[i],pSel) == 0)
	        {
		uEncoding = (ENCODING_NAME_t)i;
		break;
		}
	}
    if (uEncoding != DEFAULT_ENCODING)
        retval = init(uEncoding);
    else
        m_iErrno = -1094; 
    logTrace(">Encoding::Create (ex) OK=%s errno=%d",YESNO(retval),m_iErrno);
    return retval;
    }

#ifdef NOORE
void Encoding::Test(const char * str, const size_t uStrsize) 
	//	fill 'str' with alt rows of UC & lc chars in ANSI seq.
    {
    char cbuf[256];
    size_t chr=0;
    memset(cbuf,0,sizeof(cbuf));
    for (chr=0; chr < 256; chr++)
	{
	cbuf[2 * (chr & 0x1F)] = (chr) ? chr : ' ';
	cbuf[2 * (chr & 0x1F) + 1] = (chr) ? (char) tolower_Ansi(chr) : ' ';
	if ((chr & 0x1F) == 0x1F) 
	    {
	    strcat(cbuf,"\r\n");
	    strncat(str,cbuf,uStrsize - strlen(str) - 1);
	    memset(cbuf,0,sizeof(cbuf));
	    }
	}
    }
#endif

	//	convert 'str' from UTF8 to Windows code page
	//	if conversion not initialized, leave unconverted
void Encoding::Utf8ToAnsi(char * str) 
    {
    if (str == NULL)
	return;
    if (bzAnsiUnicode == NULL)
	return;
    size_t uStrSz = strlen(str)+1; 
    char * buf = (char *)calloc(uStrSz,1);
    if (buf == NULL)
        return; /* ignore errors */
    mbstocps(buf,str,uStrSz,bzAnsiUnicode);
    strcpy(str,buf);
    free(buf);
    }

/* 	so-called OEM (i.e. DOS code pages) are used in NT for
 * 	filenames. 
 *	Thus, we need to convert FROM 'oem' when displaying a filename
 *	and TO 'oem' when accepting a filename.
 *	All 'oem' strings (i.e. single-byte encoding with characters higher
 *	than x7F) are surrounded by SI/SO.
 *	Presumably fopen() in 'C' requires an oem string, and in
 *	Java, a Unicode string. to be verified.
 */
	//	convert 'str' from UTF8 to DOS code page
	//	if conversion not initialized, leave unconverted
	//	This fn preceeds results with SI if any chars > x7F
void Encoding::Utf8ToOem(char * str) 
    {
    if (str == NULL)
	return;
    if (bzOemUnicode == NULL)
	return;
    BOOL bHiChars = FALSE;
    size_t uStrSz = strlen(str)+3; /* more than big enough */
    for (size_t i=0; i<uStrSz-3; i++)
        if (str[i] > 0x7F)
	    {
	    bHiChars = TRUE;	/* found at least one */
	    break;
	    }
    if (bHiChars) /* else nothing to do */
        {
	char * buf = (char *)calloc(uStrSz,1);
	if (buf == NULL)
	    return; /* ignore errors */
	mbstocps(buf,str,uStrSz,bzOemUnicode);
	str[0] = ANSI_SI;
	strcpy(str+1,buf);
	//	str[strlen(str)] = ANSI_SO;
	free(buf);
	}
    }

#ifdef NOMORE
void Encoding::OemToAnsi(char * str) 
	//	convert 'str' from DOS to Windows code page
	//	if conversion not initialized, leave unconverted
    {
    size_t i;
    if (str == NULL)
	{
	return;
	}
    if (bzOemToAnsi == NULL)
	return;
    int iUnicodeSI = -1;	/* byte index of SI char if any */
    for (i=0; i<strlen(str); i++)
	{
	ushort curchar = str[i];
	if (curchar >= MAX_OEM_CHAR)
	    curchar &= 0xFF;
/* protect any SI/SO substrings, which are UTF8 Unicode */
	if ((iUnicodeSI >= 0) && (curchar == ANSI_SO))
	    {
	    iUnicodeSI = -1;
	    continue;		// end preserving unicode chars
	    }
	if (iUnicodeSI >= 0)
	    continue;		// preserve unicode chars
	if (curchar == ANSI_SI)
	    {
	    iUnicodeSI = i;
	    continue;		// start preserving unicode chars
	    }
	if (curchar < ' ')
	    continue;		// preserve ctrl chars
	str[i] = bzOemToAnsi[curchar]; 
	}
    }
//#endif

//#ifdef NOMORE
void Encoding::AnsiToOem(char * str)
	//	convert 'str' from Windows to DOS code page
	//	if conversion not initialized, leave unconverted
    {
    size_t i;
    if (bzAnsiToOem == NULL)
	return;
    if (str == NULL)
	{
	return;
	}
    for (i=0; i<strlen(str); i++)
	{
	ushort curchar = str[i];
	if (curchar >= MAX_ANSI_CHAR)
	    curchar &= 0xFF;
	if (curchar < ' ')
	    continue;		// preserve ctrl chars
	str[i] = bzAnsiToOem[curchar]; 
	}
    }
#endif /* NOMORE */

int Encoding::cptomb(char * mb,const char ch, const size_t mbsize,
		     const wchar_t * bzMap) 
	//	convert 'ch', in local code page form, to UTF8 Unicode
	//	return count of chars put into 'mb'
	//	if conversion not initialized, copy 'ch'; return 1
	//	meaningful only for 8-bit codepages
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF. If NULL, assume bzAnsiUnicode 
    {
    wchar_t w = 0;
    int retval;
    byte uch = 0xFF & ch;
    const wchar_t * pbzMap = (bzMap == NULL) ? bzAnsiUnicode : bzMap;
    if ((mbsize < 4) || (uch == '\0') || (mb == NULL))
	{
	retval = 0;
	}
    else if (pbzMap == NULL)		// not initialized
	{
	*mb = ch;
	*(mb+1) = '\0';
	retval = 1;
	}
    else
	{
	w = pbzMap[uch];
	retval = cp_UCS2toUTF8(mb,w,mbsize);
	}
    return retval;
    }

int Encoding::cpstombs(char * pmb,const char * pch, const size_t mbsize,
		       const wchar_t * bzMap) 
	//	convert 'pch', in local code page form, to UTF8 Unicode
	//	return count of chars put into 'pmb' (max size 'mbsize').
	//	'pmb' will AWAYS be returned null-terminated 
	//	(the null byte is not incl in the returned count)
	//	if conversion not initialized, copy 'pch'; return 1
	//	meaningful only for 8-bit codepages
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF
    {
    const char * pn = pch;
    size_t uMbNdx = 0;
    *pmb = '\0';
    while ((*pn != '\0') && (uMbNdx < mbsize-1))
	{
	int cnt = cptomb(&pmb[uMbNdx],*pn++,mbsize-uMbNdx-1,bzMap);
	if (cnt > 0)
	    {
	    uMbNdx += cnt;
//	    pbuf += cnt;
	    }
	}
    return uMbNdx;
    }

int Encoding::wctocp(const wchar_t w, const wchar_t * bzMap) 
	//	convert 'w', in WCS-2 Unicode
	//	return 8-bit char; '.' if 'w' not in current cp
	//	meaningful only for 8-bit codepages
    {
    int i = '.';
    if (w < 128)
	i = w;
    else
	for (int j=128; j<256; j++)
	    if (bzMap[j] == w)
		{
		i = j;
		break;
		}
    return i;
    }

int Encoding::mbtocp(char * ch,const char * mb, const wchar_t * bzMap) 
	//	convert 'mb' from UTF8 Unicode to 'ch', in local code page form
	//	return count of chars taken from 'mb'
	//	if conversion not initialized, copy 'ch'; return 1
	//	meaningful only for 8-bit codepages
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF
    {
    int retval;
    //    byte uch = 0xFF & *mb;
    if ((ch == NULL) || (mb == NULL))
	{
	retval = 0;
	}
    else if ((bzMap == NULL)			// not initialized
	    || (((byte)(0xFF & *mb)) < 0x80))	// trivial conversion
	{
	*ch = *mb;
	*(ch+1) = '\0';
	retval = 1;
	}
    else
	{
	UNICODE_WCHAR w = 0;
	retval = cp_UTF8toUCS2(&w,(const byte *)mb);
	if (retval > 0)
	    {
	    *ch = wctocp(w,bzMap);
	    *(ch+1) = '\0';
	    }
	}
    return retval;
    }

int Encoding::mbstocps(char * pch,const char * pmb,
		       const size_t uchsize, const wchar_t * bzMap)
	//	convert 'pmb' from UTF8 Unicode to local code page form.
	//	'uchsize' is  size of 'pch' buffer
	//	return count of chars taken from 'pmb'
	//	if conversion not initialized, copy 'pmb'
	//	'pch' always null terminated
	//	meaningful only for 8-bit codepages
	//	'pch' and 'pmb' can NOT be the same buffer
	//	'bzMap' is a 256-wchar_t array of UCS2 values corresp
	//	to code page values x0-xFF
    {
    size_t uMbNdx = 0;
    size_t uChNdx = 0;
    *pch = '\0';
    while ((pmb[uMbNdx] != '\0') && (uChNdx < uchsize-1))
	{
	int cnt = mbtocp(&pch[uChNdx++],&pmb[uMbNdx],bzMap);
	if (cnt > 0)
	    uMbNdx += cnt;
	}
    return uMbNdx;
    }

#ifdef NOMORE
int Encoding::mbstocps(char * pch,const char * pmb,const size_t uchsize,
			const BOOL bMixed, const wchar_t * bzMap) 
	//	convert 'pmb' from UTF8 Unicode to local code page form.
	//	'uchsize' is  size of 'pch' buffer
	//	return count of chars taken from 'pmb'
	//	if 'bMixed', then convert ONLY substrings surrounded by
	//	  SI/SO pairs (which are removed).
	//	if conversion not initialized, copy 'pch'; return 1
	//	'pch' always null terminated
	//	meaningful only for 8-bit codepages
	//	'pch' and 'pmb' can NOT be the same buffer
    {
    size_t uMbNdx = 0;
    size_t uChNdx = 0;
    BOOL bUnicodeXlate = !bMixed;	/* are we within substr to xlate? */
    *pch = '\0';
    while ((pmb[uMbNdx] != '\0') && (uChNdx < uchsize-1))
	{
/* protect any SI/SO substrings, which are UTF8 Unicode */
	if ((pmb[uMbNdx] == ANSI_SI) && bMixed)
	    {
	    bUnicodeXlate = TRUE;
	    uMbNdx++;
	    continue;		// start translating unicode chars
	    }
	if ((pmb[uMbNdx] == ANSI_SO) && bMixed)
	    {
	    bUnicodeXlate = FALSE;
	    uMbNdx++;
	    continue;		// end translating unicode chars
	    }
	if (!bUnicodeXlate)
	    {
	    pch[uChNdx++] = pmb[uMbNdx++];
	    pch[uChNdx] = '\0';
	    continue;		// preserve non-unicode chars
	    }
	int cnt = mbtocp(&pch[uChNdx++],&pmb[uMbNdx],bzMap);
	if (cnt > 0)
	    uMbNdx += cnt;
	}
    return uMbNdx;
    }
#endif

ushort Encoding::tolower_Ansi(ushort curchar)
    {
    ushort curresult;
    if (curchar >= MAX_ANSI_CHAR)
	curchar &= 0xFF;
    if (bzAnsiLowercase[curchar] == 1)
	curresult = curchar | 0x20;
    else if (bzAnsiLowercase[curchar] != 0)
	curresult = bzAnsiLowercase[curchar]; 
    else
	curresult = curchar;
//TRACE_G("`0101>Encoding::tolower converting %X to %X (ay=x%X)\n",
//		curchar,curresult,bzAnsiLowercase[curchar]);
    return curresult;
    }

void Encoding::strlwr_Ansi(char * str)
	//	convert 'str' in Windows codepage to lowercase
	//	if conversion not initialized, leave unconverted
	// 	if table==0 => no change; 1 => 0x20 OR char; else explicit value */
    {
    size_t i;
    if (bzAnsiLowercase == NULL)
	return;
    for (i=0; i<strlen(str); i++)
	{
	ushort curchar = str[i];
	ushort curresult = tolower_Ansi(curchar);
//TRACE_G("`0101>Encoding::strlwr converting x%X-th char %X to %X (ay=x%X)\n",
//		i,curchar,curresult,bzAnsiLowercase[curchar]);
	str[i] = (char) curresult;
	}
    }

		// return a formatted dump of the class member
const char * Encoding::dump(int detail, 
			    const char * czArg) const
    {
    return "encoding dump\n";
    }

extern "C" {
void ENCODING_END()
    { }		/* just a marker for the link file */
int ENCODING_END_INIT_DATA=0;
int ENCODING_END_UNINIT_DATA;
    }
