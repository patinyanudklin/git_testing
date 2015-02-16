/**
 * FileReference
 *
 * Copyright  2002-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 8/28/2002
 *
 *  $Id: FileReference.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $
 *  $Log: FileReference.java,v $
 *  Revision 1.3  2007/01/05 07:41:58  rudahl
 *  added Whatis info
 *
 *  Revision 1.2  2002/08/31 00:03:23  goldin
 *  continue major redesign of FileChooser
 *
 *  Revision 1.1  2002/08/28 16:33:05  goldin
 *  Work on merging MRU lists
 *
 *
 */

package com.grs.gui;

/**
 * This is a public data class used to create time-stamped references
 * to files.
 */
public class FileReference 
    {
    public String fileName;    // full filename and path
    public long refTime;       // last reference time (system time in seconds)

    public FileReference()
        {
	fileName = null;
	refTime = 0;
	}

    public FileReference(String fname, long time)
        {
	fileName = fname;
	refTime = time;
	}
       
    public String toString()
        {
	return fileName;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FileReference.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }





