#ifndef ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_

#include <stddata.h>

/*
 * Processes multiply commands
 */
void ProcessMultiply(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_ */
