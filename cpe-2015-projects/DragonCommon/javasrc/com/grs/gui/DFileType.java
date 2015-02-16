/**
 * DFileType
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 3/23/2001
 *
 *  $Id: DFileType.java,v 1.13 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: DFileType.java,v $
 *  Revision 1.13  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.12  2007/01/02 09:33:35  goldin
 *  Fixed behavior when file has no extension
 *
 *  Revision 1.11  2006/12/29 11:36:47  goldin
 *  Add new rule file type
 *
 *  Revision 1.10  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.9  2002/09/13 23:56:33  goldin
 *  Continue enhancements to file box behavior
 *
 *  Revision 1.8  2002/08/31 00:03:23  goldin
 *  continue major redesign of FileChooser
 *
 *  Revision 1.7  2002/08/28 16:33:05  goldin
 *  Work on merging MRU lists
 *
 *  Revision 1.6  2002/08/27 20:04:12  goldin
 *  convert filechooser to potentially using multiple file types
 *
 *  Revision 1.5  2002/06/28 15:28:00  goldin
 *  Implement 'Details' in file chooser
 *
 *  Revision 1.4  2002/05/16 13:17:11  goldin
 *  Filtering requires upper case extensions
 *
 *  Revision 1.3  2002/03/23 01:11:45  rudahl
 *  added some file types
 *
 *  Revision 1.2  2002/03/06 20:59:29  goldin
 *  Add new HTML file type
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.10  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.9  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.8  2001/10/19 16:22:00  goldin
 *  Remove reference to DragonUI
 *
 *  Revision 1.7  2001/10/08 11:55:31  goldin
 *  Change msg key for SCRIPT2 file type (used for log files)
 *
 *  Revision 1.6  2001/04/18 15:32:45  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.5  2001/04/10 11:18:46  goldin
 *  Fix problem with modal dialog in FileValidator; extend IntegerValidator
 *
 *  Revision 1.4  2001/04/04 12:16:55  goldin
 *  Checkpoint of filechooser work; partial name filtering implemented
 *
 *  Revision 1.3  2001/04/03 17:46:43  goldin
 *  Continued work on FileChooser; moved state information into new DFileChooserModel class
 *
 *  Revision 1.2  2001/03/26 17:32:08  goldin
 *  Further work implementing FileChooser
 *
 *  Revision 1.1  2001/03/23 17:01:51  goldin
 *  Initial implementation of file chooser
 *
 */

package com.grs.gui;
import java.io.*;
import java.util.*;

/**
 * This class encapsulates the concept of a Dragon file type.
 * Each instance of this class (static instances of each relevant
 * type are created here; the constructor is private so no one
 * outside the class can create instances) has a description (which
 * is extracted from the translated message file), a file pattern which
 * can be used to verify whether a string matches the appropriate
 * type, and a cache of recently-used files of this type
 * <p>
 * By making this class an implementation of java.io.FileFilter, we can also
 * use it to determine what files should be included in a file list.*/
public class DFileType implements FileFilter
    {
    public static String GENERIC_FILES_LABEL = null;
    
      /**
       * Maximum number of file to save in the MRU cache.
       */
    protected static final int MAX_MRU = 4;

      /**
       * Special file pattern used to indicate a directory.
       */
    public static final String DIR_PATTERN = "*";

      /**
       * Special file pattern used for all files.
       */
    public static final String ALL_PATTERN = "*.*";

      /**
       * Hash table that allows an instance of a file type to
       * be looked up, given its file pattern. This is needed
       * in order to transform the dataRange in the XML file to
       * a specific DFileType instance.
       * Whenever an instance of DFileType is created, it will
       * be put in this hashtable, keyed by the pattern.
       * NOTE this means that each file type must have a unique
       * pattern.
       */
    protected static Hashtable instanceHash = new Hashtable(20);
      
      /**
       * FIFO list used to maintain cache of most recently used files.
       * for each file type.
       */
    protected LinkedList mruFiles = null;

      /**
       * Pattern used to determine if a file matches. If this
       * pattern matches special pattern "*", then we are looking
       * for a directory, not a file. File patterns should be in
       * lower case.
       */
    protected String filePattern = null;

      /**
       * Key string for retrieving the internationalized description of
       * this type of file. 
       */
    protected String descriptionKey = null;

      /**
       * Key string for retrieving the filetype from the
       * hash. This must match the string used to identify the
       * the file type in the XML description.
       */
    protected String lookupKey = null;

      /**
       * Callback to call when details button is pressed on
       * the file chooser. If this is null, the details button
       * will not be enabled. This callback will be set by the
       * application, since different apps may want different 
       * behaviors, for different file types.
       */
    protected Callback detailCallback = null;

      /**
       * Constructor, sets the file pattern and key, and creates
       * the cache. This constructor is protected, so no one except
       * a subclass can create new instances.
       */
    protected DFileType(String filePattern, String descriptionKey,
			String lookupKey)
        {
	this.filePattern = filePattern;
	this.descriptionKey = descriptionKey;
	this.lookupKey = lookupKey;
        mruFiles = new LinkedList();
        instanceHash.put(lookupKey, this);
	if (GENERIC_FILES_LABEL == null)
	    GENERIC_FILES_LABEL = 
	    ApplicationManager.getTextSource().getI18NText("%h9320.2","Files");
	}

      /**
       * Retrieve and return the description for this file type,
       * in the current language.
       * @return Description of this file type.
       */
    public String getDescription()
        {
        String full = ApplicationManager.getTextSource().getI18NText(
               descriptionKey,"Files");
	int pos = full.indexOf("(");
	if (pos > 0)
            return full.substring(0,pos);
	else
	    return full;
        }

      /**
       * Add a file to the MRU list. If the list has reached its
       * limit, remove the oldest (last in the list).
       * @param filename Filename to add to the list (without path)
       */
    public void addUsedFile(String filename)
        {
        FileReference usedFileRef = null;
	FileReference element = null;
        Iterator it = mruFiles.iterator();
	while (it.hasNext())
	    {
	    element = (FileReference) it.next();
	    if (element.fileName.compareToIgnoreCase(filename) == 0)
	        {
  	        mruFiles.remove((Object)element);  // don't add twice
	        // we'll put it at the start of the list
		usedFileRef = element;
		break;
		}
	    }
	if (mruFiles.size() >=  MAX_MRU)
	    {
	    mruFiles.removeLast();
	    }
	if (usedFileRef == null)
	    {
	    usedFileRef = new FileReference();
	    }
	usedFileRef.fileName = filename;
	usedFileRef.refTime = new Date().getTime();
	mruFiles.addFirst(usedFileRef);
	}

      /**
       * Return the current contents of the MRU list as an array
       */
    public FileReference[] getUsedFiles()
        {
	Object[] temp = mruFiles.toArray();
	FileReference[] usedFiles = new FileReference[temp.length];
        for (int i = 0; i < temp.length; i++)
	    {
	    usedFiles[i] = (FileReference) temp[i];
	    }
	return usedFiles;
        }

      /**
       * Determine whether a passed file matches the
       * filename constraints for this type. For directories,
       * this is based on an actual check of whether the
       * entry is a directory.
       * <p>
       * At some point, we will want to change this to 
       * make it dependent on file content. At that point,
       * we'll probably need to write new classes for validating
       * different file types (rather like the validator approach).
       * @param testFile File to be tested
       * @return true if File matches constraints of type
       */
    public boolean accept(File testFile)
        {
	boolean bBelongs = false;
	if (filePattern == ALL_PATTERN)
	    {
	    bBelongs = true;
	    }
	else if (filePattern == DIR_PATTERN)
	    {
	    bBelongs = testFile.isDirectory();
	    }
	else
	    {
	    // screen out directories.
            if (testFile.isDirectory())
	        return false;
	    String testString = testFile.getName().toLowerCase();
	    // file pattern may have multiple alternatives
	    StringTokenizer tokenizer = new StringTokenizer(filePattern,";");
	    while ((tokenizer.hasMoreTokens())&& (!bBelongs))
	         {
		 String test = tokenizer.nextToken();
		 bBelongs = testString.endsWith(test);
		 }
	    }
	return bBelongs;
	}


      /**
       * Take a file name string and add an appropriate suffix
       * for this DFileType, if one is not already appended.
       * @param fileName  Filename to be made canonical
       * @return filename with suffix appended, if appropriate
       */
    public String getCanonicalName(String fileName)
        {
	if (fileName.length() == 0)
	    return fileName;
        if (this.equals(DFileType.ALL))
            return fileName;
	boolean bFoundMatch = false;
	String currentSuffix = null;
	String firstSuffix = null;
	StringBuffer buffer = new StringBuffer();
	buffer.append(fileName);
	String lowerFilename = fileName.toLowerCase();
	int pos = lowerFilename.lastIndexOf(".");
	if (pos > 0)
	    currentSuffix = lowerFilename.substring(pos);
	StringTokenizer tokenizer = new StringTokenizer(filePattern,";");
	while (tokenizer.hasMoreTokens())
	   {
	   String test = tokenizer.nextToken();
	   if (firstSuffix == null)
	       firstSuffix = test;
	   if ((currentSuffix != null) &&
	       (test.compareTo(currentSuffix) == 0))
	       {
               bFoundMatch = true;
	       break;
	       }
	   }
	if (!bFoundMatch)
	   {
	   buffer.append(firstSuffix);
	   }
	return buffer.toString();
	}
	  
      /**
       * Create a way to display a file type in a debug msg. Will
       * also be used if DFileType objects are used to populate a
       * list or combo.
       */
    public String toString()
        {
	return getDescription() + " - " + getFilePattern();
	}

      /**
       * Return the file pattern
       */
    public String getFilePattern()
        {
	return filePattern;
        }

      /**
       * Return an instance of DFileType, based on its lookupKey.
       */
    public static DFileType getFileType(String lookupKey)
        {
	return (DFileType) instanceHash.get(lookupKey);
	}

      /**
       * Set a detail callback.
       */
    public void setDetailCallback(Callback cb)
        {
	detailCallback = cb;
	}

      /**
       * return the detail callback if any.
       */
    public Callback getDetailCallback()
        {
	return detailCallback;
	}

      
      //**************************************************
      // Create specific instances of the file types we need.

    public static DFileType ALL = new DFileType(ALL_PATTERN,"%h9340.0",
						ALL_PATTERN);
    public static DFileType PATH = new DFileType(DIR_PATTERN,
						 TextKeys.LOCATIONS,
						 DIR_PATTERN);
    public static DFileType IMAGE = new DFileType(".img", "%h9340.1",
						  ".IMG");
    public static DFileType COLOR = new DFileType(".clf", "%h9340.2",
						  ".CLF");
    public static DFileType POLYGON = new DFileType(".ply", "%h9340.3",
						    ".PLY");
    public static DFileType SIGNATURE = new DFileType(".sig", "%h9340.4",
						      ".SIG");
    public static DFileType TABLE = new DFileType(".tab", "%h9340.5",
						  ".TAB");
    public static DFileType SCRIPT = new DFileType(".spt","%h9340.6",
						   ".SPT");
    public static DFileType SCRIPT2 = new DFileType(".spt;.log","%h9340.7",
						   ".RUN");
    public static DFileType LOG = new DFileType(".log","%h9340.12",
						".LOG");
    public static DFileType VECTOR = new DFileType(".vec","%h9340.8",
						   ".VEC");
    public static DFileType GCP = new DFileType(".gcp","%h9340.9",
						".GCP");
    public static DFileType COEFF = new DFileType(".cof","%h9340.10",
						  ".COF");
    public static DFileType CLI = new DFileType(".cli","%h9340.11",
						".CLI");
    public static DFileType HTML = new DFileType(".html;.htm","%h9340.21",
						 ".HTML");
    public static DFileType TIFF = new DFileType(".tif;.tiff","%h9340.22",
						 ".TIF");
    public static DFileType JPEG = new DFileType(".jpg;.jpeg","%h9340.23",
						 ".JPG");
    public static DFileType BIL = new DFileType(".bil","%h9340.24",
						".BIL");
    public static DFileType BSQ = new DFileType(".bsq","%h9340.25",
						".BSQ");
    public static DFileType RULE = new DFileType(".rule","%h9340.100",
						".RULE");


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DFileType.java,v 1.13 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
