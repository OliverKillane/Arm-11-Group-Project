#ifndef ASSEMBLE_FUNCTIONGEN_H_
#define ASSEMBLE_FUNCTIONGEN_H_

#include <stddata.h>
#include "commandgen/common_defs.h"

/*
 * Initializes the assembly function processing
 */
void InitFunctionGen();

/*
 * Processes a single command from assembly
 * 
 * @param symbols Map<char*, int> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 */
void FunctionGen(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

/*
 * Deallocates all helper variables
 */
void FinishFunctionGen();

#endif /* ASSEMBLE_FUNCTIONGEN_H_ */
