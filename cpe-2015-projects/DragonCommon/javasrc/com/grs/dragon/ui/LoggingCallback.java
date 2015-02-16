/* LoggingCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 4/9/2001
 *
 * $Id: LoggingCallback.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $
 * $Log: LoggingCallback.java,v $
 * Revision 1.9  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.8  2006/12/31 09:24:44  goldin
 * update the DragonFileChooser constructor with new arg
 *
 * Revision 1.7  2002/08/27 20:04:01  goldin
 * convert filechooser to potentially using multiple file types
 *
 * Revision 1.6  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.5  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.4  2001/08/20 10:13:28  goldin
 * Swap message and file types for RUN versus LOG
 *
 * Revision 1.3  2001/05/07 14:21:15  goldin
 * Modify focus lost to always call validator
 *
 * Revision 1.2  2001/05/03 15:04:31  goldin
 * Add special file handling to command line and command forwarder
 *
 * Revision 1.1  2001/04/17 13:42:35  rudahl
 * initial deposit, from tower h:\tmp\dragon\drag54\dragon_ui
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  operation of the LOG menu item.
 *  If logging is not currently enabled, the callback puts up
 *  a file selection box and allows the user to choose a log file
 *  name. Then it tells the Dragon server to log all commands.
 *  If logging is currently enabled, the callback simply
 *  tells Dragon to turn it off.
 * <p>
 *  This class has also been adapted to handle the special command
 *  line commands, LOG and LOG OFF. It determines which situation
 *  it has been called in based on the ID of the field passed to
 *  executeCallback.
 */
public class LoggingCallback implements Callback 
    {
      

      /**
       * File chooser box - set up specifically for this
       * callback.
       */
    protected DragonFileChooser logFileChooser = null;

      /**
       * File chooser title. Only retrieve it once.
       */
    protected String chooserTitle = null;


      /**    
       * Filetypes to allow
       */
  protected DFileType[] filetypes = {DFileType.LOG, DFileType.SCRIPT};

      /**
       * Constructor retrieves the chooser title. Don't
       * construct the file chooser until the first call to use
       * it; when the callback constructor is called, the parent
       * frame does not yet exist!!
       */
    public LoggingCallback()
        {
	chooserTitle = DragonUI.textSource.getI18NText(TextKeys.LOGFILE,
						       "FILE FOR LOGGING");
	}

     /** Primary method of a callback class.
       *  Depending on state of bLogging, may put up a box for
       *  the user to choose a log file name. Then
       *  sends a command to Dragon to turn logging on or off.
       * @param  field Field whose value will determine the
       *   effects of the callback. Dummy, in this case.
       */
    public void executeCallback(DragonField field)
        {
	DragonUI mainApp = (DragonUI) field.getParentComponent();
        String fieldID = field.getName();
        if (logFileChooser == null)
	    {
            logFileChooser = new DragonFileChooser(DragonUI.currentApplication,
					       DragonUI.textSource,
					       false, false, false);
	    }
	if (fieldID.equalsIgnoreCase("LOG"))
	    {
            handleSpecialCommand(field,mainApp);
	    }
	else if (mainApp.isLogging())
	    {
	    mainApp.setLogging(false); // turn off
	    }
	else
	    {
            String lastLogFileName = mainApp.getLogFile();
	    File logFile = logFileChooser.chooseFile(filetypes,
						     null,
						     null,
						     chooserTitle,
						     lastLogFileName);
	    lastLogFileName = null;
	    if (logFile != null)
	        {
		lastLogFileName = logFile.getAbsolutePath();
	  	}
	    if (lastLogFileName == null)  
	        {
		ErrorDisplay errDisplay = 
		  DragonUI.currentApplication.getErrorDisplay();
		errDisplay.showError(TextKeys.WARNING,
				     TextKeys.LOGFILEREQUIRED,
				      "");
		setLogMenuItemState(field,false);
	        }
	    else 
	        {
		mainApp.setLogging(true);
		mainApp.setLogFile(lastLogFileName);
		}
	    }
        // logging will simply check the system-wide flag
	}

      /**
       * Factorization. Handle special commands differently -
       * in that case we need to get the argument associated
       * with the command, which will be stored in the DragonField.
       */
    protected void handleSpecialCommand(DragonField field,
					DragonUI mainApp)
        {
	String argument = field.getLabelText();
	if (argument.equalsIgnoreCase("OFF"))
	     {
	     mainApp.setLogging(false);
	     setLogMenuItemState(field,false);
	     }
	else
	     {
	     mainApp.setLogging(true);
	     mainApp.setLogFile(argument);
	     setLogMenuItemState(field,true);
	     }
	}

      /**
       * Factorization. Turns on or off the log menu item to allow
       * synchronization between the command line and menus
       */
    protected void setLogMenuItemState(DragonField field,
				       boolean state)
        {
	// get the menu item based on its name
        DragonUI app = (DragonUI) field.getParentComponent();
	String menuID = "mF/SPT/LOG";
        DCheckMenuItem menuItem = 
	  (DCheckMenuItem) app.getMenuItem(app.getJMenuBar(),menuID);
	menuItem.setState(state);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: LoggingCallback.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of LoggingCallback.java



