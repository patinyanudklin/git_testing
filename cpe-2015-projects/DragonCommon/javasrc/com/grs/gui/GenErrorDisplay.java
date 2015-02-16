/**
 * GenErrorDisplay
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 3/22/2001, renamed 10/16/2001
 *
 * $Id: GenErrorDisplay.java,v 1.4 2007/01/05 07:41:58 rudahl Exp $
 * $Log: GenErrorDisplay.java,v $
 * Revision 1.4  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.3  2005/07/24 13:29:45  goldin
 * Don
 *
 * Revision 1.3  2005/07/22 07:33:33  goldin
 * Don't explicitly make dialog disappear
 *
 * Revision 1.2  2001/12/05 14:27:55  goldin
 * Set MessageDialogVisible flag when visible
 *
 * Revision 1.1  2001/11/16 16:38:20  goldin
 * Move non-Dragon-specific files to new package
 *
 * Revision 1.2  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/17 10:27:59  goldin
 * Make ErrorDisplay an interface, create UI and generic versions
 *
 *
 */

package com.grs.gui;
import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/**
 * This class encapsulates the display of errors.
 * This is a version that does not depend on DragonUI-specific
 * classes. It is used to allow the DragonFileChooser to be
 * used outside the UI. It basically provides a subset of the
 * functionality in UiErrorDisplay.
 */
public class GenErrorDisplay extends JOptionPane implements ErrorDisplay
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
    public GenErrorDisplay(I18NTextSource textSource, Component masterWindow)
        {
        super("Test message",JOptionPane.ERROR_MESSAGE,
	      JOptionPane.DEFAULT_OPTION);
        this.textSource = textSource;
        this.masterWindow = masterWindow;
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
        setMessage(msg);
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
	//System.out.println("GenErrorDisplay showError " + msgText);
	if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,"");
	     }
        setMessage(msgText);
	showDialog();
	}  

      /**
       * Factorization. Actually display dialog.
       */
    protected void showDialog()
        {
	ApplicationManager.setMessageDialogVisible(true);
	JDialog dlg = createDialog(masterWindow,title);
        dlg.setVisible(true);
        setValue(null);
        Object val = getValue();
	//dlg.setVisible(false);
	ApplicationManager.setMessageDialogVisible(false);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: GenErrorDisplay.java,v 1.4 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }

