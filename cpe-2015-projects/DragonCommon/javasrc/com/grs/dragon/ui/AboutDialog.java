/* AboutDialog.java
 *
 * Copyright  2006-2007  Goldin-Rudahl Systems and King Mongkut's
 *  University of Technology Thonburi
 *
 * Created by Sally Goldin, 10/5/2001
 *
 * $Id: AboutDialog.java,v 1.10 2007/04/07 04:09:35 rudahl Exp $
 * $Log: AboutDialog.java,v $
 * Revision 1.10  2007/04/07 04:09:35  rudahl
 * added product-spec to whatis info
 *
 * Revision 1.9  2007/02/03 09:36:03  goldin
 * Change copyright to GSI
 *
 * Revision 1.8  2007/01/06 05:14:41  rudahl
 * added Whatis info
 *
 * Revision 1.7  2006/12/30 11:24:13  goldin
 * Modify to show version and builddate if available
 *
 * Revision 1.6  2006/12/17 11:39:34  goldin
 * Add msg about contributors
 *
 * Revision 1.5  2006/03/05 05:14:08  goldin
 * Add program title to OpenDragon about dialog
 *
 * Revision 1.4  2006/02/24 11:09:20  goldin
 * Change copyright date
 *
 * Revision 1.3  2005/07/24 12:41:54  goldin
 * Added font handling - copied from 5.6
 *
 *
 * Revision 1.8  2005/06/20 07:56:19  goldin
 * About dialog customized for open dragon
 *
 * Revision 1.1  2005/04/04 08:50:14  goldin
 * Version specific About dialog with correct copyright
 *
 * Revision 1.6  2004/12/29 11:30:08  goldin
 * Change company name
 *
 * Revision 1.5  2004/12/28 09:16:48  goldin
 * Fix copyright date
 *
 * Revision 1.4  2002/01/22 14:52:24  goldin
 * Change copyright date
 *
 * Revision 1.3  2001/11/16 16:41:07  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.1  2001/10/05 11:05:34  goldin
 * Separate Dialog from callback to allow reuse by Viewport
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.awt.*;
import javax.swing.*;
import javax.swing.plaf.*;

/* THIS IS THE OPEN DRAGON VERSION OF THIS DIALOG */
//********************************************************************
/** 
 *  This class implements an About dialog. Originally it was
 *  part of the AboutCallback class. However, we have separated
 *  it out so that it can be used in the Viewport without requiring
 *  all the classes associated with DragonField (which would be required
 *  in a Callback object. The AboutCallback class uses an instance
 *  of this dialog. We do not directly extend JOptionPane, but rather,
 *  hold a reference to one, because we need to do some work to
 *  create the "message" before we can call the JOptionPane constructor.
 */
public class AboutDialog
    {
    public static String uiTitle = "OpenDragon";

    protected JOptionPane aboutDialog = null;

    protected final static String[] keys = {"%h9400.0",
					  "Global Software Institute",
					  "P.O. Box 644",
					  "Hadley, MA 01035 U.S.A.",
					  "Fax: +1-815-331-0913",
					  "Email: draco@global-soft.org",
					  "Web: www.global-soft.org",
					  "%h9400.7",
					  "%h9400.8",
					  "%h9400.9",
					  "%h9400.10",
					  "%h9400.11",
					  "%h9400.12",
					  "%h9400.13",
					  "%h9400.14",
                                          "%m10000.0",
                                          "%m10000.1"};

    protected String[] msgs = new String[keys.length];

    protected JDialog m_dlg = null;

    protected String title = null;
    protected I18NTextSource textSource = null;

      /**
       * Constructor retrieves messages for dialog from
       * the I18N text source, and creates the confirmation
       * dialog, which can then be reused.
       */
    public AboutDialog()
        {
	String version = null;
        String buildDate = null;
	String programTitle  = null;
        String buildString = null;
        textSource = ApplicationManager.getTextSource();
	int msgCount = getMessages();
        ConfigFileProcessor cfgProcessor = 
           new ConfigFileProcessor(ApplicationManager.getHomeDirectory());
        if (cfgProcessor.isInitialized())
            {
	    version = cfgProcessor.getVersion();
            buildDate = cfgProcessor.getBuildDate();
            }
        buildString = textSource.getI18NText("%m10000.3","Built on");
        if ((version != null) && (buildDate != null))
	    programTitle = uiTitle +  
		" " + version + "    " +buildString+ " " + buildDate;
	else
	    programTitle = uiTitle +  
	     " " + ApplicationManager.getVersion();
        JPanel messagePanel = new JPanel(new GridLayout(msgCount + 4,0));
        messagePanel.add(new JLabel(programTitle));
	messagePanel.add(new JLabel("Copyright 1988-2007 by the Global Software Institute"));
	messagePanel.add(new JLabel("    and King Mongkut's University of Technology Thonburi"));
	messagePanel.add(new JLabel("  "));
	for (int i = 0; i < msgCount; i++)
	    {
            if ((i==0) || (i == 7))
	        messagePanel.add(new JLabel(msgs[i]));
	    else
	        messagePanel.add(new JLabel("     " + msgs[i]));
	    }
        aboutDialog = new JOptionPane(messagePanel,JOptionPane.PLAIN_MESSAGE,
					JOptionPane.DEFAULT_OPTION);

        title = textSource.getI18NText(TextKeys.ABOUT,"About");
        }

      /**
       * Factorization of constructor. Retrieves messages
       * from text source, stores them in the msgs array, and
       * returns the number of non-null messages.
       */
    protected int getMessages()
        {
	int count = 0;
	int len = keys.length;
	for (int i = 0; i < len; i++)
	    {
            String msg = null;
	    if (keys[i].startsWith("%"))
	        msg = textSource.getI18NText(keys[i],"");
            else
                msg = keys[i];
	    if ((msg.length() > 0) &&
		(!msg.startsWith("`")))
	        {
		msgs[count] = msg;
		count++;
		}
	    }
	return count;
	}

      /** 
       *  Displays about dialog and waits for user action.
       *  @param parentWindow Component on which the dialog should be 
       *                      centered.
       */
    public void showAboutDialog(Component parentWindow)
        {
	if (parentWindow != null)
	    {
	    aboutDialog.setValue(null);
	    JDialog dlg = aboutDialog.createDialog(parentWindow,title);
	    dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
	    SwingUtilities.updateComponentTreeUI(dlg);
            dlg.setVisible(true);
            Object val = aboutDialog.getValue();
	    dlg.setVisible(false);
            }
	}

      /** 
       *  Displays about dialog but does not wait
       *  @param parentWindow Component on which the dialog should be 
       *                      centered.
       *  @param czTempTitle  string used as temporary title
       */
    public void showAboutDialog(Component parentWindow, String czTempTitle)
        {
	if (parentWindow != null)
	    {
	    aboutDialog.setValue(null);
	    m_dlg = aboutDialog.createDialog(parentWindow,czTempTitle);
	    m_dlg.setFont((FontUIResource) UIManager.get("Dialog.font"));
	    SwingUtilities.updateComponentTreeUI(m_dlg);
            m_dlg.setVisible(true);
            }
	}

      /** 
       *  Wait for user to exit dialog
       */
    public void waitAndKillDialog()
        {
	if (m_dlg != null)
	    {
            Object val = aboutDialog.getValue();
	    m_dlg.setVisible(false);
	    m_dlg = null;
            }
	}

      /** get the title string which is SUPPOSED to be displayed
       *  @return    composed i18n'd title string
       */
    public String getTitle()
        {
	return title;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#) OpenDragon $Id: AboutDialog.java,v 1.10 2007/04/07 04:09:35 rudahl Exp $ \n";
	}
    }

