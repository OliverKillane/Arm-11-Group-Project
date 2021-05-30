#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_SHIFT_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPreShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreSgnShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreSgnShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_SHIFT_H_ */
