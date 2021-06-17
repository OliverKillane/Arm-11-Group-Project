#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "stddata.h"

/**
 * @brief Given a vector of integers @p program, writes the binary value of these integers to the file of @p filename .
 * @warning asserts that the path to filename exists.
 */
void writeBinary(Vector program, char *filename);

/**
 * @brief Given a vector of integers @p program, writes the binary value of these integers to the file of @p filename .
 * @warning asserts that the path to filename exists.
 */
void readFileLines(char *filename, List textLines, List dataLines);

/**
 * @brief takes @p lines of list of null-terminated strings, and a symbol table, and returns a list of token vectors 
 * that can be used to generate the binary files. Calls tokenizeLine on each line of assembly code.
 */
List tokenize(List lines, Map symbolTable, int *totalInstructions, Vector dataVector);
/**
 * @brief Calls command generation function on each line of tokenized assembly, and will handle errors if they arise in
 * code generation. Returns a vector that maps from one to four bytes in the file.
 */
Vector tokensToBinary(Map symbolTable, List listOfTokens, Vector dataVector, int totalInstructions);

#endif