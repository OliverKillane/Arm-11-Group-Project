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
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
);

bool LayoutBranchConstant(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_BRANCH_H_ */
