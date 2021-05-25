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

void SetInstruction(Vector restrict output, int instruction, int offset);

#endif /* ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_ */
