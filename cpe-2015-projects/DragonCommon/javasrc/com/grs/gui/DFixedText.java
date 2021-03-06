/*    DFixedText.java
 *
 * Generated by java-pp.pl from DFixedText.java
 * on Mon Jan  8 11:41:04 EST 2001

 * Copyright  2002-2007  Sally Goldin & Kurt Rudahl
 * $Id: DFixedText.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: DFixedText.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.2  2002/01/04 17:26:58  goldin
 * Added ability to have multilines
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.9  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.8  2001/07/25 11:53:18  goldin
 * fix handling of CAL output field
 *
 * Revision 1.7  2001/04/18 15:32:45  goldin
 * Added home directory command line argument
 *
 * Revision 1.6  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.5  2001/01/17 14:18:23  goldin
 * Actually build initial trial panel from XML document
 *
 * Revision 1.4  2001/01/15 14:20:25  goldin
 * Implement new layout options, makeClone methods
 *
 * Revision 1.3  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 * Revision 1.2  2001/01/09 15:58:55  goldin
 * continued work implementing basic appearance of UI components
 *
 * Revision 1.1  2001/01/08 19:34:42  goldin
 * Initial population for new DRAGON-Java UI
 *
 */


package com.grs.gui;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.util.*;

/** This class is used to add fixed text to the response
*   panels. Most of the DragonField data and methods
*   are not used for this subclass. However, we make it a subclass
*   so that it can participate in the layout process.
*   Note we now support multi line labels. 
* @author  goldin
* @version  Mon Jan 08 11:36:01 EST 2001*/
public class DFixedText extends DragonField 
    {
    protected String originalText = null;    

      /**
       * Allow multiple lines of text delimited by 
       * new lines.
       */
    protected JLabel labels[] = null;
   

      /**
       * Constructor, sets the text and creates the label.
       */
    public DFixedText(String name, String text)
        {
	this.name = name;
	this.labelText = text;
        this.originalText = text; 
	setLayout(new BorderLayout());
	label = new JLabel(text);
	if (text.indexOf("\n") < 0)   // single line
	   { 
	   add(label, BorderLayout.NORTH);
	   }
	else // parse into array of text strings and 
   	     // create an array of labels.
	   {
	   StringTokenizer tokenizer = new StringTokenizer(text,"\n");
	   int lineCount = tokenizer.countTokens();
	   labels = new JLabel[lineCount];
	   JPanel inner = new JPanel(new GridLayout(lineCount,1));
	   for (int i = 0; i < lineCount; i++)
	       {
	       String line = tokenizer.nextToken();
	       labels[i] = new JLabel(line);
	       inner.add(labels[i]);
	       }
	   add(inner, BorderLayout.NORTH);
	   }

	}
  
    //********************************************************************
      /**
       * Create and return copy of the present object. Data items
       * that are set during the addition to a panel are not 
       * copied.
       */
    public DragonField makeClone()
        {
	DFixedText clone = new DFixedText(name,this.getLabelText());
	initializeClone(clone);
	return (DragonField) clone;
	}

    //********************************************************************
      /** Tries to set the focus to the control associated
       *  with the field. Since each field subclass has different
       *  controls, this method must be implemented for each one.
       */
    public void requestFocus() 
        {  // fixed text cannot accept focus
	}

    //********************************************************************
       /** Returns the current value for the field. Must be overridden
	*   by each subclass.
	*/
    public String getFieldValue() 
        {
        return labelText;
        }
    
    //********************************************************************
      /** Sets the field to be enabled or disabled depending
       *   on the value of the bEnabled argument.
       *   
       * @param  bEnabled Enablement flag
       */
    public void setEnabled(boolean bEnabled) 
        {
	this.bEnabled = bEnabled;
	label.setEnabled(bEnabled);
        }
    
    //********************************************************************
      /** Allows the panel or other outside class to set the value of the
       *   field. Must be overridden in each subclass,
       * @param  value String to use to set value of the control.
       *   This may need to be transformed to
       *   an index or some other form.
       */
    public void setFieldValue(String value) 
        {
	setLabelText(value);
        }

      /** Calculates the minimum amount of space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum width of graphical components, in pixels.
       */
    public int calculateWidth()
        {
	if (labels == null)
	    {
	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    return metrics.stringWidth(label.getText());
	    }
	else
	    {
	    int maxWidth = 0;
	    FontMetrics metrics = labels[0].getFontMetrics(
						   labels[0].getFont());
	    for (int i = 0; i < labels.length; i++)
	        {
		int currentWidth = metrics.stringWidth(labels[i].getText());
		if (maxWidth < currentWidth)
		    maxWidth = currentWidth;
		}
	    return maxWidth;
	    }
	}

      /** Calculates the minimum amount of vertical space (in pixels) required
       * by the field's graphic components. This will usually be
       * based on things like the width of the label in the current font.
       * @return Minimum height of graphical components, in pixels.
       */
    public int calculateHeight()
        {
        if (labels == null)
	    {
   	    FontMetrics metrics = label.getFontMetrics(label.getFont());
	    return (metrics.getHeight() + 
		    metrics.getMaxDescent());
	    }
	else 
	    {
	    int totalHeight = 0;
	    for (int i = 0; i < labels.length; i++)
	        {
		FontMetrics metrics = labels[i].getFontMetrics(
						   labels[i].getFont());
	        totalHeight += (metrics.getHeight() + 
		                metrics.getMaxDescent());
		}
	    return totalHeight;
	    }
	}

      /**
       * Returns true if passed control is equivalent to present
       * control - that is, all values are the same.
       */
    public boolean equivalent(DragonField field)
        {
	if (!(field instanceof DFixedText))
	    return false;
	if (!commonFieldsEqual(field))
	    return false;
	return true;
	}

      /**
       * Override general method to handle multiple line text.
       */
    public void setLabelText(String text)
        {
	labelText = text;
	if (labels == null)   // single line
	   { 
	   label.setText(text);
	   }
	else // parse into array of text strings and 
   	     // set an array of labels.
	   {
	   StringTokenizer tokenizer = new StringTokenizer(text,"\n");
	   int lineCount = tokenizer.countTokens();
	   if (lineCount > labels.length)
	       lineCount = labels.length;
	   for (int i = 0; i < lineCount; i++)
	       {
	       String line = tokenizer.nextToken();
	       labels[i].setText(line);
	       }
	   }
	}

      /**
       * Reset label to original value set upon creation.
       */
    public void resetLabelText()
        {
	setLabelText(originalText);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DFixedText.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of DFixedText.java

