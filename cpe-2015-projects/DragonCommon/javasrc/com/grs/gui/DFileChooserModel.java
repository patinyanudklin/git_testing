/**
 *  DFileChooserModel
 *
 *  Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 *  Created by Sally Goldin, 4/3/2001
 *
 *  $Id: DFileChooserModel.java,v 1.12 2007/06/15 11:06:06 goldin Exp $
 *  $Log: DFileChooserModel.java,v $
 *  Revision 1.12  2007/06/15 11:06:06  goldin
 *  Working on path validation issues
 *
 *  Revision 1.11  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.10  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.9  2004/12/05 10:00:55  goldin
 *  Fix pattern handling on first invocation
 *
 *  Revision 1.8  2002/09/27 15:45:09  goldin
 *  Change DriveTester to use JNI
 *
 *  Revision 1.7  2002/09/25 17:22:43  goldin
 *  Don't append default path to partial filename before calling file chooser
 *
 *  Revision 1.6  2002/09/13 23:56:33  goldin
 *  Continue enhancements to file box behavior
 *
 *  Revision 1.5  2002/09/12 17:21:28  goldin
 *  Work on filter behavior and setting of OK on off focus
 *
 *  Revision 1.4  2002/08/31 00:03:23  goldin
 *  continue major redesign of FileChooser
 *
 *  Revision 1.3  2002/08/27 20:04:12  goldin
 *  convert filechooser to potentially using multiple file types
 *
 *  Revision 1.2  2002/04/02 00:13:28  goldin
 *  Put in infrastructure for testing for file overwrite warning flag
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.22  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.21  2001/11/05 13:59:14  goldin
 *  Put UI code in a package
 *
 *  Revision 1.20  2001/10/30 18:06:36  goldin
 *  Maintain last selected path to use as default
 *
 *  Revision 1.19  2001/10/17 10:29:36  goldin
 *  Modify to use ApplicationManager to get error display, etc.
 *
 *  Revision 1.18  2001/07/25 11:52:41  goldin
 *  Fix problem with handling of (current)
 *
 *  Revision 1.17  2001/07/18 15:25:30  goldin
 *  Working to fix problems with handling of 'current' color scheme
 *
 *  Revision 1.16  2001/06/29 17:30:16  goldin
 *  Implemented handing of state info from reply files
 *
 *  Revision 1.15  2001/06/28 14:06:07  goldin
 *  Don't validate files with wildcards
 *
 *  Revision 1.14  2001/06/27 15:17:47  goldin
 *  Fix CalcParser bugs, table formatting
 *
 *  Revision 1.13  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.12  2001/06/05 19:36:21  goldin
 *  Add Trace; investigate file dialog bug
 *
 *  Revision 1.11  2001/05/31 17:10:53  goldin
 *  Work on problems with file dlg; esp. handling of empty drives
 *
 *  Revision 1.10  2001/05/07 12:06:52  goldin
 *  Fix bugs in path handling
 *
 *  Revision 1.9  2001/04/18 15:32:45  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.8  2001/04/10 11:18:46  goldin
 *  Fix problem with modal dialog in FileValidator; extend IntegerValidator
 *
 *  Revision 1.7  2001/04/09 14:44:15  goldin
 *  Work on file validation. Not complete
 *
 *  Revision 1.6  2001/04/06 18:02:54  goldin
 *  Fixing bugs
 *
 *  Revision 1.5  2001/04/06 09:10:51  goldin
 *  Use control label as title for chooser
 *
 *  Revision 1.4  2001/04/04 15:24:50  goldin
 *  Added partial filename filtering, validation, to file chooser
 *
 *  Revision 1.3  2001/04/04 12:16:55  goldin
 *  Checkpoint of filechooser work; partial name filtering implemented
 *
 *  Revision 1.2  2001/04/03 17:46:43  goldin
 *  Continued work on FileChooser; moved state information into new DFileChooserModel class
 *
 *  Revision 1.1  2001/04/03 16:25:31  goldin
 *  New class to maintain filechooser state
 *
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
public class DFileChooserModel
    {

      /**
       * Currently-selected filename string.
       */
    protected String currentFilename = null; 

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




      //************************************************************
      /**
       * Constructor sets references to components.
       */
    public DFileChooserModel(DragonFileChooser chooser,
			     DragonDirTree dirTree,
			     DragonFileList fileList)
        {
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
	String msg = "{ DFileChooserModel: setting filename to " +
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
	chooser.setDetailsEnabled(bEnable);
	chooser.setOkEnabled(bEnable);
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
	String msg = "{ DFileChooserModel: setting path to " +
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
        ArrayList files = new ArrayList(300);
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
	ArrayList temp = new ArrayList(maxLen);
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
	if (pName == null)
	    pName = "";
	
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
       

    public String getCurrentFilename()
        {
        return currentFilename;
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
	currentOutputFileType = ftype;
	if (currentTreeNode != null)
	    {
	    setFileList(currentTreeNode,false);
	    }
	if ((currentFilename != null) && (ftype != null))
	    {
	    File testFile = new File(currentPath,currentFilename);
	    if (!ftype.accept(testFile))
	        {
		setCurrentFilename(null);
		}
	    }
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

      /**
       * Member class to compare strings, case-insensitive
       * NOTE that this comparator is not strictly consistent
       * with String.equals.
       */
    class CaseInsensitiveComparator implements Comparator
        {
	public int compare(Object o1, Object o2)
            {
	    String s1 = o1.toString();
	    String s2 = o2.toString();
	    return s1.compareToIgnoreCase(s2);
	    }
	  
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DFileChooserModel.java,v 1.12 2007/06/15 11:06:06 goldin Exp $ \n";
	}
    }






