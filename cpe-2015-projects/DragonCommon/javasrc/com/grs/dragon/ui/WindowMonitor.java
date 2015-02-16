/**
 * WindowMonitor
 * 
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 * Created by Sally Goldin, 6/7/2000
 *
 *  $Id: WindowMonitor.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: WindowMonitor.java,v $
 *  Revision 1.6  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.5  2001/11/30 18:01:21  goldin
 *  Moved most of the UI basic components to the com.grs.gui package
 *
 *  Revision 1.4  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.3  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.2  2001/03/14 16:38:49  goldin
 *  Extracting exit code into callback
 *
 *  Revision 1.1  2001/01/26 12:49:58  rudahl
 *  initial depsit from mini via tower
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Simple window adapter to react to the user's trying to close
 * a window. Currently prompts and if the user says OK, exits
 * the application.*/
public class WindowMonitor extends WindowAdapter
{
   private Component monitoredWindow;
   protected ExitCallback exitCallback = null;
   protected DFixedText dummyField = null;

  /**
   * Constructor receives and saves a reference to the
   * window being monitored.
   * @param parentComponent  Component that requested monitoring
   */
   public WindowMonitor(Component parentComponent)
      {
      monitoredWindow = parentComponent;
      exitCallback = new ExitCallback();
      // use the dummy field to transmit the component info to the callback
      dummyField = new DFixedText("dummy","dummy");
      dummyField.setParentComponent(parentComponent);
      }

  /** 
   * Respond to the user's attempt to close the window using
   * operating-system-specific mechanisms.
   */
   public void windowClosing(WindowEvent we)
      {
      exitCallback.executeCallback(dummyField);
      }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: WindowMonitor.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
}

