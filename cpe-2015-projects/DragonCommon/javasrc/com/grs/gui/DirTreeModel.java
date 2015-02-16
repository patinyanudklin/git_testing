/**
 * DirTreeModel
 * 
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 3/26/2001
 * 
 *  $Id: DirTreeModel.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: DirTreeModel.java,v $
 *  Revision 1.9  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.8  2006/07/23 09:12:22  goldin
 *  Attempt to switch to using Java 1.5 (Axel/Windows only)
 *
 *  Revision 1.7  2006/02/19 09:23:12  goldin
 *  Fix bug in initial tree expansion for multi-level DPaths
 *
 *  Revision 1.6  2006/01/15 13:04:29  goldin
 *  Fix problem with multiple directories that start the same
 *
 *  Revision 1.5  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.4  2004/09/26 12:38:20  goldin
 *  Fix FileChooser bugs
 *
 *  Revision 1.3  2002/08/22 14:56:52  goldin
 *  Work on appearance and behavior of VP Filechooser
 *
 *  Revision 1.2  2002/05/03 18:11:09  goldin
 *  Test for children - treating the symptom not the bug
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.14  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.13  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.12  2001/10/17 10:29:36  goldin
 *  Modify to use ApplicationManager to get error display, etc.
 *
 *  Revision 1.11  2001/08/20 10:12:33  goldin
 *  Fix bug in explicit path specification
 *
 *  Revision 1.10  2001/06/25 15:01:50  goldin
 *  Fix JRE1.3 problem with setting default path in tree
 *
 *  Revision 1.9  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.8  2001/06/05 19:36:21  goldin
 *  Add Tracer; investigate file dialog bug
 *
 *  Revision 1.7  2001/05/31 17:10:53  goldin
 *  Work on problems with file dlg; esp. handling of empty drives
 *
 *  Revision 1.6  2001/04/18 15:32:45  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.5  2001/04/06 18:04:13  goldin
 *  Implement REFRESH
 *
 *  Revision 1.4  2001/04/06 11:20:59  goldin
 *  Fix bugs related to tree root
 *
 *  Revision 1.3  2001/04/04 12:16:55  goldin
 *  Checkpoint of filechooser work; partial name filtering implemented
 *
 *  Revision 1.2  2001/04/03 17:46:43  goldin
 *  Continued work on FileChooser; moved state information into new DFileChooserModel class
 *
 *  Revision 1.1  2001/03/26 18:05:43  goldin
 *  Add new tree-related classes
 *
 */

package com.grs.gui;
import javax.swing.tree.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.filechooser.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/**
 *  This class represents a tree model for a directory
 *  system. It has the ability to rebuild/refresh itself.
 *  Each node, except the root, is DirTreeNode.*/
public class DirTreeModel extends DefaultTreeModel
                          implements TreeWillExpandListener,
                                     TreeExpansionListener
    {
      /**
       * Reference to filechooser dialog, used for setting the cursor.
       */
    protected DragonFileChooser parentWindow = null;

      /**
       * Flag to prevent nested calls to setCurrentPath.
       */
    protected boolean bInternalEvent = false;

      /**
       * Constructor. Sets up the root node and file system roots
       * with dummy children. Other children are added when
       * the user does the first expansion.
       * Other nodes are added in the buildModel method.
       * @param root Root node of the tree model. It is not a directory
       *             but represents the "world", a place where we can later
       *             add URLs
       * @param parentWindow Reference to parent dialog, for setting
       *              the wait cursor.
       */
    public DirTreeModel(DirTreeNode root,
		        DragonFileChooser parentWindow)
        {
	super(root);
	this.parentWindow = parentWindow;
        rebuildFirstLevel();
        // DefaultTreeModel has protected member root.
	}

      /**
       * Populates, or repopulates, the first level of directory tree model.
       */
    public void rebuildFirstLevel()
        {
        DefaultMutableTreeNode myRoot = (DefaultMutableTreeNode) root;
        myRoot.removeAllChildren();
        //FileSystemView view = FileSystemView.getFileSystemView();
        //File[] fsRoots = view.getRoots();
        File[] fsRoots = File.listRoots();
	for (int i = 0; i < fsRoots.length; i++)
	    {
            DirTreeNode childNode = new DirTreeNode(fsRoots[i]);
            childNode.setFileSystemRoot(true);
            myRoot.add(childNode);
            // add a dummy node to each root.
            DirTreeNode dummyNode = 
                new DirTreeNode(new File(DirTreeNode.DUMMYFILE));
            dummyNode.setDummy(true);
            childNode.add(dummyNode);
            }
        reload();
	}

      /**
       * Recursive routine to find all the current subdirectories,
       * of all directories, and add them to the tree.
       * @param parentNode  Node whose children we are seeking
       *                    in this iteration.
       * @return number of children added (so we can detect the bottom
       *          of the subdirectory tree.
       */
   protected int populateSubDirs(DirTreeNode parentNode)
        {
        int count = 0;
        File[] children = parentNode.getSubDirectories();
        if (children == null)
            return count;
        count = children.length;
        for (int i = 0; i < count; i++)
	    {
            DirTreeNode node = new DirTreeNode(children[i]);
	    parentNode.add(node);
            File[] grandchildren = node.getSubDirectories();
	    if ((grandchildren != null) && (grandchildren.length > 0))
	        {
                DirTreeNode dummyNode = 
                      new DirTreeNode(new File(DirTreeNode.DUMMYFILE));
                dummyNode.setDummy(true);
                node.add(dummyNode);
		}
            }
	return count;
        }

      /**
       * Method from TreeWillExpandListener interface.
       * Populates subtree if the immediate child is a dummy node.
       */
   public void treeWillExpand(TreeExpansionEvent ev)
        throws ExpandVetoException
       {
       DirTreeNode node = (DirTreeNode) ev.getPath().getLastPathComponent();
       if (node.isFileSystemRoot())
	   {
           boolean bOk = true;
	       DriveTester.isDriveOk(node.getNodeFile().getAbsolutePath());
           if (!bOk)
	       {
	       DirTreeNode dummy = (DirTreeNode) node.getChildAt(0);
	       node.remove(dummy);
               ApplicationManager.getMessageDisplay().showWarning(
                     TextKeys.WARNING, TextKeys.NODISKINDRIVE,
		     node.getNodeFile().getAbsolutePath());
               return;
	       }
	   }
       // get the first child of the node
       DirTreeNode child = (DirTreeNode) node.getChildAt(0);
       if (child.isDummy())
	   {
           node.remove(child);
	   setWaitCursor(parentWindow);
	   populateSubDirs(node);
	   setNormalCursor(parentWindow);
           }
       // reload();  // makes other folders close when this one opens.
       }

      /** 
       * Also from TreeWillExpandListener interface.
       * Prohibits attempt to collapse a root.
       */
   public void treeWillCollapse(TreeExpansionEvent ev)
          throws ExpandVetoException
       {
       DirTreeNode node = (DirTreeNode) ev.getPath().getLastPathComponent();
       if (node.isTreeRoot())   // don't allow them to collapse the root!
	   {
	   throw new ExpandVetoException(ev);
	   }
       }
      /**
       * Method from TreeExpansionListener interface.
       * Populates file list for expanded node
       */
   public void treeExpanded(TreeExpansionEvent ev)
       {
       if (bInternalEvent)
           return;
       DirTreeNode node = (DirTreeNode) ev.getPath().getLastPathComponent();
       DFileChooserModel chooserModel = parentWindow.getModel();
       String path = node.getNodeFile().getAbsolutePath();
       String msg = "{ DirTreeModel: calling setCurrentPath to " +
	                    path + " }";
       Tracer.outputTraceMessage(msg,
				 ApplicationManager.getModulePrefix(),
				 ApplicationManager.getTimeOffset());
       chooserModel.setCurrentPath(path);
       }

      /** 
       * Also from TreeExpansionListener interface.
       * Does not do anything at the moment
       */
   public void treeCollapsed(TreeExpansionEvent ev)
       {
       }
  
      /**
       * Given a string, which is assumed to represent a file,
       * try and find a node in the tree that matches that file.
       * @param filename  Name of file we are looking for.
       * @return DirTreeNode corresponding to file, or null if not in tree
       */
   public DirTreeNode findNode(String filename)
       {
       DirTreeNode foundNode = null;
       DefaultMutableTreeNode myRoot = (DefaultMutableTreeNode) root;
       Enumeration myEnum = myRoot.depthFirstEnumeration();
       while (myEnum.hasMoreElements())
	   {
           TreeNode node = (TreeNode) myEnum.nextElement();
           if (node instanceof DirTreeNode)
	       {
               DirTreeNode dirNode = (DirTreeNode) node;
	       if (dirNode.getNodeFile().getAbsolutePath().equalsIgnoreCase(filename))
	           {
	           foundNode = dirNode;
	           break;
	           }
	       }
	   }
       return foundNode;
       }

      /**
       * Given a string, which represents a directory, make sure that
       * the path to that directory has been instantiated in the
       * tree model.
       */
   public void instantiateTreePath(String dirName)
       {
       String root = null;
       int pos = dirName.indexOf(File.separator);
       if (pos < 0)
	   return;  // what can we do? this is not an absolute path
       root = dirName.substring(0,pos+1);
       DirTreeNode rootNode = findNode(root);
       if (rootNode == null)
  	   return;  // again, we can't really do anything if the root is not
                    // in the tree
       expandNode(rootNode,dirName);
       }

      /**
       * Recursive method, expands down the tree until we have
       * gotten to the directory represented by dirName.
       * @param parentNode  Current node being expanded
       * @param dirName     Name of directory that we want to expand to.
       */
   public void expandNode(DirTreeNode parentNode, String dirName)
       {
       if (parentNode.getNodeFile().getAbsolutePath().equalsIgnoreCase(dirName))
	   return;    // we are done
       DirTreeNode child = null;
       int count = parentNode.getChildCount();
       if (count > 0)
           child = (DirTreeNode) parentNode.getChildAt(0);
       // 5/3/02 added this check to avoid out of bounds error.
       // however, I don't understand why there should ever be no children
       if ((child == null) || (child.isDummy()))
	   {
	   if (child != null)
	       parentNode.remove(child);
	   populateSubDirs(parentNode);
	   }
       // now find the next node to descend to
       count = parentNode.getChildCount();
       DirTreeNode nextNode = null;
       String compareDir = dirName.toUpperCase();
       int pos = compareDir.lastIndexOf(File.separator);
       /* Peel away lower level directories until we
        * get a match.
        */
       while ((pos > 0) && (nextNode == null))
	  {      
          compareDir = compareDir.substring(0,pos);
          for (int i = 0; i < count; i++)
	     {
	     DirTreeNode tempNode = (DirTreeNode) parentNode.getChildAt(i);
	     String path = tempNode.getNodeFile().getAbsolutePath().toUpperCase();
	     if ((dirName.equalsIgnoreCase(path)) ||
                 (compareDir.equalsIgnoreCase(path)))
	         {
	         nextNode = tempNode;
	         break;
	         }
  	     }
	  pos = compareDir.lastIndexOf(File.separator);
          }
       if (nextNode != null)
	   expandNode(nextNode,dirName);
       }

      /**
       * Given a string, which is assumed to represent a file,
       * try and find a node in the tree that represents the parent
       * directory for that file.
       * @param filename  Name of file we are looking for.
       * @return DirTreeNode corresponding to file, or null if not in tree
       */
   public DirTreeNode findParent(String filename)
       {
       DirTreeNode foundNode = null;
       File testFile = new File(filename);
       File parentFile = testFile.getParentFile();
       DefaultMutableTreeNode myRoot = (DefaultMutableTreeNode) root;
       Enumeration myEnum = myRoot.depthFirstEnumeration();
       while (myEnum.hasMoreElements())
	   {
           TreeNode node = (TreeNode) myEnum.nextElement();
           if (node instanceof DirTreeNode)
	       {
               DirTreeNode dirNode = (DirTreeNode) node;
	       if (dirNode.getNodeFile().equals(parentFile))
	           {
		   foundNode = dirNode;
		   break;
		   }
	       }
	   }
       return foundNode;
       }


      /**
       * Static method turns on wait cursor.
       */
    protected void setWaitCursor(Component window)
        {
	window.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
	}

      /**
       * Static method turns on wait cursor.
       */
    protected void setNormalCursor(Component window)
        {
	window.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	}

      /**
       * Set value for internal event flag
       */
   public void setInternalEvent(boolean bFlag)
       {
       bInternalEvent = bFlag;
       }
   }

