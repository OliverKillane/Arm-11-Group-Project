#include "process_data_processing.h"
#include <stddata.h>
#include "common_defs.h"
#include <stdio.h>
#include <setjmp.h>
#include "../tokenizer.h"
#include "../error.h"

static jmp_buf error_jump;

static inline unsigned int ProcessBaseRegisters(List restrict tokens) {
    if(ListSize(tokens) < 2) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_TOO_SHORT);
        longjmp(error_jump, 1);
    }
    
    InstructionType base = TokenInstructionType(ListFront(tokens));
    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));

    int opcode = MapGet(data_proc_opcodes, (int)base);

    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_EXPECTED_REGISTER);
        longjmp(error_jump, 1);
    }
    unsigned int reg_d, reg_n, set_cspr;
    if(base == INSTR_MOV) {
        reg_d = TokenRegisterNumber(ListFront(tokens));
        DeleteToken(ListPopFront(tokens));
        reg_n = 0;
        set_cspr = 0;
    } else if(SetQuery(comp_funcs, (int)base)) {
        reg_d = 0;
        reg_n = TokenRegisterNumber(ListFront(tokens));
        DeleteToken(ListPopFront(tokens));
        set_cspr = 1;
    } else {
        if(ListSize(tokens) < 2) {
            SetErrorCode(STAGE_DATA_PROCESSING, ERROR_TOO_SHORT);
            longjmp(error_jump, 1);
        }
        if(TokenType(ListGet(tokens, 1)) != TOKEN_REGISTER) {
            SetErrorCode(STAGE_DATA_PROCESSING, ERROR_EXPECTED_REGISTER);
            longjmp(error_jump, 1);
        }
        reg_d = TokenRegisterNumber(ListFront(tokens));
        DeleteToken(ListPopFront(tokens));
        reg_n = TokenRegisterNumber(ListFront(tokens));
        DeleteToken(ListPopFront(tokens));
        set_cspr = 0;
    }
    if(reg_d > 12 || reg_n > 12) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_INVALID_REGISTER);
        longjmp(error_jump, 1);
    }

    unsigned int instruction = 0;
    instruction |= condition << 28;
    instruction |= opcode << 21;
    instruction |= set_cspr << 20;
    instruction |= reg_n << 16;
    instruction |= reg_d << 12;
    return instruction;
}

static inline unsigned int ConvertLongToRotated(unsigned long long value) {
    return (unsigned int)value | (value >> 32);
}

static inline unsigned int ProcessImmediate(List restrict tokens) {
    if(ListSize(tokens) > 1) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_TOO_LONG);
        longjmp(error_jump, 1);
    }

    const long long expr_value_signed = TokenConstantValue(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    if(expr_value_signed < 0) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_CONST_OOB);
        longjmp(error_jump, 1);
    }
    unsigned long long expr_value = expr_value_signed;

    unsigned int rotate_right = 0;
    while(rotate_right < 16 && ConvertLongToRotated(expr_value) >= (1<<8)) {
        rotate_right++;
        expr_value <<= 2;
    }
    expr_value = ConvertLongToRotated(expr_value);
    if(expr_value >= (1<<8)) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_CONST_OOB);
        longjmp(error_jump, 1);
    }

    int operand2 = 0;
    operand2 |= rotate_right << 8;
    operand2 |= expr_value;

    return operand2;
}

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

static inline unsigned int ProcessRegister(List restrict tokens) {
    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_EXPECTED_REGISTER);
        longjmp(error_jump, 1);
    }
    unsigned int reg_m = TokenRegisterNumber(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));
    if(reg_m > 12) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_INVALID_REGISTER);
        longjmp(error_jump, 1);
    }
    
    unsigned int shift = 0;
    if(ListSize(tokens) > 0) {
        if(ListSize(tokens) < 2) {
            SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_TOO_SHORT);
            longjmp(error_jump, 1);
        }
        if(ListSize(tokens) > 2) {
            SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_TOO_LONG);
            longjmp(error_jump, 1);
        }
        if(TokenType(ListFront(tokens)) != TOKEN_INSTRUCTION || 
                TokenInstructionConditionType(ListFront(tokens)) != COND_AL || 
                !MapQuery(shift_codes, (int)TokenInstructionType(ListFront(tokens)))) {
            SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_EXPECTED_CONDITIONLESS_SHIFT);
            longjmp(error_jump, 1);
        }
        const unsigned int shift_code = 
                MapGet(shift_codes, (int)TokenInstructionType(ListFront(tokens)));
        DeleteToken(ListPopFront(tokens));
        
        shift |= shift_code << 1;

        shift |= TokenType(ListFront(tokens)) == TOKEN_CONSTANT ?
            ProcessImmediateShift(tokens) : ProcessRegisterShift(tokens);
    }

    int operand2 = 0;
    operand2 |= reg_m;
    operand2 |= shift << 4;

    return operand2;
}

bool ProcessDataProcessing(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(setjmp(error_jump) != 0) {
        return true;
    }
    unsigned int instruction = ProcessBaseRegisters(tokens);

    if(ListEmpty(tokens)) {
        SetErrorCode(STAGE_DATA_PROCESSING, ERROR_TOO_SHORT);
        longjmp(error_jump, 1);
    }
    unsigned int immediate = 0;
    if(TokenType(ListFront(tokens)) == TOKEN_CONSTANT) {
        if(TokenConstantType(ListFront(tokens)) != CONST_HASH) {
            SetErrorCode(STAGE_DATA_PROCESSING, ERROR_EXPECTED_HASH_CONSTANT);
            longjmp(error_jump, 1);
        }
        immediate = 1;
    }

    unsigned int operand2 = immediate ? ProcessImmediate(tokens) : ProcessRegister(tokens);

    instruction |= immediate << 25;
    instruction |= operand2;
    SetInstruction(output, instruction, offset);
    return false;
}