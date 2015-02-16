/* 
 *      filename internet.h
 *        $Id: internet.h,v 1.5 2012/04/15 04:46:45 rudahl Exp $
 *
 *      ~~ Copyright 2005-2012 Kurt Rudahl and Sally Goldin
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
 *******************************************************************
 *
 * $Id: internet.h,v 1.5 2012/04/15 04:46:45 rudahl Exp $
 * $Log: internet.h,v $
 * Revision 1.5  2012/04/15 04:46:45  rudahl
 * support internet licensing
 *
 * Revision 1.4  2008/06/27 03:35:09  rudahl
 * work on network license
 *
 * Revision 1.3  2008/06/26 09:46:28  rudahl
 * revising internet
 *
 * Revision 1.2  2008/04/26 10:57:02  rudahl
 * improved notices
 *
 * Revision 1.1  2006/02/26 11:52:09  rudahl
 * working on registration
 *
 * Revision 1.1  2006/02/24 13:56:30  rudahl
 * working on registration
 *
 *
 ****************************************************************
 * 
 *      This header file defines strings customized to OpenDragon's 
 *	internet server, plus prototypes for internet.cpp
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.8	2006-2-24 ktr	extracted from SSDp.h
 ********************************************************************
 */

#ifndef INTERNET_H
#define INTERNET_H

#define INSTALL_SPACE 100  // installed disk space in MB
#define TMP_SPACE 250	   // disk space needed during install in MB
#define REGFILE "register.tmp"

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
	       size_t uResultBufSize,BOOL bInitLibrary=FALSE); 

// parse string returned by web server, looking for message(s)
// to display
// @param buffer	buffer to parse. Gets changed (tokenized)
// @param ppKeys	array of strings for keys
// @param ppMsgs	array of strings for messages
// @param aySize	size of above arrays
// @return		TRUE if any messages
BOOL parseMessagesBuf(char * buffer, const char ** ppKeys, const char ** ppMsgs, int aySize);

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
		       const char * arglist, const char * pczFile);

/* Notify web server to send email about re-register problem
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
			  const char * pczEmail,const char * pczError);

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
		     const char * pczMachineCode);

/* Submit user-supplied info to be recorded in DB.
 * Unless there is a DB or network failure, there is no
 * possibility of error.
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
int SubmitToWebserver(const char * webhost,const char * url,
		      const char * pczFile,
		      const char * pczSN, const char * pczLanguage,
		      const char * pczMachineCode,
		      const char * pczFirstName, const char * pczFamilyName,
		      const char * pczOrganization,
		      const char * pczEmail,const char * pczError);

#ifdef NOTMOVED // to SSDp for OpenDragon only
int sendProbableErrorEmail(UI * uiObject, const char * filename, const char * pczAction,
			    const char * pSN, const char * pczLanguage,
			    const char * pCalcMachine,
			    const char * firstname,const char * familyname, 
			    const char * organization,
			    const char * email,const char * errorStat);

int sendDownloadRequest(UI * uiObject, const char * filename,
			 const char * pSN, const char * pczLanguage,
			 const char * pczMachineCode,
			 const char * pczFirstName, const char * pczFamilyName,
			 const char * organization,
			 const char * pczEmail,const char * pczError);

/* put up a box asking for user org, name, and email
 * using a list of orgs supplied by teh server
 */
int getUserInfo(UI * uiObject,const char * filename,
		 const char * pSN, const char * pczLanguage,
		 char * firstName,uint firstNameSz,
		 char * familyName,uint familyNameSz,
		 char * organization,uint organizationSz,
		 char * email,uint emailSz,
		 char * errorStat, uint errorStatSz);
#endif // ifdef NOTMOVED // to SSDp for OpenDragon only

/* check a ValCode supplied by the user and format it for the DB
 * @param pUserValCode
 * @return		NULL if invalid, or 8-char hex string
 */
const char * extractValCode(const char * buf);

#define VALCODE_LEN 28
#define VALDATE_LEN 12

/* Extract string returned from web app, split, and
 * put into supplied buffers
 * String format is <spell>valcode,valdate</spell>
 *               or <error>message</error>
 * @param pValCode 	buffer at least 28 chars long
 * @param pValDate	buffer at least 12 chars long
 * @param pczHtmlBuf	data obtained from web
 * @param pczErrbuf	where to put an error message
 * @param uErrbufLen	size of error buffer
 * @return		0 if OK
 *			else -1 if found error msg from web
 *			else -2 if format error
 *			else -3 if unknown error
 */
int extractSpell(char * pczValcode, char * pczDate, char * pczErrbuf, uint uErrbufLen,
                 const char * pczHtmlBuf);

void EnableVerbose(BOOL bVerbose);

#endif

