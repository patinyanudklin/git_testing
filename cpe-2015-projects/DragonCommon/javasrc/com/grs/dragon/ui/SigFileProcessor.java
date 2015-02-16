/**
 * SigFileProcessor
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin on 2/28/2001
 * $Id: SigFileProcessor.java,v 1.15 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SigFileProcessor.java,v $
 * Revision 1.15  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.14  2006/06/06 08:36:38  goldin
 * Fix reading of signature files to interpret number of bands correctly - use histogram count
 *
 * Revision 1.13  2005/02/05 13:47:58  goldin
 * Get rid of warnings about finally
 *
 * Revision 1.12  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.11  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.10  2001/10/30 18:06:37  goldin
 * Use UTF-8 to read sig names
 *
 * Revision 1.9  2001/10/12 14:02:06  goldin
 * Add new callback and validator for c/edi/mod
 *
 * Revision 1.8  2001/06/29 17:30:16  goldin
 * Implemented handing of state info from reply files
 *
 * Revision 1.7  2001/05/14 13:47:36  goldin
 * Add symbols for new text
 *
 * Revision 1.6  2001/05/10 13:14:51  goldin
 * Continue implementation of SigFile and scaling callbacks
 *
 * Revision 1.5  2001/05/09 15:16:40  goldin
 * Begin implementing signature populaing callbacks for C/EDI
 *
 * Revision 1.4  2001/05/08 13:42:23  goldin
 * Began work implementing SigFileProcessor
 *
 * Revision 1.3  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.2  2001/04/17 12:10:16  goldin
 * Modifications made with Together
 *
 * Revision 1.1  2001/02/28 16:25:09  goldin work in progress - class to read and parse signature files
 */

package com.grs.dragon.ui;
import com.grs.gui.*;

import java.io.*;
import java.util.*;

/**
 * This class reads a DRAGON signature file and then can provide 
 * information on the file, such as the number of signatures,
 * the names of signatures, and the number of bands and name of input 
 * image files for each signature. It is used primarily
 * to provide information for DragonUI callbacks.
 * <p>
 * A SigFileProcessor can also be initialized explicitly
 * by setting its various member data elements. This allows
 * the SigFileProcessor to represent the state of signatures
 * "in memory" as communicated from the server.
 */
public class SigFileProcessor
    {

    public static final int MAX_SIG_BANDS = 4;
    public static final int MAX_SIG_COUNT = 16;

      /**
       * Has this signature file processor been initalized by
       * reading a file?
       */
    protected boolean bInitialized = false;

    /** How many signatures in the file */
    protected int sigCount = 0;

      /**
       * How many bands in the signatures in the file?
       */
    protected int bandCount = 0;

    /** HashMap to keep track of images used for each signature. 
     * Keyed by signature name. 
     * Use HashMap so we can have null values if no images specified.
     */
    protected HashMap sigImages = new HashMap(64);

    /**
     * Current signature file associated with this SigFileProcessor. 
     * The same processor can be reused
     * for multiple files (one at a time)
     */
    protected String sigFileName = null;

      /**
       * Construct and keep an array of signature names so we don't
       * have to get and transform the HashMap keys every time.
       */
    protected String[] signatureNames = null;

      /**
       * Used to return an error message if some problem is encountered.
       */
    protected String errorMessage = null;

      /**
       * Hold the upper and lower bounds by signature, for MOD
       */
    protected int[][] sigUpper = null;
    protected int[][] sigLower = null;
    

    /** No argument constructor. Used to ready a processor before we know 
     * what file it should read. 
     */
    public SigFileProcessor()
        {
        bInitialized = false;
        }

    /** 
     * Alternative constructor, can be created and initialized with 
     * a signature file in one step. 
     */
    public SigFileProcessor(String sigFileName)
        {
        init(sigFileName);
        }

    /**
     * Initializes the SigFileProcessor with data from a particular 
     * signature file.
     * @param sigFileName  Name of signature file to process including path
     */
    public boolean init(String sigFileName)
        {
	boolean bOk = true;
        errorMessage = null;
        sigCount = 0;
        bandCount = 0;
        signatureNames = new String[MAX_SIG_COUNT];
        sigUpper = new int[MAX_SIG_COUNT][MAX_SIG_BANDS];
	sigLower =  new int[MAX_SIG_COUNT][MAX_SIG_BANDS];
        sigImages.clear();
        try
            {
	    String inputLine = null;
            FileInputStream fis = new FileInputStream(sigFileName);
            InputStreamReader isr = new InputStreamReader(fis,"UTF-8");
            BufferedReader reader = new BufferedReader(isr);
            String sigName = null;
	    int pos = -1;
            int sigBandCount = 0;
	    while ((inputLine = reader.readLine()) != null)
	        {
		if (inputLine.startsWith("NEW-SIG"))
	             {
		     if (bandCount == 0)
		         {
                         bandCount = sigBandCount;
			 sigBandCount = 0;
			 }
		     else if (bandCount != sigBandCount)
		         {
		         errorMessage = DragonUI.textSource.getI18NText(
			   TextKeys.INCONSISTENTSIGFILE,
			     "Inconsistent signature file. " +
                           "Number of bands varies across signatures.");
			 bOk = false;
			 }
		     else 
		         {
                         sigBandCount = 0;
                         }
                     pos = inputLine.indexOf(" ");
		     if (pos >= 0)
		          {
                          sigName = inputLine.substring(pos+1);
			  signatureNames[sigCount++] = sigName;
			  }
		     else
		          {
			  errorMessage =
                             DragonUI.textSource.getI18NText(
                                   TextKeys.INVALIDSIGFILE,
                                   "Invalid signature file format;") +
			     DragonUI.textSource.getI18NText(
				   TextKeys.MISSINGSIGNAME,
					    " missing signature name");
			  bOk = false;
			  }
 		     }
		else if (inputLine.startsWith("END-SIG"))
	             {
		     sigName = null;
		     }
		else if ((pos = inputLine.indexOf("HIST=")) >= 0)
		     {
                     boolean hasCount = readSigBandCount(inputLine);
                     if (hasCount) sigBandCount++;
		     }
                else if ((pos = inputLine.indexOf("IMAGES=")) >= 0)
	             {
                     String[] images = readSigImages(inputLine);
		     sigImages.put(sigName, images);
		     }
                else if ((pos = inputLine.indexOf("UPPER=")) >= 0)
	             {
                     parseSigBounds(inputLine,sigCount,true);
		     }
                else if ((pos = inputLine.indexOf("LOWER=")) >= 0)
	             {
                     parseSigBounds(inputLine,sigCount,false);
		     }
                }
            this.sigFileName = sigFileName;
            reader.close();
            if (bOk)
                bInitialized = true;
            }
        catch (IOException ioe)
            {
            errorMessage = DragonUI.textSource.getI18NText(
			   TextKeys.ERRORREADINGSIGFILE,
                           "Error opening or reading signature file: ") 
                  + sigFileName + "\n" + ioe.getMessage();
            bOk = false;
            }
	return bOk;
        }

    /**
     * Clears out data in an existing SigFileProcessor, so that
     * it can be reused.
     */
    public void clear()
        {
        sigCount = 0;
	bandCount = 0;
	sigFileName = null;
        signatureNames = null;
        sigImages.clear();
        bInitialized = false;
	}

    /**
     * Parse a HIST= line to determine if this band is active.
     * @return true if the histogram for this band has a nonzero total pixel count
     */
    protected boolean readSigBandCount(String inputLine)
        {
        boolean hasCount = false;
        int bands = 0;
        int tokencount = 0;
	int pos = inputLine.indexOf("HIST=");
	String values = inputLine.substring(pos+6);
	StringTokenizer tokenizer = new StringTokenizer(values," \t");
	while (tokenizer.hasMoreTokens())
	  {
	  String value = tokenizer.nextToken().trim();
	  tokencount++;
          if (tokencount == 2)
	     { 
	     long temp = Long.parseLong(value);
	     if (temp > 0)
	         hasCount = true;
	     break;
	     }
	  }
        return hasCount;
        }

    /**
    * Parse the IMAGES= line. Returns image
    * file names as an array of strings, or null if there are no image file
    * names.
    */
    protected String[] readSigImages(String inputLine)
        {
        String[] imageNames = null;
	int pos = inputLine.indexOf("IMAGES=");
	String values = inputLine.substring(pos+8);
	StringTokenizer tokenizer = new StringTokenizer(values," ");
	imageNames = new String[tokenizer.countTokens()];
	int i = 0;
	while (tokenizer.hasMoreTokens())
	    {
	    imageNames[i++] = tokenizer.nextToken();
	    }
        return imageNames;
        }

    /**
    * Parse the IMAGES= line. Returns image
    * file names as an array of strings, or null if there are no image file
    * names.
    */
    protected void parseSigBounds(String inputLine, int sigIndex,
				  boolean bUpper)
                       throws IOException
        {
	int pos;
        if (bUpper)
            pos = inputLine.indexOf("UPPER=");
	else
            pos = inputLine.indexOf("LOWER=");

	String values = inputLine.substring(pos+6);
	StringTokenizer tokenizer = new StringTokenizer(values," \t");
	int i = 0;
	int value = 0;
        String tok = null;
	while (tokenizer.hasMoreTokens())
	    {
            try
	        {
                tok = tokenizer.nextToken();
                value = Integer.parseInt(tok);
		}
	    catch (NumberFormatException nfe)
	        {
		throw new IOException(
                   "Bad upper or lower bounds value in signature file");
		}
            if (bUpper)
	        sigUpper[sigIndex-1][i++] = value;
	    else 
	        sigLower[sigIndex-1][i++] = value;
	    }
        }

      /**
       * Accessor methods
       */
    public int getSigCount()
        {
	return sigCount;
	}

    public void setSigCount(int count)
        {
	sigCount = count;
	}

    public int getBandCount()
        {
	return bandCount;
	}

    public void setBandCount(int count)
        {
	bandCount = count;
	}

    public String getSigFileName()
        {
	return sigFileName;
	}

    public void setSigFileName(String name)
        {
        sigFileName = name;
	}

    public int getSigUpper(int sigIndex, int bandIndex)
        {
	return sigUpper[sigIndex][bandIndex];
	}
    public int getSigLower(int sigIndex, int bandIndex)
        {
	return sigLower[sigIndex][bandIndex];
	}

    public void setSigUpper(int sigIndex, int bandIndex, int value)
        {
        sigUpper[sigIndex][bandIndex] = value;
	}

    public void setSigLower(int sigIndex, int bandIndex, int value)
        {
	sigLower[sigIndex][bandIndex] = value;
	}

    public boolean isInitialized()
        {
	return bInitialized;
	}

    public void setInitialized(boolean bFlag)
        {
	bInitialized = bFlag;
	}

    public String[] getSignatureNames()
        {
	return signatureNames;
	}

    public void setSignatureName(String name, int index)
        {
	if (sigCount == 0)
	    return;
        if (index >= sigCount)
	    return;
        if (signatureNames == null)
	    {
            signatureNames = new String[sigCount];
	    }
	signatureNames[index] = name;
	}

    public String[] getSignatureImages(String sigName)
        {
	return (String[]) sigImages.get(sigName);
	}

      /**
       * Given a sig name, find its index number.
       * Returns -1 if not found.
       */
    public int getSignatureIndex(String sigName)
        {
        int found = -1;
        if (signatureNames == null)
            return found;
        for (int i = 0; (i < sigCount) && (found < 0); i++)
	    {
	    if (signatureNames[i].equalsIgnoreCase(sigName))
                found = i;
	    }
        return found;
	}

    public String getErrorMessage()
        {
        return errorMessage;
	}

      /**
       * Test driver
       */
    public static void main(String[] args)
        {
	if (args.length < 1)
	     {
	     System.out.println("USAGE: SigFileProcessor <sigfilename>");
	     System.exit(0);
	     }

	SigFileProcessor sigProc = new SigFileProcessor(args[0]);
        if (!sigProc.isInitialized())
	     {
             System.out.println("Error initializing SigFileProcessor!");
	     System.exit(0);
	     }
        System.out.println("The file contains " +
			      sigProc.getSigCount() + " signatures");

        System.out.println("The signatures have " +
			      sigProc.getBandCount() + " bands");
        System.out.println("Signature names:");
	String[] names = sigProc.getSignatureNames();
        if (names != null)
	    {
	    for (int i = 0; i < sigProc.getSigCount(); i++)
	         System.out.println(names[i]);
	    String[] images = sigProc.getSignatureImages(names[0]);
            if (images != null)
	         {
		 System.out.println("Images for signature " + names[0]);
		 for (int i = 0; i < images.length; i++)
                      System.out.println(images[i]);
		 }
	    }
        }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SigFileProcessor.java,v 1.15 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }














