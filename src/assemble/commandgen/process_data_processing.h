/**
 * @file process_data_processing.h
 * @author Bartłomiej Cieślar
 * @brief data processing instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_

#include <stddata.h>
#include <stdbool.h>

/**
 * @brief Handles all data processing instructions where the operand is a constant
 */
bool LayoutProcConst(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

/**
 * @brief Handles all data processing instructions where the operand is a register shifted by a constant amount
 */
bool LayoutProcShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

/**
 * @brief Handles all data processing instructions where the operand is a register shifted by a variable amount
 */
bool LayoutProcShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_ */
