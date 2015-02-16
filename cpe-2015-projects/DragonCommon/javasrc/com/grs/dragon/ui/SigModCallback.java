/* 
 * SigModCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/12/2001
 *
 * $Id: SigModCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SigModCallback.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/12 14:02:06  goldin
 * Add new callback and validator for c/edi/mod
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It is used to 
 *  fill the upper and lower bounds values when the user chooses
 *  a signature.
 * @author  goldin
 */
public class SigModCallback implements Callback 
    {
      /** Primary method of a callback class.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    return;
        DragonUI mainApp = DragonUI.currentApplication;
        // get the current signatures - if not set something
        // is very wrong.
        SigFileProcessor currentSigs = mainApp.getCurrentSigProcessor();
	if (currentSigs == null)
            return;
	String value = field.getFieldValue();
        int sigIndex = currentSigs.getSignatureIndex(value);
        if (sigIndex < 0) // should never be
	    return;
	int bandCount = currentSigs.getBandCount();
	for (int i = 0; i < bandCount; i++)
	     {
             String suffix = String.valueOf(i+1);
             String upperName = "^UB" + suffix;
             String lowerName = "^LB" + suffix;
             DragonField uFld = parent.getField(upperName);
             if (uFld != null)
                  uFld.setFieldValue(
                       String.valueOf(currentSigs.getSigUpper(sigIndex,i)));
             DragonField lFld = parent.getField(lowerName);
             if (lFld != null)
                  lFld.setFieldValue(
                       String.valueOf(currentSigs.getSigLower(sigIndex,i)));
	     }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SigModCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


