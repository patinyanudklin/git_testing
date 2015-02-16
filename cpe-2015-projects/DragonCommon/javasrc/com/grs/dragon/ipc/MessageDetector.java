/**
 *  MessageDetector.java
 *
 *  ~~ Copyright 2002-2015 by Goldin-Rudahl Associates
 *  ~~ EndC
 *
 *  Created by Sally Goldin, 5/2/2001
 *  
 *  $Id: MessageDetector.java,v 1.6 2015/01/01 09:42:06 rudahl Exp $
 *  $Log: MessageDetector.java,v $
 *  Revision 1.6  2015/01/01 09:42:06  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.5  2007/07/30 09:12:18  goldin
 *  Get rid of unchecked warnings
 *
 *  Revision 1.4  2002/01/15 17:02:06  goldin
 *  Don't put a colon into complex err message if no arguments follow
 *
 *  Revision 1.3  2002/01/02 13:15:39  goldin
 *  Do substitution in complex err messages
 *
 *  Revision 1.2  2001/11/20 13:18:26  goldin
 *  eliminate creation of two IpcFiles
 *
 *  Revision 1.1  2001/11/19 20:30:32  goldin
 *  Move IPC classes to new package
 *
 *  Revision 1.21  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.20  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.19  2001/10/19 16:23:12  goldin
 *  Change signature of showTable method
 *
 *  Revision 1.18  2001/10/08 11:57:19  goldin
 *  Don't throw away blank msgs, but do not log them
 *
 *  Revision 1.17  2001/10/03 15:15:46  goldin
 *  Modify display to index some lines
 *
 *  Revision 1.16  2001/08/31 13:33:46  goldin
 *  Implement multiple table displays, ability to kill table displays via incoming command
 *
 *  Revision 1.15  2001/07/12 13:14:47  goldin
 *  Implement complex error message type
 *
 *  Revision 1.14  2001/06/28 14:05:45  goldin
 *  Continue work on table formatting
 *
 *  Revision 1.13  2001/06/27 15:17:47  goldin
 *  Fix CalcParser bugs, table formatting
 *
 *  Revision 1.12  2001/06/15 10:45:39  goldin
 *  Allow explicit select of which msgs should go into history
 *
 *  Revision 1.11  2001/06/11 10:24:39  goldin
 *  Save msg keys and dump at exit
 *
 *  Revision 1.10  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.9  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.8  2001/05/22 12:05:13  goldin
 *  Implement new SigFileValidator; make msgs show up in the history
 *
 *  Revision 1.7  2001/05/21 16:18:57  goldin
 *  Initial implementation of table type messages
 *
 *  Revision 1.6  2001/05/18 10:49:14  goldin
 *  Don't exit while there are still messages to be displayed
 *
 *  Revision 1.5  2001/05/11 19:06:00  goldin
 *  Change IPC file format; enhance & debug tracing
 *
 *  Revision 1.4  2001/05/07 14:54:40  goldin
 *  Initial implementation of logger
 *
 *  Revision 1.3  2001/05/02 15:11:41  goldin
 *  Implement message and progress IPC file processing
 *
 */

package com.grs.dragon.ipc;
import com.grs.gui.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;

/**
 * This class detects the appearance of a message file written by one of 
 * Dragon's other components. It processes the file and displays the message.
 * <p>
 * This class is now a general class that does not provide the
 * UI logging or history functionality.
 * The specialized subclass UiMessageDetector adds these capabilities.
 * <p>
 * Like the ProgressDetector class, and unlike the FileDetector
 * parent class, this class runs in an infinite loop; it does not
 * exit its run method when the first progress file is found.
 */
public class MessageDetector extends FileDetector 
    {
      /**
       * Attribute names for complex error type of message.
       */
    protected static final String ERRORCODE = "ErrorCode";
    protected static final String MSGKEY = "MsgKey";
    protected static final String MSGTEXT = "MsgText"; 
    protected static final String OPERATIONKEY = "OperationKey";
    protected static final String OPERATIONTEXT = "OperationText";
    protected static final String ARGUMENTKEY = "ArgumentKey";
    protected static final String ARGUMENTTEXT = "ArgumentText";

    /**
     * Hashtable to keep track of keys and messages used.
     */
    protected Hashtable<String,String> messageHash = null;

      /**
       * Local copies of MessageDisplay and ErrorDisplay, to
       * reduce # of method calls.
       */
    protected MessageDisplay messageDisplay = null;
    protected ErrorDisplay errorDisplay = null;


    public MessageDetector()
        {
        this.filePattern = "Msg*.$$$";
	this.directory = ApplicationManager.getTempPath();
        messageDisplay = ApplicationManager.getMessageDisplay();
	errorDisplay = ApplicationManager.getErrorDisplay();
        messageHash = new Hashtable<String,String>(200);
	start();
        }

    protected void executeFileAction(String filename)
             throws InterruptedException
        { 
	IpcFile currentMessageFile = new IpcFile(
					    filename,
					    ApplicationManager.getTimeOffset(),
					    false);
	while (!currentMessageFile.isComplete() &&
               !currentMessageFile.isError())
	    {
	    sleep(200);
	    currentMessageFile.retry();
	    }
        if (currentMessageFile.isError())
	    {
	    return;  // nothing we can do.
            }
        processMessageData(currentMessageFile);
        }

      /**
       * Factorization. Allows a subclass to use this
       * classes processing for some mesage types, without
       * having to create two IpcFiles.
       */
    protected void processMessageData(IpcFile currentMessageFile)
        {
        int code = currentMessageFile.getMsgCode();
	String msgText = currentMessageFile.getMsgText();
        String msgKey = currentMessageFile.getMsgKey();
        if (msgKey != null)
	    {
	    messageHash.put(msgKey, msgText);
	    }
	switch (code)
	    {
            case IpcFile.WARN_MSG_TYPE:
                messageDisplay.showWarning(TextKeys.WARNING,msgText);
	        break;
            case IpcFile.ERR_MSG_TYPE:    
                errorDisplay.showError(TextKeys.ERROR,msgText);
	        break;
            case IpcFile.INFORM_MSG_TYPE:
                int pos = msgText.indexOf("\n");
                if (pos >= 0)
	            messageDisplay.showMessage(null,msgText.substring(0,pos));
		else
	            messageDisplay.showMessage(null,msgText);
	        break;
            case IpcFile.SPT_MSG_TYPE:
	        break;    
            case IpcFile.TABLE_MSG_TYPE:
                break;
            case IpcFile.COMPLEX_ERR_TYPE:
                processErrorAttributes(currentMessageFile);
	        break;
	    }
	}

      /**
       * Factorization.
       */
    protected void reportError(Exception e, IpcFile msgFile)
        {
        errorDisplay.showError(TextKeys.ERROR,TextKeys.UNRECOGNIZEDIPCFILE,
			  msgFile.getFilename());
	}

    /**
     * Factorization. Compose and display a complex error message
     * based on information in the attributes Hashtable on the
     * msg file.
     */
    protected void processErrorAttributes(IpcFile msgFile)
        {
	int pos = 0;
	Hashtable<String,String> attributes = msgFile.getAttributes();
	StringBuffer msgBuffer = new StringBuffer(1024);
	I18NTextSource txtSource = ApplicationManager.getTextSource();
	if (attributes == null)
	    {
	    reportError(new Exception("Complex err message has no attributes"),
				      msgFile);
	    return;
	    }
	String msgKey = (String) attributes.get(MSGKEY);
	String msgText = (String) attributes.get(MSGTEXT);
	if (msgKey != null)
	    {
            msgText = txtSource.getI18NText(msgKey,msgText);     
            }
        if (msgText == null)
	    {
	    reportError(new Exception(
	      "Complex err message has neither MsgKey nor MsgText attributes"),
				      msgFile);
	    return;
	    }
	String errCode = (String) attributes.get(ERRORCODE);
	if (errCode != null)
	    {
	    msgBuffer.append(txtSource.getI18NText(TextKeys.ERROR,"Error"));
	    msgBuffer.append(" " + errCode + "\n");
	    }
        String opText = (String) attributes.get(OPERATIONTEXT);
	String opKey = (String) attributes.get(OPERATIONKEY);
        String argText = (String) attributes.get(ARGUMENTTEXT);
	String argKey = (String) attributes.get(ARGUMENTKEY);
	String argExplain = null;
	String opExplain = null;
	pos = msgText.indexOf("%");
	if ((pos >= 0) && (argText != null)) 
	    {
	    int pos1 = msgText.indexOf(" ", pos);
	    if (pos1 >= 0)
	        {
		msgBuffer.append(msgText.substring(0,pos) +
				 argText + " " + msgText.substring(pos1+1));
		}
	    else 
	        {
		msgBuffer.append(msgText.substring(0,pos) +
				 argText);
		}
	    }
	else 
	    {
	    msgBuffer.append(msgText);
	    if (argText != null)
	        msgBuffer.append(": " + argText);
	    }
	if (argKey != null)
            argExplain = txtSource.getI18NText(argKey,null);
	if (argExplain != null)
	    {
	    if (argText != null)
                 msgBuffer.append(" (");
	    else 
	         msgBuffer.append(" ");
	    msgBuffer.append(argExplain);
	    if (argText != null)
                 msgBuffer.append(")");
	   
	    }
	msgBuffer.append("\n");
        if ((opText != null) || (opKey != null))
	    {
            msgBuffer.append(txtSource.getI18NText(TextKeys.OPERATION,
						    "Operation") + 
			     ": ");
	    if (opText != null)
                 msgBuffer.append(opText);
	    if (opKey != null)
                 opExplain = txtSource.getI18NText(opKey,null);
	    if (opExplain != null)
	        {
		if (opText != null)
		    msgBuffer.append(" (");
		else 
		    msgBuffer.append(" ");
		msgBuffer.append(opExplain);
		if (opText != null)
		    msgBuffer.append(")");
		}
	    msgBuffer.append("\n");
	    }
	errorDisplay.showError(TextKeys.ERROR,msgBuffer.toString());
	}


    /**
     * Dump the contents of the message hash to a file.
     */
    public void dumpKeyedMessages(String filename)
        {
        try
	    {
	    FileWriter writer = new FileWriter(filename);
	    Enumeration keys = messageHash.keys();
	    while (keys.hasMoreElements())
	        {
                String theKey = (String) keys.nextElement();
                String theMsg = (String) messageHash.get(theKey);
		writer.write(theKey + "   " + theMsg);
                if (!theMsg.endsWith("\n"))
		    {
		    writer.write("\n");
		    }
	        }
	    writer.close();
	    }
	catch (IOException ioe)
	    {
	    return;
	    }
	}

    /**
     * This method loops, periodically examining the directory 
     * passed in to the constructor for a file that matches the 
     * pattern passed in the constructor.
     * When such a file appears in the directory, the method calls 
     * executeFileAction passing the relevant filename as an argument, 
     * and then returns to looping. 
     * <p>
     * If a file is already being processed, the method calls 
     * executeFileAction and returns to sleep; it does not look at
     * the directory for new Message files. If there is no current
     * Message file, then the run method checks the directory for
     * new files.
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
		if ((matchFiles != null) &&
		    (matchFiles.length > 0))
		     {
		     for (int i = 0; i < matchFiles.length; i++)	
		          executeFileAction(matchFiles[i].getAbsolutePath());
		     }
		}
            catch (InterruptedException ie)
	        {
		  // continue to loop 
		}
	    }
        }
    }
