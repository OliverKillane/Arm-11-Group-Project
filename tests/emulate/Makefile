CC      = gcc
CSANITIZERS = -fsanitize=address,undefined,leak,pointer-subtract
CFLAGS  = -Wall -g -I../../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.PHONY: all clean

all:
	cp ../../build/tests/stddata.o ../../build/tests/emulate/stddata.o



clean:
	rm -f $(wildcard ../../build/tests/emulate/*)
