/**
 *  DragonFileChooser 
 *
 *  Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 *  Created by Sally Goldin, 3/22/2001
 *
 *  $Id: DragonFileChooser.java,v 1.20 2007/02/15 11:16:55 goldin Exp $
 *  $Log: DragonFileChooser.java,v $
 *  Revision 1.20  2007/02/15 11:16:55  goldin
 *  Add initializer to clear multi-select file boxes when we enter a panel
 *
 *  Revision 1.19  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.18  2006/12/28 10:34:21  goldin
 *  Complete implementation of multifile selection control and file chooser
 *
 *  Revision 1.17  2006/12/25 10:48:37  goldin
 *  Begin implementation of multi-select file control
 *
 *  Revision 1.16  2006/12/10 06:26:59  goldin
 *  Fine tune help behavior - cancel if the user starts typing or brings up a file chooser
 *
 *  Revision 1.15  2005/08/13 08:40:57  goldin
 *  Fix null ptr bug due to trace statement
 *
 *  Revision 1.14  2005/08/03 04:42:26  goldin
 *  Add tracing
 *
 *  Revision 1.13  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.12  2004/09/26 12:38:20  goldin
 *  Fix FileChooser bugs
 *
 *  Revision 1.11  2002/09/25 17:22:43  goldin
 *  Don't append default path to partial filename before calling file chooser
 *
 *  Revision 1.10  2002/09/18 17:30:05  goldin
 *  Fix nullptr bug
 *
 *  Revision 1.9  2002/09/13 23:56:33  goldin
 *  Continue enhancements to file box behavior
 *
 *  Revision 1.8  2002/08/31 00:03:23  goldin
 *  continue major redesign of FileChooser
 *
 *  Revision 1.7  2002/08/27 20:04:12  goldin
 *  convert filechooser to potentially using multiple file types
 *
 *  Revision 1.6  2002/08/22 14:56:52  goldin
 *  Work on appearance and behavior of VP Filechooser
 *
 *  Revision 1.5  2002/06/28 15:28:00  goldin
 *  Implement 'Details' in file chooser
 *
 *  Revision 1.4  2002/05/16 13:17:37  goldin
 *  Factorizations to support ViewFileChooser subclass
 *
 *  Revision 1.3  2002/04/02 00:13:28  goldin
 *  Put in infrastructure for testing for file overwrite warning flag
 *
 *  Revision 1.2  2002/03/06 20:59:36  goldin
 *  Add SAVE item
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.26  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.25  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.24  2001/10/30 18:06:36  goldin
 *  Set default to last path used if available
 *
 *  Revision 1.23  2001/10/17 10:29:36  goldin
 *  Modify to use ApplicationManager to get error display, etc.
 *
 *  Revision 1.22  2001/10/08 11:56:15  goldin
 *  Always Disable Details for Beta
 *
 *  Revision 1.21  2001/10/05 11:05:34  goldin
 *  Separate Dialog from callback to allow reuse by Viewport
 *
 *  Revision 1.20  2001/07/18 15:25:30  goldin
 *  Working to fix problems with handling of 'current' color scheme
 *
 *  Revision 1.19  2001/06/13 14:12:48  goldin
 *  Move buttons to be dialogwide, add ability to have file fields in Qry boxes
 *
 *  Revision 1.18  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.17  2001/06/05 19:36:21  goldin
 *  Add Tracer; investigate file dialog bug
 *
 *  Revision 1.16  2001/05/31 17:10:53  goldin
 *  Work on problems with file dlg; esp. handling of empty drives
 *
 *  Revision 1.15  2001/05/30 15:32:53  goldin
 *  Work on getting fn keys to work in file dialog, main window w/ no RP
 *
 *  Revision 1.14  2001/05/07 12:06:52  goldin
 *  Fix bugs in path handling
 *
 *  Revision 1.13  2001/04/24 14:14:20  goldin
 *  Improve behavior and appearance of file and font choosers
 *
 */

package com.grs.gui;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/**
 * This class implements the view component for our customized file dialog. 
 * We need a custom version for internationalization
 * purposes. Also, we need some additional information not 
 * included in the standard FileChooser. 
 * <p>
 * The constructor for this class creates the dialog, but does
 * not display it. The <i>chooseFile</i> method displays the dialog 
 * and handles user input.
 */
public class DragonFileChooser extends JDialog implements ActionListener,
                                                          KeyListener
    {
    /** keep track of whether any choose is up */
    protected static boolean bChooserShowing = false;

    /** Reference to the directory tree on the left. */
    protected DragonDirTree dirTree = null;

    /** Reference to the file list on the right. */
    protected DragonFileList fileList = null;

    /** Reference to text source for translated labels. */
    protected I18NTextSource textSource = null;

    /** Reference to the model that holds the chooser state. */
    protected DFileChooserModel chooserModel = null;

    /** If true, this is a paths-only file chooser */
    protected boolean bForPaths = false;

    /** If true, this is an input file chooser (readFiles); 
     *  otherwise it is an output file chooser. 
     */
    protected boolean bReadFile = true;

    /** Buttons */
    protected JButton okButton = null;
    protected JButton cancelButton = null;
    protected JButton detailsButton = null;
    protected JButton refreshButton = null;

    /**
     * Allow an external class to discover if Ok or cancel
     * dismissed the box.
     */
    protected boolean bOkPressed = false;

      /* Lets us know the context for calling this.
       */
    protected boolean bFrameParent = false;

    /** Parent Window for dialog. */
    protected Window parent = null;

    /** File to be returned if user clicks on OK. If user clicks on Cancel, 
     * null is returned. 
     */
    protected File retFile = null;

    /**
     * Array of files to be returned if the user clicks on OK
     * for multiple selection.
     */
    protected File multiRetFile[] = null;

    /* If this is true, we can select multiple files
     * and we will have an area to display them.
     */
    protected boolean bMultiSelect = false;

    //*************************************************

    /**
     * Constructor builds the UI - frame parent
     * @param parent    Parent frame, used for centering.
     * @param textSource Text source for translated strings,
     * @param bForPaths  If true, this is a paths-only dialog. and 
     *                   will not have a file list.
     * @param bReadFile  If true, this chooser selects input files.
     * @param bMultiSelect If true, we can select multiple files.
     */
    public DragonFileChooser(Frame parent, 
			     I18NTextSource textSource, 
			     boolean bForPaths, boolean bReadFile,
			     boolean bMultiSelect)
        {
        super(parent, true);
	this.parent = (Window) parent;
        this.textSource = textSource;
        this.bForPaths = bForPaths;
        this.bReadFile = bReadFile;
	this.bMultiSelect = bMultiSelect;
	bFrameParent = true;
	createChooser();
	}

    /**
     * Alternative constructor uses a dialog parent parent
     * @param parent    Parent dialog, used for centering.
     * @param textSource Text source for translated strings,
     * @param bForPaths  If true, this is a paths-only dialog. and 
     *                   will not have a file list.
     * @param bReadFile  If true, this chooser selects input files.
     * @param bMultiSelect If true, we can select multiple files.
     */
    public DragonFileChooser(Dialog parent, 
			     I18NTextSource textSource, 
			     boolean bForPaths, boolean bReadFile,
			     boolean bMultiSelect)
        {
        super(parent, true); // make it modal
        this.parent = (Window) parent;
        this.textSource = textSource;
        this.bForPaths = bForPaths;
        this.bReadFile = bReadFile;
	this.bMultiSelect = bMultiSelect;
	createChooser();
	}


      /**
       * Factorization - creates the file chooser UI
       */
    protected void createChooser()
        {
        JPanel mainPanel = new JPanel(
            new BorderLayout());
        JPanel buttonPanel = new JPanel(
            new FlowLayout());
        String label = textSource.getI18NText(TextKeys.OK, "OK");
        okButton = new JButton(label);
        okButton.addActionListener(this);
        okButton.addKeyListener(this);
        buttonPanel.add(okButton);
        label = textSource.getI18NText(TextKeys.CANCEL, "CANCEL");
        cancelButton = new JButton(label);
        cancelButton.addActionListener(this);
        cancelButton.addKeyListener(this);
        buttonPanel.add(cancelButton);
        if ((!bForPaths) && (bReadFile))
            {
	    label = textSource.getI18NText(TextKeys.DETAILS, "Details");
	    detailsButton = new JButton(label);
	    detailsButton.addActionListener(this);
	    detailsButton.addKeyListener(this);
            buttonPanel.add(detailsButton);
            }
        label = textSource.getI18NText(TextKeys.REFRESH, "REFRESH");
        refreshButton = new JButton(label);
        refreshButton.addActionListener(this);
        refreshButton.addKeyListener(this);
        buttonPanel.add(refreshButton);
        JPanel workPanel = new JPanel();
        if (!bForPaths)
            {
            dirTree = new DragonDirTree(this, fileList, textSource);
            if (bMultiSelect)
                fileList = new DragonMultiFileList(this, bReadFile, textSource);
            else
                fileList = new DragonFileList(this, 
						   bReadFile, textSource);
            workPanel.setLayout(
                new BorderLayout());
            workPanel.add(new JSplitPane(
                             JSplitPane.HORIZONTAL_SPLIT,
			     dirTree,fileList), BorderLayout.CENTER);
            }
        else
            {
            dirTree = new DragonDirTree(this, null, textSource);
            workPanel.setLayout(
                new BorderLayout());
            workPanel.add(dirTree, BorderLayout.CENTER);
            workPanel.setPreferredSize(
                new Dimension(200, 400));
            }
        mainPanel.add(workPanel, BorderLayout.CENTER);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);
        getContentPane().add(mainPanel, BorderLayout.CENTER);
        setSize(450, 450);
        pack();
        if (bMultiSelect)
	    chooserModel = new DFileMultiChooserModel(this, 
						      dirTree, fileList);
	else
	    chooserModel = new DFileChooserModel(this, dirTree, fileList);
        }


	/**
	 * Factorization of actionPeformed, for single select situation.
	 */
    protected void processSingleSelection()
	{
	String currentName = chooserModel.getCurrentFilename();
	String currentPath = chooserModel.getCurrentPath();
	Tracer.outputTraceMessage(
		   "DragonFileChooser::actionPerformed, currentName is " + 
		   currentName +
		   " and currentPath is " + currentPath);
	if (currentName != null)
	    {
	    if ((currentName.length() > 0) && 
		(!currentName.startsWith("=")) && 
		(!currentName.startsWith("(")))
		{
		File selectedFile = 
		    new File(currentPath, currentName);
		DFileType fileType = 
		    chooserModel.getFileTypeForFile(selectedFile);
		if (fileType != null)
		    fileType.addUsedFile(selectedFile.getPath());
		}
	    if ((currentName.startsWith("=")) || 
		(currentName.startsWith("(")))
		{
		Tracer.outputTraceMessage(
                       "DragonFileChooser::actionPerforme, Thinks current name starts with paren??");
		currentPath = "";
		}
	    }
	if ((currentPath != null) && (currentPath.length() > 0))
	    {
	    DFileType.PATH.addUsedFile(currentPath);
	    chooserModel.setLastSelectedPath(currentPath);
	    }
	if (currentName != null)
	    retFile = new File(currentPath, currentName);
	else
	    retFile = new File(currentPath);
	}


    /** Method from actionListener. Processes Ok/Cancel/Details buttons. */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
        if (source == okButton)
            {
            if (!chooserModel.validateFile(null, null, bReadFile, false, true))
                {
                return;
                }
	    if (bMultiSelect)
                {
                } 
            else
                {
		processSingleSelection();
                }
	    bOkPressed = true;
            setVisible(false);
	    bChooserShowing = false;
            }
        else if (source == cancelButton)
            {
            retFile = null;
            setVisible(false);
	    bChooserShowing = false;
            }
        else if (source == refreshButton)
            {
            dirTree.refresh();
	    if (fileList != null)
	        {
                fileList.populateFiles(null);
		}
            }
        else if (source == detailsButton)
            {
	    Callback cb = 
              chooserModel.getFileTypeForCurrentFile().getDetailCallback();
	    if (cb != null)  // it shouldn't be - details only enabled
	                     // if there's a callback
	        {
		DFixedText dummyField = new DFixedText("dummy","dummy");
		String currentName = chooserModel.getCurrentFilename();
		String currentPath = chooserModel.getCurrentPath();
		if ((currentName != null) && (currentPath != null) &&
		    (currentName.length() > 0) && 
		    (!currentName.startsWith("=")) && 
		    (!currentName.startsWith("(")))
		    {
		    File temp = new File(currentPath, currentName);
		    if (temp.exists())
		        {
			dummyField.setLabelText(temp.getAbsolutePath());
			dummyField.setParentComponent(this);
			cb.executeCallback(dummyField);
		        } // end if temp exists
		    }// end if name and path not null && not special
		}
            }
        }

      /**
       * Methods from the KeyListener interface.
       */
    public void keyPressed(KeyEvent ke)
        {
	int code = ke.getKeyCode();
	switch (code)
	    {
            case KeyEvent.VK_F3:
                if ((detailsButton != null) &&
		    (detailsButton.isEnabled()))
		    detailsButton.doClick();
                ke.consume();
		break;
	    case KeyEvent.VK_F1:
	        if (okButton.isEnabled())
		    okButton.doClick();
                ke.consume();
		break;
	    case KeyEvent.VK_F10:
	    case KeyEvent.VK_ESCAPE:
                cancelButton.doClick();
		ke.consume();
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


    /**
     * Primary file chooser method. Displays the dialog and collects 
     * user input. Returns the selected filename, with
     * path, or null if the user clicked cancel (or clicked OK with 
     * nothing selected.
     * @param fileTypes  Array identifying the types of file desired
     * @param memoryFiles String of concatenated "special file names" 
     *                    currently available and legal for this choice.
     * @param partialName Current contents of the associated field, used 
     *                    as a filter pattern
     * @param title      String to use as title for the dialog. This is 
     *                   usually the label for the control.
     * @param defaultValue  If non-null, file box should come up with 
     *                   this file selected. An explicit default takes
     *                   precedence over a partial file name filter.
     * @return selected File object combining path & name, or null 
     *          if canceled or nothing selected.
     */
    public File chooseFile(DFileType[] fileTypes, String[] memoryFiles, 
			   String partialName, String title, 
			   String defaultValue)
        {
	DriveTester.setDoTest(true);
        setupChooserDisplay(fileTypes, memoryFiles,
			    partialName, title, defaultValue);
        setLocationRelativeTo(parent);
	if (!bForPaths)
	    fileList.setInitialFocus();
	bChooserShowing = true;
        setVisible(true);
	Tracer.outputTraceMessage("DragonFileChooser::chooseFile About to return " + ((retFile == null)? "null" : retFile.getAbsolutePath()));

        return retFile;  // set by the actionperformed method
        }

    /**
     * Variant chooser method for use with multiSelect file chooser.
     * Displays the dialog and collects 
     * user input. Returns an array of File objects,
     * or null if the user clicked cancel (or clicked OK with 
     * nothing selected.
     * @param fileTypes   Array identifying the types of file desired
     * @param memoryFiles String of concatenated "special file names" 
     *                    currently available and legal for this choice.
     * @param partialName Current contents of the associated field, used 
     *                    as a filter pattern
     * @param title      String to use as title for the dialog. This is 
     *                   usually the label for the control.
     * @param defaultValue  If non-null, file box should come up with 
     *                   this file selected. An explicit default takes
     *                   precedence over a partial file name filter.
     * @param maxFileCount  Maximum number of files that can be selected.
     * @return selected File object combining path & name, or null 
     *          if canceled or nothing selected.
     */
    public File[] chooseMultiFiles(DFileType[] fileTypes, 
			   String[] memoryFiles, 
			   String partialName, String title, 
			   String defaultValue,
			   int maxFileCount,
			   String[] currentFiles)
        {
	if (!bMultiSelect)
	    throw new RuntimeException("Only multiple-select file choosers support the chooseMultiFiles method!");

	DriveTester.setDoTest(true);
        setupChooserDisplay(fileTypes, memoryFiles,
			    partialName, title, defaultValue);
        ((DFileMultiChooserModel)chooserModel).setMaxAllowedFileCount(maxFileCount);
        ((DFileMultiChooserModel)chooserModel).setSelectedFiles(currentFiles);
        ((DragonMultiFileList) fileList).updateSelectedFileList();   	
        setLocationRelativeTo(parent);
	if (!bForPaths)
	    fileList.setInitialFocus();
	bChooserShowing = true;
        setVisible(true);
        multiRetFile = ((DFileMultiChooserModel)chooserModel).getCurrentFilenameList();
        return multiRetFile;  
        }

    /**
     * Factorization. Pull the "guts" of chooseFile into a 
     * separate method so that it can be called by derived
     * classes that want to use different display or return
     * strategies.
     * @param fileTypes  Array identifying the types of file desired
     * @param memoryFiles String of concatenated "special file names" 
     *                    currently available and legal for this choice.
     * @param partialName Current contents of the associated field, used 
     *                    as a filter pattern
     * @param title      String to use as title for the dialog. This is 
     *                   usually the label for the control.
     * @param defaultValue  If non-null, file box should come up with 
     *                   this file selected. An explicit default takes
     *                   precedence over a partial file name filter.
     */
    protected void setupChooserDisplay(DFileType[] fileTypes, 
				       String[] memoryFiles, 
				       String partialName, String title, 
				       String defaultValue)

        {
        String dPath = ApplicationManager.getReadPath();
	String wPath = ApplicationManager.getWritePath();
        chooserModel.clear();
	retFile = null;
	bOkPressed = false;
        if (fileTypes[0] != DFileType.PATH)
            {
            fileList.setFileTypes(fileTypes, memoryFiles);
            }
        dirTree.setupMostRecentPaths(null); // later send string array of paths
        chooserModel.setFileTypes(fileTypes);
        if (detailsButton != null)
            detailsButton.setEnabled(false);
        okButton.setEnabled(false);
        setTitle(title);
	if (bForPaths)
	     {
	     // no filter patterns for paths
             partialName = null;
	     }
        /****** NOT NOW
	if (partialName != null)
            {
   	    if (fileType.accept(new File(partialName))) 
	    // if this is a full filename, don't use as a pattern
	       {
	       partialName = null;
	       }
	    }
	    *******/
        if ((defaultValue != null) && (!defaultValue.startsWith("(")) &&
            (!defaultValue.startsWith("="))) 
            {
            File tempFile = new File(defaultValue);
            if ((bForPaths) || (tempFile.isDirectory()))
                {
                chooserModel.setCurrentPath(tempFile.getAbsolutePath());
                }
            else
                {
		String msg = 
		      "{ DragonFileChooser: calling setCurrentPath to at A }";
		Tracer.outputTraceMessage(msg,
					  ApplicationManager.getModulePrefix(),
					  ApplicationManager.getTimeOffset());
                chooserModel.setCurrentPath(tempFile.getParent());
                chooserModel.setCurrentFilename(tempFile.getName());
                }
            }
        else if (partialName != null)
            {
	    File tempFile = new File(partialName); 
	    if (tempFile.isDirectory())
	        {
		chooserModel.setCurrentPath(tempFile.getAbsolutePath());
		}
	    else
	        {
	        chooserModel.setPartialName(tempFile.getName());
		String msg = 
		  "{ DragonFileChooser: calling setCurrentPath to at B }";
		Tracer.outputTraceMessage(msg,
					  ApplicationManager.getModulePrefix(),
					  ApplicationManager.getTimeOffset());
		if (tempFile.getParent() != null)
		    chooserModel.setCurrentPath(tempFile.getParent());
                else 
		    chooserModel.setCurrentPathToLast();
		chooserModel.setCurrentFilename(tempFile.getName() + "*");
	        }
            }
	else if ((bReadFile) && (!bForPaths) && (dPath != null))
	    {
            String lastPath = chooserModel.getLastSelectedPath();
	    String msg = 
		  "{ DragonFileChooser: calling setCurrentPath to at C }";
	    Tracer.outputTraceMessage(msg,
				      ApplicationManager.getModulePrefix(),
				      ApplicationManager.getTimeOffset());
            if (lastPath == null)
	        chooserModel.setCurrentPath(dPath);
	    else
	        chooserModel.setCurrentPath(lastPath);
	    }
	else if ((!bReadFile) && (!bForPaths) && (wPath != null))
	    {
	    String msg = 
		  "{ DragonFileChooser: calling setCurrentPath to at D }";
	    Tracer.outputTraceMessage(msg,
				      ApplicationManager.getModulePrefix(),
				      ApplicationManager.getTimeOffset());
	    chooserModel.setCurrentPath(wPath);
	    }
        else
            {
            if (fileList != null)
                {
                fileList.updateView(null, null, null, null);
                }
            dirTree.updateView(null, null);
            }
	if ((partialName == null) && (fileList != null))
	    {
	    fileList.clearFilter();
	    }
	}

    /** Allow external class to clear the model */
    public void clear()
        {
	if (bMultiSelect)
            {
            DragonMultiFileList list = (DragonMultiFileList) fileList;
            list.clear();
            }
	fileList.clearFilter();
	}

    /** Enable or disable details button. */
    public void setDetailsEnabled(boolean flag)
        {
        if (detailsButton != null) 
	    {
	    DFileType currentType = chooserModel.getFileTypeForCurrentFile();
	    if ((currentType != null) && 
	        (currentType.getDetailCallback() != null))
	        detailsButton.setEnabled(flag); 
	    else 
	        detailsButton.setEnabled(false); 
	    }
        }

    /** Enable or disable OK button. This will be managed by the 
     *  DFileChooserModel based on whether a file is selected. 
     */
    public void setOkEnabled(boolean flag)
        {
        okButton.setEnabled(flag);
        }

    public DFileChooserModel getModel()
        {
        return chooserModel;
        }

      /**
       * Was OK pressed?
       */
    public boolean wasOkPressed()
        {
	return bOkPressed;
	}
    
    public boolean hasFrameParent()
        {
	return bFrameParent;
	}

    /* Allow another class to find out if any chooser is up */
    public static boolean isChooserShowing()
        {
	return bChooserShowing;
        } 

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonFileChooser.java,v 1.20 2007/02/15 11:16:55 goldin Exp $ \n";
	}
    }
