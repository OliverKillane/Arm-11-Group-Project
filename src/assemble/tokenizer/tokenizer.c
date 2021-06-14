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
    if (strncmp(str, "brl", 3) == 0) {
        instTyp = INSTR_BRL;
        str += 3;
    } else if (strncmp(str, "b", 1) == 0) {
        instTyp = INSTR_BRN;
        str += 1;
    } else if (strncmp(str, "add", 3) == 0) {
        instTyp = INSTR_ADD;
        str += 3;
    } else if (strncmp(str, "sub", 3) == 0) {
        instTyp = INSTR_SUB;
        str += 3;
    } else if (strncmp(str, "hlt", 3) == 0) {
        instTyp = INSTR_HLT;
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
    } else if (strncmp(str, "pop", 3) == 0) {
        instTyp = INSTR_POP;
        str += 3;
    } else if (strncmp(str, "ret", 3) == 0) {
        instTyp = INSTR_RET;
        str += 3;
    } else if (strncmp(str, "halt", 4) == 0) {
        return NewInstructionToken(COND_AL, INSTR_HLT);
    } else if (strncmp(str, "push", 4) == 0) {
        instTyp = INSTR_PSH;
        str += 4;
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


long long matchHex(char *str) {
    bool negated = false;
    if (*str == '-') {
        negated = true;
        str++;
    }
    long long num = 0;
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

    MapSet(symbolTable, label, currentLine*4);
}

LabelType matchLabelType(char *str) {
    if (strcmp(str, "first8") == 0) {
        return LABEL_FIRST8;
    } else if (strcmp(str, "second8") == 0) {
        return LABEL_SECOND8;
    } else if (strcmp(str, "third8") == 0) {
        return LABEL_THIRD8;
    } else if (strcmp(str, "fourth8") == 0) {
        return LABEL_FOURTH8;
    }
    printf("Failed to match a label type %s\n", str);
    assert(false);
}

DirectiveType matchDirective(char *str) {
    if (strcmp(str, "set") == 0) {
        return DIRECTIVE_SET;
    } else if (strcmp(str, "long") == 0) {
        return DIRECTIVE_LONG;
    }
    printf("unrecognized directive %s\n", str);
    assert(false);
}

Vector tokenizeTextLine(char *line, Map symbolTable, int currentLine, Vector dataVector, char *filename, int lineNumber) {
    Vector tokenList = NewEmptyVector();

    char *preservedLine = line;
    
    
    TokenizerState currentState = TOKENIZER_START;
    LabelType currentLabelType = LABEL_FULL;
    DirectiveType currentDirectiveType = DIRECTIVE_NONE;
    char *currentDirectiveLabel;

    while (currentState != TOKENIZER_FINISHED 
        && currentState != TOKENIZER_ERROR) {

        switch (currentState) {

            case TOKENIZER_START:
                if (isalpha(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_INSTR_LABEL_REG;
                } else if (line[0] == '[')  {
                    VectorPushBack(tokenList, NewBraceToken(true));
                } else if (line[0] == ']')  {
                    VectorPushBack(tokenList, NewBraceToken(false));
                } else if (line[0] == '+')  {
                    VectorPushBack(tokenList, NewSignToken(true));
                } else if (line[0] == '-')  {
                    VectorPushBack(tokenList, NewSignToken(false));
                } else if (line[0] == '!')  {
                    VectorPushBack(tokenList, NewExclamationToken());
                }else if (line[0] == '#' || line[0] == '=' || isHex(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_CONSTANT;
                } else if (line[0] == '\n' || line[0] == '@') {
                    currentState = TOKENIZER_FINISHED;
                } else if (line[0] == ':') {
                    currentState = TOKENIZER_LABEL_ORDER;
                } else if (line[0] == '.') {
                    currentState = TOKENIZER_DIRECTIVE;
                }
                break;
            case TOKENIZER_LABEL_ORDER:
                if (isalpha(line[0]) || line[0] == '8') {
                    addCharToToken(line[0]);
                } else if (line[0] == ':') {
                    addCharToToken('\0');
                    currentLabelType = matchLabelType(currentToken);
                    resetToken();
                    currentState = TOKENIZER_START;
                }
                break;
            case TOKENIZER_DIRECTIVE:
                if (isalpha(line[0])) {
                    addCharToToken(line[0]);
                } else {
                    addCharToToken('\0');
                    // printf("heyy %s\n", currentToken);
                    currentDirectiveType = matchDirective(currentToken);
                    if (currentDirectiveType == DIRECTIVE_SET) {
                        // printf("wow matched set directive\n");
                        currentState = TOKENIZER_INSTR_LABEL_REG;
                    } else if (currentDirectiveType == DIRECTIVE_LONG) {
                        // printf("wow matched long directive\n");
                        currentState = TOKENIZER_CONSTANT;
                    }
                    resetToken();
                }
                break;
            case TOKENIZER_INSTR_LABEL_REG:
                if (isalpha(line[0]) || line[0] == '_') {
                    addCharToToken(line[0]);
                } else if (line[0] == ':') {
                    addCharToToken('\0');
                    printf("Label set %s %d\n", currentToken, currentLine);
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
                        VectorPushBack(tokenList, matchedInstruction);
                        
                    } else if (matchedRegister != NULL) {
                        VectorPushBack(tokenList, matchedRegister);
                    } else {
                        if (currentDirectiveType == DIRECTIVE_SET) {
                            addCharToToken('\0');
                            currentDirectiveLabel = malloc((strlen(currentToken) + 1) * sizeof(char));
                            strcpy(currentDirectiveLabel, currentToken);
                            resetToken();
                            currentState = TOKENIZER_CONSTANT;

                        } else {
                            Token newToken = NewLabelToken(currentToken, currentLabelType);
                            VectorPushBack(tokenList, newToken);
                            currentLabelType = LABEL_FULL;
                        }
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
                        if (currentDirectiveType == DIRECTIVE_NONE) {
                            VectorPushBack(tokenList, matchedConstant);
                        } else if (currentDirectiveType == DIRECTIVE_LONG) {
                            // printf("%d\n", matchedConstant->constant.value);
                            VectorPushBack(dataVector, matchedConstant->constant.value);
                            currentDirectiveType = DIRECTIVE_NONE;
                        } else if (currentDirectiveType == DIRECTIVE_SET) {
                            printf("Label set %s %d\n", currentDirectiveLabel, matchedConstant->constant.value);
                            MapSet(symbolTable, currentDirectiveLabel, matchedConstant->constant.value);
                            // printf("%s %d\n", currentDirectiveLabel, MapGet(symbolTable, currentDirectiveLabel));
                            currentDirectiveType = DIRECTIVE_NONE;
                        }
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
        } else {
            currentState = TOKENIZER_FINISHED;
        }
    }

    VectorPushBack(tokenList, preservedLine);
    VectorPushBack(tokenList, filename);
    VectorPushBack(tokenList, lineNumber);
    return tokenList;

}

// void tokenizeDataLine(char *line, Map symbolTable, int *currentAddress, Vector dataVector) {

//     char *endl = strchr(line, '\n');
//     if (endl != NULL) {
//         *endl = '\0';
//     }
//     char *at = strchr(line, '@');
//     if (at != NULL) {
//         *at = '\0';
//     }
//     char *colon;

//     if (strncmp(line, ".set", 4) == 0) {
//         line+=5;
//         char *endLabel = strchr(line, ' ');
//         char *newLabel = malloc(sizeof(char) * (endLabel - line+1));
//         strncpy(newLabel, line, (endLabel - line));
//         newLabel[endLabel - line + 1] = '\0';
//         line = endLabel + 1;
//         int number;

//         if (isHexNumber(line)) {
//             number = matchHex(line);
//         } else {
//             number = matchDecimal(line);
//         }
//         MapSet(symbolTable, newLabel, number);
//     } else if (strncmp(line, ".long", 5) == 0) {
//         line += 6;
//         int number;
//         if (isHexNumber(line)) {
//             number = matchHex(line);
//         } else {
//             number = matchDecimal(line);
//         }
//         VectorPushBack(dataVector, number);
//         *currentAddress += 1;
//     } else if ((colon = strchr(line, ':')) != NULL) {
//         char *newLabel = malloc((colon - line +1) * sizeof(char));
//         strncpy(newLabel, line, (colon - line));
//         newLabel[colon - line + 1] = '\0';
//         MapSet(symbolTable, newLabel, *currentAddress);
//     }

// }