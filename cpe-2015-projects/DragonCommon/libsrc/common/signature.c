#include "drelease.h"
ID_ SIGNATURE_ID[]
    ="\0@(#) " __FILE__ "  $Revision: 1.3 $$Date: 2014/04/01 07:22:03 $";
D_REL_IDSTR;
/****************************************************************
 *	      >>   SIGNATURE.C <<
 *		    $Revision: 1.3 $
 *
 *   Signature statistics module
 *     Storage and access to signature stats structures.
 *
 *      ~~ Copyright 1988-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: signature.c,v 1.3 2014/04/01 07:22:03 rudahl Exp $
 *	$Log: signature.c,v $
 *	Revision 1.3  2014/04/01 07:22:03  rudahl
 *	lint esp from old mingc
 *
 *	Revision 1.2  2006/08/20 07:59:25  goldin
 *	Add new wrapper funs
 *
 *	Revision 1.1  2006/08/18 05:39:48  goldin
 *	Combine sigfio-o and sigstat into signature.c
 *	
 * 
 *
 *****************************************************************
 *
 *         V1.0       22 September 1989
 *
 *
 *                FUNCTIONAL SUMMARY
 *
 *  This file includes routines formaintaining
 *  a set of signature statistics in a static array. Previously
 *  this was a virtual file. If we add more than 16 classes,
 *  we will need to consider whether we need strategies to
 *  save memory.
 *
 *  This module combines two former Server level source files,
 *  sigstat.c and sigfio-o.c
 *
 *
 ****************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 *
 *   Date       Who         What and Why
 *   ----       ---         ------------
 *   9-22-89    S.Goldin    Created Version 1.0
 *   4-07-91    S.Goldin    Modified statrec structure to allow
 *                           use of cluster results as signatures
 *   4-09-91    S.Goldin    Modified rtns to speed them up
 *   5-12-91    S.Goldin    Moved MoveSig to here - was not
 *                           working due to new caching strategy
 *                           Now does explict Vfwrite
 *	6/7/91 ktr 	mod for Zortech small model, DRAGON 3.05
 *	6/27/94 ktr	added errstat_set for vfile ops
 * 5.0	2/27/97 ktr	added _DEBUG info
 *	8/10/97 ktr	revised so that 'sigptr' actually points
 *			to a fixed chunk of memory, not alloc'd,
 *			since there's no point when it can definitively
 *			be freed.
 *      4/26/99 seg     Changed init_modarray to return the number
 *                      of bands in use in the current signature file.
 *	12/9/99 ktr	simplified ref's to sigptr to &FixedStatRec
 *      6/4/00 ktr      fixup for GCC
 *      6/17/00 ktr     fixed missing return value in load_modarray
 *      6/27/01 ktr     changed to just use a big static array for 32-bits
 *                      this is sized NCLS+2; may need to change for 
 *                      ~~ adding more classes
 * 5.5	2005-3-5 ktr	import from Dragon 5.4.4
 * 5.9  2006-8-18 seg   Combined sigfio-o.c and sigstat.c into new module
 ****************************************************************/

#include <stdlib.h> 
#include <string.h> 
#include <stdio.h>   
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <time.h>


#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
#include "logger.h"

#include "dhead.h"
#include "dragonOb.h"
#include "files.h"
#include "img.h"
#include "wfutil.h"   /* for xcut_cmd */
#include "IpcWrap.h"
#include "signature.h"

#define SIGSTAT_C

SIGBOUNDS modarray[NCLS];
    /* initialized by init_modarray, in this module;
     * used by callback in MOD function 
     */

/**********************************************************
 *
 *	local prototypes
 *
 **********************************************************/

static int chkstatfile();

static int writesig(int, const char*);
static int readsig(int, int, char*,const char*, uint uSignameSize);
static void SetNumpts(char**); 
static void SetMin(char**);
static void SetMax(char**);
static void SetMean(char**);
static void SetVars(char**);
static void SetUpper(char**);
static void SetLower(char**);
static void SetSum(char**);
static void SetSumsq(char**);
static void SetHist(char**);
static void SetHistdot(char**);
static void SetNewsig(char**);
static void SetSource(char**);
static void SetBandFiles(char**);
static void SetEndsig(char**);
static void SetSumprod(char**);
static void SetCovar(char**);
static void SetColorInfo(char**);
static void SetThreshold(char**); 
static void WFComment(char**);
static void getintg(unsigned int*,char**);
static void getreal(double*,char**);
static void getlng(unsigned long*, char**);

/* Local data items */

#define OUT_UINT48(x)  ((x.extra > 0) ? ULONG_MAX : x.base) 
       /* output the long portion of a UINT48 struct */

extern int _OSERR;

static struct statrec StatFile[NCLS+2];  /* not a real file */
static BOOL s_bStatFileOpen = FALSE;     /* TRUE -> it has been init */

static int s_iLastclass = -1;
static int loadflag;	/* 1 permits loading signatures into struct */
                        /* needs to be global b/c used by funs called via */
                        /* xcut_cmd */
static struct statrec * cursig = NULL;
                        /* which is the current signature record */
static unsigned int curhist,curband; 
                                /* where are we loading at the moment? */
static char sigfname[PATH_MAX]= { '\0' };   /* signature file name */
static FILE* pInFp = NULL;  /* Keep track of where we are from call to call */

static int sigfilrec = 0;	    /* current record number in SIG file */
static char czLatestName[EXT_SIGNAME_SZ];    
                        /* name of latest signature read */

	/* functions available from .SIG files */
enum SG_OPS { 	NUMPTS , MEANV , MAXV , MINV , 
		VARSV , UPPERV , LOWERV , SUMXV ,
		SUMSQV , SUMPRV, HISTV , HISTDOT ,
		COVAR , NEWSIG ,
                ENDSIG , SOURCE, COLOR, /* TEST , */ NULLSG } ;
 

static int sigendflag;    /* zero while scanning a sig. record; then =1 */

	/* NOTE: the following table is used for cmd line interpretation.
	 */

static  CMDS cmds[] = {
	{ "#POINTS=",	SetNumpts,	1,	NULL, } ,
	{ "MEAN=",      SetMean,        4,      NULL, } ,
	{ "MAX=",	SetMax,    	4,	NULL, } ,
	{ "MIN=",       SetMin,         4,      NULL, } ,
	{ "VARS=",	SetVars,	4,	NULL, } ,
	{ "UPPER=",	SetUpper, 	4,	NULL, } ,
	{ "LOWER=",	SetLower,	4,	NULL, } ,
	{ "SUMX=",	SetSum,		4,	NULL, } ,
	{ "SUMSQ=",	SetSumsq,  	4,	NULL, } ,
	{ "SUMPROD=",	SetSumprod,	6,	NULL, } ,
	{ "COVARS=",	SetCovar,  	6,	NULL, } ,
	{ "HIST=",	SetHist,	18,	NULL, } ,
	{ "HIST...",	SetHistdot,	16,	NULL, } ,
	{ "NEW-SIG",	SetNewsig,	1,	NULL, } ,
	{ "END-SIG",	SetEndsig,	0,	NULL, } ,
	{ "SOURCE=",	SetSource,	1,	NULL, } ,
	{ "IMAGES=",    SetBandFiles,   4,      NULL, } ,
	{ "COLOR=",     SetColorInfo,   4,      NULL, } ,
	{ "THRESHOLD=",	SetThreshold,	1,	NULL, } ,
	{ "(",		WFComment,	0,	NULL, } ,
	{ NULL,		NULL,		0,	NULL }
  	};	

/**/
/* As of 2001, signature stat structures are stored in the static array above. 
 * No "reading" or "writing" goes on in this module; we simply return the
 * pointer to the relevant array element and manage flags. 
 */

struct statrec * getstat(unsigned clsnum)
	/*	read signature statistics record corresponding to 
	 *	class 'clsnum' and return a pointer to structure
	 *	containing appropriate data.
	 *	If necessary, open sigstat virtual file first.
	 *	Returns null if virtual file error 
	 *      or 'clsnum' illegal value. 
	 */
    {
    struct statrec * pRetval = NULL;
    if (clsnum >= NCLS+2)
        return NULL;
    if (chkstatfile() < 0)	/* reopen vf if necessary */
        {                       /* or alloc array */
	return NULL; 
        }
    pRetval = &StatFile[clsnum];
    s_iLastclass = clsnum;
    return pRetval;
    }

/**/

int savestat(unsigned clsnum)
	/*	saves data currently in memory in FixedStatRec as
	 *	element number clsnum. 
	 *	Return status returned from vfwrite - negative if error.
	 */
    {   
 	  /* actually, do not do the save here, only in getsig */
	  /* instead, just set a flag saying we want to do a write */
    return clsnum;
    } 

int MoveSig(int fromsig,int tosig)

	/*	move contents of sigstats[fromsig] to sigstats[tosig]
	 *	return 0 unless error, then neg
	 *	This should not affect the "cache" as it uses a different
	 *	pointer for the signature data.
	 */
    {	  
    int status = 0;
    if (((min(fromsig,tosig)) < 0) || ((max(fromsig,tosig)) > NCLS))
	{
	status = -1;
	}
    else
	{
	if (chkstatfile() >= 0)
	    {
	    memcpy(&StatFile[tosig],&StatFile[fromsig],sizeof(struct statrec));
	    }
	}
    if (status > 0) 
	status = 0;
    return status;    
    } 

/**/
static int chkstatfile()
	/* 	check to see if signature statistics array is active.
	 * 	If it is, just return OK (zero). 
	 * 	If not, zero the static array in preparation for reading.
	 *	Return < 0 if error.
	 */    

    {
    int status = 0;
    if (!s_bStatFileOpen)
        memset(&StatFile,0,sizeof(StatFile));
    s_bStatFileOpen = TRUE;
    return status;
    }
/**/
int clearstats()
	/*	Marks the statistics array as inactive. 
	 *	This will cause it to be zeroed and "reopened" next time we
	 *	try to access a signature.
	 *	Return value always 0
	 */
    {
    int status = 0;
    s_bStatFileOpen = FALSE;
    s_iLastclass = -1;
    return status;
    }
 
/**/

int init_modarray(int nclass)
         /* initialize the modarray with the bounds for signatures
          * 0 through nclass - 1, for use by callback in MOD
          *
          * returns the number of bands that were used to calculate
          * these signatures, or -1 if error.
          */
    {
    int i,j;
    int iHighestBand = -1;
    struct statrec * thissig;
    memset(modarray,0,sizeof(modarray));
    for (i = 0; i < nclass; i++)
        {
	thissig = getstat(i);
	if (thissig == NULL)
            return -1;
	for (j = 0; j < 4; j++)  /* by band */
	    {
	    modarray[i].lower[j] = (byte) thissig->lower[j];
	    modarray[i].upper[j] = (byte) thissig->upper[j];
	    if ((j > iHighestBand) && (thissig->hist[j][0] > 0))
	        iHighestBand = j;
	    }
	}
    return iHighestBand + 1;  /* number of bands used in all sigs */
    }
/*-----------------------------------*/

/**/
int sigio(enum SG_FNS code,const char * filename,int recno,int sigayno,
	  char * signame, uint uSignameSize)
	/*	 signature file I/O. There are several possible
	 *	 sigio functions, selected by 'code'. In each case,
	 *	 all arguments are to be supplied although in
	 *	 some cases they may not be meaningful. 
	 *	 'code': SIGLOAD=0:
	 *		 SIGCLOSE=1:	close current sig file. 
	 *		 SIGWRT=2:  	output 'sigayno' to 'filename',
	 *				creating file if necessary.
	 *		 SIGDUMP=3:	obsolete
	 *	 'filename' is the name of the signature file.
	 *	 'recno' specifies which record in the file (in order),
	 *	   or -1 => use next record.
	 *	 'sigayno' specifies which of the array of signature
	 *	   structures will receive or supply the data, or
	 *   	  -1 => do not load data, just return name. 		    
	 * 	the signature name is copied into 'signame'. 
	 * 	'sigio' returns 0 if successful, otherwise an error code.
	 *      for READ: -3 => read error, or past EOF
         *
	 *	Note, as of 6/28/90 does file handling indirectly,
	 *	through rsfgets and wfs functions. This is to
	 *	centralize handling of network-based file access
	 *  
	 *      4/7/05 returned to using normal io for reading.
	 * @return		0 OK
	 *			-1 => unknown  code
	 *			for WRITE: -4 if no valid signature, -2 if write err
	 *			for READ: -1, -3, -4 for what?
	 */ 
    {		   
    int retval = -1;
    *signame = '\0';	/* make sure it's a valid string */
    switch(code)
	{			      
	case SIGLOAD:	retval = readsig(recno,sigayno,signame,filename,uSignameSize); 
                        break;
			    
	case SIGCLOSE:	/* close current sig file. Now actually does
                         * do a close if necessary 4/7/05 
			 */
	                if (pInFp != NULL)
			   {
			   fclose(pInFp);
			   pInFp = NULL;
			   }
    		        sigfname[0] = '\0';
			retval = 0;
                        break;

	case SIGWRT:    /* output 'sigayno' to 'filename', creating file
			 * if necessary
			 */
			retval = writesig(sigayno,filename);
			break;
	default:
			break;
	}
    return retval;
    }

/**/
static int writesig(int ayno,const char * fname)
	/* 	write signature number 'ayno' to file 'fname'
	 * 	provided that a valid signature exists
	 * 	return -4 if no valid signature, -2 if write err
	 * 	else 0
	 *
         *	modified 6/28/90 to use wsf, sprintf, in order
         *	to centralize network file handling
	 */
    {
    char outbuf[256];
    int i,j,k,histnum;		 	     
    struct statrec * thissig;  /* this sig */
    int status;
    //printf("writesig number %d to filename %s\n", ayno, fname);
    if ((strlen(fname) > 0) && (strcmp(fname,sigfname)))	
        /* if not "open" (this takes the place of opensig) */
	{
        /* create or replace - zero length file */
//        if (wsf(fname,outbuf,0,WSF_TRUNC) < 0)
	remove(fname);
        strcpy_array(sigfname,fname);
        sigfilrec = 0;
        }

    thissig = getstat(ayno);
    if ((thissig) && (thissig->valid))
	{
	time_t t;	/* for 'time' */
	char *timptr;
    	time(&t);  
	timptr = ctime(&t);
	timptr[24]='\0';	/* zap the newlin */
	sprintf(outbuf,"( Time: %s )\r\n( CLASS NUMBER %d )\r\n",timptr,ayno);
        if (wsf(fname,outbuf,strlen(outbuf),
                WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;
	sprintf(outbuf,"NEW-SIG %s\r\n    #POINTS= %ld\r\n    MIN=\t%3d %3d %3d %3d\r\n",
                 thissig->name,thissig->numpt,
                 thissig->minv[0],thissig->minv[1],
	         thissig->minv[2],thissig->minv[3]);
        if (wsf(fname,outbuf,strlen(outbuf),
                WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;
	sprintf(outbuf,"    MAX=\t%3d %3d %3d %3d\r\n    MEAN=\t%3d %3d %3d %3d\r\n",
	    thissig->maxv[0],thissig->maxv[1],
	    thissig->maxv[2],thissig->maxv[3],
	    thissig->mean[0],thissig->mean[1],
	    thissig->mean[2],thissig->mean[3]);
        if (wsf(fname,outbuf,strlen(outbuf),
                WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;
	sprintf(outbuf,"    LOWER=\t%3d %3d %3d %3d\r\n    UPPER=\t%3d %3d %3d %3d\r\n",
	    thissig->lower[0],thissig->lower[1],
	    thissig->lower[2],thissig->lower[3],
	    thissig->upper[0],thissig->upper[1],
	    thissig->upper[2],thissig->upper[3]);
        if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;
	sprintf(outbuf,"    SUMX=\t%9ld %9ld %9ld %9ld\r\n    SUMSQ=\t%9ld %9ld %9ld %9ld\r\n",
	    thissig->sumx[0],thissig->sumx[1],
	    thissig->sumx[2],thissig->sumx[3],
	    OUT_UINT48(thissig->sumsqx[0]),
            OUT_UINT48(thissig->sumsqx[1]),
            OUT_UINT48(thissig->sumsqx[2]),
            OUT_UINT48(thissig->sumsqx[3]));
        if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;
	sprintf(outbuf,"    SUMPROD=\t%9ld %9ld %9ld %9ld %9ld %9ld\r\n",
	    OUT_UINT48(thissig->sumprod[0]),
            OUT_UINT48(thissig->sumprod[1]),
	    OUT_UINT48(thissig->sumprod[2]),
            OUT_UINT48(thissig->sumprod[3]),
	    OUT_UINT48(thissig->sumprod[4]),
            OUT_UINT48(thissig->sumprod[5]));
        if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;

	sprintf(outbuf,"    VARS=\t%9.3f %9.3f %9.3f %9.3f\r\n",
	    thissig->vars[0],thissig->vars[1],
	    thissig->vars[2],thissig->vars[3]);
        if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;

	sprintf(outbuf,"    COVARS=\t%9.4f %9.4f %9.4f %9.4f %9.4f %9.4f\r\n",
	    thissig->covar[0],thissig->covar[1],
	    thissig->covar[2],thissig->covar[3],
	    thissig->covar[4],thissig->covar[5]);
        if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	    return -2;

	for (i=0 ; i<4 ; i++)	/* iterate over bands */
	    {							  
	    histnum = 0;	/* counts 0 to 65 */
	    sprintf(outbuf,"    HIST= %d \t",i);
            if ((status = wsf(fname,outbuf,strlen(outbuf),
			WSF_APPEND|WSF_BUFFER)) < 0)
                {
		return -2;
                }
	    for (j=0 ; j<17 ; j++)
                {
		sprintf(outbuf," %ld",thissig->hist[i][histnum++]);
                if ((status=wsf(fname,outbuf,strlen(outbuf),
			WSF_APPEND|WSF_BUFFER))< 0)
                    {
		    return -2;
                    }
                }
	    sprintf(outbuf,"\r\n");
            if ((status = wsf(fname,outbuf,strlen(outbuf),
			WSF_APPEND|WSF_BUFFER)) < 0)
                {
		return -2;
                }
	    for (k=0 ; k<3 ; k++)
		{
		sprintf(outbuf,"    HIST... \t");
                if ((status = wsf(fname,outbuf,strlen(outbuf),
			WSF_APPEND|WSF_BUFFER)) < 0)
                    {
		    return -2;
                    }
	    	for (j=0 ; j<16 ; j++)
                    {
		    sprintf(outbuf," %ld",thissig->hist[i][histnum++]);
                    if ((status=wsf(fname,outbuf,strlen(outbuf),0x9))
                             < 0)
                        { 
			return -2;
                        }
                    }
                sprintf(outbuf,"\r\n");
                if (wsf(fname,outbuf,strlen(outbuf),0x9) < 0)
		    return -2;
		}
	    }
        if (strlen(thissig->source) > 0)
            {
            sprintf(outbuf,"    SOURCE= %s\r\n",thissig->source);
            if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	        return -2;
            }
        if (strlen(thissig->bandfile[0]) > 0)
            {
            sprintf(outbuf,"    IMAGES= %s %s %s %s\r\n",
             thissig->bandfile[0],thissig->bandfile[1],
             thissig->bandfile[2],thissig->bandfile[3]);
            if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	        return -2;
            }

        if (strlen(thissig->colorName) > 0)
            {
            sprintf(outbuf,"    COLOR= %s %d %d %d\r\n",
             thissig->colorName, thissig->redVal, thissig->greenVal,
             thissig->blueVal);
            if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	        return -2;
            }

        if (thissig->sigThresh > 0.01)
            {
            sprintf(outbuf,"    THRESHOLD= %lf\r\n",
             thissig->sigThresh);
            if (wsf(fname,outbuf,strlen(outbuf),
		WSF_APPEND|WSF_NOFLUSH|WSF_BUFFER) < 0)
	        return -2;
            }
	sprintf(outbuf,"END-SIG\r\n");
        if (wsf(fname,outbuf,strlen(outbuf),              
                WSF_APPEND|WSF_BUFFER) < 0)
	    return -2;
	return(0);
	}
    else 
	{
	sprintf(outbuf,"( CLASS NUMBER %d NOT DEFINED )\r\n",ayno);
        wsf(fname,outbuf,strlen(outbuf),0x9);
	return(0);
	}
    printf("writesig end\n");
    }

/**/
static int readsig(int recno,int ayno,char * signame,const char * fname,
		   uint uSignameSize)
	/* 	read signature numbered recno to end 
	 *	copying the name to 'signame'. Return 0 is
	 * 	OK, -3 if error opening file,
         *      -10 if EOF (not necessarily an error) 
	 * 	If 'ayno'=-1, load the contents into the "working" 
	 * 	sigstat structure; else load into signature number ayno
         *
         *	handles skipping past unwanted signatures, or
	 * 	resetting to start of file if necessary
	 */
    {	
    char cmdline[132];  
    char *toks[32];
    char **sargv;
    int i;
    int eofflag = 0;
    int iLocRecno = recno;

/*   printf("Entering readsig with recno = %d,ayno=%d,signame=%s,fname=%s\n",
//            recno,ayno,signame,fname);
//     printf("sigfilrec is %d\n",sigfilrec);
 */

    logTrace("signature::readsig starting filenamelen=%d",strlen(sigfname));
    if (recno < 0)
        logTrace("called with recno equal to -1 - may not work");
    loadflag = (ayno != -1);    /* prevent loading */
    if (loadflag) 
        cursig = getstat(ayno);     /* get ptr to the desired signature */
    else 
        cursig = getstat(NCLS);     /* dummy/work signature */
                                   /* shouldn't affect any "good" data */ 
//    if (g_iTrace)
	logTrace("   cursig=%p",cursig);
    if (cursig == NULL)             /* some kind of virtual file error */
        return -1;
    cursig->sigThresh = 0.0;      /* clear, just in case not provided in file*/

    if (iLocRecno < 0)   /* the 'next' one */
        {
	iLocRecno = sigfilrec + 1; 
	}
    if ((strlen(fname) > 0) && (strcmp(fname,sigfname)))	
        {
//	if (g_iTrace)
	    logTrace("   initial opening of sig file %s",fname);
          /* if not "open"  - this is first access to this file */
	if (pInFp != NULL)
	   {
	   fclose(pInFp);
	   pInFp = NULL;
	   }
	pInFp = fopen(fname,"r");
	if (pInFp == NULL)  /* can't open */
	   return -3;
	if (fgets(cmdline,sizeof(cmdline),pInFp) == NULL)
	   return -10;
        /* otherwise ...*/
        strcpy_array(sigfname,fname); 
	sigfilrec = 0;	
	} 
    else if (iLocRecno < sigfilrec)   /* if past where we want to be */
        {
	if (pInFp == NULL)
	   {
	   pInFp = fopen(fname,"r");
	   if (pInFp == NULL)  /* can't open */
	       return -3;
	   }
	else if (fseek(pInFp,0L,SEEK_SET) != 0)
           return -3;
	sigfilrec = 0;
	}   /* rewind file and reset signature counter */  
   /* Otherwise, read the next line from the file - the buffer */
   /* location pointer in rsfgets should be correct  */
    else
        if (fgets(cmdline,sizeof(cmdline),pInFp) == NULL)
	   return -10;
//    if (g_iTrace)
	logTrace("   sigio we just read '%s', length is %d",cmdline,
		 strlen(cmdline));

    while ((sigfilrec < iLocRecno) && (!eofflag))  /* scan to req. rec */
        {
	sigendflag = 0;
	while ((!sigendflag) && (!eofflag))
	    {
            if (strlen(cmdline) > 2)
	        {
		toks[0] = strtok(cmdline," \t\n\r");
		if (strcmp(toks[0],"END-SIG")==0)
                    SetEndsig(toks);  /* doesn't actually use the param */
                   /* this will set sigendflag for this signature */
		}
	    if (fgets(cmdline,sizeof(cmdline),pInFp) == NULL)
                {
                if (sigendflag)
                    eofflag = 1;
		else  
		    {
		    *signame='\0';
		    return (-3);  /* error or premature EOF */ 
		    }
		}
	    }  /* end loop reading one unwanted sig */ 
	}      /* end of loop through unwanted sig */
    if (eofflag)
        {
	*signame='\0';
	return (-4);   
	}
   /* ok - we should now be located at the desired signature */
   /* so read and process it. We have already read the first line  */

   sigendflag = 0;
   while (!sigendflag)
      {
      if (strlen(cmdline) > 2)
           {
           toks[0] = strtok(cmdline," \t\n\r");
           i = 1;
           sargv = &toks[0];
           while ((i < 32) && ((toks[i++] = strtok(NULL," \t\n\r")) != NULL))
	     ;
           sargv += xcut_cmd(sargv,cmds,"SIGIO");
           }
      if (!sigendflag)
           { 
	   if (fgets(cmdline,sizeof(cmdline),pInFp) == NULL)
               {
	       *signame='\0';
	       fclose(pInFp);
	       pInFp = NULL;
               return -3;  /* error or premature EOF */ 
               }
           }
      }
//    if (g_iTrace)
//	logTrace("  latestname='%s'",czLatestName);
    strncpy(signame,czLatestName,uSignameSize);
    if (!loadflag)
	ayno = NCLS;
       cursig->valid = 1;
	    /* if not, leave 'valid' as is */
       strcpy(cursig->name,czLatestName);
       if (savestat(ayno) < 0) 
           return -1;
    return 0;
    }
/**/

static void SetNumpts(char ** argv)
    {
    getlng(&cursig->numpt,argv);
    }

static void SetMin(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getintg(&cursig->minv[i],argv++);
    }

static void SetMax(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getintg(&cursig->maxv[i],argv++);
    }

static void SetMean(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getintg(&cursig->mean[i],argv++);
    }

static void SetUpper(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getintg(&cursig->upper[i],argv++);
    }

static void SetLower(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getintg(&cursig->lower[i],argv++);
    }

static void SetSum(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getlng(&cursig->sumx[i],argv++);
    }

static void SetSumsq(char ** argv)
    {
    int i;
    unsigned long tmpv;
    for (i=0 ; i<4 ; i++)
        {
	getlng(&tmpv,argv++);
        cursig->sumsqx[i].base = tmpv;
        cursig->sumsqx[i].extra = 0;
        }
    }

static void SetSumprod(char ** argv)
    {
    int i;
    unsigned long tmpv;
    for (i=0 ; i<6 ; i++)
        {
	getlng(&tmpv,argv++);
        cursig->sumprod[i].base = tmpv;
        cursig->sumprod[i].extra = 0;
        }
    }

static void SetCovar(char ** argv)
    {
    int i;
    for (i=0 ; i<6 ; i++)
	getreal(&cursig->covar[i],argv++);
    }

static void SetVars(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
	getreal(&cursig->vars[i],argv++);
    }

	/* HIST's are formatted as an initial line of 18 integers
	 * (of which the first is the band number) followed by
	 * 3 lines of 16 integers for a total of 65 integers per band,
	 * 4 bands.
	 */
static void SetHist(char ** argv)
    {
    getintg(&curband,argv++);
    for (curhist=0 ; curhist<17 ; curhist++)
	getlng(&cursig->hist[curband][curhist],argv++);
    }

static void SetHistdot(char ** argv)
    {		   
    int i;
    for (i=0 ; i<16 ; i++)
	getlng(&cursig->hist[curband][curhist++],argv++);
    }

static void SetNewsig(char ** argv)
    {
    memset(czLatestName,0,sizeof(czLatestName));
    while (*argv != NULL) 
        {
        strcat(czLatestName,*argv++);
	if (*argv)
	    strcat(czLatestName," ");
        if (strlen(czLatestName) >= (sizeof(czLatestName)-2))
	    break;
	}
    strtok(czLatestName,"\r\n");
    }

static void SetSource(char **argv)
    {
    strcpy(cursig->source,*argv++);
    strtok(cursig->source," \r\n");
    }
	
static void SetBandFiles(char ** argv)
    {
    int i;
    for (i=0 ; i<4 ; i++)
        if (*argv != NULL)
           strcpy(cursig->bandfile[i],*argv++);
        else
           cursig->bandfile[i][0] = '\0';
    }

static void SetColorInfo(char ** argv)
    {
    if (*argv != NULL)
        strcpy(cursig->colorName,*argv++);
    else
        cursig->colorName[0] = '\0';

    if (*argv != NULL)
        cursig->redVal = atoi(*argv++);
    else
        cursig->redVal = 0;
    if (*argv != NULL)
        cursig->greenVal = atoi(*argv++);
    else
        cursig->greenVal = 0;
     
    if (*argv != NULL)
        cursig->blueVal = atoi(*argv++);
    else
        cursig->greenVal = 0;
     
    }

static void SetThreshold(char ** argv)
    {
    getreal(&cursig->sigThresh,argv);
    }


static void SetEndsig(char ** argv)
    {
    sigfilrec += 1;
    sigendflag = 1;
    }

static void WFComment(char ** argv)
    {
    }
 
static void getintg(unsigned * arg,char ** argv)
	/* get numeric param from arg. line */
    {
    int i=atoi(*argv);
    *arg = i;
    }

static void getreal(double * arg,char ** argv)
	/* get real param from arg. line */
    {
    double i=atof(*argv);
    *arg = i;
    }

static void getlng(unsigned long * arg,char ** argv)
	/*	get long param from arg. line */
    {
    long i=atol(*argv);
    *arg = i;
    }

/** Wrapper functions for use in new code  and for DTK users */

/* Open and read all the signatures in a signature file.
 * Signatures are stored in static array StatFile.
 * Copy the signature names to pSigNames.
 * @param pczFilename   Name/path of file to read
 * @param pSigNames     Ptr to structure for saving sig mames
 * @return number of sigs read, or negative if some error.
 *                      -3 means can't open file 
 */   
int readSignatures(const char* pczFilename, struct ClsNameStruct * pSigNames)
   {
   int iStatus = 0;
   int iSigCount = 0;
   logTrace("signature::readSignatures (en)");
   chkstatfile(); /* zero sigs and set flag */
   while (iStatus >= 0)
       {
       iStatus =  
         sigio(SIGLOAD,pczFilename,iSigCount,iSigCount,
                pSigNames->czName[iSigCount],
                sizeof(pSigNames->czName[iSigCount]));
       logTrace("read signature %d, status %d", iSigCount, iStatus);
       if (iStatus >= 0)
          iSigCount++;
       }
   if (iStatus == -10) /* end of file */
       iStatus = 0;
   sigio(SIGCLOSE,pczFilename,-1,iSigCount,pSigNames->czName[iSigCount],
                sizeof(pSigNames->czName[iSigCount]));
   logTrace("signature::readSignatures (ex) count is %d status is %d",
               iSigCount,iStatus);
   return (iStatus >=0) ? iSigCount : iStatus;
   }

/* Write all the signatures that are current stored in
 * static array StatFile to the file passed in.
 * @param pczFilename   Name/path of file to read
 * @param iSigCount      Number of signatures to write
 * @return 0 if okay, or negative if some error.
 */   
int writeSignatures(const char* pczFilename, int iSigCount)
    {
    int iSigNo = 0;
    int iStatus = 0;
    char czDummy[16];
    logTrace("signature::writeSignatures (en)");
    for (iSigNo = 0; (iSigNo < iSigCount) && 
                        (iStatus == 0); iSigNo++)
         {    
         iStatus = sigio(SIGWRT,pczFilename,iSigNo,iSigNo,
           czDummy,sizeof(czDummy));
         logTrace("wrote signature %d, status %d", iSigNo, iStatus);
	 }   
    sigio(SIGCLOSE,pczFilename,iSigNo,iSigNo,czDummy,sizeof(czDummy));
    logTrace("signature::writeSignatures (ex) returning %d",iStatus);
    return iStatus;
    }

/* Return a requested signature. Returns null if
 * the iSigNo (signature number) is not valid.
 */  
struct statrec * getSignature(int iSigNo)
   {
   return getstat((unsigned) iSigNo);
   }


/* Figure out how many bands are represented by
 * the currently loaded signatures, based on
 * the signature histograms.
 * @return number of bands or 0 if signatures not initialized
 */
int getBandCount()
    {
    int j;
    int iHighestBand = -1;
    struct statrec * thissig;
    thissig = getstat(0);
    if (thissig != NULL)
       {
       for (j = 0; j < 4; j++)  /* by band */
	  {
	  if ((j > iHighestBand) && (thissig->hist[j][0] > 0))
	      iHighestBand = j;
	  }
       }
    return iHighestBand + 1;  /* number of bands used in first sig */
    }

void END_SIGNATURE_C() { puts(FIL_ID); }





