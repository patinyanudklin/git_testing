/**
 * GenHelpDisplayListener
 *   
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 12/18/2001
 *
 *  $Id: GenHelpDisplayListener.java,v 1.2 2007/01/05 07:41:58 rudahl Exp $
 *  $Log: GenHelpDisplayListener.java,v $
 *  Revision 1.2  2007/01/05 07:41:58  rudahl
 *  added Whatis info
 *
 *  Revision 1.1  2001/12/18 15:14:32  goldin
 *  Add new generic help display class
 *
 */

package com.grs.gui;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;

/**
 * This class is an extension of MouseInputAdapter. It is used
 * to display the help msg associated with a control when the
 * mouse enters the panel for that control.
 * This is a generic version of the class used in the DRAGON UI.
 */
public class GenHelpDisplayListener extends MouseAdapter
    {
      /**
       * Place to display the help text.
       */
    protected JTextComponent helpArea = null;

      /**
       * Constructor initializes the ref to the help area
       */
    public GenHelpDisplayListener(JTextComponent helpArea)
        {
	this.helpArea = helpArea;
	}

      /**
       * Override the MouseEntered method. Display help when mouse
       * enters the control.
       */
    public void mouseEntered(MouseEvent e)
        {
	if (!helpArea.isVisible())
	    return;
	// don't process the event if the right or middle mouse btn is down
	int modifiers = e.getModifiers();
	if ((modifiers & 
            (InputEvent.BUTTON2_MASK | InputEvent.BUTTON3_MASK)) != 0)
	    return;

	DragonMenuItem item = null;
        DragonMenu menu = null;
	DragonField field = null;
	String help = null;
	Object source = e.getSource();
	if (source instanceof DragonField)
	    {
	    field = (DragonField) source;
	    }
	else if (source instanceof DragonMenuItem)
	    {
            item = (DragonMenuItem) source;
	    }
	else if (source instanceof DragonMenu)
	    {
            menu = (DragonMenu) source;
	    }
	else 
	    {
	    JComponent src = (JComponent) source;
	    Object parent = src.getClientProperty(DragonField.PARENT_FIELD);
	    if (parent != null)
	        {
                field = (DragonField) parent;
		}
	    }

        if (field != null)
	    {
	    help = field.getHelpString();
	    }
	else if (item != null)
	    {
	    help = item.getHelpString();
	    }
	else if (menu != null)
	    {
	    help = menu.getHelpString();
	    }

	if (help != null)
	    {
	    helpArea.setText(help);
	    helpArea.setCaretPosition(0);
	    }
	else
	    {
	    helpArea.setText("");
	    }
	}


      /**
       * Override the MouseExited method. Clear help when mouse
       * leaves the control.
       */
    public void mouseExited(MouseEvent e)
        {
	if (!helpArea.isVisible())
	    return;
	// don't process the event if the right or middle mouse btn is down
	int modifiers = e.getModifiers();
	if ((modifiers & 
            (InputEvent.BUTTON2_MASK | InputEvent.BUTTON3_MASK)) != 0)
	    return;
	Object source = e.getSource();
	// try clearing unconditionally
	helpArea.setText("");
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: GenHelpDisplayListener.java,v 1.2 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }




