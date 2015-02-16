/** 
 * DMultiFileField.java
 *
 *    Control to allow selection of multiple (image) file names
 *
 *	~~ Copyright  2006-2015   Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri
 *	~~ EndC
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *    
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *
 * $Id: DMultiFileField.java,v 1.5.2.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: DMultiFileField.java,v $
 * Revision 1.5.2.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.9  2010/12/24 12:45:56  goldin
 * remove print statements
 *
 * Revision 1.8  2010/12/20 11:19:14  goldin
 * Working on callback for ORDER field
 *
 * Revision 1.7  2007/10/03 11:39:44  goldin
 * clear inputField after pressing browse button
 *
 * Revision 1.6  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.5  2007/05/13 08:26:23  goldin
 * Fix focus problem with multiselect panel
 *
 * Revision 1.4  2007/02/15 11:16:55  goldin
 * Add initializer to clear multi-select file boxes when we enter a panel
 *
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2006/12/28 10:34:21  goldin
 * Complete implementation of multifile selection control and file chooser
 *
 * Revision 1.1  2006/12/25 10:48:37  goldin
 * Begin implementation of multi-select file control
 *
 *
 */

package com.grs.gui;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;

/** Control that allows user to select multiple file names
*   
* @author  goldin
*/
public class DMultiFileField extends DFileField 
           implements ActionListener, ListSelectionListener
    {

      /**
       * inputField, innerPanel and outerPanel are declared in the
       * parent DTextField class.
       */
      //protected JTextField inputField;
      //protected JPanel innerPanel = null;
      //protected JPanel outerPanel = null;

      /* BrowseButton is declared in the DFileField class */
      //protected BrowseButton browseBtn;

    protected JPanel inputPanel = null;
    protected JList selectedFileList = null;
    protected JScrollPane fileScroller = null;

    /* buttons to control the list contents*/
    protected JButton addBtn = null;
    protected JButton removeBtn = null;
    protected JButton upBtn = null;
    protected JButton downBtn = null;

    /* Keep track of the current files in the control */
    ArrayList<String> currentListContents = null;

    /* Maximum number of files allowed */
    /* This can be set externally, and is passed to the file chooser */
    protected int maxAllowedFileCount = 12;

    protected String lastBadFileName = null;      

    //********************************************************************
      /**
       * Constructor creates the UI including
       * the input field, the list, and the browse button.
       * Also sets whether the file must previously exist.
       * @param name  Name for new field
       * @param text  Text for label; if null, no label created
       * @param columns Number of columns to display for the text field.
       * @param mustExist If true, the file entered must exist.
       */
    public DMultiFileField(String name, String text, int columns,
		      boolean mustExist, boolean isPathData)
        {
	super(name,text,columns,mustExist,isPathData);
	bFileField = true;
        currentListContents = new ArrayList<String>();
        String addString = 
	    ApplicationManager.getTextSource().getI18NText("%h2B0.0.0","ADD");
        String removeString = 
	    ApplicationManager.getTextSource().getI18NText("%f7401.2","REM");
        String upString = 
	    ApplicationManager.getTextSource().getI18NText("%f7401.3","UP");
        String downString = 
	    ApplicationManager.getTextSource().getI18NText("%f7401.4","DOWN");
	setLayout(new BorderLayout());
	inputPanel = new JPanel(new BorderLayout());
	innerPanel = new JPanel(new BorderLayout());
	outerPanel = new JPanel(new BorderLayout());
	if (text != null)
	    {
	    label = new JLabel(text);
	    innerPanel.add(label,BorderLayout.NORTH);
	    }

        if (bPathData)
	    {
	    if (columns == 0)
	        actualWidth = pathDisplayWidth;
	    else
	        actualWidth = columns;
	    }
	else
	    {
	    actualWidth = displayWidth;
	    }
	inputField = new JTextField(actualWidth);
        inputField.setDocument(new FixedLengthDocument(maxInputChars));
	inputField.addFocusListener(this);
	inputField.addKeyListener(this);
	inputField.addActionListener(this); 
               /* add to list when user hits return*/
	browseBtn = new BrowseButton();
	Dimension fldDim = inputField.getPreferredSize();
	Dimension btnDim = new Dimension(fldDim.height,fldDim.height);
	browseBtn.setPreferredSize(btnDim);
	browseBtn.addActionListener(this);
	browseBtn.addKeyListener(this);
        //addBtn = new JButton(new ImageIcon("add.gif"));
        //addBtn.setToolTipText(addString);
        //addBtn = new JButton(addString);
        //addBtn.addActionListener(this);        
	//addBtn.setPreferredSize(btnDim);
        //removeBtn = new JButton(new ImageIcon("remove.gif"));
        //removeBtn.setToolTipText(removeString);        
        removeBtn = new JButton(removeString);
        removeBtn.addActionListener(this);
	//removeBtn.setPreferredSize(btnDim);
        //upBtn = new JButton(new ImageIcon("moveUp.gif"));
        upBtn = new JButton(upString);
        upBtn.addActionListener(this);     
        //upBtn.setToolTipText(upString);   
	//upBtn.setPreferredSize(btnDim);
        //downBtn = new JButton(new ImageIcon("moveDown.gif"));
        downBtn = new JButton(downString);
        downBtn.addActionListener(this);
        //downBtn.setToolTipText(downString); 
	//downBtn.setPreferredSize(btnDim);
        disableAllButtons();
        JPanel buttonPanel = new JPanel(new GridLayout(0,1));
        buttonPanel.setBorder(new EmptyBorder(10,10,0,0));
        //buttonPanel.add(addBtn);        
        buttonPanel.add(removeBtn);        
        buttonPanel.add(upBtn);        
        buttonPanel.add(downBtn);        
        JPanel outerButtonPanel = new JPanel(new BorderLayout());
        outerButtonPanel.add(buttonPanel,BorderLayout.NORTH);
        selectedFileList = new JList();
        selectedFileList.setVisibleRowCount(5);
        selectedFileList.addListSelectionListener(this);
        fileScroller = new JScrollPane(selectedFileList); 
	JPanel innerInputPanel = new JPanel(new BorderLayout());
        innerInputPanel.setBorder(new EmptyBorder(0,0,0,5)); 
	innerInputPanel.add(inputField,BorderLayout.NORTH);
	inputPanel.add(innerInputPanel,BorderLayout.CENTER);
	inputPanel.add(browseBtn,BorderLayout.EAST);
	innerPanel.add(inputPanel,BorderLayout.SOUTH);
	outerPanel.add(innerPanel,BorderLayout.NORTH);
        outerPanel.add(fileScroller,BorderLayout.CENTER); 
	outerPanel.add(outerButtonPanel,BorderLayout.EAST);
	add(outerPanel,BorderLayout.WEST);
	if (xlatedCurrent == null)
	    xlatedCurrent = ApplicationManager.getTextSource().getI18NText(
					   TextKeys.CURRENT,"(Current)");
	}

    //********************************************************************
      /**
       * Create and return copy of the present object. Data items
       * that are set during the addition to a panel are not 
       * copied.
       */
    public DragonField makeClone()
        {
	DMultiFileField clone = new DMultiFileField(name,label.getText(),
					  actualWidth, bExisting,bPathData);
	initializeClone(clone);
        clone.setMaxInputChars(maxInputChars);
        clone.setFileTypes(fileTypes);
	clone.setAllowedMemoryFiles(allowedMemoryFiles);
	clone.setOverwriteWarning(bOverwriteWarning);
	return (DragonField) clone;
	}

    //********************************************************************
      /** Sets the field to be enabled or disabled depending
       *   on the value of the bEnabled argument.
       *   
       * @param  bEnabled Enablement flag
       */
    public void setEnabled(boolean bEnabled) 
        {
	super.setEnabled(bEnabled);
	browseBtn.setEnabled(bEnabled);
        }

      /** Calculates the minimum amount of space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum width of graphical components, in pixels.
       */
    public int calculateWidth()
        {
	int labelWidth = 0;
	int controlWidth = 0;
	if (label != null)
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    labelWidth = metrics.stringWidth(label.getText());
	    }
	controlWidth = inputField.getPreferredSize().width;
	controlWidth += browseBtn.getPreferredSize().width + 5;
	// a bit of extra space for padding between input and button
	return Math.max(labelWidth,controlWidth);
	}

      /** Calculates the minimum amount of vertical space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum height of graphical components, in pixels.
       */
    public int calculateHeight()
        {
	int controlHeight = 0;
        int listHeight = 0;
	int btnHeight = 0;
	int labelHeight = 0;
	if (label != null)
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    labelHeight = metrics.getHeight() + 
		metrics.getMaxDescent();
	    }
	FontMetrics controlMetrics = 
	   inputField.getFontMetrics(inputField.getFont());
	controlHeight = controlMetrics.getHeight() +
	                controlMetrics.getMaxDescent();
	btnHeight = browseBtn.getPreferredSize().height;
        listHeight = fileScroller.getPreferredSize().height;
        return listHeight+ labelHeight + 
                  (Math.max(controlHeight,btnHeight)) + 4;
	}

      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public boolean equivalent(DragonField field)
        {
	if (!(field instanceof DMultiFileField))
	    return false;
	if (!commonFieldsEqual(field))
	    return false;
	DMultiFileField fField = (DMultiFileField) field;
	String[] otherAllowed = fField.getAllowedMemoryFiles();
	if ((otherAllowed == null) && (allowedMemoryFiles != null))
	    return false;
	if ((otherAllowed != null) && (allowedMemoryFiles == null))
	    return false;
	if ((otherAllowed != null) && 
	    (allowedMemoryFiles != null))
	    {
	    if (otherAllowed.length != 
		allowedMemoryFiles.length)
	    return false;
	    for (int i = 0; i < allowedMemoryFiles.length; i++)
	        {
		if (fField.getAllowedMemoryFiles(i).compareTo(allowedMemoryFiles[i])
		    != 0)
		  return false;
	        }
	    }
	if (fField.isExisting() != bExisting)
	    return false;
	if (fField.getDisplayWidth() != displayWidth)
	    return false;
	return true;
	}


    //********************************************************************

    public void focusLost(FocusEvent fe)
        {
	super.focusLost(fe);
	processNewFileEntry();
	}

      /**
       * Method from list selection listener. Used to
       * enable and disable buttons.
       */
    public void valueChanged(ListSelectionEvent lse)
	{
	checkButtonEnabling();
	}

      /**
       * Method from the actionListener interface. Called when the
       * browse button is clicked or the user hits return in the
       * inputField.
       */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
        if (source.equals(inputField))
            processNewFileEntry();
        else if (source.equals(browseBtn))
            {
            invokeFileChooser();
            inputField.setText("");  /* clear pattern after choosing */
            }
        else if (source.equals(removeBtn))
            removeFileEntry();
        else if (source.equals(upBtn))
            moveFileEntry(-1);
        else if (source.equals(downBtn))
            moveFileEntry(1);
        checkButtonEnabling();
        }

	/**
	 * Add, remove, up and down buttons
	 * should all be disabled initially
	 */
    public void disableAllButtons()
	{
	    //addBtn.setEnabled(false);
	removeBtn.setEnabled(false);
	upBtn.setEnabled(false);
	downBtn.setEnabled(false);
	}


	/**
	 * Enable or disable up, down and
         * remove buttons depending on
	 * whether the list has items in
	 * it and whether an item is selected.
	 */
    protected void checkButtonEnabling()
	{
        int index = -1;
	boolean bEnable = true;
	if (currentListContents.size() == 0)
            {
	    bEnable = false;
            }
        else
            { 
            index = selectedFileList.getSelectedIndex();
	    if (index == -1)
                bEnable = false;
	    }
	removeBtn.setEnabled(bEnable);
	upBtn.setEnabled(bEnable);
	downBtn.setEnabled(bEnable);
        if (index == 0)
            upBtn.setEnabled(false);
	if ((index > 0) && 
            (index == currentListContents.size() -1))
	    downBtn.setEnabled(false);
	}
    
       /**
	* Update the JList to show the current
	* contents of the passed array.
	* @param list   List of filename strings
	*/
    protected void setFileListContents(ArrayList list)
        { 
	String contents[] = new String[list.size()];
        for (int i = 0; i < list.size(); i++)
            {
	    contents[i] = "B" + String.valueOf(i+1) + 
		":  " +  (String) list.get(i);       
            }  
        selectedFileList.setListData(contents);
        }

       /**
	* Check to see if a filename is already in
	* the list of current filenames that the
	* user has added to the control.
	* @param filename  Filename to check
	* @return True if found, false if not
	*/
    protected boolean inCurrentList(String filename)
	{
	boolean bFound = false;
        for (int i=0; i< currentListContents.size() && !bFound; i++)
	    {
	    String compareString = (String) currentListContents.get(i);
	    if (filename.compareToIgnoreCase(compareString) == 0)
		bFound = true;
	    }
	return bFound;
	}

       /**
	* Factorization of action performed.
	* Called when the user hits return in the
        * inputField.
	*/
    protected void processNewFileEntry()
	{
	String filename = getTextFieldValue();
        if (filename.length() > 0)
	    { 
	    /* check for existence */
	    File tempFile = new File(filename);
	    boolean bOk = selectChooser().getModel().validateFile(tempFile.getParent(),
								  tempFile.getName(),
								  true,false,false);
	    if (!bOk)
	       { 
	       if ((lastBadFileName == null) || 
                   (filename.compareTo(lastBadFileName) != 0))
                   {
		   lastBadFileName = filename;
	           inputField.requestFocus();
		   }
	       } 
	    else if (currentListContents.size() >= maxAllowedFileCount)
               {
	       lastBadFileName = null;
	       MessageDisplay mDisplay = ApplicationManager.getMessageDisplay();
	       String title = ApplicationManager.getTextSource().getI18NText(
					  TextKeys.WARNING,"Warning");
	       String msg = ApplicationManager.getTextSource().getI18NText(
					  "%m10000.2","Too many files");
	       mDisplay.showWarning(title,msg);
               }
	    else
	       {
	       if (!inCurrentList(filename))
		   {
                   currentListContents.add(filename);
	           setFileListContents(currentListContents);
	           }
	       inputField.setText("");
	       inputField.requestFocus();
	       }
	    }
	//addBtn.setEnabled(false);
        }

	/** 
	 * Factorizaton of actionPerformed. If 
         * an element in the list is selected,
         * we remove it from the list.
	 */
    protected void removeFileEntry()
        {
	int index = selectedFileList.getSelectedIndex();
        if (index >= 0)
	    {
	    currentListContents.remove(index);
	    setFileListContents(currentListContents);
	    }
        } 

	/** 
	 * Factorizaton of actionPerformed. If 
         * an element in the list is selected,
         * we move it either up or down in the list.
         * @param direction If -1, we move 
         *                  the entry up, if +1
         *                  we move it down.
	 */
    protected void moveFileEntry(int direction)
        {
	int index = selectedFileList.getSelectedIndex();
        if (((index > 0) && (direction < 0)) ||
            ((index < currentListContents.size() - 1) && (direction > 0))) 
	    {
            String moveItem = (String) currentListContents.get(index);
            String swapItem = 
                   (String) currentListContents.get(index+direction);
            currentListContents.set(index + direction,moveItem);
            currentListContents.set(index,swapItem);
	    setFileListContents(currentListContents);
            selectedFileList.setSelectedIndex(index+direction);
	    }
        } 


       /**
	* Factorization of action performed.
	* Called when the browse button is clicked.
	*/
    protected void invokeFileChooser()
	{
        int option;
	DragonFileChooser chooser;
        bInChoiceDialog = true;
	String partial  = inputField.getText();
        partial = partial.trim();
	if ((partial.length() == 0)||
            (partial.startsWith("=")) ||
	    (partial.startsWith("(")))
	    partial = null;
	if (bPathData)
	    partial = null;

        if  ((partial != null) &&
             ((partial.startsWith("\\")) || 
              (partial.startsWith("/"))) &&
             (System.getProperty("os.name").startsWith("Win")))
	    {
            String currentDir = System.getProperty("user.dir");
	    partial = currentDir.substring(0,2) +
	                  partial;
	    }
	chooser = selectChooser();
        if (chooser == null)
	    return;
        String currentMemoryFiles[] = null;
        if (memoryFilter != null)
                currentMemoryFiles = memoryFilter.filterAllowedMemoryFiles(
						  allowedMemoryFiles,
						  fileTypes[0]);
        String[] filesNow = 
            (String[]) currentListContents.toArray(new String[] {});
	File[] selected = chooser.chooseMultiFiles(
                                           fileTypes,currentMemoryFiles,
					   partial,labelText,defaultValue,
					   maxAllowedFileCount,filesNow);
	if ((selected != null) && (selected.length > 0))
	    {
	    currentListContents.clear();
            for (int i= 0; i < selected.length; i++)
               {
  	       String simpleFilename = selected[i].getName();
	       if ((simpleFilename.startsWith("(")) ||
		   (simpleFilename.startsWith("=")))
	           currentListContents.add(simpleFilename);
               else
	           currentListContents.add(selected[i].getAbsolutePath());
               }  
	    setFileListContents(currentListContents);
	    }

        inputField.requestFocus();
	bInChoiceDialog = false;
	}

      /**
       * Factorization: returns correct DragonFileChooser based on
       * characteristics of the field.
       */
    public DragonFileChooser selectChooser()
        {
	DragonFileChooser chooser = null;
	if ((bExisting) && (!bPathData))
  	    {
	    chooser = ApplicationManager.getMultiInFileChooser();
	    }
	else if (bPathData)
	    {
	    chooser = ApplicationManager.getPathChooser();
	    }
	else
	    {
	    chooser = ApplicationManager.getOutFileChooser();
	    }
	return chooser;
	}


      /**
       * Method to clear the field - if this is relevant.
       * Most control types use the base class method, which
       * does nothing.
       */
    public void clearField()
        {
	selectedFileList.setListData(new Object[] {});
	inputField.setText("");
	currentListContents.clear();
        DragonFileChooser chooser = selectChooser();
        chooser.clear();
	disableAllButtons();
	}

  
    //********************************************************************
      /**
       * Override addMouseListener to add to all the subcontrols
       * as well.
       */
    public void addMouseListener(MouseListener listener)
        {
	super.addMouseListener(listener);
	inputField.addMouseListener(listener);
	inputField.putClientProperty(DragonField.PARENT_FIELD,this);
	innerPanel.addMouseListener(listener);
	innerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	outerPanel.addMouseListener(listener);
	outerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	inputPanel.addMouseListener(listener);
	inputPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	browseBtn.addMouseListener(listener);
	browseBtn.putClientProperty(DragonField.PARENT_FIELD,this);
        selectedFileList.addMouseListener(listener);
	selectedFileList.putClientProperty(DragonField.PARENT_FIELD,this);
	}
      /**
       * Override addKeyListener to add to all the subcontrols
       * as well.
       */
    public void addKeyListener(KeyListener listener)
        {
	inputField.addKeyListener(listener);
	innerPanel.addKeyListener(listener);
	outerPanel.addKeyListener(listener);
	inputPanel.addKeyListener(listener);
	browseBtn.addKeyListener(listener);
        selectedFileList.addKeyListener(listener);
	}

     /** Function that allows us to get the
      * current contents of the text field and
      * add path, suffix, etc.
      */
    public String getTextFieldValue()
        {
	return super.getFieldValue();
        }

      /**
       * Return a string with concatenated pspecifiers plus
       * all the filenames in the list.
       * @return Concatenated string. Returns empty string if 
       *         there are no items in the list.
       */
    public String getMultiFieldValue()
        {
	String result = "";
        if (currentListContents.size() > 0)
	    { 
            StringBuffer buffer = new StringBuffer();
            for (int i = 0; i < currentListContents.size(); i++)
                {
		if (i > 0)
                   buffer.append("\n ");
		buffer.append(getPSpecifier() + String.valueOf(i+1) + " ");
		buffer.append("\"" +  (String) currentListContents.get(i) + 
                                       "\"" + " ");
                }
	    result = buffer.toString();
	    }
	return result;
	}

      /**
       * Method to show choices or choice dialog. Overridden by
       * so that it displays the file browsing window.
       */
    public void showChoices()
        {
	bInChoiceDialog = true;
        browseBtn.doClick();
	}



    //********************************************************************
      /** * Get/Set Methods
       */
    public String[] getAllowedMemoryFiles() 
        {
        return allowedMemoryFiles;
        }
    
    public String getAllowedMemoryFiles(int index) 
        {
        return allowedMemoryFiles[index];
        }
    
    public void setAllowedMemoryFiles(String[] allowedMemoryFiles) 
        {
        this.allowedMemoryFiles = allowedMemoryFiles;
        }
    
    public void setAllowedMemoryFiles(int index, String allowedMemoryFiles) 
        {
        this.allowedMemoryFiles[index] = allowedMemoryFiles;
        }
    
    public boolean isExisting() 
        {
        return bExisting;
        }
    
    public void setExisting(boolean bExisting) 
        {
        this.bExisting = bExisting;
        }

    public boolean getOverwriteWarning() 
        {
        return bOverwriteWarning;
        }
    
    public void setOverwriteWarning(boolean bFlag) 
        {
        this.bOverwriteWarning = bFlag;
        }

    public boolean isPathData() 
        {
        return bPathData;
        }
    
    public void setPathData(boolean bPathData) 
        {
        this.bPathData = bPathData;
        }

    public DFileType[] getFileTypes() 
        {
        return fileTypes;
        }
      

      /**
       * To ease conversion - get the first element in the
       * filetypes array.
       */
    public DFileType getFileType() 
        {
        return fileTypes[0];
        }
    
    public void setFileTypes(DFileType[] types) 
        {
	if (types != null)
            this.fileTypes = types;
	else
	    {
	    this.fileTypes = FILETYPE_ALL_ARRAY;
	    }
	}
    
    public void setMemoryFilter(MemoryFilter filter)
        {
	memoryFilter = filter;
	}

      /**
       * Override setFileField to be a null method.
       * This subclass is always a file field.
       */
    public void setFileField(boolean bFlag)
        {
	}

    public int getMaxInputChars()
        {
	return maxInputChars;
	}

    public void setMaxInputChars(int maxChars)
        {
        maxInputChars = maxChars;
	FixedLengthDocument doc = 
            (FixedLengthDocument) inputField.getDocument();
	doc.setMaxLength(maxInputChars);
	}

    public int getActualWidth()
        {
        return actualWidth;
	}

    public void setActualWidth(int newWidth)
        {
	actualWidth = newWidth;
	inputField.setColumns(actualWidth);
	setSize(calculateWidth(),calculateHeight());
	}

    public int getCurrentFileCount()
        {
	return currentListContents.size(); 
	}

    public void setMaxAllowedFileCount(int count)
	{
	maxAllowedFileCount = count;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DMultiFileField.java,v 1.5.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    } 

// End of DMultiFileField.java
