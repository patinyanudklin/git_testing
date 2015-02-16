/**
 *  ManReader
 *
 *  Copyright 2001 by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 5/29/2001
 *
 *  $Id: ManReader.java,v 1.26 2007/05/31 03:26:53 rudahl Exp $
 *  $Log: ManReader.java,v $
 *  Revision 1.26  2007/05/31 03:26:53  rudahl
 *  add 'whatis' boilerplate
 *
 *  Revision 1.25  2007/05/13 07:45:41  goldin
 *  Make manreader title reflect the product name
 *
 *  Revision 1.24  2006/04/28 11:01:34  goldin
 *  bring up 1st page in standalone manreader
 *
 *  Revision 1.23  2006/03/05 04:44:51  goldin
 *  Try to get manreader to pop to the front
 *
 *  Revision 1.22  2006/03/04 09:33:56  goldin
 *  *** empty log message ***
 *
 *  Revision 1.21  2005/08/03 04:42:53  goldin
 *  Comment out references to Win32WindowRecorder for now
 *
 *  Revision 1.20  2005/02/06 08:39:04  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.19  2003/02/21 12:04:13  rudahl
 *  Make scrollbars always visible; next and previous topic always go to next page
 *
 *  Revision 1.18  2002/09/26 15:26:49  goldin
 *  change icon
 *
 *  Revision 1.17  2002/09/20 14:22:27  goldin
 *  Call recordWindowByTitle instead of just recordWindow
 *
 *  Revision 1.16  2002/09/19 22:36:21  goldin
 *  Add calls to record handle in DRAGON.INI
 *
 *  Revision 1.15  2002/07/19 23:02:50  goldin
 *  Improve error handling when toc cannot be found
 *
 *  Revision 1.13  2002/07/19 19:51:17  goldin
 *  Give an error msg and exit if can't find TOC
 *
 *  Revision 1.12  2002/07/18 20:34:02  goldin
 *  Don't expect tempdir as argument, but instead read from config file
 *
 *  Revision 1.11  2002/06/28 14:19:46  goldin
 *  Fix minor bug in handling of successive SHOW commands
 *
 *  Revision 1.10  2002/06/27 21:30:48  goldin
 *  Miscellaneous refinements to behavior and appearance
 *
 *  Revision 1.9  2002/06/24 18:04:59  goldin
 *  Continue development for productization
 *
 *  Revision 1.8  2001/12/03 16:25:57  goldin
 *  Move SimpleWindowMonitor to common pkg
 *
 *  Revision 1.7  2001/11/29 15:16:39  goldin
 *  Various enhancements including improvement of display, add -H argument, etc.
 *
 *  Revision 1.6  2001/11/28 15:30:54  goldin
 *  Add command processing
 *
 *  Revision 1.5  2001/11/28 13:11:31  goldin
 *  Implement next/previous
 *
 *  Revision 1.4  2001/11/27 17:38:19  goldin
 *  Add capability to set details
 *
 *  Revision 1.2  2001/11/26 14:00:09  goldin
 *  Continue basic implementation of ManReader
 *
 *  Revision 1.1  2001/11/21 16:05:50  goldin
 *  begin implementing
 *
 *  Revision 1.2  2001/06/01 13:54:21  goldin
 *  Make ManReader work as an app
 *
 *  Revision 1.1  2001/05/29 14:17:40  goldin
 *  Initial code for dragon manual reader
 *
 */

package com.grs.dragon.manReader;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import com.grs.dragon.ipc.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;

/**
 * This class provides a user interface for people to
 * read the Dragon user manual. It is an applet, but
 * can also be run as a standalone application.
 */
public class ManReader extends JApplet implements ActionListener,
                                                  ChangeListener
    {
    protected static boolean bInitHidden = false;
    protected static final String INIT_ERR_MSG =
      "Manual Reader cannot access Table of Contents File; Manual Reader exiting";


    protected boolean bInitialized = false;

    protected String documentBase = new String("." + File.separator + "doc");

      /**
       * Tabbed pane used to display different types of
       * information.
       */
    protected JTabbedPane tabbedPane = null;

      /**
       * Editor panes used to show each category of information
       */

    protected DragonHtmlPane descriptionArea = null;
    protected DragonHtmlPane detailsArea = null;

      /**
       * components for the tabs.
       */
    protected TocTreePanel contentsArea = null;
    protected JPanel descripPanel = null;
    protected JPanel detailsPanel = null;
    protected JScrollPane descripScroller = null;
    protected JScrollPane detailsScroller = null;

      /**
       * Buttons for control.
       */
    protected JButton prevBtn = null;
    protected JButton nextBtn = null;
    protected JButton originalBtn = null;

      /**
       * Label for the Description area.
       */
    protected JLabel descripLabel = null;

    protected int detailIndex = -1;

      /**
       * Hold on to the id of the original topic.
       */
    protected String originalTopicId = null;

      /**
       * Hold on to the current TOC node.
       */
    protected TocTreeNode currentTocNode = null;

      /**
       * If true, was invoked from Dragon
       */
    protected boolean bFromDragon = false;


      /**
       * Init method sets up the UI.
       * @param baseDirectory  Directory where the input files are located
       * @param bHidden        If true, invoked by Dragon
       */
    public void init(String baseDirectory, boolean bHidden)
        {
	bFromDragon = bHidden;
        if (baseDirectory != null)
	    documentBase = baseDirectory;
        JPanel mainPanel = new JPanel(new BorderLayout());
	tabbedPane = new JTabbedPane();
        contentsArea = new TocTreePanel(this);
	tabbedPane.addTab("Contents",contentsArea);
        descriptionArea = new DragonHtmlPane(documentBase);
	descripPanel = new JPanel(new BorderLayout());
        descripPanel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
	descripPanel.setPreferredSize(new Dimension(600,600));
        descripLabel = new JLabel("Description: ");
	descripLabel.setFont(new Font("Lucida Sans Unicode",Font.BOLD,14));
	descripPanel.add(descripLabel,BorderLayout.NORTH);
	descripScroller = new JScrollPane(descriptionArea);
	descripScroller.setVerticalScrollBarPolicy(
			     JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
	descripPanel.add(descripScroller,BorderLayout.CENTER);
	tabbedPane.addTab("Description",descripPanel);
        detailsArea =  new DragonHtmlPane(documentBase);
	detailsPanel = new JPanel(new BorderLayout());
        detailsPanel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
	detailsPanel.setPreferredSize(new Dimension(600,600));
	detailsScroller = new JScrollPane(detailsArea);
	detailsScroller.setVerticalScrollBarPolicy(
			     JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
	detailsPanel.add(detailsScroller,BorderLayout.CENTER);
	tabbedPane.addTab("Details",detailsPanel);
        mainPanel.add(tabbedPane,BorderLayout.CENTER);
        JPanel buttonPanel = new JPanel(new FlowLayout());
        prevBtn = new JButton("Previous Topic");
        prevBtn.addActionListener(this);
        buttonPanel.add(prevBtn);
	nextBtn = new JButton("Next Topic");
        nextBtn.addActionListener(this);
        buttonPanel.add(nextBtn);
	originalBtn = new JButton("Original Topic");
        originalBtn.addActionListener(this);
        buttonPanel.add(originalBtn);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);
        getContentPane().add(mainPanel, BorderLayout.CENTER);
	detailIndex = tabbedPane.indexOfTab("Details");
	tabbedPane.addChangeListener(this);
	tabbedPane.setEnabledAt(detailIndex,false);
        enableButtons(null);
	setVisible(true);
        bInitialized = contentsArea.initialize(documentBase +
				File.separator +"toc.xml");
        if (!bInitialized)
	    {
            if (bFromDragon)
                sendInitializeError();
	    else 
	        showInitializeError();
	    }
        else
	    {
	    setTopic("1");
	    }
          
	}

      /**
       * Factorization sends a message to the UI to
       * inform user that the toc file could not be found.
       */
    protected void sendInitializeError()
        {
        long timeOffset = ApplicationManager.getTimeOffset();
	String msgFileName = null;
        StringBuffer buffer = new StringBuffer();
        buffer.append(ApplicationManager.getTempPath() + 
                      File.separator + "MsgMR999");
        buffer.append(".$$$");
        msgFileName = buffer.toString();
	long timestamp = (new Date().getTime() - timeOffset)/1000;
	String timeString = String.valueOf(timestamp);     
	StringBuffer contents = new StringBuffer();
	contents.append("( ");
	contents.append(IpcFile.ZEROS.substring(0,12 - timeString.length()));
	contents.append(timeString + " 00000 1 )\n");
	contents.append(INIT_ERR_MSG + "\n");
	int fileLen = contents.length();
        int fileLen2 = fileLen;
        int startPos = 0;
	if (fileLen < 10)
	    startPos = 19;
	else if (fileLen < 100)
            startPos = 18;
        else if (fileLen < 1000)
            startPos = 17;
        else if (fileLen < 10000)
            startPos = 16;
        else 
	    startPos = 15;
	contents = contents.replace(startPos,20,String.valueOf(fileLen));
	try
	    {
            byte[] bArray = contents.toString().getBytes("UTF-8");
            fileLen2 = bArray.length;
            //System.out.println("After UTF-8 translation, fileLen is " +
            //               fileLen2);
            if (fileLen2 != fileLen)
	         {
		 if (fileLen2 < 10)
		    startPos = 19;
		 else if (fileLen2 < 100)
		    startPos = 18;
		 else if (fileLen2 < 1000)
		    startPos = 17;
		 else if (fileLen2 < 10000)
		    startPos = 16;
		 else 
		    startPos = 15;
	         contents = contents.replace(startPos,20,
					     String.valueOf(fileLen2));
		 }
 	    FileOutputStream fos = new FileOutputStream(msgFileName);
 	    OutputStreamWriter osw = new OutputStreamWriter(fos,"UTF-8");
	    BufferedWriter writer = new BufferedWriter(osw);
	    writer.write(contents.toString());
	    writer.close();
	    }
	catch (IOException ioe)
	    {
	      // not much we can do
	    }
	}				

      /**
       * Factorization. Puts up a local JOptionPane dialog if not
       * running in conjunction with Dragon.
       */
    protected void showInitializeError()
        {
        JOptionPane.showMessageDialog(this,INIT_ERR_MSG);
	}

      /**
       * Public method, called by the TocTreePanel, which
       * sets the topic content in the Description pane.
       * @param url Url for the topic, relative to document base
       * @param id  Identifier for the topic.
       */
    public void setTopic(String url, String id, String title)
        {
	//System.out.println("SetTopic id=" + id + " url=" + url);
	enableButtons(null);
	setWaitCursor();
	descripLabel.setText(title);
        descriptionArea.setPage(url,id);
	descriptionArea.setCaretPosition(0);
        boolean bDetails = (descriptionArea.getDetailUrl() != null);
	tabbedPane.setEnabledAt(detailIndex,bDetails);
	tabbedPane.setSelectedComponent(descripPanel);
	contentsArea.selectTreeNode(currentTocNode);
	enableButtons(currentTocNode);
	setNormalCursor();
	}

      /**
       * Alternate method signature, used to implement
       * the SHOW command. Passes only an id; we look up
       * the URL.
       * @param id  Identifier for the topic.
       */
    public void setTopic(String id)
        {
        TocTreeNode node = TocTreeNode.findNodeById(id);
	if (node != null)
	    {
	    currentTocNode = node;
	    originalTopicId = id;
            setTopic(node.getNodeUrl(),id,node.toString());
	    }
	else
            setTopic("xxx#badnode",id,"");
	}

      /**
       * Set the topic content in the Details pane.
       * @param url Url for the topic, relative to document base
       * @param id  Identifier for the topic.
       */
    protected void setDetails(String url, String id)
        {
	setWaitCursor();
        detailsArea.setPage(url,id);
	detailsArea.setCaretPosition(0);
	tabbedPane.setSelectedComponent(detailsPanel);
	enableButtons(null);
	setNormalCursor();
	}


      /**
       * ActionListener method
       */
    public void actionPerformed(ActionEvent e)
        {
        TocTreeNode newNode = null;
        Object source = e.getSource();
	String id = descriptionArea.getCurrentId();
	TocTreeNode currentNode = TocTreeNode.findNodeById(id);
	if (source.equals(nextBtn))
	    {
	    if (currentNode != null)
	        {
		newNode = TocTreeNode.getNextTocNode(currentNode);
		while (descriptionArea.onCurrentPage(newNode.getNodeUrl()))
		    {
		    newNode = TocTreeNode.getNextTocNode(newNode);
		    }
		}  
	    }
	else if (source.equals(prevBtn))
	    {
	    if (currentNode != null)
	        {
		newNode = TocTreeNode.getPreviousTocNode(currentNode);
		while (descriptionArea.onCurrentPage(newNode.getNodeUrl()))
		    {
		    newNode = TocTreeNode.getPreviousTocNode(newNode);
		    }
		}  
	    }
	else if (source.equals(originalBtn))
	    {
            if (originalTopicId != null)
	        {
		newNode = TocTreeNode.findNodeById(originalTopicId);
		}
	    }
        if (newNode != null)
	    {
	    currentTocNode = newNode;
	    setTopic(newNode.getNodeUrl(),newNode.getNodeId(),
		     newNode.toString());
	    }
	}

      /**
       * Factorization. Enable or disable next and previous depending
       * on whether they exist. Public so that it can be called in
       * response to a selection event (from TocTreePanel) 
       * as well as a button press.
       * @param theNode  Tree node currently displayed, if any.
       */
    public void enableButtons(TocTreeNode theNode)
        {
        if (theNode == null)
	    {
            nextBtn.setEnabled(false);
            prevBtn.setEnabled(false);
            originalBtn.setEnabled(false);
	    return;
	    }
        boolean bFlag = (TocTreeNode.getNextTocNode(theNode) != null);
	nextBtn.setEnabled(bFlag);
	bFlag = (TocTreeNode.getPreviousTocNode(theNode) != null);
	prevBtn.setEnabled(bFlag);
        if (originalTopicId == null)
            bFlag = false;
	else 
	    bFlag = (!theNode.getNodeId().equals(originalTopicId));
	originalBtn.setEnabled(bFlag);
	}

      /**
       * ChangeListener method
       */
    public void stateChanged(ChangeEvent e)
        {
        Object source = e.getSource();
	if (!source.equals(tabbedPane))
	    return;
	int idx = tabbedPane.getSelectedIndex();
	if (idx == detailIndex)
	    {
	    String detailUrl = descriptionArea.getDetailUrl();
	    setDetails(detailUrl,"");
	    }
	else
	    {
            String id = descriptionArea.getCurrentId();
	    TocTreeNode node = TocTreeNode.findNodeById(id);
	    currentTocNode = node;
	    enableButtons(node);
	    }
	}

      /**
       * Method turns on wait cursor.
       */
    protected void setWaitCursor()
        {
	this.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
	}

      /**
       * method turns off wait cursor.
       */
    protected void setNormalCursor()
        {
	this.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	}

    public boolean isInitialized()
        {
	return bInitialized;
	}

      /**
       * Main method, creates and displays standalone application
       */
    public static void main(String[] args)
        {
        String MANREADER_TITLE = com.grs.dragon.ui.AboutDialog.uiTitle + " User Manual";
	String baseDir = null;
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
   	    {
	    System.out.println("Error setting look and feel");
	    }
	if (args.length >= 1)
	    {
	    if (args[0].compareTo("-?") == 0)
	        {
		System.out.println("Usage:");
		System.out.println("ManReader [<docBase>] [-H]");
		System.exit(0);
		}
	    }

	ConfigFileProcessor cfgProcessor = new ConfigFileProcessor(".");
	if (cfgProcessor.isInitialized())
	    ApplicationManager.setTempPath(cfgProcessor.getKpath());
	else
	    ApplicationManager.setTempPath(".");

	if (args.length >= 1)
	    baseDir = args[0];
	if (args.length >= 2)
	    if (args[1].equalsIgnoreCase("-H"))
	        bInitHidden = true;

        JFrame app = new JFrame(MANREADER_TITLE);
	app.setIconImage(new ImageIcon("mricon.gif").getImage());
        if (!bInitHidden)
	   {
	   app.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
	   SimpleWindowMonitor windowCloseMonitor = new SimpleWindowMonitor(
						    app,
						   "Exit Manual Reader?");
	   app.addWindowListener(windowCloseMonitor);
	   RemoveWindowCallback callback = new RemoveWindowCallback();
	   windowCloseMonitor.setCleanupCallback(callback);
	   }
	ManReader mr = new ManReader();
	mr.init(baseDir, bInitHidden);
        if (mr.isInitialized())
	   {
	   mr.setSize(620,700);
	   app.getContentPane().add(mr,BorderLayout.CENTER);
	   app.pack();
	   Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
	   app.setLocation((screenSize.width - 650), 0);
	   if (!bInitHidden)
	       {
	       app.setVisible(true);
	       //Win32WindowRecorder.recordWindowByTitle(MANREADER_TITLE,"MR");
	       }
	   MRIncomingCommandProcessor cmdProcessor = 
	     new MRIncomingCommandProcessor(mr,app);
	   mr.start();
           }
	else
	   {
	   System.exit(0);
	   }
	}
    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ManReader.java,v 1.26 2007/05/31 03:26:53 rudahl Exp $ \n";
	}

    }


