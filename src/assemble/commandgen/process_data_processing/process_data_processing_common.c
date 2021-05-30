#include "../common_defs.h"
#include "../process_shift.h"
#include "../../tokenizer.h"
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
    Vector restrict output, 
    int offset,
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int constant
) {
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

bool LayoutProcReg(
    Vector restrict output, 
    int offset, 
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int reg_m
) {
    SetInstruction(output, FillInstruction(
        6,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0
    ), offset);
    return false;
}

bool LayoutProcShiftConst(
    Vector restrict output, 
    int offset, 
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int reg_m,
    unsigned int shift_code,
    unsigned int constant
) {
   SetInstruction(output, FillInstruction(
        8,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        shift_code, 5,
        constant, 7
    ), offset);
    return false;
}

bool LayoutProcShiftReg(
    Vector restrict output, 
    int offset, 
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int reg_m,
    unsigned int shift_code,
    unsigned int reg_s
) {
    SetInstruction(output, FillInstruction(
        9,
        cond, 28,
        opcode, 21,
        set, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        0x1, 4,
        shift_code, 5,
        reg_s, 8
    ), offset);
    return false;
}