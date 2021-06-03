/**
 * @file process_shift.h
 * @author Bartłomiej Cieślar
 * @brief multiply instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutMUL(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutMLA(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_MULTIPLY_H_ */
