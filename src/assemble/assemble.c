#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"
#include "assemble_utils.h"
#include "tokenizer.h"

int main(int argc, char **argv) {
	// char *str = "mov r0,#1\n";
	
	Map symbolTable = NewEmptyMap(StringHash, StringEq);

	int totalInstructions = 0;

	List lines = readFileLines(argv[1]);
	List listOfTokens = tokenize(lines, symbolTable, &totalInstructions);
	// printf("Got to making binary vector\n");
	Vector binaryVector = tokensToBinary(symbolTable, listOfTokens, totalInstructions);
	

	MAPFOR(symbolTable, iter) {
 	    free((char*)(MapIteratorGet(iter).key));
  	}
	DeleteMap(symbolTable);

	LISTFOR(lines, iter) {
		free(ListIteratorGet(iter));
	}
	DeleteList(lines);

	LISTFOR(listOfTokens, iter1) {
		List line = ListIteratorGet(iter1);
		LISTFOR(line, iter2) {
			Token token = ListIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteList(line);
	}
	DeleteList(listOfTokens);



	writeBinary(binaryVector, argv[2]);

	DeleteVector(binaryVector);
	
    return EXIT_SUCCESS;
}

