/* ClfFileValidator.java
 *
 * Copyright  2002-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 4/19/2002
 *
 * $Id: ClfFileValidator.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ClfFileValidator.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2005/07/24 13:12:36  goldin
 * set the font for color dialog
 *
 * Revision 1.4  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.3  2005/02/06 09:00:25  goldin
 * Fix javadoc warnings
 *
 * Revision 1.2  2002/04/29 22:36:06  goldin
 * Fine tune error message delivery
 *
 * Revision 1.1  2002/04/19 22:29:37  goldin
 * Add special validator for color files
 *
 *
 */

package com.grs.dragon.ui;
import javax.swing.*;
import javax.swing.plaf.*;
import com.grs.gui.*;
import java.io.*;

/** 
*   This class implements the Validator interface. It is used
*   to validate the correctness of color files, given the constraints
*   associated with the file field.
*/
public class ClfFileValidator extends FileValidator 
    {
      /**
       * Constructor creates a confirmation dialog to use for
       * output files that exist.
       */
    public ClfFileValidator()
        {
	super();
	}

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
        boolean bOk = super.isValid(field);
	if (bOk)   // check length
	    {
	    String value = field.getFieldValue();
	    int pos = (value.lastIndexOf(File.separator)) + 1;
	    int pos2 = value.lastIndexOf(".");
	    if (pos2 - pos > 8)
	        {
		bOk = false;
		lastErrorKey = "%e437";
		lastErrorFile = value;
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
	   dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
	   SwingUtilities.updateComponentTreeUI(dlg);
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

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ClfFileValidator.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of ClfFileValidator.java

