#include "common_defs.h"
#include "process_alias.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdio.h>

bool LayoutRet(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data,
    int offset, 
    int instructions_num
) {
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));

    SetInstruction(text, FillInstruction(
        4,
        cond, 28,
        0xD, 21,
        0xF, 12,
        0xE, 0
    ), offset);

    return false;
}

bool LayoutHalt(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    SetInstruction(text, 0, offset);
    return false;
}

bool LayoutPush(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_d;
    ProcessDataLayout(tokens, 2, &type, &reg_d);

    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    SetInstruction(text, FillInstruction(
        7,
        cond, 28,
        0x1, 26,
        0x1, 24,
        0x1, 21,
        0xD, 16,
        reg_d, 12,
        0x4, 0
    ), offset);
    return false;
}

bool LayoutPop(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_d;
    ProcessDataLayout(tokens, 2, &type, &reg_d);

    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    SetInstruction(text, FillInstruction(
        7,
        cond, 28,
        0x1, 26,
        0x1, 23,
        0x1, 20,
        0xD, 16,
        reg_d, 12,
        0x4, 0
    ), offset);
    return false;
}