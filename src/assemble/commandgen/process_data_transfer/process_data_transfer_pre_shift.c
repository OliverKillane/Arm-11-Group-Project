#include "../common_defs.h"
#include "../../tokenizer.h"
#include "process_data_transfer_pre_shift.h"
#include "process_data_transfer_common.h"
#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPreShiftConst(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        1,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 4)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 5))),
        TokenConstantValue(VectorGet(tokens, 6))
    );
}

bool LayoutTransferPreSgnShiftConst(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        TokenIsPlus(VectorGet(tokens, 4)),
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 5)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 6))),
        TokenConstantValue(VectorGet(tokens, 7))
    );
}

bool LayoutTransferPreShiftReg(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftReg(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        1,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 4)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 5))),
        TokenRegisterNumber(VectorGet(tokens, 6))
    );
}

bool LayoutTransferPreSgnShiftReg(
    Map symbols, 
    List tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftReg(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        TokenIsPlus(VectorGet(tokens, 4)),
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 5)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 6))),
        TokenRegisterNumber(VectorGet(tokens, 7))
    );
}