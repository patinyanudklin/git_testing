/*  
 *    StripChart.java is a simple java applet that provides a strip chart
 *    capability
 *
 * BY:  Kurt Rudahl
 * $Id: StripChart.java,v 1.7 2001/11/17 21:27:41 rudahl Exp $
 * $Log: StripChart.java,v $
 * Revision 1.7  2001/11/17 21:27:41  rudahl
 * improvements for StripChart which is now in jar
 *
 * Revision 1.6  2001/11/04 19:10:01  rudahl
 * added non-working labelling of mult graphs
 *
 * Revision 1.5  2001/11/01 09:57:54  rudahl
 * added GriddedPlaneSpace.java Makefile GriddedPlaneSpace.java
 *
 * Revision 1.4  2001/10/29 20:21:14  rudahl
 * refined calling params and documentation
 *
 * Revision 1.3  2001/10/29 15:22:41  rudahl
 * clean out deadwood
 *
 * Revision 1.2  2001/10/29 13:17:41  rudahl
 *  fixed bugs in drawing fn params
 *
 * Revision 1.1  2001/10/27 19:19:41  rudahl
 * first deposit - from closet
 *
 * Revision 1.1  2001/10/22 08:15:27  rudahl
 * initial deposit - needs to be revised & refactored
 * 
 */

import java.awt.*;
import java.util.*;
import com.grs.metricCanvas.*;
import com.grs.util.*;

/** Applet to display a strip chart of data in the HTML file <PARAM> 
 *  statements.
 */
public class StripChart extends java.applet.Applet implements Runnable
    {
    Thread runner;   // thread to produce the animation
    Image OSC;  // the off-screen canvas
   
    public void start()
	{
	if (runner == null)
	    {
            runner = new Thread(this);
            runner.start();
	    }
	}
   
    public void stop()
        {
        if (runner != null) 
	    {
            runner.stop();
	    runner = null;
	    }
	}
    
    public void paint(Graphics g)
	{  // paint method just copies canvas to applet
        if (OSC != null)
            g.drawImage(OSC,0,0,this);
	}
   
    public void update(Graphics g)
	{   // replace standard update method so it doesn't
	    // erase the screen
	paint(g);
	}

    public void run()
        {        // run method for animation thread
	int w = size().width;   // get the width and height of the applet
	int h = size().height;
	OSC = createImage(w,h);  // create an off screen canvas of the same size
	Graphics g = OSC.getGraphics();   // a graphics context for drawing to canvas

	/* 'paramList' is a list of other param names in HTML file.
	 *  Of these, the first is a global chart configuration PARAM
	 *    with known structure.
	 *  Next are the optional verticalAxis and horizontalAxis records
	 *  Remaining ones are pairs corresponding to data sets to be plotted:
	 *    of each pair, the first has known structure 
	 *    and the second is a list of data values
	 */
	String[] czParamList = Parse.getParamValues("paramList",",",this);
	System.err.println("got paramList length="+czParamList.length);
	if ((czParamList == null) || (czParamList.length < 1))
	    return;
	/* 'chartConfig' values are, in order
	 *   style, which is 'histogram', 'line', 'point', ...
	 *   logical width of the data region of the graph
	 *          (i.e. the positive range of X)
	 *   logical height of the data region (i.e. the positive range of Y) 
	 *   optionally, quadrants: 1Q => X,Y >= 0; 2Q => X >= 0, or 4Q
	 *     default is 1Q, and others not yet implemented ~~
	 */
	String[] czChartConfig = Parse.getParamValues(czParamList[0],",",this);
	if ((czChartConfig == null) || (czChartConfig.length < 3))
	    return;
	String czChartType = czChartConfig[0];
	int iDataWidth = Integer.parseInt(czChartConfig[1]);
	int iDataMin = Integer.parseInt(czChartConfig[2]);
	int iDataMax = Integer.parseInt(czChartConfig[3]);
	int iFirstDataSetRecord=1;
	/* 'verticalAxis' and 'horizontalAxis' have, if present,
	 *  first a data offset where the axis line should be drawn
	 *  then successive pairs each consisting of
	 *    a label, and a graph value where that label should be placed
	 */
	double[] xAxisVals = null;
	double[] yAxisVals = null;
	String[] xAxisLabels = null;
	String[] yAxisLabels = null;
	if (czParamList[iFirstDataSetRecord].equals("verticalAxis"))
	    {
	    String[] czVertAxis 
	        = Parse.getParamValues(czParamList[iFirstDataSetRecord],
				       ",",this);
	    if ((czVertAxis != null) && (czVertAxis.length > 0))
		{
		yAxisVals = new double[czVertAxis.length/2];
		yAxisLabels = new String[czVertAxis.length/2];
		for (int iH=1; iH<czVertAxis.length-1; iH += 2)
		    {
		    int iVLoc = Integer.parseInt(czVertAxis[iH+1]);
		    yAxisVals[(iH-1)/2] = iVLoc;
		    yAxisLabels[(iH-1)/2] = czVertAxis[iH];
		    }
		}
	    iFirstDataSetRecord++;
	    }
	if (czParamList[iFirstDataSetRecord].equals("horizontalAxis"))
	    {
	    String[] czHorizAxis 
	      = Parse.getParamValues(czParamList[iFirstDataSetRecord],
				     ",",this);
	    if ((czHorizAxis != null) && (czHorizAxis.length > 0))
		{
		xAxisVals = new double[czHorizAxis.length/2];
		xAxisLabels = new String[czHorizAxis.length/2];
		for (int iH=1; iH<czHorizAxis.length-1; iH += 2)
		    {
		    int iHLoc = Integer.parseInt(czHorizAxis[iH+1]);
		    xAxisVals[(iH-1)/2] = iHLoc;
		    xAxisLabels[(iH-1)/2] = czHorizAxis[iH];
		    }
		}
	    iFirstDataSetRecord++;
	    }
	g.setColor(Color.black);
	g.fill3DRect(0,0,w,h,true);
	g.setColor(Color.green);
	int iTitleHeight = 20 * (czParamList.length - iFirstDataSetRecord)/2; 
	/* Plot origin w.r.t. bottom of display window */
	int iMargin = 5;
	int iXOrigin = 30 + iMargin;
	int iYOrigin = 20 + iMargin + iTitleHeight;

	try
	    {
	    g.setColor(Color.yellow);
  	    Ruler rx 
		= new Ruler(g,null,0,iDataWidth,
			    new Dimension(size().width-iXOrigin-iMargin,20),
			    new Dimension(iXOrigin,
					  -(size().height-(iYOrigin-20))),
			    Ruler.X_AXIS,0, xAxisVals,xAxisLabels,0.30);
  	    Ruler ry 
		= new Ruler(g,null,0,iDataMax-iDataMin,
			    new Dimension(iXOrigin-iMargin,
					  size().height-iYOrigin-iMargin),
			    new Dimension(iMargin,-(size().height-iYOrigin)),
			    Ruler.Y_AXIS,0, yAxisVals,yAxisLabels, 0.15);
	    }
	catch (Exception e)
	    {
	    e.printStackTrace();
	    }
	g.setColor(Color.white);
	PlotGraph graph 
	    = new PlotGraph(g,null,new double[]{0,iDataMin},
			    new double[]{iDataWidth,iDataMax},
			    new Dimension(size().width-iXOrigin-iMargin,
					  size().height-iYOrigin-iMargin),
			    new Dimension(iXOrigin,-(size().height-iYOrigin)),
			    PlotGraph.LINE);
	for (int iDataSetNum = 0; 
	         iDataSetNum < (czParamList.length - iFirstDataSetRecord)/2; 
	         iDataSetNum++)
	    {
	    String[] czDataDescriptor 
		= Parse.getParamValues(czParamList[iFirstDataSetRecord+iDataSetNum*2],",",this);
	    String[] czDataYvalues 
		= Parse.getParamValues(czParamList[iFirstDataSetRecord+1+iDataSetNum*2],",",this);
	    if ((czDataDescriptor == null) || (czDataYvalues == null))
		{
		continue; /* try the next pair */
		}
	    setColorByName(czDataDescriptor[0],g);
	    double[] x = new double[czDataYvalues.length];
	    double[] y = new double[czDataYvalues.length];
 	    for (int i=0; i< czDataYvalues.length; i++)
		{
		if (czDataYvalues[i] != null)
		    {
		    x[i] = i;
		    y[i] = Integer.parseInt(czDataYvalues[i]);
		    }
		}
	    try
		{
		graph.plot(x,y);
		}
	    catch (Exception e)
		{
		e.printStackTrace();
		}
	    g.setColor(Color.white);
	    g.drawString(czDataDescriptor[1],iXOrigin,
			 (size().height-(iDataSetNum*20)-iMargin));

	    }
	repaint();   // schedule the applet area for repainting
	}

    protected static java.awt.Color setColorByName(String name, Graphics g)
	{
	Color retval = Color.white;
	if (name.equals("blue"))
	    retval = Color.blue;
	else if (name.equals("green"))
	    retval = Color.green;
	else if (name.equals("red"))
	    retval = Color.red;
	else if (name.equals("cyan"))
	    retval = Color.cyan;
	else if (name.equals("magenta"))
	    retval = Color.magenta;
	g.setColor(retval);
	return retval;
	}

    }
