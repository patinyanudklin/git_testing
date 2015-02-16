/****************************************************************
 *
 *          ViewportMenu.java - 
 *             
 *             Popup menu invoked by Viewport; workaround for color
 *             problem in Windows 7.
 *
 *	  ~~ Copyright 
 *           S.E. Goldin, 3 October 2010
 *  		~~envC
 *
 ****************************************************************
 *
 *   $Id: ViewportMenu.java,v 1.1.2.4 2010/10/09 13:05:26 rudahl Exp $
 *   $Log: ViewportMenu.java,v $
 *   Revision 1.1.2.4  2010/10/09 13:05:26  rudahl
 *   fixed docs
 *
 *   Revision 1.1.2.3  2010/10/04 13:49:17  goldin
 *   Fix loop logic problem in actionPerformed
 *
 *   Revision 1.1.2.2  2010/10/04 10:28:45  goldin
 *   Test update
 *
 *   Revision 1.1.2.1  2010/10/04 10:27:26  goldin
 *   Try to add new Java menus
 *
 ****************************************************************
 */

package com.grs.dragon.viewport;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import com.grs.gui.*;

public class ViewportMenu extends JPopupMenu implements ActionListener
{
    public static int latestSelection = -2;

    int itemCount = 0;
    JMenuItem menuItems[] = null;

    /**
     * Constructor. Creates popup by looking up each key
     * in the appropriate language dictionary and adding
     * a JMenuItem for that string 
     * @param viewMsgs   Source for internationalized strings
     * @param keys       Array of keys for string lookup
     * @param title      Title string - may be null.
     */
    public ViewportMenu(I18NTextSource viewMsgs, String keys[], String title)
       {
       super();
       int len = keys.length;
       menuItems = new JMenuItem[len];
       for (itemCount = 0; itemCount < len; itemCount++)
	    {
	    String msg = "";
	    if ((keys[itemCount] != null) && (keys[itemCount].length() > 0))
	        {
	        msg = keys[itemCount];
	        if (viewMsgs != null)
		      msg = viewMsgs.getI18NText(keys[itemCount],
  				                 keys[itemCount]);
		menuItems[itemCount] = new JMenuItem(msg);
		add(menuItems[itemCount]);
		menuItems[itemCount].addActionListener(this);
		}
	    }
       }

    /**
     * Respond to the user selecting some menu item by setting
     * 'latestSelection' variable.
     * This implements the necessary method from
     * the ActionListener interface.
     * @param event   The action event that triggered this.
     */
    public void actionPerformed(ActionEvent event)
       {
       int choice = -1;
       int i = 0;
       Object source = event.getSource();
       while ((i < itemCount) && (choice < 0))
          {
	  if (menuItems[i].equals(source))
	     {
	     choice = i;
	     }
	  else
	     {
	     i++;
	     }
          }
       if (choice >= 0)
          {
	  latestSelection = choice;
	  setVisible(false);
          }
       }


    /**
     *  Set each menu item to be enabled or disabled
     *  based on the passed bitmap. The least significant
     *  bit governs item 0 and so on.
     * @param enableMask    Bitmap to control enablement
     */
    public void setItemsEnabled(int enableMask)
       {
       int i = 0;
       int testMask = 0x01;
       for (i = 0; i < itemCount; i++)
          {
	  if ((enableMask & testMask) == 1)
	      menuItems[i].setEnabled(true);
	  else
	      menuItems[i].setEnabled(false);
	  enableMask = enableMask >> 1;
          }
       }


    /**
     * Show or hide the menu after changing the value of
     * the latestSelection.
     * @param  bFlag   If true, set visible, if false, turn off.
     */
    public void setMenuVisible(boolean bFlag)
       {
       setVisible(bFlag);
       if (bFlag)
	   latestSelection = -1;
       else
	   latestSelection = -2;
       }

    /**
     * return current value of latestSelection
     */
    public static int getLatestSelection()
       {
       return latestSelection;
       }


    /** Test driver */

    public static void main(String args[])
      {
      String tempKeys[] = {"Add","Delete","Modify","Exit"};

      ViewportMenu menu = new ViewportMenu(null,tempKeys,null);
      menu.setLocation(500,400);
      menu.setItemsEnabled(0x07);
      menu.setMenuVisible(true);
      int selected = -1;
      while (selected < 0)
	  {
	  try 
	      {
	      Thread.sleep(1000);
	      }
	  catch (InterruptedException e)
	      {
	      }
	  selected = menu.getLatestSelection();
	  System.out.println("Latest selection is " + selected );
	  }
      }

}
