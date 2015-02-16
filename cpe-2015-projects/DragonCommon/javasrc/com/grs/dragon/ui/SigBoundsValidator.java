/* SigBoundsValidator.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/12/01
 *
 * $Id: SigBoundsValidator.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SigBoundsValidator.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.2  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/12 14:02:06  goldin
 * Add new callback and validator for c/edi/mod
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import java.awt.*;
import java.util.*;

/** 
 * This class checks to make sure that the value in a field
 * is a valid integer, possibly enforcing minimum and maximum values.
 * Then it checks to make sure that if it's a lower bound, it is
 * less than the corresponding upper bound, and vice versa*/
public class SigBoundsValidator extends IntegerValidator
    {
    protected HashMap correspondingField;
    
      /**
       * Constructor initializes HashMap
       */
    public SigBoundsValidator()
        {
        correspondingField = new HashMap(8);
	correspondingField.put("^UB1","^LB1");
	correspondingField.put("^UB2","^LB2");
	correspondingField.put("^UB3","^LB3");
	correspondingField.put("^UB4","^LB4");
	correspondingField.put("^LB1","^UB1");
	correspondingField.put("^LB2","^UB2");
	correspondingField.put("^LB3","^UB3");
	correspondingField.put("^LB4","^UB4");
	}

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
        if (!super.isValid(field))
            return false;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
	    return false;
	boolean bValid = true;
	int intValue = 0;
        int compareValue = 0;
	String value = field.getFieldValue();
	if (value.length() > 0)
	    {
	    try  // we know this will succeed - it has already been
		// done once in the superclass method 
	        {
		intValue = Integer.parseInt(value);
                String otherFldName = 
                   (String) correspondingField.get(field.getName());
                DragonField otherFld = parent.getField(otherFldName);
		if (otherFld != null)
		    {
                    compareValue = Integer.parseInt(otherFld.getFieldValue());
                    if (((field.getName().startsWith("^L")) &&
                         (intValue > compareValue)) ||
			((field.getName().startsWith("^U")) &&
                        (intValue < compareValue)))
		      {
                      bValid = false;
		      lastErrorKey = TextKeys.BADBOUNDS;
		      }
		    }
		}
	    catch (NumberFormatException nfe)
	        {
		bValid = false;
		lastErrorKey = TextKeys.BADINTEGER;
		}
	    }
	return bValid;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SigBoundsValidator.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


