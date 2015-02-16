/**
 * ColorEdit
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 11/20/2001
 *
 *  $Id: ColorEdit.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ColorEdit.java,v $
 *  Revision 1.2  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.1  2005/09/15 08:32:47  goldin
 *  Move color chooser to UI package, invoke directly from the UI
 *
 *  Revision 1.1  2001/11/20 18:46:46  goldin
 *  Begin work on color chooser undo
 *
 */
package com.grs.dragon.ui;
import javax.swing.undo.*;
import java.awt.*;

/**
 * This class is used to undo or redo color changes
 * in the ColorChooser class.
 * It maintains two color arrays, the pre-Edit and post-Edit
 * colors.  Undo replaces the post with the pre. Redo does the
 * opposite. Both operations use the reviseColors operation
 * of the ColorChooser, to which they have a reference.
 */
public class ColorEdit extends AbstractUndoableEdit
    {  
      /**
       * indices that are affected by this change.
       */
    protected int minIndex = -1;
    protected int maxIndex = -1;

      /**
       * Arrays where the colors are copied.
       */
    protected Color preColors[] = null;
    protected Color postColors[] = null;
    
      /**
       * Reference to color choose object which actually
       * implements the change
       */
    protected ColorChooser chooser = null;

  protected boolean bDead = false; 

      /**
       * Constructor, called when edit first done.
       * Sets all data.
       * @param chooser Chooser parent
       * @param min     Minimum value changed
       * @param max     Maximum value changed
       * @param oldColors  Original color array [256]
       * @param newColors  New color array [256]
       */
    public ColorEdit(ColorChooser chooser,
		     int min, int max, Color oldColors[], Color newColors[])
        {
        this.chooser = chooser;
	minIndex = min;
	maxIndex = max;
	preColors = new Color[256];
	System.arraycopy(oldColors,0,preColors,0,256);
	postColors = new Color[256];
	System.arraycopy(newColors,0,postColors,0,256);
	bDead = false;
        }

    public void undo() throws CannotUndoException
        {
        super.undo();
        if (bDead) 
            throw new CannotUndoException();
	chooser.reviseColors(minIndex,maxIndex,preColors);
	}

    public void redo() throws CannotRedoException
        {
	super.redo();
        if (bDead)
            throw new CannotRedoException();
	chooser.reviseColors(minIndex,maxIndex,postColors);
	}

    public void die()
        {
	bDead = true;
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ColorEdit.java,v 1.2 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
