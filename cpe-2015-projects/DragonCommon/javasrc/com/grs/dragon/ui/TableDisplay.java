/**
 * TableDisplay
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 * 
 * Created by Sally Goldin, 5/21/2001
 *
 * $Id: TableDisplay.java,v 1.24 2007/01/05 07:41:57 rudahl Exp $
 * $Log: TableDisplay.java,v $
 * Revision 1.24  2007/01/05 07:41:57  rudahl
 * added Whatis info
 *
 * Revision 1.23  2006/12/31 09:24:44  goldin
 * update the DragonFileChooser constructor with new arg
 *
 * Revision 1.22  2006/08/14 10:31:20  goldin
 * Complete implementation of image window for CUR
 *
 * Revision 1.21  2006/03/05 04:45:23  goldin
 * make length of text consistent with restriction in C
 *
 * Revision 1.20  2006/03/04 09:33:37  goldin
 * modify positioning slightly
 *
 * Revision 1.19  2006/02/11 10:08:52  goldin
 * Improve appearance of HTML tables
 *
 * Revision 1.18  2005/07/24 13:20:45  goldin
 * Set correct font in display tables
 *
 * Revision 1.18  2005/07/22 11:09:00  goldin
 * Working on Font Assignment
 *
 * Revision 1.17  2005/02/06 09:00:25  goldin
 * Fix javadoc warnings
 *
 * Revision 1.16  2002/08/27 20:04:01  goldin
 * convert filechooser to potentially using multiple file types
 *
 * Revision 1.15  2002/07/25 22:57:16  goldin
 * Get rid of debug messages
 *
 * Revision 1.14  2002/06/24 18:06:01  goldin
 * Add detailsLink for manual
 *
 * Revision 1.13  2002/03/06 20:58:40  goldin
 * Add SAVE button to TableDisplay
 *
 * Revision 1.12  2002/01/04 17:14:43  goldin
 * Size table to fit full cluster means
 *
 * Revision 1.11  2001/11/16 16:41:08  goldin
 * Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 * Revision 1.10  2001/11/05 13:59:16  goldin
 * Put UI code in a package
 *
 * Revision 1.9  2001/10/19 16:22:46  goldin
 * Further work on table formatting
 *
 * Revision 1.8  2001/08/31 13:33:46  goldin
 * Implement multiple table displays, ability to kill table displays via incoming command
 *
 * Revision 1.7  2001/08/30 14:47:32  goldin
 * Begin implementing multiple table displays
 *
 * Revision 1.6  2001/06/28 14:05:45  goldin
 * Continue work on table formatting
 *
 * Revision 1.5  2001/06/27 15:17:47  goldin
 * Fix CalcParser bugs, table formatting
 *
 * Revision 1.4  2001/06/18 12:10:00  goldin
 * Fixing bugs found by Kurt
 *
 * Revision 1.3  2001/05/22 12:05:13  goldin
 * Implement new SigFileValidator; make msgs show up in the history
 *
 * Revision 1.2  2001/05/21 16:18:57  goldin
 * Initial implementation of table type messages
 *
 * Revision 1.1  2001/05/21 14:50:25  goldin
 * Add class to display tables
 *
 */

package com.grs.dragon.ui;
import com.grs.gui.*;
import javax.swing.*;
import javax.swing.plaf.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;

/**
 * This class implements a dialog which can be used to display
 * results tables or other longish text messages. The main
 * control in the dialog is a JEditorPane set up to show HTML.
 * There is one instance of this class in the system, and it
 * reuses the same dialog for each display call.*/
public class TableDisplay extends JDialog implements ActionListener
    {
      /** Test data */
    protected static final String TABLETEXT =
        "<HTML><HEAD></HEAD><BODY>" +
        "<TABLE><tr><th>Column One</th>" +
                   "<th align=right>Column Two</th>" +
                   "<th align=right>Column Three</th></tr>" +
        "<tr><td>Class 1</td><td align=right>20999</td><td align=right>13.2</td></tr>" + 
        "<tr><td>Class 2</td><td align=right>999</td><td align=right>2.99</td></tr>" + 
        "<tr><td>Class 3</td><td align=right>1393</td><td align=right>22.34</td></tr>" + 
        "<tr><td>Class 4</td><td align=right>19882</td><td align=right>8.22</td></tr>" + 
        "<tr><td>Class 5</td><td align=right>907</td><td align=right>19.2</td></tr>" + 
        "<tr><td>Class 6</td><td align=right>12099</td><td align=right>13.0</td></tr>" + 
        "<tr><td>Class 7</td><td align=right>7854</td><td align=right>7.12</td></tr>" + 
        "<tr><td>Class 8</td><td align=right>3476</td><td align=right>15.22</td></tr>" + 
        "<tr><td>Class 9</td><td align=right>9766</td><td align=right>0.87</td></tr>" + 
        "<tr><td>Class 10</td><td align=right>231</td><td align=right>12.88</td></tr>" + 
        "<tr><td>Class 11</td><td align=right>20999</td><td align=right>13.2</td></tr>" + 
        "<tr><td>Class 12</td><td align=right>999</td><td align=right>2.99</td></tr>" + 
        "<tr><td>Class 13</td><td align=right>1393</td><td align=right>22.34</td></tr>" + 
        "<tr><td>Class 14</td><td align=right>19882</td><td align=right>8.22</td></tr>" + 
        "<tr><td>Class 15</td><td align=right>907</td><td align=right>19.2</td></tr>" + 
        "<tr><td>Class 16</td><td align=right>12099</td><td align=right>13.0</td></tr>" + 
        "<tr><td>Class 17</td><td align=right>7854</td><td align=right>7.12</td></tr>" + 
        "<tr><td>Class 18</td><td align=right>3476</td><td align=right>15.22</td></tr>" + 
        "<tr><td>Class 19</td><td align=right>9766</td><td align=right>0.87</td></tr>" + 
        "<tr><td>Class 20</td><td align=right>231</td><td align=right>12.88</td></tr>" + 
        "</TABLE></BODY></HTML>";

      /**
       * pixel offset for successive instances of TableDisplay
       */
    protected static final int OFFSET = 20;
      /**
       * reference to the text source, for getting translated
       * messages. This is set in the constructor.*/
    protected I18NTextSource textSource = null;

      /**
       * Window upon which the dialogs should be centered.
       */
    protected JFrame masterWindow = null;

      /**
       * Make title available throughout the class to simplify
       * method calls.
       */
    protected String title = null;

      /**
       * label for file box.
       */
    protected String labelText = null;

      /**
       * Hold onto the message text so we can easily
       * save it.
       */
    protected String msgText = null;


      /**
       * Area for displaying text.
       */
    protected JEditorPane textDisplayArea = null;

      /**
       * Ok button.
       */
    protected JButton okButton = null;

      /**
       * Save button.
       */
    protected JButton saveButton = null;

      /**
       * File chooser for saving contents.
       */
    protected DragonFileChooser saveChooser = null;

      /**    
       * Filetypes to allow
       */
    protected DFileType[] filetypes = {DFileType.HTML};


      /**
       * ID to distinguish multiple tables.
       */
    protected String tableId = "";

      /**
       * Index in array. Arbitrary # used for positioning.
       */
    protected int index = -1;
      

    protected JPanel innerPanel = null;
    protected JPanel outerPanel = null;
 
      /**
       * Constructor sets the text source and sets things up
       * for displaying the dialog.
       */
    public TableDisplay(I18NTextSource textSource, JFrame masterWindow)
        {
        super(masterWindow,false);
        this.textSource = textSource;
        this.masterWindow = masterWindow;
        textDisplayArea = new JEditorPane();
        textDisplayArea.setContentType("text/html");
        textDisplayArea.setEditable(false);
	//textDisplayArea.setPreferredSize(new Dimension(300,580));
        JScrollPane scroller = new JScrollPane(textDisplayArea);
        innerPanel = new JPanel(new BorderLayout());
        innerPanel.add(scroller, BorderLayout.CENTER);
        //innerPanel.setPreferredSize(new Dimension(350,590));
        outerPanel = new JPanel(new BorderLayout());
        outerPanel.setBorder(BorderFactory.createMatteBorder(10,10,10,10,
                             getBackground()));
	outerPanel.add(innerPanel,BorderLayout.NORTH);
        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.setBorder(BorderFactory.createMatteBorder(5,0,5,0,
                                   getBackground()));
        String btnLabel;
	if (textSource != null)
            btnLabel = textSource.getI18NText(TextKeys.OK,"ok");
	else
	    btnLabel = "- OK - ";
        okButton = new JButton(btnLabel);
	buttonPanel.add(okButton);
	okButton.addActionListener(this);
        outerPanel.add(buttonPanel,BorderLayout.SOUTH);
	if (textSource != null)
            btnLabel = textSource.getI18NText(TextKeys.SAVE,"save");
	else
	    btnLabel = "- SAVE - ";
        saveButton = new JButton(btnLabel);
	buttonPanel.add(saveButton);
	saveButton.addActionListener(this);
        outerPanel.add(buttonPanel,BorderLayout.SOUTH);
        getContentPane().add(outerPanel);
	this.setFont((FontUIResource) UIManager.get("Dialog.font"));
        SwingUtilities.updateComponentTreeUI(this);
	}

      /**
       * Display a particular set of text or a table.
       * @param title Title string (or null if no title)
       * @param msg  Remainder of message to be displayed.
       */
    public void showTableText(String title,String msg)
        {
	if (title != null)
	     {
	     setTitle(title);
	     }
	if (labelText == null)
	     {
	     labelText = textSource.getI18NText("%h3010.4",
						"Output File");
	     }
        textDisplayArea.setText(msg);
        msgText = msg;
	pack();
        Dimension prefSize = textDisplayArea.getPreferredSize();
        int width = prefSize.width;
        int height = prefSize.height;
        if (width > 760)
            width = 760;
        if (width < 100)
            width = 100; 
        if (height > 550)
            height = 550;
	if (height < 100)
            height = 100;
         
	/**
	System.out.println("After new text, size is " +
			   textDisplayArea.getSize().width + "," +
			   textDisplayArea.getSize().height);
	System.out.println("-- Preferred size is " +
			   textDisplayArea.getPreferredSize().width + "," +
			   textDisplayArea.getPreferredSize().height);
	**/
        textDisplayArea.setPreferredSize(new Dimension(width,height));
        innerPanel.setPreferredSize(new Dimension(width+10,height+10));
	pack();
        setLocationRelativeTo(masterWindow);
	Point masterLoc = masterWindow.getLocation();
	Point p = getLocation();
        p.y = Math.max(p.y - 100,masterLoc.y);  
               /* don't center, make it higher */
        if (index >= 0)
	    {
            p.x = p.x + index*OFFSET;
            p.y = p.y + index*OFFSET;
            }
	setLocation(p);
	setVisible(true); 
	}

      /**
       * From action listener. Hide dialog when user clicks OK.
       */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
	if (source.equals(okButton))
	    {
	    setVisible(false);
            masterWindow.repaint();
	    }
	else
	    {
	    if (saveChooser == null)
                    saveChooser = new DragonFileChooser(this,textSource,
					     false,false,false);
	    File selected = saveChooser.chooseFile(
			     filetypes,null, null,
			     labelText,null);
	    String filename = null;
	    if (selected != null)
	        {
		filename = selected.getAbsolutePath();
                saveContents(filename);
		}
	    }
	}

      /**
       * Factorization. Get the current text and save it in
       * the specified file.
       */
    protected void saveContents(String filename)
        {
	try 
	    {
	    FileWriter writer = new FileWriter(filename);
	    writer.write(msgText);
	    writer.write("\n");
	    writer.close();
	    }
	catch (IOException ioe)
	    {
            ApplicationManager.getErrorDisplay().showError(
			       TextKeys.ERROR, "%h8.8", "");
	    
	    }  
	}

    public void setTableId(String id)
        {
        tableId = id; 
	}

    public String getTableId()
        {
        return tableId;
        }

    public void setIndex(int idx)
        {
        index = idx;
	}

    public int getIndex()
        {
        return index;
	}

      /**
       * Test Driver. 
       */
    public static void main(String[] args)
        {
	JFrame parent = new JFrame();
	parent.getContentPane().add(new JLabel("TESTING..."));
        TableDisplay tdisp = new TableDisplay(null,parent);
        tdisp.showTableText(null,TABLETEXT);        
	}


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: TableDisplay.java,v 1.24 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }

