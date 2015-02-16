#include "drelease.h"
char MY_SHA1_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.2 $$Date: 2013/01/03 13:50:40 $";
D_REL_IDSTR;
/*
 *	filename my_sha1.cpp
 *		$Revision: 1.2 $ $Date: 2013/01/03 13:50:40 $	
 *
 *      ~~ Copyright 2012 Kurt Rudahl and Sally Goldin
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
 *   $Id: my-sha1.cpp,v 1.2 2013/01/03 13:50:40 rudahl Exp $
 *   $Log: my-sha1.cpp,v $
 *   Revision 1.2  2013/01/03 13:50:40  rudahl
 *   added argument to specify ipc style (method)
 *
 *   Revision 1.1  2012/04/15 04:40:39  rudahl
 *   support internet licensing
 *
 *
 ****************************************************************
 * 
 * My C++ version of a sha1_base64 like in Perl
 * this is extracted from internet.cpp and is used in the web 
 * licensing app
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 6.1	2012-03-26 ktr	extracted from internet.cpp
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <ctype.h>

#if defined __GCC__ 
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
extern int h_errno; // see `man gethostbyname`
#else
#include <windows.h>
#include <process.h>
#include <winsock2.h>
#endif
#include <openssl/bio.h> // BIO objects for I/O
#include <openssl/ssl.h> // SSL and SSL_CTX for SSL connections
#include <openssl/err.h> // Error reporting
#include <openssl/sha.h> // SHA1

#include "sqlite3.h"

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "files.h"
#include "ob.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcFile.h"
#include "IpcWrap.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "permbits.h"

#include "SSDb.h"

static BOOL s_bVerbose = FALSE;

#ifdef NOMORE
static void getSSLErrors(const char * pczSummary,
		  char * pczResultBuf,
		  size_t uResultBufSize)
    {
    char errbuf[120]; // size specified by openssl docs
    if (s_bVerbose)
        fprintf(stderr,"getSSLErrors summary=%s\n",pczSummary);
    strncat(pczResultBuf,pczSummary,uResultBufSize - strlen(pczSummary) - 1);
    while(long e = ERR_get_error())
        {
	ERR_error_string(e,errbuf);
	strncat(pczResultBuf,errbuf,
		uResultBufSize - strlen(pczResultBuf) - 1);
	}
    }

/* check a ValCode supplied by the user and format it for the DB
 * @param pUserValCode
 * @return		NULL if invalid, or 8-char hex string
 */
const char * extractValCode(const char * buf)
    {
    char check[2] = "";
    static char retbuf[20] = "";
    const char * pBuf = buf;
    ulong checksum = 0;
    uint j = 0;
    check[0] = *pBuf++;
    checksum += strtol(check,NULL,16);
    while ((*pBuf != '\0') && (j < sizeof(retbuf)-1))
        {
	if (strchr("0123456789ABCDEFabcdef",*pBuf) != NULL)
	    {
	    retbuf[j++] = toupper(*pBuf);
	    retbuf[j] = '\0';
	    check[0] = *pBuf;
	    checksum += strtol(check,NULL,16);
	    } 
	pBuf++;
	} 
    if (s_bVerbose)
      fprintf(stderr,"extractValCode inbuf='%s' returning '%s' checksum=%ld\n",
	      buf,retbuf,checksum);
    return ((checksum % 10)== 0) ? retbuf : NULL;
    }
#endif

void usage(const char * name)
        {
	fprintf(stderr, "Usage: %s -m sn -d valdate -c machinecode [-v]\n", name);
	fprintf(stderr, "    -v       for verbose\n");
	exit(1);
	}

// create a utility for creading the SHA1 magic string
// This is used in Linux, in the web app dragonValidate.pm
// but needs to return the same string as SSDb::CalcValCode
int main(int argc, char **argv)
    {
    int rc = 0;
    BOOL bVerbose = FALSE;
    printf("my_sha1 v 0.1\n");
    char * pSN = NULL;
    char * pCalcMachine = NULL;
    char * pValDate = NULL;
    while(++rc < argc)
        {
	if (strcasecmp(argv[rc],"-v") == 0)
	    {
	    bVerbose = TRUE;
	    }
	else if (strcasecmp(argv[rc],"-m") == 0)
	    {
	    pSN = strdup(argv[++rc]);
	    }
	else if (strcasecmp(argv[rc],"-d") == 0)
	    {
	    pValDate = strdup(argv[++rc]);
	    }
	else if (strcasecmp(argv[rc],"-c") == 0)
	    {
	    pCalcMachine = strdup(argv[++rc]);
	    }
	else
	    usage(argv[0]);
	}
    char basestr[1024];
    byte shabuf[22];
    char mimebuf[30];
    memset(shabuf,0,sizeof(shabuf));
    SHA_CTX ctx;
    if (pSN == NULL)
	{
	printf("Error: Serial number not specifiied\n");
	exit(1);
	}
    if (pCalcMachine == NULL)
	{
	printf("Error: Machine code not specifiied\n");
	exit(1);
	}
    if (pValDate == NULL)
	{
	printf("Error: ValDate not specifiied\n");
	exit(1);
	}
    sprintf(basestr,"%s%s%sarchaeopteryx",pSN,pCalcMachine,pValDate);
    SHA1((const byte *)basestr,strlen(basestr),shabuf);
    int j=0;
    char * pMime = mimebuf;
    for (j=0; j<7; j++)
	{
	uint bits = (0xFF0000 & shabuf[j*3]<<16)|(0xFF00 & shabuf[j*3+1]<<8)|(0xFF & shabuf[j*3+2]);
//	    printf("j=%d bits=x%X\n",j,bits);
	int jj;
	uint mask[] = {0xFC0000,0x3F000,0xFC0,0x3F};
	char xlate[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		           "abcdefghijklmnopqrstuvwxyz"
			   "01234567890+/";
	for (jj=0; jj<4; jj++) // pull the bits 3 at a time
	    {
	    byte oct = (bits & mask[jj]) >> (3-jj)*6;
//		printf("    jj=%d mask=0x%X oct=x%X\n",jj,mask[jj],oct);
	    if (oct > 63)
		{
		printf("Error in mime encoding\n");
		exit(1);
		}
	    *pMime++ = xlate[oct];
	    }
	}
    mimebuf[27] = '\0'; // match Perl's SHA1_base64 which gives 27 chars
    if (bVerbose)
	printf("my_sha1 machine code=%s sha=%s\n",pCalcMachine,mimebuf); 
    printf("%s\n",mimebuf); 
    }

void MY_SHA1_END() { puts(FIL_ID); }

