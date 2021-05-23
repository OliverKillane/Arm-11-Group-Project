#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"

void replaceChar(char oldchar, char newchar, char *str) {
	for ( ; *str != '\0'; str++) {
		if (*str == oldchar) {
			*str = newchar;
		}
	}
}

/*void splitString(char *delimeterStr, char *str, Vector *outTokens) {
	char currentDelim = *delimeterStr;
	
	int start = 0;
	int current_index = 0;
	for (int start=0, current_index=0 ; *str != '\0'; str++, current_index++) {
		for ( ; 
	}
}
*/

/* Removes the colon in sourceStr by copying to targetStr.
 * PRE: targetStr is of size one less than sourceStr.
 * POST: targetStr contains (in order) every character in sourceStr without the colon suffix.
 */
void removeColon(char *sourceStr, char *targetStr) {
	for ( ; *sourceStr != ':' ; sourceStr++, targetStr++) {
		*targetStr = *sourceStr;	
	}

	sourceStr++;
	*targetStr = *sourceStr;

	
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

	int vecSize = program -> size;

	void *progArray = program -> data;

	int progLittleEndian[vecSize];
	
	for (int i=0; i<vecSize; i++) {
		progLittleEndian[i] = VectorGet(program, i);
	}
	
	fwrite(progLittleEndian, sizeof(int)*vecSize, 1, file);

	fclose(file);
}

int main(int argc, char **argv) {	

    FILE *file;
	char *line = NULL;
	size_t length = 0;
	ssize_t read;

	const char splitTokens[4] = " \n,";
	
	List strsToDeallocate = NewEmptyList();

	List allTokens = NewEmptyList();
	Map symbolTable = NewEmptyMap(StringHash, StringEq);


	file = fopen(argv[1], "r");
	assert(file != NULL);

	int totalInstructions = 0;

	while ((read = getline(&line, &length, file)) != -1) {
		
		List lineTokens = NewEmptyList();
		char *tok;
		tok = strtok(line, splitTokens);

		bool lineHasInstr = false;
		while (tok != NULL) {	
			
			if (strchr(tok, ':') != NULL) {
				char *tokNoColon = malloc(strlen(tok));
				removeColon(tok, tokNoColon);
				MapSet(symbolTable, tokNoColon, totalInstructions);


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
					char *tokAlloc = malloc(strlen(tok)+1);
					strcpy(tokAlloc, tok);
					ListPushBack(lineTokens, tokAlloc);
					ListPushBack(strsToDeallocate, tokAlloc);
				}

				if (closeBrace != NULL) {
					ListPushBack(lineTokens, "]"); 
				}
			}

			tok = strtok(0, splitTokens);
		} 

		if (lineHasInstr) {
			totalInstructions++;
			ListPushBack(allTokens, lineTokens);
		}
		
	}
	if (line != NULL) {
		free(line);
	}
	totalInstructions++;

	Vector binaryVector = NewEmptyVector();
	InitFunctionGen();
	
	int currInstr = 0;
	LISTFOR(allTokens, allTokensIter) {	
		List lineTokens = ListIteratorGet(allTokensIter);
		
		LISTFOR(lineTokens, lineTokensIter) {
			char *token = ListIteratorGet(lineTokensIter);
			printf("%s ", token);
		}
		printf("\n");
		
		FunctionGen(symbolTable, lineTokens, binaryVector, currInstr, totalInstructions);
		
		currInstr++;		
	}

	FinishFunctionGen();

	LISTFOR(strsToDeallocate, strsIter) {
		char *str = ListIteratorGet(strsIter);
		free(str);
	}
	
	writeBinary(binaryVector, argv[2]);

    return EXIT_SUCCESS;
}

