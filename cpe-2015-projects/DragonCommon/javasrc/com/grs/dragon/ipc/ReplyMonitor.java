/**
 *  ReplyMonitor
 *
 *  ~~ Copyright 2001-2015 by Goldin-Rudahl Associates
 *  ~~ EndC
 *
 *  Implemented by Sally Goldin, 4/27/2001
 *
 *  $Id: ReplyMonitor.java,v 1.2 2015/01/01 09:42:06 rudahl Exp $
 *  $Log: ReplyMonitor.java,v $
 *  Revision 1.2  2015/01/01 09:42:06  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.1  2001/11/19 20:30:32  goldin
 *  Move IPC classes to new package
 *
 *  Revision 1.8  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.7  2001/09/10 14:38:45  goldin
 *  Separate special command processing into pre and post processing, move pre to CommandForwarder
 *
 *  Revision 1.6  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.5  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.4  2001/05/30 11:51:01  goldin
 *  Get tracing info right before creating Rpy file
 *
 *  Revision 1.3  2001/05/11 19:06:00  goldin
 *  Change IPC file format; enhance & debug tracing
 *
 *  Revision 1.2  2001/05/02 11:14:41  goldin
 *  Implement IncomingCommandProcessor functionality
 *
 *  Revision 1.1  2001/04/27 11:28:37  goldin
 *  Rename CompletionMonitor to ReplyMonitor
 *
 */
package com.grs.dragon.ipc;
import com.grs.gui.*;
import java.io.*;

/**
 * This sub-class of FileDetector waits for the file indicating 
 * the completion of a Dragon operation to appear in the appropriate 
 * directory. When it does appear, the class reads and processes the file, 
 * then signals the command forwarder  (referenced by the completionListener 
 * attribute) that the operation is complete.
 * <p>
 * The command forwarder then takes the information parsed from the server
 * operation completion file and updates the Dragon UI appropriately. 
*/
public class ReplyMonitor extends FileDetector 
    {
      // All of the below are set by the constructor.
    protected CompletionListener completionListener;
    protected String filename = null;

      /**
       * to be returned back to the listener. Set to true for
       * Rpy file detector, false for Nak file detector.
       */
    protected boolean bSuccessFlag = true;

      /**
       * Constructor creates the FileDetector, initializing
       * its arguments, and starts it.
       */
    public ReplyMonitor(CompletionListener completionListener,
			String filename, 
			boolean bSuccessFlag)
        {
	this.completionListener = completionListener;
	this.filename = filename;
	this.bSuccessFlag = bSuccessFlag;
	File temp = new File(filename);
	filePattern = temp.getName();
	directory = temp.getParent();
	start();
	}

      /**
       * This method is called when the file is detected.
       * We create a new IpcFile from the file, and pass
       * this back to the completionListener via its
       * commandCompleted method. Before we do this, we
       * do any post processing associated with the special
       * command for this monitor (if any).
       */
    protected void executeFileAction(String filename)
            throws InterruptedException
        {
        long timeOffset = ApplicationManager.getTimeOffset();
	IpcFile ipcFile = new IpcFile(filename,timeOffset,false);
	while (!ipcFile.isComplete() && !ipcFile.isError())
	     {
             sleep(200);
	     ipcFile.retry();
	     }
        if (ipcFile.isError())
             bSuccessFlag = false;
	completionListener.commandCompleted(bSuccessFlag,ipcFile);
	}
    }
