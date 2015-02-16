/*
 *	filename SIGNATURE.H
 *		$Revision: 1.5 $ $Date: 2014/12/29 03:28:29 $
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
 * 	~~ EndC
 ****************************************************************
 *
 *	prototypes and definitions for signature statistics
 *      modules sigstat.c and sigfio-o.c. Split from sigstats.h 
 *	and moved to library level on 15 August 2006.
 ************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	Revision History
 *  4/7/91   seg  Modified statrec structure to
 * 		  allow use of `clustering data
 *		  as signature statistics
 *  4/14/91  SEG  Further modifications - defined new
 *		  48 bit integer to handle really large
 *		  numbers.
 *  5/4/91   SEG  Added new bandfile[] fields - holds
 *		  img data used for bands 1-4
 *  5/12/91  SEG  Moved MoveSig to sigstat.c, added prototype
 *		  here.
 *  6/8/91   SEG  Moved prototypes for all external classif.
 *                  fns to here, in preparation for move to
 *                  zortech for V 3.05
 *
 *  12/28/91 SEG  Implemented thresholding for MAX & MDM -
 *                  modified prototypes here.
 *  3/04/93 SEG  Began adding maskimg to prototypes
 *  7/27/97 ktr	moved scatpl-o declarations here from dragon.h
 *  2/23/98 ktr	added SeedsTableIO
 *  5/18/98 ktr added ComputeCandidateMeans() in clsclu-o
 *  4/18/99 ktr	revised args to MDMClassImage()
 *  4/26/99 seg modified init_modarray to return number of bands in sigs
 *  5/9/99  seg modified statrec structure to include color name and
 *              color value fields
 *  12/3/99 ktr	added PrepareClassReport to replace SHOW-CLASS,
 *		.FTABLE etc in DRAGCLx.WFT. 
 *  6/4/00 ktr  got rid of decl. for reclass(), which is now local
 *              to clsbox-o.c; similarly for SigCalc();
 *              gave return type to settpix().
 *  8/27/00 seg Added prototypes for initClstable, in clsbox-o.c.	
 * 5.5	2005-2-16 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-8-1 ktr	moved here from DragonCommon/include - only for CGATE
 * 	2005-8-14 seg	explicitly pass index array to SetIndices
 *	2006-1-20 ktr	added buffer size arg to sigio()
 */

#ifdef __cplusplus
extern "C" { 
#endif

#ifndef SIGNATURE_H							   
#define SIGNATURE_H

#ifdef SIGSTAT_C
#define STAT_CONSTRUCT_ERR -1
#define STAT_ALLOC_ERR -2
#define STAT_FREE_ERR -10
#endif

/* note now requires DTYPES.H, DLIMITS.H */

/* moved here from cg-data.h seg 2006-Aug-15 */
/* moved here from grsproc1.h ktr 2005-Apr-24 */
/* ~~~ This doesn't match long term limits but leave for now */
#define EXT_SIGNAME_SZ 100 	// >= 32 UTF-8 chars - 2005-2-16


/* moved from DRAGON.H - 9/23/89 */

typedef struct 
    {
    UINT32 base;
    UINT16 extra;
    } UINT48;       /* special extra long int for signature calcs */     

struct re64 
    {
    double realnum;    
    int dummy;        /* need dummy word for compatibility w/ WForth */     
    } ;

struct statrec        /* signature statistics structure defn  */
    {
    unsigned long numpt; /* number of pix defining signature     */
    unsigned minv[D_NBAND];   /* minima by band */
    unsigned maxv[D_NBAND];   /* maxima by band */ 
    unsigned mean[D_NBAND];   /* means by band  */
    unsigned lower[D_NBAND];  /* lower bounds for boxcar class */ 
    unsigned upper[D_NBAND];  /* upper bounds for boxcar class */
    unsigned long hist[D_NBAND][65];/* histograms by band */
    unsigned long sumx[D_NBAND];     	/* sum of values by band */
    UINT48 sumsqx[D_NBAND];   	/* sum of squares of band values */
    UINT48 sumprod[D_NBAND*(D_NBAND-1)/2]; 	/* sum of xy products for each combo of bands */
    double vars[D_NBAND];     /* variances by band */
    double covar[D_NBAND*(D_NBAND-1)/2];    /* covariances for each combo of bands    */
    int valid;		/* 1 => record currently valid, else 0 */
    char name[EXT_SIGNAME_SZ];	/* of the signature */
    char source[8];     /* source - CLUSTER, TRAINED, etc.   */
    char bandfile[D_NBAND][60]; /* up to four file "node names" - strip off */
                         /* extension and path */
    char colorName[64];  /* optional - name of color to use for class */
    unsigned short redVal; /* optional - value of red component of color in */
                           /* colorName - 8 bits, stored in short for alignment */
    unsigned short greenVal; /* green component value */
    unsigned short blueVal;  /* blue component value */
    double sigThresh;    /* per signature threshold to be applied only if
			    not zero.
			  */
    } ;

typedef struct 
    {
    byte lower[D_NBAND];  /* lower bounds for boxcar class */ 
    byte upper[D_NBAND];  /* upper bounds for boxcar class */
    } SIGBOUNDS;

#define MAXMEANS 64

extern SIGBOUNDS modarray[D_NCLS];
    /* initialized by sigstat.c, used by callback in MOD function */

/*  NOTE: the sumprod and covar arrays in the structure above are   */
/*  assigned in the order: <0,1>, <0,2>, <0,3>, <1,2>, <1,3>, <2,3> */								      
/*  where 0 is first band, 1 is second, etc.                        */
/*  The array inxarray, defined in IMG.C, holds the actual index    */
/*  into sumprod and covar for each combination of bands.           */


enum SG_FNS {   SIGLOAD , SIGCLOSE , SIGWRT , SIGDUMP } ;
     /* used by sigfio  */

/* functions in Sigstat.c */

#if !defined LIBDTK_H

/* don't make these visible in the DTK */
struct statrec * getstat(unsigned);
int savestat(unsigned);
int clearstats(void);
int MoveSig(int,int);
int init_modarray(int nclass); /* now returns # bands in class */

/* sigfio-o.c */
int sigio(enum SG_FNS code,const char * filename,int recno,int sigayno,
	  char * signame, uint uSignameSize);
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
	 *
	 * @return		0 OK
	 *			-1 => unknown  code
	 *			for WRITE: -4 if no valid signature, -2 if write err
	 *			for READ: -1, -3, -4 for what?
	 */ 

#endif //not defined LIBDTK_H

#if DRAGON_VER >= 6
#define CMD_NUMLABELS 33	
  // number needed for CMD_PARAMBLOCK_t
  // increased from 17 8/15/07

#define CLSBUFSIZE 128  	
  // 33 utf-8 chars plus some place for delimiter and digits
#else
#define CMD_NUMLABELS 17
#define CLSBUFSIZE 100
  // 33 utf-8 chars
#endif

struct ClsNameStruct
    {
    char czName[CMD_NUMLABELS][CLSBUFSIZE];
    };

/* Open and read all the signatures in a signature file.
 * Signatures are stored in static array StatFile.
 * Copy the signature names to pSigNames.
 * @param pczFilename   Name/path of file to read
 * @param pSigNames     Ptr to structure for saving sig mames
 * @return number of sigs read, or negative if some error.
 */   
int readSignatures(const char* pczFilename, struct ClsNameStruct * pSigNames);

/* Write all the signatures that are current stored in
 * static array StatFile to the file passed in.
 * @param pczFilename   Name/path of file to read
 * @param iSigCount      Number of signatures to write
 * @return 0 if okay, or negative if some error.
 */   
int writeSignatures(const char* pczFilename, int iSigCount);

/* Return a requested signature. Returns null if
 * the iSigNo (signature number) is not valid.
 */  
struct statrec * getSignature(int iSigNo);

/* Figure out how many bands are represented by
 * the currently loaded signatures, based on
 * the signature histograms.
 * @return number of bands or 0 if signatures not initialized
 */
int getBandCount();

#endif //not defined SIGNATURE_H
#ifdef __cplusplus
  }
#endif
