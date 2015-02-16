/**
 *  DragonMenu
 *
 *  ~~Copyright  2001-2014  by Sally Goldin & Kurt Rudahl
 * ~~ EndC
 *
 *  Created by Sally Goldin, 1/19/2000
 *
 * $Id: DragonMenu.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: DragonMenu.java,v $
 * Revision 1.3.2.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.4  2007/07/20 03:53:35  goldin
 * Get rid of unchecked operation warnings by parameterizing collections
 *
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.5  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.4  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.3  2001/04/09 11:05:42  goldin
 * Add Logging facility logic
 *
 * Revision 1.2  2001/03/20 18:04:15  goldin
 * Implement tabbed panes, clean up menu help:
 *
 * Revision 1.1  2001/01/19 18:43:19  goldin
 * Add handling of xlateText, menu building
 *
 */

package com.grs.gui;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.*;

/**
 * This class extends the JMenu class to provide a menu
 * which knows its own name and has a table of its items.*/
public class DragonMenu extends JMenu
    {
      /* Name for this submenu (not its text)
       */
    String name;

      /**
       * Table of items.
       */
    Hashtable<String,JMenuItem> itemTable = new Hashtable<String,JMenuItem>(30);


      /**
       * Which menu this menu is attached to. 
       * The value will be null for toplevel menus
       */
    protected DragonMenu parentMenu = null;


      /**
       * help text for this menu item.
       */
    protected String helpString;

      /**
       * Array of keys used to retrieve the help.
       */
    protected String[] helpKeys;



      //***********************************************************

      /**
       * Constructor, sets name and calls the superclass.
       * Initially uses the name for text, but this will
       * be changed.
       */
    public DragonMenu(String name)
        {
	super(name);
	this.name = name;
	}

      /**
       * Override the add methods to set the parent 
       */
    public JMenuItem add(JMenuItem item)
        {
	super.add(item);
	if (item instanceof DMenuItem)
	    {
	    DMenuItem dItem = (DMenuItem) item;
	    dItem.setParentMenu(this);
	    itemTable.put(dItem.getName(),dItem);
	    }
	else if (item instanceof DCheckMenuItem)
	    {
	    DCheckMenuItem dItem = (DCheckMenuItem) item;
	    dItem.setParentMenu(this);
	    itemTable.put(dItem.getName(),dItem);
	    }
	else if (item instanceof DragonMenu)
	    {
	    DragonMenu dItem = (DragonMenu) item;
	    dItem.setParentMenu(this);
	    itemTable.put(dItem.getName(),dItem);
	    }
	return item;
	}

    public String getName()
        {
	return name;
	}

    public void setHelpKeys(String[] keys)
        {
	this.helpKeys = keys;
	}

    public String[] getHelpKeys()
        {
	return helpKeys;
	}

    public String getHelpString() 
        {
        return helpString;
        }
    
    public void setHelpString(String helpString) 
        {
        this.helpString = helpString;
        }

    public DragonMenu getParentMenu()
        {
	return parentMenu;
	}

    public void setParentMenu(DragonMenu parentMenu)
        {
	this.parentMenu = parentMenu;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonMenu.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }

