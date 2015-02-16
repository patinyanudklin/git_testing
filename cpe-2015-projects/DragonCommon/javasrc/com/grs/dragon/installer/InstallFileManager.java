/**
 * InstallFileManager
 *
 *  ~~ Copyright 2001-2014 Kurt Rudahl and Sally Goldin
 *  ~~ EndC
 *
 * Created by Sally Goldin, 12/4/2001
 *
 *  $Id: InstallFileManager.java,v 1.24.2.2 2014/02/21 07:56:09 rudahl Exp $
 *  $Log: InstallFileManager.java,v $
 *  Revision 1.24.2.2  2014/02/21 07:56:09  rudahl
 *  integrated changes from v 6.4
 *
 *  Revision 1.24.2.1  2011/09/24 03:16:47  rudahl
 *  purge some driver code; improved tracing
 *
 *  Revision 1.24  2007/06/19 05:35:03  goldin
 *  Fix cleanup so that it always happens on an error
 *
 *  Revision 1.23  2006/06/06 05:21:28  goldin
 *  Make status area bigger and internationalize the CMD prompt
 *
 *  Revision 1.22  2005/07/31 08:34:31  goldin
 *  Working in I18N of Installer
 *
 *  Revision 1.21  2005/07/24 12:57:16  goldin
 *  Fix problems with embedded spaces in directories
 *
 *  Revision 1.23  2005/07/22 07:32:57  goldin
 *  Fix problems with paths that have embedded spaces
 *
 *  Revision 1.22  2005/06/27 06:07:22  goldin
 *  Upcase drive letters
 *
 *  Revision 1.21  2005/06/20 13:53:54  goldin
 *  Fixes to make the installer work
 *
 *  Revision 1.20  2005/02/06 08:28:58  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.19  2004/12/18 11:06:42  goldin
 *  Make verbose mode work
 *
 *  Revision 1.18  2002/09/20 16:26:49  goldin
 *  Interrupt any ongoing processes before deleting files
 *
 *  Revision 1.17  2002/09/12 00:35:13  goldin
 *  Add Readme button; don't exit automatically after confirming success
 *
 *  Revision 1.16  2002/09/03 18:03:03  goldin
 *  Fix bugs in running off the CD
 *
 *  Revision 1.15  2002/03/06 15:47:06  goldin
 *  Take out batch file deletion
 *
 *  Revision 1.14  2002/02/20 23:55:41  goldin
 *  Add code to change permissions to allow writing
 *
 *  Revision 1.13  2002/01/25 13:21:26  goldin
 *  Add facilities for deleting batch files and creating file list
 *
 *  Revision 1.12  2002/01/07 16:38:22  goldin
 *  Change chk.com to chk.exe
 *
 *  Revision 1.11  2001/12/21 11:27:38  goldin
 *  Fix problems with blank lines in input file
 *
 *  Revision 1.10  2001/12/21 10:48:52  goldin
 *  Add -m flag to cp.exe
 *
 *  Revision 1.9  2001/12/19 20:34:38  goldin
 *  Add functionality to run CHK
 *
 *  Revision 1.8  2001/12/18 15:13:22  goldin
 *  Change error message for disk space checks
 *
 *  Revision 1.7  2001/12/11 14:24:03  goldin
 *  Make installation of driver work
 *
 *  Revision 1.6  2001/12/10 15:53:40  goldin
 *  Try installing Sentinel driver
 *
 *  Revision 1.5  2001/12/07 17:21:10  goldin
 *  Add native method
 *
 *  Revision 1.4  2001/12/07 12:11:19  goldin
 *  Add code to create temp file
 *
 *  Revision 1.3  2001/12/06 14:55:35  goldin
 *  Continue expanding implementation
 *
 *  Revision 1.2  2001/12/05 14:28:33  goldin
 *  Implement file copying and cleanup
 *
 *  Revision 1.1  2001/12/04 16:09:34  goldin
 *  Implement class to control file operations -not yet working
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import java.io.*;
import java.util.*;

/**
 * This class encapsulates the reading and interpretation of a DRAGON
 * installation file list. The class handles such functions as
 * checking disk space, copying files, deleting files if cleanup 
 * is required, and so on. It may use native methods to perform
 * some of its work.
 */
public class InstallFileManager
    {
      /* Symbols used in the file list file.
       */
    protected static final String BASEPATH = "%BASEPATH%";
    protected static final String SECONDPATH = "%SECONDPATH%";
    protected static final String ROOT = "%ROOT%";
    protected static final String DRIVE = "%DRIVE%";

      /**
       *  free space required for base, secondary and temp
       *  drives. In Kbytes
       */
    protected long baseFreeSpace = 0;
    protected long secondaryFreeSpace = 0;
    protected long tempFreeSpace = 0;


      /**
       * The primary base path for the installation.
       */
    protected String basePath = null;

      /**
       * The base for optional components such as sample data.
       */
    protected String secondPath = null;

      /**
       * Drive & path  where installation program is running.
       */
    protected String installRoot = null;
      /**
       * Drive where installation program is running.
       */
    protected String installDrive = null;

      /**
       * List of files to process.
       */
    protected ArrayList managedFiles = new ArrayList(300);


      /**
       * If true, initialization was successful. Otherwise
       * there was an error reading the file list.
       */
    protected boolean bInitialized = false;

      /**
       * Last error message
       */
    protected String lastErrorMessage = null;


      /**
       * Installer that created this manager.
       */
    protected Installer parentInstaller = null;


      /**
       * subsidiary class instances. So we can interrupt them.
       */
    protected FileCopier copier = null;
    protected FileChecker checker = null;
   
      /**
       * flags to indicate what subtasks have been completed.
       */
    protected boolean bCopyCompleted = false;
    protected boolean bFileCheckCompleted = false;
 
      /**
       * Constructor reads and parses file and initializes the 
       * list of managed files.
       */
    public InstallFileManager(Installer parent,
			      String fileListFile,
			      String mainPath,
			      String secondPath)
        {
	this.parentInstaller = parent;
	this.basePath = mainPath;
	this.secondPath = secondPath;
        this.installRoot = System.getProperty("user.dir");
	int p = installRoot.indexOf(":");
	if (p >= 0)
	    installDrive = installRoot.substring(0,p+1);
	else
	    installDrive = installRoot;
	try
	    {
	    boolean bFirst = true;
	    if (parentInstaller.isVerbose())
	        {
		System.out.println("InstallFileManager::About to read file list file.");
	        }
            BufferedReader reader = new BufferedReader(new FileReader(
						     fileListFile));
	    // the first line holds three numbers: base, secondary and
	    // temp directory required memory. Then we have
	    // space-delimited triples of file spec (possibly with
	    // wild cards), source directory and destination directory
	    // (normally containing symbols BASEPATH or SECONDPATH)
	    String inputLine = null;
	    while ((inputLine = reader.readLine()) != null)
	        {
		if (bFirst)
		    {
		    parseFreeSpace(inputLine);
		    bFirst = false;
		    }
		else
		    {
		    FileCopySpec fspec = parseFileSpec(inputLine);
		    if (fspec != null)
		        managedFiles.add(fspec);
		    }

		}

	    bInitialized = true;
	    }
	catch (IOException ioe)
	    {
	    lastErrorMessage = ioe.getMessage();
	    if (lastErrorMessage == null)
	        {
		lastErrorMessage = 
		  ApplicationManager.getTextSource().getI18NText("%01.13.0",
                    "Error reading list of files to copy.");
                }
	    }
	}

      /**
       * Factorization. Parse the first line of the file to get the
       * various free space numbers.
       * @param inputLine  Line of text to be parsed.
       */
    protected void parseFreeSpace(String inputLine)
        {
	int which = 0;
	StringTokenizer tokenizer = new StringTokenizer(inputLine," ");
	while (tokenizer.hasMoreTokens())
	    {
	    String temp = tokenizer.nextToken();
	    long lTemp = Long.parseLong(temp);
	    switch (which)
	      {
	      case 0:  baseFreeSpace = lTemp;
		       break;
	      case 1:  secondaryFreeSpace = lTemp;
		       if ((secondPath != null) &&
                           (basePath.substring(0,1).equals(secondPath.substring(0,1))))
			   {
			   /* if the two are on the same drive,
			    * need enough space for both
			    */
			   baseFreeSpace += secondaryFreeSpace;
			   secondaryFreeSpace = baseFreeSpace;
			   }
		       break;
	      case 2:  tempFreeSpace = lTemp;
		       break;
	      }
	    which++;
	    }
	if (parentInstaller.isVerbose())
	    {
            System.out.println("ParseFreeSpace: baseFreeSpace=" 
               + baseFreeSpace +
	       " secondaryFreeSpace=" + secondaryFreeSpace +
	       " tempFreeSpace=" + tempFreeSpace);
	    }
	}


      /**
       * Factorization. Parse a line of the file to get the
       * file specification components.
       * @param inputLine  Line of text to be parsed.
       * @return new FileCopySpec object or null if the line was a 
       *          comment.
       */
    protected FileCopySpec parseFileSpec(String inputLine)
                             throws IOException
        {
	FileCopySpec fSpec = null;
        int which = 0;
        if (inputLine.startsWith("#"))  // comment line
	    return fSpec;
	if (inputLine.trim().length() == 0)  // blank line
	    return fSpec;
	String locInstallRoot = installRoot;
	if ((locInstallRoot.length() == 3) && (locInstallRoot.indexOf(":") == 1)
		&& ((locInstallRoot.endsWith("/")  || (locInstallRoot.endsWith("\\") ))))
	    locInstallRoot = locInstallRoot.substring(0,2);
	fSpec = new FileCopySpec();
	StringTokenizer tokenizer = new StringTokenizer(inputLine," ");
	// parse each line (past the first one) of dragfiles.txt
	while (tokenizer.hasMoreTokens())
	    {
	    String temp = tokenizer.nextToken();
	    switch (which)
	      {
	      case 0:  fSpec.filename = temp;	// the file name
  		       break;
	      case 1:  if (temp.startsWith(ROOT)) // the from directory
  		           {
			   temp = locInstallRoot +
			     temp.substring(ROOT.length());
			   }
	               else if (temp.startsWith(DRIVE))
		           {
			   temp = installDrive +
			     temp.substring(DRIVE.length());
			   }
		       fSpec.sourceDirectory = temp;
		       break;
	      case 2:  if (temp.startsWith(BASEPATH)) // the to directory
		           {
			   temp = basePath + temp.substring(BASEPATH.length());
			   }
	               else if (temp.startsWith(SECONDPATH))
			   {
                           if (secondPath == null)
			       return null;
			   else
			       {
			       temp = secondPath + 
			            temp.substring(SECONDPATH.length());
			       }
			   } 
	               fSpec.destinationDirectory = temp;
		       break;
	      }
	    which++;
	    }
	if ((which > 0) && (which < 3))
	    {
	      // parsing error
	    
	    throw new IOException(
              "Incomplete file specification in file list: " +
	         inputLine);
	    }
	return fSpec;
	}

      /**
       * Check if there is enough space for all the main files in
       * on the selected disk.
       * @return true if ok, false if insufficient space
       */
    public boolean checkMainSpace()
        {
	long lSpace = GetFreeDiskSpace(basePath);
	if (parentInstaller.isVerbose())
	   {
	   System.out.println("checkMainSpace: for drive " + 
                            basePath.substring(0,2) +
			   " space is " + lSpace);
	   }
        if ((baseFreeSpace > 0) && (lSpace < baseFreeSpace))
	   {
	   StringBuffer buffer = new StringBuffer(256);
	   String baseDrive = basePath.substring(0,2);
           String substValues[] = new String[] {baseDrive,String.valueOf(baseFreeSpace),
						  String.valueOf(lSpace)};
           lastErrorMessage = ApplicationManager.getTextSource().getI18NText("%h01.9909",
              "Insufficent disk space available on drive %1; %2 K but only %3 K available.",
              substValues);
	   return false;
	   }
        return true;
	}
   
      /**
       * Check if there is enough space for all the secondary files in
       * on the selected disk.
       * @return true if ok, false if insufficient space
       */
    public boolean checkSecondarySpace()
        {
	long lSpace = GetFreeDiskSpace(secondPath);
	//System.out.println("for drive " + secondPath.substring(0,2) +
	//		   " space is " + lSpace);
        if ((secondaryFreeSpace > 0) && (lSpace < secondaryFreeSpace))
	    {
	    StringBuffer buffer = new StringBuffer(256);
	    String baseDrive = secondPath.substring(0,2);
            String substValues[] = new String[] {baseDrive,String.valueOf(secondaryFreeSpace),
						  String.valueOf(lSpace)};
	    lastErrorMessage = ApplicationManager.getTextSource().getI18NText("%h01.9909",
              "Insufficent disk space available on drive %1; %2 K but only %3 K available.",
              substValues);
	    return false;
	    }
        return true;
	}

      /**
       * Check if there is enough space after installation on the
       * temp directory.
       * @return true if ok, false if insufficient space
       */
    public boolean checkTempSpace(String tmpPath)
        {
	long lSpace = GetFreeDiskSpace(tmpPath);
	//System.out.println("for drive " + tmpPath.substring(0,2) +
	//		   " space is " + lSpace);
        if ((tempFreeSpace > 0) && (lSpace < tempFreeSpace))
	    {
	    StringBuffer buffer = new StringBuffer(256);
	    String baseDrive = tmpPath.substring(0,2);
            String substValues[] = new String[] {baseDrive,String.valueOf(tempFreeSpace),
						  String.valueOf(lSpace)};
	    lastErrorMessage = ApplicationManager.getTextSource().getI18NText("%h01.9909",
              "Insufficent disk space available on drive %1; %2 K but only %3 K available.",
              substValues);
	    return false;
	    }
        return true;
	}

      /**
       * Copy files as specified in the filelist.
       */
    public void copyFiles()
        {
	lastErrorMessage = null;
	// create the directories if necessary
	File sysPath = new File(basePath);
	if (!sysPath.exists())
	    sysPath.mkdirs();
	if (secondPath != null)
	    {
	    File second = new File(secondPath);
	    if (!second.exists())
	        second.mkdirs();
	    }
	copier = new FileCopier();
	copier.start();
	}

      /**
       * Check that required files are in place and have 
       * the correct checksum
       */
    public void checkIntegrity()
        {
	lastErrorMessage = null;
	checker = new FileChecker();
	checker.start();
	}

      /**
       * Called when an installation aborts prematurely.
       * Deletes any files installed by the program.
       * At the moment, it does this by removing the 
       * base and secondary directories entirely.
       * @return true if successful, else false
       */
    public boolean cleanupFiles()
        {
        if (parentInstaller.isVerbose())
	   {
	   System.out.println("InstallFileManager::cleanupFiles.");
	   }
	if (!bCopyCompleted)
	   {
	   if ((copier != null) && (copier.isAlive()))
	       {
	       copier.interrupt();
	       copier.changePermissions();
	       }
	   }
	else if (!bFileCheckCompleted)
	   {
	   if ((checker != null) && (checker.isAlive()))
	       {
	       checker.interrupt();
	       }
	   } 
	boolean bOk = deleteDirectory(basePath);
	if (!bOk)
	    bOk = deleteDirectory(basePath);  // try again
	if (secondPath != null)
	    {
	    bOk = deleteDirectory(secondPath);
	    if (!bOk)
	        bOk = deleteDirectory(secondPath);
	    }
	return bOk;
	}

      /**
       * Recursive function to delete subdirectories and ultimately
       * delete an entire directory tree.
       * @param path  Path to delete
       * @return true if success, false if failure.
       */
    protected boolean deleteDirectory(String path)
        {
	boolean bOk = true;
	File subFile = null;
	File dirFile = new File(path);
	//System.out.println(">>deleteDirectory for " + path);
	String subFileNames[] = dirFile.list();
        if (subFileNames == null)  // might be empty directory
	    return true;
	//System.out.println(">>There are " + subFileNames.length + " entries");
	for (int i = 0; i < subFileNames.length; i++)
	    {
	    //System.out.println("Checking file " + subFileNames[i]);
	    subFile = new File(path,subFileNames[i]);
	    if (subFile.isDirectory())
	        bOk = deleteDirectory(subFile.getAbsolutePath());
	    else
	        bOk = subFile.delete();
	    }
        if (bOk)
	    {
	    //System.out.println("deleting " + path);
	    bOk = dirFile.delete();
	    }
	else 
	    {
	    //System.out.println("deletion failed: " +subFile.getAbsolutePath());
	    }
	return bOk;
	}

      /**
       * Native method to call back and get free disk space
       */
    public native long GetFreeDiskSpace(String directory);

      /**
       * Native method to call to change current directory
       */
    public native int ChangeCurrentDirectory(String directory);
	  
      /**
       * Access methods
       */
    public boolean isInitialized()
        {
	return bInitialized;
        }

    public String getLastErrorMessage()
        {
	return lastErrorMessage;
        }


      /**
       * Inner data class, used to store the interpretation of the
       * file list file.
       */
    class FileCopySpec
        {
	public String filename;
	public String sourceDirectory;
	public String destinationDirectory;
        }

      //////////////////////////////////////

      /**
       * Inner class to put file copying in a separate thread,
       * so that the UI doesn't freeze while we are doing the
       * the copying.
       */
    class FileCopier extends Thread
        {
	  /**
	   * Main thread method, copied files as specified in
	   * the managedFiles list.
	   */
	public void run() 
            {
	    boolean bOk = true;
	    if (parentInstaller.isVerbose())
		System.out.println("FileCopier starting.");
	    StringBuffer cmd = new StringBuffer(512);
	    Iterator iterator = managedFiles.iterator();
	    while (iterator.hasNext())
	        {
		FileCopySpec fSpec = (FileCopySpec) iterator.next();
		if (fSpec != null)
		    {
		    if (cmd.length() > 0)
		        cmd.delete(0,cmd.length());
		    cmd.append("\"" + installRoot + File.separator + 
                                 "cp.exe\" -mR ");
		    cmd.append("\"" + fSpec.sourceDirectory + File.separator +
			       fSpec.filename + "\"");
		    cmd.append(" " + "\"" + fSpec.destinationDirectory
                                + "\"");
		    if (parentInstaller.isVerbose())
		       {
		       System.out.println("FileCopier:: about to exec cmd |"
					  + cmd.toString());
		       }
		    File tester = new File(fSpec.destinationDirectory);
		    if (!tester.exists())
		        tester.mkdirs();
		    String fileSpecs[] = new String[2];
		    fileSpecs[0] = fSpec.sourceDirectory + "/" + 
		                   fSpec.filename;
		    fileSpecs[1] = fSpec.destinationDirectory;
		    String copyMessage =
                     ApplicationManager.getTextSource().getI18NText(
                                "%h01.12.0","COPYING %1 to %2",
				fileSpecs);
		    
		    parentInstaller.updateStatusArea(copyMessage);
		    try
		        {
			Process proc = Runtime.getRuntime().exec(cmd.toString());
			proc.waitFor();
			int exit = proc.exitValue();
                	if (parentInstaller.isVerbose())
			   {
			   System.out.println("FileCopier::Copy process returned " + exit);
	                   }
			if (exit != 0)
			    {
			    lastErrorMessage = 
		  ApplicationManager.getTextSource().getI18NText("%01.13.2",
                           "Error copying files from %1 to %2",
			    new String[] {fSpec.sourceDirectory,
                                          fSpec.destinationDirectory});
			    interrupt();
			    }
		        }
		    catch (IOException ioe)
		        {
                	if (parentInstaller.isVerbose())
			   {
			   System.out.println("FileCopier::IO Error " 
					      + ioe.getMessage());
	                   }
			lastErrorMessage = ioe.getMessage();
                        if (lastErrorMessage == null)
                           {
			    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
				       "%01.13.3",
                                       "IO Error during file copy.");
                           }
			parentInstaller.copyCompleted(false);
			return;
		        }
		    catch (InterruptedException ie)
		        {
                	if (parentInstaller.isVerbose())
			   {
			   System.out.println("FileCopier::Interrupted " 
					      + ie.getMessage());
	                   }
			if (lastErrorMessage == null)
			    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
				       "%01.13.4",
				       "File Copy Interrupted");
			parentInstaller.copyCompleted(false);
			return;
		        }
		    } // endif not null
		}     // end loop
	    // if we get here, we must have copied everything successfully
	    
            bOk = createFileList();
            if (parentInstaller.isVerbose())
	     	{
		System.out.println("FileCopier::createFileList returned " + bOk);
	        }
	    if (bOk)
	        bOk = changePermissions();
            if (parentInstaller.isVerbose())
	     	{
		System.out.println("FileCopier::changePermissions returned " + bOk);
	        }
	    bCopyCompleted = true;
	    parentInstaller.copyCompleted(bOk);
	    if (parentInstaller.isVerbose())
		System.out.println("FileCopier finished.");
	    }         // end run

	  /**
	   * Factorization. Create a list of installed files in the
	   * SYSTEM directory. Returns true if ok, false if error.
	   */
	protected boolean createFileList()  
            {
	    StringBuffer cmd = new StringBuffer(512);
	    cmd.append("cmd /c dir " + basePath);
	    cmd.append(" > " + basePath + File.separator + "OUT.JNK");
	    try
	        {
		String inLine = null;
		BufferedWriter writer = new BufferedWriter(
					     new FileWriter(basePath +
						   File.separator +
						   "InstalledFiles.lis"));
		writer.write("DRAGON Files installed in " +
			     basePath + " on " +
			     new Date().toString());
		writer.newLine();
		Process proc = Runtime.getRuntime().exec(cmd.toString());
		proc.waitFor();
		int exit = proc.exitValue();
		if (exit != 0)
		    {
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
				       "%01.13.5",
                                       "Error writing file list");
		    return false;
		    }
		BufferedReader reader = new BufferedReader(
				   new FileReader(basePath +
						  File.separator +
						  "OUT.JNK"));
		// read and parse each line, then output to new file
		inLine = reader.readLine();
		while (inLine != null)
		    {
		    parseAndWrite(inLine,writer);
		    inLine = reader.readLine();
		    }
		reader.close();
		writer.close();
                File delFile = new File(basePath + File.separator + "OUT.JNK");
		delFile.delete();
		}
	    catch (IOException ioe)
	        {
		lastErrorMessage = ioe.getMessage();
		if (lastErrorMessage == null)
		   {
		   lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.6",
                          "IO Error during creation of installed files list");
		   }
		return false;
		}
	    catch (InterruptedException ie)
	        {
		if (lastErrorMessage == null)
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.7",
                               "File list creation interrupted");
		return false;
		}
	    return true;
	    }

	  /**
	   * Factorization of createFileList.
	   * Parses a single line of directory output and if
	   * appropriate, writes it to the output file.
	   */
       protected void parseAndWrite(String inputLine,
				    BufferedWriter writer)
	               throws IOException
            {
            String date = null;
	    String time = null;
	    String filename = null;
	    int tokNumber = 0;
	    StringTokenizer tokenizer = new
	        StringTokenizer(inputLine," ");
	    if (tokenizer.countTokens() != 4)
	        return;
	    while (tokenizer.hasMoreTokens())
	        {
		String temp = tokenizer.nextToken();
		if (tokNumber == 0)
		    date = temp;
		else if (tokNumber == 1)
		    time = temp;
		else if ((tokNumber == 2) && (temp.startsWith("<DIR>")))
		    return; // don't print directories
		else if (tokNumber == 3)
		    filename = temp;
		tokNumber++;
		}
            if (filename.compareTo("bytes") == 0)
		return;
            int nTabs = 6 - (filename.length()/8);
	    if (nTabs < 1)
	        nTabs = 1;
	    writer.write(filename);
	    for (int i = 0; i < nTabs; i++)
                writer.write("\t");
            writer.write(date + "\t" + time);
	    writer.newLine();
	    }

	  /**
	   * Factorization. Delete any .bat files in the
	   * SYSTEM directory. Returns true if ok, false if error.
	   */
	protected boolean deleteBatchFiles()  
            {
	    StringBuffer cmd = new StringBuffer(512);
	    cmd.append("cmd /c del ");
	    cmd.append(basePath + File.separator + "*.bat");
	    try
	        {
		Process proc = Runtime.getRuntime().exec(cmd.toString());
		proc.waitFor();
		int exit = proc.exitValue();
		// System.out.println("Exit value: " + exit);
		if (exit != 0)
		    {
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.8",
                                    "Error deleting batch files");
		    return false;
		    }
		}
	    catch (IOException ioe)
	        {
		lastErrorMessage = ioe.getMessage();
		return false;
		}
	    catch (InterruptedException ie)
	        {
		if (lastErrorMessage == null)
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.9",
				       "File Deletion Interrupted");
		return false;
		}
	    return true;
	    }

	  /**
	   * Factorization. Changes the permissions of all files
	   * to be writable in both system and sample data directories
	   * Make public so that it can be called from the InstallFileManager
	   * on a cancel
	   */
	public boolean changePermissions()  
            {
	    StringBuffer cmd = new StringBuffer(512);
	    cmd.append("\"" + installRoot + File.separator + 
                        "chmod.exe\" -R 0777 ");
	    cmd.append(basePath + File.separator + "*");
	    if (parentInstaller.isVerbose())
	        {
		System.out.println("changePermissions: About to exec |"
				   + cmd.toString());
	        }
	    try
	         {
		Process proc = Runtime.getRuntime().exec(cmd.toString());
		proc.waitFor();
		int exit = proc.exitValue();
		if (parentInstaller.isVerbose())
		    {
		    System.out.println("command "+cmd+" returned " + exit);
		    }
		if (exit != 0)
		    {
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.10",
                               "Error changing file permissions");
		    return false;
		    }
		}
	    catch (IOException ioe)
	        {
		lastErrorMessage = ioe.getMessage();
		if (lastErrorMessage == null)
		    {
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.11",
                               "IO Error changing file permissions");
		    }
		return false;
		}
	    catch (InterruptedException ie)
	        {
		if (lastErrorMessage == null)
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.12",
                               "File permission changes interrupted");
		return false;
		}
            cmd.delete(0, cmd.length());
	    if ((secondPath == null) ||
		(secondPath.length() == 0))
	        return true;
	    cmd.append("\"" + installRoot + File.separator + "chmod.exe\" -R 0777 ");
	    cmd.append(secondPath + File.separator + "*");
	    try
	        {
		Process proc = Runtime.getRuntime().exec(cmd.toString());
		proc.waitFor();
		int exit = proc.exitValue();
		// System.out.println("Exit value: " + exit);
		if (exit != 0)
		    {
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.10",
				       "Error changing file permissions");
		    return false;
		    }
		}
	    catch (IOException ioe)
	        {
		lastErrorMessage = ioe.getMessage();
		if (lastErrorMessage == null)
		   {
		   lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.11",
                     "IO Error during file copy or file protection change.");  
		   }
		return false;
		}
	    catch (InterruptedException ie)
	        {
		if (lastErrorMessage == null)
		    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.12",
                               "File Permission update Interrupted");
		return false;
		}
	    return true;
	    }
        }  // end FileCopier class

      //////////////////////////////////////

      /**
       * Inner class to put checking of file existence/integrity in a 
       * separate thread,
       * so that the UI doesn't freeze while we are doing this task
       */
    class FileChecker extends Thread
        {
	  /**
	   * Main thread method checks the file integrity using "chk.exe"
	   */
	public void run() 
            {
	    File deleteFile = null;
	    boolean bError = false;
	    String outputFile = basePath + File.separator + "out.jnk";
	    if (parentInstaller.isVerbose())
		System.out.println("FileChecker starting.");
	    int retval = ChangeCurrentDirectory(basePath);
            if (retval != 0)
	         {
		 lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.16",
		         "Cannot change to Dragon System directory.");
		 parentInstaller.chkCompleted(false);
		 return;
		 }
	    StringBuffer cmd = new StringBuffer(512);
	    String shellCmd = System.getProperty("SHELL","cmd");
	    cmd.append(shellCmd + " /c " + "\"" +
		       installRoot + File.separator + "chk.exe \"" +
		       " -t @WINFILES > " + outputFile);
	    if (parentInstaller.isVerbose())
		System.out.println("FileChecker about to exec |" +
				   cmd.toString());
	    try
	        {
		int exit = 0;
		Process proc = 
		      Runtime.getRuntime().exec(cmd.toString());
		proc.waitFor();
		BufferedReader reader = new BufferedReader(
			 new FileReader(outputFile));
		String line = null;
		while ((line = reader.readLine()) != null)
		    {
		    if (line.indexOf("ERROR") >= 0)
		        {
                        bError = true;
			//System.out.println("Found error: " + line);
			}
		    }
		exit = proc.exitValue();
		if (parentInstaller.isVerbose())
		    System.out.println("FileChecker process returned " +exit);
		if ((exit != 0) || (bError))
		    {
                    if (bError)
		       lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.17",
		         "Some required files appear to be missing.");
		    else if (exit != 0)
                       lastErrorMessage =
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.18",
				       "Error running file checking program.");
		    deleteFile= new File(outputFile);
		    if (deleteFile.exists())
		         deleteFile.delete();
		    parentInstaller.chkCompleted(false);
		    return;
		    }
		else 
		    {
		    cmd.delete(0, cmd.length());
		    cmd.append(shellCmd + " /c " +
			       "\"" + installRoot + File.separator + 
                              "chk.exe\" " +
		       "-e 1 -n @WINFILES.CHK >" + outputFile);
          	    if (parentInstaller.isVerbose())
		       {
		       System.out.println("Filechecker about to exec |" +
					   cmd.toString());
		       }
		    exit = 0;
		    proc = 
		      Runtime.getRuntime().exec(cmd.toString());
		    proc.waitFor();
		    File tester = new File(outputFile);
		    // the above command will not create any output
		    // if everything went ok
		    if (tester.exists())
		        {
			reader = new BufferedReader(
			   new FileReader(outputFile));
			while ((line = reader.readLine()) != null)
		            {
			    if (line.indexOf("ERROR") >= 0)
			       {
                               bError = true;
			       //System.out.println("Found error: " + line);
			       }
			    }
			}
		    if (tester.exists())
		        tester.delete();
		    exit = proc.exitValue();
		    if (parentInstaller.isVerbose())
			System.out.println("FileChecker process returned " 
					   +exit);
		    if ((exit != 0) || (bError))
		        {
                        if (bError)
			    lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.19",
                               "Some critical files appear to be corrupted.");
			else if (exit != 0)
			    lastErrorMessage =
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.18",
			       "Error running file checking program.");
			deleteFile= new File(outputFile);
			if (deleteFile.exists())
		            deleteFile.delete();
			parentInstaller.chkCompleted(false);
			if (parentInstaller.isVerbose())
			    System.out.println("Filechecker::run (ex) test error:"+lastErrorMessage);
			return;
		        }
		    }
	        }
	    catch (IOException ioe)
	        {
		lastErrorMessage = ioe.getMessage();
		parentInstaller.chkCompleted(false);
		if (parentInstaller.isVerbose())
		    System.out.println("Filechecker::run (ex) IO exception:"
			+ lastErrorMessage);
		return;
	        }
	    catch (InterruptedException ie)
	        {
		if (lastErrorMessage == null)
		      lastErrorMessage = 
		               ApplicationManager.getTextSource().getI18NText(
   				       "%01.13.20",
				       "File Checking Interrupted");
		parentInstaller.chkCompleted(false);
		if (parentInstaller.isVerbose())
		    System.out.println("Filechecker::run (ex) interrupted");
		return;
	        }
	    // if we get here, we must have successfully done the checks
	    bFileCheckCompleted = true;
	    parentInstaller.chkCompleted(true);
	    if (parentInstaller.isVerbose())
		System.out.println("Filechecker::run (ex) OK");
	    }         // end run
        }  // end FileChecker class

    }


