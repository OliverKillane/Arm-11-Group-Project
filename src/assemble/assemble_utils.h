#ifndef ASSEMBLE_UTILS_H
#define ASSEMBLE_UTILS_H

#include "stddata.h"

void removeColon(char *str);

void writeBinary(Vector program, char *filename);

void readFileLines(char *filename, List textLines, List dataLines);

List tokenize(List lines, Map symbolTable, int *totalInstructions, Vector dataVector);

Vector tokensToBinary(Map symbolTable, List listOfTokens, Vector dataVector, int totalInstructions);

#endif