/* EchoCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/22/2001
 *
 * $Id: EchoCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: EchoCallback.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/22 10:05:14  goldin
 * Implement ECHO menu item as check item
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  operation of the ECHO menu item. Basically, this just sends
 *  an ECHO-ON or ECHO-OFF command to Dragon. 
 */
public class EchoCallback implements Callback 
    {
     /** Primary method of a callback class.
       *  Depending on state of bLogging, may put up a box for
       *  the user to choose a log file name. Then
       *  sends a command to Dragon to turn logging on or off.
       * @param  field Field whose value will determine the
       *   effects of the callback. Dummy, in this case.
       */
    public void executeCallback(DragonField field)
        {
	DragonUI mainApp = (DragonUI) field.getParentComponent();
        String fieldID = field.getName();
	// get the menu item based on its name
        DragonUI app = (DragonUI) field.getParentComponent();
	String menuID = "mF/SPT/ECHO";
        DCheckMenuItem menuItem = 
	  (DCheckMenuItem) app.getMenuItem(app.getJMenuBar(),menuID);
	boolean checkState = menuItem.getState();
        if (checkState)
             app.getCommandForwarder().sendCommandToServer("ECHO-ON");
        else
             app.getCommandForwarder().sendCommandToServer("ECHO-OFF");
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: EchoCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of EchoCallback.java



