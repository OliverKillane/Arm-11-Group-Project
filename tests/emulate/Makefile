CC      = gcc
CFLAGS  = -Wall -g -I../../src/emulate -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic

.PHONY: all clean test

all:
	$(CC) $(CFLAGS) emulatortests.c -o ../../build/tests/emulate/emulatortests
	./../../build/tests/emulate/emulatortests

clean:
	rm -f $(wildcard ../../build/tests/emulate/*)
