/**  FontProcessor.java
 *
 *   ~~ Copyright  2005-2015  by Sally Goldin & Kurt Rudahl
 *   ~~ EndC
 *   Created by Sally Goldin, 7/22/2005
 *
 *   $Id: FontProcessor.java,v 1.4.2.1 2015/01/01 13:51:54 rudahl Exp $
 *   $Log: FontProcessor.java,v $
 *   Revision 1.4.2.1  2015/01/01 13:51:54  rudahl
 *   consolidating Dragon and OpenDragon
 *
 *   Revision 1.5  2007/07/30 09:12:19  goldin
 *   Get rid of unchecked warnings
 *
 *   Revision 1.4  2007/01/05 07:41:58  rudahl
 *   added Whatis info
 *
 *   Revision 1.3  2006/04/17 04:47:18  goldin
 *   Move setupFonts method to FontProcessor itself
 *
 *   Revision 1.2  2005/12/20 08:14:17  goldin
 *   Add FontProcessor
 *
 *   Revision 1.1  2005/07/24 13:28:48  goldin
 *   New class to handle internationalized fonts that aren't in the default unicode font
 *
 *   Revision 1.1  2005/07/22 11:09:38  goldin
 *   New class for processing and indexing fonts
 *
 *
 */
package com.grs.gui;
import java.awt.*;
import javax.swing.*;
import javax.swing.plaf.*;
import java.util.*;

/**
 * This class handles the creation of fonts that
 * are needed for internationalization. It returns
 * these fonts, as needed, when requested.
 * The idea is to provide one centralized font source
 * for an entire application.
 */
public class FontProcessor
   {
   /* maps language codes to fonts */
   private Hashtable<String,Font> fontMapTable = null;

   /**
    * Constructor creates the basic fonts that
    * are needed and stores them in the hash table
    * with relevant keys. Our assumption is that
    * we can use Lucida Sans Unicode for almost
    * everything, except Chinese, Japanese and Korean.
    * @param bIsWindows  If true, this is a windows system.
    *                    Use MS default unicode font.
    */
   public FontProcessor(boolean bIsWindows)
      {
      fontMapTable = new Hashtable<String,Font>();
      Font uniFont = null;

      
      if (bIsWindows)
         uniFont = new Font("MS Sans Serif", Font.PLAIN,
				11);
      else
	 uniFont = new Font("Lucida Sans Unicode", Font.PLAIN,
				11);
      if (uniFont != null)
	  {
	  fontMapTable.put("DEFAULT",uniFont);
	  fontMapTable.put("UNICODE",uniFont);
	  }
      else 
	  System.out.println("Cannot create unicode font");

      Font chineseFont = new Font("SimHei", Font.PLAIN, 11);
      if (chineseFont != null)
	  fontMapTable.put("ZH_TW", chineseFont);
      else
	  System.out.println("Cannot create Chinese font");

      }


     /**
      * return the font that matches the passed key,
      * or null if not found.
      */
    public Font getFont(String key)
       {
       Font retFont = null;
       retFont = (Font) fontMapTable.get(key);
       if (retFont == null)
          System.out.println("No font found for key " + key);
       return retFont;
       }

     /**
      * Use the UI Manager to set the font on various
      * categories of UI objects.
      * @param language  Two letter code for current language
      * @param componentRoot Root of UI to be updated with new fonts
      */
    public void setupFonts(String language, Component componentRoot)
        {
        FontProcessor fontProc = ApplicationManager.getFontProcessor();
        FontUIResource defaultFont = null; 
	if (language.startsWith("ZH"))
           defaultFont = 
             new FontUIResource(fontProc.getFont(language));
	if (defaultFont == null)
           defaultFont = 
             new FontUIResource(fontProc.getFont("DEFAULT"));

        UIManager.put("Button.font", defaultFont);
        UIManager.put("Dialog.font", defaultFont);
        UIManager.put("Label.font", defaultFont);
        UIManager.put("Table.font", defaultFont);
        UIManager.put("TextField.font", defaultFont);
        UIManager.put("ScrollPane.font", defaultFont);
        UIManager.put("ComboBox.font", defaultFont);
        UIManager.put("CheckBox.font", defaultFont);
        UIManager.put("TitledBorder.font", defaultFont);
        UIManager.put("RadioButton.font", defaultFont);
        UIManager.put("ToolTip.font", defaultFont);
        UIManager.put("TextPane.font", defaultFont);
        UIManager.put("TextArea.font", defaultFont);

        UIManager.put("Tree.font", defaultFont);
        UIManager.put("List.font", defaultFont);

        UIManager.put("MenuBar.font", defaultFont);
        UIManager.put("Menu.font", defaultFont);
        UIManager.put("MenuItem.font", defaultFont);
        UIManager.put("TableHeader.font", defaultFont);
        UIManager.put("TabbedPane.font", defaultFont);

        SwingUtilities.updateComponentTreeUI(componentRoot);
        }








  }
