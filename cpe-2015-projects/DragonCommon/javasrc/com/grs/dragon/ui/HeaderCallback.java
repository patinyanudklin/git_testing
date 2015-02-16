/* 
 * HeaderCallback.java
 *
 * Copyright Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 10/23/2001
 *
 * $Id: HeaderCallback.java,v 1.5 2006/02/11 07:15:31 goldin Exp $
 * $Log: HeaderCallback.java,v $
 * Revision 1.5  2006/02/11 07:15:31  goldin
 * Enable classnames tab even if no classnames yet
 *
 * Revision 1.4  2005/12/23 10:40:31  goldin
 * Don't assume that index into labels is class number
 *
 * Revision 1.3  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/10/12 11:41:05  goldin
 * New callbacks for HEA panel
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.util.*;
import javax.swing.*;

/** 
 *  This class is an abstract base class which holds some common
 *  code used by both the ImgHeaderCallback and HeaFileTypeCallback
 *  classes.
 * @author  goldin*/
public abstract class HeaderCallback implements Callback 
    {
    protected static final String[] clsFieldNames =
      {"^CNM0","^CNM1","^CNM2","^CNM3","^CNM4","^CNM5","^CNM6","^CNM7",
       "^CNM8","^CNM9","^CNM10","^CNM11","^CNM12","^CNM13","^CNM14","^CNM15",
       "^CNM16"};

      /** Primary method of a callback class.
       */
    public abstract void executeCallback(DragonField field);

    protected void processClassNames(DragonPanel parent,
				DImageHeader header)
        {
	int numlabels = clsFieldNames.length;
	String[] classnames = header.getClassnames();
        DragonField fld;
	for (int i = 0; i < numlabels; i++)
	    {
	    fld = parent.getField(clsFieldNames[i]);
	    if (fld != null)
                 fld.setFieldValue(classnames[i]);
	    }
	}

    protected void clearClassNames(DragonPanel parent,
				   DImageHeader header)
        {
	int numlabels = clsFieldNames.length;
        DragonField fld;
	for (int i = 0; i < numlabels; i++)
	    {
	    fld = parent.getField(clsFieldNames[i]);
	    if (fld != null)
                 fld.setFieldValue("");
	    }
	}
    }


