#include "..\src\emulate.c"
#include <stdbool.h>
#include <stdlib.h>

// test condition checker
void check(bool condition, char *testname) {
    printf("\nT %s:   %c", testname, condition?'P':'F');
}


int main(){

    /*GETBITS TEST:
    33222222222211111111110000000000
    10987654321098765432109876543210
    11101111001101111111111101000001
    */

    uint32_t test_data1 = 0b11101111001101111111111101000001;

    printf("\nGETBITS TESTS:");
    check(GETBITS(test_data1, 5, 0) == 1, "Can get lengths of 0 bits");
    check(GETBITS(test_data1, 0, 1) == 1, "Can get lengths of 1 bit");
    check(GETBITS(test_data1, 3, 3) == 0, "Check 1");
    check(GETBITS(test_data1, 7, 5) == 0b11110, "Check 2");
    check(GETBITS(test_data1, 7, 2) == 0b10, "Check 3");

    // getProgram Tests:

    // runProgram Tests:
    
    //checkCond Tests:

    // set CPU.CPSR
    // run checkcond with mnemonic
    // get result checked
    //CPSR = NZCV

    // 0000 EQ Z = 1
    CPU.CPSR = 0b1011;
    check(!checkCond(EQ), "EQ check 1");
    CPU.CPSR = 0b1111;
    check(checkCond(EQ), "EQ check 2");
    CPU.CPSR = 0b0000;
    check(!checkCond(EQ), "EQ check 3");

    // 0001 NE Z = 0;
    CPU.CPSR = 0b1011;
    check(checkCond(NE), "NE check 1");
    CPU.CPSR = 0b1111;
    check(!checkCond(NE), "NE check 2");
    CPU.CPSR = 0b0000;
    check(checkCond(NE), "NE check 3");

    // 1010 GE N = V
    CPU.CPSR = 0b1011;
    check(checkCond(GE), "GE check 1");
    CPU.CPSR = 0b1111;
    check(checkCond(GE), "GE check 2");
    CPU.CPSR = 0b0000;
    check(checkCond(GE), "GE check 3");
    CPU.CPSR = 0b0011;
    check(!checkCond(GE), "GE check 4");
    CPU.CPSR = 0b1110;
    check(!checkCond(GE), "GE check 5");
    CPU.CPSR = 0b0001;
    check(!checkCond(GE), "GE check 6");

    // 1011 LT N != V
    CPU.CPSR = 0b1011;
    check(!checkCond(LT), "LT check 1");
    CPU.CPSR = 0b1111;
    check(!checkCond(LT), "LT check 2");
    CPU.CPSR = 0b0000;
    check(!checkCond(LT), "LT check 3");
    CPU.CPSR = 0b0011;
    check(checkCond(LT), "LT check 4");
    CPU.CPSR = 0b1110;
    check(checkCond(LT), "LT check 5");
    CPU.CPSR = 0b0001;
    check(checkCond(LT), "LT check 6");

    // 1100 GTZ = 0 && (N = V)
    //NZCV
    CPU.CPSR = 0b0000;
    check(checkCond(GT), "GT check 1");
    CPU.CPSR = 0b0100;
    check(!checkCond(GT), "GT check 2");
    CPU.CPSR = 0b0001;
    check(!checkCond(GT), "GT check 3");
    CPU.CPSR = 0b0110;
    check(!checkCond(GT), "GT check 4");
    CPU.CPSR = 0b1001;
    check(checkCond(GT), "GT check 5");
    
    // 1101 LE Z || (N != V) NZCV
    CPU.CPSR = 0b1011;
    check(!checkCond(LE), "LE check 1");
    CPU.CPSR = 0b1111;
    check(checkCond(LE), "LE check 2");
    CPU.CPSR = 0b0000;
    check(!checkCond(LE), "LE check 3");
    CPU.CPSR = 0b0011;
    check(checkCond(LE), "LE check 4");
    CPU.CPSR = 0b1110;
    check(checkCond(LE), "LE check 5");
    CPU.CPSR = 0b0001;
    check(checkCond(LE), "LE check 6");

    // 1110 AL (ignored)
    CPU.CPSR = 0b1011;
    check(checkCond(AL), "AL check 1");
    CPU.CPSR = 0b1111;
    check(checkCond(AL), "AL check 2");
    CPU.CPSR = 0b0000;
    check(checkCond(AL), "AL check 3");
    CPU.CPSR = 0b0011;
    check(checkCond(AL), "AL check 4");
    CPU.CPSR = 0b1110;
    check(checkCond(AL), "AL check 5");
    CPU.CPSR = 0b0001;
    check(checkCond(AL), "AL check 6");

    // processInstr Tests:

    // branchInstr Tests:

    // singleDataTransInstr Tests:

    // multiplyInstr Tests:

    // processDataInstr Tests:

    // getReg Tests:
    //DEFO do, this is easier

    // storemem Tests:

    // getmem Tests:
}