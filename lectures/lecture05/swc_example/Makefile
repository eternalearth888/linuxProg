APPS=

CFLAGS+= -g -D_GNU_SOURCE -std=c99

all: ${APPS} swcmain

${APPS}: % : %.c

swcmain.o swcutils.o: swcutils.h

swcmain: swcmain.o swcutils.o

clean:
	${RM} ${APPS} swcmain *.o *~ *.bak
	
.PHONY: all clean
