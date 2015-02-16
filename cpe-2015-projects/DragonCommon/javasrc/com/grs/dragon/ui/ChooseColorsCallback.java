/**
 * ChooseColorsCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: ChooseColorsCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ChooseColorsCallback.java,v $
 * Revision 1.2  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.1  2005/09/15 08:30:09  goldin
 * Move color chooser to UI package, invoke directly from the UI
 *
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.io.File; 
import java.awt.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It invokes
 *  the color chooser in order to handle the interactions in
 *  COL, which now by-pass the server.
 */
public class ChooseColorsCallback implements Callback
    {
      /** Primary method of a callback class.
       *  Displays the dialog and waits for user input.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
	    return;
	DragonField badField = parent.checkFieldValidity();
	if (badField != null)
	    {
	    Toolkit.getDefaultToolkit().beep();
	    badField.getValidator().displayLastError();
	    badField.requestFocus();
	    return;
	    }
	badField = parent.checkRequiredFields();
	if (badField != null)
	    {
	    UiErrorDisplay errDisp = 
	      (UiErrorDisplay) ApplicationManager.getErrorDisplay();
	    errDisp.showError(null,TextKeys.MISSINGREQUIRED,
			      badField, parent);
	    badField.requestFocus();
	    return;
	    }
        DragonField baseClfField = parent.getField("^CFB");
	DragonField newClfField = parent.getField("^CFS");
	DragonField clsImgField = parent.getField("^FNC");
	if ((baseClfField == null) ||
            (newClfField == null) ||
	    (clsImgField == null))
	    {
	    UiErrorDisplay errDisp = 
	      (UiErrorDisplay) ApplicationManager.getErrorDisplay();
	    errDisp.showError(null,TextKeys.MISSINGREQUIRED,
			      badField, parent);
            }
	else
	    {
	    String baseClfFile = baseClfField.getFieldValue();
	    String newClfFile = newClfField.getFieldValue();
	    String classifiedImgFile = clsImgField.getFieldValue();
	    /* a negative return means can't fine color file */
	    if (DragonUI.colorChooser.chooseColors(
                      baseClfFile,newClfFile,classifiedImgFile) < 0)
	       {
	       UiErrorDisplay errDisp = 
	         (UiErrorDisplay) ApplicationManager.getErrorDisplay();
	       errDisp.showError(TextKeys.ERROR,"%e600",baseClfFile);
	       }
            }

        DragonUI.currentApplication.showDefaultPanel();
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ChooseColorsCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

