#ifndef ASSEMBLE_TOKENIZER_H_
#define ASSEMBLE_TOKENIZER_H_

#include "stddata.h"
#include "./tokenizer/token_utils.h"

typedef enum {
    TOKENIZER_START,
    TOKENIZER_INSTR_LABEL_REG,
    TOKENIZER_REGISTER,
    TOKENIZER_CONSTANT,
    TOKENIZER_LABEL,
    TOKENIZER_INSTR,
    TOKENIZER_ERROR,
    TOKENIZER_FINISHED,
} TokenizerState;

typedef enum {
    WHITESPACE=1,
    ALPHA=2,
    NUMERIC=4,
    HEX=8,
    COLON=16
} CharacterType;


static char currentToken[512];
static int currentTokenLength;
static TokenizerState currentState;

List tokenizeLine(char *line, Map symbolTable, int currentLine);

#endif /* ASSEMBLE_TOKENIZER_H_ */
