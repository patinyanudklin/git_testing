/**
 * DragonFileList
 *
 * Copyright  2001-2007 by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 3/23/2001
 *
 *  $Id: DragonFileList.java,v 1.13 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: DragonFileList.java,v $
 *  Revision 1.13  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.12  2006/12/28 10:34:21  goldin
 *  Complete implementation of multifile selection control and file chooser
 *
 *  Revision 1.11  2006/12/25 10:48:37  goldin
 *  Begin implementation of multi-select file control
 *
 *  Revision 1.10  2005/12/10 09:35:50  goldin
 *  Fix FilenameDocument to allow unicode characters in filenames
 *
 *  Revision 1.9  2005/12/08 09:36:19  goldin
 *  Fix problem of not being able to create thai output files
 *
 *  Revision 1.8  2002/09/19 22:38:17  goldin
 *  Make MRU list longer
 *
 *  Revision 1.7  2002/09/18 17:30:28  goldin
 *  If user supplies valid suffix for any of the filetypes, then use it, don't override
 *
 *  Revision 1.6  2002/09/13 23:56:33  goldin
 *  Continue enhancements to file box behavior
 *
 *  Revision 1.5  2002/09/12 17:21:28  goldin
 *  Work on filter behavior and setting of OK on off focus
 *
 *  Revision 1.4  2002/08/31 00:03:23  goldin
 *  continue major redesign of FileChooser
 *
 *  Revision 1.3  2002/08/28 16:33:05  goldin
 *  Work on merging MRU lists
 *
 *  Revision 1.2  2002/08/27 20:04:12  goldin
 *  convert filechooser to potentially using multiple file types
 *
 *  Revision 1.1  2001/11/16 17:29:21  goldin
 *  Move DragonFileChooser and supporting classes to new general .gui package
 *
 *  Revision 1.16  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.15  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.14  2001/10/17 10:29:37  goldin
 *  Modify to use ApplicationManager to get error display, etc.
 *
 *  Revision 1.13  2001/07/18 15:25:30  goldin
 *  Working to fix problems with handling of 'current' color scheme
 *
 *  Revision 1.12  2001/06/29 17:30:16  goldin
 *  Implemented handing of state info from reply files
 *
 *  Revision 1.11  2001/06/06 15:16:11  goldin
 *  Work on cleaning up event handling in FileChooser; improve tracing
 *
 *  Revision 1.10  2001/06/05 19:36:21  goldin
 *  Add Tracer; investigate file dialog bug
 *
 *  Revision 1.9  2001/05/31 17:10:53  goldin
 *  Work on problems with file dlg; esp. handling of empty drives
 *
 *  Revision 1.8  2001/05/30 15:32:53  goldin
 *  Work on getting fn keys to work in file dialog, main window w/ no RP
 *
 *  Revision 1.7  2001/04/24 14:14:20  goldin
 *  Improve behavior and appearance of file and font choosers
 *
 *  Revision 1.6  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.5  2001/04/06 18:02:54  goldin
 *  Fixing bugs
 *
 *  Revision 1.4  2001/04/04 12:16:55  goldin
 *  Checkpoint of filechooser work; partial name filtering implemented
 *
 *  Revision 1.3  2001/04/03 17:46:43  goldin
 *  Continued work on FileChooser; moved state information into new DFileChooserModel class
 *
 *  Revision 1.2  2001/03/26 17:32:08  goldin
 *  Further work implementing FileChooser
 *
 *  Revision 1.1  2001/03/23 17:01:51  goldin
 *  Initial implementation of file chooser
 *
 */

package com.grs.gui;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.util.*;
import java.io.*;

/**
 * This class is a UI component that presents a tree-structured
 * directory display and allows the user to choose, or to type
 * a path. When a path is entered, the class calls the setCurrentPath
 * method on its parent DragonFileChooser.*/
public class DragonFileList extends JPanel implements ListSelectionListener,
                                                     FocusListener,
                                                     KeyListener,
                                                     ActionListener
    {
    protected static final String[] empties = {"","",""};

      /**
       * Text Field for entering new files. Only on output
       * file choosers
       */
    protected JTextField fileEnterField = null;

      /**
       * Text Field for entering filter strings. Only on
       * input file choosers.
       */
    protected JTextField fileFilterField = null;

      /**
       * Combobox for filetypes - output file choosers only.
       */
    protected JComboBox fileTypeCombo = null;

      /**
       * File list
       */
    protected JList fileList = null;

      /**
       * MRU File list
       */
     protected JList mruList = null;


      /**
       * Label for type of files. This will
       * Change based on the file type.
       */
    protected JLabel filterLabel = null;

      /**
       * Text source for internationalized strings*/
    protected I18NTextSource textSource = null;

      /**
       * Parent file chooser. */
    protected DragonFileChooser parent = null;

      /**
       * FileType(s) currently being shown in the file list.*/
    protected DFileType[] fileTypes = null;

      /**
       * Array of filenames currently being displayed.
       */
    protected String[] currentFilenames = null;

      /** 
       * Flag to prevent event handlers from acting when
       * internal updates are going on.
       */
    protected boolean bInternalEvent = false;

      /**
       * Local MRU list.
       */
    protected ArrayList localMRUList = new ArrayList(30);

      /**
       * Array of sorted MRU file references. Does not include memory files.
       */
    protected FileReference[] sortedMRUList = null;
       
      /**
       * Class for sorting file references
       */
    protected static FileReferenceComparator fileRefComparator =
                     new FileReferenceComparator();
      /**
       * Number of memory files currently in the
       * mruList. Value will change with each iteration.
       */
    protected int memoryFileCount = 0;
    
      /**
       * Keep track if this is an input or output chooser
       */
    protected boolean bInputChooser = true;

      //****************************************************
     /**
      * Empty constructor for use by child classes.
      */
    protected DragonFileList()
	{
        }

      /** 
       * Constructor creates the UI components of the 
       * FileList.
       * @param parent  Parent file chooser
       * @param bInputChooser If true used for input files, else for output
       * @param textSource reference to text source to use.
       */
    public DragonFileList(DragonFileChooser parent,
			 boolean bInputChooser,
			 I18NTextSource textSource)
        {
	this.parent = parent;
	this.textSource = textSource;
	this.bInputChooser = bInputChooser;
	JTextField theTextField = null;
	setLayout(new BorderLayout(10,10));
	setBorder(BorderFactory.createMatteBorder(10,10,10,10,
						  getBackground())); 
        filterLabel = new JLabel(DFileType.ALL.getDescription());
	add(filterLabel,BorderLayout.NORTH);
        JPanel textFieldPanel = new JPanel(new BorderLayout());
	if (bInputChooser)
	    {
	    fileFilterField = new JTextField(30);
	    theTextField = fileFilterField;
	    textFieldPanel.add(
		    new JLabel(textSource.getI18NText("%h9310.6",
						      "FILE PATTERN")),
		    BorderLayout.NORTH);
	    textFieldPanel.add(fileFilterField,BorderLayout.SOUTH);
	    }
	else 
	    {
	    JPanel innerPanel1 = new JPanel(new BorderLayout());
	    JPanel innerPanel2 = new JPanel(new BorderLayout());
	    fileEnterField = new JTextField(30);
	    theTextField = fileEnterField;
	    Font unifont = ApplicationManager.getFontProcessor().getFont("UNICODE");
	    if (unifont != null)
               theTextField.setFont(unifont);
	    innerPanel1.add(
		    new JLabel(textSource.getI18NText("%h9310.16",
						      "OUTPUT FILE")),
		    BorderLayout.NORTH);
	    innerPanel1.add(fileEnterField,BorderLayout.SOUTH);
	    fileTypeCombo = new JComboBox();
	    fileTypeCombo.setEditable(false);
	    fileTypeCombo.addActionListener(this);
	    fileTypeCombo.addKeyListener(parent);
	    innerPanel2.add(
		    new JLabel(textSource.getI18NText("%h9310.9",
						      "FILE TYPE")),
		    BorderLayout.NORTH);
	    innerPanel2.add(fileTypeCombo,BorderLayout.SOUTH);
	    textFieldPanel.add(innerPanel1, BorderLayout.NORTH);
	    textFieldPanel.add(innerPanel2, BorderLayout.SOUTH);
	    }
	theTextField.setDocument(new FilenameDocument(false));
	theTextField.addActionListener(this);
	theTextField.addFocusListener(this);
        theTextField.addKeyListener(this);
        theTextField.addKeyListener(parent);
        

	add(textFieldPanel, BorderLayout.SOUTH);
	JPanel listPanel = new JPanel(new BorderLayout(10,10));
	fileList = new JList();
        fileList.setFixedCellWidth(175);
	fileList.addListSelectionListener(this);
        fileList.addKeyListener(parent);
	fileList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	listPanel.add(new JScrollPane(fileList), BorderLayout.CENTER);
        JPanel mruPanel = new JPanel(new BorderLayout());
        mruPanel.add(new JLabel(textSource.getI18NText("%h9310.7",
						      "RECENT FILES")),
		    BorderLayout.NORTH);
	mruList = new JList();
        mruList.setFixedCellWidth(175);
        mruList.setVisibleRowCount(6);
	mruList.addListSelectionListener(this);
        mruList.addKeyListener(parent);
	mruList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	mruPanel.add(new JScrollPane(mruList), BorderLayout.SOUTH);
        listPanel.add(mruPanel,BorderLayout.SOUTH);
	add(listPanel,BorderLayout.CENTER);
        this.setMinimumSize(new Dimension(200,400));
        this.setPreferredSize(new Dimension(200,400));
	}

      /**
       * Set the appropriate file type for the file list.
       * This changes the label on the list, and the
       * items, if any, in the MRU List.
       * This method also adds any memory files to the mruList.
       */
    public void setFileTypes(DFileType[] types, String[] memoryFiles)
        {
	bInternalEvent = true;
	fileTypes = types;
	int i;
        FileReference[] mruFiles = null;
	Vector mruListData = new Vector(20);
        localMRUList.clear();
        mruList.setListData(mruListData);
        for (i = 0; i < fileTypes.length; i++)
	    {
	    DFileType fileType = fileTypes[i];
	    mruFiles = fileType.getUsedFiles();
	    for (int j = 0; j < mruFiles.length; j++)
	        {
	        // save the paths in the local list - only show the names
	        // in the mruList.
		if ((mruFiles[j].fileName.startsWith("=")) ||
                    (mruFiles[j].fileName.startsWith("(")))
	            continue; // skip memory files. 
		localMRUList.add(mruFiles[j]);
		}
	    }
	// change to an array so we can easily sort it.
        Object[] tempArray = localMRUList.toArray();
	sortedMRUList = new FileReference[tempArray.length];
	for (i = 0; i < tempArray.length; i++)
	    sortedMRUList[i] = (FileReference) tempArray[i];
	Arrays.sort(sortedMRUList,fileRefComparator);
	memoryFileCount = 0;
        if (memoryFiles != null)
	    {
            int len = memoryFiles.length;
	    for (i = 0; i < len; i++)
	         {
                 if ((memoryFiles[i] != null) &&
                     (memoryFiles[i].length() > 0))
		     {
	             mruListData.add(memoryFiles[i]);
		     memoryFileCount += 1;
		     }
		 }
            }
	for (i = 0; i < sortedMRUList.length; i++)
	    mruListData.add(new File(sortedMRUList[i].fileName).getName());
	mruList.setListData(mruListData);
        if (fileTypes.length == 1)
            filterLabel.setText(fileTypes[0].getDescription());
	else
	    filterLabel.setText(DFileType.GENERIC_FILES_LABEL);
	if (!bInputChooser)
	    initializeTypeCombo(types);
        populateFiles(null);
	bInternalEvent = false;
	}

      /**
       * Factorization. Set up the combo of file types
       * @param types Array of file types.
       */
    protected void initializeTypeCombo(DFileType[] types)
       {
       int i = 0;
       int count = fileTypeCombo.getItemCount();
       if (count > 0)
          for (i = count-1; i >= 0; i--)
	      fileTypeCombo.removeItemAt(i);
       for (i = 0; i < types.length; i++)
	   {
	   fileTypeCombo.addItem(types[i]);
	   // the toString method will show what we want
	   }
       parent.getModel().setCurrentOutputFileType(types[0]);
       }

      /** 
       * populate the file list with a list of
       * filenames. This is called whenever a new
       * directory is selected.
       * @param filenames String array of file names to display.
       */
    public void populateFiles(String[] filenames)
        {  
        bInternalEvent = true;
	if (filenames == null)
	    {
	    currentFilenames = empties;
	    }
        else
	    {
            currentFilenames = filenames;
	    }
	fileList.setListData(currentFilenames);
	bInternalEvent = false;
        }

    /**
     * Event Listener methods
     */
    public void actionPerformed(ActionEvent e)
        {
	if (e.getSource() == fileEnterField)
	    {
	    DFileType type = null;
	    File tester = new File(parent.getModel().getCurrentPath(),
				   fileEnterField.getText());
            for (int i = 0; (i < fileTypes.length) && (type == null); i++)
	         {
		 if (fileTypes[i].accept(tester))
		     type = fileTypes[i];
		 }
	    if (type == null)
	         type = parent.getModel().getCurrentOutputFileType();
	    if (type != null)
	         fileEnterField.setText(
                     type.getCanonicalName(fileEnterField.getText()));
	    parent.getModel().setCurrentPath(
                     parent.getModel().getCurrentPath());
            parent.getModel().setCurrentFilename(fileEnterField.getText());
	    parent.getModel().setMemoryFileSelected(false);
	    }
	else if (e.getSource() == fileFilterField)
	    {
	    // does this exactly match one of the files in the file list?
	    String pattern = fileFilterField.getText();
	    int idx = fileIndex(pattern);
	    if (idx >= 0)
	        {
	        parent.getModel().setCurrentPath(
                     parent.getModel().getCurrentPath());
                parent.getModel().setCurrentFilename(
                    currentFilenames[idx]);
	        parent.getModel().setMemoryFileSelected(false);
		}
	    }
	else if (e.getSource() == fileTypeCombo)
	    {
	    DFileType selectedType = 
                 (DFileType) fileTypeCombo.getSelectedItem(); 
	    if (selectedType != null)
	        parent.getModel().setCurrentOutputFileType(selectedType);
	    }
	}

      /**
       * Methods from the KeyListener interface.
       * Generic keys like F3, F1 are handled by the parent.
       * Here we deal with typing in the filter field
        */
    public void keyPressed(KeyEvent ke)
        {
	Object source = ke.getSource();
	int code = ke.getKeyCode();
	if ((source == fileFilterField) &&
            ((code == KeyEvent.VK_BACK_SPACE) ||
	     (code == KeyEvent.VK_DELETE)))
	    {
	    schedulePatternUpdate(fileFilterField, parent.getModel());
	    }
	}

    public void keyReleased(KeyEvent ke)
        {
	}

    public void keyTyped(KeyEvent ke)
        {
	Object source = ke.getSource();
	if (source == fileFilterField)
	    {
	    schedulePatternUpdate(fileFilterField,parent.getModel());
	    }
	}

      /**
       * Set up a timer to update the filter in 100 milliseconds.
       */
	protected void schedulePatternUpdate(JTextField whichField,
					     DFileChooserModel whichModel)
        {
	javax.swing.Timer timer = new javax.swing.Timer(100,
			     new FilterSetter(whichField,whichModel));
	timer.setRepeats(false);
	timer.start();
	}

      /**
       * Focus listener methods.
       */
    public void focusLost(FocusEvent fe)
        {
	Object source = fe.getSource();
	if ((source == fileEnterField) || (source == fileFilterField))
	    {
	    ActionEvent ae = new ActionEvent(source,1234567,"CR");
		actionPerformed(ae);
	    }
	}

    public void focusGained(FocusEvent fe)
        {
	}


      /**
       * Called by parent to set focus appropriately; either to
       * the fileList or to the output field, depending on
       * whether this is an output box or not.
       */
    public void setInitialFocus()
        {
	if (bInputChooser)
	    fileList.requestFocus();
	else
	    fileEnterField.requestFocus();
	}


      /** 
       * Factorization of valueChanged method. 
       * Handle selection from the mruList
       */
    protected void handleMruSelection(ListSelectionEvent e)
        {
	int idx = mruList.getSelectedIndex();
        if (idx < 0) // nothing selected
	    {
	    int oldIdx = e.getFirstIndex(); // one that was changed
            mruList.setSelectedIndex(oldIdx);  // reset - don't allow a change
	    }
        else if (idx < memoryFileCount) // this is a memory file
	    {
	    String fname = (String) mruList.getSelectedValue();
	    String msg = "{ DragonFileList: calling setCurrentPath at A }";
	    Tracer.outputTraceMessage(msg,
				      ApplicationManager.getModulePrefix(),
				      ApplicationManager.getTimeOffset());
	    parent.getModel().setCurrentPath(
                     parent.getModel().getCurrentPath());
	    msg = "{ DragonFileList: calling setCurrentFilename at A  }";
	    Tracer.outputTraceMessage(msg,
				      ApplicationManager.getModulePrefix(),
				      ApplicationManager.getTimeOffset());
            parent.getModel().setCurrentFilename(fname);
	    parent.getModel().setMemoryFileSelected(true);
	    }
        else if (idx >= memoryFileCount)
	    {
	    FileReference fRef = 
                   sortedMRUList[idx - memoryFileCount];
	    File temp = new File(fRef.fileName);
	    String msg = "{ DragonFileList: calling setCurrentPath at B }";
	    Tracer.outputTraceMessage(msg,
				      ApplicationManager.getModulePrefix(),
				      ApplicationManager.getTimeOffset());
	    parent.getModel().setCurrentPath(temp.getParent());
	    msg = "{ DragonFileList: calling setCurrentFilename at B }";
	    Tracer.outputTraceMessage(msg,
				      ApplicationManager.getModulePrefix(),
				      ApplicationManager.getTimeOffset());
	    parent.getModel().setCurrentFilename(temp.getName());
	    parent.getModel().setMemoryFileSelected(false);
	    }
	}


      /** 
       * Factorization of valueChanged method. 
       * Handle selection from the fileList
       */
    protected void handleFileSelection(ListSelectionEvent e)
        {
	int idx = fileList.getSelectedIndex();
        if (idx < 0) // nothing selected
	    {
	    int oldIdx = e.getFirstIndex(); // one that was changed
            fileList.setSelectedIndex(oldIdx);  // reset - don't allow a change
	    return;
	    }
	String newName = (String) fileList.getSelectedValue();
	String msg = 
	  "{ DragonFileList: calling setCurrentPath - valueChanged }";
	Tracer.outputTraceMessage(msg,
				  ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
	parent.getModel().setCurrentPath(parent.getModel().getCurrentPath());
	msg = "{ DragonFileList: calling setCurrentFilename - valueChanged }";
	Tracer.outputTraceMessage(msg,
				  ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
	parent.getModel().setCurrentFilename(newName);
	parent.getModel().setMemoryFileSelected(false);
	}
    
    public void valueChanged(ListSelectionEvent e)
        {
	String msg = "{ DragonFileList.valueChanged- internal event is " +
	     bInternalEvent + " }";
	Tracer.outputTraceMessage(msg,
				  ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
        if (bInternalEvent)
	    return;
	if (e.getSource() == fileList)
	    handleFileSelection(e);
	else if (e.getSource() == mruList)
	    handleMruSelection(e);
	}
      
      
      /**
       * Updates the view to reflect the current state of the
       * model.
       * @param currentPath Path associated with the filename.
       * @param currentName Name selected or typed
       * @param oldPath Path of previous selected filename if any.
       * @param oldName Previous selected filename if any.
       */
    public void updateView(String currentPath, 
			   String currentName, 
			   String oldPath,
			   String oldName)
        {
        if (!representsChange(currentPath,currentName,oldPath,oldName))
	    return;  // no change 
	String msg = "{ DragonFileList: updateView " +
          oldPath + " to " + currentPath + ", " +
	  oldName + " to " + currentName + " }";
	Tracer.outputTraceMessage(msg,ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
        bInternalEvent = true;
	int idx = 0;
	if (currentName != null)
            {
            if (!(currentName.startsWith("=")) &&
                !(currentName.startsWith("(")))
	        {
		String searchFile = 
                      new File(currentPath, currentName).getPath();
                idx = findInMRU(searchFile);
		if (idx >= 0)
		    {
		    mruList.setSelectedIndex(idx+memoryFileCount);
		    }
		else 
		    {
		    mruList.clearSelection();
		    }
		}
            else  // if it's a memory file, it is already set in mruList
	          // because that's the only way to choose a memory file
	        {
		}
            idx = fileIndex(currentName);
	    if (idx >= 0)
	        {
	        fileList.setSelectedIndex(idx);
		fileList.ensureIndexIsVisible(idx);
		}
	    else
	        {
		fileList.clearSelection();
                fileList.ensureIndexIsVisible(0);
		}

	    }
	else
	    {
            mruList.clearSelection();
	    fileList.clearSelection();
	    fileList.ensureIndexIsVisible(0);
	    }
        String filter = parent.getModel().getPartialName();
	if (filter == null)
	    clearFilter();
	else if (fileFilterField != null)
	    fileFilterField.setText(filter);
	if (fileEnterField != null)
	    {
	    if (currentName != null)
	        fileEnterField.setText(currentName);
	    else
	        fileEnterField.setText("");
	    }
	bInternalEvent = false;
	}


      /**
       * Reinitialize the filter field.
       */
    public void clearFilter()
        {
	if (fileFilterField != null)
	    fileFilterField.setText("");
	}

      /**
       * Factorization of updateView. Returns true if the old and
       * new path, or the old and new files, represent a change.
       */
    protected boolean representsChange(String currentPath, String currentName,
				       String oldPath, String oldName)
        {
        
	boolean bPathChanged = false;
        boolean bNameChanged = false;
        if (currentPath != null)
	    {
	    if (!currentPath.equals(oldPath))
                 bPathChanged = true;
            }
        else if (oldPath != null)
	    {
	    bPathChanged = true;
	    }
        if (currentName != null)
	    {
	    if (!currentName.equals(oldName))
                 bNameChanged = true;
            }
        else if (oldName != null)
	    {
	    bNameChanged = true;
	    }
	return (bPathChanged || bNameChanged);
	}

      /**
       * Helper method. Looks up a filename in the array of
       * strings currently displayed in the list, and returns its
       * index, or -1 if not found.
       * Public because now used by chooser to determine if the
       * previously selected file is visible.
       */
    public int fileIndex(String filename)
        {
        int found = -1;
	int pos = 0;
        if (currentFilenames == null)
	    return found;
	int len = currentFilenames.length;
	for (int i = 0; (i < len) && (found < 0); i++)
	    {
            // currentFilenames[i] could be null if we filtered by partial
	    // name. In that case, all subsequent values would be null
	    if (currentFilenames[i] == null) 
	        {
                break;
		}
            if (currentFilenames[i].compareToIgnoreCase(filename) == 0 )
	        {
		found = i;
		break;
		}
	    else // check for a match not including the extension
	        {
		pos = currentFilenames[i].lastIndexOf(".");
		if ((pos > 0) &&
                    (currentFilenames[i].substring(0,pos).compareToIgnoreCase(filename) == 0 ))
		   {
		   found = i;
		   break;
		   }
		}
	    }
	return found;
        }
    
      /**
       * Helper method, looks through the sorted MRU list 
       * to see if file is already there.
       * @param filepath Full filename including path.
       */
    protected int findInMRU(String filepath)
        {
        int found = -1;
        if ((sortedMRUList == null) || (sortedMRUList.length == 0))
	    return found;
	int len = sortedMRUList.length;
	for (int i = 0; i < len; i++)
	    {
	    String test = sortedMRUList[i].fileName;
	    if (test.compareToIgnoreCase(filepath) == 0)
	        {
		found = i;
		break;
		}
	    }
	return found;
	}


      //*****************************************************
      /** 
       * Inner class used to issue a delayed update to
       * the filter pattern, to make sure that the key has
       * taken effect
       */
    class FilterSetter implements ActionListener
         {
	 JTextField myField;
	 DFileChooserModel model; 
	 /**
	  * Constructor sets myField
	  */
	 public FilterSetter(JTextField whichField,
			     DFileChooserModel whichModel)
             {
	     myField = whichField;
	     model = whichModel;
	     }

	 /**
	  * Action Listener method
	  */
	 public void actionPerformed(ActionEvent e)
             {
	     String newPattern = myField.getText();
	     if (newPattern.length() > 0)
	         model.setCurrentFilter(newPattern);
	     else
	         model.setCurrentFilter(null);
	     }
         }



    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonFileList.java,v 1.13 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


 
