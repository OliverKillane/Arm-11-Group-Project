#include "process_multiply.h"
<<<<<<< HEAD
#include <stddata.h>
#include <string.h>
#include "common_defs.h"
#include "../tokenizer.h"
#include "../error.h"

bool ProcessMultiply(
    Map restrict symbols, 
    List restrict tokens, 
=======
#include "../tokenizer.h"
#include <stddata.h>

bool LayoutMUL(
    Map restrict symbols, 
    Vector restrict tokens, 
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
<<<<<<< HEAD

    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    unsigned int accumulate = TokenInstructionType(ListFront(tokens)) == INSTR_MLA;
    DeleteToken(ListPopFront(tokens));

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
    unsigned int reg_d = TokenRegisterNumber(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    unsigned int reg_m = TokenRegisterNumber(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    unsigned int reg_s = TokenRegisterNumber(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    unsigned int reg_n = accumulate ? TokenRegisterNumber(ListFront(tokens)) : 0;

    unsigned int instruction = 9 << 4;
    instruction |= condition << 28;
    instruction |= accumulate << 21;
    instruction |= reg_d << 16;
    instruction |= reg_n << 12;
    instruction |= reg_s << 8;
    instruction |= reg_m;

    SetInstruction(output, instruction, offset);
=======
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
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    return false;
}