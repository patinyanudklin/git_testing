#include "drelease.h"
char INTERNET_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.21 $$Date: 2014/04/01 07:28:16 $";
D_REL_IDSTR;
/*
 *	filename internet.cpp
 *		$Revision: 1.21 $ $Date: 2014/04/01 07:28:16 $	
 *
 *      ~~ Copyright 2005-2014 Kurt Rudahl and Sally Goldin
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
 *   $Id: internet.cpp,v 1.21 2014/04/01 07:28:16 rudahl Exp $
 *   $Log: internet.cpp,v $
 *   Revision 1.21  2014/04/01 07:28:16  rudahl
 *   lint esp from old mingc
 *
 *   Revision 1.20  2012/05/30 09:24:45  rudahl
 *   working on the web licensing
 *
 *   Revision 1.19  2012/05/13 13:46:35  rudahl
 *   adapt setup to win7 - add ask.exe
 *
 *   Revision 1.18  2012/05/13 10:10:01  rudahl
 *   minor improved tyracing
 *
 *   Revision 1.17  2012/05/02 11:40:27  rudahl
 *   implemented WEBSGL enforcement
 *
 *   Revision 1.16  2012/04/15 04:40:39  rudahl
 *   support internet licensing
 *
 *   Revision 1.15  2012/02/28 02:07:06  rudahl
 *   working on unique machine code
 *
 *   Revision 1.14  2012/01/30 10:11:06  rudahl
 *   working on internet licensing
 *
 *   Revision 1.13  2011/12/30 11:56:13  rudahl
 *   working on web-based licensing
 *
 *   Revision 1.12  2011/12/13 08:41:39  rudahl
 *   added http and https internet communication
 *
 *   Revision 1.11  2008/07/10 04:51:42  rudahl
 *   fix web licensing
 *
 *   Revision 1.10  2008/06/27 03:35:09  rudahl
 *   work on network license
 *
 *   Revision 1.9  2008/06/26 09:46:28  rudahl
 *   revising internet
 *
 *   Revision 1.8  2007/05/27 06:08:12  rudahl
 *   removed unneeded headers
 *
 *   Revision 1.7  2007/04/01 06:32:34  rudahl
 *   fixed bug in clipping out ctrl-M junk
 *
 *   Revision 1.6  2007/03/27 10:54:37  goldin
 *   fixed register from KMUTT problem and bad receive buffer problem
 *
 *   Revision 1.5  2006/05/01 07:45:58  rudahl
 *   fixed 'organization' param in DoRequest
 *
 *   Revision 1.4  2006/04/09 11:12:07  rudahl
 *   require registration within 15 days; fix bugs
 *
 *   Revision 1.3  2006/03/11 12:26:52  rudahl
 *   final 5.8.0 mods
 *
 *   Revision 1.2  2006/02/26 11:58:50  rudahl
 *   working on registration
 *
 *   Revision 1.1  2006/02/24 13:50:19  rudahl
 *   working on registration
 *
 ****************************************************************
 * 
 * Functions to communicate with the Dragon web server, and related
 * tasks. These are really the same between Dragon and OpenDragon
 * internet.h contains the differences
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 * 5.8	2006-2-24 ktr	extracted from SSDp.cpp
 * 5.12	2008-06-26 ktr	moved from ScriptServer to libsrc/ipc
 *			to be available to installer/setup
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
#include "IpcWrap.h"
#include "dhead.h"
#include "imageHdr.h"
#include "img.h"
#include "permbits.h"
//#include "dp.h"

#include "SSDb.h"
//#include "SSModel.h"
//#include "Executable.h"
//#include "UI.h"
#include "internet.h"
//#include "SSDp.h"

static BOOL s_bVerbose = FALSE;
void EnableVerbose(BOOL bVerbose) { s_bVerbose = bVerbose; }
#define SERVER "dragon-ips.com"
#define SCRIPT_PAGE "cgi-bin/dragonVerify.pl"   // where the actual script is

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

// Do a GET from a web server, either http or https
// This code is inspired by the example in 
//    https://thunked.org/programming/openssl-tutorial-client-t11.html
// but with extensive changes
// @param pczServiceQ	can be "80" or "https". Others? or NULL
//			default: https
// @param pczServerQ	URL as e.g. www.google.com or NULL
//			default: SERVER
// @param pczTargetQ	the script or html file or NULL
//			default: SCRIPT_PAGE
// @param args		null or argument string as x=y[&z=w...]
// @param pczResultBuf	on return contains download info or error info
//			is zeroed by this fn
// @param uResultBufSize size of pczResultBuf
// @param bInitLibrary	TRUE => initialize the library. 
//			Do only the first time
// @return		number of characters received if OK (even if don't fit in buffer)
//			else DERR_FILE_OPEN (-51) if unable to connect
//			or DERR_FILE_RW (-53) if error retrieving data
int getFromWeb(const char * pczServiceQ,const char * pczServerQ,
	       const char * pczTargetQ, const char * args, char * pczResultBuf,
	       size_t uResultBufSize, BOOL bInitLibrary) 
    {
#undef FN_NAME
#define FN_NAME "internet::getFromWeb"
    SSL_CTX* ctx = NULL;
    BIO * bio = NULL;
    const char * pczService = (pczServiceQ != NULL) ? pczServiceQ : "https";
    const char * pczServer = (pczServerQ != NULL) ? pczServerQ : SERVER;
    const char * pczTarget = (pczTargetQ != NULL) ? pczTargetQ : SCRIPT_PAGE;
    BOOL bSsl = (strcmp(pczService,"https") == 0);
    char czServerPort[1024];
    int iRetval = 0;
    if (s_bVerbose)
        fprintf(stderr,"\n" FN_NAME " (en) host='%s:%s',url='%s' args='%s'\n",
		pczServer,pczService,pczTarget,args);
    logTrace(FN_NAME " (en) host='%s:%s',url='%s' args='%s'",
	     pczServer,pczService,pczTarget,args);
    if (bInitLibrary)
	{
	/* setup the SSL library */
	SSL_load_error_strings();                /* readable error messages */
	if (s_bVerbose)
	    fprintf(stderr,"main() SSL_load_error_strings finished\n");
	SSL_library_init();
	if (s_bVerbose)
	    fprintf(stderr,"main() SSL_library_init finished\n");
	ERR_load_BIO_strings(); // Load BIO error strings
	if (s_bVerbose)
	    fprintf(stderr,"main() ER_load_BIO_stingss finished\n");
	OpenSSL_add_all_algorithms(); // Load all available encryption algorithms
	if (s_bVerbose)
	    fprintf(stderr,"main() SSL_add_all_algorithms finished\n");
	}
    snprintf(czServerPort,sizeof(czServerPort),"%s:%s",pczServer,pczService);
    memset(pczResultBuf,0,uResultBufSize);
    if (bSsl)
	{ // Set up a SSL_CTX object, 
	  // which will tell BIO how to do its work
	ctx = SSL_CTX_new(SSLv23_client_method());
	SSL* ssl;   // Create an SSL object, which BIO object will provide.
	bio = BIO_new_ssl_connect(ctx); // Create BIO for SSL connections.
	// Failure?
	if (bio == NULL) 
	    {
	    getSSLErrors("Error Creating SSL BIO ",pczResultBuf,uResultBufSize);
	    SSL_CTX_free(ctx);  // need to free up the SSL_CTX
	    return DERR_FILE_OPEN;
	    }
	
	BIO_get_ssl(bio, &ssl); // Make ssl point to bio's SSL object.
	// Set the SSL to automatically retry on failure.
	SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);
	// connect to google.com on port 443.
	BIO_set_conn_hostname(bio, czServerPort);
	//	BIO_set_conn_hostname(bio, "www.google.com:https");
	}
    else // not SSL
        {
	  //	bio = BIO_new_connect("google.com:80");
	bio = BIO_new_connect(czServerPort);
	if (bio == NULL) // Was the BIO successfully created?
	    {
	    getSSLErrors("Error Creating BIO ",pczResultBuf,uResultBufSize);
	    logTrace(FN_NAME " (ex) Error creating BIO");
	    return DERR_FILE_OPEN;
	    }
	}
    if (s_bVerbose)
        fprintf(stderr,FN_NAME " connection created\n");
      // First, set up a BIO object. 
      // BIO objects abstract away the socket IO operations 
      // so we don't have to deal with it.
      // as a test we're connecting to google.com on port 80.
    if (BIO_do_connect(bio) <= 0) 
        {
	getSSLErrors("Error Failed to Connect ",pczResultBuf,uResultBufSize);
	if (ctx != NULL)
	    SSL_CTX_free(ctx);  // need to free up the SSL_CTX
	BIO_free_all(bio);
	logTrace(FN_NAME " (ex) Error failed to connect");
	return DERR_FILE_OPEN;
	}

    if (s_bVerbose)
        fprintf(stderr,FN_NAME " connected\n");
    if (ctx != NULL)
        {   // we need to do the SSL handshake, so we can communicate.
	if (BIO_do_handshake(bio) <= 0) 
	    {
	    getSSLErrors("Error failed handshake ",
			   pczResultBuf,uResultBufSize);
	    BIO_free_all(bio);
	    SSL_CTX_free(ctx);
	    logTrace(FN_NAME " (ex) Error handshaking");
	    return DERR_FILE_OPEN;
	    }
	if (s_bVerbose)
	    fprintf(stderr,FN_NAME " handshook\n");
	}
       
    char pczUrl[512] = "";
    if ((pczTarget != NULL) && (strlen(pczTarget) > 0))
        {
	strcpy(pczUrl,pczTarget);
	if ((args != NULL) && (strlen(args) > 0))
	    snprintf(pczUrl+strlen(pczUrl),
		     sizeof(pczUrl)-strlen(pczUrl)-1,"?%s",args);
	}
    char send[1024]; // buffer for the request we'll send to the server
    snprintf(send,sizeof(send),   // Create our GET request.
	    "GET /%s HTTP/1.1\n"
	    "Host:%s\nUser Agent: Mozilla/5.0 "
	    "(compatible; MSIE 9.0; Windows NT 6.1; Trident/5.0)\n"
	     "Connection: Close\n\n",pczUrl,pczServer);
    // BIO_puts sends a null-terminated string to the server. 
    // In this case it's our GET request.
    if (s_bVerbose)
        fprintf(stderr,FN_NAME " about to send |%s|\n",send);
    BIO_puts(bio, send);
    while (1)        // Loop while there's information to be read.
        {
        // BIO_read() reads data from the server into a buffer. 
	// It returns the number of characters read in.
	char buffer[1024]; // buffer for grabbing information from the page.
	memset(buffer, 0, sizeof(buffer));
	int x = BIO_read(bio, buffer, sizeof(buffer) - 1);
	// If we haven't read in anything, assume there's nothing more 
	//to be sent since we used Connection: Close.
	if (x == 0)
	    break;
	// If BIO_read() returns a negative number, there was an error
	else if (x < 0) 
	    {
	    // BIO_should_retry lets us know 
	    // whether we should keep trying to read data or not.
	    if (!BIO_should_retry(bio)) 
	        {
		getSSLErrors("Error Read Failed",pczResultBuf,uResultBufSize);
                BIO_free_all(bio);
		if (ctx != NULL)
		    SSL_CTX_free(ctx);
		logTrace(FN_NAME " (ex) Error reading from network");
                return DERR_FILE_RW;
		}
	    }
	// We actually got some data, without errors!
	else 
	    {
            buffer[x] = 0; // Null-terminate buffer, just in case
	    strncat(pczResultBuf,buffer,
		    uResultBufSize - strlen(pczResultBuf) - 1);
             // Echo what the server sent to the screen
	    iRetval += strlen(buffer);
	    //	    printf("%s", buffer);
	    if (s_bVerbose)
	        fprintf(stderr,FN_NAME " appended %s\n",buffer);
	    logTrace(FN_NAME " Read %s",buffer);
	    }
	}
    BIO_free_all(bio);    // Free up the BIO object we created.
    if (ctx != NULL)
        SSL_CTX_free(ctx);
    if (s_bVerbose)
        fprintf(stderr,FN_NAME " (ex) returns %d\n",iRetval);
    logTrace(FN_NAME " (ex) returns %d",iRetval);
    return iRetval;;
    }

#ifdef NOMORE
/* Submit string of args to our webserver, and retrieve any response
 * into a file
 * @param webhost
 * @param url
 * @param arglist	args to append to url, in name=value&... form
 *			(blanks etc will be fixed up before sending)
 * @param pczFile	name of file where response will be saved
 *			(html header is dropped)
 * @return	>= 0 => OK
 *		-1 => socket or hostname failure
 *		-2 => connect failure
 *		-3 => interruption during receipt
 */
int _SubmitToWebserver(const char * webhost,const char * url,
		       const char * arglist, const char * pczFile)
    {
#undef FN_NAME
#define FN_NAME "internet::_SubmitToWebserver"
#if ! defined __GCC__ 
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2),&wsaData);
#endif
    int iSocket = socket(AF_INET,SOCK_STREAM,0); // -1 => errno has error
    int iRetval = -1;
    int iStat = 0; // socket read status
    struct hostent * server_host = gethostbyname(webhost);
    char czResultBuf[1024];
    if (s_bVerbose)
        fprintf(stderr,FN_NAME 
	        " (en) host='%s' (struct at %p) socket=%d\n\t url='%s' \n\targs=\n\t|%s|\n",
	        webhost,server_host,iSocket,url,arglist);
    logTrace(FN_NAME " (en) host='%s' (struct at %p) socket=%d\n\t url='%s'\n\targs=|%s|",
	     webhost,server_host,iSocket,url,arglist);
    int gfwStat = getFromWeb("https",webhost,url,arglist,
 			     czResultBuf,sizeof(czResultBuf)); 
    if (s_bVerbose)
        fprintf(stderr,FN_NAME " gfwStat=%d result=|%s|\n",gfwStat,czResultBuf);
    logTrace(FN_NAME  " gfwStat=%d result=|%s|",gfwStat,czResultBuf);
    if ((iSocket >= 0) && (server_host != NULL))
        {
	struct sockaddr_in server;
	memset((char *)&server,0,sizeof(struct sockaddr_in));
	server.sin_family = AF_INET;
	server.sin_port = htons(80);
	memcpy((char *)&server.sin_addr.s_addr,
	       (char *)server_host->h_addr,server_host->h_length);
	if (s_bVerbose)
	    fprintf (stderr,"about to connect\n");
	logTrace("    about to connect");
	iStat = connect(iSocket,(struct sockaddr *)&server,sizeof(server));
	iRetval = -2;
	if (iStat <0 )
	    perror("error connecting to web server ");
	else
	    {
	    char buf[1024];
	    BOOL bBody = FALSE;  // suppress HTTP header
	    //	    char args[1024];
	    FILE * outf = fopen(pczFile,"w");
	    iRetval = 0;
	    if (s_bVerbose)
		fprintf(stderr,FN_NAME " connected to %s\n",webhost);
	    logTrace(FN_NAME "    connected to %s",webhost);
	    sprintf(buf,"GET /%s?%s HTTP/1.1\r\nHost: %s\r\n\r\n",url,arglist,webhost);
#if defined __GCC__ 
	    write(iSocket,buf,strlen(buf));
#else
	    iStat = send(iSocket,buf,strlen(buf),0);
#endif
	    if (s_bVerbose)
		fprintf(stderr,"\nsent '%s'\n",buf);
	    logTrace("    sent '%s' status=%d",buf,iStat);
	    while(1)
	        {
		memset(buf,0,sizeof(buf));
#if defined __GCC__ 
		iStat = read(iSocket,buf,sizeof(buf)-1);
#else
		iStat = recv(iSocket,buf,sizeof(buf)-1,0);
#endif
		if (s_bVerbose)
		    fprintf(stderr,"socket read status = %d\n",iStat);
		if (iStat < 0)
		    {
		    iRetval = -3;
		    perror("Read interrupted");
		    }
		if (iStat <= 0)
		    break;
		char * pBody = strstr(buf,"<body>");
		// char * pBody = buf;
		if (pBody != NULL)
		    bBody = TRUE;
		if (! bBody)
		    {
		    if (s_bVerbose)
		        fprintf(stderr,"No body yet: buf='%s'\n",buf);
		    continue;
		    }
		if (pBody == NULL)  // this is successive page
		    pBody = buf;
		if (s_bVerbose)
		    fprintf(stderr,FN_NAME " got %d chars: '%s'\n",iStat,pBody);
		logTrace(FN_NAME "    got %d chars: '%s'",iStat,pBody);
		char * pEndBody = strstr(pBody,"</body>\n");
		if (pEndBody != NULL)
		    {
		    *(pEndBody+strlen("</body>\n")) = '\0'; // truncate
		    }
		/* we have weird error of a "\rjunk\r" interpolated somewhere
		 * into the data - so we remove it - ktr 2007-3-27 */
		char * pStartBad = strchr(pBody,'\r');
		if (s_bVerbose)
		    fprintf(stderr,FN_NAME " pStartBad is %p '%s'\n",
			    pStartBad,NN(pStartBad));
		logTrace(FN_NAME " pStartBad is %p '%s'\n", pStartBad,NN(pStartBad));
		if (pStartBad != NULL)
		    {                 
		    const char * pEndBad = strchr(pStartBad+1,'\r');
		    const char * pNewLine = strchr(pStartBad+2,'\n');
		    int badlen = (pEndBad != NULL) ? pEndBad-pStartBad : 0;
		    if (s_bVerbose)
  		        fprintf(stderr,FN_NAME " pNewLine=%p pEndBad is %p (%d) '%s'\n",
				pNewLine,pEndBad,badlen,NN(pEndBad));
          	    logTrace(FN_NAME " pNewLine=%p pEndBad is %p (%d) '%s'\n",
			     pNewLine,pEndBad,badlen,NN(pEndBad));
		    if ((pEndBad != NULL) 
			&& ((pNewLine == NULL) || (pNewLine > pEndBad)) // no embedded \n
			&& (badlen < 10))  // ad-hoc number
		        {
			if ((*pEndBad > '\0') && (*pEndBad < ' ')) //<lf>?
			    pEndBad++;
			if ((*pEndBad > '\0') && (*pEndBad < ' ')) //<cr>?
			    pEndBad++;
			uint jj=0;
			for (jj=0; jj<=strlen(pEndBad); jj++)
			    *pStartBad++ = *(pEndBad+jj);
			}
		    }
		if (s_bVerbose)
  		    fprintf(stderr,FN_NAME " writing to file\n%s\n",pBody);
		fwrite(pBody,strlen(pBody),1,outf);
		if (pEndBody != NULL)
		    break;
		}
	    fclose(outf);
	    }
#if defined __MINGCC__ 
	closesocket(iSocket);
#endif
	}
    else // in mingw, h_errno is WSAGetLastError
        {
	if (s_bVerbose)
	    fprintf (stderr,FN_NAME " error %d creating socket %d or locating server=%p\n",
		     h_errno,iSocket,server_host);
	logTrace(FN_NAME 
		 "error %d creating socket %d or locating server=%p",
	         h_errno,iSocket,server_host);
        }
    if (s_bVerbose)
        fprintf(stderr,FN_NAME " (ex) returning %d\n",iRetval);
    logTrace(FN_NAME " (ex) returning %d socket status=%d",
	     iRetval,iStat);
    return iRetval;
    }

#endif // #ifdef NOMORE
#ifdef NOMORE
/* Notify web server to send email about re-register problem
 * @param pczFile	name of file where response will be saved
 *			(html header is dropped)
 * @param pczSN		 serial number; must be supplied
 * @param pczLanguage	 abbreviation for language, or NULL
 * @param pczMachineCode maybe NULL?
 * @param pczName
 * @param pczOrganization
 * @param pczEmail
 * @return	>= 0 => OK
 *		-1 => socket or hostname failure
 *		-2 => connect failure
 *		-3 => interruption during receipt
 */
int SendEmailViaWebserver(const char * webhost,const char * url,
			  const char * pczFile, const char * pczAction,
			  const char * pczSN, const char * pczLanguage,
			  const char * pczMachineCode,
			  const char * pczFirstName, 
			  const char * pczFamilyName, 
			  const char * pczOrganization,
			  const char * pczEmail,const char * pczError)
    {
    char args[1024];
    snprintf(args,sizeof(args),"action=%s&sn=%s%s%s%s%s&firstname=%s&familyname=%s&email=%s&error=%s",
	     pczAction,pczSN,
	     (pczLanguage!=NULL) ? "&lang=" : "",
	     (pczLanguage!=NULL) ? pczLanguage : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? "&code=" : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? pczMachineCode : "",
	     //	     (pczMachineCode!=NULL) ? "&code=" : "",
	     //(pczMachineCode!=NULL) ? pczMachineCode : "",
	     pczFirstName,pczFamilyName,pczEmail,pczError);
    while (strchr(args,' ') != NULL)
        *strchr(args,' ') = '~';  // protect blanks from htmlizing
    return _SubmitToWebserver(webhost,url,args,pczFile);
    }

#endif // #ifdef NOMORE
#ifdef NOMORE
/* @param pczSN		 serial number; must be supplied
 * @param pczLanguage	 abbreviation for language, or NULL
 * @param pczMachineCode maybe NULL?
 * @return	>= 0 => OK
 *		-1 => socket or hostname failure
 *		-2 => connect failure
 *		-3 => interruption during receipt
 */
int GetFromWebserver(const char * webhost,const char * url,
		     const char * pczFile,
		     const char * pczSN, const char * pczLanguage,
		     const char * pczMachineCode)
    {
    char args[1024];
    logTrace("internet::GetFromWebServer (en)");
    snprintf(args,sizeof(args),"sn=%s%s%s%s%s",
	     pczSN,
	     (pczLanguage!=NULL) ? "&lang=" : "",
	     (pczLanguage!=NULL) ? pczLanguage : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? "&code=" : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? pczMachineCode : "");
    //		     (pczMachineCode!=NULL) ? "&code=" : "",
    //		     (pczMachineCode!=NULL) ? pczMachineCode : "");
    while (strchr(args,' ') != NULL)
        *strchr(args,' ') = '~';  // protect blanks from htmlizing
    return _SubmitToWebserver(webhost,url,args,pczFile);
    }

#endif // #ifdef NOMORE
#ifdef NOMORE
/* Submit user-supplied info to be recorded in DB.
 * Unless there is a DB or network failure, there is no
 * possibility of error.
 * @param pczFile	 temporary file with results from web
 * @param pczSN		 serial number; must be supplied
 * @param pczLanguage	 abbreviation for language, or NULL
 * @param pczMachineCode maybe NULL?
 * @param pczFirstName, pczFamilyName
 * @param pczOrganization
 * @param pczEmail
 * @return	>= 0 => OK
 *		-1 => socket or hostname failure, or connect failure
 *		-3 => interruption during receipt
 */
int SubmitToWebserver(const char * webhost,const char * url,
		      const char * pczFile,
		      const char * pczSN, const char * pczLanguage,
		      const char * pczMachineCode,
		      const char * pczFirstName, const char * pczFamilyName,
		      const char * pczOrganization,
		      const char * pczEmail,const char * pczError)
    {
#undef FN_NAME
#define FN_NAME "internet::SubmitToWebServer"
    char args[1024];
    snprintf(args,sizeof(args),"action=livecommit&sn=%s%s%s%s%s%s%s%s%s%s%s%s%s"
	     "&error=%s",
	     pczSN,
	     (pczLanguage!=NULL) ? "&lang=" : "",
	     (pczLanguage!=NULL) ? pczLanguage : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? "&code=" : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? pczMachineCode : "",
	     //	     (pczMachineCode!=NULL) ? "&code=" : "",
	     //(pczMachineCode!=NULL) ? pczMachineCode : "",
	     (pczOrganization!=NULL) ? "&org=" : "",
	     (pczOrganization!=NULL) ? pczOrganization : "",
	     (pczFirstName!=NULL) ? "&firstname=" : "",
	     (pczFirstName!=NULL) ? pczFirstName : "",
	     (pczFamilyName!=NULL) ? "&familyname=" : "",
	     (pczFamilyName!=NULL) ? pczFamilyName : "",
	     (pczEmail!=NULL) ? "&email=" : "",
	     (pczEmail!=NULL) ? pczEmail : "",
	     (pczError != NULL) ? pczError : "");
    while (strchr(args,' ') != NULL)
        *strchr(args,' ') = '~';  // protect blanks from htmlizing
    char czResultBuf[1024];
//    if (s_bVerbose)
    //       fprintf(stderr,FN_NAME 
//	        " (en) host='%s' (struct at %p) socket=%d\n\t url='%s' \n\targs=\n\t|%s|\n",
    //        webhost,server_host,iSocket,url,arglist);
    // logTrace(FN_NAME " (en) host='%s' (struct at %p) socket=%d\n\t url='%s'\n\targs=|%s|",
//	     webhost,server_host,iSocket,url,arglist);
    int gfwStat = getFromWeb("https",
			     (webhost != NULL) ? webhost : SERVER,
			     (url != NULL) ? url : SCRIPT_PAGE,
			     args,czResultBuf,sizeof(czResultBuf)); 
    int iRetval = (gfwStat > 0) ? 0
		: (gfwStat == DERR_FILE_OPEN) ? -1
		: -3;
    if (s_bVerbose)
        fprintf(stderr,FN_NAME " gfwStat=%d result=|%s|\n",gfwStat,czResultBuf);
    logTrace(FN_NAME  " gfwStat=%d result=|%s|",gfwStat,czResultBuf);
//    return _SubmitToWebserver((webhost != NULL) ? webhost : SERVER ,
//			      (url != NULL) ? url : SCRIPT_PAGE,args,pczFile);
    return iRetval;
    }
#endif // #ifdef NOMORE

#ifdef NOTMOVED // to SSDp for OpenDragon only
int sendProbableErrorEmail(UI * uiObject, const char * filename, const char * pczAction,
			    const char * pSN, const char * pczLanguage,
			    const char * pCalcMachine,
			    const char * firstname,const char * familyname, 
			    const char * organization,
			    const char * email,const char * errorStat)
    {
    int iStat = SendEmailViaWebserver(SERVER,SCRIPT_PAGE,filename,pczAction,
				      pSN,pczLanguage,pCalcMachine,
				      firstname, familyname,organization, email, errorStat);
    if (iStat == 0)
        {
	int fsize = file_size(filename);
	char * filebuf = (char *)calloc(fsize,1);
	if (filebuf != NULL)
	    {
	    rsf(filename,filebuf,fsize,0,0);
	    if (s_bVerbose)
	        fprintf(stderr,"\nsendProbableErrorEmail received from server: '%s'\n",filebuf);
	    const char * msgs[10];
	    const char * keys[10];
				//char * pError = strstr(filebuf,"error=");
	    BOOL bMessages = parseMessagesBuf(filebuf,keys,msgs,AY_COUNT(msgs));
	    if (bMessages) // show any error messages
	        uiObject->I18NMessageBox(NULL,msgs,1);
	    free(filebuf);
	    }
	}
    else
        { 
	const char * msgs[] = { "%h29.11",NULL } ;
//			      {"Error connecting to internet server at this time. ",
//			       "Email not sent. Please try again later",
//			       NULL};
	uiObject->I18NMessageBox(NULL,msgs,1);
	return 1;
	}
    return 1;
    }

int sendDownloadRequest(UI * uiObject, const char * filename,
			 const char * pSN, const char * pczLanguage,
			 const char * pczMachineCode,
			 const char * pczFirstName, const char * pczFamilyName,
			 const char * organization,
			 const char * pczEmail,const char * pczError)
    {
    char args[1024];
    snprintf(args,sizeof(args),"action=livedownload&sn=%s%s%s%s%s"
	     "&firstname=%s&familyname=%s&email=%s&error=%s",
	     pSN,
	     (pczLanguage!=NULL) ? "&lang=" : "",
	     (pczLanguage!=NULL) ? pczLanguage : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? "&code=" : "",
	     ((pczMachineCode!=NULL)&&(strlen(pczMachineCode)>0))
	         ? pczMachineCode : "",
	     pczFirstName,pczFamilyName,pczEmail,pczError);
    while (strchr(args,' ') != NULL)
        *strchr(args,' ') = '~';  // protect blanks from htmlizing
    int iStat = _SubmitToWebserver(SERVER,DOWNLOAD_PAGE,args,filename);
    if (iStat == 0)
        {
	int fsize = file_size(filename);
	char * filebuf = (char *)calloc(fsize,1);
	if (filebuf != NULL)
	    {
	    rsf(filename,filebuf,fsize,0,0);
	    if (s_bVerbose)
	        fprintf(stderr,"\nsendDownloadRequest received from server: '%s'\n",filebuf);
	    const char * msgs[10];
	    const char * keys[10];
				//char * pError = strstr(filebuf,"error=");
	    BOOL bMessages = parseMessagesBuf(filebuf,keys,msgs,AY_COUNT(msgs));
	    if (bMessages) // show any error messages
	        uiObject->I18NMessageBox(NULL,msgs,1);
	    free(filebuf);
	    }
	}
    else
        { 
	const char * msgs[] = { "%h29.11",NULL } ;
//			      {"Error connecting to internet server at this time. ",
//			       "Please try again later",
//			       NULL};
	uiObject->I18NMessageBox(NULL,msgs,1);
	return 1;
	}
    return 1;
    }
#endif // ifdef NOTMOVED // to SSDp for OpenDragon only

#ifdef NOMORE
// parse string returned by web server, looking for message(s)
// to display
// @param buffer	buffer to parse. Gets changed (tokenized)
// @param ppKeys	array of strings for keys
// @param ppMsgs	array of strings for messages
// @param aySize	size of above arrays
// @return		TRUE if any messages
BOOL parseMessagesBuf(char * buffer, const char ** ppKeys, const char ** ppMsgs, int aySize)
    {
    char * pKey = strstr(buffer,"key=");
    char * pMsg = strstr(buffer,"msg=");
    BOOL bMessages = FALSE;
    if (s_bVerbose)
        fprintf(stderr,"parsing %p='%s'\n",pMsg,NN(pMsg));
    logTrace("parsing %p='%s'",pMsg,NN(pMsg));
    if (pKey != NULL)
        {
	strtok(pKey,"\n\r");
	pKey += strlen("key=");
	if (s_bVerbose)
	    fprintf(stderr,"pKey='%s'\n",pKey);
	ppKeys[0] = pKey;  //~~~ actually need array; not currently used
	}
    if (s_bVerbose)
        fprintf(stderr,"parsing2 %p='%s'\n",pMsg,NN(pMsg));
    if (pMsg != NULL)
        {
	int j = 0;
	bMessages = TRUE;
	while ((pMsg != NULL) && (j < aySize))
	    {
	    char * pTok = pMsg + strlen("msg=");
	    ppMsgs[j] = pTok;
	    pMsg = strstr(pTok,"msg=");
	    strtok(pTok,"\n\r");
	    if (s_bVerbose)
	        fprintf(stderr,"pMsg %d: %p='%s'; next=%p='%s'\n",
			j,pTok,NN(pTok),pMsg,NN(pMsg));
	    logTrace("pMsg %d: %p='%s'; next=%p='%s'",
		     j,pTok,NN(pTok),pMsg,NN(pMsg));
	    ppMsgs[++j] = NULL;
	    }
	}
    if (s_bVerbose)
        fprintf(stderr,"\n");
    return bMessages;
    }
#endif // #ifdef NOMORE

#ifdef NOTMOVED // to SSDp for OpenDragon only
/* put up a box asking for user org, name, and email
 * using a list of orgs supplied by the server
 */
int getUserInfo(UI * uiObject,const char * filename,
		 const char * pSN, const char * pczLanguage,
		 char * firstName,uint firstNameSz,
		 char * familyName,uint familyNameSz,
		 char * organization,uint organizationSz,
		 char * email,uint emailSz,
		 char * errorStat, uint errorStatSz)
    {
    char action[10];
    int iStat = 0;
    //uiObject->showTextMessageBox("Waiting","","Connecting to internet...");
    logTrace("internet::getUserInfo (en)");
    iStat = GetFromWebserver(SERVER,SCRIPT_PAGE,CommFileName(REGFILE),
			     pSN,pczLanguage,"");
    //    sleep(2);
    //uiObject->sendMsgKill();
    if (iStat < 0) //  server failure - show an error message
        {
	const char * msgs[] = { "%h29.11",NULL } ;
//		  {"Unable to connect to internet server at this time. ",
//		   "Please try again later",
//		   NULL};
	uiObject->I18NMessageBox(NULL,msgs,1);
	return 1;
	}
    int fsize = file_size(filename);
    char * filebuf = (char *)calloc(fsize,1);
    action[0] = firstName[0] = familyName[0] = organization[0] = email[0] = errorStat[0] = '\0';
    if (filebuf != NULL)
        {
	rsf(filename,filebuf,fsize,0,0);
	if (s_bVerbose)
	    fprintf(stderr,"received from server: '%s'\n",filebuf);
	logTrace("internet::getUserInfo received from server:\n\t'%s'\n\t",filebuf);
	char * pOrgList = strstr(filebuf,"orglist=");
	char * pError = strstr(filebuf,"error=");
	const char * msgs[10];
	const char * keys[10];
	BOOL bMessages = parseMessagesBuf(filebuf,keys,msgs,AY_COUNT(msgs));
	logTrace("internet::getUserInfo parseresults: pError=%p pOrgList=%p",
		 pError,pOrgList);
	if (pError != NULL)
	    {
	    strtok(pError,"\n\r");
	    pError += strlen("error=");
	    if (s_bVerbose)
	        fprintf(stderr,"pError='%s'\n",pError);
	    strcpy_array(errorStat,pError);
	    }
	if (pOrgList != NULL)
	    {
	    char pczSubstitutions[100];
	    ATTRIBUTE_t ReplyAttributes[] = 
	      {
	        {"action",sizeof(action)-1},
		{"orgCombo",organizationSz-1},
		{"firstNameField",firstNameSz-1},
		{"familyNameField",familyNameSz-1},
		{"emailField",emailSz-1},
	      } ;
	    ReplyAttributes[0].pczValueBuf = action;
	    ReplyAttributes[1].pczValueBuf = organization;
	    ReplyAttributes[2].pczValueBuf = firstName;
	    ReplyAttributes[3].pczValueBuf = familyName;
	    ReplyAttributes[4].pczValueBuf = email;
	    strtok(pOrgList,"\n\r");
	    pOrgList += strlen("orglist=");
//	    if (s_bVerbose)
//	        fprintf(stderr,"pOrgList='%s'\n",pOrgList);
//	    logTrace("pOrgList='%s'",pOrgList);
	    snprintf(pczSubstitutions,sizeof(pczSubstitutions),
		     "%s|%s",PRODUCT,"organization");
	    iStat = uiObject->DoRegister(pczSubstitutions,pOrgList,
					 TRUE, ReplyAttributes, 
					 AY_COUNT(ReplyAttributes)) ;
	    if (bMessages && (iStat == 0)) // show any error messages
	        uiObject->I18NMessageBox(NULL,msgs,1);
	    }
	else
	    {   // no orgs - must be a server failure
	    const char * msgs[] = { "%h29.11",NULL } ;
//	   		 {"Problem with internet server. ",
//			     "Please try again later",
//			     NULL};
	    uiObject->I18NMessageBox(NULL,msgs,1);
	    return 1;
	    }
	free(filebuf);
	}
    if (s_bVerbose)
        fprintf(stderr,"DoRegister returns status=%d action='%s' name='%s %s' org='%s' "
		"email='%s'\n", 
		iStat,action,firstName,familyName,organization,email);
    logTrace("internet::getUserInfo (ex) returns status=%d",iStat);
    return iStat;
    }
#endif // ifdef NOTMOVED // to SSDp for OpenDragon only

/* Extract string returned from web app, split, and
 * put into supplied buffers
 * String format is <spell>valcode,valdate</spell>
 *               or <error>message</error>
 * @param pczValCode 	buffer at least 28 chars long
 * @param pczValDate	buffer at least 12 chars long
 * @param pczErrbuf	where to put an error message
 * @param uErrbufLen	size of error buffer
 * @param pczHtmlBuf	data obtained from web
 * @return		0 if OK
 *			else -1 if found error msg from web
 *			else -2 if format error
 *			else -3 if unknown error
 */
int extractSpell(char * pczValCode, char * pczValDate, char * pczErrbuf, uint uErrbufLen,
                 const char * czHtmlBuf)
    {
    const char * pValidation = strstr(czHtmlBuf,"<spell>");
    const char * pValidationEnd = strstr(czHtmlBuf,"</spell>");
    const char * pFail = strstr(czHtmlBuf,"<error>");
    const char * pFailEnd = strstr(czHtmlBuf,"</error>");
    int iStat = -3;
    if ((pValidation != NULL) && (pValidationEnd != NULL)
	&& (pValidationEnd > (pValidation+strlen("<spell>"))))
	{
	pValidation += strlen("<spell>");
	const char * pComma = strchr(pValidation,',');
	if ((pComma == NULL) || (pComma - pValidation >= VALCODE_LEN))
	    return -2;
	uint uVlen = (uint)(pComma-pValidation);
	strncpy(pczValCode,pValidation,uVlen);
	pComma++;
	uVlen = (uint)(pValidationEnd - pComma);
	if (uVlen >= VALDATE_LEN)
	    return -2;
	strncpy(pczValDate,pComma,uVlen);
	iStat = 0;
	}
    else if ((pFail != NULL) && (pFailEnd != NULL)
	&& (pFailEnd > (pFail+strlen("<error>"))))
	{
	pFail += strlen("<error>");
	uint uVlen = (uint)(pFailEnd-pFail);
	if (uVlen > uErrbufLen-1)
	    uVlen = uErrbufLen-1;
	strncpy(pczErrbuf,pFail,uVlen);
	iStat = -1;
	}
    else
	{
	}
    if (s_bVerbose)
	fprintf(stdout,"setup returns %d pVal=%p pValEnd=%p pFali=%p\n",
	    iStat,pValidation,pValidationEnd,pFail);
    return iStat;
    }

#ifdef NOMORE
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
#endif // #ifdef NOMORE

void INTERNET_END() { puts(FIL_ID); }

// we need a separate executable to be spawned by setup.exe for Windows7
#if defined BUILD_ASK

void usage(const char * err)
        {
//	fprintf(stderr, "Usage: ask [-action action -sn serialno -machine code -exe executable -o file\n");
//	fprintf(stderr, "    -action  one of 'livecommit', \n");
//	fprintf(stderr, "    -sn      the serial number\n");
//	fprintf(stderr, "    -exe     one of 'setup',\n");
//	fprintf(stderr, "    -machine calculated machine code\n");
//	fprintf(stderr, "    -o       file to write string from internet\n");
	exit(1);
	}

int main(int argc, char **argv)
    {
    BOOL bVerbose = FALSE;
    int iStat = 1;
    char * pAction = NULL;
    char * pSN = NULL;
    char * pMachine = NULL;
    char * pExe = NULL;
    char * pOutFile = NULL;
    int rc=0;
    while(++rc < argc)
        {
//	printf(" arg %s\n",argv[rc]);
	if (strcmp(argv[rc],"-action") == 0)
	    pAction = strdup(argv[++rc]);
	else if (strcmp(argv[rc],"-sn") == 0)
	    pSN = strdup(argv[++rc]);
	else if (strcmp(argv[rc],"-exe") == 0)
	    pExe = strdup(argv[++rc]);
	else if (strcmp(argv[rc],"-machine") == 0)
	    pMachine = strdup(argv[++rc]);
	else if (strcmp(argv[rc],"-o") == 0)
	    pOutFile = strdup(argv[++rc]);
	else
	    usage("Unknown argument");
	}
    char czArgsBuf[2096] = "";
    char czResultBuf[2096] = "";
    if ((pAction == NULL) || (pSN == NULL) || (pExe == NULL)
	    || (pMachine == NULL) || (pOutFile == NULL))
	return iStat; 
    snprintf(czArgsBuf,sizeof(czArgsBuf),
	     "action=%s&sn=%s&machine=%s&exe=%s",pAction,pSN,pMachine,pExe);
    int iWebStat = getFromWeb("https", SERVER, SCRIPT_PAGE,czArgsBuf,
			        czResultBuf,sizeof(czResultBuf),FALSE);
//	printf("internet from dragon status=%d text=%s\n",iWebStat,czResultBuf);
    if (iWebStat > 0)  // success
	{
	FILE * OF = fopen(pOutFile,"w");
	if (OF != NULL)
	    {
	    fprintf(OF,"%s\n",czResultBuf);
	    iStat = fclose(OF);
	    }
	}
    return iStat;
    }
#endif // #if defined BUILD_ASK

#if defined TEST

void usage(const char * name)
        {
	fprintf(stderr, "Usage: %s [-m serialnumber valdate [ -c machinecode] | -s | -b] [-v]\n", name);
	fprintf(stderr, "    -s       test submit to webserver\n");
	fprintf(stderr, "    -m       show the machine code and SHA1 - requires SN, ValDate\n");
	fprintf(stderr, "    -c       provide a machine code for SHA1 calculations else use default\n");
	fprintf(stderr, "    -b       load ssh libs only (do not use them)\n");
	fprintf(stderr, "    -v       for verbose\n");
	exit(1);
	}

// create a unit test version.
// This isn't used in the system, so adapt the code as needed
// during testing
int main(int argc, char **argv)
    {
    int rc = 0;
    int iOp = 0;  // 'm' or 's'
//    int iStatus = 0;
    BOOL bVerbose = FALSE;
    printf("internet.TEST v 0.1\n");
    char * pSN = NULL;
    char * pCalcMachine = NULL;
    char * pValDate = NULL;
    while(++rc < argc)
        {
//	printf(" arg %s\n",argv[rc]);
	if (strcasecmp(argv[rc],"-v") == 0)
	    {
	    bVerbose = TRUE;
	    EnableVerbose(TRUE);
	    }
	else if (strcasecmp(argv[rc],"-s") == 0)
	    iOp = 's';
	else if (strcasecmp(argv[rc],"-m") == 0)
	    {
	    iOp = 'm';
	    pSN = strdup(argv[++rc]);
	    pValDate = strdup(argv[++rc]);
	    }
	else if (strcasecmp(argv[rc],"-c") == 0)
	    {
	    pCalcMachine = strdup(argv[++rc]);
	    }
	else if (strcasecmp(argv[rc],"-b") == 0)
	    iOp = 'b';
	else
	    usage(argv[0]);
	}
    if (bVerbose)
        fprintf(stderr,"main() about to test -%c\n",iOp);
//    if ((iOp == 's') || (iOp == 'b'))
    if (iOp == 'b') /* just test loading them; 
		     * getFromWeb() does this automatically */
	{
	SSL_load_error_strings();                /* readable error messages */
        fprintf(stderr,"main() SSL_load_error_strings finished\n");
	SSL_library_init();
        fprintf(stderr,"main() SSL_library_init finished\n");
	ERR_load_BIO_strings(); // Load BIO error strings
        fprintf(stderr,"main() ER_load_BIO_stingss finished\n");
	OpenSSL_add_all_algorithms(); // Load all available encryption algorithms
        fprintf(stderr,"main() SSL_add_all_algorithms finished\n");
	}
    if (iOp == 'm')
	{
	if (pCalcMachine == NULL)
	    pCalcMachine = strdup(SSDb::CalcMachineCode(bVerbose));
	byte shabuf[22];
	memset(shabuf,0,sizeof(shabuf));
	if (pSN == NULL)
	    {
	    printf("Error: Serial number not specifiied\n");
	    exit(1);
	    }
	if (pValDate == NULL)
	    {
	    printf("Error ValDate not specified\n");
	    exit(1);
	    }
	const char * sha1str = SSDb::CalcValCode(pCalcMachine, pSN,pValDate);
#ifdef NOMORE
	char basestr[1024];
	char mimebuf[30];
	sprintf(basestr,"%s%sarchaeopteryx",pSN,pCalcMachine);
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
#endif // #ifdef NOMORE
	printf("internet machine code = %s sha=%s\n",pCalcMachine,sha1str);
	}
    else if (iOp == 's')
	{
	const char * pCalcMachine = SSDb::CalcMachineCode(bVerbose);
//	iStatus = SubmitToWebserver(SERVER,SCRIPT_PAGE,
//				      "dragon.msg",
//				      "G5Cxxxx","EN",pCalcMachine,
//				      "Kurt","Rudahl","GRS", 
//				      "ktr", "asdfas");
//	printf("internet SubmitToWebserver calc='%s' returns status=%d\n",
//	    pCalcMachine,iStatus);
	char czArgsBuf[2096] = "";
	char czResultBuf[2096] = "";
	// exeCode is 'setup' or 'dragon' or '' (if from a eb form; not supported)
	// if email empty then they don't want notifications 
	snprintf(czArgsBuf,sizeof(czArgsBuf),
	         "sn=G5Cxxxx&machine=%s&email=abc@rornmail.org&exeCode=setup",
	         pCalcMachine);
	int iWebStat = getFromWeb("https","www.google.com",NULL,"",
	    czResultBuf,sizeof(czResultBuf),TRUE);
	printf("internet from google status=%d text=%s\n",iWebStat,czResultBuf);
	iWebStat = getFromWeb("https", SERVER, SCRIPT_PAGE,czArgsBuf,
	    czResultBuf,sizeof(czResultBuf),FALSE);
	printf("internet from dragon status=%d text=%s\n",iWebStat,czResultBuf);
	if (iWebStat > 0)  // success
	    {
	    char czValCode[VALCODE_LEN+1] = "";
	    char czValDate[VALDATE_LEN+1] = "";
	    memset(czValCode,0,sizeof(czValCode));
	    memset(czValDate,0,sizeof(czValDate));
	    char czErrbuf[1024];
	    iWebStat = extractSpell(czValCode,czValDate,czErrbuf,sizeof(czErrbuf),
		                 czResultBuf);
	    }
	}
    else
	printf("No tests specified\n");
    }
#endif // TEST
