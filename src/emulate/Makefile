CC      = gcc
CFLAGS  = -Wall -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic
PROFILETARGET = ../../bin/stresstest

.PHONY: all clean

all:
	$(CC) $(CFLAGS) emulate.c -o emulate
	mv ./emulate ../../bin/

profile:
	$(CC) $(CFLAGS) -pg emulate.c -o emulate_prof
	./emulate_prof $(PROFILETARGET)
	gprof emulate_prof gmon.out > analysis.txt
	rm -f gmon.out
	rm -f emulate_prof
	less analysis.txt

clean:
	rm -f $(wildcard ../build/emulate/*)
	rm -f ../../bin/emulate
	rm -f gmon.out
	rm -f emulate_prof
