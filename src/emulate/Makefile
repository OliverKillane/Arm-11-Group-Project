CC      = gcc
CFLAGS  = -Wall -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic

.PHONY: all clean

all:
	$(CC) $(CFLAGS) emulate.c -o emulate
	mv ./emulate ../../bin/

clean:
	rm -f $(wildcard ../build/emulate/*)
	rm -f ../../bin/emulate
