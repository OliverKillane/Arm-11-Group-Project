#ifndef ASSEMBLE_TOKENIZER_H_
#define ASSEMBLE_TOKENIZER_H_

#include "stddata.h"

static char currentToken[512];
static int currentTokenLength;
static TokenizerState currentState;

typedef enum {
    TOKENIZER_START,
    TOKENIZER_ERROR,
    TOKENIZER_FINISHED,
} TokenizerState;

typedef enum {
    WHITESPACE,
    TOKENIZER_ERROR,
    TOKENIZER_FINISHED,
} CharacterType;


List tokenizeLine(char *line);

#endif /* ASSEMBLE_TOKENIZER_H_ */
