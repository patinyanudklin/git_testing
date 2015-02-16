/**
 * UiIncomingCommandProcessor
 *
 *  Copyright  2001-2007 by Goldin-Rudahl Associates
 *  Created by Sally Goldin, 11/21/2001
 *  
 *  $Id: UiIncomingCommandProcessor.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: UiIncomingCommandProcessor.java,v $
 *  Revision 1.4  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.3  2006/01/24 06:29:58  goldin
 *  Don't enable the UI until we get a signal from the ScriptServer
 *
 *  Revision 1.2  2002/01/24 17:07:55  goldin
 *  Put wait processing in separate thread
 *
 *  Revision 1.1  2001/11/21 15:16:41  goldin
 *  Move generic IncomingCommandProcessor to ipc pkg, create specialization in UI
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.ipc.*;
import java.io.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * This class looks for files that indicate commands coming in
 * to Dragon. It handles specialized commands as well as the
 * -ABEXIT command, which cannot be dealt with in an application-
 * independent manner. It uses superclass methods to handle
 * other standard commands.
 */
public class UiIncomingCommandProcessor extends IncomingCommandProcessor
    {

      /**
       * Hold onto the main application reference.
       */
    protected DragonUI mainApp = null;


    /**
     * Constructor sets up file pattern for command files,
     * which will always have the same pattern.
     */
    public UiIncomingCommandProcessor(DragonUI mainApp)
        {
        super("UI");
	this.mainApp = mainApp;
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
        if (verb.equalsIgnoreCase("-KILLMSG"))
	     {
	     doKillMsg(ipcFile);
	     }
	else if (verb.equalsIgnoreCase("-WAIT"))
	     {
	     doWait(ipcFile);
	     }
	else if (verb.equalsIgnoreCase("-ENABLEUI"))
	     {
             mainApp.setEnableSignalled(true);
	     mainApp.setReady(true);
	     }
	else if (verb.equalsIgnoreCase("-ABEXIT"))
	     {
	     mainApp.doExit();
	     }
        else 
	     {
	     System.out.println("Unknown command: " + verb);
	     }
	}

      /**
       * Factorization of executeFileAction
       * to handle a -KILLMSG command
       */
    protected void doKillMsg(IpcFile ipcFile)
        {
        String command = ipcFile.getCmdText();
	String argument = null;
        int pos = command.indexOf(" ");
        if (pos < 0)
	    {
            argument = "*";
	    }
	else
	    {
            int pos2 = command.indexOf("\n");
            if (pos2 > 0)
                argument = command.substring(pos+1,pos2);
	    else
                argument = command.substring(pos+1);
	    }
        mainApp.killMessage(argument.trim());
	}

      /**
       * Factorization of executeFileAction
       * to handle a -WAIT command
       */
    protected void doWait(IpcFile ipcFile)
        {
        DragonUI dragonUI = DragonUI.currentApplication;
        String command = ipcFile.getCmdText();
	String argument = null;
        int pos = command.indexOf(" ");
        if (pos >=0)
	    {
            int pos2 = command.indexOf("\n");
            if (pos2 > 0)
                argument = command.substring(pos+1,pos2);
	    else
                argument = command.substring(pos+1);
	    }
	dragonUI.getScriptCtrl().setCurrentState(
                ScriptControlPanel.WAITING_STATE);

	if (argument != null)
	    {
	    try 
	       {
	       int seconds = Integer.parseInt(argument);
	       ScriptWaiter waiter = new ScriptWaiter(this,seconds);
	       waiter.start();
	       }
	    catch (NumberFormatException nfe)
	       {
		// wait forever if the wait count is bad
	       }
	    }
	}

    /**
     * Method to output a continue command, called after sleep from
     * the run method of a ScriptWaiter instance. When the timer expires,
     * this method sends a -CONTINUE message to the script server,
     * then sets the control panel state to running.
     */
   protected void sendContinueCommand()
       {
       DragonUI dragonUI = DragonUI.currentApplication;
       int currentState = dragonUI.getScriptCtrl().getCurrentState();
       // if the user already clicked on continue, don't send a 
       // second -CONTINUE command 
       if (currentState != ScriptControlPanel.WAITING_STATE)
            return;
       if (dragonUI.getScriptCtrl().wasLastScriptCancelled())
            return;
       dragonUI.getCommandForwarder().sendCommandToServer("-CONTINUE");
       dragonUI.getScriptCtrl().setCurrentState(
              ScriptControlPanel.RUNNING_STATE);
       }

    }

   /**
    * Inner class to do waiting in a separate thread from
    * the UiIncomingCommandProcessor.
    */
class ScriptWaiter extends Thread
    {      
    protected UiIncomingCommandProcessor parentProcessor = null;
    protected int waitInterval = 0;

      /**
       * Constructor sets parentProcessor and waitInterval 
       * member variables.
       */
    public ScriptWaiter(UiIncomingCommandProcessor processor,
			int waitSeconds)
        {
	parentProcessor = processor;
	waitInterval = waitSeconds;
	}

    public void run()
        {
	try 
	   {
	   sleep(waitInterval * 1000); 
	   }
	catch (InterruptedException ie)
	   {
	   }
	parentProcessor.sendContinueCommand();
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UiIncomingCommandProcessor.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }




