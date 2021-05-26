#include <commandgen.h>
#include <process_shift.h>
#include <process_multiply.h>
#include <process_data_transfer.h>
#include <process_data_processing.h>
#include <process_branch.h>
#include <common_defs.h>
#include <stddata.h>
#include <stdio.h>
#include <tokenizer.h>
#include <token_utils.h>
#include <stdbool.h>

/* ProcessBranch tests */
void SingleProcessBranch(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector output, 
    int offset, 
    int instruction_num
) {
    List tokens_list = NewEmptyList();
    for(int i = 0; i < tokens_num; i++) {
        ListPushBack(tokens_list, tokens[i]);
    }
    ProcessBranch(symbols, tokens_list, output, offset, instruction_num);
    DeleteList(tokens_list);
    for(int i = 0; i < tokens_num; i++) {
        DeleteToken(tokens[i]);
    }
}
void ProcessBranchTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    MapSet(symbols, "label", 2);
    MapSet(symbols, "wait", 5);
    
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_BRN),
        NewLabelToken("label")
    }, output, 0, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_NE, INSTR_BRN), 
        NewConstantToken(CONST_PURE, 0)
    }, output, 1, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_GE, INSTR_BRN),
        NewConstantToken(CONST_PURE, 4)
    }, output, 2, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_LT, INSTR_BRN),
        NewConstantToken(CONST_PURE, 0xC)
    }, output, 3, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_GT, INSTR_BRN),
        NewConstantToken(CONST_PURE, 0x1C)
    }, output, 4, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_LE, INSTR_BRN),
        NewConstantToken(CONST_PURE, 20)
    }, output, 5, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_AL, INSTR_BRN),
        NewConstantToken(CONST_PURE, 8)
    }, output, 6, 8);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_AL, INSTR_BRN),
        NewConstantToken(CONST_PURE, 28)
    }, output, 7, 8);

    assert((int)VectorGet(output, 0) == 0x0A000000);
    assert((int)VectorGet(output, 1) == 0x1AFFFFFD);
    assert((int)VectorGet(output, 2) == 0xAAFFFFFD);
    assert((int)VectorGet(output, 3) == 0xBAFFFFFE);
    assert((int)VectorGet(output, 4) == 0xCA000001);
    assert((int)VectorGet(output, 5) == 0xDAFFFFFE);
    assert((int)VectorGet(output, 6) == 0xEAFFFFFA);
    assert((int)VectorGet(output, 7) == 0xEAFFFFFE);

    FinishFunctionGen();
    DeleteMap(symbols);
    DeleteVector(output);
}

/* ProcessDataProcessing tests */
void SingleProcessDataProcessing(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector output, 
    int offset, 
    int instruction_num
) {
    List tokens_list = NewEmptyList();
    for(int i = 0; i < tokens_num; i++) {
        ListPushBack(tokens_list, tokens[i]);
    }
    ProcessDataProcessing(symbols, tokens_list, output, offset, instruction_num);
    DeleteList(tokens_list);
    for(int i = 0; i < tokens_num; i++) {
        DeleteToken(tokens[i]);
    }
}

void ProcessDataProcessingTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_AND),
        NewRegisterToken(12),
        NewRegisterToken(12),
        NewRegisterToken(9)
    }, output, 0, 10);
    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_NE, INSTR_EOR),
        NewRegisterToken(8),
        NewRegisterToken(6),
        NewConstantToken(CONST_HASH, 0xC0000001)
    }, output, 1, 10);
    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_GE, INSTR_SUB),
        NewRegisterToken(4),
        NewRegisterToken(4),
        NewConstantToken(CONST_HASH, 0x100)
    }, output, 2, 10);
    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_LT, INSTR_RSB),
        NewRegisterToken(1),
        NewRegisterToken(9),
        NewConstantToken(CONST_HASH, 0x3FC0)
    }, output, 3, 10);
    SingleProcessDataProcessing(symbols, 6, (Token[]){
        NewInstructionToken(COND_GT, INSTR_ADD),
        NewRegisterToken(3),
        NewRegisterToken(2),
        NewRegisterToken(2),
        NewInstructionToken(COND_AL, INSTR_ASR),
        NewRegisterToken(9)
    }, output, 4, 10);
    SingleProcessDataProcessing(symbols, 6, (Token[]){
        NewInstructionToken(COND_LE, INSTR_ORR),
        NewRegisterToken(5),
        NewRegisterToken(1),
        NewRegisterToken(3),
        NewInstructionToken(COND_AL, INSTR_LSL),
        NewRegisterToken(0)
    }, output, 5, 10);
    SingleProcessDataProcessing(symbols, 5, (Token[]){
        NewInstructionToken(COND_AL, INSTR_MOV),
        NewRegisterToken(7),
        NewRegisterToken(6),
        NewInstructionToken(COND_AL, INSTR_LSR),
        NewConstantToken(CONST_HASH, 0x18)
    }, output, 6, 10);
    SingleProcessDataProcessing(symbols, 5, (Token[]){
        NewInstructionToken(COND_AL, INSTR_TST),
        NewRegisterToken(9),
        NewRegisterToken(9),
        NewInstructionToken(COND_AL, INSTR_ROR),
        NewConstantToken(CONST_HASH, 11)
    }, output, 7, 10);
    SingleProcessDataProcessing(symbols, 5, (Token[]){
        NewInstructionToken(COND_AL, INSTR_TEQ),
        NewRegisterToken(11),
        NewRegisterToken(0),
        NewInstructionToken(COND_AL, INSTR_LSR),
        NewConstantToken(CONST_HASH, 0xF)
    }, output, 8, 10);
    SingleProcessDataProcessing(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_CMP),
        NewRegisterToken(10),
        NewConstantToken(CONST_HASH, 261120)
    }, output, 9, 10);
    
    assert((int)VectorGet(output, 0) == 0x000CC009);
    assert((int)VectorGet(output, 1) == 0x12268107);
    assert((int)VectorGet(output, 2) == 0xA2444C01);
    assert((int)VectorGet(output, 3) == 0xB2691DFF);
    assert((int)VectorGet(output, 4) == 0xC0823952);
    assert((int)VectorGet(output, 5) == 0xD1815013);
    assert((int)VectorGet(output, 6) == 0xE1A07C26);
    assert((int)VectorGet(output, 7) == 0xE11905E9);
    assert((int)VectorGet(output, 8) == 0xE13B07A0);
    assert((int)VectorGet(output, 9) == 0xE35A0BFF);

    FinishFunctionGen();
    DeleteMap(symbols);
    DeleteVector(output);
}

/* ProcessMultiply tests */
void SingleProcessMultiply(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector output, 
    int offset, 
    int instruction_num
) {
    List tokens_list = NewEmptyList();
    for(int i = 0; i < tokens_num; i++) {
        ListPushBack(tokens_list, tokens[i]);
    }
    ProcessMultiply(symbols, tokens_list, output, offset, instruction_num);
    DeleteList(tokens_list);
    for(int i = 0; i < tokens_num; i++) {
        DeleteToken(tokens[i]);
    }
}
void ProcessMultiplyTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessMultiply(symbols, 4, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_MUL),
        NewRegisterToken(3),
        NewRegisterToken(2),
        NewRegisterToken(5)
    }, output, 0, 6);
    SingleProcessMultiply(symbols, 4, (Token[]){
        NewInstructionToken(COND_LE, INSTR_MUL),
        NewRegisterToken(8),
        NewRegisterToken(9),
        NewRegisterToken(10)
    }, output, 1, 6);
    SingleProcessMultiply(symbols, 4, (Token[]){
        NewInstructionToken(COND_AL, INSTR_MUL),
        NewRegisterToken(2),
        NewRegisterToken(0),
        NewRegisterToken(2)
    }, output, 2, 6);
    SingleProcessMultiply(symbols, 5, (Token[]){
        NewInstructionToken(COND_LT, INSTR_MLA),
        NewRegisterToken(5),
        NewRegisterToken(10),
        NewRegisterToken(5),
        NewRegisterToken(11)
    }, output, 3, 6);
    SingleProcessMultiply(symbols, 5, (Token[]){
        NewInstructionToken(COND_GT, INSTR_MLA),
        NewRegisterToken(7),
        NewRegisterToken(1),
        NewRegisterToken(7),
        NewRegisterToken(7)
    }, output, 4, 6);
    SingleProcessMultiply(symbols, 5, (Token[]){
        NewInstructionToken(COND_NE, INSTR_MLA),
        NewRegisterToken(4),
        NewRegisterToken(6),
        NewRegisterToken(12),
        NewRegisterToken(0)
    }, output, 5, 6);

    assert((int)VectorGet(output, 0) == 0x00030592);
    assert((int)VectorGet(output, 1) == 0xD0080A99);
    assert((int)VectorGet(output, 2) == 0xE0020290);
    assert((int)VectorGet(output, 3) == 0xB025B59A);
    assert((int)VectorGet(output, 4) == 0xC0277791);
    assert((int)VectorGet(output, 5) == 0x10240C96);

    FinishFunctionGen();
    DeleteVector(output);
    DeleteMap(symbols);
}

/* ProcessDataTransfer tests */
void SingleProcessDataTransfer(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector output, 
    int offset, 
    int instruction_num
) {
    List tokens_list = NewEmptyList();
    for(int i = 0; i < tokens_num; i++) {
        ListPushBack(tokens_list, tokens[i]);
    }
    ProcessDataTransfer(symbols, tokens_list, output, offset, instruction_num);
    DeleteList(tokens_list);
    for(int i = 0; i < tokens_num; i++) {
        DeleteToken(tokens[i]);
    }
}
void ProcessDataTransferTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessDataTransfer(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(2),
        NewConstantToken(CONST_EQUALS, 0x20200020)
    }, output, 0, 8);
    SingleProcessDataTransfer(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(0),
        NewConstantToken(CONST_EQUALS, 15)
    }, output, 1, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(3),
        NewBraceToken(true),
        NewRegisterToken(1),
        NewConstantToken(CONST_HASH, 4),
        NewBraceToken(false)
    }, output, 2, 8);
    SingleProcessDataTransfer(symbols, 9, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(12),
        NewBraceToken(true),
        NewRegisterToken(15),
        NewSignToken(false),
        NewRegisterToken(2),
        NewInstructionToken(COND_AL, INSTR_ROR),
        NewConstantToken(CONST_HASH, 22),
        NewBraceToken(false)
    }, output, 3, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(0),
        NewBraceToken(true),
        NewRegisterToken(1),
        NewConstantToken(CONST_HASH, 28),
        NewBraceToken(false)
    }, output, 4, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(1),
        NewBraceToken(true),
        NewRegisterToken(2),
        NewBraceToken(false),
        NewRegisterToken(4)
    }, output, 5, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(10),
        NewBraceToken(true),
        NewRegisterToken(10),
        NewBraceToken(false),
        NewConstantToken(CONST_HASH, -212)
    }, output, 6, 8);
    SingleProcessDataTransfer(symbols, 9, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(9),
        NewBraceToken(true),
        NewRegisterToken(7),
        NewBraceToken(false),
        NewSignToken(false),
        NewRegisterToken(2),
        NewInstructionToken(COND_AL, INSTR_ASR),
        NewRegisterToken(15)
    }, output, 7, 8);

    assert((int)VectorGet(output, 0) == 0xE59F2018);
    assert((int)VectorGet(output, 1) == 0xE3A0000F);
    assert((int)VectorGet(output, 2) == 0xE5913004);
    assert((int)VectorGet(output, 3) == 0xE71FCB62);
    assert((int)VectorGet(output, 4) == 0xE581001C);
    assert((int)VectorGet(output, 5) == 0xE6821004);
    assert((int)VectorGet(output, 6) == 0xE40AA0D4);
    assert((int)VectorGet(output, 7) == 0xE6079F52);
    assert((int)VectorGet(output, 8) == 0x20200020);

    FinishFunctionGen();
    DeleteVector(output);
    DeleteMap(symbols);
}

/* ProcessShift tests */
void SingleProcessShift(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector output, 
    int offset, 
    int instruction_num
) {
    List tokens_list = NewEmptyList();
    for(int i = 0; i < tokens_num; i++) {
        ListPushBack(tokens_list, tokens[i]);
    }
    ProcessShift(symbols, tokens_list, output, offset, instruction_num);
    DeleteList(tokens_list);
    for(int i = 0; i < tokens_num; i++) {
        DeleteToken(tokens[i]);
    }
}
void ProcessShiftTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_ASR),
        NewRegisterToken(1),
        NewConstantToken(CONST_HASH, 0x18)
    }, output, 0, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_LE, INSTR_LSL),
        NewRegisterToken(10),
        NewConstantToken(CONST_HASH, 11)
    }, output, 1, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LSR),
        NewRegisterToken(12),
        NewConstantToken(CONST_HASH, 0xF)
    }, output, 2, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_LT, INSTR_ROR),
        NewRegisterToken(8),
        NewConstantToken(CONST_HASH, 0x18)
    }, output, 3, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_GT, INSTR_ASR),
        NewRegisterToken(4),
        NewRegisterToken(5)
    }, output, 4, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_NE, INSTR_LSL),
        NewRegisterToken(0),
        NewRegisterToken(10)
    }, output, 5, 6);

    assert((int)VectorGet(output, 0) == 0x01A01C41);
    assert((int)VectorGet(output, 1) == 0xD1A0A58A);
    assert((int)VectorGet(output, 2) == 0xE1A0C7AC);
    assert((int)VectorGet(output, 3) == 0xB1A08C68);
    assert((int)VectorGet(output, 4) == 0xC1A04554);
    assert((int)VectorGet(output, 5) == 0x11A00A10);

    FinishFunctionGen();
    DeleteVector(output);
    DeleteMap(symbols);
}

void runCommandGenTests() {
    ProcessBranchTests();
    ProcessDataProcessingTests();
    ProcessMultiplyTests();
    ProcessDataTransferTests();
    ProcessShiftTests();
    printf("Command Gen Tests passed.\n");
}