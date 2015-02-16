/**
 * DragonMultiFileList
 *
 *    This is a specialization of the file list part of the file chooser,
 *    which allows the user to choose and return more than one
 *    file.
 *
 *	Copyright  2006-2007   Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *    
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *
 * $Id: DragonMultiFileList.java,v 1.5 2007/02/15 11:16:55 goldin Exp $
 * $Log: DragonMultiFileList.java,v $
 * Revision 1.5  2007/02/15 11:16:55  goldin
 * Add initializer to clear multi-select file boxes when we enter a panel
 *
 * Revision 1.4  2007/01/08 10:15:29  goldin
 * Add clear button to multi file chooser
 *
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2006/12/28 10:34:21  goldin
 * Complete implementation of multifile selection control and file chooser
 *
 * Revision 1.1  2006/12/25 10:48:37  goldin
 * Begin implementation of multi-select file control
 *
 *
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
 * This class is a UI component that presents a list of the files
 * in a particular directory. This is a specialization of 
 * DragonFileList which allows the user to select multiple
 * files rather than just one.
 */
public class DragonMultiFileList extends DragonFileList implements KeyListener
    {
      /**
       * List of files that have been selected.
       * This replaces the MRU list
       */
    protected JList selectionList = null;

      /**
       * Text field for entering filter strings. Only on
       * input file choosers.
       */
    protected JTextField fileFilterField = null;

      /**
       * File list
       */
    protected JList fileList = null;

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
       * Selected files
       */
    protected ArrayList selectedFileList = new ArrayList(30);

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

      /**
       * Button to let the user remove items from the selected 
       * list.
       */
    protected JButton removeBtn = null;

      /**
       * Button to let the user clear all items from the selected 
       * list.
       */
    protected JButton clearBtn = null;

      //****************************************************
      /** 
       * Constructor creates the UI components of the 
       * FileList.
       * @param parent  Parent file chooser
       * @param bInputChooser If true used for input files, else for output
       * @param textSource reference to text source to use.
       */
    public DragonMultiFileList(DragonFileChooser parent,
			 boolean bInputChooser,
			 I18NTextSource textSource)
        {
	super();
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
            throw new RuntimeException(
               "MultiSelect file lists are available for input only!");

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
	mruPanel.setBorder(new EmptyBorder(0,0,5,0));
        mruPanel.add(new JLabel(textSource.getI18NText("%f9310.7",
						      "SELECTED FILES")),
		    BorderLayout.NORTH);
        String removeString = 
	    ApplicationManager.getTextSource().getI18NText("%f7401.2","REMOVE");
        String clearString = 
	    ApplicationManager.getTextSource().getI18NText("%h2B0.0.3","CLEAR");
	removeBtn = new JButton(removeString);
	removeBtn.addActionListener(this);
	removeBtn.setEnabled(false);
	clearBtn = new JButton(clearString);
	clearBtn.addActionListener(this);
	clearBtn.setEnabled(false);

        JPanel buttonPanel = new JPanel(new FlowLayout());
	buttonPanel.add(removeBtn);
	buttonPanel.add(clearBtn);
	selectionList = new JList();
        selectionList.setFixedCellWidth(175);
        selectionList.setVisibleRowCount(6);
	selectionList.addListSelectionListener(this);
        selectionList.addKeyListener(parent);
	selectionList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
	mruPanel.add(new JScrollPane(selectionList), BorderLayout.CENTER);
	mruPanel.add(buttonPanel, BorderLayout.SOUTH);

        listPanel.add(mruPanel,BorderLayout.SOUTH);
	add(listPanel,BorderLayout.CENTER);
        this.setMinimumSize(new Dimension(200,400));
        this.setPreferredSize(new Dimension(200,400));
	}

      /**
       * Set the appropriate file type for the file list.
       * This changes the label on the list, and the
       * items, if any, in the MRU List.
       * This method also adds any memory files to the selectionList.
       */
    public void setFileTypes(DFileType[] types, String[] memoryFiles)
        {
	bInternalEvent = true;
	fileTypes = types;
	int i;
        FileReference[] mruFiles = null;
	Vector selectionListData = new Vector(20);
        //localMRUList.clear();
        selectionList.setListData(selectionListData);
        for (i = 0; i < fileTypes.length; i++)
	    {
	    DFileType fileType = fileTypes[i];
	    //mruFiles = fileType.getUsedFiles();
	    //for (int j = 0; j < mruFiles.length; j++)
	        {
	        // save the paths in the local list - only show the names
	        // in the selectionList.
		//if ((mruFiles[j].fileName.startsWith("=")) ||
                //    (mruFiles[j].fileName.startsWith("(")))
	        //    continue; // skip memory files. 
		//localMRUList.add(mruFiles[j]);
		}
	     }
	// change to an array so we can easily sort it.
        //Object[] tempArray = localMRUList.toArray();
	//sortedMRUList = new FileReference[tempArray.length];
	//for (i = 0; i < tempArray.length; i++)
	//    sortedMRUList[i] = (FileReference) tempArray[i];
	//Arrays.sort(sortedMRUList,fileRefComparator);
	//memoryFileCount = 0;
        //if (memoryFiles != null)
	//    {
        //    int len = memoryFiles.length;
	//    for (i = 0; i < len; i++)
	//         {
        //         if ((memoryFiles[i] != null) &&
        //             (memoryFiles[i].length() > 0))
	//	     {
	//             selectionListData.add(memoryFiles[i]);
	//	     memoryFileCount += 1;
	//	     }
	//	 }
        //    }
	//for (i = 0; i < sortedMRUList.length; i++)
	//    selectionListData.add(new File(sortedMRUList[i].fileName).getName());
	selectionList.setListData(selectionListData);
        if (fileTypes.length == 1)
            filterLabel.setText(fileTypes[0].getDescription());
	else
	    filterLabel.setText(DFileType.GENERIC_FILES_LABEL);
	//if (!bInputChooser)
	//    initializeTypeCombo(types);
        populateFiles(null);
	bInternalEvent = false;
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
	DFileMultiChooserModel mModel = 
	    (DFileMultiChooserModel) parent.getModel();
	if (e.getSource() == fileFilterField)
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
	else if (e.getSource() == removeBtn)
	    {
	    int index = selectionList.getSelectedIndex();
	    if (index >= 0)
		{
		mModel.removeItem(index);
		updateSelectedFileList();
		}
            removeBtn.setEnabled(false);
            String names[] = mModel.getCurrentFilenameListAsString();
            if (names.length > 0)
                clearBtn.setEnabled(true);
	    else
		clearBtn.setEnabled(false);
	    }
	else if (e.getSource() == clearBtn)
	    {
	    clear();
	    }
	}

       /**
	* Allow outside classes to clear the file list.
	*/
      public void clear()
	 {
	 DFileMultiChooserModel mModel = 
	    (DFileMultiChooserModel) parent.getModel();
         String names[] = mModel.getCurrentFilenameListAsString();
	 int len = names.length;
	 for (int index = 0; index < len; index++)
	     {
	      mModel.removeItem(0);
	     }
	 updateSelectedFileList();
	 clearBtn.setEnabled(false);
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
	fileList.requestFocus();
        DFileMultiChooserModel mModel = (DFileMultiChooserModel) parent.getModel();
        String names[] = mModel.getCurrentFilenameListAsString();
        if (names.length > 0)
	    clearBtn.setEnabled(true);
	else
	    clearBtn.setEnabled(false);
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
	parent.getModel().setCurrentPath(parent.getModel().getCurrentPath());
	parent.getModel().setCurrentFilename(newName);
	parent.getModel().setMemoryFileSelected(false);
	updateSelectedFileList();
        clearBtn.setEnabled(true);
	}

    
    public void valueChanged(ListSelectionEvent e)
        {
	String msg = "{ DragonMultiFileList.valueChanged- internal event is " +
	     bInternalEvent + " }";
	Tracer.outputTraceMessage(msg,
				  ApplicationManager.getModulePrefix(),
				  ApplicationManager.getTimeOffset());
        if (bInternalEvent)
	    return;
	if (e.getSource() == fileList)
	    handleFileSelection(e);
        else if (e.getSource() == selectionList)
            {
	    if (selectionList.getSelectedIndex() == -1)
		removeBtn.setEnabled(false);
	    else
		removeBtn.setEnabled(true);
            }
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
	String msg = "{ DragonMultiFileList: updateView " +
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
		    selectionList.setSelectedIndex(idx+memoryFileCount);
		    }
		else 
		    {
		    selectionList.clearSelection();
		    }
		}
            else  // if it's a memory file, it is already set in selectionList
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
            selectionList.clearSelection();
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
	 * Called by the FileChooser to make the
	 * selected file list match the model.
	 */
    public void updateSelectedFileList()
	{
        DFileMultiChooserModel mModel = (DFileMultiChooserModel) parent.getModel();
        String names[] = mModel.getCurrentFilenameListAsString();
        selectionList.setListData(names);
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
	    schedulePatternUpdate(fileFilterField,parent.getModel());
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


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonMultiFileList.java,v 1.5 2007/02/15 11:16:55 goldin Exp $ \n";
	}
    }


 
