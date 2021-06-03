#include "process_branch.h"
<<<<<<< HEAD
#include <stddata.h>
#include "../tokenizer.h"
#include "../error.h"
#include "common_defs.h"
#include <stdio.h>

bool ProcessBranch(
    Map restrict symbols, 
    List restrict tokens, 
=======
#include "../tokenizer.h"
#include <stddata.h>
#include <stdio.h>

bool LayoutBranchLabel(
    Map restrict symbols, 
    Vector restrict tokens, 
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
<<<<<<< HEAD
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
=======
    SetInstruction(output, FillInstruction(
        3,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        0xA, 24,
        ((int)MapGet(symbols, TokenLabel(VectorGet(tokens, 1))) - 2 - offset) & ((1<<24) - 1), 0
    ), offset);
    return false;
}

bool LayoutBranchConstant(
    Map restrict symbols, 
    Vector restrict tokens, 
    Vector restrict output, 
    int offset, 
    int instructions_num
) {
    SetInstruction(output, FillInstruction(
        3,
        TokenInstructionConditionType(VectorGet(tokens, 0)), 28,
        0xA, 24,
        (TokenConstantValue(VectorGet(tokens, 1)) / 4 - 2 - offset) & ((1<<24) - 1), 0
    ), offset);
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
    return false;
}