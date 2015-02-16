/****************************************************************
 *
 *          JniFrame.java - 
 *             Base class for InfoViewports.
 *			 K.T. Rudahl & S.E. Goldin
 *
 *          Copyright 2005 by Sally Goldin and Kurt Rudahl
 ****************************************************************
 *
 *   $Id: JniFrame.java,v 1.3 2006/02/25 05:40:27 goldin Exp $
 *   $Log: JniFrame.java,v $
 *   Revision 1.3  2006/02/25 05:40:27  goldin
 *   Fallback in small screen is to position infoviewport way to the left
 *
 *   Revision 1.2  2006/02/12 07:54:18  goldin
 *   Make graph windows pop to the top
 *
 *   Revision 1.1  2005/11/22 03:24:11  goldin
 *   Update to be consistent with 5.6 - use frame for histograms and scatterplots so they'll have icons
 *
 *   Revision 1.1  2005/08/14 07:13:58  goldin
 *   New base clas to allow InfoViewport to have icons on taskbar
 *
 *
 ****************************************************************
 */
package com.grs.dragon.viewport;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import com.grs.gui.*;

abstract public class JniFrame extends JFrame implements KeyListener
    {

    protected I18NTextSource m_viewMsgs = null;
    protected ViewportWindowMonitor m_windowMonitor = null;
    protected Dimension m_MinimumSize = null;
    protected Vector m_keyEventsToViewport = new Vector();
    protected Vector m_keyEventsToDismiss = new Vector();

      /** construct a dialog setting font and I18N source
       *  @param viewMsgs  source of keyed I18N'd messages
       *  @param czTitle   title line or key
       */
    public JniFrame(I18NTextSource viewMsgs,String czTitle )
        {
	viewProg.logViewport("JniFrame ctor");
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
	setIconImage(new ImageIcon("viewnew.gif").getImage());
  	}

      /** construct a dialog setting font only
       *  @param czTitle   title line (key not possible)
       */
    public JniFrame(String czTitle)
        {
	this(null,czTitle);
	}

      /** display the dialog
       */
    public void showIt()
        {
	setVisible(true);
	requestFocus();
	toFront();
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
	    else  /* else small screen, try putting it at the left edge */
	        {
		p.x = 0;
	        p.y = 100;
                }
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
