/**
 * Splash
 *
 * Copyright  2001-2007  by Sally Goldin and Kurt Rudahl
 *
 *  Created by Sally Goldin, 12/11/2001
 * 
 *  $Id: Splash.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $
 *  $Log: Splash.java,v $
 *  Revision 1.3  2007/01/05 07:41:58  rudahl
 *  added Whatis info
 *
 *  Revision 1.2  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.1  2001/12/11 16:19:54  goldin
 *  Add splash screen
 *
 *
 */
package com.grs.gui;
import javax.swing.*;
import java.awt.*;

/**
 * This class implements a splash screen, that is, a centered
 * window with no decorations, holding an image. The file
 * to use for the splash screen is set in the constructor.
 */
public class Splash extends JWindow
    {

      /**
       * constructor creates the window and the icon label,
       * but does not show it.
       * @param imageFile  Name of image file for image to splash
       * @param rColor     Value of red component for border color
       * @param gColor     Same for green
       * @param bColor     Same for blue
       */
    public Splash(String imageFile, int rColor, int gColor, int bColor)
        {
	JPanel content = (JPanel) getContentPane();
	Color borderColor = new Color(rColor,gColor,bColor);
        JLabel splash = new JLabel(new ImageIcon(imageFile));
        content.add(splash, BorderLayout.CENTER);
	content.setBorder(BorderFactory.createLineBorder(
				     borderColor,10));
	pack();
	}


      /**
       * Show the splash screen, centered, or hide it.
       * @param bFlag  If true, show; if false, hide.
       */
    public void setVisible(boolean bFlag)
        {
	if (!bFlag)
	     super.setVisible(false);
	else
	     {
	     Dimension size = getSize();
	     Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
	     int x = (screen.width - size.width)/2;
	     int y = (screen.height - size.height)/2;
	     setLocation(x,y);
	     super.setVisible(true);
	     }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: Splash.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }
