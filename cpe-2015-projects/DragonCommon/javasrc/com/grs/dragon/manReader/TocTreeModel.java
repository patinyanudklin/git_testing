/**
 * TocTreeModel
 * 
 * Copyright 2001 by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 11/26/2001
 * 
 *  $Id: TocTreeModel.java,v 1.5 2007/05/31 03:26:53 rudahl Exp $
 *  $Log: TocTreeModel.java,v $
 *  Revision 1.5  2007/05/31 03:26:53  rudahl
 *  add 'whatis' boilerplate
 *
 *  Revision 1.4  2006/04/20 08:11:28  goldin
 *  Make mouseclick on already selected item go back to that item
 *
 *  Revision 1.3  2001/11/27 17:38:19  goldin
 *  Add capability to set details
 *
 *  Revision 1.1  2001/11/26 14:00:09  goldin
 *  Continue basic implementation of ManReader
 *
 *
 */

package com.grs.dragon.manReader;
import javax.swing.tree.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.filechooser.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/**
 *  This class represents a tree model for a nested set of topics
 *  that represent a table of contents.
 *  Each node is a TocTreeNode.
*/
public class TocTreeModel extends DefaultTreeModel
                          implements TreeWillExpandListener,
                                     TreeExpansionListener
    {
      /**
       * Reference to panel where the tree is displayed, 
       * used for setting the cursor.
       */
    protected TocTreePanel parent = null;

      /**
       * Constructor. Sets up the root node
       * Other nodes are added in during the Xml Parsing.
       * @param root Root node of the tree model. It is not a directory
       *             but represents the "world", a place where we can later
       *             add URLs
       * @param parent Reference to parent dialog, for setting
       *              the wait cursor.
       */
    public TocTreeModel(TocTreeNode root,
		        TocTreePanel parent)
        {
	super(root);
	this.parent = parent;
	}


      /**
       * Method from TreeWillExpandListener interface.
       * Populates subtree if the immediate child is a dummy node.
       */
   public void treeWillExpand(TreeExpansionEvent ev)
        throws ExpandVetoException
       {
       TocTreeNode node = (TocTreeNode) ev.getPath().getLastPathComponent();
       }

      /** 
       * Also from TreeWillExpandListener interface.
       * Prohibits attempt to collapse a root.
       */
   public void treeWillCollapse(TreeExpansionEvent ev)
          throws ExpandVetoException
       {
       TocTreeNode node = (TocTreeNode) ev.getPath().getLastPathComponent();
       }

      /**
       * Method from TreeExpansionListener interface.
       * Populates file list for expanded node
       */
   public void treeExpanded(TreeExpansionEvent ev)
       {
       TocTreeNode node = (TocTreeNode) ev.getPath().getLastPathComponent();
       }

      /** 
       * Also from TreeExpansionListener interface.
       * Does not do anything at the moment
       */
   public void treeCollapsed(TreeExpansionEvent ev)
       {
       }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: TocTreeModel.java,v 1.5 2007/05/31 03:26:53 rudahl Exp $ \n";
	}


    }

