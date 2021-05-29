#include "process_branch.h"
#include <stddata.h>
#include "../tokenizer.h"
#include "../error.h"
#include "common_defs.h"
#include <stdio.h>

bool ProcessBranch(
    Map restrict symbols, 
    List restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    if(ListSize(tokens) < 2) {
        SetErrorCode(STAGE_BRANCH, ERROR_TOO_SHORT);
        return true;
    }

    if(ListSize(tokens) > 2) {
        SetErrorCode(STAGE_BRANCH, ERROR_TOO_LONG);
        return true;
    }

    ConditionType condition = TokenInstructionConditionType(ListFront(tokens));
    DeleteToken(ListPopFront(tokens));

    Token target = ListPopFront(tokens);
    long long pc_offset;
    if(TokenType(target) == TOKEN_LABEL) {
        if(!MapQuery(symbols, TokenLabel(target))) {
            SetErrorCode(STAGE_BRANCH, ERROR_INVALID_LABEL);
            return true;
        }
        pc_offset = (long long)MapGet(symbols, TokenLabel(target)) - 2 - offset;
    } else {
        if(TokenType(target) != TOKEN_CONSTANT || TokenConstantType(target) != CONST_PURE) {
            SetErrorCode(STAGE_BRANCH, ERROR_EXPECTED_LABEL_OR_PURE_CONSTANT);
            return true;
        }
        if((TokenConstantValue(target) / 4) * 4 != TokenConstantValue(target)) {
            SetErrorCode(STAGE_BRANCH, ERROR_EXPECTED_4_DIVISIBLE);
            return true;
        }
        pc_offset = (long long)TokenConstantValue(target) / 4 - 2 - offset;
    }
    DeleteToken(target);
    if(pc_offset + 2 + offset >= instructions_num) {
        SetErrorCode(STAGE_BRANCH, ERROR_CONST_OOB);
        return true;
    }

    if(-(2<<23) > pc_offset || pc_offset >= (2 << 23)) {
        SetErrorCode(STAGE_BRANCH, ERROR_OFFSET_TOO_FAR);
        return true;
    }

    unsigned int instr = 0x0A000000;
    instr |= condition << 28;
    instr |= pc_offset & 0xFFFFFF;

    SetInstruction(output, instr, offset);
    return false;
}