#include <commandgen.h>
#include <process_shift.h>
#include <process_multiply.h>
#include <process_data_transfer.h>
#include <process_data_processing.h>
#include <process_branch.h>
#include <common_defs.h>
#include <stddata.h>
#include <stdio.h>

/* GetExpressionValue tests */
void GetExprValueTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    MapSet(symbols, "label", 2);
    MapSet(symbols, "wait", 5);
    InitFunctionGen();
    assert(GetExpressionValue(symbols, "label", false, true) == 8);
    assert(GetExpressionValue(symbols, "1234", true, true) == 1234);
    assert(GetExpressionValue(symbols, "=0xFFFF", false, false) == 0xFFFF);
    assert(GetExpressionValue(symbols, "=01010", false, false) == 0b001000001000);
    assert(GetExpressionValue(symbols, "#01237", false, true) == 0b000001010011111);
    assert(GetExpressionValue(symbols, "#0xA21", false, true) == 0b101000100001);
    assert(GetExpressionValue(symbols, "=537", false, false) == 537);
    FinishFunctionGen();
    DeleteMap(symbols);
}

/* ProcessBranch tests */
void SingleProcessBranch(
    Map symbols, 
    int tokens_num, 
    char* tokens[], 
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
}
void ProcessBranchTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    MapSet(symbols, "label", 2);
    MapSet(symbols, "wait", 5);
    
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessBranch(symbols, 2, (char*[]){"beq", "label"}, output, 0, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"bne", "00"}, output, 1, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"bge", "04"}, output, 2, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"blt", "0xC"}, output, 3, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"bgt", "0x1C"}, output, 4, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"ble", "20"}, output, 5, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"bal", "010"}, output, 6, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"b", "034"}, output, 7, 8);

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
    char* tokens[], 
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
}

void ProcessDataProcessingTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessDataProcessing(symbols, 4, (char*[]){"andeq", "R12", "R12", "R9"}, output, 0, 10);
    SingleProcessDataProcessing(symbols, 4, (char*[]){"eorne", "R8", "R6", "#0xC0000001"}, output, 1, 10);
    SingleProcessDataProcessing(symbols, 4, (char*[]){"subge", "R4", "R4", "#0x100"}, output, 2, 10);
    SingleProcessDataProcessing(symbols, 4, (char*[]){"rsblt", "R1", "R9", "#0x3FC0"}, output, 3, 10);
    SingleProcessDataProcessing(symbols, 6, (char*[]){"addgt", "R3", "R2", "R2", "asr", "R9"}, output, 4, 10);
    SingleProcessDataProcessing(symbols, 6, (char*[]){"orrle", "R5", "R1", "R3", "lsl", "R0"}, output, 5, 10);
    SingleProcessDataProcessing(symbols, 5, (char*[]){"moval", "R7", "R6", "lsr", "#0x18"}, output, 6, 10);
    SingleProcessDataProcessing(symbols, 5, (char*[]){"tst", "R9", "R9", "ror", "#11"}, output, 7, 10);
    SingleProcessDataProcessing(symbols, 5, (char*[]){"teq", "R11", "R0", "lsr", "#0xF"}, output, 8, 10);
    SingleProcessDataProcessing(symbols, 3, (char*[]){"cmp", "R10", "#261120"}, output, 9, 10);
    
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
    char* tokens[], 
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
}
void ProcessMultiplyTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessMultiply(symbols, 4, (char*[]){"muleq", "R3", "R2", "R5"}, output, 0, 6);
    SingleProcessMultiply(symbols, 4, (char*[]){"mulle", "R8", "R9", "R10"}, output, 1, 6);
    SingleProcessMultiply(symbols, 4, (char*[]){"mul", "R2", "R0", "R2"}, output, 2, 6);
    SingleProcessMultiply(symbols, 5, (char*[]){"mlalt", "R5", "R10", "R5", "R11"}, output, 3, 6);
    SingleProcessMultiply(symbols, 5, (char*[]){"mlagt", "R7", "R1", "R7", "R7"}, output, 4, 6);
    SingleProcessMultiply(symbols, 5, (char*[]){"mlane", "R4", "R6", "R12", "R0"}, output, 5, 6);

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
    char* tokens[], 
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
}
void ProcessDataTransferTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessDataTransfer(symbols, 3, (char*[]){"ldr", "r2", "=0x20200020"}, output, 0, 8);
    SingleProcessDataTransfer(symbols, 3, (char*[]){"ldr", "r0", "=017"}, output, 1, 8);
    SingleProcessDataTransfer(symbols, 6, (char*[]){"ldr", "r3", "[", "r1", "#0x4", "]"}, output, 2, 8);
    SingleProcessDataTransfer(symbols, 8, (char*[]){"ldr", "r12", "[", "r15", "-r2", "ror", "#22", "]"}, output, 3, 8);
    SingleProcessDataTransfer(symbols, 6, (char*[]){"str", "r0", "[", "r1", "#28", "]"}, output, 4, 8);
    SingleProcessDataTransfer(symbols, 6, (char*[]){"str", "r1", "[", "r2", "]", "r4"}, output, 5, 8);
    SingleProcessDataTransfer(symbols, 6, (char*[]){"str", "r10", "[", "r10", "]", "#-212"}, output, 6, 8);
    SingleProcessDataTransfer(symbols, 8, (char*[]){"str", "r9", "[", "r7", "]", "-r2", "asr", "R15"}, output, 7, 8);

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
    char* tokens[], 
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
}
void ProcessShiftTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    InitFunctionGen();
    Vector output = NewEmptyVector();

    SingleProcessShift(symbols, 3, (char*[]){"asreq", "R1", "#030"}, output, 0, 6);
    SingleProcessShift(symbols, 3, (char*[]){"lslle", "R10", "#11"}, output, 1, 6);
    SingleProcessShift(symbols, 3, (char*[]){"lsr", "R12", "#0xF"}, output, 2, 6);
    SingleProcessShift(symbols, 3, (char*[]){"rorlt", "R8", "#030"}, output, 3, 6);
    SingleProcessShift(symbols, 3, (char*[]){"asrgt", "R4", "R5"}, output, 4, 6);
    SingleProcessShift(symbols, 3, (char*[]){"lslne", "R0", "R10"}, output, 5, 6);

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
    GetExprValueTests();
    ProcessBranchTests();
    ProcessDataProcessingTests();
    ProcessMultiplyTests();
    ProcessDataTransferTests();
    ProcessShiftTests();

    printf("Command Gen Tests passed.\n");
}