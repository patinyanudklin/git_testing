/**
 *  DFileMultiChooserModel
 *
 *    This is a specialization of the file chooser model,
 *    which can keep track of more than one file and directory
 *    at a time.
 *
 *	~~ Copyright  2006-2014   Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri
 *	~~ EndC
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *    
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *
 * $Id: DFileMultiChooserModel.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: DFileMultiChooserModel.java,v $
 * Revision 1.3.2.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.4  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2006/12/28 10:34:21  goldin
 * Complete implementation of multifile selection control and file chooser
 *
 * Revision 1.1  2006/12/25 10:48:37  goldin
 * Begin implementation of multi-select file control
 */

package com.grs.gui;
import java.io.*;
import java.util.*;

/**
 * This class centralizes information on the current state of a 
 * DragonFileChooser control. This information includes the
 * currently selected path and file, the current file type,
 * whether the file selected must exist or not, etc.
 * The individual controls in the file chooser (the tree, file list,
 * combos, etc.) call methods on the DFileChooserModel to update its
 * state. It, in turn, signals the controls to update their
 * views.*/
public class DFileMultiChooserModel extends DFileChooserModel
    {

      /**
       * Currently-selected filename string.
       */
    protected String currentFilename = null; 

      /**
       * Array list of files that have been added - as File objects
       */
    protected ArrayList<File> currentFilenameList = new ArrayList<File>();

       

      /**
       * Currently-selected path
       */
    protected String currentPath = null;

      /**
       * Tree node corresponding to current path.
       */
    protected DirTreeNode currentTreeNode = null;

      /**
       * Path selected the last time the box was exited with OK
       */
    protected String lastSelectedPath = null;

      /**
       * Save the previous path & filename, since we need it in updating
       * the fileList view.
       */
    protected String oldPath = null;
    protected String oldFilename = null;

      /**
       * Parent file chooser*/
    protected DragonFileChooser chooser = null;

      /**
       * Reference to the chooser's dir tree*/
    protected DragonDirTree dirTree = null;

      /**
       * Reference to the chooser's file list - might be null.*/
    protected DragonFileList fileList = null;

      /**
       * Singleton comparator used to sort filenames.
       */
    protected static CaseInsensitiveComparator filenameComparator = null;

      /**
       * File types for filtering files. Now can have 
       * multiple.
       */
    protected DFileType[] filterFileTypes = null;

      /**
       * Partial name filter, used when user types a partial
       * filename before clicking on the button to display the dialog.
       * Also used to implement the Filter box in the dialog
       */
    protected String partialName = null;

      /**
       * For output files, the currently selected file type.
       * used to filter the filelist, also for validation.
       */
    protected DFileType currentOutputFileType = null;

      /**
       * Key to error message associated with last error, if any.
       */
    protected String lastErrorKey = null;

      /**
       * File associated with last error, if any.
       */
    protected String lastErrorFile = null;

      /**
       * Was last selected file a memory/special file?
       */
    protected boolean bMemoryFileSelected = false;

    
    protected int maxAllowedFileCount = 12;  

      //************************************************************
      /**
       * Constructor sets references to components.
       */
    public DFileMultiChooserModel(DragonFileChooser chooser,
			     DragonDirTree dirTree,
			     DragonFileList fileList)
        {
	super(chooser,dirTree,fileList);
  	this.chooser = chooser;
	this.dirTree = dirTree;
	this.fileList = fileList;
	if (filenameComparator == null)
	    filenameComparator = new CaseInsensitiveComparator();
	}

      /**
       * Allows the dirTree and fileList to set the values of
       * the path and the filename, respectively.
       */
    public void setCurrentFilename(String filename)
        {
	if (fileList == null)
	    return;
	if (currentPath == null)
	    {
            setCurrentPath(ApplicationManager.getReadPath());
	    }
	String msg = "{ DFileMultiChooserModel: setting filename to " +
	                    filename + " }";
	Tracer.outputTraceMessage(msg,
				  ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
	boolean bEnable = false;
        oldFilename = currentFilename;
        currentFilename = filename;
	fileList.updateView(currentPath,currentFilename,oldPath,oldFilename);
	if ((currentFilename != null) &&
                 ((currentFilename.startsWith("=")) ||
                  (currentFilename.startsWith("("))))
	     {
	     bEnable = true;
	     }
	else if ((currentPath != null) &&
	    (currentFilename != null) && 
	    (currentFilename.length() > 0)) 
	     {
             if (!currentFilename.endsWith("*"))
	         {
                 partialName = null;
	         bEnable = true;
	         }
	     else
	         {
		 setPartialName(currentFilename);
		 dirTree.updateView(currentPath, currentPath);
		 }
	     }
        addCurrentFileList(currentPath, currentFilename);
	chooser.setDetailsEnabled(bEnable);
	chooser.setOkEnabled(bEnable);
	}

      /**
       * Factorization of setCurrentFilename.
       * If the filename is not already in the array
       * list, add it at the end. Otherwise, ignore it.
       * @param path      Path of this filename
       * @param filename  Filename to check.
       * @return true if added, false if not (already in list)
       */
    protected boolean addCurrentFileList(String path, String filename)
        {
	boolean bFound = false;
        if ((path == null) || (filename == null))
	    return false;
        File newFile = new File(new String(path + File.separator + filename));
        String newName = newFile.getAbsolutePath();
        int count = currentFilenameList.size();
        int i = 0;
        while ((i < count) && (!bFound))
            {
	    String otherFilename = ((File)currentFilenameList.get(i)).getAbsolutePath();
            if (otherFilename.compareToIgnoreCase(newName) == 0)
		bFound = true;
            i += 1;
            }
        if (!bFound)
            {
	    if (currentFilenameList.size() >= maxAllowedFileCount)
               {
	       MessageDisplay mDisplay = ApplicationManager.getMessageDisplay();
	       String title = ApplicationManager.getTextSource().getI18NText(
					  TextKeys.WARNING,"Warning");
	       String msg = ApplicationManager.getTextSource().getI18NText(
					  "%m10000.2","Too many files");
	       mDisplay.showWarning(title,msg);
	       bFound = true;
	       }
	    else
	       {
	       currentFilenameList.add(newFile);
	       }
	    }
        return (!bFound);  // if found, return false, else true (added)
	}
	
	/**
	 * Remove an item from the set of selected files
	 * @param index  Which item to remove
	 */
    public void removeItem(int index)
        {
	currentFilenameList.remove(index);
	}
 

      /**
       * Allows the fileList to set filter value and update
       * the file list
       */
    public void setCurrentFilter(String fileFilter)
        {
	setPartialName(fileFilter);
	if (currentTreeNode != null)
	    {
	    setFileList(currentTreeNode,false);
	    if ((currentFilename != null) && 
	        (fileList.fileIndex(currentFilename) < 0))
	        {
		setCurrentFilename(null);
		}
	    else 
	        {
	        fileList.updateView(currentPath,currentFilename,
				    oldPath,oldFilename);
		}
	    }

	}


      /**
       * Reinstate the last chosen path. Use to set initial
       * default if none is provided in field.
       */
    public void setCurrentPathToLast()
        {
	if (lastSelectedPath != null)
	    setCurrentPath(lastSelectedPath);
	}

    public void setCurrentPath(String path)
        {
	String msg = "{ DFileMultiChooserModel: setting path to " +
	                    path + " }";
	Tracer.outputTraceMessage(msg,
				  ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
	boolean bEnable = false;
	// upcase the drive letter if any
	String newpath = path;
	if (path != null)
	    {
            int pos = path.indexOf(":");
	    if (pos > 0)
	        {
		newpath = path.substring(0,pos).toUpperCase() +
                          path.substring(pos);
		}
	    }
 	oldPath = currentPath;
	if (newpath.equalsIgnoreCase(currentPath))
	    return;
	currentPath = newpath;
	dirTree.updateView(currentPath,oldPath);
	currentTreeNode = dirTree.getTreeModel().findNode(newpath);
	if ((fileList == null) && (currentPath != null))
	    {
	    bEnable = true;
	    }
	chooser.setOkEnabled(bEnable);
	}


    public void setFileList(DirTreeNode node, boolean bCheckDrive)
        {
	int i = 0;
	int j = 0;
        ArrayList<String> files = new ArrayList<String>(300);
	if ((fileList != null) && (node != null))
	    {
	    if (bCheckDrive)
	        {
                if (DriveTester.isDriveOk(node.getNodeFile().getAbsolutePath()) 
		                                          == false)
                    return;
		}
	    if (currentOutputFileType != null)
	        {
		String[] matching = 
                      node.getMatchingFiles(currentOutputFileType);
		if (matching != null)
	            for (j = 0; j < matching.length; j++)
                         files.add(matching[j]);
	        }
	    else for (i = 0; i < filterFileTypes.length; i++)
	        {
		String[] matching = node.getMatchingFiles(filterFileTypes[i]); 
		if (matching != null)
	            for (j = 0; j < matching.length; j++)
                        files.add(matching[j]);
	        }
	    Object[] contents = files.toArray();
	    String[] fileNames = new String[contents.length];
	    for (i = 0; i < contents.length; i++)
	        fileNames[i] = (String) contents[i];
	    if (partialName != null)
	        fileNames = filterByName(fileNames,partialName);
	    Arrays.sort(fileNames,filenameComparator);
	    fileList.populateFiles(fileNames);
	    }
	}


      /**
       * Given an array of filenames, returns a new array
       * which holds only those filenames whose beginnings match
       * a partial name pattern (case insensitive match).
       * @param oldFiles  Array of filenames to be tested
       * @param pattern   Starting pattern to match against
       * @return New array of filenames that match the pattern.
       */
    protected String[] filterByName(String[] oldFiles, String pattern)
        {
	int maxLen = oldFiles.length;
        String lowerPattern = pattern.toLowerCase();
	ArrayList<String> temp = new ArrayList<String>(maxLen);
	for (int i = 0; i < maxLen; i++)
	     {
	     if (oldFiles[i].toLowerCase().startsWith(lowerPattern))
	         {
		 temp.add(oldFiles[i]);
		 }
	     }	
	String[] newFiles = new String[temp.size()];
	for (int i = 0; i < temp.size(); i++)
	     {
	     newFiles[i] = (String) temp.get(i);
	     }	
	return newFiles;
	}

    public void clearFileList()
        {
	if (fileList != null)
	    {
	    fileList.populateFiles(null);
	    }
	}


      /**
       * Validate current filename as appropriate for
       * the relevant control type. 
       * @param path  Path to validate. If null, use currentPath.
       * @param filename Filename to validate. If null, use currentFilename
       * @param bReadFile If true, file must exist.
       * @param bOverwriteWarning  If false, file must not exist.
       * @param bShowError If true, display error box, else just
       *                   return validation result
       * @return true if file is OK given constraints, else false.
       */
    public boolean validateFile(String path,
				String filename,
				boolean bReadFile,
				boolean bOverwriteWarning,
				boolean bShowError)
        {
	String fName = filename;
	String pName = path;
	boolean bOk = true;
	lastErrorKey = null;
	lastErrorFile = null;
	if (fName == null)
	    fName = currentFilename;
	if (pName == null)
	    pName = currentPath;
	if (fName == null)
	    fName = "";
	
	if ((fName.startsWith("=")) ||
	    (fName.startsWith("(")))
	    {
	    return bOk;   // note that this will not catch
	                  // cases where the user types in a memory file
	                  // that is not valid.
	    }
	if ((fName.indexOf("*") >= 0) ||
	    (fName.indexOf("?") >= 0))
	    {
	    return bOk;   //A few operations allow file specs with wildcards
	    }
        File testFile = null;
	if ((pName.indexOf(" ") >= 0) ||
	    (fName.indexOf(" ") >= 0))
	    {
	    bOk = false;
	    lastErrorKey = TextKeys.BADFILE_ERR;
	    }
	else
	    {
	    testFile = new File(pName,fName);
	    boolean bExists = testFile.exists();
	    if ((bReadFile) && (!bExists))
	        {
		bOk = false;
		lastErrorKey = TextKeys.NOTFOUND_ERR;
		}
            else if ((!bReadFile) && (bOverwriteWarning) && (bExists))
	        {
		bOk = false;
		lastErrorKey = TextKeys.EXISTS_ERR;
	        }
	    } 

	if  (!bOk) 
	    {
            if (pName.endsWith(File.separator))
	        lastErrorFile = pName + fName;
	    else 
	        lastErrorFile = pName + File.separator + fName;
	    if (bShowError)
	        {  
	        ErrorDisplay errDisplay = ApplicationManager.getErrorDisplay();
	        errDisplay.showError(TextKeys.ERROR,lastErrorKey,
				 lastErrorFile);
		}
	    }
	return bOk;
	}

	/**
	 * Set the contents of the selected files list. 
         * This is called when the chooser first appears,
	 * so that it shows all the files that have been
	 * selected in the main panel (if any)
	 * @param filenames   Array of currently selected files
	 */
    public void setSelectedFiles(String[] filenames)
	{
	currentFilenameList.clear();
        for (int i = 0; i < filenames.length; i++)
           {
	   File newFile = new File(filenames[i]);
	   currentFilenameList.add(newFile);
           }
	}
       
    public String getCurrentFilename()
        {
        return currentFilename;
	}

	/**
         * Return current list of selected files as an array
         * of strings.
         */
    public String[] getCurrentFilenameListAsString()
        {
	int fileCount = currentFilenameList.size();
	String [] returnList = new String[fileCount];
        for (int i = 0; i < fileCount; i++)
	    returnList[i] = ((File) currentFilenameList.get(i)).getAbsolutePath();
        return returnList;
	}

	/**
         * Return current list of selected files as an array
         * of File objects.
         */
    public File[] getCurrentFilenameList()
        {
	int fileCount = currentFilenameList.size();
	File [] returnList = (File[]) currentFilenameList.toArray(new File[] {});
        return returnList;
	}

      /**
       * Called by the file list when the user selects an output
       * file type. This will update the file list and also
       * deselect the currently selected file if it doesn't
       * match the selected file type.
       * @param ftype  New output file type. 
       */
    public void setCurrentOutputFileType(DFileType ftype)
        {
	    /** Not relevant - multi files only allowed on input */
	}

      /**
       * Returns the file type corresponding to a selected file,
       *  so that the chooser can add items
       * to its mruList. This happens only when the user clicks on
       * OK.
       */
    public DFileType getFileTypeForFile(File testFile)
        {
	DFileType returnType = null;
	for (int i = 0; i < filterFileTypes.length; i++)
	    {
	    if (filterFileTypes[i].accept(testFile))
	        {
                returnType = filterFileTypes[i];
		break;
		}
	    }
	return returnType;
	}

      /**
       * Returns the file type corresponding to the currently set file
       * if any. (returns null if none set)
       */
    public DFileType getFileTypeForCurrentFile()
        {
	DFileType returnType = null;	  
	if ((currentPath != null) && (currentFilename != null))
	    {
	    File testFile = new File(currentPath, currentFilename);
	    returnType = getFileTypeForFile(testFile);
	    }
	return returnType;
	}

    public DFileType[] getFileTypes()
        {
	return filterFileTypes;
	}

      /**
       * Sets the file type.
       */
    public void setFileTypes(DFileType[] fileTypes)
        {
	filterFileTypes = fileTypes;
	}

    public String getCurrentPath()
        {
	return currentPath;
	}

      /**
       * Explicitly set oldPath and oldFilename
       * arguments.
       */
    public void setOldPath(String path)
        {
	oldPath = path;
	}

    public void setOldFilename(String filename)
        {
	oldFilename = filename;
	}


    public void setLastSelectedPath(String path)
        {
	lastSelectedPath = path;
	}

    public String getLastSelectedPath()
        {
        return lastSelectedPath;
        }

    public DFileType getCurrentOutputFileType()
        {
	return currentOutputFileType;
	}

      /**
       * Clear all data items in the model to null;
       */
    public void clear()
        {
	currentPath = null;
	currentFilename = null;
	oldPath = null;
	oldFilename = null;
	partialName = null;
	currentOutputFileType = null;
        currentFilenameList.clear();
	}

      /**
       * set the partial name filter.
       * At the moment, we don't handle wildcards, we just
       * look at the starting characters.
       */
    public void setPartialName(String filter)
        {
        if (filter == null)
	    {
	    partialName = filter;
            }
	else
	    {
	    int pos = filter.indexOf("*");
	    if (pos >= 0)
	        partialName = filter.substring(0,pos);
	    else
	        partialName = filter;
	    }
	}

      /**
       * Get the partial name filter.
       * At the moment, we don't handle wildcards, we just
       * look at the starting characters.
       */
    public String getPartialName()
        {
	return partialName;
	}


      /**
       * get last error info.
       */
    public String getLastErrorKey()
        {
	return lastErrorKey;
	}

    public String getLastErrorFile()
        {
	return lastErrorFile;
	}


    public void setMemoryFileSelected(boolean bFlag)
        {
	bMemoryFileSelected = bFlag;
        }

    public boolean isMemoryFileSelected()
        {
        return bMemoryFileSelected;
	}

    public void setMaxAllowedFileCount(int count)
        {
	maxAllowedFileCount = count;
	}

      /**
       * Member class to compare strings, case-insensitive
       * NOTE that this comparator is not strictly consistent
       * with String.equals.
       */
    class CaseInsensitiveComparator implements Comparator<String>
        {
	public int compare(String s1, String s2)
            {
	    return s1.compareToIgnoreCase(s2);
	    }
	  
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DFileMultiChooserModel.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }






