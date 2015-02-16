#include "drelease.h"
char IPCXMLGEN_ID[]
   ="\0@(#) " __FILE__ " $$Revision: 1.19 $$Date: 2014/12/06 10:47:50 $";
D_REL_IDSTR;
/*
 *	filename IpcXmlGen.c
 *		$Id: IpcXmlGen.c,v 1.19 2014/12/06 10:47:50 rudahl Exp $	
 *
 *      ~~ Copyright 2001-2014 Kurt Rudahl and Sally Goldin
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
 *  $Log: IpcXmlGen.c,v $
 *  Revision 1.19  2014/12/06 10:47:50  rudahl
 *  no significant differences between DragonProf and OpenDragon
 *
 *  Revision 1.18  2007/05/19 11:19:04  rudahl
 *  chamge tmpnam to tempnam
 *
 *  Revision 1.17  2006/11/30 08:41:40  goldin
 *  Add new report generation functions for multi simple table category of report
 *
 *  Revision 1.16  2006/01/20 08:59:35  rudahl
 *  improved error logging
 *
 *  Revision 1.15  2005/04/25 13:55:53  goldin
 *  Add trace msg
 *
 *  Revision 1.14  2005/04/25 10:50:25  rudahl
 *  added test of large files
 *
 *  Revision 1.13  2005/04/25 05:05:45  rudahl
 *  added test caseto IpcXmlGen
 *
 *  Revision 1.12  2005/04/24 10:53:12  goldin
 *  Add more tracing
 *
 *  Revision 1.11  2005/03/30 10:56:00  rudahl
 *  small adaptations for MFC60/viewport
 *
 *  Revision 1.10  2005/02/16 04:14:00  rudahl
 *  adapt to GCC/MINGW differences
 *
 *  Revision 1.9  2005/02/09 13:36:28  goldin
 *  Update file comment block and includes in preparation 
 *  for move to RSGISProject
 *
 *  Revision 1.8  2004/12/23 12:06:07  rudahl
 *  lint-ish fix
 *
 *  Revision 1.7  2004/12/11 10:15:15  rudahl
 *  lintish fix
 *
 *  Revision 1.6  2004/11/30 04:31:44  rudahl
 *  adapt for Mingw
 *
 *  Revision 1.5  2002/04/18 00:21:36  goldin
 *  modify to remove quotes in textreport
 *
 *  Revision 1.4  2002/01/10 22:26:39  rudahl
 *  fixed bug in const attrib
 *
 *  Revision 1.3  2002/01/10 13:16:05  goldin
 *  Add function to replace XML reserved chars in report data
 *
 *  Revision 1.2  2001/10/17 15:52:04  goldin
 *  Added new methods for generating Category-based result fields
 *
 *  Revision 1.1  2001/08/23 18:03:20  goldin
 *  Move Xml report methods to new Ipc module IpcXmlGen
 ****************************************************************
 * 
 *    Base functions to construct XML-based reports (calcResults) 
 *    to be displayed by the new Dragon UI. 
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005/2/9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 
 ********************************************************************
 */

#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#ifdef __GCC__
#include <glob.h>
#endif
#if defined __MINGCC__ || defined __GCC__
#include <unistd.h>
#endif
#include <errno.h>

#include "dtypes.h"
#include "dlimits.h"
#include "dragonOb.h"
#include "logger.h"
#include "IpcWrap.h"

static char* tempFile = NULL;
static ulong msgSize = 0;

/**
 * Replace & and < with appropriate XML to avoid problems
 * in parsing. Always returns the same static buffer, so
 * this can only be used once per statement.
 * @param input  Input string to scan for reserved chars
 *               Returned intact if none found
 * @returns original string or static modified string if
 *          reserved chars found.
 */
static char* replaceReservedChars(const char* input)
    {
    static char result[1024];
    const char* p;
    char* q;
    char* badpos = strpbrk(input,"&<");
    if (badpos == NULL)
        return (char*) input;
    memset(result,0,sizeof(result));
    p = input;
    q = result;
    while ((*p != '\0') && (q < (result + sizeof(result) - 6)))
        {
	if (*p == '&') 
	    {
	    *q++ = '&';
	    *q++ = 'a';
	    *q++ = 'm';
	    *q++ = 'p';
	    *q++ = ';';
	    }
	else if (*p == '<')
	    {
	    *q++ = '&';
	    *q++ = 'l';
	    *q++ = 't';
	    *q++ = ';';
	    }
	else
	    {
	    *q++ = *p;
	    }
	p++;
	}
    return result;
    }

/**
 * Remove any quotation marks in the string passed in.
 * Always returns the same static buffer, so
 * this can only be used once per statement.
 * @param input  Input string to scan for quotes
 *               Returned intact if none found
 * @returns original string or static modified string if
 *          reserved chars found.
 */
static char* stripQuotes(const char* input)
    {
    static char result[4096];
    const char* p;
    char* q;
    char* badpos = strpbrk(input,"\"");
    if (badpos == NULL)
        return (char*) input;
    memset(result,0,sizeof(result));
    p = input;
    q = result;
    while ((*p != '\0') && (q < (result + sizeof(result) - 1)))
        {
	if (*p != '"')
	    {
	    *q++ = *p;
	    }
	p++;
	}
    return result;
    }


/**
 * Start accumulating XML data for a report.
 * pczCalcType is calculation type label.
 * pczId is Identifier. pczTitleKey is translation key
 * for title - if null, no title line will be generated.
 * pczTitleRemind is default/reminder text for title.
 * If pczTitleKey is null, pczTitleRemind will be ignored.
 * Returns a file handle to be passed to other methods
 * that add to the report.
 */
FILE * BeginReport(const char* pczCalcType,
		   const char* pczId,
		   const char* pczTitleKey,
		   const char* pczTitleRemind,
		   const int iRowCount)
     {
     FILE* fp = NULL;
     const char * pczPath = CommFileName("");
     tempFile  = tempnam(pczPath,"rpt");
     //tempFile = tmpnam(NULL);
     msgSize = 0;
     if (tempFile == NULL)
         {
	 logError(-1703,
		  "Error generating temp file name in IpcXmlGen::BeginReport; "
		  "returned NULL");
	 return NULL;
	 }
     logTrace("IpcXmlGen::BeginReport buffering data to tempFile='%s'",
	      tempFile);
     fp = fopen(tempFile,"w+");
     if (fp != NULL)
         {
	 msgSize += fprintf(fp,"<calcResult calcType=\"%s\" "
			    "identifier=\"%s\" rowCount=\"%d\" >\n",
		 pczCalcType,pczId,iRowCount);
	 msgSize += fprintf(fp,
         "<title>\n<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\"/>\n",
		 pczTitleKey, replaceReservedChars(pczTitleRemind));
	 msgSize += fprintf(fp,"</title>\n");
	 }
     else
         {
	 logError(-1703,
		  "Error (%s) opening temp file '%s' in IpcXmlGen::BeginReport",
		  strerror(errno),tempFile);
	 }
     return fp;
     }

/**
 * Finish off the XML generation and use IPC mechanism
 * to send the report to the UI.
 */
void EndReport(FILE* fp)
    {
    char* messageBuffer = NULL;
//    int fd = 0;
    size_t iBytes = 0;
    logTrace("IpcXmlGen::EndReport (en); msgSize=%d",msgSize);
    msgSize += fprintf(fp,"</calcResult>\n");
    logTrace("IpxXmlGen::EndReport msgsize is %ld\n", msgSize);
    fflush(fp);
    messageBuffer = (char*) calloc(msgSize + 2,1);
    if (messageBuffer == NULL)
        {
	logError(-1701,
	    "Memory allocation failure (%ld bytes)  in rptgen::EndReport",
		 msgSize+2);
	}
    else
        {
        memset(messageBuffer,0,msgSize+2);
	fseek(fp, 0L, SEEK_SET);
	iBytes = fread(messageBuffer,1,msgSize,fp);
       	if (iBytes != msgSize)
   	     {  
	     logError(-1702,
		  "Error reading temp file in rptgen::EndReport");
	     // handle error
	     }
	else
	     {
	     logTrace("before sendMessage; size=%d",strlen(messageBuffer));
	     sendMessage(10,messageBuffer);
	     }
	logTrace("before free of messageBuffer");
	free(messageBuffer);
	}
	
    logTrace("before fclose");
    fclose(fp);
    fp = NULL;
    logTrace("before unlink of tempfile");
    if (tempFile != NULL)
         unlink(tempFile);
    tempFile = NULL;
    logTrace("IpcXmlGen::EndReport (ex)");
    }

/**
 * Start a new table, in a report with multiple tables 
 */
void BeginTable(FILE* fp, int border)
     {
     msgSize += fprintf(fp,"<newTable border=\"%s\">\n", 
                border > 0 ? "true" : "false");
     }

/**
 * End a subtable
 */
void EndTable(FILE * fp)
     {
     msgSize += fprintf(fp,"</newTable>\n"); 
     }

/**
 * Add a ruler line in a table
 */
void AddHorizontalRule(FILE * fp)
     {
     msgSize += fprintf(fp,"<horizRule/>\n"); 
     }

/**
 * Begin the header for the report. iFldCount is the number
 * of columns per row in the report. 
 */
void BeginHeader(FILE* fp, const int iFldCount)
     {
     msgSize += fprintf(fp,"<resultHeader fieldCount=\"%d\" >\n",iFldCount);
     }

/**
 * Finish off the header row.
 */
void EndHeader(FILE* fp)
     {
     msgSize += fprintf(fp,"</resultHeader>\n");
     }

/**
 * Start a group
 */
void BeginGroup(FILE* fp, char cGrpId)
     {
     msgSize += fprintf(fp,"<resultGroup id=\"%c\" >\n",cGrpId);
     }


/**
 * Start a group with a translated header
 */
void BeginKeyedGroup(FILE* fp, char cGrpId,
                const char* pczValueKey,
                const char* pczValueRemind,
                const char* pczSubstitute)
     {
     msgSize += fprintf(fp,"<resultGroup id=\"%c\" >\n",cGrpId);
     if (pczSubstitute == NULL)
         {
	 msgSize += fprintf(fp,
		 "<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\"/>\n",
		pczValueKey, replaceReservedChars(pczValueRemind));
	 }
     else
         {
	 msgSize += fprintf(fp,
	  "<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\" substitute=\"%s\"/>\n",
		pczValueKey, replaceReservedChars(pczValueRemind),pczSubstitute);
	 }
     }

/**
 * End a group
 */
void EndGroup(FILE* fp)
     {
     msgSize += fprintf(fp,"</resultGroup>\n");
     }


/**
 * Add a header field. pczFieldId is the internal label for the column
 * pczFieldKey is the key for looking up the column title. 
 * pczFieldRemind is the default/reminder string for the column title.
 */
void AddHeaderField(FILE* fp,
		    const char* pczFieldId,
		    const char* pczFieldKey,
		    const char* pczFieldRemind,
		    const char* pczSubstitute,
		    const char* pczDisplay)
     {
     if (pczDisplay == NULL)
          pczDisplay = "yes";
     if (pczSubstitute == NULL)
          {
          msgSize += fprintf(fp,
            "<resultField fieldId=\"%s\" display=\"%s\">\n<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\"/>\n",
		 pczFieldId, pczDisplay, pczFieldKey, 
			     replaceReservedChars(pczFieldRemind));
	  }
     else
          {
          msgSize += fprintf(fp,
            "<resultField fieldId=\"%s\" display=\"%s\">\n<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\" substitute=\"%s\"/>\n",
		 pczFieldId, pczDisplay, pczFieldKey, 
		 replaceReservedChars(pczFieldRemind), pczSubstitute);
	  }
     msgSize += fprintf(fp,"</resultField>\n");
     }

/**
 * Begin a row of report data.
 */
void BeginResultRow(FILE* fp)
     {
     msgSize += fprintf(fp,"<resultRow >\n");
     }

/*
 * Finish off the current row of report data
 */
void EndResultRow(FILE* fp)
     {
     msgSize += fprintf(fp,"</resultRow>\n");
     }

/*
 * Add data field to current row.
 * pczValueKey is the key for the value. This may be an empty string, 
 * indicating that the value does not need translation. pczValueRemind is the
 * reminder string, or the actual value if pczValueKey is null.
 * pczDataType is one of several possible data types, which give the 
 * UI clues with respect to formatting. pczEncoding is optional 
 * (may be null), but if specified indicates the encoding associated 
 * with the value.
 */
void AddResultField(FILE* fp,
		    const char* pczValueKey,
		    const char* pczValueRemind,
		    const char* pczSubstitute,
		    const char* pczDataType,
		    const char* pczEncoding)
     {
     if (pczEncoding != NULL)
        msgSize += fprintf(fp,
            "<resultItem dataType=\"%s\"  encoding=\"%s\">\n",pczDataType,
	     pczEncoding);
     else
        msgSize += fprintf(fp,
            "<resultItem dataType=\"%s\" >\n",pczDataType);
     if (pczSubstitute == NULL)
         {
	 msgSize += fprintf(fp,
		 "<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\"/>\n",
		pczValueKey, replaceReservedChars(pczValueRemind));
	 }
     else
         {
	 msgSize += fprintf(fp,
	  "<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\" substitute=\"%s\"/>\n",
		pczValueKey, replaceReservedChars(pczValueRemind),pczSubstitute);
	 }
     msgSize += fprintf(fp,"</resultItem>\n");
     }

/*
 * Add data field to current row with an itemCategory & itemIndex.
 * pczValueKey is the key for the value. This may be an empty string, 
 * indicating that the value does not need translation. pczValueRemind is the
 * reminder string, or the actual value if pczValueKey is null.
 * pczDataType is one of several possible data types, which give the 
 * UI clues with respect to formatting. pczEncoding is optional 
 * (may be null), but if specified indicates the encoding associated 
 * with the value.
 * pczCategory is the value to be used for "itemCategory" and
 * iIndex is the value for itemIndex (only relevant for signature reports).
 */
void AddCategoryResultField(FILE* fp,
		    const char* pczValueKey,
		    const char* pczValueRemind,
		    const char* pczSubstitute,
		    const char* pczDataType,
		    const char* pczEncoding,
                    const char* pczCategory,
		    const int iIndex)
     {
     if (pczEncoding != NULL)
        msgSize += fprintf(fp,
   "<resultItem dataType=\"%s\"  encoding=\"%s\" itemCategory=\"%s\" itemIndex=\"%d\">\n",
	     pczDataType,pczEncoding,pczCategory,iIndex);
     else
        msgSize += fprintf(fp,
   "<resultItem dataType=\"%s\"  itemCategory=\"%s\" itemIndex=\"%d\">\n",
             pczDataType,pczCategory,iIndex);
     if (pczSubstitute == NULL)
         {
	 msgSize += fprintf(fp,
		 "<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\"/>\n",
		pczValueKey, replaceReservedChars(pczValueRemind));
	 }
     else
         {
	 msgSize += fprintf(fp,
	  "<xlateText id=\"%s\" tag=\"listItem\" remind=\"%s\" substitute=\"%s\"/>\n",
		pczValueKey, replaceReservedChars(pczValueRemind),pczSubstitute);
	 }
     msgSize += fprintf(fp,"</resultItem>\n");
     }

/**
 * Add a note consisting of one or more text strings, translated or
 * not. Keystrings is an array of keys, reminders is the corresponding
 * array of reminders, substitutes is an array of substitution strings,
 * uCount is the number of individual text items
 * in the note.
 */
void AddNoteLine(FILE* fp,
		 const char* keystrings[],
		 const char* reminders[],
		 const char* substitutes[],
		 ushort uCount)
    {
    int i;
    msgSize += fprintf(fp,"<noteLine>\n");
    for (i = 0; i < uCount; i++)
       {
       if (substitutes[i] == NULL)
	   {
           msgSize += fprintf(fp,
             "<xlateText id=\"%s\" tag=\"fragment\" remind=\"%s\"/>\n",
		keystrings[i], replaceReservedChars(reminders[i]));
	   }
       else
	   {
           msgSize += fprintf(fp,
             "<xlateText id=\"%s\" tag=\"fragment\" remind=\"%s\" substitute=\"%s\"/>\n",
		keystrings[i], replaceReservedChars(reminders[i]),
			      substitutes[i]);
	   }
       }
    msgSize += fprintf(fp,"</noteLine>\n");
    }


/**
 * Close file and delete tempfile - called in case of error.
 */
void DoReportCleanup(FILE* fp)
    {
    if (fp != NULL)
        fclose(fp);
    if (tempFile != NULL)
        unlink(tempFile);
    tempFile = NULL;
    }

/**
 * Application-level function to create a text-only (TextTable) report.
 * TextInfo is an array of TEXT_DESCRIPTORs, each of which will be used
 * to create one paragram in the report. pczTitle is an optional title.
 * uCount is the number of items in TextInfo.
 */
void PrepareTextReport(TEXT_DESCRIPTOR TextInfo[], 
                       ushort uCount, const char* pczTitle)
    {
    const char* pczKey[1];
    const char* pczRemind[1];
    const char* pczSubst[1];
    FILE* rfp = NULL;
    int i = 0;
    rfp = BeginReport("TextTable","TextTable","%hXXXX",pczTitle,(int)uCount);
    if (rfp == NULL)
       return; 
    for (i = 0; i < uCount; i++)
         {
	 BeginResultRow(rfp);
         pczKey[0] = TextInfo[i].pczTextKey;
         pczRemind[0] = stripQuotes(TextInfo[i].pczTextValue);
         pczSubst[0] = NULL;
         AddNoteLine(rfp,pczKey,pczRemind,pczSubst,1);
	 EndResultRow(rfp);
	 }
    EndReport(rfp);
    }

void IPCXMLGEN_END() { puts(FIL_ID); }

#if defined TEST

/**
 * DUMMY VERSION of fn in Server/rptgen.c
 *
 * Prepare XML to display the result of a CAL run.
 * iStatus is the status of the CAL process. If negative,
 * was unable to meet the RMSE requirements
 * iMatchGCP is number of matching GCPs.
 * iRetained is the number of points retained
 * pczRptFile is the name of the file where the regression report
 * was written. 
 * This is a very simple report which simply formats a number
 * of NoteLines.
 * @param iRetained     is a simulated row count in order to make
 *			this file really big. 
 */
int PrepareRegressionSummaryReport(const int iStatus,
				   const int iMatchGCP,
				   const int iRetained,
				   const char* pczRptFile)
    {
    const char* keys[] = {"",""};
    const char* reminders[] = {"",""};
    const char* substitutes[] = {NULL,NULL};
    FILE* rfp = NULL;    
    char czNumBuf[32];
    czNumBuf[0] = '\0';
    rfp = BeginReport("SimpleTable","","%h6910.10",
			  "CAL Results Summary", 0);
    if (rfp == NULL)
       return -1; 

    if (iStatus == 0)
        {
	int rn;
	for (rn = 0; rn < iRetained; rn++)
	    {
	    BeginResultRow(rfp);
	    keys[0]="%h6910.0";
	    reminders[0]="numMatches";
	    sprintf(czNumBuf,"%d",iMatchGCP);
	    substitutes[0]=czNumBuf;
	    AddNoteLine(rfp,keys,reminders,substitutes,1);
	    EndResultRow(rfp);
	    BeginResultRow(rfp);
	    keys[0]="%h6910.1";
	    reminders[0]="retained";
	    sprintf(czNumBuf,"%d",rn);
	    substitutes[0]=czNumBuf;
	    AddNoteLine(rfp,keys,reminders,substitutes,1);
	    EndResultRow(rfp);
	    printf(".");
	    }
	}
    else
        {
	BeginResultRow(rfp);
        keys[0]="%h6910.2";
        reminders[0]="unable to meet";
        substitutes[0]= NULL;
        AddNoteLine(rfp,keys,reminders,substitutes,1);
        EndResultRow(rfp);
	}
    BeginResultRow(rfp);
    keys[0]="%h6910.3";
    reminders[0]="report file";
    substitutes[0]= (char*) pczRptFile;
    AddNoteLine(rfp,keys,reminders,substitutes,1);
    EndResultRow(rfp);
    EndReport(rfp);
    return 0;
    }

int main(int argc, char** argv)
    {
    int option = 0;
    int iRetval = 0;
    char inpLine[128];
//    char czFilename[128];
    const char * pKp = getKpath();
    char * guardBand = (char *) malloc(77);
    int rowcnt = 1;
    BOOL bContinue = 1;
    memset(guardBand,0x55,77);
    ipcLogInit(NULL,"Dragon.err","Dragon.trc","IP","TEST");
    while(bContinue && (iRetval == 0))
        {
	printf("IpcXmlGen Test Driver: kpath='%s'\n",pKp);
	printf("   1 - PrepareRegressionReport\n");
	printf("   2 - PrepareRegressionReport large size\n");
	printf("   9 - Exit\n");
//    fprintf(stdout,"   2 - Test writing of image\n");
//    fprintf(stdout,"   3 - Test image copy\n");
	fprintf(stdout,"Enter option: ");
	fgets(inpLine,128,stdin);
	sscanf(inpLine,"%d",&option);
	printf("=========================================\n");
	switch (option)
	    {
	    case 1:
//	        fprintf(stdout,"Enter report file name with path: ");
//	        fgets(inpLine,128, stdin);
//	        sscanf(inpLine,"%s",czFilename);
		iRetval = PrepareRegressionSummaryReport(3,4,1,"sam");
		break;
	    case 2:
	        fprintf(stdout,"Enter report row count: ");
	        fgets(inpLine,128, stdin);
	        sscanf(inpLine,"%d",&rowcnt);
		iRetval = PrepareRegressionSummaryReport(0,4,rowcnt,"sam");
		break;
	    case 9:
		bContinue = 0;
		break;
	    default:
		fprintf(stderr,"Invalid option, exiting\n\n");
		iRetval = 1;
		break;		      
	    }
	free(guardBand);
	printf("test %d completed successfully: %s (%d)\n\n",
	       option,YESNO(iRetval==0),iRetval);
	}
    exit(iRetval);
    }
#endif
