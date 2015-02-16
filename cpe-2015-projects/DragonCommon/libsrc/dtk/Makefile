# -----------------------------------------------------------------
# @(#) $Id: Makefile,v 1.18 2015/01/21 10:46:41 rudahl Exp $
# ~~ Copyright
# ~~ EndC
# $Revision: 1.18 $
# Makefile for DTK under Linux or Mingw
# Sally Goldin 2/21/05
# $Id: Makefile,v 1.18 2015/01/21 10:46:41 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.18  2015/01/21 10:46:41  rudahl
# cleaner build
#
# Revision 1.17  2014/12/17 07:20:39  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.16  2007/10/22 07:26:57  rudahl
# mods to support product versions
#
# Revision 1.15  2005/08/12 03:09:09  rudahl
# clean target must zap old library
#
# Revision 1.14  2005/08/01 04:49:46  rudahl
# remove need for non-default dlimits.h
#
# Revision 1.13  2005/08/01 03:13:27  rudahl
# use DragonCommon for libs
#
# Revision 1.12  2005/03/19 09:17:50  rudahl
# cleaner clean
#
# Revision 1.11  2005/02/21 23:54:10  goldin
# First attempt to make toolkit compile; 
# except for toolcmd6, much work still needed
#
# Revision 1.10  2005/02/21 20:24:39  goldin
# Commit intermediate work and then checkout again
# -----------------------------------------------------------------
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

CINCL		=-I$(PRODUCTROOT)/include $(INCLUDE) -I$(DRAGON_DVMT)/lib/genfiles
CBASEFLAGS	=-D$(BITS) -Wall -fno-signed-char -DQSTATIC= -DEXPORT= -DGRS_EXP_CALL= 

.c.o :
	gcc -c -o $*.o $(CINCL) $(CBASEFLAGS) -D$(COMP) $*.c
	-@echo " "

.cpp.o :
	gcc -c -o $*.o $(CINCL) $(CBASEFLAGS) -D$(COMP) $*.cpp
	-@echo " "

PATHS		=
CC		=cc
CPP		=g++


#############################################################################
# file lists

OBJS	= \
	toolcmd6.o \
	toolerr.o \
	toolfile.o \
	toolifil.o \
	toolihdr.o \
	toolkit.o \
	toolsig.o

#############################################################################
# ~~~ toolerr.o requires werror.c, werror.h 

all : $(LIBDIR)/dtk.a

$(LIBDIR)/dtk.a : $(PATHS) $(OBJS)
	ar -ruv $(LIBDIR)/dtk.a $(OBJS)

toolcmd6.o : toolcmd6.c 
toolerr.o : toolerr.c 
toolfile.o : toolfile.c 
toolifil.o : toolifil.c
toolihdr.o : toolihdr.c
toolkit.o : toolkit.c
toolsig.o : toolsig.c

clean :
	-@rm $(LIBDIR)/dtk.a *.o *.jnk *~ *.log *.TEST$(EXECEXT) include/*~ 2> /dev/null
