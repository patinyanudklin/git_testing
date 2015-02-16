/*
 * Copyright (c) 1999-2000 Image Power, Inc. and the University of
 *   British Columbia.
 * Copyright (c) 2001-2002 Michael David Adams.
 * All rights reserved.
 */

/* __START_OF_JASPER_LICENSE__
 * 
 * JasPer License Version 2.0
 * 
 * Copyright (c) 2001-2006 Michael David Adams
 * Copyright (c) 1999-2000 Image Power, Inc.
 * Copyright (c) 1999-2000 The University of British Columbia
 * 
 * All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person (the
 * "User") obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of the Software, and to permit
 * persons to whom the Software is furnished to do so, subject to the
 * following conditions:
 * 
 * 1.  The above copyright notices and this permission notice (which
 * includes the disclaimer below) shall be included in all copies or
 * substantial portions of the Software.
 * 
 * 2.  The name of a copyright holder shall not be used to endorse or
 * promote products derived from the Software without specific prior
 * written permission.
 * 
 * THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL PART OF THIS
 * LICENSE.  NO USE OF THE SOFTWARE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.  THE SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS
 * "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
 * BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO
 * EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, OR ANY SPECIAL
 * INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER RESULTING
 * FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
 * WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  NO ASSURANCES ARE
 * PROVIDED BY THE COPYRIGHT HOLDERS THAT THE SOFTWARE DOES NOT INFRINGE
 * THE PATENT OR OTHER INTELLECTUAL PROPERTY RIGHTS OF ANY OTHER ENTITY.
 * EACH COPYRIGHT HOLDER DISCLAIMS ANY LIABILITY TO THE USER FOR CLAIMS
 * BROUGHT BY ANY OTHER ENTITY BASED ON INFRINGEMENT OF INTELLECTUAL
 * PROPERTY RIGHTS OR OTHERWISE.  AS A CONDITION TO EXERCISING THE RIGHTS
 * GRANTED HEREUNDER, EACH USER HEREBY ASSUMES SOLE RESPONSIBILITY TO SECURE
 * ANY OTHER INTELLECTUAL PROPERTY RIGHTS NEEDED, IF ANY.  THE SOFTWARE
 * IS NOT FAULT-TOLERANT AND IS NOT INTENDED FOR USE IN MISSION-CRITICAL
 * SYSTEMS, SUCH AS THOSE USED IN THE OPERATION OF NUCLEAR FACILITIES,
 * AIRCRAFT NAVIGATION OR COMMUNICATION SYSTEMS, AIR TRAFFIC CONTROL
 * SYSTEMS, DIRECT LIFE SUPPORT MACHINES, OR WEAPONS SYSTEMS, IN WHICH
 * THE FAILURE OF THE SOFTWARE OR SYSTEM COULD LEAD DIRECTLY TO DEATH,
 * PERSONAL INJURY, OR SEVERE PHYSICAL OR ENVIRONMENTAL DAMAGE ("HIGH
 * RISK ACTIVITIES").  THE COPYRIGHT HOLDERS SPECIFICALLY DISCLAIM ANY
 * EXPRESS OR IMPLIED WARRANTY OF FITNESS FOR HIGH RISK ACTIVITIES.
 * 
 * __END_OF_JASPER_LICENSE__
 */

/*
 * Portable Pixmap/Graymap Format Support
 *
 * $Id: pnm_cod.h,v 1.3 2014/02/09 04:58:30 rudahl Exp $
 */

#ifndef PNM_COD_H
#define PNM_COD_H

/******************************************************************************\
* Includes.
\******************************************************************************/

#include "jasper/jas_types.h"

/******************************************************************************\
* Constants.
\******************************************************************************/

/* Magic numbers. */
#define PNM_MAGIC_TXTPBM	0x5031 /* Text Portable BitMap (P1) */
#define PNM_MAGIC_TXTPGM	0x5032 /* Text Portable GrayMap (P2) */
#define PNM_MAGIC_TXTPPM	0x5033 /* Text Portable PixMap (P3) */
#define PNM_MAGIC_BINPBM	0x5034 /* Binary Portable BitMap (P4) */
#define PNM_MAGIC_BINPGM	0x5035 /* Binary Portable GrayMap (P5) */
#define PNM_MAGIC_BINPPM	0x5036 /* Binary Portable PixMap (P6) */
#define	PNM_MAGIC_PAM		0x5037 /* PAM (P7) */

/* Type of image data. */
#define PNM_TYPE_PPM	0 /* PixMap */
#define PNM_TYPE_PGM	1 /* GrayMap */
#define PNM_TYPE_PBM	2 /* BitMap */

/* Format of image data. */
#define PNM_FMT_TXT	0 /* Text */
#define PNM_FMT_BIN	1 /* Binary */

#define	PNM_MAXLINELEN	79

#define	PNM_TUPLETYPE_UNKNOWN	0
#define	PNM_TUPLETYPE_MONO	1
#define	PNM_TUPLETYPE_GRAY	2
#define	PNM_TUPLETYPE_GRAYA	3
#define	PNM_TUPLETYPE_RGB	4
#define	PNM_TUPLETYPE_RGBA	5

/******************************************************************************\
* Types.
\******************************************************************************/

/* File header. */

typedef struct {

	int magic;
	/* The magic number. */

	int width;
	/* The image width. */

	int height;
	/* The image height. */

	int numcmpts;

	int maxval;
	/* The maximum allowable sample value. */

#if 0
	int tupletype;
#endif

	bool sgnd;
	/* The sample data is signed. */

} pnm_hdr_t;

/******************************************************************************\
* Functions.
\******************************************************************************/

int pnm_type(uint_fast16_t magic);
/* Determine type (i.e., PGM or PPM) from magic number. */

int pnm_fmt(uint_fast16_t magic);
/* Determine format (i.e., text or binary) from magic number. */

int pnm_maxvaltodepth(uint_fast32_t maxval);
/* Determine depth (i.e., precision) from maximum value. */

#define	PNM_ONES(n) \
	(((n) < 32) ? ((1UL << (n)) - 1) : 0xffffffffUL)
#endif
