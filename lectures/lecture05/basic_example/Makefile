APPS=swc stdfiles query

CFLAGS+= -g

all: swc query stdfiles

swc: swcmain.o swcutils.o

query: swcutils.c

stdfiles: stdfiles.c

clean:
	${RM} swc query swc.o query.o
	
.PHONY: all clean
