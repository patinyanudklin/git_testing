/**
 * XMLDomIO
 *
 *   Created 3/2/2004 by Sally Goldin & Kurt Rudahl
 *
 *   $Id: XMLDomIO.java,v 1.1 2004/03/02 10:41:00 rudahl Exp $
 *
 *   $Log: XMLDomIO.java,v $
 *   Revision 1.1  2004/03/02 10:41:00  rudahl
 *   initially used for evp package
 *
 */

package com.grs.util;

import java.io.*;
import org.jdom.Document;
import org.jdom.JDOMException;
import org.jdom.input.SAXBuilder;
import org.jdom.output.XMLOutputter;
import java.util.*;

/**
 * <p><code>XMLDomIO</code> Reads an XML file or input stream
 * into a JDOM <code>Document</code> using a SAX 2.0
 * parser. Also contains the ability to write an
 * XML document to an XML file. This class does not
 * do any interpretation of the XML content; it simply
 * returns a DOM Document, or uses one for output.
 * </p>
  */
public class XMLDomIO
{
    /** Xerces main SAX parser class  */
    private final static String saxDriverClass =
        "org.apache.xerces.parsers.SAXParser";

    /**
     * This method just parses XML data from a Reader.
     * @param  inputReader   Reader from which it can get the data
     * @return               Document resulting from the parse. 
     * @throws JDOMException or IOException if error occurs in parse.
     */
    public static Document parse(Reader inputReader) throws JDOMException,
							    IOException
        {
	Document doc = null;
	// SAXBuilder builds a JDOM tree using SAX.
	SAXBuilder builder = new SAXBuilder(saxDriverClass, true);
	
	// Build the document from the supplied file
	doc = builder.build(inputReader);
	return doc;
	} 
 
    /**
     * Parse an XML document from a file. 
     * @param  filename    XML file to read (with path)
     * @return               Document resulting from the parse. 
     * @throws JDOMException or IOException if error occurs in parse.
     */
    public static Document parse(String filename) throws JDOMException,
							 IOException
        {
	FileReader reader = new FileReader(filename);
	return parse(reader);
	}

    /**
     * Write a Document to an XML file. 
     * @param  document   The Document to be written out
     * @param  filename   The file to which it should be written
     * @throws            IO exception if error occurs on output
     */
    public static void writeXMLFile(Document document, String filename)
	                            throws IOException
        {
	FileWriter writer = null;
	try
            {
            writer = new FileWriter(filename);
            XMLOutputter outputter = new XMLOutputter();
            outputter.setNewlines(true);
            outputter.setIndent(true);
            outputter.setTextTrim(true);
            outputter.setExpandEmptyElements(true);
	    outputter.output(document, writer);
	    }
	catch (IOException ioe)
	    {
	    throw ioe;
            }
        finally
            {
	    if (writer != null)
		writer.close();
	    }
	}

}
