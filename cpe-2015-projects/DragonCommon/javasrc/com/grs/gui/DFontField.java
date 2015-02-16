/* DFontField.java
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 4/12/2001
 *
 * $Id: DFontField.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DFontField.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.2  2002/01/09 14:47:05  goldin
 * Get rid of blue text
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.6  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.5  2001/10/30 18:06:36  goldin
 * Revamped to be view only control
 *
 * Revision 1.4  2001/04/25 10:51:02  goldin
 * Add function key handling
 *
 * Revision 1.3  2001/04/24 14:14:20  goldin
 * Improve behavior and appearance of file and font choosers
 *
 * Revision 1.2  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/04/12 14:10:10  goldin
 * Add control for selecting fonts
 *
 */


package com.grs.gui;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/** 
* Control that allows user to enter/select fonts
* As of 10/30/01, this is no longer a subclass of DTextField, because
* we don't want users typing in the font, only selecting
*/
public class DFontField extends DragonField 
                        implements ActionListener,FocusListener
    {
    
      /**
       * Button to invoke the font dialog.
       */
    protected BrowseButton browseBtn;

      /**
       * innerPanel and outerPanel are declared in the
       * parent DTextField class.
       */
    protected JPanel innerPanel = null;
    protected JPanel outerPanel = null;
    protected JPanel inputPanel = null;
    protected JTextField faceField = null;
    protected JTextField styleField = null;
    protected JTextField sizeField = null;

    protected boolean bTransparent = false;

    //********************************************************************
      /**
       * Constructor creates the UI including
       * the input field and the browse button.
       * @param name  Name for new field
       * @param text  Text for label; if null, no label created
       */
    public DFontField(String name, String text)
        {
        this.labelText = text;
        this.name = name;
	setLayout(new BorderLayout());
	inputPanel = new JPanel(new BorderLayout());
	innerPanel = new JPanel(new BorderLayout());
	outerPanel = new JPanel(new BorderLayout());
	if (text != null)
	    {
	    label = new JLabel(text);
	    innerPanel.add(label,BorderLayout.NORTH);
	    }
	faceField = new JTextField(DragonFontChooser.DFLT_FACE,20);
	styleField = new JTextField(DragonFontChooser.DFLT_STYLE,10);
	sizeField = new JTextField(DragonFontChooser.DFLT_SIZE,5);
        faceField.setEditable(false);
        styleField.setEditable(false);
        sizeField.setEditable(false);
	faceField.addKeyListener(this);
	styleField.addKeyListener(this);
	sizeField.addKeyListener(this);
	faceField.addFocusListener(this);
	styleField.addFocusListener(this);
	sizeField.addFocusListener(this);
	browseBtn = new BrowseButton();
	Dimension fldDim = faceField.getPreferredSize();
	Dimension btnDim = new Dimension(fldDim.height,fldDim.height);
	browseBtn.setPreferredSize(btnDim);
	browseBtn.addActionListener(this);
	browseBtn.addKeyListener(this);
	JPanel innerInputPanel = new JPanel(new BorderLayout(5,0));
	innerInputPanel.add(faceField,BorderLayout.WEST);
	innerInputPanel.add(styleField,BorderLayout.CENTER);
	innerInputPanel.add(sizeField,BorderLayout.EAST);
	inputPanel.add(innerInputPanel,BorderLayout.CENTER);
	inputPanel.add(browseBtn,BorderLayout.EAST);
	innerPanel.add(inputPanel,BorderLayout.SOUTH);
	outerPanel.add(innerPanel,BorderLayout.NORTH);
	add(outerPanel,BorderLayout.WEST);
	}

    //********************************************************************
      /**
       * Create and return copy of the present object. Data items
       * that are set during the addition to a panel are not 
       * copied.
       */
    public DragonField makeClone()
        {
	DFontField clone = new DFontField(name,label.getText());
	initializeClone(clone);
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
	controlWidth = faceField.getPreferredSize().width;
	controlWidth += styleField.getPreferredSize().width + 5;
	controlWidth += sizeField.getPreferredSize().width + 5;
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
	int btnHeight = 0;
	int labelHeight = 0;
	if (label != null)
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    labelHeight = metrics.getHeight() + 
		metrics.getMaxDescent();
	    }
	FontMetrics controlMetrics = 
	    faceField.getFontMetrics(faceField.getFont());
	controlHeight = controlMetrics.getHeight() +
	                controlMetrics.getMaxDescent();
	btnHeight = browseBtn.getPreferredSize().height;
        return labelHeight + (Math.max(controlHeight,btnHeight)) + 4;
	}

      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public boolean equivalent(DragonField field)
        {
	if (!(field instanceof DFontField))
	    return false;
	if (!commonFieldsEqual(field))
	    return false;
	return true;
	}

      /**
       * Method to show choices or choice dialog. Overridden by
       * so that it displays the font browsing window.
       */
    public void showChoices()
        {
        browseBtn.doClick();
	}

    //********************************************************************
      /**
       * Method from the actionListener interface. Called when the
       * browse button is clicked.
       */
    public void actionPerformed(ActionEvent e)
        {
        int option;
 	DragonFontChooser chooser = 
          ApplicationManager.getFontChooser();
        if (chooser == null)
	    return;
	String selectedFont = chooser.chooseFont(labelText);
	if (selectedFont != null)
	   setFieldValue(selectedFont);
	}

    //********************************************************************
      /**
       * Override addMouseListener to add to all the subcontrols
       * as well.
       */
    public void addMouseListener(MouseListener listener)
        {
	super.addMouseListener(listener);
	faceField.addMouseListener(listener);
	faceField.putClientProperty(DragonField.PARENT_FIELD,this);
	styleField.addMouseListener(listener);
	styleField.putClientProperty(DragonField.PARENT_FIELD,this);
	sizeField.addMouseListener(listener);
	sizeField.putClientProperty(DragonField.PARENT_FIELD,this);
	innerPanel.addMouseListener(listener);
	innerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	outerPanel.addMouseListener(listener);
	outerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	inputPanel.addMouseListener(listener);
	inputPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	browseBtn.addMouseListener(listener);
	browseBtn.putClientProperty(DragonField.PARENT_FIELD,this);
	}

      /**
       * Override addKeyListener to add to all the subcontrols
       * as well.
       */
    public void addKeyListener(KeyListener listener)
        {
	faceField.addKeyListener(listener);
	styleField.addKeyListener(listener);
	sizeField.addKeyListener(listener);
	innerPanel.addKeyListener(listener);
	outerPanel.addKeyListener(listener);
	inputPanel.addKeyListener(listener);
	browseBtn.addKeyListener(listener);
	}

      /** Tries to set the focus to the control associated
       *  with the field. Since each field subclass has different
       *  controls, this method must be implemented for each one.
       */
    public void requestFocus()
        {
	browseBtn.requestFocus();
	}


    //********************************************************************
      /**
       * Methods from FocusListener interface, responds to gain or
       * loss of focus.
       */
    public void focusLost(FocusEvent e)
        {
	  // do nothing
	}

    public void focusGained(FocusEvent e)
        {
	browseBtn.requestFocus();
	}

    //********************************************************************

      /** * Get/Set Methods
       */
    
    /**
     * Set label values based on passed string, which should
     * be of the form FACE-STYLE-SIZE
     */
    public void setFieldValue(String selectedFont)
        {
        int p1 = -1;
        int p2 = -1;
        int p3 = -1;
        p1 = selectedFont.indexOf("-");
        if (p1 >= 0)
            p2 = selectedFont.indexOf("-",p1+1);
        if (p2 >= 0)
	    p3 = selectedFont.indexOf("-",p2+1);
        if ((p1 < 0) || (p2 < 0))
            return;
        faceField.setText(selectedFont.substring(0,p1));
        styleField.setText(selectedFont.substring(p1+1,p2));
        if (p3 > 0)
	    {
            sizeField.setText(selectedFont.substring(p2+1,p3));
            if (selectedFont.substring(p3+1).equals("Transparent"))
                bTransparent = true;
            else 
	        bTransparent = false;
	    }
	else
	    {
            sizeField.setText(selectedFont.substring(p2+1));
	    bTransparent = false;
	    }
	}

     /**
      * Return the last set value.
      */
    public String getFieldValue()
        {
        StringBuffer buffer = new StringBuffer(256);
	buffer.append(faceField.getText()+"--");
        String style = styleField.getText();
	if (style.equals("Bold"))
            buffer.append("B--");
	else if (style.equals("Italic"))
            buffer.append("I--");
        else if (style.equals("Plain"))
            buffer.append("--");
	else
            buffer.append("BI--");
	String size = sizeField.getText();
	buffer.append(size + "--" + size);
        if (bTransparent)
             buffer.append("--Transparent");
	return buffer.toString();
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DFontField.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of DFontField.java

