/*
 * DragonFontChooser
 *
 * Copyright  2001-2007  by Sally Goldin & Kurt Rudahl
 *
 * Created by Sally Goldin, 4/10/2001
 *
 *  $Id: DragonFontChooser.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $
 *  $Log: DragonFontChooser.java,v $
 *  Revision 1.5  2007/01/05 07:41:57  rudahl
 *  added Whatis info
 *
 *  Revision 1.4  2005/02/06 08:08:11  goldin
 *  Fix JavaDoc warnings
 *
 *  Revision 1.3  2002/06/13 22:02:18  goldin
 *  Make some data public and static
 *
 *  Revision 1.2  2002/01/08 14:58:55  goldin
 *  Remove 'opaque' box from the font chooser
 *
 *  Revision 1.1  2001/11/30 18:03:09  goldin
 *  Moved most of the UI basic components to the com.grs.gui package
 *
 *  Revision 1.12  2001/11/16 16:41:07  goldin
 *  Move some files to common .gui package and adjust imports in dragon.ui pkg
 *
 *  Revision 1.11  2001/11/05 13:59:15  goldin
 *  Put UI code in a package
 *
 *  Revision 1.10  2001/10/31 12:21:30  goldin
 *  Add new FontInitializer
 *
 *  Revision 1.9  2001/10/30 18:06:36  goldin
 *  Use UTF-8 for commands; replace stack with hashtable for
 *
 *  Revision 1.8  2001/10/19 16:22:18  goldin
 *  Change font naming conventions
 *
 *  Revision 1.7  2001/04/25 10:51:02  goldin
 *  Add function key handling
 *
 *  Revision 1.6  2001/04/24 14:14:20  goldin
 *  Improve behavior and appearance of file and font choosers
 *
 *  Revision 1.5  2001/04/18 15:32:46  goldin
 *  Added home directory command line argument
 *
 *  Revision 1.4  2001/04/17 12:10:15  goldin
 *  Modifications made with Together
 *
 *  Revision 1.3  2001/04/13 11:08:37  goldin
 *  Add opaque box, modify semantics of set default
 *
 *  Revision 1.2  2001/04/12 14:10:31  goldin
 *  complete implementation of FontChooser and associated Font control
 *
 *  Revision 1.1  2001/04/10 15:16:33  goldin
 *  Initial implementation of Font Choosing dialog
 *
 */

package com.grs.gui;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;

/**
 * This class implements a font choosing control. It presents
 * a list of fonts, sizes and styles, and allows the user to choose one of each.*/
public class DragonFontChooser extends JDialog implements ActionListener, ListSelectionListener, WindowListener
    {
    public final static String DFLT_FACE = "Lucida Sans Unicode";
    public final static String DFLT_STYLE = "Plain";
    public final static String DFLT_SIZE ="14";


    /** Current default family - index into array */
    protected int defaultFamilyIndex = 0;

    /** Current default size - index */
    protected int defaultSizeIndex = 0;

    /** Current default style - index */
    protected int defaultStyleIndex = 0;

    /** Available font family names. */
    protected String[] fontFamilies = null;

    /** Sizes */
    protected int[] sizes = {10,11,12,14,16,18,20,22,24,26,
                             28,30,32,34,36,38,40};

    /** Styles */
    public static String[] styles = {"Plain","Bold", "Italic", "Bold Italic"};

    /** Style constants */
    public static int[] styleConstants = {Font.PLAIN, Font.BOLD,
				    Font.ITALIC, Font.BOLD+Font.ITALIC};

    /** Reference to text source for translated labels. */
    protected I18NTextSource textSource = null;

    /** Component controls. */
    protected JList nameList = null;
    protected JList sizeList = null;
    protected JList styleList = null;
    protected JLabel sampleArea = null;
    protected JButton okButton = null;
    protected JButton cancelButton = null;
    protected JCheckBox setDefaultBox = null;

    /** Parent frame for dialog. */
    protected Frame parent = null;

    /** Used to return the font selected by the user. Set in the actionPerformed method. */
    protected String selectedFont = null;

    /** Sample string */
    protected static final String sampleText = "AaBbYyZz";

    /** indices to last selected font family, size, and style */
    protected int lastFamilyIndex = -1;
    protected int lastSizeIndex = -1;
    protected int lastStyleIndex = -1;
    //*******************************************************

    /**
     * Constructor builds the UI for the dialog.
     * @param parent    Parent frame, used for centering.
     * @param textSource Text source for translated strings,
     */
    public DragonFontChooser(Frame parent, I18NTextSource textSource)
        {
        super(parent, true); // make it modal
        this.parent = parent;
        this.textSource = textSource;
        JPanel mainPanel = new JPanel(
            new BorderLayout());
        JPanel controlPanel = new JPanel(
            new FlowLayout(FlowLayout.CENTER, 20, 0));
        JPanel buttonPanel = new JPanel(
            new FlowLayout(FlowLayout.CENTER, 20, 0));
        buttonPanel.setBorder(BorderFactory.createEmptyBorder(10,10,10,10));
        String label = textSource.getI18NText(TextKeys.OK, "OK");
        okButton = new JButton(label);
        okButton.addActionListener(this);
        buttonPanel.add(okButton);
        label = textSource.getI18NText(TextKeys.CANCEL, "CANCEL");
        cancelButton = new JButton(label);
        cancelButton.addActionListener(this);
        buttonPanel.add(cancelButton);
        JPanel checkPanel = new JPanel(
            new BorderLayout());
        label = textSource.getI18NText(TextKeys.SETASDEFAULT, "Default?");
        setDefaultBox = new JCheckBox(label);
        checkPanel.add(setDefaultBox, BorderLayout.NORTH);
        buttonPanel.add(checkPanel);
        mainPanel.add(buttonPanel, BorderLayout.SOUTH);
        controlPanel.add(createFontNameList());
        controlPanel.add(createFontStyleList());
        controlPanel.add(createFontSizeList());
        initializeDefaults();
        mainPanel.add(controlPanel, BorderLayout.NORTH);
        mainPanel.add(createSampleArea(), BorderLayout.CENTER);
        getContentPane().add(mainPanel, BorderLayout.CENTER);
        addWindowListener(this);
        setSize(350, 230);
        pack();
        }

    /** Factorization of constructor. Creates a panel holding the 
     *  Fontname list and returns the panel as the value. 
     */
    protected JPanel createFontNameList()
        {
        JPanel listPanel = new JPanel(
            new BorderLayout());
        String listTitle = textSource.getI18NText(TextKeys.FONTNAME, "FONTS...");
        listPanel.add(
            new JLabel(listTitle), BorderLayout.NORTH);
        nameList = new JList();
        nameList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        nameList.addListSelectionListener(this);
        fontFamilies = filterFontFamilies();
        nameList.setListData(fontFamilies);
        listPanel.add(
            new JScrollPane(nameList), BorderLayout.CENTER);
        return listPanel;
        }

    /** Factorization of constructor. 
     *  Creates a panel holding the Font sizelist and returns the panel 
     *  as the value. 
     */
    protected JPanel createFontSizeList()
        {
        JPanel listPanel = new JPanel(
            new BorderLayout());
        String listTitle = textSource.getI18NText(TextKeys.FONTSIZE, 
						  "FONTSIZES...");
        listPanel.add(
            new JLabel(listTitle), BorderLayout.NORTH);
        sizeList = new JList();
        sizeList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        sizeList.addListSelectionListener(this);
        String[] sizeStrings = new String[sizes.length];
        for (int i = 0; i < sizes.length; i++)
            {
            sizeStrings[i] = String.valueOf(sizes[i]);
            }
        sizeList.setListData(sizeStrings);
        sizeList.setFixedCellWidth(30);
        listPanel.add(
            new JScrollPane(sizeList), BorderLayout.CENTER);
        return listPanel;
        }

    /** Factorization of constructor. Creates a panel holding the Font 
     *  stylelist and returns the panel as the value.
     */
    protected JPanel createFontStyleList()
        {
        JPanel listPanel = new JPanel(
            new BorderLayout());
        String listTitle = textSource.getI18NText(TextKeys.FONTSTYLE, 
						  "FONT STYLES...");
        listPanel.add(
            new JLabel(listTitle), BorderLayout.NORTH);
        styleList = new JList();
        styleList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
        styleList.addListSelectionListener(this);
        styleList.setListData(styles);
        listPanel.add(
            new JScrollPane(styleList), BorderLayout.CENTER);
        return listPanel;
        }

    /** Factorization of constructor. Creates area for showing sample text
     *  and returns the panel as a value. 
     */
    protected JPanel createSampleArea()
        {
        JPanel samplePanel = new JPanel(
            new BorderLayout());
        samplePanel.setBorder(BorderFactory.createMatteBorder(20, 20, 20, 20, 
							   getBackground()));
        String labelText = textSource.getI18NText(TextKeys.SAMPLE, 
						  "-- SAMPLE --");
        samplePanel.add(
            new JLabel(labelText), BorderLayout.NORTH);
        sampleArea = new JLabel();
        sampleArea.setBackground(Color.white);
        sampleArea.setHorizontalAlignment(SwingConstants.CENTER);
	sampleArea.setVerticalAlignment(SwingConstants.CENTER );
        sampleArea.setPreferredSize(
            new Dimension(250, 90));
        samplePanel.add(sampleArea, BorderLayout.CENTER);
        return samplePanel;
        }

    /**
     * Factorization. Gets list of available fonts, and 
     * filters out java-specific ones (which have a dot in them).
     * Returns filtered array of Strings.
     */
    protected String[] filterFontFamilies()
        {
        String[] allFamilies = 
	  GraphicsEnvironment.getLocalGraphicsEnvironment().getAvailableFontFamilyNames();
        Vector allVector = new Vector(allFamilies.length);
        for (int i = 0; i < allFamilies.length; i++)
            {
            String fontName = allFamilies[i];
            int pos = fontName.indexOf(".");
            if (pos < 0)
                {
                allVector.add(fontName);
                }
            }
        String[] filteredFamilies = new String[allVector.size()];
        for (int i = 0; i < allVector.size(); i++)
            {
            String fontName = (String)allVector.elementAt(i);
            filteredFamilies[i] = fontName;
            }
        return filteredFamilies;
        }

    /**
     * Factorization. Initialize the default indexes to the
     * application default.
     */
   protected void initializeDefaults()
       {
       defaultSizeIndex = 3;  // 14 point
       defaultStyleIndex = 0; // Plain
       for (int i = 0; i < fontFamilies.length; i++)
	   {
           if (fontFamilies[i].compareTo(DFLT_FACE) == 0)
	       {
               defaultFamilyIndex = i;
               break;
               }
	   }
       }

    /**
     * Display the font dialog and allow the user to choose a font, 
     * style and size.
     * @param title  Title for font dialog
     * @return String concatenating name,size and style.
     */
    public String chooseFont(String title)
        {
        selectedFont = null;
        setDefaults();
        setTitle(title);
        setLocationRelativeTo(parent);
        setVisible(true);
        return selectedFont;
        }

    /** Set default values. */
    protected void setDefaults()
        {
        nameList.setSelectedIndex(defaultFamilyIndex);
        nameList.ensureIndexIsVisible(defaultFamilyIndex);
        sizeList.setSelectedIndex(defaultSizeIndex);
        sizeList.ensureIndexIsVisible(defaultSizeIndex);
        styleList.setSelectedIndex(defaultStyleIndex);
        styleList.ensureIndexIsVisible(defaultStyleIndex);
        setDefaultBox.setSelected(true);
        }

    /** Returns true if all three components of the font have some 
     * selected value. Otherwise, returns false. 
     */
    protected boolean fontDefined()
        {
        if ((lastFamilyIndex < 0) || (lastStyleIndex < 0) || (lastSizeIndex < 0))
            return false;
        else
            return true;
        }

    /** Show a sample of the selected font. */
    protected void showSampleString(String family, int style, int size)
        {
        sampleArea.setFont(
            new Font(family, style, size-2));
        sampleArea.setText("ABC DEF");
        sampleArea.setFont(
            new Font(family, style, size));
        sampleArea.setText(sampleText);
        }

    /** Clear sample area */
    protected void clearSampleString()
        {
        sampleArea.setText("");
        }

    /** Event Listener methods */
    public void actionPerformed(ActionEvent e)
        {
        Object source = e.getSource();
        if (source == okButton)
            {
            if (setDefaultBox.isSelected())
                {
                defaultFamilyIndex = lastFamilyIndex;
                defaultSizeIndex = lastSizeIndex;
                defaultStyleIndex = lastStyleIndex;
                }
            setVisible(false);
            }
        else if (source == cancelButton)
            {
            selectedFont = null;
            setVisible(false);
            }
        }

    public void valueChanged(ListSelectionEvent e)
        {
        Object source = e.getSource();
        if (source == nameList)
            {
            lastFamilyIndex = nameList.getSelectedIndex();
            }
        else if (source == sizeList)
            {
            lastSizeIndex = sizeList.getSelectedIndex();
            }
        else if (source == styleList)
            {
            lastStyleIndex = styleList.getSelectedIndex();
            }
        if (fontDefined())
            {
            StringBuffer temp = new StringBuffer();
            temp.append(fontFamilies[lastFamilyIndex] + "-");
            temp.append(styles[lastStyleIndex] + "-");
            temp.append(String.valueOf(sizes[lastSizeIndex]));
            selectedFont = temp.toString();
            showSampleString(fontFamilies[lastFamilyIndex], 
                             styleConstants[lastStyleIndex], 
                             sizes[lastSizeIndex]);
            okButton.setEnabled(true);
            setDefaultBox.setEnabled(true);
            }
        else
            {
            clearSampleString();
            selectedFont = null;
            okButton.setEnabled(false);
            setDefaultBox.setEnabled(false);
            }
        }

      /**
       * Return the default last set, in the Face-Style-Size
       * format. If no defaults set, return the base level default
       */
    public String getCurrentDefault()
        {
	StringBuffer temp = new StringBuffer();
        temp.append(fontFamilies[defaultFamilyIndex] + "-");
        temp.append(styles[defaultStyleIndex]+"-");
        temp.append(String.valueOf(sizes[defaultSizeIndex]));
        return temp.toString();
	}

    /**
     * Respond to the user's attempt to close the window 
     * using operating-system-specific mechanisms by making closing
     * the window be equivalent to a Cancel.
     */
    public void windowClosing(WindowEvent we)
        {
        selectedFont = null;
        }

    /** Other window listener methods are empty */
    public void windowActivated(WindowEvent we) { };

    public void windowClosed(WindowEvent we) { };

    public void windowDeactivated(WindowEvent we) { };

    public void windowDeiconified(WindowEvent we) { };

    public void windowIconified(WindowEvent we) { };

    public void windowOpened(WindowEvent we) { };


    protected static String cvsInfo = null;
    protected static void setCvsInfo()
        {
        cvsInfo = "\n@(#)  $Id: DragonFontChooser.java,v 1.5 2007/01/05 07:41:57 rudahl Exp $ \n";
	}
    }







