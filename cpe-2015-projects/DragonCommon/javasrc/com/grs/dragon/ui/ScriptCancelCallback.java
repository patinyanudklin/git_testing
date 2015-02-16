/* ScriptCancelCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 9/11/2001
 *
 * $Id: ScriptCancelCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ScriptCancelCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2002/02/04 20:39:35  rudahl
 * fixed typoe
 *
 * Revision 1.3  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/09/11 11:47:03  goldin
 * implement cancel menu item
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It is called as
 *  preprocessor for the -CANCEL command, in order to set the
 *  state of the script control panel. This is necessary because
 *  a script can be cancelled either from a button or from the menu.
 */
public class ScriptCancelCallback implements Callback 
    {
     /** Primary method of a callback class.
       *  Sets the state of the script control panel.
       * @param  field Field whose value will determine the
       *   effects of the callback. Dummy, in this case.
       */
    public void executeCallback(DragonField field)
        {
	DragonUI mainApp = DragonUI.currentApplication;
	ScriptControlPanel sptCtrl = mainApp.getScriptCtrl();
	sptCtrl.setCurrentState(ScriptControlPanel.CANCELLED_STATE);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ScriptCancelCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
