CC      = gcc
CFLAGS  = -Wall -g -I../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic

.PHONY: all clean assemble emulate emulate_extension stddata

all: stddata assemble emulate emulate_extension

assemble: stddata
	cd assemble && $(MAKE)

emulate:
	cd emulate && $(MAKE)

emulate_extension:
	cd emulate_extension && $(MAKE)

stddata:
	cd ../lib/stddata && $(MAKE) library

clean:
	cd ../lib/stddata && $(MAKE) clean
	rm -f $(wildcard ../build/*.o)
	cd assemble && $(MAKE) clean
	cd emulate && $(MAKE) clean
	cd emulate_extension && $(MAKE) clean
