/**
 * Initializer.java
 * 
 * Copyright 2001 by Goldin-Rudahl Associates
 *
 * Created by Sally Goldin, 3/22/2001
 *
 * $Id: Initializer.java,v 1.1 2001/11/30 18:03:09 goldin Exp $
 * $Log: Initializer.java,v $
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.2  2001/11/05 13:59:15  goldin
 * Put UI code in a package
 *
 * Revision 1.1  2001/03/22 12:57:33  goldin
 * Implement paths panel, including initializer, callback, new path datatype
 *
 */

package com.grs.gui;

/** 
 * This is an interface used to create classes that initialize
 * a DragonField.
 * <p>
 * It has a single method, setInitialValue, which takes the
 * current field as an argument.
 */
public interface Initializer
    {
 
      /**
       * Set the initial value of the passed field as appropriate
       * @param field DragonField whose value is to be set.
       */
    public void setInitialValue(DragonField field);
    }

