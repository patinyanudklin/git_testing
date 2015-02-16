# Makefile for classes to create detail section of manual  under Linux or Mingw
# Sally Goldin 12/10/2004
#
# ~~ Copyright 2004-2015 Sally Goldin and Kurt Rudahl
# ~~ EndC
#
# $Id: Makefile,v 1.6 2015/01/01 08:37:11 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.6  2015/01/01 08:37:11  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.5  2014/02/09 04:34:58  rudahl
# suppress irritating messages during clean
#
# Revision 1.4  2005/03/27 06:16:30  goldin
# Rename MakeLinux
#
# Revision 1.2  2004/12/18 11:52:31  rudahl
# get rid of explicit compiler path
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#
#

.SUFFIXES : .java .class

# These classes are used in com/grs/dragon/ui
 
.java.class :
	javac $*.java

CLASSFILES = \
	DetailGenerator.class \
	FieldInfo.class \
	PanelInfo.class

all : $(CLASSFILES)

clean : 
	-@rm *.class *.jar *.jnk *.tmp *.log 2> /dev/null
