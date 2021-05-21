#include <deque.h>
#include <queue.h>

Queue NewQueue() {
    return NewDeque();
}

void DeleteQueue(Queue restrict queue) {
    DeleteDeque(queue);
}

void QueuePush(Queue restrict queue, void* newItem) {
    DequePushBack(queue, newItem);
}

void* QueuePop(Queue restrict queue) {
    return DequePopFront(queue);
}

void* QueuePeekFront(Queue restrict queue) {
    return DequePeekFront(queue);
}

void* QueuePeekBack(Queue restrict queue) {
    return DequePeekBack(queue);
}

int QueueSize(Queue restrict queue) {
    return DequeSize(queue);
}

bool QueueEmpty(Queue restrict queue) {
    return DequeEmpty(queue);
}