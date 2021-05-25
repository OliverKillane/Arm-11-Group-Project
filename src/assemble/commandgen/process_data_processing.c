#include "process_data_processing.h"
#include <stddata.h>
#include "common_defs.h"
#include <stdio.h>
#include "../tokenizer.h"

static inline unsigned int ProcessBaseRegisters(List restrict tokens) {
    assert(ListSize(tokens) >= 2);
    
    InstructionType base = TokenInstructionType(ListFront(tokens));
    ConditionType condition = TokenInstructionConditionType(ListPopFront(tokens));

    int opcode = MapGet(data_proc_opcodes, (int)base);

    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_d, reg_n, set_cspr;
    if(base == INSTR_MOV) {
        reg_d = TokenRegisterNumber(ListPopFront(tokens));
        reg_n = 0;
        set_cspr = 0;
    } else if(SetQuery(comp_funcs, (int)base)) {
        reg_d = 0;
        reg_n = TokenRegisterNumber(ListPopFront(tokens));
        set_cspr = 1;
    } else {
        assert(ListSize(tokens) >= 2);
        assert(TokenType(ListGet(tokens, 1)) == TOKEN_REGISTER);
        reg_d = TokenRegisterNumber(ListPopFront(tokens));
        reg_n = TokenRegisterNumber(ListPopFront(tokens));
        set_cspr = 0;
    }
    assert(reg_d <= 12 && reg_n <= 12);

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
    assert(ListSize(tokens) == 1);

    const long long expr_value_signed = TokenConstantValue(ListPopFront(tokens));
    assert(expr_value_signed >= 0);
    unsigned long long expr_value = expr_value_signed;

    unsigned int rotate_right = 0;
    while(rotate_right < 16 && ConvertLongToRotated(expr_value) >= (1<<8)) {
        rotate_right++;
        expr_value <<= 2;
    }
    expr_value = ConvertLongToRotated(expr_value);
    assert(expr_value < (1<<8));

    int operand2 = 0;
    operand2 |= rotate_right << 8;
    operand2 |= expr_value;

    return operand2;
}

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    const int shift_value = TokenConstantValue(ListPopFront(tokens));
    assert(shift_value >= 0 && shift_value < 32);
    return shift_value << 3;
}

static inline unsigned int ProcessRegisterShift(List restrict tokens) {
    assert(TokenType(ListFront(tokens)) == TOKEN_REGISTER);
    unsigned int reg_s = TokenRegisterNumber(ListPopFront(tokens));
    assert(reg_s <= 12);
    
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

void ProcessDataProcessing(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    unsigned int instruction = ProcessBaseRegisters(tokens);

    assert(!ListEmpty(tokens));
    unsigned int immediate = 0;
    if(TokenType(ListFront(tokens)) == TOKEN_CONSTANT) {
        assert(TokenConstantType(ListFront(tokens)) == CONST_HASH);
        immediate = 1;
    }

    unsigned int operand2 = immediate ? ProcessImmediate(tokens) : ProcessRegister(tokens);

    instruction |= immediate << 25;
    instruction |= operand2;
    SetInstruction(output, instruction, offset);
}