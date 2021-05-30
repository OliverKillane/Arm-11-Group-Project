#include "../common_defs.h"
#include "../../tokenizer.h"
#include <stddata.h>
#include "process_data_processing_common.h"
#include "process_data_processing_compute.h"

bool LayoutComputeConst(
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
        TokenRegisterNumber(VectorGet(tokens, 2)),
        TokenConstantValue(VectorGet(tokens, 3))
    );
}

bool LayoutComputeReg(
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
        TokenRegisterNumber(VectorGet(tokens, 2)),
        TokenRegisterNumber(VectorGet(tokens, 3))
    );
}

bool LayoutComputeShiftConst(
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
        TokenRegisterNumber(VectorGet(tokens, 2)),
        TokenRegisterNumber(VectorGet(tokens, 3)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 4))),
        TokenConstantValue(VectorGet(tokens, 5))
    );
}

bool LayoutComputeShiftReg(
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
        TokenRegisterNumber(VectorGet(tokens, 2)),
        TokenRegisterNumber(VectorGet(tokens, 3)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 4))),
        TokenRegisterNumber(VectorGet(tokens, 5))
    );
}