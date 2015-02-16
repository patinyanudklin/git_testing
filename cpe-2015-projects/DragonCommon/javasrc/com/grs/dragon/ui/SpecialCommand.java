/**
 *   SpecialCommand
 *
 *   Copyright  2001-2007  by Goldin-Rudahl Associates
 * 
 *   Created by Sally Goldin, 5/3/2001
 *
 *   $Id: SpecialCommand.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $
 *   $Log: SpecialCommand.java,v $
 *   Revision 1.6  2007/01/05 07:41:57  rudahl
 *   added Whatis info
 *
 *   Revision 1.5  2001/11/30 18:01:21  goldin
 *   Moved most of the UI basic components to the com.grs.gui package
 *
 *   Revision 1.4  2001/11/05 13:59:16  goldin
 *   Put UI code in a package
 *
 *   Revision 1.3  2001/09/10 14:38:17  goldin
 *   Separate special command processing into pre and post processing, move pre to CommandForwarder
 *
 *   Revision 1.2  2001/05/08 10:14:56  goldin
 *   Refine logging support
 *
 *   Revision 1.1  2001/05/03 15:04:31  goldin
 *   Add special file handling to command line and command forwarder
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;

/**
 * This class describes a special command - a command that can
 * be typed on the command line which requires special handling.
 * This is an attempt to try and avoid, or at least limit, the
 * special purpose code associated with the Dragon UI. Special commands
 * take effect immediately; they do not require a -. or F1
 * <p>
 * A special command is described in terms of 
 * <ul>
 * <li>the command string
 * <li>how many arguments required
 * <li>whether it gets sent to the command processor and on
 *     to the script server
 * <li>whether to expect a reply file back from the server.
 * <li>an optional callback which can contain arbitrary code in
 *     its executeCallback method, which is called before sending
 *     the command to the server 
 * <li>an optional post-processing callback which can contain
 *     arbitrary code, called when the command forwarder receives
 *     a reply. (Should never have a postCallback if there is no
 *     reply expected.)
 * </ul>
 * <p>
 * There is one instance of a SpecialCommand for each distinct special
 * command. That instance can be used as temporary storage for the
 * arguments associated with a particular invocation of the command.
 */
public class SpecialCommand
    {
      /**
       * command verb
       */
    protected String verb = null;

      /**
       * argument count. Note that at present we support only
       * zero or one arguments.
       */
    protected int argCount = 0;

      /**
       * Argument text if any.
       */
    protected String argText = null;
      /**
       * Postprocessing argument text if any.
       */
    protected String postArgText = null;


      /**
       * If true, command is handled in the UI only - do not ship to
       * the server.
       */
    protected boolean bLocalOnly = false;

      /**
       * if true, expect a reply. Otherwise, do not.
       */
    protected boolean bReplyExpected = true;

      /**
       * Callback to execute special preprocessing code.
       */
    protected Callback callback = null;

      /**
       * Callback to execute special postprocessing code.
       */
    protected Callback postCallback = null;

      /**
       * Dummy DFixedText to pass to callback. Used to 
       * transmit arguments to callback.
       */
    protected DFixedText argCarrier = null;

      /**
       * Dummy DFixedText to pass to postprocessing callback. Used to 
       * transmit arguments to callback.
       */
    protected DFixedText postArgCarrier = null;

      /**
       * Reference to main application.
       */
    protected DragonUI mainApp = null;

      /**
       * Constructor sets all relevant properties of the
       * special command.
       */
    public SpecialCommand(DragonUI mainApp, String verb, int argCount,
			  boolean bLocalOnly, boolean bReplyExpected,
			  Callback callback, Callback postCallback)
       {
       this.mainApp = mainApp;
       this.verb = verb;
       this.argCount = argCount;
       this.bLocalOnly = bLocalOnly;
       this.bReplyExpected = bReplyExpected;
       if (callback != null)
	   {
	   this.callback = callback;
	   argCarrier = new DFixedText(verb,"Dummy");
           argCarrier.setParentComponent(mainApp);
	   }
       if (postCallback != null)
	   {
	   this.postCallback = postCallback;
	   postArgCarrier = new DFixedText("post" + verb,"Dummy");
           postArgCarrier.setParentComponent(mainApp);
	   }
       }

      /**
       * Return command string - verb and argument if any
       */
    public String getCommandString()
        {
	StringBuffer cmd = new StringBuffer();
	cmd.append(verb);
	if (argCount > 0)
	    {
	    cmd.append(" ");
	    cmd.append(argText);
	    }
	return cmd.toString();
	}

      /**
       * Set argument text from current instance of command.
       * Also set this value into the DFixedText if one exists.
       */
    public void setArgText(String text)
        {
	argText = text;
	if (argCarrier != null)
            argCarrier.setLabelText(text);
	}

      /**
       * Set argument text for postprocessing command.
       * Also set this value into the DFixedText if one exists.
       */
    public void setPostArgText(String text)
        {
	postArgText = text;
	if (postArgCarrier != null)
            postArgCarrier.setLabelText(text);
	}

      /**
       * Return local only information.
       */
    public boolean isLocalOnly()
        {
        return bLocalOnly;
	}
      /**
       * Return whether reply is expected
       */
    public boolean isReplyExpected()
        {
	return bReplyExpected;
	}

      /**
       * Return argument count.
       */
    public int getArgCount()
        {
	return argCount;
	}

      /**
       * Return the command verb.
       */
    public String getVerb()
        {
	return verb;
	}

      /**
       * Do special command preprocessing logic. This is called before
       * shipping the command off to the server.
       */
    public void doPreprocessing()
        {
	if (callback != null)
	    {
	    callback.executeCallback(argCarrier);
	    }
        }
      /**
       * Do special command postprocessing logic. This is called before
       * shipping the command off to the server.
       */
    public void doPostprocessing()
        {
	if (postCallback != null)
	    {
	    postCallback.executeCallback(postArgCarrier);
	    }
        }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: SpecialCommand.java,v 1.6 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
   }
