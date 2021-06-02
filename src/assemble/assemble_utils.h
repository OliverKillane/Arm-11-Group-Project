#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "stddata.h"

/**
 * @brief Writes the contents of @p program data vector to a file associated with @p filename .
 * @note the endian that the file is written in is the endian associated with the machine architecture. 
 * @warning having non-int values in @p program will cause undefined behaviour.
 */
void writeBinary(Vector program, char *filename);

/**
 * @brief Reads the contents of @p filename into a list of strings.
 * @note The strings in each of the returned list has been allocated and then copied, so the user of this
 * function will have to ensure that the strings are freed along with the list itself.
 */
List readFileLines(char *filename);

/**
 * @brief Tokenizes @p lines into a list, and adds forward references into @p symbolTable and increments @p totalInstructions accordingly.
 * @note The tokens in each of the returned list has been allocated and then copied, so the user of this
 * function will have to ensure that the strings are freed along with the list itself.
 */
List tokenize(List lines, Map symbolTable, int *totalInstructions);

Vector tokensToBinary(Map symbolTable, List listOfTokens, int totalInstructions);

#endif