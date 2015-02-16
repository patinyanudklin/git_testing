# Makefile for Shapelib library (libshapelib.a) under Linux or Mingw
# Sally Goldin, 7 August 2006
# Creates a library and copies the .h file. The actual
# build is done by the Makefile provided by the shapelib people
####################################################################
# -----------------------------------------------------------------
# @(#) $Id: Makefile,v 1.1 2006/08/09 04:37:49 goldin Exp $
# $Revision: 1.1 $
#

ifeq ($(OSTYPE),linux)
	EXECEXT =
	PLATFORM	=linux
else
	EXECEXT =.exe
	PLATFORM	=mingw
endif
LIBDIR	=$(COMMONROOT)/lib/$(PLATFORM)
PLIBDIR	=$(PRODUCTROOT)/lib/$(PLATFORM)

EXEC	=

ifeq ($(__GCC64__),TRUE)
	BITS	=__GCC64__
else
	BITS	=__GCC32__
endif

.SUFFIXES: .c .cpp .o

VENDORS		=$(COMMONROOT)/../vendors
SHAPELIB	=$(VENDORS)/shapelib
SHAPEVERSION	=shapelib-1.2.10

LIB	=$(SHAPELIB)/lib/$(PLATFORM)/lib/libshapelib.a

OBJS	= $(SHAPEVERSION)/shpopen.o \
          $(SHAPEVERSION)/dbfopen.o

EXES	= shpcreate \
	shpadd \
	shprewind \
	dbfcreate \
	dbfadd \
	dbfdump \
	shptest

all:	directories $(LIB) $(EXES) 

directories : 
	-@mkdir -p $(SHAPELIB)/lib
	-@mkdir -p $(SHAPELIB)/lib/$(PLATFORM)
	-@mkdir -p $(SHAPELIB)/lib/$(PLATFORM)/lib
	-@mkdir -p $(SHAPELIB)/lib/$(PLATFORM)/bin
	-@mkdir -p $(SHAPELIB)/lib/include

$(LIB)	: directories $(OBJS)
	ar -r $(LIB) $(OBJS)
	cp $(SHAPEVERSION)/shapefil.h $(SHAPELIB)/lib/include
	cp $(SHAPEVERSION)/LICENSE.LGPL $(SHAPELIB)/lib

$(EXES)	: 
	cp $(SHAPEVERSION)/shpcreate $(SHAPELIB)/lib/$(PLATFORM)/bin/shpcreate$(EXECEXT)
	cp $(SHAPEVERSION)/shpadd $(SHAPELIB)/lib/$(PLATFORM)/bin/shpadd$(EXECEXT)
	cp $(SHAPEVERSION)/shprewind $(SHAPELIB)/lib/$(PLATFORM)/bin/shprewind$(EXECEXT)
	cp $(SHAPEVERSION)/dbfcreate $(SHAPELIB)/lib/$(PLATFORM)/bin/dbfcreate$(EXECEXT)
	cp $(SHAPEVERSION)/dbfadd $(SHAPELIB)/lib/$(PLATFORM)/bin/dbfadd$(EXECEXT)
	cp $(SHAPEVERSION)/dbfdump $(SHAPELIB)/lib/$(PLATFORM)/bin/dbfdump$(EXECEXT)
	cp $(SHAPEVERSION)/shptest $(SHAPELIB)/lib/$(PLATFORM)/bin/shptest$(EXECEXT)





