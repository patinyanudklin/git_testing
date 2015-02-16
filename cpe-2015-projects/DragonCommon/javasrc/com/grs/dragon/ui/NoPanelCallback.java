/* NoPanelCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/28/2001
 *
 * $Id: NoPanelCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: NoPanelCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/04/05 13:34:51  goldin
 * Cleanup behavior, fix XML errors
 *
 * Revision 1.2  2001/02/28 11:50:12  goldin
 * Extend mouse handling to checkbuttons and push buttons
 *
 * Revision 1.1  2001/02/28 11:24:24  goldin
 * Implement callbacks for additional screens
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  details of menu items that do not put up a panel or have other
 *  visible effects, but which send a command to the Dragon server.
 * @author  goldin*/
public class NoPanelCallback implements Callback 
    {
      /** Primary method of a callback class.
       *  Sends a command to Dragon, based on the 
       *  current menu item, whose ID is stored in the
       *  label text of the field.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        DragonUI app = (DragonUI) field.getParentComponent();
	String menuID = field.getLabelText();
        DragonMenuItem menuItem = app.getMenuItem(app.getJMenuBar(),menuID);
         

	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: NoPanelCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of NoPanelCallback.java

