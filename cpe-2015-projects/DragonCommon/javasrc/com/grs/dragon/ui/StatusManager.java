/**
 *  StatusManager
 *
 *  Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 *  Created 6/29/2001 by Sally Goldin
 *
 *   $Id: StatusManager.java,v 1.22 2007/01/05 07:41:57 rudahl Exp $
 *   $Log: StatusManager.java,v $
 *   Revision 1.22  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.21  2006/01/20 08:41:44  goldin
 *   Modify isMemoryFileValid to handle color file
 *
 *   Revision 1.20  2006/01/20 07:48:17  goldin
 *   New fn to clear status
 *
 *   Revision 1.19  2005/11/19 10:01:13  goldin
 *   Have to add path to GFILE, etc.
 *
 *   Revision 1.18  2005/11/04 10:53:27  goldin
 *   Working on setting and getting persistent data
 *
 *   Revision 1.17  2005/10/21 14:02:44  goldin
 *   Working on getting status info from persistent DB
 *
 *   Revision 1.16  2005/10/03 12:32:21  goldin
 *   Begin working on new status handling
 *
 *   Revision 1.15  2005/02/06 09:00:25  goldin
 *   Fix javadoc warnings
 *
 *   Revision 1.14  2002/09/15 16:20:39  goldin
 *   Make status translation retrieval more robust
 *
 *   Revision 1.13  2002/09/11 23:33:47  goldin
 *   Add new method to get real filename for =R etc.
 *
 *   Revision 1.12  2002/09/10 20:07:56  goldin
 *   Call status update even if you get a NAK and thus no attributes
 *
 *   Revision 1.11  2002/03/06 17:47:50  goldin
 *   No more 'current' color file
 *
 *   Revision 1.10  2002/02/15 23:22:10  goldin
 *   Screen out $$M
 *
 *   Revision 1.9  2001/11/30 18:01:21  goldin
 *   Moved most of the UI basic components to the com.grs.gui package
 *
 *   Revision 1.8  2001/11/16 16:41:08  goldin
 *   Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *   Revision 1.7  2001/11/05 13:59:16  goldin
 *   Put UI code in a package
 *
 *   Revision 1.6  2001/10/26 18:03:25  goldin
 *   Working on UI side of C/EDI
 *
 *   Revision 1.5  2001/10/08 11:56:47  goldin
 *   Add code to enable/disable Save menu items
 *
 *   Revision 1.4  2001/08/28 11:37:19  goldin
 *   Fix null bug when running standalone (and thus no status info)
 *
 *   Revision 1.3  2001/07/18 15:25:30  goldin
 *   Working to fix problems with handling of 'current' color scheme
 *
 *   Revision 1.2  2001/07/10 17:19:17  goldin
 *   Revise status update for sig info - incomplete
 *
 *   Revision 1.1  2001/07/05 08:18:03  goldin
 *   Add new classes
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.*;
import java.util.*;
import javax.swing.*;

/**
 * This class maintains information about the application status,
 * based on the attributes in reply files returned from the server
 * in each reply file. 
 * <p>
 * The class is responsible for formatting information
 * in the Status window (if the user selects this), and also for
 * making sure that the current Sig File processor is kept up-to-date.
 */
public class StatusManager implements MemoryFilter
    { 
      /**
       * Constant strings for attribute names.
       * Make these public so that other classes can use
       * them to request values.
       */
    public static final String MFILE = "MFile";
    public static final String MPATH = "MPath";
    public static final String MLINES = "MLines";
    public static final String MPIXELS = "MPixels";
    public static final String MFILETYPE = "MFileType";
    public static final String MOP = "MOp";
    public static final String MASK = "Mask";
    public static final String RFILE = "RFile";
    public static final String RPATH = "RPath";
    public static final String RLINES = "RLines";
    public static final String RPIXELS = "RPixels";
    public static final String RFILETYPE = "RFileType";
    public static final String GFILE = "GFile";
    public static final String GPATH = "GPath";
    public static final String GLINES = "GLines";
    public static final String GPIXELS = "GPixels";
    public static final String GFILETYPE = "GFileType";
    public static final String BFILE = "BFile";
    public static final String BPATH = "BPath";
    public static final String BLINES = "BLines";
    public static final String BPIXELS = "BPixels";
    public static final String BFILETYPE = "BFileType";
    public static final String COLORFILE = "COLORFILEFile";
    public static final String COLORPATH = "COLORFILEPath";
    public static final String SIGFILE = "SigFile";
    public static final String PLYFILE = "PlyFile";

    public static final String SIGCURRENT = "$$S.SIG";
    public static final String PLYCURRENT = "$$P.PLY";

      /**
       * Translated strings to use in status display.
       * Initialized by the constructor.
       */
    protected String IMAGE = null;
    protected String UNKNOWN = null;
    protected String EMPTY = null;
    protected String DERIVED = null;
    protected String FILE = null;
    protected String MASKED = null;
    protected String CLASSIFIED = null;
    protected String MAINIMAGE = null;
    protected String BLUEIMAGE = null;
    protected String GREENIMAGE = null;
    protected String REDIMAGE = null;
    protected String LINES = null;
    protected String PIXELS = null;
    protected String FILETYPE = null;
      /**
       * Attribute-value hashtable,
       * holds current state information as provided by Rpy file.
       */
    protected Hashtable stateTable = null;

      /**
       * Reference to parent application
       */
    protected DragonUI mainApp = null;


      /**
       * Constructor, initializes mainApp
       */
    public StatusManager(DragonUI mainApp)
        {
	this.mainApp = mainApp;
        String translation = mainApp.getTextSource().getI18NText("%e314",
 "IMAGE|UNKNOWN|EMPTY|FILE|MASKED|CLASSIFIED|DERIVED");
	StringTokenizer tokenizer = new StringTokenizer(translation,"|");
	int which = 0;
	while (tokenizer.hasMoreTokens())
	    {
	    String token = tokenizer.nextToken();
	    switch (which)
	      {
 	      case 0:
		  IMAGE = token.trim();
	          break;
 	      case 1:
		  UNKNOWN = token.trim();
	          break;
 	      case 2:
		  EMPTY = token.trim();
	          break;
 	      case 3:
		  FILE = token.trim();
	          break;
  	      case 4:
		  MASKED = token.trim();
	          break;
  	      case 5:
		  CLASSIFIED = token.trim();
	          break;
  	      case 6:
		  DERIVED = token.trim();
	          break;
	      }
	    which++;
	    }
        translation = mainApp.getTextSource().getI18NText("%e315",
		  " MAIN IMAGE|  RED IMAGE|GREEN IMAGE| BLUE IMAGE");
	tokenizer = new StringTokenizer(translation,"|");
	which = 0;
	while (tokenizer.hasMoreTokens())
	    {
	    String token = tokenizer.nextToken();
	    switch (which)
	      {
 	      case 0:
		  MAINIMAGE = token.trim();
	          break;
 	      case 1:
		  BLUEIMAGE = token.trim();
	          break;
 	      case 2:
		  GREENIMAGE = token.trim();
	          break;
 	      case 3:
		  REDIMAGE = token.trim();
	          break;
	      }
	    which++;
	    }
        LINES = mainApp.getTextSource().getI18NText("%h9500.1","Lines");
        PIXELS = mainApp.getTextSource().getI18NText("%h9500.0","Pixels");
        FILETYPE = mainApp.getTextSource().getI18NText("%h3030.7","File Type");
      
	}
     
     /**
      * Clear out all status information. This normally
      * happens only if there's an error.
      */
    public void clearCurrentState()
        {
        if (stateTable != null)
            stateTable.clear();
        } 

     /**
       * Primary method for updating state. Called by
       * the CommandForwarder when the reply file from a 
       * command is returned.
       */
    public void setCurrentState(Hashtable attributes)
        {
	if (attributes != null)
	    stateTable = attributes;
	updateSignatureInfo();
        updatePolygonInfo();
	}

      /**
       * Update the information in the state table and
       * the currentSigProcessor to reflect current signature
       * state.
       */
    protected void updateSignatureInfo()
        {
        String sigFileName = null;
	SigFileProcessor currentSigProcessor = null;
        File sigFile = new File(ApplicationManager.getTempPath(),
				SIGCURRENT);
        if (sigFile.exists())
	    {
            sigFileName = sigFile.getAbsolutePath();
            stateTable.put(SIGFILE,sigFileName);
	    currentSigProcessor = mainApp.getCurrentSigProcessor();
	    if (currentSigProcessor == null)
	        currentSigProcessor = new SigFileProcessor(sigFileName);
	    else
	        {
	        currentSigProcessor.clear();
		currentSigProcessor.init(sigFileName);
		}
	    currentSigProcessor.setInitialized(true);
            mainApp.setCurrentSigProcessor(currentSigProcessor);
	    }
	else
	    {
	    mainApp.setCurrentSigProcessor(null);
            stateTable.remove(SIGFILE);
	    }
	}

      /**
       * Update the information in the state table
       * to reflect current polygon state.
       */
    protected void updatePolygonInfo()
        {
        File plyFile = new File(ApplicationManager.getTempPath(),
				PLYCURRENT);
        if (plyFile.exists())
	    {
            stateTable.put(PLYFILE,plyFile.getAbsolutePath());
	    }
	else
	    {
            stateTable.remove(PLYFILE);
	    }
	}

      /**
       * Compose a new status table and return it.
       * Make this method public so that it can be called when
       * the user switches to the status display from Help or History.
       */
    public String getStatusData()
        {
	String temp = null;
        if (stateTable == null)
	    return null;
	DImageHeader memoryHeader = mainApp.getMemoryHeader();
	if (memoryHeader != null)
	   {
	   String fileType = memoryHeader.getFileType();
	   stateTable.put(MFILETYPE,fileType);
           }
	StringBuffer htmlContent = new StringBuffer(1024);
        htmlContent.append("<HTML><BODY><dl>\n");
        htmlContent.append("<dd><b>" + MAINIMAGE + 
                  ":</b>&nbsp;");
	temp = (String) stateTable.get(MFILE);
	if (temp == null)
	    {
	    htmlContent.append(EMPTY + "&nbsp;&nbsp;&nbsp;&nbsp;");
            }                    
	else
	    {
	    if (temp.compareToIgnoreCase("$$m.img") == 0)
               temp = (String) stateTable.get(MOP);
	    htmlContent.append(temp + "&nbsp;&nbsp;");
	    temp = (String) stateTable.get(MLINES);
	    if (temp != null)
	        htmlContent.append("("+temp + " x ");
	    temp = (String) stateTable.get(MPIXELS);
	    if (temp != null)
	        htmlContent.append(temp + ",&nbsp;&nbsp;");
	    temp = (String) stateTable.get(MFILETYPE);
	    if (temp != null)
	        htmlContent.append(FILETYPE +
                          "&nbsp;" +
                          temp + ")");
	    }
	htmlContent.append("</dd>\n");
        htmlContent.append("<dd><b>" + REDIMAGE + 
                  ":</b>&nbsp;");
	temp = (String) stateTable.get(RFILE);
	if (temp == null)
	    {
	    htmlContent.append(EMPTY + "&nbsp;&nbsp;&nbsp;&nbsp;");
            }                    
	else
	    {
	    htmlContent.append(temp + "&nbsp;&nbsp;");
	    temp = (String) stateTable.get(RLINES);
	    if (temp != null)
	        htmlContent.append("("+temp + " x ");
	    temp = (String) stateTable.get(RPIXELS);
	    if (temp != null)
	        htmlContent.append(temp + ")");
	    }
	htmlContent.append("</dd>\n");

        htmlContent.append("<dd><b>" + GREENIMAGE + 
                  ":</b>&nbsp;");
	temp = (String) stateTable.get(GFILE);
	if (temp == null)
	    {
	    htmlContent.append(EMPTY + "&nbsp;&nbsp;&nbsp;&nbsp;");
            }                    
	else
	    {
	    htmlContent.append(temp + "&nbsp;&nbsp;");
	    temp = (String) stateTable.get(GLINES);
	    if (temp != null)
	        htmlContent.append("("+temp + " x ");
	    temp = (String) stateTable.get(GPIXELS);
	    if (temp != null)
	        htmlContent.append(temp + ")");
	    }
	htmlContent.append("</dd>\n");

        htmlContent.append("<dd><b>" + BLUEIMAGE + 
                  ":</b>&nbsp;");
	temp = (String) stateTable.get(BFILE);
	if (temp == null)
	    {
	    htmlContent.append(EMPTY + "&nbsp;&nbsp;&nbsp;&nbsp;");
            }                    
	else
	    {
	    htmlContent.append(temp + "&nbsp;&nbsp;");
	    temp = (String) stateTable.get(BLINES);
	    if (temp != null)
	        htmlContent.append("("+temp + " x ");
	    temp = (String) stateTable.get(BPIXELS);
	    if (temp != null)
	        htmlContent.append(temp + ")");
	    }
	htmlContent.append("</dd>\n");
	temp = (String) stateTable.get(MASK);
        if (temp != null)
	    {
            htmlContent.append("<dd><b>" + 
			       MASKED + ":</b>&nbsp;"+ temp);
	    htmlContent.append("</dd>");
            }                    
	htmlContent.append("</dl></BODY></HTML>\n");
        return htmlContent.toString();
	}

      /**
       * Given a memory file such as "=R", returns the relevant
       * filename, or null if not found in the attributes
       * table. If this is called for "=M" it is likely to
       * return $$M.IMG. Fair warning!
       * @param memoryFile String we want to look up.
       * @return File equivalent of memory file or null if not found.
       */
    public String getMemoryFileEquivalent(String memoryFile)
        {
	String tempVal = null;
	String tempVal2 = null;
	if (stateTable == null)
            return null;
	if (memoryFile.compareTo("=M") == 0)
            {
	    tempVal = (String) stateTable.get(MFILE);
	    tempVal2 = (String) stateTable.get(MPATH);
	    }
	else if (memoryFile.compareTo("=B") == 0)
            {
	    tempVal = (String) stateTable.get(BFILE);
	    tempVal2 = (String) stateTable.get(BPATH);
	    }
	else if (memoryFile.compareTo("=G") == 0)
            {
	    tempVal = (String) stateTable.get(GFILE);
	    tempVal2 = (String) stateTable.get(GPATH);
	    }
	else if (memoryFile.compareTo("=R") == 0)
            {
	    tempVal = (String) stateTable.get(RFILE);
	    tempVal2 = (String) stateTable.get(RPATH);
	    }
        /* ~~~~ WHY??? */
	else if (memoryFile.compareTo("=C") == 0)
            {
	    tempVal = (String) stateTable.get(RFILE);
	    tempVal2 = (String) stateTable.get(RPATH);
	    }
	if (tempVal != null)
	    return tempVal2 + File.separator + tempVal;
	else
            return null;
	}

      /**
       * This method returns true if passed memory file (=M,=B,=G, and so on)
       * is currently populated with non-null data.
       * Otherwise it returns false. Used for file validation.
       * @param fileType File type this is being used to satisfy
       * @param memoryFile One of =M,=R,=G,=B,=C, or (Current) for sigs,clf ply
       */
    public boolean isMemoryFileValid(DFileType fileType, String memoryFile)
        {
	String tempVal = null;
	if (stateTable == null)  // no status - may be running standalone
	    {
	    return false;
	    }
	else if (memoryFile.startsWith("("))
            {
            if (fileType == DFileType.SIGNATURE)
	        tempVal = (String) stateTable.get(SIGFILE);
	    else if (fileType == DFileType.POLYGON)
	        tempVal = (String) stateTable.get(PLYFILE);
            else if (fileType == DFileType.COLOR)
	        tempVal = (String) stateTable.get(COLORFILE);
 
	    //System.out.println("In isMemoryFileValid, tempVal is " +
            //                   tempVal + " and file type is " +
	    //		       fileType);
	    }
	else 
	    {
	    tempVal = getMemoryFileEquivalent(memoryFile);
	    }
        return (tempVal != null);
	}

      /**
       * Allow other components to set knowledge about the
       * Signature or Polygon existence.
       */
    public void setSignaturesCurrent()
        {
        stateTable.put(SIGFILE,"$$S.SIG");
	}

    public void setPolygonsCurrent()
        {
        stateTable.put(PLYFILE,"$$P.PLY");
	}

      /**
       * Examine all the allowed memory files and create a new
       * array which contains only the ones that are currently
       * valid. E.g. if =M,=R,=G and =B are allowed, but no
       * 3band composite has been provided, then the resulting
       * filtered array would hold only "=M". This is the single method
       * of the MemoryFilter interface.
       */
    public String[] filterAllowedMemoryFiles(String[] allowedMemoryFiles,
					     DFileType fileType)
        {
	if ((allowedMemoryFiles == null) ||
	    (allowedMemoryFiles.length == 0))
	    return null;
        String[] retFiles = new String[allowedMemoryFiles.length];
	int j = 0;
	for (int i = 0; i < allowedMemoryFiles.length; i++)
	     {
             if (isMemoryFileValid(fileType,
					   allowedMemoryFiles[i]))
	          {
		  retFiles[j] = allowedMemoryFiles[i];
		  j++;
		  }
	     }
	return retFiles;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: StatusManager.java,v 1.22 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


