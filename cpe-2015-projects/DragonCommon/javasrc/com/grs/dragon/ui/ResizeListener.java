/**  
 * ResizeListener
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin on 1/29/2001
 *
 *  $Id: ResizeListener.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ResizeListener.java,v $
 *  Revision 1.9  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.8  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.7  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.6  2001/04/06 18:04:25  goldin
 *  Work on resizing issues
 *
 *  Revision 1.5  2001/03/21 14:54:16  goldin
 *  Split RP.XML into separate menu and panel files; address via new properties file.
 *
 *  Revision 1.4  2001/03/20 13:31:38  goldin
 *  Implement new sizing strategy
 *
 *  Revision 1.3  2001/03/14 16:39:31  goldin
 *  Implemented small panel size, fixed resize listener to allow them
 *
 *  Revision 1.2  2001/02/08 16:14:39  goldin
 *  Added HelpEditor capability
 *
 *  Revision 1.1  2001/01/29 12:23:28  goldin
 *  Put official UI file in CVS, also new class to control resizing
 *
 */

package com.grs.dragon.ui;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * This is a subclass of ComponentAdaptor which is intended
 * to prevent users from resizing the top-level DRAGON window
 * below a certain size. If the user resizes the application to
 * be too small, this class will expand it back to the specified
 * minimum size. This class also handles increases in size, by
 * adjusting the desired sizes of the "big" and "normal" response
 * panels.*/
public class ResizeListener extends ComponentAdapter
   {

   protected Dimension minimumSize = null;
   protected DragonUI windowMonitored = null;

    /** 
     * Constructor initializes the minimum size and the
     * component to be monitored. This allows it to detect
     * attempts to resize the application to be too small, and
     * to send correcting setSize messages if this is accomplished.
     * @param minSize    Desired minimum size to enforce
     * @param window     Window to monitor.
     */
   public ResizeListener(Dimension minSize, Component window)
       {
       minimumSize = minSize;
       windowMonitored = (DragonUI) window;
       }
     
    /**
     * For now, we are only interested in component resize events.
     * Thus, we override the componentResized() method.
     * @param ce  Component event (resize)
     */
   public void componentResized(ComponentEvent ce)
       {
       if (ce.getComponent() != windowMonitored)
	   return;
       Dimension computedMinSize = new Dimension(minimumSize.width,
						 minimumSize.height);
       Dimension newSize = windowMonitored.getSize();

       // if the resize was initiated by the program, don't
       // override it.
       DragonUI app = (DragonUI) windowMonitored;
       if (windowMonitored.isNewPanel())
	   {
	   windowMonitored.setNewPanel(false);
	   return;
	   }

       if ((newSize.height < computedMinSize.height) ||
           (newSize.width < computedMinSize.width))
	   {
           windowMonitored.setSize(computedMinSize);
	   }
       }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ResizeListener.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
   }




