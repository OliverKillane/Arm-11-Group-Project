
#include "assemble_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"


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

List readFileLines(char *filename) {

	FILE *file;
	char *line = NULL;
	size_t length = 0;
	ssize_t read;

	file = fopen(filename, "r");
	assert(file != NULL);

	List linesLst = NewEmptyList();

	while ((read = getline(&line, &length, file)) != -1) {
		char *allocatedStr = malloc(sizeof(char) * (length + 1));
		strcpy(allocatedStr, line);

		ListPushBack(linesLst, allocatedStr);
	}
	if (line != NULL) {
		free(line);
	}

    fclose(file);

	return linesLst;
}

List tokenize(List lines, Map symbolTable, int *totalInstructions) {

	const char splitTokens[4] = " \n,";

	List listOfTokens = NewEmptyList();

	LISTFOR(lines, iter) {

		char *line = ListIteratorGet(iter);

		List lineTokens = NewEmptyList();
		char *tok;

		bool lineHasInstr = false;
		for (tok = strtok(line, splitTokens); tok != NULL; tok = strtok(0, splitTokens)) {	

			char *colonPointer;
			if ((colonPointer = strchr(tok, ':')) != NULL) {

				*colonPointer = '\0';

				MapSet(symbolTable, tok, *totalInstructions);

			} else {

				lineHasInstr = true;

				if (*tok == '[') {
					ListPushBack(lineTokens, "["); 
					tok++;
				}

				char* closeBrace; 	
				if ((closeBrace = strchr(tok, ']')) != NULL) {
					*closeBrace = '\0';
				}

				if (*tok != '\0') {
					ListPushBack(lineTokens, tok);
				}

				if (closeBrace != NULL) {
					ListPushBack(lineTokens, "]"); 
				}
			}

		} 

		if (lineHasInstr) {
			(*totalInstructions)++;
			ListPushBack(listOfTokens, lineTokens);
		}
	}

	return listOfTokens;

}

Vector tokensToBinary(Map symbolTable, List listOfTokens, int totalInstructions) {

	Vector programVector = NewEmptyVector();
	InitFunctionGen();

	int currInstr = 0;
	LISTFOR(listOfTokens, allTokensIter) {	
		List lineTokens = ListIteratorGet(allTokensIter);
		
		FunctionGen(symbolTable, lineTokens, programVector, currInstr, totalInstructions);
		
		currInstr++;		
	}

	FinishFunctionGen();

	return programVector;

}