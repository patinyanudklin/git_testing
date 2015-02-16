/**
 * ProgressDetector.java
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *  Created by Sally Goldin, 5/2/2001
 *  
 *  $Id: ProgressDetector.java,v 1.12 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ProgressDetector.java,v $
 *  Revision 1.12  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.11  2001/11/21 15:17:53  goldin
 *  Make all references to getTimeOffset use ApplicationManager method
 *
 *  Revision 1.10  2001/11/19 20:29:38  goldin
 *  Moved IPC classes to new package
 *
 *  Revision 1.9  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.8  2001/08/31 14:01:03  goldin
 *  Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 *  Revision 1.7  2001/06/26 18:54:41  goldin
 *  Allow progress detector to reset retry count so we don't time out with slow progress
 *
 *  Revision 1.6  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.5  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.4  2001/05/11 19:06:00  goldin
 *  Change IPC file format; enhance & debug tracing
 *
 *  Revision 1.3  2001/05/02 15:11:41  goldin
 *  Implement message and progress IPC file processing
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.ipc.*;
import java.io.*;
import java.util.*;

/**
 * This class looks for instances of a progress file in the appropriate 
 * directory.
 * <p>
 * When one appears, the class instance parses the file and then creates
 * a progress bar to display the progress information. 
 * As the percent complete changes, this class calls the updateProgress
 * method on the progress bar dialog.
 * <p>
 * When the percentComplete reaches 100, the class dismisses the progress bar
 * dialog and goes back to looking for a new progress file.
 * <p>
 * Like the IncomingCommandProcessor class, and unlike the FileDetector
 * parent class, this class runs in an infinite loop; it does not
 * exit its run method when the first progress file is found.
 */
public class ProgressDetector extends FileDetector 
    {
    protected ProgressBar progressBar = null;
    protected IpcFile currentProgressFile = null;

    /**
     * Reference to main application.
     */
    protected DragonApp mainApp = null;

    public ProgressDetector(DragonUI mainApp)
        {
	this.mainApp = mainApp;
        this.filePattern = "Pro*.$$$";
	this.directory = mainApp.getTempPath();
        progressBar = new ProgressBar(mainApp);
	start();
        }

    protected void executeFileAction(String filename)
             throws InterruptedException
        { 
        // case 1: a new progress file has been detected
        if (filename != null)
	    {
	    currentProgressFile = new IpcFile(filename,
					   ApplicationManager.getTimeOffset(),
					   true);
	    while (!currentProgressFile.isComplete() &&
                   !currentProgressFile.isError())
	        {
                sleep(200);
	        currentProgressFile.retry();
	        }
            if (currentProgressFile.isError())
                return;
	    // set the value and message and display the progress bar
	    progressBar.setMessage(currentProgressFile.getMsgText());
	    progressBar.setValue(currentProgressFile.getPercentDone());
	    progressBar.setVisible(true);
            progressBar.setSourceModule(currentProgressFile.getSourceModule());
	    }
	// case 2: we have a progress file; check if it's done, update
	// progress if relevant.
	else
	    {
	    if (currentProgressFile.fileConsumed())  // we're done
	         {
                 progressBar.setVisible(false);
		 currentProgressFile = null;
		 }
	    else
	         {
                 currentProgressFile.setRetryCount(0);
		 currentProgressFile.retry();  // reread file
		 int value = currentProgressFile.getPercentDone();
		 if (value > progressBar.getValue())
                      progressBar.setValue(value);
		 }
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
     * the directory for new progress files. If there is no current
     * progress file, then the run method checks the directory for
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
                if (currentProgressFile != null)
		    {
		    executeFileAction(null);
		    }
		else
		    {
		    // We assume only one progress file at a time. 
		    matchFiles = dirFile.listFiles(this);
		    // if we find matches, process them
		    if ((matchFiles != null) &&
			(matchFiles.length > 0))
		        {
			executeFileAction(matchFiles[0].getAbsolutePath());
			}
		    }
		}
            catch (InterruptedException ie)
	        {
		  // continue to loop 
		}
	    }
        }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ProgressDetector.java,v 1.12 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
