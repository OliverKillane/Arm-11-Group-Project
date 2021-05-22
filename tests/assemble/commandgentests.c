#include <commandgen.h>
#include <process_shift.h>
#include <process_multiply.h>
#include <process_data_transfer.h>
#include <process_data_processing.h>
#include <process_branch.h>
#include <common_defs.h>
#include <stddata.h>

/* GetExpressionValue tests */
void GetExprValueTests() {
    Map symbols = NewEmptyMap(StringHash, StringEq);
    MapSet(symbols, "label", 2);
    MapSet(symbols, "wait", 5);
    InitFunctionGen();
    assert(GetExpressionValue(symbols, "label", false, true) == 8);
    assert(GetExpressionValue(symbols, "1234", true, true) == 1234);
    assert(GetExpressionValue(symbols, "=0xFFFF", false, false) == 0xFFFF);
    assert(GetExpressionValue(symbols, "=0b01010", false, false) == 0b01010);
    assert(GetExpressionValue(symbols, "#01237", false, true) == 0b000001010011111);
    assert(GetExpressionValue(symbols, "#0o531", false, true) == 0b101011001);
    assert(GetExpressionValue(symbols, "=0d537", false, false) == 537);
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
    SingleProcessBranch(symbols, 2, (char*[]){"bne", "0o0"}, output, 1, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"bge", "0b100"}, output, 2, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"blt", "0xC"}, output, 3, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"bgt", "0x1C"}, output, 4, 8);
    SingleProcessBranch(symbols, 2, (char*[]){"ble", "0d20"}, output, 5, 8);
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
    SingleProcessDataProcessing(symbols, 4, (char*[]){"eorne", "R8", "R6", "#0xFF00"}, output, 1, 10);
    SingleProcessDataProcessing(symbols, 4, (char*[]){"subge", "R4", "R4", "#0b10100"}, output, 2, 10);
    SingleProcessDataProcessing(symbols, 4, (char*[]){"rsblt", "R1", "R9", "#0x3FC0"}, output, 3, 10);
    SingleProcessDataProcessing(symbols, 6, (char*[]){"addgt", "R3", "R2", "R2", "asr", "R9"}, output, 4, 10);
    SingleProcessDataProcessing(symbols, 6, (char*[]){"orrle", "R5", "R1", "R3", "lsl", "R0"}, output, 5, 10);
    SingleProcessDataProcessing(symbols, 5, (char*[]){"moval", "R7", "R6", "lsr", "#0o30"}, output, 6, 10);
    SingleProcessDataProcessing(symbols, 5, (char*[]){"tst", "R9", "R9", "ror", "#0d11"}, output, 7, 10);
    SingleProcessDataProcessing(symbols, 5, (char*[]){"teq", "R11", "R0", "lsr", "#0xF"}, output, 8, 10);
    SingleProcessDataProcessing(symbols, 3, (char*[]){"cmp", "R10", "#261120"}, output, 9, 10);
    
    assert((int)VectorGet(output, 0) == 0x000CC009);
    assert((int)VectorGet(output, 1) == 0x12268CFF);
    assert((int)VectorGet(output, 2) == 0xA2444F05);
    assert((int)VectorGet(output, 3) == 0xB2691DFF);
    assert((int)VectorGet(output, 4) == 0xC0823952);
    assert((int)VectorGet(output, 5) == 0xD1815013);
    assert((int)VectorGet(output, 6) == 0xE1A07C26);
    assert((int)VectorGet(output, 7) == 0xE11905E9);
    assert((int)VectorGet(output, 8) == 0xE13B07A0);
    assert((int)VectorGet(output, 9) == 0xE35A0BFF);
    DeleteMap(symbols);
    DeleteVector(output);
}

/* ProcessMultiply tests */

/* ProcessDataTransfer tests */

/* ProcessShift tests */

int main() {
    GetExprValueTests();
    ProcessBranchTests();
    ProcessDataProcessingTests();
}