#include "commandgen.c"

/* GetCondCode tests */
void GetCondCodeTests() {
    InitFunctionGen();
    assert(GetCondCode("andeq") == 0b0000);
    assert(GetCondCode("orne") == 0b0001);
    assert(GetCondCode("movge") == 0b1010);
    assert(GetCondCode("blt") == 0b1011);
    assert(GetCondCode("eorgt") == 0b1100);
    assert(GetCondCode("mulle") == 0b1101);
    assert(GetCondCode("ldral") == 0b1110);
    assert(GetCondCode("cmp") == 0b1110);
    FinishFunctionGen();
}

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
    Vector tokens_vector = NewVector(tokens_num);
    for(int i = 0; i < tokens_num; i++) {
        VectorSet(tokens_vector, i, tokens[i]);
    }
    ProcessBranch(symbols, tokens_vector, output, offset, instruction_num);
    DeleteVector(tokens_vector);
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
}

/* ProcessDataProcessing tests */

/* ProcessMultiply tests */

/* ProcessDataTransfer tests */

int main() {
    GetCondCodeTests();
    GetExprValueTests();
    ProcessBranchTests();
}