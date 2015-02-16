/**
 * DragonMenuItem
 *
 * Copyright 2001 by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 1/19/2001
 *
 * $Id: DragonMenuItem.java,v 1.2 2002/06/28 14:11:02 goldin Exp $
 * $Log: DragonMenuItem.java,v $
 * Revision 1.2  2002/06/28 14:11:02  goldin
 * Provide infrastructure for usermanual help implementation
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.6  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.5  2001/04/09 10:55:02  goldin
 * Change DragonMenuItem to be an iterface
 *
 * Revision 1.4  2001/03/20 13:32:24  goldin
 * Add help editing and viewing for menu items
 *
 * Revision 1.3  2001/03/16 19:23:46  goldin
 * Added fixed length option for DTextField and DFileField; added callbacks to menu items
 *
 * Revision 1.2  2001/01/29 12:23:28  goldin
 * Put official UI file in CVS, also new class to control resizing
 *
 * Revision 1.1  2001/01/19 18:43:19  goldin
 * Add handling of xlateText, menu building
 *
 */

package com.grs.gui;

/**
 * This class interface defines a set of methods which are shared by
 * the DMenuItem and DCheckMenuItem classes, each of which has a
 * different Swing parent.
 */
public interface DragonMenuItem    
    {
    public String getName();

    public String getCommandString(); 
    
    public void setCommandString(String commandString); 

    public void setHelpKeys(String[] keys);

    public String[] getHelpKeys();

    public String getInvokedPanelId(); 
    
    public void setInvokedPanelId(String panelId); 

    public DragonMenu getParentMenu();

    public void setParentMenu(DragonMenu parentMenu);

    public String getHelpString(); 
    
    public void setHelpString(String helpString); 

    public Callback getCallback(); 

    public void setCallback(Callback cb); 

    public boolean isKeepContext();
    }

