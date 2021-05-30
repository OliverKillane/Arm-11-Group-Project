#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_MOV_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_MOV_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutMovConst(
    Map symbols,
    Vector tokens,
    Vector output,
    int offset,
    int instructions_num
);

bool LayoutMovReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutMovShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutMovShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_MOV_H_ */
