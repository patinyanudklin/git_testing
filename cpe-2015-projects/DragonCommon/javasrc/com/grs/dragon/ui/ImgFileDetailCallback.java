/* ImgFileDetailCallback.java
 *
 * Copyright  2002-2007  Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 6/28/2002
 *
 * $Id: ImgFileDetailCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ImgFileDetailCallback.java,v $
 * Revision 1.3  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.2  2002/09/18 19:27:01  goldin
 * Add modified date to Details
 *
 * Revision 1.1  2002/06/28 15:27:47  goldin
 * Implement 'Details' in file chooser
 *
 *
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import java.util.*;
import java.awt.*;
import java.io.*;
import java.text.DateFormat;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of executing the command associated with a response panel.
 *  If the panel is a popup, the callback sends the command substring
 *  back to the parent, rather than executing it.
 * @author  goldin*/
public class ImgFileDetailCallback implements Callback 
    {
    

      /** Primary method of a callback class. 
       *   In this case the field is a dummy used only to
       *   pass the filename whose details are to be shown
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */

    public void executeCallback(DragonField field)
        {
	Component parent = field.getParentComponent();
	I18NTextSource textSource = ApplicationManager.getTextSource();
	String filename = field.getLabelText();
	DImageHeader header = new DImageHeader(filename);
	File testFile = new File(filename);
        DateFormat dateFmt = DateFormat.getDateTimeInstance(
                    DateFormat.MEDIUM,DateFormat.SHORT);
	StringBuffer buffer = new StringBuffer();
	buffer.append(textSource.getI18NText("%h3200.2.0","Lines") + ": "
		      + Integer.toString(header.getNLines()));
	buffer.append("  " +textSource.getI18NText("%h3200.2.1","Pixels") 
		      + ": "
		      + Integer.toString(header.getNPix())+ "\n");
	buffer.append(textSource.getI18NText("%h3200.3.0","Bits/Pixel") + ": "
		      + Integer.toString(header.getBitsPerPix())+ "\n");
	buffer.append(textSource.getI18NText("%h3030.3","Scene") + ": "
		      + header.getScene()+"\n");
	buffer.append(textSource.getI18NText("%h3030.4","Subscene") + ": "
		      + header.getSubscene()+"\n");
	buffer.append(textSource.getI18NText("%h3200.7","Comment") + ": "
		      + header.getComment()+"\n");
	buffer.append(textSource.getI18NText("%h9310.3","Date") + ": "
		      + dateFmt.format(new Date(testFile.lastModified())) +"\n");
        String message = buffer.toString();
	buffer.delete(0,buffer.length());
	buffer.append(filename + " " + textSource.getI18NText("%h9310.1",
							      "Details"));
	JOptionPane.showMessageDialog(parent,message,buffer.toString(),
				      JOptionPane.PLAIN_MESSAGE,null);

	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ImgFileDetailCallback.java,v 1.3 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of ImgFileDetailCallback.java

