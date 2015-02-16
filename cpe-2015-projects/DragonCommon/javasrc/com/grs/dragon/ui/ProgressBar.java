/**
 * ProgressBar
 *
 *  Copyright  2001-2007  by Goldin-Rudahl Associates
 *  Created by Sally Goldin, 5/2/2001
 *  
 *  $Id: ProgressBar.java,v 1.8 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ProgressBar.java,v $
 *  Revision 1.8  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.7  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.6  2001/11/05 13:59:16  goldin
 *  Put UI code in a package
 *
 *  Revision 1.5  2001/08/31 14:01:03  goldin
 *  Implement INTERRUPT capability on progress bar; required changes to DragonApp interface and CommandForwarder
 *
 *  Revision 1.4  2001/06/08 18:12:32  goldin
 *  Create DragonApp interface; rework in prep for splitting out of common classes into a separate package
 *
 *  Revision 1.3  2001/05/02 15:11:41  goldin
 *  Implement message and progress IPC file processing
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;

/**
 * This class implements a simple progress bar display, embedded in 
 * a JDialog. It's value is determined by the values passed to he
 * setValue method. It's message, currently used as a title,
 * is set by the setMessage method.
 */
public class ProgressBar extends JDialog implements ActionListener
    {
      /**
       * Interrupt button.
       */
    protected JButton interruptBtn = null;

      /**
       * Current title/message string.
       */
    protected String message = null;

      /**
       * reference to main app, for positioning.
       */
    protected DragonApp mainApp = null;

      /**
       * Child progress bar control which actually shows the
       * progress.
       */
    protected JProgressBar progBar = null;

      /**
       * Source module whose progress we are charting. Used
       * to send an interrupt message.
       */
    protected String sourceModule = null;

    /**
     * The constructor builds the basic UI for the progress bar.
     * However the bar is not displayed until the setVisible method
     * is called.
     * @param mainApp  Reference to the overall user interface, 
     *        used for positioning
     */
    public ProgressBar(DragonApp mainApp)
        {
        super(mainApp.getFrame(),false);
        this.mainApp = mainApp;
        JPanel main = new JPanel(new BorderLayout(10,10));
	main.setBorder(
                  BorderFactory.createEmptyBorder(10,20,10,20));
        progBar = new JProgressBar(SwingConstants.HORIZONTAL);
        progBar.setMinimum(0);
	progBar.setMaximum(100);
        progBar.setPreferredSize(new Dimension(250,20));
        main.add(progBar,BorderLayout.CENTER);
        String btnLabel = mainApp.getTextSource().getI18NText(
					 TextKeys.INTERRUPT,"INTERRUPT");
        interruptBtn = new JButton(btnLabel);
        interruptBtn.addActionListener(this);
        JPanel btnPanel = new JPanel(new FlowLayout());
        btnPanel.add(interruptBtn);
	main.add(btnPanel,BorderLayout.SOUTH);
	getContentPane().add(main);
	setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        pack();
        }

      /**
       * Make the bar visible or invisible.
       */
    public void setVisible(boolean bVisible)
        {
	if (bVisible)
	    {
	    if (message != null)
                setTitle(message);
	    setLocationRelativeTo(mainApp.getFrame());
	    }
        super.setVisible(bVisible);
        if (!bVisible)
	    {
	    mainApp.getFrame().repaint();
	    }
	}

      /**
       * Action listener method, responds to interrupt button
       */
    public void actionPerformed(ActionEvent ae)
        {
        CommandForwarder forwarder = mainApp.getCommandForwarder();
	forwarder.sendCommandToModule("-INTERRUPT",sourceModule);
	}

      /**
       * Get or set values.
       */
    public void setMessage(String msg)
        {
	message = msg;
	}

    public void setValue(int value)
        {
	progBar.setValue(value);
	}

    public int getValue()
        {
	return progBar.getValue();
	}

    public void setSourceModule(String module)
        {
        sourceModule = module;
        }

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ProgressBar.java,v 1.8 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
