/**
 * MemoryFilter
 *
 * Copyright 2001-2006 by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 11/30/2001
 *
 * $Id: MemoryFilter.java,v 1.2 2006/01/20 08:42:32 goldin Exp $
 * $Log: MemoryFilter.java,v $
 * Revision 1.2  2006/01/20 08:42:32  goldin
 * Add isMemoryFileValid to MemoryFilter interface
 *
 * Revision 1.1  2001/11/30 18:03:44  goldin
 * interface to allow DFileField to be generic
 *
 */

package com.grs.gui;

/**
 * This is an interface which exists in order to allow us to make
 * the DTextField class generic rather than Dragon-specific.
 * The StatusManager class in the dragon/ui package implements
 * this interface.
 */
public interface MemoryFilter
    {
      /**
       * Given an array of special filenames, return
       * a filtered array which includes only those which
       * are valid based on the application's current
       * state.
       */
    public String[] filterAllowedMemoryFiles(String[] inputList,
					     DFileType fileType);

      /**
       * This method returns true if passed memory file (=M,=B,=G, and so on)
       * is currently populated with non-null data.
       * Otherwise it returns false. Used for file validation.
       * @param fileType File type this is being used to satisfy
       * @param memoryFile One of =M,=R,=G,=B,=C, or (Current) for sigs,clf ply
       */
    public boolean isMemoryFileValid(DFileType fileType, String memoryFile);

    }
