#ifndef ASSEMBLE_TOKENIZER_H_
#define ASSEMBLE_TOKENIZER_H_

#include "stddata.h"
#include "./tokenizer/token_utils.h"

typedef enum {
    TOKENIZER_START,
    TOKENIZER_ERROR,
    TOKENIZER_FINISHED,
} TokenizerState;

typedef enum {
    WHITESPACE,
    ALPHA,
    NUMERIC
} CharacterType;


static char currentToken[512];
static int currentTokenLength;
static TokenizerState currentState;

List tokenizeLine(char *line);

bool inline isWhitespace(char c);

#endif /* ASSEMBLE_TOKENIZER_H_ */
