.PHONY: all clean

all: assemble emulate
	../bin/assemble pong.s ../bin/pong

assemble:
	../bin/assemble pong.s ../bin/pong

emulate: assemble
	../bin/emulate ../bin/pong -v

clean:
	rm -f ../bin/pong
