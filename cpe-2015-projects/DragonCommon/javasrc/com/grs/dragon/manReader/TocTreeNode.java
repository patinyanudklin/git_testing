/**
 * TocTreeNode
 *
 * ~~ Copyright 2001-2015 by Sally Goldin & Kurt Rudahl
 * ~~ EndC
 *
 * Created by Sally Goldin, 11/21/2001
 *
 * $Id: TocTreeNode.java,v 1.10.2.1 2015/01/01 10:32:30 rudahl Exp $
 * $Log: TocTreeNode.java,v $
 * Revision 1.10.2.1  2015/01/01 10:32:30  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.11  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.10  2007/05/31 03:26:53  rudahl
 * add 'whatis' boilerplate
 *
 * Revision 1.9  2005/02/06 08:39:04  goldin
 * Fix javadoc warnings
 *
 * Revision 1.8  2002/06/27 21:30:48  goldin
 * Miscellaneous refinements to behavior and appearance
 *
 * Revision 1.7  2001/11/29 15:14:08  goldin
 * Make next/prev node ignore level
 *
 * Revision 1.6  2001/11/28 15:31:22  goldin
 * Fix implementation of getPreviousTocNode
 *
 * Revision 1.5  2001/11/28 13:11:31  goldin
 * Implement next/previous
 *
 * Revision 1.4  2001/11/27 17:38:19  goldin
 * Add capability to set details
 *
 * Revision 1.2  2001/11/26 14:00:09  goldin
 * Continue basic implementation of ManReader
 *
 * Revision 1.1  2001/11/21 16:05:50  goldin
 * begin implementing
 *
 *
 */
package com.grs.dragon.manReader;
import javax.swing.*;
import javax.swing.tree.*;
import java.util.*;

/**
 * This class represents nodes in a topic tree.
 */
public class TocTreeNode extends DefaultMutableTreeNode
    {
      /**
       * Data associated with the tree node.
       */
    protected String nodeId = null;
    protected String nodeUrl = null;
    protected String nodeText = null;
    protected String nodePrefix = null;
    protected int nodeLevel = 0;
    protected int nodeSequence = 0;
      /**
       * Make it possible to find a node by its Id
       */
    protected static HashMap<String,TocTreeNode> nodeMap = 
               new HashMap<String,TocTreeNode>();
    protected static HashMap<String,String> urlMap  = 
               new HashMap<String,String>();
      /**
       * Keep a linked list of all TOC nodes in the order
       * they are created. This will allow us to
       * implement the Next and Previous Topic buttons.
       */
    protected static ArrayList<TocTreeNode> nodeList = 
           new ArrayList<TocTreeNode>();

      /**
       * Constructor initializes the data
       */
    public TocTreeNode(String id, 
		       String url, 
		       String text,
		       String prefix,
		       int level, 
		       int sequence)
        {
        nodeId = id;
	nodeUrl = url;
	nodeText = text;
	nodePrefix = prefix;
	nodeMap.put(id,this);
	if (url != null)
  	     urlMap.put(url,id);   
	nodeLevel = level;
	nodeSequence = sequence;
        nodeList.add(this);
	}


      /**
       * Override toString to determine what we will see
       * in the tree.
       */
    public String toString()
        {
	StringBuffer buffer = new StringBuffer(256);
        if (!isRoot())
	    {
	    if (nodePrefix != null)
	        buffer.append(nodePrefix + " ");
	    buffer.append(getLevelString() + " ");
	    }
	if (nodeText != null)
	    buffer.append(nodeText);
	return buffer.toString();
	}

      /**
       * This method recursively constructs a string of the form
       * "x.y.z" (for instance "1.3.2") based on the sequence numbers of
       * parent nodes.
       */
    protected String getLevelString()
        {
        TocTreeNode parent = (TocTreeNode) getParent();
	if ((parent == null) || (parent.isRoot())) 
            return String.valueOf(nodeSequence);
	else 
            return parent.getLevelString() + "." +
	           String.valueOf(nodeSequence);
	}

      /**
       * access methods
       */
    public void setNodeText(String text)
        {
	nodeText = text;
	}

    public String getNodeUrl()
        {
	return nodeUrl;
	}

    public String getNodeId()
        {
	return nodeId;
	}

    public String getNodeText()
        {
	return nodeText;
	}

    public int getNodeLevel()
        {
	return nodeLevel;
	}

    public int getNodeSequence()
        {
	return nodeSequence;
	}

    public static TocTreeNode findNodeById(String nodeId)
        {
	return (TocTreeNode) nodeMap.get(nodeId);
	}

    public static TocTreeNode findNodeByUrl(String nodeUrl)
        {
        String id = (String) urlMap.get(nodeUrl);
	return findNodeById(id);
	}
    
      /**
       * Given a TOC node, return the next TOC node
       * or null if none.
       * @param focusNode Node relative to which we want the next node.
       * @return next node in list or null
       */
    public static TocTreeNode getNextTocNode(TocTreeNode focusNode)
        {
        int index = nodeList.indexOf(focusNode);
        TocTreeNode foundNode = null;
        if (nodeList.size() > index+1)
            foundNode = (TocTreeNode) nodeList.get(index + 1);
	return foundNode;
	}

      /**
       * Given a TOC node, return the previous TOC node
       * or null if none.
       * @param focusNode Node relative to which we want the previous node.
       * @return previous node in list or null
       */
    public static TocTreeNode getPreviousTocNode(TocTreeNode focusNode)
        {
        int index = nodeList.indexOf(focusNode);
        TocTreeNode foundNode = null;
        if (index > 0)	
            foundNode = (TocTreeNode) nodeList.get(index - 1);
	return foundNode;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: TocTreeNode.java,v 1.10.2.1 2015/01/01 10:32:30 rudahl Exp $ \n";
	}

    }
