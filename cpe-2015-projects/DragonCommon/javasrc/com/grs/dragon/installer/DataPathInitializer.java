/**
 * DataPathInitializer 
 *
 * Copyright 2001 by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 12/18/2001
 *
 *  $Id: DataPathInitializer.java,v 1.1 2001/12/18 15:13:49 goldin Exp $
 *  $Log: DataPathInitializer.java,v $
 *  Revision 1.1  2001/12/18 15:13:49  goldin
 *  New initializer for DPATH and WPATH
 *
 */

package com.grs.dragon.installer;
import com.grs.dragon.common.*;
import com.grs.gui.*;
import javax.swing.*;
import java.awt.*;
import java.io.File;

/**
 * This class implements the Initializer interface. It is used
 * to set the initial values on the fields used to input
 * the values for DPATH and WPATH.
 */
public class DataPathInitializer implements Initializer
    {
      /**
       * Primary method sets the values based on data in the
       * Panel table.
       * @param field One of the path fields in the path panel.
       */
    public void setInitialValue(DragonField field)
        {
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
	String basePath = (String) DragonPanel.fieldValueTable.get("SYSPATH");
	field.setFieldValue(basePath + File.separator +
				     "images");
	}
    }
