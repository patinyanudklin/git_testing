/* UserStretchCallback.java
 *
 * Copyright  2001-2007  Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 2/20/2001
 *
 * $Id: UserStretchCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: UserStretchCallback.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2001/11/30 18:01:21  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.3  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.2  2001/04/18 15:32:46  goldin
 * Added home directory command line argument
 *
 * Revision 1.1  2001/02/20 18:29:39  goldin
 * Add new callback classes
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;

/** 
 *  This class implements the Callback interface. It has the effect
 *  of displaying the sub-panel for user defined stretch if the user
 *  chooses this option.
 *  of the final DRAGON UI but is useful for testing.
 * @author  goldin*/
public class UserStretchCallback implements Callback 
    {
    
      /** Primary method of a callback class.
       *  Displays the appropriate user stretch subpanel if the
       *  value of the current field is "U".
       * @param  field Field whose value will determine the
       *   effects of the callback.
       */

    public void executeCallback(DragonField field)
        {
	String stretchValue = field.getFieldValue();
	if (stretchValue.startsWith("U"))
	    {
	    String popupId = null;
	      // determine what panel to show
	    String ctrlId = field.getName();
	    if (ctrlId.compareTo("^3HISb") == 0)
	        {
		popupId = "r3STRb";
		}
	    else if (ctrlId.compareTo("^3HISg") == 0)
	        {
		popupId = "r3STRg";
		}
	    else if (ctrlId.compareTo("^3HISr") == 0)
	        {
		popupId = "r3STRr";
		}
	    else 
	        {
		popupId = "rSTR";
	        }
	    DragonPanel parent = field.getParentPanel();
	    parent.setInvoker(popupId,field);
	    parent.showPopup(popupId);
	    }
	}



    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: UserStretchCallback.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

// End of Callback.java

