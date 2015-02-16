/**
 * XmlToUiBuilder.java
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 * 
 * Created by Sally Goldin, 1/16/2001
 *
 * $Id: XmlToUiBuilder.java,v 1.16 2007/01/14 11:53:44 goldin Exp $
 * $Log: XmlToUiBuilder.java,v $
 * Revision 1.16  2007/01/14 11:53:44  goldin
 * Allow a choice as to whether a panel returns all tabs or not
 *
 * Revision 1.15  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.14  2007/01/01 13:52:16  goldin
 * Add and integrate new controls for rule creation screen
 *
 * Revision 1.13  2006/12/25 10:48:37  goldin
 * Begin implementation of multi-select file control
 *
 * Revision 1.12  2006/11/30 05:25:47  goldin
 * Modify textsource to handle multiline messages; change constructor to take a possibly null key prefix string
 *
 * Revision 1.11  2005/12/24 12:39:03  goldin
 * Create 'verbose' variant of radio boxes
 *
 * Revision 1.10  2005/02/06 13:57:26  goldin
 * Changes to XML parsing to allow sharing of tables across multiple XML files
 *
 * Revision 1.9  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.8  2002/09/14 21:57:28  goldin
 * Add new bKeepNoncurrent attribute
 *
 * Revision 1.7  2002/08/27 20:04:12  goldin
 * convert filechooser to potentially using multiple file types
 *
 * Revision 1.6  2002/06/28 14:11:02  goldin
 * Provide infrastructure for usermanual help implementation
 *
 * Revision 1.5  2002/05/29 17:54:01  goldin
 * Add support for returning blanks
 *
 * Revision 1.4  2002/04/02 00:13:28  goldin
 * Put in infrastructure for testing for file overwrite warning flag
 *
 * Revision 1.3  2002/02/07 18:45:47  goldin
 * Make it possible to disable a menu item based on version but still include it in the UI
 *
 * Revision 1.2  2002/01/10 18:17:37  goldin
 * Change sizing strategy for variable combo fields
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.38  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.37  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.36  2001/10/22 10:58:19  goldin
 * Provide VERSIONSELECTOR functionality
 *
 * Revision 1.35  2001/09/12 11:42:27  goldin
 * Add Mnemonics to menu file & xml processing
 *
 * Revision 1.34  2001/09/05 15:08:53  goldin
 * Change I18NTextSource constructors
 *
 * Revision 1.33  2001/07/31 17:40:11  goldin
 * Add code to handle open-ended ranges
 *
 * Revision 1.32  2001/07/06 16:52:40  goldin
 * Implement override of enabled in <control> element
 *
 * Revision 1.31  2001/06/13 14:12:17  goldin
 * Add noteline etc to calcparser logic
 *
 * Revision 1.30  2001/06/04 11:11:45  goldin
 * Fix bug causing some combos to be empty
 *
 * Revision 1.29  2001/05/09 15:16:40  goldin
 * Begin implementing signature populaing callbacks for C/EDI
 *
 * Revision 1.28  2001/04/26 12:23:33  goldin
 * Implement bigHelp panels
 *
 * Revision 1.27  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.26  2001/04/18 10:47:39  goldin
 * Remove less-than signs from HTML input
 *
 * Revision 1.25  2001/04/17 19:41:38  goldin
 * Minor changes
 *
 * Revision 1.23  2001/04/12 14:10:31  goldin
 * complete implementation of FontChooser and associated Font control
 *
 * Revision 1.22  2001/04/09 14:44:16  goldin
 * Work on file validation. Not complete
 *
 * Revision 1.21  2001/04/09 11:05:42  goldin
 * Add Logging facility logic
 *
 * Revision 1.20  2001/04/06 18:03:28  goldin
 * Refine HTML lists, pull memory files from textDB
 *
 * Revision 1.19  2001/04/05 13:34:51  goldin
 * Cleanup behavior, fix XML errors
 *
 * Revision 1.18  2001/03/23 17:01:51  goldin
 * Initial implementation of file chooser
 *
 * Revision 1.17  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.16  2001/03/20 18:04:15  goldin
 * Implement tabbed panes, clean up menu help:
 *
 * Revision 1.15  2001/03/20 13:33:02  goldin
 * Disable all fields after OK
 *
 * Revision 1.14  2001/03/20 10:48:08  goldin
 * Checkpoint before changing layout strategy
 *
 * Revision 1.13  2001/03/16 19:23:46  goldin
 * Added fixed length option for DTextField and DFileField; added callbacks to menu items
 *
 * Revision 1.12  2001/03/03 19:56:58  goldin
 * Fine tuning screen layout and appearance
 *
 * Revision 1.11  2001/03/02 19:56:22  goldin
 * Add horizontal label option for DTextFields, add handling of translated help msgs
 *
 * Revision 1.10  2001/02/28 16:24:29  goldin
 * implementing defaults, enhancements to help editor
 *
 * Revision 1.9  2001/02/20 18:39:13  goldin
 * Add callback handling
 *
 * Revision 1.8  2001/02/07 20:41:06  goldin
 * Implemented actual reading of text help file
 *
 * Revision 1.7  2001/01/29 15:19:32  goldin
 * Continued work on UI
 *
 * Revision 1.6  2001/01/29 12:23:28  goldin
 * Put official UI file in CVS, also new class to control resizing
 *
 * Revision 1.5  2001/01/25 20:16:19  goldin
 * Continued work on layout and XML parsing
 *
 * Revision 1.4  2001/01/22 16:14:26  goldin
 * Changes to parse actual generated XML file
 *
 * Revision 1.3  2001/01/19 18:43:19  goldin
 * Add handling of xlateText, menu building
 *
 * Revision 1.2  2001/01/17 14:18:23  goldin
 * Actually build initial trial panel from XML document
 *
 * Revision 1.1  2001/01/16 17:50:30  goldin
 * Began implemenation of XML parsing to create UI
 *
 *
 */

package com.grs.gui;
import java.util.*;
import java.io.*;
import javax.swing.*;  // for test driver only
import java.awt.*;  // for test driver only
import org.xml.sax.*;

//*************************************************************************+
/** 
 * This class reads and parses an XML document describing a DRAGON
 * user interface, and constructs the individual panels associated
 * with that interface. The resulting panels are stored in a hashtable
 * passed to the constructor, where they can be invoked from the 
 * main DRAGON UI.
 *
 * @author  goldin*/

public class XmlToUiBuilder extends HandlerBase 
    {
      /**
       * Package prefix to add to all Validator, Callback and 
       * Initializer class names.
       */
    protected String pkgPrefix = "com.grs.dragon.ui.";

      /**
       * Local package prefix
       */
    protected static final String LOCAL_PKG = "com.grs.gui.";

      /** temp accumulation of fields as they are created 
       */
    protected Hashtable fieldTable = new Hashtable(); 

      /** temp accumulation of intermediate (non-toplevel) panels as 
       *  they are created 
       */
    protected Hashtable panelTable = new Hashtable(); 

      /** temp accumulation of menubuttons and menuspecs as they are created 
       */
    protected Hashtable menuTable = new Hashtable(); 

      /**
       * Result table of panels - initialized by the constructor.
       */
    protected Hashtable masterUITable = null;
      
      /**
       * Keep instantiated validators, so that we don't need to create
       * a new object each time.
       */
    protected Hashtable validatorTable = new Hashtable();

      /**
       * XML file to read.
       */
    protected String xmlFileName;

      /**
       * DTD file name 
       */
    protected String dtdFileName;


      /**
       * Reader that provides primary access to the XML data
       */
    protected InputStreamReader xmlReader = null;


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
       * Keep track of the current panel we are building,
       * the current control, and the current menu item.*/
    protected DragonField currentControl = null;
    protected DragonPanel currentPanel = null;
    protected DragonMenu currentMenu = null;
      /** this one may be a DragonMenuItem or a DCheckMenuItem 
       *  So we set it to be a superclass of both.
       */
    protected JMenuItem currentMenuItem = null;
    protected JMenuBar currentMenuBar = null;

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
       * If true, just test the parsing without doing any
       * object creation.
       */
    protected boolean bParseOnly = false;


      /**
       * String identifying what version we are building.
       * If not "default", we'll omit any menu items that 
       * have an explicit version that does not match.
       */
    protected String versionSelector = null;
    protected final String DEFAULT = "default";
    protected boolean bDefaultVersion = true;  // so we can test once
                                               // and hold on to results


//==================================================================
      /**
       * Constructor - initializes the masterUITable, input file
       * name, dtd file name,text source, and versionSelector,
       * and creates the reader. Also pass home directory, which
       * may be null.
       */
    public XmlToUiBuilder(String xmlFile, String dtdFile, 
			  I18NTextSource source,
			  Hashtable masterTable,
			  String versionSelector,
			  String homeDirectory)
	{
	xmlFileName = xmlFile;
	if (homeDirectory != null)
            xmlFileName = homeDirectory +
	                  File.separator + xmlFileName;
	dtdFileName = dtdFile;
	textSource = source;
	masterUITable = masterTable;
	this.versionSelector = versionSelector.toLowerCase();
        if (versionSelector.compareTo(DEFAULT) != 0)
            bDefaultVersion = false;
	try
	    {
	    FileInputStream stream = new FileInputStream(xmlFileName);
	    xmlReader = new InputStreamReader(stream);
	    }
	catch (FileNotFoundException fnf)
	    {
	    System.out.println("Cannot find XML file: " + xmlFileName);
	    }

	//FileInputStream stream2 = new FileInputStream(dtdFileName);
	//InputStreamReader reader2 = new InputStreamReader(stream2);
	//XMLTestParse.processReader(reader2);
	//System.out.println("Result: \n"+XMLTestParse.getErrorList());
	}

    /**
     * This method makes it possible to share the entities parsed
     * from one XML file with a subsequent XML file.
     * When this method is called, it will set the two 
     * hash tables initialized at the top of this class
     * to point to the tables passed in.
     * @param menuTable  Shared table of menu items
     * @param panelTable Shared table of panels
     */
    public void setSharedTables(Hashtable menuTable, Hashtable panelTable)
        {
	this.menuTable = menuTable;
	this.panelTable = panelTable;
        }  
 
    /**
     * Returns the menu table currently in use.
     */
    public Hashtable getMenuTable()
        {
	return this.menuTable;
        }

    /**
     * Returns the panel table currently in use.
     */
    public Hashtable getPanelTable()
        {
	return this.panelTable;
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
	if (bParseOnly)
	    return;

	Hashtable attributes = attributesToTags(amap);

        if (elementTag == XMLTag.CONTROLSPEC)
	    {
	    processControlSpec(attributes);
	    }
	else if (elementTag == XMLTag.PANELSPEC)
	    {
	    processPanelSpec(attributes);
	    }
	else if (elementTag == XMLTag.CONTROL)
	    {
	    processControl(attributes);
	    }
	else if (elementTag == XMLTag.PANEL)
	    {
	    processPanel(attributes);
            }
	else if (elementTag == XMLTag.MENUBUTTONSPEC)
	    {
	    processMenuButtonSpec(attributes);
            }
	else if (elementTag == XMLTag.MENUSPEC)
	    {
	    processMenuSpec(attributes);
            }
	else if (elementTag == XMLTag.MENUBUTTON)
	    {
	    processMenuButton(attributes);
            }
	else if (elementTag == XMLTag.SEPARATOR)
	    {
	    processSeparator(attributes);
            }
	else if ((elementTag == XMLTag.HELP) ||
		 (elementTag == XMLTag.LABEL) ||
		 (elementTag == XMLTag.TITLE) ||
		 (elementTag == XMLTag.TOOLTIP) ||
		 (elementTag == XMLTag.DEFAULT) ||
		 (elementTag == XMLTag.CHOICES) ||
		 (elementTag == XMLTag.COMMENTS))

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
       * Methods to handle each possible element type.
       */

      /**
       * Create a new DragonField object of the appropriate type,
       * initialize it as much as possible based on the attributes,
       * and assign it to currentControl, so that subelements can
       * add data to it.
       */
    protected void processControlSpec(Hashtable attributes)
           throws SAXException
        {
        if (currentControl != null)
	     throw new SAXException(
	       "Trying to create new field when current is not complete.");
	XMLTag typeTag = (XMLTag) attributes.get(XMLTag.TYPE);
	// above will throw a class cast exception if we have an
	// invalid type value.
	String id = (String) attributes.get(XMLTag.ID);
	XMLTag dataTypeTag = (XMLTag) attributes.get(XMLTag.DATATYPE);
	if (dataTypeTag == null)
	    dataTypeTag = XMLTag.STRING;
	String dataRange = (String) attributes.get(XMLTag.DATARANGE);

	if (typeTag == XMLTag.PUSHBUTTON)
	    {
	    DButtonField btn = new DButtonField(id,"dummyButton");
	    currentControl = btn;
	    }
	else if (typeTag == XMLTag.FIELD)
	    {
	    int displayCols = 0;
	    String width = (String) attributes.get(XMLTag.WIDTH);
	    if (width != null)
	        displayCols = Integer.parseInt(width);
	    boolean bHorizontal = false;
 	    XMLTag displayOpt = (XMLTag) attributes.get(XMLTag.DISPLAYOPTS);
	    if ((displayOpt != null) && (displayOpt == XMLTag.HORIZONTAL))
		bHorizontal = true;
	    if ((dataTypeTag != null) &&
		((dataTypeTag == XMLTag.READFILE) ||
		 (dataTypeTag == XMLTag.WRITEFILE)||
                 (dataTypeTag == XMLTag.PATH)))
	        {
		    DFileField fld = null;
		boolean bMustExist = (dataTypeTag == XMLTag.READFILE)||
		                     (dataTypeTag == XMLTag.PATH);
		boolean bPath = (dataTypeTag == XMLTag.PATH);

 	        XMLTag multiopt = 
                         (XMLTag) attributes.get(XMLTag.BMULTI);
                if (multiopt == null)
                    multiopt = XMLTag.FALSE;
                if (multiopt == XMLTag.TRUE)
		    fld = new DMultiFileField(id,"dummyFile",displayCols,
			                            bMustExist,bPath);
                else
		    fld = new DFileField(id,"dummyFile",displayCols,
			                            bMustExist,bPath);
		currentControl = fld;
		// parse the dataRange into fileType and memory
		// files, and sent them.
		String range = (String) attributes.get(XMLTag.DATARANGE);
		if (range != null)
		    {
		    fld.setAllowedMemoryFiles(
				      parseMemoryFiles(range));
		    StringTokenizer tokenizer = new StringTokenizer(range,",");
		    Vector types = new Vector(tokenizer.countTokens());
		    while (tokenizer.hasMoreTokens())
		         {
			 String filePattern = tokenizer.nextToken();
			 DFileType type = DFileType.getFileType(filePattern);
			 if (type != null)
			     types.add(type);
			 }
		    Object[] contents = types.toArray();
		    DFileType[] fileTypes = new DFileType[contents.length];
		    for (int i = 0; i < contents.length; i++)
		         fileTypes[i] = (DFileType) contents[i];
		    fld.setFileTypes(fileTypes);
		    }
 	        XMLTag overwriteOpt = 
                         (XMLTag) attributes.get(XMLTag.BOVERWRITE);
		if ((overwriteOpt != null) && (overwriteOpt == XMLTag.TRUE))
		    fld.setOverwriteWarning(true);
		}
            else if ((dataTypeTag != null) &&
		     (dataTypeTag == XMLTag.FONT))
	        {
		DFontField fld = new DFontField(id,"dummyText");
		currentControl = fld;
		}
	    else
	        {
		DTextField fld = new DTextField(id,"dummyText",
                                     displayCols,bHorizontal);
		ValueLimits limits = null;
		if (dataRange != null)
		    {
		    if (dataTypeTag == XMLTag.INTEGER)
		        {
			limits = makeIntegerLimits(dataRange);
			}
		    if (dataTypeTag == XMLTag.DOUBLE)
		        {
			limits = makeLimits(dataRange);
			}
		    fld.setValueLimits(limits);
		    }
 	        XMLTag returnBlanksOpt = 
                         (XMLTag) attributes.get(XMLTag.BRETURNBLANKS);
		if ((returnBlanksOpt != null) && 
		    (returnBlanksOpt == XMLTag.TRUE))
		    fld.setReturnBlanks(true);
		currentControl = fld;
		}
	    // check for a maximum field size
	    String maxString = (String)attributes.get(XMLTag.DATAMAXCHARS);
	    if (maxString != null)
	        {
		try 
		     {
		     int maxChars = Integer.parseInt(maxString);
		     ((DTextField) currentControl).setMaxInputChars(maxChars);
		     }
		catch (NumberFormatException nfe)
		     {
		     throw new SAXException("Invalid value " + 
			     maxString + " for maxDataChars attribute; " +
			     "control ID is " + id);
		     }
	        }
	    }
	else if (typeTag == XMLTag.FIXEDCOMBO) 
	    {
	    if (dataRange == null)
	        {
		throw new SAXException(
                  "Control " + id + 
		  ": DataRange specifying choices is required for fixedCombo controls");
		}
	    boolean bHorizontal = false;
 	    XMLTag displayOpt = (XMLTag) attributes.get(XMLTag.DISPLAYOPTS);
	    if ((displayOpt != null) && (displayOpt == XMLTag.HORIZONTAL))
		bHorizontal = true;
	    int numChoices = dataRange.length();
	    String[] choices = new String[numChoices];
	    for (int i = 0; i < numChoices; i++)
	        {
		if (i < numChoices - 1)
 	            choices[i] = dataRange.substring(i,i+1);
		else
		    choices[i] = dataRange.substring(i);
		}
	    DComboField fld = new DComboField(id,"dummyCombo",choices,choices,
					      bHorizontal);
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.VARCOMBO) 
	    {
	    int displayCols = 0;
	    String width = (String) attributes.get(XMLTag.WIDTH);
	    if (width != null)
	        displayCols = Integer.parseInt(width);
	    boolean bHorizontal = false;
 	    XMLTag displayOpt = (XMLTag) attributes.get(XMLTag.DISPLAYOPTS);
	    if ((displayOpt != null) && (displayOpt == XMLTag.HORIZONTAL))
		bHorizontal = true;
	    DComboField fld = new DComboField(id,"dummyCombo",null,null,
					      bHorizontal);
	    if (displayCols > 0)
	        fld.setMaxWidth(displayCols);
            fld.setFixed(false);
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.CHECKBUTTON)
	    {
	    if ((dataRange == null) ||
		(dataRange.length() != 2))
	        {
		  // if no data range is specified assume the choices
		  // are "Y" and "N"
		dataRange = new String("YN");
		}
	    DCheckField fld = new DCheckField(id,"dummyCheck",
					      dataRange.substring(0,1),
					      dataRange.substring(1));
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.FIXEDTEXT)
	    {
	    DFixedText fld = new DFixedText(id,"dummyFixedText");
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.RADIOPANEL)
	    {
	    if (dataRange == null)
	        {
		throw new SAXException(
                  "Control " + id + 
		  ": DataRange specifying choices is required for radioPanel controls");
		}
	    int numChoices = dataRange.length();
	    boolean bHorizontal = true;
	    XMLTag verboseOpt = (XMLTag) attributes.get(XMLTag.BVERBOSE);
            boolean bVerbose = false;
	    int commentWidth = 40;
	    if (verboseOpt != null)
	       {
	       bVerbose = true;
	       String width = (String) attributes.get(XMLTag.COMMENTWIDTH);
	       if (width != null)
	          commentWidth = Integer.parseInt(width);
	       }
 	    XMLTag displayOpt = (XMLTag) attributes.get(XMLTag.DISPLAYOPTS);
	    if ((displayOpt != null) && (displayOpt == XMLTag.VERTICAL))
		bHorizontal = false;
	    if (bVerbose)
	        bHorizontal = false;
	    String[] choices = new String[numChoices];
	    for (int i = 0; i < numChoices; i++)
	        {
		if (i < numChoices - 1)
 	            choices[i] = dataRange.substring(i,i+1);
		else
		    choices[i] = dataRange.substring(i);
		}
	    DRadioBox fld;
            if (bVerbose)
	        {
	        fld = new DRadioBox(id,"dummyRadio",choices,choices,
					choices,commentWidth);
	        }
	    else
	        {
	        fld = new DRadioBox(id,"dummyRadio",choices,choices,
					  bHorizontal);
	        }
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.RANGECONTROL)
	    {
	    int displayCols = 0;
            boolean bInteger = true;
	    String width = (String) attributes.get(XMLTag.WIDTH);
	    if (width != null)
	        displayCols = Integer.parseInt(width);
	    if ((dataTypeTag != null) &&
		(dataTypeTag != XMLTag.INTEGER))
		bInteger = false;
	    DRangeControl fld = new DRangeControl(id,"dummyText",
                                     displayCols,bInteger);
	    ValueLimits limits = null;
	    if (dataRange != null)
		{
		if (dataTypeTag == XMLTag.INTEGER)
		    {
		    limits = makeIntegerLimits(dataRange);
		    }
		if (dataTypeTag == XMLTag.DOUBLE)
		    {
		    limits = makeLimits(dataRange);
		    }
		fld.setValueLimits(limits);
		}
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.LISTBOX)
	    {
	    DListBox fld = new DListBox(id,"dummyText");
	    String addCallbackClassName = 
                 (String) attributes.get(XMLTag.ADDCALLBACK);
	    if (addCallbackClassName != null)
	       {
		Callback acb = instantiateCallback(addCallbackClassName, id);
                if (acb != null)
		    fld.setAddCallback(acb);	    
	        }
	    currentControl = fld;
	    }
	else
	    {
	    throw new SAXException(
                "Unimplemented control type: " + typeTag.toString());
	    }
	// Now set things that are common to all controls
	String pSpecStr = (String) attributes.get(XMLTag.PSPECSTR);
	if (pSpecStr != null)
	    currentControl.setPSpecifier(pSpecStr);
	String valClassName = (String) attributes.get(XMLTag.VALIDATOR);
	if (valClassName != null)
	    {
	    Validator val = instantiateValidator(valClassName, id);
	    currentControl.setValidator(val);	    
	    }
	String callbackClassName = (String) attributes.get(XMLTag.CALLBACK);
	if (callbackClassName != null)
	    {
	    Callback cb = instantiateCallback(callbackClassName, id);
	    currentControl.setCallback(cb);	    
	    }
	String initClassName = (String) attributes.get(XMLTag.INITIALIZER);
	if (initClassName != null)
	    {
	    Initializer init = instantiateInitializer(initClassName, id);
	    currentControl.setInitializer(init);	    
	    }
	String placeOpts = (String)attributes.get(XMLTag.PLACEMENTOPTS);
	if (placeOpts != null)
	    {
	    if (placeOpts.indexOf("centered") >= 0)
	        currentControl.setCentered(true);
	    if (placeOpts.indexOf("bottom") >= 0)
	        currentControl.setBottom(true);
	    if (placeOpts.indexOf("nextline") >= 0)
	        currentControl.setNewLine(true);
	    }
	XMLTag requiredTag = (XMLTag) attributes.get(XMLTag.BREQUIRED);
	if ((requiredTag != null) && (requiredTag == XMLTag.TRUE))
	    currentControl.setRequired(true);
	XMLTag enabledTag = (XMLTag) attributes.get(XMLTag.BENABLED);
	if ((enabledTag != null) && (enabledTag == XMLTag.FALSE))
	    {
	    currentControl.setEnabled(false);
	    currentControl.setDefaultEnabled(false);
	    }

	XMLTag defaultTag = (XMLTag) attributes.get(XMLTag.DEFAULTCATEGORY);
        if ((defaultTag == null) &&
            (typeTag == XMLTag.FIXEDCOMBO))
	    {
            defaultTag = XMLTag.INDEX;
	    }
        if (defaultTag == XMLTag.STRING)
	    {
	    String dflt = (String) attributes.get(XMLTag.DEFAULTSTR);
	    currentControl.setDefaultValue(dflt);
	    }
	else if (defaultTag == XMLTag.INDEX)
	    {
            String indexStr = (String) attributes.get(XMLTag.DEFAULTINDEX);
	    String range = (String) attributes.get(XMLTag.DATARANGE);
	    if (indexStr == null)
	        indexStr = "0";
            if (range == null)
	        throw new SAXException("Incorrectly specified indexed default - missing data range: control ID is " + currentControl.getName());
	    try 
	        {
	        int index = Integer.parseInt(indexStr);
		if ((index >= range.length()) || (index < 0))
		    {
		    throw new SAXException("Incorrectly specified indexed default - index must match range: control ID is " + currentControl.getName());
		    }
		String dflt;
                if (index < range.length()-1)
		    dflt = range.substring(index,index+1);
		else
		    dflt = range.substring(index);
		currentControl.setDefaultValue(dflt);
		}
	    catch (NumberFormatException nfe)
	        {
	        throw new SAXException("Incorrectly specified indexed default - index must be an integer: control ID is " + currentControl.getName());
		}
	    }

	}

//=================================================================
      /**
       * Factorization of processControlSpec. Parses a comma
       * delimited string of memory files and returns them in a
       * a string array.
       */
    protected String[] parseMemoryFiles(String parseString)
        {
	Vector memFiles = new Vector(10);
	StringTokenizer tokenizer = new StringTokenizer(parseString,",");
	while (tokenizer.hasMoreTokens())
	    {
	    String memFile = tokenizer.nextToken();
            if (memFile.startsWith("%"))
	        {
                memFile = textSource.getI18NText(memFile,memFile);
		memFiles.add(memFile);
		}
	    else if (memFile.startsWith("="))
	        {
		memFiles.add(memFile);
		}
	    }
	Object[] contents = memFiles.toArray();
	String[] memStrings = new String[contents.length];
	for (int i = 0; i < contents.length; i++)
	     memStrings[i] = (String) contents[i];
	return memStrings;
	}

//=================================================================
      /**
       * Factorization of processControlSpec, creates and
       * returns a Validator instance. If an instance already
       * exists in the validatorTable hash, it is returned, rather
       * than creating a new object. Since validators do not
       * hold on to any context, a single instance can be used for all
       * fields.
       * @param valClassName Validator class name
       * @param id  ID of control being constructed
       * @return Validator instance, or null
       * @throws SAXException converted from classnotfound
       */
    protected Validator instantiateValidator(String valClassName, String id)
          throws SAXException
        {
	// try doing a lookup first.
	Validator val = (Validator) validatorTable.get(valClassName);
	if (val != null)
	    return val;  
	// otherwise, create a new instance.
	Class valClass = null;
	try 
	    {
	    valClass = Class.forName(pkgPrefix + valClassName);
	    val = (Validator) valClass.newInstance();
	    validatorTable.put(valClassName,val);
	    }  
	    
	catch (ClassNotFoundException cnf)
	    {
	    try  
	        {
		valClass = Class.forName(LOCAL_PKG + valClassName);
		val = (Validator) valClass.newInstance();
		validatorTable.put(valClassName,val);

		}
	    catch (Exception e)
	        {
		throw new SAXException("Control " + id +
				   ": Error instantiating validator");
		}
	    }
	catch (InstantiationException ie)
	    {
	    throw new SAXException("Control " + id +
				   ": Error instantiating validator");
	    }
	catch (IllegalAccessException ia)
	    {
	    throw new SAXException("Control " + id +
				   ": Error instantiating validator");
	    }
	return val;
	}

      /**
       * Factorization of processControlSpec, creates and
       * returns a Callback instance.
       * @param cbClassName Callback class name
       * @param id  ID of control being constructed
       * @return Callback instance, or null
       * @throws SAXException converted from classnotfound
       */
    protected Callback instantiateCallback(String cbClassName, String id)
          throws SAXException
        {
	Callback cb = null;
        Class cbClass = null;
	try 
	    {
	    cbClass = Class.forName(pkgPrefix + cbClassName);
	    cb = (Callback) cbClass.newInstance();
	    }  
	catch (ClassNotFoundException cnf)
	    {
	    try   
	        {
		cbClass = Class.forName(LOCAL_PKG + cbClassName);
		cb = (Callback) cbClass.newInstance();
		}
	    catch (Exception e)
	        {
		throw new SAXException("Control " + id +
				   ": Unknown callback specified");
		}
	    }
	catch (InstantiationException ie)
	    {
	    throw new SAXException("Control " + id +
	    		   ": Error instantiating callback");
	    }
	catch (IllegalAccessException ia)
	    {
	    throw new SAXException("Control " + id +
			   ": Error instantiating callback");
	    }
	return cb;
	}

      /**
       * Factorization of processControlSpec, creates and
       * returns an Initializer instance.
       * @param initClassName Initializer class name
       * @param id  ID of control being constructed
       * @return Initializer instance, or null
       * @throws SAXException converted from classnotfound
       */
    protected Initializer instantiateInitializer(String initClassName, 
						 String id)
          throws SAXException
        {
	Initializer init = null;
	Class initClass = null;
	try 
	    {
	    initClass = Class.forName(pkgPrefix + initClassName);
	    init = (Initializer) initClass.newInstance();
	    }  
	catch (ClassNotFoundException cnf)
	    {
	    try   // try without the prefix - for generic initializers
	        {
		initClass = Class.forName(LOCAL_PKG + initClassName);
		init = (Initializer) initClass.newInstance();
		}
	    catch (Exception e)
	        {
		throw new SAXException("Control " + id +
	      		   ": Unknown initializer specified");
		}
	    }
	catch (InstantiationException ie)
	    {
	    throw new SAXException("Control " + id +
	     			   ": Error instantiating initializer");
	    }
	catch (IllegalAccessException ia)
	    {
	    throw new SAXException("Control " + id +
	      		   ": Error instantiating initializer");
	    }
	return init;
	}

      /**
       * Factorization of processControlSpec. Creates a ValueLimits
       * object, if possible, from a data range. Assumes double values.
       * @param rangeString String with data range
       * @return ValueLimits object created or null if range is empty.
       * @throws SAXException if range is incorrectly specified.
       */
    protected ValueLimits makeLimits(String rangeString)
           throws SAXException
        {
	ValueLimits vl = null;
	try
	   {
	   if (rangeString.length() > 0)
	       {
	       int pos = rangeString.indexOf("-");
	       if (pos > 0)
		   {
                   double min;
		   double max;
		   String minString = rangeString.substring(0,pos);
		   String maxString = rangeString.substring(pos+1);
                   if (minString.length() > 0)
		       min = Double.parseDouble(minString);
		   else
		       min = Double.MIN_VALUE;
                   if (maxString.length() > 0)
		       max = Double.parseDouble(maxString);
                   else 
                       max = Double.MAX_VALUE;
		   vl = new ValueLimits(min,max,false);
		   }
	       }
	   }
	catch (NumberFormatException nfe)
	   {
	   throw new SAXException("Improperly formatted numeric data range: " +
				  rangeString);
	   }
	return vl;
	}

      /**
       * Create a ValueLimits object from the range string specification,
       * with the integer flag set to true.
       * @param rangeString String with data range
       * @return ValueLimits object created or null if range is empty.
       * @throws SAXException if range is incorrectly specified.
       */
    protected ValueLimits makeIntegerLimits(String rangeString)
           throws SAXException
        {
	ValueLimits vl = makeLimits(rangeString);
	if (vl != null)
	    vl.bInteger = true;
	return vl;
	}
//==================================================================
      /**
       * Create a new DragonPanel object of the appropriate type,
       * initialize it as much as possible based on the attributes,
       * and assign it to currentPanel, so that subelements can
       * add data to it.
       */
    protected void processPanelSpec(Hashtable attributes)
           throws SAXException
        {
        if (currentPanel != null)
	     throw new SAXException(
	       "Trying to create new panel when current is not complete.");
        boolean bReturnAll = true;
	XMLTag typeTag =  (XMLTag) attributes.get(XMLTag.TYPE);
	// above will throw a class cast exception if we have an
	// invalid type value.
	String id = (String) attributes.get(XMLTag.ID);
        String retString = (String) attributes.get(XMLTag.RETURNALL);
        if ((retString != null) && (retString.compareTo("false") == 0))
            bReturnAll = false;
	DragonPanel newPanel = new DragonPanel(id);
        newPanel.setReturnAllTabs(bReturnAll);
	if (typeTag == XMLTag.TOPLEVEL)
	    newPanel.setPrimary(true);
	else 
	    newPanel.setPrimary(false);
	if (typeTag == XMLTag.TABPANEL)
	    newPanel.setTabbed(true);
	if (typeTag == XMLTag.TABGROUP)
	    newPanel.setTabGroup(true);
	if (typeTag == XMLTag.POPUP)
	    newPanel.setPopup(true);
	XMLTag styleTag = (XMLTag) attributes.get(XMLTag.LAYOUTSTYLE);
	if ((styleTag != null) && (styleTag == XMLTag.HORIZONTAL))
	    newPanel.setFlowRow(true);
	String placeOpts = (String)attributes.get(XMLTag.PLACEMENTOPTS);
	if (placeOpts != null)
	    {
	    if (placeOpts.indexOf("bottom") >= 0)
	        newPanel.setBottom(true);
	    }
	XMLTag displayOpt = (XMLTag) attributes.get(XMLTag.DISPLAYOPTS);
	if ((displayOpt != null) && (displayOpt == XMLTag.BORDER))
	    newPanel.setBorderOn();

	XMLTag bigHelpTag = (XMLTag) attributes.get(XMLTag.BIGHELP);
	if (bigHelpTag == XMLTag.TRUE)
            newPanel.setBigHelp(true);

	String cmd = (String) attributes.get(XMLTag.COMMAND);
	newPanel.setPanelCommand(cmd);
	String details = (String) attributes.get(XMLTag.DETAILSLINK);
	if (details == null)
	    newPanel.setDetailsLink(cmd);
	else
	    newPanel.setDetailsLink(details);

	String columnStr = (String) attributes.get(XMLTag.COLUMNS);
	if (columnStr != null)
	    {
            try 
	        {
	        newPanel.setColumnCount(Integer.parseInt(columnStr));
		}
	    catch (NumberFormatException nf)
	        {
                throw new SAXException("Invalid column count for panel " +
				        id);
		}
	    }
	currentPanel = newPanel;
	}

//==================================================================
      /**
       * Handles a reference to a control within a panelSpec element.
       * Makes a clone of the control and adds it to the panel.
       * If the control cannot be found, this is an error.
       */
    protected void processControl(Hashtable attributes)
           throws SAXException
        {
	String id = (String) attributes.get(XMLTag.ID);
        if (currentPanel == null)
	     {
	     throw new SAXException(
	       "Control element (" + id + 
                 ") found outside a PanelSpec element");
	     }
	DragonField fld = (DragonField) fieldTable.get(id);
	if (fld == null)
	     {
	     throw new SAXException(
	       "Control element (" + id + 
                 ") not found; probably not created yet");
	     }
	try
	     {
             DragonField clone = fld.makeClone();
             XMLTag enabledTag = (XMLTag) attributes.get(XMLTag.BENABLED);
	     if ((enabledTag != null) && (enabledTag == XMLTag.FALSE))
	         {
                 clone.setEnabled(false);
                 clone.setDefaultEnabled(false);
                 }
	     currentPanel.addField(clone);
	     }
	catch (Exception e)
	     {
	     throw new SAXException(e.getMessage());
	     }
	// also need to process the placementOpts - skip for now.
	}


//==================================================================
      /**
       * Handles a reference to a panel within another panelSpec element.
       * Makes a clone of the referenced panel and adds it to the panel
       * being built.
       * If the referenced panel cannot be found or it is
       * a primary panel, this is an error.
       */
    protected void processPanel(Hashtable attributes)
           throws SAXException
        {
	String id = (String) attributes.get(XMLTag.ID);
        if (currentPanel == null)
	     {
	     throw new SAXException(
	       "SubPanel element (" + id + 
                 ") found outside a PanelSpec element");
	     }
	DragonPanel panel = (DragonPanel) panelTable.get(id);
	if (panel == null)
	     {
	     throw new SAXException(
	       "SubPanel element (" + id + 
                 ") not found; probably not created yet");
	     }

	try
	     {
	     DragonPanel clone = panel.makeClone();
	     clone.doPanelLayout();
	     currentPanel.addPanel(clone);
	     }
	catch (Exception e)
	     {
	     throw new SAXException(e.getMessage());
	     }
	}

//==================================================================
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
	}


//==================================================================
      /**
       * Handles creation of a new menuButton, which may actually
       * be a reference to an existing submenu.
       */
    protected void processMenuButtonSpec(Hashtable attributes)
           throws SAXException
        {
	boolean bEnabled = true;
        String mnemonic = (String) attributes.get(XMLTag.PREFMNEMONIC);
	String id = (String) attributes.get(XMLTag.ID);
	XMLTag typeTag = (XMLTag) attributes.get(XMLTag.TYPE);
	XMLTag enabledTag = (XMLTag) attributes.get(XMLTag.BENABLED);
	if (enabledTag == XMLTag.FALSE)
	    bEnabled = false;
	XMLTag keepNonCurrentTag = 
               (XMLTag) attributes.get(XMLTag.BKEEPNONCURRENT);
        if (!isCurrentVersion(attributes))
	    {
	    if ((keepNonCurrentTag == null) || 
                (keepNonCurrentTag == XMLTag.FALSE))
	        {
                return;
		}
	    else
	        {
		bEnabled = false;
		}
	    }
	if (typeTag == XMLTag.SUBMENU)
	    {
	    String attachID = (String) attributes.get(XMLTag.ATTACHID);
	    if (attachID == null)
	        throw new SAXException("Found submenu (" + id +
				       ") with no attachID specified");
	       
	    DragonMenu menu = (DragonMenu) menuTable.get(attachID);
	    if (menu == null)
	         throw new SAXException("Reference to undefined menuSpec " +
                  attachID + " in menuButtonSpec " + id);
            if (mnemonic != null)
	        {
		char[] c = mnemonic.toCharArray();
                menu.setMnemonic(c[0]);
		}
	    if (!bEnabled)
	        {
	        menu.setEnabled(false);
		}
	    currentMenu = menu; // so that text will be assigned to
	                            // the submenu
	    // store the submenu under the menuButton's ID for later retrieval
	    menuTable.put(id,menu);
	    }
        else if (typeTag == XMLTag.EXECUTE)
	    {
	    DMenuItem item = new DMenuItem(id);
	    String command = (String) attributes.get(XMLTag.COMMAND);
	    if (command != null)
	        {
		// change forward slashes to spaces  
                item.setCommandString(command.replace('/',' '));
		}
	    String attachID = (String) attributes.get(XMLTag.ATTACHID);
	    if (attachID != null)
	        item.setInvokedPanelId(attachID);
            if (mnemonic != null)
	        {
		char[] c = mnemonic.toCharArray();
                item.setMnemonic(c[0]);
		}
	    if (!bEnabled)
	        {
	        item.setEnabled(false);
		}
	    XMLTag contextTag = (XMLTag) attributes.get(XMLTag.BKEEPCONTEXT);
	    if ((contextTag != null) && (contextTag == XMLTag.TRUE))
	        {
		item.setKeepContext(true);
		}
	    currentMenuItem = item;
	    menuTable.put(id,item);
	    }
        else if (typeTag == XMLTag.CHECK)
	    {
	    DCheckMenuItem item = new DCheckMenuItem(id);
	    String command = (String) attributes.get(XMLTag.COMMAND);
	    if (command != null)
                item.setCommandString(command);
            if (mnemonic != null)
	        {
		char[] c = mnemonic.toCharArray();
                item.setMnemonic(c[0]);
		}
	    currentMenuItem = item;
	    menuTable.put(id,item);
	    }
	String callbackClassName = (String) attributes.get(XMLTag.CALLBACK);
	if (callbackClassName != null)
	    {
	    Callback cb = instantiateCallback(callbackClassName, id);
            if (currentMenuItem instanceof DragonMenuItem)
	        ((DragonMenuItem) currentMenuItem).setCallback(cb);	    
	    }
	}
//==================================================================
      /**
       * Handles creation of a new menuButton, which may actually
       * be a reference to an existing submenu.
       */
    protected void processMenuSpec(Hashtable attributes)
           throws SAXException
        {
	String id = (String) attributes.get(XMLTag.ID);
	XMLTag typeTag = (XMLTag) attributes.get(XMLTag.TYPE);
        if (!isCurrentVersion(attributes))
	    {
	    return;
	    }
	if (typeTag == XMLTag.DROPDOWN)
	    {
	    DragonMenu menu = new DragonMenu(id);
	    currentMenu = menu; 
	    menuTable.put(id,menu);
	    }
        else if (typeTag == XMLTag.MENUBAR)
	    {
	    JMenuBar bar = new JMenuBar();
	    currentMenu = null;
	    currentMenuBar = bar;
	    masterUITable.put(id,bar);
	    }
	}

//==================================================================
      /**
       * Handles addition of an existing menu button to a menu
       * being built.
       */
    protected void processMenuButton(Hashtable attributes)
           throws SAXException
        {
	boolean bEnabled = true;
	XMLTag enabledTag = (XMLTag) attributes.get(XMLTag.BENABLED);
	if (enabledTag == XMLTag.FALSE)
	    bEnabled = false;
	XMLTag keepNonCurrentTag = 
               (XMLTag) attributes.get(XMLTag.BKEEPNONCURRENT);
        if (!isCurrentVersion(attributes))
	    {
	    if ((keepNonCurrentTag == null) || 
                (keepNonCurrentTag == XMLTag.FALSE))
	        {
                return;
		}
	    else
	        {
		bEnabled = false;
		}
	    }
	String id = (String) attributes.get(XMLTag.ID);
	JMenuItem item = (JMenuItem) menuTable.get(id);
	item.setEnabled(bEnabled);
	String parentName;
	if (currentMenu != null)
	     parentName = currentMenu.getName();
	else
	     parentName = "main menubar";
	if (item == null)
	    throw new SAXException("Reference to undefined menuButton " +
				   id + " in menuSpec for " +
				   parentName);
	if (currentMenu != null)
	    currentMenu.add(item);
	else if (currentMenuBar != null)
	    currentMenuBar.add((JMenu) item);
	else
            throw new SAXException("Encountered menuButton element outside of a menuSpec definition");
	}

//==================================================================
      /**
       * Handles addition of a separator to a menu
       * being built.
       */
    protected void processSeparator(Hashtable attributes)
           throws SAXException
        {
	if (currentMenu != null)
	    currentMenu.addSeparator();
	else if (currentMenuBar != null)
	    throw new SAXException("Cannot add separators to the main menu bar");
	else
            throw new SAXException("Encountered separator element outside of a menuSpec definition");
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

	if (bParseOnly)
	    return;

	// store the current item in the appropriate temp table and
	// then null it out.
	if (elementTag == XMLTag.CONTROLSPEC)
	    {
	    DragonField existingField = (DragonField)
               fieldTable.get(currentControl.getName());
	    if (existingField == null)
	        {
		fieldTable.put(currentControl.getName(), currentControl);
		}
	    else
	        {
		System.out.println("*************************************");
		System.out.println("Found duplicate field of class " +
				   currentControl.getClass().getName() +
				   " with ID " + currentControl.getName());
		System.out.println("Original control is of class " +
				   existingField.getClass().getName());
		if (existingField.equivalent(currentControl))
		    System.out.println("The two controls are equivalent");
		else 
	      	    System.out.println("The two controls are NOT equivalent");
		System.out.println("*************************************");
		}
	    currentControl = null;
	    }
	else if (elementTag == XMLTag.PANELSPEC)
	    {
	    if (currentPanel.isPrimary())

	        {
		  // Don't layout the toplevel panels until
		  // we put them in their container.
		  //currentPanel.doPanelLayout();
		masterUITable.put(currentPanel.getName(),currentPanel);
		}
	    else if (currentPanel.isPopup())
	        {
		  // lay it out, b/c it will be displayed in a frame.
		currentPanel.doPanelLayout();
		masterUITable.put(currentPanel.getName(),currentPanel);
		}
	    else
	        {
		panelTable.put(currentPanel.getName(),currentPanel);
		}
	    currentPanel = null;
	    }
	else if ((elementTag == XMLTag.HELP) ||
		 (elementTag == XMLTag.LABEL) ||
		 (elementTag == XMLTag.TITLE) ||
		 (elementTag == XMLTag.TOOLTIP) ||
		 (elementTag == XMLTag.DEFAULT) ||
		 (elementTag == XMLTag.CHOICES) ||
		 (elementTag == XMLTag.COMMENTS))
	    {
	    processTextElement(elementTag);
	    }
	else if (elementTag == XMLTag.MENUSPEC)
	    {
	    currentMenu = null;
	    currentMenuBar = null;
	    }
	else if (elementTag == XMLTag.MENUBUTTONSPEC)
	    {
	    currentMenuItem = null;
	    }
	else if (elementTag == XMLTag.UI)
	    {
	      // end of the document, so we can throw away the
	      // two temporary hash tables.
	    fieldTable.clear();
	    fieldTable = null;
	    panelTable.clear();
	    panelTable = null;
	    }
	
	}
      
      /**
       * Factorization of endElement, processes text accumulated
       * within help, choices, default, tooltip or label elements.
       */
    protected void processTextElement(XMLTag elementTag)
           throws SAXException
        {
	if (elementTag == XMLTag.LABEL)
	    {
	      // one line, no formatting, applies to either
	      // control or menu item.
	    if (currentControl != null)
	        {
		String label = (String) xlatedText.get(0);
		currentControl.setLabelText(label);
		String labelKey = (String) textKey.get(0);
		currentControl.setLabelKey(labelKey);
		}
	    else if (currentMenuItem != null)
	        {
		String label = (String) xlatedText.get(0);
		currentMenuItem.setText(label);
		}
	    else if (currentMenu != null)
	        {
		String label = (String) xlatedText.get(0);
		currentMenu.setText(label);
		}
	    }
	else if (elementTag == XMLTag.TITLE)
	    {
	      // titles apply only to panels
	    if (currentPanel != null)
	        {
		String title = (String) xlatedText.get(0);
		currentPanel.setTitle(title);
		}  
	    }
	else if (elementTag == XMLTag.HELP)
	    {
	      // Need to concatenate all strings and format
	      // as HTML
	    StringBuffer helpString = new StringBuffer();
	    helpString.append("<HTML><HEAD></HEAD><BODY><FONT SIZE=-1>\n");
	    String[] keys = new String[textKey.size()];
            boolean bInList = false;
	    for (int i = 0; i < xlatedText.size(); i++)
	        {
		String temp = replaceAngleBrackets((String) xlatedText.get(i));
		XMLTag tTag = (XMLTag) textTag.get(i);
		if (tTag == XMLTag.PARAGRAPH)
		    {
                    if (bInList)
		        {
		        helpString.append("</dl>\n");  
                        bInList = false;
			}
		    if (i == 0)
		        {
			  //~~		helpString.append("<P>");
			}
		    else
		        {
		        helpString.append("<p>");
			}
                    helpString.append(temp);
		    }
		else if (tTag == XMLTag.LISTITEM)
		    {
                    if (!bInList)
		        {
		        helpString.append("<dl>\n");
			bInList = true;
			}
		    if (i > 0)
		        helpString.append("\n");
		    helpString.append("<dd>" + temp + "</dd>\n");
		    }
		else
		    {
		    helpString.append(temp);
		    }
		keys[i] = (String) textKey.get(i);
		}
            if (bInList)
	        {
                helpString.append("</dl>\n");
		}
	    helpString.append("</p></FONT></BODY></HTML>\n");
	    // could apply to either a control or a menu item.
	    if (currentControl != null)
	        {
		currentControl.setHelpString(helpString.toString());
		currentControl.setHelpKeys(keys);
		}
	    else if (currentMenuItem != null)
	        {
		if (currentMenuItem instanceof DragonMenuItem)
		    {
		    DragonMenuItem item = (DragonMenuItem) currentMenuItem; 
		    item.setHelpString(helpString.toString());
		    item.setHelpKeys(keys);
		    }
		else if (currentMenuItem instanceof DCheckMenuItem)
		    {
		    DCheckMenuItem item = (DCheckMenuItem) currentMenuItem; 
		    item.setHelpString(helpString.toString());
		    item.setHelpKeys(keys);
		    }

		}
	    else if (currentMenu != null)
	        {
		currentMenu.setHelpString(helpString.toString());
		currentMenu.setHelpKeys(keys);
		}
	    }
	else if (elementTag == XMLTag.CHOICES)
	    {
	    // only relevant if the current control is a combo, radio,
	    // or checkbutton
	    if (currentControl.isChoiceControl())
	        {
		String[] keys = new String[textKey.size()];
		String[] choices = new String[xlatedText.size()];
		for (int i = 0; i < xlatedText.size(); i++)
		    {
		    choices[i] = (String) xlatedText.get(i);
		    keys[i] = (String) textKey.get(i);
		    }
		currentControl.setChoiceStrings(choices);
		currentControl.setChoiceKeys(keys);
		}
	    }
	else if (elementTag == XMLTag.COMMENTS)
	    {
	    // only relevant if the current control is a radiobox,
	    if (currentControl instanceof DRadioBox)
	        {
		DRadioBox box = (DRadioBox) currentControl;
		String[] comments = new String[xlatedText.size()];
		for (int i = 0; i < xlatedText.size(); i++)
		    {
		    comments[i] = (String) xlatedText.get(i);
		    }
		box.setChoiceComments(comments);
		}
	    }
	else if (elementTag == XMLTag.TOOLTIP)
	    {
	    // only relevant to menu items
	    if (currentMenuItem != null)
	        {
		String text = (String) xlatedText.get(0);
		currentMenuItem.setToolTipText(text);
		}
	    }
	else if (elementTag == XMLTag.DEFAULT)
	    {
            if (currentControl != null)
	        {
		String text = (String) xlatedText.get(0);
		currentControl.setDefaultValue(text);
		String key = (String)textKey.get(0);
		currentControl.setDefaultKey(key);
	        }
	    }
	// get rid of text and tags - we are done with them
	xlatedText.clear();
	xlatedText = null;
	textTag.clear();
	textTag = null;
	}


//*********************************************************************
      /**
       * Access Methods
       */
    public InputStreamReader getXmlReader()
        {
	return xmlReader;
	}

    public void setParseOnly(boolean flag)
        {
	bParseOnly = flag;
	}
      
    public void setTracing(boolean flag)
        {
	bTracing = flag;
	}
      
    public boolean getTracing()
        {
	return bTracing;
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
       * Replace angle brackets with HTML special character
       * indicators.
       */
    protected String replaceAngleBrackets(String inString)
        {
	StringBuffer outString = new StringBuffer(inString.length());
	int p1 = 0; 
	int p2 = 0;
	p1 = inString.indexOf("<");
	while (p1 >= 0)
	    {
            outString.append(inString.substring(p2,p1));
	    outString.append("&lt;");
	    p2 = p1 + 1;
      	    p1 = inString.indexOf("<",p2);
	    }
        if (p2 < inString.length())
            outString.append(inString.substring(p2));
	return outString.toString();
	}

      /**
       * Factorization: check if this item has a VERSIONSELECTOR,
       * and if so, does it match the current version being
       * build. If the current version is the default version
       * this method will return true regardless.
       */
    protected boolean isCurrentVersion(Hashtable attributes)
        {
        boolean bCurrentVersion = true;
        if (!bDefaultVersion)   // check the version attribute if any
	    {
	    String menuVersion = (String) attributes.get(XMLTag.VERSIONSELECTOR);
            // if there is a version selector on this menu item, 
            // and there's a non-default version specified,
	    // and this menu's version selector does not include the
            // string for the version we are building, just ignore
            if ((menuVersion != null) && 
		(menuVersion.indexOf(versionSelector) < 0))
                 bCurrentVersion = false;
	    }
	return bCurrentVersion;
	}

      /**
       * Set the package prefix to something other than the UI.
       */
    public void setPkgPrefix(String newPrefix)
        {
	pkgPrefix = newPrefix;
	}
       

//*********************************************************************
      // test program - invoke as RMWParser filename
    static public void main(String[] argv)
        {
	boolean bFirstAdded = false;
	Hashtable master = new Hashtable();
	I18NTextSource source = new I18NTextSource("EN",".\\","%");
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
   	    {
	    System.out.println("Error setting look and feel");
	    }

	if (argv.length < 1)
	    {
	    System.out.println(
      "Usage: XmlToUiBuilder <xmlfilename> [trace] [parseonly]");
	    System.exit(0);
	    }
	
	try 
	    {
	    XmlToUiBuilder parser = new XmlToUiBuilder(argv[0],null,
						       source, master,
						       "default",
						       null);
	    if ((argv.length > 1) && (argv[1].compareTo("trace") == 0))
		parser.setTracing(true);

	    if ((argv.length > 2) && (argv[2].compareTo("parseonly") == 0))
		parser.setParseOnly(true);

            InputStreamReader reader = parser.getXmlReader();
	    if (reader != null)
	        {
	        parser.parse(parser.getXmlReader());
		System.out.println("master hash table has " +
			       	   master.size() + " elements");

		}
	    }
	catch (Exception e)
	    {
	    e.printStackTrace();
	    }
	if (master.size() == 0)
	    {
	    System.exit(0);
	    }
	JFrame frame = new JFrame("XmlToUiBuilder Test"); 
        Collection panels = master.values();
	Iterator it = panels.iterator();
	while (it.hasNext())
	    {
	    Object obj = it.next();
	    if (obj instanceof DragonPanel)
	        {
		if (!bFirstAdded)
		   {
		   // we know that there is at least one
		   DragonPanel dPanel = (DragonPanel) obj;
		   Dimension dim = dPanel.getSize();
		   frame.setSize(dim);
		   frame.getContentPane().setLayout(new BorderLayout());
		   frame.getContentPane().add(dPanel,BorderLayout.CENTER);
		   bFirstAdded = true;
		   }
		}
	    else if (obj instanceof JMenuBar)
	        {
		JMenuBar bar = (JMenuBar) obj;
		frame.setJMenuBar(bar);
		}
	    }
	frame.show();
	}
    

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: XmlToUiBuilder.java,v 1.16 2007/01/14 11:53:44 goldin Exp $ \n";
	}
    }







