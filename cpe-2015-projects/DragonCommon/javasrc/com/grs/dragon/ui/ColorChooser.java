//***************************************************************
//
//          ColorChooser.java - dialog for choosing colors
//			 S.E.Goldin
//
//          Copyright 2001 by Sally Goldin & Kurt Rudahl

//***************************************************************
/*
 *  $Id: ColorChooser.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: ColorChooser.java,v $
 *  Revision 1.5  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.4  2006/04/20 08:36:11  goldin
 *  *** empty log message ***
 *
 *  Revision 1.3  2005/12/09 14:11:31  goldin
 *  Avoid problems if file has no labels
 *
 *  Revision 1.2  2005/09/16 11:50:46  goldin
 *  Making color chooser work directly from the UI
 *
 *  Revision 1.1  2005/09/15 08:32:47  goldin
 *  Move color chooser to UI package, invoke directly from the UI
 *
 *  Revision 1.15  2005/02/06 09:17:30  goldin
 *  Fix javadoc warnings
 *
 *  Revision 1.14  2002/09/11 22:23:45  goldin
 *  Don't enable Save if no output color file
 *
 *  Revision 1.13  2002/04/25 17:58:40  rudahl
 *  fixed message numbers for help
 *
 *  Revision 1.12  2002/04/03 18:01:08  goldin
 *  Show 17 bars for classified image, also implement Help
 *
 *  Revision 1.11  2002/02/19 20:57:20  goldin
 *  Fix problem with reset in classified img table
 *
 *  Revision 1.10  2002/01/04 19:08:42  goldin
 *  Fix bugs in color mapping, add new labels
 *
 *  Revision 1.9  2001/12/20 18:47:01  rudahl
 *  expanded box size
 *
 *  Revision 1.8  2001/11/28 12:09:15  goldin
 *  Add remapping to registers
 *
 *  Revision 1.7  2001/11/27 17:38:19  goldin
 *  Add capability to set details
 *
 *  Revision 1.6  2001/11/21 11:40:09  goldin
 *  Add Undo/Redo, interface to C, prelim. error reporting
 *
 *  Revision 1.5  2001/11/20 18:46:59  goldin
 *  Continue refinements of color chooser functionality
 *
 *  Revision 1.4  2001/11/16 16:37:47  goldin
 *  Begin moving UI code to other packages as relevant
 *
 *  Revision 1.3  2001/11/15 20:47:02  rudahl
 *  moved viewport java files to their own package
 *
 *  Revision 1.2  2001/11/15 18:08:40  goldin
 *  Add classified img display functionality
 *
 *  Revision 1.1  2001/11/12 16:04:19  goldin
 *  Begin implementation of ColorChooser
 *
 */
package com.grs.dragon.ui;

import javax.swing.*;
import javax.swing.border.*;
import javax.swing.undo.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import com.grs.metricCanvas.*;
import com.grs.gui.*;  // for I18NTextSource - will change
import com.grs.dragon.ui.*;  // For DImageHeader
/**
 * This class provides the functionality for viewing and modifying
 * color schemes. It is used to implement the Dragon U/COL operation.
 * <p>
 * Depending on the parameters passed to the chooseColors method,
 * the chooser will show either two or three vertically-oriented
 * panels. The leftmost panel is a color table from which colors
 * may be selected.  The middle panel shows two vertical wedges that
 * indicate the color scheme being created. The rightmost panel, present
 * only if a classified image file is passed in to the chooseColors
 * method, shows a legend-like display associating classes with colors.
 * <p>
 * The chooseColors method returns immediately, but the
 * chooser remains visible until the user
 * clicks on the Ok or Cancel button. At this point, if requested, the
 * control will write a new color file.
 */

public class ColorChooser extends JDialog
                          implements ActionListener, MouseListener,
                                     MouseMotionListener, FocusListener
    {
    protected JFrame parentFrame = null;

      /**
       * instance of class to read and write color files.
       */
    protected ColorFileProcessor clfProcessor = null;

      /**
       * ColorGridCanvas for choosing colors
       */
    protected ColorGridCanvas referenceCanvas = null;
    protected ColorGridCanvas grayCanvas = null;

      /** 
       * one by one grid for showing the currently selected 
       * color.  
       */
    protected ColorGridCanvas selectedCanvas = null;

      /**
       * ColorGridCanvas for displaying colors
       */
    protected ColorGridCanvas resultCanvas = null;

      /**
       * Three color grid canvas for the I, L, and C
       * cases.
       */
    protected ColorGridCanvas imageResultCanvas = null;
    protected ColorGridCanvas layerResultCanvas = null;
    protected ColorGridCanvas classResultCanvas = null;
      /**
       * Panel to provide alternative layouts of colors.
       */
    protected JPanel gridPanel = null;

      /**
       * Currently selected color and index on reference grid
       */
    protected int currentColorIndex = -1;
    protected Color currentColor = null;
    

      /**
       * Control buttons
       */
    protected JButton okButton = null;
    protected JButton cancelButton = null;
    protected JButton resetButton = null;
    protected JButton undoButton = null;
    protected JButton redoButton = null;
    protected JButton helpButton = null;

      /**
       * Fields for entering color numbers as an option to
       * clicking.
       */
    protected JTextField startField = null;
    protected JTextField endField = null;

      /**
       * Label for showing current value under mouse
       */
    protected JLabel currentItemLabel = null;

      /**
       * Label for the center panel, which needs to change
       * with the file name.
       */
    protected JLabel centerLabel = null;
    protected String centerTitle = null;

      /**
       * Panel for displaying classified image info.
       * Make class-wide so it can be added or removed.
       */
    protected JPanel classDisplay = null;

      /**
       * Main UI panel, saves us from having to keep getting
       * the content pane.
       */
    protected JPanel mainPanel = null;

      /**
       * Text processor for getting internationalized
       * strings.  Initialized in constructor
       */
    protected I18NTextSource textSource = null;

      /**
       * Was OK clicked to exit, or not
       */
    protected boolean bOkClicked = false;

      /**
       * File names initialized in chooseColors
       */
    protected String baseClfFile = null;
    protected String newClfFile = null;
    protected String classifiedImgFile = null;
      /* If true, and classifiedImgFile is not null
       * filetype is 'C', else if false and file not null,
       * filetype is 'L'
       */
    protected String fileType = "I";
    protected String colorColumnNames[] = new String[3];
    protected String colorIndexString = null;
    protected int mouseDownIndex = -1;
    protected int mouseUpIndex = -1;
    
    protected ColorGridCanvas classColorGrids[] = null;
    protected Color grayColors[] = null;
      /**
       * Used for Undo/Redo
       */
    protected Color preColors[] = null;
    protected Color postColors[] = null;
    protected UndoManager undoManager = null;

    protected static String[] helpKeys = { "%h6509.2",
                                         "%h6509.3",
                                         "%h6509.4"};
    protected JOptionPane helpPane = null;
    protected JDialog helpDialog = null;

      /**
       * Constructor creates the UI, but does not display it.
       */
    public ColorChooser(JFrame parent, I18NTextSource textSource)
        { 
        super(parent, "COL");
	parentFrame = parent;
        this.textSource = textSource;
	String title = textSource.getI18NText("%h3062.8","Create or Change Color Scheme");
	this.setTitle(title);
        colorColumnNames[0] = textSource.getI18NText("%h9900.16","CLASS");
        colorColumnNames[1] = textSource.getI18NText("%h9900.15","NAME");
        colorColumnNames[2] = textSource.getI18NText("%h2D0.0.5","COLOR");
        clfProcessor = new ColorFileProcessor(null);
	grayColors = new Color[40];
        for (int i = 0; i< 40; i++)
             grayColors[i] = ColorFileProcessor.BasicColors[216 + i];
        preColors = new Color[256];
	postColors = new Color[256];
	undoManager = new UndoManager();
        mainPanel = new JPanel(new BorderLayout(10,10));
        JPanel leftPanel = new JPanel(new BorderLayout(10,10));
        leftPanel.setBorder(BorderFactory.createCompoundBorder(
           new EtchedBorder(), new EmptyBorder(10,10,10,10)));
	referenceCanvas = new ColorGridCanvas(36,6,8,8,2,2);
        referenceCanvas.addMouseListener(this);
        referenceCanvas.setGridColors(ColorFileProcessor.BasicColors);
        currentColorIndex = 0;
	currentColor = ColorFileProcessor.BasicColors[0];
	grayCanvas = new ColorGridCanvas(20,2,8,8,2,2);
        grayCanvas.addMouseListener(this);
        grayCanvas.setGridColors(grayColors);
	String leftTitle = textSource.getI18NText("%h3062.10",
						  "available colors");
	JLabel leftLabel = new JLabel(leftTitle);
	leftLabel.setHorizontalAlignment(JLabel.CENTER);
	leftPanel.add(leftLabel,BorderLayout.NORTH);
        leftPanel.add(referenceCanvas,BorderLayout.CENTER);
	leftPanel.add(grayCanvas,BorderLayout.EAST);
        JPanel selectedPanel = new JPanel(new FlowLayout());
	selectedPanel.add(new JLabel(textSource.getI18NText("%h3062.7",
							"SELECTED COLOR")));
        selectedCanvas = new ColorGridCanvas(1,1,16,16,1,1);
	selectedPanel.add(selectedCanvas);
        leftPanel.add(selectedPanel,BorderLayout.SOUTH);
        mainPanel.add(leftPanel,BorderLayout.WEST);

        JPanel resultPanel = new JPanel(new BorderLayout());
        resultPanel.setBorder(BorderFactory.createCompoundBorder(
           new EtchedBorder(), new EmptyBorder(10,10,10,10)));
	centerTitle = textSource.getI18NText("%h3062.11",
						  "new colors for");
	centerLabel = new JLabel(centerTitle);
        centerLabel.setHorizontalAlignment(JLabel.CENTER);
        resultPanel.add(centerLabel,BorderLayout.NORTH);
	JPanel colorPanel = new JPanel(new BorderLayout());
	JPanel textPanel = new JPanel(new BorderLayout());
        textPanel.setBorder(BorderFactory.createCompoundBorder(
           new EtchedBorder(), new EmptyBorder(5,5,5,5)));
	imageResultCanvas = new ColorGridCanvas(64,4,50,4,10,1);
        imageResultCanvas.setColumnMajor(true);
        imageResultCanvas.addMouseListener(this);
        imageResultCanvas.addMouseMotionListener(this);
        gridPanel = new JPanel(new GridBagLayout());
	gridPanel.add(imageResultCanvas);
        resultCanvas = imageResultCanvas;

	layerResultCanvas = new ColorGridCanvas(32,2,50,8,10,1);
        layerResultCanvas.setColumnMajor(true);
        layerResultCanvas.addMouseListener(this);
        layerResultCanvas.addMouseMotionListener(this);

	classResultCanvas = new ColorGridCanvas(17,1,50,17,0,1);
        classResultCanvas.setColumnMajor(true);
        classResultCanvas.addMouseListener(this);
        classResultCanvas.addMouseMotionListener(this);

        colorPanel.add(gridPanel,BorderLayout.CENTER);

        //JLabel colorLabel = new JLabel(textSource.getI18NText(
	//			 "%h3062.6","CURRENT COLORS"));
        //colorLabel.setHorizontalAlignment(SwingConstants.CENTER);
	//colorPanel.add(colorLabel,BorderLayout.NORTH);
        colorIndexString = textSource.getI18NText("%h3062.9","Color Index:");
        currentItemLabel = new JLabel(colorIndexString + " ---");
        currentItemLabel.setHorizontalAlignment(SwingConstants.CENTER);
	colorPanel.add(currentItemLabel,BorderLayout.SOUTH);
        resultPanel.add(colorPanel,BorderLayout.CENTER);
        JLabel textTitleLabel = new JLabel(textSource.getI18NText(
					   "%h3062.0","DATA RANGE"));
        textTitleLabel.setHorizontalAlignment(SwingConstants.CENTER);
        textPanel.add(textTitleLabel, BorderLayout.NORTH);
        Box fieldsPanel = new Box(BoxLayout.X_AXIS);
        JLabel startLabel = new JLabel(textSource.getI18NText("%h3062.1",
							      "START"));
        JLabel endLabel = new JLabel(textSource.getI18NText("%h3062.2",
							      "END"));
        startField = new JTextField(5);
	endField = new JTextField(5);
        endField.addFocusListener(this);
        endField.addActionListener(this);
	fieldsPanel.add(startLabel);
	fieldsPanel.add(Box.createHorizontalStrut(5));
	fieldsPanel.add(startField);
	fieldsPanel.add(Box.createHorizontalStrut(15));
	fieldsPanel.add(endLabel);
	fieldsPanel.add(Box.createHorizontalStrut(5));
	fieldsPanel.add(endField);
	textPanel.add(fieldsPanel, BorderLayout.SOUTH);
        resultPanel.add(textPanel,BorderLayout.SOUTH);
        mainPanel.add(resultPanel, BorderLayout.CENTER);

	JPanel buttonPanel = new JPanel(new FlowLayout());
	okButton = new JButton(textSource.getI18NText("%h4502.0.0", "SAVE"));
	okButton.addActionListener(this);
	okButton.setActionCommand("F1");
	cancelButton = new JButton(textSource.getI18NText("%h1E.1", "CANCEL"));
	cancelButton.addActionListener(this);
	cancelButton.setActionCommand("F10");
	resetButton = new JButton(textSource.getI18NText("%h1E.2", "RESET"));
	resetButton.addActionListener(this);
	undoButton = new JButton(textSource.getI18NText("%h1E.3", "UNDO"));
	undoButton.addActionListener(this);
	redoButton = new JButton(textSource.getI18NText("%h1E.4", "REDO"));
	redoButton.addActionListener(this);
	helpButton = new JButton(textSource.getI18NText("%h9560.1", "HELP"));
	helpButton.addActionListener(this);
        buttonPanel.add(okButton);
        buttonPanel.add(cancelButton);
        buttonPanel.add(resetButton);
        buttonPanel.add(undoButton);
        buttonPanel.add(redoButton);
        buttonPanel.add(helpButton);
	setButtonState();
        mainPanel.add(buttonPanel,BorderLayout.SOUTH);
        getContentPane().add(mainPanel,BorderLayout.CENTER);
	setupHelp();
	}
	
	/**
	 * Primary method for this class, which encapsulates all
	 * its behavior. Displays the chooser and allows the user
	 * to select and modify colors. Upon choosing OK,
	 * the frame will be set to invisible. If an output file
	 * was specified, the current colors will be written to
	 * that file.
	 * @param baseClfFile Color file to use as starting point
	 *                    may be null
	 * @param newClfFile  Color file to write. May be null.
	 * @param classifiedImgFile Name of classified image to use as 
	 *                      reference. May be null.
	 * @return 0 if everything read and displayed ok, else false.
	 */
    public int chooseColors(String baseClfFile,
			    String newClfFile,
			    String classifiedImgFile)
        {
        boolean bOkClicked = false;
        boolean bOk = true;
        fileType = "I";
        startField.setText("");
	endField.setText("");
        currentColorIndex = 0;
	currentColor = ColorFileProcessor.BasicColors[0];
	selectedCanvas.setOneColor(0,currentColor);
	selectedCanvas.replotColors();
	selectedCanvas.repaint();
        undoManager.discardAllEdits();
	setButtonState();

        this.baseClfFile = baseClfFile;
	if (newClfFile.toUpperCase().indexOf(".CLF") > 0)
	     this.newClfFile = newClfFile;
        else 
	     this.newClfFile = null;
	this.classifiedImgFile = classifiedImgFile;
        if ((classifiedImgFile != null) &&
            (classifiedImgFile.length() > 0))
	    {
            createClassDisplay(baseClfFile);
	    }
        else
	    {
            if (classDisplay != null)
	        {
		mainPanel.remove(classDisplay);
		classDisplay = null;
		classColorGrids = null;
		}
	    }
        if (this.baseClfFile == null)
	    this. baseClfFile = new String(ApplicationManager.getReadPath()
                                         + File.separator + "DEF3BA.CLF");
	bOk = clfProcessor.init(this.baseClfFile);
	if (!bOk)
	    {
	    return -1;    // cannot read color file
	    }
        if (this.newClfFile != null)
	    { 
	    centerLabel.setText(centerTitle + " " + newClfFile.toUpperCase());
	    okButton.setEnabled(true);
	    }
	else
	    {
	    centerLabel.setText("");
	    okButton.setEnabled(false);
	    }
	if (resultCanvas != null)
	    gridPanel.remove(resultCanvas);
        if (fileType.equals("I"))
	    {
            resultCanvas = imageResultCanvas;
	    }
	else if (fileType.equals("L"))
	    {
            resultCanvas = layerResultCanvas;
	    }
        else 
	    {
	    resultCanvas = classResultCanvas;
	    }
	gridPanel.add(resultCanvas);
	resultCanvas.setGridColors(clfProcessor.getRemappedColors());
	resultCanvas.repaint();
	pack();
	Point parentLoc = parentFrame.getLocationOnScreen();
	Dimension parentSize = parentFrame.getSize();
	Dimension mySize = getSize();
        setLocation(parentLoc.x + (parentSize.width - mySize.width)/2,
                    parentLoc.y);

	setVisible(true);		     
        return 0;
	}

      /**
       * Provide a means to dismiss the chooser without clicking
       */
   public void dismissChooser()
        {
        setVisible(false);
        }

      /**
       * Factorization. Given a classified image file, create
       * a display of its classnames and add it to the dialog.
       */
    protected void createClassDisplay(String clfFile)
        {
        DImageHeader header = new DImageHeader(classifiedImgFile);
	if (!header.isInitialized())   // error - should we report?
	    {
	    return;
	    }
        this.fileType = header.getFileType();
	if (fileType.equals("I"))
	    {
	    return;
	    }
	String clsNames[] = header.getClassnames();
        int maxClass = clsNames.length - 1;
        if (maxClass < 0)
	   {
           JOptionPane.showMessageDialog(this,"No class names found in " +
                                        classifiedImgFile);
	   return; /* ~~~~ WHAT DO WE DO HERE? */ 
	   }
	while ((clsNames[maxClass] == null) ||
               (clsNames[maxClass].length() == 0))
            maxClass -= 1;
	classColorGrids = new ColorGridCanvas[maxClass+1];
	if (clfFile == null)
	    {
            if (fileType.equals("C"))
	        {
	        this.baseClfFile = new String(ApplicationManager.getReadPath() 
                                         + File.separator + "DEFCCF.CLF");
		}
            else 
	        {
		this. baseClfFile = new String(ApplicationManager.getReadPath()
                                         + File.separator + "DEF3BA.CLF");
		}
	    }
        ColorFileProcessor clsProcessor = new ColorFileProcessor(baseClfFile);
        JPanel clsTable = new JPanel(new GridLayout(maxClass+1,0));
        for (int i = 0; i <= maxClass; i++)
	    {
            if (clsNames[i].length() == 0)
	        {
		continue;
		}
            JPanel row = new JPanel(new BorderLayout(10,0));
            row.add(new JLabel(String.valueOf(i)),BorderLayout.WEST);
	    row.add(new JLabel(clsNames[i]),BorderLayout.CENTER);
	    ColorGridCanvas dummy = new ColorGridCanvas(1,1,20,20,1,1);
	    dummy.setOneColor(0,ColorFileProcessor.BasicColors[
		 clsProcessor.getCurrent3baColor(i)]);
	    row.add(dummy,BorderLayout.EAST);
	    dummy.replotColors();
	    dummy.repaint();
	    classColorGrids[i] = dummy;
            clsTable.add(row);
	    }
        JPanel innerPanel = new JPanel(new BorderLayout()); 
	innerPanel.add(clsTable, BorderLayout.NORTH);
        classDisplay = new JPanel(new BorderLayout());
        classDisplay.setBorder(BorderFactory.createCompoundBorder(
           new EtchedBorder(), new EmptyBorder(10,10,10,10)));
	JPanel labelPanel = new JPanel(new BorderLayout());
        JLabel fileLabel = new JLabel(classifiedImgFile.toUpperCase());
	fileLabel.setFont(new Font("Lucida Sans",Font.PLAIN,11));
	labelPanel.add(fileLabel,BorderLayout.NORTH);
	JLabel refOnly = new JLabel(textSource.getI18NText("%h3062.12",
			   "[reference only]"));
	labelPanel.add(refOnly,BorderLayout.SOUTH);
	classDisplay.add(labelPanel,BorderLayout.NORTH);
        classDisplay.add(innerPanel,BorderLayout.CENTER);
        mainPanel.add(classDisplay,BorderLayout.EAST);        
	}

      /* Method from JniDialog:
       * clear out local data before a new plot 
       */
    public void reinit()
        {
	 // nothing to do at the moment

	}

    /**
     * Mouse Motion Listener methods 
     */
    public void mouseMoved(MouseEvent e)
        {
        Object source = e.getSource();
	if (source == resultCanvas)
	    {
            int index = resultCanvas.getMouseIndex(e);
            if (index >= 0)
                currentItemLabel.setText(colorIndexString + " " +
					 String.valueOf(index));
	    else
                currentItemLabel.setText(colorIndexString + " ---");
	    }
        }

    public void mouseDragged(MouseEvent e)
        {
        }

    /**
     * Mouse Listener methods 
     */
    public void mouseClicked(MouseEvent e)
        {
        }

    public void mouseEntered(MouseEvent e)
        {
        }

    public void mouseExited(MouseEvent e)
        {
	currentItemLabel.setText(colorIndexString + " ---");
        }

    public void mousePressed(MouseEvent e)
        {
        Object source = e.getSource();
        if (source.equals(resultCanvas))
	    {
            mouseDownIndex = resultCanvas.getMouseIndex(e);
	    startField.setText("");
	    endField.setText("");
	    }
        }

    public void mouseReleased(MouseEvent e)
        {
        Object source = e.getSource();
	int iStart = -1;
	int iEnd = -1;
        if (source.equals(referenceCanvas))
	    {
            currentColorIndex = referenceCanvas.getLastCellClicked();
            if (currentColorIndex == -1)
                return;
	    startField.setText("");
	    endField.setText("");
	    currentColor = referenceCanvas.getOneColor(currentColorIndex);
	    //System.out.println(
	    //"Selected index: " + currentColorIndex + " Color: " +
	    //	   dumpColor(currentColor));
 	    selectedCanvas.setOneColor(0,currentColor);
            selectedCanvas.replotColors();
            selectedCanvas.repaint();
            }
        else if (source.equals(grayCanvas))
	    {
            currentColorIndex = grayCanvas.getLastCellClicked();
            if (currentColorIndex == -1)
                return;
	    startField.setText("");
	    endField.setText("");
	    currentColor = grayCanvas.getOneColor(currentColorIndex);
            currentColorIndex +=216;
	    //System.out.println(
	    //"Selected index: " + currentColorIndex + " Color: " +
	    //    dumpColor(currentColor));
 	    selectedCanvas.setOneColor(0,currentColor);
            selectedCanvas.replotColors();
            selectedCanvas.repaint();
            }
        else if (source.equals(resultCanvas))
	    {
            mouseUpIndex = resultCanvas.getMouseIndex(e);
            if ((mouseUpIndex >= 0) && (mouseDownIndex >=0))
	        {
                iStart = Math.min(mouseUpIndex, mouseDownIndex);
                iEnd = Math.max(mouseUpIndex, mouseDownIndex);
	        startField.setText(String.valueOf(iStart));
	        endField.setText(String.valueOf(iEnd));
	        setNewColor(iStart,iEnd);
		}
	    else 
	        {	
		startField.setText("");
		endField.setText("");
		}
	    }
	}

     /**
      * Factorization. Set undo and redo enablement based on
      * current state of undo manager.
      */
    protected void setButtonState()
        {
        undoButton.setEnabled(undoManager.canUndo());
        redoButton.setEnabled(undoManager.canRedo());
	}
      
     /**
      * Factorization of mouseReleased and actionPerformed.
      * Modifies the color in the resultCanvas and in the clrFileProcessor.
      * This is the core action of the color chooser, the action
      * that is undoable.
      * @param start  First index to modify
      * @param end    Last index to modify
      */
    protected void setNewColor(int start, int end)
        {
	undoManager.discardAllEdits();  // only one undoable change
        System.arraycopy(clfProcessor.getRemappedColors(),0,
			 preColors,0,256);
	for (int idx = start; idx <= end; idx++)
	    {
 	    resultCanvas.setOneColor(idx,currentColor);
	    clfProcessor.setCurrent3baColor(idx, currentColorIndex);
            if ((classColorGrids != null) && 
		(idx < classColorGrids.length) && 
		(classColorGrids[idx] != null))
	         {
	         classColorGrids[idx].setOneColor(0,currentColor);
	         classColorGrids[idx].replotColors();
	         classColorGrids[idx].repaint();
		 }
	    }
        System.arraycopy(clfProcessor.getRemappedColors(),0,
			 postColors,0,256);
        ColorEdit cEdit = new ColorEdit(this, start, end,
					preColors,postColors);
        undoManager.addEdit(cEdit);
	setButtonState();
	resultCanvas.replotColors();
	resultCanvas.repaint();
	}

     /**
      * Method used to implement undo and redo. Resets a range
      * of colors from start to end inclusive, to the appropriate
      * value from the colors array.
      * @param start  First index to modify
      * @param end    Last index to modify
      * @param colors  Index of 256 color objects
      */
    public void reviseColors(int start, int end, Color colors[])
        {
	for (int idx = start; idx <= end; idx++)
	    {
            Color theColor = colors[idx];
 	    resultCanvas.setOneColor(idx,theColor);
	    clfProcessor.setCurrent3baColor(idx, 
                clfProcessor.getMasterIndex(theColor));
            if ((classColorGrids != null) && 
		(idx < classColorGrids.length) && 
		(classColorGrids[idx] != null))
	         {
	         classColorGrids[idx].setOneColor(0,theColor);
	         classColorGrids[idx].replotColors();
	         classColorGrids[idx].repaint();
		 }
	    }
	resultCanvas.replotColors();
	resultCanvas.repaint();
	setButtonState();
	}

   /**
    * Create the help option pane and dialog
    */
   protected void setupHelp()
       {
       StringBuffer helpBuffer = new StringBuffer();
       String title = textSource.getI18NText("%h4500.0.6","help");
       for (int i = 0; i < helpKeys.length; i++)
	  {
	  String temp = textSource.getI18NText(helpKeys[i],"help");
	  if (i > 0)
             helpBuffer.append("\n\n");
	  helpBuffer.append(temp);
	  }
       JTextArea messageArea = new JTextArea(helpBuffer.toString(),10,50);
       messageArea.setLineWrap(true);
       messageArea.setWrapStyleWord(true);
       helpPane = new JOptionPane(new JScrollPane(messageArea));
       helpDialog = helpPane.createDialog(this,title);
       }


      /** 
       *  Provide some help info
       *  Copied from prompt and reply
       *  @param   czMsg        help msg (internationalized)
       *  @param   bError       true => error msg false => std help
       */
    protected void showHelp(String[] czMsg,boolean bError)
        {
	helpDialog.setVisible(true);
	  /**
	InfoText pIT = new InfoText(textSource);
	String[] czInfo;
	int msgNo = 0;
	if (bError)
	    {
	    czInfo = new String[1+czMsg.length];
	    czInfo[msgNo++] = "%e421";
	    }
	else
	    {
	    czInfo = new String[czMsg.length];
	    }
	for (int i=0; i<czMsg.length; i++)
	    czInfo[i+msgNo] = czMsg[i];
	pIT.setupContents("HELP",czInfo);
	pIT.showIt();
	**/
	}

     /**
      * Action Listener method
      */
    public void actionPerformed(ActionEvent ae)
        {
        Object source = ae.getSource();
        if (source.equals(okButton))
	    {
            boolean bOk = true;
            bOkClicked = true;
            if ((newClfFile != null) &&
		(newClfFile.length() > 0))
                bOk = clfProcessor.writeColorFile(newClfFile); 
	    setVisible(false);
	    }
        else if (source.equals(helpButton))
	    {
	    showHelp(helpKeys,false);
	    }
        else if (source.equals(cancelButton))
	    {
	    setVisible(false);
	    }
        else if (source.equals(undoButton))
	    {
	    undoManager.undo();
	    setButtonState();
	    }
        else if (source.equals(redoButton))
	    {
	    undoManager.redo();
	    setButtonState();
	    }
        else if (source.equals(resetButton))
	    {
	    clfProcessor.reset();
            undoManager.discardAllEdits();
	    setButtonState();
	    resultCanvas.setGridColors(clfProcessor.getRemappedColors());
	    resultCanvas.repaint();
            if (classDisplay != null)
	       {
               for (int i=0; i < classColorGrids.length; i++)
		   {
                   ColorGridCanvas dummy = classColorGrids[i];
		   if (dummy != null)
		       {
	               dummy.setOneColor(0,ColorFileProcessor.BasicColors[
		           clfProcessor.getCurrent3baColor(i)]);  
		       dummy.replotColors();
		       dummy.repaint();
		       }
		   }
	       }
	    }
        else if (source.equals(endField))
	    {
	    checkIndicesAndChange();
	    }
	}

      /**
       * Focus Listener methods
       */
    public void focusGained(FocusEvent e)
        {
	}

    public void focusLost(FocusEvent e)
        {
        Object source = e.getSource();
        if (source.equals(endField))
	    {
	    checkIndicesAndChange();
	    }
	}

    /**
     * Factorization - if start <= end, then
     * change the data in that range.
     */
    protected void checkIndicesAndChange()
       {
       int iStart = -1;
       int iEnd = -1;
       try
	   {
	   iStart = Integer.parseInt(startField.getText());
	   iEnd = Integer.parseInt(endField.getText());
	   }
       catch (NumberFormatException nfe)
	   {
	   }
       if ((iStart >= 0) && (iEnd >= 0) &&
	   (iEnd >= iStart) && (iEnd < 256))
	   setNewColor(iStart,iEnd);
       else
	   {
	   Toolkit.getDefaultToolkit().beep();
	   startField.setText("");
	   endField.setText("");
	   }
       }

    public boolean getOkClicked()
        {
	return bOkClicked;
	}

      /**
       * Debug method. Returns a string with color components
       * shown in hex.
       */
    protected String dumpColor(Color c)
        {
        StringBuffer buffer = new StringBuffer(128);
	buffer.append("[r=0x" + Integer.toString(c.getRed(),16).toUpperCase());
	buffer.append(" g=0x" + Integer.toString(c.getGreen(),16).toUpperCase());
	buffer.append(" b=0x" + Integer.toString(c.getBlue(),16).toUpperCase()
		      + "]");
	return buffer.toString();
	}

	/**
	 * Test driver 
	 */
    public static void main(String args[])
        {
	try
	    { 
	    UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
	    }
	catch (Exception e)
   	    {
	    System.out.println("Error setting look and feel");
	    }
	JFrame testFrame = new JFrame();
	ApplicationManager.setReadPath("E:\\PIX");
	ApplicationManager.setErrorLogger(new Logger("test.err"));
        ApplicationManager.setTextSource(new I18NTextSource(
					    "drag5-en.messages"));
        ColorChooser cc = 
          new ColorChooser(testFrame,ApplicationManager.getTextSource());
        
        int returnVal = 0;
        switch (args.length)
	    {
	    case 0:
                returnVal = cc.chooseColors(null,
				      "E:\\PIX\\TESTOUT.CLF",null);
		break;
	    case 1:
                returnVal = cc.chooseColors(args[0],
				      "E:\\PIX\\TESTOUT.CLF",null);
		break;
	    case 2:
                returnVal = cc.chooseColors(args[0],args[1],null);
		break;
	    case 3:
                returnVal = cc.chooseColors(args[0],args[1], args[2]);
		break;
	    }
	System.out.println("Returned: " + returnVal);
	}

    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: ColorChooser.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }
