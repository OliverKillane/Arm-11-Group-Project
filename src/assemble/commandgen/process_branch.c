#include "common_defs.h"
#include "process_branch.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <stdio.h>

bool LayoutBranchConstant(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    long long constant;
    ProcessDataLayout(tokens, 2, &type, &constant);
    
    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int jump_offset = (constant / 4 - 2 - offset) & ((1<<24) - 1);
    unsigned int link = (type == INSTR_BRL); 

    SetInstruction(text, FillInstruction(
        4,
        cond, 28,
        0x5, 25,
        link, 24,
        jump_offset, 0
    ), offset);
    return false;
}