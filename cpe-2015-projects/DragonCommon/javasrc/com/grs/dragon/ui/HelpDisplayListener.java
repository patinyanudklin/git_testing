/**
 * HelpDisplayListener
 *   
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 1/29/2001
 *
 *  $Id: HelpDisplayListener.java,v 1.22 2007/01/08 07:55:56 goldin Exp $
 *  $Log: HelpDisplayListener.java,v $
 *  Revision 1.22  2007/01/08 07:55:56  goldin
 *  refine behavior
 *
 *  Revision 1.21  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.20  2006/12/31 09:25:07  goldin
 *  Implement modifiable help display
 *
 *  Revision 1.19  2006/12/15 11:10:31  goldin
 *  Make a click in a field cancel the pending or visible help
 *
 *  Revision 1.18  2006/12/10 06:26:59  goldin
 *  Fine tune help behavior - cancel if the user starts typing or brings up a file chooser
 *
 *  Revision 1.17  2006/12/10 05:02:28  goldin
 *  Make delay be a symbol for easy modification
 *
 *  Revision 1.16  2006/12/10 04:53:50  goldin
 *  fine tuning of new help capabilities
 *
 *  Revision 1.15  2006/12/09 12:44:59  goldin
 *  change help to be a popup
 *
 *  Revision 1.14  2002/04/16 18:15:02  goldin
 *  Move pspec to end of help
 *
 *  Revision 1.13  2002/04/15 23:59:53  goldin
 *  Move pspec to end of help msg
 *
 *  Revision 1.12  2002/04/11 16:35:50  goldin
 *  Make reg subarea be doubles
 *
 *  Revision 1.11  2002/03/22 23:52:49  goldin
 *  Fix misc. bugs
 *
 *  Revision 1.10  2001/11/30 18:01:21  goldin
 *  Moved most of the UI basic components to the com.grs.gui package
 *
 *  Revision 1.9  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.8  2001/06/26 18:39:47  goldin
 *  add tracing for debug
 *
 *  Revision 1.7  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.6  2001/03/27 18:21:20  goldin
 *  get rid of debug msgs
 *
 *  Revision 1.5  2001/03/20 18:04:15  goldin
 *  Implement tabbed panes, clean up menu help:
 *
 *  Revision 1.4  2001/03/20 13:32:04  goldin
 *  Add help editing and viewing for menu items
 *
 *  Revision 1.3  2001/02/28 16:24:29  goldin
 *  implementing defaults, enhancements to help editor
 *
 *  Revision 1.2  2001/02/28 11:50:12  goldin
 *  Extend mouse handling to checkbuttons and push buttons
 *
 *  Revision 1.1  2001/02/08 16:15:39  goldin
 *  Add facility to display help in response to mouse enter events
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.border.*;

/**
 * This class is an extension of MouseInputAdapter. It is used
 * to display the help msg associated with a control when the
 * mouse enters the panel for that control.*/
public class HelpDisplayListener extends MouseAdapter
    {
	/* Delay before help comes up - in milliseconds */
    protected static int HELPDELAY = 2000;

     /* Screen size. We will initialize this once
      * during the constructor.
      */
    protected Dimension screenSize = null;

     /* default size of popup window.
      * we will adjust based on the text length 
      */  
    protected int width = 400;
    protected int height = 200;
    protected Dimension windowSize = null;

      /**
       * Place to display the help text.
       */
    protected JEditorPane helpArea = null;


      /** Window to pop up. Only create one. */
    protected JWindow helpWindow = null;

      /**
       * Scrollbar governing this text.
       */
    protected JScrollBar verticalBar = null;

      /**
       * Parent ui object.*/
    protected DragonUI parentUI = null;

    protected static String pSpecifierLabel = null;

      /** 
       * source of most recent mouse entered event.
       */   
    Object latestSource = null;

      /**
       * Latest control for which help has been displayed.
       * Used to prevent "flashing"
       */
    Object latestHelpControl = null; 

      /**
       * Constructor initializes the ref to parent,
       * creates window and text component to display help.
       */
    public HelpDisplayListener(DragonUI parentUI)
        {
	helpArea = new JEditorPane();
	helpArea.setContentType("text/html");
	helpArea.setEditable(false);
        helpArea.setBackground(new Color(255,255,200));
        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(new EtchedBorder());
        panel.add(helpArea, BorderLayout.CENTER);
        helpWindow = new JWindow(parentUI);
        helpWindow.getContentPane().add(panel,BorderLayout.CENTER);
        windowSize = new Dimension(width, height);
	this.parentUI = parentUI;
	if (pSpecifierLabel == null)
	   pSpecifierLabel = parentUI.getTextSource().getI18NText("%h10.2",
							 "Pspec");
        screenSize = Toolkit.getDefaultToolkit().getScreenSize();
	}

      /**
       * Alternative constructor used for installer, where helpArea
       * is part of the parent window. 
       */
    public HelpDisplayListener(JEditorPane hArea,
                               JScrollBar verticalScroll,
			       DragonUI parentUI)
        {
	this.helpArea = hArea;
        this.verticalBar = verticalScroll;
	this.parentUI = parentUI;
	if (pSpecifierLabel == null)
	   pSpecifierLabel = parentUI.getTextSource().getI18NText("%h10.2",
							 "Pspec");
	}

      /**
       * Override the MouseEntered method. Display help when mouse
       * enters the control.
       */
    public void mouseEntered(MouseEvent e)
        {
	//if (!parentUI.isHelpSelected())
	//return;
	// don't process the event if the right or middle mouse btn is down
	int modifiers = e.getModifiers();
	if ((modifiers & 
            (InputEvent.BUTTON2_MASK | InputEvent.BUTTON3_MASK)) != 0)
	    return;
        latestSource = e.getSource();
        if (helpWindow == null)  /* no delay */
           { 
	   processHelpEvent(e);
	   }
        else
	   {
	   HelpHelper helper = new HelpHelper(e);
           Timer timer = new Timer(HELPDELAY,helper);
           timer.setRepeats(false);
	   timer.start();
           }
        } 

      /**
       * Override the MouseClicked method. Cancels any 
       * pending help display.
       */
    public void mousePressed(MouseEvent e)
        {
        if (helpWindow != null)
            {
            if (helpWindow.isVisible())
                {
		/* If the mouse is IN the window, because the
		 * window came up on top of the former mouse
		 * position, don't take the window away. 
		 */
		if (helpWindow.getMousePosition() == null)  
	            helpWindow.setVisible(false);
		}
	    latestSource = null;
            }
        } 

      /** 
       * Factorization. Display help either immediately or
       * after a delay.
       * @param e Original mouse event from mouse entered.
       */ 
   protected void processHelpEvent(MouseEvent e)
        {
	DragonField field = null;
	DragonMenuItem item = null;
        DragonMenu menu = null;
	String help = null;
        int ycoord = 0;
	Object source = e.getSource();
        if (source != latestSource)
            return;  /* didn't stay long enough in the field */
	if (source instanceof DragonField)
	    {
	    field = (DragonField) source;
	    }
	else if (source instanceof DragonMenuItem)
	    {
            item = (DragonMenuItem) source;
	    }
	else if (source instanceof DragonMenu)
	    {
            menu = (DragonMenu) source;
	    }
	else 
	    {
	    JComponent src = (JComponent) source;
	    Object parent = src.getClientProperty(DragonField.PARENT_FIELD);
	    if (parent != null)
	        {
                field = (DragonField) parent;
		}
	    }

        if (field != null)
	    {
	    if (field == latestHelpControl)
                return;
            if ((!field.isShowing()) ||
                (field.getMousePosition() == null) ||
                (DragonFileChooser.isChooserShowing()))
                return;
            try 
		{
		ycoord = (int) field.getLocationOnScreen().getY();
		}
            catch (Exception badcomp)
                {
		    /* throws a runtime exception if the 
                     * component is no longer visible.
                     * This can happen if we are exiting
                     */
                }
	    help = field.getHelpString();
            String pSpec = field.getPSpecifier();
	    if ((help != null) && 
		(pSpec != null) && 
		(pSpec.length() > 1))
	        {
		StringBuffer buffer = new StringBuffer();
		int pos = help.lastIndexOf("</P>");
		if (pos < 0)
		   {
		   pos = help.indexOf("</BODY>");
		   }
		if (pos >=0)
		   {
	           buffer.append(help.substring(0,pos));
		   }
		else
		   {
		   buffer.append(help);
		   }
   	        buffer.append("<br><i>[" + pSpecifierLabel + ":");
                buffer.append("&nbsp;"  + pSpec + "]");
		buffer.append("</i>\n");
		if (pos >= 0)
                   buffer.append(help.substring(pos));
                help = buffer.toString();
		}
	    latestHelpControl = field;
            /* schedule an event to clear latestHelpControl
             * within 2 x helpdelay if the user hasn't
             * moved the mouse elsewhere.
	     */
	    StateResetter resetter = new StateResetter(latestHelpControl);
	    Timer timer = new Timer(HELPDELAY,resetter);
	    timer.setRepeats(false);
	    timer.start();
	    }
	else if (item != null)
	    {
	    if (item == latestHelpControl)
                return;
            JComponent c = (JComponent) item;
            if (!c.isShowing())
                return; 
	    help = item.getHelpString();
	    String command = item.getCommandString();
	    if ((help != null) &&
		(command != null) && 
		(command.length() > 1))
	        {
		StringBuffer buffer = new StringBuffer();
		int pos = help.indexOf("<BODY>");
	        buffer.append(help.substring(0,pos+6));
   	        buffer.append("<i>[" + command + "]&nbsp;&nbsp");
		buffer.append("</i>\n" + help.substring(pos+6));
                help = buffer.toString();
		}
            latestHelpControl = item;
	    }
	else if (menu != null)
	    {
	    if (menu == latestHelpControl)
		return;
            if (!menu.isShowing())
                return;
	    help = menu.getHelpString();
            latestHelpControl = menu;
	    }
	if (help != null)
	    {
	    helpArea.setText(help);
            if (helpWindow != null)
		{
		int xcoord = 0;
                Dimension d = helpArea.getPreferredSize();
                width = d.width + 10;
                if (width > 600)
		    width = 600;
                int lines = d.width/width + 1;
                if (d.width > 600) lines = lines - 1;
                height = lines * (d.height+5);
		//System.out.println("desired: " + d.width + "x" + d.height +
		//		   " computed " + width + "x" + height);
                windowSize.width = width;
                windowSize.height = height;
		helpWindow.setPreferredSize(windowSize);
		helpWindow.pack();

		Point p = new Point();
                p = parentUI.getLocation(p);
                Dimension size = new Dimension();
		size = parentUI.getSize(size);
                if (ycoord == 0)
                    ycoord = p.y + 10;
                xcoord = p.x + (int)(size.width * 0.5);
                if (xcoord + windowSize.width > screenSize.width)
                    {
		    int adjust = (xcoord + windowSize.width) - screenSize.width
                                + 10; 
                    xcoord -= adjust;
                    } 
                helpWindow.setLocation(xcoord,ycoord);
		helpWindow.setVisible(true);
		}
            else
		{
	        helpArea.setCaretPosition(0);
		}
	    }
	else
	    {
	    helpArea.setText("");
	    }
	if (parentUI.getShowKeys())
	    {
	    if (field != null)
                parentUI.displayKeys(field);
	    else if (item != null)
                parentUI.displayKeys(item);
	    }
	}


      /**
       * Override the MouseExited method. Clear help when mouse
       * leaves the control.
       */
    public void mouseExited(MouseEvent e)
        {
       //if (!parentUI.isHelpSelected())
       //return;
	// don't process the event if the right or middle mouse btn is down
	int modifiers = e.getModifiers();
	if ((modifiers & 
            (InputEvent.BUTTON2_MASK | InputEvent.BUTTON3_MASK)) != 0)
	    return;
        if ((helpWindow != null) && (helpWindow.isVisible()))
            {
	    /* If the mouse is IN the window, because the
	     * window came up on top of the former mouse
	     * position, don't take the window away. 
	     */
	    if (helpWindow.getMousePosition() == null)  
	        helpWindow.setVisible(false);
            }
	else
            {
	    helpArea.setText("");
            }
        latestSource = null;
	}

	/**
	 * Allow an external class to change the help delay.
         * @param delay  New delay value in milliseconds
	 */
    static public void setHelpDelay(int delay)
	{
	HELPDELAY = delay;
	}
   
    /**
     * Nested class implementing ActionListener which
     * is responsible for doing a delayed display of  
     * help.
     */
    class HelpHelper implements ActionListener
        {
         /* set by constructor, used to make sure we are 
          * still in the relevant field. 
          */
        MouseEvent triggerEvent = null;
    
        public HelpHelper(MouseEvent e)
            {
    	    triggerEvent = e;
	    }
    
         /**
          * Method from action listener 
          */
        public void actionPerformed(ActionEvent e)
            {
    	    processHelpEvent(triggerEvent);
            }
    
	}


    /**
     * Nested class implementing ActionListener which
     * is responsible for doing a delayed clear of  
     * latestHelpControl if it is still set to
     * the same value.
     */
    class StateResetter implements ActionListener
        {
         /* set by constructor. If this is equal to
	  * latestHelpControl when the timer fires,
	  * we will clear the state.
          */
	Object helpControl = null; 

    
        public StateResetter(Object control)
            {
	    helpControl = control;
	    }
    
         /**
          * Method from action listener 
          */
        public void actionPerformed(ActionEvent e)
            {
	    if (latestHelpControl == helpControl)
		latestHelpControl = null;
            }
    
	}
    
    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: HelpDisplayListener.java,v 1.22 2007/01/08 07:55:56 goldin Exp $ \n";
	}
    }
