/* PanelInfo.java
 *
 * ~~ Copyright 2002-2015 Goldin-Rudahl Associates
 * ~~ EndC
 *
 *  Created by Sally Goldin, 6/26/2002
 *
 * $Id: PanelInfo.java,v 1.3 2015/01/01 08:37:11 rudahl Exp $
 * $Log: PanelInfo.java,v $
 * Revision 1.3  2015/01/01 08:37:11  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.2  2007/07/30 09:12:18  goldin
 * Get rid of unchecked warnings
 *
 * Revision 1.1  2002/06/26 19:23:54  goldin
 * Initial implementation of classes to generate Dragon details HTML file for ManReader
 *
 *
 */

package com.grs.dragon.manReader.detailXml;
import java.util.*;

/** 
 *  This class is a data object which holds information about
 *  a Dragon screen/response panel. It is used to accumulate
 *  information from the panel XML file which is then used
 *  to generate the ddetail.html file for the ManReader.
 *  This class has no significant behavior, just data and
 *  accessor methods.
 */

public class PanelInfo
    {
      /**
       * Ordered list of all fields and subpanels.
       */
    protected ArrayList<Object> allItems = new ArrayList<Object>(30);

      /** If true, this is a primary panel, i.e. a top-level
       *   DRAGON response panel. A primary panel
       *   cannot be a tabbed panel (i.e. bTabbed must
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
    
      /** Table mapping field names to FieldInfo object instances;
       *   populated during construction of panel
       */
    protected Hashtable<String,FieldInfo>  fieldTable = 
              new Hashtable<String,FieldInfo>();
    
      /** Counts the number of fields and panels added to the
       *   panel so far.
       */
    protected int itemCount = 0;
    
      /** Unique name for the panel as a whole
       */
    protected String name;
    
      /** Command that is implemented by this panel, e.g.
       *   "3BA". Will be empty for panels that have only local
       *   effects, such as the logging panel.
       */
    protected String panelCommand = null;

      /**
       * String used to construct link to details. This will
       * be the command unless that is ambiguous,e.g. for LIS
       */
    protected String detailsLink = null;
    

      /**
       * Title or label for the panel. 
       */
    protected String title = null;

      /** Integer indicating the order in which this panel
       *   was added to its parent panel. This is within the
       *   same ordinal sequence as the fields, i.e. if a panel
       *   was added after field 2 , it would have a panelNumber of
       *    3
       */
    protected int panelNumber;
    
      /** Table of all panels added to the current panel,
       *   keyed by name.
       */
    protected Hashtable<String,PanelInfo> localPanelTable = 
           new Hashtable<String,PanelInfo>();
    
    
    //********************************************************************
      /** 
       * Constructor takes name of the panel as an argument.
       */
    public PanelInfo(String panelName)
        {
	name = panelName;
	}

      /** Adds a field to the set maintained by the panel. Marks
       *   the field with an ordinal indicating the order in which
       *   it was added.
       * @param  field Field object to be added to the set of
       *   those managed by the panel.
       */
    public void addField(FieldInfo field)
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
	allItems.add(field);
        }
    
    //********************************************************************
      /** Adds a subpanel to the layout of another panel.
       *   The ordinal will be used to determine where in
       *   the panel the subpanel should appear.
       * @param  panel Panel to add to the layout being processed.
       */
    public void addPanel(PanelInfo panel) throws Exception 
        {
        if ((bTabGroup) && (!panel.isTabbed()))
	    {
	    throw new Exception("Error constructing tab group panel " +
		name + "; child panels must all be of type tabbed.");
	    }
	panel.setPanelNumber(itemCount);
	itemCount++;
	localPanelTable.put(panel.getName(),panel);
	allItems.add(panel);
        }
    

    //********************************************************************
      /** Returns the field object with the specified name. Basically, looks up
       *   the field in the fieldTable. If not found in its own
       *   field table, checks any subtables. This method is used
       *   largely in callback classes.
       * @param  name Name for the field that is being queried by
       *   the caller.
       * @returns field object corresponding to name, or null if not found.
       */
    public FieldInfo getField(String name) 
        {
	FieldInfo fld = (FieldInfo) fieldTable.get(name);
	// If we did not get a value, check in any subpanels.
	if (fld == null) 
	    {
	    Enumeration<PanelInfo> panels = localPanelTable.elements();
	    while ((panels.hasMoreElements()) && (fld == null))
	         {
                 PanelInfo subPanel = (PanelInfo) panels.nextElement();
		 fld = subPanel.getField(name);
		 }
	    }
	return fld;
        }
    
    //********************************************************************
      /** Returns an array of all fields added to this panel, in ordinal
       *   order.
       */
    public FieldInfo[] getFields() 
        {
	FieldInfo[] fieldArray = new FieldInfo[itemCount];
	int fld = 0;
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof FieldInfo)
	        {
	        fieldArray[fld++] = (FieldInfo) uiItem;
		}
	    }
	return fieldArray;
        }


      /** 
       * Get all fields, both those directly associated with the
       * PanelInfo and those associated with subpanels.
       */
    public Vector<FieldInfo> getAllFields()
        {
	Vector<FieldInfo> fields = new Vector<FieldInfo>(itemCount*2);
	for (int i = 0; i < itemCount; i++)
	    {
	    Object uiItem = allItems.get(i);
	    if (uiItem instanceof FieldInfo)
	        {
	        fields.add((FieldInfo)uiItem);
		}
	    else
	        {
		PanelInfo subPanel = (PanelInfo) uiItem;
                Vector<FieldInfo> subFields = subPanel.getAllFields();
                Iterator<FieldInfo> subIt = subFields.iterator();
		while (subIt.hasNext())
		     {
                     FieldInfo fld = (FieldInfo) subIt.next();
		     fields.add(fld);
		     }
		}
	    }
	return fields;
	}


    //********************************************************************
      /** * Get/Set Methods
       */

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
    
    public String getTitle() 
        {
        return title;
        }

    public void setTitle(String title) 
        {
        this.title = title;
        }

    public int getItemCount()
        {
	return itemCount;
	}

    }

// End of PanelInfo.java









