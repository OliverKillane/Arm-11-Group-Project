CC      = gcc
CFLAGS  = -Wall -g -I../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.PHONY: all clean assemble emulate stddata

all: stddata assemble emulate

assemble: stddata
	cd assemble && make

emulate: stddata
	cd assemble && make

stddata:
	cd ../lib/stddata && make library
	cp ../lib/stddata/bin/stddata.o ../build/

clean:
	cd ../lib/stddata && make clean
	rm -f $(wildcard ../build/*.o)
	cd assemble && make clean
	cd emulate && make clean
