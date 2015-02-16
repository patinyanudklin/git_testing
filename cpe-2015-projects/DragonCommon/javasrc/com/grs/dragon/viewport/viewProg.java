//***************************************************************
//
//          viewProg.java - Invoke Java methods for DRAGON viewport
//			 K.T. Rudahl
//
//       ~~ Copyright 2001-2010 by Sally Goldin & Kurt Rudahl
//	 ~~ EndC
//***************************************************************
//
//   $Id: viewProg.java,v 1.47.2.2 2010/10/04 05:14:38 rudahl Exp $
//   $Log: viewProg.java,v $
//   Revision 1.47.2.2  2010/10/04 05:14:38  rudahl
//   added changes between 1.44 to 1.47
//
//   Revision 1.47.2.1  2010/10/03 11:21:41  goldin
//   add functions for new ViewportMenu class
//
//   Revision 1.44  2006/04/17 04:46:43  goldin
//   modify to create and set font processor on ApplicationManager
//
//   Revision 1.43  2006/02/12 07:54:18  goldin
//   Make graph windows pop to the top
//
//   Revision 1.42  2005/02/06 09:17:30  goldin
//   Fix javadoc warnings
//
//   Revision 1.41  2005/02/05 13:47:58  goldin
//   Get rid of warnings about finally
//
//   Revision 1.40  2002/09/05 17:51:18  goldin
//   Fix KillInfoViewports
//
//   Revision 1.39  2002/09/05 16:43:30  goldin
//   Add some logging to figure out if it's working
//
//   Revision 1.38  2002/09/05 13:08:11  rudahl
//   changed max infoviewports to 3
//
//   Revision 1.37  2002/09/04 21:45:56  goldin
//   Update file chooser to allow multiple file types
//
//   Revision 1.36  2002/09/04 19:15:11  goldin
//   Add bShow arg to InfoViewport
//
//   Revision 1.35  2002/09/03 19:46:49  goldin
//   Work on prompt and reply problems
//
//   Revision 1.34  2002/08/22 14:57:02  goldin
//   Work on appearance and behavior of VP Filechooser
//
//   Revision 1.33  2002/05/16 13:16:39  goldin
//   work on unmoveable file chooser for VP
//
//   Revision 1.32  2002/05/16 00:30:05  goldin
//   Add ViewFileChooser
//
//   Revision 1.31  2002/04/03 17:59:17  goldin
//   Allow multiple infovps per operation
//
//   Revision 1.30  2002/02/20 16:27:47  rudahl
//   moved FixupNC.. for some to cpp
//
//   Revision 1.29  2002/02/13 01:20:14  rudahl
//   added getAbscolor to P&R
//
//   Revision 1.28  2002/02/04 20:40:13  rudahl
//   added conditional tracing provision, for speed
//
//   Revision 1.27  2002/01/15 19:29:31  rudahl
//   fixes to infoviewport
//
//   Revision 1.26  2002/01/10 22:32:02  rudahl
//   improving infoviewport
//
//   Revision 1.25  2001/12/20 18:47:18  rudahl
//   implemented colorchooser
//
//   Revision 1.24  2001/12/18 12:04:07  rudahl
//   got rid of jni.log
//
//   Revision 1.23  2001/11/27 17:38:19  goldin
//   Add capability to set details
//
//   Revision 1.22  2001/11/16 16:37:47  goldin
//   Begin moving UI code to other packages as relevant
//
//   Revision 1.21  2001/11/16 12:23:43  goldin
//   try fixing loggeroutputstream
//
//   Revision 1.20  2001/11/15 20:46:41  rudahl
//   moved viewport java files to their own package
//
//   Revision 1.19  2001/11/09 19:02:59  rudahl
//   make -HIS & -PRO sep. keys
//
//   Revision 1.18  2001/11/08 21:59:54  rudahl
//    improvements in infoviewport
//
//   Revision 1.17  2001/11/07 18:48:51  rudahl
//   add support for changing button labels, for MEA
//
//   Revision 1.16  2001/11/05 20:28:49  rudahl
//   adapt to dragon.ui package *.java
//
//   Revision 1.15  2001/11/02 21:00:35  rudahl
//   further advances on U/HIS & U/SCA
//
//   Revision 1.14  2001/11/01 18:10:28  rudahl
//   added initial implementation of infoViewport
//
//   Revision 1.13  2001/10/19 08:41:55  rudahl
//   use FileChooser separate from UI
//
//   Revision 1.12  2001/10/12 20:30:26  rudahl
//   fixed numerous problems from dragsched.lst
//
//   Revision 1.11  2001/10/04 09:01:53  rudahl
//   improvements for infotext, etc
//
//   Revision 1.10  2001/09/28 13:20:20  rudahl
//   change to permit C++ to grab Java windows
//
//   Revision 1.9  2001/09/26 15:40:20  rudahl
//   continued refinement of P&R, esp. for C/TRA
//
//   Revision 1.8  2001/09/25 20:57:39  rudahl
//   further improvements to Jni Dialogs
//
//   Revision 1.7  2001/09/24 18:11:05  rudahl
//   added JniDialog as base class, and improved or added its subclasses
//
//   Revision 1.6  2001/09/19 14:44:58  rudahl
//   improved - but not yet final - dialogs
//
//   Revision 1.5  2001/09/14 14:06:15  rudahl
//   improved (but not final) Java P&R
//
//   Revision 1.4  2001/09/12 12:23:39  rudahl
//   added PromptAndReply to viewProg
//
//   Revision 1.3  2001/09/11 16:01:30  rudahl
//   improvements in buttonPanel implementation & use
//
//   Revision 1.2  2001/09/10 19:45:01  rudahl
//   further improvements to ButtonPanel
//
//
//***************************************************************
package com.grs.dragon.viewport;

import java.io.*;
import java.util.*;
import java.awt.*;
import javax.swing.*;
import com.grs.gui.*;
import com.grs.dragon.ui.*;

public class viewProg
    {
    private static String language = null;
    public static native void SendViewportEvent(int MsgNo);
    public static native void SendViewportEvent(String MsgName);
      /** Fix Non-client area of dialog which has just been displayed
       *  find the dialog window and a) change the title b) kill SystemMenu
       *  and c) set it to be TOPMOST
       *  @param CurrentTitle   string which is used to find the dialog
       *  @param NewTitle   string which will replace the title, or ""
       *  @param bMoveSizeOK  do not delete Move or Size menu items
       */
    public static native void FixupNCDialog(String CurrentTitle, 
					    String NewTitle,
					    boolean bMoveSizeOK);

      /* controls the dialog-topmost status specifically for the 
       * one and only PromptAndReply panel. Assumes viewjava.cpp
       * already knows the window handle
       * @param bRelease   true => release window from being topmost
       *                   false => restore window to being topmost
       */
    public static native void SetPandRNCDialogTopmost(boolean bRelease);

      // if 1, log to C++
      // if 2, do System.out.println
      // else do nothing
    private static int s_iLoggingMethod = 0;

      //~~ for testing, uncomment the method definition
      //~~ for production, uncomment the native declaration 
    public static native void logViewportP(String Msg);

    public static void logViewport(String str)
        {
	if ((s_iLoggingMethod > 0) || str.startsWith("Exception"))
	    {
	    if (s_iLoggingMethod == 1)
	        System.out.println(str);
	    else
	        logViewportP(str);
	    }
       }

    public static I18NTextSource i18nMessages = null;

    private static PrintStream log = null;

    private static LoggerOutputStream logStream = new LoggerOutputStream();
    private static PrintStream logWriter = new PrintStream(logStream);

    private static viewButtonPanel s_pButtonPanel = null;

    private static PromptAndReply s_pPandRQuestion = null;

    private static InfoText s_pInfoText = null;

      /* InfoViewport now permits several instances per czOp */
      /* We handle this by storing arrays on a per op basis 
	 rather than the InfoViewports directly.
	 */
    private static int MAXIV = 4;
    private static Hashtable s_hInfoViewport = new Hashtable();

    private static ColorChooser s_pColorChooser = null; 

    private static AboutDialog s_pAboutDialog = null;

    private static ViewFileChooser s_pFileChooser = null;

      //    private static ImageIcon s_ImageIcon = null;

    private static ViewportMenu vpMenus[] = new ViewportMenu[2];

    private static String fileMsgKeys[] = { "%h8500.6","%h8500.7",
					    "%h8500.8", "%h8500.10" } ;

    private static String zoomMsgKeys[] = {"%h8600.0","%h8600.1",
					  "%h8600.2","%h8600.3" } ;
	
      /** @param   args  The first element is the language selector e.g. "EN"
       *              or operation (e.g. "CLOSE").
       *           The second element is the tracing selector: 0, 1, or 2.
       *	   Additional args mean this is a a standalone test
       *		and may specify the test
       */
    public static void main(String[] args) 
        {
	logViewport("viewProg::main (en) argc="+args.length
	    +" argv[0]="+args[0]);
	System.setOut(log);
	System.setErr(log);

	try
	    {
	    if (args[0].equals("CLOSE"))
	        {
		  //	System.out.println("viewProg closing log");
		if (log != null)
		    log.close();
		log = null;
		return;
		}
	    else
	        {
		FileOutputStream logFile = new FileOutputStream("jni.log");
		log = new PrintStream(logFile,true);
		System.setOut(log);
		System.setErr(log);
		//long ulTot = Runtime.getRuntime().totalMemory();
		//System.out.println("viewProg opening log; total mem="+ulTot);
		}
	    }
	catch (IOException e) {}

	s_iLoggingMethod = Integer.parseInt(args[1]);
	logViewport("viewProg::main argc="+args.length
	    +" argv[0]="+args[0]+", "+args[1]+", "+args[2]);
	//logViewport("viewProg::main about to read I18N for "+args[0]);
        language = args[0];
         /* 3/18/07 - try using the main message file to avoid need
          * to constantly update the list for view.msgs
          * ~~ Need to change if message file name changes
          */
	i18nMessages = new I18NTextSource(args[0]+"/drag5-" +
                  args[0]+ ".messages");
	//i18nMessages = new I18NTextSource(args[0]+"/view.msg");
        /* Set up the fonts - this code grabbed from DragonUI */
        String OS = System.getProperty("os.name");
	boolean bIsWindows = false;
	if (OS.toUpperCase().indexOf("WIN") >= 0)
	    {
	    bIsWindows = true;
	    }
	FontProcessor fontProc = new FontProcessor(bIsWindows);
	ApplicationManager.setFontProcessor(fontProc);
        /**/
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
	  { // no harm done if fails
	    }
	s_pButtonPanel = new viewButtonPanel(i18nMessages,"XX??");
	fontProc.setupFonts(language,s_pButtonPanel);
	s_pPandRQuestion = new PromptAndReply(i18nMessages);
	fontProc.setupFonts(language,s_pPandRQuestion);

	//	s_pInfoText = new InfoText(i18nMessages);

	if (args.length > 3)  /* for testing only */
	    {
	      String[] set1 = { "label1"};
	      String[] set2 = { "default1","default2"};
	    s_pPandRQuestion.setupPrompts(set1,set2);
	    s_pPandRQuestion.setLocation();
	    s_pPandRQuestion.showIt();
	    String[] hlp = { "help, somebody help"};
	    s_pPandRQuestion.getResults(hlp);
	    s_pPandRQuestion.killPanel();
	    /*
	    try
	        {
	    for (int i=0; i<10; i++)
	      {
		s_pPandRQuestion.toFront(true);
		Thread.sleep(10);
		s_pPandRQuestion.toFront(false);
		Thread.sleep(10);
	      }
		}
	    catch (Exception e)
	        {
		System.out.println("Sleep exception "+e.getMessage());
		}
		*/
	    s_pPandRQuestion.toFront(true);
	    s_pButtonPanel.setupControls("VEC",null,
					 new Rectangle(300,400,500,600));
	    s_pButtonPanel.showIt();
	    try
	        {
		Thread.sleep(10);
		}
	    catch (Exception e)
	        {
		System.out.println("Sleep exception "+e.getMessage());
		}
	    s_pButtonPanel.killPanel();
	    s_pButtonPanel.setupControls("COO",null,
					 new Rectangle(300,400,500,600));
	    s_pButtonPanel.showIt();
	    String[] params = { "classXX" } ;
	    try
	        {
		s_pPandRQuestion.setupPromptAndReply("ColorRange",
						     "55.3\nfred",params);
		s_pPandRQuestion.getPromptAndReply("ColorRange", params);
		  //		String reply = PromptAndReply(args[2],"",null);
		  //System.out.println("test of "+args[2]+" returns "+reply);
		}
	    catch (Exception e)
	        {
		System.out.println("Exception on "+args[2]+" "+e.getMessage());
		}
	    System.exit(0);
	    } /* end of testing section */
	}

    static viewButtonPanel buttonPanel = null;

      /** create new or modify existing ButtonPanel
       *  @param jsOp      the relevent Dragon operation e.g. CUR
       *  @param x0        upper-left corner of parent window
       *  @param y0        upper-left corner of parent window
       *  @param width     width of parent window, or 0
       *  @param height    height of parent window, or 0
       *  @return          0 or error status
       */
    public static int ButtonPanel(String jsOp,
				  int x0, int y0, int width, int height) 
       throws Exception
        {
	logViewport("viewProg::ButtonPanel (en) about to viewButtonPanel");
	int iRetval = 0;
	try
	    {
	    Rectangle jParentRect = new Rectangle(x0,y0,width,height);
	    if (s_pButtonPanel != null) 
	        {
		s_pButtonPanel.reinit();
		s_pButtonPanel.setupControls(jsOp,null,
					     jParentRect);
	        s_pButtonPanel.showIt();
		//	buttonPanel = new viewButtonPanel(jsOp,i18nMessages,
		//			  jParentRect);
		}
	    else 
	        iRetval = -1;
	    }
	catch (RuntimeException e)
	    {
	    logViewport("viewButtonPanel runtime exception "+
			e.getMessage());
	    e.printStackTrace(logWriter);
	    throw new Exception(e.getMessage());
	    }
	logViewport("viewProg::main finished viewButtonPanel");
	return iRetval;
        }

      /** construct a panel containing the buttons and labels 
       *  appropriate to one specific Dragon operation, plus a table
       *  with specified headings.
       *  All 10 buttons are created, but only the needed ones are 
       *  displayed.
       *  @param   jsOp         "CUR" is the only one at present?
       *  @param   czHeadings   actual or keyed column headings.
       *                        (If key search fails, use as actual)
       *                        The number and sequence of headings defines
       *                        the table layout
       *  @param x0             upper-left corner of parent window
       *  @param y0             upper-left corner of parent window
       *  @param width          width of parent window, or 0
       *  @param height         height of parent window, or 0
       */
    public static int ButtonPanel(String jsOp,String[] czHeadings,
				  int x0, int y0, int width, int height) 
       throws Exception
        {
	logViewport("viewProg::ButtonPanel (en) about to viewButtonPanel");
	int iRetval = 0;
	try
	    {
	    Rectangle jParentRect = new Rectangle(x0,y0,width,height);
	    if (s_pButtonPanel != null) 
	        {
		s_pButtonPanel.reinit();
		s_pButtonPanel.setupControls(jsOp,
					     czHeadings, jParentRect);
	        s_pButtonPanel.showIt();
		//	    if (buttonPanel == null)
		// {
		//buttonPanel = new viewButtonPanel(jsOp,czHeadings,
		//				  i18nMessages,
		//				  jParentRect);
		}
	    else 
	        iRetval = -1;
	    }
	catch (RuntimeException e)
	    {
	    logViewport("viewButtonPanel2 runtime exception "+
			e.getMessage());
	    e.printStackTrace(logWriter);
	    throw new Exception(e.getMessage());
	    }
	logViewport("viewProg::main finished viewButtonPanel");
	return iRetval;
	}

      /** enable/disable one of the visible buttons of current button panel
       *  @param  iButtonIndex   button number 0 to 9, matching F1 .. F10
       *  @param  bEnable        true => enable false => disable
       *  @param  pczLabel       text or key to display.
       */
    public static void setButtonEnabled(int iButtonIndex, boolean bEnable,
					String pczLabel)
        {
	  //if ((buttonPanel != null) 
	if ((s_pButtonPanel != null) 
	      && (iButtonIndex >= 0) && (iButtonIndex < 10)) 
  	    s_pButtonPanel.setButtonEnabled(iButtonIndex,bEnable,pczLabel);
	//~~	else
	//~~  throw new Exception();
        }

      /** add a line of text to an already-existing table
       *  @param  czText   line of text already formatted as HTML
       */
    public static void addButtonPanelTableLine(String czText,
					       int replaceFlag)
        {
	  //	if (buttonPanel != null) 
	if (s_pButtonPanel != null) 
  	    s_pButtonPanel.addTableLine(czText,replaceFlag);
	//~~	else
	//~~  throw new Exception();
	}

      /** kill current buttonPanel
       */
    public static void killButtonPanel()
        {
	logViewport("viewProg::KillButtonPanel");
	//if (buttonPanel != null) 
	if (s_pButtonPanel != null) 
	    {
	    s_pButtonPanel.killPanel();
	    }
	  //buttonPanel.setButtonEnabled(iButtonIndex,bEnable);
	//~~	else
	//~~  throw new Exception();
        }

      static String s_czCurrentPandROperation = "";
      static String[] s_czCurrentPandRParams = null;

      /** construct a modal panel matching whatever czOperation calls for.
       *  Essentially, there is one value of czOperation for each specific
       *  modal box.
       *  @param   czOperation  one of 'ZoomFactor', 'ColorRange'
       *                          'GCPName', 'GCPCoords', 
       *                          'TRAClassName', 'TRAClassNumber',
       *                          'ColorSelector',
       *  @param   czDefault    String which may (depending on czOperation)
       *                        be used as a default
       *                        If multiple defaults are needed, they are
       *                        concatinated with a '\n' delimiter
       *  @param   czParams     set of parameters whose need depends on
       *                        czOperation
       *                        If multiple replies are needed, they are
       *                        concatinated with a '\n' delimiter
       */
    public static void PromptAndReply(String czOperation,String czDefault,
				      String[] czParams) 

       throws Exception
        {
	System.setOut(log);
	System.setErr(log);
	s_czCurrentPandROperation = czOperation;
	s_czCurrentPandRParams = czParams;

	try
	    {
	    s_pPandRQuestion.reinit();
	    s_pPandRQuestion.setupPromptAndReply(czOperation, 
						 czDefault,czParams);
	    //czRetval = s_pPandRQuestion.getPromptAndReply(czOperation,
	    //					  czParams);
	    }
	catch (RuntimeException e)
	    {
	    logViewport("PromptAndReply runtime exception "+
			e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("PromptAndReply exception "+
			e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::PromptAndReply (ex)");
	    }
	}

      /** retrieve result from current modal panel.
       *  @return  String containing possibly multiple results, '\n'-delim
       */
    public static String getPromptAndReply()
       throws Exception
        {
	String czRetval = null;
	System.setOut(log);
	System.setErr(log);

	try
	    {
	    czRetval 
	      = s_pPandRQuestion.getPromptAndReply(s_czCurrentPandROperation,
						   s_czCurrentPandRParams);
	    }
	catch (RuntimeException e)
	    {
	    logViewport("PromptAndReply runtime exception "+
			e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("PromptAndReply exception "+
			e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    s_czCurrentPandROperation = "";
	    s_czCurrentPandRParams = null;
	    logViewport("viewProg::getPromptAndReply finished returning '"
			+czRetval+"'");
	    }
	return czRetval;
	}

      /**
       * Set the current color file for vector drawing.
       */
    public static void setDrawingColorFile(String clfName)
        {
	s_pPandRQuestion.setDrawingColorFile(clfName);
        }

      /**
       * Return the red/green/blue components of the currently
       * selected color index, packed into a 32 bit integer.
       */
    public static int getCurrentColorComponents()
        {
	return s_pPandRQuestion.getCurrentColorComponents();
        }

      /**
       * Return the red/green/blue components of the specified
       * color index, packed into a 32 bit integer.
       */
    public static int getColorComponents(int iColorindex)
        {
	return s_pPandRQuestion.getColorComponents(iColorindex);
        }

      /** construct a modal panel containing HTML text
       *  This version is to be invoked from JNI
       *  @param   Info       Strings containing info or key to info
       *                      to display.
       *                      For each item, if first char is not '<',
       *                      then that item is formatted as a <p></p>  
       */
    public static void InfoText(String[] Info)
              throws Exception
        {
	System.setOut(log);
	System.setErr(log);

	try
	    {
	    if (s_pInfoText == null)
	        s_pInfoText = new InfoText(i18nMessages);
	    if (s_pInfoText != null)
	        {
		s_pInfoText.reinit();
		s_pInfoText.setupContents("IT??",Info);
		s_pInfoText.showIt();
		//if (s_ImageIcon == null)
		//  s_ImageIcon = new ImageIcon("dragexec.gif");
		//s_pInfoText.setIcon(s_ImageIcon);
		// force it to be topmost and immovable
		//FixupNCDialog("IT??","",false);
		}
	    }
	catch (RuntimeException e)
	    {
	    logViewport("InfoText runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("InfoText exception "+e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::InfoText (ex)");
	    }
	}

      /** wait for current modal panel
       *  This version is to be invoked from JNI
       */
    public static void waitInfoText()
              throws Exception
        {
	System.setOut(log);
	System.setErr(log);

	try
	    {
	    if (s_pInfoText != null)
	        {
		s_pInfoText.waitAndKill();
		s_pInfoText = null;
		}
	    }
	catch (RuntimeException e)
	    {
	    logViewport("InfoText runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("InfoText exception "+e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::waitInfoText (ex)");
	    }
	}

      /** construct a non-modal panel containing a drawn graphical display
       *  using parameter data read from a file. There can be MAXIV panels
       *  existing at any one time per jsOp value.
       *  @param jsOp     String identifying the operation whose 
       *		  results are being displayed
       *  @param jsFile   complete path to file containing parameters.
       *  @param x0        upper-left corner of parent window
       *  @param y0        upper-left corner of parent window
       *  @param width     width of parent window, or 0
       *  @param height    height of parent window, or 0
       */
    public static void InfoViewport(String jsOp, String jsFile,
				    int x0, int y0, int width, int height)
              throws Exception
        {
	System.setOut(log);
	System.setErr(log);
	InfoViewport[] ivArray = null;
	InfoViewport iv =  null;
	Rectangle jParentRect = new Rectangle(x0,y0,width,height);
	try
	    {
	    if (s_hInfoViewport == null)
	        s_hInfoViewport = new Hashtable();
	    String hashKey = jsOp;
	    if (s_hInfoViewport.containsKey(hashKey))
	        {
		ivArray = (InfoViewport[])s_hInfoViewport.get(hashKey);
		}
	    else
	        {
		int ht = (jsOp.equals("C/EDI/HIS")) ? 512 : 400;
                ivArray = new InfoViewport[MAXIV];
		for (int i=0; i < MAXIV; i++)
		    {
	            ivArray[i] =  
                       new InfoViewport(i18nMessages,new Dimension(512,ht),i);
		    }
		}
	    iv = getUnusedIV(ivArray);
	    if (iv != null)
	        {
		iv.reinit();
		s_hInfoViewport.put(hashKey,ivArray);
		iv.setupContents(jsOp,"IV??",jsFile,jParentRect);
		iv.setLastDisplayedTime(new Date());
		iv.showIt();
		//	FixupNCDialog("IV??",jsOp,true);
		}
	    }
	catch (RuntimeException e)
	    {
	    logViewport("InfoViewport runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("InfoViewport exception "+e.getMessage());
	    if (iv != null)
	        iv.setVisible(false);
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::InfoViewport (ex)");
	    }
	}

      /**
       * Factorization. Returns the first non-visible infoviewport
       * in the ivArray. If all are visible, returns the used furthest
       * in the past.
       */
    protected static InfoViewport getUnusedIV(InfoViewport[] ivArray)
        {
	InfoViewport foundIv = null;
	InfoViewport earliest = null;
	int i = 0;
	for (i = 0; (i < MAXIV) && (foundIv == null); i++)
	    {
	    if (!ivArray[i].isVisible())
	        foundIv = ivArray[i];
	    }
	if (foundIv == null)
	    {
	    for (i = 0; i < MAXIV; i++)
                {
                if (earliest == null)
                    earliest = ivArray[i];
                else if (ivArray[i].getLastDisplayedTime().before(
                               earliest.getLastDisplayedTime()))
                    earliest = ivArray[i];
		}
	    foundIv = earliest;
	    }
//	    foundIv = ivArray[0];
	return foundIv;
	}

      /** kill all infoviewports
       */
    public static void killInfoViewports()
        {
	logViewport("viewProg::KillInfoViewports (en)");
	if (s_hInfoViewport != null)
	    {
	    Enumeration e = s_hInfoViewport.keys();
	    while (e.hasMoreElements())
	        {
		String key = (String) e.nextElement();
		InfoViewport[] ivArray = 
		   (InfoViewport[])s_hInfoViewport.get(key);
		logViewport("viewProg::KillInfoViewports" + 
			    " processing IVs for " + key);
		for (int i = 0; i < MAXIV; i++)
		    {
		    logViewport("viewProg::KillInfoViewports #"+i);
		    if (ivArray == null)
			break;
		    InfoViewport p = ivArray[i];
		    if ((p != null) && (p.isVisible()))
		        {
		        logViewport("viewProg::KillInfoViewports" + 
				    " - found one visible, killing");
		        p.killDialog();
			}
		    }
		}
	    }
        }

      /** Display info about Dragon. 
       *  This is actually the UI class, reused.
       */
    public static void AboutDialog()
              throws Exception
        {
	System.setOut(log);
	System.setErr(log);

	try
	    {
	    Toolkit tk = Toolkit.getDefaultToolkit();
	    Dimension screenDim = tk.getScreenSize();
	    int iXCenter = screenDim.width / 2;
	    int iYCenter = screenDim.height / 2;
	    JFrame fred = new JFrame();
	    ApplicationManager.setTextSource(i18nMessages);
	    fred.setBounds(new Rectangle(iXCenter-20,iYCenter-20,40,40));
	    s_pAboutDialog = new AboutDialog();
	    s_pAboutDialog.showAboutDialog(fred,"TITLE??");
	    tk.sync();
	    //if (s_ImageIcon == null)
	    //  s_ImageIcon = new ImageIcon("dragexec.gif");
	    //s_pAboutDialog.setIcon(s_ImageIcon);
		// force it to be topmost and immovable
	    //FixupNCDialog("TITLE??",s_pAboutDialog.getTitle(),false);
	    }
	catch (RuntimeException e)
	    {
	    logViewport("AboutDialog runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("AboutDialog exception "+e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::AboutDialog (ex)");
	    }
	}

      /** wait for current modal panel
       *  This version is to be invoked from JNI
       */
    public static void waitAboutDialog()
              throws Exception
        {
	System.setOut(log);
	System.setErr(log);

	try
	    {
	    s_pAboutDialog.waitAndKillDialog();
	    s_pAboutDialog = null;
	    }
	catch (RuntimeException e)
	    {
	    logViewport("AboutDialog runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("AboutDialog exception "+e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::waitAboutDialog (ex)");
	    }
	}

      /** Display choose colors and create a color file
       */
    public static void ColorChooser(String czDpath,
				    String czRefColorfile,
				    String czOutColorfile,
				    String czRefImagefile)
              throws Exception
        {
	  //	System.setOut(log);
	  //System.setErr(log);

	logViewport("viewProg::ColorChooser (en)");
	try
	    {
	    Toolkit tk = Toolkit.getDefaultToolkit();
	    Dimension screenDim = tk.getScreenSize();
	    int iXCenter = screenDim.width / 2;
	    int iYCenter = screenDim.height / 2;
	    //	    JFrame fred = new JFrame();
	    //fred.setBounds(new Rectangle(iXCenter-20,iYCenter-20,40,40));
	    ApplicationManager.setTextSource(i18nMessages);
	    ApplicationManager.setReadPath(czDpath);
	    //	    ApplicationManager.setWritePath(czWpath);
	    //ApplicationManager.setModulePrefix(czModuleAbbr);
	    //ApplicationManager.setErrorLogger(new Logger("test.err"));
	    s_pColorChooser = 
	        new ColorChooser(ApplicationManager.getTextSource());
	    Dimension d = s_pColorChooser.getPreferredSize();
	    s_pColorChooser.setBounds(new Rectangle(iXCenter-d.width/2,
						    iYCenter-d.height/2,0,0));
            s_pColorChooser.chooseColors(czRefColorfile,
					 czOutColorfile,
					 czRefImagefile);
	    FixupNCDialog("COLTITLE??","",false);
            while (s_pColorChooser.isVisible())
	        {
		try 
		    {
		    Thread.sleep(500);
		    }
		catch (InterruptedException ie)
		    {
		    }
		}
	    }
	catch (RuntimeException e)
	    {
	    logViewport("ColorChooser runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("Colorchooser exception "+e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    logViewport("viewProg::ColorChooser (ex)");
	    }
	}

      /** Kill the color chooser (if any)
       */
    public static void killColorChooser()
        {
	if (s_pColorChooser != null)
	    s_pColorChooser.dismissChooser();
	s_pColorChooser = null;
	}

      /** Get a file name (only for F/SaveAs at present)
       * and capture
       *  This is actually the UI class, reused.
       */
    public static String FileChooser(String czModuleAbbr,String czWpath)
              throws Exception
        {
	System.setOut(log);
	System.setErr(log);
	File fResult = null;

	try
	    {
	    Toolkit tk = Toolkit.getDefaultToolkit();
	    Dimension screenDim = tk.getScreenSize();
	    int iXCenter = screenDim.width / 2;
	    int iYCenter = screenDim.height / 2;
	    JFrame fred = new JFrame();
	    ApplicationManager.setTextSource(i18nMessages);
	    ApplicationManager.setErrorLogger(new Logger("VPJAVA.ERR"));
	    GenErrorDisplay ged = new GenErrorDisplay(i18nMessages,fred);
	    ApplicationManager.setErrorDisplay(ged);
	    ApplicationManager.setReadPath(czWpath);
	    ApplicationManager.setWritePath(czWpath);
	    ApplicationManager.setModulePrefix(czModuleAbbr);
	    ApplicationManager.setLogFileName("VPJAVA.ERR");
	    fred.setBounds(new Rectangle(iXCenter-20,iYCenter-20,40,40));
            if (s_pFileChooser == null)
	       {
	       s_pFileChooser = new ViewFileChooser(fred,i18nMessages,
						   false,false);
	       ApplicationManager.getFontProcessor().setupFonts(language, 
							    s_pFileChooser);
	       }
            DFileType[] captureTypes = new DFileType[1];
	    captureTypes[0] = DFileType.TIFF;
	    fResult = s_pFileChooser.chooseFile(captureTypes,
						null,null,"FILECHOOSE??",null);
            while (s_pFileChooser.isVisible())
	        {
		try 
		    {
		    Thread.sleep(500);
		    }
		catch (InterruptedException ie)
		    {
		    }
		}
	    if (s_pFileChooser.wasOkPressed())
	        {
		fResult = s_pFileChooser.getLastChosenFile();
		}
	    else
	        {
		fResult = null;
		}
	    }
	catch (RuntimeException e)
	    {
	    logViewport("FileChooser runtime exception "+e.toString());
	    e.printStackTrace(logWriter);
	    logStream.flush();
		System.out.println("viewProg runtime exception");
	    e.printStackTrace();
	    e.fillInStackTrace();
	    e.printStackTrace();
	    throw new Exception(e.getMessage());
	    }
	catch (Exception e)
	    {
	    logViewport("FileChooser exception "+e.getMessage());
	    e.printStackTrace(logWriter);
	    logStream.flush();
	    throw new Exception(e.getMessage());
	    }
	finally
	    {
	    s_pFileChooser = null;
	    logViewport("viewProg::FileChooser (ex)");
	    }
	return (fResult != null) ? fResult.getAbsolutePath() : "";
	}

	/*********** Functions related to ViewportMenus *********/

	/**
	 * Display one of the vp menus at the designated screen
	 * coordinates. If the menu does not yet exist, create it.
	 * @param menuCode    0 if File menu, 1 if Zoom.
	 * @param x           Desired screen coordinate pixel for menu
	 *                     (upper left corner)
	 * @param y           Desired screen coordinate line
	 * @param enableMask  Bitmap for enabling/disabling menu items
	 * @return  0 if all is well, otherwise negative error code.
	 */
	public static int showVPMenu(int menuCode, int x, int y,
				     int enableMask)
	   {
	   int status = 0;
	   if ((menuCode < 0) || (menuCode > 1))
	       status = -1;
	   else
	       {
	       if (vpMenus[menuCode] == null)
	          {
		  if (menuCode == 0)
		     {
		     vpMenus[menuCode] = new ViewportMenu(i18nMessages,
							   fileMsgKeys,
							   null);
		     }
		  else
		     {
		     vpMenus[menuCode] = new ViewportMenu(i18nMessages,
							  zoomMsgKeys,
							  null);
		     }
	          }
	       vpMenus[menuCode].setItemsEnabled(enableMask);
	       vpMenus[menuCode].setLocation(x,y);
	       vpMenus[menuCode].setMenuVisible(true);
	       }
	   return status;
	   }

	/**
	 * Make any visible VP menus disappear 
	 */
	public static void killVPMenu()
	   {
	   for (int i = 0; i < vpMenus.length; i++)
	      {
	      if (vpMenus[i] != null)
	         {
		 vpMenus[i].setMenuVisible(false);
	         }
	      }
	   }

	/**
	 * Return the integer indicating the latest choice
	 * from the latest displayed menu
	 */
	public static int getVPMenuChoice()
	   {
	   return ViewportMenu.getLatestSelection();
	   }

    }
