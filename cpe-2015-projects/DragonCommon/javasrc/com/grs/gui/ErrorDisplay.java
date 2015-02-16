/**
 * ErrorDisplay
 *
 * Copyright 2001 by Goldin-Rudahl Associates
 * 
 * Created by Sally Goldin, 3/22/2001
 *
 * $Id: ErrorDisplay.java,v 1.1 2001/11/16 16:38:20 goldin Exp $
 * $Log: ErrorDisplay.java,v $
 * Revision 1.1  2001/11/16 16:38:20  goldin
 * Move non-Dragon-specific files to new package
 *
 * Revision 1.10  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.9  2001/10/17 10:27:59  goldin
 * Make ErrorDisplay an interface, create UI and generic versions
 *
 * Revision 1.8  2001/05/18 10:49:14  goldin
 * Don't exit while there are still messages to be displayed
 *
 * Revision 1.7  2001/05/11 19:06:00  goldin
 * Change IPC file format; enhance & debug tracing
 *
 * Revision 1.6  2001/05/10 13:14:51  goldin
 * Continue implementation of SigFile and scaling callbacks
 *
 * Revision 1.5  2001/05/02 15:11:41  goldin
 * Implement message and progress IPC file processing
 *
 * Revision 1.4  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.3  2001/04/04 15:24:50  goldin
 * Added partial filename filtering, validation, to file chooser
 *
 * Revision 1.2  2001/03/26 17:32:08  goldin
 * Further work implementing FileChooser
 *
 * Revision 1.1  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 */

package com.grs.gui;
import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.*;

/**
 * This is an interface that encapsulates the display of errors.
 */
public interface ErrorDisplay
    {
      /**
       * Display a particular error message with arbitrary added text.
       * @param titleKey Title string (or null if no title)
       * @param msgKey Key for internationalized part of message
       * @param addOn  Additional text to be added - not internationalized.
       */
    public void showError(String titleKey, 
			  String msgKey,
			  String addOn);
      /**
       * Display a prefetched and translated error message
       * @param titleKey Title string (or null if no title)
       * @param msgText Text for message message
       */
    public void showError(String titleKey, 
			  String msgText);

    }

