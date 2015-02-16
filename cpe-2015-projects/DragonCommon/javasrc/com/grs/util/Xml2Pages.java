/**
 * Xml2Pages.java
 *
 * Copyright 2003 by Goldin-Rudahl Associates
 * 
 * Created by Kurt Rudahl 3/19/2003
 * derived from manReader/detailGenerator
 *
 * $Id: Xml2Pages.java,v 1.4 2003/06/10 12:43:07 rudahl Exp $
 * $Log: Xml2Pages.java,v $
 * Revision 1.4  2003/06/10 12:43:07  rudahl
 * allow for empty var values
 *
 * Revision 1.3  2003/06/04 01:53:45  rudahl
 * refined especially tables, colors
 *
 * Revision 1.2  2003/05/04 21:21:20  rudahl
 * polished/added paragraph line margins attrib-inheritance
 *
 * Revision 1.1  2003/03/28 12:45:56  rudahl
 * components of Xml2Pages using lowagie - itext package
 *
 *
 */

package com.grs.util;
import com.grs.gui.ValueLimits;


import com.lowagie.text.*;
import com.lowagie.text.pdf.PdfWriter;
import com.lowagie.text.html.HtmlWriter;
import com.lowagie.text.xml.*;
import java.util.*;
import java.io.*;
import javax.xml.transform.sax.*;
import javax.xml.parsers.*;
import org.xml.sax.*;
import org.xml.sax.helpers.*;

//*************************************************************************+
/** 
 * This class reads and parses an XML document describing or defining a document
 * and produces a file consisting of the specified one or more page document.
 * This is initially created to produce pdf output using the iText package
 * but can be used to produce other formats. In particular, we are considering it
 * for Dragon, possibly as a means of specifying the contents of the Viewport,
 * or for implementing the Decorate utility.
 * <p>
 * This class uses the SAX2 Api and is intended to be compiled
 * under Java 1.4, which provides an implementation and plug-ins
 * for that interface.
 *
 * @author  rudahl
 */

public class Xml2Pages extends DefaultHandler
    {
      /** temp accumulation of field info objects as they are created 
       */
    protected Hashtable fieldTable = new Hashtable(); 

      /** temp accumulation of panel info objects  as 
       *  they are created 
       */
    protected Hashtable panelTable = new Hashtable(); 


      /**
       * XML file to read.
       */
    protected String xmlFileName = null;

      /**
       * DTD file name 
       */
    protected String dtdFileName = null;
      
      /**
       * keep track of nested element level 
       * Used in tracing
       */
    protected int nestLevel = 0;
    protected String nestString = "";

    protected boolean bTracing = false;

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
       * Source of XML data
       */
//    protected InputSource xmlSource = null;

      /**
       * Object that actually parses the
       * XML and calls the callbacks.
       */
    protected XMLReader xmlReader = null;

    protected Document document = new Document();
        
//==================================================================
      /**
       * Constructor - intializes input file name, dtd file name.
       * @param	xmlFile		full path name to XML file
       * @param	dtdFile		full path name to DTD file
       * @param sResultFile	full path name to output file
       * @param iFileType	type of desired result: 0 => PDF 1 => HTML
       */
    public Xml2Pages(String xmlFile, String dtdFile, 
		     String sResultFile, int iFileType)
	{
	xmlFileName = xmlFile;
	dtdFileName = dtdFile;
	document.setMargins(0,0,0,0);
	try
	    {
	    FileInputStream stream = new FileInputStream(xmlFileName);
            // we create a writer that listens to the document
            // and directs a XML-stream to a file
	    if (iFileType == 0)
		PdfWriter.getInstance(document, 
				      new FileOutputStream(sResultFile));
	    else
		HtmlWriter.getInstance(document, 
				       new FileOutputStream(sResultFile));
	    }
	catch (FileNotFoundException fnf)
	    {
	    System.out.println("Cannot find XML file: " + xmlFileName);
	    }
	catch (DocumentException e)
	    {
	    System.out.println("Cannot create GrsPdfWriter: " + xmlFileName);
	    }
	}

      /** 
       *  Parse the specified XML, creating the appropriate 
       *  UI data structures as described in the XML.
       *  @param	args	hash of command line name=value pairs
       *			used for substitution in <var> tags
       */
    public void parse(HashMap args)
           throws ClassNotFoundException, IllegalAccessException,
	     InstantiationException, IOException, SAXException,
	     ParserConfigurationException
        {
	if (bTracing)
	    System.out.println("Xml2Pages::parse (en)");
	SAXParser saxParser = SAXParserFactory.newInstance().newSAXParser();
	xmlReader = saxParser.getXMLReader();
	xmlReader.setContentHandler(this);
	xmlReader.setEntityResolver(this);
	xmlReader.setErrorHandler(this);
	xmlReader.setDTDHandler(this);
	TagMap tagMap = new TagMap("com/grs/util/tagmapGRS.xml");
	if (bTracing)
	    System.out.println("Xml2Pages::parse about to construct handler");
	SAXgrsHandler h = new SAXgrsHandler(document, tagMap, args, bTracing);
	if (bTracing)
	    System.out.println("Xml2Pages::parse about to parse "+xmlFileName);
	saxParser.parse(xmlFileName,h);
	}

//==================================================================
      /** display the contents of the attribute list for debugging.
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

//=================================================================
      /**
       * Methods to handle each possible element type.
       */

    protected void startPage(Hashtable  attributes)
	{
	}

    protected void endPage(Hashtable  attributes)
	{
	}

    protected void processMetaSpec(Hashtable attributes)
	{
	}

    protected void processPlacementSpec(Hashtable attributes)
	{
	}

    protected void startPageElement(XMLPagesTag elementTag,
				    Hashtable attributes) // generally a noop
	{
	}

    protected void endPageElement(XMLPagesTag elementTag,
				  Hashtable attributes) // generally where we render it
	{
	}

//*********************************************************************
      /**
       * Access Methods
       */
    public XMLReader getXmlReader()
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

    public int getPanelCount()
        {
	return panelTable.size();
	}
      

//*********************************************************************
     
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
      // driver program - invoke as Xml2Pages srcfilename destfilename
    static public void main(String[] argv)
        {
	boolean bFirstAdded = false;
	HashMap master = new HashMap();
	if (argv.length < 2)
	    {
	    System.out.println(
		"Usage: Xml2Pages <xmlfilename> <resultfilename> "
		+ "[-trace] [-pdf|-html|-rtf] [name=val...]");
	    System.exit(0);
	    }
	
	try 
	    {
	    boolean bTracing = false;
	    int iFiletype = 0;
	    master.put("argc",new Integer(argv.length));
	    master.put("argv0",argv[0]);
	    master.put("argv1",argv[1]);
	    if (argv.length > 2)
		{
		    System.out.println("Supplied "+argv.length+" args");
		for (int i=2; i<argv.length; i++)
		    {
		    if (argv[i].compareTo("-trace") == 0)
	                {
			System.out.println("Tracing enabled");
			bTracing = true;
			}
		    else if (argv[i].compareTo("-pdf") == 0)
	                {
			System.out.println("Selecting PDF output");
			iFiletype = 0;
			}
		    else if (argv[i].compareTo("-html") == 0)
	                {
			System.out.println("Selecting HTML output");
			iFiletype = 1;
			}
		    else if (argv[i].compareTo("-rtf") == 0)
	                {
			System.out.println("Selecting RTF output");
			iFiletype = 2;
			}
		    else /* any number of name=value pairs */
			{      
			String[] fields = argv[i].split("=");
			if (fields.length > 1)
			    {
			    //System.out.println("    got '"+fields[0]+"'='"
				//	   +fields[1]+"' for arg "+i);
			    master.put(fields[0],fields[1]);
			    }
			else
			    {
			    //System.out.println("    got '"+fields[0]+"'=''"
				//	   +" for arg "+i);
			    master.put(fields[0],"");
			    }
			}
		    }
		}
	    Xml2Pages generator = new Xml2Pages(argv[0],null,argv[1],iFiletype);
	    if (bTracing)
		generator.setTracing(true);
	    generator.parse(master);
	    }
	catch (Exception e)
	    {
	    e.printStackTrace();
	    }
	}
    
    }
