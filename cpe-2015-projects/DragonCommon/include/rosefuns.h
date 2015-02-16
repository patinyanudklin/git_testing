/****************************************************************
 *		 >>  ROSEFUNS.H <<
 *
 *		  by Kurt Rudahl
 *
 *	  ~~ Copyright 1994-2014 Kurt Rudahl and Sally Goldin
 *	  ~~ EndC
 ***************************************************
 *  $Id: rosefuns.h,v 1.7 2014/02/10 04:12:37 rudahl Exp $
 *  $Log: rosefuns.h,v $
 *  Revision 1.7  2014/02/10 04:12:37  rudahl
 *  no longer want screenfile in rosetta
 *
 *  Revision 1.6  2014/02/09 04:27:08  rudahl
 *  lint
 *
 *  Revision 1.5  2005/08/02 02:14:34  rudahl
 *  fixed an FMSIZE
 *
 *  Revision 1.4  2005/07/23 08:15:55  rudahl
 *  fine-tuning geotiff
 *
 *  Revision 1.3  2005/07/03 13:12:57  rudahl
 *  moved CalcStats from fconvert to rosefuns
 *
 *  Revision 1.2  2005/06/27 11:35:47  rudahl
 *  adapted fconvert for linux, v 5.8 imageWriter
 *
 *  Revision 1.1.1.1  1999/03/11 00:35:18  rudahl
 *  first checkin of only SOME common dirs
 *
 * Revision 1.2  1995/01/23  09:43:40  tower
 * checkin for class class5_0
 * 
 *
 ***************************************************
 *
 * Date structures used by multiple Tools library programs,
 * and prototypes for ROSEFUNS.C functions.
 *
 ****************************************************************
 *    Modification History
 *
 *    Version	Who		What & Why
 * 1.0 12/28/94	KTR	Created by extraction from FCONVERT
 *     1/7/95 ktr	added void dtk_errs_to_stderr()
 *     1/13/95  seg	added keys, initializers & structs for
 *                        old & new Idrisi doc files.
 *	1/21/95 ktr	extracted from rosetta.h to put into common/inc
 *	2/3/99 ktr	upped headsize to ulong ulHeadsize
 * 5.7	2005-06-28 ktr	adapt to new Dragon libraries
 ****************************************************************
 */

#if !defined ROSEFUNS_H
#define ROSEFUNS_H 1
#if defined __cplusplus
extern "C" {
#endif

	/* major image file statistics - init. struct while
	 * reading header */
typedef struct img_info
	{
	uint width;		/* #pix per line per band of (input) file */
	uint height;		/* #lines per band of (input) file */
	uint ulHeadsize;	/* size of (input) header or offset in bytes */
	uint nbands;		/* # bands in (input) file */
	uint InputDataType;	/* single char, such as 'B' or 'S' */
	uint OutputDataType;	/* 0 if not spec'd */
	char InputFileType[10];	 /* Actually use only three chars - see below */
	char OutputFileType[10]; /* Actually use only three chars  */
	uint CurrentBand;	/* 0 if single-band file; else 1-n or RGB */
	char infile[PATH_MAX];
	char outfile[PATH_MAX];	/* '\0' if not spec'd */
	} IMG_INFO ;

#define IMG_INFO_FIELDS \
	"NCOLS","NROWS","HEADER_SIZE","NBANDS",\
	"IN_DATA_TYPE","OUT_DATA_TYPE","IN_FILE_TYPE","OUT_FILE_TYPE",\
	"BANDNO","IN_FILE","OUT_FILE"

#define IMG_INFO_SIZES \
	sizeof(uint),sizeof(uint),sizeof(ulong),sizeof(uint),\
	sizeof(uint),sizeof(uint),10,10,\
	sizeof(uint),PATH_MAX,PATH_MAX

/* prototypes of functions in rosefuns.c */
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
       */
int ReadKeyedFile(const char* infile,
                  const char* keyword[],const size_t valsize[],
                  const size_t count, const char* delims,
                  const ushort maxfsize,void* destination);

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
int WriteKeyedFile(const char* outfile,
                  const char* keyword[],const size_t valsize[],
                  const size_t count, const char* delims,
                  const void* source);

	  /* trim trailing blanks and newlines from string */
void trimstring(char * instring);

void dtk_errs_to_stderr();

	/* Calculate the statistics for a Dragon image which has already been written.
	 * Then write the statistics to the file.
	 * Error messages are sent to stderr.
	 * @param  pDestImage	the image which needs to be calculated
	 * @param  linesize	the number of BYTES (not elements) per data line
	 * @param  iDataType	'S' if 16-bit data else 'B'
	 * @return		0 if successful else standard Dragon error numbers
	 */
int CalcStats(const IMAGE * pDestImage, const size_t  linesize, int iDataType);

#if defined __cplusplus
    }
#endif
#endif

