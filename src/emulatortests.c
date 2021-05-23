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

  uint32_t testWord = 0b11101111001101111111111101000001;

  int32test(GETBITS(testWord, 5, 0), 0, "Can get lengths of 0 bits");
  int32test(GETBITS(testWord, 5, 0), 0, "Can get lengths of 1 bit");
  int32test(GETBITS(testWord, 3, 3), 0, "");
  int32test(GETBITS(testWord, 7, 5), 0b11110, "");
  int32test(GETBITS(testWord, 7, 2), 0b10, "");
  int32test(GETBITS(testWord, 27, 2), 0b01, "");
  int32test(GETBITS(testWord, 19, 6), 0b100110, "");
  int32test(GETBITS(testWord, 0, 7), 0b1000001, "");


  testsection("GETBIT Tests");

  int32test(GETBIT(testWord, 7), 0, "");
  int32test(GETBIT(testWord, 0), 1, "");
  int32test(GETBIT(testWord, 31), 1, "");
  int32test(GETBIT(testWord, 27), 1, "");

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

  testsection("shiftOperation Tests");

  shiftRes holder;

  /*
  Index:  110000000000
          109876543210
  base:   SSSSSSSSRRRR
  imm:    IIIIITT0RRRR
  reg:    RRRR0TT1RRRR
  */

  //Constant Shift
  // lsl (00):
  
  *GETREG(3) = 674;
  *GETREG(4) = (1 << 31) + 6;
  *GETREG(5) = (3 << 30) + 6;

  // lsl by 3
  holder = shiftOperation(0b000110000011);
  int32test(674 << 3, holder.result, "LSL Register 3 (674) by 3 result");
  int32test(0, holder.carryout, "LSL Register 3 (674) by 3 carryout");

  holder = shiftOperation(0b001000000100);
  int32test(6 << 4, holder.result, "LSL Register 4 (2^31 + 6) by 4 result");
  int32test(0, holder.carryout, "LSL Register 4 (2^31 + 6) by 4 carryout");

  holder = shiftOperation(0b001000000101);
  int32test(6 << 4, holder.result, "LSL Register 4 (3^30 + 6) by 4 result");
  int32test(0, holder.carryout, "LSL Register 4 (3^30 + 6) by 4 carryout");

  // lsr (01):

  *GETREG(4) =  6;
  *GETREG(5) = 30;

  // lsr by 3
  holder = shiftOperation(0b000110100011);
  int32test(674 >> 3, holder.result, "LSR Register 3 (674) by 3 result");
  int32test(0, holder.carryout, "LSR Register 3 (674) by 3 carryout");

  holder = shiftOperation(0b001000100100);
  int32test(6 >> 4, holder.result, "LSR Register 4 (6) by 4 result");
  int32test(0, holder.carryout, "LSR Register 4 (6) by 4 carryout");

  holder = shiftOperation(0b001000100101);
  int32test(30 >> 4, holder.result, "LSR Register 5 (30) by 4 result");
  int32test(1, holder.carryout, "LSR Register 5 (30) by 4 carryout");

  // asr (10):

  *GETREG(6) = -13;
  holder = shiftOperation(0b000011000110);
  int32test(-7, holder.result, "ASR Register 6 (-13) by 1 result");
  int32test(1, holder.carryout, "ASR Register 6 (-13) by 1 carryout");

  holder = shiftOperation(0b000111000011);
  int32test(674 >> 3, holder.result, "ASR Register 3 (674) by 3 result");
  int32test(0, holder.carryout, "ASR Register 3 (674) by 3 carryout");

  holder = shiftOperation(0b001011000100);
  int32test(6 >> 4, holder.result, "ASR Register 4 (6) by 4 result");
  int32test(0, holder.carryout, "ASR Register 4 (6) by 4 carryout");

  // ror (11):
  //below not done yet
  holder = shiftOperation(0b000011100100);
  int32test(3, holder.result, "ROR Register 4 (6) by 1 result");
  int32test(0, holder.carryout, "ROR Register 4 (6) by 1 carryout");

  //Shift Register
  // lsl (00):

  // lsr (01):

  // asr (10):

  // ror (11):




  testsection("MultiplyInstr Tests");

  testsection("processDataInstr Tests");
}