/* GCPCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/20/2001
 *
 * $Id: GCPCallback.java,v 1.9 2007/01/07 11:33:38 goldin Exp $
 * $Log: GCPCallback.java,v $
 * Revision 1.9  2007/01/07 11:33:38  goldin
 * Use multifile control for PCA - remove display offsets for now
 *
 * Revision 1.8  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.7  2006/12/25 03:29:41  goldin
 * Set default in new initial line/pixel fields
 *
 * Revision 1.6  2002/03/19 21:14:04  goldin
 * Enable the output GCP field for Image source
 *
 * Revision 1.5  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/06/18 13:00:04  goldin
 * Add focus request to callback
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/02/20 18:29:39  goldin
 * Add new callback classes
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling fields in the GCP screen depending on
 *  the current value chosen for 'source for reference coordinates'.
 * @author  goldin*/
public class GCPCallback implements Callback 
    {
    
      /** Primary method of a callback class.
       *  Enable or disable fields based on the passed field's value.
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
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
	    return;
	// disable all the relevant fields
	DragonField refImgField = parent.getField("^FBG");
        refImgField.setEnabled(false);
        
	DragonField refILField = parent.getField("^ILGR");
        if (refILField != null)
            refILField.setEnabled(false);
	DragonField refIPField = parent.getField("^IPGR");
        if (refIPField != null)
            refIPField.setEnabled(false);
       
	DragonField inputCoordField = parent.getField("^FCI");
        inputCoordField.setEnabled(false);
	DragonField outputCoordField = parent.getField("^FCO");
        outputCoordField.setEnabled(false);
	// now enable, based on the value chosen
	if (value.startsWith("I"))
	    {
	    refImgField.setEnabled(true);
	    if (refILField != null)
		{
		refILField.setEnabled(true);
		refILField.setFieldValue(refILField.getDefaultValue());
		}
	    if (refIPField != null)
		{
		refIPField.setEnabled(true);
		refIPField.setFieldValue(refIPField.getDefaultValue());
		}
	    outputCoordField.setEnabled(true);
	    refImgField.createFocusRequestor(200);
	    }
	else if (value.startsWith("F"))
	    {
	    inputCoordField.setEnabled(true);
	    inputCoordField.createFocusRequestor(200);
	    }
	else if (value.startsWith("K"))
	    {
	    outputCoordField.setEnabled(true);
	    outputCoordField.createFocusRequestor(200);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: GCPCallback.java,v 1.9 2007/01/07 11:33:38 goldin Exp $ \n";
	}
    }

// End of Callback.java

