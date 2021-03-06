
/* DragonField.java
 *
 * Generated by java-pp.pl from DragonField.java
 * on Mon Jan  8 11:41:21 EST 2001

 * Copyright 2001 by Sally Goldin & Kurt Rudahl
 *
 * $Id: DragonField.java,v 1.8.2.1 2010/09/10 10:00:32 rudahl Exp $
 * $Log: DragonField.java,v $
 * Revision 1.8.2.1  2010/09/10 10:00:32  rudahl
 * Fix for java 1.6
 *
 * Revision 1.8  2007/02/17 10:20:57  goldin
 * Make F1 cause a focus loss so that callbacks will execute
 *
 * Revision 1.7  2006/12/28 10:34:21  goldin
 * Complete implementation of multifile selection control and file chooser
 *
 * Revision 1.6  2006/12/10 06:26:59  goldin
 * Fine tune help behavior - cancel if the user starts typing or brings up a file chooser
 *
 * Revision 1.5  2006/02/16 06:05:57  goldin
 * Fix new problem with hitting CR in the command line
 *
 * Revision 1.4  2006/01/14 09:23:55  goldin
 * Fix keyboard navigation problems
 *
 * Revision 1.3  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.2  2002/03/22 23:53:11  goldin
 * Add new key equivs for some fn keys
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.28  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.27  2001/09/05 10:44:57  goldin
 * Add history recall to cmd line
 *
 * Revision 1.26  2001/08/28 11:36:55  goldin
 * Make fn keys work even when no panel visible
 *
 * Revision 1.25  2001/07/06 16:52:15  goldin
 * Make arrow keys work like tabs for combos
 *
 * Revision 1.24  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.23  2001/05/30 15:32:53  goldin
 * Work on getting fn keys to work in file dialog, main window w/ no RP
 *
 * Revision 1.22  2001/05/22 12:05:13  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 * Revision 1.21  2001/04/27 11:29:00  goldin
 * Continue implementation of interprocess communication and command handling
 *
 * Revision 1.20  2001/04/26 12:24:23  goldin
 * further work on command line functionality
 *
 * Revision 1.19  2001/04/25 15:36:50  goldin
 * began implementation of command line
 *
 * Revision 1.18  2001/04/25 10:51:02  goldin
 * Add function key handling
 *
 * Revision 1.17  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.16  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.15  2001/03/20 13:33:02  goldin
 * Disable all fields after OK
 *
 * Revision 1.14  2001/03/16 19:23:46  goldin
 * Added fixed length option for DTextField and DFileField; added callbacks to menu items
 *
 * Revision 1.13  2001/03/14 16:39:50  goldin
 * Added parentComponent
 *
 * Revision 1.12  2001/02/28 16:24:29  goldin
 * implementing defaults, enhancements to help editor
 *
 * Revision 1.11  2001/02/20 18:39:13  goldin
 * Add callback handling
 *
 * Revision 1.10  2001/02/08 16:14:39  goldin
 * Added HelpEditor capability
 *
 * Revision 1.9  2001/01/29 15:19:32  goldin
 * Continued work on UI
 *
 * Revision 1.8  2001/01/22 16:14:26  goldin
 * Changes to parse actual generated XML file
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

package com.grs.gui;
import java.util.Date;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/** This is the abstract base class for all controls that can be added to a
*   response panel (a DragonPanel). Despite the name, DragonField
*   subclasses can implement many types of controls, not just text fields.
*   Actually, DragonField extends JPanel; the subclasses provide a layout
*   of controls and labels within the JPanel.
*   
* @author  goldin
* @version  Mon Jan 08 11:36:01 EST 2001*/
public abstract class DragonField extends JPanel
                            implements KeyListener
    {
      /**
       * Hook for data/functionality specific to a particular 
       * field. Primarily used for validation and callback methods.
       * Does not need to be copied in clone b/c will only be set
       * when UI is operating.
       */
    protected Object userData = null;

    public static final String PARENT_FIELD = "PARENT_FIELD";
    
      /** can be used to specify minimum and maximum values
       * for floating point or integer value field. If null,
       * there are no limits - or this is not a numeric field.*/
    protected ValueLimits limits = null;
    
      /** Character which, when typed with a Ctrl key, will activate
       *   this control.
       */
    protected char accelerator;
    
      /** Set to true if field represents a file, else false.
       */
    protected boolean bFileField;
    
      /** Set to true if field is of a type that has choices, that is,
       * combo, checkbox or radio box field type..
       */
    protected boolean bChoiceControl;
    
      /** Class that implements the Callback interface
       *   which will be called when the user enters data in this field.
       *   Callbacks typically do things like fill in values or enable/disable
       *   fields.*/
    protected Callback callback;
    
      /**
       * Buffer to hold any subcommand constructed by a popup that
       * was brought up by a callback on this field.
       */
    protected String callbackSubCommand = null;

      /** Value used to keep track of ordering of fields in a panel. Set
       *   by the parentPanel when the field is added to the panel.
       */
    protected int fieldNumber;
    
      /** Pattern that values must match. For filenames, this will usually
       *   be something like "*.IMG". For other types of controls, can be
       *   used to indicate special formats such as phone numbers, etc.
       *   It will be interpreted and enforced by the validator.
       */
    protected String filterPattern = null;
    
      /** String to display as help for the control.
       */
    protected String helpString;
    
      /**
       * Array of keys used to retrieve the help.
       */
    protected String[] helpKeys;


    /** Array of strings to display in the combo box. These
    *   will be translated into the currently-selected language.
    *   
    */
    protected String[] choiceStrings = null;
    
      /**
       * Array of keys used to retrieve the help.
       */
    protected String[] choiceKeys;


      /**
       * Holds the label or title text. Can be changed via 
       * setText method.
       */
    protected String labelText;

      /**
       * Translation key for label text.
       */
    protected String labelKey;


      /**
       * Holds the default value for this field.
       * Could be null.
       */
    protected String defaultValue = null;

      /**
       * Translation key for default - only if the defaultCategory is
       * xlateString
       */
    protected String defaultKey;

      /** JLabel object providing a text label for the field.
       *   May be null for some subclasses of DragonField.
       *   
       */
    protected JLabel label;
    
      /** Character which, when typed with the Alt key, will
       *   activate this control.
       */
    protected char mnemonic;
    
      /** Name for this field. Must be unique within the parent
       *   panel, not necessarily across all panels.
       */
    protected String name;
    
      /**
       *  If true, this field should be placed on a new line even
       *  if there is room on the same line in the panel.
       *  Default is false.
       */
    protected boolean bNewLine = false;

      /**
       *  If true, this field should be centered, alone on a line.
       */
    protected boolean bCentered = false;

      /** String that is used to preface the value from this control
       *   in the DRAGON command line
       */
    protected String pSpecifier;
    
      /** Panel in which this instance of the field lives.*/
    protected DragonPanel parentPanel;
    
      /** Length and width preferred for this control box.
       */
    protected Dimension preferredSize = new Dimension(10,10);
    
      /** Reference to an object which implements the
       *   Validator interface, used to determine if current
       *   contents are valid. May be null.*/
    protected Validator validator = null;

      /** Reference to an object which implements the
       *   Initializer interface, used to set initial values when
       *   the panel is displayed.*/
    protected Initializer initializer = null;

      /**
       * If true, then the control is enabled. Otherwise, it is
       * not. Must be set by each setEnabled method. (We did not
       * want to implement a concrete setEnabled method in
       * the superclass, because we want to be reminded if we forget
       * the implementation in a subclass.)
       */
    protected boolean bEnabled = true;

      /**
       * If true, then control should be enabled by default.
       * Otherwise, it should be disabled by default.
       */
    protected boolean bDefaultEnabled = true;

      /**
       * If true, then a value must be supplied for this
       * control (assuming that it is enabled). Otherwise,
       * it can be left blank.
       * Note that radio box and checkbox controls will always
       * have a value.
       */
    protected boolean bRequired = false;

      /**
       * If true, this is a text control. Set to true in
       * constructor for DTextField.
       */
    protected boolean bTextControl = false;

      /**
       * If true, this is a multiline control (combo Box or text
       * area, and up/down arrows should not be treated as tabs.
       */
    protected boolean bMultiLine = false;

      /**
       * If true, this control should be placed at the bottom
       * of the response panel.
       */
    protected boolean bBottom = false;

      /**
       * Holds the previous value for the control, if any.
       * Used to detect changes. Especially important for text
       * controls.
       */
    protected String previousValue = "";

      /**
       * Allows us to use a DragonField to pass another Component
       * to a callback. 
       */
    protected Component parentComponent = null;

    //*******************************************************************
      /**
       * Reinitialize the control after a change. This is null
       * here but has control-specific implementation for some controls
       */
    protected void reInit()
        {
	}

      /**
       * Create a clone of the current object. We make this abstract
       * because we want each sub-class to create an object of its
       * own class.
       */
    public abstract DragonField makeClone();

      /** 
       * Copy of all the generic DragonField data from the
       * object to a clone object. This will be called by each specific
       * subclass, which will then add subclass-specific data. 
       * The method is used to create new instances of controls read from the 
       * specification file, so that the same essential control
       * can be used in multiple different response panels.
       * We do not set any of the data that is initialized during the
       * addField method on the panel (such as parentPanel).
       */
    protected void initializeClone(DragonField clone)
        {
        clone.setEnabled(bEnabled);
        clone.setDefaultEnabled(bDefaultEnabled);
        clone.setBottom(bBottom);
        clone.setAccelerator(accelerator); 
        clone.setFileField(bFileField);
        clone.setCallback(callback);
        clone.setFilterPattern(filterPattern);
        clone.setHelpString(helpString);
        clone.setInitializer(initializer);
        clone.setMnemonic(mnemonic);
        clone.setName(name);
        clone.setNewLine(bNewLine); 
	clone.setCentered(bCentered);
        clone.setPSpecifier(pSpecifier); 
        clone.setPreferredSize(preferredSize);
        clone.setValidator(validator); 
        clone.setRequired(bRequired);
        clone.setValueLimits(limits);
        clone.setTextControl(bTextControl);
        clone.setMultiLine(bMultiLine);
	clone.setLabelKey(labelKey);
	clone.setHelpKeys(helpKeys);
	clone.setChoiceKeys(choiceKeys);
        clone.setDefaultValue(defaultValue);
	clone.setDefaultKey(defaultKey);
	}

    //********************************************************************
      /** Tries to set the focus to the control associated
       *  with the field. Since each field subclass has different
       *  controls, this method must be implemented for each one.
       */
    public abstract void requestFocus();
    



    //********************************************************************
      /** Returns the current value for the field. Must be overridden
       *   by each subclass.
       */
    public abstract String getFieldValue();
    

    //********************************************************************
      /** Sets the field to be enabled or disabled depending
       *   on the value of the bEnabled argument.
       *   
       * @param  bEnabled Enablement flag
       */
    public abstract void setEnabled(boolean bEnabled);
    
    //********************************************************************
      /** Allows the panel or other outside class to set the value of the
       *   field. Must be overridden in each subclass,
       * @param  value String to use to set value of the control.
       *   This may need to be transformed to
       *   an index or some other form.
       */
    public abstract void setFieldValue(String value);
    
    //********************************************************************
      /** Calculates the minimum amount of space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum width of graphical components, in pixels.
       */
    public abstract int calculateWidth();

      /** Calculates the minimum amount of vertical space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum height of graphical components, in pixels.
       */
    public abstract int calculateHeight();

      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public abstract boolean equivalent(DragonField field);


      /**
       * Component method meant to be invoked by subclasses
       * Checks fields common to all controls.
        */
    protected boolean commonFieldsEqual(DragonField field)
        {
	if (field.getName().compareTo(name) != 0)
	    return false;
	if ((field.getLabelText() != null) &&
	    (field.getLabelText().compareTo(labelText) != 0))
	    return false;
        if (field.isEnabled() != bEnabled)
	    return false;
        if (field.isDefaultEnabled() != bDefaultEnabled)
	    return false;
	if (field.isBottom() != bBottom)
	    return false;
	if (field.getAccelerator() != accelerator)
	    return false;
	if ((field.getCallback() == null) && (callback != null))
	    return false;
	if ((field.getCallback() != null) && (callback == null))
	    return false;
	if ((field.getCallback() != null) &&
	    (callback != null) &&
            (field.getCallback().getClass().getName() !=
            callback.getClass().getName()))
	    return false;
	if ((field.getFilterPattern() != null) &&
            (field.getFilterPattern().compareTo(filterPattern) != 0))
	    return false;
	if (field.isChoiceControl() != bChoiceControl)
	    return false;
	if ((field.getHelpString() != null) &&
            (field.getHelpString().compareTo(helpString) != 0))
	    return false;
        if (field.getMnemonic() != mnemonic)
	    return false;
        if (field.getNewLine() != bNewLine)
	    return false;
        if (field.getCentered() != bCentered)
	    return false;
	if (field.getPSpecifier().compareTo(pSpecifier) != 0)
	    return false;
	Dimension fieldSize = field.getPreferredSize();
	if ( (fieldSize != null) && (preferredSize != null) &&
             ((fieldSize.width != preferredSize.width) ||
              (fieldSize.height != preferredSize.height)))
	    return false;
	if ((field.getValidator() == null) && (validator != null))
	    return false;
	if ((field.getValidator() != null) && (validator == null))
	    return false;
        if ((field.getValidator() != null) &&
            (validator != null) &&
            (field.getValidator().getClass().getName() !=
            validator.getClass().getName()))
	    return false;
	if (field.isRequired() != bRequired)
	    return false;
	if ((field.getValueLimits() == null) && (limits != null))
	    return false;
	if ((field.getValueLimits() != null) && (limits == null))
	    return false;
	ValueLimits fieldLimits = field.getValueLimits();
	if ((fieldLimits != null) &&
            (limits != null) &&
            ((fieldLimits.maxValue != limits.maxValue) ||
	     (fieldLimits.minValue != limits.minValue) ||
             (fieldLimits.bInteger != limits.bInteger)))
	    return false;
	return true;
	}

      /**
       * Search up the parentPanel chain until we find the
       * top-level panel associated with this fields top-level
       * parent. May return null if called on a field that has not
       * yet been added to any panel.
       */
    public DragonPanel getTopLevelPanel()
        {
	DragonPanel ultimate = null;
	DragonPanel next = parentPanel;
	while (next != null)
	    { 
	    ultimate = next;
	    next = next.getParentPanel();
	    }
	return ultimate;
        }

      /**
       * Invoke the validator for this field, if any, and return
       * the result.
       * @return true if the field is valid, or if there is no validator
       *          else returns false.
       */
    public boolean isFieldValueValid()
       {
       boolean bValid = true;
       if (validator != null)
	   bValid = validator.isValid(this);
       return bValid;
       }

      /**
       * Method to clear the field - if this is relevant.
       * Most control types use the base class method, which
       * does nothing.
       */
    public void clearField()
        {
	}

      /**
       * Method to show choices or choice dialog. Overridden by
       * DComboField, DFileField and DFontField to actually do something.
       */
    public void showChoices()
        {
	}

      /**
       * Method which will create a focus requestor for
       * a field. This is intended to be be called from callback classes.
       * Overridden in DTextField to actually do something.
       * (FocusRequestor is an inner class of DTextField.)
       * @param delay  How long to wait before transferring focus.
       */
    public void createFocusRequestor(int delay)
         {
	 }
 
      /** 
       * Assuming that the focus is currently on this
       * component, set it to the next one in the
       * default focus traversal list.
       */
    protected void setFocusToNext()
        {
        DragonField nextField = parentPanel.getNextEnabledField(this);
        if (nextField != null)
	    nextField.requestFocus();
	}

      /** 
       * Assuming that the focus is currently on this
       * component, set it to the previous one in the
       * default focus traversal list.
       */
    protected void setFocusToPrevious()
        {
        DragonField prevField = parentPanel.getPreviousEnabledField(this);
        if (prevField != null)
	    prevField.requestFocus();
	}

    //********************************************************************
      /**
       * Methods from the KeyListener interface.
        */
    public void keyPressed(KeyEvent ke)
        {
  	DragonPanel parent;
	int code = ke.getKeyCode();
        Object source = ke.getSource();
	if (this.getName().compareTo("dummy") == 0)  
	    // event did not come from this control
	    {
	    return;
	    }
        boolean bCommandLine = (this.getName().compareTo("CommandLine") == 0);
	switch (code)
	    {
	    case KeyEvent.VK_KP_DOWN:
	    case KeyEvent.VK_DOWN:
	        if (this instanceof DComboField)
		    {
                    DComboField combo = (DComboField) this;
		    if (!combo.isPopupVisible())
		        {
		        setFocusToNext();
			ke.consume();
			}
		    }
                else if ((!isMultiLine()) && (!bCommandLine)) 
		    {
		    setFocusToNext();
		    ke.consume();
		    }
		break;
	    case KeyEvent.VK_KP_RIGHT:
	    case KeyEvent.VK_RIGHT:
	        if (!isTextControl())
		    {
		    setFocusToNext();
		    ke.consume();
		    }
		break;
	    case KeyEvent.VK_ENTER:
	        if (!bCommandLine)
		    {	      
 		    setFocusToNext();
		    ke.consume();
		    }
		break;
	    case KeyEvent.VK_KP_UP:
	    case KeyEvent.VK_UP:
	        if (this instanceof DComboField)
		    {
                    DComboField combo = (DComboField) this;
		    if (!combo.isPopupVisible())
		         {
			 setFocusToPrevious();
		         ke.consume();
		         }
		    }
                else if ((!isMultiLine()) && (!bCommandLine))
		    {
		    setFocusToPrevious();
		    ke.consume();
		    }
		break;
	    case KeyEvent.VK_KP_LEFT:
	    case KeyEvent.VK_LEFT:
	        if (!isTextControl())
		    {
		    setFocusToPrevious();
		    ke.consume();
		    }
		break;
	    case KeyEvent.VK_U:
                if ((ke.getModifiers() & InputEvent.CTRL_MASK) == 0)
		    {
		    break;  // if control mask set, fall through
		    }
	    case KeyEvent.VK_HOME:
	        clearField();
		ke.consume();
		break;
            case KeyEvent.VK_F3:
	        showChoices();
                ke.consume();
		break;
	    default:
		/* If the user is typing, don't show the help */
		cancelHelpEvents();
	        break;
	    }
	}

    public void keyReleased(KeyEvent ke)
        {
	}

    public void keyTyped(KeyEvent ke)
        {
	}

    /** 
     * Send a simulated mouseExited event to 
     * all the mouse listeners for this component.
     * This should stop help from being displayed once
     * we start typing.
     */
    protected void cancelHelpEvents()
        {
	MouseEvent event = 
	    new MouseEvent(this,MouseEvent.MOUSE_EXITED,new Date().getTime(),
                           0,0,0,1,false);
        MouseListener [] listeners =
	    (MouseListener []) (this.getListeners(MouseListener.class));

        for (int i = 0; i < listeners.length; i++)
            {
	    listeners[i].mouseExited(event);  
            }
        }  

    //********************************************************************
      /** * Get/Set Methods
       */

    public boolean isMultiLine()
        {
	return bMultiLine;
	}

    public void setMultiLine(boolean flag)
        {
	bMultiLine = flag;
	}

    public boolean isTextControl()
        {
	return bTextControl;
	}

    public void setTextControl(boolean flag)
        {
	bTextControl = flag;
	}

    public boolean isChoiceControl()
        {
	return bChoiceControl;
	}

    public void setDefaultEnabled(boolean flag)
        {
	bDefaultEnabled = flag;
	}

    public boolean isDefaultEnabled()
        {
	return bDefaultEnabled;
	}

    public boolean isEnabled()
        {
	return bEnabled;
	}

    public boolean isBottom()
        {
	return bBottom;
	}
   
    public void setBottom(boolean bFlag)
        {
	bBottom = bFlag;
	}

    public String getCallbackSubCommand()
        {
	return callbackSubCommand;
	}

    public void setCallbackSubCommand(String cmd)
        {
	callbackSubCommand = cmd;
	}

    public String[] getChoiceStrings() 
        {
        return choiceStrings;
        }
    
    public String getChoiceStrings(int index) 
        {
        return choiceStrings[index];
        }
    
    public void setChoiceStrings(String[] choiceStrings) 
        {
        this.choiceStrings = choiceStrings;
        reInit();
        }
    
    public void setChoiceStrings(int index, String choiceStrings) 
        {
        this.choiceStrings[index] = choiceStrings;
	reInit();
        }
    
    public JLabel getLabel() 
        {
        return label;
        }

    public void setLabel(JLabel label) 
        {
        this.label = label;
        }
    
    public char getAccelerator() 
        {
        return accelerator;
        }
    
    public void setAccelerator(char accelerator) 
        {
        this.accelerator = accelerator;
        }
    
    public boolean isFileField() 
        {
        return bFileField;
        }
    
    public void setFileField(boolean bFileField) 
        {
        this.bFileField = bFileField;
        }
    
    public Callback getCallback() 
        {
        return callback;
        }
    
    public void setCallback(Callback callback) 
        {
        this.callback = callback;
        }

    public Initializer getInitializer() 
        {
        return initializer;
        }
    
    public void setInitializer(Initializer initializer) 
        {
        this.initializer = initializer;
        }
    
    public int getFieldNumber() 
        {
        return fieldNumber;
        }
    
    public void setFieldNumber(int fieldNumber) 
        {
        this.fieldNumber = fieldNumber;
        }
    
    public String getFilterPattern() 
        {
        return filterPattern;
        }
    
    public void setFilterPattern(String filterPattern) 
        {
        this.filterPattern = filterPattern;
        }
    
    public String getHelpString() 
        {
        return helpString;
        }
    
    public void setHelpString(String helpString) 
        {
        this.helpString = helpString;
        }

    public void setHelpKeys(String[] keys)
        {
	this.helpKeys = keys;
	}

    public String[] getHelpKeys()
        {
	return helpKeys;
	}

    public void setChoiceKeys(String[] keys)
        {
	this.choiceKeys = keys;
	}

    public String[] getChoiceKeys()
        {
	return choiceKeys;
	}
    
    public void setLabelText(String text)
        { 
	labelText = text;
	if (label != null)
	    label.setText(labelText);
	}
      
    public String getLabelText()
        { 
	return labelText;
	}
      
    public void setLabelKey(String key)
        { 
	labelKey = key;
	}
      
    public String getLabelKey()
        { 
	return labelKey;
	}

    public void setDefaultValue(String value)
        { 
	defaultValue = value;
	}
      
    public String getDefaultValue()
        { 
	return defaultValue;
	}
      
    public void setDefaultKey(String key)
        { 
	defaultKey = key;
	}
      
    public String getDefaultKey()
        { 
	return defaultKey;
	}

    public char getMnemonic() 
        {
        return mnemonic;
        }
    
    public void setMnemonic(char mnemonic) 
        {
        this.mnemonic = mnemonic;
        }
    
    public String getName() 
        {
        return name;
        }
    
    public void setName(String name) 
        {
        this.name = name;
        }
    
    public boolean getNewLine() 
        {
        return bNewLine;
        }
    
    public void setNewLine(boolean bNew) 
        {
        this.bNewLine = bNew;
        }

    public boolean getCentered() 
        {
        return bCentered;
        }
    
    public void setCentered(boolean bCentered) 
        {
        this.bCentered = bCentered;
        }

    public Component getParentComponent() 
        {
        return parentComponent;
        }

    public void setParentComponent(Component parentComponent) 
        {
        this.parentComponent = parentComponent;
        }

    public String getPreviousValue()
        {
	return previousValue;
	}

    public String getPSpecifier() 
        {
        return pSpecifier;
        }
    
    public void setPSpecifier(String pSpecifier) 
        {
        this.pSpecifier = pSpecifier;
        }
    
    public DragonPanel getParentPanel() 
        {
        return parentPanel;
        }
    
    public void setParentPanel(DragonPanel parentPanel) 
        {
        this.parentPanel = parentPanel;
        }
    
    public Dimension getPreferredSize() 
        {
        return preferredSize;
        }
    
      /**
       * COPY the data values. Don't use the passed object
       */
    public void setPreferredSize(Dimension preferredSize) 
        {
        this.preferredSize.width = preferredSize.width;
	this.preferredSize.height = preferredSize.height;
        }
    
    public Validator getValidator() 
        {
        return validator;
        }
    
    public void setValidator(Validator validator) 
        {
        this.validator = validator;
        }

    public boolean isRequired()
        {
	return bRequired;
	}

    public void setRequired(boolean bRequired)
        {
	this.bRequired = bRequired;
	}
    

    public ValueLimits getValueLimits()
        {
	return limits;  // might be null
	}

    public void setValueLimits(ValueLimits limits)
        {
	this.limits = limits;
	}

    public void setUserData(Object data)
        {
        userData = data;
	}

    public Object getUserData()
        {
	return userData;
	}

      /**
       * Used for debugging - constructs a string that lists
       * all the keys for the text.
       */
    public String constructKeyMessage()
        {
	StringBuffer msg = new StringBuffer(1024);
	if (labelKey != null)
	    {
	    msg.append("Label key: ");
	    msg.append(labelKey);
	    msg.append("\n");
	    }
	if (helpKeys != null)
	    {
	    msg.append("Help keys: ");
	    for (int i = 0; i < helpKeys.length; i++)
	        {
	        if (i > 0)
	            msg.append(", ");
		msg.append(helpKeys[i]);
		}
	    msg.append("\n");
            }
	if (choiceKeys != null)
	    {
	    msg.append("Choice keys: ");
	    for (int i = 0; i < choiceKeys.length; i++)
	        {
	        if (i > 0)
	            msg.append(", ");
	        msg.append(choiceKeys[i]);
		}
	    msg.append("\n");
	    }
	return msg.toString();
	}

    }

// End of DragonField.java


