/*
 *	filename IpcWatcher.h
 *		$Id: IpcWatcher.h,v 1.15 2014/12/18 08:09:15 rudahl Exp $
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

 * $Id: IpcWatcher.h,v 1.15 2014/12/18 08:09:15 rudahl Exp $
 * $Log: IpcWatcher.h,v $
 * Revision 1.15  2014/12/18 08:09:15  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.14  2014/12/07 02:53:46  rudahl
 * undo most conditionals re STYLE
 *
 * Revision 1.13  2014/12/05 11:51:02  rudahl
 * added ifdefs to match DragonProf and OpenDragon
 *
 * Revision 1.12  2013/01/03 13:50:40  rudahl
 * added argument to specify ipc style (method)
 *
 * Revision 1.11  2006/01/13 14:20:29  rudahl
 * improving tracing control
 *
 * Revision 1.10  2005/09/25 12:06:51  rudahl
 * improved docs, naming
 *
 * Revision 1.9  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.8  2005/02/09 13:36:28  goldin
 * Update file comment block and includes 
 * in preparation for move to RSGISProject
 *
 * Revision 1.7  2001/11/30 19:19:16  rudahl
 * moved whichKnownCommand; added executeKnown
 *
 * Revision 1.6  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.5  2001/08/15 13:49:27  rudahl
 * enriched sendCommand; added getSender, getSequence
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
 * This is the header file for the IpcWatcher class.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005-2-9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-9-25 ktr	changed member variable names to m_
 * 6.3	2012-12-28 ktr	added IpcStyle
 * 
 */

#ifndef IPCWATCHER_H
#define IPCWATCHER_H

#ifndef IPCFILE_H
typedef int IPC_STYLE_t;
#define IPC_CLASSIC 0
class IpcFile;
#endif

/**
 * IpcWatcher watches for interprocess communications of a specified type 
 * from the asociated executing process. 
 * 
 * Tthe constructor just creates an instance, which may be either for a 
 * send IPC bSend=TRUE) or for a read IPC.
 * 
 * The read is used by polling to isAvailable(). 
 * Other access fns just return the internal params and variables as needed.
 * 
 * For writing IPCs, use send(), then monitor its progress by calling getState.
 * 
 * Each IpcWatcher normally lives as long as the owning Executable 
 */
class IpcWatcher : public DragonObject
    {
    public:	

	  /**
	   * Constructor for either a read or send IPC. 
	   * This just constructs it; it doesn't actually do anything. 
	   * It need never be destructed.
	   * @param czRemoteModule is the abbreviation of the Executable 
	   *                       who owns it.
	   * @param iType          is the file type (enum)
	   * @param bSend          true for a send IPC; false for receive
	   * @param uStyle         what type of IPC communication to use?
	   *		             IPC_XML wraps the content in XML
	   *		             IPC_URL and IPC_SOCKET yet to be defined
	   */
	IpcWatcher(const char * czRemoteModule, const int iType,
		   const BOOL bSend,IPC_STYLE_t uStyle = IPC_CLASSIC);

	IpcFile * getFile();
	virtual const char * getFilename();

	/* retrieve sequence string of current file
	 * @return         static buffer containing the sequence string,
	 *                 or '000' if fname is NULL
	 */
	const char * getFileSequence();

	/* static fn which just string processes name 
	 * @param pczName  filename, or NULL
	 * @return         static buffer containing the sequence string,
	 *                 or '000' if pczName == NULL
	 */
	static const char * getFileSequence(const char * pczName);

	int getType();
	time_t getFileTimeStamp();
	virtual const char * className();

	/* DELETE/FREE anything hanging around */
	void cleanup(); 

    protected:  /* MEMBERS */
	/* this is NEW'd and must be DELETEd */
	IpcFile * m_pFile;

	char m_czRemoteModule[IPC_MODULEABBR_SZ+1];
	int m_iFileType;

	static const char * s_czIpcCommands[];

    private:
	static Class s_class_Base;

    };

#endif //IPCWATCHER_H
