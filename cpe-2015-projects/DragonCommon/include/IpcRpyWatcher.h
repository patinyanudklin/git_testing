/*
 *	filename IpcRpyWatcher.h
 *		$Id: IpcRpyWatcher.h,v 1.7 2014/12/07 02:53:46 rudahl Exp $	
 *
 *      ~~ Copyright 2001-2014 Kurt Rudahl and Sally Goldin
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
 * $Id: IpcRpyWatcher.h,v 1.7 2014/12/07 02:53:46 rudahl Exp $
 * $Log: IpcRpyWatcher.h,v $
 * Revision 1.7  2014/12/07 02:53:46  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.6  2014/12/05 11:51:02  rudahl
 * added ifdefs to match DragonProf and OpenDragon
 *
 * Revision 1.5  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.4  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.3  2005/02/09 13:36:28  goldin
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.2  2001/08/08 15:19:34  rudahl
 * fixed parsing of files including a blob, and permit waylay other modules Rpy files
 *
 * Revision 1.1  2001/06/15 19:52:50  rudahl
 * initial version
 *
 ****************************************************************
 * 
 * This is the header file for IpcRpyWatcher class.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005-2-9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 6.3	2012-12-28 ktr	added IpcStyle
 * 
 */

#ifndef IPCRPYWATCHER_H
#define IPCRPYWATCHER_H

/**
 * Watches for rpy from anywhere with specified sequence number
 */

class IpcWatcher;
class IpcReceiveWatcher;

class IpcRpyWatcher : public IpcReceiveWatcher
    {
    public:	
	/*
	 * @param uStyle      what type of IPC communication to use?
	 *		      IPC_XML wraps the content in XML
	 *		      IPC_URL and IPC_SOCKET yet to be defined
	 */
	IpcRpyWatcher(const char * czSequence,IPC_STYLE_t uStyle = IPC_CLASSIC);

	/* this constructor permits us to waylay an Rpy addressed to a 
	 * different module than this one. It is needed by ScriptServer
	 * to detect and delete Rpy files sent by Server to UI, 
	 * which UI knows nothing about.
	 * (see the 'G' iPreExec command in CmdProcessor)
	 */
	IpcRpyWatcher(const char * czSequence, const char * czModule,IPC_STYLE_t uStyle = IPC_CLASSIC);

	~IpcRpyWatcher();
	/**
	 * Return value associated with named attribute, or null
	 * if if name not found
	 * The name returned is MALLOC'd and must be freed.
	 */
	const char * getAttributeValue(const char * attributeName);

	/**
	 * Return a blank-separated string  of all attribute names 
	 * represented in the attributes table.
	 */
	const char * getAttributeNames();

	/* is the reply available? If so, what is its status?
	 * @return  status  =0 => nothing there
	 *                  =1 => it's complete; go get it
	 *                    (and cleanup afterward)
	 */
	int getRpyStatus();

	virtual const char * className();
    protected: /* MEMBERS */
	char * czProtoFile;

    private:
	static Class s_class_Base;
    };

#endif //IPCRpyWATCHER_H
