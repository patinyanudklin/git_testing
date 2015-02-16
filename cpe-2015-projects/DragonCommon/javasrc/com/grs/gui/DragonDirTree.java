/**
 * DragonDirTree
 *
 * Copyright  2001-2007 by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 3/23/2001
 *
 *  $Id: DragonDirTree.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: DragonDirTree.java,v $
 *  Revision 1.9  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.8  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.7  2002/09/27 15:45:09  goldin
 *  Change DriveTester to use JNI
 *
 *  Revision 1.6  2002/09/15 16:45:40  goldin
 *  Don't clear filter when you switch to a new directory
 *
 *  Revision 1.5  2002/09/12 17:21:28  goldin
 *  Work on filter behavior and setting of OK on off focus
 *
 *  Revision 1.4  2002/08/31 00:03:23  goldin
 *  continue major redesign of FileChooser
 *
 *  Revision 1.3  2002/08/28 16:33:05  goldin
 *  Work on merging MRU lists
 *
 *  Revision 1.2  2002/08/27 20:04:12  goldin
 *  convert filechooser to potentially using multiple file types
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.20  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.19  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.18  2001/10/17 10:29:36  goldin
 *  Modify to use ApplicationManager to get error display, etc.
 *
 *  Revision 1.17  2001/08/20 10:12:33  goldin
 *  Fix bug in explicit path specification
 *
 *  Revision 1.16  2001/06/25 15:01:50  goldin
 *  Fix JRE1.3 problem with setting default path in tree
 *
 *  Revision 1.15  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.14  2001/06/05 19:36:21  goldin
 *  Add Tracer; investigate file dialog bug
 *
 *  Revision 1.13  2001/05/31 17:10:53  goldin
 *  Work on problems with file dlg; esp. handling of empty drives
 *
 *  Revision 1.12  2001/05/30 15:32:53  goldin
 *  Work on getting fn keys to work in file dialog, main window w/ no RP
 *
 *  Revision 1.11  2001/04/24 14:14:20  goldin
 *  Improve behavior and appearance of file and font choosers
 *
 *  Revision 1.10  2001/04/23 09:26:54  goldin
 *  Make sure project is up to date
 *
 *  Revision 1.9  2001/04/18 15:32:45  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.8  2001/04/06 18:04:13  goldin
 *  Implement REFRESH
 *
 *  Revision 1.7  2001/04/06 11:20:59  goldin
 *  Fix bugs related to tree root
 *
 *  Revision 1.6  2001/04/04 15:24:50  goldin
 *  Added partial filename filtering, validation, to file chooser
 *
 *  Revision 1.5  2001/04/04 12:16:55  goldin
 *  Checkpoint of filechooser work; partial name filtering implemented
 *
 *  Revision 1.4  2001/04/03 17:46:43  goldin
 *  Continued work on FileChooser; moved state information into new DFileChooserModel class
 *
 *  Revision 1.3  2001/03/26 18:07:12  goldin
 *  Make sure repository matches disk
 *
 *  Revision 1.1  2001/03/23 17:01:51  goldin
 *  Initial implementation of file chooser
 *
 */

package com.grs.gui;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.tree.*;
import javax.swing.event.*;
import javax.swing.filechooser.*;
import javax.swing.border.*;
import java.util.*;
import java.io.*;

/**
 * This class is a UI component that presents a tree-structured
 * directory display and allows the user to choose, or to type
 * a path. When a path is entered, the class calls the setCurrentPath
 * method on its parent DragonFileChooser.*/
public class DragonDirTree extends JPanel implements ActionListener,
                                                     TreeSelectionListener
    {

      /**
       * Combo box for entering new paths and/or selecting
       * from the MRU paths.
       */
    protected JComboBox pathCombo = null;

      /**
       * Directory tree.
       */
    protected JTree directoryTree = null;

      /**
       * Text source for internationalized strings*/
    protected I18NTextSource textSource = null;

      /**
       * Parent file chooser. */
    protected DragonFileChooser parent = null;

      /**
       * Used to screen out events that are initiated by the
       * program rather than the user.
       */
    protected boolean bInternalEvent = false;

      /**
       * Tree model associated with the path tree.*/
    protected DirTreeModel treeModel = null;

      //****************************************************
      /** 
       * Constructor creates the UI components of the 
       * DirTree.
       * @param parent  Parent file chooser
       * @param textSource reference to text source to use.
       */
    public DragonDirTree(DragonFileChooser parent,
                         DragonFileList fileList,
			 I18NTextSource textSource)
        {
	this.parent = parent;
	this.textSource = textSource;
        // set the leaf icon to be the same as the closed icon
	UIManager.put("Tree.leafIcon", UIManager.get("Tree.closedIcon"));
	setLayout(new BorderLayout(10,10));
	setBorder(BorderFactory.createMatteBorder(10,10,10,10,
						  getBackground())); 
	String titleString = textSource.getI18NText(
					   TextKeys.LOCATIONS,"Locations");
	JLabel titleLabel = new JLabel(titleString);
	add(titleLabel,BorderLayout.NORTH);
	bInternalEvent = true;
	pathCombo = new JComboBox();
	pathCombo.setEditable(true);
	pathCombo.addActionListener(this);
	pathCombo.addKeyListener(parent);
	add(pathCombo, BorderLayout.SOUTH);
        DirTreeNode rootNode = 
	     new DirTreeNode(new File(DirTreeNode.DUMMYFILE));
	rootNode.setTreeRoot(true);
	treeModel = new DirTreeModel(rootNode,parent);
	directoryTree = new JTree(treeModel);
        directoryTree.addKeyListener(parent);
        directoryTree.addTreeWillExpandListener(treeModel);
        directoryTree.addTreeExpansionListener(treeModel);
        directoryTree.addTreeSelectionListener(this);
        directoryTree.getSelectionModel().setSelectionMode(
                   TreeSelectionModel.SINGLE_TREE_SELECTION);
	add(new JScrollPane(directoryTree), BorderLayout.CENTER);
        this.setMinimumSize(new Dimension(200,400));
        this.setPreferredSize(new Dimension(200,400));
	bInternalEvent = false;
	}

      /**
       * Allow the FileChooser to clear & regenerate
       * the path MRUs
       * @param addedPaths  String array of common paths, such as DPATH
       */
    public void setupMostRecentPaths(String[] addedPaths)
        {
	bInternalEvent = true;
        int count = pathCombo.getItemCount();
	for (int i = 0; i < count ; i++)
             pathCombo.removeItemAt(0);
	FileReference[] mruList = DFileType.PATH.getUsedFiles();
	for (int i = 0; i < mruList.length; i++)
	     pathCombo.addItem(mruList[i].fileName);
        bInternalEvent = false;
        }

      /**
       * Refreshes the tree, in case removable media were 
       * changed or new files added. Delegates to the
       * tree model.
       */
    public void refresh()
        {
	treeModel.rebuildFirstLevel();
	}

    /**
     * Event Listener methods
     */
    public void actionPerformed(ActionEvent e)
        {
	if (bInternalEvent) 
            return;
        Object source = e.getSource();
	if (source != pathCombo)
	    return;
        String path = (String) pathCombo.getEditor().getItem();
	if ((path == null) || (path.length() == 0))
	    return;
	DirTreeNode pathNode = treeModel.findNode(path);
	if (pathNode == null)
	    {
            String rootPath = null;
            int pos = path.indexOf(":");
	    if (pos > 0)
	        {
		rootPath = path.substring(0,pos).toUpperCase() + ":\\";
                DirTreeNode rootNode = treeModel.findNode(rootPath);
                if (rootNode == null)
                    {
                    ApplicationManager.getErrorLogger().logError(
                     "?? In DragonDirTree - can't find root for " +
                                         rootPath, true);
                    }
                else
                    {
                    /* try expanding that branch of the tree and 
                     * looking again 
                     */
                    treeModel.expandNode(rootNode, path);
	            pathNode = treeModel.findNode(path);
                    }
                }
            }
	if (pathNode == null)  /* if still null, try creating it */
            {
            String newpath = path;
            int pos = path.indexOf(":");
	    if (pos > 0)
	        {
		newpath = path.substring(0,pos).toUpperCase() +
                          path.substring(pos);
		}
            pathNode = makeDirectories(newpath);
	    treeModel.reload();
	    }
	// DON'T CLEAR THE FILTER parent.getModel().setPartialName(null);
        String msg = null;
        if (pathNode != null)
	    {
            parent.getModel().setCurrentPath(
                 pathNode.getNodeFile().getAbsolutePath());
    	    msg = "{ DragonDirTree: calling setCurrentPath to " +
	         pathNode.getNodeFile().getAbsolutePath() + " }";
            }
        else
	    { 
            msg = "{ DragonDirTree: Pathnode for " + path + " is null }";
	    } 
	Tracer.outputTraceMessage(msg,ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
	}

      /**
       * Helper method. Called when a non-existent directory
       * is entered by the user. Recursively creates and adds
       * parents at each level. Returns the tree node for the
       * leaf directory specified by the user.
       */
    protected DirTreeNode makeDirectories(String pathSpec)
        {
        DirTreeNode pathNode = null; 
	DirTreeNode parentPath = treeModel.findParent(pathSpec);
	if (parentPath == null)
	    {
            parentPath = makeDirectories(new File(pathSpec).getParent());
	    }
	File newDir = new File(pathSpec);
	boolean bOk = newDir.mkdir();
	if (bOk)
	    {
	    pathNode = new DirTreeNode(newDir);
	    parentPath.add(pathNode);
	    }
        return pathNode;
	} 
       

      /**
       * TreeSelectionListener
       */
    public void valueChanged(TreeSelectionEvent e)
        {
        if (bInternalEvent)
	    return;
        TreePath paths[] = e.getPaths();
	DirTreeNode node = null;
        for (int i = 0; i < paths.length; i++)
	    {
            node = (DirTreeNode) paths[i].getLastPathComponent();
            if (node.isTreeRoot())
	        continue;
	    String newPathName = node.getNodeFile().getAbsolutePath();
	    if (e.isAddedPath(paths[i]))
	        {
		// DON'T CLEAR THE FILTER parent.getModel().setPartialName(null);
		parent.getModel().setCurrentPath(newPathName);
		}
	    }
	}

      /**
       * Called by the model to update the view in order to
       * be consistent with the current model state.
       * May be called several times in succession, to deselect
       * old stuff and select new stuff.
       * @param currentPath Current path as it should be reflected in
       *                    the controls.
       * @param oldPath     Previously selected path, now deselected.
       *  Either of these can be null.
       */
    public void updateView(String currentPath, String oldPath)
        {
        bInternalEvent = true;
        treeModel.setInternalEvent(bInternalEvent);
        if (oldPath != null)
	    {
	    pathCombo.removeItem(oldPath);
            parent.getModel().clearFileList();	    
	    }
        if (currentPath != null)
	    {
            int idx = findInCombo(currentPath);
            if (idx < 0)
	        {
                pathCombo.insertItemAt(currentPath,0);
                pathCombo.setSelectedIndex(0);
	        }
            else
	        {
                pathCombo.setSelectedIndex(idx);
		}
	    // expand tree if necessary, so that path exists.
	    treeModel.instantiateTreePath(currentPath);
            DirTreeNode pathNode = treeModel.findNode(currentPath);

            if (pathNode != null)
	        {
		TreePath tPath = 
	           new TreePath(treeModel.getPathToRoot(pathNode));
	        directoryTree.setSelectionPath(tPath);
                parent.getModel().setFileList(pathNode,false);
		}
	    else
	        {
		ErrorDisplay errDisplay = ApplicationManager.getErrorDisplay();
                errDisplay.showError(TextKeys.ERROR, TextKeys.NOTFOUND_ERR,
				     currentPath);
		}
	    }
	else
	    {
	    pathCombo.setSelectedIndex(-1); 
	    TreePath path = directoryTree.getLeadSelectionPath();
	    if (path != null)
	         directoryTree.removeSelectionPath(path);
	    }
	bInternalEvent = false;
        treeModel.setInternalEvent(bInternalEvent);
	}


      /**
       * Helper method, looks through the current list of stuff
       * in the combo box to see if file is already there.
       */
    protected int findInCombo(String pathname)
        {
        int found = -1;
	int len = pathCombo.getItemCount();
	for (int i = 0; i < len; i++)
	    {
	    String test = (String) pathCombo.getItemAt(i);
	    if (test.equals(pathname))
	        {
		found = i;
		break;
		}
	    }
	return found;
	}

    public DirTreeModel getTreeModel()
        {
	return treeModel;
	}

    protected void readAndParseFile()
        {
        // Write your code here
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonDirTree.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
