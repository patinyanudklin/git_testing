/* AboutCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: AboutCallback.java,v 1.11 2007/01/05 06:26:38 rudahl Exp $
 * $Log: AboutCallback.java,v $
 * Revision 1.11  2007/01/05 06:26:38  rudahl
 * added whatis info
 *
 * Revision 1.10  2001/11/30 18:01:20  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.9  2001/11/05 13:59:14  goldin
 * Put UI code in a package
 *
 * Revision 1.8  2001/10/05 11:05:34  goldin
 * Separate Dialog from callback to allow reuse by Viewport
 *
 * Revision 1.7  2001/10/03 15:15:46  goldin
 * Modify display to index some lines
 *
 * Revision 1.6  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.5  2001/04/17 19:06:21  goldin
 * Fix out of bounds error
 *
 * Revision 1.4  2001/04/06 11:20:59  goldin
 * Fix bugs related to tree root
 *
 * Revision 1.3  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.2  2001/03/21 13:05:39  goldin
 * Add language selection and config file processing functionality
 *
 * Revision 1.1  2001/03/20 18:03:55  goldin
 * Add callback to display About box
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;
import javax.swing.*;

//********************************************************************
/** 
 *  This class implements the Callback interface. It has the effect
 *  of displaying an About box.
 *  As of 10/5/2001, the actual about dialog is constructed in a 
 *  separate class.
 */
public class AboutCallback implements Callback 
    {
    protected AboutDialog aboutDialog = null;

      /**
       * Constructor creates the AboutDialog
       */
    public AboutCallback()
        {
        aboutDialog = new AboutDialog();
	}

      /** Primary method of a callback class.
       *  Displays about dialog and waits for user action.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        Component monitoredWindow = field.getParentComponent();
	if (monitoredWindow != null)
	    {
            aboutDialog.showAboutDialog(monitoredWindow);
            }
        DragonUI ui = (DragonUI) monitoredWindow;
	ui.getHelpArea().setText("");
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: AboutCallback.java,v 1.11 2007/01/05 06:26:38 rudahl Exp $ \n";
	}
    }

// End of AboutCallback.java

