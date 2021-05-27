CC      = gcc
CFLAGS  = -Wall -g -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c99 -pedantic

.SUFFIXES: .c .o

.PHONY: all clean testemulate

all: assemble emulate

assemble: assemble.o

emulate: emulate.o

emulatortests: emulatortests.o

testemulator: emulatortests
	./emulatortests
	
clean:
	rm -f $(wildcard *.o)
	rm -f $(wildcard *.exe)
	rm -f assemble
	rm -f emulate
