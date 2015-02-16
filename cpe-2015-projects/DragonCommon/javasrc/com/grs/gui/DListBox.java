/** 
 * DListBox.java
 *
 *    Control to manage a list of things. The control provides Add, Remove,
 *    Up and Down buttons. 
 *
 *	~~ Copyright 2007-2014  Global Software Institute
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
 * $Id: DListBox.java,v 1.4.2.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: DListBox.java,v $
 * Revision 1.4.2.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.5  2007/07/20 03:53:35  goldin
 * Get rid of unchecked operation warnings by parameterizing collections
 *
 * Revision 1.4  2007/02/23 08:36:29  goldin
 * Clear rule list when you re-enter the operation
 *
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2007/01/02 05:19:19  goldin
 * Complete behavioral code for Rule Creation panel
 *
 * Revision 1.1  2007/01/01 13:52:16  goldin
 * Add and integrate new controls for rule creation screen
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
import java.util.*;

/** Control that allows user to select multiple file names
*   
* @author  goldin
*/
public class DListBox extends DragonField 
           implements ActionListener, ListSelectionListener
    {
     /* callback that performs the add operation. This
      * will vary with different controls 
      */
    protected Callback addCallback = null; 

    protected JPanel innerPanel = null;
    protected JPanel outerPanel = null;
    protected JList selectedItemList = null;
    protected JScrollPane itemScroller = null;

    /* buttons to control the list contents*/
    protected JButton addBtn = null;
    protected JButton removeBtn = null;
    protected JButton upBtn = null;
    protected JButton downBtn = null;

    /* Keep track of the current files in the control */
    ArrayList<String> currentListContents = null;

    /* Maximum number of list items allowed */
    /* This can be set externally */
    protected int maxAllowedListCount = 12;
      

    //********************************************************************
      /**
       * Constructor creates the UI including
       * the list and the buttons.
       * @param name  Name for new field
       * @param text  Text for label; if null, no label created
       */
    public DListBox(String name, String text)
        {
	this.name = name;
	this.labelText = text;    
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
        JPanel innerInputPanel = new JPanel(new BorderLayout()); 
	innerPanel = new JPanel(new BorderLayout());
	outerPanel = new JPanel(new BorderLayout());
	if (text != null)
	    {
	    label = new JLabel(text);
	    innerPanel.add(label,BorderLayout.NORTH);
	    }
        addBtn = new JButton(addString);
        addBtn.addActionListener(this);        
        removeBtn = new JButton(removeString);
        removeBtn.addActionListener(this);
        upBtn = new JButton(upString);
        upBtn.addActionListener(this);     
        downBtn = new JButton(downString);
        downBtn.addActionListener(this);
        checkButtonEnabling();
        JPanel buttonPanel = new JPanel(new GridLayout(0,1));
        buttonPanel.setBorder(new EmptyBorder(10,10,0,0));
        buttonPanel.add(addBtn);        
        buttonPanel.add(removeBtn);        
        buttonPanel.add(upBtn);        
        buttonPanel.add(downBtn);        
        JPanel outerButtonPanel = new JPanel(new BorderLayout());
        outerButtonPanel.add(buttonPanel,BorderLayout.NORTH);
        selectedItemList = new JList();
        selectedItemList.setVisibleRowCount(5);
        selectedItemList.addListSelectionListener(this);
        itemScroller = new JScrollPane(selectedItemList); 
	outerPanel.add(innerPanel,BorderLayout.NORTH);
        outerPanel.add(itemScroller,BorderLayout.CENTER); 
	outerPanel.add(outerButtonPanel,BorderLayout.EAST);
	add(outerPanel,BorderLayout.CENTER);
	}

    //********************************************************************
      /**
       * Create and return copy of the present object. Data items
       * that are set during the addition to a panel are not 
       * copied.
       */
    public DragonField makeClone()
        {
	DListBox clone = new DListBox(name,label.getText());
	initializeClone(clone);
        clone.setMaxAllowedListCount(maxAllowedListCount);
        clone.setAddCallback(addCallback);
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
	selectedItemList.setEnabled(bEnabled);
	checkButtonEnabling();
        }


      /** Tries to set the focus to the control associated
       *  with the field. Since each field subclass has different
       *  controls, this method must be implemented for each one.
       */
    public void requestFocus()
        {
	addBtn.requestFocus();
        }

      /** Calculates the minimum amount of space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum width of graphical components, in pixels.
       */
    public int calculateWidth()
        {
	int controlWidth = 0;
	FontMetrics metrics = selectedItemList.getFontMetrics(label.getFont());
	controlWidth = metrics.stringWidth("W")* 50; 
	controlWidth += addBtn.getPreferredSize().width + 20;
	return controlWidth;
	}

      /** Calculates the minimum amount of vertical space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum height of graphical components, in pixels.
       */
    public int calculateHeight()
        {
        int listHeight = 0;
	int labelHeight = 0;
	if (label != null)
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    labelHeight = metrics.getHeight() + 
		metrics.getMaxDescent();
	    }
        listHeight = selectedItemList.getVisibleRowCount() * labelHeight;
        return listHeight+ labelHeight + 20;
	}

      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public boolean equivalent(DragonField field)
        {
	if (!(field instanceof DListBox))
	    return false;
	if (!commonFieldsEqual(field))
	    return false;
	DListBox fField = (DListBox) field;
        if (fField.getMaxAllowedListCount() != maxAllowedListCount)
	    return false;
        if (fField.getAddCallback() != addCallback)
	    return false;
	return true;
	}


    //********************************************************************

    public void focusLost(FocusEvent fe)
        {
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
       * Method from the actionListener interface. Called when any
       * button is clicked.
       */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
        if (source.equals(addBtn))
            { 
	    if (currentListContents.size() >= maxAllowedListCount)
               {
	       MessageDisplay mDisplay = ApplicationManager.getMessageDisplay();
	       String title = ApplicationManager.getTextSource().getI18NText(
					  TextKeys.WARNING,"Warning");
	       String msg = ApplicationManager.getTextSource().getI18NText(
					  "%m10000.4","Too many items");
	       mDisplay.showWarning(title,msg);
               }
	    else
	       {
	       addCallback.executeCallback(this);
	       }
	    }
        else if (source.equals(removeBtn))
            removeEntry();
        else if (source.equals(upBtn))
            moveEntry(-1);
        else if (source.equals(downBtn))
            moveEntry(1);
        checkButtonEnabling();
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
	addBtn.setEnabled(true);
	if (currentListContents.size() == 0)
            {
	    bEnable = false;
            }
        else
            { 
            index = selectedItemList.getSelectedIndex();
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
    protected void setItemListContents(ArrayList<String> list)
        { 
	String contents[] = (String[]) (list.toArray(new String[] {}));
        selectedItemList.setListData(contents);
        }

       /**
	* Check to see if the exact same item is already in
	* the list of items that the
	* user has added to the control.
	* @param item  Item to check
	* @return True if found, false if not
	*/
    protected boolean inCurrentList(String item)
	{
	boolean bFound = false;
        for (int i=0; i< currentListContents.size() && !bFound; i++)
	    {
	    String compareString = (String) currentListContents.get(i);
	    if (item.compareToIgnoreCase(compareString) == 0)
		bFound = true;
	    }
	return bFound;
	}

	/** 
	 * Add an item to the list box.
	 * Normally this will be called by the addCallback.
	 * @param entry  Item to be added
	 */
    public void addEntry(String entry)
        { 
	if (!inCurrentList(entry))
	    {
	    currentListContents.add(entry);
	    setItemListContents(currentListContents);
	    }
	}

	/** 
	 * Factorizaton of actionPerformed. If 
         * an element in the list is selected,
         * we remove it from the list.
	 */
    protected void removeEntry()
        {
	int index = selectedItemList.getSelectedIndex();
        if (index >= 0)
	    {
	    currentListContents.remove(index);
	    setItemListContents(currentListContents);
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
    protected void moveEntry(int direction)
        {
	int index = selectedItemList.getSelectedIndex();
        if (((index > 0) && (direction < 0)) ||
            ((index < currentListContents.size() - 1) && (direction > 0))) 
	    {
            String moveItem = (String) currentListContents.get(index);
            String swapItem = 
                   (String) currentListContents.get(index+direction);
            currentListContents.set(index + direction,moveItem);
            currentListContents.set(index,swapItem);
	    setItemListContents(currentListContents);
            selectedItemList.setSelectedIndex(index+direction);
	    }
        } 



      /**
       * Method to clear the field - if this is relevant.
       * Most control types use the base class method, which
       * does nothing.
       */
    public void clearField()
        {
	selectedItemList.setListData(new Object[] {});
	currentListContents.clear();
	checkButtonEnabling();
	}

  
    //********************************************************************
      /**
       * Override addMouseListener to add to all the subcontrols
       * as well.
       */
    public void addMouseListener(MouseListener listener)
        {
	super.addMouseListener(listener);
	innerPanel.addMouseListener(listener);
	innerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	outerPanel.addMouseListener(listener);
	outerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	addBtn.addMouseListener(listener);
	addBtn.putClientProperty(DragonField.PARENT_FIELD,this);
	removeBtn.addMouseListener(listener);
	removeBtn.putClientProperty(DragonField.PARENT_FIELD,this);
	upBtn.addMouseListener(listener);
	upBtn.putClientProperty(DragonField.PARENT_FIELD,this);
	downBtn.addMouseListener(listener);
	downBtn.putClientProperty(DragonField.PARENT_FIELD,this);
        selectedItemList.addMouseListener(listener);
	selectedItemList.putClientProperty(DragonField.PARENT_FIELD,this);
	}
      /**
       * Override addKeyListener to add to all the subcontrols
       * as well.
       */
    public void addKeyListener(KeyListener listener)
        {
	innerPanel.addKeyListener(listener);
	outerPanel.addKeyListener(listener);
        selectedItemList.addKeyListener(listener);
	}

     /** 
      * Set the field value from a string; break up the
      * the string according to newlines, and make each
      * line an item.
      * @param newVal  String to parse.
      */
     public void setFieldValue(String newVal)
        {
	StringTokenizer tokenizer = new StringTokenizer(newVal,"\n");
        currentListContents.clear();
        while (tokenizer.hasMoreTokens())
           {
	   String next = tokenizer.nextToken();
	   if (next.length() > 0)
               currentListContents.add(next);
           }
        setItemListContents(currentListContents);
        checkButtonEnabling();
        }

 
     /** Function that allows us to get the
      * current contents of the list, with newlines
      * between each item.
      * @return concatenated list items, or an empty string
      */
    public String getFieldValue()
        {
	String result = "";
        if (currentListContents.size() > 0)
	    { 
            StringBuffer buffer = new StringBuffer();
            for (int i = 0; i < currentListContents.size(); i++)
                {
		if (i > 0)
                   buffer.append("\n");
		buffer.append((String) currentListContents.get(i));
                }
	    result = buffer.toString();
	    }
	return result;
	}

    //********************************************************************
      /** * Get/Set Methods
       */

    public void setMaxAllowedListCount(int count)
	{
	maxAllowedListCount = count;
	}

    public int getMaxAllowedListCount()
	{
	return maxAllowedListCount;
	}

    public void setAddCallback(Callback callback)
	{
	addCallback = callback;
	}

    public Callback getAddCallback()
	{
	return addCallback;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DListBox.java,v 1.4.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    } 

// End of DListBox.java
