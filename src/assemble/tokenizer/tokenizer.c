#include "tokenizer.h"
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stddata.h"

bool inline matchAlpha(char c) {
    return isalpha(c) != 0;
}

bool inline isHex(char c) {
    return isdigit(c)
        || (c >= 'A' && c <= 'F')
        || (c >= 'a' && c <= 'f');
}

bool inline isWhitespace(char c) {
    return c == ' ' || c == '\t';
}

void match(bool (*func)(char), char c) {
    assert(func(c));
}

CharacterType getCharType(char c) {
    CharacterType type = 0;

    if (isWhitespace(c)) {
        type |= WHITESPACE;
    }
    if (isdigit(c)) {
        type |= NUMERIC;
    }
    if (isHex(c)) {
        type |= HEX;
    }
    if (c == ':'){
        type |= COLON;
    }
    return type;
}

void addCharToToken(char c) {
    currentToken[currentTokenLength] = c;
    currentTokenLength++;
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
    if (*str == 'j') {
        instTyp = INSTR_BRN;
        str++;
    } else if (strcmp(str, "add") == 0) {
        instTyp = INSTR_ADD;
        str += 3;
    } else if (strcmp(str, "sub") == 0) {
        instTyp = INSTR_SUB;
        str += 3;
    } else if (strcmp(str, "rsb") == 0) {
        instTyp = INSTR_RSB;
        str += 3;
    } else if (strcmp(str, "and") == 0) {
        instTyp = INSTR_AND;
        str += 3;
    } else if (strcmp(str, "eor") == 0) {
        instTyp = INSTR_EOR;
        str += 3;
    } else if (strcmp(str, "orr") == 0) {
        instTyp = INSTR_ORR;
        str += 3;
    } else if (strcmp(str, "mov") == 0) {
        instTyp = INSTR_MOV;
        str += 3;
    } else if (strcmp(str, "tst") == 0) {
        instTyp = INSTR_TST;
        str += 3;
    } else if (strcmp(str, "teq") == 0) {
        instTyp = INSTR_TEQ;
        str += 3;
    } else if (strcmp(str, "cmp") == 0) {
        instTyp = INSTR_CMP;
        str += 3;
    } else if (strcmp(str, "mul") == 0) {
        instTyp = INSTR_MUL;
        str += 3;
    } else if (strcmp(str, "mla") == 0) {
        instTyp = INSTR_MLA;
        str += 3;
    } else if (strcmp(str, "ldr") == 0) {
        instTyp = INSTR_LDR;
        str += 3;
    } else if (strcmp(str, "str") == 0) {
        instTyp = INSTR_STR;
        str += 3;
    } else if (strcmp(str, "lsl") == 0) {
        instTyp = INSTR_LSL;
        str += 3;
    } else if (strcmp(str, "asr") == 0) {
        instTyp = INSTR_ASR;
        str += 3;
    } else if (strcmp(str, "lsr") == 0) {
        instTyp = INSTR_LSR;
        str += 3;
    } else if (strcmp(str, "ror") == 0) {
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

int matchHex(char *str) {
    bool negated = false;
    if (*str == '-') {
        negated = true;
        str++;
    }
    int num = 0;

    for (; *str != '\0'; str++)
    {
        assert(isHex(*str));
        num *= 16;
        if (isdigit(*str)) {
            num += *str - '0';
        } else {
            *str |= 32; // convert to lowercase
            num += *str - 'a' + 10;
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
    
    
    if (strlen(str) < 3) {
        return NewConstantToken(conType, matchDecimal(str));
    } else {
        if (str[0] == '0' && str[1] == 'x') {
            str += 2;
            return NewConstantToken(conType, matchHex(str));
        } else {
            return NewConstantToken(conType, matchDecimal(str));
        }
    }
}

void addTokenToSymbolTable(Map symbolTable, int currentLine, char *token) {
    char *label = malloc(strlen(token)+1);
    strcpy(label,token);

    MapSet(symbolTable, label, currentLine);
}


List tokenizeLine(char *line, Map symbolTable, int currentLine) {
    // printf("Started function\n");
    List tokenList = NewEmptyList();
    currentTokenLength = 0;
    currentState = TOKENIZER_START;

    while (currentState != TOKENIZER_FINISHED 
        && currentState != TOKENIZER_ERROR) {

        // printf("Current line:%s\n", line);

        CharacterType charType = getCharType(line[0]);

        switch (currentState) {

            case TOKENIZER_START:
                // printf("STATE: START\n");
                if (isalpha(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_INSTR_LABEL_REG;
                } else if (line[0] == '[')  {
                    ListPushBack(tokenList, NewBraceToken(true));
                } else if (line[0] == ']')  {
                    ListPushBack(tokenList, NewBraceToken(false));
                } else if (line[0] == '#' || line[0] == '=' || isHex(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_CONSTANT;
                } else if (line[0] == '\n') {
                    currentState = TOKENIZER_FINISHED;
                }
                break;
            case TOKENIZER_INSTR_LABEL_REG:

                // printf("STATE: INSTR LABEL REG\n");
                if (isalpha(line[0])) {
                    addCharToToken(line[0]);
                } else if (line[0] == ':') {
                    addCharToToken('\0');
                    addTokenToSymbolTable(symbolTable, currentLine, currentToken);
                    // ListPushBack(tokenList, NewLabelToken(currentToken));
                    resetToken();
                    currentState = TOKENIZER_START;
                } else if (isdigit(line[0])) {
                    addCharToToken(line[0]);
                    currentState = TOKENIZER_REGISTER;
                } else {
                    addCharToToken('\0');
                    Token matchedInstruction = matchInstructionToken(currentToken);
                    // printf("matched token\n");
                    // printf("Token: %x\n", matchedInstruction);
                    if (matchedInstruction != NULL) {
                        ListPushBack(tokenList, matchedInstruction);
                        
                    } else {
                        
                        Token newToken = NewLabelToken(currentToken);
                        // printf("Found token to be a label\n");
                        ListPushBack(tokenList, newToken);
                        // printf("Wow!\n");
                    }
                    currentState = TOKENIZER_START;
                    // printf("finished making token\n");
                    resetToken();
                    line--;
                }
                break;
            case TOKENIZER_REGISTER:
                if (isdigit(line[0])) {
                    addCharToToken(line[0]);
                } else {
                    addCharToToken('\0');
                    Token matchedRegister = matchRegister(currentToken);
                    if (matchedRegister != NULL) {
                        ListPushBack(tokenList, matchedRegister);
                        resetToken();
                        currentState = TOKENIZER_START;
                    } else {
                        currentState = TOKENIZER_ERROR;
                    }
                    currentState = TOKENIZER_START;
                    line--;
                }
                break;
            case TOKENIZER_CONSTANT:
                if (isHex(line[0]) || line[0] == 'x') {
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

    // if (currentState == TOKENIZER_FINISHED) {
    //     printf("Tokenizer has finished\n");
    // } else {
    //     printf("Tokenizer error\n");
    // }

    return tokenList;

}