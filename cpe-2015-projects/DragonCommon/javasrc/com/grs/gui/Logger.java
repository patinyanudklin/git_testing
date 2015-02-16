/**
 *  Logger
 *
 *  Copyright  2002-2007  by Sally Goldin and Kurt Rudahl
 *
 *  Created 5/7/2001 by Sally Goldin
 *
 *   $Id: Logger.java,v 1.5 2007/01/05 07:41:58 rudahl Exp $
 *   $Log: Logger.java,v $
 *   Revision 1.5  2007/01/05 07:41:58  rudahl
 *   added Whatis info
 *
 *   Revision 1.4  2005/02/06 08:08:11  goldin
 *   Fix JavaDoc warnings
 *
 *   Revision 1.3  2002/02/15 23:22:24  goldin
 *   Fix handling of newlines so we get all lines of a multiple line command
 *
 *   Revision 1.2  2002/01/02 13:16:42  goldin
 *   Remove extraneous newlines in logging comments
 *
 *   Revision 1.1  2001/11/16 16:38:20  goldin
 *   Move non-Dragon-specific files to new package
 *
 *   Revision 1.5  2001/11/05 13:59:16  goldin
 *   Put UI code in a package
 *
 *   Revision 1.4  2001/10/17 10:29:37  goldin
 *   Modify to use ApplicationManager to get error display, etc.
 *
 *   Revision 1.3  2001/05/18 18:20:04  goldin
 *   Added keyed message handling, retry timeout
 *
 *   Revision 1.2  2001/05/18 12:05:41  goldin
 *   Add error logging functionality to Logger class, implement in IpcFile
 *
 *   Revision 1.1  2001/05/07 14:54:40  goldin
 *   Initial implementation of logger
 *
 */

package com.grs.gui;
import java.io.*;
import java.util.*;

/**
 * This class implements logging, that is, sending Dragon commands
 * to a log file. The same class (a different instance) is used for 
 * error logging.
 * <p> 
 * For command logging, the name of the file and whether logging is on
 * or off is maintained by the main application. 
 * There is a singleton logger, which is created by and referenced by the
 *  CommandLine object. This is convenient because the history 
 * (which has similar logic to the logger) is maintained by the 
 * CommandLine object.
 * <p> 
 * For error logging, the filename is passed in the constructor.
 * Error logging is always "on".
 * <p>
 * Different methods are called to log a command as opposed to an
 * error report.
 */
public class Logger 
    {
    protected static final String delimiter = 
    "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n";

    protected static final String timePrefix = "Error report at ";
      
      /**
       * Log file name. Initialized at start for error logger,
       * otherwise gotten from the ui.
       */
    protected String logFileName = null;

      /**
       * Constructor for command logger
       */
    public Logger()
       {
       logFileName = ApplicationManager.getLogFileName();
       }

      /**
       * Constructor used for error logger.
       */
    public Logger(String logFileName)
        {
        this.logFileName = logFileName;
        File oldFile = new File(logFileName);
	if (oldFile.exists())
            oldFile.delete();
	}

      /**
       * Primary method for logging commands, 
       * adds one or more lines of text to the log.
       * If bComment is true, encloses them in parens.
       */
    public void logMessage(String messageText,
			   boolean bComment)
        {
	if (!ApplicationManager.isLogging())
	    return;
	logFileName = ApplicationManager.getLogFileName();
	try
	    {
	    boolean bFirst = true;
	    FileWriter writer = new FileWriter(logFileName,true);
	    // append to any previous contents.
	    // write each line separately
	    if (bComment)
	        writer.write("( ");
            StringTokenizer tokenizer = new StringTokenizer(messageText,
							    "\n\r");
	    while (tokenizer.hasMoreTokens())
	        {
		if (!bFirst) 
		    writer.write("\n");
		String msgLine = tokenizer.nextToken();
		writer.write(msgLine);
		bFirst = false;
		}
	    if (bComment)
	        writer.write(" )");
	    writer.write("\n");
	    writer.close();
	    }
	catch (IOException ioe)
	    {
	    ApplicationManager.getErrorDisplay().showError(TextKeys.ERROR,
						   TextKeys.LOGFILEERROR,
						   logFileName);
	    }
        }
      /**
       * Primary method for logging an error.
       * If "bNew" is true, delimits errors with lines of plus signs
       * and adds a time stamp with each error report.
       */
    public void logError(String errorText,
			 boolean bNew)
        {
	try
	    {
	    BufferedWriter writer = new BufferedWriter( 
                                     new FileWriter(logFileName,true));
	    // append to any previous contents.
	    if (bNew)
	        {
	        writer.write(delimiter);
		writer.write(timePrefix);
		writer.write(new Date().toString()+ "\n");
		}
	    writer.write(errorText);
	    writer.write("\n");
	    writer.close();
	    }
	catch (IOException ioe)
	    {
	    ApplicationManager.getErrorDisplay().showError(TextKeys.ERROR,
						   TextKeys.LOGFILEERROR,
						   logFileName);
	    }
        }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: Logger.java,v 1.5 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }







