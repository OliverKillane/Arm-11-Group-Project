CC      = gcc
CFLAGS  = -Wall -g -I../../lib/stddata/include -Icommandgen -Itokenizer -I. -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -pedantic

.PHONY: all clean

all: ../../build/assemble/assemble.o\
	 ../../build/assemble/assemble_utils.o\
	 ../../build/assemble/common_defs.o\
	 ../../build/assemble/process_branch.o\
	 ../../build/assemble/process_data_processing.o\
	 ../../build/assemble/process_data_transfer.o\
	 ../../build/assemble/process_multiply.o\
	 ../../build/assemble/process_shift.o\
	 ../../build/assemble/commandgen.o\
	 ../../build/assemble/token_utils.o\
	 ../../build/assemble/tokenizer.o\
	 ../../build/assemble/error.o\
	 ../../build/assemble/instruction_layouts.o
	cp ../../build/stddata.o ../../build/assemble/
	$(CC) $(CFLAGS) $^ ../../build/assemble/stddata.o -o ../../build/assemble/assemble
	cp ../../build/assemble/assemble ../../bin/

../../build/assemble/%.o:
	$(CC) $(CFLAGS) -c $^ -o $@

../../build/assemble/error.o: error.c
../../build/assemble/assemble.o: assemble.c
../../build/assemble/token_utils.o: tokenizer/token_utils.c
../../build/assemble/tokenizer.o: tokenizer/tokenizer.c
../../build/assemble/assemble_utils.o: assemble_utils.c
../../build/assemble/commandgen.o: commandgen/commandgen.c
../../build/assemble/common_defs.o: commandgen/common_defs.c
../../build/assemble/process_branch.o: commandgen/process_branch.c
../../build/assemble/process_data_processing.o: commandgen/process_data_processing.c
../../build/assemble/process_data_transfer.o: commandgen/process_data_transfer.c
../../build/assemble/process_multiply.o: commandgen/process_multiply.c
../../build/assemble/process_shift.o: commandgen/process_shift.c
../../build/assemble/instruction_layouts.o: commandgen/instruction_layouts.c

clean:
	rm -f $(wildcard ../../build/assemble/*)
	rm -f ../../bin/assemble
