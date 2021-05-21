#include "commandgen.h"
#include <stddata.h>
#include <string.h>

#define FUNC_PROC_ARGS Map restrict symbols, Vector restrict tokens,\
                       Vector restrict output, int offset
static Map restrict func_proc; // Map<char*, void(*func)(FUNC_PROC_ARGS)
static Map restrict func_cond_codes; // Map<char*, char>

/* Helper Functions */
char GetCondCode(char* func_code) {
    if(strlen(func_code) < 2) {
        return MapGet(func_cond_codes, "al");
    }
    char* suffix = calloc(2, sizeof(char));
    strncpy(suffix, func_code, 2);
    char out;
    if(!MapQuery(func_cond_codes, suffix)) {
        out = MapGet(func_cond_codes, "al");
    } else {
        out = MapGet(func_cond_codes, suffix);
    }
    free(suffix);
    return out;
}

unsigned int GetExpressionValue(char* expression) {
    assert(strlen(expression) > 0);
    int i = 0;
    if(expression[0] == '#' || expression[0] == '=') {
        i++;
    }
}

void ProcessBranch(FUNC_PROC_ARGS) {
    assert(output)
}

void ProcessDataProcessing(FUNC_PROC_ARGS) {

}

void ProcessMultiply(FUNC_PROC_ARGS) {

}

void ProcessDataTransfer(FUNC_PROC_ARGS) {
    
}

void InitFuncProc() {
    func_proc = NewEmptyMap(StringHash, StringEq);
    MapSet(func_proc, "b", ProcessBranch);
    int data_proc_func_count = 11;
    char* data_proc_funcs[] = {
        "add", "sub", "rsb", "and", "eor", "orr", "mov", "tst", "teq", "cmp", "lsl"
    };
    for(int i = 0; i < data_proc_func_count; i++) {
        MapSet(func_proc, data_proc_funcs[i], ProcessDataProcessing);
    }
    MapSet(func_proc, "mul", ProcessMultiply);
    MapSet(func_proc, "mla", ProcessMultiply);
    MapSet(func_proc, "ldr", ProcessDataTransfer);
    MapSet(func_proc, "str", ProcessDataTransfer);
}

void InitFuncCondCodes() {
    func_cond_codes = NewEmptyMap(StringHash, StringEq);
    MapSet(func_proc, "eq", 0b0000);
    MapSet(func_proc, "ne", 0b0001);
    MapSet(func_proc, "ge", 0b1010);
    MapSet(func_proc, "lt", 0b1011);
    MapSet(func_proc, "gt", 0b1100);
    MapSet(func_proc, "le", 0b1101);
    MapSet(func_proc, "al", 0b1110);
}

/* Interface Definitions */
void InitFunctionGen() {
    InitFuncProc();
    InitFuncCondCodes();
}

void FunctionGen(FUNC_PROC_ARGS) {

}

void FinishFunctionGen() {
    DeleteMap(func_proc);
    DeleteMap(func_cond_codes);
}