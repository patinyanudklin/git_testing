/* Smallfile.java
 * class which mimics rsf, wsf in wfutl
 * kurt rudahl 7/30/01
 * ~~ Copyright Kurt Rudahl 2001-2014
 * ~~ EndC
 *
 * $Id: Smallfile.java,v 1.2.4.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: Smallfile.java,v $
 * Revision 1.2.4.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.2  2001/11/01 18:08:05  rudahl
 * added rsf
 *
 * Revision 1.1  2001/10/31 21:01:03  rudahl
 * moved here from help/edit, and significantly reworked
 *
 * Revision 1.1  2001/07/30 19:50:39  rudahl
 * all the Dragon msgs now use unicode
 *
 *  history:
 *    7/2001    ktr   created
 *   10/31/2001 ktr   moved to com.grs.util package;
 *                    methods converted to be static
 */

package com.grs.util;

import java.util.*;
import java.text.*;
import java.io.*;

public class Smallfile
    {
    protected static long g_rsfPosition = -1;
    protected static String g_rsfName = null;

    public static void wsf(String czName, String czContents, boolean bAppend,
			   String czEncoding)  throws IOException
        {
	BufferedWriter outp;
	FileOutputStream fs = new FileOutputStream(czName,bAppend);
	if (czEncoding != null)
	    outp = new BufferedWriter(new OutputStreamWriter(fs,czEncoding));
	else
	    outp = new BufferedWriter(new OutputStreamWriter(fs));
	outp.write(czContents);
	outp.close();
	}

	 /* read all lines from file
	  * @param czName       name of file
	  * @param czEncoding   null, or encoding within file
	  * @return             Vector of Strings
	  */
    public static Vector rsf(String czName, String czEncoding)
	     throws IOException
        {
	Vector<String> retval = new Vector<String>();
	BufferedReader inp;
	if (czEncoding != null)
	    {
	    FileInputStream fs = new FileInputStream(czName);
	    inp = new BufferedReader(new InputStreamReader(fs,czEncoding));
	    }
	else
	    inp = new BufferedReader(new FileReader(czName));
	String in = inp.readLine();
	while(in != null)
	    {
	    retval.addElement(in);
	    in = inp.readLine();
	    }
	return retval;
	}

	 /* read line from file
	  * @param czName       name of file
	  * @param iLineNum     0-based index of line within file, or
	  *                     -1 => 'next' line
	  *                     (to use -1, must never have used >0 lineno)
	  * @param czEncoding   null, or encoding within file
	  * @return             text line or null at eof
	  */
    public static String rsfgets(String czName, int iLineNo, String czEncoding)
	     throws IOException
        {
	BufferedReader inp;
	if (czEncoding != null)
	    {
	    FileInputStream fs = new FileInputStream(czName);
	    inp = new BufferedReader(new InputStreamReader(fs,czEncoding));
	    }
	else
	    inp = new BufferedReader(new FileReader(czName));
	String in = null;
	if (iLineNo == 0)
	       {
	       g_rsfPosition = 0;
	       g_rsfName = czName;
	       }
	else if (iLineNo > 0)
	       {
	       for (int i=0; i<iLineNo; i++)
		   if (inp.readLine() == null)
		       break;
	       }

	if (iLineNo < 0)
	       {
	       inp.skip(g_rsfPosition);
	       char fred[] = new char[1024];
	       inp.read(fred);
	       int offset=0;
	       int count=0;
	       for (int i=0; i<1024; i++)
		   {
		   boolean bIsCntrl = Character.isISOControl(fred[i]);
		   //   System.out.println("pre char value is "+(int)fred[i]);
	       	   if ((count==0) && bIsCntrl)
		       offset++;
		   else if (!bIsCntrl)
		       count++;
		   else
		       break;
		   }
	       g_rsfPosition += offset + count;
	       if (count > 0)
		   in = new String(fred,offset,count);
	       }
	else
	    in = inp.readLine();
	if ((in != null) && (iLineNo == 0) && (g_rsfPosition >= 0))
	    g_rsfPosition += in.length();
	inp.close();
	return in;
	}

    public static String rsfgets(String czName, int iLineNo)
	     throws IOException
        {
	return rsfgets(czName,iLineNo,null);
	}
    }
