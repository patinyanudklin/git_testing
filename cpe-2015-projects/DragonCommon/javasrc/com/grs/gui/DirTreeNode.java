/**
 * DirTreeNode 
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 3/26/2001
 *
 *   $Id: DirTreeNode.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $
 *   $Log: DirTreeNode.java,v $
 *   Revision 1.7  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.6  2005/02/06 08:08:11  goldin
 *   Fix JavaDoc warnings
 *
 *   Revision 1.5  2002/09/27 15:45:09  goldin
 *   Change DriveTester to use JNI
 *
 *   Revision 1.4  2002/08/31 00:03:23  goldin
 *   continue major redesign of FileChooser
 *
 *   Revision 1.3  2002/08/27 20:04:12  goldin
 *   convert filechooser to potentially using multiple file types
 *
 *   Revision 1.2  2002/08/22 14:56:52  goldin
 *   Work on appearance and behavior of VP Filechooser
 *
 *   Revision 1.1  2001/11/16 17:29:21  goldin
 *   Move DragonFileChooser and supporting classes to new general .gui package
 *
 *   Revision 1.5  2001/11/05 13:59:15  goldin
 *   Put UI code in a package
 *
 *   Revision 1.4  2001/04/24 14:14:20  goldin
 *   Improve behavior and appearance of file and font choosers
 *
 *   Revision 1.3  2001/04/18 15:32:45  goldin
 *   Added home directory command line argument
 *
 *   Revision 1.2  2001/04/06 11:20:59  goldin
 *   Fix bugs related to tree root
 *
 *   Revision 1.1  2001/03/26 18:05:43  goldin
 *   Add new tree-related classes
 *
 */

package com.grs.gui;
import javax.swing.tree.*;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;

/**
 * This class represents a node in the Dragon file chooser directory
 * tree. It is a relatively shallow subclass of DefaultMutableTree node
 * which adds a reference to DFileType.PATH for filtering, and
 * a method for returning files within a directory.*/
public class DirTreeNode extends DefaultMutableTreeNode
    {
    public final static String DUMMYFILE = "DummyFile";

      /**
       * Filter used to determine whether something is a directory.*/
    public static final DFileType DIRFILTER = DFileType.PATH;

      /**
       * If true, this node represents a filesystem root (i.e.
       * a drive, in Windows.
       */
    protected boolean bFileSystemRoot = false;

      /**
       * Indicates whether this is a dummy node.
       */
    protected boolean bDummy = false;

      /**
       * Indicates whether this is the root of the whole tree.
       */
    protected boolean bTreeRoot = false;

      /**
       * Constructor. Pass a File (directory) object; passes
       * this on to the superclass to be stored as the userObject.
       */
    public DirTreeNode(File nodeFile)
        {
        super(nodeFile);
	}


      /**
       * Returns the userObject, cast to a File.
       */
    public File getNodeFile()
        {
	return (File) getUserObject();
	}

      /**
       * Generate a list of the files in the directory
       * represented by the current node.
       * @param fileType Filetype to use for filtering
       * @return filenames as a string array.
       */
    public String[] getMatchingFiles(DFileType fileType)
        {
        File dirFile = getNodeFile();
        File[] matching = dirFile.listFiles(fileType);
        if (matching == null)
             return null;
        String[] matchingNames = new String[matching.length];
	for (int i = 0; i < matching.length; i++)
	     matchingNames[i] = matching[i].getName();
	return matchingNames;
	}

      /**
       * Generate an array of all the child subdirectories
       * for this directory.
       */
    public File[] getSubDirectories()
        {
        File dirFile = getNodeFile();
        File[] matching = dirFile.listFiles(DIRFILTER);
        return matching;
	}

    public String toString()
        {
	if (bTreeRoot)
	    return "";
	else
	    {
            String path = getNodeFile().getAbsolutePath();
	    int pos = path.lastIndexOf(File.separator);
	    if ((bFileSystemRoot) || (pos < 0))
	        return path;
	    else
	        {
		return path.substring(pos+1);
		}
            }
        }

    public boolean isDummy()
        {
        return bDummy;
	}

    public void setDummy(boolean flag)
        {
        bDummy = flag;
	}

    public boolean isTreeRoot()
        {
        return bTreeRoot;
	}

    public void setTreeRoot(boolean flag)
        {
        bTreeRoot = flag;
	}

    public boolean isFileSystemRoot()
        {
        return bFileSystemRoot;
	}

    public void setFileSystemRoot(boolean flag)
        {
        bFileSystemRoot = flag;
	}



    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DirTreeNode.java,v 1.7 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
