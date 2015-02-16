/**
 * IncomingCommandProcessor
 *
 *  ~~ Copyright 2004-2015 by Sally Goldin & Kurt Rudahl
 *  ~~ EndC
 *
 *  Created by Sally Goldin, 4/27/2001
 *  
 *  $Id: IncomingCommandProcessor.java,v 1.4 2015/01/01 09:42:06 rudahl Exp $
 *  $Log: IncomingCommandProcessor.java,v $
 *  Revision 1.4  2015/01/01 09:42:06  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.3  2008/08/09 09:42:24  goldin
 *  Change to supply geounit in DISPLAY commant, MARKER style in DrawLine
 *
 *  Revision 1.2  2005/02/06 08:35:00  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.1  2001/11/21 15:17:18  goldin
 *  Move generic IncomingCommandProcessor to ipc pkg,
 *
 *  Revision 1.18  2001/11/19 20:29:38  goldin
 *  Moved IPC classes to new package
 *
 *  Revision 1.17  2001/11/16 18:05:54  goldin
 *  Move more classes from dragon.ui to gui package
 *
 *  Revision 1.16  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.15  2001/10/12 18:40:10  goldin
 *  Remove console msgs
 *
 *  Revision 1.14  2001/10/03 15:15:46  goldin
 *  Modify display to index some lines
 *
 *  Revision 1.13  2001/09/11 14:50:30  goldin
 *  Implement -WAIT command
 *
 *  Revision 1.12  2001/08/31 13:33:46  goldin
 *  Implement multiple table displays, ability to kill table displays via incoming command
 *
 *  Revision 1.11  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.10  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.9  2001/05/22 10:51:38  goldin
 *  Get rid of debug msgs
 *
 *  Revision 1.8  2001/05/22 10:25:05  goldin
 *  Fix ANOTHR bug in processing TRACE command
 *
 *  Revision 1.7  2001/05/22 10:16:46  goldin
 *  Fix bug in processing TRACE command
 *
 *  Revision 1.6  2001/05/18 17:23:04  goldin
 *  Work on improving behavior of logo on empty panel
 *
 *  Revision 1.5  2001/05/11 19:06:00  goldin
 *  Change IPC file format; enhance & debug tracing
 *
 *  Revision 1.4  2001/05/03 15:04:31  goldin
 *  Add special file handling to command line and command forwarder
 *
 *  Revision 1.3  2001/05/02 15:11:41  goldin
 *  Implement message and progress IPC file processing
 *
 *  Revision 1.2  2001/05/02 11:14:41  goldin
 *  Implement IncomingCommandProcessor functionality
 *
 *  Revision 1.1  2001/04/27 19:42:24  goldin
 *  Initial implementation of class to handle commands coming into the UI
 *
 */

package com.grs.dragon.ipc;
import com.grs.gui.*;
import com.grs.dragon.ipc.*;
import java.io.*;
import java.util.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * This class looks for files that indicate commands coming in
 * to an application Unlike most subclasses of the FileDetector class,
 * it does not exit its run method when it finds a file, but
 * rather, continues to loop looking for additional files.
 * <p>
 * This class handles the commands that are common to all
 * Dragon applications. It is subclassed in the UI to
 * handle additional logic.
 */
public class IncomingCommandProcessor extends FileDetector
    {
    protected String modulePrefix = null;

    /**
     * Constructor sets up file pattern for command files,
     * which will always have the same pattern.
     */
    public IncomingCommandProcessor(String modulePrefix)
        {
        if (modulePrefix.length() > 2)
            this.modulePrefix = modulePrefix.substring(0,2);
	else 
	    this.modulePrefix = modulePrefix;
        this.filePattern = "Cmd"+ this.modulePrefix + "*.$$$";
	this.directory = ApplicationManager.getTempPath();
	this.modulePrefix = modulePrefix;
	start();
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
             sleep(100);
	     ipcFile.retry();
	     }
        // now, get the command and act accordingly
        String command = ipcFile.getCmdText();
	if (command == null)  // this would be totally anomalous
	     {
             return;
	     }
        processCommand(command,ipcFile);
        }

      /**
       * This method does the work of parsing and dispatching the
       * command.
       * @param  command  Full text of the command
       * @param  ipcFile  Object representing the incoming command file
       * @return true if command recognized, else false.
       */
    protected boolean processCommand(String command, IpcFile ipcFile)
        {
	boolean bOk = true;
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
	if (verb.equalsIgnoreCase("-NOOP"))
	     return bOk;
	else if (verb.equalsIgnoreCase("-SETTIME"))
	     {
             doSetTime(ipcFile);  
	     }
        else if (verb.equalsIgnoreCase("-GETTIME"))
	     {
	     doGetTime(ipcFile);
	     }
        else if (verb.equalsIgnoreCase("-TRACE"))
	     {
	     String argument;
             int posx = command.indexOf(" ",pos+1);
	     if (posx < 0)
                 posx = command.indexOf("\n",pos+1);
	     if (posx < 0)
	         argument = command.substring(pos+1);
             else
	         argument = command.substring(pos+1,posx);
	     if (argument.startsWith("0"))
	         {
                 Tracer.setTracing(false);
		 }
	     else if ((argument.length() > 7) &&
                      (argument.startsWith("file://")))
                 {        
		 String tracefile = argument.substring(7);
		 Tracer.setTraceFile(tracefile);
		 }
	     else if (argument.length() >= 1)
	         {
                 Tracer.setTracing(true);
		 }
	     }
        else 
	     {
	     bOk = false;
	     }
	return bOk;
	}

      /**
       * Factorization of executeFileAction
       * to handle a -SETTIME command
       */
    protected void doSetTime(IpcFile ipcFile)
        {
        String timeString = ipcFile.getTimeStampString();
	int p = timeString.indexOf("=");
	if (p > 0)
	  timeString = timeString.substring(p+1);
	long fileTime = Long.parseLong(timeString);
	long localTime = new Date().getTime()/(long)1000;
	long newOffset = localTime - fileTime;
	ApplicationManager.setTimeOffset(newOffset);
	}

      /**
       * Factorization of executeFileAction
       * to handle a -GETTIME command
       */
    protected void doGetTime(IpcFile ipcFile)
        {
        String timeString = ipcFile.getTimeStampString();
	int p = timeString.indexOf("=");
	if (p > 0)
	  timeString = timeString.substring(p+1);
	long fileTime = Long.parseLong(timeString);
	long localTime = new Date().getTime()/(long)1000;
	long newOffset = localTime - fileTime;
        long currentOffset = ApplicationManager.getTimeOffset();
        long offsetDiff = currentOffset - newOffset;
        String rpyFileName = directory + File.separator +
	  "Rpy" + ipcFile.getSourceModule() + ipcFile.getSequence() +
          ".$$$";
        try 
	    {
	    FileWriter writer = new FileWriter(rpyFileName);
	    StringBuffer contents = new StringBuffer();
            timeString = String.valueOf(localTime);
	    contents.append("( ");
	    contents.append(IpcFile.ZEROS.substring(0,12 - timeString.length()));
	    contents.append(timeString + " 999 " + modulePrefix + " )\n");
	    contents.append("TimeError=" + ((offsetDiff < 0)? "-" : "+"));
            String errorString = String.valueOf(Math.abs(offsetDiff));
	    contents.append(IpcFile.ZEROS.substring(0,12 - errorString.length()));
            contents.append(errorString);
	    contents.append("\n");
            contents.append("Writer=IncomingCommandProcessor\n");
	    int fileLen = contents.length();
	    if (fileLen < 100)
	        fileLen -= 1;
	    if (fileLen > 999)
	        fileLen += 1;
	    contents = contents.replace(15,18,String.valueOf(fileLen));
            writer.write(contents.toString());
            writer.close();
	    // create an IpcFile to monitor the file and log its contents
	    // monitor only - don't delete.
	    IpcFile rpyIpcFile = 
	      new IpcFile(rpyFileName,ApplicationManager.getTimeOffset(),true);
            }
	catch (IOException ioe)
	    {
            System.out.println("Error writing Rpy file for GETTIME");
	    }
	}


    /**
     * This method loops, periodically examining the directory 
     * passed in to the constructor for a file that matches the 
     * pattern passed in the constructor.
     * When such a file appears in the directory, the method calls 
     * executeFileAction passing the relevant filename as an argument, 
     * and then returns to looping. 
     */
    public void run()
        {
        File dirFile = new File(directory);
        File[] matchFiles = null;
        while (true)
	    {
            try 
	        {
	        sleep(500);
                matchFiles = dirFile.listFiles(this);
		// if we find matches, process them
                if ((matchFiles != null) &&
		    (matchFiles.length > 0))
		    {
		    for (int i = 0; i < matchFiles.length; i++)
		        {
			executeFileAction(matchFiles[i].getAbsolutePath());
			}
		    }
                }
            catch (InterruptedException ie)
	        {
		  // continue to loop 
		}
	    }
        }
    }








