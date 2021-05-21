CC	=	gcc
CFLAGS	=	-Wall
BUILDALL = emulatortests.o 
TESTALL = emulatortests.o

emulatortests: emulatortests.o
	./emulatortests.o

testall: 
	./$(TESTALL)

emulatortests.o: ..\src\emulator.c ..\src\emulator.h testutils.c


clean:
	/bin/rm -f $(BUILD) *.o core

.PHONY: emulatortests testall clean