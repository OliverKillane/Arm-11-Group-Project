CC      = gcc
CSANITIZERS = -fsanitize=address,undefined,leak,pointer-subtract
CFLAGS  = -Wall -g -I../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic

.PHONY: all clean emulate stddata assemble

all: stddata emulate assemble

assemble: stddata
	cd assemble && $(MAKE)

emulate: 
	cd emulate && $(MAKE)

stddata:
	cd ../lib/stddata && $(MAKE) library
	cp ../lib/stddata/bin/stddata.o ../build/tests/

clean:
	cd assemble && $(MAKE) clean
	cd emulate && $(MAKE) clean
	cd ../lib/stddata && $(MAKE) clean
	rm -f $(wildcard ../build/*.o)
