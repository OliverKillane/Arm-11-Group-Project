
#include "testutils.c"
#include "..\src\emulate.h"
#include <stdbool.h>
#include <stdlib.h>

// test condition checker
void check(bool condition, char *testname) {
    printf("\nT %s:   %c", testname, condition?'P':'F');
}


int main(){


    starttests("Emulator Tests");

    testsection("GETBITS tests");

    /*
    33222222222211111111110000000000
    10987654321098765432109876543210
    11101111001101111111111101000001
    */

    uint32_t test_data1 = 0b11101111001101111111111101000001;

    int32test(GETBITS(test_data1, 5, 0), 0, "Can get lengths of 0 bits");
    int32test(GETBITS(test_data1, 5, 0), 0, "Can get lengths of 1 bit");
    int32test(GETBITS(test_data1, 3, 3), 0, "");
    int32test(GETBITS(test_data1, 7, 5), 0b11110, "");
    int32test(GETBITS(test_data1, 7, 2), 0b10, "");
    int32test(GETBITS(test_data1, 27, 2), 0b01, "");
    int32test(GETBITS(test_data1, 19, 6), 0b100110, "");
    int32test(GETBITS(test_data1, 0, 7), 0b1000001, "");

    testsection("getProgram Tests");

    testsection("runProgram Tests");

    testsection("checkCond Tests");

    // set CPU.CPSR
    // run checkcond with mnemonic
    // get result checked
    //CPSR = NZCV

    0000 EQ Z = 1
    CPU.CPSR = 0b1011;
    booltest(checkCond(EQ), false, "EQ test");

    CPU.CPSR = 0b1111;
    booltest(checkCond(EQ), true, "EQ test");

    CPU.CPSR = 0b0000;
    booltest(checkCond(EQ), false, "EQ test");

    // 0001 NE Z = 0;
    CPU.CPSR = 0b1011;
    booltest(checkCond(NE), true, "NE test");

    CPU.CPSR = 0b1111;
    booltest(checkCond(NE), false, "NE test");

    CPU.CPSR = 0b0000;
    booltest(checkCond(NE), true, "NE test");

    // 1010 GE N = V
    CPU.CPSR = 0b1011;
    booltest(checkCond(GE), true, "GE test");

    CPU.CPSR = 0b1111;
    booltest(checkCond(GE), true, "GE test");

    CPU.CPSR = 0b0000;
    booltest(checkCond(GE), true, "GE test");

    CPU.CPSR = 0b0011;
    booltest(checkCond(GE), false, "GE test");
    
    CPU.CPSR = 0b1110;
    booltest(checkCond(GE), false, "GE test");

    CPU.CPSR = 0b0001;
    booltest(checkCond(GE), false, "GE test");

    // 1011 LT N != V
    CPU.CPSR = 0b1011;
    testbool(checkCond(LT), false, "LT test");
    
    CPU.CPSR = 0b1111;
    testbool(checkCond(LT), false, "LT test");

    CPU.CPSR = 0b0000;
    testbool(checkCond(LT), false, "LT test");
    
    CPU.CPSR = 0b0011;
    testbool(checkCond(LT), true, "LT test");
    
    CPU.CPSR = 0b1110;
    testbool(checkCond(LT), true, "LT test");

    CPU.CPSR = 0b0001;
    testbool(checkCond(LT), true, "LT test");

    // 1100 GTZ = 0 && (N = V)
    //NZCV
    CPU.CPSR = 0b0000;
    testbool(checkCond(GT), true, "GT test");

    CPU.CPSR = 0b0100;
    testbool(checkCond(GT), false, "GT test");

    CPU.CPSR = 0b0001;
    testbool(checkCond(GT), false, "GT test");

    CPU.CPSR = 0b0110;
    testbool(checkCond(GT), false, "GT test");

    CPU.CPSR = 0b1001;
    testbool(checkCond(GT), true, "GT test");
    
    // 1101 LE Z || (N != V) NZCV
    CPU.CPSR = 0b1011;
    testbool(checkCond(LE), false, "LE test");

    CPU.CPSR = 0b1111;
    testbool(checkCond(LE), true, "LE test");

    CPU.CPSR = 0b0000;
    testbool(checkCond(LE), false, "LE test");

    CPU.CPSR = 0b0011;
    testbool(checkCond(LE), true, "LE test");

    CPU.CPSR = 0b1110;
    testbool(checkCond(LE), true, "LE test");
    
    CPU.CPSR = 0b0001;
    testbool(checkCond(LE), false, "LE test");

    // 1110 AL (ignored)
    CPU.CPSR = 0b1011;
    testbool(checkCond(AL), true, "AL test");
    
    CPU.CPSR = 0b1111;
    testbool(checkCond(AL), true, "AL test");

    CPU.CPSR = 0b0000;
    testbool(checkCond(AL), true, "AL test");

    CPU.CPSR = 0b0011;
    testbool(checkCond(AL), true, "AL test");

    CPU.CPSR = 0b1110;
    testbool(checkCond(AL), true, "AL test");

    CPU.CPSR = 0b0001;
    testbool(checkCond(AL), true, "AL test");

    testsection("processInstr Tests");

    testsection("branchInstr Tests");

    testsection("singleDataTransInstr Tests");

    testsection("MultiplyInstr Tests");

    testsection("processDataInstr Tests");

    testsection("getReg Tests");

    testsection("storemem Tests");

    testsection("getmem Tests");
}