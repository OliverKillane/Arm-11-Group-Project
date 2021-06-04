/**
 * @file process_shift.h
 * @author Bartłomiej Cieślar
 * @brief shift instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
);

bool LayoutShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_SHIFT_H_ */
