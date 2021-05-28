#ifndef ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_

#include <stddata.h>

/*
 * Processses a branch instruction
 */
bool ProcessBranch(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_ */
