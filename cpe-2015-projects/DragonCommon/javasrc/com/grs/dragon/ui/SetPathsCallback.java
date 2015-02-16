/**
 * SetPathsCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: SetPathsCallback.java,v 1.13 2007/02/11 09:22:03 goldin Exp $
 * $Log: SetPathsCallback.java,v $
 * Revision 1.13  2007/02/11 09:22:03  goldin
 * Disable kpath and cpath fields, enable first img file for sup class.
 *
 * Revision 1.12  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.11  2005/12/05 09:38:36  goldin
 * Fix problem with WPATH not getting set
 *
 * Revision 1.10  2005/10/21 14:02:44  goldin
 * Working on getting status info from persistent DB
 *
 * Revision 1.9  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.8  2001/11/29 16:12:33  goldin
 * Add common pkg import
 *
 * Revision 1.7  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.6  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.5  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.4  2001/10/08 15:01:41  goldin
 * Send -DPATH cmd to server
 *
 * Revision 1.3  2001/05/07 14:21:15  goldin
 * Modify focus lost to always call validator
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.io.File; 
import java.awt.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  setting of new values in the config file and the writing
 *  of a new config file version.
 *  As of 10/21/05 it also sends a command to the
 *  script server to set the appropriate paths
 *  in the persistent database.
 */
public class SetPathsCallback implements Callback
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
	String dpathValue = null;
	String wpathValue = null;
	String cpathValue = null;
	String kpathValue = null;
        DragonField dpath = parent.getField("^FMD");
        if (dpath != null)
            dpathValue = dpath.getFieldValue();
	DragonField wpath = parent.getField("^FMW");
        if (wpath != null)
            wpathValue = wpath.getFieldValue();
	DragonField kpath = parent.getField("^FMK");
        if (kpath != null)
            kpathValue = kpath.getFieldValue();
	DragonField cpath = parent.getField("^FMC");
        if (cpath != null)
            cpathValue = cpath.getFieldValue();
	String newValue = null;
	newValue = dpathValue;          ;
	if ((newValue != null) && (newValue.length() > 0))
	    {            
	    if (newValue.endsWith(File.separator))
	      {
		newValue = newValue.substring(0,newValue.length()-1);
		// strip final slash or backslash
	      }
	    DragonUI.cfgProcessor.setDpath(newValue);                
	    DragonUI.currentApplication.getCommandForwarder().sendCommandToServer("-SETPERSIST CURRENT\tDPATH\t"+ newValue.replace('\\','/'));          
	    }
	newValue = wpathValue;    
	if ((newValue != null) && (newValue.length() > 0))
	    {
	    DragonUI.cfgProcessor.setWpath(newValue);                
	    DragonUI.currentApplication.getCommandForwarder().sendCommandToServer("-SETPERSIST CURRENT\tWPATH\t"+ newValue.replace('\\','/'));          
	    }
	newValue = kpathValue;
	if ((newValue != null) && (newValue.length() > 0))
 	   DragonUI.cfgProcessor.setKpath(newValue);                
	newValue = cpathValue;
	if ((newValue != null) && (newValue.length() > 0))
	         DragonUI.cfgProcessor.setCpath(newValue);                
	DragonUI.cfgProcessor.writeNewFile();
        DragonUI.currentApplication.showDefaultPanel();
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SetPathsCallback.java,v 1.13 2007/02/11 09:22:03 goldin Exp $ \n";
	}
    }

