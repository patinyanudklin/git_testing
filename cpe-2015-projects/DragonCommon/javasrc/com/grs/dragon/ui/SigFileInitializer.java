/**
 * SigFileInitializer.java
 * 
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 6/29/2001
 *
 * $Id: SigFileInitializer.java,v 1.8 2007/01/05 07:41:57 rudahl Exp $
 * $Log: SigFileInitializer.java,v $
 * Revision 1.8  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.7  2002/04/02 00:09:03  goldin
 * correct comment
 *
 * Revision 1.6  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.5  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.4  2001/10/29 15:39:31  goldin
 * Clear previous value each time before initializing
 *
 * Revision 1.3  2001/10/17 10:47:56  goldin
 * Further debugging on signature interaction
 *
 * Revision 1.2  2001/07/18 15:25:30  goldin
 * Working to fix problems with handling of 'current' color scheme
 *
 * Revision 1.1  2001/07/05 08:18:03  goldin
 * Add new classes
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;

/** 
 * This class provides a method which is invoked for primary
 * signature file fields. The method checks to see if there
 * are currently signatures in memory, and if so, sets the
 * value of the field to the translated version of "(Current)".
 */
public class SigFileInitializer implements Initializer
    {
 
      /**
       * Set the initial value of the passed field as appropriate
       * @param field DragonField whose value is to be set.
       */
    public void setInitialValue(DragonField field)
        {
        DFileField fileField = (DFileField) field;
	String currentString = DragonUI.textSource.getI18NText(
						TextKeys.CURRENT,
						"(Current)");
	field.clearField();
        // get rid of previous value
	if (DragonUI.currentApplication.getStatusManager().isMemoryFileValid(
						 fileField.getFileType(),    
						 currentString))
             field.setFieldValue(currentString);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SigFileInitializer.java,v 1.8 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


