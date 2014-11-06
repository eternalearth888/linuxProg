APPS=charcell
CFLAGS+= -g -D_GNU_SOURCE -std=c99

all: ${APPS}

${APPS}: % : %.c

clean:
	${RM} ${APPS} *.o *~ *.bak

charcell: charcell.o
	${CC} ${LDFLAGS} -o charcell charcell.o -lcurses

.PHONY: all clean
