#include "common_defs.h"
#include "process_branch.h"
#include "process_multiply.h"
#include "process_shift.h"
#include "process_data_processing.h"
#include "process_data_transfer.h"
#include <stddata.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

Map dummy;
Map func_proc; // Map<char*, void(*func)(FUNC_PROC_ARGS)
Map func_cond_codes; // Map<char*, char>
Map data_proc_opcodes; // Map<char*, char>
Set comp_funcs; // Set<char*>
Map shift_codes;

/* Helper Functions */
void InitFuncProc() {
    func_proc = NewEmptyMap(StringHash, StringEq);
    MapSet(func_proc, "b", ProcessBranch);
    int data_proc_func_count = 10;
    char* data_proc_funcs[] = {
        "add", "sub", "rsb", "and", "eor", "orr", "mov", "tst", "teq", "cmp"
    };
    for(int i = 0; i < data_proc_func_count; i++) {
        MapSet(func_proc, data_proc_funcs[i], ProcessDataProcessing);
    }
    MapSet(func_proc, "mul", ProcessMultiply);
    MapSet(func_proc, "mla", ProcessMultiply);
    MapSet(func_proc, "ldr", ProcessDataTransfer);
    MapSet(func_proc, "str", ProcessDataTransfer);
    MapSet(func_proc, "lsl", ProcessShift);
    MapSet(func_proc, "asr", ProcessShift);
    MapSet(func_proc, "lsr", ProcessShift);
    MapSet(func_proc, "ror", ProcessShift);
}

void InitFuncCondCodes() {
    func_cond_codes = NewEmptyMap(StringHash, StringEq);
    MapSet(func_cond_codes, "eq", 0b0000);
    MapSet(func_cond_codes, "ne", 0b0001);
    MapSet(func_cond_codes, "ge", 0b1010);
    MapSet(func_cond_codes, "lt", 0b1011);
    MapSet(func_cond_codes, "gt", 0b1100);
    MapSet(func_cond_codes, "le", 0b1101);
    MapSet(func_cond_codes, "al", 0b1110);
}

void InitDataProcOpcodes() {
    data_proc_opcodes = NewEmptyMap(StringHash, StringEq);
    MapSet(data_proc_opcodes, "and", 0b0000);
    MapSet(data_proc_opcodes, "eor", 0b0001);
    MapSet(data_proc_opcodes, "sub", 0b0010);
    MapSet(data_proc_opcodes, "rsb", 0b0011);
    MapSet(data_proc_opcodes, "add", 0b0100);
    MapSet(data_proc_opcodes, "orr", 0b1100);
    MapSet(data_proc_opcodes, "mov", 0b1101);
    MapSet(data_proc_opcodes, "tst", 0b1000);
    MapSet(data_proc_opcodes, "teq", 0b1001);
    MapSet(data_proc_opcodes, "cmp", 0b1010);
}

void InitCompFuncs() {
    comp_funcs = NewEmptySet(StringHash, StringEq);
    SetInsert(comp_funcs, "tst");
    SetInsert(comp_funcs, "teq");
    SetInsert(comp_funcs, "cmp");
}

void InitShiftCodes() {
    shift_codes = NewEmptyMap(StringHash, StringEq);
    MapSet(shift_codes, "lsl", 0b00);
    MapSet(shift_codes, "lsr", 0b01);
    MapSet(shift_codes, "asr", 0b10);
    MapSet(shift_codes, "ror", 0b11);
}

/* Interface Definitions */
void InitFunctionGen() {
    InitFuncProc();
    InitFuncCondCodes();
    InitDataProcOpcodes();
    InitCompFuncs();
    InitShiftCodes();
    dummy = NewEmptyMap(StringHash, StringEq);
}

void FinishFunctionGen() {
    DeleteMap(dummy);
    DeleteMap(func_proc);
    DeleteMap(func_cond_codes);
    DeleteMap(data_proc_opcodes);
    DeleteSet(comp_funcs);
    DeleteMap(shift_codes);
}

bool IsRegister(char* restrict token) {
    if(token[0] != 'r' && token[0] != 'R') {
        return false;
    }
    if(strlen(token) < 2) {
        return false;
    }
    for(int i = 1; i < strlen(token); i++) {
        if(!isdigit(token[i])) {
            return false;
        }
    }
    return true;
}

int GetRegisterNum(char* restrict reg) {
    assert(reg[0] == 'r' || reg[0] == 'R');
    assert(strlen(reg)>=2);
    int reg_num = atoi(reg + 1);
    assert(reg_num >= 0 && reg_num <= 15);
    return reg_num;
}

void SetInstruction(Vector restrict output, int instruction, int offset) {
    if(VectorSize(output) <= offset) {
        VectorResize(output, offset + 1);
    }
    VectorSet(output, offset, instruction);
}

long long GetExpressionValue(
    Map restrict symbols, 
    char* restrict expression, 
    bool pureexpression, 
    bool hashexpression
) {
    const int expr_len = strlen(expression);
    if(isalpha(expression[0])) {
        assert(MapQuery(symbols, expression));
        return (int)MapGet(symbols, expression) * 4;
    }
    char* start = expression;
    if(hashexpression && !pureexpression) {
        assert(expr_len >= 2);
        assert(expression[0] == '#');
        start++;
    }
    if(!hashexpression && !pureexpression) {
        assert(expr_len >= 2);
        assert(expression[0] == '=');
        start++;
    }
    char* end;
    long long out = strtoll(start, &end, 0);
    assert(end - expression == expr_len);
    return out;
}

void SplitFunction(
    char* restrict func_code, 
    char* restrict func_base, 
    unsigned int* restrict condition
) {
    if(MapQuery(func_proc, func_code)) {
        strcpy(func_base, func_code);
        *condition = MapGet(func_cond_codes, "al");
        return;
    }
    char* suffix = func_code + strlen(func_code) - 2;
    assert(MapQuery(func_cond_codes, suffix));
    strncpy(func_base, func_code, strlen(func_code) - 2);
    func_base[strlen(func_code) - 2] = 0;
    *condition = MapGet(func_cond_codes, suffix);
}

bool IsImmediate(char* token, bool ispure, bool ishash) {
    if(token[0] == '#' && ishash && !ispure) {
        return true;
    }

    if(token[0] == '=' && !ishash && !ispure) {
        return true;
    }
    
    if((isdigit(token[0]) || token[0] == '-' || token[0] == '+') && ispure) {
        return true;
    }
    return false;
}