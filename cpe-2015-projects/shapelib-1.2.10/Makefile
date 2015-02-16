
#LINKOPT	=	/usr/local/lib/libdbmalloc.a
CFLAGS	=	-g

all:	shpcreate shpadd shpdump shprewind dbfcreate dbfadd dbfdump shptest

clean:
	rm -f *.o dbfdump dbfcreate dbfadd shpdump shpcreate shpadd shputils shprewind
	rm -f shptreedump
	rm -rf *.lo *.la .libs
	rm -f shptest

test:	test2 test3

#
#	Note this stream only works if example data is accessable.
#	Fetch ftp://gdal.velocet.ca/pub/outgoing/shape_eg_data.zip
#
test1:
	@./stream1.sh > s1.out
	@if test "`diff s1.out stream1.out`" = '' ; then \
	    echo "******* Stream 1 Succeeded *********"; \
	    rm s1.out; \
	else \
	    echo "******* Stream 1 Failed *********"; \
	    diff s1.out stream1.out; \
	fi

test2:
	@./stream2.sh > s2.out
	@if test "`diff s2.out stream2.out`" = '' ; then \
	    echo "******* Stream 2 Succeeded *********"; \
	    rm s2.out; \
	    rm test*.s??; \
	else \
	    echo "******* Stream 2 Failed *********"; \
	    diff s2.out stream2.out; \
	fi

test3:
	@./makeshape.sh > s3.out
	@if test "`diff s3.out stream3.out`" = '' ; then \
	    echo "******* Stream 3 Succeeded *********"; \
	    rm s3.out; \
	    rm test.*; \
	else \
	    echo "******* Stream 3 Failed *********"; \
	    diff s3.out stream3.out; \
	fi


# -----------------------------------------------------------------------------
