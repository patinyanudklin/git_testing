/* 
 * ImgHeaderCallback.java
 *
 * Copyright  2001-2007 Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 5/16/2001
 *
 * $Id: ImgHeaderCallback.java,v 1.20 2007/01/05 07:41:57 rudahl Exp $
 * $Log: ImgHeaderCallback.java,v $
 * Revision 1.20  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.19  2006/12/17 11:35:56  goldin
 * fix formatting of reals
 *
 * Revision 1.18  2006/12/10 12:09:58  goldin
 * Adding new menus and panels for revised geometry/geography
 *
 * Revision 1.17  2006/02/11 07:15:31  goldin
 * Enable classnames tab even if no classnames yet
 *
 * Revision 1.16  2005/08/13 08:41:23  goldin
 * Migrate fix in 5.6 regarding display type setting based on header
 *
 * Revision 1.15  2004/12/06 03:41:56  goldin
 * Don't change display type for MEA if =M
 *
 * Revision 1.14  2002/09/11 23:34:20  goldin
 * Call new statusmanager method to translate =R etc into a filename
 *
 * Revision 1.13  2002/07/25 23:06:18  goldin
 * Make Source show up in HEA
 *
 * Revision 1.12  2002/05/29 17:52:24  goldin
 * Add processing for calibration fields
 *
 * Revision 1.11  2002/03/06 17:48:12  goldin
 * Enhance and extend use of ImgHeaderCallback to control display type
 *
 * Revision 1.10  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.9  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.8  2001/11/09 17:52:05  goldin
 * Set display type to color for =C or classified file
 *
 * Revision 1.7  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.6  2001/10/17 10:29:37  goldin
 * Modify to use ApplicationManager to get error display, etc.
 *
 * Revision 1.5  2001/10/12 11:41:05  goldin
 * New callbacks for HEA panel
 *
 * Revision 1.4  2001/07/31 17:40:38  goldin
 * display correct range as part of message for out-of-range errors
 *
 * Revision 1.3  2001/07/25 11:53:05  goldin
 * support nlines/npix in SUB
 *
 * Revision 1.2  2001/05/29 10:35:28  goldin
 * Add tab disabling capability
 *
 * Revision 1.1  2001/05/16 15:43:16  goldin
 * Implemen header-based callback
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import javax.swing.*;
import java.text.NumberFormat;

/** 
 *  This class implements the Callback interface. It is used to populate
 *  fields depending on a panel, based on data in the header of the
 *  image file specified in the field that invokes the callback.
 * @author  goldin*/
public class ImgHeaderCallback extends HeaderCallback 
    {
      /** Primary method of a callback class.
       *  Process sigFile if necessary, and set values in the
       *  appropriate combo box.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
	DImageHeader thisHeader = null;
        DragonField dispTypeField = null;
	DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)  
	    {
	    return;
	    }
        DragonUI mainApp = DragonUI.currentApplication;
	String value = field.getFieldValue();
	if ((value == null) || (value.length() == 0))
	    return;
	// determine if there is a current header and if so,
	// if that is what the user requested
        DImageHeader header = mainApp.getMemoryHeader();
        if ((header != null) && (header.isInitialized()) &&
	    (value.equals("=M")))
            {
            thisHeader = header;
            }
	else if (value.equals("=C"))
	    {
	    dispTypeField = parent.getField("^DSP");
            if (dispTypeField != null)
                 dispTypeField.setFieldValue("C");
	    return;
            }
	else 
	    {
	    if (value.startsWith("=")) 
                value = 
                   DragonUI.currentApplication.getStatusManager().getMemoryFileEquivalent(value);
	    thisHeader = new DImageHeader(value);
	    if (!thisHeader.isInitialized())
	         {
                 UiErrorDisplay errDisp = (UiErrorDisplay)
                      ApplicationManager.getErrorDisplay();
		 errDisp.sendError(thisHeader.getErrorMessage());
		 return;
		 }
            }
	String parentID = parent.getName();
        if (parentID.compareTo("rHEA")== 0)
	    {
            processHeaFields(parent, thisHeader);
	    }
	else if ((parentID.compareTo("rMEA")== 0) ||
		 (parentID.compareTo("rBUF")== 0))
	    {	
            processMeaFields(value, parent, thisHeader);
	    }
        else if (parentID.compareTo("rSUB")== 0)
	    {
            processSubFields(parent, thisHeader);
	    }
	else
	    {
	    processDisplayType(parent,thisHeader);
	    }
	}

	/**
	 * Set fields in MEA panel based on header values.
	 */
    protected void processMeaFields(String value,
                                    DragonPanel parent,
				    DImageHeader header)
	{
	NumberFormat nformat = NumberFormat.getInstance();
        nformat.setMaximumFractionDigits(2);
	DragonField units = parent.getField("^U");
	if (units != null)
             units.setFieldValue(header.getUnitname());
	DragonField xcell = parent.getField("^XF");
	if (xcell != null)
             xcell.setFieldValue(nformat.format(header.getXcell_size()));
	DragonField ycell = parent.getField("^YF");
	if (ycell != null)
             ycell.setFieldValue(nformat.format(header.getYcell_size()));
        // we have already dealt with the display type for memory files
	if (!value.startsWith("="))
	    processDisplayType(parent,header);
	}

	/** Set fields in HEA panel based on header values.  */
    protected void processHeaFields(DragonPanel parent,
				    DImageHeader header)
	{
	DragonField fld = parent.getField("^FXI");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getImg_x()));
	fld = parent.getField("^FYI");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getImg_y()));
	fld = parent.getField("^RFX");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getRef_x()));
	fld = parent.getField("^RFY");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getRef_y()));
	fld = parent.getField("^MU");
	if (fld != null)
             fld.setFieldValue(header.getUnitname());
	fld = parent.getField("^CLX");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getXcell_size()));
	fld = parent.getField("^CLY");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getYcell_size()));
	fld = parent.getField("^ECUTIL");
	if (fld != null)
             fld.setFieldValue(header.getComment());
	fld = parent.getField("^ESID");
	if (fld != null)
             fld.setFieldValue(header.getScene());
	fld = parent.getField("^ESS");
	if (fld != null)
             fld.setFieldValue(header.getSubscene());
	fld = parent.getField("^ECF");
	if (fld != null)
             fld.setFieldValue(header.getClf());
	fld = parent.getField("^ESRC");
	if (fld != null)
             fld.setFieldValue(header.getSource());
	fld = parent.getField("^EB");
	if (fld != null)
             fld.setFieldValue(header.getBand());
	fld = parent.getField("^ET");
	if (fld != null)
             fld.setFieldValue(header.getFileType());
	fld = parent.getField("^CALUNIT");
	if (fld != null)
             fld.setFieldValue(header.getZUnit());
	fld = parent.getField("^CALMULT");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getZScale()));
	fld = parent.getField("^CALOFF");
	if (fld != null)
             fld.setFieldValue(String.valueOf(header.getZOffset()));

        if (header.getFileType().compareTo("I") == 0)
	     {
	     parent.enableTab(1,false);
	     clearClassNames(parent,header);
	     }
	else
	     {
	     parent.enableTab(1,true);
	     processClassNames(parent,header);
	     }
	}

	/**
	 * Set fields in SUB panel based on header values.
	 */
    protected void processSubFields(DragonPanel parent,
				    DImageHeader header)
	{
        boolean bEnable = false;
	DragonField nlines = parent.getField("^NLS");
	if (nlines != null)
             nlines.setFieldValue(String.valueOf(header.getNLines()));
	DragonField npix = parent.getField("^NPS");
	if (npix != null)
             npix.setFieldValue(String.valueOf(header.getNPix()));
	if (header.getBitsPerPix() == 8)
	     {
	     bEnable = false;
	     }
	else
	     {
	     bEnable = true;
	     }
        DragonField fld = parent.getField("^SM");
	if (fld != null)
	     fld.setEnabled(bEnable);
	processDisplayType(parent,header);
	}

      /**
       * If the panel has a "display" type option, set it
       * to 'C' if the file is classified.
       */
    protected void processDisplayType(DragonPanel parent,
				    DImageHeader header)
	{
	DragonField dispType = parent.getField("^DSP");
	if (dispType == null)
	    return;
        if (header.getFileType().startsWith("I"))
	    dispType.setFieldValue("G");
	else if (header.getFileType().startsWith("C"))
	    dispType.setFieldValue("C");
	else if (header.getFileType().startsWith("L"))
	    dispType.setFieldValue("C");
	}
    

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ImgHeaderCallback.java,v 1.20 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }


