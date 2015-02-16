/*
 *	filename GRSTOP.H
 *
 *      fns exported by the grstop-xxx and grsproc1 'dll's
 *
 *        ~~ Copyright 1999-2014 Kurt Rudahl and Sally Goldin
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
 *	$Id: grstop.h,v 1.36 2014/12/05 09:58:46 rudahl Exp $
 *	$Log: grstop.h,v $
 *	Revision 1.36  2014/12/05 09:58:46  rudahl
 *	no differences between DragonProf and OpenDragon
 *
 *	Revision 1.35  2010/12/13 12:51:06  goldin
 *	Add necessary infrastructure for new Export op
 *
 *	Revision 1.34  2006/12/29 11:32:41  goldin
 *	Add symbol for G COM
 *
 *	Revision 1.33  2006/12/17 11:38:57  goldin
 *	Bug fixes
 *	
 *	Revision 1.32  2006/12/10 12:08:50  goldin
 *	Integrating new geography operations
 *	
 *	Revision 1.31  2006/11/19 06:02:31  goldin
 *	Integrate Import into DragonServer
 *	
 *	Revision 1.30  2006/11/13 14:11:10  goldin
 *	integrating PCA into Dragon
 *	
 *	Revision 1.29  2005/10/20 09:47:19  goldin
 *	Integrate clserror into Dragon
 *	
 *	Revision 1.28  2005/09/25 12:07:25  rudahl
 *	added CursorI
 *	
 *	Revision 1.27  2005/09/16 11:50:06  goldin
 *	Working on moving CUR to 32 bit code
 *	
 *	Revision 1.26  2005/08/19 05:15:40  rudahl
 *	adding annotation
 *	
 *	Revision 1.25  2005/04/01 08:51:55  goldin
 *	Changes to support adding new 32-bit display fns
 *	
 *	Revision 1.24  2005/04/01 03:27:52  rudahl
 *	working on grstop Server modules
 *	
 *	Revision 1.23  2002/06/10 19:28:58  goldin
 *	Defns/changes for moving GCP to 32 bit
 *	
 *	Revision 1.22  2002/03/29 02:13:53  goldin
 *	Implement new C FEA operation
 *	
 *	Revision 1.21  2002/03/26 17:33:57  rudahl
 *	added support for Rhett's pattern detection
 *	
 *	Revision 1.20  2002/01/21 19:52:57  goldin
 *	Implement HEA in 32 bits
 *	
 *	Revision 1.19  2002/01/15 12:23:27  goldin
 *	Create top level 32-bit scatterplot function
 *	
 *	Revision 1.18  2002/01/07 17:37:35  goldin
 *	Add new U Hist prototypes
 *	
 *	Revision 1.17  2001/11/06 18:06:19  goldin
 *	Implement MEA in 32 bit world
 *	
 *	Revision 1.16  2001/10/30 12:21:34  goldin
 *	Add new prototypes for C/LIS and C/EDI/HIS
 *	
 *	Revision 1.15  2001/10/25 15:12:45  goldin
 *	Continue implementation of C/EDI operations
 *	
 *	Revision 1.14  2001/09/14 18:24:45  goldin
 *	Added infrastructure for new REG operation
 *	
 *	Revision 1.13  2001/08/23 18:02:34  goldin
 *	Add VEC prototypes and data members
 *	
 *	Revision 1.12  2001/08/21 12:18:12  rudahl
 *	added conditional for GCC
 *	
 *	Revision 1.11  2001/08/15 14:09:49  goldin
 *	initial implementation of COO
 *	
 *	Revision 1.10  2001/08/01 15:05:51  goldin
 *	Add default string to ARGDESCRIPTOR struct
 *	
 *	Revision 1.9  2001/08/01 13:50:22  goldin
 *	Implement slicing and agc in 32 bit world
 *	
 *	Revision 1.8  2001/07/26 11:44:57  goldin
 *	Begin implementation of clustering in 32 bit
 *	
 *	Revision 1.7  2001/07/25 10:25:17  rudahl
 *	improvements for File ops
 *	
 *	Revision 1.6  2001/07/17 17:19:34  goldin
 *	Add protos for other enhance operations
 *	
 *	Revision 1.5  2001/07/13 17:40:55  goldin
 *	Add FIL and REL to the 32 bit version
 *	
 *	Revision 1.4  2001/07/12 19:01:28  goldin
 *	Begin implementation of G CAL in 32 bit
 *	
 *	Revision 1.3  2001/07/09 14:21:39  goldin
 *	Initial implementation of Recode, still being debugged
 *	
 *	Revision 1.2  2001/07/05 18:41:49  goldin
 *	changes to implement AUT
 *	
 *	Revision 1.1  2001/07/02 20:09:14  rudahl
 *	moved DLL export fns from grsproc1.h into new grstop.h
 *	
 ****************************************************************
 *
 *	Exported Prototypes for GRSTOP-xxx and GRSPROC1 DLL
 *
 *   4/21/99  seg  Created
 * 5.5	2005-3-31 ktr	imported from Dragon v 5.4.4
 * 5.7	2005-Aug-19 ktr	added annotation
 * -------------------------------------------------------------*/

#ifndef GRSTOP_H
#define GRSTOP_H

/* define macros so we get the right entry points. */
/* The DLL itself will be compiled with DLL_API defined */
/* Consumers of its services will not              */

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __GCC__
#define _stdcall
#endif

#ifdef _NO_EXPORT // if not using a DLL
#define EXPORT_FN
#else
#ifdef DLL_API
#define EXPORT_FN __declspec(dllexport) 
#else
#define EXPORT_FN __declspec(dllimport) 
#endif
#endif
EXPORT_FN long _stdcall GRS_ListSigsI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ShowSigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_SigHistogramI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ModifySigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CopySigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CombineSigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_RenameSigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_SaveSigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_DeleteSigI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CalcTraSigsI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CalcAppSigsI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CalcAutSigsI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_RecodeI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ClusterI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_AgroclimaticI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_SliceI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ClsErrorI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_FeatureI(const char * pczArgsFile);

EXPORT_FN long _stdcall GRS_BoxClassifyI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_MdmClassifyI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_MaxClassifyI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_MaxClassify(const int iNbands,
                                       const char * pczIFile1,
                                       const char * pczIFile2,
                                       const char * pczIFile3,
                                       const char * pczIFile4,
                                       const char * pczSigFile,
                                       const char * pczOutFile,
                                       const int iOutFileType,
                                       const double dThresh);
	/* These are top-level functions that do a max likelihood
         * classification, writing the output to a DRAGON
         * image file.
         * 
         * 'nNbands' is the number of input bands (up to 4)
         * 'pczIFile1' through 'pczIFile4' are the input image files
         *  (unused arguments should be NULL)
         * 'pczSigFile' is the signature file (DRAGON format)
         * 'pczOutFile' is the output file to be created. 
         * 'iOutFileType indicates what type of file to write. See below.
         * 'dThresh' is the threshold, which is interpreted in terms
         *   of number of SDs from the per class means.
         * Does not currently support masking.
	 *
	 * GRS_MaxClassifyI takes its args from the named argument file.
	 *
         * Returns 0 for success, negatives for errors. 
         */
EXPORT_FN long _stdcall GRS_Disp1baI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_Disp3baI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_DispGraI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_DispOveI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_DispAddI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_DispEraI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_DispLegI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageSumI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageDifI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageSymI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageRatI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageVegI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageGviI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImageMasI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_FilterI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_RelaxI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_PcaI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_WaveletI(const char * pczArgsFile);
 
EXPORT_FN long _stdcall GRS_SaveI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_SubsetI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ImportI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ExportI(const char * pczArgsFile);
 
EXPORT_FN long _stdcall GRS_UtilListI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_UtilHistI(const char * pczArgsFile);
    EXPORT_FN long _stdcall GRS_CursorI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_ScatterI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_HeaderI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_Cur(const char * pczArgsFile);

EXPORT_FN long _stdcall GRS_CalcCoefI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_RegisterImageI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CookieI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_VectorI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_MeasureI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_GroundControlI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_SlopeI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_AspectI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_BufferI(const char * pczArgsFile);
EXPORT_FN long _stdcall GRS_CombineI(const char * pczArgsFile);


#define GRS_DRAGIMG_FILE  0
#define GRS_TIFF_FILE     1

typedef struct
    {
    const char czOpName[10];         // e.g. -FO; matches 'cmdargs' element
    BOOL bRequired;                  // required to be non-zero or non-empty
    const char czDefault[20];        // default to use if not supplied 
                                     // only relevant when bRequired=false
    char czOpType[6];                // validation str from 'cmdargs'
    const char czMessagesKey[20];    // key to group of I18N'd msgs
                                     // for e.g. menu, help, error, etc
    const char czBriefMessage[100];  // default 'reminder' msg in English
    ushort uCmdDescriptorIndex;      // index into CmdDescriptor table
    } ARGDESCRIPTOR_T;

EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_MaxClassifyParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_MdmClassifyParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_BoxClassifyParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ListSigsParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ShowSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_SigHistogramParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ModifySigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CopySigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CombineSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_RenameSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_SaveSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_DeleteSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CalcTraSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CalcAppSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CalcAutSigParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_RecodeParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ClusterParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_AgroclimaticParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_SliceParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ClsErrorParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_FeatureParamList();


EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_FilterParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_RelaxParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_PcaParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_WaveletParamList();

EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_SaveParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_SubsetParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ImportParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ExportParamList();

EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_UtilListParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_UtilHistParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_ScatterParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_HeaderParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CursorParamList();

EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CalcCoefParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_RegisterParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CookieParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_VectorParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_MeasureParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_GCPParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_SlopeParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_AspectParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_BufferParamList();
EXPORT_FN const ARGDESCRIPTOR_T * _stdcall getGRS_CombineParamList();

#ifdef __cplusplus
    }
#endif

#endif
