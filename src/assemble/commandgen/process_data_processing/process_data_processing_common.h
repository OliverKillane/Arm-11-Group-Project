#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_COMMON_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_COMMON_H_

bool LayoutProcConst(
    Vector output, 
    int offset,
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int constant
);

bool LayoutProcReg(
    Vector output, 
    int offset, 
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int reg_m
);

bool LayoutProcShiftConst(
    Vector output, 
    int offset, 
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int reg_m,
    unsigned int shift_code,
    unsigned int constant
);

bool LayoutProcShiftReg(
    Vector output, 
    int offset, 
    unsigned int cond,
    unsigned int opcode,
    unsigned int set,
    unsigned int reg_d,
    unsigned int reg_n,
    unsigned int reg_m,
    unsigned int shift_code,
    unsigned int reg_s
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_COMMON_H_ */
