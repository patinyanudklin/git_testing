/* QueryDialogCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/25/2001
 *
 * $Id: QueryDialogCallback.java,v 1.14 2007/01/05 07:41:57 rudahl Exp $
 * $Log: QueryDialogCallback.java,v $
 * Revision 1.14  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.13  2002/04/29 17:23:01  goldin
 * Try making query a JFrame
 *
 * Revision 1.12  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.11  2001/11/21 15:17:53  goldin
 * Make all references to getTimeOffset use ApplicationManager method
 *
 * Revision 1.10  2001/11/19 20:29:38  goldin
 * Moved IPC classes to new package
 *
 * Revision 1.9  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.8  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.7  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.6  2001/10/12 18:40:10  goldin
 * Remove console msgs
 *
 * Revision 1.5  2001/10/05 16:54:44  goldin
 * Fix bug; was not dividing time by 1000
 *
 * Revision 1.4  2001/06/13 14:12:48  goldin
 * Move buttons to be dialogwide, add ability to have file fields in Qry boxes
 *
 * Revision 1.3  2001/06/06 15:16:11  goldin
 * Work on cleaning up event handling in FileChooser; improve tracing
 *
 * Revision 1.2  2001/05/28 16:36:26  goldin
 * Debugging QueryProcessor
 *
 * Revision 1.1  2001/05/27 15:41:44  goldin
 * Additional work on query processor class and related functionality
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.ipc.*;
import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.io.*;

/** 
 *  This class implements the Callback interface. It is called when
 *  any button on a query-generated dialog (a dialog created by the
 *  ServerQueryProcessor) is clicked. It has the effect
 *  of writing a reply file that holds the current contents of the panel
 *  in which the button is located.
 * @author  goldin
 */
public class QueryDialogCallback implements Callback 
    {
    protected DragonUI mainApp = null;
    protected DragonPanel parent = null;

      /** Primary method of a callback class. 
       *   In this case the field is a button
       *   on the response panel. The effect of the callback
       *   is to create a reply file corresponding to the query.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        boolean bOkBtn = false;
	parent = field.getTopLevelPanel();
	if (parent == null)
	    return;
	mainApp = DragonUI.currentApplication;
	if (field.getName().compareTo("OKBUTTON")==0)
    	    {
	    bOkBtn = true;
	    DragonField badField = parent.checkFieldValidity();
	    if (badField != null)
	        {
		Toolkit.getDefaultToolkit().beep();
		badField.getValidator().displayLastError();
		badField.requestFocus();
		return;
	        }
	    badField = parent.checkRequiredFields();
	    if (badField != null)
	        {
		UiErrorDisplay errDisp = (UiErrorDisplay)
                    ApplicationManager.getErrorDisplay();
                errDisp.showError(null,TextKeys.MISSINGREQUIRED,
				 badField, parent);
		badField.requestFocus();
		return;
		}
	    }
        // all seems to be well. So create the reply file.
        createRpyFile(field, bOkBtn);
	JFrame dlg = parent.getEnclosingFrame();
	dlg.setVisible(false);
	}

      /**
       * Factorization. Create a reply file that includes
       * the values of all fields on the form.
       */
    protected void createRpyFile(DragonField field,
				 boolean bOkBtn)
        {
        String qryFileName = (String) field.getUserData();
        int pos = qryFileName.toUpperCase().indexOf("QRY");
        String rpyFileName = qryFileName.substring(0,pos) +
                             "Rpy" + qryFileName.substring(pos+3);
	try
	    {
	    FileWriter writer = new FileWriter(rpyFileName);
	    StringBuffer contents = new StringBuffer();
            String timeString = String.valueOf(
                       (new Date().getTime())/(long)1000);
	    contents.append("( ");
	    contents.append(UiErrorDisplay.ZEROS.substring(0,12 - timeString.length()));
	    contents.append(timeString + " 999 UI )\n");
	    if (bOkBtn)
	        {
		contents.append("action=ok\n");
                String tempString = parent.getAttributeValueList();
	        if (tempString.length() > 0)
                    contents.append(tempString);
		}
	    else
	        {
		contents.append("action=cancel\n");
		}
	    int fileLen = contents.length();
	    if (fileLen < 100)
	        fileLen -= 1;
	    if (fileLen > 999)
	        fileLen += 1;
	    contents = contents.replace(15,18,String.valueOf(fileLen));
            writer.write(contents.toString());
            writer.close();
	    // create an IpcFile to monitor the file and log its contents
	    // monitor only - don't delete.
	    IpcFile rpyIpcFile = 
	      new IpcFile(rpyFileName,ApplicationManager.getTimeOffset(),true);
            }
        catch (IOException ioe)
	    {
	      // handle error
	    ioe.printStackTrace();
	    }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: QueryDialogCallback.java,v 1.14 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of QueryDialogCallback.java

