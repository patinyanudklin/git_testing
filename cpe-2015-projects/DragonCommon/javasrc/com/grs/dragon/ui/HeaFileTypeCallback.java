/* 
 * HeaFileTypeCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/12/2001
 *
 * $Id: HeaFileTypeCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: HeaFileTypeCallback.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/12 11:41:05  goldin
 * New callbacks for HEA panel
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It is used to enable or
 *  disable the class names panel based on whether the user enters
 *  a filetype of C/L or I.
 * @author  goldin*/
public class HeaFileTypeCallback extends HeaderCallback 
    {
      /** Primary method of a callback class.
       *  Process sigFile if necessary, and set values in the
       *  appropriate combo box.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
        DragonUI mainApp = DragonUI.currentApplication;
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
	    return;
        if (value.startsWith("I"))
	    parent.enableTab(1,false);
        else
	    parent.enableTab(1,true);
        DImageHeader header = mainApp.getMemoryHeader();
        if ((header == null) || (!header.isInitialized()))
             return; 
        if (header.getNumlabels() > 0)
	     {
	     processClassNames(parent,header);
	     }
	else
	     {
	     clearClassNames(parent,header);
	     }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: HeaFileTypeCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


