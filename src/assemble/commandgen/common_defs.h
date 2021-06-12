/**
 * @file common_defs.h
 * @author Bartłomiej Cieślar
 * @brief Common definitions used throughout all instruction processing functions
 */
#ifndef ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_
#define ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_

#include <stddata.h>

/**
 * @brief Map< @ref InstructionType , unsigned int> from the data processing instructions to their opcodes
 */
extern Map data_proc_opcodes; 
/**
 * @brief Map < @ref InstructionType , unsigned int> from the shift instructions to their shift codes
 */
extern Map shift_codes;
/**
 * @brief Map < @ref LabelType , unsigned int> from the label types to the AND mask for them
 */
extern Map label_masks;

/**
 * @brief Initializes the enum maps used in the commandgen
 */
void InitFunctionGen();

/**
 * @brief Deallocates the enum maps used in the commandgen
 */
void FinishFunctionGen();

/**
 * @brief Set the instruction at a certain offset
 */
void SetInstruction(Vector restrict output, int instruction, int offset);

/**
 * @brief Assembles the instruction from data fields
 * 
 * @param nfields number of data fields in the final instructions
 * @param param the data field to put in the instruction (unsigned int)
 * @param pos the first(smallest) bit of the data field
 */
unsigned int FillInstruction(int nfields, ...);

#endif /* ASSEMBLE_COMMANDGEN_COMMON_DEFS_H_ */
