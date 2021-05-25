CC      = gcc
CFLAGS  = -Wall -g -I../../lib/stddata/include -Icommandgen -I. -D_POSIX_SOURCE -D_DEFAULT_SOURCE -std=c17 -O3 -pedantic -Wno-int-conversion

.PHONY: all clean

all: ../../build/assemble/assemble.o\
	 ../../build/assemble/assemble_utils.o\
	 ../../build/assemble/common_defs.o\
	 ../../build/assemble/process_branch.o\
	 ../../build/assemble/process_data_processing.o\
	 ../../build/assemble/process_data_transfer.o\
	 ../../build/assemble/process_multiply.o\
	 ../../build/assemble/process_shift.o\
	 ../../build/assemble/commandgen.o
	cp ../../build/stddata.o ../../build/assemble/
	$(CC) $(CFLAGS) $(wildcard ../../build/assemble/*.o) -o ../../build/assemble/assemble
	cp ../../build/assemble/assemble ../../bin/

../../build/assemble/%.o:
	$(CC) $(CFLAGS) -c $^ -o $@

../../build/assemble/assemble.o: assemble.c
../../build/assemble/assemble_utils.o: assemble_utils.c
../../build/assemble/commandgen.o: commandgen/commandgen.c
../../build/assemble/common_defs.o: commandgen/common_defs.c
../../build/assemble/process_branch.o: commandgen/process_branch.c
../../build/assemble/process_data_processing.o: commandgen/process_data_processing.c
../../build/assemble/process_data_transfer.o: commandgen/process_data_transfer.c
../../build/assemble/process_multiply.o: commandgen/process_multiply.c
../../build/assemble/process_shift.o: commandgen/process_shift.c

clean:
	rm -f $(wildcard ../build/assemble/*)
	rm -f ../bin/assemble
