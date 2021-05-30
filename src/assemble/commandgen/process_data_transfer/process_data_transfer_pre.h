#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPre(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPreSgnReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_PRE_H_ */
