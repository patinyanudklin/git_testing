/**
 * MultiSelectInitializer.java
 * 
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/15/2007
 *
 * $Id: MultiSelectInitializer.java,v 1.2 2007/02/23 08:36:29 goldin Exp $
 * $Log: MultiSelectInitializer.java,v $
 * Revision 1.2  2007/02/23 08:36:29  goldin
 * Clear rule list when you re-enter the operation
 *
 * Revision 1.1  2007/02/15 11:16:37  goldin
 * Add initializer to clear multi-select file boxes when we enter a panel
 *
 *
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;

/** 
 * This class provides a method which initializes a multi-select
 * field by clearing any old values.
 */
public class MultiSelectInitializer implements Initializer
    {
      /**
       * Set the initial value of the passed field as appropriate
       * @param field DragonField whose value is to be set.
       */
    public void setInitialValue(DragonField field)
        {
	if (field instanceof DMultiFileField) 
	    {
	    DMultiFileField multiField = (DMultiFileField) field;
	    multiField.clearField();
	    }
	else if (field instanceof DListBox) 
	    {
	    DListBox multiField = (DListBox) field;
	    multiField.clearField();
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: MultiSelectInitializer.java,v 1.2 2007/02/23 08:36:29 goldin Exp $ \n";
	}
    }
