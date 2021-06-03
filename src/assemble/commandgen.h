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
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 * @param instruction_num int representing the overall number of instructions to process
 */
bool FunctionGen(
    Map symbols, 
<<<<<<< HEAD
    List tokens, 
=======
    Vector tokens, 
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_FUNCTIONGEN_H_ */
