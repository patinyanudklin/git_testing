/****************************************************************
 *	ROSEFUNS.C -  General routines used by Tools Library programs
 *
 *	  $Revision: 1.4 $	$Date: 2014/12/17 07:20:39 $
 *
 *	  ~~ Copyright 1994-2014 Kurt Rudahl and Sally Goldin
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *	~~ EndC
 *****************************************************************
 *	$Id: rosefuns.c,v 1.4 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: rosefuns.c,v $
 *	Revision 1.4  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.3  2004/12/23 12:15:21  rudahl
 *	lint-ish fix
 *
 *	Revision 1.2  2002/06/10 12:33:53  rudahl
 *	updated TIFF-related fns to MSC4.1
 *	
 *	Revision 1.1.1.1  1999/03/11 00:35:20  rudahl
 *	first checkin of only SOME common dirs
 *	
 *
 *****************************************************************
 *   This module holds several subroutines of general utility
 *   expected to be useful throughout ROSETTA.
 ******************************************************************
 *
 *	Revision history
 *
 * 1.0	12-28-94  seg	Created
 *	1/4/95 ktr	split into two compile modules
 *	1/13/95 seg	added trimstring, also code that would
 *                      allow keywords initializers to be in lower
 *                      case and have trailing blanks - for use
 *                      in outputting the Idrisi doc file for V4.0
 *	9/5/97 ktr	added provision for Unix (__GCC__) compilation
 * 5.4	12/22/2004 ktr	added stricmp for linux
 */

#if defined __GCC__
#else
#include <io.h>
#include <dos.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dtypes.h"
#include "dlimits.h"
//#include "dhead.h"
//#include "hdrstats.h"
#include "toolerr.h"
#include "toolkit.h"
#include "files.h"
#include "rosefuns.h"

#ifndef ROSEFUN_READ
#define ROSEFUN_WRITE	// the default - only a few need to read it
#endif

#if defined ROSEFUN_READ || defined __32BIT__
/**/
static void trimstring(char * instring)
	  /* trim trailing blanks and newlines from string */
    {
    int i;
    i = strlen(instring) - 1;
    while ((i > 0) && ((instring[i] == 0x20) || (instring[i] == '\n')))
	i--;
    instring[++i] = '\0';
    }


/**/
int ReadKeyedFile(const char* infile,
		    const char* keyword[],const size_t valsize[],
		    const size_t count, const char* delims,
		    const ushort maxfsize,void* destination)
	/* Read and convert data from a keyword-based file, 'infile'.
	 * The 'keyword' array is an ordered list of keywords.
	 * The 'valsize' array indicates the size and implicitly, the
	 * data type of the corresponding expected value.
	 * 'count' is the length of these two array. 'delims' indicates
	 * possible delimiters that we allow between keyword and value.
	 * Finally, 'destination' points to a structure which is assumed
	 * to have a layout such that the first valsize[0] bytes should
	 * hold the value from keyword[0], the next valsize[1] bytes should
	 * hold the value from keyword[1] and so on.
	 *
	 * 'maxfsize' is a "safety valve" so that if we have an ill-formed
	 * file, or one that is appended to the front of the actual data,
	 * we do not have to read through the entire file.
	 *
	 * Returns the number of keywords actually matched (0 <= n <= count)
	 * or a negative value for a file reading error.
	 * The results of the data input are of course returned in the
	 * structure pointed to by 'destination'.
         *
         * 1/13/95 delims must not be more than 28 chars long...
	 */
    {
    char linebuf[256];
    char currentkey[128];
    char far * rsfreturn;
    char* tokptr;
    char * keyptr=NULL;
    ushort shortval;
    ulong longval;
    double dblval;
    ushort fieldoffset;
    char line_end[] = "\r\n";
    char newdelims[] = " \t";
    char alldelims[32] = " \t";
    size_t matched = 0;
    long bytesread = 0;  /* keep track of how many bytes read from file */
    byte * keyfound = NULL;  /* use to keep track of which keys have been found */

    keyfound = malloc(count);
    if (keyfound == NULL)
	return -1;   /* memory allocation error...*/
    memset(keyfound,0,count);
    
    if (delims)
       strcat(alldelims,delims);
        
    while ((bytesread < (long)maxfsize) && (matched < count))
	{
	size_t wordctr=0;
	rsfreturn =  rsfgets(NEAR2FAR(linebuf),sizeof(linebuf),infile,bytesread);
	if (rsfreturn == FARNULL)
	    break;   /* presumably this means end of file */
	bytesread += strlen(linebuf);
		/* parse the keyword token */
	keyptr = strtok(linebuf,(delims) ? delims : newdelims);
	if (keyptr == NULL)
	    continue;   /* blank line, just move to the next line of file */
        trimstring(keyptr); /* remove trailing blanks */
		/* now get the value */
	tokptr = strtok(NULL,line_end);
	if (tokptr == NULL)
	    continue;   /* no value - just skip this line */
		/* search the keyword array for the keyword */
	while(wordctr < count)
	    {
            /* copy so that we can upcase & trim the key */
            strcpy(currentkey,keyword[wordctr]);
	    trimstring(currentkey);
	    if (stricmp(keyptr,currentkey) == 0)
		 break;
	    wordctr++;
	    }
	if (wordctr < count)   /* this means we found a match */
	    {
	    /* keep track of number of matches */
	    size_t j;
	    if (keyfound[wordctr] == 0)	
		 matched += 1;
	    keyfound[wordctr] = 1;
		/* calculate offset */
	    fieldoffset = 0;
	    for (j = 0; j < wordctr; j++)
		 fieldoffset += valsize[j];
	    /* use the valsize to figure out how to convert */
	    switch (valsize[wordctr])
		{
		case 2:  /* ushort */
		    shortval = atoi(tokptr);
		    *(ushort*)((byte*)destination + fieldoffset) = shortval;	
		    break;
		case 4:  /* ulong */
		    longval = atol(tokptr);
		    *(ulong*)((byte*)destination + fieldoffset) = longval;	
		    break;
		case 8:  /* double */
		    dblval = atof(tokptr);
		    *(double*)((byte*)destination + fieldoffset) = dblval;	
		    break;
		default:   /* char[] */
		    memset((char*)((byte*)destination + fieldoffset),0,
			      valsize[wordctr]);  /* set to nulls */
                    /* skip all delimiters */
                    tokptr += strspn(tokptr,alldelims);
		    strncpy((char*)((byte*)destination + fieldoffset),tokptr,
			      valsize[wordctr]-1); /* then copy the string */
		}  /* end switch */
	    }      /* end if we found a keyword */
	}	   /* end while */
    /* cleanup */

    free(keyfound);	// we returned earlier if malloc failed
    return matched;
    }
#endif //#ifdef ROSEFUN_READ

/**/

#ifdef ROSEFUN_WRITE

int WriteKeyedFile(const char* outfile,
		    const char* keyword[],const size_t valsize[],
		    const size_t count, const char* delims,
		    const void* source)
	/* Write data to a keyword-based file, 'outfile', in
	 * keyword/value form.
	 * The 'keyword' array is an ordered list of keywords.
	 * The 'valsize' array indicates the size and implicitly, the
	 * data type of the corresponding value. Values are actually
	 * stored in the 'source' structure.
	 * 'count' is the length of these two arrays. 'delims' indicates
	 * delimiters to be written between each keyword/value pair.
	 *
	 * Returns the number of keywords written
	 * or a negative value for a file writing error.
	 *
	 * Note this function appends to any existing version of outfile.
	 */
    {
    size_t i;
    int status;
    int do_write;
    char linebuf[256];
    ushort shortval;
    ulong longval;
    double dblval;
    char shortfmt[] = "%s%s%d\r\n";
    char longfmt[] = "%s%s%ld\r\n";
    char dblfmt[] = "%s%s%lf\r\n";
    char stringfmt[] = "%s%s%s\r\n";
    ushort fieldoffset = 0;

    for (i = 0; i < count; i++)
	{
	/* use the valsize to figure out how to convert */
        do_write = 1;
	switch (valsize[i])
	   {
	   case 2:  /* ushort */
	      shortval = *(ushort*)((byte*)source + fieldoffset);	
	      sprintf(linebuf,shortfmt,keyword[i],delims,shortval);
	      break;
	   case 4:  /* ulong */
	      longval = *(ulong*)((byte*)source + fieldoffset);	
	      sprintf(linebuf,longfmt,keyword[i],delims,longval);
	      break;
	   case 8:  /* double */
	      dblval = *(double*)((byte*)source + fieldoffset);	
	      sprintf(linebuf,dblfmt,keyword[i],delims,dblval);
	      break;
	   default:   /* char[] */
              if (strlen((char*)((byte*)source + fieldoffset)) > 0)
                 /* only print if value is non-blank */
  	         sprintf(linebuf,stringfmt,keyword[i],delims,
			(char*)((byte*)source + fieldoffset));
                 /* we are assuming that the string is null-terminated */
              else
                 do_write = 0;
	   }  /* end switch */
	/* now write the formatted line using wsf */
        if (do_write)
           { 
   	   if ((status = wsf(outfile,NEAR2FAR(linebuf),strlen(linebuf),
		WSF_APPEND | WSF_BUFFER | WSF_NOFLUSH)) < 0)
	        return status;
           }
	fieldoffset += valsize[i];
	}  /* end of loop */
    wsf(outfile,NEAR2FAR("\r\n"),2,WSF_APPEND | WSF_BUFFER);	// flush buffer
    return i;
    } 

void dtk_errs_to_stderr()
	//	send error messages to stderr not stdout, clear err msg stack
	//	should be arg. to atexit() AFTER dtk_init()
    {
    int emc=dtk_ErrorMsgCount();
    while (emc)
	{
	fputs(dtk_ErrorMsg(--emc),stderr);
	fputs("\n",stderr);
	}
    dtk_ErrorMsgClear();
    }

#endif // #ifdef ROSEFUN_WRITE
