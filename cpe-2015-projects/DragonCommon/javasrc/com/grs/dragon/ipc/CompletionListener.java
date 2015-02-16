/**
 * CompletionListener
 *
 * ~~ Copyright 2001-2015 by Goldin-Rudahl Associates
 * ~~ EndC
 *
 * Created by Sally Goldin, 6/8/2001
 *
 *  $Id: CompletionListener.java,v 1.2 2015/01/01 09:42:06 rudahl Exp $
 *  $Log: CompletionListener.java,v $
 *  Revision 1.2  2015/01/01 09:42:06  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.1  2001/11/19 20:30:32  goldin
 *  Move IPC classes to new package
 *
 *  Revision 1.3  2001/11/16 18:05:54  goldin
 *  Move more classes from dragon.ui to gui package
 *
 *  Revision 1.2  2001/11/05 13:59:14  goldin
 *  Put UI code in a package
 *
 *  Revision 1.1  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 */

package com.grs.dragon.ipc;
/**
 * This interface defines a single method to be called by
 * ReplyMonitor objects. Its primary reason for existence is
 * to allow the ReplyMonitor class to be common.
 */
public interface CompletionListener
    {

      /**
       * Called by reply monitor when a reply or nak file is
       * returned after a command is sent.
       * @param bSuccess Did the commmand complete successfully?
       * @param replyFile Object holding parsed contents of the reply or
       *                  Nak file.
       */
    public void commandCompleted(boolean bSuccess,
				 IpcFile replyFile);

    }
