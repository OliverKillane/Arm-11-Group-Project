.PHONY: all assemble emulate tests pong clean

all: assemble emulate tests pong doc

assemble:
	cd src && $(MAKE) assemble

emulate:
	cd src && $(MAKE) emulate

tests:
	cd tests && $(MAKE)

pong: assemble emulate
	cd extension && $(MAKE)

doc:
	cd doc && $(MAKE)

clean:
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean
	cd extension && $(MAKE) clean
	cd doc && $(MAKE) clean
