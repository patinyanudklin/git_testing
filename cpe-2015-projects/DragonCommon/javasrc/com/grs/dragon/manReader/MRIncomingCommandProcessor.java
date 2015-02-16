/**
 * MRIncomingCommandProcessor
 *
 *  Copyright by Goldin-Rudahl Associates
 *  Created by Sally Goldin, 11/28/2001
 *  
 *  $Id: MRIncomingCommandProcessor.java,v 1.10 2007/05/31 03:26:53 rudahl Exp $
 *  $Log: MRIncomingCommandProcessor.java,v $
 *  Revision 1.10  2007/05/31 03:26:53  rudahl
 *  add 'whatis' boilerplate
 *
 *  Revision 1.9  2006/03/05 04:44:51  goldin
 *  Try to get manreader to pop to the front
 *
 *  Revision 1.8  2005/08/03 04:42:53  goldin
 *  Comment out references to Win32WindowRecorder for now
 *
 *  Revision 1.7  2002/09/23 19:55:33  goldin
 *  Call orderWindows to pop the MR to the top
 *
 *  Revision 1.6  2002/09/20 14:22:27  goldin
 *  Call recordWindowByTitle instead of just recordWindow
 *
 *  Revision 1.5  2002/09/19 22:36:21  goldin
 *  Add calls to record handle in DRAGON.INI
 *
 *  Revision 1.4  2002/06/27 21:30:48  goldin
 *  Miscellaneous refinements to behavior and appearance
 *
 *  Revision 1.3  2002/06/24 18:04:59  goldin
 *  Continue development for productization
 *
 *  Revision 1.2  2001/11/29 15:16:39  goldin
 *  Various enhancements including improvement of display, add -H argument, etc.
 *
 *  Revision 1.1  2001/11/28 15:30:54  goldin
 *  Add command processing
 *
 */

package com.grs.dragon.manReader;
import com.grs.gui.*;
import com.grs.dragon.ipc.*;
import com.grs.dragon.common.*;
import java.io.*;
import java.util.*;
import java.awt.Frame;
import java.awt.event.*;
import javax.swing.*;

/**
 * This class looks for files that indicate commands coming in
 * to the ManReader. It handles specialized commands as well as the
 * -ABEXIT command, which cannot be dealt with in an application-
 * independent manner. It uses superclass methods to handle
 * other standard commands.
 */
public class MRIncomingCommandProcessor extends IncomingCommandProcessor
    {

      /**
       * Hold onto the main application reference.
       */
    protected ManReader mainApp = null;
      /**
       * Hold on to the parent frame.
       */
    protected JFrame parentFrame = null;

    /**
     * Constructor sets up file pattern for command files,
     * which will always have the same pattern.
     */
    public MRIncomingCommandProcessor(ManReader mainApp,
				      JFrame parentFrame)
        {
        super("MR");
	this.mainApp = mainApp;
	this.parentFrame = parentFrame;
        }

    /**
     * This method is called when the file we are trying to detect appears
     * in the monitored directory. It figures out what command
     * needs to be executed, and acts accordingly.
     */
    protected void executeFileAction(String filename)
              throws InterruptedException
        {
	IpcFile ipcFile = new IpcFile(filename,
				      ApplicationManager.getTimeOffset(),
				      false);
	while (!ipcFile.isComplete())
	     {
             sleep(200);
	     ipcFile.retry();
	     }
        // now, get the command and act accordingly
        String command = ipcFile.getCmdText();
	if (command == null)  // this would be totally anomalous
	     {
             return;
	     }
	boolean bOk = super.processCommand(command,ipcFile);
	if (bOk)
	  return; // if false, this command was not handled by
	          // the superclass method
	String verb;
        int pos = command.indexOf(" ");
        if (pos < 0)
	    {
            pos = command.indexOf("\n");
	    }
	if (pos < 0)
	    {
            verb = command;
	    }
	else
	    {
            verb = command.substring(0,pos);
	    }
        if (verb.equalsIgnoreCase("SHOW"))
	     {
	     doShow(ipcFile);
	     }
	else if (verb.equalsIgnoreCase("-ABEXIT"))
	     {
		 //Win32WindowRecorder.removeWindow("MR");
	     System.exit(0);
	     }
        else 
	     {
	     System.out.println("Unknown command: " + verb);
	     }
	}

      /**
       * Factorization of executeFileAction
       * to handle a SHOW command
       */
    protected void doShow(IpcFile ipcFile)
        {
        String command = ipcFile.getCmdText();
	String argument = null;
	//System.out.println("Incoming command: " + command);
        int pos = command.indexOf(" ");
        if (pos >= 0)   // if no argument, then ignore
	    {
            int pos2 = command.indexOf("\n");
            if (pos2 > 0)
                argument = command.substring(pos+1,pos2);
	    else
                argument = command.substring(pos+1);
	    mainApp.setTopic(argument);
	    if (!parentFrame.isVisible())
	        parentFrame.setVisible(true);
	    if (parentFrame.getState() == Frame.ICONIFIED)
	        parentFrame.setState(Frame.NORMAL);
	    parentFrame.toFront();
	    parentFrame.requestFocus();
	    /*** No need to sleep since we're not recording
	         the window anymore.
	    try
	        {
		sleep(500); 
		// wait to make sure the window is visible and active
		//Win32WindowRecorder.recordWindowByTitle(
		//		   ManReader.MANREADER_TITLE,"MR");
		//Win32WindowRecorder.orderWindows("MR","UI");
		}
	    catch (Exception e)
	        {
		System.out.println("Native call generated exception");
		e.printStackTrace();
		}
	    ***/
	    }
	}
    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: MRIncomingCommandProcessor.java,v 1.10 2007/05/31 03:26:53 rudahl Exp $ \n";
	}

    }








