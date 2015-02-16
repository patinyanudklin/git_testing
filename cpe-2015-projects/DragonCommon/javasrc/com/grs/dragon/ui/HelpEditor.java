/**
 *  HelpEditor
 *
 *  Copyright  2001-2007  Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 2/8/2001
 *
 *  $Id: HelpEditor.java,v 1.10 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: HelpEditor.java,v $
 *  Revision 1.10  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.9  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.8  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.7  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.6  2001/04/09 11:33:26  goldin
 *  Make it possible to turn help editing on and off via properties file
 *
 *  Revision 1.5  2001/04/05 14:59:48  goldin
 *  Fix help editor bug:
 *
 *  Revision 1.4  2001/04/03 17:46:43  goldin
 *  Continued work on FileChooser; moved state information into new DFileChooserModel class
 *
 *  Revision 1.3  2001/03/20 13:32:04  goldin
 *  Add help editing and viewing for menu items
 *
 *  Revision 1.2  2001/02/28 16:24:29  goldin
 *  implementing defaults, enhancements to help editor
 *
 *  Revision 1.1  2001/02/08 16:14:39  goldin
 *  Added HelpEditor capability
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import java.io.*;

/**
 * This class implements a facility for displaying help/choice/label
 * keys and, if requested, editing the associated text.
 * It is used as a utility associated with DRAGON, for maintaining
 * help files.*/
public class HelpEditor extends JFrame implements ActionListener,
                                                  ItemListener,
                                                  UndoableEditListener
    {

    protected boolean bInternalEvent = false;

      /**
       * Current panel ID
       */
    protected String currentPanel = null;
    
      /**
       * Current control whose help we are displaying.*/
    protected DragonField currentField = null;

      /**
       * OR Current menu item whose help we are displaying.*/
    protected DragonMenuItem currentItem = null;

      /**
       * Help keys for current control
       */
    protected String[] helpKeys = null;

      /**
       * Choice keys for current control
       */
    protected String[] choiceKeys = null;


      /**
       * Area for displaying and editing help text.
       */
    protected JTextArea helpEditArea = null;

      /**
       * Button for displaying label key
       */
    protected JButton labelKeyButton = null;

      /**
       * Combo box for help keys
       */
    protected JComboBox helpKeyCombo = null;

      /**
       * Combo box for choice keys
       */
    protected JComboBox choiceKeyCombo = null;

      /**
       * Button for invoking save
       */
    protected JButton saveButton = null;

      /**
       * Reference to DRAGON UI */
    protected DragonUI parentUI = null;

      /**
       * Reference to the help file text source.*/
    protected I18NTextSource txtSource = null;

      /**
       * File name to use for saving changes.
       */
    protected String helpChangeFile = "helpChanges.txt";

      /**
       * Writer for writing out lines to the 
       * save file.
       */
    protected BufferedWriter writer = null;

      /**
       * Keep track of last key, so we
       * don't go to the text source unnecessarily
       */
    protected String lastKey = null;

    protected static final String TITLE = "DRAGON Help Editor";
    protected final String[] dfltHelp = {"<help>"};
    protected final String[] dfltChoices = {"<choices>"};


    //************************************************************
      /**
       * Constructor creates the basic user interface,
       * creates the output file.
       */
    public HelpEditor(DragonUI parentUI)
        {
	super(TITLE);
	this.parentUI = parentUI;
	txtSource = parentUI.getTextSource();


        JPanel mainPanel = new JPanel(new BorderLayout());
	JPanel topPanel = new JPanel(new GridLayout(0,3,5,5));
	// Add the first row of labels
	topPanel.add(new JLabel("Label"));
	topPanel.add(new JLabel("HelpMsgs"));
	topPanel.add(new JLabel("Choices"));

	labelKeyButton = new JButton("<label>");
	labelKeyButton.addActionListener(this);
	topPanel.add(labelKeyButton);

	helpKeyCombo = new JComboBox(dfltHelp);
	helpKeyCombo.addItemListener(this);
	topPanel.add(helpKeyCombo);

	choiceKeyCombo = new JComboBox(dfltChoices);
	choiceKeyCombo.addItemListener(this);
	topPanel.add(choiceKeyCombo);

	mainPanel.add(topPanel,BorderLayout.NORTH);
       
	JPanel editPanel = new JPanel(new BorderLayout());
	helpEditArea = new JTextArea(10,60);
	helpEditArea.setLineWrap(true);
	helpEditArea.setWrapStyleWord(true);
	helpEditArea.getDocument().addUndoableEditListener(this);
	editPanel.add(new JScrollPane(helpEditArea),BorderLayout.CENTER);
	mainPanel.add(editPanel,BorderLayout.CENTER);

	JPanel buttonPanel = new JPanel(new GridBagLayout());
	saveButton = new JButton("Save Text");
	saveButton.addActionListener(this);
	saveButton.setEnabled(false);
	buttonPanel.add(saveButton);
	mainPanel.add(buttonPanel,BorderLayout.SOUTH);
	getContentPane().add(mainPanel);
	pack();

	try 
	    {
	    // append to existing file if it exists
	    writer = new BufferedWriter(new FileWriter(helpChangeFile,true));
	    }
	catch (IOException ioe)
	    {
	    System.out.println("ERROR opening help change file " +
			       helpChangeFile);
	    ioe.printStackTrace();
	    saveButton.setEnabled(false);
	    }
	}

      /**
       * Clear all controls and combo boxes
       */
    protected void clearControls()
        {
        labelKeyButton.setText("<label>");
	int count = helpKeyCombo.getItemCount();
	for (int i = count-1; i >= 0; i--)
	    {
	    helpKeyCombo.removeItemAt(i);
	    }
	count = choiceKeyCombo.getItemCount();
	for (int i = count-1; i >= 0; i--)
	    {
	    choiceKeyCombo.removeItemAt(i);
	    }
	helpEditArea.setText("");
	lastKey = null;
	}


      /**
       * Populate all controls and combo boxes
       * based on the current control.
       */
    protected void populateControls()
        {
	if (currentField != null)
	    {
            helpKeys = currentField.getHelpKeys();
	    choiceKeys = currentField.getChoiceKeys();
	    labelKeyButton.setText(currentField.getLabelKey());
	    labelKeyButton.setEnabled(true);
	    }
	else if (currentItem != null)
	    {
            helpKeys = currentItem.getHelpKeys();
	    choiceKeys = null;
	    labelKeyButton.setEnabled(false);
	    }
	else 
            return;
	int count = 0;
	if (helpKeys != null)
	    count = helpKeys.length;
	// if helpKeys is null, we won't execute the loop
	for (int i = 0; i < count; i++)
	    {
	    helpKeyCombo.addItem(helpKeys[i]);
	    }
	if (count == 0)
	    helpKeyCombo.setEnabled(false);
	else 
	    helpKeyCombo.setEnabled(true);
	count = 0;
	if (choiceKeys != null)
	    count = choiceKeys.length;
	// similarly, if choiceKeys is null, we won't execute the loop
	for (int i = 0; i < count; i++)
	    {
	    choiceKeyCombo.addItem(choiceKeys[i]);
	    }
	if (count == 0)
	    choiceKeyCombo.setEnabled(false);
	else 
	    choiceKeyCombo.setEnabled(true);
	helpKeyCombo.setSelectedIndex(-1);
	choiceKeyCombo.setSelectedIndex(-1);
	}


      /**
       * Set the current control. This will populate the
       * combo boxes etc.
       */
    public void setCurrentField(DragonField ctrl)
        {
        currentItem = null;
	currentField = ctrl;
	clearControls();
	populateControls();
	saveButton.setEnabled(false);
	setTitle(TITLE + " -- " + currentPanel + ":" + currentField.getName());
	}

      /**
       * Set the menu item. This will populate the
       * combo boxes etc.
       */
    public void setCurrentItem(DragonMenuItem item)
        {
        currentItem = item;
	currentField = null;
	clearControls();
	populateControls();
	saveButton.setEnabled(false);
	setTitle(TITLE + " -- " + currentPanel + ":" + currentItem.getName());
	}

      /**
       * Method from action listener interface. Responds to
       * button presses.
       */
    public void actionPerformed(ActionEvent e)
        {
	if ((currentField == null) && (currentItem == null)) 
 	    return;
	String message = null;
	Object source = e.getSource();
      
	if (source == labelKeyButton)
	    {
            if (currentField == null)
	        return;
	    bInternalEvent = true;
	    helpKeyCombo.setSelectedIndex(-1);
	    choiceKeyCombo.setSelectedIndex(-1);
	    bInternalEvent = false;
	    if (lastKey != currentField.getLabelKey())
	        {
		lastKey = currentField.getLabelKey();
		message = txtSource.getI18NText(lastKey,"dummy");
		if (message != null)
		    {
		    helpEditArea.setText(message);
		    helpEditArea.repaint();
		    }
		saveButton.setEnabled(false);
		}
	    }
	else if (source == saveButton)
	    {
	    String name;
            if (currentField != null)
	        {
		name = currentField.getName();
		}
	    else
	        {
		name = currentItem.getName();
		}
	    String msg = new String(lastKey + " " + helpEditArea.getText());
	    try 
	        {
		String comment = 
		   new String("# " + currentPanel + " " + name);
		writer.write(comment,0,comment.length());
		writer.newLine();
		writer.write(msg,0,msg.length());
		writer.newLine();
		writer.flush();
		saveButton.setEnabled(false);
		}
	    catch (IOException ioe)
	        {
		System.out.println("Error writing to help change file.");
		ioe.printStackTrace();
		}
	    }
	}


      /**
       * Method from item listener interface. Responds to
       * selections on combo box.
       */
    public void itemStateChanged(ItemEvent e)
        {
	if ( ((currentField == null) && (currentItem == null)) 
                  || (bInternalEvent))
	    return;
	String message = null;
	if (e.getStateChange() == ItemEvent.SELECTED)
	     {
	     Object source = e.getSource();
	     if (source == helpKeyCombo)
	         {
		 int index = helpKeyCombo.getSelectedIndex();
		 if (lastKey != helpKeys[index])
		     {
		     message = txtSource.getI18NText(helpKeys[index],"dummy");
		     lastKey = helpKeys[index];
		     }
		 bInternalEvent = true;
		 choiceKeyCombo.setSelectedIndex(-1);
		 bInternalEvent = false;
		 }
	     else if (source == choiceKeyCombo)
	         {
		 int index = choiceKeyCombo.getSelectedIndex();
		 if (lastKey != choiceKeys[index])
		     {
		     message = txtSource.getI18NText(choiceKeys[index],
						      "dummy");
		     lastKey = choiceKeys[index];
		     }
		 bInternalEvent = true;
		 helpKeyCombo.setSelectedIndex(-1);
		 bInternalEvent = false;

		 }
	     if (message != null)
	         {
	         helpEditArea.setText(message);
		 helpEditArea.repaint();
		 }
	     saveButton.setEnabled(false);
	     }
	else if (e.getStateChange() == ItemEvent.DESELECTED)
	     {
	     lastKey = null;
	     helpEditArea.setText("");
	     saveButton.setEnabled(false);
	     }
	}

      /**
       * Method from UndoableEditListener.
       */
    public void undoableEditHappened(UndoableEditEvent e)
        {
	saveButton.setEnabled(true);
	}

      /**
       * Set the panel ID
       */
    public void setCurrentPanel(String panelID)
        {
	currentPanel = panelID;
	}

      /**
       * Enable or disable editing the help.
       */
    public void setEditable(boolean bFlag)
        {
        helpEditArea.setEditable(bFlag);
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: HelpEditor.java,v 1.10 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
   }




