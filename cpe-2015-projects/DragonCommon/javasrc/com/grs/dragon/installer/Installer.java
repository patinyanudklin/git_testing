/**
 * Installer
 * 
 * ~~ Copyright 2001-2011 Kurt Rudahl and Sally Goldin
 * ~~ EndC 
 * Created by Sally Goldin, 12/3/2001
 *
 *
 *  $Id: Installer.java,v 1.51.2.3 2011/09/24 03:15:49 rudahl Exp $
 *  $Log: Installer.java,v $
 *  Revision 1.51.2.3  2011/09/24 03:15:49  rudahl
 *  purge some driver code; improved tracing
 *
 *  Revision 1.51.2.2  2011/02/06 10:02:09  rudahl
 *  removed some dragon-specific code
 *
 *  Revision 1.51.2.1  2010/09/11 11:27:40  rudahl
 *  recognize Windows7
 *
 *  Revision 1.51  2007/06/18 12:50:48  goldin
 *  directly call the cleanup callback upon error
 *
 *  Revision 1.50  2007/06/17 12:01:57  goldin
 *  split main in Installer so that we can check key before the UI shows up
 *
 *  Revision 1.49  2007/06/15 11:44:25  goldin
 *  Make functions to be called by setup static
 *
 *  Revision 1.48  2007/06/15 09:51:35  goldin
 *  make reportSuccess and errorAndRestart public
 *
 *  Revision 1.47  2007/05/25 14:18:25  rudahl
 *  fine-tuning Hasp & vista fixes
 *
 *  Revision 1.46  2007/05/25 11:35:18  goldin
 *  Modify error handling
 *
 *  Revision 1.45  2007/05/25 08:24:24  goldin
 *  Re-enable the installation of the rainbow drivers
 *
 *  Revision 1.44  2007/05/22 10:20:20  goldin
 *  Modify behavior for use with new Key
 *
 *  Revision 1.43  2007/05/19 10:05:19  rudahl
 *  now receives ser num from CPP if it was in the key
 *
 *  Revision 1.42  2006/12/25 10:49:27  goldin
 *  Changed constructor for file chooser
 *
 *  Revision 1.41  2006/12/10 05:02:28  goldin
 *  Make delay be a symbol for easy modification
 *
 *  Revision 1.40  2006/06/06 05:21:28  goldin
 *  Make status area bigger and internationalize the CMD prompt
 *
 *  Revision 1.39  2006/04/27 04:20:37  goldin
 *  Make CPATH equal to DPATH during installation
 *
 *  Revision 1.38  2006/04/24 07:20:25  rudahl
 *  .CFG changes: added InstallTime, removed working lines & pix
 *
 *  Revision 1.37  2006/03/07 07:20:23  goldin
 *  Change the status area to black when we are done
 *
 *  Revision 1.36  2006/03/02 06:17:26  goldin
 *  Fix parsing of dragon product string
 *
 *  Revision 1.35  2006/03/01 04:31:58  goldin
 *  Make title and installation of driver depend on product passed to installer
 *
 *  Revision 1.34  2006/02/12 06:25:45  goldin
 *  Fix word wrap in status area
 *
 *  Revision 1.33  2006/01/24 09:15:12  goldin
 *  Allow user to cancel install from language dialog
 *
 *  Revision 1.32  2005/12/21 06:15:26  goldin
 *  Remove debugging info
 *
 *  Revision 1.31  2005/12/20 08:14:17  goldin
 *  Add FontProcessor
 *
 *  Revision 1.30  2005/08/01 04:43:17  goldin
 *  Completing I18N for installer
 *
 *  Revision 1.29  2005/07/31 08:34:31  goldin
 *  Working in I18N of Installer
 *
 *  Revision 1.28  2005/07/29 09:42:08  goldin
 *  Add Language selection functionality
 *
 *  Revision 1.27  2005/07/24 13:05:45  goldin
 *  Change name of open dragon banner
 *
 *  Revision 1.26  2005/07/24 13:01:59  goldin
 *  Add upcasing of drive letters, skipping of protections - chg version to 5.8
 *
 *  Revision 1.32  2005/07/22 07:32:58  goldin
 *  Fix problems with paths that have embedded spaces
 *
 *  Revision 1.31  2005/07/06 02:49:58  goldin
 *  Fix null ptr exception if you didn't install the samples
 *
 *  Revision 1.30  2005/07/04 04:58:16  goldin
 *  Take out completion dialog
 *
 *  Revision 1.29  2005/06/27 06:07:22  goldin
 *  Upcase drive letters
 *
 *  Revision 1.28  2005/06/20 13:53:54  goldin
 *  Fixes to make the installer work
 *
 *  Revision 1.27  2005/06/20 09:31:32  rudahl
 *  adapt for FLOAT_PRODUCT
 *
 *  Revision 1.26  2005/06/20 09:15:31  goldin
 *  Change border color on splash screen
 *
 *  Revision 1.25  2005/02/06 08:28:58  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.24  2004/12/18 11:06:42  goldin
 *  Make verbose mode work
 *
 *  Revision 1.23  2004/12/11 04:56:47  goldin
 *  Capitalize SN before use
 *
 *  Revision 1.22  2003/02/12 15:26:03  rudahl
 *  java install method now returns SPATH
 *
 *  Revision 1.21  2002/10/22 15:57:57  goldin
 *  Don't ask for confirm from Cancel btn
 *
 *  Revision 1.20  2002/09/20 16:27:45  goldin
 *  Disable cancel when actually doing the install
 *
 *  Revision 1.19  2002/09/15 22:23:25  goldin
 *  Set workinglines to 512 for demo, unauth and d4s
 *
 *  Revision 1.18  2002/09/12 00:35:13  goldin
 *  Add Readme button; don't exit automatically after confirming success
 *
 *  Revision 1.17  2002/09/03 18:20:05  goldin
 *  Get rid of redundant OS check
 *
 *  Revision 1.16  2002/09/03 18:03:03  goldin
 *  Fix bugs in running off the CD
 *
 *  Revision 1.15  2002/02/15 21:20:28  goldin
 *  Rework protection mechanisms &S/N-based product algorithm
 *
 *  Revision 1.14  2002/02/08 18:02:04  goldin
 *  Add code to determine version and write to test file
 *
 *  Revision 1.13  2002/01/11 17:18:57  goldin
 *  Fix date calcs
 *
 *  Revision 1.12  2001/12/21 10:38:08  goldin
 *  Change completion message
 *
 *  Revision 1.11  2001/12/19 20:34:38  goldin
 *  Add functionality to run CHK
 *
 *  Revision 1.10  2001/12/18 15:13:06  goldin
 *  Changes to Layout and UI
 *
 *  Revision 1.9  2001/12/11 16:19:24  goldin
 *  Add splash screen
 *
 *  Revision 1.8  2001/12/11 14:24:03  goldin
 *  Make installation of driver work
 *
 *  Revision 1.7  2001/12/10 15:53:40  goldin
 *  Try installing Sentinel driver
 *
 *  Revision 1.6  2001/12/07 17:21:34  goldin
 *  Minor changes to handle the JNI interface, polishing
 *
 *  Revision 1.5  2001/12/07 12:11:19  goldin
 *  Add code to create temp file
 *
 *  Revision 1.4  2001/12/06 14:55:35  goldin
 *  Continue expanding implementation
 *
 *  Revision 1.3  2001/12/05 14:28:33  goldin
 *  Implement file copying and cleanup
 *
 *  Revision 1.2  2001/12/04 16:09:34  goldin
 *  Implement class to control file operations -not yet working
 *
 *  Revision 1.1  2001/12/03 18:02:54  goldin
 *  Initial development for installer
 *
 **************************************************************
 * 5.10	2011-02-06 ktr	removed some Dragon-specific code
 */

package com.grs.dragon.installer;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.util.*;
import java.io.*;
import javax.swing.*;
import javax.swing.plaf.*;
import java.awt.*;
import java.awt.event.*;

/**
 * This is the top-level class for a semi-generic installation
 * application. The UI has two main parts, an upper panel which
 * requests information from the user and a lower panel which
 * displays status information as the installation proceeds.
 * <p>
 * The structure of the upper panel is governed by a Dragon UI
 * XML file, which is passed in as an argument to the application.
 * The files to be installed are assumed to be copied from a CD;
 * They are listed, with source and destination directories (and
 * possibly wildcards, in a text file which is passed as the
 * second argument to the application.
 */
public class Installer extends JFrame implements ActionListener,
                                                 KeyListener
    {
    public static Installer install = null;

    protected static final String monthNames[] = {"Jan", "Feb", "Mar", "Apr",
						"May", "Jun", "Jul", "Aug",
						"Sep", "Oct", "Nov", "Dec"};

    static final int FLOAT_PRODUCT  =	0x8;  

      /**
       * offset of product byte in the test file & test file name
       * Also recorded in permbits.h
       */

      /**
       * Class to handle help display in response to mouse enter
       * events.*/
    protected GenHelpDisplayListener helpDisplayListener;

      /**
       * Source for internationalized text. Not currently
       * used (initialized with a dummy file)
       */
    protected I18NTextSource textSource = null;

      /**
       * Dragon Config file processor. A standard config
       * file is supplied with the installer and then
       * customized for the user.
       */
    protected ConfigFileProcessor cfgProcessor = null;

      /**
       * Class to cleanup after a premature exit.
       */
    protected InstallCleanupCallback cleanCallback = null;
 
      /**
       * Set to true after installation completes successfully.
       */
    protected boolean bSuccess = false;

      /**
       * Current directory in which application is running.
       */
    protected String homeDirectory = null;

      /**
       * Three file choosers, for input files, output files, 
       * and paths.*/
    protected DragonFileChooser inFileChooser = null;
    protected DragonFileChooser outFileChooser = null;
    protected DragonFileChooser pathChooser = null;
    protected boolean bVerbose = false;

      /**
       * Language to use in this UI.
       */
    protected String language = "EN";

      /**
       * Table of response panels and menus, populated by XML
       * parser.
       */
    protected Hashtable masterTable = new Hashtable(20);

      /**
       * Table of popup dialogs. Indexed by the panel's ID.
       */
    protected Hashtable dialogTable = new Hashtable(16);

      /**
       * Area of the UI where response panels will show up.
       */
    protected JPanel rpPanel = null;

      /**
       * Cardlayout for rpPanel
       */
    protected CardLayout cardLayout = null;

      /**
       * Cardlayout for bottom panel - to switch Help and Status
       */
    protected CardLayout statusCardLayout = null;

      /**
       * Panel that this cardlayout applies to
       */
    protected JPanel statusPanel = null;

      /**
       * Label to indicate if help or status.
       */
    protected JLabel statusLabel = null;

      /**
       * JTextArea for showing status.
       */
    protected JTextArea statusArea = null;

      /**
       * Help area
       */
    protected JEditorPane helpArea = null;

      /**
       * Buttons to control flow.
       */
    protected JButton continueButton = null;
    protected JButton backButton = null;
    protected JButton cancelButton = null;
    protected JButton readmeButton = null;

      /** 
       * Desired dimensions of response panels.
       */
    protected Dimension rpSize = new Dimension(400,300);

      /**
       * panel index, allows us to sythesize next panel id
       */
    protected int panelIndex = 0;

      /**
       * Hold on to the currently displayed panel so we can
       * query its fields.
       */
    protected DragonPanel currentPanel = null;

      /**
       * Window monitor - used to handle exit button as well
       * as exiting via frame.
       */
    protected SimpleWindowMonitor winMonitor = null;

      /**
       * hold on to the name of the file list 
       */
    protected String fileListFile = null;

      /**
       * Class instance to handle processing of the installation
       * kit files.
       */
    protected InstallFileManager fileManager = null;

    protected static String czSpath = null; /* for retrieval afterward */

    protected String selectedLanguage = "EN";
   
    protected DTextField dummyField = null; 

     /* If true, this is open dragon; if false, commercial */ 
    protected boolean bOpenDragon = true;

     /** serial number passed from the C++ startup (from key) 
      * Will be null for OpenDragon or for a GRS Dragon demo
      */   
    protected String passedSN = null;

     /* version number constructed from info passed by Setup program. */
    protected String softwareVersion = null;

      /****************************************************/
      /**
       * Constructor initializes and creates sub-objects,
       * creates the user interface.
       * @param xmlFileName  XML file describing the input panel(s)
       * @param fileListFile Text file telling us what to copy
       * @param bTrace If true, trace the XML processing
       * @param serialNum Serial number or null (if no key)
       * @param productString Indicates whether this is OpenDragon or not
       */
    public Installer(String xmlFileName, String fileListFile,
		     boolean bTrace, String serialNum,
                     String productString)
        {
	super();
        String windowTitle = null;
        int pos1 = 0;
        pos1  = productString.indexOf("_");
        if (productString.startsWith("Open"))
            bOpenDragon = true;
        else 
            bOpenDragon = false;
	if (pos1 > 0)
            softwareVersion = "V" + 
	         productString.substring(pos1+1);
	else
	    softwareVersion = " ";
        if (bOpenDragon)
            windowTitle = "OpenDragon " + softwareVersion +
                          " Installation";
	else
            windowTitle = "Dragon/ips " + softwareVersion +
                          " Installation";
	setTitle(windowTitle);
	boolean bIsWindows = false;
	this.fileListFile = fileListFile;
	if (serialNum != null)
            passedSN = serialNum;
	homeDirectory = System.getProperty("user.dir");
        ApplicationManager.setModulePrefix("IN");
	ApplicationManager.setHomeDirectory(homeDirectory);
	/* create a temporary English text source */
	String filename = "./system/en/drag-installer-en.messages";
	textSource = new I18NTextSource(filename);
      	if (!textSource.isInitialized())
	    {
	    System.exit(0);
	    }
        ApplicationManager.setTextSource(textSource);

        cfgProcessor = new ConfigFileProcessor(homeDirectory);
	if (cfgProcessor.isInitialized())
	    { 
	    language = cfgProcessor.getCountry();
	    ApplicationManager.setCountry(language);
            ApplicationManager.setReadPath(cfgProcessor.getDpath());
            ApplicationManager.setWritePath(cfgProcessor.getWpath());
            ApplicationManager.setTempPath(cfgProcessor.getKpath());
	    }
	else 
   	    {
	    System.exit(0);
	    }

        String OS = System.getProperty("os.name");
	//System.out.println("The operating system is " + OS);
	if (OS.toUpperCase().indexOf("WIN") >= 0)
	    {
	    bIsWindows = true;
	    }
	FontProcessor fontProc = new FontProcessor(bIsWindows);
	ApplicationManager.setFontProcessor(fontProc);
        /* Ok - find out what language they want */ 
	InstallerLanguageCallback languageCallback =
	    new InstallerLanguageCallback(this);
	dummyField = new DTextField("dummyInst");
	dummyField.setParentComponent(this);
	languageCallback.executeCallback(dummyField); 
        if (languageCallback.wasOkClicked() == false)
            System.exit(0);
	setupFonts(selectedLanguage);
        language = selectedLanguage;
	//System.out.println("Selected Language is " + language);
	/* Recreate the text source using the selected language */
	filename =  "./system/" +
                    language.toLowerCase() +
                    "/drag-installer-" + language.toLowerCase() +
                    ".messages";
	File testFile = new File(filename);
	if (testFile.exists())
	   {
	   I18NTextSource realTextSource = new I18NTextSource(filename);
	   /* If we don't have an installation file translation, 
	    * continue to use English for the installation kit.
	    */
	   if (textSource.isInitialized())
	       {
	       ApplicationManager.setTextSource(realTextSource);
	       textSource = realTextSource;
	       }
	   }
	else
	   System.out.println("Can't find installer message file - " +
			      filename);
	GenErrorDisplay errorDisplay = new GenErrorDisplay(textSource,this);
        ApplicationManager.setErrorDisplay(errorDisplay);
	MessageDisplay messageDisplay = 
	     new MessageDisplay(textSource,this);
        ApplicationManager.setMessageDisplay(messageDisplay);
	inFileChooser = new DragonFileChooser(this,textSource,
					      false,true,false);
	ApplicationManager.setInFileChooser(inFileChooser);
	outFileChooser = new DragonFileChooser(this,textSource,
					       false,false,false);
	ApplicationManager.setOutFileChooser(outFileChooser);
	pathChooser = new DragonFileChooser(this,textSource,
					     true,false,false);
	ApplicationManager.setPathChooser(pathChooser);
	createUI();
	setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
	String exitMessage = textSource.getI18NText("%h01.9904","Exit, cancelling installation?");
        winMonitor = new SimpleWindowMonitor(this,exitMessage); 
        cleanCallback = new InstallCleanupCallback();
	winMonitor.setCleanupCallback(cleanCallback);
	addWindowListener(winMonitor);
	setIconImage(new ImageIcon("dragexec.gif").getImage());
	initPanels(xmlFileName,bTrace);
	pack();
	}

   /** 
    * Called by the InstallerLanguageCallback when
    * the user chooses a new language
    */
   public void setSelectedLanguage(String language)
      {
      selectedLanguage = language;
      }

      /**
       * Build the basic user interface components.
       */
   protected void createUI()
       {
       JPanel topPanel = new JPanel(new BorderLayout()); 
       cardLayout = new CardLayout();
       rpPanel = new JPanel(cardLayout);
       rpPanel.setPreferredSize(rpSize);
       //rpPanel.setBorder(BorderFactory.createMatteBorder(0,10,10,10,
       //                 getBackground()));
       topPanel.add(rpPanel, BorderLayout.CENTER);
       JPanel buttonPanel = new JPanel(new FlowLayout());
       continueButton = new JButton(textSource.getI18NText("%h00.1",
							   "Continue"));
       buttonPanel.add(continueButton);

       continueButton.addActionListener(this);
       continueButton.addKeyListener(this);
  
       backButton = new JButton(textSource.getI18NText("%h00.2",
						       "Back"));
       buttonPanel.add(backButton);
       backButton.addActionListener(this);
       backButton.addKeyListener(this);
       backButton.setEnabled(false);

       cancelButton = new JButton(textSource.getI18NText("%h00.3",
							 "Cancel"));
       buttonPanel.add(cancelButton);
       cancelButton.addActionListener(this);
       cancelButton.addKeyListener(this);
       //cancelButton.setNextFocusableComponent(rpPanel);

       readmeButton = new JButton(textSource.getI18NText("%h00.4",
							 "Show ReadMe"));
       readmeButton.addActionListener(this);
       readmeButton.addKeyListener(this);
       readmeButton.setNextFocusableComponent(rpPanel);
       buttonPanel.add(readmeButton);

       topPanel.add(buttonPanel, BorderLayout.SOUTH);
       getContentPane().add(topPanel,BorderLayout.NORTH);

       JPanel bottomPanel = new JPanel(new BorderLayout());
       bottomPanel.setBorder(BorderFactory.createEtchedBorder());
       statusLabel = new JLabel(textSource.getI18NText(TextKeys.HELP,
						       "Help"));
       bottomPanel.add(statusLabel,BorderLayout.NORTH);

       statusPanel = new JPanel();
       statusCardLayout = new CardLayout();
       statusPanel.setLayout(statusCardLayout);
 
       helpArea = new JEditorPane();
       helpArea.setContentType("text/html");
       helpArea.setEditable(false);
       statusPanel.add(new JScrollPane(helpArea),"HELP");


       statusArea = new JTextArea(6,30);
       statusArea.setEditable(false);
       statusArea.setLineWrap(true); 
       statusArea.setWrapStyleWord(true); 
       statusArea.setForeground(Color.red);
       statusPanel.add(new JScrollPane(statusArea),"STATUS");

       helpDisplayListener = new GenHelpDisplayListener(helpArea);

       bottomPanel.add(statusPanel, BorderLayout.CENTER);
       getContentPane().add(bottomPanel, BorderLayout.CENTER);
       showHelp(true);
       }

    /**
     * Initializes the response panel(s), from an
     * XML file.
     * We pass the name of the XML file, which was provided on the
     * command line to the main method.
     */
   public boolean initPanels(String xmlFileName, boolean bTrace)
       {
       boolean bOk = true;
       try 
	   {
	   XmlToUiBuilder parser = new XmlToUiBuilder(xmlFileName,null,
						      textSource, masterTable,
						      "default",
						      homeDirectory);
	   parser.setPkgPrefix("com.grs.dragon.installer.");
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
	       else
		   {
		   dPanel.setPanelSize(rpSize);
		   dPanel.doPanelLayout();
		   rpPanel.add(dPanel,dPanel.getName());
	           }
	       // have the panel set a mouse enter listener on all its
	       // components.
	       dPanel.setMouseListener(helpDisplayListener);

	       // NOTE: This application will assume that 
	       // panels have names which indicate the order in
	       // which they should be displayed, e.g.
	       // "^1", "^2", etc. If panel Ids do not follow
	       // this convention, the application will not work
	       // correctly.
	       // Also, all fields must have unique Ids, across
	       // all the panels in the installer application
	       }
	   }
       /* If a SN was passed in, then skip the SN screen */
       if (passedSN == null)
           {
           showPanel("^1");
           panelIndex = 1;
           }
       else
           {
           showPanel("^2");
           panelIndex = 2;
           }
       return bOk;
       }

      /**
       * Display a specific panel, by ID, under program control.
       * @param panelId  Id of panel to display
       * @returns true if panel found, false if not.
       */
    protected boolean showPanel(String panelId)
        {
        boolean bFoundPanel = false;
        DragonPanel panel = (DragonPanel) masterTable.get(panelId);
	if (panel == null)  // we're done
	   {
	   return bFoundPanel;
	   }
	bFoundPanel = true;
        currentPanel = panel;
        Dimension panelSize;
	rpPanel.setPreferredSize(rpSize);
	cardLayout.show(rpPanel,panel.getName());
	panel.setAllToDefaults();
	return bFoundPanel;
	}

      /**
       * Switch from status to help or vice versa.
       * @param bFlag If true, show Help, if false, Status
       */
    protected void showHelp(boolean bFlag)
        {
	if (bFlag)
	    {
	    statusCardLayout.show(statusPanel,"HELP");
	    statusLabel.setText(textSource.getI18NText(TextKeys.HELP,
						       "Help"));
	    }
	else
	    {
	    statusCardLayout.show(statusPanel,"STATUS");
	    statusLabel.setText(textSource.getI18NText(TextKeys.STATUS,
						       "Status"));
	    }
	}

      /**
       * Method from ActionListener
       */
    public void actionPerformed(ActionEvent e)
        {
	boolean bShown = true;
	Object source = e.getSource();
	if (source.equals(continueButton))
	    {
	    // save data from current panel, then
	    // see if there is another panel to display
	    if (currentPanel != null)
	        {
		DragonField badField = currentPanel.checkFieldValidity();
		if (badField != null)
		    {
		    Toolkit.getDefaultToolkit().beep();
		    badField.getValidator().displayLastError();
		    badField.requestFocus();
		    return;
		    }
		badField = currentPanel.checkRequiredFields();
		if (badField != null)
		    {
		    GenErrorDisplay errDisp = (GenErrorDisplay)
		      ApplicationManager.getErrorDisplay();
		    String missing = textSource.getI18NText(
		       TextKeys.MISSINGREQUIRED,"Missing required field");
		    errDisp.showError(null,missing + "\n" 
                                       + badField.getLabelText());
		    badField.requestFocus();
		    return;
		    }
		currentPanel.saveValues();
		}
	    panelIndex += 1;
	    String newId = "^" + String.valueOf(panelIndex);
	    bShown = showPanel(newId);
            if (!bShown)  // last panel
	        {
		continueButton.setEnabled(false);
		readmeButton.setEnabled(false);
		doInstallation();
		}
	    }
	else if (source.equals(backButton))
	    {
	    // back up one panel. Do not save data
            if (panelIndex == 1)
	        // no back!
	        return;
	    panelIndex -= 1;
	    String newId = "^" + String.valueOf(panelIndex);
	    bShown = showPanel(newId);
	    }
	else if (source.equals(cancelButton))
	    {
	    winMonitor.setConfirm(false);
            winMonitor.windowClosing(null);
	    czSpath="cancel";
	    }
	else if (source.equals(readmeButton))
	    {
	    showReadMe();
	    }
	if ((panelIndex == 1) || (!bShown) || (bSuccess))
	    backButton.setEnabled(false);
	else 
	    backButton.setEnabled(true);
	}

      /**
       * Methods from key listener
       */
    //********************************************************************
      /**
       * Methods from the KeyListener interface.
        */
    public void keyPressed(KeyEvent ke)
        {
	int code = ke.getKeyCode();
	Object source = ke.getSource();
	switch (code)
	    {
	    case KeyEvent.VK_KP_DOWN:
	    case KeyEvent.VK_DOWN:
	    case KeyEvent.VK_KP_RIGHT:
	    case KeyEvent.VK_RIGHT:
	      if (source.equals(cancelButton))
		 {
		 if (currentPanel != null)
		     currentPanel.setFirstFocus();
		 }
	      else
		 {
		 ke.setKeyCode(KeyEvent.VK_TAB);
		 }
	      break;
	    case KeyEvent.VK_KP_UP:
	    case KeyEvent.VK_UP:
	    case KeyEvent.VK_KP_LEFT:
	    case KeyEvent.VK_LEFT:
	      ke.setKeyCode(KeyEvent.VK_TAB);
	      ke.setModifiers(InputEvent.SHIFT_MASK);
	      break;
	    default:
	        break;
	    }
	}

    public void keyReleased(KeyEvent ke)
        {
	}

    public void keyTyped(KeyEvent ke)
        {
	}

    protected void doInstallation()
        {
	showHelp(false);
	cancelButton.setEnabled(false);
	updateStatusArea(textSource.getI18NText("%h01.8000",
			         "Proceeding with installation..."));
        // check space
	String basePath = (String) DragonPanel.fieldValueTable.get("SYSPATH");
        String samplePath = (String) DragonPanel.fieldValueTable.get("SAMPPATH");
	basePath = upcaseDriveLetter(basePath);
	samplePath = upcaseDriveLetter(samplePath);
        // samplePath will be null if the user indicated that
	// s/he did not want the sample imagery
	updateStatusArea(textSource.getI18NText("%h01.8001",
			         "Reading file list"));

	fileManager = new InstallFileManager(
               this,fileListFile, basePath, samplePath);
        if (!fileManager.isInitialized())
	     {
	     errorAndRestart(fileManager.getLastErrorMessage());
	     return;
	     }
	cleanCallback.setFileManager(fileManager);
	updateStatusArea(textSource.getI18NText("%h01.8002",
			         "Checking system disk space"));
        boolean bOk = fileManager.checkMainSpace();
	if (!bOk)
	     {
	     errorAndRestart(fileManager.getLastErrorMessage());
	     return;
	     }
        if ((samplePath != null) &&
            (samplePath.length() > 0))
	     {
	     updateStatusArea(textSource.getI18NText("%h01.8003",
			         "Checking sample data disk space"));

	     bOk = fileManager.checkSecondarySpace();
	     if (!bOk)
	         {
		 errorAndRestart(fileManager.getLastErrorMessage());
		 return;
	         }
	     }
	updateStatusArea(textSource.getI18NText("%h01.8004",
			         "Copying files"));
        fileManager.copyFiles();
	// now we need to wait for copyCompleted method to be called
	}

      /**
       * This is a callback that will be executed by the
       * InstallFileManager when the file copying is complete - either
       * successfully or in error.
       * @param bStatus If true, file copying completed successfully,
       *               if false, an error occurred.
       */
    public void copyCompleted(boolean bStatus)
        {
	if (bVerbose)
	    {
	    System.out.println("Installer::copyCopyCompleted with status "
                    + bStatus);
	    }
	if (!bStatus)
	    {
	    errorAndRestart(fileManager.getLastErrorMessage());
	    return;
	    }
	// check files for corruption and presence`
	updateStatusArea(textSource.getI18NText("%h01.8005",
			         "Checking file integrity"));
        fileManager.checkIntegrity();
        // now we need to wait for the chkCompleted method to be called.
	}

      /**
       * This is a callback that will be executed by the
       * InstallFileManager when the file integrity checking is complete - 
       * either successfully or in error.
       * @param bStatus If true, file copying completed successfully,
       *               if false, an error occurred.
       */
    public void chkCompleted(boolean bStatus)
        {
	if (bVerbose)
	    System.out.println("Installer::chkCompleted (en) status="
			       +bStatus);
	if (!bStatus)
	    {
	    errorAndRestart(fileManager.getLastErrorMessage());
	    return;
	    }
	boolean bOk = updateConfigFile("chkCompleted");
        if (!bOk)
	    return;
	//String cdSn = (String) DragonPanel.fieldValueTable.get("SN");
	driverInstallCompleted(true);
	if (bVerbose)
	    System.out.println("Installer::chkCompleted (ex)");
	}

      /**
       * This is a callback that will be executed by the
       * InstallFileManager when the key driver installation
       * is complete - either successfully or in error.
       * @param bStatus If true, file copying completed successfully,
       *               if false, an error occurred.
       */
    public void driverInstallCompleted(boolean bStatus)
        {
	if (bVerbose)
	    System.out.println("Installer::driverInstallCompleted (en) status="
			       +bStatus);
	if (!bStatus)
	    {
	    errorAndRestart(fileManager.getLastErrorMessage());
	    return;
	    }
	boolean bOk = updateConfigFile("driverInstallCompleted");
        if (!bOk)
	    return;
	winMonitor.setCleanupCallback(null);
        String exitQuery = textSource.getI18NText("%h01.9905","Exit Setup?");
	winMonitor.setMessageString(exitQuery);
	bSuccess = true;
	if (bVerbose)
	    System.out.println("Installer::driverInstallCompleted (ex)");
 	// reset so we don't delete the installed files if the user
 	// attempts to exit.
	//reportSuccess();   // now called from setup
	}

      /**
       * Allow other apps to add info to the status area.
       */
    public void updateStatusArea(String newText)
        {
	int len = statusArea.getText().length();
	statusArea.setText(statusArea.getText() + "\n" +
			   newText);
        statusArea.setCaretPosition(statusArea.getText().length() - 1);
	}

    public void showFinishedStatus(String newText)
        {
	statusArea.setForeground(Color.black);
	updateStatusArea(newText);
        }

      /**
       * Factorization: update the config file with paths and
       * language. Assume that a copy of the config file was
       * placed in SPATH.
       * @param whence		for tracing: name of origin fn
       * @returns true if Ok, false if error
       */
    protected boolean updateConfigFile(String whence)
        {
	if (bVerbose)
	    {
	    System.out.println("Installer::"+whence
			       +" about to update config file.");
	    }

	Date now = new Date();
        int day = now.getDate();
	int month = now.getMonth();
	int year = now.getYear() + 1900;
	StringBuffer dateBuf = new StringBuffer(20);
        dateBuf.append(String.valueOf(year) + "-");
	dateBuf.append(monthNames[month] + "-");
	if (day < 10) 
	    dateBuf.append("0");
	dateBuf.append(String.valueOf(day));
			       
        String spath = (String) DragonPanel.fieldValueTable.get("SYSPATH");
        String kpath = (String) DragonPanel.fieldValueTable.get("TEMPPATH");
        String dpath = (String) DragonPanel.fieldValueTable.get("DPATH");
        String wpath = (String) DragonPanel.fieldValueTable.get("WPATH");
        // String language = (String) DragonPanel.fieldValueTable.get("LANGUAGE");
	//String keySn = (String) DragonPanel.fieldValueTable.get("KEY");
	String cdSn = null;
        if (passedSN != null)
            cdSn = passedSN;
        else
	    cdSn = (String) DragonPanel.fieldValueTable.get("SN");
	
	if ((kpath == null) || (dpath == null) ||
	    (spath == null) || (wpath == null) ||
	    (language == null))
	     {
             String msg = textSource.getI18NText("%h01.9906",
                           "Error 100: Missing property values - cannot continue");
	     if (bVerbose)
		 System.out.println("Installer::UpdateConfigFile error.");
	     errorAndRestart(msg);
	     return false;
	     }
	kpath = upcaseDriveLetter(kpath);
	File tmpDir = new File(kpath);
	if (!tmpDir.exists())
	     tmpDir.mkdirs();
	boolean bOk = fileManager.checkTempSpace(kpath);
	if (!bOk)
	     {
	     if (bVerbose)
		 System.out.println("Installer::UpdateConfigFile error.");
	     errorAndRestart(fileManager.getLastErrorMessage());
	     return false;
	     }
        ConfigFileProcessor newCfgProcessor = 
               new ConfigFileProcessor(spath);
	if (!cfgProcessor.isInitialized())
	     {
             String msg = textSource.getI18NText("%h01.9907",
                           "Error 101: Cannot find DRAGON.CFG file in %1",
                           new String[] {spath});
	     if (bVerbose)
		 System.out.println("Installer::UpdateConfigFile error.");
	     errorAndRestart(msg);
	     return false;
	     }

        int level = FLOAT_PRODUCT;
	String levelString = "OPEN";
        czSpath = (String) DragonPanel.fieldValueTable.get("SYSPATH");
	newCfgProcessor.setAttributeValue("LEVEL",levelString);
	newCfgProcessor.setWpath(wpath);                
	newCfgProcessor.setDpath(dpath);                
	newCfgProcessor.setKpath(kpath);                
	newCfgProcessor.setSpath(spath);                
	newCfgProcessor.setCpath(dpath);                
	newCfgProcessor.setCountry(selectedLanguage);        
        newCfgProcessor.setAttributeValue("Installed",dateBuf.toString());
        newCfgProcessor.setAttributeValue("InstallTime",String.valueOf(now.getTime()));
        /**
	if (keySn != null)
	    newCfgProcessor.setAttributeValue("Key",keySn);
	else
	    newCfgProcessor.setAttributeValue("Key","NONE");
	**/
        newCfgProcessor.setAttributeValue("SN",cdSn);
 	newCfgProcessor.writeNewFile();
	File newDir = new File(dpath);
	if (!newDir.exists())
	     newDir.mkdirs();
	newDir = new File(wpath);
	if (!newDir.exists())
	     newDir.mkdirs();
	if (bVerbose)
	    {
	    System.out.println("Installer::UpdateConfigFile (ex)");
	    }
	return true;
	}

      /**
       * Display the read me file in a separate thread.
       */
    protected void showReadMe()
        {
	ReadMe htmlDisplay = new ReadMe();
	htmlDisplay.start();
	}

      /**
       * Set the location of the window to be centered on the screen.
       */
    public void centerWindow()
        {
	Toolkit tk = Toolkit.getDefaultToolkit();
	Dimension ss = tk.getScreenSize();
	Dimension mySize = getSize();
	int x = (ss.width - mySize.width)/2;
	int y = (ss.height- mySize.height)/2;
	setLocation(x,y);
	}

   public boolean isVerbose()
       {
       return bVerbose;
       }    

   public void setVerbose(boolean flag)
       {
       bVerbose = flag;
       }    

   /**
    * utility function takes a path and if it has a drive
    * letter, returns the string with the drive letter changed
    * to upper case.
    * @param path   Path to be checked and modified
    * @return Path with upper case drive letter (if relevant)
    *         Will return null if passed path is null.
    */
   private String upcaseDriveLetter(String path)
      {
      if (path == null)
          return path;
      StringBuffer temp = new StringBuffer();
      int colonPos = path.indexOf(":");
      if (colonPos > 0)
	 {
	 temp.append(path.substring(0,colonPos).toUpperCase());
	 temp.append(path.substring(colonPos));
         }
      else
	 {
	 temp.append(path);
	 }
      return temp.toString();
      }

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

      //**************************************************************
      /**
       * Main method, sets application running.
       */
    public static String main(String[] argv)
        {
	String panelXmlFile = null;
	String fileListFile = null;
	String productString = null;
        String serialNum = null;
        boolean bVerbose = false;
	//long memory = Runtime.getRuntime().totalMemory();
	//System.out.println("total memory=" + memory);
	if (argv.length < 3)
	    {
	    System.out.println(
		  "USAGE: java Installer <xmlFile> <fileListFile> <productString>");
	    System.exit(0);
            }
	if ((argv.length > 3) && (argv[3].toUpperCase().startsWith("-V")))
	    {
	    bVerbose = true;
	    }
        if (bVerbose)
            {
	    System.out.println("argv length is " + argv.length);
	    for (int i = 0; i < argv.length; i++)
		System.out.println("argument " + i + " is " + argv[i]);
	    }
	if ((argv.length > 4) && (argv[4].toUpperCase().startsWith("G")))
	    {
	    serialNum = argv[4];
            int pos = serialNum.indexOf(" ");
            if (pos > 0)
		serialNum = serialNum.substring(0,pos);
	    if (bVerbose)
	        System.out.println("Got SN from key: "+serialNum);
	    }
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
   	    {
	    System.out.println("Error setting look and feel");
	    }
	String osName = System.getProperty("os.name");
//	System.out.println("OS name is '" + osName + "'");
	if (
	    (osName.compareTo("Windows 2000") != 0) 
            && (! osName.startsWith("Windows NT")) // Vista gives 'Windows NT (unknown)'
            && (osName.compareTo("Windows XP") != 0)
            && (osName.compareTo("Windows 7") != 0))
	    {
	    JOptionPane.showMessageDialog(null,
			    "DRAGON/ips requires Windows 2000, XP, Vista, or Windows 7 but got '"+osName+"' \nInstallation will proceed but the software may not work correctly",
			    "Unsupported Operating System",
			    JOptionPane.WARNING_MESSAGE);
	    }
        //Splash splashScreen = new Splash("banner.jpg",255,255,255);
	//splashScreen.setVisible(true);
	//try {Thread.sleep(2000); } catch (InterruptedException ie) {};
	panelXmlFile  = argv[0];
	fileListFile = argv[1];
        productString = argv[2];
	//System.out.println("Panelfile is " + panelXmlFile);
	//System.out.println("Filelist is " + fileListFile);
	//System.out.println("productString is " + productString);
	install = new Installer(panelXmlFile,
					  fileListFile,
					  false,
					  serialNum,
					  productString);
	if (bVerbose)
	    {
	    install.setVerbose(true);
	    System.out.println("Setting verbose flag in Installer class");
	    }
 
	//install.centerWindow();
	//install.setVisible(true);
	//while(czSpath == null)
	//    try {Thread.sleep(1000); } catch (InterruptedException ie) {};
	return czSpath;
	}

       /** 
        * Separate the initial setup of the Installer instance,
        * from the display of the UI and actual installation process.
        */ 
    public static String showInstaller()
	{
	install.centerWindow();
	install.setVisible(true);
	while(czSpath == null)
	    {
	    try {Thread.sleep(1000); } catch (InterruptedException ie) {};
	    if (install.bVerbose)
		System.out.println("Installer::showInstaller loop czSpath="
				   +czSpath);
	    }
	if (install.bVerbose)
	    System.out.println("Installer::showInstaller (ex) czSpath="
			       +czSpath);
	return czSpath;
        }

      /**
       * Report successful install, wait for
       * user to click Ok. This is now called from the C++
       * setup program.
       */
    public static void reportSuccess()
        {
        if (ApplicationManager.isMessageDialogVisible())
	     return;
	String exitString = 
	    ApplicationManager.getTextSource().getI18NText("%h01.9009","Exit");
        String messageString = 
            ApplicationManager.getTextSource().getI18NText("%h01.9999",
	   "DRAGON has been installed successfully. "
	   + "To run DRAGON, click on the Desktop icon, or select it from"
	   + " the Start Menu/Programs/Dragon folder.");

	/* 7/4/05 Just give a message in the scrolling area, don't
         * bring up a dialog.
	 */
	install.showFinishedStatus(messageString);

	//JOptionPane donePane = new JOptionPane(messageString,
	//			      JOptionPane.INFORMATION_MESSAGE,
	//			      JOptionPane.DEFAULT_OPTION);
	install.readmeButton.setEnabled(true);
	install.cancelButton.setText(exitString);
	install.cancelButton.setEnabled(true);
        //donePane.setValue(null);
	//JDialog dlg = donePane.createDialog(this,null);
	//dlg.setVisible(true);
	//Object val = donePane.getValue();
        }

      /**
       * Display error and then exit after a delay.
       * 6/2007 - make public and static so that setup can call the function.
       */
    public static void errorAndRestart(String message)
        {
	if (install.bVerbose)
	   {
	   System.out.println("errorAndRestart - message is " +
                              message);
           }
        ApplicationManager.getErrorDisplay().showError(TextKeys.ERROR,
							message);
        if (install.cleanCallback != null)
	    install.cleanCallback.executeCallback(null); 
	try {Thread.sleep(2000); } catch (InterruptedException ie) {};
	System.exit(1);
        }

      /** retrieve the SPATH (where things were installed) or null
       */
    public static String getSpath()
	{ return czSpath; }
       
      /**
       * Inner class to put the display of the readme file into 
       * a separate thread,
       * so that the UI doesn't freeze while we are doing this task
       */
    class ReadMe extends Thread
        {
	  /**
	   * Main thread method invokes the registered browser
	   */
	public void run() 
            {
	    boolean bError = false;
	    String readmeFile = homeDirectory + File.separator + "readme.html";
	    StringBuffer cmd = new StringBuffer(512);
	    String shellCmd = System.getProperty("SHELL","cmd");
	    cmd.append(shellCmd + " /c " + readmeFile);
	    try {
	        Process proc = 
		      Runtime.getRuntime().exec(cmd.toString());
	        }
	    catch (IOException ioe)
	        {
		System.out.println(ioe.getMessage());
	        }
	    }         // end run
        }  // end ReadMe class
    }
