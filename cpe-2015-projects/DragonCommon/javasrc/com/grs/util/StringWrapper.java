/*
 * StringWrapper.java
 *
 * ~~ Copyright 2002-2014 by Sally Goldin & Kurt Rudahl
 * ~~ EndC
 *
 * Created by Sally Goldin, 1/4/2002
 *
 * $Id: StringWrapper.java,v 1.4.4.1 2015/01/01 13:51:54 rudahl Exp $
 * $Log: StringWrapper.java,v $
 * Revision 1.4.4.1  2015/01/01 13:51:54  rudahl
 * consolidating Dragon and OpenDragon
 *
 * Revision 1.4  2005/12/27 10:41:06  goldin
 * Refine to take account of break strings in wrapAsHtml
 *
 * Revision 1.3  2005/12/24 12:39:03  goldin
 * Create 'verbose' variant of radio boxes
 *
 * Revision 1.2  2005/02/06 08:13:07  goldin
 * Fix javadoc warnings
 *
 * Revision 1.1  2002/01/04 14:48:40  goldin
 * Add new utility class to do word wrap
 *
 *
 */
package com.grs.util;
import java.util.*;

/**
 * This class is just a single static method 
 * that can be used to insert newlines into a string in
 * order to wrap it into a maximum of a specified 
 * number of chars per line.
 */
public class StringWrapper 
  {


    /**
     * Word wrap a string into lines with a maximum of 
     * maxLineChars (not including the line terminator)
     * Assumes spaces delimit all words.
     * @param inString  String to wrap
     * @param maxLineChars  Max number of chars to allow per line
     * @return String with inserted newline to mark line breaks
     */
  public static String wrap(String inString, int maxLineChars) 
     {
     int length = inString.length();
     int currentLineSize = 0;
     StringBuffer buffer = new StringBuffer(length +
					   (length/maxLineChars)*2);
     StringTokenizer tokenizer = new StringTokenizer(inString," ");
     while (tokenizer.hasMoreTokens())
         {
	 String word = tokenizer.nextToken();
	 if ((currentLineSize + word.length() + 1) > maxLineChars)
	     {
	     buffer.append("\n");
	     buffer.append(word + " ");
	     currentLineSize = word.length() + 1;
	     }
	 else
	     {
	     buffer.append(word + " ");
	     currentLineSize += word.length() + 1;
	     }
	 }
     return buffer.toString();
     }

    /**
     * Word wrap a string into lines with a maximum of 
     * maxLineChars (not including the line terminator)
     * Assumes spaces delimit all words. Embed in an HTML context
     * so we can use in a label.
     * @param inString  String to wrap
     * @param maxLineChars  Max number of chars to allow per line
     * @return String with inserted newlines or other delimiter string to mark line breaks
     */
  public static String wrapAsHtml(String inString, int maxLineChars) 
     {
     int length = inString.length();
     int currentLineSize = 0;
     StringBuffer buffer = new StringBuffer(length +
					   (length/maxLineChars)*2);
     buffer.append("<html>");
     StringTokenizer tokenizer = new StringTokenizer(inString," ");
     while (tokenizer.hasMoreTokens())
         {
	 String word = tokenizer.nextToken();
	 if (word.equalsIgnoreCase("<br>"))  /* treat like line break */
	     {
	     buffer.append(word);
	     currentLineSize = 0;
	     }
	 else if ((currentLineSize + word.length() + 1) > maxLineChars)
	     {
	     buffer.append("<br>");
	     buffer.append(word + " ");
	     currentLineSize = word.length() + 1;
	     }
	 else
	     {
	     buffer.append(word + " ");
	     currentLineSize += word.length() + 1;
	     }
	 }
     buffer.append("</html>");
     return buffer.toString();
     }


    /**
     * Test Driver - string to wrap and width are cmd line args
     */
  public static void main(String args[])
      {
      if (args.length < 2)
	  {
	  System.out.println("USAGE: StringWrapper <string> <maxChars>");
	  System.exit(0);
	  }
      String result = wrap(args[0],Integer.parseInt(args[1]));
      System.out.println("Wrapped Result +++++++++++++");
      System.out.println(result);
      }
  }
  

