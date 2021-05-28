#include "process_multiply.h"
#include <stddata.h>
#include <string.h>
#include "common_defs.h"
#include "../tokenizer.h"
#include "../error.h"

bool ProcessMultiply(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {

    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    unsigned int accumulate = TokenInstructionType(ListPopFront(tokens)) == INSTR_MLA;

    if(ListSize(tokens) - accumulate < 3) {
        SetErrorCode(STAGE_MULTIPLY, ERROR_TOO_SHORT);
        return true;
    }
    if(ListSize(tokens) - accumulate > 3) {
        SetErrorCode(STAGE_MULTIPLY, ERROR_TOO_LONG);
        return true;
    }
    LISTFOR(tokens, iter) {
        if(TokenType(ListIteratorGet(iter)) != TOKEN_REGISTER) {
            SetErrorCode(STAGE_MULTIPLY, ERROR_EXPECTED_REGISTER);
            return true;
        }
        if(TokenRegisterNumber(ListIteratorGet(iter)) > 12) {
            SetErrorCode(STAGE_MULTIPLY, ERROR_INVALID_REGISTER);
            return true;
        }
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
    return false;
}