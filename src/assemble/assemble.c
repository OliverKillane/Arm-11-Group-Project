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

	

	// printf("ALL TEXT LINES:\n");
	// LISTFOR(textLines, iter) {
	// 	char *line = ListIteratorGet(iter);
	// 	printf("%s", line);
	// }

	// printf("\nALL DATA LINES:\n");
	// LISTFOR(dataLines, iter) {
	// 	char *line = ListIteratorGet(iter);
	// 	printf("%s", line);
	// }
	Vector dataVector = NewEmptyVector();
	List textTokens = tokenize(textLines, symbolTable, &totalInstructions, dataVector);

	
	printf("finished making binaryvector\n");

	LISTFOR(dataLines, iter) {
		char *line = ListIteratorGet(iter);
		tokenizeTextLine(line, symbolTable, totalInstructions + VectorSize(dataVector), dataVector, NULL, 0);
	}
	printf("finished making binaryvector\n");

	// printf("Got to making binary vector\n");
	Vector binaryVector = tokensToBinary(symbolTable, textTokens, dataVector, totalInstructions);
	printf("finished making binaryvector\n");
	VECTORFOR(dataVector, iter) {
		int word = VectorIteratorGet(iter);
		// VectorIteratorIncr(&iter);
		// VectorIteratorIncr(&iter);
		VectorPushBack(binaryVector, word);
	}
	

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


	printf("finished making binaryvector\n");
	writeBinary(binaryVector, argv[2]);
	printf("finished making binaryvector\n");

	DeleteVector(binaryVector);
	
    return EXIT_SUCCESS;
}

