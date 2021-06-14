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
    TOKENIZER_LABEL_ORDER,
    TOKENIZER_DIRECTIVE,
    TOKENIZER_SET,
    TOKENIZER_LONG
} TokenizerState;

typedef enum {
    DIRECTIVE_SET,
    DIRECTIVE_LONG,
    DIRECTIVE_NONE
} DirectiveType;

static char currentToken[512];
static int currentTokenLength = 0;

/**
 * @brief returns true if @p c is an alpha character.
 */
bool matchAlpha(char c);
/**
 * @brief returns true if @p c is a 0-9 | a-f.
 */
bool isHex(char c);
/**
 * @brief returns true if @p c is a tab or space or newline.
 */
bool isWhitespace(char c);
/**
 * @brief adds a @p c to the currentToken variable and increments currentTokenLength.
 */
void addCharToToken(char c);
/**
 * @brief removes a character from currentToken and decrements currentTokenLength.
 */
void removeCharFromToken();
/**
 * @brief sets currentTokenLength to 0.
 */
void resetToken();
/**
 * @brief returns true if the null-terminated string @p str is a decimal number.
 */
bool isNumber(char *str);
/**
 * @brief Matches @p str to a selection of condition types.
 */
ConditionType matchConditionType(char *str);
/**
 * @brief Matches @p str to a selection of instruction types.
 */
Token matchInstructionToken(char *str);
/**
 * @brief converts a null-terminated base 10 string @p str into a long long.
 */
long long matchDecimal(char *str);
/**
 * @brief converts a null-terminated hexadecimal formatted string @p str into a long long.
 */
long long matchHex(char *str);
/**
 * @brief matches a register type token with the null-terminated string @p str .
 */
Token matchRegister(char *str);
/**
 * @brief matches a constant type token with the null-terminated string @p str .
 */
Token matchConstant(char *str);
/**
 * @brief copies the null-terminated string @p token and adds it as a key to @p symbolTable with @p currentLine as the value.
 */
void addTokenToSymbolTable(Map symbolTable, int currentLine, char *token);
/**
 * @brief Tokenizes the null-terminated string @p line into a list of tokens. Modifies @p symbolTable and @p dataVector in line with the spec of the assembler.
 */
Vector tokenizeTextLine(char *line, Map symbolTable, int currentLine, Vector dataVector, char *filename, int lineNumber);

#endif /* ASSEMBLE_TOKENIZER_H_ */
