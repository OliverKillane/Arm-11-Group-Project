#include "testutils.c"
#include "emulate.h"
#include "emulate.c"
#include <stdbool.h>
#include <stdlib.h>

// note: am aware that binary constants are a GCC only thing - only using for tests

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

    cpsr tst = {.N = 1, .Z = 0, .C = 1, .V = 1};

    //0000 EQ Z = 1
    CPU.CPSR = tst;
    booltest(checkCond(EQ), false, "EQ test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(EQ), true, "EQ test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(EQ), false, "EQ test");

    // 0001 NE Z = 0;
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(NE), true, "NE test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(NE), false, "NE test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(NE), true, "NE test");

    // 1010 GE N = V
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(GE), true, "GE test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(GE), true, "GE test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(GE), true, "GE test");

    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(GE), false, "GE test");
    
    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(GE), false, "GE test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(GE), false, "GE test");

    // 1011 LT N != V
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(LT), false, "LT test");
    
    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(LT), false, "LT test");

    CPU.CPSR = ((cpsr) {.N = 0, .Z = 0, .C = 0, .V = 0});
    booltest(checkCond(LT), false, "LT test");
    
    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(LT), true, "LT test");
    
    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(LT), true, "LT test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(LT), true, "LT test");

    // 1100 GTZ = 0 && (N = V)
    //NZCV
    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(GT), true, "GT test");

    SETCPSR(0, 1, 0, 0);
    booltest(checkCond(GT), false, "GT test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(GT), false, "GT test");

    SETCPSR(0, 1, 1, 0);
    booltest(checkCond(GT), false, "GT test");

    SETCPSR(1, 0, 0, 1);
    booltest(checkCond(GT), true, "GT test");
    
    // 1101 LE Z || (N != V) NZCV
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(LE), false, "LE test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(LE), true, "LE test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(LE), false, "LE test");

    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(LE), true, "LE test");

    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(LE), true, "LE test");
    
    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(LE), true, "LE test");

    // 1110 AL (ignored)
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(AL), true, "AL test");
    
    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(AL), true, "AL test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(AL), true, "AL test");

    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(AL), true, "AL test");

    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(AL), true, "AL test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(AL), true, "AL test");

    testsection("processInstr Tests");

    testsection("branchInstr Tests");

    testsection("singleDataTransInstr Tests");

    testsection("MultiplyInstr Tests");

    testsection("processDataInstr Tests");

    testsection("getReg Tests");

    testsection("storemem Tests");

    testsection("getmem Tests");
}