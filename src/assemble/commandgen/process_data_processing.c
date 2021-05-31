#include "common_defs.h"
#include "instruction_layouts.h"
#include "../tokenizer.h"
#include "process_data_processing.h"
#include <stddata.h>

static inline unsigned int ConvertLongToRotated(unsigned long long value) {
    return (unsigned int)value | (value >> 32);
}

static inline unsigned int ProcessImmediate(long long expr_value_signed) {
    unsigned long long expr_value = expr_value_signed;

    unsigned int rotate_right = 0;
    while(rotate_right < 16 && ConvertLongToRotated(expr_value) >= (1<<8)) {
        rotate_right++;
        expr_value <<= 2;
    }
    expr_value = ConvertLongToRotated(expr_value);

    int operand2 = 0;
    operand2 |= rotate_right << 8;
    operand2 |= expr_value;

    return operand2;
}

bool LayoutProcConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    InstructionType type;
    unsigned int reg_n = 0;
    unsigned int reg_d = 0;
    long long constant = 0;
    ProcessDataLayout(tokens, 4, &type, &reg_n, &reg_d, &constant);

    unsigned int cond = TokenInstructionConditionType(VectorGet(tokens, 0));
    unsigned int opcode = MapGet(data_proc_opcodes, type);
    unsigned int set = type == INSTR_TST || type == INSTR_TEQ || type == INSTR_CMP;
    SetInstruction(output, FillInstruction(
        7,
        cond, 28,
        0x1, 25,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        ProcessImmediate(constant), 0
    ), offset);
    return false;
}

bool LayoutProcShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
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
    unsigned int opcode = MapGet(data_proc_opcodes, type);
    unsigned int set = type == INSTR_TST || type == INSTR_TEQ || type == INSTR_CMP;
    SetInstruction(output, FillInstruction(
        8,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        MapGet(shift_codes, shift_name), 5,
        shift_value, 7
    ), offset);
    return false;
}

bool LayoutProcShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
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
    unsigned int opcode = MapGet(data_proc_opcodes, type);
    unsigned int set = type == INSTR_TST || type == INSTR_TEQ || type == INSTR_CMP;
    SetInstruction(output, FillInstruction(
        9,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        0x1, 4,
        MapGet(shift_codes, shift_name), 5,
        reg_s, 8
    ), offset);
    return false;
}