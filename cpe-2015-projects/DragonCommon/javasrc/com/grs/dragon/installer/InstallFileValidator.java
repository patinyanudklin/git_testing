/* InstallFileValidator.java
 *
 *  Copyright 2001 by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 12/11/2001
 *
 * $Id: InstallFileValidator.java,v 1.8 2007/06/15 09:51:35 goldin Exp $
 * $Log: InstallFileValidator.java,v $
 * Revision 1.8  2007/06/15 09:51:35  goldin
 * make reportSuccess and errorAndRestart public
 *
 * Revision 1.7  2005/12/10 09:35:50  goldin
 * Fix FilenameDocument to allow unicode characters in filenames
 *
 * Revision 1.6  2005/08/01 04:43:17  goldin
 * Completing I18N for installer
 *
 * Revision 1.5  2005/07/24 12:58:26  goldin
 * Make message more descriptive
 *
 * Revision 1.5  2005/07/22 07:32:58  goldin
 * Fix problems with paths that have embedded spaces
 *
 * Revision 1.4  2002/09/25 17:23:25  goldin
 * Add PathChecker
 *
 * Revision 1.3  2002/09/20 16:27:30  goldin
 * Allow directories to have empty subdirs
 *
 * Revision 1.2  2002/09/03 18:03:03  goldin
 * Fix bugs in running off the CD
 *
 * Revision 1.1  2001/12/11 14:23:36  goldin
 * Add new validator
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.io.*;
import java.awt.*;

/** 
*   This class implements the Validator interface. It is used
*   to perform validation on the paths entered in the installation
*   program.
*/
public class InstallFileValidator implements Validator 
    {
    protected String lastErrorMessage = null;
    protected String lastErrorFile = null;
    protected DTextField lastProcessedField = null;
       
    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
        boolean bOk = true;
	lastErrorMessage = null;
	lastErrorFile = null;
	if (!(field instanceof DFileField))
   	    return true;  // should never be associated with anything
	                  // other than a file field.
	DFileField fld = (DFileField) field;
	lastProcessedField = fld;
        String currentValue = fld.getFieldValue();
	if ((currentValue == null) || (currentValue.length() == 0))
	    return true;
	boolean bPathData = fld.isPathData();
        if (!bPathData)
	    return true;   // we only deal with paths for this validator
	File tempFile = new File(currentValue);
        lastErrorFile = tempFile.getAbsolutePath();
	bOk = PathChecker.isPathOk(currentValue);
	if (!bOk)
	    {
	    lastErrorMessage = 
                  ApplicationManager.getTextSource().getI18NText(
               "%h01.9903","Subdirectories must have no embedded spaces: ");
	    }
        else if (!tempFile.exists())
	    {
            bOk = tempFile.mkdirs();
	    if (!bOk)
	        {
		lastErrorMessage = 
                  ApplicationManager.getTextSource().getI18NText(
                         "%h01.9900","Invalid directory name: ");
		}
	    }
	else if (!tempFile.isDirectory())
	    {
	    lastErrorMessage = 
                  ApplicationManager.getTextSource().getI18NText(
                         "%h01.9901","Not a directory: ");
	    }
	else
	    {
	    String fileNames[] = tempFile.list();
	    if ((fileNames != null) && (fileNames.length > 0))
	        { 
		for (int j = 0; (j < fileNames.length) && (bOk); j++)
		    {
		    File testfile = new File(tempFile.getAbsolutePath(),
					     fileNames[j]);
		    if (testfile.isDirectory())
		       {
		       String files2[] = testfile.list();
		       if ((files2 != null) && (files2.length > 0))
			   bOk = false;
		       }
		    else
		       {
	               bOk = false;
		       }
		    }
		if (!bOk)
                    {
		    lastErrorMessage = 
                         ApplicationManager.getTextSource().getI18NText(
                         "%h01.9902","Directory must be empty: ");
                    }
	        }
	    }
        if (bOk)
	    fld.setFieldValue(lastErrorFile);
	return bOk;
	}

      /**
       * Asks the validator to display an error box showing
       * information on the last error.
       */
    public void displayLastError()
        {
        if (lastErrorMessage == null)  // no error
	    return;
	if (lastProcessedField.isInChoiceDialog())
	    return;
	ErrorDisplay errDisplay = 
	    ApplicationManager.getErrorDisplay();
	Toolkit.getDefaultToolkit().beep();
	errDisplay.showError(TextKeys.ERROR, lastErrorMessage + lastErrorFile);
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

// End of FileValidator.java

