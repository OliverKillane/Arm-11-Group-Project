/**
 * @file process_data_processing.h
 * @author Bartłomiej Cieślar
 * @brief data processing instructions processing
 */

#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutProcConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutProcShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

bool LayoutProcShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_PROCESSING_H_ */
