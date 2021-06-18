.PHONY: all assemble emulate emulate_extension doc tests pong clean

all: assemble emulate emulate_extension tests doc pong

assemble:
	cd src && $(MAKE) assemble

emulate:
	cd src && $(MAKE) emulate

emulate_extension:
	cd src && $(MAKE) emulate_extension

tests:
	cd tests && $(MAKE)

pong: assemble emulate_extension
	cd extension && $(MAKE)

doc:
	cd doc && $(MAKE)

clean:
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean
	cd extension && $(MAKE) clean
	cd doc && $(MAKE) clean
