/* VectorMergeCallback.java
 *
 * Copyright  2002-2007  Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 1/11/2002
 *
 *  $Id: VectorMergeCallback.java,v 1.5 2007/02/03 05:49:34 goldin Exp $
 *  $Log: VectorMergeCallback.java,v $
 *  Revision 1.5  2007/02/03 05:49:34  goldin
 *  Fix focus problem in VEC panel
 *
 *  Revision 1.4  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.3  2002/08/26 15:47:21  goldin
 *  Disable merge if bkgrd is =C
 *
 *  Revision 1.2  2002/01/23 16:07:15  goldin
 *  Enable/disable VEC fields depending on existence of background image
 *
 *  Revision 1.1  2002/01/11 15:25:42  goldin
 *  Add new callback to enable/disable new color file for vectors field
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of enabling or disabling the color file for vectors field in the 
 *  VEC screen depending on the current value chosen for 
 * 'combine with background'.
 * <p>
 * As of 1/23/02, we also use this callback on the file field of VEC,
 * to enable the checkbox if and only if the user enters a valid
 * background file which is not "=C"
 *
 * @author  goldin*/
public class VectorMergeCallback implements Callback 
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
        if (field.getName().compareTo("^FRV") == 0)
	    {
	    DragonField mergeField = parent.getField("^CV");
	    DragonField clfField = parent.getField("^CFGEOM");
	    if ((mergeField == null) || (clfField == null))
	        return;
	    if ((value == null) || (value.length() == 0) ||
                (value.compareToIgnoreCase("=C") == 0))
	         {
	         mergeField.setEnabled(false);
	         clfField.setEnabled(false);
		 }
	    else
	         {
	         clfField.setEnabled(true);
	         mergeField.setEnabled(true);
		 //mergeField.requestFocus();
		 }
	    }
	else
	    {
	    if ((value == null) || (value.length() == 0))
	        return;
	    DragonField clfField2 = parent.getField("^CFGEOM2");
	    if (clfField2 == null)
	        return;
	    // now enable, based on the value chosen
	    if (value.startsWith("Y"))
	        {
	        clfField2.setEnabled(false);
		}
	    else 
	        {
		clfField2.setEnabled(true);
	        }
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: VectorMergeCallback.java,v 1.5 2007/02/03 05:49:34 goldin Exp $ \n";
	}
    }

// End of VectorMergeCallback.java

