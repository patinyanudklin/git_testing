/**
 * DImageHeader
 * 
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 5/14/01
 *
 *  $Id: DImageHeader.java,v 1.19 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: DImageHeader.java,v $
 *  Revision 1.19  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.18  2005/12/23 10:40:31  goldin
 *  Don't assume that index into labels is class number
 *
 *  Revision 1.17  2005/04/04 08:24:17  goldin
 *  Get rid of windows/linux conditional since the syntax is the same
 *
 *  Revision 1.16  2005/04/01 08:53:21  goldin
 *  Refinements to get JNI fns working
 *
 *  Revision 1.15  2005/03/31 13:33:11  goldin
 *  add code to load DLL
 *
 *  Revision 1.14  2005/03/30 12:39:15  goldin
 *  Begin conversion to use JNI
 *
 *  Revision 1.13  2005/02/06 09:00:25  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.12  2004/12/28 09:16:29  goldin
 *  Convert UTF in header correctly
 *
 *  Revision 1.11  2002/09/11 23:34:43  goldin
 *  Add an error msg for file not found
 *
 *  Revision 1.10  2002/07/25 23:06:18  goldin
 *  Make Source show up in HEA
 *
 *  Revision 1.9  2002/05/29 17:52:24  goldin
 *  Add processing for calibration fields
 *
 *  Revision 1.8  2002/01/22 14:52:43  goldin
 *  Make pixels be default unit
 *
 *  Revision 1.7  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.6  2001/07/31 17:39:47  goldin
 *  Add code to extract bits/pix
 *
 *  Revision 1.5  2001/05/16 15:43:31  goldin
 *  Fine tune control appearance and behavior
 *
 *  Revision 1.4  2001/05/16 14:00:14  goldin
 *  Add reading of header block in Rpy file
 *
 *  Revision 1.3  2001/05/15 20:16:15  goldin
 *  Further work on header class - doubles and reading class names
 *
 *  Revision 1.2  2001/05/15 14:51:13  goldin
 *  Further work on Dragon Header class
 *
 *  Revision 1.1  2001/05/14 15:00:27  goldin
 *  Begin work on class to interpret header
 *
 */

package com.grs.dragon.ui;
import java.io.*;
import java.util.*;

/**
 * This class encapsulates the reading and interpretation of a
 * Dragon Image File header. An instance of the class can be initialized
 * from a file (presumably an image file) The class can then be 
 * queried to return the values of various Dragon header fields.
 * <p>
 * This class is now implemented via a set of native methods
 * that encapsulate the Dragon Image class. 
 * <p>
 * Note that this class represents a READ-ONLY header. The class
 * has has no setter methods. Changes to 
 * the header, at present, are implemented using the HEA command,
 * which sends modified data to the server via a command file.
 */
public class DImageHeader
    {

    protected static final int UNITSZ = 16;
             /* max text chars in name of map unit  */
    protected static final int HDR_HIST_LEN = 65;
             /* elements in header histogram */
    protected static final int IMG_HIST_LEN = 257;
             /* elements in in-memory histogram */
    protected static final String PIXELS = "Pixels";
             /* max number of labels */
    protected static final int NUMLABELS = 256;
      /**
       * Data we will gather and make available via access fns.
       */
    protected int nLines = 0;
    protected int nPix = 0;
    protected String fileType = null;
    protected int nBitsPerPix = 0;
    protected int imgmean = 0;
    protected int imgmax = 0;
    protected int imgmin = 0;
    protected double imgvar = 0.0;
    protected double imgsd = 0.0;
    protected long[] histo = new long[HDR_HIST_LEN];
    protected String source = "";
    protected String scene = "";
    protected String subscene = "";
    protected String comment = "";
    protected String band = "";
    protected String clf = "";
    protected String[] classnames = new String[NUMLABELS];
    protected int numlabels = 0;
    protected boolean regInit = false;
    protected int img_x = 0;;
    protected int img_y = 0;;
    protected double ref_x = 0.0;
    protected double ref_y = 0.0;
    protected double xcell_size = 0.0;
    protected double ycell_size = 0.0;
    protected String unitname = "";
    protected double z_offset = 0.0;
    protected double z_scale = 1.0;
    protected String z_unit = "";    
    boolean bInitialized = false;

    static boolean bIsWindows = false;
    static boolean bLibraryInitialized = false;
    protected String errorMessage = null;

      /**
       * Initializer code to load the library
       * Presumably if it is already loaded, there will be
       * no bad effects
       */
    protected static void loadLibrary()
        {
	try 
   	    {
	    /* for windows, the library is javautil.dll */
	    /* for linux, real name is libjavautil.so and must */
	    /* be located on LD_LIBRARY_PATH */
	    System.loadLibrary("javautil");
	    //System.out.println("Loaded the javautil library");
	    bLibraryInitialized = true; 
            }
	catch (Error e)
	    {
	    System.out.println("Cannot load C++ javautil library");
	    e.printStackTrace();
	    }
	}



      //**********************************************************
      /**
       * File-based constructor. 
       * Calls JNI-based functions in DImageHeader.dll to
       * initialize an image and image header based on
       * the passed filename. 
       * Then calles initializeFields, which calls accessor
       * methods in the C code to copy data values to local
       * variables.
       * @param imgFileName Name of image file whose header should be read.
       */
    public DImageHeader(String imgFileName)
        {
	if (!bLibraryInitialized)
	   {
	   loadLibrary();
	   }
        boolean bOk = openImage(imgFileName);
	if (bOk)
	    {
	    initializeFields();
	    }
	else
	    {
	    bInitialized = false;
	    errorMessage = "Can't find or open image file " + imgFileName;
	    }
	closeImage(imgFileName);
	}


      // No longer used. No more blobs.
      /**
       * In-memory data-based constructor. 
       * Takes an array of DHEAD bytes and passes the array to the 
       * initializeFields method which
       * extracts indidividual fields. 
       * @param data Array of data bytes.
       */
      //public DImageHeader(byte[] data)
      //{
      //  if (data.length < DHEAD)
      //    {
      //    System.out.println("Error - header must be " + DHEAD +
      //		       " bytes long");
      //    return;
      //    }
      //    initializeFields(data);
      //}

      /**
       * Workhorse method extracts data from fields.
       * Initializes the local fields in the DImageHeader 
       * object based on data in the image.
       */
    public void initializeFields()
        {
        bInitialized = false;
	errorMessage = null;
	extractNLines();
	extractNPix();
	extractFileType();
	extractBitsPerPix();
	extractImgmean();
        extractImgmin();
	extractImgmax();
        extractImgvar();
	extractImgsd();
        extractHisto();
        extractSource();
        extractScene();
        extractSubscene();
        extractBand();
        extractComment();
        extractClf();
        extractClassnames();
        extractRegInit();
        extractImg_x();
        extractImg_y();
        extractRef_x();
        extractRef_y();
        extractXcell_size();
        extractYcell_size();
	extractUnitname();
        extractZOffset();
	extractZScale();
	extractZUnit();
	bInitialized = true;
	}

      //***********************************************************

      /** Factorizations of initializeFields, request various fields
       * from the C++ image structure. This is now independent of
       * the actual file format.
       */

    protected void extractNLines()
        {
	nLines = getImageNLines();
	}
    
    protected void extractNPix()
        {
	nPix = getImageNPix();
	}

    protected void extractFileType()
        {
	fileType = getImageFileType();
	}

    protected void extractBitsPerPix()
        {
	nBitsPerPix = getImageBitsPerPix();
        if ((nBitsPerPix < 8) || (nBitsPerPix) > 16)
            nBitsPerPix = 8; 
	}

    protected void extractImgmean()
        {
        imgmean = getImageMean();
	}

    protected void extractImgmax()
        {
        imgmax = getImageMax();
	}

    protected void extractImgmin()
        {
        imgmin = getImageMin();
	}

    protected void extractImgvar()
        {
        imgvar = getImageVar();
	}

    protected void extractImgsd()
        {
        imgsd = getImageSd();
	}

    protected void extractHisto()
        {
	for (int i = 0; i < HDR_HIST_LEN; i++)
	    {
	    histo[i] = getImageHistElement(i);
	    }
	}

    protected void extractSource()
        {
	source = getImageSource();
	}

    protected void extractScene()
        {
	scene = getImageScene();
	}

    protected void extractSubscene()
        {
	subscene = getImageSubscene();
	}

    protected void extractBand()
        {
        band = getImageBand();
	}

    protected void extractComment()
        {
        comment = getImageComment();
	}

    protected void extractClf()
        {
	clf = getImageColorFile();
	}
    
    protected void extractClassnames()
        {
	numlabels = 0;
	for (int i = 0; i < NUMLABELS; i++)
	    {
	    classnames[i] = getImageLabel(i);
            if (classnames[i].length() > 0)
	        numlabels++;
	    }
	}

    protected void extractRegInit()
        {
	regInit = getImageRegInit();
	}

    protected void extractImg_x()
        {
        if (regInit)
	    img_x = getImageImgX();
	else
	    img_x = 0;
	}

    protected void extractImg_y()
        {
	if (regInit)
	    img_y = getImageImgY();
	else
	    img_y = 0;
	}

    protected void extractRef_x()
        {
        if (regInit)
	    ref_x = getImageRefX();
	else
            ref_x = 0.0;
	}

    protected void extractRef_y()
        {
        if (regInit)
	    ref_y = getImageRefY();
	else
	    ref_y = 0.0;
	}

    protected void extractXcell_size()
        {
        if (regInit)
	    xcell_size = getImageXCellSize();
	else
	    xcell_size = 1.0;
	}

    protected void extractYcell_size()
        {
        if (regInit)
	    ycell_size = getImageYCellSize();
	else
	    ycell_size = 1.0;
	}
    
    protected void extractUnitname()
        {
	unitname = getImageUnitname();
	}

    protected void extractZScale()
        {
	z_scale = getImageZScale();
	}

    protected void extractZOffset()
        {
	z_offset = getImageZOffset();
	}

    protected void extractZUnit()
        {
	z_unit = getImageZUnit();
	}

      //***********************************************************
      //************************************************************
      /**
       * Access methods
       */
    /**
     * If this method returns false, the constructor must have
     * failed.
     */
    public boolean isInitialized()
        {
	return bInitialized;
	}

    public int getNLines()
        {
	return nLines;
	}
    
    public int getNPix()
        {
	return nPix;
	}

    public String getFileType()
        {
	return fileType;
	}

    public int getBitsPerPix()
        {
	return nBitsPerPix;
	}

    public int getImgmean()
        {
        return imgmean;
	}

    public int getImgmax()
        {
        return imgmax;
	}

    public int getImgmin()
        {
        return imgmin;
	}

    public double getImgvar()
        {
        return imgvar;
	}

    public double getImgsd()
        {
        return imgsd;
	}

    public long[] getHisto()
        {
	return histo;
	}

    public String getSource()
        {
	return source;
	}

    public String getScene()
        {
	return scene;
	}

    public String getSubscene()
        {
	return subscene;
	}

    public String getBand()
        {
	return band;
	}

    public String getComment()
        {
	return comment;
	}

    public String getClf()
        {
	return clf;
	}
    
    public int getNumlabels()
        {
	return numlabels;
	}

    public String[] getClassnames()
        {
	return classnames;
	}

    public int getImg_x()
        {
        return img_x;
	}

    public int getImg_y()
        {
        return img_y;
	}

    public double getRef_x()
        {
        return ref_x;
	}

    public double getRef_y()
        {
        return ref_y;
	}

    public double getXcell_size()
        {
        return xcell_size;
	}

    public double getYcell_size()
        {
        return ycell_size;
	}
    
    public String getUnitname()
        {
        if ((unitname != null) && (unitname.length() > 0))
	    return unitname;
	else
	    return PIXELS;
	}

    public double getZScale()
        {
        return z_scale;
	}

    public double getZOffset()
        {
        return z_offset;
	}
    
    public String getZUnit()
        {
        if ((z_unit != null) && (z_unit.length() > 0))
	    return z_unit;
	else
	    return "";
	}

    public String getErrorMessage()
        {
	return errorMessage;
	}

      /**
       * Native methods, implemented in DImageHeader.cpp
       */
        public native boolean openImage(String filename);
        public native void closeImage(String filename);

	public native int getImageNLines();
	public native int getImageNPix();
	public native String getImageFileType();
	public native int getImageBitsPerPix();
        public native int getImageMean();
        public native int getImageMax();
        public native int getImageMin();
        public native double getImageVar();
        public native double getImageSd();
	public native long getImageHistElement(int elemNum);
	public native String getImageSource();
	public native String getImageScene();
	public native String getImageSubscene();
        public native String getImageBand();
        public native String getImageComment();
	public native String getImageColorFile();
        public native int getImageLabelCount();
        public native String getImageLabel(int labelNum);
	public native boolean getImageRegInit();
	public native int getImageImgX();
	public native int getImageImgY();
        public native double getImageRefX();
	public native double getImageRefY();
        public native double getImageXCellSize();
	public native double getImageYCellSize();
	public native String getImageUnitname();
	public native double getImageZScale();
	public native double getImageZOffset();
	public native String getImageZUnit();



      /**
       * Test driver.
       */
    public static void main(String[] args)
        {
	if (args.length < 1)
	     {
	     System.out.println("Usage: java DImageHeader <imgfilename>");
	     System.exit(0);
	     }
        DImageHeader header = new DImageHeader(args[0]);
	if (!header.isInitialized())
	     {
	     System.out.println("Error reading image file");
	     System.exit(0);
	     }
	/** 
	 * otherwise print out data.
	 */

	System.out.println("Image dimensions: " + header.getNLines() + 
			   " by " + header.getNPix());
	System.out.println("File type: " +  header.getFileType());
	System.out.println("Mean: " + header.getImgmean());
	System.out.println("Min: " + header.getImgmin());
	System.out.println("Max: " + header.getImgmax());
        System.out.println("Variance: " + header.getImgvar());
	System.out.println("Standard Dev: " + header.getImgsd());
	System.out.println("First 16 elements of histogram: ");
	long[] histarray = header.getHisto();
	for (int i = 0; i < 16; i++)
	  System.out.println(histarray[i]);
	System.out.println("Source: "+ header.getSource());
	System.out.println("Scene: " + header.getScene());
	System.out.println("Subscene: " + header.getSubscene());
	System.out.println("Band: " + header.getBand());
	System.out.println("Comment: " + header.getComment());
	System.out.println("Color file: " + header.getClf());
        System.out.println("Upper left img coords: " + header.getImg_x() +
			   "," + header.getImg_y());
        System.out.println("Upper left reference coords: " + 
			   header.getRef_x() +
			   "," + header.getRef_y());
	System.out.println("Cell size :" + header.getXcell_size() +
			   " by " + header.getYcell_size());
	System.out.println("Unit: "  + header.getUnitname());
	int labelcount = header.getNumlabels();
	if (labelcount == 0)
	    System.out.println("No labels in header");
	else
	    {
	    String[] labels = header.getClassnames();
	    for (int i = 0; i < labelcount; i++)
                System.out.println("Class " + i + ": " +
				   labels[i]);

            }
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DImageHeader.java,v 1.19 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

























