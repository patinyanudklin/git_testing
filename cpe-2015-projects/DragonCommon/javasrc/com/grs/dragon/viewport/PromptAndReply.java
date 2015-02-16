//***************************************************************
//
//          PromptAndReply.java - java-based modal input boxes
//			 K.T. Rudahl
//
//          Copyright 2001-2002 by Sally Goldin & Kurt Rudahl
//***************************************************************
//
//   $Id: PromptAndReply.java,v 1.36 2007/03/18 04:18:40 goldin Exp $
//   $Log: PromptAndReply.java,v $
//   Revision 1.36  2007/03/18 04:18:40  goldin
//   Fix internationalization in VP Java controls
//
//   Revision 1.35  2006/04/19 11:01:39  goldin
//   modify prompt and reply dialogs that can take real numbers to handle commas
//
//   Revision 1.34  2006/02/07 11:04:14  goldin
//   Add some code to test driver
//
//   Revision 1.33  2006/01/15 13:07:09  goldin
//   Provide Dragon standard keyboard naviation in dialogs
//
//   Revision 1.32  2005/02/06 09:17:30  goldin
//   Fix javadoc warnings
//
//   Revision 1.31  2004/12/30 12:39:37  goldin
//   Recreate colored box each time prompt and reply initialized
//
//   Revision 1.30  2004/12/19 12:22:36  goldin
//   Fix Problem with color panel
//
//   Revision 1.29  2004/12/12 06:39:01  goldin
//   Change colorGridCanvas to plain JPanel to fix delay problem - also add inner class to makefiles
//
//   Revision 1.28  2004/12/05 14:05:43  goldin
//   Working on focus problems
//
//   Revision 1.27  2004/11/30 07:54:14  goldin
//   Revert - checked in temp version by mistake
//
//   Revision 1.26  2004/11/30 07:48:10  goldin
//   Work to make end-to-end Java build work
//
//   Revision 1.25  2002/09/15 22:27:38  goldin
//   Get rid of debug msgs
//
//   Revision 1.24  2002/09/15 22:18:23  goldin
//   put cancel button back into prompt and reply
//
//   Revision 1.23  2002/09/11 22:24:15  goldin
//   Try to fix getcolorcomponents null pointer exception
//
//   Revision 1.22  2002/09/05 01:00:04  rudahl
//   fixed initialization problem
//
//   Revision 1.21  2002/09/03 19:46:49  goldin
//   Work on prompt and reply problems
//
//   Revision 1.20  2002/02/19 20:57:45  goldin
//   Reset current color to 211 when new color file initialized
//
//   Revision 1.19  2002/02/13 01:20:14  rudahl
//   added getAbscolor to P&R
//
//   Revision 1.18  2002/01/25 18:19:03  goldin
//   Add color square to color selection dialog
//
//   Revision 1.17  2002/01/10 22:32:48  rudahl
//   fixed all validation; removed unused
//
//   Revision 1.16  2001/12/20 18:46:38  rudahl
//   fixed 2-input version for GCP
//
//   Revision 1.15  2001/11/28 17:08:30  rudahl
//   added processing of Fn-key presses
//
//   Revision 1.14  2001/11/16 16:37:47  goldin
//   Begin moving UI code to other packages as relevant
//
//   Revision 1.13  2001/11/15 20:46:41  rudahl
//   moved viewport java files to their own package
//
//   Revision 1.12  2001/11/08 21:59:54  rudahl
//    improvements in infoviewport
//
//   Revision 1.11  2001/11/05 20:28:49  rudahl
//   adapt to dragon.ui package *.java
//
//   Revision 1.10  2001/10/12 20:30:49  rudahl
//   fixed numerous problems from dragsched.lst
//
//   Revision 1.9  2001/10/04 09:01:53  rudahl
//   improvements for infotext, etc
//
//   Revision 1.8  2001/09/28 13:20:20  rudahl
//   change to permit C++ to grab Java windows
//
//   Revision 1.7  2001/09/26 15:40:19  rudahl
//   continued refinement of P&R, esp. for C/TRA
//
//   Revision 1.6  2001/09/25 20:57:39  rudahl
//   further improvements to Jni Dialogs
//
//   Revision 1.5  2001/09/24 18:11:05  rudahl
//   added JniDialog as base class, and improved or added its subclasses
//
//   Revision 1.4  2001/09/19 14:44:58  rudahl
//   improved - but not yet final - dialogs
//
//   Revision 1.3  2001/09/17 15:51:43  rudahl
//   checkpoint before making Java objects persistent within session
//
//   Revision 1.2  2001/09/14 14:06:15  rudahl
//   improved (but not final) Java P&R
//
//   Revision 1.1  2001/09/12 12:23:39  rudahl
//   added PromptAndReply to viewProg
//
//
//***************************************************************
package com.grs.dragon.viewport;

import java.util.*;
import java.io.File;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import com.grs.util.*; /* Packerlayout */
import com.grs.gui.*;
import com.grs.metricCanvas.*;

// needed msgs: 1E.0, 1E.1, %e421, VEC color number msg & help: 6030.6, 6508

public class PromptAndReply extends JniDialog 
             implements ActionListener, ListSelectionListener,
                        FocusListener

    {
    
      /* classwide fields needed to permit the actionlistener to act 
       * during PandRQuestion
       */
    protected String czDefaultButton = null; 
    protected Object theQLastObject = null;
    protected Dimension m_buttonPanelSize = null;

    protected JPanel upperPanel = null;
    protected JComponent[] m_flds = null;
    protected JTextField firstTextField = null;
    protected JButton[] button = null;
    protected boolean m_bFinished = false; /* set true by OK or CANCEL */
    protected boolean m_bAccept = false;    /* set true by OK */
    protected boolean m_bHelp = false;    /* set true by F2 */

      /**
       * Box showing selected color
       */
    //protected ColorGridCanvas selectedColor = null;
    // replace with lightweight JPanel-based class
    protected ColorPanel selectedColorPanel = null;
    protected JPanel innerPanelH = null;
    protected JPanel innerPanelV = null;
    protected int currentColorIndex = 211;
    protected int lastSelectedColorIndex = 211;
    protected ColorFileProcessor clfProcessor = null;
    protected boolean bVecColorDialog = false;
      
    JPanel innerPanel = null;

      /* clear out local data before a new plot 
       */
    public void reinit()
        {
	theQLastObject = null;
	m_flds = null;
	firstTextField = null;
	m_bFinished = false; /* set true by OK or CANCEL */
	m_bAccept = false;    /* set true by OK */
	m_bHelp = false;    /* set true by F2 */
	// get rid of color panel if it exists.
	if (selectedColorPanel != null)
	    {
	    innerPanel.remove(innerPanelV);
	    innerPanelV.remove(innerPanelH);
	    innerPanelH.remove(selectedColorPanel);
            selectedColorPanel = null;
	    innerPanelH = null;
	    innerPanelV = null;
	    }
	}

    public void valueChanged(ListSelectionEvent e)
        {
	Object o = e.getSource();
	viewProg.logViewport("ListSelection selected item "+e.getFirstIndex());
	if (o instanceof JList)
	    {
            String selected = ((JList)o).getSelectedValue().toString().trim();
	    int iBlankChar = selected.indexOf(' ');
	    String name = (iBlankChar < 0) ? selected 
	      : selected.substring(iBlankChar+1);
	    viewProg.logViewport("ListSelection = "+selected);
	    if (firstTextField != null)
	        firstTextField.setText(name);
	    //if (m_flds[0] instanceof JTextField)
	    // ((JTextField)m_flds[0]).setText(name);
	    }
	}

    public void actionPerformed(ActionEvent e)
        {
	Object o = e.getSource();
	String s = e.getActionCommand();
        viewProg.logViewport("P&R ActionPerformed cmd='"+s+"'");
	boolean bFoundIt = false;
        for (int i=0; i<m_flds.length; i++)
            if (o.equals(m_flds[i]))
	        {
		bFoundIt = true;
		}
	if (!bFoundIt)  /* so it must have a button */
	    {
	    if (s.equals("F2"))
		{
		m_bHelp = true;
		}
	    else
	        {
		m_bFinished = true;
		m_bAccept = (s.equals("F1"));
	        }
	    }
	if ((czDefaultButton != null)
	     && (theQLastObject != null) && (o != null)
	         && theQLastObject.equals(o))
	    {
	    m_bFinished = true;
	    m_bAccept = true;
	    }
	}

    public void focusGained(FocusEvent fe)
        {
	}

    public void focusLost(FocusEvent fe)
        {
	Object o = fe.getSource();
        
	//JComponent found = null;
        //for (int i=0; i<m_flds.length; i++)
        //    if (o.equals(m_flds[i]))
	//        {
	//	found = m_flds[i];
	//	}
	if ((bVecColorDialog) && (o.equals(firstTextField))) 
	    {
            String colorString = firstTextField.getText();
	    try 
	         {
		 lastSelectedColorIndex = Integer.parseInt(colorString);
		 if ((lastSelectedColorIndex < 0) ||
		     (lastSelectedColorIndex > 255))
		     {
		     firstTextField.setText("211");
		     lastSelectedColorIndex = 211;
		     }
	         }
	    catch (NumberFormatException nfe)
	         {
		 firstTextField.setText("211");
                 lastSelectedColorIndex = 211;
		 }
	    // Using the ColorGridCanvas was for some reason
	    // incredibly slow - caused visible delays - SEG 12/12/04

            //selectedColor.setOneColor(0,ColorFileProcessor.BasicColors[
	    //   clfProcessor.getCurrent3baColor(lastSelectedColorIndex)]);
            //selectedColor.replotColors();
            //selectedColor.repaint();

            selectedColorPanel.setBackground(ColorFileProcessor.BasicColors[
	       clfProcessor.getCurrent3baColor(lastSelectedColorIndex)]);

	    }
	}

    /**
     * Factorization. Find the index of the field 
     * in the m_fld array that is the same as obj.
     * @param obj  Field we are looking for
     * @return integer index into m_flds or -1 if not found.
     */
    protected int findField(Object obj)
        {
        int found = -1;
        for (int i = 0; (i < m_flds.length)&& (found < 0); i++)
	   {
           if (m_flds[i].equals(obj))
               found = i;
           } 
        return found;
        }

    /**
     * Factorization. Find the index of the field 
     * in the button array that is the same as obj.
     * @param obj  Field we are looking for
     * @return integer index into buttons or -1 if not found.
     */
    protected int findButton(Object obj)
        {
        int found = -1;
        for (int i = 0; (i < button.length)&& (found < 0); i++)
	   {
           if (button[i].equals(obj))
               found = i;
           } 
        return found;
        }

    /**
     * Factorization. Clear a text field 
     * @param index Index in m_flds. If -1 do nothing.
     */
    protected void clearField(int index)
        {
        if ((index >= 0) && (m_flds[index] instanceof JTextField))
	    ((JTextField)m_flds[index]).setText("");
        }


    /**
     * Factorization. Set the focus to the next field. Only one
     * of fldIndex or btnIndex will be non-negative. We assume that
     * the buttons are later in the tab sequence than the
     * fields.
     * @param fldIndex  Index of current field, or -1 if focus is on a button
     * @param btnIndex  Index of current button, or -1 if focus is on a field.
     */
    protected void setFocusToNext(int fldIndex, int btnIndex)
        {
        if (fldIndex >= 0)
           {
           if ((fldIndex == (m_flds.length - 1)) && (button.length > 0))
              button[0].requestFocus();
           else if ((fldIndex == (m_flds.length - 1)) && (button.length == 0))
              m_flds[0].requestFocus();
           else
              m_flds[fldIndex + 1].requestFocus();
           }
        else if (btnIndex >= 0)
           {
           if ((btnIndex == (button.length - 1)) && (m_flds.length > 0))
              m_flds[0].requestFocus();
           if ((btnIndex == (button.length - 1)) && (m_flds.length == 0))
              button[0].requestFocus();
           else
              button[btnIndex + 1].requestFocus();
           }
        }

    /**
     * Factorization. Set the focus to the previous field. Only one
     * of fldIndex or btnIndex will be non-negative. We assume that
     * the buttons are later in the tab sequence than the
     * fields.
     * @param fldIndex  Index of current field, or -1 if focus is on a button
     * @param btnIndex  Index of current button, or -1 if focus is on a field.
     */
    protected void setFocusToPrevious(int fldIndex, int btnIndex)
        {
        if (fldIndex >= 0)
           {
           if ((fldIndex == 0) && (button.length > 0))
              button[button.length-1].requestFocus();
           else if ((fldIndex == 0) && (button.length == 0))
              m_flds[m_flds.length - 1].requestFocus();
           else
              m_flds[fldIndex - 1].requestFocus();
           }
        else if (btnIndex >= 0)
           {
           if ((btnIndex == 0) && (m_flds.length > 0))
              m_flds[m_flds.length-1].requestFocus();
           else if ((btnIndex == 0) && (m_flds.length == 0))
              button[button.length -1].requestFocus();
           else 
              button[btnIndex - 1].requestFocus();
           }
        }

    public void keyPressed(KeyEvent ke)
        {
	int code = ke.getKeyCode();
        Object source = ke.getSource();
	int fldIndex = findField(source);
        int buttonIndex = findButton(source);
	switch (code)
	    {
	    case KeyEvent.VK_KP_DOWN:
	    case KeyEvent.VK_DOWN:
		setFocusToNext(fldIndex,buttonIndex);
		ke.consume();
		break;
	    case KeyEvent.VK_ENTER:
	        if (!(source instanceof JButton))
		   {
	           setFocusToNext(fldIndex,buttonIndex);
		   ke.consume();
		   }
		break;
	    case KeyEvent.VK_KP_UP:
	    case KeyEvent.VK_UP:
	        setFocusToPrevious(fldIndex,buttonIndex);
		ke.consume();
		break;
	    case KeyEvent.VK_HOME:
	        clearField(fldIndex);
		ke.consume();
		break;
	    default:
	        break;
	    }


	}

    public void keyReleased(KeyEvent e)
        {
	String czKey = KeyEvent.getKeyText(e.getKeyCode());
	viewProg.logViewport("P&R KeyReleased "+e.toString()+"="+czKey);
	if (m_keyEventsToViewport.size() > 0)
	    viewProg.logViewport("  vect="+m_keyEventsToViewport
				 +"; count="+m_keyEventsToViewport.size()
				 +"; first='"
				 +m_keyEventsToViewport.elementAt(0)
				 +"'");
	}

    public void keyTyped(KeyEvent e)
        {
	}

      /**
       * Override showIt to set the focus on the
       * first text field.
       */
    public void showIt()
        {
        int i;
        for (i = 0; i < m_flds.length; i++)
            m_flds[i].addKeyListener(this);
        for (i = 0; i < button.length; i++)
            button[i].addKeyListener(this);
	super.showIt();
	if (bVecColorDialog)
	  {
          viewProg.logViewport("setting color for color panel");
	  selectedColorPanel.setBackground(ColorFileProcessor.BasicColors[
	       clfProcessor.getCurrent3baColor(lastSelectedColorIndex)]);
	  repaint();
	  }

	JTextField focusFld = null;
	if (firstTextField != null)
	    {
	    focusFld = firstTextField;
	    } 
       
	//for (int i = 0; i < m_flds.length; i++)
	//    {
	//    if ((m_flds[i] != null) && (m_flds[i].isVisible()) &&
	//	(m_flds[i] instanceof JTextField))
	//        {
	//        focusFld = (JTextField) m_flds[i];
        //		break;
	// 	}
	//    }
	if (focusFld != null)
	    {
	    String current = focusFld.getText();
	    if ((current != null) && (current.length() > 0))
		{
		focusFld.setCaretPosition(current.length());
		}
	    focusFld.requestFocus();
	    }

	}

    PromptAndReply() { super(null); }

      /** construct a PandRQuestion panel
       *  @param   viewMsgs     keyed set of translated messages
       */
    public PromptAndReply(I18NTextSource viewMsgs)
        {
	super(viewMsgs,"PandR??");
	viewProg.logViewport("PromptAndReply ctor");
	String[] czButtons = new String[3];
	button = new JButton[3];

	czButtons[0] = viewMsgs.getI18NText("%h1E.0","OK");
	czButtons[1] = viewMsgs.getI18NText("%h9560.1","Help");
	czButtons[2] = viewMsgs.getI18NText("%h1E.1","Cancel");
	czDefaultButton = czButtons[0];

	JPanel buttonPanel = new JPanel(new PackerLayout());
	for (int i=0; i<3; i++)
	    {
	    button[i] = new JButton();
	    button[i].setText(czButtons[i]);
	    button[i].setActionCommand("F"+Integer.toString(i+1));
	    button[i].addActionListener(this);
	    buttonPanel.add("-padx 10 -side left -anchor n -expand true", button[i]);
	    }
	upperPanel = new JPanel(new PackerLayout());
	innerPanel = new JPanel(new BorderLayout());
	innerPanel.add(upperPanel,BorderLayout.CENTER);
	innerPanel.add(buttonPanel,BorderLayout.SOUTH);

	Container cp = getContentPane();
	cp.setLayout(new PackerLayout());
	cp.add("-side top -fill both -expand true -anchor n -pady 10",
	     innerPanel);
	//cp.add(innerPanel);
	m_buttonPanelSize = buttonPanel.getPreferredSize();
	viewProg.logViewport("PromptAndReply:: ctor sizes: cp="
			     +cp.getPreferredSize().width+"," 
			     +cp.getPreferredSize().height
			     +" ip="+innerPanel.getPreferredSize().width
			     +", "+innerPanel.getPreferredSize().height
			     +" bp="+m_buttonPanelSize.width
			     +", "+m_buttonPanelSize.height);
	addKeyListener(this);
	setDrawingColorFile("DEF3BA.CLF");
	}

    void killPanel()
        {
	super.killDialog();
	upperPanel.removeAll();
	if (selectedColorPanel != null)
	    innerPanel.remove(selectedColorPanel);
	upperPanel.setSize(new Dimension(0,0));
	reinit();
	}

    public void toFront(boolean bFront)
        {
	viewProg.logViewport("PromptAndReply::toFront+"+bFront);
	if (bFront)
	  toFront();
	else
	  toBack();
	}

      /** Set the location of the panel - always in the center
       */
    public void setLocation()
        {
	super.setLocation(0,null);
	}

      /**
       * Set the current color file for vector drawing.
       * Also reset the starting default to 211
       */
    public void setDrawingColorFile(String clfName)
        {
	clfProcessor = new ColorFileProcessor(clfName);
	currentColorIndex = 211;
        }

      /**
       * Return the red/green/blue components of the currently
       * selected color index, packed into a 32 bit integer.
       */
    public int getCurrentColorComponents()
        {
	Color whichColor = null;
	// should never be null - initialized in constructor
	if (clfProcessor != null)
	    {
	    whichColor = ColorFileProcessor.BasicColors[
		 clfProcessor.getCurrent3baColor(currentColorIndex)];
	    }
	else 
	    {
	    whichColor = Color.yellow;
	    }
        return whichColor.getRGB(); 
	}

      /**
       * Return the red/green/blue components of the specified
       * color index, packed into a 32 bit integer.
       * @param   iColorIndex  index into color table, in range of 0-255
       * @return  24-bit color, with blue as low byte
       */
    public int getColorComponents(int iColorIndex)
        {
	Color whichColor = null;
	if (clfProcessor != null)  
	    {
	    whichColor = ColorFileProcessor.BasicColors[
		 clfProcessor.getCurrent3baColor(iColorIndex)];
 	    }
	else 
	    {
	    whichColor = Color.yellow;
	    }
        return whichColor.getRGB(); 
	}

      /** Get results from PandRQ
       *  @param   czHelp     strings to use as help msg if they select
       *                        the middle button
       *  @return   user-supplied string, or null if user cancelled
       *           length of it is determined by m_flds
       */
    public String[] getResults(String[] czHelp)
        {
	m_bFinished = false; /* set true by OK or CANCEL */
	m_bAccept = false;
	String czRetval[] = new String[m_flds.length];
	String czButtonRetval = null;
	while (!m_bFinished && !getWindowListener().isFinished())
	    {
	    if (m_bHelp)
		{
		m_bHelp = false;
		PandRHelp(m_viewMsgs,czHelp,false);

		}
	    try
		{
		Thread.sleep(1);
		}
	    catch(Exception e)
	        {
		System.out.println("getResults thread exception");
		}
	    }
	viewProg.logViewport("P&R Q 7 finished");
	if (!m_bAccept)
	    czRetval[0] = null;
	else
	    {

	    for(int i=0; i<m_flds.length; i++)
	        {
	        if (m_flds[i] instanceof JTextField)
	             czRetval[i] = ((JTextField)m_flds[i]).getText().trim();
	        else if (m_flds[i] instanceof JList)
	            czRetval[i] 
		      = ((JList)m_flds[i]).getSelectedValue().toString().trim();
		viewProg.logViewport("PromptAndReply::getResults for fld "
				     +i+" got value="+czRetval[i]);
		}
	    }
	return czRetval;
	}

      /** set size on dialog based on measuring components 
       */
    public void setupSize()
        {
	int count = upperPanel.getComponentCount();
	int iHeight = 0;
	int iWidth = 0;
	pack();
	for (int i=0;i<count; i++)
	    {
	    Dimension d1 = upperPanel.getComponent(i).getPreferredSize();
	    Dimension d2 = upperPanel.getComponent(i).getSize();
	    iHeight += d2.height;
	    if (iWidth < d2.width) 
	        iWidth = d2.width; 
	    }
	// Full of magic numbers, but these are based on actual measurements
	upperPanel.setSize(new Dimension(iWidth+23,iHeight+10));
	Container cp = getContentPane();
	//	iHeight = cp.getSize().height + m_buttonPanelSize.height;
	//iWidth = cp.getSize().width;
	iHeight += m_buttonPanelSize.height;
	if (iWidth < m_buttonPanelSize.width)
	    iWidth = m_buttonPanelSize.width;
	innerPanel.setSize(new Dimension(iWidth,iHeight));
	iHeight += 80;
	iWidth += 50;
	setSize(new Dimension(iWidth,iHeight));
	}

      /** Set up a complex component for Question panel
       *  depending on 'bNew' this either puts up a text field plus a list,
       *  or just a list.
       *  @param   czPrompt     strings to use as prompt 
       *  @param   czDefault    default value
       *  @param   czChoices    array of choices for list
       *  @param   bNew         true => user may supply new value
       *                        else must choose existing value
       */
    public void setupPrompts(String[] czPrompt,
			     String czDefault,
			     String[] czChoices,
			     boolean bNew)
       throws Exception
        {
	viewProg.logViewport("PromptAndReply::setupPrompts (en) complex with "
			     +czChoices.length+" choices");
	String[] czChoiceList = new String[czChoices.length];
	for (int i=0; i<czChoices.length; i++)
	    {
	    int j = i+1;
	    czChoiceList[i] = "("+j+")   "+czChoices[i];
	    }
	JList fld2 = new JList(czChoiceList);
	upperPanel.add("-side top -padx 10 -pady 5 -anchor nw",
		       new JLabel(czPrompt[0]));
	if (bNew)
	    {
	    m_flds = new JTextField[1];
	    JTextField fld = new JTextField(czDefault,32); 
	    m_flds[0] = fld;
	    firstTextField = fld;
	    fld.addActionListener(this);
	    fld.addFocusListener(this);
	    fld.setActionCommand("F4");
	    upperPanel.add("-side top -padx 20 -anchor nw -fill x",m_flds[0]);
	    if (czChoices.length > 0)
	        {
		upperPanel.add("-side top -padx 10 -pady 5 -anchor nw",
			       new JLabel(czPrompt[1]));
		fld2.setVisibleRowCount(czChoices.length);
		fld2.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		fld2.addListSelectionListener(this);
		}
	    }
	else /* not tested yet */
	    {
	    if (czChoices.length == 0)
	        throw new Exception("PromptAndReply: no choices available for user");
	    m_flds[0] = fld2;
	    }
	if (czChoices.length > 0)
	    {
	    JScrollPane sp 
	      = new JScrollPane(fld2,
			ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
			ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
	    pack();
	    upperPanel.add("-side top -padx 20 -anchor nw -fill x",sp);
	    }
	/*
	if (bNew)
	    {
	    JTextArea chList = new JTextArea(czChoices.length,26);
	    chList.setEditable(false);
	    for (int i=0; i<czChoices.length; i++)
	        {
		chList.append(czChoices[i]);
		if (i < czChoices.length - 1)
		    chList.append("\n");
		}
	    //list.setVisibleRowCount(czChoices.length);
	    //    list.setPreferredSize(new Dimension(500,400));
	    JScrollPane sp 
	      = new JScrollPane(chList,
			ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
			ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
	    pack();
	    upperPanel.add("-side top -pady 10 -anchor n ",sp);
	    }
	    */			 
	theQLastObject = m_flds[0];
	setupSize();
	viewProg.logViewport("PromptAndReply::setupPrompts (ex)");
	}

      /** Set up a set of components for Question panel
       *  @param   czPrompt     string array of strings to use as prompts
       *  @param   czDefault    string array of default values
       *                        There MUST be a non-null default corresp
       *                        to each prompt
       */
    public void setupPrompts(String[] czPrompt,
			     String[] czDefault)
        {
	viewProg.logViewport("PromptAndReply::setupPrompts (en) has "
			     +czPrompt.length+" prompts");
	m_flds = new JTextField[czPrompt.length];
	for (int i=0; i<czPrompt.length; i++)
	    {
	    upperPanel.add("-side top -padx 10 -pady 5 -anchor nw",
			    new JLabel(czPrompt[i]));
	    JTextField fld = new JTextField(czDefault[i],20);
	    if (i == 0)
	       firstTextField = fld;
	    m_flds[i] = fld;
	    fld.addActionListener(this);
	    fld.addFocusListener(this);
	    upperPanel.add("-side top -padx 20 -anchor nw",m_flds[i]);
	    theQLastObject = m_flds[i];
	    }
	setupSize();
	viewProg.logViewport("PromptAndReply::setupPrompts (ex)");
	}

      /** Ask for a single user-supplied value with no default
       *  @param   czPrompt     string array of strings to use as prompts
       *  @param   czDefault    string array of default values
       *  @param   bShowCancel  if true, show cancel btn else do not
       *                        There MUST be a non-null default corresp
       *                        to each prompt
       */
    protected void PandRQuestion(String[] czPrompt,
				 String[] czDefault,
				 boolean bShowCancel)
        {
	setupPrompts(czPrompt,czDefault);
	/** Just ignore the cancel button specification for now
	if (bShowCancel)
	    button[2].setVisible(true);
	else
	    button[2].setVisible(false);
	    ****/
	setLocation();
	showIt();
	}
      
      /** Provide some help info, usually because user provided incorrect
       *  response to question
       *  @param   viewMsgs     keyed set of translated messages
       *  @param   czMsg        help msg (internationalized)
       *  @param   bError       true => error msg false => std help
       */
    protected void PandRHelp(I18NTextSource viewMsgs,
			     String[] czMsg,boolean bError)
        {
	InfoText pIT = new InfoText(viewMsgs);
	String[] czInfo;
	int msgNo = 0;
	if (bError)
	    {
	    czInfo = new String[1+czMsg.length];
	    czInfo[msgNo++] = "%e421";
	    }
	else
	    {
	    czInfo = new String[czMsg.length];
	    }
	for (int i=0; i<czMsg.length; i++)
	    czInfo[i+msgNo] = czMsg[i];
	pIT.setupContents("HELP",czInfo);
	pIT.showIt();
	// force it to be topmost and immovable
	viewProg.SetPandRNCDialogTopmost(true); // 'true' => release it
	viewProg.FixupNCDialog("HELP","",false);
	pIT.waitAndKill();
	viewProg.SetPandRNCDialogTopmost(false);
	}
      
      /** setup to ask for the desired viewport zoom factor.
       *  @param   czDefault    ignored
       *  @param   czParams     not used
       */
    public void setupZoomFactorPane(String czDefault,
				    String[] czParams)
        {
	String[] czPrompts = new String[1];
	String[] czDefaults = new String[1];
	czPrompts[0] = m_viewMsgs.getI18NText("%h9560.5","Scale_Factor");
	czDefaults[0] = "2.0";
	PandRQuestion(czPrompts,czDefaults,true);
	}

      /** get the desired viewport zoom factor.
       *  @param   czParams     not used
       */
    public String getZoomFactorPane(String[] czParams)
        {
	String[] czHelp = { "%h9585.0", //"Bad zoom value"
			    "%h9585.1" } ;
	String czRetval = null;
	String[] czReplies = null;
	boolean bOK = false;
	while (!bOK)
	    {
	    czReplies = getResults(czHelp);
	    if ((czReplies != null) && (czReplies.length > 0)
		   && (czReplies[0] != null))
	        {
		czRetval = czReplies[0];
		try
		    {
		    /* handle possible European number format */
                    czRetval = czRetval.replace(',','.');
		    float val = Float.valueOf(czRetval).floatValue();
		    if ((val > 1.0) && (val < 10.0))
		        bOK = true;
		    }
		catch (NumberFormatException e)
		  { 
		    System.out.println("Zoomfactor number exception");
		  }
		if (!bOK)
		    {
		    PandRHelp(m_viewMsgs,czHelp,true);
		    }
		}
	    else
	        bOK = true; /* user cancel? */
	    }
	//System.out.println("zoom czRetval="+czRetval);
	return czRetval;
	}

      /** setup to ask for the desiredname for GCP point
       *  @param   czDefault    used as default
       *  @param   czParams     not used
       */
    public void setupGCPNamePane(String czDefault,
			      String[] czParams)
        {
	String[] czPrompts = new String[1];
	czPrompts[0] = m_viewMsgs.getI18NText("%h9900.17","GCPName");
	String[] czDefaults = new String[1];
	czDefaults[0] = (czDefault != null) ? czDefault : "";
	PandRQuestion(czPrompts,czDefaults,false);
	}

      /** get the desired name for GCP point
       *  @param   czParams     set of parameters whose need depends on
       *                        czOperation. 
       *                        For GCPName, czParams is a list of already
       *                        used point names.
       */
    public String getGCPNamePane(String[] czParams)
        {
	String[] czHelp = { "%h9740.0","%h9740.1" } ; // ,"Bad point name");
	String czRetval = null;
	String[] czReplies = null;
	boolean bOK = false;
	while (!bOK)
	    {
	    czReplies = getResults(czHelp);
	    if ((czReplies != null) && (czReplies.length > 0)
		   && (czReplies[0] != null))
	        {
		czRetval = czReplies[0];
		if((czRetval.length() > 0) && (czRetval.length() <= 32) 
		       && (czRetval.indexOf(' ') < 0)
		       && (czRetval.indexOf('\'') < 0)
		       && (czRetval.indexOf('"') < 0))
		    {
		    int i;
		    bOK = true;
		    if (czParams != null)
		        for (i=0; i<czParams.length; i++)
			    if (czRetval.equals(czParams[i]))
			        bOK = false;
		    }
		if (!bOK)
		    {
		    PandRHelp(m_viewMsgs,czHelp,true);
		    }
		}
	    else
	        bOK = true; /* user cancel? */
	    }
	return czRetval;
	}

      /** set up to ask for the coords of a GCP point
       *  @param   czDefault    ignored
       *  @param   czParams     not used
       */
    public void setupGCPCoordsPane(String czDefault,
				   String[] czParams)
        {
	String[] czPrompts = new String[2];
	String[] czDefaults = new String[2];
	czPrompts[0] = m_viewMsgs.getI18NText("%h9900.19","GCP_X_coord");
	czPrompts[1] = m_viewMsgs.getI18NText("%h9900.20","GCP_Y_coord");
	czDefaults[0] = "";
	czDefaults[1] = "";
	PandRQuestion(czPrompts,czDefaults,true);
	}

      /** get the coords of a GCP point
       *  @param   czParams     set of parameters whose need depends on
       *                        czOperation
       */
    public String getGCPCoordsPane(String[] czParams)
        {
	String[] czHelp = { "%h9750.0" } ; //,"Bad point name");
	String czRetval = null;
	String[] czReplies = null;
	boolean bOK = false;
	while (!bOK)
	    {
	    czReplies = getResults(czHelp);
	    if ((czReplies != null) && (czReplies.length > 1)
		   && (czReplies[0] != null)
		   && (czReplies[1] != null))
	        {
		czRetval = czReplies[0]+"\n"+czReplies[1];
                czRetval = czRetval.replace(',','.');
		try
		    {
		      /* handle possible European format */
                    czReplies[0] = czReplies[0].replace(',','.');
                    czReplies[1] = czReplies[1].replace(',','.');
		    float val = Float.valueOf(czReplies[0]).floatValue();
		    float val2 = Float.valueOf(czReplies[1]).floatValue();
		    bOK = true; // if above conversions succeeded
		    }
		catch (NumberFormatException e)
		    { 
		    System.out.println("GCPCoords number exception");
		    }
		if (!bOK)
		    {
		    PandRHelp(m_viewMsgs,czHelp,true);
		    }
		}
	    else
	        bOK = true; /* user cancel? */
	    }
	return czRetval;
	}

      /** Setup to ask for the desired class name for TRA
       *  @param   czDefault    ignored
       *  @param   czParams     set of parameters whose meaning depends on
       *                        czOperation
       *                        For TRAClassName, czParams is a list of already
       *                        used class names.
       */
    public void setupTRAClassNamePane(String czDefault,
					String[] czParams)
       throws Exception
        {
	viewProg.logViewport("P&R TRAClassName");
	String[] czPrompt = new String[2];
	czPrompt[0] = m_viewMsgs.getI18NText("%h9900.15","Class_Name");
	czPrompt[1] = m_viewMsgs.getI18NText("%h9900.25","Existing classes");
	setupPrompts(czPrompt,czDefault,czParams,true);
	setLocation();
	showIt();
	}

      /** get the desired class name for TRA
       *  @param   czParams     not used
       */
    public String getTRAClassNamePane(String[] czParams)
        {
        boolean bOK = false;
	String[] czHelp = new String[1];
	czHelp[0] = "%h9730.0"; //,"Class name");
	String czRetval = null;
	String[] czReplies = null;
	while (!bOK)
	    {
	    czReplies = getResults(czHelp);
	    if ((czReplies != null) && (czReplies.length > 0)
		   && (czReplies[0] != null))
	        {
		czRetval = czReplies[0];
		viewProg.logViewport("P&R TRAClassName got results"
                                         +" retval='"+czRetval+"'");
		if((czRetval.length() > 0) && (czRetval.length() <= 32)
		   //		       && (czRetval.indexOf(' ') < 0)
		       && (czRetval.indexOf('\'') < 0)
		       && (czRetval.indexOf('"') < 0))
		    {
		      //    int i;
		      //int iFoundIndex = -1;
		    bOK = true;
		    }
		if (!bOK)
		    {
		    PandRHelp(m_viewMsgs,czHelp,true);
		    }
		}
	    else
	        bOK = true; /* user cancel? */
	    }
	return czRetval;
	}

      /** setup to ask for the desired class number for VEC
       *  @param   czDefault    used as default
       *  @param   czParams     not used
       */
    public void setupVECColorNumberPane(String czDefault,
				     String[] czParams)
        {
	String[] czPrompts = new String[1];
	String[] czDefaults = new String[1];
	czPrompts[0] = m_viewMsgs.getI18NText("%h6910.4","Color Number");
        int pos = czPrompts[0].indexOf("=");
        if (pos > 0)
            czPrompts[0] = czPrompts[0].substring(0,pos-1);
	czDefaults[0] = String.valueOf(currentColorIndex);
	PandRQuestion(czPrompts,czDefaults,true);
	if (clfProcessor == null)
	    {
	    clfProcessor = new ColorFileProcessor("." +
						  File.separator +
						  "DEF3BA.CLF");
	    }

	// Need to recreate and redo the layout every time
	// because the viewport reuses the same dialog for
	// all operations
        //if (selectedColorPanel == null)
	    {
            selectedColorPanel = new ColorPanel();
	    innerPanelH = new JPanel(new BorderLayout());
	    innerPanelV = new JPanel(new BorderLayout());
	    // use two more border layouts to contrain both width and height.
	    innerPanelH.add(selectedColorPanel, BorderLayout.EAST);
	    innerPanelV.add(innerPanelH, BorderLayout.NORTH);
	    innerPanel.add(innerPanelV, BorderLayout.EAST);
	    }

        JTextField fld = (JTextField) m_flds[0];
	firstTextField = fld;
	fld.setText(String.valueOf(currentColorIndex));
	selectedColorPanel.setBackground(ColorFileProcessor.BasicColors[
		   clfProcessor.getCurrent3baColor(currentColorIndex)]);
	bVecColorDialog = true;
	pack();
	setLocation();
	showIt();
	}

      /** get the desired class number for VEC
       *  @param   czParams     not used
       */
    public String getVECColorNumberPane(String[] czParams)
        {
	String[] czHelp = { "%h6508.0" }; // ,"Number from 0-255");
	String czRetval = null;
	String[] czReplies = null;
	boolean bOK = false;
	while (!bOK)
	    {
	    czReplies = getResults(czHelp);
	    if ((czReplies != null) && (czReplies.length > 0)
		   && (czReplies[0] != null))
	        {
		czRetval = czReplies[0];
		try
		    {
		    int val = Integer.valueOf(czRetval).intValue();
		    if ((val >= 0) && (val < 256))
		        bOK = true;
		    currentColorIndex = val;
		    }
		catch (NumberFormatException e)
		    { 
		    System.out.println("VecColor number exception");
		    }
		if (!bOK)
		    {
		    PandRHelp(m_viewMsgs,czHelp,true);
		    }
		}
	    else
	        bOK = true; /* canceled? */
	    }
	return czRetval;
	}

      /** construct a modal panel matching whatever czOperation calls for.
       *  Essentially, there is one value of czOperation for each specific
       *  modal box.
       *  @param   czOperation  one of 'ZoomFactor',
       *                          'GCPName', 'GCPCoords', 
       *                          'TRAClassName',
       *                          'ColorSelector',
       *  @param   czDefault    String which may (depending on czOperation)
       *                        be used as a default
       *                        If multiple defaults are needed, they are
       *                        concatinated with a '\n' delimiter
       *  @param   czParams     set of parameters whose need depends on
       *                        czOperation
       */
    public void setupPromptAndReply(String czOperation,
				   String czDefault,
				   String[] czParams)
       throws Exception
        {
	viewProg.logViewport("p&r setup op="+czOperation);
	bVecColorDialog = false;
	if (czOperation.equals("ZoomFactor"))
	    setupZoomFactorPane(czDefault,czParams);
	else if (czOperation.equals("GCPName"))
	    setupGCPNamePane(czDefault,czParams);
	else if (czOperation.equals("GCPCoords"))
	    setupGCPCoordsPane(czDefault,czParams);
	else if (czOperation.equals("TRAClassName"))
	    setupTRAClassNamePane(czDefault,czParams);
	else if (czOperation.equals("ColorSelector"))
	    setupVECColorNumberPane(czDefault,czParams);
	}

      /** retrieve value from panel matching whatever czOperation calls for.
       *  Essentially, there is one value of czOperation for each specific
       *  modal box.
       *  @param   czOperation  one of 'ZoomFactor', 
       *                          'GCPName', 'GCPCoords', 
       *                          'TRAClassName',
       *                          'ColorSelector',
       *  @param   czParams     set of parameters whose need depends on
       *                        czOperation
       *  @return  reply string supplied by user, or "YES","NO","OK","CANCEL"
       *                        corresponding to button pushed, or null.
       *                        If multiple replies are needed, they are
       *                        concatinated with a '\n' delimiter
       *                        
       */
    public String getPromptAndReply(String czOperation,
				   String[] czParams)
        {
	String czRetval = "";
	viewProg.logViewport("p&r get="+czOperation);
	if (czOperation.equals("ZoomFactor"))
	    czRetval = getZoomFactorPane(czParams);
	else if (czOperation.equals("GCPName"))
	    czRetval = getGCPNamePane(czParams);
	else if (czOperation.equals("GCPCoords"))
	    czRetval = getGCPCoordsPane(czParams);
	else if (czOperation.equals("TRAClassName"))
	    czRetval = getTRAClassNamePane(czParams);
	else if (czOperation.equals("ColorSelector"))
	    czRetval = getVECColorNumberPane(czParams);
	//System.out.println("P&R returns "+czRetval);
	killPanel();
	return czRetval;
	}

    public static void main(String[] args) 
        {
	System.out.println("P&R (en)");
	try
	    {
	    I18NTextSource i18nMessages = new I18NTextSource("EN/view.msg");
	    PromptAndReply pr = new PromptAndReply(i18nMessages);
	    System.out.println("P&R");
	    pr.setupPromptAndReply("ZoomFactor","",null);
	    String czRetval = pr.getPromptAndReply("ZoomFactor",null);
	    System.out.println("P&R returns "+czRetval);
	    String[] czClasses = { "first class","tourist class","classy"}; 
	    pr.setupPromptAndReply("TRAClassName","fred",czClasses);
	    czRetval = pr.getPromptAndReply("TRAClassName",czClasses);
	    System.out.println("P&R returns "+czRetval);
            int components = pr.getColorComponents(255);
            System.out.println("getColorComponents returns " + 
                    Integer.toHexString(components));

	    }
	catch (Exception e)
	    {
	    System.out.println("exception "+e.getMessage());
	    }
	System.exit(1);
	}

      /* Inner class to create a fixed size JPanel that can
       * be used to show colors.
       */
    class ColorPanel extends JPanel
        {
          protected Dimension idealDim = new Dimension(32,32);

	  public ColorPanel()
             {
	     super();
	     setBorder(BorderFactory.createEtchedBorder());
             }
	  /** 
           * Override getPreferredSize to that we
           * can control the size.
           */
          public Dimension getPreferredSize()
	     {
             return idealDim;
	     }  
	  /** 
           * Override getMiniumSize to that we
           * can control the size.
           */
          public Dimension getMinimumSize()
	     {
             return idealDim;
	     }  
	  /** 
           * Override getMaximumize to that we
           * can control the size.
           */
          public Dimension getMaximumSize()
	     {
             return idealDim;
	     }  

        }     


    }



