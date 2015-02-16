/* ExecCmdCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: ExecCmdCallback.java,v 1.22 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ExecCmdCallback.java,v $
 * Revision 1.22  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.21  2002/10/25 21:43:58  goldin
 * Add a linefeed before filtered pspec
 *
 * Revision 1.20  2002/04/29 22:36:06  goldin
 * Fine tune error message delivery
 *
 * Revision 1.19  2002/04/17 00:53:49  goldin
 * Fix problem with dual error msg display when clicking on OK
 *
 * Revision 1.18  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.17  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.16  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.15  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.14  2001/05/28 16:36:26  goldin
 * Debugging QueryProcessor
 *
 * Revision 1.13  2001/05/14 11:46:39  goldin
 * Reformat legend/add position pspecs
 *
 * Revision 1.12  2001/05/08 10:14:56  goldin
 * Refine logging support
 *
 * Revision 1.11  2001/05/07 14:54:40  goldin
 * Initial implementation of logger
 *
 * Revision 1.10  2001/05/07 14:21:15  goldin
 * Modify focus lost to always call validator
 *
 * Revision 1.9  2001/05/04 15:36:36  goldin
 * Modify control of Ready state
 *
 * Revision 1.8  2001/04/27 11:29:00  goldin
 * Continue implementation of interprocess communication and command handling
 *
 * Revision 1.7  2001/04/26 15:45:32  goldin
 * Work on history display for command line and response panels
 *
 * Revision 1.6  2001/04/25 12:18:32  goldin
 * Fix bug wrt border redraw; set focus to first control
 *
 * Revision 1.5  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.4  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.3  2001/03/20 13:33:02  goldin
 * Disable all fields after OK
 *
 * Revision 1.2  2001/02/20 18:39:13  goldin
 * Add callback handling
 *
 * Revision 1.1  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import java.util.*;
import java.awt.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of executing the command associated with a response panel.
 *  If the panel is a popup, the callback sends the command substring
 *  back to the parent, rather than executing it.
 * @author  goldin*/
public class ExecCmdCallback implements Callback 
    {
    protected DragonUI mainApp = null;

      /** Primary method of a callback class. 
       *   In this case the field is a button
       *   on the response panel. The effect of the callback
       *   is to construct and execute the response panel command.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */

    public void executeCallback(DragonField field)
        {
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
	    return;
	parent.setValidatingAll(true);
	mainApp = DragonUI.currentApplication;
	DragonField badField = parent.checkFieldValidity();
	parent.setValidatingAll(false);
	if (badField != null)
	    {
	    Toolkit.getDefaultToolkit().beep();
	    badField.getValidator().displayLastError();
	    badField.createFocusRequestor(500);
	    return;
	    }
	badField = parent.checkRequiredFields();
	if (badField != null)
	    {
	    UiErrorDisplay errDisp = (UiErrorDisplay)
                    ApplicationManager.getErrorDisplay();
	    Toolkit.getDefaultToolkit().beep();
            errDisp.showError(null,TextKeys.MISSINGREQUIRED,
			      badField, parent);
	    badField.requestFocus();
	    return;
	    }
			       
	String command = filterContents(parent.constructCommand());
        if (command == null)
            return; 
	if (parent.isPopup())
	    {
	    parent.getInvokingField().setCallbackSubCommand(command);
	    JDialog dlg = parent.getPopupDialog();
	    dlg.setVisible(false);
	    }
	else
	    {
            CommandLine cmdLine = mainApp.getCommandLine(); 
	    // put command lines into the history list.
            command = command + " -.";
	    StringTokenizer tokenizer = new StringTokenizer(command,"\n");
            while (tokenizer.hasMoreTokens())
	         {
                 String token = tokenizer.nextToken();
		 cmdLine.addToHistory(token);
		 }
            cmdLine.getCmdLogger().logMessage(command, false);
	    mainApp.getCommandForwarder().sendCommandToServer(
				  CommandLine.CMDPROMPT + " " +
				  command);
            mainApp.refreshHistoryDisplay();
	    }
	}

      /**
       * Do any special-case processing on the command text before
       * sending it to the forwarder. Currently handles the following
       * special cases:
       *   ANN/ADD replaces two position parameters with a single one
       *   ANN/LEG  " "
       */
    protected String filterContents(String inputCmd)
        {
        int addIndex = inputCmd.indexOf("ANN ADD");
	int legIndex = inputCmd.indexOf("ANN LEG");
        if ((addIndex < 0) && (legIndex < 0))
   	    return inputCmd; // not a special case
        StringBuffer buildBuffer = new StringBuffer();
        if (addIndex >= 0)  // process add
	    {
            int linepos = inputCmd.indexOf("-TXPL");
            int pixpos = inputCmd.indexOf("-TXPP");
            if (((linepos < 0) && (pixpos >= 0)) ||
                ((linepos >= 0) && (pixpos < 0)))
	        {
		ApplicationManager.getErrorDisplay().showError(
						    TextKeys.ERROR,
						    TextKeys.NEEDBOTH,
						    null);
		return null;
		}
            if ((linepos < 0) && (pixpos < 0))
	        return inputCmd;  // nothing to replace
            // assume that the line comes before the pixel entry
	    buildBuffer.append(inputCmd.substring(0,linepos));
            buildBuffer.append("\n -TXP");
            int tmp = inputCmd.indexOf("\"",linepos+7);
	    buildBuffer.append(inputCmd.substring(linepos+5,tmp));
            int tmp2 = inputCmd.indexOf("\"",tmp+1);
            buildBuffer.append(" " + inputCmd.substring(tmp2+1));
	    }
	else if (legIndex >= 0)
	    {
            int linepos = inputCmd.indexOf("-LPL");
            int pixpos = inputCmd.indexOf("-LPP");
            if (((linepos < 0) && (pixpos >= 0)) ||
                ((linepos >= 0) && (pixpos < 0)))
	        {
		ApplicationManager.getErrorDisplay().showError(
						    TextKeys.ERROR,
						    TextKeys.NEEDBOTH,
						    null);
		return null;
		}
            if ((linepos < 0) && (pixpos < 0))
	        return inputCmd;  // nothing to replace
            // assume that the line comes before the pixel entry
	    buildBuffer.append(inputCmd.substring(0,linepos));
            buildBuffer.append("-LP");
            int tmp = inputCmd.indexOf("\"",linepos+6);
	    buildBuffer.append(inputCmd.substring(linepos+4,tmp));
            int tmp2 = inputCmd.indexOf("\"",tmp+1);
            buildBuffer.append(" " + inputCmd.substring(tmp2+1));
	    }
        return buildBuffer.toString();
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ExecCmdCallback.java,v 1.22 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of ExecCmdCallback.java

