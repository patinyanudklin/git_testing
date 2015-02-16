/* LanguageCallback.java
 *
 * ~~ Copyright 2001-2015 Goldin-Rudahl Associates
 * ~~ EndC
 *
 * $Id: LanguageCallback.java,v 1.7.2.1 2015/01/01 10:32:30 rudahl Exp $
 * $Log: LanguageCallback.java,v $
 * Revision 1.7.2.1  2015/01/01 10:32:30  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.9  2015/01/01 09:56:15  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.8  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.7  2006/11/30 05:25:47  goldin
 * Modify textsource to handle multiline messages; change constructor to take a possibly null key prefix string
 *
 * Revision 1.6  2006/07/15 11:39:36  goldin
 * Don't show a button if there's no GIF file for a language
 *
 * Revision 1.5  2006/01/24 09:14:53  goldin
 * Make dialog for languages come up on top (for install)
 *
 * Revision 1.4  2005/12/08 08:02:23  goldin
 * Use images to illustrate language, not text, to avoid font problems
 *
 * Revision 1.3  2005/11/26 09:23:46  goldin
 * Make language codes always be lower case
 *
 * Revision 1.2  2005/07/31 08:34:31  goldin
 * Working in I18N of Installer
 *
 * Revision 1.1  2005/07/29 09:37:19  goldin
 * Move to common so that functions can be shared with installer
 *
 * Revision 1.9  2005/07/24 13:18:47  goldin
 * Set correct font in languge selection dialog so that we get Chinese
 *
 * Revision 1.10  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.9  2005/06/27 08:57:09  goldin
 * Figure out what lags to display from file
 *
 * Revision 1.8  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.7  2001/11/29 16:12:33  goldin
 * Add common pkg import
 *
 * Revision 1.6  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.5  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.4  2001/09/05 15:08:53  goldin
 * Change I18NTextSource constructors
 *
 * Revision 1.3  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.2  2001/04/17 12:10:15  goldin
 * Modifications made with Together
 *
 * Revision 1.1  2001/03/21 13:05:39  goldin
 * Add language selection and config file processing functionality
 *
 */

package com.grs.dragon.common;
import com.grs.gui.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.io.*;
import java.util.*;

//********************************************************************
/** 
 *  This class implements the Callback interface. It handles the
 *  display and processing of the language selection dialog.
 *  This dialog requires special handling because
 *    1) we only want to enable languages for which a message
 *       file and a GIF file are available 
 *    2) the labels on the language radio buttons each are in
 *       the respective languages, so cannot be read from a
 *       language file.
 * There are two concrete subclasses of this class, one used
 * in Dragon and one in the Installer.
 */
public abstract class LanguageCallback implements Callback,
                                         ActionListener
    {
    private static String langFileName = "drag5-00.messages";

    private static String imagePath = "com/grs/dragon/common/";
    private static String imageSuffix = ".gif";

    protected JOptionPane languageDialog = null;

    protected static String[] codes = null;

    protected String[] labels = null; 

    protected JRadioButton[] buttons = null;

    protected String currentLanguage = "EN";

    protected int selectedIndex = -1;

    protected int labelCount = 0;  // how many languages do we have?

    protected String title = null;

    protected String changeMessage = null;

    protected String OkString = null;
    protected String CancelString = null;

    protected boolean bOkClicked = false;
      
      /** 
       *  If true, this is the language dialog in the instaler,
       *  otherwise it is the one in the Dragon preferences.
       */
    protected boolean bInstaller = false;

      /**
       * Hold on to the field passed in by the execute method.
       * This gives us a handle to the DragonUI instance, so
       * we can then access the help area.*/
    protected DragonField dummyField = null;

      /**
       * Constructor retrieves messages for dialog from
       * the I18N text source, and creates the confirmation
       * dialog, which can then be reused.
       * @param bInstaller  If true, this is the installer 
       */
    public LanguageCallback(boolean bInstaller)
        {
	this.bInstaller = bInstaller;
	ButtonGroup group = new ButtonGroup();
	initializeCodes();
	labelCount = getLabels();
	buttons = new JRadioButton[codes.length];
	if (labelCount < 0)  // error opening the language file
	    {
	    System.exit(0);
	    }
        
	//int rows = labelCount/2;  // make two cols of buttons
	//if (rows * 2 != labelCount)
	//    rows += 1;
        JPanel mainPanel = new JPanel(new BorderLayout());
        JPanel subPanel = new JPanel(new GridLayout(0,2,30,0));

	mainPanel.setBorder(BorderFactory.createMatteBorder(15,15,15,15,
						  mainPanel.getBackground()));
	subPanel.setBorder(BorderFactory.createMatteBorder(5,5,5,5,
						  subPanel.getBackground()));
	title = ApplicationManager.getTextSource().getI18NText(TextKeys.SELECTLANG,
						       "Select Lang");
	for (int i = 0; i < labelCount; i++)
	    {
            String imageFile = 
                  new String(codes[i].toLowerCase() + imageSuffix);
	    JPanel oneButtonPanel = new JPanel(new BorderLayout());
	    JRadioButton rbtn = new JRadioButton("");
	    oneButtonPanel.add(rbtn,BorderLayout.WEST);
	    oneButtonPanel.add(new JLabel(new ImageIcon(imageFile),
                                 SwingConstants.LEFT), BorderLayout.CENTER);
	    subPanel.add(oneButtonPanel);

	    //if (codes[i].startsWith("ZH"))
 	    //    rbtn.setFont(
            //       ApplicationManager.getFontProcessor().getFont(codes[i]));
	    //else 
	    //    rbtn.setFont(
            //       ApplicationManager.getFontProcessor().getFont("UNICODE"));

	    group.add(rbtn);
	    rbtn.addActionListener(this);
	    buttons[i] = rbtn;
	    }
        mainPanel.add(subPanel,BorderLayout.CENTER);
	currentLanguage = ApplicationManager.getCountry();
        if (currentLanguage == null)
            currentLanguage = codes[0];
        resetSelectedIndex();
	checkHelpFiles();
	OkString = ApplicationManager.getTextSource().getI18NText(TextKeys.OK,
								   "OK");
	CancelString = ApplicationManager.getTextSource().getI18NText(TextKeys.CANCEL,
								   "CANCEL");
	String options[] = {OkString, CancelString};
        languageDialog = new JOptionPane(mainPanel,JOptionPane.PLAIN_MESSAGE,
					JOptionPane.OK_CANCEL_OPTION,
					null,options);
        changeMessage = ApplicationManager.getTextSource().getI18NText(
                                             TextKeys.LANGCHANGE,"");
        changeMessage = "<html><head></head><body><font size=-1><p>" +
	                changeMessage + "</font></body></html";
	}

      /**
       * Open the messages file and read the first token
       * in each line, saving them in the 'codes' array.
       * They will then be used as keys to get the language
       * names. We only do this once; codes is static.
       */
    protected void initializeCodes()
       {
       if (codes != null)
 	  return;
       BufferedReader reader = null; 
       ArrayList<String> tempList = new ArrayList<String>();
       try
	  {
	  reader = 
             new BufferedReader(new FileReader(langFileName));

	  try
	     {
	     String line = null;
	     while ((line = reader.readLine()) != null)
		{
		int spacePos = line.indexOf(" ");
		if (spacePos > 0)
		    { 
                    String oneCode = line.substring(0,spacePos);
		    File checkFile = 
                        new File(oneCode.toLowerCase() + imageSuffix);
		    if (checkFile.exists())
		        tempList.add(oneCode);
		        /* Don't add code to list if no GIF file */
                    }
		}
	     reader.close();
	     }
	  catch (IOException io)
	     {
	     tempList.add("EN");
	     }
	  }
       catch (FileNotFoundException fnf)
	  {
	  System.out.println("Cannot read language list file " +
                              langFileName);
	  }
       codes = (String[]) tempList.toArray(new String[1]);
       }

      /**
       * Factorization of constructor. Retrieves labels
       * from text source, stores them in the msgs array, and
       * returns the number of non-null messages.
       */
    protected int getLabels()
        {
	int count = 0;
	int len = codes.length;
        labels = new String[len];
	I18NTextSource textSource = new I18NTextSource("00",
				  ApplicationManager.getHomeDirectory(),null);
        if (!textSource.isInitialized())
	    {
            return -1;
	    }
	for (int i = 0; i < len; i++)
	    {
	    String msg = textSource.getI18NText(codes[i],"");
	    if ((msg.length() > 0) &&
		(!msg.startsWith("`")))
	        {
		labels[count] = msg;
		count++;
		}
	    }
	return count;
	}

      /**
       * Factorization of constructor. Runs through the
       * list of languages, and checks to see if the file
       * exists. If not, disables that radio button.
       * Checks home directory, language subdirectory,
       * and language subdirectory under "system", so 
       * will work for both Dragon and the installer.
       * 
       */
    protected void checkHelpFiles()
        {
	for (int i = 0; i < labelCount; i++)
	    {
	    buttons[i].setEnabled(true);
	    // check the language subdirectory
	    String fileName = null; 
	    if (bInstaller)
	       {
               fileName = ApplicationManager.getHomeDirectory() +
	             File.separator + "system" + 
		     File.separator + codes[i].toLowerCase() +
		     File.separator +       
                     "drag-installer-" + codes[i].toLowerCase() + ".messages";
	       }
            else
	       {
	       fileName = ApplicationManager.getHomeDirectory() +
		     File.separator + codes[i].toLowerCase() +
		     File.separator +       
                     "drag5-" + codes[i].toLowerCase() + ".messages";
	       }
	    File checkFile = new File(fileName);
	    if (!checkFile.exists())
	       {
	       buttons[i].setEnabled(false);
	       }
	    }
	}

      /** Primary method of a callback class.
       *  Displays the dialog and waits for user input.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        dummyField = field;
	bOkClicked = false;
        Component monitoredWindow = field.getParentComponent();
	if (monitoredWindow != null)
	    {
	    languageDialog.setValue(null);
	    JDialog dlg = languageDialog.createDialog(monitoredWindow,title);
            dlg.setVisible(true);
	    dlg.toFront();
            Object val = languageDialog.getValue();
	    if ((val != null) && (val instanceof String))
	        {
		String value =  (String) val;
		if (value.compareTo(OkString) == 0)
		     {
		     setCurrentLanguage();
		     bOkClicked = true;
		     }
		else 
		     {
		     resetSelectedIndex();
		     }
		}
	    else
	        {
		resetSelectedIndex();
	        }
	    dlg.setVisible(false);
	    setHelpMsg("");
            }
	}

    /**
     * Process the selected index to reset the language
     * Then update the config file with this new information.
     * This behavior is different for different subclasses.
     */
    abstract protected void setCurrentLanguage();

    /**
     * Reset the selected index, which may have been changed by
     * user before the user chose cancel, to correspond to the
     * currently selected language. Then selects the corresponding
     * radio button.
     */
    protected void resetSelectedIndex()
        {
        for (int i = 0; i < labelCount; i++)
	    {
	    if (currentLanguage.compareTo(codes[i]) == 0)
	        {
	        selectedIndex = i;
		buttons[i].setSelected(true);
		break;
		}
	    }
	}

    /**
     * Method from the ActionListener interface
     */
    public void actionPerformed(ActionEvent e)
        {
        int oldIndex = selectedIndex;
	JRadioButton btn = (JRadioButton) e.getSource();
        for (int i = 0; i < labelCount; i++)
	    {
	    if (buttons[i] == btn)
	        {
		selectedIndex = i;
		break;
		}
	    }
	if (oldIndex != selectedIndex)
	    {
	    setHelpMsg(changeMessage);
	    }
        }

      /**
       * Set help message to passed string.
       * This method is different for different subclasses.
       */
    protected abstract void setHelpMsg(String msg);


      /**
       * determine if they exited with Ok or cancel 
       * @return true if exited with ok.
       */
    public boolean wasOkClicked()
       {
       return bOkClicked;
       }

    }

// End of LanguageCallback.java

