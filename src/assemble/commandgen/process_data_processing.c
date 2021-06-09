#include "common_defs.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include "../error.h"
#include "process_data_processing.h"
#include <stddata.h>
#include <stdio.h>

bool process_immediate_error;

static inline unsigned int ConvertLongToRotated(unsigned long long value) {
    return (unsigned int)value | (value >> 32);
}

static inline unsigned int ProcessImmediate(long long expr_value_signed) {
    process_immediate_error = false;

    if(expr_value_signed < 0 || expr_value_signed >= (1ll << 32)) {
        process_immediate_error = true;
        SetErrorCode(ERROR_CONSTANT_OOB);
        return 0;
    }

    unsigned long long expr_value = expr_value_signed;

    unsigned int rotate_right = 0;
    while(rotate_right < 16 && ConvertLongToRotated(expr_value) >= (1 << 8)) {
        rotate_right++;
        expr_value <<= 2;
    }
    expr_value = ConvertLongToRotated(expr_value);

    if(expr_value >= (1 << 8)) {
        process_immediate_error = true;
        SetErrorCode(ERROR_CONSTANT_OOB);
        return 0;
    }

    int operand2 = 0;
    operand2 |= rotate_right << 8;
    operand2 |= expr_value;

    return operand2;
}

bool LayoutProcConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n = 0;
    unsigned int reg_d = 0;
    long long constant = 0;
    ProcessDataLayout(tokens, 4, &type, &reg_n, &reg_d, &constant);

    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int opcode = MapGet(data_proc_opcodes, (void*)type);
    unsigned int set = type == INSTR_TST || type == INSTR_TEQ || type == INSTR_CMP;
    unsigned int operand2 = ProcessImmediate(constant);

    if(process_immediate_error) {
        return true;
    }

    SetInstruction(text, FillInstruction(
        7,
        cond, 28,
        0x1, 25,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        operand2, 0
    ), offset);
    return false;
}

bool LayoutProcShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n = 0;
    unsigned int reg_d = 0;
    unsigned int reg_m;
    InstructionType shift_name = INSTR_LSL;
    long long shift_value = 0;
    ProcessDataLayout(tokens, 6, &type, &reg_n, &reg_d, &reg_m, &shift_name, &shift_value);

    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int opcode = MapGet(data_proc_opcodes, (void*)type);
    unsigned int set = type == INSTR_TST || type == INSTR_TEQ || type == INSTR_CMP;

    if(shift_value < 0 || shift_value > 31) {
        SetErrorCode(ERROR_CONSTANT_OOB);
        return true;
    }

    SetInstruction(text, FillInstruction(
        8,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        MapGet(shift_codes, (void*)shift_name), 5,
        shift_value, 7
    ), offset);
    return false;
}

bool LayoutProcShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict text,
    Vector restrict data, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n = 0;
    unsigned int reg_d = 0;
    unsigned int reg_m;
    InstructionType shift_name;
    unsigned int reg_s;
    ProcessDataLayout(tokens, 6, &type, &reg_n, &reg_d, &reg_m, &shift_name, &reg_s);

    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int opcode = MapGet(data_proc_opcodes, (void*)type);
    unsigned int set = type == INSTR_TST || type == INSTR_TEQ || type == INSTR_CMP;

    if(reg_s == 15) {
        SetErrorCode(ERROR_INVALID_REGISTER);
        return true;
    }

    SetInstruction(text, FillInstruction(
        9,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        0x1, 4,
        MapGet(shift_codes, (void*)shift_name), 5,
        reg_s, 8
    ), offset);
    return false;
}