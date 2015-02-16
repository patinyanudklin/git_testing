#  ~~ Copyright 2004-2014 Kurt Rudahl and Sally Goldin
#  ~~ EndC
# -----------------------------------------------------------------
# @(#) $Id: Makefile,v 1.45 2014/12/29 03:32:45 rudahl Exp $
# $Revision: 1.45 $
# Makefile for wfutl under Linux or Mingw
#  Copyright 2001-2008 Kurt Rudahl and Sally Goldin
# Kurt Rudahl 8/22/2001
# $Id: Makefile,v 1.45 2014/12/29 03:32:45 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.45  2014/12/29 03:32:45  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.44  2014/12/10 11:09:53  rudahl
# zap internet use
#
# Revision 1.43  2014/12/07 08:25:47  rudahl
# adapt to OpenDragon
#
# Revision 1.42  2014/12/05 07:08:44  rudahl
# adapting to new mingw
#
# Revision 1.41  2014/04/01 07:32:53  rudahl
# prepare to separate dtk,rosetta to new mingw version
#
# Revision 1.40  2014/03/01 01:53:10  rudahl
# more detail aboout ENTER,EXIT
#
# Revision 1.39  2014/02/09 04:46:04  rudahl
# removed jasper.lib
#
# Revision 1.38  2013/01/03 13:50:40  rudahl
# added argument to specify ipc style (method)
#
# Revision 1.37  2012/05/13 13:46:35  rudahl
# adapt setup to win7 - add ask.exe
#
# Revision 1.36  2012/05/02 11:40:27  rudahl
# implemented WEBSGL enforcement
#
# Revision 1.35  2012/04/15 04:40:39  rudahl
# support internet licensing
#
# Revision 1.34  2012/01/30 10:11:06  rudahl
# working on internet licensing
#
# Revision 1.33  2012/01/02 03:01:08  rudahl
# work on web-based validation
#
# Revision 1.32  2011/12/16 09:35:10  rudahl
# add jpeg for Linux, https web communications
#
# Revision 1.31  2011/12/13 08:41:39  rudahl
# added http and https internet communication
#
# Revision 1.30  2011/12/11 14:44:25  rudahl
# added libraries for SSH, JPEG
#
# Revision 1.29  2011/01/10 06:56:48  rudahl
# add proj4
#
# Revision 1.28  2008/10/09 05:38:22  rudahl
# minor fixes for Vista64
#
# Revision 1.27  2008/08/25 09:44:54  rudahl
# make SSDb tools more available
#
# Revision 1.26  2008/08/17 06:05:36  rudahl
# adapt tests to rose.a
#
# Revision 1.25  2008/06/26 09:46:28  rudahl
# revising internet
#
# Revision 1.24  2007/10/22 07:26:57  rudahl
# mods to support product versions
#
# Revision 1.23  2007/10/21 08:24:59  rudahl
# revised library order
#
# Revision 1.22  2007/06/16 10:36:58  rudahl
# improved progress msgs
#
# Revision 1.21  2007/05/31 09:43:20  rudahl
# moved SSDb to ipc
#
# Revision 1.20  2007/03/05 09:51:39  rudahl
# changes needed for v 5.10 commercial
#
# Revision 1.19  2007/01/01 06:52:31  rudahl
# added extra ref to wfutl.a
#
# Revision 1.18  2005/09/24 14:23:14  rudahl
# lintish
#
# Revision 1.17  2005/08/18 03:58:02  rudahl
# moved vendors up a level
#
# Revision 1.16  2005/08/03 08:04:16  goldin
# Add libraries to make PropertyFile.TEST link
#
# Revision 1.15  2005/08/01 04:33:41  rudahl
# use common.a library
#
# Revision 1.14  2005/08/01 03:13:27  rudahl
# use DragonCommon for libs
#
# Revision 1.13  2005/04/25 05:05:45  rudahl
# added test caseto IpcXmlGen
#
# Revision 1.12  2005/03/19 09:17:50  rudahl
# cleaner clean
#
# Revision 1.11  2005/03/13 23:29:47  goldin
# Begin implementation of new class to replace WritePrivateProfileString
#
# Revision 1.10  2005/02/16 04:14:00  rudahl
# adapt to GCC/MINGW differences
#
# Revision 1.9  2005/02/16 01:09:21  goldin
# Fix CVS keywords
#
# Revision 1.8  2005/02/12 02:58:02  goldin
# Fixes to make this library compile
#
# Revision 1.7  2005/02/11 19:22:33  goldin
# Save interim changes
#
# Revision 1.6  2005/02/11 02:15:12  rudahl
# added explicit module targets; not really needed
#
# Revision 1.5  2004/12/23 12:04:11  rudahl
# cleanup
#
# Revision 1.4  2004/11/30 04:31:44  rudahl
# adapt for Mingw
#
#
# -----------------------------------------------------------------
#	Developers
# 		ktr	Kurt Rudahl
#		seg	Sally Goldin
#		(add more names here)
#
#	Revision History
# 5.12	2008-06-26 ktr	moved internet.cpp here from ScriptServer
#			so installer can access
#

ifeq ($(OSTYPE),linux)
	LIBDIR	=$(COMMONROOT)/lib/linux
	EXECEXT =
else
	LIBDIR	=$(COMMONROOT)/lib/mingw
	EXECEXT =.exe
ifeq ($(MINGVERS),NEW)
	MINGVERS	=-DMINGVERS_NEW
endif
endif
LIBDIR	=$(COMMONROOT)/lib/$(PLATFORM)
PLIBDIR	=$(PRODUCTROOT)/lib/$(PLATFORM)
ROSELIBDIR	=$(PRODUCTROOT)/libdtk/$(PLATFORM)/lib
PDESTDIR	=$(PRODUCTROOT)/lib/blib/$(PLATFORM)

ifeq ($(__GCC64__),TRUE)
	BITS	=__GCC64__
else
	BITS	=__GCC32__
endif

VENDORS		=$(COMMONROOT)/../vendors
#JASPER		=$(VENDORS)/jasper/lib
TIFF		=$(VENDORS)/libtiff/lib
GEOTIFF		=$(VENDORS)/geotiff/lib
SQLITE		=$(VENDORS)/sqlite/lib
PROJ4		=$(VENDORS)/proj4/lib
JPEG		=$(VENDORS)/jpeg/lib

ifeq ($(OSTYPE),linux)
	LIBSSL	=/usr/local
	SSLLIBS	=/usr/lib/libssl.a 	/usr/lib/libcrypto.a \
		/usr/lib/libz.a		/usr/lib/libdl.a \
		/usr/lib/libc.a
ifneq ($(PRODUCT),OpenDragon)
	SOCKETLIB	=
	INTERNETTEST 	=
	INTERNETASK	=
	SHA		=my-sha1$(EXECEXT) 
endif
	JPEGLIB		=$(JPEG)/$(PLATFORM)/lib/libjpeg.a 
else
	LIBSSL	=$(VENDORS)/openssl/lib
#	SSLLIBS=$(LIBSSL)/mingw/lib/libssl32.dll.a 
	SSLLIBS=$(LIBSSL)/mingw/lib/libssl.a \
		$(LIBSSL)/mingw/lib/libeay32.dll.a \
		$(LIBSSL)/mingw/lib/libcrypto.a 
ifneq ($(PRODUCT),OpenDragon)
	SOCKETLIB	=-lws2_32
#	INTERNETTEST 	=internet.TEST.tgz
#	INTERNETASK	=ask.exe
	SHA		=my-sha1$(EXECEXT) 
endif
	JPEGLIB		=
endif


CINCL		=-I$(PRODUCTROOT)/include $(INCLUDE) -I$(COMMONROOT)/genfiles \
			-I$(SQLITE)/include -I$(PROJ4)/include \
			-I$(LIBSSL)/include 

CBASEFLAGS	=-D$(BITS) -Wall -fno-signed-char -DQSTATIC= -DEXPORT= -DGRS_EXP_CALL= $(MINGVERS)

# need wfutl twice to resolve refs in common.a (linux only?)
LIBS	=$(PLIBDIR)/wfutl.a $(LIBDIR)/common.a $(LIBDIR)/ipc.a \
	$(PLIBDIR)/wfutl.a \
	$(TIFF)/$(PLATFORM)/lib/libtiff.a \
	$(GEOTIFF)/$(PLATFORM)/lib/libgeotiff.a \
	$(SQLITE)/$(PLATFORM)/lib/libsqlite3.a \
	$(PROJ4)/$(PLATFORM)/lib/libproj.a \
	$(SSLLIBS) $(SOCKETLIB) $(JPEGLIB) 

#	$(JASPER)/$(PLATFORM)/lib/libjasper.a 

.SUFFIXES: .c .cpp .o

.c.o :
	gcc -c -o $*.o $(CINCL) $(CBASEFLAGS) -D$(COMP) $*.c
	-@echo "  "

.cpp.o :
	gcc -c -o $*.o $(CINCL) $(CBASEFLAGS) -D$(COMP) $*.cpp
	-@echo "  "

%.TEST$(EXECEXT) : %.c
	gcc -c -o $*.TEST.o $(CBASEFLAGS) $(CINCL) -D$(COMP) -DTEST $*.c
	g++ -o $*.TEST$(EXECEXT) $*.TEST.o $(LIBS)
	-@echo "  "

%.TEST$(EXECEXT) : %.cpp
	g++ -o $*.TEST$(EXECEXT) $(CBASEFLAGS) $(CINCL) -D$(COMP) -DTEST $*.cpp $(LIBS) $(PLIBDIR)/prod.a
	-@echo "  "

%$(EXECEXT) : %.cpp
	g++ -o $*$(EXECEXT) $(CBASEFLAGS) $(CINCL) -D$(COMP) $*.cpp $(LIBS)
	-@echo "  "

PATHS		=
CC		=cc
CPP		=g++

#############################################################################
# file lists

OBJS	= \
	IpcCmdFile.o \
	IpcCmdWatcher.o \
	IpcDatFile.o \
	IpcFile.o \
	IpcMsgFile.o \
	IpcNakFile.o \
	IpcProFile.o \
	IpcQryFile.o \
	IpcReceiveWatcher.o \
	IpcRpyFile.o \
	IpcRpyWatcher.o \
	IpcSendWatcher.o \
	IpcWatcher.o \
	IpcWrap.o \
	IpcXmlGen.o \
	PropertyFile.o \
	SSDb.o

#	internet.o  \

#############################################################################

#ifeq ($(PRODUCT),OpenDragon)
TESTS	=PropertyFile.TEST$(EXECEXT) IpcXmlGen.TEST$(EXECEXT) \
	SSDb.TEST$(EXECEXT)  $(PDESTDIR)/SSDb$(EXECEXT) 
#else
TESTS	=SSDb.TEST$(EXECEXT) \
	 $(PDESTDIR)/SSDb$(EXECEXT) $(INTERNETTEST)
#internet.TEST$(EXECEXT) 
#endif

all : ENTER $(LIBDIR)/ipc.a $(SHA) EXIT

# tests and ask invoked from GRS-Dragon/Makefile
tests : ENTERT $(TESTS) EXITT

ask : ENTERA $(INTERNETASK) EXITA

ENTER :
	-@echo "  "
	-@echo Entering `pwd` > /dev/stderr

EXIT :
	-@echo Exiting `pwd` > /dev/stderr

ENTERT :
	-@echo "  "
	-@echo Entering `pwd` for TESTS > /dev/stderr

EXITT :
	-@echo Exiting `pwd` for TESTS > /dev/stderr

ENTERA :
	-@echo "  "
	-@echo Entering `pwd` for INTERNETASK > /dev/stderr

EXITA :
	-@echo Exiting `pwd` for INTERNETASK > /dev/stderr

# build two libs - ipc.a contains everying in the subdir
#                - ipc-setup.a contains only those modules needed for setup.exe
$(LIBDIR)/ipc.a : $(PATHS) $(OBJS)
	ar -ruv $(LIBDIR)/ipc.a $(OBJS)
	-@echo "  "

IpcCmdFile.o : IpcCmdFile.cpp 
IpcCmdWatcher.o : IpcCmdWatcher.cpp 
IpcDatFile.o : IpcDatFile.cpp 
IpcFile.o : IpcFile.cpp
IpcMsgFile.o : IpcMsgFile.cpp
IpcNakFile.o :IpcNakFile.cpp
IpcProFile.o :IpcProFile.cpp
IpcQryFile.o : IpcQryFile.cpp
IpcReceiveWatcher.o : IpcReceiveWatcher.cpp 
IpcRpyFile.o : IpcRpyFile.cpp
IpcRpyWatcher.o : IpcRpyWatcher.cpp
IpcSendWatcher.o : IpcSendWatcher.cpp
IpcWatcher.o : IpcWatcher.cpp
IpcWrap.o : IpcWrap.cpp
IpcXmlGen.o : IpcXmlGen.c
PropertyFile.o : PropertyFile.cpp
SSDb.o : SSDb.cpp

#my-sha1$(EXECEXT) : my-sha1.cpp
# requires that /usr/lib/libstdc++.so.5 copied to web host rsgis.net

IpcXmlGen.TEST$(EXECEXT) : IpcXmlGen.c $(LIBDIR)/ipc.a $(LIBDIR)/common.a
# NOTE - the tests should probably all use rose.a, 
#        and be compiled with new MingW
PropertyFile.TEST$(EXECEXT) : PropertyFile.cpp $(ROSELIBDIR)/rose.a #$(LIBDIR)/ipc.a 
SSDb.TEST$(EXECEXT) : SSDb.cpp 
internet.TEST$(EXECEXT) : internet.cpp SSDb.cpp

$(PDESTDIR)/SSDb$(EXECEXT) : SSDb.cpp 
	g++ -o SSDb$(EXECEXT) $(CBASEFLAGS) $(CINCL) -D$(COMP) -DUTIL $< $(LIBS)
	cp -p SSDb$(EXECEXT) $(PDESTDIR)
	-@echo "  "
ifeq ($(OSTYPE),linux)
#	cp -p SSDb /home/rudahl/bin     
else

internet.TEST.tgz : internet.TEST.exe
	-@mkdir test
	cp -p internet.TEST.exe test
	cp -p ../../../vendors/openssl/lib/mingw/bin/*.dll test
	-@tar -cvzf internet.TEST.tgz test
	rm -r test
	-@echo "  "

$(INTERNETASK) : internet.cpp
	g++ -o ask.exe $(CBASEFLAGS) $(CINCL) -D$(COMP) -DBUILD_ASK internet.cpp $(LIBS) $(PLIBDIR)/prod.a
	-@echo "  "

endif

clean :
	-@rm *.o *.jnk *~ *.log *.trc Msg* $(LIBDIR)/ipc.a *.TEST *.TEST.exe include/*~  SSDb SSDb.exe 2> /dev/null
