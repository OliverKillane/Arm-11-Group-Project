
#include "assemble_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"
#include "tokenizer.h"
#include "error.h"


/* Removes the colon in sourceStr by copying to targetStr.
 * PRE: targetStr is of size one less than sourceStr.
 * POST: targetStr contains (in order) every character in sourceStr without the colon suffix.
 */
void removeColon(char *str) {
	for ( ; *str != ':' || *str != '\0' ; str++);

	*str = '\0';
}

int bigToLittleEndian(int value) {
	int newValue = 0;

	int byteMask = 0xFF;
	newValue = (byteMask & value) << 24;
	byteMask = byteMask << 8;
	newValue = newValue | ((byteMask & value) << 8);
	byteMask = byteMask << 8;
	newValue = newValue | ((byteMask & value) >> 8);
	byteMask = byteMask << 8;
	newValue = newValue | ((byteMask & value) >> 24);
	return newValue;
}

void writeBinary(Vector program, char *filename) {

	FILE *file = fopen(filename, "wb");

    assert(file != NULL);

	int vecSize = (program -> size);

	int progLittleEndian[vecSize];
	
	for (int i=0; i<vecSize; i++) {
		progLittleEndian[i] = VectorGet(program, i);
	}
	
	fwrite(progLittleEndian, sizeof(int)*vecSize, 1, file);

	fclose(file);
}

void readFileLines(char *filename, List textLines, List dataLines) {

	FILE *file;
	char *line = NULL;
	size_t length = 0;
	ssize_t read;

	file = fopen(filename, "r");
	assert(file != NULL);

	// List linesLst = NewEmptyList();

	bool readingText = true;

	while ((read = getline(&line, &length, file)) != -1) {
		// printf("%s", line);
		

		if (strncmp(line, ".text", 5) == 0) {
			readingText = true;
		} else if (strncmp(line, ".data", 5) == 0) {
			readingText = false;
		} else if (strncmp(line, ".include", 8) == 0) {
			char *pos = strchr(line,'\n');
			if (pos != NULL) {
				*pos = '\0';
			}
			readFileLines(line+9, textLines, dataLines);
		} else {
			char *allocatedStr = malloc(sizeof(char) * (length + 1));
			strcpy(allocatedStr, line);
			// printf("%s", allocatedStr);
			if (readingText) {
				ListPushBack(textLines, allocatedStr);
			} else {
				ListPushBack(dataLines, allocatedStr);
			}
		}


		// ListPushBack(linesLst, allocatedStr);
	}
	if (line != NULL) {
		free(line);
	}

    fclose(file);

	// return linesLst;
}

List tokenize(List lines, Map symbolTable, int *totalInstructions, Vector dataVector) {

	List listOfTokens = NewEmptyList();

	LISTFOR(lines, iter) {

		char *line = ListIteratorGet(iter);

		Vector tokens = tokenizeTextLine(line, symbolTable, *totalInstructions, dataVector);
		bool hasInstructions = VectorSize(tokens) >= 2;
		if (hasInstructions) {
			(*totalInstructions)++;
			ListPushBack(listOfTokens, tokens);
		} else {
			DeleteVector(tokens);
		}

	}

	return listOfTokens;

}

Vector tokensToBinary(Map symbolTable, List listOfTokens, Vector dataVector, int totalInstructions) {

	Vector programVector = NewEmptyVector();
	InitFunctionGen();

	int currInstr = 0;
	LISTFOR(listOfTokens, allTokensIter) {	
		Vector lineTokens = ListIteratorGet(allTokensIter);
		char *line = VectorPopBack(lineTokens);
		if (FunctionGen(symbolTable, lineTokens, programVector, dataVector, currInstr, totalInstructions)) {
			ReportError(0, "wow", line);
			exit(1);
		}
		
		
		currInstr++;		
	}

	FinishFunctionGen();

	return programVector;

}