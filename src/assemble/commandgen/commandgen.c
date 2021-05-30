#include "../commandgen.h"
#include "../tokenizer.h"
#include "instruction_layouts.h"
#include <stddata.h>

bool FunctionGen(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    bool(*process_function)(Map, Vector, Vector, int, int) = DecisionTreeQuery(instruction_layouts, tokens);
    return process_function(symbols, tokens, output, offset, instructions_num);
}