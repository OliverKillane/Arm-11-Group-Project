#include "commandgen.h"
#include <stddata.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdio.h>

#define FUNC_PROC_ARGS Map restrict symbols, Vector restrict tokens,\
                       Vector restrict output, int offset, int instructions_num
static Map restrict dummy;
static Map restrict func_proc; // Map<char*, void(*func)(FUNC_PROC_ARGS)
static Map restrict func_cond_codes; // Map<char*, char>
static Map restrict data_proc_opcodes; // Map<char*, char>
static Set restrict comp_funcs; // Set<char*>
static Map restrict shift_codes;
const unsigned int MAX_FUNCTION_LENGTH = 3;

/* Helper Functions */
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
    *condition = MapGet(func_cond_codes, suffix);
}

unsigned int GetExpressionValue(
    Map restrict symbols, 
    char* restrict expression, 
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
    unsigned long long out = 0;
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
        assert(out < ((long long)1<<32));
    }
    return out;
}

void SetInstruction(Vector restrict output, int instruction, int offset) {
    if(VectorSize(output) <= offset) {
        VectorResize(output, offset + 1);
    }
    VectorSet(output, offset, instruction);
}

int GetRegisterNum(char* restrict reg) {
    assert(reg[0] == 'r' || reg[0] == 'R');
    assert(strlen(reg)>=2);
    int reg_num = atoi(reg + 1);
    assert(reg_num >= 0 && reg_num <= 16);
    return reg_num;
}

bool IsRegister(char* restrict token) { // may also be a label
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

/* Function Processing Functions */
void ProcessBranch(FUNC_PROC_ARGS) {
    assert(VectorSize(tokens) == 2);

    unsigned int condition;
    char dummy[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(VectorGet(tokens, 0), dummy, &condition);

    const int target = GetExpressionValue(symbols, VectorGet(tokens, 1), true, true);
    assert(((target >> 2) << 2) == target);
    assert(target < instructions_num * 4);
    
    const long long pc_offset = (long long)target / 4 - 2 - offset;
    assert((2<<23) <= pc_offset < (2 << 23));

    unsigned int instr = 0x0A000000;
    instr |= condition << 28;
    instr |= pc_offset & 0xFFFFFF;

    SetInstruction(output, instr, offset);
}

void ProcessDataProcessing(FUNC_PROC_ARGS) {
    const int tokens_num = VectorSize(tokens);
    assert(tokens_num >= 2);
    
    unsigned int condition;
    char func_base[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(VectorGet(tokens, 0), func_base, &condition);
    assert(MapQuery(data_proc_opcodes, func_base));
    int opcode = MapGet(data_proc_opcodes, func_base);

    assert(IsRegister(VectorGet(tokens, 1)));
    unsigned int reg_d, reg_n, operand_start, set_cspr;
    if(StringEq(func_base, "mov")) {
        reg_d = GetRegisterNum(VectorGet(tokens, 1));
        reg_n = 0;
        operand_start = 2;
        set_cspr = 0;
    } else if(SetQuery(comp_funcs, func_base)) {
        reg_d = 0;
        reg_n = GetRegisterNum(VectorGet(tokens, 1));
        operand_start = 2;
        set_cspr = 1;
    } else {
        assert(tokens_num >= 3);
        assert(IsRegister(VectorGet(tokens, 2)));
        reg_d = GetRegisterNum(VectorGet(tokens, 1));
        reg_n = GetRegisterNum(VectorGet(tokens, 2));
        operand_start = 3;
        set_cspr = 0;
    }
    assert(reg_d <= 12 && reg_n <= 12);

    assert(tokens_num > operand_start);
    unsigned int immediate = ((char*)VectorGet(tokens, operand_start))[0] == '#';

    unsigned int operand2 = 0;
    if(immediate) {
        assert(tokens_num == operand_start + 1);
        unsigned int expr_value = GetExpressionValue(
            dummy, VectorGet(tokens, operand_start), false, true
        );
        unsigned int rotate_left = 0;
        while((expr_value & 0b11) == 0 && expr_value > 0) {
            rotate_left++;
            expr_value >>= 2;
        }
        assert(expr_value < (1<<8));
        operand2 |= (rotate_left == 0 ? 0 : 16 - rotate_left) << 8;
        operand2 |= expr_value;
    } else {
        assert(IsRegister(VectorGet(tokens, operand_start)));
        unsigned int reg_m = GetRegisterNum(VectorGet(tokens, operand_start));
        assert(reg_m <= 12);
        
        unsigned int shift = 0;
        if(tokens_num > operand_start + 1) {
            assert(tokens_num == operand_start + 3);
            assert(MapQuery(shift_codes, VectorGet(tokens, operand_start + 1)));
            unsigned int shift_code = MapGet(shift_codes, VectorGet(tokens, operand_start + 1));

            if(((char*)VectorGet(tokens, operand_start + 2))[0] == '#') {
                unsigned int shamt = GetExpressionValue(
                    dummy, VectorGet(tokens, operand_start + 2), false, true
                );
                shift = 0;
                shift |= shift_code << 1;
                shift |= shamt << 3;

            } else {
                assert(IsRegister(VectorGet(tokens, operand_start + 2)));
                unsigned int reg_s = GetRegisterNum(VectorGet(tokens, operand_start + 2));
                assert(reg_s <= 12);

                shift = 1;
                shift |= shift_code << 1;
                shift |= reg_s << 4;
            }
        }

        operand2 |= reg_m;
        operand2 |= shift << 4;
    }

    unsigned int instr = 0;
    instr |= condition << 28;
    instr |= immediate << 25;
    instr |= opcode << 21;
    instr |= set_cspr << 20;
    instr |= reg_n << 16;
    instr |= reg_d << 12;
    instr |= operand2;
    SetInstruction(output, instr, offset);
}

void ProcessMultiply(FUNC_PROC_ARGS) {

}

void ProcessDataTransfer(FUNC_PROC_ARGS) {
    
}

void ProcessShift(FUNC_PROC_ARGS) {

}

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

void FunctionGen(FUNC_PROC_ARGS) {
    char* func_code = VectorGet(tokens, 0);
    unsigned int condition;
    char func_base[MAX_FUNCTION_LENGTH + 1];
    SplitFunction(func_code, func_base, &condition);

    void(*process_function)(FUNC_PROC_ARGS) = MapGet(func_proc, func_base);
    assert(process_function != NULL);
    process_function(symbols, tokens, output, offset, instructions_num);
}

void FinishFunctionGen() {
    DeleteMap(dummy);
    DeleteMap(func_proc);
    DeleteMap(func_cond_codes);
    DeleteMap(data_proc_opcodes);
    DeleteSet(comp_funcs);
}