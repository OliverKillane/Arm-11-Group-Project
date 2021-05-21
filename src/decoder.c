#include <stdlib.h>
#include <stdio.h>
#include "emulate.h"


void processInstr(instruction instr){

    char typeBits = GETBITS(instr, 26, 2);
    if(typeBits == 10){
        branchInstr(instr,getReg(PC));
    }
}