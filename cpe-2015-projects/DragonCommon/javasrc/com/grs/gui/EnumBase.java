/** EnumBase
*
*   ~~ Copyright  2001-2014  by Sally Goldin and Kurt Rudahl
*   ~~ EndC
*
*   Based on example in "Essential Java Style", by Jeff Langr,
*                        Prentice-Hall, 1999
*
* $Id: EnumBase.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $
* $Log: EnumBase.java,v $
* Revision 1.3.2.1  2015/01/01 13:51:54  rudahl
* consolidating Dragon and OpenDragon
*
* Revision 1.4  2007/07/20 03:53:35  goldin
* Get rid of unchecked operation warnings by parameterizing collections
*
* Revision 1.3  2007/01/05 07:41:58  rudahl
* added Whatis info
*
* Revision 1.2  2005/02/06 08:08:11  goldin
* Fix JavaDoc warnings
*
* Revision 1.1  2001/11/27 16:49:10  goldin
* Move XMLTag and EnumBase to general Gui package
*
* Revision 1.3  2001/11/05 13:59:15  goldin
* Put UI code in a package
*
* Revision 1.2  2001/04/18 15:32:46  goldin
* Added home directory command line argument
*
* Revision 1.1  2001/01/16 17:50:30  goldin
* Began implemenation of XML parsing to create UI
* 
*/

package com.grs.gui;
import java.util.List;
import java.util.ArrayList;

/**
 * This is a base class for defining classes of enumerated
 * constants, which will enforce the usage of only
 * defined constants at compile time rather than run time.
 * <p>
 * To create an enumerated class, extend this class.
 * Create a private constructor that calls the superclass
 * constructor. Then define a set of static final instances
 * of the class, with desired values and symbolic names.
 * <p>*/
public class EnumBase
    {
    protected static int numberOfConstants = 0;
    protected static List<EnumBase> list = new ArrayList<EnumBase>();

    private int ordinal; // order in list. Starts with 0.  
    private String name;

    protected EnumBase(String _name)
        {
	name = _name;
	ordinal = numberOfConstants++;
	list.add(this);
	}

    public String toString()
        {
	return name;
        }

    public int getOrdinal()
        {
	return ordinal;
        }

    public static EnumBase get(int searchOrdinal)
        {
	return (EnumBase) list.get(searchOrdinal);
	}

    public static int size()
        {
	return numberOfConstants;
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: EnumBase.java,v 1.3.2.1 2015/01/01 13:51:54 rudahl Exp $ \n";
	}
    }
 
