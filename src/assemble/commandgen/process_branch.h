/**
 * @file process_branch.h
 * @author Bartłomiej Cieślar
 * @brief branch instruction processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutBranchLabel(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutBranchConstant(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_ */
