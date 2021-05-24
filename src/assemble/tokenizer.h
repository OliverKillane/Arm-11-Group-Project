#ifndef ASSEMBLE_TOKENIZER_H_
#define ASSEMBLE_TOKENIZER_H_

#include <stdbool.h>

enum TokenType {
    INSTRUCTION,
    REGISTER,
    CONSTANT,
    LABEL,
    SIGN,
    BRACE
};

enum ConstantType {
    HASH,
    EQUALS,
    PURE
};

enum ConditionType {
    EQ = 0x0,
    NE = 0x1,
    GE = 0xA,
    LT = 0xB,
    GT = 0xC,
    LE = 0xD,
    AL = 0xE
};

enum InstructionType {
    BRN,
    ADD,
    SUB,
    RSB,
    AND,
    EOR,
    ORR,
    MOV,
    TST,
    TEQ,
    CMP,
    MUL,
    MLA,
    LDR,
    STR,
    LSL,
    ASR,
    LSR,
    ROR
};

typedef const struct {
    TokenType type;
    union contents {
        struct {
            ConstantType type;
            long long value;
        } constant;
        struct {
            ConditionType condition;
            InstructionType type;
        } instruction;
        int reg_num;
        char label[512];
        bool is_plus;
        bool is_open;
    }
} TokenRepr;

typedef TokenRepr * Token;

Token NewToken(char* token_val);

void DeleteToken(Token token);

TokenType TokenType(Token token);

ConstantType TokenConstantType(Token token);

long long TokenConstantValue(Token token);

ConditionType TokenInstructionConditionType(Token token);

InstructionType TokenInstructionType(Token token);

int TokenRegisterNumber(Token token);

char* TokenLabel(Token token);

bool TokenIsPlus(Token token);

bool TokenIsOpenBracket(Token token);

#endif /* ASSEMBLE_TOKENIZER_H_ */
