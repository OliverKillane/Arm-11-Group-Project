#include "../tokenizer.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stddata.h"

bool matchAlpha(char c) {
    return isalpha(c) != 0;
}

bool isHex(char c) {
    return isdigit(c)
        || (c >= 'A' && c <= 'F')
        || (c >= 'a' && c <= 'f');
}

bool isWhitespace(char c) {
    return c == ' ' || c == '\t';
}

void addCharToToken(char c) {
    currentToken[currentTokenLength] = c;
    currentTokenLength++;
}

void removeCharFromToken() {
    currentTokenLength--;
}

void resetToken() {
    currentTokenLength = 0;
}

bool isNumber(char *str) {
    if (*str == '-') {
        str++;
    }
    for (; *str != '\0'; str++)
    {
        if (!isdigit(*str)){
            return false;
        }
    }

    return true;
}

ConditionType matchConditionType(char *str) {
    ConditionType condTyp = COND_FAIL;
    if (strlen(str) == 0) {
        condTyp = COND_AL;
    } else if (strlen(str) > 2) {
        return COND_FAIL;
    } else if (strcmp(str, "eq") == 0) {
        condTyp = COND_EQ;
    } else if (strcmp(str, "ne") == 0) {
        condTyp = COND_NE;
    }  else if (strcmp(str, "ge") == 0) {
        condTyp = COND_GE;
    }  else if (strcmp(str, "lt") == 0) {
        condTyp = COND_LT;
    }  else if (strcmp(str, "gt") == 0) {
        condTyp = COND_GT;
    }  else if (strcmp(str, "le") == 0) {
        condTyp = COND_LE;
    }
    return condTyp;
}

Token matchInstructionToken(char *str) {
    InstructionType instTyp;
    if (*str == 'b') {
        instTyp = INSTR_BRN;
        str += 1;
    } else if (strncmp(str, "add", 3) == 0) {
        instTyp = INSTR_ADD;
        str += 3;
    } else if (strncmp(str, "sub", 3) == 0) {
        instTyp = INSTR_SUB;
        str += 3;
    } else if (strncmp(str, "rsb", 3) == 0) {
        instTyp = INSTR_RSB;
        str += 3;
    } else if (strncmp(str, "and", 3) == 0) {
        instTyp = INSTR_AND;
        str += 3;
    } else if (strncmp(str, "eor", 3) == 0) {
        instTyp = INSTR_EOR;
        str += 3;
    } else if (strncmp(str, "orr", 3) == 0) {
        instTyp = INSTR_ORR;
        str += 3;
    } else if (strncmp(str, "mov", 3) == 0) {
        instTyp = INSTR_MOV;
        str += 3;
    } else if (strncmp(str, "tst", 3) == 0) {
        instTyp = INSTR_TST;
        str += 3;
    } else if (strncmp(str, "teq", 3) == 0) {
        instTyp = INSTR_TEQ;
        str += 3;
    } else if (strncmp(str, "cmp", 3) == 0) {
        instTyp = INSTR_CMP;
        str += 3;
    } else if (strncmp(str, "mul", 3) == 0) {
        instTyp = INSTR_MUL;
        str += 3;
    } else if (strncmp(str, "mla", 3) == 0) {
        instTyp = INSTR_MLA;
        str += 3;
    } else if (strncmp(str, "ldr", 3) == 0) {
        instTyp = INSTR_LDR;
        str += 3;
    } else if (strncmp(str, "str", 3) == 0) {
        instTyp = INSTR_STR;
        str += 3;
    } else if (strncmp(str, "lsl", 3) == 0) {
        instTyp = INSTR_LSL;
        str += 3;
    } else if (strncmp(str, "asr", 3) == 0) {
        instTyp = INSTR_ASR;
        str += 3;
    } else if (strncmp(str, "lsr", 3) == 0) {
        instTyp = INSTR_LSR;
        str += 3;
    } else if (strncmp(str, "ror", 3) == 0) {
        instTyp = INSTR_ROR;
        str += 3;
    } else {
        return NULL;
    }
    ConditionType condTyp = matchConditionType(str);
    if (condTyp == COND_FAIL) {
        return NULL;
    }
    return NewInstructionToken(condTyp, instTyp);
}

int matchDecimal(char *str) {
    bool negated = false;
    if (*str == '-') {
        negated = true;
        str++;
    }
    int num = 0;
    for (; *str != '\0'; str++)
    {
        assert(isdigit(*str));
        num *= 10;
        num += *str - '0'; // ascii value for '0'
    }

    if (negated) {
        num = -num;
    }

    return num;
}

bool isHexNumber(char *str) {
    if (*str == '-') {
        str++;
    }

    for (; *str != '\0'; str++)
    {
        if (!isHex(*str)){
            return false;
        }
    }

    return true;
}


int matchHex(char *str) {
    bool negated = false;
    if (*str == '-') {
        negated = true;
        str++;
    }
    int num = 0;
    // printf("%s\n", str);

    for (; *str != '\0'; str++)
    {
        assert(isHex(*str));
        num *= 16;
        if (isdigit(*str)) {
            num += *str - '0';
        } else {
            char tmpstr = *str | 32; // convert to lowercase
            num += tmpstr - 'a' + 10;
        }
    }

    if (negated) {
        num = -num;
    }

    return num;
}

Token matchRegister(char *str) {
    if (*str != 'r') {
        return NULL;
    }
    str++;
    if (!isNumber(str)) {
        return NULL;
    }
    int num = matchDecimal(str);

    if (num < 0 || num > 16) {
        return NULL;
    }

    return NewRegisterToken(num);
}

Token matchConstant(char *str) {
    ConstantType conType;
    if (*str == '=') {
        conType = CONST_EQUALS;
        str++;
    } else if (*str == '#') {
        conType = CONST_HASH;
        str++;
    } else {
        conType = CONST_PURE;
    }
    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }
    
    
    
    if (strlen(str) < 3) {
        if (isNumber(str)) {
            return NewConstantToken(conType, sign*matchDecimal(str));
        } else {
            return NULL;
        }
    } else {
        if (str[0] == '0' && str[1] == 'x') {
            str += 2;
            if (isHexNumber(str)) {
                return NewConstantToken(conType, sign*matchHex(str));
            } else {
                return NULL;
            }
            
        } else {
            if (isNumber(str)) {
                return NewConstantToken(conType, sign*matchDecimal(str));
            } else {
                return NULL;
            }
        }
    }
}

void addTokenToSymbolTable(Map symbolTable, int currentLine, char *token) {
    char *label = malloc(strlen(token)+1);
    strcpy(label,token);

    MapSet(symbolTable, label, currentLine);
}


List tokenizeLine(char *line, Map symbolTable, int currentLine) {
    List tokenList = NewEmptyList();
    currentTokenLength = 0;
    currentState = TOKENIZER_START;

    while (currentState != TOKENIZER_FINISHED 
        && currentState != TOKENIZER_ERROR) {

        switch (currentState) {

            case TOKENIZER_START:
                if (isalpha(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_INSTR_LABEL_REG;
                } else if (line[0] == '[')  {
                    ListPushBack(tokenList, NewBraceToken(true));
                } else if (line[0] == ']')  {
                    ListPushBack(tokenList, NewBraceToken(false));
                } else if (line[0] == '+')  {
                    ListPushBack(tokenList, NewSignToken(true));
                } else if (line[0] == '-')  {
                    ListPushBack(tokenList, NewSignToken(false));
                } else if (line[0] == '#' || line[0] == '=' || isHex(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_CONSTANT;
                } else if (line[0] == '\n') {
                    currentState = TOKENIZER_FINISHED;
                }
                break;
            case TOKENIZER_INSTR_LABEL_REG:
                if (isalpha(line[0])) {
                    addCharToToken(line[0]);
                } else if (line[0] == ':') {
                    addCharToToken('\0');
                    addTokenToSymbolTable(symbolTable, currentLine, currentToken);
                    resetToken();
                    currentState = TOKENIZER_START;
                } else if (isdigit(line[0])) {
                    addCharToToken(line[0]);
                    
                } else {
                    addCharToToken('\0');
                    Token matchedInstruction = matchInstructionToken(currentToken);
                    Token matchedRegister = NULL;
                    if (matchedInstruction == NULL) {
                        matchedRegister = matchRegister(currentToken);
                    }

                    if (matchedInstruction != NULL) {
                        ListPushBack(tokenList, matchedInstruction);
                        
                    } else if (matchedRegister != NULL) {
                        ListPushBack(tokenList, matchedRegister);
                    } else {
                        
                        Token newToken = NewLabelToken(currentToken);
                        ListPushBack(tokenList, newToken);
                    }
                    currentState = TOKENIZER_START;
                    resetToken();
                    line--;
                }
                break;
            case TOKENIZER_CONSTANT:
                if (isHex(line[0]) || line[0] == 'x' || line[0] == '-') {
                    addCharToToken(line[0]);
                } else {
                    addCharToToken('\0');
                    Token matchedConstant = matchConstant(currentToken);
                    if (matchedConstant != NULL) {
                        ListPushBack(tokenList, matchedConstant);
                        resetToken();
                        currentState = TOKENIZER_START;
                    } else {
                        currentState = TOKENIZER_ERROR;
                    }
                    currentState = TOKENIZER_START;
                    line--;
                }
            
            default:
                break;
        }

        if (line[0] != '\0') {
            line++;
        }
    }
    return tokenList;

}