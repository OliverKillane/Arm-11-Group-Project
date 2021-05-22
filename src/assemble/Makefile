CC      = gcc
CFLAGS  = -Wall -g -I../../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.PHONY: all clean

all:
	cp ../build/stddata.o ../build/assemble/
	cp ../build/assemble/assemble ../bin/

clean:
	rm -f $(wildcard ../build/assemble/*)
	rm -f ../bin/assemble
