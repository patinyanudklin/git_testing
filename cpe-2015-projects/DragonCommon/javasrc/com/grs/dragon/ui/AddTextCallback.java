/* AddTextCallback.java
 *
 * Copyright  2002-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 4/1/2002
 *
 * $Id: AddTextCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 * $Log: AddTextCallback.java,v $
 * Revision 1.2  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.1  2002/04/02 00:09:02  goldin
 * Disable positioning if add is a replace
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of clearing and disabling the position fields in the Add Text 
 *  if the user selects "replace last text"
 * @author  goldin*/
public class AddTextCallback implements Callback 
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
	DragonField lineField = parent.getField("^TXPL");
	DragonField pixelField = parent.getField("^TXPP");
	// now enable, based on the value chosen
	if (value.startsWith("N"))
	    {
	    lineField.setEnabled(true);
	    pixelField.setEnabled(true);
	    }
	else 
	    {
	    lineField.setEnabled(false);
	    pixelField.setEnabled(false);
 	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: AddTextCallback.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of AddTextCallback.java

