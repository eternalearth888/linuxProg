APPS=crr
CFLAGS+= -g -D_GNU_SOURCE -std=c99

all: ${APPS}

${APPS}: % : %.c

clean:
	${RM} ${APPS} $.o $~ *.bak

crr: crr.o
	${CC} ${LDFLAGS} -o crr crr.o -lcurses

.PHONY: all clean
