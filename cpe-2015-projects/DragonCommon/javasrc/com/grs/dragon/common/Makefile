# Makefile for Dragon/common components under Linux or Mingw
# Sally Goldin 12/10/2004
#
# ~~ Copyright 2004-2015 Sally Goldin and Kurt Rudahl
# ~~ EndC
#
# $Id: Makefile,v 1.8.2.2 2015/01/01 10:32:30 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.8.2.2  2015/01/01 10:32:30  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.11  2015/01/01 09:56:15  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.10  2014/12/29 03:32:45  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.9  2014/02/09 04:34:58  rudahl
# suppress irritating messages during clean
#
# Revision 1.8  2006/07/23 09:12:22  goldin
# Attempt to switch to using Java 1.5 (Axel/Windows only)
#
# Revision 1.7  2006/02/24 13:52:45  rudahl
# cleanup useless build messages
#
# Revision 1.6  2006/02/17 07:19:48  rudahl
# simplified mkdir
#
# Revision 1.5  2006/01/21 07:53:29  goldin
# Add new class to allow UI to register itself in the global INI file
#
# Revision 1.4  2005/07/29 09:37:45  goldin
# Add LanguageCallback and get rid of WinRecorder
#
# Revision 1.3  2005/04/08 04:33:09  goldin
# Change javadoc handling
#
# Revision 1.2  2005/03/28 06:58:05  goldin
# Change DRAGONROOT to COMMONROOT
#
# Revision 1.1  2005/03/27 06:12:22  goldin
# Rename MakeLinux
#
# Revision 1.2  2004/12/11 05:37:22  rudahl
# improved clean target
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#
#

.SUFFIXES : .java .class

#rule for creating class files
.java.class :
	$(DRAGON_JAVA)/bin/javac $*.java
	-@echo "   "

CLASSFILES = \
	ConfigFileProcessor.class \
	LanguageCallback.class \
	PathChecker.class \
	PlatformSpecific.class \
	SimpleWindowMonitor.class

all : ENTER $(CLASSFILES) EXIT
	$(DRAGON_JAVA)/bin/javah -jni com.grs.dragon.common.PlatformSpecific
#	-mkdir $(COMMONROOT)/lib
	-@mkdir -p $(COMMONROOT)/lib/genfiles
	cp com_grs_dragon_common_PlatformSpecific.h $(COMMONROOT)/lib/genfiles/platformSpecific.h

ENTER :
	-@echo "   "
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

clean : 
	-@rm $(CLASSFILES) *.jar *.jnk *.tmp *.log *.h *~ 2> /dev/null


