#include "process_shift.h"
#include <stddata.h>
#include "common_defs.h"
#include "../tokenizer.h"

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    assert(TokenConstantType(ListFront(tokens)) == CONST_HASH);
    const unsigned long long shift_value = TokenConstantValue(ListPopFront(tokens));
    assert(shift_value < 32 && shift_value >= 0);
    return shift_value << 3;
}

static inline unsigned int ProcessRegisterShift(List restrict tokens) {
    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_s = TokenRegisterNumber(ListPopFront(tokens));
    assert(reg_s <= 12);
    
    return (reg_s << 4) | 1;
}

void ProcessShift(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    InstructionType shift_type = TokenInstructionType(ListFront(tokens));
    ConditionType condition = TokenInstructionConditionType(ListPopFront(tokens));

    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_d = TokenRegisterNumber(ListPopFront(tokens));
    assert(reg_d <= 12);

    unsigned int shift = TokenType(ListFront(tokens)) == TOKEN_CONSTANT ?
            ProcessImmediateShift(tokens) : ProcessRegisterShift(tokens);
    shift |= (unsigned int)MapGet(shift_codes, (int)shift_type) << 1;

    unsigned int instr = 0xD << 21;
    instr |= condition << 28;
    instr |= reg_d << 12;
    instr |= reg_d;
    instr |= shift << 4;

    SetInstruction(output, instr, offset);
}