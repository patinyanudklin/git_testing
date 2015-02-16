/* 
 *	filename IpcCmdWatcher.h
 *		$Id: IpcCmdWatcher.h,v 1.14 2014/12/07 02:53:46 rudahl Exp $
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
 * $Id: IpcCmdWatcher.h,v 1.14 2014/12/07 02:53:46 rudahl Exp $
 * $Log: IpcCmdWatcher.h,v $
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
 * Revision 1.10  2005/09/27 03:12:36  rudahl
 * integrating SSDb into Executable required a const
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
 * Revision 1.5  2001/05/15 19:43:37  rudahl
 * created wrapper for using the IPC library with C files
 * various adaptations for use with Zortech, and to fix bugs
 *
 * Revision 1.4  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
 *
 * Revision 1.3  2001/05/04 08:44:41  rudahl
 * Adapted to dual MSoft 16-bit & 32-bit build
 * added fn to IpcCmdWatcher to process the default commands automatically
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
 * Watches for commands from anywhere and handles as many as possible 
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005-2-9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 5.7	2005-9-26 ktr	migrate to v 5.7
 * 6.3	2012-12-28 ktr	added IpcStyle
 * 
 */

#ifndef IPCCMDWATCHER_H
#define IPCCMDWATCHER_H

class IpcWatcher;
class IpcReceiveWatcher;

class IpcCmdWatcher : public IpcReceiveWatcher
    {
    public:	
        /*
	 * @param uStyle      what type of IPC communication to use?
	 *		      IPC_XML wraps the content in XML
	 *		      IPC_URL and IPC_SOCKET yet to be defined
	 */
	IpcCmdWatcher(const char * czRemoteModule,IPC_STYLE_t uStyle = IPC_CLASSIC);

	/** get the abbrev. of the module which sent the command
	 */
	const char * getSourceModule();

	/* the command str is part of the IpcFile
	 * both of which are deleted when executing cleanup()
	 */
	const char * getCommand();	

	/* is there a command available? If so, what is its status?
	 * @return  status  =0 => nothing there
	 *                  =1 => it's complete; go get it
	 *                    (and cleanup afterward)
	 *                  >1 for std cmds which have been fully processed:
	 *                    (and therefore the cleanup has already been done;
	 *                     however some info is still available)
	 *                   2 = -NOOP; 3 = -TRACE 
	 *                   4 = -SETTIME; 5 = -GETTIME 6 = -ABEXIT
	 */
	int getCmdStatus();

	/* return the value which was calc'd when latest -GETTIME was received
	 */
	long getTimeOffsetError();

	virtual const char * className();
	/* STATIC fn to scan a list of known commands and return the index
	 * of the one found, or -1.
	 * @param  czCommandList    list of commands to recognize
	 *                          if NULL, use required commands
	 * @param  uCommandListSize count of list
	 * @param  cmd              string containing command
	 */
	static int whichKnownCommand(const char ** czCommandList,
				     const size_t uCommandListSize,
				     const char * cmd);

	/* STATIC fn to execute one of the 'known' commands.
	 * @param  iCmd    index of command
	 * @return         true if command was handled
	 */
	static BOOL executeKnownCommand(const int iCmd);

    protected: /* MEMBERS */
	char * czProtoFile;

	long m_lTimeOffsetError;

    private:
	static Class s_class_Base;

    };

#endif //IPCCMDWATCHER_H
