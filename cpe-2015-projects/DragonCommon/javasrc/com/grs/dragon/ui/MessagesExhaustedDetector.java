/**
 *  MessagesExhaustedDetector.java
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *  Created by Sally Goldin, 5/18/2001
 *  
 *  $Id: MessagesExhaustedDetector.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: MessagesExhaustedDetector.java,v $
 *  Revision 1.5  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.4  2001/11/19 20:29:38  goldin
 *  Moved IPC classes to new package
 *
 *  Revision 1.3  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.2  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.1  2001/05/18 10:49:14  goldin
 *  Don't exit while there are still messages to be displayed
 *
 */

package com.grs.dragon.ui;
import java.io.*;

/**
 * This class detects the appearance of message files written by one of 
 * Dragon's other components. It does not do anything to the file,
 * merely monitors its existence. It exits when it has gone through
 * a fixed number sleep cycles without finding any new message files.
 * <p>
 * The class extends MessageDetector, because it is looking for the
 * same file, but it overrides run and executeFileAction.
 */
public class MessagesExhaustedDetector extends UiMessageDetector 
    {
    public static final int MAX_CYCLES = 5;
    protected int emptyCycles = 0;
    protected DragonUI mainUI = null;

    public MessagesExhaustedDetector(DragonUI mainUI)
        {
        super((DragonApp) mainUI);
	this.mainUI = mainUI;
        }

    protected void executeFileAction(String filename)
             throws InterruptedException
        { 
	  // Just reset the cycles counter and return.
	emptyCycles = 0;
	}

    /**
     * This method loops, periodically examining the directory 
     * passed in to the constructor for a file that matches the 
     * pattern passed in the constructor.
     * When such a file appears in the directory, the method calls 
     * executeFileAction passing the relevant filename as an argument, 
     * and then returns to looping. 
     * <p>
     * When it has gone through MAX_CYCLES sleep cycles without
     * finding any message files, it exits the run method.
     */
    public void run()
        {
        emptyCycles = 0;
        File dirFile = new File(directory);
        File[] matchFiles = null;
        while ((emptyCycles < MAX_CYCLES) || 
               (mainUI.isMessageDialogVisible() == true))
	    {
            try 
	        {
	        sleep(500);
		matchFiles = dirFile.listFiles(this);
		if ((matchFiles != null) &&
		    (matchFiles.length > 0))
		     {
		     for (int i = 0; i < matchFiles.length; i++)	
		          executeFileAction(matchFiles[i].getAbsolutePath());
		     }
                else
		     {
		     emptyCycles++;
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
        cvsInfo = "\n@(#)  $Id: MessagesExhaustedDetector.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
