#ifndef ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_
#define ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_

#include <stddata.h>

#define FUNC_PROC_ARGS
extern Map dummy;
extern Map func_proc; // Map<char*, void(*func)(FUNC_PROC_ARGS)
extern Map func_cond_codes; // Map<char*, char>
extern Map data_proc_opcodes; // Map<char*, char>
extern Set comp_funcs; // Set<char*>
extern Map shift_codes; // Map<char*, char>
#define MAX_FUNCTION_LENGTH 3

/*
 * Initializes all the maps used for assembly command generation
 */
void InitFunctionGen();

/*
 * Deallocates all the maps used for assembly command generation
 */
void FinishFunctionGen();

/*
 * Checks if a given token represents a register (or a label looking like a register)
 */
bool IsRegister(char* token);

/*
 * Returns the index of a register
 */
int GetRegisterNum(char* reg);

/*
 * Sets a given instruction at the exact place even if the output vector is too short
 */
void SetInstruction(Vector output, int instruction, int offset);

/*
 * Retreives the raw value of an expression (might also be a label)
 */
unsigned int GetExpressionValue(
    Map symbols, 
    char* expression, 
    bool pureexpression, 
    bool hashexpression
);

/*
 * Splits a function into its base and the condition code
 */
void SplitFunction(
    char* func_code, 
    char* func_base, 
    unsigned int* condition
);

/*
 * Checks if a token represents an immediate value
 */
bool IsImmediate(char* token, bool ispure, bool ishash);

#endif /* ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_ */
