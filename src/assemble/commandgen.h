/**
 * @file commandgen.h
 * @author Bartłomiej Cieślar
 * @brief The top header for binary command generation
 */
#ifndef ASSEMBLE_FUNCTIONGEN_H_
#define ASSEMBLE_FUNCTIONGEN_H_

#include <stddata.h>
#include <commandgen/common_defs.h>

/**
 * @brief Initializes the assembly function processing
 */
void InitFunctionGen();

/**
 * @brief Processes a single command from assembly
 * 
 * @param symbols Map<char*, Token> mapping labels to the addresses they point to
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

/**
 * @brief Deallocates all helper variables
 */
void FinishFunctionGen();

#endif /* ASSEMBLE_FUNCTIONGEN_H_ */
