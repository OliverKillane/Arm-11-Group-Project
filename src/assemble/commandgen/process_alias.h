/**
 * @file process_alias.h
 * @author Bartłomiej Cieślar
 * @brief aliased instructions processing
 */
#ifndef ASSEMBLE_COMMANDGEN_PROCESS_ALIAS_H_
#define ASSEMBLE_COMMANDGEN_PROCESS_ALIAS_H_

#include <stddata.h>
#include <stdbool.h>

/**
 * @brief Handles the return instruction
 */
bool LayoutRet(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

/**
 * @brief Handles the halt alias
 */
bool LayoutHalt(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

/**
 * @brief Handles the stack push instruction
 */
bool LayoutPush(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

/**
 * @brief Handles the stack pop instruction
 */
bool LayoutPop(
    Map symbols, 
    Vector tokens, 
    Vector text,
    Vector data, 
    int offset, 
    int instructions_num
);

#endif /* ASSEMBLE_COMMANDGEN_PROCESS_ALIAS_H_ */
