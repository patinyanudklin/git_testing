/*  InstallerLanguageCallback.java
 *
 * Copyright 2005 Sally Goldin and Kurt Rudahl
 *
 * $Id: InstallerLanguageCallback.java,v 1.2 2005/12/08 08:02:55 goldin Exp $
 * $Log: InstallerLanguageCallback.java,v $
 * Revision 1.2  2005/12/08 08:02:55  goldin
 * Use images to illustrate language, not text, to avoid font problems
 *
 * Revision 1.1  2005/07/29 09:42:08  goldin
 * Add Language selection functionality
 *
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import com.grs.dragon.common.*;

//********************************************************************
/** 
 *  This class implements the Callback interface. It handles the
 *  display and processing of the language selection dialog.
 *  This is a concrete subclass of the LanguageCallback class,
 *  which is intended for use in the Installer only.
 */
public class InstallerLanguageCallback extends LanguageCallback
    {
      /**
       * Hold on to the field passed in by the execute method.
       * This gives us a handle to the DragonUI instance, so
       * we can then access the help area.*/
    protected DragonField dummyField = null;

      /**
       * Reference to the parent installer 
       */
    protected Installer parentInstaller = null;

      /**
       * Constructor sets the parent installer reference,
       * so we can set the language. Also passes the 
       * bInstaller flag as true to the superclass.
       */
    public InstallerLanguageCallback(Installer parent)
        {
	super(true);
	this.parentInstaller = parent;
	}


    /**
     * Process the selected index to reset the language
     */
    protected void setCurrentLanguage()
        {
	if (selectedIndex >= 0)
	    {
	    currentLanguage = codes[selectedIndex];
	    parentInstaller.setSelectedLanguage(currentLanguage);
	    }
	}

      /**
       * Set help message to passed string.
       */
    protected void setHelpMsg(String msg)
        {
	  /* No help area exists at this point */
	}


    }

