/** Generic string parsing fns
 *  All methods are static
 *
 * kurt rudahl 10/29/2001
 * ~~ Copyright Kurt Rudahl 2001-2014
 * ~~ EndC
 *
 ************************************************************************
 * $Id: Parse.java,v 1.3.4.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: Parse.java,v $
 * Revision 1.3.4.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.3  2002/01/10 22:31:15  rudahl
 * fixed error with quoted arg
 *
 * Revision 1.2  2001/11/01 18:08:33  rudahl
 * enhanced, fixed namevalue parsing
 *
 * Revision 1.1  2001/10/31 21:00:32  rudahl
 * extracted from StripChart
 *
 *
 ************************************************************************
 * history 10/29/2001   created by extracting from StripChart
 */

package com.grs.util;

import java.awt.*;
import java.util.*;
import java.applet.*;

public class Parse
    {
	/** parse a string into an array of tokens
	 *  @param  czStr  string to parse
	 *  @param  czSep  token-separating string
	 *  @return        array containing elements
	 *                 or null if czStr is null.
	 */
    public static String[] getParamValues(String czStr,String czSep)
        {
	String[] retval = null;
	if (czStr == null)
	    return null;
	try
	    {
	    StringTokenizer tr = new StringTokenizer(czStr,czSep);

	    String[] temp = new String[tr.countTokens()];
	    int i=0;
	    boolean bQuotes = false;
	    while(tr.hasMoreTokens())
		{
		String s  = tr.nextToken();
		if (bQuotes)
		    {
		    if (s.endsWith("\""))
		        {
			temp[i++] += " "+s.substring(0,s.length()-1);
			bQuotes = false;
			}
		    else
		        temp[i] += " "+s;
		  }
		else if (s.startsWith("\""))
		    {
		    if (s.endsWith("\""))
		        temp[i++] = s.substring(1,s.length()-2);
		    else
		        {
		        temp[i] = s.substring(1);
			bQuotes = true;
			}
		    }
		else
		    temp[i++] = s;
		}
	    /* want to return an array which has the exact number of elements 
	     * required (i.e. retval.length == #tokens found), so copy temp
	     */
	    retval = new String[i];
	    while (i-- > 0)
	        retval[i] = temp[i];
	    }
	catch(NoSuchElementException e) {} /* just the end of the list */
	catch(Exception e)
	    { 
	    System.out.println("Exception e "+e.getMessage());
	    }
	return retval;
	} 

	/** return values from a PARAM tag named 'czName'
	 *  @param  czName name attribute in PARAM element
	 *  @param  czSep  token-separating string
	 *  @param  applet Applet associated with the named PARAM
	 *  @return        array containing elements
	 *                 If named PARAM cannot be found, return null
	 */
    public static String[] getParamValues(String czName, String czSep,
					  Applet applet)
        {
	String czValue = applet.getParameter(czName);
	return getParamValues(czValue,czSep);
	}

	/** parse a string into an array of tokens represending Name=Value 
	 *  pairs. The values may be quoted; the quotes are removed.
	 *  @param  czStr  string to parse
	 *  @param  czSep  string which separates Name=Value pairs
	 *  @param  hash   existing Hashtable which is modified with new values
	 *                 (nothing is removed)
	 *  @return        Hashtable containing elements 
	 *		   or null if czStr is null.
	 */
    public static Hashtable<String,String> getParamNameValues(String czStr,String czSep,
							       Hashtable<String,String> hash)
       throws Exception
        {
	if ((czStr == null) || (czStr.length() < 3)) /* min string: 'a=b' */
	    return null;
	int iStartPos = 0;
	int iDelimPos = czStr.indexOf('=');
	int iEndPos = czStr.indexOf(0x1A);
	while(iDelimPos > 0)
	    {
	    if ((iDelimPos < 0) || (iStartPos < 0))
	        throw new Exception("Parse: Invalid line: "+czStr);
	    int iNextPos = czStr.indexOf(czSep,iStartPos+1);
	    boolean bQuoted = czStr.substring(iDelimPos+1).startsWith("\"");
	    String czName = czStr.substring(iStartPos,iDelimPos).trim();
	    if (bQuoted)
	        {
		iDelimPos++;
		iNextPos = czStr.indexOf("\"",iDelimPos+1);
	        }
	    String czVal = (iNextPos > iDelimPos)
	        ? czStr.substring(iDelimPos+1,iNextPos) 
	        : czStr.substring(iDelimPos+1);
	    /* if name supplied but value=="", remove hash entry */
	    if (czVal.trim().length() > 0)
	        hash.put(czName,czVal.trim());
	    else if (hash.containsKey(czName))
	        hash.remove(czName);
	    if ((iNextPos > 0) && (czStr.charAt(iNextPos) == '"'))
	        iNextPos++; /* point to delim not quote */
	    iStartPos = iNextPos;
	    if (iStartPos < 0)
	        break;
	    iDelimPos = czStr.indexOf('=',iStartPos);
	    }
	return hash;
	} 

	/** parse a string into an array of tokens represending Name=Value 
	 *  pairs. The values may be quoted; the quotes are removed.
	 *  @param  czStr  string to parse
	 *  @param  czSep  string which separates Name=Value pairs
	 *  @return        Hashtable containing elements 
	 *		   or null if czStr is null.
	 */
    public static Hashtable getParamNameValues(String czStr,String czSep)
       throws Exception
        {
	Hashtable<String,String> retval = new Hashtable<String,String>();
	return getParamNameValues(czStr,czSep,retval);
	} 
                                          
    }
