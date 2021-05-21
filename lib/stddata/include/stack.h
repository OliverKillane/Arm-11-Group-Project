#ifndef STDDATA_STACK_H_
#define STDDATA_STACK_H_
#include "vector.h"
#include <stdbool.h>

typedef Vector Stack;

/*
 * Creates new stack
 */
Stack NewStack();

/*
 * Deallocates a stack
 */
void DeleteStack(Stack stack);

/* 
 * Pushes a new element onto a stack
 */
void StackPush(Stack stack, void* newItem);

/*
 * Pops an element from a stack
 */
void* StackPop(Stack stack);

/*
 * Returns an element on top of a stack
 */
void* StackPeek(Stack stack);

/*
 * Returns a stack size
 */
int StackSize(Stack stack);

/*
 * Checks if a stack is empty
 */
bool StackEmpty(Stack stack);

/*
 * Optimizes the size of a stack
 */
void StackOptimize(Stack stack);

#endif /* STDDATA_STACK_H_ */