#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "stddata.h"
#include "commandgen.h"
#include "assemble_utils.h"
#include "tokenizer.h"

#define stringify( name ) # name


int main(int argc, char **argv) {
	char *str = "mov r0,#1\n";
	
	Map symbolTable = NewEmptyMap(StringHash, StringEq);

	int totalInstructions = 0;

	List tokList = tokenizeLine(str, symbolTable, 0);

	LISTFOR(tokList, iter) {
		Token tok = ListIteratorGet(iter);
		switch (tok->type) {
			case TOKEN_INSTRUCTION:
				printf("Instruction Token\n");
				break;
			case TOKEN_LABEL:
				printf("Label Token %s\n", tok->label);
				break;

			case TOKEN_CONSTANT:
				printf("Constant Token %d\n", tok->constant.value);
				break;
			case TOKEN_SIGN:
				printf("Sign Token %d\n", tok->is_plus);
				break;
			case TOKEN_BRACE:
				printf("Brace Token %d\n", tok->is_open);
				break;
			case TOKEN_REGISTER:
				printf("Register Token %d\n", tok->reg_num);
				break;
			default:
				printf("Token not recognized.");
				break;
		}
	}

	List listOfTokens = NewEmptyList();
	ListPushBack(listOfTokens, tokList);
	// List lines = readFileLines(argv[1]);
	// printf("Got to tokenizing\n");
	// List listOfTokens = tokenize(lines, symbolTable, &totalInstructions);
	printf("Got to making binary vector\n");
	Vector binaryVector = tokensToBinary(symbolTable, listOfTokens, totalInstructions);
	

	writeBinary(binaryVector, argv[2]);

	// LISTFOR(lines, strsIter) {
	// 	char *str = ListIteratorGet(strsIter);
	// 	free(str);
	// }
	
    return EXIT_SUCCESS;
}

