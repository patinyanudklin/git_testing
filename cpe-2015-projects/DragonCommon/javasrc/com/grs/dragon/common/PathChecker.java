/**
 *  PathChecker
 *
 *  ~~ Copyright 2002-2015 by Goldin-Rudahl Associates
 *  ~~ EndC
 *
 *  Created 9/25/2002 by Sally Goldin
 *
 *  $Id: PathChecker.java,v 1.2.4.1 2015/01/01 10:32:30 rudahl Exp $
 *  $Log: PathChecker.java,v $
 *  Revision 1.2.4.1  2015/01/01 10:32:30  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.3  2015/01/01 09:56:15  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.2  2005/12/10 09:35:50  goldin
 *  Fix FilenameDocument to allow unicode characters in filenames
 *
 *  Revision 1.1  2002/09/25 17:24:50  goldin
 *  Add PathChecker to insure 8.3 paths
 *
 */

package com.grs.dragon.common;

import java.util.StringTokenizer;

/**
 * This class is used by several Dragon validators. It
 * has a single method which takes a Windows/DOS style
 * path as an argument, and returns true if all the
 * components (subdirectories) in the path are 8 characters
 * long or fewer. Otherwise it returns false. It will
 * also return false if it finds a space or other illegal
 * character in the path specification.
 */
public class PathChecker
    {

    /**
     * Check that path expression meets DOS 8.3 specifications.
     * @param pathSpec  Path to check
     *        12/10/05 Allow longer filenames but still no blanks
     * @return true if path is legal for 16-bit/MS-DOS programs,
     *         otherwise false.
     */
    public static boolean isPathOk(String pathSpec)
        {
        boolean bOk = true;
	String testPath = null;
	int pos = pathSpec.indexOf(":");  // may have a drive letter
	if (pos > 0)
	    {
	    testPath = pathSpec.substring(pos+1);
	    }
	else 
	    {
	    testPath = pathSpec;
	    }
        StringTokenizer tokenizer = new StringTokenizer(testPath,"\\/");
        while ((tokenizer.hasMoreTokens()) && (bOk))
	    {
            String subpath = tokenizer.nextToken();
            if (subpath.indexOf(" ") >= 0)
                bOk = false;
	    //else if (subpath.length() > 8)
	    //    bOk = false;
	    }
	return bOk;
	}


    }

