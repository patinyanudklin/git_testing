/** 
 * DRangeControl.java
 *
 *    Control to allow specification of two values that indicate a range
 *
 *	Copyright 2007  Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri
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
 * $Id: DRangeControl.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DRangeControl.java,v $
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
import java.util.ArrayList;

/** Control that allows user to specify a range of two integers
*   It has the form of two text fields, with a text string in
*   between.
* @author  goldin
*/
public class DRangeControl extends DragonField implements FocusListener
{
    boolean bInteger = true;

    /* fields for min and max */
    protected JTextField minField = null;
    protected JTextField maxField = null;
    
    protected JPanel innerPanel = null;

      /** Width in character columns for the text field.
       */
    protected int columns = 8;
    
    protected int displayWidth = 0;

    /**
     * Constructor for range control. 
     * @param name   Name of the control instance
     * @param text   Text to display between the lower and
     *               upper bounds. Could be null.
     */
    public DRangeControl(String name, String text, 
			 int displayWidth, boolean bInteger)
       {
       this.name = name;
       this.labelText = text;
       this.bInteger = bInteger;
       this.displayWidth = displayWidth;
       innerPanel = new JPanel(new BorderLayout());
       setLayout(new BorderLayout());
       setBorder(new EmptyBorder(5,5,10,5));
       if (displayWidth <= 0)
	    displayWidth = columns;
       minField = new JTextField(displayWidth);
       //minField.addFocusListener(this);
       minField.addKeyListener(this);
       JPanel minPanel = new JPanel(new FlowLayout());
       //minPanel.setBorder(new EmptyBorder(0,0,0,5));
       minPanel.add(minField);
       innerPanel.add(minPanel,BorderLayout.WEST);
       JPanel textPanel = new JPanel(new FlowLayout());
       if (labelText != null)
	   {
	   textPanel.setBorder(new EmptyBorder(5,0,5,0));
	   label = new JLabel(labelText);
           textPanel.add(label);      
           innerPanel.add(textPanel,BorderLayout.CENTER);
           }
       maxField = new JTextField(displayWidth);
       maxField.addFocusListener(this);
       maxField.addKeyListener(this);
       JPanel maxPanel = new JPanel(new FlowLayout());
       //maxPanel.setBorder(new EmptyBorder(0,5,0,0));
       maxPanel.add(maxField);
       innerPanel.add(maxPanel,BorderLayout.EAST);
       add(innerPanel,BorderLayout.WEST);
       }

      /**
       * Create and return copy of the present object. Data items
       * that are set during the addition to a panel are not 
       * copied.
       */
    public DragonField makeClone()
        {
	DRangeControl clone = new DRangeControl(name,labelText,
						displayWidth,bInteger);
	initializeClone(clone);
	return (DragonField) clone;
	}


    //********************************************************************
      /** Tries to set the focus to the control associated
       *  with the field. Since each field subclass has different
       *  controls, this method must be implemented for each one.
       */
    public void requestFocus()
        {
	minField.requestFocus();
        }


    //********************************************************************
      /** Returns the current value for the field. Must be overridden
       *   by each subclass.
       */
    public String getFieldValue()
        {
	StringBuffer buffer = new StringBuffer();
	buffer.append(minField.getText());
	buffer.append("-");
	buffer.append(maxField.getText());
	return buffer.toString();
	}
    

    //********************************************************************
      /** Sets the field to be enabled or disabled depending
       *   on the value of the bEnabled argument.
       *   
       * @param  bEnabled Enablement flag
       */
    public void setEnabled(boolean bEnabled)
       {
       minField.setEnabled(bEnabled);
       maxField.setEnabled(bEnabled);
       }
    
    //********************************************************************
      /** Allows the panel or other outside class to set the value of the
       *   field. Must be overridden in each subclass,
       * @param  value String to use to set value of the control.
       *               This should have the form "min-max"
       */
    public void setFieldValue(String value)
       {
       int pos = value.indexOf("-");
       if (pos < 0) /** illegal value */
	   throw new RuntimeException("Illegal value " + value +
				      " passed to DRangeControl.setFieldValue");
       minField.setText(value.substring(0,pos));
       maxField.setText(value.substring(pos+1));
       } 
    
    //********************************************************************
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
       FontMetrics metrics2 = minField.getFontMetrics(minField.getFont());
       controlWidth = metrics2.stringWidth("W");
       controlWidth = displayWidth * 2 * controlWidth + 10;
       return labelWidth + controlWidth + 20;
       }

      /** Calculates the minimum amount of vertical space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum height of graphical components, in pixels.
       */
    public int calculateHeight()
       { 
       int labelHeight = 0;
       if (label != null)
	   {
	   FontMetrics metrics = label.getFontMetrics(label.getFont());
	   labelHeight = metrics.getHeight() + 
		   metrics.getMaxDescent();
	   }
       return labelHeight + 20;
       }

      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public boolean equivalent(DragonField field)
       {
       if (!(field instanceof DRangeControl))
	   return false;
       if (!commonFieldsEqual(field))
	   return false;
       DRangeControl tField = (DRangeControl) field;
       if (tField.getDisplayWidth() != displayWidth)
	   return false;
       if (tField.isInteger() != bInteger)
	   return false;
       return true;
       }


    /* return true if this field holds integer ranges.
     * return false if it holds real numbers or something else 
     */
    boolean isInteger()
       {
       return bInteger;
       }


    /**
     * Method to clear the field - if this is relevant.
     * Most control types use the base class method, which
     * does nothing, but here, we override it.
     */
    public void clearField()
       {
       minField.setText("");
       maxField.setText("");
       previousValue=null;
       setUserData(null);
       }

    //********************************************************************
      /**
       * Methods from FocusListener interface, responds to gain or
       * loss of focus.
       */
    public void focusLost(FocusEvent e)
        {
        boolean bDialogVisible = false;
	DragonPanel parent = getTopLevelPanel();
        if (parent != null)
	    {
	    bDialogVisible = ApplicationManager.isMessageDialogVisible();
	    }
        if (!parent.isVisible())
	    {
            clearField();
	    return;  // don't call validator if cancelled.
	    }
	if ((previousValue != null) && 
            (getFieldValue() != null) &&
            (getFieldValue().equals(previousValue)))
	    {
	    return;
	    }  // only do one focuslost validation for a particular value
	// we do not want to call the validator if there is already
	// an error box up (in this case, the focus off was probably
	// generated by the appearance and focus grab of the modal
	// error dialog).
	if ((validator != null) && (!bDialogVisible)) 
	    {
	    if (!validator.isValid(this))
	        {
		javax.swing.Timer timer = new javax.swing.Timer(200,
					  new FocusRequestor(minField,
							     false));
		timer.setRepeats(false);
		timer.start();
		previousValue = getFieldValue();
		return;
		}
	    }
	if (callback != null)
	    {
	    callback.executeCallback(this);
	    }
	previousValue = getFieldValue();
	setFieldValue(previousValue);
	}

    public void focusGained(FocusEvent e)
        {
	// put cursor at the end of any current text
	minField.setCaretPosition(minField.getText().length());
	}


    //********************************************************************
      /**
       * Override addMouseListener to add to all the subcontrols
       * as well.
       */
    public void addMouseListener(MouseListener listener)
        {
	super.addMouseListener(listener);
	minField.addMouseListener(listener);
	minField.putClientProperty(DragonField.PARENT_FIELD,this);
	innerPanel.addMouseListener(listener);
	innerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	maxField.addMouseListener(listener);
	maxField.putClientProperty(DragonField.PARENT_FIELD,this);
	}

      /**
       * Override addKeyListener to add to all the subcontrols
       * as well.
       */
    public void addKeyListener(KeyListener listener)
        {
	minField.addKeyListener(listener);
	minField.putClientProperty(DragonField.PARENT_FIELD,this);
	innerPanel.addKeyListener(listener);
	innerPanel.putClientProperty(DragonField.PARENT_FIELD,this);
	maxField.addKeyListener(listener);
	maxField.putClientProperty(DragonField.PARENT_FIELD,this);
	}
      
    //********************************************************************
      /** * Get/Set Methods
       */
    public JTextField getMinField() 
        {
        return minField;
        }

    public JTextField getMaxField() 
        {
        return maxField;
        }
    
    public int getDisplayWidth() 
        {
        return displayWidth;
        }

    
    public void setDisplayWidth(int displayWidth) 
        {
        this.displayWidth = displayWidth;
	minField.setColumns(displayWidth);
	maxField.setColumns(displayWidth);
        }
    
      /**
       * Method which will create a focus requestor for
       * a field. This is intended to be be called from callback classes.
       * @param delay  How long to wait before transferring focus.
       */
    public void createFocusRequestor(int delay)
         {
	 javax.swing.Timer timer = new javax.swing.Timer(delay,
		  new FocusRequestor(this.minField,true));
	 timer.setRepeats(false);
	 timer.start();
	 }
 

      //*****************************************************
      /** 
       * Inner class used to issue a delayed focus request when
       * a validation triggered by focusLost fails.*/
    class FocusRequestor implements ActionListener
         {
	 JTextField myField;
	 boolean bReturnFocus = false;

	 /**
	  * Constructor sets myField
	  */
	 public FocusRequestor(JTextField whichField,
			       boolean bReturnFocus)
             {
	     myField = whichField;
	     this.bReturnFocus = bReturnFocus;
	     }

	 /**
	  * Action Listener method
	  */
	 public void actionPerformed(ActionEvent e)
             {
	     if ((validator != null) &&
		 (!getTopLevelPanel().isValidatingAll()) &&
		 (validator.isErrorOutstanding()))
	          {
	          validator.displayLastError();
                  }
	     if (bReturnFocus)
	          {
	          myField.requestFocus();
		  }
	     }
         }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DRangeControl.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

