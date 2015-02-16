# Makefile for Installer classes under Linux or Mingw
#  Created by Sally Goldin, 12/10/2004
#  $Id: Makefile,v 1.15.2.2 2011/09/24 03:17:07 rudahl Exp $
#  $Log: Makefile,v $
#  Revision 1.15.2.2  2011/09/24 03:17:07  rudahl
#  purge some driver code
#
#  Revision 1.15.2.1  2010/09/10 10:10:35  rudahl
#  adapt for Java 1.6
#
#  Revision 1.15  2007/06/16 10:36:58  rudahl
#  improved progress msgs
#
#  Revision 1.14  2007/06/06 11:40:41  goldin
#  Fix makefiles to copy jar files to product-specific directory
#
#  Revision 1.13  2006/07/23 09:12:22  goldin
#  Attempt to switch to using Java 1.5 (Axel/Windows only)
#
#  Revision 1.12  2006/03/07 09:33:59  rudahl
#  fix error in clean
#
#  Revision 1.11  2006/02/24 13:51:40  rudahl
#  cleanup useless build messages
#
#  Revision 1.10  2006/02/17 07:19:48  rudahl
#  simplified mkdir
#
#  Revision 1.9  2005/12/20 08:14:17  goldin
#  Add FontProcessor
#
#  Revision 1.8  2005/12/08 08:02:55  goldin
#  Use images to illustrate language, not text, to avoid font problems
#
#  Revision 1.7  2005/07/31 08:34:31  goldin
#  Working in I18N of Installer
#
#  Revision 1.6  2005/07/31 05:41:00  goldin
#  Don't implement 'install' targets right now
#
#  Revision 1.5  2005/07/29 09:42:08  goldin
#  Add Language selection functionality
#
#  Revision 1.4  2005/04/08 04:33:09  goldin
#  Change javadoc handling
#
#  Revision 1.3  2005/03/28 06:58:05  goldin
#  Change DRAGONROOT to COMMONROOT
#
#  Revision 1.2  2005/03/27 06:13:54  goldin
#  take out misleading comment
#
#  Revision 1.1  2005/03/27 06:13:22  goldin
#  Rename MakeLinux
#
#  Revision 1.5  2004/12/23 10:52:04  rudahl
#  got rid of explicit paths to executables
#
#  Revision 1.4  2004/12/15 03:08:49  goldin
#  Update to use Java 1.4 for all of Dragon Java and JNI
#
#  Revision 1.3  2004/12/14 09:43:54  rudahl
#  added -p
#
#  Revision 1.2  2004/12/11 05:01:16  rudahl
#  clean target zaps copied gif, jpg files
#
#  Revision 1.1  2004/12/10 12:15:31  goldin
#  Add new Make files for Linux
#
#

.SUFFIXES : .java .class

#rule for creating class files
.java.class :
	javac $*.java

CLASSFILES = \
	DataPathInitializer.class \
	InstallCleanupCallback.class \
	Installer.class \
	InstallerLanguageCallback.class \
	Installer$$ReadMe.class \
	InstallFileManager.class \
	InstallFileManager$$FileChecker.class \
	InstallFileManager$$FileCopier.class \
	InstallFileManager$$FileCopySpec.class \
	InstallFileValidator.class \
	InstallSamplesCallback.class \
	KeyNumValidator.class \
	SamplePathCallback.class \
	SerialNumValidator.class 

COMMONCLASSFILES=\
  ../common/ConfigFileProcessor.class \
  ../common/LanguageCallback.class \
  ../common/PathChecker.class \
  ../common/SimpleWindowMonitor.class 

GUICLASSFILES=\
  ../../gui/ApplicationManager.class \
  ../../gui/BrowseButton.class \
  ../../gui/Callback.class \
  ../../gui/DButtonField.class \
  ../../gui/DCheckField.class \
  ../../gui/DCheckMenuItem.class \
  ../../gui/DComboField.class \
  ../../gui/DFileChooserModel.class \
  ../../gui/DFileChooserModel$$CaseInsensitiveComparator.class \
  ../../gui/DFileField.class \
  ../../gui/DFileType.class \
  ../../gui/DFixedText.class \
  ../../gui/DFontField.class \
  ../../gui/DMenuItem.class \
  ../../gui/DoubleValidator.class \
  ../../gui/DRadioBox.class \
  ../../gui/DTextField.class \
  ../../gui/DTextField$$FocusRequestor.class \
  ../../gui/DirTreeModel.class \
  ../../gui/DirTreeNode.class \
  ../../gui/DragonDirTree.class \
  ../../gui/DragonField.class \
  ../../gui/DragonFileChooser.class \
  ../../gui/DragonFileList.class \
  ../../gui/DragonFileList$$FilterSetter.class \
  ../../gui/DragonFontChooser.class \
  ../../gui/DragonMenu.class \
  ../../gui/DragonMenuItem.class \
  ../../gui/DragonPanel.class \
  ../../gui/DriveTester.class \
  ../../gui/EnumBase.class \
  ../../gui/ErrorDisplay.class \
  ../../gui/FileReference.class \
  ../../gui/FileReferenceComparator.class \
  ../../gui/FilenameDocument.class \
  ../../gui/FixedLengthDocument.class \
  ../../gui/FontProcessor.class \
  ../../gui/GenErrorDisplay.class \
  ../../gui/GenHelpDisplayListener.class \
  ../../gui/I18NTextSource.class \
  ../../gui/Initializer.class \
  ../../gui/IntegerValidator.class \
  ../../gui/Logger.class \
  ../../gui/MemoryFilter.class \
  ../../gui/MessageDisplay.class \
  ../../gui/Splash.class \
  ../../gui/TextKeys.class \
  ../../gui/Tracer.class \
  ../../gui/Validator.class \
  ../../gui/ValueLimits.class \
  ../../gui/XMLTag.class \
  ../../gui/XmlToUiBuilder.class 

UI_FILES	=../ui/dragexec.gif \
		../ui/downArrow.gif \
		../ui/dragbanr.jpg \

all : ENTER directories $(GUICLASSFILES) $(COMMONCLASSFILES) $(CLASSFILES) \
	installer.jar serialnumvalidator.h installer.h EXIT

ENTER :
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

installer.jar : $(GUICLASSFILES) $(COMMONCLASSFILES) \
	$(CLASSFILES) 
	-@rm $*.jar 2> /dev/null
	cp -p $(UI_FILES) .
	cp -p *.class classes/com/grs/dragon/installer
	cp -p ../common/*.class classes/com/grs/dragon/common
	cp -p ../common/*.gif classes/com/grs/dragon/common
	cp -p ../../gui/*.class classes/com/grs/gui
	jar -cvfm installer.jar *.gif MANIFEST.MF
	jar -uvf installer.jar -C ./classes com > /dev/null
	cp installer.jar $(PRODUCTROOT)/lib/jar
	@rm -rf classes

directories : 
	-@mkdir -p classes/com/grs/gui
	-@mkdir -p classes/com/grs/dragon/common
	-@mkdir -p classes/com/grs/dragon/installer
	-@mkdir -p $(PRODUCTROOT)/lib/jar

serialnumvalidator.h : SerialNumValidator.class
	$(DRAGON_JAVA)/bin/javah -o serialnumvalidator.h com.grs.dragon.installer.SerialNumValidator
	cp -p serialnumvalidator.h $(COMMONROOT)/lib/genfiles

installer.h : InstallFileManager.class
	$(DRAGON_JAVA)/bin/javah -o installer.h com.grs.dragon.installer.InstallFileManager
	cp -p installer.h $(COMMONROOT)/lib/genfiles

clean : 
	-@rm -rf classes 2> /dev/null
	-@rm *.class *.jar *.jnk *.tmp *.log *.h *.gif dragbanr.jpg *~ 2> /dev/null
