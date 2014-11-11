APPS=charcell-resize
CFLAGS+= -g -D_GNU_SOURCE -std=c99

all: ${APPS} charcell-resize

charcell: LIBS=-lncurses
charcell-resize: charcell-resize.o
	${CC} ${LDFLAGS} -o charcell-resize charcell-resize.o -lcurses

clean:
	${RM} ${APPS} *.o *~ *.bak

.PHONY: all clean
