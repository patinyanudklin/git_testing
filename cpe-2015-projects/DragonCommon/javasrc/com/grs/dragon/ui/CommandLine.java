/**
 *  CommandLine
 * 
 *  Copyright  2002-2007  by Sally Goldin & Kurt Rudahl 
 *
 *  Created by Sally Goldin, 4/25/2001
 *
 *  $Id: CommandLine.java,v 1.30 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: CommandLine.java,v $
 *  Revision 1.30  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.29  2006/06/06 05:21:28  goldin
 *  Make status area bigger and internationalize the CMD prompt
 *
 *  Revision 1.28  2005/12/05 09:39:08  goldin
 *  Working on UI hang problem - make CommandForwarder into its own thread
 *
 *  Revision 1.27  2005/03/29 13:05:00  goldin
 *  Only uppercase things that look like Dragon commands or Pspecs
 *
 *  Revision 1.26  2005/02/06 09:00:25  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.25  2002/06/28 14:10:47  goldin
 *  Provide infrastructure for usermanual help implementation
 *
 *  Revision 1.24  2002/04/19 22:30:20  goldin
 *  Work on history positioning bug
 *
 *  Revision 1.23  2002/01/24 17:06:50  goldin
 *  Change ECHO special command to ECHO-ON & ECHO-OFF
 *
 *  Revision 1.22  2002/01/02 13:14:08  goldin
 *  Fix embedded newlines in history
 *
 *  Revision 1.21  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.20  2001/11/05 13:59:14  goldin
 *  Put UI code in a package
 *
 *  Revision 1.19  2001/10/17 10:29:36  goldin
 *  Modify to use ApplicationManager to get error display, etc.
 *
 *  Revision 1.18  2001/10/08 11:55:06  goldin
 *  Don't show comments in history recall
 *
 *  Revision 1.17  2001/09/11 11:47:03  goldin
 *  implement cancel menu item
 *
 *  Revision 1.16  2001/09/10 14:38:17  goldin
 *  Separate special command processing into pre and post processing, move pre to CommandForwarder
 *
 *  Revision 1.15  2001/09/05 10:44:57  goldin
 *  Add history recall to cmd line
 *
 *  Revision 1.14  2001/09/04 15:08:50  goldin
 *  Begin implementing script control panel
 *
 *  Revision 1.13  2001/08/31 14:01:02  goldin
 *  Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 *  Revision 1.12  2001/06/18 12:09:59  goldin
 *  Fixing bugs found by Kurt
 *
 *  Revision 1.11  2001/05/22 12:05:13  goldin
 *  Implement new SigFileValidator; make msgs show up in the history
 *
 *  Revision 1.10  2001/05/09 09:04:56  goldin
 *  Notify SS when UI appears
 *
 *  Revision 1.9  2001/05/08 10:14:56  goldin
 *  Refine logging support
 *
 *  Revision 1.8  2001/05/07 14:54:40  goldin
 *  Initial implementation of logger
 *
 *  Revision 1.7  2001/05/07 14:21:15  goldin
 *  Modify focus lost to always call validator
 *
 *  Revision 1.6  2001/05/04 15:36:36  goldin
 *  Modify control of Ready state
 *
 *  Revision 1.5  2001/05/03 15:04:31  goldin
 *  Add special file handling to command line and command forwarder
 *
 *  Revision 1.4  2001/04/27 11:29:00  goldin
 *  Continue implementation of interprocess communication and command handling
 *
 *  Revision 1.3  2001/04/26 15:45:32  goldin
 *  Work on history display for command line and response panels
 *
 *  Revision 1.2  2001/04/26 12:24:23  goldin
 *  further work on command line functionality
 *
 *  Revision 1.1  2001/04/25 15:37:01  goldin
 *  began implementation of command line
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;

/**
 * This class implements both the model and the view for the
 * Dragon command line. The view is a simple text field that
 * accepts user input. The model includes a representation
 * of the command history, plus the logic to recognize
 * when a command has been completed and should be sent to the
 * CommandForwarder process.
 * <p>
 * This class is used as a singleton.
 */
public class CommandLine extends DTextField 
                         implements ActionListener
    {
    protected Hashtable specialCommandTable = null;
      /**
       * Reference to command forwarder, set in constructor.
       */
    protected CommandForwarder forwarder = null;

      /**
       * Reference to main application, set in constructor.
       */
    protected DragonUI mainApp = null;

      /**
       * Reference to logger object.
       */
    protected Logger cmdLogger = null;

      /**
       * Linked list used for maintaining history.
       */
    protected LinkedList historyList = null;

      /**
       * Current, that is, last displayed, line of history.
       */
    protected int currentLine = -1;

      /**
       * Size of history.
       */
    public static final int HISTORY_LENGTH = 100;

    public static final String CMDPROMPT = "CMD>>";
    public static final String EXEC = "-.";
    


      /**
       * Buffer for holding command under construction.
       */
    public StringBuffer currentCmdBuffer = new StringBuffer(256);

      /**
       * Constructor. Pass references to the forwarder and
       * the main Dragon UI. 
       */
    public CommandLine(CommandForwarder forwarder,
		       DragonUI mainApp)
        {
        super("CommandLine",CMDPROMPT,50, true);
        I18NTextSource txtSource = ApplicationManager.getTextSource();
	if (txtSource != null)
	   { 
           String promptI18N = txtSource.getI18NText("%h9320.0",CMDPROMPT);
           if (promptI18N != null)
               setLabelText(promptI18N);
           }
	setMaxInputChars(64);
        this.forwarder = forwarder;
	this.mainApp = mainApp;
	historyList = new LinkedList();
	inputField.addActionListener(this);
        cmdLogger = new Logger();
        Border outside = BorderFactory.createEtchedBorder();
        Border inside = BorderFactory.createMatteBorder(5,10,5,10,
						       getBackground());
        setBorder(BorderFactory.createCompoundBorder(outside,inside));
        initSpecialCommandTable();
	}

      /**
       * Method from ActionListener interface, called when the
       * user hits return in the command line. Stores the line
       * in the history. Displays it in the history area if that
       * is selected. Checks to see if the command is an
       * immediate command and if so executes it. Checks to see
       * if the line includes the execute flag and if so, executes
       * the command as a whole. Otherwise, adds the new line
       * to the command currently being constructed.
       */
    public void actionPerformed(ActionEvent ae)
        {
        String textEntered = massageText(inputField.getText());
        if (textEntered.length() == 0)
	    return;
	addToHistory(textEntered);
	mainApp.refreshHistoryDisplay();
        if (currentCmdBuffer.length()== 0)
	    {
            currentCmdBuffer.append(CMDPROMPT+ " ");
            } 
        else
	    {
            currentCmdBuffer.append("\n");
            } 
	currentCmdBuffer.append("  " + textEntered);
        clearField();
        if (!(processSpecialCommand(textEntered)) &&
             (textEntered.endsWith(EXEC)))
	    {
	    cmdLogger.logMessage(
             currentCmdBuffer.toString().substring(CMDPROMPT.length()),false);
	    executeCommand();
	    }
	}

    public void executeCommand()
        {
        boolean bOk = forwarder.sendCommandToServer(
                 currentCmdBuffer.toString());
	currentCmdBuffer.delete(0,currentCmdBuffer.length());
        }


      /**
       * Check if text represents a special command. If so, handle it.
       * @param cmdText Command line text just entered.
       * @return true if the text was a special command, else false.
       */
    protected boolean processSpecialCommand(String cmdText)
        {
	// strip -. if any
	int execPos = cmdText.indexOf(EXEC);
	if (execPos >= 0)
	    cmdText = cmdText.substring(0,execPos);
	int pos = cmdText.indexOf(" ");
        if (pos < 0)
	    pos = cmdText.indexOf("\n");
	String verb;
	if (pos < 0)
	    verb = cmdText;
	else
	    verb = cmdText.substring(0,pos);
	SpecialCommand cmd = getSpecialCommand(verb);
	if (cmd == null)
	    return false;
	if (cmd.getArgCount() > 0)
	    {
	    if (pos < 0)
	         {
                 mainApp.getErrorDisplay().showError(TextKeys.ERROR,
			     "%e420", null);
		 return true;
		 }
	    else
	         {
                 int pos2 = cmdText.indexOf("\n");
		 if (pos2 < 0)
		      cmd.setArgText(cmdText.substring(pos+1));
		 else
		      cmd.setArgText(cmdText.substring(pos+1, pos2));
		 }
	    }
	if (cmd.isLocalOnly())
	    {
            cmd.doPreprocessing();
	    }
	else 
	    {
	    currentCmdBuffer.delete(0,currentCmdBuffer.length());
	    currentCmdBuffer.append(CMDPROMPT+ " ");
	    currentCmdBuffer.append(cmdText);
	    executeCommand();
	    }
        if ((verb.equalsIgnoreCase("RUN")) ||
            (verb.equalsIgnoreCase("CANCEL")))
	    cmdLogger.logMessage(cmdText,true);
        else if (!verb.equalsIgnoreCase("LOG"))
	    cmdLogger.logMessage(cmdText,false);
	return true;
        }


      /**
       * Return current contents of history as an HTML document.
       */
    public String getHistory()
        {
        if (historyList.size() == 0)
	    return null;
	Object[] contents = historyList.toArray();
        int len = contents.length;
	StringBuffer historyLines = new StringBuffer(HISTORY_LENGTH * 80);
        historyLines.append("<html><head></head><body>");
	for (int i = 0; i < len; i++)
	     {
	     if (i > 0)
	         historyLines.append("<br>");
             historyLines.append((String) contents[i]);
	     }
        historyLines.append("</body></html>");
	return historyLines.toString();
	}

      /**
       * Return the "next" line in the history and update
       * currentLine to be that line. If we are at the end,
       * simply continue to return the last line.
       * This is used by the "recall" function, so we skip
       * any lines that begin with a parenthesis
       */
    public String nextHistoryLine()
        {
        String histLine = null;
        String oldLine = null;
        int newLine = currentLine;
        if (historyList.size() == 0)
	    return null;
	Object[] contents = historyList.toArray();
        oldLine = (String) contents[currentLine];
        int len = contents.length;
        newLine = Math.min(newLine + 1, len-1);
        histLine = (String) contents[newLine];
        while ((histLine.startsWith("(")) &&
               (newLine < len -1))
	    {
	    newLine = Math.min(newLine + 1, len-1);
            histLine = (String) contents[newLine];
            }
        if ((newLine == len - 1) && (histLine.startsWith("(")))
	    return oldLine;  // no more without comments
	else
	    {
            currentLine = newLine;
            return histLine;
	    }
        }

      /**
       * Return the "previous" line in the history and update
       * currentLine to be that line. If we are at the beginning
       * simply continue to return the first line.
       */
    public String previousHistoryLine()
        {
        String histLine = null;
        String oldLine = null;
        int newLine = currentLine;
        if (historyList.size() == 0)
	    return null;
	Object[] contents = historyList.toArray();
        oldLine = (String) contents[currentLine];
        newLine = Math.max(newLine - 1,0);
	histLine = (String) contents[newLine];
        while ((histLine.startsWith("(")) &&
               (newLine > 0))
	    {
	    newLine = Math.max(newLine - 1, 0);
            histLine = (String) contents[newLine];
            }
        if ((newLine == 0) && (histLine.startsWith("(")))
            return oldLine;
	else
	    {
            currentLine = newLine;
            return histLine;
	    }
        }

      /**
       * Allow other classes to add text to the history
       * so that both command line and response panel
       * commands will show up there.
       */
    public void addToHistory(String newHistoryLine)
        {
	int pos = newHistoryLine.indexOf("\n");
	if (pos >= 0)
	    newHistoryLine = newHistoryLine.substring(0,pos);
        if (historyList.size() == HISTORY_LENGTH)
	    { 
	    historyList.removeFirst();
            }
	currentLine = historyList.size();
	historyList.add(newHistoryLine);
	}

      /**
       * Allow other classes to add text to the history
       * as a "comment" 
       */
    public void addToHistory(String newHistoryLine, boolean bComment)
        {
	int pos = newHistoryLine.indexOf("\n");
	if (pos >= 0)
	    newHistoryLine = newHistoryLine.substring(0,pos);
        if (historyList.size() == HISTORY_LENGTH)
	    historyList.removeFirst();
        StringBuffer msg = new StringBuffer();
        if (bComment)
             msg.append("( ");
	msg.append(newHistoryLine);
	if (bComment)
	     msg.append(" )");
	addToHistory(msg.toString());
	}

    public Dimension getPreferredSize()
        {
        return new Dimension(calculateWidth()+ 25, calculateHeight()+15);
        }

      /**
       * Scan a line of text and upper case any plain ascii parts
       * of it. Do not uppercase anything that is in quotes. If
       * the string is all whitespace, change it to empty. Return
       * the modified string. 
       */
    protected String massageText(String inString)
        {
	StringBuffer outBuffer = new StringBuffer();
        boolean bFirst = true;
        boolean bInQuotedString = false;
	StringTokenizer tokenizer = new StringTokenizer(inString," ");
	while (tokenizer.hasMoreTokens())
	     {
             boolean startQuote = false;
	     boolean endQuote = false;
             if (bFirst)
	         {
		 bFirst = false;
		 }
	     else
	         {
                 outBuffer.append(" ");
		 }
	     String token = tokenizer.nextToken().trim();
	     if ((token.startsWith("\"")) || (token.startsWith("'")))
	         startQuote = true;
             if ((token.endsWith("\"")) || (token.endsWith("'")))
                 endQuote = true;
	     if ((startQuote) && (endQuote))
	         { 
	         outBuffer.append(token);
                 }
             else if (startQuote)
	         {
                 bInQuotedString = true;
                 outBuffer.append(token);
                 } 
             else if (bInQuotedString)
	         {
		 outBuffer.append(token);
		 if (endQuote)
                     bInQuotedString = false;
		 }
	     /* upper case p-specs and commands */
	     else if ((token.startsWith("-")) || (token.length() < 4))
	         {
		 outBuffer.append(token.toUpperCase());
	         }  
             else 
	         {
		   /** Don't upcase anything else? 
		 char[] characters = token.toCharArray();
		 int len = characters.length;
		 boolean bAllAscii = true;
		 for (int i = 0; (i < len) && (bAllAscii); i++)
		     {
		     int tester = (int) characters[i];
		     if (tester > 0x7F)
		          bAllAscii = false;
		     }
		 if (bAllAscii)
		     outBuffer.append(token.toUpperCase());
		 else
		 **/
		     outBuffer.append(token);
		 }
 	     }
	return outBuffer.toString();
	}

      /**
       * This method initializes a hashtable of "special command"
       * objects, one for each special command currently handled by
       * DRAGON. The SpecialCommand class describes the special commands
       * in a way that allows them to be handled here without detailed
       * knowledge of the command's logic.
       */
    protected void initSpecialCommandTable()
        {
	specialCommandTable = new Hashtable(24);
	//    public SpecialCommand(
	//DragonUI mainApp, String verb, int argCount,
	//boolean bLocalOnly, boolean bReplyExpected,
	//Callback callback, Callback postCallback)
        SpecialCommand specCmd = null;
	SetOnePathCallback cb = new SetOnePathCallback();
	specCmd = new SpecialCommand(mainApp,"-DPATH",1,
				     false,false,cb,null);
	specialCommandTable.put("-DPATH",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-WPATH",1,
				     false,false,cb,null);
	specialCommandTable.put("-WPATH",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-CPATH",1,
				     false,false,cb,null);
	specialCommandTable.put("-CPATH",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"ECHO-ON",0,
				     false,false,null,null);
	specialCommandTable.put("ECHO-ON",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"ECHO-OFF",0,
				     false,false,null,null);
	specialCommandTable.put("ECHO-OFF",specCmd);
        //-----
	SetScriptStateCallback ssscb = new SetScriptStateCallback();

	specCmd = new SpecialCommand(mainApp,"RUN",1,
				     false,true,ssscb,ssscb);
	specialCommandTable.put("RUN",specCmd);
	specialCommandTable.put("@",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"CANCEL",0,
				     false,false,null,null);
	specialCommandTable.put("CANCEL",specCmd);
        //-----
        ExitCallback ecb = new ExitCallback();
	specCmd = new SpecialCommand(mainApp,"EXIT",0,
				     true,false,ecb,null);
	specialCommandTable.put("EXIT",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"X",0,
				     true,false,ecb,null);
	specialCommandTable.put("X",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"LOG",1,
				     true,false,new LoggingCallback(),null);
	specialCommandTable.put("LOG",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"START",0,
				     false,false,null,null);
	specialCommandTable.put("START",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-INTERRUPT",0,
				     false,false,null,null);
	specialCommandTable.put("-INTERRUPT",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-RESTART",0,
				     false,true,null,
                                     new ScriptRestartCallback());
	specialCommandTable.put("-RESTART",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-CANCEL",0,
				     false,false,
                                     new ScriptCancelCallback(),null);

	specialCommandTable.put("-CANCEL",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-PAUSE",0,
				     false,true,null,
				     new ScriptPauseCallback());
	specialCommandTable.put("-PAUSE",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-UNPAUSE",0,
				     false,false,null,null);
	specialCommandTable.put("-UNPAUSE",specCmd);
        //-----
	specCmd = new SpecialCommand(mainApp,"-CONTINUE",0,
				     false,false,null,null);
	specialCommandTable.put("-CONTINUE",specCmd);
	//-----
	specCmd = new SpecialCommand(mainApp,"SHOW",1,
				     false,false,null,null);
	specialCommandTable.put("SHOW",specCmd);
	//-----
	specCmd = new SpecialCommand(mainApp,"-SETPERSIST",3,
				     false,false,null,null);
	specialCommandTable.put("-SETPERSIST",specCmd);
	}

      /**
       * Look up a special command by name. Returns null if not
       * found, otherwise the special command object corresponding
       * to the name.
       * @param cmdVerb String used as command verb
       */
    public SpecialCommand getSpecialCommand(String cmdVerb)
        {
	return (SpecialCommand) specialCommandTable.get(cmdVerb);
	}

      /**
       * Returns reference to the logger.
       */
    public Logger getCmdLogger()
        {
	return cmdLogger;
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: CommandLine.java,v 1.30 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

