/* InfoText.java
 * kurt rudahl 10/24/01
 * copyright Sally Goldin & Kurt Rudahl
 * purpose:
 *      Display a modal box of HTML text, with an OK button 
 ***************************************************************************
 * $Id: InfoText.java,v 1.13 2005/02/06 09:17:30 goldin Exp $
 * $Log: InfoText.java,v $
 * Revision 1.13  2005/02/06 09:17:30  goldin
 * Fix javadoc warnings
 *
 * Revision 1.12  2002/04/16 20:10:07  rudahl
 * added support for '&' and '<' in messages
 *
 * Revision 1.11  2001/11/28 17:08:30  rudahl
 * added processing of Fn-key presses
 *
 * Revision 1.10  2001/11/16 16:37:47  goldin
 * Begin moving UI code to other packages as relevant
 *
 * Revision 1.9  2001/11/15 20:46:41  rudahl
 * moved viewport java files to their own package
 *
 * Revision 1.8  2001/11/08 21:59:27  rudahl
 *  improvements in infoviewport
 *
 * Revision 1.7  2001/11/05 20:28:49  rudahl
 * adapt to dragon.ui package *.java
 *
 * Revision 1.6  2001/10/04 09:01:52  rudahl
 * improvements for infotext, etc
 *
 * Revision 1.5  2001/10/01 15:41:04  rudahl
 * refining the panels
 *
 * Revision 1.4  2001/09/28 13:20:20  rudahl
 * change to permit C++ to grab Java windows
 *
 * Revision 1.3  2001/09/26 15:40:55  rudahl
 * continued refinement of P&R, esp. for C/TRA
 *
 * Revision 1.2  2001/09/25 20:58:07  rudahl
 * further improvements to Jni Dialogs
 *
 * Revision 1.1  2001/09/24 18:11:05  rudahl
 * added JniDialog as base class, and improved or added its subclasses
 *
 ****************************************************************************
 * history 10/24/2001   created
 *                       Generated by Together
 */
package com.grs.dragon.viewport;

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.text.*;
import com.grs.gui.*;

public class InfoText extends JniDialog implements ActionListener
    {
    protected boolean m_bFinished = false; /* set true by OK */
    protected JEditorPane textDisplayArea = null;
    protected Dimension bpSize;

      /* clear out local data before a new plot 
       */
    public void reinit()
        {
	m_bFinished = false; /* set true by OK */
	}

    public void actionPerformed(ActionEvent e)
        {
	String s = e.getActionCommand();
	killDialog();
        viewProg.logViewport("InfoText ActionPerformed cmd='"+s+"'");
	m_bFinished = true;
	}

    public InfoText() { super(null); }

      /** construct an InfoText panel
       *  @param   viewMsgs     keyed set of translated messages
       */
    public InfoText(I18NTextSource viewMsgs)
        {
	super(viewMsgs,"InfoText??");
	viewProg.logViewport("InfoText::ctor (en)");

	JButton button = new JButton(viewMsgs.getI18NText("%h1E.0","OK"));
	button.setActionCommand("OK");
	button.addActionListener(this);
	JPanel buttonPanel = new JPanel();
	buttonPanel.add(button);
        textDisplayArea = new JEditorPane();
        textDisplayArea.setContentType("text/html");
        textDisplayArea.setEditable(false);
	//        scroller = new JScrollPane(textDisplayArea,
	//	ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED,
	//	ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
	//	scroller.getViewport().setViewSize(new Dimension (80,80));
	//jScrollArea = new JPanel();
	//jScrollArea.add(scroller);
	Container cp = getContentPane();
	//  cp.add(scroller, BorderLayout.CENTER);

	//	cp.setLayout(new PackerLayout());
	//cp.add("-side top -pady 10 -padx 10 -fill both -expand true -anchor n",
	//       textDisplayArea);
        //cp.add("-side bottom -pady 10 -expand false -anchor s",
	//       buttonPanel);

	cp.setLayout(new BorderLayout());
	cp.add(textDisplayArea, BorderLayout.CENTER);
        cp.add(buttonPanel, BorderLayout.SOUTH);
	bpSize = buttonPanel.getPreferredSize();

	//	setMinSize(new Dimension(350,300));
	//	m_buttonSize = button.getPreferredSize();
	viewProg.logViewport("InfoText::ctor (ex)");
	}

      /** set contents of box 
       *  @param   czTitle    title or key to title for dialog
       *  @param   czInfo     String containing info or key to info
       *                      to display.
       */
    public void setupContents(String czTitle, String czInfo)
        {
	viewProg.logViewport("InfoText::setup1 (en) info="+czInfo);
	setTitle(m_viewMsgs.getI18NText(czTitle,czTitle));
	textDisplayArea.setText(m_viewMsgs.getI18NText(czInfo,czInfo));
	Container cp = getContentPane();
	textDisplayArea.setMaximumSize(new Dimension(350,1000));
	//	textDisplayArea.pack();
	TextUI ui = textDisplayArea.getUI();
	View view = ui.getRootView(textDisplayArea);
	Dimension d = textDisplayArea.getPreferredSize(); 
	viewProg.logViewport("text area sz = "+d); //+" lineCount="
	   //	     +textDisplayArea.getLineCount());
	//jScrollArea.setPreferredSize(textDisplayArea.getPreferredSize());
	//jScrollArea.setMinimumSize(new Dimension(300,200));
	//	setSize(getContentPane().getPreferredSize());
	//scroller.getViewport().setViewSize(new Dimension (80,80));
	//setSize(new Dimension (350,100));

	// the following is totally ad-hoc, but works OK for the moment
	// we're assuming no scrolling needed
	int iMul = (d.width+349)/350;
	d.width = 350;
	if (iMul > 1)
	    d.height *= (iMul * 2);
	//	d.height *= 2;
	d.height += bpSize.height;
	//d.height += 150;
	setSize(d);
	setLocation(0,null);
	}

      /** set contents of box 
       *  @param   czTitle    title or key to title for dialog
       *  @param   Info       Strings containing info or key to info
       *                      to display.
       *                      For each item, if first char is not '<',
       *                      then that item is formatted as a <p></p>  
       */
    public void setupContents(String czTitle, String[] Info)
        {
	viewProg.logViewport("InfoText::setup2 (en)");
	String czInfo = "";
	for (int i=0; i<Info.length; i++)
	    {
	    if (Info[i].startsWith("<"))
	        czInfo += Info[i] + "\n";
	    else
	        {
		String msg = m_viewMsgs.getI18NText(Info[i],Info[i]);
		while(msg.indexOf('&') >= 0)
		    {
		    int index = msg.indexOf('&');
		    String head = msg.substring(0,index);
		    String tail = msg.substring(index+1);
		    msg = head + "&amp;" + tail;
		    }
		while(msg.indexOf('<') >= 0)
		    {
		    int index = msg.indexOf('<');
		    String head = msg.substring(0,index);
		    String tail = msg.substring(index+1);
		    msg = head + "&lt;" + tail;
		    }
	        czInfo += "<p>" + msg + "</p>\n";
		}
	    }
	setupContents(czTitle,czInfo);
	viewProg.logViewport("InfoText::setup2 (ex)");
	}

      /** wait for user to close it; then kill it
       */
    public void waitAndKill()
        {
	viewProg.logViewport("InfoText::wait (en)");
	m_bFinished = false;
	//	showIt();
	while(!m_bFinished && !getWindowListener().isFinished())
	    {
	    try
	        {
		Thread.sleep(1);
		}
	    catch (Exception e) 
	        {
		System.out.println("showandWait thread exception");
		}
	    }
	killDialog();
	}

    public static void main(String[] args) 
        {
	try
	    {
	    I18NTextSource i18nMessages = new I18NTextSource("EN/view.msg");
	    InfoText pr = new InfoText(i18nMessages);
	    String czInfo 
	        = "<p>paragraph</p><ol><li>irst</li><li>second></ol>";
	    String[] Info = { "Paragraph1Item","<ul><li>item</li></ul>",
	              "raph1Item","<ul><li>item</li></ul>",
	              "raph1Item","<ul><li>item</li></ul>"};
	    pr.setupContents("xxFred",Info);
	    pr.showIt();
	    pr.waitAndKill();
	    }
	catch (Exception e)
	    {
	    System.out.println("exception "+e.getMessage());
	    }
	System.exit(1);
	}

    }