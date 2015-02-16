/**
 * FixedLengthDocument 
 *
 * Created by Sally Goldin, 3/16/2001
 * ~~ Copyright Sally Goldin Rudahl 2001-2014
 * ~~ EndC
 *
 * $Id: FixedLengthDocument.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: FixedLengthDocument.java,v $
 * Revision 1.3.2.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.4  2010/10/10 04:18:17  rudahl
 * adapt to java 1.6
 *
 * Revision 1.3  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.2  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 */
package com.grs.gui;
import java.awt.Toolkit;
import javax.swing.*;
import javax.swing.text.*;

/**
 * This class is derived from an example in Eckstein, Loy and Wood,
 * <i>Java Swing</i>, page 772. It implements a subclass of
 * PlainDocument which retricts its length to the value entered
 * when the document is constructed.*/
public class FixedLengthDocument extends PlainDocument
    {
      /** maximum length allowed.
       */
    protected int maxLength = -1;  // indicates no restrictions

      /**
       * Constructor
       */
    public FixedLengthDocument(int maxLength)
        {
	if (maxLength >= 0)
	    {
	    this.maxLength = maxLength;
	    }
        }

      /**
       * Allows length to be changed after construction.
       */
    public void setMaxLength(int newMax)
        {
	maxLength = newMax;
        }

      /**
       * Override insertString. If the insertion would exceed the
       * maxLength, and the maxLength is >=0, beep and do nothing
       * else. Otherwise, call the superclass method.
       */
    public void insertString(int offset, String str, AttributeSet attset)
         throws BadLocationException
        {
	if (maxLength < 0)  // no limit
	    super.insertString(offset,str,attset);
	else if (getLength() + str.length() > maxLength)
            Toolkit.getDefaultToolkit().beep();
	else 
	    super.insertString(offset,str,attset);
	}
    
    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FixedLengthDocument.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }
