/**
 * DMenuItem
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 1/19/2001
 *
 * $Id: DMenuItem.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DMenuItem.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2002/06/28 14:11:02  goldin
 * Provide infrastructure for usermanual help implementation
 *
 * Revision 1.2  2002/02/07 18:45:16  goldin
 * Add method to disable
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/04/09 10:55:02  goldin
 * Change DragonMenuItem to be an iterface
 *
 */

package com.grs.gui;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * This class implements a standard, action-oriented menu item
 * with Dragon-specific features, including knowing its help
 * message and its name.*/
public class DMenuItem extends JMenuItem implements DragonMenuItem
    {
      /**
       * unique ID for this menu element
       */
    protected String name;

      /**
       * What menu is this attached to?*/
    protected DragonMenu parentMenu;

      /**
       * help text for this menu item.
       */
    protected String helpString;

      /**
       * "command" to be executed. This gets passed to the
       * invoked response panel.
       */
    protected String commandString;

      /**
       * ID of response panel to be displayed.
       */
    protected String invokedPanelId;

      /**
       * Callback for this menu item - allows execution of
       * arbitary code.*/
    protected Callback callback = null;

      /**
       * If true, don't switch away from current panel when
       * this menu item is invoked. Special case for only a few commands.
       */
    protected boolean bKeepContext = false;

      /**
       * Array of keys used to retrieve the help.
       */
    protected String[] helpKeys;

      /**
       * Should the item be enabled?
       */
    protected boolean bEnabled = true;

      //**********************************************
      /**
       * constructor sets name and uses name as preliminary
       * text. Text will be reset after creation.
       */
    public DMenuItem(String name)
        {
	super(name);
	this.name = name;
	}

    public String getName()
        {
	return name;
	}

    public String getCommandString() 
        {
        return commandString;
        }
    
    public void setCommandString(String commandString) 
        {
        this.commandString = commandString;
        }

    public void setHelpKeys(String[] keys)
        {
	this.helpKeys = keys;
	}

    public String[] getHelpKeys()
        {
	return helpKeys;
	}

    public String getInvokedPanelId() 
        {
        return invokedPanelId;
        }
    
    public void setInvokedPanelId(String panelId) 
        {
        this.invokedPanelId = panelId ;
        }

    public DragonMenu getParentMenu()
        {
	return parentMenu;
	}

    public void setParentMenu(DragonMenu parentMenu)
        {
	this.parentMenu = parentMenu;
	}

    public String getHelpString() 
        {
        return helpString;
        }
    
    public void setHelpString(String helpString) 
        {
        this.helpString = helpString;
        }

    public Callback getCallback() 
        {
        return callback;
        }
    
    public void setCallback(Callback cb) 
        {
        callback = cb;
        }

    public void setEnabled(boolean bFlag)
        {
	super.setEnabled(bFlag);
	bEnabled = bFlag;
	}

    public boolean isEnabled()
        {
	return bEnabled;
	}

    public boolean isKeepContext()
        {
	return bKeepContext;
	}

    public void setKeepContext(boolean bFlag)
        {
	bKeepContext = bFlag;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DMenuItem.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }







