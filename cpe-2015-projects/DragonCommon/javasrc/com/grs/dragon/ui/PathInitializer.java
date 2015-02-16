/**
 * PathInitializer 
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 3/22/2001
 *
 *  $Id: PathInitializer.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: PathInitializer.java,v $
 *  Revision 1.9  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.8  2001/11/30 18:01:21  goldin
 *  Moved most of the UI basic components to the com.grs.gui package
 *
 *  Revision 1.7  2001/11/29 16:12:33  goldin
 *  Add common pkg import
 *
 *  Revision 1.6  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.5  2001/10/08 15:02:13  goldin
 *  Init CPATH based on WPATH, if missing
 *
 *  Revision 1.4  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.3  2001/04/12 14:10:31  goldin
 *  complete implementation of FontChooser and associated Font control
 *
 *  Revision 1.2  2001/04/10 15:16:33  goldin
 *  Initial implementation of Font Choosing dialog
 *
 *  Revision 1.1  2001/03/22 12:57:33  goldin
 *  Implement paths panel, including initializer, callback, new path datatype
 *
 */

package com.grs.dragon.ui;
import com.grs.dragon.common.*;
import com.grs.gui.*;
import javax.swing.*;
import java.awt.*;

/**
 * This class implements the Initializer interface. It is used
 * to set the initial values on the fields in the Paths form,
 * using values from the DRAGON CFG file.*/
public class PathInitializer implements Initializer
    {
      /**
       * Primary method sets the values based on data in the
       * config file. Which data we use is determined by which
       * field we are in.
       * @param field One of the path fields in the path panel.
       */
    public void setInitialValue(DragonField field)
        {
        String fieldID = field.getName();
	String value = null;
	if (fieldID.compareTo("^FMD") == 0)
	    value = DragonUI.cfgProcessor.getDpath();
	else if (fieldID.compareTo("^FMW") == 0)
	    value = DragonUI.cfgProcessor.getWpath();
	else if (fieldID.compareTo("^FMK") == 0)
	    value = DragonUI.cfgProcessor.getKpath();
	else if (fieldID.compareTo("^FMC") == 0)
	    {
	    value = DragonUI.cfgProcessor.getCpath();
	    if ((value == null) || (value.length() == 0))
	         value = DragonUI.cfgProcessor.getWpath();
	    }
                 
	if (value != null)
	    field.setFieldValue(value);
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: PathInitializer.java,v 1.9 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
