/* IntegerValidator.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: IntegerValidator.java,v 1.4 2007/01/05 07:41:58 rudahl Exp $
 * $Log: IntegerValidator.java,v $
 * Revision 1.4  2007/01/05 07:41:58  rudahl
 * added Whatis info
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
 * Revision 1.7  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.6  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.5  2001/10/30 13:04:41  goldin
 * Get rid of leading/trailing blanks in numbers
 *
 * Revision 1.4  2001/07/31 17:40:38  goldin
 * display correct range as part of message for out-of-range errors
 *
 * Revision 1.3  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.2  2001/04/10 11:18:46  goldin
 * Fix problem with modal dialog in FileValidator; extend IntegerValidator
 *
 * Revision 1.1  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 *
 */

package com.grs.gui;
import javax.swing.*;
import java.awt.*;

/** 
 * This class checks to make sure that the value in a field
 * is a valid integer, possibly enforcing minimum and maximum values.*/
public class IntegerValidator implements Validator 
    {

    protected String lastErrorKey = null;
    protected String extraInfo = null;

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
        StringBuffer workBuffer = new StringBuffer();
	boolean bValid = true;
	lastErrorKey = null;
        extraInfo = null;
	int intValue = 0;
	String value = field.getFieldValue();
	if (value.length() > 0)
	    {
	    try
	        {
		intValue = Integer.parseInt(value.trim());
		ValueLimits limits = field.getValueLimits();
		if ((limits != null) &&
		    ((intValue > (int) limits.maxValue) ||
		     (intValue < (int) limits.minValue)))
		    {
		    bValid = false;
		    lastErrorKey = TextKeys.OUTSIDE_RANGE;
                    workBuffer.append(" (" + String.valueOf((int)
						limits.minValue));
		    workBuffer.append("-");
		    workBuffer.append(String.valueOf((int)
						limits.maxValue) + ")");
		    extraInfo = workBuffer.toString();
		    }
		}
	    catch (NumberFormatException nfe)
	        {
		bValid = false;
		lastErrorKey = TextKeys.BADINTEGER;
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
	errDisplay.showError(TextKeys.ERROR, lastErrorKey,extraInfo);
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
        cvsInfo = "\n@(#)  $Id: IntegerValidator.java,v 1.4 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }

// End of IntegerValidator.java

