/* ScriptPauseCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 9/10/2001
 *
 * $Id: ScriptPauseCallback.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ScriptPauseCallback.java,v $
 * Revision 1.6  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.5  2001/11/21 15:17:53  goldin
 * Make all references to getTimeOffset use ApplicationManager method
 *
 * Revision 1.4  2001/11/16 18:05:54  goldin
 * Move more classes from dragon.ui to gui package
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/10/02 13:21:23  goldin
 * Add tracing for debug purposes
 *
 * Revision 1.1  2001/09/10 14:37:21  goldin
 * Implement state machine while script ins running.
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It is called as
 *  postprocessor for the -PAUSE command, when the reply or nak
 *  file is received. It sets the ScriptControlPanel state
 *  appropriately depending on whether the command succeeeded (argument
 *  is true) or failed (argument is false);
 */
public class ScriptPauseCallback implements Callback 
    {
     /** Primary method of a callback class.
       *  sets the state of the script control panel.
       * @param  field Field whose value will determine the
       *   effects of the callback. Dummy, in this case.
       */
    public void executeCallback(DragonField field)
        {
	DragonUI mainApp = DragonUI.currentApplication;
	ScriptControlPanel sptCtrl = mainApp.getScriptCtrl();
	String arg = field.getLabelText();
        if (arg.compareTo("true")== 0)
	   {
           Tracer.outputTraceMessage(
                  "ScriptPauseCallback arg is " + arg 
		  + " - setting paused_state",        
		  "UI", ApplicationManager.getTimeOffset());
	   sptCtrl.setCurrentState(ScriptControlPanel.PAUSED_STATE);
	   }
	else
	   {
           Tracer.outputTraceMessage(
                  "ScriptPauseCallback arg is " + arg 
		  + " - resetting to last state",        
		  "UI", ApplicationManager.getTimeOffset());
	   sptCtrl.resetCurrentState();
	   }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ScriptPauseCallback.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
