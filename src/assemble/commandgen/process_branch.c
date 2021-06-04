#include "process_branch.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdio.h>

bool LayoutBranchLabel(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    SetInstruction(output, FillInstruction(
        3,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        0xA, 24,
        ((int)MapGet(symbols, TokenLabel(VectorGet(tokens, 1))) - 2 - offset) & ((1<<24) - 1), 0
    ), offset);
    return false;
}

bool LayoutBranchConstant(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    SetInstruction(output, FillInstruction(
        3,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        0xA, 24,
        (TokenConstantValue(VectorGet(tokens, 1)) / 4 - 2 - offset) & ((1<<24) - 1), 0
    ), offset);
    return false;
}