#  ~~ Copyright 2004-2014 Kurt Rudahl and Sally Goldin
#  ~~ EndC
#
# Makefile for generic GUI Java classes under Linux or Mingw
# Sally Goldin 12/10/2004
# $Id: Makefile,v 1.9.2.1 2014/02/21 07:57:47 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.9.2.1  2014/02/21 07:57:47  rudahl
# cleaner clean
#
# Revision 1.9  2007/01/02 05:19:19  goldin
# Complete behavioral code for Rule Creation panel
#
# Revision 1.8  2007/01/01 13:52:16  goldin
# Add and integrate new controls for rule creation screen
#
# Revision 1.7  2006/12/25 10:48:37  goldin
# Begin implementation of multi-select file control
#
# Revision 1.6  2006/07/23 09:12:22  goldin
# Attempt to switch to using Java 1.5 (Axel/Windows only)
#
# Revision 1.5  2006/02/24 13:51:40  rudahl
# cleanup useless build messages
#
# Revision 1.4  2005/12/20 08:14:17  goldin
# Add FontProcessor
#
# Revision 1.3  2005/04/08 04:33:09  goldin
# Change javadoc handling
#
# Revision 1.2  2005/03/28 06:58:05  goldin
# Change DRAGONROOT to COMMONROOT
#
# Revision 1.1  2005/03/27 06:19:03  goldin
# Rename MakeLinux
#
# Revision 1.3  2005/02/05 13:37:18  goldin
# In makefiles need to create directories before doing copies
#
# Revision 1.2  2004/12/11 04:57:25  rudahl
# clean target zaps .h files
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#
#

.SUFFIXES : .java .class

#rule for creating class files
.java.class :
	$(DRAGON_JAVA)/bin/javac $*.java

CLASSFILES = \
	ApplicationManager.class \
	BrowseButton.class \
	Callback.class \
	DButtonField.class \
	DCheckField.class \
	DCheckMenuItem.class \
	DComboField.class \
	DebugNativeHost.class \
	DFileChooserModel.class \
	DFileField.class \
        DFileMultiChooserModel.class \
	DFileType.class \
	DFixedText.class \
	DFontField.class \
        DListBox.class \
	DMenuItem.class \
	DMultiFileField.class \
	DoubleValidator.class \
	DRadioBox.class \
	DTextField.class \
	DirTreeModel.class \
	DirTreeNode.class \
	DragonDirTree.class \
	DragonField.class \
	DragonFileChooser.class \
	DragonFileList.class \
	DragonFontChooser.class \
	DragonMenu.class \
	DragonMenuItem.class \
	DragonMultiFileList.class \
	DragonPanel.class \
	DRangeControl.class \
	DriveTester.class \
	EnumBase.class \
	ErrorDisplay.class \
	FilenameDocument.class \
	FileReference.class \
	FileReferenceComparator.class \
	FixedLengthDocument.class \
	FontProcessor.class \
	GenErrorDisplay.class \
	GenHelpDisplayListener.class \
	I18NTextSource.class \
	Initializer.class \
	IntegerValidator.class \
	Logger.class \
	MemoryFilter.class \
	MessageDisplay.class \
	NativeHost.class \
	RangeValidator.class \
	Splash.class \
	StubNativeHost.class \
	TextKeys.class \
	Tracer.class \
	Validator.class \
	ValueLimits.class \
	XMLTag.class \
	XmlToUiBuilder.class 

all : $(CLASSFILES)
	$(DRAGON_JAVA)/bin/javah -jni -o DriveTester.h com.grs.gui.DriveTester
#	-mkdir $(COMMONROOT)/lib
	-@mkdir -p $(COMMONROOT)/lib/genfiles
	cp DriveTester.h $(COMMONROOT)/lib/genfiles

clean : 
	-@rm *.class *.jar *.jnk *.tmp *.log *.h 2> /dev/null
