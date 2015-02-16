/* SerialNumValidator.java
 *
 * Copyright 2002 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/14/2002
 *
 * $Id: SerialNumValidator.java,v 1.9 2007/05/22 10:20:20 goldin Exp $
 * $Log: SerialNumValidator.java,v $
 * Revision 1.9  2007/05/22 10:20:20  goldin
 * Modify behavior for use with new Key
 *
 * Revision 1.8  2006/03/07 07:19:19  goldin
 * Disable key number if this is not a keyed system
 *
 * Revision 1.7  2006/03/01 04:31:58  goldin
 * Make title and installation of driver depend on product passed to installer
 *
 * Revision 1.6  2005/12/11 09:01:52  goldin
 * Query the C++ code about whether key is needed
 *
 * Revision 1.5  2005/08/01 04:43:17  goldin
 * Completing I18N for installer
 *
 * Revision 1.4  2005/07/29 09:42:47  goldin
 * Add functionality to enable/disable key field based on SN
 *
 * Revision 1.3  2002/09/26 17:50:51  goldin
 * move serial num validation to C++
 *
 * Revision 1.2  2002/09/03 18:03:03  goldin
 * Fix bugs in running off the CD
 *
 * Revision 1.1  2002/02/15 21:20:28  goldin
 * Rework protection mechanisms &S/N-based product algorithm
 *
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import javax.swing.*;
import java.awt.*;
import java.util.*;

/** 
 * This class checks to make sure that the value entered in the
 * serial number field is of a valid form.
 */
public class SerialNumValidator implements Validator
    {
    protected static final String BAD_SN_MESSAGE =
        "Invalid Serial Number";
    protected String lastErrorMessage = null;
    protected String extraInfo = null;

    /** Returns true if current field value is valid, else false.
    * @param  field Field whose value is to be validated.
    */
    public boolean isValid(DragonField field)
        {
	boolean bValid = true;
	boolean bKeyEnabled = true;
	lastErrorMessage = null;
	String xlatedMsg = ApplicationManager.getTextSource().getI18NText(
					       "%h01.13.21",
					       BAD_SN_MESSAGE);
	String value = field.getFieldValue().toUpperCase();
	if ((value.length() < 12) || (value.length() > 14))
	    {
	    lastErrorMessage = xlatedMsg;
	    //lastErrorMessage = "Serial number is wrong length";
	    bValid = false;
	    }
	else 
	    {
            bValid = isSerialValid(value);
            if (!bValid)
                lastErrorMessage = xlatedMsg;
	    }
	field.setFieldValue(value.toUpperCase());
	// 3/7/06 changed logic - key field is enabled by default
	// can be disabled if no dongle needed

        // 5/22/07 No more key serial number with new Hasp keys
	return bValid;
	}

      /**
       * Asks the validator to display an error box showing
       * information on the last error.
       */
    public void displayLastError()
        {
        if (lastErrorMessage == null)  // no error
	    return;
	ErrorDisplay errDisplay = 
	    ApplicationManager.getErrorDisplay();
	errDisplay.showError(TextKeys.ERROR, lastErrorMessage);
	}

      /**
       * returns true if error exists that has not been reported,
       * else false.
       */
    public boolean isErrorOutstanding()
        {
	return (lastErrorMessage != null);
	}

      /**
       * Static native function that will actually call C++ code
       * to check the Serial Number.
       * @param serialNum  Serial number to check.
       * @return true if s/n is ok, else false
       */
    public static native boolean isSerialValid(String serialNum);


      /**
       * Static native function that will actually call C++ code
       * to get the license type. Based on this, we will either
       * enable or disable the key number field.
       * @param serialNum  Serial number to check.
       * @return true if software key required else false.
       */
    public static native boolean needsKey(String serialNum);



    /**
     * Based on the serial number, which implies the product
     * level, determine whether the installation needs a key
     * Public because also used by Installer.java.
     * @param sn  Serial number entered 
     * @return true if a key is needed, false if not
     */
    protected boolean needsDongle(String sn)
       {
       boolean bDongle = needsKey(sn);
       return bDongle;
       }

    }




