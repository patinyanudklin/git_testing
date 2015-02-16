/**
 * SimpleWindowMonitor
 * 
 *  ~~ Copyright 2001-2015 by Sally Goldin & Kurt Rudahl
 *  ~~ EndC
 *
 * Created by Sally Goldin, 11/27/2000
 *
 *  $Id: SimpleWindowMonitor.java,v 1.4.4.1 2015/01/01 10:32:30 rudahl Exp $
 *  $Log: SimpleWindowMonitor.java,v $
 *  Revision 1.4.4.1  2015/01/01 10:32:30  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.5  2015/01/01 09:56:15  rudahl
 *  consolidating Dragon and OpenDragon
 *
 *  Revision 1.4  2005/02/06 08:25:55  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.3  2002/10/22 15:58:14  goldin
 *  Make it possible to turn off the confirmation of exit
 *
 *  Revision 1.2  2002/09/19 16:10:17  goldin
 *  Add method to change confirm message after creation
 *
 *  Revision 1.1  2001/12/03 16:26:28  goldin
 *  Move SimpleWindowMonitor to common pkg
 *
 *  Revision 1.1  2001/11/27 17:40:00  goldin
 *  Allow us to exit -temporary
 *
 */

package com.grs.dragon.common;
import com.grs.gui.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 * Simple window adapter to react to the user's trying to close
 * a window. Currently prompts and if the user says OK, exits
 * the application.*/
public class SimpleWindowMonitor extends WindowAdapter
{
   protected Component monitoredWindow = null;
   protected JOptionPane confirmDialog = null;
   protected static final String YES = "Yes";
   protected static final String NO = "No";
   protected String messageString = null;
   protected boolean bConfirm = true;

  
  /**
   * Callback to execute (if any) before exiting.
   */
   protected Callback cleanupCallback = null;

  /**
   * Constructor receives and saves a reference to the
   * window being monitored. It also constructs a confirmation
   * dialog.
   * @param parentComponent  Component that requested monitoring
   * @param messageString    Question to ask upon attempted close
   */
   public SimpleWindowMonitor(Component parentComponent,
			      String messageString)
      {
      this.messageString = messageString;
      monitoredWindow = parentComponent;
      Object[] options = new Object[2];
      options[0] = YES;
      options[1] = NO;
      confirmDialog = new JOptionPane(messageString,
				      JOptionPane.QUESTION_MESSAGE,
				      JOptionPane.YES_NO_OPTION,null,
				      options,options[0]);
      }

  /** 
   * Respond to the user's attempt to close the window using
   * operating-system-specific mechanisms.
   */
   public void windowClosing(WindowEvent we)
      {
      if (bConfirm)
	  {
          confirmDialog.setMessage(messageString);
	  confirmDialog.setValue(null);
	  confirmDialog.setInitialValue(YES);
	  JDialog dlg = confirmDialog.createDialog(monitoredWindow,null);
	  dlg.setVisible(true);
	  Object val = confirmDialog.getValue();
	  if (val instanceof String)
	      {
	      String response = (String)val;
	      if (response.equals(YES))
	          {
		  if (cleanupCallback != null)
		    cleanupCallback.executeCallback(null);
	          System.exit(0);
		  }
	      }
   	  else
	      {
	      monitoredWindow.setVisible(true);
	      }
	  }
      else
	  {
	  if (cleanupCallback != null)
	      cleanupCallback.executeCallback(null);
	  System.exit(0);
	  }
      }

  /**
   * Set cleanup callback in case we need to do deallocations or
   * other cleanup before we exit.
   * @param cb  Callback to call before exit.
   */
   public void setCleanupCallback(Callback cb)
      {
      cleanupCallback = cb;
      }

  /**
   * Change the message string.
   */
   public void setMessageString(String msg)
       {
       messageString = msg;
       }

  /**
   * Change the confirmation flag
   */
   public void setConfirm(boolean flag)
       {
       bConfirm = flag;
       }

}

