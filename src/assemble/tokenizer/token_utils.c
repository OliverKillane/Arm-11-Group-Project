#include "token_utils.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


Token NewInstructionToken(ConditionType cond, InstructionType instr) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { 
        .type = TOKEN_INSTRUCTION, 
        .instruction = { cond, instr }
    };
    return token;
}

Token NewRegisterToken(int reg) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) {
        .type = TOKEN_REGISTER, 
        .reg_num = reg 
    };
    return token;
}

Token NewConstantToken(ConstantType type, long long value) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) {
        .type = TOKEN_CONSTANT, 
        .constant = { type, value }
    };
    return token;
}

Token NewLabelToken(char *label) {
    Token token = malloc(sizeof(TokenRepr));
    token -> type = TOKEN_LABEL;
    strncpy(token -> label, label, 512);
    return token;
}

Token NewSignToken(bool is_plus) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) { 
        .type = TOKEN_SIGN,
        .is_plus = is_plus
    };
    return token;
}

Token NewBraceToken(bool is_open) {
    Token token = malloc(sizeof(TokenRepr));
    *token = (TokenRepr) {
        .type = TOKEN_BRACE, 
        .is_open = is_open
    };
    return token;
}

void DeleteToken(Token token) {
    assert(token != NULL);
    if (TokenType(token) == TOKEN_LABEL) {
        free(token -> label);
    }
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