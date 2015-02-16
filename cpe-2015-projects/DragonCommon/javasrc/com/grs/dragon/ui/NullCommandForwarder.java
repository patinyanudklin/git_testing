/**
 *  NullCommandForwarder
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Implemented by Sally Goldin, 5/8/2001
 *
 *  $Id: NullCommandForwarder.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: NullCommandForwarder.java,v $
 *  Revision 1.4  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.3  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.2  2001/10/30 18:06:37  goldin
 *  Use UTF-8 for commands; replace stack with hashtable for
 *
 *  Revision 1.1  2001/05/08 10:14:18  goldin
 *  Add class to handle commands when UI running standalone
 *
 */

package com.grs.dragon.ui;
import java.io.*;
import java.util.*;

/**
 * This class implements the same interface as the CommandForwarder
 * class, but doesn't actually create or send any command files, or
 * wait for replies. It is used for situations where the UI runs
 * independently as a prototype/reference for translators.
 */
public class NullCommandForwarder extends CommandForwarder
    {
    /**
     * Constructor. This method sets up data items.
     * The class doesn't do anything until the immediately
     * sendCommandToServer method is invoked.
     */
    public NullCommandForwarder(DragonUI dragonUI, 
			    String filePath)
        {
	super(dragonUI,filePath);
        }

      /**
       * Cancel current command unconditionally. Override
       * the superclass method, since a null command forwarder 
       * does not have any monitors. 
       */
    public void cancelCommand(String sequence)
        {
        dragonUI.showDefaultPanel();
	dragonUI.setReady(true);
	}

      /**
       * This is the primary method of the class. We
       * display the command, add to history etc., but
       * otherwise we throw it away.
       */
    public boolean sendCommandToServer(String commandString)
        {
System.out.println("Processing command: " + commandString);
        boolean bOk = true;
        cmdCounter++;        
        SpecialCommand specCmd = checkSpecial(commandString);
        if ((specCmd != null) &&
	    (specCmd.getVerb().equalsIgnoreCase("EXIT")))
             System.exit(0);
        return bOk;
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: NullCommandForwarder.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
