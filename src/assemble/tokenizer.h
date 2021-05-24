#ifndef ASSEMBLE_TOKENIZER_H_
#define ASSEMBLE_TOKENIZER_H_

#include <stdbool.h>

typedef enum {
    TOKEN_INSTRUCTION,
    TOKEN_REGISTER,
    TOKEN_CONSTANT,
    TOKEN_LABEL,
    TOKEN_SIGN,
    TOKEN_BRACE
} TokenType;

typedef enum {
    CONST_HASH,
    CONST_EQUALS,
    CONST_PURE
} ConstantType;

typedef enum {
    COND_EQ = 0x0,
    COND_NE = 0x1,
    COND_GE = 0xA,
    COND_LT = 0xB,
    COND_GT = 0xC,
    COND_LE = 0xD,
    COND_AL = 0xE
} ConditionType;

typedef enum {
    INSTR_BRN,
    INSTR_ADD,
    INSTR_SUB,
    INSTR_RSB,
    INSTR_AND,
    INSTR_EOR,
    INSTR_ORR,
    INSTR_MOV,
    INSTR_TST,
    INSTR_TEQ,
    INSTR_CMP,
    INSTR_MUL,
    INSTR_MLA,
    INSTR_LDR,
    INSTR_STR,
    INSTR_LSL,
    INSTR_ASR,
    INSTR_LSR,
    INSTR_ROR
} InstructionType;

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
