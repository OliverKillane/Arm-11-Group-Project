/**
 * @file commandgen.h
 * @author Bartłomiej Cieślar
 * @brief The top header for binary command generation
 */
#ifndef ASSEMBLE_FUNCTIONGEN_H_
#define ASSEMBLE_FUNCTIONGEN_H_

#include <stddata.h>
#include <stdbool.h>
#include "commandgen/common_defs.h"

/**
 * @brief Processes a single instruction
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param text Vector<int> representing the text section of the final executable
 * @param data Vector<int> representing the data section of the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 */
bool FunctionGen(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data,
    int offset,
    int instructions_num
);

#endif /* ASSEMBLE_FUNCTIONGEN_H_ */
