CC      = gcc
CSANITIZERS = -fsanitize=address,undefined,leak,pointer-subtract
CFLAGS  = -Wall -g3 -I../../lib/stddata/include -I../../src/assemble -I../../src/assemble/tokenizer -I../../src/assemble/commandgen\
		  -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17  -Wno-int-conversion -Wno-pointer-to-int-cast

.PHONY: all clean 

all:     ../../build/tests/assemble/commandgen.o\
	 ../../build/tests/assemble/process_branch.o\
	 ../../build/tests/assemble/process_data_processing.o\
	 ../../build/tests/assemble/process_data_transfer.o\
	 ../../build/tests/assemble/process_multiply.o\
	 ../../build/tests/assemble/process_shift.o\
	 ../../build/tests/assemble/common_defs.o\
	 ../../build/tests/assemble/stddata.o\
	 ../../build/tests/assemble/assemble_utils.o\
	 ../../build/tests/assemble/assembletests.o\
	 ../../build/tests/assemble/tokenizer.o\
	 ../../build/tests/assemble/token_utils.o\
	 ../../build/tests/assemble/error.o
	
	$(CC) $(CSANITIZERS) $(CFLAGS) $(wildcard ../../build/tests/assemble/*.o)\
		-o ../../build/tests/assemble/tests
	cp ./fact.s ../../build/tests/assemble/
	cp ./tokenTests.s ../../build/tests/assemble/
	../../build/tests/assemble/tests

../../build/tests/assemble/stddata.o:
	cp ../../build/tests/stddata.o ../../build/tests/assemble/stddata.o

../../build/tests/assemble/%.o:
	$(CC) -c $(CFLAGS) $(CSANITIZERS) $^ -o $@


../../build/tests/assemble/assembletests.o: assembletests.c

../../build/tests/assemble/error.o:\
		../../src/assemble/error.c
../../build/tests/assemble/token_utils.o:\
		../../src/assemble/tokenizer/token_utils.c
../../build/tests/assemble/commandgen.o:\
		../../src/assemble/commandgen/commandgen.c
../../build/tests/assemble/process_branch.o:\
		../../src/assemble/commandgen/process_branch.c
../../build/tests/assemble/process_data_processing.o:\
		../../src/assemble/commandgen/process_data_processing.c
../../build/tests/assemble/process_data_transfer.o:\
		../../src/assemble/commandgen/process_data_transfer.c
../../build/tests/assemble/process_multiply.o:\
		../../src/assemble/commandgen/process_multiply.c
../../build/tests/assemble/process_shift.o:\
		../../src/assemble/commandgen/process_shift.c
../../build/tests/assemble/common_defs.o:\
		../../src/assemble/commandgen/common_defs.c
../../build/tests/assemble/assemble_utils.o:\
		../../src/assemble/assemble_utils.c
../../build/tests/assemble/tokenizer.o:\
		../../src/assemble/tokenizer/tokenizer.c

CFLAGS  = -Wall -g -I../../lib/stddata/include -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -Werror -pedantic

.PHONY: all clean

all:
	cp ../../build/tests/stddata.o ../../build/tests/assemble/stddata.o

clean:
	rm -f $(wildcard ../../build/tests/assemble/*)

