#include "drelease.h"
ID_ I18N_ID[] =
   "\0@(#) " __FILE__ "     $Revision: 1.19 $ $Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/****************************************************************
 *	I18N.C   - multibyte and wide character functions required when  
 *                 linking to the Zortech 2.1 standard libraries and other
 *		   libraries which are not completely ANSII compliant
 *
 *	  $Revision: 1.19 $	$Date: 2014/12/05 14:24:30 $
 *
 *	  ~~ Copyright 1993-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: i18n.c,v 1.19 2014/12/05 14:24:30 rudahl Exp $
 *	$Log: i18n.c,v $
 *	Revision 1.19  2014/12/05 14:24:30  rudahl
 *	reconciled DragonProfessional with OpenDragon
 *
 *	Revision 1.18  2008/08/25 12:27:05  rudahl
 *	updating
 *
 *	Revision 1.17  2006/12/17 10:35:11  rudahl
 *	fixed bug in counting chars
 *	
 *	Revision 1.16  2005/03/19 06:31:51  rudahl
 *	CVS moved from windu; maybe some history lost
 *	
 *	Revision 1.16  2005/03/13 02:40:59  rudahl
 *	fix probs found working with enhance
 *	
 *	Revision 1.15  2005/01/27 23:02:08  rudahl
 *	adapt for 64-bit machine
 *	
 *	Revision 1.14  2005/01/26 02:07:25  rudahl
 *	cleanup for Version 5.5
 *	
 *	Revision 1.13  2004/12/28 12:13:12  rudahl
 *	fixed problem reading UTF-8 from header
 *	
 *	Revision 1.12  2004/12/23 11:43:40  rudahl
 *	fixed and enhanced i18ntest
 *	
 *	Revision 1.11  2004/12/04 06:05:37  rudahl
 *	adapt for Mingw
 *	
 *	Revision 1.10  2003/04/22 22:37:37  rudahl
 *	final I18n changes
 *	
 *	Revision 1.9  2003/04/21 17:35:05  rudahl
 *	fixup and generalize uni_mbstocps
 *	
 *	Revision 1.8  2002/05/08 00:11:33  rudahl
 *	added wcslen
 *	
 *	Revision 1.7  2002/01/15 17:24:50  rudahl
 *	removed some deadwood
 *	
 *	Revision 1.6  2001/10/04 08:27:25  rudahl
 *	docs improvement
 *	
 *	Revision 1.5  2001/08/24 08:39:56  rudahl
 *	adapting for win32
 *	
 *	Revision 1.4  2001/07/03 20:00:18  rudahl
 *	added check_UTF8_char and main() for testing; also excluded mblen from 32-bit build
 *	
 *	Revision 1.3  2000/05/30 00:59:13  rudahl
 *	a cast needed for GCC
 *	
 *	Revision 1.2  1999/07/13 23:57:16  rudahl
 *	fixed RCS symbols
 *
 *	Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *	first checkin of only SOME common dirs
 *
 * Revision 4.4  1998/02/22  08:08:30  tower
 * checkin for class class5_0
 * 
 * Revision 4.3  1998/02/22  08:08:30  tower
 * checkin for class CLASS5_0
 * 
 * Revision 4.1  1994/12/13  13:41:18  tower
 * Released with DRAGON 4.1 12/94
 * 
 * Revision 4.0.1.7  1993/02/12  16:17:38  tower
 * final for DRAGON 4.0G.
 * 
 * Revision 4.0  1993/02/12  16:17:38  tower
 * final for DRAGON Release 4.0
 * 
 *
 *****************************************************************
 *****************  Revision History **************************
 *
 * 1.0	1/30/92 seg	created
 *	10/21/94 ktr	added uni_wctomb(), uni_mbtowc(), etc which have
 *			non-std ability to account for current code page.
 *			Note that in Zor3.0, wchar_t is defined as char.
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 *	6/12/98 ktr	added fns to cvt between UTF-8 and UCS-2 unicode,
 *			and adapted mbstowcs accordingly
 * 5.4	12/1/2004 ktr	adapt for Mingw. alt name for wcslen
 *	12/22/2004 ktr	convert ltoa, itoa to sprintf for 32-bit versions
 *	12/27/2004 ktr	added mbslen
 * 5.5	2005-1-22 ktr	moved from release 5.4; removed 16-bit stuff
 **************************************************************
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __GCC__
#define stricmp strcasecmp
#include <time.h>
#else
#include <dos.h>
#include <io.h>
#endif

#include "dtypes.h"
#include "dlimits.h"

#include "i18n.h"

#if !defined  __ZTC__ && !defined __WATCOMC__ && !defined __32BIT__

int mblen(const char* s, size_t n)
       /* Localization-related function. If s is non-null,
        * checks the next n bytes starting at s to see
        * if they include a valid multi-byte character. If so,
        * returns the number of bytes in the first such
        * character; if not, returns a -1. Returns 0 if
        * s is NULL.
        *
        * This is an ANSI standard function function which
        * may not be provided by all libraries. 
        *
        * This particular function is a dummy which will only
        * work for single-byte characters. Thus, it will
        * always return either 1 or 0.
        */
     {
     if ((s == NULL) || (*s == 0))
         return 0;
     else
         return 1;
     }
#endif

	/* return the number of characters (wchars) in pStr
	 */
size_t grs_wcslen(const UNICODE_WCHAR * pStr)
    {
    size_t uRetval = 0;
    const UNICODE_WCHAR  * pChar = pStr;
    while (*pChar++ != 0)
        uRetval++;
    return uRetval;
    }

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
	      int (* xlate)(UNICODE_WCHAR * pwChar,const int))
    {
    size_t count = 0;
    int iQuote = '\0';
    const char * mbstr_end = mbstr + strlen(mbstr);
    if (bQuoted && (strchr("\"'",*mbstr) != NULL))
        iQuote = *mbstr++;
    while (mbstr < mbstr_end)
        {
	if ((iQuote != '\0') && (iQuote == *mbstr))
	    break;
	else
	    {
	    UNICODE_WCHAR wchar;
	    int stat = uni_mbtowc(&wchar,mbstr,6,xlate);
	    if (stat <= 0)
	        break;
	    mbstr += stat;
	    count++;
	    }
	}
    return count;
    }

static uint cur_escape()
	/*	Return escape lead-in char spec'd in .CFG file, or
	 *	default.
	 */
    {
    static uint cur_esc = '\\'; /* '\0';	// signifies not yet init.*/
/* this doesn't work yet -- why not?  */
/*
    if (cur_esc == '\0')
	{
	char cfgstr[80];
	if (GetConfig("CHAR_ESCAPE",cfgstr,sizeof(cfgstr)) <= 0)
	    cur_esc=STD_ESC;
	else
	    cur_esc=cfgstr[0];
	}
*/
    return cur_esc;
    }

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
	       int (* xlate)(UNICODE_WCHAR * pwChar,const int))
    {
    int retval = (mbchar) ? -1 : 0;
    UNICODE_WCHAR tmp = 0;
    if (*mbchar==0) /* despite Microsoft, only needs one NULL */
	{
	retval = 0;
	*wchar = tmp;
	}
    else if (count > 0)
	{
	  /* look for escape sequences and translate them into 16-bit word */
	if (*mbchar == (char)cur_escape()) /* '\' by default */
	    {
	    char numbuf[7];
	    strcpy_array(numbuf,mbchar);
	    if((tolower(numbuf[1]) == WIDEESC) && (count >= 6)) /* "\u" */
	        {
		tmp = (UNICODE_WCHAR) strtoul(numbuf+2,NULL,16);
		retval = 6;
	        }
	    else if((tolower(numbuf[1]) == NARROWESC) && (count >= 4) /*"\x"*/
			&& (xlate != NULL)) /* else narrow escapes not valid */
	        {
		int narrowchar;
		numbuf[4] = '\0';
		narrowchar = (UNICODE_WCHAR)strtoul(numbuf+2,NULL,16);
		(* xlate)(&tmp,narrowchar);
		retval = 4;
		}
	    else /* just swallow the escape and continue */
		retval = cp_UTF8toUCS2(&tmp,(const byte *)mbchar);
	    }
	else if (xlate != NULL)	/* doing a code page? */
	    retval = (* xlate)(&tmp,*mbchar);
	else	/* anything else, assume it's a UTF-8 */
	    retval = cp_UTF8toUCS2(&tmp,(const byte *)mbchar);

	if ((retval > 0) && (wchar != NULL))
	    *wchar = tmp;
	}
    return retval;
    }

	/*	convert 'mbstr' to string of 2-byte wide chars at 'wstr',
	 *	examining at most 'icount' chars in 'mbstr'.
	 *	and writing at most 'osize' wchars to 'wstr'.
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
	 * 	strip off any SI/SO 
	 */
int uni_mbstowcs(UNICODE_WCHAR * wstr, const char * mbstr,
      const size_t icount,const size_t osize, size_t * pOcount,
      int (* xlate)(UNICODE_WCHAR * pwChar,const int))
    {
    UNICODE_WCHAR * owstr=wstr;
    size_t ocnt = 0;
    size_t icnt = 0; 
    int retval = 0;
    while (mbstr && (ocnt < osize) && (icnt < icount))
	{
		/* for SI or SO in input, just skip over them */
	if ((mbstr[icnt] == 0xF) || (mbstr[icnt] == 0xE))
	    {
	    icnt++;
	    continue;
	    }
	retval = uni_mbtowc(owstr,mbstr+icnt,6,xlate);
	if (retval <= 0)
	    break;
	if (*owstr)
	    {
	    owstr++;
	    ocnt++;
	    if ((ocnt+1 < osize) 
		    && ((*(mbstr+icnt+retval)=='\0') || (retval==0)) )
		{
		*owstr = 0;
		break;
		}
	    }
	icnt += retval;
	}
    *owstr = 0;	/* handle empty or overflow source string cases */
    if (pOcount != NULL)
        *pOcount = ocnt;
    return (retval<0) ? retval : (int)icnt;
    }

	/*	convert 'wchar' to multibyte char, writing
	 *	at most min('MB_CUR_MAX',destlimit) chars in 'mbchar'
	 *	If 'mbchar'==NULL, convert but don't store
	 *	If 'wchar' is ASCII, value is same
	 *	else if 'xlate' is non-NULL, use it to create narrow esc. seq.
	 *	 ('xlate' returns -1 if unable to convert)
	 *	else create wide-escape seq.
	 *	Return 0 if 'wchar' is NULL (2-byte 0)
	 *		-1 if invalid 'wchar' (impossible) or other err
	 *		else # chars of 'mbchar' which were written
	 */
int uni_wctomb(char * mbchar, const UNICODE_WCHAR wchar,
	       const size_t destlimit,
	       int (* xlate)(char * mbchar,const UNICODE_WCHAR,
			     const size_t))
    {
    int retval = -1;
    char * loc_mbchar = mbchar;
    if (wchar==0)
	{
	retval = 0;
	if (mbchar != NULL)
	    *mbchar = '\0';
	}
    else if ((wchar >= ' ') && (wchar < 0x7F))	/* ascii */
	{
	retval = 1;
	if ((mbchar != NULL) && (destlimit >= 1))
	    {
	    *mbchar = (char)wchar;
	    *(mbchar+1) = '\0';
	    }
	}
    else if (xlate != NULL)
	retval = (*xlate)(mbchar,wchar,destlimit);	/* if fail, gen wide-esc seq.*/
    if (retval == -1)
	{
	retval = 6;
	if (mbchar != NULL)
	    {
	    if (destlimit >= 6)
		{
		ulong ltmp = 0x10000 + wchar;	/* this will 0-fill if wchar small*/
		*loc_mbchar++ = cur_escape();
		*loc_mbchar++ = WIDEESC;
		sprintf(loc_mbchar,"%04lX",ltmp);
		}
	    else
		retval = 0;	/* no room to convert, so terminate */
	    }
	}
    return retval;
    }

int uni_wcstombs(char * mbstr,const UNICODE_WCHAR * wstr,const size_t count,
	   int (* xlate)(char * mbchar,const UNICODE_WCHAR,const size_t))
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
    {
    char * ombstr=mbstr;
    const UNICODE_WCHAR * loc_wstr = wstr;
    size_t cnt = 0;
    int retval = 0;
    while ((wstr != NULL) && (cnt < count))
	{
	retval = uni_wctomb(ombstr,*loc_wstr++,count-cnt,xlate);
	if (retval < 0)	/* error */
	    break;
	cnt += retval;
	if (ombstr)
	    {
	    ombstr+=retval;
	    if ((cnt < count) && ((*loc_wstr==0) || (retval==0)) )
		{
		*ombstr++ = 0;	/*MSoft says should cr double NULL - why?*/
		*ombstr = 0;
		break;
		}
	    }
	}
    return (retval<0) ? retval : (int)cnt;
    }

int cp_UCS2toUTF8(char * mbchar,const UNICODE_WCHAR wChar,
		const size_t uBufSpace)
	/* convert 16-bit (UCS-2) Unicode to multibyte UTF-8 form,
	 * provided that there is room for it.
	 * Always append '\0' if it will fit
	 * Return #bytes added to 'mbchar' if OK else -1
	 */
    {
    int retval = -1;
    char * pOut = mbchar;
    if ((wChar < 0x80) && (uBufSpace >= 2))
	{
	*pOut++ = (char)wChar;
	retval = 1;
	}
    else if ((wChar < 0x800) && (uBufSpace >= 3))
	{
	*pOut++ = 0xC0 | (char)(wChar>>6);
	*pOut++ = 0x80 | (char)(wChar & 0x3F);
	retval = 2;
	}
    else if (uBufSpace >= 4)
	{
	*pOut++ = 0xE0 | (char)(wChar>>12);
	*pOut++ = 0x80 | (char)((wChar >> 6) & 0x3F);
	*pOut++ = 0x80 | (char)(wChar & 0x3F);
	retval = 3;
	}
    if (retval > 0)
	*pOut++ = '\0';
    return retval;
    }

int cp_UTF8toUCS2(UNICODE_WCHAR  * pwChar,const byte * mbchar)
	/* convert multibyte UTF-8 Unicode to 16-bit (UCS-2) form,
	 * Return #bytes used from 'mbchar' if OK else -1
	 */
    {
    int retval = -1;
    UNICODE_WCHAR wChar = 0;
    const byte * pIn = mbchar;
    if (*pIn < 0x80)
	{
	wChar = *pIn;
	retval = 1;
	}
    else if ((*pIn & 0xE0) == 0xC0)
	{
	wChar = (*pIn++ & 0x1F) << 6;
	if ((*pIn & 0xC0) == 0x80)
	    {
	    wChar |= *pIn & 0x3F;
	    retval = 2;
	    }
	}
    else if ((*pIn & 0xF0) == 0xE0)
	{
	wChar = (*pIn++ & 0xF) << 12;
	if ((*pIn & 0xC0) == 0x80)
	    wChar |= (*pIn++ & 0x3F) << 6;
	if ((*pIn & 0xC0) == 0x80)
	    {
	    wChar |= *pIn & 0x3F;
	    retval = 3;
	    }
	}
    if ((retval > 0) && (pwChar != NULL))
	*pwChar = wChar;
    return retval;
    }

int check_UTF8_char(const ulong mbchar)
	/* check whether mbchar is a valid UTF-8 char 
	 * Return # bytes consumed if OK else 0
	 */
    {
    int retval = 0;
    const byte * pIn = (const byte *)&mbchar;
    if (*pIn < 0x80)
	{
	retval = 1;
	}
    else if ((*pIn & 0xE0) == 0xC0)
	{
	pIn++;
	if ((*pIn & 0xC0) == 0x80)
	    {
	    retval = 2;
	    }
	}
    else if ((*pIn & 0xF0) == 0xE0)
	{
	pIn++;
	if ((*pIn & 0xC0) == 0x80)
	    {
	    pIn++;
	    if ((*pIn & 0xC0) == 0x80)
	        {
		retval = 3;
		}
	    }
	}
    return retval;
    }

int check_UTF8_string(const byte * pMbchar)
	/* check whether pMbchar is a valid UTF-8 string
	 * Return byte number where error occurs, or -1 if OK
	 */
    {
      //    int retval = 0;
    const byte * pIn = pMbchar;
    while (*pIn != '\0')
        {
	const ulong mbchar = *(ulong *)pIn;
	int test = check_UTF8_char(mbchar);
	if (test == 0)
	    return pIn-pMbchar;
	pIn += test;
        }
    return -1;
    }

void I18N_END() { puts(FIL_ID); }		/* just a marker for the line file */

#ifdef TEST
#include <stdio.h>

void usage()
{
	printf("Test if a file is valid UTF-8\n");
	printf("Usage: i18ntest filename\n");
	exit(1);
}

/* test for valid UTF-8 file */
int main(int argc, char ** argv)
    {
    char * file = NULL;
    char buf[4096];
    char * fred = NULL;
    int iLineNo = 1;
    FILE * inf = NULL;
    if (argc < 2)
        usage();
    file = *++argv;
    if (strcmp(file,"-?") == 0)
        usage();
    inf = fopen(file,"r");
    if (inf == NULL)
        {
	printf("Error unable to open %s\n",file);
	exit(1);
	}
    do
        {
	memset(buf,sizeof(buf),0);
	fred = fgets(buf,sizeof(buf)-1,inf);
	printf("testing %d=%s",iLineNo,fred);
	if (fred != NULL)
	    {
	    int iBadByte = check_UTF8_string(fred);
	    if (iBadByte >= 0)
	        {
		printf("%s error at line %d byte %d\n",file,iLineNo,iBadByte);
		exit(1);
		}
	    }
	iLineNo++;
	}
    while (fred != NULL);
    printf("\n%s is OK\n",file);
    return 0;
    }

#endif
