#include "process_data_transfer.h"
#include <stddata.h>
#include <setjmp.h>
#include "common_defs.h"
#include "../tokenizer.h"
#include "../error.h"

jmp_buf error_jump;

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    if(TokenConstantType(ListFront(tokens)) != CONST_HASH) {
        SetErrorCode(STAGE_SHIFTED_REGISTER, ERROR_EXPECTED_REGISTER_OR_HASH_CONSTANT);
        longjmp(error_jump, 1);
    }
    const unsigned long long shift_value = TokenConstantValue(ListPopFront(tokens));
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
    unsigned int reg_s = TokenRegisterNumber(ListPopFront(tokens));
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
    unsigned int reg_m = TokenRegisterNumber(ListPopFront(tokens));
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
                MapGet(shift_codes, (int)TokenInstructionType(ListPopFront(tokens)));
        
        shift |= shift_code << 1;

        shift |= TokenType(ListFront(tokens)) == TOKEN_CONSTANT ?
            ProcessImmediateShift(tokens) : ProcessRegisterShift(tokens);
    }

    int operand2 = 0;
    operand2 |= reg_m;
    operand2 |= shift << 4;

    return operand2;
}

unsigned int ProcessLoadMov(unsigned int condition, unsigned int reg_d, unsigned int expression) {
    unsigned int instruction = 0;
    instruction |= condition << 28;
    instruction |= 0x3A << 20;
    instruction |= reg_d << 12;
    instruction |= expression;
    return instruction;
}

void ProcessLoadBig(
    unsigned int condition,
    unsigned int reg_d, 
    unsigned int expression, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(VectorSize(output) < instructions_num) {
        VectorResize(output, instructions_num);
    }
    unsigned int data_offset = VectorSize(output) * 4 - 8 - offset * 4;
    if(data_offset >= (1<<12)) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_OFFSET_TOO_FAR);
        longjmp(error_jump, 1);
    }
    VectorPushBack(output, expression);

    unsigned int instruction = 0;
    instruction |= condition << 28;
    instruction |= 0x59 << 20;
    instruction |= 0xF << 16;
    instruction |= reg_d << 12;
    instruction |= data_offset;

    SetInstruction(output, instruction, offset);
}

void ProcessLoadConst(
    unsigned int condition, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_REGISTER);
        longjmp(error_jump, 1);
    }
    unsigned int reg_d = TokenRegisterNumber(ListPopFront(tokens));
    unsigned int expression = TokenConstantValue(ListPopFront(tokens));
    if(!ListEmpty(tokens)) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_TOO_LONG);
        longjmp(error_jump, 1);
    }
    if(expression < (1<<8)) {
        SetInstruction(output, ProcessLoadMov(condition, reg_d, expression), offset);
    } else {
        ProcessLoadBig(condition, reg_d, expression, output, offset, instructions_num);
    }
}

bool ProcessDataTransfer(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(setjmp(error_jump) != 0) {
        return true;
    }

    if(ListSize(tokens) < 3) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_TOO_SHORT);
        longjmp(error_jump, 1);
    }

    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    unsigned int load_flag = TokenInstructionType(ListPopFront(tokens)) == INSTR_LDR;

    if(load_flag && TokenType(ListBack(tokens)) == TOKEN_CONSTANT && 
       TokenConstantType(ListBack(tokens)) == CONST_EQUALS
    ) {
        ProcessLoadConst(condition, tokens, output, offset, instructions_num);
        return false;
    }

    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_REGISTER);
        longjmp(error_jump, 1);
    }
    
    unsigned int reg_d = TokenRegisterNumber(ListPopFront(tokens));
    if(reg_d > 12) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_INVALID_REGISTER);
        longjmp(error_jump, 1);
    }

    if(TokenType(ListFront(tokens)) != TOKEN_BRACE || !TokenIsOpenBracket(ListPopFront(tokens))) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_EQUALS_CONSTANT_OR_BRACE);
        longjmp(error_jump, 1);
    }
    if(ListSize(tokens) < 2) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_TOO_SHORT);
        longjmp(error_jump, 1);
    }

    if(TokenType(ListFront(tokens)) != TOKEN_REGISTER) {
        SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_REGISTER);
        longjmp(error_jump, 1);
    }
    unsigned int reg_n = TokenRegisterNumber(ListPopFront(tokens));

    unsigned int pre_flag;
    if(TokenType(ListBack(tokens)) == TOKEN_BRACE) {
        if(TokenIsOpenBracket(ListBack(tokens))) {
            SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_CLOSED_BRACE);
            longjmp(error_jump, 1);
        }
        pre_flag = 1;
        ListPopBack(tokens);
    } else {
        if(TokenType(ListFront(tokens)) != TOKEN_BRACE || TokenIsOpenBracket(ListFront(tokens))) {
            SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_CLOSED_BRACE);
            longjmp(error_jump, 1);
        }
        pre_flag = 0;
        ListPopFront(tokens);
    }

    unsigned int operand = 0;
    unsigned int up_flag = 1;
    unsigned int immediate_flag = 0;

    if(!ListEmpty(tokens)) {
        if(TokenType(ListFront(tokens)) == TOKEN_CONSTANT) {
            if(TokenConstantType(ListFront(tokens)) == CONST_HASH) {
                SetErrorCode(STAGE_DATA_TRANSFER, ERROR_EXPECTED_HASH_CONSTANT);
                longjmp(error_jump, 1);
            }
            long long value = TokenConstantValue(ListPopFront(tokens));
            if(!ListEmpty(tokens)) {
                SetError(STAGE_DATA_TRANSFER, ERROR_TOO_LONG);
                longjmp(error_jump, 1);
            }
            up_flag = value >= 0;
            if(value > (1<<12) || value < -(1<<12)) {
                SetError(STAGE_DATA_TRANSFER, ERROR_CONST_OOB);
                longjmp(error_jump, 1);
            }
            operand = abs(value);
            immediate_flag = 0;
        } else {
            up_flag = TokenType(ListFront(tokens)) == TOKEN_SIGN ?
                TokenIsPlus(ListPopFront(tokens)) : 1;
            operand = ProcessRegister(tokens);
            immediate_flag = 1;
        }
    }

    int instruction = 0;
    instruction |= condition << 28;
    instruction |= 1 << 26;
    instruction |= immediate_flag << 25;
    instruction |= pre_flag << 24;
    instruction |= up_flag << 23;
    instruction |= load_flag << 20;
    instruction |= reg_n << 16;
    instruction |= reg_d << 12;
    instruction |= operand;

    SetInstruction(output, instruction, offset);
    return false;
}