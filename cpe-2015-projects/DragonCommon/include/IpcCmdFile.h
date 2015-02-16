/*
 *	filename IpcCmdFile.h
 *		$Id: IpcCmdFile.h,v 1.8 2014/12/05 09:58:46 rudahl Exp $	
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
 * $Id: IpcCmdFile.h,v 1.8 2014/12/05 09:58:46 rudahl Exp $
 * $Log: IpcCmdFile.h,v $
 * Revision 1.8  2014/12/05 09:58:46  rudahl
 * no differences between DragonProf and OpenDragon
 *
 * Revision 1.7  2005/02/12 02:58:02  goldin
 * Fixes to make this library compile
 *
 * Revision 1.6  2005/02/09 13:36:28  goldin
 * Update file comment block and includes in preparation for move to RSGISProject
 *
 * Revision 1.5  2001/11/20 20:32:55  rudahl
 * Revamped IpcCmdWatcher (and by implication, IpcReceiveWatcher) to recognize
 * that the sender of a CmdFile cannot be determined from the file name.
 *
 * Revision 1.4  2001/05/09 20:59:43  rudahl
 * finished adapting for MSC16; started for Zortech* *.cpp *.h
 *
 * Revision 1.3  2001/05/08 20:26:29  rudahl
 * extensive revisions to support Viewport (16-bit), and to generally
 * advance the implementation stage.
 *
 * Revision 1.2  2001/05/02 18:40:03  rudahl
 * added Ipc writing capabilities, CLI args
 *
 * Revision 1.1  2001/04/27 21:25:58  rudahl
 * Initial deposit from tower
 * This is the IPC package developed within Together
 ****************************************************************
 * 
 * This is the header file for the IpcCmdFile class.
 *
 ******************************************************************
 *	Developers
 * 		ktr	Kurt Rudahl
 *		seg	Sally Goldin
 *
 *	Revision History
 * 5.5	2005-2-9 ktr	imported from Dragon Academic Edition rev 5.4.4
 * 
 */

#ifndef IPCCMDFILE_H
#define IPCCMDFILE_H

/**
 * This class represents a specific type of a Dragon interprocess
 * communication (IPC) file. These files are used to communicate 
 * commands between various Dragon modules
 * (UI, server, viewport, etc.).*/
class IpcCmdFile : public IpcFile
    {
    public:	
	/**
	 * The IPC file constructor is called after a file is known to
	 * exist, with a full name including path. It reads the file to
	 * determines if it is complete (based on file size). 
	 * If it is not complete, it leaves the bComplete flag set to false
  	 * and returns immediately. 
	 * The caller must repeatedly call isComplete() until successful.
	 * When the file is complete, isComplete or the constructor 
	 * does further processing, setting
	 * the various attributes of the file, reading the data, etc. 
	 * The detailed processing depends on the type of file involved. 
	 * @param filename    Name of IpcFile (with path). Since this file has 
	 *                    been detected in the file system,
	 *                    it is assumed to exist.
	 */
	IpcCmdFile(const char * filename);	
	~IpcCmdFile();

	 /* return value is MALLOC'd but will be freed by dtor. */
	const char * getCmdText();

	virtual const char * className();
    protected:

	/**
	 * Main method for reading the non-common parts of 
	 * the IPC file. This method specifically implements
	 * CMD files.
	 */
	void parseRemainder(char * fullFileName);

    public:
	/* Create a name (including path) valid for Cmd file
	 * The name returned is MALLOC'd and must be freed.
	 * @param  czDestinationModule   the 2-letter abbreviation target
	 *                               '??' for wildcard
	 * @param  czSequence            '' for next avail, '*' for wildcard
	 */
	static char * createFilename(const char * czDestinationModule,
					   const char * czSequence);

	/* Create the file, and send it
	 * To use this, call this class with the file contents.
	 * This will prefix that with other necessary fields
	 * and call the parent class fn which will write it to the disk.
	 * Return value is ALLOCd and must be freed.
	 * @param   czName is without the path
	 * @param   czText is the trailing part of the contents.
	 * @return  NULL if error; else the full text of the file
	 *          (which must be freed)
	 */
	static char * sendFile(const char * czName,const char * czText);

    protected: /* MEMBERS */

	/**
	 * Text of command. Only relevant for CMD type files. 
	 * This is MALLOC'd and must be freed by dtor.
	 */
	char * cmdText;

	/**
	 * generator of command sequences - 0 to 999
	 */
	static ushort uCmdSequence;

    private:
	static Class s_class_Base;

    };

#endif //IPCCMDFILE_H
