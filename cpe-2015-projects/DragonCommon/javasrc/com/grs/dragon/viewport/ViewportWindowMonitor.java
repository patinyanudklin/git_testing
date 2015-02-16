/**
 * ViewportWindowMonitor
 * 
 *  Copyright 2001 by Sally Goldin & Kurt Rudahl
 * Created by Kurt Rudahl, 9/10/2000
 *
 *  $Id: ViewportWindowMonitor.java,v 1.6 2005/02/06 09:17:30 goldin Exp $
 *  $Log: ViewportWindowMonitor.java,v $
 *  Revision 1.6  2005/02/06 09:17:30  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.5  2001/11/15 20:46:40  rudahl
 *  moved viewport java files to their own package
 *
 *  Revision 1.4  2001/11/05 20:28:49  rudahl
 *  adapt to dragon.ui package *.java
 *
 *  Revision 1.3  2001/09/25 20:57:39  rudahl
 *  further improvements to Jni Dialogs
 *
 *  Revision 1.2  2001/09/19 14:44:58  rudahl
 *  improved - but not yet final - dialogs
 *
 *  Revision 1.1  2001/09/10 19:45:01  rudahl
 *  further improvements to ButtonPanel
 *
 */
package com.grs.dragon.viewport;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import com.grs.dragon.ui.*;

/**
 * Simple window adapter to react to the user's closing a window via the 
 * system menu or 'X' button. Essentially it just hides it, for reuse.
 */
public class ViewportWindowMonitor extends WindowAdapter
    {

    protected boolean m_bFinished = false;
      /**
         */
    public ViewportWindowMonitor()
        {
	}

      /** 
       * Respond to the user's attempt to close the window using
       * operating-system-specific mechanisms.
       */
    public void windowClosing(WindowEvent we)
        {
	Window w = we.getWindow();
	w.setVisible(false);
	m_bFinished = true;
	//w.dispose();
	//        monitoredWindow.setVisible(true);
	}

      /** 
       *  Return true if the window has closed.
       *  This also resets the flag, so test it only once.
       */
    public boolean isFinished() 
        { 
	boolean b = m_bFinished;
	m_bFinished = false;
	return b;
	}
    }
