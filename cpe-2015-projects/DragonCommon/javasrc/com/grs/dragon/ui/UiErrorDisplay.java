/**
 * UiErrorDisplay
 *
 * Copyright  2002-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 3/22/2001, renamed 10/16/2001
 *
 * $Id: UiErrorDisplay.java,v 1.15 2007/01/05 07:41:57 rudahl Exp $
 * $Log: UiErrorDisplay.java,v $
 * Revision 1.15  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.14  2005/12/05 10:38:46  goldin
 * Repack diaolog after changing font to avoid messages getting cut off
 *
 * Revision 1.13  2005/07/24 13:21:24  goldin
 * Set correct font in error dialogs
 *
 * Revision 1.13  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.12  2002/09/25 23:57:32  goldin
 * Remove debug msg
 *
 * Revision 1.11  2002/09/10 20:08:25  goldin
 * Shorten timeout
 *
 * Revision 1.10  2002/09/05 19:13:27  goldin
 * Get rid of infinite sleep loop
 *
 * Revision 1.9  2002/04/17 00:53:49  goldin
 * Fix problem with dual error msg display when clicking on OK
 *
 * Revision 1.8  2002/01/04 17:26:14  goldin
 * Don't display new error till last one is gone
 *
 * Revision 1.7  2002/01/02 13:14:28  goldin
 * Make error dialog modal
 *
 * Revision 1.6  2001/11/29 16:12:33  goldin
 * Add common pkg import
 *
 * Revision 1.5  2001/11/21 15:17:53  goldin
 * Make all references to getTimeOffset use ApplicationManager method
 *
 * Revision 1.4  2001/11/19 20:29:38  goldin
 * Moved IPC classes to new package
 *
 * Revision 1.3  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.2  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/17 10:27:59  goldin
 * Make ErrorDisplay an interface, create UI and generic versions
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import javax.swing.*;
import javax.swing.plaf.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/**
 * This class encapsulates the display of errors.
 * There is one instance of this class in the system, and it
 * reuses the same dialog for each error call.*/
public class UiErrorDisplay extends JOptionPane implements ErrorDisplay
    {
    public static final String ZEROS = "000000000000";
      /**
       * reference to the text source, for getting translated
       * messages. This is set in the constructor.*/
    protected I18NTextSource textSource = null;

      /**
       * Window upon which the dialogs should be centered.
       */
    protected DragonUI masterWindow = null;

      /**
       * Counter for creating message files.
       */
    protected static int msgSeq = 100; 

      /**
       * Make title available throughout the class to simplify
       * method calls.
       */
    protected String title = null;

      /**
       * Save the message for abnormal reporting.
       */
    protected String localMessage = null;

      /**
       * Constructor sets the text source and sets things up
       * for displaying the dialog.
       */
    public UiErrorDisplay(I18NTextSource textSource, DragonUI masterWindow)
        {
        super("Test message",JOptionPane.ERROR_MESSAGE,
	      JOptionPane.DEFAULT_OPTION);
        this.textSource = textSource;
        this.masterWindow = masterWindow;
	}
			
      /**
       * Display a particular error message.
       * @param titleKey  Key for title string (or null if no title)
       * @param msgKey Key for internationalized part of message
       * @param field  Field (if any) associated with the message
       * @param panel  Parent panel in which field resides.
       */
    public void showError(String titleKey, 
			  String msgKey,
			  DragonField field,
			  DragonPanel panel)
        {
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
        String msg = textSource.getI18NText(msgKey,"");
        if (field != null)
	     msg = msg + ": " + field.getLabelText();
	localMessage = msg;
        setMessage(msg);
        setValue(null);
	showDialog();
	}  

      /**
       * Display a particular error message with arbitrary added text.
       * @param titleKey Title string (or null if no title)
       * @param msgKey Key for internationalized part of message
       * @param addOn  Additional text to be added - not internationalized.
       */
    public void showError(String titleKey, 
			  String msgKey,
			  String addOn)
        {
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
        String msg = textSource.getI18NText(msgKey,"");
        if (addOn != null)
	     msg = msg + ": " + addOn;
	localMessage = msg;
        setMessage(msg);
        setValue(null);
	showDialog();
	}  

      /**
       * Display a prefetched and translated error message
       * @param titleKey Title string (or null if no title)
       * @param msgText Text for message message
       */
    public void showError(String titleKey, 
			  String msgText)
        {
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
	localMessage = msgText;
        setMessage(msgText);
        setValue(null);
	showDialog();
	}  

      /**
       * Create a message file holding the error message and
       * and wait for the message detector to pick it up.
       */
    public void sendError(String message)
        {
	String directory = masterWindow.getCfgProcessor().getKpath();
        if (!directory.endsWith(File.separator))
             directory = directory + File.separator;
        String filename = directory + 
	                  "MsgUI" + String.valueOf(msgSeq++) +
	                  ".$$$";
	long timestamp = (new Date().getTime() - 
                        ApplicationManager.getTimeOffset())/(long) 1000;
	String timeString = String.valueOf(timestamp);     
	StringBuffer contents = new StringBuffer();
        contents.append("( ");
	contents.append(ZEROS.substring(
                       0,12 - timeString.length()));
	contents.append(timeString + " 999 1 )\n");
	contents.append(message + "\n");
	int fileLen = contents.length();
	if (fileLen < 100)
	    fileLen -= 1;
	if (fileLen > 999)
	    fileLen += 1;
	contents = contents.replace(15,18,String.valueOf(fileLen));
	try
	    {
	    FileWriter writer = new FileWriter(filename);
	    writer.write(contents.toString());
	    writer.close();
	    }
        catch (IOException ioe)
	    {
	      // what can we possible do in the case of an error?
            System.out.println("Error writing error message file");
	    System.out.println("ORIGINAL ERROR: " + message);
	    }
        }
      /**
       * Factorization. Actually display dialog.
       */
    protected void showDialog()
        {
	long totalMilliseconds = 0;
	// only loop for a maximum of 5 seconds, then
	// log an erro and show the new message anyway
        while ((ApplicationManager.isMessageDialogVisible()) &&
	       (totalMilliseconds < 5000))
	    {
	    try {
	        //System.out.println("Dialog visible - about to sleep");
	        Thread.sleep(500);
		totalMilliseconds += 500; 
	        }
	    catch (InterruptedException ie)
	        {
		System.out.println("Sleep interrupted");
		}
            }
        if (totalMilliseconds >= 5000)
	    {
	    ApplicationManager.getErrorLogger().logError(
               "UIErrorDisplay: Too many retries to display error when another error is supposedly visible",true);
	    ApplicationManager.getErrorLogger().logError(
	       "Message displayed anyway: " + localMessage, false);
	    }
	ApplicationManager.setMessageDialogVisible(true);        
	JDialog dlg = createDialog(masterWindow,title);
	dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
        SwingUtilities.updateComponentTreeUI(dlg);
	dlg.setModal(true);
	dlg.pack();
	dlg.setVisible(true);
	Object val = getValue();
	dlg.setVisible(false);
	ApplicationManager.setMessageDialogVisible(false);
	masterWindow.repaint();
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UiErrorDisplay.java,v 1.15 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

