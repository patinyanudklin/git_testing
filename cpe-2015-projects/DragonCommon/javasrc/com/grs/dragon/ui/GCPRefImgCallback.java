/* GCPRefImgCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 4/19/2002
 *
 * $Id: GCPRefImgCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $
 * $Log: GCPRefImgCallback.java,v $
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2005/11/29 06:04:49  goldin
 * don't uppercase GCP filename
 *
 * Revision 1.1  2002/04/19 22:29:23  goldin
 * Add callback to set def. ref GCP filename
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of setting the default reference GCP file based on the input
 *  in the Reference Image File field.
 * @author  goldin*/
public class GCPRefImgCallback implements Callback 
    {
    
      /** Primary method of a callback class.
       *  Enable or disable fields based on the passed field's value.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	String gcpFileValue = null;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
	    return;
	DragonField outputCoordField = parent.getField("^FCO");
	int end = value.toLowerCase().indexOf(".img");
	if (end >= 0)
	    {
	    gcpFileValue = 
		  value.substring(0,end) + ".gcp";
	    outputCoordField.setFieldValue(gcpFileValue);
	    } 
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: GCPRefImgCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of Callback.java

