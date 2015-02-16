#include "drelease.h"
 ID_ STITCH_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.3 $$Date: 2014/12/17 07:20:39 $";
D_REL_IDSTR;
/****************************************************************
 *	STITCH.C - "Stitch" together two images into a mosaic.
 *	  Sample DRAGON Programmer's Toolkit Application
 *
 *	  $Revision: 1.3 $	$Date: 2014/12/17 07:20:39 $
 *
 *	  ~~ Copyright 1993-2014 by Goldin-Rudahl Systems, Inc.
 *			    P.O. Box 9648
 *			    North Amherst, MA 01059 U.S.A.
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
 *	$Id: stitch.c,v 1.3 2014/12/17 07:20:39 rudahl Exp $
 *	$Log: stitch.c,v $
 *	Revision 1.3  2014/12/17 07:20:39  rudahl
 *	consolidating Dragon and OpenDragon
 *
 *	Revision 1.2  2002/04/17 23:09:45  rudahl
 *	fixups for 32-bit, long filenames
 *
 *	Revision 1.1  2002/04/09 21:37:16  rudahl
 *	updating to 32-bit and for drugge project
 *	
 *
 *****************************************************************
 *
 *   This program is intended to illustrate the use of many DRAGON
 *   Programmer's Toolkit functions in a standalone application
 *   that does not require DRAGON to run.
 *
 *   The purpose of the program is to combine two subimages into
 *   a side-by-side mosaic and write the results to a new image file.
 *   Some minimal radiometric adjustment can be performed to make the
 *   join line less obvious, by specifying an overlap window. 
 *   The overlap window is specified in terms of the number of pixels
 *   in the two images that are assumed to overlap (represent the
 *   same spatial area). This overlap window value must be
 *   an even number, as it is considered to be split on either side of 
 *   the join line. Within this overlap window,
 *   output pixel data values will be calculated as a weighted average
 *   of the data values at the point for the two input images. 
 *
 *   The user must specify a left and a right image file. Subset
 *   parameters for each file can optionally be supplied. An optional
 *   overlap window parameter determines how wide a band around
 *   the join line will be considered in the radiometric adjustment
 *   process. The default value is zero, i.e. the images are assumed
 *   not to overlap, and no adjustment is done. Finally, the user must 
 *   specify an output image file name.
 *
 *   The program illustrates how to use the DRAGON default data directory
 *   as a default path for image files, thus simplifying the command line
 *   used to invoke the program. Note that this is only possible if the
 *   program is run in the DRAGON system directory.
 *
 *   This program should not be viewed as a paradigm of user interface
 *   design, programming style, or program structure. The main goal here
 *   was to use as many of the toolkit functions as possible, in a manner that
 *   made their use as clear as possible. We have sometimes sacrificed
 *   conciseness, elegance, or strict structuring to this goal.
 *
 ******************************************************************  
 *
 *   NOTE: The rather strange formatting of some of the lines
 *   in this program is intentional. We were trying to keep
 *   lines of code and comments short enough to allow them to be 
 *   easily included, verbatim, in the Toolkit documentation. 
 *
 ******************************************************************  
 *
 *	Revision history
 *
 * 1.0	08-09-92  seg	Created
 *      11-15-93  seg   Updated for V4.0; added error constants
 * 2.0  12-28-95  ktr   adapted for DRAGON Release 4.1, 5.0
 *                      tested with Microsoft C/C++ v 8 (Visual C)
 *			and Watcom C/C++ v 10.0
 * 5.4  4/5/2002 ktr    update for MSC32 (v 4.1p)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <ctype.h>
#include <io.h>
#include "dtypes.h"
#include "dlimits.h"
#include "dhead.h"
#include "ipcos.h"
#include "dtk6.h"
#include "toolerr.h"
#include "files.h"

#include "DragonOb.h"
#include "IpcWrap.h"

/* Prototypes for functions in this module */
int CmdSetFileSub(char * argv[],CMDDESCRIPTOR_T * cmd);
void check_input_files(void);
void build_filenames(const char* dpath, char * outfileBuf, 
		     const size_t outfileBufSize);
void open_input_images(void);
void adjust_datavals(byte * mainbuf, const byte * secondbuf, 
                    const int lpix, const int rpix);
int processOneHorizPair(const char * outfile);

/**/
#define TRUE 1
#define FALSE 0
#define MAX_OVERLAP_WINDOW 100 

/* Constants for error numbers. These
 * act as keys into the STCHMSG.DAT 
 * message file.
 */ 
#define STE_OVER_TOOBIG    -101
#define STE_OVER_ODD       -102
#define STE_CREATE_FILE    -103
#define STE_NOMEM          -104
#define STE_IMGLINE_READ   -105
#define STE_IMGLINE_WRITE  -106
#define STE_NOFILE         -107
#define STE_BAD_FILENAME   -108
#define STE_OPEN_FILE      -109
#define STE_SUBSET_TOOBIG  -110
  /* NOTE: we deliberately omitted a message 
   * for this symbol from the message file,
   * to illustrate the behavior of the
   * error/message functions.
   */
#define STE_SUBSET_REVERSE -111

/* Constants for message numbers. These
 * also act as keys into the STCHMSG.DAT 
 * message file.
 */ 
#define STM_IMAGE_IS        150
#define STM_PROGRESS        151
#define STM_NOSUBSET        152
#define STM_OVERWIN         153
#define STM_OUTDIM          154

/* static or global data items */
int quietflag=0;
int helpflag=0;
int windowpix= 0; 
          /* number of pixels in smoothing window */
int totlines, totpix;  
          /* number of lines, pixels per line in output img */
char leftfile[PATH_MAX];
char rightfile[PATH_MAX];
char s_czOutfile[PATH_MAX];
char paramfile[PATH_MAX];
char * leftstrings[5]={leftfile,NULL,NULL,NULL,NULL};
	  /* for parsing -l command line parameters */
int leftsub[5]; 
          /* subarea dimensions for left file */
	  /* element 0 is a flag - if 1, use subarea */
char * rightstrings[5]={rightfile,NULL,NULL,NULL,NULL};
	  /* for parsing -r command line parameters */
int rightsub[5];  
          /* subarea dimensions for right file */

IFILEHANDLE lfh, rfh, ofh;
          /* file handles for left, right, output files*/
char msgbuf[D_PRINTBUF],numbuf[D_NUMBUF],numbuf2[D_NUMBUF];
IHEAD hdr; 
char dpath[CONFIGSTRLEN+1];

char * Banner[] =
{"\n                     STITCH - Stitch together image files",
 "                Copyright (c) 1993-2002 Goldin-Rudahl Systems Inc.\n",
 "" } ;

char * Help[] =
{"\nusage: STITCH -l lfile [# # # #] -r rfile [# # # #] -o ofile [-w #] [-q]",
 "\t-f paramfile \tfile containing processing parameters",
 "\t-l lfile \timage file for left side of mosaic",
 "\t-r rfile \timage file for right side of mosaic",
 "\t\t\t# # # # indicates optional subset parameters",
 "\t\t\t(xmin ymin xmax ymax)",
 "\t-o ofile \timage file to hold output mosaic",
 "\t-w #\t\toverlap window for radiometric adjustment",
 "\t\t\tmeasured in number of pixels (must be even)",
 "\t-q (quiet)\tdo not display progress messages",
 "" } ;

CMDDESCRIPTOR_T cmds[] =
    {
    "l",1,dtk6_CmdSetFile,"ID",&leftstrings[0],
    "r",1,dtk6_CmdSetFile,"ID",&rightstrings[0],
//    "l",1,CmdSetFileSub,"ID",&leftstrings,
//    "r",1,CmdSetFileSub,"ID",&rightstrings,
    "o",1,dtk6_CmdSet1string,"WX",&s_czOutfile,
    "w",1,dtk6_CmdSet1int,"1:20",&windowpix,
    "q",0,dtk6_CmdSetFlag,"Q",&quietflag,
    "?",0,dtk6_CmdSetFlag,"?",&helpflag,
    0
    } ;


/**/
void main(int argc,char ** argv)
    {
    int argCnt = 1, status = 0;
#ifdef NOMORE
    int i,status;
    int ln, px; 
         /* line, pixel counters */
    int rpix0; 
         /* position of first pixel in right image, */
	 /* in combined image buffer */
    int rnpix; 
         /* number of pixels requested per line, */
         /* from right file */
    int rln, lln; 
         /* line counters for left, right images */
    int plen;  /* length of path from config file */
    int errnum = 1;
    byte * linebuf=NULL;
         /* main data buffer for image reads/writes */
    byte * secondbuf=NULL;
         /* needed if overlap specified */
#endif
//    ipcLogInit(NULL,NULL,NULL,"DS","1");
//    ipcLogInit(NULL,"stitch.err","stitch.trc","ST","1");
    /* always need to do this first */
    dtk_init(NULL);
    /* enable use of application messages */
    dtk_RegisterMsgFile("STCHMSG.DAT");
    /* parse the command line */
    paramfile[0] = '\0';
    while (argCnt < argc)
      {
	char swtch[5];
	strcpy_array(swtch,argv[argCnt])
//printf("arg %d = '%s', '%s'\n",argCnt,swtch,argv[argCnt+1]);
	if (strcmp(swtch,"-f") == 0)
	    strcpy(paramfile,argv[argCnt+1]);
	else if (strcmp(swtch,"-l") == 0)
	    leftstrings[0] = strdup(argv[argCnt+1]);
	else if (strcmp(swtch,"-r") == 0)
	    rightstrings[0] = strdup(argv[argCnt+1]);
	else if (strcmp(swtch,"-o") == 0)
	    strcpy(s_czOutfile,argv[argCnt+1]);
	else
	    dtk_Fatal(DTKE_BAD_COMMAND,
		      "Bad command line argument: %1",swtch);
	argCnt+=2;
      }

//    status=dtk6_ProcessCommandLine(argc,argv,cmds,&errnum);
    if (!quietflag)
	dtk_banner(Banner);
    if (status < 0)
	exit(1);
    if ((argc < 2) || helpflag)
	dtk_help(Help);

    /* Update argv and argc. This is for the case 
     * where there may be arguments at the end of the 
     * command line that don't use switches
     * prefaced by the minus sign. For instance, 
     * many DRAGON utilities end their command lines 
     * with <infile> <outfile>. In this case, though,
     * since we have THREE files to specify, we 
     * set it up so all arguments are handled 
     * by switches. Thus the following two lines 
     * are not entirely necessary. 
     * However, they let us give a nice error message
     * if the user added extra parameters.
     */
//    argv += status;
// /   argc -= status;

//    if (argc > 0) /* extra stuff on command line */
//        dtk_Fatal(DTKE_BAD_COMMAND,
//          "Bad command line argument: %1",*argv);
        /* Use a standard error code defined by 
         * the Toolkit. If not found, use a custom
         * message.
	 * Fatal errors automatically exit 
         */
    if (strlen(paramfile) == 0)
        status = processOneHorizPair(s_czOutfile);
    else
        {
	char czParamLine[1026];
	long offset = 0;
	ushort ublend = 0;
	char * tpath = NULL;
	size_t inImageNo = 0;
#define MAX_INIMAGES 30
	typedef struct
	    {
	    char * fname;
	    ushort urow;
	    ushort iline,ipix,nlines,npix,oline,opix;
	    } IMAGE_PARAM_T;
	IMAGE_PARAM_T imageParam[MAX_INIMAGES];
	tpath[0] = '\0';
	memset(&imageParam,0,sizeof(imageParam));

	/* param file contents and format:
	 * we're going to tile a bunch of files into a horiz/vertical matrix.
	 * Each image, by assumption, has a subregion which is desired.
	 * If that subregion is less than the entire image, then adjacent
	 *  subimages can be blended by looking outside the subregion
	 * First, we tile each horizontal strip into a subimage
	 *  using processOneHorizPair as many times as needed
	 * Then we combine the horizontal strips in top to bottom sequence
	 * each input image is described in the param file by
	 *  its path/filename
	 *  its line/pixel # of upper left corner of desired region
	 *  its line/pixel count of desired subregion
	 *  its offset from the upper left of the first mage subregion,
	 *   Format: Row=n filename iline ipix nlines npix oline opix
	 * These per-image parameters are PRECEEDED by name=value params
	 * with no embedded whitespace. current names are:
	 *   Result=path/name # of final output
	 *   Blend=count      # number of lines/pixels 
	 *   Tmp=path         # for temporary files; default is %TMP%
	 *   #                # the hash mark starts a comment line
	 * all key words start in position 0 of the line
	 */
	while(rsfgets(czParamLine,sizeof(czParamLine),
		      paramfile,offset) != NULL)
	    {
	    offset = -1;
	    strtok(czParamLine," \t#\r\n");
	    puts(czParamLine);
	    if (strncmp(czParamLine,"Row=",4) == 0)
		{
		char * pNext = strtok(NULL," \t"); 
		if (inImageNo > AY_COUNT(imageParam))
		    break;
		imageParam[inImageNo].urow = atoi(czParamLine+4);
		imageParam[inImageNo].fname = strdup(pNext);
		pNext = strtok(NULL," \t"); 
		imageParam[inImageNo].iline = atoi(pNext);
		pNext = strtok(NULL," \t"); 
		imageParam[inImageNo].ipix = atoi(pNext);
		pNext = strtok(NULL," \t"); 
		imageParam[inImageNo].nlines = atoi(pNext);
		pNext = strtok(NULL," \t"); 
		imageParam[inImageNo].npix = atoi(pNext);
		pNext = strtok(NULL," \t"); 
		imageParam[inImageNo].oline = atoi(pNext);
		pNext = strtok(NULL," \t"); 
		imageParam[inImageNo].opix = atoi(pNext);
		printf("img# %d: %s row #d "
		       "iline=%d ipix=%d nlines=%d npix=%d oline=%d opix=%d\n",
		       inImageNo,imageParam[inImageNo].fname,
		       imageParam[inImageNo].urow,
		       imageParam[inImageNo].iline,
		       imageParam[inImageNo].ipix,
		       imageParam[inImageNo].nlines,
		       imageParam[inImageNo].npix,
		       imageParam[inImageNo].oline,
		       imageParam[inImageNo].opix);
		inImageNo++;
		}
	    else
	        {
		if (strncmp(czParamLine,"Tmp=",4) == 0)
		    tpath = strdup(czParamLine+4);
		else if (strncmp(czParamLine,"Result=",7) == 0)
		    { strcpy_array(s_czOutfile,czParamLine+7); }
		else if (strncmp(czParamLine,"Blend=",6) == 0)
		    ublend = atoi(czParamLine+6);
		else
		    continue; /* empty line? unknown name? */
		}
	    }
        }
    exit((status<0) ? 1 : 0);
    }

/* process one pair of files to produce one output file.
 * Input file arguments are in leftfile & rightfile,
 *			leftsub and rightsub
 * @param    outfile         path and name of result file   
 * @return   0 if OK
 */ 
int processOneHorizPair(const char * outfile)
  {
    char czOutfile[PATH_MAX];
    int i,status;
    int ln, px; 
         /* line, pixel counters */
    int rpix0; 
         /* position of first pixel in right image, */
	 /* in combined image buffer */
    int rnpix; 
         /* number of pixels requested per line, */
         /* from right file */
    int rln, lln; 
         /* line counters for left, right images */
    int plen;  /* length of path from config file */
    int errnum = 1;
    byte * linebuf=NULL;
         /* main data buffer for image reads/writes */
    byte * secondbuf=NULL;
         /* needed if overlap specified */
    strcpy_array(czOutfile,outfile);
    if (windowpix > MAX_OVERLAP_WINDOW)
	{
	dtk_Error(STE_OVER_TOOBIG,
           "Overlap window %1 too large; maximum possible %2",
           itoa(windowpix,numbuf,10),
           itoa(MAX_OVERLAP_WINDOW,numbuf2,10));
	return STE_OVER_TOOBIG;
	}
    else if (windowpix % 2 != 0)  
	{
	dtk_Error(STE_OVER_ODD,
          "Overlap window size (%1) must be even",
           itoa(windowpix,numbuf,10));
	return STE_OVER_ODD;
	}

    /* make sure the user entered 
     * the filenames we need 
     */
    check_input_files();

    /* apply filename defaults, 
     * check filenames for legality 
     */
    plen = dtk_GetConfig("DPATH",dpath,sizeof(dpath));  
    /* get default data path if available */
    if (plen == 0)     
        /* not found - probably not running 
         * in DRAGON directory 
         */
	dpath[0] = 0;  /* empty string */
    build_filenames(dpath,czOutfile,sizeof(czOutfile));
    if (!quietflag)
	{
	dtk_ShowMsg(STM_IMAGE_IS,"","Left",leftfile);
	dtk_ShowMsg(STM_IMAGE_IS,"","Right",rightfile);
	dtk_ShowMsg(STM_IMAGE_IS,"%1 image file is %2",
                "Output", outfile);
	}
    /* Open the input files, and make sure 
     * the subareas requested (if any)
     * make sense. If an impossible subset 
     * was entered, use the whole file,
     * but give the user a warning message. 
     * If the number of lines specified
     * for the two input files is not the same, 
     * use the minimum of the two,
     * and again give a warning.
     * This function sets the global variables
     * 'totlines' and 'totpix' .
     */
    open_input_images();

    /* set dimensions for the output file */
    dtk_ImageHdrInit(&hdr,totlines,totpix);
    /* open the file, requesting on-going 
     * calculation of statistics 
     */
    ofh = 
       dtk_ImageFileWriteOpen(outfile,&hdr,"I",TRUE);
    if (ofh == NULL)  /* error */
	dtk_Fatal(STE_CREATE_FILE,
         "Cannot create output image file %1",
	 outfile);

    /* now, we need a line buffer big enough 
     * for the combined data from the two
     * input files
     */
    linebuf = malloc(totpix);
    if (linebuf == NULL)  /* allocation error */
        dtk_Fatal(STE_NOMEM,
           "Insufficient memory for data buffer");
     
    rpix0 = leftsub[3] - leftsub[1] + 1;
    rnpix = rightsub[3] - rightsub[1] + 1;
    
    if (windowpix > 0) /* overlap requested */
        {
        secondbuf = malloc(rnpix);
        if (secondbuf == NULL)  /* allocation error */
            dtk_Fatal(STE_NOMEM,
               "Insufficient memory for data buffer");
        }

    status = 0;
    for (ln=0, lln = leftsub[2], rln = rightsub[2];
	(ln < totlines) && (status >= 0); ln++)
    	{
	/* fill the first half of the buffer 
         * from the left file 
         */
	status = dtk_ImageFileGetLine(lfh,lln,
                totpix,&linebuf[0],leftsub[1],rpix0);
	if (status < 0)
	    {
	    dtk_Error(STE_IMGLINE_READ,
              "reading line %1 from %2 image file",
              itoa(rln,numbuf,10),"left");
	    break;
	    }
 
	/* Now, if no overlap, fill the second part 
         * of the buffer from the right file. 
         * Otherwise, we read that data into
         * a separate buffer and then do 
         * weighted averaging 
         */
        if (windowpix == 0)
  	    status = dtk_ImageFileGetLine(rfh,rln,
                 totpix,&linebuf[rpix0], rightsub[1],rnpix);
        else
            {
            status = dtk_ImageFileGetLine(rfh,rln,
                     rnpix,secondbuf,rightsub[1],rnpix);
            if (status >= 0)            
                adjust_datavals(linebuf,secondbuf,
                                rpix0,rnpix);              
                /* this function computes the 
                 * distance-weighted average of the
                 * data within the overlap window, 
                 * then copies remaining data from 
                 * secondbuf to linebuf
                 */
            }
	if (status < 0)
	    {
	    dtk_Error(STE_IMGLINE_READ,
              "reading line %1 from %2 image file",
              itoa(rln,numbuf,10),"right");
	    break;
	    }

	/* now, write the combined line 
         * to the output file 
         */
	status = dtk_ImageFilePutLine(ofh,ln,linebuf);

	if (status < 0)
	    {
	    dtk_Error(STE_IMGLINE_WRITE,
            "Cannot write line %1 of output file",
            itoa(ln,numbuf,10));
	    break;
	    }
	lln += 1;
	rln += 1;
	if ((!quietflag) && (((ln+1) % 10) == 0))
	    {
	    dtk_ShowMsgAt(10,5,STM_PROGRESS,
               "Finished writing line %1",
               itoa(ln+1,numbuf,10));
	    }
	}

    dtk_ShowMsg(0,"\n");   /* newline after the progress messages */ 

    /* Whether successful or not, we're done. 
     * Close the files and exit.
     * Delete the output file if we got an error.
     */

    dtk_ImageFileClose(ofh); 
    dtk_ImageFileClose(rfh);
    dtk_ImageFileClose(lfh);
    free(linebuf);
    if (windowpix > 0) 
        free(secondbuf);
    if (status < 0)
	remove(outfile);
    return status;
    }

/**/
int CmdSetFileSub(char * argv[],CMDDESCRIPTOR_T * cmd)
	/* Fn suitable to be included in 
         * CMDDESCRIPTOR table
	 * Handles 5-argument selector 
         * by setting *cmd->resultptr[] to point to 
         * either one or the next 5 tokens as strings.
	 * The strings are not copied. 
         * Either there must be only one argument 
         * (which will be a filename) or else
	 * there must five items - 
         * a filename plus x0 y0 x1 y1 for the subarea 
         * to be used. We will convert these to
	 * integers later.
	 * Return the number of items removed 
         * from 'argv' = either 1 or 5.
	 * dtk_ProcessCommandLine has guaranteed 
         * that a token is available.
	 */
    {
    char ** rptr = (char **)cmd->resultptr;
    *rptr++ = argv[1];
printf("CmdSetFileSub:: file=%s\n",*(rptr-1));
    if (!isdigit(*argv[2]))
	return 1;
    *rptr++ = argv[2];
    if (!isdigit(*argv[3]))
	return -1;   
    /* error- must have all 4 subarea params if any */
    *rptr++ = argv[3];
    if (!isdigit(*argv[4]))
	return -1;
    *rptr++ = argv[4];
    if (!isdigit(*argv[5]))
	return -1;
    *rptr++ = argv[5];
    return 5;
    }
/**/
void check_input_files()
	/* Massage the input file names 
         * in preparation for actual
	 * processing. This includes translating 
         * the subset area parameters to integers. 
         * This is primarily a factorization
	 * to make the main function more readable. 
         * We still use global variables and 
         * we can exit directly from this
	 * function in case of a user error.
	 */
    {
    size_t i;
    if (leftstrings[0] == NULL)
	dtk_Fatal(STE_NOFILE,
        "No filename specified for %1 image","left");
    else 
        /* copy the name to a more useful location */
	strcpy_array(leftfile,leftstrings[0]);

    if (leftstrings[1] == NULL) 
        /* no subarea specified */
	leftsub[0] = FALSE;
    else
	{
	leftsub[0] = TRUE;
	for (i = 1; i < 5; i++)
	    leftsub[i] = atoi(leftstrings[i]);
	/* check the validity later, 
         * when we know the actual image size 
         */
	}

    if (rightstrings[0] == NULL)
	dtk_Fatal(STE_NOFILE,
        "No filename specified for %1 image","right");
    else  /* copy the file name */
	strcpy_array(rightfile,rightstrings[0]);

    if (rightstrings[1] == NULL) 
        /* no subarea specified */
	rightsub[0] = FALSE;
    else
	{
	rightsub[0] = TRUE;;
	for (i = 1; i < 5; i++)
	    rightsub[i] = atoi(rightstrings[i]);
	}
    }
/**/
void build_filenames(const char* dpath, char * outfileBuf, 
		     const size_t outfileBufSize)
       	/* Construct input and output file names, 
         * using DRAGON default path if available,
         * and standard DRAGON image file extension. 
         * This will also check the legality of the 
         * filenames the user entered.
	 * Once again, this is just a simplification. 
         * If there is an error
	 * we will exit directly from here, 
         * rather than return, and we use
	 * global filename variables.
	 * @param dpath		
	 * @param outfileBuf	  current name of result file,
	 *			  which will be replaced by revised name
	 * @param outfileBufSize  sizeof outfileBuf
	 */
    {
    int status;
    char * brk;
    char tempfile[PATH_MAX];

    /* First, check for multiple directories in the
     * default data path. If more than one directory,
     * use the first one.
     */
    brk = strchr(dpath,';');
    if (brk)
       *brk = '\0'; 
    /* truncate at the first semicolon, if any */
       
    status = dtk_FilenameBuild(leftfile,dpath,
                               "IMG",tempfile,sizeof(tempfile));
    if (status < 0) // == DTKE_BADFILENAME)
	dtk_Fatal(STE_BAD_FILENAME,
		  "Invalid name %1 for %2 image",leftfile,"left");
    strcpy(leftfile,tempfile);  
    /* copy back to file name buffer */

    status = dtk_FilenameBuild(rightfile,dpath,
		"IMG",tempfile,sizeof(tempfile));

    /* if we pass -1, dtk_Fatal will not  */
    /* try to retrieve the message from   */
    /* the message file. */
    sprintf(msgbuf,"Invalid name %s for right image",rightfile);
    if (status < 0) // == DTKE_BADFILENAME)
	dtk_Fatal(-1,msgbuf);
    strcpy(rightfile,tempfile);  
    /* copy back to file name buffer */

    status = dtk_FilenameBuild(outfileBuf,dpath,
			       "IMG",tempfile,sizeof(tempfile));
    if ((status == DTKE_BADFILENAME) || (strlen(tempfile) > outfileBufSize))
	dtk_Fatal(status,NULL,tempfile);
    strcpy(outfileBuf,tempfile);  
    /* copy back to file name buffer */
    }
/**/

void open_input_images()
	/* This function calls dtk_ImageFileReadOpen 
         * for the left and right image files, and 
         * checks subset parameters, if any, against 
	 * the subarea parameters entered by the user.
         * If the user has specified illegal subset 
         * parameters, this function uses the full 
         * image, and displays a warning.
	 * The function also sets the global 
	 * variables 'totlines' and 'totpix', 
         * to indicate the dimensions of the output file.
	 */
    {
    int lines, pix, ok;

    lfh = dtk_ImageFileReadOpen(leftfile);
    if (lfh == NULL)  /* error */
	dtk_Fatal(STE_OPEN_FILE,
        "Cannot open %2 image file %1",
         leftfile,"left");
    rfh = dtk_ImageFileReadOpen(rightfile);
    if (rfh == NULL)  /* error */
	dtk_Fatal(STE_OPEN_FILE,
        "Cannot open %2 image file %1",
         rightfile,"right");

    lines = dtk_ImageFileLines(lfh);
    pix   = dtk_ImageFilePixels(lfh);
    ok = TRUE;
    if (!quietflag)
	{
	sprintf(msgbuf,
       "Left image dimensions: %d lines by %d pixels per line",
		lines, pix);
	dtk_ShowMsg(0,msgbuf);
	}
    if (leftsub[0])   /* they requested a subset */
	{
	if ((leftsub[1] >= pix) || (leftsub[2] >= lines))
	    {
	    ok = FALSE;
            /*  Note - there is no message corresponding to
             *  the symbol STE_SUBSET_TOOBIG, so we should
             *  always see the message below if the
             *  subset parameters are wrong.
             */
	    dtk_Warning(STE_SUBSET_TOOBIG,
            "You silly thing: left xmin/ymin is larger than the image!");
	    }
	else if ((leftsub[3] >= pix) || (leftsub[4] >= lines))
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_TOOBIG,
            "Invalid %1 image subset: %2 or %3 too large","left",
              "xmax", "ymax");
	    }
	else if (leftsub[1] >= leftsub[3])
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_REVERSE,
            "Invalid %1 image subset: %2 is larger than %3",
            "left","xmin","xmax");
	    }
	else if (leftsub[2] >= leftsub[4])
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_REVERSE,NULL,
            "left","ymin","ymax");
	    }
        else if (!quietflag)
            {
            sprintf(msgbuf,
            "Subset area for left image: (%d,%d) to (%d,%d)",
            leftsub[1],leftsub[2],leftsub[3],leftsub[4]);
	    dtk_ShowMsg(0,msgbuf);
            }
	if (!ok)
	    {
	    dtk_Warning(STM_NOSUBSET,"Using entire image area");
	    leftsub[0] = FALSE;
	    leftsub[1] = leftsub[2] = 0;
	    leftsub[3] = pix - 1;
	    leftsub[4] = lines - 1;
	    }
	}
    else
	{
	leftsub[1] = leftsub[2] = 0;
	leftsub[3] = pix - 1;
	leftsub[4] = lines - 1;
	}
    totpix = leftsub[3] - leftsub[1] + 1;
    totlines = leftsub[4] - leftsub[2] + 1;

    /* now... do the same thing for the right image */
    lines = dtk_ImageFileLines(rfh);
    pix   = dtk_ImageFilePixels(rfh);
    ok = TRUE;
    if (!quietflag)
	{
	sprintf(msgbuf,
       "Right image dimensions: %d lines by %d pixels per line",
		lines, pix);
	dtk_ShowMsg(0,msgbuf);
	}
    if (rightsub[0])   /* they requested a subset */
	{
	if ((rightsub[1] >= pix) || (rightsub[2] >= lines))
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_TOOBIG,
            "You silly thing: right xmin or ymin is larger than the image!");
	    }
	else if ((rightsub[3] >= pix) || (rightsub[4] >= lines))
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_TOOBIG,
            "Invalid %1 image subset: %2 or %3 too large","right",
              "xmax", "ymax");
	    }
	else if (rightsub[1] >= rightsub[3])
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_REVERSE,
            "Invalid %1 image subset: %2 is larger than %3",
            "right","xmin","xmax");
	    }
	else if (rightsub[2] >= rightsub[4])
	    {
	    ok = FALSE;
	    dtk_Warning(STE_SUBSET_REVERSE,
            "Invalid %1 image subset: %2 is larger than %3",
            "right","ymin","ymax");
	    }
        else if (!quietflag)
            {
            sprintf(msgbuf,
            "Subset area for right image: (%d,%d) to (%d,%d)",
            rightsub[1],rightsub[2],rightsub[3],rightsub[4]);
	    dtk_ShowMsg(0,msgbuf);
            }
	if (!ok)
	    {
	    dtk_Warning(STM_NOSUBSET,"Using entire image area");
	    rightsub[0] = FALSE;
	    rightsub[1] = rightsub[2] = 0;
	    rightsub[3] = pix - 1;
	    rightsub[4] = lines - 1;
	    }
	}
    else
	{
	rightsub[1] = rightsub[2] = 0;
	rightsub[3] = pix - 1;
	rightsub[4] = lines - 1;
	}

    /* Normally, dtk_Error and dtk_Warning do not 
     * display their messages right away. Instead, they
     * push them onto the error stack, which is dumped
     * and displayed just as the program exits. Since
     * we do not want to wait that long in the case of
     * any warnings generated above, we explicitly test
     * whether there are any messages, and if so,
     * force them to be displayed - then clear them so
     * we will not see them again.
     */  
    if (dtk_ErrorMsgCount() > 0)
        {
        dtk_ErrorMsgDisplay();  /* show any warnings */
        dtk_ErrorMsgClear();
        }
    totpix += rightsub[3] - rightsub[1] + 1;
    totlines = min(totlines,
                   (rightsub[4] - rightsub[2] + 1));
    if (windowpix > 0) 
        {
        totpix -= windowpix;  
        /* overlap area should not be counted twice*/
        if (!quietflag)
            {
            dtk_ShowMsg(STM_OVERWIN,
              "Requested overlap window: %1",
               itoa(windowpix,numbuf,10));
            }
        }
    if (!quietflag)
        {
        dtk_ShowMsg(STM_OUTDIM,
        "Output image will be %1 lines by %2 pixels per line",
        itoa(totlines,numbuf,10),itoa(totpix,numbuf2,10));
        }
    }

/**/
void adjust_datavals(byte * mainbuf, 
                     const byte * secondbuf, 
                     const int lpix, const int rpix)
	/* This function combines two buffers 
         * of data into 'mainbuf', overlapping an area 
         * 'windowpix' pixels in size. The "join line"
         * between the two buffers is assumed to occur 
         * at 'windowpix'/2.
	 * For pixel positions in the overlap area, 
         * the function calculates
	 * the final value as a weighted average of
         * the two corresponding values in the two 
         * buffers. For pixel positions beyond 
         * the window, the function simply copies 
         * the data from secondbuf to mainbuf.
         * 'lpix' is the number of pixels of 
         * left-image data, initially in 'mainbuf'. 
         * 'rpix' is the number of pixels of right-hand
         * data, in 'secondbuf'. The overlap pixels are 
         * counted in both these totals.
	 */
    {
    int j,lp,rp;
    int halfwind;

    halfwind = windowpix / 2;
    lp = lpix - windowpix; 
    rp = 0;    
    for (j = -1 * halfwind; j < halfwind; j++, lp++, rp++)
        mainbuf[lp] = (byte)
        ( ((unsigned)mainbuf[lp] * (halfwind - j) + 
           (unsigned)secondbuf[rp] * (halfwind + j))/
           windowpix);
    /* now, copy the rest of the data */
    while ((lp < totpix) && (rp < rpix))
        {
        mainbuf[lp] = secondbuf[rp];
        lp += 1;
        rp += 1;
        }

    }
