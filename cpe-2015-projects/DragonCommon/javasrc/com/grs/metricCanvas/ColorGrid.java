/**
 * ColorGrid.java
 *
 *  Copyright 2001 by Sally Goldin & Kurt Rudahl
 *
 *  Created by Sally Goldin 11/01/2001
 *
 *   $Id: ColorGrid.java,v 1.5 2005/02/06 08:21:59 goldin Exp $
 *   $Log: ColorGrid.java,v $
 *   Revision 1.5  2005/02/06 08:21:59  goldin
 *   Fix javadoc warnings
 *
 *   Revision 1.4  2001/11/12 16:04:40  goldin
 *   Modifications to support color chooser
 *
 *   Revision 1.3  2001/11/09 15:19:11  goldin
 *   Added code to set individual colors
 *
 *   Revision 1.2  2001/11/05 15:46:52  goldin
 *   Added mouse sensitivity to ColorGridCanvas, fixed calculation bugs
 *
 *   Revision 1.1  2001/11/02 19:13:59  goldin
 *   Working on color grid implementation
 *
 */

package com.grs.metricCanvas;
import java.awt.*;
/**
 * This class creates and displays a table of colored boxes or lines
 * The constructor establishes the dimensions of the table. The
 * "plot" method draws the table, given an array of Color objects.
 * The array of color objects is cached, and can be used in
 * "replot" to redisplay the same colors.
 */
public class ColorGrid extends GriddedPlaneSpace
    { 
    protected Color m_colorTable[] = null;

    protected int m_iXGutterSize = 0;
    protected int m_iYGutterSize = 0;
    protected int m_iNRows = 0;
    protected int m_iNCols = 0; 

      /**
       * Constructor, establishes the #rows and columns
       * in the table, the width and height of cells, and
       * the gutter size.
       * @param  g  Graphics of object to be drawn on
       * @param  iNRows  Number of Rows
       * @param  iNCols  Number of Columns
       * @param  iCellWidth  Width of each cell in data space (pixels)
       * @param  iCellHeight Height of each call in data space.
       * @param  iXGutterSize Size of gutter in X direction
       * @param  iYGutterSize Size of gutter between cells in Y direction
       */
    public ColorGrid(Graphics g, int iNRows, int iNCols,
                     int iCellWidth, int iCellHeight, 
		     int iXGutterSize, int iYGutterSize)
        { 
	super(g,null,makeDblArray(0,0), 
                  makeDblArray((iNCols*iCellWidth)-1,(iNRows*iCellHeight)-1),
                  new Dimension(iNCols-1,iNRows-1),
	          new Dimension(0,0),
                  new Dimension(iNCols,iNRows));
	m_iNRows = iNRows;
	m_iNCols = iNCols;
	m_iXGutterSize = iXGutterSize;
	m_iYGutterSize = iYGutterSize;
	}

    public void plot(Color dataArray[])
          throws DefectiveStructureException
        {
        setGridColors(dataArray);
        replot();
	}
    /**
     *  Set the current set of Grid colors. 
     */
    public void setGridColors(Color dataArray[])
        {
        m_colorTable = new Color[dataArray.length];
	System.arraycopy(dataArray,0,m_colorTable,0,dataArray.length);
	}

    /**
     * Set the color for a single grid cell, identified by
     * its row/color coordinates. Does not do a replot.
     * @param iRow  Row whose cell should be set.
     * @param iCol  Column whose cell should be set.
     * @param newColor  New color 
     */
    public void setOneColor(int iRow, int iCol, Color newColor)
        {
        int index = iRow * m_iNCols + iCol;
	setOneColor(index,newColor);
	}

    /**
     * Set the color for a single grid cell, identified by
     * its index into the color array. Does not do a replot.
     * @param index  Row whose cell should be set.
     * @param newColor  New color 
     */
    public void setOneColor(int index, Color newColor)
        {
        if (m_colorTable == null)
            m_colorTable = new Color[256];
        m_colorTable[index] = newColor;
	}
    /**
     * Get the current color for a single grid cell, identified by
     * its index into the color array. 
     * @param index  Row whose cell should be set.
     * @return current color at that index or null if color table
     *          not yet allocated
     */
    public Color getOneColor(int index)
        {
        if (m_colorTable == null)
            return null;
        return m_colorTable[index];
	}

      /**
       * Translate data coordinates within the grid to a row
       * (Y) and column (X) grid cell.
       * @param iInputX  X coordinate to translate
       * @param iInputY  Y coordinate to translate
       * @return Point structure where X is the column and Y is the
       *  row in the grid. Returns -1 for input outside the
       *  grid boundaries.
       */
    public Point getGridCell(int iInputX, int iInputY)
        {
	Point p = new Point(0,0);
        p.x = m_gridM[0].dataToGrid((double) iInputX); 
        p.y = m_gridM[1].dataToGrid((double) iInputY);
	return p;
	}

    public int getNRows()
        {
	return m_iNRows;
	}

    public int getNCols()
        {
	return m_iNCols;
	}


    /**
     * Assuming that the color array has been cached, redraw the
     * color table.
     */
    public void replot()
           throws DefectiveStructureException
        {
	if (m_colorTable == null)
	    return;  // should throw an exception
        int row, col;
        for (row = 0; row < m_iNRows; row++)
             for (col = 0; col < m_iNCols; col++)
	       {
               int index = row * m_iNCols + col;
	       if (index >= m_colorTable.length)
                   break; 
               m_g.setColor(m_colorTable[index]);
               fillGridCell(col, row, m_iXGutterSize,m_iYGutterSize);
	       }
        }

    protected static double[] makeDblArray(double v1, double v2)
        {
        double retArray[] = new double[2];
	retArray[0] = v1;
	retArray[1] = v2;
	return retArray;
	}



    }








