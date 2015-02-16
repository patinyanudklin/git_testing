/* RecodeCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/28/2001
 *
 * $Id: RecodeCallback.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $
 * $Log: RecodeCallback.java,v $
 * Revision 1.6  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.5  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.2  2001/02/28 11:50:12  goldin
 * Extend mouse handling to checkbuttons and push buttons
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
 *  of enabling or disabling fields in the Recode screen depending on
 *  the current value chosen for 'recoding method'.
 * @author  goldin*/
public class RecodeCallback implements Callback 
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
	DragonField val1Field = parent.getField("^VO1");
	DragonField val2Field = parent.getField("^VO2");
	DragonField newValField = parent.getField("^VN");
	DragonField tableField = parent.getField("^FTR");
	// now enable, based on the value chosen
	if (value.startsWith("V"))
	    {
	    val1Field.setEnabled(true);
	    val2Field.setEnabled(true);
	    newValField.setEnabled(true);
	    }
	else 
	    {
	    val1Field.setEnabled(false);
	    val2Field.setEnabled(false);
	    newValField.setEnabled(false);
 	    }
        if (value.startsWith("F"))
	    {
	    tableField.setEnabled(true);
	    }
	else 
	    {
	    tableField.setEnabled(false);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: RecodeCallback.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of RecodeCallback.java

