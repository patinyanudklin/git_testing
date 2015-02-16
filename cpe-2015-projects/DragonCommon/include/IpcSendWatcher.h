/*
 *	filename IpcCmdFile.h
 *		$Id: IpcSendWatcher.h,v 1.11 2014/12/07 02:53:46 rudahl Exp $	
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
 * $Id: IpcSendWatcher.h,v 1.11 2014/12/07 02:53:46 rudahl Exp $
 * $Log: IpcSendWatcher.h,v $
 * Revision 1.11  2014/12/07 02:53:46  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.10  2014/12/05 11:51:02  rudahl
 * added ifdefs to match DragonProf and OpenDragon
 *
 * Revision 1.9  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.8  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.7  2005/02/09 13:36:28  goldin
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.6  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
 *
 * Revision 1.5  2001/06/02 18:25:54  rudahl
 * added reSend, for progress file
 *
 * Revision 1.4  2001/05/30 17:28:47  rudahl
 * integrate server and viewport communication
 *
 * Revision 1.3  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 *
 ****************************************************************
 * 
 * This is the header file for the IpcSendWatcher class.
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

#ifndef IPCSENDWATCHER_H
#define IPCSENDWATCHER_H

class IpcSendWatcher : public IpcWatcher
    {
    public:
	IpcSendWatcher(const char * czTargetModule, const int iType,
		    IPC_STYLE_t uStyle = IPC_CLASSIC);

	/* create and send a file.
	 * The name of the file can be gotten from getFileName(),
	 * the sequence from getFileSequence(),
	 * the state from getSendState()
	 * but only until cleanup() is executed.
	 * @param   czMessage   all text which follows the initial, (), line
	 * @param   iSeqNo      if supplied, is the specific sequence 
	 *                      number which must be used 
	 */
	void send(const char * czMessage, const char * czSequence);

	/**
	 * send message which requires a code (see above comments)
	 * @param   iCode       code to be used in message
	 * @param   czMessage   all text which follows the initial, (), line
	 * @param   iSeqNo      if supplied, is the specific sequence 
	 *                      number which must be used 
	 */
	void send(const int iCode,const char * czMessage, 
		  const char * czSequence);

	/* this version is specialized for cases with a blob, 
	 * of which the only one is Rpy */
	void send(const char * czMessage, const char * czSequence,
		  const byte * pBlob, const size_t uBlobSize);

	/* revise an already sent file. Currently only for PRO files
	 * The name of the file can be gotten from getFileName(),
	 * the sequence from getFileSequence(),
	 * the state from getSendState()
	 * but only until cleanup() is executed.
	 * @param  uPercent ranges from 0 to 99
	 * @param  ulTare   is file size with zero percent in it
	 * @return new file size ONLY if ulTare == 0, else return 0
	 *         BUT return -1 if error
	 */
	long reSend(const ulong ulPercent, const ulong ulTare);

	/** 
	 *  get current status of message which has been sent:
	 *   0      sent
	 *   1      accepted
	 *   2      progress PRO file seen
	 *   3      RPY seen
	 *   4      accepted and no further activity expected
	 *   < 0 => various errors:
	 *   -1     unknown
	 *   -2     NAK seen
	 *   -3     send blocked
	 *   -4     timeout
	 */
	const char * getFilename();
	time_t getFileTimeStamp();
	int getSendState();

	void cleanup();

	virtual const char * className();

	/* for certain Cmd files, don't wait. 
	 * invoke this AFTER send()
	 */
	void setNoWait();

    protected: /* MEMBERS */
	char * pczFilename; /* alloc'd */
	time_t ulTimeStamp;
	BOOL bNoWait; /* this type and content does not expcet a response */ 

    private:
	static Class s_class_Base;

    };

#endif //IPCSENDWATCHER_H
