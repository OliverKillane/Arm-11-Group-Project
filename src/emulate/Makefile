CC      = gcc
CFLAGS  = -Wall -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic
PROFILETARGET = 

.PHONY: all clean

all:
	$(CC) $(CFLAGS) emulate.c -o ../../bin/emulate

profile:
	$(CC) $(CFLAGS) -pg emulate.c -o emulate_prof
	./emulate_prof $(PROFILETARGET) || $(error PROFILE TAGRET NOT SET, PLEASE ENTER TARGET IN THE MAKEFILE!)
	gprof emulate_prof gmon.out > analysis.txt
	rm -f gmon.out
	rm -f emulate_prof
	less analysis.txt

clean:
	rm -f $(wildcard ../build/emulate/*)
	rm -f ../../bin/emulate
	rm -f gmon.out
	rm -f emulate_prof
	rm -f analysis.txt
