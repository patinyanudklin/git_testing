/* FileTypeValidator.java
 *
 * Copyright  2002-2007  Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 1/10/2002
 *
 * $Id: FileTypeValidator.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $
 * $Log: FileTypeValidator.java,v $
 * Revision 1.6  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.5  2006/02/19 09:22:21  goldin
 * Handle possibility of a null file type
 *
 * Revision 1.4  2002/09/23 23:00:31  goldin
 * Make beep part of error display  rather than a reaction in the control
 *
 * Revision 1.3  2002/04/29 22:36:06  goldin
 * Fine tune error message delivery
 *
 * Revision 1.2  2002/01/22 14:54:14  goldin
 * Move focus after error
 *
 * Revision 1.1  2002/01/10 14:55:35  goldin
 * Add validator for file type in HEA
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import java.awt.*;
import java.util.*;

/** 
 * This class checks to make sure that the value in the file type
 * field is one of Dragon's legal values "I","C",or "L".
 */
public class FileTypeValidator implements Validator
    {
    protected String lastErrorKey = null;
    protected String extraInfo = null;

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
	boolean bValid = false;
	String value = field.getFieldValue();
	if ((value != null) &&
	    ((value.equals("I")) ||
	     (value.equals("L")) ||
	     (value.equals("C"))))
	    {
	    bValid = true;
	    }
	else
	    {
	    lastErrorKey = TextKeys.BADFILETYPE;
	    extraInfo = value;
	    DragonPanel parent = field.getTopLevelPanel();
	    if (parent != null)  
	        {
	        DragonField fileFld = parent.getField("^FNMX");
		if (fileFld != null)
		    fileFld.requestFocus();
	        }
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
        cvsInfo = "\n@(#)  $Id: FileTypeValidator.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


