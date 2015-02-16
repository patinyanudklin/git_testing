#include "drelease.h"
 ID_ OB_ID[]
    = "\0@(#) " __FILE__ " $Revision: 1.11 $$Date: 2014/12/05 14:24:30 $";
D_REL_IDSTR;
/****************************************************************
 *
 *		>> OB.CPP <<	
 *
 *          by K.T. Rudahl
 *          $Revision: 1.11 $ $Date: 2014/12/05 14:24:30 $
 *
 *          ~~ Copyright 1991-2014 Kurt Rudahl and Sally Goldin
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
 ***************************************************************
 *  $Id: ob.cpp,v 1.11 2014/12/05 14:24:30 rudahl Exp $
 *  $Log: ob.cpp,v $
 *  Revision 1.11  2014/12/05 14:24:30  rudahl
 *  reconciled DragonProfessional with OpenDragon
 *
 *  Revision 1.10  2005/03/19 06:31:51  rudahl
 *  CVS moved from windu; maybe some history lost
 *
 *  Revision 1.10  2005/03/13 02:40:59  rudahl
 *  fix probs found working with enhance
 *
 *  Revision 1.9  2005/03/06 00:17:30  rudahl
 *  lint-ish
 *
 *  Revision 1.8  2005/02/10 03:51:27  rudahl
 *  cleaned up tracing and error handling
 *  cleaned up image file writing
 *
 *  Revision 1.7  2005/01/04 16:15:37  rudahl
 *  converting to 5.5
 *
 *  Revision 1.6  2004/12/31 09:19:09  rudahl
 *  adapt and simplify from Dragon 5.4.4
 *
 *  Revision 1.5  2002/04/17 23:09:45  rudahl
 *  fixups for 32-bit, long filenames
 *
 *  Revision 1.1.1.1  1999/03/11 00:35:19  rudahl
 *  first checkin of only SOME common dirs
 *
 ***************************************************************
 *
 * define base classes for a class library
 *   class Class, class OB, class File
 * 
 ***************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	 history
 *	12/20/91 ktr	added 'confidence' return to fileOK()
 *  	3/92		added access() to class File, release() to FileHeader
 * 1.3	5/26/92	ktr	updated to Zortech 3.0
 *			rewrite errorstr to return informative msg
 *	8/14/92	ktr	changed zortech.h --> dtypes.h & dlimits.h
 * 4.1	1/7/95	ktr	fixed error #'s to use DTKE_OB_BASE;
 *			replaced most printf with put
 *      6/3/00 ktr      fixes for gcc for suSE 63
 * 5.5	2004/12/31 ktr	imported from Dragon Academic Edition 5.4.4
 *			removed FileHeader and File to fileclass.h
 *	2005-02-08 ktr	centralized error numbers, tracing, debugging
 *			control in this class
 ***************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "dtypes.h"
#include "dlimits.h"  /* for NOTNULL macro */
#include "dragon-errors.h"
#include "ob.h"

Class OB::s_class_Object("Object");
char OB::s_outbuf[2048];
int OB::s_iDebugAll = 0;
int OB::s_iTraceAll = 0;

OB::OB()
    {
    m_pClass = & s_class_Object;
    m_pClass->setSubClass((const Class *)NULL);
    m_iDebug = s_iDebugAll;
    m_iTrace = s_iTraceAll;
    m_iErrno = 0;
    if (m_iDebug > 4)
	printf ("OB ctor at %p class set (%p) to %p\n",this,
		&m_pClass,m_pClass);
    }

const Class * OB::isA() const
    { return m_pClass; }

		// return the parent Class
const Class * OB::isSubclassOf() const
    { return isA()->getSubClass(); }

		// return a description of the class member
const char * OB::about(const char * czArg) const
    { return isA()->nameOf(); }
	
		// return the name of the class to which the member belongs
const char * OB::nameOf() const 
    { return isA()->nameOf(); }

		// return TRUE if this is a 'testclass'
BOOL OB::isA(Class * testclass) const
    {
    BOOL bRetval = (testclass == isA());
    return bRetval;
    }

		// return TRUE if this is a 'name'
BOOL OB::isA(const char * name) const
    {
    BOOL bRetval = (name == isA()->nameOf());
    return bRetval;
    }

		// test if current class is a descendent of 'testclass'
		// @return: >0 => yes, and value is degree of separation
		//	    ==0 => current IS testclass
		//	    -48 => no relationship
int OB::isDescendentOf(Class * testclass) const
    {
    int iRetval = DERR_CLASS_UNRELATED;
    if(testclass == isA()) 
	iRetval = 0;
    else
        {
	int counter = 1;
	const Class * pClass = isSubclassOf();
	while (pClass != NULL)
	    {
	    if (testclass == pClass)
		{
		iRetval = counter;
		break;
		}
	    pClass = pClass->isSubclassOf();
	    counter++;
	    }
	}
    return iRetval;
    }

static Class class_Class("Class");

Class * Class::s_pTopClass = NULL;

	//	'name' is string naming class
	//	'descr' is string describing class
Class::Class(const char * name, const char * descr)
    {
    m_pPriorClass = s_pTopClass;	// link for list of all Class objects 
    s_pTopClass = this;
    memset(m_name,0,OB_NAMESZ);
    strncpy(m_name,name,OB_NAMESZ-1);
    m_obdescr = (descr == NULL) ? (char *) NULL : strdup(descr);
    m_pClass = this;
    m_pSubClass = OB::getObjectClass();
    }

Class::~Class()
    {
    obdesc_zap();
    }

	//	clear obdesc list: zero string[0] & release higher ones
	//	return obdescsz
const void Class::obdesc_zap()
    {
    if (m_obdescr != NULL)
	{
	free(m_obdescr); // created with strdup
	m_obdescr = NULL;
	}
    } 

	//	put text into specified available obdescr element
	//	Return 0 if OK else -48
const int Class::obdesc_put(const char * text)
    {
    if (m_obdescr != NULL)
	free(m_obdescr);
    m_obdescr = strdup(text);
    return (m_obdescr == NULL) ? DERR_MEM_ALLOC : 0;
    }

const char * Class::dump(int detail, const char * czArg) const
    {
    memset(s_outbuf,0,sizeof(s_outbuf));
    sprintf(s_outbuf,
	    "%s %s Class at %p: \tisA=%p \tsubclassof '%s'\n\tabout='%s' "
	    "\tdescription='%s'\n\t%s",
	    NOTNULL(czArg),nameOf(),this,isA(),isSubclassOf()->nameOf(),
	    NOTNULL(about()),obdesc(),FIL_ID);
    return s_outbuf;
    }

void Class::setSubClass(const Class * pclass)
    { m_pSubClass = pclass; } 

/* set either or both of the ob.h debug and trace level
 * variables. Level of -1 => don't change */
void setDebugging(OB * pOb, int iDebugLevel, int iTraceLevel)
    {
    if ((pOb != NULL) && (iDebugLevel >= 0))
	pOb->m_iDebug = iDebugLevel;
    if ((pOb != NULL) && (iTraceLevel >= 0))
	pOb->m_iTrace = iTraceLevel;
    }

#ifdef TEST

Class xx_class("xx","xx description");

class xx : public OB
    {
    public:
	const char * about(const char * czArg = NULL) { return "test about"; } ;
		// return a description of the class member
	const char * dump(int detail=6, const char * czArg=NULL) const { return "test dump"; } ;
		// return a formatted dump of the class member
	xx();
    } ;

xx::xx() 
    { m_pClass = &xx_class; m_pClass->setSubClass(OB::getObjectClass()); 
    //printf ("xx ctor at %p class set (%p) to %p\n",
    //    this,&m_pClass,m_pClass);
    }

Class xy_class("xy");  // no overrides

class xy : public xx
    {
    public:
	xy() { m_pClass = & xy_class; m_pClass->setSubClass(& xx_class); };
	const char * dump(int detail=6, const char * czArg=NULL) const  
	    { return "test dump"; }
//    	Class * isA() const { return & xy_class; } ;
		// return the Class
	//   	Class * isSubclassOf() const { return & class_Object; };
    } ;

extern "C"
int main()
    {
    xx xx0;
    xy xy0;
    printf("main(en)\n");
    printf("%s\n",xy_class.dump(6,"Dump of"));
    printf("Dump of xy0 object: %s\n",xy0.dump(6,"Dump of "));
//    printf("main(3)\n");
    xy_class.obdesc_put("xy updated description line 1");
//    printf("xy: \tname='%s'subclassof='%s'\n\tchar dump='%s'\n\tprint='%s'\n\n",
//	xy0.nameOf(),xy0.isSubclassOf()->nameOf(),xy0.dump(),xy0.about());
    const Class * pClass = Class::getTop();
    while ((pClass != NULL) && (pClass != OB::getObjectClass()))
        {
	printf("%s\n",pClass->dump(6,"Dump of "));
	pClass = pClass->getPrior();
	}
    return 0;
    }
#endif
