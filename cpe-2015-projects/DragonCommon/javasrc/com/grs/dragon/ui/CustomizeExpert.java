/**
 * CustomizeExpert
 *
 * Copyright  2005-2007  by Sally Goldin & Kurt Rudahl and
 *                   King Mongkutt's University of Technology Thonburi.
 *
 * Created by Sally Goldin, 6 Feb 2005
 *
 * $Id: CustomizeExpert.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 * $Log: CustomizeExpert.java,v $
 * Revision 1.5  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.4  2006/01/20 07:47:27  goldin
 * Check to see if customize file exists before opening
 *
 * Revision 1.3  2005/03/27 10:39:21  goldin
 * If we don
 *
 * Revision 1.2  2005/02/06 13:56:54  goldin
 * implement user-based customization
 *
 * Revision 1.1  2005/02/06 09:57:44  goldin
 * Skeleton of class to read the customization file
 *
 */

package com.grs.dragon.ui;
import java.util.*;
import java.io.*;

/**
 * This class reads a file to find out the names of
 * subsidiary menu and panel files created by users
 * in order to customize Dragon. It encapsulates
 * the format of this file. An instance of this class
 * is created in the main method of DragonUI, and used
 * to retrieve any customization file names found.
 */
public class CustomizeExpert
{
    /** Data structure to hold parsed out menu file names. **/
    protected ArrayList localMenuFileList = new ArrayList();

    /** Data structure to hold parsed out panel file names. **/
    protected ArrayList localPanelFileList = new ArrayList();

   /** Set to true if the file reading and parsing succeeds.
    * Otherwise set to false.
    */
    protected boolean bInitialized = false;

    /**
     * Constructor creates the class instance, and
     * tries to open and read the customization file,
     * which is itself a list of the XML files the
     * user has created for customization of the UI.
     * The CustomizeExpert parses the customization file 
     * and for each filename mentioned in
     * the file, checks that it exists. If it
     * does not exist, it is skipped. Otherwise
     * it is put into the appropriate local list.
     * @param filename Name and path to customization file 
     */
    public CustomizeExpert(String filename)
       {
       try
	   {
	   String inputLine = null;
	   String xmlFileName = null;
	   String fileType = null;
	   File testFile = null;
           testFile = new File(filename);
           if (!testFile.exists())
              return;  /* No customization file */
	   BufferedReader reader = new BufferedReader(
                new FileReader(filename));
	   while ((inputLine = reader.readLine()) != null)
	      {
              /* Each line is of the form 
               * MENU: filename 
               * or
               * PANEL: filename
               */
	      int pos = inputLine.indexOf(":");
	      if (pos > 0)
		  {
		  xmlFileName = inputLine.substring(pos+1).trim();
		  testFile = new File(xmlFileName);
		  if (!testFile.exists())
		      continue;
		  fileType = inputLine.substring(0,pos).trim();
		  if (fileType.toUpperCase().matches("MENU"))
		      {
		      localMenuFileList.add(xmlFileName);
		      }
		  else
		      {
	              localPanelFileList.add(xmlFileName);		
		      }
                  }
	      }
	   bInitialized = true;
	   }
       catch (IOException ioe)
	   {
	     /* If the customization file doesn't exist, just
		continue, ignoring this.
		The initialization flag will handle this in
		the caller.
		*/
	     /** 
	     System.out.println("Error trying to read customization file '" +
                           filename +"'");
	     System.out.println("Exception message: " +
                           ioe.getMessage());
	     **/
	   }
       }




    /**
     * Check if customize file was read successfully 
     */
    public boolean isInitialized()
       {
       return bInitialized;
       }


    /**
     * Copy the menu file names read from the customize file
     * into the passed ArrayList
     * @param masterList Destination list where we want to add the filenames
     */
    public void addMenuFiles(ArrayList masterList)
       {
       for (int i = 0; i < localMenuFileList.size(); i++)
	   {
	   masterList.add(localMenuFileList.get(i));
	   }
       }    

    /**
     * Copy the panel file names read from the customize file
     * into the passed ArrayList
     * @param masterList Destination list where we want to add the filenames
     */
    public void addPanelFiles(ArrayList masterList)
       {
       for (int i = 0; i < localPanelFileList.size(); i++)
	   {
	   masterList.add(localPanelFileList.get(i));
	   }
       }


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: CustomizeExpert.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
}
