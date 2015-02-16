/**
 * MemoryImageInitializer.java
 * 
 * Copyright  2002-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 4/1/2002
 *
 * $Id: MemoryImageInitializer.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 * $Log: MemoryImageInitializer.java,v $
 * Revision 1.2  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.1  2002/04/02 00:08:48  goldin
 * Set defaults for display to =M etc
 *
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;

/** 
 * This class provides a method which is invoked for the image file
 * fields in the display operations. It checks to see if there is
 * a current memory image (or RGB component image, for 3ba fields)
 * in memory, and if so, provides a default of the appropriate 
 * special filename.
 */
public class MemoryImageInitializer implements Initializer
    {
 
      /**
       * Set the initial value of the passed field as appropriate
       * @param field DragonField whose value is to be set.
       */
    public void setInitialValue(DragonField field)
        {
        DFileField fileField = (DFileField) field;
	field.clearField();
        // get rid of previous value
        String defaultVal = null;
	if (field.getName().compareTo("^FB") == 0)
            defaultVal = "=B";
	else if (field.getName().compareTo("^FG") == 0)
            defaultVal = "=G";
	else if (field.getName().compareTo("^FR") == 0)
            defaultVal = "=R";
	else
	    defaultVal = "=M";
	if (DragonUI.currentApplication.getStatusManager().isMemoryFileValid(
						 fileField.getFileType(),    
						 defaultVal))
	    {
	    fileField.setFieldValue(defaultVal);
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: MemoryImageInitializer.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


