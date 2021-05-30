#include "../common_defs.h"
#include "../../tokenizer.h"
#include <stddata.h>
#include "process_data_processing_common.h"
#include "process_data_processing_mov.h"

bool LayoutMovConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    return LayoutProcConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        MapGet(data_proc_opcodes, TokenInstructionType(VectorGet(tokens, 0))),
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        0,
        TokenConstantValue(VectorGet(tokens, 2))
    );
}

bool LayoutMovReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    return LayoutProcReg(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        MapGet(data_proc_opcodes, TokenInstructionType(VectorGet(tokens, 0))),
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        0,
        TokenRegisterNumber(VectorGet(tokens, 2))
    );
}

bool LayoutMovShiftConst(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    return LayoutProcShiftConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        MapGet(data_proc_opcodes, TokenInstructionType(VectorGet(tokens, 0))),
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        0,
        TokenRegisterNumber(VectorGet(tokens, 2)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 3))),
        TokenConstantValue(VectorGet(tokens, 4))
    );
}

bool LayoutMovShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    return LayoutProcShiftConst(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        MapGet(data_proc_opcodes, TokenInstructionType(VectorGet(tokens, 0))),
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        0,
        TokenRegisterNumber(VectorGet(tokens, 2)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 3))),
        TokenRegisterNumber(VectorGet(tokens, 4))
    );
}