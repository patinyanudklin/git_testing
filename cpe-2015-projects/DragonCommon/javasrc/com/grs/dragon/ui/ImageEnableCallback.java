/* 
 * ImageEnableCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/14/2001
 *
 * $Id: ImageEnableCallback.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ImageEnableCallback.java,v $
 * Revision 1.7  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.6  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.5  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.4  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.2  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.1  2001/05/14 10:47:42  goldin
 * Implement callback for supervised classification, to enable or disable image file fields
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It is used on a
 *  variety of panels where the number of bands of image data to
 *  be entered depends on the number of bands in the signature file.
 *  The callback is associated with a field where the user enters the
 *  signature file name. It reads the signature file and then enables
 *  the first "n" image file fields, where "n" matches the number of 
 *  bands in the signatures.
 * @author  goldin
 */
public class ImageEnableCallback implements Callback 
    {
      /** Primary method of a callback class.
       *  Process sigFile if necessary, and set values in the
       *  appropriate combo box.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        SigFileProcessor sigFileProc = null;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
        DragonUI mainApp = DragonUI.currentApplication;
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
	    return;
        DragonField f1Field = parent.getField("^F1C");
        DragonField f2Field = parent.getField("^F2C");
        DragonField f3Field = parent.getField("^F3C");
        DragonField f4Field = parent.getField("^F4C");
	// reset all to disabled 
	f1Field.setEnabled(false);
	f2Field.setEnabled(false);
	f3Field.setEnabled(false);
	f4Field.setEnabled(false);
	// determine if there is a current sig file and if so,
	// if that is what the user requested
        SigFileProcessor currentSigs = mainApp.getCurrentSigProcessor();
        if ((currentSigs != null) && (currentSigs.isInitialized()) &&
	    (value.startsWith("(")) )
            {
            sigFileProc = currentSigs;
            }
        else
	    {
	    sigFileProc = new SigFileProcessor(value);
	    if (!sigFileProc.isInitialized())
	         {
                 UiErrorDisplay errDisp = (UiErrorDisplay)
                      ApplicationManager.getErrorDisplay();
		 errDisp.sendError(sigFileProc.getErrorMessage());
		 return;
		 }
            }
        int bandCount = sigFileProc.getBandCount();
	switch (bandCount)
	    {
	    case 4:
	         f4Field.setEnabled(true);
		 // fall through
	    case 3:
	         f3Field.setEnabled(true);
		 // fall through
	    case 2:
	         f2Field.setEnabled(true);
		 // fall through
	    default:
	         f1Field.setEnabled(true);
		 f1Field.createFocusRequestor(200);
	    }
	mainApp.setCurrentSigProcessor(sigFileProc);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ImageEnableCallback.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of ImageEnableCallback.java

