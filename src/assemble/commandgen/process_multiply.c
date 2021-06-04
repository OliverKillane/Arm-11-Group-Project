#include "process_multiply.h"
#include "../tokenizer.h"
#include <stddata.h>

bool LayoutMUL(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    SetInstruction(output, FillInstruction(
        5,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        TokenRegisterNumber(VectorGet(tokens, 1)), 16,
        TokenRegisterNumber(VectorGet(tokens, 2)), 0,
        TokenRegisterNumber(VectorGet(tokens, 3)), 8,
        0x9, 4
    ), offset);
    return false;
}

bool LayoutMLA(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    SetInstruction(output, FillInstruction(
        7,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        TokenRegisterNumber(VectorGet(tokens, 1)), 16,
        TokenRegisterNumber(VectorGet(tokens, 2)), 0,
        TokenRegisterNumber(VectorGet(tokens, 3)), 8,
        TokenRegisterNumber(VectorGet(tokens, 4)), 12,
        0x9, 4,
        0x1, 21
    ), offset);
    return false;
}