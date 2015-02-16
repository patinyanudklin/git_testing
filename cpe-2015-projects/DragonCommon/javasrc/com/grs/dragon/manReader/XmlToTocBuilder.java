/**
 * XmlToTocBuilder.java
 *
 * ~~ Copyright 2001-2015 by Goldin-Rudahl Associates
 * ~~ EndC
 *
 * Created by Sally Goldin, 11/27/2001
 *
 * $Id: XmlToTocBuilder.java,v 1.2.2.1 2015/01/01 10:32:30 rudahl Exp $
 * $Log: XmlToTocBuilder.java,v $
 * Revision 1.2.2.1  2015/01/01 10:32:30  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.3  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.2  2007/05/31 03:26:53  rudahl
 * add 'whatis' boilerplate
 *
 * Revision 1.1  2001/11/27 17:37:14  goldin
 * Add capability to build tree from XML
 *
 */


package com.grs.dragon.manReader;
import com.grs.gui.XMLTag;
import java.util.*;
import java.io.*;
import org.xml.sax.*;

//*************************************************************************+
/** 
 * This class reads and parses an XML document describing the
 * table of contents to be displayed by the ManReader, and builds
 * up a tree of nodes corresponding to the topics and subtopics
 * in the XML description.
 */
public class XmlToTocBuilder extends HandlerBase 
    {

      /**
       * DTD file name 
       */
    protected String dtdFileName;


      /**
       * Reader that provides primary access to the XML data
       */
    protected StringReader xmlReader = null;


      /**
       * keep track of nested element level 
       * Used in tracing
       */
    protected int nestLevel = 0;
    protected String nestString = "";

    protected boolean bTracing = false;

      /**
       * Hashtable for attributes
       */
    protected Hashtable<XMLTag,Object> attributes = null;

      /**
       * Current parent node, to which new nodes will be
       * appended. This starts out being the root node
       * of the tree.
       */
    protected TocTreeNode currentParentNode = null;
      /**
       * Last created node.
       */
    protected TocTreeNode currentNode = null;

      /**
       * Counters for sequence within a level
       */
    protected int sequences[] = new int[10];

//==================================================================
      /**
       * Constructor - initializes currentParent, and creates the reader
       * @param xmlContent String representing the XML document.
       * @param rootNode Root of the Toc tree.
       */
    public XmlToTocBuilder(String xmlContent, 
			   TocTreeNode rootNode)
	{
	xmlReader = new StringReader(xmlContent);
	currentParentNode = rootNode;
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

        if (elementTag == XMLTag.TOC)
	    {
	    String text = (String) attributes.get(XMLTag.TEXT);
	    if (text != null)
	         currentParentNode.setNodeText(text);
	    }
	else if (elementTag == XMLTag.TOCSECTION)
	    {
            String id = (String) attributes.get(XMLTag.ID);
            String prefix = (String) attributes.get(XMLTag.PREFIX);
            String url = (String) attributes.get(XMLTag.URL);
            String text = (String) attributes.get(XMLTag.TEXT);
            String level = (String) attributes.get(XMLTag.LEVEL);
	    int iLevel = 1;
	    if (level != null) 
                iLevel = Integer.parseInt(level);
	    int iSeq = sequences[iLevel] + 1;
	    sequences[iLevel] = iSeq;
	    TocTreeNode thisNode = new TocTreeNode(id, 
						   url, 
						   text,
						   prefix,
						   iLevel, 
						   iSeq);
	    currentParentNode.add(thisNode);
	    currentNode = thisNode;
	    currentParentNode = thisNode;
	    }
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

	if (elementTag == XMLTag.TOCSECTION)
	    {
	    if (currentNode != currentParentNode)
                sequences[currentParentNode.getNodeLevel()+1] = 0;
            currentParentNode = (TocTreeNode) currentParentNode.getParent();
	    }

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
    protected Hashtable<XMLTag,Object> attributesToTags(AttributeList atts)
          throws SAXException
        {
	Hashtable<XMLTag,Object> table = null;
	for (int i = 0; i < atts.getLength(); i++)
	     {
	     if (table == null)
	         table = new Hashtable<XMLTag,Object>(atts.getLength());
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

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: XmlToTocBuilder.java,v 1.2.2.1 2015/01/01 10:32:30 rudahl Exp $ \n";
	}

    }








