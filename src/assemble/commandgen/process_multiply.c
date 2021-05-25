#include "process_multiply.h"
#include <stddata.h>
#include <string.h>
#include "common_defs.h"
#include "../tokenizer.h"

void ProcessMultiply(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(ListSize(tokens) >= 3);

    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    unsigned int accumulate = TokenInstructionType(ListPopFront(tokens)) == INSTR_MLA;

    assert(ListSize(tokens) - accumulate == 3);
    LISTFOR(tokens, iter) {
        assert(TokenType(ListIteratorGet(iter)) == TOKEN_REGISTER);
        assert(TokenRegisterNumber(ListIteratorGet(iter)) <= 12);
    }
    unsigned int reg_d = TokenRegisterNumber(ListPopFront(tokens));
    unsigned int reg_m = TokenRegisterNumber(ListPopFront(tokens));
    unsigned int reg_s = TokenRegisterNumber(ListPopFront(tokens));
    unsigned int reg_n = accumulate ? TokenRegisterNumber(ListPopFront(tokens)) : 0;

    unsigned int instruction = 9 << 4;
    instruction |= condition << 28;
    instruction |= accumulate << 21;
    instruction |= reg_d << 16;
    instruction |= reg_n << 12;
    instruction |= reg_s << 8;
    instruction |= reg_m;

    SetInstruction(output, instruction, offset);
}