#ifndef STDDATA_QUEUE_H_
#define STDDATA_QUEUE_H_

#include "deque.h"
#include <stdbool.h>

typedef Deque Queue;

/*
 * Creates a new queue
 */
Queue NewQueue();

/*
 * Deallocates a queue
 */
void DeleteQueue(Queue queue);

/*
 * Pushes an item onto a queue
 */
void QueuePush(Queue queue, void* newItem);

/*
 * Pops an item from the queue
 * The queue must have at least one item
 */
void* QueuePop(Queue queue);

/*
 * Returns an item from the front of the queue
 * The queue must have at least one item
 */
void* QueuePeekFront(Queue queue);

/*
 * Returns an item from the front of the queue
 * The queue must have at least one item
 */
void* QueuePeekBack(Queue queue);

/*
 * Returns the number of items on the queue
 */
int QueueSize(Queue queue);

/*
 * Checks if the queue is empty
 */
bool QueueEmpty(Queue queue);

#endif /* STDDATA_QUEUE_H_ */