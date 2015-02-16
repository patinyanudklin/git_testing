/**
 * DragonApp
 *
 * Copyright 2001 by Sally Goldin & Kurt Rudahl
 * 
 * Created by Sally Goldin, 6/8/2001
 *
 *  $Id: DragonApp.java,v 1.9 2005/02/06 09:00:25 goldin Exp $
 *  $Log: DragonApp.java,v $
 *  Revision 1.9  2005/02/06 09:00:25  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.8  2001/11/21 15:17:52  goldin
 *  Make all references to getTimeOffset use ApplicationManager method
 *
 *  Revision 1.7  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.6  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.5  2001/10/19 16:23:12  goldin
 *  Change signature of showTable method
 *
 *  Revision 1.4  2001/08/31 14:01:02  goldin
 *  Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 *  Revision 1.3  2001/08/31 13:33:46  goldin
 *  Implement multiple table displays, ability to kill table displays via incoming command
 *
 *  Revision 1.2  2001/06/27 15:17:47  goldin
 *  Fix CalcParser bugs, table formatting
 *
 *  Revision 1.1  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import java.awt.*;

/**
 * This interface defines a few methods that all primary Dragon
 * application components, such as the Dragon UI and the ManReader,
 * must implement. Most of these methods are used by the common
 * IpcFile-related classes.
 */
public interface DragonApp
    {

      /**
       * Return the primary frame for the application. Used by
       * dialogs to set up parents.
       */
    public Frame getFrame();

      /**
       * Return a path which should be used for temporary
       * files (such as the IpcFiles). This path will often
       * be read from a Dragon config file, but we do not
       * want to expose that here.
       * @return  Directory to use as temporary file path
       */
    public String getTempPath();

      /**
       * Initiate the application exit process. This may involve
       * application-specific cleanup.
       */
    public void doExit();

      /**
       * Refresh the history display of the application, if it
       * has one. 
       */
    public void refreshHistoryDisplay();

      /**
       * Add text to the history list, if the application has
       * one.
       * @param historyText  Text to add
       * @param bComment     If true this msg should be flagged as
       *                        a comment or message
       */
    public void addToHistory(String historyText, boolean bComment);

      /**
       * Return an object that can translate keyed messages.
       * @return Appropriate, initialized I18NTextSource
       */
    public I18NTextSource getTextSource();

      /**
       * Show an informational message.
       * @param msgText  Message text to display
       */
    public void showMessage(String msgText);

      /**
       * Show a warning.
       * @param msgText  Warning message text to display
       */
    public void showWarning(String msgText);

      /**
       * Show an error.
       * @param msgText  Error message text to display
       */
    public void showError(String msgText);

      /**
       * Show an error message made up of a translated and an
       * untranslated string.
       * @param msgKey  Key for translated part of message.
       * @param suffix  Additional text to add
       */
    public void showError(String msgKey, String suffix);

      /**
       * Show a table of data.
       * @param title  Title for table.
       * @param content  HTML text for table.
       * @return true if successful, false if no display available
       */
    public boolean showTable(String title, String content,
			  String tableId);

      /**
       * Hide a single TableDisplay identified by 'messageId', or
       * all if 'messageId' is "*".
       */
    public void killMessage(String messageId);

      /**
       * Return reference to class which will send commands.
       */
    public CommandForwarder getCommandForwarder();

      /**
       * Add a message to a user-log
       * @param msgText Message to add
       * @param bComment If true, mark as comment, not command.
       */
    public void logMessage(String msgText, boolean bComment);

      /**
       * Add a message to the error log file.
       * @param msgText Message to add
       * @param bFirst  Is this the first line to be added for this error?
       */
    public void logError(String msgText, boolean bFirst);
    }

