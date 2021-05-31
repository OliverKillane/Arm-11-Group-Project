/**
 * @file queue.h
 * @author Bartłomiej Cieślar
 * @brief @ref Queue and utilities related to it
 */
#ifndef STDDATA_QUEUE_H_
#define STDDATA_QUEUE_H_

#include "deque.h"
#include <stdbool.h>

/**
 * @brief An STL-like Queue
 * 
 * This is a linked-list-based queue, meaning all operations on it are in O(1).
 * It supports the following operations:
 *     - @ref QueuePush Adds a new element to the back of the the queue
 *     - @ref QueuePop Removes an item from the front of the queue and returns it
 *     - @ref QueuePeekFront Returns the item at the front of the queue
 *     - @ref QueuePeekBack Returns the item at the back of the queue
 * 
 * It can be created and deallocated using @ref NewQueue and @ref DeleteQueue respectively.
 * To check its size and test if it is empty, use @ref QueueSize and @ref QueueEmpty
 * 
 * @note Even though this is only a typedef, do not use @ref List or @ref Deque 
 *       as a queue for improved code clarity
 */
typedef Deque Queue;

/**
 * @brief Creates a new @ref Queue
 * 
 * Dynamically allocates a new @ref Queue using malloc.
 * 
 * @warning In order to avoid memory leaks, please use 
 *          @ref DeleteQueue to deallocate it once you are done using it.
 */
Queue NewQueue();

/**
 * @brief Deallocates a @ref Queue
 *
 * @param queue The queue to be deallocated
 * @warning Trying to use or deallocate already deallocated @ref Queue 
 *          results in an undefined behaviour
 */
void DeleteQueue(Queue queue);

/**
 * @brief Pushes an item in the back of the queue
 * 
 * @param queue The queue to be modifier
 * @param new_item A pointer to an item to push in front of the queue
 * 
 * @note the @p new_item may be used to hold an integer value as well if it fits inside a void*
 * @warning @p queue not being a valid allocated @ref Queue results in an undefined behaviour
 */
void QueuePush(Queue queue, void* new_item);

/**
 * @brief Removes an item from the front of the queue
 * 
 * @param queue The queue to be modified
 * @returns A pointer to the item removed from the queue
 * @warning Trying to remove an item from an empty queue results in an undefined behaviour
 * @warning @p queue not being a valid allocated @ref Queue results in an undefined behaviour
 */
void* QueuePop(Queue queue);

/**
 * @brief Returns an item from the front of the queue (the one to be popped next) 
 *        without removing it
 * 
 * @param queue The queue containing the item
 * @returns The item at the front of the queue
 * @warning Trying to look up an item in an empty queue results in an undefined behaviour
 * @warning @p queue not being a valid allocated @ref Queue results in an undefined behaviour
 */
void* QueuePeekFront(Queue queue);

/**
 * @brief Returns an item from the back of the queue (the one most recently pushed) 
 *        without removing it
 * 
 * @param queue The queue containing the item
 * @returns The item at the front of the queue
 * @warning Trying to look up an item in an empty queue results in an undefined behaviour
 * @warning @p queue not being a valid allocated @ref Queue results in an undefined behaviour
 */
void* QueuePeekBack(Queue queue);

/**
 * @brief Returns the number of items inside a queue
 * 
 * @param queue The queue to check the size of
 * @returns The size of the queue
 * @warning @p queue not being a valid allocated @ref Queue results in an undefined behaviour
 */
int QueueSize(Queue queue);

/**
 * @brief Checks if the queue is empty
 * 
 * @param queue The queue to check the emptiness of
 * @returns @b true if the queue has no items, otherwise @b false
 * @warning @p queue not being a valid allocated @ref Queue results in an undefined behaviour
 */
bool QueueEmpty(Queue queue);

#endif /* STDDATA_QUEUE_H_ */