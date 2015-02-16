/* ScalingCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/10/2001
 *
 * $Id: ScalingCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ScalingCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.1  2001/05/10 13:14:51  goldin
 * Continue implementation of SigFile and scaling callbacks
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling the upper & lower scaling bounds field 
 *  in the Subset screen depending on the current value chosen for the 
 *  scaling method
 * @author  goldin*/
public class ScalingCallback implements Callback 
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
	// disable the relevant field
	DragonField lowerField = parent.getField("^LBPS");
	DragonField upperField = parent.getField("^UBPS");
        if ((lowerField == null) || (upperField == null))
            return;
        lowerField.setEnabled(false);
        upperField.setEnabled(false);
	// now enable, based on the value chosen
	if (value.startsWith("U"))
	    {
	    lowerField.setEnabled(true);
	    upperField.setEnabled(true);
	    lowerField.createFocusRequestor(200);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ScalingCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of ScalingCallback.java

