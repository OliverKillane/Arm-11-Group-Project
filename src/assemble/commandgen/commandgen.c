#include "../commandgen.h"
#include "../tokenizer.h"
#include "../error.h"
#include "instruction_layouts.h"
#include <stddata.h>
#include <stdio.h>

bool FunctionGen(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data,
    int offset, 
    int instructions_num
) {
    if(VectorSize(tokens) == 0 || TokenType(VectorGet(tokens, 0)) != TOKEN_INSTRUCTION) {
        SetErrorCode(ERROR_INVALID_PATTERN);
        printf("WWW\n");
        return true;
    }
    if(ProcessExpression(symbols, tokens)) {
        return true;
    }
    bool(*process_function)(Map, Vector, Vector, Vector, int, int) = DecisionTreeQuery(instruction_layouts, tokens);
    if(process_function == NULL) {
        SetErrorCode(ERROR_INVALID_PATTERN);
        printf("QQQ\n");
        return true;
    }
    return process_function(symbols, tokens, text, data, offset, instructions_num);
}