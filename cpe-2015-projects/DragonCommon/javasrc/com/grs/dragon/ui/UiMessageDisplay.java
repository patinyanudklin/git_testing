/**
 * MessageDisplay
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 5/2/2001
 *
 * $Id: UiMessageDisplay.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: UiMessageDisplay.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2005/12/05 10:38:46  goldin
 * Repack diaolog after changing font to avoid messages getting cut off
 *
 * Revision 1.2  2005/07/24 13:22:06  goldin
 * Set correct font in message dialogs
 *
 * Revision 1.2  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.1  2001/11/16 18:25:38  goldin
 * Renamed and specialized MessageDisplay subclass
 *
 * Revision 1.4  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/05/18 10:49:14  goldin
 * Don't exit while there are still messages to be displayed
 *
 * Revision 1.1  2001/05/02 15:11:41  goldin
 * Implement message and progress IPC file processing
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import javax.swing.plaf.*;
import java.awt.*;

/**
 * This class displays non-error messages, for the Dragon UI only.
 * There is one instance of this class in the system, and it
 * reuses the same dialog for each error call.*/
public class UiMessageDisplay extends MessageDisplay
    {
      /**
       * Window upon which the dialogs should be centered.
       */
    protected DragonUI dragonUI = null;

      /**
       * Constructor sets the text source and sets things up
       * for displaying the dialog.
       */
    public UiMessageDisplay(I18NTextSource textSource, DragonUI masterWindow)
        {
        super(textSource,masterWindow);
        this.textSource = textSource;
        this.dragonUI  = (DragonUI) masterWindow;
	this.setFont(dragonUI.getFont());
	}
			
      /**
       * Override to include setting of DRAGON-specific flags.
       */
    protected void showDialog()
        {
	JDialog dlg = createDialog(dragonUI,title);
	dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
        SwingUtilities.updateComponentTreeUI(dlg);
        dragonUI.setMessageDialogVisible(true);        
	dlg.pack();
        dlg.setVisible(true);
        Object val = getValue();
	dlg.setVisible(false);
        dragonUI.setMessageDialogVisible(false);
        dragonUI.repaint();
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UiMessageDisplay.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

