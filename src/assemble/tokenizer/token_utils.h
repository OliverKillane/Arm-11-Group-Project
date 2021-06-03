#ifndef ASSEMBLE_TOKEN_UTILS_H_
#define ASSEMBLE_TOKEN_UTILS_H_

#include <stdbool.h>

typedef enum {
    TOKEN_INSTRUCTION = 10, // to be able to map over them
    TOKEN_REGISTER,
    TOKEN_CONSTANT,
    TOKEN_LABEL,
    TOKEN_SIGN,
    TOKEN_BRACE,
    TOKEN_EXCLAMATION
} TokenKind;

typedef enum {
    CONST_HASH = 10, // to be able to map over them
    CONST_EQUALS,
    CONST_PURE
} ConstantType;

typedef enum {
    COND_EQ = 0x0, // to be able to map over them
    COND_NE = 0x1,
    COND_GE = 0xA,
    COND_LT = 0xB,
    COND_GT = 0xC,
    COND_LE = 0xD,
    COND_AL = 0xE,
    COND_FAIL // Used in token matching.
} ConditionType;

typedef enum {
    INSTR_BRN = 10, // to be able to map over them
    INSTR_BRL,
    INSTR_RET,
    INSTR_PSH,
    INSTR_POP,
    INSTR_HLT,
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

typedef struct {
    TokenKind type;
    union {
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
    };
} TokenRepr;

typedef TokenRepr * Token;

Token NewInstructionToken(ConditionType cond, InstructionType instr);

Token NewRegisterToken(int reg);

Token NewConstantToken(ConstantType type, long long value);

Token NewLabelToken(char *label);

Token NewSignToken(bool is_plus);

Token NewBraceToken(bool is_open);

Token NewExclamationToken();


void DeleteToken(Token token);

TokenKind TokenType(Token token);

ConstantType TokenConstantType(Token token);

long long TokenConstantValue(Token token);

ConditionType TokenInstructionConditionType(Token token);

InstructionType TokenInstructionType(Token token);

int TokenRegisterNumber(Token token);

char* TokenLabel(Token token);

bool TokenIsPlus(Token token);

bool TokenIsOpenBracket(Token token);

#endif /* ASSEMBLE_TOKEN_UTILS_H_ */
