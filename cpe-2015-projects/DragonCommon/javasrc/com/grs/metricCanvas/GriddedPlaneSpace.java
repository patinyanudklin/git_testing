/* GriddedPlaneSpace.java
 * kurt rudahl 11/1/2001
 * copyright goldin-rudahl associates
 * purpose:
 ************************************************************************
 * $Id: GriddedPlaneSpace.java,v 1.2 2001/11/02 19:13:59 goldin Exp $
 * $Log: GriddedPlaneSpace.java,v $
 * Revision 1.2  2001/11/02 19:13:59  goldin
 * Working on color grid implementation
 *
 * Revision 1.1  2001/11/01 09:57:54  rudahl
 * added GriddedPlaneSpace.java Makefile GriddedPlaneSpace.java
 *
 ************************************************************************
 * history 11/1/2001   created by revising LinearPlaneSpace
 */

package com.grs.metricCanvas;

import java.awt.*;

/**
 * This is snap-to-grid, 2D drawing canvas 
 */
public class GriddedPlaneSpace extends PlaneSpace
    {
    protected GriddedMetric m_gridM[] = null;
      /**
       * Constructor sets up appropriate metrics.
       *
       *  @param g         Graphics of the object we are drawing into
       *  @param parent    enclosing PlaneSpace, or null
       *                   if null, remapping uses scaling factors = 1  
       *  @param offset    offset in pixels from parent or other reference.
       *                   In case of ambiguity, the reference point is
       *                   the lower-left corner.
       *  @param minRange  2D array of minimum input coords 
       *  @param maxRange  2D array of maximum input coords
       *  @param logicalRange Width and height of drawing coordinate system
       *  @param offset    X and Y offset of this GriddedPlaneSpace in parent
       *  @param iSteps    Number of steps in the grid
       */
    GriddedPlaneSpace(Graphics g, PlaneSpace parent, 
		      double[] minRange, double[] maxRange, 
		      Dimension logicalRange, Dimension offset,
		      Dimension iSteps) 
        {
	super(g,parent,(Metric[])null,minRange,maxRange,logicalRange,offset);
	m_gridM = new GriddedMetric[2];
	m_gridM[0] = new GriddedMetric(minRange[0],maxRange[0],offset.width,
				 offset.width+logicalRange.width,
				 iSteps.width);
	m_gridM[1] = new GriddedMetric(minRange[1],maxRange[1],offset.height,
				 offset.height+logicalRange.height,
				 iSteps.height);
	setMetrics(m_gridM);
	}

      /** construct a GriddedPlaneSpace using a default 0.0 to 1.0 data range
       */
    GriddedPlaneSpace(Graphics g, PlaneSpace parent, 
		      Dimension logicalRange, Dimension offset,
		      Dimension iSteps) 
        {
	this(g,parent,new double[]{0.0,0.0}, new double[]{1.0,1.0},
	     logicalRange,offset,iSteps);
	}
      
      /**
       * Draw one grid cell, given its x and y grid coordinates
       * If iGutterSize is > 0, leaves a border of that many
       * pixels around the block, on the lower right 
       * We assume that the color has already
       * been set on the graphics object.
       * 
       */
    public void fillGridCell(int xGridCoord, int yGridCoord,
                             int iXGutterSize,int iYGutterSize)
       throws DefectiveStructureException
        {
	int x0  = (int) m_gridM[0].gridToData(xGridCoord);
        int y0  = (int) m_gridM[1].gridToData(yGridCoord);
        int width  = (int) m_gridM[0].getStepSize();
        int height  = (int) m_gridM[1].getStepSize();
	width -= iXGutterSize;
	height -= iYGutterSize;
        //System.out.println("In fillGridCell x0=" + x0 + " y0="
	//   + y0 + " width=" + width
      	//   + " height=" + height);
	m_g.fillRect(x0,y0,width,height);
	}

    }
