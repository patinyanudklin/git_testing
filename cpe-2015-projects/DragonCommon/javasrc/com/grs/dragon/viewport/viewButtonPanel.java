/****************************************************************
 *
 *          viewButtonPanel.java - java-based button panel for viewport
 *			 K.T. Rudahl
 *
 *          Copyright 2001 by Sally Goldin & Kurt Rudahl
 ****************************************************************
 *
 *   $Id: viewButtonPanel.java,v 1.30 2007/01/07 11:34:05 goldin Exp $
 *   $Log: viewButtonPanel.java,v $
 *   Revision 1.30  2007/01/07 11:34:05  goldin
 *   Change handling of CUR to display data window report
 *
 *   Revision 1.29  2007/01/07 05:29:43  goldin
 *   Changes for CUR
 *
 *   Revision 1.28  2005/12/30 10:33:34  goldin
 *   Make button panel text area shorter
 *
 *   Revision 1.27  2005/02/06 09:17:30  goldin
 *   Fix javadoc warnings
 *
 *   Revision 1.26  2002/07/25 22:35:00  goldin
 *   make sure that headings change in CUR
 *
 *   Revision 1.25  2002/05/16 00:29:18  goldin
 *   put MEA/CUR buttons on bottom
 *
 *   Revision 1.24  2002/05/03 15:14:49  goldin
 *   Optimize to improve speed
 *
 *   Revision 1.23  2002/03/08 03:14:50  rudahl
 *   added some keys to keyevent list
 *
 *   Revision 1.22  2002/02/08 20:25:04  rudahl
 *   improved CUR buttonpanel sizing and table
 *
 *   Revision 1.21  2001/11/28 17:08:30  rudahl
 *   added processing of Fn-key presses
 *
 *   Revision 1.20  2001/11/16 16:37:47  goldin
 *   Begin moving UI code to other packages as relevant
 *
 *   Revision 1.19  2001/11/15 20:46:40  rudahl
 *   moved viewport java files to their own package
 *
 *   Revision 1.18  2001/11/09 19:03:23  rudahl
 *   MEA text area and button sizing
 *
 *   Revision 1.17  2001/11/08 21:59:54  rudahl
 *    improvements in infoviewport
 *
 *   Revision 1.16  2001/11/07 18:48:51  rudahl
 *   add support for changing button labels, for MEA
 *
 *   Revision 1.15  2001/11/05 20:28:49  rudahl
 *   adapt to dragon.ui package *.java
 *
 *   Revision 1.14  2001/10/12 20:30:26  rudahl
 *   fixed numerous problems from dragsched.lst
 *
 *   Revision 1.13  2001/10/08 15:12:05  rudahl
 *   fixup U CUR table
 *
 *   Revision 1.12  2001/10/06 11:47:04  rudahl
 *   button id error
 *
 *   Revision 1.11  2001/10/01 15:41:04  rudahl
 *   refining the panels
 *
 *   Revision 1.10  2001/09/28 13:20:20  rudahl
 *   change to permit C++ to grab Java windows
 *
 *   Revision 1.9  2001/09/26 15:40:20  rudahl
 *   continued refinement of P&R, esp. for C/TRA
 *
 *   Revision 1.8  2001/09/25 20:57:39  rudahl
 *   further improvements to Jni Dialogs
 *
 *   Revision 1.7  2001/09/24 18:11:05  rudahl
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
import java.io.*;
import javax.swing.*;
import com.grs.util.*; /* Packerlayout */
import com.grs.gui.*;

public class viewButtonPanel extends JniDialog implements ActionListener
    {
    public void actionPerformed(ActionEvent e)
        {
	viewProg.logViewport("Key "+e.getActionCommand()+" pressed");
	viewProg.SendViewportEvent(e.getActionCommand());
	}

      /** construct a button panel containing all buttons and labels 
       *  All 10 buttons plus a text area are created.
       *  @param viewMsgs  source of keyed I18N'd messages
       *  @param czTitle   title line or key
       */
    public viewButtonPanel(I18NTextSource viewMsgs,String czTitle)
        {
	super(viewMsgs,czTitle);
	textDisplayArea = null;
	czTableContents = "</table>";
	czTableHeader = "";
	viewProg.logViewport("viewButtonPanel ctor");

	//	setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
	//	addWindowListener(new ViewportWindowMonitor());
	Container cp = getContentPane();
	//Font font = new Font("LucidaSans",Font.PLAIN,12);
	//setFont(font);
	//cp.setLayout(new PackerLayout());
	//cp.setLayout(new FlowLayout());
	cp.setLayout(new BorderLayout());
	buttonsP.setLayout(new GridLayout(10,1));
	for (int i=0; i<10; i++)
	    {
	    button[i]= new JButton("F");
	    button[i].setActionCommand("F"+Integer.toString(i+1));
	    button[i].addActionListener(this);
	    // don't need tooltips, since these aren't icons
	    //	    button[i].setToolTipText("button tooltip");
	    }
        // create the main text display area
	iButtonHt = button[0].getPreferredSize().height;
        textDisplayArea = new JEditorPane();
        textDisplayArea.setContentType("text/html");
        textDisplayArea.setEditable(false);
	//        textDisplayArea.setPreferredSize(new Dimension(500,300));
	//pack();
	//	textDisplayArea.setPreferredSize(new Dimension(300,450));
        JPanel innerPanel = new JPanel(new BorderLayout());
        JScrollPane scroller = new JScrollPane(textDisplayArea,
			ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS,
			ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
	//pack();
        innerPanel.add(scroller, BorderLayout.CENTER);
	//innerPanel.setPreferredSize(new Dimension(550,350));
        outerPanel = new JPanel(new BorderLayout());
        outerPanel.setBorder(BorderFactory.createMatteBorder(10,10,10,10,
                             getBackground()));
	//pack();
	outerPanel.add(innerPanel,BorderLayout.CENTER);
	m_OriginalDimension = getSize();
	m_OriginalCpDimension = cp.getPreferredSize();
	setKeyEventsToViewport(new String[]{"F1","F2","F3","F4","F5",
					    "F6","F7","F8","F9","F10",
					    "Insert","Delete","Escape",
					    "Up","Down","Left","Right"});
	}

      /** Set up a set of components for Question panel
       *  @param   czOperation  one of "CUR", "GCP", etc
       *  @param   czHeadings   actual or keyed column headings, or null
       *                        (If key search fails, use as actual)
       *                        The number and sequence of headings defines
       *                        the table layout
       *  @param   parentArea   screen coords occupied by parent VP,
       *                        or all zeroes
       */
    public void setupControls(String czOperation,
			      String[] czHeadings,
			      Rectangle parentArea) 
        {
	boolean bTextArea = false;   /* select one of two layouts */
	GridLayout gLayout = null;
	String[] jsButtonKeys = null;
        String[] jsButtonLabels = null;
	String[] jsHeadingLabels = null;
	int iRows = 0;
	int iCols = 0;
	if (czOperation.equals("CUR"))
	    {
	    bTextArea = true;        /* enable text area display */
	    iCols = 2;
	    iRows = 1;
	    jsButtonKeys = jsCurButtonKeys;
	    if (jsCurButtonLabels == null)
	        {
	        jsCurButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsCurButtonLabels;
	    if (czHeadings != null)
	        {
                if ((curHeadingLabels == null) || (lastHeadings == null))
		    curHeadingLabels = initializeLabels(czHeadings);
		else if (differentArrays(lastHeadings,czHeadings))
		    curHeadingLabels = initializeLabels(czHeadings);
                lastHeadings = czHeadings;
		jsHeadingLabels = curHeadingLabels;
		}
	    }
	else if (czOperation.equals("VEC"))
	    {
	    jsButtonKeys = jsVecButtonKeys;
	    if (jsVecButtonLabels == null)
	        {
	        jsVecButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsVecButtonLabels;
	    }
	else if (czOperation.equals("MEA"))
	    {
	    bTextArea = true;        /* enable text area display */
	    iCols = 2;
	    iRows = 3;
	    jsButtonKeys = jsMeaButtonKeys;
	    if (jsMeaButtonLabels == null)
	        {
	        jsMeaButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsMeaButtonLabels;
	    if (czHeadings != null)
	        {
                if (meaHeadingLabels == null)
		    meaHeadingLabels = initializeLabels(czHeadings);
		jsHeadingLabels = meaHeadingLabels;
		}
	    }
	else if (czOperation.equals("COO"))
	    {
	    jsButtonKeys = jsCooButtonKeys;
	    if (jsCooButtonLabels == null)
	        {
	        jsCooButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsCooButtonLabels;
	    }
	else if (czOperation.equals("GCP"))
	    {
	    jsButtonKeys = jsGcpButtonKeys;
	    if (jsGcpButtonLabels == null)
	        {
	        jsGcpButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsGcpButtonLabels;
	    }
	else if (czOperation.equals("COL"))
	  // no longer used 
	    {
	    jsButtonKeys = jsColButtonKeys;
	    if (jsColButtonLabels == null)
 	        {
	        jsColButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsColButtonLabels;
	    }
	else if (czOperation.equals("TRA"))
	    {
	    jsButtonKeys = jsTraButtonKeys;
	    if (jsTraButtonLabels == null)
 	        {
	        jsTraButtonLabels = initializeLabels(jsButtonKeys);
	        }
	    jsButtonLabels = jsTraButtonLabels;
	    }
	if (iRows == 0)
	    {
	    iRows = countButtonLabels(jsButtonLabels);
	    iCols = 1;
	    }

	//viewProg.logViewport("viewButtonPanel::SetupControls op="+czOperation
	//		     +" bText="+bTextArea);
	//viewProg.logViewport("            hdrs="+czHeadings
	//		     +" parentArea="+parentArea);
	Container cp = getContentPane();
	    // buttonsP only used if bTextArea
	gLayout = (GridLayout)	buttonsP.getLayout();
	gLayout.setColumns(iCols);
	gLayout.setRows(0);

	int iButtonCount = 0;
        int len = jsButtonLabels.length;
	for (int i=0; i<len; i++)
	    {
  	    if ((jsButtonLabels != null) && (jsButtonLabels[i] != null)
		  && (jsButtonLabels[i].length() > 0))
	        {
		button[i].setText(jsButtonLabels[i]);
		buttonsP.add(button[i]);
		iButtonCount++;
		}
	    }
	cp.add(buttonsP,BorderLayout.SOUTH);
	pack();
	if (bTextArea)
	    {
	    boolean bCurWindow = false;
	    StringBuffer buffer = new StringBuffer();
	    String initialText = null;
	    if (czHeadings != null)
	        {
		len = jsHeadingLabels.length;
		buffer.append("<table align=center cellpadding=2><tr>");
		for (int i=0; i< len; i++)
		    {
		    buffer.append("<th nowrap style=\"font: 12pt\">");
                    buffer.append(jsHeadingLabels[i]);
		    buffer.append("</th>");
		    }
		buffer.append("</tr>");
		czTableHeader = buffer.toString();
		buffer.append(czTableContents);
		initialText = buffer.toString();
		textDisplayArea.setText(initialText);
		}
	    if ((initialText.indexOf("#") < 0) &&
		(czOperation.equals("CUR")))
                bCurWindow = true;
	    cp.add(outerPanel,BorderLayout.CENTER);
	    Dimension tdSize = textDisplayArea.getPreferredSize();
            if (bCurWindow)
	        {
		tdSize.width = 700;
		tdSize.height = 350;
		}
	    else if (czOperation.equals("CUR"))
	        {
		tdSize.width += tdSize.width; /* 1.75 (was1.5) * width */
		tdSize.width -= tdSize.width/4;
		tdSize.height = 200;
		}
	    else  /* MEA */
	        {
		tdSize.width = 400;
		tdSize.height = 200;
		}
	    setSize(tdSize);
	    //viewProg.logViewport("viewButtonPanel::SetupControls text setsize="
	    //+tdSize.width+","+tdSize.height);
	    }
	else
	    {
	    Dimension cpSize = cp.getPreferredSize();
	    int iHt = iButtonHt * iButtonCount; // + 65;
	    cpSize.width += cpSize.width/3;/* 1.3 * width */
	    setSize(cpSize.width,iHt); 
	    pack();
	    }
	setLocation((bTextArea) ? 2 : 1,parentArea);
	}

      /**
       * Factorization. Returns true if the two passed string
       * arrays have different contents, else false 
       * @param array1 First array to compare
       * @param array2 Second array to compare
       * @return True if arrays do NOT match, false if they do.
       */
    protected boolean differentArrays(String[] array1, String[] array2)
        {
	boolean bDifferent = false;
	if (array1.length != array2.length)
	    bDifferent = true;
	else
	    {
	    int len = array1.length;
	    for (int i = 0; i < len; i++)
	        {
		if (array1[i].compareTo(array2[i]) != 0)
		    {
		    bDifferent = true;
		    break;
		    }
		}
	    }
	return bDifferent;
        }


      /* polite way to finish using panel.
       * Hides it, but also sets some global vars to null
       */
    void killPanel()
        {
	super.killDialog();
	Container cp = getContentPane();
	int count = cp.getComponentCount();
	//System.out.println("killPanel: cp has "+cp.getComponentCount()
	//		   +" components");
	buttonsP.removeAll();
	cp.removeAll();
	
	//System.out.println("killPanel: (ex) cp has "+cp.getComponentCount()
	//		   +" components");
	}

      /**
       * Factorization. Looks up the keys in the the keys array,
       * allocates the labels array and stores the strings there.
       * @param keys  Array of i18N keys - some likely blank or null
       * @return  Initialized array of xlated strings
       */
    protected String[] initializeLabels(String[] keys)
        {
	int len = keys.length;
	String[]labels = new String[len];
	for (int i = 0; i < len; i++)
	    {
	    String msg = "";
	    if ((keys[i] != null) && (keys[i].length() > 0))
	        {
	        msg = keys[i];
	        if (m_viewMsgs != null)
		      msg = m_viewMsgs.getI18NText(keys[i],
  					           keys[i]);
		}
	    labels[i] = msg;
	    }
        return labels;
	}

      /**
       * Figure out how many buttons are needed based on
       * how many non-empty labels are in the passed array.
       * @param labels  Array of labels for buttons
       * @return count of non-blank,non-null labels 
       */
    protected int countButtonLabels(String[] labels)
        {
	int count = 0;
	int len = labels.length;
	for (int i = 0; i < len; i++)
	    {
	    if ((labels[i] != null) && (labels[i].length() > 0))
	         count++;
	    }
	return count;
	}

    static String[] jsCurButtonKeys 
       = { "%h9900.12","","","","","","","", "%h9900.6","" } ; 
    static String[] jsVecButtonKeys 
       = { "%h9900.0","","%h9900.7","%h9900.24","",
	   "%h9900.2","%h9900.3","%h9900.4", "%h9900.5","%h9900.8" } ; 
      /* 9900.2/.10 and 9900.3/.11 share button */
    static String[] jsMeaButtonKeys 
       = { "%h9900.12","","","%h9900.24","",
	   "%h9900.10","%h9900.11","%h9900.9", "%h9900.6","" } ; 
    static String[] jsCooButtonKeys 
       = { "%h9900.0","","","%h9900.24","",
	   "","%h9900.3","", "%h9900.5","%h9900.8" } ; 
    static String[] jsGcpButtonKeys 
       = { "%h9900.0","","","%h9900.24","", "","","", 
	   "%h9900.5","%h9900.8" } ; 
    static String[] jsColButtonKeys 
       = { "%h9900.0","","","","","","","", "","" } ; 
    static String[] jsTraButtonKeys 
       = { "%h9900.0","","","%h9900.24","",
	   "%h9900.13","","", "%h9900.5","%h9900.8" } ; 

    static String[] jsCurButtonLabels = null;
    static String[] jsVecButtonLabels = null;
    static String[] jsMeaButtonLabels = null;
    static String[] jsCooButtonLabels = null;
    static String[] jsGcpButtonLabels = null;
    static String[] jsColButtonLabels = null;
    static String[] jsTraButtonLabels = null;
    static String[] meaHeadingLabels = null;
    static String[] curHeadingLabels = null;
    static String[] lastHeadings = null;

      /* clear out local data before a new plot 
       */
    public void reinit()
        {
	czTableContents = "</table>";
	czTableHeader = "";
	textDisplayArea.setText("");
	setSize(m_OriginalDimension);
	getContentPane().setSize(m_OriginalCpDimension);
	}

    protected JPanel buttonsP = new JPanel();
    protected JButton[] button = new JButton[10];
      /* the table area */
    protected JEditorPane textDisplayArea = null;
    protected String czTableHeader = null;
    protected String czTableContents = null;
    protected JPanel outerPanel = null;
    protected int iButtonHt = 0;
    protected Dimension m_OriginalDimension = null;
    protected Dimension m_OriginalCpDimension = null;

      /** enable/disable one of the visible buttons
       *  @param  iButtonIndex   button number 0 to 9, matching F1 .. F10
       *  @param  bEnable        true => enable false => disable
       *  @param  pczLabel       text or key to display.
       */
    public void setButtonEnabled(int iButtonIndex, boolean bEnable,
				 String pczLabel)
        {
	if (m_viewMsgs != null)
	    {
	    String msg = m_viewMsgs.getI18NText(pczLabel,"Key = "+pczLabel);
	    button[iButtonIndex].setText(msg);
	    }
	button[iButtonIndex].setEnabled(bEnable);
        }

      /** add a line of text to an already-existing table
       *  @param  czText   line of text already formatted as HTML
       *  @param  replaceFlag  if 1, replace contents rather than adding to
       *                   existing.
       */
    public void addTableLine(String czText, int replaceFlag)
        {
	//   outputToTemp(czText);
	if (textDisplayArea != null)
	    {
	    if (replaceFlag == 1)
                {
		czTableContents = czText; // replace
		textDisplayArea.setText(czTableContents);
                }
            else
		{
		czTableContents = czText+czTableContents; // prefix new line
		textDisplayArea.setText(czTableHeader+czTableContents);
		}
	    viewProg.logViewport("viewButtonPanel::AddTableLine full table=\n"
                                 +czTableContents);
	    }
	}


    /** @link dependency */
    /*#JniDialog lnkJniDialog;*/

    public void outputToTemp(String outputString)
	{
        try
	    {
	    BufferedWriter writer = new BufferedWriter
	        (new FileWriter("javaout.tmp",true));
            writer.write("Time: " + new Date().toString() + " -- ");
	    writer.write(outputString);
	    writer.newLine();
            writer.close();
	    }
	catch (IOException ioe)
            {
	    Toolkit.getDefaultToolkit().beep();
            ioe.printStackTrace();
            }
	    
        }

    }

