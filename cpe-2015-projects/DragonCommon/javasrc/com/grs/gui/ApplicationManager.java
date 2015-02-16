/**  
 *   ApplicationManager.java
 *
 *   ~~ Copyright  2001-2014  by Goldin-Rudahl Associates
 *
 *   Created by Sally Goldin, 10/5/2001
 *   ~~ EndC
 *
 *   $Id: ApplicationManager.java,v 1.11.2.2 2014/02/21 07:55:31 rudahl Exp $
 *   $Log: ApplicationManager.java,v $
 *   Revision 1.11.2.2  2014/02/21 07:55:31  rudahl
 *   upped version number
 *
 *   Revision 1.11.2.1  2012/07/01 08:02:30  rudahl
 *   upped version number
 *
 *   Revision 1.11  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.10  2006/12/25 10:48:37  goldin
 *   Begin implementation of multi-select file control
 *
 *   Revision 1.9  2006/08/06 11:24:56  goldin
 *   Change version number for Java apps
 *
 *   Revision 1.8  2005/07/29 09:36:20  goldin
 *   Add properties for country and home directory
 *
 *   Revision 1.7  2005/07/24 13:26:07  goldin
 *   Change to 5.8
 *
 *   Revision 1.6  2005/07/24 13:24:53  goldin
 *   Add FontProcessor
 *
 *   Revision 1.7  2005/07/22 11:09:38  goldin
 *   New class for processing and indexing fonts
 *
 *   Revision 1.6  2005/06/20 07:07:25  goldin
 *   Change Version to 5.6
 *
 *   Revision 1.5  2005/04/04 08:51:50  goldin
 *   Change version to 5.5
 *
 *   Revision 1.4  2001/12/19 20:38:09  rudahl
 *   provided some crash-proof default paths
 *
 *   Revision 1.3  2001/11/30 18:03:09  goldin
 *   Moved most of the UI basic components to the com.grs.gui package
 *
 *   Revision 1.2  2001/11/16 17:29:21  goldin
 *   Move DragonFileChooser and supporting classes to new general .gui package
 *
 *   Revision 1.1  2001/11/16 16:38:20  goldin
 *   Move non-Dragon-specific files to new package
 *
 *   Revision 1.4  2001/11/05 17:53:38  rudahl
 *   added public getVersion()
 *
 *   Revision 1.3  2001/11/05 13:59:14  goldin
 *   Put UI code in a package
 *
 *   Revision 1.2  2001/10/17 10:28:47  goldin
 *   Centralize state and utility data in Application Manager
 *
 *   Revision 1.1  2001/10/05 11:04:40  goldin
 *   Add neutral class to provide critical references outside DragonUI
 *
 */

package com.grs.gui;
import com.grs.gui.*;
import java.util.*;
import java.io.*;

/**
 * This class provides an application neutral location to store
 * references to classes needed not only by DragonUI but also
 * by other classes such as the those used by the JNI-invoked
 * JVM in the viewport. It offers static methods to set and
 * get these references.
 */
public class ApplicationManager
    {
    protected final static String VERSION = "5.14";

      /**
       * Text source
       */
    protected static I18NTextSource textSource = null;

    protected static long timeOffset = 0;

    protected static String modulePrefix = "";
    protected static String readPath = "";
    protected static String writePath = "";
    protected static String tempPath = "";
    protected static String homeDirectory = "";
    protected static String country = "EN";
    protected static String logFileName = "ApplicationManager.log";
    protected static Logger errorLogger = null;
    protected static ErrorDisplay errorDisplay = null;
    protected static MessageDisplay messageDisplay = null;
    protected static boolean bLogging = false;
    protected static DragonFileChooser inFileChooser = null;
    protected static DragonFileChooser multiInFileChooser = null;
    protected static DragonFileChooser outFileChooser = null;
    protected static DragonFileChooser pathChooser = null;
    protected static DragonFontChooser fontChooser = null;
    protected static FontProcessor fontProcessor = null;      

      /**
       * Is there a message or error dialog showing.
       */
    protected static boolean bMessageDialogVisible = false;

    public static void setTextSource(I18NTextSource source)
        {
        textSource = source;
	}
    public static I18NTextSource getTextSource()
        {
	return textSource;
	}

    public static void setTimeOffset(long value)
        {
        timeOffset = value;
	}
    public static long getTimeOffset()
        {
        return timeOffset;
	}

    public static String getModulePrefix()
        {
	return modulePrefix;
	}

    public static void setModulePrefix(String value)
        {
	modulePrefix = value;
	}

    public static String getReadPath()
        {
	return readPath;
	}

    public static void setReadPath(String value)
        {
	readPath = value;
	}

    public static String getWritePath()
        {
	return writePath;
	}

    public static void setWritePath(String value)
        {
	writePath = value;
	}

    public static String getTempPath()
        {
	return tempPath;
	}

    public static void setTempPath(String value)
        {
	tempPath = value;
	}


    public static String getCountry()
        {
	return country;
	}

    public static void setCountry(String value)
        {
	country = value;
	}

    public static String getHomeDirectory()
        {
	return homeDirectory;
	}

    public static void setHomeDirectory(String value)
        {
	homeDirectory = value;
	}

    public static String getLogFileName()
        {
	return logFileName;
	}

    public static void setLogFileName(String value)
        {
	logFileName = value;
	}

    public static Logger getErrorLogger()
        {
	return errorLogger;
	}

    public static void setErrorLogger(Logger errLog)
        {
	errorLogger = errLog;
	}

    public static ErrorDisplay getErrorDisplay()
        {
	return errorDisplay;
	}

    public static void setErrorDisplay(ErrorDisplay display)
        {
	errorDisplay = display;
	}

    public static MessageDisplay getMessageDisplay()
        {
	return messageDisplay;
	}

    public static void setMessageDisplay(MessageDisplay display)
        {
	messageDisplay = display;
	}

    public static void setLogging(boolean bFlag)
        {
	bLogging = bFlag;
	}

    public static boolean isLogging()
        {
	return bLogging;
	}

    public static String getVersion()
        {
	return VERSION;
	}

    public static DragonFileChooser getInFileChooser()
        {
        return inFileChooser;
	}

    public static void setInFileChooser(DragonFileChooser chooser)
        {
        inFileChooser = chooser;
	}

    public static DragonFileChooser getMultiInFileChooser()
        {
        return multiInFileChooser;
	}

    public static void setMultiInFileChooser(DragonFileChooser chooser)
        {
        multiInFileChooser = chooser;
	}

    public static DragonFileChooser getOutFileChooser()
        {
        return outFileChooser;
	}

    public static void setOutFileChooser(DragonFileChooser chooser)
        {
        outFileChooser = chooser;
	}

    public static DragonFileChooser getPathChooser()
        {
        return pathChooser;
	}

    public static void setPathChooser(DragonFileChooser chooser)
        {
        pathChooser = chooser;
	}

    public static DragonFontChooser getFontChooser()
        {
        return fontChooser;
	}

    public static void setFontChooser(DragonFontChooser chooser)
        {
        fontChooser = chooser;
	}

    public static FontProcessor getFontProcessor()
        {
        return fontProcessor;
	}

    public static void setFontProcessor(FontProcessor processor)
        {
	fontProcessor = processor;
	}

    public static void setMessageDialogVisible(boolean flag)
        {
        bMessageDialogVisible = flag;
	}

    public static boolean isMessageDialogVisible()
        {
	return bMessageDialogVisible;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ApplicationManager.java,v 1.11.2.2 2014/02/21 07:55:31 rudahl Exp $ \n";
	}
    }


