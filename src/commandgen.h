#ifndef ASSEMBLE_FUNCTIONGEN_H_
#define ASSEMBLE_FUNCTIONGEN_H_

/*
 * Initializes the assembly function processing
 */
int init_functiongen();

/*
 * Processes a single command from assembly
 * 
 * @param symbols Map<char*, int> mapping labels to the addresses they point to
 * @param tokens Vector<char*> representing the function to process
 * @param output Vector<int> representing the final executable
 * @param offset int representing the word offset of the function to process
 */
int functiongen(Map symbols, Vector tokens, Vector output, int offset);

#endif /* ASSEMBLE_FUNCTIONGEN_H_ */
