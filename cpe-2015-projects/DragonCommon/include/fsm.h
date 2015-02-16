//***************************************************************
//
//          fsm.h - finite-state machine  
//			 K.T. Rudahl
//
//          Copyright 2007-2008 by Kurt Rudahl and Sally Goldin
//***************************************************************
/*
 *   $Id: fsm.h,v 1.3 2008/03/22 06:04:09 rudahl Exp $
 *   $Log: fsm.h,v $
 *   Revision 1.3  2008/03/22 06:04:09  rudahl
 *   update copyright
 *
 *   Revision 1.2  2007/12/08 13:12:47  rudahl
 *   adapt to MFC
 *
 *   Revision 1.1  2007/12/08 06:39:55  rudahl
 *   new generic finite-state machine
 *
 */
//
//***************************************************************
// This class implements a general-purpose finite-state machine
// which is structured following the form in "Executable UML"
//
//****************************************************************/
/**/
/*    Modification History
 * 
 * 5.11	2007-12-08 ktr	created
 */	    
#ifndef FSM_H
#define FSM_H

#if defined __MINGCC__ || defined __GCC__
#define BASE_CLASS OB
#else
#define BASE_CLASS CWnd
#include "stdafx.h"
#endif

// This fn must return < 0 if error
// in which case state transition will not happen
typedef int (BASE_CLASS::* STATE_FN)(int iStateNo);

typedef struct 
    {
    int iNo; // -1 or >= 0
    char * pczName;
    STATE_FN pFn;
    BASE_CLASS * pInstance;
    } FSM_STATE;

typedef struct 
    {
    uint uNo; // >= 0
    char * pczName;
    } FSM_EVENT;

class fsm : public BASE_CLASS
    {
    public: 
	fsm(int iDebug,int iTrace);

	// set up the state machine parameters
	// @param uStateCount	how many states 
	//			they will be numbered 0 .. n-1
	// @param pczStateNames	NULL or 'uStateCount' strings
	//			used only for tracing
	// @param uEventCount	how many (input) events
	//			they will be numbered 0 .. n-1
	// @param pczEventNames	NULL or 'uEventCount' strings
	//			used only for tracing
	// @param piResults	'UstateCount' * 'uEventCount' 
	//			state numbers each of which is the 
	//			result state if currently 
	//			in state [i] and receive event [j]
	//			arranged as a [stateno][eventno] array
	//			values < 0 are errors (transitions 
	//			which should not happen)
	// @param uInitialState	starting state
	// @return		0 if OK else <0 = DRAGON error number
	int init(size_t uStateCount, const char ** pczStateNames,
		 size_t uEventCount, const char ** pczEventNames,
		 int * piResults, uint uInistialState);

	// Register an action to be executed on entry into a state
	// see the example in fsm.cpp TEST for how this is invoked
	// Note that the fn must be to a class which subclasses BASE_CLASS.
	// @param iState	state number on entry to which this 
	//			action will be invoked
	//			if < 0, this registers the (only) 
	//			error callback fn
	// @param fn		pointer to action function
	// @param pInstance	if fn is C++, this is a pointer to an
	//			instance of the class which fn is in
	//			else NULL
	// @return		0 if OK else <0 = DRAGON error number
	//			    DERR_FN_ARG0: iState out-of-range
	int registerAction(int iState,
			   STATE_FN fn,
			   BASE_CLASS * pInstance);

	// Start by moving to the initial state and executing its
	// registered fn if any)
	// This must be after init() and normally should be after
	// all registerAction calls.
	// @return		0 if OK else <0 = DRAGON error number
	//			    DERR_BAD_STATE: init not yet called
	//			    DERR_FN_ARG0: initial state is bad
	//			    DERR_ACTION_FAILED: failure in action fn
	int start();

	// Enter state based on current state and specified event
	// This version is the normal way to transition states
	// Note that there are no GUARD fns. 
	//    The caller of this fn should verify guard conditions before
	//    invoking it
	// @return		0 if OK else <0 = DRAGON error number
	//			    DERR_FN_ARG0: uEvent out-of-range
	//			    DERR_BAD_STATE: current state out-of-range
	//			    DERR_ACTION_FAILED: failure in action fn
	int setState(uint uEvent);

	// enter specified state
	// This version should be used only in special cases
	// @return		0 if OK else <0 = DRAGON error number
	//			    DERR_FN_ARG0: iState out-of-range
	//			    DERR_ACTION_FAILED: failure in action fn
	int setState(int iState,const char * pczReason);

	// get the current state
	// @return 	current state number which comes from the
	//		results array. MAY BE ANY <0 value as
	//		specified in the results table.
	int getState() { return m_iStateNo; } ;

	// get the current state name
	const char *getStateName() const
	    { return (m_iStateNo < 0) ? m_ErrorState.pczName
		  : (m_iStateNo < (int)m_uStateCount) ? m_States[m_iStateNo].pczName : "Unknown"; } ;

	// get the specified state name
	const char * getStateName(uint uStateNo) const
	    { return (uStateNo < m_uStateCount) ? m_States[uStateNo].pczName : "Unknown"; } ;

	// get the specified event name
	const char * getEventName(uint uEventNo) const 
	    { return (uEventNo < m_uEventCount) ? m_Events[uEventNo].pczName : "Unknown"; } ;

	const char * dump(int detail, const char * pczTitle) const;

    protected:
	uint m_uStateCount;
	uint m_uEventCount;
	FSM_STATE * m_States;
	FSM_EVENT * m_Events;
	int * m_piResults;
	int m_iInitialState;
	int m_iStateNo;
	FSM_STATE m_ErrorState;
#if defined _WIN32
	int m_iDebug;
	int m_iTrace;
	static char s_outbuf[2048];
#endif
    } ;

#endif // #ifndef FSM_H

