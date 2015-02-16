/**
 * FileDetector
 *
 *  ~~ Copyright 2001-2015 by Sally Goldin & Kurt Rudahl
 *  ~~ EndC
 *
 *  Created by Sally Goldin, 4/14/2001
 *  
 *  $Id: FileDetector.java,v 1.6 2015/01/01 09:42:06 rudahl Exp $
 *  $Log: FileDetector.java,v $
 *  Revision 1.6  2015/01/01 09:42:06  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.5  2006/01/20 07:49:08  goldin
 *  Add stack trace if error
 *
 *  Revision 1.4  2005/08/12 09:24:55  goldin
 *  Fix null ptr exception
 *
 *  Revision 1.3  2005/02/06 08:35:00  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.2  2002/01/25 11:10:27  goldin
 *  Add a try/catch block around the run method
 *
 *  Revision 1.1  2001/11/19 20:30:32  goldin
 *  Move IPC classes to new package
 *
 *  Revision 1.8  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.7  2001/10/03 15:15:46  goldin
 *  Shorten sleep period
 *
 *  Revision 1.6  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.5  2001/05/02 11:14:41  goldin
 *  Implement IncomingCommandProcessor functionality
 *
 *  Revision 1.4  2001/04/27 11:29:00  goldin
 *  Continue implementation of interprocess communication and command handling
 *
 *  Revision 1.3  2001/04/24 14:14:01  goldin
 *  Initial implementation
 *
 *  Revision 1.2  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 */

package com.grs.dragon.ipc;
import com.grs.gui.*;
import javax.swing.*;
import java.io.*;

/**
 * This abstract class provides functionality to look for a file that matches
 * a particular pattern, in a particular directory. When a matching
 * file appears, the class instance calls its executeFileAction method,
 * which will be overridden by each subclass to provide class-specific 
 * behavior.
 */
public abstract class FileDetector extends Thread
    	                  implements FileFilter
    {
    protected static final int SLEEP_MS = 200;

      /**
       * Hold onto the filename and directory that we are looking for
       */
    protected String filePattern;
    protected String directory;

    /**
     * Constructor 
     */
    public void FileDetector(String filePattern, String directory)
        {
        this.filePattern = filePattern;
	this.directory = directory;
	start();
        }

    /**
     * This method is called when the file we are trying to detect appears
     * in the monitored directory. The method should be overridden with
     * a class-specific version in each sub-class. 
     */
    protected abstract void executeFileAction(String filename)
              throws InterruptedException;

    /**
     * This method loops, periodically examining the directory 
     * passed in to the constructor for a file that matches the 
     * pattern passed in the constructor.
     * When such a file appears in the directory, the method calls 
     * executeFileAction passing the relevant filename as an argument, 
     * and then exits the loop. 
     */
    public void run()
        {
	try 
	    {
	    File dirFile = new File(directory);
	    File[] matchFiles = null;
	    boolean bFoundFile = false;
	    while (!bFoundFile)
	        { 
		try 
	            {
		    sleep(SLEEP_MS);
		    matchFiles = dirFile.listFiles(this);
		    // if we find matches, process them
		    if ((matchFiles != null) &&
			(matchFiles.length > 0))
		          {
			  bFoundFile = true;
			  for (int i = 0; i < matchFiles.length; i++)
			      {
			      executeFileAction(matchFiles[i].getAbsolutePath());
			      }
			  }
		     }
		catch (InterruptedException ie)
		     {
		     break; 
		     }
		}
	    }
	catch (Exception e)
	    {
	    String message = null;
            e.printStackTrace();
            if (ApplicationManager.getTextSource() != null)
	        {
		message = ApplicationManager.getTextSource().getI18NText(
				"%h9480.0",
				"Unexpected internal error in DRAGON menu client; see DRAGERR.LOG for details.");
		}
	    else
	        {
		message = "Unexpected internal error in DRAGON menu client; see DRAGERR.LOG for details.";
		}
	    JOptionPane.showMessageDialog(new JFrame(),message,"  ",
					  JOptionPane.ERROR_MESSAGE);
	    ApplicationManager.getErrorLogger().logError(message,true);
	    if (e.getMessage() != null)
  	        ApplicationManager.getErrorLogger().logError(e.getMessage(),true);
	    }
        }


      /**
       * Primary method from the FileFilter interface. Returns true
       * if the passed File matches the pattern set up when the
       * FileDetector was constructed. The pattern may use a single
       * asterisk wildcard for any portion of the file name or
       * extension.
       * @param testFile file to be evaluated for acceptance.
       * @return true if file matches pattern, else false.
       */
    public boolean accept(File testFile)
        {
	boolean bMatch = true;
        String compareFile = testFile.getName();
        int pos = filePattern.indexOf("*");
        if (pos < 0)   // no wildcard
	    {
	    bMatch = filePattern.equalsIgnoreCase(compareFile);
	    }
        else
	    {
            int i;
            int j;
            char[] patternchars = filePattern.toUpperCase().toCharArray();
	    char[] comparechars = compareFile.toUpperCase().toCharArray();
            int len = patternchars.length;
            int comparelen = comparechars.length;
            for (i = 0; (i < pos) && (bMatch); i++)
	         {
                 if (patternchars[i] != comparechars[i])
                     bMatch = false;  
		 }
            // find start of matching region (if any) beyond wildcard
            if ((bMatch) && (pos < len - 1))
	         {
                 for (j = pos; j < comparelen; j++)
		      {
                      if (comparechars[j] == patternchars[pos+1])
                          break;
                      }
                 if (j == comparelen)  // no match
		      {
		      bMatch = false;
		      }
                 else 
		      {
                      for (i = pos+1; 
                           (i < len) && (j < comparelen) && (bMatch); 
                           i++, j++)
		          {      
			  if (patternchars[i] != comparechars[j])
			      bMatch = false;
			  }
		      // make sure both strings were consumed
		      if ((i < len) || (j < comparelen))
                          bMatch = false;
		      }
		 }
	    }
        return bMatch;
	}
    }


