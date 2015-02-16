/**
 * DragonUI
 *
 * Copyright  2002-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 1/22/2001
 *
 * $Id: DragonUI.java,v 1.157 2007/02/17 10:20:57 goldin Exp $
 * $Log: DragonUI.java,v $
 * Revision 1.157  2007/02/17 10:20:57  goldin
 * Make F1 cause a focus loss so that callbacks will execute
 *
 * Revision 1.156  2007/01/08 08:00:09  goldin
 * Try to get rid of status/history button 'ghost'
 *
 * Revision 1.155  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.154  2006/12/31 09:25:07  goldin
 * Implement modifiable help display
 *
 * Revision 1.153  2006/12/28 10:34:45  goldin
 * Complete implementation of multifile selection control and file chooser
 *
 * Revision 1.152  2006/12/25 10:49:02  goldin
 * Begin implementation of multi-select file control
 *
 * Revision 1.151  2006/12/10 09:53:23  goldin
 * make status panel be the default
 *
 * Revision 1.150  2006/12/09 12:44:59  goldin
 * change help to be a popup
 *
 * Revision 1.149  2006/11/30 05:25:47  goldin
 * Modify textsource to handle multiline messages; change constructor to take a possibly null key prefix string
 *
 * Revision 1.148  2006/08/14 10:31:20  goldin
 * Complete implementation of image window for CUR
 *
 * Revision 1.147  2006/06/06 05:21:28  goldin
 * Make status area bigger and internationalize the CMD prompt
 *
 * Revision 1.146  2006/04/17 04:47:07  goldin
 * Move setupFonts method to FontProcessor itself
 *
 * Revision 1.145  2006/03/05 05:13:18  goldin
 * Fix window titles and about box
 *
 * Revision 1.144  2006/03/04 09:33:27  goldin
 * modify positioning slightly
 *
 * Revision 1.143  2006/02/11 10:08:52  goldin
 * Improve appearance of HTML tables
 *
 * Revision 1.142  2006/01/24 06:29:58  goldin
 * Don't enable the UI until we get a signal from the ScriptServer
 *
 * Revision 1.141  2006/01/21 07:53:54  goldin
 * Add code to allow UI to register itself in the global ini file
 *
 * Revision 1.140  2006/01/20 07:48:02  goldin
 * Change error reporting
 *
 * Revision 1.139  2006/01/17 10:20:29  goldin
 * Remove synchronized
 *
 * Revision 1.138  2006/01/15 13:02:53  goldin
 * Fix display on status
 *
 * Revision 1.137  2006/01/14 09:23:19  goldin
 * Improve display of history
 *
 * Revision 1.136  2005/12/31 10:28:53  goldin
 * Try to trap interrupted exception
 *
 * Revision 1.135  2005/12/20 07:46:15  goldin
 * Try to catch interruption
 *
 * Revision 1.134  2005/12/05 09:39:08  goldin
 * Working on UI hang problem - make CommandForwarder into its own thread
 *
 * Revision 1.133  2005/11/04 10:53:27  goldin
 * Working on setting and getting persistent data
 *
 * Revision 1.132  2005/10/21 14:02:44  goldin
 * Working on getting status info from persistent DB
 *
 * Revision 1.131  2005/09/16 11:50:46  goldin
 * Making color chooser work directly from the UI
 *
 * Revision 1.130  2005/09/15 08:30:09  goldin
 * Move color chooser to UI package, invoke directly from the UI
 *
 * Revision 1.129  2005/07/29 09:40:21  goldin
 * Change name of callback
 *
 * Revision 1.128  2005/07/24 13:16:40  goldin
 * Modify font handling; change dragon version
 *
 * Revision 1.129  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.128  2005/06/27 08:57:17  goldin
 * minor fix
 *
 * Revision 1.127  2005/04/04 08:51:35  goldin
 * Space before version num
 *
 * Revision 1.126  2005/03/27 10:39:11  goldin
 * Suppress calls to WinRecorder.dll for now
 *
 * Revision 1.125  2005/02/06 13:56:54  goldin
 * implement user-based customization
 *
 * Revision 1.124  2005/02/06 09:57:13  goldin
 * Add mechanism for customization
 *
 * Revision 1.123  2005/02/06 09:00:25  goldin
 * Fix javadoc warnings
 *
 * Revision 1.122  2005/02/06 06:11:14  goldin
 * Skip windows-specific calls, fix null ponter exception
 *
 * Revision 1.121  2004/12/19 12:22:09  goldin
 * Fix problem with flashing panel on  startup
 *
 * Revision 1.120  2004/12/18 11:08:32  goldin
 * Get rid of synchronized on showPanel
 *
 * Revision 1.119  2002/10/23 21:02:38  goldin
 * Try to catch problem with history/status disappearing
 *
 * Revision 1.118  2002/09/23 23:20:16  goldin
 * Add call to recordEnvironment to store OS name
 *
 * Revision 1.117  2002/09/23 19:11:15  goldin
 * Reorder Ready fn to eliminate delay in menu activity
 *
 * Revision 1.116  2002/09/20 14:21:40  goldin
 * Add code to raise UI window
 *
 * Revision 1.115  2002/09/19 22:37:21  goldin
 * Add calls to record handle in DRAGON.INI
 *
 * Revision 1.114  2002/09/18 19:26:43  goldin
 * Don't dump messages unless tracing
 *
 * Revision 1.113  2002/09/15 16:21:04  goldin
 * Move test for screen res to after completion of UI initialization
 *
 * Revision 1.112  2002/09/14 21:56:20  goldin
 * Add msg about screen size
 *
 * Revision 1.111  2002/09/10 20:08:19  goldin
 * Clear msg line with new RP
 *
 * Revision 1.110  2002/06/28 15:27:46  goldin
 * Implement 'Details' in file chooser
 *
 * Revision 1.109  2002/06/28 14:10:47  goldin
 * Provide infrastructure for usermanual help implementation
 *
 * Revision 1.108  2002/05/07 17:58:43  goldin
 * Improve echo functionality in scripts
 *
 * Revision 1.107  2002/04/30 15:43:55  goldin
 * Try to catch write lock error
 *
 * Revision 1.106  2002/04/19 22:30:20  goldin
 * Work on history positioning bug
 *
 * Revision 1.105  2002/04/17 00:53:49  goldin
 * Fix problem with dual error msg display when clicking on OK
 *
 * Revision 1.104  2002/04/16 18:14:29  goldin
 * Fix problem with history scrolling
 *
 * Revision 1.103  2002/04/02 00:09:02  goldin
 * Disable positioning if add is a replace
 *
 * Revision 1.102  2002/03/22 23:52:49  goldin
 * Fix misc. bugs
 *
 * Revision 1.101  2002/02/13 21:41:50  goldin
 * Fix problem with status display
 *
 * Revision 1.100  2002/02/07 18:44:14  goldin
 * specify versionSelector as a system property not in properties file
 *
 * Revision 1.99  2002/01/25 11:10:11  goldin
 * Add a try/catch block around the whole dragon UI
 *
 * Revision 1.98  2002/01/24 17:07:37  goldin
 * Keep track of whether last script was cancelled, to eliminate spurious 'continue' commands
 *
 * Revision 1.97  2002/01/23 16:22:41  goldin
 * improve script handling
 *
 * Revision 1.96  2002/01/22 14:54:40  goldin
 * Positioning; fix status display
 *
 * Revision 1.95  2002/01/15 18:12:59  goldin
 * Disable Cmdline when panel invoked from menu
 *
 * Revision 1.94  2002/01/10 18:17:02  goldin
 * Show UI as soon as possible
 *
 * Revision 1.93  2002/01/02 13:15:06  goldin
 * Fix bugs in commandline key handling
 *
 * Revision 1.92  2001/12/11 16:13:23  goldin
 * Add splash screen functionality
 *
 * Revision 1.91  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.90  2001/11/29 15:36:46  goldin
 * Move ConfigFileProcessor to common pkg
 *
 * Revision 1.89  2001/11/21 15:17:52  goldin
 * Make all references to getTimeOffset use ApplicationManager method
 *
 * Revision 1.88  2001/11/19 20:29:38  goldin
 * Moved IPC classes to new package
 *
 * Revision 1.87  2001/11/16 18:05:54  goldin
 * Move more classes from dragon.ui to gui package
 *
 * Revision 1.86  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.85  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.84  2001/10/22 10:58:19  goldin
 * Provide VERSIONSELECTOR functionality
 *
 * Revision 1.83  2001/10/19 16:23:12  goldin
 * Change signature of showTable method
 *
 * Revision 1.82  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.81  2001/10/08 11:56:47  goldin
 * Add code to enable/disable Save menu items
 *
 * Revision 1.80  2001/10/05 11:05:35  goldin
 * Separate Dialog from callback to allow reuse by Viewport
 *
 * Revision 1.79  2001/10/03 15:15:46  goldin
 * Modify display to index some lines
 *
 * Revision 1.78  2001/10/02 13:21:23  goldin
 * Add tracing for debug purposes
 *
 * Revision 1.77  2001/09/28 11:53:39  goldin
 * Improve display of state during script running/pausing/waiting
 *
 * Revision 1.76  2001/09/11 11:48:11  goldin
 * Fix enabling/disabling of menus during script handling
 *
 * Revision 1.75  2001/09/10 14:39:04  goldin
 * Refine visual state during script runs
 *
 * Revision 1.74  2001/09/05 15:08:53  goldin
 * Change I18NTextSource constructors
 *
 * Revision 1.73  2001/09/04 15:08:50  goldin
 * Begin implementing script control panel
 *
 * Revision 1.72  2001/08/31 14:01:03  goldin
 * Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 * Revision 1.71  2001/08/31 13:33:46  goldin
 * Implement multiple table displays, ability to kill table displays via incoming command
 *
 * Revision 1.70  2001/08/30 14:47:32  goldin
 * Begin implementing multiple table displays
 *
 * Revision 1.69  2001/08/28 11:36:55  goldin
 * Make fn keys work even when no panel visible
 *
 * Revision 1.68  2001/08/20 10:13:03  goldin
 * Disable everything until Ready
 *
 * Revision 1.67  2001/07/31 17:40:38  goldin
 * display correct range as part of message for out-of-range errors
 *
 * Revision 1.66  2001/07/18 15:25:30  goldin
 * Working to fix problems with handling of 'current' color scheme
 *
 * Revision 1.65  2001/07/12 13:14:47  goldin
 * Implement complex error message type
 *
 * Revision 1.64  2001/06/29 17:30:16  goldin
 * Implemented handing of state info from reply files
 *
 * Revision 1.63  2001/06/27 15:17:47  goldin
 * Fix CalcParser bugs, table formatting
 *
 * Revision 1.62  2001/06/19 10:40:07  goldin
 * Fix validation/focusloss loop bug
 *
 * Revision 1.61  2001/06/11 10:24:39  goldin
 * Save msg keys and dump at exit
 *
 * Revision 1.60  2001/06/08 18:12:32  goldin
 * Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 * Revision 1.59  2001/06/06 15:16:11  goldin
 * Work on cleaning up event handling in FileChooser; improve tracing
 *
 * Revision 1.58  2001/05/30 15:32:53  goldin
 * Work on getting fn keys to work in file dialog, main window w/ no RP
 *
 * Revision 1.57  2001/05/28 16:36:26  goldin
 * Debugging QueryProcessor
 *
 * Revision 1.56  2001/05/27 15:41:44  goldin
 * Additional work on query processor class and related functionality
 *
 * Revision 1.55  2001/05/22 13:15:08  goldin
 * Reorder call to show dflt panel to eliminate initial flashing
 *
 * Revision 1.54  2001/05/22 12:05:13  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 * Revision 1.53  2001/05/21 16:18:56  goldin
 * Initial implementation of table type messages
 *
 * Revision 1.52  2001/05/18 17:23:04  goldin
 * Work on improving behavior of logo on empty panel
 *
 * Revision 1.51  2001/05/18 12:05:41  goldin
 * Add error logging functionality to Logger class, implement in IpcFile
 *
 * Revision 1.50  2001/05/18 10:49:14  goldin
 * Don't exit while there are still messages to be displayed
 *
 * Revision 1.49  2001/05/16 14:00:14  goldin
 * Add reading of header block in Rpy file
 *
 * Revision 1.48  2001/05/11 19:06:00  goldin
 * Change IPC file format; enhance & debug tracing
 *
 * Revision 1.47  2001/05/10 13:14:51  goldin
 * Continue implementation of SigFile and scaling callbacks
 *
 * Revision 1.46  2001/05/09 15:16:40  goldin
 * Begin implementing signature populaing callbacks for C/EDI
 *
 * Revision 1.45  2001/05/09 09:04:56  goldin
 * Notify SS when UI appears
 *
 * Revision 1.44  2001/05/08 13:42:23  goldin
 * Began work implementing SigFileProcessor
 *
 * Revision 1.43  2001/05/08 10:14:18  goldin
 * Add class to handle commands when UI running standalone
 *
 * Revision 1.42  2001/05/07 12:06:53  goldin
 * Fix bugs in path handling
 *
 * Revision 1.41  2001/05/03 15:04:31  goldin
 * Add special file handling to command line and command forwarder
 *
 * Revision 1.40  2001/05/02 15:11:41  goldin
 * Implement message and progress IPC file processing
 *
 * Revision 1.39  2001/05/02 11:14:41  goldin
 * Implement IncomingCommandProcessor functionality
 *
 * Revision 1.38  2001/04/27 19:42:24  goldin
 * Initial implementation of class to handle commands coming into the UI
 *
 * Revision 1.37  2001/04/27 11:29:00  goldin
 * Continue implementation of interprocess communication and command handling
 *
 * Revision 1.36  2001/04/26 15:45:32  goldin
 * Work on history display for command line and response panels
 *
 * Revision 1.35  2001/04/26 12:23:34  goldin
 * Implement bigHelp panels
 *
 * Revision 1.34  2001/04/25 15:36:50  goldin
 * began implementation of command line
 *
 * Revision 1.33  2001/04/25 12:18:32  goldin
 * Fix bug wrt border redraw; set focus to first control
 *
 * Revision 1.32  2001/04/25 10:51:02  goldin
 * Add function key handling
 *
 * Revision 1.31  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.30  2001/04/17 19:06:21  goldin
 * Fix out of bounds error
 *
 * Revision 1.29  2001/04/10 15:16:33  goldin
 * Initial implementation of Font Choosing dialog
 *
 * Revision 1.28  2001/04/09 11:33:26  goldin
 * Make it possible to turn help editing on and off via properties file
 *
 * Revision 1.27  2001/04/09 11:05:42  goldin
 * Add Logging facility logic
 *
 * Revision 1.26  2001/04/06 18:04:25  goldin
 * Work on resizing issues
 *
 * Revision 1.25  2001/04/05 13:34:51  goldin
 * Cleanup behavior, fix XML errors
 *
 * Revision 1.24  2001/03/26 18:50:06  goldin
 * Shrink the main window
 *
 * Revision 1.23  2001/03/26 17:32:08  goldin
 * Further work implementing FileChooser
 *
 * Revision 1.22  2001/03/23 17:01:51  goldin
 * Initial implementation of file chooser
 *
 * Revision 1.21  2001/03/22 15:41:47  goldin
 * Add instrumentation class
 *
 * Revision 1.20  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.19  2001/03/21 15:02:39  goldin
 * display logo in empty panel
 *
 * Revision 1.18  2001/03/21 14:54:16  goldin
 * Split RP.XML into separate menu and panel files; address via new properties file.
 *
 * Revision 1.17  2001/03/21 13:05:39  goldin
 * Add language selection and config file processing functionality
 *
 * Revision 1.16  2001/03/20 18:04:15  goldin
 * Implement tabbed panes, clean up menu help:
 *
 * Revision 1.15  2001/03/20 13:31:38  goldin
 * Implement new sizing strategy
 *
 * Revision 1.14  2001/03/20 10:48:08  goldin
 * Checkpoint before changing layout strategy
 *
 * Revision 1.13  2001/03/16 19:23:46  goldin
 * Added fixed length option for DTextField and DFileField; added callbacks to menu items
 *
 * Revision 1.12  2001/03/16 14:36:08  goldin
 * Add internationalization to exit dialog
 *
 * Revision 1.11  2001/03/14 16:39:31  goldin
 * Implemented small panel size, fixed resize listener to allow them
 *
 * Revision 1.10  2001/03/03 19:56:58  goldin
 * Fine tuning screen layout and appearance
 *
 * Revision 1.9  2001/02/28 16:24:29  goldin
 * implementing defaults, enhancements to help editor
 *
 * Revision 1.8  2001/02/28 11:50:12  goldin
 * Extend mouse handling to checkbuttons and push buttons
 *
 * Revision 1.7  2001/02/20 18:39:13  goldin
 * Add callback handling
 *
 * Revision 1.6  2001/02/08 16:14:39  goldin
 * Added HelpEditor capability
 *
 * Revision 1.5  2001/02/07 20:41:06  goldin
 * Implemented actual reading of text help file
 *
 * Revision 1.4  2001/01/29 15:19:32  goldin
 * Continued work on UI
 *
 * Revision 1.3  2001/01/29 12:23:28  goldin
 * Put official UI file in CVS, also new class to control resizing
 *
 * Revision 1.2  2001/01/25 20:16:19  goldin
 * Continued work on layout and XML parsing
 *
 * Revision 1.1  2001/01/22 16:14:26  goldin
 * Changes to parse actual generated XML file
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import com.grs.dragon.ipc.*;
import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;

/**
 * This is the top-level class for the new DRAGON UI. It
 * provides the DRAGON menu, area for response panels, and 
 * history/status/help area, as well as a message area.
 * It invokes the XmlToUiBuilder to build the UI and then
 * holds onto the master hash table of response panels to 
 * invoke as necessary.*/
public class DragonUI extends JFrame implements ActionListener,
                                                KeyListener,
                                                ComponentListener,
                                                DragonApp
    {
    protected final static String NO_STATUS = "No status";

    protected final static String EMPTY_HTML_DOCUMENT =
       "<html><head></head><body></body></html>";
    protected final static int MAX_TABLE_DISPLAY = 4;
      /**
       * Reference to object which will output performance
       * info.*/
    public static PerformanceReporter reporter = null;

      /**
       * Reference to text source object.
       * We need to make it static so that it can be accessed
       * by callback classes.*/
    public static I18NTextSource textSource = null;

      /**
       * Reference to config file processor object.
       * We need to make it static so that it can be accessed
       * by callback classes.*/
    public static ConfigFileProcessor cfgProcessor = null;

      /**
       * Reference to color chooser object.
       * We need to make it static so that it can be accessed
       * by callback classes.*/
    public static ColorChooser colorChooser = null;


      /**
       * Reference to latest used SigFileProcessor
       */
    protected SigFileProcessor currentSigProcessor = null;

      /**
       * Static reference to currently executing DragonUI. This a real
       * kludge, but some classes have no other way of getting at
       * the parent application.
       */
    public static DragonUI currentApplication = null;

      /**
       * Current directory in which application is running.
       */
    public static String homeDirectory = null;

      /**
       * Three file choosers, for input files, output files, 
       * and paths.*/
    protected DragonFileChooser inFileChooser = null;
    protected DragonFileChooser outFileChooser = null;
    protected DragonFileChooser pathChooser = null;
    protected DragonFileChooser multiInFileChooser = null;

      /**
       * And one font chooser*/
    protected DragonFontChooser fontChooser = null;
    protected ErrorDisplay errorDisplay = null;
    protected UiMessageDisplay messageDisplay = null;
    protected TableDisplay tableDisplayList[] = null;
    protected int lastTableDisplayedIndex = 0;
    protected DImageHeader memoryHeader = null;
    protected StatusManager statusManager = null;

    protected ScriptControlPanel scriptCtrl = null;
      /**
       * Language to use in this UI.
       */
    protected String language = "EN";

      /**
       * Table of response panels and menus, populated by XML
       * parser.
       */
    protected Hashtable masterTable = new Hashtable(200);

      /**
       * Table of popup dialogs. Indexed by the panel's ID.
       */
    protected Hashtable dialogTable = new Hashtable(16);


      /**
       * Minimum size allowed for panel.
       */
    protected Dimension minSize = new Dimension(680, 600); 

      /** 
       * Desired dimensions of response panels.
       */
    protected Dimension rpSize = new Dimension(680, 380);

      /**
       * Size for big help area
       */
    protected Dimension bigHelpDim = new Dimension(670,230);

      /**
       * Size for normal help area
       */
    protected Dimension helpDim = new Dimension(670,180);


      /**
       * Area of the UI where response panels will show up.
       */
    protected JPanel rpArea = null;

      /**
       * Dummy area to avoid the flashing.
       */
    protected JPanel dummyRpArea = null;


      /**
       * Top part of the UI. Needs to be classwide because
       * we add and remove the command line from it.
       */
    protected JPanel topPanel = null;
   
      /**
       * Inner panel with cardlayout so we can first show the
       * dummy rpArea then the real one.
       */
    protected JPanel switchPanel = null;

      /**
       * Bottom part of UI. Needs to be classwide because it
       * can change if a panel needs a bigger help area.
       */
    protected JPanel bottomPanel = null;

      /**
       * Text area for showing help etc.
       */
    protected JEditorPane helpArea = null;
    
      /**
       * Scroll Pane in which help area sits - so we can manually
       * set the scrollbar to the top after adding help.
       */
    protected JScrollPane helpPane = null;

      /**
       * Command line entry area.
       */
    protected CommandLine commandLine = null;

      /**
       * Message area at bottom of the UI.
       */
    protected JTextField messageArea = null;
    protected JTextField readyArea = null;
    protected JTextField timeArea = null;


      /**
       * Panel ID of currently displayed panel.
       */
    protected String currentPanelID = null;

      /**
       * Buttons for radio panel to select content of text area.
       */
    protected JPanel buttonPanel = null;
	//protected JRadioButton helpBtn;
    protected JRadioButton statusBtn;
    protected JRadioButton historyBtn;
    protected JRadioButton selectedRadioBtn = null;

      /**
       * Button to turn on and off the command line.
       */
    protected JCheckBox showCmdLineBtn = null;

      /**
       * Temporary UI infrastructure for showing keys.
       */
    protected JCheckBox showKeysBtn = null;
    protected boolean bShowKeys = false;
    protected HelpEditor keyDisplay = null;

      /**
       * Cardlayout for normal response panels
       */
    protected CardLayout cardLayout = new CardLayout();

      /**
       * Cardlayout for switch panel
       */ 
    protected CardLayout switchLayout = new CardLayout();

      /**
       * Class to handle help display in response to mouse enter
       * events.*/
    protected HelpDisplayListener helpDisplayListener;

      /**
       * Dummy field that can be used by menu items to execute
       * callbacks. Initialized by the constructor.*/
    protected DFixedText dummyField = null;
 
      /**
       * If true, we just displayed a new panel.
       * This is used to disable auto-resizing to minimum size by
       * the ResizeListener class.
       */
    protected boolean bNewPanel = false;

      /**
       * Is the command line visible?
       */
    protected boolean bCmdLineVisible = false;
      /**
       * Is the script control panel visible?
       */
    protected boolean bScriptControlVisible = false;

      /**
       * Have we received the enable signal from the
       * script server?
       */
    protected boolean bEnableSignalled = false;

    protected static String READY_STRING = null;
    protected static String WORKING_STRING = null;
    protected static String STARTING_STRING = null;
    protected static String EXITING_STRING = null;
    protected static String SCRIPT_STRING = null;
    protected static String WAITING_STRING = null;
    protected static String CANCELLED_STRING = null;
    protected static String PAUSED_STRING = null;

      /** Info needed for IpcFile processing
       */
      /** Master time offset for the UI.
       */
    protected long timeOffset = 0;

      /**
       * Data to control command logging.
       */
    protected boolean bLogging = false;
    protected String logFile = null;

      /**
       * reference to error logging class instance.
       */
    protected Logger errorLogger = null;
      
      /** Classes to handle IpcFile processing
       */
    public static CommandForwarder commandForwarder = null;
    protected UiIncomingCommandProcessor incomingCommandProcessor = null;
    protected ProgressDetector progressDetector = null;
    protected UiMessageDetector messageDetector = null;
    protected ServerQueryProcessor serverQueryProcessor = null;

      /**
       * True if the app is fully initialized
       */
    protected boolean bInitialized = false;

      /**
       * Are we in the process of exiting
       */
    protected boolean bExiting = false;

      /**
       * True if we running as a restricted version (demo or unauthorized)
       */
    protected boolean bRestrictedVersion = false;

      /** 
       * Used to keep empty panel the same size.
       */
    protected DragonPanel emptyPanel = null;
    protected Dimension emptyPanelSize = null;

      /** 
       * Keep last status, to determine whether we
       * should redisplay.
       */
    protected String lastStatus = "dummy";

    protected boolean bIsWindows = false;
    /** Common hash tables used to share intermediate results
     * across XML files.
     */
    protected Hashtable menuTable = new Hashtable();
    protected Hashtable panelTable = new Hashtable();
      //********************************************************
      /**
       * Constructor creates and displays the UI
       */
    public DragonUI(String[] menuXmlFileNames, 
                    String[] panelXmlFileNames,
		    boolean bTrace, boolean bSetTrace)
        {
	super("DRAGON/ips v5.8");
	Tracer.setTracing(bSetTrace);
        ApplicationManager.setModulePrefix("UI");
	ApplicationManager.setHomeDirectory(homeDirectory);
        cfgProcessor = new ConfigFileProcessor(homeDirectory);
	if (cfgProcessor.isInitialized())
	    { 
	    language = cfgProcessor.getCountry();
            String helpDelay = cfgProcessor.getHelpDelay();
	    if (helpDelay != null)
                HelpDisplayListener.setHelpDelay(Integer.parseInt(helpDelay));
	    ApplicationManager.setCountry(language);
            ApplicationManager.setReadPath(cfgProcessor.getDpath());
            ApplicationManager.setWritePath(cfgProcessor.getWpath());
            ApplicationManager.setTempPath(cfgProcessor.getKpath());
	    }
	else 
   	    {
	    System.exit(0);
	    }
	textSource = new I18NTextSource(language,homeDirectory,"%");
	if (!textSource.isInitialized())
	    {
	    System.exit(0);
	    }
        ApplicationManager.setTextSource(textSource);

        String OS = System.getProperty("os.name");
	//System.out.println("The operating system is " + OS);
	if (OS.toUpperCase().indexOf("WIN") >= 0)
	    {
	    bIsWindows = true;
	    }
	FontProcessor fontProc = new FontProcessor(bIsWindows);
	ApplicationManager.setFontProcessor(fontProc);
	fontProc.setupFonts(language,this);

	String windowTitle = AboutDialog.uiTitle +  " V" +
	                ApplicationManager.getVersion();

	setTitle(windowTitle);

	errorDisplay = new UiErrorDisplay(textSource,this);
        ApplicationManager.setErrorDisplay(errorDisplay);
	messageDisplay = new UiMessageDisplay(textSource,this);
        ApplicationManager.setMessageDisplay(messageDisplay);
        tableDisplayList = new TableDisplay[MAX_TABLE_DISPLAY];
        for (int i = 0; i < MAX_TABLE_DISPLAY; i++)
	     {
             tableDisplayList[i] = new TableDisplay(textSource,this);
	     tableDisplayList[i].setIndex(i);
	     }
	statusManager = new StatusManager(this);
        // create a class instance to process commands
	// create other IPC classes if we are not running standalone
        if (cfgProcessor.isStandAlone())
	    {
            commandForwarder = new NullCommandForwarder(this,
						cfgProcessor.getKpath());
	    commandForwarder.start();
	    messageDetector = new UiMessageDetector(this);
            }
        else
	    {
            commandForwarder = new CommandForwarder(this,
						cfgProcessor.getKpath());
	    commandForwarder.start();
	    incomingCommandProcessor = new UiIncomingCommandProcessor(this);
	    serverQueryProcessor = new ServerQueryProcessor(this);
	    progressDetector = new ProgressDetector(this);
	    messageDetector = new UiMessageDetector(this);
	    }
        errorLogger = new Logger(cfgProcessor.getSpath() +
                                 File.separator + "DragErr.log");
        ApplicationManager.setErrorLogger(errorLogger);

	/* Create the color chooser. We will now invoke this
	 * directly from the UI with no intervention from
	 * the viewport.
	 */
	colorChooser = new ColorChooser(this,textSource);

	// the forwarder, at least, must be created before the
	// the call to createUI, b/c it is passed to the command line in
	// its constructor
	// use the dummy field to transmit component info callbacks
	dummyField = new DFixedText("dummy","dummy");
	dummyField.setParentComponent(this);
	createUI();
	initMenus(menuXmlFileNames,bTrace);
	WindowMonitor myMonitor = new WindowMonitor(this);
	setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
	addWindowListener(myMonitor);
	setIconImage(new ImageIcon("dragexec.gif").getImage());
	showDefaultPanel();
	pack();
	positionWindow();
	show();
        PlatformSpecific.recordWindowByTitle(windowTitle,"UI");
        if (!cfgProcessor.isStandAlone())
	   {
	   commandForwarder.sendCommandToServer("START");
	   }
	setWaitCursor(this);
        setReady(false);
        setMenuBarEnabled(false);
	initPanels(panelXmlFileNames,bTrace);
        currentApplication = this;
        if (cfgProcessor.isStandAlone())
	    {
            bEnableSignalled = true;
	    setReady(true);
	    }
	else   // if we are not running standalone, wait to hear from
	       // server, with a reply, before setting to ready.
	    {
	    commandForwarder.sendCommandToServer("READY");
	    }
	// Before we go any further, check to see if the
	// screen size is large enough
	if (!screenSizeOk())
	    {
	    commandForwarder.sendCommandToServer(
			  "-ABEXIT");
	    System.exit(0);
	    }
	// get product info from properties file and save
	String versionSelector = System.getProperty("versionSelector");

        if ((versionSelector != null) &&
            ((versionSelector.compareToIgnoreCase("DEMO") == 0) ||
	     (versionSelector.compareToIgnoreCase("UNAUTHORIZED") == 0)))
	     bRestrictedVersion = true;
	}
      
      /**
       * Factorization of constructor. Reads the cfg file,
       * looks for a positioning specification and uses
       * that to determine the initial window location. If
       * there is none, uses a default.
       */
   protected void positionWindow()
       {
       int xPos = 10;
       int yPos = 10;
       String initPos = cfgProcessor.getAttributeValue("DRAGONUI");
       if (initPos != null)
	   {
	   StringTokenizer tokenizer = new StringTokenizer(initPos,",");
	   String value = tokenizer.nextToken();
	   if (value != null)
	       {
	       try 
		   {
		   xPos = Integer.parseInt(value);
		   }
	       catch (NumberFormatException nfe)
		   {
		   }
	       }
	   value = tokenizer.nextToken();
	   if (value != null)
	       {
	       try 
		   {
		   yPos = Integer.parseInt(value);
		   }
	       catch (NumberFormatException nfe)
		   {
		   }
	       }

	   }
       if (xPos > 50)
	   xPos = 50;
       if (yPos > 50)
	   yPos = 50;
       Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
       int newX = (screen.width * xPos)/100;
       int newY = (screen.height *yPos)/100;
       setLocation(newX,newY);
       }


      /**
       * Check to see if screen is large enough for the UI.
       * If too small, puts up a warning.
       * @return true if screen 1024 or bigger, else false.
       */
   protected boolean screenSizeOk()
       {
       boolean bOk = true;
       Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
       if ((dim.width < 1024) || (dim.height < 700))
	   {
	   bOk = false;
   	   String message = 
               DragonUI.textSource.getI18NText(TextKeys.BADSCREENRES,
	       "Screen resolution must be at least 1024 x 700 - exiting");
	   JOptionPane.showMessageDialog(this,message," ",
					 JOptionPane.WARNING_MESSAGE);
	   }
       return bOk;
       }

      /**
       * Creates the frame structure for the UI, where response panels
       * will be displayed.
       */
   protected void createUI()
       {
       topPanel = new JPanel(new BorderLayout()); 
       switchPanel = new JPanel(switchLayout);
       rpArea = new JPanel(cardLayout);
       rpArea.setPreferredSize(rpSize);

       dummyRpArea = new JPanel(new BorderLayout());
       dummyRpArea.setPreferredSize(rpSize);
       switchPanel.add(dummyRpArea,"DUMMY");
       switchPanel.add(rpArea,"REAL");
       switchLayout.show(switchPanel,"DUMMY");

       //topPanel.add(rpArea, BorderLayout.CENTER);

       topPanel.add(switchPanel, BorderLayout.CENTER);

       commandLine = new CommandLine(commandForwarder,this);
       commandLine.addKeyListener(this);
       // create the command line, but do not add it.
       // topPanel.add(commandLine, BorderLayout.SOUTH);
       scriptCtrl = new ScriptControlPanel(commandForwarder,this);
       // create the script control panel but do not add
       getContentPane().add(topPanel,BorderLayout.NORTH);

       bottomPanel = new JPanel(new BorderLayout());
       bottomPanel.setBorder(BorderFactory.createEtchedBorder());
       buttonPanel = new JPanel(new FlowLayout());
       ButtonGroup displayGroup = new ButtonGroup();
       String helpString = 
              textSource.getI18NText(TextKeys.HELP,"HELP");
       //helpBtn = new JRadioButton(helpString);  // needs I18N
       //buttonPanel.add(helpBtn);
       //displayGroup.add(helpBtn);
       //helpBtn.addActionListener(this);
       //helpBtn.setSelected(true);
       //selectedRadioBtn = helpBtn;
       String statusString = 
              textSource.getI18NText(TextKeys.STATUS,"STATUS");
       statusBtn = new JRadioButton(statusString);
       buttonPanel.add(statusBtn);
       displayGroup.add(statusBtn);
       statusBtn.addActionListener(this);
       statusBtn.setSelected(true);
       selectedRadioBtn = statusBtn;

       String historyString = 
              textSource.getI18NText(TextKeys.HISTORY,"HISTORY");
       historyBtn = new JRadioButton(historyString);
       buttonPanel.add(historyBtn);
       displayGroup.add(historyBtn);
       historyBtn.addActionListener(this);


       String showCmdString = textSource.getI18NText(TextKeys.SHOWCMD,
						     "SHOW CMD LINE");
       showCmdLineBtn = new JCheckBox(showCmdString);
       buttonPanel.add(showCmdLineBtn);
       showCmdLineBtn.addActionListener(this);

       bottomPanel.add(buttonPanel, BorderLayout.NORTH);
       helpArea = new JEditorPane();
       helpArea.setContentType("text/html");
       helpArea.setEditable(false);
       //helpArea.addComponentListener(this); 
       // this caused the scroll bar for history to stop working...

       helpPane = new JScrollPane(helpArea);
       bottomPanel.add(helpPane, BorderLayout.CENTER);
       bottomPanel.setPreferredSize(helpDim);
       JPanel msgPanel = new JPanel(new BorderLayout(2,2));
       readyArea = new JTextField(20);
       readyArea.setEditable(false);
       msgPanel.add(readyArea,BorderLayout.WEST);
       messageArea = new JTextField(60);
       messageArea.setEditable(false);
       msgPanel.add(messageArea, BorderLayout.CENTER);
       //timeArea = new JTextField(7);
       //timeArea.setEditable(false);
       //msgPanel.add(timeArea, BorderLayout.EAST);

       // create empty panel
       emptyPanel = new DragonPanel("^EMPTY");
       emptyPanel.setPrimary(false); // so we won't have a title
       emptyPanelSize = new Dimension(rpSize.width,rpSize.height);
       emptyPanel.setPreferredSize(emptyPanelSize);
       emptyPanel.doPanelLayout();
       emptyPanel.add(new JLabel(new ImageIcon("draglogo.gif")),
		      BorderLayout.CENTER);
       
       rpArea.add(emptyPanel,emptyPanel.getName());
       showPanel(emptyPanel);
       masterTable.put(emptyPanel.getName(), emptyPanel);

       commandLine.setParentPanel(emptyPanel);
       bottomPanel.add(msgPanel, BorderLayout.SOUTH);
       getContentPane().add(bottomPanel, BorderLayout.CENTER);
       getPreferredSize().width = rpSize.width;


       helpDisplayListener = new HelpDisplayListener(this);
       inFileChooser = new DragonFileChooser(this,textSource,
					     false,true,false);
       ApplicationManager.setInFileChooser(inFileChooser);
       outFileChooser = new DragonFileChooser(this,textSource,
					     false,false,false);
       ApplicationManager.setOutFileChooser(outFileChooser);
       pathChooser = new DragonFileChooser(this,textSource,
					     true,false,false);
       ApplicationManager.setPathChooser(pathChooser);
       multiInFileChooser = new DragonFileChooser(this,textSource,
					     false,true,true);
       ApplicationManager.setMultiInFileChooser(multiInFileChooser);
       fontChooser = new DragonFontChooser(this,textSource);
       ApplicationManager.setFontChooser(fontChooser);
       DFileType.IMAGE.setDetailCallback(new ImgFileDetailCallback());
       }

     
      /**
       * Initializes the menu system by reading the XML file(s).
       * @param menuFileNames - Array of XML files, defining the
       *                      the primary menu plus user addons
       * @param bTrace - If true, trace while doing Xml parsing, for
       *                 debugging file errors.
       * @return true if successful, false if some error
       */
   public boolean initMenus(String[] menuFileNames, boolean bTrace)
       {
       reporter.report("Starting initMenus");
       String versionSelector = "default";
       boolean bOk = true;
       ResourceBundle bundle = ResourceBundle.getBundle("DragonUI");
       try
	    {
	    // Create Editor for showing keys 
	    // We must create this object AFTER the text source has been
	    // initialized.
            String showHelpEditor = bundle.getString("showHelpEditor");
            String allowHelpEdit  = bundle.getString("allowHelpEdit");
	    if ((showHelpEditor != null) &&
                (showHelpEditor.compareTo("true") == 0))
	        {
                keyDisplay = new HelpEditor(this);
	        showKeysBtn = new JCheckBox("Show text keys");
	        buttonPanel.add(showKeysBtn);
	        showKeysBtn.addActionListener(this);
                if ((allowHelpEdit != null) &&
		    (allowHelpEdit.compareTo("true") == 0))
		     keyDisplay.setEditable(true);
		else 
		     keyDisplay.setEditable(false);
		}
            String temp  = System.getProperty("versionSelector");
            if (temp != null)
	        versionSelector = temp;
	    }
       catch (MissingResourceException e)
	    {
	      // don't do anything - these resources are not required
	    }
       /* Iterate through the menu files and read each one. */
       for (int fileIdx=0; fileIdx < menuFileNames.length; fileIdx++)
	    {
	    String xmlFileName = menuFileNames[fileIdx];
	    try 
	        {
		XmlToUiBuilder parser = new XmlToUiBuilder(xmlFileName,null,
							   textSource, 
							   masterTable,
							   versionSelector,
							   homeDirectory);
		parser.setSharedTables(menuTable,panelTable);
		if (bTrace)
		    parser.setTracing(true);
		InputStreamReader reader = parser.getXmlReader();
		if (reader != null)
		    {
		    parser.parse(reader);
		    }
		}
	    catch (Exception e)
	        {
		e.printStackTrace();
		bOk = false;
		}
	    }
       Collection menus = masterTable.values();
       Iterator it = menus.iterator();
       JMenuBar bar = null;
       int maxMenuCount = 0;
       while (it.hasNext())
	   {
	   Object obj = it.next();
	   JMenuBar tempBar = null;
	   if (obj instanceof JMenuBar)
	       {
	       tempBar = (JMenuBar) obj;
               if (tempBar.getMenuCount() > maxMenuCount)
		  {
	          bar = tempBar;
		  maxMenuCount = tempBar.getMenuCount();
		  }
	       }
	   }
       if (bar == null)
	   {
	   bar = new JMenuBar();
           }
       setJMenuBar(bar);
       // associate the main UI as action listener for all
       // components
       setActionListener(bar);
       setMouseListener(bar,helpDisplayListener);

       reporter.report("Ending initMenus");
       return bOk;
       }

    /**
     * Initializes the response panels, from a separate
     * XML file.
     * @param panelFileNames - Array of XML files, defining the
     *                      the primary set of panels plus user addons
     * @param bTrace - If true, trace while doing Xml parsing, for
     *                 debugging file errors.
     * @return true if successful, else false.
     */
   public boolean initPanels(String[] panelFileNames, boolean bTrace)
       {
       reporter.report("Starting initPanels");
       boolean bOk = true;
       /* Iterate through the panel files and read each one. */
       for (int fileIdx=0; fileIdx < panelFileNames.length; fileIdx++)
	   {
	   String xmlFileName = panelFileNames[fileIdx];
	   try 
	      {
	      XmlToUiBuilder parser = new XmlToUiBuilder(xmlFileName,null,
						      textSource, masterTable,
						      "default",
						      homeDirectory);
	      parser.setSharedTables(menuTable,panelTable);
	      if (bTrace)
		parser.setTracing(true);
	      InputStreamReader reader = parser.getXmlReader();
	      if (reader != null)
		  {
		  parser.parse(parser.getXmlReader());
		  }
	      }
	   catch (Exception e)
	      {
	      e.printStackTrace();
	      bOk = false;
	      }
	   }
       Collection panels = masterTable.values();
       Iterator it = panels.iterator();
       while (it.hasNext())
	   {
	   Object obj = it.next();
	   if (obj instanceof DragonPanel)
	       {
	       // we know that there is at least one
	       DragonPanel dPanel = (DragonPanel) obj;
	       dPanel.setPanelTable(masterTable);
	       dPanel.setDialogTable(dialogTable);
	       if (dPanel.isPopup())
		   {
		   JDialog dlg = new JDialog(this,dPanel.getTitle());
		   dlg.getContentPane().add(dPanel);
 		   dialogTable.put(dPanel.getName(),dlg);
                   dPanel.setPopupDialog(dlg);
		   dlg.setSize(dPanel.getPreferredSize());
		   }
               else if (dPanel.getName().equals("DummyPanel"))
		   {
                   processDummyPanel(dPanel);
                   }
	       else
		   {
		   dPanel.setPanelSize(rpSize);
		   dPanel.doPanelLayout();
		   rpArea.add(dPanel,dPanel.getName());
	           }
	       // have the panel set a mouse enter listener on all its
	       // components.
	       dPanel.setMouseListener(helpDisplayListener);
	       // ditto for special key listener - to handle Dragon
	       // specific keys
	       dPanel.setKeyListener(this);
	       dPanel.setMemoryFilter(statusManager);
	       }
	   }
       showPanel(emptyPanel);
       switchLayout.show(switchPanel,"REAL");
       reporter.report("Ending initPanels");
       return bOk;
       }

      /**
       * Factorization. This is something of a kludge to allow
       * us to display internationalized help for the radio and
       * check buttons controlling the status display etc.
       * These buttons are not DragonFields. However, we create a
       * set of dummy fields with the right help in PANEL.XML, and
       * associate them with the DummyPanel. In this method, we
       * retrieve them and use them as client properties on the
       * buttons/checkbox. Then we can use our standard HelpDisplayListener
       * to display their help messages (retrieved from the dummy
       * fields.
       */
    protected void processDummyPanel(DragonPanel dPanel)
       {
       DragonField fld = dPanel.getField("^STAT");
       if (fld != null)
	   {
           statusBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   statusBtn.addMouseListener(helpDisplayListener);
 	   statusBtn.addKeyListener(fld);
	   }
       fld = dPanel.getField("^HIST");
       if (fld != null)
	   {
           historyBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   historyBtn.addMouseListener(helpDisplayListener);
 	   historyBtn.addKeyListener(fld);
	   }
       /** 
       fld = dPanel.getField("^HELP");
       if (fld != null)
	   {
           helpBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   helpBtn.addMouseListener(helpDisplayListener);
 	   helpBtn.addKeyListener(fld);
	   }
       **/
       fld = dPanel.getField("^CMDLN");
       if (fld != null)
	   {
           showCmdLineBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   showCmdLineBtn.addMouseListener(helpDisplayListener);
 	   showCmdLineBtn.addKeyListener(fld);
	   }
       fld = dPanel.getField("^RESTARTSPT");
       if (fld != null)
	   {
           scriptCtrl.restartBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   scriptCtrl.restartBtn.addMouseListener(helpDisplayListener);
 	   scriptCtrl.restartBtn.addKeyListener(fld);
	   }
       fld = dPanel.getField("^CANCELSPT");
       if (fld != null)
	   {
           scriptCtrl.cancelBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   scriptCtrl.cancelBtn.addMouseListener(helpDisplayListener);
 	   scriptCtrl.cancelBtn.addKeyListener(fld);
	   }
       fld = dPanel.getField("^PAUSESPT");
       if (fld != null)
	   {
           scriptCtrl.pauseBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   scriptCtrl.pauseBtn.addMouseListener(helpDisplayListener);
 	   scriptCtrl.pauseBtn.addKeyListener(fld);
	   }
       fld = dPanel.getField("^RESUMESPT");
       if (fld != null)
	   {
           scriptCtrl.resumeBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   scriptCtrl.resumeBtn.addMouseListener(helpDisplayListener);
 	   scriptCtrl.resumeBtn.addKeyListener(fld);
	   }
       fld = dPanel.getField("^NEXTSPT");
       if (fld != null)
	   {
           scriptCtrl.nextStepBtn.putClientProperty(DragonField.PARENT_FIELD,fld);
	   scriptCtrl.nextStepBtn.addMouseListener(helpDisplayListener);
 	   scriptCtrl.nextStepBtn.addKeyListener(fld);
	   }
       }

      /**
       * Factorization of initUI. Traverses the entire menu
       * and associates the current DragonUI instance as action
       * listener for each menu item. This method is called
       * recursively.
       * @param element Top level menu bar for application.
       *                or current submenu.
       */
    protected void setActionListener(MenuElement element)
        {
	if (element instanceof DragonMenuItem)
	    {
	    // we know that everything that implements DragonMenuItem
	    // is in fact a JMenuItem subclass.
	    JMenuItem item = (JMenuItem) element;
	    item.addActionListener(this);
	    return;
	    }
	MenuElement[] subElems = element.getSubElements();
	if (subElems != null) 
	    {
	    for (int i = 0; i < subElems.length; i++)
	         {
		 setActionListener(subElems[i]);
		 }
	    }
	return;
	}

      /**
       * Factorization of initUI. Traverses the entire menu
       * and associates the passed mouse listener instance as mouse
       * listener for each menu item. This method is called
       * recursively.
       * @param element Top level menu bar for application.
       *            or current submenu.
       * @param listener Mouse listener to associate with the menus
       */
    protected void setMouseListener(MenuElement element,MouseListener listener)
        {
	if (element instanceof DragonMenuItem)
	    {
	    JMenuItem item = (JMenuItem) element;
	    item.addMouseListener(listener);
	    return;
	    }
        else if (element instanceof DragonMenu)
	    {
            DragonMenu menu = (DragonMenu) element;
	    menu.addMouseListener(listener);
	    }
	MenuElement[] subElems = element.getSubElements();
	if (subElems != null) 
	    {
	    for (int i = 0; i < subElems.length; i++)
	         {
		 setMouseListener(subElems[i],listener);
		 }
	    }
	return;
	}

      /**
       * Recursive method to looks for a menu item with a specified ID
       * @param element Top level menu bar for application.
       *            or current submenu.
       * @param id   ID of menu item we are looking for.
       * @return Desired menu item, or null if not found so far
       */
    public DragonMenuItem getMenuItem(MenuElement element,
					 String id)
        {
	DragonMenuItem desiredItem = null;
	if (element instanceof DragonMenuItem)
	    {
	    DragonMenuItem item = (DragonMenuItem) element;
	    if (item.getName().equals(id))
                {
                desiredItem = item;
		return desiredItem;
	        } 
	    }
        else 
	    {
	    Component[] subElems = null;
            if (element instanceof DragonMenu)
	         {
	         subElems = ((JMenu)element).getMenuComponents();
		 }
	    else if (element instanceof JMenuBar)
	         {
	         subElems = ((JMenuBar)element).getComponents();
		 }
	    if (subElems != null) 
	        {
	        for (int i = 0; (i < subElems.length) && 
		                (desiredItem == null);i++)
	           {
		   desiredItem = getMenuItem((MenuElement) subElems[i],id);
		   }
		}
	    }
	return desiredItem;
	}

      /**
       * Recursive method to looks for a menu with a specified ID
       * @param element Top level menu bar for application.
       *            or current submenu.
       * @param id   ID of menu item we are looking for.
       * @return Desired menu item, or null if not found so far
       */
    public DragonMenu getMenu(MenuElement element,
					 String id)
        {
	DragonMenu desiredItem = null;
	if (element instanceof DragonMenu)
	    {
	    DragonMenu item = (DragonMenu) element;
	    if (item.getName().equals(id))
                {
                desiredItem = item;
		return desiredItem;
	        } 
	    }
	MenuElement[] subElems = element.getSubElements();
	if (subElems != null) 
	    {
	    for (int i = 0; (i < subElems.length) && (desiredItem == null);i++)
	         {
		 desiredItem = getMenu(subElems[i],id);
		 }
	    }
	return desiredItem;
	}


      /** 
       * Lookup a popup dialog by ID and return it to the caller.
       * Returns null if invalid ID is passed in.
       */
    public JDialog getDialog(String dlgID)
        {
	return (JDialog) dialogTable.get(dlgID);
	}

      /** 
       * Lookup a DragonPanel by ID and return it to the caller.
       * Returns null if invalid ID is passed in.
       */
    public DragonPanel getDragonPanel(String panelID)
        {
	return (DragonPanel) masterTable.get(panelID);
	}

      /**
       * Display a blank/default response panel. Used to implement the Cancel
       * btn for response panels.
       */
    public void showDefaultPanel()
        {
        if (selectedRadioBtn == historyBtn)
           setHistoryOn();
	else if (selectedRadioBtn == statusBtn)
	   setStatusOn();
        showResponsePanel("^EMPTY");
	rpArea.repaint();
	//refreshHelpAreaContent();
	}


      /**
       * Methods to programmatically set each radio button.
       */
	/**
    public void setHelpOn()
        {
	helpBtn.doClick();
	}
	**/

    public void setHistoryOn()
        {
	historyBtn.doClick();
	}

    public void setStatusOn()
        {
	statusBtn.doClick();
	}

    public void toggleCmdLine()
        {
        showCmdLineBtn.doClick();
	}

      /**
       * Set the text of the message area
       */
    public void setMessageText(String text)
        {
	messageArea.setText(text);
	}

      /**
       * Set the app's ready state - on or off.
       */
    public void setReady(boolean bReady)
        {
        if (READY_STRING == null)
	    {
	    READY_STRING = textSource.getI18NText(TextKeys.READY,"READY");
	    WORKING_STRING = textSource.getI18NText(TextKeys.WORKING,
						    "WORKING");
	    STARTING_STRING = textSource.getI18NText(TextKeys.STARTING,
						     "STARTING");
	    EXITING_STRING = textSource.getI18NText(TextKeys.EXITING,
						    "EXITING");
	    SCRIPT_STRING = textSource.getI18NText(TextKeys.SPTRUNNING,
						    "IN SCRIPT");
	    WAITING_STRING = textSource.getI18NText(TextKeys.SPTWAITING,
						    "WAITING");
	    CANCELLED_STRING = textSource.getI18NText(TextKeys.SPTCANCELLED,
						    "CANCELLED");
	    PAUSED_STRING = textSource.getI18NText(TextKeys.SPTPAUSED,
						    "PAUSED");
 	    }
        /* Don't set to ready until we get the -ENABLEUI command */
        if (bReady && !bEnableSignalled)
            return;
	if (bReady)
	    {
            if (bScriptControlVisible)
	        {
		try
		   {
                   readyArea.setText(SCRIPT_STRING);
		   }
		catch (Throwable t) 
		   {
		     //Just catch it silently. It has no effect.
		     //System.out.println("Caught interruption problem in setReady");
                   }
		}
	    else
	        {
		// set initialized only when we get the first ready message
		bInitialized = true;
		historyBtn.setEnabled(true);
		//helpBtn.setEnabled(true);
		statusBtn.setEnabled(true);
		showCmdLineBtn.setEnabled(true);
		if (showKeysBtn != null)
		    showKeysBtn.setEnabled(true);
		helpArea.setEnabled(true);
		refreshHelpAreaContent();
		if ((currentPanelID != null) && 
		    (currentPanelID.equals("^EMPTY")))
		     statusBtn.requestFocus();
                checkForSaveEnablement();
		setMenuBarEnabled(true);
		setNormalCursor(this);
		try
		   {
		   readyArea.setText(READY_STRING);
		   }
		catch (Throwable t) 
		   {
		     //System.out.println("Caught interruption problem in setReady");
                   }
		}
	    }
        else
	    {
	    try
	       {
               if (bExiting)
                  readyArea.setText(EXITING_STRING);
               else if (bScriptControlVisible)
                  readyArea.setText(SCRIPT_STRING);
               else if (bInitialized)
                  readyArea.setText(WORKING_STRING);
	       else
	          readyArea.setText(STARTING_STRING);
	       }
	    catch (Throwable t) 
	       {
		 //System.out.println("Caught interruption problem in setReady");
	       }

            if (currentPanelID != null)
	        {
		DragonPanel panel = (DragonPanel) masterTable.get(
						     currentPanelID);
	        panel.setAllDisabled();
                if (!bInitialized)
		    {
		    historyBtn.setEnabled(false);
		    //helpBtn.setEnabled(false);
		    statusBtn.setEnabled(false);
		    showCmdLineBtn.setEnabled(false);
		    if (showKeysBtn != null)
                         showKeysBtn.setEnabled(false);
		    helpArea.setEnabled(false);
		    }
	        }
	    }
	}

      /**
       * Methods from ComponentListener interface.
       */
    public void componentHidden(ComponentEvent ce)
        {
	}
    public void componentShown(ComponentEvent ce)
        {
	}

    public void componentMoved(ComponentEvent ce)
        {
        refreshHelpAreaContent();
	}

    public void componentResized(ComponentEvent ce)
        {
	refreshHelpAreaContent();
	}


      /**
       * Methods from FocusListener interface
       */
    public void focusGained(FocusEvent fe)
        {
	System.out.println("Focus gained");
	}

    public void focusLost(FocusEvent fe)
        {
	System.out.println("Focus Lost");
	}

      /**
       * Factorization - redisplays the appropriate text in
       * the help area.
       */
    protected void refreshHelpAreaContent()
        {
        if (helpArea == null)
            return;
	helpArea.setText("");
        try 
	    {
	    refreshHistoryDisplay();
	    refreshStatusDisplay();
	    refreshHelpDisplay();
	    }
	catch (Exception e)
	    {
	    System.out.println("Error attempting to refresh help area: ");
	    e.printStackTrace();
	    }
	}

      /**
       * Method from ActionListener interface
       */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
	if (source instanceof JMenuItem)
	    {
            String rpId = null;
            Callback callback = null;
	    DragonPanel panel = null;
	    String label = null;
	    String command = null;
            if (source instanceof DragonMenuItem)
	        {
  	        DragonMenuItem menuItem = (DragonMenuItem) source;
		rpId = menuItem.getInvokedPanelId();
		callback = menuItem.getCallback();
                label = menuItem.getName();
		command = menuItem.getCommandString();
		if (callback != null)
	            {
		    // communicate the name of the menu item via the
		    // dummy field. This is a bit of a hack.
		    dummyField.setLabelText(label);
		    if (!menuItem.isKeepContext())
		        showDefaultPanel();
		    callback.executeCallback(dummyField);
		    }
		else if (rpId != null)
		    {
		    panel = (DragonPanel) masterTable.get(rpId);
		    if (panel == null)
		        {
			System.out.println(
                         "ERROR: menu item references non-existent panel " + rpId);
			return;
			}
		    panel.setPanelCommand(menuItem.getCommandString());
		    showPanel(panel);
		    currentPanelID = rpId;
		    setCmdLineOff();
		    pack();
		    }
		else if (command != null)
		    {
		    commandForwarder.sendCommandToServer(command);
		    }
		}
	    }
	else if (source instanceof JRadioButton)
	    {
	    JRadioButton btn = (JRadioButton) source;
	    processRadioButton(btn);
	    }
	else if (source == showKeysBtn)
	    {
	    bShowKeys = showKeysBtn.isSelected();
	    if (bShowKeys)
	        keyDisplay.show();
	    else
	        keyDisplay.hide();
	    }
        else if (source == showCmdLineBtn)
	    {
            handleCommandLineDisplay();
	    }
	}

      /**
       * Factorization of actionPerformed method. Handles
       * changes in the text area controlling radio buttons.
       */
    protected void processRadioButton(JRadioButton btn)
        {
	selectedRadioBtn = btn;
	refreshHelpAreaContent();
	}

      /**
       * Factorization of actionPerformed method. Handles
       * changes in the command line visibility.
       */
    protected void handleCommandLineDisplay()
        {
        DragonPanel panel = null;
	bCmdLineVisible  = showCmdLineBtn.isSelected();
	if (bCmdLineVisible)
	    topPanel.add(commandLine, BorderLayout.SOUTH);
	else
	    topPanel.remove(commandLine);
	pack();
	if (currentPanelID != null)
	    panel = (DragonPanel) 
	          masterTable.get(currentPanelID);
	if (bCmdLineVisible)
	    {
	    commandLine.requestFocus();
	    if (panel != null)
	        panel.setAllDisabled();
	    }
	else
	    {
	    if (panel != null)
	        panel.setAllToDefaults();
	    }
        }


      /**
       * Unconditionally turn off the command line.
       * Used by showPanel
       */
    protected void setCmdLineOff()
        {
	DragonPanel panel = null;
	showCmdLineBtn.setSelected(false);
	if (bCmdLineVisible)
	    topPanel.remove(commandLine);
	pack();
	if (currentPanelID != null)
	    panel = (DragonPanel) 
	          masterTable.get(currentPanelID);
	if (panel != null)
	    panel.setAllToDefaults();
        }

      /**
       * Factorization of the actionPerformed method, allows
       * us to display a panel under program control
       */
    protected void showPanel(DragonPanel panel)
        {
	bNewPanel = true;
        Dimension panelSize;
	//System.out.println("showPanel called for " + panel.getName());
        if (panel.equals(emptyPanel))
	    {
            panel.setPreferredSize(emptyPanelSize);
	    panelSize = emptyPanelSize;
	    }
	else
	    {
	    panelSize = panel.getPreferredSize();
	    setMessageText("");
            }
	rpSize.height = panelSize.height + 10;
	rpArea.setPreferredSize(rpSize);
	cardLayout.show(rpArea,panel.getName());

        Dimension oldPrefSize = bottomPanel.getPreferredSize();
        /**  
        if (panel.needsBigHelp())
	    {
            bottomPanel.setPreferredSize(bigHelpDim);
	    }
	else
	    {
	**/
	    bottomPanel.setPreferredSize(helpDim);
	    /**
	    }
	    **/
        if ((oldPrefSize.height != bottomPanel.getPreferredSize().height) ||
            (panel.equals(emptyPanel)))
	    {
	    try 
	        {
		pack();
		//if (selectedRadioBtn == helpBtn)
                //   helpArea.setText("");
		refreshHelpAreaContent();
		}
	    catch (java.lang.Error readLockErr)
	        {
		ApplicationManager.getErrorLogger().logError(
               "DragonUI: Runtime error during ShowPanel::pack",true);
	        }
	    }
	// adjust the next focusable component so Tab on
	// the show command line button will wrap back to top of
	// response panel.
	DragonField fld = panel.getFirstField();
	showCmdLineBtn.setNextFocusableComponent(fld);
	}

      /**
       * public method to show a panel based on its ID.
       * @param panelID  ID of response panel that we want
       */
    public void showResponsePanel(String panelID)
        {
        DragonPanel panel = (DragonPanel) masterTable.get(panelID);
	if (panel != null)
	   {
	   showPanel(panel);
	   currentPanelID = panelID;
	   }
        else 
	   {
	   currentPanelID = null;
	   }
	}
     
      /**
       * Enable or disable all the top level items on the menu bar.
       */
    public void setMenuBarEnabled(boolean flag)
        {
	MenuElement bar = (MenuElement) getJMenuBar();
	MenuElement[] subElems = bar.getSubElements();
	if (subElems != null) 
	    {
	    int len = subElems.length;
	    for (int i = 0; i < len; i++)
	        {
		JMenu menu = (JMenu) subElems[i];
		menu.setEnabled(flag);
		}
	    }
        }

      /**
       * This method is called from the script control panel,
       * to set the status area to say either "Waiting"
       *  or "Script running" or "Paused".
       */
    public void setScriptStatusMessage(int state )
        {
Tracer.outputTraceMessage("Entered setScriptStatusMessage with state " +
                          String.valueOf(state), "UI", ApplicationManager.getTimeOffset());
        switch (state)
            {
            case ScriptControlPanel.WAITING_STATE:
	        readyArea.setText(WAITING_STRING);
Tracer.outputTraceMessage("Text set to " + WAITING_STRING,
			  "UI", ApplicationManager.getTimeOffset());
		break;
	    case ScriptControlPanel.PAUSEPENDING_STATE:
	    case ScriptControlPanel.PAUSED_STATE:
	        readyArea.setText(PAUSED_STRING);
Tracer.outputTraceMessage("Text set to " + PAUSED_STRING,
			  "UI", ApplicationManager.getTimeOffset());
		break;
	    case ScriptControlPanel.CANCELLED_STATE:
	        readyArea.setText(CANCELLED_STRING);
Tracer.outputTraceMessage("Text set to " + CANCELLED_STRING,
			  "UI", ApplicationManager.getTimeOffset());
		break;
	    default:    
	        readyArea.setText(SCRIPT_STRING);
Tracer.outputTraceMessage("Text set to " + SCRIPT_STRING,
			  "UI", ApplicationManager.getTimeOffset());

		break;
	    }
	}


      /**
       * When script is running, enable only Exit and Cancel items
       * @param bFlag if true, enable File & Script subelements, else disable
       */
    protected void setScriptMenusEnabled(boolean bFlag)
        {
        JMenuItem item = null;
	JMenu menu = null;
	JMenu submenu = null;
	MenuElement bar = (MenuElement) getJMenuBar();
        menu = (JMenu) getMenu(bar,"mF");
	if (menu != null)
	    menu.setEnabled(true);
	Component[] subElems = menu.getMenuComponents();
	if (subElems != null) 
	    {
	    int len = subElems.length;
	    for (int i = 0; i < len; i++)
	        {
		if (subElems[i] instanceof JMenuItem)
		   {
		   item = (JMenuItem) subElems[i];
		   item.setEnabled(bFlag);
		   }
		else if (subElems[i] instanceof JMenu)
		   {
		   submenu = (JMenu) subElems[i];
		   submenu.setEnabled(bFlag);
		   }
		}
	    }
        menu = (JMenu) getMenu(bar,"mF/SPT");
	if (menu != null)
	    menu.setEnabled(true);
        subElems = menu.getMenuComponents();
	if (subElems != null) 
	    {
	    int len = subElems.length;
	    for (int i = 0; i < len; i++)
	        {
		if (subElems[i] instanceof JMenuItem)
		   {
		   item = (JMenuItem) subElems[i];
		   item.setEnabled(bFlag);
		   }
		else if (subElems[i] instanceof JMenu)
		   {
		   submenu = (JMenu) subElems[i];
		   submenu.setEnabled(bFlag);
		   }
		}
	    }
        item = (JMenuItem) getMenuItem(bar,"mF/SPT/CAN");
	if (item != null)
	    item.setEnabled(!bFlag);  // cancel only enabled when running a SPT
        if (bFlag) // all enabled
            return;
        item = (JMenuItem) getMenuItem(bar,"mF/EXIT");
	if (item != null)
	    item.setEnabled(true);

	}

      /**
       * Enable or disable the SAVE menu items based on whether
       * there is an image or any signatures to be saved.
       */ 
    protected void checkForSaveEnablement()
        {
	MenuElement bar = (MenuElement) getJMenuBar();
        JMenuItem fSaveItem =(JMenuItem) getMenuItem(bar,"mF/SAV");
        JMenuItem cSaveItem = (JMenuItem) getMenuItem(bar,"mC/EDI/SAV");
        boolean bFSave = statusManager.isMemoryFileValid(DFileType.IMAGE,
							 "=M");
	if (bRestrictedVersion)
	    bFSave = false;  // never enable for restricted
	boolean bCSave = statusManager.isMemoryFileValid(DFileType.SIGNATURE,
							 "(Current)");
        if (fSaveItem != null)
             fSaveItem.setEnabled(bFSave);
        if (cSaveItem != null)
             cSaveItem.setEnabled(bCSave);
        }

      /**
       * Display or hide the ScriptControlPanel.
       * @param bShow If true, make visible, else hide.
       */
    public void setScriptControlPanelVisible(boolean bShow)
        {
	bCmdLineVisible = showCmdLineBtn.isSelected();
	if ((bShow) && (!bScriptControlVisible))
	    {
            if (bCmdLineVisible)
	        topPanel.remove(commandLine);
	    topPanel.add(scriptCtrl, BorderLayout.SOUTH);
	    setMenuBarEnabled(false);
	    setScriptMenusEnabled(false);
            statusBtn.setEnabled(false);
	    // clear the cancelled flag, if necessary
	    scriptCtrl.setLastScriptCancelled(false);
	    bScriptControlVisible = true;
	    // select history so we can see potential echos
	    setHistoryOn();
	    }
	else if (bScriptControlVisible)
	    {
	    topPanel.remove(scriptCtrl);
            bScriptControlVisible = false;
	    setMenuBarEnabled(true);
	    setScriptMenusEnabled(true);
	    messageArea.setText(" ");
            statusBtn.setEnabled(true);
	    if (bCmdLineVisible)
	        topPanel.add(commandLine, BorderLayout.SOUTH);
            readyArea.setText(READY_STRING);
	    }
	pack();
        }


      /**
       * Methods from the KeyListener interface.
       * These were formerly part of the DragonField class
       * but were removed in order to make the UI component
       * classes general rather than specific.
       */
    public void keyPressed(KeyEvent ke)
        {
  	DragonPanel parent;
	int code = ke.getKeyCode();
        Object source = ke.getSource();
	DragonField field = null;
	JComponent src = null;
	if (source instanceof DragonField)
            field = (DragonField) source;
	else
	    {
	    src = (JComponent) source;
	    Object p = src.getClientProperty(DragonField.PARENT_FIELD);
	    if (p != null)
	        {
                field = (DragonField) p;
		}
	    }
	if (field == null)
	    return;
	if (checkGeneralKeys(code, ke))
	    {
            ke.consume();
            return;
	    }
	switch(code)
	    {
	    case KeyEvent.VK_KP_DOWN:
	    case KeyEvent.VK_DOWN:
                if (field instanceof CommandLine)
		    {
		    CommandLine cmdLine = (CommandLine) field;
		    String newCmd = cmdLine.nextHistoryLine();
		    if (newCmd != null)
                        cmdLine.setFieldValue(newCmd);
		    ke.consume();
		    }
		break;
	    case KeyEvent.VK_ENTER:
	        // for command line, enter means "do it"
                if (!(field instanceof CommandLine))
		    {
    	            ke.setKeyCode(KeyEvent.VK_TAB);
		    }
		break;
	    case KeyEvent.VK_KP_UP:
	    case KeyEvent.VK_UP:
                if (field instanceof CommandLine)
		    {
		    CommandLine cmdLine = (CommandLine) field;
		    String newCmd = cmdLine.previousHistoryLine();
		    if (newCmd != null)
                        cmdLine.setFieldValue(newCmd);
		    ke.consume();
		    }
		break;
            case KeyEvent.VK_E:
                if ((ke.getModifiers() & InputEvent.CTRL_MASK) == 0)
		    {
		    break;  // otherwise fall through
		    }
	    case KeyEvent.VK_F1:
	    case KeyEvent.VK_F5:
	        // see if the parent panel has an OK button
	        // Note hardcoded btn Ids must match XML
	        parent = field.getTopLevelPanel();
                if (field instanceof CommandLine)
		     {
		     // simulate typing -.
                     String currentVal = field.getFieldValue();
		     field.setFieldValue(currentVal + " " +
				   CommandLine.EXEC);
                     CommandLine cmd = (CommandLine) field;
                     cmd.actionPerformed(null);
		     }
		else
		     {
		       /** Any panel button that is handled as OK 
                        *  should be included in this code...
			*/
                     DragonField okBtn = parent.getField("execButton");
		     if (okBtn == null)
		         okBtn = parent.getField("pathButton");
		     if (okBtn == null)
		         okBtn = parent.getField("colorButton");
		     if ((okBtn != null) && (okBtn instanceof DButtonField))
		         {
			 DButtonField okFld = (DButtonField) okBtn;
                         okFld.requestFocus();
			 javax.swing.Timer okayTimer =
			     new javax.swing.Timer(500,
						   new ButtonInvoker(okFld));
                         okayTimer.setRepeats(false);
                         okayTimer.start(); 
		         }
		     }
		ke.consume();
		break;
            case KeyEvent.VK_X:
                if ((ke.getModifiers() & InputEvent.CTRL_MASK) == 0)
		    {
		    break;  // otherwise fall through
		    }
	    case KeyEvent.VK_F10:
	    case KeyEvent.VK_ESCAPE:
	        // see if the parent panel has an cancel button
	        // Note hardcoded btn Ids must match XML
	        parent = field.getTopLevelPanel();
                if (field instanceof CommandLine)
		     {
                     field.clearField();
		     }
		else
		     {
		     DragonField cancelBtn = parent.getField("cancelButton");
		     if ((cancelBtn != null) && 
			 (cancelBtn instanceof DButtonField))
		         {
			 DButtonField cancelFld = (DButtonField) cancelBtn;
			 cancelFld.invoke();
		         }
		     }
		ke.consume();
		break;
	    default:
	        break;
	    }
	}

      /**
       * Factorization of keyPressed. Returns true if key code
       * matches F4, F6 or F7, otherwise returns false.
       */
    protected boolean checkGeneralKeys(int keyCode,
				       KeyEvent ke)
        {
	boolean bMatches = true;
	switch (keyCode)
	    {
		/**
	    case KeyEvent.VK_F4:
	        setHelpOn();
	        break;
		**/
	    case KeyEvent.VK_F6:
	        setStatusOn();
	        break;
	    case KeyEvent.VK_F7:
	        setHistoryOn();
	        break;
            case KeyEvent.VK_N:
                if ((ke.getModifiers() & InputEvent.CTRL_MASK) == 0)
		    {
		    break;  // otherwise fall through
		    }
	    case KeyEvent.VK_F2:
		toggleCmdLine();
		break;
	    default:
	        bMatches = false;
	    }
	return bMatches;
	}

    public void keyReleased(KeyEvent ke)
        {
	}
    public void keyTyped(KeyEvent ke)
        {
	}

      /**************************************************
       * Methods required by the DragonApp interface.
       **************************************************/

      /**
       * Return the primary frame for the application. Used by
       * dialogs to set up parents.
       */
    public Frame getFrame()
        {
	return this;
	}

      /**
       * Return a path which should be used for temporary
       * files (such as the IpcFiles). This path will often
       * be read from a Dragon config file, but we do not
       * want to expose that here.
       * @return  Directory to use as temporary file path
       */
    public String getTempPath()
        {
	if (cfgProcessor != null)
	    return cfgProcessor.getKpath();
	else 
	    return ".";
        }

      /**
       * Initiate the application exit process. This may involve
       * application-specific cleanup.
       */
    public void doExit()
        {
        try 
	     {
             MessagesExhaustedDetector detector =
                     new MessagesExhaustedDetector(this);
	     detector.join();
	     if ((Tracer.isTracing()) && (messageDetector != null))
	         {
                 String filename = cfgProcessor.getKpath() +
		                   File.separator + "keyedMsg.txt";
		 messageDetector.dumpKeyedMessages(filename);
		 }
	     }
	catch (InterruptedException ie)
	     {
	     }
	System.exit(0);
	}

      /**
       * Update the currently displayed history if relevant
       * This is called from ExecCmdCallback after a command's lines
       * have been added to the history list. Also called by the
       * UiMessageDetector class, which can add lines to history.
       */
    public void refreshHistoryDisplay()
        {
        if ((helpArea == null) || (commandLine == null))
	    return;
	if (selectedRadioBtn != historyBtn)
	    {
	    return;
	    }
        if (historyBtn.isEnabled() == false)
	    {
            return;
	    }
	String history = commandLine.getHistory();
        try
	    {
	    if ((history != null) && (history.length() > 0))
	       { 
	       helpArea.setText(history);
	       }
	    else 
	       {
	       helpArea.setText("");
	       }
	    }
	catch (Throwable t)
	    {
            }
	lastStatus = NO_STATUS;
	helpArea.repaint();
	}

      /**
       * Update the currently displayed help if relevant
       */
    public void refreshHelpDisplay()
        {
	/**
        if ((helpArea == null) || (commandLine == null))
	    return;

	if (selectedRadioBtn != helpBtn)
	    {
	    return;
	    }
        if (helpBtn.isEnabled() == false)
	    {
            return;
	    }
	String help = helpArea.getText();
	if ((help != null) && (help.length() > 0))
	    helpArea.setCaretPosition(0);
	lastStatus = NO_STATUS;
	**/
	}

      /**
       * Update the currently displayed status if relevant
       */
    public void refreshStatusDisplay()
        {
	checkForSaveEnablement();
        if ((helpArea == null) || (statusManager == null))
	    return;
	if (selectedRadioBtn != statusBtn)
	    {
	    return;
	    }
        if (statusBtn.isEnabled() == false)
	    {
            return;
	    }
	String status = statusManager.getStatusData();
        String oldContents = helpArea.getText();
	if ((status != null) && (status.length() > 0)) // &&
	  //((status.compareTo(lastStatus) != 0) ||
          //   (status.compareTo(oldContents) != 0)))
	    { 
	    try
	       {
	       helpArea.setText(status);
	       helpArea.setCaretPosition(0);
	       helpArea.repaint();
	       }
	    catch (Throwable t) 
	       {
		 //System.out.println("Caught interruption problem in setReady");
	       }
	    }
	if (status != null)
	    lastStatus = status;
	}

      /**
       * Add text to the history list, if the application has
       * one.
       * @param historyText  Text to add
       * @param bComment     If true this msg should be flagged as
       *                        a comment or message
       */
    public void addToHistory(String historyText, boolean bComment)
        { 
	commandLine.addToHistory(historyText,bComment);
	}

      /**
       * Return an object that can translate keyed messages.
       * @return Appropriate, initialized I18NTextSource
       */
    public I18NTextSource getTextSource()
        {
	return textSource;
	}

      /**
       * Show an informational message.
       * @param msgText  Message text to display
       */
    public void showMessage(String msgText)
        {
        setMessageText(msgText);
        }

      /**
       * Show a warning.
       * @param msgText  Warning message text to display
       */
    public void showWarning(String msgText)
        {
        messageDisplay.showWarning(TextKeys.WARNING, msgText);
	}

      /**
       * Show an error.
       * @param msgText  Error message text to display
       */
    public void showError(String msgText)
        {
	errorDisplay.showError(TextKeys.ERROR,msgText);
	}

      /**
       * Show an error message made up of a translated and an
       * untranslated string.
       * @param msgKey  Key for translated part of message.
       * @param suffix  Additional text to add
       */
    public void showError(String msgKey, String suffix)
        {
	errorDisplay.showError(TextKeys.ERROR,msgKey,suffix);
	}

      /**
       * Show a table of data.
       * @param title  Title for table.
       * @param content  HTML text for table.
       * @param tableId  String to uniquely ID the table, so it can be killed.
       * @return true if successful, false if no display available
       */
    public boolean showTable(String title, 
			  String content,
			  String tableId)
        {
	TableDisplay tableDisplay = getTableDisplay();
        if (tableDisplay == null) /* close some table - not the most recent */
	    {
            int index = (lastTableDisplayedIndex + 1) % 4;
            if (tableDisplayList[index] != null)
	       {
               tableDisplayList[index].setVisible(false); 
	       tableDisplayList[index] = new TableDisplay(textSource,this);
               tableDisplay = tableDisplayList[index];
               tableDisplay.setIndex(index);
               }
            else
	       {
               return false;
               }
            }
        tableDisplay.showTableText(title,content);
	tableDisplay.setTableId(tableId);
	lastTableDisplayedIndex = tableDisplay.getIndex();
        return true;
	}

      /**
       * Hide a single TableDisplay identified by 'messageId', or
       * all if 'messageId' is "*".
       */
    public void killMessage(String messageId)
        {
        if (messageId.equals("*"))
	    {
            for (int i=0; i < MAX_TABLE_DISPLAY; i++)
                 if (tableDisplayList[i] != null)
                     tableDisplayList[i].setVisible(false);
	    }
        else 
	    {
            for (int i=0; i < MAX_TABLE_DISPLAY; i++)
	        {
                if ((tableDisplayList[i] != null) && 
                    (tableDisplayList[i].getTableId().equalsIgnoreCase(messageId)))
		    tableDisplayList[i].setVisible(false);
		}
	    }
        }

      /**
       * Return reference to class which will send commands.
       */
    public CommandForwarder getCommandForwarder()
        {
        return commandForwarder;
        }

      /**
       * Add a message to a user-log
       * @param msgText Message to add
       * @param bComment If true, mark as comment, not command.
       */
    public void logMessage(String msgText, boolean bComment)
        {
        commandLine.getCmdLogger().logMessage(msgText,bComment);
	}

      /**
       * Add a message to the error log file.
       * @param msgText Message to add
       * @param bFirst  Is this the first line to be added for this error?
       */
    public void logError(String msgText, boolean bFirst)
        {
	errorLogger.logError(msgText,bFirst);
	}

      /**
       * Return the detailsLink string, if any, for the
       * currently visible response panel. Returns null if
       * no current panel.
       */
    public String getCurrentPanelHelpId()
        {
	String helpId = null;
	if (currentPanelID != null)
	     {
	     DragonPanel panel = (DragonPanel) masterTable.get(
					     currentPanelID);
	     if (panel != null)
	         helpId = panel.getDetailsLink();
	     }
	return helpId;
	}

      /**
       * Accessor & mutator methods.
       */
    public void setExiting(boolean bFlag)
        {
	bExiting = bFlag;
	}

    public boolean isExiting()
        {
        return bExiting;
	}

    public boolean isWindows()
	{
	return bIsWindows;
	}

    public void setMessageDialogVisible(boolean bFlag)
        {
	ApplicationManager.setMessageDialogVisible(bFlag);
        if (!bFlag)
             setMessageText("");
	}

    public boolean isMessageDialogVisible()
        {
	return ApplicationManager.isMessageDialogVisible();
	}

    public void setLogging(boolean bFlag)
        {
	bLogging = bFlag;
        ApplicationManager.setLogging(bFlag);
	// System.out.println("Setting logging to " + bFlag);
	}

    public boolean isLogging()
        {
	return bLogging;
	}

    public void setLogFile(String filename)
        {
	// System.out.println("setting log file to " + filename);
	logFile = filename;
	ApplicationManager.setLogFileName(logFile);
	}

    public String getLogFile()
        {
	return logFile;
	}


    public void setMinSize(Dimension size)
        {
	minSize = size;
	}

    public Dimension getMinSize()
        {
	return minSize;
	}

    public Dimension getRpSize()
        {
	return rpSize;
	}

    public JPanel getResponseArea()
        {
	return rpArea;
	}
	/**
    public boolean isHelpSelected()
        {
	return ((selectedRadioBtn == helpBtn) &&
                (helpBtn.isEnabled()));
	}
	**/

    public boolean isHistorySelected()
        {
	return (selectedRadioBtn == historyBtn);
	}

    public boolean isStatusSelected()
        {
	return (selectedRadioBtn == statusBtn);
	}

    public boolean getShowKeys()
        {
	return bShowKeys;
	}

    public DImageHeader getMemoryHeader()
        {
	return memoryHeader;
	}

    public void setMemoryHeader(DImageHeader header)
        {
	memoryHeader = header;
	}

    public DragonFontChooser getFontChooser()
        {
	return fontChooser;
	}

    public DragonFileChooser getInFileChooser()
        {
	return inFileChooser;
	}

    public DragonFileChooser getMultiInFileChooser()
        {
	return multiInFileChooser;
	}

    public DragonFileChooser getOutFileChooser()
        {
	return outFileChooser;
	}

    public DragonFileChooser getPathChooser()
        {
	return pathChooser;
	}

    public ErrorDisplay getErrorDisplay()
        {
	return errorDisplay;
	}

    public MessageDisplay getMessageDisplay()
        {
	return messageDisplay;
	}

    public ScriptControlPanel getScriptCtrl()
        {
	return scriptCtrl;
	}

      /**
       * Return the first unused table display object
       */
    public TableDisplay getTableDisplay()
        {
        TableDisplay retDisplay = null;
        for (int i = 0; (i < MAX_TABLE_DISPLAY) && (retDisplay == null); i++)
	    {
            if (!(tableDisplayList[i].isVisible()))
	        {
		// create a new one 
	        tableDisplayList[i] = new TableDisplay(textSource,this);
		retDisplay = tableDisplayList[i];
                retDisplay.setIndex(i);
		}
            }
	return retDisplay;
	}

    public JEditorPane getHelpArea()
        {
	return helpArea;
	}

    public CommandLine getCommandLine()
        {
	return commandLine;
	}

    public boolean isNewPanel()
        {
	return bNewPanel;
	}

    public void setNewPanel(boolean flag)
        {
	bNewPanel = flag;
	}

    public boolean isScriptControlVisible()
        {
        return bScriptControlVisible;
        }

    public void displayKeys(DragonField ctrl)
        {
	keyDisplay.setCurrentPanel(currentPanelID);
	keyDisplay.setCurrentField(ctrl);
	}

    public void displayKeys(DragonMenuItem item)
        {
	keyDisplay.setCurrentPanel(currentPanelID);
	keyDisplay.setCurrentItem(item);
	}

    public StatusManager getStatusManager()
        {
	return statusManager;
	}

    public ConfigFileProcessor getCfgProcessor()
        {
	return cfgProcessor;
	}

    public SigFileProcessor getCurrentSigProcessor()
        {
	return currentSigProcessor;
	}

    public void setCurrentSigProcessor(SigFileProcessor sigProc)
        {
	currentSigProcessor = sigProc;
	}

    public Logger getErrorLogger()
        {
	return errorLogger;
	}

    public void setEnableSignalled(boolean flag)
        {
        bEnableSignalled = flag;
        } 

      /**
       * Static method turns on wait cursor.
       */
    public static void setWaitCursor(Component window)
        {
	window.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));
	}

      /**
       * Static method turns on wait cursor.
       */
    public static void setNormalCursor(Component window)
        {
	window.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
	}

      /**********
    protected void setupFonts(String language)
        {
        FontProcessor fontProc = ApplicationManager.getFontProcessor();
        FontUIResource defaultFont = null; 
	if (language.startsWith("ZH"))
           defaultFont = 
             new FontUIResource(fontProc.getFont(language));
	if (defaultFont == null)
           defaultFont = 
             new FontUIResource(fontProc.getFont("DEFAULT"));

        UIManager.put("Button.font", defaultFont);
        UIManager.put("Dialog.font", defaultFont);
        UIManager.put("Label.font", defaultFont);
        UIManager.put("Table.font", defaultFont);
        UIManager.put("TextField.font", defaultFont);
        UIManager.put("ScrollPane.font", defaultFont);
        UIManager.put("ComboBox.font", defaultFont);
        UIManager.put("CheckBox.font", defaultFont);
        UIManager.put("TitledBorder.font", defaultFont);
        UIManager.put("RadioButton.font", defaultFont);
        UIManager.put("ToolTip.font", defaultFont);
        UIManager.put("TextPane.font", defaultFont);
        UIManager.put("TextArea.font", defaultFont);

        UIManager.put("Tree.font", defaultFont);
        UIManager.put("List.font", defaultFont);

        UIManager.put("MenuBar.font", defaultFont);
        UIManager.put("Menu.font", defaultFont);
        UIManager.put("MenuItem.font", defaultFont);
        UIManager.put("TableHeader.font", defaultFont);
        UIManager.put("TabbedPane.font", defaultFont);

        SwingUtilities.updateComponentTreeUI(this);
        }
	***********/
 
      //**************************************************************
      /**
       * Main method, sets application running.
       */
    public static void main(String[] argv)
        {
        boolean bInstrument = false;
	// governs XML tracing
	boolean bTrace = false;
	// governs application level tracing
        boolean bSetTrace = false;
	ArrayList menuFileList = new ArrayList();
	ArrayList panelFileList = new ArrayList();
	String menuXmlFile = null;
	String panelXmlFile = null;
        DragonUI dragUI = null;
	if (argv.length > 0)
	    {
	    for (int i = 0; i < argv.length; i++)
	        {
		if (argv[i].indexOf(File.separator) >= 0)
		    {
		    DragonUI.homeDirectory = argv[i];
		    }
		else if (argv[i].compareTo("instrument") == 0)
		    {
		    bInstrument = true;
		    }
		else if (argv[i].compareTo("trace") == 0)
		    {
		    bTrace = true;
		    }
		else if (argv[i].compareTo("-t") == 0)
		    {
		    bSetTrace = true;
		    }
		}
            }
        if (DragonUI.homeDirectory == null)
	    DragonUI.homeDirectory = ".";

	DragonUI.reporter = new PerformanceReporter(bInstrument);
	DragonUI.reporter.report("Starting main");
	// bTrace = true;
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
   	    {
	    System.out.println("Error setting look and feel");
	    }

        //Splash splashScreen = new Splash("dragbanr.jpg",90,0,180);
	//splashScreen.setVisible(true);

        ResourceBundle bundle = ResourceBundle.getBundle("DragonUI");
        try
	    {
            menuXmlFile = bundle.getString("menuXmlFile");
            panelXmlFile  = bundle.getString("panelXmlFile");
	    }
        catch (MissingResourceException e)
	    {
            System.err.println(
                      "Cannot read properties file DragonUI.properties");
            System.exit(0);
	    }
        if ((menuXmlFile == null) || (panelXmlFile == null))
	    {
	    System.err.println(
                 "XML File names not specified in properties file");
	    System.exit(0);
	    }
        try 
	    {
	    menuFileList.add(menuXmlFile);
	    panelFileList.add(panelXmlFile);
	    CustomizeExpert customizer = 
                 new CustomizeExpert("./customize.txt");
	    if (customizer.isInitialized())
	       {
	       customizer.addMenuFiles(menuFileList);
	       customizer.addPanelFiles(panelFileList);
	       }
	    dragUI = new DragonUI((String[])menuFileList.toArray(new String[1]),
                                  (String[])panelFileList.toArray(new String[1]),
				  bTrace,
				  bSetTrace);
	    if (dragUI != null)
	        {
	        //splashScreen.setVisible(false);
	        //dragUI.setVisible(true);
	        Dimension minSize = dragUI.getSize();
	        dragUI.setMinSize(
		    new Dimension(minSize.width, minSize.height));
	        dragUI.addComponentListener(new ResizeListener(minSize,
					       dragUI));
		}
	    else
	        {
		System.exit(0);
		}
	    }
	catch (Exception e)
	    {
	    String message = null;
            System.out.println("Got encaught error/exception in DragonUI");
	    System.out.println("Exception message is: " + e.getMessage());
	    e.printStackTrace();
	    
           if (ApplicationManager.getTextSource() != null)
	        {
		message = ApplicationManager.getTextSource().getI18NText(
				"%h9480.0",
				"Unexpected internal error in DRAGON menu client; see DRAGERR.LOG for details.");
		}
	    else
	        {
		message = "Unexpected internal error in DRAGON menu client; see DRAGERR.LOG for details.";
		}
	    JOptionPane.showMessageDialog(null,message,"  ",
					  JOptionPane.ERROR_MESSAGE);
	    if (dragUI != null)
	        dragUI.logError(e.getMessage(),true);
	    }
	}
    

    /**
     * Inner class to handle delayed invocation of a button
     */
    class ButtonInvoker implements ActionListener
    {
	protected DButtonField okBtn = null;
        
        public ButtonInvoker(DButtonField button)
	   {
	   okBtn = button;
           }

        public void actionPerformed(ActionEvent e)
	   {
	   okBtn.invoke();
           }
    }
     

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonUI.java,v 1.157 2007/02/17 10:20:57 goldin Exp $ \n";
	}
    }








