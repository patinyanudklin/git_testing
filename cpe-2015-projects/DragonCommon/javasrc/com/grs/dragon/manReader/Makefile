# Makefile for Dragon manual reader Java components under Linux or Mingw
# Sally Goldin 12/10/2004
#
# ~~ Copyright 2004-2015 Sally Goldin and Kurt Rudahl
# ~~ EndC
#
# $Id: Makefile,v 1.9.2.2 2015/01/01 10:32:30 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.9.2.2  2015/01/01 10:32:30  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.12  2014/12/29 03:32:45  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.11  2014/02/22 13:27:27  rudahl
# cleaner clean
#
# Revision 1.10  2014/02/09 04:34:58  rudahl
# suppress irritating messages during clean
#
# Revision 1.9  2007/06/16 10:39:47  rudahl
# improved progress msgs
#
# Revision 1.8  2007/06/01 06:42:24  goldin
# copy jar files to product-specific tree after building
#
# Revision 1.7  2007/05/13 07:45:41  goldin
# Make manreader title reflect the product name
#
# Revision 1.6  2006/07/23 09:12:22  goldin
# Attempt to switch to using Java 1.5 (Axel/Windows only)
#
# Revision 1.5  2006/03/04 09:33:56  goldin
# *** empty log message ***
#
# Revision 1.4  2006/02/24 13:52:45  rudahl
# cleanup useless build messages
#
# Revision 1.3  2005/08/01 07:08:24  rudahl
# error in jar generation
#
# Revision 1.2  2005/04/05 06:12:39  rudahl
# adapt to creating better test environment
#
# Revision 1.1  2005/03/27 06:15:02  goldin
# Rename MakeLinux
#
# Revision 1.3  2005/03/27 06:01:45  goldin
# Add forTest targets
#
# Revision 1.2  2004/12/11 05:34:49  rudahl
# added tilde files to clean
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#
#

# NOTE: assumes that com/grs/gui, com/grs/ipc, com/grs/common built
# before this directory

.SUFFIXES : .java .class

#rule for creating class files
.java.class :
	$(DRAGON_JAVA)/bin/javac $*.java
	-@echo "   "

GIFS	=closbook.gif openbook.gif mricon.gif

RESULTS		=manreader.jar $(GIFS)

CLASSFILES = \
	DragonHtmlPane.class \
	ManReader.class \
	MRIncomingCommandProcessor.class \
	RemoveWindowCallback.class \
	TocTreeModel.class \
	TocTreeNode.class \
	TocTreePanel.class \
	XmlToTocBuilder.class
 
all : ENTER directories $(CLASSFILES) manreader.jar EXIT

ENTER :
	-@echo "   "
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

manreader.jar : $(CLASSFILES) 
	-@rm *.jar
	-@rm classes/com/grs/dragon/manReader/* 2> /dev/null
	cp *.class classes/com/grs/dragon/manReader
	cp ../../gui/*.class classes/com/grs/gui
	cp ../common/*.class  classes/com/grs/dragon/common
	cp ../ipc/*.class classes/com/grs/dragon/ipc
	cp ../ui/AboutDialog.class classes/com/grs/dragon/ui
	$(DRAGON_JAVA)/bin/jar -0cvf manreader.jar -C ./classes com > /dev/null
	cp manreader.jar $(PRODUCTROOT)/lib/jar
	@rm -rf classes
	-@echo "   "

install : $(RESULTS)
	cp -p $(RESULTS) $(DRAGON_BUILD_DIR)

forTest :
#	cp -p $(RESULTS) $(TESTDIR)

directories : 
#	-mkdir classes
#	-mkdir classes/com
#	-mkdir classes/com/grs
	-@mkdir -p classes/com/grs/gui
#	-mkdir classes/com/grs/dragon
	-@mkdir -p classes/com/grs/dragon/manReader
	-@mkdir -p classes/com/grs/dragon/common
	-@mkdir -p classes/com/grs/dragon/ipc
	-@mkdir -p classes/com/grs/dragon/ui
	-@mkdir -p $(PRODUCTROOT)/lib/jar

clean : 
	-@rm -r $(CLASSFILES) *.jar *.jnk *.tmp *.log *~ classes 2> /dev/null
