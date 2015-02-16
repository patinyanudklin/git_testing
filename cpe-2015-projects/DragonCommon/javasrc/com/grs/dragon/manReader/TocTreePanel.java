/**
 *  TocTreePanel
 *
 *  Copyright 2001 by Goldin-Rudahl Associates
 *  
 *  Created 11/21/2001 by Sally Goldin
 *
 *  $Id: TocTreePanel.java,v 1.13 2007/05/31 03:26:53 rudahl Exp $
 *  $Log: TocTreePanel.java,v $
 *  Revision 1.13  2007/05/31 03:26:53  rudahl
 *  add 'whatis' boilerplate
 *
 *  Revision 1.12  2006/04/20 08:11:28  goldin
 *  Make mouseclick on already selected item go back to that item
 *
 *  Revision 1.11  2006/03/05 04:44:21  goldin
 *  Close toc file after reading
 *
 *  Revision 1.10  2002/07/19 23:02:50  goldin
 *  Improve error handling when toc cannot be found
 *
 *  Revision 1.9  2002/07/19 22:10:24  goldin
 *  Fix bug in argument handling
 *
 *  Revision 1.8  2002/07/19 19:51:17  goldin
 *  Give an error msg and exit if can't find TOC
 *
 *  Revision 1.7  2001/11/29 15:16:15  goldin
 *  modify signature of setTopic
 *
 *  Revision 1.6  2001/11/29 11:15:03  goldin
 *  Add custom icons to tree
 *
 *  Revision 1.5  2001/11/28 15:32:11  goldin
 *  check for null in selecting a node
 *
 *  Revision 1.4  2001/11/28 13:11:31  goldin
 *  Implement next/previous
 *
 *  Revision 1.3  2001/11/27 17:38:01  goldin
 *  Add capability to set details
 *
 *  Revision 1.2  2001/11/26 14:00:09  goldin
 *  Continue basic implementation of ManReader
 *
 *  Revision 1.1  2001/11/21 16:05:50  goldin
 *  begin implementing
 *
 *
 */

package com.grs.dragon.manReader;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.util.*;
import java.io.*;
/**
 * This class implements a simple Table of Contents tree panel which
 * can be used by the ManReader or possibly other applications.
 * The class invokes the necessary functionality for reading and
 * parsing the Toc XML file by creating a TocParser object.
 */
public class TocTreePanel extends JPanel 
                  implements TreeSelectionListener, MouseListener
    {
      /**
       * Tree of TOC topic nodes.
       */
    protected JTree topicTree = null;

      /**
       * root of the tree.
       */
    protected TocTreeNode rootNode = null;

    protected JLabel titleLabel = null;
    protected TocTreeModel treeModel = null;

      /* keep track of last selected node */
    protected TocTreeNode lastSelectedNode = null;

      /**
       * Parent ManReader
       */
    protected ManReader manReader = null;

      //****************************************************
      /** 
       * Constructor creates the UI components of the 
       * TocTree.
       */
    public TocTreePanel(ManReader parent)
        {
	manReader= parent;
        // set the leaf icon to be the same as the closed icon
	//UIManager.put("Tree.leafIcon", UIManager.get("Tree.closedIcon"));
	setLayout(new BorderLayout(10,10));
	setBorder(BorderFactory.createMatteBorder(10,10,10,10,
						  getBackground())); 
	String titleString = "Table of Contents";
	titleLabel = new JLabel(titleString);
	add(titleLabel,BorderLayout.NORTH);
        rootNode = 
	     new TocTreeNode("Root",null,null,null,0,1);
        treeModel = new TocTreeModel(rootNode,this);
	UIManager.put("Tree.closedIcon", new ImageIcon("closbook.gif"));
	UIManager.put("Tree.openIcon", new ImageIcon("openbook.gif"));
	UIManager.put("Tree.leafIcon", new ImageIcon("openbook.gif"));
	topicTree = new JTree(treeModel);
        topicTree.addMouseListener(this);
        topicTree.addTreeSelectionListener(this);
        topicTree.getSelectionModel().setSelectionMode(
                   TreeSelectionModel.SINGLE_TREE_SELECTION);
	add(new JScrollPane(topicTree), BorderLayout.CENTER);
        this.setMinimumSize(new Dimension(500,300));
        this.setPreferredSize(new Dimension(500,300));
	}

      /**
       * Build the contents tree based on the XML file.
       *
       * @param xmlFile  Name of XML file hold topics
       * @return true if ok, false if error (e.g. XML file is bad 
       *                      or does not exist)
       */
    public boolean initialize(String xmlFile)
        {
        boolean bOk = true;
	//System.out.println("ManReader trying to read toc file: " + xmlFile);
        try
	     {
	     BufferedReader fReader = new BufferedReader(
					   new FileReader(xmlFile));
             StringBuffer buffer = new StringBuffer(4096);
	     String input = null;
             while ((input = fReader.readLine()) !=  null)
                   buffer.append(input + "\n");
	     fReader.close();
             XmlToTocBuilder parser = new XmlToTocBuilder(
                           buffer.toString(),
			   rootNode);
	     //parser.setTracing(true);
             Reader xmlReader = parser.getXmlReader();
             parser.parse(xmlReader);
	     }
	catch (Exception e)
	     {
	     bOk = false;
	     }
        treeModel.reload();
	return bOk;
	}

      /**
       * TreeSelectionListener Method
       */
    public void valueChanged(TreeSelectionEvent e)
        {
        TreePath paths[] = e.getPaths();
	TocTreeNode node = null;
        for (int i = 0; i < paths.length; i++)
	    {

            node = (TocTreeNode) paths[i].getLastPathComponent();
	    String nodeUrl = node.getNodeUrl();
	    if ((nodeUrl == null) || (nodeUrl.length() == 0))
	        continue;
	    if (e.isAddedPath(paths[i]))
	        {
		lastSelectedNode = node;
		manReader.setTopic(nodeUrl,node.getNodeId(),
				   node.toString());
		manReader.enableButtons(node);
		}
	    }
	}

      /**
       * Select a particular item in the tree. Used for next/previous/original.
       * @param theNode  Node to select.
       */
    public void selectTreeNode(TocTreeNode theNode)
        {
        if (theNode == null)
	    return;
	TreePath tPath = 
	           new TreePath(treeModel.getPathToRoot(theNode));
	topicTree.setSelectionPath(tPath);
	}

      /* Mouse listener methods */

    public void mouseClicked(MouseEvent me)
        {
        TreePath selPath = topicTree.getPathForLocation(me.getX(),me.getY());
        if (selPath == null)
            return;  
        TocTreeNode selNode = (TocTreeNode) selPath.getLastPathComponent();
        if ((lastSelectedNode != null) && (selNode != null) &&
            (lastSelectedNode == selNode))
            {
	    String nodeUrl = lastSelectedNode.getNodeUrl();
	    if ((nodeUrl != null) || (nodeUrl.length() != 0))
	        {
		manReader.setTopic(nodeUrl,lastSelectedNode.getNodeId(),
				   lastSelectedNode.toString());
		manReader.enableButtons(lastSelectedNode);
		}
	    }
        }

    public void mouseEntered(MouseEvent me)
        {
        }

    public void mouseExited(MouseEvent me)
        {
        }

    public void mousePressed(MouseEvent me)
        {
        }

    public void mouseReleased(MouseEvent me)
        {
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: TocTreePanel.java,v 1.13 2007/05/31 03:26:53 rudahl Exp $ \n";
	}
    }
