/* DComboField.java
 *
 * Generated by java-pp.pl from DComboField.java
 * on Mon Jan  8 11:41:00 EST 2001

 * Copyright  2001-2007 Sally Goldin & Kurt Rudahl
 *
 * $Id: DComboField.java,v 1.11 2007/02/03 09:29:05 goldin Exp $
 * $Log: DComboField.java,v $
 * Revision 1.11  2007/02/03 09:29:05  goldin
 * Remove messages about controls being too large
 *
 * Revision 1.10  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.9  2006/12/25 03:30:29  goldin
 * Add debugging msgs
 *
 * Revision 1.8  2006/11/20 11:14:14  goldin
 * Don't exec callback on focus lost, only on selection
 *
 * Revision 1.7  2006/11/18 10:51:16  goldin
 * Call callback when item selected
 *
 * Revision 1.6  2005/12/08 09:36:01  goldin
 * Have blank data for unit. combo box
 *
 * Revision 1.5  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.4  2002/09/23 23:00:38  goldin
 * Make beep part of error display  rather than a reaction in the control
 *
 * Revision 1.3  2002/01/22 14:55:42  goldin
 * Don't return focus to field after validation error
 *
 * Revision 1.2  2002/01/10 18:17:37  goldin
 * Change sizing strategy for variable combo fields
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.19  2001/11/29 16:00:00  goldin
 * Invoke validator etc on focus off not on item selected
 *
 * Revision 1.18  2001/11/05 13:59:14  goldin
 * Put UI code in a package
 *
 * Revision 1.17  2001/07/06 16:52:15  goldin
 * Make arrow keys work like tabs for combos
 *
 * Revision 1.16  2001/06/04 11:11:45  goldin
 * Fix bug causing some combos to be empty
 *
 * Revision 1.15  2001/05/09 15:16:40  goldin
 * Begin implementing signature populaing callbacks for C/EDI
 *
 * Revision 1.14  2001/04/25 12:18:32  goldin
 * Fix bug wrt border redraw; set focus to first control
 *
 * Revision 1.13  2001/04/25 10:51:02  goldin
 * Add function key handling
 *
 * Revision 1.12  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.11  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.10  2001/03/03 19:56:58  goldin
 * Fine tuning screen layout and appearance
 *
 * Revision 1.9  2001/03/02 19:56:21  goldin
 * Add horizontal label option for DTextFields, add handling of translated help msgs
 *
 * Revision 1.8  2001/01/29 15:19:32  goldin
 * Continued work on UI
 *
 * Revision 1.7  2001/01/19 18:43:19  goldin
 * Add handling of xlateText, menu building
 *
 * Revision 1.6  2001/01/17 14:18:23  goldin
 * Actually build initial trial panel from XML document
 *
 * Revision 1.5  2001/01/16 17:50:30  goldin
 * Began implemenation of XML parsing to create UI
 *
 * Revision 1.4  2001/01/15 14:20:25  goldin
 * Implement new layout options, makeClone methods
 *
 * Revision 1.3  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 * Revision 1.2  2001/01/09 15:58:55  goldin
 * continued work implementing basic appearance of UI components
 *
 * Revision 1.1  2001/01/08 19:34:42  goldin
 * Initial population for new DRAGON-Java UI
 *
 */

//********************************************************************

package com.grs.gui;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/** DragonField that provides a combo-box control to allow
*   the user to choose one of a fixed number of choices.
*   
* @author  goldin
* @version  Mon Jan 08 11:36:01 EST 2001*/
public class DComboField extends DragonField
                       implements FocusListener, ItemListener
    {
        
    /** If true, the set of choices for this combo box is fixed.
    *   If false, the set of choices must be initialized based on
    *   context, normally by the callback of some other field.
    */
    protected boolean bFixed = true;
    
      /**
       * If true, the combo box should be laid out with its
       * label on the same line, to the left, rather than above.
       */
    protected boolean bHorizontal = false;

      /**
       * If non-zero,maximum width of element that will be shown
       * in the combo box.
       */
    protected int maxWidth = 0;

    /** Reference to the combo box which holds the visible
    *   items that are shown to the user.
    *   
    */
    protected JComboBox comboControl;
    
    /** Array of strings that should be returned as the value
    *   of the control, always in English.
    */
    protected String[] valueStrings = null;

    JPanel innerPanel = null;
    JPanel outerPanel = null;

    //*******************************************************************
      /**
       * Constructor. Creates the combo box and label, initializes
       * choiceStrings and valueStrings if appropriate
       * @param name Name of the field
       * @param text Text for label. May be null.
       * @param values Non-translated set of possible values. May be null.
       * @param translatedValues Translated set of possible values. 
       *                         May be null.
       */
    public DComboField(String name, String text, String[] values,
		       String[] translatedValues, boolean bHorizontal)
        {
	bChoiceControl = true;
	this.bHorizontal = bHorizontal;
	this.labelText = text;
	String[] displayStrings = new String[]{"                       "};
 	this.name = name;
	setLayout(new BorderLayout());
	innerPanel = new JPanel(new BorderLayout(5,0));
	outerPanel = new JPanel(new BorderLayout());
	if (text != null)
	    {
	    label = new JLabel(text);
	    if (bHorizontal)
	        innerPanel.add(label,BorderLayout.WEST);
	    else
	        innerPanel.add(label,BorderLayout.NORTH);
	    }
	comboControl = new JComboBox();
	comboControl.addFocusListener(this);
	comboControl.addKeyListener(this);
	comboControl.addItemListener(this);
        if (bHorizontal)
	    innerPanel.add(comboControl,BorderLayout.EAST);
	else
	    innerPanel.add(comboControl,BorderLayout.SOUTH);
	outerPanel.add(innerPanel,BorderLayout.NORTH);
	add(outerPanel,BorderLayout.WEST);
	if (values != null)
	    {
	    valueStrings = values;
	    // if no translated strings supplied, use these
	    displayStrings = valueStrings;
	    }
	if (translatedValues != null)
	    {
	    choiceStrings = translatedValues;
	    // if translated strings supplied, display those instead
	    displayStrings = choiceStrings;
	    }
        if (displayStrings != null)
	    {
	    for (int i = 0; i < displayStrings.length; i++)
	        {
	        comboControl.addItem(displayStrings[i]);
	        }
	    }
	bRequired = true;  // must always have one choice selected
	bMultiLine = true;
	}


    //********************************************************************
      /**
       * Create and return copy of the present object. Data items
       * that are set during the addition to a panel are not 
       * copied.
       */
    public DragonField makeClone()
        {
	DComboField clone = new DComboField(name,label.getText(),
					    valueStrings,
					    choiceStrings,
					    bHorizontal);
	initializeClone(clone);
	clone.setMaxWidth(maxWidth);
	return (DragonField) clone;
	}

      /**
       * Clear the combo box - only for varCombos.
       */
    public void clear()
        {
        int count = comboControl.getItemCount();
	for (int i = 0; i < count; i++)
	    {
	    comboControl.removeItemAt(0);
	    }
	}

      /**
       * Reset the combo box choices after a change to choice
       * strings has been made.
       */
    protected void reInit()
        {
	clear();
	for (int i = 0; i < choiceStrings.length; i++)
	    {
	    comboControl.addItem(choiceStrings[i]);
	    }
	}

    //********************************************************************
      /** Tries to set the focus to the control associated
       *  with the field. Since each field subclass has different
       *  controls, this method must be implemented for each one.
       */
    public void requestFocus()
        {
	comboControl.requestFocus();
	}

      /**
       * For a fixed combo, deselect. For a var combo, actually
       * remove combo elements.
       */
    public void clearField()
        {
	if (bFixed)
	    comboControl.setSelectedIndex(-1);
	else
	    clear();
	}
    
    //********************************************************************
      /** Returns the current value for the field. Must be overridden
       *   by each subclass.
       */
    public String getFieldValue() 
        {
	String returnString = null;
	int index = comboControl.getSelectedIndex();
	if (index >= 0) 
	    {
	    if (valueStrings != null)
	       {
	       returnString = valueStrings[index];
	       }
	    else 
	       {
	       returnString = (String) comboControl.getSelectedItem();
	       }
	    }
	return returnString;
        }

    //********************************************************************
      /** Sets the field to be enabled or disabled depending
       *   on the value of the bEnabled argument.
       *   
       * @param  bEnabled Enablement flag
       */
    public void setEnabled(boolean bEnabled) 
        {
	this.bEnabled = bEnabled;
	if (label != null)
	    {
	    label.setEnabled(bEnabled);
	    }
	comboControl.setEnabled(bEnabled);
        }
     
    //********************************************************************
      /** Allows the panel or other outside class to set the value of the
       *   field. Must be overridden in each subclass,
       * @param  value String to use to set value of the control.
       *   This may need to be transformed to
       *   an index or some other form.
       *   In the case of this type of field, the string is assumed to
       *   match one of the valueString elements (untranslated elements)
       *   UNLESS those are null.
       */
    public void setFieldValue(String value) 
        {
	int index = -1;
	if (valueStrings == null)
	    {
	    comboControl.setSelectedItem(value);
	    }
	else
	    {
	    for (int i = 0; (i < valueStrings.length) && (index < 0); i++)
	        {
		if (value.compareTo(valueStrings[i]) == 0)
		    index = i;
		}
	    comboControl.setSelectedIndex(index);
	    }
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
        int resultWidth = 0;
	StringBuffer buf = new StringBuffer();
	if (maxWidth > 0)
	    {
	    for (int i = 0; i < maxWidth; i++) 
	        buf.append("W");
	    comboControl.addItem(buf.toString());
            }			       
	if (label != null)
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    labelWidth = metrics.stringWidth(label.getText());
	    }
	controlWidth = comboControl.getPreferredSize().width;
	if (maxWidth > 0)
	    {
	    comboControl.removeItem(buf.toString());
	    }
	if (bHorizontal)
	    resultWidth = labelWidth + controlWidth + 5;
	else
	    resultWidth =  Math.max(labelWidth,controlWidth);
        /***
        if (resultWidth > 1000)
            {
            System.out.println("Calculated width is too big: labelWidth is " +
              labelWidth + " and controlWidth is " + controlWidth);
            System.out.println("  resultWidth is " +
              resultWidth + " and bHorizontal is " + bHorizontal);
	    }
	***/
	return resultWidth;
	}

      /** Calculates the minimum amount of vertical space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum height of graphical components, in pixels.
       */
    public int calculateHeight()
        {
	int controlHeight = 0;
	int labelHeight = 0;
	if ((label != null) && (!bHorizontal))
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    labelHeight = metrics.getHeight() + 
		metrics.getMaxDescent();
	    }
	controlHeight = comboControl.getPreferredSize().height;
        return labelHeight + controlHeight + 5;
	}
    
      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public boolean equivalent(DragonField field)
        {
	if (!(field instanceof DComboField))
	    return false;
	if (!commonFieldsEqual(field))
	    return false;
	DComboField cField = (DComboField) field;
	if (cField.getChoiceStrings().length != choiceStrings.length)
	    return false;
	for (int i = 0; i < choiceStrings.length; i++)
	     {
	     if (cField.getValueStrings(i).compareTo(valueStrings[i]) != 0)
	         return false;
	     if (cField.getChoiceStrings(i).compareTo(choiceStrings[i]) != 0)
	         return false;
	     }
	if (cField.isFixed() != bFixed)
	    return false;
	if (cField.isHorizontal() != bHorizontal)
	    return false;
	return true;
	}


      /**
       * Method to show choices or choice dialog. Overridden so that
       * it pops up the set of alternative items.
       */
    public void showChoices()
        {
        comboControl.showPopup(); 
	}

      /**
       * Returns info on whether choices are visible.
       */
    public boolean isPopupVisible()
        {
	return comboControl.isPopupVisible();
	}

    //********************************************************************
      /**
       * Method from the FocusListener interface.
       */
    public void focusLost(FocusEvent e)
        {
        if (comboControl.isPopupVisible())
	    return;
	if (validator != null)
	    {
	    if (!validator.isValid(this))
	        {
		return;
		}
	    }
        /** execute the callback on selection only - not on focus lost
	if (callback != null)
	    {
	    callback.executeCallback(this);
	    }
	**/
	previousValue = getFieldValue();
	}

    public void focusGained(FocusEvent e)
        {
	}

    //*******************************************************************
    /* Method from ItemListener interface */
    public void itemStateChanged(ItemEvent ie)
        {
	/* call the callback when selected, not just when focus is lost. */
	if (ie.getStateChange() == ItemEvent.SELECTED)
            {
	    if (callback != null)
	       {
	       callback.executeCallback(this);
	       }
            } 
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
	comboControl.addMouseListener(listener);
	comboControl.putClientProperty(DragonField.PARENT_FIELD,this);
	}
      /**
       * Override addKeyListener to add to all the subcontrols
       * as well.
       */
    public void addKeyListener(KeyListener listener)
        {
	innerPanel.addKeyListener(listener);
	outerPanel.addKeyListener(listener);
	comboControl.addKeyListener(listener);
	}

    //********************************************************************
      /** * Get/Set Methods
       */
    public JComboBox getComboControl() 
        {
        return comboControl;
        }
    
    public boolean isFixed() 
        {
        return bFixed;
        }

    public boolean isHorizontal() 
        {
        return bHorizontal;
        }
    
    public void setFixed(boolean bFixed) 
        {
        this.bFixed = bFixed;
        }
    
    public String[] getValueStrings() 
        {
        return valueStrings;
        }
    
    public String getValueStrings(int index) 
        {
        return valueStrings[index];
        }
    
    public void setValueStrings(String[] valueStrings) 
        {
        this.valueStrings = valueStrings;
        }

    public void setMaxWidth(int cols)
        {
	maxWidth = cols;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DComboField.java,v 1.11 2007/02/03 09:29:05 goldin Exp $ \n";
	}
    }

// End of DComboField.java

