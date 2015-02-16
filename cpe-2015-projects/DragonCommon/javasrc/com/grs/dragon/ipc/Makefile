# Makefile for Dragon/IPC Java components under Linux or Mingw
# Sally Goldin 12/10/2004
#
# ~~ Copyright 2004-2015 Sally Goldin and Kurt Rudahl
# ~~ EndC
#
# $Id: Makefile,v 1.6 2015/01/01 09:42:06 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.6  2015/01/01 09:42:06  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.5  2014/12/29 03:32:45  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.4  2014/02/22 13:27:27  rudahl
# cleaner clean
#
# Revision 1.3  2014/02/09 04:34:58  rudahl
# suppress irritating messages during clean
#
# Revision 1.2  2006/07/23 09:12:22  goldin
# Attempt to switch to using Java 1.5 (Axel/Windows only)
#
# Revision 1.1  2005/03/27 06:14:23  goldin
# Rename MakeLinux
#
# Revision 1.1  2004/12/10 12:43:02  goldin
# Make build work on linux/mingw
#
#

.SUFFIXES : .java .class

#rule for creating class files
.java.class :
	$(DRAGON_JAVA)/bin/javac $*.java
	-@echo "   "

CLASSFILES = \
	CompletionListener.class \
	FileDetector.class \
	IpcFile.class \
	IncomingCommandProcessor.class \
	MessageDetector.class \
	ReplyMonitor.class 

all : ENTER $(CLASSFILES) EXIT

ENTER :
	-@echo "   "
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr


clean : 
	-@rm *.class *.jar *.jnk *.tmp *.log 2> /dev/null
