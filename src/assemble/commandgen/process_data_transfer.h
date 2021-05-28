#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_

#include <stddata.h>

/*
 * Processes Data Transfer commands
 */
bool ProcessDataTransfer(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_ */
