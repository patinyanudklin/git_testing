/* FilterValCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/23/2001
 *
 * $Id: FilterValCallback.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $
 * $Log: FilterValCallback.java,v $
 * Revision 1.6  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.5  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/02/28 11:24:24  goldin
 * Implement callbacks for additional screens
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling the filter value field in the Filter 
 *  screen depending on the current value chosen for the kernel type
 *  field.
 * @author  goldin*/
public class FilterValCallback implements Callback 
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
	DragonField fvalField = parent.getField("^TV");
        fvalField.setEnabled(false);
	// now enable, based on the value chosen
	if (value.startsWith("U"))
	    {
	    fvalField.setEnabled(true);
	    fvalField.createFocusRequestor(200);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FilterValCallback.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of FilterValCallback.java

