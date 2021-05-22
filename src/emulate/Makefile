CC      = gcc
CFLAGS  = -Wall -g -I../../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.PHONY: all clean

all:
	cp ../build/stddata.o ../build/emulate/
	cp ../build/emulate/emulate ../bin/

clean:
	rm -f $(wildcard ../build/emulate/*)
	rm -f ../bin/emulate
