#include "../common_defs.h"
#include "../../tokenizer.h"
#include "process_data_transfer_pre.h"
#include "process_data_transfer_common.h"
#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPre(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    return LayoutTransferCommonOffset(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        1,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        0
    );
}

bool LayoutTransferPreConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    long long data_offset = TokenConstantValue(VectorGet(tokens, 4));
    return LayoutTransferCommonOffset(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        1,
        data_offset >= 0,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        data_offset > 0 ? data_offset : -data_offset
    );
}

bool LayoutTransferPreReg(
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
        1,
        1,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 4)),
        0, 
        0
    );   
}

bool LayoutTransferPreSgnReg(
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
        1,
        TokenIsPlus(VectorGet(tokens, 4)),
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 5)),
        0, 
        0
    );
}