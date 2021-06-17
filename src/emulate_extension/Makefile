CC      = gcc
CFLAGS  = -Wall -g -o3  -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c11 -pedantic 
INCLUDE = -I../../lib/SDL2/include
LINK =  -L../../lib/SDL2 -lSDL2x86_64 -lm -ldl -lpthread -lrt
PROFILETARGET = 

.PHONY: all clean

all: emulate_extension

# currently on dynamic linking, which we should change to static with the .a included in /lib
emulate_extension:
	$(CC) $(CFLAGS) $(INCLUDE) emulate_extension.c -o ../../bin/emulate_extension $(LINK)
	

profile:
	$(CC) $(CFLAGS) -pg emulate_extension.c -o emulate_prof $(INCLUDE) $(LINK)
	./emulate_prof $(PROFILETARGET) || $(error PROFILE TAGRET NOT SET, PLEASE ENTER TARGET IN THE MAKEFILE!)
	gprof emulate_prof gmon.out > analysis.txt
	rm gmon.out
	rm emulate_prof
	less analysis.txt

clean:
	rm -f $(wildcard ../build/emulate_extension/*)
	rm -f ../../bin/emulate_extension
	rm -f gmon.out
	rm -f emulate_prof
	rm -f analysis.txt
