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
		Vector dataTokens = tokenizeTextLine(line, symbolTable, totalInstructions + VectorSize(dataVector), dataVector, NULL, 0);
		free(VectorPopBack(dataTokens));
		free(VectorPopBack(dataTokens));
		VectorPopBack(dataTokens);
		VECTORFOR(dataTokens, iter2) {
			Token token = VectorIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteVector(dataTokens);
	}
	Vector binaryVector = tokensToBinary(symbolTable, textTokens, dataVector, totalInstructions);
	VECTORFOR(dataVector, iter) {
		int word = VectorIteratorGet(iter);
		VectorPushBack(binaryVector, word);
	}

	writeBinary(binaryVector, argv[2]);
	DeleteVector(binaryVector);
	DeleteVector(dataVector);

	MAPFOR(symbolTable, iter) {
 	    free((char*)(MapIteratorGet(iter).key));
  	}
	DeleteMap(symbolTable);

	LISTFOR(textLines, iter) {
		free(ListIteratorGet(iter));
		ListIteratorIncr(&iter);
		// free(ListIteratorGet(iter));
		ListIteratorIncr(&iter);
		free(ListIteratorGet(iter));
	}
	DeleteList(textLines);

	LISTFOR(dataLines, iter) {
		free(ListIteratorGet(iter));
	}
	DeleteList(dataLines);

	LISTFOR(textTokens, iter1) {
		Vector line = ListIteratorGet(iter1);
		// VectorPopBack(line);
		// free(VectorPopBack(line));
		// VectorPopBack(line);
		VECTORFOR(line, iter2) {
			
			Token token = VectorIteratorGet(iter2);
			DeleteToken(token);
		}
		DeleteVector(line);
	}
	DeleteList(textTokens);

    return EXIT_SUCCESS;
}

