/****************************************************************
 *
 *          JniDialog.java - 
 *             Abstract base class for various dialogs etc 
 *             to be used by viewport and invoked through JNI
 *			 K.T. Rudahl
 *
 *          Copyright 2002 by Goldin-Rudahl Associates
 *                            P.O. Box 9648
 *                            North Amherst, MA 01059 U.S.A.
 ****************************************************************
 *
 *   $Id: JniDialog.java,v 1.12 2002/09/12 00:05:04 rudahl Exp $
 *   $Log: JniDialog.java,v $
 *   Revision 1.12  2002/09/12 00:05:04  rudahl
 *   fixed CUR buttonpanel position
 *
 *   Revision 1.11  2002/01/15 19:29:31  rudahl
 *   fixes to infoviewport
 *
 *   Revision 1.10  2001/12/20 18:48:54  rudahl
 *   some bulletproofing
 *
 *   Revision 1.9  2001/11/30 19:17:09  rudahl
 *   added top JFrame to support icon
 *
 *   Revision 1.8  2001/11/29 11:24:54  goldin
 *   Add icon setting to JniDialog
 *
 *   Revision 1.7  2001/11/28 17:08:30  rudahl
 *   added processing of Fn-key presses
 *
 *   Revision 1.6  2001/11/16 16:37:47  goldin
 *   Begin moving UI code to other packages as relevant
 *
 *   Revision 1.5  2001/11/15 20:47:03  rudahl
 *   moved viewport java files to their own package
 *
 *   Revision 1.4  2001/11/08 21:59:27  rudahl
 *    improvements in infoviewport
 *
 *   Revision 1.3  2001/11/05 20:28:49  rudahl
 *   adapt to dragon.ui package *.java
 *
 *   Revision 1.2  2001/09/25 20:58:07  rudahl
 *   further improvements to Jni Dialogs
 *
 *   Revision 1.1  2001/09/24 18:11:05  rudahl
 *   added JniDialog as base class, and improved or added its subclasses
 *
 *   Revision 1.6  2001/09/19 14:44:58  rudahl
 *   improved - but not yet final - dialogs
 *
 *   Revision 1.5  2001/09/17 15:51:43  rudahl
 *   checkpoint before making Java objects persistent within session
 *
 *   Revision 1.4  2001/09/14 14:06:15  rudahl
 *   improved (but not final) Java P&R
 *
 *   Revision 1.3  2001/09/11 16:01:30  rudahl
 *   improvements in buttonPanel implementation & use
 *
 *   Revision 1.2  2001/09/10 19:45:01  rudahl
 *   further improvements to ButtonPanel
 *
 ****************************************************************
 * history   
 */
package com.grs.dragon.viewport;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import com.grs.gui.*;

abstract public class JniDialog extends JDialog implements KeyListener
    {

    protected I18NTextSource m_viewMsgs = null;
    protected ViewportWindowMonitor m_windowMonitor = null;
    protected Dimension m_MinimumSize = null;
    protected Vector m_keyEventsToViewport = new Vector();
    protected Vector m_keyEventsToDismiss = new Vector();
    protected static JFrame s_fred = new JFrame();
      /** construct a dialog setting font and I18N source
       *  @param viewMsgs  source of keyed I18N'd messages
       *  @param czTitle   title line or key
       */
    public JniDialog(I18NTextSource viewMsgs,String czTitle )
        {
	super(s_fred);
	viewProg.logViewport("JniDialog ctor");
	setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
	m_windowMonitor = new ViewportWindowMonitor();
	addWindowListener(m_windowMonitor);
	Font font = new Font("LucidaSans",Font.PLAIN,12);
	setFont(font);
	m_viewMsgs = viewMsgs;
	if (czTitle != null)
	    setTitle((m_viewMsgs != null)
	        ? m_viewMsgs.getI18NText(czTitle,czTitle) : czTitle);
	addKeyListener(this);
	s_fred.setIconImage(new ImageIcon("viewnew.gif").getImage());
  	}

      /** construct a dialog setting font only
       *  @param czTitle   title line (key not possible)
       */
    public JniDialog(String czTitle)
        {
	this(null,czTitle);
	}

      /** display the dialog
       */
    public void showIt()
        {
	setVisible(true);
	requestFocus();
	//	show();
	}

      /* clear out local data before a new plot 
       */
    public abstract void reinit();

      /** Set the location of the dialog
       *  @param   iStrategy    specify placement strategy:
       *                         0 => centered; ignore parent
       *                         1 => by preference, to the side of the parent
       *                         2 => by preference below the parent
       *                         3 => like 1, but offset (staircased) a bit
       *  @param   parentArea   screen coords occupied by parent VP,
       *                        or all zeroes
       */
    public void setLocation(int iStrategy,
			    Rectangle parentArea)
        {
	Dimension screenDim = Toolkit.getDefaultToolkit().getScreenSize();
	Dimension size = getSize();
	int iXCenter = screenDim.width / 2;
	int iYCenter = screenDim.height / 2;
	Point p = new Point(iXCenter,iYCenter);
	if (iStrategy == 2)
	    {
	    int iParentCenterX = parentArea.x + parentArea.width/2;
	    int iLeftSide = iParentCenterX - size.width/2;
	    if (parentArea.width == 0)
	        p.x = iXCenter - size.width/2;
	    else if (size.height
		     < (screenDim.height - (parentArea.y+parentArea.height)))
		p = new Point(iLeftSide,parentArea.y + parentArea.height);
	    else if (size.height < parentArea.y)
		p = new Point(iLeftSide,parentArea.y - size.height);
	    else  /* else put it at bottom, centered */
		p = new Point(iLeftSide,screenDim.height - size.height);
	    setLocation(p);
	    }
	else if ((iStrategy == 1) || (iStrategy == 3))
	    {
	      /* if we have a parent, put to left or right of parent if poss */
	    if (parentArea.width == 0)  /* should never happen */
	        p.y = iYCenter - size.height/2;
	    else if (size.width < parentArea.x)
		p = new Point(parentArea.x - size.width,parentArea.y);
	    else if (size.width 
		     < (screenDim.width - (parentArea.x+parentArea.width)))
		p = new Point(parentArea.x + parentArea.width,parentArea.y);
	    else  /* else put it just right of screen center */
		p.y = iYCenter - size.height/2;
	    if (iStrategy == 3)
	        {
		p.x += 10;
		p.y += 30;
		}
	    setLocation(p);
	    }
	else if (iStrategy == 0)
	    {
	    setLocation(iXCenter - size.width/2,iYCenter - size.height/2);
	    }
	}

      /** polite way to finish using dialog
       * Hides it, but also sets some global vars to null
       */
    public void killDialog()
        {
	setVisible(false);
	}

      /** get the window listener which was added for this dialog
       */
    public ViewportWindowMonitor getWindowListener()
        {
        return m_windowMonitor;
	}

      /** override Component method to use size set by setMinsize
       */
    public Dimension getPreferredSize()
        {
	Dimension d = super.getPreferredSize();
	if (m_MinimumSize != null)
	    {
	    if (d.width < m_MinimumSize.width)
	       d.width = m_MinimumSize.width;
	    if (d.height < m_MinimumSize.height)
	       d.height = m_MinimumSize.height;
	    }
	return d;
	}

      /** permit subclass to override Component getPreferredSize method
       *  @param  d  to use size set by setMinsize
       */
    public void setMinSize(Dimension d)
        {
	m_MinimumSize = d;
	}

      /** setup to report the named key releases to viewport
       */
    protected void setKeyEventsToViewport(String[] events)
        {
	viewProg.logViewport("setKeyEventsToViewport "+events);
	for (int i=0; i<events.length; i++)
	    m_keyEventsToViewport.add(events[i]);
	viewProg.logViewport("  vect="+m_keyEventsToViewport.size()
			     +" ("+m_keyEventsToViewport+")");
        }

      /** setup which keys dismiss the current dialog
       */
    protected void setKeyEventsToDismiss(String[] events)
        {
	for (int i=0; i<events.length; i++)
	    m_keyEventsToDismiss.add(events[i]);
	}

    public void keyPressed(KeyEvent e)
        {
	  //viewProg.logViewport("KeyPressed "+e.toString()+"="+KeyEvent.getKeyText(e.getKeyCode()));
	}

    public void keyReleased(KeyEvent e)
        {
	String czKey = KeyEvent.getKeyText(e.getKeyCode());
	viewProg.logViewport("  vect="+m_keyEventsToViewport);
	viewProg.logViewport("KeyReleased "+e.toString()+"="+czKey);
	if (m_keyEventsToViewport.size() > 0)
	    viewProg.logViewport("  vect="+m_keyEventsToViewport
				 +"; count="+m_keyEventsToViewport.size()
				 +"; first='"
				 +m_keyEventsToViewport.elementAt(0)
				 +"'");
	if (m_keyEventsToViewport.contains(czKey))
	    viewProg.SendViewportEvent(czKey);
	if (m_keyEventsToDismiss.contains(czKey))
	    killDialog();
	}

    public void keyTyped(KeyEvent e)
        {
	  //	viewProg.logViewport("KeyTyped "+e.toString()+"="+KeyEvent.getKeyText(e.getKeyCode()));
	}
    }
