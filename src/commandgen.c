#include "commandgen.h"
#include <stddata.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define FUNC_PROC_ARGS Map restrict symbols, Vector restrict tokens,\
                       Vector restrict output, int offset, int instructions_num
static Map restrict func_proc; // Map<char*, void(*func)(FUNC_PROC_ARGS)
static Map restrict func_cond_codes; // Map<char*, char>

/* Helper Functions */
char GetCondCode(char* func_code) {
    if(strlen(func_code) < 2) {
        return MapGet(func_cond_codes, "al");
    }
    char* suffix = func_code + strlen(func_code) - 2;
    if(!MapQuery(func_cond_codes, suffix)) {
        return MapGet(func_cond_codes, "al");
    } else {
        return MapGet(func_cond_codes, suffix);
    }
}

unsigned int GetExpressionValue(
    Map symbols, 
    char* expression, 
    bool pureexpression, 
    bool hashexpression
) {
    const int expr_len = strlen(expression);
    if(isalpha(expression[0])) {
        return (int)MapGet(symbols, expression) * 4;
    }
    int base = 10;
    int start = 0;
    if(!isdigit(expression[0])) {
        assert(!pureexpression);
        assert(expression[0] == '#' || expression[0] == '=');
        assert((expression[0] == '#') == hashexpression);
        assert(expr_len >= 2);
        start = 1;
    }
    if(expr_len - start == 1 && expression[1] == '0') {
        return 0;
    }
    if(expression[start] == '0') {
        switch(expression[start + 1]) {
            case 'x':
                start += 2;
                base = 16;
                break;
            case 'b':
                start += 2;
                base = 2;
                break;
            case 'd':
                start += 2;
                break;
            case 'o':
                start += 2; /* pass through */
            default:
                base = 8;
        }
    }
    unsigned int out = 0;
    for(start; start < expr_len; start++) {
        char c = expression[start];
        int value;
        if(base > 10 && c <= 'Z' && c >= 'A') {
            value = c - 'A' + 10;
        } else if(base > 10 && c <= 'z' && c >= 'a') {
            value = c - 'a' + 10;
        } else {
            value = c - '0';
        }
        assert(value >= 0 && value < base);
        out = out * base + value;
    }
    return out;
}

void SetInstruction(Vector output, int instruction, int offset) {
    if(VectorSize(output) <= offset) {
        VectorResize(output, offset + 1);
    }
    VectorSet(output, offset, instruction);
}

/* Function Processing Functions */
void ProcessBranch(FUNC_PROC_ARGS) {
    assert(VectorSize(tokens) == 2);

    const int target = GetExpressionValue(symbols, VectorGet(tokens, 1), true, true);
    assert(((target >> 2) << 2) == target);
    assert(target < instructions_num * 4);
    
    const long long pc_offset = (long long)target / 4 - 2 - offset;
    assert((2<<23) <= pc_offset < (2 << 23));

    unsigned int instr = 0x0A000000;
    instr |= (unsigned int)GetCondCode(VectorGet(tokens, 0)) << 28;
    instr |= pc_offset & 0xFFFFFF;

    SetInstruction(output, instr, offset);
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
    MapSet(func_cond_codes, "eq", 0b0000);
    MapSet(func_cond_codes, "ne", 0b0001);
    MapSet(func_cond_codes, "ge", 0b1010);
    MapSet(func_cond_codes, "lt", 0b1011);
    MapSet(func_cond_codes, "gt", 0b1100);
    MapSet(func_cond_codes, "le", 0b1101);
    MapSet(func_cond_codes, "al", 0b1110);
}

/* Interface Definitions */
void InitFunctionGen() {
    InitFuncProc();
    InitFuncCondCodes();
}

void FunctionGen(FUNC_PROC_ARGS) {
    char* func_code = VectorGet(tokens, 0);
    int func_code_len = strlen(func_code);
    char* raw_func_code = malloc(sizeof(char) * (func_code_len + 1));
    if(func_code_len <= 1) {
        strcpy(raw_func_code, func_code);
    } else if(MapQuery(func_cond_codes, func_code + func_code_len - 2)) {
        strncpy(raw_func_code, func_code, func_code_len - 2);
    } else {
        strcpy(raw_func_code, func_code);
    }
    void(*process_function)(FUNC_PROC_ARGS) = MapGet(func_proc, raw_func_code);
    assert(process_function != NULL);
    process_function(symbols, tokens, output, offset, instructions_num);
}

void FinishFunctionGen() {
    DeleteMap(func_proc);
    DeleteMap(func_cond_codes);
}