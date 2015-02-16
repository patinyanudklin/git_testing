/**
 * ConfigFileProcessor
 *
 * ~~ Copyright 2001-2015 by Sally Goldin & Kurt Rudahl
 * ~~ EndC
 *
 * Created by Sally Goldin, 3/21/2001
 *
 * $Id: ConfigFileProcessor.java,v 1.9.2.1 2015/01/01 10:32:30 rudahl Exp $
 * $Log: ConfigFileProcessor.java,v $
 * Revision 1.9.2.1  2015/01/01 10:32:30  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.11  2015/01/01 09:56:15  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.10  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.9  2006/12/31 09:23:17  goldin
 * Add HELPDELAY to config file
 *
 * Revision 1.8  2006/12/30 11:23:18  goldin
 * Add version and build date strings
 *
 * Revision 1.7  2006/03/04 09:34:51  goldin
 * Get rid of comments in attrbute values
 *
 * Revision 1.6  2005/03/28 09:45:03  goldin
 * Change config filename to lower case
 *
 * Revision 1.5  2005/02/06 08:25:55  goldin
 * Fix javadoc warnings
 *
 * Revision 1.4  2002/02/08 18:02:21  goldin
 * Add LEVEL attribute
 *
 * Revision 1.3  2002/01/22 14:55:11  goldin
 * Add new DRAGONUI field
 *
 * Revision 1.2  2001/12/19 20:38:44  goldin
 * Add method to set SPATH, for installer
 *
 * Revision 1.1  2001/11/29 16:14:37  goldin
 * Move ConfigFileProcessor to common class
 *
 * Revision 1.13  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.12  2001/11/05 13:59:14  goldin
 * Put UI code in a package
 *
 * Revision 1.11  2001/10/17 10:29:36  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.10  2001/10/08 15:01:05  goldin
 * Copy keyset before processing; otherwise we actually remove items from the hashtable with ugly results
 *
 * Revision 1.9  2001/05/09 15:16:40  goldin
 * Begin implementing signature populaing callbacks for C/EDI
 *
 * Revision 1.8  2001/05/08 11:17:30  goldin
 * Determine standalone state based on config file
 *
 * Revision 1.7  2001/05/08 10:14:18  goldin
 * Add class to handle commands when UI running standalone
 *
 * Revision 1.6  2001/05/03 15:04:31  goldin
 * Add special file handling to command line and command forwarder
 *
 * Revision 1.5  2001/04/09 10:07:01  goldin
 * Try to make sure that there is
 *
 * Revision 1.4  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.3  2001/04/06 09:10:34  goldin
 * Fix bug - was not writing elements that were not in original file
 *
 * Revision 1.2  2001/03/21 13:05:39  goldin
 * Add language selection and config file processing functionality
 *
 * Revision 1.1  2001/03/21 11:10:18  goldin
 * Add new class to handle reading, querying and writing of DRAGON.CFG
 *
 */

package com.grs.dragon.common;
import com.grs.gui.*;
import java.io.*;
import java.util.*;

/**
 * This class encapsulates the reading, interpretation and writing
 * of the Dragon config file (DRAGON.CFG). */
public class ConfigFileProcessor
    {
      /**
       * If true, the script server is disabled and the UI is
       * running as a standalone app that shows screens but does
       * nothing.
       */
    protected boolean bStandAlone = false;

      /**
       * Static strings that serve as keys in the file.
       */
    protected static final String WORKING_LINES = "WORKING_LINES";
    protected static final String WORKING_PIXELS = "WORKING_PIXELS";
    protected static final String COUNTRY = "COUNTRY";
    protected static final String KPATH = "KPATH";
    protected static final String DPATH = "DPATH";
    protected static final String WPATH = "WPATH";
    protected static final String SPATH = "SPATH";
    protected static final String CPATH = "CPATH";
    protected static final String NOSCRIPTSERVER = "NOSCRIPTSERVER";
    protected static final String CFG_FILE = "dragon.cfg";
    protected static final String CFG_FILE_BACKUP = "dragon.cfgbak";
    protected static final String DRAGONUI = "DRAGONUI";
    protected static final String LEVEL = "LEVEL";
    protected static final String BUILDDATE = "BUILDDATE";
    protected static final String VERSION ="VERSION";
    protected static final String HELPDELAY ="HELPDELAY";

      /**
       * Array of keys, used for matching.
       */
    protected static final String[] keys =
         {WORKING_LINES, WORKING_PIXELS, COUNTRY,
          KPATH, DPATH, WPATH, SPATH, CPATH, NOSCRIPTSERVER,DRAGONUI,
	  LEVEL,BUILDDATE,VERSION,HELPDELAY};

      /**
       * Concatenated keys, used for quick rejection of lines
       * that do not contain a key
       */
    protected String compareString = null;

      /**
       * Filename - with or without directory.
       */
    protected String cfgFileName = null;
      /**
       * Backup Filename - with or without directory.
       */
    protected String backupFileName = null;

      /**
       * Hashtable to hold values for each item of interest.
       */
    protected Hashtable<String,String> configValues = 
                 new Hashtable<String,String>(24);

    protected int maxLen = 0;

      /**
       * use to detect errors during initialization. If true,
       * instance has been successfully initialized
       */
    protected boolean bInitialized = false;

      /**
       * Constructor opens and reads the
       * config file, extracting items that match the keys and
       * storing them in the hashtable. Note that the name of the
       * config file is currently hardcoded
       * @param homeDirectory  Directory where config file is located
       */
    public ConfigFileProcessor(String homeDirectory)
        {
	// Create the comparison string by concatenating
	// the keys, padded to all the same length.
	String blanks = "                                        ";
	maxLen = maxKeyLength();
        StringBuffer temp = new StringBuffer(128);
	int len = keys.length;
        for (int i = 0; i < len; i++)
	    {
	    temp.append(keys[i]);
	    if (keys[i].length() < maxLen)
	        temp.append(blanks.substring(0,(maxLen - keys[i].length()+ 1)));
	    temp.append("|");
            }
	compareString = temp.toString();
	if (homeDirectory != null)
	    {
	    cfgFileName = homeDirectory + File.separator +
	               CFG_FILE;
	    backupFileName = homeDirectory + File.separator +
	               CFG_FILE_BACKUP;
	    }
	else
	    {
	    cfgFileName = CFG_FILE;
	    backupFileName = CFG_FILE_BACKUP;
	    }
	try 
	    {
	    FileInputStream fis = new FileInputStream(cfgFileName);
	    InputStreamReader isr = new InputStreamReader(fis);
	    BufferedReader reader = new BufferedReader(isr);
	    String inputLine = null;
	    while ((inputLine = reader.readLine()) != null)
	        {
	        int pos = inputLine.indexOf("=");
		if (pos < 0)
		     continue;
		String key = inputLine.substring(0,pos);
		int keypos = compareString.indexOf(key);

		if (keypos >= 0)
		    {
                    int index = keypos/(maxLen + 1);
		    String value = inputLine.substring(pos+1);
		    // readLine appears to strip the newline but not the
		    // carriage return.
		    pos = value.indexOf(0xD);
		    if (pos > 0)
		       value = value.substring(0,pos);
		    pos = value.indexOf(';');  /* any comments */
		    if (pos > 0)
                       value = value.substring(0,pos).trim();
		    configValues.put(keys[index],value);
		    }
	        }
	    reader.close();
            Object tobj = configValues.get(NOSCRIPTSERVER);
            if (configValues.get(NOSCRIPTSERVER) != null)
                bStandAlone = true;
	    bInitialized = true;
	    }
	catch (IOException ioe)
	    {
	    System.out.println("ConfigFileProcessor: error opening or reading "
                                  + cfgFileName);
	    }
        }

	/**
	 * Writes out current values to new file, after renaming
	 * the old one to DRAGON.CFGBAK. Basically, any line
	 * that does not match a key is passed through unchanged.
	 * Otherwise, we replace the old value, if any, with the new.
	 * @return true if successful, else false.
	 */
    public boolean writeNewFile()
        {
	boolean bOk = true;
        File existingFile = new File(cfgFileName);
        if (!existingFile.exists())
	    {
	    System.out.println("ConfigFileProcessor: No config file found!");
	    bOk = false;
	    return bOk;
	    }
        // read the contents of the existing file into a char array
	char[] contents = new char[(int) (existingFile.length())];
	try
	    {
	    BufferedReader reader = 
                      new BufferedReader(new FileReader(cfgFileName));
	    reader.read(contents);
            reader.close();
	    File newFile = new File(backupFileName);
            if (newFile.exists())
	        {
	        newFile.delete();
	        }
	    bOk = existingFile.renameTo(newFile);
	    if (!bOk)
	        {
	        System.out.println("ConfigFileProcessor: cannot rename " + 
			       cfgFileName + " to " + backupFileName);
                insureConfigExistence(contents);
	        return bOk;
	        }
            BufferedWriter writer = 
                      new BufferedWriter(new FileWriter(cfgFileName));
	    reader = new BufferedReader(new CharArrayReader(contents));
	    TreeSet<String> allKeys = new TreeSet<String>(configValues.keySet());
	    String inputLine = null;
	    while ((inputLine = reader.readLine()) != null)
	        {
	        int pos = inputLine.indexOf("=");
		if (pos < 0)
		    {
		    writer.write(inputLine);
		    writer.newLine();
		    continue;
		    }
		String key = inputLine.substring(0,pos);
		int keypos = compareString.indexOf(key);
		if (keypos >= 0)
		    {
                    int index = keypos/(maxLen + 1);
		    String value = (String) configValues.get(keys[index]);
		    if (value == null) // this would be abnormal
		        {
		        writer.write(inputLine);
			}
		    else
		        {
			writer.write(key + "=" + value);
			// remove it from the set so we'll know that
			// it was encountered in the original file
			allKeys.remove(key);
			}
                    }
		else
		    {
		    writer.write(inputLine);
		    }
		writer.newLine();
	        }
	    // Now we have to write lines for any keys that
	    // did not already show up in the file.
	    Iterator keyIt = allKeys.iterator();
	    while (keyIt.hasNext())
	        {
		String key = (String) keyIt.next();
		String value = (String) configValues.get(key);
		if (value != null) // this would be abnormal
		    {
		    writer.write(key + "=" + value);
		    writer.newLine();
		    }
		}
	    reader.close();
	    writer.close();
	    }
	catch (IOException ioe)
	    {
	    System.out.println("ConfigFileProcessor: error opening or reading "
                                  + cfgFileName);
	    ioe.printStackTrace();
	    bOk = false;
	    }
        if (contents.length > 0)
	    insureConfigExistence(contents);
	return bOk;
	}


      /**
       * Factorization of writeNewFile. If the config file does not
       * exist, writes out the contents array to the config file.
       * This will mean that changes do not get made.
       */
    protected void insureConfigExistence(char[] contents)
        {
	File testFile = new File(cfgFileName);
	if (!testFile.exists())
	     {
	     try
	         {
                 BufferedWriter writer = 
                      new BufferedWriter(new FileWriter(cfgFileName));
		 writer.write(contents);
		 writer.close();
		 }
	     catch (IOException ioe)
	         {
		 System.out.println("ConfigFileProcessor.insureConfigExistence:"
				    + " Error writing " + cfgFileName);
		 ioe.printStackTrace();
		 }
	     }
	}

      /**
       * Factorization of constructor. Returns the length of the
       * longest key string..
       */
    protected int maxKeyLength()
        {
	int maxLen = 0;
	int len = keys.length;
	for (int i = 0; i < len; i++)
	    {
            if (keys[i].length() > maxLen)
                  maxLen = keys[i].length();
	    }
	return maxLen;
	}

      /**
       * Accessor and mutator methods for each type of info. All
       * values are stored and returned as strings.
       */
    public boolean isStandAlone()
        {
	return bStandAlone;
	}

    public String getWorkingLines()
        {
	return (String) configValues.get(WORKING_LINES);
	}

    public void setWorkingLines(String value)
        {
	configValues.put(WORKING_LINES,value);
	}
    public String getWorkingPixels()
        {
	return (String) configValues.get(WORKING_PIXELS);
	}

    public void setWorkingPixels(String value)
        {
	configValues.put(WORKING_PIXELS,value);
	}

    public String getCountry()
        {
	return (String) configValues.get(COUNTRY);
	}

    public void setCountry(String value)
        {
	configValues.put(COUNTRY,value);
	}

    public String getKpath()
        {
	return (String) configValues.get(KPATH);
	}

    public void setKpath(String value)
        {
	if (!value.endsWith(File.separator))
	     value = value + File.separator;
	configValues.put(KPATH,value);
        ApplicationManager.setTempPath(value);
	}

    public String getDpath()
        {
	return (String) configValues.get(DPATH);
	}

    public void setDpath(String value)
        {
	configValues.put(DPATH,value);
        ApplicationManager.setReadPath(value);
        //System.out.println("Setting " + DPATH + " to " + value);
	}

    public String getWpath()
        {
	return (String) configValues.get(WPATH);
	}

    public void setWpath(String value)
        {
        ApplicationManager.setWritePath(value);
	configValues.put(WPATH,value);
	}

    public String getCpath()
        {
	return (String) configValues.get(CPATH);
	}

    public void setCpath(String value)
        {
	configValues.put(CPATH,value);
	}

    public String getSpath()
        {
	return (String) configValues.get(SPATH);
	}
    // it is not possible to change SPATH inside DRAGON
    // but we need this method for the installation process.
    public void setSpath(String value)
        {
	configValues.put(SPATH,value);
	}

    public String getBuildDate()
        {
	return (String) configValues.get(BUILDDATE);
	}

    public void setBuildDate(String value)
        {
	configValues.put(BUILDDATE,value);
	}

    public String getVersion()
        {
	return (String) configValues.get(VERSION);
	}

    public void setVersion(String value)
        {
	configValues.put(VERSION,value);
	}

    public String getHelpDelay()
        {
	return (String) configValues.get(HELPDELAY);
	}

    public void setHelpDelay(String value)
        {
	configValues.put(HELPDELAY,value);
	}


      /**
       * General fn to set new attribute/value pairing.
       */
    public void setAttributeValue(String attribute,
				      String value)
        {
        configValues.put(attribute,value);
	}

      /**
       * General fn to get the value of an attribute; both assumed
       * to be strings. Note, may return null
       */
    public String getAttributeValue(String attribute)
        {
	return (String) configValues.get(attribute);
	}


      /**
       * Check to see if constructor was successful.
       */
    public boolean isInitialized()
        {
	return bInitialized;
	}

    }

    


