#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_POST_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_POST_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPostConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPostReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutTransferPostSgnReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_PROCESS_DATA_PROCESSING_POST_H_ */
