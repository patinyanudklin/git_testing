/**
 * SetOnePathCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: SetOnePathCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SetOnePathCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/29 16:12:33  goldin
 * Add common pkg import
 *
 * Revision 1.2  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/05/03 15:04:31  goldin
 * Add special file handling to command line and command forwarder
 *
 */
package com.grs.dragon.ui;
import com.grs.dragon.common.*;
import com.grs.gui.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  setting of a single path in the config file and the writing
 *  of a new config file version. It is used to implement
 *  -DPATH, -WPATH and -CPATH.
 */
public class SetOnePathCallback implements Callback
    {
      /** Primary method of a callback class.
       *  Displays the dialog and waits for user input.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        DragonUI mainApp = (DragonUI) field.getParentComponent();
        String command = field.getName();
	String pathArg = field.getLabelText();
        if (command.equalsIgnoreCase("-DPATH"))
	    {
	    DragonUI.cfgProcessor.setDpath(pathArg);                
            }
        else if (command.equalsIgnoreCase("-WPATH"))
	    {
	    DragonUI.cfgProcessor.setWpath(pathArg);                
            }
	else if (command.equalsIgnoreCase("-CPATH"))
	    {
	    DragonUI.cfgProcessor.setCpath(pathArg);                
            }
	mainApp.getCfgProcessor().writeNewFile();
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SetOnePathCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

