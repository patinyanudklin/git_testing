/**
 * ServerQueryProcessor
 *
 *  Copyright  2001-2007-2007  by Sally Goldin & Kurt Rudahl
 *  Created by Sally Goldin, 4/27/2001
 *  
 *  $Id: ServerQueryProcessor.java,v 1.27 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ServerQueryProcessor.java,v $
 *  Revision 1.27  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.26  2006/07/23 09:12:22  goldin
 *  Attempt to switch to using Java 1.5 (Axel/Windows only)
 *
 *  Revision 1.25  2006/02/21 09:01:30  goldin
 *  Allow both horizontal and stacked labels in query boxes
 *
 *  Revision 1.24  2006/01/15 13:03:37  goldin
 *  Elaborate handling of i18M in radio boxes
 *
 *  Revision 1.23  2005/12/28 06:07:03  goldin
 *  Fiddle with formatting
 *
 *  Revision 1.22  2005/12/27 10:43:02  goldin
 *  Refine appearance and handling of more complex query boxes
 *
 *  Revision 1.21  2005/12/26 11:19:10  goldin
 *  Working on enhancements to query messages for registration
 *
 *  Revision 1.20  2005/07/24 13:19:23  goldin
 *  Set correct font in query dialogs
 *
 *  Revision 1.20  2005/07/22 11:09:00  goldin
 *  Working on Font Assignment
 *
 *  Revision 1.19  2005/02/06 09:00:25  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.18  2002/09/04 22:05:24  goldin
 *  Allow file fields to have multiple file types
 *
 *  Revision 1.17  2002/06/11 21:22:04  goldin
 *  Cosmetic improvments
 *
 *  Revision 1.16  2002/05/29 21:23:03  goldin
 *  Fix bug in query dlg positioning
 *
 *  Revision 1.15  2002/04/29 17:23:01  goldin
 *  Try making query a JFrame
 *
 *  Revision 1.14  2002/01/10 15:30:55  goldin
 *  Handle case of null label
 *
 *  Revision 1.13  2002/01/04 15:58:26  goldin
 *  Handle multi-line text controls
 *
 *  Revision 1.12  2001/11/30 18:01:21  goldin
 *  Moved most of the UI basic components to the com.grs.gui package
 *
 *  Revision 1.11  2001/11/29 16:12:33  goldin
 *  Add common pkg import
 *
 *  Revision 1.10  2001/11/21 15:17:53  goldin
 *  Make all references to getTimeOffset use ApplicationManager method
 *
 *  Revision 1.9  2001/11/19 20:29:38  goldin
 *  Moved IPC classes to new package
 *
 *  Revision 1.8  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.7  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.6  2001/06/18 15:04:17  goldin
 *  Fix bugs in Qry handling
 *
 *  Revision 1.5  2001/06/18 12:10:00  goldin
 *  Fixing bugs found by Kurt
 *
 *  Revision 1.4  2001/06/13 14:12:48  goldin
 *  Move buttons to be dialogwide, add ability to have file fields in Qry boxes
 *
 *  Revision 1.3  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.2  2001/05/28 16:36:26  goldin
 *  Debugging QueryProcessor
 *
 *  Revision 1.1  2001/05/27 15:45:44  goldin
 *  Additional work on query processor class and related functionality
 *
 *  Revision 1.1  2001/05/24 11:56:12  goldin
 *  Begin work on query processor
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.util.StringWrapper;
import com.grs.dragon.common.*;
import com.grs.dragon.ipc.*;
import java.io.*;
import java.util.*;
import java.text.MessageFormat;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.plaf.*;
import java.awt.*;

/**
 * This class looks for files that indicate requests for information
 * from the user. In response to such a query, the class will construct
 * a modal dialog with the controls and text as indicated in the
 * query file, and display it. The actual sending of data
 * back to the requester is handled by callbacks associated
 * with the buttons in the dialog.
 * <p>
 * Unlike some subclasses of the FileDetector class, this class
 * it does not exit its run method when it finds a file, but
 * rather, continues to loop looking for additional files.
 */
public class ServerQueryProcessor extends FileDetector
    {
      /**
       * Strings to use as keys or parts of keys in interpreting
       * the query file attributes.
       */
    protected final static String DIALOGID = "DialogId";
    protected final static String MAXLABELCHARS = "MaxLabelChars";
    protected final static String ID = "Id";
    protected final static String CTRL = "Ctrl";
    protected final static String TYPE = "Type";
    protected final static String TITLE = "Title";
    protected final static String KEY = "Key";
    protected final static String LABEL = "Label";
    protected final static String HELPKEY = "HelpKey";
    protected final static String DEFAULTVALUE = "DefaultValue";
    protected final static String PARENTCOORDS = "ParentCoords";
    protected final static String ICON = "Icon";
    protected final static String DATATYPE = "DataType";
    protected final static String BUTTONS = "BUTTONS";
    protected final static String OKBUTTONKEY = "OkButtonKey";
    protected final static String CANCELBUTTONKEY = "CancelButtonKey";
    protected final static String CHOICES = "Choices";
    protected final static String CHOICEKEYS = "ChoiceKeys";
    protected final static String CHOICEVALUES = "ChoiceValues";
    protected final static String COMMENTS = "Comments";
    protected final static String COMMENTKEYS = "CommentKeys";
    protected final static String SUBSTITUTIONS = "Substitutions";
    protected final static String HORIZONTAL = "Horizontal";

    protected static final int MAX_CTRL_COUNT = 8;

    protected static final String TEXTNOTFOUND = "** TEXT NOT FOUND **";

    protected int maxLabelChars = 60;

      /**
       * Hold onto the main application reference.
       */
    protected DragonUI mainApp = null;

     /**
      * Text source for translation.
      */
    protected I18NTextSource textSource = null;

      /**
       * Cache of previously created dialogs - keyed based on
       * dialog IDs.
       */
    protected Hashtable dialogCache = null;  

      /**
       * Use a single callback instance for all buttons.
       */
    protected QueryDialogCallback queryDialogCallback = null;

      /**
       * Use an invisible frame as the parent of the dialog,
       * so we can position it with respect to its nominal
       * parent.
       */
    protected JFrame dummyParent = null;

    /**
     * Constructor sets up file pattern for command files,
     * which will always have the same pattern.
     */
    public ServerQueryProcessor(DragonUI mainApp)
        {
	this.mainApp = mainApp;
        this.filePattern = "Qry*.$$$";
	this.directory = mainApp.getCfgProcessor().getKpath();
        dialogCache = new Hashtable(32);
        textSource = mainApp.getTextSource();
        queryDialogCallback = new QueryDialogCallback();
        dummyParent = mainApp;
	start();
        }

    /**
     * This method is called when the file we are trying to detect appears
     * in the monitored directory. It constructs and displays the
     * necessary dialog.
     */
    protected void executeFileAction(String filename)
              throws InterruptedException
        {
	IpcFile ipcFile = new IpcFile(filename,
				    ApplicationManager.getTimeOffset(),false);
	while (!ipcFile.isComplete())
	     {
             sleep(200);
	     ipcFile.retry();
	     }
        // now, get the command and act accordingly
        Hashtable attributes = ipcFile.getAttributes();
        String panelID = (String) attributes.get(DIALOGID);
        if (panelID == null)
	     {
	       // handle error -bad file format
	     }
	String title = null;
        String titleKey = (String) attributes.get(TITLE + KEY);
        if (titleKey != null)
	     {
	     title = textSource.getI18NText(titleKey,null);
	     }
        if ((title == null) || (title.length() < 2))
	     {
	     title = (String) attributes.get(TITLE);
	     }
	if ((title == null) || (title.length() < 2))
	     {
	     title = textSource.getI18NText("%h7000.14","NOTICE");
	     }
	JFrame dlg = (JFrame) dialogCache.get(panelID);
        if (dlg == null) // new dialog
	     {
             try
	         {
                 DragonPanel dPanel = constructPanel(panelID, attributes);
		 dPanel.setPanelTable(null);
		 dPanel.setDialogTable(dialogCache);
		 dlg = new JFrame(title);
		 dlg.getContentPane().add(dPanel);
                 dPanel.setEnclosingFrame(dlg);
		 dlg.setSize(dPanel.getPreferredSize());
	         dlg.setIconImage(new ImageIcon("dragexec.gif").getImage());
		 dialogCache.put(panelID, dlg);
		 }
	     catch (Exception e)
	         {
		   // handle error
		 e.printStackTrace();
		 }
	     }
        else
	     {
	     customizeDialogText(dlg, attributes);
	     }
	dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
        SwingUtilities.updateComponentTreeUI(dlg);
	if (title != null)
	    dlg.setTitle(title);
        setFilenameOnFields(dlg,filename);
        dlg.pack();
        repositionDialog(dlg,attributes);
        dlg.setVisible(true);
	}

      /**
       * Given a set of attribute values, construct an appropriate
       * DragonPanel which has the controls listed in the
       * hashtable.
       * @param panelID  ID for the new panel
       * @param attributes  Hashtable that describes all the
       *                 controls in the panel.
       */
    protected DragonPanel constructPanel(String panelID, Hashtable attributes)
                     throws Exception
        {
	int totalLabelHeight = 0;
	int fixedTextCount = 0;
	boolean bHasFileField = false;
	DRadioBox verboseRadioBox = null;
        boolean bLabelsOnly = true;
       	DragonPanel newPanel = new DragonPanel(panelID);
        DragonPanel buttonPanel = new DragonPanel(BUTTONS);
        buttonPanel.setBottom(true);
        buttonPanel.setPrimary(false);
        buttonPanel.setFlowRow(true);
	newPanel.setPopup(true);
        newPanel.setPrimary(false);
        int maxFieldWidth = 100;
	int maxFieldHeight = 30;
	String maxCharString = (String) attributes.get(MAXLABELCHARS);
	if (maxCharString != null)
	    maxLabelChars = Integer.parseInt(maxCharString);
        for (int ctrlNum = 0; ctrlNum < MAX_CTRL_COUNT; ctrlNum++)
	     {        
	     int width = 0;
	     int height = 0;
	     DragonField fld = constructField(ctrlNum, attributes);
	     if (fld == null)
                   break;

	     if (fld instanceof DRadioBox)
	        {
		verboseRadioBox = (DRadioBox) fld;
		if (!verboseRadioBox.isVerbose())
                   verboseRadioBox = null;
	        }
	     newPanel.addField(fld);
	     if ((verboseRadioBox == null) ||
                 (!fld.equals(verboseRadioBox)))
	        {
		width = fld.calculateWidth();
		if (width > maxFieldWidth)
		    maxFieldWidth = width;
		height = fld.calculateHeight();
		if (height > maxFieldHeight)
	            maxFieldHeight = height;
		}
	     if (fld instanceof DFileField)
	          bHasFileField = true;
	     if (fld instanceof DFixedText)
	         {
	         fixedTextCount++;
		 totalLabelHeight += height;
		 }
	     else
	         {
		 bLabelsOnly = false;
	         fld.setRequired(true);
		 }
	     }
	String btnKey = (String) attributes.get(OKBUTTONKEY);
	if (btnKey != null)
	     {
	     String label = textSource.getI18NText(btnKey,"OK");
	     DButtonField btn = new DButtonField("OKBUTTON", label);
	     buttonPanel.addField(btn);
	     btn.setCallback(queryDialogCallback);
	     }
	btnKey = (String) attributes.get(CANCELBUTTONKEY);
	if (btnKey != null)
	     {
	     String label = textSource.getI18NText(btnKey,"CANCEL");
	     DButtonField btn = new DButtonField("CANCELBUTTON", label);
	     buttonPanel.addField(btn);
	     btn.setCallback(queryDialogCallback);
	     }
        int items = newPanel.getItemCount();
	int rows = 0;
        boolean bHasButtons = false;
        if (buttonPanel.getItemCount() > 0)
	     {
             bHasButtons = true;
             buttonPanel.setBorder(BorderFactory.createMatteBorder(
                        5,5,5,5,buttonPanel.getBackground()));
             buttonPanel.doPanelLayout();
             newPanel.addPanel(buttonPanel);
	     }
	
        Dimension calcSize = null;
	if (bLabelsOnly)
	     {
	     calcSize = new Dimension((maxFieldWidth + 30),
				      (totalLabelHeight + (items * 5) + 40));
	     }
	else if (verboseRadioBox != null)
	     {
	     /* Assume only one verbose radio box per dialog */
	     int radioWidth = verboseRadioBox.calculateWidth();
	     int radioHeight = verboseRadioBox.calculateHeight();
	     if (radioWidth > maxFieldWidth)
	         maxFieldWidth = radioWidth;
	     rows = items -1;
	     if (bHasButtons)
	         rows++;
             calcSize = new Dimension(maxFieldWidth + 30,
				      rows * maxFieldHeight +
				      radioHeight);
             }
	/**
        else if ((items > 1) && (!bHasFileField) && (fixedTextCount < items))
	     {
	     rows = (int) Math.max(Math.ceil(((double)items/2)),1);
	     if (bHasButtons)
	         rows++;
             calcSize = new Dimension((maxFieldWidth + 30) * 2,
				      rows * maxFieldHeight );
	     }
	**/
        else 
	     {
	     rows = items + ((bHasButtons) ? 1 : 0);
             calcSize = new Dimension((maxFieldWidth + 30),
				      rows * maxFieldHeight);
	     }
        newPanel.setPreferredSize(calcSize);
	newPanel.doPanelLayout();
	return newPanel;
	}

      /**
       * Construct a particular type of DragonField
       * based on information in the attributes table.
       * @param fieldNum Which field number? Used to construct keys
       * @param attributes Hashtable holding info on control structure.
       * @return newly constructed DragonField.
       */
    protected DragonField constructField(int fieldNum,
					 Hashtable attributes)
        {
        String fieldNumString = String.valueOf(fieldNum);
        String type = (String) attributes.get(
                 CTRL + fieldNumString +TYPE);
        if (type == null)
	     return null;  // no more controls
        XMLTag ctrlType = XMLTag.lookUp(type);
        if (ctrlType == null)
	     {
	     System.out.println("Invalid control type: " + type);
	     return null;
	     }
        String id = (String) attributes.get(CTRL + fieldNumString + ID);
        if (id == null)
	     {
	       // handle error
	     return null;
	     }
        String dataType = (String) attributes.get(CTRL + fieldNumString +
						  DATATYPE);
        String label = getFieldLabelText(fieldNumString,attributes);
	String help = getFieldHelpText(fieldNumString,attributes);
	String defaultVal = getFieldDefaultText(fieldNumString,attributes);
        DragonField newField = createField(ctrlType, id, label, help,
					   defaultVal, dataType, 
					   fieldNumString,attributes);
        return newField;
	}

      /**
       * Factorization. Get the label text for a particular control
       * number.
       * @param fieldNumString  Field number as string.
       * @param attributes      Hashtable with attribute values
       * @return label text or null.
       */
    protected String getFieldLabelText(String fieldNumString,
				       Hashtable attributes)
        {
	String label = null;
	String substitutions = null;
        substitutions = (String) attributes.get(CTRL + fieldNumString + 
						  SUBSTITUTIONS);
        String labelKey = (String) attributes.get(CTRL + fieldNumString + 
						  LABEL + KEY);
        if (labelKey != null)
	     {
	     label = textSource.getI18NText(labelKey,null);
	     }
	if (label == null)
	     {
             label = (String) attributes.get(CTRL + fieldNumString + LABEL);
	     }
	if (label != null)
	     {
	     if (substitutions != null)
	         label = doSubstitutions(label,substitutions);
             label = StringWrapper.wrap(label,maxLabelChars);
	     }
	if (label == null)
	     label = TEXTNOTFOUND;
	return label;
        }

      /**
       * Factorization. Get the help text for a particular control
       * number.
       * @param fieldNumString  Field number as string.
       * @param attributes      Hashtable with attribute values
       * @return help text or null.
       */
    protected String getFieldHelpText(String fieldNumString,
				       Hashtable attributes)
        {
	String help = null;
        String helpKey = (String) attributes.get(CTRL + fieldNumString + 
						  HELPKEY);
        if (helpKey != null)
	     {
	     help = textSource.getI18NText(helpKey,null);
	     }
	return help;
	}

      /**
       * Factorization. Get the default valuetext for a particular control
       * number.
       * @param fieldNumString  Field number as string.
       * @param attributes      Hashtable with attribute values
       * @return default text or null.
       */
    protected String getFieldDefaultText(String fieldNumString,
				       Hashtable attributes)
        {
	String defaultVal = null;
	String defaultKey = (String) attributes.get(CTRL + fieldNumString + 
						  DEFAULTVALUE + KEY);
        if (defaultKey != null)
	     {
	     defaultVal = textSource.getI18NText(defaultKey,null);
	     }
	if (defaultVal == null)
	     {
	     defaultVal = (String) attributes.get(CTRL + fieldNumString +
					       DEFAULTVALUE);
	     }
	return defaultVal;
	}

      /**
       * Factorization. Get the translated choices (labels or alternative)
       * for a radio panel or combo control.
       * @param fieldNumString  Field number as string.
       * @param attributes      Hashtable with attribute values
       * @return Array of strings parsed from hashtable, or null.
       */
    protected String[] getFieldChoices(String fieldNumString,
				       Hashtable attributes)
        {
	String[] choices = null;
	ArrayList choicesList = new ArrayList();
	String tempString = (String) attributes.get(CTRL + fieldNumString + 
						  CHOICEKEYS);
        String tempString2 = (String) attributes.get(CTRL + fieldNumString + 
						  CHOICES);
	if (tempString == null)
            tempString = tempString2;

	/* if we got either choices or keys, parse and process */
        if (tempString != null)
	     {
	     StringTokenizer tokenizer = new StringTokenizer(tempString,"|");
	     StringTokenizer tokenizer2 = null;
             if (tempString2 != null) 
                 tokenizer2 = new StringTokenizer(tempString2,"|");
	     while (tokenizer.hasMoreTokens())
	        {
		String value = null;
                String dfltValue = null;
		String token = tokenizer.nextToken();
                if ((tokenizer2 != null) && (tokenizer2.hasMoreTokens()))
                    dfltValue = tokenizer2.nextToken();
                else
                    dfltValue = token; 
		if (token.startsWith("%")) /* it is a key */
		    value = textSource.getI18NText(token,dfltValue);
		else
		    value = dfltValue;
		choicesList.add(value);
	        }
	     }
	if (choicesList.size() > 0)
	    {
	    choices = new String[choicesList.size()];
            choicesList.toArray(choices);
	    }
	return choices;
	}


      /**
       * Factorization. Get the actual values that should be returned
       * for a radio panel or combo control. These are never keys.
       * @param fieldNumString  Field number as string.
       * @param attributes      Hashtable with attribute values
       * @return Array of strings parsed from hashtable, or null.
       */
    protected String[] getFieldValues(String fieldNumString,
				       Hashtable attributes)
        {
	String[] choiceValues = null;
	ArrayList choicesList = new ArrayList();
	String tempString = (String) attributes.get(CTRL + fieldNumString + 
						  CHOICEVALUES);
	/* if we got a string, parse and process */
        if (tempString != null)
	    {
	    StringTokenizer tokenizer = new StringTokenizer(tempString,"|");
	    while (tokenizer.hasMoreTokens())
	       {
	       String token = tokenizer.nextToken();
	       choicesList.add(token);
	       }
	    }
	if (choicesList.size() > 0)
	    {
	    choiceValues = new String[choicesList.size()];
	    choicesList.toArray(choiceValues);
	    }
	return choiceValues;
	}

      /**
       * Factorization. Get the translated comments for a
       * verbpse radio panel. Also handles substitutions.
       * @param fieldNumString  Field number as string.
       * @param attributes      Hashtable with attribute values
       * @return Array of strings parsed from hashtable, or null.
       */
    protected String[] getFieldComments(String fieldNumString,
				       Hashtable attributes)
        {
	String[] comments = null;
	ArrayList commentsList = new ArrayList();
	String substitutions = null;
        substitutions = (String) attributes.get(CTRL + fieldNumString + 
						  SUBSTITUTIONS);
	String tempString = (String) attributes.get(CTRL + fieldNumString + 
						  COMMENTKEYS);
        if (tempString == null)
            tempString = (String) attributes.get(CTRL + fieldNumString + 
						  COMMENTS);
	
	/* if we got either choices or keys, parse and process */
        if (tempString != null)
	     {
	     StringTokenizer tokenizer = new StringTokenizer(tempString,"|");
	     while (tokenizer.hasMoreTokens())
	        {
		String value = null;
		String token = tokenizer.nextToken();
		if (token.startsWith("%")) /* it is a key */
		    value = textSource.getI18NText(token,token);
		else
		    value = token;
	        if (substitutions != null)
	            value = doSubstitutions(value,substitutions);
		commentsList.add(value);
	        }
	     }
	if (commentsList.size() > 0)
	    {
	    comments = new String[commentsList.size()];
            commentsList.toArray(comments);
	    }
	return comments;
	}




      /**
       * Factorization. Creates a new DragonField of the appropriate
       * type, sets whatever text is available
       * @param typeTag Determines the kind of control
       * @param id   ID for new control
       * @param label  Text label for control
       * @param help   Help text for control
       * @param defaultVal Default value for control
       *   label, help or default might be null.
       * @param dataType DataType for control. Might be null.
       * @param fieldNumString Which field number is this?
       * @param attributes Hashtable of all attributes. We might
       *               need some special ones for some controls.
       * @return Newly constructed control. 
       */
    protected DragonField createField(XMLTag typeTag, String id,
				      String label, String help,
				      String defaultVal,
				      String dataType,
				      String fieldNumString,
				      Hashtable attributes)
        {
        DragonField currentControl = null;
	if (typeTag == XMLTag.PUSHBUTTON)
	    {
	    return null;
	    // as of 6/13/01 - buttons are specified via dialog wide attribs
	    }
	else if (typeTag == XMLTag.FIELD)
	    {
	    XMLTag dataTag = null;
	    if (dataType != null)
	        {
		dataTag = XMLTag.lookUp(dataType);
		}
	    if ((dataTag != null) && 
                ((dataTag == XMLTag.READFILE) ||
		 (dataTag == XMLTag.WRITEFILE) ||
                 (dataTag == XMLTag.PATH)))
	        {
		DFileField fld = new DFileField(id,label,10,
		      (dataTag != XMLTag.WRITEFILE),
                      (dataTag == XMLTag.PATH));
		currentControl = fld;
		int pos = defaultVal.indexOf(",");
		String filePattern = defaultVal.substring(pos+1);
		DFileType type = DFileType.getFileType(filePattern);
		if (type != null)
		    {
		    DFileType[] types = new DFileType[1];
		    types[0] = type;
		    fld.setFileTypes(types);
		    }
                if (pos > 0)
		    defaultVal = defaultVal.substring(0,pos);
		else
		    defaultVal = null;
		
		}
	    else
	        {
		boolean bHorizontal = true;
		String tempString = (String) attributes.get(
                         CTRL + fieldNumString + HORIZONTAL);
                if ((tempString != null) && 
		    (tempString.equalsIgnoreCase("FALSE")))
                    bHorizontal = false;

		DTextField fld = new DTextField(id,label,maxLabelChars/2,
                                       bHorizontal);
		currentControl = fld;
	        }
	    }
	else if (typeTag == XMLTag.FIXEDCOMBO) 
	    {
	    String[] choices = getFieldChoices(fieldNumString,attributes);
	    String[] values = getFieldValues(fieldNumString,attributes);
	    if ((choices != null) || (values != null)) /* need at least one */
	       {
               DComboField fld = new DComboField(id,label,values,choices,true);
	       currentControl = fld;
	       }
	    }
	else if (typeTag == XMLTag.CHECKBUTTON)
	    {
	    String dataRange = new String("YN");
	    DCheckField fld = new DCheckField(id,label,
					      dataRange.substring(0,1),
					      dataRange.substring(1));
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.FIXEDTEXT)
	    {
	    DFixedText fld = new DFixedText(id,label);
	    fld.setNewLine(true);
	    currentControl = fld;
	    }
	else if (typeTag == XMLTag.RADIOPANEL)
	    {
	    String[] choices = getFieldChoices(fieldNumString,attributes);
	    String[] values = getFieldValues(fieldNumString,attributes);
	    String[] comments = getFieldComments(fieldNumString,attributes);
	    DRadioBox fld = null;
	    if (comments == null) /* ordinary radio box */
	       {
               fld = new DRadioBox(id,label,values,choices, true);
	       }
	    else /* "verbose" radio box */
	       {
               fld = new DRadioBox(id,label, values, choices, comments, 
			       maxLabelChars);
	       }
	    currentControl = fld;
     	    }
        if (currentControl != null)
	    {
	    if (help != null)
	        currentControl.setHelpString(help);
	    if (defaultVal != null)
	        currentControl.setDefaultValue(defaultVal);
	    currentControl.setNewLine(true);
	    }
	return currentControl;
	}


      /**
       * Modify the label, help and default associated with each control
       * in an existing dialog. 
       * @param dlg  Dialog to be modified.
       * @param attributes Hashtable that has the new values.
       */
    protected void customizeDialogText(JFrame dlg, 
				       Hashtable attributes)
        {
        Component[] components = dlg.getContentPane().getComponents();
        DragonPanel panel = (DragonPanel) components[0];
	// should only be one component.
        for (int ctrlNum = 0; ctrlNum < MAX_CTRL_COUNT; ctrlNum++)
	     { 
             String fieldNumString = String.valueOf(ctrlNum);       
	     String id = (String) attributes.get(CTRL + fieldNumString + ID);
	     if (id == null)
	          break; // no more controls
	     DragonField fld = panel.getField(id);
	     if (fld == null)
	          break;
	     String label = getFieldLabelText(fieldNumString,attributes);
	     String help = getFieldHelpText(fieldNumString,attributes);
	     String defaultVal = getFieldDefaultText(fieldNumString,attributes);
	     // set values even if null, to overwrite old values
	     fld.setLabelText(label);
	     fld.setHelpString(help);
             if (fld instanceof DFileField)
	         {
		 DFileField fileField = (DFileField) fld;
 		 int pos = defaultVal.indexOf(",");
		 String filePattern = defaultVal.substring(pos+1);
		 DFileType type = DFileType.getFileType(filePattern);
		 if (type != null)
		    {
		    DFileType[] types = new DFileType[1];
		    types[0] = type;
		    fileField.setFileTypes(types);
		    }
		 defaultVal = defaultVal.substring(0,pos);
		 }
	     fld.setDefaultValue(defaultVal);
	     }
	// set labels on buttons
	String btnKey = (String) attributes.get(OKBUTTONKEY);
	DButtonField btn = (DButtonField) panel.getField("OKBUTTON");
	if ((btnKey != null) && (btn != null))
	     {
	     String label = textSource.getI18NText(btnKey,"OK");
	     btn.setLabelText(label);
	     }
	btnKey = (String) attributes.get(CANCELBUTTONKEY);
	btn = (DButtonField) panel.getField("CANCELBUTTON");
	if ((btnKey != null) && (btn != null))
	     {
	     String label = textSource.getI18NText(btnKey,"CANCEL");
	     btn.setLabelText(label);
	     }
	}

      /**
       * In order to create an appropriate response file, the callback
       * needs to know the original query file name.
       * We transmit this information via the generic userData member
       * of the DragonField objects.
       * This method also sets all fields to default values
       */
    protected void setFilenameOnFields(JFrame dlg, String filename)
        {
	Component[] components = dlg.getContentPane().getComponents();
        DragonPanel panel = (DragonPanel) components[0];
	// call setAllToDefaults first, because it clears
	// the userData field.
        panel.setAllToDefaults();
        Vector fields = panel.getAllFields();
	Iterator fldIt = fields.iterator();
	while (fldIt.hasNext())
	    {
            DragonField field = (DragonField) fldIt.next();
	    field.setUserData(filename);
	    }
	}

      /**
       * If the attributes table includes a specification of parent
       * coordinates, use those to position the dialog.
       * @param dlg Current dialog
       * @param attributes Hashtable of attributes from the query file.
       */
    protected void repositionDialog(JFrame dlg, Hashtable attributes)
        {
	int newX, newY = 0;
        Dimension currentSize = null;
        String coords = (String) attributes.get(PARENTCOORDS);
	if (coords == null)
	    {
            Point pt = mainApp.getLocation();
            Dimension dim = mainApp.getSize();
	    currentSize = dlg.getSize();
            newX = pt.x + (dim.width/2) - (currentSize.width/2);
	    newY = pt.y + (dim.height/2) - (currentSize.height/2);
	    }
	else
	    {
            int [] coordinates = new int[4];
	    StringTokenizer tokenizer = new StringTokenizer(coords,",");
	    int which = 0;
	    while (tokenizer.hasMoreTokens())
	        {
		String token = tokenizer.nextToken();
		coordinates[which] = Integer.parseInt(token);
		which++;
	        }
	    currentSize = dlg.getSize();
	    newX = coordinates[0] - currentSize.width;
	    newY = coordinates[1] + currentSize.height;
	    }
	if ((newX < 0) || (newY < 0))
            {
	    newX = 100;
	    newY = 100;
            }
        dlg.setLocation(newX, newY);
	}

      /**
       * Do substitutions in the passed message string
       * @param message String that contains the tokens
       * @param subString String of substitution tokens, 
       *                  delimited by vertical bars.
       * @return original string (if no tokens) or
       *         string with substitutions.
       */
     protected String doSubstitutions(String message, 
				      String substString)
        {
	String newMessage = message;
	ArrayList substList = new ArrayList();
	String substValues[] = null; 
	StringTokenizer tokenizer = new StringTokenizer(substString,"|");
	while (tokenizer.hasMoreTokens())
	    {
	    String token = tokenizer.nextToken();
	    substList.add(token);
	    }
        if (substList.size() > 0)
	    {
	    substValues = new String[substList.size()];
	    substList.toArray(substValues);
            }
	if ((substValues.length > 0) &&
            (message.length() > 0) && 
	    (message.indexOf("%") >= 0))
	  {
	  String newFormat = textSource.substituteJavaTokens(message);
	  newMessage = MessageFormat.format(newFormat,(Object[])substValues);
	  }
	return newMessage;
	}

    /**
     * This method loops, periodically examining the directory 
     * passed in to the constructor for a file that matches the 
     * pattern passed in the constructor.
     * When such a file appears in the directory, the method calls 
     * executeFileAction passing the relevant filename as an argument, 
     * and then returns to looping. 
     */
    public void run()
        {
        File dirFile = new File(directory);
        File[] matchFiles = null;
        while (true)
	    {
            try 
	        {
	        sleep(500);
                matchFiles = dirFile.listFiles(this);
		// if we find matches, process them
                if ((matchFiles != null) &&
		    (matchFiles.length > 0))
		    {
		    for (int i = 0; i < matchFiles.length; i++)
		        {
			executeFileAction(matchFiles[i].getAbsolutePath());
			}
		    }
                }
            catch (InterruptedException ie)
	        {
		  // continue to loop 
		}
	    }
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ServerQueryProcessor.java,v 1.27 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }









