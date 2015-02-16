/**
 *  ViewFileChooser.java
 *
 *  Copyright 2002-2007 by Sally Goldin & Kurt Rudahl
 *
 *  Created 5/15/2002 by Sally Goldin
 * 
 *  $Id: ViewFileChooser.java,v 1.6 2007/01/05 04:00:22 rudahl Exp $
 *  $Log: ViewFileChooser.java,v $
 *  Revision 1.6  2007/01/05 04:00:22  rudahl
 *  super fix
 *
 *  Revision 1.5  2005/02/06 09:17:30  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.4  2002/09/04 21:45:56  goldin
 *  Update file chooser to allow multiple file types
 *
 *  Revision 1.3  2002/08/22 14:57:02  goldin
 *  Work on appearance and behavior of VP Filechooser
 *
 *  Revision 1.2  2002/05/16 13:16:39  goldin
 *  work on unmoveable file chooser for VP
 *
 *  Revision 1.1  2002/05/16 00:29:53  goldin
 *  Wrap file chooser with call to JNI to make window unmoveable
 *
 */

package com.grs.dragon.viewport;

import com.grs.gui.*;
import javax.swing.*;
import javax.swing.event.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/**
 * This class is a thin wrapper around the DragonFileChooser
 * class, which mplements the view component for a customized file dialog. 
 * <p>
 * The <i>chooseFile</i> method is overridden to add a call to
 * the JNI method which fixes the location of the dialog.
 */
public class ViewFileChooser extends DragonFileChooser
    {

    /**
     * Constructor builds the UI - frame parent
     * @param parent    Parent frame, used for centering.
     * @param textSource Text source for translated strings,
     * @param bForPaths  If true, this is a paths-only dialog. and 
     *                   will not have a file list.
     * @param bReadFile  If true, this chooser selects input files.
     */
    public ViewFileChooser(Frame parent, 
			     I18NTextSource textSource, 
			     boolean bForPaths, boolean bReadFile)
        {
        super(parent, textSource, bForPaths, bReadFile, false);
	//setModal(false);
	}

    /**
     * Primary file chooser method. Displays the dialog and collects 
     * user input. Returns the selected filename, with
     * path, or null if the user clicked cancel (or clicked OK with 
     * nothing selected.
     * @param fileTypes  Array of codes identifying the types of file desired
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
	setModal(false);
	DriveTester.setDoTest(false);
        setupChooserDisplay(fileTypes, memoryFiles,
			    partialName, title, defaultValue);
        setLocationRelativeTo(parent);
        setVisible(true);
        viewProg.FixupNCDialog("FILECHOOSE??","",false); 
	setModal(true);
        return retFile;  // set by the actionperformed method
        }

      /**
       * Explicitly request the last-set filename.
       * This will allow us to get the filename after the
       * file chooser box is dismissed.
       */
    public File getLastChosenFile()
        {
	return retFile;
	}

    }



