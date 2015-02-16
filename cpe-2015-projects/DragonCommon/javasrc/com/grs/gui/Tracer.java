/**
 * Tracer
 *   
 *   Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *   Created by Sally Goldin, 6/5/2001
 *
 *  $Id: Tracer.java,v 1.4 2007/01/05 07:41:58 rudahl Exp $
 *  $Log: Tracer.java,v $
 *  Revision 1.4  2007/01/05 07:41:58  rudahl
 *  added Whatis info
 *
 *  Revision 1.3  2006/12/28 10:34:21  goldin
 *  Complete implementation of multifile selection control and file chooser
 *
 *  Revision 1.2  2006/01/14 09:24:28  goldin
 *  Add time of day to the tracing
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.5  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.4  2001/10/12 18:40:10  goldin
 *  Remove console msgs
 *
 *  Revision 1.3  2001/06/27 15:17:47  goldin
 *  Fix CalcParser bugs, table formatting
 *
 *  Revision 1.2  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.1  2001/06/05 19:36:22  goldin
 *  Add Tracer; investigate file dialog bug
 *
 *
 */

package com.grs.gui;
import java.io.*;
import java.util.*;

/**
 * This simple class provides a few static methods that will
 * output tracing information to the console or to a file.
 * The class also keeps track of whether tracing is on, and
 * whether trace info should go to a file or to the console.
 */
public class Tracer
    {
    public static final String ZEROS = "000000000000";

      /** Are we tracing? 
       */
    protected static boolean bTracing = false;

      /** Is there a trace file? 
       */
    protected static String traceFile = null;

      /**
       * Write an already composed tracing message.
       * @param message Message to write
       */
    public static void outputTraceMessage(String message)
        {
	if (!bTracing)
	    return;
        // for now, if we fail to be able to write to log,
	// just write to stdout. Later, need to have a synchronization
	// strategy.
        if (traceFile != null)
	    {
	    try 
	        {
                FileWriter writer = new FileWriter(traceFile,
						   true);  // append
	        writer.write(message);
                if (!message.endsWith("\n"))
		    writer.write("\n");
	        writer.close();
	        }
	    catch (IOException ioe)
	        {
		System.out.println("Error opening tracing file: " +
                                    ioe.getMessage());
		System.out.println(message);
		}
	    }
	else
	    {
	    System.out.println(message);
	    }
        }


      /**
       * Write a composed tracing message, prepending a timestamp
       * and the name of the component.
       * @param message Message to write
       * @param component Name of Dragon component (UI, MR, etc.)
       * @param timeOffset Current time offset value for this component
       */
    public static void outputTraceMessage(String message,
					  String component,
					  long timeOffset)
        {
	if (!bTracing)
	    return;
        StringBuffer contents = new StringBuffer();
        long localTime = new Date().getTime()/(long) 1000;
	String timeString = String.valueOf(localTime - timeOffset);
	contents.append(ZEROS.substring(0,12 - timeString.length()));
	contents.append(timeString);
	contents.append(" [" + extractTime()+ "]");
        contents.append(" " + component + " " + message);
	outputTraceMessage(contents.toString());
        }

    public static void setTracing(boolean bFlag)
        {
	bTracing = bFlag;
	}

    public static boolean isTracing()
        {
	return bTracing;
	}

    public static void setTraceFile(String filename)
        {
        traceFile = filename; // includes path
        /* delete previous version of this file if it exists */
        File tFile = new File(traceFile);
        if (tFile.exists())
            tFile.delete(); 
	}

    public static String getTraceFile()
        {
	return traceFile;
	}

   /** Extract and return the time string from a formatted date */
    public static String extractTime()
        {
        String fullDate = new Date().toString();
        String parts[] = fullDate.split("\\s");
        if (parts.length > 4)
	   return parts[3];
        else
           return " ";
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: Tracer.java,v 1.4 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }

