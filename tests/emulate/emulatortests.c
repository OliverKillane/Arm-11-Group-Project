#include <stdbool.h>
#include <stdlib.h>

/* define test so that emulator main function not included */
#define TEST

#include "testutils.c"
#include "emulate.h"
#include "emulate.c"

#define SETCPSR(n,z,c,v) CPU.CPSR.N = n;CPU.CPSR.Z = z;CPU.CPSR.C = c;CPU.CPSR.V = v;
// note: am aware that binary constants are a GCC only thing - only using for tests

int main(){
    starttests("Emulator Tests");

    testsection("GETBITS tests");

    /*
    33222222222211111111110000000000
    10987654321098765432109876543210
    11101111001101111111111101000001
    */
    //                    11101111001101111111111101000001
    uint32_t testWord = 0xEF37FF41;

    int32test(GETBITS(testWord, 5, 0), 0, "Can get lengths of 0 bits");
    int32test(GETBITS(testWord, 5, 0), 0, "Can get lengths of 1 bit");
    int32test(GETBITS(testWord, 3, 3), 0, "Normal test");
    int32test(GETBITS(testWord, 7, 5), 0x1E, "Normal test"); //11110
    int32test(GETBITS(testWord, 7, 2), 0x2, "Normal test"); //10,
    int32test(GETBITS(testWord, 27, 2), 0x1, "Normal test"); //01,
    int32test(GETBITS(testWord, 19, 6), 0x26, "Normal test"); //100110,
    int32test(GETBITS(testWord, 0, 7), 0x41, "Normal test"); //1000001,


    testsection("GETBIT Tests");

    
    int32test(GETBIT(testWord, 0), 1, "Can get the LSB");
    int32test(GETBIT(testWord, 31), 1, "Can get the MSB");
    int32test(GETBIT(testWord, 27), 1, "Normal test");
    int32test(GETBIT(testWord, 7), 0, "Normal test");

    testsection("checkCond Tests");

    // set CPU.CPSR
    // run checkcond with mnemonic
    // get result checked
    //CPSR = NZCV

    cpsr tst = {.N = 1, .Z = 0, .C = 1, .V = 1};

    //0000 EQ Z = 1
    instruction inst = 0x0; //00000000000000000000000000000000
    CPU.CPSR = tst;
    booltest(checkCond(inst), false, "EQ test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(inst), true, "EQ test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(inst), false, "EQ test");

    // 0001 NE Z = 0;
    inst = 0x10000000; //00010000000000000000000000000000
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(inst), true, "NE test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(inst), false, "NE test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(inst), true, "NE test");

    // 1010 GE N = V
    inst = 0xa0000000; //10100000000000000000000000000000
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(inst), true, "GE test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(inst), true, "GE test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(inst), true, "GE test");

    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(inst), false, "GE test");
    
    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(inst), false, "GE test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(inst), false, "GE test");

    // 1011 LT N != V
    inst = 0xb0000000; //10110000000000000000000000000000
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(inst), false, "LT test");
    
    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(inst), false, "LT test");

    CPU.CPSR = ((cpsr) {.N = 0, .Z = 0, .C = 0, .V = 0});
    booltest(checkCond(inst), false, "LT test");
    
    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(inst), true, "LT test");
    
    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(inst), true, "LT test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(inst), true, "LT test");

    // 1100 GTZ = 0 && (N = V)
    //NZCV
    inst = 0xc0000000; //11000000000000000000000000000000
    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(inst), true, "GT test");

    SETCPSR(0, 1, 0, 0);
    booltest(checkCond(inst), false, "GT test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(inst), false, "GT test");

    SETCPSR(0, 1, 1, 0);
    booltest(checkCond(inst), false, "GT test");

    SETCPSR(1, 0, 0, 1);
    booltest(checkCond(inst), true, "GT test");
    
    // 1101 LE Z || (N != V) NZCV
    inst = 0xd0000000; //11010000000000000000000000000000
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(inst), false, "LE test");

    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(inst), true, "LE test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(inst), false, "LE test");

    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(inst), true, "LE test");

    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(inst), true, "LE test");
    
    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(inst), true, "LE test");

    // 1110 AL (ignored)
    inst = 0xe0000000; //11100000000000000000000000000000
    SETCPSR(1, 0, 1, 1);
    booltest(checkCond(inst), true, "AL test");
    
    SETCPSR(1, 1, 1, 1);
    booltest(checkCond(inst), true, "AL test");

    SETCPSR(0, 0, 0, 0);
    booltest(checkCond(inst), true, "AL test");

    SETCPSR(0, 0, 1, 1);
    booltest(checkCond(inst), true, "AL test");

    SETCPSR(1, 1, 1, 0);
    booltest(checkCond(inst), true, "AL test");

    SETCPSR(0, 0, 0, 1);
    booltest(checkCond(inst), true, "AL test");

    testsection("shiftOperation Tests");

    shiftRes holder;

    /*
    Index:  110000000000
                    109876543210
    base:   SSSSSSSSRRRR
    imm:    IIIIITT0RRRR
    reg:    RRRR0TT1RRRR
    */


    testsubsection("Constant Shift Tests");
    //Constant Shift
    // lsl (00):
    
    *GETREG(3) = 674;
    *GETREG(4) = (1 << 31) + 6;
    *GETREG(5) = (3 << 30) + 6;

    // lsl by 3
    holder = shiftOperation(0x183); //000110000011
    int32test(674 << 3, holder.result, "LSL Register 3 (674) by 3 result");
    booltest(0, holder.carryout, "LSL Register 3 (674) by 3 carryout");

    holder = shiftOperation(0x84); //000010000100
    int32test(6 << 1, holder.result, "LSL Register 4 (2^31 + 6) by 1 result");
    booltest(1, holder.carryout, "LSL Register 4 (2^31 + 6) by 1 carryout");

    holder = shiftOperation(0x205); //001000000101
    int32test(6 << 4, holder.result, "LSL Register 4 (3^30 + 6) by 4 result");
    booltest(0, holder.carryout, "LSL Register 4 (3^30 + 6) by 4 carryout");

    // lsr (01):

    *GETREG(4) =  6;
    *GETREG(5) = 30;

    // lsr by 3
    holder = shiftOperation(0x1a3); //000110100011
    int32test(674 >> 3, holder.result, "LSR Register 3 (674) by 3 result");
    booltest(0, holder.carryout, "LSR Register 3 (674) by 3 carryout");

    holder = shiftOperation(0x224); //001000100100
    int32test(6 >> 4, holder.result, "LSR Register 4 (6) by 4 result");
    booltest(0, holder.carryout, "LSR Register 4 (6) by 4 carryout");

    holder = shiftOperation(0x225); //001000100101
    int32test(30 >> 4, holder.result, "LSR Register 5 (30) by 4 result");
    booltest(1, holder.carryout, "LSR Register 5 (30) by 4 carryout");

    // asr (10):

    *GETREG(6) = -13;
    holder = shiftOperation(0xc6); //000011000110
    int32test(-7, holder.result, "ASR Register 6 (-13) by 1 result");
    booltest(1, holder.carryout, "ASR Register 6 (-13) by 1 carryout");

    holder = shiftOperation(0x1c3); //000111000011
    int32test(674 >> 3, holder.result, "ASR Register 3 (674) by 3 result");
    booltest(0, holder.carryout, "ASR Register 3 (674) by 3 carryout");

    holder = shiftOperation(0x2c4); //001011000100
    int32test(6 >> 4, holder.result, "ASR Register 4 (6) by 4 result");
    int32test(0, holder.carryout, "ASR Register 4 (6) by 4 carryout");

    // ror (11):
    holder = shiftOperation(0xe4); //000011100100
    int32test(3, holder.result, "ROR Register 4 (6) by 1 result");
    booltest(0, holder.carryout, "ROR Register 4 (6) by 1 carryout");

    *GETREG(1) = 7;

    holder = shiftOperation(0x161); //000101100001
    int32test(1 + (3 << 30), holder.result, "ROR Register 1 (7) by 2 result");
    booltest(1, holder.carryout, "ROR Register 1 (7) by 2 carryout");

    //Shift Register

    testsubsection("Register Shift Tests");

    // lsl (00):
    *GETREG(3) = 674;
    *GETREG(1) = 3;
    holder = shiftOperation(0x113); //000100010011
    int32test(674 << 3, holder.result, "LSL Register 3 (674) by Register 1 (3) result");
    booltest(0, holder.carryout, "LSL Register 3 (674) by Register 1 (3) carryout");

    *GETREG(4) =  6;
    *GETREG(5) = 30;

    holder = shiftOperation(0x415); //010000010101
    int32test(30 << 6, holder.result, "LSL Register 5 (30) by Register 4 (6) result");
    booltest(0, holder.carryout, "LSL Register 5 (30) by Register 4 (6) carryout");


    *GETREG(4) = (1 << 31) + 6;
    *GETREG(2) = 1;

    holder = shiftOperation(0x214); //001000010100
    int32test(6 << 1, holder.result, "LSL Register 4 (2^31 + 6) by Reg 2 (1) result");
    booltest(1, holder.carryout, "LSL Register 4 (2^31 + 6) by Reg 2 (1) carryout");

    // lsr (01):

    *GETREG(4) =  6;
    *GETREG(5) = 30;
    *GETREG(7) = 4;

    // lsr by 3
    holder = shiftOperation(0x133); //000100110011
    int32test(674 >> 3, holder.result, "LSR Register 3 (674) by Reg 1 (3) result");
    booltest(0, holder.carryout, "LSR Register 3 (674) by Reg 1 (3) carryout");

    holder = shiftOperation(0x734); //011100110100
    int32test(6 >> 4, holder.result, "LSR Register 4 (6) by Reg 7 (4) result");
    booltest(0, holder.carryout, "LSR Register 4 (6) by Reg 7 (4) carryout");

    holder = shiftOperation(0x735); //011100110101
    int32test(30 >> 4, holder.result, "LSR Register 5 (30) by Reg 7 (4) result");
    booltest(1, holder.carryout, "LSR Register 5 (30) by Reg 7 (4) carryout");

    // asr (10):

    *GETREG(6) = -13;

    holder = shiftOperation(0x256); //001001010110
    int32test(-7, holder.result, "ASR Register 6 (-13) by Reg 2 (1) result");
    booltest(1, holder.carryout, "ASR Register 6 (-13) by Reg 2 (1) carryout");

    holder = shiftOperation(0x153); //000101010011
    int32test(674 >> 3, holder.result, "ASR Register 3 (674) by Reg 1 (3) result");
    booltest(0, holder.carryout, "ASR Register 3 (674) by Reg 1 (3) carryout");

    holder = shiftOperation(0x754); //011101010100
    int32test(6 >> 4, holder.result, "ASR Register 4 (6) by Reg 7 (4) result");
    booltest(0, holder.carryout, "ASR Register 4 (6) by Reg 7 (4) carryout");

    // ror (11):

    holder = shiftOperation(0x274); //001001110100
    int32test(3, holder.result, "ROR Register 4 (6) by Reg 2 (1) result");
    booltest(0, holder.carryout, "ROR Register 4 (6) by Reg 2 (1) carryout");

    *GETREG(1) = 7;
    *GETREG(8) = 2;

    holder = shiftOperation(0x871); //100001110001
    int32test(1 + (3 << 30), holder.result, "ROR Register 1 (7) by Reg 8 (2) result");
    booltest(1, holder.carryout, "ROR Register 1 (7) by Reg 8 (2) carryout");


    testsection("processDataInstr Tests");


    instruction instr;

    testsubsection("immediate operand2 Tests");
    SETCPSR(0, 0, 0, 0);
    *GETREG(1) = 12;
    instr = 0x291100f; //00000010100100010001000000001111
    processDataInstr(instr);
    int32test(27 , *GETREG(1), "Add 15 to Register 1 (12) destination reg");
    booltest(0, CPU.CPSR.N, "Add 15 to Register 1 (12) N flag");
    booltest(0, CPU.CPSR.Z, "Add 15 to Register 1 (12) Z flag");
    booltest(0, CPU.CPSR.C, "Add 15 to Register 1 (12) C flag");
    booltest(0, CPU.CPSR.V, "Add 15 to Register 1 (12) V flag"); 

    *GETREG(1) = 12;
    instr = 0x351100f; //00000011010100010001000000001111
    processDataInstr(instr);
    int32test(12 , *GETREG(1), "Compare 15 to Register 1 (12) destination reg");
    booltest(1, CPU.CPSR.N, "Compare 15 to Register 1 (12) N flag");
    booltest(0, CPU.CPSR.Z, "Compare 15 to Register 1 (12) Z flag");
    booltest(0, CPU.CPSR.C, "Compare 15 to Register 1 (12) C flag");
    booltest(0, CPU.CPSR.V, "Compare 15 to Register 1 (12) V flag"); 

    SETCPSR(0, 0, 0, 0);
    instr = 0x3b1100f; //00000011101100010001000000001111
    processDataInstr(instr);
    int32test(15 , *GETREG(1), "Move 15 to Register 1 (12) destination reg");
    booltest(0, CPU.CPSR.N, "Move 15 to Register 1 (12) N flag");
    booltest(0, CPU.CPSR.Z, "Move 15 to Register 1 (12) Z flag");
    booltest(0, CPU.CPSR.C, "Move 15 to Register 1 (12) C flag");
    booltest(0, CPU.CPSR.V, "Move 15 to Register 1 (12) V flag"); 

    testsubsection("shifter operand2 Tests");
    SETCPSR(0, 0, 0, 0);
    *GETREG(1) = 12;
    *GETREG(3) = (1 << 30) + 4;
    instr = 0x112103; //00000000000100010010000100000011
    processDataInstr(instr);
    int32test(0 , *GETREG(2), "Reg 1(12) AND Reg 3(2^30 + 4) destination Reg 2");
    booltest(0, CPU.CPSR.N, "Reg 1(12) AND Reg 3 N flag");
    booltest(1, CPU.CPSR.Z, "Reg 1(12) AND Reg 3 Z flag");
    booltest(1, CPU.CPSR.C, "Reg 1(12) AND Reg 3 C flag");
    booltest(0, CPU.CPSR.V, "Reg 1(12) AND Reg 3 V flag"); 

    *GETREG(3) = (1 << 30) + 7;
    *GETREG(4) = 2;
    instr = 0x312413; //00000000001100010010010000010011
    processDataInstr(instr);
    int32test(16 , *GETREG(2), "Reg 1(12) EOR Reg 3(2^30 + 7) destination Reg 2");
    booltest(0, CPU.CPSR.N, "Reg 1(12) EOR Reg 3 N flag");
    booltest(0, CPU.CPSR.Z, "Reg 1(12) EOR Reg 3 Z flag");
    booltest(1, CPU.CPSR.C, "Reg 1(12) EOR Reg 3 C flag");
    booltest(0, CPU.CPSR.V, "Reg 1(12) EOR Reg 3 V flag");
    

    printResult();
}