/* 
 *
 *	filename ImportImageTypeCallback.java
 *		$Revision: 1.3 $ $Date: 2007/01/05 07:41:57 $	
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
 *   $Id: ImportImageTypeCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $
 *   $Log: ImportImageTypeCallback.java,v $
 *   Revision 1.3  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.2  2006/11/27 14:12:30  goldin
 *   Set defaults when you enable fields
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
 *  enable or disable image description fields on the Custom Import
 *  tab, based on whether the mode is Dragon or Foreign.
 **/
public class ImportImageTypeCallback implements Callback 
    {
    static String fldIds[] = {"^LINE","^PIX","^HEAD","^BANDS","^SIZE"};

      /** Primary method of a callback class.
       *  Check if there's a value in this field (the file spec field)
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	boolean bEnable = false;
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
	if (value.startsWith("F"))
            bEnable = true;
        else
            bEnable = false;
        for (int i = 0; i < fldIds.length; i++)
            {
            descriptionField = parent.getField(fldIds[i]);
            if (descriptionField != null)
                {
                descriptionField.setEnabled(bEnable);
		descriptionField.setFieldValue(
				descriptionField.getDefaultValue());
		}
            }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ImportImageTypeCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


