/**
 * @file process_shift.h
 * @author Bartłomiej Cieślar
 * @brief shift instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_

#include <stddata.h>
#include <stdbool.h>

/**
 * @brief Handles all shift instructions where shift is by a constant amount
 */
bool LayoutShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

/**
 * @brief Handles all shift instructions where shift is by a variable amount
 */
bool LayoutShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_ */
