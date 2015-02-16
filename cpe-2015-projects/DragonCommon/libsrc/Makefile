# Makefile for libsrc under Linux/Mingw 10/1/2001 rev 2005-3-15

all : ENTER
ifeq ($(COMPUTERNAME),WIN7-32-VM)  # i.e. new mingw
	make -C common -f Makefile ROSE_UTL=TRUE
else
	make -C common -f Makefile
	make -C ipc -f Makefile
	make -C dtk -f Makefile
ifeq ($(OSTYPE),linux)
	make -C common -f Makefile ROSE_UTL=TRUE
endif
endif
	@echo Exiting `pwd` > /dev/stderr

forTest : ENTER
ifneq ($(COMPUTERNAME),WIN7-32-VM)  # i.e. new mingw
	make -C common -f Makefile forTest
	make -C ipc -f Makefile tests
endif
	@echo Exiting `pwd` forTest > /dev/stderr

ENTER :
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

clean :
ifeq ($(COMPUTERNAME),WIN7-32-VM)  # i.e. new mingw
	make -C common -f Makefile ROSE_UTL=TRUE clean
else
	make -C common -f Makefile clean
	make -C ipc -f Makefile clean
	make -C dtk -f Makefile clean
endif
	-@rm *.log *.jnk *~ 2> /dev/null

