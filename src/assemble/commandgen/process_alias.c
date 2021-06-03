#include "common_defs.h"
#include "process_alias.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdio.h>

bool LayoutRet(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));

    SetInstruction(output, FillInstruction(
        4,
        cond, 28,
        0xD, 21,
        0xF, 12,
        0xE, 0
    ), offset);

    return false;
}