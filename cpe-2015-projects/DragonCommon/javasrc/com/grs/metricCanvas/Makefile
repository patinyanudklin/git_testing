# Makefile for Dragon metricCanvas components under Linux or Mingw
# Sally Goldin 12/10/2004
#
# ~~ Copyright 2004-2015 Sally Goldin and Kurt Rudahl
# ~~ EndC
#
# $Id: Makefile,v 1.4 2015/01/01 08:10:04 rudahl Exp $
# $Log: Makefile,v $
# Revision 1.4  2015/01/01 08:10:04  rudahl
# consolidating Dragon and OpenDragon
#
# Revision 1.3  2014/02/09 04:34:58  rudahl
# suppress irritating messages during clean
#
# Revision 1.2  2006/02/24 13:51:40  rudahl
# cleanup useless build messages
#
# Revision 1.1  2005/03/27 06:20:21  goldin
# Rename MakeLinux
#
# Revision 1.1  2004/12/10 12:15:31  goldin
# Add new Make files for Linux
#
#

CLASSFILES	= ColorGrid.class \
	ColorGridCanvas.class \
	DefectiveStructureException.class \
	GriddedMetric.class\
	GriddedPlaneSpace.class\
	LinearMetric.class\
	LinearPlaneSpace.class\
	Metric.class\
	PlaneSpace.class\
	PlotGraph.class\
	Ruler.class\
	Space.class 

%.class : %.java
	javac $<

all : directories $(CLASSFILES) metricCanvas.jar

metricCanvas.jar : $(CLASSFILES)
	-@rm $*.jar
	-@rm classes/com/grs/metricCanvas/*
	cp $(CLASSFILES) classes/com/grs/metricCanvas
	jar -cvf metricCanvas.jar  -C ./classes com
	@rm -rf classes

directories : 
#	-mkdir classes
#	-mkdir classes/com
#	-mkdir classes/com/grs
	-@mkdir -p classes/com/grs/metricCanvas

clean :
	-@rm -r $(CLASSFILES) classes metricCanvas.jar *.jnk *.tmp 2> /dev/null
