#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"
#include "assemble_utils.h"
#include "tokenizer.h"

int main(int argc, char **argv) {
	Map symbolTable = NewEmptyMap(StringHash, StringEq);

	int totalInstructions = 0;

	List textLines = NewEmptyList();
	List dataLines = NewEmptyList();
	readFileLines(argv[1], textLines, dataLines);

	Vector dataVector = NewEmptyVector();
	List textTokens = tokenize(textLines, symbolTable, &totalInstructions, dataVector);

	LISTFOR(dataLines, iter) {
		char *line = ListIteratorGet(iter);
		tokenizeTextLine(line, symbolTable, totalInstructions + VectorSize(dataVector), dataVector, NULL, 0);
	}
		Vector binaryVector = tokensToBinary(symbolTable, textTokens, dataVector, totalInstructions);
		VECTORFOR(dataVector, iter) {
		int word = VectorIteratorGet(iter);
						VectorPushBack(binaryVector, word);
	}

	writeBinary(binaryVector, argv[2]);
	DeleteVector(binaryVector);

	MAPFOR(symbolTable, iter) {
 	    free((char*)(MapIteratorGet(iter).key));
  	}
	DeleteMap(symbolTable);

	LISTFOR(textLines, iter) {
		free(ListIteratorGet(iter));
	}
	DeleteList(textLines);

	LISTFOR(dataLines, iter) {
		free(ListIteratorGet(iter));
	}
	DeleteList(dataLines);

	LISTFOR(textTokens, iter1) {
		Vector line = ListIteratorGet(iter1);
		VECTORFOR(line, iter2) {
			Token token = VectorIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteVector(line);
	}
	DeleteList(textTokens);



	writeBinary(binaryVector, argv[2]);

	DeleteVector(binaryVector);

    return EXIT_SUCCESS;
}

