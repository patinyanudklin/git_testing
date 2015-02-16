/**
 *  UiMessageDetector.java
 *
 *  Copyright  2002-2007  by Goldin-Rudahl Associates
 *  Created by Sally Goldin, 11/19/2001
 *  
 *  $Id: UiMessageDetector.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: UiMessageDetector.java,v $
 *  Revision 1.7  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.6  2002/05/07 17:58:43  goldin
 *  Improve echo functionality in scripts
 *
 *  Revision 1.5  2002/01/10 14:55:53  goldin
 *  Enhance error reporting
 *
 *  Revision 1.4  2002/01/02 13:14:52  goldin
 *  Do substitution in complex err messages
 *
 *  Revision 1.3  2001/11/21 10:23:36  goldin
 *  Show only first line of an informational message
 *
 *  Revision 1.2  2001/11/20 13:18:46  goldin
 *  eliminate creation of two IpcFiles
 *
 *  Revision 1.1  2001/11/20 11:53:43  goldin
 *  Add msg detector specialized for the UI
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.ipc.*;
import java.io.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;

/**
 * This class is a simple subclass of the generic MessageDetector
 * which includes some functionality specific to the Dragon UI. In 
 * particular, it handles log and history functionality, and the creation
 * of a table display type of message.
 * <p>
 * Like the ProgressDetector class, and unlike the FileDetector
 * parent class, this class runs in an infinite loop; it does not
 * exit its run method when the first progress file is found.
 */
public class UiMessageDetector extends MessageDetector 
    {
    /**
     * Reference to main application.
     */
    protected DragonApp mainApp = null;

    public UiMessageDetector(DragonApp mainApp)
        {
        super();
	this.mainApp = mainApp;
        }

    protected void executeFileAction(String filename)
             throws InterruptedException
        { 
	int pos = 0;
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
        int code = currentMessageFile.getMsgCode();
	String msgText = currentMessageFile.getMsgText();
	String msgKey = currentMessageFile.getMsgKey();
	if ((currentMessageFile.isLogMessage()) && 
	    (!currentMessageFile.isMessageBlank()))
            {
            mainApp.logMessage(msgText, true);
	    mainApp.addToHistory(msgText,true);
	    }
        if ((code != IpcFile.SPT_MSG_TYPE) &&
            (code != IpcFile.TABLE_MSG_TYPE) &&
            (code != IpcFile.INFORM_MSG_TYPE))
	    {
            super.processMessageData(currentMessageFile);
	    }
        else
	    {
	    if (msgKey != null)
	        {
	        messageHash.put(msgKey, msgText);
	        }
	    if (code == IpcFile.SPT_MSG_TYPE)
	        {
		pos = msgText.indexOf("\n");
                if (pos >= 0)
	            mainApp.addToHistory(msgText.substring(0,pos),true);
		else
		    mainApp.addToHistory(msgText,true);
	        }
            else if (code == IpcFile.INFORM_MSG_TYPE)
	        {
                pos = msgText.indexOf("\n");
                if (pos >= 0)
	            mainApp.showMessage(msgText.substring(0,pos));
		else
	            mainApp.showMessage(msgText);
		}
            else
	        {
                try
		    {
                    int p = filename.indexOf(".$$$");
                    String tableId = filename.substring(p-8,p);
                    CalcResultParser parser = new CalcResultParser(
                           msgText,mainApp.getTextSource());
                    Reader xmlReader = parser.getXmlReader();
                    parser.parse(xmlReader);
                    boolean bOk = false;
		    while (!bOk)
                        {
                        sleep(500);
                        bOk = mainApp.showTable(
			           parser.getTableTitle(),
				   parser.getParsedContent(),
				   tableId);
			}
		    }
		catch (Exception e)
		    {
		    reportError(e,currentMessageFile);
		    }
		}
	    }
        // schedule a history update. We get a null ptr error from
	// Swing if we do it immediately
	javax.swing.Timer timer = new javax.swing.Timer(250,
					  new HistoryRefresher(mainApp));
	timer.setRepeats(false);
	timer.start();
	}

      /**
       * Factorization - override superclass method to provide
       * logging
       */
    protected void reportError(Exception e, IpcFile msgFile)
        {
        mainApp.logError(e.getClass().getName(),true);
        mainApp.logError(e.getMessage(),false);
        mainApp.logError(msgFile.getMsgText(), false);	    
	mainApp.showError(TextKeys.UNRECOGNIZEDIPCFILE,
			  msgFile.getFilename());
	}

      //*****************************************************
      /** 
       * Inner class used to issue a delayed request to
       * refresh the history list*/
    class HistoryRefresher implements ActionListener
         {
         protected DragonApp mainApplication = null;

	 public HistoryRefresher(DragonApp main)
             {
	     mainApplication = main;
	     }

	 /**
	  * Action Listener method
	  */
	 public void actionPerformed(ActionEvent e)
             {
	     mainApplication.refreshHistoryDisplay();
	     }
         }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UiMessageDetector.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
