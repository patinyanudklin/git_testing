# Makefile for dllhelpers.a under Mingw
# Sally Goldin - 3/30/05
#
# ~~ Copyright Kurt rudahl and Sally goldin
# ~~ EndC
####################################################################
#
# This file builds only the modules in this directory, 
# producing a library which is used to build DLLs in Dragon 
# It is normally invoked from the Makefile in the COMMONROOT
# It assumes that etc/SetEnv has been executed to set various
# environment variables
#
####################################################################
# $Id: Makefile,v 1.3 2014/02/10 04:19:14 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.3  2014/02/10 04:19:14  rudahl
# avoid errors on mkdir
#
# Revision 1.2  2005/08/01 03:12:54  rudahl
# use DragonCommon for libs
#
# Revision 1.1  2005/03/30 12:41:28  goldin
# Add source files used for MingW dll functionality
#
#

ifeq ($(OSTYPE),linux)
	LIBDIR	=$(COMMONROOT)/lib/linux
	EXECEXT =
else
	LIBDIR	=$(COMMONROOT)/lib/mingw
	EXECEXT =.exe
endif

ifeq ($(__GCC64__),TRUE)
	BITS	=__GCC64__
else
	BITS	=__GCC32__
endif

.SUFFIXES: .c .cpp .o

CINCL		=$(INCLUDE) -Iinclude -I$(COMMONROOT)/lib/genfiles 
CBASEFLAGS	=-D$(BITS) -Wall -fno-signed-char -DQSTATIC= -DEXPORT= -DGRS_EXP_CALL= 
COMINC		=../../include


# Lines below are copied from MingW sample Make file for a C++ DLL

# Must define BUILDING_DLL when building the DLL. Otherwise import/exports 
# will not work correctly. See dllclass.h for more info.
DLL_CFLAGS = -DBUILDING_DLL=1

# The default entry point defined by dllwrap; the default user callback
# is DllMain, and there is stub in dllinit.c. 
DLL_LDFLAGS = 

DLL_HELP_LIB = $(COMMONROOT)/vendors/mingw/dllhelpers.a
DLL_SRCS  = dllclass.cc dllexterns.cc dllinit.c
DLL_OBJS  = dllclass.o dllexterns.o dllinit.o

.c.o :
	gcc -c $(CBASEFLAGS) $(CINCL) -D$(COMP)  $(DLL_CFLAGS) $*.c

.cpp.o :
	g++ -c $(CBASEFLAGS) $(CINCL) -D$(COMP) $(DLL_CFLAGS) $*.cpp

.cc.o :
	g++ -c $(CBASEFLAGS) $(CINCL) -D$(COMP) $(DLL_CFLAGS) $*.cc


ALL :	$(LIBDIR) $(LIBDIR)/dllhelpers.a $(DLL_OBJS)

$(LIBDIR) :
	-@mkdir -p $(DRAGON_DVMT)/lib
	mkdir -p $(LIBDIR)

$(LIBDIR)/dllhelpers.a : $(DLL_OBJS)
	ar -r $(LIBDIR)/dllhelpers.a $(OBJS)

