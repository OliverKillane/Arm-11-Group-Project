#include "instruction_layouts.h"
#include "../tokenizer.h"
#include "process_branch.h"
#include "process_multiply.h"
#include "process_shift.h"
#include "process_data_processing.h"
#include "process_data_transfer.h"
#include <stddata.h>
#include <stdbool.h>
#include <stdarg.h>

DecisionTree instruction_layouts;
List layout_tokens;
Set single_group_tokens;

unsigned long long InstructionLayoutHashFunc(void* restrict token_ptr) {
    Token token = token;
    return TokenType(token) + 
            257 * (TokenType(token) == TOKEN_INSTRUCTION ? TokenInstructionType(token) : 0);
}

bool InstructionLayoutEqFunc(void* token_a_ptr, void* token_b_ptr) {
    Token restrict token_a = token_a_ptr;
    Token restrict token_b = token_b_ptr;

    if(TokenType(token_a) != TokenType(token_b)) {
        return false;
    }

    switch(TokenType(token_a)) {
        case TOKEN_BRACE:
            return TokenIsOpenBracket(token_a) == TokenIsOpenBracket(token_b);
        case TOKEN_CONSTANT:
            return TokenConstantType(token_a) == TokenConstantType(token_b);
        case TOKEN_INSTRUCTION:
            if(SetQuery(single_group_tokens, TokenInstructionType(token_a))) {
                return TokenInstructionType(token_a) == TokenInstructionType(token_b);
            }
            if(TokenInstructionType(token_a) == INSTR_STR || 
               TokenInstructionType(token_a) == INSTR_LDR) {
                return TokenInstructionType(token_b) == INSTR_STR ||
                       TokenInstructionType(token_b) == INSTR_LDR;
            }
            if(TokenInstructionType(token_a) == INSTR_TST || 
               TokenInstructionType(token_a) == INSTR_TEQ ||
               TokenInstructionType(token_a) == INSTR_CMP) {
                return TokenInstructionType(token_b) == INSTR_TST || 
                       TokenInstructionType(token_b) == INSTR_TEQ ||
                       TokenInstructionType(token_b) == INSTR_CMP;
            }
            return true;
            
        default:
            return true;
    }
}

void InitSingleGroupTokens() {
    single_group_tokens = NewEmptySet(UnsafeIntHash, UnsafeIntEq);
    SetInsert(single_group_tokens, INSTR_MOV);
    SetInsert(single_group_tokens, INSTR_MUL);
    SetInsert(single_group_tokens, INSTR_MLA);
    SetInsert(single_group_tokens, INSTR_BRN);
}

void AddSingleLayout(char* layout_str, bool(*func)(Map, Vector, Vector, int, int), ...) {
    va_list args;
    va_start(args, func);

    List layout = NewEmptyList();
    for(;layout_str != '\0';layout_str++) {
        switch(*layout_str) {
            case 'i':
                ListPushBack(layout, NewInstructionToken(COND_AL, va_arg(args, InstructionType)));
                break;
            case 'r':
                ListPushBack(layout, NewRegisterToken(0));
                break;
            case 'c':
                ListPushBack(layout, NewConstantToken(CONST_PURE, 0));
                break;
            case '#':
                ListPushBack(layout, NewConstantToken(CONST_HASH, 0));
                break;
            case '=':
                ListPushBack(layout, NewConstantToken(CONST_EQUALS, 0));
                break;
            case 'l':
                ListPushBack(layout, NewLabelToken(""));
                break;
            case 's':
                ListPushBack(layout, NewSignToken(true));
                break;
            case '[':
                ListPushBack(layout, NewBraceToken(true));
                break;
            case ']':
                ListPushBack(layout, NewBraceToken(false));
                break;
        }
    }
    va_end(args);

    LISTFOR(layout, iter) {
        ListPushBack(layout_tokens, ListIteratorGet(iter));
    }
    DecisionTreeInsert(instruction_layouts, layout, func);
    DeleteList(layout);
}

void InitInstructionLayouts() {
    InitSingleGroupTokens();
    layout_tokens = NewEmptyList();
    instruction_layouts = NewEmptyDecisionTree(InstructionLayoutHashFunc, InstructionLayoutEqFunc);
    
    /* Data Processing Instructions */
    AddSingleLayout("irr#", LayoutComputeConst, INSTR_AND);
    AddSingleLayout("irrr", LayoutComputeReg, INSTR_AND);
    AddSingleLayout("irrri#", LayoutComputeShiftConst, INSTR_AND, INSTR_LSL);
    AddSingleLayout("irrrir", LayoutComputeShiftReg, INSTR_AND, INSTR_LSL);
    AddSingleLayout("irr#", LayoutMovConst, INSTR_MOV);
    AddSingleLayout("irrr", LayoutMovReg, INSTR_MOV);
    AddSingleLayout("irrri#", LayoutMovShiftConst, INSTR_MOV, INSTR_LSL);
    AddSingleLayout("irrrir", LayoutMovShiftReg, INSTR_MOV, INSTR_LSL);
    AddSingleLayout("irr#", LayoutTestConst, INSTR_TST);
    AddSingleLayout("irrr", LayoutTestReg, INSTR_TST);
    AddSingleLayout("irrri#", LayoutTestShiftConst, INSTR_TST, INSTR_LSL);
    AddSingleLayout("irrrir", LayoutTestShiftReg, INSTR_TST, INSTR_LSL);

    /* Multiply Instructions */
    AddSingleLayout("irrr", LayoutMUL, INSTR_MUL);
    AddSingleLayout("irrrr", LayoutMLA, INSTR_MLA);

    /* Single Data Transfer Instructions */
    AddSingleLayout("ir=", LayoutTransferConst, INSTR_LDR);
    AddSingleLayout("ir[r]", LayoutTransferPre, INSTR_LDR);
    AddSingleLayout("ir[r#]", LayoutTransferPreConst, INSTR_LDR);
    AddSingleLayout("ir[rr]", LayoutTransferPreReg, INSTR_LDR);
    AddSingleLayout("ir[rsr]", LayoutTransferPreSgnReg, INSTR_LDR);
    AddSingleLayout("ir[rri#]", LayoutTransferPreShiftConst, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rrir]", LayoutTransferPreShiftReg, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsri#]", LayoutTransferPreSgnShiftConst, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsrir]", LayoutTransferPreSgnShiftReg, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]#", LayoutTransferPostConst, INSTR_LDR);
    AddSingleLayout("ir[r]r", LayoutTransferPostReg, INSTR_LDR);
    AddSingleLayout("ir[r]sr", LayoutTransferPostSgnReg, INSTR_LDR);
    AddSingleLayout("ir[r]ri#", LayoutTransferPostShiftConst, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]rir", LayoutTransferPostShiftReg, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]sri#", LayoutTransferPostSgnShiftConst, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]srir", LayoutTransferPostSgnShiftReg, INSTR_LDR, INSTR_LSL);

    /* Branch Instructions */
    AddSingleLayout("il", LayoutBranchLabel, INSTR_BRN);
    AddSingleLayout("ic", LayoutBranchConstant, INSTR_BRN);

    /* Shift Instructions */
    AddSingleLayout("ir#", LayoutShiftConst, INSTR_LSL);
    AddSingleLayout("irr", LayoutShiftReg, INSTR_LSL);
}

void FinishInstructionLayouts() {
    DeleteDecisionTree(instruction_layouts);
    DeleteSet(single_group_tokens);
    LISTFOR(layout_tokens, iter) {
        DeleteToken(ListIteratorGet(iter));
    }
    DeleteList(layout_tokens);
}