#include "process_data_transfer.h"
#include <stddata.h>
#include "common_defs.h"
#include "../tokenizer.h"

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    assert(TokenConstantType(ListFront(tokens)) == CONST_HASH);
    return TokenConstantValue(ListPopFront(tokens)) << 3;
}

static inline unsigned int ProcessRegisterShift(List restrict tokens) {
    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_s = TokenRegisterNumber(ListPopFront(tokens));
    return (reg_s << 4) | 1;
}

static inline unsigned int ProcessRegister(List restrict tokens) {
    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_m = TokenRegisterNumber(ListPopFront(tokens));
    assert(reg_m <= 12);
    
    unsigned int shift = 0;
    if(ListSize(tokens) > 0) {
        assert(ListSize(tokens) == 2);
        assert(TokenType(ListFront(tokens)) == TOKEN_INSTRUCTION);
        assert(TokenInstructionConditionType(ListFront(tokens)) == COND_AL);
        assert(MapQuery(shift_codes, (int)TokenInstructionType(ListFront(tokens))));
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
    assert(data_offset < (1<<12));
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
    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_d = TokenRegisterNumber(ListPopFront(tokens));
    unsigned int expression = TokenConstantValue(ListPopFront(tokens));
    if(expression < (1<<12)) {
        SetInstruction(output, ProcessLoadMov(condition, reg_d, expression), offset);
    } else {
        ProcessLoadBig(condition, reg_d, expression, output, offset, instructions_num);
    }
}

void ProcessDataTransfer(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(ListSize(tokens) >= 3);

    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    unsigned int load_flag = TokenInstructionType(ListPopFront(tokens)) == INSTR_LDR;

    if(load_flag && TokenType(ListBack(tokens)) == TOKEN_CONSTANT && 
       TokenConstantType(ListBack(tokens)) == CONST_EQUALS
    ) {
        ProcessLoadConst(condition, tokens, output, offset, instructions_num);
        return;
    }

    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_d = TokenRegisterNumber(ListPopFront(tokens));
    assert(reg_d <= 12);

    assert(TokenType(ListFront(tokens)) == TOKEN_BRACE);
    assert(TokenIsOpenBracket(ListPopFront(tokens)));
    assert(ListSize(tokens) >= 2);

    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_n = TokenRegisterNumber(ListPopFront(tokens));

    unsigned int pre_flag;
    if(TokenType(ListBack(tokens)) == TOKEN_BRACE) {
        assert(!TokenIsOpenBracket(ListBack(tokens)));
        pre_flag = 1;
        ListPopBack(tokens);
    } else {
        assert(TokenType(ListFront(tokens)) == TOKEN_BRACE);
        assert(!TokenIsOpenBracket(ListFront(tokens)));
        pre_flag = 0;
        ListPopFront(tokens);
    }

    unsigned int operand = 0;
    unsigned int up_flag = 1;
    unsigned int immediate_flag = 0;

    if(!ListEmpty(tokens)) {
        if(TokenType(ListFront(tokens)) == TOKEN_CONSTANT) {
            assert(TokenConstantType(ListFront(tokens)) == CONST_HASH);
            long long value = TokenConstantValue(ListPopFront(tokens));
            assert(ListEmpty(tokens));
            up_flag = value >= 0;
            assert(value < (1<<12) && value > -(1<<12));
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
}