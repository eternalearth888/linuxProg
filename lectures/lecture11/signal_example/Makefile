APPS=signal_example
CFLAGS+= -g -D_GNU_SOURCE -std=c99

all: ${APPS} signal_example

signal_example: signal_example.o signal_example_utils.o

clean:
	${RM} ${APPS} *.o *~ *.bak

.PHONY: all clean
