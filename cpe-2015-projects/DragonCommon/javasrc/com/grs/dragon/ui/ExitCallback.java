/* ExitCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: ExitCallback.java,v 1.17 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ExitCallback.java,v $
 * Revision 1.17  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.16  2005/07/24 13:18:11  goldin
 * Set correct font in exit dialog
 *
 * Revision 1.16  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.15  2002/09/14 21:56:49  goldin
 * Make exitstring public
 *
 * Revision 1.14  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.13  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.12  2001/09/10 14:37:21  goldin
 * Implement state machine while script ins running.
 *
 * Revision 1.11  2001/06/27 10:50:37  goldin
 * Fix non-exit bug
 *
 * Revision 1.10  2001/06/19 10:40:07  goldin
 * Fix validation/focusloss loop bug
 *
 * Revision 1.9  2001/05/11 19:06:00  goldin
 * Change IPC file format; enhance & debug tracing
 *
 * Revision 1.8  2001/05/03 15:04:31  goldin
 * Add special file handling to command line and command forwarder
 *
 * Revision 1.7  2001/04/27 19:42:24  goldin
 * Initial implementation of class to handle commands coming into the UI
 *
 * Revision 1.6  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.5  2001/03/21 13:05:39  goldin
 * Add language selection and config file processing functionality
 *
 * Revision 1.4  2001/03/20 18:04:15  goldin
 * Implement tabbed panes, clean up menu help:
 *
 * Revision 1.3  2001/03/16 14:36:09  goldin
 * Add internationalization to exit dialog
 *
 * Revision 1.2  2001/03/14 16:38:49  goldin
 * Extracting exit code into callback
 *
 * Revision 1.1  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.plaf.*;

//********************************************************************
/** 
 *  This class implements the Callback interface. It has the effect
 *  of displaying an internationalized confirmation dialog, and if
 *  the user confirms, exiting DRAGON. It is invoked by the Exit menu
 *  item as well as in response to the user clicking the close button
 *  on the UI window.
 * @author  goldin*/
public class ExitCallback implements Callback 
    {
    protected JOptionPane confirmDialog = null;
    protected String yes;
    protected String no;
    protected CommandForwarder forwarder = null;
    public static final String EXITSTRING = "CMD>> EXIT";

      /**
       * Constructor retrieves messages for dialog from
       * the I18N text source, and creates the confirmation
       * dialog, which can then be reused.
       */
    public ExitCallback()
        {
	String message = 
            DragonUI.textSource.getI18NText(TextKeys.CONFIRMEXIT,"Really?");
	yes =
            DragonUI.textSource.getI18NText(TextKeys.YES,"Yes");
	no =
            DragonUI.textSource.getI18NText(TextKeys.NO,"No");
        forwarder = DragonUI.commandForwarder;
        Object[] options = new Object[2];
	options[0] = yes;
	options[1] = no;
        confirmDialog = new JOptionPane(message,JOptionPane.QUESTION_MESSAGE,
					JOptionPane.YES_NO_OPTION,null,
					options,options[0]);
 	}

      /** Primary method of a callback class.
       *  Puts up a confirmation dialog and exits if the user
       *   indicates that he or she does want to exit.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        DragonUI monitoredWindow = (DragonUI) field.getParentComponent();
        if (monitoredWindow.isExiting())
	    return;  // don't call command forwarder more than once
	String verb = field.getName();
	if ((monitoredWindow != null) && (!verb.equalsIgnoreCase("X")))
	    {
            confirmDialog.setValue(null);
	    confirmDialog.setInitialValue(yes);
	    JDialog dlg = confirmDialog.createDialog(monitoredWindow,null);
	    dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
	    SwingUtilities.updateComponentTreeUI(dlg);
	    monitoredWindow.setMessageDialogVisible(true);
            dlg.setVisible(true);
            Object val = confirmDialog.getValue();
	    monitoredWindow.setMessageDialogVisible(false);
            if (val instanceof String)
	        {
                String response = (String)val;
		if (response.equals(yes))
	            {
                    monitoredWindow.setExiting(true);
                    monitoredWindow.setReady(false);
		    boolean bOk = forwarder.sendCommandToServer(EXITSTRING);
	            }
   	        else
	            {
	            monitoredWindow.setVisible(true);
	            }
		}
            }
        else
	    {
            monitoredWindow.setExiting(true);
	    monitoredWindow.setReady(false);
	    boolean bOk = forwarder.sendCommandToServer(EXITSTRING);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ExitCallback.java,v 1.17 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of Callback.java

