/**
 * @file common_defs.h
 * @author Bartłomiej Cieślar
 * @brief Common definitions used throughout all instruction processing functions
 */
#ifndef ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_
#define ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_

#include <stddata.h>

/**
<<<<<<< HEAD
 * @brief Maps the instruction codes to the functions that generate them
 */
extern Map func_proc; // Map<char*, void(*func)(FUNC_PROC_ARGS)>
/**
=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
 * @brief Maps data processing instruction codes to their opcodes
 */
extern Map data_proc_opcodes; // Map<char*, char>
/**
<<<<<<< HEAD
 * @brief Contains all data processing instruction codes used for comparison
 */
extern Set comp_funcs; // Set<char*>
/**
=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
 * @brief Maps shift tokens into respective shift codes
 */
extern Map shift_codes; // Map<char*, char>

/**
 * @brief Initializes all the maps used for instruction generation
 */
void InitFunctionGen();

/**
 * @brief Deallocates all the maps used for instruction generation
 */
void FinishFunctionGen();

void SetInstruction(Vector restrict output, int instruction, int offset);

<<<<<<< HEAD
=======
unsigned int FillInstruction(int nfields, ...);

>>>>>>> assemble_tokenizer_commongen_using_decision_tree
#endif /* ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_ */
