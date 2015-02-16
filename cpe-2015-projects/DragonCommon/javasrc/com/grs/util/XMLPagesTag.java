/**  XMLPagesTag.java 
 *
 *  Implemented by Kurt Rudahl 3/19/2003 derived from gui/XMLTag.java
 *
 *  Copyright 2003 by Goldin-Rudahl Associates
 *
 * $Id: XMLPagesTag.java,v 1.1 2003/03/28 12:45:56 rudahl Exp $
 * $Log: XMLPagesTag.java,v $
 * Revision 1.1  2003/03/28 12:45:56  rudahl
 * components of Xml2Pages using lowagie - itext package
 *
 */

package com.grs.util;
import com.grs.gui.EnumBase;
import java.util.*;

/**
 * This is an enumerated class that defines legal values for
 * XML tags.
 * <p>
 * This file derived from a ccc/rmw version which was generated.
 * However, this one is NOT generated - this is the master.
 */
public class XMLPagesTag extends EnumBase
    {

      /**
       * Keep track of each final object created so that we
       * can convert a string name to the corresponding 
       * XMLTag object.
       */
    private static Hashtable nameTable = new Hashtable();

      /**
       * If true, this tag represents an attribute
       * which can have only fixed values, which are themselves
       * XMLPagesTag objects.
       */
 
    private boolean hasTagValue = false;

  /**
   * This constructor is private. Thus, no outside
   * class can create any instances of XMLPagesTag
   * other than those defined and assigned to constants,
   * below.
   */
    private XMLPagesTag(String opName, boolean bTagValue)
        {
        super(opName);
        hasTagValue = bTagValue;
	nameTable.put(opName,this);
        }

      /**
       * return the data type associated with this name, or
       * null if there is no match with any defined datatype.
       */
    public static XMLPagesTag lookUp(String tagName)
        {
	return (XMLPagesTag) (nameTable.get(tagName));
	}
  
    public boolean hasTagValue()
	{
        return hasTagValue;
	}

    // Primary element types
    public static final XMLPagesTag VERSIONSELECTOR = 
                           new XMLPagesTag("versionSelector",false);
    public static final XMLPagesTag DEFAULTCATEGORY = 
                           new XMLPagesTag("defaultCategory",true);
       
    public static final XMLPagesTag STRING = new XMLPagesTag("string",false);
    public static final XMLPagesTag INDEX = new XMLPagesTag("index",false);
    public static final XMLPagesTag ATTRIBUTE = new XMLPagesTag("attribute",false);
    public static final XMLPagesTag HEADER = new XMLPagesTag("header",false);

    public static final XMLPagesTag DEFAULTSTR = new XMLPagesTag("defaultStr",false);
    public static final XMLPagesTag DEFAULTINDEX = new XMLPagesTag("defaultIndex",false);
    public static final XMLPagesTag PSPECSTR = new XMLPagesTag("pSpecStr",false);
    public static final XMLPagesTag VALIDATOR = new XMLPagesTag("validator",false);
    public static final XMLPagesTag DATAMAXCHARS = new XMLPagesTag("dataMaxChars",false);
    public static final XMLPagesTag DATATYPE = new XMLPagesTag("dataType",true);
    public static final XMLPagesTag FLAG = new XMLPagesTag("flag",false);
    public static final XMLPagesTag INTEGER = new XMLPagesTag("integer",false);
    public static final XMLPagesTag DOUBLE = new XMLPagesTag("double",false);
    public static final XMLPagesTag FLOAT = new XMLPagesTag("float",false);
    public static final XMLPagesTag READFILE = new XMLPagesTag("readFile",false);
    public static final XMLPagesTag WRITEFILE = new XMLPagesTag("writeFile",false);
    public static final XMLPagesTag FONT = new XMLPagesTag("font",false);
    public static final XMLPagesTag COLOR = new XMLPagesTag("color",false);
    public static final XMLPagesTag UTM = new XMLPagesTag("UTM",false);
    public static final XMLPagesTag POINT = new XMLPagesTag("point",false);
    public static final XMLPagesTag VECTOR = new XMLPagesTag("vector",false);
    public static final XMLPagesTag MATRIX = new XMLPagesTag("matrix",false);

    public static final XMLPagesTag DATARANGE = new XMLPagesTag("dataRange",false);
    public static final XMLPagesTag QUERY = new XMLPagesTag("query",false);
    public static final XMLPagesTag OVERWRITE = new XMLPagesTag("overwrite",false);
    public static final XMLPagesTag APPEND = new XMLPagesTag("append",false);
    public static final XMLPagesTag ERROR = new XMLPagesTag("error",false);

    public static final XMLPagesTag VIRTUALHEIGHT = 
                                   new XMLPagesTag("virtualHeight",false);
    public static final XMLPagesTag VIRTUALWIDTH = new XMLPagesTag("virtualWidth",false);
    public static final XMLPagesTag DISPLAYOPTS = new XMLPagesTag("displayOpts",true);
    public static final XMLPagesTag HORIZONTAL = new XMLPagesTag("horizontal",false);
    public static final XMLPagesTag VERTICAL = new XMLPagesTag("vertical",false);
    public static final XMLPagesTag BORDER = new XMLPagesTag("border",false);
    public static final XMLPagesTag TTY = new XMLPagesTag("tty",false);
        // also, horizontal
    public static final XMLPagesTag COLUMNS = new XMLPagesTag("columns",false);
    public static final XMLPagesTag PLACEMENT = new XMLPagesTag("placement",false);

    /** Items for table description XML */
    public static final XMLPagesTag CALCRESULT = new XMLPagesTag("calcResult",false);
    public static final XMLPagesTag CALCTYPE = new XMLPagesTag("calcType",true);
    public static final XMLPagesTag SIMPLETABLE = new XMLPagesTag("SimpleTable",false);
    public static final XMLPagesTag TEXTTABLE = new XMLPagesTag("TextTable",false);
    public static final XMLPagesTag WIDEMULTILINETABLE =
	      new XMLPagesTag("WideMultiLineTable",false);
    public static final XMLPagesTag SIGNATURETABLE =
	      new XMLPagesTag("SignatureTable",false);
    public static final XMLPagesTag HEADERTABLE =
	      new XMLPagesTag("HeaderTable",false);
    public static final XMLPagesTag ROWCOUNT = new XMLPagesTag("rowCount",false);
    public static final XMLPagesTag ENCODING = new XMLPagesTag("encoding",false);
    public static final XMLPagesTag IDENTIFIER = new XMLPagesTag("identifier",false);
    public static final XMLPagesTag RESULTHEADER = new XMLPagesTag("resultHeader",false);
    public static final XMLPagesTag FIELDCOUNT = new XMLPagesTag("fieldCount",false);
    public static final XMLPagesTag DISPLAY = new XMLPagesTag("display",false);
    public static final XMLPagesTag FIELDID = new XMLPagesTag("fieldId",false);
    public static final XMLPagesTag DISPLAYKEY = new XMLPagesTag("displayKey",false);
   
    public static final XMLPagesTag ITEMCATEGORY = 
                             new XMLPagesTag("itemCategory",false);
    public static final XMLPagesTag ITEMINDEX = 
                              new XMLPagesTag("itemIndex",false);
    public static final XMLPagesTag DATE = new XMLPagesTag("date",false);
    public static final XMLPagesTag URL = new XMLPagesTag("url",false);
    public static final XMLPagesTag PREFIX = new XMLPagesTag("prefix",false);
    public static final XMLPagesTag TEXT = new XMLPagesTag("text",false);


    public static final XMLPagesTag DOCUMENT = new XMLPagesTag("document",false);

    public static final XMLPagesTag METASPEC = new XMLPagesTag("metaSpec",false);
    public static final XMLPagesTag ID = new XMLPagesTag("id",false);
    public static final XMLPagesTag NAME = new XMLPagesTag("name",false);

    public static final XMLPagesTag PAGESPEC = new XMLPagesTag("pageSpec",false);
    public static final XMLPagesTag TYPE = new XMLPagesTag("type",false);
    public static final XMLPagesTag LAYOUTSTYLE = new XMLPagesTag("layoutStyle",false);

    public static final XMLPagesTag PLACEMENTSPEC = new XMLPagesTag("placementSpec",false);
    public static final XMLPagesTag TOP = new XMLPagesTag("top ",false);
    public static final XMLPagesTag LEFT = new XMLPagesTag("left",false);
    public static final XMLPagesTag YCENTER = new XMLPagesTag("yCenter",false);
    public static final XMLPagesTag XCENTER = new XMLPagesTag("xCenter",false);
    public static final XMLPagesTag HEIGHT = new XMLPagesTag("height",false);
    public static final XMLPagesTag WIDTH = new XMLPagesTag("width",false);

    public static final XMLPagesTag TITLE = new XMLPagesTag("title",false);
    public static final XMLPagesTag HEADING = new XMLPagesTag("heading",false);
    public static final XMLPagesTag LEVEL = new XMLPagesTag("level",false);

    public static final XMLPagesTag PARAGRAPH = new XMLPagesTag("paragraph",false);
    public static final XMLPagesTag PREFORMATTEDTEXT
                     = new XMLPagesTag("preformattedText",false);
    public static final XMLPagesTag FRAGMENT = new XMLPagesTag("fragment",false);
    public static final XMLPagesTag EQUATION = new XMLPagesTag("equation",false);
    public static final XMLPagesTag FORMAT = new XMLPagesTag("format",false);

    public static final XMLPagesTag LIST = new XMLPagesTag("list",false);
    public static final XMLPagesTag NUMBEREDLIST = new XMLPagesTag("numberedList",false);
    public static final XMLPagesTag STYLE = new XMLPagesTag("style",false);
    public static final XMLPagesTag UNNUMBEREDLIST 
    			= new XMLPagesTag("unnumberedList",false);
    public static final XMLPagesTag BULLET = new XMLPagesTag("bullet",false);
    public static final XMLPagesTag LISTTITLE = new XMLPagesTag("listTitle",false);
    public static final XMLPagesTag LISTITEM = new XMLPagesTag("listItem",false);

    public static final XMLPagesTag TABLE = new XMLPagesTag("table",false);
    public static final XMLPagesTag TABLETITLE = new XMLPagesTag("tableTitle",false);
    public static final XMLPagesTag TABLEHEADER = new XMLPagesTag("tableHeader",false);
    public static final XMLPagesTag COLUMNTITLE = new XMLPagesTag("columnTitle",false);
    public static final XMLPagesTag COLUMNNUMBER = new XMLPagesTag("columnNumber",false);
    public static final XMLPagesTag TABLEROW = new XMLPagesTag("tableRow",false);
    public static final XMLPagesTag COLUMNVALUE = new XMLPagesTag("columnValue",false);
    public static final XMLPagesTag TABLEFOOTER = new XMLPagesTag("tableFooter",false);

    public static final XMLPagesTag IMAGE = new XMLPagesTag("image",false);
    public static final XMLPagesTag PATH = new XMLPagesTag("path",false);
    public static final XMLPagesTag GRAPHIC = new XMLPagesTag("graphic",false);
    public static final XMLPagesTag LEGEND = new XMLPagesTag("legend",false);
    public static final XMLPagesTag VAR = new XMLPagesTag("var",false);
    public static final XMLPagesTag DEFAULT = new XMLPagesTag("default",false);
    }

