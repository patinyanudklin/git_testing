/* 
 *
 *	filename ImportImageTypeCallback.java
 *		$Revision: 1.2 $ $Date: 2007/01/05 07:41:57 $	
 *	Copyright  2006-2007   Global Software Institute
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
 ****************************************************************
 *   $Id: ImportModeCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 *   $Log: ImportModeCallback.java,v $
 *   Revision 1.2  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.1  2006/11/18 10:52:55  goldin
 *   Implementing Import user interface
 *
 *
 *
 *******************************************************************
 *   Callback for PCA response panel, enables or disables
 *   the number of images and input prefix fields, depending
 *   on whether the user specifies a file list file (specification file)
 *
 *   Created by Sally Goldin, 13 November 2006
 *	
 ****************************************************************
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It is used to 
 *  enable or disable various output parameter fields on the Custom Import
 *  tab, based on whether the mode is Copy, Subset, Reduce or Extract.
 **/
public class ImportModeCallback implements Callback 
    {
    static String fldIds[] = {"^ILI","^IPI","^NLI","^NPI","^SKIP","^BI"};


      /** Primary method of a callback class.
       *  Check if there's a value in this field (the file spec field)
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	int i = 0;
	boolean fldEnableFlags[] = new boolean[fldIds.length];
        DragonField descriptionField = null;;
        DragonField pixField = null;
        DragonField headerField = null;
        DragonField bandField = null;
        DragonField sizeField = null;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
        DragonUI mainApp = DragonUI.currentApplication;
	String value = field.getFieldValue();
        for (i = 0; i < fldIds.length; i++)
            fldEnableFlags[i] = false;

	if (value.startsWith("S"))
            {
	    for (i=0; i < 4; i++)
		fldEnableFlags[i] = true;
            }
        else if (value.startsWith("R"))
            {
	    fldEnableFlags[4] = true;
            }
        else if (value.startsWith("E"))
            {
	    fldEnableFlags[5] = true;
            }
        for (i = 0; i < fldIds.length; i++)
            {
            descriptionField = parent.getField(fldIds[i]);
            if (descriptionField != null)
                descriptionField.setEnabled(fldEnableFlags[i]);
            }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ImportModeCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


