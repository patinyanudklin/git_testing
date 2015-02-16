/* ValueLimits.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * $Id: ValueLimits.java,v 1.2 2007/01/05 07:41:58 rudahl Exp $
 * $Log: ValueLimits.java,v $
 * Revision 1.2  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.2  2001/01/17 14:18:23  goldin
 * Actually build initial trial panel from XML document
 *
 * Revision 1.1  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 *
 */

package com.grs.gui;

/**
 * Simple data structure class used to set limits for floating point
 * or integer data fields.*/
public class ValueLimits
    {
      /** 
       * minimum allowed value 
       */
    public double minValue = 0;
      /**
       * maximum allowed value 
       */
    public double maxValue = 0;
      /**
       * If true, should treat these numbers as integers not doubles
       */
    public boolean bInteger = false;

      /**
       * Constructor initializes all values.
       */
    public ValueLimits(double min, double max, boolean bInt)
        {
	minValue = min;
	maxValue = max;
	bInteger = bInt;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ValueLimits.java,v 1.2 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }
