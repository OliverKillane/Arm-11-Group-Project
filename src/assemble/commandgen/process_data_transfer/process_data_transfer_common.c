#include "../common_defs.h"
#include "../../tokenizer.h"
#include "process_data_transfer_common.h"
#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferCommonOffset(
    Vector output,
    int offset,
    unsigned int cond,
    unsigned int pre,
    unsigned int sign,
    unsigned int load,
    unsigned int reg_n,
    unsigned int reg_d,
    unsigned int data_offset
) {
    SetInstruction(output, FillInstruction(
        8,
        cond, 28,
        0x2, 25,
        pre, 24,
        sign, 23,
        load, 20,
        reg_n, 16,
        reg_d, 12,
        data_offset
    ), offset);
}

bool LayoutTransferCommonShiftConst(
    Vector output,
    int offset,
    unsigned int cond,
    unsigned int pre,
    unsigned int sign,
    unsigned int load,
    unsigned int reg_n,
    unsigned int reg_d,
    unsigned int reg_m,
    unsigned int shift_code,
    unsigned int constant
) {
    SetInstruction(output, FillInstruction(
        10,
        cond, 28,
        0x2, 25,
        pre, 24,
        sign, 23,
        load, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        shift_code, 5,
        constant, 7
    ), offset);
}

bool LayoutTransferCommonShiftReg(
    Vector output,
    int offset,
    unsigned int cond,
    unsigned int pre,
    unsigned int sign,
    unsigned int load,
    unsigned int reg_n,
    unsigned int reg_d,
    unsigned int reg_m,
    unsigned int shift_code,
    unsigned int reg_s
) {
    SetInstruction(output, FillInstruction(
        11,
        cond, 28,
        0x2, 25,
        pre, 24,
        sign, 23,
        load, 20,
        reg_n, 16,
        reg_d, 12,
        reg_m, 0,
        0x1, 4,
        shift_code, 5,
        reg_s, 8
    ), offset);
}