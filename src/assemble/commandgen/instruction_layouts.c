#include "instruction_layouts.h"
#include "../tokenizer.h"
#include "process_branch.h"
#include "process_multiply.h"
#include "process_shift.h"
#include "process_data_processing.h"
#include "process_data_transfer.h"
#include "process_alias.h"
#include <stddata.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

DecisionTree instruction_layouts;
DecisionTree data_layouts;
DecisionTree bracket_layouts;
List layout_tokens;
List data_layout_vectors;
Set single_group_tokens;

unsigned long long InstructionLayoutHashFunc(void* token_ptr) {
    Token token = token_ptr;
    return TokenType(token);
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
            return TokenConstantType(token_a) == TokenConstantType(token_b) ||
                   TokenConstantType(token_a) == CONST_ANY || 
                   TokenConstantType(token_b) == CONST_ANY;
        case TOKEN_INSTRUCTION:
            if(SetQuery(single_group_tokens, (void*)TokenInstructionType(token_a)) ||
               SetQuery(single_group_tokens, (void*)TokenInstructionType(token_b))) {
                return TokenInstructionType(token_a) == TokenInstructionType(token_b);
            }
            if(TokenInstructionType(token_a) == INSTR_STR || 
               TokenInstructionType(token_a) == INSTR_LDR ||
               TokenInstructionType(token_b) == INSTR_STR || 
               TokenInstructionType(token_b) == INSTR_LDR) {
                return (TokenInstructionType(token_a) == INSTR_STR ||
                       TokenInstructionType(token_a) == INSTR_LDR) &&
                       (TokenInstructionType(token_b) == INSTR_STR ||
                       TokenInstructionType(token_b) == INSTR_LDR);
            }
            if(TokenInstructionType(token_a) == INSTR_TST || 
               TokenInstructionType(token_a) == INSTR_TEQ ||
               TokenInstructionType(token_a) == INSTR_CMP ||
               TokenInstructionType(token_b) == INSTR_TST || 
               TokenInstructionType(token_b) == INSTR_TEQ ||
               TokenInstructionType(token_b) == INSTR_CMP) {
                return (TokenInstructionType(token_a) == INSTR_TST || 
                       TokenInstructionType(token_a) == INSTR_TEQ ||
                       TokenInstructionType(token_a) == INSTR_CMP) &&
                       (TokenInstructionType(token_b) == INSTR_TST || 
                       TokenInstructionType(token_b) == INSTR_TEQ ||
                       TokenInstructionType(token_b) == INSTR_CMP);
            }
            if(TokenInstructionType(token_a) == INSTR_BRN ||
               TokenInstructionType(token_a) == INSTR_BRL ||
               TokenInstructionType(token_b) == INSTR_BRN ||
               TokenInstructionType(token_b) == INSTR_BRL) {
                return (TokenInstructionType(token_a) == INSTR_BRN ||
                        TokenInstructionType(token_a) == INSTR_BRL) &&
                       (TokenInstructionType(token_b) == INSTR_BRN ||
                        TokenInstructionType(token_b) == INSTR_BRL);
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
    SetInsert(single_group_tokens, INSTR_RET);
    SetInsert(single_group_tokens, INSTR_PSH);
    SetInsert(single_group_tokens, INSTR_POP);
    SetInsert(single_group_tokens, INSTR_HLT);
}

void AddSingleLayout(char* layout_str, bool(*func)(Map, Vector, Vector, int, int), int num_indicies, 
    void* layout_args_indicies[], void* bracket_layout_result, ...) {
    va_list args;
    va_start(args, bracket_layout_result);

    List layout = NewEmptyList();
    for(;*layout_str != '\0';layout_str++) {
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
            case 's':
                ListPushBack(layout, NewSignToken(true));
                break;
            case '[':
                ListPushBack(layout, NewBraceToken(true));
                break;
            case ']':
                ListPushBack(layout, NewBraceToken(false));
                break;
            case '!':
                ListPushBack(layout, NewExclamationToken());
                break;
        }
    }
    va_end(args);

    LISTFOR(layout, iter) {
        ListPushBack(layout_tokens, ListIteratorGet(iter));
    }

    DecisionTreeInsert(instruction_layouts, layout, func);
    if(num_indicies != 0) {
        Vector layout_args = NewFilledVector(num_indicies, layout_args_indicies);
        DecisionTreeInsert(data_layouts, layout, layout_args);
        ListPushBack(data_layout_vectors, layout_args);
    }
    DecisionTreeInsert(bracket_layouts, layout, bracket_layout_result);
    DeleteList(layout);
}

void ProcessDataLayout(Vector tokens, int n, ...) {
    va_list args;
    va_start(args, n);

    Vector layout_args = DecisionTreeQuery(data_layouts, tokens);
    void* args_ptrs[n];
    for(int i = 0; i < n; i++) {
        args_ptrs[i] = va_arg(args, void*);
    }
    VectorIterator layout_args_iter = VectorBegin(layout_args);
    int i = 0;
    VECTORFOR(tokens, tokens_iter) {
        switch(TokenType(VectorIteratorGet(tokens_iter))) {
            case TOKEN_EXCLAMATION:
            case TOKEN_BRACE:
                VectorIteratorDecr(&layout_args_iter);
                break;
            case TOKEN_CONSTANT:
                *(long long*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] = 
                        TokenConstantValue(VectorIteratorGet(tokens_iter));
                break;
            case TOKEN_INSTRUCTION:
                *(InstructionType*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] =
                        TokenInstructionType(VectorIteratorGet(tokens_iter));
                break;
            case TOKEN_REGISTER:
                *(unsigned int*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] = 
                        TokenRegisterNumber(VectorIteratorGet(tokens_iter));
                break;
            case TOKEN_SIGN:
                *(unsigned int*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] = 
                        TokenIsPlus(VectorIteratorGet(tokens_iter));
                break;
        }
        i++;
        VectorIteratorIncr(&layout_args_iter);
    }
}

void InitInstructionLayouts() {
    InitSingleGroupTokens();
    layout_tokens = NewEmptyList();
    data_layout_vectors = NewEmptyList();
    instruction_layouts = NewEmptyDecisionTree(InstructionLayoutHashFunc, InstructionLayoutEqFunc);
    data_layouts = NewEmptyDecisionTree(InstructionLayoutHashFunc, InstructionLayoutEqFunc);
    bracket_layouts = NewEmptyDecisionTree(InstructionLayoutHashFunc, InstructionLayoutEqFunc);
    
    /* Data Processing Instructions */
    AddSingleLayout("irr#", LayoutProcConst, 4, (void*[]){0, 2, 1, 3}, NULL, INSTR_AND);
    AddSingleLayout("irrr", LayoutProcShiftConst, 4, (void*[]){0, 2, 1, 3}, NULL, INSTR_AND);
    AddSingleLayout("irrri#", LayoutProcShiftConst, 6, (void*[]){0, 2, 1, 3, 4, 5}, NULL, INSTR_AND, INSTR_LSL);
    AddSingleLayout("irrrir", LayoutProcShiftReg, 6, (void*[]){0, 2, 1, 3, 4, 5}, NULL, INSTR_AND, INSTR_LSL);
    AddSingleLayout("ir#", LayoutProcConst, 3, (void*[]){0, 2, 3}, NULL, INSTR_MOV);
    AddSingleLayout("irr", LayoutProcShiftConst, 3, (void*[]){0, 2, 3}, NULL, INSTR_MOV);
    AddSingleLayout("irri#", LayoutProcShiftConst, 5, (void*[]){0, 2, 3, 4, 5}, NULL, INSTR_MOV, INSTR_LSL);
    AddSingleLayout("irrir", LayoutProcShiftReg, 5, (void*[]){0, 2, 3, 4, 5}, NULL, INSTR_MOV, INSTR_LSL);
    AddSingleLayout("ir#", LayoutProcConst, 3, (void*[]){0, 1, 3}, NULL, INSTR_TST);
    AddSingleLayout("irr", LayoutProcShiftConst, 3, (void*[]){0, 1, 3}, NULL, INSTR_TST);
    AddSingleLayout("irri#", LayoutProcShiftConst, 5, (void*[]){0, 1, 3, 4, 5}, NULL, INSTR_TST, INSTR_LSL);
    AddSingleLayout("irrir", LayoutProcShiftReg, 5, (void*[]){0, 1, 3, 4, 5}, NULL, INSTR_TST, INSTR_LSL);

    /* Multiply Instructions */
    AddSingleLayout("irrr", LayoutMUL, 0, NULL, NULL, INSTR_MUL);
    AddSingleLayout("irrrr", LayoutMLA, 0, NULL, NULL, INSTR_MLA);

    /* Single Data Transfer Instructions */
    AddSingleLayout("ir=", LayoutTransferSet, 0, NULL, NULL, INSTR_LDR);
    AddSingleLayout("ir[r]", LayoutTransferConst, 3, (void*[]){0, 2, 1}, 1, INSTR_LDR);
    AddSingleLayout("ir[r#]", LayoutTransferConst, 4, (void*[]){0, 2, 1, 3}, 1, INSTR_LDR);
    AddSingleLayout("ir[rr]", LayoutTransferShiftConst, 4, (void*[]){0, 2, 1, 3}, 1, INSTR_LDR);
    AddSingleLayout("ir[rsr]", LayoutTransferShiftConst, 5, (void*[]){0, 2, 1, 4, 3}, 1, INSTR_LDR);
    AddSingleLayout("ir[rri#]", LayoutTransferShiftConst, 6, (void*[]){0, 2, 1, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rrir]", LayoutTransferShiftReg, 6, (void*[]){0, 2, 1, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsri#]", LayoutTransferShiftConst, 7, (void*[]){0, 2, 1, 4, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsrir]", LayoutTransferShiftReg, 7, (void*[]){0, 2, 1, 4, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r#]!", LayoutTransferConst, 4, (void*[]){0, 2, 1, 3}, 2, INSTR_LDR);
    AddSingleLayout("ir[rr]!", LayoutTransferShiftConst, 4, (void*[]){0, 2, 1, 3}, 2, INSTR_LDR);
    AddSingleLayout("ir[rsr]!", LayoutTransferShiftConst, 5, (void*[]){0, 2, 1, 4, 3}, 2, INSTR_LDR);
    AddSingleLayout("ir[rri#]!", LayoutTransferShiftConst, 6, (void*[]){0, 2, 1, 3, 5, 6}, 2, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rrir]!", LayoutTransferShiftReg, 6, (void*[]){0, 2, 1, 3, 5, 6}, 2, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsri#]!", LayoutTransferShiftConst, 7, (void*[]){0, 2, 1, 4, 3, 5, 6}, 2, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsrir]!", LayoutTransferShiftReg, 7, (void*[]){0, 2, 1, 4, 3, 5, 6}, 2, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]#", LayoutTransferConst, 4, (void*[]){0, 2, 1, 3}, 0, INSTR_LDR);
    AddSingleLayout("ir[r]r", LayoutTransferShiftConst, 4, (void*[]){0, 2, 1, 3}, 0, INSTR_LDR);
    AddSingleLayout("ir[r]sr", LayoutTransferShiftConst, 5, (void*[]){0, 2, 1, 4, 3}, 0, INSTR_LDR);
    AddSingleLayout("ir[r]ri#", LayoutTransferShiftConst, 6, (void*[]){0, 2, 1, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]rir", LayoutTransferShiftReg, 6, (void*[]){0, 2, 1, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]sri#", LayoutTransferShiftConst, 7, (void*[]){0, 2, 1, 4, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]srir", LayoutTransferShiftReg, 7, (void*[]){0, 2, 1, 4, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);

    /* Branch Instructions */
    AddSingleLayout("ic", LayoutBranchConstant, 0, NULL, NULL, INSTR_BRN);

    /* Shift Instructions */
    AddSingleLayout("ir#", LayoutShiftConst, 0, NULL, NULL, INSTR_LSL);
    AddSingleLayout("irr", LayoutShiftReg, 0, NULL, NULL, INSTR_LSL);

    /* Aliased Instructions */
    AddSingleLayout("i", LayoutRet, 0, NULL, NULL, INSTR_RET);
    AddSingleLayout("i", LayoutHalt, 0, NULL, NULL, INSTR_HLT);
    AddSingleLayout("ir", LayoutPush, 2, (void*[]){0, 1}, NULL, INSTR_PSH);
    AddSingleLayout("ir", LayoutPop, 2, (void*[]){0, 1}, NULL, INSTR_POP);
}

void FinishInstructionLayouts() {
    DeleteDecisionTree(instruction_layouts);
    DeleteDecisionTree(data_layouts);
    DeleteDecisionTree(bracket_layouts);
    DeleteSet(single_group_tokens);
    LISTFOR(layout_tokens, iter) {
        DeleteToken(ListIteratorGet(iter));
    }
    LISTFOR(data_layout_vectors, iter) {
        DeleteVector(ListIteratorGet(iter));
    }
    DeleteList(layout_tokens);
    DeleteList(data_layout_vectors);
}