CC      = gcc
CFLAGS  = -Wall -g -o3  -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -pedantic 
INCLUDE = -I../../lib/SDL2/include
SDLLIB = -lSDL2x86_64 #-lSDL2x86_64 or -lSDL2arm32
LINK =  -L../../lib/SDL2/ $(SDLLIB) -lm -ldl -lpthread -lrt
PROFILETARGET = 

.PHONY: all clean

all: emulate_extension

emulate_extension:
	$(info ***USE APPROPRIATE LIBRARY FOR YOUR PLATFORM, CURRENT SDL IS $(SDLLIB)***)
	$(CC) $(CFLAGS) $(INCLUDE) emulate_extension.c -o ../../bin/emulate_extension $(LINK)

profile:
	ifndef PROFILETARGET
	$(error PROFILE TAGRET IS NOT SET - PLEASE INSERT INTO MAKEFILE)
	endif
	$(CC) $(CFLAGS) -pg $(INCLUDE) emulate_extension.c -o emulate_extension_prof $(LINK)
	./emulate_extension_prof $(PROFILETARGET)
	gprof emulate_extension_prof gmon.out > analysis.txt
	rm gmon.out
	rm emulate_prof
	less analysis.txt

clean:
	rm -f $(wildcard ../build/emulate_extension/*)
	rm -f ../../bin/emulate_extension
	rm -f gmon.out
	rm -f emulate_extension_prof
	rm -f analysis.txt
