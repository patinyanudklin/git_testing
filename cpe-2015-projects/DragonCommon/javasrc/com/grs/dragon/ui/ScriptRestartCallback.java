/* ScriptRestartCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 9/10/2001
 *
 * $Id: ScriptRestartCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ScriptRestartCallback.java,v $
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
 *  This class implements the Callback interface. It is called as
 *  postprocessor for the -RESTART command, when the reply or nak
 *  file is received. It sets the ScriptControlPanel state
 *  appropriately depending on whether the command succeeeded (argument
 *  is true) or failed (argument is false);
 */
public class ScriptRestartCallback implements Callback 
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
	String arg = field.getLabelText();
        if (arg.equals("true"))
	   {
	   sptCtrl.setCurrentState(ScriptControlPanel.RUNNING_STATE);
	   }
	else
	   {
	   sptCtrl.resetCurrentState();
	   }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ScriptRestartCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
