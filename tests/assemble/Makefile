CC      = gcc
CSANITIZERS = -fsanitize=address,undefined
CFLAGS  = -Wall -g -I../../lib/stddata/include -I../../src/assemble -I../../src/assemble/tokenizer -I../../src/assemble/commandgen\
		-D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17  -Wno-int-conversion -Wno-pointer-to-int-cast -fsanitize=address,undefined

LINK = -L../../lib/stddata/bin -lstddata

.PHONY: all clean

all: ../../build/tests/assemble/commandgen.o\
	 ../../build/tests/assemble/process_branch.o\
	 ../../build/tests/assemble/process_data_processing.o\
	 ../../build/tests/assemble/process_data_transfer.o\
	 ../../build/tests/assemble/process_multiply.o\
	 ../../build/tests/assemble/process_shift.o\
	 ../../build/tests/assemble/common_defs.o\
	 ../../build/tests/assemble/assemble_utils.o\
	 ../../build/tests/assemble/assembletests.o\
	 ../../build/tests/assemble/tokenizer.o\
	 ../../build/tests/assemble/token_utils.o\
	 ../../build/tests/assemble/error.o\
	 ../../build/tests/assemble/instruction_layouts.o\
	 ../../build/tests/assemble/process_expression.o\
	 ../../build/tests/assemble/process_alias.o
	
	$(CC) $(CSANITIZERS) $(CFLAGS) $^ -o ../../build/tests/assemble/tests $(LINK)
	cp ./fact.s ../../build/tests/assemble/
	cp ./tokenTests.s ../../build/tests/assemble/
	../../build/tests/assemble/tests

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
../../build/tests/assemble/instruction_layouts.o:\
		../../src/assemble/commandgen/instruction_layouts.c
../../build/tests/assemble/assemble_utils.o:\
		../../src/assemble/assemble_utils.c
../../build/tests/assemble/tokenizer.o:\
		../../src/assemble/tokenizer/tokenizer.c
../../build/tests/assemble/process_expression.o:\
		../../src/assemble/commandgen/process_expression.c
../../build/tests/assemble/process_alias.o:\
		../../src/assemble/commandgen/process_alias.c

clean:
	rm -f $(wildcard ../../build/tests/assemble/*)

