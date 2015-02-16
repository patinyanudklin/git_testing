/**
 *  UiReplyMonitor
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 11/19/2001
 *
 *  $Id: UiReplyMonitor.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: UiReplyMonitor.java,v $
 *  Revision 1.2  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.1  2001/11/19 20:29:38  goldin
 *  Moved IPC classes to new package
 *
 */
package com.grs.dragon.ui;
import com.grs.dragon.ipc.*;
import com.grs.gui.*;
import java.io.*;

/**
 * This is a trivial sub-class of the more generic ReplyMonitor class.
 * It adds knowledge about special commands, which at the moment
 * are Dragon-UI specific. This class was split off from the
 * main ReplyMonitor class so that we could more that class
 * to the dragon.ipc package.
 *<p>
 * The class waits for the file indicating 
 * the completion of a Dragon operation to appear in the appropriate 
 * directory. When it does appear, the class reads and processes the file, 
 * then signals the command forwarder  (referenced by the completionListener 
 * attribute) that the operation is complete.
 * <p>
 * The reply monitor may apply post-processing if its specialCmd member
 * is not null. This allows arbitrary, command-specific logic to
 * be executed when a command completes.
 * <p>
 * The command forwarder then takes the information parsed from the server
 * operation completion file and updates the Dragon UI appropriately. 
*/
public class UiReplyMonitor extends ReplyMonitor 
    {
      // All of the below are set by the constructor.
      //  protected CompletionListener completionListener;  //superclass
      //  protected String filename = null;  //superclass

      // May be explicitly set by the command forwarder or
      // other class that creates the reply monitor.
    protected SpecialCommand specialCmd = null;

      /**
       * to be returned back to the listener. Set to true for
       * Rpy file detector, false for Nak file detector.
       */
      // protected boolean bSuccessFlag = true; //superclass

      /**
       * Constructor creates the FileDetector, initializing
       * its arguments, and starts it.
       */
    public UiReplyMonitor(CompletionListener completionListener,
			String filename, 
			boolean bSuccessFlag)
        {
        super(completionListener, 
	      filename, bSuccessFlag);
	}

      /**
       * This method is called when the file is detected.
       * We create a new IpcFile from the file, and pass
       * this back to the completionListener via its
       * commandCompleted method. Before we do this, we
       * do any post processing associated with the special
       * command for this monitor (if any).
       * Overrides  the ReplyMonitor method, providing
       * processing for SpecialCommands.
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
        if (specialCmd != null)
	     {
	     // pass on info as to whether this operation 
	     // was a success or a failure.
             if (bSuccessFlag)
	         specialCmd.setPostArgText("true");
             else 
	         specialCmd.setPostArgText("false");
	     specialCmd.doPostprocessing();
	     }
	completionListener.commandCompleted(bSuccessFlag,ipcFile);
	}

      /**
       * Method to allow external class to associate a special command
       * with this reply monitor. 
       */
    public void setSpecialCmd(SpecialCommand cmd)
        {
	specialCmd = cmd;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UiReplyMonitor.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
