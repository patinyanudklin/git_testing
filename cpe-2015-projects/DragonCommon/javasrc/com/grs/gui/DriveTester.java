/**
 *  DriveTester
 * 
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 5/31/01
 *
 *   $Id: DriveTester.java,v 1.8.2.1 2010/09/10 10:02:06 rudahl Exp $
 *   $Log: DriveTester.java,v $
 *   Revision 1.8.2.1  2010/09/10 10:02:06  rudahl
 *   Needed some additional exception info
 *
 *   Revision 1.8  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.7  2005/04/01 08:52:41  goldin
 *   Changed to load javautil instead of winrecorder dll
 *
 *   Revision 1.6  2005/03/29 13:04:34  goldin
 *   Temporarily disable call to JNI fn
 *
 *   Revision 1.5  2005/02/06 06:12:01  goldin
 *   Make this a no-op if not windows
 *
 *   Revision 1.4  2002/09/27 15:45:09  goldin
 *   Change DriveTester to use JNI
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
 *   Revision 1.4  2001/11/05 13:59:15  goldin
 *   Put UI code in a package
 *
 *   Revision 1.3  2001/06/04 10:43:43  goldin
 *   Get rid of print statement
 *
 *   Revision 1.2  2001/06/04 10:42:48  goldin
 *   Fix bug - was not specifying the directory in the redirectd file name
 *
 *   Revision 1.1  2001/05/31 17:10:53  goldin
 *   Work on problems with file dlg; esp. handling of empty drives
 *
 */

package com.grs.gui;
import java.io.*;
/**
 * This class is used to test, whether a drive
 * has a disk in it. The class now calls a native function
 * which executes C library calls, rather than relying
 * on spawning an MS-DOS command.
 */
public class DriveTester
    {
    protected static boolean bDoTest = true;
    protected static boolean bIsWindows = false;
      /**
       * Initializer code to load the library
       * Presumably if it is already loaded, there will be
       * no bad effects
       */
    static 
        {
        String OS = System.getProperty("os.name");
	if (OS.toUpperCase().indexOf("WIN") >= 0)
	    {
	    bIsWindows = true;
	    }
	if (bIsWindows)
	    {
	    try 
	        {
	        System.loadLibrary("javautil");
	        }
	    catch (Error e)
	        {
	        System.out.println("Cannot load java utilities C++ library");
//		System.out.println("exception is "+e+" path is '"
//				   +System.getProperty("java.library.path")+"'");
//		e.printStackTrace();
	        }
	    }
	else
	    {
	    bDoTest = false;
	    }
	}

    public static boolean isDriveOk(String testDrive)
        {
        if (bDoTest == false)
            return true;
	String rootPath = null;
        if (testDrive.length() != 4)
	    rootPath = testDrive.substring(0,1) + ":\\";
	else
	    rootPath = testDrive;
            
        boolean bOk = CheckDrive(rootPath.toUpperCase());
        return bOk;
	}

   /**
    * Turn drive testing on or off. However, if we
    * are not running on Windows, ignore any attempts to
    * set this flag
    */
    public static void setDoTest(boolean bFlag)
        {
	if (bIsWindows)
	    bDoTest = bFlag;
	}

    public static native boolean CheckDrive(String driveString);


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DriveTester.java,v 1.8.2.1 2010/09/10 10:02:06 rudahl Exp $ \n";
	}
    }






