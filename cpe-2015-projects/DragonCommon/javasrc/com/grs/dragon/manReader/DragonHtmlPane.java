/**
 * DragonHtmlPane.java
 *
 *  ~~ Copyright 2001-2015 by Goldin-Rudahl Associates
 *  ~~ EndC
 *
 * Created by Sally Goldin, 11/26/2001
 *
 * $Id: DragonHtmlPane.java,v 1.8.2.1 2015/01/01 10:32:30 rudahl Exp $
 * $Log: DragonHtmlPane.java,v $
 * Revision 1.8.2.1  2015/01/01 10:32:30  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.9  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.8  2007/05/31 03:26:53  rudahl
 * add 'whatis' boilerplate
 *
 * Revision 1.7  2006/05/01 07:01:17  goldin
 * Fix logic error in processing comments - one line comment was causing skip to end of section
 *
 * Revision 1.6  2006/04/29 04:21:16  goldin
 * Screen out comments in HTML sent to manreader
 *
 * Revision 1.5  2006/04/27 06:26:38  goldin
 * Add code to rewrite image URLs to absolute paths
 *
 * Revision 1.4  2003/02/21 12:04:33  rudahl
 * Add code to check if a URL is on the currently visible page
 *
 * Revision 1.3  2002/06/24 18:04:59  goldin
 * Continue development for productization
 *
 * Revision 1.2  2001/11/27 17:37:35  goldin
 * Cache and index file contents
 *
 * Revision 1.1  2001/11/26 14:00:09  goldin
 * Continue basic implementation of ManReader
 *
 *
 */

package com.grs.dragon.manReader;
import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/**
 * This class is a simple subclass of JEditorPane which knows
 * how to interpret the Dragon META commands PageBreak and 
 * Details.
 */
public class DragonHtmlPane extends JEditorPane
    {
    protected static final String PAGEBREAK = "META name=\"PageBreak\""; 
    protected static final String DETAILURL = "META name=\"DetailURL\""; 
    protected static final String URLCONTENT = "content="; 
    protected static final String ANCHORPFX = "<a name=";
    protected static final String COMMENTPFX = "<!--";
    protected static final String COMMENTSFX = "-->";

    protected String currentUrl = null;
    protected String currentId = null;
    protected String detailUrl = null;
    protected String lastInputFile = null;

      /**
       * Line numbers of the first and last lines in the
       * currently visible page. We will use this to
       * determine if a url is part of the currently visible
       * page.
       */
    protected int lastVisibleLine = -1;
    protected int firstVisibleLine = -1;

      /**
       * Index for quickly locating a topic by URL
       */
    protected HashMap<String,Integer> lineIndex = null;
      /**
       * Vector for storing a file, line by line.
       */
    protected Vector<String> fileLines = null;

      /**
       * Directory where the class should look for 
       * documents. Set by constructor.
       */
    protected String documentBase = null;

    protected String imageBase = null;

      /**
       * Constructor initializes documentBase, sets content type
       */
    public DragonHtmlPane(String base)
        {
	super();
	setContentType("text/html");
        setEditable(false);
	documentBase = base;
	if ((documentBase == null) || (documentBase.length() == 0))
	    documentBase = ".";
	StringBuffer tempBuf = new StringBuffer();
	tempBuf.append("file:");
        try 
	   {
           tempBuf.append(new File("temp.tmp").getCanonicalFile().getParent());
	   tempBuf.append(File.separator);
           if (documentBase.startsWith("./"))
               tempBuf.append(documentBase.substring(2));
           else 
               tempBuf.append(documentBase);
           }
        catch (Exception e)
	   {
           tempBuf.append(documentBase);
           }
        imageBase = tempBuf.toString();
        //System.out.println("image base is " + imageBase);
        this.setMinimumSize(new Dimension(600,300));
        this.setPreferredSize(new Dimension(600,300));
	}
	
    public void setPage(String url, String id)
        {
	currentUrl = url;
	currentId = id;
	detailUrl = null;
	boolean bFoundTopic = false;
        boolean bInComment = false;
	int lineNum = 0;
        StringBuffer buffer = new StringBuffer(4096);
	int pos = url.indexOf("#");
        String inputFile = documentBase + File.separator +
	  ((pos < 0) ? url : url.substring(0,pos));
	String anchor = null;
	if (pos >= 0)
	    anchor = "<a name=\"" + url.substring(pos+1) + "\">";
        try 
	    {
	    if ((inputFile != lastInputFile) ||
                (fileLines == null))
	        processFile(inputFile);
	    lastInputFile = inputFile;
	    }
	catch (IOException fnf)
	    {
	    anchor = null;  //so we'll report a bad URL 
	    }
	if (anchor != null) 
	    {
	    Integer start = (Integer) lineIndex.get(anchor);
	    if (start != null)
	        {
		bFoundTopic = true;
                lineNum = start.intValue();
		firstVisibleLine = lineNum;
		int lastNum = fileLines.size();
		while (lineNum < lastNum)
		    {
		    String inputLine = (String) fileLines.get(lineNum);
                    if (inputLine.indexOf(PAGEBREAK) >= 0)
		        break;
		    inputLine = adjustImageUrls(inputLine);
		    /* The HTMLEditorKit/JEditorPane seems to
                     * get confused by comments in the HTML.
                     * They cause consistent, repeated index out
                     * of bounds errors. So we strip them out here.
                     * We assume that the comments are not
                     * mixed on the same line with good text.
		     * If they are, we will miss them or leave
                     * out the good text.
		     */
		    /* step 1 - check for comment start */
      		    if (inputLine.startsWith(COMMENTPFX))
		        {
                        bInComment = true;
                        }
		    if (!bInComment)  // only add non-comment lines
		        {
		        buffer.append(inputLine + "\n");
			}
                    /* after deciding whether to add, check for comment end */
		    if ((inputLine.indexOf(COMMENTSFX) >= 0) 
                             && (bInComment))
		        {
                        bInComment = false;
                        }
		    if (inputLine.indexOf(DETAILURL) >= 0)
		        {
			int pos2 = inputLine.indexOf(URLCONTENT);
			if (pos2 >= 0)
			    {
                            int pos3 = inputLine.indexOf("\"",
					    pos2 + URLCONTENT.length()+2);
			    detailUrl = inputLine.substring(
					  pos2 + URLCONTENT.length()+1,
					  pos3);
			    }

			}  // end if DETAILURL Found
		    lineNum++;
		    }  // end of loop
		}      // end if topic found
	     if (!bFoundTopic)  // bad URL?
	         buffer.append("<h3>Topic not found: " + url + "</h3>");
	     setText(buffer.toString());
	     lastVisibleLine = lineNum;
	     }
	else 
	     {
	     buffer.append(
	        "<h3>Topic or filename not found: " + url + "</h3>");
	     setText(buffer.toString());
	     }
	}

      /** 
       * Search for any "<img>" tags in this line.
       * If we find one, add the document base to
       * the "src" attribute.
       * @param origLine  Line read from file
       * @return either original line or line with prefix on the
       * URLS for the image file.
       */
    protected String adjustImageUrls(String origLine)
        {
        StringBuffer buffer = new StringBuffer();
        int pos = origLine.indexOf("<img src=");
        if (pos < 0)
            buffer.append(origLine);
        else // parse and add in the document base
	    {
            int pos2 = origLine.indexOf("=",pos);
            buffer.append(origLine.substring(0,pos2+2));
            buffer.append(imageBase + File.separator);
            buffer.append(origLine.substring(pos2+2));
            //System.out.println("adjusted image URL to: " + buffer.toString());
            }
        return buffer.toString();
        }
    
      /**
       * Read the file into the line vector and construct
       * an index of all anchors.
       * @param inputFile  File to be processed
       */
    protected void processFile(String inputFile) 
                   throws IOException
        {
	int lineCount = 0;
	if (fileLines == null)
	    fileLines = new Vector<String>(4096);
	else
	    fileLines.removeAllElements();
	if (lineIndex == null)
            lineIndex = new HashMap<String,Integer>(512);
	else
	    lineIndex.clear();
	BufferedReader reader = new BufferedReader(
			 new FileReader(inputFile));
	String inputLine = null;
	while ((inputLine = reader.readLine()) != null)
	    {
	    fileLines.add(inputLine);
	    if (inputLine.indexOf(ANCHORPFX) >= 0)
	        {
		String anchor = extractAnchor(inputLine);
		lineIndex.put(anchor,new Integer(lineCount));
	        }
	    lineCount++;
	    }  // end of loop
	reader.close();
	}


      /**
       * Factorization. Given a line, extract and return the first
       * anchor construct (i.e. <a name="anchorname">) from the
       * line and return that string.
       * @param line Line of text to be parsed.
       */
    protected String extractAnchor(String line)
        {
	int p1, p2 = 0;
	int maxpos = line.length() - 1;
	p1 = line.indexOf(ANCHORPFX);
	p2 = line.indexOf("\"",p1+2);
        while ((line.charAt(p2) != '>') &&
               (p2 < maxpos))
             p2++;
        if (p2 == maxpos)
	    return line.substring(p1);
	else
	    return line.substring(p1,p2+1);
	}

      /**
       * Check to see if the passed URL is located
       * on the current page. Used to implement a more
       * intelligent "nextTopic" and "previousTopic"
       * @param url   The url of the candidate topic
       * @return true if the url is on the present page,
       *              else false
       */
    public boolean onCurrentPage(String url)
        {
	boolean bOnPage = false;
	if (lastVisibleLine > 0)
	  {
	  int lineNum = 0;
	  int pos = url.indexOf("#");
	  String inputFile = documentBase + File.separator +
	    ((pos < 0) ? url : url.substring(0,pos));
	  String anchor = null;
	  if (pos >= 0)
	    anchor = "<a name=\"" + url.substring(pos+1) + "\">";
	  if ((inputFile.compareTo(lastInputFile) == 0) &&
	      (anchor != null))
	    {
	    Integer start = (Integer) lineIndex.get(anchor);
	    if (start != null)
	        {
                lineNum = start.intValue();
		if ((lineNum >= firstVisibleLine) &&
		    (lineNum <= lastVisibleLine))
		   bOnPage = true;
		}
	    }
	  }
	return bOnPage;
	}

    public String getCurrentUrl()
        {
	return currentUrl;
	}

    public String getCurrentId()
        {
	return currentId;
	}

    public String getDetailUrl()
        {
	return detailUrl;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonHtmlPane.java,v 1.8.2.1 2015/01/01 10:32:30 rudahl Exp $ \n";
	}

    }
