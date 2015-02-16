/*  ShortPathValidator.java
 *
 * Copyright  2002-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/25/2002
 *
 * $Id: ShortPathValidator.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ShortPathValidator.java,v $
 * Revision 1.2  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.1  2002/10/25 22:03:31  goldin
 * Only Kpath should be restricted to 8 chars
 *
 */

package com.grs.dragon.ui;
import com.grs.dragon.common.PathChecker;
import javax.swing.*;
import java.awt.*;
import com.grs.gui.*;
import java.io.*;

/** 
*   This class implements the Validator interface. It is used
*   to validate the correctness of a path with 8.3 format, 
*   given the constraints
*   associated with the file field.
*/
public class ShortPathValidator extends FileValidator 
    {

      /**
       * Constructor creates a confirmation dialog to use for
       * output files that exist.
       */
    public ShortPathValidator()
        {
	super();
	}

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
        boolean bOk = true;
	lastErrorKey = null;
	lastErrorFile = null;
        StatusManager statManager = null;
	if (!(field instanceof DFileField))
   	    return true;  // should never be associated with anything
	                  // other than a file field.
	DFileField fld = (DFileField) field;
	lastProcessedField = fld;
        String currentValue = fld.getFieldValue();
	if ((currentValue == null) || (currentValue.length() == 0))
	    return true;
        DragonUI mainApp = DragonUI.currentApplication;
	statManager = mainApp.getStatusManager();
	boolean bExisting = fld.isExisting();
	boolean bPathData = fld.isPathData();
        if (!bPathData)
	    return true;  // problem - should never have been specified
	// should never have been specified as validator for this field
	DragonFileChooser chooser = fld.selectChooser();
	File tempFile = new File(currentValue);
	bOk = chooser.getModel().validateFile(tempFile.getParent(),
					       tempFile.getName(),
					       bExisting,false,
					       false);
	if (!bOk)
	    { 
	    lastErrorKey = chooser.getModel().getLastErrorKey();
	    lastErrorFile = chooser.getModel().getLastErrorFile();
	    }
	else if (!PathChecker.isPathOk(currentValue))
	    {
	    // TEMPORARY - we should really add another key
	    // with an appropriate message saying path components
	    // must be no longer than 8 characters
	    bOk = false;  
	    lastErrorKey = "%e403";
	    lastErrorFile = currentValue;
	    }
	return bOk;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ShortPathValidator.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
     }


