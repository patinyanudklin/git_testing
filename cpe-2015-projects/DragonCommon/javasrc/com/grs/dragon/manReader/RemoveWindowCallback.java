/**
 * RemoveWindowCallback
 *
 * Copyright 2002 Goldin-Rudahl Associates
 *
 * $Id: RemoveWindowCallback.java,v 1.3 2007/05/31 03:26:53 rudahl Exp $
 * $Log: RemoveWindowCallback.java,v $
 * Revision 1.3  2007/05/31 03:26:53  rudahl
 * add 'whatis' boilerplate
 *
 * Revision 1.2  2005/08/03 04:42:53  goldin
 * Comment out references to Win32WindowRecorder for now
 *
 * Revision 1.1  2002/09/19 22:36:52  goldin
 * New callback to cleanup when manreader closes
 *
 *
 */

package com.grs.dragon.manReader;
import com.grs.gui.*;
import com.grs.dragon.common.*;

/** 
 * This class deregisters the manreader window upon exit
 */
public class RemoveWindowCallback implements Callback
    {
     /** Primary method of a callback class. Modifies other fields in a
       *   DragonPanel based on the current value in the 0.0 The
       *   DragonPanel can be accessed via its reference in the
       *   DragonField object.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	//Win32WindowRecorder.removeWindow("MR");
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: RemoveWindowCallback.java,v 1.3 2007/05/31 03:26:53 rudahl Exp $ \n";
	}

    }

