/* ViewportNativeHost.java
 * kurt rudahl 17-Apr-2002
 * copyright Sally Goldin & Kurt Rudahl
 * purpose: permit classes to use methods which may, or may not,
 *	    access a native host via e.g. JNI
 *	    In this implementation, all of the methods communicate
 *		via JNI to viewProg.java
 **************************************************************************
 * $Id: ViewportNativeHost.java,v 1.2 2005/02/06 09:17:30 goldin Exp $
 * $Log: ViewportNativeHost.java,v $
 * Revision 1.2  2005/02/06 09:17:30  goldin
 * Fix javadoc warnings
 *
 * Revision 1.1  2002/04/17 21:11:22  rudahl
 * added NativeHost interface; not yet used
 *
 **************************************************************************
 * history 4/17/2002   created
 */

package com.grs.dragon.viewport;

import com.grs.gui.*;

/**
 * Permit classes to use methods which may, or may not,
 * access a native host via  JNI.
 * In this implementation, all of the methods communicate
 * via JNI to viewProg.java
 */
public class ViewportNativeHost implements NativeHost
    {
    public void SendEvent(int MsgNo) 
	{
	viewProg.SendViewportEvent(MsgNo);
	}

    public void SendEvent(String MsgName)
	{
	viewProg.SendViewportEvent(MsgName);
	}

      /** Fix Non-client area of dialog which has just been displayed
       *  find the dialog window and a) change the title b) kill SystemMenu
       *  and c) set it to be TOPMOST
       *  @param CurrentTitle   string which is used to find the dialog
       *  @param NewTitle   string which will replace the title, or ""
       *  @param bMoveSizeOK  do not delete Move or Size menu items
       */
    public void FixupNCDialog(String CurrentTitle, 
			      String NewTitle,
			      boolean bMoveSizeOK)
	{
	viewProg.FixupNCDialog(CurrentTitle,NewTitle,bMoveSizeOK);
	}

      /* controls the dialog-topmost status specifically for the 
       * one and only PromptAndReply panel. Assumes viewjava.cpp
       * already knows the window handle
       * @param bRelease   true => release window from being topmost
       *                   false => restore window to being topmost
       */
    public void SetNCDialogTopmost(boolean bRelease)
	{
	viewProg.SetPandRNCDialogTopmost(bRelease);
	}

      //~~ for testing, uncomment the method definition
      //~~ for production, uncomment the native declaration 
    public void log(String Msg)
	{
	viewProg.logViewportP(Msg);
	}
    }

