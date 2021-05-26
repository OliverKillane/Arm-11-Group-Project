#include "tokenizer.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stddata.h"

bool inline matchAlpha(char c) {
    return isalpha(c) != 0;
}

bool inline isHex(char c) {
    return isDecimal(c)
        || (c >= 0x61 && c <= 0x66)
        || (c >= 0x41 && c <= 0x46);
}

bool inline isDecimal(char c) {
    return (c >= 0x30 && c <= 39);
}

bool inline isWhitespace(char c) {
    return c == ' ' | c == '\t';
}

void match(bool (*func)(char), char c) {
    assert(func(c));
}

List tokenizeLine(char *line) {
    List tokenList = NewEmptyList();
    currentTokenLength = 0;
    currentState = TOKENIZER_START;

    while (currentState != TOKENIZER_FINISHED 
        && currentState != TOKENIZER_ERROR) {

        switch (currentState) {

            case TOKENIZER_START:
                if (isWhitespace(line[0])) {
                    continue;
                }
                break;
            
            default:
                break;
        }

    }

}