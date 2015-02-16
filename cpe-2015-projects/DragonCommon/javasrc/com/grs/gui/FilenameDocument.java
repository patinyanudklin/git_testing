/**
 * FilenameDocument 
 *
 * Created by Sally Goldin, 9/13/2002
 *
 * $Id: FilenameDocument.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $
 * $Log: FilenameDocument.java,v $
 * Revision 1.3  2007/01/05 07:41:58  rudahl
 * added Whatis info
 *
 * Revision 1.2  2005/12/10 09:35:50  goldin
 * Fix FilenameDocument to allow unicode characters in filenames
 *
 * Revision 1.1  2002/09/13 23:56:18  goldin
 * Add filenamedocument class
 *
 */
package com.grs.gui;
import java.awt.Toolkit;
import javax.swing.*;
import javax.swing.text.*;

/**
 * This class implements a subclass of PlainDocument
 * which only allows characters that we want to permit
 * in filenames, specifically all letters and digits,
 * periods, underscores and dashes.
 * If any other character is included, it beeps and rejects
 * the string.
 */
public class FilenameDocument extends PlainDocument
    {
      /** characters NOT allowed.
       */
    protected static final String DISALLOWED_CHARACTERS  = 
    "=()&*%$|<>?{}[]\"'`!^";

    protected static final String PATH_CHARACTERS =":\\/";

    protected boolean bForPath = false;
    protected String testString = null;

      /**
       * Constructor
       * If this field allows paths, we should permit additional characters
       */
    public FilenameDocument(boolean bPath)
        {
	bForPath = bPath;
        if (bForPath)
	   testString = DISALLOWED_CHARACTERS;
	else
           testString = DISALLOWED_CHARACTERS + PATH_CHARACTERS;
        }

      /**
       * Override insertString. If the insertion would include a
       * character not allowed in filenames, beep and don't
       * insert.
       * Otherwise, call the superclass method.
       */
    public void insertString(int offset, String str, AttributeSet attset)
         throws BadLocationException
        {
	char [] theChars = str.toCharArray();
	int len = theChars.length;
	for (int i = 0; i < len; i++)
	    {
	    char c = theChars[i];
	    if ((c <= 0x20) || (testString.indexOf(c) >= 0))
	        {
                Toolkit.getDefaultToolkit().beep();
		return;
		}
	    }
	super.insertString(offset,str,attset);
	}
    

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: FilenameDocument.java,v 1.3 2007/01/05 07:41:58 rudahl Exp $ \n";
	}
    }
