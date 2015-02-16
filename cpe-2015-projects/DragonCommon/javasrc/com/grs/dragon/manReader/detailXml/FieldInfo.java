/* FieldInfo.java
 *
 * ~~Copyright 2002-2015 by Goldin-Rudahl Associates
 * ~~ EndC
 *
 * Created by Sally Goldin, 6/26/2002
 *
 *
 * $Id: FieldInfo.java,v 1.3 2015/01/01 08:37:11 rudahl Exp $
 * $Log: FieldInfo.java,v $
 * Revision 1.3  2015/01/01 08:37:11  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.2  2002/06/27 18:23:27  goldin
 * Enhance detail file structure
 *
 * Revision 1.1  2002/06/26 19:23:54  goldin
 * Initial implementation of classes to generate Dragon details HTML file for ManReader
 *
 *
 */

package com.grs.dragon.manReader.detailXml;
import com.grs.gui.*;
import java.util.*;

/** 
*  This class maintains information about a single field in
*  a Dragon panel, and by extension, a single parameter for
*  a Dragon operation. It is created based on specifications
*  in the Dragon Panel XML file, and used to generate the
*  ddetail.html file for the ManReader.
*/
public class FieldInfo 
    {
      /**
       * Encodes limits on numeric fields.
       */
    protected ValueLimits limits = null;

      
      /**
       * True if this field is a push button or label that
       * does not contribute to a dragon command
       */
    protected boolean bDummyControl = false;


      /**
       * True if this field needs a file name.
       */
    protected boolean bFileField = false;
    
      /** Set to true if this field must be filled by the
       *   name of an existing file.
       */
    protected boolean bExisting = false;

      /** Set to true if field is of a type that has choices, i.e.
       * combo, checkbox or radio box field type..
       */
    protected boolean bChoiceControl = false;
    
      /**
       * if choice control, are choices fixed?
       */
    protected boolean bChoicesFixed = false;

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

      /** Name for this field. Must be unique within the parent
       *   panel, not necessarily across all panels.
       */
    protected String name;
    
      /** String that is used to preface the value from this control
       *   in the DRAGON command line
       */
    protected String pSpecifier;
    
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


      /** Array of strings such as "=M", "=B", etc.
       *   which represent the memory files allowed for this
       *   file field, in their preferred order.
       */
    protected String[] allowedMemoryFiles = null;


      /**
       * Type of file that should be gotten for this
       * file field.*/
    protected DFileType fileType = DFileType.ALL;


      //****************************************************
      /**
       * Constructor, sets name of object. All other
       * fields set by calling access methods.
       * @param nameString Unique ID for the field.
       */
    public FieldInfo(String nameString)
        {
	name = nameString;
	}

      /** * Get/Set Methods
       */
    public boolean isDummyControl()
        {
        return bDummyControl;
	}

    public void setDummyControl(boolean flag)
        {
	bDummyControl = flag;
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

    public void setChoiceControl(boolean flag)
        {
	bChoiceControl = flag;
	}

    public boolean areChoicesFixed()
        {
	return bChoicesFixed;
	}

    public void setChoicesFixed(boolean flag)
        {
	bChoicesFixed = flag;
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
        }
    
    public void setChoiceStrings(int index, String choiceStrings) 
        {
        this.choiceStrings[index] = choiceStrings;
        }

    public String getAppendedChoices()
        {
	StringBuffer buffer = new StringBuffer();
	if (choiceStrings != null)
	    {
	    for (int i = 0; i < choiceStrings.length; i++)
	        {
		if (choiceStrings[i].length() > 1)
		     buffer.append("<b>" + choiceStrings[i].substring(0,1) +
			      "</b>" + choiceStrings[i].substring(1));
		else
		     buffer.append(choiceStrings[i]);
		if (i < choiceStrings.length - 1)
		    buffer.append(", ");
		}
	    }
	return buffer.toString();
	}
    
    public boolean isFileField() 
        {
        return bFileField;
        }
    
    public void setFileField(boolean bFileField) 
        {
        this.bFileField = bFileField;
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

    public String getName() 
        {
        return name;
        }
    
    public void setName(String name) 
        {
        this.name = name;
        }
    

    public String getPSpecifier() 
        {
        return pSpecifier;
        }
    
    public void setPSpecifier(String pSpecifier) 
        {
        this.pSpecifier = pSpecifier;
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

    public DFileType getFileType() 
        {
        return fileType;
        }
    
    public void setFileType(DFileType type) 
        {
	if (type != null)
            this.fileType = type;
	else
	    this.fileType = DFileType.ALL;
	}
    
    public boolean isExisting() 
        {
        return bExisting;
        }
    
    public void setExisting(boolean bExisting) 
        {
        this.bExisting = bExisting;
        }
    }

