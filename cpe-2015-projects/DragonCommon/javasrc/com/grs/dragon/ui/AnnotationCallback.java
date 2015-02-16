/* AnnotationCallback.java
 *
 * Copyright  2004-2007  Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 12/15/2004
 *
 * $Id: AnnotationCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $
 * $Log: AnnotationCallback.java,v $
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2004/12/28 07:21:53  goldin
 * Fix name of modified field
 *
 * Revision 1.1  2004/12/15 03:50:59  goldin
 * Add callback to handle annotation option more intelligently; update makefile and panel file
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling the Annotation option field. 
 *  If the user chooses =M the field is enabled, otherwise, it is disabled.
 * @author  goldin*/
public class AnnotationCallback implements Callback 
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
	DragonField annotField = parent.getField("^AO");
        // check for nulls - not all panels that have a color/gray
	// choice have these additional fields.
        if (annotField != null)
            annotField.setEnabled(false);
	// now enable, based on the value chosen
	if ((value.startsWith("=M")) && (annotField != null))
	    {
	    annotField.setEnabled(true);
	    annotField.setFieldValue(annotField.getDefaultValue());
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: AnnotationCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of AnnotationCallback.java

