/* 
 *	filename IpcReceiveWatcher.h
 *		$Id: IpcReceiveWatcher.h,v 1.10 2014/12/07 02:53:46 rudahl Exp $
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
 *
 * $Id: IpcReceiveWatcher.h,v 1.10 2014/12/07 02:53:46 rudahl Exp $
 * $Log: IpcReceiveWatcher.h,v $
 * Revision 1.10  2014/12/07 02:53:46  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.9  2014/12/05 11:51:02  rudahl
 * added ifdefs to match DragonProf and OpenDragon
 *
 * Revision 1.8  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.7  2006/01/13 14:20:29  rudahl
 * improving tracing control
 *
 * Revision 1.6  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.5  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.4  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.3  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 ****************************************************************
 * 
 * This is the header file for the IpcReceiveWatcher class.
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
 *
 */

#ifndef IPCRECEIVEWATCHER_H
#define IPCRECEIVEWATCHER_H

class IpcWatcher;
class IpcSendWatcher;

class IpcReceiveWatcher : public IpcWatcher
    {
    public:	
	/*
	 * @param uStyle      what type of IPC communication to use?
	 *		      IPC_XML wraps the content in XML
	 *		      IPC_URL and IPC_SOCKET yet to be defined
	 */
	IpcReceiveWatcher(const char * czRemoteModule, 
			  const int iType,IPC_STYLE_t uStyle = IPC_CLASSIC);
	/* ultimately, this MUST be followed by cleanup() before a new
	 * IpcFile can be sought */
	BOOL isAvailable(const char * filename);	

	/* DELETE/FREE anything hanging around */
	void cleanup(); 

	virtual const char * className();

	/* create and send a Rpy file.
	 * then immediately do a cleanup
	 * @param   czMessage   all text which follows the initial, (), line
	 */
	void sendReply(const char * czMessage);

	/* don't know why we need this */
	IpcSendWatcher * getSendWatcher();

	/* retrieve sender of received file
	 * @return         static buffer containing the sender abbreviation
	 */
	const char * getSender();

	/* retrieve sequence string of current file
	 * @return         static buffer containing the sequence string,
	 *                 or '000' if fname is NULL
	 */
//	const char * getFileSequence();

    protected: /* MEMBERS */
	/* ReceiveWatchers for Cmd, Qry need to be able to reply */
	IpcSendWatcher * pRpySendWatcher;

	/* this is MALLOCd and must be FREEd */
	char * pczCurrentFileName;
    private:
	static Class s_class_Base;
    };

#endif //IPCRECEIVEWATCHER_H
