/* FileValidator.java
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 4/9/2001
 *
 * $Id: FileValidator.java,v 1.23 2007/01/05 07:41:57 rudahl Exp $
 * $Log: FileValidator.java,v $
 * Revision 1.23  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.22  2005/02/06 09:00:25  goldin
 * Fix javadoc warnings
 *
 * Revision 1.21  2002/10/25 22:03:49  goldin
 * Only Kpath should be restricted to 8 chars
 *
 * Revision 1.19  2002/09/25 17:00:13  goldin
 * Check paths for more than 8 char subpaths
 *
 * Revision 1.18  2002/09/23 23:20:01  goldin
 * Fix compile bug
 *
 * Revision 1.17  2002/09/23 23:00:31  goldin
 * Make beep part of error display  rather than a reaction in the control
 *
 * Revision 1.16  2002/09/23 19:10:53  goldin
 * Don't give err msg if filechooser is up
 *
 * Revision 1.15  2002/05/29 17:53:39  goldin
 * Change message for =M when not allowed
 *
 * Revision 1.14  2002/04/29 22:36:06  goldin
 * Fine tune error message delivery
 *
 * Revision 1.13  2002/04/16 18:14:50  goldin
 * Use correct key for want to overwrite msg
 *
 * Revision 1.12  2002/04/02 00:09:02  goldin
 * Disable positioning if add is a replace
 *
 * Revision 1.11  2002/03/06 17:47:27  goldin
 * Don't set error key unless actually and error
 *
 * Revision 1.10  2002/02/20 15:37:11  goldin
 * Polygon files can be 'current' too, so expand the conditional test'
 *
 * Revision 1.9  2002/02/19 16:38:29  goldin
 * Don't check for current for color files
 *
 * Revision 1.8  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.7  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.6  2001/09/28 11:53:14  goldin
 * Fix bug in verifying memory files for fields where memory files are never allowed
 *
 * Revision 1.5  2001/07/18 15:25:30  goldin
 * Working to fix problems with handling of 'current' color scheme
 *
 * Revision 1.4  2001/06/29 17:30:16  goldin
 * Implemented handing of state info from reply files
 *
 * Revision 1.3  2001/06/28 14:06:07  goldin
 * Don't validate files with wildcards
 *
 * Revision 1.2  2001/04/24 14:14:20  goldin
 * Improve behavior and appearance of file and font choosers
 *
 * Revision 1.1  2001/04/17 13:42:35  rudahl
 * initial deposit, from tower h:\tmp\dragon\drag54\dragon_ui
 *
 *
 */

package com.grs.dragon.ui;
import javax.swing.*;
import java.awt.*;
import com.grs.gui.*;
import java.io.*;

/** 
*   This class implements the Validator interface. It is used
*   to validate the correctness of files, given the constraints
*   associated with the file field.
*/
public class FileValidator implements Validator 
    {
    protected String lastErrorKey = null;
    protected String lastErrorFile = null;
    protected DTextField lastProcessedField = null;
    protected static String xlatedCurrent = null;
    protected JOptionPane confirmDialog = null;
    protected String yes;
    protected String no;

      /**
       * Constructor creates a confirmation dialog to use for
       * output files that exist.
       */
    public FileValidator()
        {
	String message = 
            ApplicationManager.getTextSource().getI18NText(
		  "%h2.16","Really overwrite existing file?");
	yes =
            ApplicationManager.getTextSource().getI18NText(
                  TextKeys.YES,"YES");
	no =
            ApplicationManager.getTextSource().getI18NText(
                  TextKeys.NO,"NO");
        Object[] options = new Object[2];
	options[0] = yes;
	options[1] = no;
        confirmDialog = new JOptionPane(message,JOptionPane.WARNING_MESSAGE,
					JOptionPane.YES_NO_OPTION,null,
					options,options[0]);
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
	if (xlatedCurrent == null)
	    xlatedCurrent = mainApp.getTextSource().getI18NText(
					   TextKeys.CURRENT,"(Current)");
	// Check against allowed and valid memory files here...
        if (currentValue.startsWith("("))
	    {
            if (xlatedCurrent != null)
	        {
                if (((fld.getFileType() == DFileType.SIGNATURE) ||
		     (fld.getFileType() == DFileType.POLYGON)) &&
                    (currentValue.compareToIgnoreCase(xlatedCurrent) == 0))
		    {
                    bOk = statManager.isMemoryFileValid(fld.getFileType(),
                                                        currentValue);
		    if (bOk == false)
		        {
		        lastErrorKey = "%h2.15";
		        lastErrorFile = currentValue;
			}
		    }
		else
		    {
		    bOk = false;
		    lastErrorKey = "%e403";
		    lastErrorFile = currentValue;
		    }
                } 
	    }
	else if (currentValue.startsWith("="))
	    {
            String[] allowedMemoryFiles = fld.getAllowedMemoryFiles(); 
            if (allowedMemoryFiles != null)
	        {
		boolean bFound = false;
		for (int i = 0; i < allowedMemoryFiles.length; i++)
	            {
		    if (currentValue.compareTo(allowedMemoryFiles[i]) == 0)
		        {
		        bFound = true;
		        break;
		        }
		    }
		if (!bFound)
		    {
		    bOk = false;
		    }
		else // memory file is permitted, but is it currently valid?
		    {
		    bOk = statManager.isMemoryFileValid(fld.getFileType(),
						    currentValue);
		    }
		if (!bOk)
		    {
		    lastErrorKey = "%e403";
		    lastErrorFile = currentValue;
		    }
		}
            else // memory files never allowed
	        { 
		bOk = false;
		lastErrorKey = "%e354";
		lastErrorFile = currentValue;
		}
	    }
	else
	    {
	    boolean bExisting = fld.isExisting();
	    boolean bPathData = fld.isPathData();
            boolean bOverwriteWarning = fld.getOverwriteWarning();
	    DragonFileChooser chooser = fld.selectChooser();
	    File tempFile = new File(currentValue);
	    bOk = chooser.getModel().validateFile(tempFile.getParent(),
					       tempFile.getName(),
					       bExisting,bOverwriteWarning,
					       false);
	    if (!bOk)
	        { 
	        lastErrorKey = chooser.getModel().getLastErrorKey();
	        lastErrorFile = chooser.getModel().getLastErrorFile();
		if (lastErrorKey == TextKeys.EXISTS_ERR)
		     {
		     DragonPanel parent = field.getTopLevelPanel();
		     if (parent.isValidatingAll())
		       // only report a problem on final panel-wide validation
		         {
		         // about to overwrite existing file. Need
		         // to ask if this should continue
                         bOk = confirmOverwrite(fld);
			 }
		     else
		         {
			 bOk = true;
			 lastErrorKey = null;
			 lastErrorFile = null;
			 }
		     }
	        }
	    }
	return bOk;
	}

		       
      /**
       * Factorization. Displays dialog warning the user that the
       * file already exists.
       * @param field  Field being validated.
       * @return true if the user clicked on OK, meaning, continue,
       * false if the user clicked on cancel.
       */
    protected boolean confirmOverwrite(DragonField field)
       {
       boolean bOk = true;
       DragonUI mainWindow = (DragonUI) DragonUI.currentApplication;
       if (mainWindow != null) 
	   {
	   confirmDialog.setValue(null);
	   confirmDialog.setInitialValue(yes);
	   JDialog dlg = confirmDialog.createDialog(mainWindow,null);
	   mainWindow.setMessageDialogVisible(true);
	   dlg.setVisible(true);
	   Object val = confirmDialog.getValue();
	   mainWindow.setMessageDialogVisible(false);
	   if (val instanceof String)
	       {
	       String response = (String)val;
	       if (response.equals(yes))
	            {
		    bOk = true;
	            }
	       else
	            {
	            bOk = false;
	            }
	       }
	   }
        return bOk; 
        }

	 
      /**
       * Asks the validator to display an error box showing
       * information on the last error.
       */
    public void displayLastError()
        {
        if (lastErrorKey == null)  // no error
	    return;
	if (lastProcessedField.isInChoiceDialog())
	    return;
	ErrorDisplay errDisplay = 
	    DragonUI.currentApplication.getErrorDisplay();
	Toolkit.getDefaultToolkit().beep();
	errDisplay.showError(TextKeys.ERROR, lastErrorKey, lastErrorFile);
	lastErrorKey = null;
	lastErrorFile = null;
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
        cvsInfo = "\n@(#)  $Id: FileValidator.java,v 1.23 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of FileValidator.java

