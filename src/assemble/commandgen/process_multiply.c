#include "common_defs.h"
#include "process_multiply.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include "../error.h"
#include <stddata.h>

bool LayoutMUL(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    unsigned int reg_d = TokenRegisterNumber(VectorGet(tokens, 1));
    unsigned int reg_m = TokenRegisterNumber(VectorGet(tokens, 2));
    unsigned int reg_s = TokenRegisterNumber(VectorGet(tokens, 3));

    if(reg_d == 15 || reg_m == 15 || reg_s == 15) {
        SetErrorCode(ERROR_INVALID_REGISTER);
        return true;
    }

    if(reg_d == reg_m) {
        SetErrorCode(ERROR_SAME_REGISTERS);
        return true;
    }

    SetInstruction(text, FillInstruction(
        5,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        reg_d, 16,
        reg_m, 0,
        reg_s, 8,
        0x9, 4
    ), offset);
    return false;
}

bool LayoutMLA(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    unsigned int reg_d = TokenRegisterNumber(VectorGet(tokens, 1));
    unsigned int reg_m = TokenRegisterNumber(VectorGet(tokens, 2));
    unsigned int reg_s = TokenRegisterNumber(VectorGet(tokens, 3));
    unsigned int reg_n = TokenRegisterNumber(VectorGet(tokens, 4));

    if(reg_d == 15 || reg_m == 15 || reg_s == 15 || reg_n == 15) {
        SetErrorCode(ERROR_INVALID_REGISTER);
        return true;
    }

    if(reg_d == reg_m) {
        SetErrorCode(ERROR_SAME_REGISTERS);
        return true;
    }

    SetInstruction(text, FillInstruction(
        7,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        reg_d, 16,
        reg_m, 0,
        reg_s, 8,
        reg_n, 12,
        0x9, 4,
        0x1, 21
    ), offset);
    return false;
}