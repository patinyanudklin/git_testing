/**
 * FontInitializer.java
 * 
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/31/2001
 *
 * $Id: FontInitializer.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: FontInitializer.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/10/31 16:27:04  goldin
 * Add Id and Log fields
 *
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;

/** 
 * This class provides a method which sets a font field to the
 * current default font. The default is obtained by querying the
 * DragonFontChooser object.
 */
public class FontInitializer implements Initializer
    {
      /**
       * Set the initial value of the passed field as appropriate
       * @param field DragonField whose value is to be set.
       */
    public void setInitialValue(DragonField field)
        {
        DFontField fontField = (DFontField) field;
	String currentDefault = 
           DragonUI.currentApplication.getFontChooser().getCurrentDefault();
        if (currentDefault != null)
           fontField.setFieldValue(currentDefault);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FontInitializer.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
