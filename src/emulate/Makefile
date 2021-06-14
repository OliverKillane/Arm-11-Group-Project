CC      = gcc
CFLAGS  = -Wall -g -o3  -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c11 -pedantic 
INCLUDE = -I../../lib/SDL2/include
LINK = -L/usr/local/lib -I/usr/include/SDL2 -lSDL2 -Wl,--no-undefined -lm -ldl -Wl,-rpath,/opt/vc/lib -L/opt/vc/lib -lpthread -lrt
PROFILETARGET = ../../bin/stresstest


.PHONY: all clean

all: emulate

# currently on dynamic linking, which we should change to static with the .a included in /lib
emulate:
	$(CC) $(CFLAGS) emulate.c -o emulate $(INCLUDE) $(LINK)
	mv ./emulate ../../bin/
	

profile:
	$(CC) $(CFLAGS) -pg emulate.c -o emulate_prof $(INCLUDE) $(LINK)
	./emulate_prof $(PROFILETARGET)
	gprof emulate_prof gmon.out > analysis.txt
	rm gmon.out
	rm emulate_prof
	less analysis.txt

clean:
	rm -f $(wildcard ../build/emulate/*)
	rm -f ../../bin/emulate
	rm -f gmon.out
	rm -f emulate_prof
