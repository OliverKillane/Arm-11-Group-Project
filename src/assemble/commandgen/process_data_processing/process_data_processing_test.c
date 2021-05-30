#include "../common_defs.h"
#include "../../tokenizer.h"
#include <stddata.h>
#include "process_data_processing_common.h"
#include "process_data_processing_test.h"

bool LayoutTestConst(
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
        1,
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenConstantValue(VectorGet(tokens, 2))
    );
}

bool LayoutTestReg(
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
        1,
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 2))
    );
}

bool LayoutTestShiftConst(
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
        1,
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 2)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 3))),
        TokenConstantValue(VectorGet(tokens, 4))
    );
}

bool LayoutTestShiftReg(
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
        1,
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 2)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 3))),
        TokenRegisterNumber(VectorGet(tokens, 4))
    );
}