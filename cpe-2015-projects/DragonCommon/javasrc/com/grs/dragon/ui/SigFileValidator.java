/* SigFileValidator.java
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/22/2001
 *
 * $Id: SigFileValidator.java,v 1.8 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SigFileValidator.java,v $
 * Revision 1.8  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.7  2002/03/22 23:52:49  goldin
 * Fix misc. bugs
 *
 * Revision 1.6  2002/01/10 18:16:19  goldin
 * Transform (Current)
 *
 * Revision 1.5  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.4  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/10/30 13:05:08  goldin
 * Associate correct validators and callbacks with ANN and C/EDI fields
 *
 * Revision 1.2  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.1  2001/05/22 12:05:54  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.File;

/**
 * This class extends the FileValidator class. It not only
 * verifies that the field value is correct, it also makes sure
 * that the signature file in question has the same number of
 * bands as the primary signature file. 
 */
public class SigFileValidator extends FileValidator
    {


    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
        boolean bOk = super.isValid(field);
        if (!bOk)
             return bOk;
        String value = field.getFieldValue();
        if ((value == null) || (value.length() == 0))
            return true;
	if (value.indexOf("*") > 0)
	    {
	    lastErrorKey = "%e403";
	    lastErrorFile = value;
	    return false;
	    }

	if (value.startsWith("("))
	    value = ApplicationManager.getTempPath() +
	            File.separator + "$$S.SIG";
	SigFileProcessor sigFileProc = new SigFileProcessor(value);
	if (!sigFileProc.isInitialized())
	    {
            UiErrorDisplay errDisp = 
	      (UiErrorDisplay) ApplicationManager.getErrorDisplay();
	    errDisp.sendError(sigFileProc.getErrorMessage());
	    return false;
            }
        field.setUserData(sigFileProc);
        String myId = field.getName();
        String otherId = null;
        if (myId.equals("^FSACOP"))
            otherId = "^FSICOP";
        else if (myId.equals("^FSA"))
            otherId = "^FSICOM";
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
            return true;
        if (otherId != null) 
	    {
	    DragonField otherField = parent.getField(otherId);
	    if (otherField == null) 
	        return true;
	    SigFileProcessor primary = 
	        (SigFileProcessor) otherField.getUserData();
	    if (primary == null)
	        return true;
	    if (primary.getBandCount() != sigFileProc.getBandCount())
	        {
		lastErrorKey = "%h9.0";
		lastErrorFile = value;
		return false;
	        }
            }
        else if (myId.equals("^FSICOP"))
	    {
	    // if primary already has 16 sigs, cannot copy any more in.
            if (sigFileProc.getSigCount() >= 16)
	        {
		lastErrorKey = "%h1.15";
		lastErrorFile = value;
		return false;
                }
	    }
	return true;
        }



    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SigFileValidator.java,v 1.8 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

