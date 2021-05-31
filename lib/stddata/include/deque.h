/**
 * @file deque.h
 * @author Bartłomiej Cieślar
 * @brief @ref Deque and utilities related to it
 */
#ifndef STDDATA_DEQUE_H_
#define STDDATA_DEQUE_H_

#include "list.h"
#include <stdbool.h>

/**
 * @brief An STL-like Deque
 * 
 * This is a linked-list-based deque, meaning all operations on it are in O(1).
 * It supports the following operations:
 *     - @ref DequePushFront Adds a new element to the front of the deque
 *     - @ref DequePushBack Adds a new element to the back of the the deque
 *     - @ref DequePopFront Removes an item from the front of the deque and returns it
 *     - @ref DequePopBack Removes an item from the back of the deque and returns it
 *     - @ref DequePeekFront Returns the item at the front of the deque
 *     - @ref DequePeekBack Returns the item at the back of the deque
 * 
 * It can be created and deallocated using @ref NewDeque and @ref DeleteDeque respectively.
 * To check its size and test if it is empty, use @ref DequeSize and @ref DequeEmpty
 * 
 * @note Even though this is only a typedef, do not use @ref List as deque for improved code clarity
 */
typedef List Deque;

/**
 * @brief Creates a new @ref Deque
 * 
 * Dynamically allocates a new @ref Deque using malloc.
 * 
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteDeque to deallocate it once you are done using it.
 */
Deque NewDeque();

/**
 * @brief Deallocates a @ref Deque
 *
 * @param deque The deque to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref Deque 
 *          results in an undefined behaviour
 */
void DeleteDeque(Deque deque);

/**
 * @brief Pushes an item in the front of the deque
 * 
 * @param deque The deque to be modified
 * @param new_item A pointer to an item to push in front of the deque
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
void DequePushFront(Deque deque, void* new_item);

/**
 * @brief Pushes an item in the back of the deque
 * 
 * @param deque The deque to be modifier
 * @param new_item A pointer to an item to push in front of the deque
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
void DequePushBack(Deque deque, void* new_item);

/**
 * @brief Removes an item from the front of the deque
 * 
 * @param deque The deque to be modified
 * @returns A pointer to the item removed from the deque
 * @warning Trying to remove an item from an empty deque results in an undefined behaviour
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
void* DequePopFront(Deque deque);

/**
 * @brief Removes an item from the back of the deque
 * 
 * @param deque The deque to be modified
 * @returns A pointer to the item removed from the deque
 * @warning Trying to remove an item from an empty deque results in an undefined behaviour
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
void* DequePopBack(Deque deque);

/**
 * @brief Returns an item from the front of the deque without removing it
 * 
 * @param deque The deque containing the item
 * @returns The item at the front of the deque
 * @warning Trying to look up an item in an empty deque results in an undefined behaviour
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
void* DequePeekFront(Deque deque);

/**
 * @brief Returns an item from the back of the deque without removing it
 * 
 * @param deque The deque containing the item
 * @returns The item at the back of the deque
 * @warning Trying to look up an item in an empty deque results in an undefined behaviour
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
void* DequePeekBack(Deque deque);

/**
 * @brief Returns the number of items inside a deque
 * 
 * @param deque The deque to check the size of
 * @returns The size of the deque
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
int DequeSize(Deque deque);

/**
 * @brief Checks if the deque is empty
 * 
 * @param deque The deque to check the emptiness of
 * @returns @b true if the deque has no items, otherwise @b false
 * @warning @p deque not being a valid allocated @ref Deque results in an undefined behaviour
 */
bool DequeEmpty(Deque deque);

#endif /* STDDATA_DEQUE_H_ */