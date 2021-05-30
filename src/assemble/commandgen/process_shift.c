#include "common_defs.h"
#include "process_shift.h"
#include "process_data_processing/process_data_processing_common.h"
#include "../tokenizer.h"
#include <stddata.h>

bool LayoutShiftConst(
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
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 0))),
        TokenConstantValue(VectorGet(tokens, 2))
    );
}

bool LayoutShiftReg(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    return LayoutProcShiftReg(
        output,
        offset,
        TokenInstructionConditionType(VectorGet(tokens, 0)),
        MapGet(data_proc_opcodes, TokenInstructionType(VectorGet(tokens, 0))),
        0,
        0,
        TokenRegisterNumber(VectorGet(tokens, 1)),
        TokenRegisterNumber(VectorGet(tokens, 1)),
        MapGet(shift_codes, TokenInstructionType(VectorGet(tokens, 0))),
        TokenRegisterNumber(VectorGet(tokens, 2))
    );
}