/****************************************************************
 *
 *		>> OB.H <<	
 *
 *          by K.T. Rudahl
 *          $Revision: 1.12 $ $Date: 2014/12/05 09:58:46 $
 *
 *          ~~ Copyright 1991-2014 Kurt Rudahl and Sally Goldin
 *
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
 *  $Id: ob.h,v 1.12 2014/12/05 09:58:46 rudahl Exp $
 *  $Log: ob.h,v $
 *  Revision 1.12  2014/12/05 09:58:46  rudahl
 *  no differences between DragonProf and OpenDragon
 *
 *  Revision 1.11  2005/03/19 06:25:44  rudahl
 *  CVS moved from windu; maybe some history lost
 *
 *  Revision 1.11  2005/03/13 02:42:58  rudahl
 *  fix probs found working with enhance
 *
 *  Revision 1.10  2005/02/10 04:59:39  rudahl
 *  cleaned up tracing and error reporting
 *  cleaned up image file writing
 *
 *  Revision 1.9  2005/01/26 01:52:01  rudahl
 *  virtual descructor
 *
 *  Revision 1.8  2005/01/04 15:39:36  rudahl
 *  added linked list; changed fn names
 *
 *  Revision 1.7  2004/12/31 11:02:21  rudahl
 *  cleanup
 *
 *  Revision 1.6  2004/12/31 09:19:31  rudahl
 *  adapt and simplify from Dragon 5.4.4
 *
 *  Revision 1.5  2004/12/28 12:18:50  rudahl
 *  added a virtual descrictor
 *
 *  Revision 1.4  2002/04/17 23:06:40  rudahl
 *  preparing for 32-bits
 * 
 * Revision 1.1  92/03/08  12:26:46  tower
 * Initial revision
 ***************************************************
 *
 * define base classes for a class library
 *   class Class, class OB
 *
 * OB forms the base class for all other classes. It defines
 *	an isA test, some dump functions, and a way to get the
 *	print name of the class. 
 *
 *	For each derived class it is necessary to create a Class
 *	   such as Class xx_class("xx");
 *	Then the derived class must implement the  declared 
 *	virtual function:
 *	   const Class * iSa() const { return xx_class; }
 *	 and may override others:
 *	   const char * about()
 *	   const char * dump()
 *
 * Each class derived from OB includes a singe static member of
 *	class Class, which provides some constant info about the
 *	derived class.
 ****************************************************************
 *
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *		(add more names here)
 *
 *	 history
 *	5/25/92 ktr	minor fixes for Zortech 3.0
 *			added error message strings
 *	8/13/92 ktr	added fullfilename() to class File
 * 4.1	1/7/95	ktr	fixed error #'s to use DTKE_OB_BASE;
 *	12/12/95 ktr	adapt to Watcom 10.0 & MSC v 8
 *      6/2/00 ktr      minor fix for gcc
 * 5.4	12/21/2004 ktr	created virtual destructor for class OB
 *			to satisfy linux - is it OK? ~~
 * 5.5	2004/12/31 ktr	imported from Dragon Academic Edition 5.4.4
 *			removed FileHeader and File to fileclass.h
 *	2005-1-21 ktr	added virtual descructor to make GCC happy
 *	2005-02-08 ktr	centralized error numbers, tracing, debugging
 *			control in this class
 ***************************************************/

#ifndef OB_H
#define OB_H

#if defined __cplusplus

class Class;

class OB
	{
    public:
	OB();
		// return the Class
	const Class * isA() const;

		// return the parent Class
	const Class * isSubclassOf() const;

		// return TRUE if this is a 'testclass'
	BOOL isA(Class * testclass) const;

		// return TRUE if this is a 'name'
	BOOL isA(const char * name) const;

		// test if current class is a descendent of 'testclass'
		// @return: >0 => yes, and value is degree of separation
		//	    ==0 => current IS testclass
		//	    <0 => no relationship
	int isDescendentOf(Class * testclass) const;

		// return a description of the class member
	virtual const char * about(const char * czArg=NULL) const ;

		// return a formatted dump of the class member
	virtual const char * dump(int detail=6, 
				  const char * czArg=NULL) const = 0;

		// return the name of the class to which the member belongs
	const char * nameOf() const;

		// return the class_Object class
	static const Class * getObjectClass() { return &s_class_Object;};

	/* return an English text string describing the current val of m_iErrno
	 * This is based on dragon-error.c for non I18N use, 
	 * but can be overridden */
	const char * getErrorMessage() { return dragonErrorMessage(m_iErrno);};

	int getErrorNo() const { return m_iErrno; } ;

	virtual ~OB() {};

	/* Following control debug output (printf, etc) and tracing (logTrace)
	 * usually used as boolean (0 => no output) but can control
	 * detail with higher numbers implying more detail.
	 * the static xx_All variables enable the action in ALL classes, 
	 * for ALL instances created after the xx_All was set
	 */
	int m_iDebug;
	int m_iTrace;
	static int s_iDebugAll;
	static int s_iTraceAll;
    protected:
	Class * m_pClass;
	int m_iErrno;
//	static char * getOutbuf() { return s_outbuf; } ;
	static char s_outbuf[2048]; // for composing dump and error messages
	static Class s_class_Object;
	} ;

#define OB_NAMESZ	30	/* size of class name */

class Class : public OB
	{ 
    public:
		//  create an instance of Class
		//	'name' is string naming class
		//	'descr' is descriptor
	Class(const char * name,const char * descr = NULL);

		// return the name of the instance 
	const char * nameOf() const { return m_name; } ;

		// return a (possibly multi-line) description of the class
	const char * obdesc() const { return m_obdescr; } ;

		// install  the description of the class
		//	return 0 if OK, -1 if error
	const int obdesc_put(const char * text);

		// delete the description
	const void obdesc_zap();

		// dump the Class info
	const char * dump(int detail=6, const char * czArg=NULL) const;

		// Classes form a linked list. 
		// Get a pointer to the previous one.
	const Class * getPrior() const { return m_pPriorClass; } ;

		// Get a pointer to the start of the list (the latest one)
	static const Class * getTop() { return s_pTopClass; } ;

		// accessors to get and set what Class this is
		// a subclass of. Only OB is NULL
	void setSubClass(const Class * pclass);
	const Class * getSubClass() const { return m_pSubClass; } ;

	~Class();
    private:
	char m_name[OB_NAMESZ];
	char * m_obdescr;
	const Class * m_pSubClass;
	const Class* m_pPriorClass;	// link for list of all Class objects 
	static Class* s_pTopClass;	// list of all Class objects 
	} ;

extern "C" {
#else
typedef void * OB;
#endif

/* set either or both of the ob.h debug and trace level
 * variables. Level of -1 => don't change */
void setDebugging(OB * pOb, int iDebugLevel, int iTraceLevel);

#if defined __cplusplus
           }
#endif

#endif // OB_H

