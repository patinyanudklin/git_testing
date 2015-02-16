# Makefile for Dragon util components under Linux or Mingw
# Sally Goldin 12/10/2004
#
# ~~ Copyright Kurt Rudahl and Sally Goldin
# ~~ endC
#
# $Id: Makefile,v 1.6.2.2 2015/01/01 13:51:54 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.6.2.2  2015/01/01 13:51:54  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.7  2014/02/09 05:14:42  rudahl
# suppress irritating messages during clean
#
# Revision 1.6  2007/06/06 11:40:41  goldin
# Fix makefiles to copy jar files to product-specific directory
#
# Revision 1.5  2006/07/23 09:12:22  goldin
# Attempt to switch to using Java 1.5 (Axel/Windows only)
#
# Revision 1.4  2005/04/08 04:33:09  goldin
# Change javadoc handling
#
# Revision 1.3  2005/04/05 06:12:39  rudahl
# adapt to creating better test environment
#
# Revision 1.2  2005/03/27 10:39:48  goldin
# Add forTest and other minor Makefile changes
#
# Revision 1.1  2005/03/27 06:21:18  goldin
# Rename MakeLinux
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#
#


.SUFFIXES : .java .class

#rule for creating class files
.java.class :
	$(DRAGON_JAVA)/bin/javac $*.java

CLASSFILES = PackerLayout.class\
	Parse.class\
	Smallfile.class\
	StringSplitter.class\
	StringWrapper.class

all : $(CLASSFILES)

forTest:

clean : 
	-@rm *.class *.jnk *.tmp *.log 2> /dev/null

