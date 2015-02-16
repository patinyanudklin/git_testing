# Makefile for Dragon Java UI components under Linux or Mingw
# Sally Goldin 12/10/2004
# $Id: Makefile,v 1.27.2.2 2015/01/01 10:33:22 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.27.2.2  2015/01/01 10:33:22  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.27.2.1  2014/02/21 07:59:39  rudahl
# cleaner clean
#
# Revision 1.27  2007/06/16 10:39:47  rudahl
# improved progress msgs
#
# Revision 1.26  2007/06/01 06:42:12  goldin
# copy jar files to product-specific tree after building
#
# Revision 1.25  2007/02/17 10:20:57  goldin
# Make F1 cause a focus loss so that callbacks will execute
#
# Revision 1.24  2007/02/15 11:16:37  goldin
# Add initializer to clear multi-select file boxes when we enter a panel
#
# Revision 1.23  2007/01/02 05:19:19  goldin
# Complete behavioral code for Rule Creation panel
#
# Revision 1.22  2007/01/01 13:53:55  goldin
# Added panel for rule creation
#
# Revision 1.21  2006/12/29 03:13:30  goldin
# Get rid of ugly gifs for multi file chooser
#
# Revision 1.20  2006/12/25 10:49:02  goldin
# Begin implementation of multi-select file control
#
# Revision 1.19  2006/12/09 12:44:59  goldin
# change help to be a popup
#
# Revision 1.18  2006/11/18 10:52:55  goldin
# Implementing Import user interface
#
# Revision 1.17  2006/11/13 14:13:34  goldin
# implementing UI for PCA
#
# Revision 1.16  2006/07/23 09:12:22  goldin
# Attempt to switch to using Java 1.5 (Axel/Windows only)
#
# Revision 1.15  2006/02/24 13:51:40  rudahl
# cleanup useless build messages
#
# Revision 1.14  2006/02/17 07:19:48  rudahl
# simplified mkdir
#
# Revision 1.13  2005/12/08 08:02:45  goldin
# Use images to illustrate language, not text, to avoid font problems
#
# Revision 1.12  2005/10/29 02:58:26  rudahl
# drag5-00.messages is now a source file
#
# Revision 1.11  2005/09/15 08:30:09  goldin
# Move color chooser to UI package, invoke directly from the UI
#
# Revision 1.10  2005/07/31 08:34:31  goldin
# Working in I18N of Installer
#
# Revision 1.9  2005/07/31 05:41:06  goldin
# Don't implement 'install' targets right now
#
# Revision 1.8  2005/07/29 09:39:54  goldin
# Add DragonLanguageCallback.java
#
# Revision 1.7  2005/06/27 03:12:42  rudahl
# fixed dest. name for dImageGeader.h
#
# Revision 1.6  2005/04/08 04:33:09  goldin
# Change javadoc handling
#
# Revision 1.5  2005/04/05 06:12:39  rudahl
# adapt to creating better test environment
#
# Revision 1.4  2005/04/04 08:51:20  goldin
# Add command to copy product-specific files before build
#
# Revision 1.3  2005/04/01 08:53:21  goldin
# Refinements to get JNI fns working
#
# Revision 1.2  2005/03/30 12:39:45  goldin
# Add lines to generate JNI header file
#
# Revision 1.1  2005/03/27 06:17:20  goldin
# Rename MakeLinux
#
# Revision 1.5  2005/03/27 06:01:45  goldin
# Add forTest targets
#
# Revision 1.4  2005/02/06 13:56:54  goldin
# implement user-based customization
#
# Revision 1.3  2005/02/05 13:37:18  goldin
# In makefiles need to create directories before doing copies
#
# Revision 1.2  2004/12/15 03:50:59  goldin
# Add callback to handle annotation option more intelligently; update makefile and panel file
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
  AboutCallback.class \
  AboutDialog.class \
  AddRuleCallback.class \
  AddTextCallback.class \
  AnnotationCallback.class \
  CalcResultParser.class \
  ChooseColorsCallback.class \
  ClfFileValidator.class \
  ColorChooser.class \
  ColorEdit.class \
  ColorFileCallback.class \
  ColorFileProcessor.class \
  CommandForwarder.class \
  CommandLine.class \
  CustomizeExpert.class \
  DImageHeader.class \
  DismissCallback.class \
  DisplayTypeCallback.class \
  DragonApp.class \
  DragonLanguageCallback.class \
  DragonUI.class \
  DragonUI$$ButtonInvoker.class \
  EchoCallback.class \
  ExecCmdCallback.class \
  ExecScriptCallback.class \
  ExitCallback.class \
  FileListCallback.class \
  FileTypeValidator.class \
  FileValidator.class \
  FilterValCallback.class \
  FontInitializer.class \
  GCPCallback.class \
  GCPRefImgCallback.class \
  HeaFileTypeCallback.class \
  HeaderCallback.class \
  HelpDisplayListener.class \
  HelpDisplayListener$$HelpHelper.class \
  HelpEditor.class \
  ImageEnableCallback.class \
  ImgFileDetailCallback.class \
  ImgHeaderCallback.class \
  ImportImageTypeCallback.class \
  ImportModeCallback.class \
  LoggingCallback.class \
  MemoryImageInitializer.class \
  MessagesExhaustedDetector.class \
  MultiSelectInitializer.class \
  NoPanelCallback.class \
  NullCommandForwarder.class \
  PathInitializer.class \
  PerformanceReporter.class \
  ProgressBar.class \
  ProgressDetector.class \
  QueryDialogCallback.class \
  RecodeCallback.class \
  RegressionCallback.class \
  ResizeListener.class \
  SaveRulesCallback.class \
  ScalingCallback.class \
  ScriptCancelCallback.class \
  ScriptControlPanel.class \
  ScriptPauseCallback.class \
  ScriptRestartCallback.class \
  ServerQueryProcessor.class \
  SetOnePathCallback.class \
  SetPathsCallback.class \
  SetScriptStateCallback.class \
  ShortPathValidator.class \
  SigBoundsValidator.class \
  SigFileCallback.class \
  SigFileInitializer.class \
  SigFileProcessor.class \
  SigFileValidator.class \
  SigModCallback.class \
  SpecialCommand.class \
  StatusManager.class \
  TableDisplay.class \
  UiErrorDisplay.class \
  UiIncomingCommandProcessor.class \
  UiMessageDetector$$HistoryRefresher.class \
  UiMessageDetector.class \
  UiMessageDisplay.class \
  UiReplyMonitor.class \
  UserManualCallback.class \
  UserStretchCallback.class \
  VectorMergeCallback.class \
  WindowMonitor.class 

COMMONCLASSFILES=\
  ../common/ConfigFileProcessor.class \
  ../common/LanguageCallback.class \
  ../common/PathChecker.class \
  ../common/SimpleWindowMonitor.class 

IPCCLASSFILES =\
  ../ipc/CompletionListener.class \
  ../ipc/FileDetector.class \
  ../ipc/IncomingCommandProcessor.class \
  ../ipc/IpcFile.class \
  ../ipc/MessageDetector.class \
  ../ipc/ReplyMonitor.class 

UTILCLASSFILES=\
  ../../util/StringWrapper.class 

GUICLASSFILES=\
../../gui/ApplicationManager.class \
../../gui/BrowseButton.class \
../../gui/Callback.class \
../../gui/DButtonField.class \
../../gui/DCheckField.class \
../../gui/DCheckMenuItem.class \
../../gui/DComboField.class \
../../gui/DFileChooserModel$$CaseInsensitiveComparator.class \
../../gui/DFileChooserModel.class \
../../gui/DFileField.class \
../../gui/DFileMultiChooserModel.class \
../../gui/DFileType.class \
../../gui/DFixedText.class \
../../gui/DFontField.class \
../../gui/DMenuItem.class \
../../gui/DListBox.class \
../../gui/DMultiFileField.class \
../../gui/DRadioBox.class \
../../gui/DTextField$$FocusRequestor.class \
../../gui/DTextField.class \
../../gui/DebugNativeHost.class \
../../gui/DirTreeModel.class \
../../gui/DirTreeNode.class \
../../gui/DoubleValidator.class \
../../gui/DragonDirTree.class \
../../gui/DragonField.class \
../../gui/DragonFileChooser.class \
../../gui/DragonFileList$$FilterSetter.class \
../../gui/DragonFileList.class \
../../gui/DragonFontChooser.class \
../../gui/DragonMenu.class \
../../gui/DragonMenuItem.class \
../../gui/DragonMultiFileList.class \
../../gui/DragonPanel.class \
../../gui/DRangeControl.class \
../../gui/DriveTester.class \
../../gui/EnumBase.class \
../../gui/ErrorDisplay.class \
../../gui/FileReference.class \
../../gui/FileReferenceComparator.class \
../../gui/FilenameDocument.class \
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
../../gui/RangeValidator.class \
../../gui/Splash.class \
../../gui/StubNativeHost.class \
../../gui/TextKeys.class \
../../gui/Tracer.class \
../../gui/Validator.class \
../../gui/ValueLimits.class \
../../gui/XMLTag.class \
../../gui/XmlToUiBuilder.class 

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

GIFFILES = \
	cancel.gif \
	downArrow.gif \
	dragexec.gif \
	draglogo.gif \
	nextstep.gif \
	pause.gif \
	restart.gif \
	resume.gif

INSTALLFILES = \
	dragonui.jar \
	$(PRODUCTROOT)/system/MENU.XML $(PRODUCTROOT)/system/PANEL.XML \
	$(GIFFILES) ../common/*.gif dragbanr.jpg \
	drag5-00.messages

all : ENTER directories $(GUICLASSFILES) $(UTILCLASSFILES) \
		$(IPCCLASSFILES) $(COMMONCLASSFILES) $(METRIC_CLASSES) \
		$(CLASSFILES) dragonui.jar EXIT # drag5-00.messages
	cd $(COMMONROOT)/javasrc
	$(DRAGON_JAVA)/bin/javah -jni -o DImageHeader.h com.grs.dragon.ui.DImageHeader
#	-mkdir $(COMMONROOT)/lib
	-@mkdir -p $(COMMONROOT)/lib/genfiles 2> /dev/null
	cp DImageHeader.h $(COMMONROOT)/lib/genfiles/dImageHeader.h
	cd $(COMMONROOT)/javasrc/com/grs/dragon/ui

ENTER :
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

dragonui.jar : $(GUICLASSFILES) $(IPCCLASSFILES) $(COMMONCLASSFILES) \
	$(CLASSFILES) $(METRIC_CLASSES) DragonUI.properties
	-@rm $*.jar 2> /dev/null
	-@rm classes/com/grs/dragon/ui/* 2> /dev/null
	cp *.class classes/com/grs/dragon/ui
	cp ../ipc/*.class classes/com/grs/dragon/ipc
	cp ../common/*.class  classes/com/grs/dragon/common
	cp ../common/*.gif classes/com/grs/dragon/common
	cp ../../gui/*.class classes/com/grs/gui
	cp ../../util/*.class classes/com/grs/util
	cp ../../metricCanvas/*.class  classes/com/grs/metricCanvas
	$(DRAGON_JAVA)/bin/jar -0cvf dragonui.jar DragonUI.properties > /dev/null
	$(DRAGON_JAVA)/bin/jar -0uvf dragonui.jar -C ./classes com > /dev/null
	cp dragonui.jar $(PRODUCTROOT)/lib/jar
	@rm -rf classes

#drag5-00.messages : drag5-00.ascii
#	native2ascii -reverse -encoding UTF8 drag5-00.ascii > drag5-00.messages

#install :
#	-mkdir $(DRAGON_BUILD_DIR)
#	cp -p $(INSTALLFILES) $(DRAGON_BUILD_DIR)

forTest :
	cp -p $(INSTALLFILES) $(TESTDIR)

directories : 
#	-mkdir classes
#	-mkdir classes/com
#	-mkdir classes/com/grs
	-@mkdir -p classes/com/grs/gui 2> /dev/null
	-@mkdir -p classes/com/grs/util 2> /dev/null
	-@mkdir -p classes/com/grs/metricCanvas 2> /dev/null
#	-mkdir classes/com/grs/dragon
	-@mkdir -p classes/com/grs/dragon/ui 2> /dev/null
	-@mkdir -p classes/com/grs/dragon/common 2> /dev/null
	-@mkdir -p classes/com/grs/dragon/ipc 2> /dev/null
	-@mkdir -p $(PRODUCTROOT)/lib/jar 2> /dev/null
	cp $(PRODUCTROOT)/javasrc/com/grs/dragon/ui/AboutDialog.java .
clean : 
	-@rm *.class dragonui.jar *.jnk *.tmp *.log AboutDialog.java DImageHeader.h 2> /dev/null
	-@rm -r classes  2> /dev/null

