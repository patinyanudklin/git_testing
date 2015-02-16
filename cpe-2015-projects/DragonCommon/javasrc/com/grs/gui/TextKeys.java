/**
 * TextKeys
 *
 * Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 3/16/2001
 *
 *  $Id: TextKeys.java,v 1.7 2007/01/05 07:41:58 rudahl Exp $
 *  $Log: TextKeys.java,v $
 *  Revision 1.7  2007/01/05 07:41:58  rudahl
 *  added Whatis info
 *
 *  Revision 1.6  2002/09/14 21:57:13  goldin
 *  Add new msgs
 *
 *  Revision 1.5  2002/06/27 19:29:56  goldin
 *  Add new keys for bad character errors
 *
 *  Revision 1.4  2002/03/06 20:59:36  goldin
 *  Add SAVE item
 *
 *  Revision 1.3  2002/01/24 17:08:22  goldin
 *  Added 'CANCELLED' string
 *
 *  Revision 1.2  2002/01/10 14:56:09  goldin
 *  Add new item
 *
 *  Revision 1.1  2001/11/16 16:38:20  goldin
 *  Move non-Dragon-specific files to new package
 *
 *  Revision 1.34  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.33  2001/10/17 17:49:23  goldin
 *  Begin rework of HTML reports
 *
 *  Revision 1.32  2001/10/12 14:02:06  goldin
 *  Add new callback and validator for c/edi/mod
 *
 *  Revision 1.31  2001/10/02 13:21:23  goldin
 *  Add tracing for debug purposes
 *
 *  Revision 1.30  2001/09/28 11:53:39  goldin
 *  Improve display of state during script running/pausing/waiting
 *
 *  Revision 1.29  2001/09/10 14:39:04  goldin
 *  Refine visual state during script runs
 *
 *  Revision 1.28  2001/09/05 10:46:12  goldin
 *  Add tooltips
 *
 *  Revision 1.27  2001/08/20 10:13:28  goldin
 *  Swap message and file types for RUN versus LOG
 *
 *  Revision 1.26  2001/08/06 13:02:36  goldin
 *  Add new msg keys
 *
 *  Revision 1.25  2001/07/31 09:26:03  goldin
 *  slight mod to help for VEG
 *
 *  Revision 1.24  2001/07/12 13:14:47  goldin
 *  Implement complex error message type
 *
 *  Revision 1.23  2001/06/29 17:30:16  goldin
 *  Implemented handing of state info from reply files
 *
 *  Revision 1.22  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.21  2001/05/31 17:10:53  goldin
 *  Work on problems with file dlg; esp. handling of empty drives
 *
 *  Revision 1.20  2001/05/18 12:05:41  goldin
 *  Add error logging functionality to Logger class, implement in IpcFile
 *
 *  Revision 1.19  2001/05/18 11:11:55  goldin
 *  Add validators to numeric fields
 *
 *  Revision 1.18  2001/05/14 13:47:36  goldin
 *  Add symbols for new text
 *
 *  Revision 1.17  2001/05/14 11:46:39  goldin
 *  Reformat legend/add position pspecs
 *
 *  Revision 1.16  2001/05/11 19:06:00  goldin
 *  Change IPC file format; enhance & debug tracing
 *
 *  Revision 1.15  2001/05/07 14:54:40  goldin
 *  Initial implementation of logger
 *
 *  Revision 1.14  2001/05/02 15:11:41  goldin
 *  Implement message and progress IPC file processing
 *
 *  Revision 1.13  2001/04/26 12:22:41  goldin
 *  Add string for turning on cmd line
 *
 *  Revision 1.12  2001/04/25 12:18:32  goldin
 *  Fix bug wrt border redraw; set focus to first control
 *
 *  Revision 1.11  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.10  2001/04/13 11:08:37  goldin
 *  Add opaque box, modify semantics of set default
 *
 *  Revision 1.9  2001/04/10 15:16:33  goldin
 *  Initial implementation of Font Choosing dialog
 *
 *  Revision 1.8  2001/04/10 11:18:46  goldin
 *  Fix problem with modal dialog in FileValidator; extend IntegerValidator
 *
 *  Revision 1.7  2001/04/09 11:05:42  goldin
 *  Add Logging facility logic
 *
 *  Revision 1.6  2001/04/06 18:04:25  goldin
 *  Work on resizing issues
 *
 *  Revision 1.5  2001/04/05 13:34:51  goldin
 *  Cleanup behavior, fix XML errors
 *
 *  Revision 1.4  2001/04/04 15:24:50  goldin
 *  Added partial filename filtering, validation, to file chooser
 *
 *  Revision 1.3  2001/03/26 17:32:08  goldin
 *  Further work implementing FileChooser
 *
 *  Revision 1.2  2001/03/23 17:01:51  goldin
 *  Initial implementation of file chooser
 *
 *  Revision 1.1  2001/03/22 12:57:33  goldin
 *  Implement paths panel, including initializer, callback, new path datatype
 *
 */

package com.grs.gui;

/**
 * This class defines a set of constant strings used to
 * reference translated strings. It is used by various UI
 * components that are not constructed by the XML processing.
*/
public class TextKeys
    {
    public static final String WINDOWTITLE = "%h9380.6";
    public static final String ABOUT = "%h9380.5";
    public static final String CONFIRMEXIT = "%h9360.0";
    public static final String YES = "%h10.1";
    public static final String NO = "%h10.0";
    public static final String HELP = "%h9560.1";
    public static final String STATUS = "%h8700.3";
    public static final String HISTORY = "%h9300.6";

    public static final String SELECTLANG = "%h8210.0";
    public static final String LANGCHANGE = "%h9440.0";
    public static final String MISSINGREQUIRED = "%e420";
    public static final String INVALIDVAL = "%e421";
    public static final String OK = "%h1E.0";   
    public static final String SAVE = "%h4502.0.0";   
    public static final String CANCEL = "%h1E.1";
    public static final String DETAILS = "%h9310.1"; 
    public static final String REFRESH = "%h9310.5"; 
    public static final String LOCATIONS = "%h9310.0" ; 
    public static final String ERROR = "%h7000.12";
    public static final String WARNING = "%h7000.13";
    public static final String NOTE = "%h7000.14";
    public static final String NOTFOUND_ERR = "%e404";
    public static final String EXISTS_ERR = "%e405";
    public static final String BADFILE_ERR = "%e403";
    public static final String LOGFILE = "%h9340.20";
    public static final String SPTFILE = "%h9340.7";
    public static final String OUTSIDE_RANGE = "%h1.3";
    public static final String BADINTEGER = "%e407";
    public static final String BADDOUBLE = "%e406";
    public static final String BADBOUNDS = "%h2.0";
    public static final String BADFILETYPE = "%hA.6";
    public static final String FONTNAME = "%h9310.10";
    public static final String FONTSIZE = "%h9310.11";    
    public static final String FONTSTYLE = "%h9310.12";
    public static final String SAMPLE = "%h9310.13";  
    public static final String SETASDEFAULT = "%h9310.14"; 
    public static final String OPAQUE = "%h9310.15";
    public static final String READY = "%h9360.1";
    public static final String WORKING = "%h9420.2";
    public static final String INTERRUPT = "%h9950.5";
    public static final String EXITING = "%h9420.1"; 
    public static final String CURRENT = "%e435"; 
    public static final String UNRECOGNIZEDIPCFILE = "%h9600.10"; 
    public static final String BADCHARSIPCFILE = "%h9600.11"; 
    public static final String BADCHARSEXPLAIN = "%h9600.12"; 
    public static final String STARTING = "%h9420.6";
    public static final String LOGFILEREQUIRED = "%h9.17"; 
    public static final String LOGFILEERROR = "%h9.16"; 
    public static final String NEEDBOTH = "%h9.18"; 
    public static final String SHOWCMD = "%h9300.7";  
    public static final String INVALIDSIGFILE = "%h9.19"; 
    public static final String INCONSISTENTSIGFILE = "%h9.21"; 
    public static final String MISSINGSIGNAME = "%h9.20";  
    public static final String ERRORREADINGSIGFILE = "%h9.22";
    public static final String DIFFERENTBANDS = "%h9.23";
    public static final String NODISKINDRIVE = "%hA.4"; 
    public static final String OPERATION = "%h7600.15"; 
    public static final String RESTARTSPT = "%h4550.2"; 
    public static final String CANCELSPT = "%h4550.3"; 
    public static final String PAUSESPT = "%h4550.4"; 
    public static final String RESUMESPT = "%h4550.5"; 
    public static final String NEXTSTEPSPT = "%h4550.6"; 
    public static final String SPTRUNNING = "%h9420.7"; 
    public static final String SPTWAITING = "%e426"; 
    public static final String SPTPAUSED = "%h9420.8"; 
    public static final String SPTCANCELLED = "%h9420.9"; 
    public static final String BAND = "%h3200.6.1";
    public static final String BADSCREENRES = "%e631";

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: TextKeys.java,v 1.7 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }






