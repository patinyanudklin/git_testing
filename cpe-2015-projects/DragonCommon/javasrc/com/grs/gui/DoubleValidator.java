/* DoubleValidator.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: DoubleValidator.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DoubleValidator.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2006/04/19 11:01:05  goldin
 * Double validator should allow commas instead of dec. pts.
 *
 * Revision 1.3  2002/09/23 23:00:38  goldin
 * Make beep part of error display  rather than a reaction in the control
 *
 * Revision 1.2  2002/04/29 22:36:16  goldin
 * Fine tune error message delivery
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.3  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/10/30 13:04:41  goldin
 * Get rid of leading/trailing blanks in numbers
 *
 * Revision 1.1  2001/05/18 11:11:55  goldin
 * Add validators to numeric fields
 *
 */

package com.grs.gui;
import javax.swing.*;
import java.awt.*;

/** 
 * This class checks to make sure that the value in a field
 * is a valid Double, possibly enforcing minimum and maximum values.*/
public class DoubleValidator implements Validator 
    {

    protected String lastErrorKey = null;

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
	boolean bValid = true;
	lastErrorKey = null;
	double dblValue = 0;
	String value = field.getFieldValue();
        String newValue = value;
	if (value.length() > 0)
	    {
	    /* replace commas with decimal points */
            newValue = value.replace(',','.');
	    try
	        {
		dblValue = Double.parseDouble(newValue.trim());
		ValueLimits limits = field.getValueLimits();
		if ((limits != null) &&
		    ((dblValue >  limits.maxValue) ||
		     (dblValue < limits.minValue)))
		    {
		    bValid = false;
		    lastErrorKey = TextKeys.OUTSIDE_RANGE;
		    }
		}
	    catch (NumberFormatException nfe)
	        {
		bValid = false;
		lastErrorKey = TextKeys.BADDOUBLE;
		}
	    }
        field.setFieldValue(value.trim());
	return bValid;
	}
    
      /**
       * Asks the validator to display an error box showing
       * information on the last error.
       */
    public void displayLastError()
        {
        if (lastErrorKey == null)  // no error
	    return;
	Toolkit.getDefaultToolkit().beep();
	ErrorDisplay errDisplay = 
	    ApplicationManager.getErrorDisplay();
	errDisplay.showError(TextKeys.ERROR, lastErrorKey, null);
	lastErrorKey = null;
	}

      /**
       * Return true if there is an unreported error.
       */
    public boolean isErrorOutstanding()
        {
	return (lastErrorKey != null);
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DoubleValidator.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of DoubleValidator.java

