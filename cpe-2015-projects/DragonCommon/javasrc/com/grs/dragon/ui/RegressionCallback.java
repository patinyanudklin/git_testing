/* RegressionCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/14/2001
 *
 * $Id: RegressionCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: RegressionCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/07/25 11:53:19  goldin
 * fix handling of CAL output field
 *
 * Revision 1.1  2001/05/14 11:07:41  goldin
 * Add callback to handle regression output file name
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It is used in the
 *  G/CAL operation to set the name of the regression report file based 
 *  on the value entered for the coefficient file name.
 * @author  goldin*/
public class RegressionCallback implements Callback 
    {
      /** Primary method of a callback class.
       *  Create regression report filename based on coefficient filename.
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
	DFixedText labelField = (DFixedText) parent.getField("^ROFILE");
        if (labelField == null)
            return;
        String labelText = labelField.getLabelText();
	int pos = labelText.indexOf(":");
        if (pos < labelText.length() - 2)
            labelText = labelText.substring(0,pos+1);
	String value = field.getFieldValue();
	if ((value != null) && (value.length() > 0))
	    {
            int end = value.toUpperCase().indexOf(".COF");
	    if (end >= 0)
	        {
		labelText = labelText + " " + 
		  value.toUpperCase().substring(0,end) + ".OUT";
		} 
	    labelField.setLabelText(labelText);
	    }
        else
	    {
            labelField.resetLabelText();
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: RegressionCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of RegressionCallback.java

