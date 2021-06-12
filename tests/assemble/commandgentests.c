#include <commandgen.h>
#include <common_defs.h>
#include <instruction_layouts.h>
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
    Vector text,
    Vector data, 
    int offset, 
    int instruction_num
) {
    Vector tokens_vector = NewEmptyVector();
    for(int i = 0; i < tokens_num; i++) {
        VectorPushBack(tokens_vector, tokens[i]);
    }
    FunctionGen(symbols, tokens_vector, text, data, offset, instruction_num);
    while(!VectorEmpty(tokens_vector)) {
        DeleteToken(VectorPopBack(tokens_vector));
    }
    DeleteVector(tokens_vector);
}
void ProcessBranchTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    MapSet(symbols, "label", 2);
    MapSet(symbols, "wait", 1);
    
    InitFunctionGen();
    Vector text = NewEmptyVector();
    Vector data = NewEmptyVector();

    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_BRN),
        NewLabelToken("label", LABEL_FULL)
    }, text, data, 0, 4);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_NE, INSTR_BRN), 
        NewConstantToken(CONST_PURE, 0)
    }, text, data, 1, 4);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_GE, INSTR_BRL),
        NewLabelToken("wait", LABEL_FULL)
    }, text, data, 2, 4);
    SingleProcessBranch(symbols, 2, (Token[]){
        NewInstructionToken(COND_LT, INSTR_BRN),
        NewConstantToken(CONST_PURE, 0xC)
    }, text, data, 3, 4);

    assert((int)VectorGet(text, 0) == 0x0A000000);
    assert((int)VectorGet(text, 1) == 0x1AFFFFFD);
    assert((int)VectorGet(text, 2) == 0xABFFFFFD);
    assert((int)VectorGet(text, 3) == 0xBAFFFFFE);

    FinishFunctionGen();
    DeleteMap(symbols);
    DeleteVector(text);
    DeleteVector(data);
}

/* ProcessDataProcessing tests */
void SingleProcessDataProcessing(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector text,
    Vector data, 
    int offset, 
    int instruction_num
) {
    Vector tokens_vector = NewEmptyVector();
    for(int i = 0; i < tokens_num; i++) {
        VectorPushBack(tokens_vector, tokens[i]);
    }
    FunctionGen(symbols, tokens_vector, text, data, offset, instruction_num);
    while(!VectorEmpty(tokens_vector)) {
        DeleteToken(VectorPopBack(tokens_vector));
    }
    DeleteVector(tokens_vector);
}

void ProcessDataProcessingTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    
    InitFunctionGen();
    Vector text = NewEmptyVector();
    Vector data = NewEmptyVector();

    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_AND),
        NewRegisterToken(12),
        NewRegisterToken(12),
        NewRegisterToken(9)
    }, text, data, 0, 10);
    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_NE, INSTR_EOR),
        NewRegisterToken(8),
        NewRegisterToken(6),
        NewConstantToken(CONST_HASH, 0xC0000001)
    }, text, data, 1, 10);
    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_GE, INSTR_SUB),
        NewRegisterToken(4),
        NewRegisterToken(4),
        NewConstantToken(CONST_HASH, 0x100)
    }, text, data, 2, 10);
    SingleProcessDataProcessing(symbols, 4, (Token[]){
        NewInstructionToken(COND_LT, INSTR_RSB),
        NewRegisterToken(1),
        NewRegisterToken(9),
        NewConstantToken(CONST_HASH, 0x3FC0)
    }, text, data, 3, 10);
    SingleProcessDataProcessing(symbols, 6, (Token[]){
        NewInstructionToken(COND_GT, INSTR_ADD),
        NewRegisterToken(3),
        NewRegisterToken(2),
        NewRegisterToken(2),
        NewInstructionToken(COND_AL, INSTR_ASR),
        NewRegisterToken(9)
    }, text, data, 4, 10);
    SingleProcessDataProcessing(symbols, 6, (Token[]){
        NewInstructionToken(COND_LE, INSTR_ORR),
        NewRegisterToken(5),
        NewRegisterToken(1),
        NewRegisterToken(3),
        NewInstructionToken(COND_AL, INSTR_LSL),
        NewRegisterToken(0)
    }, text, data, 5, 10);
    SingleProcessDataProcessing(symbols, 5, (Token[]){
        NewInstructionToken(COND_AL, INSTR_MOV),
        NewRegisterToken(7),
        NewRegisterToken(6),
        NewInstructionToken(COND_AL, INSTR_LSR),
        NewConstantToken(CONST_HASH, 0x18)
    }, text, data, 6, 10);
    SingleProcessDataProcessing(symbols, 5, (Token[]){
        NewInstructionToken(COND_AL, INSTR_TST),
        NewRegisterToken(9),
        NewRegisterToken(9),
        NewInstructionToken(COND_AL, INSTR_ROR),
        NewConstantToken(CONST_HASH, 11)
    }, text, data, 7, 10);
    SingleProcessDataProcessing(symbols, 5, (Token[]){
        NewInstructionToken(COND_AL, INSTR_TEQ),
        NewRegisterToken(11),
        NewRegisterToken(0),
        NewInstructionToken(COND_AL, INSTR_LSR),
        NewConstantToken(CONST_HASH, 0xF)
    }, text, data, 8, 10);
    SingleProcessDataProcessing(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_CMP),
        NewRegisterToken(10),
        NewConstantToken(CONST_HASH, 261120)
    }, text, data, 9, 10);
    
    assert((int)VectorGet(text, 0) == 0x000CC009);
    assert((int)VectorGet(text, 1) == 0x12268107);
    assert((int)VectorGet(text, 2) == 0xA2444C01);
    assert((int)VectorGet(text, 3) == 0xB2691DFF);
    assert((int)VectorGet(text, 4) == 0xC0823952);
    assert((int)VectorGet(text, 5) == 0xD1815013);
    assert((int)VectorGet(text, 6) == 0xE1A07C26);
    assert((int)VectorGet(text, 7) == 0xE11905E9);
    assert((int)VectorGet(text, 8) == 0xE13B07A0);
    assert((int)VectorGet(text, 9) == 0xE35A0BFF);

    FinishFunctionGen();
    DeleteMap(symbols);
    DeleteVector(text);
    DeleteVector(data);
}

/* ProcessMultiply tests */
void SingleProcessMultiply(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector text,
    Vector data, 
    int offset, 
    int instruction_num
) {
    Vector tokens_vector = NewEmptyVector();
    for(int i = 0; i < tokens_num; i++) {
        VectorPushBack(tokens_vector, tokens[i]);
    }
    FunctionGen(symbols, tokens_vector, text, data, offset, instruction_num);
    while(!VectorEmpty(tokens_vector)) {
        DeleteToken(VectorPopBack(tokens_vector));
    }
    DeleteVector(tokens_vector);
}
void ProcessMultiplyTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector text = NewEmptyVector();
    Vector data = NewEmptyVector();

    SingleProcessMultiply(symbols, 4, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_MUL),
        NewRegisterToken(3),
        NewRegisterToken(2),
        NewRegisterToken(5)
    }, text, data, 0, 6);
    SingleProcessMultiply(symbols, 4, (Token[]){
        NewInstructionToken(COND_LE, INSTR_MUL),
        NewRegisterToken(8),
        NewRegisterToken(9),
        NewRegisterToken(10)
    }, text, data, 1, 6);
    SingleProcessMultiply(symbols, 4, (Token[]){
        NewInstructionToken(COND_AL, INSTR_MUL),
        NewRegisterToken(2),
        NewRegisterToken(0),
        NewRegisterToken(2)
    }, text, data, 2, 6);
    SingleProcessMultiply(symbols, 5, (Token[]){
        NewInstructionToken(COND_LT, INSTR_MLA),
        NewRegisterToken(5),
        NewRegisterToken(10),
        NewRegisterToken(5),
        NewRegisterToken(11)
    }, text, data, 3, 6);
    SingleProcessMultiply(symbols, 5, (Token[]){
        NewInstructionToken(COND_GT, INSTR_MLA),
        NewRegisterToken(7),
        NewRegisterToken(1),
        NewRegisterToken(7),
        NewRegisterToken(7)
    }, text, data, 4, 6);
    SingleProcessMultiply(symbols, 5, (Token[]){
        NewInstructionToken(COND_NE, INSTR_MLA),
        NewRegisterToken(4),
        NewRegisterToken(6),
        NewRegisterToken(12),
        NewRegisterToken(0)
    }, text, data, 5, 6);

    assert((int)VectorGet(text, 0) == 0x00030592);
    assert((int)VectorGet(text, 1) == 0xD0080A99);
    assert((int)VectorGet(text, 2) == 0xE0020290);
    assert((int)VectorGet(text, 3) == 0xB025B59A);
    assert((int)VectorGet(text, 4) == 0xC0277791);
    assert((int)VectorGet(text, 5) == 0x10240C96);

    FinishFunctionGen();
    DeleteVector(text);
    DeleteVector(data);
    DeleteMap(symbols);
}

/* ProcessDataTransfer tests */
void SingleProcessDataTransfer(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector text,
    Vector data, 
    int offset, 
    int instruction_num
) {
    Vector tokens_vector = NewEmptyVector();
    for(int i = 0; i < tokens_num; i++) {
        VectorPushBack(tokens_vector, tokens[i]);
    }
    FunctionGen(symbols, tokens_vector, text, data, offset, instruction_num);
    while(!VectorEmpty(tokens_vector)) {
        DeleteToken(VectorPopBack(tokens_vector));
    }
    DeleteVector(tokens_vector);
}
void ProcessDataTransferTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector text = NewEmptyVector();
    Vector data = NewEmptyVector();

    SingleProcessDataTransfer(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(2),
        NewConstantToken(CONST_EQUALS, 0x20200020)
    }, text, data, 0, 8);
    SingleProcessDataTransfer(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(0),
        NewConstantToken(CONST_EQUALS, 15)
    }, text, data, 1, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LDR),
        NewRegisterToken(3),
        NewBraceToken(true),
        NewRegisterToken(1),
        NewConstantToken(CONST_HASH, 4),
        NewBraceToken(false),
        NewExclamationToken()
    }, text, data, 2, 8);
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
    }, text, data, 3, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(0),
        NewBraceToken(true),
        NewRegisterToken(1),
        NewConstantToken(CONST_HASH, 28),
        NewBraceToken(false)
    }, text, data, 4, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(1),
        NewBraceToken(true),
        NewRegisterToken(2),
        NewBraceToken(false),
        NewRegisterToken(4)
    }, text, data, 5, 8);
    SingleProcessDataTransfer(symbols, 6, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(10),
        NewBraceToken(true),
        NewRegisterToken(10),
        NewBraceToken(false),
        NewConstantToken(CONST_HASH, -212)
    }, text, data, 6, 8);
    SingleProcessDataTransfer(symbols, 9, (Token[]){
        NewInstructionToken(COND_AL, INSTR_STR),
        NewRegisterToken(9),
        NewBraceToken(true),
        NewRegisterToken(7),
        NewBraceToken(false),
        NewSignToken(false),
        NewRegisterToken(2),
        NewInstructionToken(COND_AL, INSTR_ASR),
        NewRegisterToken(12)
    }, text, data, 7, 8);

    assert((int)VectorGet(text, 0) == 0xE59F2018);
    assert((int)VectorGet(text, 1) == 0xE3A0000F);
    assert((int)VectorGet(text, 2) == 0xE5913004);
    assert((int)VectorGet(text, 3) == 0xE71FCB62);
    assert((int)VectorGet(text, 4) == 0xE581001C);
    assert((int)VectorGet(text, 5) == 0xE6821004);
    assert((int)VectorGet(text, 6) == 0xE40AA0D4);
    assert((int)VectorGet(text, 7) == 0xE6079C52);
    assert((int)VectorGet(data, 0) == 0x20200020);

    FinishFunctionGen();
    DeleteVector(text);
    DeleteVector(data);
    DeleteMap(symbols);
}

/* ProcessShift tests */
void SingleProcessShift(
    Map symbols, 
    int tokens_num, 
    Token tokens[], 
    Vector text,
    Vector data, 
    int offset, 
    int instruction_num
) {
    Vector tokens_vector = NewEmptyVector();
    for(int i = 0; i < tokens_num; i++) {
        VectorPushBack(tokens_vector, tokens[i]);
    }
    FunctionGen(symbols, tokens_vector, text, data, offset, instruction_num);
    while(!VectorEmpty(tokens_vector)) {
        DeleteToken(VectorPopBack(tokens_vector));
    }
    DeleteVector(tokens_vector);
}
void ProcessShiftTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector text = NewEmptyVector();
    Vector data = NewEmptyVector();

    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_EQ, INSTR_ASR),
        NewRegisterToken(1),
        NewConstantToken(CONST_HASH, 0x18)
    }, text, data, 0, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_LE, INSTR_LSL),
        NewRegisterToken(10),
        NewConstantToken(CONST_HASH, 11)
    }, text, data, 1, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_AL, INSTR_LSR),
        NewRegisterToken(12),
        NewConstantToken(CONST_HASH, 0xF)
    }, text, data, 2, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_LT, INSTR_ROR),
        NewRegisterToken(8),
        NewConstantToken(CONST_HASH, 0x18)
    }, text, data, 3, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_GT, INSTR_ASR),
        NewRegisterToken(4),
        NewRegisterToken(5)
    }, text, data, 4, 6);
    SingleProcessShift(symbols, 3, (Token[]){
        NewInstructionToken(COND_NE, INSTR_LSL),
        NewRegisterToken(0),
        NewRegisterToken(10)
    }, text, data, 5, 6);

    assert((int)VectorGet(text, 0) == 0x01A01C41);
    assert((int)VectorGet(text, 1) == 0xD1A0A58A);
    assert((int)VectorGet(text, 2) == 0xE1A0C7AC);
    assert((int)VectorGet(text, 3) == 0xB1A08C68);
    assert((int)VectorGet(text, 4) == 0xC1A04554);
    assert((int)VectorGet(text, 5) == 0x11A00A10);

    FinishFunctionGen();
    DeleteVector(text);
    DeleteVector(data);
    DeleteMap(symbols);
}

void runCommandGenTests() {
    fprintf(stderr, "Branch\n");
    ProcessBranchTests();
    fprintf(stderr, "DataProc\n");
    ProcessDataProcessingTests();
    fprintf(stderr, "Mult\n");
    ProcessMultiplyTests();
    fprintf(stderr, "DataTransfer\n");
    ProcessDataTransferTests();
    fprintf(stderr, "Shift\n");
    ProcessShiftTests();
    printf("Command Gen Tests passed.\n");
}