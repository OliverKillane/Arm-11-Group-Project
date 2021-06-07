#include "../commandgen.h"
#include "../tokenizer.h"
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
    ProcessExpression(symbols, tokens);
    bool(*process_function)(Map, Vector, Vector, int, int) = DecisionTreeQuery(instruction_layouts, tokens);
    return process_function(symbols, tokens, output, offset, instructions_num);
}