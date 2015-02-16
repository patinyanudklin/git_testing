/*
 * SAXgrsHandler.java
 *
 * Copyright 2003 by Goldin-Rudahl Associates
 * 
 * Created by Kurt Rudahl 3/26/2003
 * derived from itext info
 *
 * This class is used just like SAXmyHandler, with two additions:
 *	1. it can recognize certain grs-specific tags and convert
 *	   them into API calls.
 *      2. it conditionally outputs tracing
 *
 * $Id: SAXgrsHandler.java,v 1.4 2003/06/10 12:43:27 rudahl Exp $
 * $Log: SAXgrsHandler.java,v $
 * Revision 1.4  2003/06/10 12:43:27  rudahl
 * allow for SQL stmt in Xml file
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

import java.awt.Color;
import java.util.*;
import java.text.SimpleDateFormat;
import java.text.FieldPosition;

import org.xml.sax.Attributes;

import com.lowagie.text.*;
import com.lowagie.text.xml.*;

/**
 * The <CODE>Tags</CODE>-class maps several XHTML-tags to iText-objects.
 */

public class SAXgrsHandler extends SAXiTextHandler
    {
    
    protected boolean bTracing = false;

	/* unlike SAXmyHandler, we require that all tags in the document
	 * be in myTags
	 */
    protected HashMap myTags;

    protected HashMap args;

    protected Properties documentProperties = new Properties();
    protected Stack documentPropertiesStack = new Stack();
    protected int iStackDepth = 0;
/**
 * Constructs a new SAXmyHandler that will translate all the events
 * triggered by the parser to actions on the <CODE>Document</CODE>-object.
 *
 * @param	document	this is the document on which events 
 *				must be triggered
 * @param	myTags		HashMap created from a tagmapxxx.xml file, 
 *				setting aliases for XML tags
 * @param	args		HashMap of commandline name=value pairs, to
 *				be used by ,val> tags
 * @param	bTracing	enable tracing
 */
    
    public SAXgrsHandler(DocListener document, HashMap myTags, 
			 HashMap args, boolean bTracing)
	{
        super(document);
	if (bTracing)
	    System.out.println("SAXgrsHandler::ctor (en)");
	this.bTracing = bTracing;
	this.myTags = myTags;
	this.args = args;
	if (bTracing)
	    System.out.println("SAXgrsHandler::ctor (ex)");
        }
    
/**
 * This method gets called when a start tag is encountered.
 *
 * @param	uri		not used
 * @param	lname		not used
 * @param	name		the name of the tag that is encountered
 * @param	attrs		the list of attributes
 */
    
    public void startElement(String uri, String lname, String name, 
			     Attributes attrs) 
	{
	if (bTracing)
	    System.out.println("SAXgrsHandler::startElement '"+name
			       +"' is called");
	if (! myTags.containsKey(name))
	    System.out.println("SAXgrsHandler::startElement '"+name
			       +"' is unknown");
	else
	    {
	    XmlPeer peer = (XmlPeer)myTags.get(name);
	    String sPeerTag = peer.getTag();
	    Properties peerAttrs = peer.getAttributes(attrs);
	    if (bTracing)
		System.out.println("SAXgrsHandler::startElement name='"
				   +name+"' peer='"+sPeerTag+"' stackdepth="+iStackDepth);

	    if (name.equals("SQL"))
		return;
	    if (name.equals("pageSpec"))
		{
		Enumeration enum = peerAttrs.propertyNames();
		while(enum.hasMoreElements())
	            {
		    String atName = (String)enum.nextElement();
		    String atValue = peerAttrs.getProperty(atName);
		    if (bTracing)
			System.out.println("SAXgrsHandler::startElement pageSpec '"
					   +atName+"' attribute ='"+atValue+"'");
		    if (atName.equals("defaultFont")) 
			documentProperties.setProperty("font",atValue);
		    else if (atName.equals("defaultSize")) 
			documentProperties.setProperty("size",atValue);
		    }
		}
	    /* copy documentProperties into new attributes without editing */
	    Properties attributes = new Properties();
	    Enumeration enum = documentProperties.propertyNames();
	    while(enum.hasMoreElements())
	        {
		String atName = (String)enum.nextElement();
		String atValue = documentProperties.getProperty(atName);
		//System.out.println("  copying attribute "+atName+"="+atValue);
		attributes.setProperty(atName,atValue);
		}
	    /* push copy of properties BEFORE getting other new attributes */
	    documentPropertiesStack.push(attributes);
	    iStackDepth++;

	    /* get values from attribute elements of tagmap 
	     * and from element itself and merge into property list */
	    enum = peerAttrs.propertyNames();
	    while(enum.hasMoreElements())
	        {
		String atName = (String)enum.nextElement();
		String atValue = peerAttrs.getProperty(atName);
		if (bTracing)
		    System.out.println("SAXgrsHandler::startElement found '"
				       +atName+"' attribute ='"+atValue+"'");
		if (! atName.equals("pageSize")		// only for attrs to pass to 
			&& ! atName.equals("pageStyle") // itext
		        && ! atName.equals("margins") 
		        && ! atName.equals("defaultFont") 
		        && ! atName.equals("defaultSize") 
		        && ! atName.equals("name") 
		        && ! atName.equals("id")) 
		    {
			//System.out.println("   from locProps: setting property "+atName+"="+atValue);
		    documentProperties.setProperty(atName,atValue);
		    }
		}


	    if (name.equals("document"))
		{
		enum = peerAttrs.propertyNames();
		while(enum.hasMoreElements())
	            {
		    String atName = (String)enum.nextElement();
		    String atValue = peerAttrs.getProperty(atName);
		    if (bTracing)
			System.out.println("SAXgrsHandler::startElement document '"
					   +atName+"' attribute ='"+atValue+"'");
		    if (atName.equals("margins")) 
		        {
			String[] fields = atValue.split(",");
			try
			    {
			    document.setMargins(Integer.parseInt(fields[0]),
						Integer.parseInt(fields[1]),
						Integer.parseInt(fields[2]),
						Integer.parseInt(fields[3]));
			    }
			catch (NumberFormatException nfe)
			    {
			    System.err.println("Format error in pageSpec margins spec");
			    System.err.println("  should be left,right,top,bottim");
			    System.err.println("Continuing processing with argins unchanged");
			    }
			}
		    }
		handleStartingTags(sPeerTag, documentProperties);
		}
	    else  if (name.equals("line"))
		{
		handleStartingTags("phrase",documentProperties);
		}
	    else  if (name.equals("table"))
	        {
		enum = peerAttrs.propertyNames();
		while(enum.hasMoreElements())
	            {
		    String atName = (String)enum.nextElement();
		    String atValue = peerAttrs.getProperty(atName);
		    if (atName.equals("font")) 
			documentProperties.setProperty("font",atValue);
		    else if (atName.equals("size")) 
			documentProperties.setProperty("size",atValue);
		    else if (atName.equals("leading")) 
			documentProperties.setProperty("leading",atValue);
		    }
		handleStartingTags(sPeerTag, documentProperties);
		}
	    else  if (name.equals("cell"))
		{
		handleStartingTags("cell",documentProperties);
		handleStartingTags("paragraph",documentProperties);
		}
	    else if (name.equals("var"))
		{
		String varName = peerAttrs.getProperty("name");
		String varDefault = peerAttrs.getProperty("default");
		String varVal = (String)args.get(varName);
		if (varVal == null)
		    varVal = varDefault; /* may also be null */
		if (currentChunk == null)
		    {
		    handleStartingTags("chunk",documentProperties);
		    currentChunk.append(varVal);
		    handleEndingTags("chunk");
		    }
		else
		    currentChunk.append(varVal);
		}
	    else if (name.equals("function"))
		{
		String fnName = peerAttrs.getProperty("name");
		String fnArg = peerAttrs.getProperty("arg");
		if (fnName.equals("date"))
		    {
		    StringBuffer b = new StringBuffer(32);
		    SimpleDateFormat f 
			= new SimpleDateFormat("MMMM d, yyyy");
		    String fnVal 
			= f.format(new Date(),b,
				   new FieldPosition(0)).toString();
		    if (currentChunk == null)
		        {
			handleStartingTags("chunk",documentProperties);
			currentChunk.append(fnVal);
			handleEndingTags("chunk"); /* appends & closes tmp chunk */
			}
		    else
			currentChunk.append(fnVal); /* eventually chunk will end */
		    }
		}
	    else if (! name.equals("pageSpec"))
		handleStartingTags(sPeerTag, documentProperties);
	    }
	if (bTracing)
	    System.out.println("SAXgrsHandler::startElement (ex) stackDepth="+iStackDepth);
	}
    
/**
 * This method gets called when an end tag is encountered.
 *
 * @param	name		the name of the tag that ends
 */
    
    public void endElement(String uri, String lname, String name)
	{
	if (bTracing)
	    System.out.println("SAXgrsHandler::endElement '"+name
			       +"' (en) stackDepth="+iStackDepth);
	if (name.equals("SQL"))
	    return;
	if (! myTags.containsKey(name))
	    System.out.println("SAXgrsHandler::endElement '"+name
			       +"' is unknown");
	else 
	    {
	    documentProperties = (Properties)documentPropertiesStack.pop();
	    iStackDepth--;
	    if (name.equals("line"))
	        {
		Phrase current = (Phrase) stack.peek();
		handleEndingTags("phrase");
		if (!current.isEmpty())
		    handleStartingTags("newline",null);
		}
	    else if (name.equals("cell"))
	        {
		handleEndingTags("paragraph");
		handleEndingTags("cell");
		}
	    else
	        {
		XmlPeer peer = (XmlPeer)myTags.get(name);
		String sPeerTag = peer.getTag();
		if (name.equals("paragraph"))
		    {
		    Paragraph current = (Paragraph) stack.peek();
		    System.out.println("SAXgrsHandler::endElement paragraph size="+current.size());
		    for (int i=0; i<current.size(); i++)
		        {
			Chunk ch = (Chunk)current.get(i);
			System.out.print(ch.content()+" ");
		        }
		    System.out.println("");
		    }
		handleEndingTags(sPeerTag);
		}
	    }
	}
    }

