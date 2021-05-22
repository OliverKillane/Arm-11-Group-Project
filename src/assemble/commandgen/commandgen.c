#include "commandgen.h"
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
    char* func_code = ListFront(tokens);
    unsigned int condition;
    char func_base[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(func_code, func_base, &condition);

    void(*process_function)(FUNC_PROC_ARGS) = MapGet(func_proc, func_base);
    assert(process_function != NULL);
    process_function(symbols, tokens, output, offset, instructions_num);
}