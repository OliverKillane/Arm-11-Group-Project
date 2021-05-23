CC      = gcc
CSANITIZERS = -fsanitize=address,undefined,leak,pointer-subtract
CFLAGS  = -Wall -g -I../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.PHONY: all clean assemble emulate stddata

all: stddata assemble emulate

assemble: stddata
<<<<<<< HEAD
	cd assemble && $(MAKE)

emulate: stddata
	cd emulate && $(MAKE)

stddata:
	cd ../lib/stddata && $(MAKE) library
	cp ../lib/stddata/bin/stddata.o ../build/tests/

clean:
	cd assemble && $(MAKE) clean
	cd emulate && $(MAKE) clean
	cd ../lib/stddata && $(MAKE) clean
=======
	cd assemble && make

emulate: stddata
	cd emulate && make

stddata:
	cd ../lib/stddata && make library
	cp ../lib/stddata/bin/stddata.o ../build/tests/

clean:
	cd assemble && make clean
	cd emulate && make clean
	cd ../lib/stddata && make clean
>>>>>>> 2c45c69212bc643f4b54f2a58589964c28909b65
	rm -f $(wildcard ../build/*.o)
