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

	List textLines = NewEmptyList();
	List dataLines = NewEmptyList();
	readFileLines(argv[1], textLines, dataLines);

	printf("ALL TEXT LINES:\n");
	LISTFOR(textLines, iter) {
		char *line = ListIteratorGet(iter);
		printf("%s", line);
	}

	printf("\nALL DATA LINES:\n");
	LISTFOR(dataLines, iter) {
		char *line = ListIteratorGet(iter);
		printf("%s", line);
	}
	// List listOfTokens = tokenize(lines, symbolTable, &totalInstructions);
	// printf("Got to making binary vector\n");
	// Vector binaryVector = tokensToBinary(symbolTable, listOfTokens, totalInstructions);
	

	// MAPFOR(symbolTable, iter) {
 	//     free((char*)(MapIteratorGet(iter).key));
  	// }
	// DeleteMap(symbolTable);

	// LISTFOR(lines, iter) {
	// 	free(ListIteratorGet(iter));
	// }
	// DeleteList(lines);

	// LISTFOR(listOfTokens, iter1) {
	// 	Vector line = ListIteratorGet(iter1);
	// 	VECTORFOR(line, iter2) {
	// 		Token token = VectorIteratorGet(iter2);
	// 		DeleteToken(token);
	// 	}
	// 	DeleteVector(line);
	// }
	// DeleteList(listOfTokens);



	// writeBinary(binaryVector, argv[2]);

	// DeleteVector(binaryVector);
	
    return EXIT_SUCCESS;
}

