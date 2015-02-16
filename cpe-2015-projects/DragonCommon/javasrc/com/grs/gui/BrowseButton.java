/**
 *  BrowseButton.java
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 4/24/2001
 *
 *  $Id: BrowseButton.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: BrowseButton.java,v $
 *  Revision 1.2  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.1  2001/11/30 18:03:09  goldin
 *  Moved most of the UI basic components to the com.grs.gui package
 *
 *  Revision 1.2  2001/11/05 13:59:14  goldin
 *  Put UI code in a package
 *
 *  Revision 1.1  2001/04/24 14:14:20  goldin
 *  Improve behavior and appearance of file and font choosers
 *
 */

package com.grs.gui;
import javax.swing.*;

/**
 *  This class is a shallow subclass of JButton, which exists
 *  only so that we can make the buttons on the font and file
 *  dialogs not focus traversable.
 */
public class BrowseButton extends JButton
    { 

    protected static ImageIcon browseIcon =
         new ImageIcon("downArrow.gif");


      /** 
       * Constructor. For now, assume that all browse buttons
       * use the same icon.
       */
    public BrowseButton()
        {
	super(browseIcon);
        setRequestFocusEnabled(true);
        }

      /**
       * Override JComponent method.
       */
    public boolean isFocusTraversable()
        {
	return false;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: BrowseButton.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
