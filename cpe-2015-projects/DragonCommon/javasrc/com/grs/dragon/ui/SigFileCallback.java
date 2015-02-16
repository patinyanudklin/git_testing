/* 
 * SigFileCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/9/2001
 *
 * $Id: SigFileCallback.java,v 1.17 2007/02/11 06:53:13 goldin Exp $
 * $Log: SigFileCallback.java,v $
 * Revision 1.17  2007/02/11 06:53:13  goldin
 * Make sure that sigfilevalidator called for all input sign. files
 *
 * Revision 1.16  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.15  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.14  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.13  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.12  2001/10/30 13:05:08  goldin
 * Associate correct validators and callbacks with ANN and C/EDI fields
 *
 * Revision 1.11  2001/10/29 15:39:17  goldin
 * Fix bug in handling of CURRENT
 *
 * Revision 1.10  2001/10/26 18:03:25  goldin
 * Working on UI side of C/EDI
 *
 * Revision 1.9  2001/10/17 10:47:56  goldin
 * Further debugging on signature interaction
 *
 * Revision 1.8  2001/10/17 10:29:05  goldin
 * Fix bug - was not resetting signames
 *
 * Revision 1.7  2001/06/29 17:30:16  goldin
 * Implemented handing of state info from reply files
 *
 * Revision 1.6  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.5  2001/05/22 12:05:13  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 * Revision 1.4  2001/05/14 15:00:27  goldin
 * Begin work on class to interpret header
 *
 * Revision 1.3  2001/05/14 13:47:36  goldin
 * Add symbols for new text
 *
 * Revision 1.2  2001/05/10 13:14:51  goldin
 * Continue implementation of SigFile and scaling callbacks
 *
 * Revision 1.1  2001/05/09 15:16:40  goldin
 * Begin implementing signature populaing callbacks for C/EDI
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.io.File;
import java.util.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of populating one or more combo boxes with the names of 
 *  signatures read from a new or already read signature file.
 * @author  goldin*/
public class SigFileCallback implements Callback 
    {
      /**
       * Table to map panel IDs to the IDs of combo box that
       * should be populated. Initialized the first time a SigFileCallback
       * is created.
       */
    protected static Hashtable comboTable = null;

      /**
       * Constructor. The first time that this is called, it
       * creates and initializes the hash table.
       */
    public SigFileCallback()
        {
	if (comboTable == null)
	    {
	    comboTable = new Hashtable(16);
            comboTable.put("^FSIMOD","^SN1M");
            comboTable.put("^FSISHO","^SN1SHO");
            comboTable.put("^FSACOP","^SN1COP");
            comboTable.put("^FSICOM","^SN1C");
            comboTable.put("^FSIREN","^SN1R");
            comboTable.put("^FSIDEL","^SN1D");
            comboTable.put("^FSIHIS","^SN1H");
            comboTable.put("^FSA","^SN2C");
	    }
        }
    
      /** Primary method of a callback class.
       *  Process sigFile if necessary, and set values in the
       *  appropriate combo box.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        SigFileProcessor sigFileProc = null;
        DragonField fsaField = null;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
        DragonUI mainApp = DragonUI.currentApplication;
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
	    return;
	// determine if there is a current sig file and if so,
	// if that is what the user requested
        SigFileProcessor currentSigs = mainApp.getCurrentSigProcessor();
        if ((currentSigs != null) && (value.startsWith("(")) )
            {
	    File sigFile = new File(ApplicationManager.getTempPath(),
				StatusManager.SIGCURRENT);
            sigFileProc = currentSigs;
	    sigFileProc.clear();
	    sigFileProc.init(sigFile.getAbsolutePath());
            }
        else
	    {
	    // sigfileprocessor may already have been instantiated
	    // in the validator, for secondary files only
		//            sigFileProc = (SigFileProcessor) field.getUserData();
		//if (sigFileProc == null)
		//{
	    sigFileProc = new SigFileProcessor(value);
		 // }
	    if (!sigFileProc.isInitialized())
	         {
                 UiErrorDisplay errDisp = 
		   (UiErrorDisplay) ApplicationManager.getErrorDisplay();
		 errDisp.sendError(sigFileProc.getErrorMessage());
		 return;
		 }
            }
	String myID = field.getName();
        if ((myID.compareTo("^FSACOP") != 0) &&
	    (myID.compareTo("^FSA") != 0))
	    {
	    mainApp.setCurrentSigProcessor(sigFileProc);
	    }
	String comboID = (String) comboTable.get(myID);
        DComboField comboField = null;
	if (comboID != null)
            comboField = (DComboField) parent.getField(comboID);
	if (comboField == null)
	    {
	    if (myID.equals("^FSICOP"))
	        {
	        // need to enable the secondary file field.
	        fsaField = parent.getField("^FSACOP");
		if (fsaField != null)
		    {
	            fsaField.setEnabled(true);
	            fsaField.createFocusRequestor(200);
		    }
		}
	    // FSICOP does not init a combo - we use this
	    // callback only to initialize the SigFileProcessor
	    return;
	    }
        String[] sigNames = sigFileProc.getSignatureNames();
	String[] tempNames = null;
        int sigCount = sigFileProc.getSigCount();
	int altSigCount = 0;
        if (myID.equals("^FSISHO"))  // special case, add "*"
	    {
	    tempNames = new String[sigCount + 1];
            }
        else if (myID.equals("^FSA")) // special case, combine with current
	    {
            altSigCount = mainApp.getCurrentSigProcessor().getSigCount(); 
	    tempNames = new String[sigCount + altSigCount];
	    }
	else
	    {
	    tempNames = new String[sigCount];
            }
	int i = 0; 
	while (i < sigCount)
	    {
	    tempNames[i] = sigNames[i];
	    i++;
	    }
        if (myID.equals("^FSISHO"))  // special case, add "*"
	    {
	    tempNames[i] = "*";
	    }
        if (myID.equals("^FSA"))  // special case, add current names
	    {
            String[] altNames = 
                 mainApp.getCurrentSigProcessor().getSignatureNames();
            for (int j = 0; j < altSigCount; j++)
	         {
	         tempNames[i+j] = altNames[j];
		 }
	    }
	comboField.setChoiceStrings(tempNames);
	if (myID.equals("^FSICOM"))
	    {
            // populate the secondary combo box.
	    // will be overwritten if the user supplies a file for
            // the secondary file name (which is not required)
            comboField = (DComboField) parent.getField("^SN2C");
            if (comboField != null)
   	        comboField.setChoiceStrings(tempNames);
	    // need to enable the secondary file field.
	    fsaField = parent.getField("^FSA");
	    if (fsaField != null)
	        {
	        fsaField.setEnabled(true);
		fsaField.createFocusRequestor(200);
		}
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SigFileCallback.java,v 1.17 2007/02/11 06:53:13 goldin Exp $ \n";
	}
    }

// End of SigFileCallback.java














