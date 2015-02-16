/* SamplePathCallback.java
 *
 * Copyright Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 12/6/2001
 *
 * $Id: SamplePathCallback.java,v 1.1 2001/12/06 14:55:18 goldin Exp $
 * $Log: SamplePathCallback.java,v $
 * Revision 1.1  2001/12/06 14:55:18  goldin
 * Add callbacks for setting defaults
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of setting DPATH and WPATH defaults based on the data entered\
 *  in the sample data path field.
 */
public class SamplePathCallback implements Callback 
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
	DragonField dpathField = parent.getField("DPATH");
	DragonField wpathField = parent.getField("WPATH");
	dpathField.setFieldValue(value);
	wpathField.setFieldValue(value);
	}

    }


