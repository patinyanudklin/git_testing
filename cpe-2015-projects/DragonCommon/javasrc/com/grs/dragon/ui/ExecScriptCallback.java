/* ExecScriptCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 4/9/2001
 *
 * $Id: ExecScriptCallback.java,v 1.12 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ExecScriptCallback.java,v $
 * Revision 1.12  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.11  2006/12/31 09:24:44  goldin
 * update the DragonFileChooser constructor with new arg
 *
 * Revision 1.10  2002/08/27 20:04:01  goldin
 * convert filechooser to potentially using multiple file types
 *
 * Revision 1.9  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.8  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.7  2001/09/10 14:37:21  goldin
 * Implement state machine while script ins running.
 *
 * Revision 1.6  2001/09/05 10:45:54  goldin
 * Add facility for command line 'RUN' to turn on control panel
 *
 * Revision 1.5  2001/09/04 15:08:50  goldin
 * Begin implementing script control panel
 *
 * Revision 1.4  2001/08/20 10:13:28  goldin
 * Swap message and file types for RUN versus LOG
 *
 * Revision 1.3  2001/05/08 10:14:56  goldin
 * Refine logging support
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/04/09 11:17:07  goldin
 * Add facility to run scripts
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  operation of the RUN menu item. Basically, it puts up a file box
 *  to prompt for a script name. If the user enters a script, then
 *  the callback asks Dragon to run it.
*/
public class ExecScriptCallback implements Callback 
    {
      /**
       * Name of last selected script file.
       */
    protected String lastScriptFileName = null;

      /**
       * File chooser box - set up specifically for this
       * callback.*/
    protected DragonFileChooser scriptFileChooser = null;

      /**
       * File chooser title. Only retrieve it once.
       */
    protected String chooserTitle = null;

      /**    
       * Filetypes to allow
       */
  protected DFileType[] filetypes = {DFileType.SCRIPT2};

      /**
       * Constructor retrieves the chooser title. Don't
       * construct the file chooser until the first call to use
       * it; when the callback constructor is called, the parent
       * frame does not yet exist!!
       */
    public ExecScriptCallback()
        {
	chooserTitle = DragonUI.textSource.getI18NText(TextKeys.SPTFILE,
						       "SCRIPT FILE TO RUN");
	}

     /** Primary method of a callback class.
       *  Puts up a box to allow 
       *  the user to choose a script file name to run. Then,
       *  if the user clicks on OK, asks Dragon to execute the script.
       * @param  field Field whose value will determine the
       *   effects of the callback. Dummy, in this case.
       */
    public void executeCallback(DragonField field)
        {
        File scriptFile = null;
        lastScriptFileName = field.getLabelText();
        if (lastScriptFileName != null)  // see if this is a file
	                                 // put there by cmd line
	    {
            scriptFile = new File(lastScriptFileName);
            if (!scriptFile.exists())
	         {
                 scriptFile = null;
		 lastScriptFileName = null;
		 }
            }
        if (scriptFile == null)
	    {
	    if (scriptFileChooser == null)
	        {
                scriptFileChooser = new DragonFileChooser(
					       DragonUI.currentApplication,
					       DragonUI.textSource,
					       false, true, false);
	        }
	    scriptFile = scriptFileChooser.chooseFile(filetypes,
						     null,
						     null,
						     chooserTitle,
						     lastScriptFileName);
  	    lastScriptFileName = null;
	    if (scriptFile != null)
	        {
	        lastScriptFileName = scriptFile.getAbsolutePath();
                }
            }
        if (lastScriptFileName != null)
	    {
	    DragonUI mainApp = DragonUI.currentApplication;
            CommandLine cmdLine = mainApp.getCommandLine(); 
	    // put command lines into the history list.
            String command = "RUN "+ lastScriptFileName;
	    cmdLine.addToHistory(command);
            cmdLine.getCmdLogger().logMessage(command, true);
	    mainApp.getCommandForwarder().sendCommandToServer(
				  CommandLine.CMDPROMPT + " " +
				  command);
            mainApp.refreshHistoryDisplay();
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ExecScriptCallback.java,v 1.12 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of ExecScriptCallback.java


