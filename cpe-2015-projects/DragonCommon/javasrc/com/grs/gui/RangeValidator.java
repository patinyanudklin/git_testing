/*  RangeValidator.java
 *
 *  Validator for DRangeControl values. Makes sure that
 *  values are within limits and that the min is less than
 *  or equal to the max. 
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
 * $Id: RangeValidator.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $
 * $Log: RangeValidator.java,v $
 * Revision 1.3  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.2  2007/01/02 13:21:29  goldin
 * minor modification to rule panel behavior
 *
 * Revision 1.1  2007/01/02 05:19:19  goldin
 * Complete behavioral code for Rule Creation panel
 *
 *
 */

package com.grs.gui;
import javax.swing.*;
import java.awt.*;

/** 
 * This class checks to make sure that the values in min and max fields
 * are valid or double, possibly enforcing minimum and maximum values.
 * and then checks that the upper bound is greater than or equal to
 * the lower bound.
 */
public class RangeValidator implements Validator 
    {

    protected String lastErrorKey = null;
    protected String extraInfo = null;

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
	DRangeControl rangeField = (DRangeControl) field;
	boolean bValid = true;
	String value = field.getFieldValue();
	lastErrorKey = null;
        extraInfo = null;
	if (value.length() > 0)
	    {
	    if (rangeField.isInteger())
	       bValid = checkIntegerRange(rangeField,value); 
            else
	       bValid = checkDoubleRange(rangeField,value);
            } 
	return bValid;
	}

	/**
	 * Factorization of isValid. Checks if an integer
         * range is okay.
         * @param field   Field whose value we are checking
	 * @param value   Current value in the field. It will
	 *                be in the form "min-max"
	 * @return true if valid, false if error.
	 */
     protected boolean checkIntegerRange(DRangeControl field, String value)
	{
        StringBuffer workBuffer = new StringBuffer();
	boolean bValid = true;
	int minVal = 0;
	int maxVal = 0;
        int pos = value.indexOf("-");
        try 
            {
	    if (pos>0)
                minVal = Integer.parseInt(value.substring(0,pos));
            if (pos < value.length() - 1)
	        maxVal = Integer.parseInt(value.substring(pos+1));
	    ValueLimits limits = field.getValueLimits();
	    if ((limits != null) &&
		    ((minVal > (int) limits.maxValue) ||
		     (minVal < (int) limits.minValue) ||
		     (maxVal < (int) limits.minValue) ||
		     (maxVal > (int) limits.maxValue)))
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
	if (minVal > maxVal)
	    {
	    bValid = false;
	    lastErrorKey = TextKeys.BADBOUNDS;
	    }
        return bValid;
	}

	/**
	 * Factorization of isValid. Checks if a double
         * range is okay.
         * @param field   Field whose value we are checking
	 * @param value   Current value in the field. It will
	 *                be in the form "min-max"
	 * @return true if valid, false if error.
	 */
     protected boolean checkDoubleRange(DRangeControl field, String value)
	{
        StringBuffer workBuffer = new StringBuffer();
	boolean bValid = true;
	double minVal = 0;
	double maxVal = 0;
        int pos = value.indexOf("-");
        try 
            {
	    if (pos > 0)
               minVal = Double.parseDouble(value.substring(0,pos));
            if (pos < value.length() - 1)
	       maxVal = Double.parseDouble(value.substring(pos+1));
	    ValueLimits limits = field.getValueLimits();
	    if ((limits != null) &&
		    ((minVal > limits.maxValue) ||
		     (minVal < limits.minValue) ||
		     (maxVal < limits.minValue) ||
		     (maxVal > limits.maxValue)))
	       {
	       bValid = false;
	       lastErrorKey = TextKeys.OUTSIDE_RANGE;
	       workBuffer.append(" (" + String.valueOf(
						       limits.minValue));
		    workBuffer.append("-");
		    workBuffer.append(String.valueOf(
						     limits.maxValue) + ")");
	       extraInfo = workBuffer.toString();
	       }
	    }
	catch (NumberFormatException nfe)
	    {
	    bValid = false;
	    lastErrorKey = TextKeys.BADDOUBLE;
	    }
	if (minVal > maxVal)
	    {
	    bValid = false;
	    lastErrorKey = TextKeys.BADBOUNDS;
	    }
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
        cvsInfo = "\n@(#)  $Id: RangeValidator.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }

// End of IntegerValidator.java

