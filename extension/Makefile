.PHONY: all assemble emulate clean

all: assemble emulate

assemble:
	../bin/assemble pong.s ../bin/pong

emulate: assemble
	../bin/emulate_extension ../bin/pong -v -n

clean:
	rm -f ../bin/pong
