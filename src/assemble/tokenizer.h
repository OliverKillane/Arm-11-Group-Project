#ifndef ASSEMBLE_TOKENIZER_H_
#define ASSEMBLE_TOKENIZER_H_

#include "stddata.h"
#include "./tokenizer/token_utils.h"

typedef enum {
    TOKENIZER_START,
    TOKENIZER_INSTR_LABEL_REG,
    TOKENIZER_REGISTER,
    TOKENIZER_CONSTANT,
    TOKENIZER_LABEL,
    TOKENIZER_INSTR,
    TOKENIZER_ERROR,
    TOKENIZER_FINISHED,
} TokenizerState;

static char currentToken[512];
static int currentTokenLength;
static TokenizerState currentState;

bool matchAlpha(char c);
bool isHex(char c);
bool isWhitespace(char c);
void addCharToToken(char c);
void removeCharFromToken();
void resetToken();
bool isNumber(char *str);
ConditionType matchConditionType(char *str);
Token matchInstructionToken(char *str);
int matchDecimal(char *str);
int matchHex(char *str);
Token matchRegister(char *str);
Token matchConstant(char *str);
void addTokenToSymbolTable(Map symbolTable, int currentLine, char *token);
List tokenizeTextLine(char *line, Map symbolTable, int currentLine);
void tokenizeDataLine(char *line, Map symbolTable, int *currentAddress, Vector dataVector);

#endif /* ASSEMBLE_TOKENIZER_H_ */
