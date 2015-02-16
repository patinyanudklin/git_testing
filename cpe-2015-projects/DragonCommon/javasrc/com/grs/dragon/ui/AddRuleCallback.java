/**
 * AddRuleCallback.java
 *
 *
 *    Callback to handle adding a rule to the rules list box in the
 *    Rule Creation operation.
 *
 *	Copyright 2007  Global Software Institute
 *			and King Mongkut's University of Technology Thon Buri
 *
 *	All rights are reserved. Copying or other reproduction of
 *	this program except for archival purposes is prohibited
 *	without the prior written consent of Goldin-Rudahl Associates.
 *
 *			  RESTRICTED RIGHTS LEGEND
 *    
 *	Use, duplication, or disclosure by the U.S. Government
 *	is subject to restrictions as set forth in
 *	paragraph (b) (3) (B) of the Rights in Technical
 *	Data and Computer Software clause in DAR 7-104.9(a).
 *
 *	The moral right of the copyright holder is hereby asserted
 *
 * $Id: AddRuleCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $
 * $Log: AddRuleCallback.java,v $
 * Revision 1.4  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.3  2007/01/02 13:06:21  goldin
 * minor modification to rule panel behavior
 *
 * Revision 1.2  2007/01/02 05:19:19  goldin
 * Complete behavioral code for Rule Creation panel
 *
 * Revision 1.1  2007/01/01 13:53:55  goldin
 * Added panel for rule creation
 *
 *
 */
package com.grs.dragon.ui;
import com.grs.gui.*;
import com.grs.dragon.common.*;
import java.io.File; 
import java.awt.*;
import javax.swing.*;

/** 
 *  This class implements the Callback interface. It handles the
 *  retrieval of rule limits from other fields in the panel,
 *  then formatting them and adding them to the list box which
 *  invoked the callback.
 */
public class AddRuleCallback implements Callback
    {
    static protected String clauseFields[] = 
      {"^B1R","^B2R","^B3R","^B4R","^B5R","^B6R",
      "^B7R","^B8R","^B9R","^B10R","^B11R","^B12R"};


      /** Primary method of a callback class.
       *  Gets the rule data from the upper fields and formats
       *  into a new line for the list box.
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */
    public void executeCallback(DragonField field)
        {
        DragonPanel parent = field.getTopLevelPanel();
	if (parent == null)
	    return;
        StringBuffer ruleBuffer = new StringBuffer();
        int clauseCount = countRuleClauses(parent);
        if (clauseCount == 0)
            {
	    // show a message  
	    MessageDisplay mDisplay = ApplicationManager.getMessageDisplay();
	    String title = ApplicationManager.getTextSource().getI18NText(
					  TextKeys.WARNING,"Warning");
	    String msg = ApplicationManager.getTextSource().getI18NText(
					  "%m10000.5","Empty rule");
	    mDisplay.showWarning(title,msg);
            }
        else
            {
	    DragonField outputFld = parent.getField("^VR");
	    if (outputFld != null)
		{
		ruleBuffer.append(outputFld.getFieldValue() + " IF ");
		}
            clauseCount = 0;
	    for (int band = 0; band < 12; band++)
		{
		DragonField fld = parent.getField(clauseFields[band]);
		if (fld != null)
		    {
                    String clause = generateRuleClause(
			       fld.getFieldValue(),band+1);
                    if (clause != null)
                        { 
		        if (clauseCount > 0)
			    ruleBuffer.append(" & ");
			ruleBuffer.append(clause);
                        clauseCount++;
			}
                    } 
		}
	    DListBox listBox = (DListBox) field;
	    listBox.addEntry(ruleBuffer.toString());
            resetClauseDefaults(parent);
	    }
	}

	/* Create a formatted clause to add to the
         * rule being created.
         * @param range  String in the form of "lower-upper"
         * @param band   Which band number (1-12)
         * @return string in the form "(lower <= Bband <= upper)"
         *         However, if lower is 0 and upper is 66536, return
         *            null (we don't want to add redundant clauses)
	 */
    protected String generateRuleClause(String range, int band) 
        {
	    StringBuffer buffer = new StringBuffer();
	int min = 0;
	int max = 65536;
	int pos = range.indexOf("-");
        if (pos > 0)
	    {
            min = Integer.parseInt(range.substring(0,pos));
            }
	if (pos < range.length() - 1)
            {
	    max = Integer.parseInt(range.substring(pos+1));
            }
        if ((min > 0) || (max < 65536))
            {
	    buffer.append("(" + String.valueOf(min) + " <= ");
	    buffer.append("B" + String.valueOf(band) + " <= ");
	    buffer.append(String.valueOf(max) + ")");
	    return buffer.toString();
	    }
	else
	    {
	    return null;
	    }
        }

	/* Count how many non-empty clauses there are in the
         * current rule.
         * @param parent Parent panel,needed to access fields
         * @return number of non-empty clauses. 
	 */
    protected int countRuleClauses(DragonPanel parent) 
        {
	int clauseCount = 0;
	for (int band = 0; band < 12; band++)
	    {
	    DragonField fld = parent.getField(clauseFields[band]);
	    if (fld != null)
		{
                String range = fld.getFieldValue();
        	int min = 0;
        	int max = 65536;
         	int pos = range.indexOf("-");
		if (pos > 0)
		    {
		    min = Integer.parseInt(range.substring(0,pos));
		    }
		if (pos < range.length() - 1)
		    {
		    max = Integer.parseInt(range.substring(pos+1));
		    }
		if ((min > 0) || (max < 65536))
		    clauseCount = clauseCount + 1;
		}
	    }
	return clauseCount;
        }

	/* Set all the clauses back to the default range,
	 * and set the result value back to zero.
         * @param parent Parent panel,needed to access fields
	 */
    protected void resetClauseDefaults(DragonPanel parent) 
        {
	for (int band = 0; band < 12; band++)
	    {
	    DragonField fld = parent.getField(clauseFields[band]);
	    if (fld != null)
		{
		fld.setFieldValue(fld.getDefaultValue());
		}
	    }
	DragonField outputFld = parent.getField("^VR");
	if (outputFld != null)
	    {
	    outputFld.setFieldValue(outputFld.getDefaultValue());
	    }
        }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: AddRuleCallback.java,v 1.4 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

