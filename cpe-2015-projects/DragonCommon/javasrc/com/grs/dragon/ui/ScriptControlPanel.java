/**
 *  ScriptControlPanel
 * 
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 9/4/2001
 *
 *  $Id: ScriptControlPanel.java,v 1.14 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ScriptControlPanel.java,v $
 *  Revision 1.14  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.13  2002/01/24 17:07:37  goldin
 *  Keep track of whether last script was cancelled, to eliminate spurious 'continue' commands
 *
 *  Revision 1.12  2002/01/23 16:22:41  goldin
 *  improve script handling
 *
 *  Revision 1.11  2001/11/21 15:17:53  goldin
 *  Make all references to getTimeOffset use ApplicationManager method
 *
 *  Revision 1.10  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.9  2001/11/16 12:09:23  goldin
 *  Revise border setting to work with java 1.2
 *
 *  Revision 1.8  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.7  2001/10/03 15:15:46  goldin
 *  Trying to debug state changes
 *
 *  Revision 1.6  2001/09/28 11:53:39  goldin
 *  Improve display of state during script running/pausing/waiting
 *
 *  Revision 1.5  2001/09/11 14:50:30  goldin
 *  Implement -WAIT command
 *
 *  Revision 1.4  2001/09/11 11:48:11  goldin
 *  Fix enabling/disabling of menus during script handling
 *
 *  Revision 1.3  2001/09/10 14:39:04  goldin
 *  Refine visual state during script runs
 *
 *  Revision 1.2  2001/09/05 10:46:12  goldin
 *  Add tooltips
 *
 *  Revision 1.1  2001/09/04 15:08:50  goldin
 *  Begin implementing script control panel
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;

/**
 * This class implements a button pad for controlling scripts.
 * It is visible only when DRAGON is in fact running a script.
 * The class handles its own actions, and also manages the
 * display of help messages and tooltips.
 */
public class ScriptControlPanel extends JPanel 
                                implements ActionListener
    {
      /**
       * Constants to indicate the current state of the script
       */
    public static final int UNKNOWN_STATE = -1;
    public static final int RUNNING_STATE = 0;
    public static final int PAUSEPENDING_STATE = 1;
    public static final int PAUSED_STATE = 2;
    public static final int REWINDING_STATE = 3;
    public static final int WAITING_STATE = 4;
    public static final int CANCELLED_STATE = 5;

    protected int currentState = UNKNOWN_STATE;
    protected int lastState = UNKNOWN_STATE;

      /**
       * Buttons on the control panel. Make them public so we can
       * set the help listener etc in the main DragonUI 
       * processDummyPanel method.
       */
    public JButton restartBtn = null;
    public JButton cancelBtn = null;
    public JButton pauseBtn = null;
    public JButton resumeBtn = null;
    public JButton nextStepBtn = null;

      /**
       * Reference to DRAGON main app. Initialized in constructor
       */
    protected DragonUI mainApp = null;

      /** 
       * Reference to the command forwarder. Pushing buttons
       * causes commands to be sent to the script server
       */
    protected CommandForwarder forwarder = null;
    
      /**
       * Keep track of whether latest script was cancelled.
       * This will allow us to disregard "CONTINUE" commands
       * that get generated after the CANCEL has been processed.\
       */
    protected boolean bLastScriptCancelled = false;

      /**
       * Constructor. Pass references to the forwarder and
       * the main Dragon UI. 
       */
    public ScriptControlPanel(CommandForwarder forwarder,
		       DragonUI mainApp)
        {
        this.forwarder = forwarder;
	this.mainApp = mainApp;
	String toolTip = null;
	I18NTextSource textSource = mainApp.getTextSource();
        setBorder(new EtchedBorder(EtchedBorder.RAISED));
	setLayout(new FlowLayout());
        Insets insets = new Insets(0,0,0,0);

        restartBtn = new JButton(new ImageIcon("restart.gif"));
	restartBtn.setMargin(insets);
	add(restartBtn);
        restartBtn.addActionListener(this);
	toolTip = textSource.getI18NText(TextKeys.RESTARTSPT,"RESTART SCRIPT");
	restartBtn.setToolTipText(toolTip);

        cancelBtn = new JButton(new ImageIcon("cancel.gif"));
	cancelBtn.setMargin(insets);
	add(cancelBtn);
        cancelBtn.addActionListener(this);
	toolTip = textSource.getI18NText(TextKeys.CANCELSPT,"CANCEL SCRIPT");
	cancelBtn.setToolTipText(toolTip);

        pauseBtn = new JButton(new ImageIcon("pause.gif"));
	pauseBtn.setMargin(insets);
	add(pauseBtn);
        pauseBtn.addActionListener(this);
	toolTip = textSource.getI18NText(TextKeys.PAUSESPT,"PAUSE SCRIPT");
	pauseBtn.setToolTipText(toolTip);

        resumeBtn = new JButton(new ImageIcon("resume.gif"));
	resumeBtn.setMargin(insets);
	add(resumeBtn);
        resumeBtn.addActionListener(this);
	toolTip = textSource.getI18NText(TextKeys.RESUMESPT,"RESUME SCRIPT");
	resumeBtn.setToolTipText(toolTip);

        nextStepBtn = new JButton(new ImageIcon("nextStep.gif"));
	nextStepBtn.setMargin(insets);
	add(nextStepBtn);
        nextStepBtn.addActionListener(this);
	toolTip = textSource.getI18NText(TextKeys.NEXTSTEPSPT,
					 "NEXT SCRIPT STEP");
	nextStepBtn.setToolTipText(toolTip);

        currentState = RUNNING_STATE;
	enableButtonsForState();
	}

   public void actionPerformed(ActionEvent ev)
        {
        Object source = ev.getSource();
	if (source.equals(restartBtn))
	    {
            forwarder.sendCommandToServer("-RESTART");
	    setCurrentState(REWINDING_STATE);
	    }
	else if (source.equals(cancelBtn))
	    {	    
            forwarder.sendCommandToServer("-CANCEL");
	    bLastScriptCancelled = true;
	    setCurrentState(CANCELLED_STATE);
	    }
	else if (source.equals(pauseBtn))
	    {
            forwarder.sendCommandToServer("-PAUSE");
	    setCurrentState(PAUSEPENDING_STATE);
	    }
	else if (source.equals(resumeBtn))
	    {
            forwarder.sendCommandToServer("-UNPAUSE");
	    setCurrentState(RUNNING_STATE);
	    }
	else if (source.equals(nextStepBtn))
	    {
            forwarder.sendCommandToServer("-CONTINUE");
	    setCurrentState(RUNNING_STATE);
	    }
	}

      /**
       * Enable/disable buttons depending on the currentState
       */
   protected void enableButtonsForState()
       {
	 // start by disabling them all
	 // in many states, this is the correct situation.
       restartBtn.setEnabled(false);
       cancelBtn.setEnabled(false);
       pauseBtn.setEnabled(false);
       resumeBtn.setEnabled(false);
       nextStepBtn.setEnabled(false);
       switch (currentState)
	   {
	   case RUNNING_STATE:
               restartBtn.setEnabled(true);
	       cancelBtn.setEnabled(true);
	       pauseBtn.setEnabled(true);
               break;
	   case PAUSED_STATE:
               restartBtn.setEnabled(true);
	       cancelBtn.setEnabled(true);
	       resumeBtn.setEnabled(true);
               resumeBtn.requestFocus();
	       break;
	   case WAITING_STATE:
               restartBtn.setEnabled(true);
	       cancelBtn.setEnabled(true);
	       nextStepBtn.setEnabled(true);
               nextStepBtn.requestFocus();
	       break;
	   default:
	       break;
	   }
       repaint();
       }
      
      /**
       * Allow callbacks to set the current state of the
       * buttons.
       */
   public synchronized void setCurrentState(int state)
       {
       lastState = currentState;
       currentState = state;
       //Tracer.outputTraceMessage("Setting script state to " +
       //                          String.valueOf(state),"UI",
       //                          ApplicationManager.getTimeOffset());
       mainApp.setScriptStatusMessage(currentState);
       enableButtonsForState();
       }

      /**
       * Allow callbacks to set state back to previous value
       * in cases where a command returns a Nak.
       */
   public void resetCurrentState()
       {
       setCurrentState(lastState);
       }

      /**
       * Return current state for outsiders to know.
       */
   public int getCurrentState()
       {
       return currentState;
       }

   public boolean wasLastScriptCancelled()
       {
       return bLastScriptCancelled;
       }

   public void setLastScriptCancelled(boolean bFlag)
       {
       bLastScriptCancelled = bFlag;
       }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ScriptControlPanel.java,v 1.14 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
   }


