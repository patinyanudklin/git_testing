/**
 *  CommandForwarder
 *
 *  Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 *  Implemented by Sally Goldin, 4/27/2001
 *
 *  $Id: CommandForwarder.java,v 1.42 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: CommandForwarder.java,v $
 *  Revision 1.42  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.41  2006/07/22 07:59:03  goldin
 *  Comment out experimental code
 *
 *  Revision 1.40  2006/07/21 06:01:04  goldin
 *  Try adding file signature code to identify modules
 *
 *  Revision 1.39  2006/01/20 07:47:48  goldin
 *  If we get a NAK, ask for new status info
 *
 *  Revision 1.38  2006/01/14 09:23:00  goldin
 *  Remove extra getpersist command
 *
 *  Revision 1.37  2005/12/05 09:39:08  goldin
 *  Working on UI hang problem - make CommandForwarder into its own thread
 *
 *  Revision 1.36  2005/11/17 08:25:37  goldin
 *  Only request a status update after successful operation
 *
 *  Revision 1.35  2005/11/04 10:53:27  goldin
 *  Working on setting and getting persistent data
 *
 *  Revision 1.34  2005/10/21 14:02:44  goldin
 *  Working on getting status info from persistent DB
 *
 *  Revision 1.33  2005/10/03 12:32:21  goldin
 *  Begin working on new status handling
 *
 *  Revision 1.32  2005/07/29 05:41:26  goldin
 *  Use image from status to init memory header
 *
 *  Revision 1.31  2005/07/24 13:14:06  goldin
 *  Put blob processing back in temporarily
 *
 *  Revision 1.31  2005/07/11 04:41:02  goldin
 *  Put blob processing back in
 *
 *  Revision 1.30  2005/03/29 09:11:17  goldin
 *  Remove blob processing
 *
 *  Revision 1.29  2005/02/06 09:00:25  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.28  2002/09/10 20:07:56  goldin
 *  Call status update even if you get a NAK and thus no attributes
 *
 *  Revision 1.27  2001/11/21 15:17:52  goldin
 *  Make all references to getTimeOffset use ApplicationManager method
 *
 *  Revision 1.26  2001/11/19 20:29:38  goldin
 *  Moved IPC classes to new package
 *
 *  Revision 1.25  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.24  2001/11/05 13:59:14  goldin
 *  Put UI code in a package
 *
 *  Revision 1.23  2001/10/31 12:44:07  goldin
 *  Fix bugs in UTF-8 conversion; RPY file cannot be UTF-8 b/c of binary data
 *
 *  Revision 1.22  2001/10/31 12:21:55  goldin
 *  work on UTF-8 encoding IPC files
 *
 *  Revision 1.21  2001/10/30 18:06:36  goldin
 *  Use UTF-8 for commands; replace stack with hashtable for
 *
 *  Revision 1.20  2001/10/08 15:00:26  goldin
 *  Need to set argument before processing special command
 *
 *  Revision 1.19  2001/10/02 13:20:47  goldin
 *  Don't include fixed text in commands
 *
 *  Revision 1.18  2001/09/10 14:38:17  goldin
 *  Separate special command processing into pre and post processing, move pre to CommandForwarder
 *
 *  Revision 1.17  2001/09/04 15:08:50  goldin
 *  Begin implementing script control panel
 *
 *  Revision 1.16  2001/08/31 14:01:02  goldin
 *  Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 *  Revision 1.15  2001/06/29 17:30:16  goldin
 *  Implemented handing of state info from reply files
 *
 *  Revision 1.14  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.13  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.12  2001/05/30 11:51:01  goldin
 *  Get tracing info right before creating Rpy file
 *
 *  Revision 1.11  2001/05/16 15:43:31  goldin
 *  Fine tune control appearance and behavior
 *
 *  Revision 1.10  2001/05/11 19:06:00  goldin
 *  Change IPC file format; enhance & debug tracing
 *
 *  Revision 1.9  2001/05/07 12:06:52  goldin
 *  Fix bugs in path handling
 *
 *  Revision 1.8  2001/05/04 15:36:36  goldin
 *  Modify control of Ready state
 *
 *  Revision 1.7  2001/05/03 15:04:31  goldin
 *  Add special file handling to command line and command forwarder
 *
 *  Revision 1.6  2001/05/02 15:11:41  goldin
 *  Implement message and progress IPC file processing
 *
 *  Revision 1.5  2001/05/02 11:14:41  goldin
 *  Implement IncomingCommandProcessor functionality
 *
 *  Revision 1.4  2001/04/27 11:29:00  goldin
 *  Continue implementation of interprocess communication and command handling
 *
 */

package com.grs.dragon.ui;
import com.grs.dragon.ipc.*;
import com.grs.gui.*;
import java.io.*;
import java.util.*;

/**
 * This class provides the interface between the Dragon user interface
 * and the Dragon server. It ships commands prepared by the UI to the
 * server, and processes responses. Responses can include either a Nak
 * or a reply indicating completion (possibly with errors). 
 * Progress messages and error/warning messages are handled by
 * other classes.
 */
public class CommandForwarder extends Thread implements CompletionListener
    {
      /*********
    static
      {
      StringBuffer buffer = new StringBuffer();
      buffer.append(
         "(#) $Id: CommandForwarder.java,v 1.42 2007/01/05 07:41:57 rudahl Exp $\n");
      }
      *****/
    protected static boolean bWaiting = false;
   
    protected static int cmdCounter = 0;
    protected String lastFileSequence = null;
      /**
       * Hashtables to handle nested or interleaved commands.
       * We want to make sure that we kill the correct
       * reply monitor for the command.
       */
    protected Hashtable completionTable = null;
    protected Hashtable nakTable = null;

      /**
       * monitoring objects created when a command is sent.
       * to look for Rpy or Nak files.
       */
    protected UiReplyMonitor completionMonitor = null;
    protected UiReplyMonitor nakMonitor = null;
      
      /**
       * Reference to main application.
       */
    protected DragonUI dragonUI;

      /**
       * Path where all files will be created/detected.
       */
    protected String filePath;

      /**
       * Master time offset for the UI.
       * Maintained by the DragonUI, checked before creating monitors.
       */
    protected long timeOffset = 0;

      /**
       * True if we are  tracing. Maintained by the UI, checked before
       * creating monitors.
       */
    protected boolean bTracing = false;

      /** 
       * True if there is a trace file. Maintained by UI, checked
       * before creating monitors.
       */
    protected String traceFile = null;

    protected boolean bFinished = false;

      /**
       * local reference to the IpcFile for the last created command.
       * Allows us to check if the file has been consumed, if we want,
       * and also handles logging.
       */
    protected IpcFile cmdIpcFile = null;


    /**
     * Constructor. This method sets up data items.
     * The class doesn't do anything until the immediately
     * sendCommandToServer method is invoked.
     */
    public CommandForwarder(DragonUI dragonUI, 
			    String filePath)
        {
        this.dragonUI = dragonUI;
	this.filePath = filePath;
        completionTable = new Hashtable(8);
        nakTable = new Hashtable(8);
        }


      /**
       * Callback executed by the completionMonitor or
       * the nakMonitor after a command has been executed.
       * @param bSuccess If true, we got a RPY file, which means
       *                 that the server at least tried to execute the
       *                 cmd. If false, we got a Nak.
       * @param replyFile Reference to IPCFile (Nak or Rpy) that 
       *                 was detected.
       */
    public void commandCompleted(boolean bSuccess,
				 IpcFile replyFile)
        {
        String mainImageName = null;
	bWaiting = false;
	cancelCommand(replyFile.getSequence());
	/* If we got a NAK, then request the current status. 
         * We'll process the results as a RPY 
         */
        if (replyFile.getFileType() == IpcFile.NAK_FILE_TYPE)
	   {
	   if (!(sendCommandToModule(
				  "-GETPERSIST table=CURRENT selector=STATUS",
				  "SS")))
	      {
	      dragonUI.getStatusManager().clearCurrentState();
	      dragonUI.refreshStatusDisplay();
              }
           }
        else
	   {
	   /* get the attributes */
	   Hashtable attributes = replyFile.getAttributes();
           if (attributes != null)
	       mainImageName = (String) attributes.get(StatusManager.MFILE);
  	   if (mainImageName != null)
	       {
	       String mainImagePath = (String) attributes.get(StatusManager.MPATH);
	       StringBuffer buffer = new StringBuffer();
	       if (mainImageName.compareTo("=M") == 0)
		   {
		   mainImageName = "$$m.img";
		   mainImagePath = DragonUI.cfgProcessor.getKpath();
		   attributes.put(StatusManager.MFILE,mainImageName);
		   attributes.put(StatusManager.MPATH,mainImagePath);
		   }
	       if (mainImagePath != null)
		 buffer.append(mainImagePath + File.separator);
	       buffer.append(mainImageName);
	       DImageHeader memoryHeader = new DImageHeader(buffer.toString());
	       if (memoryHeader.isInitialized())
		   dragonUI.setMemoryHeader(memoryHeader);
	       else
		   dragonUI.setMemoryHeader(null);
	       }
	   // Note - if this is a NAK file, we may not have any attributes
	   // but we still need to call this method in order to update
	   // the situation regarding the current signature & ply files.
	   dragonUI.getStatusManager().setCurrentState(attributes);
	   dragonUI.refreshStatusDisplay();
	   }
        }

      /**
       * Cancel current command unconditionally, killing off the monitors. 
       * This can be used to implement a timeout or other unusual event.
       * It is also called by commandCompleted to do cleanup.
       */
    public void cancelCommand(String sequenceKey)
        {
	// System.out.println("cancel command for sequence Key " + sequenceKey);
 	completionMonitor = (UiReplyMonitor) completionTable.get(sequenceKey);
        if (completionMonitor != null)
	    {
	    completionMonitor.interrupt();
            completionTable.remove(sequenceKey);
	    }
	nakMonitor = (UiReplyMonitor) nakTable.get(sequenceKey);
        if (nakMonitor != null)
	    {
	    nakMonitor.interrupt();
	    nakTable.remove(sequenceKey);
	    }
        dragonUI.showDefaultPanel();
        if (completionTable.isEmpty())
	    {
	    dragonUI.setReady(true);
	    bWaiting = false;
	    }
	// don't want to call if we're in a script because it may
	// wipe out the "paused" message
	}

    public boolean sendCommandToServer(String commandString)
        {
	boolean bOk = false;
        if (bWaiting)
	   {
	   /* Send a Nak to the DS just to make sure
	    * that any ongoing commands will be 
	    * canceled.
	    */
	   StringBuffer buffer = new StringBuffer();
           buffer.append(filePath + File.separator + "NakDS");
   	   if (cmdCounter < 10)
               buffer.append("00");
	   else if (cmdCounter < 100)
	       buffer.append("0");
	   buffer.append(String.valueOf(cmdCounter));
	   buffer.append(".$$$");
	   String nakFileName = buffer.toString();
	   StringBuffer contents = createFileContents(" ");
	   try
	      {
	      FileOutputStream fos = new FileOutputStream(nakFileName);
	      OutputStreamWriter osw = new OutputStreamWriter(fos,"UTF-8");
	      BufferedWriter writer = new BufferedWriter(osw);
	      writer.write(contents.toString());
	      writer.close();
	      bOk = true;
	      }
	   catch (IOException ioe)
	      {
		bOk = false; // this won't do anything...
	      }
	   }
        bOk = sendCommandToModule(commandString,"SS");
	return bOk;
	}

    public boolean sendCommandToModule(String commandString,
				       String module)
        {
	  //System.out.println("Processing command: " + commandString);
	boolean bExpectReply = true;
        String cmdFileName = null;
        String rpyFileName = null;
        String nakFileName = null;
        boolean bOk = true;
        cmdCounter++;
        if (cmdCounter > 100)
	   cmdCounter = 0;
        SpecialCommand specCmd = checkSpecial(commandString);
        if (specCmd != null)
	     {
             bExpectReply = specCmd.isReplyExpected();
             specCmd.doPreprocessing();
	     }
        StringBuffer buffer = new StringBuffer();
        buffer.append(filePath + File.separator + "Cmd" + module);
	if (cmdCounter < 10)
            buffer.append("00");
	else if (cmdCounter < 100)
	    buffer.append("0");
	buffer.append(String.valueOf(cmdCounter));
        lastFileSequence = buffer.substring(buffer.length()-3,
					   buffer.length());
          
        buffer.append(".$$$");
        cmdFileName = buffer.toString();
        if (bExpectReply)
	    {
            // set up monitors to look for the files before
	    // we actually send the command.
	    nakFileName = filePath + File.separator + "NakUI" + 
	      lastFileSequence + ".$$$";
	    rpyFileName = filePath + File.separator + "RpyUI" + 
	      lastFileSequence + ".$$$";
	    completionMonitor = new UiReplyMonitor(this,
					     rpyFileName,
					     true);
	    nakMonitor = new UiReplyMonitor(this,
					  nakFileName,
					  false);
	    if (specCmd != null)
	        {
		completionMonitor.setSpecialCmd(specCmd);
		nakMonitor.setSpecialCmd(specCmd);
		}
            completionTable.put(lastFileSequence,completionMonitor);
            nakTable.put(lastFileSequence,nakMonitor);
   	    bWaiting = true;
	    }
	StringBuffer contents = createFileContents(commandString);
	try
	    {
 	    FileOutputStream fos = new FileOutputStream(cmdFileName);
 	    OutputStreamWriter osw = new OutputStreamWriter(fos,"UTF-8");
	    BufferedWriter writer = new BufferedWriter(osw);
	    writer.write(contents.toString());
	    writer.close();
	    }
	catch (IOException ioe)
	    {
	    bOk = false;
	    }
        // create an IpcFile to monitor the file and log its contents
	// monitor only - don't delete.
        cmdIpcFile = new IpcFile(cmdFileName,
				 ApplicationManager.getTimeOffset(),
				 true);
	if (bExpectReply)
	    {
	    dragonUI.setReady(false);
	    }
        return bOk;
        }
     /**
     * Factorization - Create the command file contents 
     * and translate to UTF-8
     * @param  commandString command we are trying to write - could be empty
     * @return StringBuffer with contents ready to write.
     */
    protected StringBuffer createFileContents(String commandString)
       {
       long timestamp = (new Date().getTime() - timeOffset)/1000;
       String timeString = String.valueOf(timestamp);     
       StringBuffer contents = new StringBuffer();
       contents.append("( ");
       contents.append(IpcFile.ZEROS.substring(0,12 - timeString.length()));
       contents.append(timeString + " 00000 UI )\n");
       contents.append(commandString + "\n");
       int fileLen = contents.length();
       int fileLen2 = fileLen;
       int startPos = 0;
       if (fileLen < 10)
	  startPos = 19;
       else if (fileLen < 100)
	  startPos = 18;
       else if (fileLen < 1000)
          startPos = 17;
       else if (fileLen < 10000)
	  startPos = 16;
       else 
	  startPos = 15;
        //System.out.println("Before UTF-8 translation, fileLen is " +
        //                   fileLen); 
	contents = contents.replace(startPos,20,String.valueOf(fileLen));
	try 
	   {
	   byte[] bArray = contents.toString().getBytes("UTF-8");
	   fileLen2 = bArray.length;
	   //System.out.println("After UTF-8 translation, fileLen is " +
	   //               fileLen2);
	   if (fileLen2 != fileLen)
	       {
	       if (fileLen2 < 10)
		 startPos = 19;
	       else if (fileLen2 < 100)
		 startPos = 18;
	       else if (fileLen2 < 1000)
		 startPos = 17;
	       else if (fileLen2 < 10000)
		 startPos = 16;
	       else 
		 startPos = 15;
	       contents = contents.replace(startPos,20,
					   String.valueOf(fileLen2));
	       }
	  }
       catch (UnsupportedEncodingException uee)
	  {
          }
       return contents;	
       }

      /**
       * Check if text represents a special command. If so, return 
       * the SpecialCommand object for further processing.
       * @param cmdText Command line text just entered.
       * @return true if the text was a special command, else false.
       */
    protected SpecialCommand checkSpecial(String cmdText)
        {
	// strip off the CMD>> 
        if (cmdText.startsWith(CommandLine.CMDPROMPT))
	    {
	    int p = cmdText.indexOf(" ");
	    cmdText = cmdText.substring(p+1);
	    }
	int pos = cmdText.indexOf(" ");
        if (pos < 0)
	    pos = cmdText.indexOf("\n");
	String verb;
	if (pos < 0)
	    verb = cmdText;
	else
	    verb = cmdText.substring(0,pos);
	SpecialCommand cmd = dragonUI.getCommandLine().getSpecialCommand(verb);
	if (cmd == null)
	    return null;
	if (cmd.getArgCount() > 0)
	    {
	    if (pos < 0)
	         {
                 dragonUI.getErrorDisplay().showError(TextKeys.ERROR,
			     "%e420", null);
		 return null;
		 }
	    else
	         {
                 int pos2 = cmdText.indexOf("\n");
		 if (pos2 < 0)
		      cmd.setArgText(cmdText.substring(pos+1));
		 else
		      cmd.setArgText(cmdText.substring(pos+1, pos2));
		 }
	    }
	return cmd;
	}

      /**
       * File path may change during execution, so we need
       * to be able to reset it here.
       */
    public void setFilePath(String newPath)
        {
	filePath = newPath;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: CommandForwarder.java,v 1.42 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }




