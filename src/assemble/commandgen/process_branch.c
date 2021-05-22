#include "process_branch.h"
#include <stddata.h>
#include "common_defs.h"

void ProcessBranch(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(ListSize(tokens) == 2);

    unsigned int condition;
    char dummy[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(ListPopFront(tokens), dummy, &condition);

    const int target = GetExpressionValue(symbols, ListPopFront(tokens), true, true);
    assert(((target >> 2) << 2) == target);
    assert(target < instructions_num * 4);
    
    const long long pc_offset = (long long)target / 4 - 2 - offset;
    assert(-(2<<23) <= pc_offset && pc_offset < (2 << 23));

    unsigned int instr = 0x0A000000;
    instr |= condition << 28;
    instr |= pc_offset & 0xFFFFFF;

    SetInstruction(output, instr, offset);
}