# -----------------------------------------------------------------
# This file contains the build information necessary to create
# the VIEWPORT Java classes for DRAGON/ips under Linux or Mingw
#
# ~~ Copyright 2004-2015 Sally Goldin and Kurt Rudahl
# ~~ EndC
#
# -----------------------------------------------------------------
#
# $Id: Makefile,v 1.9.2.4 2015/01/01 10:33:22 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.9.2.4  2015/01/01 10:33:22  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.9.2.3  2014/02/21 07:59:39  rudahl
# cleaner clean
#
# Revision 1.9.2.2  2010/10/04 05:13:52  rudahl
# changed args for javah
#
# Revision 1.9.2.1  2010/10/03 11:21:41  goldin
# add functions for new ViewportMenu class
#
# Revision 1.6  2006/02/24 13:52:45  rudahl
# cleanup useless build messages
#
# Revision 1.5  2006/02/17 07:19:48  rudahl
# simplified mkdir
#
# Revision 1.4  2005/11/22 03:25:40  goldin
# Add jniframe
#
# Revision 1.3  2005/04/08 04:33:09  goldin
# Change javadoc handling
#
# Revision 1.2  2005/03/28 06:58:05  goldin
# Change DRAGONROOT to COMMONROOT
#
# Revision 1.1  2005/03/27 06:17:52  goldin
# Rename MakeLinux
#
# Revision 1.5  2005/03/27 06:01:45  goldin
# Add forTest targets
#
# Revision 1.4  2004/12/12 06:39:01  goldin
# Change colorGridCanvas to plain JPanel to fix delay problem 
# - also add inner class to makefiles
#
# Revision 1.3  2004/12/11 04:59:16  rudahl
# clean target zaps classes tree
#
# Revision 1.2  2004/12/11 04:52:44  rudahl
# bad caps in metricCanvas
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#

# must keep viewProg.h as last target
RESULTS		=directories $(JAVA_CLASSES) viewProg.jar viewProg.h

# file lists

JAVA_CLASSES	=\
		ColorChooser.class \
		ColorEdit.class \
		ColorFileProcessor.class \
		InfoText.class \
		InfoViewport.class \
	        JniDialog.class \
	        JniFrame.class \
		PromptAndReply.class\
		PromptAndReply$$ColorPanel.class\
		LoggerOutputStream.class \
		ViewFileChooser.class \
		viewProg.class \
		viewButtonPanel.class \
		ViewportMenu.class \
		ViewportNativeHost.class \
		ViewportWindowMonitor.class

UTIL_CLASSES	=\
		../../util/PackerLayout.class \
		../../util/PackerLayout$$PackRecord.class \
		../../util/PackingException.class \
		../../util/Parse.class \
		../../util/Smallfile.class \
		../../util/StringSplitter.class \
		../../util/StringWrapper.class

METRIC_CLASSES	= ../../metricCanvas/ColorGrid.class \
	../../metricCanvas/ColorGridCanvas.class \
	../../metricCanvas/DefectiveStructureException.class \
	../../metricCanvas/GriddedMetric.class\
	../../metricCanvas/GriddedPlaneSpace.class\
	../../metricCanvas/LinearMetric.class\
	../../metricCanvas/LinearPlaneSpace.class\
	../../metricCanvas/Metric.class\
	../../metricCanvas/PlaneSpace.class\
	../../metricCanvas/PlotGraph.class\
	../../metricCanvas/Ruler.class\
	../../metricCanvas/Space.class 

GUI_CLASSES = \
	../../gui/ApplicationManager.class \
	../../gui/BrowseButton.class \
	../../gui/Callback.class \
	../../gui/DButtonField.class \
	../../gui/DCheckField.class \
	../../gui/DCheckMenuItem.class \
	../../gui/DComboField.class \
	../../gui/DebugNativeHost.class \
	../../gui/DFileChooserModel.class \
	../../gui/DFileField.class \
	../../gui/DFileType.class \
	../../gui/DFixedText.class \
	../../gui/DFontField.class \
	../../gui/DMenuItem.class \
	../../gui/DoubleValidator.class \
	../../gui/DRadioBox.class \
	../../gui/DTextField.class \
	../../gui/DirTreeModel.class \
	../../gui/DirTreeNode.class \
	../../gui/DragonDirTree.class \
	../../gui/DragonField.class \
	../../gui/DragonFileChooser.class \
	../../gui/DragonFileList.class \
	../../gui/DragonFontChooser.class \
	../../gui/DragonMenu.class \
	../../gui/DragonMenuItem.class \
	../../gui/DragonPanel.class \
	../../gui/DriveTester.class \
	../../gui/EnumBase.class \
	../../gui/ErrorDisplay.class \
	../../gui/FixedLengthDocument.class \
	../../gui/GenErrorDisplay.class \
	../../gui/GenHelpDisplayListener.class \
	../../gui/I18NTextSource.class \
	../../gui/Initializer.class \
	../../gui/IntegerValidator.class \
	../../gui/Logger.class \
	../../gui/MemoryFilter.class \
	../../gui/MessageDisplay.class \
	../../gui/NativeHost.class \
	../../gui/Splash.class \
	../../gui/StubNativeHost.class \
	../../gui/TextKeys.class \
	../../gui/Tracer.class \
	../../gui/Validator.class \
	../../gui/ValueLimits.class \
	../../gui/XMLTag.class \
	../../gui/XmlToUiBuilder.class 

%.class : %.java
	javac $<
	-@echo "   "

all : ENTER $(RESULTS) EXIT
	@echo Finished with VIEWPORT

ENTER :
	-@echo "   "
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

install : $(RESULTS)
	cp -p viewProg.jar $(PRODUCTROOT)/lib/jar

forTest :
#	cp -p viewProg.jar $(TESTDIR)


#############################################################################

viewProg.h : viewProg.class
	cd ../../../..
	javah -o viewProg.h com.grs.dragon.viewport.viewProg
	cp -p viewProg.h $(COMMONROOT)/lib/genfiles
#	javap -s com.grs.dragon.viewport.viewProg 

viewProg.jar : $(JAVA_CLASSES) $(UTIL_CLASSES) $(GUI_CLASSES) \
		../../metricCanvas/metricCanvas.jar
	-@rm $*.jar 2> /dev/null
	-@rm classes/com/grs/dragon/viewport/* 2> /dev/null
	cp *.class classes/com/grs/dragon/viewport
	cp ../../util/*.class classes/com/grs/util
	cp ../../gui/*.class classes/com/grs/gui
	cp ../../metricCanvas/*.class classes/com/grs/metricCanvas
	jar -cvf viewProg.jar -C ./classes com > /dev/null
	cp -p viewProg.jar $(PRODUCTROOT)/lib/jar
	@rm -rf classes 2> /dev/null

directories : 
#	-mkdir classes
#	-mkdir classes/com
#	-mkdir classes/com/grs
	-@mkdir -p classes/com/grs/gui
	-@mkdir -p classes/com/grs/util
	-@mkdir -p classes/com/grs/metricCanvas
	-@mkdir -p classes/com/grs/dragon
	-@mkdir -p classes/com/grs/dragon/viewport

clean :
	-@rm -r *.class *.jnk viewProg.h viewProg.jar *.h classes 2> /dev/null
