/**
 * SaveRulesCallback.java
 *
 *
 *    Callback to handle saving a set of rules from the rules list box in the
 *    Rule Creation operation.
 *
 *	Copyright 2007  Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *    
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *
 * $Id: SaveRulesCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SaveRulesCallback.java,v $
 * Revision 1.2  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.1  2007/01/02 05:19:19  goldin
 * Complete behavioral code for Rule Creation panel
 *
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.io.*; 
import java.awt.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It retrieves the
 *  contents of the currently defined rules from the list box
 *  control and saves them in the appropriate file.
 */
public class SaveRulesCallback implements Callback
    {
    protected final static String LISTBOXNAME = "^RULES";
    protected final static String FILEFLDNAME = "^FRO";

    protected String lastErrorKey = null;
    protected String extraInfo = null;

      /** Primary method of a callback class.
       *  Gets the rules from the list box and saves them
       * in the output file (whose name it gets from the 
       * parent panel as well.
       * @param  field Field whose value will determine the
       *   effects of the callback. (OK button)
       */
    public void executeCallback(DragonField field)
        {
	lastErrorKey = null;
	extraInfo = null;    
        DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
	    return;
        DListBox listBoxFld = (DListBox) parent.getField(LISTBOXNAME);
        DragonField fileFld = parent.getField(FILEFLDNAME);
        String filename = fileFld.getFieldValue();
	String ruleContents = listBoxFld.getFieldValue();
	if ((ruleContents == null) || (ruleContents.length() == 0))
	    {
	    lastErrorKey = TextKeys.MISSINGREQUIRED;
	    extraInfo = listBoxFld.getLabelText();
            } 
	else if ((filename == null) || (filename.length() == 0))
	    {
	    lastErrorKey = TextKeys.MISSINGREQUIRED;
	    extraInfo = fileFld.getLabelText();
            } 
        if (lastErrorKey == null) // everything seems okay
            {
            try 
                {
	        BufferedWriter writer = new BufferedWriter(
				     new FileWriter(filename));
                writer.write(ruleContents); 
		writer.newLine();
		writer.close();
		}
	    catch (IOException ioe)
                {
		lastErrorKey = "%e7000.8";
                extraInfo = filename;
		}
            }
        if (lastErrorKey != null)
            displayLastError();
	else
            DragonUI.currentApplication.showDefaultPanel();
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

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SaveRulesCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

