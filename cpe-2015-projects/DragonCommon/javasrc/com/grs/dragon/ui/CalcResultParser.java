/**
 * CalcResultParser.java
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 5/21/2001
 *
 * $Id: CalcResultParser.java,v 1.28 2007/01/05 07:41:57 rudahl Exp $
 * $Log: CalcResultParser.java,v $
 * Revision 1.28  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.27  2006/12/31 09:25:07  goldin
 * Implement modifiable help display
 *
 * Revision 1.26  2006/11/30 08:40:38  goldin
 * Add some new formatting options, new MultiSimpleTable type
 *
 * Revision 1.25  2006/11/18 10:52:55  goldin
 * Implementing Import user interface
 *
 * Revision 1.24  2005/04/25 13:56:28  goldin
 * Revise to remove version field in header report
 *
 * Revision 1.23  2004/12/30 13:16:34  goldin
 * Fix HTML generation when no report header
 *
 * Revision 1.22  2002/08/26 15:47:08  goldin
 * Fix report format
 *
 * Revision 1.21  2002/07/18 19:49:12  goldin
 * Fix position of comment in LIS report
 *
 * Revision 1.20  2002/03/23 02:10:49  goldin
 * Add handling for 'source
 *
 * Revision 1.19  2002/03/06 21:11:45  goldin
 * Ignore 'isDisplay'
 *
 * Revision 1.18  2002/01/22 15:11:48  goldin
 * Center tables for better visual effect
 *
 * Revision 1.17  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.16  2001/11/05 13:59:14  goldin
 * Put UI code in a package
 *
 * Revision 1.15  2001/10/19 16:22:46  goldin
 * Further work on table formatting
 *
 * Revision 1.14  2001/10/18 15:04:13  goldin
 * Further development work on special HTML tables
 *
 * Revision 1.13  2001/10/17 17:49:23  goldin
 * Begin rework of HTML reports
 *
 * Revision 1.12  2001/10/12 18:39:58  goldin
 * Work on table format
 *
 * Revision 1.11  2001/09/05 15:08:53  goldin
 * Change I18NTextSource constructors
 *
 * Revision 1.10  2001/08/23 18:05:40  goldin
 * Add functionality to interpret TextTable calcResult messages
 *
 * Revision 1.9  2001/07/12 13:14:33  goldin
 * Make processing more robust
 *
 * Revision 1.8  2001/07/04 12:17:45  goldin
 * Remove width=
 *
 * Revision 1.7  2001/06/28 14:05:45  goldin
 * Continue work on table formatting
 *
 * Revision 1.6  2001/06/27 15:17:47  goldin
 * Fix CalcParser bugs, table formatting
 *
 * Revision 1.5  2001/06/18 12:09:59  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.4  2001/06/15 16:26:14  goldin
 * Modify CalcResultParser to handle different output formats
 *
 * Revision 1.3  2001/06/13 14:12:17  goldin
 * Add noteline etc to calcparser logic
 *
 * Revision 1.2  2001/05/22 12:05:13  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 * Revision 1.1  2001/05/21 15:55:39  goldin
 * Add class to parse XML description of table
 *
 */


package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import java.io.*;
import org.xml.sax.*;

//*************************************************************************+
/** 
 * This class reads and parses an XML document describing a DRAGON
 * calculated results table. It translates that document into
 * an HTML document for display within Dragon.
 * Depending on the value of the calcType attribute, items
 * may be interpreted in very different ways.
 * @author  goldin
 */

public class CalcResultParser extends HandlerBase 
    {
    protected static final String NBSSTRING =
      "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";

      /**
       * Constants for calctypes
       */
    protected final static int SIMPLE_TABLE = 0;
    protected final static int WIDE_TABLE_SINGLE_ROW = 1;
    protected final static int WIDE_TABLE_MULTI_ROW = 2;  
    protected final static int TEXT_TABLE = 3;  
    protected final static int SIG_TABLE = 4;
    protected final static int HEADER_TABLE = 5;
    protected final static int MULTI_TABLE = 6;
    protected final static int MULTI_SIMPLE_TABLE = 7;

    protected String bandString = null;
      /**
       * Array used to determine item categories
       */
    protected final String[] itemCategories = {"classname",  	// 0
					   "filename",  	// 1
					   "lines",  		// 2
					   "pixels",  		// 3
					   "bits",  		// 4
					   "version",  		// 5
					   "filetype",  	// 6
					   "clrfile",  		// 7
					   "scene",  		// 8
					   "subscene",  	// 9
					   "band",  		// 10
					   "comment",  		// 11
					   "mean",  		// 12
					   "min",  		// 13
					   "max",  		// 14
					   "variance",  	// 15
					   "standev",  		// 16
					   "fixedpt",  		// 17
					   "referencept",  	// 18
					   "xcellsize",  	// 19
					   "ycellsize",  	// 20
					   "unit",  		// 21
					   "caliboffset",  	// 22
					   "calibmult",  	// 23
					   "calibunit",  	// 24
					   "signame",  		// 25
					   "signumpts",  	// 26
					   "image",  		// 27
					   "lower",  		// 28
					   "upper",  		// 29
					   "covariance",  	// 30
					   "source",            // 31
					   "sigsource"};        // 32


      /**
       * Array of column span values for custom positioning.
       */
      protected final int[] itemSpan = {1,   //"classnamee"      0
					3,   //"filename",  	 1
					1,   //"lines",  	 2
					1,   //  "pixels",  	 3
					1,   //  "bits",  	 4
					1,   //  "version",  	 5
					1,   //  "filetype",  	 6
					1,   //  "clrfile",  	 7
					1,   //  "scene",  	 8
					1,   //  "subscene",  	 9
					1,   //  "band",  	 10
					3,   //  "comment",  	 11
					1,   //  "mean",  	 12
					1,   //  "min",  	 13
					1,   //  "max",  	 14
					1,   //  "variance",  	 15
					1,   //  "standev",  	 16
					1,   //  "fixedpt",  	 17
					2,   //  "referencept",  18
					1,   //  "xcellsize",  	 19
					1,   //  "ycellsize",  	 20
					1,   //  "unit",  	 21
					1,   //  "caliboffset",  22
					1,   //  "calibmult",  	 23
					1,   //  "calibunit",  	 24
					5,   //  "signame",  	 25
 					3,   //  "signumpts",  	 26
					2,   //  "image",        27
					1,   //  "lower",  	 28
					1,   //  "upper",  	 29
					5,   //  "covariance",   30
					1,   //  "source"        31
					3};   //  "sigsource"     32

      /**
       * Array associating header labels with data. Only used
       * for signature report
       */
      protected final int[] hdrIndex = {-1,   //"classname"      0
					-1,   //"filename",  	 1
					-1,   //"lines",  	 2
					-1,   //  "pixels",  	 3
					-1,   //  "bits",  	 4
					-1,   //  "version",  	 5
					-1,   //  "filetype",  	 6
					-1,   //  "clrfile",  	 7
					-1,   //  "scene",  	 8
					-1,   //  "subscene",  	 9
					-1,   //  "band",  	 10
					-1,   //  "comment",  	 11
					 4,   //  "mean",  	 12
					 6,   //  "min",  	 13
					 7,   //  "max",  	 14
					 5,   //  "variance",  	 15
					-1,   //  "standev",  	 16
					-1,   //  "fixedpt",  	 17
					-1,   //  "referencept",  18
					-1,   //  "xcellsize",    19
					-1,   //  "ycellsize",    20
					-1,   //  "unit",  	 21
					-1,   //  "caliboffset",  22
					-1,   //  "calibmult",    23
					-1,   //  "calibunit",    24
					 0,   //  "signame",  	 25
					 1,   //  "signumpts",    26
					 3,   //  "image",        27
					 8,   //  "lower",  	 28
					 9,   //  "upper",  	 29
					 10,  //  "covariance",   30
					-1,   //  "source"        31
					 2};  //  "sigsource"     32



      /**
       * DTD file name 
       */
    protected String dtdFileName;


      /**
       * Reader that provides primary access to the XML data
       */
    protected StringReader xmlReader = null;


      /**
       * Class that provides access to internationalized text.*/
    protected I18NTextSource textSource = null;

      /**
       * keep track of nested element level 
       * Used in tracing
       */
    protected int nestLevel = 0;
    protected String nestString = "";

    protected boolean bTracing = false;

      /**
       * String buffer where we are accumulating the
       * HTML translation.
       */
    protected StringBuffer htmlContent = null;	

      /**
       * Save the title of the whole table, so we can
       * retrieve it.
       */
    protected String tableTitle = null;

      /**
       * State variables.
       */
    protected boolean bParsingResultField = false;
    protected boolean bTableStarted = false;

      /**
       * Vector to hold accumulated strings during a
       * help, label, default, tooltip or choices element.
       */
    protected Vector xlatedText = null;

      /**
       * Tags corresponding to each element in xlatedText.
       * Needed for formatting after all the elements have
       * been found and translations retrieved.
       */
    protected Vector textTag = null;

      /**
       * Keys corresponding to each element in xlatedText.
       * Used for debugging.
       */
    protected Vector textKey = null;

      /**
       * how many columns in current table?
       */
    protected String fieldCount = "1";

      /**
       * Hashtable for attributes
       */
    protected Hashtable attributes = null;

      /**
       * Hold onto a copy for resultfields
       */
    protected Hashtable itemAttributes = null;

      /**
       * What type of result do we have?
       */
    protected int calcTypeCode = SIMPLE_TABLE;

      /**
       * mapping columns to groups
       */
    protected Vector columnGroups = null;

      /**
       * mapping columns to display value (yes/no/maybe)
       */
    protected Vector columnDisplay = null;

      /**
       * mapping columns to column titles.
       */
    protected Vector columnTitles = null;

      /**
       * maps groups to their titles if any
       */
    protected Vector groupTitles = null;
      /**
       * map groups to their IDs
       */
    protected Vector groupIds = null;

      /**
       * Keeps track of current column number in either
       * headers or data fields.
       */
    protected int currentColumn = 0;
  
      /**
       * Keeps track of current column number relative to 
       * start of row.
       */
    protected int columnInRow = 0;

      /**
       * Keep track of bands during signature reporting.
       */
    protected int bandIndex = 0;

      /**
       * Keeps track of current group. 
       * If null, no current group.
       */
    protected String currentGroup = null;

      /**
       * keep track of group count
       */
    protected int currentGroupIndex = -1;

      /**
       * Are we processing a group?
       */
    protected boolean bProcessingGroup = false;
      /**
       * Data Type of result item being processed
       */
    protected XMLTag currentDataType = null;

      /**
       * maximum number of items in a group.
       * and number of items in current group
       * Used to establish how many rows per line.
       */
    protected int maxGroupSize = 3;
    protected int currentGroupSize = 0;
    
    protected int numItems = 0;

      /**
       * Use maximum column header width to size the columns.
       */
    protected int maxHeaderSize = 0;

//==================================================================
      /**
       * Constructor - initializes text source, and creates the reader
       * @param xmlContent String representing the XML document.
       * @param source  Text source to use for internationalization
       */
    public CalcResultParser(String xmlContent, 
			  I18NTextSource source)
	{
	textSource = source;
  	columnGroups = new Vector(64);
  	columnDisplay = new Vector(64);
	columnTitles = new Vector(64);
        groupTitles = new Vector(16);
        groupIds = new Vector(16);
        htmlContent = new StringBuffer(4026);
	xmlReader = new StringReader(xmlContent);
        bandString = textSource.getI18NText(TextKeys.BAND,"BAND");
	}


      /** 
       *  Parse the specified XML, creating the appropriate 
       *  UI data structures as described in the XML.
       *  @param  reader  XML data to parse. 
       */
    public void parse(Reader reader)
           throws ClassNotFoundException, IllegalAccessException,
	     InstantiationException, IOException, SAXException
        {
	String p = "com.ibm.xml.parser.SAXDriver";
	        // get class object for SAX Driver
	Class c = Class.forName(p);
	        // create instance of the class
	Parser parser = (Parser)c.newInstance();
	        // create document handler,
	parser.setDocumentHandler(this);
	InputSource source = new InputSource(reader);
	parser.parse(source);
	}


//==================================================================
      /** display the contents of the attribute list.
       */
    public void dumpAttributeList(AttributeList atts)
        {
	if (atts.getLength() == 0)
	    System.out.println(nestString + " (no attributes) ");
	else
	    {
	    System.out.println(nestString + " AttributeList: ");
	    for (int i = 0; i < atts.getLength(); i++)
		{
		String name = atts.getName(i);
		// String type = atts.getType(i);
		String value = atts.getValue(i);
		System.out.println(nestString + "   name=" + name + 
				     " value=" + value);
		}
	    }
	}

    public void startDocument() throws SAXException
        {
	if (bTracing)
	    System.out.println("startDocument is called");
	}

    public void endDocument() throws SAXException
        {
	if (bTracing)
	    System.out.println("endDocument is called");
	}

//==================================================================
      /* callback fn to handle startelement tags in the XML data 
       * For the dragon.dtd, startElement() and endElement()
       * do all of the important processing.

       * These methods are automatically invoked from SAX, and should 
       * not be called directly.
       */
    public void startElement(String name, AttributeList amap) 
           throws SAXException
        {
	XMLTag elementTag = XMLTag.lookUp(name);
	if (elementTag == null)
	     throw new SAXException("No tag found for element " + name);

	if (bTracing)
	    {
	    nestLevel++;
	    nestString = getLevelString();
	    System.out.println(nestString + 
			   "startElement starting: element name=" + name);
	    dumpAttributeList(amap);
	    }

	attributes = attributesToTags(amap);

        if (elementTag == XMLTag.CALCRESULT)
	    {
	    bTableStarted = false;
	    XMLTag calcType = (XMLTag) attributes.get(XMLTag.CALCTYPE);
	    String rowCount = (String) attributes.get(XMLTag.ROWCOUNT);
            int iRows = Integer.parseInt(rowCount);
	    if (calcType == XMLTag.SIMPLETABLE)
                 calcTypeCode = SIMPLE_TABLE;
	    else if (calcType == XMLTag.TEXTTABLE)
                 calcTypeCode = TEXT_TABLE;
	    else if (calcType == XMLTag.WIDEMULTILINETABLE)
	         {
                 if (iRows == 1)
                      calcTypeCode = WIDE_TABLE_SINGLE_ROW;
		 else 
		      calcTypeCode = WIDE_TABLE_MULTI_ROW;
		 }
	    else if (calcType == XMLTag.SIGNATURETABLE)
	         {
		 calcTypeCode = SIG_TABLE;
		 }
	    else if (calcType == XMLTag.HEADERTABLE)
	         {
		 calcTypeCode = HEADER_TABLE;
		 }
	    else if (calcType == XMLTag.MULTISIMPLETABLE)
	         {
		 calcTypeCode = MULTI_SIMPLE_TABLE;
		 }

	    String identifier = (String) attributes.get(XMLTag.IDENTIFIER);
	    String encoding = (String) attributes.get(XMLTag.ENCODING);
	    htmlContent.append("<HTML><HEAD><!-- " + calcType.toString() 
			       + " " + identifier + " -->\n");
	    }
	else if (elementTag == XMLTag.RESULTHEADER)
	    {
	    currentColumn = 0;
	    maxGroupSize = 0;
            numItems = 0;
	    columnInRow = 0;
	    maxHeaderSize = 0;
	    fieldCount = (String) attributes.get(XMLTag.FIELDCOUNT);
	    if (calcTypeCode == SIG_TABLE)
	        // enclosing table so we'll have a border
	        htmlContent.append("<TABLE nowrap border=2>\n");
            else if (calcTypeCode == HEADER_TABLE)
                htmlContent.append("<TABLE nowrap cellspacing=20>\n");
            else if (calcTypeCode != MULTI_SIMPLE_TABLE)
                htmlContent.append("<TABLE align=center nowrap border=2 cellspacing=20>\n");
	    bTableStarted = true;
	    if ((calcTypeCode == WIDE_TABLE_MULTI_ROW) ||
                (calcTypeCode == SIMPLE_TABLE) || 
		calcTypeCode == MULTI_SIMPLE_TABLE)
                htmlContent.append("<TR>");
	    }
	else if (elementTag == XMLTag.RESULTGROUP)
	    {
	    String group = (String) attributes.get(XMLTag.ID);
            currentGroup = group;
            groupIds.add(group);
            currentGroupSize = 0;
            currentGroupIndex += 1;
            // we might get some text, so allocate space for it
	    xlatedText = new Vector();
	    textTag = new Vector();
	    textKey = new Vector();
            bProcessingGroup = true;
	    }
	else if (elementTag == XMLTag.RESULTFIELD)
	    {
	    // we will be expecting xlateText elements, which
	    // we will accumulate until we get to the endelement.
	    // Allocate a place to put them.
	    xlatedText = new Vector();
	    textTag = new Vector();
	    textKey = new Vector();
	    columnGroups.add(currentGroup);
            if (currentGroup != null)
	        {
		currentGroupSize += 1;
		if (currentGroupSize > maxGroupSize)
                    maxGroupSize = currentGroupSize;
		}
            String display = (String) attributes.get(XMLTag.DISPLAY);
	    columnDisplay.add(display);
	    }
	else if (elementTag == XMLTag.RESULTROW)
	    {
	    if (!bTableStarted)
	       {
	       htmlContent.append("<TABLE align=center nowrap border=2 cellspacing=20>\n");
	       bTableStarted = true;
	       }
            currentColumn = 0;
	    columnInRow = 0;
            if (calcTypeCode == TEXT_TABLE)
                htmlContent.append("<P>");
            else
                htmlContent.append("<TR>");
            }
	else if (elementTag == XMLTag.RESULTITEM)
	    {
	    // we will be expecting xlateText elements, which
	    // we will accumulate until we get to the endelement.
	    // Allocate a place to put them.
	    xlatedText = new Vector();
	    textTag = new Vector();
	    textKey = new Vector();
            itemAttributes = attributes;  // save the old attributes
            currentDataType = (XMLTag) attributes.get(XMLTag.DATATYPE);
            if ((calcTypeCode == SIMPLE_TABLE)||
                (calcTypeCode == WIDE_TABLE_MULTI_ROW) ||
                (calcTypeCode == MULTI_SIMPLE_TABLE)) 
	        {
                if ((currentDataType == XMLTag.FLOAT) || 
		    (currentDataType == XMLTag.DOUBLE) ||
		    (currentDataType == XMLTag.INTEGER))
		    {
                    htmlContent.append("<TD NOWRAP align=right valign=top>");
		    }
	        else 
		    {
	            htmlContent.append("<TD NOWRAP valign=top>");
		    }
	        }
            }
	else if (elementTag == XMLTag.NEWTABLE)
	    {
	    /* let's ignore if this is not a multi simple report */
            if (calcTypeCode == MULTI_SIMPLE_TABLE)
		{ 
	        if (bTableStarted)
	           {
		   htmlContent.append("</TABLE>\n");
		    bTableStarted = false;
		   }
		if (!bTableStarted)
		    {
		    String border = (String) attributes.get(XMLTag.BORDER);
		    if (border.compareTo("true") == 0)
			    htmlContent.append("<br><TABLE align=left nowrap border=2 cellspacing=10>\n");
		     else
			    htmlContent.append("<br><TABLE align=left nowrap cellspacing=10>\n");
		    bTableStarted = true;
		    }
		currentColumn = 0;
		columnInRow = 0;
		}
            }
        else if (elementTag == XMLTag.HORIZRULE)
            {
	    if (bTableStarted)
		{
		htmlContent.append("<TR><TD COLSPAN=" + 
				   String.valueOf(currentColumn+1) + 
                                   "><HR></TD></TR>\n");
                            
                }
            else
                {
		htmlContent.append("<HR>");
                }
            }
	else if (elementTag == XMLTag.NOTELINE)
	    {
	    // we will be expecting xlateText elements, which
	    // we will accumulate until we get to the endelement.
	    // Allocate a place to put them.
	    xlatedText = new Vector();
	    textTag = new Vector();
	    textKey = new Vector();
            if (calcTypeCode != TEXT_TABLE)
	        htmlContent.append("<TD NOWRAP colspan=" + fieldCount + ">");
            }
	else if (elementTag == XMLTag.TITLE)
	    {
	    // we will be expecting xlateText elements, which
	    // we will accumulate until we get to the endelement.
	    // Allocate a place to put them.
	    xlatedText = new Vector();
	    textTag = new Vector();
	    textKey = new Vector();
	    }
	else if (elementTag == XMLTag.XLATETEXT)
	    {
	    processXlateText(attributes);
	    }

	}

//=================================================================
      /**
       * Handles all xlateText elements, by extracting the
       * key, looking up the text, and saving the tag and the
       * text in current vectors.
       */
    protected void processXlateText(Hashtable attributes)
           throws SAXException
        {
	String key = (String) attributes.get(XMLTag.ID);
	if ((xlatedText == null) || (textTag == null))
	    {
	    throw new SAXException("Encountered xlateText element (id=" +
			  key + ") outside defining element.");
	    }
	XMLTag tag = (XMLTag) attributes.get(XMLTag.TAG);
	String dflt = (String) attributes.get(XMLTag.REMIND);
	String substitute = (String) attributes.get(XMLTag.SUBSTITUTE);
	String xlated = textSource.getI18NText(key,dflt);
        // ignore lines that are bare accent graves
        if (xlated.compareTo("`") == 0)
            return;
        if (substitute != null)
	    {
	    int p1 = xlated.indexOf("%1");
	    if (p1 < 0)
	        p1 = xlated.indexOf("%s");
	    if (p1 < 0)
	        p1 = xlated.indexOf("%d");
	    if (p1 >= 0)
	        {
                int p2 = xlated.indexOf(" ",p1);
		if (p2 < 0)
		    {
                    xlated = xlated.substring(0,p1) + substitute;
		    }
		else
		    {
                    xlated = xlated.substring(0,p1) + substitute +
		             xlated.substring(p2);
		    }
		}
	    else  // just append the substitute string.
	        {
                p1 = xlated.lastIndexOf(" ");
		if (p1 < (xlated.length() - 1))
		    {
		    xlated = xlated + " ";
		    }
		xlated = xlated + substitute;
		}
	    }
	xlatedText.add(xlated);
	textTag.add(tag);
	textKey.add(key);
        if (bProcessingGroup)
            groupTitles.add(xlated);
        bProcessingGroup = false;            
	}

//==================================================================
      /* callback fn to handle endelement tags in the XML data 
       * For the rmw.dtd, startElement() and endElement()
       * do all of the important processing.
       * These methods are automatically invoked from SAX, and should 
       * not be called directly.
       */
    public void endElement(String name) throws SAXException
        {
	if (bTracing)
	    { 
	    System.out.println(nestString + "endElement is called: " + name);
	    nestLevel--;
	    nestString = getLevelString();
	    }

	XMLTag elementTag = XMLTag.lookUp(name);
	if (elementTag == null)
	     throw new SAXException("No tag found for element " + name);

	if (elementTag == XMLTag.CALCRESULT)
	    {
            htmlContent.append("</TABLE></BODY></HTML>\n");
	    }
	else if (elementTag == XMLTag.TITLE)
	    {
	    processTextElement(elementTag);
            if (tableTitle != null)
                htmlContent.append("<TITLE>" + tableTitle +
                                   "</TITLE>\n");
	    htmlContent.append("</HEAD><BODY>\n");
	    }
	else if (elementTag == XMLTag.RESULTGROUP)
	    {
	    currentGroup = null;
	    }
	else if (elementTag == XMLTag.RESULTFIELD)
	    {
	    processTextElement(elementTag);
            currentColumn += 1;
	    }
	else if (elementTag == XMLTag.NOTELINE)
	    {
	    processTextElement(elementTag);
	    }
	else if (elementTag == XMLTag.RESULTHEADER)
	    {
            generateResultHeader();
	    }
	else if (elementTag == XMLTag.RESULTROW)
	    {
            if (calcTypeCode == TEXT_TABLE)
                htmlContent.append("</P>\n");
            else
                htmlContent.append("</TR>\n");
	    }
	else if (elementTag == XMLTag.RESULTITEM)
	    {
	    processTextElement(elementTag);
            currentColumn += 1;
	    }

	}
      
      /**
       * Factorization of endElement, processes text accumulated
       * within help, choices, default, tooltip or label elements.
       */
    protected void processTextElement(XMLTag elementTag)
           throws SAXException
        {
	if (elementTag == XMLTag.TITLE)
	    {
	    tableTitle = (String) xlatedText.get(0);
	    }
	else if (elementTag == XMLTag.RESULTFIELD)
	    {
            String colHeader = (String) xlatedText.get(0);
            columnTitles.add(colHeader);
            if (isDisplay(currentColumn))
	        {
                if (((calcTypeCode == SIMPLE_TABLE)||
                     (calcTypeCode == WIDE_TABLE_MULTI_ROW) ||
                     (calcTypeCode == MULTI_SIMPLE_TABLE))  &&
                     (currentGroupIndex < 0))
		   {
                   htmlContent.append("<TH NOWRAP valign=top>");
		   htmlContent.append("<font face=\"Courier\">");
	           htmlContent.append(colHeader);
                   htmlContent.append("</font>");
		   htmlContent.append("</TH>\n");
                   }
	       if (colHeader.length() > maxHeaderSize)
		   {
		   maxHeaderSize = colHeader.length(); 
		   }
               }
 	    }
	else if (elementTag == XMLTag.RESULTITEM)
	    {
	    String value = (String) xlatedText.get(0);
	    if (currentDataType == XMLTag.MATRIX)
	         value = formatMatrix(value);
	    else if (currentDataType == XMLTag.VECTOR)
	         {
	         value = formatVector(value);
		 }
	    if ((calcTypeCode == SIMPLE_TABLE)||
		(calcTypeCode == WIDE_TABLE_MULTI_ROW)||
		(calcTypeCode == MULTI_SIMPLE_TABLE))
                {
		htmlContent.append("<font face=\"Courier\">");
		htmlContent.append(value);
		htmlContent.append("</font>");
		htmlContent.append("</TD>\n");
	        }
	    else if (calcTypeCode == HEADER_TABLE)
	        {
		if (currentColumn == 0)
		    currentGroupIndex = -1;
		if (newGroup(currentColumn)) 
		    {
                    currentGroupIndex += 1;
		    if (currentColumn > 0)
		        htmlContent.append("</TR>");
		    htmlContent.append(
                          "<TR><TH COLSPAN=3 BGCOLOR=\"#DDDDDD\" ALIGN=LEFT>" 
			  + (String) groupTitles.get(currentGroupIndex));
		    htmlContent.append("</TH></TR>\n<TR>");
		    }
		String category = 
		     (String) itemAttributes.get(XMLTag.ITEMCATEGORY);
		int catIndex = findCategory(category);
		switch (catIndex)
		    {
		    case -1:   // unrecognized, do nothing
		       break;
		    // the following each start a new row
		    case 2:
		    case 6:
		    case 8:
		    case 12:
		    case 15:
		    case 17:
		    case 19:
		    case 22:  
		    case 31:
		       htmlContent.append("</TR>\n<TR>");
		       break;
                    case 0:  // classnames
                       int clsIdx = 0;
                       String idxString = 
                          (String) itemAttributes.get(XMLTag.ITEMINDEX);
                       if (idxString != null)
			   {
			   clsIdx = Integer.parseInt(idxString);
			   }
                       if ((clsIdx == 0) || (clsIdx == 4) ||
                           (clsIdx == 7) || (clsIdx == 10) ||
                           (clsIdx == 13)|| (clsIdx == 16))
			  {
			  htmlContent.append("</TR>\n<TR>");
			  break;
			  }
		    default:
		       break;
		    }
		String span = null;
		if (catIndex < 0)
		    span = "1";
		else
		    span = String.valueOf(itemSpan[catIndex]);
		String temp = "<b>" + 
		  (String)columnTitles.get(currentColumn) +
		  "</b>&nbsp;&nbsp;" + value ;
		htmlContent.append("<TD NOWRAP COLSPAN=" + span
				   + " valign=top>"
                                        + temp + "</TD>\n");
		}
	    else if (calcTypeCode == SIG_TABLE)
	        {
		String category = 
		  (String) itemAttributes.get(XMLTag.ITEMCATEGORY);
		int catIndex = findCategory(category);
		switch (catIndex)
		    {
		    case -1:   // unrecognized, do nothing
		       break;
		    case 25:
		       bandIndex = -1;
                       // start a new subtable
                       htmlContent.append("<TD COLSPAN=1><TABLE nowrap cellspacing=10><TR>\n");
		       break;
		    case 27:
		       bandIndex += 1;
                       htmlContent.append("</TR><TR><TD ROWSPAN=2>" 
                                    + "<b>" +  bandString 
		                    + " " + String.valueOf(bandIndex + 1)
				    + "</b>");
		       htmlContent.append("</TD>");
		       break;
		    case 13:
		    case 30:
		    case 26:
		       htmlContent.append("</TR>\n<TR>");
		       break;
		    default:
		       break;
		    }
		String span = null;
		if (catIndex < 0)
		    span = "1";
		else
		    span = String.valueOf(itemSpan[catIndex]);
		String temp = "<b>" + 
		    (String)columnTitles.get(hdrIndex[catIndex]) +
				   "</b>&nbsp;&nbsp;" + value ;
		htmlContent.append("<TD NOWRAP COLSPAN=" + span
				        + " valign=top>"
                                        + temp + "</TD>\n");
                // end the subtable after the covariance
                if (catIndex == 30)
		    {
                    htmlContent.append("</TD></TR></TABLE></TR>\n");
		    }
		}
	    numItems++;
 	    }
	else if (elementTag == XMLTag.NOTELINE)
	    {
            StringBuffer buildBuf = new StringBuffer();
	    for (int i = 0; i < xlatedText.size(); i++)
	        {
		String value = (String) xlatedText.get(i);
		if (i == 0)
		    buildBuf.append(value);
		else
		    {
		    XMLTag tag = (XMLTag) textTag.get(i);
		    if (tag == XMLTag.FRAGMENT)
		        {
			buildBuf.append(" " + value);
			}
		    else
		        {
			break;
			}
		    }
		}
	    htmlContent.append(buildBuf.toString() + "</TD>\n");
	    }
	// get rid of text and tags - we are done with them
	xlatedText.clear();
	xlatedText = null;
	textTag.clear();
	textTag = null;
	}

      /**
       * Factorization of endElement. Generates an appropriate
       * set of column headers, with or without groups.
       * We assume that the initial <TR> has already been generated.
       */
    protected void generateResultHeader()
        {
        if ((calcTypeCode != SIMPLE_TABLE) &&
            (calcTypeCode != WIDE_TABLE_MULTI_ROW)&&
            (calcTypeCode != MULTI_SIMPLE_TABLE))
	    return;   // no headers for these
	if (currentGroupIndex >= 0)   // there are groups, we need
	                              // two sets of headers
	    {
            for (int grp = 0; grp <= currentGroupIndex; grp++)
	         {
                 String groupId = (String) groupIds.get(grp);
                 int colCount = countGroupColumns(groupId);
		 htmlContent.append("<TH NOWRAP COLSPAN=" + 
				    String.valueOf(colCount)+
                                    ">");
                 htmlContent.append((String) groupTitles.get(grp));
		 htmlContent.append("</TH>\n");
                 }
	    htmlContent.append("</TR>\n<TR>");
            for (int col=0; col < currentColumn; col++)
	         {
		 htmlContent.append("<TH NOWRAP align=left>");
		 htmlContent.append((String) columnTitles.get(col));
		 htmlContent.append("</TH>\n");
                 }
            }
	htmlContent.append("</TR>\n");
	}

//*********************************************************************
      /**
       * Access Methods
       */
    public Reader getXmlReader()
        {
	return xmlReader;
	}

    public void setTracing(boolean flag)
        {
	bTracing = flag;
	}
      
    public boolean getTracing()
        {
	return bTracing;
	}

      /** These should only be called AFTER parsing.
       */
    public String getParsedContent()
        {
	return htmlContent.toString();
        }

    public String getTableTitle()
        {
	return tableTitle;
	}


//*********************************************************************
     
      /**
       * Debug fn. Return a string with 'nestLevel' angle brackets
       */
    protected String getLevelString()
        {
	StringBuffer buf = new StringBuffer();
	for (int i = 0; i < nestLevel; i++)
	    buf.append(">");
	return buf.toString();
	}

      /**
       * Factorization. Turns a string intended to be a matrix
       * into a subtable. First item is dimension of the matrix.
       * remaining items are elements.
       */
    protected String formatMatrix(String input)
        {
	StringBuffer buffer = new StringBuffer();
	int dimension = 0;
	StringTokenizer tokenizer = new StringTokenizer(input," ");
	String temp = tokenizer.nextToken();
	if (temp != null)
	    { 
	    dimension = Integer.parseInt(temp);
	    buffer.append("<table nowrap cellspacing=10 cols=" + temp + ">");
	    for (int i = 0; i < dimension; i++)
	        {
		buffer.append("<tr>");
                for (int j=0; j < dimension; j++)
		     {
                     if (tokenizer.hasMoreTokens())
		         {
			 temp = tokenizer.nextToken();
			 buffer.append("<td nowrap>" + temp + "</td>");
			 }
		     }
		buffer.append("</tr>");
		}
	    buffer.append("</table>");
	    }
        return buffer.toString();
	}

    /**
     * Factorization. Returns the number of columns in the
     * group with id "groupId"
     */
    protected int countGroupColumns(String groupId)
        {
        int returnVal = 0;
        for (int i = 0; i < columnGroups.size(); i++)
	     {
             String grp = (String) columnGroups.get(i);
	     if (grp.compareTo(groupId) == 0)
                 returnVal++;
	     }
	return returnVal;
	}

      /**
       * Factorization. Turns a string intended to be a vector
       * into a string with fixed spacing for each value.
       * We assume that we'll never have values more than six chars long
       * so we allow 7 spaces for each field.
       */
    protected String formatVector(String input)
        {
	StringBuffer buffer = new StringBuffer();
	StringTokenizer tokenizer = new StringTokenizer(input," ");
	String temp;
        while (tokenizer.hasMoreTokens())
	    {
	    temp = tokenizer.nextToken();
	    buffer.append(NBSSTRING.substring(0,(7-temp.length())*6));
	    buffer.append(temp);
	    }
        return buffer.toString();
	}

      /**
       * Factorization. Returns true if current column has a
       * display value of "yes"
       */
    protected boolean isDisplay(int colNo)
        {
        try 
	    {
	    String colDisplay = (String) columnDisplay.get(colNo);
	    return (colDisplay.compareTo("yes") == 0);
	    }
        catch (Exception e)
	    {
	    return false;
	    }
	}

      /**
       * Factorization. Returns true if current column has a
       * different group than the previous one.
       */
    protected boolean newGroup(int colNo)
        {
	if (colNo == 0) // first column
	    return true;
	String currGroup = (String) columnGroups.get(colNo);
        String oldGroup = (String) columnGroups.get(colNo - 1);
        if ((currGroup == null) && (oldGroup == null))
            return false;
	if ((currGroup == null) && (oldGroup != null))
            return true;
	if ((oldGroup == null) && (currGroup != null))
	    return true;
	return (currGroup.compareTo(oldGroup) != 0);
	}

     /**
      * Factorization. Find a category name in the array of
      * item categories and return the index.
      * Returns -1 if passed a null string or if the category
      * is not found.
      */
    protected int findCategory(String testItem)
        {
	int found = -1;
        if (testItem == null)
            return found;
	for (int i = 0; (i < itemCategories.length) && (found < 0); i++)
	    {
            if (itemCategories[i].compareTo(testItem) == 0)
                 found = i;
	    }
        return found;
	}

      /**
       * Translate an AttributeList into a hashtable keyed by
       * XMLTag objects, with values that are XMLTag objects
       * if possible (otherwise, strings). Throws an exception if
       * it is unable to map an attribute to an XMLTag - this means
       * that there is a mispelling or that our XMLTag.java needs to
       * be regenerated.
       * <p>
       * Returns null if the AttributeList is empty.
       */
    protected Hashtable attributesToTags(AttributeList atts)
          throws SAXException
        {
	Hashtable table = null;
	for (int i = 0; i < atts.getLength(); i++)
	     {
	     if (table == null)
	         table = new Hashtable(atts.getLength());
	     String name = atts.getName(i);
	     String value = atts.getValue(i);
	     XMLTag nameTag = XMLTag.lookUp(name);
	     if (nameTag == null)
	         throw new SAXException("No tag found for attribute " + name);
	     if (nameTag.hasTagValue())
	         {
	         XMLTag valueTag = XMLTag.lookUp(value);
	         if (valueTag != null)
                     table.put(nameTag,valueTag);
		 else
	             throw new SAXException("Invalid value (" +
				 value + ") found for attribute " + name);
		 }
	     else
	         table.put(nameTag,value);
	     }
	return table;
	}

      /**
       * Test Driver.
       */
    public static void main(String[] args)
        {
	if (args.length < 1)
	     {
	     System.out.println("USAGE: java CalcResultParser <xmlFile>");
	     System.exit(0);
	     }
        try
	     {
	     BufferedReader fReader = new BufferedReader(
					   new FileReader(args[0]));
             StringBuffer buffer = new StringBuffer(4096);
	     String input = null;
             while ((input = fReader.readLine()) !=  null)
                   buffer.append(input + "\n");
             CalcResultParser parser = new CalcResultParser(
                           buffer.toString(),
			   new I18NTextSource("EN",".\\","%"));
             if ((args.length > 1) &&
                 (args[1].equals("trace")))
                  parser.setTracing(true);
             Reader xmlReader = parser.getXmlReader();
             parser.parse(xmlReader);
	     System.out.println(parser.getParsedContent());
	     }
	catch (Exception e)
	     {
	     e.printStackTrace();
	     }

	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: CalcResultParser.java,v 1.28 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }








