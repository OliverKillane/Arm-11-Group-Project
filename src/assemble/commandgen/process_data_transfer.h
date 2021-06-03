/**
 * @file process_data_transfer.h
 * @author Bartłomiej Cieślar
 * @brief data transfer instructions processing
 */

#ifndef ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_

#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferSet(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data,
    int offset, 
    int instructions_num
);

bool LayoutTransferConst(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutTransferShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

bool LayoutTransferShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_DATA_TRANSFER_H_ */
