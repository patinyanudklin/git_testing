/**
 * IpcFile
 *
 * ~~ Copyright 2002-2015 by Sally Goldin & Kurt Rudahl
 * ~~ EndC
 *
 * Created by Sally Goldin, 4/23/2001. Originally generated
 * from Together model.
 *
 * $Id: IpcFile.java,v 1.12 2015/01/01 09:46:04 rudahl Exp $
 * $Log: IpcFile.java,v $
 * Revision 1.12  2015/01/01 09:46:04  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.11  2011/01/16 14:13:52  goldin
 * log an error if delete of an IPC file fails
 *
 * Revision 1.10  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.9  2006/01/14 09:24:40  goldin
 * Add time of day to the tracing
 *
 * Revision 1.8  2005/11/04 10:53:27  goldin
 * Working on setting and getting persistent data
 *
 * Revision 1.7  2005/07/24 13:11:13  goldin
 * Put blob processing back in temporarily
 *
 * Revision 1.7  2005/07/11 04:41:08  goldin
 * Put blob processing back in
 *
 * Revision 1.6  2005/03/29 09:11:25  goldin
 * Remove blob processing
 *
 * Revision 1.5  2005/02/06 08:35:00  goldin
 * Fix javadoc warnings
 *
 * Revision 1.4  2002/07/19 23:04:04  goldin
 * Add special case for monitored file that is consumed before it can be read
 *
 * Revision 1.3  2002/06/27 19:29:32  goldin
 * Add special case error handling for non-unicode chars in files
 *
 * Revision 1.2  2002/01/02 13:16:12  goldin
 * Simplify substitution code - use any percent string
 *
 * Revision 1.1  2001/11/19 20:30:32  goldin
 * Move IPC classes to new package
 *
 * Revision 1.38  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.37  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.36  2001/11/02 10:40:06  goldin
 * Handle case where file exists but has not been written
 *
 * Revision 1.35  2001/10/31 12:44:07  goldin
 * Fix bugs in UTF-8 conversion; RPY file cannot be UTF-8 b/c of binary data
 *
 * Revision 1.34  2001/10/31 12:21:55  goldin
 * work on UTF-8 encoding IPC files
 *
 * Revision 1.33  2001/10/08 11:57:57  goldin
 * Use msg key as remind string so we will see any missing messages
 *
 * Revision 1.32  2001/10/04 12:31:04  goldin
 * Read Msg files as UTF-8
 *
 * Revision 1.31  2001/10/03 15:15:46  goldin
 * Modify display to index some lines
 *
 * Revision 1.30  2001/10/01 11:52:55  goldin
 * Added facility to handle embedded substitution strings via %s, %d or %1 in keyed msgs
 *
 * Revision 1.29  2001/08/31 14:01:03  goldin
 * Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 * Revision 1.28  2001/07/12 13:14:47  goldin
 * Implement complex error message type
 *
 * Revision 1.27  2001/07/10 17:18:49  goldin
 * Handle new keyed format for error msgs
 *
 * Revision 1.26  2001/06/29 17:30:16  goldin
 * Implemented handing of state info from reply files
 *
 * Revision 1.25  2001/06/27 10:50:37  goldin
 * Fix non-exit bug
 *
 * Revision 1.24  2001/06/26 18:54:41  goldin
 * Allow progress detector to reset retry count so we don't time out with slow progress
 *
 * Revision 1.23  2001/06/26 18:39:47  goldin
 * add tracing for debug
 *
 * Revision 1.22  2001/06/18 15:04:17  goldin
 * Fix bugs in Qry handling
 *
 * Revision 1.21  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.20  2001/06/15 10:45:39  goldin
 * Allow explicit select of which msgs should go into history
 *
 * Revision 1.19  2001/06/11 10:24:39  goldin
 * Save msg keys and dump at exit
 *
 * Revision 1.18  2001/06/08 18:12:32  goldin
 * Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 * Revision 1.17  2001/06/06 15:16:11  goldin
 * Work on cleaning up event handling in FileChooser; improve tracing
 *
 * Revision 1.16  2001/06/05 19:36:21  goldin
 * Add Tracer; investigate file dialog bug
 *
 * Revision 1.15  2001/05/27 15:41:44  goldin
 * Additional work on query processor class and related functionality
 *
 * Revision 1.14  2001/05/24 11:56:12  goldin
 * Begin work on query processor
 *
 * Revision 1.13  2001/05/22 10:51:38  goldin
 * Get rid of debug msgs
 *
 * Revision 1.12  2001/05/22 10:30:30  goldin
 * add debug msgs
 *
 * Revision 1.11  2001/05/21 16:18:57  goldin
 * Initial implementation of table type messages
 *
 * Revision 1.10  2001/05/18 18:20:04  goldin
 * Added keyed message handling, retry timeout
 *
 * Revision 1.9  2001/05/18 12:05:41  goldin
 * Add error logging functionality to Logger class, implement in IpcFile
 *
 * Revision 1.8  2001/05/16 14:00:14  goldin
 * Add reading of header block in Rpy file
 *
 * Revision 1.7  2001/05/11 19:06:00  goldin
 * Change IPC file format; enhance & debug tracing
 *
 * Revision 1.6  2001/05/02 15:11:41  goldin
 * Implement message and progress IPC file processing
 *
 * Revision 1.5  2001/05/02 11:14:41  goldin
 * Implement IncomingCommandProcessor functionality
 *
 * Revision 1.4  2001/04/27 19:42:24  goldin
 * Initial implementation of class to handle commands coming into the UI
 *
 * Revision 1.3  2001/04/27 11:29:00  goldin
 * Continue implementation of interprocess communication and command handling
 *
 * Revision 1.2  2001/04/23 14:58:37  goldin
 * Added functionality to handle real files
 *
 */

package com.grs.dragon.ipc;
import com.grs.gui.*;
import java.io.*;
import java.util.*;

/** 
 * This class represents an instance of a Dragon interprocess
 * communication (IPC) file. These files, which are of various types
 * and formats, are used to communicate between various Dragon modules
 * (UI, server, viewport, etc.). The present class encapsulates
 * some of the behaviors associated with these files, such as
 * checking if the file has been fully written, parsing the
 * file, and tracing the file detection.
 * <p>
 * Detailed code for this class currently supports only
 * the file types generated or used by the UI: CMD, RPY, MSG, PRO, NAK
 */
public class IpcFile
    {
    public final static int CMD_FILE_TYPE = 0;
    public final static int RPY_FILE_TYPE = 1;    
    public final static int NAK_FILE_TYPE = 2;    
    public final static int MSG_FILE_TYPE = 3;    
    public final static int PRO_FILE_TYPE = 4;    
    public final static int QRY_FILE_TYPE = 5;
    public final static int DAT_FILE_TYPE = 6;
    public final static int UNKNOWN_FILE_TYPE = 255;

    public final static int KEYED_MSG_FLAG = 0x100;
    public final static int LOG_MSG_FLAG = 0x200;
    public final static int WARN_MSG_TYPE = 0;
    public final static int ERR_MSG_TYPE = 1;    
    public final static int INFORM_MSG_TYPE = 2;    
    public final static int SPT_MSG_TYPE = 3;    
    public final static int TABLE_MSG_TYPE = 10;
    public final static int COMPLEX_ERR_TYPE = 11;
    public final static int OTHER_MSG_TYPE = 255;    

    public final static String SENT = " >Sent ";
    public final static String RECEIVED = " >Received ";

    public static final String ZEROS = "000000000000";

    public static int MAX_RETRIES = 25;

    protected final int BLOBSIZE = 2048;

    protected int retryCount = 0;

      /**
       * Type of file. One of the constants above.
       */
    protected int fileType;

    /**
     * Code for module that generated this file 
     */
    protected String sourceModule;

    /**
     * If true, file has been completely written. Otherwise, still 
     * in the process. 
     */
    protected boolean bComplete = false;

    /**
     * code for the target module for this file 
     * (what module it is directed to) 
     */
    protected String targetModule;

    /**
     * Text of command. Only relevant for CMD type files. 
     */
    protected String cmdText;

    /**
     * String holding message text read from file. 
     * Only relevant for types MSG, NAK, PRO. 
     */
    protected String msgText;

    /**
     * For messages that come in with translation keys - save
     * the key.
     */
    protected String msgKey;
	

    /**
     * Full filename of file (without path). Note that all IPC files 
     * use 8+3 filename format. 
     */
    protected String filename;

    /**
     * Timestamp read from the file header 
     */
    protected String timeStampString;

    /**
     * Code indicating type of message. Only relevant for MSG. 
     * One of the MSG_TYPE constants above.
     */
    protected int msgCode;

    /**
     * Sequence string from filename (for example "003")
     */
    protected String sequence = null;

    /**
     * Current timeoffset for this module. Set in the constructor.
     */
    protected long timeOffset = 0;

      /**
       * Size of file as indicated in the file header. This is needed
       * after the initial test by the progress file type, so that
       * progress can be computed from file size.
       */
    protected int sizeInFile = 0;

      /**
       * Hashtable holding attributes and values found in a
       * RPY or QRY file, or a COMPLEX_ERR_TYPE Msg file.
       * Only allocated if that is the file type.
       */
    protected Hashtable<String,String> attributes = null;

      /**
       * Byte array of binary header data. Only allocated for RPY
       * files.
       */
    protected byte[] headerData = null;

      /**
       * Current percent complete. Only used for progress files.
       */
    protected int percentDone = 0;

      /**
       * Set to true if we just monitoring the file, false if
       * it should be deleted after processing. 
       * This flag is always true for progress files, and
       * for files that are created by the ui.
       */
    protected boolean bMonitor = false;

      /**
       * Keep track of whether an error occurred.
       * We cannot use bComplete for this
       * or we'll get infinite loops.
       */
    protected boolean bError = false;

      /**
       * Should this message be logged?
       */
    protected boolean bLogMessage = false;

      /**
       * Make the reader available class wide so we can close it
       * in case of an exception.
       */
    protected BufferedReader reader = null;

      /**
       * Keep a copy of all the file data read, in case of an error.
       */
    protected StringBuffer fileContents = null;


    /**
     * The IPC file constructor reads the file and determines if
     * it is complete (based on file size). If it is not complete, it 
     * leaves the bComplete flag set to false and 
     * and returns immediately. The caller must query this flag to determine
     * whether to delete or keep the IpcFile instance. If the file is 
     * complete, the constructor does further processing, setting
     * the various attributes of the file, reading the data, etc. 
     * The detailed processing depends on the type of file involved. 
     * @param filename Name of IpcFile (with path). Since this file has 
     *                 been detected
     *                 in the file system, it is assumed to exist.
     * @param timeOffset Current time offset in creating module.
     * @param bMonitor Only monitor file state, do not delete the file.
     */
    public IpcFile(String filename, long timeOffset, 
                   boolean bMonitor)
        {
	this.timeOffset = timeOffset;
	this.filename = filename;
        this.bMonitor = bMonitor;
        fileContents = new StringBuffer();
	retry();
        }
    
      /**
       * Try again to see if the file is complete.
       * If it is, read and process the file. Returns
       * true if file complete, else false.
       * This can also be used to reread an existing file, e.g. a 
       * progress file.
       */
    public boolean retry()
        {
        retryCount++;
        if (retryCount > MAX_RETRIES)
	    {
	    handleFailure(new Exception("Exceeded maximum retries for file " +
					filename));
            return bComplete;
	    }
	try
	    {
	    bComplete = processFile();
	    }
        catch (NumberFormatException nfe)
	    {
            handleFailure(new Exception(
			"Invalid IPC File format:  " + filename));
	    }
	catch (IOException ioe)
	    {
            handleFailure(ioe);
	    }
        return bComplete;
	}


      /**
       * Factorization. Log an error and delete the file
       * to avoid an infinite loop.
       */
    protected void handleFailure(Exception e)
        {
        if ((bMonitor == true) && (e instanceof java.io.FileNotFoundException))
	    {
	    // file created and sent was deleted before we could trace it.
	    try
	        {
	        doTracing(filename);
		}
            catch (Exception new_e)  // will never happen in this branch
	        {
		}
	    bComplete = true;
	    return;
	    }
	bComplete = false;
	bError = true;
	try  
	    {
	    if (reader != null)
	        reader.close();     
            Logger logger = ApplicationManager.getErrorLogger();
            if (logger != null)
	        {
                if (e.getMessage() != null)
	            logger.logError(e.getMessage(),true);
                else 
	            logger.logError(e.toString(),true);
                if ((fileContents != null) && (fileContents.length() > 0))
                    logger.logError(fileContents.toString(), false);	    
	        }
	    ErrorDisplay errDisplay = 
                ApplicationManager.getErrorDisplay();
            if (errDisplay != null)
	        {
 	        if (e instanceof IOException)
		     {
                     errDisplay.showError(TextKeys.ERROR,
				   TextKeys.BADCHARSIPCFILE,
				   filename);
                     errDisplay.showError(TextKeys.WARNING,
				   TextKeys.BADCHARSEXPLAIN,
				   null);
		     }
		else
		     {
                     errDisplay.showError(TextKeys.ERROR,
				   TextKeys.UNRECOGNIZEDIPCFILE,
				   filename);
		     }
		}
	    deleteFile();
	    }
	catch (IOException except)
	    {
	    }
	}

      /**
       * Factorization of main processing logic, allows
       * both constructor and retry methods to access same
       * code.
       * @return true if complete, else false.
       */
    protected boolean processFile()
              throws IOException, NumberFormatException
        {
	File focusFile = new File(filename);
	String fname = focusFile.getName();
        sequence = fname.substring(5,8);
	fileType = determineFileType(fname);	     
	sizeInFile = parseHeader(filename);
        if (sizeInFile < 0)  // file not written to at all yet
            return false;
	if (focusFile.length() < sizeInFile)
	    {
	    String msg = "File " + filename + " claims length of " +
	      String.valueOf(sizeInFile) + " but is actually " +
	      String.valueOf(focusFile.length());
  	    Tracer.outputTraceMessage(msg,"UI",
                    ApplicationManager.getTimeOffset());
	    return false;
	    }
	bComplete = true;
	if (fileContents.length() > 0)
            fileContents.delete(0, fileContents.length());
	doTracing(filename);
	parseRemainder(filename);
	if (!bMonitor)
	    {
	    deleteFile();
	    }
        return true;
        }

      /**
       * Determine and return the fileType code, based on
       * the file name.
       */
    protected int determineFileType(String fname)
        {
	int type = UNKNOWN_FILE_TYPE;
        String testName = fname.toUpperCase();
	if (testName.startsWith("CMD"))
	    type = CMD_FILE_TYPE;
	else if (testName.startsWith("RPY"))
	    type = RPY_FILE_TYPE;
	else if (testName.startsWith("NAK"))
	    type = NAK_FILE_TYPE;
	else if (testName.startsWith("MSG"))
	    type = MSG_FILE_TYPE;
	else if (testName.startsWith("PRO"))
	    type = PRO_FILE_TYPE;
	else if (testName.startsWith("QRY"))
	    type = QRY_FILE_TYPE;
	else if (testName.startsWith("DAT"))
	    type = DAT_FILE_TYPE;
	return type;
	}

	/**
	 * Read the first line of the file and extract the
	 * timestamp and the size fields, which are common to
	 * all file types.
	 * Return the size recorded in the file.
	 */
    protected int parseHeader(String fullFileName)
	              throws IOException,NumberFormatException
	{
        int size = -1;
        if (fileContents.length() > 0)
            fileContents.delete(0, fileContents.length());
        reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(fullFileName)));
	String firstLine = reader.readLine();
        if (firstLine == null)   // nothing in file yet
            return size;
        fileContents.append(firstLine + "\n");
        reader.close();
	reader = null;
	int pos = firstLine.indexOf("=");
        if (pos < 0)
	    pos = firstLine.indexOf(" ");
	if (pos < 0)
	    throw new IOException("IPC file " + filename +
				  ": header has invalid format");
	int pos2 = firstLine.indexOf(" ",pos+1);
	if (pos2 < 0)
	    throw new IOException("IPC file " + filename +
				  ": header has invalid format");
	int pos3 = firstLine.indexOf(" ",pos2+1);
	if (pos3 < 0)
	    throw new IOException("IPC file " + filename +
				  ": header has invalid format");
        timeStampString = firstLine.substring(pos+1,pos2);
        size = Integer.parseInt(firstLine.substring(pos2+1,pos3));
        return size;
	}

	/**
	 * Main method for reading the non-common parts of 
	 * the IPC file. This method branches to sub-methods
	 * depending on the type of the file.
	 */
    protected void parseRemainder(String fullFileName)
                        throws IOException
        {
        File parseFile = new File(fullFileName);
        switch (fileType)
	    {
	    case CMD_FILE_TYPE:
	         parseCmdFile(parseFile);
		 break;
	    case RPY_FILE_TYPE:
	         parseRpyFile(parseFile);
		 break;
	    case NAK_FILE_TYPE:
	         parseNakFile(parseFile);
		 break;
	    case MSG_FILE_TYPE:
	         parseMsgFile(parseFile);
		 break;
	    case PRO_FILE_TYPE:
	         parseProFile(parseFile);
		 break;
	    case QRY_FILE_TYPE:
	         parseQryFile(parseFile);
		 break;
	    default:
		 break;
	    }
	}


	/**
	 * Factorization: method to parse CMD file input.
	 */
    protected void parseCmdFile(File parseFile)
                     throws IOException
        {
        StringBuffer cmdBuffer = new StringBuffer(sizeInFile);
        String filename = parseFile.getName().toUpperCase();
	targetModule = filename.substring(3,5);
	reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(parseFile),
				    "UTF-8"));
	String input = reader.readLine();
        fileContents.append(input);
	int end = input.lastIndexOf(")");
	if (end < 0)
	    throw new IOException("IPC Cmd file " + filename +
				  ": header has invalid format");
	int start = input.lastIndexOf(" ",end-2);
	if (start < 0)
	    throw new IOException("IPC Cmd file " + filename +
				  ": header has invalid format");
        sourceModule = input.substring(start+1, end-1);
	// get command text - may be multiline
	while ((input = reader.readLine()) != null)
	      {
              fileContents.append(input + "\n");
	      cmdBuffer.append(input);
	      cmdBuffer.append("\n");
	      }
	reader.close();
	reader = null;
	cmdText = cmdBuffer.toString();
	}


	/**
	 * Factorization: method to parse RPY file input.
	 */
    protected void parseRpyFile(File parseFile)
                     throws IOException
        {
        String filename = parseFile.getName();
	targetModule = filename.substring(3,5);
	reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(parseFile)));
	String input = reader.readLine();
        fileContents.append(input + "\n");
        
	int end = input.lastIndexOf(")");
	if (end < 0)
	    throw new IOException("IPC Rpy file " + filename +
				  ": header has invalid format");
	int start = input.lastIndexOf(" ",end-2);
	if (start < 0)
	    throw new IOException("IPC Rpy file " + filename +
				  ": header has invalid format");
        sourceModule = input.substring(start+1, end-1);
        attributes = new Hashtable<String,String>();
	// get attribute values - may be multiline
        int eqpos = 0;
	while ((input = reader.readLine()) != null)
	      {
	      fileContents.append(input + "\n");
              int ctrlpos = input.indexOf(0x1A);
              if (ctrlpos >= 0)
		  break; // done with attributes
              eqpos = input.indexOf("=");
              if (eqpos >= 0)
		  {
		  attributes.put(input.substring(0,eqpos).trim(),
				 input.substring(eqpos+1).trim());
		  }
	      }
	reader.close();
	reader = null;
	// need to handle binary header data section.
        headerData = new byte[BLOBSIZE];
	BufferedInputStream bis = new BufferedInputStream(
                                new FileInputStream(parseFile));
        int nextByte = bis.read(); 
        while ((nextByte != -1) && (nextByte != 0x1A)) // control-Z marks hdr
	      {
	      nextByte = bis.read();
	      }
	/* The following code should no longer execute since
         * we are not sending blobs anymore.
         */
        if (nextByte == 0x1A)   // we have reached the header section
	      {
              int bytecount = bis.read(headerData,0,BLOBSIZE);
	      if ((bytecount > 0) && (bytecount < BLOBSIZE))
 	              throw new IOException("IPC Rpy file " + filename +
				  ": Dragon header is too short");
	      }
	bis.close();
	}


	/**
	 * Factorization: method to parse QRY file input.
         * Very similar to Rpy - populates an attribute/value
         * hash table.
	 */
    protected void parseQryFile(File parseFile)
                     throws IOException
        {
        String filename = parseFile.getName();
	targetModule = filename.substring(3,5);
	reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(parseFile),
                                    "UTF-8"));
	String input = reader.readLine();
        fileContents.append(input + "\n");
        
	int end = input.lastIndexOf(")");
	if (end < 0)
	    throw new IOException("IPC Qry file " + filename +
				  ": header has invalid format");
	int start = input.lastIndexOf(" ",end-2);
	if (start < 0)
	    throw new IOException("IPC Qry file " + filename +
				  ": header has invalid format");
        sourceModule = input.substring(start+1, end-1);
        attributes = new Hashtable<String,String>();
	// get attribute values - may be multiline
        int eqpos = 0;
	while ((input = reader.readLine()) != null)
	      {
	      fileContents.append(input + "\n");
              int ctrlpos = input.indexOf(0x1A);
              if (ctrlpos >= 0)
		  break; // done with attributes
              eqpos = input.indexOf("=");
              if (eqpos >= 0)
		  {
		  attributes.put(input.substring(0,eqpos).trim(),
				 input.substring(eqpos+1).trim());
		  }
	      }
	reader.close();
	}

	/**
	 * Factorization: method to parse Nak file input.
	 */
    protected void parseNakFile(File parseFile)
                     throws IOException
        {
        String filename = parseFile.getName();
	targetModule = filename.substring(3,5);
	reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(parseFile),
				    "UTF-8"));
	String input = reader.readLine();
        fileContents.append(input + "\n");
	int end = input.lastIndexOf(")");
	if (end < 0)
	    throw new IOException("IPC Nak file " + filename +
				  ": header has invalid format");
	int mid = input.lastIndexOf(" ",end-2);
	if (mid < 0)
	    throw new IOException("IPC Nak file " + filename +
				  ": header has invalid format");
	int start = input.lastIndexOf(" ",mid-1);
	if (start < 0)
	    throw new IOException("IPC Nak file " + filename +
				  ": header has invalid format");
        sourceModule = input.substring(start+1, mid);
        // don't bother getting the msg code for now.
	// just get the one message.
	input = reader.readLine();
        fileContents.append(input + "\n");
	msgText = input;
	reader.close();
	reader = null;
	}

	/**
	 * Factorization: method to parse Msg file input.
	 */
    protected void parseMsgFile(File parseFile)
                     throws IOException, NumberFormatException
        {
        String filename = parseFile.getName();
	sourceModule = filename.substring(3,5);
        targetModule = "UI";
	reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(parseFile),
                                    "UTF-8"));
	String input = reader.readLine();
        fileContents.append(input + "\n");
	int end = input.lastIndexOf(")");
	if (end < 0)
	    throw new IOException("IPC Msg file " + filename +
				  ": header has invalid format");
	int start = input.lastIndexOf(" ",end-2);
	if (start < 0)
	    throw new IOException("IPC Msg file " + filename +
				  ": header has invalid format");
        msgCode = Integer.parseInt(input.substring(start+1, end-1));
        StringBuffer msgBuffer = new StringBuffer();
	while((input = reader.readLine()) != null)
	    {
            fileContents.append(input + "\n");
            if ((msgCode & (KEYED_MSG_FLAG | LOG_MSG_FLAG)) > 0)
	        {
                if ((msgCode & KEYED_MSG_FLAG) > 0)
		    {
                    msgBuffer.append(translateKeyedMessage(input)+ "\n");
		    }
		else
		    {
		    msgBuffer.append(input + "\n");
		    }
		if ((msgCode & LOG_MSG_FLAG) > 0)
		    {
		    bLogMessage = true;
		    }
	        msgCode = msgCode & 0xFF;
	        }
	    else
	        {
	        if (msgCode == COMPLEX_ERR_TYPE)
	            {
		    if (attributes == null)
                         attributes = new Hashtable<String,String>();
		    int eqpos = input.indexOf("=");
                    if (eqpos >= 0)
		         {
                         String value = input.substring(eqpos+1).trim();
			 if (value.length() > 0)
		               attributes.put(input.substring(0,eqpos).trim(),
				              value );
		         }
		    }
		else
	            {
		    msgBuffer.append(input + "\n");
	            }
		}
	    }
        msgText = msgBuffer.toString();
	reader.close();
	reader = null;
	}


      /**
       * Factorization of parseMsgFile. Tries to use first token
       * in input line as key to look up message. Returns composed
       * message. 
       */
    protected String translateKeyedMessage(String inputString)
                   throws IOException
        {
	String key = null;
	String xlateMsg = null;
	int pos = inputString.indexOf(" ");
	if (pos >= 0)
	    {
            key = inputString.substring(0,pos);
	    }
	else
	    {
	    key = inputString;
	    }
	xlateMsg = ApplicationManager.getTextSource().getI18NText(key,key);
	msgKey = key;
	if ((pos >= 0) && (pos < inputString.length()))
	    {
	    // handle internal substitution
	    int p1 = xlateMsg.indexOf("%");
	    if (p1 >= 0)
	        {
		int p2 = xlateMsg.indexOf(" ",p1);
		if (p2 < 0)  // substitution string is at end of xlated string
		     {
		     xlateMsg = xlateMsg.substring(0,p1)
                            + inputString.substring(pos+1);
		     }
		else        // substitution string is inside xlated string
		     {
		     xlateMsg = xlateMsg.substring(0,p1) 
                            + inputString.substring(pos+1) 
                            + xlateMsg.substring(p2);
		     }
		}    // end if substitution text found.
	    else     // no substitution text found
	        {
		xlateMsg = xlateMsg + " " + inputString.substring(pos+1);
		}
	    }
	// otherwise, no text after the key, so just returned xlated msg
	return xlateMsg;
	}

	/**
	 * Factorization: method to parse PRO file input.
	 */
    protected void parseProFile(File parseFile)
                     throws IOException
        {
        String filename = parseFile.getName();
	sourceModule = filename.substring(3,5);
	reader = new BufferedReader(new InputStreamReader(
				    new FileInputStream(parseFile),
                                    "UTF-8"));
	// skip header since we already have the size
	String input = reader.readLine();
        fileContents.append(input + "\n");
	msgText = reader.readLine();
        fileContents.append(input + "\n");
        percentDone = (int) (parseFile.length()) - sizeInFile;
	reader.close();
	reader = null;
	}
      

      /**
       * Allow external class to remove the file.
       * Also called by the class itself after reading, if
       * bMonitor is false;
       */
    public void deleteFile()
        {
        File delFile = new File(filename);
	boolean result = delFile.delete();
	if (!result) //delete failed for some reason
	    {
            Logger logger = ApplicationManager.getErrorLogger();
            if (logger != null)
	        {
		logger.logError("Attempted delete of IPC file failed: " 
				+ filename,true);	    
	        }
	    }
        }

      /**
       * Allows external class to discover if a file has been consumed.
       * Returns false if file still exists, else true.
       */
    public boolean fileConsumed()
        {
	File theFile = new File(filename);
	if (theFile.exists())
	    return false;
	else 
	    return true;
	}

      /**
       * Deduce, based on filetype, source and target, whether
       * this IPCfile is one we are sending or receiving.
       * Return the string " >Sent " or " >Received "
       */
    protected String getSendOrReceive()
        {
	String returnString = RECEIVED;
        if ((bMonitor) && (fileType != PRO_FILE_TYPE))
	     returnString = SENT;
        return returnString;
	}


    public void doTracing(String filename)
                       throws IOException
        {
        if (!Tracer.isTracing())
            return;
        File testFile = new File(filename);
        StringBuffer contents = new StringBuffer();
        String sendOrReceive = getSendOrReceive();
        long localTime = new Date().getTime()/(long) 1000;
	String timeString = String.valueOf(localTime - timeOffset);
	contents.append(ZEROS.substring(0,12 - timeString.length()));
	contents.append(timeString);
        contents.append(" [" + Tracer.extractTime() + "]");
        contents.append(" UI " + sendOrReceive);
        contents.append(testFile.getName() + "  { ");
        if ((bMonitor) && (!testFile.exists()))
            {
            contents.append("(monitored file deleted before it could be logged)");
	    }
        else
	    {
	    // add content
	    reader = new BufferedReader(
					  new FileReader(filename));
	    String input = null;
	    while ((input = reader.readLine()) != null)
		{
		int ctrlpos = input.indexOf(0x1A);
		if (ctrlpos >= 0)
		    {
		    contents.append(input.substring(0,ctrlpos) + "\n");
		    break; // done with text data
		    }
		else
		    {
		    contents.append(input + "\n");
		    }
		}
	    reader.close();
	    reader = null;
	    }
        contents.append(" }");
	Tracer.outputTraceMessage(contents.toString());
        }

      /**
       * Checks to see if there are any non whitespace characters
       * in the message text. If there are, returns false. Otherwise
       * returns true. If msgText is null, also returns true.
       */
    public boolean isMessageBlank()
        {
	boolean bAllBlanks = true;
	if (msgText == null)
	    return bAllBlanks;
	char[] msgChars = msgText.toCharArray();
	int i = 0;
	while ((i < msgChars.length) && (bAllBlanks))
	    {
            if (!Character.isWhitespace(msgChars[i]))
                bAllBlanks = false;
            i++;
	    }
	return bAllBlanks;
        }

    public int getSizeInFile()
        {
        return sizeInFile;
        }

    public String getTimeStampString()
        {
        return timeStampString;
        }

    public int getMsgCode()
        {
        return msgCode;
        }

    public int getFileType()
        {
        return fileType;
        }

    public String getSourceModule()
        {
        return sourceModule;
        }

    public String getCmdText()
        {
	return cmdText;
        }

    public String getMsgText()
        {
        return msgText; 
        }

    public String getMsgKey()
        {
        return msgKey; 
        }

    public boolean isComplete()
        {
        return bComplete;
        }

    public boolean isError()
        {
        return bError;
        }
    public boolean isLogMessage()
        {
	return bLogMessage;
	}
    public String getTargetModule()
        {
	return targetModule;
        }

    public int getPercentDone()
        {
	return percentDone;
        }

    public String getFilename()
        {
        return filename;
	}

    public String getSequence()
        {
	return sequence;
	}

    public byte[] getHeaderData()
        {
	return headerData;
	}

      /**
       * Allow another class to reset the retry count accumulator.
       * Needed for progress files, which get repeatedly reread.
       */
    public void setRetryCount(int count)
        {
	retryCount = count;
	}

     /**
      * Return value associated with named attribute, or null
      * if current file is not of type RPY.
      */
    public String getAttributeValue(String attributeName)
        {
	String attVal = null;
	if (attributes != null)
	    {
	    attVal = (String) attributes.get(attributeName);
	    }
	return attVal;
        }

      /**
       * Return an array of all attribute names represented in
       * the attributes table, or null if the file is not of type
       * RPY.
       */
    public String[] getAttributeNames()
        {
        String[] names = null;
	if (attributes != null)
	     {
	     Object[] keys = attributes.keySet().toArray();
	     names = new String[keys.length];
             for (int i = 0; i < keys.length; i++)
	         names[i] = (String) keys[i];
	     }
	return names;
	}

      /**
       * Return the whole attribute hashtable.
       */
    public Hashtable<String,String> getAttributes()
        {
	return attributes;
	}

      /**
       *  Test driver
       */
    public static void main(String[] args)
                 throws IOException
        {
	BufferedReader reader = new BufferedReader(new 
                                    InputStreamReader(System.in));
	while (true)
	    {
	    System.out.println("Enter filename:");
	    String filename = reader.readLine();
	    IpcFile test = new IpcFile(filename,20000,false);
            if (test.isError())
	        continue;
	    while (!test.isComplete())
	        {
                test.retry();
		}
	    int fileType = test.getFileType();
	    System.out.println("Target: " + test.getTargetModule());
	    System.out.println("Source: " + test.getSourceModule());
	    System.out.println("Timestamp: " + test.getTimeStampString());
	    System.out.println("size: " + test.getSizeInFile());
	    switch (fileType)
	      {
	      case CMD_FILE_TYPE:
		System.out.println("CMD");
		System.out.println("Command is:");
		System.out.println(test.getCmdText());
		break;
	      case RPY_FILE_TYPE:
		System.out.println("RPY");
		String[] atts = test.getAttributeNames();
		for (int i = 0; i < atts.length; i++)
		    System.out.println(atts[i] + "=" +
				       test.getAttributeValue(atts[i]));
		/****              
                byte[] hdr = test.getHeaderData();
		if (hdr != null)
		    {
		    DImageHeader imgHdr = new DImageHeader(hdr);
		    if (imgHdr.isInitialized())
		        {
			System.out.println("Image dimensions: " + 
					   imgHdr.getNLines() + 
					   " by " + imgHdr.getNPix());
			System.out.println("File type: " +  
					   imgHdr.getFileType());
			System.out.println("Mean: " + imgHdr.getImgmean());
			System.out.println("Min: " + imgHdr.getImgmin());
			System.out.println("Max: " + imgHdr.getImgmax());

			}
		    }
		 ***/
		break;
	      case NAK_FILE_TYPE:
		System.out.println("NAK");
		System.out.println("Message: " + test.getMsgText());
		break;
	      case MSG_FILE_TYPE:
		System.out.println("MSG");
		System.out.println("Message: " + test.getMsgText());
		System.out.println("Message code: " + test.getMsgCode());
		break;
	      case PRO_FILE_TYPE:
		System.out.println("PRO");
		System.out.println("Message: " + test.getMsgText());
                System.out.println(test.getPercentDone() + " done...");
		break;
	      case UNKNOWN_FILE_TYPE:
		System.out.println("UNKNOWN TYPE!!!");
		break;
	      }
	    }
	}

    }




