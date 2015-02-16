/**  XMLTag.java 
*
*  Implemented by Kurt Rudahl 9/19/2000
*
*  ~~ Copyright  2000-2015  by Goldin-Rudahl Associates
*  ~~ EndC
*
* $Id: XMLTag.java,v 1.14.2.1 2015/01/01 13:51:54 rudahl Exp $
* $Log: XMLTag.java,v $
* Revision 1.14.2.1  2015/01/01 13:51:54  rudahl
* consolidating Dragon and OpenDragon
*
* Revision 1.19  2011/01/10 13:38:35  goldin
* Create new pattern-focused file chooser capability for LIS
*
* Revision 1.18  2010/12/06 11:16:27  goldin
* Add new attribute to XML to require a drive
*
* Revision 1.17  2007/08/27 11:36:47  goldin
* Add functionality to table including ability to sort
*
* Revision 1.16  2007/08/19 11:19:05  goldin
* Changes to allow creation of DTableField objects from XML
*
* Revision 1.15  2007/07/20 03:53:35  goldin
* Get rid of unchecked operation warnings by parameterizing collections
*
* Revision 1.14  2007/01/14 11:53:44  goldin
* Allow a choice as to whether a panel returns all tabs or not
*
* Revision 1.13  2007/01/05 07:41:58  rudahl
* added Whatis info
*
* Revision 1.12  2007/01/01 13:52:16  goldin
* Add and integrate new controls for rule creation screen
*
* Revision 1.11  2006/12/25 10:48:37  goldin
* Begin implementation of multi-select file control
*
* Revision 1.10  2006/11/30 08:41:40  goldin
* Add new report generation functions for multi simple table category of report
*
* Revision 1.9  2005/12/24 12:39:03  goldin
* Create 'verbose' variant of radio boxes
*
* Revision 1.8  2002/09/14 21:57:28  goldin
* Add new bKeepNoncurrent attribute
*
* Revision 1.7  2002/06/28 14:11:02  goldin
* Provide infrastructure for usermanual help implementation
*
* Revision 1.6  2002/06/24 18:05:38  goldin
* Add new Tag for detailsLink
*
* Revision 1.5  2002/05/29 17:54:01  goldin
* Add support for returning blanks
*
* Revision 1.4  2002/04/02 00:13:28  goldin
* Put in infrastructure for testing for file overwrite warning flag
*
* Revision 1.3  2001/11/29 16:13:31  goldin
* Add date attribute
*
* Revision 1.2  2001/11/27 16:54:46  goldin
* Add tags for Toc processing
*
* Revision 1.1  2001/11/27 16:49:10  goldin
* Move XMLTag and EnumBase to general Gui package
*
* Revision 1.17  2001/11/05 13:59:16  goldin
* Put UI code in a package
*
* Revision 1.16  2001/10/22 10:58:19  goldin
* Provide VERSIONSELECTOR functionality
*
* Revision 1.15  2001/10/17 17:49:23  goldin
* Begin rework of HTML reports
*
* Revision 1.14  2001/08/23 18:05:40  goldin
* Add functionality to interpret TextTable calcResult messages
*
* Revision 1.13  2001/06/15 16:26:15  goldin
* Modify CalcResultParser to handle different output formats
*
* Revision 1.12  2001/06/13 14:12:48  goldin
* Move buttons to be dialogwide, add ability to have file fields in Qry boxes
*
* Revision 1.11  2001/05/21 16:18:57  goldin
* Initial implementation of table type messages
*
* Revision 1.10  2001/04/26 12:24:03  goldin
* implement bigHelp
*
* Revision 1.9  2001/04/05 13:34:51  goldin
* Cleanup behavior, fix XML errors
*
* Revision 1.8  2001/03/20 18:04:15  goldin
* Implement tabbed panes, clean up menu help:
*
* Revision 1.7  2001/03/16 19:23:46  goldin
* Added fixed length option for DTextField and DFileField; added callbacks to menu items
*
* Revision 1.6  2001/03/03 19:56:58  goldin
* Fine tuning screen layout and appearance
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
*/

package com.grs.gui;
import java.util.*;

/**
 * This is an enumerated class that defines legal values for
 * XML tags.
 * <p>
 * This file exists in two forms:<br>
 * XMLTag.java.template is the original source, kept under version control<br>
 * XMLTag.java is generated from the .template file and the current rmw.dtd.
 * <br><b>DO NOT EDIT XMLTag.java</b>
 */
public class XMLTag extends EnumBase
    {

      /**
       * Keep track of each final object created so that we
       * can convert a string name to the corresponding 
       * XMLTag object.
       */
    private static Hashtable<String,XMLTag> nameTable = 
             new Hashtable<String,XMLTag>();

      /**
       * If true, this tag represents an attribute
       * which can have only fixed values, which are themselves
       * XMLTag objects.
       */
 
    private boolean hasTagValue = false;

  /**
   * This constructor is private. Thus, no outside
   * class can create any instances of XMLTag
   * other than those defined and assigned to constants,
   * below.
   */
    private XMLTag(String opName, boolean bTagValue)
        {
        super(opName);
        hasTagValue = bTagValue;
	nameTable.put(opName,this);
        }

      /**
       * return the data type associated with this name, or
       * null if there is no match with any defined datatype.
       */
    public static XMLTag lookUp(String tagName)
        {
	return (XMLTag) (nameTable.get(tagName));
	}
  
    public boolean hasTagValue()
	{
        return hasTagValue;
	}

    // Primary element types
    public static final XMLTag MENUBUTTONSPEC = 
                  new XMLTag("menuButtonSpec",false);
    public static final XMLTag UI = new XMLTag("UI",false);
    public static final XMLTag XLATETEXT = new XMLTag("xlateText",false);
    public static final XMLTag LABEL = new XMLTag("label",false);
    public static final XMLTag HELP = new XMLTag("help",false);
    public static final XMLTag DEFAULT = new XMLTag("default",false);
    public static final XMLTag TOOLTIP = new XMLTag("toolTip",false);
    public static final XMLTag MENUSPEC = new XMLTag("menuSpec",false);
    public static final XMLTag MENUBUTTON = new XMLTag("menuButton",false);
    public static final XMLTag SEPARATOR = new XMLTag("separator",false);
    public static final XMLTag CONTROLSPEC = new XMLTag("controlSpec",false);
    public static final XMLTag CHOICES = new XMLTag("choices",false);
    public static final XMLTag COMMENTS = new XMLTag("comments",false);
    public static final XMLTag PANELSPEC = new XMLTag("panelSpec",false);
    public static final XMLTag TITLE = new XMLTag("title",false);
    public static final XMLTag CONTROL = new XMLTag("control",false);
    public static final XMLTag PANEL = new XMLTag("panel",false);

    // Attributes and, where relevant, their possible values
    public static final XMLTag ID = new XMLTag("id",false);
    public static final XMLTag VAR = new XMLTag("var",false);
    public static final XMLTag COMMAND = new XMLTag("command",false);
    public static final XMLTag ACCELERATOR = new XMLTag("accelerator",false);
    public static final XMLTag ATTACHID = new XMLTag("attachID",false);
    public static final XMLTag BENABLED = new XMLTag("bEnabled",true);
       public static final XMLTag TRUE = new XMLTag("true",false);
       public static final XMLTag FALSE = new XMLTag("false",false);
    public static final XMLTag BMULTI = new XMLTag("bMulti",true);
    public static final XMLTag SUBSTITUTE = new XMLTag("substitute",false);
    public static final XMLTag TAG = new XMLTag("tag",true);
       public static final XMLTag PARAGRAPH = new XMLTag("paragraph", false);
       public static final XMLTag LISTITEM = new XMLTag("listItem", false);
       public static final XMLTag PANELTITLE = new XMLTag("panelTitle", false);
       public static final XMLTag FRAGMENT = new XMLTag("fragment", false);
       public static final XMLTag CONTROLLABEL = 
		      new XMLTag("controlLabel", false);
       public static final XMLTag CONTROLDEFAULT = 
		      new XMLTag("controlDefault", false);
    public static final XMLTag REMIND = new XMLTag("remind",false);
    public static final XMLTag TYPE = new XMLTag("type",true);
	// menu button spec types:
       public static final XMLTag CHECK = new XMLTag("check",false);
       public static final XMLTag EXECUTE = new XMLTag("execute",false);
       public static final XMLTag SUBMENU = new XMLTag("submenu",false);
	// menu spec types
       public static final XMLTag MENUBAR = new XMLTag("menubar",false);
       public static final XMLTag DROPDOWN = new XMLTag("dropdown",false);
	// control types
       public static final XMLTag FIELD = new XMLTag("field",false);
       public static final XMLTag FIXEDCOMBO = new XMLTag("fixedCombo",false);
       public static final XMLTag VARCOMBO = new XMLTag("varCombo",false);
       public static final XMLTag PUSHBUTTON = new XMLTag("pushButton",false);
       public static final XMLTag CHECKBUTTON = new XMLTag("checkButton",false);
       public static final XMLTag FIXEDTEXT = new XMLTag("fixedText",false);
       public static final XMLTag RADIOPANEL = new XMLTag("radioPanel",false);
       public static final XMLTag EDITBOX = new XMLTag("editBox",false);
       public static final XMLTag LISTBOX = new XMLTag("listBox",false);
       public static final XMLTag RANGECONTROL = new XMLTag("rangeControl",
							    false);
       public static final XMLTag TABLECONTROL = new XMLTag("tableControl",
							    false);

	// panel types
       public static final XMLTag TOPLEVEL = new XMLTag("topLevel",false);
       public static final XMLTag FRAME = new XMLTag("frame",false);
       public static final XMLTag TABPANEL = new XMLTag("tabPanel",false);
          public static final XMLTag RETURNALL = new XMLTag("returnAll",false);

       public static final XMLTag TABGROUP = new XMLTag("tabGroup",false);
       public static final XMLTag POPUP = new XMLTag("popup",false);
       public static final XMLTag FILE = new XMLTag("file",false);
          // also, font & color
    
    public static final XMLTag VERSIONSELECTOR = 
                           new XMLTag("versionSelector",false);
    public static final XMLTag DEFAULTCATEGORY = 
                           new XMLTag("defaultCategory",true);
       
       public static final XMLTag STRING = new XMLTag("string",false);
       public static final XMLTag XLATESTRING = 
		          new XMLTag("xlateString",false);
       public static final XMLTag INDEX = new XMLTag("index",false);
       public static final XMLTag ATTRIBUTE = new XMLTag("attribute",false);
       public static final XMLTag HEADER = new XMLTag("header",false);

    public static final XMLTag DEFAULTSTR = new XMLTag("defaultStr",false);
    public static final XMLTag DEFAULTINDEX = new XMLTag("defaultIndex",false);
    public static final XMLTag PSPECSTR = new XMLTag("pSpecStr",false);
    public static final XMLTag VALIDATOR = new XMLTag("validator",false);
    public static final XMLTag DATAMAXCHARS = new XMLTag("dataMaxChars",false);
    public static final XMLTag DATATYPE = new XMLTag("dataType",true);
       public static final XMLTag FLAG = new XMLTag("flag",false);
       public static final XMLTag INTEGER = new XMLTag("integer",false);
       public static final XMLTag DOUBLE = new XMLTag("double",false);
       public static final XMLTag FLOAT = new XMLTag("float",false);
       public static final XMLTag READFILE = new XMLTag("readFile",false);
       public static final XMLTag WRITEFILE = new XMLTag("writeFile",false);
       public static final XMLTag PATH = new XMLTag("path",false);
       public static final XMLTag FONT = new XMLTag("font",false);
       public static final XMLTag COLOR = new XMLTag("color",false);
       public static final XMLTag UTM = new XMLTag("UTM",false);
       public static final XMLTag POINT = new XMLTag("point",false);
       public static final XMLTag VECTOR = new XMLTag("vector",false);
       public static final XMLTag MATRIX = new XMLTag("matrix",false);

    public static final XMLTag MAXROWS = new XMLTag("maxRows",false);
    public static final XMLTag SORTCOLUMN = new XMLTag("sortColumn",false);
    public static final XMLTag DATARANGE = new XMLTag("dataRange",false);
    public static final XMLTag WRITEFILEOPTION = 
                                   new XMLTag("writeFileOption",true);
       public static final XMLTag QUERY = new XMLTag("query",false);
       public static final XMLTag OVERWRITE = new XMLTag("overwrite",false);
       public static final XMLTag APPEND = new XMLTag("append",false);
       public static final XMLTag ERROR = new XMLTag("error",false);

    public static final XMLTag BKEEPCONTEXT = new XMLTag("bKeepContext",true);
    public static final XMLTag BKEEPNONCURRENT = 
                        new XMLTag("bKeepNonCurrent",true);
    public static final XMLTag BREQUIRED = new XMLTag("bRequired",true);
    public static final XMLTag BPATTERNS = new XMLTag("bPatterns",true);
    public static final XMLTag BOVERWRITE = new XMLTag("bOverwrite",true);
    public static final XMLTag BDRIVEREQUIRED = new XMLTag("bDriveRequired",true);
    public static final XMLTag BRETURNBLANKS = new XMLTag("bReturnBlanks",true);
    public static final XMLTag BVERBOSE = new XMLTag("bVerbose",true);
    public static final XMLTag CALLBACK = new XMLTag("callback",false);
    public static final XMLTag ADDCALLBACK = new XMLTag("addCallback",false);
    public static final XMLTag INITIALIZER = new XMLTag("initializer",false);
    public static final XMLTag PREFMNEMONIC = new XMLTag("prefMnemonic",false);
    public static final XMLTag PLACEMENTOPTS = new XMLTag("placementOpts",false);

    public static final XMLTag COMMENTWIDTH = new XMLTag("commentWidth",false);
    public static final XMLTag HEIGHT = new XMLTag("height",false);
    public static final XMLTag WIDTH = new XMLTag("width",false);
    public static final XMLTag VIRTUALHEIGHT = 
                                   new XMLTag("virtualHeight",false);
    public static final XMLTag VIRTUALWIDTH = new XMLTag("virtualWidth",false);
    public static final XMLTag DISPLAYOPTS = new XMLTag("displayOpts",true);
       public static final XMLTag HORIZONTAL = new XMLTag("horizontal",false);
       public static final XMLTag VERTICAL = new XMLTag("vertical",false);
       public static final XMLTag BORDER = new XMLTag("border",false);
    public static final XMLTag BIGHELP = new XMLTag("bBigHelp",true);
    public static final XMLTag LAYOUTSTYLE = new XMLTag("layoutStyle",true);
       public static final XMLTag TTY = new XMLTag("tty",false);
        // also, horizontal
    public static final XMLTag COLUMNS = new XMLTag("columns",false);
    public static final XMLTag PLACEMENT = new XMLTag("placement",false);

    /** Items for table description XML */
    public static final XMLTag CALCRESULT = new XMLTag("calcResult",false);
    public static final XMLTag CALCTYPE = new XMLTag("calcType",true);
       public static final XMLTag SIMPLETABLE = new XMLTag("SimpleTable",
	false);
       public static final XMLTag TEXTTABLE = new XMLTag("TextTable",
	false);
       public static final XMLTag WIDEMULTILINETABLE =
	      new XMLTag("WideMultiLineTable",false);
       public static final XMLTag SIGNATURETABLE =
	      new XMLTag("SignatureTable",false);
       public static final XMLTag HEADERTABLE =
	      new XMLTag("HeaderTable",false);
       public static final XMLTag MULTISIMPLETABLE =
	      new XMLTag("MultiSimpleTable",false);
    public static final XMLTag HORIZRULE = new XMLTag("horizRule",false);
    public static final XMLTag NEWTABLE = new XMLTag("newTable",false);
    public static final XMLTag ROWCOUNT = new XMLTag("rowCount",false);
    public static final XMLTag ENCODING = new XMLTag("encoding",false);
    public static final XMLTag IDENTIFIER = new XMLTag("identifier",false);
    public static final XMLTag RESULTHEADER = new XMLTag("resultHeader",false);
    public static final XMLTag FIELDCOUNT = new XMLTag("fieldCount",false);
    public static final XMLTag DISPLAY = new XMLTag("display",false);
    public static final XMLTag FIELDID = new XMLTag("fieldId",false);
    public static final XMLTag DISPLAYKEY = new XMLTag("displayKey",false);
    public static final XMLTag RESULTROW = new XMLTag("resultRow",false);
    public static final XMLTag RESULTITEM = new XMLTag("resultItem",false);
    public static final XMLTag RESULTGROUP = new XMLTag("resultGroup",false);
    public static final XMLTag RESULTFIELD = new XMLTag("resultField",false);
    public static final XMLTag NOTELINE  = new XMLTag("noteLine",false);
   
      public static final XMLTag ITEMCATEGORY = 
                              new XMLTag("itemCategory",false);
      public static final XMLTag ITEMINDEX = 
                              new XMLTag("itemIndex",false);
    public static final XMLTag TOC  = new XMLTag("toc",false);
      public static final XMLTag DATE = 
                              new XMLTag("date",false);
    public static final XMLTag TOCSECTION  = new XMLTag("toc_section",false);
      public static final XMLTag LEVEL = 
                              new XMLTag("level",false);
      public static final XMLTag URL = 
                              new XMLTag("url",false);
      public static final XMLTag PREFIX = 
                              new XMLTag("prefix",false);
      public static final XMLTag TEXT = 
                              new XMLTag("text",false);
    public static final XMLTag DETAILSLINK  = new XMLTag("detailsLink",false);


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: XMLTag.java,v 1.14.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }




