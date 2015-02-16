/* DragonLanguageCallback.java
 *
 * Copyright  2005-2007  by Sally Goldin and Kurt Rudahl
 *
 * $Id: DragonLanguageCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DragonLanguageCallback.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2005/12/08 08:02:45  goldin
 * Use images to illustrate language, not text, to avoid font problems
 *
 * Revision 1.2  2005/07/31 05:22:44  goldin
 * Add swing import
 *
 * Revision 1.1  2005/07/29 09:39:54  goldin
 * Add DragonLanguageCallback.java
 *
 */

package com.grs.dragon.ui;
import com.grs.dragon.common.*;
import com.grs.gui.*;
import javax.swing.*;

//********************************************************************
/** 
 *  This is a concrete subclass of LanguageCallback that handles the
 *  display and processing of the language selection dialog in Dragon.
 *  There is another subclass used in the Installation application.
 */
public class DragonLanguageCallback extends LanguageCallback
    {
      /**
       * Hold on to the field passed in by the execute method.
       * This gives us a handle to the DragonUI instance, so
       * we can then access the help area.*/
    protected DragonField dummyField = null;

    /**
     * Constructor calls superclass constructor with
     * bInstaller set to false.
     */
    public DragonLanguageCallback()
       {
       super(false);
       }

    /**
     * Process the selected index to reset the language
     * Then update the config file with this new information.
     */
    protected void setCurrentLanguage()
        {
	if (selectedIndex >= 0)
	    {
	    currentLanguage = codes[selectedIndex];
	    DragonUI.cfgProcessor.setCountry(currentLanguage);
	    DragonUI.cfgProcessor.writeNewFile();
	    }
	}

      /**
       * Set help message to passed string.
       */
    protected void setHelpMsg(String msg)
        {
	if (dummyField == null)
	    return;
        DragonUI ui = (DragonUI) dummyField.getParentComponent();
	JEditorPane helpArea = ui.getHelpArea();
	helpArea.setText(msg);
	}



    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonLanguageCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }



