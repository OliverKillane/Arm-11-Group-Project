CC      = gcc
CFLAGS  = -Wall -g -I../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.SUFFIXES: .c .o

.PHONY: all clean

all: stddata assemble emulate

assemble: assemble.o stddata.o

emulate: emulate.o stddata.o

stddata:
	cd ../lib/stddata && make library
	cp ../lib/stddata/bin/stddata.o .

clean:
	rm -f $(wildcard *.o)
	rm -f assemble
	rm -f emulate
	cd ../lib/stddata && make clean
