#include "common_defs.h"
#include "process_branch.h"
#include "process_multiply.h"
#include "process_shift.h"
#include "process_data_processing.h"
#include "process_data_transfer.h"
#include "../tokenizer.h"
#include <stddata.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

Map func_proc; // Map<Token, void(*func)(FUNC_PROC_ARGS)
Map data_proc_opcodes; // Map<Token, char>
Set comp_funcs; // Set<Token>
Map shift_codes;

/* Helper Functions */
void InitFuncProc() {
    func_proc = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(func_proc, INSTR_BRN, ProcessBranch);
    int data_proc_func_count = 10;
    InstructionType data_proc_funcs[] = {
        INSTR_ADD,
        INSTR_SUB,
        INSTR_RSB,
        INSTR_AND,
        INSTR_EOR,
        INSTR_ORR,
        INSTR_MOV,
        INSTR_TST,
        INSTR_TEQ,
        INSTR_CMP
    };
    for(int i = 0; i < data_proc_func_count; i++) {
        MapSet(func_proc, (int)data_proc_funcs[i], ProcessDataProcessing);
    }
    MapSet(func_proc, INSTR_MUL, ProcessMultiply);
    MapSet(func_proc, INSTR_MLA, ProcessMultiply);
    MapSet(func_proc, INSTR_LDR, ProcessDataTransfer);
    MapSet(func_proc, INSTR_STR, ProcessDataTransfer);
    MapSet(func_proc, INSTR_LSL, ProcessShift);
    MapSet(func_proc, INSTR_ASR, ProcessShift);
    MapSet(func_proc, INSTR_LSR, ProcessShift);
    MapSet(func_proc, INSTR_ROR, ProcessShift);
}

void InitDataProcOpcodes() {
    data_proc_opcodes = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(data_proc_opcodes, INSTR_AND, 0b0000);
    MapSet(data_proc_opcodes, INSTR_EOR, 0b0001);
    MapSet(data_proc_opcodes, INSTR_SUB, 0b0010);
    MapSet(data_proc_opcodes, INSTR_RSB, 0b0011);
    MapSet(data_proc_opcodes, INSTR_ADD, 0b0100);
    MapSet(data_proc_opcodes, INSTR_ORR, 0b1100);
    MapSet(data_proc_opcodes, INSTR_MOV, 0b1101);
    MapSet(data_proc_opcodes, INSTR_TST, 0b1000);
    MapSet(data_proc_opcodes, INSTR_TEQ, 0b1001);
    MapSet(data_proc_opcodes, INSTR_CMP, 0b1010);
}

void InitCompFuncs() {
    comp_funcs = NewEmptySet(UnsafeIntHash, UnsafeIntEq);
    SetInsert(comp_funcs, INSTR_TST);
    SetInsert(comp_funcs, INSTR_TEQ);
    SetInsert(comp_funcs, INSTR_CMP);
}

void InitShiftCodes() {
    shift_codes = NewEmptyMap(UnsafeIntHash, UnsafeIntEq);
    MapSet(shift_codes, INSTR_LSL, 0b00);
    MapSet(shift_codes, INSTR_LSR, 0b01);
    MapSet(shift_codes, INSTR_ASR, 0b10);
    MapSet(shift_codes, INSTR_ROR, 0b11);
}

/* Interface Definitions */
void InitFunctionGen() {
    InitFuncProc();
    InitDataProcOpcodes();
    InitCompFuncs();
    InitShiftCodes();
}

void FinishFunctionGen() {
    DeleteMap(func_proc);
    DeleteMap(data_proc_opcodes);
    DeleteSet(comp_funcs);
    DeleteMap(shift_codes);
}

void SetInstruction(Vector restrict output, int instruction, int offset) {
    if(VectorSize(output) <= offset) {
        VectorResize(output, offset + 1);
    }
    VectorSet(output, offset, instruction);
}