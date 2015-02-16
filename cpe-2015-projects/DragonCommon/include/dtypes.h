/*
 *	filename DTYPES.H
 *		$Revision: 1.40 $ $Date: 2014/12/05 07:10:33 $	
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
 ****************************************************************
 *   $Id: dtypes.h,v 1.40 2014/12/05 07:10:33 rudahl Exp $
 *   $Log: dtypes.h,v $
 *   Revision 1.40  2014/12/05 07:10:33  rudahl
 *   adapting sleep() to new mingw
 *
 *   Revision 1.39  2014/04/01 07:24:45  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.38  2014/03/28 14:59:05  rudahl
 *   changes needed for new mingw
 *
 *   Revision 1.37  2010/12/13 12:50:43  goldin
 *   Change name of RASTER_t type
 *
 *   Revision 1.36  2010/11/16 03:16:02  rudahl
 *   moved RASTER_t to dtypes
 *
 *   Revision 1.35  2006/09/17 05:01:03  rudahl
 *   got rid of 'far' keyword
 *
 *   Revision 1.34  2006/01/08 09:30:26  rudahl
 *   made macros safer
 *
 *   Revision 1.33  2005/11/29 09:22:43  goldin
 *   moved NN macro to dtypes.h
 *
 *   Revision 1.32  2005/08/02 02:14:17  rudahl
 *   fine-tuning separation into product,common
 *
 *   Revision 1.31  2005/06/27 11:46:35  rudahl
 *   fixed problem with PATH_MAX
 *
 *   Revision 1.30  2005/02/18 19:54:20  goldin
 *   Add macros for sleep
 *
 *   Revision 1.29  2005/02/18 17:24:29  rudahl
 *   first pass adapt to v 5.5
 *
 *   Revision 1.28  2005/02/18 02:48:22  rudahl
 *   moved POINT_T here
 *
 *   Revision 1.27  2005/02/16 04:17:02  rudahl
 *   adapt to GCC/MINGW differences
 *
 *   Revision 1.26  2005/01/27 23:03:15  rudahl
 *   adapt for 64-bit
 *
 *   Revision 1.25  2005/01/03 07:39:05  rudahl
 *   typo
 *
 *   Revision 1.24  2004/12/31 11:02:21  rudahl
 *   cleanup
 *
 *   Revision 1.23  2004/12/31 05:47:22  rudahl
 *   imported from Dragon 5.4.4
 *
 *   Revision 1.22  2004/12/25 04:23:10  rudahl
 *   O_RAW for mingw
 *
 *   Revision 1.16  2004/11/30 03:38:02  rudahl
 *   adapt to Mingw 3.4.2 compiler
 *
 *   Revision 1.15  2003/04/20 19:29:57  rudahl
 *   make isAspace a macro
 *
 * Revision 1.1  92/11/13  11:21:21  tower
 * Initial revision
 *
 ****************************************************************
 *
 *	Defines simple data types and macros used by all DRAGON-related 
 *	software.
 *	This file should present a consistent and distinctive set of
 *	simple data type names which can be adapted to different
 *	compiler and OS environments, and which will facilitate the 
 *	software evolution to include data values and value ranges
 *	not presently supported. Therefore:
 *	1. This header file should be included in all source modules,
 *	   immediately after the needed compiler-vendor-supplied headers.
 *	2. All adaptations to different compiler vendors, revisions, and
 *	   environments should be in this file.
 *
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 1.0	8/12/92	ktr	Created
 *      11/13/92 ktr	moved the undef's of Zortech tools constants from
 *			tstack.h. These manifest constants in Zortech conflict
 *			with other usage in GRS & DRAGON.
 * 4.0	11/21/93 ktr	cosmetic changes B4 release toolkit v 4
 *	12/22/93 ktr	began adapting for MSC6 using macro MSC
 * 4.1  7/18/94 ktr	adapted for MSCv8
 *	10/18/94 ktr	added UNICODE_WCHAR
 *	1/22/95 ktr	minor fixes for MSC 8.5 - added getDS  prototype
 * 5.0	12/10/95 ktr	added Watcom (v10.0) specific stuff
 *	6/28/97 ktr	adaptations for Watcom (BOOL typedef)
 *	9/5/97 ktr	adaptations for GCC Linux
 *      4/17/99 seg     added conditionals on _WIN32 for DLL build
 *      7/22/00 ktr     changed conditionals on __MSC__
 * 5.4  5/7/01 ktr      changed BOOL for win32 to be consistent with MSOFT
 *                        windows.h
 *      6/30/01 ktr     added symbols __16BIT__, __32BIT__, __64BIT__
 *	1/9/02 ktr	enhanced _find_t for long filenames
 *	1/9/02 ktr	moved POSIX defns here from dlimits.h
 *      11/28/2004 	adapt for Mingw
 *	12/4/2004 ktr	reversed sequence of two versions of BOOL, for CGATE
 *	12/7/2004 ktr	got rid of schar, pchar, dchar; but achar used in dtk
 * 5.5	2004/12/31 ktr	imported from Dragon Academic Edition 5.4.4
 * 5.5	2005-2-17 ktr	added RECT_T, POINT_T; zapped far memory
 * 5.7	2005-6-27 ktr	unconditionally sets PATH_MAX
 *	2005-8-1 ktr	moved string macros here from dlimits
 *	2006-1-7 ktr	improved NN, NOTNULL, YESNO
 * 6.1	2010-11-16 ktr	added RASTER_t
 */

#ifndef DTYPES_H
#define DTYPES_H

/* if compiler doesn't know about 'const', uncomment the next line */
/* #define const */

/* if C++ compiler doesn't generate the macro '__cplusplus',
 * uncomment the next line */
/* #define __cplusplus */

/* the following typedefs are for consistency with various UNIX systems
 * they add nothing but clarity.
 */

/* the following #defines are for use where a universal 
 * compiler and/or platform conditional is needed. 
 * 
 * there are independent symbols for compiler:
 *   __ZTC__		   (built into the compiler)
 *   __MSC__               (defined here)
 *   __GCC__               (defined in make file)
 * and UI modality (a.k.a. "operating system"):
 *   UI_DOS, UI_WIN (any kind), UI_UNIX
 *     UI_WIN can be specialized into UI_WIN3, UIWIN32S, UI_WIN32, UI_WINNT
 *   _WIN32 - for MSC 4.1 32 bit (built into compiler)
 * see also  __16BIT__, __32BIT__, __64BIT__ below
 */

#if defined MSWIND && !defined UI_WIN
#define UI_WIN 1
#define UI_WIN3 1
#endif
	/* MSVC - based defines */
#if defined _MSC_VER
#if !defined MSC
#define MSC 1
#endif
#define __MSC__ 1
#endif
#if defined _WINDOWS && !defined UI_WIN	/* MSVC protected mode (only?) */
#define UI_WIN 1
#endif

	/* make sure at least one of each series is defined */
#if !defined __ZTC__ && !defined __MSC__ && !defined __GCC__ && !defined _WIN32
#define __GCC__
#endif
#if !defined UI_WIN32S && !defined UI_WIN32 && !defined UI_WINNT && !defined UI_WIN3
#define UI_WIN3
#endif
#if !defined UI_WIN && !defined UI_UNIX && !defined UI_DOS
#define UI_DOS 1
#endif

/* the following typedefs are for use where an environment-independent
 * specification of exact word length is needed. The definitions 
 * should be changed as needed to make these work in different
 * environments.
 */
#if defined _WIN32 || defined UI_UNIX || defined __GCC__
#define __32BIT__ 1
#endif
#if defined MSC && !defined _WIN32
#define __16BIT__ 1
#endif
#if defined UI_DOS || defined __ZTC__ || !defined __32BIT__
#define __16BIT__ 1
#endif

#ifdef __MSC__	
#ifdef _INC_STDARG	/* this is v8 - don't know about v6 */
#define __STDARG_H 1
#endif
#if defined M_I86SM
#define __SMALL__ 1
#elif defined M_I86MM
#define __MEDIUM__ 1
#elif defined M_I86LM
#define __LARGE__ 1
#endif
#endif

#ifdef __ZTC__
#if defined __SMALL__ && ! defined __IO_H
#include <io.h> /* needed for getDS() */
#endif
typedef signed short SINT16;
typedef unsigned short UINT16;
typedef signed long SINT32;
typedef unsigned long UINT32;
#ifndef TYPE_H
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned int uint;
#endif
#endif
#if !  defined __MINGCC__
#if defined __MSC__  || defined _WIN32
typedef signed short SINT16;
typedef unsigned short UINT16;
#ifndef TYPE_H
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned int uint;
#endif
#endif
#if defined __MSC__  && ! defined _WIN32
typedef signed long SINT32;
typedef unsigned long UINT32;
#endif

#if defined _WIN32
typedef signed int SINT32;
typedef unsigned int UINT32;
#endif
#endif


#if defined __GCC64__
typedef signed short SINT16;
typedef unsigned short UINT16;
typedef signed int SINT32;
typedef unsigned int UINT32;
#endif

/* this should probably be based on __32BIT__ */
#if ! defined __GCC64__ && (defined __GCC__ || defined __MINGCC__)
#define __LARGE__ 1
# if ! defined _BASETSD_H
typedef unsigned long UINT32;
#endif
typedef signed short SINT16;
typedef unsigned short UINT16;
typedef signed long SINT32;

//#ifndef _LINUX_TYPES_H   // removed 4/00 SuSE6.3
//typedef unsigned int uint;
//typedef unsigned short ushort;
//typedef unsigned long ulong;
//#endif

// new (2010) data type for expressing line, pixel number and count
// for INTERNAL use
// Initially used by georast
typedef unsigned int IMGDIM_t;

//#if defined __GCC__ || defined __MINGCC__
#if defined __MINGCC__
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned long ulong;
#endif

#ifdef ANCIENT
	/* define these out of existence */
#define far
#define _far
#define near
#define _near
#endif

#ifdef _WIN32   /* define these out of existence here, too */
#define far
#define _far
#define near
#define _near
#endif
#endif // ANCIENT

#if (!defined FALSE && defined _WIN32)
typedef int BOOL;
#define FALSE		    0
#define TRUE		    1
#define _BOOL_DEFINED
#endif

#if (!defined _BOOL_DEFINED && !defined MSC && !defined __WINDOWS_H && !defined _INC_WINDOWS)
	 /* defined in MSC & Zortech Windows.h, in Watcom Win16.h */
#if ! defined _WINVER_H
typedef unsigned int BOOL;
#define FALSE		    0
#define TRUE		    1
#define _BOOL_DEFINED
#endif
#endif

/****************************************************************
 *
 *	POSIX stuff
 *
 ****************************************************************/

/* POSIX requires PATH_MAX, NAME_MAX in <limits.h>
 * MSC v 4 defines path_max as 512, name_max as 255
 *      linux/limits.h defines it as 4096
 * we need a large but also consistent value
 */
#ifdef PATH_MAX
#undef PATH_MAX
#endif
#define PATH_MAX 512

#ifdef NAME_MAX
#undef NAME_MAX
#endif
#define NAME_MAX 255

/****************************************************************
 *
 *	8-bit data types
 *
 ****************************************************************/

/* historically, the "char" data type has been used for at least three
 * distinct purposes. None of these purposes is completely consistent
 * with modern needs and specifications. Therefore, it is recommended 
 * that "char" be replaced in all software as follows:
 *
 * 1. "char" in its fundamental form is an alphabetic character. ANSI
 *    defines it as a signed type, so that in practise it has only 
 *    7 available bits making it fairly useless for either internationalization
 *    or binary data. However, many standard library functions
 *    specifically expect "char" or "char *" arguments. Therefore, we 
 *    create a special type to distinguish computer from human chars:
 *	"achar" is an alphabetic character in a use which produces text
 *	  intended to be read by a computer, not a human. File names are
 *	  "achar", as is data read from .CFG files or written to
 *	  .SIG, .PLY or .CLF files, or PostScript programs.
 */

typedef char achar;	/* "ASCII char": for system data files, etc */

/* 2. A true 8-bit data element, not intended to be an alphabetic character,
 *    can be stored in a "char[]" array, but this is dangerous since the
 *    compiler may sign-extend this supposedly signed data element at
 *    unexpected moments. 
 *
 *    For any use of 8-bit data which is not an alphabetic character
 *    (i.e. does not use special values like '\0', '\n', '\r'), use 
 *    "byte". The strxxx functions will object, but generally they should
 *    not be used with this type of data anyway. If you get this error,
 *    check to be sure you are doing what you think you're doing!
 */

typedef unsigned char byte;
#define _BYTE_DEFINED

/* 3. "char *" has traditionally be used for declaring generic pointers.
 *    This is obsolete, unnecessary, quite dangerous, and should be
 *    eliminated. The following alternatives are available:
 *
 *    Generic pointer declarations. Whenever possible, pointers should 
 *    be declared as pointing to the data type they will actually be 
 *    used with. Generic pointers shoud be declared as type "void *".
 *
 *    Pointer arithmetic. Whenever possible, pointer arithmetic should
 *    be performed on pointers declared or cast to the actual data types.
 *    This is the only method which is guaranteed (ANSI) to work correctly.
 *    It is not possible to do arithmetic on "void *" pointers (since a
 *    void has no size). If it appears necessary to do arithmetic on a
 *    pointer of unknown type: pause and reconsider the situation. */

/* 4. A "char" (or any signed 8-bit form) used as a calling argument to a 
 *    function is REQUIRED to be extended to an "int". Automatic sign 
 *    extension will cause the binary value to be changed, so BEWARE.
 *    Best approach is never to use a "char" in a calling sequence.
 */

/****************************************************************
 *
 *	other scalar data types
 *
 ****************************************************************/

typedef unsigned short UNICODE_WCHAR;	/* this is substitute for wchar_t */

#ifndef max
#define max(a,b)  ((a) > (b)) ? (a) : (b)
#define min(a,b)  ((a) < (b)) ? (a) : (b)
#endif

/**************************************************************
 *
 * complex data types
 *
 *************************************************************/

typedef struct RECT_t        /* Rectangle structure type       */
    {
    int      Xmin;
    int      Ymin;
    int      Xmax;
    int      Ymax;
    }  RECT_T;

typedef RECT_T rect; /* deprecated */

typedef struct PT          /* Point structure type           */
   {int      X;
    int      Y;
   }  POINT_T;

typedef POINT_T point; /* deprecated */

/****************************************************************
 *
 *	DOS-specific flags
 *
 ****************************************************************/

#ifdef __ZTC__		/* otherwise, reexamine the values - needed for files.c */
#define O_RAW 0		/* zortech doesn't have this */
#define O_NETRDONLY 0x20 /* readonly - network read permitted - dos >= 3.1 */
#define O_NETRDWR 0x12   /* read/write - network deny all - dos >= 3.1 */
#endif

/****************************************************************
 *
 *	Zortech tools-specific undefs - these conflict with other usage
 *
 ****************************************************************/

#ifdef INT16	/* Zortech tools "tools.hpp" defines it as int */
#undef INT16	/* if using tools fns, put tstack.h after tools hdr files */
#endif

#ifdef __IOBJECT_HPP
#define  I_HANDLED HANDLED
#define  I_ERROR ERROR
#define  I_CANCELLED CANCELLED
#define  I_INTERRUPTED INTERRUPTED
#define  I_IGNORED IGNORED 		/* = -4 */
#undef   HANDLED
#undef   ERROR
#undef   CANCELLED
#undef   INTERRUPTED
#undef   IGNORED
#endif	/*  __IOBJECT_HPP */

/****************************************************************
 *
 *	Compiler-specific non-standard functions
 *
 ****************************************************************/

#if defined __ZTC__   || defined __32BIT__
                        /* this is the MSC 16 bit findfirst struct */
struct _find_t {	/* we need a common basis for these files ops */
    char reserved[21];
    char attrib;
    unsigned wr_time;
    unsigned wr_date;
    long size;
#if defined __ZTC__
    char name[13];
#else
    char name[NAME_MAX];
#endif
    };
#endif

#ifdef __ZTC__
#define stricmp(a,b) strcmpl(a,b)
	/* 'a' is long element count; 'b' is short elt size, power of 2 */
#define hspace()    dos_avail()
#endif

#if defined MSC 	/* maybe only versions > 6? */
#define stricmp(a,b) _stricmp(a,b)
#define peek(seg,off,dest,size) _fmemcpy(dest,MK_FP(seg,off),size)
#define dos_getftime(a,b,c) _dos_getftime(a,b,c)
/* #define hspace()    dos_avail()  not avail in MSC */
/* #define malloc(a)   _nmalloc(a) */	/* make certain it's on near heap */
/* #define calloc(a,b) _ncalloc(a,b) */
/* #define free(a)	    _nfree(a)*/
#ifdef FP_SEG
#undef FP_SEG	/* MSC defns are wrong, in that the arg can't be */
#undef FP_OFF   /* of the form &value. They still exist as _FP_SEG, etc */
#define FP_SEG(fp)	((unsigned)((unsigned long)(fp) >> 16))
#define FP_OFF(fp)	((unsigned)((unsigned long)(fp) & 0xFFFF))
#endif		/* redefine FP_SEG */
#endif		/* MSC & Watcom */

	/* compiler-specific fns - in compmisc.c */
#if defined __MINGCC__ && ! defined MINGVERS_NEW
#define O_RAW 0
/* In Microsoft and old MingWthe _sleep function takes milliseconds.
 * In Linux, sleep takes seconds, usleep takes microseconds 
 */
#define sleep(n) _sleep(n * 1000)
//#if COMPUTERNAME != WIN7-32-VM
#define usleep(n) _sleep(n / 1000)
//#endif

#endif
#ifdef __GCC__
char *strlwr(char *string);
char *strupr(char *string);
#define O_RAW 0
#define stricmp strcasecmp
#define isAspace(c) isspace(c)
#define _P_WAIT 0	/* for simulating spawnv() in GCC */
#define _P_NOWAIT 1
#else
   /* isspace() replacement; isspace is broken
    * @return TRUE if char is blank, or ctrl from tab through cr
    */
#define isAspace(c) ((c == ' ') || ((c >= 0x9) && (c <= 0xD)))
#endif

/* this shouldn't be necessary */
#if defined __cplusplus && defined MSC
#define TO_CHARPTR (char *)
#define TO_BYTEPTR (byte *)
#define TO_VOIDPTR (void *)
//#define TO_FARCHARPTR (char far *)
//#define TO_FARBYTEPTR (byte far *)
//#define TO_FARVOIDPTR (void far *)
#else
#define TO_CHARPTR
#define TO_BYTEPTR
#define TO_VOIDPTR
//#define TO_FARCHARPTR
//#define TO_FARBYTEPTR
//#define TO_FARVOIDPTR
#endif

/* string overrun bugs can be minimized by using the following macros
 * in place of strcpy() and strcat(). However, the 'ay' argument in both
 * MUST be an array, not a pointer.
 */
#define strcpy_array(ay,str) if (1) \
	{strncpy(ay,str,sizeof(ay));\
	 ay[sizeof(ay)-1]='\0'; }
#define strcat_array(ay,str) if (sizeof(ay) > (strlen(ay)+1)) \
	{strncpy(&ay[strlen(ay)],str,sizeof(ay)-strlen(ay));\
	 ay[sizeof(ay)-1]='\0'; }

	/* macro yields number of elts in array 'a' */
#define AY_COUNT(a) (sizeof(a) / sizeof(a[0]))
#define nameof(strings,val) \
	( (strings && ((uint)(val) < AY_COUNT(strings)) && strings[(val)] ) \
	? strings[(val)] : "Unknown")

     /* for use in tracing char string pointers */
#define NOTNULL(a) ((a != NULL) ? a : "(NULL)")
#define NN(a) ((a != NULL) ? a : "")

     /* for use in tracing boolean values */
#define YESNO(a) ((a) ? "YES" : "NO")

#endif	/*  DTYPES_H */

/*#endif */
