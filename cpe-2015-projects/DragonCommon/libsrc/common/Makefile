# Makefile for wfutl under Linux or Mingw
# Kurt Rudahl 4/11/2000
#  ~~ Copyright 2001-2014 Kurt Rudahl and Sally Goldin
#  ~~ EndC
####################################################################
#

PRODUCT		=OpenDragon
COMMONROOT	=../../../DragonCommon
PRODUCTROOT	=../../../DragonCommon
INCLUDE		=-Iinclude -I../../include
COMP		=__GCC__

JDK	=$(DRAGON_JAVA)
ifeq ($(OSTYPE),linux)
	EXECEXT =
	PLATFORM	=linux
	JDKINCLUDE      =-I$(JDK)/include -I$(JDK)/include/linux
	COMPJ           =__GCC__
else
	EXECEXT =.exe
	PLATFORM	=mingw
	JDKINCLUDE      =-I$(JDK)/include -I$(JDK)/include/win32
	COMPJ           =__MINGCC__
endif
LIBDIR		=$(COMMONROOT)/lib/$(PLATFORM)
PLIBDIR		=$(PRODUCTROOT)/lib/$(PLATFORM)

ifeq ($(__GCC64__),TRUE)
	BITS	=__GCC64__
else
	BITS	=__GCC32__
endif

OBJDIR		=objs
ROSEFLG		=
ROSE_STR	=-DVERR=\"NON-ROSE\"
TARGLIBS	=$(PLIBDIR)/wfutl.a $(LIBDIR)/common.a 

VENDORS		=$(COMMONROOT)/../vendors
SHAPELIB	=$(VENDORS)/shapelib/lib/$(PLATFORM)/lib
SHAPEINC	=$(VENDORS)/shapelib/lib/include
TIFF		=$(VENDORS)/libtiff/lib
GEOTIFF		=$(VENDORS)/geotiff/lib
PROJ4		=$(VENDORS)/proj4/lib
JPEG		=$(VENDORS)/jpeg/lib

CINCL		=$(PRODUCT_INCLUDE) $(INCLUDE) \
			-I$(TIFF)/include  \
			-I$(GEOTIFF)/include -I$(PROJ4)/include \
			-I$(JPEG)/include

CBASEFLAGS	=-D$(BITS) -Wall -fno-signed-char -DQSTATIC= \
			-DEXPORT= -DGRS_EXP_CALL= $(ROSEFLG) $(ROSE_STR) $(PRODFLAGS) $(MINGVERS)
COMINC		=../../include

ifeq ($(OSTYPE),linux)
	JPEGLIB		=$(JPEG)/$(PLATFORM)/lib/libjpeg.a 
else
	JPEGLIB		=
endif
LIBS	=$(TARGLIBS) $(LIBDIR)/ipc.a \
	$(TIFF)/$(PLATFORM)/lib/libtiff.a \
	$(GEOTIFF)/$(PLATFORM)/lib/libgeotiff.a \
	$(SHAPELIB)/libshapelib.a \
	$(PROJ4)/$(PLATFORM)/lib/libproj.a \
	$(JPEGLIB)

OBJS	=objs/common_ipc.o \
	objs/dhead.o \
	objs/dragon-errors.o \
	objs/dragonObject.o \
	objs/dragonImageReader.o \
	objs/dragonImageWriter.o \
	objs/dragonOldImageReader.o \
	objs/dragonOldImageWriter.o \
	objs/encoding.o \
	objs/externImageReader.o \
	objs/filename.o \
	objs/files.o \
	objs/getcfg.o \
	objs/hdrstats.o \
	objs/imageHdr.o \
	objs/i18n.o \
	objs/iff.o \
	objs/imagelinesIO.o \
	objs/imageReader.o \
	objs/imageWriter.o \
	objs/java_vm.o \
	objs/logger.o \
	objs/ob.o \
	objs/screenImageReader.o \
	objs/screenImageWriter.o \
	objs/signature.o \
	objs/tiffImageReader.o \
	objs/tiffImageWriter.o \
	objs/werror.o \
	objs/wfutil.o 
POBJS	= \
	objs/dragonVectorDataReader.o \
	objs/dragonVectorDataWriter.o \
	objs/igcMetaData.o \
	objs/img.o \
	objs/img_acc.o \
	objs/img_hdr.o \
	objs/shapeVectorDataReader.o \
	objs/shapeVectorDataWriter.o \
	objs/vectorData.o \
	objs/vectorDataAccess.o \
	objs/vectorDataReader.o \
	objs/vectorDataWriter.o 

$(OBJDIR)/%.o : %.c
	gcc -c  -o $(OBJDIR)/$*.o $(CBASEFLAGS) $(CINCL) -D$(COMP) $*.c
	-@echo "   "

$(OBJDIR)/%.o : %.cpp
	g++ -c  -o $(OBJDIR)/$*.o $(CBASEFLAGS) $(CINCL) -D$(COMP) $*.cpp
	-@echo "   "

ALL :	ENTER $(OBJDIR) $(LIBDIR) $(PLIBDIR) $(TARGLIBS) EXIT

ENTER :
	-@echo "   "
	@echo Entering `pwd` > /dev/stderr

EXIT :
	@echo Exiting `pwd` > /dev/stderr

$(LIBDIR) :
	-mkdir -p $(LIBDIR)

$(OBJDIR) :
	-mkdir $(OBJDIR)

$(PLIBDIR) :
	-mkdir -p $(PLIBDIR)

$(LIBDIR)/common.a : $(OBJS)
	ar -r $(LIBDIR)/common.a $(OBJS)
	-@echo "   "

$(PLIBDIR)/wfutl.a : $(POBJS)
	ar -r $(PLIBDIR)/wfutl.a $(POBJS)
	-@echo "   "

$(OBJDIR)/compmisc.o : compmisc.c
$(OBJDIR)/dhead.o : dhead.cpp $(COMINC)/dhead.h

$(OBJDIR)/dragonImageReader.o : dragonImageReader.cpp include/dragonImageReader.h
$(OBJDIR)/dragonOldImageReader.o : dragonOldImageReader.cpp \
				include/dragonOldImageReader.h
$(OBJDIR)/dragonImageWriter.o : dragonImageWriter.cpp include/dragonImageWriter.h
$(OBJDIR)/dragonOldImageWriter.o : dragonOldImageWriter.cpp \
				include/dragonOldImageWriter.h
$(OBJDIR)/dragonObject.o : dragonObject.cpp $(COMINC)/dragonOb.h
$(OBJDIR)/dragon-errors.o : dragon-errors.c $(COMINC)/dragon-errors.h
$(OBJDIR)/encoding.o : encoding.cpp
$(OBJDIR)/event.o : event.cpp
$(OBJDIR)/eventsim.o : eventsim.cpp
$(OBJDIR)/externImageWriter.o : externImageWriter.cpp include/externImageWriter.h
$(OBJDIR)/file_sa.o : file_sa.c
$(OBJDIR)/filecall.o : filecall.c
$(OBJDIR)/filename.o : filename.c
$(OBJDIR)/files.o : files.c
$(OBJDIR)/ftime.o : ftime.c
$(OBJDIR)/g_assert.o : g_assert.c
$(OBJDIR)/getcfg.o : getcfg.c
$(OBJDIR)/hdrstats.o : hdrstats.c
$(OBJDIR)/hdr-dump.o : hdr-dump.c
$(OBJDIR)/i18n.o : i18n.c
$(OBJDIR)/iff.o : iff.c
$(OBJDIR)/imageHdr.o : imageHdr.cpp $(COMINC)/imageHdr.h
$(OBJDIR)/imageReader.o : imageReader.cpp $(COMINC)/imageReader.h
$(OBJDIR)/imageWriter.o : imageWriter.cpp $(COMINC)/imageWriter.h
$(OBJDIR)/imageStrip.o : imageStrip.cpp $(COMINC)/imageStrip.h 
	g++ -c -o $@ $(CBASEFLAGS) $(PRODUCT_INCLUDE) $(CINCL) -D$(COMP) $<
	-@echo "   "

$(OBJDIR)/img.o : img.cpp $(COMINC)/img.h  $(PRODUCTROOT)/include/dp.h
	g++ -c -o $@ $(CBASEFLAGS) $(PRODUCT_INCLUDE) $(CINCL) -D$(COMP) $<
	-@echo "   "

$(OBJDIR)/img_acc.o : img_acc.cpp $(COMINC)/img_acc.h  $(PRODUCTROOT)/include/dp.h

$(OBJDIR)/img_hdr.o : img_hdr.c
	gcc -o  $@ -x c++ -c $(CINCL) $(CBASEFLAGE) -D$(COMP) $<
	-@echo "   "

$(OBJDIR)/iscale.o : iscale.c
$(OBJDIR)/isin.o : isin.c
$(OBJDIR)/java_vm.o : java_vm.cpp
	g++ -c -o  $@ $(CBASEFLAGS) $(CINCL) $(JDKINCLUDE) $(PRODINC) -D$(COMPJ) $< 
	-@echo "   "

$(OBJDIR)/logger.o : logger.cpp $(COMINC)/logger.h
$(OBJDIR)/ob.o : ob.cpp $(COMINC)/ob.h

$(OBJDIR)/screenImageReader.o : screenImageReader.cpp include/screenImageReader.h
$(OBJDIR)/screenImageWriter.o : screenImageWriter.cpp include/screenImageWriter.h
$(OBJDIR)/signature.o  : signature.c ../../include/signature.h
$(OBJDIR)/tiffImageReader.o : tiffImageReader.cpp ../../include/tiffImageReader.h
$(OBJDIR)/tiffImageWriter.o : tiffImageWriter.cpp include/tiffImageWriter.h
$(OBJDIR)/trace.o : trace.c
$(OBJDIR)/tstack.o : tstack.c
$(OBJDIR)/vectorData.o : vectorData.cpp ../../include/vectorData.h
$(OBJDIR)/vectorDataAccess.o : vectorDataAccess.cpp ../../include/vectorDataAccess.h
$(OBJDIR)/vectorDataReader.o : vectorDataReader.cpp ../../include/vectorDataReader.h
$(OBJDIR)/vectorDataWriter.o : vectorDataWriter.cpp ../../include/vectorDataWriter.h
$(OBJDIR)/dragonVectorDataReader.o : dragonVectorDataReader.cpp \
      include/dragonVectorDataReader.h
$(OBJDIR)/dragonVectorDataWriter.o : dragonVectorDataWriter.cpp \
      include/dragonVectorDataWriter.h

$(OBJDIR)/shapeVectorDataReader.o : shapeVectorDataReader.cpp \
      include/shapeVectorDataReader.h
	g++ -c -o  $@ $(CBASEFLAGS) -I$(SHAPEINC) $(PRODUCT_INCLUDE) $(CINCL) -D$(COMP) $<
	-@echo "   "

$(OBJDIR)/shapeVectorDataWriter.o : shapeVectorDataWriter.cpp \
      include/shapeVectorDataWriter.h
	g++ -c -o  $@ $(CBASEFLAGS) -I$(SHAPEINC) $(PRODUCT_INCLUDE) $(CINCL) -D$(COMP) $<
	-@echo "   "

$(OBJDIR)/vf-sim.o : vf-sim.cpp
$(OBJDIR)/vgachk.o : vgachk.c
$(OBJDIR)/werror.o : werror.c
$(OBJDIR)/wfutil.o : wfutil.c
$(OBJDIR)/workingMem.o : workingMem.cpp

clean : cleanobjs
	-@rm  $(TARGLIBS) 2> /dev/null 

# clean only the local objs and trash
cleanobjs :
	-@rm objs/* *.pdb *.log *~ include/*~ 2> /dev/null 

