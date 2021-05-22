#ifndef ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_

#include <stddata.h>

/*
 * Processes shift-related commands
 */
void ProcessShift(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);


#endif /* ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_ */
