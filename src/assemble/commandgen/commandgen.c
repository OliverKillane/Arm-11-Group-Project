#include "commandgen.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>

void FunctionGen(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(ListSize(tokens) >= 1);
    assert(TokenType(ListFront(tokens)) == TOKEN_INSTRUCTION);

    void(*process_function)(FUNC_PROC_ARGS) = 
            MapGet(func_proc, (int)TokenInstructionType(ListFront(tokens)));
    assert(process_function != NULL);
    process_function(symbols, tokens, output, offset, instructions_num);
}