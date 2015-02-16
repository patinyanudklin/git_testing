/* 
 *
 *	filename FileListCallback.java
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
 *   $Id: FileListCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 *   $Log: FileListCallback.java,v $
 *   Revision 1.2  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.1  2006/11/13 14:13:34  goldin
 *   implementing UI for PCA
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
 *  This class implements the Callback interface. It is used to populate
 *  fields depending on a panel, based on data in the header of the
 *  image file specified in the field that invokes the callback.
 * @author  goldin*/
public class FileListCallback implements Callback 
    {
      /** Primary method of a callback class.
       *  Check if there's a value in this field (the file spec field)
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	boolean bEnable = true;
        DragonField numImagesField = null;
        DragonField inPrefixField = null;
        DragonField outPrefixField = null;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
        DragonUI mainApp = DragonUI.currentApplication;
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
            bEnable = true;
        else
            bEnable = false;

	numImagesField = parent.getField("^NB");
	inPrefixField = parent.getField("^I");
	outPrefixField = parent.getField("^O");
	if (numImagesField != null)
            numImagesField.setEnabled(bEnable);
	if (inPrefixField != null)
            inPrefixField.setEnabled(bEnable);
        if (bEnable)
            {
	    if (numImagesField != null)
		numImagesField.requestFocus();
            }
        else
            {
	    if (outPrefixField != null)
		outPrefixField.requestFocus();
            }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FileListCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


