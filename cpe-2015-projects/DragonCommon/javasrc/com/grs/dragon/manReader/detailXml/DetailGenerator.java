/**
 * DetailGenerator.java
 *
 * ~~ Copyright 2002-2015 by Goldin-Rudahl Associates
 * ~~ EndC
 *
 * Created by Sally Goldin, 6/25/2002
 *
 * $Id: DetailGenerator.java,v 1.9 2015/01/01 08:37:11 rudahl Exp $
 * $Log: DetailGenerator.java,v $
 * Revision 1.9  2015/01/01 08:37:11  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.8  2007/09/01 07:30:56  goldin
 * Add TableControl
 *
 * Revision 1.7  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.6  2007/01/05 04:14:24  goldin
 * Add new control types
 *
 * Revision 1.5  2006/12/09 06:12:15  goldin
 * Update text source constructor in the main function
 *
 * Revision 1.4  2006/03/03 12:03:29  goldin
 * Require the language file directory on the command line
 *
 * Revision 1.3  2003/03/02 23:24:22  rudahl
 * added explicit setting of ApplicationManager, to fix apparent bug
 *
 * Revision 1.2  2002/06/27 18:23:27  goldin
 * Enhance detail file structure
 *
 * Revision 1.1  2002/06/26 19:23:54  goldin
 * Initial implementation of classes to generate Dragon details HTML file for ManReader
 *
 *
 */

package com.grs.dragon.manReader.detailXml;
import com.grs.gui.*;
import java.util.*;
import java.io.*;
import javax.xml.transform.sax.*;
import javax.xml.parsers.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

//*************************************************************************+
/** 
 * This class reads and parses an XML document describing a DRAGON
 * user interface (PANEL.XML), and generates an HTML document with
 * details about each Dragon operation.
 * <p>
 * This class uses the SAX2 Api and is intended to be compiled
 * under Java 1.4, which provides an implementation and plug-ins
 * for that interface.
 *
 * @author  goldin
 */

public class DetailGenerator extends DefaultHandler
    {
      /** temp accumulation of field info objects as they are created 
       */
    protected Hashtable<String,FieldInfo> fieldTable = 
       new Hashtable<String,FieldInfo>(); 

      /** temp accumulation of panel info objects  as 
       *  they are created 
       */
    protected Hashtable<String,PanelInfo> panelTable = 
       new Hashtable<String,PanelInfo>(); 


      /**
       * XML file to read.
       */
    protected String xmlFileName;

      /**
       * DTD file name 
       */
    protected String dtdFileName;
      
      /* Class that provides access to internationalized text.*/
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
    protected FieldInfo currentControl = null;
    protected PanelInfo currentPanel = null;

      /**
       * Vector to hold accumulated strings during a
       * help, label, default, tooltip or choices element.
       */
    protected Vector<String> xlatedText = null;

      /**
       * Tags corresponding to each element in xlatedText.
       * Needed for formatting after all the elements have
       * been found and translations retrieved.
       */
    protected Vector<XMLTag> textTag = null;

      /**
       * Keys corresponding to each element in xlatedText.
       * Used for debugging.
       */
    protected Vector<String> textKey = null;

      /** 
       * If true, just test the parsing without doing any
       * object creation.
       */
    protected boolean bParseOnly = false;

      /**
       * Source of XML data
       */
    protected InputSource xmlSource = null;

      /**
       * Object that actually parses the
       * XML and calls the callbacks.
       */
    protected XMLReader xmlReader = null;

//==================================================================
      /**
       * Constructor - intializes input file
       * name, dtd file name,text source
       * and creates the InputSource. Also pass home directory, which
       * may be null.
       */
    public DetailGenerator(String xmlFile, String dtdFile, 
			  I18NTextSource source,
			  String homeDirectory)
	{
	xmlFileName = xmlFile;
	if (homeDirectory != null)
            xmlFileName = homeDirectory +
	                  File.separator + xmlFileName;
	dtdFileName = dtdFile;
	textSource = source;
	ApplicationManager.setTextSource(textSource);
	try
	    {
	    FileInputStream stream = new FileInputStream(xmlFileName);
	    xmlSource = new InputSource(new InputStreamReader(stream));
	    }
	catch (FileNotFoundException fnf)
	    {
	    System.out.println("Cannot find XML file: " + xmlFileName);
	    }

	}


      /** 
       *  Parse the specified XML, creating the appropriate 
       *  UI data structures as described in the XML.
       */
    public void parse()
           throws ClassNotFoundException, IllegalAccessException,
	     InstantiationException, IOException, SAXException,
	     ParserConfigurationException
        {
	SAXParser saxParser = SAXParserFactory.newInstance().newSAXParser();
	xmlReader = saxParser.getXMLReader();
	xmlReader.setContentHandler(this);
	xmlReader.setEntityResolver(this);
	xmlReader.setErrorHandler(this);
	xmlReader.setDTDHandler(this);
	xmlReader.parse(xmlSource);
	}


//==================================================================
      /** display the contents of the attribute list.
       */
    public void dumpAttributeList(Attributes atts)
        {
	if (atts.getLength() == 0)
	    System.out.println(nestString + " (no attributes) ");
	else
	    {
	    System.out.println(nestString + " AttributeList: ");
	    for (int i = 0; i < atts.getLength(); i++)
		{
		String name = atts.getQName(i);
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
    public void startElement(String namespaceURI, String name, 
			     String qName, Attributes amap) 
           throws SAXException
        {
  	if (bTracing)
	    {
	    nestLevel++;
	    nestString = getLevelString();
	    System.out.println(nestString + 
	       "startElement starting: element name=" + name + " qname=" +
			       qName);
	    dumpAttributeList(amap);
	    }
	XMLTag elementTag = XMLTag.lookUp(qName);
	if (elementTag == null)
	     throw new SAXException("No tag found for element " + name);

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
	else if ((elementTag == XMLTag.HELP) ||
		 (elementTag == XMLTag.LABEL) ||
		 (elementTag == XMLTag.TITLE) ||
		 (elementTag == XMLTag.TOOLTIP) ||
		 (elementTag == XMLTag.DEFAULT) ||
		 (elementTag == XMLTag.CHOICES))

	    {
	    // we will be expecting xlateText elements, which
	    // we will accumulate until we get to the endelement.
	    // Allocate a place to put them.
	    xlatedText = new Vector<String>();
	    textTag = new Vector<XMLTag>();
	    textKey = new Vector<String>();
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
       * Create a new FieldInfo object of the appropriate type,
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
        FieldInfo fld = new FieldInfo(id);
        if ((typeTag == XMLTag.FIXEDTEXT) || 
            (typeTag == XMLTag.PUSHBUTTON))
	    {
	    fld.setDummyControl(true);
	    }
	else if (typeTag == XMLTag.FIELD)
	    {
	    fld.setTextControl(true);
	    if ((dataTypeTag != null) &&
		((dataTypeTag == XMLTag.READFILE) ||
		 (dataTypeTag == XMLTag.WRITEFILE)||
                 (dataTypeTag == XMLTag.PATH)))
	        {
		fld.setFileField(true);
		boolean bMustExist = (dataTypeTag == XMLTag.READFILE)||
		                     (dataTypeTag == XMLTag.PATH);
		fld.setExisting(bMustExist);
		String range = (String) attributes.get(XMLTag.DATARANGE);
		if (range != null)
		    {
		    String filePattern;
		    int pos = range.indexOf(",");
		    if (pos >= 0)
		         {
			 filePattern = range.substring(0,pos);
			 String memoryFiles = range.substring(pos+1);
			 fld.setAllowedMemoryFiles(
				      parseMemoryFiles(memoryFiles));
			 }
		    else
		         {
			 filePattern = range;
			 }
		    DFileType type = DFileType.getFileType(filePattern);
		    if (type != null)
		         fld.setFileType(type);
		    }
		}
	    else
	        {
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
	    int numChoices = dataRange.length();
	    String[] choices = new String[numChoices];
	    for (int i = 0; i < numChoices; i++)
	        {
		if (i < numChoices - 1)
 	            choices[i] = dataRange.substring(i,i+1);
		else
		    choices[i] = dataRange.substring(i);
		}
            fld.setChoiceControl(true);
	    fld.setChoicesFixed(true);
	    }
	else if (typeTag == XMLTag.VARCOMBO) 
	    {
            fld.setChoiceControl(true);
	    fld.setChoicesFixed(false);
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
	    int numChoices = dataRange.length();
	    String[] choices = new String[numChoices];
	    for (int i = 0; i < numChoices; i++)
	        {
		if (i < numChoices - 1)
 	            choices[i] = dataRange.substring(i,i+1);
		else
		    choices[i] = dataRange.substring(i);
		}
            fld.setChoiceControl(true);
	    fld.setChoicesFixed(true);
	    fld.setChoiceStrings(choices);

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
 	    XMLTag displayOpt = (XMLTag) attributes.get(XMLTag.DISPLAYOPTS);
	    if ((displayOpt != null) && (displayOpt == XMLTag.VERTICAL))
		bHorizontal = false;
	    String[] choices = new String[numChoices];
	    for (int i = 0; i < numChoices; i++)
	        {
		if (i < numChoices - 1)
 	            choices[i] = dataRange.substring(i,i+1);
		else
		    choices[i] = dataRange.substring(i);
		}
            fld.setChoiceControl(true);
	    fld.setChoicesFixed(true);
	    }
	else if (typeTag == XMLTag.RANGECONTROL)
	    {
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
		}
	    fld.setValueLimits(limits);
            }
	else if (typeTag == XMLTag.LISTBOX)
	    {
	    /* No special processing to be done for a list box */
            }
	else if (typeTag == XMLTag.TABLECONTROL)
            {
	    /* No special processing to be done for a list box */
	    }
	else
	    {
	    throw new SAXException(
                "Unimplemented control type: " + typeTag.toString());
	    }
	// Now set things that are common to all controls
	currentControl = fld;
	String pSpecStr = (String) attributes.get(XMLTag.PSPECSTR);
	if (pSpecStr != null)
	    currentControl.setPSpecifier(pSpecStr);
	XMLTag requiredTag = (XMLTag) attributes.get(XMLTag.BREQUIRED);
	if ((requiredTag != null) && (requiredTag == XMLTag.TRUE))
	    currentControl.setRequired(true);
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
	Vector<String> memFiles = new Vector<String>(10);
	StringTokenizer tokenizer = new StringTokenizer(parseString,",");
	while (tokenizer.hasMoreTokens())
	    {
	    String memFile = tokenizer.nextToken();
            if (memFile.startsWith("%"))
	        {
                memFile = textSource.getI18NText(memFile,memFile);
		}
	    memFiles.add(memFile);
	    }
	Object[] contents = memFiles.toArray();
	String[] memStrings = new String[contents.length];
	for (int i = 0; i < contents.length; i++)
	     memStrings[i] = (String) contents[i];
	return memStrings;
	}


      /**
       * Factorization of processControlSpec. Creates a ValueLimits
       * object, if possible, from a data range. Assumes double values.
       * @param rangeString String with data range
       * @returns ValueLimits object created or null if range is empty.
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
       * @returns ValueLimits object created or null if range is empty.
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
       * Create a new PanelInfo object of the appropriate type,
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
	XMLTag typeTag =  (XMLTag) attributes.get(XMLTag.TYPE);
	// above will throw a class cast exception if we have an
	// invalid type value.
	String id = (String) attributes.get(XMLTag.ID);
	PanelInfo newPanel = new PanelInfo(id);
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
	String cmd = (String) attributes.get(XMLTag.COMMAND);
	newPanel.setPanelCommand(cmd);
	String details = (String) attributes.get(XMLTag.DETAILSLINK);
	if (details == null)
	    newPanel.setDetailsLink(cmd);
	else
	    newPanel.setDetailsLink(details);
	currentPanel = newPanel;
	}

//==================================================================
      /**
       * Handles a reference to a control within a panelSpec element.
       * Finds control and adds it to the panel.
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
	FieldInfo fld = (FieldInfo) fieldTable.get(id);
	if (fld == null)
	     {
	     throw new SAXException(
	       "Control element (" + id + 
                 ") not found; probably not created yet");
	     }
	try
	     {
	     currentPanel.addField(fld);
	     }
	catch (Exception e)
	     {
	     throw new SAXException(e.getMessage());
	     }
	}


//==================================================================
      /**
       * Handles a reference to a panel within another panelSpec element.
       * Makes finds the referenced panel and adds it to the panel
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
	PanelInfo panel = (PanelInfo) panelTable.get(id);
	if (panel == null)
	     {
	     throw new SAXException(
	       "SubPanel element (" + id + 
                 ") not found; probably not created yet");
	     }

	try
	     {
	     currentPanel.addPanel(panel);
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
      /* callback fn to handle endelement tags in the XML data 
       * For the rmw.dtd, startElement() and endElement()
       * do all of the important processing.
       * These methods are automatically invoked from SAX, and should 
       * not be called directly.
       */
    public void endElement(String namespaceURI, String name, 
			   String qName) throws SAXException
        {
	if (bTracing)
	    { 
	    System.out.println(nestString + "endElement is called: " + qName);
	    nestLevel--;
	    nestString = getLevelString();
	    }

	XMLTag elementTag = XMLTag.lookUp(qName);
	if (elementTag == null)
	     throw new SAXException("No tag found for element " + name);

	if (bParseOnly)
	    return;

	// store the current item in the appropriate temp table and
	// then null it out.
	if (elementTag == XMLTag.CONTROLSPEC)
	    {
	    if (currentControl == null)
	        return;
	    FieldInfo existingField = (FieldInfo)
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
		System.out.println("*************************************");
		}
	    currentControl = null;
	    }
	else if (elementTag == XMLTag.PANELSPEC)
	    {
	    panelTable.put(currentPanel.getName(),currentPanel);
	    currentPanel = null;
	    }
	else if ((elementTag == XMLTag.HELP) ||
		 (elementTag == XMLTag.LABEL) ||
		 (elementTag == XMLTag.TITLE) ||
		 (elementTag == XMLTag.TOOLTIP) ||
		 (elementTag == XMLTag.DEFAULT) ||
		 (elementTag == XMLTag.CHOICES))
	    {
	    processTextElement(elementTag);
	    }
	else if (elementTag == XMLTag.UI)
	    {
	      // do Nothing
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
	    }
	else if (elementTag == XMLTag.TITLE)
	    {
	    if (currentPanel != null)
	        {
		String title = (String) xlatedText.get(0);
		currentPanel.setTitle(title);
		}  
	    }
	else if (elementTag == XMLTag.HELP)
	    {
	      // Need to concatenate all strings and format
	      // as HTML - will be embedded in another HTML
	      // document, so we can leave off the <HTML> and <BODY>
	    StringBuffer helpString = new StringBuffer();
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
	    helpString.append("</p></FONT>\n");
	    // could apply to either a control or a menu item.
	    if (currentControl != null)
	        {
		currentControl.setHelpString(helpString.toString());
		currentControl.setHelpKeys(keys);
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
	else if (elementTag == XMLTag.TOOLTIP)
	    {
	      // just ignore 
	      // only relevant to menu items

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

      //**************************************************************
      /**
       * Method to actually generate the details file.
       * @param filename  HTML filename to generate.
       *                  If null, use standard name.
       */
    public void generateDetailHtml(String filename)
        {
	String htmlFileName = "ddetail.html";
	String panelSection = null;
	FileWriter writer = null;
	if (filename != null)
            htmlFileName = filename;
	try 
	    {
	    writer = new FileWriter(htmlFileName);
	    writer.write("<HTML><BODY>\n");
	    Iterator panelIter = panelTable.values().iterator();
            while (panelIter.hasNext())
	        {
		PanelInfo panel = (PanelInfo) panelIter.next();
		if (panel.isPrimary())
		    {
		    panelSection = generatePanelDetails(panel);
		    writer.write(panelSection);
		    }
		}
	    writer.write("</BODY></HTML>\n");
	    writer.close();
	    }

	catch (IOException ioe)
	    {
	    System.out.println("Error creating or writing to " + htmlFileName);
	    ioe.printStackTrace();
	    }
	}

	/**
	 * Factorization. Generates an HTML string for a single
	 * panel and returns it.
	 * @param panel  Primary panel for which we want to generate HTML
	 * @returns HTML for this panel as a string.
	 */
    protected String generatePanelDetails(PanelInfo panel)
        {
	StringBuffer buffer = new StringBuffer(2048);
	buffer.append("<a name=\"" + panel.getDetailsLink() + "\">");
	buffer.append("<h3 align=center>" + panel.getTitle() + "</h3></a>");
	buffer.append("<table>\n");
	Vector fields = panel.getAllFields();
	for (int i = 0; i < fields.size(); i++)
	     {
	     FieldInfo fld = (FieldInfo) fields.get(i);
	     if (fld.isDummyControl())
	         continue;
	     String pSpec = fld.getPSpecifier();
	     if ((pSpec == null) || (pSpec.length() == 0))
	         continue;
             //buffer.append("<tr><td><table>\n");
	     buffer.append("<tr><th nowrap align=left>" + pSpec + "</th>\n");
	     buffer.append("<th></th><th></th>\n");
	     buffer.append("<th align=right>"+fld.getLabelText() + "</th></tr>\n");
	     buffer.append("<tr><td></td><td nowrap valign=top><b>Description:</b></td>");
	     buffer.append("<td colspan=2>");
	     buffer.append(fld.getHelpString());
             buffer.append("</td></tr>");
	     buffer.append("<tr><td></td><td nowrap valign=top><b>Required:</b></td>");
	     buffer.append("<td>");
	     buffer.append(fld.isRequired() ? "Yes" : "No");
	     buffer.append("</td></tr>\n");
	     String choices = null;
	     ValueLimits limits = fld.getValueLimits();
	     if ((fld.isChoiceControl()) && (fld.areChoicesFixed()))
                 {
		 choices = fld.getAppendedChoices();
		 }
	     else if (fld.isFileField())
	         {
                 if (fld.isExisting())
		     choices = "Input (existing) path and filename";
		 else
		     choices = "Output path and filename";
		 }
	     else if (limits != null)
	         {
		 if (limits.bInteger)
                     choices ="Integer value between " +
		               Integer.toString((int)limits.minValue) + " and " +
		               Integer.toString((int)limits.maxValue);
		 else
                     choices ="Real number between " +
		               Double.toString(limits.minValue) + " and " +
		               Double.toString(limits.maxValue);
		 }
	     if (choices != null)
	         {
	         buffer.append("<tr><td></td><td nowrap valign=top><b>Values:</b></td>");
	         buffer.append("<td colspan=2>" + choices + "</td></tr>\n");
		 }
             String dflt = fld.getDefaultValue();
	     if ((dflt != null) && (dflt.length() > 0))
	         {
	         buffer.append("<tr><td></td><td><b>Default:</b></td><td>" + dflt);
		 buffer.append("</td></tr>\n");
		 }
	     buffer.append("<tr><td colspan=4><hr></td></tr>\n");
	     //buffer.append("</table></td></tr>");
	     }
	buffer.append("</table>\n");
	buffer.append("<META name=\"PageBreak\" content=\"\">\n");
	return buffer.toString();
	}

//*********************************************************************
      /**
       * Access Methods
       */
    public XMLReader getXmlReader()
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

    public int getPanelCount()
        {
	return panelTable.size();
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
       * Translate an Attributes object into a hashtable keyed by
       * XMLTag objects, with values that are XMLTag objects
       * if possible (otherwise, strings). Throws an exception if
       * it is unable to map an attribute to an XMLTag - this means
       * that there is a mispelling or that our XMLTag.java needs to
       * be regenerated.
       * <p>
       * Returns null if the AttributeList is empty.
       */
    protected Hashtable attributesToTags(Attributes atts)
          throws SAXException
        {
	Hashtable<XMLTag,Object> table = null;
	for (int i = 0; i < atts.getLength(); i++)
	     {
	     if (table == null)
	         table = new Hashtable<XMLTag,Object>(atts.getLength());
	     String name = atts.getQName(i);
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


//*********************************************************************
      // driver program - invoke as DetailGenerator filename langFileDirectory
    static public void main(String[] argv)
        {
	boolean bFirstAdded = false;
	Hashtable master = new Hashtable();
	if (argv.length < 2)
	    {
	    System.out.println(
      "Usage: DetailGenerator <xmlfilename> <langFileDirectory> [trace] [parseonly]");
	    System.exit(0);
	    }
	
	I18NTextSource source = new I18NTextSource("en",argv[1],"%");
	try 
	    {
	    DetailGenerator generator = new DetailGenerator(argv[0],null,
						       source,
						       null);
	    if ((argv.length > 2) && (argv[2].compareTo("trace") == 0))
		generator.setTracing(true);

	    if ((argv.length > 3) && (argv[3].compareTo("parseonly") == 0))
		generator.setParseOnly(true);

	    generator.parse();
	    if (generator.getPanelCount() > 0)
	        generator.generateDetailHtml(null);
	    }
	catch (Exception e)
	    {
	    e.printStackTrace();
	    }
	}
    
    }
