/* KeyNumValidator.java
 *
 * Copyright 2002 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/14/2002
 *
 * $Id: KeyNumValidator.java,v 1.7.4.1 2014/12/25 07:27:43 rudahl Exp $
 * $Log: KeyNumValidator.java,v $
 * Revision 1.7.4.1  2014/12/25 07:27:43  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.7  2006/03/11 03:15:45  goldin
 * Don't give message if Key field is blank
 *
 * Revision 1.6  2005/08/01 04:43:17  goldin
 * Completing I18N for installer
 *
 * Revision 1.5  2002/09/18 17:27:11  goldin
 * No key msg should be a warning
 *
 * Revision 1.4  2002/09/15 16:29:56  goldin
 * Only give empty key warning once
 *
 * Revision 1.3  2002/09/14 22:01:59  goldin
 * minor changes
 *
 * Revision 1.2  2002/09/03 18:03:03  goldin
 * Fix bugs in running off the CD
 *
 * Revision 1.1  2002/02/15 21:20:28  goldin
 * Rework protection mechanisms &S/N-based product algorithm
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import javax.swing.*;
import java.awt.*;
import java.util.*;

/** 
 * This class checks to make sure that the value entered in the
 * Key number field is of a valid form.
 */
public class KeyNumValidator implements Validator
    {
    protected static final String BAD_KN_MESSAGE =
        "Invalid Key Number";
    protected static final String EMPTY_KN_MESSAGE =
        "Note that if you do not provide a key number\nthis installation will be run only in Demo/Evaluation mode";
    protected String lastErrorMessage = null;
    protected String extraInfo = null;
    protected boolean bWarnedOnce = false;

    /** Returns true if current field value is valid, else false.
     * Warns the user if the key number field is empty.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
	boolean bValid = true;
	boolean bEnabled = field.isEnabled();
        if (!bEnabled)
            return bValid;
	lastErrorMessage = null;
	String xlatedMsg = ApplicationManager.getTextSource().getI18NText(
					      "%H01.13.22", BAD_KN_MESSAGE);
	String value = field.getFieldValue();
	if ((value.length() == 0) && (!bWarnedOnce))
	    {
	    MessageDisplay msgDisplay = 
	    ApplicationManager.getMessageDisplay();
	    String xlatedWarning =
	       ApplicationManager.getTextSource().getI18NText(
                            "%H01.502", EMPTY_KN_MESSAGE);					    
	    msgDisplay.showWarning(TextKeys.WARNING, xlatedWarning);
	    bWarnedOnce = true;
	    return true;
            }
	char snChars[] = value.toUpperCase().toCharArray();
	for (int i=0; i < snChars.length; i++)
	    {
            if (snChars[i] == '0')
	        continue;
	    if (snChars[i] == '7')
	        break;
	    else 
	        {
	        lastErrorMessage = xlatedMsg;
	        bValid = false;
	        }
	    }
	field.setFieldValue(value.toUpperCase());
	return bValid;
	}

      /**
       * Asks the validator to display an error box showing
       * information on the last error.
       */
    public void displayLastError()
        {
        if (lastErrorMessage == null)  // no error
	    return;
	ErrorDisplay errDisplay = 
	    ApplicationManager.getErrorDisplay();
	errDisplay.showError(TextKeys.ERROR, lastErrorMessage);
	}

      /**
       * returns true if error exists that has not been reported,
       * else false.
       */
    public boolean isErrorOutstanding()
        {
	return (lastErrorMessage != null);
	}

    }


