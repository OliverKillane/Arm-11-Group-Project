#include "process_shift.h"
#include <stddata.h>
#include "common_defs.h"

static inline unsigned int ProcessImmediateShift(List restrict tokens) {
    return GetExpressionValue(
        dummy, ListPopFront(tokens), false, true
    ) << 3;
}

static inline unsigned int ProcessRegisterShift(List restrict tokens) {
    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_s = GetRegisterNum(ListPopFront(tokens));
    assert(reg_s <= 12);
    
    return (reg_s << 4) | 1;
}

void ProcessShift(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    unsigned int condition;
    char func_base[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(ListPopFront(tokens), func_base, &condition);

    assert(MapQuery(shift_codes, func_base));

    assert(IsRegister(ListFront(tokens)));
    unsigned int reg_d = GetRegisterNum(ListPopFront(tokens));
    assert(reg_d <= 12);
    unsigned int shift = IsImmediate(ListFront(tokens), false, true) ?
            ProcessImmediateShift(tokens) : ProcessRegisterShift(tokens);

    shift |= (unsigned int)MapGet(shift_codes, func_base) << 1;

    unsigned int instruction = 13 << 21;
    instruction |= condition << 28;
    instruction |= reg_d << 12;
    instruction |= reg_d;
    instruction |= shift << 4;

    SetInstruction(output, instruction, offset);
}