#include "common_defs.h"
#include "instruction_layouts.h"
#include "process_shift.h"
#include "../tokenizer.h"
#include <stddata.h>

bool LayoutShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    SetInstruction(text, FillInstruction(
        6,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        MapGet(data_proc_opcodes, (void*)INSTR_MOV), 21,
        TokenRegisterNumber(VectorGet(tokens, 1)), 12,
        TokenRegisterNumber(VectorGet(tokens, 1)), 0,
        MapGet(shift_codes, (void*)TokenInstructionType(VectorGet(tokens, 0))), 5,
        TokenConstantValue(VectorGet(tokens, 2)), 7
    ), offset);
    return false;
}

bool LayoutShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    SetInstruction(text, FillInstruction(
        7,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        MapGet(data_proc_opcodes, (void*)INSTR_MOV), 21,
        TokenRegisterNumber(VectorGet(tokens, 1)), 12,
        TokenRegisterNumber(VectorGet(tokens, 1)), 0,
        0x1, 4,
        MapGet(shift_codes, (void*)TokenInstructionType(VectorGet(tokens, 0))), 5,
        TokenRegisterNumber(VectorGet(tokens, 2)), 8
    ), offset);
    return false;
}