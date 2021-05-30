#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_SHIFT_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPreShiftConst(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreSgnShiftConst(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreShiftReg(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreSgnShiftReg(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_SHIFT_H_ */
