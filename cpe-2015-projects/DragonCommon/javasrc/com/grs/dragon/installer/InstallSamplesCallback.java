/* InstallSamplesCallback.java
 *
 * Copyright Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 12/6/2001
 *
 * $Id: InstallSamplesCallback.java,v 1.2 2002/09/20 16:25:44 goldin Exp $
 * $Log: InstallSamplesCallback.java,v $
 * Revision 1.2  2002/09/20 16:25:44  goldin
 * Install samples by default
 *
 * Revision 1.1  2001/12/06 14:55:18  goldin
 * Add callbacks for setting defaults
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling fields and setting values 
 *  in the sample data screen depending on
 *  the current value chosen for "Install sample images.
 */
public class InstallSamplesCallback implements Callback 
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
	DragonField sampleField = parent.getField("SAMPPATH");
	// now enable, based on the value chosen
	if (value.startsWith("Y"))
	    {
	    sampleField.setEnabled(true);
	    }
	else
	    {
	    sampleField.setEnabled(false);
	    }
	}
    }


