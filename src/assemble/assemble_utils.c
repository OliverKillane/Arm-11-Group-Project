#include "assemble_utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
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

	int lineNum = 1;

	printf("reading file '%s'\n", filename);
	file = fopen(filename, "r");
	if(file == NULL) {
		fprintf(stderr, "Couldn't open file %s\n", filename);
		assert(false);
	}

	
	bool readingText = true;
	char *preservedLine;

	while ((read = getline(&preservedLine, &length, file)) != -1) {
		line = preservedLine;
		while(isWhitespace(*line)) {
			line++;
		}
		

		if (strncmp(line, ".text", 5) == 0) {
			readingText = true;
		} else if (strncmp(line, ".data", 5) == 0) {
			readingText = false;
		} else if (strncmp(line, ".include", 8) == 0) {
			char *pos = strrchr(line,'\n');
			if (pos != NULL) {
				*pos = '\0';
			}
			line += 9;
			char *slash = strrchr(filename, '/');
			
			if (slash != NULL) {
				char *newFileName = calloc(sizeof(char), (strlen(line) + strlen(filename) + 10));
				strncpy(newFileName, filename, slash - filename + 1);
				strcat(newFileName, line);
				readFileLines(newFileName, textLines, dataLines);
				free(newFileName);

			} else {
				char *newFileName = calloc(sizeof(char), (strlen(line) + 3));
				strcpy(newFileName, "./");
				strcat(newFileName, line);
				readFileLines(newFileName, textLines, dataLines);
				free(newFileName);
			}
		} else {
			char *allocatedStr = malloc(sizeof(char) * (length + 1));
			strcpy(allocatedStr, line);
			
			if (readingText) {
				
				char *filenameCpy = malloc(sizeof(char) * (strlen(filename) + 1));
				strcpy(filenameCpy, filename);
				ListPushBack(textLines, allocatedStr);
				ListPushBack(textLines, lineNum);
				ListPushBack(textLines, filenameCpy);
			} else {
				ListPushBack(dataLines, allocatedStr);
			}
		}
		lineNum++;
		// line = NULL;
		
		// if (preservedLine != NULL) {
		// 	free(preservedLine);
		// }
	}
	if (preservedLine != NULL) {
		free(preservedLine);
	}
			
    fclose(file);

}

List tokenize(List lines, Map symbolTable, int *totalInstructions, Vector dataVector) {

	List listOfTokens = NewEmptyList();

	LISTFOR(lines, iter) {
		char *line = ListIteratorGet(iter);
		ListIteratorIncr(&iter);
		int lineNum = ListIteratorGet(iter);
		ListIteratorIncr(&iter);
		char *filename = ListIteratorGet(iter);

		Vector tokens = tokenizeTextLine(line, symbolTable, *totalInstructions, dataVector, filename, lineNum);
		bool hasInstructions = VectorSize(tokens) >= 4;
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
		int lineNum = VectorPopBack(lineTokens);
		char *filename = VectorPopBack(lineTokens);
		char *line = VectorPopBack(lineTokens);
		if (FunctionGen(symbolTable, lineTokens, programVector, dataVector, currInstr, totalInstructions)) {
			ReportError(lineNum, filename, line);
		}
		// free(filename);
		
		
		currInstr++;		
	}

	FinishFunctionGen();

	return programVector;

}