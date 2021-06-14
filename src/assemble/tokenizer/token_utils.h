#ifndef ASSEMBLE_TOKEN_UTILS_H_
#define ASSEMBLE_TOKEN_UTILS_H_

#include <stdbool.h>

/**
 * @brief Enum that determines the type of token.
 */
typedef enum {
    TOKEN_INSTRUCTION = 10, // to be able to map over them
    TOKEN_REGISTER,
    TOKEN_CONSTANT,
    TOKEN_LABEL,
    TOKEN_SIGN,
    TOKEN_BRACE,
    TOKEN_EXCLAMATION
} TokenKind;

/**
 * @brief Enum that determines the type constant a constant token represents.
 */
typedef enum {
    CONST_HASH = 10, // to be able to map over them
    CONST_EQUALS,
    CONST_PURE,
    CONST_ANY // for handling labels
} ConstantType;

/**
 * @brief Enum that determines the type condition an instruction token represents.
 */
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

/**
 * @brief Enum that determines the type instruction an instruction token represents.
 */
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


/**
 * @brief Enum that determines the type of label a label token represents.
 */
typedef enum {
    LABEL_FULL = 10, // to be able to map over them
    LABEL_FIRST8,
    LABEL_SECOND8,
    LABEL_THIRD8,
    LABEL_FOURTH8
} LabelType;

/**
 * @brief A struct that contains all of the token information. This is used for tokenizing and command generation.
 */
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
        struct {
            char string[512];
            LabelType type;
        } label;
        bool is_plus;
        bool is_open;
    };
} TokenRepr;

typedef TokenRepr * Token;

/**
 * @brief Creates a new token of type TOKEN_INSTRUCTION.
 */
Token NewInstructionToken(ConditionType cond, InstructionType instr);

/**
 * @brief Creates a new token of type TOKEN_REGISTER.
 * @param reg is the register that is being referenced.
 * @warning @p reg should be in the range 0-16.
 */
Token NewRegisterToken(int reg);

/**
 * @brief Creates a new token of type TOKEN_CONSTANT.
 * @param value is the value of the constant token
 */
Token NewConstantToken(ConstantType type, long long value);

/**
 * @brief Creates a new token of type TOKEN_LABEL.
 * @param label is a pointer to a string that will be copied into the token.
 */
Token NewLabelToken(char *label, LabelType type);

/**
 * @brief Creates a new token of type TOKEN_SIGN.
 * @param is_plus is true if the token was '+' and false if the token was '-'.
 */
Token NewSignToken(bool is_plus);

/**
 * @brief Creates a new token of type TOKEN_BRACE.
 * @param is_open is true if the token was '[' and false if the token was ']'.
 */
Token NewBraceToken(bool is_open);

/**
 * @brief Creates a new token of type TOKEN_EXCLAIMATION.
 */
Token NewExclamationToken();

/**
 * @brief Deallocates the given token.
 */
void DeleteToken(Token token);

/**
 * @brief Returns the token type of a given token.
 */
TokenKind TokenType(Token token);


/**
 * @brief Returns the token constant type of a provided token.
 * 
 * @warning asserts token is of type TOKEN_CONSTANT
 */
ConstantType TokenConstantType(Token token);

/**
 * @brief Returns the token constant value of a provided token.
 * 
 * @warning asserts token is of type TOKEN_CONSTANT
 */
long long TokenConstantValue(Token token);

/**
 * @brief Returns the instruction condition type of a provided token.
 * 
 * @warning asserts token is of type TOKEN_INSTRUCTION
 */
ConditionType TokenInstructionConditionType(Token token);

/**
 * @brief Returns the instruction type of a provided token.
 * 
 * @warning asserts token is of type TOKEN_INSTRUCTION
 */
InstructionType TokenInstructionType(Token token);

/**
 * @brief Returns the register type value of a provided token.
 * 
 * @warning asserts token is of type TOKEN_REGISTER
 */
int TokenRegisterNumber(Token token);

/**
 * @brief Returns the label string of a provided token.
 * 
 * @warning asserts token is of type TOKEN_LABEL
 */
char* TokenLabel(Token token);

/**
 * @brief Returns the label type of a provided token.
 * 
 * @warning asserts token is of type TOKEN_LABEL
 */
LabelType TokenLabelType(Token token);

/**
 * @brief Returns true if the token is '+' and not if the token is '-'.
 * 
 * @warning asserts token is of type TOKEN_SIGN
 */
bool TokenIsPlus(Token token);

/**
 * @brief Returns true if the token is '[' and not if the token is ']'.
 * 
 * @warning asserts token is of type TOKEN_BRACE
 */
bool TokenIsOpenBracket(Token token);

#endif /* ASSEMBLE_TOKEN_UTILS_H_ */
