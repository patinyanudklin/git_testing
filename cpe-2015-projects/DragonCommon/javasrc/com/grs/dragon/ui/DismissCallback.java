/* DismissCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/20/2001
 *
 * $Id: DismissCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DismissCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/02/20 18:29:39  goldin
 * Add new callback classes
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of dismissing the current response panel or dialog.
 *  This callback is associated with Cancel buttons.
 * @author  goldin*/
public class DismissCallback implements Callback 
    {
    
      /** Primary method of a callback class.
       *   Simply dismiss the current dialog or response panel.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */

    public void executeCallback(DragonField field)
        {
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
	    return;
	if (parent.isPopup())
	    {
	    JDialog dlg = DragonUI.currentApplication.getDialog(parent.getName());
	    dlg.hide();
	    }
	else
	    {
	    DragonUI.currentApplication.showDefaultPanel();
	    }

	}



    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DismissCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of Callback.java

