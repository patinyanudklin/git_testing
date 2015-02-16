/* SetScriptStateCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 9/10/2001
 *
 * $Id: SetScriptStateCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SetScriptStateCallback.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/09/10 14:37:21  goldin
 * Implement state machine while script ins running.
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  display of the script control panel when a script is 
 *  run or completed.
*/
public class SetScriptStateCallback implements Callback 
    {
     /** Primary method of a callback class.
       *  Displays or hides (toggles) the script control panel.
       * @param  field Field whose value will determine the
       *   effects of the callback. Dummy, in this case.
       */
    public void executeCallback(DragonField field)
        {
	DragonUI mainApp = DragonUI.currentApplication;
        if (mainApp.isScriptControlVisible())
	   {
	   mainApp.setScriptControlPanelVisible(false);
	   }
	else
	   {
	   mainApp.setScriptControlPanelVisible(true);
	   }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SetScriptStateCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
