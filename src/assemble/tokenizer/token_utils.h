<<<<<<< HEAD
/**
 * @file token_utils.h 
 * @author Jordan HaLL
 * @brief @ref Helper functions and enums related to the Token struct.
 */
=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
#ifndef ASSEMBLE_TOKEN_UTILS_H_
#define ASSEMBLE_TOKEN_UTILS_H_

#include <stdbool.h>

<<<<<<< HEAD
/**
 * @brief An enum for describing the type of token that this struct represents.
 * 
 * Each token type needs its own enum for ensuring the right helper functions
 * are used on each token.
 * 
 * @note the enums have a value of 10 so that they may be used as void pointers.
 */
=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
typedef enum {
    TOKEN_INSTRUCTION = 10, // to be able to map over them
    TOKEN_REGISTER,
    TOKEN_CONSTANT,
    TOKEN_LABEL,
    TOKEN_SIGN,
    TOKEN_BRACE,
} TokenKind;
<<<<<<< HEAD
/**
 * @brief An enum for describing the type of constant a constant type token represents.
 * 
 * There are three different types of constants that can appear in the assembly. Equals, Hash,
 * and Pure constants.
 * 
 * @note the enums have a value of 10 so that they may be used as void pointers.
 */
=======

>>>>>>> assemble_tokenizer_commongen_using_decision_tree
typedef enum {
    CONST_HASH = 10, // to be able to map over them
    CONST_EQUALS,
    CONST_PURE
} ConstantType;

<<<<<<< HEAD
/**
 * @brief An enum for describing the type of condition an instruction token has.
 * 
 * @note the enums have a value of 10 so that they may be used as void pointers.
 */

=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
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

<<<<<<< HEAD
/**
 * @brief An enum for describing the type of instruction an instruction token has.
 * 
 * @note the enums have a value of 10 so that they may be used as void pointers.
 */

=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
typedef enum {
    INSTR_BRN = 10, // to be able to map over them
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

<<<<<<< HEAD
/**
 * @brief A struct for containing data associated with tokens.
 * 
 * The struct contains a TokenKind enum, which describes the type of token
 * and limits the functions that can be called on it.
 * Then it has a union that describes the type of data that can be associated with the
 * struct depending on what the type is. The constant struct is associated with the 
 * Constant token type, the instruction struct is associated with the instruction token.
 * reg_num, label, is_plus and is_open are associated with register, label, sign and brace tokens.
 * 
 * @warning Attempting to access values in the union not associated with TokenKind will result in
 *          undefined behaviour.
 */

=======
>>>>>>> assemble_tokenizer_commongen_using_decision_tree
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
<<<<<<< HEAD
/**
 * @brief A function for allocating and preparing an Instruction token with @ref ConditionType enum and @ref InstructionType enums.
 * @warning token will need to be deleted with @ref DeleteToken to free associated memory.
 */
Token NewInstructionToken(ConditionType cond, InstructionType instr);
/**
 * @brief A function for allocating and preparing an Register token with register number as integer.
 * @warning token will need to be deleted with @ref DeleteToken to free associated memory.
 */
Token NewRegisterToken(int reg);
/**
 * @brief A function for allocating and preparing a Constant token with ConstantType and a 
 * value associated with the token.
 * @warning token will need to be deleted with @ref DeleteToken to free associated memory.
 */
Token NewConstantToken(ConstantType type, long long value);
/**
 * @brief A function for allocating and preparing an Label token with string as label value.
 * @note string is copied into a byte array of size 512. 
 * @warning token will need to be deleted with @ref DeleteToken to free associated memory.
 */
Token NewLabelToken(char *label);
/**
 * @brief A function for allocating and preparing a Sign token, with a boolean desciribing if
 * the sign is a plus or minus sign
 * @warning token will need to be deleted with @ref DeleteToken to free associated memory.
 */
Token NewSignToken(bool is_plus);
/**
 * @brief A function for allocating and preparing a Brace token, with a boolean desciribing if
 * the brace is an open or close brace.
 * @warning token will need to be deleted with @ref DeleteToken to free associated memory.
 */
Token NewBraceToken(bool is_open);

/**
 * @brief A function for deallocating a token and its data when it's no longer needed.
 */
void DeleteToken(Token token);
/**
 * @brief A function for getting the token kind associated with a Token struct.
 */
TokenKind TokenType(Token token);
/**
 * @brief A function for getting the ConstantKind associated with a Constant Token struct.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_CONSTANT.
 */
ConstantType TokenConstantType(Token token);
/**
 * @brief A function for getting the value associated with a Constant Token struct.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_CONSTANT.
 */
long long TokenConstantValue(Token token);
/**
 * @brief A function for getting the ConditionType associated with an Instruction Token struct.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_INSTRUCTION.
 */
ConditionType TokenInstructionConditionType(Token token);
/**
 * @brief A function for getting the InstructionType associated with an Instruction Token struct.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_INSTRUCTION.
 */
InstructionType TokenInstructionType(Token token);
/**
 * @brief A function for getting the register number associated with an Register Token struct.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_REGISTER.
 */
int TokenRegisterNumber(Token token);
/**
 * @brief A function for getting the label associated with an Label Token struct.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_LABEL.
 */
char* TokenLabel(Token token);
/**
 * @brief A function that returns true if the sign of the token is a '+'.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_SIGN.
 */
bool TokenIsPlus(Token token);
/**
 * @brief A function that returns true if the character of the token is a '['.
 * @warning this function will assert that the TokenKind associated with the Token is TOKEN_BRACE.
 */
=======

Token NewInstructionToken(ConditionType cond, InstructionType instr);

Token NewRegisterToken(int reg);

Token NewConstantToken(ConstantType type, long long value);

Token NewLabelToken(char *label);

Token NewSignToken(bool is_plus);

Token NewBraceToken(bool is_open);


void DeleteToken(Token token);

TokenKind TokenType(Token token);

ConstantType TokenConstantType(Token token);

long long TokenConstantValue(Token token);

ConditionType TokenInstructionConditionType(Token token);

InstructionType TokenInstructionType(Token token);

int TokenRegisterNumber(Token token);

char* TokenLabel(Token token);

bool TokenIsPlus(Token token);
>>>>>>> assemble_tokenizer_commongen_using_decision_tree

bool TokenIsOpenBracket(Token token);

#endif /* ASSEMBLE_TOKEN_UTILS_H_ */
