#include "process_shift.h"
#include <stddata.h>
#include "common_defs.h"
#include "../tokenizer.h"
#include "../error.h"
#include <setjmp.h>

static jmp_buf error_jump;

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    if(TokenConstantType(ListFront(tokens)) != CONST_HASH) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_EXPECTED_REGISTER_OR_HASH_CONSTANT);
        longjmp(error_jump, 1);
    }
    const unsigned long long shift_value = TokenConstantValue(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    if(shift_value >= 32 && shift_value < 0) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_SHIFT_OOB);
        longjmp(error_jump, 1);
    }
    return shift_value << 3;
}

static inline unsigned int ProcessRegisterShift(List restrict tokens) {
    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_EXPECTED_REGISTER_OR_HASH_CONSTANT);
        longjmp(error_jump, 1);
    }
    unsigned int reg_s = TokenRegisterNumber(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    if(reg_s > 12) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_INVALID_REGISTER);
        longjmp(error_jump, 1);
    }
    
    return (reg_s << 4) | 1;
}

bool ProcessShift(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(setjmp(error_jump) != 0) {
        return true;
    }

    InstructionType shift_type = TokenInstructionType(ListFront(tokens));
    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));

    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_EXPECTED_REGISTER);
        longjmp(error_jump, 1);
    }
    unsigned int reg_d = TokenRegisterNumber(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    if(reg_d > 12) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_INVALID_REGISTER);
        longjmp(error_jump, 1);
    }

    unsigned int shift = TokenType(ListFront(tokens)) == TOKEN_CONSTANT ?
            ProcessImmediateShift(tokens) : ProcessRegisterShift(tokens);

    if(!ListEmpty(tokens)) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_TOO_LONG);
        longjmp(error_jump, 1);
    }
    
    shift |= (unsigned int)MapGet(shift_codes, (int)shift_type) << 1;

    unsigned int instr = 0xD << 21;
    instr |= condition << 28;
    instr |= reg_d << 12;
    instr |= reg_d;
    instr |= shift << 4;

    SetInstruction(output, instr, offset);
    return false;
}