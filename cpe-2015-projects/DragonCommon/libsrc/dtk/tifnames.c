static char sccsid[] = "(@)#TIFNAMES.C $Date: 2014/12/17 07:20:39 $ $Revision: 1.6 $";
/****************************************************************************
 *
 * 	file TIFNAMES.C
 *	
 *	definition of TAG messeges (names) for TIFF
 *
 *	~~ Copyright kurt t. rudahl 1988-2014
 *	~~ EndC
 *          $Revision: 1.6 $ $Date: 2014/12/17 07:20:39 $
 *******************************************************************
 * $Id: tifnames.c,v 1.6 2014/12/17 07:20:39 rudahl Exp $
 * $Log: tifnames.c,v $
 * Revision 1.6  2014/12/17 07:20:39  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.5  2004/12/23 12:14:38  rudahl
 * lint-ish fix
 *
 * Revision 1.4  2004/11/30 09:45:11  rudahl
 * adapt for mingw
 *
 * Revision 1.3  2002/06/18 19:06:26  rudahl
 * fixup for 32-bit
 *
 * Revision 1.2  2002/06/10 12:33:53  rudahl
 * updated TIFF-related fns to MSC4.1
 *
 * Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 * first checkin of only SOME common dirs
 *
 * Revision 4.0.1.1  1994/01/04  19:45:46  tower
 * no significant changes
 * 
 * Revision 4.0  1994/01/04  19:45:46  tower
 * distrib. concurrent with DRAGON rel 4.0 - minor change
 * 
 * Revision 1.4  92/06/02  19:00:22  tower
 * Changes to TIFF library for Zortech 3.0, for released DRAGSCAN & TIF2DRAG
 * and for first released use of imagfile
 * 
 * Revision 1.3  92/03/08  12:18:52  tower
 * shortened some names, and updated for use with DECORATE & IMAGEFILE
 * TIFF version 5.0
 * 
 * Revision 1.2  91/04/09  21:59:04  tower
 * improved wordings
 * 
 * Revision 1.1  91/03/06  17:48:20  tower
 * Initial revision
 * 
 *
 *******************************************************************
 *	created 2/3/91 for Zortech C
 *	TIFF revision 5.0, TIFF X classes
 *	The sequence of character strings must match the tag sequence
 *	of TAGINDEX in TIFF.HPP
 *
 *  12/3/91 ktr	changed entries for x&y position, resolution unit
 *		added DECORATE & IMAGEFILE references
 * 1.4	5/26/92	ktr	updated to Zortech 3.0; changed Photometric name
 * 5.4	12/22/2004 ktr	added stdlib, stdio for linux uint defn
 */

//#include "host.h"
#include <stdio.h>
#include <stdlib.h>

#include "dtypes.h"
#include "tiff.hpp"

const char * tagnames[] = 
    {
    "NewSubfileType",
    "SubFile_Type",
    "ImageWidth",
    "ImageLength",
    "BitsPerSample",
    "Compression",
    "Photometric",
    "Threshholding",
    "CellWidth",
    "CellLength",
    "ImageFillOrder",
    "DocumentName",
    "ImageDescription",
    "Make",
    "Model",
    "StripOffsets",
    "ImageOrientation",
    "SamplesPerPixel",
    "RowsPerStrip",
    "StripByteCounts",
    "MinSampleValue",
    "MaxSampleValue",
    "XResolution",
    "YResolution",
    "PlanarConfiguration",
    "PageName",
    "XPosition",
    "YPosition",
    "FreeOffsets",
    "FreeByteCounts",
    "GrayResponseUnit",
    "GrayResponseCurve",
    "Group3Options",
    "Group4Options",
    "ResolutionUnit",
    "PageNumber",
    "ColorResponseCurves",
    "Software",
    "DataTime",
    "Artist",
    "HostComputer",
    "Predictor",
    "WhitePoint",
    "PrimaryChromaticities",
    "ColorMap"
    } ;

const char * tagdescribe[] = 
    {
    "Bit 0=>reduced res. 1=>several pages 2=>mask",
    "1=>full res. 2=>reduced res. 3=>several pages",
    "Width of image in pixels",
    "Height of image in pixels",
    "Bits of data. Three values: Red, Green, Blue",
    "1=>No compression 2=>1D Huffman 3=>FAX3 4=>FAX4 5=>LZW 32773=>PackBits",
    "0=>0=White 1=>0=Black 2=>RGB 3=>Mapped 4=>Mask",
    "1=>Line art 2=>Dithered 3=>Diffused. Obsolete",
    "Width of dither matrix. Obsolete",
    "Height of dither matrix. Obsolete",
    "1=>MSB first 2=>LSB first. Obsolete",
    "Document Storage. Name of scanned document",
    "Information tag. Caption.",
    "Information tag. Scanner or sensor brand name.",
    "Information tag.",
    "Header size",
    "Rotation and mirroring. Obsolete",
    "1=bilevel, gray, or palette; 3=RGB",
    "",
    "",
    "Used for statistical purposes only.",
    "Used for statistical purposes only.",
    "Resolution in X direction.",
    "Resolution in Y direction.",
    "1=>stored contiguously (e.g. RGBRGB...) 2=>separate planes",
    "Document storage. Name of scanned page",
    "X location of upper-left-corner of image area",
    "Y location of upper-left-corner of image area",
    "Obsolete",
    "Obsolete",
    "Divisor of GrayResponseCurve. Number is power of 10.",
    "2**BitsPerSample entries, gray only.",
    "Facsimile. Bit 0=>2D coding 1=>uncompressed 2=>byte fill bits added",
    "Facsimile. Bit 1=>uncompressed.",
    "1=>device-dependent 2=>dots/inch 3=>dots/cm.",
    "Document storage. Page number and total number of pages",
    "2**BitsPerSample entries in Red Green Blue order",
    "Information tag. Software package used",
    "Information tag. YYYY:MM:DD HH:MM:SS",
    "Information tag. Who created image",
    "Information tag.",
    "Component for use with LZW compression.",
    "Colorometric info - appendix H",
    "Colorometric info - appendix H",
    "Red, then Green, then Blue. Each has 2**BitsPerSample entries"
    } ;

	/* bits identify which TIFF spec applies:
		bit 0 => TIFF-B	req'd	1 => TIFF-G req'd
		    2 => TIFF-P	req'd	3 => TIFF-R req'd
		    4 => obsolete	5 => info only
		    6 => fax		7 => document
		    8 => TIFF-X req'd   9 => TIFF-X recommended	
		    10 => PRINTIFF uses
		    11 => TIFALYZE report
		    12 => DECORATE & IMAGEFILE use
	*/

/*UINT16 tagspecs[] = { TAGSSPEC } ;*/
#ifdef NOMORE
    {
    0xA0F,	/* "newsubfiletype */
    0x61F,	/* "Subfile type */
    0x1F0F,	/* "ImageWidth" */
    0x1F0F,	/* "ImageLength", */
    0x1C0F,	/* "BitsPerSample",*/
    0x1C4F,	/* "Compression",*/
    0x1C0F,	/* "PhotometricInterpretation",*/
    0x10 ,	/* "Threshholding",*/
    0x10 ,	/* "CellWidth", */
    0x10 ,	/* "CellLength", */
    0x10 , 	/* "FillOrder", */
    0xA0 ,	/* "DocumentName",*/
    0x1820 , 	/* "ImageDescription", */
    0x20 , 	/* "Make", */
    0x20 , 	/* "Model", */
    0x1F0F,	/* "StripOffsets",*/
    0x1010 ,	/* "Orientation",*/
    0x1C0F,	/* "SamplesPerPixel",*/
    0x1F0F,	/* "RowsPerStrip", */
    0x1F0F,	/* "StripByteCounts", */
    0x820 , 	/* "MinSampleValue", */
    0x820 ,	/* "MaxSampleValue", */
    0x30F,	/* "XResolution */
    0x30F,	/* "YResolution",*/
    0x1C08,	/* "PlanarConfiguration",*/
    0xA0 ,	/* "PageName",*/
    0x1080 ,	/* "XPosition", */
    0x1080 ,	/* "YPosition", */
    0x10 ,	/* "FreeOffsets", */
    0x10 ,	/* "FreeByteCounts", */
    0 ,		/* "GrayResponseUnit",*/
    0 ,		/* "GrayResponseCurve",*/
    0x40 ,	/* "Group3Options", */
    0x40 ,	/* "Group4Options", */
    0x130F,	/* "ResolutionUnit",*/
    0xA0 ,	/* "PageNumber",*/
    0x1C00 ,	/* "ColorResponseCurves", */
    0x820 , 	/* "Software",*/
    0x820 , 	/* "DataTime",*/
    0x20 ,	/* "Artist", */
    0x20 ,	/* "HostComputer",*/
    0 , 	/* "Predictor", */
    0 ,		/* "WhitePoint",*/
    0 ,		/* "PrimaryChromaticities",*/
    0x1C04	/* "ColorMap"*/
    } ;
#endif


