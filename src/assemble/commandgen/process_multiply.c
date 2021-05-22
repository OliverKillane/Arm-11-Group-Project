#include "process_multiply.h"
#include <stddata.h>
#include <string.h>
#include "common_defs.h"

void ProcessMultiply(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    unsigned int condition;
    char func_base[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(ListPopFront(tokens), func_base, &condition);

    unsigned int accumulate = strcmp(func_base, "mla") == 0;
    assert(ListSize(tokens) - accumulate == 3);
    LISTFOR(tokens, iter) {
        assert(IsRegister(ListIteratorGet(iter)));
        assert(GetRegisterNum(ListIteratorGet(iter)) <= 12);
    }
    unsigned int reg_d = GetRegisterNum(ListPopFront(tokens));
    unsigned int reg_m = GetRegisterNum(ListPopFront(tokens));
    unsigned int reg_s = GetRegisterNum(ListPopFront(tokens));
    unsigned int reg_n = accumulate ?  GetRegisterNum(ListPopFront(tokens)) : 0;

    unsigned int instruction = 9 << 4;
    instruction |= condition << 28;
    instruction |= accumulate << 21;
    instruction |= reg_d << 16;
    instruction |= reg_n << 12;
    instruction |= reg_s << 8;
    instruction |= reg_m;

    SetInstruction(output, instruction, offset);
}