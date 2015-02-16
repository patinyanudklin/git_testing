/**
 * PlatformSpecific.java
 *
 *	Copyright 2006 Kurt Rudahl and Sally Goldin
 *                     and King Mongkut's University of Technology Thonburi
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *
 ***************************************************
 *  $Id: PlatformSpecific.java,v 1.1.4.1 2010/09/10 10:12:25 rudahl Exp $
 *  $Log: PlatformSpecific.java,v $
 *  Revision 1.1.4.1  2010/09/10 10:12:25  rudahl
 *  Needed some additional exception info
 *
 *  Revision 1.1  2006/01/21 07:53:29  goldin
 *  Add new class to allow UI to register itself in the global INI file
 *
 *
 ***************************************************
 *  This class exposes native methods that invoke
 *  operating system dependent functionality.
 *  Normally, if the operating system does not need
 *  or support the functionality, a call the function
 *  will be a no-op.
 */

package com.grs.dragon.common;

import java.awt.*;

/**
 * This class exposes native methods that invoke
 * platform-specific functionality.
 */
public class PlatformSpecific
    {
      /**
       * Initializer code to load the library
       * Also invoked by other classes, but documentations says
       * if the library is already loaded, there will
       * be no negative effects.
       */
    static 
        {
	try 
	     {
	     System.loadLibrary("javautil");
	     }
	catch (Error e)
	     {
	     System.out.println("Cannot load C++ utility DLL");
//	     System.out.println("exception is "+e);
//	     e.printStackTrace();
	     }
	}

      /**
       * Record the window handle of the window with a title
       * that matches 'windowTitle'
       * in the profile file using the passed key
       * @param windowTitle  Title bar title, used to look up window
       * @param moduleKey  Key/identifier used to look up the
       *                      this window. This is module name, e.g. "UI"
       */
    public static native void recordWindowByTitle(String windowTitle,
					          String moduleKey);


}












