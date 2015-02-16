/**
 * MessageDisplay
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 5/2/2001
 *
 * $Id: MessageDisplay.java,v 1.5 2007/01/05 07:41:58 rudahl Exp $
 * $Log: MessageDisplay.java,v $
 * Revision 1.5  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/12/05 14:27:55  goldin
 * Set MessageDialogVisible flag when visible
 *
 * Revision 1.3  2001/12/03 18:04:34  goldin
 * MessageDisplay should  not be abstract
 *
 * Revision 1.2  2001/11/19 20:31:22  goldin
 * Add new ShowMessage method
 *
 * Revision 1.1  2001/11/16 17:29:21  goldin
 * Move DragonFileChooser and supporting classes to new general .gui package
 *
 * Revision 1.4  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/05/18 10:49:14  goldin
 * Don't exit while there are still messages to be displayed
 *
 * Revision 1.1  2001/05/02 15:11:41  goldin
 * Implement message and progress IPC file processing
 *
 */

package com.grs.gui;
import javax.swing.*;
import java.awt.*;

/**
 * This class encapsulates the display of non-error messages, 
 * either in a dialog or in the message area of the main window.
 * This is a generic base class which can be specialized for
 * use in the Dragon UI, used in its generic form
 * for other applications.
 */
public class MessageDisplay extends JOptionPane
    {
      /**
       * reference to the text source, for getting translated
       * messages. This is set in the constructor.*/
    protected I18NTextSource textSource = null;

      /**
       * Window upon which the dialogs should be centered.
       */
    protected Component masterWindow = null;

      /**
       * Make title available throughout the class to simplify
       * method calls.
       */
    protected String title = null;

      /**
       * Constructor sets the text source and sets things up
       * for displaying the dialog.
       */
    public MessageDisplay(I18NTextSource textSource, Component masterWindow)
        {
        super("Test message",JOptionPane.WARNING_MESSAGE,
	      JOptionPane.DEFAULT_OPTION);
        this.textSource = textSource;
        this.masterWindow = masterWindow;
	}
			
      /**
       * Display a particular warning message with arbitrary added text.
       * @param titleKey Title string (or null if no title)
       * @param msgKey Key for internationalized part of message
       * @param addOn  Additional text to be added - not internationalized.
       */
    public void showWarning(String titleKey, 
			  String msgKey,
			  String addOn)
        {
	setMessageType(JOptionPane.WARNING_MESSAGE);
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
        String msg = textSource.getI18NText(msgKey,"");
        if (addOn != null)
	     msg = msg + ": " + addOn;
        setMessage(msg);
        setValue(null);
        showDialog();
	}  

      /**
       * Display a prefetched and translated warning message
       * @param titleKey Title string (or null if no title)
       * @param msgText Text for message message
       */
    public void showWarning(String titleKey, 
			  String msgText)
        {
	setMessageType(JOptionPane.WARNING_MESSAGE);
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
        setMessage(msgText);
        setValue(null);
        showDialog();
	}  

      /**
       * Display a prefetched and translated informational message
       * @param titleKey Title string (or null if no title)
       * @param msgText Text for message message
       */
    public void showMessage(String titleKey, 
			  String msgText)
        {
	setMessageType(JOptionPane.PLAIN_MESSAGE);
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
        setMessage(msgText);
        setValue(null);
        showDialog();
	}  

      /**
       * Factorization. Actually display dialog.
       * 
       */
    protected void showDialog()
        {
	ApplicationManager.setMessageDialogVisible(true);
	JDialog dlg = createDialog(masterWindow,title);
        dlg.setVisible(true);
        Object val = getValue();
	dlg.setVisible(false);
	ApplicationManager.setMessageDialogVisible(false);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: MessageDisplay.java,v 1.5 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }

