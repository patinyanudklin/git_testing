/**
 * FileReferenceComparator
 *
 * ~~ Copyright  2002-2015  by Goldin-Rudahl Associates
 * ~~ EndC
 *
 * Created by Sally Goldin, 8/28/2002
 *
 *  $Id: FileReferenceComparator.java,v 1.2.2.1 2015/01/01 13:51:54 rudahl Exp $
 *  $Log: FileReferenceComparator.java,v $
 *  Revision 1.2.2.1  2015/01/01 13:51:54  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.3  2007/07/30 09:12:19  goldin
 *  Get rid of unchecked warnings
 *
 *  Revision 1.2  2007/01/05 07:41:58  rudahl
 *  added Whatis info
 *
 *  Revision 1.1  2002/08/28 16:33:05  goldin
 *  Work on merging MRU lists
 *
 *
 */

package com.grs.gui;
import java.util.*;

/**
 * This class provides methods used to sort FileReferences by
 * their access times. The most recent references should come
 * first in the list, i.e. the sort is descending by time stamp.
 */
public class FileReferenceComparator implements Comparator<FileReference>  
    {
      /**
       * Main comparator method. Will throw a class cast exception
       * if the objects being compared are not FileReference objects.
       */
    public int compare(FileReference f1, FileReference f2)
        {
        long difference = f2.refTime - f1.refTime;
	if (difference < 0)
	    return -1;
	else if (difference > 0)
	    return 1;
	else
	    return (f1.fileName.compareToIgnoreCase(f2.fileName));
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FileReferenceComparator.java,v 1.2.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }

