/**
 * InstallCleanupCallback
 * 
 *  Copyright 2001 by Goldin-Rudahl Associates
 *
 *  Created by Sally Goldin, 12/3/2001
 */

package com.grs.dragon.installer;
import com.grs.gui.*;

/**
 * This callback class is used to delete copied files when
 * an installation is interrupted.
 */
public class InstallCleanupCallback implements Callback
    {
      
      /**
       * Reference to filemanager which knows what to delete.
       */
    protected InstallFileManager fileManager = null;

      /**
       * Allow creator to set the file manager
       */
    public void setFileManager(InstallFileManager manager)
        {
        fileManager = manager;
        }

      /**
       * Execute operation undoes any operations in the fileList.
       */
    public void executeCallback(DragonField fld)
        {
	if (fileManager == null)
	  return;  // no files copied yet
	
	boolean bOk = fileManager.cleanupFiles();
	}

    }

