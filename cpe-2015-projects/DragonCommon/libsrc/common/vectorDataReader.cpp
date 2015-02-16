extern "C"
{
#include "drelease.h"
char VECTORDATAREADER_CPP_ID[]=
  "\0@(#) " __FILE__ "  $Revision: 1.5 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
}
/*
 *	filename vectorDataReader.cpp
 *		$Revision: 1.5 $ $Date: 2014/12/05 14:24:30 $	
 *
 *      ~~ Copyright 2006-2014 Kurt Rudahl and Sally Goldin
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
 ***************************************************
 *  $Id: vectorDataReader.cpp,v 1.5 2014/12/05 14:24:30 rudahl Exp $
 *  $Log: vectorDataReader.cpp,v $
 *  Revision 1.5  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.4  2008/04/26 10:55:55  rudahl
 *  improved notices
 *
 *  Revision 1.3  2007/05/27 06:06:03  rudahl
 *  removed unneeded headers
 *
 *  Revision 1.2  2006/08/14 07:20:17  goldin
 *  Debugging new vector framework
 *
 *  Revision 1.1  2006/08/04 11:06:41  goldin
 *  Create class hierarchy similar to that for image classes
 *
 *
 *
 *******************************************************************
 *   This is the VectorDataReader base class. This is an
 *   abstract base class for concrete classes that handling
 *   the reading of reading vector files of various format.
 *   This class is roughly analagous to the the ImageReader class.
 *
 *   Created by Sally Goldin, 4 August 2006
 *	
 ****************************************************************
 */
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <sys/stat.h>
#include <unistd.h>
#include <stddef.h>	/* for offsetof() */

#include "dtypes.h"
#include "dlimits.h"
#include "dragon-errors.h"
//#include "files.h"

#include "ob.h"
#include "dhead.h"
#include "dragonHd.h"
#include "imageHdr.h"
#include "img.h"
#include "imageReader.h"
#include "imageWriter.h"
#include "vectorData.h"
#include "vectorDataReader.h"
//#include "i18n.h"

#include "dragonOb.h"
#include "logger.h"
//#include "dp.h"

Class VectorDataReader::s_class_Base("VectorDataReader","Class for reading vector files");

VectorDataReader::VectorDataReader(int iDebug,int iTrace)
    {
    m_pVectorData = NULL;         
    m_pClass = &s_class_Base; m_pClass->setSubClass(OB::getObjectClass());
    }

void VectorDataReader_END() { puts(FIL_ID); }
