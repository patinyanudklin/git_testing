#include "drelease.h"
char KEYEDFILES_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.2 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/****************************************************************
 *	KEYED_FILES.C -  routines for reading and writing keyed files
 *
 *	  $Revision: 1.2 $	$Date: 2014/12/05 14:24:30 $
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
 *	$Id: keyed_files.c,v 1.2 2014/12/05 14:24:30 rudahl Exp $
 *	$Log: keyed_files.c,v $
 *	Revision 1.2  2014/12/05 14:24:30  rudahl
 *	reconciled DragonProfessional with OpenDragon
 *
 *	Revision 1.1  2006/08/14 06:28:01  rudahl
 *	extracted from rosefuns
 *
 *
 *****************************************************************
 *   This module holds subroutines for reading and writing 
 *	"keyed" files - i.e. sequences of name=value
 *   used with BIL files etc
 ******************************************************************
 *
 *	Revision history
 * 5.9	2006-8-12 ktr	extracted from rosefuns.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdtk.h"
#include "img_acc.h"
#include "toolerr.h"
#include "rosefuns.h"

/**/
	  /* trim trailing blanks and newlines from string */
void trimstring(char * instring)
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
    char* tokptr;
    char * keyptr=NULL;
    ushort shortval;
    ulong longval;
    double dblval;
    ushort fieldoffset=0;
    char line_end[] = "\r\n";
    char newdelims[] = " \t";
    char alldelims[32] = " \t";
    size_t matched = 0;
    long bytesread = 0;  /* keep track of how many bytes read from file */
    int iLineNo = 0;
    byte * keyfound = NULL;  /* use to keep track of which keys have been found */
    FILE * kf = fopen(infile,"r");
//    printf("keyedfile destination=%d\n",(int)destination);
    if (kf == NULL)
	return DERR_FILE_OPEN;
    keyfound = (byte *)calloc(count,sizeof(byte));
    if (keyfound == NULL)
	return DERR_MEM_ALLOC;   /* memory allocation error...*/
    
    if (delims != NULL)
       strcat(alldelims,delims);
        
    while ((bytesread < (long)maxfsize) && (matched < count))
	{
	size_t wordctr=0;
	if (fgets(linebuf,sizeof(linebuf),kf) == NULL)
	    break;   /* presumably this means end of file */
	bytesread += strlen(linebuf);
		/* parse the keyword token */
//	printf("ReadKeyedFile line %d = '%s'",iLineNo,linebuf);
	iLineNo++;
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
		case sizeof(short):  /* ushort */
		    shortval = atoi(tokptr);
//		    printf("    short keyword='%s' val=%d offset=%d\n",
//			   keyword[wordctr],shortval,
//			   (byte *)destination+fieldoffset);
		    *(ushort*)((byte*)destination + fieldoffset) = shortval;
		    break;
//~~~ not platform-independent for long and possibly double
		case sizeof(long):  /* ulong */
		    longval = atol(tokptr);
//		    printf("    long keyword='%s' val=%ld at %d offset=%d\n",
//			   keyword[wordctr],longval,
//			   (byte *)destination+fieldoffset,fieldoffset);
		    *(ulong*)((byte*)destination + fieldoffset) = longval;
		    break;
		case sizeof(double):  /* double */
		    dblval = atof(tokptr);
//		    printf("    double keyword='%s' val=%f offset=%d\n",
//			   keyword[wordctr],dblval,
//			   (byte *)destination+fieldoffset);
		    *(double*)((byte*)destination + fieldoffset) = dblval;
		    break;
		default:   /* char[] */
		    memset((char*)((byte*)destination + fieldoffset),0,
			      valsize[wordctr]);  /* set to nulls */
                    /* skip all delimiters */
                    tokptr += strspn(tokptr,alldelims);
		    strncpy((char*)((byte*)destination + fieldoffset),tokptr,
			      valsize[wordctr]-1); /* then copy the string */
//		    printf("    string keyword='%s' val=%s offset=%d\n",
//			   keyword[wordctr],tokptr,
//			   (byte *)destination+fieldoffset);
		    break;
		}  /* end switch */
	    }      /* end if we found a keyword */
	}	   /* end while */
    /* cleanup */
    fclose(kf);
    free(keyfound);	// we returned earlier if malloc failed
    return matched;
    }

/**/

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
   	   if ((status = wsf(outfile,linebuf,strlen(linebuf),
		WSF_APPEND | WSF_BUFFER | WSF_NOFLUSH)) < 0)
	        return status;
           }
	fieldoffset += valsize[i];
	}  /* end of loop */
    wsf(outfile,"\n",2,WSF_APPEND | WSF_BUFFER);	// flush buffer
    return i;
    } 

void KEYEDFILEEND() { puts(FIL_ID); }
