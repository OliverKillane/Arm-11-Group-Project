#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_COMMON_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_COMMON_H_

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
);

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
);

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
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_COMMON_H_ */
