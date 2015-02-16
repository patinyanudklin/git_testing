/* DisplayTypeCallback.java
 *
 * Copyright  2001-2007  Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 7/6/2001
 *
 * $Id: DisplayTypeCallback.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DisplayTypeCallback.java,v $
 * Revision 1.7  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.6  2006/01/20 08:42:03  goldin
 * Disable the 'same as last' if there is no current color file
 *
 * Revision 1.5  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/10/08 11:55:57  goldin
 * Set default val when enabling color selection
 *
 * Revision 1.2  2001/08/28 11:36:21  goldin
 * Fix null ptr bu; not all display opt uses have color file fields
 *
 * Revision 1.1  2001/07/06 16:51:04  goldin
 * Add class to control color option based on display type (Enh)
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling the Color Option field, 
 *  if the user chooses a Display Type of "C", otherwise, disabling
 *  it.
 * @author  goldin*/
public class DisplayTypeCallback implements Callback 
    {
    
      /** Primary method of a callback class.
       *  Enable or disable field based on the passed field's value.
       * @param  field Field whose value will determine the
       *   effects of the callback (display type field).
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
	DragonField clrOptField = parent.getField("^C");
        // check for nulls - not all panels that have a color/gray
	// choice have these additional fields.
        if (clrOptField != null)
            clrOptField.setEnabled(false);
	DragonField clrFileField = parent.getField("^CF");
        if (clrFileField != null)
            clrFileField.setEnabled(false);
	// now enable, based on the value chosen
	if ((value.startsWith("C")) && (clrOptField != null))
	    {
	    clrOptField.setEnabled(true);
	    clrOptField.setFieldValue(clrOptField.getDefaultValue());
            if (!(parent.getMemoryFilter().isMemoryFileValid(DFileType.COLOR,"(Current)")))
	       {
 	       ((DRadioBox)clrOptField).enableChoice(1,false);
	       }
            else
	       {
 	       ((DRadioBox)clrOptField).enableChoice(1,true);
	       }
	    clrOptField.createFocusRequestor(200);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DisplayTypeCallback.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of DisplayTypeCallback.java

