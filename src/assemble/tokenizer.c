#include "tokenizer.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>


Token NewInstructionToken(ConditionType cond, InstructionType instr) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { TOKEN_INSTRUCTION, cond, instr };
    return token;
}

Token NewRegisterToken(int reg) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { TOKEN_REGISTER, reg };
    return token;
}

Token NewConstantToken(ConstantType type, long long value) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { TOKEN_CONSTANT, type, value };
    return token;
}

Token NewLabelToken(char label[512]) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { TOKEN_LABEL, label };
    return token;
}

Token NewSignToken(bool is_plus) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { TOKEN_SIGN, is_plus };
    return token;
}

Token NewBraceToken(bool is_open) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { TOKEN_BRACE, is_open };
    return token;
}

void DeleteToken(Token token) {
    assert(token != NULL);
    free(token);
}

TokenKind TokenType(Token token) {
    assert(token != NULL);
    return token -> type;
}

ConstantType TokenConstantType(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_CONSTANT);
    return token -> constant.type;
}

long long TokenConstantValue(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_CONSTANT);
    return token -> constant.value;
}

ConditionType TokenInstructionConditionType(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_INSTRUCTION);
    return token -> instruction.condition;
}

InstructionType TokenInstructionType(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_INSTRUCTION);
    return token -> instruction.type;
}

int TokenRegisterNumber(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_REGISTER);
    return token -> reg_num;
}

char* TokenLabel(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_LABEL);
    return token -> label;
}

bool TokenIsPlus(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_SIGN);
    return token -> is_plus;
}

bool TokenIsOpenBracket(Token token) {
    assert(token != NULL);
    assert(token -> type == TOKEN_BRACE);
    return token -> is_open;
}