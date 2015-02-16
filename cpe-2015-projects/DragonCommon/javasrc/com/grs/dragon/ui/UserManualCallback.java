/* UserManualCallback.java
 *
 * Copyright  2002-2007  Goldin-Rudahl Associates
 *
 * $Id: UserManualCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: UserManualCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2002/09/10 20:07:28  goldin
 * bring up first section if not in RP
 *
 * Revision 1.3  2002/07/18 19:49:15  goldin
 * *** empty log message ***
 *
 * Revision 1.2  2002/06/28 14:10:48  goldin
 * Provide infrastructure for usermanual help implementation
 *
 * Revision 1.1  2002/01/22 14:53:27  goldin
 * Add new UserManualCallback
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;
import javax.swing.*;

//********************************************************************
/** 
 *  This class implements the Callback interface. It has the effect
 *  of displaying the Dragon manual reader, set to the present context..
 */
public class UserManualCallback implements Callback 
    {
      /** Primary method of a callback class.
       *  Sends a command to the manreader, which should be running.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	String commandString = null;
	DragonUI dragUI = (DragonUI) field.getParentComponent();
	if (dragUI == null)
	    {
	    System.out.println("Parent component not set in UserManualCallback");
	    return;
	    }
	String helpId = dragUI.getCurrentPanelHelpId();
	if (helpId == null)
	    helpId = "1";    // no panel; show first section
	commandString = "SHOW " + helpId;
	boolean bOk = dragUI.getCommandForwarder().sendCommandToServer(
                         commandString);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UserManualCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of UserManualCallback.java

