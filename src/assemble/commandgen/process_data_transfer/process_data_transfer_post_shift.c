#include "../common_defs.h"
#include "../../tokenizer.h"
#include "process_data_transfer_post_shift.h"
#include "process_data_transfer_common.h"
#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPostShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        0,
        1,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 5)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 6))),
        TokenConstantValue(VectorGet(tokens, 7))
    );
}

bool LayoutTransferPostSgnShiftConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        0,
        TokenIsPlus(VectorGet(tokens, 5)),
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 6)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 7))),
        TokenConstantValue(VectorGet(tokens, 8))
    );
}

bool LayoutTransferPostShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftReg(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        0,
        1,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 5)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 6))),
        TokenRegisterNumber(VectorGet(tokens, 7))
    );
}

bool LayoutTransferPostSgnShiftReg(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonShiftReg(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        0,
        TokenIsPlus(VectorGet(tokens, 5)),
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 6)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 7))),
        TokenRegisterNumber(VectorGet(tokens, 8))
    );
}