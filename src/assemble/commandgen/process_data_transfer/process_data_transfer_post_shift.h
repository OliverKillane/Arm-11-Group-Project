#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_POST_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_POST_SHIFT_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPostShiftConst(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPostSgnShiftConst(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPostShiftReg(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPostSgnShiftReg(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_POST_SHIFT_H_ */
