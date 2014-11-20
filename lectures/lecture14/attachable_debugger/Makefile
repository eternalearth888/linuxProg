APPS= test
CFLAGS+= -g -D_GNU_SOURCE -std=c99
LIBS = -L. -lattachable_debugger

include Makefile.so

all:: libattachable_debugger.so ${APPS} 

test: test.o

libattachable_debugger.so: attachable_debugger.o

attachable_debugger.o: CFLAGS+= -fPIC

clean::
	${RM} ${APPS} *.o *~ *.bak 
		
${APPS}: % : %.o
	${CC} ${LDFLAGS} -o $@ $^ ${LIBS}

SOFLAGS+= -shared
LD = cc
%.so:
	${LD} ${SOFLAGS} -o ${@F} $^ ${SOLIBS}


.PHONY: all clean

