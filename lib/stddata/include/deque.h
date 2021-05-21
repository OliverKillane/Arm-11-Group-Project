#ifndef STDDATA_DEQUE_H_
#define STDDATA_DEQUE_H_

#include "list.h"
#include <stdbool.h>

typedef List Deque;

/*
 * Creates a new deque
 */
Deque NewDeque();

/*
 * Deallocates a deque
 */
void DeleteDeque(Deque deque);

/*
 * Pushes an item in the front of a deque
 */
void DequePushFront(Deque deque, void* newItem);

/*
 * Pushes an item in the back of a deque
 */
void DequePushBack(Deque deque, void* newItem);

/*
 * Pops an item from the front of the deque
 * The deque must have at least one item
 */
void* DequePopFront(Deque deque);

/*
 * Pops an item from the back of the deque
 * The deque must have at least one item
 */
void* DequePopBack(Deque deque);

/*
 * Returns an item from the front of the deque
 * The deque must have at least one item
 */
void* DequePeekFront(Deque deque);

/*
 * Returns an item from the front of the deque
 * The deque must have at least one item
 */
void* DequePeekBack(Deque deque);

/*
 * Returns the number of items on the deque
 */
int DequeSize(Deque deque);

/*
 * Checks if the deque is empty
 */
bool DequeEmpty(Deque deque);

#endif /* STDDATA_DEQUE_H_ */