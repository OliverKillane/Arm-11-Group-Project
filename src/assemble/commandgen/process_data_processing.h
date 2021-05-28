#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_

#include <stddata.h>

/*
 * Processes a data processing command
 */
bool ProcessDataProcessing(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_ */
