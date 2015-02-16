# Top level makefile for Dragon Java components under Linux or Mingw
# Extracted from com/grs/Makefile 2014-12-25 Kurt Rudahl
# $Id: Makefile,v 1.1.2.1 2014/12/25 07:50:49 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.1.2.1  2014/12/25 07:50:49  rudahl
# prune unused branches of javasrc tree
#

# NOTE this make process now assumes that Java
# is on the path and is the default Java system.

ifeq ($(OSTYPE),'linux')
	COMP	=__GCC__
	LIBDIR	=../../../lib
else
	COMP	=__MINGCC__
	LIBDIR	=../../../lib/mingw
endif

all : ENTER product EXIT

ENTER :
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

product :
	-@mkdir -p $(DOCDIR)
	make -C common 
	make -C ipc 
	make -C ui 
#	make -C ui  install 
	make -C manReader 
#	make -C manReader  install
	make -C viewport 
#	make -C viewport  install
	make -C manReader/detailXml 
	make -C installer 	

doc : 
	-@javadoc -d $(DOCDIR) com.grs

jresystem : $(TESTDIR)/j2re-1.4.2

$(TESTDIR)/j2re-1.4.2 :
	cp -R $(DRAGON_JAVA)/jre $(TESTDIR)/j2re-1.4.2

forTest: jresystem
	make -C ui  forTest
	make -C manReader  forTest
	make -C viewport  forTest

clean :
	make -C common  clean
	make -C installer  clean
	make -C ipc  clean
	make -C ui  clean
	make -C manReader  clean
	make -C viewport  clean
	make -C manReader/detailXml  clean

