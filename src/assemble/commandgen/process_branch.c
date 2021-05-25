#include "process_branch.h"
#include <stddata.h>
#include "../tokenizer.h"
#include "common_defs.h"
#include <stdio.h>

void ProcessBranch(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    assert(ListSize(tokens) == 2);

    ConditionType condition = TokenInstructionConditionType(ListPopFront(tokens));

    Token target = ListPopFront(tokens);
    long long pc_offset;
    if(TokenType(target) == TOKEN_LABEL) {
        pc_offset = (long long)MapGet(symbols, TokenLabel(target)) - 2 - offset;
    } else {
        assert(TokenType(target) == TOKEN_CONSTANT);
        assert(TokenConstantType(target) == CONST_PURE);
        assert((TokenConstantValue(target) / 4) * 4 == TokenConstantValue(target));
        pc_offset = (long long)TokenConstantValue(target) / 4 - 2 - offset;
    }
    assert(pc_offset < instructions_num);
    assert(-(2<<23) <= pc_offset && pc_offset < (2 << 23));

    unsigned int instr = 0x0A000000;
    instr |= condition << 28;
    instr |= pc_offset & 0xFFFFFF;

    SetInstruction(output, instr, offset);
}