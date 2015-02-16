/**
 * PerformanceReporter
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 3/22/2001
 *
 * $Id: PerformanceReporter.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: PerformanceReporter.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/03/22 15:41:47  goldin
 * Add instrumentation class
 *
 */

package com.grs.dragon.ui;
import java.util.*;

/**
 * This class is a simple instrumentation class that can output
 * messages, with time stamps, to stdout. If it is instantiated
 * with bInstrumentOn set to true, it does this; otherwise, calls
 * to the report method are simply return without doing anything.*/
public class PerformanceReporter
    {
    protected boolean bInstrumentOn = false;
      
    public PerformanceReporter(boolean bOn)
        {
	bInstrumentOn = bOn;
	}

      /**
       * Send a timestamped message out to stdout if instrumentation
       * is turned on.
       */
    public void report(String message)
        {
	if (!bInstrumentOn) return;
	System.out.println(message + ": at " + new Date().getTime());
	}

      /**
       * Allow turning instrumentation on and off at different
       * points in the program.
       */
    public void setInstrumentOn(boolean flag)
        {
        bInstrumentOn = flag;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: PerformanceReporter.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
