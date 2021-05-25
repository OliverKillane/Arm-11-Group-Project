#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"
#include "assemble_utils.h"


int main(int argc, char **argv) {	
	
	Map symbolTable = NewEmptyMap(StringHash, StringEq);

	int totalInstructions = 0;

	List lines = readFileLines(argv[1]);

	List listOfTokens = tokenize(lines, symbolTable, &totalInstructions);
	
	Vector binaryVector = tokensToBinary(symbolTable, listOfTokens, totalInstructions);
	

	writeBinary(binaryVector, argv[2]);

	LISTFOR(lines, strsIter) {
		char *str = ListIteratorGet(strsIter);
		free(str);
	}
	
    return EXIT_SUCCESS;
}

