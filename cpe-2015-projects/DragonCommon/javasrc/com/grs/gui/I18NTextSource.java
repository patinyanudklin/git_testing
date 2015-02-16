/**  I18NTextSource.java
 *
 *   ~~ Copyright  2001-2015  by Sally Goldin & Kurt Rudahl
 *   ~~ EndC
 *
 *   Created by Sally Goldin, 1/19/2001
 *
 *   $Id: I18NTextSource.java,v 1.13.2.1 2015/01/01 13:51:54 rudahl Exp $
 *   $Log: I18NTextSource.java,v $
 *   Revision 1.13.2.1  2015/01/01 13:51:54  rudahl
 *   consolidating Dragon and OpenDragon
 *
 *   Revision 1.14  2007/07/30 09:12:19  goldin
 *   Get rid of unchecked warnings
 *
 *   Revision 1.13  2007/01/05 07:41:58  rudahl
 *   added Whatis info
 *
 *   Revision 1.12  2006/12/09 12:40:28  goldin
 *   fix null pointer error
 *
 *   Revision 1.11  2006/11/30 05:25:47  goldin
 *   Modify textsource to handle multiline messages; change constructor to take a possibly null key prefix string
 *
 *   Revision 1.10  2006/07/23 09:12:22  goldin
 *   Attempt to switch to using Java 1.5 (Axel/Windows only)
 *
 *   Revision 1.9  2006/01/15 13:04:44  goldin
 *   Defensive coding in substituteTokens
 *
 *   Revision 1.8  2005/12/27 10:42:06  goldin
 *   Make substituteJavaTokens method public
 *
 *   Revision 1.7  2005/07/31 08:34:31  goldin
 *   Working in I18N of Installer
 *
 *   Revision 1.6  2005/07/24 13:30:59  goldin
 *   Allow tabs as language file delimiters - continue if file can't be found
 *
 *   Revision 1.7  2005/07/22 11:09:38  goldin
 *   New class for processing and indexing fonts
 *
 *   Revision 1.6  2005/07/11 13:36:29  goldin
 *   Allow use of tabs or spaces as delims
 *
 *   Revision 1.5  2005/03/28 09:45:32  goldin
 *   Change msg files to lower case
 *
 *   Revision 1.4  2005/02/06 08:08:11  goldin
 *   Fix JavaDoc warnings
 *
 *   Revision 1.3  2002/06/13 22:04:22  goldin
 *   Provide a noarg constructor for convenience
 *
 *   Revision 1.2  2001/11/29 16:13:12  goldin
 *   Allow language files to exist in language subdirs
 *
 *   Revision 1.1  2001/11/16 16:38:20  goldin
 *   Move non-Dragon-specific files to new package
 *
 *   Revision 1.13  2001/11/05 13:59:15  goldin
 *   Put UI code in a package
 *
 *   Revision 1.12  2001/09/05 15:08:53  goldin
 *   Change I18NTextSource constructors
 *
 *   Revision 1.11  2001/06/08 18:12:32  goldin
 *   Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *   Revision 1.10  2001/04/18 15:32:46  goldin
 *   Added home directory command line argument
 *
 *   Revision 1.9  2001/04/18 13:13:35  goldin
 *   Add test constructor
 *
 *   Revision 1.8  2001/04/17 19:41:38  goldin
 *   Minor changes
 *
 *   Revision 1.7  2001/04/02 17:13:36  rudahl
 *   made UTF8 be UTF-8
 *
 *   Revision 1.6  2001/03/23 17:01:51  goldin
 *   Initial implementation of file chooser
 *
 *   Revision 1.5  2001/03/21 13:05:39  goldin
 *   Add language selection and config file processing functionality
 *
 *   Revision 1.4  2001/02/28 16:24:29  goldin
 *   implementing defaults, enhancements to help editor
 *
 *   Revision 1.3  2001/02/08 16:14:39  goldin
 *   Added HelpEditor capability
 *
 *   Revision 1.2  2001/02/07 20:41:06  goldin
 *   Implemented actual reading of text help file
 *
 *   Revision 1.1  2001/01/19 18:43:19  goldin
 *   Add handling of xlateText, menu building
 *
 *
 */
package com.grs.gui;
import java.util.*;
import java.io.*;
import java.text.*;

/**
 * This class encapsulates all access to translated help files
 * in DRAGON. Its primary method takes a key plus an English
 * string, and returns the appropriate text for the specified
 * language. (The language is specified in the constructor.)
 * <p>
 * Theoretically, multiple instances of I18NTextSource could be
 * used simultaneously, allowing presention of the same information
 * in multiple languages.*/
public class I18NTextSource
    {
    /** 
     * String used to signal beginning of a key 
     * If null, all messages must be one line
     */
    protected String keyPrefix = null;
      
     /** 
      * Used while reading dictionary - holds first line of
      * next entry.
      */
    protected String firstLine = null;
      /**
       * Current language for this text source (2 letter abbreviation)
       */
    protected String language = "EN";

      /**
       * Hash table for saving text and keys.
       */
    protected Hashtable<String,String> textTable = new Hashtable<String,String>();

      /**
       * Allows an outside program to test whether the
       * constructor was successful.
       */
    protected boolean bInitialized = false;

      /**
       * Constructor assembles name for dictionary file based on
       * language code and directory. Reads the data in directly as UTF-8.
       * @param language Code for the language this class will use
       * @param homeDirectory  Directory where dictionary file resides
       * @param keyPrefix If not null, what prefix starts keys
       */
    public I18NTextSource(String language,String homeDirectory, String keyPrefix)
        {
        language = language.toLowerCase();
	this.language = language;
        this.keyPrefix = keyPrefix;
	String infile = "drag5-" + language + ".messages";
	// put into lower case for Linux. Windows doesn't care.
	infile = infile.toLowerCase();
        if (homeDirectory == null)
            homeDirectory = ".";
	File tester = new File(homeDirectory + File.separator + language +
	             File.separator + infile);
	if (tester.exists())
	    {
	    infile = homeDirectory + File.separator + language +
		          File.separator + infile;
	    }
	else
	    {
	    infile = homeDirectory + File.separator + infile;
	    }
 	try 
	    {
            readDictionaryFile(infile, keyPrefix);
	    }
	catch (IOException ioe)
	    {
	      //ioe.printStackTrace();
	    System.out.println("I18NTextSource: error opening or reading " +
			       infile);
	    }
	finally
	    {
            bInitialized = true;
	    }
	}

      /**
       * Alternative constructor is given full path name for 
       * dictionary file. Note that language code and the keyPrefix
       *  will not be set.
       * @param infile Name of dictionary file, including path.
       */
    public I18NTextSource(String infile)
        {
 	try 
	    {
            readDictionaryFile(infile,keyPrefix);
            bInitialized = true;
	    }
	catch (IOException ioe)
	    {
	    ioe.printStackTrace();
	    System.out.println("I18NTextSource: error opening or reading " +
			       infile);
	    }
	}

      /**
       * Convenience Constructor. Creates a text source without a 
       * dictionary. Will always return the reminder string.
       */
    public I18NTextSource()
        {
	textTable.put("dummyKey","dummyMessage");
	}

      /**
       * Factorization of constructors, which use different ways
       * of setting the file name. Reads, parses & store the
       * dictionary file data as UTF-8.
       * Can also be called to initialize a "null" text source
       * created by the empty constructor.
       * @param infile  File to read.
       * @param keyPrefix If there's a special character for the
       *                 key prefix (e.g. %) this string will hold
       *                 it. Otherwise, it will be null. 
       *                 If there's a keyPrefix, we use readNextEntry,
       *                 instead of just readLine, because readNextEntry
       *                 correctly handles line breaks.
       */
    public void readDictionaryFile(String infile,String keyPrefix)
             throws IOException
        {
	boolean bDone = false;
	FileInputStream fis = new FileInputStream(infile);
	InputStreamReader isr = new InputStreamReader(fis,"UTF-8");
	BufferedReader reader = new BufferedReader(isr);
        String inputLine = null;
       
	while (!bDone) 
	    {
	    if (keyPrefix != null)
                inputLine = readNextEntry(reader,keyPrefix);
            else
                inputLine = reader.readLine();
            if (inputLine == null)
                bDone = true;
            else
                {
	        if (inputLine.startsWith("."))
	           {
 	           continue;
	           }
	        parseAndHash(inputLine);
                }
	    }
	reader.close();
	}


      /** 
       * Read the next "entry" from the open dictionary file.
       * Concatenate lines into a single string. Stop when
       * you get to the next percent sign at the beginning
       * of a line.
       * @param reader  Reader, assumed open and positioned
       *                at the next entry of the dictionary file.
       * @param keyPrefix String that starts a new message key
       * @return Concatenated string or null if EOF or error.
       */   
    public String readNextEntry(BufferedReader reader,
				String keyPrefix) throws IOException
        {
	String result = null;
        int pos = 0;
	String tempLine = null;
	StringBuffer entry = new StringBuffer();
        if ((tempLine = reader.readLine()) != null)
            {
	    if (firstLine == null)
                {
		pos = tempLine.indexOf(0x0D);
                if (pos > 0)
		    tempLine = tempLine.substring(0,pos);  

		entry.append(tempLine);
                }
	    else
                {
                entry.append(firstLine);
                }
            firstLine = null;
            while ((tempLine != null) &&
                   (!tempLine.startsWith(keyPrefix)))
		{
		pos = tempLine.indexOf(0x0D);
                if (pos > 0)
		    tempLine = tempLine.substring(0,pos);  
		entry.append(tempLine);
                if (!tempLine.endsWith(" "))
		    entry.append(" ");
                tempLine = reader.readLine();
                }
            if ((tempLine != null) && (tempLine.startsWith(keyPrefix)))
                firstLine = tempLine;
            }        
        if (entry.length() > 0)
            result = entry.toString();
	//System.out.println("readNextEntry - result is |" + result);
        return result;
        }

      /**
       * Given a key, look up and return the internationalized
       * string corresponding to that key. If not found, return
       * the default string passed in.
       * <p>
       * Any formatting that must be applied to the string will
       * be handled by the caller.
       * @param key  String that identifies the text across all translations
       * @param defText String to be returned if value associated with the
       *                key cannot be found.
       * @return Internationalized text that corresponds to the key
       */
    public String getI18NText(String key, String defText)
        {
	if ((key == null) || (key.length() == 0))
	    return defText;
	String message = (String) textTable.get(key);
	if (message == null)
	    return defText;
	else
	    return message;
	}

      /**
       * Given a key, look up and return the internationalized
       * string corresponding to that key. Then substitute any
       * tokens of the form %1, %2 etc. with values from the
       * passed String array. If not found, try and do substitution
       * on the default string passed in.
       * @param key  String that identifies the text across all translations
       * @param defText String to be returned if value associated with the
       *                key cannot be found.
       * @param substValues Array of strings to be substituted for tokens
       *                   in the message.
       * @return Internationalized text that corresponds to the key
       */
    public String getI18NText(String key, String defText, 
			      String[] substValues)
        {
	String message = getI18NText(key,defText);
	if ((substValues.length > 0) &&
	    (message.indexOf("%1") >= 0))
	  {
	  String newFormat = substituteJavaTokens(message);
	  message = MessageFormat.format(newFormat,(Object[]) substValues);
	  }
	return message;
	}

    /**
     * Changes a Dragon-style message format, which uses
     * placeholders of the form "%1", to a Java-style message
     * format which uses placeholders of the form "{0}"
     * @param format  Dragon style format
     * @return Java style format
     */
    public String substituteJavaTokens(String format)
        {
	int start = 0;
	int end = format.length();
	int tokenNum = 0;
	char stringChars[] = format.toCharArray();
	boolean bDone = false;
	StringBuffer buffer = new StringBuffer();
	while (!bDone)
	   {
	   int pos = format.indexOf("%",start);
	   if (pos < 0)
	      {
	      buffer.append(format.substring(start,end));
	      bDone = true;
	      }
	   else
	      {
	      buffer.append(format.substring(start,pos));
	      buffer.append("{");
	      int pos2 = pos+1;
	      while ((pos2 < end) && (Character.isDigit(stringChars[pos2])))
		 pos2++;
              try 
		{
	        tokenNum = Integer.parseInt(format.substring(pos+1,pos2));
		}
              catch (NumberFormatException nfe)
                {
                tokenNum = 100;
                }
	      buffer.append(String.valueOf(tokenNum-1) + "}");
	      start = pos2;
	      }
	   }
	return buffer.toString();
        }


    
    public String getLanguage()
        {
	return language;
	}

    public boolean isInitialized()
        {
	return bInitialized;
	}

      /**
       * Factorization of constructor. Parses and hashes
       * the key and value from one string.
       */
    protected void parseAndHash(String inputLine)
        {
        int pos = inputLine.indexOf("%");
	// If no % in key, just take the first word
	// This will allow us to use the language codes as keys
	if (pos < 0) 
	     pos = 0;
	// check for tab first 
	int pos2 = inputLine.indexOf("\t",pos);
	if (pos2 < 0)	
	    pos2 = inputLine.indexOf(" ",pos);
        if (pos2 < 0)
	   {
           return;
	   }
	String key = inputLine.substring(pos,pos2).trim();
	String message = inputLine.substring(pos2+1);
	// readLine appears to strip the newline but not the
	// carriage return.
	pos = message.indexOf(0xD);
	if (pos > 0)
	     message = message.substring(0,pos);
        if ((key != null) && (message != null))
	    textTable.put(key,message);
        }

      /**
       * Test driver 
       */
    public static void main(String[] args)
        {
	if (args.length < 2)
	    {
	    System.out.println(
               "Usage: java I18NTextSource <languagecode> <directory>");
	    System.exit(0);
	    }
	I18NTextSource source = new I18NTextSource(args[0],args[1],"%");
	
        try
	    {
	    BufferedReader reader = new BufferedReader(new InputStreamReader(
						    System.in));
            while (true)
	        {
		System.out.println("Enter text key: ");
		String key = reader.readLine();
                String value = source.getI18NText(key,"NOT FOUND");
		System.out.println("VALUE: " + value);
		}
	    }
	catch (Exception e)
	    {
	    e.printStackTrace();
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: I18NTextSource.java,v 1.13.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }


