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

DecisionTree restrict instruction_layouts;
DecisionTree restrict data_layouts;
DecisionTree restrict bracket_layouts;
List restrict layout_tokens;
List restrict data_layout_vectors;
Set restrict single_group_tokens;

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

void AddSingleLayout(char* layout_str, bool(*func)(Map, Vector, Vector, int, int), int num_indicies, 
    void* layout_args_indicies[], void* bracket_layout_result, ...) {
    va_list args;
    va_start(args, bracket_layout_result);

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
    VECTORFOR(tokens, tokens_iter) {
        switch(TokenType(VectorIteratorGet(tokens_iter))) {
            TOKEN_BRACE:
                VectorIteratorDecr(&layout_args_iter);
                break;
            TOKEN_CONSTANT:
                *(long long*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] = 
                        TokenConstantValue(VectorIteratorGet(tokens_iter));
                break;
            TOKEN_INSTRUCTION:
                *(InstructionType*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] =
                        TokenInstructionType(VectorIteratorGet(tokens_iter));
                break;
            TOKEN_LABEL:
                *(unsigned char**)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] =
                        TokenLabel(VectorIteratorGet(tokens_iter));
                break;
            TOKEN_REGISTER:
                *(unsigned int*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] = 
                        TokenRegisterNumber(VectorIteratorGet(tokens_iter));
                break;
            TOKEN_SIGN:
                *(unsigned int*)args_ptrs[(int)VectorIteratorGet(layout_args_iter)] = 
                        TokenIsPlus(VectorIteratorGet(tokens_iter));
                break;
        }
        VectorIteratorIncr(&layout_args_iter);
    }
}

void InitInstructionLayouts() {
    InitSingleGroupTokens();
    layout_tokens = NewEmptyList();
    data_layout_vectors = NewEmptyList();
    instruction_layouts = NewEmptyDecisionTree(InstructionLayoutHashFunc, InstructionLayoutEqFunc);
    data_layouts = NewEmptyDecisionTree(InstructionLayoutEqFunc, InstructionLayoutHashFunc);
    
    /* Data Processing Instructions */
    AddSingleLayout("irr#", LayoutProcConst, 4, (void*){0, 2, 1, 3}, NULL, INSTR_AND);
    AddSingleLayout("irrr", LayoutProcShiftConst, 4, (void*){0, 2, 1, 3}, NULL, INSTR_AND);
    AddSingleLayout("irrri#", LayoutProcShiftConst, 6, (void*){0, 2, 1, 3, 4, 5}, NULL, INSTR_AND, INSTR_LSL);
    AddSingleLayout("irrrir", LayoutProcShiftReg, 6, (void*){0, 2, 1, 3, 4, 5}, NULL, INSTR_AND, INSTR_LSL);
    AddSingleLayout("ir#", LayoutProcConst, 3, (void*){0, 2, 3}, NULL, INSTR_MOV);
    AddSingleLayout("irr", LayoutProcShiftConst, 3, (void*){0, 2, 3}, NULL, INSTR_MOV);
    AddSingleLayout("irri#", LayoutProcShiftConst, 5, (void*){0, 2, 3, 4, 5}, NULL, INSTR_MOV, INSTR_LSL);
    AddSingleLayout("irrir", LayoutProcShiftReg, 5, (void*){0, 2, 3, 4, 5}, NULL, INSTR_MOV, INSTR_LSL);
    AddSingleLayout("ir#", LayoutProcConst, 3, (void*){0, 1, 3}, NULL, INSTR_TST);
    AddSingleLayout("irr", LayoutProcShiftConst, 3, (void*){0, 1, 3}, NULL, INSTR_TST);
    AddSingleLayout("irri#", LayoutProcShiftConst, 5, (void*){0, 1, 3, 4, 5}, NULL, INSTR_TST, INSTR_LSL);
    AddSingleLayout("irrir", LayoutProcShiftReg, 5, (void*){0, 1, 3, 4, 5}, NULL, INSTR_TST, INSTR_LSL);

    /* Multiply Instructions */
    AddSingleLayout("irrr", LayoutMUL, 0, NULL, NULL, INSTR_MUL);
    AddSingleLayout("irrrr", LayoutMLA, 0, NULL, NULL, INSTR_MLA);

    /* Single Data Transfer Instructions */
    AddSingleLayout("ir=", LayoutTransferSet, 0, NULL, NULL, INSTR_LDR);
    AddSingleLayout("ir[r]", LayoutTransferConst, 3, (void*){0, 2, 1}, 1, INSTR_LDR);
    AddSingleLayout("ir[r#]", LayoutTransferConst, 4, (void*){0, 2, 1, 3}, 1, INSTR_LDR);
    AddSingleLayout("ir[rr]", LayoutTransferShiftConst, 4, (void*){0, 2, 1, 3}, 1, INSTR_LDR);
    AddSingleLayout("ir[rsr]", LayoutTransferShiftConst, 5, (void*){0, 2, 1, 4, 3}, 1, INSTR_LDR);
    AddSingleLayout("ir[rri#]", LayoutTransferShiftConst, 6, (void*){0, 2, 1, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rrir]", LayoutTransferShiftReg, 6, (void*){0, 2, 1, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsri#]", LayoutTransferShiftConst, 7, (void*){0, 2, 1, 4, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[rsrir]", LayoutTransferShiftReg, 7, (void*){0, 2, 1, 4, 3, 5, 6}, 1, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]#", LayoutTransferConst, 4, (void*){0, 2, 1, 3}, 0, INSTR_LDR);
    AddSingleLayout("ir[r]r", LayoutTransferShiftConst, 4, (void*){0, 2, 1, 3}, 0, INSTR_LDR);
    AddSingleLayout("ir[r]sr", LayoutTransferShiftConst, 5, (void*){0, 2, 1, 4, 3}, 0, INSTR_LDR);
    AddSingleLayout("ir[r]ri#", LayoutTransferShiftConst, 6, (void*){0, 2, 1, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]rir", LayoutTransferShiftReg, 6, (void*){0, 2, 1, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]sri#", LayoutTransferShiftConst, 7, (void*){0, 2, 1, 4, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);
    AddSingleLayout("ir[r]srir", LayoutTransferShiftReg, 7, (void*){0, 2, 1, 4, 3, 5, 6}, 0, INSTR_LDR, INSTR_LSL);

    /* Branch Instructions */
    AddSingleLayout("il", LayoutBranchLabel, NULL, NULL, INSTR_BRN);
    AddSingleLayout("ic", LayoutBranchConstant, NULL, NULL, INSTR_BRN);

    /* Shift Instructions */
    AddSingleLayout("ir#", LayoutShiftConst, NULL, NULL, INSTR_LSL);
    AddSingleLayout("irr", LayoutShiftReg, NULL, NULL, INSTR_LSL);
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