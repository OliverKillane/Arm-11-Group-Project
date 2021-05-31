/**
 * @file stack.h 
 * @author Bartłomiej Cieślar
 * @brief @ref Stack and utilities related to it
 */
#ifndef STDDATA_STACK_H_
#define STDDATA_STACK_H_
#include "vector.h"
#include <stdbool.h>

/**
 * @brief An STL-like Stack
 * 
 * This is a vector based stack, meaning all operations on it are in amortized O(1).
 * It supports the following operations:
 *     - @ref StackPush Adds a new element to the top of the stack
 *     - @ref StackPop Removes an item from the top of the stack and returns it
 *     - @ref StackPeek Returns the item at the top of the stack
 * 
 * It can be created and deallocated using @ref NewStack and @ref DeleteStack respectively.
 * To check its size and test if it is empty, use @ref StackSize and @ref StackEmpty.
 * It can be optimized for size by shrinking it to the number of elements it has using 
 * @ref StackOptimize; however, this operation is in O(n).
 * 
 * @note Even though this is only a typedef, do not use @ref Vector as stack 
 *       for improved code clarity
 */
typedef Vector Stack;

/**
 * @brief Creates a new @ref Stack
 * 
 * Dynamically allocates a new @ref Stack using malloc.
 * 
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteStack to deallocate it once you are done using it.
 */
Stack NewStack();

/**
 * @brief Deallocates a @ref Stack
 *
 * @param stack The stack to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref Stack
 *          results in an undefined behaviour
 */
void DeleteStack(Stack stack);

/**
 * @brief Adds an item to the top of the stack
 * 
 * @param stack The stack to be modified
 * @param new_item A pointer to an item to add on top of the stack
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p stack not being a valid allocated @ref Stack results in an undefined behaviour
 */
void StackPush(Stack stack, void* new_item);

/**
 * @brief Removes an item from the top of the stack
 * 
 * @param stack The stack to be modified
 * @returns A pointer to the item removed from the stack
 * @warning Trying to remove an item from an empty stack results in an undefined behaviour
 * @warning @p stack not being a valid allocated @ref Stack results in an undefined behaviour
 */
void* StackPop(Stack stack);

/**
 * @brief Returns an item from the top of the stack without removing it
 * 
 * @param stack The stack containing the item
 * @returns The item at the top of the stack
 * @warning Trying to look up an item in an empty stack results in an undefined behaviour
 * @warning @p stack not being a valid allocated @ref Stack results in an undefined behaviour
 */
void* StackPeek(Stack stack);

/**
 * @brief Returns the number of items inside a stack
 * 
 * @param stack The stack to check the size of
 * @returns The size of the stack
 * @warning @p stack not being a valid allocated @ref Stack results in an undefined behaviour
 */
int StackSize(Stack stack);

/**
 * @brief Returns the number of items on a stack
 * 
 * @param stack The stack to check the size of
 * @returns The size of the stack
 * @warning @p stack not being a valid allocated @ref Stack results in an undefined behaviour
 */
bool StackEmpty(Stack stack);

/**
 * @brief Optimizes the size of a stack
 * 
 * The funciton reallocated the stack to be as close to the number of items on the stack as possible.
 * @note The copying of items to the new allocation is O(n), so it should not be used excessively
 * @warning @p stack not being a valid allocated @ref Stack results in an undefined behaviour
 */
void StackOptimize(Stack stack);

#endif /* STDDATA_STACK_H_ */