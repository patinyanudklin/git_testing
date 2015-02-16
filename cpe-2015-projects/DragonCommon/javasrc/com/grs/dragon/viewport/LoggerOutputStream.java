//***************************************************************
//
//          LoggerOutputStream.java - extend OutputStream to send to C++
//			 K.T. Rudahl
//
//          Copyright 2001 by Goldin-Rudahl Associates
//                            P.O. Box 9648
//                            North Amherst, MA 01059 U.S.A.
//***************************************************************
//
//   $Id: LoggerOutputStream.java,v 1.4 2001/11/16 17:16:59 rudahl Exp $
//   $Log: LoggerOutputStream.java,v $
//   Revision 1.4  2001/11/16 17:16:59  rudahl
//   removed some tracing
//
//   Revision 1.3  2001/11/16 12:23:43  goldin
//   try fixing loggeroutputstream
//
//   Revision 1.2  2001/11/15 20:47:03  rudahl
//   moved viewport java files to their own package
//
//   Revision 1.1  2001/11/12 14:58:24  rudahl
//   initial deposit, but it doesn't work right
//
//
//***************************************************************
package com.grs.dragon.viewport;

import java.util.*;
import java.io.*;

public class LoggerOutputStream extends OutputStream
    {
    protected StringBuffer czCurrent = null;

    public void write(byte[] b,int off, int len)
        {
	  //viewProg.logViewport("LoggerOutputStream3 write1 appending "+b);
	if (czCurrent == null)
	    czCurrent = new StringBuffer(1024);
	czCurrent.append(new String(b,off,len));
        }
    public void write(int b)
        {
	  //viewProg.logViewport("LoggerOutputStream3 write2 appending "+b);
	if (czCurrent == null)
	    czCurrent = new StringBuffer(1024);
        char cc[] = new char[1];
	cc[0] = (char) b;
	czCurrent.append(new String(cc));
        }
    public void write(byte[] b)
        {
	  //viewProg.logViewport("LoggerOutputStream3 write3 appending "+b);
	if (czCurrent == null)
	    czCurrent = new StringBuffer(1024);
	czCurrent.append(new String(b));
        }

    public void flush()
        {
	if (czCurrent != null)
	    viewProg.logViewport(
               "LoggerOutputStream flushing "+czCurrent.toString());
	czCurrent = null;
	}

    public void close()
        {
	flush();
	}
    }

