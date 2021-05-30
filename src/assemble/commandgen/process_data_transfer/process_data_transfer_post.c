#include "../common_defs.h"
#include "../../tokenizer.h"
#include "process_data_transfer_post.h"
#include "process_data_transfer_common.h"
#include <stddata.h>
#include <stdbool.h>

bool LayoutTransferPostConst(
    Map symbols, 
    Vector tokens, 
    Vector output, 
    int offset, 
    int instructions_num
) {
    long long data_offset = TokenConstantValue(VectorGet(tokens, 5));
    return LayoutTransferCommonOffset(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        0,
        data_offset >= 0,
        TokenInstructionType(VectorGet(tokens, 0)) == INSTR_LDR,
        TokenRegisterNumber(VectorGet(tokens, 3)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        data_offset > 0 ? data_offset : -data_offset
    );
}

bool LayoutTransferPostReg(
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
        0, 
        0
    );   
}

bool LayoutTransferPostSgnReg(
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
        0, 
        0
    );
}