#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "stddata.h"

void removeColon(char *str);

void writeBinary(Vector program, char *filename);

List readFileLines(char *filename);

List tokenize(List lines, Map symbolTable, int *totalInstructions);

Vector tokensToBinary(Map symbolTable, List listOfTokens, int totalInstructions);

#endif