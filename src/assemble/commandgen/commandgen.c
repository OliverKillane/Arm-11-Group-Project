#include "../commandgen.h"
#include "../tokenizer.h"
#include "../error.h"
#include <stddata.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>

bool FunctionGen(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(ListSize(tokens) < 1) {
        SetErrorCode(STAGE_DISPATCH, ERROR_TOO_SHORT);
        return true;
    }
    if(TokenType(ListFront(tokens)) != TOKEN_INSTRUCTION) {
        SetErrorCode(STAGE_DISPATCH, ERROR_EXPECTED_INSTRUCTION);
        return true;
    }

    bool(*process_function)(FUNC_PROC_ARGS) = 
            MapGet(func_proc, (int)TokenInstructionType(ListFront(tokens)));
    
    if(TokenType(ListFront(tokens)) == NULL) {
        SetErrorCode(STAGE_DISPATCH, ERROR_INVALID_INSTRUCTION);
        return true;
    }

    return process_function(symbols, tokens, output, offset, instructions_num);
}