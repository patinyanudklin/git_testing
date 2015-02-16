/* DragonPanel.java
 *
 * Copyright  2001-2007 Sally Goldin and Kurt Rudahl
 *
 * $Id: DragonPanel.java,v 1.22.2.1 2010/09/10 10:00:32 rudahl Exp $
 * $Log: DragonPanel.java,v $
 * Revision 1.22.2.1  2010/09/10 10:00:32  rudahl
 * Fix for java 1.6
 *
 * Revision 1.22  2007/02/03 09:29:05  goldin
 * Remove messages about controls being too large
 *
 * Revision 1.21  2007/01/14 11:53:44  goldin
 * Allow a choice as to whether a panel returns all tabs or not
 *
 * Revision 1.20  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.19  2006/12/28 10:34:21  goldin
 * Complete implementation of multifile selection control and file chooser
 *
 * Revision 1.18  2006/11/24 12:01:46  goldin
 * Don't add parameters from unselected tab pane to command
 *
 * Revision 1.17  2006/11/23 08:56:26  goldin
 * Fix problems in import response panel
 *
 * Revision 1.16  2006/11/18 10:51:32  goldin
 * Make border on tabbed panes a bit wider
 *
 * Revision 1.15  2006/01/20 08:42:49  goldin
 * Hold on to the MemoryFilter at the panel level
 *
 * Revision 1.14  2006/01/14 09:23:55  goldin
 * Fix keyboard navigation problems
 *
 * Revision 1.13  2005/12/21 07:43:20  goldin
 * Don't try to give focus to fixed text or font fields
 *
 * Revision 1.12  2005/02/06 08:08:11  goldin
 * Fix JavaDoc warnings
 *
 * Revision 1.11  2002/10/23 21:03:22  goldin
 * Special handling for tabbed panels
 *
 * Revision 1.10  2002/06/28 14:11:02  goldin
 * Provide infrastructure for usermanual help implementation
 *
 * Revision 1.9  2002/06/11 21:21:50  goldin
 * Cosmetic improvments
 *
 * Revision 1.8  2002/04/29 17:23:23  goldin
 * Add enclosingFrame property
 *
 * Revision 1.7  2002/04/17 00:54:16  goldin
 * Fix problem with dual error msg display when clicking on OK
 *
 * Revision 1.6  2002/04/02 00:13:28  goldin
 * Put in infrastructure for testing for file overwrite warning flag
 *
 * Revision 1.5  2002/01/22 14:56:16  goldin
 * Add code to always show first tab in tabbed panel
 *
 * Revision 1.4  2002/01/22 11:37:34  goldin
 * Add some space inside bordered subpanels
 *
 * Revision 1.3  2001/12/11 14:24:26  goldin
 * Add setFocusFirst method
 *
 * Revision 1.2  2001/12/03 18:04:19  goldin
 * Add saveValues method for install kit
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.38  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.37  2001/10/23 12:00:03  goldin
 * Need to clear disabled as well as enabled fields when panel first appears
 *
 * Revision 1.36  2001/10/12 18:39:33  goldin
 * Fix contents of query reply by not including fixed text fields in getAttributeValueList output
 *
 * Revision 1.35  2001/10/02 13:21:23  goldin
 * Add tracing for debug purposes
 *
 * Revision 1.34  2001/06/13 19:53:17  goldin
 * Put spaces in front of cmd continuation lines
 *
 * Revision 1.33  2001/05/29 10:35:28  goldin
 * Add tab disabling capability
 *
 * Revision 1.32  2001/05/28 16:36:26  goldin
 * Debugging QueryProcessor
 *
 * Revision 1.31  2001/05/27 15:41:44  goldin
 * Additional work on query processor class and related functionality
 *
 * Revision 1.30  2001/05/24 11:56:12  goldin
 * Begin work on query processor
 *
 * Revision 1.29  2001/05/22 12:05:13  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 * Revision 1.28  2001/04/26 12:24:23  goldin
 * further work on command line functionality
 *
 * Revision 1.27  2001/04/25 12:18:32  goldin
 * Fix bug wrt border redraw; set focus to first control
 *
 * Revision 1.26  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.25  2001/04/18 13:13:51  goldin
 * Make panel size consistent with actual app
 *
 * Revision 1.24  2001/04/10 11:18:46  goldin
 * Fix problem with modal dialog in FileValidator; extend IntegerValidator
 *
 * Revision 1.23  2001/04/05 13:34:50  goldin
 * Cleanup behavior, fix XML errors
 *
 * Revision 1.22  2001/03/26 18:50:06  goldin
 * Shrink the main window
 *
 * Revision 1.21  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 * Revision 1.20  2001/03/21 13:05:39  goldin
 * Add language selection and config file processing functionality
 *
 * Revision 1.19  2001/03/20 18:04:15  goldin
 * Implement tabbed panes, clean up menu help:
 *
 * Revision 1.18  2001/03/20 13:33:02  goldin
 * Disable all fields after OK
 *
 * Revision 1.17  2001/03/14 16:40:05  goldin
 * Made getField recursive
 *
 * Revision 1.16  2001/03/03 19:56:58  goldin
 * Fine tuning screen layout and appearance
 *
 * Revision 1.15  2001/03/02 19:56:21  goldin
 * Add horizontal label option for DTextFields, add handling of translated help msgs
 *
 * Revision 1.14  2001/02/28 16:24:29  goldin
 * implementing defaults, enhancements to help editor
 *
 * Revision 1.13  2001/02/28 11:50:12  goldin
 * Extend mouse handling to checkbuttons and push buttons
 *
 * Revision 1.12  2001/02/20 18:39:13  goldin
 * Add callback handling
 *
 * Revision 1.11  2001/02/08 16:14:39  goldin
 * Added HelpEditor capability
 *
 * Revision 1.10  2001/01/29 15:19:32  goldin
 * Continued work on UI
 *
 * Revision 1.9  2001/01/29 12:23:28  goldin
 * Put official UI file in CVS, also new class to control resizing
 *
 * Revision 1.8  2001/01/25 20:16:19  goldin
 * Continued work on layout and XML parsing
 *
 * Revision 1.7  2001/01/22 16:14:26  goldin
 * Changes to parse actual generated XML file
 *
 * Revision 1.6  2001/01/17 14:18:23  goldin
 * Actually build initial trial panel from XML document
 *
 * Revision 1.5  2001/01/16 17:50:30  goldin
 * Began implemenation of XML parsing to create UI
 *
 * Revision 1.4  2001/01/15 14:20:25  goldin
 * Implement new layout options, makeClone methods
 *
 * Revision 1.3  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 * Revision 1.2  2001/01/09 15:58:55  goldin
 * continued work implementing basic appearance of UI components
 *
 * Revision 1.1  2001/01/08 19:34:42  goldin
 * Initial population for new DRAGON-Java UI
 *
 */

package com.grs.gui;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;
import java.util.*;

/** This class is the primary container for DRAGON screens, that is
*   the response panel container. It holds knowledge about
*   how to lay out fields and how to process the input when
*   the user clicks on Execute/Ok.
* @author  goldin
* @version  Mon Jan 08 11:36:01 EST 2001*/

public class DragonPanel extends JPanel
    {
     /* If true, the command should be constructed
      * using fields on all tabs. If false,
      * only use the currently selected tab.
      */
    protected boolean bReturnAllTabs = true;

    protected static int fileFieldChars = 0;

      /**
       * Table used to hold values for each field in a panel.
       * This static table allows different panels to share
       * values with eachother, and an outside application to
       * retrieve any value - provided that the "saveValues" method
       * has been called on each DragonPanel.
       */
    public static Hashtable fieldValueTable = new Hashtable(200);

      /**
       * Ordered list of all fields and subpanels.
       */
    protected ArrayList allItems = new ArrayList(30);

      /** If true, this is a primary panel, that is, a top-level
       *   DRAGON response panel. A primary panel
       *   cannot be a tabbed panel (that is, bTabbed must
       *   be false.)
       *   
       */
    protected boolean bPrimary = true;
    
      /** If true, this is a tabbed panel. A panel cannot
       *   be a primary panel and a tabbed panel simultaneously.
       */
    protected boolean bTabbed = false;

      /**
       * If true, this is a tabGroup panel.
       */
    protected boolean bTabGroup = false;

      /** If true, this is a popup subpanel. A panel cannot
       *   be a primary panel and a popup panel simultaneously.
       */
    protected boolean bPopup = false;
    
      /**
       * If true, this panel needs extra space for its help messages.
       */
    protected boolean bBigHelp = false;

      /** Table mapping field names to field object instances;
       *   populated during construction of panel, used for
       *   callbacks and to get data from fields.
       */
    protected Hashtable fieldTable = new Hashtable();
    
      /** Counts the number of fields and panels added to the
       *   panel so far.
       */
    protected int itemCount = 0;
    
      /** Unique name for the panel as a whole
       */
    protected String name;
    
      /** Command that is implemented by this panel, e.g.
       *   "D 3BA". Will be empty for panels that have only local
       *   effects, such as the logging panel.
       */
    protected String panelCommand;
    
      /**
       * String used to construct link to details. This will
       * be the unqualified command name unless that is ambiguous,
       * e.g. for LIS
       */
    protected String detailsLink = null;

      /**
       * Title or label for the panel. How this is displayed depends
       * on whether the panel is primary, tabbed, etc.
       */
    protected String title = null;

      /** Integer indicating the order in which this panel
       *   was added to its parent panel. This is within the
       *   same ordinal sequence as the fields, that is if a panel
       *   was added after field 2 , it would have a panelNumber of
       *    3
       */
    protected int panelNumber;
    
      /**
       * Size of the enclosing panel. Used in the layout algorithm.
       */
    protected Dimension panelSize = new Dimension(680,500);

      /**
       * Size of a popup subpanel. Used in the layout algorithm.
       */
    protected Dimension popupSize = new Dimension(300,150);


      /** Table of all panels added to the current panel,
       *   keyed by name.
       */
    protected Hashtable localPanelTable = new Hashtable();
    
      /** For subpanels, references the panel within which the
       *   subpanel is directly embedded.*/
    protected DragonPanel parentPanel = null;
    
      /**
       * For popups, what field on the main panel invoked this popup.
       * This must be set in the callback that displays the popup.*/
    protected DragonField invokingField = null;

      /**
       * For popups, reference to the dialog enclosing the panel.
       */
    protected JDialog popupDialog = null;

      /**
       * For standalone panels, reference to the frame enclosing the panel.
       */
    protected JFrame enclosingFrame = null;

      /**
       * For tabGroups, reference to tabbed pane, so we can
       * enable/disable tabs. Null unless bTabGroup is true.
       */
    protected JTabbedPane tabbedPane = null;

      /**
       * If this flag is set to true, then we do not align the
       * controls in columns, but instead use a flow layout.
       */
    protected boolean bFlowRow = false;

      /**
       * If this flag is true, there is a border, which will 
       * take up some screen real-estate.
       */
    protected boolean bBorderOn = false;

      /**
       * If this flag is true, then this panel should be placed
       * at the bottom of the layout, hugging the bottom of the
       * panel even if is empty space above.
       */
    protected boolean bBottom = false;

      /**
       * Number of columns in the layout. Make this a parameter
       * in order to provide flexiblity. Default is 4.
       */
    protected int columnCount = 4;

      /**
       * Label holding title. Make class-global so title can
       * be changed if desired.
       */
    protected JLabel titleLabel = null;
     
      /**
       * reference to hashtable of dialogs. Needed in order to access
       * popups. Must be explicitly initialized by parent application
       */
    protected Hashtable dialogTable = null;
      /**
       * reference to hashtable of normal panels. Needed in order to process
       * popups. Must be explicitly initialized by parent application
       */
    protected Hashtable panelTable = null;

      /**
       * Make some space between controls
       */
    protected int SPACING = 5;

      /**
       * If true, size has already been set by external
       * class, so do not override.
       */
    protected boolean bSizeSet = false;

      /**
       * If true, the panel is currently being validated globally
       * by checkFieldValidity. Any scheduled messages from individual
       * focusLost events should not be delivered.
       */
    protected boolean bValidatingAll = false;

      /**
       * If true, panel is enabled, else not. Used to
       * suppress processing of tabbed panels that are disabled
       */
    protected boolean bEnabled = true;

      /**
       * Hold on to reference for "memory filter" at the panel level.
       */
    protected MemoryFilter memoryFilter = null;

    //********************************************************************
      /** 
       * Constructor takes name of the panel as an argument.
       */
    public DragonPanel(String panelName)
        {
	super();
	name = panelName;
	setLayout(new BorderLayout());
	setSize(panelSize);
	}

    //********************************************************************
      /**
       * Create and return a clone of this panel, including of all its
       * fields and subpanels. This is necessary in order for us to
       * be able to reuse subpanel definitions. This method does
       * not call doPanelLayout on the returned clone. It also does
       * not copy data that will be initialized when the clone is added
       * to its parent panel.
       */
    public DragonPanel makeClone()
                   throws Exception
        {
	DragonPanel clone = new DragonPanel(this.name);
	// copy data
	clone.setPrimary(bPrimary);
	clone.setTabbed(bTabbed);
	clone.setTabGroup(bTabGroup);
	clone.setColumnCount(columnCount);
	clone.setBottom(bBottom);
	clone.setFlowRow(bFlowRow);
	clone.setBigHelp(bBigHelp);
	clone.setTitle(title);
	if (bBorderOn)
	    clone.setBorderOn();
	clone.setPanelCommand(panelCommand);
	clone.setDetailsLink(detailsLink);
	clone.setReturnAllTabs(bReturnAllTabs);
	// now iterate through the child objects, cloning and adding them
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		clone.addField(field.makeClone());
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
                DragonPanel newSub = panel.makeClone();
		newSub.doPanelLayout();
		clone.addPanel(newSub);
		}
	    }
	return clone;
	}

    //********************************************************************
    public void setBorderOn()
        {
	bBorderOn = true;
	setBorder(BorderFactory.createCompoundBorder(
                  BorderFactory.createEtchedBorder(),
		  BorderFactory.createEmptyBorder(10,10,10,10)));
	}

    //********************************************************************
      /** Adds a field to the set maintained by the panel. Marks
       *   the field with an ordinal indicating the order in which
       *   it was added.
       * @param  field Field object to be added to the set of
       *   those managed by the panel.
       */
    public void addField(DragonField field)
              throws Exception 
        {
        if (bTabGroup)
	    {
	    throw new Exception("Error constructing tab group panel " +
		name + "; tab groups cannot hold fields.");
	    }
	field.setFieldNumber(itemCount);
	itemCount++;
	fieldTable.put(field.getName(),field);
	field.setParentPanel(this);
	allItems.add(field);
        }
    
    //********************************************************************
      /** Adds a subpanel to the layout of another panel.
       *   The ordinal will be used to determine where in
       *   the panel the subpanel should appear.
       * @param  panel Panel to add to the layout being processed.
       */
    public void addPanel(DragonPanel panel) throws Exception 
        {
        if ((bTabGroup) && (!panel.isTabbed()))
	    {
	    throw new Exception("Error constructing tab group panel " +
		name + "; child panels must all be of type tabbed.");
	    }
	panel.setPanelNumber(itemCount);
	itemCount++;
	localPanelTable.put(panel.getName(),panel);
	panel.setParentPanel(this);
	allItems.add(panel);
        }
    
    //********************************************************************
      /** Constructs a DRAGON script command based on the current
       *   contents of the controls in the panel.
       *   Skip if this is a tabbed panel and not the currently selected one.
       */
    public String constructCommand() 
        {
	int lastNewlinePos = 0;
	StringBuffer cmd = new StringBuffer(2048);
	StringBuffer onePair = new StringBuffer(80);
        if (!bEnabled)
            return "";
        if ((bTabbed) && (!bReturnAllTabs) &&
            (!getParentPanel().isSelected(this)))
            return "";  // don't check if the current tab is not at the front
	if ((panelCommand != null) && (panelCommand.length() > 0))
	    cmd.append(panelCommand + " ");
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if ((uiItem instanceof DragonField) &&
                (!(uiItem instanceof DFixedText)))
	        {
		DragonField field = (DragonField) uiItem;
		if ((field.isEnabled()) && 
		    (field.getPSpecifier() != null) &&
		    (field.getFieldValue() != null))
		    
		    {
		    if (uiItem instanceof DMultiFileField)
                        {
			DMultiFileField mField = (DMultiFileField) uiItem;
			onePair.append(mField.getMultiFieldValue());
		        }
                    else if (field.getFieldValue().length() > 0)
                        {
		        onePair.append(field.getPSpecifier() + " ");
		        onePair.append("\"" + 
                                      field.getFieldValue() + 
                                       "\"" + " ");
                        }
		    }
		if ((cmd.length() - lastNewlinePos + onePair.length()) > 60)
		    {
		    cmd.append("\n  ");
		    lastNewlinePos = cmd.length() - 3;
		    }
		cmd.append(onePair);
		onePair.delete(0,onePair.length());
		String subcmd = field.getCallbackSubCommand();
		if ((subcmd != null) && (subcmd.length() > 0))
		    {
		    if ((cmd.length() - lastNewlinePos + subcmd.length()) > 60)
		        {
			cmd.append("\n  ");
			lastNewlinePos = cmd.length() - 3;
			}
		    cmd.append(subcmd + " ");
		    }
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		String subcmd = panel.constructCommand();
		if ((subcmd != null) && (subcmd.length() > 0))
		    {
                    int subNewline = subcmd.indexOf("\n");
		    if (subNewline < 0)
                        subNewline = subcmd.length();
		    if ((cmd.length() - lastNewlinePos + subNewline) > 60)
		        {
			cmd.append("\n  ");
			lastNewlinePos = cmd.length() - 3;
			}
		    cmd.append(subcmd + " ");
		    }
		}
	    }
	return cmd.toString();
        }

      /** 
       *   Runs through the panel and saves all non-empty field values
       *   in the passed hashtable, using the field Ids as keys.
       */
    public void saveValues() 
        {
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if ((uiItem instanceof DragonField) &&
                (!(uiItem instanceof DFixedText)))
	        {
		DragonField field = (DragonField) uiItem;
		if ((field.isEnabled()) && 
		    (field.getFieldValue() != null) && 
		    (field.getFieldValue().length() > 0) )
		    {
		    fieldValueTable.put(field.getName(), field.getFieldValue());
		    }
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.saveValues();
		}
	    }
        }

   
     /** This method applies only to panels that are tab groups.
      * If this panel is a tabgroup, then the method checks to
      * see if the selected (visible) tab pane is childPanel.
      * If it is, the method returns true. If it is not, or if
      * the current DragonPanel is not a tabgroup, returns false.
      * @param childPanel Panel to check for current selection.
      * @return true if this is a tabgroup and the child panel
      * is selected; otherwise false.
      */
    public boolean isSelected(DragonPanel childPanel)
        {
        boolean bSelected = false;
        if ((bTabGroup) && (tabbedPane.getSelectedComponent() == childPanel))
            bSelected = true;
        return bSelected;
        }    

    //********************************************************************
      /**
       * Runs through all enabled fields in the panel, and checks
       * to make sure that any that are marked as required
       * do in fact have values. (Normally all validation functions
       * should have been called on the fields, before this method
       * is called. So we only check to make sure that the value is
       * not empty.
       * @return First required field that has a missing values.
       *          If all have values, returns null
       *           
       */
    public DragonField checkRequiredFields()
        {
	DragonField missingField = null;
        if ((bTabbed) && (!getParentPanel().isSelected(this)))
            return missingField;  // don't check if the current tab is not at the front
	for (int i = 0; (i < itemCount) && (missingField == null); i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		if ((field.isEnabled()) && 
		    (field.isRequired()))
		    {
		    String value = null;
		    if (uiItem instanceof DMultiFileField)
			{
			value = ((DMultiFileField) field).getMultiFieldValue();
			}
		    else
			{
		        value = field.getFieldValue();
		        }
		    if ((value == null) || 
			(value.length() == 0))
		        missingField = field;
		    }
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		missingField = panel.checkRequiredFields();
		}
	    }
	return missingField;
	}
    
    //********************************************************************
      /**
       * Runs through all enabled fields in the panel, and executes
       * the validation function for each. 
       * @return First field that has an invalid value.
       *          If all values are valid, returns null
       *           
       */
    public DragonField checkFieldValidity()
        {
	DragonField invalidField = null;
	for (int i = 0; (i < itemCount) && (invalidField == null); i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		if (field.isEnabled())
		    {
		    if (!field.isFieldValueValid())
		        invalidField = field;
		    }
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		invalidField = panel.checkFieldValidity();
		}
	    }
	return invalidField;
	}
    //********************************************************************
      /**
       * Runs through all enabled fields in the panel, and sets the
       * value for each to be its default value, if any.
       * Also, disables all fields that should be disabled by default.
       * For subpanels, calls the setAllToDefaults method on them.
       */
    public void setAllToDefaults()
        {
	Initializer initObject = null;
        boolean bFirstEnabled = true;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
                field.setUserData(null);  // clear old references
		if (field.isDefaultEnabled())
		    {
		    field.setEnabled(true);
		    initObject = field.getInitializer();
		    if (initObject != null)
		        {
			initObject.setInitialValue(field);
			}
		    else
		        {
		        String dflt = field.getDefaultValue();
		        if (dflt != null)
		             field.setFieldValue(dflt);
			else 
			     field.clearField();
			}
		    if (!(field instanceof DFontField) &&
                        !(field instanceof DFixedText) &&
                         (bFirstEnabled) && 
                        (bPrimary || bPopup ||
                          ( bTabbed && (getPanelNumber() == 0))) )
		        {
			bFirstEnabled = false;
			field.requestFocus();
			}
		    }
		else 
  		    {
                    field.clearField();
                    field.setEnabled(false);
		    }
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setAllToDefaults();
		}
	    }
	if (bTabGroup)  // if this is a tab group, reset to first tab
	    {
            if (tabbedPane != null)
	        {
                tabbedPane.setSelectedIndex(0);
		}
	    }
	}

      //*************************************************************
      /**
       * Runs through all fields in the panel and disables all of them.
       * This is called after the user chooses OK.
       * For subpanels, calls the setAllDisabled method on them.
       */
    public void setAllDisabled()
        {
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		field.setEnabled(false);
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setAllDisabled();
		}
	    }
	}

    //********************************************************************
      /**
       * Runs through all fields in the panel, and adds the passed
       * object as mouse listener for each. This is to handle help display.
       * @param listener Reference to object that will handle help display
       */
    public void setMouseListener(MouseListener listener)
        {
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		field.addMouseListener(listener);
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setMouseListener(listener);
		}
	    }
	}
    
      /**
       * Runs through all fields in the panel, and adds the passed
       * object as key listener for each. This is to handle Dragon-specific
       * keys e.g. for help, history, etc.
       * @param listener Reference to object that will handle keys
       */
    public void setKeyListener(KeyListener listener)
         {
	 for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		field.addKeyListener(listener);
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setKeyListener(listener);
		}
	    }
	}
    
      /**
       * Runs through all fields in the panel, and adds the passed
       * object as memory filter for all DFileFields.
       * @param filter Reference to memory filter
       */
    public void setMemoryFilter(MemoryFilter filter)
        {
        memoryFilter = filter;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DFileField)
	        {
		DFileField field = (DFileField) uiItem;
		field.setMemoryFilter(filter);
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setMemoryFilter(filter);
		}
	    }
	}

      /** Return currently set memory filter if any
       */
    public MemoryFilter getMemoryFilter()
       {
       return memoryFilter;
       }

      /**
       * Display a popup dialog centered on the current panel.
       * @param dlgID  ID of popup dialog to display.
       */
    public void showPopup(String dlgID)
        {
	if (dialogTable == null)
	    return;
	JDialog dlg = (JDialog) dialogTable.get(dlgID);
	if (dlg != null)
	    {
	    dlg.setLocationRelativeTo(this);
	    dlg.show();
	    }
	}

      /**
       * Finds the DragonPanel associated with a particular
       * panel ID and sets its invokingField attribute to a particular
       * field. Normally, the specified DragonPanel is a popup,
       * which is invoked in response to some values in the specified
       * field. The invokingField attribute is used to pass the
       * popup command fragment back to the main panel.
       * @param panelID ID of the popup panel.
       * @param field   Reference to the field that invokes this panel.
       */
    public void setInvoker(String panelID, DragonField field)
        {
	if (panelTable == null)
            return;
	DragonPanel popup = (DragonPanel) panelTable.get(panelID);
	if (popup != null)
	    {
	    popup.setInvokingField(field);
	    }
	}

       

    //********************************************************************
      /** 
       *   This is the primary layout method. It should be called after
       *   all controls and subpanels have been added. Also, the 
       *   doPanelLayout method of subpanels must be invoked before the
       *   same method is called on the main panel.
       *   Calculates the appropriate layout, size and positioning for each
       *   field previously added to the panel, and then actually adds them
       *   to the UI.
       */
    public void doPanelLayout() 
        {
	if (bTabGroup)
	    {
	    doTabGroupLayout();
	    return;
	    }
	if (bPopup)
	    {
            if (!bSizeSet)
	         {
	         setPreferredSize(popupSize);
		 }
	    setSize(getPreferredSize());
	    columnCount = 2;
	    setBorder(BorderFactory.createEmptyBorder
				     (10,10,0,5));
	    }
	if (bTabbed)
	    {
	    setBorder(BorderFactory.createEmptyBorder
				     (10,10,10,10));
            }
	JPanel subPanel = null;
	JPanel newPanel = null;
	Vector rows = computeRows();
	subPanel = new JPanel(new BorderLayout());
	add(subPanel, BorderLayout.NORTH);
	if (bPrimary)  // popups put the title in the title bar of the dlg
	    {
	    setBorder(BorderFactory.createEmptyBorder
				     (10,10,10,10));
	    JPanel enclosingPanel = new JPanel();
	    enclosingPanel.setBorder(BorderFactory.createEmptyBorder
				     (10,10,10,10));
	    JPanel titlePanel = new JPanel(new FlowLayout());
	    titlePanel.setBorder(BorderFactory.createEtchedBorder());
	    if (title != null)
	        titleLabel = new JLabel(title);
	    else 
	        titleLabel = new JLabel("DUMMY TITLE");
	    titleLabel.setHorizontalAlignment(SwingConstants.CENTER);
	    titlePanel.add(titleLabel);
	    enclosingPanel.add(titlePanel);
	    subPanel.add(enclosingPanel,BorderLayout.NORTH);
	    newPanel = new JPanel(new BorderLayout());
	    subPanel.add(newPanel,BorderLayout.SOUTH);
	    subPanel = newPanel;
	    }

	for (int iRow = 0; iRow < rows.size(); iRow++)
  	    {
	    Vector controls = (Vector) rows.get(iRow);
	    JPanel rowPanel = layoutRow(controls);
	    if ( (iRow == rows.size() - 1) &&
		 (isBottomRow(controls)) )
	        add(rowPanel,BorderLayout.SOUTH);
	    else
	        subPanel.add(rowPanel,BorderLayout.NORTH);
	    // if this is not the last row, allocate a new subpanel
	    if (iRow < rows.size() - 1)
	        {
		newPanel = new JPanel(new BorderLayout());
		subPanel.add(newPanel,BorderLayout.SOUTH);
		subPanel = newPanel;
	        }
	    }
        }

	/**
	 * Factorization of doPanelLayout. Figures out, based on size
	 * plus layout directives, which controls/panels will
	 * be in which rows. Returns a vector of vectors (one
	 * vector for each row.
	 */
    protected Vector computeRows()
        {
	Dimension controlSize = new Dimension(0,0);
	int[] colWidths = new int[columnCount];
	int fullWidth = getSize().width;
	if ((bBorderOn) || (bTabbed))
             fullWidth -= 20;
        if (bPrimary)
	     fullWidth -= 20;
	colWidths[0] = (fullWidth / columnCount) - SPACING;
	for (int i = 1; i < columnCount; i++)
	    {
            colWidths[i] = colWidths[i - 1] + colWidths[0];
	    }
        Vector allRows = new Vector();
	Vector oneRow = new Vector();
	int remainingWidth = fullWidth;
	int maxHeight = 0;

	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		int width = field.calculateWidth();
		int height = field.calculateHeight();
		if (width > fullWidth)
		    {
		    if (field instanceof DFileField)
		        {
			DFileField fileField = (DFileField) field;
			if (fileFieldChars == 0)
			    {
			      /** all file fields same width so only
			       * calculate this once.
			       */
			    int currentChars = fileField.getActualWidth();
			    while (width > fullWidth)
			        {
				currentChars -= 1;
			        fileField.setActualWidth(currentChars);
			        width = fileField.calculateWidth();
			        }
			    fileFieldChars = currentChars + 1;
			    }
			if (bTabbed)
			    fileField.setActualWidth(fileFieldChars - 3);
			else
			    fileField.setActualWidth(fileFieldChars);
			}
		    else
		        {
			    /**
		        System.out.println("Control " +
				       field.getName() +
				       " too large for layout");
		        System.out.println("  Control width is " + width +
				       " while panel width is " +
				       fullWidth);
			    **/
			width = fullWidth;
			}
		    }
		if ((field.getNewLine()) || 
		    (field.getCentered()) || 
		    (width > remainingWidth))
		    {
		    if (oneRow.size() > 0)
		        {
			allRows.add(oneRow);
			oneRow = new Vector();
			}
		    maxHeight = 0;
		    remainingWidth = fullWidth;
		    }
		maxHeight = Math.max(height,maxHeight);
		// "quantize" the control sizes - UNLESS we are
		// creating a flowed row or the field is a centered
		// control.
		if ((!bFlowRow) && (!field.getCentered()))
		    {
	            width = quantizeWidth(width,colWidths);
		    if (width == 0)
		        width = fullWidth;
		    }
		controlSize.width = width;
		controlSize.height = maxHeight;
		field.setPreferredSize(controlSize);
		remainingWidth -= width;
		oneRow.add(field);
		if (field.getCentered()) 
		  // by defn, centered controls live alone 
		  // on their row.
		    {
		    allRows.add(oneRow);
		    oneRow = new Vector();
		    maxHeight = 0;
		    remainingWidth = fullWidth;
		    }
		}
	    else if (uiItem instanceof DragonPanel)
	        {
		// for now, enforce the constraint that a subpanel
		// always gets a row of its own.
		DragonPanel panel = (DragonPanel) uiItem;
		if (oneRow.size() > 0)
		    {
		    allRows.add(oneRow);
		    oneRow = new Vector();
		    }
		oneRow.add(panel);
		Dimension dim = panel.getPreferredSize();

		if (panel.isBorderOn())
		    dim.width = fullWidth - 20;
		else
		    dim.width = fullWidth;
	        panel.setPreferredSize(dim);
	        panel.setSize(dim);
		allRows.add(oneRow);
		oneRow = new Vector();
		maxHeight = 0;
		remainingWidth = fullWidth;
		}
	    }
	if (oneRow.size() > 0)
	    allRows.add(oneRow);
	return allRows;
	}

   
      /**
       * Factorization of doPanelLayout. Given an original control
       * width, plus an array of widths that depends on the number
       * of columns, determine which is closest to the control
       * width (e.g. one quarter of the panel, one half of the panel,
       * etc.) and return that width. Note, will return 0 if the
       * control is too wide for the panel.
       */
    protected int quantizeWidth(int controlWidth, int[] colWidth)
        {
	int width = 0;
        for (int i = 0; (i < columnCount) && (width == 0); i++)
	    {
	    if (controlWidth < colWidth[i])
	        width = colWidth[i];
	    }
	return width;
	}

      /**
       * Factorization of doPanelLayout. Give a Vector of controls,
       * lays them out in a single row, based on the setting of 
       * bFlowRow.
       */
    protected JPanel layoutRow(Vector controls)
        {
	// See if this is a centered row. If it is, then we handle
	// the layout entirely differently
	if (controls.size() == 1)
	    {
	    Object uiItem = controls.get(0);
	    if (uiItem instanceof DragonField)
	        {
		DragonField field = (DragonField) uiItem;
		if (field.getCentered())
		    return layoutCenteredRow(field);
		}
	    }
	if (bFlowRow)
	    return layoutFlowedRow(controls);
	else
	    return layoutColumnedRow(controls);
	}

      /**
       * Factorization of doPanelLayout. Give a Vector of controls,
       * determines if at least one of them is marked as the "bottom"
       * If so, returns true, else returns false.
       */
    protected boolean isBottomRow(Vector controls)
        {
	for (int i = 0; i < controls.size(); i++)
	    {
	    Object uiItem = controls.get(0);
	    if (uiItem instanceof DragonField)
	        { 
		DragonField field = (DragonField) uiItem;
		if (field.isBottom())
		    return true;
	        } 
	    else 
	        { 
		DragonPanel panel = (DragonPanel) uiItem;
		if (panel.isBottom())
		    return true;
	        } 
	    }
	return false;
	}

      /**
       * Factorization of layoutRow. Give a single field, adds that
       * field in the center of the row.
       */
    protected JPanel layoutCenteredRow(DragonField field)
        {
	JPanel rowPanel = new JPanel(new GridBagLayout());
	// a single component in a gridbaglayout will be centered
	rowPanel.add(field);
	return rowPanel;
	}

      /**
       * Factorization of layoutRow. Give a Vector of controls,
       * lays them out in a single row with a flow layout.
       */
    protected JPanel layoutFlowedRow(Vector controls)
        {
	JPanel rowPanel = new JPanel(new FlowLayout());
	DragonField field = null;
	for (int i = 0; i < controls.size(); i++)
	    {
	    JComponent uiItem = (JComponent) controls.get(i);
	    rowPanel.add(uiItem);
	    }
	return rowPanel;
	}

      /**
       * Factorization of layoutRow. Give a Vector of controls,
       * figures out and constructs a set of nested panels with
       * borderlayouts that will preserve the horizontal dimensions
       * of the controls. Returns the top level JPanel for the row.
       * Note we assume that there will never be more than columnCount
       * items in a row. This should be enforced by the code that
       * actually creates the control vector.
       */
    protected JPanel layoutColumnedRow(Vector controls)
        {
	JPanel rowPanel = new JPanel(new BorderLayout());
	JComponent field = null;
	JPanel innerPanel = new JPanel(new BorderLayout());
	JPanel outerPanel = rowPanel;
	outerPanel.add(innerPanel,BorderLayout.WEST);

	  // There can be between one and 'columnCount' in a row.
	int ctrlCount = controls.size();
	if (ctrlCount > columnCount)
	    {
	    System.out.println("Unexpected error:" +
				controls.size() + 
				" controls in the row but only " + 
				columnCount + " columns defined.");
	    }
	else
	    {
            for (int i = 0; i < ctrlCount; i++)
	        {
		field = (JComponent) controls.get(i);
		if ((i > 0) && (i < ctrlCount - 1))
		    {
		    innerPanel = new JPanel(new BorderLayout());
		    outerPanel.add(innerPanel,BorderLayout.EAST);
		    }
		if (i < ctrlCount - 1)
		    {
		    innerPanel.add(field,BorderLayout.WEST);
		    }
		else  // make the last field be east on the inmost JPanel 
		    {
		    innerPanel.add(field,BorderLayout.EAST);
		    }
		outerPanel = innerPanel;
	        }
	    }
	return rowPanel;
	}

      /**
       * Branch of doPanelLayout, lays out a tab group. This
       * is a special case in that we need to create a JTabbedPane,
       * and add each subpanel to it.
       */
    protected void doTabGroupLayout()
        {
	int fullWidth = getSize().width;
	if (bBorderOn) fullWidth -= 20;
	tabbedPane = new JTabbedPane();
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    // we know they are all panels, b/c we would
	    // have otherwise thrown an exception upon creation.
	    DragonPanel panel = (DragonPanel) uiItem;
	    Dimension dim = panel.getPreferredSize();
	    if (panel.isBorderOn())
	         dim.width = fullWidth - 20;
	    else
	         dim.width = fullWidth;
	    panel.setPreferredSize(dim);
	    panel.setSize(dim);
	    tabbedPane.add(panel.getTitle(),panel);
	    }
        add(tabbedPane,BorderLayout.CENTER);
	}

    //********************************************************************
      /** Returns the field object with the specified name. Basically, looks up
       *   the field in the fieldTable. If not found in its own
       *   field table, checks any subtables. This method is used
       *   largely in callback classes.
       * @param  name Name for the field that is being queried by
       *   the caller.
       * @return field object corresponding to name, or null if not found.
       */
    public DragonField getField(String name) 
        {
	DragonField fld = (DragonField) fieldTable.get(name);
	// If we did not get a value, check in any subpanels.
	if (fld == null) 
	    {
	    Enumeration panels = localPanelTable.elements();
	    while ((panels.hasMoreElements()) && (fld == null))
	         {
                 DragonPanel subPanel = (DragonPanel) panels.nextElement();
		 fld = subPanel.getField(name);
		 }
	    }
	return fld;
        }
    
    //********************************************************************
      /** Returns an array of all fields added to this panel, in ordinal
       *   order.
       */
    public DragonField[] getFields() 
        {
	DragonField[] fieldArray = new DragonField[itemCount];
	int fld = 0;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
	        fieldArray[fld++] = (DragonField) uiItem;
		}
	    }
	return fieldArray;
        }


      /** Sets the focus to the first enabled field on the panel.
       */
    public void setFirstFocus() 
        {
	DragonField fld = getFirstField();
	if (fld != null)
	   {
	   fld.requestFocus();
	   }
        }

      /** returns the field which is the first enabled field on the panel.
       */
    public DragonField getFirstField() 
        {
        DragonField foundFld = null;
	DragonField fld = null;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		fld = (DragonField) uiItem;
	        if (fld.isEnabled())
		    {
		    foundFld = fld;
		    break;
		    }
		}
	    }
	return foundFld;
        }

      /** returns the field which is the last enabled field on the panel.
       */
    public DragonField getLastField() 
        {
        DragonField foundFld = null;
	DragonField fld = null;
	for (int i = itemCount-1; i >= 0; i--)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
		fld = (DragonField) uiItem;
	        if (fld.isEnabled())
		    {
		    foundFld = fld;
		    break;
		    }
		}
	    }
	return foundFld;
        }

      /** 
       * Get all fields, both those directly associated with the
       * DragonPanel and those associated with subpanels.
       */
    public Vector getAllFields()
        {
	Vector fields = new Vector(itemCount*2);
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonField)
	        {
	        fields.add(uiItem);
		}
	    else
	        {
		DragonPanel subPanel = (DragonPanel) uiItem;
                Vector subFields = subPanel.getAllFields();
                Iterator subIt = subFields.iterator();
		while (subIt.hasNext())
		     {
                     DragonField fld = (DragonField) subIt.next();
		     fields.add(fld);
		     }
		}
	    }
	return fields;
	}

      /** 
       * Given a field, return the next enabled field in the panel.
       * May wrap to the first field.
       * Used for focus traversal.
       */
    public DragonField getNextEnabledField(DragonField thisField)
        {
        DragonField nextField = null;
        int thisIndex = -1;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if ((uiItem instanceof DragonField) && (uiItem.equals(thisField)))
	        {
	        thisIndex = i;
		break;
		}
	    }
	if (thisIndex >= 0)
	    {
            while ((++thisIndex < itemCount) && (nextField == null))
               {
               Object uiItem = allItems.get(thisIndex);
	       if (uiItem instanceof DragonField)
		   {
                   DragonField dfld = (DragonField) uiItem;
		   if (dfld.isEnabled())
		      nextField = dfld;
                   }
               }
            }
	if (nextField == null)
            nextField = getFirstField();
	return nextField;
        }

      /** 
       * Given a field, return the previous enabled field in the panel.
       * May wrap to the last field.
       * Used for focus traversal.
       */
    public DragonField getPreviousEnabledField(DragonField thisField)
        {
        DragonField prevField = null;
        int thisIndex = -1;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if ((uiItem instanceof DragonField) && (uiItem.equals(thisField)))
	        {
	        thisIndex = i;
		break;
		}
	    }
	if (thisIndex >= 0)
	    {
            while ((--thisIndex >= 0) && (prevField == null))
               {
               Object uiItem = allItems.get(thisIndex);
	       if (uiItem instanceof DragonField)
		   {
                   DragonField dfld = (DragonField) uiItem;
		   if (dfld.isEnabled())
		      prevField = dfld;
                   }
               }
            }
	if (prevField == null)
            prevField = getLastField();
	return prevField;
        }

      /**
       * Return the contents of the panel as a newline delimited
       * list of attribute = value pairs. If a value is null,
       * do not include it.
       */
    public String getAttributeValueList()
        {
        StringBuffer listBuffer = new StringBuffer();
	Vector fields = getAllFields();
	Iterator fldIt = fields.iterator();
	while (fldIt.hasNext())
	    {
	    DragonField fld = (DragonField) fldIt.next();
            if (!(fld instanceof DFixedText))
	        {  
	        String value = fld.getFieldValue();
	        if (value != null)
	            { 
                    listBuffer.append(fld.getName() + "=" + value + "\n");
		    }
		}
	    } 
        return listBuffer.toString();
	}

    //****************************************************************
      /**
       * Enable or disable a tab, by index. If the present
       * panel is not a tab group, search recursively through
       * embedded panels until a tab group is found. If the
       * present DragonPanel does not contain any tabs, this
       * method does nothing.
       * @param tabIndex  Which tab to change
       * @param bEnabled  Flag indicating whether it should be enabled or
       *                    disabled.
       */
    public void enableTab(int tabIndex, boolean bEnabled)
        {
	if ((bTabGroup) && (tabbedPane != null))
	     {
	     tabbedPane.setEnabledAt(tabIndex, bEnabled);
	     Object uiItem = allItems.get(tabIndex);
	     // we know they are all panels, b/c we would
	     // have otherwise thrown an exception upon creation.
	     DragonPanel panel = (DragonPanel) uiItem;
	     panel.setEnabled(bEnabled);
	     }
	else
	     {
	     for (int i = 0; i < itemCount; i++)
	         {
	         Object uiItem = allItems.get(i);
	         if (uiItem instanceof DragonPanel)
		     {
		     DragonPanel subPanel = (DragonPanel) uiItem;
		     subPanel.enableTab(tabIndex, bEnabled);
		     }
		 }
	     }
	}

    //*******************************************************************
      /**
       * Find out, and return the name of, the current datapath
       */
    public String getDpath()
        {
	return ApplicationManager.getReadPath();
	}

    //********************************************************************
      /** * Get/Set Methods
       */

    public void setValidatingAll(boolean bFlag)
        {
	bValidatingAll = bFlag;
	}

    public boolean isValidatingAll()
        {
	return bValidatingAll;
	}

    public void setEnabled(boolean bFlag)
        {
	bEnabled = bFlag;
	}

    public boolean isEnabled()
        {
	return bEnabled;
	}

    public void setBigHelp(boolean bFlag)
        {
	bBigHelp = bFlag;
	}

    public boolean needsBigHelp()
        {
	return bBigHelp;
	}

    public void setColumnCount(int count)
        {
	columnCount = count;
	}

    public int getColumnCount()
        {
	return columnCount;
	}

    public boolean isBorderOn()
        {
	return bBorderOn;
	}

    public boolean isBottom()
        {
	return bBottom;
	}
   
    public void setBottom(boolean bFlag)
        {
	bBottom = bFlag;
	}

    public void setFlowRow(boolean bFlow)
        {
	bFlowRow = bFlow;
	}

    public boolean isFlowRow()
        {
	return bFlowRow;
	}

    public void setPopupDialog(JDialog dlg)
        {
	popupDialog = dlg;
	}

    public JDialog getPopupDialog()
        {
	return popupDialog;
	}

    public void setEnclosingFrame(JFrame frame)
        {
	enclosingFrame = frame;
	}

    public JFrame getEnclosingFrame()
        {
	return enclosingFrame;
	}

    public void setInvokingField(DragonField field)
        {
	invokingField = field;
	}

    public DragonField getInvokingField()
        {
	return invokingField;
	}
    public String getName() 
        {
        return name;
        }
    
    public String getPanelCommand() 
        {
        return panelCommand;
        }

    public void setPanelCommand(String cmd) 
        {
        panelCommand = cmd;
        }
    
    public String getDetailsLink() 
        {
        return detailsLink;
        }

    public void setDetailsLink(String cmd) 
        {
        detailsLink = cmd;
        }
 
    public boolean isPrimary() 
        {
        return bPrimary;
        }
    
    public void setPrimary(boolean bPrimary) 
        {
        this.bPrimary = bPrimary;
        }
    
    public boolean isPopup() 
        {
        return bPopup;
        }
    
    public void setPopup(boolean bPopup) 
        {
        this.bPopup = bPopup;
        }
    
    public boolean isTabbed() 
        {
        return bTabbed;
        }
    
    public void setTabbed(boolean bTabbed) 
        {
        this.bTabbed = bTabbed;
        }

    public boolean isTabGroup() 
        {
        return bTabGroup;
        }
    
    public void setTabGroup(boolean bTabGroup) 
        {
        this.bTabGroup = bTabGroup;
        }
    
    public int getPanelNumber() 
        {
        return panelNumber;
        }
    
    public void setPanelNumber(int panelNumber) 
        {
        this.panelNumber = panelNumber;
        }
    
    public Dimension getPanelSize() 
        {
        return panelSize;
        }
    
    public void setPanelSize(Dimension size) 
        {
        this.panelSize.width = size.width;
        this.panelSize.height = size.height;
        }
    
    public DragonPanel getParentPanel() 
        {
        return parentPanel;
        }
    
    public void setParentPanel(DragonPanel parentPanel) 
        {
        this.parentPanel = parentPanel;
        }
    
    public String getTitle() 
        {
        return title;
        }

    public void setTitle(String title) 
        {
        this.title = title;
	if (titleLabel != null)
	    titleLabel.setText(title);
        }

    public void setDialogTable(Hashtable table)
        {
        dialogTable = table;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setDialogTable(table);
		}
	    }
	}

    public void setPanelTable(Hashtable table)
        {
        panelTable = table;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof DragonPanel)
	        {
		DragonPanel panel = (DragonPanel) uiItem;
		panel.setPanelTable(table);
		}
	    }
	}

    public int getItemCount()
        {
	return itemCount;
	}

    public void setReturnAllTabs(boolean flag)
        {
	bReturnAllTabs = flag;
        }

    public boolean getReturnAllTabs()
        {
	return bReturnAllTabs;
        } 

      /** 
       * Set a flag when preferred size is set, so we
       * can override the default from an external class.
       */
    public void setPreferredSize(Dimension size)
        {
        super.setPreferredSize(size);
	bSizeSet = true;
	}

      //******************************************************
      /**
       * Test driver
       */
    public static void main(String[] args)
        {
	String[] dummy5 = {"","","","",""};
	String[] dummy7 = {"","","","","","",""};
	String[] colorValues = {"Red","Green","Blue","Black","Yellow"};
	String[] colors = {"Rouge","Vert","Bleu","Noir","Jaune"};
	String[] animals = {"Cat","Rabbit","Horse","Whale","Cricket",
			    "Gorilla","Mouse"};
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
   	    {
	    System.out.println("Error setting look and feel");
	    }
	JFrame frame = new JFrame("DragonPanel Test"); 
	DragonPanel dPanel = new DragonPanel("test");
	dPanel.setColumnCount(4);
	dPanel.setPanelCommand("D 1BA");
	DragonField f1 = new DFileField("F1","",20,true,false);
	f1.setLabelText("Name for First file");
	try
	     { 
	     dPanel.addField(f1.makeClone());
	     dPanel.getField("F1").setPSpecifier("-F1");
	     DragonField f2 = new DFileField("F2","",20,false,false);
	     f2.setLabelText("Name for Second File");
	     dPanel.addField(f2.makeClone());
	     dPanel.getField("F2").setPSpecifier("-F2");
	     //dPanel.getField("F2").setEnabled(false);
	     dPanel.getField("F2").setBottom(true);  // should be ignored
	     
	     DragonPanel subPanel = new DragonPanel("sub");
	     
	     subPanel.setBorderOn();
	     // subPanel.setColumnCount(5);
	     DragonField f3 = new DTextField("F3",
					     "",5,false);
	     f3.setLabelText("X");
	     subPanel.addField(f3.makeClone());
	     subPanel.getField("F3").setNewLine(true);
	     subPanel.getField("F3").setPSpecifier("-X");
	     subPanel.getField("F3").setValueLimits(new ValueLimits(0,9999,true));
	     //subPanel.getField("F3").setValidator(new IntegerValidator());
	     
	     DragonField f4 = new DTextField("F4",
					     "Y",5,false);
	     subPanel.addField(f4.makeClone());
	     subPanel.getField("F4").setPSpecifier("-Y");
	     subPanel.getField("F4").setRequired(true);
	     
	     DragonField f5 = new DTextField("F5",
					     "Z",5,false);
	     subPanel.addField(f5.makeClone());
	     subPanel.getField("F5").setPSpecifier("-Z");
	     DragonField f5half = new DTextField("F5half",
						 "W",5,false);
	     subPanel.addField(f5half.makeClone());
	     subPanel.getField("F5half").setPSpecifier("-W");
	     subPanel.getField("F5half").setEnabled(false);
	     /***
	       subPanel.addField(new DTextField("F5.5",
	       "Q",5,false));
	       subPanel.getField("F5.5").setPSpecifier("-Q");
	       ***/
	     subPanel.doPanelLayout();
	     
	     dPanel.addPanel(subPanel);
	     
	     DragonField f6 = new DCheckField("F6",
					      "","Y","N");
	     f6.setLabelText("Log all operations to file?");
	     f6.setPSpecifier("-LOG");
	     f6.setCentered(true);
	     dPanel.addField(f6.makeClone());
	     
	     DragonField fld = new DRadioBox("F10",
					     "",
					     colorValues,dummy5,true);
	     fld.setLabelText("Colors");
	     fld.setChoiceStrings(colors);
	     fld.setPSpecifier("-TC");
	     fld.setNewLine(true);
	     // fld.setEnabled(false);
	     dPanel.addField(fld.makeClone());
	     dPanel.getField("F10").setFieldValue("Green");
	     
	     DragonField f11 = new DComboField("F11",
					       "",animals,
					       null,false);
	     f11.setLabelText("Favorite Animal to have as a Pet");
	     
	     f11.setPSpecifier("-PET");
	     dPanel.addField(f11.makeClone());
	     DragonPanel panel2 = new DragonPanel("buttons");
	     DragonField b1 = new DButtonField("B1","");
	     b1.setLabelText("Show Cmd");
	     panel2.addField(b1.makeClone());
	     //panel2.getField("B1").setCallback(new ExecCmdCallback());
	     panel2.addField(new DButtonField("B2","Exit"));
	     //panel2.getField("B2").setCallback(new ExitCallback());
	     panel2.setFlowRow(true);
	     panel2.setBottom(true);
	     panel2.doPanelLayout();
	     dPanel.addPanel(panel2);
	     dPanel.doPanelLayout();
	     }
	catch (Exception e)
	     {
	     e.printStackTrace();
	     }
	Dimension dim = dPanel.getSize();
	frame.setSize(dim);
	frame.getContentPane().setLayout(new BorderLayout());
	frame.getContentPane().add(dPanel,BorderLayout.CENTER);
	frame.show();
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonPanel.java,v 1.22.2.1 2010/09/10 10:00:32 rudahl Exp $ \n";
	}
    }

// End of DragonPanel.java



