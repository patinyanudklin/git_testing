/* Validator.java
 *
 * Generated by java-pp.pl from Validator.java
 * on Mon Jan  8 11:41:24 EST 2001

 * Copyright Goldin-Rudahl Associates
 *
 * $Id: Validator.java,v 1.2 2002/04/29 22:36:16 goldin Exp $
 * $Log: Validator.java,v $
 * Revision 1.2  2002/04/29 22:36:16  goldin
 * Fine tune error message delivery
 *
 * Revision 1.1  2001/11/30 18:03:09  goldin
 * Moved most of the UI basic components to the com.grs.gui package
 *
 * Revision 1.4  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.3  2001/04/10 11:18:46  goldin
 * Fix problem with modal dialog in FileValidator; extend IntegerValidator
 *
 * Revision 1.2  2001/01/12 19:10:21  goldin
 * Completed implementation of basic control types, added validation and callback support, key handling
 *
 * Revision 1.1  2001/01/08 19:34:42  goldin
 * Initial population for new DRAGON-Java UI
 *
 */

package com.grs.gui;

/** Interface which must be implemented by classes that
*   perform validation on field values.
*   
* @author  goldin
* @version  Mon Jan 08 11:36:01 EST 2001
*/
public interface Validator 
    {
    
    //********************************************************************
    /** Returns true if current field value is valid, else false.
     * @param  field Field whose value is to be validated.
     */
    public boolean isValid(DragonField field);

      /**
       * Asks the validator to display an error box showing
       * information on the last error.
       */
    public void displayLastError();
    
      /**
       * returns true if error exists that has not been reported,
       * else false.
       */
    public boolean isErrorOutstanding();

    }

// End of Validator.java

